/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "CCScene.h"
#include "CCDirector.h"
#include "CCLayer.h"
#include "CCSprite.h"
#include "CCSpriteBatchNode.h"
#include "CCPhysicsWorld.h"
#include "deprecated/CCString.h"

NS_CC_BEGIN

Scene::Scene()
#if CC_USE_PHYSICS
: _physicsWorld(nullptr)
#endif
{
    _ignoreAnchorPointForPosition = true;
    setAnchorPoint(Point(0.5f, 0.5f));
}

Scene::~Scene()
{
#if CC_USE_PHYSICS
    CC_SAFE_DELETE(_physicsWorld);
#endif
}

bool Scene::init()
{
    bool ret = false;
     do 
     {
         Director * director;
         CC_BREAK_IF( ! (director = Director::getInstance()) );
         this->setContentSize(director->getWinSize());
         // success
         ret = true;
     } while (0);
     return ret;
}

Scene *Scene::create()
{
    Scene *ret = new Scene();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

std::string Scene::getDescription() const
{
    return StringUtils::format("<Scene | tag = %d>", _tag);
}

Scene* Scene::getScene()
{
    return this;
}

#if CC_USE_PHYSICS
void Scene::addChild(Node* child, int zOrder, int tag)
{
    Node::addChild(child, zOrder, tag);
    addChildToPhysicsWorld(child);
}

void Scene::update(float delta)
{
    Node::update(delta);
    if (nullptr != _physicsWorld)
    {
        _physicsWorld->update(delta);
    }
}

Scene *Scene::createWithPhysics()
{
    Scene *ret = new Scene();
    if (ret && ret->initWithPhysics())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

bool Scene::initWithPhysics()
{
    bool ret = false;
    do
    {
        Director * director;
        CC_BREAK_IF( ! (director = Director::getInstance()) );
        this->setContentSize(director->getWinSize());
        CC_BREAK_IF(! (_physicsWorld = PhysicsWorld::construct(*this)));
        
        this->scheduleUpdate();
        // success
        ret = true;
    } while (0);
    return ret;
}

void Scene::addChildToPhysicsWorld(Node* child)
{
    if (_physicsWorld)
    {
        std::function<void(Node*)> addToPhysicsWorldFunc = nullptr;
        addToPhysicsWorldFunc = [this, &addToPhysicsWorldFunc](Node* node) -> void
        {
            if (node->getPhysicsBody())
            {
                _physicsWorld->addBody(node->getPhysicsBody());
            }
            
            auto& children = node->getChildren();
            for( const auto &n : children) {
                addToPhysicsWorldFunc(n);
            }
        };
        
        addToPhysicsWorldFunc(child);
    }
}
#endif

NS_CC_END
