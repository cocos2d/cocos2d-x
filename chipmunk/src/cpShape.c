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
 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "chipmunk_private.h"
#include "chipmunk_unsafe.h"

#define CP_DefineShapeGetter(struct, type, member, name) \
CP_DeclareShapeGetter(struct, type, name){ \
	cpAssert(shape->klass == &struct##Class, "shape is not a "#struct); \
	return ((struct *)shape)->member; \
}
cpHashValue SHAPE_ID_COUNTER = 0;

void
cpResetShapeIdCounter(void)
{
	SHAPE_ID_COUNTER = 0;
}


cpShape*
cpShapeInit(cpShape *shape, const cpShapeClass *klass, cpBody *body)
{
	shape->klass = klass;
	
	shape->hashid = SHAPE_ID_COUNTER;
	SHAPE_ID_COUNTER++;
	
	shape->body = body;
	shape->sensor = 0;
	
	shape->e = 0.0f;
	shape->u = 0.0f;
	shape->surface_v = cpvzero;
	
	shape->collision_type = 0;
	shape->group = CP_NO_GROUP;
	shape->layers = CP_ALL_LAYERS;
	
	shape->data = NULL;
	shape->next = NULL;
	
//	cpShapeCacheBB(shape);
	
	return shape;
}

void
cpShapeDestroy(cpShape *shape)
{
	if(shape->klass && shape->klass->destroy) shape->klass->destroy(shape);
}

void
cpShapeFree(cpShape *shape)
{
	if(shape){
		cpShapeDestroy(shape);
		cpfree(shape);
	}
}

// TODO this function should really take a position and rotation explicitly and be renamed
cpBB
cpShapeCacheBB(cpShape *shape)
{
	cpBody *body = shape->body;
	
	shape->bb = shape->klass->cacheData(shape, body->p, body->rot);
	return shape->bb;
}

cpBool
cpShapePointQuery(cpShape *shape, cpVect p){
	return shape->klass->pointQuery(shape, p);
}

cpBool
cpShapeSegmentQuery(cpShape *shape, cpVect a, cpVect b, cpSegmentQueryInfo *info){
	cpSegmentQueryInfo blank = {NULL, 0.0f, cpvzero};
	(*info) = blank;
	
	shape->klass->segmentQuery(shape, a, b, info);
	return (info->shape != NULL);
}

void
cpSegmentQueryInfoPrint(cpSegmentQueryInfo *info)
{
	printf("Segment Query:\n");
	printf("\tt: %f\n", info->t);
//	printf("\tdist: %f\n", info->dist);
//	printf("\tpoint: %s\n", cpvstr(info->point));
	printf("\tn: %s\n", cpvstr(info->n));
}




cpCircleShape *
cpCircleShapeAlloc(void)
{
	return (cpCircleShape *)cpcalloc(1, sizeof(cpCircleShape));
}

static inline cpBB
bbFromCircle(const cpVect c, const cpFloat r)
{
	return cpBBNew(c.x-r, c.y-r, c.x+r, c.y+r);
}

static cpBB
cpCircleShapeCacheData(cpShape *shape, cpVect p, cpVect rot)
{
	cpCircleShape *circle = (cpCircleShape *)shape;
	
	circle->tc = cpvadd(p, cpvrotate(circle->c, rot));
	return bbFromCircle(circle->tc, circle->r);
}

static cpBool
cpCircleShapePointQuery(cpShape *shape, cpVect p){
	cpCircleShape *circle = (cpCircleShape *)shape;
	return cpvnear(circle->tc, p, circle->r);
}

static void
circleSegmentQuery(cpShape *shape, cpVect center, cpFloat r, cpVect a, cpVect b, cpSegmentQueryInfo *info)
{
	// offset the line to be relative to the circle
	a = cpvsub(a, center);
	b = cpvsub(b, center);
	
	cpFloat qa = cpvdot(a, a) - 2.0f*cpvdot(a, b) + cpvdot(b, b);
	cpFloat qb = -2.0f*cpvdot(a, a) + 2.0f*cpvdot(a, b);
	cpFloat qc = cpvdot(a, a) - r*r;
	
	cpFloat det = qb*qb - 4.0f*qa*qc;
	
	if(det >= 0.0f){
		cpFloat t = (-qb - cpfsqrt(det))/(2.0f*qa);
		if(0.0f<= t && t <= 1.0f){
			info->shape = shape;
			info->t = t;
			info->n = cpvnormalize(cpvlerp(a, b, t));
		}
	}
}

static void
cpCircleShapeSegmentQuery(cpShape *shape, cpVect a, cpVect b, cpSegmentQueryInfo *info)
{
	cpCircleShape *circle = (cpCircleShape *)shape;
	circleSegmentQuery(shape, circle->tc, circle->r, a, b, info);
}

static const cpShapeClass cpCircleShapeClass = {
	CP_CIRCLE_SHAPE,
	cpCircleShapeCacheData,
	NULL,
	cpCircleShapePointQuery,
	cpCircleShapeSegmentQuery,
};

cpCircleShape *
cpCircleShapeInit(cpCircleShape *circle, cpBody *body, cpFloat radius, cpVect offset)
{
	circle->c = offset;
	circle->r = radius;
	
	cpShapeInit((cpShape *)circle, &cpCircleShapeClass, body);
	
	return circle;
}

cpShape *
cpCircleShapeNew(cpBody *body, cpFloat radius, cpVect offset)
{
	return (cpShape *)cpCircleShapeInit(cpCircleShapeAlloc(), body, radius, offset);
}

CP_DefineShapeGetter(cpCircleShape, cpVect, c, Offset)
CP_DefineShapeGetter(cpCircleShape, cpFloat, r, Radius)

cpSegmentShape *
cpSegmentShapeAlloc(void)
{
	return (cpSegmentShape *)cpcalloc(1, sizeof(cpSegmentShape));
}

static cpBB
cpSegmentShapeCacheData(cpShape *shape, cpVect p, cpVect rot)
{
	cpSegmentShape *seg = (cpSegmentShape *)shape;
	
	seg->ta = cpvadd(p, cpvrotate(seg->a, rot));
	seg->tb = cpvadd(p, cpvrotate(seg->b, rot));
	seg->tn = cpvrotate(seg->n, rot);
	
	cpFloat l,r,s,t;
	
	if(seg->ta.x < seg->tb.x){
		l = seg->ta.x;
		r = seg->tb.x;
	} else {
		l = seg->tb.x;
		r = seg->ta.x;
	}
	
	if(seg->ta.y < seg->tb.y){
		s = seg->ta.y;
		t = seg->tb.y;
	} else {
		s = seg->tb.y;
		t = seg->ta.y;
	}
	
	cpFloat rad = seg->r;
	return cpBBNew(l - rad, s - rad, r + rad, t + rad);
}

static cpBool
cpSegmentShapePointQuery(cpShape *shape, cpVect p){
	if(!cpBBcontainsVect(shape->bb, p)) return cpFalse;
	
	cpSegmentShape *seg = (cpSegmentShape *)shape;
	
	// Calculate normal distance from segment.
	cpFloat dn = cpvdot(seg->tn, p) - cpvdot(seg->ta, seg->tn);
	cpFloat dist = cpfabs(dn) - seg->r;
	if(dist > 0.0f) return cpFalse;
	
	// Calculate tangential distance along segment.
	cpFloat dt = -cpvcross(seg->tn, p);
	cpFloat dtMin = -cpvcross(seg->tn, seg->ta);
	cpFloat dtMax = -cpvcross(seg->tn, seg->tb);
	
	// Decision tree to decide which feature of the segment to collide with.
	if(dt <= dtMin){
		if(dt < (dtMin - seg->r)){
			return cpFalse;
		} else {
			return cpvlengthsq(cpvsub(seg->ta, p)) < (seg->r*seg->r);
		}
	} else {
		if(dt < dtMax){
			return cpTrue;
		} else {
			if(dt < (dtMax + seg->r)) {
				return cpvlengthsq(cpvsub(seg->tb, p)) < (seg->r*seg->r);
			} else {
				return cpFalse;
			}
		}
	}
	
	return cpTrue;	
}

static inline cpBool inUnitRange(cpFloat t){return (0.0f < t && t < 1.0f);}

static void
cpSegmentShapeSegmentQuery(cpShape *shape, cpVect a, cpVect b, cpSegmentQueryInfo *info)
{
	// TODO this function could be optimized better.
	
	cpSegmentShape *seg = (cpSegmentShape *)shape;
	cpVect n = seg->tn;
	// flip n if a is behind the axis
	if(cpvdot(a, n) < cpvdot(seg->ta, n))
		n = cpvneg(n);
	
	cpFloat an = cpvdot(a, n);
	cpFloat bn = cpvdot(b, n);
	
	if(an != bn){
		cpFloat d = cpvdot(seg->ta, n) + seg->r;
		cpFloat t = (d - an)/(bn - an);
		
		if(0.0f < t && t < 1.0f){
			cpVect point = cpvlerp(a, b, t);
			cpFloat dt = -cpvcross(seg->tn, point);
			cpFloat dtMin = -cpvcross(seg->tn, seg->ta);
			cpFloat dtMax = -cpvcross(seg->tn, seg->tb);
			
			if(dtMin < dt && dt < dtMax){
				info->shape = shape;
				info->t = t;
				info->n = n;
				
				return; // don't continue on and check endcaps
			}
		}
	}
	
	if(seg->r) {
		cpSegmentQueryInfo info1 = {NULL, 1.0f, cpvzero};
		cpSegmentQueryInfo info2 = {NULL, 1.0f, cpvzero};
		circleSegmentQuery(shape, seg->ta, seg->r, a, b, &info1);
		circleSegmentQuery(shape, seg->tb, seg->r, a, b, &info2);
		
		if(info1.t < info2.t){
			(*info) = info1;
		} else {
			(*info) = info2;
		}
	}
}

static const cpShapeClass cpSegmentShapeClass = {
	CP_SEGMENT_SHAPE,
	cpSegmentShapeCacheData,
	NULL,
	cpSegmentShapePointQuery,
	cpSegmentShapeSegmentQuery,
};

cpSegmentShape *
cpSegmentShapeInit(cpSegmentShape *seg, cpBody *body, cpVect a, cpVect b, cpFloat r)
{
	seg->a = a;
	seg->b = b;
	seg->n = cpvperp(cpvnormalize(cpvsub(b, a)));
	
	seg->r = r;
	
	cpShapeInit((cpShape *)seg, &cpSegmentShapeClass, body);
	
	return seg;
}

cpShape*
cpSegmentShapeNew(cpBody *body, cpVect a, cpVect b, cpFloat r)
{
	return (cpShape *)cpSegmentShapeInit(cpSegmentShapeAlloc(), body, a, b, r);
}

CP_DefineShapeGetter(cpSegmentShape, cpVect, a, A)
CP_DefineShapeGetter(cpSegmentShape, cpVect, b, B)
CP_DefineShapeGetter(cpSegmentShape, cpVect, n, Normal)
CP_DefineShapeGetter(cpSegmentShape, cpFloat, r, Radius)

// Unsafe API (chipmunk_unsafe.h)

void
cpCircleShapeSetRadius(cpShape *shape, cpFloat radius)
{
	cpAssert(shape->klass == &cpCircleShapeClass, "Shape is not a circle shape.");
	cpCircleShape *circle = (cpCircleShape *)shape;
	
	circle->r = radius;
}

void
cpCircleShapeSetOffset(cpShape *shape, cpVect offset)
{
	cpAssert(shape->klass == &cpCircleShapeClass, "Shape is not a circle shape.");
	cpCircleShape *circle = (cpCircleShape *)shape;
	
	circle->c = offset;
}

void
cpSegmentShapeSetEndpoints(cpShape *shape, cpVect a, cpVect b)
{
	cpAssert(shape->klass == &cpSegmentShapeClass, "Shape is not a segment shape.");
	cpSegmentShape *seg = (cpSegmentShape *)shape;
	
	seg->a = a;
	seg->b = b;
	seg->n = cpvperp(cpvnormalize(cpvsub(b, a)));
}

void
cpSegmentShapeSetRadius(cpShape *shape, cpFloat radius)
{
	cpAssert(shape->klass == &cpSegmentShapeClass, "Shape is not a segment shape.");
	cpSegmentShape *seg = (cpSegmentShape *)shape;
	
	seg->r = radius;
}
