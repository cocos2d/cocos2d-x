/* Copyright (c) 2007 Scott Lembcke
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

/// @defgroup cpBBB cpBB
/// Chipmunk's axis-aligned 2D bounding box type along with a few handy routines.
/// @{

/// Chipmunk's axis-aligned 2D bounding box type. (left, bottom, right, top)
typedef struct cpBB{
	cpFloat l, b, r ,t;
} cpBB;

/// Convenience constructor for cpBB structs.
static inline cpBB cpBBNew(const cpFloat l, const cpFloat b, const cpFloat r, const cpFloat t)
{
	cpBB bb = {l, b, r, t};
	return bb;
}

/// Constructs a cpBB for a circle with the given position and radius.
static inline cpBB cpBBNewForCircle(const cpVect p, const cpFloat r)
{
	return cpBBNew(p.x - r, p.y - r, p.x + r, p.y + r);
}

/// Returns true if @c a and @c b intersect.
static inline cpBool cpBBIntersects(const cpBB a, const cpBB b)
{
	return (a.l <= b.r && b.l <= a.r && a.b <= b.t && b.b <= a.t);
}

/// Returns true if @c other lies completely within @c bb.
static inline cpBool cpBBContainsBB(const cpBB bb, const cpBB other)
{
	return (bb.l <= other.l && bb.r >= other.r && bb.b <= other.b && bb.t >= other.t);
}

/// Returns true if @c bb contains @c v.
static inline cpBool cpBBContainsVect(const cpBB bb, const cpVect v)
{
	return (bb.l <= v.x && bb.r >= v.x && bb.b <= v.y && bb.t >= v.y);
}

/// Returns a bounding box that holds both bounding boxes.
static inline cpBB cpBBMerge(const cpBB a, const cpBB b){
	return cpBBNew(
		cpfmin(a.l, b.l),
		cpfmin(a.b, b.b),
		cpfmax(a.r, b.r),
		cpfmax(a.t, b.t)
	);
}

/// Returns a bounding box that holds both @c bb and @c v.
static inline cpBB cpBBExpand(const cpBB bb, const cpVect v){
	return cpBBNew(
		cpfmin(bb.l, v.x),
		cpfmin(bb.b, v.y),
		cpfmax(bb.r, v.x),
		cpfmax(bb.t, v.y)
	);
}

/// Returns the area of the bounding box.
static inline cpFloat cpBBArea(cpBB bb)
{
	return (bb.r - bb.l)*(bb.t - bb.b);
}

/// Merges @c a and @c b and returns the area of the merged bounding box.
static inline cpFloat cpBBMergedArea(cpBB a, cpBB b)
{
	return (cpfmax(a.r, b.r) - cpfmin(a.l, b.l))*(cpfmax(a.t, b.t) - cpfmin(a.b, b.b));
}

#if defined(_WIN32)
#pragma warning(disable:4056)
#endif // #if defined(WIN32)

/// Returns the fraction along the segment query the cpBB is hit. Returns INFINITY if it doesn't hit.
static inline cpFloat cpBBSegmentQuery(cpBB bb, cpVect a, cpVect b)
{
	cpFloat idx = 1.0f/(b.x - a.x);
	cpFloat tx1 = (bb.l == a.x ? -INFINITY : (bb.l - a.x)*idx);
	cpFloat tx2 = (bb.r == a.x ?  INFINITY : (bb.r - a.x)*idx);
	cpFloat txmin = cpfmin(tx1, tx2);
	cpFloat txmax = cpfmax(tx1, tx2);
	
	cpFloat idy = 1.0f/(b.y - a.y);
	cpFloat ty1 = (bb.b == a.y ? -INFINITY : (bb.b - a.y)*idy);
	cpFloat ty2 = (bb.t == a.y ?  INFINITY : (bb.t - a.y)*idy);
	cpFloat tymin = cpfmin(ty1, ty2);
	cpFloat tymax = cpfmax(ty1, ty2);
	
	if(tymin <= txmax && txmin <= tymax){
		cpFloat min = cpfmax(txmin, tymin);
		cpFloat max = cpfmin(txmax, tymax);
		
		if(0.0 <= max && min <= 1.0) return cpfmax(min, 0.0);
	}
	
	return INFINITY;
}

#if defined(_WIN32)
#pragma warning(default:4056)
#endif // #if defined(WIN32)

/// Return true if the bounding box intersects the line segment with ends @c a and @c b.
static inline cpBool cpBBIntersectsSegment(cpBB bb, cpVect a, cpVect b)
{
	return (cpBBSegmentQuery(bb, a, b) != INFINITY);
}

/// Clamp a vector to a bounding box.
static inline cpVect
cpBBClampVect(const cpBB bb, const cpVect v)
{
	return cpv(cpfclamp(v.x, bb.l, bb.r), cpfclamp(v.y, bb.b, bb.t));
}

// TODO edge case issue
/// Wrap a vector to a bounding box.
cpVect cpBBWrapVect(const cpBB bb, const cpVect v); // wrap a vector to a bbox

///@}
