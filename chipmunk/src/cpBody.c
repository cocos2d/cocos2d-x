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
#include <float.h>
#include <stdarg.h>

#include "chipmunk_private.h"

// initialized in cpInitChipmunk()
cpBody cpStaticBodySingleton;

cpBody*
cpBodyAlloc(void)
{
	return (cpBody *)cpmalloc(sizeof(cpBody));
}

cpBodyVelocityFunc cpBodyUpdateVelocityDefault = cpBodyUpdateVelocity;
cpBodyPositionFunc cpBodyUpdatePositionDefault = cpBodyUpdatePosition;

cpBody*
cpBodyInit(cpBody *body, cpFloat m, cpFloat i)
{
	body->velocity_func = cpBodyUpdateVelocityDefault;
	body->position_func = cpBodyUpdatePositionDefault;
	
	cpBodySetMass(body, m);
	cpBodySetMoment(body, i);

	body->p = cpvzero;
	body->v = cpvzero;
	body->f = cpvzero;
	
	cpBodySetAngle(body, 0.0f);
	body->w = 0.0f;
	body->t = 0.0f;
	
	body->v_bias = cpvzero;
	body->w_bias = 0.0f;
	
	body->data = NULL;
	body->v_limit = (cpFloat)INFINITY;
	body->w_limit = (cpFloat)INFINITY;
	
	body->space = NULL;
	body->shapesList = NULL;
	
	cpComponentNode node = {NULL, NULL, 0, 0.0f};
	body->node = node;
	
	return body;
}

cpBody*
cpBodyNew(cpFloat m, cpFloat i)
{
	return cpBodyInit(cpBodyAlloc(), m, i);
}

cpBody *
cpBodyInitStatic(cpBody *body)
{
	cpBodyInit(body, (cpFloat)INFINITY, (cpFloat)INFINITY);
	body->node.idleTime = (cpFloat)INFINITY;
	
	return body;
}

cpBody *
cpBodyNewStatic()
{
	return cpBodyInitStatic(cpBodyAlloc());
}

void cpBodyDestroy(cpBody *body){}

void
cpBodyFree(cpBody *body)
{
	if(body){
		cpBodyDestroy(body);
		cpfree(body);
	}
}

void
cpBodySetMass(cpBody *body, cpFloat mass)
{
	body->m = mass;
	body->m_inv = 1.0f/mass;
}

void
cpBodySetMoment(cpBody *body, cpFloat moment)
{
	body->i = moment;
	body->i_inv = 1.0f/moment;
}

void
cpBodySetAngle(cpBody *body, cpFloat angle)
{
	body->a = angle;//fmod(a, (cpFloat)M_PI*2.0f);
	body->rot = cpvforangle(angle);
}

void
cpBodySlew(cpBody *body, cpVect pos, cpFloat dt)
{
	cpVect delta = cpvsub(pos, body->p);
	body->v = cpvmult(delta, 1.0f/dt);
}

void
cpBodyUpdateVelocity(cpBody *body, cpVect gravity, cpFloat damping, cpFloat dt)
{
	body->v = cpvclamp(cpvadd(cpvmult(body->v, damping), cpvmult(cpvadd(gravity, cpvmult(body->f, body->m_inv)), dt)), body->v_limit);
	
	cpFloat w_limit = body->w_limit;
	body->w = cpfclamp(body->w*damping + body->t*body->i_inv*dt, -w_limit, w_limit);
}

void
cpBodyUpdatePosition(cpBody *body, cpFloat dt)
{
	body->p = cpvadd(body->p, cpvmult(cpvadd(body->v, body->v_bias), dt));
	cpBodySetAngle(body, body->a + (body->w + body->w_bias)*dt);
	
	body->v_bias = cpvzero;
	body->w_bias = 0.0f;
}

void
cpBodyResetForces(cpBody *body)
{
	body->f = cpvzero;
	body->t = 0.0f;
}

void
cpBodyApplyForce(cpBody *body, cpVect force, cpVect r)
{
	body->f = cpvadd(body->f, force);
	body->t += cpvcross(r, force);
}

void
cpApplyDampedSpring(cpBody *a, cpBody *b, cpVect anchr1, cpVect anchr2, cpFloat rlen, cpFloat k, cpFloat dmp, cpFloat dt)
{
	// Calculate the world space anchor coordinates.
	cpVect r1 = cpvrotate(anchr1, a->rot);
	cpVect r2 = cpvrotate(anchr2, b->rot);
	
	cpVect delta = cpvsub(cpvadd(b->p, r2), cpvadd(a->p, r1));
	cpFloat dist = cpvlength(delta);
	cpVect n = dist ? cpvmult(delta, 1.0f/dist) : cpvzero;
	
	cpFloat f_spring = (dist - rlen)*k;

	// Calculate the world relative velocities of the anchor points.
	cpVect v1 = cpvadd(a->v, cpvmult(cpvperp(r1), a->w));
	cpVect v2 = cpvadd(b->v, cpvmult(cpvperp(r2), b->w));
	
	// Calculate the damping force.
	// This really should be in the impulse solver and can produce problems when using large damping values.
	cpFloat vrn = cpvdot(cpvsub(v2, v1), n);
	cpFloat f_damp = vrn*cpfmin(dmp, 1.0f/(dt*(a->m_inv + b->m_inv)));
	
	// Apply!
	cpVect f = cpvmult(n, f_spring + f_damp);
	cpBodyApplyForce(a, f, r1);
	cpBodyApplyForce(b, cpvneg(f), r2);
}
