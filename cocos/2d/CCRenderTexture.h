/****************************************************************************
Copyright (c) 2009      Jason Booth
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
#pragma once

#include "2d/CCNode.h"
#include "2d/CCSprite.h"
#include "platform/CCImage.h"
#include "renderer/CCGroupCommand.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCCallbackCommand.h"
#include "renderer/backend/Types.h"

NS_CC_BEGIN

namespace backend
{
    class TextureBackend;
}

class EventCustom;

/**
 * @addtogroup _2d
 * @{
 */

/**
 * @brief RenderTexture is a generic rendering target. To render things into it,
 * simply construct a render target, call begin on it, call visit on any cocos
 * scenes or objects to render them, and call end. For convenience, render texture
 * adds a sprite as it's display child with the results, so you can simply add
 * the render texture to your scene and treat it like any other CocosNode.
 * There are also functions for saving the render texture to disk in PNG or JPG format.
 * @since v0.8.1
 */
class CC_DLL RenderTexture : public Node 
{
public:
    /** Initializes a RenderTexture object with width and height in Points and a pixel format( only RGB and RGBA formats are valid ) and depthStencil format. 
     *
     * @param w The RenderTexture object width.
     * @param h The RenderTexture object height.
     * @param format In Points and a pixel format( only RGB and RGBA formats are valid ).
     * @param depthStencilFormat The depthStencil format.
     */
    static RenderTexture * create(int w ,int h, backend::PixelFormat format, backend::PixelFormat depthStencilFormat);

    /** Creates a RenderTexture object with width and height in Points and a pixel format, only RGB and RGBA formats are valid. 
     *
     * @param w The RenderTexture object width.
     * @param h The RenderTexture object height.
     * @param format In Points and a pixel format( only RGB and RGBA formats are valid ).
     */
    static RenderTexture * create(int w, int h, backend::PixelFormat format);

    /** Creates a RenderTexture object with width and height in Points, pixel format is RGBA8888. 
     *
     * @param w The RenderTexture object width.
     * @param h The RenderTexture object height.
     */
    static RenderTexture * create(int w, int h);

    // Overrides
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
    
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

    /** Starts grabbing. */
    virtual void begin();

    /** Starts rendering to the texture while clearing the texture first.
     * This is more efficient then calling -clear first and then -begin.
     *
     * @param r Red.
     * @param g Green.
     * @param b Blue.
     * @param a Alpha.
     */
    virtual void beginWithClear(float r, float g, float b, float a);

    /** Starts rendering to the texture while clearing the texture first.
     * This is more efficient then calling -clear first and then -begin.
     *
     * @param r Red.
     * @param g Green.
     * @param b Blue.
     * @param a Alpha.
     * @param depthValue The depth Value.
     */
    virtual void beginWithClear(float r, float g, float b, float a, float depthValue);

    /** Starts rendering to the texture while clearing the texture first.
     * This is more efficient then calling -clear first and then -begin. 
     *
     * @param r Red.
     * @param g Green.
     * @param b Blue.
     * @param a Alpha.
     * @param depthValue A specified depth value.
     * @param stencilValue A specified stencil value.
     */
    virtual void beginWithClear(float r, float g, float b, float a, float depthValue, int stencilValue);

    /** Ends grabbing.
     * @lua endToLua
     */
    virtual void end();

    /** Clears the texture with a color. 
     *
     * @param r Red.
     * @param g Green.
     * @param b Blue.
     * @param a Alpha.
     */
    void clear(float r, float g, float b, float a);

    /** Clears the texture with a specified depth value. 
     *
     * @param depthValue A specified depth value.
     */
    virtual void clearDepth(float depthValue);

    /** Clears the texture with a specified stencil value.
     *
     * @param stencilValue A specified stencil value.
     */
    virtual void clearStencil(int stencilValue);
    
    /* Creates a new Image from with the texture's data.
     * Caller is responsible for releasing it by calling delete.
     *
     * @param flipImage Whether or not to flip image.
     * @return An image.
     * @js NA
     */
    void newImage(std::function<void(Image*)> imageCallback, bool flipImage = true);
    
    /** Saves the texture into a file using JPEG format. The file will be saved in the Documents folder.
     * Returns true if the operation is successful.
     *
     * @param filename The file name.
     * @param isRGBA The file is RGBA or not.
     * @param callback When the file is save finished,it will callback this function.
     * @return Returns true if the operation is successful.
     */
    bool saveToFileAsNonPMA(const std::string& filename, bool isRGBA = true, std::function<void(RenderTexture*, const std::string&)> callback = nullptr);

    /** Saves the texture into a file using JPEG format. The file will be saved in the Documents folder.
     * Returns true if the operation is successful.
     *
     * @param filename The file name.
     * @param isRGBA The file is RGBA or not.
     * @param callback When the file is save finished,it will callback this function.
     * @return Returns true if the operation is successful.
     */
    bool saveToFile(const std::string& filename, bool isRGBA = true, std::function<void (RenderTexture*, const std::string&)> callback = nullptr);

   /** saves the texture into a file in non-PMA. The format could be JPG or PNG. The file will be saved in the Documents folder.
        Returns true if the operation is successful.
     * Notes: since v3.x, saveToFile will generate a custom command, which will be called in the following render->render().
     * So if this function is called in a event handler, the actual save file will be called in the next frame. If we switch to a different scene, the game will crash.
     * To solve this, add Director::getInstance()->getRenderer()->render(); after this function.
     *
     * @param filename The file name.
     * @param format The image format.
     * @param isRGBA The file is RGBA or not.
     * @param callback When the file is save finished,it will callback this function.
     * @return Returns true if the operation is successful.
     */
    bool saveToFileAsNonPMA(const std::string& fileName, Image::Format format, bool isRGBA, std::function<void(RenderTexture*, const std::string&)> callback);

    /** saves the texture into a file. The format could be JPG or PNG. The file will be saved in the Documents folder.
        Returns true if the operation is successful.
     * Notes: since v3.x, saveToFile will generate a custom command, which will be called in the following render->render().
     * So if this function is called in a event handler, the actual save file will be called in the next frame. If we switch to a different scene, the game will crash.
     * To solve this, add Director::getInstance()->getRenderer()->render(); after this function.
     *
     * @param filename The file name.
     * @param format The image format.
     * @param isRGBA The file is RGBA or not.
     * @param callback When the file is save finished,it will callback this function.
     * @return Returns true if the operation is successful.
     */
    bool saveToFile(const std::string& filename, Image::Format format, bool isRGBA = true, std::function<void (RenderTexture*, const std::string&)> callback = nullptr);
    
    /** Listen "come to background" message, and save render texture.
     * It only has effect on Android.
     * 
     * @param event Event Custom.
     */
    void listenToBackground(EventCustom *event);
    
    /** Listen "come to foreground" message and restore the frame buffer object.
     * It only has effect on Android.
     *
     * @param event Event Custom.
     */
    void listenToForeground(EventCustom *event);

    /** Valid when "autoDraw" is true.
     *
     * @return Clear flags.
     */
    inline ClearFlag getClearFlags() const { return _clearFlags; }

    /** Set flags.
     *
     * @param clearFlags set clear flags.
     */
    void setClearFlags(ClearFlag clearFlags);
    
    /** Clear color value. Valid only when "autoDraw" is true. 
     *
     * @return Color value.
     */
    inline const Color4F& getClearColor() const { return _clearColor; }
    
    /** Set color value. 
     *
     * @param clearColor Color value.
     */
    inline void setClearColor(const Color4F &clearColor) { _clearColor = clearColor; }
    
    /** Value for clearDepth. Valid only when "autoDraw" is true. 
     *
     * @return Value for clearDepth.
     */
    inline float getClearDepth() const { return _clearDepth; }
    
    /** Set Value for clearDepth.
     *
     * @param clearDepth Value for clearDepth.
     */
    inline void setClearDepth(float clearDepth) { _clearDepth = clearDepth; }
    
    /** Value for clear Stencil. Valid only when "autoDraw" is true.
     *
     * @return Value for clear Stencil.
     */
    inline int getClearStencil() const { return _clearStencil; }
    
    /** Set Value for clear Stencil.
     *
     * @param clearStencil Value for clear Stencil.
     */
    inline void setClearStencil(int clearStencil) { _clearStencil = clearStencil; }
    
    /** When enabled, it will render its children into the texture automatically. Disabled by default for compatibility reasons.
     * Will be enabled in the future.
     *
     * @return Return the autoDraw value.
     */
    inline bool isAutoDraw() const { return _autoDraw; }
    
    /** Set a valve to control whether or not render its children into the texture automatically. 
     *
     * @param isAutoDraw Whether or not render its children into the texture automatically.
     */
    inline void setAutoDraw(bool isAutoDraw) { _autoDraw = isAutoDraw; }

    /** Gets the Sprite being used. 
     *
     * @return A Sprite.
     */
    inline Sprite* getSprite() const { return _sprite; }
    
    /** Sets the Sprite being used. 
     *
     * @param sprite A Sprite.
     */
    void setSprite(Sprite* sprite);

    /** Flag: Use stack matrix computed from scene hierarchy or generate new modelView and projection matrix.
     *
     * @param keepMatrix Whether or not use stack matrix computed from scene hierarchy or generate new modelView and projection matrix.
     * @js NA
     */
    inline void setKeepMatrix(bool keepMatrix) { _keepMatrix = keepMatrix; }
    /**Used for grab part of screen to a texture. 
     * @param rtBegin The position of renderTexture on the fullRect.
     * @param fullRect The total size of screen.
     * @param fullViewport The total viewportSize.
     */
    void setVirtualViewport(const Vec2& rtBegin, const Rect& fullRect, const Rect& fullViewport);

public:
    /** FIXME: should be protected.
     * but due to a bug in PowerVR + Android,
     * the constructor is public again.
     * @js ctor
     */
    RenderTexture();

    /**
     * @js NA
	 * @lua NA
     */
    virtual ~RenderTexture();
    /** Initializes a RenderTexture object with width and height in Points and a pixel format, only RGB and RGBA formats are valid.
     *
     * @param w The RenderTexture object width.
     * @param h The RenderTexture object height.
     * @param format In Points and a pixel format( only RGB and RGBA formats are valid ).
     * @return If succeed, it will return true.
     */
    bool initWithWidthAndHeight(int w, int h, backend::PixelFormat format);
    /** Initializes a RenderTexture object with width and height in Points and a pixel format( only RGB and RGBA formats are valid ) and depthStencil format. 
     *
     * @param w The RenderTexture object width.
     * @param h The RenderTexture object height.
     * @param format In Points and a pixel format( only RGB and RGBA formats are valid ).
     * @param depthStencilFormat The depthStencil format.
     * @return If succeed, it will return true.
     */
    bool initWithWidthAndHeight(int w, int h, backend::PixelFormat format, backend::PixelFormat depthStencilFormat);

protected:
    virtual void beginWithClear(float r, float g, float b, float a, float depthValue, int stencilValue, ClearFlag flags);
    //renderer caches and callbacks
    void onBegin();
    void onEnd();
    void clearColorAttachment();

    void onSaveToFile(const std::string& fileName, bool isRGBA = true, bool forceNonPMA = false);

    bool         _keepMatrix = false;
    Rect         _rtTextureRect;
    Rect         _fullRect;
    Rect         _fullviewPort;

    Viewport     _oldViewport;
    
    Texture2D* _texture2D = nullptr;
    Texture2D* _depthStencilTexture = nullptr;
    Texture2D* _texture2DCopy = nullptr;    // a copy of _texture
    Texture2D* _oldColorAttachment = nullptr;
    Texture2D* _oldDepthAttachment = nullptr;
    Texture2D* _oldStencilAttachment = nullptr;
    RenderTargetFlag _renderTargetFlags;
    RenderTargetFlag _oldRenderTargetFlag;
    Image*     _UITextureImage = nullptr;
    backend::PixelFormat _pixelFormat = backend::PixelFormat::RGBA8888;
    
    Color4F _clearColor;
    float _clearDepth = 1.f;
    int _clearStencil = 0;
    bool _autoDraw = false;
    ClearFlag _clearFlags = ClearFlag::NONE;

    /** The Sprite being used.
     The sprite, by default, will use the following blending function: BlendFactor::ONE, BlendFactor::ONE_MINUS_SRC_ALPHA.
     The blending function can be changed in runtime by calling:
     - renderTexture->getSprite()->setBlendFunc((BlendFunc){BlendFactor::ONE, BlendFactor::ONE_MINUS_SRC_ALPHA});
     */
    Sprite* _sprite = nullptr;
    
    GroupCommand _groupCommand;
    CallbackCommand _beginCommand;
    CallbackCommand _endCommand;

    CallbackCommand _beforeClearAttachmentCommand;
    CallbackCommand _afterClearAttachmentCommand;
    /*this command is used to encapsulate saveToFile,
     call saveToFile twice will overwrite this command and callback
     and the command and callback will be executed twice.
    */
    CallbackCommand _saveToFileCommand;
    std::function<void (RenderTexture*, const std::string&)> _saveFileCallback = nullptr;
    
    Mat4 _oldTransMatrix, _oldProjMatrix;
    Mat4 _transformMatrix, _projectionMatrix;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(RenderTexture);
};

// end of textures group
/// @}

NS_CC_END
