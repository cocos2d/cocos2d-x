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

/// @defgroup cpBody cpBody
/// Chipmunk's rigid body type. Rigid bodies hold the physical properties of an object like
/// it's mass, and position and velocity of it's center of gravity. They don't have an shape on their own.
/// They are given a shape by creating collision shapes (cpShape) that point to the body.
/// @{

/// Rigid body velocity update function type.
typedef void (*cpBodyVelocityFunc)(cpBody *body, cpVect gravity, cpFloat damping, cpFloat dt);
/// Rigid body position update function type.
typedef void (*cpBodyPositionFunc)(cpBody *body, cpFloat dt);

/// Used internally to track information on the collision graph.
/// @private
typedef struct cpComponentNode {
	cpBody *root;
	cpBody *next;
	cpFloat idleTime;
} cpComponentNode;

/// Chipmunk's rigid body struct.
struct cpBody {
	/// Function that is called to integrate the body's velocity. (Defaults to cpBodyUpdateVelocity)
	cpBodyVelocityFunc velocity_func;
	
	/// Function that is called to integrate the body's position. (Defaults to cpBodyUpdatePosition)
	cpBodyPositionFunc position_func;
	
	/// Mass of the body.
	/// Must agree with cpBody.m_inv! Use cpBodySetMass() when changing the mass for this reason.
	cpFloat m;
	/// Mass inverse.
	cpFloat m_inv;
	
	/// Moment of inertia of the body.
	/// Must agree with cpBody.i_inv! Use cpBodySetMoment() when changing the moment for this reason.
	cpFloat i;
	/// Moment of inertia inverse.
	cpFloat i_inv;
	
	/// Position of the rigid body's center of gravity.
	cpVect p;
	/// Velocity of the rigid body's center of gravity.
	cpVect v;
	/// Force acting on the rigid body's center of gravity.
	cpVect f;
	
	/// Rotation of the body around it's center of gravity in radians.
	/// Must agree with cpBody.rot! Use cpBodySetAngle() when changing the angle for this reason.
	cpFloat a;
	/// Angular velocity of the body around it's center of gravity in radians/second.
	cpFloat w;
	/// Torque applied to the body around it's center of gravity.
	cpFloat t;
	
	/// Cached unit length vector representing the angle of the body.
	/// Used for fast rotations using cpvrotate().
	cpVect rot;
	
	/// User definable data pointer.
	/// Generally this points to your the game object class so you can access it
	/// when given a cpBody reference in a callback.
	cpDataPointer data;
	
	/// Maximum velocity allowed when updating the velocity.
	cpFloat v_limit;
	/// Maximum rotational rate (in radians/second) allowed when updating the angular velocity.
	cpFloat w_limit;
	
	CP_PRIVATE(cpVect v_bias);
	CP_PRIVATE(cpFloat w_bias);
	
	CP_PRIVATE(cpSpace *space);
	
	CP_PRIVATE(cpShape *shapeList);
	CP_PRIVATE(cpArbiter *arbiterList);
	CP_PRIVATE(cpConstraint *constraintList);
	
	CP_PRIVATE(cpComponentNode node);
};

/// Allocate a cpBody.
cpBody* cpBodyAlloc(void);
/// Initialize a cpBody.
cpBody* cpBodyInit(cpBody *body, cpFloat m, cpFloat i);
/// Allocate and initialize a cpBody.
cpBody* cpBodyNew(cpFloat m, cpFloat i);

/// Initialize a static cpBody.
cpBody* cpBodyInitStatic(cpBody *body);
/// Allocate and initialize a static cpBody.
cpBody* cpBodyNewStatic(void);

/// Destroy a cpBody.
void cpBodyDestroy(cpBody *body);
/// Destroy and free a cpBody.
void cpBodyFree(cpBody *body);

/// Check that the properties of a body is sane. (Only in debug mode)
#ifdef NDEBUG
	#define	cpBodyAssertSane(body)
#else
	void cpBodySanityCheck(cpBody *body);
	#define	cpBodyAssertSane(body) cpBodySanityCheck(body)
#endif

// Defined in cpSpace.c
/// Wake up a sleeping or idle body.
void cpBodyActivate(cpBody *body);
/// Wake up any sleeping or idle bodies touching a static body.
void cpBodyActivateStatic(cpBody *body, cpShape *filter);

/// Force a body to fall asleep immediately.
void cpBodySleep(cpBody *body);
/// Force a body to fall asleep immediately along with other bodies in a group.
void cpBodySleepWithGroup(cpBody *body, cpBody *group);

/// Returns true if the body is sleeping.
static inline cpBool cpBodyIsSleeping(const cpBody *body)
{
	return (CP_PRIVATE(body->node).root != ((cpBody*)0));
}

/// Returns true if the body is static.
static inline cpBool cpBodyIsStatic(const cpBody *body)
{
	return CP_PRIVATE(body->node).idleTime == INFINITY;
}

/// Returns true if the body has not been added to a space.
/// Note: Static bodies are a subtype of rogue bodies.
static inline cpBool cpBodyIsRogue(const cpBody *body)
{
	return (body->CP_PRIVATE(space) == ((cpSpace*)0));
}


#define CP_DefineBodyStructGetter(type, member, name) \
static inline type cpBodyGet##name(const cpBody *body){return body->member;}

#define CP_DefineBodyStructSetter(type, member, name) \
static inline void cpBodySet##name(cpBody *body, const type value){ \
	cpBodyActivate(body); \
	body->member = value; \
	cpBodyAssertSane(body); \
}

#define CP_DefineBodyStructProperty(type, member, name) \
CP_DefineBodyStructGetter(type, member, name) \
CP_DefineBodyStructSetter(type, member, name)

// TODO add to docs
CP_DefineBodyStructGetter(cpSpace*, CP_PRIVATE(space), Space)

CP_DefineBodyStructGetter(cpFloat, m, Mass)
/// Set the mass of a body.
void cpBodySetMass(cpBody *body, cpFloat m);

CP_DefineBodyStructGetter(cpFloat, i, Moment)
/// Set the moment of a body.
void cpBodySetMoment(cpBody *body, cpFloat i);

CP_DefineBodyStructGetter(cpVect, p, Pos)
/// Set the position of a body.
void cpBodySetPos(cpBody *body, cpVect pos);
CP_DefineBodyStructProperty(cpVect, v, Vel)
CP_DefineBodyStructProperty(cpVect, f, Force)
CP_DefineBodyStructGetter(cpFloat, a, Angle)
/// Set the angle of a body.
void cpBodySetAngle(cpBody *body, cpFloat a);
CP_DefineBodyStructProperty(cpFloat, w, AngVel)
CP_DefineBodyStructProperty(cpFloat, t, Torque)
CP_DefineBodyStructGetter(cpVect, rot, Rot)
CP_DefineBodyStructProperty(cpFloat, v_limit, VelLimit)
CP_DefineBodyStructProperty(cpFloat, w_limit, AngVelLimit)
CP_DefineBodyStructProperty(cpDataPointer, data, UserData)

/// Default Integration functions.
void cpBodyUpdateVelocity(cpBody *body, cpVect gravity, cpFloat damping, cpFloat dt);
void cpBodyUpdatePosition(cpBody *body, cpFloat dt);

/// Convert body relative/local coordinates to absolute/world coordinates.
static inline cpVect cpBodyLocal2World(const cpBody *body, const cpVect v)
{
	return cpvadd(body->p, cpvrotate(v, body->rot));
}

/// Convert body absolute/world coordinates to  relative/local coordinates.
static inline cpVect cpBodyWorld2Local(const cpBody *body, const cpVect v)
{
	return cpvunrotate(cpvsub(v, body->p), body->rot);
}

/// Set the forces and torque or a body to zero.
void cpBodyResetForces(cpBody *body);
/// Apply an force (in world coordinates) to the body at a point relative to the center of gravity (also in world coordinates).
void cpBodyApplyForce(cpBody *body, const cpVect f, const cpVect r);
/// Apply an impulse (in world coordinates) to the body at a point relative to the center of gravity (also in world coordinates).
void cpBodyApplyImpulse(cpBody *body, const cpVect j, const cpVect r);

/// Get the velocity on a body (in world units) at a point on the body in world coordinates.
cpVect cpBodyGetVelAtWorldPoint(cpBody *body, cpVect point);
/// Get the velocity on a body (in world units) at a point on the body in local coordinates.
cpVect cpBodyGetVelAtLocalPoint(cpBody *body, cpVect point);


/// Get the kinetic energy of a body.
static inline cpFloat cpBodyKineticEnergy(const cpBody *body)
{
	// Need to do some fudging to avoid NaNs
	cpFloat vsq = cpvdot(body->v, body->v);
	cpFloat wsq = body->w*body->w;
	return (vsq ? vsq*body->m : 0.0f) + (wsq ? wsq*body->i : 0.0f);
}

/// Body/shape iterator callback function type. 
typedef void (*cpBodyShapeIteratorFunc)(cpBody *body, cpShape *shape, void *data);
/// Call @c func once for each shape attached to @c body and added to the space.
void cpBodyEachShape(cpBody *body, cpBodyShapeIteratorFunc func, void *data);

/// Body/constraint iterator callback function type. 
typedef void (*cpBodyConstraintIteratorFunc)(cpBody *body, cpConstraint *constraint, void *data);
/// Call @c func once for each constraint attached to @c body and added to the space.
void cpBodyEachConstraint(cpBody *body, cpBodyConstraintIteratorFunc func, void *data);

/// Body/arbiter iterator callback function type. 
typedef void (*cpBodyArbiterIteratorFunc)(cpBody *body, cpArbiter *arbiter, void *data);
/// Call @c func once for each arbiter that is currently active on the body.
void cpBodyEachArbiter(cpBody *body, cpBodyArbiterIteratorFunc func, void *data);

///@}
