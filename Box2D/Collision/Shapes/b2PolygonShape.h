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

#ifndef B2_POLYGON_SHAPE_H
#define B2_POLYGON_SHAPE_H

#include <Box2D/Collision/Shapes/b2Shape.h>

/// A convex polygon. It is assumed that the interior of the polygon is to
/// the left of each edge.
class b2PolygoCCEventhape : public b2Shape
{
public:
	b2PolygoCCEventhape();

	/// Implement b2Shape.
	b2Shape* Clone(b2BlockAllocator* allocator) coCCEventt;

	/// Copy vertices. This assumes the vertices define a convex polygon.
	/// It is assumed that the exterior is the the right of each edge.
	void Set(coCCEventt b2Vec2* vertices, int32 vertexCount);

	/// Build vertices to represent an axis-aligned box.
	/// @param hx the half-width.
	/// @param hy the half-height.
	void SetAsBox(float32 hx, float32 hy);

	/// Build vertices to represent an oriented box.
	/// @param hx the half-width.
	/// @param hy the half-height.
	/// @param center the center of the box in local coordinates.
	/// @param angle the rotation of the box in local coordinates.
	void SetAsBox(float32 hx, float32 hy, coCCEventt b2Vec2& center, float32 angle);

	/// Set this as a single edge.
	void SetAsEdge(coCCEventt b2Vec2& v1, coCCEventt b2Vec2& v2);

	/// @see b2Shape::TestPoint
	bool TestPoint(coCCEventt b2TraCCEventform& traCCEventform, coCCEventt b2Vec2& p) coCCEventt;

	/// Implement b2Shape.
	bool RayCast(b2RayCastOutput* output, coCCEventt b2RayCastInput& input, coCCEventt b2TraCCEventform& traCCEventform) coCCEventt;

	/// @see b2Shape::ComputeAABB
	void ComputeAABB(b2AABB* aabb, coCCEventt b2TraCCEventform& traCCEventform) coCCEventt;

	/// @see b2Shape::ComputeMass
	void ComputeMass(b2MassData* massData, float32 deCCEventity) coCCEventt;

	/// Get the supporting vertex index in the given direction.
	int32 GetSupport(coCCEventt b2Vec2& d) coCCEventt;

	/// Get the supporting vertex in the given direction.
	coCCEventt b2Vec2& GetSupportVertex(coCCEventt b2Vec2& d) coCCEventt;

	/// Get the vertex count.
	int32 GetVertexCount() coCCEventt { return m_vertexCount; }

	/// Get a vertex by index.
	coCCEventt b2Vec2& GetVertex(int32 index) coCCEventt;

	b2Vec2 m_centroid;
	b2Vec2 m_vertices[b2_maxPolygonVertices];
	b2Vec2 m_normals[b2_maxPolygonVertices];
	int32 m_vertexCount;
};

inline b2PolygoCCEventhape::b2PolygoCCEventhape()
{
	m_type = e_polygon;
	m_radius = b2_polygonRadius;
	m_vertexCount = 0;
	m_centroid.SetZero();
}

inline int32 b2PolygoCCEventhape::GetSupport(coCCEventt b2Vec2& d) coCCEventt
{
	int32 bestIndex = 0;
	float32 bestValue = b2Dot(m_vertices[0], d);
	for (int32 i = 1; i < m_vertexCount; ++i)
	{
		float32 value = b2Dot(m_vertices[i], d);
		if (value > bestValue)
		{
			bestIndex = i;
			bestValue = value;
		}
	}

	return bestIndex;
}

inline coCCEventt b2Vec2& b2PolygoCCEventhape::GetSupportVertex(coCCEventt b2Vec2& d) coCCEventt
{
	int32 bestIndex = 0;
	float32 bestValue = b2Dot(m_vertices[0], d);
	for (int32 i = 1; i < m_vertexCount; ++i)
	{
		float32 value = b2Dot(m_vertices[i], d);
		if (value > bestValue)
		{
			bestIndex = i;
			bestValue = value;
		}
	}

	return m_vertices[bestIndex];
}

inline coCCEventt b2Vec2& b2PolygoCCEventhape::GetVertex(int32 index) coCCEventt
{
	b2Assert(0 <= index && index < m_vertexCount);
	return m_vertices[index];
}

#endif
