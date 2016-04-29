/* Copyright (c) 2013 Scott Lembcke and Howling Moon Software
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifdef CHIPMUNK_FFI

// Create non static inlined copies of Chipmunk functions, useful for working with dynamic FFIs
// This file should only be included in chipmunk.c

// TODO: get rid of the reliance on static inlines.
// They make a mess for FFIs.

#ifdef _MSC_VER
 #if _MSC_VER >= 1600
  #define MAKE_REF(name) CP_EXPORT decltype(name) *_##name = name
 #else
  #define MAKE_REF(name)
 #endif
#else
 #define MAKE_REF(name) __typeof__(name) *_##name = name
#endif

#ifdef __cplusplus
extern "C" {
#endif

MAKE_REF(cpv); // makes a variable named _cpv that contains the function pointer for cpv()
MAKE_REF(cpveql);
MAKE_REF(cpvadd);
MAKE_REF(cpvneg);
MAKE_REF(cpvsub);
MAKE_REF(cpvmult);
MAKE_REF(cpvdot);
MAKE_REF(cpvcross);
MAKE_REF(cpvperp);
MAKE_REF(cpvrperp);
MAKE_REF(cpvproject);
MAKE_REF(cpvforangle);
MAKE_REF(cpvtoangle);
MAKE_REF(cpvrotate);
MAKE_REF(cpvunrotate);
MAKE_REF(cpvlengthsq);
MAKE_REF(cpvlength);
MAKE_REF(cpvlerp);
MAKE_REF(cpvnormalize);
MAKE_REF(cpvclamp);
MAKE_REF(cpvlerpconst);
MAKE_REF(cpvdist);
MAKE_REF(cpvdistsq);
MAKE_REF(cpvnear);

MAKE_REF(cpfmax);
MAKE_REF(cpfmin);
MAKE_REF(cpfabs);
MAKE_REF(cpfclamp);
MAKE_REF(cpflerp);
MAKE_REF(cpflerpconst);

MAKE_REF(cpBBNew);
MAKE_REF(cpBBNewForExtents);
MAKE_REF(cpBBNewForCircle);
MAKE_REF(cpBBIntersects);
MAKE_REF(cpBBContainsBB);
MAKE_REF(cpBBContainsVect);
MAKE_REF(cpBBMerge);
MAKE_REF(cpBBExpand);
MAKE_REF(cpBBCenter);
MAKE_REF(cpBBArea);
MAKE_REF(cpBBMergedArea);
MAKE_REF(cpBBSegmentQuery);
MAKE_REF(cpBBIntersectsSegment);
MAKE_REF(cpBBClampVect);

MAKE_REF(cpSpatialIndexDestroy);
MAKE_REF(cpSpatialIndexCount);
MAKE_REF(cpSpatialIndexEach);
MAKE_REF(cpSpatialIndexContains);
MAKE_REF(cpSpatialIndexInsert);
MAKE_REF(cpSpatialIndexRemove);
MAKE_REF(cpSpatialIndexReindex);
MAKE_REF(cpSpatialIndexReindexObject);
MAKE_REF(cpSpatialIndexSegmentQuery);
MAKE_REF(cpSpatialIndexQuery);
MAKE_REF(cpSpatialIndexReindexQuery);

#ifdef __cplusplus
}
#endif

#endif
