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

/// @defgroup cpDampedRotarySpring cpDampedRotarySpring
/// @{

/// Check if a constraint is a damped rotary springs.
CP_EXPORT cpBool cpConstraintIsDampedRotarySpring(const cpConstraint *constraint);

/// Function type used for damped rotary spring force callbacks.
typedef cpFloat (*cpDampedRotarySpringTorqueFunc)(struct cpConstraint *spring, cpFloat relativeAngle);

/// Allocate a damped rotary spring.
CP_EXPORT cpDampedRotarySpring* cpDampedRotarySpringAlloc(void);
/// Initialize a damped rotary spring.
CP_EXPORT cpDampedRotarySpring* cpDampedRotarySpringInit(cpDampedRotarySpring *joint, cpBody *a, cpBody *b, cpFloat restAngle, cpFloat stiffness, cpFloat damping);
/// Allocate and initialize a damped rotary spring.
CP_EXPORT cpConstraint* cpDampedRotarySpringNew(cpBody *a, cpBody *b, cpFloat restAngle, cpFloat stiffness, cpFloat damping);

/// Get the rest length of the spring.
CP_EXPORT cpFloat cpDampedRotarySpringGetRestAngle(const cpConstraint *constraint);
/// Set the rest length of the spring.
CP_EXPORT void cpDampedRotarySpringSetRestAngle(cpConstraint *constraint, cpFloat restAngle);

/// Get the stiffness of the spring in force/distance.
CP_EXPORT cpFloat cpDampedRotarySpringGetStiffness(const cpConstraint *constraint);
/// Set the stiffness of the spring in force/distance.
CP_EXPORT void cpDampedRotarySpringSetStiffness(cpConstraint *constraint, cpFloat stiffness);

/// Get the damping of the spring.
CP_EXPORT cpFloat cpDampedRotarySpringGetDamping(const cpConstraint *constraint);
/// Set the damping of the spring.
CP_EXPORT void cpDampedRotarySpringSetDamping(cpConstraint *constraint, cpFloat damping);

/// Get the damping of the spring.
CP_EXPORT cpDampedRotarySpringTorqueFunc cpDampedRotarySpringGetSpringTorqueFunc(const cpConstraint *constraint);
/// Set the damping of the spring.
CP_EXPORT void cpDampedRotarySpringSetSpringTorqueFunc(cpConstraint *constraint, cpDampedRotarySpringTorqueFunc springTorqueFunc);

/// @}
