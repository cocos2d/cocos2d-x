/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen
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

#include "ui/UIEditBox/UIEditBox.h"
#include "ui/UIEditBox/UIEditBoxImpl.h"

NS_CC_BEGIN

namespace ui {

static const float CHECK_EDITBOX_POSITION_INTERVAL = 0.1f;

EditBox::EditBox()
: _editBoxImpl(nullptr)
, _delegate(nullptr)
, _backgroundSprite(nullptr)
, _adjustHeight(0.f)
#if CC_ENABLE_SCRIPT_BINDING
, _scriptEditBoxHandler(0)
#endif
{
}

EditBox::~EditBox()
{
    CC_SAFE_DELETE(_editBoxImpl);
#if CC_ENABLE_SCRIPT_BINDING
    unregisterScriptEditBoxHandler();
#endif
}


void EditBox::touchDownAction(Ref* /*sender*/, TouchEventType controlEvent)
{
    if (controlEvent == Widget::TouchEventType::ENDED) {
        _editBoxImpl->openKeyboard();
    }
}

EditBox* EditBox::create(const Size& size,
                         const std::string& normalSprite,
                        TextureResType texType /*= TextureResType::LOCAL*/)
{
    EditBox* pRet = new (std::nothrow) EditBox();
    
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
    
    
EditBox* EditBox::create(const cocos2d::Size &size, cocos2d::ui::Scale9Sprite *normalSprite, ui::Scale9Sprite* /*pressedSprite*/, Scale9Sprite* /*disabledSprite*/)
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
        if (_editBoxImpl != nullptr)
        {
            _editBoxImpl->setText(pText);
        }
    }
}

const char* EditBox::getText() const
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
    CCASSERT(pFontName != nullptr, "fontName can't be nullptr");
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
    CCASSERT(pFontName != nullptr, "fontName can't be nullptr");
    if (_editBoxImpl != nullptr)
    {
        _editBoxImpl->setFont(pFontName, _editBoxImpl->getFontSize());
    }
}

const char* EditBox::getFontName() const
{
    if (_editBoxImpl != nullptr)
    {
        return _editBoxImpl->getFontName();
    }
    return "";
}

void EditBox::setFontSize(int fontSize)
{
    if (_editBoxImpl != nullptr)
    {
        _editBoxImpl->setFont(_editBoxImpl->getFontName(), fontSize);
    }
}

int EditBox::getFontSize() const
{
    if (_editBoxImpl != nullptr)
    {
        return _editBoxImpl->getFontSize();
    }
    return -1;
}
void EditBox::setFontColor(const Color3B& color)
{
    setFontColor(Color4B(color));
}

void EditBox::setFontColor(const Color4B& color)
{
    if (_editBoxImpl != nullptr)
    {
        _editBoxImpl->setFontColor(color);
    }
}

const Color4B& EditBox::getFontColor() const
{
    if (_editBoxImpl != nullptr)
    {
        return _editBoxImpl->getFontColor();
    }
    return Color4B::WHITE;
}

void EditBox::setPlaceholderFont(const char* pFontName, int fontSize)
{
    CCASSERT(pFontName != nullptr, "fontName can't be nullptr");
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
    CCASSERT(pFontName != nullptr, "fontName can't be nullptr");
    if (_editBoxImpl != nullptr)
    {
        _editBoxImpl->setPlaceholderFont(pFontName, _editBoxImpl->getPlaceholderFontSize());
    }
}

const char* EditBox::getPlaceholderFontName() const
{
    if (_editBoxImpl != nullptr)
    {
        return _editBoxImpl->getPlaceholderFontName();
    }
    return "";
}

void EditBox::setPlaceholderFontSize(int fontSize)
{
    if (_editBoxImpl != nullptr)
    {
        _editBoxImpl->setPlaceholderFont(_editBoxImpl->getPlaceholderFontName(), fontSize);
    }
}

int EditBox::getPlaceholderFontSize() const
{
    if (_editBoxImpl != nullptr)
    {
        return _editBoxImpl->getPlaceholderFontSize();
    }
    return -1;
}

void EditBox::setPlaceholderFontColor(const Color3B& color)
{
    setPlaceholderFontColor(Color4B(color));
}

void EditBox::setPlaceholderFontColor(const Color4B& color)
{
    if (_editBoxImpl != nullptr)
    {
        _editBoxImpl->setPlaceholderFontColor(color);
    }
}

const Color4B& EditBox::getPlaceholderFontColor() const
{
    if (_editBoxImpl != nullptr)
    {
        return _editBoxImpl->getPlaceholderFontColor();
    }
    return Color4B::GRAY;
}

void EditBox::setPlaceHolder(const char* pText)
{
    if (pText != nullptr)
    {
        if (_editBoxImpl != nullptr)
        {
            _editBoxImpl->setPlaceHolder(pText);
        }
    }
}

const char* EditBox::getPlaceHolder() const
{
    if (_editBoxImpl != nullptr)
    {
        return _editBoxImpl->getPlaceHolder();
    }
    return "";
}

void EditBox::setInputMode(EditBox::InputMode inputMode)
{
    if (_editBoxImpl != nullptr)
    {
        _editBoxImpl->setInputMode(inputMode);
    }
}

EditBox::InputMode EditBox::getInputMode() const
{
    if (_editBoxImpl != nullptr)
    {
        return _editBoxImpl->getInputMode();
    }
    return InputMode::SINGLE_LINE;
}

void EditBox::setMaxLength(int maxLength)
{
    if (_editBoxImpl != nullptr)
    {
        _editBoxImpl->setMaxLength(maxLength);
    }
}


int EditBox::getMaxLength()
{
    if (_editBoxImpl != nullptr)
    {
        return _editBoxImpl->getMaxLength();
    }
    return -1;
}

void EditBox::setInputFlag(EditBox::InputFlag inputFlag)
{
    if (_editBoxImpl != nullptr)
    {
        _editBoxImpl->setInputFlag(inputFlag);
    }
}

EditBox::InputFlag EditBox::getInputFlag() const
{
    if (_editBoxImpl != nullptr)
    {
        return _editBoxImpl->getInputFlag();
    }
    return InputFlag::LOWERCASE_ALL_CHARACTERS;
}

void EditBox::setReturnType(EditBox::KeyboardReturnType returnType)
{
    if (_editBoxImpl != nullptr)
    {
        _editBoxImpl->setReturnType(returnType);
    }
}

EditBox::KeyboardReturnType EditBox::getReturnType() const
{
    if (_editBoxImpl != nullptr)
    {
        return _editBoxImpl->getReturnType();
    }
    return KeyboardReturnType::DEFAULT;
}

void EditBox::setTextHorizontalAlignment(TextHAlignment alignment)
{
    if (_editBoxImpl != nullptr)
    {
        _editBoxImpl->setTextHorizontalAlignment(alignment);
    }
}

TextHAlignment EditBox::getTextHorizontalAlignment() const
{
    if (_editBoxImpl != nullptr)
    {
        return _editBoxImpl->getTextHorizontalAlignment();
    }
    return TextHAlignment::LEFT;
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

std::string EditBox::getDescription() const
{
    return "EditBox";
}

void EditBox::draw(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    Widget::draw(renderer, parentTransform, parentFlags);
    if (_editBoxImpl != nullptr)
    {
        _editBoxImpl->draw(renderer, parentTransform, parentFlags & FLAGS_TRANSFORM_DIRTY);
    }
}

void EditBox::onEnter()
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
    this->schedule(CC_SCHEDULE_SELECTOR(EditBox::updatePosition), CHECK_EDITBOX_POSITION_INTERVAL);
#endif
}

void EditBox::updatePosition(float dt)
{
    if (nullptr != _editBoxImpl) {
        _editBoxImpl->updatePosition(dt);
    }
}


void EditBox::onExit()
{
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeJavascript)
    {
        if (ScriptEngineManager::sendNodeEventToJSExtended(this, kNodeOnExit))
            return;
    }
#endif
    
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

void EditBox::keyboardDidShow(IMEKeyboardNotificationInfo& /*info*/)
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

void EditBox::keyboardDidHide(IMEKeyboardNotificationInfo& /*info*/)
{
	
}

#if CC_ENABLE_SCRIPT_BINDING
void EditBox::registerScriptEditBoxHandler(int handler)
{
    unregisterScriptEditBoxHandler();
    _scriptEditBoxHandler = handler;
}

void EditBox::unregisterScriptEditBoxHandler()
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
