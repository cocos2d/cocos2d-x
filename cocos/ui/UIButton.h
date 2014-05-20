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
     * Default constructor
     */
    Button();

    /**
     * Default destructor
     */
    virtual ~Button();

    /**
     * Allocates and initializes.
     */
    static Button* create();
    
    /**
     * create a button with custom textures
     * @normalImage normal state texture name
     * @selectedImage  selected state texture name
     * @disableImage disabled state texture name
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    static Button* create(const std::string& normalImage,
                          const std::string& selectedImage = "",
                          const std::string& disableImage = "",
                          TextureResType texType = TextureResType::LOCAL);
    

    /**
     * Load textures for button.
     *
     * @param normal    normal state texture name.
     *
     * @param selected    selected state texture name.
     *
     * @param disabled    disabled state texture name.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextures(const std::string& normal,
                      const std::string& selected,
                      const std::string& disabled = "",
                      TextureResType texType = TextureResType::LOCAL);

    /**
     * Load normal state texture for button.
     *
     * @param normal    normal state texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureNormal(const std::string& normal, TextureResType texType = TextureResType::LOCAL);

    /**
     * Load selected state texture for button.
     *
     * @param selected    selected state texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTexturePressed(const std::string& selected, TextureResType texType = TextureResType::LOCAL);

    /**
     * Load dark state texture for button.
     *
     * @param disabled    dark state texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureDisabled(const std::string& disabled, TextureResType texType = TextureResType::LOCAL);

    /**
     * Sets capinsets for button, if button is using scale9 renderer.
     *
     * @param capInsets    capinsets for button
     */
    void setCapInsets(const Rect &capInsets);

    /**
     * Sets capinsets for button, if button is using scale9 renderer.
     *
     * @param capInsets    capinsets for button
     */
    void setCapInsetsNormalRenderer(const Rect &capInsets);

    const Rect& getCapInsetsNormalRenderer();

    /**
     * Sets capinsets for button, if button is using scale9 renderer.
     *
     * @param capInsets    capinsets for button
     */
    void setCapInsetsPressedRenderer(const Rect &capInsets);

    const Rect& getCapInsetsPressedRenderer();

    /**
     * Sets capinsets for button, if button is using scale9 renderer.
     *
     * @param capInsets    capinsets for button
     */
    void setCapInsetsDisabledRenderer(const Rect &capInsets);

    const Rect& getCapInsetsDisabledRenderer();

    /**
     * Sets if button is using scale9 renderer.
     *
     * @param true that using scale9 renderer, false otherwise.
     */
    virtual void setScale9Enabled(bool able);

    bool isScale9Enabled();

    /**
     * Changes if button can be clicked zoom effect.
     *
     * @param true that can be clicked zoom effect, false otherwise.
     */
    void setPressedActionEnabled(bool enabled);

    //override "ignoreContentAdaptWithSize" method of widget.
    virtual void ignoreContentAdaptWithSize(bool ignore) override;

    //override "getVirtualRendererSize" method of widget.
    virtual const Size& getVirtualRendererSize() const override;

    //override "getVirtualRenderer" method of widget.
    virtual Node* getVirtualRenderer() override;

    /**
     * Returns the "class name" of widget.
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
