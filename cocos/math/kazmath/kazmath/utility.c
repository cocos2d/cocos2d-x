/*
Copyright (c) 2008, Luke Benstead.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "utility.h"

/**
 * Returns the square of s (e.g. s*s)
 */
kmScalar kmSQR(kmScalar s) {
	return s*s;
}

/**
 * Returns degrees as radians.
 */
kmScalar kmDegreesToRadians(kmScalar degrees) {
	return degrees * kmPIOver180;
}

/**
 * Returns radians as degrees
 */
kmScalar kmRadiansToDegrees(kmScalar radians) {
	return radians * kmPIUnder180;
}

kmScalar kmMin(kmScalar lhs, kmScalar rhs) {
    return (lhs < rhs)? lhs : rhs;
}

kmScalar kmMax(kmScalar lhs, kmScalar rhs) {
    return (lhs > rhs)? lhs : rhs;
}

kmBool kmAlmostEqual(kmScalar lhs, kmScalar rhs) {
    return (lhs + kmEpsilon > rhs && lhs - kmEpsilon < rhs);
}

kmScalar kmClamp(kmScalar x, kmScalar min, kmScalar max)
{
    return x < min ? min : (x > max ? max : x);
}

kmScalar kmLerp(kmScalar x, kmScalar y, kmScalar t )
{
    return x + t * ( y - x );
}
