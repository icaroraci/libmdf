#!/usr/bin/env python3
"""Servidor HTTPS falso da SEFAZ (SVRS) para tests/test_sefaz.c.

Exige o certificado de cliente de tests/certificados/teste.pfx (autenticação
mútua, como a SEFAZ), confere a mensagem de cada webservice do MDF-e 3.00 e
responde mensagens fixas. Escreve a porta na saída e atende até ser
encerrado. Os caminhos escolhem a resposta: /autoriza, /rejeita, /fault...

Uso: servidor_sefaz.py <diretório tests>
"""

import base64
import gzip
import http.server
import os
import re
import ssl
import sys

NS = "http://www.portalfiscal.inf.br/mdfe"
WSDL = NS + "/wsdl/"
DH = "2026-10-04T10:00:00-03:00"


def envelope(corpo):
    return ('<?xml version="1.0" encoding="utf-8"?><soap:Envelope '
            'xmlns:soap="http://www.w3.org/2003/05/soap-envelope">'
            '<soap:Body>' + corpo + '</soap:Body></soap:Envelope>')


def fault(motivo):
    return envelope('<soap:Fault><soap:Code><soap:Value>soap:Receiver'
                    '</soap:Value></soap:Code><soap:Reason>'
                    '<soap:Text xml:lang="pt">' + motivo +
                    '</soap:Text></soap:Reason></soap:Fault>')


def resultado(servico, corpo):
    return envelope('<mdfeResultMsg xmlns="' + WSDL + servico + '">' +
                    corpo + '</mdfeResultMsg>')


def status():
    return resultado(
        "MDFeStatusServico",
        '<retConsStatServMDFe xmlns="' + NS + '" versao="3.00">'
        '<tpAmb>2</tpAmb><verAplic>TESTE</verAplic><cStat>107</cStat>'
        '<xMotivo>Servico em Operacao</xMotivo><cUF>43</cUF>'
        '<dhRecbto>' + DH + '</dhRecbto></retConsStatServMDFe>')


def protocolo(chave, cstat, motivo):
    nprot = '<n:nProt>943260000000001</n:nProt>' if cstat == "100" else ''
    return ('<n:protMDFe versao="3.00"><n:infProt><n:tpAmb>2</n:tpAmb>'
            '<n:verAplic>TESTE</n:verAplic><n:chMDFe>' + chave +
            '</n:chMDFe><n:dhRecbto>' + DH + '</n:dhRecbto>' + nprot +
            '<n:digVal>AAAAAAAAAAAAAAAAAAAAAAAAAAA=</n:digVal>'
            '<n:cStat>' + cstat + '</n:cStat><n:xMotivo>' + motivo +
            '</n:xMotivo></n:infProt></n:protMDFe>')


def autorizacao(chave, cstat="100", motivo="Autorizado o uso do MDF-e"):
    # Namespace com prefixo no elemento de fora, para conferir que o
    # cliente reconstrói as declarações herdadas
    return envelope(
        '<mdfeResultMsg xmlns="' + WSDL + 'MDFeRecepcaoSinc" xmlns:n="' +
        NS + '"><n:retMDFe versao="3.00"><n:tpAmb>2</n:tpAmb>'
        '<n:cUF>43</n:cUF><n:verAplic>TESTE</n:verAplic>'
        '<n:cStat>104</n:cStat><n:xMotivo>Arquivo processado</n:xMotivo>' +
        protocolo(chave, cstat, motivo) + '</n:retMDFe></mdfeResultMsg>')


def recusado():
    return resultado(
        "MDFeRecepcaoSinc",
        '<retMDFe xmlns="' + NS + '" versao="3.00"><tpAmb>2</tpAmb>'
        '<cUF>43</cUF><verAplic>TESTE</verAplic><cStat>244</cStat>'
        '<xMotivo>Rejeicao: Falha na descompactacao da area de dados'
        '</xMotivo></retMDFe>')


def consulta(chave):
    return resultado(
        "MDFeConsulta",
        '<retConsSitMDFe xmlns="' + NS + '" versao="3.00"><tpAmb>2</tpAmb>'
        '<verAplic>TESTE</verAplic><cStat>100</cStat>'
        '<xMotivo>Autorizado o uso do MDF-e</xMotivo><cUF>43</cUF>' +
        protocolo(chave, "100", "Autorizado o uso do MDF-e")
        .replace('n:', '') + '</retConsSitMDFe>')


def nao_encerrados(chave):
    return resultado(
        "MDFeConsNaoEnc",
        '<retConsMDFeNaoEnc xmlns="' + NS + '" versao="3.00">'
        '<tpAmb>2</tpAmb><verAplic>TESTE</verAplic><cStat>111</cStat>'
        '<xMotivo>Consulta nao encerrados localizou MDF-e</xMotivo>'
        '<cUF>43</cUF><infMDFe><chMDFe>' + chave + '</chMDFe>'
        '<nProt>943260000000001</nProt></infMDFe></retConsMDFeNaoEnc>')


def evento(chave, tipo, seq, cstat="135",
           motivo="Evento registrado e vinculado a MDF-e"):
    nprot = ('<nProt>943260000000002</nProt>' if cstat == "135" else '')
    return resultado(
        "MDFeRecepcaoEvento",
        '<retEventoMDFe xmlns="' + NS + '" versao="3.00"><infEvento>'
        '<tpAmb>2</tpAmb><verAplic>TESTE</verAplic><cOrgao>43</cOrgao>'
        '<cStat>' + cstat + '</cStat><xMotivo>' + motivo + '</xMotivo>'
        '<chMDFe>' + chave + '</chMDFe><tpEvento>' + tipo + '</tpEvento>'
        '<xEvento>Encerramento</xEvento><nSeqEvento>' + seq +
        '</nSeqEvento><dhRegEvento>' + DH + '</dhRegEvento>' + nprot +
        '</infEvento></retEventoMDFe>')


def dados(corpo, servico):
    """Conteúdo de mdfeDadosMsg, se o elemento tem o namespace do serviço"""
    m = re.search(r'<mdfeDadosMsg xmlns="' + re.escape(WSDL + servico) +
                  r'">(.*)</mdfeDadosMsg>', corpo, re.S)
    return m.group(1) if m else None


class Tratador(http.server.BaseHTTPRequestHandler):
    def responde(self, codigo, corpo):
        dados = corpo.encode("utf-8")
        self.send_response(codigo)
        self.send_header("Content-Type", "application/soap+xml; charset=utf-8")
        self.send_header("Content-Length", str(len(dados)))
        self.end_headers()
        self.wfile.write(dados)

    def do_POST(self):
        n = int(self.headers.get("Content-Length", "0"))
        corpo = self.rfile.read(n).decode("utf-8")
        tipo = self.headers.get("Content-Type", "")
        m = re.search(r'action="([^"]*)"', tipo)
        acao = m.group(1) if m else ""
        if not self.connection.getpeercert():
            self.responde(403, fault("sem certificado"))
        elif "<soap12:Header>" in corpo:
            self.responde(500, fault("SOAP Header descontinuado"))
        elif self.path == "/fault":
            self.responde(500, fault("Erro de teste"))
        elif acao == WSDL + "MDFeStatusServico/mdfeStatusServicoMDF":
            msg = dados(corpo, "MDFeStatusServico")
            if msg and ('<consStatServMDFe xmlns="' + NS +
                        '" versao="3.00"><tpAmb>2</tpAmb>'
                        '<xServ>STATUS</xServ>') in msg:
                self.responde(200, status())
            else:
                self.responde(500, fault("status invalido"))
        elif acao == WSDL + "MDFeRecepcaoSinc/mdfeRecepcao":
            # A mensagem vai compactada (gzip) e em base64
            msg = dados(corpo, "MDFeRecepcaoSinc")
            try:
                xml = gzip.decompress(base64.b64decode(msg)).decode("utf-8")
            except Exception:
                xml = ""
            m = re.search(r'Id="MDFe([0-9A-Z]{44})"', xml)
            if not (m and xml.startswith("<MDFe ") and
                    "<infMDFeSupl><qrCodMDFe>" in xml and
                    "<Signature" in xml):
                self.responde(200, recusado())
            elif self.path == "/rejeita":
                self.responde(200, autorizacao(
                    m.group(1), "611",
                    "Rejeicao: Existe MDF-e nao encerrado para esta placa"))
            elif self.path == "/outra":
                self.responde(200, autorizacao("0" * 44))
            else:
                self.responde(200, autorizacao(m.group(1)))
        elif acao == WSDL + "MDFeConsulta/mdfeConsultaMDF":
            msg = dados(corpo, "MDFeConsulta")
            m = re.search(r'<xServ>CONSULTAR</xServ><chMDFe>([0-9A-Z]{44})'
                          r'</chMDFe>', msg or "")
            if m:
                self.responde(200, consulta(m.group(1)))
            else:
                self.responde(500, fault("consulta invalida"))
        elif acao == WSDL + "MDFeConsNaoEnc/mdfeConsNaoEnc":
            msg = dados(corpo, "MDFeConsNaoEnc")
            if msg and ("<xServ>CONSULTAR NÃO ENCERRADOS</xServ>"
                        "<CNPJ>11222333000181</CNPJ>") in msg:
                self.responde(200, nao_encerrados(
                    "4326101122233300018158001000000001112345678" + "0"))
            else:
                self.responde(500, fault("consulta invalida"))
        elif acao == WSDL + "MDFeRecepcaoEvento/mdfeRecepcaoEvento":
            msg = dados(corpo, "MDFeRecepcaoEvento") or ""
            m = re.search(r'Id="ID([0-9]{6})([0-9A-Z]{44})([0-9]{2,3})"',
                          msg)
            if not (m and msg.startswith("<eventoMDFe ") and
                    "<Signature" in msg):
                self.responde(500, fault("evento invalido"))
            elif self.path == "/rejeita":
                self.responde(200, evento(
                    m.group(2), m.group(1), str(int(m.group(3))), "631",
                    "Rejeicao: Duplicidade de evento"))
            else:
                self.responde(200, evento(m.group(2), m.group(1),
                                          str(int(m.group(3)))))
        else:
            self.responde(500, fault("acao desconhecida: " + acao))

    def log_message(self, *args):
        pass


def main():
    certs = os.path.join(sys.argv[1], "certificados")
    ctx = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
    ctx.load_cert_chain(os.path.join(certs, "servidor.pem"),
                        os.path.join(certs, "servidor_chave.pem"))
    ctx.verify_mode = ssl.CERT_REQUIRED
    ctx.load_verify_locations(os.path.join(certs, "teste_cert.pem"))
    srv = http.server.HTTPServer(("127.0.0.1", 0), Tratador)
    srv.socket = ctx.wrap_socket(srv.socket, server_side=True)
    print(srv.server_address[1], flush=True)
    srv.serve_forever()


if __name__ == "__main__":
    main()
