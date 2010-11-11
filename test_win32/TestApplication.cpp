#include "TestApplication.h"
#include "main.h"
#include "tests/controller.h"

using namespace cocos2d;

//////////////////////////////////////////////////////////////////////////
// implement TestApplication
//////////////////////////////////////////////////////////////////////////

bool TestApplication::InitInstance()
{
	return m_MainForm.Create(L"Cocos2dx-Win32", 320, 480);
}

bool TestApplication::initCocos2d()
{
	// init director
	CCDirector * pDirector = CCDirector::sharedDirector();
	pDirector->setOpenGLView(&m_MainForm);
	pDirector->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);

	pDirector->setDisplayFPS(true);

	CCScene * pScene = CCScene::node();
	CCLayer * pLayer = new TestController();
	pLayer->autorelease();

	pScene->addChild(pLayer);
	pDirector->runWithScene(pScene);

	return true;
}

void TestApplication::applicationDidEnterBackground()
{
	CCDirector::sharedDirector()->stopAnimation();
}

void TestApplication::applicationWillEnterForeground()
{
	CCDirector::sharedDirector()->startAnimation();
}
