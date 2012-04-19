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

/// @defgroup cpRotaryLimitJoint cpRotaryLimitJoint
/// @{

const cpConstraintClass *cpRotaryLimitJointGetClass(void);

/// @private
typedef struct cpRotaryLimitJoint {
    cpConstraint constraint;
    cpFloat min, max;
    
    cpFloat iSum;
        
    cpFloat bias;
    cpFloat jAcc, jMax;
} cpRotaryLimitJoint;

/// Allocate a damped rotary limit joint.
cpRotaryLimitJoint* cpRotaryLimitJointAlloc(void);
/// Initialize a damped rotary limit joint.
cpRotaryLimitJoint* cpRotaryLimitJointInit(cpRotaryLimitJoint *joint, cpBody *a, cpBody *b, cpFloat min, cpFloat max);
/// Allocate and initialize a damped rotary limit joint.
cpConstraint* cpRotaryLimitJointNew(cpBody *a, cpBody *b, cpFloat min, cpFloat max);

CP_DefineConstraintProperty(cpRotaryLimitJoint, cpFloat, min, Min);
CP_DefineConstraintProperty(cpRotaryLimitJoint, cpFloat, max, Max);

/// @}
