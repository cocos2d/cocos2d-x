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

#include <stdlib.h>
#include <stdio.h>

#include "chipmunk.h"

#ifdef __cplusplus
extern "C" {
#endif
	void cpInitCollisionFuncs(void);
#ifdef __cplusplus
}
#endif

void
cpMessage(const char *message, const char *condition, const char *file, int line, int isError)
{
	fprintf(stderr, (isError ? "Aborting due to Chipmunk error: %s\n" : "Chipmunk warning: %s\n"), message);
	fprintf(stderr, "\tFailed condition: %s\n", condition);
	fprintf(stderr, "\tSource:%s:%d\n", file, line);
	
	if(isError) abort();
}


char *cpVersionString = "5.x.x";

void
cpInitChipmunk(void)
{
#ifndef NDEBUG
	printf("Initializing Chipmunk v%s (Debug Enabled)\n", cpVersionString);
	printf("Compile with -DNDEBUG defined to disable debug mode and runtime assertion checks\n");
#endif
	
	cpInitCollisionFuncs();
}

cpFloat
cpMomentForCircle(cpFloat m, cpFloat r1, cpFloat r2, cpVect offset)
{
	return (1.0f/2.0f)*m*(r1*r1 + r2*r2) + m*cpvdot(offset, offset);
}

cpFloat
cpMomentForSegment(cpFloat m, cpVect a, cpVect b)
{
	cpFloat length = cpvlength(cpvsub(b, a));
	cpVect offset = cpvmult(cpvadd(a, b), 1.0f/2.0f);
	
	return m*length*length/12.0f + m*cpvdot(offset, offset);
}

cpFloat
cpMomentForPoly(cpFloat m, const int numVerts, cpVect *verts, cpVect offset)
{
	cpVect *tVerts = (cpVect *)cpcalloc(numVerts, sizeof(cpVect));
	for(int i=0; i<numVerts; i++)
		tVerts[i] = cpvadd(verts[i], offset);
	
	cpFloat sum1 = 0.0f;
	cpFloat sum2 = 0.0f;
	for(int i=0; i<numVerts; i++){
		cpVect v1 = tVerts[i];
		cpVect v2 = tVerts[(i+1)%numVerts];
		
		cpFloat a = cpvcross(v2, v1);
		cpFloat b = cpvdot(v1, v1) + cpvdot(v1, v2) + cpvdot(v2, v2);
		
		sum1 += a*b;
		sum2 += a;
	}
	
	cpfree(tVerts);
	return (m*sum1)/(6.0f*sum2);
}

cpFloat
cpMomentForBox(cpFloat m, cpFloat width, cpFloat height)
{
	return m*(width*width + height*height)/12;
}


#include "chipmunk_ffi.h"
