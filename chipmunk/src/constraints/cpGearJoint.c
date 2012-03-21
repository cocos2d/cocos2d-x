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
#include <math.h>

#include "chipmunk_private.h"
#include "constraints/util.h"

static void
preStep(cpGearJoint *joint, cpFloat dt)
{
	cpBody *a = joint->constraint.a;
	cpBody *b = joint->constraint.b;
	
	// calculate moment of inertia coefficient.
	joint->iSum = 1.0f/(a->i_inv*joint->ratio_inv + joint->ratio*b->i_inv);
	
	// calculate bias velocity
	cpFloat maxBias = joint->constraint.maxBias;
	joint->bias = cpfclamp(-bias_coef(joint->constraint.errorBias, dt)*(b->a*joint->ratio - a->a - joint->phase)/dt, -maxBias, maxBias);
	
	// compute max impulse
	joint->jMax = J_MAX(joint, dt);
}

static void
applyCachedImpulse(cpGearJoint *joint, cpFloat dt_coef)
{
	cpBody *a = joint->constraint.a;
	cpBody *b = joint->constraint.b;
	
	cpFloat j = joint->jAcc*dt_coef;
	a->w -= j*a->i_inv*joint->ratio_inv;
	b->w += j*b->i_inv;
}

static void
applyImpulse(cpGearJoint *joint)
{
	cpBody *a = joint->constraint.a;
	cpBody *b = joint->constraint.b;
	
	// compute relative rotational velocity
	cpFloat wr = b->w*joint->ratio - a->w;
	
	// compute normal impulse	
	cpFloat j = (joint->bias - wr)*joint->iSum;
	cpFloat jOld = joint->jAcc;
	joint->jAcc = cpfclamp(jOld + j, -joint->jMax, joint->jMax);
	j = joint->jAcc - jOld;
	
	// apply impulse
	a->w -= j*a->i_inv*joint->ratio_inv;
	b->w += j*b->i_inv;
}

static cpFloat
getImpulse(cpGearJoint *joint)
{
	return cpfabs(joint->jAcc);
}

static const cpConstraintClass klass = {
	(cpConstraintPreStepImpl)preStep,
	(cpConstraintApplyCachedImpulseImpl)applyCachedImpulse,
	(cpConstraintApplyImpulseImpl)applyImpulse,
	(cpConstraintGetImpulseImpl)getImpulse,
};
CP_DefineClassGetter(cpGearJoint)

cpGearJoint *
cpGearJointAlloc(void)
{
	return (cpGearJoint *)cpcalloc(1, sizeof(cpGearJoint));
}

cpGearJoint *
cpGearJointInit(cpGearJoint *joint, cpBody *a, cpBody *b, cpFloat phase, cpFloat ratio)
{
	cpConstraintInit((cpConstraint *)joint, &klass, a, b);
	
	joint->phase = phase;
	joint->ratio = ratio;
	joint->ratio_inv = 1.0f/ratio;
	
	joint->jAcc = 0.0f;
	
	return joint;
}

cpConstraint *
cpGearJointNew(cpBody *a, cpBody *b, cpFloat phase, cpFloat ratio)
{
	return (cpConstraint *)cpGearJointInit(cpGearJointAlloc(), a, b, phase, ratio);
}

void
cpGearJointSetRatio(cpConstraint *constraint, cpFloat value)
{
	cpConstraintCheckCast(constraint, cpGearJoint);
	((cpGearJoint *)constraint)->ratio = value;
	((cpGearJoint *)constraint)->ratio_inv = 1.0f/value;
	cpConstraintActivateBodies(constraint);
}
