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

## O que já foi feito, na libmdf

1. **XML do MDF-e** (leiaute 3.00): os grupos de `infMDFe` pelo motor de grupos (`ide`, `emit`, `infDoc`, `seg`, `prodPred`, `tot`, `lacres`, `autXML`, `infAdic`, `infRespTec`), com a chave, o cDV e o Id calculados, validado contra o XSD (`mdfe.h`).
2. **Modal rodoviário** (`infModal`/`rodo`): veículo de tração, reboques, condutores, CIOT, vale-pedágio, contratantes e pagamento do frete, validado contra `mdfeModalRodoviario_v3.00.xsd`.
3. **QR Code** (`infMDFeSupl/qrCodMDFe`), em emissão normal e em contingência (com `sign`, a assinatura RSA-SHA1 da chave).
4. **Autorização síncrona** (`MDFeRecepcaoSinc`, gzip e base64) com `mdfeProc`; status do serviço, consulta pela chave e MDF-e não encerrados (`sefaz.h`).
5. **Eventos**: cancelamento, encerramento, inclusão de condutor, inclusão de DF-e e pagamento da operação (`evento.h`), com `procEventoMDFe`.
6. **Homologação real** na SVRS em 4 de outubro de 2026: status, autorização, consulta, não encerrados, encerramento e cancelamento aceitos, com os endereços de homologação e o QR Code confirmados (`docs/HOMOLOGACAO.md`).
7. **Versão 1.0.0-rc1**, candidata à 1.0.

## O que falta

1. Homologação dos eventos ainda não testados na SVRS (inclusão de condutor, inclusão de DF-e, pagamento da operação) e da emissão em contingência; conferência dos endereços de produção, marcados "(conferir)" em `docs/ENDERECOS.md`.
2. Eventos de outros autores ou mais raros: alteração do pagamento do serviço (110118) e confirmação do serviço de transporte (110117, do contratante).
3. Modais aéreo, aquaviário e ferroviário; distribuição de DF-e (`MDFeDistribuicaoDFe`).
4. Grupos de regimes especiais em `infMDFe`: Nota Fiscal Fácil (`infSolicNFF`) e Provedor de Assinatura e Autorização (`infPAA`).

O DAMDFE (impressão) fica fora do escopo: é responsabilidade do programa emissor, que recebe o `mdfeProc` autorizado.

Se algum item exigir mudança no que é comum aos documentos fiscais (assinatura, comunicação, validação), a mudança vai para a libnfe, e a libmdf passa a exigir a versão que a trouxer.
