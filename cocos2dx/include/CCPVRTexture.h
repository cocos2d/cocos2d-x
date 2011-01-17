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

#if 0 // PVR TEXTURE CANNOT CROSS PLATFORM

#ifndef __CCPVRTEXTURE_H__
#define __CCPVRTEXTURE_H__

#include <string>
#include <GLES/gl.h>
#include <GLES/glext.h>

#include "CCXCocos2dDefine.h"
#include "NSObject.h"
#include "NSMutableArray.h"

namespace   cocos2d {
class NSData;

class CCPVRTexture : public NSObject
{
protected:
	NSMutableArray<NSData*> * m_pImageData;

public:

	CCPVRTexture();
	virtual ~CCPVRTexture();

	CCPVRTexture * initWithContentsOfFile(const char* path);
// @todo	CCPVRTexture * initWithContentsOfURL(NSURL *url);
	static CCPVRTexture * pvrTextureWithContentsOfFile(const char* path);
// @todo	static CCPVRTexture * pvrTextureWithContentsOfURL(NSURL *url);

	CCX_PROPERTY_READONLY(GLuint, m_uName, Name)
	CCX_PROPERTY_READONLY(unsigned int, m_uWidth, Width)
	CCX_PROPERTY_READONLY(unsigned int, m_uHeight, Height)
	CCX_PROPERTY_READONLY(GLenum, m_uInternalFormat, InternalFormat)
	CCX_PROPERTY_READONLY(bool, m_bHasAlpha, HasAlpha)

	// cocos2d integration
	CCX_PROPERTY(bool, m_bRetainName, RetainName);

private:
	bool unpackPVRData(NSData *data);
	bool createGLTexture();
};
}//namespace   cocos2d 


#endif //__CCPVRTEXTURE_H__

#endif
