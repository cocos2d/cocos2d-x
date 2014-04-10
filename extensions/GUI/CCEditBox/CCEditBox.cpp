/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen
 
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

#include "CCEditBox.h"
#include "CCEditBoxImpl.h"

NS_CC_EXT_BEGIN

static const float CHECK_EDITBOX_POSITION_INTERVAL = 0.1f;

EditBox::EditBox(void)
: _editBoxImpl(nullptr)
, _delegate(nullptr)
, _editBoxInputMode(EditBox::InputMode::SINGLE_LINE)
, _editBoxInputFlag(EditBox::InputFlag::INTIAL_CAPS_ALL_CHARACTERS)
, _keyboardReturnType(KeyboardReturnType::DEFAULT)
, _fontSize(-1)
, _placeholderFontSize(-1)
, _colText(Color3B::WHITE)
, _colPlaceHolder(Color3B::GRAY)
, _maxLength(0)
, _adjustHeight(0.0f)
#if CC_ENABLE_SCRIPT_BINDING
, _scriptEditBoxHandler(0)
#endif
{
}

EditBox::~EditBox(void)
{
    CC_SAFE_DELETE(_editBoxImpl);
#if CC_ENABLE_SCRIPT_BINDING
    unregisterScriptEditBoxHandler();
#endif
}


void EditBox::touchDownAction(Ref *sender, Control::EventType controlEvent)
{
    _editBoxImpl->openKeyboard();
}

EditBox* EditBox::create(const Size& size, Scale9Sprite* pNormal9SpriteBg, Scale9Sprite* pPressed9SpriteBg/* = NULL*/, Scale9Sprite* pDisabled9SpriteBg/* = NULL*/)
{
    EditBox* pRet = new EditBox();
    
    if (pRet != NULL && pRet->initWithSizeAndBackgroundSprite(size, pNormal9SpriteBg))
    {
        if (pPressed9SpriteBg != NULL)
        {
            pRet->setBackgroundSpriteForState(pPressed9SpriteBg, Control::State::HIGH_LIGHTED);
        }
        
        if (pDisabled9SpriteBg != NULL)
        {
            pRet->setBackgroundSpriteForState(pDisabled9SpriteBg, Control::State::DISABLED);
        }
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

bool EditBox::initWithSizeAndBackgroundSprite(const Size& size, Scale9Sprite* pPressed9SpriteBg)
{
    if (ControlButton::initWithBackgroundSprite(pPressed9SpriteBg))
    {
        _editBoxImpl = __createSystemEditBox(this);
        _editBoxImpl->initWithSize(size);
        _editBoxImpl->setInputMode(EditBox::InputMode::ANY);
        
        this->setZoomOnTouchDown(false);
        this->setPreferredSize(size);
        this->setPosition(Point(0, 0));
        this->addTargetWithActionForControlEvent(this, cccontrol_selector(EditBox::touchDownAction), Control::EventType::TOUCH_UP_INSIDE);
        
        return true;
    }
    return false;
}

void EditBox::setDelegate(EditBoxDelegate* pDelegate)
{
    _delegate = pDelegate;
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->setDelegate(pDelegate);
    }
}

EditBoxDelegate* EditBox::getDelegate()
{
    return _delegate;
}

void EditBox::setText(const char* pText)
{
    if (pText != NULL)
    {
        _text = pText;
        if (_editBoxImpl != NULL)
        {
            _editBoxImpl->setText(pText);
        }
    }
}

const char* EditBox::getText(void)
{
    if (_editBoxImpl != NULL)
    {
		const char* pText = _editBoxImpl->getText();
		if(pText != NULL)
			return pText;
    }
    
    return "";
}

void EditBox::setFont(const char* pFontName, int fontSize)
{
    _fontName = pFontName;
    _fontSize = fontSize;
    if (pFontName != NULL)
    {
        if (_editBoxImpl != NULL)
        {
            _editBoxImpl->setFont(pFontName, fontSize);
        }
    }
}

void EditBox::setFontName(const char* pFontName)
{
    _fontName = pFontName;
    if (_editBoxImpl != NULL && _fontSize != -1)
    {
        _editBoxImpl->setFont(pFontName, _fontSize);
    }
}

void EditBox::setFontSize(int fontSize)
{
    _fontSize = fontSize;
    if (_editBoxImpl != NULL && _fontName.length() > 0)
    {
        _editBoxImpl->setFont(_fontName.c_str(), _fontSize);
    }
}

void EditBox::setFontColor(const Color3B& color)
{
    _colText = color;
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->setFontColor(color);
    }
}

void EditBox::setPlaceholderFont(const char* pFontName, int fontSize)
{
    _placeholderFontName = pFontName;
    _placeholderFontSize = fontSize;
    if (pFontName != NULL)
    {
        if (_editBoxImpl != NULL)
        {
            _editBoxImpl->setPlaceholderFont(pFontName, fontSize);
        }
    }
}

void EditBox::setPlaceholderFontName(const char* pFontName)
{
    _placeholderFontName = pFontName;
    if (_editBoxImpl != NULL && _placeholderFontSize != -1)
    {
        _editBoxImpl->setPlaceholderFont(pFontName, _fontSize);
    }
}

void EditBox::setPlaceholderFontSize(int fontSize)
{
    _placeholderFontSize = fontSize;
    if (_editBoxImpl != NULL && _placeholderFontName.length() > 0)
    {
        _editBoxImpl->setPlaceholderFont(_placeholderFontName.c_str(), _fontSize);
    }
}

void EditBox::setPlaceholderFontColor(const Color3B& color)
{
    _colText = color;
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->setPlaceholderFontColor(color);
    }
}

void EditBox::setPlaceHolder(const char* pText)
{
    if (pText != NULL)
    {
        _placeHolder = pText;
        if (_editBoxImpl != NULL)
        {
            _editBoxImpl->setPlaceHolder(pText);
        }
    }
}

const char* EditBox::getPlaceHolder(void)
{
    return _placeHolder.c_str();
}

void EditBox::setInputMode(EditBox::InputMode inputMode)
{
    _editBoxInputMode = inputMode;
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->setInputMode(inputMode);
    }
}

void EditBox::setMaxLength(int maxLength)
{
    _maxLength = maxLength;
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->setMaxLength(maxLength);
    }
}


int EditBox::getMaxLength()
{
    return _maxLength;
}

void EditBox::setInputFlag(EditBox::InputFlag inputFlag)
{
    _editBoxInputFlag = inputFlag;
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->setInputFlag(inputFlag);
    }
}

void EditBox::setReturnType(EditBox::KeyboardReturnType returnType)
{
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->setReturnType(returnType);
    }
}

/* override function */
void EditBox::setPosition(const Point& pos)
{
    ControlButton::setPosition(pos);
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->setPosition(pos);
    }
}

void EditBox::setVisible(bool visible)
{
    ControlButton::setVisible(visible);
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->setVisible(visible);
    }
}

void EditBox::setContentSize(const Size& size)
{
    ControlButton::setContentSize(size);
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->setContentSize(size);
    }
}

void EditBox::setAnchorPoint(const Point& anchorPoint)
{
    ControlButton::setAnchorPoint(anchorPoint);
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->setAnchorPoint(anchorPoint);
    }
}

void EditBox::visit(Renderer *renderer, const kmMat4 &parentTransform, bool parentTransformUpdated)
{
    ControlButton::visit(renderer, parentTransform, parentTransformUpdated);
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->visit();
    }
}

void EditBox::onEnter(void)
{
    ControlButton::onEnter();
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->onEnter();
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    this->schedule(schedule_selector(EditBox::updatePosition), CHECK_EDITBOX_POSITION_INTERVAL);
#endif
}

void EditBox::updatePosition(float dt)
{
    if (nullptr != _editBoxImpl) {
        _editBoxImpl->updatePosition(dt);
    }
}


void EditBox::onExit(void)
{
    ControlButton::onExit();
    if (_editBoxImpl != NULL)
    {
        // remove system edit control
        _editBoxImpl->closeKeyboard();
    }
}

static Rect getRect(Node * pNode)
{
	Size contentSize = pNode->getContentSize();
	Rect rect = Rect(0, 0, contentSize.width, contentSize.height);
	return RectApplyTransform(rect, pNode->getNodeToWorldTransform());
}

void EditBox::keyboardWillShow(IMEKeyboardNotificationInfo& info)
{
    // CCLOG("CCEditBox::keyboardWillShow");
    Rect rectTracked = getRect(this);
	// some adjustment for margin between the keyboard and the edit box.
	rectTracked.origin.y -= 4;

    // if the keyboard area doesn't intersect with the tracking node area, nothing needs to be done.
    if (!rectTracked.intersectsRect(info.end))
    {
        CCLOG("needn't to adjust view layout.");
        return;
    }
    
    // assume keyboard at the bottom of screen, calculate the vertical adjustment.
    _adjustHeight = info.end.getMaxY() - rectTracked.getMinY();
    // CCLOG("CCEditBox:needAdjustVerticalPosition(%f)", _adjustHeight);
    
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->doAnimationWhenKeyboardMove(info.duration, _adjustHeight);
    }
}

void EditBox::keyboardDidShow(IMEKeyboardNotificationInfo& info)
{
	
}

void EditBox::keyboardWillHide(IMEKeyboardNotificationInfo& info)
{
    // CCLOG("CCEditBox::keyboardWillHide");
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->doAnimationWhenKeyboardMove(info.duration, -_adjustHeight);
    }
}

void EditBox::keyboardDidHide(IMEKeyboardNotificationInfo& info)
{
	
}

#if CC_ENABLE_SCRIPT_BINDING
void EditBox::registerScriptEditBoxHandler(int handler)
{
    unregisterScriptEditBoxHandler();
    _scriptEditBoxHandler = handler;
}

void EditBox::unregisterScriptEditBoxHandler(void)
{
    if (0 != _scriptEditBoxHandler)
    {
        ScriptEngineManager::getInstance()->getScriptEngine()->removeScriptHandler(_scriptEditBoxHandler);
        _scriptEditBoxHandler = 0;
    }
}
#endif

NS_CC_EXT_END
