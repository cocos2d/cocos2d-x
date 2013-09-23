/****************************************************************************
Copyright (c) 2011 Jirka Fajfr for cocos2d-x
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

#ifndef __CCPVRTEXTURE_H__
#define __CCPVRTEXTURE_H__

#include "CCStdC.h"
#include "CCGL.h"
#include "cocoa/CCObject.h"
#include "cocoa/CCArray.h"

NS_CC_BEGIN

/**
 * @addtogroup textures
 * @{
 */

/**
 @brief Structure which can tell where mipmap begins and how long is it
*/
struct CCPVRMipmap {
    unsigned char *address;
    unsigned int len;
};

typedef struct _ccPVRTexturePixelFormatInfo {
	GLenum internalFormat;
	GLenum format;
	GLenum type;
	uint32_t bpp;
	bool compressed;
	bool alpha;
	CCTexture2DPixelFormat ccPixelFormat;
} ccPVRTexturePixelFormatInfo;

/**
 @brief Determine how many mipmaps can we have. 
 Its same as define but it respects namespaces
*/
enum {
    CC_PVRMIPMAP_MAX = 16,
};


/** CCTexturePVR
     
 Object that loads PVR images.

 Supported PVR formats:
    - RGBA8888
    - BGRA8888
    - RGBA4444
    - RGBA5551
    - RGB565
    - A8
    - I8
    - AI88
    - PVRTC 4BPP
    - PVRTC 2BPP
     
 Limitations:
    Pre-generated mipmaps, such as PVR textures with mipmap levels embedded in file,
    are only supported if all individual sprites are of _square_ size. 
    To use mipmaps with non-square textures, instead call CCTexture2D#generateMipmap on the sheet texture itself
    (and to save space, save the PVR sprite sheet without mip maps included).
 @js NA
 @lua NA
*/
class CCTexturePVR : public CCObject
{
public:
    CCTexturePVR();
    virtual ~CCTexturePVR();

    /** initializes a CCTexturePVR with a path */
    bool initWithContentsOfFile(const char* path);

    /** creates and initializes a CCTexturePVR with a path */
    static CCTexturePVR* create(const char* path);
    
    // properties 
    
    /** texture id name */
    inline unsigned int getName() { return m_uName; }
    /** texture width */
    inline unsigned int getWidth() { return m_uWidth; }
    /** texture height */
    inline unsigned int getHeight() { return m_uHeight; }
    /** whether or not the texture has alpha */
    inline bool hasAlpha() { return m_bHasAlpha; }
    /** whether or not the texture has premultiplied alpha */
    inline bool hasPremultipliedAlpha() { return m_bHasPremultipliedAlpha; }
    /** whether or not the texture should use hasPremultipliedAlpha instead of global default */
    inline bool isForcePremultipliedAlpha() { return m_bForcePremultipliedAlpha; }
    /** how many mipmaps the texture has. 1 means one level (level 0 */
    inline unsigned int getNumberOfMipmaps() { return m_uNumberOfMipmaps; }
    inline CCTexture2DPixelFormat getFormat() { return m_eFormat; }
    inline bool isRetainName() { return m_bRetainName; }
    inline void setRetainName(bool retainName) { m_bRetainName = retainName; }

private:
    bool unpackPVRv2Data(unsigned char* data, unsigned int len);
    bool unpackPVRv3Data(unsigned char* dataPointer, unsigned int dataLength);
    bool createGLTexture();
    
protected:
    struct CCPVRMipmap m_asMipmaps[CC_PVRMIPMAP_MAX];   // pointer to mipmap images    
    unsigned int m_uNumberOfMipmaps;                    // number of mipmap used
    
    unsigned int m_uWidth, m_uHeight;
    GLuint m_uName;
    bool m_bHasAlpha;
    bool m_bHasPremultipliedAlpha;
    bool m_bForcePremultipliedAlpha;
    
    // cocos2d integration
    bool m_bRetainName;
    CCTexture2DPixelFormat m_eFormat;
    
   const ccPVRTexturePixelFormatInfo *m_pPixelFormatInfo;
};

// end of textures group
/// @}

NS_CC_END


#endif //__CCPVRTEXTURE_H__