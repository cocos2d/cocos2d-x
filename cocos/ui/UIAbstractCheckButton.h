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

#ifndef __UIABSTRACTCHECKBUTTON_H__
#define __UIABSTRACTCHECKBUTTON_H__

#include "ui/UIWidget.h"
#include "ui/GUIExport.h"

/**
 * @addtogroup ui
 * @{
 */
NS_CC_BEGIN
class Sprite;

namespace ui {
    
/**
 *  AbstractCheckButton is a specific type of two-states button that can be either checked or unchecked.
 */
class CC_GUI_DLL AbstractCheckButton : public Widget
{
    
public:
    /**
     * Load all textures for initializing a check button.
     *
     * @param background    The background image name.
     * @param backgroundSelected    The background selected image name.
     * @param cross    The cross image name.
     * @param backgroundDisabled    The background disabled state texture.
     * @param frontCrossDisabled    The front cross disabled state image name.
     * @param texType    @see `Widget::TextureResType`
     */
    void loadTextures(const std::string& background,
                      const std::string& backgroundSelected,
                      const std::string& cross,
                      const std::string& backgroundDisabled,
                      const std::string& frontCrossDisabled,
                      TextureResType texType = TextureResType::LOCAL);
    
    /**
     * Load background texture for check button.
     *
     * @param backGround   The background image name.
     * @param type    @see `Widget::TextureResType`
     */
    void loadTextureBackGround(const std::string& backGround,TextureResType type = TextureResType::LOCAL);
    
    /**
     * Load background selected state texture for check button.
     *
     * @param backGroundSelected    The background selected state image name.
     * @param texType    @see `Widget::TextureResType`
     */
    void loadTextureBackGroundSelected(const std::string& backGroundSelected,TextureResType texType = TextureResType::LOCAL);
    
    /**
     * Load cross texture for check button.
     *
     * @param crossTextureName    The cross texture name.
     * @param texType    @see `Widget::TextureResType`
     */
    void loadTextureFrontCross(const std::string& crossTextureName,TextureResType texType = TextureResType::LOCAL);
    
    /**
     * Load background disabled state texture for checkbox.
     *
     * @param backGroundDisabled    The background disabled state texture name.
     *
     * @param texType    @see `Widget::TextureResType`
     */
    void loadTextureBackGroundDisabled(const std::string& backGroundDisabled,TextureResType texType = TextureResType::LOCAL);
    
    /**
     * Load frontcross disabled texture for checkbox.
     *
     * @param frontCrossDisabled    The front cross disabled state texture name.
     * @param texType    @see `Widget::TextureResType`
     */
    void loadTextureFrontCrossDisabled(const std::string& frontCrossDisabled,TextureResType texType = TextureResType::LOCAL);
    
    /**
     * Query whether CheckBox is selected or not.
     *@return true means "selected", false otherwise.
     */
    bool isSelected()const;
    
    /**
     * Change CheckBox state.
     * Set to true will cause the CheckBox's state to "selected", false otherwise.
     *@param selected Set to true will change CheckBox to selected state, false otherwise.
     */
    void setSelected(bool selected);
    
    //override functions
    virtual Size getVirtualRendererSize() const override;
    virtual Node* getVirtualRenderer() override;
    
    /** When user pressed the CheckBox, the button will zoom to a scale.
     * The final scale of the CheckBox  equals (CheckBox original scale + _zoomScale)
     * @since v3.3
     */
    void setZoomScale(float scale);
    /**
     * @brief Return a zoom scale
     * @return A zoom scale of Checkbox.
     * @since v3.3
     */
    float getZoomScale()const;
    
    /**
     * @brief Return the sprite instance of background
     * @return the sprite instance of background.
     */
    Sprite* getRendererBackground() const { return _backGroundBoxRenderer; }
    
    /**
     * @brief Return the sprite instance of background when selected
     * @return the sprite instance of background when selected
     */
    Sprite* getRendererBackgroundSelected() const { return _backGroundSelectedBoxRenderer; }
    
    /**
     * @brief Return the sprite instance of front cross
     * @return the sprite instance of front cross
     */
    Sprite* getRendererFrontCross() const { return _frontCrossRenderer; }
    
    /**
     * @brief Return the sprite instance of background when disabled
     * @return the sprite instance of background when disabled
     */
    Sprite* getRendererBackgroundDisabled() const { return _backGroundBoxDisabledRenderer; }
    
    /**
     * @brief Return the sprite instance of front cross when disabled
     * @return the sprite instance of front cross when disabled
     */
    Sprite* getRendererFrontCrossDisabled() const { return _frontCrossDisabledRenderer; }
    
CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    virtual bool init(const std::string& backGround,
                      const std::string& backGroundSeleted,
                      const std::string& cross,
                      const std::string& backGroundDisabled,
                      const std::string& frontCrossDisabled,
                      TextureResType texType = TextureResType::LOCAL);
    
protected:
    /**
     * Default constructor.
     */
    AbstractCheckButton();
    
    /**
     * Default destructor.
     *
     * @lua NA
     */
    virtual ~AbstractCheckButton();
    
    virtual void initRenderer() override;
    virtual void onPressStateChangedToNormal() override;
    virtual void onPressStateChangedToPressed() override;
    virtual void onPressStateChangedToDisabled() override;
    
    void setupBackgroundTexture();
    void loadTextureBackGround(SpriteFrame* spriteFrame);
    void setupBackgroundSelectedTexture();
    void loadTextureBackGroundSelected(SpriteFrame* spriteFrame);
    void setupFrontCrossTexture();
    void loadTextureFrontCross(SpriteFrame* spriteframe);
    void setupBackgroundDisable();
    void loadTextureBackGroundDisabled(SpriteFrame* spriteframe);
    void setupFrontCrossDisableTexture();
    void loadTextureFrontCrossDisabled(SpriteFrame* spriteframe);
    
    virtual void dispatchSelectChangedEvent(bool selected) = 0;
    
    virtual void onSizeChanged() override;
    
    void backGroundTextureScaleChangedWithSize();
    void backGroundSelectedTextureScaleChangedWithSize();
    void frontCrossTextureScaleChangedWithSize();
    void backGroundDisabledTextureScaleChangedWithSize();
    void frontCrossDisabledTextureScaleChangedWithSize();
    
    virtual void copySpecialProperties(Widget* model) override;
    virtual void adaptRenderers() override;
protected:
    Sprite* _backGroundBoxRenderer;
    Sprite* _backGroundSelectedBoxRenderer;
    Sprite* _frontCrossRenderer;
    Sprite* _backGroundBoxDisabledRenderer;
    Sprite* _frontCrossDisabledRenderer;
    bool _isSelected;
    
    bool _isBackgroundSelectedTextureLoaded;
    bool _isBackgroundDisabledTextureLoaded;
    bool _isFrontCrossDisabledTextureLoaded;
    TextureResType _backGroundTexType;
    TextureResType _backGroundSelectedTexType;
    TextureResType _frontCrossTexType;
    TextureResType _backGroundDisabledTexType;
    TextureResType _frontCrossDisabledTexType;
    
    float _zoomScale;
    float _backgroundTextureScaleX;
    float _backgroundTextureScaleY;
    
    bool _backGroundBoxRendererAdaptDirty;
    bool _backGroundSelectedBoxRendererAdaptDirty;
    bool _frontCrossRendererAdaptDirty;
    bool _backGroundBoxDisabledRendererAdaptDirty;
    bool _frontCrossDisabledRendererAdaptDirty;
};
    
}

NS_CC_END
// end of ui group
/// @}

#endif /* defined(__UIABSTRACTCHECKBUTTON_H__) */
