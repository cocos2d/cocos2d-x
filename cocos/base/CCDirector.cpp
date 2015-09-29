/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2013 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2015 Chukong Technologies Inc.

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
#include "base/CCDirector.h"

// standard includes
#include <string>

#include "2d/CCDrawingPrimitives.h"
#include "2d/CCSpriteFrameCache.h"
#include "platform/CCFileUtils.h"

#include "2d/CCActionManager.h"
#include "2d/CCFontFNT.h"
#include "2d/CCFontAtlasCache.h"
#include "2d/CCAnimationCache.h"
#include "2d/CCTransition.h"
#include "2d/CCFontFreeType.h"
#include "2d/CCLabelAtlas.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/CCGLProgramStateCache.h"
#include "renderer/CCTextureCache.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCRenderState.h"
#include "renderer/CCFrameBuffer.h"
#include "2d/CCCamera.h"
#include "base/CCUserDefault.h"
#include "base/ccFPSImages.h"
#include "base/CCScheduler.h"
#include "base/ccMacros.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventCustom.h"
#include "base/CCConsole.h"
#include "base/CCAutoreleasePool.h"
#include "base/CCConfiguration.h"
#include "base/CCAsyncTaskPool.h"
#include "platform/CCApplication.h"

#if CC_ENABLE_SCRIPT_BINDING
#include "CCScriptSupport.h"
#endif

using namespace std;

NS_CC_BEGIN
// FIXME: it should be a Director ivar. Move it there once support for multiple directors is added

// singleton stuff
static DisplayLinkDirector *s_SharedDirector = nullptr;

#define kDefaultFPS        60  // 60 frames per second
extern const char* cocos2dVersion(void);

const char *Director::EVENT_PROJECTION_CHANGED = "director_projection_changed";
const char *Director::EVENT_AFTER_DRAW = "director_after_draw";
const char *Director::EVENT_AFTER_VISIT = "director_after_visit";
const char *Director::EVENT_AFTER_UPDATE = "director_after_update";

/*static*/ Director* Director::getInstance()
{
    if (!s_SharedDirector)
    {
        s_SharedDirector = new (std::nothrow) DisplayLinkDirector();
        CCASSERT(s_SharedDirector, "FATAL: Not enough memory");
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

    // FPS
    _accumDt = 0.0f;
    _frameRate = 0.0f;
    _totalFrames = 0;
    _lastUpdate = new struct timeval;
    _secondsPerFrame = 1.0f;

    // paused ?
    _paused = false;

    // purge ?
    _purgeDirectorInNextLoop = false;
    
    // restart ?
    _restartDirectorInNextLoop = false;
    
	_console = new (std::nothrow) Console;

	_windowCreatorScheduler = new Scheduler();
	_isPendingWindowCreation = false;

    _eventAfterDraw = new (std::nothrow) EventCustom(EVENT_AFTER_DRAW);
    _eventAfterDraw->setUserData(this);
    _eventAfterVisit = new (std::nothrow) EventCustom(EVENT_AFTER_VISIT);
    _eventAfterVisit->setUserData(this);
    _eventAfterUpdate = new (std::nothrow) EventCustom(EVENT_AFTER_UPDATE);
    _eventAfterUpdate->setUserData(this);
    _eventProjectionChanged = new (std::nothrow) EventCustom(EVENT_PROJECTION_CHANGED);
    _eventProjectionChanged->setUserData(this);


    //init TextureCache
    initTextureCache();

    _renderer = new (std::nothrow) Renderer;
    RenderState::initialize();

    return true;
}

Director::~Director(void)
{
    CCLOGINFO("deallocing Director: %p", this);

    delete _eventAfterUpdate;
    delete _eventAfterDraw;
    delete _eventAfterVisit;
    delete _eventProjectionChanged;

	_contexts.clear();

    delete _renderer;

    delete _console;

    // delete _lastUpdate
    CC_SAFE_DELETE(_lastUpdate);

    Configuration::destroyInstance();

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
        _defaultProjection = DirectorWindow::Projection::_3D;
    else if (projection == "2d")
        _defaultProjection = DirectorWindow::Projection::_2D;
    else if (projection == "custom")
        _defaultProjection = DirectorWindow::Projection::CUSTOM;
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
    Image::setPVRImagesHavePremultipliedAlpha(pvr_alpha_premultipled);
}

void Director::setGLDefaultValues()
{
	if(!_contexts.isLocked())
	{
		CCASSERT(false, "active context needs to be set before calling");
		return;
	}

	if(_contexts.getCurrentWindow()->openGLView == nullptr)
	{
		CCASSERT(false, "current window openglview needs to be set.");
		return;
	}

	setAlphaBlending(true);  //does this require the context to be active?
	setDepthTest(false); //does this require the context to be active?
	setProjection(_contexts.getCurrentWindow()->projection);
}

// Draw the Scene
void Director::drawScene()
{
    // calculate "global" dt
    calculateDeltaTime();

	GLImpl::pollEvents();

	for(auto& iter : _contexts)
	{
		bool lockSuccess = _contexts.setContextAndLock(iter.first);
		CCASSERT(lockSuccess, "context was not able to be locked");
		
		//TODO: (day): it this occurs, something went really wrong.
		//Either something held the lock on, or a window with that key could not be found.
		if(!lockSuccess)
			continue;

		DirectorWindow* window = iter.second;
		//TODO: (day): cleaner if iterating automatically lock and unlock.  don't implement in begin/end though.
		//which means this needs to be refactored to use a custom iterator.  For now, just make sure that our
		//values are the same.
		CCASSERT(window == _contexts.getCurrentWindow(), "values don't line up.  this is really bad.");
		if(window != iter.second)
			continue; //another catastrophic error.  

		window->openGLView->dispatchDeferredEvents();
		
		if (! _paused)
		{
			window->scheduler->update(_deltaTime);
			window->eventDispatcher->dispatchEvent(_eventAfterUpdate);
		}

		clearFBOs();
		_renderer->clear();

		/* to avoid flickr, nextScene MUST be here: after tick and before draw.
		 * FIXME: Which bug is this one. It seems that it can't be reproduced with v0.9
		 */
		if (window->nextScene)
		{
			setNextScene(*window);
		}

		pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    
		if (window->runningScene)
		{
	#if (CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION) || CC_USE_NAVMESH)
			window->runningScene->stepPhysicsAndNavigation(_deltaTime);
	#endif
			//clear draw stats
			_renderer->clearDrawStats();
        
			//render the scene
			window->runningScene->render(_renderer);
        
			window->eventDispatcher->dispatchEvent(_eventAfterVisit);
		}

		// draw the notifications node
		if (window->notificationNode)
		{
			window->notificationNode->visit(_renderer, Mat4::IDENTITY, 0);
		}

		if (_displayStats && window->openGLView)
		{
			showStats();
		}
		_renderer->render();

		window->eventDispatcher->dispatchEvent(_eventAfterDraw);

		popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

		_totalFrames++;

		// swap buffers
		if (window->openGLView)
		{
			window->openGLView->swapBuffers();
		}

		if (_displayStats)
		{
			calculateMPF();
		}

		GL::invalidateStateCache();

		_contexts.unlock();
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

void Director::createWithNewScene(GLView *openGLView, const std::function<void()> &onCreateFunction)
{
	_windowCreatorScheduler->performFunctionInCocosThread([&, openGLView, onCreateFunction]()
		{
			CCASSERT(openGLView, "opengl view should not be null");
			addOpenGLView(openGLView);

			_contexts.setContextAndLock(openGLView->getKey());

			onCreateFunction();

			_contexts.unlock();
		});

	_isPendingWindowCreation = true;
}

void Director::addOpenGLView(GLView *openGLView)
{
	//for now, we'll assume the first GLView added will be used as the main one.
	DirectorWindow* window = nullptr;
	if(_contexts.getMainWindow() == nullptr)
		window = _contexts.createMainView(openGLView);
	else
		window = _contexts.addGLView(openGLView);

	CCASSERT(window != nullptr,"null window");
	_contexts.setContextAndLock(openGLView->getKey());

	window->scenesStack.reserve(15);
	window->projection = _defaultProjection;
	window->initMatrixStack();

    // Configuration. Gather GPU info
    Configuration *conf = Configuration::getInstance();
    conf->gatherGPUInfo();
    CCLOG("%s\n",conf->getInfo().c_str());

    // set size
	window->cachedLastAbsoluteWindowSize = openGLView->getDesignResolutionSize();

    window->isStatusLabelUpdated = true;

    if (openGLView)
    {
        setGLDefaultValues();
    }

    _renderer->initGLView();

    CHECK_GL_ERROR_DEBUG();

	window->eventDispatcher->setEnabled(true);
	_contexts.unlock();
}

void Director::checkAndCloseGLViews()
{
	_contexts.removeIf(
		[](const DirectorWindow& window)
		{
			if(window.openGLView->windowShouldClose() || window.terminate)
			{
				return true;
			}
			return false;
		});
}


TextureCache* Director::getTextureCache() const
{
    return _textureCache;
}

void Director::initTextureCache()
{
    _textureCache = new (std::nothrow) TextureCache();
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
	DirectorWindow* window = _contexts.getCurrentWindow();
	CCASSERT(window != nullptr, "director does not have a current window set");

	if(window && window->openGLView)
	{
		window->openGLView->setViewPortInPoints(0, 0, window->openGLView->getDesignResolutionSize().width, window->openGLView->getDesignResolutionSize().height);
	}
}

void Director::setNextDeltaTimeZero(bool nextDeltaTimeZero)
{
    _nextDeltaTimeZero = nextDeltaTimeZero;
}

//Here to continue support for kmGLFreeAll(void) in deprecated.cpp 
void Director::resetMatrixStack()
{
	for (auto& iter : _contexts)
	{
		bool lockSuccess = _contexts.setContextAndLock(iter.first);
		CCASSERT(lockSuccess, "context was not able to be locked");
		iter.second->initMatrixStack();
		_contexts.unlock();
	}
}

void Director::popMatrix(MATRIX_STACK_TYPE type)
{
	DirectorWindow* window = _contexts.getCurrentWindow();
	CCASSERT(window != nullptr, "we must have a valid window when this is called!");
	if(window == nullptr)
		return;

    if(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW == type)
    {
        window->modelViewMatrixStack.pop();
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION == type)
    {
        window->projectionMatrixStack.pop();
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE == type)
    {
        window->textureMatrixStack.pop();
    }
    else
    {
        CCASSERT(false, "unknow matrix stack type");
    }
}

void Director::loadIdentityMatrix(MATRIX_STACK_TYPE type)
{
	DirectorWindow* window = _contexts.getCurrentWindow();
	CCASSERT(window != nullptr, "we must have a valid window when this is called!");
	if(window == nullptr)
		return;

    if(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW == type)
    {
        window->modelViewMatrixStack.top() = Mat4::IDENTITY;
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION == type)
    {
        window->projectionMatrixStack.top() = Mat4::IDENTITY;
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE == type)
    {
        window->textureMatrixStack.top() = Mat4::IDENTITY;
    }
    else
    {
        CCASSERT(false, "unknow matrix stack type");
    }
}

void Director::loadMatrix(MATRIX_STACK_TYPE type, const Mat4& mat)
{
	DirectorWindow* window = _contexts.getCurrentWindow();
	CCASSERT(window != nullptr, "we must have a valid window when this is called!");
	if(window == nullptr)
		return;

    if(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW == type)
    {
        window->modelViewMatrixStack.top() = mat;
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION == type)
    {
        window->projectionMatrixStack.top() = mat;
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE == type)
    {
        window->textureMatrixStack.top() = mat;
    }
    else
    {
        CCASSERT(false, "unknow matrix stack type");
    }
}

void Director::multiplyMatrix(MATRIX_STACK_TYPE type, const Mat4& mat)
{
	DirectorWindow* window = _contexts.getCurrentWindow();
	CCASSERT(window != nullptr, "we must have a valid window when this is called!");
	if(window == nullptr)
		return;

    if(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW == type)
    {
        window->modelViewMatrixStack.top() *= mat;
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION == type)
    {
        window->projectionMatrixStack.top() *= mat;
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE == type)
    {
        window->textureMatrixStack.top() *= mat;
    }
    else
    {
        CCASSERT(false, "unknow matrix stack type");
    }
}

void Director::pushMatrix(MATRIX_STACK_TYPE type)
{
	DirectorWindow* window = _contexts.getCurrentWindow();
	CCASSERT(window != nullptr, "we must have a valid window when this is called!");
	if(window == nullptr)
		return;

    if(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW == type)
    {
        window->modelViewMatrixStack.push(window->modelViewMatrixStack.top());
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION == type)
    {
        window->projectionMatrixStack.push(window->projectionMatrixStack.top());
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE == type)
    {
        window->textureMatrixStack.push(window->textureMatrixStack.top());
    }
    else
    {
        CCASSERT(false, "unknow matrix stack type");
    }
}

const Mat4& Director::getMatrix(MATRIX_STACK_TYPE type)
{
	DirectorWindow* window = _contexts.getCurrentWindow();
	CCASSERT(window != nullptr, "we must have a valid window when this is called!");
	if(window == nullptr)
		return Mat4::IDENTITY;

    if(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW == type)
    {
        return window->modelViewMatrixStack.top();
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION == type)
    {
        return window->projectionMatrixStack.top();
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE == type)
    {
        return window->textureMatrixStack.top();
    }

    CCASSERT(false, "unknow matrix stack type, will return modelview matrix instead");
    return  _contexts.getCurrentWindow()->modelViewMatrixStack.top();
}

void Director::setProjection(DirectorWindow::Projection projection)
{
	DirectorWindow* window = _contexts.getCurrentWindow();
	CCASSERT(window != nullptr, "we must have a valid window when this is called!");
	if(window == nullptr)
		return;

    Size size = window->openGLView->getDesignResolutionSize();

    setViewport();

    switch (projection)
    {
		case DirectorWindow::Projection::_2D:
        {
            loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);

            Mat4 orthoMatrix;
            Mat4::createOrthographicOffCenter(0, size.width, 0, size.height, -1024, 1024, &orthoMatrix);
            multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, orthoMatrix);
            loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
            break;
        }
            
		case DirectorWindow::Projection::_3D:
        {
            float zeye = this->getZEye();

            Mat4 matrixPerspective, matrixLookup;

            loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);

            // issue #1334
            Mat4::createPerspective(60, (GLfloat)size.width/size.height, 10, zeye+size.height/2, &matrixPerspective);

            multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, matrixPerspective);

            Vec3 eye(size.width/2, size.height/2, zeye), center(size.width/2, size.height/2, 0.0f), up(0.0f, 1.0f, 0.0f);
            Mat4::createLookAt(eye, center, up, &matrixLookup);
            multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, matrixLookup);
            
            loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
            break;
        }

		case DirectorWindow::Projection::CUSTOM:
            // Projection Delegate is no longer needed
            // since the event "PROJECTION CHANGED" is emitted
            break;

        default:
            CCLOG("cocos2d: Director: unrecognized projection");
            break;
    }

    window->projection = projection;
    GL::setProjectionMatrixDirty();

    window->eventDispatcher->dispatchEvent(_eventProjectionChanged);
}

void Director::purgeCachedData(void)
{
    FontFNT::purgeCachedData();
    FontAtlasCache::purgeCachedData();

	if(GLImpl::isGLViewStaticInitialized())
	{
		SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
		_textureCache->removeUnusedTextures();

		// Note: some tests such as ActionsTest are leaking refcounted textures
		// There should be no test textures left in the cache
		log("%s\n", _textureCache->getCachedTextureInfo().c_str());
	}

	FileUtils::getInstance()->purgeCachedEntries();
}

float Director::getZEye(void) const
{
	DirectorWindow* window = _contexts.getCurrentWindow();
	CCASSERT(window != nullptr, "we must have a valid window when this is called!");
	CCASSERT(window->openGLView != nullptr, "current window has a null openGLView");
	return ( window != nullptr && window->openGLView != nullptr )
		? window->openGLView->getDesignResolutionSize().height / 1.1566f
		: 0.0f;
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
    _renderer->setDepthTest(on);
}

void Director::setClearColor(const Color4F& clearColor)
{
    _renderer->setClearColor(clearColor);
	if(auto fb = getDefaultFrameBuffer())
	{
		fb->setClearColor(clearColor);
	}
}

void Director::createPendingWindows()
{
	CCASSERT(!_contexts.isLocked(), "no context should be active during window creation.");
	_windowCreatorScheduler->update(0.0f);
	_isPendingWindowCreation = false;
}

static void GLToClipTransform(Mat4 *transformOut)
{
    if(nullptr == transformOut) return;
    
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when setting matrix stack");

    auto projection = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    auto modelview = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    *transformOut = projection * modelview;
}

Vec2 Director::convertToGL(const Vec2& uiPoint)
{
	DirectorWindow* window = _contexts.getCurrentWindow();
	if(window == nullptr || window->openGLView == nullptr)
	{
		CCASSERT(window != nullptr, "we must have a valid window when this is called!");
		CCASSERT(window->openGLView != nullptr, "current window has a null openGLView");
		return Vec2::ZERO;
	}

	Mat4 transform;
    GLToClipTransform(&transform);

    Mat4 transformInv = transform.getInversed();

    // Calculate z=0 using -> transform*[0, 0, 0, 1]/w
    float zClip = transform.m[14]/transform.m[15];

    Size glSize = window->openGLView->getDesignResolutionSize();
    Vec4 clipCoord(2.0f*uiPoint.x/glSize.width - 1.0f, 1.0f - 2.0f*uiPoint.y/glSize.height, zClip, 1);

    Vec4 glCoord;
    //transformInv.transformPoint(clipCoord, &glCoord);
    transformInv.transformVector(clipCoord, &glCoord);
    float factor = 1.0/glCoord.w;
    return Vec2(glCoord.x * factor, glCoord.y * factor);
}

Vec2 Director::convertToUI(const Vec2& glPoint)
{
	DirectorWindow* window = _contexts.getCurrentWindow();
	if(window == nullptr || window->openGLView == nullptr)
	{
		CCASSERT(window != nullptr, "we must have a valid window when this is called!");
		CCASSERT(window->openGLView != nullptr, "current window has a null openGLView");
		return Vec2::ZERO;
	}

    Mat4 transform;
    GLToClipTransform(&transform);

    Vec4 clipCoord;
    // Need to calculate the zero depth from the transform.
    Vec4 glCoord(glPoint.x, glPoint.y, 0.0, 1);
    transform.transformVector(glCoord, &clipCoord);

	/*
	BUG-FIX #5506

	a = (Vx, Vy, Vz, 1)
	b = (a×M)T
	Out = 1 ⁄ bw(bx, by, bz)
	*/
	
	clipCoord.x = clipCoord.x / clipCoord.w;
	clipCoord.y = clipCoord.y / clipCoord.w;
	clipCoord.z = clipCoord.z / clipCoord.w;

    Size glSize = window->openGLView->getDesignResolutionSize();
    float factor = 1.0/glCoord.w;
    return Vec2(glSize.width*(clipCoord.x*0.5 + 0.5) * factor, glSize.height*(-clipCoord.y*0.5 + 0.5) * factor);
}

const Size& Director::getWinSize() const
{
	DirectorWindow* window = _contexts.getCurrentWindow();
	CCASSERT(window->openGLView != nullptr, "current window has a null openGLView");
	return ( window != nullptr && window->openGLView != nullptr )
		? window->openGLView->getDesignResolutionSize()
		: Size::ZERO;
}

Size Director::getWinSizeInPixels() const
{
	DirectorWindow* window = _contexts.getCurrentWindow();
	CCASSERT(window->openGLView != nullptr, "current window has a null openGLView");
    return ( window != nullptr && window->openGLView != nullptr )
		? Size(window->openGLView->getDesignResolutionSize().width * window->contentScaleFactor, window->openGLView->getDesignResolutionSize().height * window->contentScaleFactor)
		: Size::ZERO;
}

Size Director::getVisibleSize() const
{
	DirectorWindow* window = _contexts.getCurrentWindow();
	CCASSERT(window->openGLView != nullptr, "current window has a null openGLView");

    if (window && window->openGLView)
        return window->openGLView->getVisibleSize();
    else
        return Size::ZERO;
}

Vec2 Director::getVisibleOrigin() const
{
	DirectorWindow* window = _contexts.getCurrentWindow();
	CCASSERT(window->openGLView != nullptr, "current window has a null openGLView");

	if (window && window->openGLView)
		return window->openGLView->getVisibleOrigin();
	else
		return Vec2::ZERO;
}

// scene management
void Director::runWithScene(Scene *scene)
{
	CCASSERT(scene != nullptr, "This command can only be used to start the Director. There is already a scene present.");
	CCASSERT(_contexts.getCurrentWindow()->runningScene == nullptr, "_runningScene should be null");
	pushScene(scene);
	startAnimation();
}

void Director::replaceScene(Scene *scene)
{
	DirectorWindow* window = _contexts.getCurrentWindow();
	if(window == nullptr)
	{
		CCASSERT(false, "window is null!");
		return;
	}

    CCASSERT(scene != nullptr, "the scene should not be null");
    
    if (window->runningScene == nullptr) {
        runWithScene(scene);
        return;
    }
    
    if (scene == window->nextScene)
        return;
    
    if (window->nextScene)
    {
        if (window->nextScene->isRunning())
        {
            window->nextScene->onExit();
        }
        window->nextScene->cleanup();
        window->nextScene = nullptr;
    }

    ssize_t index = window->scenesStack.size();

    window->sendCleanupToScene = true;
    window->scenesStack.replace(index - 1, scene);

    window->nextScene = scene;
}

void Director::pushScene(Scene *scene)
{
	DirectorWindow* window = _contexts.getCurrentWindow();
	if(window == nullptr)
	{
		CCASSERT(false, "window is null!");
		return;
	}

	CCASSERT(scene, "the scene should not null");

    window->sendCleanupToScene = false;

    window->scenesStack.pushBack(scene);
    window->nextScene = scene;
}

void Director::popScene()
{
	DirectorWindow* window = _contexts.getCurrentWindow();
	if(window == nullptr)
	{
		CCASSERT(false, "window is null!");
		return;
	}

    CCASSERT(window->runningScene != nullptr, "running scene should not null");

    window->scenesStack.popBack();
    ssize_t c = window->scenesStack.size();

    if (c == 0)
    {
		window->terminate = true;
    }
    else
    {
        window->sendCleanupToScene = true;
        window->nextScene = window->scenesStack.at(c - 1);
    }
}

void Director::popToRootScene()
{
    popToSceneStackLevel(1);
}

void Director::popToSceneStackLevel(int level)
{
	DirectorWindow* window = _contexts.getCurrentWindow();
	if(window == nullptr)
	{
		CCASSERT(false, "window is null!");
		return;
	}

    CCASSERT(window->runningScene != nullptr, "A running Scene is needed");
    ssize_t c = window->scenesStack.size();

    // level 0? -> end
    if (level == 0)
    {
		window->terminate = true;
        return;
    }

    // current level or lower -> nothing
    if (level >= c)
        return;

    auto fisrtOnStackScene = window->scenesStack.back();
    if (fisrtOnStackScene == window->runningScene)
    {
        window->scenesStack.popBack();
        --c;
    }

    // pop stack until reaching desired level
    while (c > level)
    {
        auto current = window->scenesStack.back();

        if (current->isRunning())
        {
            current->onExit();
        }

        current->cleanup();
        window->scenesStack.popBack();
        --c;
    }

    window->nextScene = window->scenesStack.back();

    // cleanup running scene
    window->sendCleanupToScene = true;
}

void Director::end()
{
    _purgeDirectorInNextLoop = true;
}

void Director::restart()
{
    _restartDirectorInNextLoop = true;
}

void Director::reset()
{   
	for(auto& iter : _contexts)
	{
		iter.second->reset();
	}
    
	_windowCreatorScheduler->unscheduleAll();
	_isPendingWindowCreation = false;

    stopAnimation();  
    
    // purge bitmap cache
    FontFNT::purgeCachedData();
    
    FontFreeType::shutdownFreeType();
    
    // purge all managed caches
    
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (push)
#pragma warning (disable: 4996)
#endif
//it will crash clang static analyzer so hide it if __clang_analyzer__ defined
#ifndef __clang_analyzer__
    DrawPrimitives::freeResources();
#endif
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (pop)
#endif
    AnimationCache::destroyInstance();
    SpriteFrameCache::destroyInstance();
    GLProgramCache::destroyInstance();
    GLProgramStateCache::destroyInstance();
    FileUtils::destroyInstance();
    AsyncTaskPool::destoryInstance();
    
    // cocos2d-x specific data structures
    UserDefault::destroyInstance();

    GL::invalidateStateCache();

    RenderState::finalize();
    
    destroyTextureCache();
}

void Director::purgeDirector()
{
	_contexts.clear();

    reset();

    CHECK_GL_ERROR_DEBUG();

    // delete Director
    release();
}

void Director::restartDirector()
{
    reset();
    
    // RenderState need to be reinitialized
    RenderState::initialize();

    // Texture cache need to be reinitialized
    initTextureCache();

	for(auto& iter : _contexts)
	{
		iter.second->resetScheduler();
	}
  
    // release the objects
    PoolManager::getInstance()->getCurrentPool()->clear();
    
    // Real restart in script level
#if CC_ENABLE_SCRIPT_BINDING
    ScriptEvent scriptEvent(kRestartGame, NULL);
    ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&scriptEvent);
#endif
}

void Director::setNextScene(DirectorWindow& window)
{
    bool runningIsTransition = dynamic_cast<TransitionScene*>(window.runningScene) != nullptr;
    bool newIsTransition = dynamic_cast<TransitionScene*>(window.nextScene) != nullptr;

    // If it is not a transition, call onExit/cleanup
     if (! newIsTransition)
     {
         if (window.runningScene)
         {
             window.runningScene->onExitTransitionDidStart();
             window.runningScene->onExit();
         }
 
         // issue #709. the root node (scene) should receive the cleanup message too
         // otherwise it might be leaked.
         if (window.sendCleanupToScene && window.runningScene)
         {
             window.runningScene->cleanup();
         }
     }

    if (window.runningScene)
    {
        window.runningScene->release();
    }
    window.runningScene = window.nextScene;
    window.nextScene->retain();
    window.nextScene = nullptr;

    if ((! runningIsTransition) && window.runningScene)
    {
        window.runningScene->onEnter();
        window.runningScene->onEnterTransitionDidFinish();
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
	DirectorWindow* window = _contexts.getCurrentWindow();
	if(window == nullptr)
	{
		CCASSERT(false, "window is null!");
		return;
	}

    if (window->isStatusLabelUpdated)
    {
        window->createStatsLabel();
        window->isStatusLabelUpdated = false;
    }

    static unsigned long prevCalls = 0;
    static unsigned long prevVerts = 0;
    static float prevDeltaTime  = 0.016f; // 60FPS
    static const float FPS_FILTER = 0.10f;

    _accumDt += _deltaTime;
    
    if (_displayStats && window->FPSLabel && window->drawnBatchesLabel && window->drawnVerticesLabel)
    {
        char buffer[30];

        float dt = _deltaTime * FPS_FILTER + (1-FPS_FILTER) * prevDeltaTime;
        prevDeltaTime = dt;
        _frameRate = 1/dt;

        // Probably we don't need this anymore since
        // the framerate is using a low-pass filter
        // to make the FPS stable
        if (_accumDt > CC_DIRECTOR_STATS_INTERVAL)
        {
            sprintf(buffer, "%.1f / %.3f", _frameRate, _secondsPerFrame);
            window->FPSLabel->setString(buffer);
            _accumDt = 0;
        }

        auto currentCalls = (unsigned long)_renderer->getDrawnBatches();
        auto currentVerts = (unsigned long)_renderer->getDrawnVertices();
        if( currentCalls != prevCalls ) {
            sprintf(buffer, "GL calls:%6lu", currentCalls);
            window->drawnBatchesLabel->setString(buffer);
            prevCalls = currentCalls;
        }

        if( currentVerts != prevVerts) {
            sprintf(buffer, "GL verts:%6lu", currentVerts);
            window->drawnVerticesLabel->setString(buffer);
            prevVerts = currentVerts;
        }

        const Mat4& identity = Mat4::IDENTITY;
        window->drawnVerticesLabel->visit(_renderer, identity, 0);
        window->drawnBatchesLabel->visit(_renderer, identity, 0);
        window->FPSLabel->visit(_renderer, identity, 0);
    }
}

void Director::calculateMPF()
{
    static float prevSecondsPerFrame = 0;
    static const float MPF_FILTER = 0.10f;

    struct timeval now;
    gettimeofday(&now, nullptr);
    
    _secondsPerFrame = (now.tv_sec - _lastUpdate->tv_sec) + (now.tv_usec - _lastUpdate->tv_usec) / 1000000.0f;

    _secondsPerFrame = _secondsPerFrame * MPF_FILTER + (1-MPF_FILTER) * prevSecondsPerFrame;
    prevSecondsPerFrame = _secondsPerFrame;
}

// returns the FPS image data pointer and len
void Director::getFPSImageData(unsigned char** datapointer, ssize_t* length)
{
    // FIXME: fixed me if it should be used 
    *datapointer = cc_fps_images_png;
    *length = cc_fps_images_len();
}

void Director::setContentScaleFactor(float scaleFactor)
{
	DirectorWindow* window = _contexts.getCurrentWindow();
	if(window)
	{
		if(scaleFactor != window->contentScaleFactor)
		{
			window->contentScaleFactor = scaleFactor;
			window->isStatusLabelUpdated = true;
		}
	}
}

void Director::setNotificationNode(Node *node)
{
	DirectorWindow* window = _contexts.getCurrentWindow();
	if(window == nullptr)
	{
		CCASSERT(false, "window is null!");
		return;
	}

	Node* notificationNode = window->notificationNode;
	
	if (notificationNode != nullptr){
		notificationNode->onExitTransitionDidStart();
		notificationNode->onExit();
		notificationNode->cleanup();
	}
	CC_SAFE_RELEASE(notificationNode);

	window->notificationNode = node;
	if (node == nullptr)
		return;
	node->onEnter();
	node->onEnterTransitionDidFinish();
    CC_SAFE_RETAIN(node);
}

Scheduler* Director::getMainScheduler()
{
	return (_contexts.getMainWindow() != nullptr ) ? _contexts.getMainWindow()->scheduler : nullptr;
}

Scheduler* Director::getCurrentWindowScheduler() const
{
	DirectorWindow* window = _contexts.getCurrentWindow();
	CCASSERT(window != nullptr, "unable to find window");
	return (window != nullptr) ? window->scheduler : nullptr;
}

void Director::setScheduler(Scheduler* scheduler)
{
	if(_contexts.getMainWindow() != nullptr)
	{
		CC_SAFE_RETAIN(scheduler);
		CC_SAFE_RELEASE(_contexts.getMainWindow()->scheduler);
		_contexts.getMainWindow()->scheduler = scheduler;
	}
}

ActionManager* Director::getMainActionManager()
{
	return (_contexts.getMainWindow() != nullptr ) ? _contexts.getMainWindow()->actionManager : nullptr;
}

ActionManager* Director::getCurrentWindowActionManager() const
{
	DirectorWindow* window = _contexts.getCurrentWindow();
	CCASSERT(window != nullptr, "unable to find window");
	return (window != nullptr) ? window->actionManager : nullptr;
}

void Director::setActionManager(ActionManager* actionManager)
{
	if (_contexts.getMainWindow() != nullptr)
	{
		CC_SAFE_RETAIN(actionManager);
		CC_SAFE_RELEASE(_contexts.getMainWindow()->actionManager);
		_contexts.getMainWindow()->actionManager = actionManager;
	}
}

EventDispatcher* Director::getMainEventDispatcher()
{
	return (_contexts.getMainWindow() != nullptr ) ? _contexts.getMainWindow()->eventDispatcher : nullptr;
}

EventDispatcher* Director::getCurrentWindowEventDispatcher() const
{
	DirectorWindow* window = _contexts.getCurrentWindow();
	return (window != nullptr) ? window->eventDispatcher : nullptr;
}

void Director::setEventDispatcher(EventDispatcher* dispatcher)
{
	if (_contexts.getMainWindow() != nullptr)
	{
		CC_SAFE_RETAIN(dispatcher);
		CC_SAFE_RELEASE(_contexts.getMainWindow()->eventDispatcher);
		_contexts.getMainWindow()->eventDispatcher = dispatcher;
	}
}

void Director::applyDefaultFrameBuffer() 
{ 
	if(_contexts.getCurrentWindow() != nullptr) 
		_contexts.getCurrentWindow()->defaultFrameBuffer->applyFBO(); 
}

void Director::clearFBOs() 
{ 
	DirectorWindow* window = _contexts.getCurrentWindow();
	if(window != nullptr)
	{
		for (auto fbo : window->frameBuffers)
		{
			fbo->clearFBO();
		}
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

    _cocos2d_thread_id = std::this_thread::get_id();

    Application::getInstance()->setAnimationInterval(_animationInterval);

    // fix issue #3509, skip one fps to avoid incorrect time calculation.
    setNextDeltaTimeZero(true);
}

bool DisplayLinkDirector::mainLoop()
{
    if (_purgeDirectorInNextLoop)
    {
        _purgeDirectorInNextLoop = false;
        purgeDirector();
		return false;
    }
    else if (_restartDirectorInNextLoop)
    {
        _restartDirectorInNextLoop = false;
        restartDirector();
    }
    else if (! _invalid)
    {
        drawScene();
     
		checkAndCloseGLViews();

		if(_contexts.getMainWindow() == nullptr)
		{
			 purgeDirector();
			return false;
		}

        // release the objects
        PoolManager::getInstance()->getCurrentPool()->clear();
    }

	return true;
}

void DisplayLinkDirector::stopAnimation()
{
    _invalid = true;
}

void DisplayLinkDirector::setAnimationInterval(float interval)
{
    _animationInterval = interval;
    if (! _invalid)
    {
        stopAnimation();
        startAnimation();
    }    
}

NS_CC_END

