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

#ifndef LIBMDF_VERSAO_H
#define LIBMDF_VERSAO_H

/* Versão da biblioteca, no formato MAIOR.MENOR.REVISÃO[-PRÉ] (versionamento
 * semântico): a versão maior muda quando a API ou a ABI deixam de ser
 * compatíveis; enquanto ela for 0, a API ainda pode mudar a cada versão
 * menor. MDF_VERSAO_PRE marca uma pré-versão (ex.: "dev") e fica vazio
 * numa versão final. O Makefile lê estas macros para nomear libmdf.so. */
#define MDF_VERSAO_MAIOR   0
#define MDF_VERSAO_MENOR   1
#define MDF_VERSAO_REVISAO 0
#define MDF_VERSAO_PRE     "dev"
#define MDF_VERSAO         "0.1.0-dev"

/* Versão da biblioteca carregada em tempo de execução (ex.: "0.1.0-dev"),
 * que pode diferir de MDF_VERSAO, a dos headers usados na compilação. */
const char *mdf_versao(void);

#endif /* LIBMDF_VERSAO_H */
