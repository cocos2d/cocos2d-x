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

/// @defgroup cpSpace cpSpace
/// @{

typedef struct cpContactBufferHeader cpContactBufferHeader;
typedef void (*cpSpaceArbiterApplyImpulseFunc)(cpArbiter *arb);

/// Basic Unit of Simulation in Chipmunk
struct cpSpace {
	/// Number of iterations to use in the impulse solver to solve contacts.
	int iterations;
	
	/// Gravity to pass to rigid bodies when integrating velocity.
	cpVect gravity;
	
	/// Damping rate expressed as the fraction of velocity bodies retain each second.
	/// A value of 0.9 would mean that each body's velocity will drop 10% per second.
	/// The default value is 1.0, meaning no damping is applied.
	/// @note This damping value is different than those of cpDampedSpring and cpDampedRotarySpring.
	cpFloat damping;
	
	/// Speed threshold for a body to be considered idle.
	/// The default value of 0 means to let the space guess a good threshold based on gravity.
	cpFloat idleSpeedThreshold;
	
	/// Time a group of bodies must remain idle in order to fall asleep.
	/// Enabling sleeping also implicitly enables the the contact graph.
	/// The default value of INFINITY disables the sleeping algorithm.
	cpFloat sleepTimeThreshold;
	
	/// Amount of encouraged penetration between colliding shapes.
	/// Used to reduce oscillating contacts and keep the collision cache warm.
	/// Defaults to 0.1. If you have poor simulation quality,
	/// increase this number as much as possible without allowing visible amounts of overlap.
	cpFloat collisionSlop;
	
	/// Determines how fast overlapping shapes are pushed apart.
	/// Expressed as a fraction of the error remaining after each second.
	/// Defaults to pow(1.0 - 0.1, 60.0) meaning that Chipmunk fixes 10% of overlap each frame at 60Hz.
	cpFloat collisionBias;
	
	/// Number of frames that contact information should persist.
	/// Defaults to 3. There is probably never a reason to change this value.
	cpTimestamp collisionPersistence;
	
	/// Rebuild the contact graph during each step. Must be enabled to use the cpBodyEachArbiter() function.
	/// Disabled by default for a small performance boost. Enabled implicitly when the sleeping feature is enabled.
	cpBool enableContactGraph;
	
	/// User definable data pointer.
	/// Generally this points to your game's controller or game state
	/// class so you can access it when given a cpSpace reference in a callback.
	cpDataPointer data;
	
	/// The designated static body for this space.
	/// You can modify this body, or replace it with your own static body.
	/// By default it points to a statically allocated cpBody in the cpSpace struct.
	cpBody *staticBody;
	
	CP_PRIVATE(cpTimestamp stamp);
	CP_PRIVATE(cpFloat curr_dt);

	CP_PRIVATE(cpArray *bodies);
	CP_PRIVATE(cpArray *rousedBodies);
	CP_PRIVATE(cpArray *sleepingComponents);
	
	CP_PRIVATE(cpSpatialIndex *staticShapes);
	CP_PRIVATE(cpSpatialIndex *activeShapes);
	
	CP_PRIVATE(cpArray *arbiters);
	CP_PRIVATE(cpContactBufferHeader *contactBuffersHead);
	CP_PRIVATE(cpHashSet *cachedArbiters);
	CP_PRIVATE(cpArray *pooledArbiters);
	CP_PRIVATE(cpArray *constraints);
	
	CP_PRIVATE(cpArray *allocatedBuffers);
	CP_PRIVATE(int locked);
	
	CP_PRIVATE(cpHashSet *collisionHandlers);
	CP_PRIVATE(cpCollisionHandler defaultHandler);
	
	CP_PRIVATE(cpBool skipPostStep);
	CP_PRIVATE(cpArray *postStepCallbacks);
	
	CP_PRIVATE(cpBody _staticBody);
};

/// Allocate a cpSpace.
cpSpace* cpSpaceAlloc(void);
/// Initialize a cpSpace.
cpSpace* cpSpaceInit(cpSpace *space);
/// Allocate and initialize a cpSpace.
cpSpace* cpSpaceNew(void);

/// Destroy a cpSpace.
void cpSpaceDestroy(cpSpace *space);
/// Destroy and free a cpSpace.
void cpSpaceFree(cpSpace *space);

#define CP_DefineSpaceStructGetter(type, member, name) \
static inline type cpSpaceGet##name(const cpSpace *space){return space->member;}

#define CP_DefineSpaceStructSetter(type, member, name) \
static inline void cpSpaceSet##name(cpSpace *space, type value){space->member = value;}

#define CP_DefineSpaceStructProperty(type, member, name) \
CP_DefineSpaceStructGetter(type, member, name) \
CP_DefineSpaceStructSetter(type, member, name)

CP_DefineSpaceStructProperty(int, iterations, Iterations);
CP_DefineSpaceStructProperty(cpVect, gravity, Gravity);
CP_DefineSpaceStructProperty(cpFloat, damping, Damping);
CP_DefineSpaceStructProperty(cpFloat, idleSpeedThreshold, IdleSpeedThreshold);
CP_DefineSpaceStructProperty(cpFloat, sleepTimeThreshold, SleepTimeThreshold);
CP_DefineSpaceStructProperty(cpFloat, collisionSlop, CollisionSlop);
CP_DefineSpaceStructProperty(cpFloat, collisionBias, CollisionBias);
CP_DefineSpaceStructProperty(cpTimestamp, collisionPersistence, CollisionPersistence);
CP_DefineSpaceStructProperty(cpBool, enableContactGraph, EnableContactGraph);
CP_DefineSpaceStructProperty(cpDataPointer, data, UserData);
CP_DefineSpaceStructGetter(cpBody*, staticBody, StaticBody);
CP_DefineSpaceStructGetter(cpFloat, CP_PRIVATE(curr_dt), CurrentTimeStep);

/// returns true from inside a callback and objects cannot be added/removed.
static inline cpBool
cpSpaceIsLocked(cpSpace *space)
{
	return space->CP_PRIVATE(locked);
}

/// Set a default collision handler for this space.
/// The default collision handler is invoked for each colliding pair of shapes
/// that isn't explicitly handled by a specific collision handler.
/// You can pass NULL for any function you don't want to implement.
void cpSpaceSetDefaultCollisionHandler(
	cpSpace *space,
	cpCollisionBeginFunc begin,
	cpCollisionPreSolveFunc preSolve,
	cpCollisionPostSolveFunc postSolve,
	cpCollisionSeparateFunc separate,
	void *data
);

/// Set a collision handler to be used whenever the two shapes with the given collision types collide.
/// You can pass NULL for any function you don't want to implement.
void cpSpaceAddCollisionHandler(
	cpSpace *space,
	cpCollisionType a, cpCollisionType b,
	cpCollisionBeginFunc begin,
	cpCollisionPreSolveFunc preSolve,
	cpCollisionPostSolveFunc postSolve,
	cpCollisionSeparateFunc separate,
	void *data
);

/// Unset a collision handler.
void cpSpaceRemoveCollisionHandler(cpSpace *space, cpCollisionType a, cpCollisionType b);

/// Add a collision shape to the simulation.
/// If the shape is attached to a static body, it will be added as a static shape.
cpShape* cpSpaceAddShape(cpSpace *space, cpShape *shape);
/// Explicity add a shape as a static shape to the simulation.
cpShape* cpSpaceAddStaticShape(cpSpace *space, cpShape *shape);
/// Add a rigid body to the simulation.
cpBody* cpSpaceAddBody(cpSpace *space, cpBody *body);
/// Add a constraint to the simulation.
cpConstraint* cpSpaceAddConstraint(cpSpace *space, cpConstraint *constraint);

/// Remove a collision shape from the simulation.
void cpSpaceRemoveShape(cpSpace *space, cpShape *shape);
/// Remove a collision shape added using cpSpaceAddStaticShape() from the simulation.
void cpSpaceRemoveStaticShape(cpSpace *space, cpShape *shape);
/// Remove a rigid body from the simulation.
void cpSpaceRemoveBody(cpSpace *space, cpBody *body);
/// Remove a constraint from the simulation.
void cpSpaceRemoveConstraint(cpSpace *space, cpConstraint *constraint);

/// Test if a collision shape has been added to the space.
cpBool cpSpaceContainsShape(cpSpace *space, cpShape *shape);
/// Test if a rigid body has been added to the space.
cpBool cpSpaceContainsBody(cpSpace *space, cpBody *body);
/// Test if a constraint has been added to the space.
cpBool cpSpaceContainsConstraint(cpSpace *space, cpConstraint *constraint);

/// Post Step callback function type.
typedef void (*cpPostStepFunc)(cpSpace *space, void *obj, void *data);
/// Schedule a post-step callback to be called when cpSpaceStep() finishes.
/// You can only register one callback per unique value for @c key.
void cpSpaceAddPostStepCallback(cpSpace *space, cpPostStepFunc func, void *key, void *data);

/// Point query callback function type.
typedef void (*cpSpacePointQueryFunc)(cpShape *shape, void *data);
/// Query the space at a point and call @c func for each shape found.
void cpSpacePointQuery(cpSpace *space, cpVect point, cpLayers layers, cpGroup group, cpSpacePointQueryFunc func, void *data);
/// Query the space at a point and return the first shape found. Returns NULL if no shapes were found.
cpShape *cpSpacePointQueryFirst(cpSpace *space, cpVect point, cpLayers layers, cpGroup group);

/// Nearest point query callback function type.
typedef void (*cpSpaceNearestPointQueryFunc)(cpShape *shape, cpFloat distance, cpVect point, void *data);
/// Query the space at a point and call @c func for each shape found.
void cpSpaceNearestPointQuery(cpSpace *space, cpVect point, cpFloat maxDistance, cpLayers layers, cpGroup group, cpSpaceNearestPointQueryFunc func, void *data);
/// Query the space at a point and return the nearest shape found. Returns NULL if no shapes were found.
cpShape *cpSpaceNearestPointQueryNearest(cpSpace *space, cpVect point, cpFloat maxDistance, cpLayers layers, cpGroup group, cpNearestPointQueryInfo *out);

/// Segment query callback function type.
typedef void (*cpSpaceSegmentQueryFunc)(cpShape *shape, cpFloat t, cpVect n, void *data);
/// Perform a directed line segment query (like a raycast) against the space calling @c func for each shape intersected.
void cpSpaceSegmentQuery(cpSpace *space, cpVect start, cpVect end, cpLayers layers, cpGroup group, cpSpaceSegmentQueryFunc func, void *data);
/// Perform a directed line segment query (like a raycast) against the space and return the first shape hit. Returns NULL if no shapes were hit.
cpShape *cpSpaceSegmentQueryFirst(cpSpace *space, cpVect start, cpVect end, cpLayers layers, cpGroup group, cpSegmentQueryInfo *out);

/// Rectangle Query callback function type.
typedef void (*cpSpaceBBQueryFunc)(cpShape *shape, void *data);
/// Perform a fast rectangle query on the space calling @c func for each shape found.
/// Only the shape's bounding boxes are checked for overlap, not their full shape.
void cpSpaceBBQuery(cpSpace *space, cpBB bb, cpLayers layers, cpGroup group, cpSpaceBBQueryFunc func, void *data);

/// Shape query callback function type.
typedef void (*cpSpaceShapeQueryFunc)(cpShape *shape, cpContactPointSet *points, void *data);
/// Query a space for any shapes overlapping the given shape and call @c func for each shape found.
cpBool cpSpaceShapeQuery(cpSpace *space, cpShape *shape, cpSpaceShapeQueryFunc func, void *data);

/// Call cpBodyActivate() for any shape that is overlaps the given shape.
void cpSpaceActivateShapesTouchingShape(cpSpace *space, cpShape *shape);


/// Space/body iterator callback function type.
typedef void (*cpSpaceBodyIteratorFunc)(cpBody *body, void *data);
/// Call @c func for each body in the space.
void cpSpaceEachBody(cpSpace *space, cpSpaceBodyIteratorFunc func, void *data);

/// Space/body iterator callback function type.
typedef void (*cpSpaceShapeIteratorFunc)(cpShape *shape, void *data);
/// Call @c func for each shape in the space.
void cpSpaceEachShape(cpSpace *space, cpSpaceShapeIteratorFunc func, void *data);

/// Space/constraint iterator callback function type.
typedef void (*cpSpaceConstraintIteratorFunc)(cpConstraint *constraint, void *data);
/// Call @c func for each shape in the space.
void cpSpaceEachConstraint(cpSpace *space, cpSpaceConstraintIteratorFunc func, void *data);

/// Update the collision detection info for the static shapes in the space.
void cpSpaceReindexStatic(cpSpace *space);
/// Update the collision detection data for a specific shape in the space.
void cpSpaceReindexShape(cpSpace *space, cpShape *shape);
/// Update the collision detection data for all shapes attached to a body.
void cpSpaceReindexShapesForBody(cpSpace *space, cpBody *body);

/// Switch the space to use a spatial has as it's spatial index.
void cpSpaceUseSpatialHash(cpSpace *space, cpFloat dim, int count);

/// Step the space forward in time by @c dt.
void cpSpaceStep(cpSpace *space, cpFloat dt);

/// @}
