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

static cpSpace *space;

static cpFloat
springForce(cpConstraint *spring, cpFloat dist)
{
	cpFloat clamp = 20.0f;
	return cpfclamp(cpDampedSpringGetRestLength(spring) - dist, -clamp, clamp)*cpDampedSpringGetStiffness(spring);
}

static cpConstraint *
new_spring(cpBody *a, cpBody *b, cpVect anchr1, cpVect anchr2, cpFloat restLength, cpFloat stiff, cpFloat damp)
{
	cpConstraint *spring = cpDampedSpringNew(a, b, anchr1, anchr2, restLength, stiff, damp);
	cpDampedSpringSetSpringForceFunc(spring, springForce);
	
	return spring;
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

static cpBody *
add_bar(cpVect a, cpVect b, int group)
{
	cpVect center = cpvmult(cpvadd(a, b), 1.0f/2.0f);
	cpFloat length = cpvlength(cpvsub(b, a));
	cpFloat mass = length/160.0f;
	
	cpBody *body = cpSpaceAddBody(space, cpBodyNew(mass, mass*length*length/12.0f));
	body->p = center;
	
	cpShape *shape = cpSpaceAddShape(space, cpSegmentShapeNew(body, cpvsub(a, center), cpvsub(b, center), 10.0f));
	shape->group = group;
	
	return body;
}

static cpSpace *
init(void)
{
	space = cpSpaceNew();
	cpBody *staticBody = &space->staticBody;
	
	cpBody *body1  = add_bar(cpv(-240,  160), cpv(-160,   80), 1);
	cpBody *body2  = add_bar(cpv(-160,   80), cpv( -80,  160), 1);
	cpBody *body3  = add_bar(cpv(   0,  160), cpv(  80,    0), 0);
	cpBody *body4  = add_bar(cpv( 160,  160), cpv( 240,  160), 0);
	cpBody *body5  = add_bar(cpv(-240,    0), cpv(-160,  -80), 2);
	cpBody *body6  = add_bar(cpv(-160,  -80), cpv( -80,    0), 2);
	cpBody *body7  = add_bar(cpv( -80,    0), cpv(   0,    0), 2);
	cpBody *body8  = add_bar(cpv(   0,  -80), cpv(  80,  -80), 0);
	cpBody *body9  = add_bar(cpv( 240,   80), cpv( 160,    0), 3);
	cpBody *body10 = add_bar(cpv( 160,    0), cpv( 240,  -80), 3);
	cpBody *body11 = add_bar(cpv(-240,  -80), cpv(-160, -160), 4);
	cpBody *body12 = add_bar(cpv(-160, -160), cpv( -80, -160), 0);
	cpBody *body13 = add_bar(cpv(   0, -160), cpv(  80, -160), 0);
	cpBody *body14 = add_bar(cpv( 160, -160), cpv( 240, -160), 0);
	
	cpSpaceAddConstraint(space, cpPivotJointNew2( body1,  body2, cpv( 40,-40), cpv(-40,-40)));
	cpSpaceAddConstraint(space, cpPivotJointNew2( body5,  body6, cpv( 40,-40), cpv(-40,-40)));
	cpSpaceAddConstraint(space, cpPivotJointNew2( body6,  body7, cpv( 40, 40), cpv(-40,  0)));
	cpSpaceAddConstraint(space, cpPivotJointNew2( body9, body10, cpv(-40,-40), cpv(-40, 40)));
	cpSpaceAddConstraint(space, cpPivotJointNew2(body11, body12, cpv( 40,-40), cpv(-40,  0)));
	
	cpFloat stiff = 100.0f;
	cpFloat damp = 0.5f;
	cpSpaceAddConstraint(space, new_spring(staticBody,  body1, cpv(-320,  240), cpv(-40, 40), 0.0f, stiff, damp));
	cpSpaceAddConstraint(space, new_spring(staticBody,  body1, cpv(-320,   80), cpv(-40, 40), 0.0f, stiff, damp));
	cpSpaceAddConstraint(space, new_spring(staticBody,  body1, cpv(-160,  240), cpv(-40, 40), 0.0f, stiff, damp));

	cpSpaceAddConstraint(space, new_spring(staticBody,  body2, cpv(-160,  240), cpv( 40, 40), 0.0f, stiff, damp));
	cpSpaceAddConstraint(space, new_spring(staticBody,  body2, cpv(   0,  240), cpv( 40, 40), 0.0f, stiff, damp));

	cpSpaceAddConstraint(space, new_spring(staticBody,  body3, cpv(  80,  240), cpv(-40, 80), 0.0f, stiff, damp));

	cpSpaceAddConstraint(space, new_spring(staticBody,  body4, cpv(  80,  240), cpv(-40,  0), 0.0f, stiff, damp));
	cpSpaceAddConstraint(space, new_spring(staticBody,  body4, cpv( 320,  240), cpv( 40,  0), 0.0f, stiff, damp));

	cpSpaceAddConstraint(space, new_spring(staticBody,  body5, cpv(-320,   80), cpv(-40, 40), 0.0f, stiff, damp));
	
	cpSpaceAddConstraint(space, new_spring(staticBody,  body9, cpv( 320,  80), cpv( 40, 40), 0.0f, stiff, damp));

	cpSpaceAddConstraint(space, new_spring(staticBody, body10, cpv( 320,   0), cpv( 40,-40), 0.0f, stiff, damp));
	cpSpaceAddConstraint(space, new_spring(staticBody, body10, cpv( 320,-160), cpv( 40,-40), 0.0f, stiff, damp));

	cpSpaceAddConstraint(space, new_spring(staticBody, body11, cpv(-320,-160), cpv(-40, 40), 0.0f, stiff, damp));

	cpSpaceAddConstraint(space, new_spring(staticBody, body12, cpv(-240,-240), cpv(-40,  0), 0.0f, stiff, damp));
	cpSpaceAddConstraint(space, new_spring(staticBody, body12, cpv(   0,-240), cpv( 40,  0), 0.0f, stiff, damp));

	cpSpaceAddConstraint(space, new_spring(staticBody, body13, cpv(   0,-240), cpv(-40,  0), 0.0f, stiff, damp));
	cpSpaceAddConstraint(space, new_spring(staticBody, body13, cpv(  80,-240), cpv( 40,  0), 0.0f, stiff, damp));

	cpSpaceAddConstraint(space, new_spring(staticBody, body14, cpv(  80,-240), cpv(-40,  0), 0.0f, stiff, damp));
	cpSpaceAddConstraint(space, new_spring(staticBody, body14, cpv( 240,-240), cpv( 40,  0), 0.0f, stiff, damp));
	cpSpaceAddConstraint(space, new_spring(staticBody, body14, cpv( 320,-160), cpv( 40,  0), 0.0f, stiff, damp));

	cpSpaceAddConstraint(space, new_spring( body1,  body5, cpv( 40,-40), cpv(-40, 40), 0.0f, stiff, damp));
	cpSpaceAddConstraint(space, new_spring( body1,  body6, cpv( 40,-40), cpv( 40, 40), 0.0f, stiff, damp));
	cpSpaceAddConstraint(space, new_spring( body2,  body3, cpv( 40, 40), cpv(-40, 80), 0.0f, stiff, damp));
	cpSpaceAddConstraint(space, new_spring( body3,  body4, cpv(-40, 80), cpv(-40,  0), 0.0f, stiff, damp));
	cpSpaceAddConstraint(space, new_spring( body3,  body4, cpv( 40,-80), cpv(-40,  0), 0.0f, stiff, damp));
	cpSpaceAddConstraint(space, new_spring( body3,  body7, cpv( 40,-80), cpv( 40,  0), 0.0f, stiff, damp));
	cpSpaceAddConstraint(space, new_spring( body3,  body7, cpv(-40, 80), cpv(-40,  0), 0.0f, stiff, damp));
	cpSpaceAddConstraint(space, new_spring( body3,  body8, cpv( 40,-80), cpv( 40,  0), 0.0f, stiff, damp));
	cpSpaceAddConstraint(space, new_spring( body3,  body9, cpv( 40,-80), cpv(-40,-40), 0.0f, stiff, damp));
	cpSpaceAddConstraint(space, new_spring( body4,  body9, cpv( 40,  0), cpv( 40, 40), 0.0f, stiff, damp));
	cpSpaceAddConstraint(space, new_spring( body5, body11, cpv(-40, 40), cpv(-40, 40), 0.0f, stiff, damp));
	cpSpaceAddConstraint(space, new_spring( body5, body11, cpv( 40,-40), cpv( 40,-40), 0.0f, stiff, damp));
	cpSpaceAddConstraint(space, new_spring( body7,  body8, cpv( 40,  0), cpv(-40,  0), 0.0f, stiff, damp));
	cpSpaceAddConstraint(space, new_spring( body8, body12, cpv(-40,  0), cpv( 40,  0), 0.0f, stiff, damp));
	cpSpaceAddConstraint(space, new_spring( body8, body13, cpv(-40,  0), cpv(-40,  0), 0.0f, stiff, damp));
	cpSpaceAddConstraint(space, new_spring( body8, body13, cpv( 40,  0), cpv( 40,  0), 0.0f, stiff, damp));
	cpSpaceAddConstraint(space, new_spring( body8, body14, cpv( 40,  0), cpv(-40,  0), 0.0f, stiff, damp));
	cpSpaceAddConstraint(space, new_spring(body10, body14, cpv( 40,-40), cpv(-40,  0), 0.0f, stiff, damp));
	cpSpaceAddConstraint(space, new_spring(body10, body14, cpv( 40,-40), cpv(-40,  0), 0.0f, stiff, damp));
	
	return space;
}

static void
destroy(void)
{
	cpSpaceFreeChildren(space);
	cpSpaceFree(space);
}

chipmunkDemo Springies = {
	"Springies",
	NULL,
	init,
	update,
	destroy,
};
