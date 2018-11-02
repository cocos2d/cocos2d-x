/****************************************************************************
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
struct CC_DLL ResourceData;

namespace ui{

    class Scale9Sprite;
/**
 * Represents a push-button widget.
 * Push-buttons can be pressed, or clicked, by the user to perform an action.
 */
class CC_GUI_DLL Button : public Widget
{

    DECLARE_CLASS_GUI_INFO

public:

    /**
     * Default constructor.
     */
    Button();

    /**
     * Default destructor.
     *
     * @lua NA
     */
    virtual ~Button();

    /**
     * Create a empty Button.
     *@return A empty Button instance.
     */
    static Button* create();

    /**
     * Create a button with custom textures.
     * @param normalImage normal state texture name.
     * @param selectedImage  selected state texture name.
     * @param disableImage disabled state texture name.
     * @param texType    @see `TextureResType`
     * @return a Button instance.
     */
    static Button* create(const std::string& normalImage,
                          const std::string& selectedImage = "",
                          const std::string& disableImage = "",
                          TextureResType texType = TextureResType::LOCAL);

    /**
     * Load textures for button.
     *
     * @param normal    normal state texture name.
     * @param selected    selected state texture name.
     * @param disabled    disabled state texture name.
     * @param texType    @see `TextureResType`
     */
    void loadTextures(const std::string& normal,
                      const std::string& selected,
                      const std::string& disabled = "",
                      TextureResType texType = TextureResType::LOCAL);

    /**
     * Load normal state texture for button.
     *
     * @param normal    normal state texture.
     * @param texType    @see `TextureResType`
     */
    void loadTextureNormal(const std::string& normal, TextureResType texType = TextureResType::LOCAL);

    /**
     * Load selected state texture for button.
     *
     * @param selected    selected state texture.
     * @param texType    @see `TextureResType`
     */
    void loadTexturePressed(const std::string& selected, TextureResType texType = TextureResType::LOCAL);

    /**
     * Load disabled state texture for button.
     *
     * @param disabled    dark state texture.
     * @param texType    @see `TextureResType`
     */
    void loadTextureDisabled(const std::string& disabled, TextureResType texType = TextureResType::LOCAL);

    /**
     * Sets capInsets for button.
     * The capInset affects  all button scale9 renderer only if `setScale9Enabled(true)` is called
     *
     * @param capInsets    capInset in Rect.
     */
    void setCapInsets(const Rect &capInsets);

    /**
     * Sets capInsets for button, only the normal state scale9 renderer will be affected.
     *
     * @param capInsets    capInsets in Rect.
     */
    void setCapInsetsNormalRenderer(const Rect &capInsets);

    /**
     * Return the capInsets of normal state scale9sprite.
     *@return The normal scale9 renderer capInsets.
     */
    const Rect& getCapInsetsNormalRenderer()const;

    /**
     * Sets capInsets for button, only the pressed state scale9 renderer will be affected.
     *
     * @param capInsets    capInsets in Rect
     */
    void setCapInsetsPressedRenderer(const Rect &capInsets);

    /**
     * Return the capInsets of pressed state scale9sprite.
     *@return The pressed scale9 renderer capInsets.
     */
    const Rect& getCapInsetsPressedRenderer()const;

    /**
     * Sets capInsets for button, only the disabled state scale9 renderer will be affected.
     *
     * @param capInsets  capInsets in Rect.
     */
    void setCapInsetsDisabledRenderer(const Rect &capInsets);

    /**
     * Return the capInsets of disabled state scale9sprite.
     *@return The disabled scale9 renderer capInsets.
     */
    const Rect& getCapInsetsDisabledRenderer()const;

    /**
     * Enable scale9 renderer.
     *
     * @param enable Set to true will use scale9 renderer, false otherwise.
     */
    virtual void setScale9Enabled(bool enable);

    /**
     * Query whether button is using scale9 renderer or not.
     *@return whether button use scale9 renderer or not.
     */
    bool isScale9Enabled()const;

    /**
     * Enable zooming action when button is pressed.
     *
     * @param enabled Set to true will enable zoom effect, false otherwise.
     */
    void setPressedActionEnabled(bool enabled);

    //override methods
    virtual void ignoreContentAdaptWithSize(bool ignore) override;
    virtual Size getVirtualRendererSize() const override;
    virtual Node* getVirtualRenderer() override;
    virtual std::string getDescription() const override;

    /**
     * Return the inner title renderer of Button.
     * @return The button title.
     * @since v3.3
     */
    Label* getTitleRenderer()const;

    /**
     * Change the content of button's title.
     *@param text The title in std::string.
     */
    void setTitleText(const std::string& text);

    /**
     * Query the button title content.
     *@return Get the button's title content.
     */
    std::string getTitleText() const;

    /**
     * Change the color of button's title.
     *@param color The title color in Color3B.
     */
    void setTitleColor(const Color3B& color);

    /**
     * Query the button title color.
     *@return Color3B of button title.
     */
    Color3B getTitleColor() const;

    /**
     * Change the font size of button's title
     *@param size Title font size in float.
     */
    void setTitleFontSize(float size);

    /**
     * Query the font size of button title
     *@return font size in float.
     */
    float getTitleFontSize() const;

    /**
     * Change the font name of button's title
     *@param fontName a font name string.
     */
    void setTitleFontName(const std::string& fontName);

    /**
     * Query the font name of button's title
     *@return font name in std::string
     */
    std::string getTitleFontName() const;

    /**
     * Sets the title's text horizontal alignment.
     *
     * @param hAlignment see TextHAlignment
     */
    void setTitleAlignment(TextHAlignment hAlignment);

    /**
     * Sets the title's text vertical alignment.
     *
     * @param hAlignment see TextHAlignment.
     * @param vAlignment see TextVAlignment.
     */
    void setTitleAlignment(TextHAlignment hAlignment, TextVAlignment vAlignment);

    /** replaces the current Label node with a new one */
    void setTitleLabel(Label* label);

    /** returns the current Label being used */
    Label* getTitleLabel() const;


    /** @brief When user pressed the button, the button will zoom to a scale.
     * The final scale of the button  equals (button original scale + _zoomScale)
     * @since v3.3
     */
    void setZoomScale(float scale);

    /**
     * @brief Return a zoom scale
     * @return the zoom scale in float
     * @since v3.3
     */
    float getZoomScale()const;
    
    /**
     * @brief Return the nine-patch sprite of normal state
     * @return the nine-patch sprite of normal state
     * @since v3.9
     */
    Scale9Sprite* getRendererNormal() const { return _buttonNormalRenderer; }
    
    /**
     * @brief Return the nine-patch sprite of clicked state
     * @return the nine-patch sprite of clicked state
     * @since v3.9
     */
    Scale9Sprite* getRendererClicked() const { return _buttonClickedRenderer; }
    
    /**
     * @brief Return the nine-patch sprite of disabled state
     * @return the nine-patch sprite of disabled state
     * @since v3.9
     */
    Scale9Sprite* getRendererDisabled() const { return _buttonDisabledRenderer; }

    void resetNormalRender();
    void resetPressedRender();
    void resetDisabledRender();

    ResourceData getNormalFile();
    ResourceData getPressedFile();
    ResourceData getDisabledFile();

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
    void setupNormalTexture(bool textureLoaded);
    void loadTexturePressed(SpriteFrame* pressedSpriteFrame);
    void setupPressedTexture(bool textureLoaded);
    void loadTextureDisabled(SpriteFrame* disabledSpriteFrame);
    void setupDisabledTexture(bool textureLoaded);

    void normalTextureScaleChangedWithSize();
    void pressedTextureScaleChangedWithSize();
    void disabledTextureScaleChangedWithSize();

    virtual void adaptRenderers() override;
    void updateTitleLocation();
    void updateContentSize();
    virtual void createTitleRenderer();
    bool createTitleRendererIfNull();

    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;

    virtual Size getNormalSize() const;
protected:
    Scale9Sprite* _buttonNormalRenderer;
    Scale9Sprite* _buttonClickedRenderer;
    Scale9Sprite* _buttonDisabledRenderer;
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

    bool _normalTextureLoaded;
    bool _pressedTextureLoaded;
    bool _disabledTextureLoaded;
    bool _normalTextureAdaptDirty;
    bool _pressedTextureAdaptDirty;
    bool _disabledTextureAdaptDirty;

    std::string _normalFileName;
    std::string _clickedFileName;
    std::string _disabledFileName;
    TextureResType _normalTexType;
    TextureResType _pressedTexType;
    TextureResType _disabledTexType;

private:
    std::string _fontName;
};

}

NS_CC_END
// end of ui group
/// @}

#endif /* defined(__CocoGUI__Button__) */
