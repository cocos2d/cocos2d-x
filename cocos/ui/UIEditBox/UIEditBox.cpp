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
#include "ui/UIHelper.h"

NS_CC_BEGIN

namespace ui {

static const int NORMAL_RENDERER_Z = (-2);
static const int PRESSED_RENDERER_Z = (-2);
static const int DISABLED_RENDERER_Z = (-2);

static const float CHECK_EDITBOX_POSITION_INTERVAL = 0.1f;

EditBox::EditBox()
: _normalRenderer(nullptr)
, _pressedRenderer(nullptr)
, _disabledRenderer(nullptr)
, _normalFileName("")
, _pressedFileName("")
, _disabledFileName("")
, _normalTexType(TextureResType::LOCAL)
, _pressedTexType(TextureResType::LOCAL)
, _disabledTexType(TextureResType::LOCAL)
, _capInsetsNormal(Rect::ZERO)
, _capInsetsPressed(Rect::ZERO)
, _capInsetsDisabled(Rect::ZERO)
, _normalTextureSize(_contentSize)
, _pressedTextureSize(_contentSize)
, _disabledTextureSize(_contentSize)
, _normalTextureLoaded(false)
, _pressedTextureLoaded(false)
, _disabledTextureLoaded(false)
, _normalTextureAdaptDirty(true)
, _pressedTextureAdaptDirty(true)
, _disabledTextureAdaptDirty(true)
, _editBoxImpl(nullptr)
, _delegate(nullptr)
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

void EditBox::openKeyboard() const
{
    _editBoxImpl->openKeyboard();
}

void EditBox::touchDownAction(Ref* /*sender*/, TouchEventType controlEvent)
{
    if (controlEvent == Widget::TouchEventType::ENDED) {
        openKeyboard();
    }
}

EditBox* EditBox::create(const Size& size,
                         const std::string& normalImage,
                         TextureResType texType) {
    return EditBox::create(size, normalImage, "", "", texType);
}

EditBox* EditBox::create(const Size& size,
                         const std::string& normalImage,
                         const std::string& pressedImage /* = "" */,
                         const std::string& disabledImage /* = "" */,
                         TextureResType texType /* = TextureResType::LOCAL */)
{
    EditBox* pRet = new (std::nothrow) EditBox();
    if (pRet != nullptr && pRet->initWithSizeAndTexture(size, normalImage, pressedImage, disabledImage, texType))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}


EditBox* EditBox::create(const cocos2d::Size &size, cocos2d::ui::Scale9Sprite *normalSprite, ui::Scale9Sprite* pressedSprite, Scale9Sprite* disabledSprite)
{
    EditBox* pRet = new (std::nothrow) EditBox();
    if (pRet != nullptr && pRet->initWithSizeAndBackgroundSprite(size, normalSprite, pressedSprite, disabledSprite))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool EditBox::initWithSizeAndBackgroundSprite(const Size& size, Scale9Sprite* normal9SpriteBg)
{
    return initWithSizeAndBackgroundSprite(size, normal9SpriteBg, nullptr, nullptr);
}

bool EditBox::initWithSizeAndBackgroundSprite(const Size& size, Scale9Sprite* normalSprite, Scale9Sprite* pressedSprite, Scale9Sprite* disabledSprite)
{
    if (Widget::init())
    {
        _editBoxImpl = __createSystemEditBox(this);
        _editBoxImpl->initWithSize(size);
        _editBoxImpl->setInputMode(EditBox::InputMode::ANY);

        loadTextureNormal(normalSprite->getResourceName(), normalSprite->getResourceType() == 0 ? TextureResType::LOCAL : TextureResType::PLIST);
        if (pressedSprite != nullptr)
        {
            loadTexturePressed(pressedSprite->getResourceName(), pressedSprite->getResourceType() == 0 ? TextureResType::LOCAL : TextureResType::PLIST);
        }
        if (disabledSprite != nullptr)
        {
            loadTexturePressed(disabledSprite->getResourceName(), disabledSprite->getResourceType() == 0 ? TextureResType::LOCAL : TextureResType::PLIST);
        }

        this->setContentSize(size);

        this->setTouchEnabled(true);

        return true;
    }
    return false;
}

bool EditBox::initWithSizeAndBackgroundSprite(const Size& size,
                                              const std::string& pNormal9SpriteBg,
                                              TextureResType texType)
{
    return initWithSizeAndTexture(size, pNormal9SpriteBg, "", "", texType);
}

bool EditBox::initWithSizeAndTexture(const Size& size,
                                     const std::string& normalImage,
                                     const std::string& pressedImage /* = "" */,
                                     const std::string& disabledImage /* = "" */,
                                     TextureResType texType /* = TextureResType::LOCAL */)
{
    if (Widget::init())
    {
        _editBoxImpl = __createSystemEditBox(this);
        _editBoxImpl->initWithSize(size);
        _editBoxImpl->setInputMode(EditBox::InputMode::ANY);

        loadTextures(normalImage, pressedImage, disabledImage, texType);

        this->setContentSize(size);
        this->setTouchEnabled(true);

        return true;
    }
    return false;
}

void EditBox::initRenderer()
{
    _normalRenderer = Scale9Sprite::create();
    _pressedRenderer = Scale9Sprite::create();
    _disabledRenderer = Scale9Sprite::create();
    _normalRenderer->setRenderingType(Scale9Sprite::RenderingType::SLICE);
    _pressedRenderer->setRenderingType(Scale9Sprite::RenderingType::SLICE);
    _disabledRenderer->setRenderingType(Scale9Sprite::RenderingType::SLICE);

    addProtectedChild(_normalRenderer, NORMAL_RENDERER_Z, -1);
    addProtectedChild(_pressedRenderer, PRESSED_RENDERER_Z, -1);
    addProtectedChild(_disabledRenderer, DISABLED_RENDERER_Z, -1);
}

void EditBox::loadTextures(const std::string& normal,
                           const std::string& pressed,
                           const std::string& disabled,
                           TextureResType texType)
{
    loadTextureNormal(normal, texType);
    loadTexturePressed(pressed, texType);
    loadTextureDisabled(disabled, texType);
}

void EditBox::loadTextureNormal(const std::string& normal,TextureResType texType)
{
    _normalFileName = normal;
    _normalTexType = texType;
    bool textureLoaded = true;
    if (normal.empty())
    {
        _normalRenderer->resetRender();
        textureLoaded = false;
    }
    else
    {
        switch (texType)
        {
            case TextureResType::LOCAL:
                _normalRenderer->initWithFile(normal);
                break;
            case TextureResType::PLIST:
                _normalRenderer->initWithSpriteFrameName(normal);
                break;
            default:
                break;
        }
    }
    //FIXME: https://github.com/cocos2d/cocos2d-x/issues/12249
    if (!_ignoreSize && _customSize.equals(Size::ZERO)) {
        _customSize = _normalRenderer->getContentSize();
    }
    this->setupNormalTexture(textureLoaded);
}

void EditBox::setupNormalTexture(bool textureLoaded)
{
    _normalTextureSize = _normalRenderer->getContentSize();

    this->updateChildrenDisplayedRGBA();

    _normalTextureLoaded = textureLoaded;
    _normalTextureAdaptDirty = true;
}

void EditBox::loadTextureNormal(SpriteFrame* normalSpriteFrame)
{
    _normalRenderer->initWithSpriteFrame(normalSpriteFrame);
    this->setupNormalTexture(nullptr != normalSpriteFrame);
}

void EditBox::loadTexturePressed(const std::string& pressed, TextureResType texType)
{
    _pressedFileName = pressed;
    _pressedTexType = texType;
    bool textureLoaded = true;
    if (pressed.empty())
    {
        _pressedRenderer->resetRender();
        textureLoaded = false;
    }
    else
    {
        switch (texType)
        {
            case TextureResType::LOCAL:
                _pressedRenderer->initWithFile(pressed);
                break;
            case TextureResType::PLIST:
                _pressedRenderer->initWithSpriteFrameName(pressed);
                break;
            default:
                break;
        }
    }
    this->setupPressedTexture(textureLoaded);
}

void EditBox::setupPressedTexture(bool textureLoaded)
{
    _pressedTextureSize = _pressedRenderer->getContentSize();

    this->updateChildrenDisplayedRGBA();

    _pressedTextureLoaded = textureLoaded;
    _pressedTextureAdaptDirty = true;
}

void EditBox::loadTexturePressed(SpriteFrame* pressedSpriteFrame)
{
    _pressedRenderer->initWithSpriteFrame(pressedSpriteFrame);
    this->setupPressedTexture(nullptr != pressedSpriteFrame);
}

void EditBox::loadTextureDisabled(const std::string& disabled,TextureResType texType)
{
    _disabledFileName = disabled;
    _disabledTexType = texType;
    bool textureLoaded = true;
    if (disabled.empty())
    {
        _disabledRenderer->resetRender();
        textureLoaded = false;
    }
    else
    {
        switch (texType)
        {
            case TextureResType::LOCAL:
                _disabledRenderer->initWithFile(disabled);
                break;
            case TextureResType::PLIST:
                _disabledRenderer->initWithSpriteFrameName(disabled);
                break;
            default:
                break;
        }
    }
    this->setupDisabledTexture(textureLoaded);
}

void EditBox::setupDisabledTexture(bool textureLoaded)
{
    _disabledTextureSize = _disabledRenderer->getContentSize();

    this->updateChildrenDisplayedRGBA();

    _disabledTextureLoaded = textureLoaded;
    _disabledTextureAdaptDirty = true;
}

void EditBox::loadTextureDisabled(SpriteFrame* disabledSpriteFrame)
{
    _disabledRenderer->initWithSpriteFrame(disabledSpriteFrame);
    this->setupDisabledTexture(nullptr != disabledSpriteFrame);
}

void EditBox::setCapInsets(const Rect &capInsets)
{
    setCapInsetsNormalRenderer(capInsets);
    setCapInsetsPressedRenderer(capInsets);
    setCapInsetsDisabledRenderer(capInsets);
}

void EditBox::setCapInsetsNormalRenderer(const Rect &capInsets)
{
    _capInsetsNormal = Helper::restrictCapInsetRect(capInsets, this->_normalTextureSize);
    _normalRenderer->setCapInsets(_capInsetsNormal);
}

void EditBox::setCapInsetsPressedRenderer(const Rect &capInsets)
{
    _capInsetsPressed = Helper::restrictCapInsetRect(capInsets, this->_pressedTextureSize);
    _pressedRenderer->setCapInsets(_capInsetsPressed);
}

void EditBox::setCapInsetsDisabledRenderer(const Rect &capInsets)
{
    _capInsetsDisabled = Helper::restrictCapInsetRect(capInsets, this->_disabledTextureSize);
    _disabledRenderer->setCapInsets(_capInsetsDisabled);
}

const Rect& EditBox::getCapInsetsNormalRenderer() const
{
    return _capInsetsNormal;
}

const Rect& EditBox::getCapInsetsPressedRenderer() const
{
    return _capInsetsPressed;
}

const Rect& EditBox::getCapInsetsDisabledRenderer() const
{
    return _capInsetsDisabled;
}

void EditBox::onPressStateChangedToNormal()
{
    _normalRenderer->setVisible(true);
    _pressedRenderer->setVisible(false);
    _disabledRenderer->setVisible(false);
    _normalRenderer->setState(Scale9Sprite::State::NORMAL);
}

void EditBox::onPressStateChangedToPressed()
{
    _normalRenderer->setState(Scale9Sprite::State::NORMAL);

    if (_pressedTextureLoaded)
    {
        _normalRenderer->setVisible(false);
        _pressedRenderer->setVisible(true);
        _disabledRenderer->setVisible(false);
    }
    else
    {
        _normalRenderer->setVisible(true);
        _pressedRenderer->setVisible(true);
        _disabledRenderer->setVisible(false);
    }
}

void EditBox::onPressStateChangedToDisabled()
{
    //if disabled resource is null
    if (!_disabledTextureLoaded)
    {
        if (_normalTextureLoaded)
        {
            _normalRenderer->setState(Scale9Sprite::State::GRAY);
        }
    }
    else
    {
        _normalRenderer->setVisible(false);
        _disabledRenderer->setVisible(true);
    }

    _pressedRenderer->setVisible(false);
}

void EditBox::releaseUpEvent()
{
    Widget::releaseUpEvent();
    openKeyboard();
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

void EditBox::onSizeChanged()
{
    Widget::onSizeChanged();
    _normalTextureAdaptDirty = true;
    _pressedTextureAdaptDirty = true;
    _disabledTextureAdaptDirty = true;
}

void EditBox::adaptRenderers()
{
    if (_normalTextureAdaptDirty)
    {
        normalTextureScaleChangedWithSize();
        _normalTextureAdaptDirty = false;
    }

    if (_pressedTextureAdaptDirty)
    {
        pressedTextureScaleChangedWithSize();
        _pressedTextureAdaptDirty = false;
    }

    if (_disabledTextureAdaptDirty)
    {
        disabledTextureScaleChangedWithSize();
        _disabledTextureAdaptDirty = false;
    }
}

void EditBox::normalTextureScaleChangedWithSize()
{
    _normalRenderer->setPreferredSize(_contentSize);
    _normalRenderer->setPosition(_contentSize.width / 2.0f, _contentSize.height / 2.0f);
}

void EditBox::pressedTextureScaleChangedWithSize()
{
    _pressedRenderer->setPreferredSize(_contentSize);
    _pressedRenderer->setPosition(_contentSize.width / 2.0f, _contentSize.height / 2.0f);
}

void EditBox::disabledTextureScaleChangedWithSize()
{
    _disabledRenderer->setPreferredSize(_contentSize);
    _disabledRenderer->setPosition(_contentSize.width / 2.0f, _contentSize.height / 2.0f);
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
