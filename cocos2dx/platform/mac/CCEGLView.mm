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
#include "event_dispatcher/CCTouch.h"
#include "event_dispatcher/CCEventDispatcher.h"
#include "event_dispatcher/CCEventKeyboard.h"
#include "CCIMEDispatcher.h"

NS_CC_BEGIN


static std::map<int, EventKeyboard::KeyCode> g_keyCodeMap = {
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
    { GLFW_KEY_LEFT_SHIFT      , EventKeyboard::KeyCode::KEY_SHIFT         },
    { GLFW_KEY_LEFT_CONTROL    , EventKeyboard::KeyCode::KEY_CTRL          },
    { GLFW_KEY_LEFT_ALT        , EventKeyboard::KeyCode::KEY_ALT           },
    { GLFW_KEY_LEFT_SUPER      , EventKeyboard::KeyCode::KEY_HYPER         },
    { GLFW_KEY_RIGHT_SHIFT     , EventKeyboard::KeyCode::KEY_SHIFT         },
    { GLFW_KEY_RIGHT_CONTROL   , EventKeyboard::KeyCode::KEY_CTRL          },
    { GLFW_KEY_RIGHT_ALT       , EventKeyboard::KeyCode::KEY_ALT           },
    { GLFW_KEY_RIGHT_SUPER     , EventKeyboard::KeyCode::KEY_HYPER         },
    { GLFW_KEY_MENU            , EventKeyboard::KeyCode::KEY_MENU          },
    { GLFW_KEY_LAST            , EventKeyboard::KeyCode::KEY_NONE          }
};


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
    EventKeyboard event(g_keyCodeMap[key], GLFW_PRESS == action);
    EventDispatcher::getInstance()->dispatchEvent(&event);
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
