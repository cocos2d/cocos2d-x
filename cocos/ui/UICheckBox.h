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
#include "ui/GUIExport.h"

/**
 * @addtogroup ui
 * @{
 */
NS_CC_BEGIN
class Sprite;

namespace ui {

/**
 * Checkbox event type, there are two type here:
 * - selected state
 * - unselected state
 * @deprecated use `CheckBox::EventType` instead
 */
typedef enum
{
    CHECKBOX_STATE_EVENT_SELECTED,
    CHECKBOX_STATE_EVENT_UNSELECTED
}CheckBoxEventType;

/**
 * A callback which will be called after checkbox event happens.
 * @deprecated use `CheckBox::ccCheckBoxCallback` instead.
 */
typedef void (Ref::*SEL_SelectedStateEvent)(Ref*,CheckBoxEventType);
#define checkboxselectedeventselector(_SELECTOR) (SEL_SelectedStateEvent)(&_SELECTOR)

/**
 *  Checkbox is a specific type of two-states button that can be either checked or unchecked.
 */
class CC_GUI_DLL CheckBox : public Widget
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
     * CheckBox event type, currently only "selected" and "unselected" event are cared.
     */
    enum class EventType
    {
        SELECTED,
        UNSELECTED
    };
    
    /**
     * A callback which will be called after certain CheckBox event issue.
     * @see `CheckBox::EventType`
     */
    typedef std::function<void(Ref*,CheckBox::EventType)> ccCheckBoxCallback;
    
    /**
     * Default constructor.
     * 
     * @lua new
     */
    CheckBox();

    /**
     * Default destructor.
     * 
     * @lua NA
     */
    virtual ~CheckBox();

    /**
     * Create and return a empty CheckBox instance pointer.
     */
    static CheckBox* create();
    
    /**
     * Create an checkbox with various images.
     *
     * @param backGround    backGround texture.
     * @param backGroundSelected    backGround selected state texture.
     * @param cross    cross texture.
     * @param backGroundDisabled    backGround disabled state texture.
     * @param frontCrossDisabled    cross dark state texture.
     * @param texType    @see `Widget::TextureResType`
     *
     * @return A CheckBox instance pointer.
     */
    static CheckBox* create(const std::string& backGround,
                            const std::string& backGroundSelected,
                            const std::string& cross,
                            const std::string& backGroundDisabled,
                            const std::string& frontCrossDisabled,
                            TextureResType texType = TextureResType::LOCAL);
    
    /**
     * Another factory method to create a CheckBox instance.
     * This method uses less resource to create a CheckBox.
     * @param backGround The background image name in `std::string`.
     * @param cross The cross image name in `std::string`.
     * @param texType  The texture's resource type in `Widget::TextureResType`.
     * @return A CheckBox instance pointer
     */
    static CheckBox* create(const std::string& backGround,
                            const std::string& cross,
                            TextureResType texType = TextureResType::LOCAL);

    /**
     * Load all textures for initializing a checkbox.
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
     * Load background texture for checkbox.
     *
     * @param backGround   The background image name.
     * @param type    @see `Widget::TextureResType`
     */
    void loadTextureBackGround(const std::string& backGround,TextureResType type = TextureResType::LOCAL);

    /**
     * Load background selected state texture for checkbox.
     *
     * @param backGroundSelected    The background selected state image name.
     * @param texType    @see `Widget::TextureResType`
     */
    void loadTextureBackGroundSelected(const std::string& backGroundSelected,TextureResType texType = TextureResType::LOCAL);

    /**
     * Load cross texture for checkbox.
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
     * Change Checkbox state to selected.
     *
     * @deprecated use `isSelected()` instead
     * @param selected   True means the Checkbox will be selected, false means unselected.
     */
    CC_DEPRECATED_ATTRIBUTE void setSelectedState(bool selected){this->setSelected(selected);}

    /**
     * Query whether the CheckBox is selected or not.
     *
     * @deprecated use `setSelected(bool)` instead.
     * @return selected    true that checkbox is selected, false otherwise.
     */
    CC_DEPRECATED_ATTRIBUTE bool getSelectedState()const{return this->isSelected();}
    
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

    /**Add a callback function which would be called when checkbox is selected or unselected.
     *@deprecated use `addEventListener(const ccCheckBoxCallback&)` instead
     *@param target A pointer type in Ref*.
     *@param selector A member function pointer in SEL_SelectedStateEvent.
     */
    CC_DEPRECATED_ATTRIBUTE void addEventListenerCheckBox(Ref* target,SEL_SelectedStateEvent selector);

    /**
     *Add a callback function which would be called when checkbox is selected or unselected.
     *@param callback A std::function with type @see `ccCheckBoxCallback`
     */
    void addEventListener(const ccCheckBoxCallback& callback);


    //override functions
    virtual Size getVirtualRendererSize() const override;
    virtual Node* getVirtualRenderer() override;
    virtual std::string getDescription() const override;
    
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
    
CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    virtual bool init(const std::string& backGround,
                      const std::string& backGroundSeleted,
                      const std::string& cross,
                      const std::string& backGroundDisabled,
                      const std::string& frontCrossDisabled,
                      TextureResType texType = TextureResType::LOCAL);

protected:
    virtual void initRenderer() override;
    virtual void onPressStateChangedToNormal() override;
    virtual void onPressStateChangedToPressed() override;
    virtual void onPressStateChangedToDisabled() override;
    
    void selectedEvent();
    void unSelectedEvent();
    
    virtual void releaseUpEvent() override;
    
    virtual void onSizeChanged() override;
    
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
    //if you use the old event callback, it will retain the _checkBoxEventListener
    Ref*       _checkBoxEventListener;
    
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (push)
#pragma warning (disable: 4996)
#endif
    SEL_SelectedStateEvent    _checkBoxEventSelector;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (pop)
#endif
    
    ccCheckBoxCallback _checkBoxEventCallback;

    TextureResType _backGroundTexType;
    TextureResType _backGroundSelectedTexType;
    TextureResType _frontCrossTexType;
    TextureResType _backGroundDisabledTexType;
    TextureResType _frontCrossDisabledTexType;

    float _zoomScale;
    float _backgroundTextureScaleX;
    float _backgroundTextureScaleY;
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
// end of ui group
/// @}

#endif /* defined(__CocoGUI__CheckBox__) */
