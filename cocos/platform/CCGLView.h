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

/** There are some Resolution Policy for Adapt to the screen. */
enum class ResolutionPolicy
{
    /** The entire application is visible in the specified area without trying to preserve the original aspect ratio.
     * Distortion can occur, and the application may appear stretched or compressed.
     */
    EXACT_FIT,
    /** The entire application fills the specified area, without distortion but possibly with some cropping,
     * while maintaining the original aspect ratio of the application.
     */
    NO_BORDER,
    /** The entire application is visible in the specified area without distortion while maintaining the original
     * aspect ratio of the application. Borders can appear on two sides of the application.
     */
    SHOW_ALL,
    /** The application takes the height of the design resolution size and modifies the width of the internal
     * canvas so that it fits the aspect ratio of the device.
     * No distortion will occur however you must make sure your application works on different
     * aspect ratios.
     */
    FIXED_HEIGHT,
    /** The application takes the width of the design resolution size and modifies the height of the internal
     * canvas so that it fits the aspect ratio of the device.
     * No distortion will occur however you must make sure your application works on different
     * aspect ratios.
     */
    FIXED_WIDTH,

    UNKNOWN,
};

/** @struct GLContextAttrs 
 *
 * There are six opengl Context Attrs. 
 */
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
/**
 * @brief By GLView you can operate the frame information of EGL view through some function.
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

    /** Open or close IME keyboard , subclass must implement this method. 
     *
     * @param open Open or close IME keyboard.
     */
    virtual void setIMEKeyboardState(bool open) = 0;
    
    /** When the window is closed, it will return false if the platforms is Ios or Android.
     * If the platforms is windows or Mac,it will return true.
     *
     * @return In ios and android it will return false,if in windows or Mac it will return true.
     */
    virtual bool windowShouldClose() { return false; };

    /** Static method and member so that we can modify it on all platforms before create OpenGL context. 
     *
     * @param glContextAttrs The OpenGL context attrs.
     */
    static void setGLContextAttrs(GLContextAttrs& glContextAttrs);
    
    /** Return the OpenGL context attrs. 
     *
     * @return Return the OpenGL context attrs.
     */
    static GLContextAttrs getGLContextAttrs();
    
    /** The OpenGL context attrs. */
    static GLContextAttrs _glContextAttrs;

    /** @deprecated
     * Polls input events. Subclass must implement methods if platform
     * does not provide event callbacks.
     */
    CC_DEPRECATED_ATTRIBUTE virtual void pollInputEvents();
    
    /** Polls the events. */
    virtual void pollEvents();

    /**
     * Get the frame size of EGL view.
     * In general, it returns the screen size since the EGL view is a fullscreen view.
     *
     * @return The frame size of EGL view.
     */
    virtual const Size& getFrameSize() const;

    /**
     * Set the frame size of EGL view.
     *
     * @param width The width of the fram size.
     * @param height The height of the fram size.
     */
    virtual void setFrameSize(float width, float height);

    /** Set zoom factor for frame. This methods are for
     * debugging big resolution (e.g.new ipad) app on desktop.
     * 
     * @param zoomFactor The zoom factor for frame.
     */
    virtual void setFrameZoomFactor(float zoomFactor) {}
    
    /** Get zoom factor for frame. This methods are for
     * debugging big resolution (e.g.new ipad) app on desktop.
     *
     * @return The zoom factor for frame.
     */
    virtual float getFrameZoomFactor() const { return 1.0; }
    
    /**
     * Hide or Show the mouse cursor if there is one.
     *
     * @param isVisible Hide or Show the mouse cursor if there is one.
     */
    virtual void setCursorVisible(bool isVisible) {}

    /** Get retina factor.
     *
     * @return The retina factor.
     */
    virtual int getRetinaFactor() const { return 1; }

    /** Only works on ios platform. Set Content Scale of the Factor. */
    virtual bool setContentScaleFactor(float scaleFactor) { return false; }
    
    /** Only works on ios platform. Get Content Scale of the Factor. */
    virtual float getContentScaleFactor() const { return 1.0; }
    
    /** Returns whether or not the view is in Retina Display mode.
     *
     * @return Returns whether or not the view is in Retina Display mode.
     */
    virtual bool isRetinaDisplay() const { return false; }
 
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    virtual void* getEAGLView() const { return nullptr; }
#endif /* (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) */

    /**
     * Get the visible area size of opengl viewport.
     *
     * @return The visible area size of opengl viewport.
     */
    virtual Size getVisibleSize() const;

    /**
     * Get the visible origin point of opengl viewport.
     *
     * @return The visible origin point of opengl viewport.
     */
    virtual Vec2 getVisibleOrigin() const;

    /**
     * Get the visible rectangle of opengl viewport.
     *
     * @return The visible rectangle of opengl viewport.
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
     *
     * @return The design resolution size.
     */
    virtual const Size&  getDesignResolutionSize() const;

    /**
     * Set opengl view port rectangle with points.
     *
     * @param x Set the points of x.
     * @param y Set the points of y.
     * @param w Set the width of  the view port
     * @param h Set the Height of the view port.
     */
    virtual void setViewPortInPoints(float x , float y , float w , float h);

    /**
     * Set Scissor rectangle with points.
     *
     * @param x Set the points of x.
     * @param y Set the points of y.
     * @param w Set the width of  the view port
     * @param h Set the Height of the view port.
     */
    virtual void setScissorInPoints(float x , float y , float w , float h);

    /**
     * Get whether GL_SCISSOR_TEST is enable.
     *
     * @return Whether GL_SCISSOR_TEST is enable.
     */
    virtual bool isScissorEnabled();

    /**
     * Get the current scissor rectangle.
     *
     * @return The current scissor rectangle.
     */
    virtual Rect getScissorRect() const;

    /** Set the view name. 
     *
     * @param viewname A string will be set to the view as name.
     */
    virtual void setViewName(const std::string& viewname);
    
    /** Get the view name.
     *
     * @return The view name.
     */
    const std::string& getViewName() const;

    /** Touch events are handled by default; if you want to customize your handlers, please override this function.
     *
     * @param num The number of touch.
     * @param ids The identity of the touch.
     * @param xs The points of x.
     * @param ys The points of y.
     */
    virtual void handleTouchesBegin(int num, intptr_t ids[], float xs[], float ys[]);
    
    /** Touch events are handled by default; if you want to customize your handlers, please override this function.
     *
     * @param num The number of touch.
     * @param ids The identity of the touch.
     * @param xs The points of x.
     * @param ys The points of y.
     */
    virtual void handleTouchesMove(int num, intptr_t ids[], float xs[], float ys[]);

    /** Touch events are handled by default; if you want to customize your handlers, please override this function.
     *
     * @param num The number of touch.
     * @param ids The identity of the touch.
     * @param xs The points of x.
     * @param ys The points of y.
     * @param fs The force of 3d touches.
     # @param ms The maximum force of 3d touches
     */
    virtual void handleTouchesMove(int num, intptr_t ids[], float xs[], float ys[], float fs[], float ms[]);
    
    /** Touch events are handled by default; if you want to customize your handlers, please override this function.
     *
     * @param num The number of touch.
     * @param ids The identity of the touch.
     * @param xs The points of x.
     * @param ys The points of y.
     */
    virtual void handleTouchesEnd(int num, intptr_t ids[], float xs[], float ys[]);
    
    /** Touch events are handled by default; if you want to customize your handlers, please override this function.
     *
     * @param num The number of touch.
     * @param ids The identity of the touch.
     * @param xs The points of x.
     * @param ys The points of y.
     */
    virtual void handleTouchesCancel(int num, intptr_t ids[], float xs[], float ys[]);

    /**
     * Get the opengl view port rectangle.
     *
     * @return Return the opengl view port rectangle.
     */
    const Rect& getViewPortRect() const;
    
    /**
     * Get list of all active touches.
     *
     * @return A list of all active touches.
     */
    std::vector<Touch*> getAllTouches() const;

    /**
     * Get scale factor of the horizontal direction.
     *
     * @return Scale factor of the horizontal direction.
     */
    float getScaleX() const;

    /**
     * Get scale factor of the vertical direction.
     *
     * @return Scale factor of the vertical direction.
     */
    float getScaleY() const;

    /** Returns the current Resolution policy.
     *
     * @return The current Resolution policy.
     */
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
