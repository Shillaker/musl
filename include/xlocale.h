// -*- C++ -*-
//===------------------- support/musl/xlocale.h ------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
// This adds support for the extended locale functions that are currently
// missing from the Musl C library.
//
// This only works when the specified locale is "C" or "POSIX", but that's
// about as good as we can do without implementing full xlocale support
// in Musl.
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP_SUPPORT_MUSL_XLOCALE_H
#define _LIBCPP_SUPPORT_MUSL_XLOCALE_H

#include <cstdlib>
#include <cwchar>

#ifdef __cplusplus
extern "C" {
#endif

// THIS IS A HACK TO GET EMSCRIPTEN WORKING
#define _CTYPE_A  0x00000400   /* Alpha */
#define _CTYPE_C  0x00000002   /* Control */
#define _CTYPE_D  0x00000800   /* Digit */
#define _CTYPE_L  0x00000200   /* Lower */
#define _CTYPE_P  0x00000004   /* Punct */
#define _CTYPE_S  0x00002000   /* Space */
#define _CTYPE_U  0x00000100   /* Upper */
#define _CTYPE_X  0x00001000   /* X digit */
#define _CTYPE_B  0x00000001   /* Blank */
#define _CTYPE_R  0x00004000   /* Print */

static inline long long strtoll_l(const char *nptr, char **endptr, int base,
                                  locale_t) {
  return strtoll(nptr, endptr, base);
}

static inline unsigned long long strtoull_l(const char *nptr, char **endptr,
                                            int base, locale_t) {
  return strtoull(nptr, endptr, base);
}

static inline long long wcstoll_l(const wchar_t *nptr, wchar_t **endptr,
                                  int base, locale_t) {
  return wcstoll(nptr, endptr, base);
}

static inline unsigned long long wcstoull_l(const wchar_t *nptr,
                                            wchar_t **endptr, int base,
                                            locale_t) {
  return wcstoull(nptr, endptr, base);
}

static inline long double wcstold_l(const wchar_t *nptr, wchar_t **endptr,
                                    locale_t) {
  return wcstold(nptr, endptr);
}

#ifdef __cplusplus
}
#endif

#endif // _LIBCPP_SUPPORT_MUSL_XLOCALE_H
