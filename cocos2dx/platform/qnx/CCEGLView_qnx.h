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

#ifndef __CC_EGLVIEW_QNX_H__
#define __CC_EGLVIEW_QNX_H__

#include "CCGeometry.h"
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <EGL/egl.h>
#include <screen/screen.h>

namespace   cocos2d {
class CCSet;
class CCTouch;
class EGLTouchDelegate;

class CC_DLL CCEGLView
{
public:
    CCEGLView();
    virtual ~CCEGLView();

    CCSize  getSize();
    bool    isOpenGLReady();
	/**
	 * the width and height is the real size of phone
	 */
    void    setFrameWidthAndHeight(int width, int height);
	/**
	 * create a drawing rect, 
	 * the width and heiht is the resource size match best
	 */
	bool    Create(int width, int height);
    EGLTouchDelegate* getDelegate(void);
    
    // keep compatible
    void    release();
    void    setTouchDelegate(EGLTouchDelegate * pDelegate);
    void    swapBuffers();
    bool    canSetContentScaleFactor();
    void    setContentScaleFactor(float contentScaleFactor); 
	void    setViewPortInPoints(float x, float y, float w, float h);
    void    setScissorInPoints(float x, float y, float w, float h);
	CCRect  getViewPort();
	float   getScreenScaleFactor();
    void    setIMEKeyboardState(bool bOpen);

    bool 	HandleEvents();

	// static function
	/**
	@brief	get the shared main open gl window
	*/
	static CCEGLView& sharedOpenGLView();

	// pointer to OES methods from EGL
	static PFNGLGENERATEMIPMAPOESPROC         glGenerateMipmapOES;
	static PFNGLGENFRAMEBUFFERSOESPROC        glGenFramebuffersOES;
	static PFNGLBINDFRAMEBUFFEROESPROC		  glBindFramebufferOES;
	static PFNGLFRAMEBUFFERTEXTURE2DOESPROC   glFramebufferTexture2DOES;
	static PFNGLDELETEFRAMEBUFFERSOESPROC     glDeleteFramebuffersOES;
	static PFNGLCHECKFRAMEBUFFERSTATUSOESPROC glCheckFramebufferStatusOES;

private:

	bool 		initGL();
	void		initEGLFunctions();
	bool    	isGLExtension(const char *searchName) const;
	bool 		initDriver();
	void 		printEGLInfo(const EGLConfig &config) const;
	EGLConfig   chooseConfig(const EGLDisplay &eglDisplay, const char* str);
	int         chooseFormat(const EGLDisplay &eglDisplay, const EGLConfig &config);
	bool		createNativeWindow(const EGLConfig &config);
	void		showKeyboard();
	void		hideKeyboard();

	CCSize  			m_sSizeInPixel;
	CCSize 			 	m_sSizeInPoint;
	CCRect  			m_rcViewPort;
	bool    			m_bNotHVGA;
	bool				m_isGLInitialized;
	
	EGLTouchDelegate   *m_pDelegate;
	float  				m_fScreenScaleFactor;

	bool 				m_isWindowActive;

	static bool 		m_initializedFunctions;
	static const GLubyte *m_extensions;

	EGLDisplay 		 m_eglDisplay;
	EGLContext 		 m_eglContext;
	EGLSurface 		 m_eglSurface;
    screen_event_t 	 m_screenEvent;
    screen_window_t  m_screenWindow;
    screen_context_t m_screenContext;
};

}   // end of namespace   cocos2d

#endif	// end of __CC_EGLVIEW_QNX_H__
