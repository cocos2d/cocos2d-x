/*
* Copyright (c) 2006-2007 Erin Catto http://www.gphysics.com
*
* iPhone port by Simon Oliver - http://www.simonoliver.com - http://www.handcircus.com
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

//
// File modified for cocos2d integration
// http://www.cocos2d-iphone.org
//


#ifndef TEST_H
#define TEST_H

//#import <UIKit/UIKit.h>
#include <Box2D/Box2D.h>
#include "GLES-Render.h"

#include <cstdlib>

class Test;
struct Settings;

typedef Test* TestCreateFcn();

#define	RAND_LIMIT	32767

/// Random number in range [-1,1]
inline float32 RandomFloat()
{
	float32 r = (float32)(rand() & (RAND_LIMIT));
	r /= RAND_LIMIT;
	r = 2.0f * r - 1.0f;
	return r;
}

/// Random floating point number in range [lo, hi]
inline float32 RandomFloat(float32 lo, float32 hi)
{
	float32 r = (float32)(rand() & (RAND_LIMIT));
	r /= RAND_LIMIT;
	r = (hi - lo) * r + lo;
	return r;
}

/// Test settings. Some can be controlled in the GUI.
struct Settings
{
	Settings() :
	hz(40.0f),
	velocityIterations(8),
	positionIterations(3),
	drawStats(0),
	drawShapes(1),
	drawJoints(1),
	drawAABBs(0),
	drawPairs(0),
	drawContactPoints(0),
	drawContactNormals(0),
	drawContactForces(0),
	drawFrictionForces(0),
	drawCOMs(0),
	enableWarmStarting(1),
	enableContinuous(1),
	pause(0),
	singleStep(0)
	{}
	
	float32 hz;
	int velocityIterations;
	int positionIterations;
	int drawShapes;
	int drawJoints;
	int drawAABBs;
	int drawPairs;
	int drawContactPoints;
	int drawContactNormals;
	int drawContactForces;
	int drawFrictionForces;
	int drawCOMs;
	int drawStats;
	int enableWarmStarting;
	int enableContinuous;
	int pause;
	int singleStep;
};

struct TestEntry
{
    const char*		name;
	TestCreateFcn* createFcn;
};

extern TestEntry g_testEntries[];
// This is called when a joint in the world is implicitly destroyed
// because an attached body is destroyed. This gives us a chance to
// nullify the mouse joint.
class DestructionListener : public b2DestructionListener
	{
	public:
		void SayGoodbye(b2Fixture* fixture) { B2_NOT_USED(fixture); }
		void SayGoodbye(b2Joint* joint);
		
		Test* test;
	};

const int k_maxContactPoints = 2048;

struct ContactPoint
{
	b2Fixture* fixtureA;
	b2Fixture* fixtureB;
	b2Vec2 normal;
	b2Vec2 position;
	b2PointState state;
};

class Test : public b2ContactListener
	{
	public:
		
		Test();
		virtual ~Test();
		
		void SetGravity(float x,float y);
		void SetTextLine(int line) { m_textLine = line; }
		void DrawTitle(int x, int y, const char *string);
		virtual void Step(Settings* settings);
		virtual void Keyboard(unsigned char key) { B2_NOT_USED(key); }
		void ShiftMouseDown(const b2Vec2& p);
		virtual bool MouseDown(const b2Vec2& p);
		virtual void MouseUp(const b2Vec2& p);
		void MouseMove(const b2Vec2& p);
		void LaunchBomb();
		void LaunchBomb(const b2Vec2& position, const b2Vec2& velocity);
		
		void SpawnBomb(const b2Vec2& worldPt);
		void CompleteBombSpawn(const b2Vec2& p);
		
		// Let derived tests know that a joint was destroyed.
		virtual void JointDestroyed(b2Joint* joint) { B2_NOT_USED(joint); }
		
		// Callbacks for derived classes.
		virtual void BeginContact(b2Contact* contact) { B2_NOT_USED(contact); }
		virtual void EndContact(b2Contact* contact) { B2_NOT_USED(contact); }
		virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
		virtual void PostSolve(const b2Contact* contact, const b2ContactImpulse* impulse)
		{
			B2_NOT_USED(contact);
			B2_NOT_USED(impulse);
		}
		
		b2World* m_world;

	protected:
		friend class DestructionListener;
		friend class BoundaryListener;
		friend class ContactListener;
		
		b2Body* m_groundBody;
		b2AABB m_worldAABB;
		ContactPoint m_points[k_maxContactPoints];
		int m_pointCount;
		DestructionListener m_destructionListener;
		GLESDebugDraw m_debugDraw;
		int m_textLine;
		b2Body* m_bomb;
		b2MouseJoint* m_mouseJoint;
		b2Vec2 m_bombSpawnPoint;
		bool m_bombSpawning;
		b2Vec2 m_mouseWorld;
		int m_stepCount;
	};

#endif
