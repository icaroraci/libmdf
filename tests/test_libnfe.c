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

/* Testes da dependência libnfe: os headers são encontrados, a biblioteca
 * é ligada e a chave de acesso do MDF-e (modelo 58), que tem a mesma
 * estrutura da chave da NF-e, é conferida por ela */

#include <libnfe/chave.h>
#include <libnfe/versao.h>

#include "teste.h"

int main(void)
{
	/* RS, 10/2026, CNPJ 11.222.333/0001-81, modelo 58, série 1, nº 1,
	 * emissão normal */
	static const char chave[] =
	        "43261011222333000181580010000000011100000015";

	/* libnfe 1.x (SONAME libnfe.so.1) */
	VERIFICA_INT(NFE_VERSAO_MAIOR, 1);
	VERIFICA(nfe_versao() != NULL && nfe_versao()[0] == '1');

	VERIFICA_INT(nfe_chave_dv(chave), 5);
	VERIFICA_INT(nfe_chave_validar(chave), 0);
	TESTE_FIM();
}
