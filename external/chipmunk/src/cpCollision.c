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

#include <stdio.h>
#include <string.h>

#ifndef WIN32
#include <alloca.h>
#endif

#include "chipmunk_private.h"

#if DEBUG && 0
#include "ChipmunkDemo.h"
#define DRAW_ALL 0
#define DRAW_GJK (0 || DRAW_ALL)
#define DRAW_EPA (0 || DRAW_ALL)
#define DRAW_CLOSEST (0 || DRAW_ALL)
#define DRAW_CLIP (0 || DRAW_ALL)

#define PRINT_LOG 0
#endif

#define ENABLE_CACHING 1

#define MAX_GJK_ITERATIONS 30
#define MAX_EPA_ITERATIONS 30
#define WARN_GJK_ITERATIONS 20
#define WARN_EPA_ITERATIONS 20

// Add contact points for circle to circle collisions.
// Used by several collision tests.
// TODO should accept hash parameter
static int
CircleToCircleQuery(const cpVect p1, const cpVect p2, const cpFloat r1, const cpFloat r2, cpHashValue hash, cpContact *con)
{
	cpFloat mindist = r1 + r2;
	cpVect delta = cpvsub(p2, p1);
	cpFloat distsq = cpvlengthsq(delta);
	
	if(distsq < mindist*mindist){
		cpFloat dist = cpfsqrt(distsq);
		cpVect n = (dist ? cpvmult(delta, 1.0f/dist) : cpv(1.0f, 0.0f));
		cpContactInit(con, cpvlerp(p1, p2, r1/(r1 + r2)), n, dist - mindist, hash);
		
		return 1;
	} else {
		return 0;
	}
}

//MARK: Support Points and Edges:

static inline int
PolySupportPointIndex(const int count, const cpVect *verts, const cpVect n)
{
	cpFloat max = -INFINITY;
	int index = 0;
	
	for(int i=0; i<count; i++){
		cpVect v = verts[i];
		cpFloat d = cpvdot(v, n);
		if(d > max){
			max = d;
			index = i;
		}
	}
	
	return index;
}

struct SupportPoint {
	cpVect p;
	cpCollisionID id;
};

static inline struct SupportPoint
SupportPointNew(cpVect p, cpCollisionID id)
{
	struct SupportPoint point = {p, id};
	return point;
}

typedef struct SupportPoint (*SupportPointFunc)(const cpShape *shape, const cpVect n);

static inline struct SupportPoint
CircleSupportPoint(const cpCircleShape *circle, const cpVect n)
{
	return SupportPointNew(circle->tc, 0);
}

static inline struct SupportPoint
SegmentSupportPoint(const cpSegmentShape *seg, const cpVect n)
{
	if(cpvdot(seg->ta, n) > cpvdot(seg->tb, n)){
		return SupportPointNew(seg->ta, 0);
	} else {
		return SupportPointNew(seg->tb, 1);
	}
}

static inline struct SupportPoint
PolySupportPoint(const cpPolyShape *poly, const cpVect n)
{
	const cpVect *verts = poly->tVerts;
	int i = PolySupportPointIndex(poly->numVerts, verts, n);
	return SupportPointNew(verts[i], i);
}

struct MinkowskiPoint {
	cpVect a, b;
	cpVect ab;
	cpCollisionID id;
};

static inline struct MinkowskiPoint
MinkowskiPointNew(const struct SupportPoint a, const struct SupportPoint b)
{
	struct MinkowskiPoint point = {a.p, b.p, cpvsub(b.p, a.p), (a.id & 0xFF)<<8 | (b.id & 0xFF)};
	return point;
}

struct SupportContext {
	const cpShape *shape1, *shape2;
	SupportPointFunc func1, func2;
};

static inline struct MinkowskiPoint
Support(const struct SupportContext *ctx, const cpVect n)
{
	struct SupportPoint a = ctx->func1(ctx->shape1, cpvneg(n));
	struct SupportPoint b = ctx->func2(ctx->shape2, n);
	return MinkowskiPointNew(a, b);
}

struct EdgePoint {
	cpVect p;
	cpHashValue hash;
};

struct Edge {
	struct EdgePoint a, b;
	cpFloat r;
	cpVect n;
};

static inline struct Edge
EdgeNew(cpVect va, cpVect vb, cpHashValue ha, cpHashValue hb, cpFloat r)
{
	struct Edge edge = {{va, ha}, {vb, hb}, r, cpvnormalize(cpvperp(cpvsub(vb, va)))};
	return edge;
}

static struct Edge
SupportEdgeForPoly(const cpPolyShape *poly, const cpVect n)
{
	int numVerts = poly->numVerts;
	int i1 = PolySupportPointIndex(poly->numVerts, poly->tVerts, n);
	
	// TODO get rid of mod eventually, very expensive on ARM
	int i0 = (i1 - 1 + numVerts)%numVerts;
	int i2 = (i1 + 1)%numVerts;
	
	cpVect *verts = poly->tVerts;
	if(cpvdot(n, poly->tPlanes[i1].n) > cpvdot(n, poly->tPlanes[i2].n)){
		struct Edge edge = {{verts[i0], CP_HASH_PAIR(poly, i0)}, {verts[i1], CP_HASH_PAIR(poly, i1)}, poly->r, poly->tPlanes[i1].n};
		return edge;
	} else {
		struct Edge edge = {{verts[i1], CP_HASH_PAIR(poly, i1)}, {verts[i2], CP_HASH_PAIR(poly, i2)}, poly->r, poly->tPlanes[i2].n};
		return edge;
	}
}

static struct Edge
SupportEdgeForSegment(const cpSegmentShape *seg, const cpVect n)
{
	if(cpvdot(seg->tn, n) > 0.0){
		struct Edge edge = {{seg->ta, CP_HASH_PAIR(seg, 0)}, {seg->tb, CP_HASH_PAIR(seg, 1)}, seg->r, seg->tn};
		return edge;
	} else {
		struct Edge edge = {{seg->tb, CP_HASH_PAIR(seg, 1)}, {seg->ta, CP_HASH_PAIR(seg, 0)}, seg->r, cpvneg(seg->tn)};
		return edge;
	}
}

static inline cpFloat
ClosestT(const cpVect a, const cpVect b)
{
	cpVect delta = cpvsub(b, a);
	return -cpfclamp(cpvdot(delta, cpvadd(a, b))/cpvlengthsq(delta), -1.0f, 1.0f);
}

static inline cpVect
LerpT(const cpVect a, const cpVect b, const cpFloat t)
{
	cpFloat ht = 0.5f*t;
	return cpvadd(cpvmult(a, 0.5f - ht), cpvmult(b, 0.5f + ht));
}

struct ClosestPoints {
	cpVect a, b;
	cpVect n;
	cpFloat d;
	cpCollisionID id;
};

static inline struct ClosestPoints
ClosestPointsNew(const struct MinkowskiPoint v0, const struct MinkowskiPoint v1)
{
	cpFloat t = ClosestT(v0.ab, v1.ab);
	cpVect p = LerpT(v0.ab, v1.ab, t);
	
	cpVect pa = LerpT(v0.a, v1.a, t);
	cpVect pb = LerpT(v0.b, v1.b, t);
	cpCollisionID id = (v0.id & 0xFFFF)<<16 | (v1.id & 0xFFFF);
	
	cpVect delta = cpvsub(v1.ab, v0.ab);
	cpVect n = cpvnormalize(cpvperp(delta));
	cpFloat d = -cpvdot(n, p);
	
	if(d <= 0.0f || (0.0f < t && t < 1.0f)){
		struct ClosestPoints points = {pa, pb, cpvneg(n), d, id};
		return points;
	} else {
		cpFloat d2 = cpvlength(p);
		cpVect n2 = cpvmult(p, 1.0f/(d2 + CPFLOAT_MIN));
		
		struct ClosestPoints points = {pa, pb, n2, d2, id};
		return points;
	}
}

//MARK: EPA Functions

static inline cpFloat
ClosestDist(const cpVect v0,const cpVect v1)
{
	return cpvlengthsq(LerpT(v0, v1, ClosestT(v0, v1)));
}

static struct ClosestPoints
EPARecurse(const struct SupportContext *ctx, const int count, const struct MinkowskiPoint *hull, const int iteration)
{
	int mini = 0;
	cpFloat minDist = INFINITY;
	
	// TODO: precalculate this when building the hull and save a step.
	for(int j=0, i=count-1; j<count; i=j, j++){
		cpFloat d = ClosestDist(hull[i].ab, hull[j].ab);
		if(d < minDist){
			minDist = d;
			mini = i;
		}
	}
	
	struct MinkowskiPoint v0 = hull[mini];
	struct MinkowskiPoint v1 = hull[(mini + 1)%count];
	cpAssertSoft(!cpveql(v0.ab, v1.ab), "Internal Error: EPA vertexes are the same (%d and %d)", mini, (mini + 1)%count);
	
	struct MinkowskiPoint p = Support(ctx, cpvperp(cpvsub(v1.ab, v0.ab)));
	
#if DRAW_EPA
	cpVect verts[count];
	for(int i=0; i<count; i++) verts[i] = hull[i].ab;
	
	ChipmunkDebugDrawPolygon(count, verts, RGBAColor(1, 1, 0, 1), RGBAColor(1, 1, 0, 0.25));
	ChipmunkDebugDrawSegment(v0.ab, v1.ab, RGBAColor(1, 0, 0, 1));
	
	ChipmunkDebugDrawPoints(5, 1, (cpVect[]){p.ab}, RGBAColor(1, 1, 1, 1));
#endif
	
	cpFloat area2x = cpvcross(cpvsub(v1.ab, v0.ab), cpvadd(cpvsub(p.ab, v0.ab), cpvsub(p.ab, v1.ab)));
	if(area2x > 0.0f && iteration < MAX_EPA_ITERATIONS){
		int count2 = 1;
		struct MinkowskiPoint *hull2 = (struct MinkowskiPoint *)alloca((count + 1)*sizeof(struct MinkowskiPoint));
		hull2[0] = p;
		
		for(int i=0; i<count; i++){
			int index = (mini + 1 + i)%count;
			
			cpVect h0 = hull2[count2 - 1].ab;
			cpVect h1 = hull[index].ab;
			cpVect h2 = (i + 1 < count ? hull[(index + 1)%count] : p).ab;
			
			// TODO: Should this be changed to an area2x check?
			if(cpvcross(cpvsub(h2, h0), cpvsub(h1, h0)) > 0.0f){
				hull2[count2] = hull[index];
				count2++;
			}
		}
		
		return EPARecurse(ctx, count2, hull2, iteration + 1);
	} else {
		cpAssertWarn(iteration < WARN_EPA_ITERATIONS, "High EPA iterations: %d", iteration);
		return ClosestPointsNew(v0, v1);
	}
}

static struct ClosestPoints
EPA(const struct SupportContext *ctx, const struct MinkowskiPoint v0, const struct MinkowskiPoint v1, const struct MinkowskiPoint v2)
{
	// TODO: allocate a NxM array here and do an in place convex hull reduction in EPARecurse
	struct MinkowskiPoint hull[3] = {v0, v1, v2};
	return EPARecurse(ctx, 3, hull, 1);
}

//MARK: GJK Functions.

static inline struct ClosestPoints
GJKRecurse(const struct SupportContext *ctx, const struct MinkowskiPoint v0, const struct MinkowskiPoint v1, const int iteration)
{
	if(iteration > MAX_GJK_ITERATIONS){
		cpAssertWarn(iteration < WARN_GJK_ITERATIONS, "High GJK iterations: %d", iteration);
		return ClosestPointsNew(v0, v1);
	}
	
	cpVect delta = cpvsub(v1.ab, v0.ab);
	if(cpvcross(delta, cpvadd(v0.ab, v1.ab)) > 0.0f){
		// Origin is behind axis. Flip and try again.
		return GJKRecurse(ctx, v1, v0, iteration + 1);
	} else {
		cpFloat t = ClosestT(v0.ab, v1.ab);
		cpVect n = (-1.0f < t && t < 1.0f ? cpvperp(delta) : cpvneg(LerpT(v0.ab, v1.ab, t)));
		struct MinkowskiPoint p = Support(ctx, n);
		
#if DRAW_GJK
		ChipmunkDebugDrawSegment(v0.ab, v1.ab, RGBAColor(1, 1, 1, 1));
		cpVect c = cpvlerp(v0.ab, v1.ab, 0.5);
		ChipmunkDebugDrawSegment(c, cpvadd(c, cpvmult(cpvnormalize(n), 5.0)), RGBAColor(1, 0, 0, 1));
		
		ChipmunkDebugDrawPoints(5.0, 1, &p.ab, RGBAColor(1, 1, 1, 1));
#endif
		
		if(
			cpvcross(cpvsub(v1.ab, p.ab), cpvadd(v1.ab, p.ab)) > 0.0f &&
			cpvcross(cpvsub(v0.ab, p.ab), cpvadd(v0.ab, p.ab)) < 0.0f
		){
			cpAssertWarn(iteration < WARN_GJK_ITERATIONS, "High GJK->EPA iterations: %d", iteration);
			// The triangle v0, p, v1 contains the origin. Use EPA to find the MSA.
			return EPA(ctx, v0, p, v1);
		} else {
			// The new point must be farther along the normal than the existing points.
			if(cpvdot(p.ab, n) <= cpfmax(cpvdot(v0.ab, n), cpvdot(v1.ab, n))){
				cpAssertWarn(iteration < WARN_GJK_ITERATIONS, "High GJK iterations: %d", iteration);
				return ClosestPointsNew(v0, v1);
			} else {
				if(ClosestDist(v0.ab, p.ab) < ClosestDist(p.ab, v1.ab)){
					return GJKRecurse(ctx, v0, p, iteration + 1);
				} else {
					return GJKRecurse(ctx, p, v1, iteration + 1);
				}
			}
		}
	}
}

static struct SupportPoint
ShapePoint(const cpShape *shape, const int i)
{
	switch(shape->klass->type){
		case CP_CIRCLE_SHAPE: {
			return SupportPointNew(((cpCircleShape *)shape)->tc, 0);
		} case CP_SEGMENT_SHAPE: {
			cpSegmentShape *seg = (cpSegmentShape *)shape;
			return SupportPointNew(i == 0 ? seg->ta : seg->tb, i);
		} case CP_POLY_SHAPE: {
			cpPolyShape *poly = (cpPolyShape *)shape;
			// Poly shapes may change vertex count.
			int index = (i < poly->numVerts ? i : 0);
			return SupportPointNew(poly->tVerts[index], index);
		} default: {
			return SupportPointNew(cpvzero, 0);
		}
	}
}

static struct ClosestPoints
GJK(const struct SupportContext *ctx, cpCollisionID *id)
{
#if DRAW_GJK || DRAW_EPA
	// draw the minkowski difference origin
	cpVect origin = cpvzero;
	ChipmunkDebugDrawPoints(5.0, 1, &origin, RGBAColor(1,0,0,1));
	
	int mdiffCount = ctx->count1*ctx->count2;
	cpVect *mdiffVerts = alloca(mdiffCount*sizeof(cpVect));
	
	for(int i=0; i<ctx->count1; i++){
		for(int j=0; j<ctx->count2; j++){
			cpVect v1 = ShapePoint(ctx->count1, ctx->verts1, i).p;
			cpVect v2 = ShapePoint(ctx->count2, ctx->verts2, j).p;
			mdiffVerts[i*ctx->count2 + j] = cpvsub(v2, v1);
		}
	}
	 
	cpVect *hullVerts = alloca(mdiffCount*sizeof(cpVect));
	int hullCount = cpConvexHull(mdiffCount, mdiffVerts, hullVerts, NULL, 0.0);
	
	ChipmunkDebugDrawPolygon(hullCount, hullVerts, RGBAColor(1, 0, 0, 1), RGBAColor(1, 0, 0, 0.25));
	ChipmunkDebugDrawPoints(2.0, mdiffCount, mdiffVerts, RGBAColor(1, 0, 0, 1));
#endif
	
	struct MinkowskiPoint v0, v1;
	if(*id && ENABLE_CACHING){
		v0 = MinkowskiPointNew(ShapePoint(ctx->shape1, (*id>>24)&0xFF), ShapePoint(ctx->shape2, (*id>>16)&0xFF));
		v1 = MinkowskiPointNew(ShapePoint(ctx->shape1, (*id>> 8)&0xFF), ShapePoint(ctx->shape2, (*id    )&0xFF));
	} else {
		cpVect axis = cpvperp(cpvsub(cpBBCenter(ctx->shape1->bb), cpBBCenter(ctx->shape2->bb)));
		v0 = Support(ctx, axis);
		v1 = Support(ctx, cpvneg(axis));
	}
	
	struct ClosestPoints points = GJKRecurse(ctx, v0, v1, 1);
	*id = points.id;
	return points;
}

//MARK: Contact Clipping

static inline void
Contact1(cpFloat dist, cpVect a, cpVect b, cpFloat refr, cpFloat incr, cpVect n, cpHashValue hash, cpContact *arr)
{
	cpFloat rsum = refr + incr;
	cpFloat alpha = (rsum > 0.0f ? refr/rsum : 0.5f);
	cpVect point = cpvlerp(a, b, alpha);
	
	cpContactInit(arr, point, n, dist - rsum, hash);
}

static inline int
Contact2(cpVect refp, cpVect inca, cpVect incb, cpFloat refr, cpFloat incr, cpVect refn, cpVect n, cpHashValue hash, cpContact *arr)
{
	cpFloat cian = cpvcross(inca, refn);
	cpFloat cibn = cpvcross(incb, refn);
	cpFloat crpn = cpvcross(refp, refn);
	cpFloat t = 1.0f - cpfclamp01((cibn - crpn)/(cibn - cian));
	
	cpVect point = cpvlerp(inca, incb, t);
	cpFloat pd = cpvdot(cpvsub(point, refp), refn);
	
	if(t > 0.0f && pd <= 0.0f){
		cpFloat rsum = refr + incr;
		cpFloat alpha = (rsum > 0.0f ? incr*(1.0f - (rsum + pd)/rsum) : -0.5f*pd);
		
		cpContactInit(arr, cpvadd(point, cpvmult(refn, alpha)), n, pd, hash);
		return 1;
	} else {
		return 0;
	}
}

static inline int
ClipContacts(const struct Edge ref, const struct Edge inc, const struct ClosestPoints points, const cpFloat nflip, cpContact *arr)
{
	cpVect inc_offs = cpvmult(inc.n, inc.r);
	cpVect ref_offs = cpvmult(ref.n, ref.r);
	
	cpVect inca = cpvadd(inc.a.p, inc_offs);
	cpVect incb = cpvadd(inc.b.p, inc_offs);
	
	cpVect closest_inca = cpClosetPointOnSegment(inc.a.p, ref.a.p, ref.b.p);
	cpVect closest_incb = cpClosetPointOnSegment(inc.b.p, ref.a.p, ref.b.p);
	
	cpVect msa = cpvmult(points.n, nflip*points.d);
	cpFloat cost_a = cpvdistsq(cpvsub(inc.a.p, closest_inca), msa);
	cpFloat cost_b = cpvdistsq(cpvsub(inc.b.p, closest_incb), msa);
	
#if DRAW_CLIP
	ChipmunkDebugDrawSegment(ref.a.p, ref.b.p, RGBAColor(1, 0, 0, 1));
	ChipmunkDebugDrawSegment(inc.a.p, inc.b.p, RGBAColor(0, 1, 0, 1));
	ChipmunkDebugDrawSegment(inca, incb, RGBAColor(0, 1, 0, 1));
	
	cpVect cref = cpvlerp(ref.a.p, ref.b.p, 0.5);
	ChipmunkDebugDrawSegment(cref, cpvadd(cref, cpvmult(ref.n, 5.0)), RGBAColor(1, 0, 0, 1));
	
	cpVect cinc = cpvlerp(inc.a.p, inc.b.p, 0.5);
	ChipmunkDebugDrawSegment(cinc, cpvadd(cinc, cpvmult(inc.n, 5.0)), RGBAColor(1, 0, 0, 1));
	
	ChipmunkDebugDrawPoints(5.0, 2, (cpVect[]){ref.a.p, inc.a.p}, RGBAColor(1, 1, 0, 1));
	ChipmunkDebugDrawPoints(5.0, 2, (cpVect[]){ref.b.p, inc.b.p}, RGBAColor(0, 1, 1, 1));
	
	if(cost_a < cost_b){
		ChipmunkDebugDrawSegment(closest_inca, inc.a.p, RGBAColor(1, 0, 1, 1));
	} else {
		ChipmunkDebugDrawSegment(closest_incb, inc.b.p, RGBAColor(1, 0, 1, 1));
	}
#endif
	
	cpHashValue hash_iarb = CP_HASH_PAIR(inc.a.hash, ref.b.hash);
	cpHashValue hash_ibra = CP_HASH_PAIR(inc.b.hash, ref.a.hash);
	
	if(cost_a < cost_b){
		cpVect refp = cpvadd(ref.a.p, ref_offs);
		Contact1(points.d, closest_inca, inc.a.p, ref.r, inc.r, points.n, hash_iarb, arr);
		return Contact2(refp, inca, incb, ref.r, inc.r, ref.n, points.n, hash_ibra, arr + 1) + 1;
	} else {
		cpVect refp = cpvadd(ref.b.p, ref_offs);
		Contact1(points.d, closest_incb, inc.b.p, ref.r, inc.r, points.n, hash_ibra, arr);
		return Contact2(refp, incb, inca, ref.r, inc.r, ref.n, points.n, hash_iarb, arr + 1) + 1;
	}
}

static inline int
ContactPoints(const struct Edge e1, const struct Edge e2, const struct ClosestPoints points, cpContact *arr)
{
	cpFloat mindist = e1.r + e2.r;
	if(points.d <= mindist){
		cpFloat pick = cpvdot(e1.n, points.n) + cpvdot(e2.n, points.n);
		
		if(
			(pick != 0.0f && pick > 0.0f) ||
			// If the edges are both perfectly aligned weird things happen.
			// This is *very* common at the start of a simulation.
			// Pick the longest edge as the reference to break the tie.
			(pick == 0.0f && (cpvdistsq(e1.a.p, e1.b.p) > cpvdistsq(e2.a.p, e2.b.p)))
		){
			return ClipContacts(e1, e2, points,  1.0f, arr);
		} else {
			return ClipContacts(e2, e1, points, -1.0f, arr);
		}
	} else {
		return 0;
	}
}

//MARK: Collision Functions

typedef int (*CollisionFunc)(const cpShape *a, const cpShape *b, cpCollisionID *id, cpContact *arr);

// Collide circle shapes.
static int
CircleToCircle(const cpCircleShape *c1, const cpCircleShape *c2, cpCollisionID *id, cpContact *arr)
{
	return CircleToCircleQuery(c1->tc, c2->tc, c1->r, c2->r, 0, arr);
}

static int
CircleToSegment(const cpCircleShape *circleShape, const cpSegmentShape *segmentShape, cpCollisionID *id, cpContact *con)
{
	cpVect seg_a = segmentShape->ta;
	cpVect seg_b = segmentShape->tb;
	cpVect center = circleShape->tc;
	
	cpVect seg_delta = cpvsub(seg_b, seg_a);
	cpFloat closest_t = cpfclamp01(cpvdot(seg_delta, cpvsub(center, seg_a))/cpvlengthsq(seg_delta));
	cpVect closest = cpvadd(seg_a, cpvmult(seg_delta, closest_t));
	
	if(CircleToCircleQuery(center, closest, circleShape->r, segmentShape->r, 0, con)){
		cpVect n = con[0].n;
		
		// Reject endcap collisions if tangents are provided.
		if(
			(closest_t != 0.0f || cpvdot(n, cpvrotate(segmentShape->a_tangent, segmentShape->shape.body->rot)) >= 0.0) &&
			(closest_t != 1.0f || cpvdot(n, cpvrotate(segmentShape->b_tangent, segmentShape->shape.body->rot)) >= 0.0)
		){
			return 1;
		}
	}
	
	return 0;
}

static int
SegmentToSegment(const cpSegmentShape *seg1, const cpSegmentShape *seg2, cpCollisionID *id, cpContact *arr)
{
	struct SupportContext context = {(cpShape *)seg1, (cpShape *)seg2, (SupportPointFunc)SegmentSupportPoint, (SupportPointFunc)SegmentSupportPoint};
	struct ClosestPoints points = GJK(&context, id);
	
#if DRAW_CLOSEST
#if PRINT_LOG
//	ChipmunkDemoPrintString("Distance: %.2f\n", points.d);
#endif
	
	ChipmunkDebugDrawDot(6.0, points.a, RGBAColor(1, 1, 1, 1));
	ChipmunkDebugDrawDot(6.0, points.b, RGBAColor(1, 1, 1, 1));
	ChipmunkDebugDrawSegment(points.a, points.b, RGBAColor(1, 1, 1, 1));
	ChipmunkDebugDrawSegment(points.a, cpvadd(points.a, cpvmult(points.n, 10.0)), RGBAColor(1, 0, 0, 1));
#endif
	
	cpVect n = points.n;
	cpVect rot1 = seg1->shape.body->rot;
	cpVect rot2 = seg2->shape.body->rot;
	if(
		points.d <= (seg1->r + seg2->r) &&
		(
			(!cpveql(points.a, seg1->ta) || cpvdot(n, cpvrotate(seg1->a_tangent, rot1)) <= 0.0) &&
			(!cpveql(points.a, seg1->tb) || cpvdot(n, cpvrotate(seg1->b_tangent, rot1)) <= 0.0) &&
			(!cpveql(points.b, seg2->ta) || cpvdot(n, cpvrotate(seg2->a_tangent, rot2)) >= 0.0) &&
			(!cpveql(points.b, seg2->tb) || cpvdot(n, cpvrotate(seg2->b_tangent, rot2)) >= 0.0)
		)
	){
		return ContactPoints(SupportEdgeForSegment(seg1, n), SupportEdgeForSegment(seg2, cpvneg(n)), points, arr);
	} else {
		return 0;
	}
}

static int
PolyToPoly(const cpPolyShape *poly1, const cpPolyShape *poly2, cpCollisionID *id, cpContact *arr)
{
	struct SupportContext context = {(cpShape *)poly1, (cpShape *)poly2, (SupportPointFunc)PolySupportPoint, (SupportPointFunc)PolySupportPoint};
	struct ClosestPoints points = GJK(&context, id);
	
#if DRAW_CLOSEST
#if PRINT_LOG
//	ChipmunkDemoPrintString("Distance: %.2f\n", points.d);
#endif
	
	ChipmunkDebugDrawDot(3.0, points.a, RGBAColor(1, 1, 1, 1));
	ChipmunkDebugDrawDot(3.0, points.b, RGBAColor(1, 1, 1, 1));
	ChipmunkDebugDrawSegment(points.a, points.b, RGBAColor(1, 1, 1, 1));
	ChipmunkDebugDrawSegment(points.a, cpvadd(points.a, cpvmult(points.n, 10.0)), RGBAColor(1, 0, 0, 1));
#endif
	
	if(points.d - poly1->r - poly2->r <= 0.0){
		return ContactPoints(SupportEdgeForPoly(poly1, points.n), SupportEdgeForPoly(poly2, cpvneg(points.n)), points, arr);
	} else {
		return 0;
	}
}

static int
SegmentToPoly(const cpSegmentShape *seg, const cpPolyShape *poly, cpCollisionID *id, cpContact *arr)
{
	struct SupportContext context = {(cpShape *)seg, (cpShape *)poly, (SupportPointFunc)SegmentSupportPoint, (SupportPointFunc)PolySupportPoint};
	struct ClosestPoints points = GJK(&context, id);
	
#if DRAW_CLOSEST
#if PRINT_LOG
//	ChipmunkDemoPrintString("Distance: %.2f\n", points.d);
#endif
	
	ChipmunkDebugDrawDot(3.0, points.a, RGBAColor(1, 1, 1, 1));
	ChipmunkDebugDrawDot(3.0, points.b, RGBAColor(1, 1, 1, 1));
	ChipmunkDebugDrawSegment(points.a, points.b, RGBAColor(1, 1, 1, 1));
	ChipmunkDebugDrawSegment(points.a, cpvadd(points.a, cpvmult(points.n, 10.0)), RGBAColor(1, 0, 0, 1));
#endif
	
	// Reject endcap collisions if tangents are provided.
	cpVect n = points.n;
	cpVect rot = seg->shape.body->rot;
	if(
		points.d - seg->r - poly->r <= 0.0 &&
		(
			(!cpveql(points.a, seg->ta) || cpvdot(n, cpvrotate(seg->a_tangent, rot)) <= 0.0) &&
			(!cpveql(points.a, seg->tb) || cpvdot(n, cpvrotate(seg->b_tangent, rot)) <= 0.0)
		)
	){
		return ContactPoints(SupportEdgeForSegment(seg, n), SupportEdgeForPoly(poly, cpvneg(n)), points, arr);
	} else {
		return 0;
	}
}

// This one is less gross, but still gross.
// TODO: Comment me!
static int
CircleToPoly(const cpCircleShape *circle, const cpPolyShape *poly, cpCollisionID *id, cpContact *con)
{
	struct SupportContext context = {(cpShape *)circle, (cpShape *)poly, (SupportPointFunc)CircleSupportPoint, (SupportPointFunc)PolySupportPoint};
	struct ClosestPoints points = GJK(&context, id);
	
#if DRAW_CLOSEST
	ChipmunkDebugDrawDot(3.0, points.a, RGBAColor(1, 1, 1, 1));
	ChipmunkDebugDrawDot(3.0, points.b, RGBAColor(1, 1, 1, 1));
	ChipmunkDebugDrawSegment(points.a, points.b, RGBAColor(1, 1, 1, 1));
	ChipmunkDebugDrawSegment(points.a, cpvadd(points.a, cpvmult(points.n, 10.0)), RGBAColor(1, 0, 0, 1));
#endif
	
	cpFloat mindist = circle->r + poly->r;
	if(points.d - mindist <= 0.0){
		cpVect p = cpvlerp(points.a, points.b, circle->r/(mindist));
		cpContactInit(con, p, points.n, points.d - mindist, 0);
		return 1;
	} else {
		return 0;
	}
}

static const CollisionFunc builtinCollisionFuncs[9] = {
	(CollisionFunc)CircleToCircle,
	NULL,
	NULL,
	(CollisionFunc)CircleToSegment,
	NULL,
	NULL,
	(CollisionFunc)CircleToPoly,
	(CollisionFunc)SegmentToPoly,
	(CollisionFunc)PolyToPoly,
};
static const CollisionFunc *colfuncs = builtinCollisionFuncs;

static const CollisionFunc segmentCollisions[9] = {
	(CollisionFunc)CircleToCircle,
	NULL,
	NULL,
	(CollisionFunc)CircleToSegment,
	(CollisionFunc)SegmentToSegment,
	NULL,
	(CollisionFunc)CircleToPoly,
	(CollisionFunc)SegmentToPoly,
	(CollisionFunc)PolyToPoly,
};

void
cpEnableSegmentToSegmentCollisions(void)
{
	colfuncs = segmentCollisions;
}

int
cpCollideShapes(const cpShape *a, const cpShape *b, cpCollisionID *id, cpContact *arr)
{
	// Their shape types must be in order.
	cpAssertSoft(a->klass->type <= b->klass->type, "Internal Error: Collision shapes passed to cpCollideShapes() are not sorted.");
	
	CollisionFunc cfunc = colfuncs[a->klass->type + b->klass->type*CP_NUM_SHAPES];
	
	int numContacts = (cfunc? cfunc(a, b, id, arr) : 0);
	cpAssertSoft(numContacts <= CP_MAX_CONTACTS_PER_ARBITER, "Internal error: Too many contact points returned.");
	
	return numContacts;
}
