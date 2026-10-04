# Roteiro

A libmdf depende da [libnfe](https://github.com/icaroraci/tooldoce) 1.x e não duplica nada dela. Esta página separa o que a libnfe já entrega para o MDF-e do que falta construir aqui. Versões de leiaute, códigos de evento e endereços devem ser conferidos no [Portal do MDF-e](https://dfe-portal.svrs.rs.gov.br/Mdfe) antes de virarem código.

## O que a libnfe já faz pelo MDF-e

| Recurso | Onde, na libnfe |
|---|---|
| Chave de acesso de 44 posições e dígito verificador (mesma estrutura, `mod` 58) | `chave.h` |
| Certificado A1 e assinatura RSA-SHA1 fora do XML (QR Code em contingência) | `nfe_certificado_pfx`, `nfe_certificado_assinar` (`assinatura.h`) |
| Assinatura XMLDSig de `<MDFe>` e `<eventoMDFe>` | `nfe_assinar_elemento` (`assinatura.h`, icaroraci/tooldoce#273) |
| Envio SOAP 1.2 com TLS e certificado cliente aos webservices do MDF-e | `nfe_sefaz_enviar_ws` (`sefaz.h`, icaroraci/tooldoce#273) |
| Validação contra os XSD do MDF-e | `nfe_validador_xsd`, `nfe_validar_xsd` (`validar.h`, icaroraci/tooldoce#273) |

## O que falta, na libmdf

1. **XML do MDF-e** (leiaute 3.00): `ide` (UF de carregamento e de descarregamento, percurso), `emit`, `infDoc` (NF-e e CT-e por município de descarregamento), `seg`, `prodPred`, `tot`, `lacres`, `autXML`, `infAdic`, `infRespTec`, validado contra o XSD.
2. **Modal rodoviário** (`infModal`): veículo de tração, reboques, condutores, CIOT, vale-pedágio, contratantes e pagamento do frete.
3. **QR Code** (`infMDFeSupl/qrCodMDFe`), em emissão normal e em contingência (com `sign`).
4. **Autorização síncrona** (`MDFeRecepcaoSinc`, mensagem compactada em gzip e codificada em base64) com `mdfeProc`; status do serviço e consulta.
5. **Eventos**: encerramento, cancelamento, inclusão de condutor e de DF-e, pagamento da operação; consulta de MDF-e não encerrados.
6. **Homologação real** na SVRS, registrada em `docs/HOMOLOGACAO.md` (só chaves, protocolos e cStat).
7. Modais aéreo, aquaviário e ferroviário; distribuição de DF-e.

O DAMDFE (impressão) fica fora do escopo: é responsabilidade do programa emissor, que recebe o `mdfeProc` autorizado.

Se algum item exigir mudança no que é comum aos documentos fiscais (assinatura, comunicação, validação), a mudança vai para a libnfe, e a libmdf passa a exigir a versão que a trouxer.
