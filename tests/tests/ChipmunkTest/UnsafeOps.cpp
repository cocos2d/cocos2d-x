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
#include <string.h>

#include "chipmunk.h"
#include "chipmunk_unsafe.h"
#include "drawSpace.h"
#include "ChipmunkDemo.h"

static cpSpace *space;

#define NUM_CIRCLES 30
static cpShape *circles[NUM_CIRCLES];
static cpFloat circleRadius = 30.0f;

static void
update(int ticks)
{
	if(arrowDirection.y){
		circleRadius = cpfmax(10.0f, circleRadius + arrowDirection.y);
		
		for(int i=0; i<NUM_CIRCLES; i++){
			circles[i]->body->m = cpMomentForCircle(1.0f, 0.0f, circleRadius, cpvzero);
			cpCircleShapeSetRadius(circles[i], circleRadius);
		}
	}
	
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
	space->iterations = 5;
	space->gravity = cpv(0, -100);
	
	cpSpaceResizeStaticHash(space, 40.0f, 999);
	cpSpaceResizeActiveHash(space, 30.0f, 2999);
	
	cpBody *body, *staticBody = &space->staticBody;
	cpShape *shape;
	
	shape = cpSpaceAddStaticShape(space, cpSegmentShapeNew(staticBody, cpv(-320,-240), cpv(-320,240), 0.0f));
	shape->e = 1.0f; shape->u = 1.0f;
	shape->layers = NOT_GRABABLE_MASK;

	shape = cpSpaceAddStaticShape(space, cpSegmentShapeNew(staticBody, cpv(320,-240), cpv(320,240), 0.0f));
	shape->e = 1.0f; shape->u = 1.0f;
	shape->layers = NOT_GRABABLE_MASK;

	shape = cpSpaceAddStaticShape(space, cpSegmentShapeNew(staticBody, cpv(-320,-240), cpv(320,-240), 0.0f));
	shape->e = 1.0f; shape->u = 1.0f;
	shape->layers = NOT_GRABABLE_MASK;
	
	for(int i=0; i<NUM_CIRCLES; i++){
		body = cpSpaceAddBody(space, cpBodyNew(1.0f, cpMomentForCircle(1.0f, 0.0f, circleRadius, cpvzero)));
		body->p = cpvmult(cpv(frand()*2.0f - 1.0f, frand()*2.0f - 1.0f), circleRadius*5.0f);
		
		circles[i] = shape = cpSpaceAddShape(space, cpCircleShapeNew(body, circleRadius, cpvzero));
		shape->e = 0.0f; shape->u = 1.0f;
	}
	
	strcat(messageString,
		"chipmunk_unsafe.h Contains functions for changing shapes, but they can cause severe stability problems if used incorrectly.\n"
		"Shape changes occur as instantaneous changes to position without an accompanying velocity change. USE WITH CAUTION!");
	return space;
}

static void
destroy(void)
{
	cpSpaceFreeChildren(space);
	cpSpaceFree(space);
}

chipmunkDemo UnsafeOps = {
	"Unsafe Operations",
	NULL,
	init,
	update,
	destroy,
};
