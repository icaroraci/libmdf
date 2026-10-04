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

/* Auxiliares de texto e XML usados pelo MDF-e, pelos eventos e pelos
 * webservices */

#include <stdlib.h>
#include <string.h>

#include <libxml/parser.h>
#include <libxml/xmlregexp.h>

#include <libnfe/erros.h>

#include "interno.h"

void mdf_buf_poe_n(struct mdf_buf *b, const char *s, size_t n)
{
	if (b->erro)
		return;
	if (b->n + n + 1 > b->cap) {
		size_t cap = b->cap ? b->cap : 256;
		char *p;

		while (cap < b->n + n + 1)
			cap *= 2;
		p = (char *)realloc(b->p, cap);
		if (!p) {
			b->erro = E_MALLOC;
			return;
		}
		b->p = p;
		b->cap = cap;
	}
	memcpy(b->p + b->n, s, n);
	b->n += n;
	b->p[b->n] = '\0';
}

void mdf_buf_poe(struct mdf_buf *b, const char *s)
{
	mdf_buf_poe_n(b, s, strlen(s));
}

int mdf_buf_entrega(struct mdf_buf *b, char **dst, size_t *tam)
{
	if (b->erro || !b->p) {
		free(b->p);
		b->p = NULL;
		return E_MALLOC;
	}
	*dst = b->p;
	if (tam)
		*tam = b->n;
	b->p = NULL;
	return 0;
}

int mdf_padrao(const char *valor, const char *padrao)
{
	xmlRegexpPtr re;
	int ok;

	if (!valor || !padrao)
		return E_ISNULL;
	re = xmlRegexpCompile(BAD_CAST padrao);
	if (!re)
		return E_MALLOC;
	ok = xmlRegexpExec(re, BAD_CAST valor) == 1;
	xmlRegFreeRegexp(re);
	return ok ? 0 : E_VALOR;
}

int mdf_xml_gera(int (*escreve)(xmlTextWriterPtr, const void *),
                 const void *dados, char **xml, size_t *tam)
{
	xmlBufferPtr buf;
	xmlTextWriterPtr writer;
	struct mdf_buf saida = { 0 };
	const char *conteudo, *fim;
	size_t decl, n;
	int rc;

	buf = xmlBufferCreate();
	writer = buf ? xmlNewTextWriterMemory(buf, 0) : NULL;
	if (!writer) {
		xmlBufferFree(buf);
		return E_MALLOC;
	}
	rc = xmlTextWriterStartDocument(writer, NULL, "UTF-8", NULL) < 0 ? E_XML
	                                                                 : 0;
	if (rc == 0)
		rc = escreve(writer, dados);
	if (rc == 0 && xmlTextWriterEndDocument(writer) < 0)
		rc = E_XML;
	xmlFreeTextWriter(writer);
	if (rc == 0) {
		/* Sem as quebras de linha após a declaração e no fim */
		conteudo = (const char *)xmlBufferContent(buf);
		fim = strstr(conteudo, "?>");
		decl = fim ? (size_t)(fim + 2 - conteudo) : 0;
		mdf_buf_poe_n(&saida, conteudo, decl);
		fim = conteudo + decl;
		while (*fim == '\n')
			fim++;
		n = strlen(fim);
		while (n > 0 && fim[n - 1] == '\n')
			n--;
		mdf_buf_poe_n(&saida, fim, n);
		rc = mdf_buf_entrega(&saida, xml, tam);
	}
	xmlBufferFree(buf);
	return rc;
}

static int espaco(char c)
{
	return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

const char *mdf_pula_declaracao(const char *s, size_t *n)
{
	const char *fim = s + *n, *p;

	if (fim - s >= 3 && memcmp(s, "\xEF\xBB\xBF", 3) == 0)
		s += 3;
	while (s < fim && espaco(*s))
		s++;
	if (fim - s >= 5 && memcmp(s, "<?xml", 5) == 0) {
		for (p = s; p + 1 < fim && !(p[0] == '?' && p[1] == '>'); p++)
			;
		s = p + 1 < fim ? p + 2 : fim;
		while (s < fim && espaco(*s))
			s++;
	}
	while (fim > s && espaco(fim[-1]))
		fim--;
	*n = (size_t)(fim - s);
	return s;
}

xmlDocPtr mdf_le_xml(const char *xml, size_t tam)
{
	if (tam > 0x7fffffff)
		return NULL;
	return xmlReadMemory(xml, (int)tam, "mdfe.xml", NULL,
	                     XML_PARSE_NONET | XML_PARSE_NOERROR |
	                             XML_PARSE_NOWARNING | XML_PARSE_NOBLANKS);
}

xmlNodePtr mdf_filho(xmlNodePtr pai, const char *nome)
{
	xmlNodePtr f;

	for (f = pai ? pai->children : NULL; f; f = f->next)
		if (f->type == XML_ELEMENT_NODE &&
		    (!nome || xmlStrEqual(f->name, BAD_CAST nome)))
			return f;
	return NULL;
}

const char *mdf_texto(xmlNodePtr pai, const char *nome)
{
	xmlNodePtr e = mdf_filho(pai, nome);

	if (e && e->children && e->children->type == XML_TEXT_NODE &&
	    e->children->content)
		return (const char *)e->children->content;
	return "";
}

xmlNodePtr mdf_acha(xmlNodePtr no, const char *nome)
{
	xmlNodePtr f, achado;

	for (f = no; f; f = f->next) {
		if (f->type != XML_ELEMENT_NODE)
			continue;
		if (xmlStrEqual(f->name, BAD_CAST nome))
			return f;
		achado = mdf_acha(f->children, nome);
		if (achado)
			return achado;
	}
	return NULL;
}

int mdf_serializa(xmlNodePtr no, char **dst, size_t *tam)
{
	xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
	xmlNodePtr copia;
	xmlBufferPtr b;
	struct mdf_buf saida = { 0 };
	int rc = E_MALLOC;

	if (!doc)
		return E_MALLOC;
	copia = xmlDocCopyNode(no, doc, 1);
	if (copia) {
		xmlDocSetRootElement(doc, copia);
		xmlReconciliateNs(doc, copia);
		b = xmlBufferCreate();
		if (b) {
			if (xmlNodeDump(b, doc, copia, 0, 0) >= 0) {
				mdf_buf_poe_n(&saida,
				              (const char *)xmlBufferContent(b),
				              (size_t)xmlBufferLength(b));
				rc = mdf_buf_entrega(&saida, dst, tam);
			}
			xmlBufferFree(b);
		}
	}
	xmlFreeDoc(doc);
	return rc;
}

int mdf_proc(const char *raiz, const char *doc, size_t tam_doc, xmlNodePtr ret,
             char **proc, size_t *tam_proc)
{
	struct mdf_buf b = { 0 };
	char *r = NULL;
	size_t tam_r = 0;
	int rc;

	doc = mdf_pula_declaracao(doc, &tam_doc);
	rc = mdf_serializa(ret, &r, &tam_r);
	if (rc != 0)
		return rc;
	mdf_buf_poe(&b, "<?xml version=\"1.0\" encoding=\"UTF-8\"?><");
	mdf_buf_poe(&b, raiz);
	mdf_buf_poe(&b,
	            " xmlns=\"" MDF_NS "\" versao=\"" MDF_VERSAO_LEIAUTE "\">");
	mdf_buf_poe_n(&b, doc, tam_doc);
	mdf_buf_poe_n(&b, r, tam_r);
	mdf_buf_poe(&b, "</");
	mdf_buf_poe(&b, raiz);
	mdf_buf_poe(&b, ">");
	free(r);
	return mdf_buf_entrega(&b, proc, tam_proc);
}
