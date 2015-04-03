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

#include "BulletTest.h"

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

static int sceneIdx = -1;

static std::function<Layer*()> createFunctions[] =
{
    CL(BulletWireDrawDemo),
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

void BulletTestScene::runThisTest()
{
    auto layer = nextSpriteTestAction();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
}

void BulletTestDemo::restartCallback( Ref* sender )
{
    auto s = new (std::nothrow) BulletTestScene();
    s->addChild(restartSpriteTestAction());

    Director::getInstance()->replaceScene(s);
    s->release();
}

void BulletTestDemo::nextCallback( Ref* sender )
{
    auto s = new (std::nothrow) BulletTestScene();
    s->addChild( nextSpriteTestAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void BulletTestDemo::backCallback( Ref* sender )
{
    auto s = new (std::nothrow) BulletTestScene();
    s->addChild( backSpriteTestAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

std::string BulletTestDemo::title() const 
{
    return "Bullet Test";
}

std::string BulletTestDemo::subtitle() const 
{
    return "";
}

bool BulletTestDemo::init()
{
    if (!BaseTest::init()) return false;

    Size size = Director::getInstance()->getWinSize();
    _camera = Camera::createPerspective(30.0f, size.width / size.height, 1.0f, 1000.0f);
    _camera->setPosition3D(Vec3(0.0f, 0.0f, 10.0f));
    _camera->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
    _camera->setCameraFlag(CameraFlag::USER1);
    this->addChild(_camera);

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(BulletTestDemo::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(BulletTestDemo::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(BulletTestDemo::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    scheduleUpdate();
    return true;
}

void BulletTestDemo::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    
}

void BulletTestDemo::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    if (touches.size())
    {
        auto touch = touches[0];
        auto delta = touch->getDelta();
        
        _angle -= CC_DEGREES_TO_RADIANS(delta.x);
        _camera->setPosition3D(Vec3(10.0f * sinf(_angle), 0.0f, 10.0f * cosf(_angle)));
        _camera->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
    }
}

void BulletTestDemo::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    
}

BulletTestDemo::BulletTestDemo( void )
: _angle(0.0f)
{

}

void BulletTestDemo::update( float delta )
{

}

BulletTestDemo::~BulletTestDemo( void )
{
}

std::string BulletWireDrawDemo::subtitle() const 
{
    return "BulletWireDraw";
}

bool BulletWireDrawDemo::init()
{
    if (!BulletTestDemo::init()) 
        return false;

	this->setCameraMask((unsigned int)CameraFlag::USER1);
    return true;
}

void BulletWireDrawDemo::draw( Renderer *renderer, const Mat4& transform, uint32_t flags )
{
	_phyViewer.draw(renderer, transform, flags);
	BulletTestDemo::draw(renderer, transform, flags);
}
