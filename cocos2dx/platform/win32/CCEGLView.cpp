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
#include "cocoa/CCSet.h"
#include "ccMacros.h"
#include "CCDirector.h"
#include "text_input_node/CCIMEDispatcher.h"
#include "CCApplication.h"
#include "event_dispatcher/CCTouch.h"
#include "event_dispatcher/CCEventDispatcher.h"
#include "event_dispatcher/CCKeyboardEvent.h"


NS_CC_BEGIN

struct keyCodeItem
{
    int glfwKeyCode;
    KeyboardEvent::KeyCode keyCode;
};

static std::map<int, KeyboardEvent::KeyCode> g_keyCodeMap;

static keyCodeItem g_keyCodeStructArray[] = {
    /* The unknown key */
    { GLFW_KEY_UNKNOWN         , KeyboardEvent::KeyCode::KEY_NONE          },
    
    /* Printable keys */

    { GLFW_KEY_SPACE           , KeyboardEvent::KeyCode::KEY_SPACE         },
    { GLFW_KEY_APOSTROPHE      , KeyboardEvent::KeyCode::KEY_APOSTROPHE    },
    { GLFW_KEY_COMMA           , KeyboardEvent::KeyCode::KEY_COMMA         },
    { GLFW_KEY_MINUS           , KeyboardEvent::KeyCode::KEY_MINUS         },
    { GLFW_KEY_PERIOD          , KeyboardEvent::KeyCode::KEY_PERIOD        },
    { GLFW_KEY_SLASH           , KeyboardEvent::KeyCode::KEY_SLASH         },
    { GLFW_KEY_0               , KeyboardEvent::KeyCode::KEY_0             },
    { GLFW_KEY_1               , KeyboardEvent::KeyCode::KEY_1             },
    { GLFW_KEY_2               , KeyboardEvent::KeyCode::KEY_2             },
    { GLFW_KEY_3               , KeyboardEvent::KeyCode::KEY_3             },
    { GLFW_KEY_4               , KeyboardEvent::KeyCode::KEY_4             },
    { GLFW_KEY_5               , KeyboardEvent::KeyCode::KEY_5             },
    { GLFW_KEY_6               , KeyboardEvent::KeyCode::KEY_6             },
    { GLFW_KEY_7               , KeyboardEvent::KeyCode::KEY_7             },
    { GLFW_KEY_8               , KeyboardEvent::KeyCode::KEY_8             },
    { GLFW_KEY_9               , KeyboardEvent::KeyCode::KEY_9             },
    { GLFW_KEY_SEMICOLON       , KeyboardEvent::KeyCode::KEY_SEMICOLON     },
    { GLFW_KEY_EQUAL           , KeyboardEvent::KeyCode::KEY_EQUAL         },
    { GLFW_KEY_A               , KeyboardEvent::KeyCode::KEY_A             },
    { GLFW_KEY_B               , KeyboardEvent::KeyCode::KEY_B             },
    { GLFW_KEY_C               , KeyboardEvent::KeyCode::KEY_C             },
    { GLFW_KEY_D               , KeyboardEvent::KeyCode::KEY_D             },
    { GLFW_KEY_E               , KeyboardEvent::KeyCode::KEY_E             },
    { GLFW_KEY_F               , KeyboardEvent::KeyCode::KEY_F             },
    { GLFW_KEY_G               , KeyboardEvent::KeyCode::KEY_G             },
    { GLFW_KEY_H               , KeyboardEvent::KeyCode::KEY_H             },
    { GLFW_KEY_I               , KeyboardEvent::KeyCode::KEY_I             },
    { GLFW_KEY_J               , KeyboardEvent::KeyCode::KEY_J             },
    { GLFW_KEY_K               , KeyboardEvent::KeyCode::KEY_K             },
    { GLFW_KEY_L               , KeyboardEvent::KeyCode::KEY_L             },
    { GLFW_KEY_M               , KeyboardEvent::KeyCode::KEY_M             },
    { GLFW_KEY_N               , KeyboardEvent::KeyCode::KEY_N             },
    { GLFW_KEY_O               , KeyboardEvent::KeyCode::KEY_O             },
    { GLFW_KEY_P               , KeyboardEvent::KeyCode::KEY_P             },
    { GLFW_KEY_Q               , KeyboardEvent::KeyCode::KEY_Q             },
    { GLFW_KEY_R               , KeyboardEvent::KeyCode::KEY_R             },
    { GLFW_KEY_S               , KeyboardEvent::KeyCode::KEY_S             },
    { GLFW_KEY_T               , KeyboardEvent::KeyCode::KEY_T             },
    { GLFW_KEY_U               , KeyboardEvent::KeyCode::KEY_U             },
    { GLFW_KEY_V               , KeyboardEvent::KeyCode::KEY_V             },
    { GLFW_KEY_W               , KeyboardEvent::KeyCode::KEY_W             },
    { GLFW_KEY_X               , KeyboardEvent::KeyCode::KEY_X             },
    { GLFW_KEY_Y               , KeyboardEvent::KeyCode::KEY_Y             },
    { GLFW_KEY_Z               , KeyboardEvent::KeyCode::KEY_Z             },
    { GLFW_KEY_LEFT_BRACKET    , KeyboardEvent::KeyCode::KEY_LEFT_BRACKET  },
    { GLFW_KEY_BACKSLASH       , KeyboardEvent::KeyCode::KEY_BACK_SLASH    },
    { GLFW_KEY_RIGHT_BRACKET   , KeyboardEvent::KeyCode::KEY_RIGHT_BRACKET },
    { GLFW_KEY_GRAVE_ACCENT    , KeyboardEvent::KeyCode::KEY_GRAVE         },
    { GLFW_KEY_WORLD_1         , KeyboardEvent::KeyCode::KEY_GRAVE         },
    { GLFW_KEY_WORLD_2         , KeyboardEvent::KeyCode::KEY_NONE          },
    
    /* Function keys */
    { GLFW_KEY_ESCAPE          , KeyboardEvent::KeyCode::KEY_ESCAPE        },
    { GLFW_KEY_ENTER           , KeyboardEvent::KeyCode::KEY_KP_ENTER      },
    { GLFW_KEY_TAB             , KeyboardEvent::KeyCode::KEY_TAB           },
    { GLFW_KEY_BACKSPACE       , KeyboardEvent::KeyCode::KEY_BACKSPACE     },
    { GLFW_KEY_INSERT          , KeyboardEvent::KeyCode::KEY_INSERT        },
    { GLFW_KEY_DELETE          , KeyboardEvent::KeyCode::KEY_DELETE        },
    { GLFW_KEY_RIGHT           , KeyboardEvent::KeyCode::KEY_RIGHT_ARROW   },
    { GLFW_KEY_LEFT            , KeyboardEvent::KeyCode::KEY_LEFT_ARROW    },
    { GLFW_KEY_DOWN            , KeyboardEvent::KeyCode::KEY_DOWN_ARROW    },
    { GLFW_KEY_UP              , KeyboardEvent::KeyCode::KEY_UP_ARROW      },
    { GLFW_KEY_PAGE_UP         , KeyboardEvent::KeyCode::KEY_KP_PG_UP      },
    { GLFW_KEY_PAGE_DOWN       , KeyboardEvent::KeyCode::KEY_KP_PG_DOWN    },
    { GLFW_KEY_HOME            , KeyboardEvent::KeyCode::KEY_KP_HOME       },
    { GLFW_KEY_END             , KeyboardEvent::KeyCode::KEY_END           },
    { GLFW_KEY_CAPS_LOCK       , KeyboardEvent::KeyCode::KEY_CAPS_LOCK     },
    { GLFW_KEY_SCROLL_LOCK     , KeyboardEvent::KeyCode::KEY_SCROLL_LOCK   },
    { GLFW_KEY_NUM_LOCK        , KeyboardEvent::KeyCode::KEY_NUM_LOCK      },
    { GLFW_KEY_PRINT_SCREEN    , KeyboardEvent::KeyCode::KEY_PRINT         },
    { GLFW_KEY_PAUSE           , KeyboardEvent::KeyCode::KEY_PAUSE         },
    { GLFW_KEY_F1              , KeyboardEvent::KeyCode::KEY_F1            },
    { GLFW_KEY_F2              , KeyboardEvent::KeyCode::KEY_F2            },
    { GLFW_KEY_F3              , KeyboardEvent::KeyCode::KEY_F3            },
    { GLFW_KEY_F4              , KeyboardEvent::KeyCode::KEY_F4            },
    { GLFW_KEY_F5              , KeyboardEvent::KeyCode::KEY_F5            },
    { GLFW_KEY_F6              , KeyboardEvent::KeyCode::KEY_F6            },
    { GLFW_KEY_F7              , KeyboardEvent::KeyCode::KEY_F7            },
    { GLFW_KEY_F8              , KeyboardEvent::KeyCode::KEY_F8            },
    { GLFW_KEY_F9              , KeyboardEvent::KeyCode::KEY_F9            },
    { GLFW_KEY_F10             , KeyboardEvent::KeyCode::KEY_F10           },
    { GLFW_KEY_F11             , KeyboardEvent::KeyCode::KEY_F11           },
    { GLFW_KEY_F12             , KeyboardEvent::KeyCode::KEY_F12           },
    { GLFW_KEY_F13             , KeyboardEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F14             , KeyboardEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F15             , KeyboardEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F16             , KeyboardEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F17             , KeyboardEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F18             , KeyboardEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F19             , KeyboardEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F20             , KeyboardEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F21             , KeyboardEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F22             , KeyboardEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F23             , KeyboardEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F24             , KeyboardEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F25             , KeyboardEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_KP_0            , KeyboardEvent::KeyCode::KEY_0             },
    { GLFW_KEY_KP_1            , KeyboardEvent::KeyCode::KEY_1             },
    { GLFW_KEY_KP_2            , KeyboardEvent::KeyCode::KEY_2             },
    { GLFW_KEY_KP_3            , KeyboardEvent::KeyCode::KEY_3             },
    { GLFW_KEY_KP_4            , KeyboardEvent::KeyCode::KEY_4             },
    { GLFW_KEY_KP_5            , KeyboardEvent::KeyCode::KEY_5             },
    { GLFW_KEY_KP_6            , KeyboardEvent::KeyCode::KEY_6             },
    { GLFW_KEY_KP_7            , KeyboardEvent::KeyCode::KEY_7             },
    { GLFW_KEY_KP_8            , KeyboardEvent::KeyCode::KEY_8             },
    { GLFW_KEY_KP_9            , KeyboardEvent::KeyCode::KEY_9             },
    { GLFW_KEY_KP_DECIMAL      , KeyboardEvent::KeyCode::KEY_PERIOD        },
    { GLFW_KEY_KP_DIVIDE       , KeyboardEvent::KeyCode::KEY_KP_DIVIDE     },
    { GLFW_KEY_KP_MULTIPLY     , KeyboardEvent::KeyCode::KEY_KP_MULTIPLY   },
    { GLFW_KEY_KP_SUBTRACT     , KeyboardEvent::KeyCode::KEY_KP_MINUS      },
    { GLFW_KEY_KP_ADD          , KeyboardEvent::KeyCode::KEY_KP_PLUS       },
    { GLFW_KEY_KP_ENTER        , KeyboardEvent::KeyCode::KEY_KP_ENTER      },
    { GLFW_KEY_KP_EQUAL        , KeyboardEvent::KeyCode::KEY_EQUAL         },
    { GLFW_KEY_LEFT_SHIFT      , KeyboardEvent::KeyCode::KEY_SHIFT         },
    { GLFW_KEY_LEFT_CONTROL    , KeyboardEvent::KeyCode::KEY_CTRL          },
    { GLFW_KEY_LEFT_ALT        , KeyboardEvent::KeyCode::KEY_ALT           },
    { GLFW_KEY_LEFT_SUPER      , KeyboardEvent::KeyCode::KEY_HYPER         },
    { GLFW_KEY_RIGHT_SHIFT     , KeyboardEvent::KeyCode::KEY_SHIFT         },
    { GLFW_KEY_RIGHT_CONTROL   , KeyboardEvent::KeyCode::KEY_CTRL          },
    { GLFW_KEY_RIGHT_ALT       , KeyboardEvent::KeyCode::KEY_ALT           },
    { GLFW_KEY_RIGHT_SUPER     , KeyboardEvent::KeyCode::KEY_HYPER         },
    { GLFW_KEY_MENU            , KeyboardEvent::KeyCode::KEY_MENU          },
    { GLFW_KEY_LAST            , KeyboardEvent::KeyCode::KEY_NONE          }
};

#if(_MSC_VER >= 1600) // Visual Studio 2010 or higher version.
// Windows Touch define
#define MOUSEEVENTF_FROMTOUCH 0xFF515700

// Windows Touch functions
// Workaround to be able tu run app on Windows XP
typedef WINUSERAPI BOOL (WINAPI *RegisterTouchWindowFn)(_In_ HWND hwnd, _In_ ULONG ulFlags);
typedef WINUSERAPI BOOL (WINAPI *UnregisterTouchWindowFn)(_In_ HWND hwnd);
typedef WINUSERAPI LPARAM (WINAPI *GetMessageExtraInfoFn)(VOID);
typedef WINUSERAPI BOOL (WINAPI *GetTouchInputInfoFn)(_In_ HTOUCHINPUT hTouchInput, _In_ UINT cInputs, __out_ecount(cInputs) PTOUCHINPUT pInputs, _In_ int cbSize);
typedef WINUSERAPI BOOL (WINAPI *CloseTouchInputHandleFn)(_In_ HTOUCHINPUT hTouchInput);

static RegisterTouchWindowFn s_pfRegisterTouchWindowFunction = NULL;
static UnregisterTouchWindowFn s_pfUnregisterTouchWindowFunction = NULL;
static GetMessageExtraInfoFn s_pfGetMessageExtraInfoFunction = NULL;
static GetTouchInputInfoFn s_pfGetTouchInputInfoFunction = NULL;
static CloseTouchInputHandleFn s_pfCloseTouchInputHandleFunction = NULL;

static bool CheckTouchSupport()
{
	s_pfRegisterTouchWindowFunction = (RegisterTouchWindowFn)GetProcAddress(GetModuleHandle(TEXT("user32.dll")), "RegisterTouchWindow");
	s_pfUnregisterTouchWindowFunction = (UnregisterTouchWindowFn)GetProcAddress(GetModuleHandle(TEXT("user32.dll")), "UnregisterTouchWindow");
	s_pfGetMessageExtraInfoFunction = (GetMessageExtraInfoFn)GetProcAddress(GetModuleHandle(TEXT("user32.dll")), "GetMessageExtraInfo");
	s_pfGetTouchInputInfoFunction = (GetTouchInputInfoFn)GetProcAddress(GetModuleHandle(TEXT("user32.dll")), "GetTouchInputInfo");
	s_pfCloseTouchInputHandleFunction = (CloseTouchInputHandleFn)GetProcAddress(GetModuleHandle(TEXT("user32.dll")), "CloseTouchInputHandle");

	return (s_pfRegisterTouchWindowFunction && s_pfUnregisterTouchWindowFunction && s_pfGetMessageExtraInfoFunction && s_pfGetTouchInputInfoFunction && s_pfCloseTouchInputHandleFunction);
}

#endif /* #if(_MSC_VER >= 1600) */

static bool glew_dynamic_binding()
{
	const char *gl_extensions = (const char*)glGetString(GL_EXTENSIONS);

	// If the current opengl driver doesn't have framebuffers methods, check if an extension exists
	if (glGenFramebuffers == NULL)
	{
		log("OpenGL: glGenFramebuffers is NULL, try to detect an extension");
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
    KeyboardEvent event(g_keyCodeMap[key], GLFW_PRESS == action);
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
, _lpfnAccelerometerKeyHook(NULL)
, _frameZoomFactor(1.0f)
, _supportTouch(false)
, _mainWindow(nullptr)
{
    CCASSERT(nullptr == s_pEglView, "EGLView is singleton, Should be inited only one time\n");
    s_pEglView = this;
    g_keyCodeMap.clear();
    for (auto& item : g_keyCodeStructArray)
    {
        g_keyCodeMap.insert(std::make_pair(item.glfwKeyCode, item.keyCode));
    }
    strcpy(_viewName, "Cocos2dxWin32");
    glfwSetErrorCallback(EGLViewEventHandler::OnGLFWError);
    glfwInit();
}

EGLView::~EGLView()
{
    glfwTerminate();
    s_pEglView = nullptr;
}

bool EGLView::init(const char* viewName, float width, float height, float frameZoomFactor)
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

    if(glew_dynamic_binding() == false)
    {
        MessageBox("No OpenGL framebuffer support. Please upgrade the driver of your video card.", "OpenGL error");
        return false;
    }

    // Enable point size by default on windows.
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    return true;
}

void EGLView::setAccelerometerKeyHook( LPFN_ACCELEROMETER_KEYHOOK lpfnAccelerometerKeyHook )
{
    _lpfnAccelerometerKeyHook=lpfnAccelerometerKeyHook;
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
		return glfwWindowShouldClose(_mainWindow) != 0;
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

NS_CC_END
