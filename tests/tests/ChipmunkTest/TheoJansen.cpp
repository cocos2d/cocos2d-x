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

/*
 * The previous WalkBot demo I designed was fairly disappointing, so I implemented
 * the mechanism that Theo Jansen uses in his kinetic sculptures. Brilliant.
 * Read more here: http://en.wikipedia.org/wiki/Theo_Jansen
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "chipmunk.h"
#include "drawSpace.h"
#include "ChipmunkDemo.h"

static cpSpace *space;

static cpConstraint *motor;

static void
update(int ticks)
{
	cpFloat coef = (2.0f + arrowDirection.y)/3.0f;
	cpFloat rate = arrowDirection.x*10.0f*coef;
	cpSimpleMotorSetRate(motor, rate);
	motor->maxForce = (rate) ? 100000.0f : 0.0f;
	
	int steps = 3;
	cpFloat dt = 1.0f/60.0f/(cpFloat)steps;
	
	for(int i=0; i<steps; i++){
		cpSpaceStep(space, dt);
	}
}

static cpFloat seg_radius = 3.0f;

static void
make_leg(cpFloat side, cpFloat offset, cpBody *chassis, cpBody *crank, cpVect anchor)
{
	cpVect a, b;
	cpShape *shape;
	
	cpFloat leg_mass = 1.0f;

	// make leg
	a = cpvzero, b = cpv(0.0f, side);
	cpBody *upper_leg = cpBodyNew(leg_mass, cpMomentForSegment(leg_mass, a, b));
	upper_leg->p = cpv(offset, 0.0f);
	cpSpaceAddBody(space, upper_leg);
	cpSpaceAddShape(space, cpSegmentShapeNew(upper_leg, a, b, seg_radius));
	cpSpaceAddConstraint(space, cpPivotJointNew2(chassis, upper_leg, cpv(offset, 0.0f), cpvzero));
	
	// lower leg
	a = cpvzero, b = cpv(0.0f, -1.0f*side);
	cpBody *lower_leg = cpBodyNew(leg_mass, cpMomentForSegment(leg_mass, a, b));
	lower_leg->p = cpv(offset, -side);
	cpSpaceAddBody(space, lower_leg);
	shape = cpSegmentShapeNew(lower_leg, a, b, seg_radius);
	shape->group = 1;
	cpSpaceAddShape(space, shape);
	shape = cpCircleShapeNew(lower_leg, seg_radius*2.0f, b);
	shape->group = 1;
	shape->e = 0.0f; shape->u = 1.0f;
	cpSpaceAddShape(space, shape);
	cpSpaceAddConstraint(space, cpPinJointNew(chassis, lower_leg, cpv(offset, 0.0f), cpvzero));
	
	cpSpaceAddConstraint(space, cpGearJointNew(upper_leg, lower_leg, 0.0f, 1.0f));
	
	cpConstraint *constraint;
	cpFloat diag = cpfsqrt(side*side + offset*offset);
	
	constraint = cpPinJointNew(crank, upper_leg, anchor, cpv(0.0f, side));
	cpPinJointSetDist(constraint, diag);
	cpSpaceAddConstraint(space, constraint);
	constraint = cpPinJointNew(crank, lower_leg, anchor, cpvzero);
	cpPinJointSetDist(constraint, diag);
	cpSpaceAddConstraint(space, constraint);
}

static cpSpace *
init(void)
{
	space = cpSpaceNew();
	
	cpResetShapeIdCounter();
	
	space = cpSpaceNew();
	space->iterations = 20;
	space->gravity = cpv(0,-500);
	
	cpBody *staticBody = &space->staticBody;
	cpShape *shape;
	cpVect a, b;
	
	// Create segments around the edge of the screen.
	shape = cpSegmentShapeNew(staticBody, cpv(-320,-240), cpv(-320,240), 0.0f);
	shape->e = 1.0f; shape->u = 1.0f;
	shape->layers = NOT_GRABABLE_MASK;
	cpSpaceAddShape(space, shape);

	shape = cpSegmentShapeNew(staticBody, cpv(320,-240), cpv(320,240), 0.0f);
	shape->e = 1.0f; shape->u = 1.0f;
	shape->layers = NOT_GRABABLE_MASK;
	cpSpaceAddShape(space, shape);

	shape = cpSegmentShapeNew(staticBody, cpv(-320,-240), cpv(320,-240), 0.0f);
	shape->e = 1.0f; shape->u = 1.0f;
	shape->layers = NOT_GRABABLE_MASK;
	cpSpaceAddShape(space, shape);
	
	cpFloat offset = 30.0f;

	// make chassis
	cpFloat chassis_mass = 2.0f;
	a = cpv(-offset, 0.0f), b = cpv(offset, 0.0f);
	cpBody *chassis = cpBodyNew(chassis_mass, cpMomentForSegment(chassis_mass, a, b));
	cpSpaceAddBody(space, chassis);
	shape = cpSegmentShapeNew(chassis, a, b, seg_radius);
	shape->group = 1;
	cpSpaceAddShape(space, shape);
	
	// make crank
	cpFloat crank_mass = 1.0f;
	cpFloat crank_radius = 13.0f;
	cpBody *crank = cpBodyNew(crank_mass, cpMomentForCircle(crank_mass, crank_radius, 0.0f, cpvzero));
	cpSpaceAddBody(space, crank);
	shape = cpCircleShapeNew(crank, crank_radius, cpvzero);
	shape->group = 1;
	cpSpaceAddShape(space, shape);
	cpSpaceAddConstraint(space, cpPivotJointNew2(chassis, crank, cpvzero, cpvzero));
	
	cpFloat side = 30.0f;
	
	int num_legs = 2;
	for(int i=0; i<num_legs; i++){
		make_leg(side,  offset, chassis, crank, cpvmult(cpvforangle((cpFloat)(2*i+0)/num_legs*(cpFloat)M_PI), crank_radius));
		make_leg(side, -offset, chassis, crank, cpvmult(cpvforangle((cpFloat)(2*i+1)/num_legs*(cpFloat)M_PI), crank_radius));
	}
	
	motor = cpSimpleMotorNew(chassis, crank, 6.0f);
	cpSpaceAddConstraint(space, motor);

	return space;
}

static void
destroy(void)
{
	cpSpaceFreeChildren(space);
	cpSpaceFree(space);
}

chipmunkDemo TheoJansen = {
	"Theo Jansen Machine",
	NULL,
	init,
	update,
	destroy,
};
