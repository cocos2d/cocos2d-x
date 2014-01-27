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

#include "platform/CCCommon.h"
#include "platform/CCEGLViewProtocol.h"
#include "glfw3.h"

NS_CC_BEGIN

class CC_DLL EGLView : public EGLViewProtocol
{
public:
    // static function
    /**
     @brief    get the shared main open gl window
     */
    static EGLView* getInstance();

    /** @deprecated Use getInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static EGLView* sharedOpenGLView();

    /**
     * @js ctor
     */
    EGLView();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~EGLView();
    
    /* override functions */
    virtual bool isOpenGLReady();
    virtual void end();
    virtual void swapBuffers();
    virtual void setFrameSize(float width, float height);
    virtual void setIMEKeyboardState(bool bOpen);
    /*
     *frameZoomFactor for frame. This method is for debugging big resolution (e.g.new ipad) app on desktop.
     */
    bool init(const std::string& viewName, float width, float height, float frameZoomFactor = 1.0f);
    bool initWithFullScreen(const std::string& viewName);

    //void resize(int width, int height);
 
	float getFrameZoomFactor();
    //void centerWindow();

    
    virtual void setViewPortInPoints(float x , float y , float w , float h);
    virtual void setScissorInPoints(float x , float y , float w , float h);


    bool windowShouldClose();
    void pollEvents();
    GLFWwindow* getWindow() const { return _mainWindow; }

protected:
    /*
     * Set zoom factor for frame. This method is for debugging big resolution (e.g.new ipad) app on desktop.
     */
    void setFrameZoomFactor(float zoomFactor);
    bool initGlew();
    inline bool isRetina() { return _isRetina; };

    bool _captured;
    bool _supportTouch;
    bool _isRetina;

    float _frameZoomFactor;
    static EGLView* s_pEglView;

    GLFWwindow* _mainWindow;
    GLFWmonitor* _primaryMonitor;
    friend class EGLViewEventHandler;
};

NS_CC_END   // end of namespace   cocos2d

#endif	// end of __CC_EGLVIEW_DESKTOP_H__
