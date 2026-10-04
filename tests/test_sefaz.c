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

/* Testes dos webservices do MDF-e (sefaz.h): endereços da SVRS e cada
 * serviço contra o servidor falso tests/servidor_sefaz.py (HTTPS com
 * autenticação mútua, em 127.0.0.1), com o MDF-e e o evento assinados com o
 * certificado de teste; o mdfeProc e o procEventoMDFe são validados contra
 * os schemas oficiais.
 *
 * Uso: test_sefaz <diretório tests> */

#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include <libnfe/erros.h>
#include <libnfe/validar.h>
#include <libmdf/evento.h>
#include <libmdf/mdfe.h>
#include <libmdf/sefaz.h>

#include "teste.h"
#include "mdfe_teste.h"

static const char *dir_testes;
static int porta;

/* Inicia o servidor falso; devolve o pid e a porta em porta (0 se não foi
 * possível) */
static pid_t inicia_servidor(void)
{
	char script[1024], linha[32];
	int fd[2];
	pid_t pid;
	FILE *f;

	porta = 0;
	snprintf(script, sizeof script, "%s/servidor_sefaz.py", dir_testes);
	if (pipe(fd) != 0)
		return -1;
	pid = fork();
	if (pid < 0)
		return -1;
	if (pid == 0) {
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("python3", "python3", script, dir_testes, (char *)NULL);
		_exit(127);
	}
	close(fd[1]);
	f = fdopen(fd[0], "r");
	if (f && fgets(linha, sizeof linha, f))
		porta = atoi(linha);
	if (f)
		fclose(f);
	else
		close(fd[0]);
	return pid;
}

static const char *url(const char *caminho)
{
	static char u[128];

	snprintf(u, sizeof u, "https://127.0.0.1:%d%s", porta, caminho);
	return u;
}

static int valida(const char *xsd, const char *xml, size_t tam)
{
	char caminho[1024];
	nfe_validador *v;
	nfe_erros *erros = nfe_erros_new();
	int rc, i;

	snprintf(caminho, sizeof caminho, "%s/schemas/mdfe/%s", dir_testes,
	         xsd);
	v = nfe_validador_xsd(caminho);
	if (!v) {
		nfe_erros_free(erros);
		return E_ARQUIVO;
	}
	rc = nfe_validar_xsd(v, xml, tam, 0, erros);
	for (i = 0; i < nfe_erros_qtd(erros); i++)
		fprintf(stderr, "%s: %s\n", xsd, nfe_erros_msg(erros, i));
	nfe_erros_free(erros);
	nfe_validador_free(v);
	return rc;
}

static void testa_enderecos(void)
{
	const char *u = NULL;

	VERIFICA_INT(mdf_sefaz_endereco(NFE_AMBIENTE_HOMOLOGACAO,
	                                MDF_SERVICO_AUTORIZACAO, &u),
	             0);
	VERIFICA_STR(u, "https://mdfe-homologacao.svrs.rs.gov.br/ws/"
	                "MDFeRecepcaoSinc/MDFeRecepcaoSinc.asmx");
	VERIFICA_INT(mdf_sefaz_endereco(NFE_AMBIENTE_PRODUCAO,
	                                MDF_SERVICO_EVENTO, &u),
	             0);
	VERIFICA_STR(u, "https://mdfe.svrs.rs.gov.br/ws/MDFeRecepcaoEvento/"
	                "MDFeRecepcaoEvento.asmx");
	VERIFICA_INT(mdf_sefaz_endereco(NFE_AMBIENTE_PRODUCAO,
	                                MDF_SERVICO_NAO_ENCERRADOS, &u),
	             0);
	VERIFICA(u && strstr(u, "/MDFeConsNaoEnc/") != NULL);
	VERIFICA_INT(
	        mdf_sefaz_endereco((nfe_ambiente)3, MDF_SERVICO_STATUS, &u),
	        E_VALOR);
	VERIFICA_INT(
	        mdf_sefaz_endereco(NFE_AMBIENTE_PRODUCAO, (mdf_servico)99, &u),
	        E_VALOR);
	VERIFICA_INT(mdf_sefaz_endereco(NFE_AMBIENTE_PRODUCAO,
	                                MDF_SERVICO_STATUS, NULL),
	             E_ISNULL);
}

/* MDF-e de teste assinado */
static char *mdfe_assinado(const nfe_certificado *cert, char *chave)
{
	mdf_mdfe *m = mdfe_teste("1");
	char *xml = NULL, *mdfe = NULL;
	size_t tam = 0;

	VERIFICA_INT(mdf_mdfe_xml(m, &xml, &tam), 0);
	VERIFICA_INT(mdf_mdfe_chave(m, chave), 0);
	if (xml)
		VERIFICA_INT(mdf_assinar(cert, xml, tam, &mdfe, NULL), 0);
	free(xml);
	mdf_mdfe_free(m);
	return mdfe;
}

static void testa_autorizacao(nfe_sefaz *s, const char *mdfe, const char *chave)
{
	char motivo[256], *proc = NULL;
	size_t tam = 0;
	int cstat = 0;

	VERIFICA_INT(mdf_sefaz_autorizar(s, url("/autoriza"), mdfe, &cstat,
	                                 motivo, sizeof motivo, &proc, &tam),
	             0);
	VERIFICA_INT(cstat, 100);
	VERIFICA_STR(motivo, "Autorizado o uso do MDF-e");
	VERIFICA(proc && strlen(proc) == tam);
	if (proc) {
		VERIFICA(strstr(proc,
		                "<mdfeProc xmlns=\"http://www.portalfiscal"
		                ".inf.br/mdfe\" versao=\"3.00\"><MDFe") !=
		         NULL);
		VERIFICA(strstr(proc, chave) != NULL);
		VERIFICA_INT(valida("procMDFe_v3.00.xsd", proc, tam), 0);
	}
	free(proc);

	/* Rejeição no protocolo: sem mdfeProc */
	proc = NULL;
	VERIFICA_INT(mdf_sefaz_autorizar(s, url("/rejeita"), mdfe, &cstat,
	                                 motivo, sizeof motivo, &proc, NULL),
	             0);
	VERIFICA_INT(cstat, 611);
	VERIFICA(proc == NULL);

	/* Protocolo de outro MDF-e */
	VERIFICA_INT(mdf_sefaz_autorizar(s, url("/outra"), mdfe, &cstat, NULL,
	                                 0, &proc, NULL),
	             E_XML);
	VERIFICA(proc == NULL);

	/* MDF-e malformado: o servidor recusa sem protocolo */
	VERIFICA_INT(mdf_sefaz_autorizar(s, url("/autoriza"),
	                                 "<MDFe Id=\"x\"/>", &cstat, NULL, 0,
	                                 &proc, NULL),
	             E_XML);
	VERIFICA_INT(mdf_sefaz_autorizar(s, url("/fault"), mdfe, &cstat, NULL,
	                                 0, &proc, NULL),
	             E_REDE);
	VERIFICA(strstr(nfe_sefaz_erro(s), "Erro de teste") != NULL);
	VERIFICA_INT(mdf_sefaz_autorizar(NULL, url("/autoriza"), mdfe, &cstat,
	                                 NULL, 0, &proc, NULL),
	             E_ISNULL);
}

static void testa_consultas(nfe_sefaz *s, const char *chave)
{
	char motivo[256], *ret = NULL;
	size_t tam = 0;
	int cstat = 0;

	VERIFICA_INT(mdf_sefaz_status(s, url("/"), NFE_AMBIENTE_HOMOLOGACAO,
	                              &cstat, motivo, sizeof motivo),
	             0);
	VERIFICA_INT(cstat, 107);
	VERIFICA_STR(motivo, "Servico em Operacao");
	VERIFICA_INT(
	        mdf_sefaz_status(s, url("/"), (nfe_ambiente)0, &cstat, NULL, 0),
	        E_VALOR);

	VERIFICA_INT(mdf_sefaz_consultar(s, url("/"), NFE_AMBIENTE_HOMOLOGACAO,
	                                 chave, &cstat, NULL, 0, &ret, &tam),
	             0);
	VERIFICA_INT(cstat, 100);
	VERIFICA(ret && strstr(ret, "<protMDFe") != NULL);
	if (ret)
		VERIFICA_INT(valida("retConsSitMDFe_v3.00.xsd", ret, tam), 0);
	free(ret);
	VERIFICA_INT(mdf_sefaz_consultar(s, url("/"), NFE_AMBIENTE_HOMOLOGACAO,
	                                 "123", &cstat, NULL, 0, NULL, NULL),
	             E_VALOR);

	ret = NULL;
	VERIFICA_INT(mdf_sefaz_nao_encerrados(s, url("/"),
	                                      NFE_AMBIENTE_HOMOLOGACAO,
	                                      "11222333000181", &cstat, motivo,
	                                      sizeof motivo, &ret, &tam),
	             0);
	VERIFICA_INT(cstat, 111);
	VERIFICA(ret && strstr(ret, "<chMDFe>") != NULL);
	if (ret)
		VERIFICA_INT(valida("retConsMDFeNaoEnc_v3.00.xsd", ret, tam),
		             0);
	free(ret);
	VERIFICA_INT(mdf_sefaz_nao_encerrados(s, url("/"),
	                                      NFE_AMBIENTE_HOMOLOGACAO, "1",
	                                      &cstat, NULL, 0, NULL, NULL),
	             E_VALOR);
}

static void testa_evento(nfe_sefaz *s, const nfe_certificado *cert,
                         const char *chave)
{
	mdf_evento *e = mdf_evento_new(MDF_EVENTO_ENCERRAMENTO);
	nfe_grupo *det = mdf_evento_detalhe(e);
	char *xml = NULL, *assinado = NULL, *proc = NULL, motivo[256];
	size_t tam = 0, tam_proc = 0;
	int cstat = 0;

	VERIFICA_INT(mdf_evento_set_chave(e, chave), 0);
	VERIFICA_INT(mdf_evento_set_autor(e, "11222333000181"), 0);
	VERIFICA_INT(mdf_evento_set_ambiente(e, NFE_AMBIENTE_HOMOLOGACAO), 0);
	VERIFICA_INT(mdf_evento_set_data(e, "2026-10-04T18:00:00-03:00"), 0);
	VERIFICA_INT(nfe_grupo_set(det, "nProt", "943260000000001"), 0);
	VERIFICA_INT(nfe_grupo_set(det, "dtEnc", "2026-10-04"), 0);
	VERIFICA_INT(nfe_grupo_set(det, "cUF", "43"), 0);
	VERIFICA_INT(nfe_grupo_set(det, "cMun", "4304606"), 0);
	VERIFICA_INT(mdf_evento_xml(e, &xml, &tam), 0);
	if (xml)
		VERIFICA_INT(nfe_assinar_elemento(cert, xml, tam, "infEvento",
		                                  &assinado, NULL),
		             0);
	if (assinado) {
		VERIFICA_INT(mdf_sefaz_evento(s, url("/"), assinado, &cstat,
		                              motivo, sizeof motivo, &proc,
		                              &tam_proc),
		             0);
		VERIFICA_INT(cstat, 135);
		VERIFICA(proc != NULL);
		if (proc)
			VERIFICA_INT(valida("procEventoMDFe_v3.00.xsd", proc,
			                    tam_proc),
			             0);
		free(proc);

		proc = NULL;
		VERIFICA_INT(mdf_sefaz_evento(s, url("/rejeita"), assinado,
		                              &cstat, NULL, 0, &proc, NULL),
		             0);
		VERIFICA_INT(cstat, 631);
		VERIFICA(proc == NULL);
		/* Evento sem assinatura: o servidor recusa */
		VERIFICA_INT(mdf_sefaz_evento(s, url("/"), xml, &cstat, NULL, 0,
		                              &proc, NULL),
		             E_REDE);
		VERIFICA_INT(mdf_sefaz_evento(s, url("/"), "<MDFe/>", &cstat,
		                              NULL, 0, &proc, NULL),
		             E_XML);
	}
	free(assinado);
	free(xml);
	mdf_evento_free(e);
}

int main(int argc, char **argv)
{
	char caminho[1024], ca[1024], chave[MDF_TAM_CHAVE + 1];
	nfe_certificado *cert;
	nfe_sefaz *s;
	char *mdfe;
	pid_t pid;
	int rc;

	dir_testes = argc > 1 ? argv[1] : "tests";
	testa_enderecos();

	snprintf(caminho, sizeof caminho, "%s/certificados/teste.pfx",
	         dir_testes);
	snprintf(ca, sizeof ca, "%s/certificados/servidor.pem", dir_testes);
	cert = nfe_certificado_pfx(caminho, "teste", &rc);
	VERIFICA(cert != NULL);
	if (!cert)
		TESTE_FIM();
	pid = inicia_servidor();
	VERIFICA(porta > 0);
	s = nfe_sefaz_new(cert);
	VERIFICA(s != NULL);
	if (porta > 0 && s) {
		VERIFICA_INT(nfe_sefaz_set_ca(s, ca), 0);
		mdfe = mdfe_assinado(cert, chave);
		if (mdfe)
			testa_autorizacao(s, mdfe, chave);
		free(mdfe);
		testa_consultas(s, chave);
		testa_evento(s, cert, chave);
	}
	nfe_sefaz_free(s);
	nfe_certificado_free(cert);
	if (pid > 0) {
		kill(pid, SIGTERM);
		waitpid(pid, NULL, 0);
	}
	TESTE_FIM();
}
