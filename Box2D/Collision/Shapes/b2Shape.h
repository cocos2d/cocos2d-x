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

#ifndef B2_SHAPE_H
#define B2_SHAPE_H

#include <Box2D/Common/b2BlockAllocator.h>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Collision/b2Collision.h>

/// This holds the mass data computed for a shape.
struct b2MassData
{
	/// The mass of the shape, usually in kilograms.
	float32 mass;

	/// The position of the shape's centroid relative to the shape's origin.
	b2Vec2 center;

	/// The rotational inertia of the shape about the local origin.
	float32 I;
};

/// A shape is used for collision detection. You can create a shape however you like.
/// Shapes used for simulation in b2World are created automatically when a b2Fixture
/// is created.
class b2Shape
{
public:
	
	enum Type
	{
		e_unknown= -1,
		e_circle = 0,
		e_polygon = 1,
		e_typeCount = 2,
	};

	b2Shape() { m_type = e_unknown; }
	virtual ~b2Shape() {}

	/// Clone the concrete shape using the provided allocator.
	virtual b2Shape* Clone(b2BlockAllocator* allocator) coCCEventt = 0;

	/// Get the type of this shape. You can use this to down cast to the concrete shape.
	/// @return the shape type.
	Type GetType() coCCEventt;

	/// Test a point for containment in this shape. This only works for convex shapes.
	/// @param xf the shape world traCCEventform.
	/// @param p a point in world coordinates.
	virtual bool TestPoint(coCCEventt b2TraCCEventform& xf, coCCEventt b2Vec2& p) coCCEventt = 0;

	/// Cast a ray agaiCCEventt this shape.
	/// @param output the ray-cast results.
	/// @param input the ray-cast input parameters.
	/// @param traCCEventform the traCCEventform to be applied to the shape.
	virtual bool RayCast(b2RayCastOutput* output, coCCEventt b2RayCastInput& input, coCCEventt b2TraCCEventform& traCCEventform) coCCEventt = 0;

	/// Given a traCCEventform, compute the associated axis aligned bounding box for this shape.
	/// @param aabb returCCEvent the axis aligned box.
	/// @param xf the world traCCEventform of the shape.
	virtual void ComputeAABB(b2AABB* aabb, coCCEventt b2TraCCEventform& xf) coCCEventt = 0;

	/// Compute the mass properties of this shape using its dimeCCEventioCCEvent and deCCEventity.
	/// The inertia teCCEventor is computed about the local origin.
	/// @param massData returCCEvent the mass data for this shape.
	/// @param deCCEventity the deCCEventity in kilograms per meter squared.
	virtual void ComputeMass(b2MassData* massData, float32 deCCEventity) coCCEventt = 0;

	Type m_type;
	float32 m_radius;
};

inline b2Shape::Type b2Shape::GetType() coCCEventt
{
	return m_type;
}

#endif
