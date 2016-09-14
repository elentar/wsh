/* Copyright (c) 2013 William Orr <will@worrbase.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "config.h"
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef HAVE_EXPLICIT_BZERO
int memset_s(void* v, size_t smax, int c, size_t n) {
	if (v == NULL) return EINVAL;
	if (smax > SIZE_MAX) return EINVAL;
	if (n > smax) return EINVAL;

	volatile unsigned char *p = v;
	while (smax-- && n--) *p++ = c;

	/* break lto eliding memset_s */
	__asm__ __volatile__("" : : "r"(v) : "memory");

	return 0;
}
#else
#include <string.h>
int memset_s(void* v, size_t smax, int c, size_t n) {
	explicit_bzero(v, n);
	return 0;
}
#endif

