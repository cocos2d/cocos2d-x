/****************************************************************************
Copyright (c) 2015 Neo Kim (neo.kim@neofect.com)

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

#ifndef __UIRADIOBUTTON_H__
#define __UIRADIOBUTTON_H__

#include "ui/UIAbstractCheckButton.h"
#include "ui/GUIExport.h"

/**
 * @addtogroup ui
 * @{
 */
NS_CC_BEGIN

namespace ui {

class RadioButtonGroup;

/**@~english
 *  RadioButton is a specific type of two-states button that is similar to CheckBox.
 *  Additionally, it can be used together with RadioButtonGroup to interact with other radio buttons.
 * @~chinese 
 * RadioButton是一种特定类型的两状态按钮,它与复选框相似。
 * 此外,它可以 和RadioButtonGroup一起使用,形成一个"组". 在这个组里面, 同时只能有一个单选按钮处于被选中状态.
 */
class CC_GUI_DLL RadioButton : public AbstractCheckButton
{

    DECLARE_CLASS_GUI_INFO
    
    friend class RadioButtonGroup;
    
public:
    /**@~english
     * Radio button event types.
     * @~chinese 
     * 单选按钮事件类型。
     */
    enum class EventType
    {
        SELECTED,
        UNSELECTED
    };
    
    /**@~english
     * A callback which will be called after certain RadioButton event issue.
     * @~chinese 
     * 一个回调函数,它将在某些RadioButton事件发出后被调用。
     * @see `RadioButton::EventType`
     */
    typedef std::function<void(RadioButton* radioButton, EventType)> ccRadioButtonCallback;
    
    /**@~english
     * Default constructor.
     *
     * @~chinese 
     * 默认构造函数。
     * 
     * @lua new
     */
    RadioButton();
    
    /**@~english
     * Default destructor.
     *
     * @~chinese 
     * 默认的析构函数。
     * 
     * @lua NA
     */
    virtual ~RadioButton();
    
    /**@~english
     * Create and return a empty RadioButton instance pointer.
     * @~chinese 
     * 创建并返回一个空指针RadioButton实例。
     */
    static RadioButton* create();
    
    /**@~english
     * Create a radio button with various images.
     *
     * @~chinese 
     * 使用各种图像创建一个单选按钮。
     * 
     * @param backGround    @~english backGround texture.
     * @~chinese 背景纹理名称。
     * @param backGroundSelected    @~english backGround selected state texture.
     * @~chinese 背景纹理选择状态纹理名称。
     * @param cross    @~english cross texture.
     * @~chinese 前景纹理名称。
     * @param backGroundDisabled    @~english backGround disabled state texture.
     * @~chinese 背景纹理禁用状态名称。
     * @param frontCrossDisabled    @~english cross dark state texture.
     * @~chinese 前景禁用状态纹理名称。
     * @param texType    @see `Widget::TextureResType`
     *
     * @return @~english A RadioButton instance pointer.
     * @~chinese 一个RadioButton实例指针。
     */
    static RadioButton* create(const std::string& backGround,
                            const std::string& backGroundSelected,
                            const std::string& cross,
                            const std::string& backGroundDisabled,
                            const std::string& frontCrossDisabled,
                            TextureResType texType = TextureResType::LOCAL);
    
    /**@~english
     * Another factory method to create a RadioButton instance.
     * This method uses less resource to create a RadioButton.
     * @~chinese 
     * 另一个工厂方法, 用来创建一个RadioButton实例。
     * 该方法使用更少的资源来创建RadioButton。
     * @param backGround @~english The background image name in `std::string`.
     * @~chinese 背景图片的名字, 类型为std::string
     * @param cross @~english The cross image name in `std::string`.
     * @~chinese 前景图片的名称,类型为std::string
     * @param texType  @~english The texture's resource type in `Widget::TextureResType`.
     * @~chinese 纹理资源类型, 类型为“Widget::TextureResType”。
     * @return @~english A RadioButton instance pointer
     * @~chinese 一个RadioButton实例的指针
     */
    static RadioButton* create(const std::string& backGround,
                            const std::string& cross,
                            TextureResType texType = TextureResType::LOCAL);
    
    /**@~english
     * Add a callback function which would be called when radio button is selected or unselected.
     * @~chinese 
     * 注册一个回调函数, 它将在单选按钮被选中或者取消的时候被调用.
     *@param callback @~english A std::function with type @see `ccRadioButtonCallback`
     * @~chinese 一个类型为ccRadioButtonCallback的回调函数
     */
    void addEventListener(const ccRadioButtonCallback& callback);
    
    virtual std::string getDescription() const override;
    
protected:
    virtual void releaseUpEvent() override;

    virtual void dispatchSelectChangedEvent(bool selected) override;
    
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    
    ccRadioButtonCallback _radioButtonEventCallback;
    RadioButtonGroup* _group;
    
};

/**@~english
 *  RadioButtonGroup groups designated radio buttons to make them interact to each other.
 *  In one RadioButtonGroup, only one or no RadioButton can be checked.
 * @~chinese 
 * RadioButtonGroup可以把指定的单选按钮组织起来, 形成一个组, 使它们彼此交互。
 * 在一个RadioButtonGroup, 有且只有一个或者没有RadioButton可以处于被选中状态.
 */
class CC_GUI_DLL RadioButtonGroup : public Widget
{
    friend class RadioButton;
public:
    /**@~english
     * Radio button group event types.
     * @~chinese 
     * 单选按钮组事件类型。
     */
    enum class EventType
    {
        SELECT_CHANGED,
    };
    
    /**@~english
     * A callback which will be called after RadioButtonGroup event issue.
     * @~chinese 
     * 一个回调函数, 它将在RadioButtonGroup事件产生的时候被调用。
     * @see `RadioButtonGroup::EventType`
     */
    typedef std::function<void(RadioButton* radioButton, int index, EventType)> ccRadioButtonGroupCallback;
    
    /**@~english
     * Default constructor.
     *
     * @~chinese 
     * 默认构造函数。
     * 
     * @lua new
     */
    RadioButtonGroup();
    
    /**@~english
     * Default destructor.
     *
     * @~chinese 
     * 默认的析构函数。
     * 
     * @lua NA
     */
    virtual ~RadioButtonGroup();
    
    /**@~english
     * Create and return a empty RadioButtonGroup instance pointer.
     * @~chinese 
     * 创建并返回一个RadioButtonGroup实例。
     */
    static RadioButtonGroup* create();
    
    /**@~english
     * Add a callback function which would be called when radio button is selected or unselected.
     * @~chinese 
     * 添加一个回调函数, 它将在单选按钮被选中或者取消的时候被调用.
     *@param callback @~english A std::function with type @see `ccRadioButtonGroupCallback`
     * @~chinese 类型为 ccRadioButtonGroupCallback的回调函数
     */
    void addEventListener(const ccRadioButtonGroupCallback& callback);
    
    /**@~english
     * Get the index of selected radio button.
     *
     * @~chinese 
     * 获取选中单选按钮的索引。
     * 
     * @return @~english the selected button's index. Returns -1 if no button is selected.
     * @~chinese 选中按钮的索引。返回-1表示没有按钮被选中。
     */
    virtual int getSelectedButtonIndex() const;
    
    /**@~english
     * Select a radio button by index.
     *
     * @~chinese 
     * 通过索引设置一个单选按钮处于选中状态。
     * 
     * @param index @~english of the radio button
     * @~chinese 单选按钮在组里面的索引
     */
    virtual void setSelectedButton(int index);
    
    /**@~english
     * Select a radio button by instance.
     *
     * @~chinese 
     * 通过指针设置一个单选按钮处于选中状态.
     * 
     * @param radio @~english button instance
     * @~chinese 按钮实例
     */
    virtual void setSelectedButton(RadioButton* radioButton);
    
    /**@~english
     * Select a radio button by index without event dispatch.
     *
     * @~chinese 
     * 通过单选按钮在组里面的索引来设置选中状态, 但是此方法不会响应事件处理
     * 
     * @param index @~english of the radio button
     * @~chinese 的单选按钮
     */
    virtual void setSelectedButtonWithoutEvent(int index);
    
    /**@~english
     * Select a radio button by instance without event dispatch.
     *
     * @~chinese 
     * 通过单选按钮的指针来设置选中状态, 但是此方法不会响应事件处理
     * 
     * @param radio @~english button instance
     * @~chinese 按钮实例
     */
    virtual void setSelectedButtonWithoutEvent(RadioButton* radioButton);
    
    /**@~english
     * Add a radio button into this group.
     *
     * @~chinese 
     * 添加一个单选按钮到这个组。
     * 
     * @param radio @~english button instance
     * @~chinese 按钮实例
     */
    virtual void addRadioButton(RadioButton* radioButton);
    
    /**@~english
     * Remove a radio button from this group.
     *
     * @~chinese 
     * 从这组删除一个单选按钮。
     * 
     * @param radio @~english button instance
     * @~chinese 按钮实例
     */
    virtual void removeRadioButton(RadioButton* radioButton);
    
    /**@~english
     * Remove all radio button from this group.
     * @~chinese 
     * 从这一组中删除所有单选按钮。
     */
    virtual void removeAllRadioButtons();
    
    /**@~english
     * Get the number of radio buttons in this group.
     *
     * @~chinese 
     * 获取分组里面的单选按钮的数量.
     * 
     * @return @~english the number of radio buttons in this group
     * @~chinese 这一组单选按钮的数量
     */
    ssize_t getNumberOfRadioButtons() const;
    
    /**@~english
     * Get a radio button in this group by index.
     *
     * @~chinese 
     * 在一组单选按钮中, 通过索引来选择。
     * 
     * @param index @~english  index of the radio button
     * @~chinese 单选按钮在组里面的索引值
     * @return @~english radio button instance. Returns nullptr if out of index.
     * @~chinese 返回一个单选按钮的实例,  如果索引值超出范围, 则返回nullptr.
     */
    RadioButton* getRadioButtonByIndex(int index) const;
    
    /**@~english
     * Set a flag for allowing no-selection feature.
     * If it is allowed, no radio button can be selected.
     * If it is not allowed, one radio button must be selected all time except it is empty.
     * Default is not allowed.
     *
     * @~chinese 
     * 设置一个标记允许组里面出现未选择功能。
     * 如果它是允许的,则可以不用选择单选按钮。
     * 如果它是不允许的,那么, 每时每刻都必须选择一个单选按钮,除了它是空的。
     * 默认是不允许的。
     * 
     * @param true @~english means allowing no-selection, false means disallowing no-selection.
     * @~chinese 设置是否允许组里面存在没有选中的单选按键. True则表示允许组里面存在没有一个单选按钮被选中.
     */
    void setAllowedNoSelection(bool allowedNoSelection);
    
    /**@~english
     * Query whether no-selection is allowed or not.
     *
     * @~chinese 
     * 查询是否允许组里面存在一个都不选择的情况。
     * 
     * @param true @~english means no-selection is allowed, false means no-selection is not allowed.
     * @~chinese True, 则意味着允许未选择, 反之, 则意味着不允许未选择的单选按钮存在.
     */
    bool isAllowedNoSelection() const;
    
    virtual std::string getDescription() const override;
    
protected:
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    
    void onChangedRadioButtonSelect(RadioButton* radioButton);
    void deselect();
    
    Vector<RadioButton*> _radioButtons;
    ccRadioButtonGroupCallback _radioButtonGroupEventCallback;
    RadioButton* _selectedRadioButton;
    bool _allowedNoSelection;
    
};
    
}

NS_CC_END
// end of ui group
/// @}

#endif /* defined(__UIRADIOBUTTON_H__) */
