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

#ifndef __CC_EGLVIEW_DESKTOP_H__
#define __CC_EGLVIEW_DESKTOP_H__

#include "base/CCRef.h"
#include "2d/platform/CCCommon.h"
#include "2d/platform/CCGLViewProtocol.h"
#include "glfw3.h"

NS_CC_BEGIN

class CC_DLL GLView : public GLViewProtocol, public Ref
{
public:
    static GLView* create(const std::string& viewName);
    static GLView* createWithRect(const std::string& viewName, Rect size, float frameZoomFactor = 1.0f);
    static GLView* createWithFullScreen(const std::string& viewName);
    static GLView* createWithFullScreen(const std::string& viewName, const GLFWvidmode &videoMode, GLFWmonitor *monitor);

    /*
     *帧缩放因子。这个函数是用来调试桌面版的大分辨率的（如：ipad）应用程序
     */

    //void resize(int width, int height);

    float getFrameZoomFactor();
    //void centerWindow();

    virtual void setViewPortInPoints(float x , float y , float w , float h);
    virtual void setScissorInPoints(float x , float y , float w , float h);


    bool windowShouldClose();
    void pollEvents();
    GLFWwindow* getWindow() const { return _mainWindow; }

    /* 重载函数 */
    virtual bool isOpenGLReady() override;
    virtual void end() override;
    virtual void swapBuffers() override;
    virtual void setFrameSize(float width, float height) override;
    virtual void setIMEKeyboardState(bool bOpen) override;

    /*
     *设置帧缩放因子。这个函数是用来调试桌面版的大分辨率应用程序（如：iPad）
     */
    void setFrameZoomFactor(float zoomFactor);

    /** 默认情况下Retina支持是不可用的
     *  @note 这个函数只能在Mac平台上使用.
     */
    void enableRetina(bool enabled);
    /** 检查是否支持retina display */
    bool isRetinaEnabled() { return _isRetinaEnabled; };

protected:
    GLView();
    virtual ~GLView();

    bool initWithRect(const std::string& viewName, Rect rect, float frameZoomFactor);
    bool initWithFullScreen(const std::string& viewName);
    bool initWithFullscreen(const std::string& viewname, const GLFWvidmode &videoMode, GLFWmonitor *monitor);

    bool initGlew();

    void updateFrameSize();

    // GLFW 回调函数
    void onGLFWError(int errorID, const char* errorDesc);
    void onGLFWMouseCallBack(GLFWwindow* window, int button, int action, int modify);
    void onGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y);
    void onGLFWMouseScrollCallback(GLFWwindow* window, double x, double y);
    void onGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void onGLFWCharCallback(GLFWwindow* window, unsigned int character);
    void onGLFWWindowPosCallback(GLFWwindow* windows, int x, int y);
    void onGLFWframebuffersize(GLFWwindow* window, int w, int h);
    void onGLFWWindowSizeFunCallback(GLFWwindow *window, int width, int height);

    bool _captured;
    bool _supportTouch;
    bool _isInRetinaMonitor;
    bool _isRetinaEnabled;
    int  _retinaFactor;  // 值应该是1或者2

    float _frameZoomFactor;

    GLFWwindow* _mainWindow;
    GLFWmonitor* _monitor;

    float _mouseX;
    float _mouseY;

    friend class GLFWEventHandler;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(GLView);
};

NS_CC_END   // end of namespace   cocos2d

#endif  // end of __CC_EGLVIEW_DESKTOP_H__
