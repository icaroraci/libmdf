/* Gerado por tools/gerar_padroes.py a partir de tests/schemas/mdfe.
 * Não edite à mão: rode `python3 "$(pkg-config --variable=ferramentas libnfe)/gerar_padroes.py" --config tools/documento.json`.
 *
 * Padrões (MDF_PADRAO_*) na sintaxe de expressões regulares do XML Schema,
 * já ancorados ao valor inteiro; use com nfe_valida_padrao() (valida.h). */

#ifndef LIBMDF_PADROES_H
#define LIBMDF_PADROES_H

/* clang-format off */
/* TDateTimeUTC (base xs:string) */
#define MDF_PADRAO_TDateTimeUTC "(((20(([02468][048])|([13579][26]))-02-29))|(20[0-9][0-9])-((((0[1-9])|(1[0-2]))-((0[1-9])|(1\\d)|(2[0-8])))|((((0[13578])|(1[02]))-31)|(((0[1,3-9])|(1[0-2]))-(29|30)))))T(20|21|22|23|[0-1]\\d):[0-5]\\d:[0-5]\\d([\\-,\\+](0[0-9]|10|11):00|([\\+](12):00))"

/* TCodUfIBGE (base xs:string) */
#define MDF_VALORES_TCodUfIBGE "11", "12", "13", "14", "15", "16", "17", "21", "22", "23", "24", "25", "26", "27", "28", "29", "31", "32", "33", "35", "41", "42", "43", "50", "51", "52", "53"

/* TCodMunIBGE (base xs:string) */
#define MDF_PADRAO_TCodMunIBGE "[0-9]{7}"

/* TCOrgaoIBGE (base xs:string) */
#define MDF_VALORES_TCOrgaoIBGE "11", "12", "13", "14", "15", "16", "17", "21", "22", "23", "24", "25", "26", "27", "28", "29", "31", "32", "33", "35", "41", "42", "43", "50", "51", "52", "53", "90", "91", "92", "93", "94"

/* TCodUfIBGE_EX (base xs:string) */
#define MDF_VALORES_TCodUfIBGE_EX "11", "12", "13", "14", "15", "16", "17", "21", "22", "23", "24", "25", "26", "27", "28", "29", "31", "32", "33", "35", "41", "42", "43", "50", "51", "52", "53", "99"

/* TChCTe (base xs:string) */
#define MDF_PADRAO_TChCTe "[0-9]{6}[A-Z0-9]{12}[0-9]{26}"
#define MDF_TAM_MAX_TChCTe 44

/* TChNFe (base xs:string) */
#define MDF_PADRAO_TChNFe "[0-9]{6}[A-Z0-9]{12}[0-9]{26}"
#define MDF_TAM_MAX_TChNFe 44

/* TChMDFe (base xs:string) */
#define MDF_PADRAO_TChMDFe "[0-9]{6}[A-Z0-9]{12}[0-9]{26}"
#define MDF_TAM_MAX_TChMDFe 44

/* TSegCodBarra (base xs:string) */
#define MDF_PADRAO_TSegCodBarra "[0-9]{36}"

/* TProt (base xs:string) */
#define MDF_PADRAO_TProt "[0-9]{15}"

/* TRec (base xs:string) */
#define MDF_PADRAO_TRec "[0-9]{15}"

/* TStat (base xs:string) */
#define MDF_PADRAO_TStat "[0-9]{3,4}"

/* TCnpj (base xs:string) */
#define MDF_PADRAO_TCnpj "[A-Z0-9]{12}[0-9]{2}"

/* TCnpjOpc (base xs:string) */
#define MDF_PADRAO_TCnpjOpc "[0-9]{0}|[A-Z0-9]{12}[0-9]{2}"

/* TCpf (base xs:string) */
#define MDF_PADRAO_TCpf "[0-9]{11}"

/* TCpfVar (base xs:string) */
#define MDF_PADRAO_TCpfVar "[0-9]{3,11}"

/* TDec_0302 (base xs:string) */
#define MDF_PADRAO_TDec_0302 "0|0\\.[0-9]{2}|[1-9]{1}[0-9]{0,2}(\\.[0-9]{2})?"

/* TDec_0303 (base xs:string) */
#define MDF_PADRAO_TDec_0303 "0|0\\.[0-9]{2}|[1-9]{1}[0-9]{0,2}(\\.[0-9]{3})?"

/* TDec_0302Opc (base xs:string) */
#define MDF_PADRAO_TDec_0302Opc "0\\.[0-9]{1}[1-9]{1}|0\\.[1-9]{1}[0-9]{1}|[1-9]{1}[0-9]{0,2}(\\.[0-9]{2})?"

/* TDec_0302_0303 (base xs:string) */
#define MDF_PADRAO_TDec_0302_0303 "[0-9]{1,3}(\\.[0-9]{2,3})?"

/* TDec_0803 (base xs:string) */
#define MDF_PADRAO_TDec_0803 "0|0\\.[0-9]{3}|[1-9]{1}[0-9]{0,7}(\\.[0-9]{3})?"

/* TDec_0803Opc (base xs:string) */
#define MDF_PADRAO_TDec_0803Opc "0\\.[1-9]{1}[0-9]{2}|0\\.[0-9]{2}[1-9]{1}|0\\.[0-9]{1}[1-9]{1}[0-9]{1}|[1-9]{1}[0-9]{0,7}(\\.[0-9]{3})?"

/* TDec_0804 (base xs:string) */
#define MDF_PADRAO_TDec_0804 "0|0\\.[0-9]{4}|[1-9]{1}[0-9]{0,7}(\\.[0-9]{4})?"

/* TDec_0804Opc (base xs:string) */
#define MDF_PADRAO_TDec_0804Opc "0\\.[1-9]{1}[0-9]{3}|0\\.[0-9]{3}[1-9]{1}|0\\.[0-9]{2}[1-9]{1}[0-9]{1}|0\\.[0-9]{1}[1-9]{1}[0-9]{2}|[1-9]{1}[0-9]{0,7}(\\.[0-9]{4})?"

/* TDec_0906Opc (base xs:string) */
#define MDF_PADRAO_TDec_0906Opc "0\\.[1-9]{1}[0-9]{5}|0\\.[0-9]{1}[1-9]{1}[0-9]{4}|0\\.[0-9]{2}[1-9]{1}[0-9]{3}|0\\.[0-9]{3}[1-9]{1}[0-9]{2}|0\\.[0-9]{4}[1-9]{1}[0-9]{1}|0\\.[0-9]{5}[1-9]{1}|[1-9]{1}[0-9]{0,8}(\\.[0-9]{6})?"

/* TDec_1104 (base xs:string) */
#define MDF_PADRAO_TDec_1104 "0|0\\.[0-9]{4}|[1-9]{1}[0-9]{0,10}(\\.[0-9]{4})?"

/* TDec_1104Opc (base xs:string) */
#define MDF_PADRAO_TDec_1104Opc "0\\.[1-9]{1}[0-9]{3}|0\\.[0-9]{3}[1-9]{1}|0\\.[0-9]{2}[1-9]{1}[0-9]{1}|0\\.[0-9]{1}[1-9]{1}[0-9]{2}|[1-9]{1}[0-9]{0,10}(\\.[0-9]{4})?"

/* TDec_1203 (base xs:string) */
#define MDF_PADRAO_TDec_1203 "0|0\\.[0-9]{3}|[1-9]{1}[0-9]{0,11}(\\.[0-9]{3})?"

/* TDec_1203Opc (base xs:string) */
#define MDF_PADRAO_TDec_1203Opc "0\\.[1-9]{1}[0-9]{2}|0\\.[0-9]{2}[1-9]{1}|0\\.[0-9]{1}[1-9]{1}[0-9]{1}|[1-9]{1}[0-9]{0,11}(\\.[0-9]{3})?"

/* TDec_1204 (base xs:string) */
#define MDF_PADRAO_TDec_1204 "0|0\\.[0-9]{4}|[1-9]{1}[0-9]{0,11}(\\.[0-9]{4})?"

/* TDec_1204Opc (base xs:string) */
#define MDF_PADRAO_TDec_1204Opc "0\\.[1-9]{1}[0-9]{3}|0\\.[0-9]{3}[1-9]{1}|0\\.[0-9]{2}[1-9]{1}[0-9]{1}|0\\.[0-9]{1}[1-9]{1}[0-9]{2}|[1-9]{1}[0-9]{0,11}(\\.[0-9]{4})?"

/* TDec_1302 (base xs:string) */
#define MDF_PADRAO_TDec_1302 "0|0\\.[0-9]{2}|[1-9]{1}[0-9]{0,12}(\\.[0-9]{2})?"

/* TDec_1302Opc (base xs:string) */
#define MDF_PADRAO_TDec_1302Opc "0\\.[0-9]{1}[1-9]{1}|0\\.[1-9]{1}[0-9]{1}|[1-9]{1}[0-9]{0,12}(\\.[0-9]{2})?"

/* TIeDest (base xs:string) */
#define MDF_PADRAO_TIeDest "[0-9]{0,14}|ISENTO|PR[0-9]{4,8}"

/* TModMD (base xs:string) */
#define MDF_VALORES_TModMD "58"

/* TIe (base xs:string) */
#define MDF_PADRAO_TIe "[0-9]{2,14}"

/* TNF (base xs:string) */
#define MDF_PADRAO_TNF "[1-9]{1}[0-9]{0,8}"

/* TSerie (base xs:string) */
#define MDF_PADRAO_TSerie "0|[1-9]{1}[0-9]{0,2}"

/* TUf (base xs:string) */
#define MDF_VALORES_TUf "AC", "AL", "AM", "AP", "BA", "CE", "DF", "ES", "GO", "MA", "MG", "MS", "MT", "PA", "PB", "PE", "PI", "PR", "RJ", "RN", "RO", "RR", "RS", "SC", "SE", "SP", "TO", "EX"

/* TAmb (base xs:string) */
#define MDF_VALORES_TAmb "1", "2"

/* TEmit (base xs:string) */
#define MDF_VALORES_TEmit "1", "2", "3"

/* TTransp (base xs:string) */
#define MDF_VALORES_TTransp "1", "2", "3"

/* TVerAplic (base TString) */
#define MDF_PADRAO_TVerAplic MDF_PADRAO_TString
#define MDF_TAM_MIN_TVerAplic 1
#define MDF_TAM_MAX_TVerAplic 20

/* TMotivo (base TString) */
#define MDF_PADRAO_TMotivo MDF_PADRAO_TString
#define MDF_TAM_MIN_TMotivo 1
#define MDF_TAM_MAX_TMotivo 255

/* TJust (base TString) */
#define MDF_PADRAO_TJust MDF_PADRAO_TString
#define MDF_TAM_MIN_TJust 15
#define MDF_TAM_MAX_TJust 255

/* TServ (base TString) */
#define MDF_PADRAO_TServ MDF_PADRAO_TString

/* Tano (base xs:string) */
#define MDF_PADRAO_Tano "[0-9]{2}"

/* TMed (base xs:string) */
#define MDF_PADRAO_TMed "[0-9]{1,4}"

/* TString (base xs:string) */
#define MDF_PADRAO_TString "[!-\xC3\xBF]{1}[ -\xC3\xBF]{0,}[!-\xC3\xBF]{1}|[!-\xC3\xBF]{1}"

/* TData (base xs:string) */
#define MDF_PADRAO_TData "(((20(([02468][048])|([13579][26]))-02-29))|(20[0-9][0-9])-((((0[1-9])|(1[0-2]))-((0[1-9])|(1\\d)|(2[0-8])))|((((0[13578])|(1[02]))-31)|(((0[1,3-9])|(1[0-2]))-(29|30)))))"

/* TLatitude (base TString) */
#define MDF_PADRAO_TLatitude "[0-9]\\.[0-9]{6}|[1-8][0-9]\\.[0-9]{6}|90\\.[0-9]{6}|-[0-9]\\.[0-9]{6}|-[1-8][0-9]\\.[0-9]{6}|-90\\.[0-9]{6}"

/* TLongitude (base TString) */
#define MDF_PADRAO_TLongitude "[0-9]\\.[0-9]{6}|[1-9][0-9]\\.[0-9]{6}|1[0-7][0-9]\\.[0-9]{6}|180\\.[0-9]{6}|-[0-9]\\.[0-9]{6}|-[1-9][0-9]\\.[0-9]{6}|-1[0-7][0-9]\\.[0-9]{6}|-180\\.[0-9]{6}"

/* TtipoUnidTransp (base xs:string) */
#define MDF_VALORES_TtipoUnidTransp "1", "2", "3", "4", "5", "6", "7"

/* TtipoUnidCarga (base xs:string) */
#define MDF_VALORES_TtipoUnidCarga "1", "2", "3", "4"

/* TNSU (base xs:string) */
#define MDF_PADRAO_TNSU "[0-9]{15}"

/* TIPv4 (base xs:string) */
#define MDF_PADRAO_TIPv4 "(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])"

/* TPlaca (base xs:string) */
#define MDF_PADRAO_TPlaca "[A-Z]{2,3}[0-9]{4}|[A-Z]{3,4}[0-9]{3}|[A-Z0-9]{7}"

/* TRNTRC (base TString) */
#define MDF_PADRAO_TRNTRC "[0-9]{8}"

/* TCIOT (base TString) */
#define MDF_PADRAO_TCIOT "[0-9]{12}"

/* TVerEvento (base xs:string) */
#define MDF_PADRAO_TVerEvento "3\\.00"

/* TProcEmi (base xs:string) */
#define MDF_VALORES_TProcEmi "0", "4"

/* TIdLote (base xs:string) */
#define MDF_PADRAO_TIdLote "[0-9]{1,15}"

/* TModalMD (base xs:string) */
#define MDF_VALORES_TModalMD "1", "2", "3", "4"

/* TModDoc (base xs:string) */
#define MDF_VALORES_TModDoc "01", "1B", "02", "2D", "2E", "04", "06", "07", "08", "8B", "09", "10", "11", "13", "14", "15", "16", "17", "18", "20", "21", "22", "23", "24", "25", "26", "27", "28", "55"

/* TVerMDe (base xs:string) */
#define MDF_PADRAO_TVerMDe "3\\.00"

/* TTime (base xs:string) */
#define MDF_PADRAO_TTime "(([0-1][0-9])|([2][0-3])):([0-5][0-9]):([0-5][0-9])"

/* TPIN (base xs:string) */
#define MDF_PADRAO_TPIN "[1-9]{1}[0-9]{1,8}"
#define MDF_TAM_MIN_TPIN 2
#define MDF_TAM_MAX_TPIN 9

/* TContainer (base xs:string) */
#define MDF_PADRAO_TContainer "[A-Z0-9]+"
#define MDF_TAM_MIN_TContainer 1
#define MDF_TAM_MAX_TContainer 20

/* TEmail (base xs:string) */
#define MDF_PADRAO_TEmail "[^@]+@[^\\.]+\\..+"
#define MDF_TAM_MIN_TEmail 6
#define MDF_TAM_MAX_TEmail 60

/* Todos os tipos com MDF_PADRAO_*: MDF_TIPOS_COM_PADRAO(X) chama
 * X(tipo) para cada um */
#define MDF_TIPOS_COM_PADRAO(X) \
	X(TDateTimeUTC) \
	X(TCodMunIBGE) \
	X(TChCTe) \
	X(TChNFe) \
	X(TChMDFe) \
	X(TSegCodBarra) \
	X(TProt) \
	X(TRec) \
	X(TStat) \
	X(TCnpj) \
	X(TCnpjOpc) \
	X(TCpf) \
	X(TCpfVar) \
	X(TDec_0302) \
	X(TDec_0303) \
	X(TDec_0302Opc) \
	X(TDec_0302_0303) \
	X(TDec_0803) \
	X(TDec_0803Opc) \
	X(TDec_0804) \
	X(TDec_0804Opc) \
	X(TDec_0906Opc) \
	X(TDec_1104) \
	X(TDec_1104Opc) \
	X(TDec_1203) \
	X(TDec_1203Opc) \
	X(TDec_1204) \
	X(TDec_1204Opc) \
	X(TDec_1302) \
	X(TDec_1302Opc) \
	X(TIeDest) \
	X(TIe) \
	X(TNF) \
	X(TSerie) \
	X(TVerAplic) \
	X(TMotivo) \
	X(TJust) \
	X(TServ) \
	X(Tano) \
	X(TMed) \
	X(TString) \
	X(TData) \
	X(TLatitude) \
	X(TLongitude) \
	X(TNSU) \
	X(TIPv4) \
	X(TPlaca) \
	X(TRNTRC) \
	X(TCIOT) \
	X(TVerEvento) \
	X(TIdLote) \
	X(TVerMDe) \
	X(TTime) \
	X(TPIN) \
	X(TContainer) \
	X(TEmail)

/* clang-format on */

#endif
