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

#include "ui/UIAbstractCheckButton.h"
#include "ui/GUIExport.h"

/**
 * @addtogroup ui
 * @{
 */
NS_CC_BEGIN

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
} CheckBoxEventType;

/**
 * A callback which will be called after checkbox event happens.
 * @deprecated use `CheckBox::ccCheckBoxCallback` instead.
 */
typedef void (Ref::*SEL_SelectedStateEvent)(Ref*,CheckBoxEventType);
#define checkboxselectedeventselector(_SELECTOR) (SEL_SelectedStateEvent)(&_SELECTOR)

/**
 *  Checkbox is a specific type of two-states button that can be either checked or unchecked.
 */
class CC_GUI_DLL CheckBox : public AbstractCheckButton
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
    virtual std::string getDescription() const override;
    
protected:
    virtual void releaseUpEvent() override;
    
    virtual void dispatchSelectChangedEvent(bool selected) override;
    
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    
protected:
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

};

}

NS_CC_END
// end of ui group
/// @}

#endif /* defined(__CocoGUI__CheckBox__) */
