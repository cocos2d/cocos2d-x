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

#include "CCGLViewImpl-desktop.h"

#include <unordered_map>

#include "platform/CCApplication.h"
#include "base/CCDirector.h"
#include "base/CCTouch.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventKeyboard.h"
#include "base/CCEventMouse.h"
#include "base/CCIMEDispatcher.h"
#include "base/ccUtils.h"
#include "base/ccUTF8.h"


NS_CC_BEGIN

// GLFWEventHandler

class GLFWEventHandler
{
public:
    static void onGLFWError(int errorID, const char* errorDesc)
    {
        if (_view)
            _view->onGLFWError(errorID, errorDesc);
    }

    static void onGLFWMouseCallBack(GLFWwindow* window, int button, int action, int modify)
    {
        if (_view)
            _view->onGLFWMouseCallBack(window, button, action, modify);
    }

    static void onGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y)
    {
        if (_view)
            _view->onGLFWMouseMoveCallBack(window, x, y);
    }

    static void onGLFWMouseScrollCallback(GLFWwindow* window, double x, double y)
    {
        if (_view)
            _view->onGLFWMouseScrollCallback(window, x, y);
    }

    static void onGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (_view)
            _view->onGLFWKeyCallback(window, key, scancode, action, mods);
    }

    static void onGLFWCharCallback(GLFWwindow* window, unsigned int character)
    {
        if (_view)
            _view->onGLFWCharCallback(window, character);
    }

    static void onGLFWWindowPosCallback(GLFWwindow* windows, int x, int y)
    {
        if (_view)
            _view->onGLFWWindowPosCallback(windows, x, y);
    }

    static void onGLFWframebuffersize(GLFWwindow* window, int w, int h)
    {
        if (_view)
            _view->onGLFWframebuffersize(window, w, h);
    }

    static void onGLFWWindowSizeFunCallback(GLFWwindow *window, int width, int height)
    {
        if (_view)
            _view->onGLFWWindowSizeFunCallback(window, width, height);
    }

    static void setGLViewImpl(GLViewImpl* view)
    {
        _view = view;
    }

    static void onGLFWWindowIconifyCallback(GLFWwindow* window, int iconified)
    {
        if (_view)
        {
            _view->onGLFWWindowIconifyCallback(window, iconified);
        }
    }

private:
    static GLViewImpl* _view;
};

GLViewImpl* GLFWEventHandler::_view = nullptr;

////////////////////////////////////////////////////

struct keyCodeItem
{
    int glfwKeyCode;
    EventKeyboard::KeyCode keyCode;
};

static std::unordered_map<int, EventKeyboard::KeyCode> g_keyCodeMap;

static keyCodeItem g_keyCodeStructArray[] = {
    /* The unknown key */
    { GLFW_KEY_UNKNOWN         , EventKeyboard::KeyCode::KEY_NONE          },

    /* Printable keys */
    { GLFW_KEY_SPACE           , EventKeyboard::KeyCode::KEY_SPACE         },
    { GLFW_KEY_APOSTROPHE      , EventKeyboard::KeyCode::KEY_APOSTROPHE    },
    { GLFW_KEY_COMMA           , EventKeyboard::KeyCode::KEY_COMMA         },
    { GLFW_KEY_MINUS           , EventKeyboard::KeyCode::KEY_MINUS         },
    { GLFW_KEY_PERIOD          , EventKeyboard::KeyCode::KEY_PERIOD        },
    { GLFW_KEY_SLASH           , EventKeyboard::KeyCode::KEY_SLASH         },
    { GLFW_KEY_0               , EventKeyboard::KeyCode::KEY_0             },
    { GLFW_KEY_1               , EventKeyboard::KeyCode::KEY_1             },
    { GLFW_KEY_2               , EventKeyboard::KeyCode::KEY_2             },
    { GLFW_KEY_3               , EventKeyboard::KeyCode::KEY_3             },
    { GLFW_KEY_4               , EventKeyboard::KeyCode::KEY_4             },
    { GLFW_KEY_5               , EventKeyboard::KeyCode::KEY_5             },
    { GLFW_KEY_6               , EventKeyboard::KeyCode::KEY_6             },
    { GLFW_KEY_7               , EventKeyboard::KeyCode::KEY_7             },
    { GLFW_KEY_8               , EventKeyboard::KeyCode::KEY_8             },
    { GLFW_KEY_9               , EventKeyboard::KeyCode::KEY_9             },
    { GLFW_KEY_SEMICOLON       , EventKeyboard::KeyCode::KEY_SEMICOLON     },
    { GLFW_KEY_EQUAL           , EventKeyboard::KeyCode::KEY_EQUAL         },
    { GLFW_KEY_A               , EventKeyboard::KeyCode::KEY_A             },
    { GLFW_KEY_B               , EventKeyboard::KeyCode::KEY_B             },
    { GLFW_KEY_C               , EventKeyboard::KeyCode::KEY_C             },
    { GLFW_KEY_D               , EventKeyboard::KeyCode::KEY_D             },
    { GLFW_KEY_E               , EventKeyboard::KeyCode::KEY_E             },
    { GLFW_KEY_F               , EventKeyboard::KeyCode::KEY_F             },
    { GLFW_KEY_G               , EventKeyboard::KeyCode::KEY_G             },
    { GLFW_KEY_H               , EventKeyboard::KeyCode::KEY_H             },
    { GLFW_KEY_I               , EventKeyboard::KeyCode::KEY_I             },
    { GLFW_KEY_J               , EventKeyboard::KeyCode::KEY_J             },
    { GLFW_KEY_K               , EventKeyboard::KeyCode::KEY_K             },
    { GLFW_KEY_L               , EventKeyboard::KeyCode::KEY_L             },
    { GLFW_KEY_M               , EventKeyboard::KeyCode::KEY_M             },
    { GLFW_KEY_N               , EventKeyboard::KeyCode::KEY_N             },
    { GLFW_KEY_O               , EventKeyboard::KeyCode::KEY_O             },
    { GLFW_KEY_P               , EventKeyboard::KeyCode::KEY_P             },
    { GLFW_KEY_Q               , EventKeyboard::KeyCode::KEY_Q             },
    { GLFW_KEY_R               , EventKeyboard::KeyCode::KEY_R             },
    { GLFW_KEY_S               , EventKeyboard::KeyCode::KEY_S             },
    { GLFW_KEY_T               , EventKeyboard::KeyCode::KEY_T             },
    { GLFW_KEY_U               , EventKeyboard::KeyCode::KEY_U             },
    { GLFW_KEY_V               , EventKeyboard::KeyCode::KEY_V             },
    { GLFW_KEY_W               , EventKeyboard::KeyCode::KEY_W             },
    { GLFW_KEY_X               , EventKeyboard::KeyCode::KEY_X             },
    { GLFW_KEY_Y               , EventKeyboard::KeyCode::KEY_Y             },
    { GLFW_KEY_Z               , EventKeyboard::KeyCode::KEY_Z             },
    { GLFW_KEY_LEFT_BRACKET    , EventKeyboard::KeyCode::KEY_LEFT_BRACKET  },
    { GLFW_KEY_BACKSLASH       , EventKeyboard::KeyCode::KEY_BACK_SLASH    },
    { GLFW_KEY_RIGHT_BRACKET   , EventKeyboard::KeyCode::KEY_RIGHT_BRACKET },
    { GLFW_KEY_GRAVE_ACCENT    , EventKeyboard::KeyCode::KEY_GRAVE         },
    { GLFW_KEY_WORLD_1         , EventKeyboard::KeyCode::KEY_GRAVE         },
    { GLFW_KEY_WORLD_2         , EventKeyboard::KeyCode::KEY_NONE          },

    /* Function keys */
    { GLFW_KEY_ESCAPE          , EventKeyboard::KeyCode::KEY_ESCAPE        },
    { GLFW_KEY_ENTER           , EventKeyboard::KeyCode::KEY_KP_ENTER      },
    { GLFW_KEY_TAB             , EventKeyboard::KeyCode::KEY_TAB           },
    { GLFW_KEY_BACKSPACE       , EventKeyboard::KeyCode::KEY_BACKSPACE     },
    { GLFW_KEY_INSERT          , EventKeyboard::KeyCode::KEY_INSERT        },
    { GLFW_KEY_DELETE          , EventKeyboard::KeyCode::KEY_DELETE        },
    { GLFW_KEY_RIGHT           , EventKeyboard::KeyCode::KEY_RIGHT_ARROW   },
    { GLFW_KEY_LEFT            , EventKeyboard::KeyCode::KEY_LEFT_ARROW    },
    { GLFW_KEY_DOWN            , EventKeyboard::KeyCode::KEY_DOWN_ARROW    },
    { GLFW_KEY_UP              , EventKeyboard::KeyCode::KEY_UP_ARROW      },
    { GLFW_KEY_PAGE_UP         , EventKeyboard::KeyCode::KEY_KP_PG_UP      },
    { GLFW_KEY_PAGE_DOWN       , EventKeyboard::KeyCode::KEY_KP_PG_DOWN    },
    { GLFW_KEY_HOME            , EventKeyboard::KeyCode::KEY_KP_HOME       },
    { GLFW_KEY_END             , EventKeyboard::KeyCode::KEY_END           },
    { GLFW_KEY_CAPS_LOCK       , EventKeyboard::KeyCode::KEY_CAPS_LOCK     },
    { GLFW_KEY_SCROLL_LOCK     , EventKeyboard::KeyCode::KEY_SCROLL_LOCK   },
    { GLFW_KEY_NUM_LOCK        , EventKeyboard::KeyCode::KEY_NUM_LOCK      },
    { GLFW_KEY_PRINT_SCREEN    , EventKeyboard::KeyCode::KEY_PRINT         },
    { GLFW_KEY_PAUSE           , EventKeyboard::KeyCode::KEY_PAUSE         },
    { GLFW_KEY_F1              , EventKeyboard::KeyCode::KEY_F1            },
    { GLFW_KEY_F2              , EventKeyboard::KeyCode::KEY_F2            },
    { GLFW_KEY_F3              , EventKeyboard::KeyCode::KEY_F3            },
    { GLFW_KEY_F4              , EventKeyboard::KeyCode::KEY_F4            },
    { GLFW_KEY_F5              , EventKeyboard::KeyCode::KEY_F5            },
    { GLFW_KEY_F6              , EventKeyboard::KeyCode::KEY_F6            },
    { GLFW_KEY_F7              , EventKeyboard::KeyCode::KEY_F7            },
    { GLFW_KEY_F8              , EventKeyboard::KeyCode::KEY_F8            },
    { GLFW_KEY_F9              , EventKeyboard::KeyCode::KEY_F9            },
    { GLFW_KEY_F10             , EventKeyboard::KeyCode::KEY_F10           },
    { GLFW_KEY_F11             , EventKeyboard::KeyCode::KEY_F11           },
    { GLFW_KEY_F12             , EventKeyboard::KeyCode::KEY_F12           },
    { GLFW_KEY_F13             , EventKeyboard::KeyCode::KEY_NONE          },
    { GLFW_KEY_F14             , EventKeyboard::KeyCode::KEY_NONE          },
    { GLFW_KEY_F15             , EventKeyboard::KeyCode::KEY_NONE          },
    { GLFW_KEY_F16             , EventKeyboard::KeyCode::KEY_NONE          },
    { GLFW_KEY_F17             , EventKeyboard::KeyCode::KEY_NONE          },
    { GLFW_KEY_F18             , EventKeyboard::KeyCode::KEY_NONE          },
    { GLFW_KEY_F19             , EventKeyboard::KeyCode::KEY_NONE          },
    { GLFW_KEY_F20             , EventKeyboard::KeyCode::KEY_NONE          },
    { GLFW_KEY_F21             , EventKeyboard::KeyCode::KEY_NONE          },
    { GLFW_KEY_F22             , EventKeyboard::KeyCode::KEY_NONE          },
    { GLFW_KEY_F23             , EventKeyboard::KeyCode::KEY_NONE          },
    { GLFW_KEY_F24             , EventKeyboard::KeyCode::KEY_NONE          },
    { GLFW_KEY_F25             , EventKeyboard::KeyCode::KEY_NONE          },
    { GLFW_KEY_KP_0            , EventKeyboard::KeyCode::KEY_0             },
    { GLFW_KEY_KP_1            , EventKeyboard::KeyCode::KEY_1             },
    { GLFW_KEY_KP_2            , EventKeyboard::KeyCode::KEY_2             },
    { GLFW_KEY_KP_3            , EventKeyboard::KeyCode::KEY_3             },
    { GLFW_KEY_KP_4            , EventKeyboard::KeyCode::KEY_4             },
    { GLFW_KEY_KP_5            , EventKeyboard::KeyCode::KEY_5             },
    { GLFW_KEY_KP_6            , EventKeyboard::KeyCode::KEY_6             },
    { GLFW_KEY_KP_7            , EventKeyboard::KeyCode::KEY_7             },
    { GLFW_KEY_KP_8            , EventKeyboard::KeyCode::KEY_8             },
    { GLFW_KEY_KP_9            , EventKeyboard::KeyCode::KEY_9             },
    { GLFW_KEY_KP_DECIMAL      , EventKeyboard::KeyCode::KEY_PERIOD        },
    { GLFW_KEY_KP_DIVIDE       , EventKeyboard::KeyCode::KEY_KP_DIVIDE     },
    { GLFW_KEY_KP_MULTIPLY     , EventKeyboard::KeyCode::KEY_KP_MULTIPLY   },
    { GLFW_KEY_KP_SUBTRACT     , EventKeyboard::KeyCode::KEY_KP_MINUS      },
    { GLFW_KEY_KP_ADD          , EventKeyboard::KeyCode::KEY_KP_PLUS       },
    { GLFW_KEY_KP_ENTER        , EventKeyboard::KeyCode::KEY_KP_ENTER      },
    { GLFW_KEY_KP_EQUAL        , EventKeyboard::KeyCode::KEY_EQUAL         },
    { GLFW_KEY_LEFT_SHIFT      , EventKeyboard::KeyCode::KEY_LEFT_SHIFT         },
    { GLFW_KEY_LEFT_CONTROL    , EventKeyboard::KeyCode::KEY_LEFT_CTRL          },
    { GLFW_KEY_LEFT_ALT        , EventKeyboard::KeyCode::KEY_LEFT_ALT           },
    { GLFW_KEY_LEFT_SUPER      , EventKeyboard::KeyCode::KEY_HYPER         },
    { GLFW_KEY_RIGHT_SHIFT     , EventKeyboard::KeyCode::KEY_RIGHT_SHIFT         },
    { GLFW_KEY_RIGHT_CONTROL   , EventKeyboard::KeyCode::KEY_RIGHT_CTRL          },
    { GLFW_KEY_RIGHT_ALT       , EventKeyboard::KeyCode::KEY_RIGHT_ALT           },
    { GLFW_KEY_RIGHT_SUPER     , EventKeyboard::KeyCode::KEY_HYPER         },
    { GLFW_KEY_MENU            , EventKeyboard::KeyCode::KEY_MENU          },
    { GLFW_KEY_LAST            , EventKeyboard::KeyCode::KEY_NONE          }
};

//////////////////////////////////////////////////////////////////////////
// implement GLViewImpl
//////////////////////////////////////////////////////////////////////////


GLViewImpl::GLViewImpl()
: _captured(false)
, _supportTouch(false)
, _isInRetinaMonitor(false)
, _isRetinaEnabled(false)
, _retinaFactor(1)
, _frameZoomFactor(1.0f)
, _mainWindow(nullptr)
, _monitor(nullptr)
, _mouseX(0.0f)
, _mouseY(0.0f)
{
    _viewName = "cocos2dx";
    g_keyCodeMap.clear();
    for (auto& item : g_keyCodeStructArray)
    {
        g_keyCodeMap[item.glfwKeyCode] = item.keyCode;
    }

    GLFWEventHandler::setGLViewImpl(this);

    glfwSetErrorCallback(GLFWEventHandler::onGLFWError);
    glfwInit();
}

GLViewImpl::~GLViewImpl()
{
    CCLOGINFO("deallocing GLViewImpl: %p", this);
    GLFWEventHandler::setGLViewImpl(nullptr);
    glfwTerminate();
}

GLViewImpl* GLViewImpl::create(const std::string& viewName)
{
    auto ret = new (std::nothrow) GLViewImpl;
    if(ret && ret->initWithRect(viewName, Rect(0, 0, 960, 640), 1)) {
        ret->autorelease();
        return ret;
    }

    return nullptr;
}

GLViewImpl* GLViewImpl::createWithRect(const std::string& viewName, Rect rect, float frameZoomFactor)
{
    auto ret = new (std::nothrow) GLViewImpl;
    if(ret && ret->initWithRect(viewName, rect, frameZoomFactor)) {
        ret->autorelease();
        return ret;
    }

    return nullptr;
}

GLViewImpl* GLViewImpl::createWithFullScreen(const std::string& viewName)
{
    auto ret = new (std::nothrow) GLViewImpl();
    if(ret && ret->initWithFullScreen(viewName)) {
        ret->autorelease();
        return ret;
    }

    return nullptr;
}

GLViewImpl* GLViewImpl::createWithFullScreen(const std::string& viewName, const GLFWvidmode &videoMode, GLFWmonitor *monitor)
{
    auto ret = new (std::nothrow) GLViewImpl();
    if(ret && ret->initWithFullscreen(viewName, videoMode, monitor)) {
        ret->autorelease();
        return ret;
    }
    
    return nullptr;
}

bool GLViewImpl::initWithRect(const std::string& viewName, Rect rect, float frameZoomFactor)
{
    setViewName(viewName);

    _frameZoomFactor = frameZoomFactor;

    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
    glfwWindowHint(GLFW_RED_BITS,_glContextAttrs.redBits);
    glfwWindowHint(GLFW_GREEN_BITS,_glContextAttrs.greenBits);
    glfwWindowHint(GLFW_BLUE_BITS,_glContextAttrs.blueBits);
    glfwWindowHint(GLFW_ALPHA_BITS,_glContextAttrs.alphaBits);
    glfwWindowHint(GLFW_DEPTH_BITS,_glContextAttrs.depthBits);
    glfwWindowHint(GLFW_STENCIL_BITS,_glContextAttrs.stencilBits);

    _mainWindow = glfwCreateWindow(rect.size.width * _frameZoomFactor,
                                   rect.size.height * _frameZoomFactor,
                                   _viewName.c_str(),
                                   _monitor,
                                   nullptr);
    glfwMakeContextCurrent(_mainWindow);

    glfwSetMouseButtonCallback(_mainWindow, GLFWEventHandler::onGLFWMouseCallBack);
    glfwSetCursorPosCallback(_mainWindow, GLFWEventHandler::onGLFWMouseMoveCallBack);
    glfwSetScrollCallback(_mainWindow, GLFWEventHandler::onGLFWMouseScrollCallback);
    glfwSetCharCallback(_mainWindow, GLFWEventHandler::onGLFWCharCallback);
    glfwSetKeyCallback(_mainWindow, GLFWEventHandler::onGLFWKeyCallback);
    glfwSetWindowPosCallback(_mainWindow, GLFWEventHandler::onGLFWWindowPosCallback);
    glfwSetFramebufferSizeCallback(_mainWindow, GLFWEventHandler::onGLFWframebuffersize);
    glfwSetWindowSizeCallback(_mainWindow, GLFWEventHandler::onGLFWWindowSizeFunCallback);
    glfwSetWindowIconifyCallback(_mainWindow, GLFWEventHandler::onGLFWWindowIconifyCallback);

    setFrameSize(rect.size.width, rect.size.height);

    // check OpenGL version at first
    const GLubyte* glVersion = glGetString(GL_VERSION);

    if ( utils::atof((const char*)glVersion) < 1.5 )
    {
        char strComplain[256] = {0};
        sprintf(strComplain,
                "OpenGL 1.5 or higher is required (your version is %s). Please upgrade the driver of your video card.",
                glVersion);
        MessageBox(strComplain, "OpenGL version too old");
        return false;
    }

    initGlew();

    // Enable point size by default.
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    return true;
}

bool GLViewImpl::initWithFullScreen(const std::string& viewName)
{
    //Create fullscreen window on primary monitor at its current video mode.
    _monitor = glfwGetPrimaryMonitor();
    if (nullptr == _monitor)
        return false;

    const GLFWvidmode* videoMode = glfwGetVideoMode(_monitor);
    return initWithRect(viewName, Rect(0, 0, videoMode->width, videoMode->height), 1.0f);
}

bool GLViewImpl::initWithFullscreen(const std::string &viewname, const GLFWvidmode &videoMode, GLFWmonitor *monitor)
{
    //Create fullscreen on specified monitor at the specified video mode.
    _monitor = monitor;
    if (nullptr == _monitor)
        return false;
    
    //These are soft contraints. If the video mode is retrieved at runtime, the resulting window and context should match these exactly. If invalid attribs are passed (eg. from an outdated cache), window creation will NOT fail but the actual window/context may differ.
    glfwWindowHint(GLFW_REFRESH_RATE, videoMode.refreshRate);
    glfwWindowHint(GLFW_RED_BITS, videoMode.redBits);
    glfwWindowHint(GLFW_BLUE_BITS, videoMode.blueBits);
    glfwWindowHint(GLFW_GREEN_BITS, videoMode.greenBits);
    
    return initWithRect(viewname, Rect(0, 0, videoMode.width, videoMode.height), 1.0f);
}

bool GLViewImpl::isOpenGLReady()
{
    return nullptr != _mainWindow;
}

void GLViewImpl::end()
{
    if(_mainWindow)
    {
        glfwSetWindowShouldClose(_mainWindow,1);
        _mainWindow = nullptr;
    }
    // Release self. Otherwise, GLViewImpl could not be freed.
    release();
}

void GLViewImpl::swapBuffers()
{
    if(_mainWindow)
        glfwSwapBuffers(_mainWindow);
}

bool GLViewImpl::windowShouldClose()
{
    if(_mainWindow)
        return glfwWindowShouldClose(_mainWindow) ? true : false;
    else
        return true;
}

void GLViewImpl::pollEvents()
{
    glfwPollEvents();
}

void GLViewImpl::enableRetina(bool enabled)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    _isRetinaEnabled = enabled;
    if (_isRetinaEnabled)
    {
        _retinaFactor = 1;
    }
    else
    {
        _retinaFactor = 2;
    }
    updateFrameSize();
#endif
}


void GLViewImpl::setIMEKeyboardState(bool /*bOpen*/)
{

}

void GLViewImpl::setCursorVisible( bool isVisible )
{
    if( _mainWindow == NULL )
        return;
    
    if( isVisible )
        glfwSetInputMode(_mainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    else
        glfwSetInputMode(_mainWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void GLViewImpl::setFrameZoomFactor(float zoomFactor)
{
    CCASSERT(zoomFactor > 0.0f, "zoomFactor must be larger than 0");

    if (fabs(_frameZoomFactor - zoomFactor) < FLT_EPSILON)
    {
        return;
    }

    _frameZoomFactor = zoomFactor;
    updateFrameSize();
}

float GLViewImpl::getFrameZoomFactor() const
{
    return _frameZoomFactor;
}

void GLViewImpl::updateFrameSize()
{
    if (_screenSize.width > 0 && _screenSize.height > 0)
    {
        int w = 0, h = 0;
        glfwGetWindowSize(_mainWindow, &w, &h);

        int frameBufferW = 0, frameBufferH = 0;
        glfwGetFramebufferSize(_mainWindow, &frameBufferW, &frameBufferH);

        if (frameBufferW == 2 * w && frameBufferH == 2 * h)
        {
            if (_isRetinaEnabled)
            {
                _retinaFactor = 1;
            }
            else
            {
                _retinaFactor = 2;
            }
            glfwSetWindowSize(_mainWindow, _screenSize.width/2 * _retinaFactor * _frameZoomFactor, _screenSize.height/2 * _retinaFactor * _frameZoomFactor);

            _isInRetinaMonitor = true;
        }
        else
        {
            if (_isInRetinaMonitor)
            {
                _retinaFactor = 1;
            }
            glfwSetWindowSize(_mainWindow, _screenSize.width * _retinaFactor * _frameZoomFactor, _screenSize.height *_retinaFactor * _frameZoomFactor);

            _isInRetinaMonitor = false;
        }
    }
}

void GLViewImpl::setFrameSize(float width, float height)
{
    GLView::setFrameSize(width, height);
    updateFrameSize();
}

void GLViewImpl::setViewPortInPoints(float x , float y , float w , float h)
{
    glViewport((GLint)(x * _scaleX * _retinaFactor * _frameZoomFactor + _viewPortRect.origin.x * _retinaFactor * _frameZoomFactor),
               (GLint)(y * _scaleY * _retinaFactor  * _frameZoomFactor + _viewPortRect.origin.y * _retinaFactor * _frameZoomFactor),
               (GLsizei)(w * _scaleX * _retinaFactor * _frameZoomFactor),
               (GLsizei)(h * _scaleY * _retinaFactor * _frameZoomFactor));
}

void GLViewImpl::setScissorInPoints(float x , float y , float w , float h)
{
    glScissor((GLint)(x * _scaleX * _retinaFactor * _frameZoomFactor + _viewPortRect.origin.x * _retinaFactor * _frameZoomFactor),
               (GLint)(y * _scaleY * _retinaFactor  * _frameZoomFactor + _viewPortRect.origin.y * _retinaFactor * _frameZoomFactor),
               (GLsizei)(w * _scaleX * _retinaFactor * _frameZoomFactor),
               (GLsizei)(h * _scaleY * _retinaFactor * _frameZoomFactor));
}

void GLViewImpl::onGLFWError(int errorID, const char* errorDesc)
{
    CCLOGERROR("GLFWError #%d Happen, %s\n", errorID, errorDesc);
}

void GLViewImpl::onGLFWMouseCallBack(GLFWwindow* window, int button, int action, int modify)
{
    if(GLFW_MOUSE_BUTTON_LEFT == button)
    {
        if(GLFW_PRESS == action)
        {
            _captured = true;
            if (this->getViewPortRect().equals(Rect::ZERO) || this->getViewPortRect().containsPoint(Vec2(_mouseX,_mouseY)))
            {
                intptr_t id = 0;
                this->handleTouchesBegin(1, &id, &_mouseX, &_mouseY);
            }
        }
        else if(GLFW_RELEASE == action)
        {
            if (_captured)
            {
                _captured = false;
                intptr_t id = 0;
                this->handleTouchesEnd(1, &id, &_mouseX, &_mouseY);
            }
        }
    }
    
    //Because OpenGL and cocos2d-x uses different Y axis, we need to convert the coordinate here
    float cursorX = (_mouseX - _viewPortRect.origin.x) / _scaleX;
    float cursorY = (_viewPortRect.origin.y + _viewPortRect.size.height - _mouseY) / _scaleY;

    if(GLFW_PRESS == action)
    {
        EventMouse event(EventMouse::MouseEventType::MOUSE_DOWN);
        event.setCursorPosition(cursorX, cursorY);
        event.setMouseButton(button);
        Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    }
    else if(GLFW_RELEASE == action)
    {
        EventMouse event(EventMouse::MouseEventType::MOUSE_UP);
        event.setCursorPosition(cursorX, cursorY);
        event.setMouseButton(button);
        Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    }
}

void GLViewImpl::onGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y)
{
    _mouseX = (float)x;
    _mouseY = (float)y;

    _mouseX /= this->getFrameZoomFactor();
    _mouseY /= this->getFrameZoomFactor();

    if (_isInRetinaMonitor)
    {
        if (_retinaFactor == 1)
        {
            _mouseX *= 2;
            _mouseY *= 2;
        }
    }

    if (_captured)
    {
        intptr_t id = 0;
        this->handleTouchesMove(1, &id, &_mouseX, &_mouseY);
    }
    
    //Because OpenGL and cocos2d-x uses different Y axis, we need to convert the coordinate here
    float cursorX = (_mouseX - _viewPortRect.origin.x) / _scaleX;
    float cursorY = (_viewPortRect.origin.y + _viewPortRect.size.height - _mouseY) / _scaleY;

    EventMouse event(EventMouse::MouseEventType::MOUSE_MOVE);
    // Set current button
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        event.setMouseButton(GLFW_MOUSE_BUTTON_LEFT);
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        event.setMouseButton(GLFW_MOUSE_BUTTON_RIGHT);
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
    {
        event.setMouseButton(GLFW_MOUSE_BUTTON_MIDDLE);
    }
    event.setCursorPosition(cursorX, cursorY);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

void GLViewImpl::onGLFWMouseScrollCallback(GLFWwindow* window, double x, double y)
{
    EventMouse event(EventMouse::MouseEventType::MOUSE_SCROLL);
    //Because OpenGL and cocos2d-x uses different Y axis, we need to convert the coordinate here
    float cursorX = (_mouseX - _viewPortRect.origin.x) / _scaleX;
    float cursorY = (_viewPortRect.origin.y + _viewPortRect.size.height - _mouseY) / _scaleY;
    event.setScrollData((float)x, -(float)y);
    event.setCursorPosition(cursorX, cursorY);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

void GLViewImpl::onGLFWKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (GLFW_REPEAT != action)
    {
        EventKeyboard event(g_keyCodeMap[key], GLFW_PRESS == action);
        auto dispatcher = Director::getInstance()->getEventDispatcher();
        dispatcher->dispatchEvent(&event);
    }
    
    if (GLFW_RELEASE != action && g_keyCodeMap[key] == EventKeyboard::KeyCode::KEY_BACKSPACE)
    {
        IMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
    }
}

void GLViewImpl::onGLFWCharCallback(GLFWwindow *window, unsigned int character)
{
    char16_t wcharString[2] = { (char16_t) character, 0 };
    std::string utf8String;

    StringUtils::UTF16ToUTF8( wcharString, utf8String );
    IMEDispatcher::sharedDispatcher()->dispatchInsertText( utf8String.c_str(), utf8String.size() );
}

void GLViewImpl::onGLFWWindowPosCallback(GLFWwindow *windows, int x, int y)
{
    Director::getInstance()->setViewport();
}

void GLViewImpl::onGLFWframebuffersize(GLFWwindow* window, int w, int h)
{
    float frameSizeW = _screenSize.width;
    float frameSizeH = _screenSize.height;
    float factorX = frameSizeW / w * _retinaFactor * _frameZoomFactor;
    float factorY = frameSizeH / h * _retinaFactor * _frameZoomFactor;

    if (fabs(factorX - 0.5f) < FLT_EPSILON && fabs(factorY - 0.5f) < FLT_EPSILON )
    {
        _isInRetinaMonitor = true;
        if (_isRetinaEnabled)
        {
            _retinaFactor = 1;
        }
        else
        {
            _retinaFactor = 2;
        }

        glfwSetWindowSize(window, static_cast<int>(frameSizeW * 0.5f * _retinaFactor * _frameZoomFactor) , static_cast<int>(frameSizeH * 0.5f * _retinaFactor * _frameZoomFactor));
    }
    else if(fabs(factorX - 2.0f) < FLT_EPSILON && fabs(factorY - 2.0f) < FLT_EPSILON)
    {
        _isInRetinaMonitor = false;
        _retinaFactor = 1;
        glfwSetWindowSize(window, static_cast<int>(frameSizeW * _retinaFactor * _frameZoomFactor), static_cast<int>(frameSizeH * _retinaFactor * _frameZoomFactor));
    }
}

void GLViewImpl::onGLFWWindowSizeFunCallback(GLFWwindow *window, int width, int height)
{
    if (_resolutionPolicy != ResolutionPolicy::UNKNOWN)
    {
        updateDesignResolutionSize();
        Director::getInstance()->setViewport();
    }
}

void GLViewImpl::onGLFWWindowIconifyCallback(GLFWwindow* window, int iconified)
{
    if (iconified == GL_TRUE)
    {
        Application::getInstance()->applicationDidEnterBackground();
    }
    else
    {
        Application::getInstance()->applicationWillEnterForeground();
    }
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
static bool glew_dynamic_binding()
{
    const char *gl_extensions = (const char*)glGetString(GL_EXTENSIONS);

    // If the current opengl driver doesn't have framebuffers methods, check if an extension exists
    if (glGenFramebuffers == nullptr)
    {
        log("OpenGL: glGenFramebuffers is nullptr, try to detect an extension");
        if (strstr(gl_extensions, "ARB_framebuffer_object"))
        {
            log("OpenGL: ARB_framebuffer_object is supported");

            glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC) wglGetProcAddress("glIsRenderbuffer");
            glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC) wglGetProcAddress("glBindRenderbuffer");
            glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC) wglGetProcAddress("glDeleteRenderbuffers");
            glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC) wglGetProcAddress("glGenRenderbuffers");
            glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC) wglGetProcAddress("glRenderbufferStorage");
            glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC) wglGetProcAddress("glGetRenderbufferParameteriv");
            glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC) wglGetProcAddress("glIsFramebuffer");
            glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) wglGetProcAddress("glBindFramebuffer");
            glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC) wglGetProcAddress("glDeleteFramebuffers");
            glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) wglGetProcAddress("glGenFramebuffers");
            glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) wglGetProcAddress("glCheckFramebufferStatus");
            glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC) wglGetProcAddress("glFramebufferTexture1D");
            glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) wglGetProcAddress("glFramebufferTexture2D");
            glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC) wglGetProcAddress("glFramebufferTexture3D");
            glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC) wglGetProcAddress("glFramebufferRenderbuffer");
            glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) wglGetProcAddress("glGetFramebufferAttachmentParameteriv");
            glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) wglGetProcAddress("glGenerateMipmap");
        }
        else
        if (strstr(gl_extensions, "EXT_framebuffer_object"))
        {
            log("OpenGL: EXT_framebuffer_object is supported");
            glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC) wglGetProcAddress("glIsRenderbufferEXT");
            glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC) wglGetProcAddress("glBindRenderbufferEXT");
            glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC) wglGetProcAddress("glDeleteRenderbuffersEXT");
            glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC) wglGetProcAddress("glGenRenderbuffersEXT");
            glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC) wglGetProcAddress("glRenderbufferStorageEXT");
            glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC) wglGetProcAddress("glGetRenderbufferParameterivEXT");
            glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC) wglGetProcAddress("glIsFramebufferEXT");
            glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) wglGetProcAddress("glBindFramebufferEXT");
            glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC) wglGetProcAddress("glDeleteFramebuffersEXT");
            glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) wglGetProcAddress("glGenFramebuffersEXT");
            glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) wglGetProcAddress("glCheckFramebufferStatusEXT");
            glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC) wglGetProcAddress("glFramebufferTexture1DEXT");
            glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) wglGetProcAddress("glFramebufferTexture2DEXT");
            glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC) wglGetProcAddress("glFramebufferTexture3DEXT");
            glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC) wglGetProcAddress("glFramebufferRenderbufferEXT");
            glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) wglGetProcAddress("glGetFramebufferAttachmentParameterivEXT");
            glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) wglGetProcAddress("glGenerateMipmapEXT");
        }
        else
        {
            log("OpenGL: No framebuffers extension is supported");
            log("OpenGL: Any call to Fbo will crash!");
            return false;
        }
    }
    return true;
}
#endif

// helper
bool GLViewImpl::initGlew()
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_MAC)
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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    if(glew_dynamic_binding() == false)
    {
        MessageBox("No OpenGL framebuffer support. Please upgrade the driver of your video card.", "OpenGL error");
        return false;
    }
#endif

#endif // (CC_TARGET_PLATFORM != CC_PLATFORM_MAC)

    return true;
}

NS_CC_END // end of namespace cocos2d;
