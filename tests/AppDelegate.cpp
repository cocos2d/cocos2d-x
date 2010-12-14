#include "AppDelegate.h"
#include "cocos2d.h"
#include "tests/controller.h"

using namespace cocos2d;

// static void TimerCallback1(Int32 nTimerId, UInt32 uUserData);
AppDelegate::AppDelegate()
:m_pMainWnd(NULL)
{

}

AppDelegate::~AppDelegate()
{
#if defined(CCX_PLATFORM_WIN32)
    CCX_SAFE_DELETE(m_pMainWnd);
#endif
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// init the window
#if defined(CCX_PLATFORM_UPHONE)
	if (!(m_pMainWnd = new CCXEGLView(this)) || 
		! m_pMainWnd->Create(&TRectangle(0,0,GetScreenWidth(),GetScreenHeight())))
#elif defined(CCX_PLATFORM_WIN32)
	if (!(m_pMainWnd = new CCXEGLView()) ||
		! m_pMainWnd->Create(L"cocos2d-win32", 320, 480) )
#elif defined(CCX_PLATFORM_IPHONE)
    if (!(m_pMainWnd = new CCXEGLView()))
#elif defined(CCX_PLATFORM_ANDROID)
    if (!(m_pMainWnd = CCDirector::sharedDirector()->getOpenGLView()))
#elif defined(CCX_PLATFORM_BADA)
    if (!(m_pMainWnd = new CCXEGLView()) || !m_pMainWnd->Create(this))
#else
    #error
#endif
	{
        CCX_SAFE_DELETE(m_pMainWnd);
		return false;
	}

    // init director
    CCDirector * pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(m_pMainWnd);
    pDirector->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);
	// pDirector->setDeviceOrientation(kCCDeviceOrientationPortrait);
    pDirector->setDisplayFPS(true);

#if defined(CCX_PLATFORM_UPHONE)

#if 1
    // set the resource path
    CCFileUtils::setResourcePath("/NEWPLUS/TDA_DATA/Data/cocos2d_tests/");
#else
    // set the resource zip file
    CCFileUtils::setResourceZipFile("/NEWPLUS/TDA_DATA/Data/cocos2d_tests/cocos2d_tests.zip");
#endif


#elif defined(CCX_PLATFORM_ANDROID)
    CCFileUtils::setResourcePath("/data/app/org.cocos2dx.tests-1.apk");
	CCFileUtils::setRelativePath("assets");
#elif defined(CCX_PLATFORM_BADA)
    // set the resource path
    CCFileUtils::setResourcePath("/Res/");
#endif

#if 0
	// SHOW SPLASH SCREEN

    // load background image texture and get window size
    CCTexture2D * pSplashTexture = CCTextureCache::sharedTextureCache()->addImage("b1.png");
    CGSize size = CCDirector::sharedDirector()->getWinSize();

    // splash sprite
	CCSprite * pSplashSprite = CCSprite::spriteWithTexture(pSplashTexture);
    pSplashSprite->setPosition(CGPoint(size.width / 2, size.height / 2));

    // splash layer
    CCLayer * pSplashLayer = new CCLayer();
    pSplashLayer->addChild(pSplashSprite);
    pSplashLayer->autorelease();

    // add layer to scene
    CCScene * pSplashScene = CCScene::node();
    pSplashScene->addChild(pSplashLayer);

	// add scene to director
    CCDirector::sharedDirector()->runWithScene(pSplashScene);

	// CCSequence::actions(this, callfunc_selector(AppDelegate::replaceSplashScreen))
    m_nTimer = TIMER_Create(3000, TIMER_MODE_NORMAL, TimerCallback1, 0, 0);
    TIMER_Start(m_nTimer, 0);
#endif
    CCScene * pScene = CCScene::node();
    CCLayer * pLayer = new TestController();
    pLayer->autorelease();

    pScene->addChild(pLayer);
	pDirector->runWithScene(pScene);

    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();
}

void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
}

/*
static void TimerCallback1(Int32 nTimerId, UInt32 uUserData)
{
    CCScene * pScene = CCScene::node();
    CCLayer * pLayer = new TestController();
    pLayer->autorelease();

    pScene->addChild(pLayer);
    CCDirector::sharedDirector()->replaceScene(pScene);
}
*/
