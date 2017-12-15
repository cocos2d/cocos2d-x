/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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
#include "TestUserScene.h"
#include "MyUserManager.h"
#include "HelloWorldScene.h"

USING_NS_CC;

const std::string s_aTestCases[] = {
    "QH360",
    "ND91",
#if TEST_UC
    "UC",
#endif
};

Scene* TestUser::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    TestUser *layer = TestUser::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestUser::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    MyUserManager::getInstance()->loadPlugin();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    Point posMid = Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    Point posBR = Point(origin.x + visibleSize.width, origin.y);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    MenuItemFont *pBackItem = MenuItemFont::create("Back", CC_CALLBACK_1(TestUser::menuBackCallback, this));
    Size backSize = pBackItem->getContentSize();
    pBackItem->setPosition(posBR + Point(- backSize.width / 2, backSize.height / 2));

    // create menu, it's an autorelease object
    Menu* pMenu = Menu::create(pBackItem, NULL);
    pMenu->setPosition(Point::ZERO);

    Label* label1 = Label::create("Login", "Arial", 32);
    MenuItemLabel* pItemLogin = MenuItemLabel::create(label1, CC_CALLBACK_1(TestUser::testLogin, this));
    pItemLogin->setAnchorPoint(Point(0.5f, 0));
    pMenu->addChild(pItemLogin, 0);
    pItemLogin->setPosition(posMid + Point(-100, -120));

    Label* label2 = Label::create("Logout", "Arial", 32);
    MenuItemLabel* pItemLogout = MenuItemLabel::create(label2, CC_CALLBACK_1(TestUser::testLogout, this));
    pItemLogout->setAnchorPoint(Point(0.5f, 0));
    pMenu->addChild(pItemLogout, 0);
    pItemLogout->setPosition(posMid + Point(100, -120));

    // create optional menu
    // cases item
    _caseItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(TestUser::caseChanged, this),
                                                MenuItemFont::create( s_aTestCases[0].c_str() ),
                                                NULL );
    int caseLen = sizeof(s_aTestCases) / sizeof(std::string);
    for (int i = 1; i < caseLen; ++i)
    {
        _caseItem->getSubItems().pushBack( MenuItemFont::create( s_aTestCases[i].c_str() ) );
    }
    _caseItem->setPosition(posMid + Point(0, 120));
    pMenu->addChild(_caseItem);

    _selectedCase = 0;

    this->addChild(pMenu, 1);
    return true;
}

void TestUser::caseChanged(Ref* pSender)
{
    _selectedCase = _caseItem->getSelectedIndex();
}

void TestUser::testLogin(Ref* pSender)
{
    MyUserManager::getInstance()->loginByMode((MyUserManager::MyUserMode) (_selectedCase + 1));
}

void TestUser::testLogout(Ref* pSender)
{
    MyUserManager::getInstance()->logoutByMode((MyUserManager::MyUserMode) (_selectedCase + 1));
}

void TestUser::menuBackCallback(Ref* pSender)
{
    MyUserManager::purgeManager();

    Scene* newScene = HelloWorld::scene();
    Director::getInstance()->replaceScene(newScene);
}
