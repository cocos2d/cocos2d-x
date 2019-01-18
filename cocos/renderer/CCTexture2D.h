/****************************************************************************
Copyright (c) 2008      Apple Inc. All Rights Reserved.
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
#include <unordered_map>

#include "base/CCRef.h"
#include "math/CCGeometry.h"
#include "base/ccTypes.h"

NS_CC_BEGIN

class Image;
class NinePatchInfo;
class SpriteFrame;
typedef struct _MipmapInfo MipmapInfo;

namespace ui
{
    class Scale9Sprite;
}

namespace backend {
    class Texture;
}

/**
 * @addtogroup _2d
 * @{
 */

//CONSTANTS:

//CLASS INTERFACES:

/** 
* @brief Texture2D class. This class allows to easily create OpenGL 2D textures from images, text or raw data.
* The created Texture2D object will always have power-of-two dimensions.
* Depending on how you create the Texture2D object, the actual image area of the texture might be smaller than the texture dimensions i.e. "contentSize" != (pixelsWide, pixelsHigh) and (maxS, maxT) != (1.0, 1.0).
* Be aware that the content of the generated textures will be upside-down!
*/
class CC_DLL Texture2D : public Ref
{
public:
    /** @typedef Texture2D::PixelFormat
     Possible texture pixel formats
     */
    enum class PixelFormat
    {
        //! auto detect the type
        AUTO,
        //! 32-bit texture: BGRA8888
        BGRA8888,
        //! 32-bit texture: RGBA8888
        RGBA8888,
        //! 24-bit texture: RGBA888
        RGB888,
        //! 16-bit texture without Alpha channel
        RGB565,
        //! 8-bit textures used as masks
        A8,
        //! 8-bit intensity texture
        I8,
        //! 16-bit textures used as masks
        AI88,
        //! 16-bit textures: RGBA4444
        RGBA4444,
        //! 16-bit textures: RGB5A1
        RGB5A1,
        //! 4-bit PVRTC-compressed texture: PVRTC4
        PVRTC4,
        //! 4-bit PVRTC-compressed texture: PVRTC4 (has alpha channel)
        PVRTC4A,
        //! 2-bit PVRTC-compressed texture: PVRTC2
        PVRTC2,
        //! 2-bit PVRTC-compressed texture: PVRTC2 (has alpha channel)
        PVRTC2A,
        //! ETC-compressed texture: ETC
        ETC,
        //! S3TC-compressed texture: S3TC_Dxt1
        S3TC_DXT1,
        //! S3TC-compressed texture: S3TC_Dxt3
        S3TC_DXT3,
        //! S3TC-compressed texture: S3TC_Dxt5
        S3TC_DXT5,
        //! ATITC-compressed texture: ATC_RGB
        ATC_RGB,
        //! ATITC-compressed texture: ATC_EXPLICIT_ALPHA
        ATC_EXPLICIT_ALPHA,
        //! ATITC-compressed texture: ATC_INTERPOLATED_ALPHA
        ATC_INTERPOLATED_ALPHA,
        //! Default texture format: AUTO
        
        MTL_B5G6R5,
        //MTL_A1BGR5,
        MTL_BGR5A1,
        MTL_ABGR4,
        
        DEFAULT = AUTO,
        
        NONE = -1
    };
    
    
    struct PixelFormatInfo {

        PixelFormatInfo(GLenum anInternalFormat, GLenum aFormat, GLenum aType, int aBpp, bool aCompressed, bool anAlpha)
            : internalFormat(anInternalFormat)
            , format(aFormat)
            , type(aType)
            , bpp(aBpp)
            , compressed(aCompressed)
            , alpha(anAlpha)
        {}

        GLenum internalFormat;
        GLenum format;
        GLenum type;
        int bpp;
        bool compressed;
        bool alpha;
    };
    
    typedef std::map<Texture2D::PixelFormat, const PixelFormatInfo> PixelFormatInfoMap;
    
    /**
     Extension to set the Min / Mag filter
     */
    typedef struct _TexParams {
        GLuint    minFilter;
        GLuint    magFilter;
        GLuint    wrapS;
        GLuint    wrapT;
    }TexParams;
    
public:
    /** sets the default pixel format for UIImagescontains alpha channel.
     
     @param format
     If the UIImage contains alpha channel, then the options are:
     - generate 32-bit textures: Texture2D::PixelFormat::RGBA8888 (default one)
     - generate 24-bit textures: Texture2D::PixelFormat::RGB888
     - generate 16-bit textures: Texture2D::PixelFormat::RGBA4444
     - generate 16-bit textures: Texture2D::PixelFormat::RGB5A1
     - generate 16-bit textures: Texture2D::PixelFormat::RGB565
     - generate 8-bit textures: Texture2D::PixelFormat::A8 (only use it if you use just 1 color)

     How does it work ?
     - If the image is an RGBA (with Alpha) then the default pixel format will be used (it can be a 8-bit, 16-bit or 32-bit texture)
     - If the image is an RGB (without Alpha) then: If the default pixel format is RGBA8888 then a RGBA8888 (32-bit) will be used. Otherwise a RGB565 (16-bit texture) will be used.

     This parameter is not valid for PVR / PVR.CCZ images.

     @since v0.8
     */
    static void setDefaultAlphaPixelFormat(Texture2D::PixelFormat format);

    /** Returns the alpha pixel format.
     @since v0.8
     */
    static Texture2D::PixelFormat getDefaultAlphaPixelFormat();
    
public:
    /**
     * @js ctor
     */
    Texture2D();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Texture2D();

    /** Initializes with a texture2d with data.
     
     @param data Specifies a pointer to the image data in memory.
     @param dataLen The image data length.
     @param pixelFormat The image pixelFormat.
     @param pixelsWide The image width.
     @param pixelsHigh The image height.
     @param contentSize The image content size.
     * @js NA
     * @lua NA
     */
    bool initWithData(const void *data, ssize_t dataLen, Texture2D::PixelFormat pixelFormat, int pixelsWide, int pixelsHigh, const Size& contentSize) { return initWithData(data, dataLen, pixelFormat, pixelFormat, pixelsWide, pixelsHigh, contentSize);}

    /** Initializes with a texture2d with data.
     
     @param data Specifies a pointer to the image data in memory.
     @param dataLen The image data length.
     @param pixelFormat The image pixelFormat.
     @param renderFormat The format converted to.
     @param pixelsWide The image width.
     @param pixelsHigh The image height.
     @param contentSize The image content size.
     * @js NA
     * @lua NA
     */
    bool initWithData(const void *data, ssize_t dataLen, Texture2D::PixelFormat pixelFormat, Texture2D::PixelFormat renderFormat, int pixelsWide, int pixelsHigh, const Size& contentSize);
    
    /** Initializes with mipmaps. 
     
     @param mipmaps Specifies a pointer to the image data in memory.
     @param mipmapsNum The mipmaps number.
     @param pixelFormat The image pixelFormat.
     @param pixelsWide The image width.
     @param pixelsHigh The image height.
     */
    bool initWithMipmaps(MipmapInfo* mipmaps, int mipmapsNum, Texture2D::PixelFormat pixelFormat, Texture2D::PixelFormat renderFormat, int pixelsWide, int pixelsHigh);
    
    /** Update with texture data.
     
     @param data Specifies a pointer to the image data in memory.
     @param offsetX Specifies a texel offset in the x direction within the texture array.
     @param offsetY Specifies a texel offset in the y direction within the texture array.
     @param width Specifies the width of the texture subimage.
     @param height Specifies the height of the texture subimage.
     */
    bool updateWithData(void *data,int offsetX,int offsetY,int width,int height);
    /**
    Drawing extensions to make it easy to draw basic quads using a Texture2D object.
    These functions require GL_TEXTURE_2D and both GL_VERTEX_ARRAY and GL_TEXTURE_COORD_ARRAY client states to be enabled.
    */
    /** Draws a texture at a given point. */
//    void drawAtPoint(const Vec2& point);
    /** Draws a texture inside a rect.*/
//    void drawInRect(const Rect& rect);

    /**
    Extensions to make it easy to create a Texture2D object from an image file.
    */
    /** 
    Initializes a texture from a UIImage object.

    We will use the format you specified with setDefaultAlphaPixelFormat to convert the image for texture.
    NOTE: It will not convert the pvr image file.
    @param image An UIImage object.
    */
    bool initWithImage(Image * image);
    
    /** 
    Initializes a texture from a UIImage object.

    We will use the format you passed to the function to convert the image format to the texture format.
    If you pass PixelFormat::Automatic, we will auto detect the image render type and use that type for texture to render.
    @param image An UIImage object.
    @param format Texture pixel formats.
    **/
    bool initWithImage(Image * image, PixelFormat format);

    /** Initializes a texture from a string with dimensions, alignment, font name and font size. 
     
     @param text A null terminated string.
     @param fontName The font name.
     @param fontSize The font size.
     @param dimensions The font dimension.
     @param hAlignment The font horizontal text alignment type.
     @param vAlignment The font vertical text alignment type.
     @param enableWrap Whether enable text wrap or not.
     @param overflow Whether shrink font size when content larger than the dimensions.
     */
    bool initWithString(const char *text,  const std::string &fontName, float fontSize, const Size& dimensions = Size(0, 0), TextHAlignment hAlignment = TextHAlignment::CENTER, TextVAlignment vAlignment = TextVAlignment::TOP, bool enableWrap = true, int overflow = 0);

    /** Initializes a texture from a string using a text definition.
     
     @param text A null terminated string.
     @param textDefinition A FontDefinition object contains font attributes.
     */
    bool initWithString(const char *text, const FontDefinition& textDefinition);
    
    //TODO: minggo: is it resaonable?
    bool initWithBackendTexture(backend::Texture* texture);

    /** Set sampler properties
    */
    void setSamplerDescriptor(const backend::SamplerDescriptor& texParams);
    
    /** Generates mipmap images for the texture.
     It only works if the texture size is POT (power of 2).
     @since v0.99.0
     */
//    TODO coulsonwang
    void generateMipmap();
    
    /** Sets antialias texture parameters:
     - GL_TEXTURE_MIN_FILTER = GL_LINEAR
     - GL_TEXTURE_MAG_FILTER = GL_LINEAR
     
     @warning Calling this method could allocate additional texture memory.
     
     @since v0.8
     */
    void setAntiAliasTexParameters();

    /** Sets alias texture parameters:
    - GL_TEXTURE_MIN_FILTER = GL_NEAREST
    - GL_TEXTURE_MAG_FILTER = GL_NEAREST

    @warning Calling this method could allocate additional texture memory.

    @since v0.8
    */
    void setAliasTexParameters();

    /** Returns the pixel format.
     @since v2.0
     */
    const char* getStringForFormat() const;

    /** Returns the bits-per-pixel of the in-memory OpenGL texture
    @since v1.0
    */
    unsigned int getBitsPerPixelForFormat() const;

    /** Helper functions that returns bits per pixels for a given format.
     @since v2.0
     */
    unsigned int getBitsPerPixelForFormat(Texture2D::PixelFormat format) const;

    /** Get content size. */
    const Size& getContentSizeInPixels();

    /** Whether or not the texture has their Alpha premultiplied. */
    bool hasPremultipliedAlpha() const;
    
    /** Whether or not the texture has mip maps.*/
    bool hasMipmaps() const;

    /** Gets the pixel format of the texture. */
    Texture2D::PixelFormat getPixelFormat() const;
    
    /** Gets the width of the texture in pixels. */
    int getPixelsWide() const;
    
    /** Gets the height of the texture in pixels. */
    int getPixelsHigh() const;
    
    /** Gets the texture name. */
    GLuint getName() const;
    backend::Texture* getBackendTexture() const;
    
    /** Gets max S. */
    GLfloat getMaxS() const;
    /** Sets max S. */
    void setMaxS(GLfloat maxS);
    
    /** Gets max T. */
    GLfloat getMaxT() const;
    /** Sets max T. */
    void setMaxT(GLfloat maxT);
    
    /** Get the texture content size.*/
    Size getContentSize() const;

    std::string getPath()const { return _filePath; }

    void setAlphaTexture(Texture2D* alphaTexture);
    Texture2D* getAlphaTexture() const;

    bool getAlphaTextureName() const;
public:
    /** Get pixel info map, the key-value pairs is PixelFormat and PixelFormatInfo.*/
    static const PixelFormatInfoMap& getPixelFormatInfoMap();
    
private:
    /**
    * A struct for storing 9-patch image capInsets.
    */

    class NinePatchInfo
    {
    public:
        Rect capInsetSize;
        std::unordered_map<SpriteFrame*, Rect> capInsetMap;
    };

    /**
     * Whether the texture contains a 9-patch capInset info or not.
     *
     * @return True is Texture contains a 9-patch info, false otherwise.
     */
    bool isContain9PatchInfo()const;

    /**
     * Get spriteFrame capInset, If spriteFrame can't be found in 9-patch info map,
     * then single 9-patch texture capInset will be returned.
     * If the arg is nullptr, the capInset of single 9-patch texture will be returned.
     *
     * @param spriteFrame A SpriteFrame object pointer.
     *
     * @return The capInset of the SpriteFrame object.
     */
    const Rect& getSpriteFrameCapInset(SpriteFrame* spriteFrame)const;
    /**
     * Remove the spriteFrame capInset info when the spriteFrame is removed.
     *
     * @param spriteFrame A SpriteFrame object pointer.
     */
    void removeSpriteFrameCapInset(SpriteFrame* spriteFrame);
    /**
     * Add capInset for sprite atlas.
     * When handling single texture, pass nullptr in the first arg.
     *
     * @param spritframe The sprite frame object.
     * @param capInsets The parsed capInset from a .9 patch image.
     */
    void addSpriteFrameCapInset(SpriteFrame* spritframe, const Rect& capInsets);



    
protected:
    /** pixel format of the texture */
    Texture2D::PixelFormat _pixelFormat;

    /** width in pixels */
    int _pixelsWide;

    /** height in pixels */
    int _pixelsHigh;

    /** texture name */
    backend::Texture* _texture;
    

    /** texture max S */
    GLfloat _maxS;
    
    /** texture max T */
    GLfloat _maxT;

    /** content size */
    Size _contentSize;

    /** whether or not the texture has their Alpha premultiplied */
    bool _hasPremultipliedAlpha;
    
    /** whether or not the texture has mip maps*/
    bool _hasMipmaps;

    static const PixelFormatInfoMap _pixelFormatInfoTables;

    bool _antialiasEnabled;
    NinePatchInfo* _ninePatchInfo;
    friend class SpriteFrameCache;
    friend class TextureCache;
    friend class ui::Scale9Sprite;

    bool _valid;
    std::string _filePath;

    Texture2D* _alphaTexture;
};


// end of textures group
/// @}

NS_CC_END

#endif //__CCTEXTURE2D_H__

