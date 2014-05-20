/****************************************************************************
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

#ifndef __UIBUTTON_H__
#define __UIBUTTON_H__

#include "ui/UIWidget.h"

NS_CC_BEGIN

namespace ui{

/**
*   @js NA
*   @lua NA
*/
class Button : public Widget
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
     * 默认构造函数（constructor）
     */
    Button();

    /**
     * 默认析构函数（destructor）
     */
    virtual ~Button();

    /**
     * 分配并初始化
     */
    static Button* create();
    
    /**
     * 使用自定义纹理贴图（textures）创建一个按钮
     * @normalImage    正常状态的纹理贴图（texture）名
     * @selectedImage  选中状态的纹理贴图（texture）名
     * @disableImage   禁用状态的纹理贴图（texture）名
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    static Button* create(const std::string& normalImage,
                          const std::string& selectedImage = "",
                          const std::string& disableImage = "",
                          TextureResType texType = TextureResType::LOCAL);
    

    /**
     * 加载按钮的纹理贴图（texture）
     *
     * @param normal    正常状态的纹理贴图（texture）名
     *
     * @param selected    选中状态的纹理贴图（texture）名
     *
     * @param disabled   禁用状态的纹理贴图（texture）名
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextures(const std::string& normal,
                      const std::string& selected,
                      const std::string& disabled = "",
                      TextureResType texType = TextureResType::LOCAL);

    /**
     * 加载按钮正常状态的纹理贴图（texture）
     *
     * @param normal    正常状态的纹理贴图（texture）
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureNormal(const std::string& normal, TextureResType texType = TextureResType::LOCAL);

    /**
     * 加载按钮选中状态的纹理贴图（texture）
     *
     * @param selected    选中状态的纹理贴图（texture）
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTexturePressed(const std::string& selected, TextureResType texType = TextureResType::LOCAL);

    /**
     * 加载按钮暗态（dark state）的纹理贴图（texture）（此处暗态（dark state）即为禁用状态（disabled）原文写为dark state。译者注）
     *
     * @param disabled    暗态（dark state）纹理贴图（texture）
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureDisabled(const std::string& disabled, TextureResType texType = TextureResType::LOCAL);

    /**
     * 如果按钮使用scale9渲染器进行渲染，设置按钮的capinsets
     *
     * @param capInsets    按钮的capinsets
     */
    void setCapInsets(const Rect &capInsets);

    /**
     * 如果按钮使用scale9渲染器进行渲染，设置按钮的capinsets
     *
     * @param capInsets    按钮的capinsets
     */
    void setCapInsetsNormalRenderer(const Rect &capInsets);

    const Rect& getCapInsetsNormalRenderer();

    /**
     * 如果按钮使用scale9渲染器进行渲染，设置按钮的capinsets
     *
     * @param capInsets    按钮的capinsets
     */
    void setCapInsetsPressedRenderer(const Rect &capInsets);

    const Rect& getCapInsetsPressedRenderer();

    /**
     * 如果按钮使用scale9渲染器进行渲染，设置按钮的capinsets
     *
     * @param capInsets    按钮的capinsets
     */
    void setCapInsetsDisabledRenderer(const Rect &capInsets);

    const Rect& getCapInsetsDisabledRenderer();

    /**
     * 如果按钮使用scale9渲染器进行渲染，设置按钮
     *
     * @param 值为true则使用scale9渲染器, 为false则不会。
     */
    virtual void setScale9Enabled(bool able);

    bool isScale9Enabled();

    /**
     * 如果按钮使用点击缩放效果（zoom effect），改变按钮状态
     *
     * @param 值为true则为使用点击缩放效果（zoom effect）, 为false 则不会.
     */
    void setPressedActionEnabled(bool enabled);

    //重写（override）widget 的"ignoreContentAdaptWithSize" 方法.
    virtual void ignoreContentAdaptWithSize(bool ignore) override;

    //重写（override）widget 的"getVirtualRendererSize" 方法.
    virtual const Size& getVirtualRendererSize() const override;

    //重写（override）widget 的"getVirtualRenderer" 方法.
    virtual Node* getVirtualRenderer() override;

    /**
     * 返回weight的“类名（class name）”.
     */
    virtual std::string getDescription() const override;

    void setTitleText(const std::string& text);
    const std::string& getTitleText() const;
    void setTitleColor(const Color3B& color);
    const Color3B& getTitleColor() const;
    void setTitleFontSize(float size);
    float getTitleFontSize() const;
    void setTitleFontName(const std::string& fontName);
    const std::string& getTitleFontName() const;
    
CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    virtual bool init(const std::string& normalImage,
                      const std::string& selectedImage = "",
                      const std::string& disableImage = "",
                      TextureResType texType = TextureResType::LOCAL);


protected:
    virtual void initRenderer() override;
    virtual void onPressStateChangedToNormal() override;
    virtual void onPressStateChangedToPressed() override;
    virtual void onPressStateChangedToDisabled() override;
    virtual void onSizeChanged() override;
    virtual void updateTextureColor() override;
    virtual void updateTextureOpacity() override;
    virtual void updateTextureRGBA() override;
    virtual void updateFlippedX() override;
    virtual void updateFlippedY() override;
    void normalTextureScaleChangedWithSize();
    void pressedTextureScaleChangedWithSize();
    void disabledTextureScaleChangedWithSize();
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void adaptRenderers() override;
    void updateTitleLocation();
protected:
    Node* _buttonNormalRenderer;
    Node* _buttonClickedRenderer;
    Node* _buttonDisableRenderer;
    Label* _titleRenderer;
    std::string _normalFileName;
    std::string _clickedFileName;
    std::string _disabledFileName;
    bool _prevIgnoreSize;
    bool _scale9Enabled;
    Rect _capInsetsNormal;
    Rect _capInsetsPressed;
    Rect _capInsetsDisabled;
    TextureResType _normalTexType;
    TextureResType _pressedTexType;
    TextureResType _disabledTexType;
    Size _normalTextureSize;
    Size _pressedTextureSize;
    Size _disabledTextureSize;
    bool _pressedActionEnabled;
    Color3B _titleColor;
    float _normalTextureScaleXInSize;
    float _normalTextureScaleYInSize;
    float _pressedTextureScaleXInSize;
    float _pressedTextureScaleYInSize;
    bool _normalTextureLoaded;
    bool _pressedTextureLoaded;
    bool _disabledTextureLoaded;
    bool _normalTextureAdaptDirty;
    bool _pressedTextureAdaptDirty;
    bool _disabledTextureAdaptDirty;
};

}

NS_CC_END

#endif /* defined(__CocoGUI__Button__) */
