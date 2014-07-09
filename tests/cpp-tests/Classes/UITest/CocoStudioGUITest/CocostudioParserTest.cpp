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

#include "CocostudioParserTest.h"

#include "CocoStudioGUITest.h"
#include "CocostudioParserTest/CocostudioParserJsonTest.h"

enum
{
    LINE_SPACE = 40,
    kItemTagBasic = 1000,
};

static struct
{
	const char *name;
	std::function<void(Ref* sender)> callback;
}
g_guisTests[] =
{
	{
        "cocostudio 1.3",
        [](Ref* sender)
        {
            CocostudioParserJsonScene* pScene = new CocostudioParserJsonScene("cocosui/UIEditorTest/cocostudio1_3/CocostudioV1_3_1.ExportJson");
            pScene->runThisTest();
            pScene->release();
        }
	},
    {
        "cocostudio 1.4",
        [](Ref* sender)
        {
            CocostudioParserJsonScene* pScene = new CocostudioParserJsonScene("cocosui/UIEditorTest/cocostudio1_4/Cocostudio1_4_1.ExportJson");
            pScene->runThisTest();
            pScene->release();
        }
	},
    {
        "cocostudio 1.5",
        [](Ref* sender)
        {
            CocostudioParserJsonScene* pScene = new CocostudioParserJsonScene("cocosui/UIEditorTest/cocostudio1_5/Cocostudio1_5_1.ExportJson");
            pScene->runThisTest();
            pScene->release();
        }
	},

};

static const int g_maxTests = sizeof(g_guisTests) / sizeof(g_guisTests[0]);

////////////////////////////////////////////////////////
//
// CocostudioParserTestMainLayer
//
////////////////////////////////////////////////////////

static Vec2 _curPos = Vec2::ZERO;


void CocostudioParserTestMainLayer::onEnter()
{
    Layer::onEnter();
    
    auto s = Director::getInstance()->getWinSize();
    
    _itemMenu = Menu::create();
    _itemMenu->setPosition( _curPos );
    MenuItemFont::setFontName("fonts/arial.ttf");
    MenuItemFont::setFontSize(24);
    for (int i = 0; i < g_maxTests; ++i)
    {
        auto pItem = MenuItemFont::create(g_guisTests[i].name, g_guisTests[i].callback);
        //        pItem->setPosition(Vec2(s.width / 2, s.height / 2));
        pItem->setPosition(Vec2(s.width / 2, s.height - (i + 1) * LINE_SPACE));
        _itemMenu->addChild(pItem, kItemTagBasic + i);
    }
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(CocostudioParserTestMainLayer::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(CocostudioParserTestMainLayer::onTouchesMoved, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    addChild(_itemMenu);
}

void CocostudioParserTestMainLayer::onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event *event)
{
    auto touch = static_cast<Touch*>(touches[0]);
    
    _beginPos = touch->getLocation();
}


////////////////////////////////////////////////////////
//
// CocostudioParserTestScene
//
////////////////////////////////////////////////////////

void CocostudioParserTestScene::onEnter()
{
    CCScene::onEnter();
    
    auto label = Label::createWithTTF("Back", "fonts/arial.ttf", 20);
    //#endif
    MenuItemLabel* pMenuItem = MenuItemLabel::create(label, CC_CALLBACK_1(CocostudioParserTestScene::BackCallback, this));
    
    Menu* pMenu = Menu::create(pMenuItem, NULL);
    
    pMenu->setPosition( Vec2::ZERO );
    pMenuItem->setPosition( Vec2( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );
    
    addChild(pMenu, 1);
}

void CocostudioParserTestScene::runThisTest()
{
    Layer* pLayer = new CocostudioParserTestMainLayer();
    addChild(pLayer);
    pLayer->release();
    
    CCDirector::getInstance()->replaceScene(this);
}

void CocostudioParserTestScene::BackCallback(Ref* pSender)
{
    CocoStudioGUITestScene* pScene = new CocoStudioGUITestScene();
    pScene->runThisTest();
    pScene->release();
}