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

#include "ui/UIRadioButton.h"

NS_CC_BEGIN

namespace ui {
    
IMPLEMENT_CLASS_GUI_INFO(RadioButton)

RadioButton::RadioButton() :
_radioButtonEventCallback(nullptr),
_group(nullptr)
{
}

RadioButton::~RadioButton()
{
    _radioButtonEventCallback = nullptr;
    _group = nullptr;
}

RadioButton* RadioButton::create()
{
    RadioButton* widget = new (std::nothrow) RadioButton();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

RadioButton* RadioButton::create(const std::string& backGround,
                           const std::string& backGroundSeleted,
                           const std::string& cross,
                           const std::string& backGroundDisabled,
                           const std::string& frontCrossDisabled,
                           TextureResType texType)
{
    RadioButton *pWidget = new (std::nothrow) RadioButton;
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

RadioButton* RadioButton::create(const std::string& backGround,
                           const std::string& cross,
                           TextureResType texType)
{
    RadioButton *pWidget = new (std::nothrow) RadioButton;
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

void RadioButton::dispatchSelectChangedEvent(bool selected)
{
    EventType eventType = (selected ? EventType::SELECTED : EventType::UNSELECTED);
    this->retain();
    if (_radioButtonEventCallback)
    {
        _radioButtonEventCallback(this, eventType);
    }
    if (_ccEventCallback)
    {
        _ccEventCallback(this, static_cast<int>(eventType));
    }
    
    if(selected && _group != nullptr)
    {
        _group->onChangedRadioButtonSelect(this);
    }
    this->release();
}

void RadioButton::addEventListener(const ccRadioButtonCallback& callback)
{
    _radioButtonEventCallback = callback;
}

void RadioButton::releaseUpEvent()
{
    Widget::releaseUpEvent();
    
    if (!_isSelected)
    {
        setSelected(true);
        dispatchSelectChangedEvent(true);
    }
}

std::string RadioButton::getDescription() const
{
    return "RadioButton";
}

Widget* RadioButton::createCloneInstance()
{
    return RadioButton::create();
}

void RadioButton::copySpecialProperties(Widget *widget)
{
    RadioButton* radioButton = dynamic_cast<RadioButton*>(widget);
    if (radioButton)
    {
        AbstractCheckButton::copySpecialProperties(widget);
        _radioButtonEventCallback = radioButton->_radioButtonEventCallback;
        _ccEventCallback = radioButton->_ccEventCallback;
        _group = radioButton->_group;
    }
}

RadioButtonGroup::RadioButtonGroup() :
_radioButtonGroupEventCallback(nullptr),
_selectedRadioButton(nullptr),
_allowedNoSelection(false)
{
}

RadioButtonGroup::~RadioButtonGroup()
{
    _radioButtonGroupEventCallback = nullptr;
    _selectedRadioButton = nullptr;
    _radioButtons.clear();
}

RadioButtonGroup* RadioButtonGroup::create()
{
    RadioButtonGroup* widget = new (std::nothrow) RadioButtonGroup();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

void RadioButtonGroup::addEventListener(const ccRadioButtonGroupCallback& callback)
{
    _radioButtonGroupEventCallback = callback;
}

void RadioButtonGroup::addRadioButton(RadioButton* radioButton)
{
    if(radioButton != nullptr)
    {
        CCASSERT(!radioButton->_group, "It already belongs to a group!");
        radioButton->_group = this;
        _radioButtons.pushBack(radioButton);
        
        if(!_allowedNoSelection && _selectedRadioButton == nullptr)
        {
            setSelectedButton(radioButton);
        }
    }
}

void RadioButtonGroup::removeRadioButton(RadioButton* radioButton)
{
    ssize_t index = _radioButtons.getIndex(radioButton);
    if( index == CC_INVALID_INDEX )
    {
        CCLOGERROR("The radio button does not belong to this group!");
        return;
    }
    
    if(radioButton != nullptr)
    {
        radioButton->_group = nullptr;
        if(radioButton == _selectedRadioButton)
        {
            deselect();
        }
        _radioButtons.erase(index);
        
        if(!_allowedNoSelection && _selectedRadioButton == nullptr && !_radioButtons.empty())
        {
            setSelectedButton(0);
        }
    }
}

ssize_t RadioButtonGroup::getNumberOfRadioButtons() const
{
    return _radioButtons.size();
}

RadioButton* RadioButtonGroup::getRadioButtonByIndex(int index) const
{
    if(index >= _radioButtons.size())
    {
        CCLOGERROR("Out of array index! length=%d, requestedIndex=%d", (int)_radioButtons.size(), index);
        return nullptr;
    }
    return _radioButtons.at(index);
}

void RadioButtonGroup::deselect()
{
    if(_selectedRadioButton != nullptr)
    {
        _selectedRadioButton->setSelected(false);
        _selectedRadioButton->dispatchSelectChangedEvent(false);
    }
    _selectedRadioButton = nullptr;
}

int RadioButtonGroup::getSelectedButtonIndex() const
{
    return (int) _radioButtons.getIndex(_selectedRadioButton);
}

void RadioButtonGroup::setSelectedButton(int index)
{
    CCASSERT(index < _radioButtons.size(), "Out of array index!");
    setSelectedButton(_radioButtons.at(index));
}

void RadioButtonGroup::setSelectedButton(RadioButton* radioButton)
{
    if(!_allowedNoSelection && radioButton == nullptr)
    {
        return;
    }
    if(_selectedRadioButton == radioButton)
    {
        return;
    }
    if(radioButton != nullptr && !_radioButtons.contains(radioButton))
    {
        CCLOGERROR("The radio button does not belong to this group!");
        return;
    }
    
    deselect();
    _selectedRadioButton = radioButton;
    if(_selectedRadioButton != nullptr)
    {
        _selectedRadioButton->setSelected(true);
    }
    onChangedRadioButtonSelect(_selectedRadioButton);
}

std::string RadioButtonGroup::getDescription() const
{
    return "RadioButtonGroup";
}

void RadioButtonGroup::setAllowedNoSelection(bool allowedNoSelection)
{
    _allowedNoSelection = allowedNoSelection;
}

bool RadioButtonGroup::isAllowedNoSelection() const
{
    return _allowedNoSelection;
}

Widget* RadioButtonGroup::createCloneInstance()
{
    return RadioButtonGroup::create();
}

void RadioButtonGroup::copySpecialProperties(Widget *widget)
{
    RadioButtonGroup* radioButtonGroup = dynamic_cast<RadioButtonGroup*>(widget);
    if (radioButtonGroup)
    {
        _radioButtonGroupEventCallback = radioButtonGroup->_radioButtonGroupEventCallback;
        _ccEventCallback = radioButtonGroup->_ccEventCallback;
        _selectedRadioButton = radioButtonGroup->_selectedRadioButton;
        _allowedNoSelection = radioButtonGroup->_allowedNoSelection;
        
        _radioButtons.clear();
        for(const auto& radioButton : radioButtonGroup->_radioButtons)
        {
            _radioButtons.pushBack(radioButton);
        }
    }
}

void RadioButtonGroup::onChangedRadioButtonSelect(RadioButton* radioButton)
{
    if(_selectedRadioButton != radioButton)
    {
        deselect();
        _selectedRadioButton = radioButton;
    }
    
    this->retain();
    if (_radioButtonGroupEventCallback)
    {
        int index = (int) _radioButtons.getIndex(radioButton);
        _radioButtonGroupEventCallback(_selectedRadioButton, index, EventType::SELECT_CHANGED);
    }
    if (_ccEventCallback)
    {
        _ccEventCallback(this, static_cast<int>(EventType::SELECT_CHANGED));
    }
    this->release();
}
    
}

NS_CC_END
