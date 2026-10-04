# Endereços

O MDF-e é autorizado pela SVRS para todas as UFs, então os endereços não dependem da UF do emitente: só do ambiente. Estão em `src/libmdf/sefaz.c` e são devolvidos por `mdf_sefaz_endereco` (`<libmdf/sefaz.h>`).

| Serviço (`mdf_servico`) | Webservice | Operação | Mensagem |
|---|---|---|---|
| `MDF_SERVICO_AUTORIZACAO` | MDFeRecepcaoSinc | mdfeRecepcao | `<MDFe>` em gzip e base64 |
| `MDF_SERVICO_CONSULTA` | MDFeConsulta | mdfeConsultaMDF | `<consSitMDFe>` |
| `MDF_SERVICO_STATUS` | MDFeStatusServico | mdfeStatusServicoMDF | `<consStatServMDFe>` |
| `MDF_SERVICO_EVENTO` | MDFeRecepcaoEvento | mdfeRecepcaoEvento | `<eventoMDFe>` |
| `MDF_SERVICO_NAO_ENCERRADOS` | MDFeConsNaoEnc | mdfeConsNaoEnc | `<consMDFeNaoEnc>` |

Os nomes dos webservices, as operações e o formato das mensagens vêm do MOC 3.00b (Visão Geral, seções 3.4.1, 4 e 5). O SOAP Header (`mdfeCabecMsg`) não é enviado: o MOC 3.00b o descontinuou.

## Servidores

Os endereços seguem o padrão publicado no [Portal do MDF-e](https://dfe-portal.svrs.rs.gov.br/MDFe/Servicos). Os de homologação foram confirmados em 4 de outubro de 2026, com os cinco webservices respondendo (ver `docs/HOMOLOGACAO.md`). Os de produção seguem o mesmo padrão, mas ainda não foram usados: ficam marcados como "(conferir)".

| Ambiente | Servidor | Caminho |
|---|---|---|
| Produção | `https://mdfe.svrs.rs.gov.br` | `/ws/<Webservice>/<Webservice>.asmx` (conferir) |
| Homologação | `https://mdfe-homologacao.svrs.rs.gov.br` | `/ws/<Webservice>/<Webservice>.asmx` |

O certificado do servidor da SVRS é emitido pela ICP-Brasil, cuja raiz não vem nas autoridades do sistema: sem a cadeia em `MDF_CA` (raiz ICP-Brasil v10, ver `docs/TLS.md` do tooldoce), a conexão falha com "unable to get local issuer certificate".

## QR Code

`MDF_URL_QRCODE` (`<libmdf/mdfe.h>`) é `https://dfe-portal.svrs.rs.gov.br/mdfe/qrCode`, o mesmo nos dois ambientes (MOC 3.00b, seção 9.2: o ambiente vai no parâmetro `tpAmb`). A SEFAZ compara o endereço sem diferenciar maiúsculas e minúsculas (regra F115, cStat 479). Confirmado na homologação: os MDF-e com esse endereço foram autorizados (cStat 100).
