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

enum CollisionTypes {
	BALL_TYPE,
	BLOCKING_SENSOR_TYPE,
	CATCH_SENSOR_TYPE,
};

typedef struct Emitter {
	int queue;
	int blocked;
	cpVect position;
} Emitter;

static Emitter emitterInstance;

static cpBool
blockerBegin(cpArbiter *arb, cpSpace *space, void *unused)
{
	CP_ARBITER_GET_SHAPES(arb, a, b);
	Emitter *emitter = (Emitter *) a->data;
	
	emitter->blocked++;
	
	return cpFalse; // Return values from sensors callbacks are ignored,
}

static void
blockerSeparate(cpArbiter *arb, cpSpace *space, void *unused)
{
	CP_ARBITER_GET_SHAPES(arb, a, b);
	Emitter *emitter = (Emitter *) a->data;
	
	emitter->blocked--;
}

static void
postStepRemove(cpSpace *space, cpShape *shape, void *unused)
{
	cpSpaceRemoveBody(space, shape->body);
	cpBodyFree(shape->body);
	
	cpSpaceRemoveShape(space, shape);
	cpShapeFree(shape);
}

static cpBool
catcherBarBegin(cpArbiter *arb, cpSpace *space, void *unused)
{
	cpShape *a, *b; cpArbiterGetShapes(arb, &a, &b);
	Emitter *emitter = (Emitter *) a->data;
	
	emitter->queue++;
	cpSpaceAddPostStepCallback(space, (cpPostStepFunc)postStepRemove, b, NULL);
	
	return cpFalse;
}

static cpFloat frand_unit(){return 2.0f*((cpFloat)rand()/(cpFloat)RAND_MAX) - 1.0f;}

static void
update(int ticks)
{
	int steps = 1;
	cpFloat dt = 1.0f/60.0f/(cpFloat)steps;
	
	if(!emitterInstance.blocked && emitterInstance.queue){
		emitterInstance.queue--;
		
		cpBody *body = cpSpaceAddBody(space, cpBodyNew(1.0f, cpMomentForCircle(1.0f, 15.0f, 0.0f, cpvzero)));
		body->p = emitterInstance.position;
		body->v = cpvmult(cpv(frand_unit(), frand_unit()), 100.0f);
		
		cpShape *shape = cpSpaceAddShape(space, cpCircleShapeNew(body, 15.0f, cpvzero));
		shape->collision_type = BALL_TYPE;
	}
	
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
	
	cpBody *staticBody = &space->staticBody;
	cpShape *shape;
	
	// Data structure for our ball emitter
	// We'll use two sensors for it, one to see if the emitter is blocked
	// a second to catch the balls and add them back to the emitter
	emitterInstance.queue = 5;
	emitterInstance.blocked = 0;
	emitterInstance.position = cpv(0, 150);
	
	// Create our blocking sensor, so we know when the emitter is clear to emit another ball
	shape = cpSpaceAddShape(space, cpCircleShapeNew(staticBody, 15.0f, emitterInstance.position));
	shape->sensor = 1;
	shape->collision_type = BLOCKING_SENSOR_TYPE;
	shape->data = &emitterInstance;
	
	// Create our catch sensor to requeue the balls when they reach the bottom of the screen
	shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(-2000, -200), cpv(2000, -200), 15.0f));
	shape->sensor = 1;
	shape->collision_type = CATCH_SENSOR_TYPE;
	shape->data = &emitterInstance;
	
	cpSpaceAddCollisionHandler(space, BLOCKING_SENSOR_TYPE, BALL_TYPE, blockerBegin, NULL, NULL, blockerSeparate, NULL);
	cpSpaceAddCollisionHandler(space, CATCH_SENSOR_TYPE, BALL_TYPE, catcherBarBegin, NULL, NULL, NULL, NULL);
	
	return space;
}

static void
destroy(void)
{
	cpSpaceFreeChildren(space);
	cpSpaceFree(space);
}

chipmunkDemo Sensors = {
	"Sensors",
	NULL,
	init,
	update,
	destroy,
};
