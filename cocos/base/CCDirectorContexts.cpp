
#include "2d/CCActionManager.h"
#include "2d/CCLabelAtlas.h"
#include "base/CCDirector.h"
#include "base/CCDirectorContexts.h"
#include "base/CCEventDispatcher.h"
#include "base/CCScheduler.h"
#include "platform/CCFileUtils.h"
#include "renderer/CCFrameBuffer.h"
#include "renderer/CCTextureCache.h"


NS_CC_BEGIN

DirectorWindow::DirectorWindow(GLView *glView)
		: openGLView(glView)
		, defaultFrameBuffer(nullptr)
		, frameBuffers()
		, runningScene(nullptr)
		, nextScene(nullptr)
		, sendCleanupToScene(nullptr)
		, scenesStack()
		, projection(Projection::DEFAULT)
		, contentScaleFactor(1.f)
		, notificationNode(nullptr)
		, landscape(false)
		, isStatusLabelUpdated(true)
		, FPSLabel( nullptr )
		, drawnBatchesLabel( nullptr )
		, drawnVerticesLabel( nullptr )
		, terminate(false)
		, defaultViewport()
		, modelViewMatrixStack()
		, projectionMatrixStack()
		, textureMatrixStack()
		, cachedLastAbsoluteWindowSize()
		, eventDispatcher(new EventDispatcher())
		, scheduler(new Scheduler())
		, actionManager(new ActionManager())
{
	CCASSERT(glView != nullptr, "glView cannot be null");
	defaultFrameBuffer = experimental::FrameBuffer::createFromDefault(glView);
	CCASSERT(defaultFrameBuffer != nullptr, "default frame buffer cannot be null");
	defaultFrameBuffer->retain();

    scheduler->scheduleUpdate(actionManager, Scheduler::PRIORITY_SYSTEM, false);

	frameBuffers.insert(defaultFrameBuffer);
}

DirectorWindow::~DirectorWindow()
{
	for(auto iter = frameBuffers.begin(); iter != frameBuffers.end(); ++iter)
	{
		delete *iter;
	}

	reset();

	CC_SAFE_RELEASE(actionManager);
	CC_SAFE_RELEASE(scheduler);
	CC_SAFE_RELEASE(eventDispatcher);

	if(openGLView)
	{
		openGLView->end(); //calls release
		openGLView = nullptr;
	}
}

void DirectorWindow::reset()
{
	CC_SAFE_RELEASE(notificationNode);
	CC_SAFE_RELEASE(FPSLabel);
    CC_SAFE_RELEASE(drawnVerticesLabel);
    CC_SAFE_RELEASE(drawnBatchesLabel);

	if(runningScene)
	{
		runningScene->onExit();
		runningScene->cleanup();
		runningScene->release();
	}

	runningScene = nullptr;
	nextScene = nullptr;
	eventDispatcher->removeAllEventListeners();

	scenesStack.clear();

	initMatrixStack();
}

void DirectorWindow::resetScheduler()
{
	scheduler->scheduleUpdate(actionManager, Scheduler::PRIORITY_SYSTEM, false);
}

//
// FIXME TODO
// Matrix code MUST NOT be part of the Director
// MUST BE moved outide.
// Why the Director must have this code ?
//
void DirectorWindow::initMatrixStack()
{
    while (!modelViewMatrixStack.empty())
    {
        modelViewMatrixStack.pop();
    }
    
    while (!projectionMatrixStack.empty())
    {
        projectionMatrixStack.pop();
    }
    
    while (!textureMatrixStack.empty())
    {
        textureMatrixStack.pop();
    }
    
    modelViewMatrixStack.push(Mat4::IDENTITY);
    projectionMatrixStack.push(Mat4::IDENTITY);
    textureMatrixStack.push(Mat4::IDENTITY);
}

void DirectorWindow::createStatsLabel()
{
	Texture2D *texture = nullptr;
    std::string fpsString = "00.0";
    std::string drawBatchString = "000";
    std::string drawVerticesString = "00000";
    if (FPSLabel)
    {
        fpsString = FPSLabel->getString();
        drawBatchString = drawnBatchesLabel->getString();
        drawVerticesString = drawnVerticesLabel->getString();
        
        CC_SAFE_RELEASE_NULL(FPSLabel);
        CC_SAFE_RELEASE_NULL(drawnBatchesLabel);
        CC_SAFE_RELEASE_NULL(drawnVerticesLabel);
        Director::getInstance()->getTextureCache()->removeTextureForKey("/cc_fps_images");
        FileUtils::getInstance()->purgeCachedEntries();
    }

    Texture2D::PixelFormat currentFormat = Texture2D::getDefaultAlphaPixelFormat();
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);
    unsigned char *data = nullptr;
    ssize_t dataLength = 0;
    Director::getInstance()->getFPSImageData(&data, &dataLength);

    Image* image = new (std::nothrow) Image();
    bool isOK = image->initWithImageData(data, dataLength);
    if (! isOK) {
        CCLOGERROR("%s", "Fails: init fps_images");
        return;
    }

    texture = Director::getInstance()->getTextureCache()->addImage(image, "/cc_fps_images");
    CC_SAFE_RELEASE(image);

    /*
     We want to use an image which is stored in the file named ccFPSImage.c 
     for any design resolutions and all resource resolutions. 
     
     To achieve this, we need to ignore 'contentScaleFactor' in 'AtlasNode' and 'LabelAtlas'.
     So I added a new method called 'setIgnoreContentScaleFactor' for 'AtlasNode',
     this is not exposed to game developers, it's only used for displaying FPS now.
     */
    float scaleFactor = 1 / CC_CONTENT_SCALE_FACTOR();

    FPSLabel = LabelAtlas::create();
    FPSLabel->retain();
    FPSLabel->setIgnoreContentScaleFactor(true);
    FPSLabel->initWithString(fpsString, texture, 12, 32 , '.');
    FPSLabel->setScale(scaleFactor);

    drawnBatchesLabel = LabelAtlas::create();
    drawnBatchesLabel->retain();
    drawnBatchesLabel->setIgnoreContentScaleFactor(true);
    drawnBatchesLabel->initWithString(drawBatchString, texture, 12, 32, '.');
    drawnBatchesLabel->setScale(scaleFactor);

    drawnVerticesLabel = LabelAtlas::create();
    drawnVerticesLabel->retain();
    drawnVerticesLabel->setIgnoreContentScaleFactor(true);
    drawnVerticesLabel->initWithString(drawVerticesString, texture, 12, 32, '.');
    drawnVerticesLabel->setScale(scaleFactor);


    Texture2D::setDefaultAlphaPixelFormat(currentFormat);

    const int height_spacing = 22 / CC_CONTENT_SCALE_FACTOR();
    drawnVerticesLabel->setPosition(Vec2(0, height_spacing*2) + openGLView->getVisibleOrigin());
    drawnBatchesLabel->setPosition(Vec2(0, height_spacing*1) + openGLView->getVisibleOrigin());
    FPSLabel->setPosition(Vec2(0, height_spacing*0) + openGLView->getVisibleOrigin());
}

ContextManager::ContextManager()
		: _windowMap()
		, _windowList()
		, _isLocked(false)
		, _currentWindow(nullptr)
		, _mainWindow(nullptr)
{
}

ContextManager::~ContextManager()
{
	delete _mainWindow;
}

DirectorWindow* ContextManager::createMainView(GLView *openGLView)
{
	CCASSERT(_windowList.size() == 0, "main window should be the first window created");
	CCASSERT(!_isLocked, "no context must be set");
	CCASSERT(openGLView, "opengl view should not be null");

	if(_mainWindow != nullptr)
	{
		if(_mainWindow->openGLView != nullptr && _mainWindow->openGLView != openGLView)
		{
			_mainWindow->openGLView->release();
			_mainWindow->openGLView = openGLView;
			openGLView->retain();
		}
	}
	else
	{
		_mainWindow = new DirectorWindow(openGLView);
		_windowMap[openGLView->getKey()] = _mainWindow;
		openGLView->retain();
	}

	return _mainWindow;
}

DirectorWindow* ContextManager::addGLView(GLView *openGLView)
{
	CCASSERT(_mainWindow != nullptr, "main window should be the first window created");
	CCASSERT(!_isLocked, "no context must be set");
	CCASSERT(openGLView, "opengl view should not be null");
	WindowKey windowKey = openGLView->getKey();

	DirectorWindow* window;

	//because the main view is also in the map, it can also have its openGLView replaced through this function.
	auto iter = _windowMap.find(windowKey);
	if(iter != _windowMap.end())
	{
		CCASSERT(iter->second != nullptr, "all DirectorWindow pointers in the map should be non-null, always.");
		window = iter->second;
		CCASSERT(false, "all DirectorWindows should have non null openGLViews");
		if(window->openGLView == openGLView)
		{
			//openGLView already inserted.  Early out.
			return window;
		}

		if(window->openGLView != nullptr)
			window->openGLView->release(); //end() destroys the window.  Probably don't want that.
		window->openGLView = openGLView;
	}
	else
	{
		_windowList.emplace_back(openGLView);
		window = &(_windowList.back());
		_windowMap[windowKey] = window;
	}

	openGLView->retain();

	//+1 because the map also contains the main window.
	CCASSERT(_windowMap.size() == _windowList.size() + 1, "list and map are out of sync");

	return window;
}

bool ContextManager::setContextAndLock(WindowKey windowKey)
{
	CCASSERT(!_isLocked, "context is already locked");
	if(_isLocked)
		return false;
	if(makeWindowCurrent(windowKey))
		_isLocked = true;
	return _isLocked;
}

bool ContextManager::unlock()
{
	CCASSERT(_isLocked, "context is already unlocked");
	if(!_isLocked)
		return false;
	detachCurrentWindow();
	_isLocked = false;
	return true;
}

bool ContextManager::isLocked()
{
	return _isLocked;
}

DirectorWindow* ContextManager::getWindow(WindowKey windowKey) const
{
	if(windowKey == WindowKey::NULLKEY)
	{
		CCASSERT(false, "returning null, windowkey is null");
		return nullptr;
	}
	else
	{
		auto iter = _windowMap.find(windowKey);
		if(iter != _windowMap.end())
		{
			return iter->second;
		}
	}

	return nullptr;
}

DirectorWindow* ContextManager::getCurrentWindow() const
{
	CCASSERT(_isLocked, "must set context and lock before calling this.  In general, this is only done while inside the update loop.");
	CCASSERT(_currentWindow, "lock is true, so _currentWindow should not be null");
	return _currentWindow;
}

DirectorWindow* ContextManager::getMainWindow()
{
	return _mainWindow;
}

//TODO: (day) it will be cleaner to create our own iterator here
//that locks the context as it iterates the windows.
ContextManager::tWindowMap::iterator ContextManager::begin()
{
	CCASSERT(!_isLocked, "no context must be set");
	return _windowMap.begin();
}

ContextManager::tWindowMap::iterator ContextManager::end()
{
	CCASSERT(!_isLocked, "no context must be set");
	return _windowMap.end();
}

void ContextManager::removeIf( bool(*pred)(const DirectorWindow& window) )
{
	CCASSERT(!_isLocked, "no context must be set");

	for(auto iter = _windowMap.begin(); iter != _windowMap.end(); )
	{
		CCASSERT(iter->second != nullptr, "directorWindow pointer should never be null in map");
		if(pred(*(iter->second)))
			_windowMap.erase(iter++);
		else
			++iter;
	}

	if(pred(*_mainWindow))
	{
		deleteMainWindowPointer();
	}
	else
		_windowList.remove_if(pred);
}

void ContextManager::clear()
{
	CCASSERT(!_isLocked, "no context must be set");
	_windowMap.clear();
	_windowList.clear();
	deleteMainWindowPointer();
}

unsigned int ContextManager::getNumContexts()
{
	if(_mainWindow == nullptr)
	{
		CCASSERT(_windowList.size() == 0, "main is null but we have non-main GLViews");
		return 0;
	}

	return _windowList.size() + 1;
}

NS_CC_END
