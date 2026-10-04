#!/bin/sh
# Compila e instala a libnfe (repositório tooldoce) num prefixo, para o CI.
# O `make install` da libnfe grava o libnfe.pc (icaroraci/tooldoce#269).
#
# Uso: sh .github/scripts/instalar_libnfe.sh PREFIXO [REF]
#   PREFIXO  destino da instalação (ex.: "$RUNNER_TEMP/libnfe")
#   REF      branch, tag ou commit do tooldoce (padrão: master)
# Depois: export PKG_CONFIG_PATH="PREFIXO/lib/pkgconfig"

set -eu

prefixo=$1
ref=${2:-master}
fonte=$(mktemp -d)

git clone --quiet https://github.com/icaroraci/tooldoce.git "$fonte"
git -C "$fonte" checkout --quiet "$ref"
echo "libnfe: tooldoce $(git -C "$fonte" rev-parse --short HEAD) ($ref)"

make -C "$fonte" install PREFIX="$prefixo"
test -f "$prefixo/lib/pkgconfig/libnfe.pc"

rm -rf "$fonte"
