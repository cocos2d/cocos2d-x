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

#ifndef CHIPMUNK_TRANSFORM_H
#define CHIPMUNK_TRANSFORM_H

#include "chipmunk_types.h"
#include "cpVect.h"
#include "cpBB.h"

/// Identity transform matrix.
static const cpTransform cpTransformIdentity = {1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f};

/// Construct a new transform matrix.
/// (a, b) is the x basis vector.
/// (c, d) is the y basis vector.
/// (tx, ty) is the translation.
static inline cpTransform
cpTransformNew(cpFloat a, cpFloat b, cpFloat c, cpFloat d, cpFloat tx, cpFloat ty)
{
	cpTransform t = {a, b, c, d, tx, ty};
	return t;
}

/// Construct a new transform matrix in transposed order.
static inline cpTransform
cpTransformNewTranspose(cpFloat a, cpFloat c, cpFloat tx, cpFloat b, cpFloat d, cpFloat ty)
{
	cpTransform t = {a, b, c, d, tx, ty};
	return t;
}

/// Get the inverse of a transform matrix.
static inline cpTransform
cpTransformInverse(cpTransform t)
{
  cpFloat inv_det = 1.0/(t.a*t.d - t.c*t.b);
  return cpTransformNewTranspose(
     t.d*inv_det, -t.c*inv_det, (t.c*t.ty - t.tx*t.d)*inv_det,
    -t.b*inv_det,  t.a*inv_det, (t.tx*t.b - t.a*t.ty)*inv_det
  );
}

/// Multiply two transformation matrices.
static inline cpTransform
cpTransformMult(cpTransform t1, cpTransform t2)
{
  return cpTransformNewTranspose(
    t1.a*t2.a + t1.c*t2.b, t1.a*t2.c + t1.c*t2.d, t1.a*t2.tx + t1.c*t2.ty + t1.tx,
    t1.b*t2.a + t1.d*t2.b, t1.b*t2.c + t1.d*t2.d, t1.b*t2.tx + t1.d*t2.ty + t1.ty
  );
}

/// Transform an absolute point. (i.e. a vertex)
static inline cpVect
cpTransformPoint(cpTransform t, cpVect p)
{
  return cpv(t.a*p.x + t.c*p.y + t.tx, t.b*p.x + t.d*p.y + t.ty);
}

/// Transform a vector (i.e. a normal)
static inline cpVect
cpTransformVect(cpTransform t, cpVect v)
{
  return cpv(t.a*v.x + t.c*v.y, t.b*v.x + t.d*v.y);
}

/// Transform a cpBB.
static inline cpBB
cpTransformbBB(cpTransform t, cpBB bb)
{
	cpVect center = cpBBCenter(bb);
	cpFloat hw = (bb.r - bb.l)*0.5;
	cpFloat hh = (bb.t - bb.b)*0.5;
	
	cpFloat a = t.a*hw, b = t.c*hh, d = t.b*hw, e = t.d*hh;
	cpFloat hw_max = cpfmax(cpfabs(a + b), cpfabs(a - b));
	cpFloat hh_max = cpfmax(cpfabs(d + e), cpfabs(d - e));
	return cpBBNewForExtents(cpTransformPoint(t, center), hw_max, hh_max);
}

/// Create a transation matrix.
static inline cpTransform
cpTransformTranslate(cpVect translate)
{
  return cpTransformNewTranspose(
    1.0, 0.0, translate.x,
    0.0, 1.0, translate.y
  );
}

/// Create a scale matrix.
static inline cpTransform
cpTransformScale(cpFloat scaleX, cpFloat scaleY)
{
	return cpTransformNewTranspose(
		scaleX,    0.0, 0.0,
		   0.0, scaleY, 0.0
	);
}

/// Create a rotation matrix.
static inline cpTransform
cpTransformRotate(cpFloat radians)
{
	cpVect rot = cpvforangle(radians);
	return cpTransformNewTranspose(
		rot.x, -rot.y, 0.0,
		rot.y,  rot.x, 0.0
	);
}

/// Create a rigid transformation matrix. (transation + rotation)
static inline cpTransform
cpTransformRigid(cpVect translate, cpFloat radians)
{
	cpVect rot = cpvforangle(radians);
	return cpTransformNewTranspose(
		rot.x, -rot.y, translate.x,
		rot.y,  rot.x, translate.y
	);
}

/// Fast inverse of a rigid transformation matrix.
static inline cpTransform
cpTransformRigidInverse(cpTransform t)
{
  return cpTransformNewTranspose(
     t.d, -t.c, (t.c*t.ty - t.tx*t.d),
    -t.b,  t.a, (t.tx*t.b - t.a*t.ty)
  );
}

//MARK: Miscellaneous (but useful) transformation matrices.
// See source for documentation...

static inline cpTransform
cpTransformWrap(cpTransform outer, cpTransform inner)
{
  return cpTransformMult(cpTransformInverse(outer), cpTransformMult(inner, outer));
}

static inline cpTransform
cpTransformWrapInverse(cpTransform outer, cpTransform inner)
{
  return cpTransformMult(outer, cpTransformMult(inner, cpTransformInverse(outer)));
}

static inline cpTransform
cpTransformOrtho(cpBB bb)
{
  return cpTransformNewTranspose(
    2.0/(bb.r - bb.l), 0.0, -(bb.r + bb.l)/(bb.r - bb.l),
    0.0, 2.0/(bb.t - bb.b), -(bb.t + bb.b)/(bb.t - bb.b)
  );
}

static inline cpTransform
cpTransformBoneScale(cpVect v0, cpVect v1)
{
  cpVect d = cpvsub(v1, v0); 
  return cpTransformNewTranspose(
    d.x, -d.y, v0.x,
    d.y,  d.x, v0.y
  );
}

static inline cpTransform
cpTransformAxialScale(cpVect axis, cpVect pivot, cpFloat scale)
{
  cpFloat A = axis.x*axis.y*(scale - 1.0);
  cpFloat B = cpvdot(axis, pivot)*(1.0 - scale);
  
  return cpTransformNewTranspose(
    scale*axis.x*axis.x + axis.y*axis.y, A, axis.x*B,
    A, axis.x*axis.x + scale*axis.y*axis.y, axis.y*B
  );
}

#endif
