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

#ifndef __UICHECKBOX_H__
#define __UICHECKBOX_H__

#include "gui/UIWidget.h"

namespace gui {

typedef enum
{
    CHECKBOX_STATE_EVENT_SELECTED,
    CHECKBOX_STATE_EVENT_UNSELECTED
}CheckBoxEventType;

typedef void (cocos2d::Object::*SEL_SelectedStateEvent)(cocos2d::Object*,CheckBoxEventType);
#define checkboxselectedeventselector(_SELECTOR) (SEL_SelectedStateEvent)(&_SELECTOR)

/**
*   @js NA
*   @lua NA
*/
class UICheckBox : public UIWidget
{
public:
    /**
     * Default constructor
     */
    UICheckBox();
    
    /**
     * Default destructor
     */
    virtual ~UICheckBox();
    
    /**
     * Allocates and initializes.
     */
    static UICheckBox* create();
    
    /**
     * Load textures for checkbox.
     *
     * @param backGround    backGround texture.
     *
     * @param backGroundSelected    backGround selected state texture.
     *
     * @param cross    cross texture.
     *
     * @param frontCrossDisabled    cross dark state texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextures(const char* backGround,const char* backGroundSelected,const char* cross,const char* backGroundDisabled,const char* frontCrossDisabled,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Load backGround texture for checkbox.
     *
     * @param backGround    backGround texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureBackGround(const char* backGround,TextureResType type = UI_TEX_TYPE_LOCAL);
    
    /**
     * Load backGroundSelected texture for checkbox.
     *
     * @param backGroundSelected     backGround selected state texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureBackGroundSelected(const char* backGroundSelected,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Load cross texture for checkbox.
     *
     * @param cross    cross texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureFrontCross(const char* cross,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Load backGroundDisabled texture for checkbox.
     *
     * @param backGroundDisabled    backGroundDisabled texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureBackGroundDisabled(const char* backGroundDisabled,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Load frontCrossDisabled texture for checkbox.
     *
     * @param frontCrossDisabled    frontCrossDisabled texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureFrontCrossDisabled(const char* frontCrossDisabled,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Sets selcted state for checkbox.
     *
     * @param selected    true that checkbox is selected, false otherwise.
     */
    void setSelectedState(bool selected);
    
    /**
     * Gets selcted state of checkbox.
     *
     * @return selected    true that checkbox is selected, false otherwise.
     */
    bool getSelectedState();
    
    //override "setAnchorPoint" method of widget.
    virtual void setAnchorPoint(const cocos2d::Point &pt) override;
    
    //add a call back function would called when checkbox is selected or unselected.
    void addEventListenerCheckBox(cocos2d::Object* target,SEL_SelectedStateEvent selector);
    
    //override "setFlipX" method of widget.
    virtual void setFlipX(bool flipX) override;
    
    //override "setFlipY" method of widget.
    virtual void setFlipY(bool flipY) override;
    
    //override "isFlipX" method of widget.
    virtual bool isFlipX() override;
    
    //override "isFlipY" method of widget.
    virtual bool isFlipY() override;
    
    //override "onTouchEnded" method of widget.
    virtual void onTouchEnded(const cocos2d::Point &touchPoint) override;
    
    //override "getContentSize" method of widget.
    virtual const cocos2d::Size& getContentSize() const override;
    
    //override "getVirtualRenderer" method of widget.
    virtual cocos2d::Node* getVirtualRenderer() override;
    
    /**
     * Returns the "class name" of widget.
     */
    virtual const char* getDescription() const override;

protected:
    virtual bool init() override;
    virtual void initRenderer() override;
    virtual void onPressStateChangedToNormal() override;
    virtual void onPressStateChangedToPressed() override;
    virtual void onPressStateChangedToDisabled() override;
    void selectedEvent();
    void unSelectedEvent();
    virtual void onSizeChanged() override;
    void backGroundTextureScaleChangedWithSize();
    void backGroundSelectedTextureScaleChangedWithSize();
    void frontCrossTextureScaleChangedWithSize();
    void backGroundDisabledTextureScaleChangedWithSize();
    void frontCrossDisabledTextureScaleChangedWithSize();
    virtual UIWidget* createCloneInstance() override;
    virtual void copySpecialProperties(UIWidget* model) override;
protected:
    cocos2d::Sprite* _backGroundBoxRenderer;
    cocos2d::Sprite* _backGroundSelectedBoxRenderer;
    cocos2d::Sprite* _frontCrossRenderer;
    cocos2d::Sprite* _backGroundBoxDisabledRenderer;
    cocos2d::Sprite* _frontCrossDisabledRenderer;
    bool _isSelected;

    cocos2d::Object*       _checkBoxEventListener;
    SEL_SelectedStateEvent    _checkBoxEventSelector;
    
    TextureResType _backGroundTexType;
    TextureResType _backGroundSelectedTexType;
    TextureResType _frontCrossTexType;
    TextureResType _backGroundDisabledTexType;
    TextureResType _frontCrossDisabledTexType;
    
    std::string _backGroundFileName;
    std::string _backGroundSelectedFileName;
    std::string _frontCrossFileName;
    std::string _backGroundDisabledFileName;
    std::string _frontCrossDisabledFileName;
};

}

#endif /* defined(__CocoGUI__UICheckBox__) */
