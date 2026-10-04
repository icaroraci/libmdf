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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/evp.h>
#include <zlib.h>

#include <libnfe/erros.h>
#include <libmdf/mdfe.h>
#include <libmdf/sefaz.h>

#include "interno.h"
#include "padroes.h"

#define WSDL MDF_NS "/wsdl/"

/* Webservices: nome (namespace do WSDL) e operação (MOC 3.00b, seções 4
 * e 5) */
static const struct {
	const char *nome, *operacao;
} servicos[] = {
	[MDF_SERVICO_AUTORIZACAO] = { "MDFeRecepcaoSinc", "mdfeRecepcao" },
	[MDF_SERVICO_CONSULTA] = { "MDFeConsulta", "mdfeConsultaMDF" },
	[MDF_SERVICO_STATUS] = { "MDFeStatusServico", "mdfeStatusServicoMDF" },
	[MDF_SERVICO_EVENTO] = { "MDFeRecepcaoEvento", "mdfeRecepcaoEvento" },
	[MDF_SERVICO_NAO_ENCERRADOS] = { "MDFeConsNaoEnc", "mdfeConsNaoEnc" },
};

#define NSERVICOS (sizeof servicos / sizeof servicos[0])

/* Endereços da SVRS (docs/ENDERECOS.md): servidor de cada ambiente e o
 * caminho, que é o mesmo nos dois */
static const char *const enderecos[2][NSERVICOS] = {
	{
	        "https://mdfe.svrs.rs.gov.br/ws/MDFeRecepcaoSinc/"
	        "MDFeRecepcaoSinc.asmx",
	        "https://mdfe.svrs.rs.gov.br/ws/MDFeConsulta/MDFeConsulta.asmx",
	        "https://mdfe.svrs.rs.gov.br/ws/MDFeStatusServico/"
	        "MDFeStatusServico.asmx",
	        "https://mdfe.svrs.rs.gov.br/ws/MDFeRecepcaoEvento/"
	        "MDFeRecepcaoEvento.asmx",
	        "https://mdfe.svrs.rs.gov.br/ws/MDFeConsNaoEnc/"
	        "MDFeConsNaoEnc.asmx",
	},
	{
	        "https://mdfe-homologacao.svrs.rs.gov.br/ws/MDFeRecepcaoSinc/"
	        "MDFeRecepcaoSinc.asmx",
	        "https://mdfe-homologacao.svrs.rs.gov.br/ws/MDFeConsulta/"
	        "MDFeConsulta.asmx",
	        "https://mdfe-homologacao.svrs.rs.gov.br/ws/MDFeStatusServico/"
	        "MDFeStatusServico.asmx",
	        "https://mdfe-homologacao.svrs.rs.gov.br/ws/MDFeRecepcaoEvento/"
	        "MDFeRecepcaoEvento.asmx",
	        "https://mdfe-homologacao.svrs.rs.gov.br/ws/MDFeConsNaoEnc/"
	        "MDFeConsNaoEnc.asmx",
	},
};

static int amb_valido(nfe_ambiente amb)
{
	return amb == NFE_AMBIENTE_PRODUCAO || amb == NFE_AMBIENTE_HOMOLOGACAO;
}

int mdf_sefaz_endereco(nfe_ambiente amb, mdf_servico servico, const char **url)
{
	if (!url)
		return E_ISNULL;
	if (!amb_valido(amb) || (unsigned)servico >= NSERVICOS)
		return E_VALOR;
	*url = enderecos[amb == NFE_AMBIENTE_PRODUCAO ? 0 : 1][servico];
	return 0;
}

/* Envia msg ao serviço e devolve o retorno em *ret */
static int envia(nfe_sefaz *s, const char *url, mdf_servico servico,
                 const char *msg, char **ret, size_t *tam)
{
	char ns[96];

	snprintf(ns, sizeof ns, WSDL "%s", servicos[servico].nome);
	return nfe_sefaz_enviar_ws(s, url, ns, servicos[servico].operacao,
	                           "mdfeDadosMsg", NULL, msg, ret, tam);
}

/* Envia msg e lê o cStat; o retorno vai em *ret (se ret não for NULL) */
static int consulta(nfe_sefaz *s, const char *url, mdf_servico servico,
                    const char *msg, int *cstat, char *xmotivo,
                    size_t tam_xmotivo, char **ret, size_t *tam_ret)
{
	char *r = NULL;
	size_t tam = 0;
	int rc;

	rc = envia(s, url, servico, msg, &r, &tam);
	if (rc != 0)
		return rc;
	rc = nfe_sefaz_cstat(r, tam, cstat, xmotivo, tam_xmotivo);
	if (rc == 0 && ret) {
		*ret = r;
		if (tam_ret)
			*tam_ret = tam;
		return 0;
	}
	free(r);
	return rc;
}

int mdf_sefaz_status(nfe_sefaz *s, const char *url, nfe_ambiente amb,
                     int *cstat, char *xmotivo, size_t tam_xmotivo)
{
	char msg[160];

	if (!s || !url || !cstat)
		return E_ISNULL;
	if (!amb_valido(amb))
		return E_VALOR;
	snprintf(msg, sizeof msg,
	         "<consStatServMDFe xmlns=\"" MDF_NS
	         "\" versao=\"" MDF_VERSAO_LEIAUTE
	         "\"><tpAmb>%d</tpAmb><xServ>STATUS</xServ></consStatServMDFe>",
	         (int)amb);
	return consulta(s, url, MDF_SERVICO_STATUS, msg, cstat, xmotivo,
	                tam_xmotivo, NULL, NULL);
}

int mdf_sefaz_consultar(nfe_sefaz *s, const char *url, nfe_ambiente amb,
                        const char *chave, int *cstat, char *xmotivo,
                        size_t tam_xmotivo, char **ret, size_t *tam_ret)
{
	char msg[256];

	if (!s || !url || !chave || !cstat)
		return E_ISNULL;
	if (!amb_valido(amb) || mdf_padrao(chave, MDF_PADRAO_TChMDFe) != 0)
		return E_VALOR;
	snprintf(msg, sizeof msg,
	         "<consSitMDFe xmlns=\"" MDF_NS
	         "\" versao=\"" MDF_VERSAO_LEIAUTE
	         "\"><tpAmb>%d</tpAmb><xServ>CONSULTAR</xServ>"
	         "<chMDFe>%s</chMDFe></consSitMDFe>",
	         (int)amb, chave);
	return consulta(s, url, MDF_SERVICO_CONSULTA, msg, cstat, xmotivo,
	                tam_xmotivo, ret, tam_ret);
}

int mdf_sefaz_nao_encerrados(nfe_sefaz *s, const char *url, nfe_ambiente amb,
                             const char *cnpj_cpf, int *cstat, char *xmotivo,
                             size_t tam_xmotivo, char **ret, size_t *tam_ret)
{
	char msg[256];
	const char *tag;

	if (!s || !url || !cnpj_cpf || !cstat)
		return E_ISNULL;
	if (!amb_valido(amb))
		return E_VALOR;
	if (mdf_padrao(cnpj_cpf, MDF_PADRAO_TCnpj) == 0)
		tag = "CNPJ";
	else if (mdf_padrao(cnpj_cpf, MDF_PADRAO_TCpf) == 0)
		tag = "CPF";
	else
		return E_VALOR;
	snprintf(msg, sizeof msg,
	         "<consMDFeNaoEnc xmlns=\"" MDF_NS
	         "\" versao=\"" MDF_VERSAO_LEIAUTE
	         "\"><tpAmb>%d</tpAmb><xServ>CONSULTAR N\xC3\x83O "
	         "ENCERRADOS</xServ><%s>%s</%s></consMDFeNaoEnc>",
	         (int)amb, tag, cnpj_cpf, tag);
	return consulta(s, url, MDF_SERVICO_NAO_ENCERRADOS, msg, cstat, xmotivo,
	                tam_xmotivo, ret, tam_ret);
}

/* ---- autorização ---- */

/* gzip de n bytes, em base64, alocado em *msg (MOC 3.00b, 3.4.1) */
static int compacta(const char *dados, size_t n, char **msg)
{
	z_stream z;
	unsigned char *gz;
	uLong cap;
	size_t tam;
	int rc;

	memset(&z, 0, sizeof z);
	if (n > 0x3fffffff)
		return E_VALOR;
	/* 15 + 16: janela padrão com cabeçalho gzip */
	if (deflateInit2(&z, Z_BEST_COMPRESSION, Z_DEFLATED, 15 + 16, 8,
	                 Z_DEFAULT_STRATEGY) != Z_OK)
		return E_MALLOC;
	cap = deflateBound(&z, (uLong)n);
	gz = (unsigned char *)malloc(cap);
	if (!gz) {
		deflateEnd(&z);
		return E_MALLOC;
	}
	z.next_in = (Bytef *)(uintptr_t)dados;
	z.avail_in = (uInt)n;
	z.next_out = gz;
	z.avail_out = (uInt)cap;
	rc = deflate(&z, Z_FINISH);
	tam = (size_t)z.total_out;
	deflateEnd(&z);
	if (rc != Z_STREAM_END) {
		free(gz);
		return E_MALLOC;
	}
	*msg = (char *)malloc(4 * ((tam + 2) / 3) + 1);
	if (*msg)
		EVP_EncodeBlock((unsigned char *)*msg, gz, (int)tam);
	free(gz);
	return *msg ? 0 : E_MALLOC;
}

/* Chave do Id de infMDFe (texto do documento), em chave */
static int chave_do_mdfe(const char *mdfe, size_t tam, char *chave)
{
	static const char marca[] = "Id=\"MDFe";
	size_t k = sizeof marca - 1, i;

	for (i = 0; i + k + MDF_TAM_CHAVE <= tam; i++)
		if (memcmp(mdfe + i, marca, k) == 0) {
			memcpy(chave, mdfe + i + k, MDF_TAM_CHAVE);
			chave[MDF_TAM_CHAVE] = '\0';
			return mdf_padrao(chave, MDF_PADRAO_TChMDFe) == 0
			               ? 0
			               : E_XML;
		}
	return E_XML;
}

int mdf_sefaz_autorizar(nfe_sefaz *s, const char *url, const char *mdfe,
                        int *cstat, char *xmotivo, size_t tam_xmotivo,
                        char **proc, size_t *tam_proc)
{
	char chave[MDF_TAM_CHAVE + 1];
	char *msg = NULL, *ret = NULL, *prot = NULL;
	size_t tam_ret = 0, tam_prot = 0, tam;
	const char *doc;
	xmlDocPtr x;
	xmlNodePtr p;
	int rc;

	if (!s || !url || !mdfe || !cstat || !proc)
		return E_ISNULL;
	*proc = NULL;
	tam = strlen(mdfe);
	doc = mdf_pula_declaracao(mdfe, &tam);
	if (tam < 6 || memcmp(doc, "<MDFe", 5) != 0 ||
	    chave_do_mdfe(doc, tam, chave) != 0)
		return E_XML;
	rc = compacta(doc, tam, &msg);
	if (rc != 0)
		return rc;
	rc = envia(s, url, MDF_SERVICO_AUTORIZACAO, msg, &ret, &tam_ret);
	free(msg);
	if (rc != 0)
		return rc;

	x = mdf_le_xml(ret, tam_ret);
	p = x ? mdf_acha(xmlDocGetRootElement(x), "protMDFe") : NULL;
	if (!p) {
		/* Sem protocolo: vale o cStat do retorno */
		xmlFreeDoc(x);
		rc = nfe_sefaz_cstat(ret, tam_ret, cstat, xmotivo, tam_xmotivo);
		free(ret);
		return rc;
	}
	free(ret);
	rc = mdf_serializa(p, &prot, &tam_prot);
	if (rc == 0)
		rc = nfe_sefaz_cstat(prot, tam_prot, cstat, xmotivo,
		                     tam_xmotivo);
	free(prot);
	if (rc == 0 && *cstat == 100) {
		if (strcmp(mdf_texto(mdf_filho(p, "infProt"), "chMDFe"),
		           chave) != 0)
			rc = E_XML; /* protocolo de outro MDF-e */
		else
			rc = mdf_proc("mdfeProc", doc, tam, p, proc, tam_proc);
	}
	xmlFreeDoc(x);
	return rc;
}

/* ---- eventos ---- */

int mdf_sefaz_evento(nfe_sefaz *s, const char *url, const char *evento,
                     int *cstat, char *xmotivo, size_t tam_xmotivo, char **proc,
                     size_t *tam_proc)
{
	char *ret = NULL;
	size_t tam_ret = 0, tam;
	const char *doc;
	xmlDocPtr x;
	xmlNodePtr r;
	int rc;

	if (!s || !url || !evento || !cstat || !proc)
		return E_ISNULL;
	*proc = NULL;
	tam = strlen(evento);
	doc = mdf_pula_declaracao(evento, &tam);
	if (tam < 12 || memcmp(doc, "<eventoMDFe", 11) != 0)
		return E_XML;
	rc = consulta(s, url, MDF_SERVICO_EVENTO, doc, cstat, xmotivo,
	              tam_xmotivo, &ret, &tam_ret);
	if (rc != 0)
		return rc;
	if (*cstat == 135 || *cstat == 136) {
		x = mdf_le_xml(ret, tam_ret);
		r = x ? xmlDocGetRootElement(x) : NULL;
		if (r && xmlStrEqual(r->name, BAD_CAST "retEventoMDFe"))
			rc = mdf_proc("procEventoMDFe", doc, tam, r, proc,
			              tam_proc);
		else
			rc = E_XML;
		xmlFreeDoc(x);
	}
	free(ret);
	return rc;
}
