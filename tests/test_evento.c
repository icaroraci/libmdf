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

/* Testes dos eventos do MDF-e (evento.h): cabeçalho, Id, detalhe pelo
 * motor de grupos, XML validado contra eventoMDFe_v3.00.xsd e o schema do
 * detalhe, assinatura com o certificado de teste.
 *
 * Uso: test_evento <diretório tests> */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libnfe/assinatura.h>
#include <libnfe/chave.h>
#include <libnfe/erros.h>
#include <libnfe/validar.h>
#include <libmdf/evento.h>
#include <libmdf/mdfe.h>

#include "teste.h"

#define NS "http://www.portalfiscal.inf.br/mdfe"

static const char *dir_testes;
static char chave[MDF_TAM_CHAVE + 1];

static int valida(const char *xsd, const char *xml, size_t tam,
                  int completar_assinatura)
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
	rc = nfe_validar_xsd(v, xml, tam, completar_assinatura, erros);
	for (i = 0; i < nfe_erros_qtd(erros); i++)
		fprintf(stderr, "%s: %s\n", xsd, nfe_erros_msg(erros, i));
	nfe_erros_free(erros);
	nfe_validador_free(v);
	return rc;
}

/* O detalhe <elemento> do evento, validado contra o seu schema */
static int valida_detalhe(const char *xml, const char *elemento,
                          const char *xsd)
{
	char ini[64], fim[64], *det;
	const char *a, *b;
	size_t n;
	int rc;

	snprintf(ini, sizeof ini, "<%s>", elemento);
	snprintf(fim, sizeof fim, "</%s>", elemento);
	a = strstr(xml, ini);
	b = strstr(xml, fim);
	if (!a || !b)
		return E_XML;
	n = (size_t)(b - a) + strlen(fim);
	det = (char *)malloc(n + 128);
	if (!det)
		return E_MALLOC;
	snprintf(det, n + 128, "<%s xmlns=\"" NS "\">%.*s", elemento,
	         (int)(n - strlen(ini)), a + strlen(ini));
	rc = valida(xsd, det, strlen(det), 0);
	free(det);
	return rc;
}

static mdf_evento *evento(mdf_tipo_evento tipo)
{
	mdf_evento *e = mdf_evento_new(tipo);

	VERIFICA(e != NULL);
	if (!e)
		return NULL;
	VERIFICA_INT(mdf_evento_set_chave(e, chave), 0);
	VERIFICA_INT(mdf_evento_set_autor(e, "11222333000181"), 0);
	VERIFICA_INT(mdf_evento_set_ambiente(e, NFE_AMBIENTE_HOMOLOGACAO), 0);
	VERIFICA_INT(mdf_evento_set_data(e, "2026-10-04T18:00:00-03:00"), 0);
	return e;
}

/* Gera, valida, assina e valida de novo */
static void confere(const nfe_certificado *cert, mdf_evento *e,
                    const char *detalhe, const char *xsd, const char *id)
{
	char *xml = NULL, *assinado = NULL;
	size_t tam = 0, tam_ass = 0;

	VERIFICA_INT(mdf_evento_xml(e, &xml, &tam), 0);
	if (!xml)
		return;
	VERIFICA(strstr(xml, id) != NULL);
	VERIFICA_INT(valida("eventoMDFe_v3.00.xsd", xml, tam, 1), 0);
	VERIFICA_INT(valida_detalhe(xml, detalhe, xsd), 0);
	if (cert) {
		VERIFICA_INT(nfe_assinar_elemento(cert, xml, tam, "infEvento",
		                                  &assinado, &tam_ass),
		             0);
		if (assinado) {
			VERIFICA_INT(valida("eventoMDFe_v3.00.xsd", assinado,
			                    tam_ass, 0),
			             0);
			VERIFICA_INT(nfe_verificar_assinatura_elemento(
			                     assinado, tam_ass, "infEvento"),
			             0);
		}
	}
	free(assinado);
	free(xml);
}

static void testa_cabecalho(void)
{
	mdf_evento *e;
	char *xml = NULL;
	char outra[MDF_TAM_CHAVE + 1];

	VERIFICA(mdf_evento_new((mdf_tipo_evento)110113) == NULL);
	e = mdf_evento_new(MDF_EVENTO_CANCELAMENTO);
	VERIFICA(e != NULL);
	VERIFICA_STR(nfe_grupo_get(mdf_evento_detalhe(e), "descEvento"),
	             "Cancelamento");

	/* Sem chave, autor, ambiente e data não gera */
	VERIFICA_INT(mdf_evento_xml(e, &xml, NULL), E_VALOR);
	VERIFICA(xml == NULL);

	VERIFICA_INT(mdf_evento_set_chave(e, NULL), E_ISNULL);
	VERIFICA_INT(mdf_evento_set_chave(e, "123"), E_TAMANHO);
	strcpy(outra, chave);
	outra[43] = outra[43] == '9' ? '0' : (char)(outra[43] + 1);
	VERIFICA_INT(mdf_evento_set_chave(e, outra), E_VALOR);
	VERIFICA_INT(mdf_evento_set_autor(e, "123"), E_VALOR);
	VERIFICA_INT(mdf_evento_set_autor(e, "12345678909"), 0);
	VERIFICA_INT(mdf_evento_set_ambiente(e, (nfe_ambiente)3), E_VALOR);
	VERIFICA_INT(mdf_evento_set_data(e, "2026-10-04 18:00:00"), E_VALOR);
	VERIFICA_INT(mdf_evento_set_sequencia(e, 0), E_VALOR);
	VERIFICA_INT(mdf_evento_set_sequencia(e, 1000), E_VALOR);
	VERIFICA_INT(mdf_evento_set_orgao(e, "99"), E_VALOR);
	VERIFICA_INT(mdf_evento_set_orgao(e, "43"), 0);
	mdf_evento_free(e);
	mdf_evento_free(NULL);
}

int main(int argc, char **argv)
{
	char caminho[1024], id[64];
	nfe_certificado *cert;
	mdf_evento *e;
	nfe_grupo *det, *item;
	int rc;

	dir_testes = argc > 1 ? argv[1] : "tests";
	memcpy(chave, "4326101122233300018158001000000001112345678", 43);
	chave[43] = (char)('0' + nfe_chave_dv(chave));
	chave[44] = '\0';
	snprintf(caminho, sizeof caminho, "%s/certificados/teste.pfx",
	         dir_testes);
	cert = nfe_certificado_pfx(caminho, "teste", &rc);
	VERIFICA(cert != NULL);

	testa_cabecalho();

	/* Cancelamento */
	e = evento(MDF_EVENTO_CANCELAMENTO);
	det = mdf_evento_detalhe(e);
	VERIFICA_INT(nfe_grupo_set(det, "nProt", "943260000000001"), 0);
	VERIFICA_INT(nfe_grupo_set(det, "xJust", "Curta"), E_TAMANHO);
	VERIFICA_INT(nfe_grupo_set(det, "xJust",
	                           "Viagem cancelada pelo "
	                           "contratante"),
	             0);
	snprintf(id, sizeof id, "Id=\"ID110111%s01\"", chave);
	confere(cert, e, "evCancMDFe", "evCancMDFe_v3.00.xsd", id);
	mdf_evento_free(e);

	/* Encerramento, com sequência de 3 dígitos no Id */
	e = evento(MDF_EVENTO_ENCERRAMENTO);
	det = mdf_evento_detalhe(e);
	VERIFICA_INT(mdf_evento_set_sequencia(e, 100), 0);
	VERIFICA_INT(nfe_grupo_set(det, "nProt", "943260000000001"), 0);
	VERIFICA_INT(nfe_grupo_set(det, "dtEnc", "2026-10-04"), 0);
	VERIFICA_INT(nfe_grupo_set(det, "cUF", "43"), 0);
	VERIFICA_INT(nfe_grupo_set(det, "cMun", "4304606"), 0);
	snprintf(id, sizeof id, "Id=\"ID110112%s100\"", chave);
	confere(cert, e, "evEncMDFe", "evEncMDFe_v3.00.xsd", id);
	mdf_evento_free(e);

	/* Inclusão de condutor */
	e = evento(MDF_EVENTO_INCLUSAO_CONDUTOR);
	det = mdf_evento_detalhe(e);
	VERIFICA_INT(nfe_grupo_set(det, "condutor/xNome", "MARIA DE SOUZA"), 0);
	VERIFICA_INT(nfe_grupo_set(det, "condutor/CPF", "98765432100"), 0);
	snprintf(id, sizeof id, "Id=\"ID110114%s01\"", chave);
	confere(cert, e, "evIncCondutorMDFe", "evIncCondutorMDFe_v3.00.xsd",
	        id);
	mdf_evento_free(e);

	/* Inclusão de DF-e */
	e = evento(MDF_EVENTO_INCLUSAO_DFE);
	det = mdf_evento_detalhe(e);
	VERIFICA_INT(nfe_grupo_set(det, "nProt", "943260000000001"), 0);
	VERIFICA_INT(nfe_grupo_set(det, "cMunCarrega", "4314902"), 0);
	VERIFICA_INT(nfe_grupo_set(det, "xMunCarrega", "PORTO ALEGRE"), 0);
	VERIFICA_INT(nfe_grupo_add(det, "infDoc", &item), 0);
	VERIFICA_INT(nfe_grupo_set(item, "cMunDescarga", "4304606"), 0);
	VERIFICA_INT(nfe_grupo_set(item, "xMunDescarga", "CANOAS"), 0);
	VERIFICA_INT(
	        nfe_grupo_set(item, "chNFe",
	                      "43261011222333000181550010000001231000001232"),
	        0);
	snprintf(id, sizeof id, "Id=\"ID110115%s01\"", chave);
	confere(cert, e, "evIncDFeMDFe", "evInclusaoDFeMDFe_v3.00.xsd", id);
	mdf_evento_free(e);

	nfe_certificado_free(cert);
	TESTE_FIM();
}
