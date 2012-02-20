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

#include "CCEGLView_qnx.h"
#include "GLES/gl.h"

#include <ctype.h>
#include <input/screen_helpers.h>
#include <sys/keycodes.h>

#include <bps/bps.h>
#include <bps/event.h>
#include <bps/screen.h>
#include <bps/navigator.h>
#include <bps/orientation.h>
#include <bps/virtualkeyboard.h>

#include "CCSet.h"
#include "CCDirector.h"
#include "CCApplication.h"
#include "ccMacros.h"
#include "CCTouch.h"
#include "CCTouchDispatcher.h"
#include "CCKeypadDispatcher.h"
#include "CCIMEDispatcher.h"


using namespace std;

namespace cocos2d {

bool CCEGLView::m_initializedFunctions = false;
const GLubyte *CCEGLView::m_extensions = 0;

PFNGLGENERATEMIPMAPOESPROC         CCEGLView::glGenerateMipmapOES = 0;
PFNGLGENFRAMEBUFFERSOESPROC        CCEGLView::glGenFramebuffersOES = 0;
PFNGLBINDFRAMEBUFFEROESPROC		   CCEGLView::glBindFramebufferOES = 0;
PFNGLFRAMEBUFFERTEXTURE2DOESPROC   CCEGLView::glFramebufferTexture2DOES = 0;
PFNGLDELETEFRAMEBUFFERSOESPROC     CCEGLView::glDeleteFramebuffersOES = 0;
PFNGLCHECKFRAMEBUFFERSTATUSOESPROC CCEGLView::glCheckFramebufferStatusOES = 0;

enum Orientation
{
	PORTRAIT,
	LANDSCAPE,
	AUTO
};

static Orientation orientation = LANDSCAPE;

static struct {
	EGLint surface_type;
	EGLint red_size;
	EGLint green_size;
	EGLint blue_size;
	EGLint alpha_size;
	EGLint samples;
	EGLint config_id;
} the_configAttr;

#define MAX_TOUCHES         4
static CCTouch *s_pTouches[MAX_TOUCHES] = { NULL };
static CCEGLView* s_pInstance = NULL;

CCEGLView::CCEGLView()
: m_pDelegate(NULL),
  m_fScreenScaleFactor(1.0),
  m_bNotHVGA(false),
  m_isWindowActive(false)
{
	s_pInstance = this;
	m_eglDisplay = EGL_NO_DISPLAY;
	m_eglContext = EGL_NO_CONTEXT;
	m_eglSurface = EGL_NO_SURFACE;
    m_screenEvent = 0;
    m_screenWindow = 0;

    bps_initialize();
    navigator_request_events(0);

    navigator_rotation_lock(true);

    the_configAttr.surface_type = EGL_WINDOW_BIT;
    the_configAttr.red_size 	= EGL_DONT_CARE;
    the_configAttr.green_size 	= EGL_DONT_CARE;
	the_configAttr.blue_size 	= EGL_DONT_CARE;
	the_configAttr.alpha_size 	= EGL_DONT_CARE;
	the_configAttr.samples 		= EGL_DONT_CARE;
	the_configAttr.config_id 	= EGL_DONT_CARE;

    m_isGLInitialized = initGL();

    if (m_isGLInitialized)
    	initEGLFunctions();
}

CCEGLView::~CCEGLView()
{
	release();

	CC_SAFE_DELETE(m_pDelegate);
}

void CCEGLView::initEGLFunctions()
{
	m_extensions = glGetString(GL_EXTENSIONS);

	glGenerateMipmapOES = 0;
	glGenFramebuffersOES = 0;
	glBindFramebufferOES = 0;
	glFramebufferTexture2DOES = 0;
	glDeleteFramebuffersOES = 0;
	glCheckFramebufferStatusOES = 0;

	if (isGLExtension("GL_OES_framebuffer_object"))
	{
		glGenerateMipmapOES = (PFNGLGENERATEMIPMAPOESPROC)eglGetProcAddress("glGenerateMipmapOES");
		glGenFramebuffersOES = (PFNGLGENFRAMEBUFFERSOESPROC)eglGetProcAddress("glGenFramebuffersOES");
		glBindFramebufferOES = (PFNGLBINDFRAMEBUFFEROESPROC)eglGetProcAddress("glBindFramebufferOES");
		glFramebufferTexture2DOES = (PFNGLFRAMEBUFFERTEXTURE2DOESPROC)eglGetProcAddress("glFramebufferTexture2DOES");
		glDeleteFramebuffersOES = (PFNGLDELETEFRAMEBUFFERSOESPROC)eglGetProcAddress("glDeleteFramebuffersOES");
		glCheckFramebufferStatusOES = (PFNGLCHECKFRAMEBUFFERSTATUSOESPROC)eglGetProcAddress("glCheckFramebufferStatusOES");
	}

	m_initializedFunctions = true;
}

void CCEGLView::setFrameWidthAndHeight(int width, int height)
{
	m_sSizeInPixel.width = width;
	m_sSizeInPixel.height = height;
}

bool CCEGLView::Create(int width, int height)
{
	if (width == 0 || height == 0)
	{
		return false;
	}

	m_sSizeInPoint.width = width;
	m_sSizeInPoint.height = height;

	// calculate the factor and the rect of viewport	
	m_fScreenScaleFactor =  MIN((float)m_sSizeInPixel.width / m_sSizeInPoint.width,
		                        (float)m_sSizeInPixel.height / m_sSizeInPoint.height);

	int viewPortW = (int)(m_sSizeInPoint.width * m_fScreenScaleFactor);
	int viewPortH = (int)(m_sSizeInPoint.height * m_fScreenScaleFactor);

	m_rcViewPort.origin.x = (m_sSizeInPixel.width - viewPortW) / 2;
	m_rcViewPort.origin.y = (m_sSizeInPixel.height - viewPortH) / 2;
	m_rcViewPort.size.width = viewPortW;
	m_rcViewPort.size.height = viewPortH;
	
	m_bNotHVGA = true;
	
	return true;
}

EGLConfig CCEGLView::chooseConfig(const EGLDisplay &eglDisplay, const char* str)
{
	EGLConfig   config = (EGLConfig)0;
	EGLConfig  *configurations;
	EGLint      egl_num_configs;
	EGLint      val;
	EGLBoolean  rc;
	const char *tok;
	EGLint      i;

	if (str != NULL)
	{
		tok = str;
		while (*tok == ' ' || *tok == ',')
			tok++;

		while (*tok != '\0')
		{
			if (strncmp(tok, "rgba8888", strlen("rgba8888")) == 0)
			{
				the_configAttr.red_size   = 8;
				the_configAttr.green_size = 8;
				the_configAttr.blue_size  = 8;
				the_configAttr.alpha_size = 8;
				tok += strlen("rgba8888");
			}
			else if (strncmp(tok, "rgba5551", strlen("rgba5551")) == 0)
			{
				the_configAttr.red_size   = 5;
				the_configAttr.green_size = 5;
				the_configAttr.blue_size  = 5;
				the_configAttr.alpha_size = 1;
				tok += strlen("rgba5551");
			}
			else if (strncmp(tok, "rgba4444", strlen("rgba4444")) == 0)
			{
				the_configAttr.red_size   = 4;
				the_configAttr.green_size = 4;
				the_configAttr.blue_size  = 4;
				the_configAttr.alpha_size = 4;
				tok += strlen("rgba4444");
			}
			else if (strncmp(tok, "rgb565", strlen("rgb565")) == 0)
			{
				the_configAttr.red_size   = 5;
				the_configAttr.green_size = 6;
				the_configAttr.blue_size  = 5;
				the_configAttr.alpha_size = 0;
				tok += strlen("rgb565");
			}
			else if (isdigit(*tok))
			{
				val = atoi(tok);
				while (isdigit(*(++tok)));
				if (*tok == 'x')
				{
					the_configAttr.samples = val;
					tok++;
				}
				else
				{
					the_configAttr.config_id = val;
				}
			}
			else
			{
				fprintf(stderr, "invalid configuration specifier: ");
				while (*tok != ' ' && *tok != ',' && *tok != '\0')
					fputc(*tok++, stderr);

				fputc('\n', stderr);
			}

			while (*tok == ' ' || *tok == ',')
				tok++;
		}
	}

	rc = eglGetConfigs(eglDisplay, NULL, 0, &egl_num_configs);
	if (rc != EGL_TRUE)
	{
		fprintf(stderr, "eglGetConfigs");
		return config;
	}

	if (egl_num_configs == 0)
	{
		fprintf(stderr, "eglGetConfigs: could not find a configuration\n");
		return config;
	}

	configurations = (EGLConfig *)malloc(egl_num_configs * sizeof(*configurations));
	if (configurations == NULL)
	{
		fprintf(stderr, "could not allocate memory for %d EGL configs\n", egl_num_configs);
		return config;
	}

	rc = eglGetConfigs(eglDisplay, configurations, egl_num_configs, &egl_num_configs);
	if (rc != EGL_TRUE)
	{
		fprintf(stderr, "eglGetConfigs");
		free(configurations);
		return config;
	}

	for (i = 0; i < egl_num_configs; i++)
	{
		if (the_configAttr.config_id != EGL_DONT_CARE)
		{
			eglGetConfigAttrib(eglDisplay, configurations[i], EGL_CONFIG_ID, &val);
			if (val == the_configAttr.config_id)
			{
				config = configurations[i];
				break;
			}
			else
			{
				continue;
			}
		}

		eglGetConfigAttrib(eglDisplay, configurations[i], EGL_SURFACE_TYPE, &val);
		if ((val & the_configAttr.surface_type) != the_configAttr.surface_type)
			continue;

		eglGetConfigAttrib(eglDisplay, configurations[i], EGL_RENDERABLE_TYPE, &val);
		if (!(val & EGL_OPENGL_ES_BIT))
			continue;

		eglGetConfigAttrib(eglDisplay, configurations[i], EGL_DEPTH_SIZE, &val);
		if (val == 0)
			continue;

		if (the_configAttr.red_size != EGL_DONT_CARE)
		{
			eglGetConfigAttrib(eglDisplay, configurations[i], EGL_RED_SIZE, &val);
			if (val != the_configAttr.red_size)
				continue;
		}

		if (the_configAttr.green_size != EGL_DONT_CARE)
		{
			eglGetConfigAttrib(eglDisplay, configurations[i], EGL_GREEN_SIZE, &val);
			if (val != the_configAttr.green_size)
				continue;
		}

		if (the_configAttr.blue_size != EGL_DONT_CARE)
		{
			eglGetConfigAttrib(eglDisplay, configurations[i], EGL_BLUE_SIZE, &val);
			if (val != the_configAttr.blue_size)
				continue;
		}

		if (the_configAttr.alpha_size != EGL_DONT_CARE)
		{
			eglGetConfigAttrib(eglDisplay, configurations[i], EGL_ALPHA_SIZE, &val);
			if (val != the_configAttr.alpha_size)
				continue;
		}

		if (the_configAttr.samples != EGL_DONT_CARE)
		{
			eglGetConfigAttrib(eglDisplay, configurations[i], EGL_SAMPLES, &val);
			if (val != the_configAttr.samples)
				continue;
		}

		config = configurations[i];
		break;
	}

	free(configurations);

	if (config == (EGLConfig)0)
	{
		fprintf(stderr, "eglChooseConfig: could not find a matching configuration\n");
	}

	return config;
}

int CCEGLView::chooseFormat(const EGLDisplay &eglDisplay, const EGLConfig &config)
{
	EGLint buffer_bit_depth, alpha_bit_depth;

	eglGetConfigAttrib(eglDisplay, config, EGL_BUFFER_SIZE, &buffer_bit_depth);
	eglGetConfigAttrib(eglDisplay, config, EGL_ALPHA_SIZE,  &alpha_bit_depth);

	switch (buffer_bit_depth)
	{
		case 32: return SCREEN_FORMAT_RGBA8888;
		case 24: return SCREEN_FORMAT_RGB888;
		case 16:
		{
			switch (alpha_bit_depth)
			{
				case 4:  return SCREEN_FORMAT_RGBA4444;
				case 1:  return SCREEN_FORMAT_RGBA5551;
				default: return SCREEN_FORMAT_RGB565;
			}
		}

		default:  return 0;
	}
}

void CCEGLView::printEGLInfo(const EGLConfig &config) const
{
	int i;

	fprintf(stderr,"EGL_VENDOR = %s\n", eglQueryString(m_eglDisplay, EGL_VENDOR));
	fprintf(stderr,"EGL_VERSION = %s\n", eglQueryString(m_eglDisplay, EGL_VERSION));
	fprintf(stderr,"EGL_CLIENT_APIS = %s\n", eglQueryString(m_eglDisplay, EGL_CLIENT_APIS));
	fprintf(stderr,"EGL_EXTENSIONS = %s\n\n", eglQueryString(m_eglDisplay, EGL_EXTENSIONS));

	i = -1;
	eglGetConfigAttrib(m_eglDisplay, config, EGL_CONFIG_ID, &i);
	fprintf(stderr,"EGL_CONFIG_ID = %d\n", i);

	i = 0;
	eglGetConfigAttrib(m_eglDisplay, config, EGL_RED_SIZE, &i);
	fprintf(stderr,"EGL_RED_SIZE = %d\n", i);

	i = 0;
	eglGetConfigAttrib(m_eglDisplay, config, EGL_GREEN_SIZE, &i);
	fprintf(stderr,"EGL_GREEN_SIZE = %d\n", i);

	i = 0;
	eglGetConfigAttrib(m_eglDisplay, config, EGL_BLUE_SIZE, &i);
	fprintf(stderr,"EGL_BLUE_SIZE = %d\n", i);

	i = 0;
	eglGetConfigAttrib(m_eglDisplay, config, EGL_ALPHA_SIZE, &i);
	fprintf(stderr,"EGL_ALPHA_SIZE = %d\n", i);

	i = 0;
	eglGetConfigAttrib(m_eglDisplay, config, EGL_DEPTH_SIZE, &i);
	fprintf(stderr,"EGL_DEPTH_SIZE = %d\n", i);

	i = 0;
	eglGetConfigAttrib(m_eglDisplay, config, EGL_LEVEL, &i);
	fprintf(stderr,"EGL_LEVEL = %d\n", i);

	i = 0;
	eglGetConfigAttrib(m_eglDisplay, config, EGL_NATIVE_RENDERABLE, &i);
	fprintf(stderr,"EGL_NATIVE_RENDERABLE = %s\n", i ? "EGL_TRUE" : "EGL_FALSE");

	i = 0;
	eglGetConfigAttrib(m_eglDisplay, config, EGL_NATIVE_VISUAL_TYPE, &i);
	fprintf(stderr,"EGL_NATIVE_VISUAL_TYPE = %d\n", i);

	i = 0;
	eglGetConfigAttrib(m_eglDisplay, config, EGL_RENDERABLE_TYPE, &i);
	fprintf(stderr,"EGL_RENDERABLE_TYPE = 0x%04x\n", i);

	i = 0;
	eglGetConfigAttrib(m_eglDisplay, config, EGL_SURFACE_TYPE, &i);
	fprintf(stderr,"EGL_SURFACE_TYPE = 0x%04x\n", i);

	i = 0;
	eglGetConfigAttrib(m_eglDisplay, config, EGL_TRANSPARENT_TYPE, &i);
	if (i == EGL_TRANSPARENT_RGB)
	{
		fprintf(stderr,"EGL_TRANSPARENT_TYPE = EGL_TRANSPARENT_RGB\n");

		i = 0;
		eglGetConfigAttrib(m_eglDisplay, config, EGL_TRANSPARENT_RED_VALUE, &i);
		fprintf(stderr,"EGL_TRANSPARENT_RED = 0x%02x\n", i);

		i = 0;
		eglGetConfigAttrib(m_eglDisplay, config, EGL_TRANSPARENT_GREEN_VALUE, &i);
		fprintf(stderr,"EGL_TRANSPARENT_GREEN = 0x%02x\n", i);

		i = 0;
		eglGetConfigAttrib(m_eglDisplay, config, EGL_TRANSPARENT_BLUE_VALUE, &i);
		fprintf(stderr,"EGL_TRANSPARENT_BLUE = 0x%02x\n\n", i);
	}
	else
	{
		fprintf(stderr,"EGL_TRANSPARENT_TYPE = EGL_NONE\n\n");
	}
}

static void printEglError( GLuint errorCode )
{
    switch( errorCode )
    {
		case EGL_SUCCESS:
			fprintf( stderr, "EGL_SUCCESS");
			break;
		case EGL_NOT_INITIALIZED:
			fprintf( stderr, ">>EGL_NOT_INITIALIZED");
			break;
		case EGL_BAD_ACCESS:
			fprintf( stderr, ">>EGL_BAD_ACCESS");
			break;
		case EGL_BAD_ALLOC:
			fprintf( stderr, ">>EGL_BAD_ALLOC");
			break;
		case EGL_BAD_ATTRIBUTE:
			fprintf( stderr, ">>EGL_BAD_ATTRIBUTE");
			break;
		case EGL_BAD_CONTEXT:
			fprintf( stderr, ">>EGL_BAD_CONTEXT");
			break;
		case EGL_BAD_CONFIG:
			fprintf( stderr, ">>EGL_BAD_CONFIG");
			break;
		case EGL_BAD_CURRENT_SURFACE:
			fprintf( stderr, ">>EGL_BAD_CURRENT_SURFACE");
			break;
		case EGL_BAD_DISPLAY:
			fprintf( stderr, ">>EGL_BAD_DISPLAY");
			break;
		case EGL_BAD_SURFACE:
			fprintf( stderr, ">>EGL_BAD_SURFACE");
			break;
		case EGL_BAD_MATCH:
			fprintf( stderr, ">>EGL_BAD_MATCH");
			break;
		case EGL_BAD_PARAMETER:
			fprintf( stderr, ">>EGL_BAD_PARAMETER");
			break;
		case EGL_BAD_NATIVE_PIXMAP:
			fprintf( stderr, ">>EGL_BAD_NATIVE_PIXMAP");
			break;
		case EGL_BAD_NATIVE_WINDOW:
			fprintf( stderr, ">>EGL_BAD_NATIVE_WIN i=i+2DOW");
			break;
		case EGL_CONTEXT_LOST:
			fprintf( stderr, ">>EGL_CONTEXT_LOST");
			break;
		default:
			fprintf( stderr, ">>Unknown error");
			break;
    }
}

bool CCEGLView::initDriver()
{
    int         err;
    int         egl_ret;
    EGLint      majorVersion;
    EGLint      minorVersion;

    // Get EGL display
    m_eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    err = eglGetError();
    if (m_eglDisplay == EGL_NO_DISPLAY || err != EGL_SUCCESS)
    {
        printEglError( err );
        return false;
    }

    // Initialize EGL
    egl_ret = eglInitialize(m_eglDisplay, &majorVersion, &minorVersion);
    err = eglGetError();
    if ( egl_ret != EGL_TRUE || err != EGL_SUCCESS )
    {
        printEglError( err );
        return false;
    }

    return true;
}

bool CCEGLView::createNativeWindow(const EGLConfig &config)
{
    int 	usage = SCREEN_USAGE_OPENGL_ES1;
	int 	transp = SCREEN_TRANSPARENCY_NONE;
	int 	pos[2] = { 0, 0 };
	int 	nbuffers = 2;
	EGLint 	interval = 1;
	int 	format;
    EGLint  err;

    err = screen_create_context(&m_screenContext, 0);
	if (err)
	{
		fprintf(stderr, "screen_create_context");
		return false;
	}

    err = screen_create_window(&m_screenWindow, m_screenContext);
	if (err)
	{
		fprintf(stderr, "screen_create_window");
		return false;
	}

	format = chooseFormat(m_eglDisplay, config);
	err = screen_set_window_property_iv(m_screenWindow, SCREEN_PROPERTY_FORMAT, &format);
	if (err)
	{
		fprintf(stderr, "screen_set_window_property_iv(SCREEN_PROPERTY_FORMAT)");
		return false;
	}

	err = screen_set_window_property_iv(m_screenWindow, SCREEN_PROPERTY_USAGE, &usage);
	if (err)
	{
		fprintf(stderr, "screen_set_window_property_iv(SCREEN_PROPERTY_USAGE)");
		return false;
	}

	if (pos[0] != 0 || pos[1] != 0)
	{
		err = screen_set_window_property_iv(m_screenWindow, SCREEN_PROPERTY_POSITION, pos);
		if (err)
		{
			fprintf(stderr, "screen_set_window_property_iv(SCREEN_PROPERTY_POSITION)");
			return false;
		}
	}

	err = screen_set_window_property_iv(m_screenWindow, SCREEN_PROPERTY_TRANSPARENCY, &transp);
	if (err)
	{
		fprintf(stderr, "screen_set_window_property_iv(SCREEN_PROPERTY_TRANSPARENCY)");
		return false;
	}

	err = screen_set_window_property_iv(m_screenWindow, SCREEN_PROPERTY_SWAP_INTERVAL, &interval);
	if (err)
	{
		fprintf(stderr, "screen_set_window_property_iv(SCREEN_PROPERTY_SWAP_INTERVAL)");
		return false;
	}

	screen_display_t screen_disp;
    int rc = screen_get_window_property_pv(m_screenWindow, SCREEN_PROPERTY_DISPLAY, (void **)&screen_disp);
    if (rc)
    {
    	fprintf(stderr, "screen_get_window_property_pv(SCREEN_PROPERTY_DISPLAY)");
        return false;
    }

	screen_display_mode_t screen_mode;
	rc = screen_get_display_property_pv(screen_disp, SCREEN_PROPERTY_MODE, (void**)&screen_mode);
	if (rc)
	{
		fprintf(stderr, "screen_get_display_property_pv(SCREEN_PROPERTY_MODE)");
	    return false;
	}

    int size[2];
	rc = screen_get_window_property_iv(m_screenWindow, SCREEN_PROPERTY_BUFFER_SIZE, size);
	if (rc)
	{
		fprintf(stderr, "screen_get_window_property_iv(SCREEN_PROPERTY_BUFFER_SIZE)");
		return false;
	}

	int angle = atoi(getenv("ORIENTATION"));
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
			((screen_mode.width < screen_mode.height && size[0] < size[1])))
		{
			buffer_size[1] = size[0];
			buffer_size[0] = size[1];
		}
	}
	else
	{
		fprintf(stderr, "Navigator returned an unexpected orientation angle of %d.\n", angle);
		return false;
	}

	rc = screen_set_window_property_iv(m_screenWindow, SCREEN_PROPERTY_BUFFER_SIZE, buffer_size);
	if (rc)
	{
		fprintf(stderr, "screen_set_window_property_iv(SCREEN_PROPERTY_BUFFER_SIZE)");
		return false;
	}

	rc = screen_set_window_property_iv(m_screenWindow, SCREEN_PROPERTY_ROTATION, &angle);
	if (rc)
	{
		fprintf(stderr, "screen_set_window_property_iv(SCREEN_PROPERTY_ROTATION)");
		return false;
	}

	err = screen_create_window_buffers(m_screenWindow, nbuffers);
	if (err)
	{
		fprintf(stderr, "screen_create_window_buffers");
		return false;
	}

	return true;
}

#define N_BPS_EVENTS 1

bool CCEGLView::initGL()
{
	EGLConfig 			config;
    EGLint    			err;

    initDriver();

    config = chooseConfig(m_eglDisplay, "rgb565");
    if (config == (EGLConfig)0)
    {
        fprintf(stderr, "Failed to find config!" );
        return false;
	}

    // Create EGL rendering context
    m_eglContext = eglCreateContext( m_eglDisplay, config, EGL_NO_CONTEXT, NULL );
    err = eglGetError( );
    if ( m_eglContext == EGL_NO_CONTEXT )
    {
        fprintf(stderr, "Can't create gles2 context!" );
        printEglError( err );
		return false;
    }

//    printEGLInfo(config);

    if (!createNativeWindow(config))
    {
    	fprintf(stderr, "Unable to create a native window\n");
    	return false;
    }

    // set up the screen events
	err = screen_create_event(&m_screenEvent);
	if (err)
	{
		fprintf(stderr, "screen_create_event");
		return false;
	}

#ifdef BPS_EVENTS
	// Request screen events
	screen_request_events(m_screenContext);
#endif

	m_eglSurface = eglCreateWindowSurface(m_eglDisplay, config, m_screenWindow, NULL);
	if (m_eglSurface == EGL_NO_SURFACE)
	{
        fprintf(stderr, "Demo Thread Init: can't create surface!" );
        printEglError( err );
        return false;
	}

	err = eglMakeCurrent(m_eglDisplay, m_eglSurface, m_eglSurface, m_eglContext);
	if (err != EGL_TRUE)
	{
        fprintf(stderr, "Demo Thread Init: can't make current!" );
		return false;
	}

    EGLint width, height;

    if ((m_eglDisplay == EGL_NO_DISPLAY) || (m_eglSurface == EGL_NO_SURFACE) )
    	return EXIT_FAILURE;

	eglQuerySurface(m_eglDisplay, m_eglSurface, EGL_WIDTH, &width);
    eglQuerySurface(m_eglDisplay, m_eglSurface, EGL_HEIGHT, &height);

	m_sSizeInPixel.width = width;
	m_sSizeInPixel.height = height;

    return true;
}

CCSize CCEGLView::getSize()
{
	if (m_bNotHVGA)
	{
		CCSize size(m_sSizeInPoint.width, m_sSizeInPoint.height);
		return size;
	}
	else
	{
		CCSize size(m_sSizeInPixel.width, m_sSizeInPixel.height);
		return size;
	}
}

bool CCEGLView::isOpenGLReady()
{
	return (m_isGLInitialized && m_sSizeInPixel.width != 0 && m_sSizeInPixel.height != 0);
}

void CCEGLView::release()
{
	if (!m_eglContext || !m_eglDisplay)
		return;
#ifdef BPS_EVENTS
	screen_stop_events(m_screenContext);
#endif
	bps_shutdown();

	screen_destroy_event(m_screenEvent);

	eglMakeCurrent(m_eglDisplay, NULL, NULL, NULL);
	eglDestroySurface(m_eglDisplay, m_eglSurface);
	screen_destroy_window(m_screenWindow);
	screen_destroy_context(m_screenContext);
	eglDestroyContext(m_eglDisplay, m_eglContext);
	eglTerminate(m_eglDisplay);
	eglReleaseThread();

	m_eglDisplay = NULL;
	m_eglContext = NULL;
	m_eglSurface = NULL;

	m_isGLInitialized = false;

	exit(0);
}

void CCEGLView::setTouchDelegate(EGLTouchDelegate * pDelegate)
{
	m_pDelegate = pDelegate;
}

EGLTouchDelegate* CCEGLView::getDelegate(void)
{
	return m_pDelegate;
}

bool CCEGLView::HandleEvents()
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

#ifdef BPS_EVENTS
		// break if no more events
		if (event == NULL)
			break;
#else
		if (event != NULL)
		{
#endif

		domain = bps_event_get_domain(event);

		if (domain == navigator_get_domain())
		{
			switch (bps_event_get_code(event))
			{
				case NAVIGATOR_SWIPE_DOWN:
					CCKeypadDispatcher::sharedDispatcher()->dispatchKeypadMSG(kTypeMenuClicked);
					break;

				case NAVIGATOR_EXIT:
					// exit the application
				//	release();
					break;

				case NAVIGATOR_WINDOW_INACTIVE:
					if(m_isWindowActive)
					{
						CCApplication::sharedApplication().applicationDidEnterBackground();
						m_isWindowActive = false;
					}
					break;

				case NAVIGATOR_WINDOW_ACTIVE:
					if(!m_isWindowActive)
					{
						CCApplication::sharedApplication().applicationWillEnterForeground();
						m_isWindowActive = true;
					}
					break;

				case NAVIGATOR_WINDOW_STATE:
				{
					switch(navigator_event_get_window_state(event))
					{
						case NAVIGATOR_WINDOW_FULLSCREEN:
							if(!m_isWindowActive)
							{
								CCApplication::sharedApplication().applicationWillEnterForeground();
								m_isWindowActive = true;
							}
							break;
						case NAVIGATOR_WINDOW_THUMBNAIL:
							if(m_isWindowActive)
							{
								CCApplication::sharedApplication().applicationDidEnterBackground();
								m_isWindowActive = false;
							}
							break;
					}
					break;
				}

				default:
					break;
			}
		}
		}
#ifndef BPS_EVENTS
		// for now handle screen events separately from BPS events
		if (screen_get_event(m_screenContext, m_screenEvent, 0) < 0)
		{
			// we have an error condition in the screen event
			break;
		}
		else
		{
#else
		else if (domain == screen_get_domain())
		{
			m_screenEvent = screen_event_get_event(event);
#endif
			rc = screen_get_event_property_iv(m_screenEvent, SCREEN_PROPERTY_TYPE, &val);
			if (rc || val == SCREEN_EVENT_NONE)
				break;

			switch (val)
			{
				case SCREEN_EVENT_CLOSE:
					fprintf(stderr, "SCREEN CLOSE EVENT!\n");
					break;

				case SCREEN_EVENT_MTOUCH_RELEASE:
					screen_get_mtouch_event(m_screenEvent, &mtouch_event, 0);
					touch_id = mtouch_event.contact_id;

					if (m_pDelegate && touch_id < MAX_TOUCHES)
					{
						CCTouch* touch = s_pTouches[touch_id];
						if (touch)
						{
							CCSet set;
							touch->SetTouchInfo(0, ((float)(mtouch_event.x) - m_rcViewPort.origin.x) / m_fScreenScaleFactor,
												   ((float)(mtouch_event.y) - m_rcViewPort.origin.y) / m_fScreenScaleFactor);
							set.addObject(touch);
							m_pDelegate->touchesEnded(&set, NULL);

							touch->release();
							for (int i = touch_id; i < MAX_TOUCHES; i++)
							{
								if (i != (MAX_TOUCHES - 1))
								{
									s_pTouches[i] = s_pTouches[i + 1];
								}
								else
								{
									s_pTouches[i] = NULL;
								}
							}
						}
					}

					break;

				case SCREEN_EVENT_MTOUCH_TOUCH:
					screen_get_mtouch_event(m_screenEvent, &mtouch_event, 0);
					touch_id = mtouch_event.contact_id;

					if (m_pDelegate && touch_id < MAX_TOUCHES)
					{
						CCTouch* touch = s_pTouches[touch_id];
						if (!touch)
							touch = new CCTouch;

						touch->SetTouchInfo(0, ((float)(mtouch_event.x) - m_rcViewPort.origin.x) / m_fScreenScaleFactor,
											   ((float)(mtouch_event.y) - m_rcViewPort.origin.y) / m_fScreenScaleFactor);
						s_pTouches[touch_id] = touch;

						CCSet set;
						set.addObject(touch);
						m_pDelegate->touchesBegan(&set, NULL);
					}

					break;

				case SCREEN_EVENT_MTOUCH_MOVE:
					screen_get_mtouch_event(m_screenEvent, &mtouch_event, 0);
					touch_id = mtouch_event.contact_id;

					if (m_pDelegate && touch_id < MAX_TOUCHES)
					{
						CCTouch* touch = s_pTouches[touch_id];
						if (touch)
						{
							CCSet set;
							touch->SetTouchInfo(0, ((float)(mtouch_event.x) - m_rcViewPort.origin.x) / m_fScreenScaleFactor,
												   ((float)(mtouch_event.y) - m_rcViewPort.origin.y) / m_fScreenScaleFactor);
							set.addObject(touch);
							m_pDelegate->touchesMoved(&set, NULL);
						}
					}

					break;

				case SCREEN_EVENT_POINTER:
					{
						int buttons;
						int pair[2];
						static bool mouse_pressed = false;

						// this is a mouse move event, it is applicable to a device with a usb mouse or simulator
						screen_get_event_property_iv(m_screenEvent, SCREEN_PROPERTY_BUTTONS, &buttons);
						screen_get_event_property_iv(m_screenEvent, SCREEN_PROPERTY_SOURCE_POSITION, pair);

						if (buttons & SCREEN_LEFT_MOUSE_BUTTON)
						{
							if (mouse_pressed)
							{
								// Left mouse button was released
								if (m_pDelegate && touch_id < MAX_TOUCHES)
								{
									CCTouch* touch = s_pTouches[touch_id];
									if (touch)
									{
										CCSet set;
										touch->SetTouchInfo(0, ((float)(pair[0]) - m_rcViewPort.origin.x) / m_fScreenScaleFactor,
															   ((float)(pair[1]) - m_rcViewPort.origin.y) / m_fScreenScaleFactor);
										set.addObject(touch);
										m_pDelegate->touchesMoved(&set, NULL);
									}
								}
							}
							else
							{
								// Left mouse button is pressed
								mouse_pressed = true;
								if (m_pDelegate && touch_id < MAX_TOUCHES)
								{
									CCTouch* touch = s_pTouches[touch_id];
									if (!touch)
										touch = new CCTouch;

									touch->SetTouchInfo(0, ((float)(pair[0]) - m_rcViewPort.origin.x) / m_fScreenScaleFactor,
														   ((float)(pair[1]) - m_rcViewPort.origin.y) / m_fScreenScaleFactor);
									s_pTouches[touch_id] = touch;

									CCSet set;
									set.addObject(touch);
									m_pDelegate->touchesBegan(&set, NULL);
								}
							}
						}
						else
						{
							if (mouse_pressed)
							{
								if (m_pDelegate && touch_id < MAX_TOUCHES)
								{
									mouse_pressed = false;

									CCTouch* touch = s_pTouches[touch_id];
									if (touch)
									{
										CCSet set;
										touch->SetTouchInfo(0, ((float)(pair[0]) - m_rcViewPort.origin.x) / m_fScreenScaleFactor,
															   ((float)(pair[1]) - m_rcViewPort.origin.y) / m_fScreenScaleFactor);
										set.addObject(touch);
										m_pDelegate->touchesEnded(&set, NULL);

										touch->release();
										for (int i = touch_id; i < MAX_TOUCHES; i++)
										{
											if (i != (MAX_TOUCHES - 1))
											{
												s_pTouches[i] = s_pTouches[i + 1];
											}
											else
											{
												s_pTouches[i] = NULL;
											}
										}
									}
								}
							}
						}
					}
					break;

				case SCREEN_EVENT_KEYBOARD:
					screen_get_event_property_iv(m_screenEvent, SCREEN_PROPERTY_KEY_FLAGS, &val);
					if (val & KEY_DOWN)
					{
						screen_get_event_property_iv(m_screenEvent, SCREEN_PROPERTY_KEY_SYM, &val);

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
	}

	return true;
}

void CCEGLView::swapBuffers()
{
	eglSwapBuffers(m_eglDisplay, m_eglSurface);
}

bool CCEGLView::canSetContentScaleFactor()
{
    // can scale content?
    return false;
}

void CCEGLView::setContentScaleFactor(float contentScaleFactor)
{
	m_fScreenScaleFactor = contentScaleFactor;
} 

void CCEGLView::setViewPortInPoints(float x, float y, float w, float h)
{
    if (m_bNotHVGA)
    {
        float factor = m_fScreenScaleFactor / CC_CONTENT_SCALE_FACTOR();
        glViewport( (GLint)(x * factor) + m_rcViewPort.origin.x,
					(GLint)(y * factor) + m_rcViewPort.origin.y,
					(GLint)(w * factor),
					(GLint)(h * factor));
    }
    else
    {
        glViewport( (GLint)x,
					(GLint)y,
					(GLint)w,
					(GLint)h);
    }		
}

void CCEGLView::setScissorInPoints(float x, float y, float w, float h)
{
    if (m_bNotHVGA)
    {
        float factor = m_fScreenScaleFactor / CC_CONTENT_SCALE_FACTOR();
        glScissor(  (GLint)(x * factor) + m_rcViewPort.origin.x,
					(GLint)(y * factor) + m_rcViewPort.origin.y,
					(GLint)(w * factor),
					(GLint)(h * factor));
    }
    else
    {
        glScissor(  (GLint)x,
					(GLint)y,
					(GLint)w,
					(GLint)h);
    }
}

CCEGLView& CCEGLView::sharedOpenGLView()
{
	CCAssert(s_pInstance != NULL, "CCEGLView wasn't constructed yet");
	return *s_pInstance;
}

float CCEGLView::getScreenScaleFactor()
{
    return m_fScreenScaleFactor;
}

CCRect CCEGLView::getViewPort()
{
    if (m_bNotHVGA)
    {
        return m_rcViewPort;
    }
    else
    {
        CCRect rect(0, 0, 0, 0);
        return rect;
    }
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

void CCEGLView::showKeyboard()
{
	int height;

	virtualkeyboard_get_height(&height);

	float factor = m_fScreenScaleFactor / CC_CONTENT_SCALE_FACTOR();
	height = (float)height / factor;

	CCRect rect_begin(0, 0 - height, m_sSizeInPixel.width / factor, height);
	CCRect rect_end(0, 0, m_sSizeInPixel.width / factor, height);

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

}       // end of namespace cocos2d
