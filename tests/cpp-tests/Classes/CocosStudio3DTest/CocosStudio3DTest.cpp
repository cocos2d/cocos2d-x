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
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

CocosStudio3DTests::CocosStudio3DTests()
{
    ADD_TEST_CASE(CSNode3DTest);
    ADD_TEST_CASE(CSSprite3DTest);
    ADD_TEST_CASE(CSUserCameraTest);
    ADD_TEST_CASE(CSParticle3DTest);
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
    auto node = CSLoader::createNode("ccs-res/CocosStudio3DTest/Node3D.csb");

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
    auto node = CSLoader::createNode("ccs-res/CocosStudio3DTest/Sprite3D.csb");
    
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
    auto node = CSLoader::createNode("ccs-res/CocosStudio3DTest/UserCamera.csb");
    
    auto sprite3D = Sprite3D::create("ccs-res/CocosStudio3DTest/dragon/dragon.c3b");
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
    auto node = CSLoader::createNode("ccs-res/CocosStudio3DTest/Particle3D.csb");
    
    addChild(node);
}

std::string CSParticle3DTest::title() const
{
    return "Particle3DReader Test";
}
