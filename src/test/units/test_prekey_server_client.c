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

#include <glib.h>

#include "test_helpers.h"
#include "deserialize.h"

static void test_prekey_dake1_message_serialize(void) {
  const uint8_t ser_client_profile[] = {
      0x00, 0x00, 0x00, 0x05, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x02,
      0x00, 0x10, 0x05, 0x72, 0xC1, 0x4C, 0xB1, 0x30, 0x77, 0x44, 0xB9, 0x2F,
      0x38, 0x37, 0xF9, 0x96, 0x39, 0xAB, 0xBB, 0x20, 0xFF, 0xC4, 0x71, 0xD8,
      0x9D, 0x9D, 0x54, 0x53, 0x49, 0xDC, 0x70, 0x0E, 0x01, 0x27, 0x49, 0x1F,
      0x06, 0x13, 0x14, 0xFA, 0xF8, 0x9A, 0x85, 0xC7, 0x07, 0x60, 0xBD, 0x01,
      0x88, 0xA5, 0x66, 0x9D, 0x1A, 0x43, 0x93, 0xF0, 0x83, 0x4B, 0x80, 0x00,
      0x03, 0x00, 0x12, 0x98, 0x97, 0x31, 0xEE, 0xBB, 0x0A, 0x1B, 0xA5, 0xA6,
      0x90, 0x43, 0xC8, 0xC1, 0x25, 0x16, 0xB1, 0x68, 0xBE, 0xA1, 0x23, 0x74,
      0x65, 0x4B, 0x04, 0xE8, 0xB3, 0xD3, 0x85, 0x93, 0xBA, 0x37, 0x0B, 0x07,
      0x1A, 0x4C, 0xBE, 0x3F, 0x20, 0x8E, 0xE1, 0xE2, 0x0E, 0x97, 0x7D, 0x61,
      0xE5, 0x1F, 0xFC, 0xCA, 0x7F, 0x87, 0x15, 0x0C, 0x18, 0xA5, 0xFC, 0x00,
      0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x34, 0x00, 0x00, 0x05, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x4C, 0x2B, 0x42, 0x40, 0x35,
      0xDF, 0x51, 0xC7, 0x0C, 0x6A, 0xA9, 0x3E, 0x99, 0x15, 0x63, 0x32, 0xBA,
      0xC3, 0x19, 0x22, 0x7B, 0x2E, 0x35, 0x54, 0x43, 0xFA, 0xDB, 0xBB, 0xEF,
      0x32, 0x26, 0xAD, 0xE5, 0xE4, 0xD2, 0x45, 0x3A, 0xB2, 0xFE, 0x61, 0x9F,
      0x76, 0x00, 0x02, 0x83, 0x53, 0xEA, 0x78, 0xDA, 0x79, 0x44, 0xDC, 0x6A,
      0x95, 0x1F, 0x80, 0xBC, 0x47, 0x3B, 0x23, 0xD7, 0x7B, 0xD5, 0x78, 0x89,
      0xCA, 0x4C, 0xDB, 0xFF, 0x0E, 0x34, 0xF8, 0x5F, 0x11, 0xD4, 0xF0, 0xFE,
      0xA9, 0x93, 0xDE, 0x5E, 0x3A, 0x25, 0xEE, 0x9D, 0x2C, 0x59, 0x25, 0x5F,
      0xAF, 0xE7, 0x75, 0xC7, 0x0F, 0x6C, 0x93, 0xA6, 0x8B, 0xD2, 0xB7, 0x6C,
      0xA4, 0x6D, 0xCD, 0xB7, 0x10, 0x5A, 0x00, 0x8A, 0x1D, 0x4A, 0x07, 0x00,
  };

  const uint8_t ser_i[] = {
      0x26, 0xcf, 0xec, 0x88, 0x85, 0x11, 0x4a, 0x5f, 0x79, 0xf4, 0x2c, 0xd1,
      0x15, 0x65, 0x23, 0xe7, 0x9a, 0xa3, 0x27, 0xff, 0x56, 0xb7, 0xae, 0xac,
      0x89, 0x4e, 0x2d, 0x9e, 0xfa, 0x29, 0xc9, 0xba, 0x8d, 0x55, 0xc1, 0x23,
      0xd1, 0x4c, 0xc0, 0x9a, 0x5e, 0x70, 0x9a, 0x5c, 0x77, 0x18, 0xe1, 0x8f,
      0xeb, 0x57, 0xd3, 0x8d, 0x6,  0xf4, 0xfb, 0x27, 0x0};

  otrng_prekey_dake1_message_s msg[1];
  msg->client_instance_tag = 0x56781234;
  otrng_assert_is_success(
      otrng_client_profile_deserialize(msg->client_profile, ser_client_profile,
                                       sizeof(ser_client_profile), NULL));
  otrng_assert_is_success(
      otrng_deserialize_ec_point(msg->I, ser_i, sizeof(ser_i)));

  uint8_t header[] = {
      0x00, 0x04,             // protocol version
      0x35,                   // message type
      0x56, 0x78, 0x12, 0x34, // instance tag
  };

  uint8_t *dst = NULL;
  size_t dstlen = 0;
  otrng_assert_is_success(
      otrng_prekey_dake1_message_asprint(&dst, &dstlen, msg));
  otrng_prekey_dake1_message_destroy(msg);

  size_t w = 0;
  otrng_assert_cmpmem(dst, header, sizeof(header));
  w += sizeof(header);

  otrng_assert_cmpmem(dst + w, ser_client_profile, sizeof(ser_client_profile));
  w += sizeof(ser_client_profile);

  otrng_assert_cmpmem(dst + w, ser_i, sizeof(ser_i));
  free(dst);
}

static void test_prekey_dake2_message_deserialize(void) {
  uint8_t serialized[] = {
      0x00, 0x04,             // protocol version
      0x36,                   // message type
      0x7e, 0x5a, 0x9a, 0x61, // instance tag

      // PREKEY-SERVER-COMP-ID
      0x00, 0x00, 0x00, 0x17, // len
      0x70, 0x72, 0x65, 0x6b, 0x65, 0x79, 0x73, 0x2e, 0x74, 0x68, 0x61, 0x74,
      0x73, 0x6e, 0x6f, 0x74, 0x6d, 0x79, 0x2e, 0x77, 0x6f, 0x72, 0x6b,

      // ED448-PUBKEY
      0x00, 0x10, // pubkey type
      0x57, 0xd5, 0x5a, 0x70, 0x2b, 0xc9, 0xcb, 0x5f, 0x43, 0x42, 0xc0, 0x1b,
      0x7b, 0x60, 0x22, 0x27, 0x7c, 0x99, 0xf3, 0x3a, 0x6e, 0xd5, 0x01, 0x5f,
      0x4c, 0x0b, 0x10, 0x0a, 0x46, 0xc7, 0xc6, 0xc0, 0x97, 0x9d, 0xb9, 0x2f,
      0x9f, 0x35, 0xa5, 0x1c, 0x77, 0x2b, 0x77, 0xa0, 0x90, 0x76, 0x2d, 0xaf,
      0xf3, 0x90, 0x46, 0x21, 0xfb, 0x2c, 0xb8, 0x94, 0x00,

      // S
      0xc0, 0x3d, 0xc6, 0x1f, 0x8b, 0x2e, 0xae, 0x34, 0x6e, 0x05, 0xa8, 0x42,
      0xa2, 0x73, 0xfc, 0x25, 0x3c, 0x9f, 0xcb, 0x49, 0xf1, 0x80, 0x12, 0xc5,
      0xaa, 0x76, 0x57, 0x58, 0x3f, 0xd2, 0xa9, 0x5b, 0x5d, 0x5e, 0x2c, 0xb2,
      0xc6, 0x84, 0xff, 0x9c, 0x3a, 0x5f, 0x53, 0x0b, 0x9d, 0x26, 0x2f, 0xc5,
      0x4f, 0x16, 0x95, 0x06, 0xba, 0xa1, 0x54, 0xc4, 0x00,

      // sigma
      0xec, 0x3c, 0xf6, 0x13, 0xdc, 0xe5, 0xfa, 0xfe, 0x9b, 0xa3, 0x25, 0x33,
      0x93, 0x3d, 0x8a, 0xb0, 0x64, 0x03, 0x2f, 0xc5, 0x8c, 0x04, 0xdc, 0xd8,
      0x15, 0xb2, 0x77, 0x9e, 0x94, 0x63, 0xe2, 0x4d, 0x25, 0x41, 0xec, 0x8f,
      0x0a, 0x8e, 0x98, 0x1b, 0xfe, 0xad, 0x92, 0x13, 0x90, 0x01, 0x77, 0xde,
      0xaf, 0x7a, 0x32, 0xf5, 0x9b, 0xec, 0xb2, 0x2c, 0x08, 0x2d, 0xcf, 0x24,
      0x05, 0x56, 0xc4, 0xa1, 0x5c, 0x0f, 0xe4, 0xc5, 0x20, 0xcb, 0xa1, 0xdf,
      0x06, 0x06, 0x40, 0x8e, 0xe0, 0x35, 0xa6, 0x5e, 0x40, 0xa9, 0x99, 0xaf,
      0x00, 0xf2, 0x15, 0x59, 0x80, 0xb6, 0x88, 0x1b, 0xae, 0x72, 0xb2, 0x7c,
      0x98, 0xf5, 0x30, 0xa0, 0x1e, 0x98, 0xa0, 0x6d, 0x7d, 0x15, 0xb3, 0x8c,
      0xd6, 0x9b, 0x94, 0x3e, 0xd8, 0xbc, 0x6f, 0x24, 0x8c, 0xd0, 0xdb, 0xd0,
      0x6d, 0x5b, 0x2a, 0xb1, 0x1f, 0xd3, 0xd7, 0xf8, 0xc3, 0x11, 0x9a, 0xaa,
      0xef, 0xc4, 0x59, 0xab, 0xa1, 0xfc, 0x47, 0xf9, 0x62, 0x70, 0x98, 0x60,
      0x3d, 0x9c, 0x96, 0x27, 0x2b, 0xe7, 0x80, 0x59, 0x1a, 0xe5, 0x0c, 0x98,
      0x98, 0xbd, 0x30, 0xa6, 0xba, 0x6c, 0x7a, 0x28, 0xd3, 0x6a, 0xf7, 0x16,
      0x8f, 0xa6, 0xd5, 0x75, 0xb4, 0x9a, 0x17, 0x91, 0x19, 0x26, 0x9e, 0x3b,
      0x51, 0x61, 0x07, 0xbd, 0x17, 0x91, 0xf5, 0xaa, 0xce, 0x6a, 0xd4, 0x89,
      0xbc, 0xb1, 0xd7, 0x8d, 0x55, 0x6c, 0x19, 0xe4, 0x1f, 0x5f, 0x88, 0x54,
      0x3b, 0x98, 0x1f, 0x54, 0x82, 0x12, 0x6b, 0x7f, 0x46, 0x53, 0x20, 0x21,
      0xfa, 0xd9, 0x98, 0x85, 0x45, 0x0a, 0x99, 0x14, 0xac, 0x7f, 0x1f, 0xe0,
      0xa0, 0x97, 0x1a, 0x81, 0xff, 0x40, 0x21, 0xe2, 0x3c, 0x21, 0xf3, 0x7d,
      0xb3, 0x11, 0x9d, 0x16, 0x08, 0x3f, 0x9e, 0x1f, 0xb7, 0xd4, 0x26, 0x19,
      0xe5, 0x15, 0xc7, 0x2c, 0x44, 0x31, 0x73, 0x87, 0x3e, 0x0c, 0x5d, 0x2d,
      0x6e, 0xe5, 0x20, 0x3a, 0x1a, 0x6b, 0xb4, 0x73, 0x80, 0x58, 0x8a, 0x59,
      0xcb, 0xa4, 0x62, 0x2f, 0x6f, 0xa0, 0x51, 0x26, 0xf8, 0xfa, 0x54, 0xa0,
      0xd5, 0xb1, 0xc9, 0x4f, 0xa5, 0x4e, 0x9a, 0x5e, 0x4f, 0x51, 0x5a, 0x8a,
      0x41, 0x3a, 0x79, 0x5f, 0xe1, 0xfe, 0x81, 0xac, 0x11, 0xc6, 0xa4, 0x6e,
      0x89, 0xe5, 0x77, 0xb8, 0x1a, 0xa3, 0xab, 0x94, 0xe1, 0x2e, 0x78, 0xf7,
      0x3d, 0x87, 0x43, 0x34, 0x94, 0xd9, 0xef, 0xb9, 0xf8, 0x94, 0x25, 0x32};

  otrng_prekey_dake2_message_s dst;
  otrng_prekey_dake2_message_init(&dst);
  otrng_assert_is_success(otrng_prekey_dake2_message_deserialize(
      &dst, serialized, sizeof(serialized)));

  g_assert_cmpint(dst.client_instance_tag, ==, 0x7e5a9a61);
  // TODO: check the identity from PREKEY-SERVER-COMP-ID
  // TODO: check the fingerprint of the long-term pub key

  otrng_prekey_dake2_message_destroy(&dst);
}

static void test_prekey_dake3_message_serialize(void) {
  uint8_t sigma_ser[] = {
      0xec, 0x3c, 0xf6, 0x13, 0xdc, 0xe5, 0xfa, 0xfe, 0x9b, 0xa3, 0x25, 0x33,
      0x93, 0x3d, 0x8a, 0xb0, 0x64, 0x03, 0x2f, 0xc5, 0x8c, 0x04, 0xdc, 0xd8,
      0x15, 0xb2, 0x77, 0x9e, 0x94, 0x63, 0xe2, 0x4d, 0x25, 0x41, 0xec, 0x8f,
      0x0a, 0x8e, 0x98, 0x1b, 0xfe, 0xad, 0x92, 0x13, 0x90, 0x01, 0x77, 0xde,
      0xaf, 0x7a, 0x32, 0xf5, 0x9b, 0xec, 0xb2, 0x2c, 0x08, 0x2d, 0xcf, 0x24,
      0x05, 0x56, 0xc4, 0xa1, 0x5c, 0x0f, 0xe4, 0xc5, 0x20, 0xcb, 0xa1, 0xdf,
      0x06, 0x06, 0x40, 0x8e, 0xe0, 0x35, 0xa6, 0x5e, 0x40, 0xa9, 0x99, 0xaf,
      0x00, 0xf2, 0x15, 0x59, 0x80, 0xb6, 0x88, 0x1b, 0xae, 0x72, 0xb2, 0x7c,
      0x98, 0xf5, 0x30, 0xa0, 0x1e, 0x98, 0xa0, 0x6d, 0x7d, 0x15, 0xb3, 0x8c,
      0xd6, 0x9b, 0x94, 0x3e, 0xd8, 0xbc, 0x6f, 0x24, 0x8c, 0xd0, 0xdb, 0xd0,
      0x6d, 0x5b, 0x2a, 0xb1, 0x1f, 0xd3, 0xd7, 0xf8, 0xc3, 0x11, 0x9a, 0xaa,
      0xef, 0xc4, 0x59, 0xab, 0xa1, 0xfc, 0x47, 0xf9, 0x62, 0x70, 0x98, 0x60,
      0x3d, 0x9c, 0x96, 0x27, 0x2b, 0xe7, 0x80, 0x59, 0x1a, 0xe5, 0x0c, 0x98,
      0x98, 0xbd, 0x30, 0xa6, 0xba, 0x6c, 0x7a, 0x28, 0xd3, 0x6a, 0xf7, 0x16,
      0x8f, 0xa6, 0xd5, 0x75, 0xb4, 0x9a, 0x17, 0x91, 0x19, 0x26, 0x9e, 0x3b,
      0x51, 0x61, 0x07, 0xbd, 0x17, 0x91, 0xf5, 0xaa, 0xce, 0x6a, 0xd4, 0x89,
      0xbc, 0xb1, 0xd7, 0x8d, 0x55, 0x6c, 0x19, 0xe4, 0x1f, 0x5f, 0x88, 0x54,
      0x3b, 0x98, 0x1f, 0x54, 0x82, 0x12, 0x6b, 0x7f, 0x46, 0x53, 0x20, 0x21,
      0xfa, 0xd9, 0x98, 0x85, 0x45, 0x0a, 0x99, 0x14, 0xac, 0x7f, 0x1f, 0xe0,
      0xa0, 0x97, 0x1a, 0x81, 0xff, 0x40, 0x21, 0xe2, 0x3c, 0x21, 0xf3, 0x7d,
      0xb3, 0x11, 0x9d, 0x16, 0x08, 0x3f, 0x9e, 0x1f, 0xb7, 0xd4, 0x26, 0x19,
      0xe5, 0x15, 0xc7, 0x2c, 0x44, 0x31, 0x73, 0x87, 0x3e, 0x0c, 0x5d, 0x2d,
      0x6e, 0xe5, 0x20, 0x3a, 0x1a, 0x6b, 0xb4, 0x73, 0x80, 0x58, 0x8a, 0x59,
      0xcb, 0xa4, 0x62, 0x2f, 0x6f, 0xa0, 0x51, 0x26, 0xf8, 0xfa, 0x54, 0xa0,
      0xd5, 0xb1, 0xc9, 0x4f, 0xa5, 0x4e, 0x9a, 0x5e, 0x4f, 0x51, 0x5a, 0x8a,
      0x41, 0x3a, 0x79, 0x5f, 0xe1, 0xfe, 0x81, 0xac, 0x11, 0xc6, 0xa4, 0x6e,
      0x89, 0xe5, 0x77, 0xb8, 0x1a, 0xa3, 0xab, 0x94, 0xe1, 0x2e, 0x78, 0xf7,
      0x3d, 0x87, 0x43, 0x34, 0x94, 0xd9, 0xef, 0xb9, 0xf8, 0x94, 0x25, 0x32};

  otrng_prekey_dake3_message_s msg;
  otrng_prekey_dake3_message_init(&msg);
  msg.client_instance_tag = 0x56781234;
  otrng_assert_is_success(otrng_deserialize_ring_sig(msg.sigma, sigma_ser,
                                                     sizeof(sigma_ser), NULL));

  msg.message = (uint8_t *)otrng_xstrdup("hi");
  msg.message_len = 3;

  uint8_t header[] = {
      0x00, 0x04,             // protocol version
      0x37,                   // message type
      0x56, 0x78, 0x12, 0x34, // instance tag
  };

  uint8_t *dst = NULL;
  size_t dstlen = 0;
  otrng_assert_is_success(
      otrng_prekey_dake3_message_asprint(&dst, &dstlen, &msg));
  otrng_prekey_dake3_message_destroy(&msg);

  size_t w = 0;
  otrng_assert_cmpmem(dst, header, sizeof(header));
  w += sizeof(header);

  otrng_assert_cmpmem(dst + w, sigma_ser, sizeof(sigma_ser));
  w += sizeof(sigma_ser);

  // DATA (len)
  g_assert_cmpint(*(dst + w++), ==, 0);
  g_assert_cmpint(*(dst + w++), ==, 0);
  g_assert_cmpint(*(dst + w++), ==, 0);
  g_assert_cmpint(*(dst + w++), ==, 0x3);

  // DATA (val)
  otrng_assert_cmpmem(dst + w, "hi", 3);
  free(dst);
}

static void test_prekey_dake3_message_append_storage_info_req(void) {
  otrng_prekey_dake3_message_s msg;
  otrng_prekey_dake3_message_init(&msg);

  uint8_t prekey_mac[64] = {
      0x26, 0xcf, 0xec, 0x88, 0x85, 0x11, 0x4a, 0x5f, 0x79, 0xf4, 0x2c,
      0xd1, 0x26, 0xcf, 0xec, 0x88, 0x85, 0x11, 0x4a, 0x5f, 0x79, 0xf4,
      0x2c, 0xd1, 0x26, 0xcf, 0xec, 0x88, 0x85, 0x11, 0x4a, 0x5f, 0x79,
      0xf4, 0x2c, 0xd1, 0x26, 0xcf, 0xec, 0x88, 0x85, 0x11, 0x4a, 0x5f,
      0x79, 0xf4, 0x2c, 0xd1, 0x26, 0xcf, 0xec, 0x88, 0x85, 0x11, 0xf4,
      0x2c, 0xd1, 0x26, 0xcf, 0xec, 0x88, 0x85, 0x11, 0x0};

  uint8_t expected[] = {
      // protocol version
      0x0, 0x4,
      // type
      0x09,

      // MAC
      0x4a, 0x7d, 0x67, 0xe2, 0xe1, 0xe5, 0x01, 0x57, 0x81, 0x73, 0xf0, 0x2d,
      0xa3, 0xc4, 0xc9, 0x99, 0x73, 0x4b, 0x11, 0x42, 0x53, 0xe6, 0xe0, 0xb9,
      0x3e, 0x78, 0x7f, 0x42, 0x35, 0xa8, 0xe6, 0x91, 0x6b, 0x8c, 0xf3, 0x6c,
      0x5f, 0x3d, 0x97, 0x3b, 0x6d, 0x91, 0x37, 0x48, 0x20, 0x28, 0x65, 0x71,
      0x08, 0x28, 0x55, 0x14, 0x94, 0xf6, 0x29, 0xf7, 0xe5, 0x0c, 0x8b, 0x16,
      0x61, 0xfb, 0x97, 0x88

  };

  otrng_assert_is_success(
      otrng_prekey_dake3_message_append_storage_information_request(
          &msg, prekey_mac));

  g_assert_cmpint(msg.message_len, ==, sizeof(expected));
  otrng_assert_cmpmem(msg.message, expected, sizeof(expected));

  otrng_prekey_dake3_message_destroy(&msg);
}

static void test_prekey_storage_status_message_deserialize(void) {
  uint8_t serialized[] = {
      // protocol version
      0x00, 0x04,

      // message type
      0x0b,

      // instance tag
      0x7e, 0x5a, 0x9a, 0x61,

      // number of messages
      0x00, 0x00, 0x00, 0x00,

      // MAC
      0x59, 0xce, 0x0a, 0x6b, 0x9e, 0x8b, 0x0d, 0xe6, 0x90, 0x84, 0x65, 0xe2,
      0xc1, 0x8d, 0xb6, 0x52, 0x92, 0xb7, 0x18, 0xf8, 0xca, 0xa1, 0x3b, 0x2f,
      0x7d, 0xb0, 0xf7, 0x1b, 0x26, 0x64, 0x0b, 0x89, 0x7c, 0xa5, 0xc5, 0xb7,
      0xb4, 0x2a, 0xd6, 0xb3, 0x7f, 0xae, 0x5e, 0xab, 0x3a, 0x23, 0x7c, 0x04,
      0x39, 0x51, 0x15, 0x6e, 0xf6, 0xea, 0x99, 0x97, 0xdb, 0xf3, 0x8d, 0xe9,
      0xb8, 0xae, 0x46, 0x9e};

  otrng_prekey_storage_status_message_s msg[1];
  otrng_assert_is_success(otrng_prekey_storage_status_message_deserialize(
      msg, serialized, sizeof(serialized)));

  g_assert_cmpint(msg->client_instance_tag, ==, 0x7e5a9a61);
  g_assert_cmpint(msg->stored_prekeys, ==, 0x0);
  otrng_assert_cmpmem(msg->mac, serialized + 11, sizeof(msg->mac));

  otrng_prekey_storage_status_message_destroy(msg);
}

static void test_prekey_ensemble_retrieval_message_deserialize(void) {
  uint8_t serialized[] = {
      // protocol version
      0x00, 0x04,
      // message type
      0x13,
      // instance tag
      0x0e, 0xee, 0x86, 0xa6,
      // L
      0x02,

      // Ensemble 1
      // Client Profile
      0x00, 0x00, 0x00, 0x04, 0x00, 0x01, 0x0e, 0xee, 0x86, 0xa6, 0x00, 0x02,
      0x00, 0x10, 0xc5, 0x3f, 0xeb, 0xe1, 0xd4, 0xd5, 0xab, 0xb8, 0x8b, 0xbe,
      0xbb, 0xdb, 0x70, 0x67, 0xb9, 0x8d, 0x76, 0xa5, 0xa6, 0xd4, 0x4b, 0x84,
      0x82, 0xca, 0x93, 0x0b, 0xa3, 0x6d, 0x11, 0x70, 0x21, 0xec, 0x8c, 0xe1,
      0xec, 0x55, 0xd7, 0x19, 0xad, 0x30, 0x95, 0xa9, 0x9e, 0x27, 0x70, 0x08,
      0x3b, 0x1c, 0xdb, 0x09, 0x22, 0x5f, 0xf6, 0x37, 0x9b, 0xb6, 0x80, 0x00,
      0x04, 0x00, 0x00, 0x00, 0x03, 0x33, 0x34, 0x00, 0x00, 0x05, 0x00, 0x00,
      0x00, 0x00, 0x5b, 0x7d, 0xc0, 0xa6, 0xa1, 0x2a, 0x86, 0xab, 0xef, 0x8a,
      0x1a, 0x3a, 0x31, 0xa2, 0x75, 0x8a, 0x78, 0xb5, 0xc5, 0xa9, 0x50, 0xba,
      0xb6, 0x22, 0x6d, 0xfe, 0x76, 0x20, 0xa7, 0xee, 0x31, 0xe7, 0x38, 0x92,
      0xe5, 0x8e, 0xee, 0xdc, 0xb5, 0x4b, 0xd0, 0x9c, 0xfe, 0x05, 0x28, 0x6d,
      0x38, 0x1b, 0x28, 0x09, 0x99, 0x31, 0x2c, 0x4c, 0x97, 0xd5, 0x77, 0xfa,
      0x26, 0x8b, 0x80, 0x55, 0x3e, 0xf3, 0x6f, 0xb1, 0xf9, 0xe2, 0x55, 0x17,
      0xc3, 0x03, 0x44, 0x81, 0x52, 0x5b, 0xa1, 0x15, 0x29, 0xe9, 0x2b, 0xd9,
      0x97, 0xe0, 0x43, 0x6f, 0xf3, 0xa0, 0x53, 0x0b, 0x37, 0x2f, 0xdf, 0xa7,
      0xba, 0x5b, 0x8f, 0x28, 0x60, 0x1d, 0xc1, 0xf8, 0xc5, 0x23, 0xa0, 0x32,
      0x07, 0xad, 0x49, 0xb3, 0x67, 0x52, 0xdf, 0x45, 0x47, 0x62, 0x30, 0x00,
      // Prekey profile
      0x0e, 0xee, 0x86, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x5b, 0x94, 0x14, 0xe4,
      0x00, 0x11, 0x45, 0x25, 0x33, 0x2e, 0xb4, 0xf3, 0xc0, 0x6d, 0xd6, 0xe6,
      0xf9, 0xb9, 0x96, 0xc5, 0x5d, 0x32, 0x79, 0xe3, 0xae, 0xce, 0x03, 0x5e,
      0x89, 0x0e, 0x0d, 0xb9, 0xd4, 0x5a, 0x79, 0x1b, 0x9a, 0xab, 0x33, 0xf7,
      0x87, 0xf6, 0xd0, 0x98, 0x41, 0x94, 0x4c, 0x3d, 0xd5, 0x52, 0x2e, 0x7a,
      0xd8, 0x5a, 0xbd, 0x71, 0xec, 0x0f, 0xc7, 0xe8, 0x66, 0x92, 0x00, 0xa8,
      0xaf, 0x97, 0xfb, 0x7c, 0x81, 0x67, 0x20, 0x80, 0x40, 0xf3, 0x71, 0x87,
      0xd6, 0x4e, 0x60, 0x24, 0xcf, 0x3d, 0x6d, 0x6a, 0x37, 0xbf, 0x7c, 0x34,
      0xef, 0xa5, 0xf9, 0x00, 0xb2, 0x87, 0xff, 0xc2, 0x60, 0xe4, 0xf1, 0x79,
      0x95, 0xc2, 0x94, 0xc9, 0xe0, 0x3f, 0xea, 0x41, 0x9f, 0x04, 0xbf, 0x0b,
      0x6b, 0x9a, 0x39, 0xfe, 0x0b, 0x4f, 0xeb, 0x00, 0x0e, 0x3d, 0xd7, 0xe6,
      0x45, 0xe0, 0x37, 0xeb, 0x45, 0x16, 0x49, 0xbc, 0xda, 0xb7, 0x49, 0x9c,
      0x1f, 0xd9, 0x1f, 0x85, 0x59, 0x03, 0x00, 0xda, 0x52, 0xaa, 0x0a, 0x46,
      0xd7, 0x9f, 0xce, 0xf0, 0xe1, 0xd5, 0x9a, 0xd1, 0x55, 0x7d, 0x41, 0x8f,
      0x0f, 0x8d, 0xce, 0x25, 0x80, 0xa6, 0x82, 0xc3, 0xc9, 0xd6, 0xc3, 0x55,
      0xd8, 0xf0, 0x8b, 0x02, 0x00,
      // Prekey message
      0x00, 0x04, 0x0f, 0x33, 0x6e, 0xba, 0x12, 0x0e, 0xee, 0x86, 0xa6, 0x75,
      0x0f, 0xfc, 0xd3, 0xf7, 0xbb, 0x2d, 0x1d, 0x4b, 0x17, 0x8a, 0xed, 0x3b,
      0x55, 0xd0, 0xf7, 0xbe, 0xaa, 0xb3, 0x7f, 0x89, 0xa0, 0xcf, 0x20, 0x31,
      0xc8, 0xc1, 0xae, 0xa9, 0x76, 0x2e, 0x08, 0xf9, 0x95, 0x8b, 0x99, 0xf8,
      0x8e, 0xc0, 0xc0, 0x4f, 0xcc, 0xef, 0xce, 0x82, 0x6b, 0x07, 0xe9, 0x39,
      0xc9, 0x11, 0x4d, 0x0a, 0x4b, 0xee, 0xcc, 0x80, 0x00, 0x00, 0x01, 0x80,
      0x2f, 0x92, 0x39, 0x25, 0x73, 0xbb, 0x82, 0x85, 0xe1, 0x1a, 0x24, 0x5e,
      0xf0, 0x49, 0xaf, 0x36, 0xba, 0x45, 0x06, 0xe3, 0x71, 0xb5, 0xa0, 0xbe,
      0x9c, 0xc0, 0xa7, 0xf4, 0xf2, 0x17, 0xbf, 0xfb, 0x76, 0xca, 0xa8, 0xf3,
      0x68, 0xf2, 0xdd, 0x6e, 0x77, 0x41, 0x44, 0x41, 0xfa, 0x55, 0xba, 0x41,
      0x81, 0xe9, 0xeb, 0x6e, 0x26, 0xb9, 0x68, 0x26, 0x7c, 0x38, 0x4f, 0x71,
      0xf1, 0xac, 0x18, 0xd2, 0x1e, 0x7d, 0x4b, 0x06, 0xea, 0x18, 0x38, 0x2d,
      0x9e, 0xf1, 0x4e, 0xa2, 0x3b, 0x3f, 0x3c, 0xd0, 0xb6, 0xe6, 0x6f, 0xbc,
      0x54, 0xf6, 0x44, 0x31, 0xa8, 0xd5, 0x56, 0xec, 0x49, 0x5e, 0xee, 0x68,
      0x1a, 0x76, 0x1b, 0x1a, 0xf9, 0x04, 0xea, 0x1e, 0x53, 0x16, 0xa3, 0x99,
      0x3a, 0xc1, 0xcc, 0x08, 0x7c, 0xd8, 0xd1, 0xfb, 0x56, 0x44, 0xe9, 0x1a,
      0xc9, 0x88, 0x25, 0x23, 0xb4, 0xfb, 0x8f, 0x6b, 0xad, 0xbb, 0x64, 0x15,
      0xb5, 0x9d, 0x54, 0xcb, 0x7b, 0xe8, 0xff, 0xcb, 0x1d, 0x5c, 0xbc, 0xe2,
      0xb8, 0x10, 0xe8, 0xa3, 0xe1, 0xbc, 0xe2, 0xd1, 0xa7, 0x33, 0x06, 0x3f,
      0x83, 0x41, 0x02, 0xc7, 0x48, 0xea, 0x47, 0xbb, 0x19, 0x92, 0xbc, 0xb5,
      0x39, 0xa2, 0xcc, 0xfc, 0xda, 0x5c, 0x16, 0x3b, 0xd5, 0x6e, 0x7f, 0x1d,
      0x0f, 0x68, 0xef, 0xd6, 0x8b, 0xb8, 0xaa, 0xa6, 0xe9, 0x23, 0xfc, 0x8e,
      0xc1, 0x66, 0xd6, 0x2d, 0x6e, 0x0a, 0x2d, 0xd9, 0x63, 0x47, 0xa3, 0x59,
      0x29, 0x23, 0x7b, 0xf2, 0x25, 0x58, 0xd0, 0xb0, 0x0a, 0x2b, 0x3b, 0x62,
      0x59, 0x9b, 0xe9, 0x91, 0xa2, 0xed, 0xbb, 0xe8, 0x87, 0xa3, 0x31, 0xae,
      0x1e, 0xa4, 0x7b, 0xb1, 0x95, 0x8e, 0x93, 0x1b, 0x10, 0x30, 0xc8, 0xfc,
      0xa9, 0xcc, 0x3c, 0x72, 0xf3, 0xe1, 0xa9, 0xc8, 0x96, 0x28, 0xf1, 0xba,
      0x46, 0x93, 0x69, 0x6e, 0x4b, 0x32, 0x71, 0x49, 0x11, 0x37, 0x21, 0x17,
      0x97, 0xd2, 0x7b, 0xe2, 0x5f, 0x7b, 0xbd, 0x48, 0xb5, 0xf0, 0xa1, 0x70,
      0x1e, 0x88, 0x2a, 0x09, 0x5b, 0x9e, 0xae, 0x97, 0x6a, 0xa6, 0xe1, 0x30,
      0x89, 0x24, 0x76, 0x57, 0xb4, 0x0e, 0xc0, 0x5d, 0x6f, 0x74, 0xbf, 0x1d,
      0x15, 0x4b, 0xfa, 0xf5, 0x9b, 0x0a, 0xd3, 0xec, 0xb7, 0xc6, 0x12, 0xeb,
      0x74, 0xb2, 0xa7, 0x0e, 0x20, 0xf4, 0xaa, 0x48, 0xf8, 0xf7, 0x4f, 0xb3,
      0x9d, 0x66, 0xac, 0x03, 0x8b, 0xa2, 0x94, 0x1f, 0x80, 0xb3, 0x74, 0x2c,
      0x28, 0x5b, 0x7f, 0xa3, 0xc7, 0x4b, 0x41, 0x31, 0xcf, 0x16, 0x0f, 0xee,
      0x43, 0x56, 0x6c, 0x59, 0xdb, 0x90, 0xcc, 0x3c, 0xaa, 0xfc, 0xb3, 0x88,
      0x25, 0x6f, 0x72, 0xcf, 0xb5, 0x81, 0xc9, 0x02, 0x6b, 0x9d, 0xd2, 0x7b,
      0x78, 0xab, 0x2f, 0x39, 0xcd, 0x83, 0x82, 0x1b, 0xf7, 0x78, 0x92, 0x80,

      // Ensemble 2
      // Client Profile
      0x00, 0x00, 0x00, 0x04, 0x00, 0x01, 0x0e, 0xee, 0x86, 0xa6, 0x00, 0x02,
      0x00, 0x10, 0xc5, 0x3f, 0xeb, 0xe1, 0xd4, 0xd5, 0xab, 0xb8, 0x8b, 0xbe,
      0xbb, 0xdb, 0x70, 0x67, 0xb9, 0x8d, 0x76, 0xa5, 0xa6, 0xd4, 0x4b, 0x84,
      0x82, 0xca, 0x93, 0x0b, 0xa3, 0x6d, 0x11, 0x70, 0x21, 0xec, 0x8c, 0xe1,
      0xec, 0x55, 0xd7, 0x19, 0xad, 0x30, 0x95, 0xa9, 0x9e, 0x27, 0x70, 0x08,
      0x3b, 0x1c, 0xdb, 0x09, 0x22, 0x5f, 0xf6, 0x37, 0x9b, 0xb6, 0x80, 0x00,
      0x04, 0x00, 0x00, 0x00, 0x03, 0x33, 0x34, 0x00, 0x00, 0x05, 0x00, 0x00,
      0x00, 0x00, 0x5b, 0x7d, 0xc0, 0xa6, 0xa1, 0x2a, 0x86, 0xab, 0xef, 0x8a,
      0x1a, 0x3a, 0x31, 0xa2, 0x75, 0x8a, 0x78, 0xb5, 0xc5, 0xa9, 0x50, 0xba,
      0xb6, 0x22, 0x6d, 0xfe, 0x76, 0x20, 0xa7, 0xee, 0x31, 0xe7, 0x38, 0x92,
      0xe5, 0x8e, 0xee, 0xdc, 0xb5, 0x4b, 0xd0, 0x9c, 0xfe, 0x05, 0x28, 0x6d,
      0x38, 0x1b, 0x28, 0x09, 0x99, 0x31, 0x2c, 0x4c, 0x97, 0xd5, 0x77, 0xfa,
      0x26, 0x8b, 0x80, 0x55, 0x3e, 0xf3, 0x6f, 0xb1, 0xf9, 0xe2, 0x55, 0x17,
      0xc3, 0x03, 0x44, 0x81, 0x52, 0x5b, 0xa1, 0x15, 0x29, 0xe9, 0x2b, 0xd9,
      0x97, 0xe0, 0x43, 0x6f, 0xf3, 0xa0, 0x53, 0x0b, 0x37, 0x2f, 0xdf, 0xa7,
      0xba, 0x5b, 0x8f, 0x28, 0x60, 0x1d, 0xc1, 0xf8, 0xc5, 0x23, 0xa0, 0x32,
      0x07, 0xad, 0x49, 0xb3, 0x67, 0x52, 0xdf, 0x45, 0x47, 0x62, 0x30, 0x00,
      // Prekey profile
      0x0e, 0xee, 0x86, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x5b, 0x94, 0x14, 0xe4,
      0x00, 0x11, 0x45, 0x25, 0x33, 0x2e, 0xb4, 0xf3, 0xc0, 0x6d, 0xd6, 0xe6,
      0xf9, 0xb9, 0x96, 0xc5, 0x5d, 0x32, 0x79, 0xe3, 0xae, 0xce, 0x03, 0x5e,
      0x89, 0x0e, 0x0d, 0xb9, 0xd4, 0x5a, 0x79, 0x1b, 0x9a, 0xab, 0x33, 0xf7,
      0x87, 0xf6, 0xd0, 0x98, 0x41, 0x94, 0x4c, 0x3d, 0xd5, 0x52, 0x2e, 0x7a,
      0xd8, 0x5a, 0xbd, 0x71, 0xec, 0x0f, 0xc7, 0xe8, 0x66, 0x92, 0x00, 0xa8,
      0xaf, 0x97, 0xfb, 0x7c, 0x81, 0x67, 0x20, 0x80, 0x40, 0xf3, 0x71, 0x87,
      0xd6, 0x4e, 0x60, 0x24, 0xcf, 0x3d, 0x6d, 0x6a, 0x37, 0xbf, 0x7c, 0x34,
      0xef, 0xa5, 0xf9, 0x00, 0xb2, 0x87, 0xff, 0xc2, 0x60, 0xe4, 0xf1, 0x79,
      0x95, 0xc2, 0x94, 0xc9, 0xe0, 0x3f, 0xea, 0x41, 0x9f, 0x04, 0xbf, 0x0b,
      0x6b, 0x9a, 0x39, 0xfe, 0x0b, 0x4f, 0xeb, 0x00, 0x0e, 0x3d, 0xd7, 0xe6,
      0x45, 0xe0, 0x37, 0xeb, 0x45, 0x16, 0x49, 0xbc, 0xda, 0xb7, 0x49, 0x9c,
      0x1f, 0xd9, 0x1f, 0x85, 0x59, 0x03, 0x00, 0xda, 0x52, 0xaa, 0x0a, 0x46,
      0xd7, 0x9f, 0xce, 0xf0, 0xe1, 0xd5, 0x9a, 0xd1, 0x55, 0x7d, 0x41, 0x8f,
      0x0f, 0x8d, 0xce, 0x25, 0x80, 0xa6, 0x82, 0xc3, 0xc9, 0xd6, 0xc3, 0x55,
      0xd8, 0xf0, 0x8b, 0x02, 0x00,
      // Prekey message
      0x00, 0x04, 0x0f, 0x33, 0x6e, 0xba, 0x12, 0x0e, 0xee, 0x86, 0xa6, 0x75,
      0x0f, 0xfc, 0xd3, 0xf7, 0xbb, 0x2d, 0x1d, 0x4b, 0x17, 0x8a, 0xed, 0x3b,
      0x55, 0xd0, 0xf7, 0xbe, 0xaa, 0xb3, 0x7f, 0x89, 0xa0, 0xcf, 0x20, 0x31,
      0xc8, 0xc1, 0xae, 0xa9, 0x76, 0x2e, 0x08, 0xf9, 0x95, 0x8b, 0x99, 0xf8,
      0x8e, 0xc0, 0xc0, 0x4f, 0xcc, 0xef, 0xce, 0x82, 0x6b, 0x07, 0xe9, 0x39,
      0xc9, 0x11, 0x4d, 0x0a, 0x4b, 0xee, 0xcc, 0x80, 0x00, 0x00, 0x01, 0x80,
      0x2f, 0x92, 0x39, 0x25, 0x73, 0xbb, 0x82, 0x85, 0xe1, 0x1a, 0x24, 0x5e,
      0xf0, 0x49, 0xaf, 0x36, 0xba, 0x45, 0x06, 0xe3, 0x71, 0xb5, 0xa0, 0xbe,
      0x9c, 0xc0, 0xa7, 0xf4, 0xf2, 0x17, 0xbf, 0xfb, 0x76, 0xca, 0xa8, 0xf3,
      0x68, 0xf2, 0xdd, 0x6e, 0x77, 0x41, 0x44, 0x41, 0xfa, 0x55, 0xba, 0x41,
      0x81, 0xe9, 0xeb, 0x6e, 0x26, 0xb9, 0x68, 0x26, 0x7c, 0x38, 0x4f, 0x71,
      0xf1, 0xac, 0x18, 0xd2, 0x1e, 0x7d, 0x4b, 0x06, 0xea, 0x18, 0x38, 0x2d,
      0x9e, 0xf1, 0x4e, 0xa2, 0x3b, 0x3f, 0x3c, 0xd0, 0xb6, 0xe6, 0x6f, 0xbc,
      0x54, 0xf6, 0x44, 0x31, 0xa8, 0xd5, 0x56, 0xec, 0x49, 0x5e, 0xee, 0x68,
      0x1a, 0x76, 0x1b, 0x1a, 0xf9, 0x04, 0xea, 0x1e, 0x53, 0x16, 0xa3, 0x99,
      0x3a, 0xc1, 0xcc, 0x08, 0x7c, 0xd8, 0xd1, 0xfb, 0x56, 0x44, 0xe9, 0x1a,
      0xc9, 0x88, 0x25, 0x23, 0xb4, 0xfb, 0x8f, 0x6b, 0xad, 0xbb, 0x64, 0x15,
      0xb5, 0x9d, 0x54, 0xcb, 0x7b, 0xe8, 0xff, 0xcb, 0x1d, 0x5c, 0xbc, 0xe2,
      0xb8, 0x10, 0xe8, 0xa3, 0xe1, 0xbc, 0xe2, 0xd1, 0xa7, 0x33, 0x06, 0x3f,
      0x83, 0x41, 0x02, 0xc7, 0x48, 0xea, 0x47, 0xbb, 0x19, 0x92, 0xbc, 0xb5,
      0x39, 0xa2, 0xcc, 0xfc, 0xda, 0x5c, 0x16, 0x3b, 0xd5, 0x6e, 0x7f, 0x1d,
      0x0f, 0x68, 0xef, 0xd6, 0x8b, 0xb8, 0xaa, 0xa6, 0xe9, 0x23, 0xfc, 0x8e,
      0xc1, 0x66, 0xd6, 0x2d, 0x6e, 0x0a, 0x2d, 0xd9, 0x63, 0x47, 0xa3, 0x59,
      0x29, 0x23, 0x7b, 0xf2, 0x25, 0x58, 0xd0, 0xb0, 0x0a, 0x2b, 0x3b, 0x62,
      0x59, 0x9b, 0xe9, 0x91, 0xa2, 0xed, 0xbb, 0xe8, 0x87, 0xa3, 0x31, 0xae,
      0x1e, 0xa4, 0x7b, 0xb1, 0x95, 0x8e, 0x93, 0x1b, 0x10, 0x30, 0xc8, 0xfc,
      0xa9, 0xcc, 0x3c, 0x72, 0xf3, 0xe1, 0xa9, 0xc8, 0x96, 0x28, 0xf1, 0xba,
      0x46, 0x93, 0x69, 0x6e, 0x4b, 0x32, 0x71, 0x49, 0x11, 0x37, 0x21, 0x17,
      0x97, 0xd2, 0x7b, 0xe2, 0x5f, 0x7b, 0xbd, 0x48, 0xb5, 0xf0, 0xa1, 0x70,
      0x1e, 0x88, 0x2a, 0x09, 0x5b, 0x9e, 0xae, 0x97, 0x6a, 0xa6, 0xe1, 0x30,
      0x89, 0x24, 0x76, 0x57, 0xb4, 0x0e, 0xc0, 0x5d, 0x6f, 0x74, 0xbf, 0x1d,
      0x15, 0x4b, 0xfa, 0xf5, 0x9b, 0x0a, 0xd3, 0xec, 0xb7, 0xc6, 0x12, 0xeb,
      0x74, 0xb2, 0xa7, 0x0e, 0x20, 0xf4, 0xaa, 0x48, 0xf8, 0xf7, 0x4f, 0xb3,
      0x9d, 0x66, 0xac, 0x03, 0x8b, 0xa2, 0x94, 0x1f, 0x80, 0xb3, 0x74, 0x2c,
      0x28, 0x5b, 0x7f, 0xa3, 0xc7, 0x4b, 0x41, 0x31, 0xcf, 0x16, 0x0f, 0xee,
      0x43, 0x56, 0x6c, 0x59, 0xdb, 0x90, 0xcc, 0x3c, 0xaa, 0xfc, 0xb3, 0x88,
      0x25, 0x6f, 0x72, 0xcf, 0xb5, 0x81, 0xc9, 0x02, 0x6b, 0x9d, 0xd2, 0x7b,
      0x78, 0xab, 0x2f, 0x39, 0xcd, 0x83, 0x82, 0x1b, 0xf7, 0x78, 0x92, 0x80};

  otrng_prekey_ensemble_retrieval_message_s msg[1];
  otrng_assert_is_success(otrng_prekey_ensemble_retrieval_message_deserialize(
      msg, serialized, sizeof(serialized)));

  g_assert_cmpint(msg->num_ensembles, ==, 2);
  otrng_assert(msg->ensembles[0]);
  otrng_assert(msg->ensembles[1]);
  g_assert_cmpint(msg->instance_tag, ==, 0x0eee86a6);

  otrng_assert(msg->ensembles[0]->client_profile);
  otrng_assert(msg->ensembles[0]->prekey_profile);
  otrng_assert(msg->ensembles[0]->message);
  otrng_assert(msg->ensembles[1]->client_profile);
  otrng_assert(msg->ensembles[1]->prekey_profile);
  otrng_assert(msg->ensembles[1]->message);

  otrng_prekey_ensemble_retrieval_message_destroy(msg);
}

void units_prekey_server_client_add_tests(void) {
  g_test_add_func("/prekey_server/dake/dake-1/serialize",
                  test_prekey_dake1_message_serialize);
  g_test_add_func("/prekey_server/dake/dake-2/deserialize",
                  test_prekey_dake2_message_deserialize);
  g_test_add_func("/prekey_server/dake/dake-3/storage_info_request",
                  test_prekey_dake3_message_append_storage_info_req);
  g_test_add_func("/prekey_server/dake/dake-3/serialize",
                  test_prekey_dake3_message_serialize);
  g_test_add_func("/prekey_server/dake/storage-status/deserialize",
                  test_prekey_storage_status_message_deserialize);
  g_test_add_func("/prekey_server/dake/ensemble-retrieval/deserialize",
                  test_prekey_ensemble_retrieval_message_deserialize);
}