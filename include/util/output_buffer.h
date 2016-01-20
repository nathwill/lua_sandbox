/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/** Data stream output buffer @file */

#ifndef luasandbox_util_output_buffer_h_
#define luasandbox_util_output_buffer_h_

#include <stdbool.h>

#include "luasandbox.h"

#define LSB_OUTPUT_SIZE 1024

struct lsb_output_buffer {
  size_t  maxsize;
  size_t  size;
  size_t  pos;
  char    *buf;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize the provided input buffer
 *
 * @param b Output buffer
 * @param max_message_size The maximum message size the buffer will handle
 *                 before erroring
 *
 * @return int 0 on success
 */
LSB_EXPORT
int lsb_init_output_buffer(lsb_output_buffer *b, size_t max_message_size);

/**
 * Frees the memory internally allocated by the buffer and resets the state
 *
 * @param b Output buffer
 */
LSB_EXPORT void lsb_free_output_buffer(lsb_output_buffer *b);

/**
 * Resize the output buffer when more space is needed.
 *
 * @param b Output buffer to resize.
 * @param needed Number of additional bytes needed.
 *
 * @return int 0 on success
 */
LSB_EXPORT int lsb_expand_output_buffer(lsb_output_buffer *b, size_t needed);

/**
 * Append a character to the output buffer.
 *
 * @param b Pointer the b buffer.
 * @param ch Character to append to the b.
 *
 * @return int 0 on success, false if out of memory.
 */
LSB_EXPORT int lsb_outputc(lsb_output_buffer *b, char ch);

/**
 * Append a formatted string to the output buffer.
 *
 * @param b Pointer the b buffer.
 * @param fmt Printf format specifier.
 *
 * @return int 0 on success, false if out of memory.
 */
LSB_EXPORT int lsb_outputf(lsb_output_buffer *b, const char *fmt, ...);

/**
 * Append a fixed string to the output buffer.
 *
 * @param b Pointer the b buffer.
 * @param str String to append to the b.
 * @param len Length of the string to append
 *
 * @return int 0 on success, false if out of memory.
 */
LSB_EXPORT int lsb_outputs(lsb_output_buffer *b,
                           const char *str,
                           size_t len);

/**
 * More efficient output of a double to a string. NaN/Inf check and then calls
 * lsb_outputfd.
 *
 * @param output Pointer the output buffer.
 * @param d Double value to convert to a string.
 *
 * @return int 0 on success, false if out of memory.
 */
LSB_EXPORT int lsb_outputd(lsb_output_buffer *output, double d);


/**
 * More efficient output of a double to a string; no NaN or Inf outputs.
 *
 * @param output Pointer the output buffer.
 * @param d Double value to convert to a string.
 *
 * @return int 0 on success, false if out of memory.
 */
LSB_EXPORT int lsb_outputfd(lsb_output_buffer *ob, double d);

#ifdef __cplusplus
}
#endif

#endif
