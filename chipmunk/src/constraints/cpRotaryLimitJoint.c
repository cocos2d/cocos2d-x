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
preStep(cpRotaryLimitJoint *joint, cpFloat dt, cpFloat dt_inv)
{
	CONSTRAINT_BEGIN(joint, a, b);
	
	cpFloat dist = b->a - a->a;
	cpFloat pdist = 0.0f;
	if(dist > joint->max) {
		pdist = joint->max - dist;
	} else if(dist < joint->min) {
		pdist = joint->min - dist;
	}
	
	// calculate moment of inertia coefficient.
	joint->iSum = 1.0f/(a->i_inv + b->i_inv);
	
	// calculate bias velocity
	cpFloat maxBias = joint->constraint.maxBias;
	joint->bias = cpfclamp(-joint->constraint.biasCoef*dt_inv*(pdist), -maxBias, maxBias);
	
	// compute max impulse
	joint->jMax = J_MAX(joint, dt);

	// If the bias is 0, the joint is not at a limit. Reset the impulse.
	if(!joint->bias)
		joint->jAcc = 0.0f;

	// apply joint torque
	a->w -= joint->jAcc*a->i_inv;
	b->w += joint->jAcc*b->i_inv;
}

static void
applyImpulse(cpRotaryLimitJoint *joint)
{
	if(!joint->bias) return; // early exit

	CONSTRAINT_BEGIN(joint, a, b);
	
	// compute relative rotational velocity
	cpFloat wr = b->w - a->w;
	
	// compute normal impulse	
	cpFloat j = -(joint->bias + wr)*joint->iSum;
	cpFloat jOld = joint->jAcc;
	if(joint->bias < 0.0f){
		joint->jAcc = cpfclamp(jOld + j, 0.0f, joint->jMax);
	} else {
		joint->jAcc = cpfclamp(jOld + j, -joint->jMax, 0.0f);
	}
	j = joint->jAcc - jOld;
	
	// apply impulse
	a->w -= j*a->i_inv;
	b->w += j*b->i_inv;
}

static cpFloat
getImpulse(cpRotaryLimitJoint *joint)
{
	return cpfabs(joint->jAcc);
}

static const cpConstraintClass klass = {
	(cpConstraintPreStepFunction)preStep,
	(cpConstraintApplyImpulseFunction)applyImpulse,
	(cpConstraintGetImpulseFunction)getImpulse,
};
CP_DefineClassGetter(cpRotaryLimitJoint)

cpRotaryLimitJoint *
cpRotaryLimitJointAlloc(void)
{
	return (cpRotaryLimitJoint *)cpcalloc(1, sizeof(cpRotaryLimitJoint));
}

cpRotaryLimitJoint *
cpRotaryLimitJointInit(cpRotaryLimitJoint *joint, cpBody *a, cpBody *b, cpFloat min, cpFloat max)
{
	cpConstraintInit((cpConstraint *)joint, &klass, a, b);
	
	joint->min = min;
	joint->max  = max;
	
	joint->jAcc = 0.0f;
	
	return joint;
}

cpConstraint *
cpRotaryLimitJointNew(cpBody *a, cpBody *b, cpFloat min, cpFloat max)
{
	return (cpConstraint *)cpRotaryLimitJointInit(cpRotaryLimitJointAlloc(), a, b, min, max);
}
