# Histórico de mudanças

As mudanças relevantes de cada versão ficam registradas aqui. O formato segue o [Keep a Changelog](https://keepachangelog.com/pt-BR/1.1.0/) e as versões seguem o [versionamento semântico](https://semver.org/lang/pt-BR/): a versão maior muda quando a API ou a ABI deixam de ser compatíveis, e com ela o `SONAME` da biblioteca. Enquanto a versão maior for 0, a API pode mudar a cada versão menor.

## [Não lançado]

## [1.0.0-rc1] - 2026-10-04

Candidata à primeira versão estável (1.0.0). Cobre a emissão do MDF-e 3.00 com o modal rodoviário, da montagem do XML aos eventos na SVRS, testada na homologação real (ver [`docs/HOMOLOGACAO.md`](docs/HOMOLOGACAO.md)). Requer a libnfe 1.0.0-rc3 ou posterior.

### Adicionado

- Estrutura do projeto, no modelo da [libnfc](https://github.com/icaroraci/libnfc): Makefile (biblioteca `libmdf.so.1`, testes, `make install` com `libmdf.pc`), testes com AddressSanitizer e UBSan, CI com gcc e clang e `.clang-format`.
- Dependência da libnfe 1.x (1.0.0-rc3 ou posterior, com o motor de grupos como API) pelo `pkg-config`, e da libxml2, OpenSSL e zlib.
- Versão da biblioteca em `<libmdf/versao.h>` (`MDF_VERSAO`) e em tempo de execução (`mdf_versao()`).
- Roteiro em `docs/ROTEIRO.md`.
- Schemas oficiais do MDF-e 3.00 (PL_MDFe_300b, NT 2025.001) em `tests/schemas/mdfe`, sem alteração e com os hashes conferidos no CI, e a configuração dos geradores da libnfe em `tools/documento.json`.
- MDF-e 3.00 com o modal rodoviário (`<libmdf/mdfe.h>`): grupos do leiaute pelo motor de grupos da libnfe, gerados dos schemas oficiais (`src/libmdf/esquemas.c`); chave de acesso, cDV e Id calculados; `mdf_assinar` assina `infMDFe` e acrescenta o QR Code, com o parâmetro `sign` em contingência.
- Eventos do MDF-e (`<libmdf/evento.h>`): cancelamento, encerramento, inclusão de condutor, inclusão de DF-e e pagamento da operação.
- Webservices da SVRS (`<libmdf/sefaz.h>`): autorização síncrona com a mensagem em gzip e base64 e o `mdfeProc`, status do serviço, consulta pela chave, eventos com o `procEventoMDFe` e MDF-e não encerrados; endereços em `docs/ENDERECOS.md`.
- Testes contra os schemas oficiais e contra um servidor falso da SEFAZ (`tests/servidor_sefaz.py`, com TLS e certificado de cliente de teste).
- Exemplo `examples/emitir_mdfe.c`, para a homologação no computador do mantenedor (`docs/HOMOLOGACAO.md`).
- Primeira homologação real na SVRS (`docs/HOMOLOGACAO.md`): status, autorização, consulta, não encerrados, encerramento e cancelamento aceitos; endereços de homologação e URL do QR Code confirmados em `docs/ENDERECOS.md`.
- Diagramas do leiaute em `docs/diagramas` e a lista de estruturas em `TODO.md`, gerados dos schemas.

[Não lançado]: https://github.com/icaroraci/libmdf/compare/v1.0.0-rc1...HEAD
[1.0.0-rc1]: https://github.com/icaroraci/libmdf/releases/tag/v1.0.0-rc1
