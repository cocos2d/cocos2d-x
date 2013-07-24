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

#ifndef __CC_EGLVIEW_BLACKBERRY_H__
#define __CC_EGLVIEW_BLACKBERRY_H__

#include "cocoa/CCGeometry.h"
#include "platform/CCEGLViewProtocol.h"
#include "platform/CCPlatformMacros.h"

//#include <bps/event.h>

NS_CC_BEGIN

class CC_DLL EGLView : public EGLViewProtocol
{
public:
    EGLView();
    virtual ~EGLView();

    bool    isOpenGLReady();
	
    const char* getWindowGroupId() const;

    // keep compatible
    void    end();
    void    swapBuffers();
    void    setIMEKeyboardState(bool bOpen);
    
    // static function
    /**
    @brief    get the shared main open gl window
    */
    static EGLView* getInstance();

    /** @deprecated Use getInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static EGLView* sharedOpenGLView();
    
    bool    handleEvents();

private:
    void        release();

	bool 		initGL();
	void		initEGLFunctions();
	bool    	isGLExtension(const char *searchName) const;
	bool 		initDriver();
	void		showKeyboard();
	void		hideKeyboard();

	static bool 		_initializedFunctions;
	static const GLubyte *_extensions;

	bool			 _isGLInitialized;
	bool 		     _isWindowActive;
	
	EGLDisplay 		 _eglDisplay;
	EGLContext 		 _eglContext;
	EGLSurface 		 _eglSurface;
    char 			 _windowGroupID[16];
};

NS_CC_END

#endif	// end of __CC_EGLVIEW_QNX_H__
