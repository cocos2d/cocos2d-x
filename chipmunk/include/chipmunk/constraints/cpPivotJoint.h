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

/// @defgroup cpPivotJoint cpPivotJoint
/// @{

const cpConstraintClass *cpPivotJointGetClass(void);

/// @private
typedef struct cpPivotJoint {
	cpConstraint constraint;
	cpVect anchr1, anchr2;
	
	cpVect r1, r2;
	cpVect k1, k2;
	
	cpVect jAcc;
	cpFloat jMaxLen;
	cpVect bias;
} cpPivotJoint;

/// Allocate a pivot joint
cpPivotJoint* cpPivotJointAlloc(void);
/// Initialize a pivot joint.
cpPivotJoint* cpPivotJointInit(cpPivotJoint *joint, cpBody *a, cpBody *b, cpVect anchr1, cpVect anchr2);
/// Allocate and initialize a pivot joint.
cpConstraint* cpPivotJointNew(cpBody *a, cpBody *b, cpVect pivot);
/// Allocate and initialize a pivot joint with specific anchors.
cpConstraint* cpPivotJointNew2(cpBody *a, cpBody *b, cpVect anchr1, cpVect anchr2);

CP_DefineConstraintProperty(cpPivotJoint, cpVect, anchr1, Anchr1);
CP_DefineConstraintProperty(cpPivotJoint, cpVect, anchr2, Anchr2);

/// @}
