# Diagramas das estruturas do MDF-e (leiaute 3.00)

Gerados automaticamente a partir do schema oficial (`tests/schemas/mdfe/mdfeTiposBasico_v3.00.xsd`) por `tools/gerar_diagramas.py`. **Não edite os SVGs**: atualize o schema e rode `python3 "$(pkg-config --variable=ferramentas libnfe)/gerar_diagramas.py" --config tools/documento.json`.

Em cada diagrama: caixa tracejada = opcional; `0..1`, `1..∞` = ocorrências; **seq.** = os filhos aparecem nessa ordem; **escolha** = apenas um dos filhos; caixas amarelas (⊞) são estruturas com diagrama próprio, listadas abaixo.

- [MDFe](MDFe.svg) — Tipo Manifesto de Documentos Fiscais Eletrônicos
  - [infMDFe](MDFe/infMDFe.svg) — Informações do MDF-e
    - [ide](MDFe/infMDFe/ide.svg) — Identificação do MDF-e
      - [infMunCarrega](MDFe/infMDFe/ide/infMunCarrega.svg) `1..50` — Informações dos Municípios de Carregamento
      - [infPercurso](MDFe/infMDFe/ide/infPercurso.svg) `0..25` — Informações do Percurso do MDF-e
    - [emit](MDFe/infMDFe/emit.svg) — Identificação do Emitente do Manifesto
      - [enderEmit](MDFe/infMDFe/emit/enderEmit.svg) — Endereço do emitente
    - [infModal](MDFe/infMDFe/infModal.svg) — Informações do modal
    - [infDoc](MDFe/infMDFe/infDoc.svg) — Informações dos Documentos fiscais vinculados ao manifesto
      - [infMunDescarga](MDFe/infMDFe/infDoc/infMunDescarga.svg) `1..1000` — Informações dos Municípios de descarregamento
        - [infCTe](MDFe/infMDFe/infDoc/infMunDescarga/infCTe.svg) `0..20000` — Conhecimentos de Tranporte - usar este grupo quando for prestador de serviço de transporte
          - [infUnidTransp](MDFe/infMDFe/infDoc/infMunDescarga/infCTe/infUnidTransp.svg) `0..∞` — Informações das Unidades de Transporte (Carreta/Reboque/Vagão)
            - [lacUnidTransp](MDFe/infMDFe/infDoc/infMunDescarga/infCTe/infUnidTransp/lacUnidTransp.svg) `0..∞` — Lacres das Unidades de Transporte
            - [infUnidCarga](MDFe/infMDFe/infDoc/infMunDescarga/infCTe/infUnidTransp/infUnidCarga.svg) `0..∞` — Informações das Unidades de Carga (Containeres/ULD/Outros)
              - [lacUnidCarga](MDFe/infMDFe/infDoc/infMunDescarga/infCTe/infUnidTransp/infUnidCarga/lacUnidCarga.svg) `0..∞` — Lacres das Unidades de Carga
          - [peri](MDFe/infMDFe/infDoc/infMunDescarga/infCTe/peri.svg) `0..∞` — Preenchido quando for transporte de produtos classificados pela ONU como perigosos.
          - [infEntregaParcial](MDFe/infMDFe/infDoc/infMunDescarga/infCTe/infEntregaParcial.svg) `0..1` — Grupo de informações da Entrega Parcial (Corte de Voo)
          - [infNFePrestParcial](MDFe/infMDFe/infDoc/infMunDescarga/infCTe/infNFePrestParcial.svg) `1..∞` — Grupo de informações das NFe que foram entregues do CTe relacionado
        - [infNFe](MDFe/infMDFe/infDoc/infMunDescarga/infNFe.svg) `0..20000` — Nota Fiscal Eletronica
          - [infUnidTransp](MDFe/infMDFe/infDoc/infMunDescarga/infNFe/infUnidTransp.svg) `0..∞` — Informações das Unidades de Transporte (Carreta/Reboque/Vagão)
            - [lacUnidTransp](MDFe/infMDFe/infDoc/infMunDescarga/infNFe/infUnidTransp/lacUnidTransp.svg) `0..∞` — Lacres das Unidades de Transporte
            - [infUnidCarga](MDFe/infMDFe/infDoc/infMunDescarga/infNFe/infUnidTransp/infUnidCarga.svg) `0..∞` — Informações das Unidades de Carga (Containeres/ULD/Outros)
              - [lacUnidCarga](MDFe/infMDFe/infDoc/infMunDescarga/infNFe/infUnidTransp/infUnidCarga/lacUnidCarga.svg) `0..∞` — Lacres das Unidades de Carga
          - [peri](MDFe/infMDFe/infDoc/infMunDescarga/infNFe/peri.svg) `0..∞` — Preenchido quando for transporte de produtos classificados pela ONU como perigosos.
        - [infMDFeTransp](MDFe/infMDFe/infDoc/infMunDescarga/infMDFeTransp.svg) `0..20000` — Manifesto Eletrônico de Documentos Fiscais. Somente para modal Aquaviário (vide regras MOC)
          - [infUnidTransp](MDFe/infMDFe/infDoc/infMunDescarga/infMDFeTransp/infUnidTransp.svg) `0..∞` — Informações das Unidades de Transporte (Carreta/Reboque/Vagão)
            - [lacUnidTransp](MDFe/infMDFe/infDoc/infMunDescarga/infMDFeTransp/infUnidTransp/lacUnidTransp.svg) `0..∞` — Lacres das Unidades de Transporte
            - [infUnidCarga](MDFe/infMDFe/infDoc/infMunDescarga/infMDFeTransp/infUnidTransp/infUnidCarga.svg) `0..∞` — Informações das Unidades de Carga (Containeres/ULD/Outros)
              - [lacUnidCarga](MDFe/infMDFe/infDoc/infMunDescarga/infMDFeTransp/infUnidTransp/infUnidCarga/lacUnidCarga.svg) `0..∞` — Lacres das Unidades de Carga
          - [peri](MDFe/infMDFe/infDoc/infMunDescarga/infMDFeTransp/peri.svg) `0..∞` — Preenchido quando for transporte de produtos classificados pela ONU como perigosos.
    - [seg](MDFe/infMDFe/seg.svg) `0..∞` — Informações de Seguro da Carga
      - [infResp](MDFe/infMDFe/seg/infResp.svg) — Informações do responsável pelo seguro da carga
      - [infSeg](MDFe/infMDFe/seg/infSeg.svg) `0..1` — Informações da seguradora
    - [prodPred](MDFe/infMDFe/prodPred.svg) `0..1` — Produto predominante
      - [infLotacao](MDFe/infMDFe/prodPred/infLotacao.svg) `0..1` — Informações da carga lotação. Informar somente quando MDF-e for de carga lotação
        - [infLocalCarrega](MDFe/infMDFe/prodPred/infLotacao/infLocalCarrega.svg) — Informações da localização de carregamento do MDF-e de carga lotação
        - [infLocalDescarrega](MDFe/infMDFe/prodPred/infLotacao/infLocalDescarrega.svg) — Informações da localização de descarregamento do MDF-e de carga lotação
    - [tot](MDFe/infMDFe/tot.svg) — Totalizadores da carga transportada e seus documentos fiscais
    - [lacres](MDFe/infMDFe/lacres.svg) `0..∞` — Lacres do MDF-e
    - [autXML](MDFe/infMDFe/autXML.svg) `0..10` — Autorizados para download do XML do DF-e
    - [infAdic](MDFe/infMDFe/infAdic.svg) `0..1` — Informações Adicionais
    - [infRespTec](MDFe/infMDFe/infRespTec.svg) `0..1` — Informações do Responsável Técnico pela emissão do DF-e
    - [infSolicNFF](MDFe/infMDFe/infSolicNFF.svg) `0..1` — Grupo de informações do pedido de emissão da Nota Fiscal Fácil
    - [infPAA](MDFe/infMDFe/infPAA.svg) `0..1` — Grupo de Informação do Provedor de Assinatura e Autorização
      - [PAASignature](MDFe/infMDFe/infPAA/PAASignature.svg) — Assinatura RSA do Emitente para DFe gerados por PAA
        - [RSAKeyValue](MDFe/infMDFe/infPAA/PAASignature/RSAKeyValue.svg) — Chave Publica no padrão XML RSA Key
  - [infMDFeSupl](MDFe/infMDFeSupl.svg) `0..1` — Informações suplementares do MDF-e
