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
#include "HelloWorldScene.h"
#include "PluginManager.h"
#include "AppDelegate.h"
#include "MyPurchase.h"

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

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCSize size = CCDirector::sharedDirector()->getWinSize();

    CCSprite* pBackground = CCSprite::create("background.png");
    pBackground->setPosition(ccp(size.width / 2, size.height / 2));
    addChild(pBackground);
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    CCPoint posBR = ccp(pEGLView->getVisibleOrigin().x + pEGLView->getVisibleSize().width, pEGLView->getVisibleOrigin().y);
    CCPoint posTL = ccp(pEGLView->getVisibleOrigin().x, pEGLView->getVisibleOrigin().y + pEGLView->getVisibleSize().height);

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(posBR.x - 20, posBR.y + 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    CCPoint posStep = ccp(220, -150);
    CCPoint beginPos = ccpAdd(posTL, ccpMult(posStep, 0.5f));
    int line = 0;
    int row = 0;
    for (int i = 0; i < sizeof(s_EventMenuItem)/sizeof(s_EventMenuItem[0]); i++) {
    	CCMenuItemImage* pMenuItem = CCMenuItemImage::create(s_EventMenuItem[i].id.c_str(), s_EventMenuItem[i].id.c_str(),
    			this, menu_selector(HelloWorld::eventMenuCallback));
        pMenu->addChild(pMenuItem, 0, s_EventMenuItem[i].tag);

        CCPoint pos = ccpAdd(beginPos, ccp(posStep.x * row, posStep.y * line));
        CCSize itemSize = pMenuItem->getContentSize();
        if ((pos.x + itemSize.width / 2) > posBR.x)
		{
			line += 1;
			row = 0;
			pos = ccpAdd(beginPos, ccp(posStep.x * row, posStep.y * line));
		}
        row += 1;
        pMenuItem->setPosition(pos);
    }

    CCLabelTTF* label = CCLabelTTF::create("reload all plugins", "Arial", 24);
    CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(HelloWorld::reloadPluginMenuCallback));
    pMenuItem->setAnchorPoint(ccp(0.5f, 0));
    pMenu->addChild(pMenuItem, 0);
    pMenuItem->setPosition( ccp(size.width / 2, 0));

    return true;
}

void HelloWorld::reloadPluginMenuCallback(CCObject* pSender)
{
    MyPurchase::sharedPurchase()->unloadIAPPlugin();
    MyPurchase::sharedPurchase()->loadIAPPlugin();
}

void HelloWorld::eventMenuCallback(CCObject* pSender)
{
    CCMenuItemLabel* pMenuItem = (CCMenuItemLabel*)pSender;
    TProductInfo pInfo;
    MyPurchase::MyPayMode mode = (MyPurchase::MyPayMode) (pMenuItem->getTag() - TAG_PAY_BY_ALIPAY + 1);
    pInfo["productName"] = "100金币";
	pInfo["productPrice"] = "0.01";
	pInfo["productDesc"] = "100个金灿灿的游戏币哦";
	pInfo["Nd91ProductId"] = "685994";
    MyPurchase::sharedPurchase()->payByMode(pInfo, mode);
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	MyPurchase::purgePurchase();

    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
