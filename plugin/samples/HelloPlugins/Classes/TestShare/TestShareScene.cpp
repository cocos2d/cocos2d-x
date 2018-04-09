/****************************************************************************
Copyright (c) 2012-2013 cocos2d-x.org

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
#include "TestShareScene.h"
#include "PluginManager.h"
#include "AppDelegate.h"
#include "MyShareManager.h"
#include "HelloWorldScene.h"

using namespace cocos2d;
using namespace cocos2d::plugin;

enum {
	TAG_SHARE_BY_TWWITER = 100,
	TAG_SHARE_BY_WEIBO = 101,
};

typedef struct tagEventMenuItem {
    std::string id;
    int tag;
}EventMenuItem;

static EventMenuItem s_EventMenuItem[] = {
    {"twitter.jpeg", TAG_SHARE_BY_TWWITER},
    {"weibo.png", TAG_SHARE_BY_WEIBO}
};

Scene* TestShare::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    TestShare *layer = TestShare::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestShare::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    MyShareManager::getInstance()->loadSharePlugin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    auto pEGLView = Director::getInstance()->getOpenGLView();
    Point posBR = Point(pEGLView->getVisibleOrigin().x + pEGLView->getVisibleSize().width, pEGLView->getVisibleOrigin().y);
    Point posTL = Point(pEGLView->getVisibleOrigin().x, pEGLView->getVisibleOrigin().y + pEGLView->getVisibleSize().height);

    // add a "close" icon to exit the progress. it's an autorelease object
    MenuItemFont *pBackItem = MenuItemFont::create("Back", CC_CALLBACK_1(TestShare::menuBackCallback, this));
    Size backSize = pBackItem->getContentSize();
    pBackItem->setPosition(posBR + Point(- backSize.width / 2, backSize.height / 2));

    // create menu, it's an autorelease object
    Menu* pMenu = Menu::create(pBackItem, NULL);
    pMenu->setPosition( Point::ZERO );
    this->addChild(pMenu, 1);

    Point posStep = Point(150, -150);
    Point beginPos = posTL + (posStep * 0.5f);
    int line = 0;
    int row = 0;
    for (int i = 0; i < sizeof(s_EventMenuItem)/sizeof(s_EventMenuItem[0]); i++) {
    	MenuItemImage* pMenuItem = MenuItemImage::create(s_EventMenuItem[i].id.c_str(), s_EventMenuItem[i].id.c_str(), CC_CALLBACK_1(TestShare::eventMenuCallback, this));
        pMenu->addChild(pMenuItem, 0, s_EventMenuItem[i].tag);

        Point pos = beginPos + Point(posStep.x * row, posStep.y * line);
        Size itemSize = pMenuItem->getContentSize();
        if ((pos.x + itemSize.width / 2) > posBR.x)
		{
			line += 1;
			row = 0;
			pos = beginPos + Point(posStep.x * row, posStep.y * line);
		}
        row += 1;
        pMenuItem->setPosition(pos);
    }

    return true;
}

void TestShare::eventMenuCallback(Ref* pSender)
{
	MenuItemLabel* pMenuItem = (MenuItemLabel*)pSender;
    TShareInfo pInfo;
    pInfo["SharedText"] = "Share message : HelloShare!";
    // pInfo["SharedImagePath"] = "Full/path/to/image";
    MyShareManager::MyShareMode mode = (MyShareManager::MyShareMode) (pMenuItem->getTag() - TAG_SHARE_BY_TWWITER + 1);
    MyShareManager::getInstance()->shareByMode(pInfo, mode);
}

void TestShare::menuBackCallback(Ref* pSender)
{
    MyShareManager::purgeManager();
    Scene* newScene = HelloWorld::scene();
    Director::getInstance()->replaceScene(newScene);
}
