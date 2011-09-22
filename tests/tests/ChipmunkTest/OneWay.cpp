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

#include "chipmunk.h"
#include "drawSpace.h"
#include "ChipmunkDemo.h"

static cpSpace *space;

typedef struct OneWayPlatform {
	cpVect n; // direction objects may pass through
	cpArray *passThruList; // list of objects passing through
} OneWayPlatform;

static OneWayPlatform platformInstance;

static cpBool
preSolve(cpArbiter *arb, cpSpace *space, void *ignore)
{
	CP_ARBITER_GET_SHAPES(arb, a, b);
	OneWayPlatform *platform = (OneWayPlatform *)a->data;
		
	if(cpvdot(cpArbiterGetNormal(arb, 0), platform->n) < 0){
		cpArbiterIgnore(arb);
		return cpFalse;
	}
	
	return cpTrue;
}

static void
update(int ticks)
{
	int steps = 1;
	cpFloat dt = 1.0f/60.0f/(cpFloat)steps;
	
	for(int i=0; i<steps; i++){
		cpSpaceStep(space, dt);
	}
}

static cpSpace *
init(void)
{
	cpResetShapeIdCounter();
	
	space = cpSpaceNew();
	space->iterations = 10;
	space->gravity = cpv(0, -100);

	cpBody *body, *staticBody = &space->staticBody;
	cpShape *shape;

	// Create segments around the edge of the screen.
	shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(-320,-240), cpv(-320,240), 0.0f));
	shape->e = 1.0f; shape->u = 1.0f;
	shape->layers = NOT_GRABABLE_MASK;

	shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(320,-240), cpv(320,240), 0.0f));
	shape->e = 1.0f; shape->u = 1.0f;
	shape->layers = NOT_GRABABLE_MASK;

	shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(-320,-240), cpv(320,-240), 0.0f));
	shape->e = 1.0f; shape->u = 1.0f;
	shape->layers = NOT_GRABABLE_MASK;
	
	// Add our one way segment
	shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(-160,-100), cpv(160,-100), 10.0f));
	shape->e = 1.0f; shape->u = 1.0f;
	shape->collision_type = 1;
	shape->layers = NOT_GRABABLE_MASK;
	
	// We'll use the data pointer for the OneWayPlatform struct
	platformInstance.n = cpv(0, 1); // let objects pass upwards
	platformInstance.passThruList = cpArrayNew(0);
	shape->data = &platformInstance;
	
	
	// Add a ball to make things more interesting
	cpFloat radius = 15.0f;
	body = cpSpaceAddBody(space, cpBodyNew(10.0f, cpMomentForCircle(10.0f, 0.0f, radius, cpvzero)));
	body->p = cpv(0, -200);
	body->v = cpv(0, 170);

	shape = cpSpaceAddShape(space, cpCircleShapeNew(body, radius, cpvzero));
	shape->e = 0.0f; shape->u = 0.9f;
	shape->collision_type = 2;
	
	cpSpaceAddCollisionHandler(space, 1, 2, NULL, preSolve, NULL, NULL, NULL);
	
	return space;
}

static void
destroy(void)
{
	cpSpaceFreeChildren(space);
	cpSpaceFree(space);
	
	cpArrayFree(platformInstance.passThruList);
}

chipmunkDemo OneWay = {
	"One Way Platforms",
	NULL,
	init,
	update,
	destroy,
};
