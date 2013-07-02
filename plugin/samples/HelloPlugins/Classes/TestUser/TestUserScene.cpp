#include "TestUserScene.h"
#include "MyUserManager.h"
#include "HelloWorldScene.h"

USING_NS_CC;

const std::string s_aTestCases[] = {
    "QH360",
    "ND91",
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

    MyUserManager::sharedManager()->loadPlugin();
    Size visibleSize = Director::sharedDirector()->getVisibleSize();
    Point origin = Director::sharedDirector()->getVisibleOrigin();
    Point posMid = ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    Point posBR = ccp(origin.x + visibleSize.width, origin.y);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    MenuItemFont *pBackItem = MenuItemFont::create("Back", CC_CALLBACK_1(TestUser::menuBackCallback, this));
    Size backSize = pBackItem->getContentSize();
    pBackItem->setPosition(ccpAdd(posBR, ccp(- backSize.width / 2, backSize.height / 2)));

    // create menu, it's an autorelease object
    Menu* pMenu = Menu::create(pBackItem, NULL);
    pMenu->setPosition(PointZero);

    LabelTTF* label1 = LabelTTF::create("Login", "Arial", 32);
    MenuItemLabel* pItemLogin = MenuItemLabel::create(label1, CC_CALLBACK_1(TestUser::testLogin, this));
    pItemLogin->setAnchorPoint(ccp(0.5f, 0));
    pMenu->addChild(pItemLogin, 0);
    pItemLogin->setPosition(ccpAdd(posMid, ccp(-100, -120)));

    LabelTTF* label2 = LabelTTF::create("Logout", "Arial", 32);
    MenuItemLabel* pItemLogout = MenuItemLabel::create(label2, CC_CALLBACK_1(TestUser::testLogout, this));
    pItemLogout->setAnchorPoint(ccp(0.5f, 0));
    pMenu->addChild(pItemLogout, 0);
    pItemLogout->setPosition(ccpAdd(posMid, ccp(100, -120)));

    // create optional menu
    // cases item
    _caseItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(TestUser::caseChanged, this),
                                                MenuItemFont::create( s_aTestCases[0].c_str() ),
                                                NULL );
    int caseLen = sizeof(s_aTestCases) / sizeof(std::string);
    for (int i = 1; i < caseLen; ++i)
    {
        _caseItem->getSubItems()->addObject( MenuItemFont::create( s_aTestCases[i].c_str() ) );
    }
    _caseItem->setPosition(ccpAdd(posMid, ccp(0, 120)));
    pMenu->addChild(_caseItem);

    _selectedCase = 0;

    this->addChild(pMenu, 1);
    return true;
}

void TestUser::caseChanged(Object* pSender)
{
    _selectedCase = _caseItem->getSelectedIndex();
}

void TestUser::testLogin(Object* pSender)
{
    MyUserManager::sharedManager()->loginByMode((MyUserManager::MyUserMode) (_selectedCase + 1));
}

void TestUser::testLogout(Object* pSender)
{
    MyUserManager::sharedManager()->logoutByMode((MyUserManager::MyUserMode) (_selectedCase + 1));
}

void TestUser::menuBackCallback(Object* pSender)
{
    MyUserManager::purgeManager();

    Scene* newScene = HelloWorld::scene();
    Director::sharedDirector()->replaceScene(newScene);
}
