/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2013 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

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
#include "CCDrawingPrimitives.h"
#include "CCNS.h"
#include "CCScene.h"
#include "CCArray.h"
#include "CCScheduler.h"
#include "ccMacros.h"
#include "CCTransition.h"
#include "CCTextureCache.h"
#include "CCSpriteFrameCache.h"
#include "CCAutoreleasePool.h"
#include "platform/CCFileUtils.h"
#include "CCApplication.h"
#include "CCLabelBMFont.h"
#include "CCActionManager.h"
#include "CCAnimationCache.h"
#include "CCTouch.h"
#include "CCUserDefault.h"
#include "ccGLStateCache.h"
#include "CCShaderCache.h"
#include "kazmath/kazmath.h"
#include "kazmath/GL/matrix.h"
#include "CCProfiling.h"
#include "platform/CCImage.h"
#include "CCEGLView.h"
#include "CCConfiguration.h"
#include "CCEventDispatcher.h"
#include "CCEventCustom.h"
#include "CCFontFreeType.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCFrustum.h"
#include "CCConsole.h"

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
static DisplayLinkDirector *s_SharedDirector = nullptr;

#define kDefaultFPS        60  // 60 frames per second
extern const char* cocos2dVersion(void);

const char *Director::EVENT_PROJECTION_CHANGED = "director_projection_changed";
const char *Director::EVENT_AFTER_DRAW = "director_after_draw";
const char *Director::EVENT_AFTER_VISIT = "director_after_visit";
const char *Director::EVENT_AFTER_UPDATE = "director_after_udpate";

Director* Director::getInstance()
{
    if (!s_SharedDirector)
    {
        s_SharedDirector = new DisplayLinkDirector();
        s_SharedDirector->init();
    }

    return s_SharedDirector;
}

Director::Director()
{
}

bool Director::init(void)
{
    setDefaultValues();

    // scenes
    _runningScene = nullptr;
    _nextScene = nullptr;

    _notificationNode = nullptr;

    _scenesStack.reserve(15);

    // FPS
    _accumDt = 0.0f;
    _frameRate = 0.0f;
    _FPSLabel = nullptr;
    _SPFLabel = nullptr;
    _drawsLabel = nullptr;
    _totalFrames = _frames = 0;
    _FPS = new char[10];
    _lastUpdate = new struct timeval;

    // paused ?
    _paused = false;

    // purge ?
    _purgeDirectorInNextLoop = false;

    _winSizeInPoints = Size::ZERO;

    _openGLView = nullptr;

    _cullingFrustum = new Frustum();

    _contentScaleFactor = 1.0f;

    // scheduler
    _scheduler = new Scheduler();
    // action manager
    _actionManager = new ActionManager();
    _scheduler->scheduleUpdateForTarget(_actionManager, Scheduler::PRIORITY_SYSTEM, false);

    _eventDispatcher = new EventDispatcher();
    _eventAfterDraw = new EventCustom(EVENT_AFTER_DRAW);
    _eventAfterDraw->setUserData(this);
    _eventAfterVisit = new EventCustom(EVENT_AFTER_VISIT);
    _eventAfterVisit->setUserData(this);
    _eventAfterUpdate = new EventCustom(EVENT_AFTER_UPDATE);
    _eventAfterUpdate->setUserData(this);
    _eventProjectionChanged = new EventCustom(EVENT_PROJECTION_CHANGED);
    _eventProjectionChanged->setUserData(this);


    //init TextureCache
    initTextureCache();

    _renderer = new Renderer;
    _console = new Console;

    return true;
}

Director::~Director(void)
{
    CCLOGINFO("deallocing Director: %p", this);

    CC_SAFE_RELEASE(_FPSLabel);
    CC_SAFE_RELEASE(_SPFLabel);
    CC_SAFE_RELEASE(_drawsLabel);

    CC_SAFE_RELEASE(_runningScene);
    CC_SAFE_RELEASE(_notificationNode);
    CC_SAFE_RELEASE(_scheduler);
    CC_SAFE_RELEASE(_actionManager);
    CC_SAFE_RELEASE(_eventDispatcher);

    delete _eventAfterUpdate;
    delete _eventAfterDraw;
    delete _eventAfterVisit;
    delete _eventProjectionChanged;

    delete _renderer;
    delete _console;

    // clean auto release pool
    PoolManager::destroyInstance();

    // delete _lastUpdate
    CC_SAFE_DELETE(_lastUpdate);
    // delete fps string
    delete []_FPS;

    s_SharedDirector = nullptr;
}

void Director::setDefaultValues(void)
{
	Configuration *conf = Configuration::getInstance();

	// default FPS
	double fps = conf->getValue("cocos2d.x.fps", Value(kDefaultFPS)).asDouble();
	_oldAnimationInterval = _animationInterval = 1.0 / fps;

	// Display FPS
	_displayStats = conf->getValue("cocos2d.x.display_fps", Value(false)).asBool();

	// GL projection
    std::string projection = conf->getValue("cocos2d.x.gl.projection", Value("3d")).asString();
	if (projection == "3d")
		_projection = Projection::_3D;
	else if (projection == "2d")
		_projection = Projection::_2D;
	else if (projection == "custom")
		_projection = Projection::CUSTOM;
	else
		CCASSERT(false, "Invalid projection value");

	// Default pixel format for PNG images with alpha
    std::string pixel_format = conf->getValue("cocos2d.x.texture.pixel_format_for_png", Value("rgba8888")).asString();
	if (pixel_format == "rgba8888")
		Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
	else if(pixel_format == "rgba4444")
		Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);
	else if(pixel_format == "rgba5551")
		Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGB5A1);

	// PVR v2 has alpha premultiplied ?
	bool pvr_alpha_premultipled = conf->getValue("cocos2d.x.texture.pvrv2_has_alpha_premultiplied", Value(false)).asBool();
	Texture2D::PVRImagesHavePremultipliedAlpha(pvr_alpha_premultipled);
}

void Director::setGLDefaultValues()
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
void Director::drawScene()
{
    // calculate "global" dt
    calculateDeltaTime();

    if (_openGLView)
    {
        _openGLView->pollInputEvents();
    }

    //tick before glClear: issue #533
    if (! _paused)
    {
        _scheduler->update(_deltaTime);
        _eventDispatcher->dispatchEvent(_eventAfterUpdate);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* to avoid flickr, nextScene MUST be here: after tick and before draw.
     XXX: Which bug is this one. It seems that it can't be reproduced with v0.9 */
    if (_nextScene)
    {
        setNextScene();
    }

    kmGLPushMatrix();

    //construct the frustum
    {
        kmMat4 view;
        kmMat4 projection;
        kmGLGetMatrix(KM_GL_PROJECTION, &projection);
        kmGLGetMatrix(KM_GL_MODELVIEW, &view);

        _cullingFrustum->setupFromMatrix(view, projection);
    }

    // draw the scene
    if (_runningScene)
    {
        _runningScene->visit();
        _eventDispatcher->dispatchEvent(_eventAfterVisit);
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

    _renderer->render();
    _eventDispatcher->dispatchEvent(_eventAfterDraw);

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

void Director::calculateDeltaTime()
{
    struct timeval now;

    if (gettimeofday(&now, nullptr) != 0)
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

#if COCOS2D_DEBUG
    // If we are debugging our code, prevent big delta time
    if (_deltaTime > 0.2f)
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
void Director::setOpenGLView(EGLView *openGLView)
{
    CCASSERT(openGLView, "opengl view should not be null");

    if (_openGLView != openGLView)
    {
		// Configuration. Gather GPU info
		Configuration *conf = Configuration::getInstance();
		conf->gatherGPUInfo();
        CCLOG("%s\n",conf->getInfo().c_str());

        // EAGLView is not a Object
        delete _openGLView; // [openGLView_ release]
        _openGLView = openGLView;

        // set size
        _winSizeInPoints = _openGLView->getDesignResolutionSize();

        createStatsLabel();

        if (_openGLView)
        {
            setGLDefaultValues();
        }

        _renderer->initGLView();

        CHECK_GL_ERROR_DEBUG();

//        _touchDispatcher->setDispatchEvents(true);
    }
}

TextureCache* Director::getTextureCache() const
{
    return _textureCache;
}

void Director::initTextureCache()
{
#ifdef EMSCRIPTEN
    _textureCache = new TextureCacheEmscripten();
#else
    _textureCache = new TextureCache();
#endif // EMSCRIPTEN
}

void Director::destroyTextureCache()
{
    if (_textureCache)
    {
        _textureCache->waitForQuit();
        CC_SAFE_RELEASE_NULL(_textureCache);
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
            kmMat4OrthographicProjection(&orthoMatrix, 0, size.width, 0, size.height, -1024, 1024);
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
            kmMat4PerspectiveProjection(&matrixPerspective, 60, (GLfloat)size.width/size.height, 0.1f, zeye*2);
            // kmMat4PerspectiveProjection( &matrixPerspective, 60, (GLfloat)size.width/size.height, 0.1f, 1500);

            kmGLMultMatrix(&matrixPerspective);

            kmGLMatrixMode(KM_GL_MODELVIEW);
            kmGLLoadIdentity();
            kmVec3 eye, center, up;
            kmVec3Fill(&eye, size.width/2, size.height/2, zeye);
            kmVec3Fill(&center, size.width/2, size.height/2, 0.0f);
            kmVec3Fill(&up, 0.0f, 1.0f, 0.0f);
            kmMat4LookAt(&matrixLookup, &eye, &center, &up);
            kmGLMultMatrix(&matrixLookup);
            break;
        }

        case Projection::CUSTOM:
            // Projection Delegate is no longer needed
            // since the event "PROJECTION CHANGED" is emitted
            break;

        default:
            CCLOG("cocos2d: Director: unrecognized projection");
            break;
    }

    _projection = projection;
    GL::setProjectionMatrixDirty();

    _eventDispatcher->dispatchEvent(_eventProjectionChanged);
}

void Director::purgeCachedData(void)
{
    LabelBMFont::purgeCachedData();
    if (s_SharedDirector->getOpenGLView())
    {
        SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
        _textureCache->removeUnusedTextures();
    }
    FileUtils::getInstance()->purgeCachedEntries();
}

float Director::getZEye(void) const
{
    return (_winSizeInPoints.height / 1.1566f);
}

void Director::setAlphaBlending(bool on)
{
    if (on)
    {
        GL::blendFunc(CC_BLEND_SRC, CC_BLEND_DST);
    }
    else
    {
        GL::blendFunc(GL_ONE, GL_ZERO);
    }

    CHECK_GL_ERROR_DEBUG();
}

void Director::setDepthTest(bool on)
{
    if (on)
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

static void GLToClipTransform(kmMat4 *transformOut)
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

void Director::runWithScene(Scene *scene)
{
    CCASSERT(scene != nullptr, "This command can only be used to start the Director. There is already a scene present.");
    CCASSERT(_runningScene == nullptr, "_runningScene should be null");

    pushScene(scene);
    startAnimation();
}

void Director::replaceScene(Scene *scene)
{
    CCASSERT(_runningScene, "Use runWithScene: instead to start the director");
    CCASSERT(scene != nullptr, "the scene should not be null");

    ssize_t index = _scenesStack.size();

    _sendCleanupToScene = true;
    _scenesStack.replace(index - 1, scene);

    _nextScene = scene;
}

void Director::pushScene(Scene *scene)
{
    CCASSERT(scene, "the scene should not null");

    _sendCleanupToScene = false;

    _scenesStack.pushBack(scene);
    _nextScene = scene;
}

void Director::popScene(void)
{
    CCASSERT(_runningScene != nullptr, "running scene should not null");

    _scenesStack.popBack();
    ssize_t c = _scenesStack.size();

    if (c == 0)
    {
        end();
    }
    else
    {
        _sendCleanupToScene = true;
        _nextScene = _scenesStack.at(c - 1);
    }
}

void Director::popToRootScene(void)
{
    popToSceneStackLevel(1);
}

void Director::popToSceneStackLevel(int level)
{
    CCASSERT(_runningScene != nullptr, "A running Scene is needed");
    ssize_t c = _scenesStack.size();

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
        auto current = _scenesStack.back();

		if (current->isRunning())
        {
            current->onExitTransitionDidStart();
            current->onExit();
		}

        current->cleanup();
        _scenesStack.popBack();
		--c;
	}

    _nextScene = _scenesStack.back();
	_sendCleanupToScene = false;
}

void Director::end()
{
    _purgeDirectorInNextLoop = true;
}

void Director::purgeDirector()
{
    // cleanup scheduler
    getScheduler()->unscheduleAll();
    
    // don't release the event handlers
    // They are needed in case the director is run again
//    _touchDispatcher->removeAllDelegates();

    if (_runningScene)
    {
        _runningScene->onExitTransitionDidStart();
        _runningScene->onExit();
        _runningScene->cleanup();
        _runningScene->release();
    }
    
    _runningScene = nullptr;
    _nextScene = nullptr;

    // remove all objects, but don't release it.
    // runWithScene might be executed after 'end'.
    _scenesStack.clear();

    stopAnimation();

    CC_SAFE_RELEASE_NULL(_FPSLabel);
    CC_SAFE_RELEASE_NULL(_SPFLabel);
    CC_SAFE_RELEASE_NULL(_drawsLabel);
    CC_SAFE_DELETE(_cullingFrustum);

    // purge bitmap cache
    LabelBMFont::purgeCachedData();

    FontFreeType::shutdownFreeType();

    // purge all managed caches
    DrawPrimitives::free();
    AnimationCache::destroyInstance();
    SpriteFrameCache::destroyInstance();
    ShaderCache::destroyInstance();
    FileUtils::destroyInstance();
    Configuration::destroyInstance();

    // cocos2d-x specific data structures
    UserDefault::destroyInstance();
    
    GL::invalidateStateCache();
    
    destroyTextureCache();

    CHECK_GL_ERROR_DEBUG();
    
    // OpenGL view
    if (_openGLView)
    {
        _openGLView->end();
        _openGLView = nullptr;
    }

    // delete Director
    release();
}

void Director::setNextScene()
{
    bool runningIsTransition = dynamic_cast<TransitionScene*>(_runningScene) != nullptr;
    bool newIsTransition = dynamic_cast<TransitionScene*>(_nextScene) != nullptr;

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
    _nextScene = nullptr;

    if ((! runningIsTransition) && _runningScene)
    {
        _runningScene->onEnter();
        _runningScene->onEnterTransitionDidFinish();
    }
}

void Director::pause()
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

void Director::resume()
{
    if (! _paused)
    {
        return;
    }

    setAnimationInterval(_oldAnimationInterval);

    _paused = false;
    _deltaTime = 0;
    // fix issue #3509, skip one fps to avoid incorrect time calculation.
    setNextDeltaTimeZero(true);
}

// display the FPS using a LabelAtlas
// updates the FPS every frame
void Director::showStats()
{
    ++_frames;
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
    gettimeofday(&now, nullptr);
    
    _secondsPerFrame = (now.tv_sec - _lastUpdate->tv_sec) + (now.tv_usec - _lastUpdate->tv_usec) / 1000000.0f;
}

// returns the FPS image data pointer and len
void Director::getFPSImageData(unsigned char** datapointer, ssize_t* length)
{
    // XXX fixed me if it should be used 
    *datapointer = cc_fps_images_png;
	*length = cc_fps_images_len();
}

void Director::createStatsLabel()
{
    Texture2D *texture = nullptr;

    if (_FPSLabel && _SPFLabel)
    {
        CC_SAFE_RELEASE_NULL(_FPSLabel);
        CC_SAFE_RELEASE_NULL(_SPFLabel);
        CC_SAFE_RELEASE_NULL(_drawsLabel);
        _textureCache->removeTextureForKey("/cc_fps_images");
        FileUtils::getInstance()->purgeCachedEntries();
    }

    Texture2D::PixelFormat currentFormat = Texture2D::getDefaultAlphaPixelFormat();
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);
    unsigned char *data = nullptr;
    ssize_t dataLength = 0;
    getFPSImageData(&data, &dataLength);

    Image* image = new Image();
    bool isOK = image->initWithImageData(data, dataLength);
    if (! isOK) {
        CCLOGERROR("%s", "Fails: init fps_images");
        return;
    }

    texture = _textureCache->addImage(image, "/cc_fps_images");
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

    _FPSLabel = LabelAtlas::create();
    _FPSLabel->retain();
    _FPSLabel->setIgnoreContentScaleFactor(true);
    _FPSLabel->initWithString("00.0", texture, 12, 32 , '.');
    _FPSLabel->setScale(factor);

    _SPFLabel = LabelAtlas::create();
    _SPFLabel->retain();
    _SPFLabel->setIgnoreContentScaleFactor(true);
    _SPFLabel->initWithString("0.000", texture, 12, 32, '.');
    _SPFLabel->setScale(factor);

    _drawsLabel = LabelAtlas::create();
    _drawsLabel->retain();
    _drawsLabel->setIgnoreContentScaleFactor(true);
    _drawsLabel->initWithString("000", texture, 12, 32, '.');
    _drawsLabel->setScale(factor);

    Texture2D::setDefaultAlphaPixelFormat(currentFormat);

    _drawsLabel->setPosition(Point(0, 34*factor) + CC_DIRECTOR_STATS_POSITION);
    _SPFLabel->setPosition(Point(0, 17*factor) + CC_DIRECTOR_STATS_POSITION);
    _FPSLabel->setPosition(CC_DIRECTOR_STATS_POSITION);
}

void Director::setContentScaleFactor(float scaleFactor)
{
    if (scaleFactor != _contentScaleFactor)
    {
        _contentScaleFactor = scaleFactor;
        createStatsLabel();
    }
}

void Director::setNotificationNode(Node *node)
{
    CC_SAFE_RELEASE(_notificationNode);
    _notificationNode = node;
    CC_SAFE_RETAIN(_notificationNode);
}

void Director::setScheduler(Scheduler* scheduler)
{
    if (_scheduler != scheduler)
    {
        CC_SAFE_RETAIN(scheduler);
        CC_SAFE_RELEASE(_scheduler);
        _scheduler = scheduler;
    }
}

void Director::setActionManager(ActionManager* actionManager)
{
    if (_actionManager != actionManager)
    {
        CC_SAFE_RETAIN(actionManager);
        CC_SAFE_RELEASE(_actionManager);
        _actionManager = actionManager;
    }    
}

void Director::setEventDispatcher(EventDispatcher* dispatcher)
{
    if (_eventDispatcher != dispatcher)
    {
        CC_SAFE_RETAIN(dispatcher);
        CC_SAFE_RELEASE(_eventDispatcher);
        _eventDispatcher = dispatcher;
    }
}

/***************************************************
* implementation of DisplayLinkDirector
**************************************************/

// should we implement 4 types of director ??
// I think DisplayLinkDirector is enough
// so we now only support DisplayLinkDirector
void DisplayLinkDirector::startAnimation()
{
    if (gettimeofday(_lastUpdate, nullptr) != 0)
    {
        CCLOG("cocos2d: DisplayLinkDirector: Error on gettimeofday");
    }

    _invalid = false;

    Application::getInstance()->setAnimationInterval(_animationInterval);
}

void DisplayLinkDirector::mainLoop()
{
    if (_purgeDirectorInNextLoop)
    {
        _purgeDirectorInNextLoop = false;
        purgeDirector();
    }
    else if (! _invalid)
    {
        drawScene();
     
        // release the objects
        PoolManager::getInstance()->getCurrentPool()->clear();
    }
}

void DisplayLinkDirector::stopAnimation()
{
    _invalid = true;
}

void DisplayLinkDirector::setAnimationInterval(double interval)
{
    _animationInterval = interval;
    if (! _invalid)
    {
        stopAnimation();
        startAnimation();
    }    
}

NS_CC_END

