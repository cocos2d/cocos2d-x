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


#include "CCPhysicsWorld.h"
#include "../utils/CCArmatureDefine.h"
#include "Box2D/Box2D.h"
#include "../external_tool/GLES-Render.h"

namespace cocos2d { namespace extension { namespace armature {


class Contact
{
public:
	b2Fixture *fixtureA;
	b2Fixture *fixtureB;
};

class ContactListener : public b2ContactListener
{
	//! Callbacks for derived classes.
	virtual void BeginContact(b2Contact *contact)
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
	virtual void EndContact(b2Contact *contact)
	{
		contact_list.clear();
		B2_NOT_USED(contact);
	}
	virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
	{
		B2_NOT_USED(contact);
		B2_NOT_USED(oldManifold);
	}
	virtual void PostSolve(const b2Contact *contact, const b2ContactImpulse *impulse)
	{
		B2_NOT_USED(contact);
		B2_NOT_USED(impulse);
	}

public:
	std::list<Contact> contact_list;
};



CCPhysicsWorld *CCPhysicsWorld::s_PhysicsWorld = NULL;


CCPhysicsWorld *CCPhysicsWorld::sharedPhysicsWorld()
{
    if (s_PhysicsWorld == NULL)
    {
        s_PhysicsWorld = new CCPhysicsWorld();
        s_PhysicsWorld->initNoGravityWorld();
    }

    return s_PhysicsWorld;
}

void CCPhysicsWorld::purgePhysicsWorld()
{
    delete s_PhysicsWorld;
    s_PhysicsWorld = NULL;
}

CCPhysicsWorld::CCPhysicsWorld()
    : _noGravityWorld(NULL)
    , _debugDraw(NULL)
{
}

CCPhysicsWorld::~CCPhysicsWorld()
{
    CC_SAFE_DELETE(_debugDraw);
    CC_SAFE_DELETE(_noGravityWorld);
    CC_SAFE_DELETE(_contactListener);
}

void CCPhysicsWorld::initNoGravityWorld()
{
    b2Vec2 noGravity(0, 0);

    _noGravityWorld = new b2World(noGravity);
    _noGravityWorld->SetAllowSleeping(true);

    _contactListener = new ContactListener();
    _noGravityWorld->SetContactListener(_contactListener);


#if ENABLE_PHYSICS_DEBUG
    _debugDraw = new GLESDebugDraw( PT_RATIO );
    _noGravityWorld->SetDebugDraw(_debugDraw);

    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    //        flags += b2Draw::e_jointBit;
    //        flags += b2Draw::e_aabbBit;
    //        flags += b2Draw::e_pairBit;
    //        flags += b2Draw::e_centerOfMassBit;
    _debugDraw->SetFlags(flags);
#endif
}

b2World *CCPhysicsWorld::getNoGravityWorld()
{
    return _noGravityWorld;
}

void CCPhysicsWorld::update(float dt)
{
    _noGravityWorld->Step(dt, 0, 0);

    for (std::list<Contact>::iterator it = _contactListener->contact_list.begin(); it != _contactListener->contact_list.end(); ++it)
    {
        Contact &contact = *it;

        b2Body *b2a = contact.fixtureA->GetBody();
        b2Body *b2b = contact.fixtureB->GetBody();

        CCBone *ba = (CCBone *)b2a->GetUserData();
        CCBone *bb = (CCBone *)b2b->GetUserData();

        BoneColliderSignal.emit(ba, bb);
    }

}

void CCPhysicsWorld::drawDebug()
{
    _noGravityWorld->DrawDebugData();
}

}}} // namespace cocos2d { namespace extension { namespace armature {
