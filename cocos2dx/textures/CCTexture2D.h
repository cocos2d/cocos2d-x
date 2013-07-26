/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (C) 2008      Apple Inc. All Rights Reserved.

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

#ifndef __CCTEXTURE2D_H__
#define __CCTEXTURE2D_H__

#include <string>
#include <map>

#include "cocoa/CCObject.h"
#include "cocoa/CCGeometry.h"
#include "ccTypes.h"
#ifdef EMSCRIPTEN
#include "base_nodes/CCGLBufferedNode.h"
#endif // EMSCRIPTEN

NS_CC_BEGIN

class Image;
typedef struct _MipmapInfo MipmapInfo;

/**
 * @addtogroup textures
 * @{
 */

//CONSTANTS:

/** @typedef Texture2DPixelFormat
Possible texture pixel formats
*/
typedef enum {
    //! auto detect the type
    kTexture2DPixelFormat_Automatic,

    //! 32-bit texture: BGRA8888
    kTexture2DPixelFormat_BGRA8888,
    //! 32-bit texture: RGBA8888
    kTexture2DPixelFormat_RGBA8888,
    //! 24-bit texture: RGBA888
    kTexture2DPixelFormat_RGB888,
    //! 16-bit texture without Alpha channel
    kTexture2DPixelFormat_RGB565,
    //! 8-bit textures used as masks
    kTexture2DPixelFormat_A8,
    //! 8-bit intensity texture
    kTexture2DPixelFormat_I8,
    //! 16-bit textures used as masks
    kTexture2DPixelFormat_AI88,
    //! 16-bit textures: RGBA4444
    kTexture2DPixelFormat_RGBA4444,
    //! 16-bit textures: RGB5A1
    kTexture2DPixelFormat_RGB5A1,    
    //! 4-bit PVRTC-compressed texture: PVRTC4
    kTexture2DPixelFormat_PVRTC4,
    //! 4-bit PVRTC-compressed texture: PVRTC4 (has alpha channel)
    kTexture2DPixelFormat_PVRTC4A,
    //! 2-bit PVRTC-compressed texture: PVRTC2
    kTexture2DPixelFormat_PVRTC2,
    //! 2-bit PVRTC-compressed texture: PVRTC2 (has alpha channel)
    kTexture2DPixelFormat_PVRTC2A,
    //! ETC-compressed texture: ETC
    kTexture2DPixelFormat_ETC,

    //! Default texture format: Automatic
    kTexture2DPixelFormat_Default = kTexture2DPixelFormat_Automatic,

    //! none type, for unsigned type or unpassed params
    kTexture2DPixelFormat_None = -1,
} Texture2DPixelFormat;

class GLProgram;

/**
Extension to set the Min / Mag filter
*/
typedef struct _ccTexParams {
    GLuint    minFilter;
    GLuint    magFilter;
    GLuint    wrapS;
    GLuint    wrapT;
} ccTexParams;



class TexturePixelFormatInfo {
public:
    GLenum internalFormat;
    GLenum format;
    GLenum type;
    int bpp;
    bool compressed;
    bool alpha;

    TexturePixelFormatInfo(GLenum internalFormat, GLenum format, GLenum type, int bpp, bool compressed, bool alpha)
        :internalFormat(internalFormat), format(format), type(type), bpp(bpp), compressed(compressed), alpha(alpha){}
};

typedef const std::map<Texture2DPixelFormat, const TexturePixelFormatInfo> ConstTexturePixelFormatInfoMap;
typedef const ConstTexturePixelFormatInfoMap::value_type ConstTexturePixelFormatInfoMapValue;

static ConstTexturePixelFormatInfoMapValue TexturePixelFormatInfoTablesValue[] = 
{
    ConstTexturePixelFormatInfoMapValue(kTexture2DPixelFormat_BGRA8888, TexturePixelFormatInfo(GL_RGBA, GL_BGRA, GL_UNSIGNED_BYTE, 32, false, true)),
    ConstTexturePixelFormatInfoMapValue(kTexture2DPixelFormat_RGBA8888, TexturePixelFormatInfo(GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, 32, false, true)),
    ConstTexturePixelFormatInfoMapValue(kTexture2DPixelFormat_RGBA4444, TexturePixelFormatInfo(GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, 16, false, true)),
    ConstTexturePixelFormatInfoMapValue(kTexture2DPixelFormat_RGB5A1, TexturePixelFormatInfo(GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, 16, false, true)),
    ConstTexturePixelFormatInfoMapValue(kTexture2DPixelFormat_RGB565, TexturePixelFormatInfo(GL_RGB, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 16, false, false)),
    ConstTexturePixelFormatInfoMapValue(kTexture2DPixelFormat_RGB888, TexturePixelFormatInfo(GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, 24, false, false)),
    ConstTexturePixelFormatInfoMapValue(kTexture2DPixelFormat_A8, TexturePixelFormatInfo(GL_ALPHA, GL_ALPHA, GL_UNSIGNED_BYTE, 8, false, false)),
    ConstTexturePixelFormatInfoMapValue(kTexture2DPixelFormat_I8, TexturePixelFormatInfo(GL_LUMINANCE, GL_LUMINANCE, GL_UNSIGNED_BYTE, 8, false, false)),
    ConstTexturePixelFormatInfoMapValue(kTexture2DPixelFormat_AI88, TexturePixelFormatInfo(GL_LUMINANCE_ALPHA, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, 16, false, true)),

#ifdef GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG
    ConstTexturePixelFormatInfoMapValue(kTexture2DPixelFormat_PVRTC2, TexturePixelFormatInfo(GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG, 0xFFFFFFFF, 0xFFFFFFFF, 2, true, false)),
    ConstTexturePixelFormatInfoMapValue(kTexture2DPixelFormat_PVRTC2A, TexturePixelFormatInfo(GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG, 0xFFFFFFFF, 0xFFFFFFFF, 2, true, true)),
    ConstTexturePixelFormatInfoMapValue(kTexture2DPixelFormat_PVRTC4, TexturePixelFormatInfo(GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG, 0xFFFFFFFF, 0xFFFFFFFF, 4, true, false)),
    ConstTexturePixelFormatInfoMapValue(kTexture2DPixelFormat_PVRTC4A, TexturePixelFormatInfo(GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG, 0xFFFFFFFF, 0xFFFFFFFF, 4, true, true)),
#endif

#ifdef GL_ETC1_RGB8_OES
    ConstTexturePixelFormatInfoMapValue(kTexture2DPixelFormat_ETC, TexturePixelFormatInfo(GL_ETC1_RGB8_OES, 0xFFFFFFFF, 0xFFFFFFFF, 24, true, false)),
#endif
};

static ConstTexturePixelFormatInfoMap g_texturePixelFormatInfoTables(TexturePixelFormatInfoTablesValue,
                                                             TexturePixelFormatInfoTablesValue + sizeof(TexturePixelFormatInfoTablesValue) / sizeof(TexturePixelFormatInfoTablesValue[0]));

//CLASS INTERFACES:

/** @brief Texture2D class.
* This class allows to easily create OpenGL 2D textures from images, text or raw data.
* The created Texture2D object will always have power-of-two dimensions. 
* Depending on how you create the Texture2D object, the actual image area of the texture might be smaller than the texture dimensions i.e. "contentSize" != (pixelsWide, pixelsHigh) and (maxS, maxT) != (1.0, 1.0).
* Be aware that the content of the generated textures will be upside-down!
*/
class CC_DLL Texture2D : public Object
#ifdef EMSCRIPTEN
, public GLBufferedNode
#endif // EMSCRIPTEN
{
public:
    /** sets the default pixel format for UIImagescontains alpha channel.
     If the UIImage contains alpha channel, then the options are:
     - generate 32-bit textures: kTexture2DPixelFormat_RGBA8888 (default one)
     - generate 24-bit textures: kTexture2DPixelFormat_RGB888
     - generate 16-bit textures: kTexture2DPixelFormat_RGBA4444
     - generate 16-bit textures: kTexture2DPixelFormat_RGB5A1
     - generate 16-bit textures: kTexture2DPixelFormat_RGB565
     - generate 8-bit textures: kTexture2DPixelFormat_A8 (only use it if you use just 1 color)

     How does it work ?
     - If the image is an RGBA (with Alpha) then the default pixel format will be used (it can be a 8-bit, 16-bit or 32-bit texture)
     - If the image is an RGB (without Alpha) then: If the default pixel format is RGBA8888 then a RGBA8888 (32-bit) will be used. Otherwise a RGB565 (16-bit texture) will be used.

     This parameter is not valid for PVR / PVR.CCZ images.

     @since v0.8
     */
    static void setDefaultAlphaPixelFormat(Texture2DPixelFormat format);

    /** returns the alpha pixel format
     @since v0.8
     */
    static Texture2DPixelFormat defaultAlphaPixelFormat();

    /** treats (or not) PVR files as if they have alpha premultiplied.
     Since it is impossible to know at runtime if the PVR images have the alpha channel premultiplied, it is
     possible load them as if they have (or not) the alpha channel premultiplied.

     By default it is disabled.

     @since v0.99.5
     */
    static void PVRImagesHavePremultipliedAlpha(bool haveAlphaPremultiplied);
    
public:
    Texture2D();
    virtual ~Texture2D();

    const char* description(void) const;

    /** These functions are needed to create mutable textures */
    void releaseData(void *data);
    void* keepData(void *data, unsigned int length);

    /** Initializes with a texture2d with data */
    bool initWithData(const void *data, int dataLen, Texture2DPixelFormat pixelFormat, unsigned int pixelsWide, unsigned int pixelsHigh, const Size& contentSize);

    /** Initializes with mipmaps */
    bool initWithMipmaps(MipmapInfo* mipmaps, int mipmapsNum, Texture2DPixelFormat pixelFormat, unsigned int pixelsWide, unsigned int pixelsHigh);

    /**
    Drawing extensions to make it easy to draw basic quads using a Texture2D object.
    These functions require GL_TEXTURE_2D and both GL_VERTEX_ARRAY and GL_TEXTURE_COORD_ARRAY client states to be enabled.
    */
    /** draws a texture at a given point */
    void drawAtPoint(const Point& point);
    /** draws a texture inside a rect */
    void drawInRect(const Rect& rect);

    /**
    Extensions to make it easy to create a Texture2D object from an image file.
    */
    /** 
	Initializes a texture from a UIImage object.
    We will use the format you specified with setDefaultAlphaPixelFormat to convert the image for texture.
    NOTE: It will not convert the pvr image file.
	*/
    bool initWithImage(Image * uiImage);
    
    /** 
	Initializes a texture from a UIImage object.
	first, we will use the format you passed to the function to convert the image format to the texture format.
    If you pass kTexture2DPixelFormat_Automatic, we will auto detect the image render type and use that type for texture to render.
    NOTE: It will not convert the pvr image file.
    **/
    bool initWithImage(Image * uiImage, Texture2DPixelFormat format);

    /** Initializes a texture from a string with dimensions, alignment, font name and font size */
    bool initWithString(const char *text,  const char *fontName, float fontSize, const Size& dimensions, TextAlignment hAlignment, VerticalTextAlignment vAlignment);
    /** Initializes a texture from a string with font name and font size */
    bool initWithString(const char *text, const char *fontName, float fontSize);
    /** Initializes a texture from a string using a text definition*/
    bool initWithString(const char *text, const FontDefinition& textDefinition);

    /** sets the min filter, mag filter, wrap s and wrap t texture parameters.
    If the texture size is NPOT (non power of 2), then in can only use GL_CLAMP_TO_EDGE in GL_TEXTURE_WRAP_{S,T}.

    @warning Calling this method could allocate additional texture memory.

    @since v0.8
    */
    void setTexParameters(const ccTexParams& texParams);

    /** sets antialias texture parameters:
    - GL_TEXTURE_MIN_FILTER = GL_LINEAR
    - GL_TEXTURE_MAG_FILTER = GL_LINEAR

    @warning Calling this method could allocate additional texture memory.

    @since v0.8
    */
    void setAntiAliasTexParameters();

    /** sets alias texture parameters:
    - GL_TEXTURE_MIN_FILTER = GL_NEAREST
    - GL_TEXTURE_MAG_FILTER = GL_NEAREST

    @warning Calling this method could allocate additional texture memory.

    @since v0.8
    */
    void setAliasTexParameters();


    /** Generates mipmap images for the texture.
    It only works if the texture size is POT (power of 2).
    @since v0.99.0
    */
    void generateMipmap();

    /** returns the pixel format.
     @since v2.0
     */
    const char* stringForFormat() const;

    /** returns the bits-per-pixel of the in-memory OpenGL texture
    @since v1.0
    */
    unsigned int bitsPerPixelForFormat() const;

    /** Helper functions that returns bits per pixels for a given format.
     @since v2.0
     */
    unsigned int bitsPerPixelForFormat(Texture2DPixelFormat format) const;

    /** content size */
    const Size& getContentSizeInPixels();

    bool hasPremultipliedAlpha() const;
    bool hasMipmaps() const;

private:

    /**convert functions*/

    /**
    Convert the format to the format param you specified, if the format is kTexture2DPixelFormat_Automatic, it will detect it automatically and convert to the closest format for you.
    It will return the converted format to you. if the outData != data, you must delete it manually.
    */
    static Texture2DPixelFormat convertDataToFormat(const unsigned char* data, int dataLen, Texture2DPixelFormat originFormat, Texture2DPixelFormat format, unsigned char** outData, int* outDataLen);

    static Texture2DPixelFormat convertI8ToFormat(const unsigned char* data, int dataLen, Texture2DPixelFormat format, unsigned char** outData, int* outDataLen);
    static Texture2DPixelFormat convertAI88ToFormat(const unsigned char* data, int dataLen, Texture2DPixelFormat format, unsigned char** outData, int* outDataLen);
    static Texture2DPixelFormat convertRGB888ToFormat(const unsigned char* data, int dataLen, Texture2DPixelFormat format, unsigned char** outData, int* outDataLen);
    static Texture2DPixelFormat convertRGBA8888ToFormat(const unsigned char* data, int dataLen, Texture2DPixelFormat format, unsigned char** outData, int* outDataLen);

    //I8 to XXX
    static void convertI8ToRGB888(const unsigned char* in, int len, unsigned char* out);
    static void convertI8ToRGBA8888(const unsigned char* in, int len, unsigned char* out);
    static void convertI8ToRGB565(const unsigned char* in, int len, unsigned char* out);
    static void convertI8ToRGBA4444(const unsigned char* in, int len, unsigned char* out);
    static void convertI8ToRGB5A1(const unsigned char* in, int len, unsigned char* out);
    static void convertI8ToAI88(const unsigned char* in, int len, unsigned char* out);

    //AI88 to XXX
    static void convertAI88ToRGB888(const unsigned char* in, int len, unsigned char* out);
    static void convertAI88ToRGBA8888(const unsigned char* in, int len, unsigned char* out);
    static void convertAI88ToRGB565(const unsigned char* in, int len, unsigned char* out);
    static void convertAI88ToRGBA4444(const unsigned char* in, int len, unsigned char* out);
    static void convertAI88ToRGB5A1(const unsigned char* in, int len, unsigned char* out);
    static void convertAI88ToA8(const unsigned char* in, int len, unsigned char* out);
    static void convertAI88ToI8(const unsigned char* in, int len, unsigned char* out);

    //RGB888 to XXX
    static void convertRGB888ToRGBA8888(const unsigned char* in, int len, unsigned char* out);
    static void convertRGB888ToRGB565(const unsigned char* in, int len, unsigned char* out);
    static void convertRGB888ToI8(const unsigned char* in, int len, unsigned char* out);
    static void convertRGB888ToAI88(const unsigned char* in, int len, unsigned char* out);
    static void convertRGB888ToRGBA4444(const unsigned char* in, int len, unsigned char* out);
    static void convertRGB888ToRGB5A1(const unsigned char* in, int len, unsigned char* out);

    //RGBA8888 to XXX
    static void convertRGBA8888ToRGB888(const unsigned char* in, int len, unsigned char* out);
    static void convertRGBA8888ToRGB565(const unsigned char* in, int len, unsigned char* out);
    static void convertRGBA8888ToI8(const unsigned char* in, int len, unsigned char* out);
    static void convertRGBA8888ToA8(const unsigned char* in, int len, unsigned char* out);
    static void convertRGBA8888ToAI88(const unsigned char* in, int len, unsigned char* out);
    static void convertRGBA8888ToRGBA4444(const unsigned char* in, int len, unsigned char* out);
    static void convertRGBA8888ToRGB5A1(const unsigned char* in, int len, unsigned char* out);

    // By default PVR images are treated as if they don't have the alpha channel premultiplied
    bool _PVRHaveAlphaPremultiplied;

    /** pixel format of the texture */
    CC_PROPERTY_READONLY(Texture2DPixelFormat, _pixelFormat, PixelFormat)
    /** width in pixels */
    CC_PROPERTY_READONLY(unsigned int, _pixelsWide, PixelsWide)
    /** height in pixels */
    CC_PROPERTY_READONLY(unsigned int, _pixelsHigh, PixelsHigh)

    /** texture name */
    CC_PROPERTY_READONLY(GLuint, _name, Name)

    /** texture max S */
    CC_PROPERTY(GLfloat, _maxS, MaxS)
    /** texture max T */
    CC_PROPERTY(GLfloat, _maxT, MaxT)
    /** content size */
    CC_PROPERTY_READONLY(Size, _contentSize, ContentSize)

    /** whether or not the texture has their Alpha premultiplied */
    bool _hasPremultipliedAlpha;

    bool _hasMipmaps;

    /** shader program used by drawAtPoint and drawInRect */
    CC_PROPERTY(GLProgram*, _shaderProgram, ShaderProgram);
};

// end of textures group
/// @}

NS_CC_END

#endif //__CCTEXTURE2D_H__

