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

#include "chipmunk_private.h"
#include "constraints/util.h"

static void
preStep(cpGrooveJoint *joint, cpFloat dt, cpFloat dt_inv)
{
	CONSTRAINT_BEGIN(joint, a, b);
	
	// calculate endpoints in worldspace
	cpVect ta = cpBodyLocal2World(a, joint->grv_a);
	cpVect tb = cpBodyLocal2World(a, joint->grv_b);

	// calculate axis
	cpVect n = cpvrotate(joint->grv_n, a->rot);
	cpFloat d = cpvdot(ta, n);
	
	joint->grv_tn = n;
	joint->r2 = cpvrotate(joint->anchr2, b->rot);
	
	// calculate tangential distance along the axis of r2
	cpFloat td = cpvcross(cpvadd(b->p, joint->r2), n);
	// calculate clamping factor and r2
	if(td <= cpvcross(ta, n)){
		joint->clamp = 1.0f;
		joint->r1 = cpvsub(ta, a->p);
	} else if(td >= cpvcross(tb, n)){
		joint->clamp = -1.0f;
		joint->r1 = cpvsub(tb, a->p);
	} else {
		joint->clamp = 0.0f;
		joint->r1 = cpvsub(cpvadd(cpvmult(cpvperp(n), -td), cpvmult(n, d)), a->p);
	}
	
	// Calculate mass tensor
	k_tensor(a, b, joint->r1, joint->r2, &joint->k1, &joint->k2);	
	
	// compute max impulse
	joint->jMaxLen = J_MAX(joint, dt);
	
	// calculate bias velocity
	cpVect delta = cpvsub(cpvadd(b->p, joint->r2), cpvadd(a->p, joint->r1));
	joint->bias = cpvclamp(cpvmult(delta, -joint->constraint.biasCoef*dt_inv), joint->constraint.maxBias);
	
	// apply accumulated impulse
	apply_impulses(a, b, joint->r1, joint->r2, joint->jAcc);
}

static inline cpVect
grooveConstrain(cpGrooveJoint *joint, cpVect j){
	cpVect n = joint->grv_tn;
	cpVect jClamp = (joint->clamp*cpvcross(j, n) > 0.0f) ? j : cpvproject(j, n);
	return cpvclamp(jClamp, joint->jMaxLen);
}

static void
applyImpulse(cpGrooveJoint *joint)
{
	CONSTRAINT_BEGIN(joint, a, b);
	
	cpVect r1 = joint->r1;
	cpVect r2 = joint->r2;
	
	// compute impulse
	cpVect vr = relative_velocity(a, b, r1, r2);

	cpVect j = mult_k(cpvsub(joint->bias, vr), joint->k1, joint->k2);
	cpVect jOld = joint->jAcc;
	joint->jAcc = grooveConstrain(joint, cpvadd(jOld, j));
	j = cpvsub(joint->jAcc, jOld);
	
	// apply impulse
	apply_impulses(a, b, joint->r1, joint->r2, j);
}

static cpFloat
getImpulse(cpGrooveJoint *joint)
{
	return cpvlength(joint->jAcc);
}

static const cpConstraintClass klass = {
	(cpConstraintPreStepFunction)preStep,
	(cpConstraintApplyImpulseFunction)applyImpulse,
	(cpConstraintGetImpulseFunction)getImpulse,
};
CP_DefineClassGetter(cpGrooveJoint)

cpGrooveJoint *
cpGrooveJointAlloc(void)
{
	return (cpGrooveJoint *)cpmalloc(sizeof(cpGrooveJoint));
}

cpGrooveJoint *
cpGrooveJointInit(cpGrooveJoint *joint, cpBody *a, cpBody *b, cpVect groove_a, cpVect groove_b, cpVect anchr2)
{
	cpConstraintInit((cpConstraint *)joint, &klass, a, b);
	
	joint->grv_a = groove_a;
	joint->grv_b = groove_b;
	joint->grv_n = cpvperp(cpvnormalize(cpvsub(groove_b, groove_a)));
	joint->anchr2 = anchr2;
	
	joint->jAcc = cpvzero;
	
	return joint;
}

cpConstraint *
cpGrooveJointNew(cpBody *a, cpBody *b, cpVect groove_a, cpVect groove_b, cpVect anchr2)
{
	return (cpConstraint *)cpGrooveJointInit(cpGrooveJointAlloc(), a, b, groove_a, groove_b, anchr2);
}

void
cpGrooveJointSetGrooveA(cpConstraint *constraint, cpVect value)
{
	cpGrooveJoint *g = (cpGrooveJoint *)constraint;
	cpConstraintCheckCast(constraint, cpGrooveJoint);
	
	g->grv_a = value;
	g->grv_n = cpvperp(cpvnormalize(cpvsub(g->grv_b, value)));
	
	cpConstraintActivateBodies(constraint);
}

void
cpGrooveJointSetGrooveB(cpConstraint *constraint, cpVect value)
{
	cpGrooveJoint *g = (cpGrooveJoint *)constraint;
	cpConstraintCheckCast(constraint, cpGrooveJoint);
	
	g->grv_b = value;
	g->grv_n = cpvperp(cpvnormalize(cpvsub(value, g->grv_a)));
	
	cpConstraintActivateBodies(constraint);
}

