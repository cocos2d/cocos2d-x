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

#include <stdlib.h>

// XXX: For sleep -- remove.
#include <unistd.h>

extern "C" {
void glutInit(int *argcp, char **argv);
void glutMouseFunc(void (*func)(int button, int state, int x, int y));
void glutMotionFunc(void (*func)(int x, int y));
void glutPassiveMotionFunc(void (*func)(int x, int y));
}

// Constants for mouse events (inferred from experiment)
static const int glutLeftButton = 0;
static const int glutMouseDown = 0;
static const int glutMouseUp = 1;

NS_CC_BEGIN

bool CCEGLView::m_initializedFunctions = false;
const GLubyte *CCEGLView::m_extensions = 0;

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

static bool buttonDepressed = false;
extern "C" void mouseCB(int button, int state, int x, int y)
{
    float fx = x;
    float fy = y;
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    int id = 0;

    if(button != glutLeftButton) return;

    if(state == glutMouseDown)
    {
        pEGLView->handleTouchesBegin(1, &id, &fx, &fy);
        buttonDepressed = true;
    }
    else if(state == glutMouseUp)
    {
        pEGLView->handleTouchesEnd(1, &id, &fx, &fy);
        buttonDepressed = false;
    }
}

extern "C" void motionCB(int x, int y)
{
    float fx = x;
    float fy = y;
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    int id = 0;

    if(buttonDepressed)
    {
        pEGLView->handleTouchesMove(1, &id, &fx, &fy);
    }
}

CCEGLView::CCEGLView()
{
	m_eglDisplay = EGL_NO_DISPLAY;
	m_eglContext = EGL_NO_CONTEXT;
	m_eglSurface = EGL_NO_SURFACE;

    strcpy(m_windowGroupID, "");
    snprintf(m_windowGroupID, sizeof(m_windowGroupID), "%d", 1);

    m_isGLInitialized = initGL();

    if (m_isGLInitialized)
    	initEGLFunctions();

    char *arg1 = (char*)malloc(1);
    char **dummyArgv = (char**)malloc(sizeof(char*));
    dummyArgv[0] = arg1;
    glutInit(0, dummyArgv);
    free(dummyArgv[0]);
    free(dummyArgv);

    glutMouseFunc(&mouseCB);
    glutMotionFunc(&motionCB);
    glutPassiveMotionFunc(&motionCB);

}

CCEGLView::~CCEGLView()
{
}

const char* CCEGLView::getWindowGroupId() const
{
	return m_windowGroupID;
}

void CCEGLView::release()
{
    if (m_eglDisplay != EGL_NO_DISPLAY)
    {
        eglMakeCurrent(m_eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    }

    if (m_eglSurface != EGL_NO_SURFACE)
    {
        eglDestroySurface(m_eglDisplay, m_eglSurface);
        m_eglSurface = EGL_NO_SURFACE;
    }

    if (m_eglContext != EGL_NO_CONTEXT)
    {
        eglDestroyContext(m_eglDisplay, m_eglContext);
        m_eglContext = EGL_NO_CONTEXT;
    }

    if (m_eglDisplay != EGL_NO_DISPLAY)
    {
        eglTerminate(m_eglDisplay);
        m_eglDisplay = EGL_NO_DISPLAY;
    }

	eglReleaseThread();

	m_isGLInitialized = false;

	exit(0);
}

void CCEGLView::initEGLFunctions()
{
	m_extensions = glGetString(GL_EXTENSIONS);
	m_initializedFunctions = true;
}

bool CCEGLView::isOpenGLReady()
{
//	return (m_isGLInitialized && m_screenWidth != 0 && m_screenHeight != 0);
	return (m_isGLInitialized && m_obScreenSize.height != 0 && m_obScreenSize.width != 0);
}

void CCEGLView::end()
{
    release();
}

void CCEGLView::swapBuffers()
{
	eglSwapBuffers(m_eglDisplay, m_eglSurface);
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
}

void CCEGLView::hideKeyboard()
{
}

void CCEGLView::setIMEKeyboardState(bool bOpen)
{
}

bool CCEGLView::isGLExtension(const char *searchName) const
{
	const GLubyte *start;
	GLubyte *where, *terminator;

	/* It takes a bit of care to be fool-proof about parsing the
	 OpenGL extensions string. Don't be fooled by sub-strings,
	 etc. */
	start = m_extensions;
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
    int angle = 0;

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



    // Get the EGL display and initialize.
    m_eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (m_eglDisplay == EGL_NO_DISPLAY)
    {
        perror("eglGetDisplay");
        return false;
    }

    sleep(1);

    if (eglInitialize(m_eglDisplay, NULL, NULL) != EGL_TRUE)
    {
        perror("eglInitialize");
        return false;
    }

    if (eglChooseConfig(m_eglDisplay, eglConfigAttrs, &config, 1, &eglConfigCount) != EGL_TRUE || eglConfigCount == 0)
    {
        checkErrorEGL("eglChooseConfig");
        return false;
    }

    m_eglContext = eglCreateContext(m_eglDisplay, config, EGL_NO_CONTEXT, eglContextAttrs);
    if (m_eglContext == EGL_NO_CONTEXT)
    {
        checkErrorEGL("eglCreateContext");
        return false;
    }

    m_eglSurface = eglCreateWindowSurface(m_eglDisplay, config, NULL, eglSurfaceAttrs);
    if (m_eglSurface == EGL_NO_SURFACE)
    {
        checkErrorEGL("eglCreateWindowSurface");
        return false;
    }

    if (eglMakeCurrent(m_eglDisplay, m_eglSurface, m_eglSurface, m_eglContext) != EGL_TRUE)
    {
        checkErrorEGL("eglMakeCurrent");
        return false;
    }

    // FIXME: Get the actual canvas size somehow.
    EGLint width = 800;
    EGLint height = 500;
#warning Assuming screen size is 800X500. Mouse cursor will be offset if a different sized canvas is used.

    if ((m_eglDisplay == EGL_NO_DISPLAY) || (m_eglSurface == EGL_NO_SURFACE) )
    	return EXIT_FAILURE;

    /*
	eglQuerySurface(m_eglDisplay, m_eglSurface, EGL_WIDTH, &width);
    eglQuerySurface(m_eglDisplay, m_eglSurface, EGL_HEIGHT, &height);
    */

    m_obScreenSize.width = width;
    m_obScreenSize.height = height;

    printf("width, height = %d, %d\n", width, height);

    glViewport(0, 0, width, height);

    // Set vsync.
//    eglSwapInterval(m_eglDisplay, screenSwapInterval);

    return true;
}

static long time2millis(struct timespec *times)
{
    return times->tv_sec*1000 + times->tv_nsec/1000000;
}

bool CCEGLView::handleEvents()
{
	return true;
}

NS_CC_END
