# Homologação

Registro dos testes na homologação real da SVRS. Só entram chave, protocolo e cStat, nunca o XML: ele tem dados do certificado e da empresa.

A homologação roda no computador do mantenedor (WSL), com o certificado A1 da empresa e a senha numa variável de ambiente; a rede das sessões na nuvem não alcança a SEFAZ.

## Como rodar

```sh
sh .github/scripts/instalar_libnfe.sh "$HOME/.local/libnfe" v1.0.0-rc4
export PKG_CONFIG_PATH="$HOME/.local/libnfe/lib/pkgconfig"
make exemplos

# Dados do emitente (os do certificado) e da viagem
export MDF_CNPJ=... MDF_IE=... MDF_XNOME="..." MDF_CUF=33 MDF_UF=RJ \
       MDF_CMUN=... MDF_XMUN="..." MDF_PLACA=... MDF_CONDUTOR_CPF=... \
       MDF_CONDUTOR_NOME="..." MDF_CHNFE=<chave de uma NF-e da empresa> \
       MDF_UF_FIM=RJ MDF_CUF_FIM=33 MDF_CMUN_FIM=... MDF_XMUN_FIM="..."
pfx=caminho/do/certificado.pfx

./obj/emitir_mdfe "$pfx" "$TOOLDOCE_PFX_PASSWORD" status
./obj/emitir_mdfe "$pfx" "$TOOLDOCE_PFX_PASSWORD" autorizar > mdfeProc.xml
./obj/emitir_mdfe "$pfx" "$TOOLDOCE_PFX_PASSWORD" consultar <chave>
./obj/emitir_mdfe "$pfx" "$TOOLDOCE_PFX_PASSWORD" nao-encerrados
./obj/emitir_mdfe "$pfx" "$TOOLDOCE_PFX_PASSWORD" encerrar <chave> <nProt>
```

Para testar o cancelamento, emita outro MDF-e (`MDF_NMDF=2`) e use `cancelar <chave> <nProt>` em vez de `encerrar`. A SVRS usa certificado da ICP-Brasil, que não está nas autoridades do sistema: informe a cadeia (raiz ICP-Brasil v10) em `MDF_CA` (ver `docs/TLS.md` do tooldoce).

Nos testes do WSL, `make test` travou com `AddressSanitizer:DEADLYSIGNAL` repetido: é o ASan com a aleatoriedade de endereços do kernel do WSL 2 (6.18), não um erro da biblioteca. Rodando os testes com `setarch $(uname -m) -R ./obj/test_...`, todos passam.

## Resultados

Emitente de Sapucaia (RJ), descarga no Rio de Janeiro (RJ). A NF-e transportada é uma chave fictícia da própria empresa, com dígito verificador válido: a SVRS não exige que ela exista na homologação.

| Data | Serviço | Webservice | cStat | Chave | Protocolo |
|---|---|---|---|---|---|
| 2026-10-04 | Status | MDFeStatusServico | 107 | | |
| 2026-10-04 | Não encerrados (antes) | MDFeConsNaoEnc | 112 | | |
| 2026-10-04 | Autorização (nMDF 1) | MDFeRecepcaoSinc | 100 | 33261003465862000188580010000000011911474584 | 933260000026333 |
| 2026-10-04 | Consulta (nMDF 1) | MDFeConsulta | 100 | 33261003465862000188580010000000011911474584 | 933260000026333 |
| 2026-10-04 | Não encerrados | MDFeConsNaoEnc | 111 | 33261003465862000188580010000000011911474584 | 933260000026333 |
| 2026-10-04 | Encerramento (110112) | MDFeRecepcaoEvento | 135 | 33261003465862000188580010000000011911474584 | 933260000026334 |
| 2026-10-04 | Consulta após encerramento | MDFeConsulta | 132 | 33261003465862000188580010000000011911474584 | |
| 2026-10-04 | Autorização (nMDF 2) | MDFeRecepcaoSinc | 100 | 33261003465862000188580010000000021911474808 | 933260000026335 |
| 2026-10-04 | Cancelamento (110111) | MDFeRecepcaoEvento | 135 | 33261003465862000188580010000000021911474808 | 933260000026336 |
| 2026-10-04 | Consulta após cancelamento | MDFeConsulta | 101 | 33261003465862000188580010000000021911474808 | |
| 2026-10-04 | Não encerrados (depois) | MDFeConsNaoEnc | 112 | | |

O QR Code (`https://dfe-portal.svrs.rs.gov.br/mdfe/qrCode?chMDFe=...&tpAmb=2`) foi aceito nas duas autorizações.

## Ainda não testado na homologação

- Inclusão de condutor (110114), inclusão de DF-e (110115) e pagamento da operação (110116).
- Emissão em contingência (`tpEmis` 2, QR Code com `sign`).
