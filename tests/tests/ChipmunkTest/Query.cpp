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
#include "drawSpace.h"
#include "ChipmunkDemo.h"

#include "chipmunk_unsafe.h"

static cpSpace *space;
extern cpVect mousePoint;

static cpShape *querySeg = NULL;


static void
update(int ticks)
{
	messageString[0] = '\0';
	
	cpVect start = cpvzero;
	cpVect end = /*cpv(0, 85);//*/mousePoint;
	cpVect lineEnd = end;
	
	{
		char infoString[1024];
		sprintf(infoString, "Query: Dist(%f) Point%s, ", cpvdist(start, end), cpvstr(end));
		strcat(messageString, infoString);
	}
	
	cpSegmentQueryInfo info = {};
	if(cpSpaceSegmentQueryFirst(space, start, end, CP_ALL_LAYERS, CP_NO_GROUP, &info)){
		cpVect point = cpSegmentQueryHitPoint(start, end, info);
		lineEnd = cpvadd(point, cpvzero);//cpvmult(info.n, 4.0f));
		
		char infoString[1024];
		sprintf(infoString, "Segment Query: Dist(%f) Normal%s", cpSegmentQueryHitDist(start, end, info), cpvstr(info.n));
		strcat(messageString, infoString);
	} else {
		strcat(messageString, "Segment Query (None)");
	}
	
	cpSegmentShapeSetEndpoints(querySeg, start, lineEnd);
	cpShapeCacheBB(querySeg); // force it to update it's collision detection data so it will draw
	
	// normal other stuff.
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
	space->elasticIterations = 0;
	space->iterations = 5;

	cpSpaceResizeStaticHash(space, 40.0f, 999);
	cpSpaceResizeActiveHash(space, 30.0f, 2999);

	cpBody *staticBody = &space->staticBody;
	cpShape *shape;
	
	// add a non-collidable segment as a quick and dirty way to draw the query line
	shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpvzero, cpv(100.0f, 0.0f), 4.0f));
	shape->layers = 0;
	querySeg = shape;
	
	{ // add a fat segment
		cpFloat mass = 1.0f;
		cpFloat length = 100.0f;
		cpVect a = cpv(-length/2.0f, 0.0f), b = cpv(length/2.0f, 0.0f);
		
		cpBody *body = cpSpaceAddBody(space, cpBodyNew(mass, cpMomentForSegment(mass, a, b)));
		body->p = cpv(0.0f, 100.0f);
		
		cpSpaceAddShape(space, cpSegmentShapeNew(body, a, b, 20.0f));
	}
	
	{ // add a static segment
		cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(0, 300), cpv(300, 0), 0.0f));
	}
	
	{ // add a pentagon
		cpFloat mass = 1.0f;
		const int NUM_VERTS = 5;
		
		cpVect verts[NUM_VERTS];
		for(int i=0; i<NUM_VERTS; i++){
			cpFloat angle = -2*(cpFloat)M_PI*i/((cpFloat) NUM_VERTS);
			verts[i] = cpv(30*cosf(angle), 30*sinf(angle));
		}
		
		cpBody *body = cpSpaceAddBody(space, cpBodyNew(mass, cpMomentForPoly(mass, NUM_VERTS, verts, cpvzero)));
		body->p = cpv(50.0f, 50.0f);
		
		cpSpaceAddShape(space, cpPolyShapeNew(body, NUM_VERTS, verts, cpvzero));
	}
	
	{ // add a circle
		cpFloat mass = 1.0f;
		cpFloat r = 20.0f;
		
		cpBody *body = cpSpaceAddBody(space, cpBodyNew(mass, cpMomentForCircle(mass, 0.0f, r, cpvzero)));
		body->p = cpv(100.0f, 100.0f);
		
		cpSpaceAddShape(space, cpCircleShapeNew(body, r, cpvzero));
	}
	
	return space;
}

static void
destroy(void)
{
	cpSpaceFreeChildren(space);
	cpSpaceFree(space);
}

chipmunkDemo Query = {
	"Segment Query",
	NULL,
	init,
	update,
	destroy,
};
