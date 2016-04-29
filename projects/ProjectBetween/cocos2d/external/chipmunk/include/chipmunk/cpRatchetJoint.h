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

/// @defgroup cpRatchetJoint cpRatchetJoint
/// @{

/// Check if a constraint is a damped rotary springs.
CP_EXPORT cpBool cpConstraintIsRatchetJoint(const cpConstraint *constraint);

/// Allocate a ratchet joint.
CP_EXPORT cpRatchetJoint* cpRatchetJointAlloc(void);
/// Initialize a ratched joint.
CP_EXPORT cpRatchetJoint* cpRatchetJointInit(cpRatchetJoint *joint, cpBody *a, cpBody *b, cpFloat phase, cpFloat ratchet);
/// Allocate and initialize a ratchet joint.
CP_EXPORT cpConstraint* cpRatchetJointNew(cpBody *a, cpBody *b, cpFloat phase, cpFloat ratchet);

/// Get the angle of the current ratchet tooth.
CP_EXPORT cpFloat cpRatchetJointGetAngle(const cpConstraint *constraint);
/// Set the angle of the current ratchet tooth.
CP_EXPORT void cpRatchetJointSetAngle(cpConstraint *constraint, cpFloat angle);

/// Get the phase offset of the ratchet.
CP_EXPORT cpFloat cpRatchetJointGetPhase(const cpConstraint *constraint);
/// Get the phase offset of the ratchet.
CP_EXPORT void cpRatchetJointSetPhase(cpConstraint *constraint, cpFloat phase);

/// Get the angular distance of each ratchet.
CP_EXPORT cpFloat cpRatchetJointGetRatchet(const cpConstraint *constraint);
/// Set the angular distance of each ratchet.
CP_EXPORT void cpRatchetJointSetRatchet(cpConstraint *constraint, cpFloat ratchet);

/// @}
