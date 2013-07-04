/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2009      Jason Booth

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
#ifndef __CCRENDER_TEXTURE_H__
#define __CCRENDER_TEXTURE_H__

#include "base_nodes/CCNode.h"
#include "sprite_nodes/CCSprite.h"
#include "kazmath/mat4.h"

NS_CC_BEGIN

/**
 * @addtogroup textures
 * @{
 */

typedef enum eImageFormat
{
    kImageFormatJPEG      = 0,
    kImageFormatPNG       = 1,
} tImageFormat;
/**
@brief RenderTexture is a generic rendering target. To render things into it,
simply construct a render target, call begin on it, call visit on any cocos
scenes or objects to render them, and call end. For convenience, render texture
adds a sprite as it's display child with the results, so you can simply add
the render texture to your scene and treat it like any other CocosNode.
There are also functions for saving the render texture to disk in PNG or JPG format.

@since v0.8.1
*/
class CC_DLL RenderTexture : public Node 
{
    /** The Sprite being used.
    The sprite, by default, will use the following blending function: GL_ONE, GL_ONE_MINUS_SRC_ALPHA.
    The blending function can be changed in runtime by calling:
    - [[renderTexture sprite] setBlendFunc:(ccBlendFunc){GL_ONE, GL_ONE_MINUS_SRC_ALPHA}];
    */
    CC_PROPERTY(Sprite*, _sprite, Sprite)
public:
    RenderTexture();
    virtual ~RenderTexture();
    
    virtual void visit();
    virtual void draw();

    /** initializes a RenderTexture object with width and height in Points and a pixel format( only RGB and RGBA formats are valid ) and depthStencil format*/
    static RenderTexture * create(int w ,int h, Texture2DPixelFormat eFormat, GLuint uDepthStencilFormat);

    /** creates a RenderTexture object with width and height in Points and a pixel format, only RGB and RGBA formats are valid */
    static RenderTexture * create(int w, int h, Texture2DPixelFormat eFormat);

    /** creates a RenderTexture object with width and height in Points, pixel format is RGBA8888 */
    static RenderTexture * create(int w, int h);

    /** initializes a RenderTexture object with width and height in Points and a pixel format, only RGB and RGBA formats are valid */
    bool initWithWidthAndHeight(int w, int h, Texture2DPixelFormat eFormat);

    /** initializes a RenderTexture object with width and height in Points and a pixel format( only RGB and RGBA formats are valid ) and depthStencil format*/
    bool initWithWidthAndHeight(int w, int h, Texture2DPixelFormat eFormat, GLuint uDepthStencilFormat);

    /** starts grabbing */
    void begin();

    /** starts rendering to the texture while clearing the texture first.
    This is more efficient then calling -clear first and then -begin */
    void beginWithClear(float r, float g, float b, float a);

    /** starts rendering to the texture while clearing the texture first.
     This is more efficient then calling -clear first and then -begin */
    void beginWithClear(float r, float g, float b, float a, float depthValue);

    /** starts rendering to the texture while clearing the texture first.
     This is more efficient then calling -clear first and then -begin */
    void beginWithClear(float r, float g, float b, float a, float depthValue, int stencilValue);

    /** end is key word of lua, use other name to export to lua. */
    inline void endToLua(){ end();};

    /** ends grabbing*/
    void end();

    /** clears the texture with a color */
    void clear(float r, float g, float b, float a);

    /** clears the texture with a specified depth value */
    void clearDepth(float depthValue);

    /** clears the texture with a specified stencil value */
    void clearStencil(int stencilValue);
    /* creates a new Image from with the texture's data.
       Caller is responsible for releasing it by calling delete.
     */
    Image* newImage(bool flipImage = true);

    /** saves the texture into a file using JPEG format. The file will be saved in the Documents folder.
        Returns YES if the operation is successful.
     */
    bool saveToFile(const char *szFilePath);

    /** saves the texture into a file. The format could be JPG or PNG. The file will be saved in the Documents folder.
        Returns YES if the operation is successful.
     */
    bool saveToFile(const char *name, tImageFormat format);
    
    /** Listen "come to background" message, and save render texture.
     It only has effect on Android.
     */
    void listenToBackground(Object *obj);
    
    /** Listen "come to foreground" message and restore the frame buffer object
     It only has effect on Android.
     */
    void listenToForeground(Object *obj);
    
    /** Valid flags: GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT. They can be OR'ed. Valid when "autoDraw is YES. */
    unsigned int getClearFlags() const;
    void setClearFlags(unsigned int uClearFlags);
    
    /** Clear color value. Valid only when "autoDraw" is true. */
    const ccColor4F& getClearColor() const;
    void setClearColor(const ccColor4F &clearColor);
    
    /** Value for clearDepth. Valid only when autoDraw is true. */
    float getClearDepth() const;
    void setClearDepth(float fClearDepth);
    
    /** Value for clear Stencil. Valid only when autoDraw is true */
    int getClearStencil() const;
    void setClearStencil(float fClearStencil);
    
    /** When enabled, it will render its children into the texture automatically. Disabled by default for compatiblity reasons.
     Will be enabled in the future.
     */
    bool isAutoDraw() const;
    void setAutoDraw(bool bAutoDraw);

private:
    void beginWithClear(float r, float g, float b, float a, float depthValue, int stencilValue, GLbitfield flags);

protected:
    GLuint       _FBO;
    GLuint       _depthRenderBufffer;
    GLint        _oldFBO;
    Texture2D* _texture;
    Texture2D* _textureCopy;    // a copy of _texture
    Image*     _UITextureImage;
    GLenum       _pixelFormat;
    
    // code for "auto" update
    GLbitfield   _clearFlags;
    ccColor4F    _clearColor;
    GLclampf     _clearDepth;
    GLint        _clearStencil;
    bool         _autoDraw;
};

// end of textures group
/// @}

NS_CC_END

#endif //__CCRENDER_TEXTURE_H__
