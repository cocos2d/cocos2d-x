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

CCEditBox::CCEditBox(void)
: _editBoxImpl(NULL)
, _delegate(NULL)
, _editBoxInputMode(kEditBoxInputModeSingleLine)
, _editBoxInputFlag(kEditBoxInputFlagInitialCapsAllCharacters)
, _keyboardReturnType(kKeyboardReturnTypeDefault)
, _fontSize(-1)
, _placeholderFontSize(-1)
, _colText(ccWHITE)
, _colPlaceHolder(ccGRAY)
, _maxLength(0)
, _adjustHeight(0.0f)
, _scriptEditBoxHandler(0)
{
}

CCEditBox::~CCEditBox(void)
{
    CC_SAFE_DELETE(_editBoxImpl);
    unregisterScriptEditBoxHandler();
}


void CCEditBox::touchDownAction(CCObject *sender, CCControlEvent controlEvent)
{
    _editBoxImpl->openKeyboard();
}

CCEditBox* CCEditBox::create(const CCSize& size, CCScale9Sprite* pNormal9SpriteBg, CCScale9Sprite* pPressed9SpriteBg/* = NULL*/, CCScale9Sprite* pDisabled9SpriteBg/* = NULL*/)
{
    CCEditBox* pRet = new CCEditBox();
    
    if (pRet != NULL && pRet->initWithSizeAndBackgroundSprite(size, pNormal9SpriteBg))
    {
        if (pPressed9SpriteBg != NULL)
        {
            pRet->setBackgroundSpriteForState(pPressed9SpriteBg, CCControlStateHighlighted);
        }
        
        if (pDisabled9SpriteBg != NULL)
        {
            pRet->setBackgroundSpriteForState(pDisabled9SpriteBg, CCControlStateDisabled);
        }
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

bool CCEditBox::initWithSizeAndBackgroundSprite(const CCSize& size, CCScale9Sprite* pPressed9SpriteBg)
{
    if (CCControlButton::initWithBackgroundSprite(pPressed9SpriteBg))
    {
        _editBoxImpl = __createSystemEditBox(this);
        _editBoxImpl->initWithSize(size);
        
        this->setZoomOnTouchDown(false);
        this->setPreferredSize(size);
        this->setPosition(ccp(0, 0));
        this->addTargetWithActionForControlEvent(this, cccontrol_selector(CCEditBox::touchDownAction), CCControlEventTouchUpInside);
        
        return true;
    }
    return false;
}

void CCEditBox::setDelegate(CCEditBoxDelegate* pDelegate)
{
    _delegate = pDelegate;
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->setDelegate(pDelegate);
    }
}

CCEditBoxDelegate* CCEditBox::getDelegate()
{
    return _delegate;
}

void CCEditBox::setText(const char* pText)
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

const char* CCEditBox::getText(void)
{
    if (_editBoxImpl != NULL)
    {
		const char* pText = _editBoxImpl->getText();
		if(pText != NULL)
			return pText;
    }
    
    return "";
}

void CCEditBox::setFont(const char* pFontName, int fontSize)
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

void CCEditBox::setFontName(const char* pFontName)
{
    _fontName = pFontName;
    if (_editBoxImpl != NULL && _fontSize != -1)
    {
        _editBoxImpl->setFont(pFontName, _fontSize);
    }
}

void CCEditBox::setFontSize(int fontSize)
{
    _fontSize = fontSize;
    if (_editBoxImpl != NULL && _fontName.length() > 0)
    {
        _editBoxImpl->setFont(_fontName.c_str(), _fontSize);
    }
}

void CCEditBox::setFontColor(const ccColor3B& color)
{
    _colText = color;
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->setFontColor(color);
    }
}

void CCEditBox::setPlaceholderFont(const char* pFontName, int fontSize)
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

void CCEditBox::setPlaceholderFontName(const char* pFontName)
{
    _placeholderFontName = pFontName;
    if (_editBoxImpl != NULL && _placeholderFontSize != -1)
    {
        _editBoxImpl->setPlaceholderFont(pFontName, _fontSize);
    }
}

void CCEditBox::setPlaceholderFontSize(int fontSize)
{
    _placeholderFontSize = fontSize;
    if (_editBoxImpl != NULL && _placeholderFontName.length() > 0)
    {
        _editBoxImpl->setPlaceholderFont(_placeholderFontName.c_str(), _fontSize);
    }
}

void CCEditBox::setPlaceholderFontColor(const ccColor3B& color)
{
    _colText = color;
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->setPlaceholderFontColor(color);
    }
}

void CCEditBox::setPlaceHolder(const char* pText)
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

const char* CCEditBox::getPlaceHolder(void)
{
    return _placeHolder.c_str();
}

void CCEditBox::setInputMode(EditBoxInputMode inputMode)
{
    _editBoxInputMode = inputMode;
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->setInputMode(inputMode);
    }
}

void CCEditBox::setMaxLength(int maxLength)
{
    _maxLength = maxLength;
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->setMaxLength(maxLength);
    }
}


int CCEditBox::getMaxLength()
{
    return _maxLength;
}

void CCEditBox::setInputFlag(EditBoxInputFlag inputFlag)
{
    _editBoxInputFlag = inputFlag;
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->setInputFlag(inputFlag);
    }
}

void CCEditBox::setReturnType(KeyboardReturnType returnType)
{
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->setReturnType(returnType);
    }
}

/* override function */
void CCEditBox::setPosition(const CCPoint& pos)
{
    CCControlButton::setPosition(pos);
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->setPosition(pos);
    }
}

void CCEditBox::setVisible(bool visible)
{
    CCControlButton::setVisible(visible);
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->setVisible(visible);
    }
}

void CCEditBox::setContentSize(const CCSize& size)
{
    CCControlButton::setContentSize(size);
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->setContentSize(size);
    }
}

void CCEditBox::setAnchorPoint(const CCPoint& anchorPoint)
{
    CCControlButton::setAnchorPoint(anchorPoint);
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->setAnchorPoint(anchorPoint);
    }
}

void CCEditBox::visit(void)
{
    CCControlButton::visit();
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->visit();
    }
}

void CCEditBox::onEnter(void)
{
    CCControlButton::onEnter();
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->onEnter();
    }
}

void CCEditBox::onExit(void)
{
    CCControlButton::onExit();
    if (_editBoxImpl != NULL)
    {
        // remove system edit control
        _editBoxImpl->closeKeyboard();
    }
}

static CCRect getRect(CCNode * pNode)
{
	CCSize contentSize = pNode->getContentSize();
	CCRect rect = CCRectMake(0, 0, contentSize.width, contentSize.height);
	return CCRectApplyAffineTransform(rect, pNode->nodeToWorldTransform());
}

void CCEditBox::keyboardWillShow(CCIMEKeyboardNotificationInfo& info)
{
    // CCLOG("CCEditBox::keyboardWillShow");
    CCRect rectTracked = getRect(this);
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

void CCEditBox::keyboardDidShow(CCIMEKeyboardNotificationInfo& info)
{
	
}

void CCEditBox::keyboardWillHide(CCIMEKeyboardNotificationInfo& info)
{
    // CCLOG("CCEditBox::keyboardWillHide");
    if (_editBoxImpl != NULL)
    {
        _editBoxImpl->doAnimationWhenKeyboardMove(info.duration, -_adjustHeight);
    }
}

void CCEditBox::keyboardDidHide(CCIMEKeyboardNotificationInfo& info)
{
	
}

void CCEditBox::registerScriptEditBoxHandler(int handler)
{
    unregisterScriptEditBoxHandler();
    _scriptEditBoxHandler = handler;
}

void CCEditBox::unregisterScriptEditBoxHandler(void)
{
    if (0 != _scriptEditBoxHandler)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(_scriptEditBoxHandler);
        _scriptEditBoxHandler = 0;
    }
}


NS_CC_EXT_END
