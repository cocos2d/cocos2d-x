#include "HelloWorldScene.h"
#include "PluginManager.h"

USING_NS_CC;
using namespace cocos2d::plugin;

const std::string s_aTestCases[] = {
	"Test: Admob",
};

const std::string s_aTestPoses[] = {
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
    
    m_pAdmob = dynamic_cast<AdsAdmob*>(PluginManager::getInstance()->loadPlugin("AdsAdmob"));
    TAppInfo appInfo;
    appInfo["AdmobID"] = "a1516fb6b16b12f";
    m_pAdmob->initAppInfo(appInfo);
    m_pListener = new MyAdListener();
    ProtocolAds::setAdListener(m_pListener);
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

	CCLabelTTF* label1 = CCLabelTTF::create("ShowAdView", "Arial", 24);
	CCMenuItemLabel* pItemShow = CCMenuItemLabel::create(label1, this, menu_selector(HelloWorld::testShow));
	pItemShow->setAnchorPoint(ccp(0.5f, 0));
	pMenu->addChild(pItemShow, 0);
	pItemShow->setPosition(ccpAdd(posMid, ccp(-100, -50)));

	CCLabelTTF* label2 = CCLabelTTF::create("HideAdView", "Arial", 24);
	CCMenuItemLabel* pItemHide = CCMenuItemLabel::create(label2, this, menu_selector(HelloWorld::testHide));
	pItemHide->setAnchorPoint(ccp(0.5f, 0));
	pMenu->addChild(pItemHide, 0);
	pItemHide->setPosition(ccpAdd(posMid, ccp(100, -50)));

	// create optional menu
	m_pCaseItem = CCMenuItemToggle::createWithTarget(this,
												menu_selector(HelloWorld::caseChanged),
												CCMenuItemFont::create( s_aTestCases[0].c_str() ),
												NULL );
	int caseLen = sizeof(s_aTestCases) / sizeof(std::string);
	for (int i = 1; i < caseLen; ++i)
	{
		m_pCaseItem->getSubItems()->addObject( CCMenuItemFont::create( s_aTestCases[i].c_str() ) );
	}
	m_pCaseItem->setPosition(ccpAdd(posMid, ccp(-150, 50)));
	pMenu->addChild(m_pCaseItem);

	m_pPosItem = CCMenuItemToggle::createWithTarget(this,
												menu_selector(HelloWorld::posChanged),
												CCMenuItemFont::create( s_aTestPoses[0].c_str() ),
												NULL );
	int posLen = sizeof(s_aTestPoses) / sizeof(std::string);
	for (int i = 1; i < posLen; ++i)
	{
		m_pPosItem->getSubItems()->addObject( CCMenuItemFont::create( s_aTestPoses[i].c_str() ) );
	}
	m_pPosItem->setPosition(ccpAdd(posMid, ccp(150, 50)));
	pMenu->addChild(m_pPosItem);

	// init options
	m_pAds = m_pAdmob;
	m_ePos = ProtocolAds::ePosTop;

    this->addChild(pMenu, 1);

    return true;
}

void HelloWorld::testShow(CCObject* pSender)
{
	if (m_pAds == m_pAdmob)
	{
		m_pAds->showBannerAd(m_ePos, AdsAdmob::eSizeBanner);
	}
}

void HelloWorld::testHide(CCObject* pSender)
{
	m_pAds->hideBannerAd();
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

void HelloWorld::posChanged(CCObject* pSender)
{
	switch (m_pPosItem->getSelectedIndex())
	{
	case 0:
		m_ePos = ProtocolAds::ePosTop;
		break;
	case 1:
		m_ePos = ProtocolAds::ePosTopLeft;
		break;
	case 2:
		m_ePos = ProtocolAds::ePosTopRight;
		break;
	case 3:
		m_ePos = ProtocolAds::ePosBottom;
		break;
	case 4:
		m_ePos = ProtocolAds::ePosBottomLeft;
		break;
	case 5:
		m_ePos = ProtocolAds::ePosBottomRight;
		break;
	default:
		break;
	}
	CCLog("pos selected change to : %d", m_ePos);
}

void MyAdListener::onReceiveAd()
{
	CCLog("My listener onReceiveAd");
}

void MyAdListener::onPresentScreen()
{
	CCLog("My listener onPresentScreen");
}

void MyAdListener::onFailedToReceiveAd(EAdErrorCode code, const char* msg)
{
	char logStr[128] = {0};
	sprintf(logStr, "My listener onFailedToReceiveAd, error code : %d, message : %s", code, msg);
	CCLog(logStr);
}

void MyAdListener::onDismissScreen()
{
	CCLog("My listener onDismissScreen");
}
