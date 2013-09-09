/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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
#include "sprite_nodes/CCSprite.h"
#include "physics/CCPhysicsWorld.h"

NS_CC_BEGIN

Scene::Scene()
{
    _ignoreAnchorPointForPosition = true;
    setAnchorPoint(Point(0.5f, 0.5f));
}

Scene::~Scene()
{
}

bool Scene::init()
{
    bool bRet = false;
     do 
     {
         Director * pDirector;
         CC_BREAK_IF( ! (pDirector = Director::getInstance()) );
         this->setContentSize(pDirector->getWinSize());
         // success
         bRet = true;
     } while (0);
     return bRet;
}

Scene *Scene::create(bool usePhysics/* = false*/)
{
    Scene *pRet = new Scene();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

void Scene::addChild(Node* child)
{
    Node::addChild(child);
}

void Scene::addChild(Node* child, int zOrder)
{
    Node::addChild(child, zOrder);
}

void Scene::addChild(Node* child, int zOrder, int tag)
{
    Node::addChild(child, zOrder, tag);
    
    auto addToPhysicsWorldFunc = [this](Object* node) -> void
    {
        if (typeid(Sprite).hash_code() == typeid(node).hash_code())
        {
            Sprite* sp = dynamic_cast<Sprite*>(node);
            
            if (sp && sp->getPhysicsBody())
            {
                _physicsWorld->addChild(sp->getPhysicsBody());
            }
        }
    };
    
    if(typeid(Layer).hash_code() == typeid(child).hash_code())
    {
        Object* subChild = nullptr;
        CCARRAY_FOREACH(child->getChildren(), subChild)
        {
            addToPhysicsWorldFunc(subChild);
        }
    }else
    {
        addToPhysicsWorldFunc(child);
    }
}


NS_CC_END
