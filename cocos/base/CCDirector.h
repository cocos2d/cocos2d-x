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

#ifndef __CCDIRECTOR_H__
#define __CCDIRECTOR_H__

#include <stack>

#include "platform/CCPlatformMacros.h"
#include "base/CCRef.h"
#include "base/CCVector.h"
#include "2d/CCScene.h"
#include "math/CCMath.h"
#include "platform/CCGL.h"
#include "platform/CCGLView.h"

NS_CC_BEGIN

/**
 * @addtogroup base_nodes
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
@brief Class that creates and handles the main Window and manages how
and when to execute the Scenes.
 
 The Director is also responsible for:
  - initializing the OpenGL context
  - setting the OpenGL pixel format (default on is RGB565)
  - setting the OpenGL buffer depth (default one is 0-bit)
  - setting the projection (default one is 3D)
  - setting the orientation (default one is Portrait)
 
 Since the Director is a singleton, the standard way to use it is by calling:
  _ Director::getInstance()->methodName();
 
 The Director also sets the default OpenGL context:
  - GL_TEXTURE_2D is enabled
  - GL_VERTEX_ARRAY is enabled
  - GL_COLOR_ARRAY is enabled
  - GL_TEXTURE_COORD_ARRAY is enabled
*/
enum class MATRIX_STACK_TYPE
{
    MATRIX_STACK_MODELVIEW,
    MATRIX_STACK_PROJECTION,
    MATRIX_STACK_TEXTURE
};

class CC_DLL Director : public Ref
{
public:
    static const char *EVENT_PROJECTION_CHANGED;
    static const char* EVENT_AFTER_UPDATE;
    static const char* EVENT_AFTER_VISIT;
    static const char* EVENT_AFTER_DRAW;

    /** @typedef ccDirectorProjection
     Possible OpenGL projections used by director
     */
    enum class Projection
    {
        /// sets a 2D projection (orthogonal projection)
        _2D,
        
        /// sets a 3D projection with a fovy=60, znear=0.5f and zfar=1500.
        _3D,
        
        /// it calls "updateProjection" on the projection delegate.
        CUSTOM,
        
        /// Default projection is 3D projection
        DEFAULT = _3D,
    };
    
    /** returns a shared instance of the director */
    static Director* getInstance();

    /** @deprecated Use getInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static Director* sharedDirector() { return Director::getInstance(); }
    /**
     * @js ctor
     */
    Director(void);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Director();
    virtual bool init();

    // attribute

    /** Get current running Scene. Director can only run one Scene at a time */
    inline Scene* getRunningScene() { return _runningScene; }

    /** Get the FPS value */
    inline double getAnimationInterval() { return _animationInterval; }
    /** Set the FPS value. */
    virtual void setAnimationInterval(double interval) = 0;

    /** Whether or not to display the FPS on the bottom-left corner */
    inline bool isDisplayStats() { return _displayStats; }
    /** Display the FPS on the bottom-left corner */
    inline void setDisplayStats(bool displayStats) { _displayStats = displayStats; }
    
    /** seconds per frame */
    inline float getSecondsPerFrame() { return _secondsPerFrame; }

    /** Get the GLView, where everything is rendered
    * @js NA
    * @lua NA
    */
    inline GLView* getOpenGLView() { return _openGLView; }
    void setOpenGLView(GLView *openGLView);

    TextureCache* getTextureCache() const;

    inline bool isNextDeltaTimeZero() { return _nextDeltaTimeZero; }
    void setNextDeltaTimeZero(bool nextDeltaTimeZero);

    /** Whether or not the Director is paused */
    inline bool isPaused() { return _paused; }

    /** How many frames were called since the director started */
    inline unsigned int getTotalFrames() { return _totalFrames; }
    
    /** Sets an OpenGL projection
     @since v0.8.2
     * @js NA
     * @lua NA
     */
    inline Projection getProjection() { return _projection; }
    void setProjection(Projection projection);
    
    /** Sets the glViewport*/
    void setViewport();

    /** How many frames were called since the director started */
    
    
    /** Whether or not the replaced scene will receive the cleanup message.
     If the new scene is pushed, then the old scene won't receive the "cleanup" message.
     If the new scene replaces the old one, the it will receive the "cleanup" message.
     @since v0.99.0
     */
    inline bool isSendCleanupToScene() { return _sendCleanupToScene; }

    /** This object will be visited after the main scene is visited.
     This object MUST implement the "visit" selector.
     Useful to hook a notification object, like Notifications (http://github.com/manucorporat/CCNotifications)
     @since v0.99.5
     */
    Node* getNotificationNode() const { return _notificationNode; }
    void setNotificationNode(Node *node);
    
    // window size

    /** returns the size of the OpenGL view in points.
    */
    const Size& getWinSize() const;

    /** returns the size of the OpenGL view in pixels.
    */
    Size getWinSizeInPixels() const;
    
    /** returns visible size of the OpenGL view in points.
     *  the value is equal to getWinSize if don't invoke
     *  GLView::setDesignResolutionSize()
     */
    Size getVisibleSize() const;
    
    /** returns visible origin of the OpenGL view in points.
     */
    Vec2 getVisibleOrigin() const;

    /** converts a UIKit coordinate to an OpenGL coordinate
     Useful to convert (multi) touch coordinates to the current layout (portrait or landscape)
     */
    Vec2 convertToGL(const Vec2& point);

    /** converts an OpenGL coordinate to a UIKit coordinate
     Useful to convert node points to window points for calls such as glScissor
     */
    Vec2 convertToUI(const Vec2& point);

    /// FIXME: missing description 
    float getZEye() const;

    // Scene Management

    /** Enters the Director's main loop with the given Scene.
     * Call it to run only your FIRST scene.
     * Don't call it if there is already a running scene.
     *
     * It will call pushScene: and then it will call startAnimation
     */
    void runWithScene(Scene *scene);

    /** Suspends the execution of the running scene, pushing it on the stack of suspended scenes.
     * The new scene will be executed.
     * Try to avoid big stacks of pushed scenes to reduce memory allocation. 
     * ONLY call it if there is a running scene.
     */
    void pushScene(Scene *scene);

    /** Pops out a scene from the stack.
     * This scene will replace the running one.
     * The running scene will be deleted. If there are no more scenes in the stack the execution is terminated.
     * ONLY call it if there is a running scene.
     */
    void popScene();

    /** Pops out all scenes from the stack until the root scene in the queue.
     * This scene will replace the running one.
     * Internally it will call `popToSceneStackLevel(1)`
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
     */
    void replaceScene(Scene *scene);

    /** Ends the execution, releases the running scene.
     It doesn't remove the OpenGL view from its parent. You have to do it manually.
     * @lua endToLua
     */
    void end();

    /** Pauses the running scene.
     The running scene will be _drawed_ but all scheduled timers will be paused
     While paused, the draw rate will be 4 FPS to reduce CPU consumption
     */
    void pause();

    /** Resumes the paused scene
     The scheduled timers will be activated again.
     The "delta time" will be 0 (as if the game wasn't paused)
     */
    void resume();
    
    /** Restart the director
     */
    void restart();

    /** Stops the animation. Nothing will be drawn. The main loop won't be triggered anymore.
     If you don't want to pause your animation call [pause] instead.
     */
    virtual void stopAnimation() = 0;

    /** The main loop is triggered again.
     Call this function only if [stopAnimation] was called earlier
     @warning Don't call this function to start the main loop. To run the main loop call runWithScene
     */
    virtual void startAnimation() = 0;

    /** Draw the scene.
    This method is called every frame. Don't call it manually.
    */
    void drawScene();

    // Memory Helper

    /** Removes all cocos2d cached data.
     It will purge the TextureCache, SpriteFrameCache, LabelBMFont cache
     @since v0.99.3
     */
    void purgeCachedData();

	/** sets the default values based on the Configuration info */
    void setDefaultValues();

    // OpenGL Helper

    /** sets the OpenGL default values */
    void setGLDefaultValues();

    /** enables/disables OpenGL alpha blending */
    void setAlphaBlending(bool on);
    
    /** set clear values for the color buffers, value range of each element is [0.0, 1.0] */
    void setClearColor(const Color4F& clearColor);

    /** enables/disables OpenGL depth test */
    void setDepthTest(bool on);

    virtual void mainLoop() = 0;

    /** The size in pixels of the surface. It could be different than the screen size.
    High-res devices might have a higher surface size than the screen size.
    Only available when compiled using SDK >= 4.0.
    @since v0.99.4
    */
    void setContentScaleFactor(float scaleFactor);
    float getContentScaleFactor() const { return _contentScaleFactor; }

    /** Gets the Scheduler associated with this director
     @since v2.0
     */
    Scheduler* getScheduler() const { return _scheduler; }
    
    /** Sets the Scheduler associated with this director
     @since v2.0
     */
    void setScheduler(Scheduler* scheduler);

    /** Gets the ActionManager associated with this director
     @since v2.0
     */
    ActionManager* getActionManager() const { return _actionManager; }
    
    /** Sets the ActionManager associated with this director
     @since v2.0
     */
    void setActionManager(ActionManager* actionManager);
    
    /** Gets the EventDispatcher associated with this director 
     @since v3.0
     */
    EventDispatcher* getEventDispatcher() const { return _eventDispatcher; }
    
    /** Sets the EventDispatcher associated with this director 
     @since v3.0
     */
    void setEventDispatcher(EventDispatcher* dispatcher);

    /** Returns the Renderer
     @since v3.0
     */
    Renderer* getRenderer() const { return _renderer; }

    /** Returns the Console 
     @since v3.0
     */
    Console* getConsole() const { return _console; }

    /* Gets delta time since last tick to main loop */
	float getDeltaTime() const;
    
    /**
     *  get Frame Rate
     */
    float getFrameRate() const { return _frameRate; }

    void pushMatrix(MATRIX_STACK_TYPE type);
    void popMatrix(MATRIX_STACK_TYPE type);
    void loadIdentityMatrix(MATRIX_STACK_TYPE type);
    void loadMatrix(MATRIX_STACK_TYPE type, const Mat4& mat);
    void multiplyMatrix(MATRIX_STACK_TYPE type, const Mat4& mat);
    const Mat4& getMatrix(MATRIX_STACK_TYPE type);
    void resetMatrixStack();

protected:
    void reset();
    
    void purgeDirector();
    bool _purgeDirectorInNextLoop; // this flag will be set to true in end()
    
    void restartDirector();
    bool _restartDirectorInNextLoop; // this flag will be set to true in restart()
    
    void setNextScene();
    
    void showStats();
    void createStatsLabel();
    void calculateMPF();
    void getFPSImageData(unsigned char** datapointer, ssize_t* length);
    
    /** calculates delta time since last time it was called */    
    void calculateDeltaTime();

    //textureCache creation or release
    void initTextureCache();
    void destroyTextureCache();

    void initMatrixStack();

    std::stack<Mat4> _modelViewMatrixStack;
    std::stack<Mat4> _projectionMatrixStack;
    std::stack<Mat4> _textureMatrixStack;

    /** Scheduler associated with this director
     @since v2.0
     */
    Scheduler *_scheduler;
    
    /** ActionManager associated with this director
     @since v2.0
     */
    ActionManager *_actionManager;
    
    /** EventDispatcher associated with this director
     @since v3.0
     */
    EventDispatcher* _eventDispatcher;
    EventCustom *_eventProjectionChanged, *_eventAfterDraw, *_eventAfterVisit, *_eventAfterUpdate;
        
    /* delta time since last tick to main loop */
	float _deltaTime;
    
    /* The _openGLView, where everything is rendered, GLView is a abstract class,cocos2d-x provide GLViewImpl
     which inherit from it as default renderer context,you can have your own by inherit from it*/
    GLView *_openGLView;

    //texture cache belongs to this director
    TextureCache *_textureCache;

    double _animationInterval;
    double _oldAnimationInterval;

    /* landscape mode ? */
    bool _landscape;
    
    bool _displayStats;
    float _accumDt;
    float _frameRate;
    
    LabelAtlas *_FPSLabel;
    LabelAtlas *_drawnBatchesLabel;
    LabelAtlas *_drawnVerticesLabel;
    
    /** Whether or not the Director is paused */
    bool _paused;

    /* How many frames were called since the director started */
    unsigned int _totalFrames;
    float _secondsPerFrame;
    
    /* The running scene */
    Scene *_runningScene;
    
    /* will be the next 'runningScene' in the next frame
     nextScene is a weak reference. */
    Scene *_nextScene;
    
    /* If true, then "old" scene will receive the cleanup message */
    bool _sendCleanupToScene;

    /* scheduled scenes */
    Vector<Scene*> _scenesStack;
    
    /* last time the main loop was updated */
    struct timeval *_lastUpdate;

    /* whether or not the next delta time will be zero */
    bool _nextDeltaTimeZero;
    
    /* projection used */
    Projection _projection;

    /* window size in points */
    Size _winSizeInPoints;
    
    /* content scale factor */
    float _contentScaleFactor;

    /* This object will be visited after the scene. Useful to hook a notification node */
    Node *_notificationNode;

    /* Renderer for the Director */
    Renderer *_renderer;

    /* Console for the director */
    Console *_console;

    // GLView will recreate stats labels to fit visible rect
    friend class GLView;
};

/** 
 @brief DisplayLinkDirector is a Director that synchronizes timers with the refresh rate of the display.
 
 Features and Limitations:
  - Scheduled timers & drawing are synchronizes with the refresh rate of the display
  - Only supports animation intervals of 1/60 1/30 & 1/15
 
 @since v0.8.2
 */
class DisplayLinkDirector : public Director
{
public:
    DisplayLinkDirector() 
        : _invalid(false)
    {}
    virtual ~DisplayLinkDirector(){}

    //
    // Overrides
    //
    virtual void mainLoop() override;
    virtual void setAnimationInterval(double value) override;
    virtual void startAnimation() override;
    virtual void stopAnimation() override;

protected:
    bool _invalid;
};

// end of base_node group
/// @}

NS_CC_END

#endif // __CCDIRECTOR_H__
