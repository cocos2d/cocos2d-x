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

/// @defgroup cpSpace cpSpace
/// @{

//MARK: Definitions

/// Collision begin event function callback type.
/// Returning false from a begin callback causes the collision to be ignored until
/// the the separate callback is called when the objects stop colliding.
typedef cpBool (*cpCollisionBeginFunc)(cpArbiter *arb, cpSpace *space, cpDataPointer userData);
/// Collision pre-solve event function callback type.
/// Returning false from a pre-step callback causes the collision to be ignored until the next step.
typedef cpBool (*cpCollisionPreSolveFunc)(cpArbiter *arb, cpSpace *space, cpDataPointer userData);
/// Collision post-solve event function callback type.
typedef void (*cpCollisionPostSolveFunc)(cpArbiter *arb, cpSpace *space, cpDataPointer userData);
/// Collision separate event function callback type.
typedef void (*cpCollisionSeparateFunc)(cpArbiter *arb, cpSpace *space, cpDataPointer userData);

/// Struct that holds function callback pointers to configure custom collision handling.
/// Collision handlers have a pair of types; when a collision occurs between two shapes that have these types, the collision handler functions are triggered.
struct cpCollisionHandler {
	/// Collision type identifier of the first shape that this handler recognizes.
	/// In the collision handler callback, the shape with this type will be the first argument. Read only.
	const cpCollisionType typeA;
	/// Collision type identifier of the second shape that this handler recognizes.
	/// In the collision handler callback, the shape with this type will be the second argument. Read only.
	const cpCollisionType typeB;
	/// This function is called when two shapes with types that match this collision handler begin colliding.
	cpCollisionBeginFunc beginFunc;
	/// This function is called each step when two shapes with types that match this collision handler are colliding.
	/// It's called before the collision solver runs so that you can affect a collision's outcome.
	cpCollisionPreSolveFunc preSolveFunc;
	/// This function is called each step when two shapes with types that match this collision handler are colliding.
	/// It's called after the collision solver runs so that you can read back information about the collision to trigger events in your game.
	cpCollisionPostSolveFunc postSolveFunc;
	/// This function is called when two shapes with types that match this collision handler stop colliding.
	cpCollisionSeparateFunc separateFunc;
	/// This is a user definable context pointer that is passed to all of the collision handler functions.
	cpDataPointer userData;
};

// TODO: Make timestep a parameter?


//MARK: Memory and Initialization

/// Allocate a cpSpace.
CP_EXPORT cpSpace* cpSpaceAlloc(void);
/// Initialize a cpSpace.
CP_EXPORT cpSpace* cpSpaceInit(cpSpace *space);
/// Allocate and initialize a cpSpace.
CP_EXPORT cpSpace* cpSpaceNew(void);

/// Destroy a cpSpace.
CP_EXPORT void cpSpaceDestroy(cpSpace *space);
/// Destroy and free a cpSpace.
CP_EXPORT void cpSpaceFree(cpSpace *space);


//MARK: Properties

/// Number of iterations to use in the impulse solver to solve contacts and other constraints.
CP_EXPORT int cpSpaceGetIterations(const cpSpace *space);
CP_EXPORT void cpSpaceSetIterations(cpSpace *space, int iterations);

/// Gravity to pass to rigid bodies when integrating velocity.
CP_EXPORT cpVect cpSpaceGetGravity(const cpSpace *space);
CP_EXPORT void cpSpaceSetGravity(cpSpace *space, cpVect gravity);

/// Damping rate expressed as the fraction of velocity bodies retain each second.
/// A value of 0.9 would mean that each body's velocity will drop 10% per second.
/// The default value is 1.0, meaning no damping is applied.
/// @note This damping value is different than those of cpDampedSpring and cpDampedRotarySpring.
CP_EXPORT cpFloat cpSpaceGetDamping(const cpSpace *space);
CP_EXPORT void cpSpaceSetDamping(cpSpace *space, cpFloat damping);

/// Speed threshold for a body to be considered idle.
/// The default value of 0 means to let the space guess a good threshold based on gravity.
CP_EXPORT cpFloat cpSpaceGetIdleSpeedThreshold(const cpSpace *space);
CP_EXPORT void cpSpaceSetIdleSpeedThreshold(cpSpace *space, cpFloat idleSpeedThreshold);

/// Time a group of bodies must remain idle in order to fall asleep.
/// Enabling sleeping also implicitly enables the the contact graph.
/// The default value of INFINITY disables the sleeping algorithm.
CP_EXPORT cpFloat cpSpaceGetSleepTimeThreshold(const cpSpace *space);
CP_EXPORT void cpSpaceSetSleepTimeThreshold(cpSpace *space, cpFloat sleepTimeThreshold);

/// Amount of encouraged penetration between colliding shapes.
/// Used to reduce oscillating contacts and keep the collision cache warm.
/// Defaults to 0.1. If you have poor simulation quality,
/// increase this number as much as possible without allowing visible amounts of overlap.
CP_EXPORT cpFloat cpSpaceGetCollisionSlop(const cpSpace *space);
CP_EXPORT void cpSpaceSetCollisionSlop(cpSpace *space, cpFloat collisionSlop);

/// Determines how fast overlapping shapes are pushed apart.
/// Expressed as a fraction of the error remaining after each second.
/// Defaults to pow(1.0 - 0.1, 60.0) meaning that Chipmunk fixes 10% of overlap each frame at 60Hz.
CP_EXPORT cpFloat cpSpaceGetCollisionBias(const cpSpace *space);
CP_EXPORT void cpSpaceSetCollisionBias(cpSpace *space, cpFloat collisionBias);

/// Number of frames that contact information should persist.
/// Defaults to 3. There is probably never a reason to change this value.
CP_EXPORT cpTimestamp cpSpaceGetCollisionPersistence(const cpSpace *space);
CP_EXPORT void cpSpaceSetCollisionPersistence(cpSpace *space, cpTimestamp collisionPersistence);

/// User definable data pointer.
/// Generally this points to your game's controller or game state
/// class so you can access it when given a cpSpace reference in a callback.
CP_EXPORT cpDataPointer cpSpaceGetUserData(const cpSpace *space);
CP_EXPORT void cpSpaceSetUserData(cpSpace *space, cpDataPointer userData);

/// The Space provided static body for a given cpSpace.
/// This is merely provided for convenience and you are not required to use it.
CP_EXPORT cpBody* cpSpaceGetStaticBody(const cpSpace *space);

/// Returns the current (or most recent) time step used with the given space.
/// Useful from callbacks if your time step is not a compile-time global.
CP_EXPORT cpFloat cpSpaceGetCurrentTimeStep(const cpSpace *space);

/// returns true from inside a callback when objects cannot be added/removed.
CP_EXPORT cpBool cpSpaceIsLocked(cpSpace *space);


//MARK: Collision Handlers

/// Create or return the existing collision handler that is called for all collisions that are not handled by a more specific collision handler.
CP_EXPORT cpCollisionHandler *cpSpaceAddDefaultCollisionHandler(cpSpace *space);
/// Create or return the existing collision handler for the specified pair of collision types.
/// If wildcard handlers are used with either of the collision types, it's the responibility of the custom handler to invoke the wildcard handlers.
CP_EXPORT cpCollisionHandler *cpSpaceAddCollisionHandler(cpSpace *space, cpCollisionType a, cpCollisionType b);
/// Create or return the existing wildcard collision handler for the specified type.
CP_EXPORT cpCollisionHandler *cpSpaceAddWildcardHandler(cpSpace *space, cpCollisionType type);


//MARK: Add/Remove objects

/// Add a collision shape to the simulation.
/// If the shape is attached to a static body, it will be added as a static shape.
CP_EXPORT cpShape* cpSpaceAddShape(cpSpace *space, cpShape *shape);
/// Add a rigid body to the simulation.
CP_EXPORT cpBody* cpSpaceAddBody(cpSpace *space, cpBody *body);
/// Add a constraint to the simulation.
CP_EXPORT cpConstraint* cpSpaceAddConstraint(cpSpace *space, cpConstraint *constraint);

/// Remove a collision shape from the simulation.
CP_EXPORT void cpSpaceRemoveShape(cpSpace *space, cpShape *shape);
/// Remove a rigid body from the simulation.
CP_EXPORT void cpSpaceRemoveBody(cpSpace *space, cpBody *body);
/// Remove a constraint from the simulation.
CP_EXPORT void cpSpaceRemoveConstraint(cpSpace *space, cpConstraint *constraint);

/// Test if a collision shape has been added to the space.
CP_EXPORT cpBool cpSpaceContainsShape(cpSpace *space, cpShape *shape);
/// Test if a rigid body has been added to the space.
CP_EXPORT cpBool cpSpaceContainsBody(cpSpace *space, cpBody *body);
/// Test if a constraint has been added to the space.
CP_EXPORT cpBool cpSpaceContainsConstraint(cpSpace *space, cpConstraint *constraint);

//MARK: Post-Step Callbacks

/// Post Step callback function type.
typedef void (*cpPostStepFunc)(cpSpace *space, void *key, void *data);
/// Schedule a post-step callback to be called when cpSpaceStep() finishes.
/// You can only register one callback per unique value for @c key.
/// Returns true only if @c key has never been scheduled before.
/// It's possible to pass @c NULL for @c func if you only want to mark @c key as being used.
CP_EXPORT cpBool cpSpaceAddPostStepCallback(cpSpace *space, cpPostStepFunc func, void *key, void *data);


//MARK: Queries

// TODO: Queries and iterators should take a cpSpace parametery.
// TODO: They should also be abortable.

/// Nearest point query callback function type.
typedef void (*cpSpacePointQueryFunc)(cpShape *shape, cpVect point, cpFloat distance, cpVect gradient, void *data);
/// Query the space at a point and call @c func for each shape found.
CP_EXPORT void cpSpacePointQuery(cpSpace *space, cpVect point, cpFloat maxDistance, cpShapeFilter filter, cpSpacePointQueryFunc func, void *data);
/// Query the space at a point and return the nearest shape found. Returns NULL if no shapes were found.
CP_EXPORT cpShape *cpSpacePointQueryNearest(cpSpace *space, cpVect point, cpFloat maxDistance, cpShapeFilter filter, cpPointQueryInfo *out);

/// Segment query callback function type.
typedef void (*cpSpaceSegmentQueryFunc)(cpShape *shape, cpVect point, cpVect normal, cpFloat alpha, void *data);
/// Perform a directed line segment query (like a raycast) against the space calling @c func for each shape intersected.
CP_EXPORT void cpSpaceSegmentQuery(cpSpace *space, cpVect start, cpVect end, cpFloat radius, cpShapeFilter filter, cpSpaceSegmentQueryFunc func, void *data);
/// Perform a directed line segment query (like a raycast) against the space and return the first shape hit. Returns NULL if no shapes were hit.
CP_EXPORT cpShape *cpSpaceSegmentQueryFirst(cpSpace *space, cpVect start, cpVect end, cpFloat radius, cpShapeFilter filter, cpSegmentQueryInfo *out);

/// Rectangle Query callback function type.
typedef void (*cpSpaceBBQueryFunc)(cpShape *shape, void *data);
/// Perform a fast rectangle query on the space calling @c func for each shape found.
/// Only the shape's bounding boxes are checked for overlap, not their full shape.
CP_EXPORT void cpSpaceBBQuery(cpSpace *space, cpBB bb, cpShapeFilter filter, cpSpaceBBQueryFunc func, void *data);

/// Shape query callback function type.
typedef void (*cpSpaceShapeQueryFunc)(cpShape *shape, cpContactPointSet *points, void *data);
/// Query a space for any shapes overlapping the given shape and call @c func for each shape found.
CP_EXPORT cpBool cpSpaceShapeQuery(cpSpace *space, cpShape *shape, cpSpaceShapeQueryFunc func, void *data);


//MARK: Iteration

/// Space/body iterator callback function type.
typedef void (*cpSpaceBodyIteratorFunc)(cpBody *body, void *data);
/// Call @c func for each body in the space.
CP_EXPORT void cpSpaceEachBody(cpSpace *space, cpSpaceBodyIteratorFunc func, void *data);

/// Space/body iterator callback function type.
typedef void (*cpSpaceShapeIteratorFunc)(cpShape *shape, void *data);
/// Call @c func for each shape in the space.
CP_EXPORT void cpSpaceEachShape(cpSpace *space, cpSpaceShapeIteratorFunc func, void *data);

/// Space/constraint iterator callback function type.
typedef void (*cpSpaceConstraintIteratorFunc)(cpConstraint *constraint, void *data);
/// Call @c func for each shape in the space.
CP_EXPORT void cpSpaceEachConstraint(cpSpace *space, cpSpaceConstraintIteratorFunc func, void *data);


//MARK: Indexing

/// Update the collision detection info for the static shapes in the space.
CP_EXPORT void cpSpaceReindexStatic(cpSpace *space);
/// Update the collision detection data for a specific shape in the space.
CP_EXPORT void cpSpaceReindexShape(cpSpace *space, cpShape *shape);
/// Update the collision detection data for all shapes attached to a body.
CP_EXPORT void cpSpaceReindexShapesForBody(cpSpace *space, cpBody *body);

/// Switch the space to use a spatial has as it's spatial index.
CP_EXPORT void cpSpaceUseSpatialHash(cpSpace *space, cpFloat dim, int count);


//MARK: Time Stepping

/// Step the space forward in time by @c dt.
CP_EXPORT void cpSpaceStep(cpSpace *space, cpFloat dt);


//MARK: Debug API

#ifndef CP_SPACE_DISABLE_DEBUG_API

/// Color type to use with the space debug drawing API.
typedef struct cpSpaceDebugColor {
	float r, g, b, a;
} cpSpaceDebugColor;

/// Callback type for a function that draws a filled, stroked circle.
typedef void (*cpSpaceDebugDrawCircleImpl)(cpVect pos, cpFloat angle, cpFloat radius, cpSpaceDebugColor outlineColor, cpSpaceDebugColor fillColor, cpDataPointer data);
/// Callback type for a function that draws a line segment.
typedef void (*cpSpaceDebugDrawSegmentImpl)(cpVect a, cpVect b, cpSpaceDebugColor color, cpDataPointer data);
/// Callback type for a function that draws a thick line segment.
typedef void (*cpSpaceDebugDrawFatSegmentImpl)(cpVect a, cpVect b, cpFloat radius, cpSpaceDebugColor outlineColor, cpSpaceDebugColor fillColor, cpDataPointer data);
/// Callback type for a function that draws a convex polygon.
typedef void (*cpSpaceDebugDrawPolygonImpl)(int count, const cpVect *verts, cpFloat radius, cpSpaceDebugColor outlineColor, cpSpaceDebugColor fillColor, cpDataPointer data);
/// Callback type for a function that draws a dot.
typedef void (*cpSpaceDebugDrawDotImpl)(cpFloat size, cpVect pos, cpSpaceDebugColor color, cpDataPointer data);
/// Callback type for a function that returns a color for a given shape. This gives you an opportunity to color shapes based on how they are used in your engine.
typedef cpSpaceDebugColor (*cpSpaceDebugDrawColorForShapeImpl)(cpShape *shape, cpDataPointer data);

typedef enum cpSpaceDebugDrawFlags {
	CP_SPACE_DEBUG_DRAW_SHAPES = 1<<0,
	CP_SPACE_DEBUG_DRAW_CONSTRAINTS = 1<<1,
	CP_SPACE_DEBUG_DRAW_COLLISION_POINTS = 1<<2,
} cpSpaceDebugDrawFlags;

/// Struct used with cpSpaceDebugDraw() containing drawing callbacks and other drawing settings.
typedef struct cpSpaceDebugDrawOptions {
	/// Function that will be invoked to draw circles.
	cpSpaceDebugDrawCircleImpl drawCircle;
	/// Function that will be invoked to draw line segments.
	cpSpaceDebugDrawSegmentImpl drawSegment;
	/// Function that will be invoked to draw thick line segments.
	cpSpaceDebugDrawFatSegmentImpl drawFatSegment;
	/// Function that will be invoked to draw convex polygons.
	cpSpaceDebugDrawPolygonImpl drawPolygon;
	/// Function that will be invoked to draw dots.
	cpSpaceDebugDrawDotImpl drawDot;
	
	/// Flags that request which things to draw (collision shapes, constraints, contact points).
	cpSpaceDebugDrawFlags flags;
	/// Outline color passed to the drawing function.
	cpSpaceDebugColor shapeOutlineColor;
	/// Function that decides what fill color to draw shapes using.
	cpSpaceDebugDrawColorForShapeImpl colorForShape;
	/// Color passed to drawing functions for constraints.
	cpSpaceDebugColor constraintColor;
	/// Color passed to drawing functions for collision points.
	cpSpaceDebugColor collisionPointColor;
	
	/// User defined context pointer passed to all of the callback functions as the 'data' argument.
	cpDataPointer data;
} cpSpaceDebugDrawOptions;

/// Debug draw the current state of the space using the supplied drawing options.
CP_EXPORT void cpSpaceDebugDraw(cpSpace *space, cpSpaceDebugDrawOptions *options);

#endif

/// @}
