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
static cpConstraint *motor;

#define numBalls 5
static cpBody *balls[numBalls];

static void
update(int ticks)
{
	cpFloat coef = (2.0f + arrowDirection.y)/3.0f;
	cpFloat rate = arrowDirection.x*30.0f*coef;
	
	cpSimpleMotorSetRate(motor, rate);
	motor->maxForce = (rate ? 1000000.0f : 0.0f);

	int steps = 2;
	cpFloat dt = 1.0f/60.0f/(cpFloat)steps;
	
	for(int i=0; i<steps; i++){
		cpSpaceStep(space, dt);
		
		for(int i=0; i<numBalls; i++){
			cpBody *ball = balls[i];
			if(ball->p.x > 320.0f){
				ball->v = cpvzero;
				ball->p = cpv(-224.0f, 200.0f);
			}
		}
	}
}

static cpBody *
add_ball(cpVect pos)
{
	cpBody *body = cpSpaceAddBody(space, cpBodyNew(1.0f, cpMomentForCircle(1.0f, 30, 0, cpvzero)));
	body->p = pos;
	
	cpShape *shape = cpSpaceAddShape(space, cpCircleShapeNew(body, 30, cpvzero));
	shape->e = 0.0f; shape->u = 0.5f;
	
	return body;
}

static cpSpace *
init(void)
{
	space = cpSpaceNew();
	space->gravity = cpv(0, -600);
	
	cpBody *staticBody = &space->staticBody;
	cpShape *shape;
	
	// beveling all of the line segments slightly helps prevent things from getting stuck on cracks
	shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(-256,16), cpv(-256,300), 2.0f));
	shape->e = 0.0f; shape->u = 0.5f; shape->layers = 1;
	shape->layers = NOT_GRABABLE_MASK;

	shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(-256,16), cpv(-192,0), 2.0f));
	shape->e = 0.0f; shape->u = 0.5f; shape->layers = 1;
	shape->layers = NOT_GRABABLE_MASK;

	shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(-192,0), cpv(-192, -64), 2.0f));
	shape->e = 0.0f; shape->u = 0.5f; shape->layers = 1;
	shape->layers = NOT_GRABABLE_MASK;

	shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(-128,-64), cpv(-128,144), 2.0f));
	shape->e = 0.0f; shape->u = 0.5f; shape->layers = 1;
	shape->layers = NOT_GRABABLE_MASK;

	shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(-192,80), cpv(-192,176), 2.0f));
	shape->e = 0.0f; shape->u = 0.5f; shape->layers = 1;
	shape->layers = NOT_GRABABLE_MASK;

	shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(-192,176), cpv(-128,240), 2.0f));
	shape->e = 0.0f; shape->u = 0.0f; shape->layers = 1;
	shape->layers = NOT_GRABABLE_MASK;

	shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(-128,144), cpv(192,64), 2.0f));
	shape->e = 0.0f; shape->u = 0.5f; shape->layers = 1;
	shape->layers = NOT_GRABABLE_MASK;

	cpVect verts[] = {
		cpv(-30,-80),
		cpv(-30, 80),
		cpv( 30, 64),
		cpv( 30,-80),
	};

	cpBody *plunger = cpSpaceAddBody(space, cpBodyNew(1.0f, INFINITY));
	plunger->p = cpv(-160,-80);
	
	shape = cpSpaceAddShape(space, cpPolyShapeNew(plunger, 4, verts, cpvzero));
	shape->e = 1.0f; shape->u = 0.5f; shape->layers = 1;
	
	// add balls to hopper
	for(int i=0; i<numBalls; i++)
		balls[i] = add_ball(cpv(-224 + i,80 + 64*i));
	
	// add small gear
	cpBody *smallGear = cpSpaceAddBody(space, cpBodyNew(10.0f, cpMomentForCircle(10.0f, 80, 0, cpvzero)));
	smallGear->p = cpv(-160,-160);
	cpBodySetAngle(smallGear, (cpFloat)-M_PI_2);

	shape = cpSpaceAddShape(space, cpCircleShapeNew(smallGear, 80.0f, cpvzero));
	shape->layers = 0;
	
	cpSpaceAddConstraint(space, cpPivotJointNew2(staticBody, smallGear, cpv(-160,-160), cpvzero));

	// add big gear
	cpBody *bigGear = cpSpaceAddBody(space, cpBodyNew(40.0f, cpMomentForCircle(40.0f, 160, 0, cpvzero)));
	bigGear->p = cpv(80,-160);
	cpBodySetAngle(bigGear, (cpFloat)M_PI_2);
	
	shape = cpSpaceAddShape(space, cpCircleShapeNew(bigGear, 160.0f, cpvzero));
	shape->layers = 0;
	
	cpSpaceAddConstraint(space, cpPivotJointNew2(staticBody, bigGear, cpv(80,-160), cpvzero));

	// connect the plunger to the small gear.
	cpSpaceAddConstraint(space, cpPinJointNew(smallGear, plunger, cpv(80,0), cpv(0,0)));
	// connect the gears.
	cpSpaceAddConstraint(space, cpGearJointNew(smallGear, bigGear, (cpFloat)-M_PI_2, -2.0f));
	
	
	// feeder mechanism
	cpFloat bottom = -300.0f;
	cpFloat top = 32.0f;
	cpBody *feeder = cpSpaceAddBody(space, cpBodyNew(1.0f, cpMomentForSegment(1.0f, cpv(-224.0f, bottom), cpv(-224.0f, top))));
	feeder->p = cpv(-224, (bottom + top)/2.0f);
	
	cpFloat len = top - bottom;
	cpSpaceAddShape(space, cpSegmentShapeNew(feeder, cpv(0.0f, len/2.0f), cpv(0.0f, -len/2.0f), 20.0f));
	
	cpSpaceAddConstraint(space, cpPivotJointNew2(staticBody, feeder, cpv(-224.0f, bottom), cpv(0.0f, -len/2.0f)));
	cpVect anchr = cpBodyWorld2Local(feeder, cpv(-224.0f, -160.0f));
	cpSpaceAddConstraint(space, cpPinJointNew(feeder, smallGear, anchr, cpv(0.0f, 80.0f)));

	// motorize the second gear
	motor = cpSpaceAddConstraint(space, cpSimpleMotorNew(staticBody, bigGear, 3.0f));

	return space;
}

static void
destroy(void)
{
	cpSpaceFreeChildren(space);
	cpSpaceFree(space);
}

chipmunkDemo Pump = {
	"Pump",
	NULL,
	init,
	update,
	destroy,
};
