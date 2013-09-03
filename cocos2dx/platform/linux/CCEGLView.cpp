/*
 * EGLViewlinux.cpp
 *
 *  Created on: Aug 8, 2011
 *      Author: laschweinski
 */

#include "CCEGLView.h"
#include "CCGL.h"
#include "ccMacros.h"
#include "CCDirector.h"
#include "event_dispatcher/CCTouch.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "text_input_node/CCIMEDispatcher.h"
#include "event_dispatcher/CCEventDispatcher.h"
#include "event_dispatcher/CCKeyboardEvent.h"
#include <unistd.h>

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
    KeyboardEvent event;
    event.keyCode = key;
    event.isPressed = (GLFW_PRESS == action);
    EventDispatcher::getInstance()->dispatchEvent(event);
}

void EGLViewEventHandler::OnGLFWCharCallback(GLFWwindow *window, unsigned int character)
{
    IMEDispatcher::sharedDispatcher()->dispatchInsertText((const char*) &character, 1);
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
    glfwTerminate();
    s_pEglView = nullptr;
}

bool EGLView::init(const char* viewName, float width, float height)
{
    if(nullptr != _mainWindow) return true;

    setViewName(viewName);
    setFrameSize(width, height);

    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
    _mainWindow = glfwCreateWindow(_screenSize.width, _screenSize.height, _viewName, nullptr, nullptr);
    glfwMakeContextCurrent(_mainWindow);
    glfwSetMouseButtonCallback(_mainWindow,EGLViewEventHandler::OnGLFWMouseCallBack);
    glfwSetCursorPosCallback(_mainWindow,EGLViewEventHandler::OnGLFWMouseMoveCallBack);
    glfwSetCharCallback(_mainWindow, EGLViewEventHandler::OnGLFWCharCallback);
    glfwSetKeyCallback(_mainWindow, EGLViewEventHandler::OnGLFWKeyCallback);
    
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
    
    GLenum GlewInitResult = glewInit();
    if (GLEW_OK != GlewInitResult)
    {
        MessageBox((char *)glewGetErrorString(GlewInitResult), "OpenGL error");
        return false;
    }
    
    if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
    {
        log("Ready for GLSL");
    }
    else
    {
        log("Not totally ready :(");
    }
    
    if (glewIsSupported("GL_VERSION_2_0"))
    {
       log("Ready for OpenGL 2.0");
    }
    else
    {
        log("OpenGL 2.0 not supported");
    }
    
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
    glViewport((GLint)(x * _scaleX * _frameZoomFactor + _viewPortRect.origin.x * _frameZoomFactor),
               (GLint)(y * _scaleY  * _frameZoomFactor + _viewPortRect.origin.y * _frameZoomFactor),
               (GLsizei)(w * _scaleX * _frameZoomFactor),
               (GLsizei)(h * _scaleY * _frameZoomFactor));
}

void EGLView::setScissorInPoints(float x , float y , float w , float h)
{
    glScissor((GLint)(x * _scaleX * _frameZoomFactor + _viewPortRect.origin.x * _frameZoomFactor),
              (GLint)(y * _scaleY * _frameZoomFactor + _viewPortRect.origin.y * _frameZoomFactor),
              (GLsizei)(w * _scaleX * _frameZoomFactor),
              (GLsizei)(h * _scaleY * _frameZoomFactor));
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

NS_CC_END
