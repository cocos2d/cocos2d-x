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

#ifndef CHIPMUNK_HEADER
#define CHIPMUNK_HEADER

#ifdef __cplusplus
extern "C" {
#endif

void cpMessage(const char *message, const char *condition, const char *file, int line, int isError);
#ifdef NDEBUG
	#define	cpAssertWarn(condition, message)
#else
	#define cpAssertWarn(condition, message) if(!(condition)) cpMessage(message, #condition, __FILE__, __LINE__, 0)
#endif

#ifdef NDEBUG
	#define	cpAssert(condition, message)
#else
	#define cpAssert(condition, message) if(!(condition)) cpMessage(message, #condition, __FILE__, __LINE__, 1)
#endif

#include "chipmunk_types.h"

static inline cpFloat 
cpfmax(cpFloat a, cpFloat b)
{
	return (a > b) ? a : b;
}

static inline cpFloat
cpfmin(cpFloat a, cpFloat b)
{
	return (a < b) ? a : b;
}

static inline cpFloat
cpfabs(cpFloat n)
{
	return (n < 0) ? -n : n;
}

static inline cpFloat
cpfclamp(cpFloat f, cpFloat min, cpFloat max)
{
	return cpfmin(cpfmax(f, min), max);
}

static inline cpFloat
cpflerp(cpFloat f1, cpFloat f2, cpFloat t)
{
	return f1*(1.0f - t) + f2*t;
}

static inline cpFloat
cpflerpconst(cpFloat f1, cpFloat f2, cpFloat d)
{
	return f1 + cpfclamp(f2 - f1, -d, d);
}

#ifndef INFINITY
	#ifdef _MSC_VER
		union MSVC_EVIL_FLOAT_HACK
		{
			unsigned __int8 Bytes[4];
			float Value;
		};
		static union MSVC_EVIL_FLOAT_HACK INFINITY_HACK = {{0x00, 0x00, 0x80, 0x7F}};
		#define INFINITY (INFINITY_HACK.Value)
	#endif
	
	#ifdef __GNUC__
		#define INFINITY (__builtin_inf())
	#endif
	
	#ifndef INFINITY
		#define INFINITY (1e1000)
	#endif
#endif

// Maximum allocated size for various Chipmunk buffer sizes
#define CP_BUFFER_BYTES (32*1024)

#define cpmalloc malloc
#define cpcalloc calloc
#define cprealloc realloc
#define cpfree free

#include "cpVect.h"
#include "cpBB.h"
#include "cpBody.h"
#include "cpArray.h"
#include "cpHashSet.h"
#include "cpSpaceHash.h"

#include "cpShape.h"
#include "cpPolyShape.h"

#include "cpArbiter.h"
#include "cpCollision.h"
	
#include "constraints/cpConstraint.h"

#include "cpSpace.h"

#define CP_HASH_COEF (3344921057ul)
#define CP_HASH_PAIR(A, B) ((cpHashValue)(A)*CP_HASH_COEF ^ (cpHashValue)(B)*CP_HASH_COEF)

extern char *cpVersionString;
void cpInitChipmunk(void);

// Calculate the moment of inertia for a circle, r1 and r2 are the inner and outer diameters.
// (A solid circle has an inner diameter of 0)
cpFloat cpMomentForCircle(cpFloat m, cpFloat r1, cpFloat r2, cpVect offset);

// Calculate the moment of inertia for a line segment. (beveling radius not supported)
cpFloat cpMomentForSegment(cpFloat m, cpVect a, cpVect b);

// Calculate the moment of inertia for a solid polygon shape.
cpFloat cpMomentForPoly(cpFloat m, int numVerts, cpVect *verts, cpVect offset);

// Calculate the moment of inertia for a solid box.
cpFloat cpMomentForBox(cpFloat m, cpFloat width, cpFloat height);

#ifdef __cplusplus
}
#endif

#endif
