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

/// @defgroup cpSimpleMotor cpSimpleMotor
/// @{

/// Opaque struct type for damped rotary springs.
typedef struct cpSimpleMotor cpSimpleMotor;

/// Check if a constraint is a damped rotary springs.
CP_EXPORT cpBool cpConstraintIsSimpleMotor(const cpConstraint *constraint);

/// Allocate a simple motor.
CP_EXPORT cpSimpleMotor* cpSimpleMotorAlloc(void);
/// initialize a simple motor.
CP_EXPORT cpSimpleMotor* cpSimpleMotorInit(cpSimpleMotor *joint, cpBody *a, cpBody *b, cpFloat rate);
/// Allocate and initialize a simple motor.
CP_EXPORT cpConstraint* cpSimpleMotorNew(cpBody *a, cpBody *b, cpFloat rate);

/// Get the rate of the motor.
CP_EXPORT cpFloat cpSimpleMotorGetRate(const cpConstraint *constraint);
/// Set the rate of the motor.
CP_EXPORT void cpSimpleMotorSetRate(cpConstraint *constraint, cpFloat rate);

/// @}
