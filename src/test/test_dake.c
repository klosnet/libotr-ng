/*
 *  This file is part of the Off-the-Record Next Generation Messaging
 *  library (libotr-ng).
 *
 *  Copyright (C) 2016-2018, the libotr-ng contributors.
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
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
#include <string.h>

#define OTRNG_DAKE_PRIVATE

#include "../auth.h"
#include "../dake.h"
#include "../serialize.h"

void test_build_interactive_rsign_tag() {
  otrng_err err = ERROR;

  // Wow. 1KB
  uint8_t expected_t1[1083] = {
      0x01, 0x5d, 0x59, 0x91, 0x6e, 0x9a, 0x5c, 0x4b, 0x8c, 0xce, 0xf7, 0xcd,
      0x42, 0xfd, 0xa6, 0xf2, 0x21, 0x6e, 0x35, 0xf4, 0x7b, 0x67, 0xfc, 0xda,
      0x03, 0x67, 0xfd, 0x0f, 0x17, 0x32, 0x98, 0xad, 0xee, 0xf3, 0xb4, 0xa1,
      0x65, 0x6b, 0x06, 0xfa, 0x8c, 0xc3, 0xf7, 0x87, 0x4c, 0xf0, 0xde, 0x7d,
      0xe3, 0x1a, 0x08, 0x46, 0x91, 0x50, 0xf3, 0xcc, 0x54, 0xdf, 0xb5, 0xa5,
      0x77, 0x32, 0xc8, 0xcd, 0xe5, 0x1f, 0xfe, 0xd7, 0x7f, 0x4b, 0x3a, 0x2d,
      0xca, 0x85, 0x6f, 0xe5, 0x28, 0xfd, 0x41, 0x69, 0x78, 0x77, 0x8f, 0x46,
      0x29, 0x40, 0xe0, 0xf0, 0x7e, 0xc3, 0x6e, 0x9c, 0x72, 0xa5, 0x2f, 0x3f,
      0xe6, 0xee, 0x08, 0x20, 0x38, 0x3b, 0x6c, 0x35, 0xa9, 0xf2, 0x74, 0x4b,
      0xcf, 0x88, 0xd0, 0xa8, 0xd3, 0xf1, 0x22, 0x34, 0x1d, 0x87, 0xfd, 0x20,
      0x6a, 0x34, 0x2f, 0xf0, 0xec, 0xe3, 0x47, 0x68, 0x25, 0x73, 0x58, 0x9d,
      0x71, 0x77, 0xac, 0x23, 0x70, 0x07, 0xe4, 0xa4, 0x5c, 0xf8, 0xcf, 0xb4,
      0x96, 0x58, 0x18, 0x11, 0x8f, 0x9e, 0xc4, 0x00, 0x7b, 0xef, 0xea, 0xba,
      0x4f, 0x42, 0xd3, 0xfe, 0x16, 0x6f, 0xe0, 0xd5, 0xc6, 0x76, 0x7c, 0x4b,
      0x72, 0xc7, 0x74, 0xf1, 0x20, 0x7e, 0xf8, 0x00, 0xd4, 0x43, 0xce, 0x4b,
      0x51, 0x51, 0x6a, 0x46, 0x90, 0x00, 0xe1, 0x69, 0x32, 0xb4, 0x5d, 0x24,
      0x54, 0xd2, 0x4a, 0xf1, 0x17, 0xa0, 0x3c, 0xb5, 0xcf, 0x12, 0xbc, 0xc5,
      0xeb, 0x41, 0x60, 0xe9, 0xdc, 0xb3, 0xa4, 0xba, 0xaa, 0x46, 0xbb, 0xfe,
      0xcd, 0x0d, 0x90, 0x9a, 0xd2, 0x44, 0x01, 0xf1, 0x48, 0x58, 0x1c, 0x0d,
      0xcd, 0xd3, 0xbf, 0x13, 0x17, 0x9b, 0x1c, 0x6b, 0x13, 0x28, 0xb5, 0x3c,
      0xfa, 0xbf, 0x80, 0x00, 0x00, 0x01, 0x80, 0x77, 0x98, 0xd0, 0x39, 0x9f,
      0xe3, 0x45, 0x5b, 0x2c, 0xb0, 0x62, 0x5f, 0xb2, 0x62, 0x8f, 0x5a, 0x9c,
      0x35, 0xa5, 0xd5, 0x19, 0xb0, 0xaf, 0x4b, 0x70, 0xcc, 0xeb, 0xdc, 0x81,
      0xc9, 0x24, 0xa3, 0x1b, 0xcb, 0xc1, 0xf8, 0x4d, 0x84, 0xa7, 0x55, 0xb9,
      0xd2, 0xba, 0x3c, 0x84, 0x6e, 0x62, 0x29, 0xd5, 0x9b, 0x86, 0x11, 0xe7,
      0xe9, 0x93, 0xd6, 0x41, 0x9e, 0xce, 0x9d, 0xfb, 0x4a, 0x57, 0x91, 0x11,
      0xdb, 0x5e, 0x4f, 0x4b, 0x99, 0x43, 0x58, 0x50, 0xc9, 0x29, 0xce, 0x9b,
      0x75, 0x4b, 0x56, 0x3a, 0xfc, 0xe5, 0x92, 0x5b, 0xa3, 0x04, 0x9d, 0xf7,
      0xf8, 0x1a, 0xed, 0x98, 0x86, 0x3a, 0xeb, 0xd6, 0x23, 0xaf, 0xb9, 0x96,
      0x73, 0xbd, 0x5a, 0x68, 0xb2, 0x99, 0xb1, 0x28, 0xb3, 0x8b, 0x2b, 0xb4,
      0x4b, 0x82, 0x23, 0x43, 0xee, 0xa0, 0xf9, 0x64, 0x90, 0x13, 0x9e, 0xa8,
      0x3d, 0x0f, 0x09, 0x36, 0xe3, 0x0a, 0x51, 0x3f, 0x10, 0x91, 0xd6, 0x9b,
      0x3b, 0x6d, 0x32, 0xf2, 0x08, 0xbc, 0x0e, 0x9e, 0x63, 0x5a, 0x64, 0x22,
      0x83, 0xe2, 0x9c, 0xfe, 0xf8, 0x68, 0xc5, 0x14, 0x42, 0x8e, 0x8d, 0x25,
      0x30, 0x69, 0x7b, 0x3c, 0x04, 0x25, 0x4f, 0xef, 0x5b, 0x26, 0x09, 0xe6,
      0xc3, 0xa7, 0x50, 0xeb, 0x25, 0x99, 0xea, 0xa8, 0x7b, 0x94, 0xfc, 0x78,
      0xce, 0x2c, 0x43, 0x0a, 0x2b, 0x0f, 0x1b, 0xc7, 0xdd, 0xec, 0x75, 0xcc,
      0x27, 0x86, 0x71, 0xc2, 0x1b, 0xcf, 0x77, 0x7b, 0x4a, 0xce, 0xcb, 0xd7,
      0xd9, 0xbf, 0x91, 0x6f, 0xe1, 0x3c, 0x00, 0x1c, 0x32, 0xdd, 0xc1, 0x40,
      0x91, 0xd6, 0xce, 0xca, 0x7d, 0x7c, 0xd8, 0xaf, 0xdb, 0x24, 0xfb, 0xa9,
      0xc6, 0x62, 0x19, 0x54, 0xf4, 0x2c, 0x7a, 0xbc, 0x00, 0x3e, 0xc8, 0x66,
      0xc1, 0xac, 0xd2, 0x03, 0x8b, 0x33, 0x52, 0x08, 0x92, 0x88, 0xe9, 0x5b,
      0x24, 0x12, 0x61, 0x0c, 0x54, 0x5e, 0x57, 0x21, 0xe8, 0x40, 0x73, 0x89,
      0x1c, 0x45, 0xf8, 0x99, 0x4f, 0xcc, 0xfa, 0xd7, 0xf1, 0x58, 0x10, 0xb0,
      0xeb, 0x53, 0x1a, 0x4c, 0xca, 0xb8, 0x0f, 0x57, 0xf6, 0x35, 0x87, 0x87,
      0x83, 0x1b, 0x66, 0x3b, 0x94, 0xfc, 0xcd, 0x27, 0xac, 0x99, 0x30, 0x86,
      0x46, 0x79, 0x23, 0xa5, 0xf8, 0x24, 0xe6, 0x1a, 0x54, 0x89, 0x09, 0x15,
      0x8f, 0x41, 0x81, 0x5e, 0x01, 0xbc, 0x7e, 0x67, 0x84, 0x8a, 0x83, 0xf2,
      0x6b, 0x99, 0x77, 0xd6, 0x20, 0x1e, 0xc2, 0x13, 0xf0, 0x3c, 0xcd, 0x1e,
      0xed, 0xcc, 0xed, 0x40, 0x8b, 0x73, 0xdd, 0xf4, 0xd6, 0x23, 0x48, 0xf9,
      0xbc, 0x94, 0x8c, 0x18, 0x88, 0x0d, 0x9d, 0x76, 0x77, 0x63, 0xd7, 0xab,
      0x4f, 0x7f, 0x25, 0x6d, 0xe2, 0xad, 0x80, 0x23, 0x53, 0xe5, 0x4c, 0xa6,
      0xbf, 0xc4, 0x2d, 0x3d, 0x88, 0x9d, 0x2d, 0x00, 0x00, 0x01, 0x80, 0xc3,
      0x65, 0xc1, 0x7f, 0x33, 0x1a, 0x11, 0xc6, 0x03, 0x51, 0x86, 0x38, 0xab,
      0x10, 0x0b, 0x80, 0x4d, 0x25, 0xdf, 0x0b, 0xb1, 0xeb, 0x09, 0x8e, 0xba,
      0x09, 0x62, 0x53, 0xdb, 0x05, 0x55, 0xf4, 0xd5, 0xaa, 0x02, 0x86, 0x71,
      0xd6, 0x0c, 0x17, 0x49, 0xe1, 0xa3, 0x55, 0x4c, 0x51, 0x2e, 0x1d, 0xaf,
      0xa4, 0x64, 0xd6, 0x64, 0xa2, 0xdb, 0x9e, 0x9a, 0x9d, 0x57, 0x3f, 0xcb,
      0x28, 0x34, 0x4e, 0x47, 0x1c, 0x45, 0x3f, 0x11, 0xf3, 0xb8, 0x52, 0xf2,
      0x15, 0x5b, 0x3e, 0xc5, 0xca, 0xa2, 0x1b, 0x7b, 0x2c, 0xc9, 0x34, 0xd5,
      0x9f, 0xfc, 0x06, 0x43, 0xd8, 0x6c, 0xce, 0xee, 0x3f, 0xc7, 0x18, 0xbb,
      0x37, 0x81, 0xea, 0x75, 0x76, 0xea, 0x4d, 0x5f, 0x9d, 0x90, 0x91, 0x66,
      0x35, 0x6e, 0xf3, 0x9b, 0xa9, 0xb4, 0x8f, 0x84, 0xbd, 0xf1, 0x83, 0xa4,
      0x09, 0x08, 0x3a, 0xc9, 0xd7, 0xb3, 0xfe, 0xa9, 0xd0, 0x72, 0x0e, 0x9a,
      0xc4, 0xfa, 0x8a, 0x6f, 0x0e, 0x65, 0x56, 0x7b, 0x0b, 0xd1, 0x61, 0x28,
      0xe9, 0xcd, 0xe1, 0xc1, 0x8a, 0xba, 0xce, 0x93, 0xe6, 0x29, 0x08, 0xa8,
      0xf7, 0xd4, 0xdb, 0x88, 0xee, 0xfd, 0xe5, 0x55, 0x1f, 0x17, 0xa9, 0x81,
      0x86, 0xc6, 0xdc, 0x5a, 0xcd, 0xa7, 0x37, 0x54, 0xfe, 0xe9, 0x6b, 0x2d,
      0x0e, 0xf2, 0x6d, 0x2f, 0x10, 0x97, 0x07, 0x46, 0x75, 0xf8, 0x82, 0xaa,
      0xe8, 0xfc, 0xd0, 0xd1, 0xa1, 0x39, 0x72, 0x1f, 0x43, 0xb5, 0xff, 0x6f,
      0xa1, 0x17, 0x91, 0x5f, 0x2c, 0x6a, 0x65, 0xd2, 0xd1, 0x8a, 0x49, 0x65,
      0x25, 0xd1, 0xfb, 0x00, 0x47, 0x93, 0x6b, 0xd4, 0x4e, 0x10, 0x4f, 0xb0,
      0xff, 0xe8, 0x5d, 0xef, 0xdf, 0xe4, 0x1c, 0xb8, 0x0d, 0xc5, 0x64, 0x10,
      0xfa, 0xb8, 0x4c, 0xb4, 0x47, 0x0e, 0x8d, 0x41, 0xc6, 0x7e, 0x57, 0xb1,
      0x64, 0x7e, 0xb6, 0x24, 0xd5, 0x95, 0xcf, 0xbc, 0xc4, 0x65, 0xf0, 0x97,
      0xe4, 0x07, 0x82, 0x14, 0x2c, 0xad, 0x61, 0x71, 0x0d, 0x66, 0xda, 0xa5,
      0x56, 0x36, 0x21, 0x2d, 0x69, 0xc4, 0xa1, 0x2a, 0x0b, 0xcb, 0xe3, 0x52,
      0x6a, 0xac, 0x8c, 0xfa, 0xef, 0x2b, 0x81, 0xe5, 0x70, 0x73, 0xee, 0x1f,
      0xfc, 0xb8, 0x7c, 0x6f, 0xe9, 0x93, 0x81, 0xef, 0x08, 0x66, 0x22, 0xbf,
      0x23, 0x34, 0xb9, 0x38, 0x0e, 0xc5, 0xf9, 0xe7, 0x2f, 0x02, 0x58, 0xcb,
      0x1c, 0x9f, 0x23, 0x14, 0xf6, 0x61, 0x33, 0x12, 0xc5, 0xf9, 0x65, 0xf3,
      0x83, 0x23, 0xf2, 0xd8, 0x4b, 0xcd, 0x27, 0xe7, 0x55, 0x3e, 0x36, 0x34,
      0xa3, 0xf2, 0x6e, 0x9d, 0xb3, 0xe6, 0x76, 0x4d, 0xd7, 0x51, 0x91, 0xdd,
      0x29, 0x34, 0xde, 0xaa, 0xed, 0xef, 0x22, 0x4c, 0xee, 0x32, 0x30, 0x1e,
      0xfc, 0xad, 0x23, 0xe9, 0xfa, 0xaf, 0x71, 0x63, 0x4b, 0xf6, 0xe9, 0x64,
      0xd2, 0x72, 0x8a, 0xd9, 0x3d, 0x9f, 0x94, 0x83, 0x53, 0x28, 0x2c, 0x92,
      0xf3, 0x13, 0x3f, 0x8d, 0x65, 0x8d, 0x5b, 0x50, 0x32, 0x40, 0xca, 0x66,
      0x02, 0x51, 0x34, 0x0b, 0xed, 0xe6, 0xfa, 0xea, 0xdb, 0x8a, 0xbb, 0x51,
      0xed, 0xe9, 0x22, 0x7d, 0x8e, 0x20, 0x65, 0xff, 0xef, 0xa3, 0xe1, 0xce,
      0x32, 0xfd, 0xe6, 0x6e, 0xee, 0x18, 0x0a, 0x1d, 0x23, 0xff, 0xfd, 0x20,
      0x2c, 0xa3, 0xc6,
  };

  uint8_t expected_t2[1083] = {
      0x02, 0xba, 0x49, 0x6b, 0x8d, 0x71, 0x80, 0xab, 0x29, 0x7e, 0x61, 0xb8,
      0x7d, 0xd2, 0xb8, 0x10, 0x45, 0x1f, 0xf1, 0x40, 0x4c, 0xef, 0x12, 0x5b,
      0x53, 0x6b, 0xe7, 0x2f, 0xb2, 0xed, 0xfb, 0x40, 0x5f, 0x93, 0x74, 0xf7,
      0x68, 0xb2, 0x3c, 0xbc, 0xd6, 0x27, 0xc6, 0xbe, 0x35, 0xec, 0x84, 0x98,
      0xf4, 0x78, 0x70, 0xe0, 0xac, 0xca, 0xf7, 0x68, 0xc0, 0xcc, 0x2a, 0x3a,
      0xc1, 0x44, 0xd1, 0x4f, 0x9b, 0x48, 0xdb, 0xe9, 0xbd, 0xec, 0xda, 0xb3,
      0x3b, 0x3f, 0xd8, 0x7d, 0x3d, 0x39, 0xdc, 0xb7, 0x5c, 0x3b, 0x1d, 0x45,
      0x0f, 0x32, 0x31, 0x42, 0xe0, 0x13, 0x94, 0x35, 0x53, 0x84, 0xa2, 0xdc,
      0x97, 0xa1, 0x04, 0x16, 0xba, 0x98, 0x2c, 0x29, 0x0c, 0x04, 0x31, 0x31,
      0xe6, 0x92, 0x26, 0x6b, 0x9b, 0x51, 0xf6, 0xa4, 0xe2, 0x5e, 0xb4, 0xab,
      0x8d, 0xe9, 0x1c, 0xac, 0x92, 0x8f, 0x6e, 0xb7, 0xed, 0x73, 0x58, 0x9d,
      0x71, 0x77, 0xac, 0x23, 0x70, 0x07, 0xe4, 0xa4, 0x5c, 0xf8, 0xcf, 0xb4,
      0x96, 0x58, 0x18, 0x11, 0x8f, 0x9e, 0xc4, 0x00, 0x7b, 0xef, 0xea, 0xba,
      0x4f, 0x42, 0xd3, 0xfe, 0x16, 0x6f, 0xe0, 0xd5, 0xc6, 0x76, 0x7c, 0x4b,
      0x72, 0xc7, 0x74, 0xf1, 0x20, 0x7e, 0xf8, 0x00, 0xd4, 0x43, 0xce, 0x4b,
      0x51, 0x51, 0x6a, 0x46, 0x90, 0x00, 0xe1, 0x69, 0x32, 0xb4, 0x5d, 0x24,
      0x54, 0xd2, 0x4a, 0xf1, 0x17, 0xa0, 0x3c, 0xb5, 0xcf, 0x12, 0xbc, 0xc5,
      0xeb, 0x41, 0x60, 0xe9, 0xdc, 0xb3, 0xa4, 0xba, 0xaa, 0x46, 0xbb, 0xfe,
      0xcd, 0x0d, 0x90, 0x9a, 0xd2, 0x44, 0x01, 0xf1, 0x48, 0x58, 0x1c, 0x0d,
      0xcd, 0xd3, 0xbf, 0x13, 0x17, 0x9b, 0x1c, 0x6b, 0x13, 0x28, 0xb5, 0x3c,
      0xfa, 0xbf, 0x80, 0x00, 0x00, 0x01, 0x80, 0x77, 0x98, 0xd0, 0x39, 0x9f,
      0xe3, 0x45, 0x5b, 0x2c, 0xb0, 0x62, 0x5f, 0xb2, 0x62, 0x8f, 0x5a, 0x9c,
      0x35, 0xa5, 0xd5, 0x19, 0xb0, 0xaf, 0x4b, 0x70, 0xcc, 0xeb, 0xdc, 0x81,
      0xc9, 0x24, 0xa3, 0x1b, 0xcb, 0xc1, 0xf8, 0x4d, 0x84, 0xa7, 0x55, 0xb9,
      0xd2, 0xba, 0x3c, 0x84, 0x6e, 0x62, 0x29, 0xd5, 0x9b, 0x86, 0x11, 0xe7,
      0xe9, 0x93, 0xd6, 0x41, 0x9e, 0xce, 0x9d, 0xfb, 0x4a, 0x57, 0x91, 0x11,
      0xdb, 0x5e, 0x4f, 0x4b, 0x99, 0x43, 0x58, 0x50, 0xc9, 0x29, 0xce, 0x9b,
      0x75, 0x4b, 0x56, 0x3a, 0xfc, 0xe5, 0x92, 0x5b, 0xa3, 0x04, 0x9d, 0xf7,
      0xf8, 0x1a, 0xed, 0x98, 0x86, 0x3a, 0xeb, 0xd6, 0x23, 0xaf, 0xb9, 0x96,
      0x73, 0xbd, 0x5a, 0x68, 0xb2, 0x99, 0xb1, 0x28, 0xb3, 0x8b, 0x2b, 0xb4,
      0x4b, 0x82, 0x23, 0x43, 0xee, 0xa0, 0xf9, 0x64, 0x90, 0x13, 0x9e, 0xa8,
      0x3d, 0x0f, 0x09, 0x36, 0xe3, 0x0a, 0x51, 0x3f, 0x10, 0x91, 0xd6, 0x9b,
      0x3b, 0x6d, 0x32, 0xf2, 0x08, 0xbc, 0x0e, 0x9e, 0x63, 0x5a, 0x64, 0x22,
      0x83, 0xe2, 0x9c, 0xfe, 0xf8, 0x68, 0xc5, 0x14, 0x42, 0x8e, 0x8d, 0x25,
      0x30, 0x69, 0x7b, 0x3c, 0x04, 0x25, 0x4f, 0xef, 0x5b, 0x26, 0x09, 0xe6,
      0xc3, 0xa7, 0x50, 0xeb, 0x25, 0x99, 0xea, 0xa8, 0x7b, 0x94, 0xfc, 0x78,
      0xce, 0x2c, 0x43, 0x0a, 0x2b, 0x0f, 0x1b, 0xc7, 0xdd, 0xec, 0x75, 0xcc,
      0x27, 0x86, 0x71, 0xc2, 0x1b, 0xcf, 0x77, 0x7b, 0x4a, 0xce, 0xcb, 0xd7,
      0xd9, 0xbf, 0x91, 0x6f, 0xe1, 0x3c, 0x00, 0x1c, 0x32, 0xdd, 0xc1, 0x40,
      0x91, 0xd6, 0xce, 0xca, 0x7d, 0x7c, 0xd8, 0xaf, 0xdb, 0x24, 0xfb, 0xa9,
      0xc6, 0x62, 0x19, 0x54, 0xf4, 0x2c, 0x7a, 0xbc, 0x00, 0x3e, 0xc8, 0x66,
      0xc1, 0xac, 0xd2, 0x03, 0x8b, 0x33, 0x52, 0x08, 0x92, 0x88, 0xe9, 0x5b,
      0x24, 0x12, 0x61, 0x0c, 0x54, 0x5e, 0x57, 0x21, 0xe8, 0x40, 0x73, 0x89,
      0x1c, 0x45, 0xf8, 0x99, 0x4f, 0xcc, 0xfa, 0xd7, 0xf1, 0x58, 0x10, 0xb0,
      0xeb, 0x53, 0x1a, 0x4c, 0xca, 0xb8, 0x0f, 0x57, 0xf6, 0x35, 0x87, 0x87,
      0x83, 0x1b, 0x66, 0x3b, 0x94, 0xfc, 0xcd, 0x27, 0xac, 0x99, 0x30, 0x86,
      0x46, 0x79, 0x23, 0xa5, 0xf8, 0x24, 0xe6, 0x1a, 0x54, 0x89, 0x09, 0x15,
      0x8f, 0x41, 0x81, 0x5e, 0x01, 0xbc, 0x7e, 0x67, 0x84, 0x8a, 0x83, 0xf2,
      0x6b, 0x99, 0x77, 0xd6, 0x20, 0x1e, 0xc2, 0x13, 0xf0, 0x3c, 0xcd, 0x1e,
      0xed, 0xcc, 0xed, 0x40, 0x8b, 0x73, 0xdd, 0xf4, 0xd6, 0x23, 0x48, 0xf9,
      0xbc, 0x94, 0x8c, 0x18, 0x88, 0x0d, 0x9d, 0x76, 0x77, 0x63, 0xd7, 0xab,
      0x4f, 0x7f, 0x25, 0x6d, 0xe2, 0xad, 0x80, 0x23, 0x53, 0xe5, 0x4c, 0xa6,
      0xbf, 0xc4, 0x2d, 0x3d, 0x88, 0x9d, 0x2d, 0x00, 0x00, 0x01, 0x80, 0xc3,
      0x65, 0xc1, 0x7f, 0x33, 0x1a, 0x11, 0xc6, 0x03, 0x51, 0x86, 0x38, 0xab,
      0x10, 0x0b, 0x80, 0x4d, 0x25, 0xdf, 0x0b, 0xb1, 0xeb, 0x09, 0x8e, 0xba,
      0x09, 0x62, 0x53, 0xdb, 0x05, 0x55, 0xf4, 0xd5, 0xaa, 0x02, 0x86, 0x71,
      0xd6, 0x0c, 0x17, 0x49, 0xe1, 0xa3, 0x55, 0x4c, 0x51, 0x2e, 0x1d, 0xaf,
      0xa4, 0x64, 0xd6, 0x64, 0xa2, 0xdb, 0x9e, 0x9a, 0x9d, 0x57, 0x3f, 0xcb,
      0x28, 0x34, 0x4e, 0x47, 0x1c, 0x45, 0x3f, 0x11, 0xf3, 0xb8, 0x52, 0xf2,
      0x15, 0x5b, 0x3e, 0xc5, 0xca, 0xa2, 0x1b, 0x7b, 0x2c, 0xc9, 0x34, 0xd5,
      0x9f, 0xfc, 0x06, 0x43, 0xd8, 0x6c, 0xce, 0xee, 0x3f, 0xc7, 0x18, 0xbb,
      0x37, 0x81, 0xea, 0x75, 0x76, 0xea, 0x4d, 0x5f, 0x9d, 0x90, 0x91, 0x66,
      0x35, 0x6e, 0xf3, 0x9b, 0xa9, 0xb4, 0x8f, 0x84, 0xbd, 0xf1, 0x83, 0xa4,
      0x09, 0x08, 0x3a, 0xc9, 0xd7, 0xb3, 0xfe, 0xa9, 0xd0, 0x72, 0x0e, 0x9a,
      0xc4, 0xfa, 0x8a, 0x6f, 0x0e, 0x65, 0x56, 0x7b, 0x0b, 0xd1, 0x61, 0x28,
      0xe9, 0xcd, 0xe1, 0xc1, 0x8a, 0xba, 0xce, 0x93, 0xe6, 0x29, 0x08, 0xa8,
      0xf7, 0xd4, 0xdb, 0x88, 0xee, 0xfd, 0xe5, 0x55, 0x1f, 0x17, 0xa9, 0x81,
      0x86, 0xc6, 0xdc, 0x5a, 0xcd, 0xa7, 0x37, 0x54, 0xfe, 0xe9, 0x6b, 0x2d,
      0x0e, 0xf2, 0x6d, 0x2f, 0x10, 0x97, 0x07, 0x46, 0x75, 0xf8, 0x82, 0xaa,
      0xe8, 0xfc, 0xd0, 0xd1, 0xa1, 0x39, 0x72, 0x1f, 0x43, 0xb5, 0xff, 0x6f,
      0xa1, 0x17, 0x91, 0x5f, 0x2c, 0x6a, 0x65, 0xd2, 0xd1, 0x8a, 0x49, 0x65,
      0x25, 0xd1, 0xfb, 0x00, 0x47, 0x93, 0x6b, 0xd4, 0x4e, 0x10, 0x4f, 0xb0,
      0xff, 0xe8, 0x5d, 0xef, 0xdf, 0xe4, 0x1c, 0xb8, 0x0d, 0xc5, 0x64, 0x10,
      0xfa, 0xb8, 0x4c, 0xb4, 0x47, 0x0e, 0x8d, 0x41, 0xc6, 0x7e, 0x57, 0xb1,
      0x64, 0x7e, 0xb6, 0x24, 0xd5, 0x95, 0xcf, 0xbc, 0xc4, 0x65, 0xf0, 0x97,
      0xe4, 0x07, 0x82, 0x14, 0x2c, 0xad, 0x61, 0x71, 0x0d, 0x66, 0xda, 0xa5,
      0x56, 0x36, 0x21, 0x2d, 0x69, 0xc4, 0xa1, 0x2a, 0x0b, 0xcb, 0xe3, 0x52,
      0x6a, 0xac, 0x8c, 0xfa, 0xef, 0x2b, 0x81, 0xe5, 0x70, 0x73, 0xee, 0x1f,
      0xfc, 0xb8, 0x7c, 0x6f, 0xe9, 0x93, 0x81, 0xef, 0x08, 0x66, 0x22, 0xbf,
      0x23, 0x34, 0xb9, 0x38, 0x0e, 0xc5, 0xf9, 0xe7, 0x2f, 0x02, 0x58, 0xcb,
      0x1c, 0x9f, 0x23, 0x14, 0xf6, 0x61, 0x33, 0x12, 0xc5, 0xf9, 0x65, 0xf3,
      0x83, 0x23, 0xf2, 0xd8, 0x4b, 0xcd, 0x27, 0xe7, 0x55, 0x3e, 0x36, 0x34,
      0xa3, 0xf2, 0x6e, 0x9d, 0xb3, 0xe6, 0x76, 0x4d, 0xd7, 0x51, 0x91, 0xdd,
      0x29, 0x34, 0xde, 0xaa, 0xed, 0xef, 0x22, 0x4c, 0xee, 0x32, 0x30, 0x1e,
      0xfc, 0xad, 0x23, 0xe9, 0xfa, 0xaf, 0x71, 0x63, 0x4b, 0xf6, 0xe9, 0xba,
      0x74, 0xe4, 0xc5, 0xab, 0xb1, 0xf1, 0xac, 0x4d, 0xa3, 0xb0, 0x39, 0xac,
      0xe1, 0x53, 0x87, 0x0b, 0xb5, 0x9e, 0x55, 0x22, 0x45, 0x05, 0x25, 0x70,
      0x5f, 0xd3, 0xa6, 0x88, 0x62, 0x0a, 0x2b, 0xf0, 0x20, 0x06, 0x4b, 0x47,
      0xcf, 0xbd, 0xa1, 0x4a, 0x4a, 0x0d, 0x9d, 0x74, 0xeb, 0x8d, 0x03, 0x67,
      0x18, 0xed, 0x7d, 0xb3, 0x15, 0x98, 0x6a, 0xac, 0x58, 0x8a, 0xa3, 0xe6,
      0xe3, 0x7f, 0x66,
  };

  dh_mpi_p initiator_dh = NULL;
  uint8_t initiator_dh_s[DH3072_MOD_LEN_BYTES] = {
      0x77, 0x98, 0xd0, 0x39, 0x9f, 0xe3, 0x45, 0x5b, 0x2c, 0xb0, 0x62, 0x5f,
      0xb2, 0x62, 0x8f, 0x5a, 0x9c, 0x35, 0xa5, 0xd5, 0x19, 0xb0, 0xaf, 0x4b,
      0x70, 0xcc, 0xeb, 0xdc, 0x81, 0xc9, 0x24, 0xa3, 0x1b, 0xcb, 0xc1, 0xf8,
      0x4d, 0x84, 0xa7, 0x55, 0xb9, 0xd2, 0xba, 0x3c, 0x84, 0x6e, 0x62, 0x29,
      0xd5, 0x9b, 0x86, 0x11, 0xe7, 0xe9, 0x93, 0xd6, 0x41, 0x9e, 0xce, 0x9d,
      0xfb, 0x4a, 0x57, 0x91, 0x11, 0xdb, 0x5e, 0x4f, 0x4b, 0x99, 0x43, 0x58,
      0x50, 0xc9, 0x29, 0xce, 0x9b, 0x75, 0x4b, 0x56, 0x3a, 0xfc, 0xe5, 0x92,
      0x5b, 0xa3, 0x04, 0x9d, 0xf7, 0xf8, 0x1a, 0xed, 0x98, 0x86, 0x3a, 0xeb,
      0xd6, 0x23, 0xaf, 0xb9, 0x96, 0x73, 0xbd, 0x5a, 0x68, 0xb2, 0x99, 0xb1,
      0x28, 0xb3, 0x8b, 0x2b, 0xb4, 0x4b, 0x82, 0x23, 0x43, 0xee, 0xa0, 0xf9,
      0x64, 0x90, 0x13, 0x9e, 0xa8, 0x3d, 0x0f, 0x09, 0x36, 0xe3, 0x0a, 0x51,
      0x3f, 0x10, 0x91, 0xd6, 0x9b, 0x3b, 0x6d, 0x32, 0xf2, 0x08, 0xbc, 0x0e,
      0x9e, 0x63, 0x5a, 0x64, 0x22, 0x83, 0xe2, 0x9c, 0xfe, 0xf8, 0x68, 0xc5,
      0x14, 0x42, 0x8e, 0x8d, 0x25, 0x30, 0x69, 0x7b, 0x3c, 0x04, 0x25, 0x4f,
      0xef, 0x5b, 0x26, 0x09, 0xe6, 0xc3, 0xa7, 0x50, 0xeb, 0x25, 0x99, 0xea,
      0xa8, 0x7b, 0x94, 0xfc, 0x78, 0xce, 0x2c, 0x43, 0x0a, 0x2b, 0x0f, 0x1b,
      0xc7, 0xdd, 0xec, 0x75, 0xcc, 0x27, 0x86, 0x71, 0xc2, 0x1b, 0xcf, 0x77,
      0x7b, 0x4a, 0xce, 0xcb, 0xd7, 0xd9, 0xbf, 0x91, 0x6f, 0xe1, 0x3c, 0x00,
      0x1c, 0x32, 0xdd, 0xc1, 0x40, 0x91, 0xd6, 0xce, 0xca, 0x7d, 0x7c, 0xd8,
      0xaf, 0xdb, 0x24, 0xfb, 0xa9, 0xc6, 0x62, 0x19, 0x54, 0xf4, 0x2c, 0x7a,
      0xbc, 0x00, 0x3e, 0xc8, 0x66, 0xc1, 0xac, 0xd2, 0x03, 0x8b, 0x33, 0x52,
      0x08, 0x92, 0x88, 0xe9, 0x5b, 0x24, 0x12, 0x61, 0x0c, 0x54, 0x5e, 0x57,
      0x21, 0xe8, 0x40, 0x73, 0x89, 0x1c, 0x45, 0xf8, 0x99, 0x4f, 0xcc, 0xfa,
      0xd7, 0xf1, 0x58, 0x10, 0xb0, 0xeb, 0x53, 0x1a, 0x4c, 0xca, 0xb8, 0x0f,
      0x57, 0xf6, 0x35, 0x87, 0x87, 0x83, 0x1b, 0x66, 0x3b, 0x94, 0xfc, 0xcd,
      0x27, 0xac, 0x99, 0x30, 0x86, 0x46, 0x79, 0x23, 0xa5, 0xf8, 0x24, 0xe6,
      0x1a, 0x54, 0x89, 0x09, 0x15, 0x8f, 0x41, 0x81, 0x5e, 0x01, 0xbc, 0x7e,
      0x67, 0x84, 0x8a, 0x83, 0xf2, 0x6b, 0x99, 0x77, 0xd6, 0x20, 0x1e, 0xc2,
      0x13, 0xf0, 0x3c, 0xcd, 0x1e, 0xed, 0xcc, 0xed, 0x40, 0x8b, 0x73, 0xdd,
      0xf4, 0xd6, 0x23, 0x48, 0xf9, 0xbc, 0x94, 0x8c, 0x18, 0x88, 0x0d, 0x9d,
      0x76, 0x77, 0x63, 0xd7, 0xab, 0x4f, 0x7f, 0x25, 0x6d, 0xe2, 0xad, 0x80,
      0x23, 0x53, 0xe5, 0x4c, 0xa6, 0xbf, 0xc4, 0x2d, 0x3d, 0x88, 0x9d, 0x2d,
  };

  dh_mpi_p responder_dh = NULL;
  uint8_t responder_dh_s[DH3072_MOD_LEN_BYTES] = {
      0xc3, 0x65, 0xc1, 0x7f, 0x33, 0x1a, 0x11, 0xc6, 0x03, 0x51, 0x86, 0x38,
      0xab, 0x10, 0x0b, 0x80, 0x4d, 0x25, 0xdf, 0x0b, 0xb1, 0xeb, 0x09, 0x8e,
      0xba, 0x09, 0x62, 0x53, 0xdb, 0x05, 0x55, 0xf4, 0xd5, 0xaa, 0x02, 0x86,
      0x71, 0xd6, 0x0c, 0x17, 0x49, 0xe1, 0xa3, 0x55, 0x4c, 0x51, 0x2e, 0x1d,
      0xaf, 0xa4, 0x64, 0xd6, 0x64, 0xa2, 0xdb, 0x9e, 0x9a, 0x9d, 0x57, 0x3f,
      0xcb, 0x28, 0x34, 0x4e, 0x47, 0x1c, 0x45, 0x3f, 0x11, 0xf3, 0xb8, 0x52,
      0xf2, 0x15, 0x5b, 0x3e, 0xc5, 0xca, 0xa2, 0x1b, 0x7b, 0x2c, 0xc9, 0x34,
      0xd5, 0x9f, 0xfc, 0x06, 0x43, 0xd8, 0x6c, 0xce, 0xee, 0x3f, 0xc7, 0x18,
      0xbb, 0x37, 0x81, 0xea, 0x75, 0x76, 0xea, 0x4d, 0x5f, 0x9d, 0x90, 0x91,
      0x66, 0x35, 0x6e, 0xf3, 0x9b, 0xa9, 0xb4, 0x8f, 0x84, 0xbd, 0xf1, 0x83,
      0xa4, 0x09, 0x08, 0x3a, 0xc9, 0xd7, 0xb3, 0xfe, 0xa9, 0xd0, 0x72, 0x0e,
      0x9a, 0xc4, 0xfa, 0x8a, 0x6f, 0x0e, 0x65, 0x56, 0x7b, 0x0b, 0xd1, 0x61,
      0x28, 0xe9, 0xcd, 0xe1, 0xc1, 0x8a, 0xba, 0xce, 0x93, 0xe6, 0x29, 0x08,
      0xa8, 0xf7, 0xd4, 0xdb, 0x88, 0xee, 0xfd, 0xe5, 0x55, 0x1f, 0x17, 0xa9,
      0x81, 0x86, 0xc6, 0xdc, 0x5a, 0xcd, 0xa7, 0x37, 0x54, 0xfe, 0xe9, 0x6b,
      0x2d, 0x0e, 0xf2, 0x6d, 0x2f, 0x10, 0x97, 0x07, 0x46, 0x75, 0xf8, 0x82,
      0xaa, 0xe8, 0xfc, 0xd0, 0xd1, 0xa1, 0x39, 0x72, 0x1f, 0x43, 0xb5, 0xff,
      0x6f, 0xa1, 0x17, 0x91, 0x5f, 0x2c, 0x6a, 0x65, 0xd2, 0xd1, 0x8a, 0x49,
      0x65, 0x25, 0xd1, 0xfb, 0x00, 0x47, 0x93, 0x6b, 0xd4, 0x4e, 0x10, 0x4f,
      0xb0, 0xff, 0xe8, 0x5d, 0xef, 0xdf, 0xe4, 0x1c, 0xb8, 0x0d, 0xc5, 0x64,
      0x10, 0xfa, 0xb8, 0x4c, 0xb4, 0x47, 0x0e, 0x8d, 0x41, 0xc6, 0x7e, 0x57,
      0xb1, 0x64, 0x7e, 0xb6, 0x24, 0xd5, 0x95, 0xcf, 0xbc, 0xc4, 0x65, 0xf0,
      0x97, 0xe4, 0x07, 0x82, 0x14, 0x2c, 0xad, 0x61, 0x71, 0x0d, 0x66, 0xda,
      0xa5, 0x56, 0x36, 0x21, 0x2d, 0x69, 0xc4, 0xa1, 0x2a, 0x0b, 0xcb, 0xe3,
      0x52, 0x6a, 0xac, 0x8c, 0xfa, 0xef, 0x2b, 0x81, 0xe5, 0x70, 0x73, 0xee,
      0x1f, 0xfc, 0xb8, 0x7c, 0x6f, 0xe9, 0x93, 0x81, 0xef, 0x08, 0x66, 0x22,
      0xbf, 0x23, 0x34, 0xb9, 0x38, 0x0e, 0xc5, 0xf9, 0xe7, 0x2f, 0x02, 0x58,
      0xcb, 0x1c, 0x9f, 0x23, 0x14, 0xf6, 0x61, 0x33, 0x12, 0xc5, 0xf9, 0x65,
      0xf3, 0x83, 0x23, 0xf2, 0xd8, 0x4b, 0xcd, 0x27, 0xe7, 0x55, 0x3e, 0x36,
      0x34, 0xa3, 0xf2, 0x6e, 0x9d, 0xb3, 0xe6, 0x76, 0x4d, 0xd7, 0x51, 0x91,
      0xdd, 0x29, 0x34, 0xde, 0xaa, 0xed, 0xef, 0x22, 0x4c, 0xee, 0x32, 0x30,
      0x1e, 0xfc, 0xad, 0x23, 0xe9, 0xfa, 0xaf, 0x71, 0x63, 0x4b, 0xf6, 0xe9,
  };

  ec_point_p initiator_ecdh;
  uint8_t initiator_ecdh_s[ED448_POINT_BYTES] = {
      0x73, 0x58, 0x9d, 0x71, 0x77, 0xac, 0x23, 0x70, 0x07, 0xe4, 0xa4, 0x5c,
      0xf8, 0xcf, 0xb4, 0x96, 0x58, 0x18, 0x11, 0x8f, 0x9e, 0xc4, 0x00, 0x7b,
      0xef, 0xea, 0xba, 0x4f, 0x42, 0xd3, 0xfe, 0x16, 0x6f, 0xe0, 0xd5, 0xc6,
      0x76, 0x7c, 0x4b, 0x72, 0xc7, 0x74, 0xf1, 0x20, 0x7e, 0xf8, 0x00, 0xd4,
      0x43, 0xce, 0x4b, 0x51, 0x51, 0x6a, 0x46, 0x90, 0x00,
  };

  ec_point_p responder_ecdh;
  uint8_t responder_ecdh_s[ED448_POINT_BYTES] = {
      0xe1, 0x69, 0x32, 0xb4, 0x5d, 0x24, 0x54, 0xd2, 0x4a, 0xf1, 0x17, 0xa0,
      0x3c, 0xb5, 0xcf, 0x12, 0xbc, 0xc5, 0xeb, 0x41, 0x60, 0xe9, 0xdc, 0xb3,
      0xa4, 0xba, 0xaa, 0x46, 0xbb, 0xfe, 0xcd, 0x0d, 0x90, 0x9a, 0xd2, 0x44,
      0x01, 0xf1, 0x48, 0x58, 0x1c, 0x0d, 0xcd, 0xd3, 0xbf, 0x13, 0x17, 0x9b,
      0x1c, 0x6b, 0x13, 0x28, 0xb5, 0x3c, 0xfa, 0xbf, 0x80,
  };

  client_profile_p initiator_profile;
  uint8_t initiator_profile_s[251] = {
      0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x05, 0x00, 0x10, 0x98, 0x4c,
      0x9c, 0x0b, 0xfb, 0x0a, 0x3b, 0x10, 0x52, 0x17, 0x0d, 0x68, 0xcb, 0xc3,
      0x83, 0xa8, 0x94, 0x3d, 0x7e, 0x45, 0x1e, 0xcc, 0x4d, 0x72, 0xa0, 0xc1,
      0xa2, 0x50, 0x7a, 0x9a, 0x37, 0xff, 0xfe, 0x3e, 0x0b, 0x1c, 0xfa, 0x1a,
      0x12, 0xc8, 0x7a, 0x92, 0x79, 0x3f, 0xc1, 0xa0, 0x54, 0xce, 0xbb, 0xe3,
      0xff, 0x4e, 0x67, 0x46, 0xd9, 0xcc, 0x00, 0x00, 0x00, 0x00, 0x03, 0x33,
      0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5a, 0xe8, 0xad, 0x19, 0xe9, 0x9a,
      0xd5, 0x82, 0x5a, 0x2c, 0xef, 0x1d, 0xe5, 0x9b, 0x77, 0xe3, 0xf5, 0x2e,
      0xed, 0x7f, 0xfd, 0xff, 0x0f, 0x58, 0xf3, 0x05, 0x23, 0x6f, 0xdb, 0xbc,
      0x54, 0x17, 0x48, 0xcd, 0x56, 0xf1, 0x77, 0xac, 0x18, 0x06, 0xaf, 0xc7,
      0x04, 0x68, 0x21, 0x8b, 0xd7, 0x93, 0x3b, 0xe5, 0xe0, 0x2c, 0x2b, 0xe2,
      0xb4, 0x29, 0x4d, 0x6c, 0x4a, 0x26, 0x00, 0x70, 0xce, 0xa9, 0xb7, 0x70,
      0xe3, 0xab, 0x38, 0xba, 0xf8, 0x6d, 0xdb, 0xa3, 0xf7, 0x42, 0x15, 0x1a,
      0x0b, 0xe4, 0x69, 0x8e, 0x94, 0xcd, 0xcf, 0x6f, 0x7c, 0x97, 0x33, 0x61,
      0xb5, 0xe6, 0x22, 0xb1, 0x0b, 0xdb, 0x02, 0x4c, 0x24, 0xef, 0xb4, 0xc6,
      0xe2, 0x0d, 0xaf, 0x11, 0x38, 0xce, 0x58, 0x9b, 0xc2, 0xd0, 0x1b, 0x2e,
      0xfd, 0x15, 0x3b, 0x00, 0x00, 0x00, 0x00, 0x00,
  };

  client_profile_p responder_profile;
  uint8_t responder_profile_s[251] = {
      0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x10, 0xf2, 0x54,
      0x0f, 0x37, 0xd7, 0x72, 0xe9, 0x6a, 0x9e, 0x32, 0x09, 0x5c, 0x15, 0xfd,
      0x48, 0xe3, 0x4c, 0x8e, 0x56, 0xcf, 0x8f, 0xd6, 0x5d, 0x09, 0x54, 0xcd,
      0xdb, 0x99, 0x4c, 0x36, 0xc9, 0x2d, 0xaf, 0xd2, 0xaf, 0x59, 0x16, 0x93,
      0x80, 0x61, 0xb7, 0x60, 0xf3, 0x29, 0xee, 0x30, 0xf5, 0x5b, 0x83, 0x19,
      0xc8, 0xd8, 0xa8, 0x97, 0x99, 0xb4, 0x80, 0x00, 0x00, 0x00, 0x03, 0x34,
      0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5a, 0xe8, 0xae, 0x66, 0x7d, 0x50,
      0xb3, 0x5b, 0xdc, 0xce, 0xef, 0x21, 0x41, 0xe8, 0xb2, 0xa9, 0x6d, 0xe4,
      0xfb, 0x60, 0x1b, 0xd5, 0x0d, 0xeb, 0xc7, 0x0d, 0xf7, 0xdc, 0x32, 0x56,
      0xf4, 0x79, 0xae, 0x95, 0x6c, 0x4e, 0x35, 0x8b, 0xce, 0x27, 0x8b, 0xf4,
      0x2b, 0xd3, 0xaf, 0xf3, 0x28, 0x97, 0xef, 0x91, 0xd3, 0x10, 0xdb, 0xf8,
      0x99, 0xd9, 0x16, 0x5f, 0xe5, 0x1b, 0x80, 0xb1, 0x31, 0xd7, 0x81, 0x26,
      0xdb, 0xbf, 0x3e, 0x2d, 0xe9, 0xd8, 0x9c, 0x77, 0xd7, 0xf7, 0x57, 0xba,
      0x5c, 0x3b, 0x7c, 0x71, 0xfe, 0xcf, 0x0b, 0xa6, 0x3d, 0x29, 0xc3, 0x29,
      0x6c, 0xf6, 0x46, 0x1a, 0xc4, 0xfa, 0xb0, 0xef, 0x76, 0x30, 0x66, 0xfe,
      0xb1, 0x56, 0x1c, 0x53, 0x0b, 0x13, 0xb2, 0x3c, 0x8c, 0x5a, 0x61, 0x14,
      0x31, 0x38, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00,
  };

  err = otrng_dh_mpi_deserialize(&initiator_dh, initiator_dh_s,
                                 DH3072_MOD_LEN_BYTES, NULL);
  otrng_assert(SUCCESS == err);

  err = otrng_dh_mpi_deserialize(&responder_dh, responder_dh_s,
                                 DH3072_MOD_LEN_BYTES, NULL);
  otrng_assert(SUCCESS == err);

  err = otrng_ec_point_decode(initiator_ecdh, initiator_ecdh_s);
  otrng_assert(SUCCESS == err);

  err = otrng_ec_point_decode(responder_ecdh, responder_ecdh_s);
  otrng_assert(SUCCESS == err);

  err = otrng_client_profile_deserialize(initiator_profile, initiator_profile_s,
                                         sizeof(initiator_profile_s), NULL);
  otrng_assert(SUCCESS == err);

  err = otrng_client_profile_deserialize(responder_profile, responder_profile_s,
                                         sizeof(responder_profile_s), NULL);
  otrng_assert(SUCCESS == err);

  uint8_t *dst = NULL;
  size_t dstlen = 0;

  err = build_interactive_rsign_tag(
      &dst, &dstlen, 0x01, initiator_profile, responder_profile, initiator_ecdh,
      responder_ecdh, initiator_dh, responder_dh, "phi");

  otrng_assert(SUCCESS == err);
  otrng_assert(dstlen == 1083);
  otrng_assert_cmpmem(dst, expected_t1, dstlen);

  free(dst);

  err = build_interactive_rsign_tag(
      &dst, &dstlen, 0x02, initiator_profile, responder_profile, initiator_ecdh,
      responder_ecdh, initiator_dh, responder_dh, "phi");

  otrng_assert(SUCCESS == err);
  otrng_assert(dstlen == 1083);
  otrng_assert_cmpmem(dst, expected_t2, dstlen);

  free(dst);

  otrng_dh_mpi_release(initiator_dh);
  otrng_dh_mpi_release(responder_dh);
  otrng_client_profile_destroy(initiator_profile);
  otrng_client_profile_destroy(responder_profile);
}
