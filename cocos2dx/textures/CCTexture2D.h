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
#include "cocoa/CCObject.h"
#include "cocoa/CCGeometry.h"
#include "ccTypes.h"
#ifdef EMSCRIPTEN
#include "base_nodes/CCGLBufferedNode.h"
#endif // EMSCRIPTEN

NS_CC_BEGIN

class Image;

/**
 * @addtogroup textures
 * @{
 */

//CONSTANTS:

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
    /** @typedef Texture2D::PixelFormat
     Possible texture pixel formats
     */
    enum class PixelFormat
    {
        
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
        PRVTC4,
        //! 2-bit PVRTC-compressed texture: PVRTC2
        PRVTC2,

        //! Default texture format: RGBA8888
        DEFAULT = RGBA8888
    };
    
    /** sets the default pixel format for UIImagescontains alpha channel.
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

    /** returns the alpha pixel format
     @since v0.8
     */
    static Texture2D::PixelFormat getDefaultAlphaPixelFormat();
    CC_DEPRECATED_ATTRIBUTE static Texture2D::PixelFormat defaultAlphaPixelFormat() { return Texture2D::getDefaultAlphaPixelFormat(); };

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
    bool initWithData(const void* data, Texture2D::PixelFormat pixelFormat, unsigned int pixelsWide, unsigned int pixelsHigh, const Size& contentSize);

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
    Note that RGBA type textures will have their alpha premultiplied - use the blending mode (GL_ONE, GL_ONE_MINUS_SRC_ALPHA).
    */
    /** Initializes a texture from a UIImage object */

    bool initWithImage(Image * uiImage);

    /** Initializes a texture from a string with dimensions, alignment, font name and font size */
    bool initWithString(const char *text,  const char *fontName, float fontSize, const Size& dimensions = Size(0, 0), Label::HAlignment hAlignment = Label::HAlignment::CENTER, Label::VAlignment vAlignment = Label::VAlignment::TOP);
    /** Initializes a texture from a string using a text definition*/
    bool initWithString(const char *text, const FontDefinition& textDefinition);
    
    /** Initializes a texture from a PVR file */
    bool initWithPVRFile(const char* file);
    
    /** Initializes a texture from a ETC file */
    bool initWithETCFile(const char* file);

    /** sets the min filter, mag filter, wrap s and wrap t texture parameters.
    If the texture size is NPOT (non power of 2), then in can only use GL_CLAMP_TO_EDGE in GL_TEXTURE_WRAP_{S,T}.

    @warning Calling this method could allocate additional texture memory.

    @since v0.8
    */
    void setTexParameters(const ccTexParams& texParams);
    CC_DEPRECATED_ATTRIBUTE void setTexParameters(const ccTexParams* texParams) { return setTexParameters(*texParams); };

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
    const char* getStringForFormat() const;
    CC_DEPRECATED_ATTRIBUTE const char* stringForFormat() const { return getStringForFormat(); };

    /** returns the bits-per-pixel of the in-memory OpenGL texture
    @since v1.0
    */
    unsigned int getBitsPerPixelForFormat() const;
    CC_DEPRECATED_ATTRIBUTE unsigned int bitsPerPixelForFormat() const { return getBitsPerPixelForFormat(); };

    /** Helper functions that returns bits per pixels for a given format.
     @since v2.0
     */
    unsigned int getBitsPerPixelForFormat(Texture2D::PixelFormat format) const;
    CC_DEPRECATED_ATTRIBUTE unsigned int bitsPerPixelForFormat(Texture2D::PixelFormat format) const { return getBitsPerPixelForFormat(format); };

    /** content size */
    const Size& getContentSizeInPixels();

    bool hasPremultipliedAlpha() const;
    bool hasMipmaps() const;

    /** Gets the pixel format of the texture */
    Texture2D::PixelFormat getPixelFormat() const;
    
    /** Gets the width of the texture in pixels */
    unsigned int getPixelsWide() const;
    
    /** Gets the height of the texture in pixels */
    unsigned int getPixelsHigh() const;
    
    /** Gets the texture name */
    GLuint getName() const;
    
    /** Gets max S */
    GLfloat getMaxS() const;
    /** Sets max S */
    void setMaxS(GLfloat maxS);
    
    /** Gets max T */
    GLfloat getMaxT() const;
    /** Sets max T */
    void setMaxT(GLfloat maxT);
    
    Size getContentSize() const;
    
    void setShaderProgram(GLProgram* program);
    GLProgram* getShaderProgram() const;
    
private:
    bool initPremultipliedATextureWithImage(Image * image, unsigned int pixelsWide, unsigned int pixelsHigh);

protected:
    /** pixel format of the texture */
    Texture2D::PixelFormat _pixelFormat;

    /** width in pixels */
    unsigned int _pixelsWide;

    /** height in pixels */
    unsigned int _pixelsHigh;

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

    bool _hasMipmaps;

    /** shader program used by drawAtPoint and drawInRect */
    GLProgram* _shaderProgram;
};

// end of textures group
/// @}

NS_CC_END

#endif //__CCTEXTURE2D_H__

