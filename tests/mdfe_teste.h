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

/* MDF-e de teste (modal rodoviário, RS, homologação) montado com a API da
 * libmdf, usado pelos testes */

#ifndef LIBMDF_MDFE_TESTE_H
#define LIBMDF_MDFE_TESTE_H

#include <string.h>

#include <libnfe/chave.h>
#include <libnfe/grupo.h>
#include <libmdf/mdfe.h>

#include "teste.h"

#define SET(g, campo, valor) VERIFICA_INT(nfe_grupo_set(g, campo, valor), 0)

/* Chave de uma NF-e de teste (RS, CNPJ 11.222.333/0001-81), em chave */
static void chave_nfe(char chave[45])
{
	memcpy(chave, "4326101122233300018155001000000123100000123", 43);
	chave[43] = (char)('0' + nfe_chave_dv(chave));
	chave[44] = '\0';
}

/* MDF-e com os grupos obrigatórios e os opcionais mais comuns; tpemis 2
 * emite em contingência */
static mdf_mdfe *mdfe_teste(const char *tpemis)
{
	mdf_mdfe *m = mdf_mdfe_new();
	nfe_grupo *ide, *emit, *rodo, *g, *item;
	char nfe[45];

	VERIFICA(m != NULL);
	if (!m)
		return NULL;
	ide = mdf_mdfe_grupo(m, "ide");
	SET(ide, "cUF", "43");
	SET(ide, "tpAmb", "2");
	SET(ide, "tpEmit", "2");
	SET(ide, "serie", "1");
	SET(ide, "nMDF", "1");
	SET(ide, "cMDF", "12345678");
	SET(ide, "modal", "1");
	SET(ide, "dhEmi", "2026-10-04T10:00:00-03:00");
	SET(ide, "tpEmis", tpemis);
	SET(ide, "procEmi", "0");
	SET(ide, "verProc", "libmdf 1.0");
	SET(ide, "UFIni", "RS");
	SET(ide, "UFFim", "RS");
	VERIFICA_INT(nfe_grupo_add(ide, "infMunCarrega", &item), 0);
	SET(item, "cMunCarrega", "4314902");
	SET(item, "xMunCarrega", "PORTO ALEGRE");

	emit = mdf_mdfe_grupo(m, "emit");
	SET(emit, "CNPJ", "11222333000181");
	SET(emit, "IE", "0960000000");
	SET(emit, "xNome", "EMPRESA DE TESTE LTDA");
	SET(emit, "xLgr", "RUA DOS TESTES");
	SET(emit, "nro", "100");
	SET(emit, "xBairro", "CENTRO");
	SET(emit, "cMun", "4314902");
	SET(emit, "xMun", "PORTO ALEGRE");
	SET(emit, "UF", "RS");

	rodo = mdf_mdfe_grupo(m, "rodo");
	SET(rodo, "veicTracao/placa", "ABC1D23");
	SET(rodo, "veicTracao/tara", "5000");
	SET(rodo, "veicTracao/capKG", "10000");
	SET(rodo, "veicTracao/tpRod", "02");
	SET(rodo, "veicTracao/tpCar", "02");
	SET(rodo, "veicTracao/UF", "RS");
	VERIFICA_INT(nfe_grupo_add(rodo, "veicTracao/condutor", &item), 0);
	SET(item, "xNome", "JOSE DA SILVA");
	SET(item, "CPF", "12345678909");

	g = mdf_mdfe_grupo(m, "infDoc");
	VERIFICA_INT(nfe_grupo_add(g, "infMunDescarga", &item), 0);
	SET(item, "cMunDescarga", "4304606");
	SET(item, "xMunDescarga", "CANOAS");
	chave_nfe(nfe);
	{
		nfe_grupo *doc;

		VERIFICA_INT(nfe_grupo_add(item, "infNFe", &doc), 0);
		SET(doc, "chNFe", nfe);
	}

	g = mdf_mdfe_grupo(m, "prodPred");
	SET(g, "tpCarga", "05");
	SET(g, "xProd", "MERCADORIAS DIVERSAS");

	g = mdf_mdfe_grupo(m, "tot");
	SET(g, "qNFe", "1");
	SET(g, "vCarga", "1000.00");
	SET(g, "cUnid", "01");
	SET(g, "qCarga", "100.0000");

	VERIFICA_INT(mdf_mdfe_add(m, "lacres", &item), 0);
	SET(item, "nLacre", "LACRE001");
	VERIFICA_INT(mdf_mdfe_add(m, "autXML", &item), 0);
	SET(item, "CPF", "12345678909");

	g = mdf_mdfe_grupo(m, "infAdic");
	SET(g, "infCpl", "MDF-E DE TESTE DA LIBMDF");
	return m;
}

#endif
