/* ===-- udivdi3.c - Implement __udivdi3 -----------------------------------===
 *
 *                    The LLVM Compiler Infrastructure
 *
 * This file is dual licensed under the MIT and the University of Illinois Open
 * Source Licenses. See LICENSE.TXT for details.
 *
 * ===----------------------------------------------------------------------===
 *
 * This file implements __udivdi3 for the compiler_rt library.
 *
 * ===----------------------------------------------------------------------===
 */

#include "int_lib.h"

du_int COMPILER_RT_ABI __udivmoddi4(du_int a, du_int b, du_int* rem);

/* Returns: a / b */

COMPILER_RT_ABI du_int
__udivdi3(du_int a, du_int b)
{
    return __udivmoddi4(a, b, 0);
}

/* XXX EMSCRIPTEN */

COMPILER_RT_ABI du_int
__uremdi3(du_int a, du_int b)
{
    du_int rem;
    __udivmoddi4(a, b, &rem);
    return rem;
}

