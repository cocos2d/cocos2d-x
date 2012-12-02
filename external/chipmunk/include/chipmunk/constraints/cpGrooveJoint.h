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

/// @defgroup cpGrooveJoint cpGrooveJoint
/// @{

const cpConstraintClass *cpGrooveJointGetClass(void);

/// @private
typedef struct cpGrooveJoint {
	cpConstraint constraint;
	cpVect grv_n, grv_a, grv_b;
	cpVect  anchr2;
	
	cpVect grv_tn;
	cpFloat clamp;
	cpVect r1, r2;
	cpMat2x2 k;
	
	cpVect jAcc;
	cpVect bias;
} cpGrooveJoint;

/// Allocate a groove joint.
cpGrooveJoint* cpGrooveJointAlloc(void);
/// Initialize a groove joint.
cpGrooveJoint* cpGrooveJointInit(cpGrooveJoint *joint, cpBody *a, cpBody *b, cpVect groove_a, cpVect groove_b, cpVect anchr2);
/// Allocate and initialize a groove joint.
cpConstraint* cpGrooveJointNew(cpBody *a, cpBody *b, cpVect groove_a, cpVect groove_b, cpVect anchr2);

CP_DefineConstraintGetter(cpGrooveJoint, cpVect, grv_a, GrooveA)
/// Set endpoint a of a groove joint's groove
void cpGrooveJointSetGrooveA(cpConstraint *constraint, cpVect value);
CP_DefineConstraintGetter(cpGrooveJoint, cpVect, grv_b, GrooveB)
/// Set endpoint b of a groove joint's groove
void cpGrooveJointSetGrooveB(cpConstraint *constraint, cpVect value);
CP_DefineConstraintProperty(cpGrooveJoint, cpVect, anchr2, Anchr2)

/// @}
