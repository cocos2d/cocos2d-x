// Helloworld-win32.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Helloworld-win32.h"

using namespace cocos2d;

#define IMG_PATH        "HelloWorld.png"

static HINSTANCE s_hInstance;

//////////////////////////////////////////////////////////////////////////
// implement MyLayer
//////////////////////////////////////////////////////////////////////////

class MyLayer : public CCLayer
{
public:
	virtual void onEnter()
	{
		CCLayer::onEnter();
		setIsTouchEnabled(true);
	}

	virtual bool ccTouchBegan(CCTouch *pTouch, UIEvent *pEvent)
	{
		CCDirector::sharedDirector()->end();
		return true;
	}

	virtual void registerWithTouchDispatcher(void)
	{
		CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
	}
};

//////////////////////////////////////////////////////////////////////////
// implement HelloWorldApplication
//////////////////////////////////////////////////////////////////////////

bool HelloWorldApplication::applicationDidFinishLaunching()
{
    // init the window
    if (!m_MainForm.Create(L"HelloWorld", 480, 320) )
	{
		return false;
	}

    
	// init director
	CCDirector::sharedDirector()->setOpenGLView(&m_MainForm);

	// load background image texture and get window size
	CCTexture2D * pTexture = CCTextureCache::sharedTextureCache()->addImage(IMG_PATH);
	CGSize size = CCDirector::sharedDirector()->getWinSize();

	// create sprite instance
	CCSprite * pSprite = new CCSprite(); 
	pSprite->initWithTexture(pTexture);
	pSprite->setPosition(CGPoint(size.width / 2, size.height / 2));

	// create layer instance
	CCLayer * pLayer = new MyLayer();
	pLayer->addChild(pSprite);

	// add layer to scene
	CCScene * pScene = CCScene::node();
	pScene->addChild(pLayer);

	// add scene to director
	CCDirector::sharedDirector()->runWithScene(pScene);

	pSprite->release();
	pLayer->release();

	return true;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	s_hInstance = hInstance;

	int nRet = 0;
	HelloWorldApplication app;
	nRet = app.Run();
	return nRet;
}
