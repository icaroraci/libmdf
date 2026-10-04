/* Copyright (c) 2026 Gabriel Lampa da Cunha <gabriellampa@gmail.com>
 *
 * This file is part of libmdf.
 *
 * libmdf is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libmdf is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libmdf.  If not, see <https://www.gnu.org/licenses/>.
 * */

#ifndef LIBMDF_SEFAZ_H
#define LIBMDF_SEFAZ_H

#include <stddef.h>

#include <libnfe/nfe.h>
#include <libnfe/sefaz.h>

/*
 * Webservices do MDF-e 3.00, todos na SVRS (autorizador de todas as UFs),
 * pela conexão da libnfe (nfe_sefaz_new com o certificado A1):
 *
 *   nfe_sefaz *s = nfe_sefaz_new(cert);
 *   const char *url;
 *   mdf_sefaz_endereco(NFE_AMBIENTE_HOMOLOGACAO, MDF_SERVICO_AUTORIZACAO,
 *                      &url);
 *   mdf_sefaz_autorizar(s, url, mdfe, &cstat, motivo, sizeof motivo,
 *                       &proc, &tam_proc);
 *   if (cstat == 100) ... guarde proc (mdfeProc) ...
 *
 * Cada função monta a mensagem, envia ao webservice url e devolve o cStat
 * da resposta em *cstat e o xMotivo em xmotivo (pode ser NULL; truncado
 * em tam_xmotivo, como em nfe_sefaz_cstat). Retornam 0 quando houve
 * resposta da SEFAZ, aceitando ou não o pedido, ou E_ISNULL, E_VALOR
 * (parâmetro inválido), E_REDE (ver nfe_sefaz_erro), E_XML (resposta sem
 * cStat) ou E_MALLOC. O SOAP Header (mdfeCabecMsg) não é enviado: foi
 * descontinuado no MOC 3.00b.
 */

typedef enum mdf_servico {
	MDF_SERVICO_AUTORIZACAO,   /* MDFeRecepcaoSinc */
	MDF_SERVICO_CONSULTA,      /* MDFeConsulta */
	MDF_SERVICO_STATUS,        /* MDFeStatusServico */
	MDF_SERVICO_EVENTO,        /* MDFeRecepcaoEvento */
	MDF_SERVICO_NAO_ENCERRADOS /* MDFeConsNaoEnc */
} mdf_servico;

/* Endereço do webservice na SVRS, sem acesso à rede (texto estático; não
 * libere). Fontes em docs/ENDERECOS.md. Retorna 0, E_ISNULL ou E_VALOR
 * (ambiente ou serviço inválido). */
int mdf_sefaz_endereco(nfe_ambiente amb, mdf_servico servico, const char **url);

/* Status do serviço (consStatServMDFe; 107: em operação) */
int mdf_sefaz_status(nfe_sefaz *s, const char *url, nfe_ambiente amb,
                     int *cstat, char *xmotivo, size_t tam_xmotivo);

/* Autorização síncrona do MDF-e assinado mdfe (de mdf_assinar, terminado
 * em '\0'), enviado compactado (gzip e base64). *cstat recebe o cStat do
 * protocolo (100: autorizado) ou, sem protocolo, o do retorno. Se
 * autorizado, *proc recebe o mdfeProc (MDF-e e protocolo; libere com
 * free()) e o tamanho vai em *tam_proc, se não for NULL; senão *proc fica
 * NULL. */
int mdf_sefaz_autorizar(nfe_sefaz *s, const char *url, const char *mdfe,
                        int *cstat, char *xmotivo, size_t tam_xmotivo,
                        char **proc, size_t *tam_proc);

/* Situação do MDF-e pela chave (consSitMDFe; 100: autorizado, 101:
 * cancelado, 132: encerrado). *ret recebe o retConsSitMDFe completo, com
 * o protocolo e os eventos (libere com free()), e o tamanho vai em
 * *tam_ret, se não for NULL; ret pode ser NULL. */
int mdf_sefaz_consultar(nfe_sefaz *s, const char *url, nfe_ambiente amb,
                        const char *chave, int *cstat, char *xmotivo,
                        size_t tam_xmotivo, char **ret, size_t *tam_ret);

/* Registro do evento assinado evento (<eventoMDFe> assinado, terminado em
 * '\0'). *cstat recebe o cStat do retorno do evento (135: registrado e
 * vinculado ao MDF-e). Se registrado (135 ou 136), *proc recebe o
 * procEventoMDFe (evento e retorno; libere com free()) e o tamanho vai em
 * *tam_proc, se não for NULL; senão *proc fica NULL. */
int mdf_sefaz_evento(nfe_sefaz *s, const char *url, const char *evento,
                     int *cstat, char *xmotivo, size_t tam_xmotivo, char **proc,
                     size_t *tam_proc);

/* MDF-e não encerrados do emitente com o CNPJ (14 caracteres) ou CPF (11
 * dígitos) (consMDFeNaoEnc; 111: há MDF-e não encerrados, 112: não há).
 * *ret recebe o retConsMDFeNaoEnc completo, com a chave e o protocolo de
 * cada um (infMDFe; libere com free()), e o tamanho vai em *tam_ret, se
 * não for NULL; ret pode ser NULL. */
int mdf_sefaz_nao_encerrados(nfe_sefaz *s, const char *url, nfe_ambiente amb,
                             const char *cnpj_cpf, int *cstat, char *xmotivo,
                             size_t tam_xmotivo, char **ret, size_t *tam_ret);

#endif /* LIBMDF_SEFAZ_H */
