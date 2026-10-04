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

#include <stdlib.h>
#include <string.h>

#include <openssl/evp.h>

#include <libnfe/chave.h>
#include <libnfe/erros.h>
#include <libnfe/esquema.h>
#include <libmdf/mdfe.h>

#include "esquemas.h"
#include "interno.h"

/* Grupos que aparecem uma vez, na ordem do leiaute */
enum {
	G_IDE,
	G_EMIT,
	G_RODO,
	G_INFDOC,
	G_PRODPRED,
	G_TOT,
	G_INFADIC,
	G_RESPTEC,
	NGRUPOS
};

static const struct {
	const char *nome;
	const struct nfe_esq *esq;
	int obrigatorio;
} grupos[NGRUPOS] = {
	[G_IDE] = { "ide", &mdf_esq_ide, 1 },
	[G_EMIT] = { "emit", &mdf_esq_emit, 1 },
	[G_RODO] = { "rodo", &mdf_esq_rodo, 1 },
	[G_INFDOC] = { "infDoc", &mdf_esq_infDoc, 1 },
	[G_PRODPRED] = { "prodPred", &mdf_esq_prodPred, 0 },
	[G_TOT] = { "tot", &mdf_esq_tot, 1 },
	[G_INFADIC] = { "infAdic", &mdf_esq_infAdic, 0 },
	[G_RESPTEC] = { "infRespTec", &mdf_esq_infRespTec, 0 },
};

/* Grupos que se repetem */
enum { L_SEG, L_LACRES, L_AUTXML, NLISTAS };

static const struct {
	const char *nome;
	const struct nfe_esq *esq;
	int max; /* 0: sem limite */
} listas[NLISTAS] = {
	[L_SEG] = { "seg", &mdf_esq_seg, 0 },
	[L_LACRES] = { "lacres", &mdf_esq_lacres, 0 },
	[L_AUTXML] = { "autXML", &mdf_esq_autXML, 10 },
};

struct lista {
	nfe_grupo **itens;
	int n;
};

struct mdf_mdfe {
	nfe_grupo *g[NGRUPOS];
	struct lista l[NLISTAS];
};

mdf_mdfe *mdf_mdfe_new(void)
{
	mdf_mdfe *m = (mdf_mdfe *)calloc(1, sizeof *m);
	int i;

	if (!m)
		return NULL;
	for (i = 0; i < NGRUPOS; i++) {
		m->g[i] = nfe_grupo_new(grupos[i].esq);
		if (!m->g[i]) {
			mdf_mdfe_free(m);
			return NULL;
		}
	}
	if (nfe_grupo_set(m->g[G_IDE], "mod", "58") != 0) {
		mdf_mdfe_free(m);
		return NULL;
	}
	return m;
}

void mdf_mdfe_free(mdf_mdfe *m)
{
	int i, j;

	if (!m)
		return;
	for (i = 0; i < NGRUPOS; i++)
		nfe_grupo_free(m->g[i]);
	for (i = 0; i < NLISTAS; i++) {
		for (j = 0; j < m->l[i].n; j++)
			nfe_grupo_free(m->l[i].itens[j]);
		free(m->l[i].itens);
	}
	free(m);
}

nfe_grupo *mdf_mdfe_grupo(mdf_mdfe *m, const char *nome)
{
	int i;

	if (!m || !nome)
		return NULL;
	for (i = 0; i < NGRUPOS; i++)
		if (strcmp(nome, grupos[i].nome) == 0)
			return m->g[i];
	return NULL;
}

static int indice_lista(const char *nome)
{
	int i;

	for (i = 0; nome && i < NLISTAS; i++)
		if (strcmp(nome, listas[i].nome) == 0)
			return i;
	return -1;
}

int mdf_mdfe_add(mdf_mdfe *m, const char *nome, nfe_grupo **item)
{
	struct lista *l;
	nfe_grupo **itens, *g;
	int i;

	if (!m || !nome || !item)
		return E_ISNULL;
	i = indice_lista(nome);
	if (i < 0)
		return E_VALOR;
	l = &m->l[i];
	if (listas[i].max && l->n >= listas[i].max)
		return E_VALOR;
	itens = (nfe_grupo **)realloc(l->itens,
	                              (size_t)(l->n + 1) * sizeof *itens);
	if (!itens)
		return E_MALLOC;
	l->itens = itens;
	g = nfe_grupo_new(listas[i].esq);
	if (!g)
		return E_MALLOC;
	l->itens[l->n++] = g;
	*item = g;
	return 0;
}

int mdf_mdfe_quantidade(const mdf_mdfe *m, const char *nome)
{
	int i = indice_lista(nome);

	return m && i >= 0 ? m->l[i].n : 0;
}

nfe_grupo *mdf_mdfe_item(const mdf_mdfe *m, const char *nome, int i)
{
	int k = indice_lista(nome);

	if (!m || k < 0 || i < 0 || i >= m->l[k].n)
		return NULL;
	return m->l[k].itens[i];
}

/* Só dígitos, com tamanho entre min e max */
static int digitos(const char *s, size_t min, size_t max)
{
	size_t n, i;

	if (!s)
		return 0;
	n = strlen(s);
	if (n < min || n > max)
		return 0;
	for (i = 0; i < n; i++)
		if (s[i] < '0' || s[i] > '9')
			return 0;
	return 1;
}

/* Copia s em dst com zeros à esquerda até n caracteres */
static void zeros(char *dst, const char *s, size_t n)
{
	size_t k = strlen(s);

	memset(dst, '0', n - k);
	memcpy(dst + n - k, s, k);
}

int mdf_mdfe_chave(const mdf_mdfe *m, char chave[MDF_TAM_CHAVE + 1])
{
	const char *cuf, *dh, *cnpj, *cpf, *serie, *nmdf, *tpemis, *cmdf;
	nfe_grupo *ide, *emit;
	int dv;

	if (!m || !chave)
		return E_ISNULL;
	ide = m->g[G_IDE];
	emit = m->g[G_EMIT];
	cuf = nfe_grupo_get(ide, "cUF");
	dh = nfe_grupo_get(ide, "dhEmi");
	serie = nfe_grupo_get(ide, "serie");
	nmdf = nfe_grupo_get(ide, "nMDF");
	tpemis = nfe_grupo_get(ide, "tpEmis");
	cmdf = nfe_grupo_get(ide, "cMDF");
	cnpj = nfe_grupo_get(emit, "CNPJ");
	cpf = nfe_grupo_get(emit, "CPF");
	/* Os valores já foram conferidos pelo motor de grupos ao serem
	 * gravados; aqui só falta conferir se existem */
	if (!digitos(cuf, 2, 2) || !dh || strlen(dh) < 7 ||
	    !digitos(serie, 1, 3) || !digitos(nmdf, 1, 9) ||
	    !digitos(tpemis, 1, 1) || !digitos(cmdf, 8, 8) ||
	    !(cnpj || digitos(cpf, 11, 11)))
		return E_VALOR;

	memcpy(chave, cuf, 2);
	chave[2] = dh[2];
	chave[3] = dh[3];
	chave[4] = dh[5];
	chave[5] = dh[6];
	if (cnpj && strlen(cnpj) == 14)
		memcpy(chave + 6, cnpj, 14);
	else if (cpf)
		zeros(chave + 6, cpf, 14);
	else
		return E_VALOR;
	memcpy(chave + 20, "58", 2);
	zeros(chave + 22, serie, 3);
	zeros(chave + 25, nmdf, 9);
	chave[34] = tpemis[0];
	memcpy(chave + 35, cmdf, 8);
	chave[43] = '0';
	chave[44] = '\0';
	dv = nfe_chave_dv(chave);
	if (dv < 0)
		return E_VALOR;
	chave[43] = (char)('0' + dv);
	return 0;
}

/* ---- XML ---- */

struct escrita {
	const mdf_mdfe *m;
	const char *chave;
};

static int elemento(xmlTextWriterPtr w, const nfe_grupo *g, int obrigatorio)
{
	if (!obrigatorio && nfe_grupo_vazio(g))
		return 0;
	return nfe_grupo_write_xml(w, g);
}

static int escreve_lista(xmlTextWriterPtr w, const struct lista *l)
{
	int i, rc;

	for (i = 0; i < l->n; i++) {
		rc = nfe_grupo_write_xml(w, l->itens[i]);
		if (rc != 0)
			return rc;
	}
	return 0;
}

static int escreve_mdfe(xmlTextWriterPtr w, const void *dados)
{
	const struct escrita *e = (const struct escrita *)dados;
	const mdf_mdfe *m = e->m;
	char id[4 + MDF_TAM_CHAVE + 1];
	int rc;

	memcpy(id, "MDFe", 4);
	memcpy(id + 4, e->chave, MDF_TAM_CHAVE + 1);
	if (xmlTextWriterStartElement(w, BAD_CAST "MDFe") < 0 ||
	    xmlTextWriterWriteAttribute(w, BAD_CAST "xmlns", BAD_CAST MDF_NS) <
	            0 ||
	    xmlTextWriterStartElement(w, BAD_CAST "infMDFe") < 0 ||
	    xmlTextWriterWriteAttribute(w, BAD_CAST "versao",
	                                BAD_CAST MDF_VERSAO_LEIAUTE) < 0 ||
	    xmlTextWriterWriteAttribute(w, BAD_CAST "Id", BAD_CAST id) < 0)
		return E_XML;
	rc = elemento(w, m->g[G_IDE], 1);
	if (rc == 0)
		rc = elemento(w, m->g[G_EMIT], 1);
	if (rc == 0) {
		if (xmlTextWriterStartElement(w, BAD_CAST "infModal") < 0 ||
		    xmlTextWriterWriteAttribute(w, BAD_CAST "versaoModal",
		                                BAD_CAST MDF_VERSAO_LEIAUTE) <
		            0)
			return E_XML;
		rc = elemento(w, m->g[G_RODO], 1);
		if (rc == 0 && xmlTextWriterEndElement(w) < 0)
			rc = E_XML;
	}
	if (rc == 0)
		rc = elemento(w, m->g[G_INFDOC], 1);
	if (rc == 0)
		rc = escreve_lista(w, &m->l[L_SEG]);
	if (rc == 0)
		rc = elemento(w, m->g[G_PRODPRED], 0);
	if (rc == 0)
		rc = elemento(w, m->g[G_TOT], 1);
	if (rc == 0)
		rc = escreve_lista(w, &m->l[L_LACRES]);
	if (rc == 0)
		rc = escreve_lista(w, &m->l[L_AUTXML]);
	if (rc == 0)
		rc = elemento(w, m->g[G_INFADIC], 0);
	if (rc == 0)
		rc = elemento(w, m->g[G_RESPTEC], 0);
	if (rc != 0)
		return rc;
	/* </infMDFe></MDFe> */
	if (xmlTextWriterEndElement(w) < 0 || xmlTextWriterEndElement(w) < 0)
		return E_XML;
	return 0;
}

int mdf_mdfe_xml(mdf_mdfe *m, char **xml, size_t *tam)
{
	char chave[MDF_TAM_CHAVE + 1], dv[2];
	struct escrita e;
	int rc;

	if (!m || !xml)
		return E_ISNULL;
	rc = mdf_mdfe_chave(m, chave);
	if (rc != 0)
		return rc;
	dv[0] = chave[MDF_TAM_CHAVE - 1];
	dv[1] = '\0';
	rc = nfe_grupo_set(m->g[G_IDE], "cDV", dv);
	if (rc != 0)
		return rc;
	e.m = m;
	e.chave = chave;
	return mdf_xml_gera(escreve_mdfe, &e, xml, tam);
}

/* ---- assinatura e QR Code ---- */

/* Base64 (sem quebras de linha) de n bytes, alocado em *b64 */
static int base64(const unsigned char *dados, size_t n, char **b64)
{
	size_t tam = 4 * ((n + 2) / 3) + 1;

	if (n > 0x3fffffff)
		return E_VALOR;
	*b64 = (char *)malloc(tam);
	if (!*b64)
		return E_MALLOC;
	EVP_EncodeBlock((unsigned char *)*b64, dados, (int)n);
	return 0;
}

/* Texto de qrCodMDFe (já escapado para o XML: & vira &amp;) */
static int qrcode(const nfe_certificado *cert, const char *chave,
                  const char *tpamb, int contingencia, struct mdf_buf *b)
{
	unsigned char *ass = NULL;
	size_t tam_ass = 0;
	char *b64 = NULL;
	int rc;

	mdf_buf_poe(b, MDF_URL_QRCODE "?chMDFe=");
	mdf_buf_poe(b, chave);
	mdf_buf_poe(b, "&amp;tpAmb=");
	mdf_buf_poe(b, tpamb);
	if (!contingencia)
		return 0;
	/* MOC 3.00b, 9.2.2: assinatura RSA-SHA1 da chave de acesso, em
	 * base64, com o certificado que assina o MDF-e */
	rc = nfe_certificado_assinar(cert, chave, MDF_TAM_CHAVE, &ass,
	                             &tam_ass);
	if (rc != 0)
		return rc;
	rc = base64(ass, tam_ass, &b64);
	free(ass);
	if (rc != 0)
		return rc;
	mdf_buf_poe(b, "&amp;sign=");
	mdf_buf_poe(b, b64);
	free(b64);
	return 0;
}

/* Chave, tpAmb e tpEmis do MDF-e assinado */
static int dados_mdfe(const char *xml, size_t tam, char *chave, char *tpamb,
                      int *contingencia)
{
	xmlDocPtr doc = mdf_le_xml(xml, tam);
	xmlNodePtr raiz = doc ? xmlDocGetRootElement(doc) : NULL;
	xmlNodePtr inf = mdf_filho(raiz, "infMDFe"),
	           ide = mdf_filho(inf, "ide");
	xmlChar *id = inf ? xmlGetProp(inf, BAD_CAST "Id") : NULL;
	const char *amb = mdf_texto(ide, "tpAmb");
	int rc = E_XML;

	if (raiz && xmlStrEqual(raiz->name, BAD_CAST "MDFe") && id &&
	    xmlStrlen(id) == 4 + MDF_TAM_CHAVE && strlen(amb) == 1 &&
	    !mdf_filho(raiz, "infMDFeSupl")) {
		memcpy(chave, id + 4, MDF_TAM_CHAVE + 1);
		tpamb[0] = amb[0];
		tpamb[1] = '\0';
		*contingencia = strcmp(mdf_texto(ide, "tpEmis"), "2") == 0;
		rc = 0;
	}
	xmlFree(id);
	xmlFreeDoc(doc);
	return rc;
}

int mdf_assinar(const nfe_certificado *cert, const char *xml, size_t tam,
                char **mdfe, size_t *tam_mdfe)
{
	static const char fim_inf[] = "</infMDFe>";
	char chave[MDF_TAM_CHAVE + 1], tpamb[2];
	char *assinado = NULL;
	size_t tam_assinado = 0, antes;
	struct mdf_buf b = { 0 };
	const char *p;
	int rc, contingencia = 0;

	if (!cert || !xml || !mdfe)
		return E_ISNULL;
	rc = dados_mdfe(xml, tam, chave, tpamb, &contingencia);
	if (rc != 0)
		return rc;
	rc = nfe_assinar_elemento(cert, xml, tam, "infMDFe", &assinado,
	                          &tam_assinado);
	if (rc != 0)
		return rc;
	/* infMDFeSupl vem entre infMDFe e a assinatura, que não o cobre */
	p = strstr(assinado, fim_inf);
	if (!p) {
		free(assinado);
		return E_XML;
	}
	antes = (size_t)(p - assinado) + sizeof fim_inf - 1;
	mdf_buf_poe_n(&b, assinado, antes);
	mdf_buf_poe(&b, "<infMDFeSupl><qrCodMDFe>");
	rc = qrcode(cert, chave, tpamb, contingencia, &b);
	mdf_buf_poe(&b, "</qrCodMDFe></infMDFeSupl>");
	mdf_buf_poe_n(&b, assinado + antes, tam_assinado - antes);
	free(assinado);
	if (rc != 0) {
		free(b.p);
		return rc;
	}
	return mdf_buf_entrega(&b, mdfe, tam_mdfe);
}
