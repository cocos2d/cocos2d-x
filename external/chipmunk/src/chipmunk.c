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
 
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "chipmunk_private.h"

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
	
	if(isError) abort();
}

#define STR(s) #s
#define XSTR(s) STR(s)

const char *cpVersionString = XSTR(CP_VERSION_MAJOR)"."XSTR(CP_VERSION_MINOR)"."XSTR(CP_VERSION_RELEASE);

void
cpInitChipmunk(void)
{
	cpAssertWarn(cpFalse, "cpInitChipmunk is deprecated and no longer required. It will be removed in the future.");
}

//MARK: Misc Functions

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
	cpVect offset = cpvmult(cpvadd(a, b), 0.5f);
	return m*(cpvdistsq(b, a)/12.0f + cpvlengthsq(offset));
}

cpFloat
cpAreaForSegment(cpVect a, cpVect b, cpFloat r)
{
	return r*((cpFloat)M_PI*r + 2.0f*cpvdist(a, b));
}

cpFloat
cpMomentForPoly(cpFloat m, const int numVerts, const cpVect *verts, cpVect offset)
{
	if(numVerts == 2) return cpMomentForSegment(m, verts[0], verts[1]);
	
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
	
	// TODO NaN when offset is 0 and m is INFINITY
	return cpMomentForBox(m, width, height) + m*cpvlengthsq(offset);
}

//MARK: Quick Hull

void
cpLoopIndexes(cpVect *verts, int count, int *start, int *end)
{
	(*start) = (*end) = 0;
	cpVect min = verts[0];
	cpVect max = min;
	
  for(int i=1; i<count; i++){
    cpVect v = verts[i];
		
    if(v.x < min.x || (v.x == min.x && v.y < min.y)){
      min = v;
      (*start) = i;
    } else if(v.x > max.x || (v.x == max.x && v.y > max.y)){
			max = v;
			(*end) = i;
		}
	}
}

#define SWAP(__A__, __B__) {cpVect __TMP__ = __A__; __A__ = __B__; __B__ = __TMP__;}

static int
QHullPartition(cpVect *verts, int count, cpVect a, cpVect b, cpFloat tol)
{
	if(count == 0) return 0;
	
	cpFloat max = 0;
	int pivot = 0;
	
	cpVect delta = cpvsub(b, a);
	cpFloat valueTol = tol*cpvlength(delta);
	
	int head = 0;
	for(int tail = count-1; head <= tail;){
		cpFloat value = cpvcross(delta, cpvsub(verts[head], a));
		if(value > valueTol){
			if(value > max){
				max = value;
				pivot = head;
			}
			
			head++;
		} else {
			SWAP(verts[head], verts[tail]);
			tail--;
		}
	}
	
	// move the new pivot to the front if it's not already there.
	if(pivot != 0) SWAP(verts[0], verts[pivot]);
	return head;
}

static int
QHullReduce(cpFloat tol, cpVect *verts, int count, cpVect a, cpVect pivot, cpVect b, cpVect *result)
{
	if(count < 0){
		return 0;
	} else if(count == 0) {
		result[0] = pivot;
		return 1;
	} else {
		int left_count = QHullPartition(verts, count, a, pivot, tol);
		int index = QHullReduce(tol, verts + 1, left_count - 1, a, verts[0], pivot, result);
		
		result[index++] = pivot;
		
		int right_count = QHullPartition(verts + left_count, count - left_count, pivot, b, tol);
		return index + QHullReduce(tol, verts + left_count + 1, right_count - 1, pivot, verts[left_count], b, result + index);
	}
}

// QuickHull seemed like a neat algorithm, and efficient-ish for large input sets.
// My implementation performs an in place reduction using the result array as scratch space.
int
cpConvexHull(int count, cpVect *verts, cpVect *result, int *first, cpFloat tol)
{
	if(result){
		// Copy the line vertexes into the empty part of the result polyline to use as a scratch buffer.
		memcpy(result, verts, count*sizeof(cpVect));
	} else {
		// If a result array was not specified, reduce the input instead.
		result = verts;
	}
	
	// Degenerate case, all poins are the same.
	int start, end;
	cpLoopIndexes(verts, count, &start, &end);
	if(start == end){
		if(first) (*first) = 0;
		return 1;
	}
	
	SWAP(result[0], result[start]);
	SWAP(result[1], result[end == 0 ? start : end]);
	
	cpVect a = result[0];
	cpVect b = result[1];
	
	if(first) (*first) = start;
	int resultCount = QHullReduce(tol, result + 2, count - 2, a, b, a, result + 1) + 1;
	cpAssertSoft(cpPolyValidate(result, resultCount),
		"Internal error: cpConvexHull() and cpPolyValidate() did not agree."
		"Please report this error with as much info as you can.");
	return resultCount;
}

//MARK: Alternate Block Iterators

#if defined(__has_extension)
#if __has_extension(blocks)

static void IteratorFunc(void *ptr, void (^block)(void *ptr)){block(ptr);}

void cpSpaceEachBody_b(cpSpace *space, void (^block)(cpBody *body)){
	cpSpaceEachBody(space, (cpSpaceBodyIteratorFunc)IteratorFunc, block);
}

void cpSpaceEachShape_b(cpSpace *space, void (^block)(cpShape *shape)){
	cpSpaceEachShape(space, (cpSpaceShapeIteratorFunc)IteratorFunc, block);
}

void cpSpaceEachConstraint_b(cpSpace *space, void (^block)(cpConstraint *constraint)){
	cpSpaceEachConstraint(space, (cpSpaceConstraintIteratorFunc)IteratorFunc, block);
}

static void BodyIteratorFunc(cpBody *body, void *ptr, void (^block)(void *ptr)){block(ptr);}

void cpBodyEachShape_b(cpBody *body, void (^block)(cpShape *shape)){
	cpBodyEachShape(body, (cpBodyShapeIteratorFunc)BodyIteratorFunc, block);
}

void cpBodyEachConstraint_b(cpBody *body, void (^block)(cpConstraint *constraint)){
	cpBodyEachConstraint(body, (cpBodyConstraintIteratorFunc)BodyIteratorFunc, block);
}

void cpBodyEachArbiter_b(cpBody *body, void (^block)(cpArbiter *arbiter)){
	cpBodyEachArbiter(body, (cpBodyArbiterIteratorFunc)BodyIteratorFunc, block);
}

static void NearestPointQueryIteratorFunc(cpShape *shape, cpFloat distance, cpVect point, cpSpaceNearestPointQueryBlock block){block(shape, distance, point);}
void cpSpaceNearestPointQuery_b(cpSpace *space, cpVect point, cpFloat maxDistance, cpLayers layers, cpGroup group, cpSpaceNearestPointQueryBlock block){
	cpSpaceNearestPointQuery(space, point, maxDistance, layers, group, (cpSpaceNearestPointQueryFunc)NearestPointQueryIteratorFunc, block);
}

static void SegmentQueryIteratorFunc(cpShape *shape, cpFloat t, cpVect n, cpSpaceSegmentQueryBlock block){block(shape, t, n);}
void cpSpaceSegmentQuery_b(cpSpace *space, cpVect start, cpVect end, cpLayers layers, cpGroup group, cpSpaceSegmentQueryBlock block){
	cpSpaceSegmentQuery(space, start, end, layers, group, (cpSpaceSegmentQueryFunc)SegmentQueryIteratorFunc, block);
}

void cpSpaceBBQuery_b(cpSpace *space, cpBB bb, cpLayers layers, cpGroup group, cpSpaceBBQueryBlock block){
	cpSpaceBBQuery(space, bb, layers, group, (cpSpaceBBQueryFunc)IteratorFunc, block);
}

static void ShapeQueryIteratorFunc(cpShape *shape, cpContactPointSet *points, cpSpaceShapeQueryBlock block){block(shape, points);}
cpBool cpSpaceShapeQuery_b(cpSpace *space, cpShape *shape, cpSpaceShapeQueryBlock block){
	return cpSpaceShapeQuery(space, shape, (cpSpaceShapeQueryFunc)ShapeQueryIteratorFunc, block);
}

#endif
#endif

#include "chipmunk_ffi.h"
