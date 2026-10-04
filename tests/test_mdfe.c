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

/* Testes do MDF-e (mdfe.h): grupos pelo motor de grupos, chave de acesso,
 * XML validado contra os schemas oficiais (mdfe_v3.00.xsd e o do modal
 * rodoviário), assinatura com o certificado de teste e QR Code, normal e
 * em contingência (com sign conferido pela chave pública).
 *
 * Uso: test_mdfe <diretório tests> */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/evp.h>
#include <openssl/pem.h>

#include <libnfe/assinatura.h>
#include <libnfe/erros.h>
#include <libnfe/validar.h>
#include <libmdf/mdfe.h>

#include "teste.h"
#include "mdfe_teste.h"

#define NS "http://www.portalfiscal.inf.br/mdfe"

static const char *dir_testes;

/* Valida xml contra o schema da pasta tests/schemas/mdfe */
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

/* O grupo <rodo> do MDF-e, validado contra o schema do modal */
static int valida_rodo(const char *xml)
{
	const char *ini = strstr(xml, "<rodo>"), *fim = strstr(xml, "</rodo>");
	char *rodo;
	size_t n;
	int rc;

	if (!ini || !fim)
		return E_XML;
	n = (size_t)(fim - ini) + strlen("</rodo>");
	rodo = (char *)malloc(n + 64);
	if (!rodo)
		return E_MALLOC;
	strcpy(rodo, "<rodo xmlns=\"" NS "\">");
	strncat(rodo, ini + strlen("<rodo>"), n - strlen("<rodo>"));
	rc = valida("mdfeModalRodoviario_v3.00.xsd", rodo, strlen(rodo), 0);
	free(rodo);
	return rc;
}

static nfe_certificado *certificado(void)
{
	char caminho[1024];
	int rc;

	snprintf(caminho, sizeof caminho, "%s/certificados/teste.pfx",
	         dir_testes);
	return nfe_certificado_pfx(caminho, "teste", &rc);
}

/* Confere o parâmetro sign do QR Code com a chave pública do certificado
 * de teste */
static int confere_sign(const char *chave, const char *sign)
{
	char caminho[1024];
	unsigned char bin[1024];
	FILE *f;
	X509 *x509;
	EVP_PKEY *pub;
	EVP_MD_CTX *md;
	size_t k;
	int n, ok = 0;

	snprintf(caminho, sizeof caminho, "%s/certificados/teste_cert.pem",
	         dir_testes);
	f = fopen(caminho, "r");
	if (!f)
		return 0;
	x509 = PEM_read_X509(f, NULL, NULL, NULL);
	fclose(f);
	pub = x509 ? X509_get_pubkey(x509) : NULL;
	n = EVP_DecodeBlock(bin, (const unsigned char *)sign,
	                    (int)strlen(sign));
	/* EVP_DecodeBlock conta o enchimento ("=") como bytes */
	for (k = strlen(sign); n > 0 && k > 0 && sign[k - 1] == '='; k--)
		n--;
	md = EVP_MD_CTX_new();
	if (pub && md && n > 0 &&
	    EVP_DigestVerifyInit(md, NULL, EVP_sha1(), NULL, pub) == 1)
		ok = EVP_DigestVerify(md, bin, (size_t)n,
		                      (const unsigned char *)chave,
		                      MDF_TAM_CHAVE) == 1;
	EVP_MD_CTX_free(md);
	EVP_PKEY_free(pub);
	X509_free(x509);
	return ok;
}

static void testa_grupos(void)
{
	mdf_mdfe *m = mdf_mdfe_new();
	nfe_grupo *item;
	int i;

	VERIFICA(m != NULL);
	VERIFICA_STR(nfe_grupo_get(mdf_mdfe_grupo(m, "ide"), "mod"), "58");
	VERIFICA(mdf_mdfe_grupo(m, "rodo") != NULL);
	VERIFICA(mdf_mdfe_grupo(m, "infRespTec") != NULL);
	VERIFICA(mdf_mdfe_grupo(m, "seg") == NULL);
	VERIFICA(mdf_mdfe_grupo(m, "xyz") == NULL);
	VERIFICA(mdf_mdfe_grupo(NULL, "ide") == NULL);

	/* Valores conferidos pelo motor com as regras do XSD */
	VERIFICA_INT(nfe_grupo_set(mdf_mdfe_grupo(m, "ide"), "mod", "55"),
	             E_VALOR);
	VERIFICA_INT(nfe_grupo_set(mdf_mdfe_grupo(m, "ide"), "UFIni", "XX"),
	             E_VALOR);
	VERIFICA_INT(nfe_grupo_set(mdf_mdfe_grupo(m, "rodo"),
	                           "veicTracao/placa", "abc1234"),
	             E_VALOR);

	/* Grupos que se repetem */
	VERIFICA_INT(mdf_mdfe_add(m, "xyz", &item), E_VALOR);
	VERIFICA_INT(mdf_mdfe_add(m, "seg", NULL), E_ISNULL);
	VERIFICA_INT(mdf_mdfe_add(m, "seg", &item), 0);
	VERIFICA_INT(nfe_grupo_set(item, "infResp/respSeg", "1"), 0);
	VERIFICA_INT(mdf_mdfe_quantidade(m, "seg"), 1);
	VERIFICA(mdf_mdfe_item(m, "seg", 0) == item);
	VERIFICA(mdf_mdfe_item(m, "seg", 1) == NULL);
	for (i = 0; i < 10; i++)
		VERIFICA_INT(mdf_mdfe_add(m, "autXML", &item), 0);
	VERIFICA_INT(mdf_mdfe_add(m, "autXML", &item), E_VALOR);
	VERIFICA_INT(mdf_mdfe_quantidade(m, "autXML"), 10);
	mdf_mdfe_free(m);
	mdf_mdfe_free(NULL);
}

static void testa_chave(void)
{
	char chave[MDF_TAM_CHAVE + 1], esperada[MDF_TAM_CHAVE + 1];
	mdf_mdfe *m = mdfe_teste("1");
	nfe_grupo *emit = mdf_mdfe_grupo(m, "emit");

	/* cUF, AAMM, CNPJ, modelo, série, número, tpEmis, cMDF e DV */
	strcpy(esperada, "43"
	                 "2610"
	                 "11222333000181"
	                 "58"
	                 "001"
	                 "000000001"
	                 "1"
	                 "12345678"
	                 "0");
	esperada[43] = (char)('0' + nfe_chave_dv(esperada));
	VERIFICA_INT(mdf_mdfe_chave(m, chave), 0);
	VERIFICA_STR(chave, esperada);
	VERIFICA_INT(nfe_chave_validar(chave), 0);

	/* Emitente pessoa física: CPF com zeros à esquerda */
	VERIFICA_INT(nfe_grupo_set(emit, "CPF", "12345678909"), 0);
	VERIFICA_INT(nfe_grupo_remove(emit, "CNPJ"), 0);
	VERIFICA_INT(mdf_mdfe_chave(m, chave), 0);
	VERIFICA(memcmp(chave + 6, "00012345678909", 14) == 0);

	/* Sem cMDF não há chave */
	VERIFICA_INT(nfe_grupo_remove(mdf_mdfe_grupo(m, "ide"), "cMDF"), 0);
	VERIFICA_INT(mdf_mdfe_chave(m, chave), E_VALOR);
	VERIFICA_INT(mdf_mdfe_chave(NULL, chave), E_ISNULL);
	mdf_mdfe_free(m);
}

static void testa_xml(void)
{
	mdf_mdfe *m = mdfe_teste("1");
	char *xml = NULL;
	size_t tam = 0;

	VERIFICA_INT(mdf_mdfe_xml(m, &xml, &tam), 0);
	VERIFICA(xml && strlen(xml) == tam);
	if (xml) {
		VERIFICA(strstr(xml, "<cDV>") != NULL);
		VERIFICA(strstr(xml, "Id=\"MDFe43261011222333000181580010000000"
		                     "01112345678") != NULL);
		VERIFICA(strstr(xml, "<infModal versaoModal=\"3.00\"><rodo>") !=
		         NULL);
		VERIFICA_INT(valida("mdfe_v3.00.xsd", xml, tam, 1), 0);
		VERIFICA_INT(valida_rodo(xml), 0);
	}
	free(xml);

	/* Falta grupo obrigatório: tot */
	VERIFICA_INT(nfe_grupo_remove(mdf_mdfe_grupo(m, "tot"), "vCarga"), 0);
	xml = NULL;
	VERIFICA_INT(mdf_mdfe_xml(m, &xml, NULL), E_VALOR);
	VERIFICA(xml == NULL);
	mdf_mdfe_free(m);
}

static void testa_assinatura(const nfe_certificado *cert, const char *tpemis)
{
	mdf_mdfe *m = mdfe_teste(tpemis);
	char *xml = NULL, *mdfe = NULL, chave[MDF_TAM_CHAVE + 1];
	size_t tam = 0, tam_mdfe = 0;
	const char *qr, *sign;

	VERIFICA_INT(mdf_mdfe_xml(m, &xml, &tam), 0);
	VERIFICA_INT(mdf_mdfe_chave(m, chave), 0);
	VERIFICA_INT(mdf_assinar(cert, xml, tam, &mdfe, &tam_mdfe), 0);
	VERIFICA(mdfe && strlen(mdfe) == tam_mdfe);
	if (!mdfe) {
		free(xml);
		mdf_mdfe_free(m);
		return;
	}
	VERIFICA_INT(valida("mdfe_v3.00.xsd", mdfe, tam_mdfe, 0), 0);
	VERIFICA_INT(
	        nfe_verificar_assinatura_elemento(mdfe, tam_mdfe, "infMDFe"),
	        0);
	/* infMDFeSupl entre infMDFe e Signature */
	VERIFICA(strstr(mdfe,
	                "</infMDFe><infMDFeSupl><qrCodMDFe>" MDF_URL_QRCODE
	                "?chMDFe=") != NULL);
	VERIFICA(strstr(mdfe, "</infMDFeSupl><Signature") != NULL);
	qr = strstr(mdfe, "?chMDFe=");
	VERIFICA(qr && strncmp(qr + 8, chave, MDF_TAM_CHAVE) == 0);
	VERIFICA(strstr(mdfe, "&amp;tpAmb=2") != NULL);
	sign = strstr(mdfe, "&amp;sign=");
	if (tpemis[0] == '2') {
		VERIFICA(sign != NULL);
		if (sign) {
			char b64[1024];
			const char *fim = strstr(sign, "</qrCodMDFe>");
			size_t n = fim ? (size_t)(fim - sign) - 10 : 0;

			VERIFICA(n > 0 && n < sizeof b64);
			if (n > 0 && n < sizeof b64) {
				memcpy(b64, sign + 10, n);
				b64[n] = '\0';
				VERIFICA(confere_sign(chave, b64));
			}
		}
	} else {
		VERIFICA(sign == NULL);
	}

	/* Já assinado */
	{
		char *de_novo = NULL;

		VERIFICA_INT(mdf_assinar(cert, mdfe, tam_mdfe, &de_novo, NULL),
		             E_XML);
		VERIFICA(de_novo == NULL);
	}
	VERIFICA_INT(mdf_assinar(NULL, xml, tam, &mdfe, NULL), E_ISNULL);
	free(mdfe);
	free(xml);
	mdf_mdfe_free(m);
}

int main(int argc, char **argv)
{
	nfe_certificado *cert;

	dir_testes = argc > 1 ? argv[1] : "tests";
	testa_grupos();
	testa_chave();
	testa_xml();
	cert = certificado();
	VERIFICA(cert != NULL);
	if (cert) {
		testa_assinatura(cert, "1");
		testa_assinatura(cert, "2");
	}
	nfe_certificado_free(cert);
	TESTE_FIM();
}
