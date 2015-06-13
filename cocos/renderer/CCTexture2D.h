/****************************************************************************
Copyright (c) 2008      Apple Inc. All Rights Reserved.
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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
#ifdef EMSCRIPTEN
#include "CCGLBufferedNode.h"
#endif // EMSCRIPTEN

NS_CC_BEGIN

class Image;
class NinePatchInfo;
class SpriteFrame;
typedef struct _MipmapInfo MipmapInfo;

namespace ui
{
    class Scale9Sprite;
}

/**
 * @addtogroup _2d
 * @{
 */

//CONSTANTS:

class GLProgram;

//CLASS INTERFACES:

/** 
 * @brief @~english Texture2D class. This class allows to easily create OpenGL 2D textures from images, text or raw data.
 * The created Texture2D object will always have power-of-two dimensions.
 * Depending on how you create the Texture2D object, the actual image area of the texture might be smaller than the texture dimensions i.e. "contentSize" != (pixelsWide, pixelsHigh) and (maxS, maxT) != (1.0, 1.0).
 * Be aware that the content of the generated textures will be upside-down!
 * @~chinese Texture2D 类。这个类可以轻松地从图片，文本或者数据创建 OpenGL 2D 纹理。
 * 创建的 Texture2D 对象的宽与高总是保持为 2 的幂次方。
 * 实际纹理的图像大小可能小于创建的纹理大小。比如：contentSize != (pixelsWide, pixelsHigh) 和 (maxS, maxT) != (1.0,1.0)。
 * 注意：生成的纹理对象内容是上下颠倒的。
 */
class CC_DLL Texture2D : public Ref
#ifdef EMSCRIPTEN
, public GLBufferedNode
#endif // EMSCRIPTEN
{
public:
    /** @typedef Texture2D::PixelFormat
     * @~english Possible texture pixel formats
     * @~chinese 纹理的像素格式。
     */
    enum class PixelFormat
    {
        /** @~english auto detect the type
        * @~chinese 自动检测类型。
        */
        AUTO,
        /**@~english  32-bit texture: BGRA8888
        * @~chinese 32位纹理：BGRA8888
        */
        BGRA8888,
        /**@~english  32-bit texture: RGBA8888
        * @~chinese 32位纹理：RGBA8888
        */
        RGBA8888,
        /**@~english  24-bit texture: RGB888
        * @~chinese 24位纹理：RGB888
        */
        RGB888,
        /**@~english  16-bit texture without Alpha channel
        * @~chinese 不包含 alpha 通道的 16位纹理
        */
        RGB565,
        /**@~english  8-bit textures used as masks
        * @~chinese 当做遮罩使用的 8位纹理
        */
        A8,
        /**@~english  8-bit intensity texture
        * @~chinese 8位亮度纹理
        */
        I8,
        /**@~english  16-bit textures used as masks
        * @~chinese 当做遮罩使用的 16 位纹理
        */
        AI88,
        /**@~english  16-bit textures: RGBA4444
        * @~chinese 16位纹理：RGBA4444
        */
        RGBA4444,
        /**@~english  16-bit textures: RGB5A1
        * @~chinese 16位纹理 RGB5A1
        */
        RGB5A1,
        /**@~english  4-bit PVRTC-compressed texture: PVRTC4
        * @~chinese 4位 PVRTC 压缩纹理：PVRTC4
        */
        PVRTC4,
        /**@~english  4-bit PVRTC-compressed texture: PVRTC4 (has alpha channel)
        * @~chinese 4位 PVRTC 压缩纹理：PVRTC4（有 alpha 通道）
        */
        PVRTC4A,
        /**@~english  2-bit PVRTC-compressed texture: PVRTC2
        * @~chinese 2位 PVRTC 压缩纹理：PVRTC2
        */
        PVRTC2,
        /**@~english  2-bit PVRTC-compressed texture: PVRTC2 (has alpha channel)
        * @~chinese 2位 PVRTC 压缩纹理：PVRTC2（有 alpha 通道）
        */
        PVRTC2A,
        /**@~english  ETC-compressed texture: ETC
        * @~chinese ETC 压缩纹理：ETC
        */
        ETC,
        /**@~english  S3TC-compressed texture: S3TC_Dxt1
        * @~chinese S3TC 压缩纹理：S3TC_Dxt1
        */
        S3TC_DXT1,
        /**@~english  S3TC-compressed texture: S3TC_Dxt3
        * @~chinese S3TC 压缩纹理：S3TC_Dxt3
        */
        S3TC_DXT3,
        /**@~english  S3TC-compressed texture: S3TC_Dxt5
        * @~chinese S3TC 压缩纹理：S3TC_Dxt5
        */
        S3TC_DXT5,
        /**@~english  ATITC-compressed texture: ATC_RGB
        * @~chinese ATITC 压缩纹理：ATC_RGB
        */
        ATC_RGB,
        /**@~english  ATITC-compressed texture: ATC_EXPLICIT_ALPHA
        * @~chinese ATITC 压缩纹理：ATC_EXPLICIT_ALPHA
        */
        ATC_EXPLICIT_ALPHA,
        /**@~english  ATITC-compresed texture: ATC_INTERPOLATED_ALPHA
        * @~chinese ATITC 压缩纹理：ATC_INTERPOLATED_ALPHA
        */
        ATC_INTERPOLATED_ALPHA,
        /**@~english  Default texture format: AUTO
        * @~chinese 默认纹理格式为：AUTO
        */
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
    
    /**@~english
     * Extension to set the Min / Mag filter
     * @~chinese 
     * 用于设置 Min / Mag 过滤器的扩展结构体。
     */
    typedef struct _TexParams {
        GLuint    minFilter;
        GLuint    magFilter;
        GLuint    wrapS;
        GLuint    wrapT;
    }TexParams;
    
public:
    /** @~english sets the default pixel format for `Image` contains alpha channel.
     * @~chinese 为包含 alpha 通道的 `Image` 对象设置默认的像素格式。
     * 
     * @param format @~english
     * If the `Image` contains alpha channel, then the options are:
     * - generate 32-bit textures: `Texture2D::PixelFormat::RGBA8888` (default one)
     * - generate 24-bit textures: `Texture2D::PixelFormat::RGB888`
     * - generate 16-bit textures: `Texture2D::PixelFormat::RGBA4444`
     * - generate 16-bit textures: `Texture2D::PixelFormat::RGB5A1`
     * - generate 16-bit textures: `Texture2D::PixelFormat::RGB565`
     * - generate 8-bit textures: Texture2D::PixelFormat::A8 (only use it if you use just 1 color)
     * 
     * How does it work ?
     * - If the image is an RGBA (with Alpha) then the default pixel format will be used (it can be a 8-bit, 16-bit or 32-bit texture)
     * - If the image is an RGB (without Alpha) then: If the default pixel format is RGBA8888 then a RGBA8888 (32-bit) will be used. Otherwise a RGB565 (16-bit texture) will be used.
     * 
     * This parameter is not valid for PVR / PVR.CCZ images.
     * 
     * @~chinese
     * 如果 `Image` 对象包含 alpha 通道，那么可以:
     * - 生成32位的纹理: `Texture2D::PixelFormat:RGBA8888` (默认值)
     * - 生成24位纹理: `Texture2D::PixelFormat::RGB888`
     * - 生成16位纹理: `Texture2D::PixelFormat::RGBA4444`
     * - 生成16位纹理: `Texture2D::PixelFormat::RGB5A1`
     * - 生成16位纹理: `Texture2D::PixelFormat::RGB565`
     * - 生成8位纹理: `Texture2D::PixelFormat:A8` (只有当你使用单色时才能使用此格式)
     * 
     * 它是如何工作的?
     * - 如果是一个 RGBA (包含 alpha 通道) 图像，则使用默认的像素格式(它可以是一个8位,16位或32位的纹理)
     * - 如果是一个 RGB (没有 alpha 通道) 图像，那么：当默认的像素格式为 RGBA8888 时，RGBA8888 (32位) 将被使用。否则，RGB565(16位纹理)将被使用。
     * 
     * 这个参数对 PVR/PVR.CCZ 图像是无效的。
     * 
     * @since v0.8
     */
    static void setDefaultAlphaPixelFormat(Texture2D::PixelFormat format);

    /** @~english Returns the default alpha pixel format.
     * @~chinese 返回默认的 alpha 通道像素格式。
     * @since v0.8
     */
    static Texture2D::PixelFormat getDefaultAlphaPixelFormat();
    CC_DEPRECATED_ATTRIBUTE static Texture2D::PixelFormat defaultAlphaPixelFormat() { return Texture2D::getDefaultAlphaPixelFormat(); };

    /** @~english Treats (or not) PVR files as if they have alpha premultiplied.
     * @~chinese 设置处理 PVR 文件时是否进行 alpha 预乘。
     * 
     * @param haveAlphaPremultiplied @~english
     * Since it is impossible to know at runtime if the PVR images have the alpha channel premultiplied, it is
     * possible load them as if they have (or not) the alpha channel premultiplied.
     * 
     * By default it is disabled.
     * 
     * deprecated, please use Image::setPVRImagesHavePremultipliedAlpha() instead.
     * 
     * @~chinese 
     * 因为在运行时无法知道 PVR 图像是否需要进行 alpha 预乘,
     * 所以需要在加载时，决定是否进行 alpha 预乘。
     * 
     * 在默认情况下是禁用的。
     * 
     * 弃用，请使用 `Image::setPVRImagesHavePremultipliedAlpha()` 代替。
     * 
     * @since v0.99.5
     */
    CC_DEPRECATED_ATTRIBUTE static void PVRImagesHavePremultipliedAlpha(bool haveAlphaPremultiplied);
    
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
    /**@~english
     * Get texutre name, dimensions and coordinates message by a string.
     * @~chinese 
     * 以字符串形式获取纹理名称，大小和坐标信息。
     * @return @~english The string include texture name, dimensions and coordinates message.
     * @~chinese 包含纹理名称，大小和坐标信息的字符串。
     * @js NA
     * @lua NA
     */
    virtual std::string getDescription() const;

	/** @~english Release only the gl texture.
     * @~chinese 只释放 gl 纹理。
     * @js NA
     * @lua NA
     */
	void releaseGLTexture();

    /** @~english Initializes a Texture2D object with data.
     * @~chinese 使用指定的数据初始化 Texture2D 对象。
     * @param data @~english Specifies a pointer to the image data in memory.
     * @~chinese 图像数据的指针。
     * @param dataLen @~english The image data length.
     * @~chinese 图像数据的长度。
     * @param pixelFormat @~english The image pixelFormat.
     * @~chinese 图像的像素格式。
     * @param pixelsWide @~english The image width.
     * @~chinese 图像的宽度。
     * @param pixelsHigh @~english The image height.
     * @~chinese 图像的高度。
     * @param contentSize @~english The image content size.
     * @~chinese 图像内容的大小。
     * @return @~english If the initialization is success, return true; else return false.
     * @~chinese 如果初始化成功，返回 true；否则返回 false。
     * @js NA
     * @lua NA
     */
    bool initWithData(const void *data, ssize_t dataLen, Texture2D::PixelFormat pixelFormat, int pixelsWide, int pixelsHigh, const Size& contentSize);

    /** @~english Initializes with mipmaps. 
     * @~chinese 使用 mipmaps 图像初始化。
     * @param mipmaps @~english Specifies a pointer to the mipmaps image data in memory.
     * @~chinese mipmaps 图像数据的指针。
     * @param mipmapsNum @~english The mipmaps number.
     * @~chinese mipmaps 图像数据的长度。
     * @param pixelFormat @~english The image pixelFormat.
     * @~chinese mipmaps 图像的像素格式。
     * @param pixelsWide @~english The image width.
     * @~chinese 图像的宽度。
     * @param pixelsHigh @~english The image height.
     * @~chinese 图像的高度。
     * @return @~english If the initialization is success, return true; else return false.
     * @~chinese 如果初始化成功，返回 true；否则返回 false。
     */
    bool initWithMipmaps(MipmapInfo* mipmaps, int mipmapsNum, Texture2D::PixelFormat pixelFormat, int pixelsWide, int pixelsHigh);

    /** @~english Update with texture data.
     * @~chinese 使用指定的数据更新纹理。
     * @param data @~english Specifies a pointer to the image data in memory.
     * @~chinese 图像数据的指针。
     * @param offsetX @~english Specifies a texel offset in the x direction within the texture array.
     * @~chinese 纹理数据中的 x 轴的偏移量。
     * @param offsetY @~english Specifies a texel offset in the y direction within the texture array.
     * @~chinese 纹理数据中的 y 轴的偏移量。
     * @param width @~english Specifies the width of the texture subimage.
     * @~chinese 指定纹理中所使用图象的宽度。
     * @param height @~english Specifies the height of the texture subimage.
     * @~chinese 指定纹理中所使用图象的高度。
     * @return @~english If the update is success, return true; else return false.
     * @~chinese 如果更新成功，返回 true；否则返回 false。
     */
    bool updateWithData(const void *data,int offsetX,int offsetY,int width,int height);
    /**@~english
     * Drawing extensions to make it easy to draw basic quads using a Texture2D object.
     * These functions require GL_TEXTURE_2D and both GL_VERTEX_ARRAY and GL_TEXTURE_COORD_ARRAY client states to be enabled.
     * @~chinese 
     * 绘制相关的扩展方法，让使用 Texture2D 绘制基础图形变得更简单。
     * 这些功能需要开启 GL_TEXTURE_2D，GL_VERTEX_ARRAY 和 GL_TEXTURE_COORD_ARRAY 这些 GL 状态。
     */
    /** @~english Draws a texture at a given point.
     * @~chinese 在给定的坐标绘制纹理。
     */
    void drawAtPoint(const Vec2& point);
    /** @~english Draws a texture inside a rect.
     * @~chinese 在一个矩形区域内绘制纹理。
     */
    void drawInRect(const Rect& rect);

    /**@~english
     * Extensions to make it easy to create a Texture2D object from an image file.
     * @~chinese 
     * 简化从图像文件创建 Texture2D 对象的扩展方法。
    */
    /** @~english
	 * Initializes a texture from a `Image` object.
     *
     * We will use the format you specified with setDefaultAlphaPixelFormat to convert the image for texture.
     * NOTE: It will not convert the pvr image file.
     * @~chinese 
     * 使用 `Image` 对象初始化纹理。
     * 
     * 这个方法将使用 `setDefaultAlphaPixelFormat` 函数设置的像素格式来转换图像数据。
     * 注意：它不会转换 pvr 图像文件。
     * @param image @~english An `Image` object.
     * @~chinese 一个 `Image` 对象。
     * @return @~english If the initialization is success, return true; else return false.
     * @~chinese 如果初始化成功，返回 true；否则返回 false。
	 */
    bool initWithImage(Image * image);
    
    /** @~english
	 * Initializes a texture from a UIImage object.
     * 
     * We will use the format you passed to the function to convert the image format to the texture format.
     * If you pass PixelFormat::Automatic, we will auto detect the image render type and use that type for texture to render.
     * @~chinese 
     * 使用 `Image` 对象初始化纹理。
     * 
     * 这个方法将使用参数指定的像素格式来转换图像数据。
     * 如果 format 参数值为 `PixelFormat:AUTO`，将自动检测图像的渲染类型并使用该类型渲染纹理。
     * @param image @~english An `Image` object.
     * @~chinese 一个 `Image` 对象。
     * @param format @~english Texture pixel formats.
     * @~chinese 纹理像素格式。
     * @return @~english If the initialization is success, return true; else return false.
     * @~chinese 如果初始化成功，返回 true；否则返回 false。
     */
    bool initWithImage(Image * image, PixelFormat format);

    /** @~english Initializes a texture from a string with dimensions, alignment, font name and font size. 
     * @~chinese 使用指定的字符串，字体名称，字体大小，纹理大小和文本对齐方式初始化一个纹理。
     * 
     * @param text @~english A null terminated string.
     * @~chinese 以空字符结尾的字符串。
     * @param fontName @~english The font name.
     * @~chinese 字体名称。
     * @param fontSize @~english The font size.
     * @~chinese 字体大小。
     * @param dimensions @~english The font dimension.
     * @~chinese 纹理大小
     * @param hAlignment @~english The font horizontal text alignment type.
     * @~chinese 文本水平对齐方式。
     * @param vAlignment @~english The font vertical text alignment type.
     * @~chinese 文本垂直对齐方式。
     * @return @~english If the initialization is success, return true; else return false.
     * @~chinese 如果初始化成功，返回 true；否则返回 false。
     */
    bool initWithString(const char *text,  const std::string &fontName, float fontSize, const Size& dimensions = Size(0, 0), TextHAlignment hAlignment = TextHAlignment::CENTER, TextVAlignment vAlignment = TextVAlignment::TOP);

    /** @~english Initializes a texture from a string using a text definition.
     * @~chinese 使用指定的文本与指定的字体属性初始化一个纹理。
     * @param text @~english A null terminated string.
     * @~chinese 以空字符结尾的字符串。
     * @param textDefinition @~english A FontDefinition object contains font attributes.
     * @~chinese 包含字体属性的 `FontDefinition` 对象。
     * @return @~english If the initialization is success, return true; else return false.
     * @~chinese 如果初始化成功，返回 true；否则返回 false。
     */
    bool initWithString(const char *text, const FontDefinition& textDefinition);

    /** @~english Sets the min filter, mag filter, wrap s and wrap t texture parameters.
     * If the texture size is NPOT (non power of 2), then in can only use GL_CLAMP_TO_EDGE in GL_TEXTURE_WRAP_{S,T}.
     *
     * @~chinese 设置 min 过滤器，mag 过滤器，wrap s 和 wrap t 这些纹理参数。
     * 如果纹理大小为 NPOT(非 2 的幂次方)，那么只能在 GL_TEXTURE_WRAP_{S,T} 中使用 GL_CLAMP_TO_EDGE。
     * 
     * @warning @~english Calling this method could allocate additional texture memory.
     * @code 
     * When this function bound into js or lua,the input parameter will be changed
     * In js: var setTexParameters(var arg1, var arg2, var arg3, var arg4)
     * In lua: local setTexParameters(local arg1, local arg2, local arg3, local arg4)
     * @endcode
     *
     * @~chinese 调用该方法会分配额外的纹理内存。
     * @code 
     * 当此方法绑定到 js 或者 lua 中，参数需要变为：
     * js 中: var setTexParameters(var arg1, var arg2, var arg3, var arg4)
     * lua 中: local setTexParameters(local arg1, local arg2, local arg3, local arg4)
     * @endcode
     * @since v0.8
     */
    void setTexParameters(const TexParams& texParams);

    /**
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE void setTexParameters(const TexParams* texParams) { return setTexParameters(*texParams); };

    /** @~english Sets antialias texture parameters:
     * - GL_TEXTURE_MIN_FILTER = GL_LINEAR
     * - GL_TEXTURE_MAG_FILTER = GL_LINEAR
     *
     * @~chinese 设置抗锯齿纹理参数:
     * - GL_TEXTURE_MIN_FILTER = GL_LINEAR
     * - GL_TEXTURE_MAG_FILTER = GL_LINEAR
     * 
     * @warning @~english Calling this method could allocate additional texture memory.
     * @~chinese 调用该方法会分配额外的纹理内存。
     * 
     * @since v0.8
     */
    void setAntiAliasTexParameters();

    /** @~english Sets alias texture parameters:
     * - GL_TEXTURE_MIN_FILTER = GL_NEAREST
     * - GL_TEXTURE_MAG_FILTER = GL_NEAREST
     *
     * @~chinese 设置锯齿纹理参数:
     * - GL_TEXTURE_MIN_FILTER = GL_NEAREST
     * - GL_TEXTURE_MAG_FILTER = GL_NEAREST
     * 
     * @warning @~english Calling this method could allocate additional texture memory.
     * @~chinese 调用该方法会分配额外的纹理内存。
     * 
     * @since v0.8
     */
    void setAliasTexParameters();


    /** @~english Generates mipmap images for the texture.
     * It only works if the texture size is POT (power of 2).
     * @~chinese 为纹理生成 mipmaps 图像。
     * 只有当纹理大小为 POT（2的幂次方） 是起效。
     * @since v0.99.0
     */
    void generateMipmap();

    /** @~english Returns the pixel format by string.
     * @~chinese 返回像素格式的字符串。
     * @since v2.0
     */
    const char* getStringForFormat() const;
    CC_DEPRECATED_ATTRIBUTE const char* stringForFormat() const { return getStringForFormat(); };

    /** @~english Returns the bits-per-pixel of the in-memory OpenGL texture
     * @~chinese 返回内存中 OpenGL 纹理每个像素所使用的位数。
    * @since v1.0
    */
    unsigned int getBitsPerPixelForFormat() const;
    CC_DEPRECATED_ATTRIBUTE unsigned int bitsPerPixelForFormat() const { return getBitsPerPixelForFormat(); };

    /** @~english Helper functions that returns bits per pixels for a given format.
     * @~chinese 这个工具函数获取指定的像素格式下每个像素所使用的位数。
     * @since v2.0
     */
    unsigned int getBitsPerPixelForFormat(Texture2D::PixelFormat format) const;
    CC_DEPRECATED_ATTRIBUTE unsigned int bitsPerPixelForFormat(Texture2D::PixelFormat format) const { return getBitsPerPixelForFormat(format); };

    /** @~english Get content size in pixels.  @~chinese 获取纹理的大小，以像素为单位。*/
    const Size& getContentSizeInPixels();

    /** @~english Whether or not the texture has their Alpha premultiplied.
     *  @~chinese 获取纹理是否有 alpha 预乘。
     */
    bool hasPremultipliedAlpha() const;
    
    /** @~english Whether or not the texture has mip maps.
     * @~chinese 获取纹理是否有 mipmaps.
     */
    bool hasMipmaps() const;

    /** @~english Gets the pixel format of the texture.
     *  @~chinese 获取纹理的像素格式。
     */
    Texture2D::PixelFormat getPixelFormat() const;
    
    /** @~english Gets the width of the texture in pixels. 
     * @~chinese 获取纹理的宽度(以像素为单位)。
     */
    int getPixelsWide() const;
    
    /** @~english Gets the height of the texture in pixels.
     *  @~chinese 获取纹理的高度(以像素为单位)。
     */
    int getPixelsHigh() const;
    
    /** @~english Gets the texture name.
     *  @~chinese 获取纹理的名字。
     */
    GLuint getName() const;
    
    /** @~english Gets max S.
     *  @~chinese 获取 S 的最大值。
     */
    GLfloat getMaxS() const;
    /** @~english Sets max S. 
     * @~chinese 设置 S 的最大值。
     */
    void setMaxS(GLfloat maxS);
    
    /** @~english Gets max T. 
     * @~chinese 获取 T 的最大值。
     */
    GLfloat getMaxT() const;
    /** @~english Sets max T. 
     * @~chinese 设置 T 的最大值。
     */
    void setMaxT(GLfloat maxT);
    
    /** @~english Get the texture content size.
     * @~chinese 获取纹理内容的大小。
     */
    Size getContentSize() const;
    
    /** @~english Set a shader program to the texture.
     * It's used by drawAtPoint and drawInRect
     * @~chinese 设置一个纹理所使用的 shader。
     * 在 `drawAtPoint` 和 `drawInRect` 中使用。
     */
    void setGLProgram(GLProgram* program);

    /** @~english Get a shader program from the texture.
     * @~chinese 获取纹理所使用的 shader。
     */
    GLProgram* getGLProgram() const;


public:
    /** @~english Get pixel info map, the key-value pairs is PixelFormat and PixelFormatInfo.
     * @~chinese 获取像素信息的映射，是 `PixelFormat` 与 `PixelFormatInfo` 组成的键值对。
     */
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

    /**convert functions*/

    /**
    Convert the format to the format param you specified, if the format is PixelFormat::Automatic, it will detect it automatically and convert to the closest format for you.
    It will return the converted format to you. if the outData != data, you must delete it manually.
    */
    static PixelFormat convertDataToFormat(const unsigned char* data, ssize_t dataLen, PixelFormat originFormat, PixelFormat format, unsigned char** outData, ssize_t* outDataLen);

    static PixelFormat convertI8ToFormat(const unsigned char* data, ssize_t dataLen, PixelFormat format, unsigned char** outData, ssize_t* outDataLen);
    static PixelFormat convertAI88ToFormat(const unsigned char* data, ssize_t dataLen, PixelFormat format, unsigned char** outData, ssize_t* outDataLen);
    static PixelFormat convertRGB888ToFormat(const unsigned char* data, ssize_t dataLen, PixelFormat format, unsigned char** outData, ssize_t* outDataLen);
    static PixelFormat convertRGBA8888ToFormat(const unsigned char* data, ssize_t dataLen, PixelFormat format, unsigned char** outData, ssize_t* outDataLen);

    //I8 to XXX
    static void convertI8ToRGB888(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertI8ToRGBA8888(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertI8ToRGB565(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertI8ToRGBA4444(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertI8ToRGB5A1(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertI8ToAI88(const unsigned char* data, ssize_t dataLen, unsigned char* outData);

    //AI88 to XXX
    static void convertAI88ToRGB888(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertAI88ToRGBA8888(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertAI88ToRGB565(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertAI88ToRGBA4444(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertAI88ToRGB5A1(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertAI88ToA8(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertAI88ToI8(const unsigned char* data, ssize_t dataLen, unsigned char* outData);

    //RGB888 to XXX
    static void convertRGB888ToRGBA8888(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGB888ToRGB565(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGB888ToI8(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGB888ToAI88(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGB888ToRGBA4444(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGB888ToRGB5A1(const unsigned char* data, ssize_t dataLen, unsigned char* outData);

    //RGBA8888 to XXX
    static void convertRGBA8888ToRGB888(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGBA8888ToRGB565(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGBA8888ToI8(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGBA8888ToA8(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGBA8888ToAI88(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGBA8888ToRGBA4444(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGBA8888ToRGB5A1(const unsigned char* data, ssize_t dataLen, unsigned char* outData);

protected:
    /** pixel format of the texture */
    Texture2D::PixelFormat _pixelFormat;

    /** width in pixels */
    int _pixelsWide;

    /** height in pixels */
    int _pixelsHigh;

    /** texture name */
    GLuint _name;

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

    /** shader program used by drawAtPoint and drawInRect */
    GLProgram* _shaderProgram;

    static const PixelFormatInfoMap _pixelFormatInfoTables;

    bool _antialiasEnabled;
    NinePatchInfo* _ninePatchInfo;
    friend class SpriteFrameCache;
    friend class TextureCache;
    friend class ui::Scale9Sprite;
};


// end of textures group
/// @}

NS_CC_END

#endif //__CCTEXTURE2D_H__

