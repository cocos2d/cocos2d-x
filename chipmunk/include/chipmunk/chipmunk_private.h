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

#ifndef _CHIPMUNK_PRIVATE_H_
#define _CHIPMUNK_PRIVATE_H_

#define CP_ALLOW_PRIVATE_ACCESS 1
#include "chipmunk.h"

void *cpSpaceGetPostStepData(cpSpace *space, void *obj);

void cpSpaceActivateBody(cpSpace *space, cpBody *body);

static inline void
cpSpaceLock(cpSpace *space)
{
	space->locked++;
}

static inline void
cpSpaceUnlock(cpSpace *space)
{
	space->locked--;
	cpAssert(space->locked >= 0, "Internal error:Space lock underflow.");
	
	if(!space->locked){
		cpArray *waking = space->rousedBodies;
		for(int i=0, count=waking->num; i<count; i++){
			cpSpaceActivateBody(space, (cpBody *)waking->arr[i]);
		}
		
		waking->num = 0;
	}
}

#endif

