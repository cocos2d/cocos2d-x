/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#include "../BaseClasses/UIWidget.h"

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
     * Load textures for button.
     *
     * @param normal    normal state texture.
     *
     * @param selected    selected state texture.
     *
     * @param disabled    dark state texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextures(const char* normal,const char* selected,const char* disabled,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Load normal state texture for button.
     *
     * @param normal    normal state texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureNormal(const char* normal, TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Load selected state texture for button.
     *
     * @param selected    selected state texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTexturePressed(const char* selected, TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Load dark state texture for button.
     *
     * @param disabled    dark state texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureDisabled(const char* disabled, TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Sets capinsets for button, if button is using scale9 renderer.
     *
     * @param capInsets    capinsets for button
     */
    void setCapInsets(const CCRect &capInsets);

    /**
     * Sets capinsets for button, if button is using scale9 renderer.
     *
     * @param capInsets    capinsets for button
     */
    void setCapInsetsNormalRenderer(const CCRect &capInsets);
    
    const CCRect& getCapInsetNormalRenderer();
    
    /**
     * Sets capinsets for button, if button is using scale9 renderer.
     *
     * @param capInsets    capinsets for button
     */
    void setCapInsetsPressedRenderer(const CCRect &capInsets);
    
    const CCRect& getCapInsetPressedRenderer();
    
    /**
     * Sets capinsets for button, if button is using scale9 renderer.
     *
     * @param capInsets    capinsets for button
     */
    void setCapInsetsDisabledRenderer(const CCRect &capInsets);
    
    const CCRect& getCapInsetDisabledRenderer();
    
    //override "setAnchorPoint" of widget.
    virtual void setAnchorPoint(const CCPoint &pt);
    
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
    virtual void ignoreContentAdaptWithSize(bool ignore);
    
    //override "getContentSize" method of widget.
    virtual const CCSize& getContentSize() const;
    
    //override "getVirtualRenderer" method of widget.
    virtual CCNode* getVirtualRenderer();
    
    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const;
    
    void setTitleText(const std::string& text);
    const char* getTitleText() const;
    void setTitleColor(const ccColor3B& color);
    const ccColor3B& getTitleColor() const;
    void setTitleFontSize(float size);
    float getTitleFontSize() const;
    void setTitleFontName(const char* fontName);
    const char* getTitleFontName() const;

protected:
    virtual bool init();
    virtual void initRenderer();
    virtual void onPressStateChangedToNormal();
    virtual void onPressStateChangedToPressed();
    virtual void onPressStateChangedToDisabled();
    virtual void onSizeChanged();
    virtual void updateTextureColor();
    virtual void updateTextureOpacity();
    virtual void updateTextureRGBA();
    virtual void updateFlippedX();
    virtual void updateFlippedY();
    void normalTextureScaleChangedWithSize();
    void pressedTextureScaleChangedWithSize();
    void disabledTextureScaleChangedWithSize();
    virtual Widget* createCloneInstance();
    virtual void copySpecialProperties(Widget* model);
protected:
    CCNode* _buttonNormalRenderer;
    CCNode* _buttonClickedRenderer;
    CCNode* _buttonDisableRenderer;
    CCLabelTTF* _titleRenderer;
    std::string _normalFileName;
    std::string _clickedFileName;
    std::string _disabledFileName;
    bool _prevIgnoreSize;
    bool _scale9Enabled;
    CCRect _capInsetsNormal;
    CCRect _capInsetsPressed;
    CCRect _capInsetsDisabled;
    TextureResType _normalTexType;
    TextureResType _pressedTexType;
    TextureResType _disabledTexType;
    CCSize _normalTextureSize;
    CCSize _pressedTextureSize;
    CCSize _disabledTextureSize;
    bool _pressedActionEnabled;
    ccColor3B _titleColor;
    float _normalTextureScaleXInSize;
    float _normalTextureScaleYInSize;
    float _pressedTextureScaleXInSize;
    float _pressedTextureScaleYInSize;
    bool _normalTextureLoaded;
    bool _pressedTextureLoaded;
    bool _disabledTextureLoaded;
};

}

NS_CC_END

#endif /* defined(__CocoGUI__Button__) */
