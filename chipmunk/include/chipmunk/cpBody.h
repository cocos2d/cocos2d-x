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

struct cpBody;
struct cpShape;
struct cpSpace;

typedef void (*cpBodyVelocityFunc)(struct cpBody *body, cpVect gravity, cpFloat damping, cpFloat dt);
typedef void (*cpBodyPositionFunc)(struct cpBody *body, cpFloat dt);

extern cpBodyVelocityFunc cpBodyUpdateVelocityDefault;
extern cpBodyPositionFunc cpBodyUpdatePositionDefault;

// Structure to hold information about the contact graph components
// when putting groups of objects to sleep.
// No interesting user accessible fields.
typedef struct cpComponentNode {
	struct cpBody *parent;
	struct cpBody *next;
	int rank;
	cpFloat idleTime;
} cpComponentNode;

typedef struct cpBody{
	// *** Integration Functions.

	// Function that is called to integrate the body's velocity. (Defaults to cpBodyUpdateVelocity)
	cpBodyVelocityFunc velocity_func;
	
	// Function that is called to integrate the body's position. (Defaults to cpBodyUpdatePosition)
	cpBodyPositionFunc position_func;
	
	// *** Mass Properties
	
	// Mass and it's inverse.
	// Always use cpBodySetMass() whenever changing the mass as these values must agree.
	cpFloat m, m_inv;
	
	// Moment of inertia and it's inverse.
	// Always use cpBodySetMoment() whenever changing the moment as these values must agree.
	cpFloat i, i_inv;
	
	// *** Positional Properties
	
	// Linear components of motion (position, velocity, and force)
	cpVect p, v, f;
	
	// Angular components of motion (angle, angular velocity, and torque)
	// Always use cpBodySetAngle() to set the angle of the body as a and rot must agree.
	cpFloat a, w, t;
	
	// Cached unit length vector representing the angle of the body.
	// Used for fast vector rotation using cpvrotate().
	cpVect rot;
	
	// *** User Definable Fields
	
	// User defined data pointer.
	cpDataPointer data;
	
	// *** Other Fields
	
	// Maximum velocities this body can move at after integrating velocity
	cpFloat v_limit, w_limit;
	
	// *** Internally Used Fields
	
	// Velocity bias values used when solving penetrations and correcting constraints.
	CP_PRIVATE(cpVect v_bias);
	CP_PRIVATE(cpFloat w_bias);
	
	// Space this body has been added to
	CP_PRIVATE(struct cpSpace *space);
	
	// Pointer to the shape list.
	// Shapes form a linked list using cpShape.next when added to a space.
	CP_PRIVATE(struct cpShape *shapesList);
	
	// Used by cpSpaceStep() to store contact graph information.
	CP_PRIVATE(cpComponentNode node);
} cpBody;

// Basic allocation/destruction functions
cpBody *cpBodyAlloc(void);
cpBody *cpBodyInit(cpBody *body, cpFloat m, cpFloat i);
cpBody *cpBodyNew(cpFloat m, cpFloat i);

cpBody *cpBodyInitStatic(cpBody *body);
cpBody *cpBodyNewStatic();

void cpBodyDestroy(cpBody *body);
void cpBodyFree(cpBody *body);

// Wake up a sleeping or idle body. (defined in cpSpace.c)
void cpBodyActivate(cpBody *body);

// Force a body to sleep;
// defined in cpSpaceComponent.c
void cpBodySleep(cpBody *body);
void cpBodySleepWithGroup(cpBody *body, cpBody *group);

static inline cpBool
cpBodyIsSleeping(const cpBody *body)
{
	return (CP_PRIVATE(body->node).next != ((cpBody*)0));
}

static inline cpBool
cpBodyIsStatic(const cpBody *body)
{
	return CP_PRIVATE(body->node).idleTime == INFINITY;
}

static inline cpBool
cpBodyIsRogue(const cpBody *body)
{
	return (body->CP_PRIVATE(space) == ((struct cpSpace*)0));
}


#define CP_DefineBodyGetter(type, member, name) \
static inline type cpBodyGet##name(const cpBody *body){return body->member;}

#define CP_DefineBodySetter(type, member, name) \
static inline void \
cpBodySet##name(cpBody *body, const type value){ \
	cpBodyActivate(body); \
	body->member = value; \
} \

#define CP_DefineBodyProperty(type, member, name) \
CP_DefineBodyGetter(type, member, name) \
CP_DefineBodySetter(type, member, name)


// Accessors for cpBody struct members
CP_DefineBodyGetter(cpFloat, m, Mass);
void cpBodySetMass(cpBody *body, cpFloat m);

CP_DefineBodyGetter(cpFloat, i, Moment);
void cpBodySetMoment(cpBody *body, cpFloat i);


CP_DefineBodyProperty(cpVect, p, Pos);
CP_DefineBodyProperty(cpVect, v, Vel);
CP_DefineBodyProperty(cpVect, f, Force);
CP_DefineBodyGetter(cpFloat, a, Angle);
void cpBodySetAngle(cpBody *body, cpFloat a);
CP_DefineBodyProperty(cpFloat, w, AngVel);
CP_DefineBodyProperty(cpFloat, t, Torque);
CP_DefineBodyGetter(cpVect, rot, Rot);
CP_DefineBodyProperty(cpFloat, v_limit, VelLimit);
CP_DefineBodyProperty(cpFloat, w_limit, AngVelLimit);

//  Modify the velocity of the body so that it will move to the specified absolute coordinates in the next timestep.
// Intended for objects that are moved manually with a custom velocity integration function.
void cpBodySlew(cpBody *body, cpVect pos, cpFloat dt);

// Default Integration functions.
void cpBodyUpdateVelocity(cpBody *body, cpVect gravity, cpFloat damping, cpFloat dt);
void cpBodyUpdatePosition(cpBody *body, cpFloat dt);

// Convert body local to world coordinates
static inline cpVect
cpBodyLocal2World(const cpBody *body, const cpVect v)
{
	return cpvadd(body->p, cpvrotate(v, body->rot));
}

// Convert world to body local coordinates
static inline cpVect
cpBodyWorld2Local(const cpBody *body, const cpVect v)
{
	return cpvunrotate(cpvsub(v, body->p), body->rot);
}

// Apply an impulse (in world coordinates) to the body at a point relative to the center of gravity (also in world coordinates).
static inline void
cpBodyApplyImpulse(cpBody *body, const cpVect j, const cpVect r)
{
	body->v = cpvadd(body->v, cpvmult(j, body->m_inv));
	body->w += body->i_inv*cpvcross(r, j);
}

// Zero the forces on a body.
void cpBodyResetForces(cpBody *body);
// Apply a force (in world coordinates) to a body at a point relative to the center of gravity (also in world coordinates).
void cpBodyApplyForce(cpBody *body, const cpVect f, const cpVect r);

static inline cpFloat
cpBodyKineticEnergy(const cpBody *body)
{
	// Need to do some fudging to avoid NaNs
	cpFloat vsq = cpvdot(body->v, body->v);
	cpFloat wsq = body->w*body->w;
	return (vsq ? vsq*body->m : 0.0f) + (wsq ? wsq*body->i : 0.0f);
}

// Apply a damped spring force between two bodies.
// Warning: Large damping values can be unstable. Use a cpDampedSpring constraint for this instead.
void cpApplyDampedSpring(cpBody *a, cpBody *b, cpVect anchr1, cpVect anchr2, cpFloat rlen, cpFloat k, cpFloat dmp, cpFloat dt);
