/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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

#ifndef __CCGLVIEW_H__
#define __CCGLVIEW_H__

#include "base/ccTypes.h"
#include "base/CCEventTouch.h"

#include <vector>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <windows.h>
#endif /* (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) */

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
typedef void* id;
#endif /* (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) */

enum class ResolutionPolicy
{
    // The entire application is visible in the specified area without trying to preserve the original aspect ratio.
    // Distortion can occur, and the application may appear stretched or compressed.
    EXACT_FIT,
    // The entire application fills the specified area, without distortion but possibly with some cropping,
    // while maintaining the original aspect ratio of the application.
    NO_BORDER,
    // The entire application is visible in the specified area without distortion while maintaining the original
    // aspect ratio of the application. Borders can appear on two sides of the application.
    SHOW_ALL,
    // The application takes the height of the design resolution size and modifies the width of the internal
    // canvas so that it fits the aspect ratio of the device
    // no distortion will occur however you must make sure your application works on different
    // aspect ratios
    FIXED_HEIGHT,
    // The application takes the width of the design resolution size and modifies the height of the internal
    // canvas so that it fits the aspect ratio of the device
    // no distortion will occur however you must make sure your application works on different
    // aspect ratios
    FIXED_WIDTH,

    UNKNOWN,
};

struct GLContextAttrs
{
    int redBits;
    int greenBits;
    int blueBits;
    int alphaBits;
    int depthBits;
    int stencilBits;
};

NS_CC_BEGIN

/**
 * @addtogroup platform
 * @{
 */

class CC_DLL GLView : public Ref
{
public:
    /**
     * @js ctor
     */
    GLView();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~GLView();

    /** Force destroying EGL view, subclass must implement this method. */
    virtual void end() = 0;

    /** Get whether opengl render system is ready, subclass must implement this method. */
    virtual bool isOpenGLReady() = 0;

    /** Exchanges the front and back buffers, subclass must implement this method. */
    virtual void swapBuffers() = 0;

    /** Open or close IME keyboard , subclass must implement this method. */
    virtual void setIMEKeyboardState(bool open) = 0;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    virtual void setIMEKeyboardState(bool open, std::string str) = 0;
#endif
    
    virtual bool windowShouldClose() { return false; };

    //static method and member so that we can modify it on all platforms before create OpenGL context
    static void setGLContextAttrs(GLContextAttrs& glContextAttrs);
    static GLContextAttrs getGLContextAttrs();
    static GLContextAttrs _glContextAttrs;

    /**
     * Polls input events. Subclass must implement methods if platform
     * does not provide event callbacks.
     */
    CC_DEPRECATED_ATTRIBUTE virtual void pollInputEvents();

    virtual void pollEvents();

    /**
     * Get the frame size of EGL view.
     * In general, it returns the screen size since the EGL view is a fullscreen view.
     */
    virtual const Size& getFrameSize() const;

    /**
     * Set the frame size of EGL view.
     */
    virtual void setFrameSize(float width, float height);

    /** Set and get zoom factor for frame. This two methods are for
     debugging big resolution (e.g.new ipad) app on desktop.*/
    virtual void setFrameZoomFactor(float zoomFactor) {}
    virtual float getFrameZoomFactor() const { return 1.0; }
    
    /** Get retina factor */
    virtual int getRetinaFactor() const { return 1; }

    /** only works on ios platform*/
    virtual bool setContentScaleFactor(float scaleFactor) { return false; }
    virtual float getContentScaleFactor() const { return 1.0; }
    
    /** returns whether or not the view is in Retina Display mode */
    virtual bool isRetinaDisplay() const { return false; }
 
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    virtual void* getEAGLView() const { return nullptr; }
#endif /* (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) */

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	virtual Size getRenerTargetSize() const = 0;
	virtual const Mat4& getOrientationMatrix() const = 0;
	virtual const Mat4& getReverseOrientationMatrix() const = 0;
#endif
    /**
     * Get the visible area size of opengl viewport.
     */
    virtual Size getVisibleSize() const;

    /**
     * Get the visible origin point of opengl viewport.
     */
    virtual Vec2 getVisibleOrigin() const;

    /**
     * Get the visible rectangle of opengl viewport.
     */
    virtual Rect getVisibleRect() const;

    /**
     * Set the design resolution size.
     * @param width Design resolution width.
     * @param height Design resolution height.
     * @param resolutionPolicy The resolution policy desired, you may choose:
     *                         [1] EXACT_FIT Fill screen by stretch-to-fit: if the design resolution ratio of width to height is different from the screen resolution ratio, your game view will be stretched.
     *                         [2] NO_BORDER Full screen without black border: if the design resolution ratio of width to height is different from the screen resolution ratio, two areas of your game view will be cut.
     *                         [3] SHOW_ALL  Full screen with black border: if the design resolution ratio of width to height is different from the screen resolution ratio, two black borders will be shown.
     */
    virtual void setDesignResolutionSize(float width, float height, ResolutionPolicy resolutionPolicy);

    /** Get design resolution size.
     *  Default resolution size is the same as 'getFrameSize'.
     */
    virtual const Size&  getDesignResolutionSize() const;

    /**
     * Set opengl view port rectangle with points.
     */
    virtual void setViewPortInPoints(float x , float y , float w , float h);

    /**
     * Set Scissor rectangle with points.
     */
    virtual void setScissorInPoints(float x , float y , float w , float h);

    /**
     * Get whether GL_SCISSOR_TEST is enable
     */
    virtual bool isScissorEnabled();

    /**
     * Get the current scissor rectangle
     */
    virtual Rect getScissorRect() const;

    virtual void setViewName(const std::string& viewname);
    const std::string& getViewName() const;

    /** Touch events are handled by default; if you want to customize your handlers, please override these functions: */
    virtual void handleTouchesBegin(int num, intptr_t ids[], float xs[], float ys[]);
    virtual void handleTouchesMove(int num, intptr_t ids[], float xs[], float ys[]);
    virtual void handleTouchesEnd(int num, intptr_t ids[], float xs[], float ys[]);
    virtual void handleTouchesCancel(int num, intptr_t ids[], float xs[], float ys[]);

    /**
     * Get the opengl view port rectangle.
     */
    const Rect& getViewPortRect() const;
    
    /**
     * Get list of all active touches
     */
    std::vector<Touch*> getAllTouches() const;

    /**
     * Get scale factor of the horizontal direction.
     */
    float getScaleX() const;

    /**
     * Get scale factor of the vertical direction.
     */
    float getScaleY() const;

    /** returns the current Resolution policy */
    ResolutionPolicy getResolutionPolicy() const { return _resolutionPolicy; }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    virtual HWND getWin32Window() = 0;
#endif /* (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) */

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    virtual id getCocoaWindow() = 0;
#endif /* (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) */
    
protected:
    void updateDesignResolutionSize();
    
    void handleTouchesOfEndOrCancel(EventTouch::EventCode eventCode, int num, intptr_t ids[], float xs[], float ys[]);

    // real screen size
    Size _screenSize;
    // resolution size, it is the size appropriate for the app resources.
    Size _designResolutionSize;
    // the view port size
    Rect _viewPortRect;
    // the view name
    std::string _viewName;

    float _scaleX;
    float _scaleY;
    ResolutionPolicy _resolutionPolicy;
};

// end of platform group
/// @}

NS_CC_END

#endif /* __CCGLVIEW_H__ */
