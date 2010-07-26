/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "ccConfig.h"
#include "ccTypes.h"
#include "Cocos2dDefine.h"
#include "cocoa/NSObject.h"
#include "cocoa/CGGeometry.h"
#include "cocoa/NSMutableArray.h"
#include "cocoa/CGGeometry.h"

// OpenGL related
// #include "support/EAGLView.h"

#include "platform/Cocos2dTypes.h"
#include "platform/CCTime.h"

/** @typedef tPixelFormat
 Possible Pixel Formats for the EAGLView
 */
typedef enum {
	/** RGB565 pixel format. No alpha. 16-bit. (Default) */
	kCCPixelFormatRGB565,
	/** RGBA format. 32-bit. Needed for some 3D effects. It is not as fast as the RGB565 format. */
	kCCPixelFormatRGBA8888,
	/** default pixel format */
	kCCPixelFormatDefault = kCCPixelFormatRGB565,

	// backward compatibility stuff
	kPixelFormatRGB565 = kCCPixelFormatRGB565,
	kRGB565 = kCCPixelFormatRGB565,
	kPixelFormatRGBA8888 = kCCPixelFormatRGBA8888,
	kRGBA8 = kCCPixelFormatRGBA8888,
} tPixelFormat;

/** @typedef tDepthBufferFormat
 Possible DepthBuffer Formats for the EAGLView.
 Use 16 or 24 bit depth buffers if you are going to use real 3D objects.
 */
typedef enum {
	/// A Depth Buffer of 0 bits will be used (default)
	kCCDepthBufferNone,
	/// A depth buffer of 16 bits will be used
	kCCDepthBuffer16,
	/// A depth buffer of 24 bits will be used
	kCCDepthBuffer24,
	
	// backward compatibility stuff
	kDepthBuffer16 = kCCDepthBuffer16,
	kDepthBuffer24 = kCCDepthBuffer24,
} tDepthBufferFormat;

/** @typedef ccDirectorProjection
 Possible OpenGL projections used by director
 */
typedef enum {
	/// sets a 2D projection (orthogonal projection)
	kCCDirectorProjection2D,
	
	/// sets a 3D projection with a fovy=60, znear=0.5f and zfar=1500.
	kCCDirectorProjection3D,
	
	/// it does nothing. But if you are using a custom projection set it this value.
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
	 * - The invertal update is customizable from 1 to 60
	 */
	kCCDirectorTypeNSTimer,
	
	/** will use a Director that triggers the main loop from a custom main loop.
	 *
	 * Features and Limitations:
	 * - Faster than NSTimer Director
	 * - It doesn't integrate well with UIKit objecgts
	 * - The interval update can't be customizable
	 */
	kCCDirectorTypeMainLoop,
	
	/** Will use a Director that triggers the main loop from a thread, but the main loop will be executed on the main thread.
	 *
	 * Features and Limitations:
	 * - Faster than NSTimer Director
	 * - It doesn't integrate well with UIKit objecgts
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

class CCLabelAtlas;
class CCScene;

/**Class that creates and handle the main Window and manages how
and when to execute the Scenes.
 
 The CCDirector is also resposible for:
  - initializing the OpenGL ES context
  - setting the OpenGL ES pixel format (default on is RGB565)
  - setting the OpenGL ES buffer depth (default one is 0-bit)
  - setting the projection (default one is 2D)
  - setting the orientation (default one is Protrait)
 
 Since the CCDirector is a singleton, the standard way to use it is by calling:
  - [[CCDirector sharedDirector] xxxx];
 
 The CCDirector also sets the default OpenGL ES context:
  - GL_TEXTURE_2D is enabled
  - GL_VERTEX_ARRAY is enabled
  - GL_COLOR_ARRAY is enabled
  - GL_TEXTURE_COORD_ARRAY is enabled
*/
class CCDirector : public NSObject
{
public: 
	virtual CCDirector* init(void);
	virtual ~CCDirector(void);
	CCDirector(void) {}

	// attribute

	// The current running Scene. Director can only run one Scene at the time 
	CCScene* getRunningScene(void);

	// The FPS value
	double getAnimationInterval(void);
	virtual void setAnimationInterval(double dValue);

	// Whether or not to display the FPS on the bottom-left corner
	bool isDisplayFPS(void);
	void setDisplayFPS(bool bDisplayFPS);

	// The EAGLView, where everything is rendered
	EAGLView* getOpenGLView(void);
	void setOpenGLView(EAGLView *pobOpenGLView);

	// Pixel format used to create the context
	tPixelFormat getPiexFormat(void);

	// whether or not the next delta time will be zero
	bool isNextDeltaTimeZero(void);
	void setNextDeltaTimeZero(bool bNextDeltaTimeZero);

	// The device orientattion
	ccDeviceOrientation getDeviceOrientation(void);
	void setDeviceOrientation(ccDeviceOrientation kDeviceOrientation);

	// Whether or not the Director is paused
	bool isPaused(void);

	/** Sets an OpenGL projection
	 @since v0.8.2
	 */
	ccDirectorProjection getProjection(void);
	void setProjection(ccDirectorProjection kProjection);

	/** Whether or not the replaced scene will receive the cleanup message.
	 If the new scene is pushed, then the old scene won't receive the "cleanup" message.
	 If the new scene replaces the old one, the it will receive the "cleanup" message.
	 @since v0.99.0
	 */
	bool isSendCleanupToScene(void);

	/** The size in pixels of the surface. It could be different than the screen size.
	 High-res devices might have a higher surface size than the screen size.
	 Only available when compiled using SDK >= 4.0.
	 @since v0.99.4
	 */
	CGFloat getContentScaleFactor(void);
	void setContentScaleFactor(CGFloat obCGFloatValue);

    // UI dependent

	/** Uses a new pixel format for the EAGLView.
	 Call this class method before attaching it to a UIView
	 Default pixel format: kRGB565. Supported pixel formats: kRGBA8 and kRGB565
	 
	 @deprecated Set the pixel format when creating the EAGLView. This method will be removed in v1.0
	 */
	void setPixelFormat(tPixelFormat kPixelFormat);

	/** Change depth buffer format of the render buffer.
	 Call this class method before attaching it to a UIWindow/UIView
	 Default depth buffer: 0 (none).  Supported: kCCDepthBufferNone, kCCDepthBuffer16, and kCCDepthBuffer24
	 
	 @deprecated Set the depth buffer format when creating the EAGLView. This method will be removed in v1.0
	 */
	void setDepthBufferFormat(tDepthBufferFormat kDepthBufferFormat);

	// Integration with UI
	/** detach the cocos2d view from the view/window */
	bool detach(void);

	/** attach in UIWindow using the full frame.
	 It will create a EAGLView.
	 
	 @deprecated set setOpenGLView instead. Will be removed in v1.0
	 */
	// bool attachInWindow(UIWindow *pWindow);

	/** attach in UIView using the full frame.
	 It will create a EAGLView.
	 
	 @deprecated set setOpenGLView instead. Will be removed in v1.0
	 */
	// bool attachInView(UIView *pView);

	/** attach in UIView using the given frame.
	 It will create a EAGLView and use it.
	 
	 @deprecated set setOpenGLView instead. Will be removed in v1.0
	 */
	// bool attchInViewWithFrame(UIView *pView, CGRect frame);

    
	// set the view where opengl to draw in
	bool attachWindow(UIWindow *pVindow);

	// Landspace

	// returns the size of the OpenGL view in pixels, according to the landspace
	CGSize getWinSize(void);

	// returns the display size of the OpenGL view in pixels
	CGSize getDisplaySize(void);

	/** converts a UIKit coordinate to an OpenGL coordinate
	 Useful to convert (multi) touchs coordinates to the current layout (portrait or landscape)
	 */
	CGPoint convertToGL(CGPoint obPoint);

	/** converts an OpenGL coordinate to a UIKit coordinate
	 Useful to convert node points to window points for calls such as glScissor
	 */
	CGPoint convertToUI(CGPoint obPoint);

	// rotates the screen if Landscape mode is activated
	void applyLandspace(void);

	// XXX: missing description
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
	void end(void);

	/** Pauses the running scene.
	 The running scene will be _drawed_ but all scheduled timers will be paused
	 While paused, the draw rate will be 4 FPS to reduce CPU consuption
	 */
	void pause(void);

	/** Resumes the paused scene
	 The scheduled timers will be activated again.
	 The "delta time" will be 0 (as if the game wasn't paused)
	 */
	void resume(void);

	/** Stops the animation. Nothing will be drawn. The main loop won't be triggered anymore.
	 If you wan't to pause your animation call [pause] instead.
	 */
	virtual void stopAnimation(void);

	/** The main loop is triggered again.
	 Call this function only if [stopAnimation] was called earlier
	 @warning Dont' call this function to start the main loop. To run the main loop call runWithScene
	 */
	virtual void startAnimation(void);

	// Memory Helper

	/** Removes cached all cocos2d cached data.
	 It will purge the CCTextureCache, CCSpriteFrameCache, CCBitmapFont cache
	 @since v0.99.3
	 */
	void purgeCachedData(void);

	// OpenGL Helper

	// sets the OpenGL default values
	void setGLDefaultValues(void);

	// enables/disables OpenGL alpha blending
	void setAlphaBlending(bool bOn);

	// enables/disables OpenGL depth test
	void setDepthTest(bool bOn);

public:
	// returns a shared instance of the director
	static CCDirector* getSharedDirector(void);

	/** There are 4 types of Director.
	 - CCDirectorTypeNSTimer (default)
	 - CCDirectorTypeMainLoop
	 - CCDirectorTypeThreadMainLoop
	 - CCDirectorTypeDisplayLink
	 
	 Each Director has it's own benefits, limitations.
	 If you are using SDK 3.1 or newer it is recommed to use the DisplayLink director
	 
	 This method should be called before any other call to the director.

	 It will return NO if the director type is CCDirectorTypeDisplayLink and the running SDK is < 3.1. Otherwise it will return YES.
	 
	 @since v0.8.2
	 */
	// should we support four types???
	static bool setDierectorType(ccDirectorType obDirectorType);

protected:
	bool isOpenGLAttached(void);
	// bool initOpenGLViewWithViewWithFrame(UIView *pView, CGRect obRect);

	virtual void preMainLoop(void);
	void mainLoop(void);
	void setNextScene(void);
	// shows the FPS in the screen
	void showFPS(void);
	// calculates delta time since last time it was called
	void calculateDeltaTime(void);

#if defined CC_ENABLE_PROFILERS
	void showProfilers(void);
#endif // CC_ENABLE_PROFILERS

protected:
	EAGLView	*m_pobOpenGLView;

	//NSTimeInterval animationInterval;
	//NSTimeInterval oldAnimationInterval;
	// NSTimeInterval -> double
	double m_dAnimationInterval;
	double m_dOldAnimationInterval;

	tPixelFormat m_ePixelFormat;
	tDepthBufferFormat m_eDepthBufferFormat;

	/* landscape mode ? */
	bool m_bLandscape;
	
	/* orientation */
	ccDeviceOrientation	m_eDeviceOrientation;
	
	/* display FPS ? */
	bool   m_bDisplayFPS;
	INT32  m_nFrames;
	ccTime m_fAccumDt;
	ccTime m_fFrameRate;
#if	CC_DIRECTOR_FAST_FPS
	// todo implement CCLabelAtlas
//	CCLabelAtlas *FPSLabel;
#endif
	
	/* is the running scene paused */
	bool m_bPaused;
	
	/* The running scene */
	CCScene *m_pRunningScene;
	
	/* will be the next 'runningScene' in the next frame
	 nextScene is a weak reference. */
	CCScene *m_pNextScene;
	
	/* If YES, then "old" scene will receive the cleanup message */
	bool	m_bSendCleanupToScene;

	/* scheduled scenes */
	NSMutableArray<CCScene*> *m_pobScenesStack;
	
	/* last time the main loop was updated */
	struct cc_timeval m_sLastUpdate;

	/* delta time since last tick to main loop */
	ccTime m_fDeltaTime;

	/* whether or not the next delta time will be zero */
	bool m_bNextDeltaTimeZero;
	
	/* projection used */
	ccDirectorProjection m_eProjection;
	
	/* screen, different than surface size */
	CGSize	m_obScreenSize;

	/* screen, different than surface size */
	CGSize	m_obSurfaceSize;
	
	/* content scale factor */
	CGFloat	m_fContentScaleFactor;
	
#if CC_ENABLE_PROFILERS
	ccTime m_fAccumDtForProfiler;
#endif
};


/** FastDirector is a Director that triggers the main loop as fast as possible.
 *
 * Features and Limitations:
 *  - Faster than "normal" director
 *  - Consumes more battery than the "normal" director
 *  - It has some issues while using UIKit objects
 */
/*
class CCFastDirector : public CCDirector
{
public:
	static CCFastDirector* getSharedDirector(void);

protected:
	virtual void preMainLoop(void);

private:
	CCFastDirector(void) {}

protected:
	bool isRunning;
	NSAutoreleasePool *pAutoreleasePool;
};
*/

/** ThreadedFastDirector is a Director that triggers the main loop from a thread.
 *
 * Features and Limitations:
 *  - Faster than "normal" director
 *  - Consumes more battery than the "normal" director
 *  - It can be used with UIKit objects
 *
 * @since v0.8.2
 */
/*
class CCThreadedFastDirector : public CCDirector
{
public:
	static CCThreadedFastDirector* getSharedDirector(void);
protected:
	virtual void preMainLoop(void);

private:
	CCThreadedFastDirector(void){}

protected:
	bool isRunning;
};
*/

/** DisplayLinkDirector is a Director that synchronizes timers with the refresh rate of the display.
 *
 * Features and Limitations:
 * - Only available on 3.1+
 * - Scheduled timers & drawing are synchronizes with the refresh rate of the display
 * - Only supports animation intervals of 1/60 1/30 & 1/15
 *
 * It is the recommended Director if the SDK is 3.1 or newer
 *
 * @since v0.8.2
 */
class CCDisplayLinkDirector : public CCDirector
{
public:
	CCDisplayLinkDirector(void) {}

   //static CCDisplayLinkDirector* getSharedDirector(void);
	virtual void preMainLoop(void);
	virtual void setAnimationInterval(double dValue);
	virtual void startAnimation(void);
	virtual void stopAnimation();

protected:
	bool m_bInvalid;
};

/** TimerDirector is a Director that calls the main loop from an NSTimer object
 *
 * Features and Limitations:
 * - Integrates OK with UIKit objects
 * - It the slowest director
 * - The invertal update is customizable from 1 to 60
 *
 * It is the default Director.
 */
/*
class CCTimerDirector : public CCDirector
{
public:
    static CCTimerDirector* getSharedDirector(void);

protected:
	virtual void preMain(void);

private:
	CCTimerDirector(void) {}

protected:
	NSTimer *pAnimationTimer;
};
*/

#endif // __CCDIRECTOR_H__
