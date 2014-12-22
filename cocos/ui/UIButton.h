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

NS_CC_BEGIN

class Label;

namespace ui{
    
    class Scale9Sprite;
/**
*   @js NA
*   @lua NA
*/
class CC_GUI_DLL Button : public Widget
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
     * @param texType    @see TextureResType
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
     * @param texType    @see TextureResType
     */
    void loadTextureNormal(const std::string& normal, TextureResType texType = TextureResType::LOCAL);

    /**
     * Load selected state texture for button.
     *
     * @param selected    selected state texture.
     *
     * @param texType    @see TextureResType
     */
    void loadTexturePressed(const std::string& selected, TextureResType texType = TextureResType::LOCAL);

    /**
     * Load dark state texture for button.
     *
     * @param disabled    dark state texture.
     *
     * @param texType    @see TextureResType
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

    const Rect& getCapInsetsNormalRenderer()const;

    /**
     * Sets capinsets for button, if button is using scale9 renderer.
     *
     * @param capInsets    capinsets for button
     */
    void setCapInsetsPressedRenderer(const Rect &capInsets);

    const Rect& getCapInsetsPressedRenderer()const;

    /**
     * Sets capinsets for button, if button is using scale9 renderer.
     *
     * @param capInsets    capinsets for button
     */
    void setCapInsetsDisabledRenderer(const Rect &capInsets);

    const Rect& getCapInsetsDisabledRenderer()const;

    /**
     * Sets if button is using scale9 renderer.
     *
     * @param true that using scale9 renderer, false otherwise.
     */
    virtual void setScale9Enabled(bool able);

    bool isScale9Enabled()const;

    /**
     * Changes if button can be clicked zoom effect.
     *
     * @param true that can be clicked zoom effect, false otherwise.
     */
    void setPressedActionEnabled(bool enabled);

    //override "ignoreContentAdaptWithSize" method of widget.
    virtual void ignoreContentAdaptWithSize(bool ignore) override;

    //override "getVirtualRendererSize" method of widget.
    virtual Size getVirtualRendererSize() const override;

    //override "getVirtualRenderer" method of widget.
    virtual Node* getVirtualRenderer() override;
    
    /**
     * Return the inner title renderer of Button
     * @since v3.3
     */
    Label* getTitleRenderer()const;

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
    /** When user pressed the button, the button will zoom to a scale.
     * The final scale of the button  equals (button original scale + _zoomScale)
     * @since v3.3
     */
    void setZoomScale(float scale);
    /**
     * @brief Return a zoom scale 
     * @since v3.3
     */
    float getZoomScale()const;
    
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
  
    void normalTextureScaleChangedWithSize();
    void pressedTextureScaleChangedWithSize();
    void disabledTextureScaleChangedWithSize();
    
    virtual void adaptRenderers() override;
    void updateTitleLocation();
    void updateContentSize();
    
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
   
    virtual Size getNormalSize() const;
protected:
    Scale9Sprite* _buttonNormalRenderer;
    Scale9Sprite* _buttonClickedRenderer;
    Scale9Sprite* _buttonDisableRenderer;
    Label* _titleRenderer;
   
    float _zoomScale;
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
        TTF
    };

    std::string _fontName;
    int _fontSize;
    FontType _type;
};

}

NS_CC_END

#endif /* defined(__CocoGUI__Button__) */
