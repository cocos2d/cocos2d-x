/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#ifndef __CCCONFIGURATION_H__
#define __CCCONFIGURATION_H__

#include "include/Cocos2dTypes.h"
#include "include/NSObject.h"
#include <GLES/gl.h>
#include <string>

/**
 CCConfiguration contains some openGL variables
 @since v0.99.0
 */
class CCConfiguration : public NSObject
{
protected:
	GLint	m_nMaxTextureSize;
	GLint	m_nMaxModelviewStackDepth;
	BOOL	m_bSupportsPVRTC;
	BOOL	m_bSupportsNPOT;
	BOOL	m_bSupportsBGRA8888;
	BOOL	m_bSupportsDiscardFramebuffer;

public:
	CCConfiguration(void);
	
	// OpenGL Max texture size.
	INT32 getMaxTextureSize(void);

	// OpenGL Max Modelview Stack Depth
	INT32 getMaxModelviewStackDepth(void);

	/** Whether or not the GPU supports NPOT (Non Power Of Two) textures.
	 NPOT textures have the following limitations:
	 - They can't have mipmaps
	 - They only accept GL_CLAMP_TO_EDGE in GL_TEXTURE_WRAP_{S,T}
	 
	 @since v0.99.2
	 */
	BOOL isSupportsNPOT(void);

	// Whether or not PVR Texture Compressed is supported
	BOOL isSupportsPVRTC(void);

	/** Whether or not BGRA8888 textures are supported.
	 @since v0.99.2
	 */
	BOOL isSupportsBGRA8888(void);

	/** Whether or not glDiscardFramebufferEXT is supported
	 @since v0.99.2
	 */
	BOOL isSupportsDiscardFramebuffer(void);

	// returns whether or not an OpenGL is supported
	BOOL checkForGLExtension(const std::string &searchName);

public:
	// returns a shared instance of the CCConfiguration
	static CCConfiguration* sharedConfiguration(void);
};

#endif // __CCCONFIGURATION_H__
