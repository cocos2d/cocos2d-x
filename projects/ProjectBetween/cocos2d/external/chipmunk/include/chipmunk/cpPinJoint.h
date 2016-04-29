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

/// @defgroup cpPinJoint cpPinJoint
/// @{

/// Check if a constraint is a pin joint.
CP_EXPORT cpBool cpConstraintIsPinJoint(const cpConstraint *constraint);

/// Allocate a pin joint.
CP_EXPORT cpPinJoint* cpPinJointAlloc(void);
/// Initialize a pin joint.
CP_EXPORT cpPinJoint* cpPinJointInit(cpPinJoint *joint, cpBody *a, cpBody *b, cpVect anchorA, cpVect anchorB);
/// Allocate and initialize a pin joint.
CP_EXPORT cpConstraint* cpPinJointNew(cpBody *a, cpBody *b, cpVect anchorA, cpVect anchorB);

/// Get the location of the first anchor relative to the first body.
CP_EXPORT cpVect cpPinJointGetAnchorA(const cpConstraint *constraint);
/// Set the location of the first anchor relative to the first body.
CP_EXPORT void cpPinJointSetAnchorA(cpConstraint *constraint, cpVect anchorA);

/// Get the location of the second anchor relative to the second body.
CP_EXPORT cpVect cpPinJointGetAnchorB(const cpConstraint *constraint);
/// Set the location of the second anchor relative to the second body.
CP_EXPORT void cpPinJointSetAnchorB(cpConstraint *constraint, cpVect anchorB);

/// Get the distance the joint will maintain between the two anchors.
CP_EXPORT cpFloat cpPinJointGetDist(const cpConstraint *constraint);
/// Set the distance the joint will maintain between the two anchors.
CP_EXPORT void cpPinJointSetDist(cpConstraint *constraint, cpFloat dist);

///@}
