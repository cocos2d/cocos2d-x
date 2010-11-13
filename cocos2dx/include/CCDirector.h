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
#include "CCXCocos2dDefine.h"
#include "NSObject.h"
#include "CGGeometry.h"
#include "NSMutableArray.h"
#include "CGGeometry.h"
#include "CCXEGLView.h"
#include "ccxCommon.h"

#include <assert.h>
namespace   cocos2d {

/** @typedef tPixelFormat
 Possible Pixel Formats for the CCXEGLView
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
 Possible DepthBuffer Formats for the CCXEGLView.
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

class CCLabel;
class CCScene;
class cocos2d::CCXEGLView;

/**
@brief Class that creates and handle the main Window and manages how
and when to execute the Scenes.
 
 The CCDirector is also responsible for:
  - initializing the OpenGL ES context
  - setting the OpenGL ES pixel format (default on is RGB565)
  - setting the OpenGL ES buffer depth (default one is 0-bit)
  - setting the projection (default one is 2D)
  - setting the orientation (default one is Protrait)
 
 Since the CCDirector is a singleton, the standard way to use it is by calling:
  _ CCDirector::sharedDirector()->xxx();
 
 The CCDirector also sets the default OpenGL ES context:
  - GL_TEXTURE_2D is enabled
  - GL_VERTEX_ARRAY is enabled
  - GL_COLOR_ARRAY is enabled
  - GL_TEXTURE_COORD_ARRAY is enabled
*/
class CCX_DLL CCDirector : public NSObject
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
	virtual void setAnimationInterval(double dValue);

	/** Whether or not to display the FPS on the bottom-left corner */
	inline bool isDisplayFPS(void) { return m_bDisplayFPS; }
	/** Display the FPS on the bottom-left corner */
	inline void setDisplayFPS(bool bDisplayFPS) { m_bDisplayFPS = bDisplayFPS; }

	/** Get the CCXEGLView, where everything is rendered */
	inline cocos2d::CCXEGLView* getOpenGLView(void) { return m_pobOpenGLView; }
	void setOpenGLView(cocos2d::CCXEGLView *pobOpenGLView);

	inline bool isNextDeltaTimeZero(void) { return m_bNextDeltaTimeZero; }
	void setNextDeltaTimeZero(bool bNextDeltaTimeZero);

	inline ccDeviceOrientation getDeviceOrientation(void) { return m_eDeviceOrientation; }
	void setDeviceOrientation(ccDeviceOrientation kDeviceOrientation);

	/** Whether or not the Director is paused */
	inline bool isPaused(void) { return m_bPaused; }

	/** Sets an OpenGL projection
	 @since v0.8.2
	 */
	inline ccDirectorProjection getProjection(void) { return m_eProjection; }
	void setProjection(ccDirectorProjection kProjection);

	/** Whether or not the replaced scene will receive the cleanup message.
	 If the new scene is pushed, then the old scene won't receive the "cleanup" message.
	 If the new scene replaces the old one, the it will receive the "cleanup" message.
	 @since v0.99.0
	 */
	inline bool isSendCleanupToScene(void) { return m_bSendCleanupToScene; }

	/** The size in pixels of the surface. It could be different than the screen size.
	 High-res devices might have a higher surface size than the screen size.
	 Only available when compiled using SDK >= 4.0.
	 @since v0.99.4
	 */
	void setContentScaleFactor(CGFloat scaleFactor);
	
	inline CGFloat getContentScaleFactor(void) { return m_fContentScaleFactor; }

    // UI dependent

	/** Uses a new pixel format for the CCXEGLView.
	 Call this class method before attaching it to a UIView
	 Default pixel format: kRGB565. Supported pixel formats: kRGBA8 and kRGB565
	 
	 @deprecated Set the pixel format when creating the CCXEGLView. This method will be removed in v1.0
	 */
	inline void setPixelFormat(tPixelFormat kPixelFormat)
	{
		// assert(! isOpenGLAttached());
	    m_ePixelFormat = kPixelFormat;
	}
	/** Pixel format used to create the context */
	inline tPixelFormat getPiexFormat(void) { return m_ePixelFormat; }

	/** Change depth buffer format of the render buffer.
	 Call this class method before attaching it to a UIWindow/UIView
	 Default depth buffer: 0 (none).  Supported: kCCDepthBufferNone, kCCDepthBuffer16, and kCCDepthBuffer24
	 
	 @deprecated Set the depth buffer format when creating the CCXEGLView. This method will be removed in v1.0
	 */
	inline void setDepthBufferFormat(tDepthBufferFormat kDepthBufferFormat)
	{
        assert(! isOpenGLAttached());
		m_eDepthBufferFormat = kDepthBufferFormat;
	}

	// Integration with UI
	/** detach the cocos2d view from the view/window */
	bool detach(void);

	// Landspace

	/** returns the size of the OpenGL view in pixels, according to the landspace */
	CGSize getWinSize(void);

	/** returns the display size of the OpenGL view in pixels */
	CGSize getDisplaySize(void);

	/** converts a UIKit coordinate to an OpenGL coordinate
	 Useful to convert (multi) touches coordinates to the current layout (portrait or landscape)
	 */
	CGPoint convertToGL(CGPoint obPoint);

	/** converts an OpenGL coordinate to a UIKit coordinate
	 Useful to convert node points to window points for calls such as glScissor
	 */
	CGPoint convertToUI(CGPoint obPoint);

	/** rotates the screen if an orientation different than Portrait is used */
	void applyOrientation(void);

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
	virtual void stopAnimation(void);

	/** The main loop is triggered again.
	 Call this function only if [stopAnimation] was called earlier
	 @warning Don't call this function to start the main loop. To run the main loop call runWithScene
	 */
	virtual void startAnimation(void);

	/** Draw the scene.
	This method is called every frame. Don't call it manually.
	*/
	void drawScene(void);

	// Memory Helper

	/** Removes cached all cocos2d cached data.
	 It will purge the CCTextureCache, CCSpriteFrameCache, CCBitmapFont cache
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

	virtual void preMainLoop(void);

public:
	/** returns a shared instance of the director */
	static CCDirector* sharedDirector(void);

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

protected:
	bool isOpenGLAttached(void);

	void updateContentScaleFactor(void);
	void setNextScene(void);
	
#if CC_DIRECTOR_FAST_FPS
	/** shows the FPS in the screen */
	void showFPS(void);
#else
	void showFPS(void) {}
#endif // CC_DIRECTOR_FAST_FPS

	/** calculates delta time since last time it was called */
	void calculateDeltaTime();

#if CC_ENABLE_PROFILERS
	void showProfilers(void);
#endif // CC_ENABLE_PROFILERS

	/** recalculate the projection view and projection size based on the EAGLVIEW
	@since v0.99.4
	*/
	void recalculateProjectionAndEAGLViewSize();

protected:
	// compute frame rate
    void computeFrameRate(void);
	// compute delta time between computing frame rate
	void calculateFramerateDeltaTime(void);

protected:
	/* The CCXEGLView, where everything is rendered */
    cocos2d::CCXEGLView	*m_pobOpenGLView;

	double m_dAnimationInterval;
	double m_dOldAnimationInterval;

	tPixelFormat m_ePixelFormat;
	tDepthBufferFormat m_eDepthBufferFormat;

	/* landscape mode ? */
	bool m_bLandscape;
	
	/* The device orientation */
	ccDeviceOrientation	m_eDeviceOrientation;
	
	bool m_bDisplayFPS;
	int  m_nFrames;
	ccTime m_fAccumDt;
	ccTime m_fFrameRate;
	ccTime m_fExpectedFrameRate;
#if	CC_DIRECTOR_FAST_FPS
	CCLabel *m_pFPSLabel;
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
	struct cc_timeval *m_pLastUpdate;

	/* delta time since last tick to main loop */
	ccTime m_fDeltaTime;

	/* last time the director compute frame rate */
	struct cc_timeval *m_pLastComputeFrameRate;
	/* delta time since last computing frame rate */
	ccTime m_fComputeFrameRateDeltaTime;

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

	/* contentScaleFactor could be simulated */
	bool m_bIsContentScaleSupported;

	/* store the fps string */
	char *m_pszFPS;
	
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
	CCDisplayLinkDirector(void) {}

	virtual void preMainLoop(void);
	virtual void setAnimationInterval(double dValue);
	virtual void startAnimation(void);
	virtual void stopAnimation();

protected:
	bool m_bInvalid;
};

}//namespace   cocos2d 

#endif // __CCDIRECTOR_H__
