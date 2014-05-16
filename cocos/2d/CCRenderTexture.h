/****************************************************************************
Copyright (c) 2009      Jason Booth
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
#ifndef __CCRENDER_TEXTURE_H__
#define __CCRENDER_TEXTURE_H__

#include "2d/CCNode.h"
#include "2d/CCSprite.h"
#include "platform/CCImage.h"
#include "renderer/CCGroupCommand.h"
#include "renderer/CCCustomCommand.h"

NS_CC_BEGIN

class EventCustom;

/**
 * @addtogroup textures
 * @{
 */

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
public:
    /** initializes a RenderTexture object with width and height in Points and a pixel format( only RGB and RGBA formats are valid ) and depthStencil format*/
    static RenderTexture * create(int w ,int h, Texture2D::PixelFormat format, GLuint depthStencilFormat);

    /** creates a RenderTexture object with width and height in Points and a pixel format, only RGB and RGBA formats are valid */
    static RenderTexture * create(int w, int h, Texture2D::PixelFormat format);

    /** creates a RenderTexture object with width and height in Points, pixel format is RGBA8888 */
    static RenderTexture * create(int w, int h);

    /** starts grabbing */
    virtual void begin();

    /** starts rendering to the texture while clearing the texture first.
    This is more efficient then calling -clear first and then -begin */
    virtual void beginWithClear(float r, float g, float b, float a);

    /** starts rendering to the texture while clearing the texture first.
     This is more efficient then calling -clear first and then -begin */
    virtual void beginWithClear(float r, float g, float b, float a, float depthValue);

    /** starts rendering to the texture while clearing the texture first.
     This is more efficient then calling -clear first and then -begin */
    virtual void beginWithClear(float r, float g, float b, float a, float depthValue, int stencilValue);

    /** end is key word of lua, use other name to export to lua. */
    inline void endToLua(){ end();};

    /** ends grabbing*/
    virtual void end();

    /** clears the texture with a color */
    void clear(float r, float g, float b, float a);

    /** clears the texture with a specified depth value */
    virtual void clearDepth(float depthValue);

    /** clears the texture with a specified stencil value */
    virtual void clearStencil(int stencilValue);
    /* creates a new Image from with the texture's data.
       Caller is responsible for releasing it by calling delete.
     */
    
    Image* newImage(bool flipImage = true);
    
    CC_DEPRECATED_ATTRIBUTE Image* newCCImage(bool flipImage = true) { return newImage(flipImage); };

    /** saves the texture into a file using JPEG format. The file will be saved in the Documents folder.
        Returns true if the operation is successful.
     */
    bool saveToFile(const std::string& filename);

    /** saves the texture into a file. The format could be JPG or PNG. The file will be saved in the Documents folder.
        Returns true if the operation is successful.
     */
    bool saveToFile(const std::string& filename, Image::Format format);
    
    /** Listen "come to background" message, and save render texture.
     It only has effect on Android.
     */
    void listenToBackground(EventCustom *event);
    
    /** Listen "come to foreground" message and restore the frame buffer object
     It only has effect on Android.
     */
    void listenToForeground(EventCustom *event);
    
    /** Valid flags: GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT. They can be OR'ed. Valid when "autoDraw" is true. */
    inline unsigned int getClearFlags() const { return _clearFlags; };
    inline void setClearFlags(unsigned int clearFlags) { _clearFlags = clearFlags; };
    
    /** Clear color value. Valid only when "autoDraw" is true. */
    inline const Color4F& getClearColor() const { return _clearColor; };
    inline void setClearColor(const Color4F &clearColor) { _clearColor = clearColor; };
    
    /** Value for clearDepth. Valid only when "autoDraw" is true. */
    inline float getClearDepth() const { return _clearDepth; };
    inline void setClearDepth(float clearDepth) { _clearDepth = clearDepth; };
    
    /** Value for clear Stencil. Valid only when "autoDraw" is true */
    inline int getClearStencil() const { return _clearStencil; };
    inline void setClearStencil(int clearStencil) { _clearStencil = clearStencil; };
    
    /** When enabled, it will render its children into the texture automatically. Disabled by default for compatiblity reasons.
     Will be enabled in the future.
     */
    inline bool isAutoDraw() const { return _autoDraw; };
    inline void setAutoDraw(bool isAutoDraw) { _autoDraw = isAutoDraw; };

    /** Gets the Sprite being used. */
    inline Sprite* getSprite() const { return _sprite; };
    
    /** Sets the Sprite being used. */
    inline void setSprite(Sprite* sprite) {
        CC_SAFE_RETAIN(sprite);
        CC_SAFE_RELEASE(_sprite);
        _sprite = sprite;
    };
    
    // Overrides
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, bool parentTransformUpdated) override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;

    //flag: use stack matrix computed from scene hierarchy or generate new modelView and projection matrix
    void setKeepMatrix(bool keepMatrix);
    /**Used for grab part of screen to a texture. 
    //rtBegin: the position of renderTexture on the fullRect
    //fullRect: the total size of screen
    //fullViewport: the total viewportSize
    */
    void setVirtualViewport(const Vec2& rtBegin, const Rect& fullRect, const Rect& fullViewport);

public:
    // XXX should be procted.
    // but due to a bug in PowerVR + Android,
    // the constructor is public again
    RenderTexture();
    virtual ~RenderTexture();
    /** initializes a RenderTexture object with width and height in Points and a pixel format, only RGB and RGBA formats are valid */
    bool initWithWidthAndHeight(int w, int h, Texture2D::PixelFormat format);
    /** initializes a RenderTexture object with width and height in Points and a pixel format( only RGB and RGBA formats are valid ) and depthStencil format*/
    bool initWithWidthAndHeight(int w, int h, Texture2D::PixelFormat format, GLuint depthStencilFormat);

protected:
    virtual void beginWithClear(float r, float g, float b, float a, float depthValue, int stencilValue, GLbitfield flags);
    
    //flags: whether generate new modelView and projection matrix or not
    bool         _keepMatrix;
    Rect         _rtTextureRect;
    Rect         _fullRect;
    Rect         _fullviewPort;
    
    GLuint       _FBO;
    GLuint       _depthRenderBufffer;
    GLint        _oldFBO;
    Texture2D* _texture;
    Texture2D* _textureCopy;    // a copy of _texture
    Image*     _UITextureImage;
    Texture2D::PixelFormat _pixelFormat;
    
    // code for "auto" update
    GLbitfield   _clearFlags;
    Color4F    _clearColor;
    GLclampf     _clearDepth;
    GLint        _clearStencil;
    bool         _autoDraw;

    /** The Sprite being used.
     The sprite, by default, will use the following blending function: GL_ONE, GL_ONE_MINUS_SRC_ALPHA.
     The blending function can be changed in runtime by calling:
     - renderTexture->getSprite()->setBlendFunc((BlendFunc){GL_ONE, GL_ONE_MINUS_SRC_ALPHA});
     */
    Sprite* _sprite;
    
    GroupCommand _groupCommand;
    CustomCommand _beginWithClearCommand;
    CustomCommand _clearDepthCommand;
    CustomCommand _clearCommand;
    CustomCommand _beginCommand;
    CustomCommand _endCommand;
    CustomCommand _saveToFileCommand;
protected:
    //renderer caches and callbacks
    void onBegin();
    void onEnd();

    void onClear();
    void onClearDepth();

    void onSaveToFile(const std::string& fileName);
    
    Mat4 _oldTransMatrix, _oldProjMatrix;
    Mat4 _transformMatrix, _projectionMatrix;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(RenderTexture);

};

// end of textures group
/// @}

NS_CC_END

#endif //__CCRENDER_TEXTURE_H__
