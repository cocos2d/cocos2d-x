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
#include "CCDirector.h"
#include "ccMacros.h"
#include "touch_dispatcher/CCTouch.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "text_input_node/CCIMEDispatcher.h"
#include "keypad_dispatcher/CCKeypadDispatcher.h"
#include "CCGL.h"
#include "CCAccelerometer.h"
#include "CCApplication.h"

#include <ctype.h>
#include <input/screen_helpers.h>
#include <sys/keycodes.h>

#include <bps/bps.h>
#include <bps/event.h>
#include <bps/screen.h>
#include <bps/navigator.h>
#include <bps/orientation.h>
#include <bps/sensor.h>
#include <bps/virtualkeyboard.h>

#include <stdlib.h>

#if CC_TEXTURE_ATLAS_USE_VAO
PFNGLGENVERTEXARRAYSOESPROC glGenVertexArrays = 0;
PFNGLBINDVERTEXARRAYOESPROC glBindVertexArray = 0;
PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArrays = 0;
#endif

PFNGLMAPBUFFEROESPROC glMapBuffer = 0;
PFNGLUNMAPBUFFEROESPROC glUnmapBuffer = 0;
PFNGLGETBUFFERPOINTERVOESPROC glGetBufferPointerv = 0;

NS_CC_BEGIN

bool CCEGLView::_initializedFunctions = false;
const GLubyte *CCEGLView::_extensions = 0;

enum Orientation
{
	PORTRAIT,
	LANDSCAPE,
	AUTO
};

static Orientation orientation = LANDSCAPE;

#define MAX_TOUCHES         4
static CCTouch *s_pTouches[MAX_TOUCHES] = { NULL };
static CCEGLView* s_pInstance = NULL;

CCEGLView::CCEGLView()
	: _eventHandler(NULL)
{
	_eglDisplay = EGL_NO_DISPLAY;
	_eglContext = EGL_NO_CONTEXT;
	_eglSurface = EGL_NO_SURFACE;
    _screenEvent = 0;
    _screenWindow = 0;

    strcpy(_windowGroupID, "");
    snprintf(_windowGroupID, sizeof(_windowGroupID), "%d", getpid());
    bps_initialize();
    navigator_request_events(0);

    static const int SENSOR_RATE = 25000;
    sensor_set_rate(SENSOR_TYPE_ACCELEROMETER, SENSOR_RATE);
    sensor_request_events(SENSOR_TYPE_ACCELEROMETER);

    navigator_rotation_lock(true);

    _isGLInitialized = initGL();

    if (_isGLInitialized)
    	initEGLFunctions();
}

CCEGLView::~CCEGLView()
{
}

void CCEGLView::setEventHandler(EventHandler* pHandler)
{
	_eventHandler = pHandler;
}

const char* CCEGLView::getWindowGroupId() const
{
	return _windowGroupID;
}

void CCEGLView::release()
{
	screen_stop_events(_screenContext);

	bps_shutdown();

    if (_eglDisplay != EGL_NO_DISPLAY)
    {
        eglMakeCurrent(_eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    }

    if (_eglSurface != EGL_NO_SURFACE)
    {
        eglDestroySurface(_eglDisplay, _eglSurface);
        _eglSurface = EGL_NO_SURFACE;
    }

    if (_eglContext != EGL_NO_CONTEXT)
    {
        eglDestroyContext(_eglDisplay, _eglContext);
        _eglContext = EGL_NO_CONTEXT;
    }

    if (_eglDisplay != EGL_NO_DISPLAY)
    {
        eglTerminate(_eglDisplay);
        _eglDisplay = EGL_NO_DISPLAY;
    }

    if (_screenWindow)
    {
        screen_destroy_window(_screenWindow);
        _screenWindow = NULL;
    }

    if (_screenEvent)
    {
    	screen_destroy_event(_screenEvent);
    	_screenEvent = NULL;
    }

    if (_screenContext)
    {
        screen_destroy_context(_screenContext);
        _screenContext = NULL;
    }

	eglReleaseThread();

	_isGLInitialized = false;

	exit(0);
}

void CCEGLView::initEGLFunctions()
{
	_extensions = glGetString(GL_EXTENSIONS);

#if CC_TEXTURE_ATLAS_USE_VAO
    if (isGLExtension("GL_OES_vertex_array_object") || isGLExtension("GL_ARB_vertex_array_object"))
    {
    	glGenVertexArrays = (PFNGLGENVERTEXARRAYSOESPROC)eglGetProcAddress("glGenVertexArraysOES");
    	glBindVertexArray = (PFNGLBINDVERTEXARRAYOESPROC)eglGetProcAddress("glBindVertexArrayOES");
        glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSOESPROC)eglGetProcAddress("glDeleteVertexArraysOES");
    }
#endif

    glMapBuffer = (PFNGLMAPBUFFEROESPROC)eglGetProcAddress("glMapBufferOES");
    glUnmapBuffer = (PFNGLUNMAPBUFFEROESPROC)eglGetProcAddress("glUnmapBufferOES");
    glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVOESPROC)eglGetProcAddress("glGetBufferPointervOES");


	_initializedFunctions = true;
}

bool CCEGLView::isOpenGLReady()
{
//	return (_isGLInitialized && _screenWidth != 0 && _screenHeight != 0);
	return (_isGLInitialized && _screenSize.height != 0 && _screenSize.width != 0);
}

void CCEGLView::end()
{
    release();
}

void CCEGLView::swapBuffers()
{
	eglSwapBuffers(_eglDisplay, _eglSurface);
}

CCEGLView* CCEGLView::sharedOpenGLView()
{
	if (!s_pInstance)
	{
		s_pInstance = new CCEGLView();
	}

	CCAssert(s_pInstance != NULL, "CCEGLView wasn't constructed yet");
	return s_pInstance;
}

void CCEGLView::showKeyboard()
{
	int height;

	virtualkeyboard_get_height(&height);

	float factor = _scaleY / CC_CONTENT_SCALE_FACTOR();
	height = (float)height / factor;

	CCRect rect_begin(0, 0 - height, _screenSize.width / factor, height);
	CCRect rect_end(0, 0, _screenSize.width / factor, height);

    CCIMEKeyboardNotificationInfo info;
    info.begin = rect_begin;
    info.end = rect_end;
    info.duration = 0;

    CCIMEDispatcher::sharedDispatcher()->dispatchKeyboardWillShow(info);
    virtualkeyboard_show();
    CCIMEDispatcher::sharedDispatcher()->dispatchKeyboardDidShow(info);
}

void CCEGLView::hideKeyboard()
{
	virtualkeyboard_hide();
}

void CCEGLView::setIMEKeyboardState(bool bOpen)
{
	if (bOpen)
		showKeyboard();
	else
		hideKeyboard();
}

bool CCEGLView::isGLExtension(const char *searchName) const
{
	const GLubyte *start;
	GLubyte *where, *terminator;

	/* It takes a bit of care to be fool-proof about parsing the
	 OpenGL extensions string. Don't be fooled by sub-strings,
	 etc. */
	start = _extensions;
	for (;;)
	{
		where = (GLubyte *) strstr((const char *) start, searchName);
		if (!where)
			break;

		terminator = where + strlen(searchName);
		if (where == start || *(where - 1) == ' ')
			if (*terminator == ' ' || *terminator == '\0')
				return true;

		start = terminator;
	}

	return false;
}


static EGLenum checkErrorEGL(const char* msg)
{
    assert(msg);
    static const char* errmsg[] =
    {
        "EGL function succeeded",
        "EGL is not initialized, or could not be initialized, for the specified display",
        "EGL cannot access a requested resource",
        "EGL failed to allocate resources for the requested operation",
        "EGL fail to access an unrecognized attribute or attribute value was passed in an attribute list",
        "EGLConfig argument does not name a valid EGLConfig",
        "EGLContext argument does not name a valid EGLContext",
        "EGL current surface of the calling thread is no longer valid",
        "EGLDisplay argument does not name a valid EGLDisplay",
        "EGL arguments are inconsistent",
        "EGLNativePixmapType argument does not refer to a valid native pixmap",
        "EGLNativeWindowType argument does not refer to a valid native window",
        "EGL one or more argument values are invalid",
        "EGLSurface argument does not name a valid surface configured for rendering",
        "EGL power management event has occurred",
    };
    EGLenum error = eglGetError();
    fprintf(stderr, "%s: %s\n", msg, errmsg[error - EGL_SUCCESS]);
    return error;
}

bool CCEGLView::initGL()
{
    int rc = 0;
    int screenFormat = SCREEN_FORMAT_RGBA8888;
#ifdef __X86__
    int screenUsage = SCREEN_USAGE_OPENGL_ES2;
#else
    int screenUsage = SCREEN_USAGE_DISPLAY|SCREEN_USAGE_OPENGL_ES2; // Physical device copy directly into physical display
#endif
//    int screenSwapInterval = WINDOW_VSYNC ? 1 : 0;
    int screenTransparency = SCREEN_TRANSPARENCY_NONE;
    int angle = atoi(getenv("ORIENTATION"));

    // Hard-coded to (0,0).
    int windowPosition[] =
    {
        0, 0
    };

    EGLint eglConfigCount;
    EGLConfig config;

    // Hard-coded to 32-bit/OpenGL ES 2.0.
    const EGLint eglConfigAttrs[] =
    {
        EGL_RED_SIZE,           8,
        EGL_GREEN_SIZE,         8,
        EGL_BLUE_SIZE,          8,
        EGL_ALPHA_SIZE,         8,
        EGL_DEPTH_SIZE,         24,
        EGL_STENCIL_SIZE,       8,
        EGL_SURFACE_TYPE,       EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE,    EGL_OPENGL_ES2_BIT,
        EGL_NONE
    };

    const EGLint eglContextAttrs[] =
    {
        EGL_CONTEXT_CLIENT_VERSION,    2,
        EGL_NONE
    };

    const EGLint eglSurfaceAttrs[] =
    {
        EGL_RENDER_BUFFER,    EGL_BACK_BUFFER,
        EGL_NONE
    };

    // Create the screen context.
    rc = screen_create_context(&_screenContext, SCREEN_APPLICATION_CONTEXT);
    if (rc)
    {
        perror("screen_create_context");
        return false;
    }

    // Create the screen window.
    rc = screen_create_window(&_screenWindow, _screenContext);
    if (rc)
    {
        perror("screen_create_window");
        return false;
    }

    rc = screen_create_window_group(_screenWindow, _windowGroupID);
	if (rc)
	{
		perror("screen_create_window_group");
		return false;
	}
    // Set/get any window prooperties.
    rc = screen_set_window_property_iv(_screenWindow, SCREEN_PROPERTY_FORMAT, &screenFormat);
    if (rc)
    {
        perror("screen_set_window_property_iv(SCREEN_PROPERTY_FORMAT)");
        return false;
    }

    rc = screen_set_window_property_iv(_screenWindow, SCREEN_PROPERTY_USAGE, &screenUsage);
    if (rc)
    {
        perror("screen_set_window_property_iv(SCREEN_PROPERTY_USAGE)");
        return false;
    }


	char *width_str = getenv("WIDTH");
	char *height_str = getenv("HEIGHT");

	if (width_str && height_str)
	{
		int screen_res[2];
		screen_res[0] = atoi(width_str);
		screen_res[1] = atoi(height_str);

		rc = screen_set_window_property_iv(_screenWindow, SCREEN_PROPERTY_BUFFER_SIZE, screen_res);
		if (rc)
		{
			fprintf(stderr, "screen_set_window_property_iv(SCREEN_PROPERTY_BUFFER_SIZE)");
			return false;
		}

        rc = screen_get_window_property_pv(_screenWindow, SCREEN_PROPERTY_DISPLAY, (void **)&_screen_display);
        if (rc)
        {
            perror("screen_get_window_property_pv(SCREEN_PROPERTY_DISPLAY)");
            return false;
        }
	}
	else
	{
	    rc = screen_get_window_property_pv(_screenWindow, SCREEN_PROPERTY_DISPLAY, (void **)&_screen_display);
	    if (rc)
	    {
	        perror("screen_get_window_property_pv(SCREEN_PROPERTY_DISPLAY)");
	        return false;
	    }

	    screen_display_mode_t screen_mode;
	    rc = screen_get_display_property_pv(_screen_display, SCREEN_PROPERTY_MODE, (void**)&screen_mode);
	    if (rc)
	    {
	        perror("screen_get_display_property_pv(SCREEN_PROPERTY_MODE)");
	        return false;
	    }

	    int size[2];
	    rc = screen_get_window_property_iv(_screenWindow, SCREEN_PROPERTY_BUFFER_SIZE, size);
	    if (rc)
	    {
	        perror("screen_get_window_property_iv(SCREEN_PROPERTY_BUFFER_SIZE)");
	        return false;
	    }

	    int buffer_size[2] = { size[0], size[1] };

		if ((angle == 0) || (angle == 180))
		{
			if (((screen_mode.width > screen_mode.height) && (size[0] < size[1])) ||
				((screen_mode.width < screen_mode.height) && (size[0] > size[1])))
			{
				buffer_size[1] = size[0];
				buffer_size[0] = size[1];
			}
		}
		else if ((angle == 90) || (angle == 270))
		{
			if (((screen_mode.width > screen_mode.height) && (size[0] > size[1])) ||
				((screen_mode.width < screen_mode.height) && (size[0] < size[1])))
			{
				buffer_size[1] = size[0];
				buffer_size[0] = size[1];
			}
		}
		else
		{
			perror("Navigator returned an unexpected orientation angle.");
			return false;
		}

	    rc = screen_set_window_property_iv(_screenWindow, SCREEN_PROPERTY_ROTATION, &angle);
	    if (rc)
	    {
	        perror("screen_set_window_property_iv(SCREEN_PROPERTY_ROTATION)");
	        return false;
	    }

	    rc = screen_set_window_property_iv(_screenWindow, SCREEN_PROPERTY_BUFFER_SIZE, buffer_size);
	    if (rc)
	    {
	        perror("screen_set_window_property_iv(SCREEN_PROPERTY_BUFFER_SIZE)");
	        return false;
	    }
	}

    if (windowPosition[0] != 0 || windowPosition[1] != 0)
    {
        rc = screen_set_window_property_iv(_screenWindow, SCREEN_PROPERTY_POSITION, windowPosition);
        if (rc)
        {
            perror("screen_set_window_property_iv(SCREEN_PROPERTY_POSITION)");
            return false;
        }
    }

    rc = screen_set_window_property_iv(_screenWindow, SCREEN_PROPERTY_TRANSPARENCY, &screenTransparency);
    if (rc)
    {
        perror("screen_set_window_property_iv(SCREEN_PROPERTY_TRANSPARENCY)");
        return false;
    }

    // Double buffered.
    rc = screen_create_window_buffers(_screenWindow, 2);
    if (rc)
    {
        perror("screen_create_window_buffers");
        return false;
    }

    // Create screen event object.
    rc = screen_create_event(&_screenEvent);
    if (rc)
    {
        perror("screen_create_event");
        return false;
    }

    // Request screen events.
    screen_request_events(_screenContext);

    // Get the EGL display and initialize.
    _eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (_eglDisplay == EGL_NO_DISPLAY)
    {
        perror("eglGetDisplay");
        return false;
    }
    if (eglInitialize(_eglDisplay, NULL, NULL) != EGL_TRUE)
    {
        perror("eglInitialize");
        return false;
    }

    if (eglChooseConfig(_eglDisplay, eglConfigAttrs, &config, 1, &eglConfigCount) != EGL_TRUE || eglConfigCount == 0)
    {
        checkErrorEGL("eglChooseConfig");
        return false;
    }

    _eglContext = eglCreateContext(_eglDisplay, config, EGL_NO_CONTEXT, eglContextAttrs);
    if (_eglContext == EGL_NO_CONTEXT)
    {
        checkErrorEGL("eglCreateContext");
        return false;
    }

    _eglSurface = eglCreateWindowSurface(_eglDisplay, config, _screenWindow, eglSurfaceAttrs);
    if (_eglSurface == EGL_NO_SURFACE)
    {
        checkErrorEGL("eglCreateWindowSurface");
        return false;
    }

    if (eglMakeCurrent(_eglDisplay, _eglSurface, _eglSurface, _eglContext) != EGL_TRUE)
    {
        checkErrorEGL("eglMakeCurrent");
        return false;
    }

    EGLint width, height;

    if ((_eglDisplay == EGL_NO_DISPLAY) || (_eglSurface == EGL_NO_SURFACE) )
    	return EXIT_FAILURE;

	eglQuerySurface(_eglDisplay, _eglSurface, EGL_WIDTH, &width);
    eglQuerySurface(_eglDisplay, _eglSurface, EGL_HEIGHT, &height);

    _screenSize.width = width;
    _screenSize.height = height;

    // Set vsync.
//    eglSwapInterval(_eglDisplay, screenSwapInterval);

    return true;
}

static long time2millis(struct timespec *times)
{
    return times->tv_sec*1000 + times->tv_nsec/1000000;
}

bool CCEGLView::handleEvents()
{
	bps_event_t*    event = NULL;
	mtouch_event_t  mtouch_event;
	int				touch_id = 0;
	int				val = 0;
	int				rc = 0;
	int 			domain = 0;
	char 			buf[4] = {0};

	for (;;)
	{
		rc = bps_get_event(&event, 1);
		assert(rc == BPS_SUCCESS);

		// break if no more events
		if (event == NULL)
			break;
			
		if (_eventHandler && _eventHandler->HandleBPSEvent(event))
			continue;

		domain = bps_event_get_domain(event);

		if (domain == navigator_get_domain())
		{
			switch (bps_event_get_code(event))
			{
				case NAVIGATOR_SWIPE_DOWN:
					CCDirector::sharedDirector()->getKeypadDispatcher()->dispatchKeypadMSG(kTypeMenuClicked);
					break;

				case NAVIGATOR_EXIT:
					// exit the application
				//	release();
					end();
					break;

				case NAVIGATOR_WINDOW_INACTIVE:
					if (_isWindowActive)
					{
						CCApplication::sharedApplication()->applicationDidEnterBackground();
						_isWindowActive = false;
					}
					break;

				case NAVIGATOR_WINDOW_ACTIVE:
					if (!_isWindowActive)
					{
						CCApplication::sharedApplication()->applicationWillEnterForeground();
						_isWindowActive = true;
					}
					break;

				case NAVIGATOR_WINDOW_STATE:
				{
					switch(navigator_event_get_window_state(event))
					{
						case NAVIGATOR_WINDOW_FULLSCREEN:
							if (!_isWindowActive)
							{
								CCApplication::sharedApplication()->applicationWillEnterForeground();
								_isWindowActive = true;
							}
							break;
						case NAVIGATOR_WINDOW_THUMBNAIL:
							if (_isWindowActive)
							{
								CCApplication::sharedApplication()->applicationDidEnterBackground();
								_isWindowActive = false;
							}
							break;
					}
					break;
				}

				default:
					break;
			}
		}
		else if (domain == screen_get_domain())
		{
			_screenEvent = screen_event_get_event(event);
			rc = screen_get_event_property_iv(_screenEvent, SCREEN_PROPERTY_TYPE, &val);
			if (rc || val == SCREEN_EVENT_NONE)
				break;

			float x, y;

			switch (val)
			{
				case SCREEN_EVENT_CLOSE:
					fprintf(stderr, "SCREEN CLOSE EVENT!\n");
					break;

				case SCREEN_EVENT_MTOUCH_RELEASE:
					screen_get_mtouch_event(_screenEvent, &mtouch_event, 0);
					touch_id = mtouch_event.contact_id;
					x = mtouch_event.x;
					y = mtouch_event.y;

					handleTouchesEnd(1, &touch_id, &x, &y);

					break;

				case SCREEN_EVENT_MTOUCH_TOUCH:
					screen_get_mtouch_event(_screenEvent, &mtouch_event, 0);
					touch_id = mtouch_event.contact_id;
					x = mtouch_event.x;
					y = mtouch_event.y;

					handleTouchesBegin(1, &touch_id, &x, &y);

					break;

				case SCREEN_EVENT_MTOUCH_MOVE:
					screen_get_mtouch_event(_screenEvent, &mtouch_event, 0);
					touch_id = mtouch_event.contact_id;
					x = mtouch_event.x;
					y = mtouch_event.y;

					handleTouchesMove(1, &touch_id, &x, &y);

					break;

				case SCREEN_EVENT_POINTER:
					{
						int buttons = 0;
						int pair_[2] = {0};
						float pair[2] = {0.0f};
						static bool mouse_pressed = false;

						// this is a mouse move event, it is applicable to a device with a usb mouse or simulator
						screen_get_event_property_iv(_screenEvent, SCREEN_PROPERTY_BUTTONS, &buttons);
						screen_get_event_property_iv(_screenEvent, SCREEN_PROPERTY_SOURCE_POSITION, pair_);
						pair[0] = (float)pair_[0];
						pair[1] = (float)pair_[1];
						if (buttons & SCREEN_LEFT_MOUSE_BUTTON)
						{
							if (mouse_pressed)
							{
								handleTouchesMove(1, &touch_id, &pair[0], &pair[1]);
							}
							else
							{
								// Left mouse button is pressed
								mouse_pressed = true;

								handleTouchesBegin(1, &touch_id, &pair[0], &pair[1]);
							}
						}
						else
						{
							if (mouse_pressed)
							{
								mouse_pressed = false;
								handleTouchesEnd(1, &touch_id, &pair[0], &pair[1]);
							}
						}
					}
					break;

				case SCREEN_EVENT_KEYBOARD:
					screen_get_event_property_iv(_screenEvent, SCREEN_PROPERTY_KEY_FLAGS, &val);
					if (val & KEY_DOWN)
					{
						screen_get_event_property_iv(_screenEvent, SCREEN_PROPERTY_KEY_SYM, &val);

						if (val >= ' ' && val < '~')
						{
							buf[0] = val;
							buf[1]=  '\0';
							CCIMEDispatcher::sharedDispatcher()->dispatchInsertText(buf, 1);
						}
						else
						{
							val = val - 0xf000;
							buf[0] = val;
							buf[1]=  '\0';

							switch (val)
							{
								case 8: // backspace
									//		CCKeypadDispatcher::sharedDispatcher()->dispatchKeypadMSG(kTypeBackClicked);
									CCIMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
									break;

								default:
									CCIMEDispatcher::sharedDispatcher()->dispatchInsertText(buf, 1);
									break;
							}
						}
					}

					break;

				default:
					break;
			}
		}
        else if (domain == sensor_get_domain())
        {
            if (bps_event_get_code(event) == SENSOR_ACCELEROMETER_READING)
            {
            	struct timespec time_struct;
            	long current_time;
                float x, y, z;

                clock_gettime(CLOCK_REALTIME, &time_struct);
                current_time = time2millis(&time_struct);

                sensor_event_get_xyz(event, &x, &y, &z);
                CCDirector::sharedDirector()->getAccelerometer()->update(current_time, -x, -y, z);
            }
        }
	}

	return true;
}

screen_display_t CCEGLView::getScreenDisplay() const
{
    return _screen_display;
}

NS_CC_END
