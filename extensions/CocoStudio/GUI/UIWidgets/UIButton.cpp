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

#include "UIButton.h"
#include "../../../GUI/CCControlExtension/CCScale9Sprite.h"

NS_CC_BEGIN

namespace ui {

static const int NORMAL_RENDERER_Z = (-2);
static const int PRESSED_RENDERER_Z = (-2);
static const int DISABLED_RENDERER_Z = (-2);
static const int TITLE_RENDERER_Z = (-1);
    
IMPLEMENT_CLASS_GUI_INFO(Button)
    
Button::Button():
_buttonNormalRenderer(NULL),
_buttonClickedRenderer(NULL),
_buttonDisableRenderer(NULL),
_titleRenderer(NULL),
_normalFileName(""),
_clickedFileName(""),
_disabledFileName(""),
_prevIgnoreSize(true),
_scale9Enabled(false),
_capInsetsNormal(CCRectZero),
_capInsetsPressed(CCRectZero),
_capInsetsDisabled(CCRectZero),
_normalTexType(UI_TEX_TYPE_LOCAL),
_pressedTexType(UI_TEX_TYPE_LOCAL),
_disabledTexType(UI_TEX_TYPE_LOCAL),
_normalTextureSize(_size),
_pressedTextureSize(_size),
_disabledTextureSize(_size),
_pressedActionEnabled(false),
_titleColor(ccWHITE),
_normalTextureScaleXInSize(1.0f),
_normalTextureScaleYInSize(1.0f),
_pressedTextureScaleXInSize(1.0f),
_pressedTextureScaleYInSize(1.0f),
_normalTextureLoaded(false),
_pressedTextureLoaded(false),
_disabledTextureLoaded(false)
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
    return NULL;
}

bool Button::init()
{
    if (Widget::init())
    {
        setTouchEnabled(true);
        return true;
    }
    return false;
}

void Button::initRenderer()
{
    _buttonNormalRenderer = CCSprite::create();
    _buttonClickedRenderer = CCSprite::create();
    _buttonDisableRenderer = CCSprite::create();
    _titleRenderer = CCLabelTTF::create();
    
    CCNode::addChild(_buttonNormalRenderer, NORMAL_RENDERER_Z, -1);
    CCNode::addChild(_buttonClickedRenderer,PRESSED_RENDERER_Z, -1);
    CCNode::addChild(_buttonDisableRenderer,DISABLED_RENDERER_Z, -1);
    CCNode::addChild(_titleRenderer,TITLE_RENDERER_Z, -1);
}

void Button::setScale9Enabled(bool able)
{
    if (_scale9Enabled == able)
    {
        return;
    }
    _brightStyle = BRIGHT_NONE;
    _scale9Enabled = able;
    CCNode::removeChild(_buttonNormalRenderer, true);
    CCNode::removeChild(_buttonClickedRenderer, true);
    CCNode::removeChild(_buttonDisableRenderer, true);
    _buttonNormalRenderer = NULL;
    _buttonClickedRenderer = NULL;
    _buttonDisableRenderer = NULL;
    if (_scale9Enabled)
    {
        _buttonNormalRenderer = extension::CCScale9Sprite::create();
        _buttonClickedRenderer = extension::CCScale9Sprite::create();
        _buttonDisableRenderer = extension::CCScale9Sprite::create();
    }
    else
    {
        _buttonNormalRenderer = CCSprite::create();
        _buttonClickedRenderer = CCSprite::create();
        _buttonDisableRenderer = CCSprite::create();
    }

    loadTextureNormal(_normalFileName.c_str(), _normalTexType);
    loadTexturePressed(_clickedFileName.c_str(), _pressedTexType);
    loadTextureDisabled(_disabledFileName.c_str(), _disabledTexType);
    CCNode::addChild(_buttonNormalRenderer, NORMAL_RENDERER_Z, -1);
    CCNode::addChild(_buttonClickedRenderer,PRESSED_RENDERER_Z, -1);
    CCNode::addChild(_buttonDisableRenderer,DISABLED_RENDERER_Z, -1);
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
    
bool Button::isScale9Enabled()
{
    return _scale9Enabled;
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
        extension::CCScale9Sprite* normalRendererScale9 = static_cast<extension::CCScale9Sprite*>(_buttonNormalRenderer);
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
        normalRendererScale9->setCapInsets(_capInsetsNormal);
    }
    else
    {
        CCSprite* normalRenderer = static_cast<CCSprite*>(_buttonNormalRenderer);
        switch (_normalTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                normalRenderer->initWithFile(normal);
                break;
            case UI_TEX_TYPE_PLIST:
                normalRenderer->initWithSpriteFrameName(normal);
                break;
            default:
                break;
        }
    }
    _normalTextureSize = _buttonNormalRenderer->getContentSize();
    normalTextureScaleChangedWithSize();
    updateAnchorPoint();
    updateFlippedX();
    updateFlippedY();
    updateRGBAToRenderer(_buttonNormalRenderer);
    _normalTextureLoaded = true;
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
        extension::CCScale9Sprite* clickedRendererScale9 = static_cast<extension::CCScale9Sprite*>(_buttonClickedRenderer);
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
        clickedRendererScale9->setCapInsets(_capInsetsPressed);
    }
    else
    {
        CCSprite* clickedRenderer = static_cast<CCSprite*>(_buttonClickedRenderer);
        switch (_pressedTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                clickedRenderer->initWithFile(selected);
                break;
            case UI_TEX_TYPE_PLIST:
                clickedRenderer->initWithSpriteFrameName(selected);
                break;
            default:
                break;
        }
    }
    _pressedTextureSize = _buttonClickedRenderer->getContentSize();
    pressedTextureScaleChangedWithSize();
    updateAnchorPoint();
    updateFlippedX();
    updateFlippedY();
    updateRGBAToRenderer(_buttonClickedRenderer);
    _pressedTextureLoaded = true;
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
        extension::CCScale9Sprite* disabledScale9 = static_cast<extension::CCScale9Sprite*>(_buttonDisableRenderer);
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
        disabledScale9->setCapInsets(_capInsetsDisabled);
    }
    else
    {
        CCSprite* disabledRenderer = static_cast<CCSprite*>(_buttonDisableRenderer);
        switch (_disabledTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                disabledRenderer->initWithFile(disabled);
                break;
            case UI_TEX_TYPE_PLIST:
                disabledRenderer->initWithSpriteFrameName(disabled);
                break;
            default:
                break;
        }
    }
    _disabledTextureSize = _buttonDisableRenderer->getContentSize();
    disabledTextureScaleChangedWithSize();
    updateAnchorPoint();
    updateFlippedX();
    updateFlippedY();
    updateRGBAToRenderer(_buttonDisableRenderer);
    _disabledTextureLoaded = true;
}

void Button::setCapInsets(const CCRect &capInsets)
{
    setCapInsetsNormalRenderer(capInsets);
    setCapInsetsPressedRenderer(capInsets);
    setCapInsetsDisabledRenderer(capInsets);
}

void Button::setCapInsetsNormalRenderer(const CCRect &capInsets)
{
    _capInsetsNormal = capInsets;
    if (!_scale9Enabled)
    {
        return;
    }
    static_cast<extension::CCScale9Sprite*>(_buttonNormalRenderer)->setCapInsets(capInsets);
}
    
const CCRect& Button::getCapInsetNormalRenderer()
{
    return _capInsetsNormal;
}

void Button::setCapInsetsPressedRenderer(const CCRect &capInsets)
{
    _capInsetsPressed = capInsets;
    if (!_scale9Enabled)
    {
        return;
    }
    static_cast<extension::CCScale9Sprite*>(_buttonClickedRenderer)->setCapInsets(capInsets);
}
    
const CCRect& Button::getCapInsetPressedRenderer()
{
    return _capInsetsPressed;
}

void Button::setCapInsetsDisabledRenderer(const CCRect &capInsets)
{
    _capInsetsDisabled = capInsets;
    if (!_scale9Enabled)
    {
        return;
    }
    static_cast<extension::CCScale9Sprite*>(_buttonDisableRenderer)->setCapInsets(capInsets);
}
    
const CCRect& Button::getCapInsetDisabledRenderer()
{
    return _capInsetsDisabled;
}

void Button::onPressStateChangedToNormal()
{
    _buttonNormalRenderer->setVisible(true);
    _buttonClickedRenderer->setVisible(false);
    _buttonDisableRenderer->setVisible(false);
    if (_pressedTextureLoaded)
    {
        if (_pressedActionEnabled)
        {
            _buttonNormalRenderer->stopAllActions();
            _buttonClickedRenderer->stopAllActions();
            CCAction *zoomAction = CCScaleTo::create(0.05f, _normalTextureScaleXInSize, _normalTextureScaleYInSize);
            _buttonNormalRenderer->runAction(zoomAction);
            _buttonClickedRenderer->setScale(_pressedTextureScaleXInSize, _pressedTextureScaleYInSize);
        }
    }
    else
    {
        if (_scale9Enabled)
        {
            updateTextureRGBA();
        }
        else
        {
            _buttonNormalRenderer->stopAllActions();
            _buttonNormalRenderer->setScale(_normalTextureScaleXInSize, _normalTextureScaleYInSize);
        }
    }
}

void Button::onPressStateChangedToPressed()
{
    if (_pressedTextureLoaded)
    {
        _buttonNormalRenderer->setVisible(false);
        _buttonClickedRenderer->setVisible(true);
        _buttonDisableRenderer->setVisible(false);
        if (_pressedActionEnabled)
        {
            _buttonNormalRenderer->stopAllActions();
            _buttonClickedRenderer->stopAllActions();
            CCAction *zoomAction = CCScaleTo::create(0.05f, _pressedTextureScaleXInSize + 0.1f, _pressedTextureScaleYInSize + 0.1f);
            _buttonClickedRenderer->runAction(zoomAction);
            _buttonNormalRenderer->setScale(_pressedTextureScaleXInSize + 0.1f, _pressedTextureScaleYInSize + 0.1f);
        }
    }
    else
    {
        _buttonNormalRenderer->setVisible(true);
        _buttonClickedRenderer->setVisible(true);
        _buttonDisableRenderer->setVisible(false);
        if (_scale9Enabled)
        {
            dynamic_cast<CCRGBAProtocol*>(_buttonNormalRenderer)->setColor(ccGRAY);
        }
        else
        {
            _buttonNormalRenderer->stopAllActions();
            _buttonNormalRenderer->setScale(_normalTextureScaleXInSize + 0.1f, _normalTextureScaleYInSize + 0.1f);
        }
    }
}

void Button::onPressStateChangedToDisabled()
{
    _buttonNormalRenderer->setVisible(false);
    _buttonClickedRenderer->setVisible(false);
    _buttonDisableRenderer->setVisible(true);
    _buttonNormalRenderer->setScale(_normalTextureScaleXInSize, _normalTextureScaleYInSize);
    _buttonClickedRenderer->setScale(_pressedTextureScaleXInSize, _pressedTextureScaleYInSize);
}
    
void Button::updateFlippedX()
{
    _titleRenderer->setFlipX(_flippedX);
    if (_scale9Enabled)
    {
        if (_flippedX)
        {
            _buttonNormalRenderer->setScaleX(-1);
            _buttonClickedRenderer->setScaleX(-1);
            _buttonDisableRenderer->setScaleX(-1);
        }
        else
        {
            _buttonNormalRenderer->setScaleX(1);
            _buttonClickedRenderer->setScaleX(1);
            _buttonDisableRenderer->setScaleX(1);
        }
        
    }
    else
    {
        static_cast<CCSprite*>(_buttonNormalRenderer)->setFlipX(_flippedX);
        static_cast<CCSprite*>(_buttonClickedRenderer)->setFlipX(_flippedX);
        static_cast<CCSprite*>(_buttonDisableRenderer)->setFlipX(_flippedX);
    }
}
    
void Button::updateFlippedY()
{
    _titleRenderer->setFlipY(_flippedY);
    if (_scale9Enabled)
    {
        if (_flippedY)
        {
            _buttonNormalRenderer->setScaleY(-1);
            _buttonClickedRenderer->setScaleY(-1);
            _buttonDisableRenderer->setScaleY(-1);
        }
        else
        {
            _buttonNormalRenderer->setScaleY(1);
            _buttonClickedRenderer->setScaleY(1);
            _buttonDisableRenderer->setScaleY(1);
        }

    }
    else
    {
        static_cast<CCSprite*>(_buttonNormalRenderer)->setFlipY(_flippedY);
        static_cast<CCSprite*>(_buttonClickedRenderer)->setFlipY(_flippedY);
        static_cast<CCSprite*>(_buttonDisableRenderer)->setFlipY(_flippedY);
    }
}

void Button::setAnchorPoint(const CCPoint &pt)
{
    Widget::setAnchorPoint(pt);
    _buttonNormalRenderer->setAnchorPoint(pt);
    _buttonClickedRenderer->setAnchorPoint(pt);
    _buttonDisableRenderer->setAnchorPoint(pt);
    _titleRenderer->setPosition(CCPoint(_size.width*(0.5f-m_obAnchorPoint.x), _size.height*(0.5f-m_obAnchorPoint.y)));
}

void Button::onSizeChanged()
{
    Widget::onSizeChanged();
    normalTextureScaleChangedWithSize();
    pressedTextureScaleChangedWithSize();
    disabledTextureScaleChangedWithSize();
}

const CCSize& Button::getContentSize() const
{
    return _normalTextureSize;
}

CCNode* Button::getVirtualRenderer()
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
                return NULL;
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
            _normalTextureScaleXInSize = _normalTextureScaleYInSize = 1.0f;
            _size = _normalTextureSize;
        }
    }
    else
    {
        if (_scale9Enabled)
        {
            static_cast<extension::CCScale9Sprite*>(_buttonNormalRenderer)->setPreferredSize(_size);
            _normalTextureScaleXInSize = _normalTextureScaleYInSize = 1.0f;
        }
        else
        {
            CCSize textureSize = _normalTextureSize;
            if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
            {
                _buttonNormalRenderer->setScale(1.0f);
                return;
            }
            float scaleX = _size.width / textureSize.width;
            float scaleY = _size.height / textureSize.height;
            _buttonNormalRenderer->setScaleX(scaleX);
            _buttonNormalRenderer->setScaleY(scaleY);
            _normalTextureScaleXInSize = scaleX;
            _normalTextureScaleYInSize = scaleY;
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
            _pressedTextureScaleXInSize = _pressedTextureScaleYInSize = 1.0f;
        }
    }
    else
    {
        if (_scale9Enabled)
        {
            static_cast<extension::CCScale9Sprite*>(_buttonClickedRenderer)->setPreferredSize(_size);
            _pressedTextureScaleXInSize = _pressedTextureScaleYInSize = 1.0f;
        }
        else
        {
            CCSize textureSize = _pressedTextureSize;
            if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
            {
                _buttonClickedRenderer->setScale(1.0f);
                return;
            }
            float scaleX = _size.width / _pressedTextureSize.width;
            float scaleY = _size.height / _pressedTextureSize.height;
            _buttonClickedRenderer->setScaleX(scaleX);
            _buttonClickedRenderer->setScaleY(scaleY);
            _pressedTextureScaleXInSize = scaleX;
            _pressedTextureScaleYInSize = scaleY;
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
            static_cast<extension::CCScale9Sprite*>(_buttonDisableRenderer)->setPreferredSize(_size);
        }
        else
        {
            CCSize textureSize = _disabledTextureSize;
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
    _titleRenderer->setString(text.c_str());
}

const char* Button::getTitleText() const
{
    return _titleRenderer->getString();
}

void Button::setTitleColor(const ccColor3B& color)
{
    _titleColor = color;
    _titleRenderer->updateDisplayedColor(color);
}

const ccColor3B& Button::getTitleColor() const
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
    return _titleRenderer->getFontName();
}
    
void Button::updateTextureColor()
{
    updateColorToRenderer(_buttonNormalRenderer);
    updateColorToRenderer(_buttonClickedRenderer);
    updateColorToRenderer(_buttonDisableRenderer);
}
    
void Button::updateTextureOpacity()
{
    updateOpacityToRenderer(_buttonNormalRenderer);
    updateOpacityToRenderer(_buttonClickedRenderer);
    updateOpacityToRenderer(_buttonDisableRenderer);
}
    
void Button::updateTextureRGBA()
{
    updateRGBAToRenderer(_buttonNormalRenderer);
    updateRGBAToRenderer(_buttonClickedRenderer);
    updateRGBAToRenderer(_buttonDisableRenderer);
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