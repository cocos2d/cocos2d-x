/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

static const int NORMAL_RENDERER_Z = (-2);
static const int PRESSED_RENDERER_Z = (-2);
static const int DISABLED_RENDERER_Z = (-2);
static const int TITLE_RENDERER_Z = (-1);
    
Button::Button():
_titleRenderer(nullptr),
_prevIgnoreSize(true),
_scale9Enabled(false),
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
    _normalState.renderer = Sprite::create();
    _pressedState.renderer = Sprite::create();
    _disabledState.renderer = Sprite::create();
    _titleRenderer = LabelTTF::create();
    
    Node::addChild(_normalState.renderer, NORMAL_RENDERER_Z, -1);
    Node::addChild(_pressedState.renderer, PRESSED_RENDERER_Z, -1);
    Node::addChild(_disabledState.renderer, DISABLED_RENDERER_Z, -1);
    Node::addChild(_titleRenderer, TITLE_RENDERER_Z, -1);
}

void Button::setScale9Enabled(bool able)
{
    if (_scale9Enabled == able)
    {
        return;
    }
    _brightStyle = BRIGHT_NONE;
    _scale9Enabled = able;
    
    Node::removeChild(_normalState.renderer);
    Node::removeChild(_pressedState.renderer);
    Node::removeChild(_disabledState.renderer);
    _normalState.renderer = nullptr;
    _pressedState.renderer = nullptr;
    _disabledState.renderer = nullptr;
    if (_scale9Enabled)
    {
        _normalState.renderer = extension::Scale9Sprite::create();
        _pressedState.renderer = extension::Scale9Sprite::create();
        _disabledState.renderer = extension::Scale9Sprite::create();
    }
    else
    {
        _normalState.renderer = Sprite::create();
        _pressedState.renderer = Sprite::create();
        _disabledState.renderer = Sprite::create();
    }
    
    load(_normalState);
    load(_pressedState);
    load(_disabledState);
    
    Node::addChild(_normalState.renderer, NORMAL_RENDERER_Z, -1);
    Node::addChild(_pressedState.renderer, PRESSED_RENDERER_Z, -1);
    Node::addChild(_disabledState.renderer, DISABLED_RENDERER_Z, -1);
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
    setCapInsetsNormalRenderer(_normalState.capInsets);
    setCapInsetsPressedRenderer(_pressedState.capInsets);
    setCapInsetsDisabledRenderer(_disabledState.capInsets);
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
    CC_SAFE_RELEASE_NULL(_normalState.sprite);
    CC_SAFE_RELEASE_NULL(_pressedState.sprite);
    CC_SAFE_RELEASE_NULL(_disabledState.sprite);

    loadTextureNormal(normal,texType);
    loadTexturePressed(selected,texType);
    loadTextureDisabled(disabled,texType);
}

void Button::loadTextures(cocos2d::SpriteFrame* normal, cocos2d::SpriteFrame* selected, cocos2d::SpriteFrame* disabled) {
    CC_SAFE_RELEASE_NULL(_normalState.sprite);
    CC_SAFE_RELEASE_NULL(_pressedState.sprite);
    CC_SAFE_RELEASE_NULL(_disabledState.sprite);
    
    _normalState.sprite = normal;
    _normalState.texType = ButtonState::TexType::SPRITE_FRAME;
    load(_normalState);
    _pressedState.sprite = selected;
    _pressedState.texType = ButtonState::TexType::SPRITE_FRAME;
    load(_pressedState);
    _disabledState.sprite = disabled;
    _disabledState.texType = ButtonState::TexType::SPRITE_FRAME;
    load(_disabledState);
    
    CC_SAFE_RETAIN(_normalState.sprite);
    CC_SAFE_RETAIN(_pressedState.sprite);
    CC_SAFE_RETAIN(_disabledState.sprite);
}

void Button::load(ButtonState &state) {
    
    if ( state.texType == ButtonState::TexType::SPRITE_FRAME ) {
        if (!state.sprite)
        {
            return;
        }
    } else {
        if (state.fileName.empty())
        {
            return;
        }
    }
    
    if (_scale9Enabled)
    {
        auto renderer = static_cast<cocos2d::extension::Scale9Sprite*>(state.renderer);
        switch (state.texType)
        {
            case ButtonState::TexType::SPRITE_FRAME:
                renderer->setSpriteFrame(state.sprite);
                break;
            case ButtonState::TexType::LOCAL:
                renderer->initWithFile(state.fileName.c_str());
                break;
            case ButtonState::TexType::PLIST:
                renderer->initWithSpriteFrameName(state.fileName.c_str());
                break;
        }
        
        renderer->setCapInsets(_normalState.capInsets);
    }
    else
    {
        auto renderer = static_cast<cocos2d::Sprite*>(state.renderer);
        switch (state.texType)
        {
            case ButtonState::TexType::SPRITE_FRAME:
                renderer->setSpriteFrame(state.sprite);
                break;
            case ButtonState::TexType::LOCAL:
                renderer->setTexture(state.fileName.c_str());
                break;
            case ButtonState::TexType::PLIST:
                renderer->setSpriteFrame(state.fileName.c_str());
                break;
        }
    }
    state.textureSize = state.renderer->getContentSize();
    state.textureLoaded = true;
    updateDisplayedColor(getColor());
    updateDisplayedOpacity(getOpacity());
    updateAnchorPoint();
    textureScaleChangedWithSize(state);
}

void Button::loadTextureNormal(const char* normal,TextureResType texType)
{
    CC_SAFE_RELEASE_NULL(_normalState.sprite);
    _normalState.setTexType(texType);
    _normalState.fileName = normal;
    load(_normalState);
}

void Button::loadTexturePressed(const char* pressed,TextureResType texType)
{
    CC_SAFE_RELEASE_NULL(_pressedState.sprite);
    _pressedState.setTexType(texType);
    _pressedState.fileName = pressed;
    load(_pressedState);
}

void Button::loadTextureDisabled(const char* disabled,TextureResType texType)
{
    CC_SAFE_RELEASE_NULL(_disabledState.sprite);
    _disabledState.setTexType(texType);
    _disabledState.fileName = disabled;
    load(_disabledState);
}

void Button::loadTextureNormal(cocos2d::SpriteFrame *normal)
{
    CC_SAFE_RELEASE_NULL(_normalState.sprite);
    _normalState.sprite = normal;
    _normalState.texType = ButtonState::TexType::SPRITE_FRAME;
    load(_normalState);
    CC_SAFE_RETAIN(_normalState.sprite);
}

void Button::loadTexturePressed(cocos2d::SpriteFrame *pressed)
{
    CC_SAFE_RELEASE_NULL(_pressedState.sprite);
    _pressedState.sprite = pressed;
    _pressedState.texType = ButtonState::TexType::SPRITE_FRAME;
    load(_pressedState);
    CC_SAFE_RETAIN(_pressedState.sprite);
}

void Button::loadTextureDisabled(cocos2d::SpriteFrame *disabled)
{
    CC_SAFE_RELEASE_NULL(_disabledState.sprite);
    _disabledState.sprite = disabled;
    _disabledState.texType = ButtonState::TexType::SPRITE_FRAME;
    load(_disabledState);
    CC_SAFE_RETAIN(_disabledState.sprite);
}


void Button::setCapInsets(const Rect &capInsets)
{
    setCapInsetsNormalRenderer(capInsets);
    setCapInsetsPressedRenderer(capInsets);
    setCapInsetsDisabledRenderer(capInsets);
}

void Button::setCapInsetsNormalRenderer(const Rect &capInsets)
{
    setCapInsets(_normalState, capInsets);
}

void Button::setCapInsetsPressedRenderer(const Rect &capInsets)
{
    setCapInsets(_pressedState, capInsets);
}

void Button::setCapInsetsDisabledRenderer(const Rect &capInsets)
{
    setCapInsets(_disabledState, capInsets);
}

void Button::setCapInsets(ButtonState &s, const Rect &capInsets) {
    s.capInsets = capInsets;
    if (!_scale9Enabled)
    {
        return;
    }
    static_cast<extension::Scale9Sprite*>(s.renderer)->setCapInsets(capInsets);
}

void Button::onPressStateChangedToNormal()
{
    _normalState.renderer->setVisible(true);
    _pressedState.renderer->setVisible(false);
    _disabledState.renderer->setVisible(false);
    if (_pressedState.textureLoaded)
    {
        if (_pressedActionEnabled)
        {
            _normalState.renderer->stopAllActions();
            _pressedState.renderer->stopAllActions();
            Action *zoomAction = ScaleTo::create(0.05f, _normalState.textureScaleInSize.x, _normalState.textureScaleInSize.y);
            _normalState.renderer->runAction(zoomAction);
            _pressedState.renderer->setScale(_pressedState.textureScaleInSize.x, _pressedState.textureScaleInSize.y);
        }
    }
    else
    {
        _normalState.renderer->stopAllActions();
        Action *zoomAction = ScaleTo::create(0.05f, _normalState.textureScaleInSize.x, _normalState.textureScaleInSize.y);
        _normalState.renderer->runAction(zoomAction);
    }
}

void Button::onPressStateChangedToPressed()
{
    if (_pressedState.textureLoaded)
    {
        _normalState.renderer->setVisible(false);
        _pressedState.renderer->setVisible(true);
        _disabledState.renderer->setVisible(false);
        if (_pressedActionEnabled)
        {
            _normalState.renderer->stopAllActions();
            _pressedState.renderer->stopAllActions();
            Action *zoomAction = ScaleTo::create(0.05f, _pressedState.textureScaleInSize.x + 0.1f, _pressedState.textureScaleInSize.y + 0.1f);
            _pressedState.renderer->runAction(zoomAction);
            _normalState.renderer->setScale(_pressedState.textureScaleInSize.x + 0.1f, _pressedState.textureScaleInSize.y + 0.1f);
        }
    }
    else
    {
        _normalState.renderer->setVisible(true);
        _pressedState.renderer->setVisible(true);
        _disabledState.renderer->setVisible(false);
        _normalState.renderer->stopAllActions();
        Action *zoomAction = ScaleTo::create(0.05f, _pressedState.textureScaleInSize.x + 0.1f, _pressedState.textureScaleInSize.y + 0.1f);
        _normalState.renderer->runAction(zoomAction);
    }
}

void Button::onPressStateChangedToDisabled()
{
    _normalState.renderer->setVisible(false);
    _pressedState.renderer->setVisible(false);
    _disabledState.renderer->setVisible(true);
    _normalState.renderer->setScale(_normalState.textureScaleInSize.x, _normalState.textureScaleInSize.y);
    _pressedState.renderer->setScale(_pressedState.textureScaleInSize.x, _pressedState.textureScaleInSize.y);
}

void Button::setFlipX(bool flipX)
{
    _titleRenderer->setFlippedX(flipX);
    if (_scale9Enabled)
    {
        return;
    }
    static_cast<Sprite*>(_normalState.renderer)->setFlippedX(flipX);
    static_cast<Sprite*>(_pressedState.renderer)->setFlippedX(flipX);
    static_cast<Sprite*>(_disabledState.renderer)->setFlippedX(flipX);
}

void Button::setFlipY(bool flipY)
{
    _titleRenderer->setFlippedY(flipY);
    if (_scale9Enabled)
    {
        return;
    }
    static_cast<Sprite*>(_normalState.renderer)->setFlippedY(flipY);
    static_cast<Sprite*>(_pressedState.renderer)->setFlippedY(flipY);
    static_cast<Sprite*>(_disabledState.renderer)->setFlippedY(flipY);
}

bool Button::isFlipX()
{
    if (_scale9Enabled)
    {
        return false;
    }
    return static_cast<Sprite*>(_normalState.renderer)->isFlippedX();
}

bool Button::isFlipY()
{
    if (_scale9Enabled)
    {
        return false;
    }
    return static_cast<Sprite*>(_normalState.renderer)->isFlippedY();
}

void Button::setAnchorPoint(const Point &pt)
{
    Widget::setAnchorPoint(pt);
    _normalState.renderer->setAnchorPoint(pt);
    _pressedState.renderer->setAnchorPoint(pt);
    _disabledState.renderer->setAnchorPoint(pt);
    _titleRenderer->setPosition(Point(_size.width*(0.5f-_anchorPoint.x), _size.height*(0.5f-_anchorPoint.y)));
}

void Button::onSizeChanged()
{
    Widget::onSizeChanged();
    textureScaleChangedWithSize(_normalState);
    textureScaleChangedWithSize(_pressedState);
    textureScaleChangedWithSize(_disabledState);
}

const Size& Button::getContentSize() const
{
    return _normalState.textureSize;
}

Node* Button::getVirtualRenderer()
{
    if (_bright)
    {
        switch (_brightStyle)
        {
            case BRIGHT_NORMAL:
                return _normalState.renderer;
            case BRIGHT_HIGHLIGHT:
                return _pressedState.renderer;
            default:
                return nullptr;
        }
    }
    else
    {
        return _disabledState.renderer;
    }
}

void Button::textureScaleChangedWithSize(ButtonState &s)
{
    if (_ignoreSize)
    {
        if (!_scale9Enabled)
        {
            s.renderer->setScale(1.0f);
            s.textureScaleInSize = Point(1,1);
            _size = _normalState.textureSize;
        }
    }
    else
    {
        if (_scale9Enabled)
        {
            static_cast<extension::Scale9Sprite*>(s.renderer)->setPreferredSize(_size);
            s.textureScaleInSize = Point(1,1);
        }
        else
        {
            auto sz = s.renderer->getContentSize();
            if (sz.width <= 0.0f || sz.height <= 0.0f)
            {
                s.renderer->setScale(1.0f);
                return;
            }
            float scaleX = _size.width / sz.width;
            float scaleY = _size.height / sz.height;
            s.renderer->setScaleX(scaleX);
            s.renderer->setScaleY(scaleY);
            s.textureScaleInSize = Point(scaleX, scaleY);
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
    _titleRenderer->updateDisplayedColor(color);
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
        load(_normalState = button->_normalState);
        load(_pressedState = button->_pressedState);
        load(_disabledState = button->_disabledState);
        setCapInsetsNormalRenderer(button->_normalState.capInsets);
        setCapInsetsPressedRenderer(button->_pressedState.capInsets);
        setCapInsetsDisabledRenderer(button->_disabledState.capInsets);
        setTitleText(button->getTitleText());
        setTitleFontName(button->getTitleFontName());
        setTitleFontSize(button->getTitleFontSize());
        setTitleColor(button->getTitleColor());
        setPressedActionEnabled(button->_pressedActionEnabled);
    }
}

}

NS_CC_END