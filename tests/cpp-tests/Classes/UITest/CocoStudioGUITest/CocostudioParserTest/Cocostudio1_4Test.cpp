/****************************************************************************
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

#include "Cocostudio1_4Test.h"
#include "cocostudio/CCSGUIReader.h"
#include "CocostudioParserTest.h"


USING_NS_CC;
using namespace cocostudio;

// CustomImageLayer


void CocostudioV1_4Layer::onEnter()
{
    Layer::onEnter();
    
    GUIReader* guiReader = GUIReader::getInstance();
    
    
    Layout* layout = static_cast<Layout*>(guiReader->widgetFromJsonFile("cocosui/UIEditorTest/cocostudio1_4/Cocostudio1_4_1.json"));
    layout->setScale(0.5);
    CCLOG("content size  = %f", Director::getInstance()->getContentScaleFactor());
    addChild(layout);
}


// CocostudioV1_4Scene


void CocostudioV1_4Scene::onEnter()
{
    CCScene::onEnter();
    
    auto label = Label::createWithTTF("Back", "fonts/arial.ttf", 20);
    //#endif
    MenuItemLabel* pMenuItem = MenuItemLabel::create(label, CC_CALLBACK_1(CocostudioV1_4Scene::BackCallback, this));
    
    Menu* pMenu = Menu::create(pMenuItem, NULL);
    
    pMenu->setPosition( Vec2::ZERO );
    pMenuItem->setPosition( Vec2( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );
    
    addChild(pMenu, 1);
}

void CocostudioV1_4Scene::runThisTest()
{
    Layer* pLayer = new CocostudioV1_4Layer();
    addChild(pLayer);
    pLayer->release();
    
    CCDirector::getInstance()->replaceScene(this);
}

void CocostudioV1_4Scene::BackCallback(Ref* pSender)
{
    CocostudioParserTestScene* pScene = new CocostudioParserTestScene();
    pScene->runThisTest();
    pScene->release();
}