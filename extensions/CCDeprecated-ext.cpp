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

#include "cocos-ext.h"

 NS_CC_EXT_BEGIN

const Control::EventType CCControlEventTouchDown = Control::EventType::TOUCH_DOWN;
const Control::EventType CCControlEventTouchDragInside = Control::EventType::DRAG_INSIDE;
const Control::EventType CCControlEventTouchDragOutside = Control::EventType::DRAG_OUTSIDE;
const Control::EventType CCControlEventTouchDragEnter = Control::EventType::DRAG_ENTER;
const Control::EventType CCControlEventTouchDragExit = Control::EventType::DRAG_EXIT;
const Control::EventType CCControlEventTouchUpInside = Control::EventType::TOUCH_UP_INSIDE;
const Control::EventType CCControlEventTouchUpOutside = Control::EventType::TOUCH_UP_OUTSIDE;
const Control::EventType CCControlEventTouchCancel = Control::EventType::TOUCH_CANCEL;
const Control::EventType CCControlEventValueChanged = Control::EventType::VALUE_CHANGED;

const Control::State CCControlStateNormal = Control::State::NORMAL;
const Control::State CCControlStateHighlighted = Control::State::HIGH_LIGHTED;
const Control::State CCControlStateDisabled = Control::State::DISABLED;
const Control::State CCControlStateSelected = Control::State::SELECTED;

const EditBox::EditBox::KeyboardReturnType  kKeyboardReturnTypeDefault = EditBox::EditBox::KeyboardReturnType::DEFAULT;
const EditBox::EditBox::KeyboardReturnType  kKeyboardReturnTypeDone = EditBox::EditBox::KeyboardReturnType::DONE;
const EditBox::EditBox::KeyboardReturnType  kKeyboardReturnTypeSend = EditBox::EditBox::KeyboardReturnType::SEND;
const EditBox::EditBox::KeyboardReturnType  kKeyboardReturnTypeSearch = EditBox::EditBox::KeyboardReturnType::SEARCH;
const EditBox::EditBox::KeyboardReturnType  kKeyboardReturnTypeGo = EditBox::EditBox::KeyboardReturnType::GO;

const EditBox::InputMode kEditBoxInputModeAny = EditBox::InputMode::ANY;
const EditBox::InputMode kEditBoxInputModeEmailAddr = EditBox::InputMode::EMAIL_ADDRESS;
const EditBox::InputMode kEditBoxInputModeNumeric = EditBox::InputMode::NUMERIC;
const EditBox::InputMode kEditBoxInputModePhoneNumber = EditBox::InputMode::PHONE_NUMBER;
const EditBox::InputMode kEditBoxInputModeUrl = EditBox::InputMode::URL;
const EditBox::InputMode kEditBoxInputModeDecimal = EditBox::InputMode::DECIMAL;
const EditBox::InputMode kEditBoxInputModeSingleLine = EditBox::InputMode::SINGLE_LINE;

const EditBox::InputFlag kEditBoxInputFlagPassword = EditBox::InputFlag::PASSWORD;
const EditBox::InputFlag kEditBoxInputFlagSensitive = EditBox::InputFlag::SENSITIVE;
const EditBox::InputFlag kEditBoxInputFlagInitialCapsWord = EditBox::InputFlag::INITIAL_CAPS_WORD;
const EditBox::InputFlag kEditBoxInputFlagInitialCapsSentence = EditBox::InputFlag::INITIAL_CAPS_SENTENCE;
const EditBox::InputFlag kEditBoxInputFlagInitialCapsAllCharacters = EditBox::InputFlag::INTIAL_CAPS_ALL_CHARACTERS;

NS_CC_EXT_END
