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

#ifndef DUMP_SHELL_H
#define DUMP_SHELL_H

// This test holds worlds dumped using b2World::Dump.
class DumpShell : public Test
{
public:

	DumpShell()
	{
		//Source code dump of Box2D scene: issue304-minimal-case.rube
		//
		//  Created by R.U.B.E 1.3.0
		//  Using Box2D version 2.3.0
		//  Wed April 3 2013 04:33:28
		//
		//  This code is originally intended for use in the Box2D testbed,
		//  but you can easily use it in other applications by providing
		//  a b2World for use as the 'm_world' variable in the code below.

		b2Vec2 g(0.000000000000000e+00f, -1.000000000000000e+01f);
		m_world->SetGravity(g);
		b2Body** bodies = (b2Body**)b2Alloc(3 * sizeof(b2Body*));
		b2Joint** joints = (b2Joint**)b2Alloc(0 * sizeof(b2Joint*));
		{
			b2BodyDef bd;
			bd.type = b2BodyType(0);
			bd.position.Set(2.587699890136719e-02f, 5.515012264251709e+00f);
			bd.angle = 0.000000000000000e+00f;
			bd.linearVelocity.Set(0.000000000000000e+00f, 0.000000000000000e+00f);
			bd.angularVelocity = 0.000000000000000e+00f;
			bd.linearDamping = 0.000000000000000e+00f;
			bd.angularDamping = 0.000000000000000e+00f;
			bd.allowSleep = bool(4);
			bd.awake = bool(2);
			bd.fixedRotation = bool(0);
			bd.bullet = bool(0);
			bd.active = bool(32);
			bd.gravityScale = 1.000000000000000e+00f;
			bodies[0] = m_world->CreateBody(&bd);

			{
				b2FixtureDef fd;
				fd.friction = 2.000000029802322e-01f;
				fd.restitution = 0.000000000000000e+00f;
				fd.density = 1.000000000000000e+00f;
				fd.isSensor = bool(0);
				fd.filter.categoryBits = uint16(1);
				fd.filter.maskBits = uint16(65535);
				fd.filter.groupIndex = int16(0);
				b2PolygonShape shape;
				b2Vec2 vs[8];
				vs[0].Set(7.733039855957031e-01f, -1.497260034084320e-01f);
				vs[1].Set(-4.487270116806030e-01f, 1.138330027461052e-01f);
				vs[2].Set(-1.880589962005615e+00f, -1.365900039672852e-01f);
				vs[3].Set(3.972740173339844e-01f, -3.897832870483398e+00f);
				shape.Set(vs, 4);

				fd.shape = &shape;

				bodies[0]->CreateFixture(&fd);
			}
		}
		{
			b2BodyDef bd;
			bd.type = b2BodyType(2);
			bd.position.Set(-3.122138977050781e-02f, 7.535382270812988e+00f);
			bd.angle = -1.313644275069237e-02f;
			bd.linearVelocity.Set(8.230687379837036e-01f, 7.775862514972687e-02f);
			bd.angularVelocity = 3.705333173274994e-02f;
			bd.linearDamping = 0.000000000000000e+00f;
			bd.angularDamping = 0.000000000000000e+00f;
			bd.allowSleep = bool(4);
			bd.awake = bool(2);
			bd.fixedRotation = bool(0);
			bd.bullet = bool(0);
			bd.active = bool(32);
			bd.gravityScale = 1.000000000000000e+00f;
			bodies[1] = m_world->CreateBody(&bd);

			{
				b2FixtureDef fd;
				fd.friction = 5.000000000000000e-01f;
				fd.restitution = 0.000000000000000e+00f;
				fd.density = 5.000000000000000e+00f;
				fd.isSensor = bool(0);
				fd.filter.categoryBits = uint16(1);
				fd.filter.maskBits = uint16(65535);
				fd.filter.groupIndex = int16(0);
				b2PolygonShape shape;
				b2Vec2 vs[8];
				vs[0].Set(3.473900079727173e+00f, -2.009889930486679e-01f);
				vs[1].Set(3.457079887390137e+00f, 3.694039955735207e-02f);
				vs[2].Set(-3.116359949111938e+00f, 2.348500071093440e-03f);
				vs[3].Set(-3.109960079193115e+00f, -3.581250011920929e-01f);
				vs[4].Set(-2.590820074081421e+00f, -5.472509860992432e-01f);
				vs[5].Set(2.819370031356812e+00f, -5.402340292930603e-01f);
				shape.Set(vs, 6);

				fd.shape = &shape;

				bodies[1]->CreateFixture(&fd);
			}
		}
		{
			b2BodyDef bd;
			bd.type = b2BodyType(2);
			bd.position.Set(-7.438077926635742e-01f, 6.626811981201172e+00f);
			bd.angle = -1.884713363647461e+01f;
			bd.linearVelocity.Set(1.785794943571091e-01f, 3.799796104431152e-07f);
			bd.angularVelocity = -5.908820639888290e-06f;
			bd.linearDamping = 0.000000000000000e+00f;
			bd.angularDamping = 0.000000000000000e+00f;
			bd.allowSleep = bool(4);
			bd.awake = bool(2);
			bd.fixedRotation = bool(0);
			bd.bullet = bool(0);
			bd.active = bool(32);
			bd.gravityScale = 1.000000000000000e+00f;
			bodies[2] = m_world->CreateBody(&bd);

			{
				b2FixtureDef fd;
				fd.friction = 9.499999880790710e-01f;
				fd.restitution = 0.000000000000000e+00f;
				fd.density = 1.000000000000000e+01f;
				fd.isSensor = bool(0);
				fd.filter.categoryBits = uint16(1);
				fd.filter.maskBits = uint16(65535);
				fd.filter.groupIndex = int16(-3);
				b2PolygonShape shape;
				b2Vec2 vs[8];
				vs[0].Set(1.639146506786346e-01f, 4.428443685173988e-02f);
				vs[1].Set(-1.639146655797958e-01f, 4.428443685173988e-02f);
				vs[2].Set(-1.639146655797958e-01f, -4.428443312644958e-02f);
				vs[3].Set(1.639146357774734e-01f, -4.428444057703018e-02f);
				shape.Set(vs, 4);

				fd.shape = &shape;

				bodies[2]->CreateFixture(&fd);
			}
		}
		b2Free(joints);
		b2Free(bodies);
		joints = NULL;
		bodies = NULL;

	}

	static Test* Create()
	{
		return new DumpShell;
	}
};

#endif
