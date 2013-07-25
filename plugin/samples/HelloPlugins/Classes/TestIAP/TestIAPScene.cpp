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
#include "TestIAPScene.h"
#include "PluginManager.h"
#include "AppDelegate.h"
#include "MyPurchase.h"
#include "HelloWorldScene.h"

using namespace cocos2d;
using namespace cocos2d::plugin;

enum {
	TAG_PAY_BY_ALIPAY = 100,
	TAG_PAY_BY_ND91,
};

typedef struct tagEventMenuItem {
    std::string id;
    int tag;
}EventMenuItem;

static EventMenuItem s_EventMenuItem[] = {
    {"BtnAlipay.png", TAG_PAY_BY_ALIPAY},
	{"BtnND91.png", TAG_PAY_BY_ND91},
};

Scene* TestIAP::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    TestIAP *layer = TestIAP::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestIAP::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    MyPurchase::getInstance()->loadIAPPlugin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    EGLView* pEGLView = EGLView::getInstance();
    Point posBR = Point(pEGLView->getVisibleOrigin().x + pEGLView->getVisibleSize().width, pEGLView->getVisibleOrigin().y);
    Point posTL = Point(pEGLView->getVisibleOrigin().x, pEGLView->getVisibleOrigin().y + pEGLView->getVisibleSize().height);

    // add a "close" icon to exit the progress. it's an autorelease object
    MenuItemFont *pBackItem = MenuItemFont::create("Back", CC_CALLBACK_1(TestIAP::menuBackCallback, this));
    Size backSize = pBackItem->getContentSize();
    pBackItem->setPosition(posBR + Point(- backSize.width / 2, backSize.height / 2));

    // create menu, it's an autorelease object
    Menu* pMenu = Menu::create(pBackItem, NULL);
    pMenu->setPosition( Point::ZERO );
    this->addChild(pMenu, 1);

    Point posStep = Point(220, -150);
    Point beginPos = posTL + (posStep * 0.5f);
    int line = 0;
    int row = 0;
    for (int i = 0; i < sizeof(s_EventMenuItem)/sizeof(s_EventMenuItem[0]); i++) {
    	MenuItemImage* pMenuItem = MenuItemImage::create(s_EventMenuItem[i].id.c_str(), s_EventMenuItem[i].id.c_str(),
    			CC_CALLBACK_1(TestIAP::eventMenuCallback, this));
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

void TestIAP::eventMenuCallback(Object* pSender)
{
    MenuItemLabel* pMenuItem = (MenuItemLabel*)pSender;
    TProductInfo pInfo;
    MyPurchase::MyPayMode mode = (MyPurchase::MyPayMode) (pMenuItem->getTag() - TAG_PAY_BY_ALIPAY + 1);
    pInfo["productName"] = "100金币";
	pInfo["productPrice"] = "0.01";
	pInfo["productDesc"] = "100个金灿灿的游戏币哦";
	pInfo["Nd91ProductId"] = "685994";
    MyPurchase::getInstance()->payByMode(pInfo, mode);
}

void TestIAP::menuBackCallback(Object* pSender)
{
	MyPurchase::purgePurchase();

	Scene* newScene = HelloWorld::scene();
    Director::getInstance()->replaceScene(newScene);
}
