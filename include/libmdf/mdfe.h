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

#ifndef LIBMDF_MDFE_H
#define LIBMDF_MDFE_H

#include <stddef.h>

#include <libnfe/assinatura.h>
#include <libnfe/grupo.h>

/*
 * MDF-e (modelo 58, leiaute 3.00) com o modal rodoviário.
 *
 * Os grupos do leiaute são preenchidos pelo motor de grupos da libnfe
 * (<libnfe/grupo.h>), pelo caminho do campo, com as regras (padrões,
 * tamanhos, valores) tiradas dos schemas oficiais:
 *
 *   mdf_mdfe *m = mdf_mdfe_new();
 *   nfe_grupo *ide = mdf_mdfe_grupo(m, "ide"), *mun, *cond, *doc;
 *   nfe_grupo_set(ide, "cUF", "43");
 *   nfe_grupo_set(ide, "dhEmi", "2026-10-04T10:00:00-03:00");
 *   ...
 *   nfe_grupo_add(ide, "infMunCarrega", &mun);
 *   nfe_grupo_set(mun, "cMunCarrega", "4314902");
 *   nfe_grupo_set(mdf_mdfe_grupo(m, "rodo"), "veicTracao/placa", "ABC1D23");
 *   nfe_grupo_add(mdf_mdfe_grupo(m, "rodo"), "veicTracao/condutor", &cond);
 *   nfe_grupo_add(mdf_mdfe_grupo(m, "infDoc"), "infMunDescarga", &doc);
 *   ...
 *   mdf_mdfe_xml(m, &xml, &tam);              (chave, cDV e Id calculados)
 *   mdf_assinar(cert, xml, tam, &mdfe, &tam_mdfe);  (assinatura e QR Code)
 *   mdf_sefaz_autorizar(...)                  (ver sefaz.h)
 *
 * O cDV de ide e o Id de infMDFe são calculados por mdf_mdfe_xml a partir
 * de cUF, dhEmi, CNPJ ou CPF do emitente, serie, nMDF, tpEmis e cMDF; o
 * modelo (mod) vale 58 desde mdf_mdfe_new. O modal rodoviário vai em
 * infModal com versaoModal 3.00.
 */

/* Tamanho da chave de acesso (sem o terminador) */
#define MDF_TAM_CHAVE 44

/* Endereço da consulta do QR Code (infMDFeSupl/qrCodMDFe), o mesmo nos
 * dois ambientes (MOC 3.00b, seção 9.2; conferir em
 * https://dfe-portal.svrs.rs.gov.br/MDFe/Servicos) */
#define MDF_URL_QRCODE "https://dfe-portal.svrs.rs.gov.br/mdfe/qrCode"

typedef struct mdf_mdfe mdf_mdfe;

/* Cria um MDF-e vazio (com mod 58). Retorna NULL se faltar memória. */
mdf_mdfe *mdf_mdfe_new(void);
void mdf_mdfe_free(mdf_mdfe *m);

/* Grupo do MDF-e com o nome do elemento: "ide", "emit", "rodo" (modal
 * rodoviário), "infDoc", "prodPred", "tot", "infAdic", "infRespTec",
 * "infSolicNFF" (pedido de emissão da Nota Fiscal Fácil) ou "infPAA"
 * (Provedor de Assinatura e Autorização).
 * O grupo pertence ao MDF-e (não libere). Retorna NULL se m ou nome
 * forem NULL ou se o nome não for de um desses grupos. */
nfe_grupo *mdf_mdfe_grupo(mdf_mdfe *m, const char *nome);

/* Acrescenta um item a um grupo que se repete no MDF-e: "seg" (seguro da
 * carga), "lacres" ou "autXML" (autorizados a baixar o XML). O novo
 * grupo, que pertence ao MDF-e, vai em *item. Retorna 0, E_ISNULL,
 * E_VALOR (nome desconhecido ou limite do leiaute: 10 autXML) ou
 * E_MALLOC. */
int mdf_mdfe_add(mdf_mdfe *m, const char *nome, nfe_grupo **item);
/* Quantidade de itens de um desses grupos (0 se m ou nome forem
 * inválidos) */
int mdf_mdfe_quantidade(const mdf_mdfe *m, const char *nome);
/* Item i (a partir de 0) de um desses grupos, ou NULL */
nfe_grupo *mdf_mdfe_item(const mdf_mdfe *m, const char *nome, int i);

/* Chave de acesso (44 caracteres e '\0', em chave) calculada a partir de
 * ide e emit, com o dígito verificador. Retorna 0, E_ISNULL ou E_VALOR
 * (falta cUF, dhEmi, CNPJ ou CPF, serie, nMDF, tpEmis ou cMDF). */
int mdf_mdfe_chave(const mdf_mdfe *m, char chave[MDF_TAM_CHAVE + 1]);

/* Gera o documento <MDFe> sem assinatura, com o cDV e o Id calculados
 * (gravados também em ide), alocado e terminado em '\0' em *xml (libere
 * com free()); o tamanho vai em *tam, se não for NULL. Retorna 0,
 * E_ISNULL, E_VALOR (falta campo obrigatório, escolha com mais de um
 * ramo ou chave incompleta), E_XML ou E_MALLOC. */
int mdf_mdfe_xml(mdf_mdfe *m, char **xml, size_t *tam);

/* Assina o MDF-e xml (documento <MDFe> de mdf_mdfe_xml, tam bytes) com o
 * certificado e acrescenta o QR Code (infMDFeSupl/qrCodMDFe) com
 * MDF_URL_QRCODE, a chave e o tpAmb; em contingência (tpEmis 2), também o
 * parâmetro sign, a assinatura RSA-SHA1 da chave com o mesmo certificado,
 * em base64. Devolve em *mdfe o documento pronto para transmitir (alocado
 * e terminado em '\0'; libere com free()); o tamanho vai em *tam_mdfe, se
 * não for NULL. Retorna 0, E_ISNULL, E_XML (documento malformado, sem
 * infMDFe com Id ou já assinado), E_VALOR (falha ao assinar) ou
 * E_MALLOC. */
int mdf_assinar(const nfe_certificado *cert, const char *xml, size_t tam,
                char **mdfe, size_t *tam_mdfe);

#endif /* LIBMDF_MDFE_H */
