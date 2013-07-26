/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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

// cocos2d includes
#include "CCDirector.h"

// standard includes
#include <string>

#include "ccFPSImages.h"
#include "draw_nodes/CCDrawingPrimitives.h"
#include "CCConfiguration.h"
#include "cocoa/CCNS.h"
#include "layers_scenes_transitions_nodes/CCScene.h"
#include "cocoa/CCArray.h"
#include "CCScheduler.h"
#include "ccMacros.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "support/CCNotificationCenter.h"
#include "layers_scenes_transitions_nodes/CCTransition.h"
#include "textures/CCTextureCache.h"
#include "sprite_nodes/CCSpriteFrameCache.h"
#include "cocoa/CCAutoreleasePool.h"
#include "platform/CCFileUtils.h"
#include "CCApplication.h"
#include "label_nodes/CCLabelBMFont.h"
#include "label_nodes/CCLabelAtlas.h"
#include "actions/CCActionManager.h"
#include "CCConfiguration.h"
#include "keypad_dispatcher/CCKeypadDispatcher.h"
#include "CCAccelerometer.h"
#include "sprite_nodes/CCAnimationCache.h"
#include "touch_dispatcher/CCTouch.h"
#include "support/user_default/CCUserDefault.h"
#include "shaders/ccGLStateCache.h"
#include "shaders/CCShaderCache.h"
#include "kazmath/kazmath.h"
#include "kazmath/GL/matrix.h"
#include "support/CCProfiling.h"
#include "platform/CCImage.h"
#include "CCEGLView.h"
#include "CCConfiguration.h"
#include "keyboard_dispatcher/CCKeyboardDispatcher.h"


/**
 Position of the FPS
 
 Default: 0,0 (bottom-left corner)
 */
#ifndef CC_DIRECTOR_STATS_POSITION
#define CC_DIRECTOR_STATS_POSITION Director::getInstance()->getVisibleOrigin()
#endif

using namespace std;

unsigned int g_uNumberOfDraws = 0;

NS_CC_BEGIN
// XXX it should be a Director ivar. Move it there once support for multiple directors is added

// singleton stuff
static DisplayLinkDirector *s_SharedDirector = NULL;

#define kDefaultFPS        60  // 60 frames per second
extern const char* cocos2dVersion(void);

Director* Director::getInstance()
{
    if (!s_SharedDirector)
    {
        s_SharedDirector = new DisplayLinkDirector();
        s_SharedDirector->init();
    }

    return s_SharedDirector;
}

Director::Director(void)
{

}

bool Director::init(void)
{
	setDefaultValues();

    // scenes
    _runningScene = NULL;
    _nextScene = NULL;

    _notificationNode = NULL;

    _scenesStack = new Array();
    _scenesStack->init();

    // projection delegate if "Custom" projection is used
    _projectionDelegate = NULL;

    // FPS
    _accumDt = 0.0f;
    _frameRate = 0.0f;
    _FPSLabel = NULL;
    _SPFLabel = NULL;
    _drawsLabel = NULL;
    _totalFrames = _frames = 0;
    _FPS = new char[10];
    _lastUpdate = new struct timeval;

    // paused ?
    _paused = false;
   
    // purge ?
    _purgeDirecotorInNextLoop = false;

    _winSizeInPoints = Size::ZERO;    

    _openGLView = NULL;

    _contentScaleFactor = 1.0f;

    // scheduler
    _scheduler = new Scheduler();
    // action manager
    _actionManager = new ActionManager();
    _scheduler->scheduleUpdateForTarget(_actionManager, Scheduler::PRIORITY_SYSTEM, false);
    // touchDispatcher
    _touchDispatcher = new TouchDispatcher();
    _touchDispatcher->init();

    // KeyboardDispatcher
    _keyboardDispatcher = new KeyboardDispatcher();

    // KeypadDispatcher
    _keypadDispatcher = new KeypadDispatcher();

    // Accelerometer
    _accelerometer = new Accelerometer();

    // create autorelease pool
    PoolManager::sharedPoolManager()->push();

    return true;
}
    
Director::~Director(void)
{
    CCLOG("cocos2d: deallocing Director %p", this);

    CC_SAFE_RELEASE(_FPSLabel);
    CC_SAFE_RELEASE(_SPFLabel);
    CC_SAFE_RELEASE(_drawsLabel);
    
    CC_SAFE_RELEASE(_runningScene);
    CC_SAFE_RELEASE(_notificationNode);
    CC_SAFE_RELEASE(_scenesStack);
    CC_SAFE_RELEASE(_scheduler);
    CC_SAFE_RELEASE(_actionManager);
    CC_SAFE_RELEASE(_touchDispatcher);
    CC_SAFE_RELEASE(_keyboardDispatcher);
    CC_SAFE_RELEASE(_keypadDispatcher);
    CC_SAFE_DELETE(_accelerometer);

    // pop the autorelease pool
    PoolManager::sharedPoolManager()->pop();
    PoolManager::purgePoolManager();

    // delete _lastUpdate
    CC_SAFE_DELETE(_lastUpdate);
    // delete fps string
    delete []_FPS;

    s_SharedDirector = NULL;
}

void Director::setDefaultValues(void)
{
	Configuration *conf = Configuration::getInstance();

	// default FPS
	double fps = conf->getNumber("cocos2d.x.fps", kDefaultFPS);
	_oldAnimationInterval = _animationInterval = 1.0 / fps;

	// Display FPS
	_displayStats = conf->getBool("cocos2d.x.display_fps", false);

	// GL projection
	const char *projection = conf->getCString("cocos2d.x.gl.projection", "3d");
	if( strcmp(projection, "3d") == 0 )
		_projection = Projection::_3D;
	else if (strcmp(projection, "2d") == 0)
		_projection = Projection::_2D;
	else if (strcmp(projection, "custom") == 0)
		_projection = Projection::CUSTOM;
	else
		CCASSERT(false, "Invalid projection value");

	// Default pixel format for PNG images with alpha
	const char *pixel_format = conf->getCString("cocos2d.x.texture.pixel_format_for_png", "rgba8888");
	if( strcmp(pixel_format, "rgba8888") == 0 )
		Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
	else if( strcmp(pixel_format, "rgba4444") == 0 )
		Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);
	else if( strcmp(pixel_format, "rgba5551") == 0 )
		Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGB5A1);

	// PVR v2 has alpha premultiplied ?
	bool pvr_alpha_premultipled = conf->getBool("cocos2d.x.texture.pvrv2_has_alpha_premultiplied", false);
	Texture2D::PVRImagesHavePremultipliedAlpha(pvr_alpha_premultipled);
}

void Director::setGLDefaultValues(void)
{
    // This method SHOULD be called only after openGLView_ was initialized
    CCASSERT(_openGLView, "opengl view should not be null");

    setAlphaBlending(true);
    // XXX: Fix me, should enable/disable depth test according the depth format as cocos2d-iphone did
    // [self setDepthTest: view_.depthFormat];
    setDepthTest(false);
    setProjection(_projection);

    // set other opengl default values
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Draw the Scene
void Director::drawScene(void)
{
    // calculate "global" dt
    calculateDeltaTime();

    //tick before glClear: issue #533
    if (! _paused)
    {
        _scheduler->update(_deltaTime);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* to avoid flickr, nextScene MUST be here: after tick and before draw.
     XXX: Which bug is this one. It seems that it can't be reproduced with v0.9 */
    if (_nextScene)
    {
        setNextScene();
    }

    kmGLPushMatrix();

    // draw the scene
    if (_runningScene)
    {
        _runningScene->visit();
    }

    // draw the notifications node
    if (_notificationNode)
    {
        _notificationNode->visit();
    }
    
    if (_displayStats)
    {
        showStats();
    }

    kmGLPopMatrix();

    _totalFrames++;

    // swap buffers
    if (_openGLView)
    {
        _openGLView->swapBuffers();
    }
    
    if (_displayStats)
    {
        calculateMPF();
    }
}

void Director::calculateDeltaTime(void)
{
    struct timeval now;

    if (gettimeofday(&now, NULL) != 0)
    {
        CCLOG("error in gettimeofday");
        _deltaTime = 0;
        return;
    }

    // new delta time. Re-fixed issue #1277
    if (_nextDeltaTimeZero)
    {
        _deltaTime = 0;
        _nextDeltaTimeZero = false;
    }
    else
    {
        _deltaTime = (now.tv_sec - _lastUpdate->tv_sec) + (now.tv_usec - _lastUpdate->tv_usec) / 1000000.0f;
        _deltaTime = MAX(0, _deltaTime);
    }

#ifdef DEBUG
    // If we are debugging our code, prevent big delta time
    if(_deltaTime > 0.2f)
    {
        _deltaTime = 1 / 60.0f;
    }
#endif

    *_lastUpdate = now;
}
float Director::getDeltaTime() const
{
	return _deltaTime;
}
void Director::setOpenGLView(EGLView *pobOpenGLView)
{
    CCASSERT(pobOpenGLView, "opengl view should not be null");

    if (_openGLView != pobOpenGLView)
    {
		// Configuration. Gather GPU info
		Configuration *conf = Configuration::getInstance();
		conf->gatherGPUInfo();
		conf->dumpInfo();

        // EAGLView is not a Object
        delete _openGLView; // [openGLView_ release]
        _openGLView = pobOpenGLView;

        // set size
        _winSizeInPoints = _openGLView->getDesignResolutionSize();
        
        createStatsLabel();
        
        if (_openGLView)
        {
            setGLDefaultValues();
        }  
        
        CHECK_GL_ERROR_DEBUG();

        _openGLView->setTouchDelegate(_touchDispatcher);
        _touchDispatcher->setDispatchEvents(true);
    }
}

void Director::setViewport()
{
    if (_openGLView)
    {
        _openGLView->setViewPortInPoints(0, 0, _winSizeInPoints.width, _winSizeInPoints.height);
    }
}

void Director::setNextDeltaTimeZero(bool bNextDeltaTimeZero)
{
    _nextDeltaTimeZero = bNextDeltaTimeZero;
}

void Director::setProjection(Projection projection)
{
    Size size = _winSizeInPoints;

    setViewport();

    switch (projection)
    {
        case Projection::_2D:
            kmGLMatrixMode(KM_GL_PROJECTION);
            kmGLLoadIdentity();
            kmMat4 orthoMatrix;
            kmMat4OrthographicProjection(&orthoMatrix, 0, size.width, 0, size.height, -1024, 1024 );
            kmGLMultMatrix(&orthoMatrix);
            kmGLMatrixMode(KM_GL_MODELVIEW);
            kmGLLoadIdentity();
            break;

        case Projection::_3D:
        {
            float zeye = this->getZEye();

            kmMat4 matrixPerspective, matrixLookup;

            kmGLMatrixMode(KM_GL_PROJECTION);
            kmGLLoadIdentity();

            // issue #1334
            kmMat4PerspectiveProjection( &matrixPerspective, 60, (GLfloat)size.width/size.height, 0.1f, zeye*2);
            // kmMat4PerspectiveProjection( &matrixPerspective, 60, (GLfloat)size.width/size.height, 0.1f, 1500);

            kmGLMultMatrix(&matrixPerspective);

            kmGLMatrixMode(KM_GL_MODELVIEW);
            kmGLLoadIdentity();
            kmVec3 eye, center, up;
            kmVec3Fill( &eye, size.width/2, size.height/2, zeye );
            kmVec3Fill( &center, size.width/2, size.height/2, 0.0f );
            kmVec3Fill( &up, 0.0f, 1.0f, 0.0f);
            kmMat4LookAt(&matrixLookup, &eye, &center, &up);
            kmGLMultMatrix(&matrixLookup);
            break;
        }
            
        case Projection::CUSTOM:
            if (_projectionDelegate)
                _projectionDelegate->updateProjection();
            break;
            
        default:
            CCLOG("cocos2d: Director: unrecognized projection");
            break;
    }

    _projection = projection;
    GL::setProjectionMatrixDirty();
}

void Director::purgeCachedData(void)
{
    LabelBMFont::purgeCachedData();
    if (s_SharedDirector->getOpenGLView())
    {
        SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
        TextureCache::getInstance()->removeUnusedTextures();
    }
    FileUtils::getInstance()->purgeCachedEntries();
}

float Director::getZEye(void) const
{
    return (_winSizeInPoints.height / 1.1566f);
}

void Director::setAlphaBlending(bool bOn)
{
    if (bOn)
    {
        GL::blendFunc(CC_BLEND_SRC, CC_BLEND_DST);
    }
    else
    {
        GL::blendFunc(GL_ONE, GL_ZERO);
    }

    CHECK_GL_ERROR_DEBUG();
}

void Director::setDepthTest(bool bOn)
{
    if (bOn)
    {
        glClearDepth(1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
//        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }
    CHECK_GL_ERROR_DEBUG();
}

static void
GLToClipTransform(kmMat4 *transformOut)
{
	kmMat4 projection;
	kmGLGetMatrix(KM_GL_PROJECTION, &projection);
	
	kmMat4 modelview;
	kmGLGetMatrix(KM_GL_MODELVIEW, &modelview);
	
	kmMat4Multiply(transformOut, &projection, &modelview);
}

Point Director::convertToGL(const Point& uiPoint)
{
    kmMat4 transform;
	GLToClipTransform(&transform);
	
	kmMat4 transformInv;
	kmMat4Inverse(&transformInv, &transform);
	
	// Calculate z=0 using -> transform*[0, 0, 0, 1]/w
	kmScalar zClip = transform.mat[14]/transform.mat[15];
	
    Size glSize = _openGLView->getDesignResolutionSize();
	kmVec3 clipCoord = {2.0f*uiPoint.x/glSize.width - 1.0f, 1.0f - 2.0f*uiPoint.y/glSize.height, zClip};
	
	kmVec3 glCoord;
	kmVec3TransformCoord(&glCoord, &clipCoord, &transformInv);
	
	return Point(glCoord.x, glCoord.y);
}

Point Director::convertToUI(const Point& glPoint)
{
    kmMat4 transform;
	GLToClipTransform(&transform);
    
	kmVec3 clipCoord;
	// Need to calculate the zero depth from the transform.
	kmVec3 glCoord = {glPoint.x, glPoint.y, 0.0};
	kmVec3TransformCoord(&clipCoord, &glCoord, &transform);
	
	Size glSize = _openGLView->getDesignResolutionSize();
	return Point(glSize.width*(clipCoord.x*0.5 + 0.5), glSize.height*(-clipCoord.y*0.5 + 0.5));
}

const Size& Director::getWinSize(void) const
{
    return _winSizeInPoints;
}

Size Director::getWinSizeInPixels() const
{
    return Size(_winSizeInPoints.width * _contentScaleFactor, _winSizeInPoints.height * _contentScaleFactor);
}

Size Director::getVisibleSize() const
{
    if (_openGLView)
    {
        return _openGLView->getVisibleSize();
    }
    else 
    {
        return Size::ZERO;
    }
}

Point Director::getVisibleOrigin() const
{
    if (_openGLView)
    {
        return _openGLView->getVisibleOrigin();
    }
    else 
    {
        return Point::ZERO;
    }
}

// scene management

void Director::runWithScene(Scene *pScene)
{
    CCASSERT(pScene != NULL, "This command can only be used to start the Director. There is already a scene present.");
    CCASSERT(_runningScene == NULL, "_runningScene should be null");

    pushScene(pScene);
    startAnimation();
}

void Director::replaceScene(Scene *pScene)
{
    CCASSERT(_runningScene, "Use runWithScene: instead to start the director");
    CCASSERT(pScene != NULL, "the scene should not be null");

    unsigned int index = _scenesStack->count();

    _sendCleanupToScene = true;
    _scenesStack->replaceObjectAtIndex(index - 1, pScene);

    _nextScene = pScene;
}

void Director::pushScene(Scene *pScene)
{
    CCASSERT(pScene, "the scene should not null");

    _sendCleanupToScene = false;

    _scenesStack->addObject(pScene);
    _nextScene = pScene;
}

void Director::popScene(void)
{
    CCASSERT(_runningScene != NULL, "running scene should not null");

    _scenesStack->removeLastObject();
    unsigned int c = _scenesStack->count();

    if (c == 0)
    {
        end();
    }
    else
    {
        _sendCleanupToScene = true;
        _nextScene = (Scene*)_scenesStack->objectAtIndex(c - 1);
    }
}

void Director::popToRootScene(void)
{
    popToSceneStackLevel(1);
}

void Director::popToSceneStackLevel(int level)
{
    CCASSERT(_runningScene != NULL, "A running Scene is needed");
    int c = (int)_scenesStack->count();

    // level 0? -> end
    if (level == 0)
    {
        end();
        return;
    }

    // current level or lower -> nothing
    if (level >= c)
        return;

	// pop stack until reaching desired level
	while (c > level)
    {
		Scene *current = (Scene*)_scenesStack->lastObject();

		if (current->isRunning())
        {
            current->onExitTransitionDidStart();
            current->onExit();
		}

        current->cleanup();
        _scenesStack->removeLastObject();
		c--;
	}

	_nextScene = (Scene*)_scenesStack->lastObject();
	_sendCleanupToScene = false;
}

void Director::end()
{
    _purgeDirecotorInNextLoop = true;
}

void Director::purgeDirector()
{
    // cleanup scheduler
    getScheduler()->unscheduleAll();
    
    // don't release the event handlers
    // They are needed in case the director is run again
    _touchDispatcher->removeAllDelegates();

    if (_runningScene)
    {
        _runningScene->onExitTransitionDidStart();
        _runningScene->onExit();
        _runningScene->cleanup();
        _runningScene->release();
    }
    
    _runningScene = NULL;
    _nextScene = NULL;

    // remove all objects, but don't release it.
    // runWithScene might be executed after 'end'.
    _scenesStack->removeAllObjects();

    stopAnimation();

    CC_SAFE_RELEASE_NULL(_FPSLabel);
    CC_SAFE_RELEASE_NULL(_SPFLabel);
    CC_SAFE_RELEASE_NULL(_drawsLabel);

    // purge bitmap cache
    LabelBMFont::purgeCachedData();

    // purge all managed caches
    DrawPrimitives::free();
    AnimationCache::destroyInstance();
    SpriteFrameCache::destroyInstance();
    TextureCache::destroyInstance();
    ShaderCache::destroyInstance();
    FileUtils::destroyInstance();
    Configuration::destroyInstance();

    // cocos2d-x specific data structures
    UserDefault::destroyInstance();
    NotificationCenter::destroyInstance();

    GL::invalidateStateCache();
    
    CHECK_GL_ERROR_DEBUG();
    
    // OpenGL view
    _openGLView->end();
    _openGLView = NULL;

    // delete Director
    release();
}

void Director::setNextScene(void)
{
    bool runningIsTransition = dynamic_cast<TransitionScene*>(_runningScene) != NULL;
    bool newIsTransition = dynamic_cast<TransitionScene*>(_nextScene) != NULL;

    // If it is not a transition, call onExit/cleanup
     if (! newIsTransition)
     {
         if (_runningScene)
         {
             _runningScene->onExitTransitionDidStart();
             _runningScene->onExit();
         }
 
         // issue #709. the root node (scene) should receive the cleanup message too
         // otherwise it might be leaked.
         if (_sendCleanupToScene && _runningScene)
         {
             _runningScene->cleanup();
         }
     }

    if (_runningScene)
    {
        _runningScene->release();
    }
    _runningScene = _nextScene;
    _nextScene->retain();
    _nextScene = NULL;

    if ((! runningIsTransition) && _runningScene)
    {
        _runningScene->onEnter();
        _runningScene->onEnterTransitionDidFinish();
    }
}

void Director::pause(void)
{
    if (_paused)
    {
        return;
    }

    _oldAnimationInterval = _animationInterval;

    // when paused, don't consume CPU
    setAnimationInterval(1 / 4.0);
    _paused = true;
}

void Director::resume(void)
{
    if (! _paused)
    {
        return;
    }

    setAnimationInterval(_oldAnimationInterval);

    if (gettimeofday(_lastUpdate, NULL) != 0)
    {
        CCLOG("cocos2d: Director: Error in gettimeofday");
    }

    _paused = false;
    _deltaTime = 0;
}

// display the FPS using a LabelAtlas
// updates the FPS every frame
void Director::showStats(void)
{
    _frames++;
    _accumDt += _deltaTime;
    
    if (_displayStats)
    {
        if (_FPSLabel && _SPFLabel && _drawsLabel)
        {
            if (_accumDt > CC_DIRECTOR_STATS_INTERVAL)
            {
                sprintf(_FPS, "%.3f", _secondsPerFrame);
                _SPFLabel->setString(_FPS);
                
                _frameRate = _frames / _accumDt;
                _frames = 0;
                _accumDt = 0;
                
                sprintf(_FPS, "%.1f", _frameRate);
                _FPSLabel->setString(_FPS);
                
                sprintf(_FPS, "%4lu", (unsigned long)g_uNumberOfDraws);
                _drawsLabel->setString(_FPS);
            }
            
            _drawsLabel->visit();
            _FPSLabel->visit();
            _SPFLabel->visit();
        }
    }    
    
    g_uNumberOfDraws = 0;
}

void Director::calculateMPF()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    
    _secondsPerFrame = (now.tv_sec - _lastUpdate->tv_sec) + (now.tv_usec - _lastUpdate->tv_usec) / 1000000.0f;
}

// returns the FPS image data pointer and len
void Director::getFPSImageData(unsigned char** datapointer, unsigned int* length)
{
    // XXX fixed me if it should be used 
    *datapointer = cc_fps_images_png;
	*length = cc_fps_images_len();
}

void Director::createStatsLabel()
{
    Texture2D *texture = NULL;
    TextureCache *textureCache = TextureCache::getInstance();

    if( _FPSLabel && _SPFLabel )
    {
        CC_SAFE_RELEASE_NULL(_FPSLabel);
        CC_SAFE_RELEASE_NULL(_SPFLabel);
        CC_SAFE_RELEASE_NULL(_drawsLabel);
        textureCache->removeTextureForKey("cc_fps_images");
        FileUtils::getInstance()->purgeCachedEntries();
    }

    Texture2D::PixelFormat currentFormat = Texture2D::getDefaultAlphaPixelFormat();
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);
    unsigned char *data = NULL;
    unsigned int data_len = 0;
    getFPSImageData(&data, &data_len);

    Image* image = new Image();
    bool isOK = image->initWithImageData(data, data_len);
    if (!isOK) {
        CCLOGERROR("%s", "Fails: init fps_images");
        return;
    }

    texture = textureCache->addUIImage(image, "cc_fps_images");
    CC_SAFE_RELEASE(image);

    /*
     We want to use an image which is stored in the file named ccFPSImage.c 
     for any design resolutions and all resource resolutions. 
     
     To achieve this,
     
     Firstly, we need to ignore 'contentScaleFactor' in 'AtlasNode' and 'LabelAtlas'.
     So I added a new method called 'setIgnoreContentScaleFactor' for 'AtlasNode',
     this is not exposed to game developers, it's only used for displaying FPS now.
     
     Secondly, the size of this image is 480*320, to display the FPS label with correct size, 
     a factor of design resolution ratio of 480x320 is also needed.
     */
    float factor = EGLView::getInstance()->getDesignResolutionSize().height / 320.0f;

    _FPSLabel = new LabelAtlas();
    _FPSLabel->setIgnoreContentScaleFactor(true);
    _FPSLabel->initWithString("00.0", texture, 12, 32 , '.');
    _FPSLabel->setScale(factor);

    _SPFLabel = new LabelAtlas();
    _SPFLabel->setIgnoreContentScaleFactor(true);
    _SPFLabel->initWithString("0.000", texture, 12, 32, '.');
    _SPFLabel->setScale(factor);

    _drawsLabel = new LabelAtlas();
    _drawsLabel->setIgnoreContentScaleFactor(true);
    _drawsLabel->initWithString("000", texture, 12, 32, '.');
    _drawsLabel->setScale(factor);

    Texture2D::setDefaultAlphaPixelFormat(currentFormat);

    _drawsLabel->setPosition(Point(0, 34*factor) + CC_DIRECTOR_STATS_POSITION);
    _SPFLabel->setPosition(Point(0, 17*factor) + CC_DIRECTOR_STATS_POSITION);
    _FPSLabel->setPosition(CC_DIRECTOR_STATS_POSITION);
}

float Director::getContentScaleFactor(void) const
{
    return _contentScaleFactor;
}

void Director::setContentScaleFactor(float scaleFactor)
{
    if (scaleFactor != _contentScaleFactor)
    {
        _contentScaleFactor = scaleFactor;
        createStatsLabel();
    }
}

Node* Director::getNotificationNode() 
{ 
    return _notificationNode; 
}

void Director::setNotificationNode(Node *node)
{
    CC_SAFE_RELEASE(_notificationNode);
    _notificationNode = node;
    CC_SAFE_RETAIN(_notificationNode);
}

DirectorDelegate* Director::getDelegate() const
{
    return _projectionDelegate;
}

void Director::setDelegate(DirectorDelegate* pDelegate)
{
    _projectionDelegate = pDelegate;
}

void Director::setScheduler(Scheduler* pScheduler)
{
    if (_scheduler != pScheduler)
    {
        CC_SAFE_RETAIN(pScheduler);
        CC_SAFE_RELEASE(_scheduler);
        _scheduler = pScheduler;
    }
}

Scheduler* Director::getScheduler() const
{
    return _scheduler;
}

void Director::setActionManager(ActionManager* pActionManager)
{
    if (_actionManager != pActionManager)
    {
        CC_SAFE_RETAIN(pActionManager);
        CC_SAFE_RELEASE(_actionManager);
        _actionManager = pActionManager;
    }    
}

ActionManager* Director::getActionManager() const
{
    return _actionManager;
}

void Director::setTouchDispatcher(TouchDispatcher* pTouchDispatcher)
{
    if (_touchDispatcher != pTouchDispatcher)
    {
        CC_SAFE_RETAIN(pTouchDispatcher);
        CC_SAFE_RELEASE(_touchDispatcher);
        _touchDispatcher = pTouchDispatcher;
    }    
}

TouchDispatcher* Director::getTouchDispatcher() const
{
    return _touchDispatcher;
}

void Director::setKeyboardDispatcher(KeyboardDispatcher* pKeyboardDispatcher)
{
    CC_SAFE_RETAIN(pKeyboardDispatcher);
    CC_SAFE_RELEASE(_keyboardDispatcher);
    _keyboardDispatcher = pKeyboardDispatcher;
}

KeyboardDispatcher* Director::getKeyboardDispatcher() const
{
    return _keyboardDispatcher;
}

void Director::setKeypadDispatcher(KeypadDispatcher* pKeypadDispatcher)
{
    CC_SAFE_RETAIN(pKeypadDispatcher);
    CC_SAFE_RELEASE(_keypadDispatcher);
    _keypadDispatcher = pKeypadDispatcher;
}

KeypadDispatcher* Director::getKeypadDispatcher() const
{
    return _keypadDispatcher;
}

void Director::setAccelerometer(Accelerometer* pAccelerometer)
{
    if (_accelerometer != pAccelerometer)
    {
        CC_SAFE_DELETE(_accelerometer);
        _accelerometer = pAccelerometer;
    }
}

Accelerometer* Director::getAccelerometer() const
{
    return _accelerometer;
}

/***************************************************
* implementation of DisplayLinkDirector
**************************************************/

// should we implement 4 types of director ??
// I think DisplayLinkDirector is enough
// so we now only support DisplayLinkDirector
void DisplayLinkDirector::startAnimation(void)
{
    if (gettimeofday(_lastUpdate, NULL) != 0)
    {
        CCLOG("cocos2d: DisplayLinkDirector: Error on gettimeofday");
    }

    _invalid = false;
#ifndef EMSCRIPTEN
    Application::getInstance()->setAnimationInterval(_animationInterval);
#endif // EMSCRIPTEN
}

void DisplayLinkDirector::mainLoop(void)
{
    if (_purgeDirecotorInNextLoop)
    {
        _purgeDirecotorInNextLoop = false;
        purgeDirector();
    }
    else if (! _invalid)
     {
         drawScene();
     
         // release the objects
         PoolManager::sharedPoolManager()->pop();        
     }
}

void DisplayLinkDirector::stopAnimation(void)
{
    _invalid = true;
}

void DisplayLinkDirector::setAnimationInterval(double dValue)
{
    _animationInterval = dValue;
    if (! _invalid)
    {
        stopAnimation();
        startAnimation();
    }    
}

NS_CC_END

