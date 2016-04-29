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

/// @defgroup cpDampedSpring cpDampedSpring
/// @{

/// Check if a constraint is a slide joint.
CP_EXPORT cpBool cpConstraintIsDampedSpring(const cpConstraint *constraint);

/// Function type used for damped spring force callbacks.
typedef cpFloat (*cpDampedSpringForceFunc)(cpConstraint *spring, cpFloat dist);

/// Allocate a damped spring.
CP_EXPORT cpDampedSpring* cpDampedSpringAlloc(void);
/// Initialize a damped spring.
CP_EXPORT cpDampedSpring* cpDampedSpringInit(cpDampedSpring *joint, cpBody *a, cpBody *b, cpVect anchorA, cpVect anchorB, cpFloat restLength, cpFloat stiffness, cpFloat damping);
/// Allocate and initialize a damped spring.
CP_EXPORT cpConstraint* cpDampedSpringNew(cpBody *a, cpBody *b, cpVect anchorA, cpVect anchorB, cpFloat restLength, cpFloat stiffness, cpFloat damping);

/// Get the location of the first anchor relative to the first body.
CP_EXPORT cpVect cpDampedSpringGetAnchorA(const cpConstraint *constraint);
/// Set the location of the first anchor relative to the first body.
CP_EXPORT void cpDampedSpringSetAnchorA(cpConstraint *constraint, cpVect anchorA);

/// Get the location of the second anchor relative to the second body.
CP_EXPORT cpVect cpDampedSpringGetAnchorB(const cpConstraint *constraint);
/// Set the location of the second anchor relative to the second body.
CP_EXPORT void cpDampedSpringSetAnchorB(cpConstraint *constraint, cpVect anchorB);

/// Get the rest length of the spring.
CP_EXPORT cpFloat cpDampedSpringGetRestLength(const cpConstraint *constraint);
/// Set the rest length of the spring.
CP_EXPORT void cpDampedSpringSetRestLength(cpConstraint *constraint, cpFloat restLength);

/// Get the stiffness of the spring in force/distance.
CP_EXPORT cpFloat cpDampedSpringGetStiffness(const cpConstraint *constraint);
/// Set the stiffness of the spring in force/distance.
CP_EXPORT void cpDampedSpringSetStiffness(cpConstraint *constraint, cpFloat stiffness);

/// Get the damping of the spring.
CP_EXPORT cpFloat cpDampedSpringGetDamping(const cpConstraint *constraint);
/// Set the damping of the spring.
CP_EXPORT void cpDampedSpringSetDamping(cpConstraint *constraint, cpFloat damping);

/// Get the damping of the spring.
CP_EXPORT cpDampedSpringForceFunc cpDampedSpringGetSpringForceFunc(const cpConstraint *constraint);
/// Set the damping of the spring.
CP_EXPORT void cpDampedSpringSetSpringForceFunc(cpConstraint *constraint, cpDampedSpringForceFunc springForceFunc);

/// @}
