#include "HelloWorldScene.h"
#include "MyUserManager.h"

USING_NS_CC;

const std::string s_aTestCases[] = {
    "QH360",
    "ND91",
};

Scene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
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
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::sharedDirector()->getVisibleSize();
    Point origin = Director::sharedDirector()->getVisibleOrigin();
    Point posMid = ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    MenuItemImage *pCloseItem = MenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    Menu* pMenu = Menu::create(pCloseItem, NULL);
    pMenu->setPosition(PointZero);

    LabelTTF* label1 = LabelTTF::create("Login", "Arial", 32);
    MenuItemLabel* pItemLogin = MenuItemLabel::create(label1, CC_CALLBACK_1(HelloWorld::testLogin, this));
    pItemLogin->setAnchorPoint(ccp(0.5f, 0));
    pMenu->addChild(pItemLogin, 0);
    pItemLogin->setPosition(ccpAdd(posMid, ccp(-100, -120)));

    LabelTTF* label2 = LabelTTF::create("Logout", "Arial", 32);
    MenuItemLabel* pItemLogout = MenuItemLabel::create(label2, CC_CALLBACK_1(HelloWorld::testLogout, this));
    pItemLogout->setAnchorPoint(ccp(0.5f, 0));
    pMenu->addChild(pItemLogout, 0);
    pItemLogout->setPosition(ccpAdd(posMid, ccp(100, -120)));

    // create optional menu
    // cases item
    _caseItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(HelloWorld::caseChanged, this),
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

void HelloWorld::caseChanged(Object* pSender)
{
    _selectedCase = _caseItem->getSelectedIndex();
}

void HelloWorld::testLogin(Object* pSender)
{
    MyUserManager::sharedManager()->loginByMode((MyUserManager::MyUserMode) (_selectedCase + 1));
}

void HelloWorld::testLogout(Object* pSender)
{
    MyUserManager::sharedManager()->logoutByMode((MyUserManager::MyUserMode) (_selectedCase + 1));
}

void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
