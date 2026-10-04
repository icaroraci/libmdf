# libmdf

[![CI](https://github.com/icaroraci/libmdf/actions/workflows/ci.yml/badge.svg)](https://github.com/icaroraci/libmdf/actions/workflows/ci.yml)
[![Licença: LGPL v3+](https://img.shields.io/badge/licen%C3%A7a-LGPLv3%2B-blue.svg)](LICENSE)

Biblioteca C para emissão de MDF-e (Manifesto Eletrônico de Documentos Fiscais, modelo 58).

A libmdf é construída sobre a [libnfe](https://github.com/icaroraci/tooldoce), de quem usa a chave de acesso, o certificado A1, a assinatura XMLDSig, o envio SOAP/TLS à SEFAZ e a validação contra XSD. Aqui fica o que é próprio do MDF-e: o XML do leiaute 3.00 e dos modais, o QR Code (`infMDFeSupl`), os webservices da SVRS e os eventos do MDF-e. O DAMDFE (impressão) fica fora do escopo. O roteiro está em [`docs/ROTEIRO.md`](docs/ROTEIRO.md).

## Situação

Início do projeto (0.1.0-dev): estrutura, dependência da libnfe e CI. Nada do MDF-e está pronto ainda.

## Dependências

- [libnfe](https://github.com/icaroraci/tooldoce) 1.x, encontrada pelo `pkg-config` (`libnfe.pc`, instalado pelo `make install` do tooldoce), com as dependências dela (libxml2, xmlsec1 com OpenSSL e libcurl).
- libxml2, OpenSSL (`libssl-dev`) e zlib (`zlib1g-dev`, para a mensagem compactada da autorização), usadas diretamente.
- Compilador C99 (gcc ou clang) e GNU make.

```sh
# libnfe num prefixo, com o script do CI
sh .github/scripts/instalar_libnfe.sh "$HOME/.local/libnfe"
export PKG_CONFIG_PATH="$HOME/.local/libnfe/lib/pkgconfig"
```

## Compilação

```sh
make                      # lib/libmdf.so (SONAME libmdf.so.0)
make test                 # testes com AddressSanitizer e UBSan
make install PREFIX=/usr  # biblioteca, headers em include/libmdf e libmdf.pc
```

Quem usa a biblioteca compila com `pkg-config --cflags --libs libmdf` e inclui `<libmdf/...>`.

## Contribuindo

Veja [`CONTRIBUTING.md`](CONTRIBUTING.md) e as [convenções de código](docs/CONVENCOES.md).

## Licença

LGPLv3 ou posterior ([`LICENSE`](LICENSE), que complementa a GPLv3 em [`COPYING`](COPYING)), a mesma da libnfe: a biblioteca pode ser usada em programas de qualquer licença.
