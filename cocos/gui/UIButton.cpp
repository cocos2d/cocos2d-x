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

#include "gui/UIButton.h"
#include "extensions/GUI/CCControlExtension/CCScale9Sprite.h"

namespace gui {

#define NORMALRENDERERZ (0)
#define PRESSEDRENDERERZ (0)
#define DISABLEDRENDERERZ (0)
#define TITLERENDERERZ (1)
    
UIButton::UIButton():
_buttonNormalRenderer(nullptr),
_buttonClickedRenderer(nullptr),
_buttonDisableRenderer(nullptr),
_titleRenderer(nullptr),
_normalFileName(""),
_clickedFileName(""),
_disabledFileName(""),
_prevIgnoreSize(true),
_scale9Enabled(false),
_capInsetsNormal(cocos2d::Rect::ZERO),
_capInsetsPressed(cocos2d::Rect::ZERO),
_capInsetsDisabled(cocos2d::Rect::ZERO),
_normalTexType(UI_TEX_TYPE_LOCAL),
_pressedTexType(UI_TEX_TYPE_LOCAL),
_disabledTexType(UI_TEX_TYPE_LOCAL),
_normalTextureSize(_size),
_pressedTextureSize(_size),
_disabledTextureSize(_size),
_pressedActionEnabled(false),
_titleColor(cocos2d::Color3B::WHITE)
{
    
}

UIButton::~UIButton()
{
}

UIButton* UIButton::create()
{
    UIButton* widget = new UIButton();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

bool UIButton::init()
{
    if (UIWidget::init())
    {
        return true;
    }
    return false;
}

void UIButton::initRenderer()
{
    UIWidget::initRenderer();
    _buttonNormalRenderer = cocos2d::Sprite::create();
    _buttonClickedRenderer = cocos2d::Sprite::create();
    _buttonDisableRenderer = cocos2d::Sprite::create();
    _titleRenderer = cocos2d::LabelTTF::create();
    _renderer->addChild(_buttonNormalRenderer,NORMALRENDERERZ);
    _renderer->addChild(_buttonClickedRenderer,PRESSEDRENDERERZ);
    _renderer->addChild(_buttonDisableRenderer,DISABLEDRENDERERZ);
    _renderer->addChild(_titleRenderer,TITLERENDERERZ);
}

void UIButton::setScale9Enabled(bool able)
{
    if (_scale9Enabled == able)
    {
        return;
    }
    _brightStyle = BRIGHT_NONE;
    _scale9Enabled = able;

    
    _renderer->removeChild(_buttonNormalRenderer, true);
    _renderer->removeChild(_buttonClickedRenderer, true);
    _renderer->removeChild(_buttonDisableRenderer, true);
    
    _buttonNormalRenderer = nullptr;
    _buttonClickedRenderer = nullptr;
    _buttonDisableRenderer = nullptr;
    if (_scale9Enabled)
    {
        _buttonNormalRenderer = cocos2d::extension::Scale9Sprite::create();
        _buttonClickedRenderer = cocos2d::extension::Scale9Sprite::create();
        _buttonDisableRenderer = cocos2d::extension::Scale9Sprite::create();
    }
    else
    {
        _buttonNormalRenderer = cocos2d::Sprite::create();
        _buttonClickedRenderer = cocos2d::Sprite::create();
        _buttonDisableRenderer = cocos2d::Sprite::create();
    }

    loadTextureNormal(_normalFileName.c_str(), _normalTexType);
    loadTexturePressed(_clickedFileName.c_str(), _pressedTexType);
    loadTextureDisabled(_disabledFileName.c_str(), _disabledTexType);
    _renderer->addChild(_buttonNormalRenderer,NORMALRENDERERZ);
    _renderer->addChild(_buttonClickedRenderer,PRESSEDRENDERERZ);
    _renderer->addChild(_buttonDisableRenderer,DISABLEDRENDERERZ);
    if (_scale9Enabled)
    {
        bool ignoreBefore = _ignoreSize;
        ignoreContentAdaptWithSize(false);
        _prevIgnoreSize = ignoreBefore;
    }
    else
    {
        ignoreContentAdaptWithSize(_prevIgnoreSize);
    }
    setCapInsetsNormalRenderer(_capInsetsNormal);
    setCapInsetsPressedRenderer(_capInsetsPressed);
    setCapInsetsDisabledRenderer(_capInsetsDisabled);
    setBright(_bright);
}

void UIButton::ignoreContentAdaptWithSize(bool ignore)
{
    if (!_scale9Enabled || (_scale9Enabled && !ignore))
    {
        UIWidget::ignoreContentAdaptWithSize(ignore);
        _prevIgnoreSize = ignore;
    }
}

void UIButton::loadTextures(const char* normal,const char* selected,const char* disabled,TextureResType texType)
{
    loadTextureNormal(normal,texType);
    loadTexturePressed(selected,texType);
    loadTextureDisabled(disabled,texType);
}

void UIButton::loadTextureNormal(const char* normal,TextureResType texType)
{
    if (!normal || strcmp(normal, "") == 0)
    {
        return;
    }
    _normalFileName = normal;
    _normalTexType = texType;
    if (_scale9Enabled)
    {
        switch (_normalTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<cocos2d::extension::Scale9Sprite*>(_buttonNormalRenderer)->initWithFile(normal);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<cocos2d::extension::Scale9Sprite*>(_buttonNormalRenderer)->initWithSpriteFrameName(normal);
                break;
            default:
                break;
        }
        dynamic_cast<cocos2d::extension::Scale9Sprite*>(_buttonNormalRenderer)->setColor(getColor());
        dynamic_cast<cocos2d::extension::Scale9Sprite*>(_buttonNormalRenderer)->setOpacity(getOpacity());
        dynamic_cast<cocos2d::extension::Scale9Sprite*>(_buttonNormalRenderer)->setCapInsets(_capInsetsNormal);
    }
    else
    {
        switch (_normalTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<cocos2d::Sprite*>(_buttonNormalRenderer)->initWithFile(normal);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<cocos2d::Sprite*>(_buttonNormalRenderer)->initWithSpriteFrameName(normal);
                break;
            default:
                break;
        }
        dynamic_cast<cocos2d::Sprite*>(_buttonNormalRenderer)->setColor(getColor());
        dynamic_cast<cocos2d::Sprite*>(_buttonNormalRenderer)->setOpacity(getOpacity());
    }
    _normalTextureSize = _buttonNormalRenderer->getContentSize();
    updateAnchorPoint();
    normalTextureScaleChangedWithSize();
}

void UIButton::loadTexturePressed(const char* selected,TextureResType texType)
{
    if (!selected || strcmp(selected, "") == 0)
    {
        return;
    }
    _clickedFileName = selected;
    _pressedTexType = texType;
    if (_scale9Enabled)
    {
        switch (_pressedTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<cocos2d::extension::Scale9Sprite*>(_buttonClickedRenderer)->initWithFile(selected);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<cocos2d::extension::Scale9Sprite*>(_buttonClickedRenderer)->initWithSpriteFrameName(selected);
                break;
            default:
                break;
        }
        dynamic_cast<cocos2d::extension::Scale9Sprite*>(_buttonClickedRenderer)->setColor(getColor());
        dynamic_cast<cocos2d::extension::Scale9Sprite*>(_buttonClickedRenderer)->setOpacity(getOpacity());
        dynamic_cast<cocos2d::extension::Scale9Sprite*>(_buttonClickedRenderer)->setCapInsets(_capInsetsPressed);
    }
    else
    {
        switch (_pressedTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<cocos2d::Sprite*>(_buttonClickedRenderer)->initWithFile(selected);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<cocos2d::Sprite*>(_buttonClickedRenderer)->initWithSpriteFrameName(selected);
                break;
            default:
                break;
        }
        dynamic_cast<cocos2d::Sprite*>(_buttonClickedRenderer)->setColor(getColor());
        dynamic_cast<cocos2d::Sprite*>(_buttonClickedRenderer)->setOpacity(getOpacity());
    }
    _pressedTextureSize = _buttonClickedRenderer->getContentSize();
    updateAnchorPoint();
    pressedTextureScaleChangedWithSize();
}

void UIButton::loadTextureDisabled(const char* disabled,TextureResType texType)
{
    if (!disabled || strcmp(disabled, "") == 0)
    {
        return;
    }
    _disabledFileName = disabled;
    _disabledTexType = texType;
    if (_scale9Enabled)
    {
        switch (_disabledTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<cocos2d::extension::Scale9Sprite*>(_buttonDisableRenderer)->initWithFile(disabled);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<cocos2d::extension::Scale9Sprite*>(_buttonDisableRenderer)->initWithSpriteFrameName(disabled);
                break;
            default:
                break;
        }
        dynamic_cast<cocos2d::extension::Scale9Sprite*>(_buttonDisableRenderer)->setColor(getColor());
        dynamic_cast<cocos2d::extension::Scale9Sprite*>(_buttonDisableRenderer)->setOpacity(getOpacity());
        dynamic_cast<cocos2d::extension::Scale9Sprite*>(_buttonDisableRenderer)->setCapInsets(_capInsetsDisabled);
    }
    else
    {
        switch (_disabledTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<cocos2d::Sprite*>(_buttonDisableRenderer)->initWithFile(disabled);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<cocos2d::Sprite*>(_buttonDisableRenderer)->initWithSpriteFrameName(disabled);
                break;
            default:
                break;
        }
        dynamic_cast<cocos2d::Sprite*>(_buttonDisableRenderer)->setColor(getColor());
        dynamic_cast<cocos2d::Sprite*>(_buttonDisableRenderer)->setOpacity(getOpacity());
    }
    _disabledTextureSize = _buttonDisableRenderer->getContentSize();
    updateAnchorPoint();
    disabledTextureScaleChangedWithSize();
}

void UIButton::setCapInsets(const cocos2d::Rect &capInsets)
{
    setCapInsetsNormalRenderer(capInsets);
    setCapInsetsPressedRenderer(capInsets);
    setCapInsetsDisabledRenderer(capInsets);
}

void UIButton::setCapInsetsNormalRenderer(const cocos2d::Rect &capInsets)
{
    _capInsetsNormal = capInsets;
    if (!_scale9Enabled)
    {
        return;
    }
    dynamic_cast<cocos2d::extension::Scale9Sprite*>(_buttonNormalRenderer)->setCapInsets(capInsets);
}

void UIButton::setCapInsetsPressedRenderer(const cocos2d::Rect &capInsets)
{
    _capInsetsPressed = capInsets;
    if (!_scale9Enabled)
    {
        return;
    }
    dynamic_cast<cocos2d::extension::Scale9Sprite*>(_buttonClickedRenderer)->setCapInsets(capInsets);
}

void UIButton::setCapInsetsDisabledRenderer(const cocos2d::Rect &capInsets)
{
    _capInsetsDisabled = capInsets;
    if (!_scale9Enabled)
    {
        return;
    }
    dynamic_cast<cocos2d::extension::Scale9Sprite*>(_buttonDisableRenderer)->setCapInsets(capInsets);
}

void UIButton::onPressStateChangedToNormal()
{
    _buttonNormalRenderer->setVisible(true);
    _buttonClickedRenderer->setVisible(false);
    _buttonDisableRenderer->setVisible(false);
    if (_pressedActionEnabled)
    {
        _buttonNormalRenderer->stopAllActions();
        _buttonClickedRenderer->stopAllActions();
        _buttonDisableRenderer->stopAllActions();
        cocos2d::Action *zoomAction = cocos2d::ScaleTo::create(0.05f, 1.0f);
        cocos2d::Action *zoomAction1 = cocos2d::ScaleTo::create(0.05f, 1.0f);
        cocos2d::Action *zoomAction2 = cocos2d::ScaleTo::create(0.05f, 1.0f);
        _buttonNormalRenderer->runAction(zoomAction);
        _buttonClickedRenderer->runAction(zoomAction1);
        _buttonDisableRenderer->runAction(zoomAction2);
    }
}

void UIButton::onPressStateChangedToPressed()
{
    _buttonNormalRenderer->setVisible(false);
    _buttonClickedRenderer->setVisible(true);
    _buttonDisableRenderer->setVisible(false);
    if (_pressedActionEnabled)
    {
        _buttonNormalRenderer->stopAllActions();
        _buttonClickedRenderer->stopAllActions();
        _buttonDisableRenderer->stopAllActions();
        cocos2d::Action *zoomAction = cocos2d::ScaleTo::create(0.05f, 1.1f);
        cocos2d::Action *zoomAction1 = cocos2d::ScaleTo::create(0.05f, 1.1f);
        cocos2d::Action *zoomAction2 = cocos2d::ScaleTo::create(0.05f, 1.1f);
        _buttonNormalRenderer->runAction(zoomAction);
        _buttonClickedRenderer->runAction(zoomAction1);
        _buttonDisableRenderer->runAction(zoomAction2);
    }
}

void UIButton::onPressStateChangedToDisabled()
{
    _buttonNormalRenderer->setVisible(false);
    _buttonClickedRenderer->setVisible(false);
    _buttonDisableRenderer->setVisible(true);
}

void UIButton::setFlipX(bool flipX)
{
    _titleRenderer->setFlippedX(flipX);
    if (_scale9Enabled)
    {
        return;
    }
    dynamic_cast<cocos2d::Sprite*>(_buttonNormalRenderer)->setFlippedX(flipX);
    dynamic_cast<cocos2d::Sprite*>(_buttonClickedRenderer)->setFlippedX(flipX);
    dynamic_cast<cocos2d::Sprite*>(_buttonDisableRenderer)->setFlippedX(flipX);
}

void UIButton::setFlipY(bool flipY)
{
    _titleRenderer->setFlippedY(flipY);
    if (_scale9Enabled)
    {
        return;
    }
    dynamic_cast<cocos2d::Sprite*>(_buttonNormalRenderer)->setFlippedY(flipY);
    dynamic_cast<cocos2d::Sprite*>(_buttonClickedRenderer)->setFlippedY(flipY);
    dynamic_cast<cocos2d::Sprite*>(_buttonDisableRenderer)->setFlippedY(flipY);
}

bool UIButton::isFlipX()
{
    if (_scale9Enabled)
    {
        return false;
    }
    return dynamic_cast<cocos2d::Sprite*>(_buttonNormalRenderer)->isFlippedX();
}

bool UIButton::isFlipY()
{
    if (_scale9Enabled)
    {
        return false;
    }
    return dynamic_cast<cocos2d::Sprite*>(_buttonNormalRenderer)->isFlippedY();
}

void UIButton::setAnchorPoint(const cocos2d::Point &pt)
{
    UIWidget::setAnchorPoint(pt);
    _buttonNormalRenderer->setAnchorPoint(pt);
    _buttonClickedRenderer->setAnchorPoint(pt);
    _buttonDisableRenderer->setAnchorPoint(pt);
    _titleRenderer->setPosition(cocos2d::Point(_size.width*(0.5f-_anchorPoint.x), _size.height*(0.5f-_anchorPoint.y)));
}

void UIButton::onSizeChanged()
{
    normalTextureScaleChangedWithSize();
    pressedTextureScaleChangedWithSize();
    disabledTextureScaleChangedWithSize();
}

const cocos2d::Size& UIButton::getContentSize() const
{
    return _normalTextureSize;
}

cocos2d::Node* UIButton::getVirtualRenderer()
{
    if (_bright)
    {
        switch (_brightStyle)
        {
            case BRIGHT_NORMAL:
                return _buttonNormalRenderer;
            case BRIGHT_HIGHLIGHT:
                return _buttonClickedRenderer;
            default:
                return nullptr;
        }
    }
    else
    {
        return _buttonDisableRenderer;
    }
}

void UIButton::normalTextureScaleChangedWithSize()
{
    if (_ignoreSize)
    {
        if (!_scale9Enabled)
        {
            _buttonNormalRenderer->setScale(1.0f);
            _size = _normalTextureSize;
        }
    }
    else
    {
        if (_scale9Enabled)
        {
            dynamic_cast<cocos2d::extension::Scale9Sprite*>(_buttonNormalRenderer)->setPreferredSize(_size);
        }
        else
        {
            cocos2d::Size textureSize = _normalTextureSize;
            if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
            {
                _buttonNormalRenderer->setScale(1.0f);
                return;
            }
            float scaleX = _size.width / textureSize.width;
            float scaleY = _size.height / textureSize.height;
            _buttonNormalRenderer->setScaleX(scaleX);
            _buttonNormalRenderer->setScaleY(scaleY);
        }
    }
}

void UIButton::pressedTextureScaleChangedWithSize()
{
    if (_ignoreSize)
    {
        if (!_scale9Enabled)
        {
            _buttonClickedRenderer->setScale(1.0f);
        }
    }
    else
    {
        if (_scale9Enabled)
        {
            dynamic_cast<cocos2d::extension::Scale9Sprite*>(_buttonClickedRenderer)->setPreferredSize(_size);
        }
        else
        {
            cocos2d::Size textureSize = _pressedTextureSize;
            if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
            {
                _buttonClickedRenderer->setScale(1.0f);
                return;
            }
            float scaleX = _size.width / _pressedTextureSize.width;
            float scaleY = _size.height / _pressedTextureSize.height;
            _buttonClickedRenderer->setScaleX(scaleX);
            _buttonClickedRenderer->setScaleY(scaleY);
        }
    }
}

void UIButton::disabledTextureScaleChangedWithSize()
{
    if (_ignoreSize)
    {
        if (!_scale9Enabled)
        {
            _buttonDisableRenderer->setScale(1.0f);
        }
    }
    else
    {
        if (_scale9Enabled)
        {
            dynamic_cast<cocos2d::extension::Scale9Sprite*>(_buttonDisableRenderer)->setPreferredSize(_size);
        }
        else
        {
            cocos2d::Size textureSize = _disabledTextureSize;
            if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
            {
                _buttonDisableRenderer->setScale(1.0f);
                return;
            }
            float scaleX = _size.width / _disabledTextureSize.width;
            float scaleY = _size.height / _disabledTextureSize.height;
            _buttonDisableRenderer->setScaleX(scaleX);
            _buttonDisableRenderer->setScaleY(scaleY);
        }
    }
}

void UIButton::setPressedActionEnabled(bool enabled)
{
    _pressedActionEnabled = enabled;
}

void UIButton::setTitleText(const std::string& text)
{
    _titleRenderer->setString(text);
}

const std::string& UIButton::getTitleText() const
{
    return _titleRenderer->getString();
}

void UIButton::setTitleColor(const cocos2d::Color3B& color)
{
    _titleColor = color;
    _titleRenderer->setColor(color);
}

const cocos2d::Color3B& UIButton::getTitleColor() const
{
    return _titleRenderer->getColor();
}

void UIButton::setTitleFontSize(float size)
{
    _titleRenderer->setFontSize(size);
}

float UIButton::getTitleFontSize() const
{
    return _titleRenderer->getFontSize();
}

void UIButton::setTitleFontName(const char* fontName)
{
    _titleRenderer->setFontName(fontName);
}

const char* UIButton::getTitleFontName() const
{
    return _titleRenderer->getFontName().c_str();
}

void UIButton::setColor(const cocos2d::Color3B &color)
{
    UIWidget::setColor(color);
    setTitleColor(_titleColor);
}

const char* UIButton::getDescription() const
{
    return "Button";
}

UIWidget* UIButton::createCloneInstance()
{
    return UIButton::create();
}

void UIButton::copySpecialProperties(UIWidget *widget)
{
    UIButton* button = dynamic_cast<UIButton*>(widget);
    if (button)
    {   
        _prevIgnoreSize = button->_prevIgnoreSize;
        setScale9Enabled(button->_scale9Enabled);
        loadTextureNormal(button->_normalFileName.c_str(), button->_normalTexType);
        loadTexturePressed(button->_clickedFileName.c_str(), button->_pressedTexType);
        loadTextureDisabled(button->_disabledFileName.c_str(), button->_disabledTexType);
        setCapInsetsNormalRenderer(button->_capInsetsNormal);
        setCapInsetsPressedRenderer(button->_capInsetsPressed);
        setCapInsetsDisabledRenderer(button->_capInsetsDisabled);
        setTitleText(button->getTitleText());
        setTitleFontName(button->getTitleFontName());
        setTitleFontSize(button->getTitleFontSize());
        setTitleColor(button->getTitleColor());
        setPressedActionEnabled(button->_pressedActionEnabled);
    }
}

}