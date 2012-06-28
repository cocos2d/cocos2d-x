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

/// @defgroup cpSimpleMotor cpSimpleMotor
/// @{

const cpConstraintClass *cpSimpleMotorGetClass(void);

/// @private
typedef struct cpSimpleMotor {
	cpConstraint constraint;
	cpFloat rate;
	
	cpFloat iSum;
		
	cpFloat jAcc, jMax;
} cpSimpleMotor;

/// Allocate a simple motor.
cpSimpleMotor* cpSimpleMotorAlloc(void);
/// initialize a simple motor.
cpSimpleMotor* cpSimpleMotorInit(cpSimpleMotor *joint, cpBody *a, cpBody *b, cpFloat rate);
/// Allocate and initialize a simple motor.
cpConstraint* cpSimpleMotorNew(cpBody *a, cpBody *b, cpFloat rate);

CP_DefineConstraintProperty(cpSimpleMotor, cpFloat, rate, Rate);

/// @}
