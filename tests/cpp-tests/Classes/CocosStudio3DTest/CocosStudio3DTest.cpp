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
    CL(CSNode3DTest)
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
    auto node = CSLoader::createNode("CocosStudio3DTest/Node3D.csb");

    addChild(node);
}

std::string CSNode3DTest::title() const
{
    return "CocosStudio Node3D Test";
}

std::string CSNode3DTest::subtitle() const
{
    return "CCNode in 3D space";
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
