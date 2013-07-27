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

#ifndef __CCDIRECTOR_H__
#define __CCDIRECTOR_H__

#include "platform/CCPlatformMacros.h"

#include "cocoa/CCObject.h"
#include "ccTypes.h"
#include "cocoa/CCGeometry.h"
#include "cocoa/CCArray.h"
#include "CCGL.h"
#include "kazmath/mat4.h"
#include "label_nodes/CCLabelAtlas.h"
#include "ccTypeInfo.h"


NS_CC_BEGIN

/**
 * @addtogroup base_nodes
 * @{
 */

/* Forward declarations. */
class LabelAtlas;
class Scene;
class EGLView;
class DirectorDelegate;
class Node;
class Scheduler;
class ActionManager;
class TouchDispatcher;
class KeyboardDispatcher;
class KeypadDispatcher;
class Accelerometer;

/**
@brief Class that creates and handle the main Window and manages how
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
class CC_DLL Director : public Object, public TypeInfo
{
public:
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

    Director(void);
    virtual ~Director(void);
    virtual bool init(void);
    virtual long getClassTypeInfo() {
		static const long id = cocos2d::getHashCodeByString(typeid(cocos2d::Director).name());
		return id;
    }

    // attribute

    /** Get current running Scene. Director can only run one Scene at the time */
    inline Scene* getRunningScene(void) { return _runningScene; }

    /** Get the FPS value */
    inline double getAnimationInterval(void) { return _animationInterval; }
    /** Set the FPS value. */
    virtual void setAnimationInterval(double dValue) = 0;

    /** Whether or not to display the FPS on the bottom-left corner */
    inline bool isDisplayStats(void) { return _displayStats; }
    /** Display the FPS on the bottom-left corner */
    inline void setDisplayStats(bool displayStats) { _displayStats = displayStats; }
    
    /** seconds per frame */
    inline float getSecondsPerFrame() { return _secondsPerFrame; }

    /** Get the EGLView, where everything is rendered */
    inline EGLView* getOpenGLView(void) { return _openGLView; }
    void setOpenGLView(EGLView *pobOpenGLView);

    inline bool isNextDeltaTimeZero(void) { return _nextDeltaTimeZero; }
    void setNextDeltaTimeZero(bool nextDeltaTimeZero);

    /** Whether or not the Director is paused */
    inline bool isPaused(void) { return _paused; }

    /** How many frames were called since the director started */
    inline unsigned int getTotalFrames(void) { return _totalFrames; }
    
    /** Sets an OpenGL projection
     @since v0.8.2
     */
    inline Projection getProjection(void) { return _projection; }
    void setProjection(Projection projection);
    
    /** Sets the glViewport*/
    void setViewport();

    /** How many frames were called since the director started */
    
    
    /** Whether or not the replaced scene will receive the cleanup message.
     If the new scene is pushed, then the old scene won't receive the "cleanup" message.
     If the new scene replaces the old one, the it will receive the "cleanup" message.
     @since v0.99.0
     */
    inline bool isSendCleanupToScene(void) { return _sendCleanupToScene; }

    /** This object will be visited after the main scene is visited.
     This object MUST implement the "visit" selector.
     Useful to hook a notification object, like Notifications (http://github.com/manucorporat/CCNotifications)
     @since v0.99.5
     */
    Node* getNotificationNode();
    void setNotificationNode(Node *node);
    
    /** Director delegate. It shall implemente the DirectorDelegate protocol
     @since v0.99.5
     */
    DirectorDelegate* getDelegate() const;
    void setDelegate(DirectorDelegate* pDelegate);

    // window size

    /** returns the size of the OpenGL view in points.
    */
    const Size& getWinSize(void) const;

    /** returns the size of the OpenGL view in pixels.
    */
    Size getWinSizeInPixels(void) const;
    
    /** returns visible size of the OpenGL view in points.
     *  the value is equal to getWinSize if don't invoke
     *  EGLView::setDesignResolutionSize()
     */
    Size getVisibleSize() const;
    
    /** returns visible origin of the OpenGL view in points.
     */
    Point getVisibleOrigin() const;

    /** converts a UIKit coordinate to an OpenGL coordinate
     Useful to convert (multi) touch coordinates to the current layout (portrait or landscape)
     */
    Point convertToGL(const Point& point);

    /** converts an OpenGL coordinate to a UIKit coordinate
     Useful to convert node points to window points for calls such as glScissor
     */
    Point convertToUI(const Point& point);

    /// XXX: missing description 
    float getZEye(void) const;

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

    /** Pops out a scene from the queue.
     * This scene will replace the running one.
     * The running scene will be deleted. If there are no more scenes in the stack the execution is terminated.
     * ONLY call it if there is a running scene.
     */
    void popScene(void);

    /** Pops out all scenes from the queue until the root scene in the queue.
     * This scene will replace the running one.
     * Internally it will call `popToSceneStackLevel(1)`
     */
    void popToRootScene(void);

    /** Pops out all scenes from the queue until it reaches `level`.
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
     */
    void end(void);

    /** Pauses the running scene.
     The running scene will be _drawed_ but all scheduled timers will be paused
     While paused, the draw rate will be 4 FPS to reduce CPU consumption
     */
    void pause(void);

    /** Resumes the paused scene
     The scheduled timers will be activated again.
     The "delta time" will be 0 (as if the game wasn't paused)
     */
    void resume(void);

    /** Stops the animation. Nothing will be drawn. The main loop won't be triggered anymore.
     If you don't want to pause your animation call [pause] instead.
     */
    virtual void stopAnimation(void) = 0;

    /** The main loop is triggered again.
     Call this function only if [stopAnimation] was called earlier
     @warning Don't call this function to start the main loop. To run the main loop call runWithScene
     */
    virtual void startAnimation(void) = 0;

    /** Draw the scene.
    This method is called every frame. Don't call it manually.
    */
    void drawScene(void);

    // Memory Helper

    /** Removes cached all cocos2d cached data.
     It will purge the TextureCache, SpriteFrameCache, LabelBMFont cache
     @since v0.99.3
     */
    void purgeCachedData(void);

	/** sets the default values based on the Configuration info */
    void setDefaultValues(void);

    // OpenGL Helper

    /** sets the OpenGL default values */
    void setGLDefaultValues(void);

    /** enables/disables OpenGL alpha blending */
    void setAlphaBlending(bool bOn);

    /** enables/disables OpenGL depth test */
    void setDepthTest(bool bOn);

    virtual void mainLoop(void) = 0;

    /** The size in pixels of the surface. It could be different than the screen size.
    High-res devices might have a higher surface size than the screen size.
    Only available when compiled using SDK >= 4.0.
    @since v0.99.4
    */
    void setContentScaleFactor(float scaleFactor);
    float getContentScaleFactor(void) const;

public:
    /** Gets the Scheduler associated with this director
     @since v2.0
     */
    Scheduler* getScheduler() const;
    
    /** Sets the Scheduler associated with this director
     @since v2.0
     */
    void setScheduler(Scheduler* scheduler);

    /** Gets the ActionManager associated with this director
     @since v2.0
     */
    ActionManager* getActionManager() const;
    
    /** Sets the ActionManager associated with this director
     @since v2.0
     */
    void setActionManager(ActionManager* actionManager);
    
    /** Gets the TouchDispatcher associated with this director
     @since v2.0
     */
    TouchDispatcher* getTouchDispatcher() const;
    
    /** Sets the TouchDispatcher associated with this director
     @since v2.0
     */
    void setTouchDispatcher(TouchDispatcher* touchDispatcher);

    /** Gets the KeyboardDispatcher associated with this director
     @note Supported on Mac and Linux only now.
     @since v3.0
     */
    KeyboardDispatcher* getKeyboardDispatcher() const;

    /** Sets the KeyboardDispatcher associated with this director
     @note Supported on Mac and Linux only now.
     @since v3.0
     */
    void setKeyboardDispatcher(KeyboardDispatcher* keyboardDispatcher);
    
    /** Gets the KeypadDispatcher associated with this director
     @since v2.0
     */
    KeypadDispatcher* getKeypadDispatcher() const;

    /** Sets the KeypadDispatcher associated with this director
     @since v2.0
     */
    void setKeypadDispatcher(KeypadDispatcher* keypadDispatcher);
    
    /** Gets Accelerometer associated with this director
     @since v2.0
     */
    Accelerometer* getAccelerometer() const;
    
    /** Sets Accelerometer associated with this director
     @since v2.0
     */
    void setAccelerometer(Accelerometer* acc);

    /* Gets delta time since last tick to main loop */
	float getDeltaTime() const;

protected:
    void purgeDirector();
    bool _purgeDirecotorInNextLoop; // this flag will be set to true in end()
    
    void setNextScene(void);
    
    void showStats();
    void createStatsLabel();
    void calculateMPF();
    void getFPSImageData(unsigned char** datapointer, unsigned int* length);
    
    /** calculates delta time since last time it was called */    
    void calculateDeltaTime();

protected:
    /** Scheduler associated with this director
     @since v2.0
     */
    Scheduler* _scheduler;
    
    /** ActionManager associated with this director
     @since v2.0
     */
    ActionManager* _actionManager;
    
    /** TouchDispatcher associated with this director
     @since v2.0
     */
    TouchDispatcher* _touchDispatcher;
    
    /** KeyboardDispatcher associated with this director
     @note Supported on Mac and Linux only now.
     @since v3.0
     */
    KeyboardDispatcher* _keyboardDispatcher;
    
    /** KeypadDispatcher associated with this director
     @since v2.0
     */
    KeypadDispatcher* _keypadDispatcher;
    
    /** Accelerometer associated with this director
     @since v2.0
     */
    Accelerometer* _accelerometer;
    
    /* delta time since last tick to main loop */
	float _deltaTime;
    
    /* The EGLView, where everything is rendered */
    EGLView    *_openGLView;

    double _animationInterval;
    double _oldAnimationInterval;

    /* landscape mode ? */
    bool _landscape;
    
    bool _displayStats;
    float _accumDt;
    float _frameRate;
    
    LabelAtlas *_FPSLabel;
    LabelAtlas *_SPFLabel;
    LabelAtlas *_drawsLabel;
    
    /** Whether or not the Director is paused */
    bool _paused;

    /* How many frames were called since the director started */
    unsigned int _totalFrames;
    unsigned int _frames;
    float _secondsPerFrame;
     
    /* The running scene */
    Scene *_runningScene;
    
    /* will be the next 'runningScene' in the next frame
     nextScene is a weak reference. */
    Scene *_nextScene;
    
    /* If YES, then "old" scene will receive the cleanup message */
    bool    _sendCleanupToScene;

    /* scheduled scenes */
    Array* _scenesStack;
    
    /* last time the main loop was updated */
    struct timeval *_lastUpdate;

    /* whether or not the next delta time will be zero */
    bool _nextDeltaTimeZero;
    
    /* projection used */
    Projection _projection;

    /* window size in points */
    Size    _winSizeInPoints;
    
    /* content scale factor */
    float    _contentScaleFactor;

    /* store the fps string */
    char *_FPS;

    /* This object will be visited after the scene. Useful to hook a notification node */
    Node *_notificationNode;

    /* Projection protocol delegate */
    DirectorDelegate *_projectionDelegate;
    
    // EGLViewProtocol will recreate stats labels to fit visible rect
    friend class EGLViewProtocol;
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
    DisplayLinkDirector(void) 
        : _invalid(false)
    {}

    //
    // Overrides
    //
    virtual void mainLoop(void) override;
    virtual void setAnimationInterval(double dValue) override;
    virtual void startAnimation(void) override;
    virtual void stopAnimation() override;

protected:
    bool _invalid;
};

// end of base_node group
/// @}

NS_CC_END

#endif // __CCDIRECTOR_H__
