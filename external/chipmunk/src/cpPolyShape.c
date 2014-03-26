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
 
#include "chipmunk_private.h"
#include "chipmunk_unsafe.h"

cpPolyShape *
cpPolyShapeAlloc(void)
{
	return (cpPolyShape *)cpcalloc(1, sizeof(cpPolyShape));
}

static cpBB
cpPolyShapeTransformVerts(cpPolyShape *poly, cpVect p, cpVect rot)
{
	cpVect *src = poly->verts;
	cpVect *dst = poly->tVerts;
	
	cpFloat l = (cpFloat)INFINITY, r = -(cpFloat)INFINITY;
	cpFloat b = (cpFloat)INFINITY, t = -(cpFloat)INFINITY;
	
	for(int i=0; i<poly->numVerts; i++){
		cpVect v = cpvadd(p, cpvrotate(src[i], rot));
		
		dst[i] = v;
		l = cpfmin(l, v.x);
		r = cpfmax(r, v.x);
		b = cpfmin(b, v.y);
		t = cpfmax(t, v.y);
	}
	
	cpFloat radius = poly->r;
	return cpBBNew(l - radius, b - radius, r + radius, t + radius);
}

static void
cpPolyShapeTransformAxes(cpPolyShape *poly, cpVect p, cpVect rot)
{
	cpSplittingPlane *src = poly->planes;
	cpSplittingPlane *dst = poly->tPlanes;
	
	for(int i=0; i<poly->numVerts; i++){
		cpVect n = cpvrotate(src[i].n, rot);
		dst[i].n = n;
		dst[i].d = cpvdot(p, n) + src[i].d;
	}
}

static cpBB
cpPolyShapeCacheData(cpPolyShape *poly, cpVect p, cpVect rot)
{
	cpPolyShapeTransformAxes(poly, p, rot);
	cpBB bb = poly->shape.bb = cpPolyShapeTransformVerts(poly, p, rot);
	
	return bb;
}

static void
cpPolyShapeDestroy(cpPolyShape *poly)
{
	cpfree(poly->verts);
	cpfree(poly->planes);
}

static void
cpPolyShapeNearestPointQuery(cpPolyShape *poly, cpVect p, cpNearestPointQueryInfo *info){
	int count = poly->numVerts;
	cpSplittingPlane *planes = poly->tPlanes;
	cpVect *verts = poly->tVerts;
	cpFloat r = poly->r;
	
	cpVect v0 = verts[count - 1];
	cpFloat minDist = INFINITY;
	cpVect closestPoint = cpvzero;
	cpVect closestNormal = cpvzero;
	cpBool outside = cpFalse;
	
	for(int i=0; i<count; i++){
		if(cpSplittingPlaneCompare(planes[i], p) > 0.0f) outside = cpTrue;
		
		cpVect v1 = verts[i];
		cpVect closest = cpClosetPointOnSegment(p, v0, v1);
		
		cpFloat dist = cpvdist(p, closest);
		if(dist < minDist){
			minDist = dist;
			closestPoint = closest;
			closestNormal = planes[i].n;
		}
		
		v0 = v1;
	}
	
	cpFloat dist = (outside ? minDist : -minDist);
	cpVect g = cpvmult(cpvsub(p, closestPoint), 1.0f/dist);
	
	info->shape = (cpShape *)poly;
	info->p = cpvadd(closestPoint, cpvmult(g, r));
	info->d = dist - r;
	
	// Use the normal of the closest segment if the distance is small.
	info->g = (minDist > MAGIC_EPSILON ? g : closestNormal);
}

static void
cpPolyShapeSegmentQuery(cpPolyShape *poly, cpVect a, cpVect b, cpSegmentQueryInfo *info)
{
	cpSplittingPlane *axes = poly->tPlanes;
	cpVect *verts = poly->tVerts;
	int numVerts = poly->numVerts;
	cpFloat r = poly->r;
	
	for(int i=0; i<numVerts; i++){
		cpVect n = axes[i].n;
		cpFloat an = cpvdot(a, n);
		cpFloat d = axes[i].d + r - an;
		if(d > 0.0f) continue;
		
		cpFloat bn = cpvdot(b, n);
		cpFloat t = d/(bn - an);
		if(t < 0.0f || 1.0f < t) continue;
		
		cpVect point = cpvlerp(a, b, t);
		cpFloat dt = -cpvcross(n, point);
		cpFloat dtMin = -cpvcross(n, verts[(i - 1 + numVerts)%numVerts]);
		cpFloat dtMax = -cpvcross(n, verts[i]);
		
		if(dtMin <= dt && dt <= dtMax){
			info->shape = (cpShape *)poly;
			info->t = t;
			info->n = n;
		}
	}
	
	// Also check against the beveled vertexes.
	if(r > 0.0f){
		for(int i=0; i<numVerts; i++){
			cpSegmentQueryInfo circle_info = {NULL, 1.0f, cpvzero};
			CircleSegmentQuery(&poly->shape, verts[i], r, a, b, &circle_info);
			if(circle_info.t < info->t) (*info) = circle_info;
		}
	}
}

static const cpShapeClass polyClass = {
	CP_POLY_SHAPE,
	(cpShapeCacheDataImpl)cpPolyShapeCacheData,
	(cpShapeDestroyImpl)cpPolyShapeDestroy,
	(cpShapeNearestPointQueryImpl)cpPolyShapeNearestPointQuery,
	(cpShapeSegmentQueryImpl)cpPolyShapeSegmentQuery,
};

cpBool
cpPolyValidate(const cpVect *verts, const int numVerts)
{
	for(int i=0; i<numVerts; i++){
		cpVect a = verts[i];
		cpVect b = verts[(i+1)%numVerts];
		cpVect c = verts[(i+2)%numVerts];
		
		if(cpvcross(cpvsub(b, a), cpvsub(c, a)) > 0.0f){
			return cpFalse;
		}
	}
	
	return cpTrue;
}

int
cpPolyShapeGetNumVerts(const cpShape *shape)
{
	cpAssertHard(shape->klass == &polyClass, "Shape is not a poly shape.");
	return ((cpPolyShape *)shape)->numVerts;
}

cpVect
cpPolyShapeGetVert(const cpShape *shape, int idx)
{
	cpAssertHard(shape->klass == &polyClass, "Shape is not a poly shape.");
	cpAssertHard(0 <= idx && idx < cpPolyShapeGetNumVerts(shape), "Index out of range.");
	
	return ((cpPolyShape *)shape)->verts[idx];
}

cpFloat
cpPolyShapeGetRadius(const cpShape *shape)
{
	cpAssertHard(shape->klass == &polyClass, "Shape is not a poly shape.");
	return ((cpPolyShape *)shape)->r;
}


static void
setUpVerts(cpPolyShape *poly, int numVerts, const cpVect *verts, cpVect offset)
{
	// Fail if the user attempts to pass a concave poly, or a bad winding.
	cpAssertHard(cpPolyValidate(verts, numVerts), "Polygon is concave or has a reversed winding. Consider using cpConvexHull() or CP_CONVEX_HULL().");
	
	poly->numVerts = numVerts;
	poly->verts = (cpVect *)cpcalloc(2*numVerts, sizeof(cpVect));
	poly->planes = (cpSplittingPlane *)cpcalloc(2*numVerts, sizeof(cpSplittingPlane));
	poly->tVerts = poly->verts + numVerts;
	poly->tPlanes = poly->planes + numVerts;
	
	for(int i=0; i<numVerts; i++){
		cpVect a = cpvadd(offset, verts[i]);
		cpVect b = cpvadd(offset, verts[(i+1)%numVerts]);
		cpVect n = cpvnormalize(cpvperp(cpvsub(b, a)));

		poly->verts[i] = a;
		poly->planes[i].n = n;
		poly->planes[i].d = cpvdot(n, a);
	}
	
	// TODO: Why did I add this? It duplicates work from above.
	for(int i=0; i<numVerts; i++){
		poly->planes[i] = cpSplittingPlaneNew(poly->verts[(i - 1 + numVerts)%numVerts], poly->verts[i]);
	}
}

cpPolyShape *
cpPolyShapeInit(cpPolyShape *poly, cpBody *body, int numVerts, const cpVect *verts, cpVect offset)
{
	return cpPolyShapeInit2(poly, body, numVerts, verts, offset, 0.0f);
}

cpPolyShape *
cpPolyShapeInit2(cpPolyShape *poly, cpBody *body, int numVerts, const cpVect *verts, cpVect offset, cpFloat radius)
{
	setUpVerts(poly, numVerts, verts, offset);
	cpShapeInit((cpShape *)poly, &polyClass, body);
	poly->r = radius;

	return poly;
}


cpShape *
cpPolyShapeNew(cpBody *body, int numVerts, const cpVect *verts, cpVect offset)
{
	return cpPolyShapeNew2(body, numVerts, verts, offset, 0.0f);
}

cpShape *
cpPolyShapeNew2(cpBody *body, int numVerts, const cpVect *verts, cpVect offset, cpFloat radius)
{
	return (cpShape *)cpPolyShapeInit2(cpPolyShapeAlloc(), body, numVerts, verts, offset, radius);
}

cpPolyShape *
cpBoxShapeInit(cpPolyShape *poly, cpBody *body, cpFloat width, cpFloat height)
{
	cpFloat hw = width/2.0f;
	cpFloat hh = height/2.0f;
	
	return cpBoxShapeInit2(poly, body, cpBBNew(-hw, -hh, hw, hh));
}

cpPolyShape *
cpBoxShapeInit2(cpPolyShape *poly, cpBody *body, cpBB box)
{
	return cpBoxShapeInit3(poly, body, box, 0.0f);
}

cpPolyShape *
cpBoxShapeInit3(cpPolyShape *poly, cpBody *body, cpBB box, cpFloat radius)
{
	cpVect verts[] = {
		cpv(box.l, box.b),
		cpv(box.l, box.t),
		cpv(box.r, box.t),
		cpv(box.r, box.b),
	};
	
	return cpPolyShapeInit2(poly, body, 4, verts, cpvzero, radius);
}

cpShape *
cpBoxShapeNew(cpBody *body, cpFloat width, cpFloat height)
{
	return (cpShape *)cpBoxShapeInit(cpPolyShapeAlloc(), body, width, height);
}

cpShape *
cpBoxShapeNew2(cpBody *body, cpBB box)
{
	return (cpShape *)cpBoxShapeInit2(cpPolyShapeAlloc(), body, box);
}

cpShape *
cpBoxShapeNew3(cpBody *body, cpBB box, cpFloat radius)
{
	return (cpShape *)cpBoxShapeInit3(cpPolyShapeAlloc(), body, box, radius);
}

// Unsafe API (chipmunk_unsafe.h)

void
cpPolyShapeSetVerts(cpShape *shape, int numVerts, cpVect *verts, cpVect offset)
{
	cpAssertHard(shape->klass == &polyClass, "Shape is not a poly shape.");
	cpPolyShapeDestroy((cpPolyShape *)shape);
	setUpVerts((cpPolyShape *)shape, numVerts, verts, offset);
}

void
cpPolyShapeSetRadius(cpShape *shape, cpFloat radius)
{
	cpAssertHard(shape->klass == &polyClass, "Shape is not a poly shape.");
	((cpPolyShape *)shape)->r = radius;
}
