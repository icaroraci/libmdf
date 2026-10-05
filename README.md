# libmdf

[![CI](https://github.com/icaroraci/libmdf/actions/workflows/ci.yml/badge.svg)](https://github.com/icaroraci/libmdf/actions/workflows/ci.yml)
[![Release](https://img.shields.io/github/v/release/icaroraci/libmdf?include_prereleases&label=vers%C3%A3o)](https://github.com/icaroraci/libmdf/releases)
[![Licença: LGPL v3+](https://img.shields.io/badge/licen%C3%A7a-LGPLv3%2B-blue.svg)](LICENSE)
[![MDF-e homologado](https://img.shields.io/badge/MDF--e%2058-homologado%20na%20SVRS-brightgreen.svg)](docs/HOMOLOGACAO.md)

Biblioteca C para emissão de MDF-e (Manifesto Eletrônico de Documentos Fiscais, modelo 58).

A libmdf é construída sobre a [libnfe](https://github.com/icaroraci/tooldoce), de quem usa a chave de acesso, o certificado A1, a assinatura XMLDSig, o envio SOAP/TLS à SEFAZ e a validação contra XSD. Aqui fica o que é próprio do MDF-e: o XML do leiaute 3.00 e dos modais, o QR Code (`infMDFeSupl`), os webservices da SVRS e os eventos do MDF-e. O DAMDFE (impressão) fica fora do escopo. O roteiro está em [`docs/ROTEIRO.md`](docs/ROTEIRO.md).

## Situação

**Versão 1.0.0-rc1**, candidata à 1.0 (ver o [histórico de mudanças](CHANGELOG.md)). O caminho completo do MDF-e com o modal rodoviário está pronto: montagem do XML, assinatura e QR Code, autorização, consulta, não encerrados, encerramento e cancelamento, testados contra os schemas oficiais e na homologação real da SVRS ([`docs/HOMOLOGACAO.md`](docs/HOMOLOGACAO.md)). A partir da 1.0, a API segue o [versionamento semântico](https://semver.org/lang/pt-BR/): mudanças incompatíveis só numa nova versão maior, que também troca o `SONAME` (`libmdf.so.1`). A versão fica em `<libmdf/versao.h>` (`MDF_VERSAO`) e, em tempo de execução, em `mdf_versao()`.

| Parte | Header |
|---|---|
| MDF-e 3.00 com modal rodoviário: grupos pelo motor de grupos da libnfe, chave de acesso, XML, assinatura e QR Code (normal e contingência) | `<libmdf/mdfe.h>` |
| Eventos: cancelamento, encerramento, inclusão de condutor, inclusão de DF-e e pagamento da operação | `<libmdf/evento.h>` |
| Webservices da SVRS: autorização síncrona (gzip e base64), status, consulta, eventos e MDF-e não encerrados | `<libmdf/sefaz.h>` |

O que falta está em [`docs/ROTEIRO.md`](docs/ROTEIRO.md) e a lista de grupos do leiaute, em [`TODO.md`](TODO.md).

## Uso

```c
mdf_mdfe *m = mdf_mdfe_new();
nfe_grupo *ide = mdf_mdfe_grupo(m, "ide");
nfe_grupo_set(ide, "cUF", "43");
/* ... ide, emit, rodo, infDoc, tot (ver examples/emitir_mdfe.c) ... */
nfe_grupo_set(mdf_mdfe_grupo(m, "rodo"), "veicTracao/placa", "ABC1D23");

mdf_mdfe_xml(m, &xml, &tam);                    /* chave, cDV e Id */
mdf_assinar(cert, xml, tam, &mdfe, NULL);       /* assinatura e QR Code */
mdf_sefaz_endereco(NFE_AMBIENTE_HOMOLOGACAO, MDF_SERVICO_AUTORIZACAO, &url);
mdf_sefaz_autorizar(s, url, mdfe, &cstat, motivo, sizeof motivo, &proc, NULL);
```

O exemplo [`examples/emitir_mdfe.c`](examples/emitir_mdfe.c) emite, consulta e encerra um MDF-e na homologação, com os dados do emitente em variáveis de ambiente.

## Dependências

- [libnfe](https://github.com/icaroraci/tooldoce) 1.0.0-rc4 ou posterior (o motor de grupos como API), encontrada pelo `pkg-config` (`libnfe.pc`, instalado pelo `make install` do tooldoce), com as dependências dela (libxml2, xmlsec1 com OpenSSL e libcurl).
- libxml2, OpenSSL (`libssl-dev`) e zlib (`zlib1g-dev`, para a mensagem compactada da autorização), usadas diretamente.
- Compilador C99 (gcc ou clang) e GNU make.

```sh
# libnfe num prefixo, com o script do CI
sh .github/scripts/instalar_libnfe.sh "$HOME/.local/libnfe" v1.0.0-rc4
export PKG_CONFIG_PATH="$HOME/.local/libnfe/lib/pkgconfig"
```

## Compilação

```sh
make                      # lib/libmdf.so (SONAME libmdf.so.1)
make test                 # testes com AddressSanitizer e UBSan
make install PREFIX=/usr  # biblioteca, headers em include/libmdf e libmdf.pc
```

Quem usa a biblioteca compila com `pkg-config --cflags --libs libmdf` e inclui `<libmdf/...>`.

## Contribuindo

Veja [`CONTRIBUTING.md`](CONTRIBUTING.md) e as [convenções de código](docs/CONVENCOES.md).

## Licença

LGPLv3 ou posterior ([`LICENSE`](LICENSE), que complementa a GPLv3 em [`COPYING`](COPYING)), a mesma da libnfe: a biblioteca pode ser usada em programas de qualquer licença.
