/****************************************************************************
Copyright (c) 2013-2016 Chukong Technologies Inc.

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

#include "ui/UICheckBox.h"

NS_CC_BEGIN

namespace ui {
    
IMPLEMENT_CLASS_GUI_INFO(CheckBox)

CheckBox::CheckBox():
_checkBoxEventListener(nullptr),
_checkBoxEventSelector(nullptr)
{
}

CheckBox::~CheckBox()
{
    _checkBoxEventSelector = nullptr;
}

CheckBox* CheckBox::create()
{
    CheckBox* widget = new (std::nothrow) CheckBox();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}
    
CheckBox* CheckBox::create(const std::string& backGround,
                           const std::string& backGroundSeleted,
                           const std::string& cross,
                           const std::string& backGroundDisabled,
                           const std::string& frontCrossDisabled,
                           TextureResType texType)
{
    CheckBox *pWidget = new (std::nothrow) CheckBox;
    if (pWidget && pWidget->init(backGround,
                                 backGroundSeleted,
                                 cross,
                                 backGroundDisabled,
                                 frontCrossDisabled,
                                 texType))
    {
        pWidget->autorelease();
        return pWidget;
    }
    CC_SAFE_DELETE(pWidget);
    return nullptr;
}
    
CheckBox* CheckBox::create(const std::string& backGround,
                           const std::string& cross,
                           TextureResType texType)
{
    CheckBox *pWidget = new (std::nothrow) CheckBox;
    if (pWidget && pWidget->init(backGround,
                                 "",
                                 cross,
                                 "",
                                 "",
                                 texType))
    {
        pWidget->autorelease();
        return pWidget;
    }
    CC_SAFE_DELETE(pWidget);
    return nullptr;
}
    
void CheckBox::onTouchEnded(Touch *touch, Event *unusedEvent)
{
    if (_isSelected)
    {
        setSelected(false);
        AbstractCheckButton::onTouchEnded(touch, unusedEvent);
        dispatchSelectChangedEvent(false);
    }
    else
    {
        setSelected(true);
        AbstractCheckButton::onTouchEnded(touch, unusedEvent);
        dispatchSelectChangedEvent(true);
    }
}
    

void CheckBox::dispatchSelectChangedEvent(bool selected)
{
    EventType eventType = (selected ? EventType::SELECTED : EventType::UNSELECTED);
    CheckBoxEventType checkBoxEventType = (selected ? CHECKBOX_STATE_EVENT_SELECTED : CHECKBOX_STATE_EVENT_UNSELECTED);
    
    this->retain();
    if (_checkBoxEventCallback)
    {
        _checkBoxEventCallback(this, eventType);
    }
    if (_ccEventCallback)
    {
        _ccEventCallback(this, static_cast<int>(eventType));
    }
    
    if (_checkBoxEventListener && _checkBoxEventSelector)
    {
        (_checkBoxEventListener->*_checkBoxEventSelector)(this, checkBoxEventType);
    }
    this->release();
    
}

void CheckBox::addEventListenerCheckBox(Ref *target, SEL_SelectedStateEvent selector)
{
    _checkBoxEventListener = target;
    _checkBoxEventSelector = selector;
}

void CheckBox::addEventListener(const ccCheckBoxCallback& callback)
{
    _checkBoxEventCallback = callback;
}
    
std::string CheckBox::getDescription() const
{
    return "CheckBox";
}

Widget* CheckBox::createCloneInstance()
{
    return CheckBox::create();
}

void CheckBox::copySpecialProperties(Widget *widget)
{
    CheckBox* checkBox = dynamic_cast<CheckBox*>(widget);
    if (checkBox)
    {
        AbstractCheckButton::copySpecialProperties(widget);
        _checkBoxEventListener = checkBox->_checkBoxEventListener;
        _checkBoxEventSelector = checkBox->_checkBoxEventSelector;
        _checkBoxEventCallback = checkBox->_checkBoxEventCallback;
        _ccEventCallback = checkBox->_ccEventCallback;
    }
}

}

NS_CC_END
