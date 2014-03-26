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

#define CP_ALLOW_PRIVATE_ACCESS 1
#include "chipmunk.h"

#define CP_HASH_COEF (3344921057ul)
#define CP_HASH_PAIR(A, B) ((cpHashValue)(A)*CP_HASH_COEF ^ (cpHashValue)(B)*CP_HASH_COEF)

// TODO: Eww. Magic numbers.
#define MAGIC_EPSILON 1e-5

//MARK: cpArray

struct cpArray {
	int num, max;
	void **arr;
};

cpArray *cpArrayNew(int size);

void cpArrayFree(cpArray *arr);

void cpArrayPush(cpArray *arr, void *object);
void *cpArrayPop(cpArray *arr);
void cpArrayDeleteObj(cpArray *arr, void *obj);
cpBool cpArrayContains(cpArray *arr, void *ptr);

void cpArrayFreeEach(cpArray *arr, void (freeFunc)(void*));


//MARK: Foreach loops

static inline cpConstraint *
cpConstraintNext(cpConstraint *node, cpBody *body)
{
	return (node->a == body ? node->next_a : node->next_b);
}

#define CP_BODY_FOREACH_CONSTRAINT(bdy, var)\
	for(cpConstraint *var = bdy->constraintList; var; var = cpConstraintNext(var, bdy))

static inline cpArbiter *
cpArbiterNext(cpArbiter *node, cpBody *body)
{
	return (node->body_a == body ? node->thread_a.next : node->thread_b.next);
}

#define CP_BODY_FOREACH_ARBITER(bdy, var)\
	for(cpArbiter *var = bdy->arbiterList; var; var = cpArbiterNext(var, bdy))

#define CP_BODY_FOREACH_SHAPE(body, var)\
	for(cpShape *var = body->shapeList; var; var = var->next)

#define CP_BODY_FOREACH_COMPONENT(root, var)\
	for(cpBody *var = root; var; var = var->node.next)


//MARK: cpHashSet

typedef cpBool (*cpHashSetEqlFunc)(void *ptr, void *elt);
typedef void *(*cpHashSetTransFunc)(void *ptr, void *data);

cpHashSet *cpHashSetNew(int size, cpHashSetEqlFunc eqlFunc);
void cpHashSetSetDefaultValue(cpHashSet *set, void *default_value);

void cpHashSetFree(cpHashSet *set);

int cpHashSetCount(cpHashSet *set);
void *cpHashSetInsert(cpHashSet *set, cpHashValue hash, void *ptr, void *data, cpHashSetTransFunc trans);
void *cpHashSetRemove(cpHashSet *set, cpHashValue hash, void *ptr);
void *cpHashSetFind(cpHashSet *set, cpHashValue hash, void *ptr);

typedef void (*cpHashSetIteratorFunc)(void *elt, void *data);
void cpHashSetEach(cpHashSet *set, cpHashSetIteratorFunc func, void *data);

typedef cpBool (*cpHashSetFilterFunc)(void *elt, void *data);
void cpHashSetFilter(cpHashSet *set, cpHashSetFilterFunc func, void *data);


//MARK: Body Functions

void cpBodyAddShape(cpBody *body, cpShape *shape);
void cpBodyRemoveShape(cpBody *body, cpShape *shape);
void cpBodyRemoveConstraint(cpBody *body, cpConstraint *constraint);


//MARK: Shape/Collision Functions

// TODO should move this to the cpVect API. It's pretty useful.
static inline cpVect
cpClosetPointOnSegment(const cpVect p, const cpVect a, const cpVect b)
{
	cpVect delta = cpvsub(a, b);
	cpFloat t = cpfclamp01(cpvdot(delta, cpvsub(p, b))/cpvlengthsq(delta));
	return cpvadd(b, cpvmult(delta, t));
}

cpShape* cpShapeInit(cpShape *shape, const cpShapeClass *klass, cpBody *body);

static inline cpBool
cpShapeActive(cpShape *shape)
{
	return shape->prev || (shape->body && shape->body->shapeList == shape);
}

int cpCollideShapes(const cpShape *a, const cpShape *b, cpCollisionID *id, cpContact *arr);

static inline void
CircleSegmentQuery(cpShape *shape, cpVect center, cpFloat r, cpVect a, cpVect b, cpSegmentQueryInfo *info)
{
	cpVect da = cpvsub(a, center);
	cpVect db = cpvsub(b, center);
	
	cpFloat qa = cpvdot(da, da) - 2.0f*cpvdot(da, db) + cpvdot(db, db);
	cpFloat qb = -2.0f*cpvdot(da, da) + 2.0f*cpvdot(da, db);
	cpFloat qc = cpvdot(da, da) - r*r;
	
	cpFloat det = qb*qb - 4.0f*qa*qc;
	
	if(det >= 0.0f){
		cpFloat t = (-qb - cpfsqrt(det))/(2.0f*qa);
		if(0.0f<= t && t <= 1.0f){
			info->shape = shape;
			info->t = t;
			info->n = cpvnormalize(cpvlerp(da, db, t));
		}
	}
}

// TODO doesn't really need to be inline, but need a better place to put this function
static inline cpSplittingPlane
cpSplittingPlaneNew(cpVect a, cpVect b)
{
	cpVect n = cpvnormalize(cpvperp(cpvsub(b, a)));
	cpSplittingPlane plane = {n, cpvdot(n, a)};
	return plane;
}

static inline cpFloat
cpSplittingPlaneCompare(cpSplittingPlane plane, cpVect v)
{
	return cpvdot(plane.n, v) - plane.d;
}

void cpLoopIndexes(cpVect *verts, int count, int *start, int *end);


//MARK: Spatial Index Functions

cpSpatialIndex *cpSpatialIndexInit(cpSpatialIndex *index, cpSpatialIndexClass *klass, cpSpatialIndexBBFunc bbfunc, cpSpatialIndex *staticIndex);


//MARK: Space Functions

extern cpCollisionHandler cpDefaultCollisionHandler;
void cpSpaceProcessComponents(cpSpace *space, cpFloat dt);

void cpSpacePushFreshContactBuffer(cpSpace *space);
cpContact *cpContactBufferGetArray(cpSpace *space);
void cpSpacePushContacts(cpSpace *space, int count);

typedef struct cpPostStepCallback {
	cpPostStepFunc func;
	void *key;
	void *data;
} cpPostStepCallback;

cpPostStepCallback *cpSpaceGetPostStepCallback(cpSpace *space, void *key);

cpBool cpSpaceArbiterSetFilter(cpArbiter *arb, cpSpace *space);
void cpSpaceFilterArbiters(cpSpace *space, cpBody *body, cpShape *filter);

void cpSpaceActivateBody(cpSpace *space, cpBody *body);
void cpSpaceLock(cpSpace *space);
void cpSpaceUnlock(cpSpace *space, cpBool runPostStep);

static inline cpCollisionHandler *
cpSpaceLookupHandler(cpSpace *space, cpCollisionType a, cpCollisionType b)
{
	cpCollisionType types[] = {a, b};
	return (cpCollisionHandler *)cpHashSetFind(space->collisionHandlers, CP_HASH_PAIR(a, b), types);
}

static inline void
cpSpaceUncacheArbiter(cpSpace *space, cpArbiter *arb)
{
	cpShape *a = arb->a, *b = arb->b;
	cpShape *shape_pair[] = {a, b};
	cpHashValue arbHashID = CP_HASH_PAIR((cpHashValue)a, (cpHashValue)b);
	cpHashSetRemove(space->cachedArbiters, arbHashID, shape_pair);
	cpArrayDeleteObj(space->arbiters, arb);
}

void cpShapeUpdateFunc(cpShape *shape, void *unused);
cpCollisionID cpSpaceCollideShapes(cpShape *a, cpShape *b, cpCollisionID id, cpSpace *space);


//MARK: Arbiters

struct cpContact {
	cpVect p, n;
	cpFloat dist;
	
	cpVect r1, r2;
	cpFloat nMass, tMass, bounce;

	cpFloat jnAcc, jtAcc, jBias;
	cpFloat bias;
	
	cpHashValue hash;
};

cpContact* cpContactInit(cpContact *con, cpVect p, cpVect n, cpFloat dist, cpHashValue hash);
cpArbiter* cpArbiterInit(cpArbiter *arb, cpShape *a, cpShape *b);

static inline void
cpArbiterCallSeparate(cpArbiter *arb, cpSpace *space)
{
	// The handler needs to be looked up again as the handler cached on the arbiter may have been deleted since the last step.
	cpCollisionHandler *handler = cpSpaceLookupHandler(space, arb->a->collision_type, arb->b->collision_type);
	handler->separate(arb, space, handler->data);
}

static inline struct cpArbiterThread *
cpArbiterThreadForBody(cpArbiter *arb, cpBody *body)
{
	return (arb->body_a == body ? &arb->thread_a : &arb->thread_b);
}

void cpArbiterUnthread(cpArbiter *arb);

void cpArbiterUpdate(cpArbiter *arb, cpContact *contacts, int numContacts, struct cpCollisionHandler *handler, cpShape *a, cpShape *b);
void cpArbiterPreStep(cpArbiter *arb, cpFloat dt, cpFloat bias, cpFloat slop);
void cpArbiterApplyCachedImpulse(cpArbiter *arb, cpFloat dt_coef);
void cpArbiterApplyImpulse(cpArbiter *arb);
