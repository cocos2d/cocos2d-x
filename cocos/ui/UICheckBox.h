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

/**@~english
 * Checkbox event type, there are two type here:
 * - selected state
 * - unselected state
 * @~chinese 
 * 复选框事件类型,有两种类型:
 * - 选中事件
 * - 未选中事件
 * @deprecated use `CheckBox::EventType` instead
 */
typedef enum
{
    CHECKBOX_STATE_EVENT_SELECTED,
    CHECKBOX_STATE_EVENT_UNSELECTED
} CheckBoxEventType;

/**@~english
 * A callback which will be called after checkbox event happens.
 * @~chinese 
 * 一个回调函数，它将在复选框事件发生后被调用。
 * @deprecated use `CheckBox::ccCheckBoxCallback` instead.
 */
typedef void (Ref::*SEL_SelectedStateEvent)(Ref*,CheckBoxEventType);
#define checkboxselectedeventselector(_SELECTOR) (SEL_SelectedStateEvent)(&_SELECTOR)

/**@~english
 *  Checkbox is a specific type of two-states button that can be either checked or unchecked.
 * @~chinese 
 * 复选框是一种特定类型的“两状态”按钮,可以处于“选中”和“未选中状态”
 */
class CC_GUI_DLL CheckBox : public AbstractCheckButton
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**@~english
     * CheckBox event type, currently only "selected" and "unselected" event are cared.
     * @~chinese 
     * 复选框事件类型,目前只有“选中”和“未选中”两种事件
     */
    enum class EventType
    {
        SELECTED,
        UNSELECTED
    };
    
    /**@~english
     * A callback which will be called after certain CheckBox event issue.
     * @~chinese 
     * 一个回调函数,它将在某个复选框事件触发后被调用。
     * @see `CheckBox::EventType`
     */
    typedef std::function<void(Ref*,CheckBox::EventType)> ccCheckBoxCallback;
    
    /**@~english
     * Default constructor.
     * 
     * @~chinese 
     * 默认构造函数。
     * 
     * @lua new
     */
    CheckBox();

    /**@~english
     * Default destructor.
     * 
     * @~chinese 
     * 默认的析构函数。
     * 
     * @lua NA
     */
    virtual ~CheckBox();

    /**@~english
     * Create and return a empty CheckBox instance pointer.
     * @~chinese 
     * 创建并返回一个空的复选框实例。
     */
    static CheckBox* create();
    
    /**@~english
     * Create an checkbox with various images.
     *
     * @~chinese 
     * 使用一些图片来创建一个复选框
     * 
     * @param backGround    @~english backGround texture.
     * @~chinese 背景普通状态纹理。
     * @param backGroundSelected    @~english backGround selected state texture.
     * @~chinese 背景选中状态纹理。
     * @param cross    @~english cross texture.
     * @~chinese 勾选选中状态纹理
     * @param backGroundDisabled    @~english backGround disabled state texture.
     * @~chinese 背景禁用状态纹理。
     * @param frontCrossDisabled    @~english cross dark state texture.
     * @~chinese 勾选禁用状态纹理。
     * @param texType    @see `Widget::TextureResType`
     *
     * @return @~english A CheckBox instance pointer.
     * @~chinese 一个复选框实例的指针。
     */
    static CheckBox* create(const std::string& backGround,
                            const std::string& backGroundSelected,
                            const std::string& cross,
                            const std::string& backGroundDisabled,
                            const std::string& frontCrossDisabled,
                            TextureResType texType = TextureResType::LOCAL);
    
    /**@~english
     * Another factory method to create a CheckBox instance.
     * This method uses less resource to create a CheckBox.
     * @~chinese 
     * 另一个工厂方法，用来创建一个复选框实例。
     * 这种方法使用更少的图片资源来创建一个复选框。
     * @param backGround @~english The background image name in `std::string`.
     * @~chinese 背景普通状态图片的名字，类型是std::string
     * @param cross @~english The cross image name in `std::string`.
     * @~chinese 勾选选中状态图片的名字，类型是std::string
     * @param texType  @~english The texture's resource type in `Widget::TextureResType`.
     * @~chinese 纹理资源类型的“Widget::TextureResType”。
     * @return @~english A CheckBox instance pointer
     * @~chinese 一个复选框实例
     */
    static CheckBox* create(const std::string& backGround,
                            const std::string& cross,
                            TextureResType texType = TextureResType::LOCAL);

    /**
     * Change Checkbox state to selected.
     *
     * @~chinese 
     * 修改复选框的状态为“选中状态“
     * 
     * @deprecated use `isSelected()` instead
     * @param selected   @~english True means the Checkbox will be selected, false means unselected.
     * @~chinese 传True设置为”选中状态”，False设置为“未选中状态”
     */
    CC_DEPRECATED_ATTRIBUTE void setSelectedState(bool selected){this->setSelected(selected);}

    /**@~english
     * Query whether the CheckBox is selected or not.
     *
     * @~chinese 
     * 查询复选框是否被选中。
     * 
     * @deprecated use `setSelected(bool)` instead.
     * @return @~english selected    true that checkbox is selected, false otherwise.
     * @~chinese 如果复选框被选中了，则返回True,否则返回False.
     */
    CC_DEPRECATED_ATTRIBUTE bool getSelectedState()const{return this->isSelected();}

    /**@~english Add a callback function which would be called when checkbox is selected or unselected.
     * @~chinese 注册一个回调函数，它会在复选框的选择事件发生时被调用。
     *@deprecated use `addEventListener(const ccCheckBoxCallback&)` instead
     *@param target @~english A pointer type in Ref*.
     * @~chinese 一个Ref类型的指针
     *@param selector @~english A member function pointer in SEL_SelectedStateEvent.
     * @~chinese 一个SEL_SelectedStateEvent类型的成员函数指针。
     */
    CC_DEPRECATED_ATTRIBUTE void addEventListenerCheckBox(Ref* target,SEL_SelectedStateEvent selector);

    /**@~english
     *Add a callback function which would be called when checkbox is selected or unselected.
     * @~chinese 
     * 注册一个回调函数，它将在复选框被选中或者取消选中时被调用。
     *@param callback @~english A std::function with type @see `ccCheckBoxCallback`
     * @~chinese std::function类型 @see `ccCheckBoxCallback`
     */
    void addEventListener(const ccCheckBoxCallback& callback);


    //override functions
    virtual std::string getDescription() const override;

    virtual void onTouchEnded(Touch *touch, Event *unusedEvent) override;
protected:
    
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
