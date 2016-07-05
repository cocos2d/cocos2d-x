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

#ifndef __CC_EGLViewIMPL_EMSCRIPTEN_H__
#define __CC_EGLViewIMPL_EMSCRIPTEN_H__

#include "base/CCRef.h"
#include "platform/CCCommon.h"
#include "platform/CCGLView.h"

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

NS_CC_BEGIN

class CC_DLL GLViewImpl : public GLView
{
public:
	static GLViewImpl* create(const std::string& viewName);
	static GLViewImpl* createWithRect(const std::string& viewName, Rect size, float frameZoomFactor = 1.0f);
	static GLViewImpl* createWithFullScreen(const std::string& viewName);

	bool isOpenGLReady() override;
	void end() override;
	void swapBuffers() override;
	void pollEvents() override;
	void setIMEKeyboardState(bool bOpen) override;
    virtual void setFrameSize(float width, float height) override;
    
    float getFrameZoomFactor() const override;
    
    virtual void setViewPortInPoints(float x , float y , float w , float h) override;
    virtual void setScissorInPoints(float x , float y , float w , float h) override;
    virtual Rect getScissorRect() const override;
    
    void toggleToFullscreen();
    bool isFullscreen();

protected:
    GLViewImpl();
    virtual ~GLViewImpl();

    bool initWithRect(const std::string& viewName, Rect rect, float frameZoomFactor);
    bool initWithFullScreen(const std::string& viewName);
    
    void onMouseMoveCallBack(double x, double y);
    void onMouseCallBack(int button, int action, double x, double y);
    void onMouseScrollCallback(double x, double y);
    void onKeyCallback(int key, int action, int repeat);
    void onCharCallback(unsigned int character);
    
    static int EventHandler(void *userdata, SDL_Event *event);
    
private:
    SDL_Surface *_screenSurface = nullptr;
	bool _isGLInitialized = false;
    
    bool _captured = false;
    float _frameZoomFactor = 1.0f;
    
    int _windowWidth = 0;
    int _windowHeight = 0;
    
    int _defaultWindowWidth = 0;
    int _defaultWindowHeight = 0;
    int _windowFullscreen = 0;
    int _wheelScrollScale = 1;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(GLViewImpl);
};

NS_CC_END   // end of namespace   cocos2d

#endif  // end of __CC_EGLViewImpl_EMSCRIPTEN_H__
