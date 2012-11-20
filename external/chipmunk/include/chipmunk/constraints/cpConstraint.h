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

/// @defgroup cpConstraint cpConstraint
/// @{

typedef struct cpConstraintClass cpConstraintClass;

typedef void (*cpConstraintPreStepImpl)(cpConstraint *constraint, cpFloat dt);
typedef void (*cpConstraintApplyCachedImpulseImpl)(cpConstraint *constraint, cpFloat dt_coef);
typedef void (*cpConstraintApplyImpulseImpl)(cpConstraint *constraint, cpFloat dt);
typedef cpFloat (*cpConstraintGetImpulseImpl)(cpConstraint *constraint);

/// @private
struct cpConstraintClass {
	cpConstraintPreStepImpl preStep;
	cpConstraintApplyCachedImpulseImpl applyCachedImpulse;
	cpConstraintApplyImpulseImpl applyImpulse;
	cpConstraintGetImpulseImpl getImpulse;
};

/// Callback function type that gets called before solving a joint.
typedef void (*cpConstraintPreSolveFunc)(cpConstraint *constraint, cpSpace *space);
/// Callback function type that gets called after solving a joint.
typedef void (*cpConstraintPostSolveFunc)(cpConstraint *constraint, cpSpace *space);


/// Opaque cpConstraint struct.
struct cpConstraint {
	CP_PRIVATE(const cpConstraintClass *klass);
	
	/// The first body connected to this constraint.
	cpBody *a;
	/// The second body connected to this constraint.
	cpBody *b;
	
	CP_PRIVATE(cpSpace *space);
	
	CP_PRIVATE(cpConstraint *next_a);
	CP_PRIVATE(cpConstraint *next_b);
	
	/// The maximum force that this constraint is allowed to use.
	/// Defaults to infinity.
	cpFloat maxForce;
	/// The rate at which joint error is corrected.
	/// Defaults to pow(1.0 - 0.1, 60.0) meaning that it will
	/// correct 10% of the error every 1/60th of a second.
	cpFloat errorBias;
	/// The maximum rate at which joint error is corrected.
	/// Defaults to infinity.
	cpFloat maxBias;
	
	/// Function called before the solver runs.
	/// Animate your joint anchors, update your motor torque, etc.
	cpConstraintPreSolveFunc preSolve;
	
	/// Function called after the solver runs.
	/// Use the applied impulse to perform effects like breakable joints.
	cpConstraintPostSolveFunc postSolve;
	
	/// User definable data pointer.
	/// Generally this points to your the game object class so you can access it
	/// when given a cpConstraint reference in a callback.
	cpDataPointer data;
};

/// Destroy a constraint.
void cpConstraintDestroy(cpConstraint *constraint);
/// Destroy and free a constraint.
void cpConstraintFree(cpConstraint *constraint);

/// @private
static inline void cpConstraintActivateBodies(cpConstraint *constraint)
{
	cpBody *a = constraint->a; if(a) cpBodyActivate(a);
	cpBody *b = constraint->b; if(b) cpBodyActivate(b);
}

/// @private
#define CP_DefineConstraintStructGetter(type, member, name) \
static inline type cpConstraint##Get##name(const cpConstraint *constraint){return constraint->member;}

/// @private
#define CP_DefineConstraintStructSetter(type, member, name) \
static inline void cpConstraint##Set##name(cpConstraint *constraint, type value){ \
	cpConstraintActivateBodies(constraint); \
	constraint->member = value; \
}

/// @private
#define CP_DefineConstraintStructProperty(type, member, name) \
CP_DefineConstraintStructGetter(type, member, name) \
CP_DefineConstraintStructSetter(type, member, name)

CP_DefineConstraintStructGetter(cpSpace*, CP_PRIVATE(space), Space)

CP_DefineConstraintStructGetter(cpBody*, a, A)
CP_DefineConstraintStructGetter(cpBody*, b, B)
CP_DefineConstraintStructProperty(cpFloat, maxForce, MaxForce)
CP_DefineConstraintStructProperty(cpFloat, errorBias, ErrorBias)
CP_DefineConstraintStructProperty(cpFloat, maxBias, MaxBias)
CP_DefineConstraintStructProperty(cpConstraintPreSolveFunc, preSolve, PreSolveFunc)
CP_DefineConstraintStructProperty(cpConstraintPostSolveFunc, postSolve, PostSolveFunc)
CP_DefineConstraintStructProperty(cpDataPointer, data, UserData)

// Get the last impulse applied by this constraint.
static inline cpFloat cpConstraintGetImpulse(cpConstraint *constraint)
{
	return constraint->CP_PRIVATE(klass)->getImpulse(constraint);
}

/// @}

#define cpConstraintCheckCast(constraint, struct) \
	cpAssertHard(constraint->CP_PRIVATE(klass) == struct##GetClass(), "Constraint is not a "#struct)

#define CP_DefineConstraintGetter(struct, type, member, name) \
static inline type struct##Get##name(const cpConstraint *constraint){ \
	cpConstraintCheckCast(constraint, struct); \
	return ((struct *)constraint)->member; \
}

#define CP_DefineConstraintSetter(struct, type, member, name) \
static inline void struct##Set##name(cpConstraint *constraint, type value){ \
	cpConstraintCheckCast(constraint, struct); \
	cpConstraintActivateBodies(constraint); \
	((struct *)constraint)->member = value; \
}

#define CP_DefineConstraintProperty(struct, type, member, name) \
CP_DefineConstraintGetter(struct, type, member, name) \
CP_DefineConstraintSetter(struct, type, member, name)

#include "cpPinJoint.h"
#include "cpSlideJoint.h"
#include "cpPivotJoint.h"
#include "cpGrooveJoint.h"
#include "cpDampedSpring.h"
#include "cpDampedRotarySpring.h"
#include "cpRotaryLimitJoint.h"
#include "cpRatchetJoint.h"
#include "cpGearJoint.h"
#include "cpSimpleMotor.h"
