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
#include "CCXGLExtFunc.h"

#include <GLES/egl.h>

PFNGLGENFRAMEBUFFERSOESPROC  glGenFramebuffersOES;
PFNGLDELETEFRAMEBUFFERSOESPROC glDeleteFramebuffersOES;
PFNGLFRAMEBUFFERTEXTURE2DOESPROC glFramebufferTexture2DOES;
PFNGLCHECKFRAMEBUFFERSTATUSOESPROC glCheckFramebufferStatusOES;
PFNGLBINDFRAMEBUFFEROESPROC glBindFramebufferOES;
PFNGLGENERATEMIPMAPOESPROC glGenerateMipmapOES;

void loadExtension()
{
	const GLubyte *pszGLExtensions = glGetString(GL_EXTENSIONS);

    /* GL_OES_Framebuffer_object*/
	if (strstr((char *)pszGLExtensions, "GL_OES_framebuffer_object"))
	{
		glGenFramebuffersOES = (PFNGLGENFRAMEBUFFERSOESPROC)eglGetProcAddress("glGenFramebuffersOES");
		glDeleteFramebuffersOES = (PFNGLDELETEFRAMEBUFFERSOESPROC)eglGetProcAddress("glDeleteFramebuffersOES");
		glFramebufferTexture2DOES = (PFNGLFRAMEBUFFERTEXTURE2DOESPROC)eglGetProcAddress("glFramebufferTexture2DOES");
		glCheckFramebufferStatusOES = (PFNGLCHECKFRAMEBUFFERSTATUSOESPROC)eglGetProcAddress("glCheckFramebufferStatusOES");
		glBindFramebufferOES = (PFNGLBINDFRAMEBUFFEROESPROC)eglGetProcAddress("glBindFramebufferOES");
		glGenerateMipmapOES = (PFNGLGENERATEMIPMAPOESPROC)eglGetProcAddress("glGenerateMipmapOES");
	}

	/* GL_OES_draw_texture */
	//if (strstr((char *)pszGLExtensions, "GL_OES_draw_texture"))
	//{
	//	glDrawTexiOES = (PFNGLDRAWTEXIOES)eglGetProcAddress("glDrawTexiOES");
	//	glDrawTexivOES = (PFNGLDRAWTEXIVOES)eglGetProcAddress("glDrawTexivOES");
	//	glDrawTexsOES = (PFNGLDRAWTEXSOES)eglGetProcAddress("glDrawTexsOES");
	//	glDrawTexsvOES = (PFNGLDRAWTEXSVOES)eglGetProcAddress("glDrawTexsvOES");
	//	glDrawTexxOES = (PFNGLDRAWTEXXOES)eglGetProcAddress("glDrawTexxOES");
	//	glDrawTexxvOES = (PFNGLDRAWTEXXVOES)eglGetProcAddress("glDrawTexxvOES");
	//	glDrawTexfOES = (PFNGLDRAWTEXFOES)eglGetProcAddress("glDrawTexfOES");
	//	glDrawTexfvOES = (PFNGLDRAWTEXFVOES)eglGetProcAddress("glDrawTexfvOES");
	//}
}
