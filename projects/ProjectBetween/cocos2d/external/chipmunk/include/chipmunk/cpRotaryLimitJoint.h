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

/// @defgroup cpRotaryLimitJoint cpRotaryLimitJoint
/// @{

/// Check if a constraint is a damped rotary springs.
CP_EXPORT cpBool cpConstraintIsRotaryLimitJoint(const cpConstraint *constraint);

/// Allocate a damped rotary limit joint.
CP_EXPORT cpRotaryLimitJoint* cpRotaryLimitJointAlloc(void);
/// Initialize a damped rotary limit joint.
CP_EXPORT cpRotaryLimitJoint* cpRotaryLimitJointInit(cpRotaryLimitJoint *joint, cpBody *a, cpBody *b, cpFloat min, cpFloat max);
/// Allocate and initialize a damped rotary limit joint.
CP_EXPORT cpConstraint* cpRotaryLimitJointNew(cpBody *a, cpBody *b, cpFloat min, cpFloat max);

/// Get the minimum distance the joint will maintain between the two anchors.
CP_EXPORT cpFloat cpRotaryLimitJointGetMin(const cpConstraint *constraint);
/// Set the minimum distance the joint will maintain between the two anchors.
CP_EXPORT void cpRotaryLimitJointSetMin(cpConstraint *constraint, cpFloat min);

/// Get the maximum distance the joint will maintain between the two anchors.
CP_EXPORT cpFloat cpRotaryLimitJointGetMax(const cpConstraint *constraint);
/// Set the maximum distance the joint will maintain between the two anchors.
CP_EXPORT void cpRotaryLimitJointSetMax(cpConstraint *constraint, cpFloat max);

/// @}
