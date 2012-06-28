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

#include "chipmunk_private.h"
#include "constraints/util.h"

// TODO: Comment me!

void cpConstraintDestroy(cpConstraint *constraint){}

void
cpConstraintFree(cpConstraint *constraint)
{
	if(constraint){
		cpConstraintDestroy(constraint);
		cpfree(constraint);
	}
}

// *** declared in util.h TODO move declaration to chipmunk_private.h

void
cpConstraintInit(cpConstraint *constraint, const cpConstraintClass *klass, cpBody *a, cpBody *b)
{
	constraint->klass = klass;
	
	constraint->a = a;
	constraint->b = b;
	constraint->space = NULL;
	
	constraint->next_a = NULL;
	constraint->next_b = NULL;
	
	constraint->maxForce = (cpFloat)INFINITY;
	constraint->errorBias = cpfpow(1.0f - 0.1f, 60.0f);
	constraint->maxBias = (cpFloat)INFINITY;
	
	constraint->preSolve = NULL;
	constraint->postSolve = NULL;
}
