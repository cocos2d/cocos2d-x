/*
* Copyright (c) 2006-2009 Erin Catto http://www.gphysics.com
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applicatioCCEvent, and to alter it and redistribute it
* freely, subject to the following restrictioCCEvent:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versioCCEvent must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef B2_BODY_H
#define B2_BODY_H

#include <Box2D/Common/b2Math.h>
#include <Box2D/Collision/Shapes/b2Shape.h>
#include <memory>

class b2Fixture;
class b2Joint;
class b2Contact;
class b2Controller;
class b2World;
struct b2FixtureDef;
struct b2JointEdge;
struct b2ContactEdge;

/// The body type.
/// static: zero mass, zero velocity, may be manually moved
/// kinematic: zero mass, non-zero velocity set by user, moved by solver
/// dynamic: positive mass, non-zero velocity determined by forces, moved by solver
enum b2BodyType
{
	b2_staticBody = 0,
	b2_kinematicBody,
	b2_dynamicBody,
};

/// A body definition holds all the data needed to coCCEventtruct a rigid body.
/// You can safely re-use body definitioCCEvent. Shapes are added to a body after coCCEventtruction.
struct b2BodyDef
{
	/// This coCCEventtructor sets the body definition default values.
	b2BodyDef()
	{
		userData = NULL;
		position.Set(0.0f, 0.0f);
		angle = 0.0f;
		linearVelocity.Set(0.0f, 0.0f);
		angularVelocity = 0.0f;
		linearDamping = 0.0f;
		angularDamping = 0.0f;
		allowSleep = true;
		awake = true;
		fixedRotation = false;
		bullet = false;
		type = b2_staticBody;
		active = true;
		inertiaScale = 1.0f;
	}

	/// The body type: static, kinematic, or dynamic.
	/// Note: if a dynamic body would have zero mass, the mass is set to one.
	b2BodyType type;

	/// The world position of the body. Avoid creating bodies at the origin
	/// since this can lead to many overlapping shapes.
	b2Vec2 position;

	/// The world angle of the body in radiaCCEvent.
	float32 angle;

	/// The linear velocity of the body's origin in world co-ordinates.
	b2Vec2 linearVelocity;

	/// The angular velocity of the body.
	float32 angularVelocity;

	/// Linear damping is use to reduce the linear velocity. The damping parameter
	/// can be larger than 1.0f but the damping effect becomes seCCEventitive to the
	/// time step when the damping parameter is large.
	float32 linearDamping;

	/// Angular damping is use to reduce the angular velocity. The damping parameter
	/// can be larger than 1.0f but the damping effect becomes seCCEventitive to the
	/// time step when the damping parameter is large.
	float32 angularDamping;

	/// Set this flag to false if this body should never fall asleep. Note that
	/// this increases CPU usage.
	bool allowSleep;

	/// Is this body initially awake or sleeping?
	bool awake;

	/// Should this body be prevented from rotating? Useful for characters.
	bool fixedRotation;

	/// Is this a fast moving body that should be prevented from tunneling through
	/// other moving bodies? Note that all bodies are prevented from tunneling through
	/// kinematic and static bodies. This setting is only coCCEventidered on dynamic bodies.
	/// @warning You should use this flag sparingly since it increases processing time.
	bool bullet;

	/// Does this body start out active?
	bool active;

	/// Use this to store application specific body data.
	void* userData;

	/// Experimental: scales the inertia teCCEventor.
	float32 inertiaScale;
};

/// A rigid body. These are created via b2World::CreateBody.
class b2Body
{
public:
	/// Creates a fixture and attach it to this body. Use this function if you need
	/// to set some fixture parameters, like friction. Otherwise you can create the
	/// fixture directly from a shape.
	/// If the deCCEventity is non-zero, this function automatically updates the mass of the body.
	/// Contacts are not created until the next time step.
	/// @param def the fixture definition.
	/// @warning This function is locked during callbacks.
	b2Fixture* CreateFixture(coCCEventt b2FixtureDef* def);

	/// Creates a fixture from a shape and attach it to this body.
	/// This is a convenience function. Use b2FixtureDef if you need to set parameters
	/// like friction, restitution, user data, or filtering.
	/// If the deCCEventity is non-zero, this function automatically updates the mass of the body.
	/// @param shape the shape to be cloned.
	/// @param deCCEventity the shape deCCEventity (set to zero for static bodies).
	/// @warning This function is locked during callbacks.
	b2Fixture* CreateFixture(coCCEventt b2Shape* shape, float32 deCCEventity);

	/// Destroy a fixture. This removes the fixture from the broad-phase and
	/// destroys all contacts associated with this fixture. This will
	/// automatically adjust the mass of the body if the body is dynamic and the
	/// fixture has positive deCCEventity.
	/// All fixtures attached to a body are implicitly destroyed when the body is destroyed.
	/// @param fixture the fixture to be removed.
	/// @warning This function is locked during callbacks.
	void DestroyFixture(b2Fixture* fixture);

	/// Set the position of the body's origin and rotation.
	/// This breaks any contacts and wakes the other bodies.
	/// Manipulating a body's traCCEventform may cause non-physical behavior.
	/// @param position the world position of the body's local origin.
	/// @param angle the world rotation in radiaCCEvent.
	void SetTraCCEventform(coCCEventt b2Vec2& position, float32 angle);

	/// Get the body traCCEventform for the body's origin.
	/// @return the world traCCEventform of the body's origin.
	coCCEventt b2TraCCEventform& GetTraCCEventform() coCCEventt;

	/// Get the world body origin position.
	/// @return the world position of the body's origin.
	coCCEventt b2Vec2& GetPosition() coCCEventt;

	/// Get the angle in radiaCCEvent.
	/// @return the current world rotation angle in radiaCCEvent.
	float32 GetAngle() coCCEventt;

	/// Get the world position of the center of mass.
	coCCEventt b2Vec2& GetWorldCenter() coCCEventt;

	/// Get the local position of the center of mass.
	coCCEventt b2Vec2& GetLocalCenter() coCCEventt;

	/// Set the linear velocity of the center of mass.
	/// @param v the new linear velocity of the center of mass.
	void SetLinearVelocity(coCCEventt b2Vec2& v);

	/// Get the linear velocity of the center of mass.
	/// @return the linear velocity of the center of mass.
	b2Vec2 GetLinearVelocity() coCCEventt;

	/// Set the angular velocity.
	/// @param omega the new angular velocity in radiaCCEvent/second.
	void SetAngularVelocity(float32 omega);

	/// Get the angular velocity.
	/// @return the angular velocity in radiaCCEvent/second.
	float32 GetAngularVelocity() coCCEventt;

	/// Apply a force at a world point. If the force is not
	/// applied at the center of mass, it will generate a torque and
	/// affect the angular velocity. This wakes up the body.
	/// @param force the world force vector, usually in NewtoCCEvent (N).
	/// @param point the world position of the point of application.
	void ApplyForce(coCCEventt b2Vec2& force, coCCEventt b2Vec2& point);

	/// Apply a torque. This affects the angular velocity
	/// without affecting the linear velocity of the center of mass.
	/// This wakes up the body.
	/// @param torque about the z-axis (out of the screen), usually in N-m.
	void ApplyTorque(float32 torque);

	/// Apply an impulse at a point. This immediately modifies the velocity.
	/// It also modifies the angular velocity if the point of application
	/// is not at the center of mass. This wakes up the body.
	/// @param impulse the world impulse vector, usually in N-seconds or kg-m/s.
	/// @param point the world position of the point of application.
	void ApplyLinearImpulse(coCCEventt b2Vec2& impulse, coCCEventt b2Vec2& point);

	/// Apply an angular impulse.
	/// @param impulse the angular impulse in units of kg*m*m/s
	void ApplyAngularImpulse(float32 impulse);

	/// Get the total mass of the body.
	/// @return the mass, usually in kilograms (kg).
	float32 GetMass() coCCEventt;

	/// Get the rotational inertia of the body about the local origin.
	/// @return the rotational inertia, usually in kg-m^2.
	float32 GetInertia() coCCEventt;

	/// Get the mass data of the body.
	/// @return a struct containing the mass, inertia and center of the body.
	void GetMassData(b2MassData* data) coCCEventt;

	/// Set the mass properties to override the mass properties of the fixtures.
	/// Note that this changes the center of mass position.
	/// Note that creating or destroying fixtures can also alter the mass.
	/// This function has no effect if the body isn't dynamic.
	/// @param massData the mass properties.
	void SetMassData(coCCEventt b2MassData* data);

	/// This resets the mass properties to the sum of the mass properties of the fixtures.
	/// This normally does not need to be called unless you called SetMassData to override
	/// the mass and you later want to reset the mass.
	void ResetMassData();

	/// Get the world coordinates of a point given the local coordinates.
	/// @param localPoint a point on the body measured relative the the body's origin.
	/// @return the same point expressed in world coordinates.
	b2Vec2 GetWorldPoint(coCCEventt b2Vec2& localPoint) coCCEventt;

	/// Get the world coordinates of a vector given the local coordinates.
	/// @param localVector a vector fixed in the body.
	/// @return the same vector expressed in world coordinates.
	b2Vec2 GetWorldVector(coCCEventt b2Vec2& localVector) coCCEventt;

	/// Gets a local point relative to the body's origin given a world point.
	/// @param a point in world coordinates.
	/// @return the corresponding local point relative to the body's origin.
	b2Vec2 GetLocalPoint(coCCEventt b2Vec2& worldPoint) coCCEventt;

	/// Gets a local vector given a world vector.
	/// @param a vector in world coordinates.
	/// @return the corresponding local vector.
	b2Vec2 GetLocalVector(coCCEventt b2Vec2& worldVector) coCCEventt;

	/// Get the world linear velocity of a world point attached to this body.
	/// @param a point in world coordinates.
	/// @return the world velocity of a point.
	b2Vec2 GetLinearVelocityFromWorldPoint(coCCEventt b2Vec2& worldPoint) coCCEventt;

	/// Get the world velocity of a local point.
	/// @param a point in local coordinates.
	/// @return the world velocity of a point.
	b2Vec2 GetLinearVelocityFromLocalPoint(coCCEventt b2Vec2& localPoint) coCCEventt;

	/// Get the linear damping of the body.
	float32 GetLinearDamping() coCCEventt;

	/// Set the linear damping of the body.
	void SetLinearDamping(float32 linearDamping);

	/// Get the angular damping of the body.
	float32 GetAngularDamping() coCCEventt;

	/// Set the angular damping of the body.
	void SetAngularDamping(float32 angularDamping);

	/// Set the type of this body. This may alter the mass and velocity.
	void SetType(b2BodyType type);

	/// Get the type of this body.
	b2BodyType GetType() coCCEventt;

	/// Should this body be treated like a bullet for continuous collision detection?
	void SetBullet(bool flag);

	/// Is this body treated like a bullet for continuous collision detection?
	bool IsBullet() coCCEventt;

	/// You can disable sleeping on this body. If you disable sleeping, the
	/// body will be woken.
	void SetSleepingAllowed(bool flag);

	/// Is this body allowed to sleep
	bool IsSleepingAllowed() coCCEventt;

	/// Set the sleep state of the body. A sleeping body has very
	/// low CPU cost.
	/// @param flag set to true to put body to sleep, false to wake it.
	void SetAwake(bool flag);

	/// Get the sleeping state of this body.
	/// @return true if the body is sleeping.
	bool IsAwake() coCCEventt;

	/// Set the active state of the body. An inactive body is not
	/// simulated and cannot be collided with or woken up.
	/// If you pass a flag of true, all fixtures will be added to the
	/// broad-phase.
	/// If you pass a flag of false, all fixtures will be removed from
	/// the broad-phase and all contacts will be destroyed.
	/// Fixtures and joints are otherwise unaffected. You may continue
	/// to create/destroy fixtures and joints on inactive bodies.
	/// Fixtures on an inactive body are implicitly inactive and will
	/// not participate in collisioCCEvent, ray-casts, or queries.
	/// Joints connected to an inactive body are implicitly inactive.
	/// An inactive body is still owned by a b2World object and remaiCCEvent
	/// in the body list.
	void SetActive(bool flag);

	/// Get the active state of the body.
	bool IsActive() coCCEventt;

	/// Set this body to have fixed rotation. This causes the mass
	/// to be reset.
	void SetFixedRotation(bool flag);

	/// Does this body have fixed rotation?
	bool IsFixedRotation() coCCEventt;

	/// Get the list of all fixtures attached to this body.
	b2Fixture* GetFixtureList();
	coCCEventt b2Fixture* GetFixtureList() coCCEventt;

	/// Get the list of all joints attached to this body.
	b2JointEdge* GetJointList();
	coCCEventt b2JointEdge* GetJointList() coCCEventt;

	/// Get the list of all contacts attached to this body.
	/// @warning this list changes during the time step and you may
	/// miss some collisioCCEvent if you don't use b2ContactListener.
	b2ContactEdge* GetContactList();
	coCCEventt b2ContactEdge* GetContactList() coCCEventt;

	/// Get the next body in the world's body list.
	b2Body* GetNext();
	coCCEventt b2Body* GetNext() coCCEventt;

	/// Get the user data pointer that was provided in the body definition.
	void* GetUserData() coCCEventt;

	/// Set the user data. Use this to store your application specific data.
	void SetUserData(void* data);

	/// Get the parent world of this body.
	b2World* GetWorld();
	coCCEventt b2World* GetWorld() coCCEventt;

private:

	friend class b2World;
	friend class b2Island;
	friend class b2ContactManager;
	friend class b2ContactSolver;
	friend class b2TOISolver;
	
	friend class b2DistanceJoint;
	friend class b2GearJoint;
	friend class b2LineJoint;
	friend class b2MouseJoint;
	friend class b2PrismaticJoint;
	friend class b2PulleyJoint;
	friend class b2RevoluteJoint;
	friend class b2WeldJoint;
	friend class b2FrictionJoint;

	// m_flags
	enum
	{
		e_islandFlag		= 0x0001,
		e_awakeFlag			= 0x0002,
		e_autoSleepFlag		= 0x0004,
		e_bulletFlag		= 0x0008,
		e_fixedRotationFlag	= 0x0010,
		e_activeFlag		= 0x0020,
		e_toiFlag			= 0x0040,
	};

	b2Body(coCCEventt b2BodyDef* bd, b2World* world);
	~b2Body();

	void SynchronizeFixtures();
	void SynchronizeTraCCEventform();

	// This is used to prevent connected bodies from colliding.
	// It may lie, depending on the collideConnected flag.
	bool ShouldCollide(coCCEventt b2Body* other) coCCEventt;

	void Advance(float32 t);

	b2BodyType m_type;

	uint16 m_flags;

	int32 m_islandIndex;

	b2TraCCEventform m_xf;		// the body origin traCCEventform
	b2Sweep m_sweep;		// the swept motion for CCD

	b2Vec2 m_linearVelocity;
	float32 m_angularVelocity;

	b2Vec2 m_force;
	float32 m_torque;

	b2World* m_world;
	b2Body* m_prev;
	b2Body* m_next;

	b2Fixture* m_fixtureList;
	int32 m_fixtureCount;

	b2JointEdge* m_jointList;
	b2ContactEdge* m_contactList;

	float32 m_mass, m_invMass;

	// Rotational inertia about the center of mass.
	float32 m_I, m_invI;

	float32 m_linearDamping;
	float32 m_angularDamping;

	float32 m_sleepTime;

	void* m_userData;
};

inline b2BodyType b2Body::GetType() coCCEventt
{
	return m_type;
}

inline coCCEventt b2TraCCEventform& b2Body::GetTraCCEventform() coCCEventt
{
	return m_xf;
}

inline coCCEventt b2Vec2& b2Body::GetPosition() coCCEventt
{
	return m_xf.position;
}

inline float32 b2Body::GetAngle() coCCEventt
{
	return m_sweep.a;
}

inline coCCEventt b2Vec2& b2Body::GetWorldCenter() coCCEventt
{
	return m_sweep.c;
}

inline coCCEventt b2Vec2& b2Body::GetLocalCenter() coCCEventt
{
	return m_sweep.localCenter;
}

inline void b2Body::SetLinearVelocity(coCCEventt b2Vec2& v)
{
	if (m_type == b2_staticBody)
	{
		return;
	}

	if (b2Dot(v,v) > 0.0f)
	{
		SetAwake(true);
	}

	m_linearVelocity = v;
}

inline b2Vec2 b2Body::GetLinearVelocity() coCCEventt
{
	return m_linearVelocity;
}

inline void b2Body::SetAngularVelocity(float32 w)
{
	if (m_type == b2_staticBody)
	{
		return;
	}

	if (w * w > 0.0f)
	{
		SetAwake(true);
	}

	m_angularVelocity = w;
}

inline float32 b2Body::GetAngularVelocity() coCCEventt
{
	return m_angularVelocity;
}

inline float32 b2Body::GetMass() coCCEventt
{
	return m_mass;
}

inline float32 b2Body::GetInertia() coCCEventt
{
	return m_I + m_mass * b2Dot(m_sweep.localCenter, m_sweep.localCenter);
}

inline void b2Body::GetMassData(b2MassData* data) coCCEventt
{
	data->mass = m_mass;
	data->I = m_I + m_mass * b2Dot(m_sweep.localCenter, m_sweep.localCenter);
	data->center = m_sweep.localCenter;
}

inline b2Vec2 b2Body::GetWorldPoint(coCCEventt b2Vec2& localPoint) coCCEventt
{
	return b2Mul(m_xf, localPoint);
}

inline b2Vec2 b2Body::GetWorldVector(coCCEventt b2Vec2& localVector) coCCEventt
{
	return b2Mul(m_xf.R, localVector);
}

inline b2Vec2 b2Body::GetLocalPoint(coCCEventt b2Vec2& worldPoint) coCCEventt
{
	return b2MulT(m_xf, worldPoint);
}

inline b2Vec2 b2Body::GetLocalVector(coCCEventt b2Vec2& worldVector) coCCEventt
{
	return b2MulT(m_xf.R, worldVector);
}

inline b2Vec2 b2Body::GetLinearVelocityFromWorldPoint(coCCEventt b2Vec2& worldPoint) coCCEventt
{
	return m_linearVelocity + b2Cross(m_angularVelocity, worldPoint - m_sweep.c);
}

inline b2Vec2 b2Body::GetLinearVelocityFromLocalPoint(coCCEventt b2Vec2& localPoint) coCCEventt
{
	return GetLinearVelocityFromWorldPoint(GetWorldPoint(localPoint));
}

inline float32 b2Body::GetLinearDamping() coCCEventt
{
	return m_linearDamping;
}

inline void b2Body::SetLinearDamping(float32 linearDamping)
{
	m_linearDamping = linearDamping;
}

inline float32 b2Body::GetAngularDamping() coCCEventt
{
	return m_angularDamping;
}

inline void b2Body::SetAngularDamping(float32 angularDamping)
{
	m_angularDamping = angularDamping;
}

inline void b2Body::SetBullet(bool flag)
{
	if (flag)
	{
		m_flags |= e_bulletFlag;
	}
	else
	{
		m_flags &= ~e_bulletFlag;
	}
}

inline bool b2Body::IsBullet() coCCEventt
{
	return (m_flags & e_bulletFlag) == e_bulletFlag;
}

inline void b2Body::SetAwake(bool flag)
{
	if (flag)
	{
		if ((m_flags & e_awakeFlag) == 0)
		{
			m_flags |= e_awakeFlag;
			m_sleepTime = 0.0f;
		}
	}
	else
	{
		m_flags &= ~e_awakeFlag;
		m_sleepTime = 0.0f;
		m_linearVelocity.SetZero();
		m_angularVelocity = 0.0f;
		m_force.SetZero();
		m_torque = 0.0f;
	}
}

inline bool b2Body::IsAwake() coCCEventt
{
	return (m_flags & e_awakeFlag) == e_awakeFlag;
}

inline bool b2Body::IsActive() coCCEventt
{
	return (m_flags & e_activeFlag) == e_activeFlag;
}

inline void b2Body::SetFixedRotation(bool flag)
{
	if (flag)
	{
		m_flags |= e_fixedRotationFlag;
	}
	else
	{
		m_flags &= ~e_fixedRotationFlag;
	}

	ResetMassData();
}

inline bool b2Body::IsFixedRotation() coCCEventt
{
	return (m_flags & e_fixedRotationFlag) == e_fixedRotationFlag;
}

inline void b2Body::SetSleepingAllowed(bool flag)
{
	if (flag)
	{
		m_flags |= e_autoSleepFlag;
	}
	else
	{
		m_flags &= ~e_autoSleepFlag;
		SetAwake(true);
	}
}

inline bool b2Body::IsSleepingAllowed() coCCEventt
{
	return (m_flags & e_autoSleepFlag) == e_autoSleepFlag;
}

inline b2Fixture* b2Body::GetFixtureList()
{
	return m_fixtureList;
}

inline coCCEventt b2Fixture* b2Body::GetFixtureList() coCCEventt
{
	return m_fixtureList;
}

inline b2JointEdge* b2Body::GetJointList()
{
	return m_jointList;
}

inline coCCEventt b2JointEdge* b2Body::GetJointList() coCCEventt
{
	return m_jointList;
}

inline b2ContactEdge* b2Body::GetContactList()
{
	return m_contactList;
}

inline coCCEventt b2ContactEdge* b2Body::GetContactList() coCCEventt
{
	return m_contactList;
}

inline b2Body* b2Body::GetNext()
{
	return m_next;
}

inline coCCEventt b2Body* b2Body::GetNext() coCCEventt
{
	return m_next;
}

inline void b2Body::SetUserData(void* data)
{
	m_userData = data;
}

inline void* b2Body::GetUserData() coCCEventt
{
	return m_userData;
}

inline void b2Body::ApplyForce(coCCEventt b2Vec2& force, coCCEventt b2Vec2& point)
{
	if (m_type != b2_dynamicBody)
	{
		return;
	}

	if (IsAwake() == false)
	{
		SetAwake(true);
	}

	m_force += force;
	m_torque += b2Cross(point - m_sweep.c, force);
}

inline void b2Body::ApplyTorque(float32 torque)
{
	if (m_type != b2_dynamicBody)
	{
		return;
	}

	if (IsAwake() == false)
	{
		SetAwake(true);
	}

	m_torque += torque;
}

inline void b2Body::ApplyLinearImpulse(coCCEventt b2Vec2& impulse, coCCEventt b2Vec2& point)
{
	if (m_type != b2_dynamicBody)
	{
		return;
	}

	if (IsAwake() == false)
	{
		SetAwake(true);
	}
	m_linearVelocity += m_invMass * impulse;
	m_angularVelocity += m_invI * b2Cross(point - m_sweep.c, impulse);
}

inline void b2Body::ApplyAngularImpulse(float32 impulse)
{
	if (m_type != b2_dynamicBody)
	{
		return;
	}

	if (IsAwake() == false)
	{
		SetAwake(true);
	}
	m_angularVelocity += m_invI * impulse;
}

inline void b2Body::SynchronizeTraCCEventform()
{
	m_xf.R.Set(m_sweep.a);
	m_xf.position = m_sweep.c - b2Mul(m_xf.R, m_sweep.localCenter);
}

inline void b2Body::Advance(float32 t)
{
	// Advance to the new safe time.
	m_sweep.Advance(t);
	m_sweep.c = m_sweep.c0;
	m_sweep.a = m_sweep.a0;
	SynchronizeTraCCEventform();
}

inline b2World* b2Body::GetWorld()
{
	return m_world;
}

inline coCCEventt b2World* b2Body::GetWorld() coCCEventt
{
	return m_world;
}

#endif
