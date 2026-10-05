# TODO

Estruturas do MDF-e (leiaute 3.00) a implementar, na ordem do schema oficial. Cada item leva ao diagrama da estrutura.

Marque `[x]` quando a estrutura tiver: criação/liberação, setters com validação, geração do XML e testes validando contra o XSD. A lista é gerada por `python3 "$(pkg-config --variable=ferramentas libnfe)/gerar_diagramas.py" --config tools/documento.json --todo`, que preserva os itens marcados.

## Estruturas do MDF-e

- [x] [**MDFe**](docs/diagramas/MDFe.svg)
  - [x] [**infMDFe**](docs/diagramas/MDFe/infMDFe.svg)
    - [x] [**ide**](docs/diagramas/MDFe/infMDFe/ide.svg)
      - [x] [**infMunCarrega**](docs/diagramas/MDFe/infMDFe/ide/infMunCarrega.svg) `1..50`
      - [x] [**infPercurso**](docs/diagramas/MDFe/infMDFe/ide/infPercurso.svg) `0..25` _(opcional)_
    - [x] [**emit**](docs/diagramas/MDFe/infMDFe/emit.svg)
      - [x] [**enderEmit**](docs/diagramas/MDFe/infMDFe/emit/enderEmit.svg)
    - [x] [**infModal**](docs/diagramas/MDFe/infMDFe/infModal.svg)
    - [x] [**infDoc**](docs/diagramas/MDFe/infMDFe/infDoc.svg)
      - [x] [**infMunDescarga**](docs/diagramas/MDFe/infMDFe/infDoc/infMunDescarga.svg) `1..1000`
        - [x] [**infCTe**](docs/diagramas/MDFe/infMDFe/infDoc/infMunDescarga/infCTe.svg) `0..20000` _(opcional)_
          - [x] [**infUnidTransp**](docs/diagramas/MDFe/infMDFe/infDoc/infMunDescarga/infCTe/infUnidTransp.svg) `0..∞` _(opcional)_
            - [x] [**lacUnidTransp**](docs/diagramas/MDFe/infMDFe/infDoc/infMunDescarga/infCTe/infUnidTransp/lacUnidTransp.svg) `0..∞` _(opcional)_
            - [x] [**infUnidCarga**](docs/diagramas/MDFe/infMDFe/infDoc/infMunDescarga/infCTe/infUnidTransp/infUnidCarga.svg) `0..∞` _(opcional)_
              - [x] [**lacUnidCarga**](docs/diagramas/MDFe/infMDFe/infDoc/infMunDescarga/infCTe/infUnidTransp/infUnidCarga/lacUnidCarga.svg) `0..∞` _(opcional)_
          - [x] [**peri**](docs/diagramas/MDFe/infMDFe/infDoc/infMunDescarga/infCTe/peri.svg) `0..∞` _(opcional)_
          - [x] [**infEntregaParcial**](docs/diagramas/MDFe/infMDFe/infDoc/infMunDescarga/infCTe/infEntregaParcial.svg) `0..1` _(opcional)_
          - [x] [**infNFePrestParcial**](docs/diagramas/MDFe/infMDFe/infDoc/infMunDescarga/infCTe/infNFePrestParcial.svg) `1..∞`
        - [x] [**infNFe**](docs/diagramas/MDFe/infMDFe/infDoc/infMunDescarga/infNFe.svg) `0..20000` _(opcional)_
          - [x] [**infUnidTransp**](docs/diagramas/MDFe/infMDFe/infDoc/infMunDescarga/infNFe/infUnidTransp.svg) `0..∞` _(opcional)_
            - [x] [**lacUnidTransp**](docs/diagramas/MDFe/infMDFe/infDoc/infMunDescarga/infNFe/infUnidTransp/lacUnidTransp.svg) `0..∞` _(opcional)_
            - [x] [**infUnidCarga**](docs/diagramas/MDFe/infMDFe/infDoc/infMunDescarga/infNFe/infUnidTransp/infUnidCarga.svg) `0..∞` _(opcional)_
              - [x] [**lacUnidCarga**](docs/diagramas/MDFe/infMDFe/infDoc/infMunDescarga/infNFe/infUnidTransp/infUnidCarga/lacUnidCarga.svg) `0..∞` _(opcional)_
          - [x] [**peri**](docs/diagramas/MDFe/infMDFe/infDoc/infMunDescarga/infNFe/peri.svg) `0..∞` _(opcional)_
        - [x] [**infMDFeTransp**](docs/diagramas/MDFe/infMDFe/infDoc/infMunDescarga/infMDFeTransp.svg) `0..20000` _(opcional)_
          - [x] [**infUnidTransp**](docs/diagramas/MDFe/infMDFe/infDoc/infMunDescarga/infMDFeTransp/infUnidTransp.svg) `0..∞` _(opcional)_
            - [x] [**lacUnidTransp**](docs/diagramas/MDFe/infMDFe/infDoc/infMunDescarga/infMDFeTransp/infUnidTransp/lacUnidTransp.svg) `0..∞` _(opcional)_
            - [x] [**infUnidCarga**](docs/diagramas/MDFe/infMDFe/infDoc/infMunDescarga/infMDFeTransp/infUnidTransp/infUnidCarga.svg) `0..∞` _(opcional)_
              - [x] [**lacUnidCarga**](docs/diagramas/MDFe/infMDFe/infDoc/infMunDescarga/infMDFeTransp/infUnidTransp/infUnidCarga/lacUnidCarga.svg) `0..∞` _(opcional)_
          - [x] [**peri**](docs/diagramas/MDFe/infMDFe/infDoc/infMunDescarga/infMDFeTransp/peri.svg) `0..∞` _(opcional)_
    - [x] [**seg**](docs/diagramas/MDFe/infMDFe/seg.svg) `0..∞` _(opcional)_
      - [x] [**infResp**](docs/diagramas/MDFe/infMDFe/seg/infResp.svg)
      - [x] [**infSeg**](docs/diagramas/MDFe/infMDFe/seg/infSeg.svg) `0..1` _(opcional)_
    - [x] [**prodPred**](docs/diagramas/MDFe/infMDFe/prodPred.svg) `0..1` _(opcional)_
      - [x] [**infLotacao**](docs/diagramas/MDFe/infMDFe/prodPred/infLotacao.svg) `0..1` _(opcional)_
        - [x] [**infLocalCarrega**](docs/diagramas/MDFe/infMDFe/prodPred/infLotacao/infLocalCarrega.svg)
        - [x] [**infLocalDescarrega**](docs/diagramas/MDFe/infMDFe/prodPred/infLotacao/infLocalDescarrega.svg)
    - [x] [**tot**](docs/diagramas/MDFe/infMDFe/tot.svg)
    - [x] [**lacres**](docs/diagramas/MDFe/infMDFe/lacres.svg) `0..∞` _(opcional)_
    - [x] [**autXML**](docs/diagramas/MDFe/infMDFe/autXML.svg) `0..10` _(opcional)_
    - [x] [**infAdic**](docs/diagramas/MDFe/infMDFe/infAdic.svg) `0..1` _(opcional)_
    - [x] [**infRespTec**](docs/diagramas/MDFe/infMDFe/infRespTec.svg) `0..1` _(opcional)_
    - [x] [**infSolicNFF**](docs/diagramas/MDFe/infMDFe/infSolicNFF.svg) `0..1` _(opcional)_
    - [x] [**infPAA**](docs/diagramas/MDFe/infMDFe/infPAA.svg) `0..1` _(opcional)_
      - [x] [**PAASignature**](docs/diagramas/MDFe/infMDFe/infPAA/PAASignature.svg)
        - [x] [**RSAKeyValue**](docs/diagramas/MDFe/infMDFe/infPAA/PAASignature/RSAKeyValue.svg)
  - [x] [**infMDFeSupl**](docs/diagramas/MDFe/infMDFeSupl.svg) `0..1` _(opcional)_

## Além do leiaute

- [x] Assinatura
- [x] Transmissão
- [x] Eventos
