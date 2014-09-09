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

#include "UIEditBox.h"
#include "UIEditBoxImpl.h"

NS_CC_BEGIN

namespace ui {

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
, _backgroundSprite(nullptr)
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


void EditBox::touchDownAction(Ref *sender, TouchEventType controlEvent)
{
    if (controlEvent == Widget::TouchEventType::ENDED) {
        _editBoxImpl->openKeyboard();
    }
}

EditBox* EditBox::create(const Size& size,
                         const std::string& normalSprite,
                        TextureResType texType /*= TextureResType::LOCAL*/)
{
    EditBox* pRet = new EditBox();
    
    if (pRet != nullptr && pRet->initWithSizeAndBackgroundSprite(size, normalSprite, texType))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}
    
    
EditBox* EditBox::create(const cocos2d::Size &size, cocos2d::ui::Scale9Sprite *normalSprite, ui::Scale9Sprite *pressedSprite, Scale9Sprite* disabledSprite)
{
    EditBox* pRet = new (std::nothrow) EditBox();
    
    if (pRet != nullptr && pRet->initWithSizeAndBackgroundSprite(size, normalSprite))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}
    
bool EditBox::initWithSizeAndBackgroundSprite(const cocos2d::Size &size, cocos2d::ui::Scale9Sprite *pNormal9SpriteBg)
{
    if (Widget::init())
    {
        _editBoxImpl = __createSystemEditBox(this);
        _editBoxImpl->initWithSize(size);
        _editBoxImpl->setInputMode(EditBox::InputMode::ANY);
        
        _backgroundSprite = pNormal9SpriteBg;
        
        this->setContentSize(size);
        this->setPosition(Vec2(0, 0));
        
        _backgroundSprite->setPosition(Vec2(_contentSize.width/2, _contentSize.height/2));
        _backgroundSprite->setContentSize(size);
        this->addProtectedChild(_backgroundSprite);
        
        this->setTouchEnabled(true);
        
        this->addTouchEventListener(CC_CALLBACK_2(EditBox::touchDownAction, this));
        
        return true;
    }
    return false;
}


bool EditBox::initWithSizeAndBackgroundSprite(const Size& size,
                                                        const std::string& pNormal9SpriteBg,
                                                        TextureResType texType)
{
    if (Widget::init())
    {
        _editBoxImpl = __createSystemEditBox(this);
        _editBoxImpl->initWithSize(size);
        _editBoxImpl->setInputMode(EditBox::InputMode::ANY);
       
        if (texType == Widget::TextureResType::LOCAL)
        {
            _backgroundSprite = Scale9Sprite::create(pNormal9SpriteBg);
        }
        else
        {
            _backgroundSprite = Scale9Sprite::createWithSpriteFrameName(pNormal9SpriteBg);
        }
        this->setContentSize(size);
        this->setPosition(Vec2(0, 0));
        
        _backgroundSprite->setPosition(Vec2(_contentSize.width/2, _contentSize.height/2));
        _backgroundSprite->setContentSize(size);
        this->addProtectedChild(_backgroundSprite);
        
        this->setTouchEnabled(true);
        
        this->addTouchEventListener(CC_CALLBACK_2(EditBox::touchDownAction, this));
        
        return true;
    }
    return false;
}

void EditBox::setDelegate(EditBoxDelegate* pDelegate)
{
    _delegate = pDelegate;
    if (_editBoxImpl != nullptr)
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
    if (pText != nullptr)
    {
        _text = pText;
        if (_editBoxImpl != nullptr)
        {
            _editBoxImpl->setText(pText);
        }
    }
}

const char* EditBox::getText(void)
{
    if (_editBoxImpl != nullptr)
    {
		const char* pText = _editBoxImpl->getText();
		if(pText != nullptr)
			return pText;
    }
    
    return "";
}

void EditBox::setFont(const char* pFontName, int fontSize)
{
    _fontName = pFontName;
    _fontSize = fontSize;
    if (pFontName != nullptr)
    {
        if (_editBoxImpl != nullptr)
        {
            _editBoxImpl->setFont(pFontName, fontSize);
        }
    }
}

void EditBox::setFontName(const char* pFontName)
{
    _fontName = pFontName;
    if (_editBoxImpl != nullptr && _fontSize != -1)
    {
        _editBoxImpl->setFont(pFontName, _fontSize);
    }
}

void EditBox::setFontSize(int fontSize)
{
    _fontSize = fontSize;
    if (_editBoxImpl != nullptr && _fontName.length() > 0)
    {
        _editBoxImpl->setFont(_fontName.c_str(), _fontSize);
    }
}

void EditBox::setFontColor(const Color3B& color)
{
    _colText = color;
    if (_editBoxImpl != nullptr)
    {
        _editBoxImpl->setFontColor(color);
    }
}

void EditBox::setPlaceholderFont(const char* pFontName, int fontSize)
{
    _placeholderFontName = pFontName;
    _placeholderFontSize = fontSize;
    if (pFontName != nullptr)
    {
        if (_editBoxImpl != nullptr)
        {
            _editBoxImpl->setPlaceholderFont(pFontName, fontSize);
        }
    }
}

void EditBox::setPlaceholderFontName(const char* pFontName)
{
    _placeholderFontName = pFontName;
    if (_editBoxImpl != nullptr && _placeholderFontSize != -1)
    {
        _editBoxImpl->setPlaceholderFont(pFontName, _fontSize);
    }
}

void EditBox::setPlaceholderFontSize(int fontSize)
{
    _placeholderFontSize = fontSize;
    if (_editBoxImpl != nullptr && _placeholderFontName.length() > 0)
    {
        _editBoxImpl->setPlaceholderFont(_placeholderFontName.c_str(), fontSize);
    }
}

void EditBox::setPlaceholderFontColor(const Color3B& color)
{
    _colText = color;
    if (_editBoxImpl != nullptr)
    {
        _editBoxImpl->setPlaceholderFontColor(color);
    }
}

void EditBox::setPlaceHolder(const char* pText)
{
    if (pText != nullptr)
    {
        _placeHolder = pText;
        if (_editBoxImpl != nullptr)
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
    if (_editBoxImpl != nullptr)
    {
        _editBoxImpl->setInputMode(inputMode);
    }
}

void EditBox::setMaxLength(int maxLength)
{
    _maxLength = maxLength;
    if (_editBoxImpl != nullptr)
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
    if (_editBoxImpl != nullptr)
    {
        _editBoxImpl->setInputFlag(inputFlag);
    }
}

void EditBox::setReturnType(EditBox::KeyboardReturnType returnType)
{
    if (_editBoxImpl != nullptr)
    {
        _editBoxImpl->setReturnType(returnType);
    }
}

/* override function */
void EditBox::setPosition(const Vec2& pos)
{
    Widget::setPosition(pos);
    if (_editBoxImpl != nullptr)
    {
        _editBoxImpl->setPosition(pos);
    }
}

void EditBox::setVisible(bool visible)
{
    Widget::setVisible(visible);
    if (_editBoxImpl != nullptr)
    {
        _editBoxImpl->setVisible(visible);
    }
}

void EditBox::setContentSize(const Size& size)
{
    Widget::setContentSize(size);
    if (_editBoxImpl != nullptr)
    {
        _editBoxImpl->setContentSize(size);
    }
}
    
void EditBox::adaptRenderers()
{
    if (_contentSizeDirty)
    {
        _backgroundSprite->setContentSize(_contentSize);
        _backgroundSprite->setPosition(Vec2(_contentSize.width/2, _contentSize.height/2));
    }
}

void EditBox::setAnchorPoint(const Vec2& anchorPoint)
{
    Widget::setAnchorPoint(anchorPoint);
    if (_editBoxImpl != nullptr)
    {
        _editBoxImpl->setAnchorPoint(anchorPoint);
    }
}

void EditBox::visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    Widget::visit(renderer, parentTransform, parentFlags);
    if (_editBoxImpl != nullptr)
    {
        _editBoxImpl->visit();
    }
}

void EditBox::onEnter(void)
{
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeJavascript)
    {
        if (ScriptEngineManager::sendNodeEventToJSExtended(this, kNodeOnEnter))
            return;
    }
#endif
    
    Widget::onEnter();
    if (_editBoxImpl != nullptr)
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
    Widget::onExit();
    if (_editBoxImpl != nullptr)
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
    
    if (_editBoxImpl != nullptr)
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
    if (_editBoxImpl != nullptr)
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

}

NS_CC_END
