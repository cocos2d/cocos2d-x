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
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::plugin;
using namespace cocos2d::ui;

Scene* TestIAP::scene()
{
    Scene *scene = Scene::create();
    TestIAP *layer = TestIAP::create();

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool TestIAP::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    //Load plugins
    MyPurchase::getInstance()->loadIAPPlugin();

    Size winSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //Back button
    auto backButton = Button::create("btn_normal.png","btn_pressed.png");
    backButton->setAnchorPoint(Vec2(1, 0));
    backButton->setTitleText("Back");
    backButton->setScale(2);
    backButton->setPosition(Vec2(origin.x + winSize.width, origin.y));
    backButton->addClickEventListener([=](Ref* sender){
    	MyPurchase::purgePurchase();
        Director::getInstance()->replaceScene(HelloWorld::scene());
    });
    addChild(backButton);

    auto panel = Layout::create();
    panel->setAnchorPoint(Vec2(0.5,0.5));
    panel->setPosition(Vec2(origin.x + winSize.width/2, origin.y + winSize.height/2));
    panel->setLayoutType(LayoutType::VERTICAL);
    addChild(panel);

    //Google IAP button
    auto btnGoogle = Button::create("btn_normal.png","btn_pressed.png");
    btnGoogle->setTitleText("Google");
    btnGoogle->setScale(2);
    btnGoogle->addClickEventListener([=](Ref* sender){
    	//Perform IAP callback
        TProductInfo pInfo;
        MyPurchase::MyPayMode mode = MyPurchase::MyPayMode::eGoogle;
    	pInfo["IAPId"] = "android.test.purchased";
        MyPurchase::getInstance()->payByMode(pInfo, mode);

    });
    panel->addChild(btnGoogle);    


    return true;
}
