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
 * @addtogroup _2d
 * @{
 */

/**
 * @brief @~english RenderTexture is a generic rendering target. To render things into it,
 * simply construct a render target, call begin on it, call visit on any cocos
 * scenes or objects to render them, and call end. For convenience, render texture
 * adds a sprite as it's display child with the results, so you can simply add
 * the render texture to your scene and treat it like any other Node.
 * There are also functions for saving the render texture to disk in PNG or JPG format.
 * @~chinese RenderTexture是一个通用的渲染节点。要在其中进行渲染，只需简单的构造一个 RenderTexture 对象，
 * 然后调用 begin 方法，再调用需要渲染的场景或对象，最终调用 end 方法即可。
 * 为了方便起见，RenderTexture 添加了一个 Sprite 作为显示结果的节点，你可以将这个 Sprite 做为一个 Node 添加
 * 到任何场景中进行渲染与显示。
 * 此外，还可以通过接口将渲染的结果保存为 PNG 或 JPG 格式文件。
 * @since v0.8.1
 */
class CC_DLL RenderTexture : public Node 
{
public:
    /** @~english Initializes a RenderTexture object with width and height in Points and a pixel format( only RGB and RGBA formats are valid ) and depthStencil format. 
     *
     * @~chinese 使用指定的宽度，高度，像素格式和深度模板格式初始化一个RenderTexture对象。
     * 
     * @param w @~english The RenderTexture object width.
     * @~chinese RenderTexture对象的宽度。
     * @param h @~english The RenderTexture object height.
     * @~chinese RenderTexture对象的高度。
     * @param format @~english In Points and a pixel format( only RGB and RGBA formats are valid ).
     * @~chinese 像素格式(只有RGB和RGBA格式可用)。
     * @param depthStencilFormat @~english The depthStencil format.
     * @~chinese 深度模板格式。
     */
    static RenderTexture * create(int w ,int h, Texture2D::PixelFormat format, GLuint depthStencilFormat);

    /** @~english Creates a RenderTexture object with width and height in Points and a pixel format, only RGB and RGBA formats are valid. 
     *
     * @~chinese 使用指定的宽度，高度，像素格式初始化一个RenderTexture对象。（只有RGB和RGBA格式可用。）
     * 
     * @param w @~english The RenderTexture object width.
     * @~chinese RenderTexture对象的宽度。
     * @param h @~english The RenderTexture object height.
     * @~chinese RenderTexture对象的高度。
     * @param format @~english In Points and a pixel format( only RGB and RGBA formats are valid ).
     * @~chinese 像素格式(只有RGB和RGBA格式可用)。
     */
    static RenderTexture * create(int w, int h, Texture2D::PixelFormat format);

    /** @~english Creates a RenderTexture object with width and height in Points, pixel format is RGBA8888. 
     *
     * @~chinese 指定宽度，高度初始化一个RenderTexture对象。（像素格式是RGBA8888。）
     * 
     * @param w @~english The RenderTexture object width.
     * @~chinese RenderTexture对象的宽度。
     * @param h @~english The RenderTexture object height.
     * @~chinese RenderTexture对象的高度。
     */
    static RenderTexture * create(int w, int h);

    /** @~english Starts grabbing.  @~chinese 开始渲染。*/
    virtual void begin();

    /** @~english Starts rendering to the texture while clearing the texture first.
     * This is more efficient than calling -clear first and then -begin.
     *
     * @~chinese 使用指定的颜色清理纹理并开始渲染。
     * 这个函数实现比先调用 clear 再调用 begin 更高效。
     * 
     * @param r @~english Red.
     * @~chinese 红色分量值。
     * @param g @~english Green.
     * @~chinese 绿色分量值。
     * @param b @~english Blue.
     * @~chinese 蓝色分量值。
     * @param a @~english Alpha.
     * @~chinese 透明度。
     */
    virtual void beginWithClear(float r, float g, float b, float a);

    /** @~english Starts rendering to the texture while clearing the texture first.
     * This is more efficient than calling -clear first and then -begin.
     *
     * @~chinese 使用指定的颜色与深度清理纹理，并开始渲染。
     * 这个函数实现比先调用 clear 再调用 begin 更高效。
     * 
     * @param r @~english Red.
     * @~chinese 红色分量值。
     * @param g @~english Green.
     * @~chinese 绿色分量值。
     * @param b @~english Blue.
     * @~chinese 蓝色分量值。
     * @param a @~english Alpha.
     * @~chinese 透明度。
     * @param depthValue @~english The depth Value.
     * @~chinese 深度值。
     */
    virtual void beginWithClear(float r, float g, float b, float a, float depthValue);

    /** @~english Starts rendering to the texture while clearing the texture first.
     * This is more efficient then calling -clear first and then -begin. 
     *
     * @~chinese 使用指定的颜色，深度以及模板清理纹理，并开始渲染。
     * 这个函数实现比先调用 clear 再调用 begin 更高效。
     * 
     * @param r @~english Red.
     * @~chinese 红色分量值。
     * @param g @~english Green.
     * @~chinese 绿色分量值。
     * @param b @~english Blue.
     * @~chinese 蓝色分量值。
     * @param a @~english Alpha.
     * @~chinese 透明度。
     * @param depthValue @~english The depth Value.
     * @~chinese 深度值。
     * @param stencilValue @~english A specified stencil value.
     * @~chinese 指定的模板。
     */
    virtual void beginWithClear(float r, float g, float b, float a, float depthValue, int stencilValue);

    /** @~english End is key word of lua, use other name to export to lua.
     * @~chinese 因为 end 是 lua 中的关键字，此接口是为 lua binding 增加的。
     * @js NA
     */
    inline void endToLua(){ end();};

    /** @~english Ends grabbing.  @~chinese 结束渲染。*/
    virtual void end();

    /** @~english Clears the texture with a color. 
     *
     * @~chinese 使用指定的颜色清除纹理。
     * 
     * @param r @~english Red.
     * @~chinese 红色分量值。
     * @param g @~english Green.
     * @~chinese 绿色分量值。
     * @param b @~english Blue.
     * @~chinese 蓝色分量值。
     * @param a @~english Alpha.
     * @~chinese 透明度。
     */
    void clear(float r, float g, float b, float a);

    /** @~english Clears the texture with a specified depth value. 
     *
     * @~chinese 使用指定的深度清除深度缓存。
     * 
     * @param depthValue @~english A specified depth value.
     * @~chinese 一个指定的深度值。
     */
    virtual void clearDepth(float depthValue);

    /** @~english Clears the texture with a specified stencil value.
     *
     * @~chinese 使用指定的值清除模板缓存。
     * 
     * @param stencilValue @~english A specified stencil value.
     * @~chinese 指定的模板。
     */
    virtual void clearStencil(int stencilValue);
    
    /* @~english Creates a new Image from with the texture's data.
     * Caller is responsible for releasing it by calling delete.
     *
     * @~chinese 从纹理数据生成一个 Image 实例。
     * 使用这个函数需要负责销毁该 Image 实例。
     * 
     * @param flipImage @~english Whether or not to flip image.
     * @~chinese 是否翻转图像。
     * @return @~english An image.
     * @~chinese 一个 Image 实例。
     * @js NA
     */
    Image* newImage(bool flipImage = true);
    
    CC_DEPRECATED_ATTRIBUTE Image* newCCImage(bool flipImage = true) { return newImage(flipImage); };

    /** @~english Saves the texture into a file using JPEG format. The file will be saved in the Documents folder.
     * Returns true if the operation is successful.
     *
     * @~chinese 将纹理保存为JPEG格式文件。该文件将被保存在“文档”文件夹。
     * 如果操作成功返回true。
     * 
     * @param filename @~english The file name.
     * @~chinese 文件的名字。
     * @param isRGBA @~english The file is RGBA or not.
     * @~chinese 该文件是否为RGBA格式。
     * @param callback @~english When the file is save finished,it will callback this function.
     * @~chinese 当文件保存成功后需要调用的回调函数。
     * @return @~english Returns true if the operation is successful.
     * @~chinese 如果操作成功返回true。
     */
    bool saveToFile(const std::string& filename, bool isRGBA = true, std::function<void (RenderTexture*, const std::string&)> callback = nullptr);

    /** @~english saves the texture into a file. The format could be JPG or PNG. The file will be saved in the Documents folder.
        Returns true if the operation is successful.
     * Notes: since v3.x, saveToFile will generate a custom command, which will be called in the following render->render().
     * So if this function is called in a event handler, the actual save file will be called in the next frame. If we switch to a different scene, the game will crash.
     * To solve this, add Director::getInstance()->getRenderer()->render(); after this function.
     *
     * @~chinese 保存纹理到一个文件中。可能是JPG或PNG格式。该文件将被保存在“文档”文件夹。
     * 如果操作成功返回true。
     * 注:因为v3.x，saveToFile将生成一个自定义命令，该命令将在 render->render() 中被调用。
     * 因此，如果在一个事件处理程序中，调用这个函数保存的文件在下一帧被使用。这时我们切换到一个不同的场景，游戏会崩溃。
     * 为了解决这个问题，在这个函数执行完之后调用一次 Director::getInstance()->getRenderer()->render()。
     * 
     * @param filename @~english The file name.
     * @~chinese 文件的名字。
     * @param format @~english The image format.
     * @~chinese 图像格式。
     * @param isRGBA @~english The file is RGBA or not.
     * @~chinese 是否为 RGBA 格式。
     * @param callback @~english When the file is save finished,it will callback this function.
     * @~chinese 当文件保存完成后的回调函数。
     * @return @~english Returns true if the operation is successful.
     * @~chinese 如果操作成功返回true。
     */
    bool saveToFile(const std::string& filename, Image::Format format, bool isRGBA = true, std::function<void (RenderTexture*, const std::string&)> callback = nullptr);
    
    /** @~english Listen "come to background" message, and save render texture.
     * It only has effect on Android.
     * 
     * @~chinese 监听退到后台的消息，并保存渲染纹理。
     * 它只在Android上有效果。
     * 
     * @param event @~english Event Custom.
     * @~chinese 自定义事件。
     */
    void listenToBackground(EventCustom *event);
    
    /** @~english Listen "come to foreground" message and restore the frame buffer object.
     * It only has effect on Android.
     *
     * @~chinese 监听回到前台的消息，并恢复帧缓冲区对象。
     * 它只在Android上有效果。
     * 
     * @param event @~english Event Custom.
     * @~chinese 自定义事件。
     */
    void listenToForeground(EventCustom *event);
    
    /** @~english Valid flags: GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT. They can be OR'ed. Valid when "autoDraw" is true. 
     *
     * @~chinese 有效的标志:GL_COLOR_BUFFER_BIT GL_DEPTH_BUFFER_BIT GL_STENCIL_BUFFER_BIT。他们可以使用“或”操作来组合标记。当“autoDraw”为 true 时起效。
     * 
     * @return @~english Clear flags.
     * @~chinese 清除所使用的 GL 标志。
     */
    inline unsigned int getClearFlags() const { return _clearFlags; };
    
    /** @~english Set flags.
     *
     * @~chinese 设置标志。
     * 
     * @param clearFlags @~english Valid flags: GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT.
     * @~chinese 有效的标志:GL_COLOR_BUFFER_BIT GL_DEPTH_BUFFER_BIT GL_STENCIL_BUFFER_BIT。
     */
    inline void setClearFlags(unsigned int clearFlags) { _clearFlags = clearFlags; };
    
    /** @~english Clear color value. Valid only when "autoDraw" is true. 
     *
     * @~chinese 清除所使用的颜色值。只有当“autoDraw”为 true 时起效。
     * 
     * @return @~english Color value.
     * @~chinese 颜色值。
     */
    inline const Color4F& getClearColor() const { return _clearColor; };
    
    /** @~english Set color value. 
     *
     * @~chinese 设置清除所使用的颜色值。
     * 
     * @param clearColor @~english Color value.
     * @~chinese 颜色值。
     */
    inline void setClearColor(const Color4F &clearColor) { _clearColor = clearColor; };
    
    /** @~english Value for clearDepth. Valid only when "autoDraw" is true. 
     *
     * @~chinese 清除所使用的深度值。只有当“autoDraw”为 true 时起效。
     * 
     * @return @~english Value for clearDepth.
     * @~chinese 使用的深度值。
     */
    inline float getClearDepth() const { return _clearDepth; };
    
    /** @~english Set Value for clearDepth.
     *
     * @~chinese 设置清除所使用的深度值。
     * 
     * @param clearDepth @~english Value for clearDepth.
     * @~chinese 使用的深度值。
     */
    inline void setClearDepth(float clearDepth) { _clearDepth = clearDepth; };
    
    /** @~english Value for clear Stencil. Valid only when "autoDraw" is true.
     *
     * @~chinese 获取清除所使用的模板。只有当“autoDraw”为 true 时起效。
     * 
     * @return @~english Value for clear Stencil.
     * @~chinese 使用的模板
     */
    inline int getClearStencil() const { return _clearStencil; };
    
    /** @~english Set Value for clear Stencil.
     *
     * @~chinese 设置清除所使用的模板。
     * 
     * @param clearStencil @~english Value for clear Stencil.
     * @~chinese 使用的模板
     */
    inline void setClearStencil(int clearStencil) { _clearStencil = clearStencil; };
    
    /** @~english When enabled, it will render its children into the texture automatically. Disabled by default for compatiblity reasons.
     * Will be enabled in the future.
     *
     * @~chinese 当启用时，它将自动渲染子节点。出于兼容性的考虑，默认值为关闭。
     * 在未来将会启用。
     * 
     * @return @~english Return the autoDraw value.
     * @~chinese 返回是否自动渲染。
     */
    inline bool isAutoDraw() const { return _autoDraw; };
    
    /** @~english Set a valve to control whether or not render its children into the texture automatically. 
     *
     * @~chinese 设置是否自动渲染子节点。
     * 
     * @param isAutoDraw @~english Whether or not render its children into the texture automatically.
     * @~chinese 是否自动渲染子节点。
     */
    inline void setAutoDraw(bool isAutoDraw) { _autoDraw = isAutoDraw; };

    /** @~english Gets the Sprite being used. 
     *
     * @~chinese 正在使用的 Sprite。
     * 
     * @return @~english A Sprite.
     * @~chinese Sprite 实例。
     */
    inline Sprite* getSprite() const { return _sprite; };
    
    /** @~english Sets the Sprite being used. 
     *
     * @~chinese 设置使用的 Sprite。
     * 
     * @param sprite @~english A Sprite.
     * @~chinese Sprite 实例。
     */
    inline void setSprite(Sprite* sprite) {
        CC_SAFE_RETAIN(sprite);
        CC_SAFE_RELEASE(_sprite);
        _sprite = sprite;
    };
    
    // Overrides
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

    /** @~english Flag: Use stack matrix computed from scene hierarchy or generate new modelView and projection matrix.
     *
     * @~chinese 标志：使用从场景中计算的堆栈矩阵或生成新的视点矩阵和投影矩阵。
     * 
     * @param keepMatrix @~english Wether or not use stack matrix computed from scene hierarchy or generate new modelView and projection matrix.
     * @~chinese 是否使用从场景中计算的堆栈矩阵或生成新的视点矩阵和投影矩阵。
     * @js NA
     */
    void setKeepMatrix(bool keepMatrix);
    /**@~english Used for grab part of screen to a texture. 
     * @~chinese 用于截取屏幕纹理的一部分。
     * @param rtBegin @~english The position of renderTexture on the fullRect.
     * @~chinese 需要截取的起点位置。
     * @param fullRect @~english The total size of screen.
     * @~chinese 需要截取的矩形区域大小。
     * @param fullViewport @~english The total viewportSize.
     * @~chinese 视窗大小。
     */
    void setVirtualViewport(const Vec2& rtBegin, const Rect& fullRect, const Rect& fullViewport);

public:
    /** @~english FIXME: should be procted.
     * but due to a bug in PowerVR + Android,
     * the constructor is public again.
     * @~chinese 应该为 protected。
     * 但由于在 PowerVR + 安卓环境的 bug，
     * 所以构造函数还是 public。
     * @js ctor
     */
    RenderTexture();

    /**
     * @js NA
	 * @lua NA
     */
    virtual ~RenderTexture();
    /** @~english Initializes a RenderTexture object with width and height in Points and a pixel format, only RGB and RGBA formats are valid.
     *
     * @~chinese 使用指定的宽度，高度和像素格式初始化一个RenderTexture对象，（只有RGB和RGBA格式可用。）
     * 
     * @param w @~english The RenderTexture object width.
     * @~chinese RenderTexture对象的宽度。
     * @param h @~english The RenderTexture object height.
     * @~chinese RenderTexture对象的高度。
     * @param format @~english In Points and a pixel format( only RGB and RGBA formats are valid ).
     * @~chinese 像素格式(只有RGB和RGBA格式可用)。
     * @return @~english If successed,it will return true.
     * @~chinese 如果成功,它将返回true。
     */
    bool initWithWidthAndHeight(int w, int h, Texture2D::PixelFormat format);
    /** @~english Initializes a RenderTexture object with width and height in Points and a pixel format( only RGB and RGBA formats are valid ) and depthStencil format. 
     *
     * @~chinese 使用指定的宽度，高度，像素格式和深度模板格式初始化一个RenderTexture对象。
     * 
     * @param w @~english The RenderTexture object width.
     * @~chinese RenderTexture对象的宽度。
     * @param h @~english The RenderTexture object height.
     * @~chinese RenderTexture对象的高度。
     * @param format @~english In Points and a pixel format( only RGB and RGBA formats are valid ).
     * @~chinese 像素格式(只有RGB和RGBA格式可用)。
     * @param depthStencilFormat @~english The depthStencil format.
     * @~chinese 深度模板格式。
     * @return @~english If successed,it will return true.
     * @~chinese 如果成功,它将返回true。
     */
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

    Sprite* _sprite;
    
    GroupCommand _groupCommand;
    CustomCommand _beginWithClearCommand;
    CustomCommand _clearDepthCommand;
    CustomCommand _clearCommand;
    CustomCommand _beginCommand;
    CustomCommand _endCommand;
    CustomCommand _saveToFileCommand;
    std::function<void (RenderTexture*, const std::string&)> _saveFileCallback;
protected:
    //renderer caches and callbacks
    void onBegin();
    void onEnd();

    void onClear();
    void onClearDepth();

    void onSaveToFile(const std::string& fileName, bool isRGBA = true);
    
    Mat4 _oldTransMatrix, _oldProjMatrix;
    Mat4 _transformMatrix, _projectionMatrix;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(RenderTexture);

};

// end of textures group
/// @}

NS_CC_END

#endif //__CCRENDER_TEXTURE_H__
