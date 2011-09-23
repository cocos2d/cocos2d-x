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
	
	for(int i=0; i<steps; i++)
		cpSpaceStep(space, dt);
}

static cpSpace *
init(void)
{
	cpResetShapeIdCounter();
	
	space = cpSpaceNew();
	space->iterations = 30;
	cpSpaceResizeActiveHash(space, 30.0f, 2999);
	cpSpaceResizeStaticHash(space, 30.0f, 999);
	space->gravity = cpv(0, -300);
	space->sleepTimeThreshold = 0.5f;
	
	cpBody *body;
	
	cpShape *shape;
	
	// Vertexes for the dominos.
	int num = 4;
	cpVect verts[] = {
		cpv(-3,-20),
		cpv(-3, 20),
		cpv( 3, 20),
		cpv( 3,-20),
	};
	
	// Add a floor.
	shape = cpSpaceAddShape(space, cpSegmentShapeNew(&space->staticBody, cpv(-600,-240), cpv(600,-240), 0.0f));
	shape->e = 1.0f; shape->u = 1.0f;
	shape->layers = NOT_GRABABLE_MASK;
	
	// Shared friction constant.
	cpFloat u = 0.6f;
	
	// Add the dominoes. Skim over this. It doesn't do anything fancy, and it's hard to follow.
	int n = 9;
	for(int i=1; i<=n; i++){
		cpVect offset = cpv(-i*60/2.0f, (n - i)*52);
		
		for(int j=0; j<i; j++){
			body = cpSpaceAddBody(space, cpBodyNew(1.0f, cpMomentForPoly(1.0f, num, verts, cpvzero)));
			body->p = cpvadd(cpv(j*60, -220), offset);
			
			shape = cpSpaceAddShape(space, cpPolyShapeNew(body, num, verts, cpvzero));
			shape->e = 0.0f; shape->u = u;
			

			body = cpSpaceAddBody(space, cpBodyNew(1.0f, cpMomentForPoly(1.0f, num, verts, cpvzero)));
			body->p = cpvadd(cpv(j*60, -197), offset);
			cpBodySetAngle(body, (cpFloat)M_PI/2.0f);
			
			shape = cpSpaceAddShape(space, cpPolyShapeNew(body, num, verts, cpvzero));
			shape->e = 0.0f; shape->u = u;
			
			
			if(j == (i - 1)) continue;
			body = cpSpaceAddBody(space, cpBodyNew(1.0f, cpMomentForPoly(1.0f, num, verts, cpvzero)));
			body->p = cpvadd(cpv(j*60 + 30, -191), offset);
			cpBodySetAngle(body, (cpFloat)M_PI/2.0f);
			
			shape = cpSpaceAddShape(space, cpPolyShapeNew(body, num, verts, cpvzero));
			shape->e = 0.0f; shape->u = u;
		}

		body = cpSpaceAddBody(space, cpBodyNew(1.0f, cpMomentForPoly(1.0f, num, verts, cpvzero)));
		body->p = cpvadd(cpv(-17, -174), offset);
		
		shape = cpSpaceAddShape(space, cpPolyShapeNew(body, num, verts, cpvzero));
		shape->e = 0.0f; shape->u = u;
		

		body = cpSpaceAddBody(space, cpBodyNew(1.0f, cpMomentForPoly(1.0f, num, verts, cpvzero)));
		body->p = cpvadd(cpv((i - 1)*60 + 17, -174), offset);
		
		shape = cpSpaceAddShape(space, cpPolyShapeNew(body, num, verts, cpvzero));
		shape->e = 0.0f; shape->u = u;
	}
	
	// Give the last domino a little tap.
//	body->w = -1;
//	body->v = cpv(-body->w*20, 0);
	return space;
}

static void
destroy(void)
{
	cpSpaceFreeChildren(space);
	cpSpaceFree(space);
}

chipmunkDemo PyramidTopple = {
	"Pyramid Topple",
	NULL,
	init,
	update,
	destroy,
};
