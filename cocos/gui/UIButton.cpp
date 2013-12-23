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

NS_CC_BEGIN

namespace gui {

#define NORMALRENDERERZ (0)
#define PRESSEDRENDERERZ (0)
#define DISABLEDRENDERERZ (0)
#define TITLERENDERERZ (1)
    
Button::Button():
_buttonNormalRenderer(nullptr),
_buttonClickedRenderer(nullptr),
_buttonDisableRenderer(nullptr),
_titleRenderer(nullptr),
_normalFileName(""),
_clickedFileName(""),
_disabledFileName(""),
_prevIgnoreSize(true),
_scale9Enabled(false),
_capInsetsNormal(Rect::ZERO),
_capInsetsPressed(Rect::ZERO),
_capInsetsDisabled(Rect::ZERO),
_normalTexType(UI_TEX_TYPE_LOCAL),
_pressedTexType(UI_TEX_TYPE_LOCAL),
_disabledTexType(UI_TEX_TYPE_LOCAL),
_normalTextureSize(_size),
_pressedTextureSize(_size),
_disabledTextureSize(_size),
_pressedActionEnabled(false),
_titleColor(Color3B::WHITE)
{
    
}

Button::~Button()
{
}

Button* Button::create()
{
    Button* widget = new Button();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

bool Button::init()
{
    if (Widget::init())
    {
        return true;
    }
    return false;
}

void Button::initRenderer()
{
    Widget::initRenderer();
    _buttonNormalRenderer = Sprite::create();
    _buttonClickedRenderer = Sprite::create();
    _buttonDisableRenderer = Sprite::create();
    _titleRenderer = LabelTTF::create();
    _renderer->addChild(_buttonNormalRenderer,NORMALRENDERERZ);
    _renderer->addChild(_buttonClickedRenderer,PRESSEDRENDERERZ);
    _renderer->addChild(_buttonDisableRenderer,DISABLEDRENDERERZ);
    _renderer->addChild(_titleRenderer,TITLERENDERERZ);
}

void Button::setScale9Enabled(bool able)
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
        _buttonNormalRenderer = extension::Scale9Sprite::create();
        _buttonClickedRenderer = extension::Scale9Sprite::create();
        _buttonDisableRenderer = extension::Scale9Sprite::create();
    }
    else
    {
        _buttonNormalRenderer = Sprite::create();
        _buttonClickedRenderer = Sprite::create();
        _buttonDisableRenderer = Sprite::create();
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

void Button::ignoreContentAdaptWithSize(bool ignore)
{
    if (!_scale9Enabled || (_scale9Enabled && !ignore))
    {
        Widget::ignoreContentAdaptWithSize(ignore);
        _prevIgnoreSize = ignore;
    }
}

void Button::loadTextures(const char* normal,const char* selected,const char* disabled,TextureResType texType)
{
    loadTextureNormal(normal,texType);
    loadTexturePressed(selected,texType);
    loadTextureDisabled(disabled,texType);
}

void Button::loadTextureNormal(const char* normal,TextureResType texType)
{
    if (!normal || strcmp(normal, "") == 0)
    {
        return;
    }
    _normalFileName = normal;
    _normalTexType = texType;
    if (_scale9Enabled)
    {
        extension::Scale9Sprite* normalRendererScale9 = static_cast<extension::Scale9Sprite*>(_buttonNormalRenderer);
        switch (_normalTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                normalRendererScale9->initWithFile(normal);
                break;
            case UI_TEX_TYPE_PLIST:
                normalRendererScale9->initWithSpriteFrameName(normal);
                break;
            default:
                break;
        }
        normalRendererScale9->setColor(getColor());
        normalRendererScale9->setOpacity(getOpacity());
        normalRendererScale9->setCapInsets(_capInsetsNormal);
    }
    else
    {
        Sprite* normalRenderer = static_cast<Sprite*>(_buttonNormalRenderer);
        switch (_normalTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                normalRenderer->setTexture(normal);
                break;
            case UI_TEX_TYPE_PLIST:
                normalRenderer->setSpriteFrame(normal);
                break;
            default:
                break;
        }
        normalRenderer->setColor(getColor());
        normalRenderer->setOpacity(getOpacity());
    }
    _normalTextureSize = _buttonNormalRenderer->getContentSize();
    updateAnchorPoint();
    normalTextureScaleChangedWithSize();
}

void Button::loadTexturePressed(const char* selected,TextureResType texType)
{
    if (!selected || strcmp(selected, "") == 0)
    {
        return;
    }
    _clickedFileName = selected;
    _pressedTexType = texType;
    if (_scale9Enabled)
    {
        extension::Scale9Sprite* clickedRendererScale9 = static_cast<extension::Scale9Sprite*>(_buttonClickedRenderer);
        switch (_pressedTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                clickedRendererScale9->initWithFile(selected);
                break;
            case UI_TEX_TYPE_PLIST:
                clickedRendererScale9->initWithSpriteFrameName(selected);
                break;
            default:
                break;
        }
        clickedRendererScale9->setColor(getColor());
        clickedRendererScale9->setOpacity(getOpacity());
        clickedRendererScale9->setCapInsets(_capInsetsPressed);
    }
    else
    {
        Sprite* clickedRenderer = static_cast<Sprite*>(_buttonClickedRenderer);
        switch (_pressedTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                clickedRenderer->setTexture(selected);
                break;
            case UI_TEX_TYPE_PLIST:
                clickedRenderer->setSpriteFrame(selected);
                break;
            default:
                break;
        }
        clickedRenderer->setColor(getColor());
        clickedRenderer->setOpacity(getOpacity());
    }
    _pressedTextureSize = _buttonClickedRenderer->getContentSize();
    updateAnchorPoint();
    pressedTextureScaleChangedWithSize();
}

void Button::loadTextureDisabled(const char* disabled,TextureResType texType)
{
    if (!disabled || strcmp(disabled, "") == 0)
    {
        return;
    }
    _disabledFileName = disabled;
    _disabledTexType = texType;
    if (_scale9Enabled)
    {
        extension::Scale9Sprite* disabledScale9 = static_cast<extension::Scale9Sprite*>(_buttonDisableRenderer);
        switch (_disabledTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                disabledScale9->initWithFile(disabled);
                break;
            case UI_TEX_TYPE_PLIST:
                disabledScale9->initWithSpriteFrameName(disabled);
                break;
            default:
                break;
        }
        disabledScale9->setColor(getColor());
        disabledScale9->setOpacity(getOpacity());
        disabledScale9->setCapInsets(_capInsetsDisabled);
    }
    else
    {
        Sprite* disabledRenderer = static_cast<Sprite*>(_buttonDisableRenderer);
        switch (_disabledTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                disabledRenderer->setTexture(disabled);
                break;
            case UI_TEX_TYPE_PLIST:
                disabledRenderer->setSpriteFrame(disabled);
                break;
            default:
                break;
        }
        disabledRenderer->setColor(getColor());
        disabledRenderer->setOpacity(getOpacity());
    }
    _disabledTextureSize = _buttonDisableRenderer->getContentSize();
    updateAnchorPoint();
    disabledTextureScaleChangedWithSize();
}

void Button::setCapInsets(const Rect &capInsets)
{
    setCapInsetsNormalRenderer(capInsets);
    setCapInsetsPressedRenderer(capInsets);
    setCapInsetsDisabledRenderer(capInsets);
}

void Button::setCapInsetsNormalRenderer(const Rect &capInsets)
{
    _capInsetsNormal = capInsets;
    if (!_scale9Enabled)
    {
        return;
    }
    static_cast<extension::Scale9Sprite*>(_buttonNormalRenderer)->setCapInsets(capInsets);
}

void Button::setCapInsetsPressedRenderer(const Rect &capInsets)
{
    _capInsetsPressed = capInsets;
    if (!_scale9Enabled)
    {
        return;
    }
    static_cast<extension::Scale9Sprite*>(_buttonClickedRenderer)->setCapInsets(capInsets);
}

void Button::setCapInsetsDisabledRenderer(const Rect &capInsets)
{
    _capInsetsDisabled = capInsets;
    if (!_scale9Enabled)
    {
        return;
    }
    static_cast<extension::Scale9Sprite*>(_buttonDisableRenderer)->setCapInsets(capInsets);
}

void Button::onPressStateChangedToNormal()
{
    _buttonNormalRenderer->setVisible(true);
    _buttonClickedRenderer->setVisible(false);
    _buttonDisableRenderer->setVisible(false);
    if (_pressedActionEnabled)
    {
        _buttonNormalRenderer->stopAllActions();
        _buttonClickedRenderer->stopAllActions();
        _buttonDisableRenderer->stopAllActions();
        Action *zoomAction = ScaleTo::create(0.05f, 1.0f);
        Action *zoomAction1 = ScaleTo::create(0.05f, 1.0f);
        Action *zoomAction2 = ScaleTo::create(0.05f, 1.0f);
        _buttonNormalRenderer->runAction(zoomAction);
        _buttonClickedRenderer->runAction(zoomAction1);
        _buttonDisableRenderer->runAction(zoomAction2);
    }
}

void Button::onPressStateChangedToPressed()
{
    _buttonNormalRenderer->setVisible(false);
    _buttonClickedRenderer->setVisible(true);
    _buttonDisableRenderer->setVisible(false);
    if (_pressedActionEnabled)
    {
        _buttonNormalRenderer->stopAllActions();
        _buttonClickedRenderer->stopAllActions();
        _buttonDisableRenderer->stopAllActions();
        Action *zoomAction = ScaleTo::create(0.05f, 1.1f);
        Action *zoomAction1 = ScaleTo::create(0.05f, 1.1f);
        Action *zoomAction2 = ScaleTo::create(0.05f, 1.1f);
        _buttonNormalRenderer->runAction(zoomAction);
        _buttonClickedRenderer->runAction(zoomAction1);
        _buttonDisableRenderer->runAction(zoomAction2);
    }
}

void Button::onPressStateChangedToDisabled()
{
    _buttonNormalRenderer->setVisible(false);
    _buttonClickedRenderer->setVisible(false);
    _buttonDisableRenderer->setVisible(true);
}

void Button::setFlipX(bool flipX)
{
    _titleRenderer->setFlippedX(flipX);
    if (_scale9Enabled)
    {
        return;
    }
    static_cast<Sprite*>(_buttonNormalRenderer)->setFlippedX(flipX);
    static_cast<Sprite*>(_buttonClickedRenderer)->setFlippedX(flipX);
    static_cast<Sprite*>(_buttonDisableRenderer)->setFlippedX(flipX);
}

void Button::setFlipY(bool flipY)
{
    _titleRenderer->setFlippedY(flipY);
    if (_scale9Enabled)
    {
        return;
    }
    static_cast<Sprite*>(_buttonNormalRenderer)->setFlippedY(flipY);
    static_cast<Sprite*>(_buttonClickedRenderer)->setFlippedY(flipY);
    static_cast<Sprite*>(_buttonDisableRenderer)->setFlippedY(flipY);
}

bool Button::isFlipX()
{
    if (_scale9Enabled)
    {
        return false;
    }
    return static_cast<Sprite*>(_buttonNormalRenderer)->isFlippedX();
}

bool Button::isFlipY()
{
    if (_scale9Enabled)
    {
        return false;
    }
    return static_cast<Sprite*>(_buttonNormalRenderer)->isFlippedY();
}

void Button::setAnchorPoint(const Point &pt)
{
    Widget::setAnchorPoint(pt);
    _buttonNormalRenderer->setAnchorPoint(pt);
    _buttonClickedRenderer->setAnchorPoint(pt);
    _buttonDisableRenderer->setAnchorPoint(pt);
    _titleRenderer->setPosition(Point(_size.width*(0.5f-_anchorPoint.x), _size.height*(0.5f-_anchorPoint.y)));
}

void Button::onSizeChanged()
{
    Widget::onSizeChanged();
    normalTextureScaleChangedWithSize();
    pressedTextureScaleChangedWithSize();
    disabledTextureScaleChangedWithSize();
}

const Size& Button::getContentSize() const
{
    return _normalTextureSize;
}

Node* Button::getVirtualRenderer()
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

void Button::normalTextureScaleChangedWithSize()
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
            static_cast<extension::Scale9Sprite*>(_buttonNormalRenderer)->setPreferredSize(_size);
        }
        else
        {
            Size textureSize = _normalTextureSize;
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

void Button::pressedTextureScaleChangedWithSize()
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
            static_cast<extension::Scale9Sprite*>(_buttonClickedRenderer)->setPreferredSize(_size);
        }
        else
        {
            Size textureSize = _pressedTextureSize;
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

void Button::disabledTextureScaleChangedWithSize()
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
            static_cast<extension::Scale9Sprite*>(_buttonDisableRenderer)->setPreferredSize(_size);
        }
        else
        {
            Size textureSize = _disabledTextureSize;
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

void Button::setPressedActionEnabled(bool enabled)
{
    _pressedActionEnabled = enabled;
}

void Button::setTitleText(const std::string& text)
{
    _titleRenderer->setString(text);
}

const std::string& Button::getTitleText() const
{
    return _titleRenderer->getString();
}

void Button::setTitleColor(const Color3B& color)
{
    _titleColor = color;
    _titleRenderer->setColor(color);
}

const Color3B& Button::getTitleColor() const
{
    return _titleRenderer->getColor();
}

void Button::setTitleFontSize(float size)
{
    _titleRenderer->setFontSize(size);
}

float Button::getTitleFontSize() const
{
    return _titleRenderer->getFontSize();
}

void Button::setTitleFontName(const char* fontName)
{
    _titleRenderer->setFontName(fontName);
}

const char* Button::getTitleFontName() const
{
    return _titleRenderer->getFontName().c_str();
}

void Button::setColor(const Color3B &color)
{
    Widget::setColor(color);
    setTitleColor(_titleColor);
}

std::string Button::getDescription() const
{
    return "Button";
}

Widget* Button::createCloneInstance()
{
    return Button::create();
}

void Button::copySpecialProperties(Widget *widget)
{
    Button* button = dynamic_cast<Button*>(widget);
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

NS_CC_END