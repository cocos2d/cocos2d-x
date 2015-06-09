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
#include "ui/GUIExport.h"

/**
 * @addtogroup ui
 * @{
 */
NS_CC_BEGIN

class Label;
class SpriteFrame;

namespace ui{

    class Scale9Sprite;
/**@~english
 * Represents a push-button widget.
 * Push-buttons can be pressed, or clicked, by the user to perform an action.
 * @~chinese 
 * 表示一个按钮组件。
 * 按钮可以被按下,或者点击, 并且在按下或者点击之后，可以由用户指定一个动作来执行。
 */
class CC_GUI_DLL Button : public Widget
{

    DECLARE_CLASS_GUI_INFO

public:

    /**@~english
     * Default constructor.
     * @~chinese 
     * 默认构造函数。
     */
    Button();

    /**@~english
     * Default destructor.
     *
     * @~chinese 
     * 默认析构函数。
     * 
     * @lua NA
     */
    virtual ~Button();

    /**@~english
     * Create a empty Button.
     * @~chinese 
     * 创建一个空的按钮。
     *@return @~english A empty Button instance.
     * @~chinese 一个空按钮实例。
     */
    static Button* create();

    /**@~english
     * Create a button with custom textures.
     * @~chinese 
     * 使用自定义的纹理创建一个按钮。
     * @param normalImage @~english normal state texture name.
     * @~chinese 正常状态纹理的名字。
     * @param selectedImage  @~english selected state texture name.
     * @~chinese 选中状态纹理名称。
     * @param disableImage @~english disabled state texture name.
     * @~chinese  禁用状态纹理的名字
     * @param texType    @see `TextureResType`
     * @return @~english a Button instance.
     * @~chinese 一个按钮实例。
     */
    static Button* create(const std::string& normalImage,
                          const std::string& selectedImage = "",
                          const std::string& disableImage = "",
                          TextureResType texType = TextureResType::LOCAL);

    /**@~english
     * Load textures for button.
     *
     * @~chinese 
     * 加载按钮的纹理。
     * 
     * @param normal    @~english normal state texture name.
     * @~chinese 正常状态纹理的名字。
     * @param selected    @~english selected state texture name.
     * @~chinese 选中状态纹理名字。
     * @param disabled    @~english disabled state texture name.
     * @~chinese 禁用状态纹理的名字。
     * @param texType    @see `TextureResType`
     */
    void loadTextures(const std::string& normal,
                      const std::string& selected,
                      const std::string& disabled = "",
                      TextureResType texType = TextureResType::LOCAL);

    /**@~english
     * Load normal state texture for button.
     *
     * @~chinese 
     * 加载按钮正常状态的纹理。
     * 
     * @param normal    @~english normal state texture.
     * @~chinese 正常状态纹理。
     * @param texType    @see `TextureResType`
     */
    void loadTextureNormal(const std::string& normal, TextureResType texType = TextureResType::LOCAL);

    /**@~english
     * Load selected state texture for button.
     *
     * @~chinese 
     *  加载按钮选中状态纹理。
     * 
     * @param selected    @~english selected state texture.
     * @~chinese  选中状态纹理名字
     * @param texType    @see `TextureResType`
     */
    void loadTexturePressed(const std::string& selected, TextureResType texType = TextureResType::LOCAL);

    /**@~english
     * Load disabled state texture for button.
     *
     * @~chinese 
     * 加载按钮禁用状态的纹理。
     * 
     * @param disabled    @~english dark state texture.
     * @~chinese  禁用状态纹理。
     * @param texType    @see `TextureResType`
     */
    void loadTextureDisabled(const std::string& disabled, TextureResType texType = TextureResType::LOCAL);

    /**@~english
     * Sets capInsets for button.
     * The capInset affects  all button scale9 renderer only if `setScale9Enabled(true)` is called
     *
     * @~chinese 
     * 设置按钮的capInsets。
     * 这个capInset影响按钮所有的九宫格渲染器，只有在调用“setScale9Enabled(true)”后才生效
     * 
     * @param capInsets    @~english capInset in Rect.
     * @~chinese 一个矩形类型的capInset
     */
    void setCapInsets(const Rect &capInsets);

    /**@~english
     * Sets capInsets for button, only the normal state scale9 renderer will be affected.
     *
     * @~chinese 
     * 设置按钮的capInsets,只有正常状态的九宫格渲染器才会受到影响。
     * 
     * @param capInsets    @~english capInsets in Rect.
     * @~chinese 一个矩形类型的capInset
     */
    void setCapInsetsNormalRenderer(const Rect &capInsets);

    /**@~english
     * Return the capInsets of normal state scale9sprite.
     * @~chinese 
     * 返回正常状态的九宫格渲染器的capInsets。
     *@return @~english The normal scale9 renderer capInsets.
     * @~chinese 正常状态的九宫格渲染器的capInsets。
     */
    const Rect& getCapInsetsNormalRenderer()const;

    /**@~english
     * Sets capInsets for button, only the pressed state scale9 renderer will be affected.
     *
     * @~chinese 
     * 设置按钮的capInsets,只有按下状态的九宫格渲染器会受到影响。
     * 
     * @param capInsets    @~english capInsets in Rect
     * @~chinese 一个矩形类型的capInset
     */
    void setCapInsetsPressedRenderer(const Rect &capInsets);

    /**@~english
     * Return the capInsets of pressed state scale9sprite.
     * @~chinese 
     * 返回按下状态的九宫格渲染器的capInsets
     *@return @~english The pressed scale9 renderer capInsets.
     * @~chinese 按下状态的九宫格渲染器的capInsets
     */
    const Rect& getCapInsetsPressedRenderer()const;

    /**@~english
     * Sets capInsets for button, only the disabled state scale9 renderer will be affected.
     *
     * @~chinese 
     * 设置按钮的capInsets,只有禁用状态的九宫格渲染器会受到影响。
     * 
     * @param capInsets  @~english capInsets in Rect.
     * @~chinese 一个矩形类型的capInset
     */
    void setCapInsetsDisabledRenderer(const Rect &capInsets);

    /**@~english
     * Return the capInsets of disabled state scale9sprite.
     * @~chinese 
     * 返回禁用状态的九宫格渲染器的capInsets。
     *@return @~english The disabled scale9 renderer capInsets.
     * @~chinese 禁用状态的九宫格渲染器的capInsets
     */
    const Rect& getCapInsetsDisabledRenderer()const;

    /**@~english
     * Enable scale9 renderer.
     *
     * @~chinese 
     * 启用九宫格渲染
     * 
     * @param enable @~english Set to true will use scale9 renderer, false otherwise.
     * @~chinese 设置为true则使用九宫格渲染，设置false则不使用九宫格渲染
     */
    virtual void setScale9Enabled(bool enable);

    /**@~english
     * Query whether button is using scale9 renderer or not.
     * @~chinese 
     * 查询按钮是否使用scale9渲染
     *@return @~english whether button use scale9 renderer or not.
     * @~chinese 按钮是否使用九宫格渲染。
     */
    bool isScale9Enabled()const;

    /**@~english
     * Enable zooming action when button is pressed.
     *
     * @~chinese 
     * 设置启用按钮被按下时的缩放操作。
     * 
     * @param enabled @~english Set to true will enable zoom effect, false otherwise.
     * @~chinese 设置为true将使用缩放效果,false则不启用缩放
     */
    void setPressedActionEnabled(bool enabled);

    //override methods
    virtual void ignoreContentAdaptWithSize(bool ignore) override;
    virtual Size getVirtualRendererSize() const override;
    virtual Node* getVirtualRenderer() override;
    virtual std::string getDescription() const override;

    /**@~english
     * Return the inner title renderer of Button.
     * @~chinese 
     * 返回按钮的内部标题渲染器。
     * @return @~english The button title.
     * @~chinese 按钮标题渲染器。
     * @since v3.3
     */
    Label* getTitleRenderer()const;

    /**@~english
     * Change the content of button's title.
     * @~chinese 
     * 改变按钮的标题的内容。
     *@param text @~english The title in std::string.
     * @~chinese std::string格式的标题
     */
    void setTitleText(const std::string& text);

    /**@~english
     * Query the button title content.
     * @~chinese 
     * 查询按钮标题内容。
     *@return @~english Get the button's title content.
     * @~chinese 按钮的标题内容。
     */
    const std::string getTitleText() const;

    /**@~english
     * Change the color of button's title.
     * @~chinese 
     * 改变按钮的标题的颜色。
     *@param color @~english The title color in Color3B.
     * @~chinese Color3B格式的标题颜色。
     */
    void setTitleColor(const Color3B& color);

    /**@~english
     * Query the button title color.
     * @~chinese 
     * 查询按钮标题的颜色。
     *@return @~english Color3B of button title.
     * @~chinese Color3B格式的标题颜色
     */
    Color3B getTitleColor() const;

    /**@~english
     * Change the font size of button's title
     * @~chinese 
     * 改变按钮的标题的字体大小
     *@param size @~english Title font size in float.
     * @~chinese float格式的标题字体大小
     */
    void setTitleFontSize(float size);

    /**@~english
     * Query the font size of button title
     * @~chinese 
     * 查询按钮标题的字体大小
     *@return @~english font size in float.
     * @~chinese float格式的标题字体大小
     */
    float getTitleFontSize() const;

    /**@~english
     * Change the font name of button's title
     * @~chinese 
     * 改变按钮的标题的字体名称
     *@param fontName @~english a font name string.
     * @~chinese std::string格式的字体名称
     */
    void setTitleFontName(const std::string& fontName);

    /**@~english
     * Query the font name of button's title
     * @~chinese 
     * 查询按钮的标题的字体名称
     *@return @~english font name in std::string
     * @~chinese std::string格式的字体名称
     */
    const std::string getTitleFontName() const;

    /**@~english
     * Sets the title's text horizontal alignment.
     *
     * @~chinese 
     * 设置标题的文本的水平对齐方式
     * 
     * @param hAlignment @~english see TextHAlignment
     */
    void setTitleAlignment(TextHAlignment hAlignment);

    /**@~english
     * Sets the title's text vertical alignment.
     *
     * @~chinese 
     * 设置标题的文本垂直对齐方式
     * 
     * @param hAlignment @~english see TextHAlignment.
     * @param vAlignment @~english see TextVAlignment.
     */
    void setTitleAlignment(TextHAlignment hAlignment, TextVAlignment vAlignment);

    /** @brief @~english When user pressed the button, the button will zoom to a scale.
     * The final scale of the button  equals (button original scale + _zoomScale)
     * @~chinese 当用户按下按钮,按钮将照一个缩放比例来缩放
     * 按钮最终的缩放比例等于（按钮初始缩放比例+ _zoomScale)
     * @since v3.3
     */
    void setZoomScale(float scale);

    /**
     * @brief @~english Return a zoom scale
     * @~chinese 返回一个缩放比例
     * @return @~english the zoom scale in float
     * @~chinese float类型的缩放比例
     * @since v3.3
     */
    float getZoomScale()const;

CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    virtual bool init(const std::string& normalImage,
                      const std::string& selectedImage = "",
                      const std::string& disableImage = "",
                      TextureResType texType = TextureResType::LOCAL);

    virtual Size getNormalTextureSize() const;

protected:
    virtual void initRenderer() override;
    virtual void onPressStateChangedToNormal() override;
    virtual void onPressStateChangedToPressed() override;
    virtual void onPressStateChangedToDisabled() override;
    virtual void onSizeChanged() override;

    void loadTextureNormal(SpriteFrame* normalSpriteFrame);
    void setupNormalTexture();
    void loadTexturePressed(SpriteFrame* pressedSpriteFrame);
    void setupPressedTexture();
    void loadTextureDisabled(SpriteFrame* disabledSpriteFrame);
    void setupDisabledTexture();

    void normalTextureScaleChangedWithSize();
    void pressedTextureScaleChangedWithSize();
    void disabledTextureScaleChangedWithSize();

    virtual void adaptRenderers() override;
    void updateTitleLocation();
    void updateContentSize();
    void createTitleRenderer();

    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;

    virtual Size getNormalSize() const;
protected:
    Scale9Sprite* _buttonNormalRenderer;
    Scale9Sprite* _buttonClickedRenderer;
    Scale9Sprite* _buttonDisableRenderer;
    Label* _titleRenderer;

    float _zoomScale;
    bool _prevIgnoreSize;
    bool _scale9Enabled;
    bool _pressedActionEnabled;

    Rect _capInsetsNormal;
    Rect _capInsetsPressed;
    Rect _capInsetsDisabled;

    Size _normalTextureSize;
    Size _pressedTextureSize;
    Size _disabledTextureSize;

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

private:
    enum class FontType
    {
        SYSTEM,
        TTF,
        BMFONT
    };

    int _fontSize;
    FontType _type;
};

}

NS_CC_END
// end of ui group
/// @}

#endif /* defined(__CocoGUI__Button__) */
