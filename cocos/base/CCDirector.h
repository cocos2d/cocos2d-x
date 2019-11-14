/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2010-2013 cocos2d-x.org
 Copyright (c) 2011      Zynga Inc.
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2019 Xiamen Yaji Software Co., Ltd.

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
#pragma once

#include <stack>
#include <thread>
#include <chrono>

#include "platform/CCPlatformMacros.h"
#include "base/CCRef.h"
#include "base/CCVector.h"
#include "2d/CCScene.h"
#include "math/CCMath.h"
#include "platform/CCGLView.h"

NS_CC_BEGIN

/**
 * @addtogroup base
 * @{
 */

/* Forward declarations. */
class LabelAtlas;
//class GLView;
class DirectorDelegate;
class Node;
class Scheduler;
class ActionManager;
class EventDispatcher;
class EventCustom;
class EventListenerCustom;
class TextureCache;
class Renderer;
class Camera;

class Console;

/**
 * @brief Matrix stack type.
 */
enum class MATRIX_STACK_TYPE
{
    /// Model view matrix stack
    MATRIX_STACK_MODELVIEW,
    
    /// projection matrix stack
    MATRIX_STACK_PROJECTION,
    
    /// texture matrix stack
    MATRIX_STACK_TEXTURE
};

/**
 @brief Class that creates and handles the main Window and manages how
 and when to execute the Scenes.
 
 The Director is also responsible for:
 - initializing the OpenGL context
 - setting the OpenGL buffer depth (default one is 0-bit)
 - setting the projection (default one is 3D)
 
 Since the Director is a singleton, the standard way to use it is by calling:
 _ Director::getInstance()->methodName();
 */
class CC_DLL Director : public Ref
{
public:
    /** Director will trigger an event before set next scene. */
    static const char* EVENT_BEFORE_SET_NEXT_SCENE;
    /** Director will trigger an event after set next scene. */
    static const char* EVENT_AFTER_SET_NEXT_SCENE;
    
    /** Director will trigger an event when projection type is changed. */
    static const char* EVENT_PROJECTION_CHANGED;
    /** Director will trigger an event before Schedule::update() is invoked. */
    static const char* EVENT_BEFORE_UPDATE;
    /** Director will trigger an event after Schedule::update() is invoked. */
    static const char* EVENT_AFTER_UPDATE;
    /** Director will trigger an event while resetting Director */
    static const char* EVENT_RESET;
    /** Director will trigger an event after Scene::render() is invoked. */
    static const char* EVENT_AFTER_VISIT;
    /** Director will trigger an event after a scene is drawn, the data is sent to GPU. */
    static const char* EVENT_AFTER_DRAW;
    /** Director will trigger an event before a scene is drawn, right after clear. */
    static const char* EVENT_BEFORE_DRAW;

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
    
    /** 
     * Returns a shared instance of the director. 
     * @js _getInstance
     */
    static Director* getInstance();

    /**
     * @js ctor
     */
    Director();
    
    /**
     * @js NA
     * @lua NA
     */
    ~Director();
    bool init();

    // attribute

    /** Gets current running Scene. Director can only run one Scene at a time. */
    Scene* getRunningScene() { return _runningScene; }

    /** Gets the FPS value. */
    float getAnimationInterval() { return _animationInterval; }
    /** Sets the FPS value. FPS = 1/interval. */
    void setAnimationInterval(float interval);

    /** Whether or not displaying the FPS on the bottom-left corner of the screen. */
    bool isDisplayStats() { return _displayStats; }
    /** Display the FPS on the bottom-left corner of the screen. */
    void setDisplayStats(bool displayStats) { _displayStats = displayStats; }
    
    /** Get seconds per frame. */
    float getSecondsPerFrame() { return _secondsPerFrame; }

    /** 
     * Get the GLView.
     * @lua NA
     */
    GLView* getOpenGLView() { return _openGLView; }
    /** 
     * Sets the GLView. 
     * @lua NA
     */
    void setOpenGLView(GLView *openGLView);

    /*
     * Gets singleton of TextureCache.
     * @js NA
     */
    TextureCache* getTextureCache() const;

    /** Whether or not `_nextDeltaTimeZero` is set to 0. */
    bool isNextDeltaTimeZero() { return _nextDeltaTimeZero; }
    /** 
     * Sets the delta time between current frame and next frame is 0.
     * This value will be used in Schedule, and will affect all functions that are using frame delta time, such as Actions.
     * This value will take effect only one time.
     */
    void setNextDeltaTimeZero(bool nextDeltaTimeZero);

    /** Whether or not the Director is paused. */
    bool isPaused() { return _paused; }

    /** How many frames were called since the director started */
    unsigned int getTotalFrames() { return _totalFrames; }
    
    /** Gets an OpenGL projection.
     * @since v0.8.2
     * @lua NA
     */
    Projection getProjection() { return _projection; }
    /** Sets OpenGL projection. */
    void setProjection(Projection projection);
    
    /** Sets the glViewport.*/
    void setViewport();
    
    /** Whether or not the replaced scene will receive the cleanup message.
     * If the new scene is pushed, then the old scene won't receive the "cleanup" message.
     * If the new scene replaces the old one, the it will receive the "cleanup" message.
     * @since v0.99.0
     */
    bool isSendCleanupToScene() { return _sendCleanupToScene; }

    /** This object will be visited after the main scene is visited.
     * This object MUST implement the "visit" function.
     * Useful to hook a notification object, like Notifications (http://github.com/manucorporat/CCNotifications)
     * @since v0.99.5
     */
    Node* getNotificationNode() const { return _notificationNode; }
    /** 
     * Sets the notification node.
     * @see Director::getNotificationNode()
     */
    void setNotificationNode(Node *node);
    
    // window size

    /** Returns the size of the OpenGL view in points. */
    const Size& getWinSize() const;

    /** Returns the size of the OpenGL view in pixels. */
    Size getWinSizeInPixels() const;
    
    /** 
     * Returns visible size of the OpenGL view in points.
     * The value is equal to `Director::getWinSize()` if don't invoke `GLView::setDesignResolutionSize()`.
     */
    Size getVisibleSize() const;
    
    /** Returns visible origin coordinate of the OpenGL view in points. */
    Vec2 getVisibleOrigin() const;

    /**
     * Returns safe area rectangle of the OpenGL view in points.
     */
    Rect getSafeAreaRect() const;

    /**
     * Converts a screen coordinate to an OpenGL coordinate.
     * Useful to convert (multi) touch coordinates to the current layout (portrait or landscape).
     */
    Vec2 convertToGL(const Vec2& point);

    /** 
     * Converts an OpenGL coordinate to a screen coordinate.
     * Useful to convert node points to window points for calls such as glScissor.
     */
    Vec2 convertToUI(const Vec2& point);

    /** 
     * Gets the distance between camera and near clipping frame.
     * It is correct for default camera that near clipping frame is same as the screen.
     */
    float getZEye() const;

    // Scene Management

    /** 
     * Enters the Director's main loop with the given Scene.
     * Call it to run only your FIRST scene.
     * Don't call it if there is already a running scene.
     *
     * It will call pushScene: and then it will call startAnimation
     * @js NA
     */
    void runWithScene(Scene *scene);

    /** 
     * Suspends the execution of the running scene, pushing it on the stack of suspended scenes.
     * The new scene will be executed.
     * Try to avoid big stacks of pushed scenes to reduce memory allocation. 
     * ONLY call it if there is a running scene.
     */
    void pushScene(Scene *scene);

    /** 
     * Pops out a scene from the stack.
     * This scene will replace the running one.
     * The running scene will be deleted. If there are no more scenes in the stack the execution is terminated.
     * ONLY call it if there is a running scene.
     */
    void popScene();

    /** 
     * Pops out all scenes from the stack until the root scene in the queue.
     * This scene will replace the running one.
     * Internally it will call `popToSceneStackLevel(1)`.
     */
    void popToRootScene();

    /** Pops out all scenes from the stack until it reaches `level`.
     If level is 0, it will end the director.
     If level is 1, it will pop all scenes until it reaches to root scene.
     If level is <= than the current stack level, it won't do anything.
     */
 	void popToSceneStackLevel(int level);

    /** Replaces the running scene with a new one. The running scene is terminated.
     * ONLY call it if there is a running scene.
     * @js NA
     */
    void replaceScene(Scene *scene);

    /** Ends the execution, releases the running scene.
     * @lua endToLua
     */
    void end();

    /** Pauses the running scene.
     * The running scene will be _drawed_ but all scheduled timers will be paused.
     * While paused, the draw rate will be 4 FPS to reduce CPU consumption.
     */
    void pause();

    /** Resumes the paused scene.
     * The scheduled timers will be activated again.
     * The "delta time" will be 0 (as if the game wasn't paused).
     */
    void resume();
    
    /*
     * Restart the director. 
     * @js NA
     */
    void restart();

    /** Stops the animation. Nothing will be drawn. The main loop won't be triggered anymore.
     * If you don't want to pause your animation call [pause] instead.
     */
    void stopAnimation();

    /** The main loop is triggered again.
     * Call this function only if [stopAnimation] was called earlier.
     * @warning Don't call this function to start the main loop. To run the main loop call runWithScene.
     */
    void startAnimation();

    /** Draw the scene.
     * This method is called every frame. Don't call it manually.
     */
    void drawScene();

    // Memory Helper

    /** Removes all cocos2d cached data.
     * It will purge the TextureCache, SpriteFrameCache, LabelBMFont cache
     * @since v0.99.3
     */
    void purgeCachedData();

	/** Sets the default values based on the Configuration info. */
    void setDefaultValues();

    // OpenGL Helper

    /** Sets the OpenGL default values.
     * It will enable alpha blending, disable depth test.
     * @js NA
     */
    void setGLDefaultValues();
    
    /** Sets clear values for the color buffers,
     * value range of each element is [0.0, 1.0].
     * @js NA
     */
    void setClearColor(const Color4F& clearColor);

    void mainLoop();
    /** Invoke main loop with delta time. Then `calculateDeltaTime` can just use the delta time directly.
     * The delta time paseed may include vsync time. See issue #17806
     * @since 3.16
     */
    void mainLoop(float dt);

    /** The size in pixels of the surface. It could be different than the screen size.
     * High-res devices might have a higher surface size than the screen size.
     * Only available when compiled using SDK >= 4.0.
     * @since v0.99.4
     */
    void setContentScaleFactor(float scaleFactor);
    /**
     * Gets content scale factor.
     * @see Director::setContentScaleFactor()
     */
    float getContentScaleFactor() const { return _contentScaleFactor; }

    /** Gets the Scheduler associated with this director.
     * @since v2.0
     */
    Scheduler* getScheduler() const { return _scheduler; }
    
    /** Sets the Scheduler associated with this director.
     * @since v2.0
     */
    void setScheduler(Scheduler* scheduler);

    /** Gets the ActionManager associated with this director.
     * @since v2.0
     */
    ActionManager* getActionManager() const { return _actionManager; }
    
    /** Sets the ActionManager associated with this director.
     * @since v2.0
     */
    void setActionManager(ActionManager* actionManager);
    
    /** Gets the EventDispatcher associated with this director.
     * @since v3.0
     * @js NA
     */
    EventDispatcher* getEventDispatcher() const { return _eventDispatcher; }
    
    /** Sets the EventDispatcher associated with this director.
     * @since v3.0
     * @js NA
     */
    void setEventDispatcher(EventDispatcher* dispatcher);

    /** Returns the Renderer associated with this director.
     * @since v3.0
     */
    Renderer* getRenderer() const { return _renderer; }

    /** Returns the Console associated with this director.
     * @since v3.0
     * @js NA
     */
    Console* getConsole() const { return _console; }

    /* Gets delta time since last tick to main loop. */
	float getDeltaTime() const;
    
    /**
     *  Gets Frame Rate.
     * @js NA
     */
    float getFrameRate() const { return _frameRate; }

    /** 
     * Clones a specified type matrix and put it to the top of specified type of matrix stack.
     * @js NA
     */
    void pushMatrix(MATRIX_STACK_TYPE type);

    /** Pops the top matrix of the specified type of matrix stack.
     * @js NA
     */
    void popMatrix(MATRIX_STACK_TYPE type);

    /** Adds an identity matrix to the top of specified type of matrix stack.
     * @js NA
     */
    void loadIdentityMatrix(MATRIX_STACK_TYPE type);

    /**
     * Adds a matrix to the top of specified type of matrix stack.
     * 
     * @param type Matrix type.
     * @param mat The matrix that to be added.
     * @js NA
     */
    void loadMatrix(MATRIX_STACK_TYPE type, const Mat4& mat);

    /**
     * Multiplies a matrix to the top of specified type of matrix stack.
     *
     * @param type Matrix type.
     * @param mat The matrix that to be multiplied.
     * @js NA
     */
    void multiplyMatrix(MATRIX_STACK_TYPE type, const Mat4& mat);

    /**
     * Gets the top matrix of specified type of matrix stack.
     * @js NA
     */
    const Mat4& getMatrix(MATRIX_STACK_TYPE type) const;

    /**
     * Clear all types of matrix stack, and add identity matrix to these matrix stacks.
     * @js NA
     */
    void resetMatrixStack();

    /**
     * returns the cocos2d thread id.
     Useful to know if certain code is already running on the cocos2d thread
     */
    const std::thread::id& getCocos2dThreadId() const { return _cocos2d_thread_id; }

    /**
     * returns whether or not the Director is in a valid state
     */
    bool isValid() const { return !_invalid; }

protected:
    void reset();
    

    virtual void startAnimation(SetIntervalReason reason);
    virtual void setAnimationInterval(float interval, SetIntervalReason reason);

    void purgeDirector();
    bool _purgeDirectorInNextLoop = false; // this flag will be set to true in end()
    
    void restartDirector();
    bool _restartDirectorInNextLoop = false; // this flag will be set to true in restart()
    
    void setNextScene();
    
    void updateFrameRate();
#if !CC_STRIP_FPS
    void showStats();
    void createStatsLabel();
    void calculateMPF();
    void getFPSImageData(unsigned char** datapointer, ssize_t* length);
#endif
    
    /** calculates delta time since last time it was called */    
    void calculateDeltaTime();

    //textureCache creation or release
    void initTextureCache();
    void destroyTextureCache();

    void initMatrixStack();

    std::stack<Mat4> _modelViewMatrixStack;
    std::stack<Mat4> _textureMatrixStack;
    std::stack<Mat4> _projectionMatrixStack;

    /** Scheduler associated with this director
     @since v2.0
     */
    Scheduler *_scheduler = nullptr;
    
    /** ActionManager associated with this director
     @since v2.0
     */
    ActionManager *_actionManager = nullptr;
    
    /** EventDispatcher associated with this director
     @since v3.0
     */
    EventDispatcher* _eventDispatcher = nullptr;
    EventCustom* _eventProjectionChanged = nullptr;
    EventCustom* _eventBeforeDraw =nullptr; 
    EventCustom* _eventAfterDraw = nullptr;
    EventCustom* _eventAfterVisit = nullptr;
    EventCustom* _eventBeforeUpdate = nullptr;
    EventCustom* _eventAfterUpdate = nullptr;
    EventCustom* _eventResetDirector = nullptr;
    EventCustom* _beforeSetNextScene = nullptr;
    EventCustom* _afterSetNextScene = nullptr;
        
    /* delta time since last tick to main loop */
	float _deltaTime = 0.0f;
    bool _deltaTimePassedByCaller = false;
    
    /* The _openGLView, where everything is rendered, GLView is a abstract class,cocos2d-x provide GLViewImpl
     which inherit from it as default renderer context,you can have your own by inherit from it*/
    GLView *_openGLView = nullptr;

    //texture cache belongs to this director
    TextureCache *_textureCache = nullptr;

    float _animationInterval = 0.0f;
    float _oldAnimationInterval = 0.0f;
    
    bool _displayStats = false;
    float _accumDt = 0.0f;
    float _frameRate = 0.0f;
    
    LabelAtlas *_FPSLabel = nullptr;
    LabelAtlas *_drawnBatchesLabel = nullptr;
    LabelAtlas *_drawnVerticesLabel = nullptr;
    
    /** Whether or not the Director is paused */
    bool _paused = false;

    /* How many frames were called since the director started */
    unsigned int _totalFrames = 0;
    unsigned int _frames = 0;
    float _secondsPerFrame = 1.f;
    
    /* The running scene */
    Scene *_runningScene = nullptr;
    
    /* will be the next 'runningScene' in the next frame
     nextScene is a weak reference. */
    Scene *_nextScene = nullptr;
    
    /* If true, then "old" scene will receive the cleanup message */
    bool _sendCleanupToScene = false;

    /* scheduled scenes */
    Vector<Scene*> _scenesStack;
    
    /* last time the main loop was updated */
    std::chrono::steady_clock::time_point _lastUpdate;

    /* whether or not the next delta time will be zero */
    bool _nextDeltaTimeZero = false;
    
    /* projection used */
    Projection _projection = Projection::DEFAULT;

    /* window size in points */
    Size _winSizeInPoints = Size::ZERO;
    
    /* content scale factor */
    float _contentScaleFactor = 1.0f;

    /* This object will be visited after the scene. Useful to hook a notification node */
    Node *_notificationNode = nullptr;

    /* Renderer for the Director */
    Renderer *_renderer = nullptr;

    Color4F _clearColor = {0, 0, 0, 1};

    /* Console for the director */
    Console *_console = nullptr;

    bool _isStatusLabelUpdated = true;

    /* cocos2d thread id */
    std::thread::id _cocos2d_thread_id;

    /* whether or not the director is in a valid state */
    bool _invalid = false;

    // GLView will recreate stats labels to fit visible rect
    friend class GLView;
};

// end of base group
/** @} */

NS_CC_END
