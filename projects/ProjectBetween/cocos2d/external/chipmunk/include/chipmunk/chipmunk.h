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

#ifndef CHIPMUNK_H
#define CHIPMUNK_H

#include <stdlib.h>
#include <math.h>

#ifdef WIN32
	// For alloca().
	#include <malloc.h>
    #if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
        #define CP_EXPORT __declspec(dllexport)
    #else
	    #define CP_EXPORT
    #endif
#else
	#include <alloca.h>
	#define CP_EXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif

// NUKE
#ifndef CP_ALLOW_PRIVATE_ACCESS
	#define CP_ALLOW_PRIVATE_ACCESS 0
#endif

#if CP_ALLOW_PRIVATE_ACCESS == 1
	#define CP_PRIVATE(__symbol__) __symbol__
#else
	#define CP_PRIVATE(__symbol__) __symbol__##_private
#endif

CP_EXPORT void cpMessage(const char *condition, const char *file, int line, int isError, int isHardError, const char *message, ...);
#ifdef NDEBUG
	#define	cpAssertWarn(__condition__, ...)
	#define	cpAssertSoft(__condition__, ...)
#else
	#define cpAssertSoft(__condition__, ...) if(!(__condition__)){cpMessage(#__condition__, __FILE__, __LINE__, 1, 0, __VA_ARGS__); abort();}
	#define cpAssertWarn(__condition__, ...) if(!(__condition__)) cpMessage(#__condition__, __FILE__, __LINE__, 0, 0, __VA_ARGS__)
#endif

// Hard assertions are used in situations where the program definitely will crash anyway, and the reason is inexpensive to detect.
#define cpAssertHard(__condition__, ...) if(!(__condition__)){cpMessage(#__condition__, __FILE__, __LINE__, 1, 1, __VA_ARGS__); abort();}

#include "chipmunk_types.h"
	
/// @defgroup misc Misc
/// @{

/// Allocated size for various Chipmunk buffers
#ifndef CP_BUFFER_BYTES
	#define CP_BUFFER_BYTES (32*1024)
#endif

#ifndef cpcalloc
	/// Chipmunk calloc() alias.
	#define cpcalloc calloc
#endif

#ifndef cprealloc
	/// Chipmunk realloc() alias.
	#define cprealloc realloc
#endif

#ifndef cpfree
	/// Chipmunk free() alias.
	#define cpfree free
#endif

typedef struct cpArray cpArray;
typedef struct cpHashSet cpHashSet;

typedef struct cpBody cpBody;

typedef struct cpShape cpShape;
typedef struct cpCircleShape cpCircleShape;
typedef struct cpSegmentShape cpSegmentShape;
typedef struct cpPolyShape cpPolyShape;

typedef struct cpConstraint cpConstraint;
typedef struct cpPinJoint cpPinJoint;
typedef struct cpSlideJoint cpSlideJoint;
typedef struct cpPivotJoint cpPivotJoint;
typedef struct cpGrooveJoint cpGrooveJoint;
typedef struct cpDampedSpring cpDampedSpring;
typedef struct cpDampedRotarySpring cpDampedRotarySpring;
typedef struct cpRotaryLimitJoint cpRotaryLimitJoint;
typedef struct cpRatchetJoint cpRatchetJoint;
typedef struct cpGearJoint cpGearJoint;
typedef struct cpSimpleMotorJoint cpSimpleMotorJoint;

typedef struct cpCollisionHandler cpCollisionHandler;
typedef struct cpContactPointSet cpContactPointSet;
typedef struct cpArbiter cpArbiter;

typedef struct cpSpace cpSpace;

#include "cpVect.h"
#include "cpBB.h"
#include "cpTransform.h"
#include "cpSpatialIndex.h"

#include "cpArbiter.h"	

#include "cpBody.h"
#include "cpShape.h"
#include "cpPolyShape.h"

#include "cpConstraint.h"

#include "cpSpace.h"
#include "cpHastySpace.h"

// Chipmunk 7.0.1
#define CP_VERSION_MAJOR 7
#define CP_VERSION_MINOR 0
#define CP_VERSION_RELEASE 1

/// Version string.
CP_EXPORT extern const char *cpVersionString;

/// Calculate the moment of inertia for a circle.
/// @c r1 and @c r2 are the inner and outer diameters. A solid circle has an inner diameter of 0.
CP_EXPORT cpFloat cpMomentForCircle(cpFloat m, cpFloat r1, cpFloat r2, cpVect offset);

/// Calculate area of a hollow circle.
/// @c r1 and @c r2 are the inner and outer diameters. A solid circle has an inner diameter of 0.
CP_EXPORT cpFloat cpAreaForCircle(cpFloat r1, cpFloat r2);

/// Calculate the moment of inertia for a line segment.
/// Beveling radius is not supported.
CP_EXPORT cpFloat cpMomentForSegment(cpFloat m, cpVect a, cpVect b, cpFloat radius);

/// Calculate the area of a fattened (capsule shaped) line segment.
CP_EXPORT cpFloat cpAreaForSegment(cpVect a, cpVect b, cpFloat radius);

/// Calculate the moment of inertia for a solid polygon shape assuming it's center of gravity is at it's centroid. The offset is added to each vertex.
CP_EXPORT cpFloat cpMomentForPoly(cpFloat m, int count, const cpVect *verts, cpVect offset, cpFloat radius);

/// Calculate the signed area of a polygon. A Clockwise winding gives positive area.
/// This is probably backwards from what you expect, but matches Chipmunk's the winding for poly shapes.
CP_EXPORT cpFloat cpAreaForPoly(const int count, const cpVect *verts, cpFloat radius);

/// Calculate the natural centroid of a polygon.
CP_EXPORT cpVect cpCentroidForPoly(const int count, const cpVect *verts);

/// Calculate the moment of inertia for a solid box.
CP_EXPORT cpFloat cpMomentForBox(cpFloat m, cpFloat width, cpFloat height);

/// Calculate the moment of inertia for a solid box.
CP_EXPORT cpFloat cpMomentForBox2(cpFloat m, cpBB box);

/// Calculate the convex hull of a given set of points. Returns the count of points in the hull.
/// @c result must be a pointer to a @c cpVect array with at least @c count elements. If @c verts == @c result, then @c verts will be reduced inplace.
/// @c first is an optional pointer to an integer to store where the first vertex in the hull came from (i.e. verts[first] == result[0])
/// @c tol is the allowed amount to shrink the hull when simplifying it. A tolerance of 0.0 creates an exact hull.
CP_EXPORT int cpConvexHull(int count, const cpVect *verts, cpVect *result, int *first, cpFloat tol);

#ifdef _MSC_VER
#include "malloc.h"
#endif

/// Convenience macro to work with cpConvexHull.
/// @c count and @c verts is the input array passed to cpConvexHull().
/// @c count_var and @c verts_var are the names of the variables the macro creates to store the result.
/// The output vertex array is allocated on the stack using alloca() so it will be freed automatically, but cannot be returned from the current scope.
#define CP_CONVEX_HULL(__count__, __verts__, __count_var__, __verts_var__) \
cpVect *__verts_var__ = (cpVect *)alloca(__count__*sizeof(cpVect)); \
int __count_var__ = cpConvexHull(__count__, __verts__, __verts_var__, NULL, 0.0); \

/// Returns the closest point on the line segment ab, to the point p.
static inline cpVect
cpClosetPointOnSegment(const cpVect p, const cpVect a, const cpVect b)
{
	cpVect delta = cpvsub(a, b);
	cpFloat t = cpfclamp01(cpvdot(delta, cpvsub(p, b))/cpvlengthsq(delta));
	return cpvadd(b, cpvmult(delta, t));
}

#if defined(__has_extension)
#if __has_extension(blocks)
// Define alternate block based alternatives for a few of the callback heavy functions.
// Collision handlers are post-step callbacks are not included to avoid memory management issues.
// If you want to use blocks for those and are aware of how to correctly manage the memory, the implementation is trivial. 

void cpSpaceEachBody_b(cpSpace *space, void (^block)(cpBody *body));
void cpSpaceEachShape_b(cpSpace *space, void (^block)(cpShape *shape));
void cpSpaceEachConstraint_b(cpSpace *space, void (^block)(cpConstraint *constraint));

void cpBodyEachShape_b(cpBody *body, void (^block)(cpShape *shape));
void cpBodyEachConstraint_b(cpBody *body, void (^block)(cpConstraint *constraint));
void cpBodyEachArbiter_b(cpBody *body, void (^block)(cpArbiter *arbiter));

typedef void (^cpSpacePointQueryBlock)(cpShape *shape, cpVect point, cpFloat distance, cpVect gradient);
void cpSpacePointQuery_b(cpSpace *space, cpVect point, cpFloat maxDistance, cpShapeFilter filter, cpSpacePointQueryBlock block);

typedef void (^cpSpaceSegmentQueryBlock)(cpShape *shape, cpVect point, cpVect normal, cpFloat alpha);
void cpSpaceSegmentQuery_b(cpSpace *space, cpVect start, cpVect end, cpFloat radius, cpShapeFilter filter, cpSpaceSegmentQueryBlock block);

typedef void (^cpSpaceBBQueryBlock)(cpShape *shape);
void cpSpaceBBQuery_b(cpSpace *space, cpBB bb, cpShapeFilter filter, cpSpaceBBQueryBlock block);

typedef void (^cpSpaceShapeQueryBlock)(cpShape *shape, cpContactPointSet *points);
cpBool cpSpaceShapeQuery_b(cpSpace *space, cpShape *shape, cpSpaceShapeQueryBlock block);

#endif
#endif


//@}

#ifdef __cplusplus
}

static inline cpVect operator *(const cpVect v, const cpFloat s){return cpvmult(v, s);}
static inline cpVect operator +(const cpVect v1, const cpVect v2){return cpvadd(v1, v2);}
static inline cpVect operator -(const cpVect v1, const cpVect v2){return cpvsub(v1, v2);}
static inline cpBool operator ==(const cpVect v1, const cpVect v2){return cpveql(v1, v2);}
static inline cpVect operator -(const cpVect v){return cpvneg(v);}

#endif
#endif
