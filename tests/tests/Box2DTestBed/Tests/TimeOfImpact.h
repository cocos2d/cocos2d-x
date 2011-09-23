/*
* Copyright (c) 2006-2009 Erin Catto http://www.gphysics.com
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef TIME_OF_IMPACT_H
#define TIME_OF_IMPACT_H

class TimeOfImpact : public Test
{
public:
	TimeOfImpact()
	{
		{
			//m_shapeA.SetAsEdge(b2Vec2(-10.0f, 0.0f), b2Vec2(10.0f, 0.0f));
			m_shapeA.SetAsBox(0.2f, 1.0f, b2Vec2(0.5f, 1.0f), 0.0f);
		}

		{
			m_shapeB.SetAsBox(2.0f, 0.1f);
		}
	}

	static Test* Create()
	{
		return new TimeOfImpact;
	}

	void Step(Settings* settings)
	{
		Test::Step(settings);

		b2Sweep sweepA;
		sweepA.c0.SetZero();
		sweepA.a0 = 0.0f;
		sweepA.c = sweepA.c0;
		sweepA.a = sweepA.a0;
		sweepA.localCenter.SetZero();

		b2Sweep sweepB;
		sweepB.c0.Set(-0.20382018f, 2.1368704f);
		sweepB.a0 = -3.1664171f;
		sweepB.c.Set(-0.26699525f, 2.3552670f);
		sweepB.a = -3.3926492f;
		sweepB.localCenter.SetZero();

		b2TOIInput input;
		input.proxyA.Set(&m_shapeA);
		input.proxyB.Set(&m_shapeB);
		input.sweepA = sweepA;
		input.sweepB = sweepB;
		input.tMax = 1.0f;

		b2TOIOutput output;

		b2TimeOfImpact(&output, &input);

		m_debugDraw.DrawString(5, m_textLine, "toi = %g", output.t);
		m_textLine += 15;

		extern int b2_toiMaxIters, b2_toiMaxRootIters;
		m_debugDraw.DrawString(5, m_textLine, "max toi iters = %d, max root iters = %d", b2_toiMaxIters, b2_toiMaxRootIters);
		m_textLine += 15;

		b2Vec2 vertices[b2_maxPolygonVertices];

		b2Transform transformA;
		sweepA.GetTransform(&transformA, 0.0f);
		for (int i = 0; i < m_shapeA.m_vertexCount; ++i)
		{
			vertices[i] = b2Mul(transformA, m_shapeA.m_vertices[i]);
		}
		m_debugDraw.DrawPolygon(vertices, m_shapeA.m_vertexCount, b2Color(0.9f, 0.9f, 0.9f));

		b2Transform transformB;
		sweepB.GetTransform(&transformB, 0.0f);
		
		b2Vec2 localPoint(2.0f, -0.1f);
		b2Vec2 rB = b2Mul(transformB, localPoint) - sweepB.c0;
		float32 wB = sweepB.a - sweepB.a0;
		b2Vec2 vB = sweepB.c - sweepB.c0;
		b2Vec2 v = vB + b2Cross(wB, rB);

		for (int i = 0; i < m_shapeB.m_vertexCount; ++i)
		{
			vertices[i] = b2Mul(transformB, m_shapeB.m_vertices[i]);
		}
		m_debugDraw.DrawPolygon(vertices, m_shapeB.m_vertexCount, b2Color(0.5f, 0.9f, 0.5f));

		sweepB.GetTransform(&transformB, output.t);
		for (int i = 0; i < m_shapeB.m_vertexCount; ++i)
		{
			vertices[i] = b2Mul(transformB, m_shapeB.m_vertices[i]);
		}
		m_debugDraw.DrawPolygon(vertices, m_shapeB.m_vertexCount, b2Color(0.5f, 0.7f, 0.9f));

		sweepB.GetTransform(&transformB, 1.0f);
		for (int i = 0; i < m_shapeB.m_vertexCount; ++i)
		{
			vertices[i] = b2Mul(transformB, m_shapeB.m_vertices[i]);
		}
		m_debugDraw.DrawPolygon(vertices, m_shapeB.m_vertexCount, b2Color(0.9f, 0.5f, 0.5f));

#if 0
		for (float32 t = 0.0f; t < 1.0f; t += 0.1f)
		{
			sweepB.GetTransform(&transformB, t);
			for (int i = 0; i < m_shapeB.m_vertexCount; ++i)
			{
				vertices[i] = b2Mul(transformB, m_shapeB.m_vertices[i]);
			}
			m_debugDraw.DrawPolygon(vertices, m_shapeB.m_vertexCount, b2Color(0.9f, 0.5f, 0.5f));
		}
#endif
	}

	b2PolygonShape m_shapeA;
	b2PolygonShape m_shapeB;
};

#endif
