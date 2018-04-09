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
#include "TestIAPOnlineScene.h"
#include "PluginManager.h"
#include "AppDelegate.h"
#include "MyIAPOLManager.h"
#include "HelloWorldScene.h"

using namespace cocos2d;
using namespace cocos2d::plugin;

enum {
	TAG_PAY_BY_QH360 = 100,
	TAG_PAY_BY_ND91,
	TAG_PAY_BY_UC,
};

typedef struct tagEventMenuItem {
    std::string id;
    int tag;
}EventMenuItem;

static EventMenuItem s_EventMenuItem[] = {
    {"BtnQH360.png", TAG_PAY_BY_QH360},
	{"BtnND91.png", TAG_PAY_BY_ND91},
#if TEST_UC
	{"BtnUC.png", TAG_PAY_BY_UC},
#endif
};

Scene* TestIAPOnline::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    TestIAPOnline *layer = TestIAPOnline::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestIAPOnline::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    MyIAPOLManager::getInstance()->loadPlugins();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    auto pEGLView = Director::getInstance()->getOpenGLView();
    Point posBR = Point(pEGLView->getVisibleOrigin().x + pEGLView->getVisibleSize().width, pEGLView->getVisibleOrigin().y);
    Point posTL = Point(pEGLView->getVisibleOrigin().x, pEGLView->getVisibleOrigin().y + pEGLView->getVisibleSize().height);

    // add a "close" icon to exit the progress. it's an autorelease object
    MenuItemFont *pBackItem = MenuItemFont::create("Back", CC_CALLBACK_1(TestIAPOnline::menuBackCallback, this));
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
    			CC_CALLBACK_1(TestIAPOnline::eventMenuCallback, this));
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

void TestIAPOnline::eventMenuCallback(Ref* pSender)
{
    MenuItemLabel* pMenuItem = (MenuItemLabel*)pSender;
    MyIAPOLManager::MyPayMode mode = (MyIAPOLManager::MyPayMode) (pMenuItem->getTag() - TAG_PAY_BY_QH360 + 1);

    TProductInfo pInfo;
    pInfo["productName"] = "100金币";
    pInfo["productPrice"] = "0.01";
    pInfo["productDesc"] = "100个金灿灿的游戏币哦";
    pInfo["Nd91ProductId"] = "685994";

    if (mode == MyIAPOLManager::eQH360) {
        log("To test the IAP online in plugin qh360, you should do this:");
        log("1. Login by UserQH360");
        log("2. Get QH360 user info by your game server (userID, AccessToken)");
        log("3. Fill the product info");

        /**
         * @warning ProductInfo you need filled
         */
        // pInfo["QHAccessToken"] = "User Access Token";    // The access token of user (Get from game server)
        // pInfo["QHUserId"] = "User ID on QH360 server";   // The user ID on QH360 server (Get from game server)
        // pInfo["QHProductID"] = "Product ID";             // The product ID (Game defined this)
        // pInfo["QHNotifyUri"] = "Notify uri";             // The uri which will receive the pay result
        // pInfo["QHUserName"] = "User name in game";       // The user name in game
        // pInfo["QHAppUserID"] = "User ID on game server"; // The user ID on game server

        /**
         * Optional data
         */
        // pInfo["QHExtra1"] = "Extra data 1";              // The extra data will be passed to game server
        // pInfo["QHExtra2"] = "Extra data 2";              // The extra data will be passed to game server
        // pInfo["QHAppOrderID"] = "Order ID in game";      // The order ID in game (Game defined this)
    }

    MyIAPOLManager::getInstance()->payByMode(pInfo, mode);
}

void TestIAPOnline::menuBackCallback(Ref* pSender)
{
	MyIAPOLManager::purge();

	Scene* newScene = HelloWorld::scene();
    Director::getInstance()->replaceScene(newScene);
}
