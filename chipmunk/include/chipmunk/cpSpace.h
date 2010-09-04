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

struct cpSpace;

// Number of frames that contact information should persist.
extern int cp_contact_persistence;

// User collision handler function types.
typedef int (*cpCollisionBeginFunc)(cpArbiter *arb, struct cpSpace *space, void *data);
typedef int (*cpCollisionPreSolveFunc)(cpArbiter *arb, struct cpSpace *space, void *data);
typedef void (*cpCollisionPostSolveFunc)(cpArbiter *arb, struct cpSpace *space, void *data);
typedef void (*cpCollisionSeparateFunc)(cpArbiter *arb, struct cpSpace *space, void *data);

// Structure for holding collision pair function information.
// Used internally.
typedef struct cpCollisionHandler {
	cpCollisionType a;
	cpCollisionType b;
	cpCollisionBeginFunc begin;
	cpCollisionPreSolveFunc preSolve;
	cpCollisionPostSolveFunc postSolve;
	cpCollisionSeparateFunc separate;
	void *data;
} cpCollisionHandler;

#define CP_MAX_CONTACTS_PER_ARBITER 6
typedef struct cpContactBufferHeader {
	int stamp;
	struct cpContactBufferHeader *next;
	unsigned int numContacts;
} cpContactBufferHeader;

typedef struct cpSpace{
	// *** User definable fields
	
	// Number of iterations to use in the impulse solver to solve contacts.
	int iterations;
	
	// Number of iterations to use in the impulse solver to solve elastic collisions.
	int elasticIterations;
	
	// Default gravity to supply when integrating rigid body motions.
	cpVect gravity;
	
	// Default damping to supply when integrating rigid body motions.
	cpFloat damping;
	
	// *** Internally Used Fields
	
	// When the space is locked, you should not add or remove objects;
	int locked;
	
	// Time stamp. Is incremented on every call to cpSpaceStep().
	int stamp;

	// The static and active shape spatial hashes.
	cpSpaceHash *staticShapes;
	cpSpaceHash *activeShapes;
	
	// List of bodies in the system.
	cpArray *bodies;
	
	// List of active arbiters for the impulse solver.
	cpArray *arbiters, *pooledArbiters;
	
	// Linked list ring of contact buffers.
	// Head is the current buffer. Tail is the oldest buffer.
	// The list points in the direction of tail->head.
	cpContactBufferHeader *contactBuffersHead, *contactBuffersTail;
	
	// List of buffers to be free()ed when destroying the space.
	cpArray *allocatedBuffers;
	
	// Persistant contact set.
	cpHashSet *contactSet;
	
	// List of constraints in the system.
	cpArray *constraints;
	
	// Set of collisionpair functions.
	cpHashSet *collFuncSet;
	// Default collision handler.
	cpCollisionHandler defaultHandler;
	
	cpHashSet *postStepCallbacks;
} cpSpace;

// Basic allocation/destruction functions.
cpSpace* cpSpaceAlloc(void);
cpSpace* cpSpaceInit(cpSpace *space);
cpSpace* cpSpaceNew(void);

void cpSpaceDestroy(cpSpace *space);
void cpSpaceFree(cpSpace *space);

// Convenience function. Frees all referenced entities. (bodies, shapes and constraints)
void cpSpaceFreeChildren(cpSpace *space);

// Collision handler management functions.
void cpSpaceSetDefaultCollisionHandler(
	cpSpace *space,
	cpCollisionBeginFunc begin,
	cpCollisionPreSolveFunc preSolve,
	cpCollisionPostSolveFunc postSolve,
	cpCollisionSeparateFunc separate,
	void *data
);
void cpSpaceAddCollisionHandler(
	cpSpace *space,
	cpCollisionType a, cpCollisionType b,
	cpCollisionBeginFunc begin,
	cpCollisionPreSolveFunc preSolve,
	cpCollisionPostSolveFunc postSolve,
	cpCollisionSeparateFunc separate,
	void *data
);
void cpSpaceRemoveCollisionHandler(cpSpace *space, cpCollisionType a, cpCollisionType b);

// Add and remove entities from the system.
cpShape *cpSpaceAddShape(cpSpace *space, cpShape *shape);
cpShape *cpSpaceAddStaticShape(cpSpace *space, cpShape *shape);
cpBody *cpSpaceAddBody(cpSpace *space, cpBody *body);
cpConstraint *cpSpaceAddConstraint(cpSpace *space, cpConstraint *constraint);

void cpSpaceRemoveShape(cpSpace *space, cpShape *shape);
void cpSpaceRemoveStaticShape(cpSpace *space, cpShape *shape);
void cpSpaceRemoveBody(cpSpace *space, cpBody *body);
void cpSpaceRemoveConstraint(cpSpace *space, cpConstraint *constraint);

// Post Step function definition
typedef void (*cpPostStepFunc)(cpSpace *space, void *obj, void *data);
// Register a post step function to be called after cpSpaceStep() has finished.
// obj is used a key, you can only register one callback per unique value for obj
void cpSpaceAddPostStepCallback(cpSpace *space, cpPostStepFunc func, void *obj, void *data);

// Point query callback function
typedef void (*cpSpacePointQueryFunc)(cpShape *shape, void *data);
void cpSpacePointQuery(cpSpace *space, cpVect point, cpLayers layers, cpGroup group, cpSpacePointQueryFunc func, void *data);
cpShape *cpSpacePointQueryFirst(cpSpace *space, cpVect point, cpLayers layers, cpGroup group);

// Segment query callback function
typedef void (*cpSpaceSegmentQueryFunc)(cpShape *shape, cpFloat t, cpVect n, void *data);
int cpSpaceSegmentQuery(cpSpace *space, cpVect start, cpVect end, cpLayers layers, cpGroup group, cpSpaceSegmentQueryFunc func, void *data);
cpShape *cpSpaceSegmentQueryFirst(cpSpace *space, cpVect start, cpVect end, cpLayers layers, cpGroup group, cpSegmentQueryInfo *out);

// BB query callback function
typedef void (*cpSpaceBBQueryFunc)(cpShape *shape, void *data);
void cpSpaceBBQuery(cpSpace *space, cpBB bb, cpLayers layers, cpGroup group, cpSpaceBBQueryFunc func, void *data);


// Iterator function for iterating the bodies in a space.
typedef void (*cpSpaceBodyIterator)(cpBody *body, void *data);
void cpSpaceEachBody(cpSpace *space, cpSpaceBodyIterator func, void *data);

// Spatial hash management functions.
void cpSpaceResizeStaticHash(cpSpace *space, cpFloat dim, int count);
void cpSpaceResizeActiveHash(cpSpace *space, cpFloat dim, int count);
void cpSpaceRehashStatic(cpSpace *space);

// Update the space.
void cpSpaceStep(cpSpace *space, cpFloat dt);
