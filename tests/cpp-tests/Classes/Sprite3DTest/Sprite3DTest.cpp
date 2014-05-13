/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
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

#include "Sprite3DTest.h"
#include "3d/CCSprite3D.h"

#include <algorithm>
#include "../testResource.h"

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

static int sceneIdx = -1;


static std::function<Layer*()> createFunctions[] =
{
	CL(Sprite3D1),
};

#define MAX_LAYER    (sizeof(createFunctions) / sizeof(createFunctions[0]))

static Layer* nextSpriteTestAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;
    
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

static Layer* backSpriteTestAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;
    
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

static Layer* restartSpriteTestAction()
{
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

//------------------------------------------------------------------
//
// SpriteTestDemo
//
//------------------------------------------------------------------

Sprite3DTestDemo::Sprite3DTestDemo(void)
: BaseTest()
{
}

Sprite3DTestDemo::~Sprite3DTestDemo(void)
{
}

std::string Sprite3DTestDemo::title() const
{
    return "No title";
}

std::string Sprite3DTestDemo::subtitle() const
{
    return "";
}

void Sprite3DTestDemo::onEnter()
{
    BaseTest::onEnter();
}

void Sprite3DTestDemo::restartCallback(Ref* sender)
{
    auto s = new Sprite3DTestScene();
    s->addChild(restartSpriteTestAction());
    
    Director::getInstance()->replaceScene(s);
    s->release();
}

void Sprite3DTestDemo::nextCallback(Ref* sender)
{
    auto s = new Sprite3DTestScene();
    s->addChild( nextSpriteTestAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void Sprite3DTestDemo::backCallback(Ref* sender)
{
    auto s = new Sprite3DTestScene();
    s->addChild( backSpriteTestAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}


//------------------------------------------------------------------
//
// Sprite1
//
//------------------------------------------------------------------

Sprite3D1::Sprite3D1()
{
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(Sprite3D1::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto s = Director::getInstance()->getWinSize();
    addNewSpriteWithCoords( Vector2(s.width/2, s.height/2) );
}

void Sprite3D1::addNewSpriteWithCoords(Vector2 p)
{
    //int idx = (int)(CCRANDOM_0_1() * 1400.0f / 100.0f);
    //int x = (idx%5) * 85;
    //int y = (idx/5) * 121;
    
//    //option 1: load a obj that contain the texture in it
//    auto sprite = Sprite3D::create("sprite3dTest/scene01.obj");
    
    //option 2: load obj and assign the texture
    auto sprite = Sprite3D::create("Sprite3DTest/boss.obj");
    sprite->setScale(3.f);
    sprite->setTexture("Sprite3DTest/boss.png");
    
    
//    //create outline effect and set the parameter
//    Sprite3DOutlineEffect* effect = Sprite3DOutlineEffect::create();
//    sprite->setEffect(effect);
//    effect->setOutlineColor(Vector3(1.0f, 1.0f, 0.0f));
//    effect->setOutlineWidth(0.3);
    
    
    //
    //sprite->setEffect(cocos2d::EFFECT_OUTLINE);
    
    //add to scene
    addChild( sprite );
    
    sprite->setPosition( Vector2( p.x, p.y) );
    
    ActionInterval* action;
    float random = CCRANDOM_0_1();
    
    if( random < 0.20 )
        action = ScaleBy::create(3, 2);
    else if(random < 0.40)
        action = RotateBy::create(3, 360);
    else if( random < 0.60)
        action = Blink::create(1, 3);
    else if( random < 0.8 )
        action = TintBy::create(2, 0, -255, -255);
    else
        action = FadeOut::create(2);
    auto action_back = action->reverse();
    auto seq = Sequence::create( action, action_back, NULL );
    
    sprite->runAction( RepeatForever::create(seq) );
}

void Sprite3D1::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    for (auto touch: touches)
    {
        auto location = touch->getLocation();
        
        addNewSpriteWithCoords( location );
    }
}

std::string Sprite3D1::title() const
{
    return "Testing Sprite3D";
}

std::string Sprite3D1::subtitle() const
{
    return "Tap screen to add more sprites";
}

void Sprite3DTestScene::runThisTest()
{
    auto layer = nextSpriteTestAction();
    addChild(layer);
    
    Director::getInstance()->replaceScene(this);
}
