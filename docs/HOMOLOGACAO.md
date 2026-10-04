# Homologação

Registro dos testes na homologação real da SVRS. Só entram chave, protocolo e cStat, nunca o XML: ele tem dados do certificado e da empresa.

A homologação roda no computador do mantenedor (WSL), com o certificado A1 da empresa e a senha numa variável de ambiente; a rede das sessões na nuvem não alcança a SEFAZ.

## Como rodar

```sh
sh .github/scripts/instalar_libnfe.sh "$HOME/.local/libnfe" claude/project-thread-dyl1yz   # ou master, depois do tooldoce#278
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

Para testar o cancelamento, emita outro MDF-e (`MDF_NMDF=2`) e use `cancelar <chave> <nProt>` em vez de `encerrar`. Se o servidor da SVRS não for aceito pelas autoridades do sistema, informe a cadeia em `MDF_CA` (ver `docs/TLS.md` do tooldoce).

## Resultados

| Data | Serviço | Webservice | cStat | Chave | Protocolo |
|---|---|---|---|---|---|
| | Status | MDFeStatusServico | (pendente) | | |
| | Autorização | MDFeRecepcaoSinc | (pendente) | | |
| | Consulta | MDFeConsulta | (pendente) | | |
| | Não encerrados | MDFeConsNaoEnc | (pendente) | | |
| | Encerramento (110112) | MDFeRecepcaoEvento | (pendente) | | |
| | Cancelamento (110111) | MDFeRecepcaoEvento | (pendente) | | |

## Ainda não testado na homologação

- Inclusão de condutor (110114), inclusão de DF-e (110115) e pagamento da operação (110116).
- Emissão em contingência (`tpEmis` 2, QR Code com `sign`).
