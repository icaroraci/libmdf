/* Copyright (c) 2026 Gabriel Lampa da Cunha <gabriellampa@gmail.com>
 *
 * This file is part of libmdf.
 *
 * libmdf is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libmdf is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libmdf.  If not, see <https://www.gnu.org/licenses/>.
 * */

/* Exemplo: emite um MDF-e rodoviário de homologação (um veículo, um
 * condutor, uma NF-e), assina com o certificado A1, acrescenta o QR Code
 * e conversa com os webservices da SVRS.
 *
 * Compilar e executar (na raiz do projeto):
 *   make exemplos
 *   ./obj/emitir_mdfe <arquivo.pfx> <senha> [comando]
 *
 * Comandos (sem comando, escreve o MDF-e assinado na saída padrão, sem
 * acessar a rede):
 *   status                      status do serviço (107: em operação)
 *   autorizar                   transmite o MDF-e; escreve o mdfeProc
 *   consultar <chave>           situação do MDF-e
 *   encerrar <chave> <nProt>    evento de encerramento (UF e município de
 *                               MDF_CUF_FIM e MDF_CMUN_FIM)
 *   cancelar <chave> <nProt>    evento de cancelamento
 *   nao-encerrados              MDF-e não encerrados do emitente
 * O cStat e o motivo vão para a saída de erros; os XML (mdfeProc,
 * procEventoMDFe ou o retorno da consulta), para a saída padrão.
 *
 * Os dados vêm de variáveis de ambiente; sem elas valem os dados fictícios
 * do RS, que só servem sem comando:
 *   MDF_CNPJ, MDF_IE, MDF_XNOME, MDF_CUF (43), MDF_UF (RS),
 *   MDF_CMUN (4314902), MDF_XMUN (PORTO ALEGRE), MDF_SERIE (1),
 *   MDF_NMDF (1), MDF_PLACA, MDF_TARA (5000), MDF_RNTRC (opcional),
 *   MDF_CONDUTOR_CPF, MDF_CONDUTOR_NOME, MDF_CHNFE (chave da NF-e
 *   transportada), MDF_UF_FIM (RS), MDF_CUF_FIM (43),
 *   MDF_CMUN_FIM (4304606), MDF_XMUN_FIM (CANOAS),
 *   MDF_CA (arquivo PEM com as autoridades certificadoras da SEFAZ, se as
 *   do sistema não bastarem).
 *
 * Com o certificado de teste:
 *   ./obj/emitir_mdfe tests/certificados/teste.pfx teste
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <libnfe/assinatura.h>
#include <libnfe/erros.h>
#include <libnfe/grupo.h>
#include <libnfe/sefaz.h>
#include <libmdf/evento.h>
#include <libmdf/mdfe.h>
#include <libmdf/sefaz.h>
#include <libmdf/versao.h>

#define AMB NFE_AMBIENTE_HOMOLOGACAO

/* Variável de ambiente ou o valor padrão */
static const char *var(const char *nome, const char *padrao)
{
	const char *v = getenv(nome);

	return v && *v ? v : padrao;
}

static int set(nfe_grupo *g, const char *campo, const char *valor)
{
	int rc = nfe_grupo_set(g, campo, valor);

	if (rc != 0)
		fprintf(stderr, "%s = \"%s\": %s\n", campo, valor,
		        nfe_strerror(rc));
	return rc;
}

/* Data e hora atuais no fuso de Brasília */
static void agora(char *dh, size_t tam, int so_data)
{
	time_t t = time(NULL) - 3 * 3600;
	struct tm tm = *gmtime(&t);

	strftime(dh, tam, so_data ? "%Y-%m-%d" : "%Y-%m-%dT%H:%M:%S-03:00",
	         &tm);
}

static mdf_mdfe *monta(void)
{
	mdf_mdfe *m = mdf_mdfe_new();
	nfe_grupo *ide, *emit, *rodo, *item, *doc;
	char dh[32], cmdf[16];
	int rc = 0;

	if (!m)
		return NULL;
	agora(dh, sizeof dh, 0);
	snprintf(cmdf, sizeof cmdf, "%08ld", (long)(time(NULL) % 100000000));
	ide = mdf_mdfe_grupo(m, "ide");
	rc |= set(ide, "cUF", var("MDF_CUF", "43"));
	rc |= set(ide, "tpAmb", "2");
	rc |= set(ide, "tpEmit", "2"); /* transportador de carga própria */
	rc |= set(ide, "serie", var("MDF_SERIE", "1"));
	rc |= set(ide, "nMDF", var("MDF_NMDF", "1"));
	rc |= set(ide, "cMDF", cmdf);
	rc |= set(ide, "modal", "1");
	rc |= set(ide, "dhEmi", dh);
	rc |= set(ide, "tpEmis", "1");
	rc |= set(ide, "procEmi", "0");
	rc |= set(ide, "verProc", "libmdf " MDF_VERSAO);
	rc |= set(ide, "UFIni", var("MDF_UF", "RS"));
	rc |= set(ide, "UFFim", var("MDF_UF_FIM", "RS"));
	rc |= nfe_grupo_add(ide, "infMunCarrega", &item);
	if (rc == 0) {
		rc |= set(item, "cMunCarrega", var("MDF_CMUN", "4314902"));
		rc |= set(item, "xMunCarrega", var("MDF_XMUN", "PORTO ALEGRE"));
	}

	emit = mdf_mdfe_grupo(m, "emit");
	rc |= set(emit, "CNPJ", var("MDF_CNPJ", "11222333000181"));
	rc |= set(emit, "IE", var("MDF_IE", "0960000000"));
	rc |= set(emit, "xNome", var("MDF_XNOME", "EMPRESA DE TESTE LTDA"));
	rc |= set(emit, "xLgr", var("MDF_XLGR", "RUA DOS TESTES"));
	rc |= set(emit, "nro", var("MDF_NRO", "100"));
	rc |= set(emit, "xBairro", var("MDF_XBAIRRO", "CENTRO"));
	rc |= set(emit, "cMun", var("MDF_CMUN", "4314902"));
	rc |= set(emit, "xMun", var("MDF_XMUN", "PORTO ALEGRE"));
	rc |= set(emit, "UF", var("MDF_UF", "RS"));

	rodo = mdf_mdfe_grupo(m, "rodo");
	if (getenv("MDF_RNTRC"))
		rc |= set(rodo, "infANTT/RNTRC", getenv("MDF_RNTRC"));
	rc |= set(rodo, "veicTracao/placa", var("MDF_PLACA", "ABC1D23"));
	rc |= set(rodo, "veicTracao/tara", var("MDF_TARA", "5000"));
	rc |= set(rodo, "veicTracao/tpRod", "02"); /* toco */
	rc |= set(rodo, "veicTracao/tpCar", "02"); /* fechada/baú */
	rc |= set(rodo, "veicTracao/UF", var("MDF_UF", "RS"));
	rc |= nfe_grupo_add(rodo, "veicTracao/condutor", &item);
	if (rc == 0) {
		rc |= set(item, "xNome",
		          var("MDF_CONDUTOR_NOME", "JOSE DA SILVA"));
		rc |= set(item, "CPF", var("MDF_CONDUTOR_CPF", "12345678909"));
	}

	rc |= nfe_grupo_add(mdf_mdfe_grupo(m, "infDoc"), "infMunDescarga",
	                    &item);
	if (rc == 0) {
		rc |= set(item, "cMunDescarga", var("MDF_CMUN_FIM", "4304606"));
		rc |= set(item, "xMunDescarga", var("MDF_XMUN_FIM", "CANOAS"));
		rc |= nfe_grupo_add(item, "infNFe", &doc);
		if (rc == 0)
			rc |= set(doc, "chNFe",
			          var("MDF_CHNFE", "432610112223330001815500"
			                           "10000001231000001232"));
	}

	rc |= set(mdf_mdfe_grupo(m, "prodPred"), "tpCarga", "05");
	rc |= set(mdf_mdfe_grupo(m, "prodPred"), "xProd",
	          "MERCADORIAS DIVERSAS");
	rc |= set(mdf_mdfe_grupo(m, "tot"), "qNFe", "1");
	rc |= set(mdf_mdfe_grupo(m, "tot"), "vCarga", "1000.00");
	rc |= set(mdf_mdfe_grupo(m, "tot"), "cUnid", "01");
	rc |= set(mdf_mdfe_grupo(m, "tot"), "qCarga", "100.0000");
	if (rc != 0) {
		mdf_mdfe_free(m);
		return NULL;
	}
	return m;
}

/* Evento de encerramento ou cancelamento, assinado */
static char *evento(const nfe_certificado *cert, mdf_tipo_evento tipo,
                    const char *chave, const char *nprot)
{
	mdf_evento *e = mdf_evento_new(tipo);
	nfe_grupo *det = mdf_evento_detalhe(e);
	char dh[32], data[16], *xml = NULL, *assinado = NULL;
	size_t tam = 0;
	int rc;

	agora(dh, sizeof dh, 0);
	agora(data, sizeof data, 1);
	rc = mdf_evento_set_chave(e, chave);
	if (rc == 0)
		rc = mdf_evento_set_autor(e, var("MDF_CNPJ", "11222333000181"));
	if (rc == 0)
		rc = mdf_evento_set_ambiente(e, AMB);
	if (rc == 0)
		rc = mdf_evento_set_data(e, dh);
	if (rc == 0)
		rc = set(det, "nProt", nprot);
	if (rc == 0 && tipo == MDF_EVENTO_ENCERRAMENTO) {
		rc |= set(det, "dtEnc", data);
		rc |= set(det, "cUF", var("MDF_CUF_FIM", "43"));
		rc |= set(det, "cMun", var("MDF_CMUN_FIM", "4304606"));
	} else if (rc == 0) {
		rc = set(det, "xJust", "MDF-E DE TESTE EMITIDO PELA LIBMDF");
	}
	if (rc == 0)
		rc = mdf_evento_xml(e, &xml, &tam);
	if (rc == 0)
		rc = nfe_assinar_elemento(cert, xml, tam, "infEvento",
		                          &assinado, NULL);
	if (rc != 0)
		fprintf(stderr, "evento: %s\n", nfe_strerror(rc));
	free(xml);
	mdf_evento_free(e);
	return assinado;
}

static int resultado(nfe_sefaz *s, int rc, int cstat, const char *motivo,
                     char *xml)
{
	if (rc != 0) {
		fprintf(stderr, "erro: %s %s\n", nfe_strerror(rc),
		        nfe_sefaz_erro(s));
		return 1;
	}
	fprintf(stderr, "cStat %d: %s\n", cstat, motivo);
	if (xml)
		printf("%s\n", xml);
	free(xml);
	return 0;
}

int main(int argc, char **argv)
{
	const char *cmd = argc > 3 ? argv[3] : NULL, *url;
	char motivo[256], chave[MDF_TAM_CHAVE + 1];
	char *xml = NULL, *mdfe = NULL, *saida = NULL;
	nfe_certificado *cert;
	nfe_sefaz *s = NULL;
	mdf_mdfe *m = NULL;
	size_t tam = 0;
	int rc, cstat = 0, falhou = 1;

	if (argc < 3) {
		fprintf(stderr, "uso: %s <arquivo.pfx> <senha> [comando]\n",
		        argv[0]);
		return 2;
	}
	cert = nfe_certificado_pfx(argv[1], argv[2], &rc);
	if (!cert) {
		fprintf(stderr, "certificado: %s\n", nfe_strerror(rc));
		return 1;
	}
	if (cmd) {
		s = nfe_sefaz_new(cert);
		if (s && getenv("MDF_CA"))
			nfe_sefaz_set_ca(s, getenv("MDF_CA"));
	}

	if (!cmd || strcmp(cmd, "autorizar") == 0) {
		m = monta();
		rc = m ? mdf_mdfe_xml(m, &xml, &tam) : E_VALOR;
		if (rc == 0)
			rc = mdf_assinar(cert, xml, tam, &mdfe, NULL);
		if (rc == 0 && mdf_mdfe_chave(m, chave) == 0)
			fprintf(stderr, "chave %s\n", chave);
		if (rc != 0) {
			fprintf(stderr, "MDF-e: %s\n", nfe_strerror(rc));
		} else if (!cmd) {
			printf("%s\n", mdfe);
			falhou = 0;
		} else {
			mdf_sefaz_endereco(AMB, MDF_SERVICO_AUTORIZACAO, &url);
			rc = mdf_sefaz_autorizar(s, url, mdfe, &cstat, motivo,
			                         sizeof motivo, &saida, NULL);
			falhou = resultado(s, rc, cstat, motivo, saida);
		}
	} else if (strcmp(cmd, "status") == 0) {
		mdf_sefaz_endereco(AMB, MDF_SERVICO_STATUS, &url);
		rc = mdf_sefaz_status(s, url, AMB, &cstat, motivo,
		                      sizeof motivo);
		falhou = resultado(s, rc, cstat, motivo, NULL);
	} else if (strcmp(cmd, "consultar") == 0 && argc > 4) {
		mdf_sefaz_endereco(AMB, MDF_SERVICO_CONSULTA, &url);
		rc = mdf_sefaz_consultar(s, url, AMB, argv[4], &cstat, motivo,
		                         sizeof motivo, &saida, NULL);
		falhou = resultado(s, rc, cstat, motivo, saida);
	} else if (strcmp(cmd, "nao-encerrados") == 0) {
		mdf_sefaz_endereco(AMB, MDF_SERVICO_NAO_ENCERRADOS, &url);
		rc = mdf_sefaz_nao_encerrados(
		        s, url, AMB, var("MDF_CNPJ", "11222333000181"), &cstat,
		        motivo, sizeof motivo, &saida, NULL);
		falhou = resultado(s, rc, cstat, motivo, saida);
	} else if ((strcmp(cmd, "encerrar") == 0 ||
	            strcmp(cmd, "cancelar") == 0) &&
	           argc > 5) {
		char *ev = evento(cert,
		                  cmd[0] == 'e' ? MDF_EVENTO_ENCERRAMENTO
		                                : MDF_EVENTO_CANCELAMENTO,
		                  argv[4], argv[5]);

		if (ev) {
			mdf_sefaz_endereco(AMB, MDF_SERVICO_EVENTO, &url);
			rc = mdf_sefaz_evento(s, url, ev, &cstat, motivo,
			                      sizeof motivo, &saida, NULL);
			falhou = resultado(s, rc, cstat, motivo, saida);
		}
		free(ev);
	} else {
		fprintf(stderr, "comando desconhecido ou incompleto: %s\n",
		        cmd);
		falhou = 2;
	}

	free(mdfe);
	free(xml);
	mdf_mdfe_free(m);
	nfe_sefaz_free(s);
	nfe_certificado_free(cert);
	return falhou;
}
