/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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

#include "cocoa/CCNS.h"
#include "CCDirector.h"
#include "CCScene.h"
#include "CCMutableArray.h"
#include "CCScheduler.h"
#include "ccMacros.h"
#include "CCTouchDispatcher.h"
#include "CCPointExtension.h"
#include "CCTransition.h"
#include "CCTextureCache.h"
#include "CCTransition.h"
#include "CCSpriteFrameCache.h"
#include "CCAutoreleasePool.h"
#include "platform/platform.h"
#include "CCApplication.h"
#include "CCLabelBMFont.h"
#include "CCActionManager.h"
#include "CCLabelTTF.h"
#include "CCConfiguration.h"
#include "CCKeypadDispatcher.h"
#include "CCGL.h"
#include "CCAnimationCache.h"
#include "CCTouch.h"

//#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)
#include "CCUserDefault.h"
//#endif

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
extern const char* cocos2dVersion(void);

CCDirector* CCDirector::sharedDirector(void)
{
	if (s_bFirstRun)
	{
		s_sharedDirector.init();
        s_bFirstRun = false;
	}

	return &s_sharedDirector;
}

bool CCDirector::init(void)
{
	CCLOG("cocos2d: %s", cocos2dVersion());

	// scenes
	m_pRunningScene = NULL;
	m_pNextScene = NULL;

	m_pNotificationNode = NULL;

	m_dOldAnimationInterval = m_dAnimationInterval = 1.0 / kDefaultFPS;	
	m_pobScenesStack = new CCMutableArray<CCScene*>();

	// Set default projection (3D)
	m_eProjection = kCCDirectorProjectionDefault;

	// projection delegate if "Custom" projection is used
	m_pProjectionDelegate = NULL;

	// FPS
	m_bDisplayFPS = false;
	m_uTotalFrames = m_uFrames = 0;
	m_pszFPS = new char[10];
	m_pLastUpdate = new struct cc_timeval();

	// paused ?
	m_bPaused = false;
	
	// purge ?
	m_bPurgeDirecotorInNextLoop = false;

	m_obWinSizeInPixels = m_obWinSizeInPoints = CCSizeZero;

	// portrait mode default
	m_eDeviceOrientation = CCDeviceOrientationPortrait;		

	m_pobOpenGLView = NULL;

    m_bRetinaDisplay = false;
    m_fContentScaleFactor = 1;	
	m_bIsContentScaleSupported = false;

	// create autorelease pool
	CCPoolManager::getInstance()->push();

	return true;
}
	
CCDirector::~CCDirector(void)
{
	CCLOGINFO("cocos2d: deallocing %p", this);

#if CC_DIRECTOR_FAST_FPS
	CC_SAFE_RELEASE(m_pFPSLabel);
#endif 
    
	CC_SAFE_RELEASE(m_pRunningScene);
	CC_SAFE_RELEASE(m_pNotificationNode);
	CC_SAFE_RELEASE(m_pobScenesStack);

	// pop the autorelease pool
	CCPoolManager::getInstance()->pop();

	// delete m_pLastUpdate
	CC_SAFE_DELETE(m_pLastUpdate);

    CCKeypadDispatcher::purgeSharedDispatcher();

	// delete fps string
	delete []m_pszFPS;
}

void CCDirector::setGLDefaultValues(void)
{
	// This method SHOULD be called only after openGLView_ was initialized
	CCAssert(m_pobOpenGLView, "opengl view should not be null");

	setAlphaBlending(true);
	setDepthTest(true);
	setProjection(m_eProjection);

	// set other opengl default values
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

#if CC_DIRECTOR_FAST_FPS
	if (! m_pFPSLabel)
	{
        m_pFPSLabel = CCLabelTTF::labelWithString("00.0", "Arial", 24);
		m_pFPSLabel->retain();
	}
#endif
}

// Draw the SCene
void CCDirector::drawScene(void)
{
	// calculate "global" dt
	calculateDeltaTime();

	//tick before glClear: issue #533
	if (! m_bPaused)
	{
		CCScheduler::sharedScheduler()->tick(m_fDeltaTime);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* to avoid flickr, nextScene MUST be here: after tick and before draw.
	 XXX: Which bug is this one. It seems that it can't be reproduced with v0.9 */
	if (m_pNextScene)
	{
		setNextScene();
	}

	glPushMatrix();

	applyOrientation();

	// By default enable VertexArray, ColorArray, TextureCoordArray and Texture2D
	CC_ENABLE_DEFAULT_GL_STATES();

	// draw the scene
    if (m_pRunningScene)
    {
        m_pRunningScene->visit();
    }

	// draw the notifications node
	if (m_pNotificationNode)
	{
		m_pNotificationNode->visit();
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

	m_uTotalFrames++;

	// swap buffers
	if (m_pobOpenGLView)
    {
        m_pobOpenGLView->swapBuffers();
    }
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

#ifdef DEBUG
	// If we are debugging our code, prevent big delta time
	if(m_fDeltaTime > 0.2f)
	{
		m_fDeltaTime = 1 / 60.0f;
	}
#endif

	*m_pLastUpdate = now;
}


// m_pobOpenGLView

void CCDirector::setOpenGLView(CC_GLVIEW *pobOpenGLView)
{
	CCAssert(pobOpenGLView, "opengl view should not be null");

	if (m_pobOpenGLView != pobOpenGLView)
	{
		// because EAGLView is not kind of CCObject
		delete m_pobOpenGLView; // [openGLView_ release]
		m_pobOpenGLView = pobOpenGLView;

		// set size
		m_obWinSizeInPoints = m_pobOpenGLView->getSize();
		m_obWinSizeInPixels = CCSizeMake(m_obWinSizeInPoints.width * m_fContentScaleFactor, m_obWinSizeInPoints.height * m_fContentScaleFactor);
        setGLDefaultValues();

		if (m_fContentScaleFactor != 1)
		{
			updateContentScaleFactor();
		}

 		CCTouchDispatcher *pTouchDispatcher = CCTouchDispatcher::sharedDispatcher();
 		m_pobOpenGLView->setTouchDelegate(pTouchDispatcher);
        pTouchDispatcher->setDispatchEvents(true);
	}
}

void CCDirector::setNextDeltaTimeZero(bool bNextDeltaTimeZero)
{
	m_bNextDeltaTimeZero = bNextDeltaTimeZero;
}

void CCDirector::setProjection(ccDirectorProjection kProjection)
{
	CCSize size = m_obWinSizeInPixels;
	float zeye = this->getZEye();
	switch (kProjection)
	{
	case kCCDirectorProjection2D:
        if (m_pobOpenGLView) 
        {
            m_pobOpenGLView->setViewPortInPoints(0, 0, size.width, size.height);
        }
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		ccglOrtho(0, size.width, 0, size.height, -1024 * CC_CONTENT_SCALE_FACTOR(), 
			1024 * CC_CONTENT_SCALE_FACTOR());
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		break;

	case kCCDirectorProjection3D:		
        if (m_pobOpenGLView) 
        {
            m_pobOpenGLView->setViewPortInPoints(0, 0, size.width, size.height);
        }
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60, (GLfloat)size.width/size.height, 0.5f, 1500.0f);
			
		glMatrixMode(GL_MODELVIEW);	
		glLoadIdentity();
		gluLookAt( size.width/2, size.height/2, zeye,
				 size.width/2, size.height/2, 0,
				 0.0f, 1.0f, 0.0f);				
		break;
			
	case kCCDirectorProjectionCustom:
		if (m_pProjectionDelegate)
		{
			m_pProjectionDelegate->updateProjection();
		}
		break;
			
	default:
		CCLOG("cocos2d: Director: unrecognized projecgtion");
		break;
	}

	m_eProjection = kProjection;
}

void CCDirector::purgeCachedData(void)
{
    CCLabelBMFont::purgeCachedData();
	CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

float CCDirector::getZEye(void)
{
    return (m_obWinSizeInPixels.height / 1.1566f);	
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
		ccglClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
//		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}
}

CCPoint CCDirector::convertToGL(const CCPoint& obPoint)
{
	CCSize s = m_obWinSizeInPoints;
	float newY = s.height - obPoint.y;
	float newX = s.width - obPoint.x;

	CCPoint ret = CCPointZero;
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
	
	return ret;
}

CCPoint CCDirector::convertToUI(const CCPoint& obPoint)
{
	CCSize winSize = m_obWinSizeInPoints;
	float oppositeX = winSize.width - obPoint.x;
	float oppositeY = winSize.height - obPoint.y;
	CCPoint uiPoint = CCPointZero;

	switch (m_eDeviceOrientation)
	{
	case CCDeviceOrientationPortrait:
		uiPoint = ccp(obPoint.x, oppositeY);
		break;
	case CCDeviceOrientationPortraitUpsideDown:
		uiPoint = ccp(oppositeX, obPoint.y);
		break;
	case CCDeviceOrientationLandscapeLeft:
		uiPoint = ccp(obPoint.y, obPoint.x);
		break;
	case CCDeviceOrientationLandscapeRight:
		// Can't use oppositeX/Y because x/y are flipped
		uiPoint = ccp(winSize.width - obPoint.y, winSize.height - obPoint.x);
		break;
	}

	return uiPoint;
}

CCSize CCDirector::getWinSize(void)
{
	CCSize s = m_obWinSizeInPoints;

	if (m_eDeviceOrientation == CCDeviceOrientationLandscapeLeft
		|| m_eDeviceOrientation == CCDeviceOrientationLandscapeRight)
	{
		// swap x,y in landspace mode
		CCSize tmp = s;
		s.width = tmp.height;
		s.height = tmp.width;
	}

	return s;
}

CCSize CCDirector::getWinSizeInPixels()
{
	CCSize s = getWinSize();

	s.width *= CC_CONTENT_SCALE_FACTOR();
	s.height *= CC_CONTENT_SCALE_FACTOR();

	return s;
}

// return the current frame size
CCSize CCDirector::getDisplaySizeInPixels(void)
{
	return m_obWinSizeInPixels;
}

void CCDirector::reshapeProjection(const CCSize& newWindowSize)
{
    CC_UNUSED_PARAM(newWindowSize);
    m_obWinSizeInPoints = m_pobOpenGLView->getSize();
	m_obWinSizeInPixels = CCSizeMake(m_obWinSizeInPoints.width * m_fContentScaleFactor,
		                             m_obWinSizeInPoints.height * m_fContentScaleFactor);

	setProjection(m_eProjection);
}

// scene management

void CCDirector::runWithScene(CCScene *pScene)
{
	CCAssert(pScene != NULL, "running scene should not be null");
	CCAssert(m_pRunningScene == NULL, "m_pRunningScene should be null");

	pushScene(pScene);
	startAnimation();
}

void CCDirector::replaceScene(CCScene *pScene)
{
	CCAssert(pScene != NULL, "the scene should not be null");

	unsigned int index = m_pobScenesStack->count();

	m_bSendCleanupToScene = true;
	m_pobScenesStack->replaceObjectAtIndex(index - 1, pScene);

	m_pNextScene = pScene;
}

void CCDirector::pushScene(CCScene *pScene)
{
	CCAssert(pScene, "the scene should not null");

	m_bSendCleanupToScene = false;

	m_pobScenesStack->addObject(pScene);
	m_pNextScene = pScene;
}

void CCDirector::popScene(void)
{
	CCAssert(m_pRunningScene != NULL, "running scene should not null");

	m_pobScenesStack->removeLastObject();
	unsigned int c = m_pobScenesStack->count();

	if (c == 0)
	{
		end();
	}
	else
	{
		m_bSendCleanupToScene = true;
		m_pNextScene = m_pobScenesStack->getObjectAtIndex(c - 1);
	}
}

void CCDirector::end()
{
	m_bPurgeDirecotorInNextLoop = true;
}


void CCDirector::resetDirector()
{
	// don't release the event handlers
	// They are needed in case the director is run again
	CCTouchDispatcher::sharedDispatcher()->removeAllDelegates();

    if (m_pRunningScene)
    {
    	m_pRunningScene->onExit();
    	m_pRunningScene->cleanup();
    	m_pRunningScene->release();
    }
    
	m_pRunningScene = NULL;
	m_pNextScene = NULL;

	// remove all objects, but don't release it.
	// runWithScene might be executed after 'end'.
	m_pobScenesStack->removeAllObjects();

	stopAnimation();

	CC_SAFE_RELEASE_NULL(m_pProjectionDelegate);

	// purge bitmap cache
	CCLabelBMFont::purgeCachedData();

	// purge all managers
	CCAnimationCache::purgeSharedAnimationCache();
 	CCSpriteFrameCache::purgeSharedSpriteFrameCache();
	CCActionManager::sharedManager()->purgeSharedManager();
	CCScheduler::purgeSharedScheduler();
	CCTextureCache::purgeSharedTextureCache();
}


void CCDirector::purgeDirector()
{
	// don't release the event handlers
	// They are needed in case the director is run again
	CCTouchDispatcher::sharedDispatcher()->removeAllDelegates();

    if (m_pRunningScene)
    {
    	m_pRunningScene->onExit();
    	m_pRunningScene->cleanup();
    	m_pRunningScene->release();
    }
    
	m_pRunningScene = NULL;
	m_pNextScene = NULL;

	// remove all objects, but don't release it.
	// runWithScene might be executed after 'end'.
	m_pobScenesStack->removeAllObjects();

	stopAnimation();

#if CC_DIRECTOR_FAST_FPS
	CC_SAFE_RELEASE_NULL(m_pFPSLabel);
#endif

		CC_SAFE_RELEASE_NULL(m_pProjectionDelegate);

	// purge bitmap cache
	CCLabelBMFont::purgeCachedData();

	// purge all managers
	CCAnimationCache::purgeSharedAnimationCache();
 	CCSpriteFrameCache::purgeSharedSpriteFrameCache();
	CCActionManager::sharedManager()->purgeSharedManager();
	CCScheduler::purgeSharedScheduler();
	CCTextureCache::purgeSharedTextureCache();
	
//#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)	
	CCUserDefault::purgeSharedUserDefault();
//#endif
	// OpenGL view
	m_pobOpenGLView->release();
	m_pobOpenGLView = NULL;
}

void CCDirector::setNextScene(void)
{
	bool runningIsTransition = dynamic_cast<CCTransitionScene*>(m_pRunningScene) != NULL;
	bool newIsTransition = dynamic_cast<CCTransitionScene*>(m_pNextScene) != NULL;

	// If it is not a transition, call onExit/cleanup
 	if (! newIsTransition)
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

	if ((! runningIsTransition) && m_pRunningScene)
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

#if CC_DIRECTOR_FAST_FPS
// display the FPS using a LabelAtlas
// updates the FPS every frame
void CCDirector::showFPS(void)
{
	m_uFrames++;
	m_fAccumDt += m_fDeltaTime;

	if (m_fAccumDt > CC_DIRECTOR_FPS_INTERVAL)
	{
		m_fFrameRate = m_uFrames / m_fAccumDt;
		m_uFrames = 0;
		m_fAccumDt = 0;

		sprintf(m_pszFPS, "%.1f", m_fFrameRate);
		m_pFPSLabel->setString(m_pszFPS);
	}

    m_pFPSLabel->draw();
}
#endif // CC_DIRECTOR_FAST_FPS


void CCDirector::showProfilers()
{
#if CC_ENABLE_PROFILERS
	m_fAccumDtForProfiler += m_fDeltaTime;
	if (m_fAccumDtForProfiler > 1.0f)
	{
		m_fAccumDtForProfiler = 0;
		CCProfiler::sharedProfiler()->displayTimers();
	}
#endif
}

/***************************************************
* mobile platforms specific functions
**************************************************/

void CCDirector::updateContentScaleFactor()
{
	// [openGLView responseToSelector:@selector(setContentScaleFactor)]
	if (m_pobOpenGLView->canSetContentScaleFactor())
	{
		m_pobOpenGLView->setContentScaleFactor(m_fContentScaleFactor);
		m_bIsContentScaleSupported = true;
	}
	else
	{
		CCLOG("cocos2d: setContentScaleFactor:'is not supported on this device");
	}
}


bool CCDirector::setDirectorType(ccDirectorType obDirectorType)
{
    CC_UNUSED_PARAM(obDirectorType);
	// we only support CCDisplayLinkDirector
	CCDirector::sharedDirector();

	return true;
}

bool CCDirector::enableRetinaDisplay(bool enabled)
{
	// Already enabled?
	if (enabled && m_fContentScaleFactor == 2)
	{
		return true;
	}

	// Already diabled?
	if (!enabled && m_fContentScaleFactor == 1)
	{
		return false;
	}

	// setContentScaleFactor is not supported
	if (! m_pobOpenGLView->canSetContentScaleFactor())
	{
		return false;
	}

	float newScale = (float)(enabled ? 2 : 1);
	setContentScaleFactor(newScale);

    // release cached texture
    CCTextureCache::purgeSharedTextureCache();

#if CC_DIRECTOR_FAST_FPS
    if (m_pFPSLabel)
    {
        CC_SAFE_RELEASE_NULL(m_pFPSLabel);
        m_pFPSLabel = CCLabelTTF::labelWithString("00.0", "Arial", 24);
        m_pFPSLabel->retain();
    }
#endif

    if (m_fContentScaleFactor == 2)
    {
        m_bRetinaDisplay = true;
    }
    else
    {
        m_bRetinaDisplay = false;
    }

	return true;
}

CGFloat CCDirector::getContentScaleFactor(void)
{
	return m_fContentScaleFactor;
}

void CCDirector::setContentScaleFactor(CGFloat scaleFactor)
{
	if (scaleFactor != m_fContentScaleFactor)
	{
		m_fContentScaleFactor = scaleFactor;
		m_obWinSizeInPixels = CCSizeMake(m_obWinSizeInPoints.width * scaleFactor, m_obWinSizeInPoints.height * scaleFactor);

		if (m_pobOpenGLView)
		{
			updateContentScaleFactor();
		}

		// update projection
		setProjection(m_eProjection);
	}
}

CCNode* CCDirector::getNotificationNode() 
{ 
	return m_pNotificationNode; 
}

void CCDirector::setNotificationNode(CCNode *node)
{
	CC_SAFE_RELEASE(m_pNotificationNode);
	m_pNotificationNode = node;
	CC_SAFE_RETAIN(m_pNotificationNode);
}

void CCDirector::applyOrientation(void)
{
	CCSize s = m_obWinSizeInPixels;
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

ccDeviceOrientation CCDirector::getDeviceOrientation(void)
{
	return m_eDeviceOrientation;
}

void CCDirector::setDeviceOrientation(ccDeviceOrientation kDeviceOrientation)
{
	ccDeviceOrientation eNewOrientation;

	eNewOrientation = (ccDeviceOrientation)CCApplication::sharedApplication().setOrientation(
        (CCApplication::Orientation)kDeviceOrientation);

	if (m_eDeviceOrientation != eNewOrientation)
	{
		m_eDeviceOrientation = eNewOrientation;
	}
    else
    {
        // this logic is only run on win32 now
        // On win32,the return value of CCApplication::setDeviceOrientation is always kCCDeviceOrientationPortrait
        // So,we should calculate the Projection and window size again.
        m_obWinSizeInPoints = m_pobOpenGLView->getSize();
        m_obWinSizeInPixels = CCSizeMake(m_obWinSizeInPoints.width * m_fContentScaleFactor, m_obWinSizeInPoints.height * m_fContentScaleFactor);
        setProjection(m_eProjection);
    }
}


/***************************************************
* implementation of DisplayLinkDirector
**************************************************/

// should we afford 4 types of director ??
// I think DisplayLinkDirector is enough
// so we now only support DisplayLinkDirector
void CCDisplayLinkDirector::startAnimation(void)
{
	if (CCTime::gettimeofdayCocos2d(m_pLastUpdate, NULL) != 0)
	{
		CCLOG("cocos2d: DisplayLinkDirector: Error on gettimeofday");
	}

	m_bInvalid = false;
	CCApplication::sharedApplication().setAnimationInterval(m_dAnimationInterval);
}

void CCDisplayLinkDirector::mainLoop(void)
{
	if (m_bPurgeDirecotorInNextLoop)
	{
		purgeDirector();
        m_bPurgeDirecotorInNextLoop = false;
	}
	else if (! m_bInvalid)
 	{
 		drawScene();
	 
 		// release the objects
 		CCPoolManager::getInstance()->pop();		
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
