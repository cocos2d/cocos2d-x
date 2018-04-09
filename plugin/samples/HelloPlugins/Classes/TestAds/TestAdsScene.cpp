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
#include "TestAdsScene.h"
#include "PluginManager.h"
#include "HelloWorldScene.h"
#include "Configs.h"

USING_NS_CC;
using namespace cocos2d::plugin;

const std::string s_aTestAdType[] = {
    
    "Banner",
    "Interstitial"
};

const std::string s_aTestCases[] = {
	"Admob",
    "Flurry",
    "Facebook"
};

const std::string s_aTestPoses[] = {
	"Pos: Center",
	"Pos: Top",
	"Pos: TopLeft",
	"Pos: TopRight",
	"Pos: Bottom",
	"Pos: BottomLeft",
	"Pos: BottomRight",
};

Scene* TestAds::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    TestAds *layer = TestAds::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestAds::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    _listener = new MyAdsListener();
    _admob = dynamic_cast<ProtocolAds*>(PluginManager::getInstance()->loadPlugin("AdsAdmob"));
    _flurryAds = dynamic_cast<ProtocolAds*>(PluginManager::getInstance()->loadPlugin("AdsFlurry"));
    _facebookAds = dynamic_cast<ProtocolAds*>(PluginManager::getInstance()->loadPlugin("AdsFacebook"));
    
    TAdsDeveloperInfo devInfo;
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    devInfo["AdmobID"]      = ADMOB_ID_IOS;
    devInfo["FlurryAppKey"] = FLURRY_KEY_IOS;
    devInfo["FacebookAdID"]   = FACEBOOK_KEY_IOS;
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    devInfo["AdmobID"]      = ADMOB_ID_ANDROID;
    devInfo["FlurryAppKey"] = FLURRY_KEY_ANDROID;
    devInfo["FacebookAdID"]   = FACEBOOK_KEY_ANDROID;
#endif
    
    _admob->configDeveloperInfo(devInfo);
    _admob->setAdsListener(_listener);
    _admob->setDebugMode(true);

    _flurryAds->configDeveloperInfo(devInfo);
    _flurryAds->setAdsListener(_listener);
    _flurryAds->setDebugMode(true);
    
    _facebookAds->configDeveloperInfo(devInfo);
    _facebookAds->setAdsListener(_listener);
    _facebookAds->setDebugMode(true);
    PluginParam pParam2("7d842b871e121416b2f732443a355523");
    _facebookAds->callFuncWithParam("addTestDevice", &pParam2, NULL);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    Point posMid = Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    Point posBR = Point(origin.x + visibleSize.width, origin.y);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    MenuItemFont *pBackItem = MenuItemFont::create("Back", CC_CALLBACK_1(TestAds::menuBackCallback, this));
    Size backSize = pBackItem->getContentSize();
    pBackItem->setPosition(posBR + Point(- backSize.width / 2, backSize.height / 2));

    // create menu, it's an autorelease object
    Menu* pMenu = Menu::create(pBackItem, NULL);
    pMenu->setPosition( Point::ZERO );

	Label* label1 = Label::create("ShowAds", "Arial", 24);
	MenuItemLabel* pItemShow = MenuItemLabel::create(label1, CC_CALLBACK_1(TestAds::testShow, this));
	pItemShow->setAnchorPoint(Point(0.5f, 0));
	pMenu->addChild(pItemShow, 0);
	pItemShow->setPosition(posMid + Point(-100, -120));

	Label* label2 = Label::create("HideAds", "Arial", 24);
	MenuItemLabel* pItemHide = MenuItemLabel::create(label2, CC_CALLBACK_1(TestAds::testHide, this));
	pItemHide->setAnchorPoint(Point(0.5f, 0));
	pMenu->addChild(pItemHide, 0);
	pItemHide->setPosition(posMid + Point(100, -120));

	// create optional menu
	// cases item
	_caseItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(TestAds::caseChanged, this),
												MenuItemFont::create( s_aTestCases[0].c_str() ),
												NULL );
	int caseLen = sizeof(s_aTestCases) / sizeof(std::string);
	for (int i = 1; i < caseLen; ++i)
	{
		_caseItem->getSubItems().pushBack(MenuItemFont::create( s_aTestCases[i].c_str() ) );
	}
	_caseItem->setPosition(posMid + Point(-200, 120));
	pMenu->addChild(_caseItem);

	// poses item
	_posItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(TestAds::posChanged, this),
												MenuItemFont::create( s_aTestPoses[0].c_str() ),
												NULL );
	int posLen = sizeof(s_aTestPoses) / sizeof(std::string);
	for (int i = 1; i < posLen; ++i)
	{
		_posItem->getSubItems().pushBack( MenuItemFont::create( s_aTestPoses[i].c_str() ) );
	}
	_posItem->setPosition(posMid + Point(200, 120));
	pMenu->addChild(_posItem);
    
    // type item
    _typeItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(TestAds::typeChanged, this),
                                                   MenuItemFont::create(s_aTestAdType[0].c_str()),
                                                   NULL);
    
    int typeLen = sizeof(s_aTestAdType) / sizeof(std::string);
    for (int i = 1; i < typeLen; ++i)
    {
        _typeItem->getSubItems().pushBack(MenuItemFont::create(s_aTestAdType[i].c_str()));
    }
    
    _typeItem->setPosition(posMid + Point(0,120));
    pMenu->addChild(_typeItem);

	// init options
	_ads = _admob;
	_pos = ProtocolAds::kPosCenter;

    // init the AdsInfo
    adInfo["AdmobType"] = "1";
    adInfo["AdmobSizeEnum"] = "1";
    adInfo["FlurryAdsID"] = "BANNER_MAIN_VC";
    adInfo["FlurryAdsSize"] = "2";
    adInfo["FBAdType"] = "1";
    adInfo["FBAdSizeEnum"] = "1";

    this->addChild(pMenu, 1);

    return true;
}

void TestAds::testShow(Ref* pSender)
{
    if (_ads)
	{
        _ads->showAds(adInfo, _pos);
	}
}

void TestAds::testHide(Ref* pSender)
{
	_ads->hideAds(adInfo);
}

void TestAds::menuBackCallback(Ref* pSender)
{
    if (_admob != NULL)
    {
        _admob->hideAds(adInfo);
    	PluginManager::getInstance()->unloadPlugin("AdsAdmob");
    	_admob = NULL;
    }
    
    if (_facebookAds != NULL)
    {
        _facebookAds->hideAds(adInfo);
        PluginManager::getInstance()->unloadPlugin("AdsFacebook");
        _facebookAds = NULL;
    }

    if (NULL != _listener)
    {
    	delete _listener;
    	_listener = NULL;
    }

    Scene* newScene = HelloWorld::scene();
    Director::getInstance()->replaceScene(newScene);
}

void TestAds::caseChanged(Ref* pSender)
{
	std::string strLog = "";
	switch (_caseItem->getSelectedIndex())
	{
        case 0:
            _ads = _admob;
            strLog = "Admob";
            break;
        case 1:
            _ads = _flurryAds;
            strLog = "Flurry Ads";
            break;
        case 2:
            _ads = _facebookAds;
            strLog = "Facebook Ads";
            break;
        default:
            break;
	}
	log("case selected change to : %s", strLog.c_str());
}

void TestAds::posChanged(Ref* pSender)
{
	int selectIndex = _posItem->getSelectedIndex();
	_pos = (ProtocolAds::AdsPos) selectIndex;
	log("pos selected change to : %d", _pos);
}

void TestAds::typeChanged(cocos2d::Ref *pSender)
{
    int selectedIndex = _typeItem->getSelectedIndex();
    
    switch (selectedIndex)
    {
        case 0:
            // Banner
            // init the AdsInfo
            adInfo["AdmobType"] = "1";
            adInfo["FBAdType"] = "1";
            break;
        case 1:
            // Interstitial
            // init the AdsInfo
            adInfo["AdmobType"] = "2";
            adInfo["FBAdType"] = "2";
            break;
        default:
            break;
    }
    if (_admob != NULL)
    {
        log("type ad changed to : %s", s_aTestAdType[selectedIndex].c_str());
    }
}

void MyAdsListener::onAdsResult(AdsResultCode code, const char* msg)
{
	log("OnAdsResult, code : %d, msg : %s", code, msg);
}

void MyAdsListener::onPlayerGetPoints(cocos2d::plugin::ProtocolAds* pAdsPlugin, int points)
{
	log("Player get points : %d", points);

	// @warning should add code to give game-money to player here

	// spend the points of player
	if (pAdsPlugin != NULL) {
		pAdsPlugin->spendPoints(points);
	}
}
