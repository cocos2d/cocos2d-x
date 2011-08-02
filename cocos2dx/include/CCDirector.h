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

#ifndef __CCDIRECTOR_H__
#define __CCDIRECTOR_H__

#include "platform/CCPlatformMacros.h"
#include "CCObject.h"
#include "ccTypes.h"
#include "CCGeometry.h"
#include "CCMutableArray.h"
#include "CCGeometry.h"
#include "CCEGLView.h"
#include "CCGL.h"

namespace   cocos2d {

/** @typedef ccDirectorProjection
 Possible OpenGL projections used by director
 */
typedef enum {
	/// sets a 2D projection (orthogonal projection)
	kCCDirectorProjection2D,
	
	/// sets a 3D projection with a fovy=60, znear=0.5f and zfar=1500.
	kCCDirectorProjection3D,
	
	/// it calls "updateProjection" on the projection delegate.
	kCCDirectorProjectionCustom,
	
	/// Detault projection is 3D projection
	kCCDirectorProjectionDefault = kCCDirectorProjection3D,

	// backward compatibility stuff
	CCDirectorProjection2D = kCCDirectorProjection2D,
	CCDirectorProjection3D = kCCDirectorProjection3D,
	CCDirectorProjectionCustom = kCCDirectorProjectionCustom,
} ccDirectorProjection;

/** @typedef ccDirectorType
 Possible Director Types.
 @since v0.8.2
 */
typedef enum {
	/** Will use a Director that triggers the main loop from an NSTimer object
	 *
	 * Features and Limitations:
	 * - Integrates OK with UIKit objects
	 * - It the slowest director
	 * - The interval update is customizable from 1 to 60
	 */
	kCCDirectorTypeNSTimer,
	
	/** will use a Director that triggers the main loop from a custom main loop.
	 *
	 * Features and Limitations:
	 * - Faster than NSTimer Director
	 * - It doesn't integrate well with UIKit objects
	 * - The interval update can't be customizable
	 */
	kCCDirectorTypeMainLoop,
	
	/** Will use a Director that triggers the main loop from a thread, but the main loop will be executed on the main thread.
	 *
	 * Features and Limitations:
	 * - Faster than NSTimer Director
	 * - It doesn't integrate well with UIKit objects
	 * - The interval update can't be customizable
	 */
	kCCDirectorTypeThreadMainLoop,
	
	/** Will use a Director that synchronizes timers with the refresh rate of the display.
	 *
	 * Features and Limitations:
	 * - Faster than NSTimer Director
	 * - Only available on 3.1+
	 * - Scheduled timers & drawing are synchronizes with the refresh rate of the display
	 * - Integrates OK with UIKit objects
	 * - The interval update can be 1/60, 1/30, 1/15
	 */	
	kCCDirectorTypeDisplayLink,
	
	/** Default director is the NSTimer directory */
	kCCDirectorTypeDefault = kCCDirectorTypeNSTimer,

	// backward compatibility stuff
	CCDirectorTypeNSTimer = kCCDirectorTypeNSTimer,
	CCDirectorTypeMainLoop = kCCDirectorTypeMainLoop,
	CCDirectorTypeThreadMainLoop = kCCDirectorTypeThreadMainLoop,
	CCDirectorTypeDisplayLink = kCCDirectorTypeDisplayLink,
	CCDirectorTypeDefault =kCCDirectorTypeDefault,
} ccDirectorType;

/** @typedef ccDeviceOrientation
 Possible device orientations
 */
typedef enum {
	/// Device oriented vertically, home button on the bottom
	kCCDeviceOrientationPortrait = 0, // UIDeviceOrientationPortrait,	
	/// Device oriented vertically, home button on the top
    kCCDeviceOrientationPortraitUpsideDown = 1, // UIDeviceOrientationPortraitUpsideDown,
	/// Device oriented horizontally, home button on the right
    kCCDeviceOrientationLandscapeLeft = 2, // UIDeviceOrientationLandscapeLeft,
	/// Device oriented horizontally, home button on the left
    kCCDeviceOrientationLandscapeRight = 3, // UIDeviceOrientationLandscapeRight,

	// Backward compatibility stuff
	CCDeviceOrientationPortrait = kCCDeviceOrientationPortrait,
	CCDeviceOrientationPortraitUpsideDown = kCCDeviceOrientationPortraitUpsideDown,
	CCDeviceOrientationLandscapeLeft = kCCDeviceOrientationLandscapeLeft,
	CCDeviceOrientationLandscapeRight = kCCDeviceOrientationLandscapeRight,
} ccDeviceOrientation;

class CCLabelTTF;
class CCScene;
class CCEGLView;
class CCNode;
class CCProjectionProtocol;

/**
@brief Class that creates and handle the main Window and manages how
and when to execute the Scenes.
 
 The CCDirector is also responsible for:
  - initializing the OpenGL context
  - setting the OpenGL pixel format (default on is RGB565)
  - setting the OpenGL buffer depth (default one is 0-bit)
  - setting the projection (default one is 3D)
  - setting the orientation (default one is Protrait)
 
 Since the CCDirector is a singleton, the standard way to use it is by calling:
  _ CCDirector::sharedDirector()->methodName();
 
 The CCDirector also sets the default OpenGL context:
  - GL_TEXTURE_2D is enabled
  - GL_VERTEX_ARRAY is enabled
  - GL_COLOR_ARRAY is enabled
  - GL_TEXTURE_COORD_ARRAY is enabled
*/
class CC_DLL CCDirector : public CCObject
{
public: 
	virtual bool init(void);
	virtual ~CCDirector(void);
	CCDirector(void) {}

	// attribute

	/** Get current running Scene. Director can only run one Scene at the time */
	inline CCScene* getRunningScene(void) { return m_pRunningScene; }

	/** Get the FPS value */
	inline double getAnimationInterval(void) { return m_dAnimationInterval; }
	/** Set the FPS value. */
	virtual void setAnimationInterval(double dValue) = 0;

	/** Whether or not to display the FPS on the bottom-left corner */
	inline bool isDisplayFPS(void) { return m_bDisplayFPS; }
	/** Display the FPS on the bottom-left corner */
	inline void setDisplayFPS(bool bDisplayFPS) { m_bDisplayFPS = bDisplayFPS; }

	/** Get the CCEGLView, where everything is rendered */
	inline CC_GLVIEW* getOpenGLView(void) { return m_pobOpenGLView; }
	void setOpenGLView(CC_GLVIEW *pobOpenGLView);

	inline bool isNextDeltaTimeZero(void) { return m_bNextDeltaTimeZero; }
	void setNextDeltaTimeZero(bool bNextDeltaTimeZero);

	/** Whether or not the Director is paused */
	inline bool isPaused(void) { return m_bPaused; }
    
    /** How many frames were called since the director started */
    inline unsigned int getFrames(void) { return m_uFrames; }
    
	/** Sets an OpenGL projection
	 @since v0.8.2
	 */
	inline ccDirectorProjection getProjection(void) { return m_eProjection; }
	void setProjection(ccDirectorProjection kProjection);

    /** How many frames were called since the director started */
    
    
	/** Whether or not the replaced scene will receive the cleanup message.
	 If the new scene is pushed, then the old scene won't receive the "cleanup" message.
	 If the new scene replaces the old one, the it will receive the "cleanup" message.
	 @since v0.99.0
	 */
	inline bool isSendCleanupToScene(void) { return m_bSendCleanupToScene; }


	// window size

	/** returns the size of the OpenGL view in points.
	It takes into account any possible rotation (device orientation) of the window
	*/
	CCSize getWinSize(void);

	/** returns the size of the OpenGL view in pixels.
	It takes into account any possible rotation (device orientation) of the window.
	On Mac winSize and winSizeInPixels return the same value.
	*/
	CCSize getWinSizeInPixels(void);

	/** returns the display size of the OpenGL view in pixels.
	It doesn't take into account any possible rotation of the window.
	*/
	CCSize getDisplaySizeInPixels(void);

	/** changes the projection size */
	void reshapeProjection(CCSize newWindowSize);

	/** converts a UIKit coordinate to an OpenGL coordinate
	 Useful to convert (multi) touches coordinates to the current layout (portrait or landscape)
	 */
	CCPoint convertToGL(CCPoint obPoint);

	/** converts an OpenGL coordinate to a UIKit coordinate
	 Useful to convert node points to window points for calls such as glScissor
	 */
	CCPoint convertToUI(CCPoint obPoint);

	/// XXX: missing description 
	float getZEye(void);

	// Scene Management

	/**Enters the Director's main loop with the given Scene. 
	 * Call it to run only your FIRST scene.
	 * Don't call it if there is already a running scene.
	 */
	void runWithScene(CCScene *pScene);

	/**Suspends the execution of the running scene, pushing it on the stack of suspended scenes.
	 * The new scene will be executed.
	 * Try to avoid big stacks of pushed scenes to reduce memory allocation. 
	 * ONLY call it if there is a running scene.
	 */
	void pushScene(CCScene *pScene);

	/**Pops out a scene from the queue.
	 * This scene will replace the running one.
	 * The running scene will be deleted. If there are no more scenes in the stack the execution is terminated.
	 * ONLY call it if there is a running scene.
	 */
	void popScene(void);

	/** Replaces the running scene with a new one. The running scene is terminated.
	 * ONLY call it if there is a running scene.
	 */
	void replaceScene(CCScene *pScene);

	/** Ends the execution, releases the running scene.
	 It doesn't remove the OpenGL view from its parent. You have to do it manually.
	 */

	/* end is key word of lua, use other name to export to lua. */
	inline void endToLua(void){end();}

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
	 It will purge the CCTextureCache, CCSpriteFrameCache, CCLabelBMFont cache
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

	// Profiler
	void showProfilers(void);

	/** rotates the screen if an orientation different than Portrait is used */
	void applyOrientation(void);

	ccDeviceOrientation getDeviceOrientation(void);
	void setDeviceOrientation(ccDeviceOrientation kDeviceOrientation);

	/** The size in pixels of the surface. It could be different than the screen size.
	High-res devices might have a higher surface size than the screen size.
	Only available when compiled using SDK >= 4.0.
	@since v0.99.4
	*/
	void setContentScaleFactor(CGFloat scaleFactor);
	CGFloat getContentScaleFactor(void);

	/** Will enable Retina Display on devices that supports it.
	It will enable Retina Display on iPhone4 and iPod Touch 4.
	It will return YES, if it could enabled it, otherwise it will return NO.

	This is the recommened way to enable Retina Display.
	@since v0.99.5
	*/
	bool enableRetinaDisplay(bool enabled);
    bool isRetinaDisplay() { return m_bRetinaDisplay; }

	/** There are 4 types of Director.
	- kCCDirectorTypeNSTimer (default)
	- kCCDirectorTypeMainLoop
	- kCCDirectorTypeThreadMainLoop
	- kCCDirectorTypeDisplayLink

	Each Director has it's own benefits, limitations.
	Now we only support DisplayLink director, so it has not effect. 

	This method should be called before any other call to the director.

	@since v0.8.2
	*/
	static bool setDirectorType(ccDirectorType obDirectorType);

public:
	/** returns a shared instance of the director */
	static CCDirector* sharedDirector(void);

protected:

	void purgeDirector();
	bool m_bPurgeDirecotorInNextLoop; // this flag will be set to true in end()
	
	void updateContentScaleFactor(void);

	void setNextScene(void);
	
#if CC_DIRECTOR_FAST_FPS
	/** shows the FPS in the screen */
	void showFPS(void);
#else
	void showFPS(void) {}
#endif // CC_DIRECTOR_FAST_FPS

/** calculates delta time since last time it was called */	void calculateDeltaTime();protected:
	/* The CCEGLView, where everything is rendered */
    CC_GLVIEW	*m_pobOpenGLView;

	double m_dAnimationInterval;
	double m_dOldAnimationInterval;

	/* landscape mode ? */
	bool m_bLandscape;
	
	bool m_bDisplayFPS;
	ccTime m_fAccumDt;
	ccTime m_fFrameRate;
#if	CC_DIRECTOR_FAST_FPS
	CCLabelTTF *m_pFPSLabel;
#endif
	
	/* is the running scene paused */
	bool m_bPaused;
	
    /* How many frames were called since the director started */
	unsigned int m_uTotalFrames;
    unsigned int m_uFrames;
     
	/* The running scene */
	CCScene *m_pRunningScene;
	
	/* will be the next 'runningScene' in the next frame
	 nextScene is a weak reference. */
	CCScene *m_pNextScene;
	
	/* If YES, then "old" scene will receive the cleanup message */
	bool	m_bSendCleanupToScene;

	/* scheduled scenes */
	CCMutableArray<CCScene*> *m_pobScenesStack;
	
	/* last time the main loop was updated */
	struct cc_timeval *m_pLastUpdate;

	/* delta time since last tick to main loop */
	ccTime m_fDeltaTime;

	/* whether or not the next delta time will be zero */
	bool m_bNextDeltaTimeZero;
	
	/* projection used */
	ccDirectorProjection m_eProjection;

	/* window size in points */
	CCSize	m_obWinSizeInPoints;

	/* window size in pixels */
	CCSize m_obWinSizeInPixels;
	
	/* content scale factor */
	CGFloat	m_fContentScaleFactor;

	/* store the fps string */
	char *m_pszFPS;

	/* This object will be visited after the scene. Useful to hook a notification node */
	CCNode *m_pNotificationNode;

	/* Projection protocol delegate */
	CCProjectionProtocol *m_pProjectionDelegate;

	/* The device orientation */
	ccDeviceOrientation	m_eDeviceOrientation;
	/* contentScaleFactor could be simulated */
	bool m_bIsContentScaleSupported;

	bool m_bRetinaDisplay;
	
#if CC_ENABLE_PROFILERS
	ccTime m_fAccumDtForProfiler;
#endif
};

/** 
 @brief DisplayLinkDirector is a Director that synchronizes timers with the refresh rate of the display.
 
 Features and Limitations:
  - Scheduled timers & drawing are synchronizes with the refresh rate of the display
  - Only supports animation intervals of 1/60 1/30 & 1/15
 
 @since v0.8.2
 */
class CCDisplayLinkDirector : public CCDirector
{
public:
	CCDisplayLinkDirector(void) 
		: m_bInvalid(false)
	{}

	virtual void mainLoop(void);
	virtual void setAnimationInterval(double dValue);
	virtual void startAnimation(void);
	virtual void stopAnimation();

protected:
	bool m_bInvalid;
};

}//namespace   cocos2d 

#endif // __CCDIRECTOR_H__
