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

static void
update(int ticks)
{
	int steps = 3;
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
	space->iterations = 30;
	cpSpaceResizeStaticHash(space, 40.0f, 1000);
	cpSpaceResizeActiveHash(space, 40.0f, 1000);
	space->gravity = cpv(0, -100);
	space->sleepTimeThreshold = 0.5f;
	
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
	
	// Add lots of boxes.
	for(int i=0; i<14; i++){
		for(int j=0; j<=i; j++){
			body = cpSpaceAddBody(space, cpBodyNew(1.0f, cpMomentForBox(1.0f, 30.0f, 30.0f)));
			body->p = cpv(j*32 - i*16, 300 - i*32);
			
			shape = cpSpaceAddShape(space, cpBoxShapeNew(body, 30.0f, 30.0f));
			shape->e = 0.0f; shape->u = 0.8f;
		}
	}
	
	// Add a ball to make things more interesting
	cpFloat radius = 15.0f;
	body = cpSpaceAddBody(space, cpBodyNew(10.0f, cpMomentForCircle(10.0f, 0.0f, radius, cpvzero)));
	body->p = cpv(0, -240 + radius+5);

	shape = cpSpaceAddShape(space, cpCircleShapeNew(body, radius, cpvzero));
	shape->e = 0.0f; shape->u = 0.9f;
	
	return space;
}

static void
destroy(void)
{
	cpSpaceFreeChildren(space);
	cpSpaceFree(space);
}

chipmunkDemo PyramidStack = {
	"Pyramid Stack",
	NULL,
	init,
	update,
	destroy,
};
