/****************************************************************************
Copyright (c) 2013 The Chromium Authors

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

#ifndef __CCEGLVIEW_H__
#define __CCEGLVIEW_H__

#include "platform/CCCommon.h"
#include "cocoa/CCGeometry.h"
#include "platform/CCEGLViewProtocol.h"
#include "ppapi/cpp/input_event.h"
#include <pthread.h>
#include <queue>


bool initExtensions();

class OpenGLContext;
class CocosPepperInstance;

NS_CC_BEGIN

class CCEGLView : public CCEGLViewProtocol
{
public:
    CCEGLView();
    virtual ~CCEGLView();

    /**
     * iPixelWidth, height: the window's size
     * iWidth ,height: the point size, which may scale.
     * iDepth is not the buffer depth of opengl, it indicate how may bits for a pixel
     */
    virtual void setFrameSize(float width, float height);
    virtual void setViewPortInPoints(float x , float y , float w , float h);
    virtual void setScissorInPoints(float x , float y , float w , float h);

    /*
     * Set zoom factor for frame. This method is for debugging big resolution (e.g.new ipad) app on desktop.
     */
    virtual bool isOpenGLReady();
    virtual void end();
    virtual void swapBuffers();
    virtual void setIMEKeyboardState(bool bOpen);

    void addEvent();
    void ProcessEventQueue();
    void AddEvent(const pp::InputEvent& event);

    /**
     @brief get the shared main open gl window
     */
    static CCEGLView* sharedOpenGLView();
    static CocosPepperInstance* g_instance;
private:
    void HandleMouseEvent(const pp::MouseInputEvent* event);
    bool initGL();
    void destroyGL();
    bool bIsInit;
    bool bIsMouseDown;
    float m_fFrameZoomFactor;
    OpenGLContext* m_context;
    std::queue<pp::InputEvent> m_event_queue;
    pthread_mutex_t m_mutex;
};

NS_CC_END

#endif /* __CCEGLVIEW_H__ */
