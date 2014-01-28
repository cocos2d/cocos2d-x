/*
* Copyright (c) 2011 Erin Catto http://www.box2d.org
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

#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

class ConvexHull : public Test
{
public:
	enum
	{
		e_count = b2_maxPolygonVertices
	};

	ConvexHull()
	{
		Generate();
		m_auto = false;
	}

	void Generate()
	{
		b2Vec2 lowerBound(-8.0f, -8.0f);
		b2Vec2 upperBound(8.0f, 8.0f);

		for (int32 i = 0; i < e_count; ++i)
		{
			float32 x = 10.0f * RandomFloat();
			float32 y = 10.0f * RandomFloat();

			// Clamp onto a square to help create collinearities.
			// This will stress the convex hull algorithm.
			b2Vec2 v(x, y);
			v = b2Clamp(v, lowerBound, upperBound);
			m_points[i] = v;
		}

		m_count = e_count;

		m_points[0].Set( -1.70082211f,  -1.43221712f );
		m_points[1].Set(  0.5f,         -0.5f );
		m_points[2].Set(  0.104992867f,  0.97400856f );
		m_points[3].Set( -0.658002853f,  0.926608086f );
		m_points[4].Set( -0.994554818f,  0.165337861f );
		m_count = 5;
	}

	static Test* Create()
	{
		return new ConvexHull;
	}

	void Keyboard(unsigned char key)
	{
		switch (key)
		{
		case 'a':
			m_auto = !m_auto;
			break;

		case 'g':
			Generate();
			break;
		}
	}

	void Step(Settings* settings)
	{
		Test::Step(settings);

		b2PolygonShape shape;
		shape.Set(m_points, m_count);

		m_debugDraw.DrawString(5, m_textLine, "Press g to generate a new random convex hull");
		m_textLine += DRAW_STRING_NEW_LINE;

		m_debugDraw.DrawPolygon(shape.m_vertices, shape.m_count, b2Color(0.9f, 0.9f, 0.9f));

		for (int32 i = 0; i < m_count; ++i)
		{
			m_debugDraw.DrawPoint(m_points[i], 2.0f, b2Color(0.9f, 0.5f, 0.5f));
			//m_debugDraw.DrawString(m_points[i] + b2Vec2(0.05f, 0.05f), "%d", i);
		}

		if (shape.Validate() == false)
		{
			m_textLine += 0;
		}

		if (m_auto)
		{
			Generate();
		}
	}

	b2Vec2 m_points[b2_maxPolygonVertices];
	int32 m_count;
	bool m_auto;
};

#endif
