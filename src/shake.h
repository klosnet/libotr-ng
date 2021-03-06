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

#ifndef OTRNG_SHAKE_H
#define OTRNG_SHAKE_H

#include "error.h"
#include "goldilocks/shake.h"
#include "shared.h"

#define hash_init goldilocks_shake256_init
#define hash_update goldilocks_shake256_update
#define hash_final goldilocks_shake256_final
#define hash_destroy goldilocks_shake256_destroy
#define hash_hash goldilocks_shake256_hash

otrng_result
hash_init_with_usage_and_domain_separation(goldilocks_shake256_ctx_p hash,
                                           uint8_t usage, const char *domain);

otrng_result hash_init_with_usage(goldilocks_shake256_ctx_p hash,
                                  uint8_t usage);

otrng_result shake_kkdf(uint8_t *dst, size_t dst_len, const uint8_t *key,
                        size_t key_len, const uint8_t *secret,
                        size_t secret_len);

/* KDF_1("OTRv4" || usageID || values, len) */
otrng_result shake_256_kdf1(uint8_t *dst, size_t dst_len, uint8_t usage,
                            const uint8_t *values, size_t values_len);

/* KDF_1("OTR-Prekey-Server" || usageID || values, len) */
otrng_result shake_256_prekey_server_kdf(uint8_t *dst, size_t dst_len,
                                         uint8_t usage, const uint8_t *values,
                                         size_t values_len);

otrng_result shake_256_hash(uint8_t *dst, size_t dst_len, const uint8_t *secret,
                            size_t secret_len);

#ifdef OTRNG_SHAKE_PRIVATE

tstatic otrng_result hash_init_with_dom(goldilocks_shake256_ctx_p hash);

#endif

#endif
