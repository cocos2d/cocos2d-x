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
#ifndef CHIPMUNK_PRIVATE_H
#define CHIPMUNK_PRIVATE_H
#ifdef CHIPMUNK_H
#error Cannot include chipmunk_private.h after chipmunk.h.
#endif

#define CP_ALLOW_PRIVATE_ACCESS 1
#include "chipmunk/chipmunk.h"

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


//MARK: cpHashSet

typedef cpBool (*cpHashSetEqlFunc)(void *ptr, void *elt);
typedef void *(*cpHashSetTransFunc)(void *ptr, void *data);

cpHashSet *cpHashSetNew(int size, cpHashSetEqlFunc eqlFunc);
void cpHashSetSetDefaultValue(cpHashSet *set, void *default_value);

void cpHashSetFree(cpHashSet *set);

int cpHashSetCount(cpHashSet *set);
void *cpHashSetInsert(cpHashSet *set, cpHashValue hash, void *ptr, cpHashSetTransFunc trans, void *data);
void *cpHashSetRemove(cpHashSet *set, cpHashValue hash, void *ptr);
void *cpHashSetFind(cpHashSet *set, cpHashValue hash, void *ptr);

typedef void (*cpHashSetIteratorFunc)(void *elt, void *data);
void cpHashSetEach(cpHashSet *set, cpHashSetIteratorFunc func, void *data);

typedef cpBool (*cpHashSetFilterFunc)(void *elt, void *data);
void cpHashSetFilter(cpHashSet *set, cpHashSetFilterFunc func, void *data);


//MARK: Bodies

struct cpBody {
	// Integration functions
	cpBodyVelocityFunc velocity_func;
	cpBodyPositionFunc position_func;
	
	// mass and it's inverse
	cpFloat m;
	cpFloat m_inv;
	
	// moment of inertia and it's inverse
	cpFloat i;
	cpFloat i_inv;
	
	// center of gravity
	cpVect cog;
	
	// position, velocity, force
	cpVect p;
	cpVect v;
	cpVect f;
	
	// Angle, angular velocity, torque (radians)
	cpFloat a;
	cpFloat w;
	cpFloat t;
	
	cpTransform transform;
	
	cpDataPointer userData;
	
	// "pseudo-velocities" used for eliminating overlap.
	// Erin Catto has some papers that talk about what these are.
	cpVect v_bias;
	cpFloat w_bias;
	
	cpSpace *space;
	
	cpShape *shapeList;
	cpArbiter *arbiterList;
	cpConstraint *constraintList;
	
	struct {
		cpBody *root;
		cpBody *next;
		cpFloat idleTime;
	} sleeping;
};

void cpBodyAddShape(cpBody *body, cpShape *shape);
void cpBodyRemoveShape(cpBody *body, cpShape *shape);

//void cpBodyAccumulateMassForShape(cpBody *body, cpShape *shape);
void cpBodyAccumulateMassFromShapes(cpBody *body);

void cpBodyRemoveConstraint(cpBody *body, cpConstraint *constraint);


//MARK: Spatial Index Functions

cpSpatialIndex *cpSpatialIndexInit(cpSpatialIndex *index, cpSpatialIndexClass *klass, cpSpatialIndexBBFunc bbfunc, cpSpatialIndex *staticIndex);


//MARK: Arbiters

enum cpArbiterState {
	// Arbiter is active and its the first collision.
	CP_ARBITER_STATE_FIRST_COLLISION,
	// Arbiter is active and its not the first collision.
	CP_ARBITER_STATE_NORMAL,
	// Collision has been explicitly ignored.
	// Either by returning false from a begin collision handler or calling cpArbiterIgnore().
	CP_ARBITER_STATE_IGNORE,
	// Collison is no longer active. A space will cache an arbiter for up to cpSpace.collisionPersistence more steps.
	CP_ARBITER_STATE_CACHED,
	// Collison arbiter is invalid because one of the shapes was removed.
	CP_ARBITER_STATE_INVALIDATED,
};

struct cpArbiterThread {
	struct cpArbiter *next, *prev;
};

struct cpContact {
	cpVect r1, r2;
	
	cpFloat nMass, tMass;
	cpFloat bounce; // TODO: look for an alternate bounce solution.

	cpFloat jnAcc, jtAcc, jBias;
	cpFloat bias;
	
	cpHashValue hash;
};

struct cpCollisionInfo {
	const cpShape *a, *b;
	cpCollisionID id;
	
	cpVect n;
	
	int count;
	// TODO Should this be a unique struct type?
	struct cpContact *arr;
};

struct cpArbiter {
	cpFloat e;
	cpFloat u;
	cpVect surface_vr;
	
	cpDataPointer data;
	
	const cpShape *a, *b;
	cpBody *body_a, *body_b;
	struct cpArbiterThread thread_a, thread_b;
	
	int count;
	struct cpContact *contacts;
	cpVect n;
	
	// Regular, wildcard A and wildcard B collision handlers.
	cpCollisionHandler *handler, *handlerA, *handlerB;
	cpBool swapped;
	
	cpTimestamp stamp;
	enum cpArbiterState state;
};

cpArbiter* cpArbiterInit(cpArbiter *arb, cpShape *a, cpShape *b);

static inline struct cpArbiterThread *
cpArbiterThreadForBody(cpArbiter *arb, cpBody *body)
{
	return (arb->body_a == body ? &arb->thread_a : &arb->thread_b);
}

void cpArbiterUnthread(cpArbiter *arb);

void cpArbiterUpdate(cpArbiter *arb, struct cpCollisionInfo *info, cpSpace *space);
void cpArbiterPreStep(cpArbiter *arb, cpFloat dt, cpFloat bias, cpFloat slop);
void cpArbiterApplyCachedImpulse(cpArbiter *arb, cpFloat dt_coef);
void cpArbiterApplyImpulse(cpArbiter *arb);


//MARK: Shapes/Collisions

struct cpShapeMassInfo {
	cpFloat m;
	cpFloat i;
	cpVect cog;
	cpFloat area;
};

typedef enum cpShapeType{
	CP_CIRCLE_SHAPE,
	CP_SEGMENT_SHAPE,
	CP_POLY_SHAPE,
	CP_NUM_SHAPES
} cpShapeType;

typedef cpBB (*cpShapeCacheDataImpl)(cpShape *shape, cpTransform transform);
typedef void (*cpShapeDestroyImpl)(cpShape *shape);
typedef void (*cpShapePointQueryImpl)(const cpShape *shape, cpVect p, cpPointQueryInfo *info);
typedef void (*cpShapeSegmentQueryImpl)(const cpShape *shape, cpVect a, cpVect b, cpFloat radius, cpSegmentQueryInfo *info);

typedef struct cpShapeClass cpShapeClass;

struct cpShapeClass {
	cpShapeType type;
	
	cpShapeCacheDataImpl cacheData;
	cpShapeDestroyImpl destroy;
	cpShapePointQueryImpl pointQuery;
	cpShapeSegmentQueryImpl segmentQuery;
};

struct cpShape {
	const cpShapeClass *klass;
	
	cpSpace *space;
	cpBody *body;
	struct cpShapeMassInfo massInfo;
	cpBB bb;
	
	cpBool sensor;
	
	cpFloat e;
	cpFloat u;
	cpVect surfaceV;

	cpDataPointer userData;
	
	cpCollisionType type;
	cpShapeFilter filter;
	
	cpShape *next;
	cpShape *prev;
	
	cpHashValue hashid;
};

struct cpCircleShape {
	cpShape shape;
	
	cpVect c, tc;
	cpFloat r;
};

struct cpSegmentShape {
	cpShape shape;
	
	cpVect a, b, n;
	cpVect ta, tb, tn;
	cpFloat r;
	
	cpVect a_tangent, b_tangent;
};

struct cpSplittingPlane {
	cpVect v0, n;
};

#define CP_POLY_SHAPE_INLINE_ALLOC 6

struct cpPolyShape {
	cpShape shape;
	
	cpFloat r;
	
	int count;
	// The untransformed planes are appended at the end of the transformed planes.
	struct cpSplittingPlane *planes;
	
	// Allocate a small number of splitting planes internally for simple poly.
	struct cpSplittingPlane _planes[2*CP_POLY_SHAPE_INLINE_ALLOC];
};

cpShape *cpShapeInit(cpShape *shape, const cpShapeClass *klass, cpBody *body, struct cpShapeMassInfo massInfo);

static inline cpBool
cpShapeActive(cpShape *shape)
{
	// checks if the shape is added to a shape list.
	// TODO could this just check the space now?
	return (shape->prev || (shape->body && shape->body->shapeList == shape));
}

// Note: This function returns contact points with r1/r2 in absolute coordinates, not body relative.
struct cpCollisionInfo cpCollide(const cpShape *a, const cpShape *b, cpCollisionID id, struct cpContact *contacts);

static inline void
CircleSegmentQuery(cpShape *shape, cpVect center, cpFloat r1, cpVect a, cpVect b, cpFloat r2, cpSegmentQueryInfo *info)
{
	cpVect da = cpvsub(a, center);
	cpVect db = cpvsub(b, center);
	cpFloat rsum = r1 + r2;
	
	cpFloat qa = cpvdot(da, da) - 2.0f*cpvdot(da, db) + cpvdot(db, db);
	cpFloat qb = cpvdot(da, db) - cpvdot(da, da);
	cpFloat det = qb*qb - qa*(cpvdot(da, da) - rsum*rsum);
	
	if(det >= 0.0f){
		cpFloat t = (-qb - cpfsqrt(det))/(qa);
		if(0.0f<= t && t <= 1.0f){
			cpVect n = cpvnormalize(cpvlerp(da, db, t));
			
			info->shape = shape;
			info->point = cpvsub(cpvlerp(a, b, t), cpvmult(n, r2));
			info->normal = n;
			info->alpha = t;
		}
	}
}

static inline cpBool
cpShapeFilterReject(cpShapeFilter a, cpShapeFilter b)
{
	// Reject the collision if:
	return (
		// They are in the same non-zero group.
		(a.group != 0 && a.group == b.group) ||
		// One of the category/mask combinations fails.
		(a.categories & b.mask) == 0 ||
		(b.categories & a.mask) == 0
	);
}

void cpLoopIndexes(const cpVect *verts, int count, int *start, int *end);


//MARK: Constraints
// TODO naming conventions here

typedef void (*cpConstraintPreStepImpl)(cpConstraint *constraint, cpFloat dt);
typedef void (*cpConstraintApplyCachedImpulseImpl)(cpConstraint *constraint, cpFloat dt_coef);
typedef void (*cpConstraintApplyImpulseImpl)(cpConstraint *constraint, cpFloat dt);
typedef cpFloat (*cpConstraintGetImpulseImpl)(cpConstraint *constraint);

typedef struct cpConstraintClass {
	cpConstraintPreStepImpl preStep;
	cpConstraintApplyCachedImpulseImpl applyCachedImpulse;
	cpConstraintApplyImpulseImpl applyImpulse;
	cpConstraintGetImpulseImpl getImpulse;
} cpConstraintClass;

struct cpConstraint {
	const cpConstraintClass *klass;
	
	cpSpace *space;
	
	cpBody *a, *b;
	cpConstraint *next_a, *next_b;
	
	cpFloat maxForce;
	cpFloat errorBias;
	cpFloat maxBias;
	
	cpBool collideBodies;
	
	cpConstraintPreSolveFunc preSolve;
	cpConstraintPostSolveFunc postSolve;
	
	cpDataPointer userData;
};

struct cpPinJoint {
	cpConstraint constraint;
	cpVect anchorA, anchorB;
	cpFloat dist;
	
	cpVect r1, r2;
	cpVect n;
	cpFloat nMass;
	
	cpFloat jnAcc;
	cpFloat bias;
};

struct cpSlideJoint {
	cpConstraint constraint;
	cpVect anchorA, anchorB;
	cpFloat min, max;
	
	cpVect r1, r2;
	cpVect n;
	cpFloat nMass;
	
	cpFloat jnAcc;
	cpFloat bias;
};

struct cpPivotJoint {
	cpConstraint constraint;
	cpVect anchorA, anchorB;
	
	cpVect r1, r2;
	cpMat2x2 k;
	
	cpVect jAcc;
	cpVect bias;
};

struct cpGrooveJoint {
	cpConstraint constraint;
	cpVect grv_n, grv_a, grv_b;
	cpVect  anchorB;
	
	cpVect grv_tn;
	cpFloat clamp;
	cpVect r1, r2;
	cpMat2x2 k;
	
	cpVect jAcc;
	cpVect bias;
};

struct cpDampedSpring {
	cpConstraint constraint;
	cpVect anchorA, anchorB;
	cpFloat restLength;
	cpFloat stiffness;
	cpFloat damping;
	cpDampedSpringForceFunc springForceFunc;
	
	cpFloat target_vrn;
	cpFloat v_coef;
	
	cpVect r1, r2;
	cpFloat nMass;
	cpVect n;
	
	cpFloat jAcc;
};

struct cpDampedRotarySpring {
	cpConstraint constraint;
	cpFloat restAngle;
	cpFloat stiffness;
	cpFloat damping;
	cpDampedRotarySpringTorqueFunc springTorqueFunc;
	
	cpFloat target_wrn;
	cpFloat w_coef;
	
	cpFloat iSum;
	cpFloat jAcc;
};

struct cpRotaryLimitJoint {
	cpConstraint constraint;
	cpFloat min, max;
	
	cpFloat iSum;
		
	cpFloat bias;
	cpFloat jAcc;
};

struct cpRatchetJoint {
	cpConstraint constraint;
	cpFloat angle, phase, ratchet;
	
	cpFloat iSum;
		
	cpFloat bias;
	cpFloat jAcc;
};

struct cpGearJoint {
	cpConstraint constraint;
	cpFloat phase, ratio;
	cpFloat ratio_inv;
	
	cpFloat iSum;
		
	cpFloat bias;
	cpFloat jAcc;
};

struct cpSimpleMotor {
	cpConstraint constraint;
	cpFloat rate;
	
	cpFloat iSum;
		
	cpFloat jAcc;
};

void cpConstraintInit(cpConstraint *constraint, const struct cpConstraintClass *klass, cpBody *a, cpBody *b);

static inline void
cpConstraintActivateBodies(cpConstraint *constraint)
{
	cpBody *a = constraint->a; cpBodyActivate(a);
	cpBody *b = constraint->b; cpBodyActivate(b);
}

static inline cpVect
relative_velocity(cpBody *a, cpBody *b, cpVect r1, cpVect r2){
	cpVect v1_sum = cpvadd(a->CP_PRIVATE(v), cpvmult(cpvperp(r1), a->CP_PRIVATE(w)));
	cpVect v2_sum = cpvadd(b->CP_PRIVATE(v), cpvmult(cpvperp(r2), b->CP_PRIVATE(w)));
	
	return cpvsub(v2_sum, v1_sum);
}

static inline cpFloat
normal_relative_velocity(cpBody *a, cpBody *b, cpVect r1, cpVect r2, cpVect n){
	return cpvdot(relative_velocity(a, b, r1, r2), n);
}

static inline void
apply_impulse(cpBody *body, cpVect j, cpVect r){
	body->CP_PRIVATE(v) = cpvadd(body->CP_PRIVATE(v), cpvmult(j, body->CP_PRIVATE(m_inv)));
	body->CP_PRIVATE(w) += body->CP_PRIVATE(i_inv)*cpvcross(r, j);
}

static inline void
apply_impulses(cpBody *a , cpBody *b, cpVect r1, cpVect r2, cpVect j)
{
	apply_impulse(a, cpvneg(j), r1);
	apply_impulse(b, j, r2);
}

static inline void
apply_bias_impulse(cpBody *body, cpVect j, cpVect r)
{
	body->CP_PRIVATE(v_bias) = cpvadd(body->CP_PRIVATE(v_bias), cpvmult(j, body->CP_PRIVATE(m_inv)));
	body->CP_PRIVATE(w_bias) += body->CP_PRIVATE(i_inv)*cpvcross(r, j);
}

static inline void
apply_bias_impulses(cpBody *a , cpBody *b, cpVect r1, cpVect r2, cpVect j)
{
	apply_bias_impulse(a, cpvneg(j), r1);
	apply_bias_impulse(b, j, r2);
}

static inline cpFloat
k_scalar_body(cpBody *body, cpVect r, cpVect n)
{
	cpFloat rcn = cpvcross(r, n);
	return body->CP_PRIVATE(m_inv) + body->CP_PRIVATE(i_inv)*rcn*rcn;
}

static inline cpFloat
k_scalar(cpBody *a, cpBody *b, cpVect r1, cpVect r2, cpVect n)
{
	cpFloat value = k_scalar_body(a, r1, n) + k_scalar_body(b, r2, n);
	cpAssertSoft(value != 0.0, "Unsolvable collision or constraint.");
	
	return value;
}

static inline cpMat2x2
k_tensor(cpBody *a, cpBody *b, cpVect r1, cpVect r2)
{
	cpFloat m_sum = a->CP_PRIVATE(m_inv) + b->CP_PRIVATE(m_inv);
	
	// start with Identity*m_sum
	cpFloat k11 = m_sum, k12 = 0.0f;
	cpFloat k21 = 0.0f,  k22 = m_sum;
	
	// add the influence from r1
	cpFloat a_i_inv = a->CP_PRIVATE(i_inv);
	cpFloat r1xsq =  r1.x * r1.x * a_i_inv;
	cpFloat r1ysq =  r1.y * r1.y * a_i_inv;
	cpFloat r1nxy = -r1.x * r1.y * a_i_inv;
	k11 += r1ysq; k12 += r1nxy;
	k21 += r1nxy; k22 += r1xsq;
	
	// add the influnce from r2
	cpFloat b_i_inv = b->CP_PRIVATE(i_inv);
	cpFloat r2xsq =  r2.x * r2.x * b_i_inv;
	cpFloat r2ysq =  r2.y * r2.y * b_i_inv;
	cpFloat r2nxy = -r2.x * r2.y * b_i_inv;
	k11 += r2ysq; k12 += r2nxy;
	k21 += r2nxy; k22 += r2xsq;
	
	// invert
	cpFloat det = k11*k22 - k12*k21;
	cpAssertSoft(det != 0.0, "Unsolvable constraint.");
	
	cpFloat det_inv = 1.0f/det;
	return cpMat2x2New(
		 k22*det_inv, -k12*det_inv,
		-k21*det_inv,  k11*det_inv
 	);
}

static inline cpFloat
bias_coef(cpFloat errorBias, cpFloat dt)
{
	return 1.0f - cpfpow(errorBias, dt);
}


//MARK: Spaces

typedef struct cpContactBufferHeader cpContactBufferHeader;
typedef void (*cpSpaceArbiterApplyImpulseFunc)(cpArbiter *arb);

struct cpSpace {
	int iterations;
	
	cpVect gravity;
	cpFloat damping;
	
	cpFloat idleSpeedThreshold;
	cpFloat sleepTimeThreshold;
	
	cpFloat collisionSlop;
	cpFloat collisionBias;
	cpTimestamp collisionPersistence;
	
	cpDataPointer userData;
	
	cpTimestamp stamp;
	cpFloat curr_dt;

	cpArray *dynamicBodies;
	cpArray *staticBodies;
	cpArray *rousedBodies;
	cpArray *sleepingComponents;
	
	cpHashValue shapeIDCounter;
	cpSpatialIndex *staticShapes;
	cpSpatialIndex *dynamicShapes;
	
	cpArray *constraints;
	
	cpArray *arbiters;
	cpContactBufferHeader *contactBuffersHead;
	cpHashSet *cachedArbiters;
	cpArray *pooledArbiters;
	
	cpArray *allocatedBuffers;
	unsigned int locked;
	
	cpBool usesWildcards;
	cpHashSet *collisionHandlers;
	cpCollisionHandler defaultHandler;
	
	cpBool skipPostStep;
	cpArray *postStepCallbacks;
	
	cpBody *staticBody;
	cpBody _staticBody;
};

#define cpAssertSpaceUnlocked(space) \
	cpAssertHard(!space->locked, \
		"This operation cannot be done safely during a call to cpSpaceStep() or during a query. " \
		"Put these calls into a post-step callback." \
	);

void cpSpaceSetStaticBody(cpSpace *space, cpBody *body);

extern cpCollisionHandler cpCollisionHandlerDoNothing;

void cpSpaceProcessComponents(cpSpace *space, cpFloat dt);

void cpSpacePushFreshContactBuffer(cpSpace *space);
struct cpContact *cpContactBufferGetArray(cpSpace *space);
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

static inline void
cpSpaceUncacheArbiter(cpSpace *space, cpArbiter *arb)
{
	const cpShape *a = arb->a, *b = arb->b;
	const cpShape *shape_pair[] = {a, b};
	cpHashValue arbHashID = CP_HASH_PAIR((cpHashValue)a, (cpHashValue)b);
	cpHashSetRemove(space->cachedArbiters, arbHashID, shape_pair);
	cpArrayDeleteObj(space->arbiters, arb);
}

static inline cpArray *
cpSpaceArrayForBodyType(cpSpace *space, cpBodyType type)
{
	return (type == CP_BODY_TYPE_STATIC ? space->staticBodies : space->dynamicBodies);
}

void cpShapeUpdateFunc(cpShape *shape, void *unused);
cpCollisionID cpSpaceCollideShapes(cpShape *a, cpShape *b, cpCollisionID id, cpSpace *space);


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
	for(cpBody *var = root; var; var = var->sleeping.next)

#endif
