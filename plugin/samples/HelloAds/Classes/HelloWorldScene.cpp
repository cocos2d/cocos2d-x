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
    
    m_pAdmob = dynamic_cast<ProtocolAds*>(PluginManager::getInstance()->loadPlugin("AdsAdmob"));
    TAdsDeveloperInfo devInfo;
    devInfo["AdmobID"] = "a1516fb6b16b12f";
    m_pAdmob->configDeveloperInfo(devInfo);
    m_pListener = new MyAdsListener();
    m_pAdmob->setAdsListener(m_pListener);
    m_pAdmob->setDebugMode(true);

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCPoint posMid = ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);

	CCLabelTTF* label1 = CCLabelTTF::create("ShowAds", "Arial", 24);
	CCMenuItemLabel* pItemShow = CCMenuItemLabel::create(label1, this, menu_selector(HelloWorld::testShow));
	pItemShow->setAnchorPoint(ccp(0.5f, 0));
	pMenu->addChild(pItemShow, 0);
	pItemShow->setPosition(ccpAdd(posMid, ccp(-100, -120)));

	CCLabelTTF* label2 = CCLabelTTF::create("HideAds", "Arial", 24);
	CCMenuItemLabel* pItemHide = CCMenuItemLabel::create(label2, this, menu_selector(HelloWorld::testHide));
	pItemHide->setAnchorPoint(ccp(0.5f, 0));
	pMenu->addChild(pItemHide, 0);
	pItemHide->setPosition(ccpAdd(posMid, ccp(100, -120)));

	// create optional menu
	// cases item
	m_pCaseItem = CCMenuItemToggle::createWithTarget(this,
												menu_selector(HelloWorld::caseChanged),
												CCMenuItemFont::create( s_aTestCases[0].c_str() ),
												NULL );
	int caseLen = sizeof(s_aTestCases) / sizeof(std::string);
	for (int i = 1; i < caseLen; ++i)
	{
		m_pCaseItem->getSubItems()->addObject( CCMenuItemFont::create( s_aTestCases[i].c_str() ) );
	}
	m_pCaseItem->setPosition(ccpAdd(posMid, ccp(-200, 120)));
	pMenu->addChild(m_pCaseItem);

	// type item
	m_pTypeItem = CCMenuItemToggle::createWithTarget(this,
												menu_selector(HelloWorld::typeChanged),
												CCMenuItemFont::create( s_aTestTypes[0].c_str() ),
												NULL );
	int typeLen = sizeof(s_aTestTypes) / sizeof(std::string);
	for (int i = 1; i < typeLen; ++i)
	{
		m_pTypeItem->getSubItems()->addObject( CCMenuItemFont::create( s_aTestTypes[i].c_str() ) );
	}
	m_pTypeItem->setPosition(ccpAdd(posMid, ccp(0, 120)));
	pMenu->addChild(m_pTypeItem);

	// poses item
	m_pPosItem = CCMenuItemToggle::createWithTarget(this,
												menu_selector(HelloWorld::posChanged),
												CCMenuItemFont::create( s_aTestPoses[0].c_str() ),
												NULL );
	int posLen = sizeof(s_aTestPoses) / sizeof(std::string);
	for (int i = 1; i < posLen; ++i)
	{
		m_pPosItem->getSubItems()->addObject( CCMenuItemFont::create( s_aTestPoses[i].c_str() ) );
	}
	m_pPosItem->setPosition(ccpAdd(posMid, ccp(200, 120)));
	pMenu->addChild(m_pPosItem);

	// init options
	m_pAds = m_pAdmob;
	m_ePos = ProtocolAds::kPosCenter;
	m_eType = ProtocolAds::kBannerAd;

    this->addChild(pMenu, 1);

    return true;
}

void HelloWorld::testShow(CCObject* pSender)
{
    int nSize = 0;
	if (m_pAds == m_pAdmob)
	{
	    nSize = 0;
	}

    if (m_pAds)
	{
        m_pAds->showAds(m_eType, nSize, m_ePos);
	}
}

void HelloWorld::testHide(CCObject* pSender)
{
	m_pAds->hideAds(m_eType);
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

    if (m_pAdmob != NULL)
    {
    	PluginManager::getInstance()->unloadPlugin("AdsAdmob");
    	m_pAdmob = NULL;
    }

    if (NULL != m_pListener)
    {
    	delete m_pListener;
    	m_pListener = NULL;
    }

    PluginManager::end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::caseChanged(CCObject* pSender)
{
	std::string strLog = "";
	switch (m_pCaseItem->getSelectedIndex())
	{
	case 0:
		m_pAds = m_pAdmob;
		strLog = "Admob";
		break;
	default:
		break;
	}
	CCLog("case selected change to : %s", strLog.c_str());
}

void HelloWorld::typeChanged(CCObject* pSender)
{
	int selectIndex = m_pTypeItem->getSelectedIndex();
	m_eType = (ProtocolAds::AdsType) selectIndex;
	CCLog("type selected change to : %d", m_eType);
}

void HelloWorld::posChanged(CCObject* pSender)
{
	int selectIndex = m_pPosItem->getSelectedIndex();
	m_ePos = (ProtocolAds::AdsPos) selectIndex;
	CCLog("pos selected change to : %d", m_ePos);
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
