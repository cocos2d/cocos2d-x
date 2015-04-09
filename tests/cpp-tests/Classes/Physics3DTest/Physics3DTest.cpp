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

#if (CC_ENABLE_BULLET_INTEGRATION)

#include "Physics3DTest.h"
#include "extensions/Physics3D/CCPhysics3D.h"
USING_NS_CC_EXT;

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

static int sceneIdx = -1;
#define PARTICLE_SYSTEM_TAG 0x0001

static std::function<Layer*()> createFunctions[] =
{
    CL(BasicPhysics3DDemo),
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

void Physics3DTestScene::runThisTest()
{
    auto layer = nextSpriteTestAction();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
}

Physics3DTestScene::Physics3DTestScene()
#if CC_USE_3D_PHYSICS
: TestScene(false, true)
#else
: TestScene()
#endif
{
    getPhysics3DWorld()->setDebugDrawEnable(true);
}

void Physics3DTestDemo::restartCallback( Ref* sender )
{
    auto s = new (std::nothrow) Physics3DTestScene();
    s->addChild(restartSpriteTestAction());

    Director::getInstance()->replaceScene(s);
    s->release();
}

void Physics3DTestDemo::nextCallback( Ref* sender )
{
    auto s = new (std::nothrow) Physics3DTestScene();
    s->addChild( nextSpriteTestAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void Physics3DTestDemo::backCallback( Ref* sender )
{
    auto s = new (std::nothrow) Physics3DTestScene();
    s->addChild( backSpriteTestAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

std::string Physics3DTestDemo::title() const
{
    return "Physics3D Test";
}

std::string Physics3DTestDemo::subtitle() const
{
    return "";
}

bool Physics3DTestDemo::init()
{
    if (!BaseTest::init()) return false;

    Size size = Director::getInstance()->getWinSize();
    _camera = Camera::createPerspective(30.0f, size.width / size.height, 1.0f, 1000.0f);
    _camera->setPosition3D(Vec3(0.0f, 0.0f, 100.0f));
    _camera->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
    _camera->setCameraFlag(CameraFlag::USER1);
    this->addChild(_camera);

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(Physics3DTestDemo::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(Physics3DTestDemo::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(Physics3DTestDemo::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    _angle = 0.0f;
    return true;
}

void Physics3DTestDemo::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    
}

void Physics3DTestDemo::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    if (touches.size() && _camera)
    {
        auto touch = touches[0];
        auto delta = touch->getDelta();

        _angle -= CC_DEGREES_TO_RADIANS(delta.x);
        _camera->setPosition3D(Vec3(100.0f * sinf(_angle), 0.0f, 100.0f * cosf(_angle)));
        _camera->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
    }
}

void Physics3DTestDemo::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    
}

Physics3DTestDemo::Physics3DTestDemo( void )
: _angle(0.0f)
, _camera(nullptr)
{

}

void Physics3DTestDemo::update( float delta )
{
    
}

Physics3DTestDemo::~Physics3DTestDemo( void )
{
    
}

std::string BasicPhysics3DDemo::subtitle() const
{
    return "Basic Physics3D";
}

bool BasicPhysics3DDemo::init()
{
    if (!Physics3DTestDemo::init())
        return false;

    Physics3DRigidBodyDes rbDes;
    rbDes.mass = 0.0f;
    rbDes.shape = Physics3DShape::createBox(Vec3(10.0f, 10.0f, 10.0f));
    auto rigitBody = Physics3DRigidBody::create(&rbDes);
    auto component = Physics3DComponent::create(rigitBody);

    auto node = Node::create();
    node->addComponent(component);
    //node->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(node);

    Director::getInstance()->getRunningScene()->setPhysics3DDebugCamera(_camera);

    return true;
}

#endif
