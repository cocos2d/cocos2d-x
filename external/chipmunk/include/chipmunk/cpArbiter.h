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

/// @defgroup cpArbiter cpArbiter
/// The cpArbiter struct controls pairs of colliding shapes.
/// They are also used in conjuction with collision handler callbacks
/// allowing you to retrieve information on the collision and control it.
/// @{

/// Collision begin event function callback type.
/// Returning false from a begin callback causes the collision to be ignored until
/// the the separate callback is called when the objects stop colliding.
typedef cpBool (*cpCollisionBeginFunc)(cpArbiter *arb, cpSpace *space, void *data);
/// Collision pre-solve event function callback type.
/// Returning false from a pre-step callback causes the collision to be ignored until the next step.
typedef cpBool (*cpCollisionPreSolveFunc)(cpArbiter *arb, cpSpace *space, void *data);
/// Collision post-solve event function callback type.
typedef void (*cpCollisionPostSolveFunc)(cpArbiter *arb, cpSpace *space, void *data);
/// Collision separate event function callback type.
typedef void (*cpCollisionSeparateFunc)(cpArbiter *arb, cpSpace *space, void *data);

/// @private
struct cpCollisionHandler {
	cpCollisionType a;
	cpCollisionType b;
	cpCollisionBeginFunc begin;
	cpCollisionPreSolveFunc preSolve;
	cpCollisionPostSolveFunc postSolve;
	cpCollisionSeparateFunc separate;
	void *data;
};

typedef struct cpContact cpContact;

#define CP_MAX_CONTACTS_PER_ARBITER 2

/// @private
typedef enum cpArbiterState {
	// Arbiter is active and its the first collision.
	cpArbiterStateFirstColl,
	// Arbiter is active and its not the first collision.
	cpArbiterStateNormal,
	// Collision has been explicitly ignored.
	// Either by returning false from a begin collision handler or calling cpArbiterIgnore().
	cpArbiterStateIgnore,
	// Collison is no longer active. A space will cache an arbiter for up to cpSpace.collisionPersistence more steps.
	cpArbiterStateCached,
} cpArbiterState;

/// @private
struct cpArbiterThread {
	// Links to next and previous arbiters in the contact graph.
	struct cpArbiter *next, *prev;
};

/// A colliding pair of shapes.
struct cpArbiter {
	/// Calculated value to use for the elasticity coefficient.
	/// Override in a pre-solve collision handler for custom behavior.
	cpFloat e;
	/// Calculated value to use for the friction coefficient.
	/// Override in a pre-solve collision handler for custom behavior.
	cpFloat u;
	 /// Calculated value to use for applying surface velocities.
	/// Override in a pre-solve collision handler for custom behavior.
	cpVect surface_vr;
	
	/// User definable data pointer.
	/// The value will persist for the pair of shapes until the separate() callback is called.
	/// NOTE: If you need to clean up this pointer, you should implement the separate() callback to do it.
	cpDataPointer data;
	
	CP_PRIVATE(cpShape *a);
	CP_PRIVATE(cpShape *b);
	CP_PRIVATE(cpBody *body_a);
	CP_PRIVATE(cpBody *body_b);
	
	CP_PRIVATE(struct cpArbiterThread thread_a);
	CP_PRIVATE(struct cpArbiterThread thread_b);
	
	CP_PRIVATE(int numContacts);
	CP_PRIVATE(cpContact *contacts);
	
	CP_PRIVATE(cpTimestamp stamp);
	CP_PRIVATE(cpCollisionHandler *handler);
	CP_PRIVATE(cpBool swappedColl);
	CP_PRIVATE(cpArbiterState state);
};

#define CP_DefineArbiterStructGetter(type, member, name) \
static inline type cpArbiterGet##name(const cpArbiter *arb){return arb->member;}

#define CP_DefineArbiterStructSetter(type, member, name) \
static inline void cpArbiterSet##name(cpArbiter *arb, type value){arb->member = value;}

#define CP_DefineArbiterStructProperty(type, member, name) \
CP_DefineArbiterStructGetter(type, member, name) \
CP_DefineArbiterStructSetter(type, member, name)

CP_DefineArbiterStructProperty(cpFloat, e, Elasticity)
CP_DefineArbiterStructProperty(cpFloat, u, Friction)

// Get the relative surface velocity of the two shapes in contact.
cpVect cpArbiterGetSurfaceVelocity(cpArbiter *arb);

// Override the relative surface velocity of the two shapes in contact.
// By default this is calculated to be the difference of the two
// surface velocities clamped to the tangent plane.
void cpArbiterSetSurfaceVelocity(cpArbiter *arb, cpVect vr);

CP_DefineArbiterStructProperty(cpDataPointer, data, UserData)

/// Calculate the total impulse that was applied by this arbiter.
/// This function should only be called from a post-solve, post-step or cpBodyEachArbiter callback.
cpVect cpArbiterTotalImpulse(const cpArbiter *arb);
/// Calculate the total impulse including the friction that was applied by this arbiter.
/// This function should only be called from a post-solve, post-step or cpBodyEachArbiter callback.
cpVect cpArbiterTotalImpulseWithFriction(const cpArbiter *arb);
/// Calculate the amount of energy lost in a collision including static, but not dynamic friction.
/// This function should only be called from a post-solve, post-step or cpBodyEachArbiter callback.
cpFloat cpArbiterTotalKE(const cpArbiter *arb);


/// Causes a collision pair to be ignored as if you returned false from a begin callback.
/// If called from a pre-step callback, you will still need to return false
/// if you want it to be ignored in the current step.
void cpArbiterIgnore(cpArbiter *arb);

/// Return the colliding shapes involved for this arbiter.
/// The order of their cpSpace.collision_type values will match
/// the order set when the collision handler was registered.
static inline void cpArbiterGetShapes(const cpArbiter *arb, cpShape **a, cpShape **b)
{
	if(arb->CP_PRIVATE(swappedColl)){
		(*a) = arb->CP_PRIVATE(b), (*b) = arb->CP_PRIVATE(a);
	} else {
		(*a) = arb->CP_PRIVATE(a), (*b) = arb->CP_PRIVATE(b);
	}
}
/// A macro shortcut for defining and retrieving the shapes from an arbiter.
#define CP_ARBITER_GET_SHAPES(__arb__, __a__, __b__) cpShape *__a__, *__b__; cpArbiterGetShapes(__arb__, &__a__, &__b__);

/// Return the colliding bodies involved for this arbiter.
/// The order of the cpSpace.collision_type the bodies are associated with values will match
/// the order set when the collision handler was registered.
static inline void cpArbiterGetBodies(const cpArbiter *arb, cpBody **a, cpBody **b)
{
	CP_ARBITER_GET_SHAPES(arb, shape_a, shape_b);
	(*a) = shape_a->body;
	(*b) = shape_b->body;
}
/// A macro shortcut for defining and retrieving the bodies from an arbiter.
#define CP_ARBITER_GET_BODIES(__arb__, __a__, __b__) cpBody *__a__, *__b__; cpArbiterGetBodies(__arb__, &__a__, &__b__);

/// A struct that wraps up the important collision data for an arbiter.
typedef struct cpContactPointSet {
	/// The number of contact points in the set.
	int count;
	
	/// The array of contact points.
	struct {
		/// The position of the contact point.
		cpVect point;
		/// The normal of the contact point.
		cpVect normal;
		/// The depth of the contact point.
		cpFloat dist;
	} points[CP_MAX_CONTACTS_PER_ARBITER];
} cpContactPointSet;

/// Return a contact set from an arbiter.
cpContactPointSet cpArbiterGetContactPointSet(const cpArbiter *arb);

/// Replace the contact point set for an arbiter.
/// This can be a very powerful feature, but use it with caution!
void cpArbiterSetContactPointSet(cpArbiter *arb, cpContactPointSet *set);

/// Returns true if this is the first step a pair of objects started colliding.
cpBool cpArbiterIsFirstContact(const cpArbiter *arb);
/// Get the number of contact points for this arbiter.
int cpArbiterGetCount(const cpArbiter *arb);
/// Get the normal of the @c ith contact point.
cpVect cpArbiterGetNormal(const cpArbiter *arb, int i);
/// Get the position of the @c ith contact point.
cpVect cpArbiterGetPoint(const cpArbiter *arb, int i);
/// Get the depth of the @c ith contact point.
cpFloat cpArbiterGetDepth(const cpArbiter *arb, int i);

/// @}
