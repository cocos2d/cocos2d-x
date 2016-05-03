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

/// @defgroup cpGrooveJoint cpGrooveJoint
/// @{

/// Check if a constraint is a slide joint.
CP_EXPORT cpBool cpConstraintIsGrooveJoint(const cpConstraint *constraint);

/// Allocate a groove joint.
CP_EXPORT cpGrooveJoint* cpGrooveJointAlloc(void);
/// Initialize a groove joint.
CP_EXPORT cpGrooveJoint* cpGrooveJointInit(cpGrooveJoint *joint, cpBody *a, cpBody *b, cpVect groove_a, cpVect groove_b, cpVect anchorB);
/// Allocate and initialize a groove joint.
CP_EXPORT cpConstraint* cpGrooveJointNew(cpBody *a, cpBody *b, cpVect groove_a, cpVect groove_b, cpVect anchorB);

/// Get the first endpoint of the groove relative to the first body.
CP_EXPORT cpVect cpGrooveJointGetGrooveA(const cpConstraint *constraint);
/// Set the first endpoint of the groove relative to the first body.
CP_EXPORT void cpGrooveJointSetGrooveA(cpConstraint *constraint, cpVect grooveA);

/// Get the first endpoint of the groove relative to the first body.
CP_EXPORT cpVect cpGrooveJointGetGrooveB(const cpConstraint *constraint);
/// Set the first endpoint of the groove relative to the first body.
CP_EXPORT void cpGrooveJointSetGrooveB(cpConstraint *constraint, cpVect grooveB);

/// Get the location of the second anchor relative to the second body.
CP_EXPORT cpVect cpGrooveJointGetAnchorB(const cpConstraint *constraint);
/// Set the location of the second anchor relative to the second body.
CP_EXPORT void cpGrooveJointSetAnchorB(cpConstraint *constraint, cpVect anchorB);

/// @}
