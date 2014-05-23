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

#ifndef __CCGLVIEWPROTOCOL_H__
#define __CCGLVIEWPROTOCOL_H__

#include "base/ccTypes.h"
#include "base/CCEventTouch.h"

#include <vector>

enum class ResolutionPolicy
{
    //在指定的区域可以显示整个应用程序，并且不会保留它原始样子的比例。
    //所以可能发生变形，应用程序可能会被拉伸或者压缩
    EXACT_FIT,
    //整个应用程序填充指定的区域，不会发生变形但是可能会有剪切，同时保留应用程序原始样子的比例。
    NO_BORDER,
    //在指定的区域可以显示整个应用程序，同时保留应用程序原始样子的比例而不发生变形。但是应用程序的两侧可能会出现边框。
    SHOW_ALL,
    //程序取设计分辨率的高度，然后更改内部画布的宽度使程序适配设备的尺寸比例
    //不会发生变形，但是你必须确保你的程序可以运行在不同比例下
    FIXED_HEIGHT,
    //程序取设计分辨率的宽度，然后更改内部画布的高度使程序适配设备的尺寸比例
    //不会发生变形，但是你必须确保你的程序可以运行在不同比例下
    FIXED_WIDTH,

    UNKNOWN,
};

NS_CC_BEGIN

/**
 * @addtogroup platform
 * @{
 */

class CC_DLL GLViewProtocol
{
public:
    /**
     * @js ctor
     */
    GLViewProtocol();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~GLViewProtocol();

    /**强制销毁EGL视图，子类必须实现这个方法 */
    virtual void end() = 0;

    /** 获取OpenGL渲染系统是否就绪，子类必须实现这个方法 */
    virtual bool isOpenGLReady() = 0;

    /** 交换前后缓冲区，子类必须实现这个方法 */
    virtual void swapBuffers() = 0;

    /** 开启或者关闭键盘，子类必须实现这个方法*/
    virtual void setIMEKeyboardState(bool open) = 0;

    /**
     * 轮询输入事件。如果平台没有提供事件回调函数，子类必须实现这个方法
     */
    virtual void pollInputEvents();

    /**获取EGL视图的框架尺寸
     * 一般情况下，因为EGL视图是全屏视图，所以它会返回屏幕的尺寸
     */
    virtual const Size& getFrameSize() const;

    /**
     * 设置EGL 视图的框架尺寸
     */
    virtual void setFrameSize(float width, float height);

    /**
     * Get the visible area size of opengl viewport.
     */
    virtual Size getVisibleSize() const;

    /**
     * 获取OpenGL视口的可视原点
     */
    virtual Vec2 getVisibleOrigin() const;

    /**
     *获取OpenGL视口的可视矩形
     */
    virtual Rect getVisibleRect() const;

    /**
     * 设置设计分辨率尺寸
     * @param width 设计分辨率的宽度
     * @param height 设计分辨率的高度
     * @param resolutionPolicy 你选择的期望的分辨率规则：
     *                         [1] EXACT_FIT 伸展以适配屏幕: 如果你的设计分辨率的宽和高的比例与屏幕的分辨率的比例不同，你的游戏视图就会被拉伸。
     *                         [2] NO_BORDER 无边框适配屏幕: 如果你的设计分辨率的宽和高的比例与屏幕的分辨率的比例不同，你的游戏视图的两个区域将会被剪切。
     *                         [3] SHOW_ALL  有黑框适配屏幕: 如果你的设计分辨率的宽和高的比例与屏幕的分辨率的比例不同，两侧会出现两个黑色的边框。
     */
    virtual void setDesignResolutionSize(float width, float height, ResolutionPolicy resolutionPolicy);

    /** 获得设计分辨率的尺寸。
     *  默认的分辨率尺寸和 'getFrameSize'一样。
     */
    virtual const Size&  getDesignResolutionSize() const;

    /**
     * 通过点来设置OpenGL视口的矩形。
     */
    virtual void setViewPortInPoints(float x , float y , float w , float h);

    /**
     * 通过点来设置裁剪矩形。
     */
    virtual void setScissorInPoints(float x , float y , float w , float h);

    /**
     * 获取GL_SCISSOR_TEST 是否可用
     */
    virtual bool isScissorEnabled();

    /**
     * 获取当前的裁剪矩形。
     */
    virtual Rect getScissorRect() const;

    virtual void setViewName(const std::string& viewname);
    const std::string& getViewName() const;

    /** 通过默认的方式处理触摸事件; 如果你想自定义处理程序，可以重载下面的这些函数： */
    virtual void handleTouchesBegin(int num, intptr_t ids[], float xs[], float ys[]);
    virtual void handleTouchesMove(int num, intptr_t ids[], float xs[], float ys[]);
    virtual void handleTouchesEnd(int num, intptr_t ids[], float xs[], float ys[]);
    virtual void handleTouchesCancel(int num, intptr_t ids[], float xs[], float ys[]);

    /**
     * 获取OpenGL视口矩形。
     */
    const Rect& getViewPortRect() const;

    /**
     * 获取水平方向的缩放因子
     */
    float getScaleX() const;

    /**
     * 获取垂直方向的缩放因子
     */
    float getScaleY() const;

    /** 返回当前的分辨率适配规则*/
    ResolutionPolicy getResolutionPolicy() const { return _resolutionPolicy; }

protected:
    void updateDesignResolutionSize();
    
    void handleTouchesOfEndOrCancel(EventTouch::EventCode eventCode, int num, intptr_t ids[], float xs[], float ys[]);

    // 真正的屏幕尺寸
    Size _screenSize;
    // 分辨率尺寸。它是应用程序资源的适当的尺寸。
    Size _designResolutionSize;
    // 视口尺寸
    Rect _viewPortRect;
    // 视图的名字
    std::string _viewName;

    float _scaleX;
    float _scaleY;
    ResolutionPolicy _resolutionPolicy;
};

// end of platform group
/// @}

NS_CC_END

#endif /* __CCGLVIEWPROTOCOL_H__ */
