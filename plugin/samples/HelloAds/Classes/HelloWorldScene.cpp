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

USING_NS_CC;
using namespace cocos2d::plugin;

const std::string s_aTestCases[] = {
	"Admob",
};

const std::string s_aTestTypes[] = {
	"Banner",
	"Full Screen",
    "More App",
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
    
    _admob = dynamic_cast<ProtocolAds*>(PluginManager::getInstance()->loadPlugin("AdsAdmob"));
    TAdsDeveloperInfo devInfo;
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    devInfo["AdmobID"] = "a1517500cc8f794";
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    devInfo["AdmobID"] = "a1516fb6b16b12f";
#endif
    
    _admob->configDeveloperInfo(devInfo);
    _listener = new MyAdsListener();
    _admob->setAdsListener(_listener);
    _admob->setDebugMode(true);

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

	LabelTTF* label1 = LabelTTF::create("ShowAds", "Arial", 24);
	MenuItemLabel* pItemShow = MenuItemLabel::create(label1, CC_CALLBACK_1(HelloWorld::testShow, this));
	pItemShow->setAnchorPoint(ccp(0.5f, 0));
	pMenu->addChild(pItemShow, 0);
	pItemShow->setPosition(ccpAdd(posMid, ccp(-100, -120)));

	LabelTTF* label2 = LabelTTF::create("HideAds", "Arial", 24);
	MenuItemLabel* pItemHide = MenuItemLabel::create(label2, CC_CALLBACK_1(HelloWorld::testHide, this));
	pItemHide->setAnchorPoint(ccp(0.5f, 0));
	pMenu->addChild(pItemHide, 0);
	pItemHide->setPosition(ccpAdd(posMid, ccp(100, -120)));

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
	_caseItem->setPosition(ccpAdd(posMid, ccp(-200, 120)));
	pMenu->addChild(_caseItem);

	// type item
	_typeItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(HelloWorld::typeChanged, this),
												MenuItemFont::create( s_aTestTypes[0].c_str() ),
												NULL );
	int typeLen = sizeof(s_aTestTypes) / sizeof(std::string);
	for (int i = 1; i < typeLen; ++i)
	{
		_typeItem->getSubItems()->addObject( MenuItemFont::create( s_aTestTypes[i].c_str() ) );
	}
	_typeItem->setPosition(ccpAdd(posMid, ccp(0, 120)));
	pMenu->addChild(_typeItem);

	// poses item
	_posItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(HelloWorld::posChanged, this),
												MenuItemFont::create( s_aTestPoses[0].c_str() ),
												NULL );
	int posLen = sizeof(s_aTestPoses) / sizeof(std::string);
	for (int i = 1; i < posLen; ++i)
	{
		_posItem->getSubItems()->addObject( MenuItemFont::create( s_aTestPoses[i].c_str() ) );
	}
	_posItem->setPosition(ccpAdd(posMid, ccp(200, 120)));
	pMenu->addChild(_posItem);

	// init options
	_ads = _admob;
	_pos = ProtocolAds::kPosCenter;
	_type = ProtocolAds::kBannerAd;

    this->addChild(pMenu, 1);

    return true;
}

void HelloWorld::testShow(Object* pSender)
{
    int nSize = 0;
	if (_ads == _admob)
	{
	    nSize = 0;
	}

    if (_ads)
	{
        _ads->showAds(_type, nSize, _pos);
	}
}

void HelloWorld::testHide(Object* pSender)
{
	_ads->hideAds(_type);
}

void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::sharedDirector()->end();

    if (_admob != NULL)
    {
    	PluginManager::getInstance()->unloadPlugin("AdsAdmob");
    	_admob = NULL;
    }

    if (NULL != _listener)
    {
    	delete _listener;
    	_listener = NULL;
    }

    PluginManager::end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::caseChanged(Object* pSender)
{
	std::string strLog = "";
	switch (_caseItem->getSelectedIndex())
	{
	case 0:
		_ads = _admob;
		strLog = "Admob";
		break;
	default:
		break;
	}
	CCLog("case selected change to : %s", strLog.c_str());
}

void HelloWorld::typeChanged(Object* pSender)
{
	int selectIndex = _typeItem->getSelectedIndex();
	_type = (ProtocolAds::AdsType) selectIndex;
	CCLog("type selected change to : %d", _type);
}

void HelloWorld::posChanged(Object* pSender)
{
	int selectIndex = _posItem->getSelectedIndex();
	_pos = (ProtocolAds::AdsPos) selectIndex;
	CCLog("pos selected change to : %d", _pos);
}

void MyAdsListener::onAdsResult(AdsResultCode code, const char* msg)
{
	CCLog("OnAdsResult, code : %d, msg : %s", code, msg);
}

void MyAdsListener::onPlayerGetPoints(cocos2d::plugin::ProtocolAds* pAdsPlugin, int points)
{
	CCLog("Player get points : %d", points);

	// @warning should add code to give game-money to player here

	// spend the points of player
	if (pAdsPlugin != NULL) {
		pAdsPlugin->spendPoints(points);
	}
}
