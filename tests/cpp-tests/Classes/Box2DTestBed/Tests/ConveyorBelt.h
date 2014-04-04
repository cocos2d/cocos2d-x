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

#ifndef CONVEYOR_BELT_H
#define CONVEYOR_BELT_H

class ConveyorBelt : public Test
{
public:

	ConveyorBelt()
	{
		// Ground
		{
			b2BodyDef bd;
			b2Body* ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.Set(b2Vec2(-20.0f, 0.0f), b2Vec2(20.0f, 0.0f));
			ground->CreateFixture(&shape, 0.0f);
		}

		// Platform
		{
			b2BodyDef bd;
			bd.position.Set(-5.0f, 5.0f);
			b2Body* body = m_world->CreateBody(&bd);

			b2PolygonShape shape;
			shape.SetAsBox(10.0f, 0.5f);

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.friction = 0.8f;
			m_platform = body->CreateFixture(&fd);
		}

		// Boxes
		for (int32 i = 0; i < 5; ++i)
		{
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(-10.0f + 2.0f * i, 7.0f);
			b2Body* body = m_world->CreateBody(&bd);

			b2PolygonShape shape;
			shape.SetAsBox(0.5f, 0.5f);
			body->CreateFixture(&shape, 20.0f);
		}
	}

	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
		Test::PreSolve(contact, oldManifold);

		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA == m_platform)
		{
			contact->SetTangentSpeed(5.0f);
		}

		if (fixtureB == m_platform)
		{
			contact->SetTangentSpeed(-5.0f);
		}
	}

	void Step(Settings* settings)
	{
		Test::Step(settings);
	}

	static Test* Create()
	{
		return new ConveyorBelt;
	}

	b2Fixture* m_platform;
};

#endif
