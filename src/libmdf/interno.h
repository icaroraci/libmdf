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

/* Funções de uso interno da biblioteca (não exportadas) */

#ifndef LIBMDF_INTERNO_H
#define LIBMDF_INTERNO_H

#include <stddef.h>

#include <libxml/tree.h>
#include <libxml/xmlwriter.h>

#define MDF_INTERNO __attribute__((visibility("hidden")))

#define MDF_NS             "http://www.portalfiscal.inf.br/mdfe"
#define MDF_VERSAO_LEIAUTE "3.00"

/* Texto que cresce (erro: E_MALLOC depois de uma falha) */
struct mdf_buf {
	char *p;
	size_t n, cap;
	int erro;
};

MDF_INTERNO void mdf_buf_poe_n(struct mdf_buf *b, const char *s, size_t n);
MDF_INTERNO void mdf_buf_poe(struct mdf_buf *b, const char *s);
/* Entrega o texto em *dst (e o tamanho em *tam); 0 ou E_MALLOC */
MDF_INTERNO int mdf_buf_entrega(struct mdf_buf *b, char **dst, size_t *tam);

/* Confere valor contra um xs:pattern (padroes.h). 0 ou E_VALOR. */
MDF_INTERNO int mdf_padrao(const char *valor, const char *padrao);

/* Gera um documento (declaração e o que escreve põe) em *xml, sem as
 * quebras de linha da libxml2. 0, o erro de escreve, E_XML ou E_MALLOC. */
MDF_INTERNO int mdf_xml_gera(int (*escreve)(xmlTextWriterPtr, const void *),
                             const void *dados, char **xml, size_t *tam);

/* Pula BOM, espaços e a declaração <?xml?> de s (n bytes); devolve o
 * início do elemento e acerta *n (sem espaços no fim) */
MDF_INTERNO const char *mdf_pula_declaracao(const char *s, size_t *n);

/* Lê o XML (sem rede, sem mensagens); NULL se malformado */
MDF_INTERNO xmlDocPtr mdf_le_xml(const char *xml, size_t tam);
/* Primeiro filho elemento com o nome local (NULL: qualquer) */
MDF_INTERNO xmlNodePtr mdf_filho(xmlNodePtr pai, const char *nome);
/* Texto do filho com o nome; "" se não houver */
MDF_INTERNO const char *mdf_texto(xmlNodePtr pai, const char *nome);
/* Primeiro elemento com o nome local em no, nos irmãos seguintes ou nos
 * descendentes */
MDF_INTERNO xmlNodePtr mdf_acha(xmlNodePtr no, const char *nome);
/* Serializa o elemento, com as declarações de namespace herdadas, em
 * *dst. 0 ou E_MALLOC. */
MDF_INTERNO int mdf_serializa(xmlNodePtr no, char **dst, size_t *tam);

/* Monta <raiz xmlns versao="3.00">doc ret</raiz> (procs), com doc sem a
 * declaração e ret serializado. 0, E_XML ou E_MALLOC. */
MDF_INTERNO int mdf_proc(const char *raiz, const char *doc, size_t tam_doc,
                         xmlNodePtr ret, char **proc, size_t *tam_proc);

#endif /* LIBMDF_INTERNO_H */
