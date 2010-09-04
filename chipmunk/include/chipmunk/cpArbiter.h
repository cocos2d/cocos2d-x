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
 
 struct cpArbiter;
 struct cpSpace;
 struct cpCollisionHandler;

// Determines how fast penetrations resolve themselves.
extern cpFloat cp_bias_coef;
// Amount of allowed penetration. Used to reduce vibrating contacts.
extern cpFloat cp_collision_slop;

// Data structure for contact points.
typedef struct cpContact {
	// Contact point and normal.
	cpVect p, n;
	// Penetration distance.
	cpFloat dist;
	
	// Calculated by cpArbiterPreStep().
	cpVect r1, r2;
	cpFloat nMass, tMass, bounce;

	// Persistant contact information.
	cpFloat jnAcc, jtAcc, jBias;
	cpFloat bias;
	
	// Hash value used to (mostly) uniquely identify a contact.
	cpHashValue hash;
} cpContact;

// Contacts are always allocated in groups.
cpContact* cpContactInit(cpContact *con, cpVect p, cpVect n, cpFloat dist, cpHashValue hash);

// Sum the contact impulses. (Can be used after cpSpaceStep() returns)
cpVect cpContactsSumImpulses(cpContact *contacts, int numContacts);
cpVect cpContactsSumImpulsesWithFriction(cpContact *contacts, int numContacts);

typedef enum cpArbiterState {
	cpArbiterStateNormal,
	cpArbiterStateFirstColl,
	cpArbiterStateIgnore,
} cpArbiterState;

// Data structure for tracking collisions between shapes.
typedef struct cpArbiter {
	// Information on the contact points between the objects.
	int numContacts;
	cpContact *contacts;
	
	// The two shapes involved in the collision.
	// These variables are NOT in the order defined by the collision handler.
	cpShape *private_a, *private_b;
	
	// Calculated before calling the pre-solve collision handler
	// Override them with custom values if you want specialized behavior
	cpFloat e;
	cpFloat u;
	 // Used for surface_v calculations, implementation may change
	cpVect surface_vr;
	
	// Time stamp of the arbiter. (from cpSpace)
	int stamp;
	
	struct cpCollisionHandler *handler;
	
	// Are the shapes swapped in relation to the collision handler?
	char swappedColl;
	char state;
} cpArbiter;

// Arbiters are allocated in large buffers by the space and don't require a destroy function
cpArbiter* cpArbiterInit(cpArbiter *arb, cpShape *a, cpShape *b);

// These functions are all intended to be used internally.
// Inject new contact points into the arbiter while preserving contact history.
void cpArbiterUpdate(cpArbiter *arb, cpContact *contacts, int numContacts, struct cpCollisionHandler *handler, cpShape *a, cpShape *b);
// Precalculate values used by the solver.
void cpArbiterPreStep(cpArbiter *arb, cpFloat dt_inv);
void cpArbiterApplyCachedImpulse(cpArbiter *arb);
// Run an iteration of the solver on the arbiter.
void cpArbiterApplyImpulse(cpArbiter *arb, cpFloat eCoef);

// Arbiter Helper Functions
cpVect cpArbiterTotalImpulse(cpArbiter *arb);
cpVect cpArbiterTotalImpulseWithFriction(cpArbiter *arb);
void cpArbiterIgnore(cpArbiter *arb);


static inline void
cpArbiterGetShapes(cpArbiter *arb, cpShape **a, cpShape **b)
{
	if(arb->swappedColl){
		(*a) = arb->private_b, (*b) = arb->private_a;
	} else {
		(*a) = arb->private_a, (*b) = arb->private_b;
	}
}
#define CP_ARBITER_GET_SHAPES(arb, a, b) cpShape *a, *b; cpArbiterGetShapes(arb, &a, &b);

static inline int
cpArbiterIsFirstContact(cpArbiter *arb)
{
	return arb->state == cpArbiterStateFirstColl;
}

static inline cpVect
cpArbiterGetNormal(cpArbiter *arb, int i)
{
	cpVect n = arb->contacts[i].n;
	return arb->swappedColl ? cpvneg(n) : n;
}

static inline cpVect
cpArbiterGetPoint(cpArbiter *arb, int i)
{
	return arb->contacts[i].p;
}
