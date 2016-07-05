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

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_EMSCRIPTEN

#include "CCApplication.h"
#include "CCGLViewImpl-emcc.h"
#include "base/CCDirector.h"
#include "base/ccMacros.h"
#include "base/CCDirector.h"
#include "base/CCTouch.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventKeyboard.h"
#include "base/CCEventMouse.h"
#include "base/CCIMEDispatcher.h"
#include "base/ccUtils.h"
#include "base/ccUTF8.h"
#include "2d/CCCamera.h"

#include <emscripten/emscripten.h>

#include <SDL/SDL.h>
#include <emscripten.h>

NS_CC_BEGIN

struct keyCodeItem
{
	int glfwKeyCode;
	EventKeyboard::KeyCode keyCode;
};

static std::unordered_map<int, EventKeyboard::KeyCode> g_keyCodeMap;

static keyCodeItem g_keyCodeStructArray[] = {
	/* The unknown key */
	{ SDLK_UNKNOWN, EventKeyboard::KeyCode::KEY_NONE },

	/* Printable keys */
	{ SDLK_SPACE, EventKeyboard::KeyCode::KEY_SPACE },
	{ SDLK_QUOTE, EventKeyboard::KeyCode::KEY_APOSTROPHE },
	{ SDLK_COMMA, EventKeyboard::KeyCode::KEY_COMMA },
	{ SDLK_MINUS, EventKeyboard::KeyCode::KEY_MINUS },
	{ SDLK_PERIOD, EventKeyboard::KeyCode::KEY_PERIOD },
	{ SDLK_SLASH, EventKeyboard::KeyCode::KEY_SLASH },
	{ SDLK_0, EventKeyboard::KeyCode::KEY_0 },
	{ SDLK_1, EventKeyboard::KeyCode::KEY_1 },
	{ SDLK_2, EventKeyboard::KeyCode::KEY_2 },
	{ SDLK_3, EventKeyboard::KeyCode::KEY_3 },
	{ SDLK_4, EventKeyboard::KeyCode::KEY_4 },
	{ SDLK_5, EventKeyboard::KeyCode::KEY_5 },
	{ SDLK_6, EventKeyboard::KeyCode::KEY_6 },
	{ SDLK_7, EventKeyboard::KeyCode::KEY_7 },
	{ SDLK_8, EventKeyboard::KeyCode::KEY_8 },
	{ SDLK_9, EventKeyboard::KeyCode::KEY_9 },
	{ SDLK_SEMICOLON, EventKeyboard::KeyCode::KEY_SEMICOLON },
	{ SDLK_EQUALS, EventKeyboard::KeyCode::KEY_EQUAL },
	{ SDLK_a, EventKeyboard::KeyCode::KEY_A },
	{ SDLK_b, EventKeyboard::KeyCode::KEY_B },
	{ SDLK_c, EventKeyboard::KeyCode::KEY_C },
	{ SDLK_d, EventKeyboard::KeyCode::KEY_D },
	{ SDLK_e, EventKeyboard::KeyCode::KEY_E },
	{ SDLK_f, EventKeyboard::KeyCode::KEY_F },
	{ SDLK_g, EventKeyboard::KeyCode::KEY_G },
	{ SDLK_h, EventKeyboard::KeyCode::KEY_H },
	{ SDLK_i, EventKeyboard::KeyCode::KEY_I },
	{ SDLK_j, EventKeyboard::KeyCode::KEY_J },
	{ SDLK_k, EventKeyboard::KeyCode::KEY_K },
	{ SDLK_l, EventKeyboard::KeyCode::KEY_L },
	{ SDLK_m, EventKeyboard::KeyCode::KEY_M },
	{ SDLK_n, EventKeyboard::KeyCode::KEY_N },
	{ SDLK_o, EventKeyboard::KeyCode::KEY_O },
	{ SDLK_p, EventKeyboard::KeyCode::KEY_P },
	{ SDLK_q, EventKeyboard::KeyCode::KEY_Q },
	{ SDLK_r, EventKeyboard::KeyCode::KEY_R },
	{ SDLK_s, EventKeyboard::KeyCode::KEY_S },
	{ SDLK_t, EventKeyboard::KeyCode::KEY_T },
	{ SDLK_u, EventKeyboard::KeyCode::KEY_U },
	{ SDLK_v, EventKeyboard::KeyCode::KEY_V },
	{ SDLK_w, EventKeyboard::KeyCode::KEY_W },
	{ SDLK_x, EventKeyboard::KeyCode::KEY_X },
	{ SDLK_y, EventKeyboard::KeyCode::KEY_Y },
	{ SDLK_z, EventKeyboard::KeyCode::KEY_Z },
	{ SDLK_LEFTBRACKET, EventKeyboard::KeyCode::KEY_LEFT_BRACKET },
	{ SDLK_BACKSLASH, EventKeyboard::KeyCode::KEY_BACK_SLASH },
	{ SDLK_RIGHTBRACKET, EventKeyboard::KeyCode::KEY_RIGHT_BRACKET },
	{ SDLK_BACKQUOTE, EventKeyboard::KeyCode::KEY_GRAVE },

	/* Function keys */
	{ SDLK_ESCAPE, EventKeyboard::KeyCode::KEY_ESCAPE },
	{ SDLK_RETURN, EventKeyboard::KeyCode::KEY_KP_ENTER },
	{ SDLK_TAB, EventKeyboard::KeyCode::KEY_TAB },
	{ SDLK_BACKSPACE, EventKeyboard::KeyCode::KEY_BACKSPACE },
	{ SDLK_INSERT, EventKeyboard::KeyCode::KEY_INSERT },
	{ SDLK_DELETE, EventKeyboard::KeyCode::KEY_DELETE },
	{ SDLK_RIGHT, EventKeyboard::KeyCode::KEY_RIGHT_ARROW },
	{ SDLK_LEFT, EventKeyboard::KeyCode::KEY_LEFT_ARROW },
	{ SDLK_DOWN, EventKeyboard::KeyCode::KEY_DOWN_ARROW },
	{ SDLK_UP, EventKeyboard::KeyCode::KEY_UP_ARROW },
	{ SDLK_PAGEUP, EventKeyboard::KeyCode::KEY_KP_PG_UP },
	{ SDLK_PAGEDOWN, EventKeyboard::KeyCode::KEY_KP_PG_DOWN },
	{ SDLK_HOME, EventKeyboard::KeyCode::KEY_KP_HOME },
	{ SDLK_END, EventKeyboard::KeyCode::KEY_END },
	{ SDLK_CAPSLOCK, EventKeyboard::KeyCode::KEY_CAPS_LOCK },
	{ SDLK_SCROLLLOCK, EventKeyboard::KeyCode::KEY_SCROLL_LOCK },
	{ SDLK_NUMLOCK, EventKeyboard::KeyCode::KEY_NUM_LOCK },
	{ SDLK_PRINTSCREEN, EventKeyboard::KeyCode::KEY_PRINT },
	{ SDLK_PAUSE, EventKeyboard::KeyCode::KEY_PAUSE },
	{ SDLK_F1, EventKeyboard::KeyCode::KEY_F1 },
	{ SDLK_F2, EventKeyboard::KeyCode::KEY_F2 },
	{ SDLK_F3, EventKeyboard::KeyCode::KEY_F3 },
	{ SDLK_F4, EventKeyboard::KeyCode::KEY_F4 },
	{ SDLK_F5, EventKeyboard::KeyCode::KEY_F5 },
	{ SDLK_F6, EventKeyboard::KeyCode::KEY_F6 },
	{ SDLK_F7, EventKeyboard::KeyCode::KEY_F7 },
	{ SDLK_F8, EventKeyboard::KeyCode::KEY_F8 },
	{ SDLK_F9, EventKeyboard::KeyCode::KEY_F9 },
	{ SDLK_F10, EventKeyboard::KeyCode::KEY_F10 },
	{ SDLK_F11, EventKeyboard::KeyCode::KEY_F11 },
	{ SDLK_F12, EventKeyboard::KeyCode::KEY_F12 },
	{ SDLK_F13, EventKeyboard::KeyCode::KEY_NONE },
	{ SDLK_F14, EventKeyboard::KeyCode::KEY_NONE },
	{ SDLK_F15, EventKeyboard::KeyCode::KEY_NONE },
	{ SDLK_F16, EventKeyboard::KeyCode::KEY_NONE },
	{ SDLK_F17, EventKeyboard::KeyCode::KEY_NONE },
	{ SDLK_F18, EventKeyboard::KeyCode::KEY_NONE },
	{ SDLK_F19, EventKeyboard::KeyCode::KEY_NONE },
	{ SDLK_F20, EventKeyboard::KeyCode::KEY_NONE },
	{ SDLK_F21, EventKeyboard::KeyCode::KEY_NONE },
	{ SDLK_F22, EventKeyboard::KeyCode::KEY_NONE },
	{ SDLK_F23, EventKeyboard::KeyCode::KEY_NONE },
	{ SDLK_F24, EventKeyboard::KeyCode::KEY_NONE },
	{ SDLK_KP_0, EventKeyboard::KeyCode::KEY_0 },
	{ SDLK_KP_1, EventKeyboard::KeyCode::KEY_1 },
	{ SDLK_KP_2, EventKeyboard::KeyCode::KEY_2 },
	{ SDLK_KP_3, EventKeyboard::KeyCode::KEY_3 },
	{ SDLK_KP_4, EventKeyboard::KeyCode::KEY_4 },
	{ SDLK_KP_5, EventKeyboard::KeyCode::KEY_5 },
	{ SDLK_KP_6, EventKeyboard::KeyCode::KEY_6 },
	{ SDLK_KP_7, EventKeyboard::KeyCode::KEY_7 },
	{ SDLK_KP_8, EventKeyboard::KeyCode::KEY_8 },
	{ SDLK_KP_9, EventKeyboard::KeyCode::KEY_9 },
	{ SDLK_KP_DECIMAL, EventKeyboard::KeyCode::KEY_PERIOD },
	{ SDLK_KP_DIVIDE, EventKeyboard::KeyCode::KEY_KP_DIVIDE },
	{ SDLK_KP_MULTIPLY, EventKeyboard::KeyCode::KEY_KP_MULTIPLY },
	{ SDLK_KP_MEMSUBTRACT, EventKeyboard::KeyCode::KEY_KP_MINUS },
	{ SDLK_KP_MEMADD, EventKeyboard::KeyCode::KEY_KP_PLUS },
	{ SDLK_KP_ENTER, EventKeyboard::KeyCode::KEY_KP_ENTER },
	{ SDLK_KP_EQUALS, EventKeyboard::KeyCode::KEY_EQUAL },
	{ SDLK_LSHIFT, EventKeyboard::KeyCode::KEY_SHIFT },
	{ SDLK_LCTRL, EventKeyboard::KeyCode::KEY_CTRL },
	{ SDLK_LALT, EventKeyboard::KeyCode::KEY_ALT },
	{ SDLK_LGUI, EventKeyboard::KeyCode::KEY_HYPER },
	{ SDLK_RSHIFT, EventKeyboard::KeyCode::KEY_SHIFT },
	{ SDLK_RCTRL, EventKeyboard::KeyCode::KEY_CTRL },
	{ SDLK_RALT, EventKeyboard::KeyCode::KEY_ALT },
	{ SDLK_RGUI, EventKeyboard::KeyCode::KEY_HYPER },
	{ SDLK_MENU, EventKeyboard::KeyCode::KEY_MENU },
	{ SDLK_LAST, EventKeyboard::KeyCode::KEY_NONE }
};

GLViewImpl* GLViewImpl::createWithRect(const std::string& viewName, Rect rect, float frameZoomFactor)
{
	auto ret = new GLViewImpl;
    if(ret && ret->initWithRect(viewName, rect, frameZoomFactor)) {
		ret->autorelease();
		return ret;
	}

	return nullptr;
}

GLViewImpl* GLViewImpl::create(const std::string& viewName)
{
	auto ret = new GLViewImpl;
    if(ret && ret->initWithRect(viewName, Rect(0, 0, 960, 640), 1)) {
		ret->autorelease();
		return ret;
	}

	return nullptr;
}

GLViewImpl* GLViewImpl::createWithFullScreen(const std::string& viewName)
{
	auto ret = new GLViewImpl();
	if (ret && ret->initWithFullScreen(viewName))
    {
		ret->autorelease();
		return ret;
	}

	return nullptr;
}

GLViewImpl::GLViewImpl()
    :_screenSurface(nullptr),
    _captured(false)
{
    g_keyCodeMap.clear();
    for (auto& item : g_keyCodeStructArray)
    {
        g_keyCodeMap[item.glfwKeyCode] = item.keyCode;
    }
}

GLViewImpl::~GLViewImpl()
{
}

bool GLViewImpl::initWithRect(const std::string& viewName, Rect rect, float frameZoomFactor)
{
	setViewName(viewName); 

	CCLOG("GL Context attrs: %d %d %d %d %d %d", _glContextAttrs.redBits, _glContextAttrs.greenBits, _glContextAttrs.blueBits, _glContextAttrs.alphaBits, _glContextAttrs.depthBits, _glContextAttrs.stencilBits);
    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, _glContextAttrs.redBits);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, _glContextAttrs.greenBits);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, _glContextAttrs.blueBits);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, _glContextAttrs.alphaBits);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, _glContextAttrs.depthBits);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, _glContextAttrs.stencilBits);
    
    _frameZoomFactor = frameZoomFactor;
    int bpp = _glContextAttrs.redBits + _glContextAttrs.greenBits + _glContextAttrs.blueBits + _glContextAttrs.alphaBits;
    _screenSurface = SDL_SetVideoMode(rect.size.width * frameZoomFactor, rect.size.height * frameZoomFactor, bpp, SDL_OPENGL);
    
    setFrameSize(rect.size.width, rect.size.height);
    
    _windowWidth = rect.size.width * frameZoomFactor;
    _windowHeight = rect.size.height * frameZoomFactor;

    emscripten_SDL_SetEventHandler(&GLViewImpl::EventHandler, static_cast<void*>(this));

	const GLubyte* glVersion = glGetString(GL_VERSION);
	const GLubyte* glExtensions = glGetString(GL_EXTENSIONS);
	CCLOG("Version %s", glVersion);
	CCLOG("Extensions %s", glExtensions);
    
    _wheelScrollScale = EM_ASM_INT(
    {
        var nAgt = navigator.userAgent;
        var browserName = navigator.appName;
        var verOffset = -1;
        var OSName = "Unknown OS";
        var result = 1;
        
        if ((verOffset = nAgt.indexOf("OPR")) != -1) browserName = "Opera";
        else if ((verOffset = nAgt.indexOf("MSIE")) != -1) browserName = "MSIE";
        else if ((verOffset = nAgt.indexOf("Netscape")) != -1) browserName = "MSIE";
        else if ((verOffset = nAgt.indexOf("Chrome")) != -1) browserName = "Chrome";
        else if ((verOffset = nAgt.indexOf("Safari")) != -1) browserName = "Safari";
        else if ((verOffset = nAgt.indexOf("Firefox")) != -1) browserName = "Firefox";
        
        if (navigator.appVersion.indexOf("Win") != -1) OSName = "Windows";
        if (navigator.appVersion.indexOf("Mac") != -1) OSName = "MacOS";
        if (navigator.appVersion.indexOf("X11") != -1) OSName = "UNIX";
        if (navigator.appVersion.indexOf("Linux") != -1) OSName = "Linux";
        
        if (browserName == "Chrome" || browserName == "Opera" || browserName == "Safari")
        {
            if (OSName == "MacOS")
            {
                result = 4;
            }
            else if (OSName == "Windows")
            {
                result = 100;
            }
            else if (OSName == "UNIX" || OSName == "Linux")
            {
                result = 53;
            }
        }
        else if (browserName == "MSIE" || browserName == "Netscape")
        {
            result = 147;
        }
        else if (browserName == "Firefox")
        {
            if (OSName == "MacOS")
            {
                result = 1;
            }
            else if (OSName == "Windows" || OSName == "UNIX" || OSName == "Linux")
            {
                result = 3;
            }
        }
        
        Module.print("nAgt " + nAgt);
        Module.print("browserName " + browserName);
        Module.print("OSName " + OSName);
        return result;
    }, 1);
	return true;
}

void GLViewImpl::setFrameSize(float width, float height)
{
    GLView::setFrameSize(width, height);
}

bool GLViewImpl::initWithFullScreen(const std::string& viewName)
{
	return initWithRect(viewName, Rect(0, 0, 800, 600), 1.0f);
}

bool GLViewImpl::isOpenGLReady()
{
	return nullptr != _screenSurface;
}

void GLViewImpl::end()
{
	if (_screenSurface)
	{
        SDL_FreeSurface(_screenSurface);
		_screenSurface = nullptr;
	}

	// Release self. Otherwise, GLViewImpl could not be freed.
	release();
}

void GLViewImpl::swapBuffers()
{
	if (_screenSurface)
	{
        SDL_GL_SwapBuffers();
	}
}

void GLViewImpl::pollEvents()
{
	int windowWidth = 0;
	int windowHeight = 0;
	int windowFullscreen = 0;
	emscripten_get_canvas_size(&windowWidth, &windowHeight, &windowFullscreen);
    
	if(_windowWidth != windowWidth || windowHeight != _windowHeight)
	{
		clearAllTouches();
        _windowWidth = windowWidth;
        _windowHeight = windowHeight;
	
		int zoomWidth = windowWidth / _frameZoomFactor;
		int zoomHeight = windowHeight / _frameZoomFactor;

		CCLOG("change window size(%i, %i, %i)", zoomWidth, zoomHeight, windowFullscreen);

        if (_windowFullscreen == 1 && windowFullscreen == 0)
        {
            _windowFullscreen = 0;
            const std::string &script = "Module['forcedAspectRatio'] = " + std::to_string(_defaultWindowHeight / _defaultWindowWidth) + ";";
            emscripten_run_script(script.c_str());
            emscripten_set_canvas_size(_defaultWindowWidth, _defaultWindowHeight);
        }
        else
        {
            screenSizeChanged(zoomWidth, zoomHeight);
            Application::getInstance()->applicationScreenSizeChanged(zoomWidth, zoomHeight);

        }
	}
    
    _windowFullscreen = windowFullscreen;
}

float GLViewImpl::getFrameZoomFactor() const
{
    return _frameZoomFactor;
}

void GLViewImpl::toggleToFullscreen()
{
    if(isFullscreen())
    {
        emscripten_run_script("Module['canvas'].cancelFullScreen();");
    }
    else
    {
        _defaultWindowWidth = _windowWidth;
        _defaultWindowHeight = _windowHeight;
        
        EM_ASM(
               Module['forcedAspectRatio'] = screen.width / screen.height;
               Browser.lockPointer = false;
               Browser.resizeCanvas = true;
               
               if (typeof Browser.lockPointer === 'undefined') Browser.lockPointer = true;
               if (typeof Browser.resizeCanvas === 'undefined') Browser.resizeCanvas = false;
               
               var canvas = Module['canvas'];
               function fullScreenChange() {
                   Browser.isFullScreen = false;
                   var canvasContainer = canvas.parentNode;
                   if ((document['webkitFullScreenElement'] || document['webkitFullscreenElement'] ||
                        document['mozFullScreenElement'] || document['mozFullscreenElement'] ||
                        document['fullScreenElement'] || document['fullscreenElement'] ||
                        document['msFullScreenElement'] || document['msFullscreenElement'] ||
                        document['webkitCurrentFullScreenElement']) === canvasContainer) {
                       
                       canvas.cancelFullScreen = document['cancelFullScreen'] ||
                       document['mozCancelFullScreen'] ||
                       document['webkitCancelFullScreen'] ||
                       document['msExitFullscreen'] ||
                       document['exitFullscreen'] ||
                       function() {};
                       canvas.cancelFullScreen = canvas.cancelFullScreen.bind(document);
                       
                       if (Browser.lockPointer) canvas.requestPointerLock();
                       Browser.isFullScreen = true;
                       if (Browser.resizeCanvas) Browser.setFullScreenCanvasSize();
                   } else {
                       
                       // remove the full screen specific parent of the canvas again to restore the HTML structure from before going full screen
                       canvasContainer.parentNode.insertBefore(canvas, canvasContainer);
                       canvasContainer.parentNode.removeChild(canvasContainer);
                       
                       if (Browser.resizeCanvas) Browser.setWindowedCanvasSize();
                   }
                   
                   if (Module['onFullScreen']) Module['onFullScreen'](Browser.isFullScreen);
                   Browser.updateCanvasDimensions(canvas);
               }
               
               if (!Browser.fullScreenHandlersInstalled) {
                   Browser.fullScreenHandlersInstalled = true;
                   document.addEventListener('fullscreenchange', fullScreenChange, false);
                   document.addEventListener('mozfullscreenchange', fullScreenChange, false);
                   document.addEventListener('webkitfullscreenchange', fullScreenChange, false);
                   document.addEventListener('MSFullscreenChange', fullScreenChange, false);
               }
               // create a new parent to ensure the canvas has no siblings. this allows browsers to optimize full screen performance when its parent is the full screen root
               var canvasContainer = document.createElement("div");
               canvasContainer.style.background = 'none';
               canvasContainer.id = "div_fullscreen";
               canvas.parentNode.insertBefore(canvasContainer, canvas);
               canvasContainer.appendChild(canvas);
               
               // use parent of canvas as full screen root to allow aspect ratio correction (Firefox stretches the root to screen size)
               canvasContainer.requestFullScreen = canvasContainer['requestFullScreen'] ||
               canvasContainer['mozRequestFullScreen'] ||
               canvasContainer['msRequestFullscreen'] ||
               (canvasContainer['webkitRequestFullScreen'] ? function() 
                { 
                    canvasContainer['webkitRequestFullScreen'](Element['ALLOW_KEYBOARD_INPUT']);
                    if (!document.webkitCurrentFullScreenElement) canvasContainer['webkitRequestFullScreen']();
                } : function() {});
               
               canvasContainer.requestFullScreen();
        );
    }
}

bool GLViewImpl::isFullscreen()
{
    int windowWidth = 0;
    int windowHeight = 0;
    int windowFullscreen = 0;
    emscripten_get_canvas_size(&windowWidth, &windowHeight, &windowFullscreen);
    return windowFullscreen;
}

int GLViewImpl::EventHandler(void *userdata, SDL_Event *event)
{
    GLViewImpl *thiz = static_cast<GLViewImpl*>(userdata);
    
    switch(event->type)
    {
        case SDL_FINGERMOTION:
        {
            SDL_TouchFingerEvent *touch = (SDL_TouchFingerEvent*)&event->tfinger;
            intptr_t touchId = (intptr_t)touch->fingerId;
            float realScreenWidth = thiz->_viewPortRect.size.width * thiz->getFrameZoomFactor();
            float realScreenHeight = thiz->_viewPortRect.size.height * thiz->getFrameZoomFactor();
            float mouseX = static_cast<float>(touch->x * realScreenWidth) / thiz->getFrameZoomFactor();
            float mouseY = static_cast<float>(touch->y * realScreenHeight) / thiz->getFrameZoomFactor();
            float maxForce = 1.0f;
            
            auto glview = cocos2d::Director::getInstance()->getOpenGLView();
            glview->handleTouchesMove(1, &touchId, &mouseX, &mouseY, &touch->pressure, &maxForce);
            break;
        }
            
        case SDL_FINGERDOWN:
        {
            SDL_TouchFingerEvent *touch = (SDL_TouchFingerEvent*)&event->tfinger;
            intptr_t touchId = (intptr_t)touch->fingerId;
            float realScreenWidth = thiz->_viewPortRect.size.width * thiz->getFrameZoomFactor();
            float realScreenHeight = thiz->_viewPortRect.size.height * thiz->getFrameZoomFactor();
            float mouseX = static_cast<float>(touch->x * realScreenWidth) / thiz->getFrameZoomFactor();
            float mouseY = static_cast<float>(touch->y * realScreenHeight) / thiz->getFrameZoomFactor();
            
            auto glview = cocos2d::Director::getInstance()->getOpenGLView();
            glview->handleTouchesBegin(1, &touchId, &mouseX, &mouseY);
            break;
        }
            
        case SDL_FINGERUP:
        {
            SDL_TouchFingerEvent *touch = (SDL_TouchFingerEvent*)&event->tfinger;
            intptr_t touchId = (intptr_t)touch->fingerId;
            float realScreenWidth = thiz->_viewPortRect.size.width * thiz->getFrameZoomFactor();
            float realScreenHeight = thiz->_viewPortRect.size.height * thiz->getFrameZoomFactor();
            float mouseX = static_cast<float>(touch->x * realScreenWidth) / thiz->getFrameZoomFactor();
            float mouseY = static_cast<float>(touch->y * realScreenHeight) / thiz->getFrameZoomFactor();
            
            auto glview = cocos2d::Director::getInstance()->getOpenGLView();
            glview->handleTouchesEnd(1, &touchId, &mouseX, &mouseY);
            break;
        }
            
        case SDL_MOUSEMOTION:
        {
            SDL_MouseMotionEvent *mouse = (SDL_MouseMotionEvent*)event;
            thiz->onMouseMoveCallBack(mouse->x, mouse->y);
            break;
        }
            
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        {
            SDL_MouseButtonEvent *mouse = (SDL_MouseButtonEvent*)event;
            thiz->onMouseCallBack(mouse->button, event->type, mouse->x, mouse->y);

            float realScreenWidth = ((thiz->_viewPortRect.size.width - thiz->_viewPortRect.origin.x) * thiz->getFrameZoomFactor()) - 1;
            float realScreenHeight = ((thiz->_viewPortRect.size.height - thiz->_viewPortRect.origin.y) * thiz->getFrameZoomFactor()) - 1;
            float cursorX = mouse->x * thiz->getFrameZoomFactor();
            float cursorY = mouse->y * thiz->getFrameZoomFactor();

            if (event->type == SDL_MOUSEBUTTONUP && (cursorX < 0.0f || cursorX > realScreenWidth || cursorY < 0.0f || cursorY > realScreenHeight))
            {
                auto glview = cocos2d::Director::getInstance()->getOpenGLView();
                glview->clearAllTouches();
            }
            break;
        }
            
        case SDL_MOUSEWHEEL:
        {
            SDL_MouseWheelEvent *mouse = (SDL_MouseWheelEvent*)event;
            thiz->onMouseScrollCallback(mouse->x, mouse->y);
            break;
        }
            
        case SDL_KEYDOWN:
        case SDL_KEYUP:
        {
            SDL_KeyboardEvent *key = (SDL_KeyboardEvent*)event;
            thiz->onKeyCallback(key->keysym.sym, key->state, key->repeat);
            break;
        }
            
        case SDL_WINDOWEVENT:
        {
            switch (event->window.event)
            {
                case SDL_WINDOWEVENT_SHOWN:
                    Application::getInstance()->setForegroundMainLoop();
                    break;
                    
                case SDL_WINDOWEVENT_HIDDEN:
                    Application::getInstance()->setBackgroundMainLoop();
                    break;
            }
            
            break;
        }
        
        case SDL_TEXTINPUT:
        {
            thiz->onCharCallback(static_cast<unsigned int>(*event->text.text));
            break;
        }
    }
    
    return 0;
}

void GLViewImpl::onMouseCallBack(int button, int action, double x, double y)
{
	//Because OpenGL and cocos2d-x uses different Y axis, we need to convert the coordinate here
    if (SDL_MOUSEBUTTONDOWN == action || SDL_MOUSEBUTTONUP == action)
    {
        float mouseX = static_cast<float>(x) / this->getFrameZoomFactor();
        float mouseY = static_cast<float>(y) / this->getFrameZoomFactor();
        float cursorX = (mouseX - _viewPortRect.origin.x) / _scaleX;
        float cursorY = (_viewPortRect.origin.y + _viewPortRect.size.height - mouseY) / _scaleY;
        
        EventMouse event(SDL_MOUSEBUTTONDOWN == action ? EventMouse::MouseEventType::MOUSE_DOWN : EventMouse::MouseEventType::MOUSE_UP);
        event.setCursorPosition(cursorX, cursorY);
        event.setMouseButton(button);
        Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    }
}

void GLViewImpl::onMouseMoveCallBack(double x, double y)
{
	float mouseX = static_cast<float>(x) / this->getFrameZoomFactor();
	float mouseY = static_cast<float>(y) / this->getFrameZoomFactor();
    Uint32 mouseState = SDL_GetMouseState(nullptr, nullptr);

    float cursorX = (mouseX - _viewPortRect.origin.x) / _scaleX;
    float cursorY = (mouseY - _viewPortRect.origin.y) / _scaleY;
    
    EventMouse event(EventMouse::MouseEventType::MOUSE_MOVE);
    
	// Set current button
	if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		event.setMouseButton(SDL_BUTTON_LEFT);
	}
	else if (mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		event.setMouseButton(SDL_BUTTON_RIGHT);
	}
	else if (mouseState & SDL_BUTTON(SDL_BUTTON_MIDDLE))
	{
		event.setMouseButton(SDL_BUTTON_MIDDLE);
	}
    
	event.setCursorPosition(cursorX, cursorY);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

void GLViewImpl::onMouseScrollCallback(double x, double y)
{
    y /= _wheelScrollScale;
    float mouseX = static_cast<float>(x) / this->getFrameZoomFactor();
    float mouseY = static_cast<float>(y) / this->getFrameZoomFactor();
    
	EventMouse event(EventMouse::MouseEventType::MOUSE_SCROLL);
	float cursorX = (mouseX - _viewPortRect.origin.x) / _scaleX;
	float cursorY = (mouseY - _viewPortRect.origin.y) / _scaleY;
	event.setScrollData(static_cast<float>(x), -static_cast<float>(y));
	event.setCursorPosition(cursorX, cursorY);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

void GLViewImpl::onKeyCallback(int key, int action, int repeat)
{
    if (repeat == 0)
	{
		EventKeyboard event(g_keyCodeMap[key], SDL_PRESSED == action);
		auto dispatcher = Director::getInstance()->getEventDispatcher();
		dispatcher->dispatchEvent(&event);
	}
    
    if (SDL_RELEASED != action && g_keyCodeMap[key] == EventKeyboard::KeyCode::KEY_BACKSPACE)
	{
		IMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
	}
}

void GLViewImpl::setViewPortInPoints(float x , float y , float w , float h)
{
    experimental::Viewport vp((float)(x * _scaleX * _frameZoomFactor + _viewPortRect.origin.x * _frameZoomFactor),
                              (float)(y * _scaleY * _frameZoomFactor + _viewPortRect.origin.y * _frameZoomFactor),
                              (float)(w * _scaleX * _frameZoomFactor),
                              (float)(h * _scaleY * _frameZoomFactor));
    Camera::setDefaultViewport(vp);
}

void GLViewImpl::setScissorInPoints(float x , float y , float w , float h)
{
    glScissor((GLint)(x * _scaleX * _frameZoomFactor + _viewPortRect.origin.x * _frameZoomFactor),
              (GLint)(y * _scaleY * _frameZoomFactor + _viewPortRect.origin.y * _frameZoomFactor),
              (GLsizei)(w * _scaleX * _frameZoomFactor),
              (GLsizei)(h * _scaleY * _frameZoomFactor));
}

Rect GLViewImpl::getScissorRect() const
{
    GLfloat params[4];
    glGetFloatv(GL_SCISSOR_BOX, params);
    float x = (params[0] - _viewPortRect.origin.x * _frameZoomFactor) / (_scaleX * _frameZoomFactor);
    float y = (params[1] - _viewPortRect.origin.y * _frameZoomFactor) / (_scaleY * _frameZoomFactor);
    float w = params[2] / (_scaleX * _frameZoomFactor);
    float h = params[3] / (_scaleY * _frameZoomFactor);
    return Rect(x, y, w, h);
}

void GLViewImpl::onCharCallback(unsigned int character)
{
	char16_t wcharString[2] = { (char16_t)character, 0 };
	std::string utf8String;

	StringUtils::UTF16ToUTF8(wcharString, utf8String);
	IMEDispatcher::sharedDispatcher()->dispatchInsertText(utf8String.c_str(), utf8String.size());
}

void GLViewImpl::setIMEKeyboardState(bool open)
{
    if (open)
    {
        SDL_StartTextInput();
    }
    else
    {
        SDL_StopTextInput();
    }
}


NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
