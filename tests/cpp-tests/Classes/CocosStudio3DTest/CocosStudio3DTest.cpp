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

#include "CocosStudio3DTest.h"
#include "editor-support/cocostudio/CocoStudio.h"

USING_NS_CC;

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

CocosStudio3DTests::CocosStudio3DTests()
{
    FileUtils::getInstance()->addSearchPath("ccs-res/CocosStudio3DTest");
    ADD_TEST_CASE(CSNode3DTest);
    ADD_TEST_CASE(CSSprite3DTest);
    ADD_TEST_CASE(CSUserCameraTest);
    ADD_TEST_CASE(CSParticle3DTest);
    ADD_TEST_CASE(CSSceneSkyBoxTest);
    ADD_TEST_CASE(CSSceneLight3DTest);
}

//------------------------------------------------------------------
//
// CocosStudio3DTestDemo
//
//------------------------------------------------------------------

CocosStudio3DTestDemo::CocosStudio3DTestDemo(void)
{
}

CocosStudio3DTestDemo::~CocosStudio3DTestDemo(void)
{
}

std::string CocosStudio3DTestDemo::title() const
{
    return "No title";
}

void CocosStudio3DTestDemo::onExit()
{
    cocostudio::destroyCocosStudio();
    TestCase::onExit();
}

//------------------------------------------------------------------
//
// CSNode3DTestTest
//
//------------------------------------------------------------------
CSNode3DTest::CSNode3DTest()
{
    auto node = CSLoader::createNode("Node3D.csb");

    auto size = Director::getInstance()->getWinSize();
    auto label = Label::create();
    label->setString(std::string("Function demo, no content to show"));
    label->setPosition(size.width / 2, size.height / 2);
    label->setTextColor(Color4B::ORANGE);
    node->addChild(label);

    addChild(node);
}

std::string CSNode3DTest::title() const
{
    return "Node3DReader Test";
}

//------------------------------------------------------------------
//
// CSSprite3DTest
//
//------------------------------------------------------------------
CSSprite3DTest::CSSprite3DTest()
{
    auto node = CSLoader::createNode("Sprite3D.csb");
    
    auto size = Director::getInstance()->getWinSize();
    auto sprite3D = node->getChildByTag(8);
    
    sprite3D->setPosition(size.width / 2, size.height / 2 - 50);
    sprite3D->setColor(Color3B::WHITE);
    sprite3D->setOpacity(255);
    
    addChild(node);
}

std::string CSSprite3DTest::title() const
{
    return "Sprite3DReader Test";
}

//------------------------------------------------------------------
//
// CSUserCameraTest
//
//------------------------------------------------------------------
CSUserCameraTest::CSUserCameraTest()
{
    auto node = CSLoader::createNode("UserCamera.csb");
    
    auto sprite3D = Sprite3D::create("dragon/dragon.c3b");
    sprite3D->setPosition3D(Vec3(100, 95, 80));
    sprite3D->setCameraMask((unsigned int)CameraFlag::USER1);
    
    addChild(node);
    addChild(sprite3D);
}

std::string CSUserCameraTest::title() const
{
    return "UserCameraReader Test";
}

//------------------------------------------------------------------
//
// CSParticle3DTest
//
//------------------------------------------------------------------
CSParticle3DTest::CSParticle3DTest()
{
    auto node = CSLoader::createNode("Particle3D.csb");
    
    addChild(node);
}

std::string CSParticle3DTest::title() const
{
    return "Particle3DReader Test";
}

//------------------------------------------------------------------
//
// CSSceneSkyBoxTest
//
//------------------------------------------------------------------
CSSceneSkyBoxTest::CSSceneSkyBoxTest()
{
    auto node = CSLoader::createNode("SkyBox.csb");

    addChild(node);

    _camera = static_cast<Camera*>(node->getChildByName("UserCamera_0"));
    CameraBackgroundSkyBoxBrush * brush = dynamic_cast<CameraBackgroundSkyBoxBrush *>(_camera->getBackgroundBrush());
    if (nullptr != brush)
    {
        CCLOG("CameraBackgroundSkyBoxBrush active value is : %s", brush->isActived() ? "true" : "false");
        CCLOG("CameraBackgroundSkyBoxBrush valid value is : %s", brush->isValid() ? "true" : "false");
    }

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesMoved = CC_CALLBACK_2(CSSceneSkyBoxTest::onTouchesMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

std::string CSSceneSkyBoxTest::title() const
{
    return "CocosStudio SkyBox Test";
}

void CSSceneSkyBoxTest::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    if (touches.size())
    {
        auto touch = touches[0];
        auto delta = touch->getDelta();

        static float _angle = 0.f;
        _angle -= CC_DEGREES_TO_RADIANS(delta.x);
        _camera->setPosition3D(Vec3(50.0f * sinf(_angle), 0.0f, 50.0f * cosf(_angle)));
        _camera->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
    }
}

//------------------------------------------------------------------
//
// CSSceneLight3DTest
//
//------------------------------------------------------------------
CSSceneLight3DTest::CSSceneLight3DTest()
{
    auto node = CSLoader::createNode("Light3D.csb");
    addChild(node);
}

std::string CSSceneLight3DTest::title() const
{
    return "Light3DReader Test";
}