/* Copyright (c) 2013 Scott Lembcke and Howling Moon Software
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

/// Callback function type that gets called before solving a joint.
typedef void (*cpConstraintPreSolveFunc)(cpConstraint *constraint, cpSpace *space);
/// Callback function type that gets called after solving a joint.
typedef void (*cpConstraintPostSolveFunc)(cpConstraint *constraint, cpSpace *space);

/// Destroy a constraint.
CP_EXPORT void cpConstraintDestroy(cpConstraint *constraint);
/// Destroy and free a constraint.
CP_EXPORT void cpConstraintFree(cpConstraint *constraint);

/// Get the cpSpace this constraint is added to.
CP_EXPORT cpSpace* cpConstraintGetSpace(const cpConstraint *constraint);

/// Get the first body the constraint is attached to.
CP_EXPORT cpBody* cpConstraintGetBodyA(const cpConstraint *constraint);

/// Get the second body the constraint is attached to.
CP_EXPORT cpBody* cpConstraintGetBodyB(const cpConstraint *constraint);

/// Get the maximum force that this constraint is allowed to use.
CP_EXPORT cpFloat cpConstraintGetMaxForce(const cpConstraint *constraint);
/// Set the maximum force that this constraint is allowed to use. (defaults to INFINITY)
CP_EXPORT void cpConstraintSetMaxForce(cpConstraint *constraint, cpFloat maxForce);

/// Get rate at which joint error is corrected.
CP_EXPORT cpFloat cpConstraintGetErrorBias(const cpConstraint *constraint);
/// Set rate at which joint error is corrected.
/// Defaults to pow(1.0 - 0.1, 60.0) meaning that it will
/// correct 10% of the error every 1/60th of a second.
CP_EXPORT void cpConstraintSetErrorBias(cpConstraint *constraint, cpFloat errorBias);

/// Get the maximum rate at which joint error is corrected.
CP_EXPORT cpFloat cpConstraintGetMaxBias(const cpConstraint *constraint);
/// Set the maximum rate at which joint error is corrected. (defaults to INFINITY)
CP_EXPORT void cpConstraintSetMaxBias(cpConstraint *constraint, cpFloat maxBias);

/// Get if the two bodies connected by the constraint are allowed to collide or not.
CP_EXPORT cpBool cpConstraintGetCollideBodies(const cpConstraint *constraint);
/// Set if the two bodies connected by the constraint are allowed to collide or not. (defaults to cpFalse)
CP_EXPORT void cpConstraintSetCollideBodies(cpConstraint *constraint, cpBool collideBodies);

/// Get the pre-solve function that is called before the solver runs.
CP_EXPORT cpConstraintPreSolveFunc cpConstraintGetPreSolveFunc(const cpConstraint *constraint);
/// Set the pre-solve function that is called before the solver runs.
CP_EXPORT void cpConstraintSetPreSolveFunc(cpConstraint *constraint, cpConstraintPreSolveFunc preSolveFunc);

/// Get the post-solve function that is called before the solver runs.
CP_EXPORT cpConstraintPostSolveFunc cpConstraintGetPostSolveFunc(const cpConstraint *constraint);
/// Set the post-solve function that is called before the solver runs.
CP_EXPORT void cpConstraintSetPostSolveFunc(cpConstraint *constraint, cpConstraintPostSolveFunc postSolveFunc);

/// Get the user definable data pointer for this constraint
CP_EXPORT cpDataPointer cpConstraintGetUserData(const cpConstraint *constraint);
/// Set the user definable data pointer for this constraint
CP_EXPORT void cpConstraintSetUserData(cpConstraint *constraint, cpDataPointer userData);

/// Get the last impulse applied by this constraint.
CP_EXPORT cpFloat cpConstraintGetImpulse(cpConstraint *constraint);

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

///@}
