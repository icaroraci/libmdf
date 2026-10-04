# Convenções de código

A libmdf segue as [convenções da libnfe](https://github.com/icaroraci/tooldoce/blob/master/docs/CONVENCOES.md) (objetos opacos com `_new`/`_free`, setters validados, retorno `0` ou código de erro negativo, nenhuma impressão, textos UTF-8 com limite de tamanho), trocando o prefixo:

| Elemento | Padrão | Exemplo |
|---|---|---|
| Funções públicas | `mdf_<grupo>_<ação>[_<campo>]` | `mdf_versao` |
| Tipos opacos | `typedef struct mdf_<grupo> mdf_<grupo>;` | |
| Constantes de enum | `MDF_<NOME>_<VALOR>` | |
| Macros e constantes | `MDF_<NOME>` | `MDF_VERSAO` |
| Guardas de header | `LIBMDF_<ARQUIVO>_H` | `LIBMDF_VERSAO_H` |

- Headers públicos em `include/libmdf/`, incluídos como `<libmdf/arquivo.h>`; cada um compila sozinho (o CI confere).
- Tipos e funções da libnfe são usados diretamente (`nfe_nfe`, `nfe_grupo`, `nfe_sefaz`), sem embrulhá-los. Os códigos de erro também são os de `<libnfe/erros.h>`, até haver um erro próprio do MDF-e.
- **A biblioteca não imprime nada**; o CI falha se ela usar funções de saída da libc.

## Formatação

`.clang-format` na raiz (o mesmo da libnfe). Aplique com `make formatar`; o CI confere com `make verificar-formato`.
