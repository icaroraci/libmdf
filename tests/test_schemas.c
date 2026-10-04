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

/* Schemas oficiais do MDF-e em tests/schemas/mdfe: cada schema de
 * mensagem, de modal e de evento é carregado pelo validador da libnfe, e
 * uma consulta de status é validada contra o seu schema */

#include <stdio.h>
#include <string.h>

#include <libnfe/erros.h>
#include <libnfe/validar.h>

#include "teste.h"

static const char *const schemas[] = {
	"mdfe_v3.00.xsd",
	"enviMDFe_v3.00.xsd",
	"retMDFe_v3.00.xsd",
	"procMDFe_v3.00.xsd",
	"consSitMDFe_v3.00.xsd",
	"consStatServMDFe_v3.00.xsd",
	"consMDFeNaoEnc_v3.00.xsd",
	"eventoMDFe_v3.00.xsd",
	"retEventoMDFe_v3.00.xsd",
	"procEventoMDFe_v3.00.xsd",
	"mdfeModalRodoviario_v3.00.xsd",
	"mdfeModalAereo_v3.00.xsd",
	"mdfeModalAquaviario_v3.00.xsd",
	"mdfeModalFerroviario_v3.00.xsd",
	"evCancMDFe_v3.00.xsd",
	"evEncMDFe_v3.00.xsd",
	"evIncCondutorMDFe_v3.00.xsd",
	"evInclusaoDFeMDFe_v3.00.xsd",
	"evPagtoOperMDFe_v3.00.xsd",
	"evAlteracaoPagtoServMDFe_v3.00.xsd",
	"evConfirmaServMDFe_v3.00.xsd",
	NULL,
};

static nfe_validador *carrega(const char *dir, const char *xsd)
{
	char caminho[1024];

	snprintf(caminho, sizeof caminho, "%s/schemas/mdfe/%s", dir, xsd);
	return nfe_validador_xsd(caminho);
}

int main(int argc, char **argv)
{
	const char *dir = argc > 1 ? argv[1] : "tests";
	static const char status[] =
	        "<consStatServMDFe "
	        "xmlns=\"http://www.portalfiscal.inf.br/mdfe\""
	        " versao=\"3.00\"><tpAmb>2</tpAmb><xServ>STATUS</xServ>"
	        "</consStatServMDFe>";
	static const char status_errado[] =
	        "<consStatServMDFe "
	        "xmlns=\"http://www.portalfiscal.inf.br/mdfe\""
	        " versao=\"3.00\"><tpAmb>3</tpAmb><xServ>STATUS</xServ>"
	        "</consStatServMDFe>";
	nfe_validador *v;
	int i;

	for (i = 0; schemas[i]; i++) {
		v = carrega(dir, schemas[i]);
		if (!v)
			fprintf(stderr, "não carregou %s\n", schemas[i]);
		VERIFICA(v != NULL);
		nfe_validador_free(v);
	}

	v = carrega(dir, "consStatServMDFe_v3.00.xsd");
	VERIFICA(v != NULL);
	VERIFICA_INT(nfe_validar_xsd(v, status, strlen(status), 0, NULL), 0);
	VERIFICA_INT(nfe_validar_xsd(v, status_errado, strlen(status_errado), 0,
	                             NULL),
	             E_VALOR);
	nfe_validador_free(v);
	TESTE_FIM();
}
