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

/** @~english There are some Resolution Policy for Adapt to the screen.  @~chinese 为了适配屏幕的分辨率方案。*/
enum class ResolutionPolicy
{
    /** @~english The entire application is visible in the specified area without trying to preserve the original aspect ratio.
     * Distortion can occur, and the application may appear stretched or compressed.
     * @~chinese 整个应用程序在指定的区域是可见的,并且没有试图维持原来的宽高比。
     * 可能会发生变形,应用程序会出现拉伸或压缩。
     */
    EXACT_FIT,
    /** @~english The entire application fills the specified area, without distortion but possibly with some cropping,
     * while maintaining the original aspect ratio of the application.
     * @~chinese 整个应用程序填充指定的区域,没有变形,但是可能会被裁剪掉一部分,
     * 同时应用程序保持原来的宽高比。
     */
    NO_BORDER,
    /** @~english The entire application is visible in the specified area without distortion while maintaining the original
     * aspect ratio of the application. Borders can appear on two sides of the application.
     * @~chinese 整个应用程序在指定的区域是可见的 不会变形,同时保持原
     * 应用程序的宽高比。但是在应用的两边可能会出现黑边。
     */
    SHOW_ALL,
    /** @~english The application takes the height of the design resolution size and modifies the width of the internal
     * canvas so that it fits the aspect ratio of the device.
     * No distortion will occur however you must make sure your application works on different
     * aspect ratIOS.
     * @~chinese 应用程序将会采用设计分辨率的高度，并修改画布内部的宽度
     * 以达到和设备一致的比例
     * 没有变形会发生但是你必须确保你的应用程序能够在不同宽高比例下正常显示。
     */
    FIXED_HEIGHT,
    /** @~english The application takes the width of the design resolution size and modifies the height of the internal
     * canvas so that it fits the aspect ratio of the device.
     * No distortion will occur however you must make sure your application works on different
     * aspect ratIOS.
     * @~chinese 应用程序将会采用设计分辨率的宽度，并修改画布内部的高度
     * 以达到和设备一致的比例。
     * 没有变形会发生但是你必须确保你的应用程序能够在不同宽高比例下正常显示。
     */
    FIXED_WIDTH,

    UNKNOWN,
};

/** @struct @~english GLContextAttrs 
 *
 * There are six opengl Context Attrs. 
 * @~chinese GLContextAttrs
 * 
 * 有六个opengl 上下文环境属性。
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
 * @brief @~english By GLView you can operate the frame information of EGL view through some function.
 * @~chinese 通过GLView的一些函数可以操作EGL视图的界面信息。
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

    /** @~english Force destroying EGL view, subclass must implement this method.  @~chinese 强制摧毁EGL视图,子类必须实现这个方法。*/
    virtual void end() = 0;

    /** @~english Get whether opengl render system is ready, subclass must implement this method.  @~chinese opengl渲染系统是否准备好,子类必须实现这个方法。*/
    virtual bool isOpenGLReady() = 0;

    /** @~english Exchanges the front and back buffers, subclass must implement this method.  @~chinese 交换前后缓冲区,子类必须实现这个方法。*/
    virtual void swapBuffers() = 0;

    /** @~english Open or close IME keyboard , subclass must implement this method. 
     *
     * @~chinese 打开或关闭输入法键盘,子类必须实现这个方法。
     * 
     * @param open @~english Open or close IME keyboard.
     * @~chinese 打开或关闭输入法键盘。
     */
    virtual void setIMEKeyboardState(bool open) = 0;
    
    /** @~english When the window is closed, it will return false if the platforms is IOS or Android.
     * If the platforms is windows or Mac,it will return true.
     *
     * @~chinese 当窗口已关闭时,如果是IOS和Android平台。它将返回false
     * 如果windows或Mac平台,它将返回true。
     * 
     * @return @~english In IOS and Android it will return false,if in windows or Mac it will return true.
     * @~chinese 在IOS和Android平台,它将返回false,如果在windows或Mac,它将返回true。
     */
    virtual bool windowShouldClose() { return false; };

    /** @~english Static method and member so that we can modify it on all platforms before create OpenGL context. 
     *
     * @~chinese 静态方法和成员,以便我们创建OpenGL上下文之前可以在所有平台上修改它。
     * 
     * @param glContextAttrs @~english The OpenGL context attrs.
     * @~chinese OpenGL的属性上下文。
     */
    static void setGLContextAttrs(GLContextAttrs& glContextAttrs);
    
    /** @~english Return the OpenGL context attrs. 
     *
     * @~chinese 返回OpenGL的属性上下文。
     * 
     * @return @~english Return the OpenGL context attrs.
     * @~chinese 返回OpenGL的属性上下文。
     */
    static GLContextAttrs getGLContextAttrs();
    
    /** @~english The OpenGL context attrs.  @~chinese OpenGL的属性上下文。*/
    static GLContextAttrs _glContextAttrs;

    /** @deprecated@~english
     * Polls input events. Subclass must implement methods if platform
     * does not provide event callbacks.
     * @~chinese 
     * 输入事件。平台不提供事件回调 子类必须实现这个函数
     * 
     */
    CC_DEPRECATED_ATTRIBUTE virtual void pollInputEvents();
    
    /** @~english Polls the events.  @~chinese 民意调查的事件。*/
    virtual void pollEvents();

    /**@~english
     * Get the frame size of EGL view.
     * In general, it returns the screen size since the EGL view is a fullscreen view.
     *
     * @~chinese 
     * 得到EGL视图的界面大小。
     * 一般来说,它返回屏幕大小的EGL视图是一个全屏视图。
     * 
     * @return @~english The frame size of EGL view.
     * @~chinese EGL视图的界面大小。
     */
    virtual const Size& getFrameSize() const;

    /**@~english
     * Set the frame size of EGL view.
     *
     * @~chinese 
     * 设置EGL视图界面大小的。
     * 
     * @param width @~english The width of the frame size.
     * @~chinese 界面的宽度
     * @param height @~english The height of the frame size.
     * @~chinese 界面的高度
     */
    virtual void setFrameSize(float width, float height);

    /** @~english Set zoom factor for frame. This methods are for
     * debugging big resolution (e.g.new ipad) app on desktop.
     * 
     * @~chinese 这个方法是为界面设置缩放因子。
     * 大决议(如调试。新ipad)在桌面应用程序。
     * 
     * @param zoomFactor @~english The zoom factor for frame.
     * @~chinese 框架的放大因子。
     */
    virtual void setFrameZoomFactor(float zoomFactor) {}
    
    /** @~english Get zoom factor for frame. This methods are for
     * debugging big resolution (e.g.new ipad) app on desktop.
     *
     * @~chinese 获得界面的缩放因子。这个方法是
     * 用来调试大分辨率(如new ipad)的桌面应用程序。
     * 
     * @return @~english The zoom factor for frame.
     * @~chinese 框架的放大因子。
     */
    virtual float getFrameZoomFactor() const { return 1.0; }
    
    /**@~english
     * Hide or Show the mouse cursor if there is one.
     *
     * @~chinese 
     * 如果有一个鼠标光标，这个函数是用来隐藏或显示光标的。
     * 
     * @param isVisible @~english Hide or Show the mouse cursor if there is one.
     * @~chinese 如果有一个鼠标光标 true是显示光标，false是隐藏光标。
     */
    virtual void setCursorVisible(bool isVisible) {}

    /** @~english Get retina factor.
     *
     * @~chinese 获取视网膜的系数。
     * 
     * @return @~english The retina factor.
     * @~chinese 视网膜的系数。
     */
    virtual int getRetinaFactor() const { return 1; }

    /** @~english Only works on IOS platform. Set Content Scale of the Factor.  @~chinese 只有在IOS平台上工作。设置内容缩放系数。*/
    virtual bool setContentScaleFactor(float scaleFactor) { return false; }
    
    /** @~english Only works on IOS platform. Get Content Scale of the Factor.  @~chinese 只有在IOS平台上工作。获取内容缩放系数。*/
    virtual float getContentScaleFactor() const { return 1.0; }
    
    /** @~english Returns whether or not the view is in Retina Display mode.
     *
     * @~chinese 返回视图是否是高清显示模式。
     * 
     * @return @~english Returns whether or not the view is in Retina Display mode.
     * @~chinese 返回视图是否是高清显示模式。
     */
    virtual bool isRetinaDisplay() const { return false; }
 
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    virtual void* getEAGLView() const { return nullptr; }
#endif /* (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) */

    /**@~english
     * Get the visible area size of opengl viewport.
     *
     * @~chinese 
     * opengl窗口的可见区域大小。
     * 
     * @return @~english The visible area size of opengl viewport.
     * @~chinese opengl窗口的可见区域大小。
     */
    virtual Size getVisibleSize() const;

    /**@~english
     * Get the visible origin point of opengl viewport.
     *
     * @~chinese 
     * opengl可见窗口的源点。
     * 
     * @return @~english The visible origin point of opengl viewport.
     * @~chinese opengl可见窗口的源点。
     */
    virtual Vec2 getVisibleOrigin() const;

    /**@~english
     * Get the visible rectangle of opengl viewport.
     *
     * @~chinese 
     * opengl窗口的可见矩形。
     * 
     * @return @~english The visible rectangle of opengl viewport.
     * @~chinese opengl窗口的可见矩形。
     */
    virtual Rect getVisibleRect() const;

    /**@~english
     * Set the design resolution size.
     * @~chinese 
     * 设置设计分辨率大小。
     * @param width @~english Design resolution width.
     * @~chinese 设计分辨率宽度。
     * @param height @~english Design resolution height.
     * @~chinese 设计分辨率高度
     * @param resolutionPolicy @~english The resolution policy desired, you may choose:
     *                         [1] EXACT_FIT Fill screen by stretch-to-fit: if the design resolution ratio of width to height is different from the screen resolution ratio, your game view will be stretched.
     *                         [2] NO_BORDER Full screen without black border: if the design resolution ratio of width to height is different from the screen resolution ratio, two areas of your game view will be cut.
     *                         [3] SHOW_ALL  Full screen with black border: if the design resolution ratio of width to height is different from the screen resolution ratio, two black borders will be shown.
     * @~chinese 分辨率方案,你可以选择:
     * [1]EXACT_FIT 拉伸适配屏幕:如果设计分辨率与屏幕分辨率的宽,高比例是不同的,你的游戏视图将会被拉伸。
     * [2]NO_BORDER 没有黑边的全屏:如果设计分辨率与屏幕分辨率的宽,高比例是不同的,会有两个区域的游戏视图将被裁剪。
     * [3]SHOW_ALL 有黑边的全屏:如果设计分辨率与屏幕分辨率的宽,高比例是不同的,游戏视频边界将会有两个黑边。
     */
    virtual void setDesignResolutionSize(float width, float height, ResolutionPolicy resolutionPolicy);

    /** @~english Get design resolution size.
     *  Default resolution size is the same as 'getFrameSize'.
     *
     * @~chinese 获得设计分辨率大小。
     * 默认的设计分辨率与函数“getFrameSize”。大小一样
     * 
     * @return @~english The design resolution size.
     * @~chinese 获得设计分辨率大小。
     */
    virtual const Size&  getDesignResolutionSize() const;

    /**@~english
     * Set opengl view port rectangle with points.
     *
     * @~chinese 
     * 设置opengl视窗。
     * 
     * @param x @~english Set the points of x.
     * @~chinese 设置视窗的x坐标。
     * @param y @~english Set the points of y.
     * @~chinese 设置视窗的y坐标。
     * @param w @~english Set the width of  the view port
     * @~chinese 设置视窗的宽度
     * @param h @~english Set the Height of the view port.
     * @~chinese 设置视窗的高度。
     */
    virtual void setViewPortInPoints(float x , float y , float w , float h);

    /**@~english
     * Set Scissor rectangle with points.
     *
     * @~chinese 
     * 设置裁剪矩形宽度
     * 
     * @param x @~english Set the points of x.
     * @~chinese 设置裁剪点的x坐标。
     * @param y @~english Set the points of y.
     * @~chinese 设置裁剪点y坐标。
     * @param w @~english Set the width of  the view port
     * @~chinese 设置裁剪视窗宽度
     * @param h @~english Set the Height of the view port.
     * @~chinese 设置裁剪视窗高度。
     */
    virtual void setScissorInPoints(float x , float y , float w , float h);

    /**@~english
     * Get whether GL_SCISSOR_TEST is enable.
     *
     * @~chinese 
     * 获取GL_SCISSOR_TEST是否启用。
     * 
     * @return @~english Whether GL_SCISSOR_TEST is enable.
     * @~chinese 返回GL_SCISSOR_TEST 是否有效。
     */
    virtual bool isScissorEnabled();

    /**@~english
     * Get the current scissor rectangle.
     *
     * @~chinese 
     * 获取当前的裁剪的矩形。
     * 
     * @return @~english The current scissor rectangle.
     * @~chinese 当前裁剪的矩形
     */
    virtual Rect getScissorRect() const;

    /** @~english Set the view name. 
     *
     * @~chinese 设置视图名称。
     * 
     * @param viewname @~english A string will be set to the view as name.
     * @~chinese 一个给定的字符串将被设置为视图名称。
     */
    virtual void setViewName(const std::string& viewname);
    
    /** @~english Get the view name.
     *
     * @~chinese 获取视图名称。
     * 
     * @return @~english The view name.
     * @~chinese 返回视图的名称。
     */
    const std::string& getViewName() const;

    /** @~english Touch events are handled by default; if you want to customize your handlers, please override this function.
     *
     * @~chinese 默认处理触摸事件;如果你想定制处理程序,请重写这个函数。
     * 
     * @param num @~english The number of touch.
     * @~chinese 触摸的数量。
     * @param ids @~english The identity of the touch.
     * @~chinese 触摸的唯一标识
     * @param xs @~english The points of x.
     * @~chinese 触摸点的x坐标。
     * @param ys @~english The points of y.
     * @~chinese 触摸点的y坐标。
     */
    virtual void handleTouchesBegin(int num, intptr_t ids[], float xs[], float ys[]);
    
    /** @~english Touch events are handled by default; if you want to customize your handlers, please override this function.
     *
     * @~chinese 默认处理触摸事件;如果你想定制处理程序,请重写这个函数。
     * 
     * @param num @~english The number of touch.
     * @~chinese 触摸的数量。
     * @param ids @~english The identity of the touch.
     * @~chinese 触摸的唯一标识
     * @param xs @~english The points of x.
     * @~chinese 触摸点的x坐标。
     * @param ys @~english The points of y.
     * @~chinese 触摸点的y坐标。
     */
    virtual void handleTouchesMove(int num, intptr_t ids[], float xs[], float ys[]);
    
    /** @~english Touch events are handled by default; if you want to customize your handlers, please override this function.
     *
     * @~chinese 默认处理触摸事件;如果你想定制处理程序,请重写这个函数。
     * 
     * @param num @~english The number of touch.
     * @~chinese 触摸的数量。
     * @param ids @~english The identity of the touch.
     * @~chinese 触摸的唯一标识
     * @param xs @~english The points of x.
     * @~chinese 触摸点的x坐标。
     * @param ys @~english The points of y.
     * @~chinese 触摸点的y坐标。
     */
    virtual void handleTouchesEnd(int num, intptr_t ids[], float xs[], float ys[]);
    
    /** @~english Touch events are handled by default; if you want to customize your handlers, please override this function.
     *
     * @~chinese 默认处理触摸事件;如果你想定制处理程序,请重写这个函数。
     * 
     * @param num @~english The number of touch.
     * @~chinese 触摸的数量。
     * @param ids @~english The identity of the touch.
     * @~chinese 触摸的唯一标识
     * @param xs @~english The points of x.
     * @~chinese 触摸点的x坐标。
     * @param ys @~english The points of y.
     * @~chinese 触摸点的y坐标。
     */
    virtual void handleTouchesCancel(int num, intptr_t ids[], float xs[], float ys[]);

    /**@~english
     * Get the opengl view port rectangle.
     *
     * @~chinese 
     * 获取opengl视窗矩形。
     * 
     * @return @~english Return the opengl view port rectangle.
     * @~chinese 返回opengl视窗矩形。
     */
    const Rect& getViewPortRect() const;
    
    /**@~english
     * Get list of all active touches.
     *
     * @~chinese 
     * 获取所有激活的触摸列表。
     * 
     * @return @~english A list of all active touches.
     * @~chinese 所有激活的触摸列表。
     */
    std::vector<Touch*> getAllTouches() const;

    /**@~english
     * Get scale factor of the horizontal direction.
     *
     * @~chinese 
     * 得到水平方向的缩放系数。
     * 
     * @return @~english Scale factor of the horizontal direction.
     * @~chinese 水平方向的缩放系数。
     */
    float getScaleX() const;

    /**@~english
     * Get scale factor of the vertical direction.
     *
     * @~chinese 
     * 垂直方向的缩放系数。
     * 
     * @return @~english Scale factor of the vertical direction.
     * @~chinese 垂直方向的缩放系数。
     */
    float getScaleY() const;

    /** @~english Returns the current Resolution policy.
     *
     * @~chinese 返回当前的分辨率适配方案。
     * 
     * @return @~english The current Resolution policy.
     * @~chinese 当前的分辨率适配方案
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
