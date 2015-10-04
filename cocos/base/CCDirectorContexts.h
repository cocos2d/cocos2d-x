#ifndef __CCDIRECTORCONTEXTS_H__
#define __CCDIRECTORCONTEXTS_H__

#include <stack>
#include <list>
#include <set>
#include <unordered_map>

#include "2d/CCScene.h"
#include "base/CCEventDispatcher.h"
#include "base/CCRef.h"
#include "base/CCVector.h"
#include "math/CCMath.h"
#include "platform/CCGL.h"
#include "platform/CCGLView.h"
#include "platform/CCPlatformMacros.h"
#include "platform/CCWindowKey.h"
#include "renderer/CCFrameBuffer.h"

NS_CC_BEGIN

class LabelAtlas;

struct DirectorWindow
{
	/**
     * @brief Possible OpenGL projections used by director
     */
    enum class Projection
    {
        /// Sets a 2D projection (orthogonal projection).
        _2D,
        
        /// Sets a 3D projection with a fovy=60, znear=0.5f and zfar=1500.
        _3D,
        
        /// It calls "updateProjection" on the projection delegate.
        CUSTOM,
        
        /// Default projection is 3D projection.
        DEFAULT = _3D,
    };

	DirectorWindow(GLView *glView);

	~DirectorWindow();

	void reset();
	void resetScheduler();

	void initMatrixStack();

	void createStatsLabel();

	//maybe these two things should be managed elsewhere?
	GLView* openGLView;
	//default frame buffer
	experimental::FrameBuffer* defaultFrameBuffer;
	//user created FBOs.  They can't be shared between contexts.
	std::set<experimental::FrameBuffer*> frameBuffers;

	 /* The running scene */
    Scene* runningScene;
    
    /* will be the next 'runningScene' in the next frame
     nextScene is a weak reference. */
    Scene* nextScene;
    
    /* If true, then "old" scene will receive the cleanup message */
    bool sendCleanupToScene;

    /* scheduled scenes */
    Vector<Scene*> scenesStack;

	/* projection used */
	Projection projection;

	/* content scale factor */
	float contentScaleFactor;

	/* This object will be visited after the scene. Useful to hook a notification node */
	Node* notificationNode;

	/* landscape mode ? */
	bool landscape;

	bool isStatusLabelUpdated;

	LabelAtlas* FPSLabel;
    LabelAtlas* drawnBatchesLabel;
    LabelAtlas* drawnVerticesLabel;

	bool terminate;

	experimental::Viewport defaultViewport;

	//TODO: (day) check if these are always identity at the start of the frame
	//if these are identity at the start of every frame, then we don't need an instance per window.
	//we can just set them back to identity each time we iterate through the window events/update/rendering
	std::stack<Mat4> modelViewMatrixStack;
	std::stack<Mat4> projectionMatrixStack;
	std::stack<Mat4> textureMatrixStack;

	Size cachedLastAbsoluteWindowSize;

	/** EventDispatcher associated with this director window
     @since v3.0
     */
    EventDispatcher* eventDispatcher;

	/** Scheduler associated with this director window
     @since v2.0
     */
    Scheduler* scheduler;
    
    /** ActionManager associated with this director window
     @since v2.0
     */
    ActionManager* actionManager;
};

//prevents and asserts when get and sets are initiated while _isLocked is true.
//this class helps prevent any modifications to current window from outside of the
//update loop
//the MAIN context is the first context in the list.  The director will treat this one as a special context.
//if this context is destroyed, the application is destroyed.
class ContextManager
{
public:
	typedef std::unordered_map<WindowKey, DirectorWindow*, WindowKeyHash, WindowKeyCompare> tWindowMap;

	ContextManager();
	~ContextManager();

	DirectorWindow* createMainView(GLView *openGLView);
	DirectorWindow* addGLView(GLView *openGLView);

	bool setContextAndLock(WindowKey windowKey);

	bool unlock();

	bool isLocked();

	DirectorWindow* getWindow(WindowKey windowKey) const;

	DirectorWindow* getCurrentWindow() const;

	DirectorWindow* getMainWindow();

	//TODO: (day) it will be cleaner to create our own iterator here
	//that locks the context as it iterates the windows.
	tWindowMap::iterator begin();

	tWindowMap::iterator end();

	void removeIf( bool(*pred)(const DirectorWindow& window) );

	void clear();

	unsigned int getNumContexts();

private:
	ContextManager(const ContextManager&);
	ContextManager& operator=(const ContextManager&);

	inline void detachCurrentWindow()
	{
		if(_currentWindow != nullptr)
		{
			_currentWindow->openGLView->detachContext();
			_currentWindow = nullptr;
		}
	}

	inline bool makeWindowCurrent(WindowKey windowKey)
	{
		auto iter = _windowMap.find(windowKey);
		if(iter != _windowMap.end())
		{
			_currentWindow = iter->second;
			CCASSERT(_currentWindow->openGLView != nullptr, "window being set to current doesn't have non-null openGLview");
			_currentWindow->openGLView->makeContextCurrent();
			return true;
		}
		else
		{
			return false;
		}
	}

	//do not call unless you've already removed the pointer from the map.
	inline void deleteMainWindowPointer()
	{
		//need to null it first since there are things that might need to get the _mainWindow when they delete themselves.
		DirectorWindow* tmpWindow = _mainWindow;
		_mainWindow = nullptr;
		delete tmpWindow;
	}

	tWindowMap _windowMap;

	//we store the DirectorWindows in a list because they have memory stability. Adding and removing elements
	//will not invalidate pointers of the other elements.  As long as _windowList and _windowMap update in unison, 
	//all the DirectorWindow pointers will stay valid.  This also allows us to cache a pointer to the currently 
	//active DirectorWindow so we don't have to always go through the map.
	std::list<DirectorWindow> _windowList; 

	bool _isLocked;
	DirectorWindow* _currentWindow;
	DirectorWindow* _mainWindow;
};


NS_CC_END

#endif // __CCDIRECTORCONTEXTS_H__