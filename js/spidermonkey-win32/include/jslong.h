/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Mozilla Communicator client code, released
 * March 31, 1998.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either of the GNU General Public License Version 2 or later (the "GPL"),
 * or the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

/*
** File:                jslong.h
** Description: Portable access to 64 bit numerics
**
** Long-long (64-bit signed integer type) support. Some C compilers
** don't support 64 bit integers yet, so we use these macros to
** support both machines that do and don't.
**/
#ifndef jslong_h___
#define jslong_h___

#include "jstypes.h"

JS_BEGIN_EXTERN_C

#define JSLL_INIT(hi, lo)  ((((JSInt64)(hi)) << 32) + (JSInt64)(lo))

/***********************************************************************
** MACROS:      JSLL_*
** DESCRIPTION:
**      The following macros define portable access to the 64 bit
**      math facilities.
**
***********************************************************************/

/***********************************************************************
** MACROS:      JSLL_<relational operators>
**
**  JSLL_IS_ZERO        Test for zero
**  JSLL_EQ             Test for equality
**  JSLL_NE             Test for inequality
**  JSLL_GE_ZERO        Test for zero or positive
**  JSLL_CMP            Compare two values
***********************************************************************/
#define JSLL_IS_ZERO(a)       ((a) == 0)
#define JSLL_EQ(a, b)         ((a) == (b))
#define JSLL_NE(a, b)         ((a) != (b))
#define JSLL_GE_ZERO(a)       ((a) >= 0)
#define JSLL_CMP(a, op, b)    ((JSInt64)(a) op (JSInt64)(b))
#define JSLL_UCMP(a, op, b)   ((JSUint64)(a) op (JSUint64)(b))

/***********************************************************************
** MACROS:      JSLL_<logical operators>
**
**  JSLL_AND            Logical and
**  JSLL_OR             Logical or
**  JSLL_XOR            Logical exclusion
**  JSLL_OR2            A disgusting deviation
**  JSLL_NOT            Negation (one's compliment)
***********************************************************************/
#define JSLL_AND(r, a, b)        ((r) = (a) & (b))
#define JSLL_OR(r, a, b)        ((r) = (a) | (b))
#define JSLL_XOR(r, a, b)        ((r) = (a) ^ (b))
#define JSLL_OR2(r, a)        ((r) = (r) | (a))
#define JSLL_NOT(r, a)        ((r) = ~(a))

/***********************************************************************
** MACROS:      JSLL_<mathematical operators>
**
**  JSLL_NEG            Negation (two's compliment)
**  JSLL_ADD            Summation (two's compliment)
**  JSLL_SUB            Difference (two's compliment)
***********************************************************************/
#define JSLL_NEG(r, a)        ((r) = -(a))
#define JSLL_ADD(r, a, b)     ((r) = (a) + (b))
#define JSLL_SUB(r, a, b)     ((r) = (a) - (b))

/***********************************************************************
** MACROS:      JSLL_<mathematical operators>
**
**  JSLL_MUL            Product (two's compliment)
**  JSLL_DIV            Quotient (two's compliment)
**  JSLL_MOD            Modulus (two's compliment)
***********************************************************************/
#define JSLL_MUL(r, a, b)        ((r) = (a) * (b))
#define JSLL_DIV(r, a, b)        ((r) = (a) / (b))
#define JSLL_MOD(r, a, b)        ((r) = (a) % (b))

/***********************************************************************
** MACROS:      JSLL_<shifting operators>
**
**  JSLL_SHL            Shift left [0..64] bits
**  JSLL_SHR            Shift right [0..64] bits with sign extension
**  JSLL_USHR           Unsigned shift right [0..64] bits
**  JSLL_ISHL           Signed shift left [0..64] bits
***********************************************************************/
#define JSLL_SHL(r, a, b)     ((r) = (JSInt64)(a) << (b))
#define JSLL_SHR(r, a, b)     ((r) = (JSInt64)(a) >> (b))
#define JSLL_USHR(r, a, b)    ((r) = (JSUint64)(a) >> (b))
#define JSLL_ISHL(r, a, b)    ((r) = (JSInt64)(a) << (b))

/***********************************************************************
** MACROS:      JSLL_<conversion operators>
**
**  JSLL_L2I            Convert to signed 32 bit
**  JSLL_L2UI           Convert to unsigned 32 bit
**  JSLL_L2F            Convert to floating point
**  JSLL_L2D            Convert to floating point
**  JSLL_I2L            Convert signed to 64 bit
**  JSLL_UI2L           Convert unsigned to 64 bit
**  JSLL_F2L            Convert float to 64 bit
**  JSLL_D2L            Convert float to 64 bit
***********************************************************************/
#define JSLL_L2I(i, l)        ((i) = (JSInt32)(l))
#define JSLL_L2UI(ui, l)        ((ui) = (JSUint32)(l))
#define JSLL_L2F(f, l)        ((f) = (JSFloat64)(l))
#define JSLL_L2D(d, l)        ((d) = (JSFloat64)(l))

#define JSLL_I2L(l, i)        ((l) = (JSInt64)(i))
#define JSLL_UI2L(l, ui)        ((l) = (JSInt64)(ui))
#define JSLL_F2L(l, f)        ((l) = (JSInt64)(f))
#define JSLL_D2L(l, d)        ((l) = (JSInt64)(d))

/***********************************************************************
** MACROS:      JSLL_UDIVMOD
** DESCRIPTION:
**  Produce both a quotient and a remainder given an unsigned
** INPUTS:      JSUint64 a: The dividend of the operation
**              JSUint64 b: The quotient of the operation
** OUTPUTS:     JSUint64 *qp: pointer to quotient
**              JSUint64 *rp: pointer to remainder
***********************************************************************/
#define JSLL_UDIVMOD(qp, rp, a, b) \
    (*(qp) = ((JSUint64)(a) / (b)), \
     *(rp) = ((JSUint64)(a) % (b)))

JS_END_EXTERN_C

#endif /* jslong_h___ */
