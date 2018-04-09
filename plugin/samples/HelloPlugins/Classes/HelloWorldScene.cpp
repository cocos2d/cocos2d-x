#include "HelloWorldScene.h"
#include "TestAdsScene.h"
#include "TestAnalyticsScene.h"
#include "TestShareScene.h"
#include "TestIAPScene.h"
#include "TestIAPOnlineScene.h"
#include "TestUserScene.h"
#include "TestSocialScene.h"
#include "TestFacebookUserScene.h"
#include "TestFacebookShare.h"

USING_NS_CC;

std::string g_testCases[] = {
    "Test Ads",
    "Test Analytics",
    "Test Share",
    "Test Facebook User",
    "Test Facebook Share",
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    "Test IAP",
    "Test IAP Online",
    "Test User",
    "Test Social",
#endif
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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    MenuItemImage *pCloseItem = MenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	pCloseItem->setPosition(Point(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    Menu* pMenu = Menu::create(pCloseItem, NULL);
    pMenu->setPosition(Point::ZERO);
    this->addChild(pMenu, 1);

    Point beginPos = Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 50);
    float step = 60.0f;
    int nCaseCount = sizeof(g_testCases) / sizeof(std::string);
    for (int i = 0; i < nCaseCount; ++i) {
        std::string caseName = g_testCases[i];
        MenuItemFont *pItem = MenuItemFont::create(caseName.c_str(), CC_CALLBACK_1(HelloWorld::menuCallback, this));
        pItem->setTag(i);
        pItem->setPosition(Point(beginPos.x, beginPos.y - i * step));
        pMenu->addChild(pItem);
    }
    return true;
}

void HelloWorld::menuCallback(Ref* pSender)
{
    MenuItemFont *pItem = (MenuItemFont*) pSender;
    Scene* newScene = NULL;
    switch (pItem->getTag()) {
    case 0:
        newScene = TestAds::scene();
        break;
    case 1:
        newScene = TestAnalytics::scene();
        break;
    case 2:
        newScene = TestShare::scene();
        break;
    case 3:
        newScene = TestFacebookUser::scene();
        break;
    case 4:
        newScene = TestFacebookShare::scene();
        break;
    case 5:
        newScene = TestIAP::scene();
        break;
    case 6:
        newScene = TestIAPOnline::scene();
        break;
    case 7:
        newScene = TestUser::scene();
        break;
    case 8:
        newScene = TestSocial::scene();
        break;
    case 9:
        break;
    default:
        break;
    }

    if (newScene) {
        Director::getInstance()->replaceScene(newScene);
    }
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
