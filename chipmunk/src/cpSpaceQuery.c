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

#include "chipmunk_private.h"

//MARK: Point Query Functions

typedef struct pointQueryContext {
	cpLayers layers;
	cpGroup group;
	cpSpacePointQueryFunc func;
	void *data;
} pointQueryContext;

static void 
pointQueryHelper(cpVect *point, cpShape *shape, pointQueryContext *context)
{
	if(
		!(shape->group && context->group == shape->group) && (context->layers&shape->layers) &&
		cpShapePointQuery(shape, *point)
	){
		context->func(shape, context->data);
	}
}

void
cpSpacePointQuery(cpSpace *space, cpVect point, cpLayers layers, cpGroup group, cpSpacePointQueryFunc func, void *data)
{
	pointQueryContext context = {layers, group, func, data};
	
	cpSpaceLock(space); {
    cpSpatialIndexPointQuery(space->activeShapes, point, (cpSpatialIndexQueryFunc)pointQueryHelper, &context);
    cpSpatialIndexPointQuery(space->staticShapes, point, (cpSpatialIndexQueryFunc)pointQueryHelper, &context);
	} cpSpaceUnlock(space, cpTrue);
}

static void
rememberLastPointQuery(cpShape *shape, cpShape **outShape)
{
	if(!shape->sensor) *outShape = shape;
}

cpShape *
cpSpacePointQueryFirst(cpSpace *space, cpVect point, cpLayers layers, cpGroup group)
{
	cpShape *shape = NULL;
	cpSpacePointQuery(space, point, layers, group, (cpSpacePointQueryFunc)rememberLastPointQuery, &shape);
	
	return shape;
}


//MARK: Segment Query Functions

typedef struct segQueryContext {
	cpVect start, end;
	cpLayers layers;
	cpGroup group;
	cpSpaceSegmentQueryFunc func;
} segQueryContext;

static cpFloat
segQueryFunc(segQueryContext *context, cpShape *shape, void *data)
{
	cpSegmentQueryInfo info;
	
	if(
		!(shape->group && context->group == shape->group) && (context->layers&shape->layers) &&
		cpShapeSegmentQuery(shape, context->start, context->end, &info)
	){
		context->func(shape, info.t, info.n, data);
	}
	
	return 1.0f;
}

void
cpSpaceSegmentQuery(cpSpace *space, cpVect start, cpVect end, cpLayers layers, cpGroup group, cpSpaceSegmentQueryFunc func, void *data)
{
	segQueryContext context = {
		start, end,
		layers, group,
		func,
	};
	
	cpSpaceLock(space); {
    cpSpatialIndexSegmentQuery(space->staticShapes, &context, start, end, 1.0f, (cpSpatialIndexSegmentQueryFunc)segQueryFunc, data);
    cpSpatialIndexSegmentQuery(space->activeShapes, &context, start, end, 1.0f, (cpSpatialIndexSegmentQueryFunc)segQueryFunc, data);
	} cpSpaceUnlock(space, cpTrue);
}

typedef struct segQueryFirstContext {
	cpVect start, end;
	cpLayers layers;
	cpGroup group;
} segQueryFirstContext;

static cpFloat
segQueryFirst(segQueryFirstContext *context, cpShape *shape, cpSegmentQueryInfo *out)
{
	cpSegmentQueryInfo info;
	
	if(
		!(shape->group && context->group == shape->group) && (context->layers&shape->layers) &&
		!shape->sensor &&
		cpShapeSegmentQuery(shape, context->start, context->end, &info) &&
		info.t < out->t
	){
		*out = info;
	}
	
	return out->t;
}

cpShape *
cpSpaceSegmentQueryFirst(cpSpace *space, cpVect start, cpVect end, cpLayers layers, cpGroup group, cpSegmentQueryInfo *out)
{
	cpSegmentQueryInfo info = {NULL, 1.0f, cpvzero};
	if(out){
		(*out) = info;
  } else {
		out = &info;
	}
	
	segQueryFirstContext context = {
		start, end,
		layers, group
	};
	
	cpSpatialIndexSegmentQuery(space->staticShapes, &context, start, end, 1.0f, (cpSpatialIndexSegmentQueryFunc)segQueryFirst, out);
	cpSpatialIndexSegmentQuery(space->activeShapes, &context, start, end, out->t, (cpSpatialIndexSegmentQueryFunc)segQueryFirst, out);
	
	return out->shape;
}

//MARK: BB Query Functions

typedef struct bbQueryContext {
	cpLayers layers;
	cpGroup group;
	cpSpaceBBQueryFunc func;
	void *data;
} bbQueryContext;

static void 
bbQueryHelper(cpBB *bb, cpShape *shape, bbQueryContext *context)
{
	if(
		!(shape->group && context->group == shape->group) && (context->layers&shape->layers) &&
		cpBBIntersects(*bb, shape->bb)
	){
		context->func(shape, context->data);
	}
}

void
cpSpaceBBQuery(cpSpace *space, cpBB bb, cpLayers layers, cpGroup group, cpSpaceBBQueryFunc func, void *data)
{
	bbQueryContext context = {layers, group, func, data};
	
	cpSpaceLock(space); {
    cpSpatialIndexQuery(space->activeShapes, &bb, bb, (cpSpatialIndexQueryFunc)bbQueryHelper, &context);
    cpSpatialIndexQuery(space->staticShapes, &bb, bb, (cpSpatialIndexQueryFunc)bbQueryHelper, &context);
	} cpSpaceUnlock(space, cpTrue);
}

//MARK: Shape Query Functions

typedef struct shapeQueryContext {
	cpSpaceShapeQueryFunc func;
	void *data;
	cpBool anyCollision;
} shapeQueryContext;

// Callback from the spatial hash.
static void
shapeQueryHelper(cpShape *a, cpShape *b, shapeQueryContext *context)
{
	// Reject any of the simple cases
	if(
		(a->group && a->group == b->group) ||
		!(a->layers & b->layers) ||
		a == b
	) return;
	
	cpContact contacts[CP_MAX_CONTACTS_PER_ARBITER];
	int numContacts = 0;
	
	// Shape 'a' should have the lower shape type. (required by cpCollideShapes() )
	if(a->klass->type <= b->klass->type){
		numContacts = cpCollideShapes(a, b, contacts);
	} else {
		numContacts = cpCollideShapes(b, a, contacts);
		for(int i=0; i<numContacts; i++) contacts[i].n = cpvneg(contacts[i].n);
	}
	
	if(numContacts){
		context->anyCollision = !(a->sensor || b->sensor);
		
		if(context->func){
			cpContactPointSet set = {numContacts, {}};
			for(int i=0; i<set.count; i++){
				set.points[i].point = contacts[i].p;
				set.points[i].normal = contacts[i].n;
				set.points[i].dist = contacts[i].dist;
			}
			
			context->func(b, &set, context->data);
		}
	}
}

cpBool
cpSpaceShapeQuery(cpSpace *space, cpShape *shape, cpSpaceShapeQueryFunc func, void *data)
{
	cpBody *body = shape->body;
	cpBB bb = (body ? cpShapeUpdate(shape, body->p, body->rot) : shape->bb);
	shapeQueryContext context = {func, data, cpFalse};
	
	cpSpaceLock(space); {
    cpSpatialIndexQuery(space->activeShapes, shape, bb, (cpSpatialIndexQueryFunc)shapeQueryHelper, &context);
    cpSpatialIndexQuery(space->staticShapes, shape, bb, (cpSpatialIndexQueryFunc)shapeQueryHelper, &context);
	} cpSpaceUnlock(space, cpTrue);
	
	return context.anyCollision;
}
