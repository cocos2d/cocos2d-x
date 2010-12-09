/* libs/graphics/sgl/SkGeometry.h
**
** Copyright 2006, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License"); 
** you may not use this file except in compliance with the License. 
** You may obtain a copy of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** Unless required by applicable law or agreed to in writing, software 
** distributed under the License is distributed on an "AS IS" BASIS, 
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
** See the License for the specific language governing permissions and 
** limitations under the License.
*/

#ifndef SkGeometry_DEFINED
#define SkGeometry_DEFINED

#include "SkMatrix.h"

/** Given a quadratic equation Ax^2 + Bx + C = 0, return 0, 1, 2 roots for the
    equation.
*/
int SkFindUnitQuadRoots(SkScalar A, SkScalar B, SkScalar C, SkScalar roots[2]);

///////////////////////////////////////////////////////////////////////////////

/** Set pt to the point on the src quadratic specified by t. t must be
    0 <= t <= 1.0
*/
void SkEvalQuadAt(const SkPoint src[3], SkScalar t, SkPoint* pt, SkVector* tangent = NULL);
void SkEvalQuadAtHalf(const SkPoint src[3], SkPoint* pt, SkVector* tangent = NULL);

/** Given a src quadratic bezier, chop it at the specified t value,
    where 0 < t < 1, and return the two new quadratics in dst:
    dst[0..2] and dst[2..4]
*/
void SkChopQuadAt(const SkPoint src[3], SkPoint dst[5], SkScalar t);

/** Given a src quadratic bezier, chop it at the specified t == 1/2,
    The new quads are returned in dst[0..2] and dst[2..4]
*/
void SkChopQuadAtHalf(const SkPoint src[3], SkPoint dst[5]);

/** Given the 3 coefficients for a quadratic bezier (either X or Y values), look
    for extrema, and return the number of t-values that are found that represent
    these extrema. If the quadratic has no extrema betwee (0..1) exclusive, the
    function returns 0.
    Returned count      tValues[]
    0                   ignored
    1                   0 < tValues[0] < 1
*/
int SkFindQuadExtrema(SkScalar a, SkScalar b, SkScalar c, SkScalar tValues[1]);

/** Given 3 points on a quadratic bezier, chop it into 1, 2 beziers such that
    the resulting beziers are monotonic in Y. This is called by the scan converter.
    Depending on what is returned, dst[] is treated as follows
    1   dst[0..2] is the original quad
    2   dst[0..2] and dst[2..4] are the two new quads
    If dst == null, it is ignored and only the count is returned.
*/
int SkChopQuadAtYExtrema(const SkPoint src[3], SkPoint dst[5]);

/** Given 3 points on a quadratic bezier, divide it into 2 quadratics
    if the point of maximum curvature exists on the quad segment.
    Depending on what is returned, dst[] is treated as follows
    1   dst[0..2] is the original quad
    2   dst[0..2] and dst[2..4] are the two new quads
    If dst == null, it is ignored and only the count is returned.
*/
int SkChopQuadAtMaxCurvature(const SkPoint src[3], SkPoint dst[5]);

////////////////////////////////////////////////////////////////////////////////////////

/** Convert from parametric from (pts) to polynomial coefficients
    coeff[0]*T^3 + coeff[1]*T^2 + coeff[2]*T + coeff[3]
*/
void SkGetCubicCoeff(const SkPoint pts[4], SkScalar cx[4], SkScalar cy[4]);

/** Set pt to the point on the src cubic specified by t. t must be
    0 <= t <= 1.0
*/
void SkEvalCubicAt(const SkPoint src[4], SkScalar t, SkPoint* locOrNull, SkVector* tangentOrNull, SkVector* curvatureOrNull);

/** Given a src cubic bezier, chop it at the specified t value,
    where 0 < t < 1, and return the two new cubics in dst:
    dst[0..3] and dst[3..6]
*/
void SkChopCubicAt(const SkPoint src[4], SkPoint dst[7], SkScalar t);
void SkChopCubicAt(const SkPoint src[4], SkPoint dst[7], const SkScalar t[], int t_count);

/** Given a src cubic bezier, chop it at the specified t == 1/2,
    The new cubics are returned in dst[0..3] and dst[3..6]
*/
void SkChopCubicAtHalf(const SkPoint src[4], SkPoint dst[7]);

/** Given the 4 coefficients for a cubic bezier (either X or Y values), look
    for extrema, and return the number of t-values that are found that represent
    these extrema. If the cubic has no extrema betwee (0..1) exclusive, the
    function returns 0.
    Returned count      tValues[]
    0                   ignored
    1                   0 < tValues[0] < 1
    2                   0 < tValues[0] < tValues[1] < 1
*/
int SkFindCubicExtrema(SkScalar a, SkScalar b, SkScalar c, SkScalar d, SkScalar tValues[2]);

/** Given 4 points on a cubic bezier, chop it into 1, 2, 3 beziers such that
    the resulting beziers are monotonic in Y. This is called by the scan converter.
    Depending on what is returned, dst[] is treated as follows
    1   dst[0..3] is the original cubic
    2   dst[0..3] and dst[3..6] are the two new cubics
    3   dst[0..3], dst[3..6], dst[6..9] are the three new cubics
    If dst == null, it is ignored and only the count is returned.
*/
int SkChopCubicAtYExtrema(const SkPoint src[4], SkPoint dst[10]);

/** Given a cubic bezier, return 0, 1, or 2 t-values that represent the
    inflection points.
*/
int SkFindCubicInflections(const SkPoint src[4], SkScalar tValues[2]);

/** Return 1 for no chop, or 2 for having chopped the cubic at its
    inflection point.
*/
int SkChopCubicAtInflections(const SkPoint src[4], SkPoint dst[10]);

int SkFindCubicMaxCurvature(const SkPoint src[4], SkScalar tValues[3]);
int SkChopCubicAtMaxCurvature(const SkPoint src[4], SkPoint dst[13], SkScalar tValues[3] = NULL);

///////////////////////////////////////////////////////////////////////////////////////////

enum SkRotationDirection {
    kCW_SkRotationDirection,
    kCCW_SkRotationDirection
};

/** Maximum number of points needed in the quadPoints[] parameter for
    SkBuildQuadArc()
*/
#define kSkBuildQuadArcStorage  17

/** Given 2 unit vectors and a rotation direction, fill out the specified
    array of points with quadratic segments. Return is the number of points
    written to, which will be { 0, 3, 5, 7, ... kSkBuildQuadArcStorage }

    matrix, if not null, is appled to the points before they are returned.
*/
int SkBuildQuadArc(const SkVector& unitStart, const SkVector& unitStop, SkRotationDirection,
                   const SkMatrix* matrix, SkPoint quadPoints[]);

#endif
