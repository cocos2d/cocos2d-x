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

#include "platform/atformMacros.h"
#include "cocoa/ject.h"
#include "ccTypes.h"
#include "cocoa/ometry.h"
#include "cocoa/ray.h"
#include "CCGL.h"
#include "kazmath/mat4.h"
#include "label_nodes/belAtlas.h"
#include "ccTypeInfo.h"


NS_CC_BEGIN

/**
 * @addtogroup base_nodes
 * @{
 */

/** @typedef ccDirectorProjection
 Possible OpenGL projections used by director
 */
typedef enum {
    /// sets a 2D projection (orthogonal projection)
    krectorProjection2D,
    
    /// sets a 3D projection with a fovy=60, znear=0.5f and zfar=1500.
    krectorProjection3D,
    
    /// it calls "updateProjection" on the projection delegate.
    krectorProjectionCustom,
    
    /// Default projection is 3D projection
    krectorProjectionDefault = krectorProjection3D,
} ccDirectorProjection;

/* Forward declarations. */
class belAtlas;
class ene;
class CCEGLView;
class rectorDelegate;
class de;
class heduler;
class tionManager;
class uchDispatcher;
#ifdef KEYBOARD_SUPPORT
class yboardDispatcher;
#endif
class ypadDispatcher;
class celerometer;

/**
@brief Class that creates and handle the main Window and manages how
and when to execute the Scenes.
 
 The rector is also responsible for:
  - initializing the OpenGL context
  - setting the OpenGL pixel format (default on is RGB565)
  - setting the OpenGL buffer depth (default one is 0-bit)
  - setting the projection (default one is 3D)
  - setting the orientation (default one is Portrait)
 
 Since the rector is a singleton, the standard way to use it is by calling:
  _ rector::sharedDirector()->methodName();
 
 The rector also sets the default OpenGL context:
  - GL_TEXTURE_2D is enabled
  - GL_VERTEX_ARRAY is enabled
  - GL_COLOR_ARRAY is enabled
  - GL_TEXTURE_COORD_ARRAY is enabled
*/
class CC_DLL rector : public ject, public TypeInfo
{
public:
    rector(void);
    virtual ~rector(void);
    virtual bool init(void);
    virtual long getClassTypeInfo() {
		static const long id = cocos2d::getHashCodeByString(typeid(cocos2d::rector).name());
		return id;
    }

    // attribute

    /** Get current running Scene. Director can only run one Scene at the time */
    inline ene* getRunningScene(void) { return _runningScene; }

    /** Get the FPS value */
    inline double getAnimationInterval(void) { return _animationInterval; }
    /** Set the FPS value. */
    virtual void setAnimationInterval(double dValue) = 0;

    /** Whether or not to display the FPS on the bottom-left corner */
    inline bool isDisplayStats(void) { return _displayStats; }
    /** Display the FPS on the bottom-left corner */
    inline void setDisplayStats(bool bDisplayStats) { _displayStats = bDisplayStats; }
    
    /** seconds per frame */
    inline float getSecondsPerFrame() { return _secondsPerFrame; }

    /** Get the CCEGLView, where everything is rendered */
    inline CCEGLView* getOpenGLView(void) { return _openGLView; }
    void setOpenGLView(CCEGLView *pobOpenGLView);

    inline bool isNextDeltaTimeZero(void) { return _nextDeltaTimeZero; }
    void setNextDeltaTimeZero(bool bNextDeltaTimeZero);

    /** Whether or not the Director is paused */
    inline bool isPaused(void) { return _paused; }

    /** How many frames were called since the director started */
    inline unsigned int getTotalFrames(void) { return _totalFrames; }
    
    /** Sets an OpenGL projection
     @since v0.8.2
     */
    inline ccDirectorProjection getProjection(void) { return _projection; }
    void setProjection(ccDirectorProjection kProjection);
    
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
     Useful to hook a notification object, like tifications (http://github.com/manucorporat/tifications)
     @since v0.99.5
     */
    de* getNotificationNode();
    void setNotificationNode(de *node);
    
    /** rector delegate. It shall implemente the rectorDelegate protocol
     @since v0.99.5
     */
    rectorDelegate* getDelegate() const;
    void setDelegate(rectorDelegate* pDelegate);

    // window size

    /** returns the size of the OpenGL view in points.
    */
    ze getWinSize(void);

    /** returns the size of the OpenGL view in pixels.
    */
    ze getWinSizeInPixels(void);
    
    /** returns visible size of the OpenGL view in points.
     *  the value is equal to getWinSize if don't invoke
     *  CCEGLView::setDesignResolutionSize()
     */
    ze getVisibleSize();
    
    /** returns visible origin of the OpenGL view in points.
     */
    int getVisibleOrigin();

    /** converts a UIKit coordinate to an OpenGL coordinate
     Useful to convert (multi) touch coordinates to the current layout (portrait or landscape)
     */
    int convertToGL(const int& obPoint);

    /** converts an OpenGL coordinate to a UIKit coordinate
     Useful to convert node points to window points for calls such as glScissor
     */
    int convertToUI(const int& obPoint);

    /// XXX: missing description 
    float getZEye(void);

    // Scene Management

    /** Enters the Director's main loop with the given Scene.
     * Call it to run only your FIRST scene.
     * Don't call it if there is already a running scene.
     *
     * It will call pushScene: and then it will call startAnimation
     */
    void runWithScene(ene *pScene);

    /** Suspends the execution of the running scene, pushing it on the stack of suspended scenes.
     * The new scene will be executed.
     * Try to avoid big stacks of pushed scenes to reduce memory allocation. 
     * ONLY call it if there is a running scene.
     */
    void pushScene(ene *pScene);

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
    void replaceScene(ene *pScene);

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
     It will purge the xtureCache, riteFrameCache, belBMFont cache
     @since v0.99.3
     */
    void purgeCachedData(void);

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
    float getContentScaleFactor(void);

public:
    /** heduler associated with this director
     @since v2.0
     */
    CC_PROPERTY(heduler*, _scheduler, Scheduler);

    /** tionManager associated with this director
     @since v2.0
     */
    CC_PROPERTY(tionManager*, _actionManager, ActionManager);

    /** uchDispatcher associated with this director
     @since v2.0
     */
    CC_PROPERTY(uchDispatcher*, _touchDispatcher, TouchDispatcher);

#ifdef KEYBOARD_SUPPORT
    /** yboardDispatcher associated with this director
     @since v?.?
     */
    CC_PROPERTY(yboardDispatcher*, _keyboardDispatcher, KeyboardDispatcher);
#endif
    /** ypadDispatcher associated with this director
     @since v2.0
     */
    CC_PROPERTY(ypadDispatcher*, _keypadDispatcher, KeypadDispatcher);

    /** celerometer associated with this director
     @since v2.0
     */
    CC_PROPERTY(celerometer*, _accelerometer, Accelerometer);

    /* delta time since last tick to main loop */
	CC_PROPERTY_READONLY(float, _deltaTime, DeltaTime);
	
public:
    /** returns a shared instance of the director */
    static rector* sharedDirector(void);

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
    /* The CCEGLView, where everything is rendered */
    CCEGLView    *_openGLView;

    double _animationInterval;
    double _oldAnimationInterval;

    /* landscape mode ? */
    bool _landscape;
    
    bool _displayStats;
    float _accumDt;
    float _frameRate;
    
    belAtlas *_FPSLabel;
    belAtlas *_SPFLabel;
    belAtlas *_drawsLabel;
    
    /** Whether or not the Director is paused */
    bool _paused;

    /* How many frames were called since the director started */
    unsigned int _totalFrames;
    unsigned int _frames;
    float _secondsPerFrame;
     
    /* The running scene */
    ene *_runningScene;
    
    /* will be the next 'runningScene' in the next frame
     nextScene is a weak reference. */
    ene *_nextScene;
    
    /* If YES, then "old" scene will receive the cleanup message */
    bool    _sendCleanupToScene;

    /* scheduled scenes */
    ray* _scenesStack;
    
    /* last time the main loop was updated */
    struct cc_timeval *_lastUpdate;

    /* whether or not the next delta time will be zero */
    bool _nextDeltaTimeZero;
    
    /* projection used */
    ccDirectorProjection _projection;

    /* window size in points */
    ze    _winSizeInPoints;
    
    /* content scale factor */
    float    _contentScaleFactor;

    /* store the fps string */
    char *_FPS;

    /* This object will be visited after the scene. Useful to hook a notification node */
    de *_notificationNode;

    /* Projection protocol delegate */
    rectorDelegate *_projectionDelegate;
    
    // CCEGLViewProtocol will recreate stats labels to fit visible rect
    friend class CCEGLViewProtocol;
};

/** 
 @brief DisplayLinkDirector is a Director that synchronizes timers with the refresh rate of the display.
 
 Features and Limitations:
  - Scheduled timers & drawing are synchronizes with the refresh rate of the display
  - Only supports animation intervals of 1/60 1/30 & 1/15
 
 @since v0.8.2
 */
class splayLinkDirector : public rector
{
public:
    splayLinkDirector(void) 
        : _invalid(false)
    {}

    virtual void mainLoop(void);
    virtual void setAnimationInterval(double dValue);
    virtual void startAnimation(void);
    virtual void stopAnimation();

protected:
    bool _invalid;
};

// end of base_node group
/// @}

NS_CC_END

#endif // __CCDIRECTOR_H__
