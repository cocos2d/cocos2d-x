/* The MIT License

   Copyright (c) 2008, by Attractive Chaos <attractor@live.co.uk>

   Permission is hereby granted, free of charge, to any person obtaining
   a copy of this software and associated documentation files (the
   "Software"), to deal in the Software without restriction, including
   without limitation the rights to use, copy, modify, merge, publish,
   distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to do so, subject to
   the following conditions:

   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
   BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

/*
  An example:

#include "kvec.h"
int main() {
	kvec_t(int) array;
	kv_init(array);
	kv_push(int, array, 10); // append
	kv_a(int, array, 20) = 5; // dynamic
	kv_A(array, 20) = 4; // static
	kv_destroy(array);
	return 0;
}
*/

/*
  2008-09-22 (0.1.0):

	* The initial version.

  2017-19-18 (0.1.1):

	Spine Special Edition
	* Made helper macros for alloc, free and memcpy, which can be overridden.
	* Made these helpers point to the Spine C Runtime alloc and free functions by default
	* Reimplemented kv_resize to use alloc and free instead of realloc
	* Changed kv_push to use kv_resize instead of realloc
	* Removed kv_pushp and kv_a macros because the weren't used
	* Removed stdlib include
*/

#ifndef AC_KVEC_H
#define AC_KVEC_H

#ifndef _kv_free
#define _kv_free(type, p) (FREE(p))
#endif

#ifndef _kv_alloc
#define _kv_alloc(type, s) ((type*)(MALLOC(type, (s))))
#endif

#ifndef _kv_copy
#define _kv_copy(type, d, s, n) memcpy((d), (s), sizeof(type) * (n))
#endif

#define kv_roundup32(x) (--(x), (x)|=(x)>>1, (x)|=(x)>>2, (x)|=(x)>>4, (x)|=(x)>>8, (x)|=(x)>>16, ++(x))

#define kvec_t(type) struct { size_t n, m; type *a; }
#define kv_init(v) ((v).n = (v).m = 0, (v).a = 0)
#define kv_destroy(v) _kv_free(type, (v).a)
#define kv_A(v, i) ((v).a[(i)])
#define kv_array(v) ((v).a)
#define kv_pop(v) ((v).a[--(v).n])
#define kv_size(v) ((v).n)
#define kv_max(v) ((v).m)

#define kv_resize(type, v, s) do {									\
		type* b = _kv_alloc(type, (s));								\
		if (((s) > 0) && ((v).m > 0))								\
			_kv_copy(type, b, (v).a, ((s) < (v).m)? (s) : (v).m);	\
		_kv_free(type, (v).a);										\
		(v).a = b; (v).m = (s);										\
	} while (0)
	
#define kv_trim(type, v) kv_resize(type, (v), kv_size(v))

#define kv_copy(type, v1, v0) do {								\
		if ((v1).m < (v0).n) kv_resize(type, v1, (v0).n);		\
		(v1).n = (v0).n;										\
		_kv_copy(type, (v1).a, (v0).a, (v0).n);					\
	} while (0)													\

#define kv_push(type, v, x) do {								\
		if ((v).n == (v).m) 									\
			kv_resize(type, (v), ((v).m? (v).m<<1 : 2));		\
		(v).a[(v).n++] = (x);									\
	} while (0)

#endif
