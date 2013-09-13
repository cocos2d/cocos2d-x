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
#include "CCEGLView.h"
#include "EAGLView.h"
#include "CCDirector.h"
#include "CCSet.h"
#include "CCTouch.h"
#include "CCTouchDispatcher.h"
#include "CCKeyboardDispatcher.h"
#include "CCIMEDispatcher.h"

NS_CC_BEGIN

//begin EGLViewEventHandler
class EGLViewEventHandler
{
public:
    static bool s_captured;
    static float s_mouseX;
    static float s_mouseY;
    
    static void OnGLFWError(int errorID, const char* errorDesc);
    static void OnGLFWMouseCallBack(GLFWwindow* window, int button, int action, int modify);
    static void OnGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y);
    static void OnGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void OnGLFWCharCallback(GLFWwindow* window, unsigned int character);
    static void OnGLFWWindowPosCallback(GLFWwindow* windows, int x, int y);
};

bool EGLViewEventHandler::s_captured = false;
float EGLViewEventHandler::s_mouseX = 0;
float EGLViewEventHandler::s_mouseY = 0;

void EGLViewEventHandler::OnGLFWError(int errorID, const char* errorDesc)
{
    CCLOGERROR("GLFWError #%d Happen, %s\n", errorID, errorDesc);
}

void EGLViewEventHandler::OnGLFWMouseCallBack(GLFWwindow* window, int button, int action, int modify)
{
    EGLView* eglView = EGLView::getInstance();
    if(nullptr == eglView) return;
    if(GLFW_MOUSE_BUTTON_LEFT == button)
    {
        if(GLFW_PRESS == action)
        {
            s_captured = true;
            if (eglView->getViewPortRect().equals(Rect::ZERO) || eglView->getViewPortRect().containsPoint(Point(s_mouseX,s_mouseY)))
            {
                int id = 0;
                eglView->handleTouchesBegin(1, &id, &s_mouseX, &s_mouseY);
            }
        }
        else if(GLFW_RELEASE == action)
        {
            s_captured = false;
            if (eglView->getViewPortRect().equals(Rect::ZERO) || eglView->getViewPortRect().containsPoint(Point(s_mouseX,s_mouseY)))
            {
                int id = 0;
                eglView->handleTouchesEnd(1, &id, &s_mouseX, &s_mouseY);
            }
        }
    }
}

void EGLViewEventHandler::OnGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y)
{
    s_mouseX = (float)x;
    s_mouseY = (float)y;
    EGLView* eglView = EGLView::getInstance();
    if(nullptr == eglView) return;
    
    s_mouseX /= eglView->getFrameZoomFactor();
    s_mouseY /= eglView->getFrameZoomFactor();
    
    if(s_captured)
    {
        if (eglView->getViewPortRect().equals(Rect::ZERO) || eglView->getViewPortRect().containsPoint(Point(s_mouseX,eglView->getFrameSize().height - s_mouseY)))
        {
            int id = 0;
            eglView->handleTouchesMove(1, &id, &s_mouseX, &s_mouseY);
        }
    }
}

void EGLViewEventHandler::OnGLFWKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if(GLFW_PRESS == action)
    {
        Director::getInstance()->getKeyboardDispatcher()->dispatchKeyboardEvent(key, true);
    }
    else if(GLFW_RELEASE == action)
    {
        Director::getInstance()->getKeyboardDispatcher()->dispatchKeyboardEvent(key,false);
    }
}

void EGLViewEventHandler::OnGLFWCharCallback(GLFWwindow *window, unsigned int character)
{
    IMEDispatcher::sharedDispatcher()->dispatchInsertText((const char*) &character, 1);
}

void EGLViewEventHandler::OnGLFWWindowPosCallback(GLFWwindow *windows, int x, int y)
{
    if(Director::getInstance())
    {
        Director::getInstance()->setViewport();
    }
}

//end EGLViewEventHandler


//////////////////////////////////////////////////////////////////////////
// impliment EGLView
//////////////////////////////////////////////////////////////////////////

EGLView* EGLView::s_pEglView = nullptr;

EGLView::EGLView()
: _captured(false)
, _frameZoomFactor(1.0f)
, _supportTouch(false)
, _mainWindow(nullptr)
{
    CCASSERT(nullptr == s_pEglView, "EGLView is singleton, Should be inited only one time\n");
    s_pEglView = this;
    strcpy(_viewName, "Cocos2dxWin32");
    glfwSetErrorCallback(EGLViewEventHandler::OnGLFWError);
    glfwInit();
}

EGLView::~EGLView()
{
    CCLOGINFO("deallocing EGLView: %p", this);
    glfwTerminate();
    s_pEglView = nullptr;
}

bool EGLView::init(const char *viewName, float width, float height, float frameZoomFactor)
{
    if(nullptr != _mainWindow) return true;
    
    setViewName(viewName);
    setFrameSize(width, height);
    setFrameZoomFactor(frameZoomFactor);
    
    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
    _mainWindow = glfwCreateWindow(_screenSize.width * _frameZoomFactor, _screenSize.height * _frameZoomFactor, _viewName, nullptr, nullptr);
    glfwMakeContextCurrent(_mainWindow);
    
    glfwGetFramebufferSize(_mainWindow, &_frameBufferSize[0], &_frameBufferSize[1]);
    
    glfwSetMouseButtonCallback(_mainWindow,EGLViewEventHandler::OnGLFWMouseCallBack);
    glfwSetCursorPosCallback(_mainWindow,EGLViewEventHandler::OnGLFWMouseMoveCallBack);
    glfwSetCharCallback(_mainWindow, EGLViewEventHandler::OnGLFWCharCallback);
    glfwSetKeyCallback(_mainWindow, EGLViewEventHandler::OnGLFWKeyCallback);
    glfwSetWindowPosCallback(_mainWindow, EGLViewEventHandler::OnGLFWWindowPosCallback);
    
    // check OpenGL version at first
    const GLubyte* glVersion = glGetString(GL_VERSION);
    CCLOG("OpenGL version = %s", glVersion);
    
    if ( atof((const char*)glVersion) < 1.5 )
    {
        char strComplain[256] = {0};
        sprintf(strComplain,
                "OpenGL 1.5 or higher is required (your version is %s). Please upgrade the driver of your video card.",
                glVersion);
        MessageBox(strComplain, "OpenGL version too old");
        return false;
    }
//    
//    GLenum GlewInitResult = glewInit();
//    if (GLEW_OK != GlewInitResult)
//    {
//        MessageBox((char *)glewGetErrorString(GlewInitResult), "OpenGL error");
//        return false;
//    }
//    
//    if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
//    {
//        log("Ready for GLSL");
//    }
//    else
//    {
//        log("Not totally ready :(");
//    }
//    
//    if (glewIsSupported("GL_VERSION_2_0"))
//    {
//        log("Ready for OpenGL 2.0");
//    }
//    else
//    {
//        log("OpenGL 2.0 not supported");
//    }
//    
//    if(glew_dynamic_binding() == false)
//    {
//        MessageBox("No OpenGL framebuffer support. Please upgrade the driver of your video card.", "OpenGL error");
//        return false;
//    }
//    
    // Enable point size by default on windows.
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    
    return true;
}

bool EGLView::isOpenGLReady()
{
    return nullptr != _mainWindow;
}

void EGLView::end()
{
    if(_mainWindow)
        glfwSetWindowShouldClose(_mainWindow,1);
}

void EGLView::swapBuffers()
{
    if(_mainWindow)
        glfwSwapBuffers(_mainWindow);
}

bool EGLView::windowShouldClose()
{
    if(_mainWindow)
        return glfwWindowShouldClose(_mainWindow);
    else
        return true;
}

void EGLView::pollEvents()
{
    glfwPollEvents();
}

void EGLView::setIMEKeyboardState(bool /*bOpen*/)
{
    
}

void EGLView::setFrameZoomFactor(float fZoomFactor)
{
    _frameZoomFactor = fZoomFactor;
    Director::getInstance()->setProjection(Director::getInstance()->getProjection());
}

float EGLView::getFrameZoomFactor()
{
    return _frameZoomFactor;
}

void EGLView::setFrameSize(float width, float height)
{
    EGLViewProtocol::setFrameSize(width, height);
}

void EGLView::setViewPortInPoints(float x , float y , float w , float h)
{
    float frameZoomFactorX = _frameBufferSize[0]/_screenSize.width;
    float frameZoomFactorY = _frameBufferSize[1]/_screenSize.height;
    glViewport((GLint)(x * _scaleX * frameZoomFactorX + _viewPortRect.origin.x * frameZoomFactorX),
               (GLint)(y * _scaleY  * frameZoomFactorY + _viewPortRect.origin.y * frameZoomFactorY),
               (GLsizei)(w * _scaleX * frameZoomFactorX),
               (GLsizei)(h * _scaleY * frameZoomFactorY));
}

void EGLView::setScissorInPoints(float x , float y , float w , float h)
{
    float frameZoomFactorX = _frameBufferSize[0]/_screenSize.width;
    float frameZoomFactorY = _frameBufferSize[1]/_screenSize.height;
    glScissor((GLint)(x * _scaleX * frameZoomFactorX + _viewPortRect.origin.x * frameZoomFactorX),
               (GLint)(y * _scaleY  * frameZoomFactorY + _viewPortRect.origin.y * frameZoomFactorY),
               (GLsizei)(w * _scaleX * frameZoomFactorX),
               (GLsizei)(h * _scaleY * frameZoomFactorY));
}

EGLView* EGLView::getInstance()
{
    CCASSERT(nullptr != s_pEglView, "EGL singleton should not be null");
    return s_pEglView;
}

// XXX: deprecated
EGLView* EGLView::sharedOpenGLView()
{
    return EGLView::getInstance();
}

NS_CC_END // end of namespace cocos2d;
