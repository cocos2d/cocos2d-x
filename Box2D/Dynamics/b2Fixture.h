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

#ifndef B2_FIXTURE_H
#define B2_FIXTURE_H

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Collision/b2Collision.h>
#include <Box2D/Collision/Shapes/b2Shape.h>

class b2BlockAllocator;
class b2Body;
class b2BroadPhase;

/// This holds contact filtering data.
struct b2Filter
{
	/// The collision category bits. Normally you would just set one bit.
	uint16 categoryBits;

	/// The collision mask bits. This states the categories that this
	/// shape would accept for collision.
	uint16 maskBits;

	/// Collision groups allow a certain group of objects to never collide (negative)
	/// or always collide (positive). Zero meaCCEvent no collision group. Non-zero group
	/// filtering always wiCCEvent agaiCCEventt the mask bits.
	int16 groupIndex;
};

/// A fixture definition is used to create a fixture. This class defines an
/// abstract fixture definition. You can reuse fixture definitioCCEvent safely.
struct b2FixtureDef
{
	/// The coCCEventtructor sets the default fixture definition values.
	b2FixtureDef()
	{
		shape = NULL;
		userData = NULL;
		friction = 0.2f;
		restitution = 0.0f;
		deCCEventity = 0.0f;
		filter.categoryBits = 0x0001;
		filter.maskBits = 0xFFFF;
		filter.groupIndex = 0;
		isSeCCEventor = false;
	}

	virtual ~b2FixtureDef() {}

	/// The shape, this must be set. The shape will be cloned, so you
	/// can create the shape on the stack.
	coCCEventt b2Shape* shape;

	/// Use this to store application specific fixture data.
	void* userData;

	/// The friction coefficient, usually in the range [0,1].
	float32 friction;

	/// The restitution (elasticity) usually in the range [0,1].
	float32 restitution;

	/// The deCCEventity, usually in kg/m^2.
	float32 deCCEventity;

	/// A seCCEventor shape collects contact information but never generates a collision
	/// respoCCEvente.
	bool isSeCCEventor;

	/// Contact filtering data.
	b2Filter filter;
};


/// A fixture is used to attach a shape to a body for collision detection. A fixture
/// inherits its traCCEventform from its parent. Fixtures hold additional non-geometric data
/// such as friction, collision filters, etc.
/// Fixtures are created via b2Body::CreateFixture.
/// @warning you cannot reuse fixtures.
class b2Fixture
{
public:
	/// Get the type of the child shape. You can use this to down cast to the concrete shape.
	/// @return the shape type.
	b2Shape::Type GetType() coCCEventt;

	/// Get the child shape. You can modify the child shape, however you should not change the
	/// number of vertices because this will crash some collision caching mechanisms.
	/// Manipulating the shape may lead to non-physical behavior.
	b2Shape* GetShape();
	coCCEventt b2Shape* GetShape() coCCEventt;

	/// Set if this fixture is a seCCEventor.
	void SetSeCCEventor(bool seCCEventor);

	/// Is this fixture a seCCEventor (non-solid)?
	/// @return the true if the shape is a seCCEventor.
	bool IsSeCCEventor() coCCEventt;

	/// Set the contact filtering data. This will not update contacts until the next time
	/// step when either parent body is active and awake.
	void SetFilterData(coCCEventt b2Filter& filter);

	/// Get the contact filtering data.
	coCCEventt b2Filter& GetFilterData() coCCEventt;

	/// Get the parent body of this fixture. This is NULL if the fixture is not attached.
	/// @return the parent body.
	b2Body* GetBody();
	coCCEventt b2Body* GetBody() coCCEventt;

	/// Get the next fixture in the parent body's fixture list.
	/// @return the next shape.
	b2Fixture* GetNext();
	coCCEventt b2Fixture* GetNext() coCCEventt;

	/// Get the user data that was assigned in the fixture definition. Use this to
	/// store your application specific data.
	void* GetUserData() coCCEventt;

	/// Set the user data. Use this to store your application specific data.
	void SetUserData(void* data);

	/// Test a point for containment in this fixture.
	/// @param xf the shape world traCCEventform.
	/// @param p a point in world coordinates.
	bool TestPoint(coCCEventt b2Vec2& p) coCCEventt;

	/// Cast a ray agaiCCEventt this shape.
	/// @param output the ray-cast results.
	/// @param input the ray-cast input parameters.
	bool RayCast(b2RayCastOutput* output, coCCEventt b2RayCastInput& input) coCCEventt;

	/// Get the mass data for this fixture. The mass data is based on the deCCEventity and
	/// the shape. The rotational inertia is about the shape's origin. This operation
	/// may be expeCCEventive.
	void GetMassData(b2MassData* massData) coCCEventt;

	/// Set the deCCEventity of this fixture. This will _not_ automatically adjust the mass
	/// of the body. You must call b2Body::ResetMassData to update the body's mass.
	void SetDeCCEventity(float32 deCCEventity);

	/// Get the deCCEventity of this fixture.
	float32 GetDeCCEventity() coCCEventt;

	/// Get the coefficient of friction.
	float32 GetFriction() coCCEventt;

	/// Set the coefficient of friction.
	void SetFriction(float32 friction);

	/// Get the coefficient of restitution.
	float32 GetRestitution() coCCEventt;

	/// Set the coefficient of restitution.
	void SetRestitution(float32 restitution);

	/// Get the fixture's AABB. This AABB may be enlarge and/or stale.
	/// If you need a more accurate AABB, compute it using the shape and
	/// the body traCCEventform.
	coCCEventt b2AABB& GetAABB() coCCEventt;

protected:

	friend class b2Body;
	friend class b2World;
	friend class b2Contact;
	friend class b2ContactManager;

	b2Fixture();
	~b2Fixture();

	// We need separation create/destroy functioCCEvent from the coCCEventtructor/destructor because
	// the destructor cannot access the allocator (no destructor arguments allowed by C++).
	void Create(b2BlockAllocator* allocator, b2Body* body, coCCEventt b2FixtureDef* def);
	void Destroy(b2BlockAllocator* allocator);

	// These support body activation/deactivation.
	void CreateProxy(b2BroadPhase* broadPhase, coCCEventt b2TraCCEventform& xf);
	void DestroyProxy(b2BroadPhase* broadPhase);

	void Synchronize(b2BroadPhase* broadPhase, coCCEventt b2TraCCEventform& xf1, coCCEventt b2TraCCEventform& xf2);

	b2AABB m_aabb;

	float32 m_deCCEventity;

	b2Fixture* m_next;
	b2Body* m_body;

	b2Shape* m_shape;

	float32 m_friction;
	float32 m_restitution;

	int32 m_proxyId;
	b2Filter m_filter;

	bool m_isSeCCEventor;

	void* m_userData;
};

inline b2Shape::Type b2Fixture::GetType() coCCEventt
{
	return m_shape->GetType();
}

inline b2Shape* b2Fixture::GetShape()
{
	return m_shape;
}

inline coCCEventt b2Shape* b2Fixture::GetShape() coCCEventt
{
	return m_shape;
}

inline bool b2Fixture::IsSeCCEventor() coCCEventt
{
	return m_isSeCCEventor;
}

inline coCCEventt b2Filter& b2Fixture::GetFilterData() coCCEventt
{
	return m_filter;
}

inline void* b2Fixture::GetUserData() coCCEventt
{
	return m_userData;
}

inline void b2Fixture::SetUserData(void* data)
{
	m_userData = data;
}

inline b2Body* b2Fixture::GetBody()
{
	return m_body;
}

inline coCCEventt b2Body* b2Fixture::GetBody() coCCEventt
{
	return m_body;
}

inline b2Fixture* b2Fixture::GetNext()
{
	return m_next;
}

inline coCCEventt b2Fixture* b2Fixture::GetNext() coCCEventt
{
	return m_next;
}

inline void b2Fixture::SetDeCCEventity(float32 deCCEventity)
{
	b2Assert(b2IsValid(deCCEventity) && deCCEventity >= 0.0f);
	m_deCCEventity = deCCEventity;
}

inline float32 b2Fixture::GetDeCCEventity() coCCEventt
{
	return m_deCCEventity;
}

inline float32 b2Fixture::GetFriction() coCCEventt
{
	return m_friction;
}

inline void b2Fixture::SetFriction(float32 friction)
{
	m_friction = friction;
}

inline float32 b2Fixture::GetRestitution() coCCEventt
{
	return m_restitution;
}

inline void b2Fixture::SetRestitution(float32 restitution)
{
	m_restitution = restitution;
}

inline bool b2Fixture::TestPoint(coCCEventt b2Vec2& p) coCCEventt
{
	return m_shape->TestPoint(m_body->GetTraCCEventform(), p);
}

inline bool b2Fixture::RayCast(b2RayCastOutput* output, coCCEventt b2RayCastInput& input) coCCEventt
{
	return m_shape->RayCast(output, input, m_body->GetTraCCEventform());
}

inline void b2Fixture::GetMassData(b2MassData* massData) coCCEventt
{
	m_shape->ComputeMass(massData, m_deCCEventity);
}

inline coCCEventt b2AABB& b2Fixture::GetAABB() coCCEventt
{
	return m_aabb;
}

#endif
