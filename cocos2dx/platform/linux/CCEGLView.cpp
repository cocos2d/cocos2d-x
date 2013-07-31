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
#include "touch_dispatcher/CCTouch.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "text_input_node/CCIMEDispatcher.h"
#include "keyboard_dispatcher/CCKeyboardDispatcher.h"
#include <unistd.h>

bool initExtensions()
{
    // Do nothing, on Linux we use GLEW.
}

NS_CC_BEGIN

EGLView::EGLView()
: _wasInit(false)
, _frameZoomFactor(1.0f)
,_window(nullptr)
,_context(nullptr)
{
}

EGLView::~EGLView()
{
}

static std::string getApplicationName()
{
    char fullpath[256] = {0};
    ssize_t length = readlink("/proc/self/exe", fullpath, sizeof(fullpath)-1);

    if (length <= 0) {
        return "Cocos2dx-Linux";
    }

    fullpath[length] = '\0';
    const std::string appPath = fullpath;
    return appPath.substr(appPath.find_last_of('/') + 1);
}

void checkSDLError(int line)
{
#if COCOS2D_DEBUG > 0
    const char *error = SDL_GetError();
    if (*error != '\0')
    {
        if (line != -1)
            CCLOG("SDL Error: %s, line: %i", error, line);
        else
            CCLOG("SDL Error: %s", error);
        SDL_ClearError();
    }
#endif
}

void EGLView::setFrameSize(float width, float height)
{
    bool eResult = false;
    //create the window by SDL2.

    //check
    CCAssert(width!=0&&height!=0, "invalid window's size equal 0");

    //Inits SDL2
    eResult = SDL_Init(SDL_INIT_VIDEO) == 0;
    if (!eResult) {
        CCAssert(0, "fail to init the SDL");
    }

    const std::string appName = getApplicationName();
    const int iDepth = 16; // set default value

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    _window = SDL_CreateWindow(appName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, iDepth);
    checkSDLError(__LINE__);

    _context = SDL_GL_CreateContext(_window);

    if (!_window || !_context) {
        CCAssert(0, "Failed to initialize OpenGL context");
    } else {
        SDL_GL_SetSwapInterval(1);
        checkSDLError(__LINE__);
        _wasInit = true;

        EGLViewProtocol::setFrameSize(width, height);
        initGL();
        if (!GLEW_ARB_framebuffer_object)
            CCAssert(0, "fail to init OpenGL extension ARB_framebuffer_object");
        if (!GLEW_ARB_vertex_buffer_object)
            CCAssert(0, "fail to init OpenGL extension ARB_vertex_buffer_object");
    }
}

void EGLView::setFrameZoomFactor(float fZoomFactor)
{
    _frameZoomFactor = fZoomFactor;
    SDL_SetWindowSize(_window, _screenSize.width * fZoomFactor, _screenSize.height * fZoomFactor);
    Director::getInstance()->setProjection(Director::getInstance()->getProjection());
}

float EGLView::getFrameZoomFactor()
{
    return _frameZoomFactor;
}

void EGLView::setViewPortInPoints(float x , float y , float w , float h)
{
    glViewport((GLint)(x * _scaleX * _frameZoomFactor+ _viewPortRect.origin.x * _frameZoomFactor),
        (GLint)(y * _scaleY * _frameZoomFactor + _viewPortRect.origin.y * _frameZoomFactor),
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


bool EGLView::isOpenGLReady()
{
    return _wasInit;
}

void EGLView::end()
{
    SDL_GL_DeleteContext(_context);
    SDL_DestroyWindow(_window);
    SDL_Quit();

    delete this;
    exit(0);
}

void EGLView::swapBuffers() {
    if (_wasInit) {
        /* Swap buffers */
        SDL_GL_SwapWindow(_window);
    }
}

// Polls events if SDL backend is on.
// Note that finger events allow multi-touch on Linux, but libsdl with X11
// backend does not support multitouch. However multitouch should work
// out of the box on upcoming Weston and Mir display servers.
// Also supports mouse touches emulation, keyboard events, text events.
void EGLView::pollInputEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            Director::sharedDirector()->end();
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                int id = event.button.which;
                _pressedMouseInstances.insert(id);
                Point oPoint((float)event.button.x, (float)event.button.y);
                oPoint.x /= _frameZoomFactor;
                oPoint.y /= _frameZoomFactor;
                handleTouchesBegin(1, &id, &oPoint.x, &oPoint.y);
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT) {
                int id = event.button.which;
                _pressedMouseInstances.erase(id);
                Point oPoint((float)event.button.x, (float)event.button.y);
                oPoint.x /= _frameZoomFactor;
                oPoint.y /= _frameZoomFactor;
                handleTouchesEnd(1, &id, &oPoint.x, &oPoint.y);
            }
            break;
        case SDL_MOUSEMOTION:
            if (_pressedMouseInstances.count(event.motion.which)) {
                int id = event.motion.which;
                Point oPoint((float)event.motion.x, (float)event.motion.y);
                oPoint.x /= _frameZoomFactor;
                oPoint.y /= _frameZoomFactor;
                handleTouchesMove(1, &id, &oPoint.x, &oPoint.y);
            }
            break;
        case SDL_FINGERDOWN: {
            int fingerId = event.tfinger.fingerId;
            Point oPoint((float)event.tfinger.x, (float)event.tfinger.y);
            oPoint.x /= _frameZoomFactor;
            oPoint.y /= _frameZoomFactor;
            handleTouchesBegin(1, &fingerId, &oPoint.x, &oPoint.y);
        }
            break;
        case SDL_FINGERUP: {
            int fingerId = event.tfinger.fingerId;
            Point oPoint((float)event.tfinger.x, (float)event.tfinger.y);
            oPoint.x /= _frameZoomFactor;
            oPoint.y /= _frameZoomFactor;
            handleTouchesEnd(1, &fingerId, &oPoint.x, &oPoint.y);
            break;
        }
        case SDL_FINGERMOTION: {
            int fingerId = event.tfinger.fingerId;
            Point oPoint((float)event.tfinger.x, (float)event.tfinger.y);
            oPoint.x /= _frameZoomFactor;
            oPoint.y /= _frameZoomFactor;
            handleTouchesMove(1, &fingerId, &oPoint.x, &oPoint.y);
        }
            break;
        case SDL_TEXTINPUT: {
            const std::string text = event.text.text;
            IMEDispatcher::sharedDispatcher()->dispatchInsertText(text.c_str(), text.size());
        }
            break;
        case SDL_TEXTEDITING:
            // TODO: not implemented.
            // In SDL text editing is similar to patching. Each patch consists of
            // selected text range and string that replaces selected text.
            break;
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_BACKSPACE)
                IMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
            Director::sharedDirector()->getKeyboardDispatcher()->dispatchKeyboardEvent(event.key.keysym.sym, true);
            break;
        case SDL_KEYUP:
            Director::sharedDirector()->getKeyboardDispatcher()->dispatchKeyboardEvent(event.key.keysym.sym, false);
            }
            break;
        }
    }
}

void EGLView::setIMEKeyboardState(bool bOpen)
{
    _IMEKeyboardOpened = bOpen;
    Rect zeroRect(0, 0, 0, 0);
    IMEKeyboardNotificationInfo info;
    info.begin = zeroRect;
    info.end = zeroRect;
    info.duration = 0;
    if (bOpen) {
        IMEDispatcher::sharedDispatcher()->dispatchKeyboardWillShow(info);
        IMEDispatcher::sharedDispatcher()->dispatchKeyboardDidShow(info);
    } else {
        IMEDispatcher::sharedDispatcher()->dispatchKeyboardWillHide(info);
        IMEDispatcher::sharedDispatcher()->dispatchKeyboardDidHide(info);
    }
}

bool EGLView::initGL()
{
    GLenum GlewInitResult = glewInit();
    if (GLEW_OK != GlewInitResult) 
    {
        fprintf(stderr,"ERROR: %s\n",glewGetErrorString(GlewInitResult));
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

    // Enable point size by default on linux.
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    return true;
}

void EGLView::destroyGL()
{
}

EGLView* EGLView::getInstance()
{
    static EGLView* s_pEglView = NULL;
    if (s_pEglView == NULL)
    {
        s_pEglView = new EGLView();
    }
    return s_pEglView;
}

// XXX: deprecated
EGLView* EGLView::sharedOpenGLView()
{
    return EGLView::getInstance();
}

NS_CC_END
