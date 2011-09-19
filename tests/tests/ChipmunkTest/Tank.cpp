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

extern cpVect mousePoint;

static cpSpace *space;

static cpBody *tankBody, *tankControlBody;

static void
update(int ticks)
{
	int steps = 1;
	cpFloat dt = 1.0f/60.0f/(cpFloat)steps;
	
	for(int i=0; i<steps; i++){
		// turn the control body based on the angle relative to the actual body
		cpVect mouseDelta = cpvsub(mousePoint, tankBody->p);
		cpFloat turn = cpvtoangle(cpvunrotate(tankBody->rot, mouseDelta));
		cpBodySetAngle(tankControlBody, tankBody->a - turn);
		
		// drive the tank towards the mouse
		if(cpvnear(mousePoint, tankBody->p, 30.0f)){
			tankControlBody->v = cpvzero; // stop
		} else {
			cpFloat direction = (cpvdot(mouseDelta, tankBody->rot) > 0.0f ? 1.0f : -1.0f);
			tankControlBody->v = cpvrotate(tankBody->rot, cpv(30.0f*direction, 0.0f));
		}
		
		cpSpaceStep(space, dt);
	}
}

static cpBody *
add_box(cpFloat size, cpFloat mass)
{
	cpVect verts[] = {
		cpv(-size,-size),
		cpv(-size, size),
		cpv( size, size),
		cpv( size,-size),
	};
	
	cpFloat radius = cpvlength(cpv(size, size));

	cpBody *body = cpSpaceAddBody(space, cpBodyNew(mass, cpMomentForPoly(mass, 4, verts, cpvzero)));
	body->p = cpv(frand()*(640 - 2*radius) - (320 - radius), frand()*(480 - 2*radius) - (240 - radius));
	
	cpShape *shape = cpSpaceAddShape(space, cpPolyShapeNew(body, 4, verts, cpvzero));
	shape->e = 0.0f; shape->u = 0.7f;
	
	return body;
}

static cpSpace *
init(void)
{
	cpResetShapeIdCounter();
	
	space = cpSpaceNew();
	cpSpaceResizeActiveHash(space, 30.0f, 1000);
	space->iterations = 10;
	space->sleepTimeThreshold = 0.5f;
	
	cpBody *staticBody = &space->staticBody;
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

	shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(-320,240), cpv(320,240), 0.0f));
	shape->e = 1.0f; shape->u = 1.0f;
	shape->layers = NOT_GRABABLE_MASK;
	
	for(int i=0; i<50; i++){
		cpBody *body = add_box(10.0f, 1.0f);
		
		cpConstraint *pivot = cpSpaceAddConstraint(space, cpPivotJointNew2(staticBody, body, cpvzero, cpvzero));
		pivot->biasCoef = 0.0f; // disable joint correction
		pivot->maxForce = 1000.0f; // emulate linear friction
		
		cpConstraint *gear = cpSpaceAddConstraint(space, cpGearJointNew(staticBody, body, 0.0f, 1.0f));
		gear->biasCoef = 0.0f; // disable joint correction
		gear->maxForce = 5000.0f; // emulate angular friction
	}
	
	// We joint the tank to the control body and control the tank indirectly by modifying the control body.
	tankControlBody = cpBodyNew(INFINITY, INFINITY);
	tankBody = add_box(15.0f, 10.0f);
	
	cpConstraint *pivot = cpSpaceAddConstraint(space, cpPivotJointNew2(tankControlBody, tankBody, cpvzero, cpvzero));
	pivot->biasCoef = 0.0f; // disable joint correction
	pivot->maxForce = 10000.0f; // emulate linear friction
	
	cpConstraint *gear = cpSpaceAddConstraint(space, cpGearJointNew(tankControlBody, tankBody, 0.0f, 1.0f));
	gear->biasCoef = 1.0f; // limit angular correction rate
	gear->maxBias = 1.0f; // limit angular correction rate
	gear->maxForce = 500000.0f; // emulate angular friction
		
	return space;
}

static void
destroy(void)
{
	cpBodyFree(tankControlBody);
	cpSpaceFreeChildren(space);
	cpSpaceFree(space);
}

chipmunkDemo Tank = {
	"Tank",
	NULL,
	init,
	update,
	destroy,
};
