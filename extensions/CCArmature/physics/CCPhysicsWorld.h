/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __CCPHYSICSWORLD_H__
#define __CCPHYSICSWORLD_H__

#include "../utils/CCArmatureDefine.h"
#include "Box2D/Box2D.h"
#include "../CCBone.h"
#include "../external_tool/sigslot.h"
#include "../external_tool/GLES-Render.h"

#include <list>
using std::list;

#ifndef PT_RATIO
#define PT_RATIO 32
#endif

NS_CC_EXT_BEGIN

class Contact
{
public:
	b2Fixture *fixtureA;
	b2Fixture *fixtureB;
};

class ContactListener : public b2ContactListener
{
	//! Callbacks for derived classes.
	virtual void BeginContact(b2Contact* contact) 
	{ 
		if (contact)
		{
			Contact c;
			c.fixtureA = contact->GetFixtureA();
			c.fixtureB = contact->GetFixtureB();

			contact_list.push_back(c);
		}
		B2_NOT_USED(contact); 
	}
	virtual void EndContact(b2Contact* contact) 
	{ 
		contact_list.clear();
		B2_NOT_USED(contact); 
	}
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
		B2_NOT_USED(contact);
		B2_NOT_USED(oldManifold);
	}
	virtual void PostSolve(const b2Contact* contact, const b2ContactImpulse* impulse)
	{
		B2_NOT_USED(contact);
		B2_NOT_USED(impulse);
	}

public:
	std::list<Contact> contact_list;
};


class CCPhysicsWorld
{
public:
	static CCPhysicsWorld *sharedPhysicsWorld();
	static void purgePhysicsWorld();

	void initNoGravityWorld();
private:
	CCPhysicsWorld();
	~CCPhysicsWorld();

private:
	static CCPhysicsWorld *s_PhysicsWorld;

	b2World *m_pNoGravityWorld;

	ContactListener *m_pContactListener;

	GLESDebugDraw *m_pDebugDraw;
public:
	void update(float dt);
	void drawDebug();

	b2World *getNoGravityWorld();

	sigslot::signal2<CCBone*, CCBone*> BoneColliderSignal;
};

NS_CC_EXT_END

#endif/*__CCPHYSICSWORLD_H__*/