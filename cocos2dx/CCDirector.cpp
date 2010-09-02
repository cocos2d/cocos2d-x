/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "CCDirector.h"
#include "CCScene.h"
#include "NSMutableArray.h"
#include "CCScheduler.h"
#include "ccMacros.h"
#include "Cocos2dDefine.h"
#include "CCTouchDispatcher.h"
#include "support/opengl_support/glu.h"
#include "CGPointExtension.h"
#include "CCTransition.h"
#include "CCTextureCache.h"
#include "CCTransition.h"
#include "CCSpriteFrameCache.h"
#include "NSAutoreleasePool.h"
#include "platform/platform.h"
#include "CCXApplication.h"
#include "CCBitmapFontAtlas.h"
#include "CCActionManager.h"
#include "CCLabelAtlas.h"

#if CC_ENABLE_PROFILERS
#include "support/CCProfiling.h"
#endif // CC_ENABLE_PROFILERS

#include <string>

using namespace std;
using namespace cocos2d;
namespace  cocos2d 
{

// singleton stuff
static CCDisplayLinkDirector s_sharedDirector;
static bool s_bFirstRun = true;

#define kDefaultFPS		60  // 60 frames per second
extern string cocos2dVersion(void);

CCDirector* CCDirector::getSharedDirector(void)
{
	if (s_bFirstRun)
	{
		s_sharedDirector.init();
        s_bFirstRun = false;
	}

	return &s_sharedDirector;
}

bool CCDirector::setDierectorType(ccDirectorType obDirectorType)
{
	/*
	switch (obDirectorType)
	{
	case CCDirectorTypeNSTimer:
		CCTimerDirector::getSharedDirector();
		break;
	case CCDirectorTypeMainLoop:
		CCFastDirector::getSharedDirector();
		break;
	case CCDirectorTypeThreadMainLoop:
		CCThreadedFastDirector::getSharedDirector();
		break;
	case CCDirectorTypeDiaplayLink:
		CCDisplayLinkDirector::getSharedDirector();
		break;
	default:
        assert(false);
		break;
	}
	*/

    // we only support CCDisplayLinkDirector
	CCDirector::getSharedDirector();

	return true;
}

CCDirector* CCDirector::init(void)
{
	CCLOG("cocos2d: %s", cocos2dVersion());

	CCLOG("cocos2d: Using Director Type: %d", CCDirectorTypeDiaplayLink);

	// default values
    m_ePixelFormat = kCCPixelFormatDefault;
	m_eDepthBufferFormat = kCCDepthBufferNone; // 0

	// scenes
	m_pRunningScene = NULL;
	m_pNextScene = NULL;

	m_dOldAnimationInterval = m_dAnimationInterval = 1.0 / kDefaultFPS;

	m_pobScenesStack = new NSMutableArray<CCScene*>();

	// landspace
	m_eDeviceOrientation = CCDeviceOrientationPortrait;

	// FPS
	m_bDisplayFPS = false;
	m_nFrames = 0;

	// paused ?
	m_bPaused = false;

	m_pobOpenGLView = NULL;

    m_fContentScaleFactor = 1;
	m_obScreenSize = m_obSurfaceSize = CGSizeZero;

	m_pLastUpdate = new struct cc_timeval();

	// create autorelease pool
	NSPoolManager::getInstance()->push();

	return this;
}

CCDirector::~CCDirector(void)
{
	CCLOGINFO("cocos2d: deallocing %p", this);

#if CC_DIRECTOR_FAST_FPS
	CCX_SAFE_RELEASE(m_pFPSLabel);
#endif 
    
	CCX_SAFE_RELEASE(m_pRunningScene);
	CCX_SAFE_RELEASE(m_pobScenesStack);


	// pop the autorelease pool
	NSPoolManager::getInstance()->pop();

	// delete m_pLastUpdate
	delete m_pLastUpdate;
	m_pLastUpdate = NULL;
}

void CCDirector::setGLDefaultValues(void)
{
	// This method SHOULD be called only after openGLView_ was initialized
	assert(m_pobOpenGLView);

	setAlphaBlending(true);
	setDepthTest(true);
	setProjection(kCCDirectorProjectionDefault);

	// set other opengl default values
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

#if CC_DIRECTOR_FAST_FPS
	if (! m_pFPSLabel)
	{
		CCTexture2DPixelFormat currentFormat = CCTexture2D::defaultAlphaPixelFormat();
		CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA4444);
		m_pFPSLabel = CCLabelAtlas::labelAtlasWithString("00.0", "fps_images.png", 16, 24, '.');
		m_pFPSLabel->retain();
		CCTexture2D::setDefaultAlphaPixelFormat(currentFormat);
	}
#endif
}

// main loop
void CCDirector::mainLoop(void)
{
	// calculate "global" dt
	calculateDeltaTime();

	//tick before glClear: issue #533
	if (! m_bPaused)
	{
		CCScheduler::getSharedScheduler()->tick(m_fDeltaTime);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* to avoid flickr, nextScene MUST be here: after tick and before draw.
	 XXX: Which bug is this one. It seems that it can't be reproduced with v0.9 */
	if (m_pNextScene)
	{
		setNextScene();
	}

	glPushMatrix();

	applyLandspace();

	// By default enable VertexArray, ColorArray, TextureCoordArray and Texture2D
	CC_ENABLE_DEFAULT_GL_STATES();

	// draw the scene
    if (m_pRunningScene)
    {
        m_pRunningScene->visit();
    }

	if (m_bDisplayFPS)
	{
		showFPS();
	}

#if CC_ENABLE_PROFILERS
	showProfilers();
#endif

	CC_DISABLE_DEFAULT_GL_STATES();

	glPopMatrix();

	// swap buffers
	m_pobOpenGLView->swapBuffers();
}

void CCDirector::calculateDeltaTime(void)
{
    struct cc_timeval now;

	if (CCTime::gettimeofdayCocos2d(&now, NULL) != 0)
	{
		CCLOG("error in gettimeofday");
        m_fDeltaTime = 0;
		return;
	}

	// new delta time
	if (m_bNextDeltaTimeZero)
	{
		m_fDeltaTime = 0;
		m_bNextDeltaTimeZero = false;
	}
	else 
	{
		m_fDeltaTime = (now.tv_sec - m_pLastUpdate->tv_sec) + (now.tv_usec - m_pLastUpdate->tv_usec) / 1000000.0f;
		m_fDeltaTime = MAX(0, m_fDeltaTime);
	}

	*m_pLastUpdate = now;
}


// m_dAnimationInterval
void CCDirector::setAnimationInterval(double dValue)
{
	CCLOG("cocos2d: Director#setAnimationInterval. Overrride me");
	assert(0);
}


// m_pobOpenGLView

void CCDirector::setOpenGLView(CCXEGLView *pobOpenGLView)
{
	assert(pobOpenGLView);

	if (m_pobOpenGLView != pobOpenGLView)
	{
		// because EAGLView is not kind of NSObject
		delete m_pobOpenGLView; // [openGLView_ release]
		m_pobOpenGLView = pobOpenGLView;

		// set size
		m_obScreenSize = pobOpenGLView->getSize();
		m_obSurfaceSize = CGSizeMake(m_obScreenSize.width * m_fContentScaleFactor,
			m_obScreenSize.height * m_fContentScaleFactor);

 		CCTouchDispatcher *pTouchDispatcher = CCTouchDispatcher::getSharedDispatcher();
 		m_pobOpenGLView->setTouchDelegate(pTouchDispatcher);
        pTouchDispatcher->setDispatchEvents(true);

		setGLDefaultValues();
	}
}

void CCDirector::setNextDeltaTimeZero(bool bNextDeltaTimeZero)
{
	m_bNextDeltaTimeZero = bNextDeltaTimeZero;
}

// m_eDeviceOrientation
void CCDirector::setDeviceOrientation(ccDeviceOrientation kDeviceOrientation)
{
	if (m_eDeviceOrientation != kDeviceOrientation)
	{
		m_eDeviceOrientation = kDeviceOrientation;

		switch (m_eDeviceOrientation)
		{
		case CCDeviceOrientationPortrait:
			CCXApplication::getSharedApplication()->setDeviceOrientation(CCDeviceOrientationPortrait);
			break;
        case CCDeviceOrientationPortraitUpsideDown:
			CCXApplication::getSharedApplication()->setDeviceOrientation(CCDeviceOrientationPortraitUpsideDown);
			break;
        case CCDeviceOrientationLandscapeLeft:
			CCXApplication::getSharedApplication()->setDeviceOrientation(CCDeviceOrientationLandscapeLeft);
			break;
        case CCDeviceOrientationLandscapeRight:
			CCXApplication::getSharedApplication()->setDeviceOrientation(CCDeviceOrientationLandscapeRight);
			break;
		default:
			CCLOG("Director: Unknown device orientation");
			break;
		}
	}
}

void CCDirector::setProjection(ccDirectorProjection kProjection)
{
	CGSize size = m_obSurfaceSize;
	switch (kProjection)
	{
	case kCCDirectorProjection2D:
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrthof(0, size.width, 0, size.height, -1000, 1000);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		break;

	case kCCDirectorProjection3D:
		glViewport(0, 0, (GLsizei)size.width, (GLsizei)size.height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60, (GLfloat)size.width/size.height, 0.5f, 1500.0f);
			
		glMatrixMode(GL_MODELVIEW);	
		glLoadIdentity();
		gluLookAt( size.width/2, size.height/2, getZEye(),
				 size.width/2, size.height/2, 0,
				 0.0f, 1.0f, 0.0f);				
		break;
			
	case kCCDirectorProjectionCustom:
		// if custom, ignore it. The user is resposible for setting the correct projection
		break;
			
	default:
		CCLOG("cocos2d: Director: unrecognized projecgtion");
		break;
	}

	m_eProjection = kProjection;
}

void CCDirector::purgeCachedData(void)
{
    CCBitmapFontAtlas::purgeCachedData();
	CCSpriteFrameCache::purgeSharedSpriteFrameCache();
	CCTextureCache::purgeSharedTextureCache();
}

float CCDirector::getZEye(void)
{
	return (m_obSurfaceSize.height / 1.1566f);
}

void CCDirector::setAlphaBlending(bool bOn)
{
	if (bOn)
	{
		glEnable(GL_BLEND);
		glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
	}
	else
	{
		glDisable(GL_BLEND);
	}
}

void CCDirector::setDepthTest(bool bOn)
{
	if (bOn)
	{
		glClearDepthf(1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}
}

// is the view currently attached
bool CCDirector::isOpenGLAttached(void)
{
	return m_pobOpenGLView->isOpenGLReady();
}

// detach or attach to a view or a window
bool CCDirector::detach(void)
{
	assert(isOpenGLAttached());

	CCX_SAFE_DELETE(m_pobOpenGLView);
	return true;
}

CGPoint CCDirector::convertToGL(CGPoint obPoint)
{
	CGSize s = m_obScreenSize;
	float newY = s.height - obPoint.y;
	float newX = s.width - obPoint.x;

	CGPoint ret;
	switch (m_eDeviceOrientation)
	{
	case CCDeviceOrientationPortrait:
		ret = ccp(obPoint.x, newY);
		break;
	case CCDeviceOrientationPortraitUpsideDown:
		ret = ccp(newX, obPoint.y);
		break;
	case CCDeviceOrientationLandscapeLeft:
		ret.x = obPoint.y;
		ret.y = obPoint.x;
		break;
	case CCDeviceOrientationLandscapeRight:
		ret.x = newY;
		ret.y = newX;
		break;
	}

	ret = ccpMult(ret, m_fContentScaleFactor);
	return ret;
}

CGPoint CCDirector::convertToUI(CGPoint obPoint)
{
	CGSize winSize = m_obSurfaceSize;
	float oppositeX = winSize.width - obPoint.x;
	float oppositeY = winSize.height - obPoint.y;
	CGPoint uiPoint;

	switch (m_eDeviceOrientation)
	{
	case CCDeviceOrientationPortrait:
		uiPoint = ccp(obPoint.x, obPoint.y);
		break;
	case CCDeviceOrientationPortraitUpsideDown:
		uiPoint = ccp(oppositeX, oppositeY);
		break;
	case CCDeviceOrientationLandscapeLeft:
		uiPoint = ccp(obPoint.y, oppositeX);
		break;
	case CCDeviceOrientationLandscapeRight:
		uiPoint = ccp(oppositeY, obPoint.x);
		break;
	}

	uiPoint = ccpMult(uiPoint, 1/m_fContentScaleFactor);
	return uiPoint;
}

CGSize CCDirector::getWinSize(void)
{
	CGSize s = m_obSurfaceSize;

	if (m_eDeviceOrientation == CCDeviceOrientationLandscapeLeft
		|| m_eDeviceOrientation == CCDeviceOrientationLandscapeRight)
	{
		// swap x,y in landspace mode
		CGSize tmp = s;
		s.width = tmp.height;
		s.height = tmp.width;
	}

	return s;
}

// return the current frame size
CGSize CCDirector::getDisplaySize(void)
{
	return m_obSurfaceSize;
}

void CCDirector::applyLandspace(void)
{
	CGSize s = m_obSurfaceSize;
	float w = s.width / 2;
	float h = s.height / 2;

	// XXX it's using hardcoded values.
	// What if the the screen size changes in the future?
	switch (m_eDeviceOrientation)
	{
	case CCDeviceOrientationPortrait:
		// nothing
		break;
	case CCDeviceOrientationPortraitUpsideDown:
		// upside down
		glTranslatef(w,h,0);
		glRotatef(180,0,0,1);
		glTranslatef(-w,-h,0);
		break;
	case CCDeviceOrientationLandscapeRight:
		glTranslatef(w,h,0);
		glRotatef(90,0,0,1);
		glTranslatef(-h,-w,0);
		break;
	case CCDeviceOrientationLandscapeLeft:
		glTranslatef(w,h,0);
		glRotatef(-90,0,0,1);
		glTranslatef(-h,-w,0);
		break;
	}
}

// scene management

void CCDirector::runWithScene(CCScene *pScene)
{
	assert(pScene != NULL);
	assert(m_pRunningScene == NULL);

	pushScene(pScene);
	startAnimation();

	// render the 1st frame to avoid flicker (issue #350)
	//mainLoop();
}

void CCDirector::replaceScene(CCScene *pScene)
{
	assert(pScene != NULL);

	unsigned int index = m_pobScenesStack->count();

	m_bSendCleanupToScene = true;
	m_pobScenesStack->replaceObjectAtIndex(index - 1, pScene);

	m_pNextScene = pScene;
}

void CCDirector::pushScene(CCScene *pScene)
{
	assert(pScene);

	m_bSendCleanupToScene = false;

	m_pobScenesStack->addObject(pScene);
	m_pNextScene = pScene;
}

void CCDirector::popScene(void)
{
	assert(m_pRunningScene != NULL);

	m_pobScenesStack->removeLastObject();
	unsigned int c = m_pobScenesStack->count();

	if (c == 0)
	{
		end();
	}
	else
	{
		m_pNextScene = m_pobScenesStack->getObjectAtIndex(c - 1);
	}
}

void CCDirector::end(void)
{
	m_pRunningScene->onExit();
	m_pRunningScene->cleanup();
	m_pRunningScene->release();

	m_pRunningScene = NULL;
	m_pNextScene = NULL;

	// remove all objects, but don't release it.
	// runWithScene might be executed after 'end'.
	m_pobScenesStack->removeAllObjects();

	// don't release the event handlers
	// They are needed in case the director is run again
	CCTouchDispatcher::getSharedDispatcher()->removeAllDelegates();

	stopAnimation();

#if CC_DIRECTOR_FAST_FPS
	CCX_SAFE_RELEASE_NULL(m_pFPSLabel);
#endif

	// purge bitmap cache
	CCBitmapFontAtlas::purgeCachedData();

	// purge all managers
 	CCSpriteFrameCache::purgeSharedSpriteFrameCache();
	CCActionManager::getSharedManager()->purgeSharedManager();
	CCScheduler::purgeSharedScheduler();
	CCTextureCache::purgeSharedTextureCache();

	// OpenGL view
	m_pobOpenGLView->release();
	m_pobOpenGLView = NULL;
}

void CCDirector::setNextScene(void)
{
// 	bool runningIsTransition = dynamic_cast<CCTransitionScene *>(m_pRunningScene) != NULL;
// 	bool newIsTransition = dynamic_cast<CCTransitionScene *>(m_pNextScene) != NULL;
	ccSceneFlag runningSceneType = ccNormalScene;
	ccSceneFlag newSceneType = m_pNextScene->getSceneType();

	if (m_pRunningScene)
	{
		runningSceneType = m_pRunningScene->getSceneType();
	}

	// If it is not a transition, call onExit/cleanup
 	/*if (! newIsTransition)*/
	if (! (newSceneType & ccTransitionScene))
 	{
         if (m_pRunningScene)
         {
             m_pRunningScene->onExit();
         }
 
 		// issue #709. the root node (scene) should receive the cleanup message too
 		// otherwise it might be leaked.
 		if (m_bSendCleanupToScene && m_pRunningScene)
 		{
 			m_pRunningScene->cleanup();
 		}
 	}

    if (m_pRunningScene)
    {
        m_pRunningScene->release();
    }
    m_pRunningScene = m_pNextScene;
	m_pNextScene->retain();
	m_pNextScene = NULL;

	/*if (! runningIsTransition && m_pRunningScene)*/
	if (! (runningSceneType & ccTransitionScene) && m_pRunningScene)
	{
		m_pRunningScene->onEnter();
		m_pRunningScene->onEnterTransitionDidFinish();
	}
}

void CCDirector::pause(void)
{
	if (m_bPaused)
	{
		return;
	}

	m_dOldAnimationInterval = m_dAnimationInterval;

	// when paused, don't consume CPU
	setAnimationInterval(1 / 4.0);
	m_bPaused = true;
}

void CCDirector::resume(void)
{
	if (! m_bPaused)
	{
		return;
	}

	setAnimationInterval(m_dOldAnimationInterval);

	if (CCTime::gettimeofdayCocos2d(m_pLastUpdate, NULL) != 0)
	{
		CCLOG("cocos2d: Director: Error in gettimeofday");
	}

	m_bPaused = false;
	m_fDeltaTime = 0;
}

void CCDirector::startAnimation(void)
{
	CCLOG("cocos2d: Director#startAnimation. Overrride me");
	assert(0);
}

void CCDirector::stopAnimation(void)
{
	CCLOG("cocos2d: Director#stopAnimation. Overrride me");
	assert(0);
}

void CCDirector::preMainLoop(void)
{
    CCLOG("cocos2d: Director#preMainLoop. Overrride me");
	assert(0);
}

#if CC_DIRECTOR_FAST_FPS
// display the FPS using a LabelAtlas
// updates the FPS every frame
void CCDirector::showFPS(void)
{
	++m_nFrames;
	m_fAccumDt += m_fDeltaTime;

	if (m_fAccumDt > CC_DIRECTOR_FPS_INTERVAL)
	{
		m_fFrameRate = m_nFrames / m_fAccumDt;
		m_nFrames = 0;
		m_fAccumDt = 0;
        
		char *str = new char[10];
		sprintf(str, "%.1f", m_fFrameRate);
		m_pFPSLabel->setString(str);
		delete [] str;
	}

    m_pFPSLabel->draw();
}
#endif // CC_DIRECTOR_FAST_FPS

#if CC_ENABLE_PROFILERS
void CCDirector::showProfilers()
{
	m_fAccumDtForProfiler += m_fDeltaTime;
	if (m_fAccumDtForProfiler > 1.0f)
	{
		m_fAccumDtForProfiler = 0;
		CCProfiler::getSharedProfiler()->displayTimers();
	}
}
#endif

// should we afford 4 types of director ??
// I think DisplayLinkDirector is enough
// so we now only support DisplayLinkDirector

// implementation of DisplayLinkDirector
void CCDisplayLinkDirector::startAnimation(void)
{
	if (CCTime::gettimeofdayCocos2d(m_pLastUpdate, NULL) != 0)
	{
		CCLOG("cocos2d: DisplayLinkDirector: Error on gettimeofday");
	}

	m_bInvalid = false;

	// approximate frame rate
	// assumes device refreshes at 60 fps
	//int frameInterval	= (int) floor(animationInterval * 60.0f);
	
	//CCLOG(@"cocos2d: Frame interval: %d", frameInterval);

	//displayLink = [NSClassFromString(@"CADisplayLink") displayLinkWithTarget:self selector:@selector(preMainLoop:)];
	//[displayLink setFrameInterval:frameInterval];
	//[displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}

void CCDisplayLinkDirector::preMainLoop(void)
{
	if (! m_bInvalid)
	{
		mainLoop();
	}
}

void CCDisplayLinkDirector::stopAnimation(void)
{
	m_bInvalid = true;
}

void CCDisplayLinkDirector::setAnimationInterval(double dValue)
{
	m_dAnimationInterval = dValue;
	if (! m_bInvalid)
	{
		stopAnimation();
		startAnimation();
	}	
}

} //namespace   cocos2d 
