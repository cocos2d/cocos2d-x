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
#include <math.h>
#include <stdarg.h>

#include "chipmunk_private.h"

//#ifdef __cplusplus
//extern "C" {
//#endif
//	void cpInitCollisionFuncs(void);
//#ifdef __cplusplus
//}
//#endif

void
cpMessage(const char *condition, const char *file, int line, cpBool isError, cpBool isHardError, const char *message, ...)
{
	fprintf(stderr, (isError ? "Aborting due to Chipmunk error: " : "Chipmunk warning: "));
	
	va_list vargs;
	va_start(vargs, message); {
		vfprintf(stderr, message, vargs);
		fprintf(stderr, "\n");
	} va_end(vargs);
	
	fprintf(stderr, "\tFailed condition: %s\n", condition);
	fprintf(stderr, "\tSource:%s:%d\n", file, line);
	
	if(isHardError) abort();
}

#define STR(s) #s
#define XSTR(s) STR(s)

const char *cpVersionString = XSTR(CP_VERSION_MAJOR)"."XSTR(CP_VERSION_MINOR)"."XSTR(CP_VERSION_RELEASE);

void
cpInitChipmunk(void)
{
//#ifndef NDEBUG
//	printf("Initializing Chipmunk v%s (Debug Enabled)\n", cpVersionString);
//	printf("Compile with -DNDEBUG defined to disable debug mode and runtime assertion checks\n");
//#endif
//	
//	cpInitCollisionFuncs();
}

cpFloat
cpMomentForCircle(cpFloat m, cpFloat r1, cpFloat r2, cpVect offset)
{
	return m*(0.5f*(r1*r1 + r2*r2) + cpvlengthsq(offset));
}

cpFloat
cpAreaForCircle(cpFloat r1, cpFloat r2)
{
	return (cpFloat)M_PI*cpfabs(r1*r1 - r2*r2);
}

cpFloat
cpMomentForSegment(cpFloat m, cpVect a, cpVect b)
{
	cpFloat length = cpvlength(cpvsub(b, a));
	cpVect offset = cpvmult(cpvadd(a, b), 1.0f/2.0f);
	
	return m*(length*length/12.0f + cpvlengthsq(offset));
}

cpFloat
cpAreaForSegment(cpVect a, cpVect b, cpFloat r)
{
	return r*((cpFloat)M_PI*r + 2.0f*cpvdist(a, b));
}

cpFloat
cpMomentForPoly(cpFloat m, const int numVerts, const cpVect *verts, cpVect offset)
{
	cpFloat sum1 = 0.0f;
	cpFloat sum2 = 0.0f;
	for(int i=0; i<numVerts; i++){
		cpVect v1 = cpvadd(verts[i], offset);
		cpVect v2 = cpvadd(verts[(i+1)%numVerts], offset);
		
		cpFloat a = cpvcross(v2, v1);
		cpFloat b = cpvdot(v1, v1) + cpvdot(v1, v2) + cpvdot(v2, v2);
		
		sum1 += a*b;
		sum2 += a;
	}
	
	return (m*sum1)/(6.0f*sum2);
}

cpFloat
cpAreaForPoly(const int numVerts, const cpVect *verts)
{
	cpFloat area = 0.0f;
	for(int i=0; i<numVerts; i++){
		area += cpvcross(verts[i], verts[(i+1)%numVerts]);
	}
	
	return -area/2.0f;
}

cpVect
cpCentroidForPoly(const int numVerts, const cpVect *verts)
{
	cpFloat sum = 0.0f;
	cpVect vsum = cpvzero;
	
	for(int i=0; i<numVerts; i++){
		cpVect v1 = verts[i];
		cpVect v2 = verts[(i+1)%numVerts];
		cpFloat cross = cpvcross(v1, v2);
		
		sum += cross;
		vsum = cpvadd(vsum, cpvmult(cpvadd(v1, v2), cross));
	}
	
	return cpvmult(vsum, 1.0f/(3.0f*sum));
}

void
cpRecenterPoly(const int numVerts, cpVect *verts){
	cpVect centroid = cpCentroidForPoly(numVerts, verts);
	
	for(int i=0; i<numVerts; i++){
		verts[i] = cpvsub(verts[i], centroid);
	}
}

cpFloat
cpMomentForBox(cpFloat m, cpFloat width, cpFloat height)
{
	return m*(width*width + height*height)/12.0f;
}

cpFloat
cpMomentForBox2(cpFloat m, cpBB box)
{
	cpFloat width = box.r - box.l;
	cpFloat height = box.t - box.b;
	cpVect offset = cpvmult(cpv(box.l + box.r, box.b + box.t), 0.5f);
	
	return cpMomentForBox(m, width, height) + m*cpvlengthsq(offset);
}

#include "chipmunk_ffi.h"
