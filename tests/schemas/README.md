# Schemas do MDF-e

`mdfe/` contém os schemas oficiais do MDF-e, leiaute 3.00, do **pacote de liberação PL_MDFe_300b da NT 2025.001** (arquivo `PL_MDFe_300b_NT012025_1.04.zip`, cuja pasta interna se chama `PL_MDFe_300b_NT012025_1.05`; o arquivo mais recente do pacote é `mdfeTiposBasico_v3.00.xsd`, de 25/04/2026), publicado no [Portal do MDF-e](https://dfe-portal.svrs.rs.gov.br/Mdfe/Documentos) (Documentos › Esquemas XML). Os 41 arquivos são mantidos **sem alteração** e cobrem:

| Grupo | Schemas |
|---|---|
| Documento | `mdfe_v3.00.xsd`, `mdfeTiposBasico_v3.00.xsd` (leiaute, tipo `TMDFe`), `tiposGeralMDFe_v3.00.xsd`, `xmldsig-core-schema_v1.01.xsd` |
| Modais | `mdfeModalRodoviario_v3.00.xsd`, `mdfeModalAereo_v3.00.xsd`, `mdfeModalAquaviario_v3.00.xsd`, `mdfeModalFerroviario_v3.00.xsd` |
| Autorização | `enviMDFe`, `retEnviMDFe`, `retMDFe`, `procMDFe`, `consReciMDFe`, `retConsReciMDFe` |
| Consultas | `consSitMDFe`, `consStatServMDFe`, `consMDFeNaoEnc` (não encerrados), `mdfeConsultaDFe`, `distMDFe`/`leiauteDistMDFe` (distribuição) e os retornos |
| Eventos | `eventoMDFe`, `retEventoMDFe`, `procEventoMDFe`, `eventoMDFeTiposBasico` e o detalhe de cada evento: cancelamento (`evCancMDFe`), encerramento (`evEncMDFe`), inclusão de condutor (`evIncCondutorMDFe`), inclusão de DF-e (`evInclusaoDFeMDFe`), pagamento da operação (`evPagtoOperMDFe`), alteração de pagamento (`evAlteracaoPagtoServMDFe`) e confirmação do serviço (`evConfirmaServMDFe`) |

Em relação ao pacote anterior (NT 2024.002), mudaram `mdfeTiposBasico`, `tiposGeralMDFe`, `mdfeModalRodoviario`, `mdfeModalAquaviario`, `eventoMDFeTiposBasico`, `evPagtoOperMDFe` e `evAlteracaoPagtoServMDFe`.

`SHA256SUMS` guarda o hash de cada arquivo; o CI confere (`sha256sum -c`) que nenhum foi alterado. `tests/test_schemas.c` carrega os schemas de mensagem, modal e evento com o validador da libnfe e valida uma consulta de status.

A configuração em [`tools/documento.json`](../../tools/documento.json) descreve estes schemas para os geradores da libnfe (tabelas do motor de grupos, padrões, diagramas e TODO), conforme o `docs/ESQUEMAS.md` do tooldoce.

O Manual de Orientação do Contribuinte (MOC 3.00b, com o Anexo I de leiaute e regras de validação) não fica no repositório; consulte-o no portal.

## Atualizar

1. Baixe o pacote novo no Portal do MDF-e (Documentos › Esquemas XML).
2. Substitua os arquivos de `mdfe/` pelos do pacote, sem alterar, e atualize o nome e a data do pacote acima.
3. Regere os hashes: `cd tests/schemas && find . -name '*.xsd' | sort | xargs sha256sum > SHA256SUMS`.
4. Rode `make test` e os geradores (`docs/ESQUEMAS.md` do tooldoce).
