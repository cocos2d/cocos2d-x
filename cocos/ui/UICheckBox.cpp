/****************************************************************************
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

CheckBox::CheckBox()
: _checkBoxEventListener(nullptr)
{
}

CheckBox::~CheckBox()
{
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
                           const std::string& backGroundSelected,
                           const std::string& cross,
                           const std::string& backGroundDisabled,
                           const std::string& frontCrossDisabled,
                           TextureResType texType)
{
    CheckBox *pWidget = new (std::nothrow) CheckBox;
    if (pWidget && pWidget->init(backGround,
                                 backGroundSelected,
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
    bool highlight = _highlight;

    AbstractCheckButton::onTouchEnded(touch, unusedEvent);

    if (highlight)
    {
        if (_isSelected)
        {
            setSelected(false);
            dispatchSelectChangedEvent(false);
        }
        else
        {
            setSelected(true);
            dispatchSelectChangedEvent(true);
        }
    }
}
    

void CheckBox::dispatchSelectChangedEvent(bool selected)
{
    EventType eventType = (selected ? EventType::SELECTED : EventType::UNSELECTED);
    
    this->retain();
    if (_checkBoxEventCallback)
    {
        _checkBoxEventCallback(this, eventType);
    }
    if (_ccEventCallback)
    {
        _ccEventCallback(this, static_cast<int>(eventType));
    }
    
    this->release();
    
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
        _checkBoxEventCallback = checkBox->_checkBoxEventCallback;
        _ccEventCallback = checkBox->_ccEventCallback;
    }
}

}

NS_CC_END
