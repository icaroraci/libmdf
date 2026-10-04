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

/* Testes da versão da biblioteca */

#include <stdio.h>

#include <libmdf/versao.h>

#include "teste.h"

int main(void)
{
	char esperado[32];

	snprintf(esperado, sizeof esperado, "%d.%d.%d%s%s", MDF_VERSAO_MAIOR,
	         MDF_VERSAO_MENOR, MDF_VERSAO_REVISAO,
	         MDF_VERSAO_PRE[0] ? "-" : "", MDF_VERSAO_PRE);
	VERIFICA_STR(MDF_VERSAO, esperado);
	VERIFICA_STR(mdf_versao(), MDF_VERSAO);
	TESTE_FIM();
}
