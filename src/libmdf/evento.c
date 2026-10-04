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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libnfe/chave.h>
#include <libnfe/erros.h>
#include <libnfe/esquema.h>
#include <libmdf/evento.h>
#include <libmdf/mdfe.h>

#include "esquemas.h"
#include "interno.h"
#include "padroes.h"

static const struct {
	mdf_tipo_evento tipo;
	const struct nfe_esq *esq;
	const char *desc; /* descEvento, fixo no schema */
} tipos[] = {
	{ MDF_EVENTO_CANCELAMENTO, &mdf_esq_evCancMDFe, "Cancelamento" },
	{ MDF_EVENTO_ENCERRAMENTO, &mdf_esq_evEncMDFe, "Encerramento" },
	{ MDF_EVENTO_INCLUSAO_CONDUTOR, &mdf_esq_evIncCondutorMDFe,
	  "Inclusao Condutor" },
	{ MDF_EVENTO_INCLUSAO_DFE, &mdf_esq_evIncDFeMDFe, "Inclusao DF-e" },
	{ MDF_EVENTO_PAGAMENTO_OPERACAO, &mdf_esq_evPagtoOperMDFe,
	  "Pagamento Operacao MDF-e" },
};

#define NTIPOS (sizeof tipos / sizeof tipos[0])

struct mdf_evento {
	mdf_tipo_evento tipo;
	nfe_grupo *det;
	char chave[MDF_TAM_CHAVE + 1];
	char orgao[3];
	char cnpj[15], cpf[12];
	int amb;
	char dh[32];
	int seq;
};

mdf_evento *mdf_evento_new(mdf_tipo_evento tipo)
{
	mdf_evento *e;
	size_t i;

	for (i = 0; i < NTIPOS && tipos[i].tipo != tipo; i++)
		;
	if (i == NTIPOS)
		return NULL;
	e = (mdf_evento *)calloc(1, sizeof *e);
	if (!e)
		return NULL;
	e->tipo = tipo;
	e->seq = 1;
	e->det = nfe_grupo_new(tipos[i].esq);
	if (!e->det || nfe_grupo_set(e->det, "descEvento", tipos[i].desc)) {
		mdf_evento_free(e);
		return NULL;
	}
	return e;
}

void mdf_evento_free(mdf_evento *e)
{
	if (!e)
		return;
	nfe_grupo_free(e->det);
	free(e);
}

nfe_grupo *mdf_evento_detalhe(mdf_evento *e)
{
	return e ? e->det : NULL;
}

int mdf_evento_set_chave(mdf_evento *e, const char *chave)
{
	int rc;

	if (!e || !chave)
		return E_ISNULL;
	rc = nfe_chave_validar(chave);
	if (rc != 0)
		return rc;
	if (mdf_padrao(chave, MDF_PADRAO_TChMDFe) != 0 ||
	    memcmp(chave + 20, "58", 2) != 0)
		return E_VALOR;
	memcpy(e->chave, chave, MDF_TAM_CHAVE + 1);
	if (!e->orgao[0])
		memcpy(e->orgao, chave, 2);
	return 0;
}

int mdf_evento_set_orgao(mdf_evento *e, const char *corgao)
{
	static const char *const orgaos[] = { MDF_VALORES_TCOrgaoIBGE, NULL };
	int i;

	if (!e || !corgao)
		return E_ISNULL;
	for (i = 0; orgaos[i]; i++)
		if (strcmp(corgao, orgaos[i]) == 0) {
			memcpy(e->orgao, corgao, 3);
			return 0;
		}
	return E_VALOR;
}

int mdf_evento_set_autor(mdf_evento *e, const char *cnpj_cpf)
{
	if (!e || !cnpj_cpf)
		return E_ISNULL;
	if (mdf_padrao(cnpj_cpf, MDF_PADRAO_TCnpj) == 0) {
		strcpy(e->cnpj, cnpj_cpf);
		e->cpf[0] = '\0';
		return 0;
	}
	if (mdf_padrao(cnpj_cpf, MDF_PADRAO_TCpf) == 0) {
		strcpy(e->cpf, cnpj_cpf);
		e->cnpj[0] = '\0';
		return 0;
	}
	return E_VALOR;
}

int mdf_evento_set_ambiente(mdf_evento *e, nfe_ambiente amb)
{
	if (!e)
		return E_ISNULL;
	if (amb != NFE_AMBIENTE_PRODUCAO && amb != NFE_AMBIENTE_HOMOLOGACAO)
		return E_VALOR;
	e->amb = (int)amb;
	return 0;
}

int mdf_evento_set_data(mdf_evento *e, const char *dh_evento)
{
	if (!e || !dh_evento)
		return E_ISNULL;
	if (strlen(dh_evento) >= sizeof e->dh ||
	    mdf_padrao(dh_evento, MDF_PADRAO_TDateTimeUTC) != 0)
		return E_VALOR;
	strcpy(e->dh, dh_evento);
	return 0;
}

int mdf_evento_set_sequencia(mdf_evento *e, int n)
{
	if (!e)
		return E_ISNULL;
	if (n < 1 || n > 999)
		return E_VALOR;
	e->seq = n;
	return 0;
}

static int texto(xmlTextWriterPtr w, const char *nome, const char *valor)
{
	return xmlTextWriterWriteElement(w, BAD_CAST nome, BAD_CAST valor) < 0
	               ? E_XML
	               : 0;
}

static int escreve_evento(xmlTextWriterPtr w, const void *dados)
{
	const mdf_evento *e = (const mdf_evento *)dados;
	/* "ID" + tpEvento + chave + nSeqEvento com 2 ou 3 dígitos */
	char id[2 + 6 + MDF_TAM_CHAVE + 3 + 1], tipo[8], amb[2], seq[4];
	int rc;

	snprintf(tipo, sizeof tipo, "%d", (int)e->tipo);
	snprintf(amb, sizeof amb, "%d", e->amb);
	snprintf(seq, sizeof seq, "%d", e->seq);
	snprintf(id, sizeof id, "ID%s%s%0*d", tipo, e->chave,
	         e->seq > 99 ? 3 : 2, e->seq);
	if (xmlTextWriterStartElement(w, BAD_CAST "eventoMDFe") < 0 ||
	    xmlTextWriterWriteAttribute(w, BAD_CAST "xmlns", BAD_CAST MDF_NS) <
	            0 ||
	    xmlTextWriterWriteAttribute(w, BAD_CAST "versao",
	                                BAD_CAST MDF_VERSAO_LEIAUTE) < 0 ||
	    xmlTextWriterStartElement(w, BAD_CAST "infEvento") < 0 ||
	    xmlTextWriterWriteAttribute(w, BAD_CAST "Id", BAD_CAST id) < 0)
		return E_XML;
	rc = texto(w, "cOrgao", e->orgao);
	if (rc == 0)
		rc = texto(w, "tpAmb", amb);
	if (rc == 0)
		rc = e->cnpj[0] ? texto(w, "CNPJ", e->cnpj)
		                : texto(w, "CPF", e->cpf);
	if (rc == 0)
		rc = texto(w, "chMDFe", e->chave);
	if (rc == 0)
		rc = texto(w, "dhEvento", e->dh);
	if (rc == 0)
		rc = texto(w, "tpEvento", tipo);
	if (rc == 0)
		rc = texto(w, "nSeqEvento", seq);
	if (rc != 0)
		return rc;
	if (xmlTextWriterStartElement(w, BAD_CAST "detEvento") < 0 ||
	    xmlTextWriterWriteAttribute(w, BAD_CAST "versaoEvento",
	                                BAD_CAST MDF_VERSAO_LEIAUTE) < 0)
		return E_XML;
	rc = nfe_grupo_write_xml(w, e->det);
	if (rc != 0)
		return rc;
	/* </detEvento></infEvento></eventoMDFe> */
	if (xmlTextWriterEndElement(w) < 0 || xmlTextWriterEndElement(w) < 0 ||
	    xmlTextWriterEndElement(w) < 0)
		return E_XML;
	return 0;
}

int mdf_evento_xml(const mdf_evento *e, char **xml, size_t *tam)
{
	if (!e || !xml)
		return E_ISNULL;
	if (!e->chave[0] || !e->orgao[0] || !(e->cnpj[0] || e->cpf[0]) ||
	    !e->amb || !e->dh[0])
		return E_VALOR;
	return mdf_xml_gera(escreve_evento, e, xml, tam);
}
