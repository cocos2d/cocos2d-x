/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2010      Ricardo Quesada

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

#ifndef __CCCONFIGURATION_H__
#define __CCCONFIGURATION_H__

#include "CCObject.h"
#include <string>
#include "CCGL.h"

namespace   cocos2d {

	/** OS version definitions.
	*/
	enum {
		kCCiOSVersion_3_0   = 0x03000000,
		kCCiOSVersion_3_1   = 0x03010000,
		kCCiOSVersion_3_1_1 = 0x03010100,
		kCCiOSVersion_3_1_2 = 0x03010200,
		kCCiOSVersion_3_1_3 = 0x03010300,
		kCCiOSVersion_3_2   = 0x03020000,
		kCCiOSVersion_3_2_1 = 0x03020100,
		kCCiOSVersion_4_0   = 0x04000000,
		kCCiOSVersion_4_0_1 = 0x04000100,
		kCCiOSVersion_4_1   = 0x04010000,
		kCCiOSVersion_4_2   = 0x04020000,
		kCCiOSVersion_4_3   = 0x04030000,
		kCCiOSVersion_4_3_1 = 0x04030100,
		kCCiOSVersion_4_3_2 = 0x04030200,
		kCCiOSVersion_4_3_3 = 0x04030300,
	};

	typedef enum 
	{
		GLES_VER_INVALID,
		GLES_VER_1_0,
		GLES_VER_1_1,
		GLES_VER_2_0,
	} CCGlesVersion;

/**
 @brief CCConfiguration contains some openGL variables
 @since v0.99.0
 */
class CC_DLL CCConfiguration : public CCObject
{
protected:
	GLint			m_nMaxTextureSize;
	GLint			m_nMaxModelviewStackDepth;
	bool			m_bSupportsPVRTC;
	bool			m_bSupportsNPOT;
	bool			m_bSupportsBGRA8888;
	bool			m_bSupportsDiscardFramebuffer;
    bool            m_bInited;
	unsigned int	m_uOSVersion;
	GLint           m_nMaxSamplesAllowed;
    char *          m_pGlExtensions;

private:

    CCConfiguration(void);

public:	

	CCGlesVersion getGlesVersion();
	
	/** OpenGL Max texture size. */
	inline int getMaxTextureSize(void)
	{
		return m_nMaxTextureSize;
	}

	/** OpenGL Max Modelview Stack Depth */
	inline int getMaxModelviewStackDepth(void)
	{
		return m_nMaxModelviewStackDepth;
	}

	/** Whether or not the GPU supports NPOT (Non Power Of Two) textures.
	 NPOT textures have the following limitations:
	 - They can't have mipmaps
	 - They only accept GL_CLAMP_TO_EDGE in GL_TEXTURE_WRAP_{S,T}
	 
	 @since v0.99.2
	 */
	inline bool isSupportsNPOT(void)
	{
		return m_bSupportsNPOT;
	}

	/** Whether or not PVR Texture Compressed is supported */
	inline bool isSupportsPVRTC(void)
	{
		return m_bSupportsPVRTC;
	}

	/** Whether or not BGRA8888 textures are supported.
	 @since v0.99.2
	 */
	inline bool isSupportsBGRA8888(void)
	{
		return m_bSupportsBGRA8888;
	}

	/** Whether or not glDiscardFramebufferEXT is supported
	 @since v0.99.2
	 */
	inline bool isSupportsDiscardFramebuffer(void)
	{
		return m_bSupportsDiscardFramebuffer;
	}

	/** returns the OS version.
	- On iOS devices it returns the firmware version.
	- On Mac returns the OS version

	@since v0.99.5
	*/
	inline unsigned int getOSVersion() { return m_uOSVersion; }

	/** returns whether or not an OpenGL is supported */
	bool checkForGLExtension(const std::string &searchName);

	bool init(void);

public:
	/** returns a shared instance of the CCConfiguration */
	static CCConfiguration *sharedConfiguration(void);
};
}//namespace   cocos2d 

#endif // __CCCONFIGURATION_H__
