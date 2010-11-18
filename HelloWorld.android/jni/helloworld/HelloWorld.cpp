#include "HelloWorld.h"

#include <jni.h>
#include <android/log.h>

using namespace cocos2d;

#define IMG_PATH        "res/drawable/helloworld.png"
#define RESOURCE_PATH	"/data/app/org.cocos2dx.application-1.apk"

class MyLayer : public CCLayer
{
public:
	bool init()
	{
		if( !CCLayer::init())
		{
			return false;
		}

		this->setIsTouchEnabled(true);

		return true;
	};

	void ccTouchesEnded(NSSet* pTouches, UIEvent* pEvent)
    {
        CCDirector::getSharedDirector()->end();
    };

	LAYER_NODE_FUNC(MyLayer);
};

bool HelloWorld::initCocos2d()
{
	 // the view is freeed in CCDirector
	 CCDirector::getSharedDirector()->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);
	 CCDirector::getSharedDirector()->setDisplayFPS(true);
	 	
	 // set resource path
	 CCFileUtils::setResourcePath(RESOURCE_PATH);
 		
     // load background image texture and get window size
     CCTexture2D * pTexture = CCTextureCache::sharedTextureCache()->addImage(IMG_PATH);
     CGSize size = CCDirector::getSharedDirector()->getWinSize();
 
     // create sprite instance
     CCSprite * pSprite = new CCSprite(); 
 	 pSprite->initWithTexture(pTexture);
     pSprite->setPosition(CGPoint(size.width / 2, size.height / 2));
 
     // create layer instance
     CCLayer * pLayer = MyLayer::node();
     pLayer->addChild(pSprite);
 
     // add layer to scene
     CCScene * pScene = CCScene::node();
     pScene->addChild(pLayer);
 
     // add scene to director
     CCDirector::getSharedDirector()->runWithScene(pScene);
 
     pSprite->release();
     
     return true;
}

static HelloWorld *s_pApp;

extern "C"
{
void initProgram()
{
	s_pApp = new HelloWorld();
 	s_pApp->initCocos2d();
}

void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h)
{
	cocos2d::CCXEGLView *view = new cocos2d::CCXEGLView();
 	view->setFrameWitdAndHeight(w, h);
 	cocos2d::CCDirector::getSharedDirector()->setOpenGLView(view);
 		
 	initProgram();
}

}
