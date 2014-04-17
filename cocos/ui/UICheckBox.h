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

#include "ui/UIWidget.h"

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
    
    DECLARE_CLASS_GUI_INFO
    
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
     * create an checkbox
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
    static CheckBox* create(const std::string& backGround,
                            const std::string& backGroundSeleted,
                            const std::string& cross,
                            const std::string& backGroundDisabled,
                            const std::string& frontCrossDisabled,
                            TextureResType texType = UI_TEX_TYPE_LOCAL);

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
    void loadTextures(const std::string& backGround,
                      const std::string& backGroundSelected,
                      const std::string& cross,
                      const std::string& backGroundDisabled,
                      const std::string& frontCrossDisabled,
                      TextureResType texType = UI_TEX_TYPE_LOCAL);

    /**
     * Load backGround texture for checkbox.
     *
     * @param backGround    backGround texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureBackGround(const std::string& backGround,TextureResType type = UI_TEX_TYPE_LOCAL);

    /**
     * Load backGroundSelected texture for checkbox.
     *
     * @param backGroundSelected     backGround selected state texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureBackGroundSelected(const std::string& backGroundSelected,TextureResType texType = UI_TEX_TYPE_LOCAL);

    /**
     * Load cross texture for checkbox.
     *
     * @param cross    cross texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureFrontCross(const std::string&,TextureResType texType = UI_TEX_TYPE_LOCAL);

    /**
     * Load backGroundDisabled texture for checkbox.
     *
     * @param backGroundDisabled    backGroundDisabled texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureBackGroundDisabled(const std::string& backGroundDisabled,TextureResType texType = UI_TEX_TYPE_LOCAL);

    /**
     * Load frontCrossDisabled texture for checkbox.
     *
     * @param frontCrossDisabled    frontCrossDisabled texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureFrontCrossDisabled(const std::string& frontCrossDisabled,TextureResType texType = UI_TEX_TYPE_LOCAL);

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


    //add a call back function would called when checkbox is selected or unselected.
    void addEventListenerCheckBox(Ref* target,SEL_SelectedStateEvent selector);

    //override "onTouchEnded" method of widget.
    virtual void onTouchEnded(Touch *touch, Event *unusedEvent);

    //override "getVirtualRendererSize" method of widget.
    virtual const Size& getVirtualRendererSize() const override;

    //override "getVirtualRenderer" method of widget.
    virtual Node* getVirtualRenderer() override;

    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    virtual bool init(const std::string& backGround,
                      const std::string& backGroundSeleted,
                      const std::string& cross,
                      const std::string& backGroundDisabled,
                      const std::string& frontCrossDisabled,
                      TextureResType texType = UI_TEX_TYPE_LOCAL);

protected:
    virtual void initRenderer() override;
    virtual void onPressStateChangedToNormal() override;
    virtual void onPressStateChangedToPressed() override;
    virtual void onPressStateChangedToDisabled() override;
    void selectedEvent();
    void unSelectedEvent();
    virtual void onSizeChanged() override;
    virtual void updateTextureColor() override;
    virtual void updateTextureOpacity() override;
    virtual void updateTextureRGBA() override;
    virtual void updateFlippedX() override;
    virtual void updateFlippedY() override;
    void backGroundTextureScaleChangedWithSize();
    void backGroundSelectedTextureScaleChangedWithSize();
    void frontCrossTextureScaleChangedWithSize();
    void backGroundDisabledTextureScaleChangedWithSize();
    void frontCrossDisabledTextureScaleChangedWithSize();
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void adaptRenderers() override;
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
    
    bool _backGroundBoxRendererAdaptDirty;
    bool _backGroundSelectedBoxRendererAdaptDirty;
    bool _frontCrossRendererAdaptDirty;
    bool _backGroundBoxDisabledRendererAdaptDirty;
    bool _frontCrossDisabledRendererAdaptDirty;
};

}

NS_CC_END

#endif /* defined(__CocoGUI__CheckBox__) */
