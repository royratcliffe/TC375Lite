/*!
 * \file matf.h
 * \copyright Roy Ratcliffe, Northumberland, United Kingdom
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge,  to any person obtaining a
 * copy  of  this  software  and    associated   documentation  files  (the
 * "Software"), to deal in  the   Software  without  restriction, including
 * without limitation the rights to  use,   copy,  modify,  merge, publish,
 * distribute, sublicense, and/or sell  copies  of   the  Software,  and to
 * permit persons to whom the Software is   furnished  to do so, subject to
 * the following conditions:
 *
 *     The above copyright notice and this permission notice shall be
 *     included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT  WARRANTY OF ANY KIND, EXPRESS
 * OR  IMPLIED,  INCLUDING  BUT  NOT   LIMITED    TO   THE   WARRANTIES  OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR   PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS  OR   COPYRIGHT  HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY,  WHETHER   IN  AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM,  OUT  OF   OR  IN  CONNECTION  WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <stddef.h>

#include "build_assert.h"

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(__x__) (sizeof(__x__) / sizeof(__x__[0]))
#endif

#define MAT_ROWS_OF(__A__) ARRAY_SIZE(__A__)

#define MAT_COLS_OF(__A__) ARRAY_SIZE(__A__[0])

#define MATF_DEFINE(__A__, __m__, __n__) static float __A__[__m__][__n__]

/*!
 * \brief Performs a single-precision general matrix multiplication operation.
 *
 * Multiplies the first two matrix arguments, giving the resulting product in
 * the third matrix. The matrix dimensions must make sense. The macro fails at
 * compile time if the following constraints prove false.
 *
 * 1.  The number of rows in \e{A} must match the number of rows in \e{C}.
 * 2.  The number of columns in \e{B} must match the number in \e{C}.
 * 3.  The number of columns in \e{A} must match the number of rows in \e{B}.
 */
#define MATF_MULTIPLY(__A__, __B__, __C__)                                     \
  {                                                                            \
    BUILD_ASSERT(MAT_ROWS_OF(__A__) == MAT_ROWS_OF(__C__) &&                   \
                 MAT_COLS_OF(__B__) == MAT_COLS_OF(__C__) &&                   \
                 MAT_COLS_OF(__A__) == MAT_ROWS_OF(__B__));                    \
    const size_t __m__ = MAT_ROWS_OF(__A__);                                   \
    const size_t __n__ = MAT_COLS_OF(__B__);                                   \
    const size_t __k__ = MAT_COLS_OF(__A__);                                   \
    for (size_t __j__ = 0; __j__ < __n__; __j__++)                             \
      for (size_t __i__ = 0; __i__ < __m__; __i__++) {                         \
        register float __c__ = 0.0F;                                           \
        for (size_t __l__ = 0; __l__ < __k__; __l__++)                         \
          __c__ += __A__[__l__][__i__] * __B__[__j__][__l__];                  \
        __C__[__i__][__j__] = __c__;                                           \
      }                                                                        \
  }
