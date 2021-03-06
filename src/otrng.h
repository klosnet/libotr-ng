/*
 *  This file is part of the Off-the-Record Next Generation Messaging
 *  library (libotr-ng).
 *
 *  Copyright (C) 2016-2018, the libotr-ng contributors.
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 2.1 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OTRNG_OTRNG_H
#define OTRNG_OTRNG_H

#include "client_profile.h"
#include "data_message.h"
#include "fragment.h"
#include "key_management.h"
#include "keys.h"
#include "prekey_ensemble.h"
#include "prekey_profile.h"
#include "protocol.h"
#include "shared.h"
#include "smp.h"
#include "str.h"
#include "v3.h"

#define MSG_PLAINTEXT 1
#define MSG_TAGGED_PLAINTEXT 2
#define MSG_QUERY_STRING 3
#define MSG_OTR_ENCODED 4
#define MSG_OTR_ERROR 5
#define QUERY_MSG_TAG_BYTES 5
#define WHITESPACE_TAG_BASE_BYTES 16
#define WHITESPACE_TAG_VERSION_BYTES 8

#define UNUSED_ARG(x) (void)(x)

#define OTRNG_INIT otrng_init(otrng_true)
#define OTRNG_FREE otrng_dh_free()

typedef struct otrng_response_s {
  string_p to_display;
  string_p to_send;
  tlv_list_s *tlvs;
  otrng_warning warning;
} otrng_response_s;

typedef struct otrng_header_s {
  uint16_t version;
  uint8_t type;
} otrng_header_s;

INTERNAL otrng_s *otrng_new(struct otrng_client_s *client,
                            otrng_policy_s policy);

INTERNAL void otrng_conn_free(/*@only@ */ otrng_s *otr);

INTERNAL otrng_result otrng_build_query_message(string_p *dst,
                                                const string_p msg,
                                                otrng_s *otr);

INTERNAL otrng_response_s *otrng_response_new(void);

INTERNAL void otrng_response_free(otrng_response_s *response);

INTERNAL otrng_result otrng_receive_message(otrng_response_s *response,
                                            otrng_warning *warn,
                                            const string_p msg, otrng_s *otr);

INTERNAL otrng_result otrng_send_message(string_p *to_send, const string_p msg,
                                         otrng_warning *warn,
                                         /*@null@*/ const tlv_list_s *tlvs,
                                         uint8_t flags, otrng_s *otr);

INTERNAL otrng_result otrng_close(string_p *to_send, otrng_s *otr);

INTERNAL otrng_result otrng_expire_session(string_p *to_send, otrng_s *otr);

API otrng_result otrng_build_whitespace_tag(string_p *whitespace_tag,
                                            const string_p msg, otrng_s *otr);

API otrng_result otrng_send_symkey_message(string_p *to_send, unsigned int use,
                                           const unsigned char *usedata,
                                           size_t usedatalen,
                                           uint8_t *extra_key, otrng_s *otr);

API otrng_result otrng_send_offline_message(char **dst,
                                            const prekey_ensemble_s *ensemble,
                                            const char *plaintext,
                                            otrng_s *otr);

API otrng_result otrng_send_non_interactive_auth(
    char **dst, const prekey_ensemble_s *ensemble, otrng_s *otr);

API otrng_result otrng_init(otrng_bool die);

INTERNAL prekey_ensemble_s *otrng_build_prekey_ensemble(otrng_s *otr);

API int otrng_get_msg_type(const string_p msg);

#ifdef OTRNG_OTRNG_PRIVATE

tstatic void otrng_destroy(otrng_s *otr);

tstatic otrng_shared_session_state_s

    tstatic
    otrng_get_shared_session_state(otrng_s *otr);

tstatic char *
otrng_generate_session_state_string(const otrng_shared_session_state_s *state);

tstatic tlv_s *process_tlv(const tlv_s *tlv, otrng_s *otr);

#endif

#endif
