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
 
#include <float.h>

#include "chipmunk_private.h"
#include "constraints/util.h"

// initialized in cpInitChipmunk()
cpBody cpStaticBodySingleton;

cpBody*
cpBodyAlloc(void)
{
	return (cpBody *)cpcalloc(1, sizeof(cpBody));
}

cpBody *
cpBodyInit(cpBody *body, cpFloat m, cpFloat i)
{
	body->space = NULL;
	body->shapeList = NULL;
	body->arbiterList = NULL;
	body->constraintList = NULL;
	
	body->velocity_func = cpBodyUpdateVelocity;
	body->position_func = cpBodyUpdatePosition;
	
	cpComponentNode node = {NULL, NULL, 0.0f};
	body->node = node;
	
	body->p = cpvzero;
	body->v = cpvzero;
	body->f = cpvzero;
	
	body->w = 0.0f;
	body->t = 0.0f;
	
	body->v_bias = cpvzero;
	body->w_bias = 0.0f;
	
	body->v_limit = (cpFloat)INFINITY;
	body->w_limit = (cpFloat)INFINITY;
	
	body->data = NULL;
	
	// Setters must be called after full initialization so the sanity checks don't assert on garbage data.
	cpBodySetMass(body, m);
	cpBodySetMoment(body, i);
	cpBodySetAngle(body, 0.0f);
	
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
cpBodyNewStatic(void)
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

static void cpv_assert_nan(cpVect v, char *message){cpAssertSoft(v.x == v.x && v.y == v.y, message);}
static void cpv_assert_infinite(cpVect v, char *message){cpAssertSoft(cpfabs(v.x) != INFINITY && cpfabs(v.y) != INFINITY, message);}
static void cpv_assert_sane(cpVect v, char *message){cpv_assert_nan(v, message); cpv_assert_infinite(v, message);}

#ifdef __cplusplus
extern "C" {
#endif

void
cpBodySanityCheck(cpBody *body)
{
	cpAssertSoft(body->m == body->m && body->m_inv == body->m_inv, "Body's mass is invalid.");
	cpAssertSoft(body->i == body->i && body->i_inv == body->i_inv, "Body's moment is invalid.");
	
	cpv_assert_sane(body->p, "Body's position is invalid.");
	cpv_assert_sane(body->v, "Body's velocity is invalid.");
	cpv_assert_sane(body->f, "Body's force is invalid.");

	cpAssertSoft(body->a == body->a && cpfabs(body->a) != INFINITY, "Body's angle is invalid.");
	cpAssertSoft(body->w == body->w && cpfabs(body->w) != INFINITY, "Body's angular velocity is invalid.");
	cpAssertSoft(body->t == body->t && cpfabs(body->t) != INFINITY, "Body's torque is invalid.");
	
	cpv_assert_sane(body->rot, "Body's rotation vector is invalid.");
	
	cpAssertSoft(body->v_limit == body->v_limit, "Body's velocity limit is invalid.");
	cpAssertSoft(body->w_limit == body->w_limit, "Body's angular velocity limit is invalid.");
}

#ifdef __cplusplus
}
#endif

void
cpBodySetMass(cpBody *body, cpFloat mass)
{
	cpAssertHard(mass > 0.0f, "Mass must be positive and non-zero.");
	
	cpBodyActivate(body);
	body->m = mass;
	body->m_inv = 1.0f/mass;
	cpBodyAssertSane(body);
}

void
cpBodySetMoment(cpBody *body, cpFloat moment)
{
	cpAssertHard(moment > 0.0f, "Moment of Inertia must be positive and non-zero.");
	
	cpBodyActivate(body);
	body->i = moment;
	body->i_inv = 1.0f/moment;
	cpBodyAssertSane(body);
}

void
cpBodyAddShape(cpBody *body, cpShape *shape)
{
	cpShape *next = body->shapeList;
	if(next) next->prev = shape;
	
	shape->next = next;
	body->shapeList = shape;
}

void
cpBodyRemoveShape(cpBody *body, cpShape *shape)
{
  cpShape *prev = shape->prev;
  cpShape *next = shape->next;
  
  if(prev){
		prev->next = next;
  } else {
		body->shapeList = next;
  }
  
  if(next){
		next->prev = prev;
	}
  
  shape->prev = NULL;
  shape->next = NULL;
}

static cpConstraint *
filterConstraints(cpConstraint *node, cpBody *body, cpConstraint *filter)
{
	if(node == filter){
		return cpConstraintNext(node, body);
	} else if(node->a == body){
		node->next_a = filterConstraints(node->next_a, body, filter);
	} else {
		node->next_b = filterConstraints(node->next_b, body, filter);
	}
	
	return node;
}

void
cpBodyRemoveConstraint(cpBody *body, cpConstraint *constraint)
{
	body->constraintList = filterConstraints(body->constraintList, body, constraint);
}

void
cpBodySetPos(cpBody *body, cpVect pos)
{
	cpBodyActivate(body);
	body->p = pos;
	cpBodyAssertSane(body);
}

static inline void
setAngle(cpBody *body, cpFloat angle)
{
	body->a = angle;//fmod(a, (cpFloat)M_PI*2.0f);
	body->rot = cpvforangle(angle);
	cpBodyAssertSane(body);
}

void
cpBodySetAngle(cpBody *body, cpFloat angle)
{
	cpBodyActivate(body);
	setAngle(body, angle);
}

void
cpBodyUpdateVelocity(cpBody *body, cpVect gravity, cpFloat damping, cpFloat dt)
{
	body->v = cpvclamp(cpvadd(cpvmult(body->v, damping), cpvmult(cpvadd(gravity, cpvmult(body->f, body->m_inv)), dt)), body->v_limit);
	
	cpFloat w_limit = body->w_limit;
	body->w = cpfclamp(body->w*damping + body->t*body->i_inv*dt, -w_limit, w_limit);
	
	cpBodySanityCheck(body);
}

void
cpBodyUpdatePosition(cpBody *body, cpFloat dt)
{
	body->p = cpvadd(body->p, cpvmult(cpvadd(body->v, body->v_bias), dt));
	setAngle(body, body->a + (body->w + body->w_bias)*dt);
	
	body->v_bias = cpvzero;
	body->w_bias = 0.0f;
	
	cpBodySanityCheck(body);
}

void
cpBodyResetForces(cpBody *body)
{
	cpBodyActivate(body);
	body->f = cpvzero;
	body->t = 0.0f;
}

void
cpBodyApplyForce(cpBody *body, cpVect force, cpVect r)
{
	cpBodyActivate(body);
	body->f = cpvadd(body->f, force);
	body->t += cpvcross(r, force);
}

void
cpBodyApplyImpulse(cpBody *body, const cpVect j, const cpVect r)
{
	cpBodyActivate(body);
	apply_impulse(body, j, r);
}

static inline cpVect
cpBodyGetVelAtPoint(cpBody *body, cpVect r)
{
	return cpvadd(body->v, cpvmult(cpvperp(r), body->w));
}

cpVect
cpBodyGetVelAtWorldPoint(cpBody *body, cpVect point)
{
	return cpBodyGetVelAtPoint(body, cpvsub(point, body->p));
}

cpVect
cpBodyGetVelAtLocalPoint(cpBody *body, cpVect point)
{
	return cpBodyGetVelAtPoint(body, cpvrotate(point, body->rot));
}

void
cpBodyEachShape(cpBody *body, cpBodyShapeIteratorFunc func, void *data)
{
	cpShape *shape = body->shapeList;
	while(shape){
		cpShape *next = shape->next;
		func(body, shape, data);
		shape = next;
	}
}

void
cpBodyEachConstraint(cpBody *body, cpBodyConstraintIteratorFunc func, void *data)
{
	cpConstraint *constraint = body->constraintList;
	while(constraint){
		cpConstraint *next = cpConstraintNext(constraint, body);
		func(body, constraint, data);
		constraint = next;
	}
}

void
cpBodyEachArbiter(cpBody *body, cpBodyArbiterIteratorFunc func, void *data)
{
	cpArbiter *arb = body->arbiterList;
	while(arb){
		cpArbiter *next = cpArbiterNext(arb, body);
		
		arb->swappedColl = (body == arb->body_b);
		func(body, arb, data);
		
		arb = next;
	}
}
