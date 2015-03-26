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

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

static int sceneIdx = -1;


static std::function<Layer*()> createFunctions[] =
{
    CL(CSNode3DTest),
    CL(CSSprite3DTest),
    CL(CSUserCameraTest),
    CL(CSParticle3DTest)
};

#define MAX_LAYER    (sizeof(createFunctions) / sizeof(createFunctions[0]))

static Layer* nextCocosStudio3DTestAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;
    
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

static Layer* backCocosStudio3DTestAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;
    
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

static Layer* restartCocosStudio3DTestAction()
{
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

//------------------------------------------------------------------
//
// CocosStudio3DTestDemo
//
//------------------------------------------------------------------

CocosStudio3DTestDemo::CocosStudio3DTestDemo(void)
: BaseTest()
{
}

CocosStudio3DTestDemo::~CocosStudio3DTestDemo(void)
{
}

std::string CocosStudio3DTestDemo::title() const
{
    return "No title";
}

std::string CocosStudio3DTestDemo::subtitle() const
{
    return "";
}

void CocosStudio3DTestDemo::onEnter()
{
    BaseTest::onEnter();
}

void CocosStudio3DTestDemo::restartCallback(Ref* sender)
{
    auto s = new (std::nothrow) CS3DTestScene();
    s->addChild(restartCocosStudio3DTestAction());
    
    Director::getInstance()->replaceScene(s);
    s->release();
}

void CocosStudio3DTestDemo::nextCallback(Ref* sender)
{
    auto s = new (std::nothrow) CS3DTestScene();
    s->addChild( nextCocosStudio3DTestAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void CocosStudio3DTestDemo::backCallback(Ref* sender)
{
    auto s = new (std::nothrow) CS3DTestScene();
    s->addChild( backCocosStudio3DTestAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

//------------------------------------------------------------------
//
// CSNode3DTestTest
//
//------------------------------------------------------------------
CSNode3DTest::CSNode3DTest()
{
    auto node = CSLoader::createNode("ccs-res/CocosStudio3DTest/Node3D.csb");

    addChild(node);
}

std::string CSNode3DTest::title() const
{
    return "Node3DReader Test";
}

std::string CSNode3DTest::subtitle() const
{
    return "";
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

std::string CSSprite3DTest::subtitle() const
{
    return "";
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

std::string CSUserCameraTest::subtitle() const
{
    return "";
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

std::string CSParticle3DTest::subtitle() const
{
    return "";
}


//------------------------------------------------------------------
//
// CS3DTestScene
//
//------------------------------------------------------------------
void CS3DTestScene::runThisTest()
{
    auto layer = nextCocosStudio3DTestAction();
    addChild(layer);
        
    Director::getInstance()->replaceScene(this);
}
                   
CS3DTestScene::CS3DTestScene()
{
        
}
