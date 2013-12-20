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

/**
 * @file mat4.c
 */
#include <memory.h>
#include <assert.h>
#include <stdlib.h>

#include "kazmath/utility.h"
#include "kazmath/vec3.h"
#include "kazmath/mat4.h"
#include "kazmath/mat3.h"
#include "kazmath/quaternion.h"
#include "kazmath/plane.h"

#include "kazmath/neon_matrix_impl.h"

/**
 * Fills a kmMat4 structure with the values from a 16
 * element array of floats
 * @Params pOut - A pointer to the destination matrix
 *            pMat - A 16 element array of floats
 * @Return Returns pOut so that the call can be nested
 */
kmMat4* const kmMat4Fill(kmMat4* pOut, const kmScalar* pMat)
{
    memcpy(pOut->mat, pMat, sizeof(kmScalar) * 16);
    return pOut;
}

/**
 * Sets pOut to an identity matrix returns pOut
 * @Params pOut - A pointer to the matrix to set to identity
 * @Return Returns pOut so that the call can be nested
 */
kmMat4* const kmMat4Identity(kmMat4* pOut)
{
    memset(pOut->mat, 0, sizeof(float) * 16);
    pOut->mat[0] = pOut->mat[5] = pOut->mat[10] = pOut->mat[15] = 1.0f;
    return pOut;
}


float get(const kmMat4 * pIn, int row, int col)
{
    return pIn->mat[row + 4*col];
}

void set(kmMat4 * pIn, int row, int col, float value)
{
    pIn->mat[row + 4*col] = value;
}

void swap(kmMat4 * pIn, int r1, int c1, int r2, int c2)
{
    float tmp = get(pIn,r1,c1);
    set(pIn,r1,c1,get(pIn,r2,c2));
    set(pIn,r2,c2, tmp);
}

//Returns an upper and a lower triangular matrix which are L and R in the Gauss algorithm
int gaussj(kmMat4 *a, kmMat4 *b)
{
    int i, icol = 0, irow = 0, j, k, l, ll, n = 4, m = 4;
    float big, dum, pivinv;
    int indxc[4] = {0};
    int indxr[4] = {0};
    int ipiv[4] = {0};

    for (j = 0; j < n; j++) {
        ipiv[j] = 0;
    }

    for (i = 0; i < n; i++) {
        big = 0.0f;
        for (j = 0; j < n; j++) {
            if (ipiv[j] != 1) {
                for (k = 0; k < n; k++) {
                    if (ipiv[k] == 0) {
                        if (abs(get(a,j, k)) >= big) {
                            big = abs(get(a,j, k));
                            irow = j;
                            icol = k;
                        }
                    }
                }
            }
        }
        ++(ipiv[icol]);
        if (irow != icol) {
            for (l = 0; l < n; l++) {
                swap(a,irow, l, icol, l);
            }
            for (l = 0; l < m; l++) {
                swap(b,irow, l, icol, l);
            }
        }
        indxr[i] = irow;
        indxc[i] = icol;
        if (get(a,icol, icol) == 0.0) {
            return KM_FALSE;
        }
        pivinv = 1.0f / get(a,icol, icol);
        set(a,icol, icol, 1.0f);
        for (l = 0; l < n; l++) {
            set(a,icol, l, get(a,icol, l) * pivinv);
        }
        for (l = 0; l < m; l++) {
            set(b,icol, l, get(b,icol, l) * pivinv);
        }

        for (ll = 0; ll < n; ll++) {
            if (ll != icol) {
                dum = get(a,ll, icol);
                set(a,ll, icol, 0.0f);
                for (l = 0; l < n; l++) {
                    set(a,ll, l, get(a,ll, l) - get(a,icol, l) * dum);
                }
                for (l = 0; l < m; l++) {
                    set(b,ll, l, get(a,ll, l) - get(b,icol, l) * dum);
                }
            }
        }
    }
//    This is the end of the main loop over columns of the reduction. It only remains to unscram-
//    ble the solution in view of the column interchanges. We do this by interchanging pairs of
//    columns in the reverse order that the permutation was built up.
    for (l = n - 1; l >= 0; l--) {
        if (indxr[l] != indxc[l]) {
            for (k = 0; k < n; k++) {
                swap(a,k, indxr[l], k, indxc[l]);
            }
        }
    }
    return KM_TRUE;
}

/**
 * Calculates the inverse of pM and stores the result in
 * pOut.
 * @Return Returns NULL if there is no inverse, else pOut
 */
kmMat4* const kmMat4Inverse(kmMat4* pOut, const kmMat4* pM)
{
    kmMat4 inv;
    kmMat4 tmp;

    kmMat4Assign(&inv, pM);

    kmMat4Identity(&tmp);

    if(gaussj(&inv, &tmp) == KM_FALSE) {
        return NULL;
    }

    kmMat4Assign(pOut, &inv);
    return pOut;
}
/**
 * Returns KM_TRUE if pIn is an identity matrix
 * KM_FALSE otherwise
 */
const int  kmMat4IsIdentity(const kmMat4* pIn)
{
    static const float identity [] = {     1.0f, 0.0f, 0.0f, 0.0f,
                                        0.0f, 1.0f, 0.0f, 0.0f,
                                        0.0f, 0.0f, 1.0f, 0.0f,
                                        0.0f, 0.0f, 0.0f, 1.0f
                                     };

    return (memcmp(identity, pIn->mat, sizeof(float) * 16) == 0);
}

/**
 * Sets pOut to the transpose of pIn, returns pOut
 */
kmMat4* const kmMat4Transpose(kmMat4* pOut, const kmMat4* pIn)
{
    int x, z;

    for (z = 0; z < 4; ++z) {
        for (x = 0; x < 4; ++x) {
        pOut->mat[(z * 4) + x] = pIn->mat[(x * 4) + z];
        }
    }

    return pOut;
}

/**
 * Multiplies pM1 with pM2, stores the result in pOut, returns pOut
 */
kmMat4* const kmMat4Multiply(kmMat4* pOut, const kmMat4* pM1, const kmMat4* pM2)
{
#if defined(__ARM_NEON__) && !defined(__arm64__)

    // It is possible to skip the memcpy() since "out" does not overwrite p1 or p2.
    // otherwise a temp must be needed.
    float *mat = pOut->mat;

    // Invert column-order with row-order
    NEON_Matrix4Mul( &pM2->mat[0], &pM1->mat[0], &mat[0] );

#else
    float mat[16];

    const float *m1 = pM1->mat, *m2 = pM2->mat;

    mat[0] = m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2] + m1[12] * m2[3];
    mat[1] = m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2] + m1[13] * m2[3];
    mat[2] = m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2] + m1[14] * m2[3];
    mat[3] = m1[3] * m2[0] + m1[7] * m2[1] + m1[11] * m2[2] + m1[15] * m2[3];

    mat[4] = m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6] + m1[12] * m2[7];
    mat[5] = m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6] + m1[13] * m2[7];
    mat[6] = m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6] + m1[14] * m2[7];
    mat[7] = m1[3] * m2[4] + m1[7] * m2[5] + m1[11] * m2[6] + m1[15] * m2[7];

    mat[8] = m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10] + m1[12] * m2[11];
    mat[9] = m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10] + m1[13] * m2[11];
    mat[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10] + m1[14] * m2[11];
    mat[11] = m1[3] * m2[8] + m1[7] * m2[9] + m1[11] * m2[10] + m1[15] * m2[11];

    mat[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14] + m1[12] * m2[15];
    mat[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14] + m1[13] * m2[15];
    mat[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15];
    mat[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15];

    memcpy(pOut->mat, mat, sizeof(pOut->mat));

#endif

    return pOut;
}

/**
 * Assigns the value of pIn to pOut
 */
kmMat4* const kmMat4Assign(kmMat4* pOut, const kmMat4* pIn)
{
    assert(pOut != pIn && "You have tried to self-assign!!");

    memcpy(pOut->mat, pIn->mat, sizeof(float)*16);

    return pOut;
}

/**
 * Returns KM_TRUE if the 2 matrices are equal (approximately)
 */
const int kmMat4AreEqual(const kmMat4* pMat1, const kmMat4* pMat2)
{
    int i = 0;

    assert(pMat1 != pMat2 && "You are comparing the same thing!");

    for (i = 0; i < 16; ++i)
    {
        if (!(pMat1->mat[i] + kmEpsilon > pMat2->mat[i] &&
            pMat1->mat[i] - kmEpsilon < pMat2->mat[i])) {
            return KM_FALSE;
        }
    }

    return KM_TRUE;
}

/**
 * Build a rotation matrix from an axis and an angle. Result is stored in pOut.
 * pOut is returned.
 */
kmMat4* const kmMat4RotationAxisAngle(kmMat4* pOut, const kmVec3* axis, kmScalar radians)
{
    float rcos = cosf(radians);
    float rsin = sinf(radians);

    kmVec3 normalizedAxis;
    kmVec3Normalize(&normalizedAxis, axis);

    pOut->mat[0] = rcos + normalizedAxis.x * normalizedAxis.x * (1 - rcos);
    pOut->mat[1] = normalizedAxis.z * rsin + normalizedAxis.y * normalizedAxis.x * (1 - rcos);
    pOut->mat[2] = -normalizedAxis.y * rsin + normalizedAxis.z * normalizedAxis.x * (1 - rcos);
    pOut->mat[3] = 0.0f;

    pOut->mat[4] = -normalizedAxis.z * rsin + normalizedAxis.x * normalizedAxis.y * (1 - rcos);
    pOut->mat[5] = rcos + normalizedAxis.y * normalizedAxis.y * (1 - rcos);
    pOut->mat[6] = normalizedAxis.x * rsin + normalizedAxis.z * normalizedAxis.y * (1 - rcos);
    pOut->mat[7] = 0.0f;

    pOut->mat[8] = normalizedAxis.y * rsin + normalizedAxis.x * normalizedAxis.z * (1 - rcos);
    pOut->mat[9] = -normalizedAxis.x * rsin + normalizedAxis.y * normalizedAxis.z * (1 - rcos);
    pOut->mat[10] = rcos + normalizedAxis.z * normalizedAxis.z * (1 - rcos);
    pOut->mat[11] = 0.0f;

    pOut->mat[12] = 0.0f;
    pOut->mat[13] = 0.0f;
    pOut->mat[14] = 0.0f;
    pOut->mat[15] = 1.0f;

    return pOut;
}

/**
 * Builds an X-axis rotation matrix and stores it in pOut, returns pOut
 */
kmMat4* const kmMat4RotationX(kmMat4* pOut, const float radians)
{
    /*
         |  1  0       0       0 |
     M = |  0  cos(A) -sin(A)  0 |
         |  0  sin(A)  cos(A)  0 |
         |  0  0       0       1 |

    */

    pOut->mat[0] = 1.0f;
    pOut->mat[1] = 0.0f;
    pOut->mat[2] = 0.0f;
    pOut->mat[3] = 0.0f;

    pOut->mat[4] = 0.0f;
    pOut->mat[5] = cosf(radians);
    pOut->mat[6] = sinf(radians);
    pOut->mat[7] = 0.0f;

    pOut->mat[8] = 0.0f;
    pOut->mat[9] = -sinf(radians);
    pOut->mat[10] = cosf(radians);
    pOut->mat[11] = 0.0f;

    pOut->mat[12] = 0.0f;
    pOut->mat[13] = 0.0f;
    pOut->mat[14] = 0.0f;
    pOut->mat[15] = 1.0f;

    return pOut;
}

/**
 * Builds a rotation matrix using the rotation around the Y-axis
 * The result is stored in pOut, pOut is returned.
 */
kmMat4* const kmMat4RotationY(kmMat4* pOut, const float radians)
{
    /*
         |  cos(A)  0   sin(A)  0 |
     M = |  0       1   0       0 |
         | -sin(A)  0   cos(A)  0 |
         |  0       0   0       1 |
    */

    pOut->mat[0] = cosf(radians);
    pOut->mat[1] = 0.0f;
    pOut->mat[2] = -sinf(radians);
    pOut->mat[3] = 0.0f;

    pOut->mat[4] = 0.0f;
    pOut->mat[5] = 1.0f;
    pOut->mat[6] = 0.0f;
    pOut->mat[7] = 0.0f;

    pOut->mat[8] = sinf(radians);
    pOut->mat[9] = 0.0f;
    pOut->mat[10] = cosf(radians);
    pOut->mat[11] = 0.0f;

    pOut->mat[12] = 0.0f;
    pOut->mat[13] = 0.0f;
    pOut->mat[14] = 0.0f;
    pOut->mat[15] = 1.0f;

    return pOut;
}

/**
 * Builds a rotation matrix around the Z-axis. The resulting
 * matrix is stored in pOut. pOut is returned.
 */
kmMat4* const kmMat4RotationZ(kmMat4* pOut, const float radians)
{
    /*
         |  cos(A)  -sin(A)   0   0 |
     M = |  sin(A)   cos(A)   0   0 |
         |  0        0        1   0 |
         |  0        0        0   1 |
    */

    pOut->mat[0] = cosf(radians);
    pOut->mat[1] = sinf(radians);
    pOut->mat[2] = 0.0f;
    pOut->mat[3] = 0.0f;

    pOut->mat[4] = -sinf(radians);;
    pOut->mat[5] = cosf(radians);
    pOut->mat[6] = 0.0f;
    pOut->mat[7] = 0.0f;

    pOut->mat[8] = 0.0f;
    pOut->mat[9] = 0.0f;
    pOut->mat[10] = 1.0f;
    pOut->mat[11] = 0.0f;

    pOut->mat[12] = 0.0f;
    pOut->mat[13] = 0.0f;
    pOut->mat[14] = 0.0f;
    pOut->mat[15] = 1.0f;

    return pOut;
}

/**
 * Builds a rotation matrix from pitch, yaw and roll. The resulting
 * matrix is stored in pOut and pOut is returned
 */
kmMat4* const kmMat4RotationPitchYawRoll(kmMat4* pOut, const kmScalar pitch, const kmScalar yaw, const kmScalar roll)
{
    double cr = cos(pitch);
    double sr = sin(pitch);
    double cp = cos(yaw);
    double sp = sin(yaw);
    double cy = cos(roll);
    double sy = sin(roll);
    double srsp = sr * sp;
    double crsp = cr * sp;

    pOut->mat[0] = (kmScalar) cp * cy;
    pOut->mat[4] = (kmScalar) cp * sy;
    pOut->mat[8] = (kmScalar) - sp;

    pOut->mat[1] = (kmScalar) srsp * cy - cr * sy;
    pOut->mat[5] = (kmScalar) srsp * sy + cr * cy;
    pOut->mat[9] = (kmScalar) sr * cp;

    pOut->mat[2] = (kmScalar) crsp * cy + sr * sy;
    pOut->mat[6] = (kmScalar) crsp * sy - sr * cy;
    pOut->mat[10] = (kmScalar) cr * cp;

    pOut->mat[3] = pOut->mat[7] = pOut->mat[11] = 0.0;
    pOut->mat[15] = 1.0;

    return pOut;
}

/** Converts a quaternion to a rotation matrix,
 * the result is stored in pOut, returns pOut
 */
kmMat4* const kmMat4RotationQuaternion(kmMat4* pOut, const kmQuaternion* pQ)
{
    pOut->mat[0] = 1.0f - 2.0f * (pQ->y * pQ->y + pQ->z * pQ->z );
    pOut->mat[1] = 2.0f * (pQ->x * pQ->y + pQ->z * pQ->w);
    pOut->mat[2] = 2.0f * (pQ->x * pQ->z - pQ->y * pQ->w);
    pOut->mat[3] = 0.0f;

    // Second row
    pOut->mat[4] = 2.0f * ( pQ->x * pQ->y - pQ->z * pQ->w );
    pOut->mat[5] = 1.0f - 2.0f * ( pQ->x * pQ->x + pQ->z * pQ->z );
    pOut->mat[6] = 2.0f * (pQ->z * pQ->y + pQ->x * pQ->w );
    pOut->mat[7] = 0.0f;

    // Third row
    pOut->mat[8] = 2.0f * ( pQ->x * pQ->z + pQ->y * pQ->w );
    pOut->mat[9] = 2.0f * ( pQ->y * pQ->z - pQ->x * pQ->w );
    pOut->mat[10] = 1.0f - 2.0f * ( pQ->x * pQ->x + pQ->y * pQ->y );
    pOut->mat[11] = 0.0f;

    // Fourth row
    pOut->mat[12] = 0;
    pOut->mat[13] = 0;
    pOut->mat[14] = 0;
    pOut->mat[15] = 1.0f;

    return pOut;
}

/** Builds a scaling matrix */
kmMat4* const kmMat4Scaling(kmMat4* pOut, const kmScalar x, const kmScalar y,
                      const kmScalar z)
{
    memset(pOut->mat, 0, sizeof(float) * 16);
    pOut->mat[0] = x;
    pOut->mat[5] = y;
    pOut->mat[10] = z;
    pOut->mat[15] = 1.0f;

    return pOut;
}

/**
 * Builds a translation matrix. All other elements in the matrix
 * will be set to zero except for the diagonal which is set to 1.0
 */
kmMat4* const kmMat4Translation(kmMat4* pOut, const kmScalar x,
                          const kmScalar y, const kmScalar z)
{
    //FIXME: Write a test for this
    memset(pOut->mat, 0, sizeof(float) * 16);

    pOut->mat[0] = 1.0f;
    pOut->mat[5] = 1.0f;
    pOut->mat[10] = 1.0f;

    pOut->mat[12] = x;
    pOut->mat[13] = y;
    pOut->mat[14] = z;
    pOut->mat[15] = 1.0f;

    return pOut;
}

/**
 * Get the up vector from a matrix. pIn is the matrix you
 * wish to extract the vector from. pOut is a pointer to the
 * kmVec3 structure that should hold the resulting vector
 */
kmVec3* const kmMat4GetUpVec3(kmVec3* pOut, const kmMat4* pIn)
{
    pOut->x = pIn->mat[4];
    pOut->y = pIn->mat[5];
    pOut->z = pIn->mat[6];

    kmVec3Normalize(pOut, pOut);

    return pOut;
}

/** Extract the right vector from a 4x4 matrix. The result is
 * stored in pOut. Returns pOut.
 */
kmVec3* const kmMat4GetRightVec3(kmVec3* pOut, const kmMat4* pIn)
{
    pOut->x = pIn->mat[0];
    pOut->y = pIn->mat[1];
    pOut->z = pIn->mat[2];

    kmVec3Normalize(pOut, pOut);

    return pOut;
}

/**
 * Extract the forward vector from a 4x4 matrix. The result is
 * stored in pOut. Returns pOut.
 */
kmVec3* const kmMat4GetForwardVec3(kmVec3* pOut, const kmMat4* pIn)
{
    pOut->x = pIn->mat[8];
    pOut->y = pIn->mat[9];
    pOut->z = pIn->mat[10];

    kmVec3Normalize(pOut, pOut);

    return pOut;
}

/**
 * Creates a perspective projection matrix in the
 * same way as gluPerspective
 */
kmMat4* const kmMat4PerspectiveProjection(kmMat4* pOut, kmScalar fovY,
                                    kmScalar aspect, kmScalar zNear,
                                    kmScalar zFar)
{
    kmScalar r = kmDegreesToRadians(fovY / 2);
    kmScalar deltaZ = zFar - zNear;
    kmScalar s = sin(r);
    kmScalar cotangent = 0;

    if (deltaZ == 0 || s == 0 || aspect == 0) {
        return NULL;
    }

    //cos(r) / sin(r) = cot(r)
    cotangent = cos(r) / s;

    kmMat4Identity(pOut);
    pOut->mat[0] = cotangent / aspect;
    pOut->mat[5] = cotangent;
    pOut->mat[10] = -(zFar + zNear) / deltaZ;
    pOut->mat[11] = -1;
    pOut->mat[14] = -2 * zNear * zFar / deltaZ;
    pOut->mat[15] = 0;

    return pOut;
}

/** Creates an orthographic projection matrix like glOrtho */
kmMat4* const kmMat4OrthographicProjection(kmMat4* pOut, kmScalar left,
                                     kmScalar right, kmScalar bottom,
                                     kmScalar top, kmScalar nearVal,
                                     kmScalar farVal)
{
    kmScalar tx = -((right + left) / (right - left));
    kmScalar ty = -((top + bottom) / (top - bottom));
    kmScalar tz = -((farVal + nearVal) / (farVal - nearVal));

    kmMat4Identity(pOut);
    pOut->mat[0] = 2 / (right - left);
    pOut->mat[5] = 2 / (top - bottom);
    pOut->mat[10] = -2 / (farVal - nearVal);
    pOut->mat[12] = tx;
    pOut->mat[13] = ty;
    pOut->mat[14] = tz;

    return pOut;
}

/**
 * Builds a translation matrix in the same way as gluLookAt()
 * the resulting matrix is stored in pOut. pOut is returned.
 */
kmMat4* const kmMat4LookAt(kmMat4* pOut, const kmVec3* pEye,
                     const kmVec3* pCenter, const kmVec3* pUp)
{
    kmVec3 f, up, s, u;
    kmMat4 translate;

    kmVec3Subtract(&f, pCenter, pEye);
    kmVec3Normalize(&f, &f);

    kmVec3Assign(&up, pUp);
    kmVec3Normalize(&up, &up);

    kmVec3Cross(&s, &f, &up);
    kmVec3Normalize(&s, &s);

    kmVec3Cross(&u, &s, &f);
    kmVec3Normalize(&s, &s);

    kmMat4Identity(pOut);

    pOut->mat[0] = s.x;
    pOut->mat[4] = s.y;
    pOut->mat[8] = s.z;

    pOut->mat[1] = u.x;
    pOut->mat[5] = u.y;
    pOut->mat[9] = u.z;

    pOut->mat[2] = -f.x;
    pOut->mat[6] = -f.y;
    pOut->mat[10] = -f.z;

    kmMat4Translation(&translate, -pEye->x, -pEye->y, -pEye->z);
    kmMat4Multiply(pOut, pOut, &translate);

    return pOut;
}

/**
 * Extract a 3x3 rotation matrix from the input 4x4 transformation.
 * Stores the result in pOut, returns pOut
 */
kmMat3* const kmMat4ExtractRotation(kmMat3* pOut, const kmMat4* pIn)
{
    pOut->mat[0] = pIn->mat[0];
    pOut->mat[1] = pIn->mat[1];
    pOut->mat[2] = pIn->mat[2];

    pOut->mat[3] = pIn->mat[4];
    pOut->mat[4] = pIn->mat[5];
    pOut->mat[5] = pIn->mat[6];

    pOut->mat[6] = pIn->mat[8];
    pOut->mat[7] = pIn->mat[9];
    pOut->mat[8] = pIn->mat[10];

    return pOut;
}

/**
 * Take the rotation from a 4x4 transformation matrix, and return it as an axis and an angle (in radians)
 * returns the output axis.
 */
kmVec3* const kmMat4RotationToAxisAngle(kmVec3* pAxis, kmScalar* radians, const kmMat4* pIn)
{
    /*Surely not this easy?*/
    kmQuaternion temp;
    kmMat3 rotation;
    kmMat4ExtractRotation(&rotation, pIn);
    kmQuaternionRotationMatrix(&temp, &rotation);
    kmQuaternionToAxisAngle(&temp, pAxis, radians);
    return pAxis;
}

/** Build a 4x4 OpenGL transformation matrix using a 3x3 rotation matrix,
 * and a 3d vector representing a translation. Assign the result to pOut,
 * pOut is also returned.
 */
kmMat4* const kmMat4RotationTranslation(kmMat4* pOut, const kmMat3* rotation, const kmVec3* translation)
{
    pOut->mat[0] = rotation->mat[0];
    pOut->mat[1] = rotation->mat[1];
    pOut->mat[2] = rotation->mat[2];
    pOut->mat[3] = 0.0f;

    pOut->mat[4] = rotation->mat[3];
    pOut->mat[5] = rotation->mat[4];
    pOut->mat[6] = rotation->mat[5];
    pOut->mat[7] = 0.0f;

    pOut->mat[8] = rotation->mat[6];
    pOut->mat[9] = rotation->mat[7];
    pOut->mat[10] = rotation->mat[8];
    pOut->mat[11] = 0.0f;

    pOut->mat[12] = translation->x;
    pOut->mat[13] = translation->y;
    pOut->mat[14] = translation->z;
    pOut->mat[15] = 1.0f;

    return pOut;
}

kmPlane* const kmMat4ExtractPlane(kmPlane* pOut, const kmMat4* pIn, const kmEnum plane)
{
    float t = 1.0f;

    switch(plane) {
        case KM_PLANE_RIGHT:
            pOut->a = pIn->mat[3] - pIn->mat[0];
            pOut->b = pIn->mat[7] - pIn->mat[4];
            pOut->c = pIn->mat[11] - pIn->mat[8];
            pOut->d = pIn->mat[15] - pIn->mat[12];
        break;
        case KM_PLANE_LEFT:
            pOut->a = pIn->mat[3] + pIn->mat[0];
            pOut->b = pIn->mat[7] + pIn->mat[4];
            pOut->c = pIn->mat[11] + pIn->mat[8];
            pOut->d = pIn->mat[15] + pIn->mat[12];
        break;
        case KM_PLANE_BOTTOM:
            pOut->a = pIn->mat[3] + pIn->mat[1];
            pOut->b = pIn->mat[7] + pIn->mat[5];
            pOut->c = pIn->mat[11] + pIn->mat[9];
            pOut->d = pIn->mat[15] + pIn->mat[13];
        break;
        case KM_PLANE_TOP:
            pOut->a = pIn->mat[3] - pIn->mat[1];
            pOut->b = pIn->mat[7] - pIn->mat[5];
            pOut->c = pIn->mat[11] - pIn->mat[9];
            pOut->d = pIn->mat[15] - pIn->mat[13];
        break;
        case KM_PLANE_FAR:
            pOut->a = pIn->mat[3] - pIn->mat[2];
            pOut->b = pIn->mat[7] - pIn->mat[6];
            pOut->c = pIn->mat[11] - pIn->mat[10];
            pOut->d = pIn->mat[15] - pIn->mat[14];
        break;
        case KM_PLANE_NEAR:
            pOut->a = pIn->mat[3] + pIn->mat[2];
            pOut->b = pIn->mat[7] + pIn->mat[6];
            pOut->c = pIn->mat[11] + pIn->mat[10];
            pOut->d = pIn->mat[15] + pIn->mat[14];
        break;
        default:
            assert(0 && "Invalid plane index");
    }

    t = sqrtf(pOut->a * pOut->a +
                    pOut->b * pOut->b +
                    pOut->c * pOut->c);
    pOut->a /= t;
    pOut->b /= t;
    pOut->c /= t;
    pOut->d /= t;

    return pOut;
}
