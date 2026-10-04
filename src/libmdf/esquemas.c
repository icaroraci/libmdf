/* Gerado por tools/gerar_esquemas.py a partir de tests/schemas/mdfe.
 * Não edite à mão: rode `python3 "$(pkg-config --variable=ferramentas libnfe)/gerar_esquemas.py" --config tools/documento.json`. */

#include <stddef.h>

#include "esquemas.h"

#if NFE_ESQ_VERSAO != 1
#error "tabelas geradas para outra versão do motor de grupos da libnfe"
#endif

/* clang-format off */
static const char *const valores_0[] = { "AC", "AL", "AM", "AP", "BA", "CE", "DF", "ES", "GO", "MA", "MG", "MS", "MT", "PA", "PB", "PE", "PI", "PR", "RJ", "RN", "RO", "RR", "RS", "SC", "SE", "SP", "TO", "EX", NULL };
static const char *const valores_1[] = { "11", "12", "13", "14", "15", "16", "17", "21", "22", "23", "24", "25", "26", "27", "28", "29", "31", "32", "33", "35", "41", "42", "43", "50", "51", "52", "53", NULL };
static const char *const valores_2[] = { "1", "2", NULL };
static const char *const valores_3[] = { "1", "2", "3", NULL };
static const char *const valores_4[] = { "58", NULL };
static const char *const valores_5[] = { "1", "2", "3", "4", NULL };
static const char *const valores_6[] = { "0", "4", NULL };
static const char *const valores_7[] = { "1", NULL };
static const char *const valores_8[] = { "1", "2", "3", "4", "5", "6", "7", NULL };
static const char *const valores_9[] = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", NULL };
static const char *const valores_10[] = { "01", "02", NULL };
static const char *const valores_11[] = { "01", "04", NULL };
static const char *const valores_12[] = { "01", "02", "03", "04", "99", NULL };
static const char *const valores_13[] = { "0", "1", NULL };
static const char *const valores_14[] = { "0", "1", "2", NULL };
static const char *const valores_15[] = { "00", "01", "02", "03", "04", "05", NULL };
static const char *const valores_16[] = { "02", "04", "06", "07", "08", "10", "11", "12", "13", "14", NULL };
static const char *const valores_17[] = { "01", "02", "03", "04", "05", "06", NULL };
static const char *const valores_18[] = { "Cancelamento", NULL };
static const char *const valores_19[] = { "Encerramento", NULL };
static const char *const valores_20[] = { "11", "12", "13", "14", "15", "16", "17", "21", "22", "23", "24", "25", "26", "27", "28", "29", "31", "32", "33", "35", "41", "42", "43", "50", "51", "52", "53", "99", NULL };
static const char *const valores_21[] = { "Inclusao Condutor", NULL };
static const char *const valores_22[] = { "Inclus\xC3\xA3o DF-e", "Inclusao DF-e", NULL };
static const char *const valores_23[] = { "Pagamento Opera\xC3\xA7\xC3\xA3o MDF-e", "Pagamento Operacao MDF-e", NULL };

static const struct nfe_esq_no nos_ide_infMunCarrega[] = {
	{ "infMunCarrega", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 2, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 2, -1, 0, 0, NULL },
	{ "cMunCarrega", ESQ_ELEM, 1, 1, "[0-9]{7}", NULL, 0, 0, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "xMunCarrega", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 2, 60, 1, 1, -1, -1, 1, 1, 2, -1, 0, 0, NULL },
};

static const struct nfe_esq mdf_esq_ide_infMunCarrega = { "infMunCarrega", nos_ide_infMunCarrega, 4, 2, 0 };

static const struct nfe_esq_no nos_ide_infPercurso[] = {
	{ "infPercurso", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 1, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 1, -1, 0, 0, NULL },
	{ "UFPer", ESQ_ELEM, 1, 1, NULL, valores_0, 0, 0, 0, 1, -1, -1, 0, 0, 1, -1, 0, 0, NULL },
};

static const struct nfe_esq mdf_esq_ide_infPercurso = { "infPercurso", nos_ide_infPercurso, 3, 1, 0 };

static const struct nfe_esq_no nos_ide[] = {
	{ "ide", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 19, -1, 0, 2, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 19, -1, 0, 2, NULL },
	{ "cUF", ESQ_ELEM, 1, 1, NULL, valores_1, 0, 0, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "tpAmb", ESQ_ELEM, 1, 1, NULL, valores_2, 0, 0, 0, 1, -1, 4, 1, 1, 2, -1, 0, 0, NULL },
	{ "tpEmit", ESQ_ELEM, 1, 1, NULL, valores_3, 0, 0, 0, 1, -1, 5, 2, 2, 3, -1, 0, 0, NULL },
	{ "tpTransp", ESQ_ELEM, 0, 1, NULL, valores_3, 0, 0, 0, 1, -1, 6, 3, 3, 4, -1, 0, 0, NULL },
	{ "mod", ESQ_ELEM, 1, 1, NULL, valores_4, 0, 0, 0, 1, -1, 7, 4, 4, 5, -1, 0, 0, NULL },
	{ "serie", ESQ_ELEM, 1, 1, "0|[1-9]{1}[0-9]{0,2}", NULL, 0, 0, 0, 1, -1, 8, 5, 5, 6, -1, 0, 0, NULL },
	{ "nMDF", ESQ_ELEM, 1, 1, "[1-9]{1}[0-9]{0,8}", NULL, 0, 0, 0, 1, -1, 9, 6, 6, 7, -1, 0, 0, NULL },
	{ "cMDF", ESQ_ELEM, 1, 1, "[0-9]{8}", NULL, 0, 0, 0, 1, -1, 10, 7, 7, 8, -1, 0, 0, NULL },
	{ "cDV", ESQ_ELEM, 1, 1, "[0-9]{1}", NULL, 0, 0, 0, 1, -1, 11, 8, 8, 9, -1, 0, 0, NULL },
	{ "modal", ESQ_ELEM, 1, 1, NULL, valores_5, 0, 0, 0, 1, -1, 12, 9, 9, 10, -1, 0, 0, NULL },
	{ "dhEmi", ESQ_ELEM, 1, 1, "(((20(([02468][048])|([13579][26]))-02-29))|(20[0-9][0-9])-((((0[1-9])|(1[0-2]))-((0[1-9])|(1\\d)|(2[0-8])))|((((0[13578])|(1[02]))-31)|(((0[1,3-9])|(1[0-2]))-(29|30)))))T(20|21|22|23|[0-1]\\d):[0-5]\\d:[0-5]\\d([\\-,\\+](0[0-9]|10|11):00|([\\+](12):00))", NULL, 0, 0, 0, 1, -1, 13, 10, 10, 11, -1, 0, 0, NULL },
	{ "tpEmis", ESQ_ELEM, 1, 1, NULL, valores_3, 0, 0, 0, 1, -1, 14, 11, 11, 12, -1, 0, 0, NULL },
	{ "procEmi", ESQ_ELEM, 1, 1, NULL, valores_6, 0, 0, 0, 1, -1, 15, 12, 12, 13, -1, 0, 0, NULL },
	{ "verProc", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 20, 1, 1, -1, 16, 13, 13, 14, -1, 0, 0, NULL },
	{ "UFIni", ESQ_ELEM, 1, 1, NULL, valores_0, 0, 0, 0, 1, -1, 17, 14, 14, 15, -1, 0, 0, NULL },
	{ "UFFim", ESQ_ELEM, 1, 1, NULL, valores_0, 0, 0, 0, 1, -1, 18, 15, 15, 16, -1, 0, 0, NULL },
	{ "infMunCarrega", ESQ_LISTA, 1, 50, NULL, NULL, 0, 0, 0, 1, -1, 19, -1, 16, 16, 0, 0, 1, &mdf_esq_ide_infMunCarrega },
	{ "infPercurso", ESQ_LISTA, 0, 25, NULL, NULL, 0, 0, 0, 1, -1, 20, -1, 16, 16, 1, 1, 2, &mdf_esq_ide_infPercurso },
	{ "dhIniViagem", ESQ_ELEM, 0, 1, "(((20(([02468][048])|([13579][26]))-02-29))|(20[0-9][0-9])-((((0[1-9])|(1[0-2]))-((0[1-9])|(1\\d)|(2[0-8])))|((((0[13578])|(1[02]))-31)|(((0[1,3-9])|(1[0-2]))-(29|30)))))T(20|21|22|23|[0-1]\\d):[0-5]\\d:[0-5]\\d([\\-,\\+](0[0-9]|10|11):00|([\\+](12):00))", NULL, 0, 0, 0, 1, -1, 21, 16, 16, 17, -1, 2, 2, NULL },
	{ "indCanalVerde", ESQ_ELEM, 0, 1, NULL, valores_7, 0, 0, 0, 1, -1, 22, 17, 17, 18, -1, 2, 2, NULL },
	{ "indCarregaPosterior", ESQ_ELEM, 0, 1, NULL, valores_7, 0, 0, 0, 1, -1, -1, 18, 18, 19, -1, 2, 2, NULL },
};

const struct nfe_esq mdf_esq_ide = { "ide", nos_ide, 23, 19, 2 };

static const struct nfe_esq_no nos_emit[] = {
	{ "emit", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 15, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 15, -1, 0, 0, NULL },
	{ NULL, ESQ_CHOICE, 1, 1, NULL, NULL, 0, 0, 0, 1, 3, 5, -1, 0, 2, -1, 0, 0, NULL },
	{ "CNPJ", ESQ_ELEM, 1, 1, "[A-Z0-9]{12}[0-9]{2}", NULL, 0, 0, 0, 2, -1, 4, 0, 0, 1, -1, 0, 0, NULL },
	{ "CPF", ESQ_ELEM, 1, 1, "[0-9]{11}", NULL, 0, 0, 0, 2, -1, -1, 1, 1, 2, -1, 0, 0, NULL },
	{ "IE", ESQ_ELEM, 0, 1, "[0-9]{2,14}", NULL, 0, 0, 0, 1, -1, 6, 2, 2, 3, -1, 0, 0, NULL },
	{ "xNome", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 2, 60, 1, 1, -1, 7, 3, 3, 4, -1, 0, 0, NULL },
	{ "xFant", ESQ_ELEM, 0, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 60, 1, 1, -1, 8, 4, 4, 5, -1, 0, 0, NULL },
	{ "enderEmit", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, 1, 9, -1, -1, 5, 15, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 8, 10, -1, -1, 5, 15, -1, 0, 0, NULL },
	{ "xLgr", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 2, 60, 1, 9, -1, 11, 5, 5, 6, -1, 0, 0, NULL },
	{ "nro", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 60, 1, 9, -1, 12, 6, 6, 7, -1, 0, 0, NULL },
	{ "xCpl", ESQ_ELEM, 0, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 60, 1, 9, -1, 13, 7, 7, 8, -1, 0, 0, NULL },
	{ "xBairro", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 2, 60, 1, 9, -1, 14, 8, 8, 9, -1, 0, 0, NULL },
	{ "cMun", ESQ_ELEM, 1, 1, "[0-9]{7}", NULL, 0, 0, 0, 9, -1, 15, 9, 9, 10, -1, 0, 0, NULL },
	{ "xMun", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 2, 60, 1, 9, -1, 16, 10, 10, 11, -1, 0, 0, NULL },
	{ "CEP", ESQ_ELEM, 0, 1, "[0-9]{8}", NULL, 0, 0, 0, 9, -1, 17, 11, 11, 12, -1, 0, 0, NULL },
	{ "UF", ESQ_ELEM, 1, 1, NULL, valores_0, 0, 0, 0, 9, -1, 18, 12, 12, 13, -1, 0, 0, NULL },
	{ "fone", ESQ_ELEM, 0, 1, "[0-9]{7,12}", NULL, 0, 0, 0, 9, -1, 19, 13, 13, 14, -1, 0, 0, NULL },
	{ "email", ESQ_ELEM, 0, 1, "[^@]+@[^\\.]+\\..+", NULL, 6, 60, 0, 9, -1, -1, 14, 14, 15, -1, 0, 0, NULL },
};

const struct nfe_esq mdf_esq_emit = { "emit", nos_emit, 20, 15, 0 };

static const struct nfe_esq_no nos_infDoc_infMunDescarga_infCTe_infUnidTransp_lacUnidTransp[] = {
	{ "lacUnidTransp", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 1, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 1, -1, 0, 0, NULL },
	{ "nLacre", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 20, 1, 1, -1, -1, 0, 0, 1, -1, 0, 0, NULL },
};

static const struct nfe_esq mdf_esq_infDoc_infMunDescarga_infCTe_infUnidTransp_lacUnidTransp = { "lacUnidTransp", nos_infDoc_infMunDescarga_infCTe_infUnidTransp_lacUnidTransp, 3, 1, 0 };

static const struct nfe_esq_no nos_infDoc_infMunDescarga_infCTe_infUnidTransp_infUnidCarga_lacUnidCarga[] = {
	{ "lacUnidCarga", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 1, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 1, -1, 0, 0, NULL },
	{ "nLacre", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 20, 1, 1, -1, -1, 0, 0, 1, -1, 0, 0, NULL },
};

static const struct nfe_esq mdf_esq_infDoc_infMunDescarga_infCTe_infUnidTransp_infUnidCarga_lacUnidCarga = { "lacUnidCarga", nos_infDoc_infMunDescarga_infCTe_infUnidTransp_infUnidCarga_lacUnidCarga, 3, 1, 0 };

static const struct nfe_esq_no nos_infDoc_infMunDescarga_infCTe_infUnidTransp_infUnidCarga[] = {
	{ "infUnidCarga", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 3, -1, 0, 1, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 3, -1, 0, 1, NULL },
	{ "tpUnidCarga", ESQ_ELEM, 1, 1, NULL, valores_5, 0, 0, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "idUnidCarga", ESQ_ELEM, 1, 1, "[A-Z0-9]+", NULL, 1, 20, 0, 1, -1, 4, 1, 1, 2, -1, 0, 0, NULL },
	{ "lacUnidCarga", ESQ_LISTA, 0, 0, NULL, NULL, 0, 0, 0, 1, -1, 5, -1, 2, 2, 0, 0, 1, &mdf_esq_infDoc_infMunDescarga_infCTe_infUnidTransp_infUnidCarga_lacUnidCarga },
	{ "qtdRat", ESQ_ELEM, 0, 1, "[0-9]{1,3}(\\.[0-9]{2,3})?", NULL, 0, 0, 0, 1, -1, -1, 2, 2, 3, -1, 1, 1, NULL },
};

static const struct nfe_esq mdf_esq_infDoc_infMunDescarga_infCTe_infUnidTransp_infUnidCarga = { "infUnidCarga", nos_infDoc_infMunDescarga_infCTe_infUnidTransp_infUnidCarga, 6, 3, 1 };

static const struct nfe_esq_no nos_infDoc_infMunDescarga_infCTe_infUnidTransp[] = {
	{ "infUnidTransp", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 3, -1, 0, 2, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 3, -1, 0, 2, NULL },
	{ "tpUnidTransp", ESQ_ELEM, 1, 1, NULL, valores_8, 0, 0, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "idUnidTransp", ESQ_ELEM, 1, 1, "[A-Z0-9]+", NULL, 1, 20, 0, 1, -1, 4, 1, 1, 2, -1, 0, 0, NULL },
	{ "lacUnidTransp", ESQ_LISTA, 0, 0, NULL, NULL, 0, 0, 0, 1, -1, 5, -1, 2, 2, 0, 0, 1, &mdf_esq_infDoc_infMunDescarga_infCTe_infUnidTransp_lacUnidTransp },
	{ "infUnidCarga", ESQ_LISTA, 0, 0, NULL, NULL, 0, 0, 0, 1, -1, 6, -1, 2, 2, 1, 1, 2, &mdf_esq_infDoc_infMunDescarga_infCTe_infUnidTransp_infUnidCarga },
	{ "qtdRat", ESQ_ELEM, 0, 1, "[0-9]{1,3}(\\.[0-9]{2,3})?", NULL, 0, 0, 0, 1, -1, -1, 2, 2, 3, -1, 2, 2, NULL },
};

static const struct nfe_esq mdf_esq_infDoc_infMunDescarga_infCTe_infUnidTransp = { "infUnidTransp", nos_infDoc_infMunDescarga_infCTe_infUnidTransp, 7, 3, 2 };

static const struct nfe_esq_no nos_infDoc_infMunDescarga_infCTe_peri[] = {
	{ "peri", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 6, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 6, -1, 0, 0, NULL },
	{ "nONU", ESQ_ELEM, 1, 1, "[0-9]{4}|ND", NULL, 0, 0, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "xNomeAE", ESQ_ELEM, 0, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 150, 1, 1, -1, 4, 1, 1, 2, -1, 0, 0, NULL },
	{ "xClaRisco", ESQ_ELEM, 0, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 40, 1, 1, -1, 5, 2, 2, 3, -1, 0, 0, NULL },
	{ "grEmb", ESQ_ELEM, 0, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 6, 1, 1, -1, 6, 3, 3, 4, -1, 0, 0, NULL },
	{ "qTotProd", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 20, 1, 1, -1, 7, 4, 4, 5, -1, 0, 0, NULL },
	{ "qVolTipo", ESQ_ELEM, 0, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 60, 1, 1, -1, -1, 5, 5, 6, -1, 0, 0, NULL },
};

static const struct nfe_esq mdf_esq_infDoc_infMunDescarga_infCTe_peri = { "peri", nos_infDoc_infMunDescarga_infCTe_peri, 8, 6, 0 };

static const struct nfe_esq_no nos_infDoc_infMunDescarga_infCTe_infNFePrestParcial[] = {
	{ "infNFePrestParcial", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 1, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 1, -1, 0, 0, NULL },
	{ "chNFe", ESQ_ELEM, 1, 1, "[0-9]{6}[A-Z0-9]{12}[0-9]{26}", NULL, 0, 44, 0, 1, -1, -1, 0, 0, 1, -1, 0, 0, NULL },
};

static const struct nfe_esq mdf_esq_infDoc_infMunDescarga_infCTe_infNFePrestParcial = { "infNFePrestParcial", nos_infDoc_infMunDescarga_infCTe_infNFePrestParcial, 3, 1, 0 };

static const struct nfe_esq_no nos_infDoc_infMunDescarga_infCTe[] = {
	{ "infCTe", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 6, -1, 0, 3, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 6, -1, 0, 3, NULL },
	{ "chCTe", ESQ_ELEM, 1, 1, "[0-9]{6}[A-Z0-9]{12}[0-9]{26}", NULL, 0, 44, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "SegCodBarra", ESQ_ELEM, 0, 1, "[0-9]{36}", NULL, 0, 0, 0, 1, -1, 4, 1, 1, 2, -1, 0, 0, NULL },
	{ "indReentrega", ESQ_ELEM, 0, 1, NULL, valores_7, 0, 0, 0, 1, -1, 5, 2, 2, 3, -1, 0, 0, NULL },
	{ "infUnidTransp", ESQ_LISTA, 0, 0, NULL, NULL, 0, 0, 0, 1, -1, 6, -1, 3, 3, 0, 0, 1, &mdf_esq_infDoc_infMunDescarga_infCTe_infUnidTransp },
	{ "peri", ESQ_LISTA, 0, 0, NULL, NULL, 0, 0, 0, 1, -1, 7, -1, 3, 3, 1, 1, 2, &mdf_esq_infDoc_infMunDescarga_infCTe_peri },
	{ "infEntregaParcial", ESQ_ELEM, 0, 1, NULL, NULL, 0, 0, 0, 1, 8, 11, -1, 3, 5, -1, 2, 2, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 7, 9, -1, -1, 3, 5, -1, 2, 2, NULL },
	{ "qtdTotal", ESQ_ELEM, 1, 1, "0|0\\.[0-9]{4}|[1-9]{1}[0-9]{0,10}(\\.[0-9]{4})?", NULL, 0, 0, 0, 8, -1, 10, 3, 3, 4, -1, 2, 2, NULL },
	{ "qtdParcial", ESQ_ELEM, 1, 1, "0|0\\.[0-9]{4}|[1-9]{1}[0-9]{0,10}(\\.[0-9]{4})?", NULL, 0, 0, 0, 8, -1, -1, 4, 4, 5, -1, 2, 2, NULL },
	{ NULL, ESQ_SEQ, 0, 1, NULL, NULL, 0, 0, 0, 1, 12, -1, -1, 5, 6, -1, 2, 3, NULL },
	{ "indPrestacaoParcial", ESQ_ELEM, 1, 1, NULL, valores_7, 0, 0, 0, 11, -1, 13, 5, 5, 6, -1, 2, 2, NULL },
	{ "infNFePrestParcial", ESQ_LISTA, 1, 0, NULL, NULL, 0, 0, 0, 11, -1, -1, -1, 6, 6, 2, 2, 3, &mdf_esq_infDoc_infMunDescarga_infCTe_infNFePrestParcial },
};

static const struct nfe_esq mdf_esq_infDoc_infMunDescarga_infCTe = { "infCTe", nos_infDoc_infMunDescarga_infCTe, 14, 6, 3 };

static const struct nfe_esq_no nos_infDoc_infMunDescarga_infNFe_infUnidTransp_lacUnidTransp[] = {
	{ "lacUnidTransp", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 1, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 1, -1, 0, 0, NULL },
	{ "nLacre", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 20, 1, 1, -1, -1, 0, 0, 1, -1, 0, 0, NULL },
};

static const struct nfe_esq mdf_esq_infDoc_infMunDescarga_infNFe_infUnidTransp_lacUnidTransp = { "lacUnidTransp", nos_infDoc_infMunDescarga_infNFe_infUnidTransp_lacUnidTransp, 3, 1, 0 };

static const struct nfe_esq_no nos_infDoc_infMunDescarga_infNFe_infUnidTransp_infUnidCarga_lacUnidCarga[] = {
	{ "lacUnidCarga", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 1, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 1, -1, 0, 0, NULL },
	{ "nLacre", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 20, 1, 1, -1, -1, 0, 0, 1, -1, 0, 0, NULL },
};

static const struct nfe_esq mdf_esq_infDoc_infMunDescarga_infNFe_infUnidTransp_infUnidCarga_lacUnidCarga = { "lacUnidCarga", nos_infDoc_infMunDescarga_infNFe_infUnidTransp_infUnidCarga_lacUnidCarga, 3, 1, 0 };

static const struct nfe_esq_no nos_infDoc_infMunDescarga_infNFe_infUnidTransp_infUnidCarga[] = {
	{ "infUnidCarga", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 3, -1, 0, 1, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 3, -1, 0, 1, NULL },
	{ "tpUnidCarga", ESQ_ELEM, 1, 1, NULL, valores_5, 0, 0, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "idUnidCarga", ESQ_ELEM, 1, 1, "[A-Z0-9]+", NULL, 1, 20, 0, 1, -1, 4, 1, 1, 2, -1, 0, 0, NULL },
	{ "lacUnidCarga", ESQ_LISTA, 0, 0, NULL, NULL, 0, 0, 0, 1, -1, 5, -1, 2, 2, 0, 0, 1, &mdf_esq_infDoc_infMunDescarga_infNFe_infUnidTransp_infUnidCarga_lacUnidCarga },
	{ "qtdRat", ESQ_ELEM, 0, 1, "[0-9]{1,3}(\\.[0-9]{2,3})?", NULL, 0, 0, 0, 1, -1, -1, 2, 2, 3, -1, 1, 1, NULL },
};

static const struct nfe_esq mdf_esq_infDoc_infMunDescarga_infNFe_infUnidTransp_infUnidCarga = { "infUnidCarga", nos_infDoc_infMunDescarga_infNFe_infUnidTransp_infUnidCarga, 6, 3, 1 };

static const struct nfe_esq_no nos_infDoc_infMunDescarga_infNFe_infUnidTransp[] = {
	{ "infUnidTransp", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 3, -1, 0, 2, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 3, -1, 0, 2, NULL },
	{ "tpUnidTransp", ESQ_ELEM, 1, 1, NULL, valores_8, 0, 0, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "idUnidTransp", ESQ_ELEM, 1, 1, "[A-Z0-9]+", NULL, 1, 20, 0, 1, -1, 4, 1, 1, 2, -1, 0, 0, NULL },
	{ "lacUnidTransp", ESQ_LISTA, 0, 0, NULL, NULL, 0, 0, 0, 1, -1, 5, -1, 2, 2, 0, 0, 1, &mdf_esq_infDoc_infMunDescarga_infNFe_infUnidTransp_lacUnidTransp },
	{ "infUnidCarga", ESQ_LISTA, 0, 0, NULL, NULL, 0, 0, 0, 1, -1, 6, -1, 2, 2, 1, 1, 2, &mdf_esq_infDoc_infMunDescarga_infNFe_infUnidTransp_infUnidCarga },
	{ "qtdRat", ESQ_ELEM, 0, 1, "[0-9]{1,3}(\\.[0-9]{2,3})?", NULL, 0, 0, 0, 1, -1, -1, 2, 2, 3, -1, 2, 2, NULL },
};

static const struct nfe_esq mdf_esq_infDoc_infMunDescarga_infNFe_infUnidTransp = { "infUnidTransp", nos_infDoc_infMunDescarga_infNFe_infUnidTransp, 7, 3, 2 };

static const struct nfe_esq_no nos_infDoc_infMunDescarga_infNFe_peri[] = {
	{ "peri", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 6, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 6, -1, 0, 0, NULL },
	{ "nONU", ESQ_ELEM, 1, 1, "[0-9]{4}|ND", NULL, 0, 0, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "xNomeAE", ESQ_ELEM, 0, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 150, 1, 1, -1, 4, 1, 1, 2, -1, 0, 0, NULL },
	{ "xClaRisco", ESQ_ELEM, 0, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 40, 1, 1, -1, 5, 2, 2, 3, -1, 0, 0, NULL },
	{ "grEmb", ESQ_ELEM, 0, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 6, 1, 1, -1, 6, 3, 3, 4, -1, 0, 0, NULL },
	{ "qTotProd", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 20, 1, 1, -1, 7, 4, 4, 5, -1, 0, 0, NULL },
	{ "qVolTipo", ESQ_ELEM, 0, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 60, 1, 1, -1, -1, 5, 5, 6, -1, 0, 0, NULL },
};

static const struct nfe_esq mdf_esq_infDoc_infMunDescarga_infNFe_peri = { "peri", nos_infDoc_infMunDescarga_infNFe_peri, 8, 6, 0 };

static const struct nfe_esq_no nos_infDoc_infMunDescarga_infNFe[] = {
	{ "infNFe", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 3, -1, 0, 2, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 3, -1, 0, 2, NULL },
	{ "chNFe", ESQ_ELEM, 1, 1, "[0-9]{6}[A-Z0-9]{12}[0-9]{26}", NULL, 0, 44, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "SegCodBarra", ESQ_ELEM, 0, 1, "[0-9]{36}", NULL, 0, 0, 0, 1, -1, 4, 1, 1, 2, -1, 0, 0, NULL },
	{ "indReentrega", ESQ_ELEM, 0, 1, NULL, valores_7, 0, 0, 0, 1, -1, 5, 2, 2, 3, -1, 0, 0, NULL },
	{ "infUnidTransp", ESQ_LISTA, 0, 0, NULL, NULL, 0, 0, 0, 1, -1, 6, -1, 3, 3, 0, 0, 1, &mdf_esq_infDoc_infMunDescarga_infNFe_infUnidTransp },
	{ "peri", ESQ_LISTA, 0, 0, NULL, NULL, 0, 0, 0, 1, -1, -1, -1, 3, 3, 1, 1, 2, &mdf_esq_infDoc_infMunDescarga_infNFe_peri },
};

static const struct nfe_esq mdf_esq_infDoc_infMunDescarga_infNFe = { "infNFe", nos_infDoc_infMunDescarga_infNFe, 7, 3, 2 };

static const struct nfe_esq_no nos_infDoc_infMunDescarga_infMDFeTransp_infUnidTransp_lacUnidTransp[] = {
	{ "lacUnidTransp", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 1, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 1, -1, 0, 0, NULL },
	{ "nLacre", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 20, 1, 1, -1, -1, 0, 0, 1, -1, 0, 0, NULL },
};

static const struct nfe_esq mdf_esq_infDoc_infMunDescarga_infMDFeTransp_infUnidTransp_lacUnidTransp = { "lacUnidTransp", nos_infDoc_infMunDescarga_infMDFeTransp_infUnidTransp_lacUnidTransp, 3, 1, 0 };

static const struct nfe_esq_no nos_infDoc_infMunDescarga_infMDFeTransp_infUnidTransp_infUnidCarga_lacUnidCarga[] = {
	{ "lacUnidCarga", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 1, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 1, -1, 0, 0, NULL },
	{ "nLacre", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 20, 1, 1, -1, -1, 0, 0, 1, -1, 0, 0, NULL },
};

static const struct nfe_esq mdf_esq_infDoc_infMunDescarga_infMDFeTransp_infUnidTransp_infUnidCarga_lacUnidCarga = { "lacUnidCarga", nos_infDoc_infMunDescarga_infMDFeTransp_infUnidTransp_infUnidCarga_lacUnidCarga, 3, 1, 0 };

static const struct nfe_esq_no nos_infDoc_infMunDescarga_infMDFeTransp_infUnidTransp_infUnidCarga[] = {
	{ "infUnidCarga", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 3, -1, 0, 1, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 3, -1, 0, 1, NULL },
	{ "tpUnidCarga", ESQ_ELEM, 1, 1, NULL, valores_5, 0, 0, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "idUnidCarga", ESQ_ELEM, 1, 1, "[A-Z0-9]+", NULL, 1, 20, 0, 1, -1, 4, 1, 1, 2, -1, 0, 0, NULL },
	{ "lacUnidCarga", ESQ_LISTA, 0, 0, NULL, NULL, 0, 0, 0, 1, -1, 5, -1, 2, 2, 0, 0, 1, &mdf_esq_infDoc_infMunDescarga_infMDFeTransp_infUnidTransp_infUnidCarga_lacUnidCarga },
	{ "qtdRat", ESQ_ELEM, 0, 1, "[0-9]{1,3}(\\.[0-9]{2,3})?", NULL, 0, 0, 0, 1, -1, -1, 2, 2, 3, -1, 1, 1, NULL },
};

static const struct nfe_esq mdf_esq_infDoc_infMunDescarga_infMDFeTransp_infUnidTransp_infUnidCarga = { "infUnidCarga", nos_infDoc_infMunDescarga_infMDFeTransp_infUnidTransp_infUnidCarga, 6, 3, 1 };

static const struct nfe_esq_no nos_infDoc_infMunDescarga_infMDFeTransp_infUnidTransp[] = {
	{ "infUnidTransp", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 3, -1, 0, 2, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 3, -1, 0, 2, NULL },
	{ "tpUnidTransp", ESQ_ELEM, 1, 1, NULL, valores_8, 0, 0, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "idUnidTransp", ESQ_ELEM, 1, 1, "[A-Z0-9]+", NULL, 1, 20, 0, 1, -1, 4, 1, 1, 2, -1, 0, 0, NULL },
	{ "lacUnidTransp", ESQ_LISTA, 0, 0, NULL, NULL, 0, 0, 0, 1, -1, 5, -1, 2, 2, 0, 0, 1, &mdf_esq_infDoc_infMunDescarga_infMDFeTransp_infUnidTransp_lacUnidTransp },
	{ "infUnidCarga", ESQ_LISTA, 0, 0, NULL, NULL, 0, 0, 0, 1, -1, 6, -1, 2, 2, 1, 1, 2, &mdf_esq_infDoc_infMunDescarga_infMDFeTransp_infUnidTransp_infUnidCarga },
	{ "qtdRat", ESQ_ELEM, 0, 1, "[0-9]{1,3}(\\.[0-9]{2,3})?", NULL, 0, 0, 0, 1, -1, -1, 2, 2, 3, -1, 2, 2, NULL },
};

static const struct nfe_esq mdf_esq_infDoc_infMunDescarga_infMDFeTransp_infUnidTransp = { "infUnidTransp", nos_infDoc_infMunDescarga_infMDFeTransp_infUnidTransp, 7, 3, 2 };

static const struct nfe_esq_no nos_infDoc_infMunDescarga_infMDFeTransp_peri[] = {
	{ "peri", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 6, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 6, -1, 0, 0, NULL },
	{ "nONU", ESQ_ELEM, 1, 1, "[0-9]{4}|ND", NULL, 0, 0, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "xNomeAE", ESQ_ELEM, 0, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 150, 1, 1, -1, 4, 1, 1, 2, -1, 0, 0, NULL },
	{ "xClaRisco", ESQ_ELEM, 0, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 40, 1, 1, -1, 5, 2, 2, 3, -1, 0, 0, NULL },
	{ "grEmb", ESQ_ELEM, 0, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 6, 1, 1, -1, 6, 3, 3, 4, -1, 0, 0, NULL },
	{ "qTotProd", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 20, 1, 1, -1, 7, 4, 4, 5, -1, 0, 0, NULL },
	{ "qVolTipo", ESQ_ELEM, 0, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 60, 1, 1, -1, -1, 5, 5, 6, -1, 0, 0, NULL },
};

static const struct nfe_esq mdf_esq_infDoc_infMunDescarga_infMDFeTransp_peri = { "peri", nos_infDoc_infMunDescarga_infMDFeTransp_peri, 8, 6, 0 };

static const struct nfe_esq_no nos_infDoc_infMunDescarga_infMDFeTransp[] = {
	{ "infMDFeTransp", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 2, -1, 0, 2, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 2, -1, 0, 2, NULL },
	{ "chMDFe", ESQ_ELEM, 1, 1, "[0-9]{6}[A-Z0-9]{12}[0-9]{26}", NULL, 0, 44, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "indReentrega", ESQ_ELEM, 0, 1, NULL, valores_7, 0, 0, 0, 1, -1, 4, 1, 1, 2, -1, 0, 0, NULL },
	{ "infUnidTransp", ESQ_LISTA, 0, 0, NULL, NULL, 0, 0, 0, 1, -1, 5, -1, 2, 2, 0, 0, 1, &mdf_esq_infDoc_infMunDescarga_infMDFeTransp_infUnidTransp },
	{ "peri", ESQ_LISTA, 0, 0, NULL, NULL, 0, 0, 0, 1, -1, -1, -1, 2, 2, 1, 1, 2, &mdf_esq_infDoc_infMunDescarga_infMDFeTransp_peri },
};

static const struct nfe_esq mdf_esq_infDoc_infMunDescarga_infMDFeTransp = { "infMDFeTransp", nos_infDoc_infMunDescarga_infMDFeTransp, 6, 2, 2 };

static const struct nfe_esq_no nos_infDoc_infMunDescarga[] = {
	{ "infMunDescarga", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 2, -1, 0, 3, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 2, -1, 0, 3, NULL },
	{ "cMunDescarga", ESQ_ELEM, 1, 1, "[0-9]{7}", NULL, 0, 0, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "xMunDescarga", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 2, 60, 1, 1, -1, 4, 1, 1, 2, -1, 0, 0, NULL },
	{ "infCTe", ESQ_LISTA, 0, 20000, NULL, NULL, 0, 0, 0, 1, -1, 5, -1, 2, 2, 0, 0, 1, &mdf_esq_infDoc_infMunDescarga_infCTe },
	{ "infNFe", ESQ_LISTA, 0, 20000, NULL, NULL, 0, 0, 0, 1, -1, 6, -1, 2, 2, 1, 1, 2, &mdf_esq_infDoc_infMunDescarga_infNFe },
	{ "infMDFeTransp", ESQ_LISTA, 0, 20000, NULL, NULL, 0, 0, 0, 1, -1, -1, -1, 2, 2, 2, 2, 3, &mdf_esq_infDoc_infMunDescarga_infMDFeTransp },
};

static const struct nfe_esq mdf_esq_infDoc_infMunDescarga = { "infMunDescarga", nos_infDoc_infMunDescarga, 7, 2, 3 };

static const struct nfe_esq_no nos_infDoc[] = {
	{ "infDoc", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 0, -1, 0, 1, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 0, -1, 0, 1, NULL },
	{ "infMunDescarga", ESQ_LISTA, 1, 1000, NULL, NULL, 0, 0, 0, 1, -1, -1, -1, 0, 0, 0, 0, 1, &mdf_esq_infDoc_infMunDescarga },
};

const struct nfe_esq mdf_esq_infDoc = { "infDoc", nos_infDoc, 3, 0, 1 };

static const struct nfe_esq_no nos_seg_nAver[] = {
	{ "nAver", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 40, 1, -1, -1, -1, 0, 0, 1, -1, 0, 0, NULL },
};

static const struct nfe_esq mdf_esq_seg_nAver = { "nAver", nos_seg_nAver, 1, 1, 0 };

static const struct nfe_esq_no nos_seg[] = {
	{ "seg", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 6, -1, 0, 1, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 6, -1, 0, 1, NULL },
	{ "infResp", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, 1, 3, 8, -1, 0, 3, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 2, 4, -1, -1, 0, 3, -1, 0, 0, NULL },
	{ "respSeg", ESQ_ELEM, 1, 1, NULL, valores_2, 1, 1, 0, 3, -1, 5, 0, 0, 1, -1, 0, 0, NULL },
	{ NULL, ESQ_CHOICE, 0, 1, NULL, NULL, 0, 0, 0, 3, 6, -1, -1, 1, 3, -1, 0, 0, NULL },
	{ "CNPJ", ESQ_ELEM, 1, 1, "[A-Z0-9]{12}[0-9]{2}", NULL, 0, 0, 0, 5, -1, 7, 1, 1, 2, -1, 0, 0, NULL },
	{ "CPF", ESQ_ELEM, 1, 1, "[0-9]{11}", NULL, 0, 0, 0, 5, -1, -1, 2, 2, 3, -1, 0, 0, NULL },
	{ "infSeg", ESQ_ELEM, 0, 1, NULL, NULL, 0, 0, 0, 1, 9, 12, -1, 3, 5, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 8, 10, -1, -1, 3, 5, -1, 0, 0, NULL },
	{ "xSeg", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 30, 1, 9, -1, 11, 3, 3, 4, -1, 0, 0, NULL },
	{ "CNPJ", ESQ_ELEM, 1, 1, "[0-9]{0}|[A-Z0-9]{12}[0-9]{2}", NULL, 0, 0, 0, 9, -1, -1, 4, 4, 5, -1, 0, 0, NULL },
	{ "nApol", ESQ_ELEM, 0, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 20, 1, 1, -1, 13, 5, 5, 6, -1, 0, 0, NULL },
	{ "nAver", ESQ_LISTA, 0, 0, NULL, NULL, 0, 0, 0, 1, -1, -1, -1, 6, 6, 0, 0, 1, &mdf_esq_seg_nAver },
};

const struct nfe_esq mdf_esq_seg = { "seg", nos_seg, 14, 6, 1 };

static const struct nfe_esq_no nos_prodPred[] = {
	{ "prodPred", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 10, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 10, -1, 0, 0, NULL },
	{ "tpCarga", ESQ_ELEM, 1, 1, NULL, valores_9, 0, 0, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "xProd", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 120, 1, 1, -1, 4, 1, 1, 2, -1, 0, 0, NULL },
	{ "cEAN", ESQ_ELEM, 0, 1, "SEM GTIN|[0-9]{0}|[0-9]{8}|[0-9]{12,14}", NULL, 0, 0, 0, 1, -1, 5, 2, 2, 3, -1, 0, 0, NULL },
	{ "NCM", ESQ_ELEM, 0, 1, "[0-9]{2}|[0-9]{8}", NULL, 0, 0, 0, 1, -1, 6, 3, 3, 4, -1, 0, 0, NULL },
	{ "infLotacao", ESQ_ELEM, 0, 1, NULL, NULL, 0, 0, 0, 1, 7, -1, -1, 4, 10, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 6, 8, -1, -1, 4, 10, -1, 0, 0, NULL },
	{ "infLocalCarrega", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, 7, 9, 14, -1, 4, 7, -1, 0, 0, NULL },
	{ NULL, ESQ_CHOICE, 1, 1, NULL, NULL, 0, 0, 0, 8, 10, -1, -1, 4, 7, -1, 0, 0, NULL },
	{ "CEP", ESQ_ELEM, 1, 1, "[0-9]{8}", NULL, 0, 0, 0, 9, -1, 11, 4, 4, 5, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 9, 12, -1, -1, 5, 7, -1, 0, 0, NULL },
	{ "latitude", ESQ_ELEM, 1, 1, "[0-9]\\.[0-9]{6}|[1-8][0-9]\\.[0-9]{6}|90\\.[0-9]{6}|-[0-9]\\.[0-9]{6}|-[1-8][0-9]\\.[0-9]{6}|-90\\.[0-9]{6}", NULL, 0, 0, 1, 11, -1, 13, 5, 5, 6, -1, 0, 0, NULL },
	{ "longitude", ESQ_ELEM, 1, 1, "[0-9]\\.[0-9]{6}|[1-9][0-9]\\.[0-9]{6}|1[0-7][0-9]\\.[0-9]{6}|180\\.[0-9]{6}|-[0-9]\\.[0-9]{6}|-[1-9][0-9]\\.[0-9]{6}|-1[0-7][0-9]\\.[0-9]{6}|-180\\.[0-9]{6}", NULL, 0, 0, 1, 11, -1, -1, 6, 6, 7, -1, 0, 0, NULL },
	{ "infLocalDescarrega", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, 7, 15, -1, -1, 7, 10, -1, 0, 0, NULL },
	{ NULL, ESQ_CHOICE, 1, 1, NULL, NULL, 0, 0, 0, 14, 16, -1, -1, 7, 10, -1, 0, 0, NULL },
	{ "CEP", ESQ_ELEM, 1, 1, "[0-9]{8}", NULL, 0, 0, 0, 15, -1, 17, 7, 7, 8, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 15, 18, -1, -1, 8, 10, -1, 0, 0, NULL },
	{ "latitude", ESQ_ELEM, 1, 1, "[0-9]\\.[0-9]{6}|[1-8][0-9]\\.[0-9]{6}|90\\.[0-9]{6}|-[0-9]\\.[0-9]{6}|-[1-8][0-9]\\.[0-9]{6}|-90\\.[0-9]{6}", NULL, 0, 0, 1, 17, -1, 19, 8, 8, 9, -1, 0, 0, NULL },
	{ "longitude", ESQ_ELEM, 1, 1, "[0-9]\\.[0-9]{6}|[1-9][0-9]\\.[0-9]{6}|1[0-7][0-9]\\.[0-9]{6}|180\\.[0-9]{6}|-[0-9]\\.[0-9]{6}|-[1-9][0-9]\\.[0-9]{6}|-1[0-7][0-9]\\.[0-9]{6}|-180\\.[0-9]{6}", NULL, 0, 0, 1, 17, -1, -1, 9, 9, 10, -1, 0, 0, NULL },
};

const struct nfe_esq mdf_esq_prodPred = { "prodPred", nos_prodPred, 20, 10, 0 };

static const struct nfe_esq_no nos_tot[] = {
	{ "tot", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 6, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 6, -1, 0, 0, NULL },
	{ "qCTe", ESQ_ELEM, 0, 1, "[0-9]{1,6}", NULL, 0, 0, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "qNFe", ESQ_ELEM, 0, 1, "[0-9]{1,6}", NULL, 0, 0, 0, 1, -1, 4, 1, 1, 2, -1, 0, 0, NULL },
	{ "qMDFe", ESQ_ELEM, 0, 1, "[0-9]{1,6}", NULL, 0, 0, 0, 1, -1, 5, 2, 2, 3, -1, 0, 0, NULL },
	{ "vCarga", ESQ_ELEM, 1, 1, "0|0\\.[0-9]{2}|[1-9]{1}[0-9]{0,12}(\\.[0-9]{2})?", NULL, 0, 0, 0, 1, -1, 6, 3, 3, 4, -1, 0, 0, NULL },
	{ "cUnid", ESQ_ELEM, 1, 1, NULL, valores_10, 0, 0, 0, 1, -1, 7, 4, 4, 5, -1, 0, 0, NULL },
	{ "qCarga", ESQ_ELEM, 1, 1, "0|0\\.[0-9]{4}|[1-9]{1}[0-9]{0,10}(\\.[0-9]{4})?", NULL, 0, 0, 0, 1, -1, -1, 5, 5, 6, -1, 0, 0, NULL },
};

const struct nfe_esq mdf_esq_tot = { "tot", nos_tot, 8, 6, 0 };

static const struct nfe_esq_no nos_lacres[] = {
	{ "lacres", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 1, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 1, -1, 0, 0, NULL },
	{ "nLacre", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 60, 1, 1, -1, -1, 0, 0, 1, -1, 0, 0, NULL },
};

const struct nfe_esq mdf_esq_lacres = { "lacres", nos_lacres, 3, 1, 0 };

static const struct nfe_esq_no nos_autXML[] = {
	{ "autXML", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 2, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 2, -1, 0, 0, NULL },
	{ NULL, ESQ_CHOICE, 1, 1, NULL, NULL, 0, 0, 0, 1, 3, -1, -1, 0, 2, -1, 0, 0, NULL },
	{ "CNPJ", ESQ_ELEM, 1, 1, "[A-Z0-9]{12}[0-9]{2}", NULL, 0, 0, 0, 2, -1, 4, 0, 0, 1, -1, 0, 0, NULL },
	{ "CPF", ESQ_ELEM, 1, 1, "[0-9]{11}", NULL, 0, 0, 0, 2, -1, -1, 1, 1, 2, -1, 0, 0, NULL },
};

const struct nfe_esq mdf_esq_autXML = { "autXML", nos_autXML, 5, 2, 0 };

static const struct nfe_esq_no nos_infAdic[] = {
	{ "infAdic", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 2, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 2, -1, 0, 0, NULL },
	{ "infAdFisco", ESQ_ELEM, 0, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 2000, 1, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "infCpl", ESQ_ELEM, 0, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 5000, 1, 1, -1, -1, 1, 1, 2, -1, 0, 0, NULL },
};

const struct nfe_esq mdf_esq_infAdic = { "infAdic", nos_infAdic, 4, 2, 0 };

static const struct nfe_esq_no nos_infRespTec[] = {
	{ "infRespTec", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 6, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 6, -1, 0, 0, NULL },
	{ "CNPJ", ESQ_ELEM, 1, 1, "[A-Z0-9]{12}[0-9]{2}", NULL, 0, 0, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "xContato", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 2, 60, 1, 1, -1, 4, 1, 1, 2, -1, 0, 0, NULL },
	{ "email", ESQ_ELEM, 1, 1, "[^@]+@[^\\.]+\\..+", NULL, 6, 60, 0, 1, -1, 5, 2, 2, 3, -1, 0, 0, NULL },
	{ "fone", ESQ_ELEM, 1, 1, "[0-9]{7,12}", NULL, 0, 0, 0, 1, -1, 6, 3, 3, 4, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 0, 1, NULL, NULL, 0, 0, 0, 1, 7, -1, -1, 4, 6, -1, 0, 0, NULL },
	{ "idCSRT", ESQ_ELEM, 1, 1, "[0-9]{3}", NULL, 0, 0, 0, 6, -1, 8, 4, 4, 5, -1, 0, 0, NULL },
	{ "hashCSRT", ESQ_ELEM, 1, 1, "[A-Za-z0-9+/]{24}[A-Za-z0-9+/]{3}=", NULL, 0, 0, 0, 6, -1, -1, 5, 5, 6, -1, 0, 0, NULL },
};

const struct nfe_esq mdf_esq_infRespTec = { "infRespTec", nos_infRespTec, 9, 6, 0 };

static const struct nfe_esq_no nos_rodo_infCIOT[] = {
	{ "infCIOT", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 3, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 3, -1, 0, 0, NULL },
	{ "CIOT", ESQ_ELEM, 0, 1, "[0-9]{12}", NULL, 0, 0, 1, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ NULL, ESQ_CHOICE, 1, 1, NULL, NULL, 0, 0, 0, 1, 4, -1, -1, 1, 3, -1, 0, 0, NULL },
	{ "CPF", ESQ_ELEM, 1, 1, "[0-9]{11}", NULL, 0, 0, 0, 3, -1, 5, 1, 1, 2, -1, 0, 0, NULL },
	{ "CNPJ", ESQ_ELEM, 1, 1, "[0-9]{0}|[A-Z0-9]{12}[0-9]{2}", NULL, 0, 0, 0, 3, -1, -1, 2, 2, 3, -1, 0, 0, NULL },
};

static const struct nfe_esq mdf_esq_rodo_infCIOT = { "infCIOT", nos_rodo_infCIOT, 6, 3, 0 };

static const struct nfe_esq_no nos_rodo_disp[] = {
	{ "disp", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 6, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 6, -1, 0, 0, NULL },
	{ "CNPJForn", ESQ_ELEM, 1, 1, "[A-Z0-9]{12}[0-9]{2}", NULL, 0, 0, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ NULL, ESQ_CHOICE, 0, 1, NULL, NULL, 0, 0, 0, 1, 4, 6, -1, 1, 3, -1, 0, 0, NULL },
	{ "CNPJPg", ESQ_ELEM, 1, 1, "[0-9]{0}|[A-Z0-9]{12}[0-9]{2}", NULL, 0, 0, 0, 3, -1, 5, 1, 1, 2, -1, 0, 0, NULL },
	{ "CPFPg", ESQ_ELEM, 1, 1, "[0-9]{11}", NULL, 0, 0, 0, 3, -1, -1, 2, 2, 3, -1, 0, 0, NULL },
	{ "nCompra", ESQ_ELEM, 0, 1, "[0-9]{1,20}", NULL, 0, 0, 0, 1, -1, 7, 3, 3, 4, -1, 0, 0, NULL },
	{ "vValePed", ESQ_ELEM, 1, 1, "0|0\\.[0-9]{2}|[1-9]{1}[0-9]{0,12}(\\.[0-9]{2})?", NULL, 0, 0, 0, 1, -1, 8, 4, 4, 5, -1, 0, 0, NULL },
	{ "tpValePed", ESQ_ELEM, 0, 1, NULL, valores_11, 0, 0, 0, 1, -1, -1, 5, 5, 6, -1, 0, 0, NULL },
};

static const struct nfe_esq mdf_esq_rodo_disp = { "disp", nos_rodo_disp, 9, 6, 0 };

static const struct nfe_esq_no nos_rodo_infContratante[] = {
	{ "infContratante", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 6, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 6, -1, 0, 0, NULL },
	{ "xNome", ESQ_ELEM, 0, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 2, 60, 1, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ NULL, ESQ_CHOICE, 1, 1, NULL, NULL, 0, 0, 0, 1, 4, 7, -1, 1, 4, -1, 0, 0, NULL },
	{ "CPF", ESQ_ELEM, 1, 1, "[0-9]{11}", NULL, 0, 0, 0, 3, -1, 5, 1, 1, 2, -1, 0, 0, NULL },
	{ "CNPJ", ESQ_ELEM, 1, 1, "[A-Z0-9]{12}[0-9]{2}", NULL, 0, 0, 0, 3, -1, 6, 2, 2, 3, -1, 0, 0, NULL },
	{ "idEstrangeiro", ESQ_ELEM, 1, 1, "([!-\xC3\xBF]{0}|[!-\xC3\xBF]{2,20})?", NULL, 2, 20, 0, 3, -1, -1, 3, 3, 4, -1, 0, 0, NULL },
	{ "infContrato", ESQ_ELEM, 0, 1, NULL, NULL, 0, 0, 0, 1, 8, -1, -1, 4, 6, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 7, 9, -1, -1, 4, 6, -1, 0, 0, NULL },
	{ "NroContrato", ESQ_ELEM, 1, 1, NULL, NULL, 2, 20, 0, 8, -1, 10, 4, 4, 5, -1, 0, 0, NULL },
	{ "vContratoGlobal", ESQ_ELEM, 1, 1, "0\\.[0-9]{1}[1-9]{1}|0\\.[1-9]{1}[0-9]{1}|[1-9]{1}[0-9]{0,12}(\\.[0-9]{2})?", NULL, 0, 0, 0, 8, -1, -1, 5, 5, 6, -1, 0, 0, NULL },
};

static const struct nfe_esq mdf_esq_rodo_infContratante = { "infContratante", nos_rodo_infContratante, 11, 6, 0 };

static const struct nfe_esq_no nos_rodo_infPag_Comp[] = {
	{ "Comp", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 3, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 3, -1, 0, 0, NULL },
	{ "tpComp", ESQ_ELEM, 1, 1, NULL, valores_12, 0, 0, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "vComp", ESQ_ELEM, 1, 1, "0|0\\.[0-9]{2}|[1-9]{1}[0-9]{0,12}(\\.[0-9]{2})?", NULL, 0, 0, 0, 1, -1, 4, 1, 1, 2, -1, 0, 0, NULL },
	{ "xComp", ESQ_ELEM, 0, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 2, 60, 1, 1, -1, -1, 2, 2, 3, -1, 0, 0, NULL },
};

static const struct nfe_esq mdf_esq_rodo_infPag_Comp = { "Comp", nos_rodo_infPag_Comp, 5, 3, 0 };

static const struct nfe_esq_no nos_rodo_infPag_infPrazo[] = {
	{ "infPrazo", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 3, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 3, -1, 0, 0, NULL },
	{ "nParcela", ESQ_ELEM, 1, 1, "[0-9]{3}", NULL, 0, 0, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "dVenc", ESQ_ELEM, 1, 1, "(((20(([02468][048])|([13579][26]))-02-29))|(20[0-9][0-9])-((((0[1-9])|(1[0-2]))-((0[1-9])|(1\\d)|(2[0-8])))|((((0[13578])|(1[02]))-31)|(((0[1,3-9])|(1[0-2]))-(29|30)))))", NULL, 0, 0, 0, 1, -1, 4, 1, 1, 2, -1, 0, 0, NULL },
	{ "vParcela", ESQ_ELEM, 1, 1, "0\\.[0-9]{1}[1-9]{1}|0\\.[1-9]{1}[0-9]{1}|[1-9]{1}[0-9]{0,12}(\\.[0-9]{2})?", NULL, 0, 0, 0, 1, -1, -1, 2, 2, 3, -1, 0, 0, NULL },
};

static const struct nfe_esq mdf_esq_rodo_infPag_infPrazo = { "infPrazo", nos_rodo_infPag_infPrazo, 5, 3, 0 };

static const struct nfe_esq_no nos_rodo_infPag[] = {
	{ "infPag", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 14, -1, 0, 2, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 14, -1, 0, 2, NULL },
	{ "xNome", ESQ_ELEM, 0, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 2, 60, 1, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ NULL, ESQ_CHOICE, 1, 1, NULL, NULL, 0, 0, 0, 1, 4, 7, -1, 1, 4, -1, 0, 0, NULL },
	{ "CPF", ESQ_ELEM, 1, 1, "[0-9]{11}", NULL, 0, 0, 0, 3, -1, 5, 1, 1, 2, -1, 0, 0, NULL },
	{ "CNPJ", ESQ_ELEM, 1, 1, "[0-9]{0}|[A-Z0-9]{12}[0-9]{2}", NULL, 0, 0, 0, 3, -1, 6, 2, 2, 3, -1, 0, 0, NULL },
	{ "idEstrangeiro", ESQ_ELEM, 1, 1, "([!-\xC3\xBF]{0}|[!-\xC3\xBF]{5,20})?", NULL, 2, 20, 0, 3, -1, -1, 3, 3, 4, -1, 0, 0, NULL },
	{ "Comp", ESQ_LISTA, 1, 0, NULL, NULL, 0, 0, 0, 1, -1, 8, -1, 4, 4, 0, 0, 1, &mdf_esq_rodo_infPag_Comp },
	{ "vContrato", ESQ_ELEM, 1, 1, "0|0\\.[0-9]{2}|[1-9]{1}[0-9]{0,12}(\\.[0-9]{2})?", NULL, 0, 0, 0, 1, -1, 9, 4, 4, 5, -1, 1, 1, NULL },
	{ "indAltoDesemp", ESQ_ELEM, 0, 1, NULL, valores_7, 0, 0, 0, 1, -1, 10, 5, 5, 6, -1, 1, 1, NULL },
	{ "indPag", ESQ_ELEM, 1, 1, NULL, valores_13, 0, 0, 0, 1, -1, 11, 6, 6, 7, -1, 1, 1, NULL },
	{ "vAdiant", ESQ_ELEM, 0, 1, "0|0\\.[0-9]{2}|[1-9]{1}[0-9]{0,12}(\\.[0-9]{2})?", NULL, 0, 0, 0, 1, -1, 12, 7, 7, 8, -1, 1, 1, NULL },
	{ "indAntecipaAdiant", ESQ_ELEM, 0, 1, NULL, valores_7, 0, 0, 0, 1, -1, 13, 8, 8, 9, -1, 1, 1, NULL },
	{ "infPrazo", ESQ_LISTA, 0, 0, NULL, NULL, 0, 0, 0, 1, -1, 14, -1, 9, 9, 1, 1, 2, &mdf_esq_rodo_infPag_infPrazo },
	{ "tpAntecip", ESQ_ELEM, 0, 1, NULL, valores_14, 0, 0, 0, 1, -1, 15, 9, 9, 10, -1, 2, 2, NULL },
	{ "infBanc", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, 1, 16, -1, -1, 10, 14, -1, 2, 2, NULL },
	{ NULL, ESQ_CHOICE, 1, 1, NULL, NULL, 0, 0, 0, 15, 17, -1, -1, 10, 14, -1, 2, 2, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 16, 18, 20, -1, 10, 12, -1, 2, 2, NULL },
	{ "codBanco", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 3, 5, 1, 17, -1, 19, 10, 10, 11, -1, 2, 2, NULL },
	{ "codAgencia", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 10, 1, 17, -1, -1, 11, 11, 12, -1, 2, 2, NULL },
	{ "CNPJIPEF", ESQ_ELEM, 1, 1, "[0-9]{0}|[A-Z0-9]{12}[0-9]{2}", NULL, 0, 0, 0, 16, -1, 21, 12, 12, 13, -1, 2, 2, NULL },
	{ "PIX", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 2, 60, 1, 16, -1, -1, 13, 13, 14, -1, 2, 2, NULL },
};

static const struct nfe_esq mdf_esq_rodo_infPag = { "infPag", nos_rodo_infPag, 22, 14, 2 };

static const struct nfe_esq_no nos_rodo_condutor[] = {
	{ "condutor", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 2, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 2, -1, 0, 0, NULL },
	{ "xNome", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 2, 60, 1, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "CPF", ESQ_ELEM, 1, 1, "[0-9]{11}", NULL, 0, 0, 0, 1, -1, -1, 1, 1, 2, -1, 0, 0, NULL },
};

static const struct nfe_esq mdf_esq_rodo_condutor = { "condutor", nos_rodo_condutor, 4, 2, 0 };

static const struct nfe_esq_no nos_rodo_veicReboque[] = {
	{ "veicReboque", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 15, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 15, -1, 0, 0, NULL },
	{ "cInt", ESQ_ELEM, 0, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 10, 1, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "placa", ESQ_ELEM, 1, 1, "[A-Z]{2,3}[0-9]{4}|[A-Z]{3,4}[0-9]{3}|[A-Z0-9]{7}", NULL, 0, 0, 0, 1, -1, 4, 1, 1, 2, -1, 0, 0, NULL },
	{ "RENAVAM", ESQ_ELEM, 0, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 9, 11, 1, 1, -1, 5, 2, 2, 3, -1, 0, 0, NULL },
	{ "tara", ESQ_ELEM, 1, 1, "0|[1-9]{1}[0-9]{0,5}", NULL, 0, 0, 0, 1, -1, 6, 3, 3, 4, -1, 0, 0, NULL },
	{ "capKG", ESQ_ELEM, 1, 1, "0|[1-9]{1}[0-9]{0,5}", NULL, 0, 0, 0, 1, -1, 7, 4, 4, 5, -1, 0, 0, NULL },
	{ "capM3", ESQ_ELEM, 0, 1, "0|[1-9]{1}[0-9]{0,2}", NULL, 0, 0, 0, 1, -1, 8, 5, 5, 6, -1, 0, 0, NULL },
	{ "prop", ESQ_ELEM, 0, 1, NULL, NULL, 0, 0, 0, 1, 9, 19, -1, 6, 13, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 8, 10, -1, -1, 6, 13, -1, 0, 0, NULL },
	{ NULL, ESQ_CHOICE, 1, 1, NULL, NULL, 0, 0, 0, 9, 11, 13, -1, 6, 8, -1, 0, 0, NULL },
	{ "CPF", ESQ_ELEM, 1, 1, "[0-9]{11}", NULL, 0, 0, 0, 10, -1, 12, 6, 6, 7, -1, 0, 0, NULL },
	{ "CNPJ", ESQ_ELEM, 1, 1, "[0-9]{0}|[A-Z0-9]{12}[0-9]{2}", NULL, 0, 0, 0, 10, -1, -1, 7, 7, 8, -1, 0, 0, NULL },
	{ "RNTRC", ESQ_ELEM, 1, 1, "[0-9]{8}", NULL, 0, 0, 1, 9, -1, 14, 8, 8, 9, -1, 0, 0, NULL },
	{ "xNome", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 60, 1, 9, -1, 15, 9, 9, 10, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 0, 1, NULL, NULL, 0, 0, 0, 9, 16, 18, -1, 10, 12, -1, 0, 0, NULL },
	{ "IE", ESQ_ELEM, 1, 1, "[0-9]{0,14}|ISENTO|PR[0-9]{4,8}", NULL, 0, 0, 0, 15, -1, 17, 10, 10, 11, -1, 0, 0, NULL },
	{ "UF", ESQ_ELEM, 1, 1, NULL, valores_0, 0, 0, 0, 15, -1, -1, 11, 11, 12, -1, 0, 0, NULL },
	{ "tpProp", ESQ_ELEM, 1, 1, NULL, valores_14, 0, 0, 0, 9, -1, -1, 12, 12, 13, -1, 0, 0, NULL },
	{ "tpCar", ESQ_ELEM, 1, 1, NULL, valores_15, 0, 0, 0, 1, -1, 20, 13, 13, 14, -1, 0, 0, NULL },
	{ "UF", ESQ_ELEM, 0, 1, NULL, valores_0, 0, 0, 0, 1, -1, -1, 14, 14, 15, -1, 0, 0, NULL },
};

static const struct nfe_esq mdf_esq_rodo_veicReboque = { "veicReboque", nos_rodo_veicReboque, 21, 15, 0 };

static const struct nfe_esq_no nos_rodo_lacRodo[] = {
	{ "lacRodo", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 1, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 1, -1, 0, 0, NULL },
	{ "nLacre", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 20, 1, 1, -1, -1, 0, 0, 1, -1, 0, 0, NULL },
};

static const struct nfe_esq mdf_esq_rodo_lacRodo = { "lacRodo", nos_rodo_lacRodo, 3, 1, 0 };

static const struct nfe_esq_no nos_rodo[] = {
	{ "rodo", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 19, -1, 0, 7, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 19, -1, 0, 7, NULL },
	{ "infANTT", ESQ_ELEM, 0, 1, NULL, NULL, 0, 0, 0, 1, 3, 12, -1, 0, 2, -1, 0, 4, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 2, 4, -1, -1, 0, 2, -1, 0, 4, NULL },
	{ "RNTRC", ESQ_ELEM, 0, 1, "[0-9]{8}", NULL, 0, 0, 1, 3, -1, 5, 0, 0, 1, -1, 0, 0, NULL },
	{ "infCIOT", ESQ_LISTA, 0, 0, NULL, NULL, 0, 0, 0, 3, -1, 6, -1, 1, 1, 0, 0, 1, &mdf_esq_rodo_infCIOT },
	{ "valePed", ESQ_ELEM, 0, 1, NULL, NULL, 0, 0, 0, 3, 7, 10, -1, 1, 2, -1, 1, 2, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 6, 8, -1, -1, 1, 2, -1, 1, 2, NULL },
	{ "disp", ESQ_LISTA, 1, 0, NULL, NULL, 0, 0, 0, 7, -1, 9, -1, 1, 1, 1, 1, 2, &mdf_esq_rodo_disp },
	{ "categCombVeic", ESQ_ELEM, 0, 1, NULL, valores_16, 0, 0, 0, 7, -1, -1, 1, 1, 2, -1, 2, 2, NULL },
	{ "infContratante", ESQ_LISTA, 0, 0, NULL, NULL, 0, 0, 0, 3, -1, 11, -1, 2, 2, 2, 2, 3, &mdf_esq_rodo_infContratante },
	{ "infPag", ESQ_LISTA, 0, 0, NULL, NULL, 0, 0, 0, 3, -1, -1, -1, 2, 2, 3, 3, 4, &mdf_esq_rodo_infPag },
	{ "veicTracao", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, 1, 13, 35, -1, 2, 18, -1, 4, 5, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 12, 14, -1, -1, 2, 18, -1, 4, 5, NULL },
	{ "cInt", ESQ_ELEM, 0, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 10, 1, 13, -1, 15, 2, 2, 3, -1, 4, 4, NULL },
	{ "placa", ESQ_ELEM, 1, 1, "[A-Z]{2,3}[0-9]{4}|[A-Z]{3,4}[0-9]{3}|[A-Z0-9]{7}", NULL, 0, 0, 0, 13, -1, 16, 3, 3, 4, -1, 4, 4, NULL },
	{ "RENAVAM", ESQ_ELEM, 0, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 9, 11, 1, 13, -1, 17, 4, 4, 5, -1, 4, 4, NULL },
	{ "tara", ESQ_ELEM, 1, 1, "0|[1-9]{1}[0-9]{0,5}", NULL, 0, 0, 0, 13, -1, 18, 5, 5, 6, -1, 4, 4, NULL },
	{ "capKG", ESQ_ELEM, 0, 1, "0|[1-9]{1}[0-9]{0,5}", NULL, 0, 0, 0, 13, -1, 19, 6, 6, 7, -1, 4, 4, NULL },
	{ "capM3", ESQ_ELEM, 0, 1, "0|[1-9]{1}[0-9]{0,2}", NULL, 0, 0, 0, 13, -1, 20, 7, 7, 8, -1, 4, 4, NULL },
	{ "prop", ESQ_ELEM, 0, 1, NULL, NULL, 0, 0, 0, 13, 21, 31, -1, 8, 15, -1, 4, 4, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 20, 22, -1, -1, 8, 15, -1, 4, 4, NULL },
	{ NULL, ESQ_CHOICE, 1, 1, NULL, NULL, 0, 0, 0, 21, 23, 25, -1, 8, 10, -1, 4, 4, NULL },
	{ "CPF", ESQ_ELEM, 1, 1, "[0-9]{11}", NULL, 0, 0, 0, 22, -1, 24, 8, 8, 9, -1, 4, 4, NULL },
	{ "CNPJ", ESQ_ELEM, 1, 1, "[0-9]{0}|[A-Z0-9]{12}[0-9]{2}", NULL, 0, 0, 0, 22, -1, -1, 9, 9, 10, -1, 4, 4, NULL },
	{ "RNTRC", ESQ_ELEM, 1, 1, "[0-9]{8}", NULL, 0, 0, 1, 21, -1, 26, 10, 10, 11, -1, 4, 4, NULL },
	{ "xNome", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 2, 60, 1, 21, -1, 27, 11, 11, 12, -1, 4, 4, NULL },
	{ NULL, ESQ_SEQ, 0, 1, NULL, NULL, 0, 0, 0, 21, 28, 30, -1, 12, 14, -1, 4, 4, NULL },
	{ "IE", ESQ_ELEM, 1, 1, "[0-9]{0,14}|ISENTO|PR[0-9]{4,8}", NULL, 0, 0, 0, 27, -1, 29, 12, 12, 13, -1, 4, 4, NULL },
	{ "UF", ESQ_ELEM, 1, 1, NULL, valores_0, 0, 0, 0, 27, -1, -1, 13, 13, 14, -1, 4, 4, NULL },
	{ "tpProp", ESQ_ELEM, 1, 1, NULL, valores_14, 0, 0, 0, 21, -1, -1, 14, 14, 15, -1, 4, 4, NULL },
	{ "condutor", ESQ_LISTA, 1, 10, NULL, NULL, 0, 0, 0, 13, -1, 32, -1, 15, 15, 4, 4, 5, &mdf_esq_rodo_condutor },
	{ "tpRod", ESQ_ELEM, 1, 1, NULL, valores_17, 0, 0, 0, 13, -1, 33, 15, 15, 16, -1, 5, 5, NULL },
	{ "tpCar", ESQ_ELEM, 1, 1, NULL, valores_15, 0, 0, 0, 13, -1, 34, 16, 16, 17, -1, 5, 5, NULL },
	{ "UF", ESQ_ELEM, 0, 1, NULL, valores_0, 0, 0, 0, 13, -1, -1, 17, 17, 18, -1, 5, 5, NULL },
	{ "veicReboque", ESQ_LISTA, 0, 3, NULL, NULL, 0, 0, 0, 1, -1, 36, -1, 18, 18, 5, 5, 6, &mdf_esq_rodo_veicReboque },
	{ "codAgPorto", ESQ_ELEM, 0, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 0, 16, 1, 1, -1, 37, 18, 18, 19, -1, 6, 6, NULL },
	{ "lacRodo", ESQ_LISTA, 0, 0, NULL, NULL, 0, 0, 0, 1, -1, -1, -1, 19, 19, 6, 6, 7, &mdf_esq_rodo_lacRodo },
};

const struct nfe_esq mdf_esq_rodo = { "rodo", nos_rodo, 38, 19, 7 };

static const struct nfe_esq_no nos_evCancMDFe[] = {
	{ "evCancMDFe", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 3, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 3, -1, 0, 0, NULL },
	{ "descEvento", ESQ_ELEM, 1, 1, NULL, valores_18, 0, 0, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "nProt", ESQ_ELEM, 1, 1, "[0-9]{15}", NULL, 0, 0, 0, 1, -1, 4, 1, 1, 2, -1, 0, 0, NULL },
	{ "xJust", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 15, 255, 1, 1, -1, -1, 2, 2, 3, -1, 0, 0, NULL },
};

const struct nfe_esq mdf_esq_evCancMDFe = { "evCancMDFe", nos_evCancMDFe, 5, 3, 0 };

static const struct nfe_esq_no nos_evEncMDFe[] = {
	{ "evEncMDFe", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 6, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 6, -1, 0, 0, NULL },
	{ "descEvento", ESQ_ELEM, 1, 1, NULL, valores_19, 0, 0, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "nProt", ESQ_ELEM, 1, 1, "[0-9]{15}", NULL, 0, 0, 0, 1, -1, 4, 1, 1, 2, -1, 0, 0, NULL },
	{ "dtEnc", ESQ_ELEM, 1, 1, "(((20(([02468][048])|([13579][26]))-02-29))|(20[0-9][0-9])-((((0[1-9])|(1[0-2]))-((0[1-9])|(1\\d)|(2[0-8])))|((((0[13578])|(1[02]))-31)|(((0[1,3-9])|(1[0-2]))-(29|30)))))", NULL, 0, 0, 0, 1, -1, 5, 2, 2, 3, -1, 0, 0, NULL },
	{ "cUF", ESQ_ELEM, 1, 1, NULL, valores_20, 0, 0, 0, 1, -1, 6, 3, 3, 4, -1, 0, 0, NULL },
	{ "cMun", ESQ_ELEM, 1, 1, "[0-9]{7}", NULL, 0, 0, 0, 1, -1, 7, 4, 4, 5, -1, 0, 0, NULL },
	{ "indEncPorTerceiro", ESQ_ELEM, 0, 1, NULL, valores_7, 0, 0, 0, 1, -1, -1, 5, 5, 6, -1, 0, 0, NULL },
};

const struct nfe_esq mdf_esq_evEncMDFe = { "evEncMDFe", nos_evEncMDFe, 8, 6, 0 };

static const struct nfe_esq_no nos_evIncCondutorMDFe[] = {
	{ "evIncCondutorMDFe", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 3, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 3, -1, 0, 0, NULL },
	{ "descEvento", ESQ_ELEM, 1, 1, NULL, valores_21, 0, 0, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "condutor", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, 1, 4, -1, -1, 1, 3, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 3, 5, -1, -1, 1, 3, -1, 0, 0, NULL },
	{ "xNome", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 2, 60, 1, 4, -1, 6, 1, 1, 2, -1, 0, 0, NULL },
	{ "CPF", ESQ_ELEM, 1, 1, "[0-9]{11}", NULL, 0, 0, 0, 4, -1, -1, 2, 2, 3, -1, 0, 0, NULL },
};

const struct nfe_esq mdf_esq_evIncCondutorMDFe = { "evIncCondutorMDFe", nos_evIncCondutorMDFe, 7, 3, 0 };

static const struct nfe_esq_no nos_evIncDFeMDFe_infDoc[] = {
	{ "infDoc", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 3, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 3, -1, 0, 0, NULL },
	{ "cMunDescarga", ESQ_ELEM, 1, 1, "[0-9]{7}", NULL, 0, 0, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "xMunDescarga", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 2, 60, 1, 1, -1, 4, 1, 1, 2, -1, 0, 0, NULL },
	{ "chNFe", ESQ_ELEM, 1, 1, "[0-9]{6}[A-Z0-9]{12}[0-9]{26}", NULL, 0, 44, 0, 1, -1, -1, 2, 2, 3, -1, 0, 0, NULL },
};

static const struct nfe_esq mdf_esq_evIncDFeMDFe_infDoc = { "infDoc", nos_evIncDFeMDFe_infDoc, 5, 3, 0 };

static const struct nfe_esq_no nos_evIncDFeMDFe[] = {
	{ "evIncDFeMDFe", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 4, -1, 0, 1, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 4, -1, 0, 1, NULL },
	{ "descEvento", ESQ_ELEM, 1, 1, NULL, valores_22, 0, 0, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "nProt", ESQ_ELEM, 1, 1, "[0-9]{15}", NULL, 0, 0, 0, 1, -1, 4, 1, 1, 2, -1, 0, 0, NULL },
	{ "cMunCarrega", ESQ_ELEM, 1, 1, "[0-9]{7}", NULL, 0, 0, 0, 1, -1, 5, 2, 2, 3, -1, 0, 0, NULL },
	{ "xMunCarrega", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 2, 60, 1, 1, -1, 6, 3, 3, 4, -1, 0, 0, NULL },
	{ "infDoc", ESQ_LISTA, 1, 0, NULL, NULL, 0, 0, 0, 1, -1, -1, -1, 4, 4, 0, 0, 1, &mdf_esq_evIncDFeMDFe_infDoc },
};

const struct nfe_esq mdf_esq_evIncDFeMDFe = { "evIncDFeMDFe", nos_evIncDFeMDFe, 7, 4, 1 };

static const struct nfe_esq_no nos_evPagtoOperMDFe_infPag_Comp[] = {
	{ "Comp", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 3, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 3, -1, 0, 0, NULL },
	{ "tpComp", ESQ_ELEM, 1, 1, NULL, valores_12, 0, 0, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "vComp", ESQ_ELEM, 1, 1, "0|0\\.[0-9]{2}|[1-9]{1}[0-9]{0,12}(\\.[0-9]{2})?", NULL, 0, 0, 0, 1, -1, 4, 1, 1, 2, -1, 0, 0, NULL },
	{ "xComp", ESQ_ELEM, 0, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 2, 60, 1, 1, -1, -1, 2, 2, 3, -1, 0, 0, NULL },
};

static const struct nfe_esq mdf_esq_evPagtoOperMDFe_infPag_Comp = { "Comp", nos_evPagtoOperMDFe_infPag_Comp, 5, 3, 0 };

static const struct nfe_esq_no nos_evPagtoOperMDFe_infPag_infPrazo[] = {
	{ "infPrazo", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 3, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 3, -1, 0, 0, NULL },
	{ "nParcela", ESQ_ELEM, 1, 1, "[0-9]{3}", NULL, 0, 0, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "dVenc", ESQ_ELEM, 1, 1, "(((20(([02468][048])|([13579][26]))-02-29))|(20[0-9][0-9])-((((0[1-9])|(1[0-2]))-((0[1-9])|(1\\d)|(2[0-8])))|((((0[13578])|(1[02]))-31)|(((0[1,3-9])|(1[0-2]))-(29|30)))))", NULL, 0, 0, 0, 1, -1, 4, 1, 1, 2, -1, 0, 0, NULL },
	{ "vParcela", ESQ_ELEM, 1, 1, "0\\.[0-9]{1}[1-9]{1}|0\\.[1-9]{1}[0-9]{1}|[1-9]{1}[0-9]{0,12}(\\.[0-9]{2})?", NULL, 0, 0, 0, 1, -1, -1, 2, 2, 3, -1, 0, 0, NULL },
};

static const struct nfe_esq mdf_esq_evPagtoOperMDFe_infPag_infPrazo = { "infPrazo", nos_evPagtoOperMDFe_infPag_infPrazo, 5, 3, 0 };

static const struct nfe_esq_no nos_evPagtoOperMDFe_infPag[] = {
	{ "infPag", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 13, -1, 0, 2, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 13, -1, 0, 2, NULL },
	{ "xNome", ESQ_ELEM, 0, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 2, 60, 1, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ NULL, ESQ_CHOICE, 1, 1, NULL, NULL, 0, 0, 0, 1, 4, 7, -1, 1, 4, -1, 0, 0, NULL },
	{ "CPF", ESQ_ELEM, 1, 1, "[0-9]{11}", NULL, 0, 0, 0, 3, -1, 5, 1, 1, 2, -1, 0, 0, NULL },
	{ "CNPJ", ESQ_ELEM, 1, 1, "[0-9]{0}|[A-Z0-9]{12}[0-9]{2}", NULL, 0, 0, 0, 3, -1, 6, 2, 2, 3, -1, 0, 0, NULL },
	{ "idEstrangeiro", ESQ_ELEM, 1, 1, "([!-\xC3\xBF]{0}|[!-\xC3\xBF]{5,20})?", NULL, 2, 20, 0, 3, -1, -1, 3, 3, 4, -1, 0, 0, NULL },
	{ "Comp", ESQ_LISTA, 1, 0, NULL, NULL, 0, 0, 0, 1, -1, 8, -1, 4, 4, 0, 0, 1, &mdf_esq_evPagtoOperMDFe_infPag_Comp },
	{ "vContrato", ESQ_ELEM, 1, 1, "0|0\\.[0-9]{2}|[1-9]{1}[0-9]{0,12}(\\.[0-9]{2})?", NULL, 0, 0, 0, 1, -1, 9, 4, 4, 5, -1, 1, 1, NULL },
	{ "indPag", ESQ_ELEM, 1, 1, NULL, valores_13, 0, 0, 0, 1, -1, 10, 5, 5, 6, -1, 1, 1, NULL },
	{ "vAdiant", ESQ_ELEM, 0, 1, "0|0\\.[0-9]{2}|[1-9]{1}[0-9]{0,12}(\\.[0-9]{2})?", NULL, 0, 0, 0, 1, -1, 11, 6, 6, 7, -1, 1, 1, NULL },
	{ "indAntecipaAdiant", ESQ_ELEM, 0, 1, NULL, valores_7, 0, 0, 0, 1, -1, 12, 7, 7, 8, -1, 1, 1, NULL },
	{ "infPrazo", ESQ_LISTA, 0, 0, NULL, NULL, 0, 0, 0, 1, -1, 13, -1, 8, 8, 1, 1, 2, &mdf_esq_evPagtoOperMDFe_infPag_infPrazo },
	{ "tpAntecip", ESQ_ELEM, 0, 1, NULL, valores_14, 0, 0, 0, 1, -1, 14, 8, 8, 9, -1, 2, 2, NULL },
	{ "infBanc", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, 1, 15, -1, -1, 9, 13, -1, 2, 2, NULL },
	{ NULL, ESQ_CHOICE, 1, 1, NULL, NULL, 0, 0, 0, 14, 16, -1, -1, 9, 13, -1, 2, 2, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 15, 17, 19, -1, 9, 11, -1, 2, 2, NULL },
	{ "codBanco", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 3, 5, 1, 16, -1, 18, 9, 9, 10, -1, 2, 2, NULL },
	{ "codAgencia", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 1, 10, 1, 16, -1, -1, 10, 10, 11, -1, 2, 2, NULL },
	{ "CNPJIPEF", ESQ_ELEM, 1, 1, "[0-9]{0}|[A-Z0-9]{12}[0-9]{2}", NULL, 0, 0, 0, 15, -1, 20, 11, 11, 12, -1, 2, 2, NULL },
	{ "PIX", ESQ_ELEM, 1, 1, "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}", NULL, 2, 60, 1, 15, -1, -1, 12, 12, 13, -1, 2, 2, NULL },
};

static const struct nfe_esq mdf_esq_evPagtoOperMDFe_infPag = { "infPag", nos_evPagtoOperMDFe_infPag, 21, 13, 2 };

static const struct nfe_esq_no nos_evPagtoOperMDFe[] = {
	{ "evPagtoOperMDFe", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, -1, 1, -1, -1, 0, 4, -1, 0, 1, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 0, 2, -1, -1, 0, 4, -1, 0, 1, NULL },
	{ "descEvento", ESQ_ELEM, 1, 1, NULL, valores_23, 0, 0, 0, 1, -1, 3, 0, 0, 1, -1, 0, 0, NULL },
	{ "nProt", ESQ_ELEM, 1, 1, "[0-9]{15}", NULL, 0, 0, 0, 1, -1, 4, 1, 1, 2, -1, 0, 0, NULL },
	{ "infViagens", ESQ_ELEM, 1, 1, NULL, NULL, 0, 0, 0, 1, 5, 8, -1, 2, 4, -1, 0, 0, NULL },
	{ NULL, ESQ_SEQ, 1, 1, NULL, NULL, 0, 0, 0, 4, 6, -1, -1, 2, 4, -1, 0, 0, NULL },
	{ "qtdViagens", ESQ_ELEM, 1, 1, "[0-9]{5}", NULL, 0, 0, 0, 5, -1, 7, 2, 2, 3, -1, 0, 0, NULL },
	{ "nroViagem", ESQ_ELEM, 1, 1, "[0-9]{5}", NULL, 0, 0, 0, 5, -1, -1, 3, 3, 4, -1, 0, 0, NULL },
	{ "infPag", ESQ_LISTA, 1, 0, NULL, NULL, 0, 0, 0, 1, -1, -1, -1, 4, 4, 0, 0, 1, &mdf_esq_evPagtoOperMDFe_infPag },
};

const struct nfe_esq mdf_esq_evPagtoOperMDFe = { "evPagtoOperMDFe", nos_evPagtoOperMDFe, 9, 4, 1 };

/* clang-format on */
