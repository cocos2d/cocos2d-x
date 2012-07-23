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
static cpBody *staticBody;

static void
update(int ticks)
{
	int steps = 3;
	cpFloat dt = 1.0f/60.0f/(cpFloat)steps;
	
	for(int i=0; i<steps; i++){
		cpSpaceStep(space, dt);
		
		// Manually update the position of the static shape so that
		// the box rotates.
		cpBodyUpdatePosition(staticBody, dt);
		
		// Because the box was added as a static shape and we moved it
		// we need to manually rehash the static spatial hash.
		cpSpaceRehashStatic(space);
	}
}

static cpSpace *
init(void)
{
	staticBody = cpBodyNew(INFINITY, INFINITY);
	
	cpResetShapeIdCounter();
	
	space = cpSpaceNew();
	cpSpaceResizeActiveHash(space, 40.0f, 999);
	cpSpaceResizeStaticHash(space, 40.0f, 99);
	space->gravity = cpv(0, -600);
	
	cpBody *body;
	cpShape *shape;
	
	// Vertexes for the bricks
	int num = 4;
	cpVect verts[] = {
		cpv(-30,-15),
		cpv(-30, 15),
		cpv( 30, 15),
		cpv( 30,-15),
	};
	
	// Set up the static box.
	cpVect a = cpv(-200, -200);
	cpVect b = cpv(-200,  200);
	cpVect c = cpv( 200,  200);
	cpVect d = cpv( 200, -200);
	
	shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, a, b, 0.0f));
	shape->e = 1.0f; shape->u = 1.0f;
	shape->layers = NOT_GRABABLE_MASK;

	shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, b, c, 0.0f));
	shape->e = 1.0f; shape->u = 1.0f;
	shape->layers = NOT_GRABABLE_MASK;

	shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, c, d, 0.0f));
	shape->e = 1.0f; shape->u = 1.0f;
	shape->layers = NOT_GRABABLE_MASK;

	shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, d, a, 0.0f));
	shape->e = 1.0f; shape->u = 1.0f;
	shape->layers = NOT_GRABABLE_MASK;
	
	// Give the box a little spin.
	// Because staticBody is never added to the space, we will need to
	// update it ourselves. (see above).
	// NOTE: Normally you would want to add the segments as normal and not static shapes.
	// I'm just doing it to demonstrate the cpSpaceRehashStatic() function.
	staticBody->w = 0.4f;
	
	// Add the bricks.
	for(int i=0; i<3; i++){
		for(int j=0; j<7; j++){
			body = cpSpaceAddBody(space, cpBodyNew(1.0f, cpMomentForPoly(1.0f, num, verts, cpvzero)));
			body->p = cpv(i*60 - 150, j*30 - 150);
			
			shape = cpSpaceAddShape(space, cpPolyShapeNew(body, num, verts, cpvzero));
			shape->e = 0.0f; shape->u = 0.7f;
		}
	}
	
	return space;
}

static void
destroy(void)
{
	cpBodyFree(staticBody);
	cpSpaceFreeChildren(space);
	cpSpaceFree(space);
}

chipmunkDemo Tumble = {
	"Tumble",
	NULL,
	init,
	update,
	destroy,
};
