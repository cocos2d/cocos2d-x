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

#include "CCEGLView.h"
#include "CCGL.h"
#include "ccMacros.h"
#include "CCDirector.h"
#include "CCInstance.h"
#include "touch_dispatcher/CCTouch.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "text_input_node/CCIMEDispatcher.h"

#include "ppapi/c/ppb_opengles2.h"
#include "ppapi/cpp/graphics_3d.h"
#include "ppapi/cpp/graphics_3d_client.h"
#include "ppapi/cpp/size.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/completion_callback.h"
#include "ppapi/gles2/gl2ext_ppapi.h"

class OpenGLContext : public pp::Graphics3DClient
{
public:
    OpenGLContext(pp::Instance* instance, pp::Size size);
    ~OpenGLContext();

    virtual void Graphics3DContextLost()
    {
        assert(!"Unexpectedly lost graphics context");
    }

    bool MakeContextCurrent();
    void InvalidateContext();
    void ResizeContext(int width, int height);
    void FlushContext();
    pp::Size GetSize() { return m_size; }
private:
    pp::Size m_size;
    pp::Graphics3D m_graphics3d;
    const struct PPB_OpenGLES2* m_gles2_interface;
    pp::Instance* m_instance;
};

OpenGLContext::OpenGLContext(pp::Instance* instance, pp::Size size) :
   pp::Graphics3DClient(instance), m_size(size), m_instance(instance)
{
    pp::Module* module = pp::Module::Get();
    assert(module);
    m_gles2_interface = static_cast<const struct PPB_OpenGLES2*>(
            module->GetBrowserInterface(PPB_OPENGLES2_INTERFACE));
    assert(m_gles2_interface);
}

OpenGLContext::~OpenGLContext()
{
    CCLOG("OpenGLContext::~OpenGLContext");
    glSetCurrentContextPPAPI(0);
}

bool OpenGLContext::MakeContextCurrent()
{
    CCLOG("OpenGLContext::MakeContextCurrent %dx%d",
          m_size.width(), m_size.height());

    // Lazily create the Pepper context.
    if (m_graphics3d.is_null())
    {
        int32_t attribs[] = {
            PP_GRAPHICS3DATTRIB_ALPHA_SIZE, 8,
            PP_GRAPHICS3DATTRIB_DEPTH_SIZE, 24,
            PP_GRAPHICS3DATTRIB_STENCIL_SIZE, 8,
            PP_GRAPHICS3DATTRIB_SAMPLES, 0,
            PP_GRAPHICS3DATTRIB_SAMPLE_BUFFERS, 0,
            PP_GRAPHICS3DATTRIB_WIDTH, m_size.width(),
            PP_GRAPHICS3DATTRIB_HEIGHT, m_size.height(),
            PP_GRAPHICS3DATTRIB_NONE
        };
        m_graphics3d = pp::Graphics3D(m_instance, pp::Graphics3D(), attribs);
        if (m_graphics3d.is_null())
        {
            glSetCurrentContextPPAPI(0);
            return false;
        }
        bool rtn = m_instance->BindGraphics(m_graphics3d);
        assert(rtn && "BindGraphics failed");
        if (!rtn)
          return false;
    }

    CCLOG("glSetCurrentContextPPAPI: %p", m_graphics3d.pp_resource());
    glSetCurrentContextPPAPI(m_graphics3d.pp_resource());
    return true;
}

void OpenGLContext::InvalidateContext()
{
    CCLOG("InvalidateContext");
    glSetCurrentContextPPAPI(0);
}

void OpenGLContext::ResizeContext(int width, int height)
{
    CCLOG("OpenGLContext::ResizeContext %dx%d", width, height);
    m_size.SetSize(width, height);
    if (!m_graphics3d.is_null())
    {
        m_graphics3d.ResizeBuffers(width, height);
    }
}

void OpenGLContext::FlushContext()
{
    //CCLOG("OpenGLContext::FlushContext");
    m_graphics3d.SwapBuffers(pp::BlockUntilComplete());
}


NS_CC_BEGIN

CCEGLView::CCEGLView() : bIsInit(false), bIsMouseDown(false), m_fFrameZoomFactor(1.0f), m_context(NULL)
{
    CCLOG("CCEGLView::CCEGLView");
    pthread_mutex_init(&m_mutex, NULL);
    initGL();
}

CCEGLView::~CCEGLView()
{
}

void CCEGLView::setFrameSize(float width, float height)
{
    CCEGLViewProtocol::setFrameSize(width, height);
    if (m_context)
      m_context->ResizeContext(width, height);
}

void CCEGLView::setViewPortInPoints(float x , float y , float w , float h)
{
    glViewport((GLint)(x * m_fScaleX * m_fFrameZoomFactor+ m_obViewPortRect.origin.x * m_fFrameZoomFactor),
            (GLint)(y * m_fScaleY * m_fFrameZoomFactor + m_obViewPortRect.origin.y * m_fFrameZoomFactor),
            (GLsizei)(w * m_fScaleX * m_fFrameZoomFactor),
            (GLsizei)(h * m_fScaleY * m_fFrameZoomFactor));
}

void CCEGLView::setScissorInPoints(float x , float y , float w , float h)
{
    glScissor((GLint)(x * m_fScaleX * m_fFrameZoomFactor + m_obViewPortRect.origin.x * m_fFrameZoomFactor),
            (GLint)(y * m_fScaleY * m_fFrameZoomFactor + m_obViewPortRect.origin.y * m_fFrameZoomFactor),
            (GLsizei)(w * m_fScaleX * m_fFrameZoomFactor),
            (GLsizei)(h * m_fScaleY * m_fFrameZoomFactor));
}


bool CCEGLView::isOpenGLReady()
{
    return bIsInit;
}

void CCEGLView::end()
{
    delete this;
    exit(0);
}

void CCEGLView::swapBuffers()
{
    if (!bIsInit)
        return;

    m_context->FlushContext();
}

void CCEGLView::setIMEKeyboardState(bool bOpen)
{
}

bool CCEGLView::initGL()
{
    CCLOG("initGL: instance=%p", g_instance);
    assert(g_instance);
    assert(!m_context);
    const pp::Size& size = g_instance->Size();
    setFrameSize(size.width(), size.height());
    m_context = new OpenGLContext(g_instance, size);
    CCLOG("initGL: m_context=%p", m_context);
    bool rtn = m_context->MakeContextCurrent();
    CCLOG("MakeContextCurrent returned: %d", rtn);
    assert(rtn == true && "MakeContextCurrent failed");
    if (!rtn)
      return false;
    bIsInit = true;
    return true;
}

void CCEGLView::destroyGL()
{
    delete m_context;
    bIsInit = false;
    CCLOG("destroyGL");
}

CCEGLView* CCEGLView::sharedOpenGLView()
{
    static CCEGLView* s_pEglView = NULL;
    if (s_pEglView == NULL)
    {
        CCLOG("creating CCEGLView");
        s_pEglView = new CCEGLView();
    }
    return s_pEglView;
}

void CCEGLView::HandleMouseEvent(const pp::MouseInputEvent* event)
{
    pp::Point pos = event->GetPosition();
    float x = pos.x();
    float y = pos.y();
    int touchID = 1;

    // Clamp event position to be within cocos2dx window size
    CCSize frame_size = getFrameSize();
    float max_y = frame_size.height;
    float max_x = frame_size.width;

    if (x < 0)
      x = 0;
    if (y < 0)
      y = 0;
    if (y > max_y)
      y = max_y;
    if (x > max_x)
      x = max_x;

    switch (event->GetType())
    {
        case PP_INPUTEVENT_TYPE_MOUSEDOWN:
            handleTouchesBegin(1, &touchID, &x, &y);
            bIsMouseDown = true;
            break;
        case PP_INPUTEVENT_TYPE_MOUSEUP:
            handleTouchesEnd(1, &touchID, &x, &y);
            bIsMouseDown = false;
            break;
        case PP_INPUTEVENT_TYPE_MOUSEMOVE:
            if (bIsMouseDown)
                handleTouchesMove(1, &touchID, &x, &y);
            break;
        default:
            break;
    }
}

void CCEGLView::ProcessEventQueue()
{
    const pp::Size& size = g_instance->Size();
    // If the size of the global instance has changed then
    // we need to update our GL frame size accordingly
    if (size != m_context->GetSize())
    {
        setFrameSize(size.width(), size.height());
    }

    pthread_mutex_lock(&m_mutex);
    while (m_event_queue.size())
    {
        pp::InputEvent event = m_event_queue.front();
        m_event_queue.pop();
        PP_InputEvent_Type type = event.GetType();
        switch (type)
        {
            case PP_INPUTEVENT_TYPE_KEYDOWN:
                CCLOG("got KEYDOWN");
                break;
            case PP_INPUTEVENT_TYPE_KEYUP:
                CCLOG("got KEYUP");
                break;
            case PP_INPUTEVENT_TYPE_CHAR:
                CCLOG("got KEYCHAR");
                break;
            case PP_INPUTEVENT_TYPE_MOUSEENTER:
                CCLOG("got MOUSEENTER");
                break;
            case PP_INPUTEVENT_TYPE_MOUSELEAVE:
                CCLOG("got MOUSELEAVE");
                break;
            case PP_INPUTEVENT_TYPE_MOUSEDOWN:
            case PP_INPUTEVENT_TYPE_MOUSEUP:
            case PP_INPUTEVENT_TYPE_MOUSEMOVE:
                {
                    const pp::MouseInputEvent* mevent =
                        reinterpret_cast<const pp::MouseInputEvent*>(&event);
                    HandleMouseEvent(mevent);
                    break;
                }
            default:
                CCLOG("unhandled event type: %d", type);
                break;
        }
    }
    pthread_mutex_unlock(&m_mutex);
}

void CCEGLView::AddEvent(const pp::InputEvent& event)
{
    pthread_mutex_lock(&m_mutex);
    m_event_queue.push(event);
    pthread_mutex_unlock(&m_mutex);
}

CocosPepperInstance* CCEGLView::g_instance;

NS_CC_END
