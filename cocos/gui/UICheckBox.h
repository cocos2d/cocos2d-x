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

#ifndef __UICHECKBOX_H__
#define __UICHECKBOX_H__

#include "gui/UIWidget.h"

NS_CC_BEGIN

namespace ui {

typedef enum
{
    CHECKBOX_STATE_EVENT_SELECTED,
    CHECKBOX_STATE_EVENT_UNSELECTED
}CheckBoxEventType;

typedef void (Ref::*SEL_SelectedStateEvent)(Ref*,CheckBoxEventType);
#define checkboxselectedeventselector(_SELECTOR) (SEL_SelectedStateEvent)(&_SELECTOR)

/**
*   @js NA
*   @lua NA
*/
class CheckBox : public Widget
{
public:
    /**
     * Default constructor
     */
    CheckBox();

    /**
     * Default destructor
     */
    virtual ~CheckBox();

    /**
     * Allocates and initializes.
     */
    static CheckBox* create();

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
    virtual void setAnchorPoint(const Point &pt) override;

    //add a call back function would called when checkbox is selected or unselected.
    void addEventListenerCheckBox(Ref* target,SEL_SelectedStateEvent selector);

    //override "setFlippedX" method of widget.
    virtual void setFlippedX(bool flippedX) override;

    //override "setFlippedY" method of widget.
    virtual void setFlippedY(bool flippedY) override;

    //override "isFlippedX" method of widget.
    virtual bool isFlippedX() override;

    //override "isFlippedY" method of widget.
    virtual bool isFlippedY() override;

    /** @deprecated Use isFlippedX() instead */
    CC_DEPRECATED_ATTRIBUTE bool isFlipX() { return isFlippedX(); };
    /** @deprecated Use setFlippedX() instead */
    CC_DEPRECATED_ATTRIBUTE void setFlipX(bool flipX) { setFlippedX(flipX); };
    /** @deprecated Use isFlippedY() instead */
    CC_DEPRECATED_ATTRIBUTE bool isFlipY() { return isFlippedY(); };
    /** @deprecated Use setFlippedY() instead */
    CC_DEPRECATED_ATTRIBUTE void setFlipY(bool flipY) { setFlippedY(flipY); };

    //override "onTouchEnded" method of widget.
    virtual void onTouchEnded(Touch *touch, Event *unusedEvent);

    //override "getContentSize" method of widget.
    virtual const Size& getContentSize() const override;

    //override "getVirtualRenderer" method of widget.
    virtual Node* getVirtualRenderer() override;

    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const override;

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
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
protected:
    Sprite* _backGroundBoxRenderer;
    Sprite* _backGroundSelectedBoxRenderer;
    Sprite* _frontCrossRenderer;
    Sprite* _backGroundBoxDisabledRenderer;
    Sprite* _frontCrossDisabledRenderer;
    bool _isSelected;

    Ref*       _checkBoxEventListener;
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

NS_CC_END

#endif /* defined(__CocoGUI__CheckBox__) */
