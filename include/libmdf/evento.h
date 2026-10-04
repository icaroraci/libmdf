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

#ifndef LIBMDF_EVENTO_H
#define LIBMDF_EVENTO_H

#include <stddef.h>

#include <libnfe/grupo.h>
#include <libnfe/nfe.h>

/*
 * Eventos do MDF-e (eventoMDFe, leiaute 3.00), do emitente.
 *
 * O cabeçalho (infEvento) é preenchido pelas funções abaixo; o detalhe do
 * evento (detEvento) é um grupo do motor de grupos, gerado do schema do
 * evento, com descEvento já preenchido:
 *
 *   mdf_evento *e = mdf_evento_new(MDF_EVENTO_ENCERRAMENTO);
 *   nfe_grupo *det = mdf_evento_detalhe(e);
 *   mdf_evento_set_chave(e, chave);              (também o cOrgao)
 *   mdf_evento_set_autor(e, "11222333000181");
 *   mdf_evento_set_ambiente(e, NFE_AMBIENTE_HOMOLOGACAO);
 *   mdf_evento_set_data(e, "2026-10-04T18:00:00-03:00");
 *   nfe_grupo_set(det, "nProt", "943260000000001");
 *   nfe_grupo_set(det, "dtEnc", "2026-10-04");
 *   nfe_grupo_set(det, "cUF", "43");
 *   nfe_grupo_set(det, "cMun", "4314902");
 *   mdf_evento_xml(e, &xml, &tam);
 *   nfe_assinar_elemento(cert, xml, tam, "infEvento", &assinado, &n);
 *   mdf_sefaz_evento(...)                      (ver sefaz.h)
 *
 * Campos do detalhe de cada tipo (ver os schemas ev*MDFe_v3.00.xsd):
 *   cancelamento: nProt, xJust
 *   encerramento: nProt, dtEnc, cUF, cMun, indEncPorTerceiro
 *   inclusão de condutor: condutor/xNome, condutor/CPF
 *   inclusão de DF-e: nProt, cMunCarrega, xMunCarrega, infDoc (lista com
 *     cMunDescarga, xMunDescarga, chNFe)
 *   pagamento da operação: nProt, infViagens, infPag (como em rodo)
 */

typedef enum mdf_tipo_evento {
	MDF_EVENTO_CANCELAMENTO = 110111,
	MDF_EVENTO_ENCERRAMENTO = 110112,
	MDF_EVENTO_INCLUSAO_CONDUTOR = 110114,
	MDF_EVENTO_INCLUSAO_DFE = 110115,
	MDF_EVENTO_PAGAMENTO_OPERACAO = 110116
} mdf_tipo_evento;

typedef struct mdf_evento mdf_evento;

/* Cria um evento do tipo, com nSeqEvento 1. Retorna NULL se o tipo não
 * for um dos acima ou se faltar memória. */
mdf_evento *mdf_evento_new(mdf_tipo_evento tipo);
void mdf_evento_free(mdf_evento *e);

/* Grupo do detalhe do evento (evCancMDFe, evEncMDFe...), que pertence ao
 * evento (não libere); NULL se e for NULL */
nfe_grupo *mdf_evento_detalhe(mdf_evento *e);

/* Chave de acesso do MDF-e (44 caracteres, com dígito verificador
 * válido). Também define o cOrgao como a UF da chave, se ele não tiver
 * sido informado. Retorna 0, E_ISNULL, E_TAMANHO ou E_VALOR. */
int mdf_evento_set_chave(mdf_evento *e, const char *chave);
/* Órgão de recepção do evento (código IBGE da UF, tabela estendida) */
int mdf_evento_set_orgao(mdf_evento *e, const char *corgao);
/* CNPJ (14 caracteres) ou CPF (11 dígitos) do autor do evento */
int mdf_evento_set_autor(mdf_evento *e, const char *cnpj_cpf);
int mdf_evento_set_ambiente(mdf_evento *e, nfe_ambiente amb);
/* Data e hora do evento, AAAA-MM-DDTHH:MM:SS seguido do fuso (-03:00) */
int mdf_evento_set_data(mdf_evento *e, const char *dh_evento);
/* Sequencial do evento do mesmo tipo (1 a 999) */
int mdf_evento_set_sequencia(mdf_evento *e, int n);

/* Gera o documento <eventoMDFe> sem assinatura (Id calculado), alocado e
 * terminado em '\0' em *xml (libere com free()); o tamanho vai em *tam,
 * se não for NULL. Assine com nfe_assinar_elemento(..., "infEvento", ...).
 * Retorna 0, E_ISNULL, E_VALOR (falta chave, autor, ambiente ou data, ou
 * campo obrigatório do detalhe), E_XML ou E_MALLOC. */
int mdf_evento_xml(const mdf_evento *e, char **xml, size_t *tam);

#endif /* LIBMDF_EVENTO_H */
