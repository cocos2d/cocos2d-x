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

#include "ui/UIButton.h"
#include "ui/UIScale9Sprite.h"
#include "2d/CCLabel.h"
#include "2d/CCSprite.h"
#include "2d/CCActionInterval.h"
#include "platform/CCFileUtils.h"

NS_CC_BEGIN

namespace ui {

static const int NORMAL_RENDERER_Z = (-2);
static const int PRESSED_RENDERER_Z = (-2);
static const int DISABLED_RENDERER_Z = (-2);
static const int TITLE_RENDERER_Z = (-1);
static const float ZOOM_ACTION_TIME_STEP = 0.05;
    
IMPLEMENT_CLASS_GUI_INFO(Button)
    
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
_normalTexType(TextureResType::LOCAL),
_pressedTexType(TextureResType::LOCAL),
_disabledTexType(TextureResType::LOCAL),
_normalTextureSize(_contentSize),
_pressedTextureSize(_contentSize),
_disabledTextureSize(_contentSize),
_pressedActionEnabled(false),
_normalTextureScaleXInSize(1.0f),
_normalTextureScaleYInSize(1.0f),
_pressedTextureScaleXInSize(1.0f),
_pressedTextureScaleYInSize(1.0f),
_zoomScale(0.1f),
_normalTextureLoaded(false),
_pressedTextureLoaded(false),
_disabledTextureLoaded(false),
_normalTextureAdaptDirty(true),
_pressedTextureAdaptDirty(true),
_disabledTextureAdaptDirty(true),
_fontName("Thonburi"),
_fontSize(10),
_type(FontType::SYSTEM),
_state(State::NORMAL),
_normalBackgroundColor(Color3B::WHITE),
_pressedBackgroundColor(Color3B::WHITE),
_disabledBackgroundColor(Color3B::WHITE),
_normalBackgroundOpacity(255),
_pressedBackgroundOpacity(255),
_disabledBackgroundOpacity(255),
_normalTitleColor(Color3B::WHITE),
_pressedTitleColor(Color3B::WHITE),
_disabledTitleColor(Color3B::WHITE),
_normalTitleOpacity(255),
_pressedTitleOpacity(255),
_disabledTitleOpacity(255)
{
    setTouchEnabled(true);
}

Button::~Button()
{
}

Button* Button::create()
{
    Button* widget = new (std::nothrow) Button();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}
    
Button* Button::create(const std::string &normalImage,
                       const std::string& selectedImage ,
                       const std::string& disableImage,
                       TextureResType texType)
{
    Button *btn = new (std::nothrow) Button;
    if (btn && btn->init(normalImage,selectedImage,disableImage,texType)) {
        btn->autorelease();
        return btn;
    }
    CC_SAFE_DELETE(btn);
    return nullptr;
}
    
bool Button::init(const std::string &normalImage,
                  const std::string& selectedImage ,
                  const std::string& disableImage,
                  TextureResType texType)
{
    bool ret = true;
    do {
        if (!Widget::init()) {
            ret = false;
            break;
        }
        
        this->loadTextures(normalImage, selectedImage, disableImage,texType);
    } while (0);
    return ret;
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
    _buttonNormalRenderer = Scale9Sprite::create();
    _buttonClickedRenderer = Scale9Sprite::create();
    _buttonDisableRenderer = Scale9Sprite::create();
    _buttonClickedRenderer->setScale9Enabled(false);
    _buttonNormalRenderer->setScale9Enabled(false);
    _buttonDisableRenderer->setScale9Enabled(false);
    
    _titleRenderer = Label::create();
    _titleRenderer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

    addProtectedChild(_buttonNormalRenderer, NORMAL_RENDERER_Z, -1);
    addProtectedChild(_buttonClickedRenderer, PRESSED_RENDERER_Z, -1);
    addProtectedChild(_buttonDisableRenderer, DISABLED_RENDERER_Z, -1);
    addProtectedChild(_titleRenderer, TITLE_RENDERER_Z, -1);
}

void Button::setScale9Enabled(bool able)
{
    if (_scale9Enabled == able)
    {
        return;
    }
    
    _scale9Enabled = able;
    
    _buttonNormalRenderer->setScale9Enabled(_scale9Enabled);
    _buttonClickedRenderer->setScale9Enabled(_scale9Enabled);
    _buttonDisableRenderer->setScale9Enabled(_scale9Enabled);
   
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
    
    _brightStyle = BrightStyle::NONE;
    setBright(_bright);
}

bool Button::isScale9Enabled()const
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

void Button::loadTextures(const std::string& normal,
                          const std::string& selected,
                          const std::string& disabled,
                          TextureResType texType)
{
    loadTextureNormal(normal,texType);
    loadTexturePressed(selected,texType);
    loadTextureDisabled(disabled,texType);
}

void Button::loadTextureNormal(const std::string& normal,TextureResType texType)
{
    if (normal.empty())
    {
        return;
    }
    _normalFileName = normal;
    _normalTexType = texType;
    
    switch (_normalTexType)
    {
        case TextureResType::LOCAL:
            _buttonNormalRenderer->initWithFile(normal);
            break;
        case TextureResType::PLIST:
            _buttonNormalRenderer->initWithSpriteFrameName(normal);
            break;
        default:
            break;
    }
    
    _normalTextureSize = _buttonNormalRenderer->getContentSize();
    updateFlippedX();
    updateFlippedY();
    this->updateChildrenDisplayedRGBA();
    
    updateContentSizeWithTextureSize(_normalTextureSize);
    _normalTextureLoaded = true;
    _normalTextureAdaptDirty = true;
}

void Button::loadTexturePressed(const std::string& selected,TextureResType texType)
{
    if (selected.empty())
    {
        return;
    }
    _clickedFileName = selected;
    _pressedTexType = texType;

    switch (_pressedTexType)
    {
        case TextureResType::LOCAL:
            _buttonClickedRenderer->initWithFile(selected);
            break;
        case TextureResType::PLIST:
            _buttonClickedRenderer->initWithSpriteFrameName(selected);
            break;
        default:
            break;
    }
    
    _pressedTextureSize = _buttonClickedRenderer->getContentSize();
    //TODO: mark as dirty
    updateFlippedX();
    updateFlippedY();
    this->updateChildrenDisplayedRGBA();

    _pressedTextureLoaded = true;
    _pressedTextureAdaptDirty = true;
}

void Button::loadTextureDisabled(const std::string& disabled,TextureResType texType)
{
    if (disabled.empty())
    {
        return;
    }
    _disabledFileName = disabled;
    _disabledTexType = texType;

    switch (_disabledTexType)
    {
        case TextureResType::LOCAL:
            _buttonDisableRenderer->initWithFile(disabled);
            break;
        case TextureResType::PLIST:
            _buttonDisableRenderer->initWithSpriteFrameName(disabled);
            break;
        default:
            break;
    }

    _disabledTextureSize = _buttonDisableRenderer->getContentSize();
    updateFlippedX();
    updateFlippedY();
    this->updateChildrenDisplayedRGBA();

    _disabledTextureLoaded = true;
    _disabledTextureAdaptDirty = true;
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
    _buttonNormalRenderer->setCapInsets(capInsets);
}

const Rect& Button::getCapInsetsNormalRenderer()const
{
    return _capInsetsNormal;
}

void Button::setCapInsetsPressedRenderer(const Rect &capInsets)
{
    _capInsetsPressed = capInsets;
    if (!_scale9Enabled)
    {
        return;
    }
    _buttonClickedRenderer->setCapInsets(capInsets);
}

const Rect& Button::getCapInsetsPressedRenderer()const
{
    return _capInsetsPressed;
}

void Button::setCapInsetsDisabledRenderer(const Rect &capInsets)
{
    _capInsetsDisabled = capInsets;
    if (!_scale9Enabled)
    {
        return;
    }
    _buttonDisableRenderer->setCapInsets(capInsets);
}

const Rect& Button::getCapInsetsDisabledRenderer()const
{
    return _capInsetsDisabled;
}
    
static Color3B multiplyColors(const Color3B& color1, const Color3B& color2)
{
    return Color3B(color1.r * color2.r/255.0,color1.g * color2.g/255.0,color1.b * color2.b/255.0);
}
    
static GLubyte multiplyOpacity(GLubyte opacity1, GLubyte opacity2)
{
    return opacity1 * opacity2/255.0;
}

void Button::onPressStateChangedToNormal()
{
    _buttonNormalRenderer->setVisible(true);
    _buttonClickedRenderer->setVisible(false);
    _buttonDisableRenderer->setVisible(false);
    _state = State::NORMAL;
    
    Color3B realBackgroundColor(multiplyColors(_normalBackgroundColor, _displayedColor));
    GLubyte realBackgroundOpacity(multiplyOpacity(_normalBackgroundOpacity, _displayedOpacity));
    Color3B realTitleColor(multiplyColors(_normalTitleColor, _displayedColor));
    GLubyte realTitleOpacity(multiplyOpacity(_normalTitleOpacity, _displayedOpacity));
    
    if (_pressedActionEnabled)
    {
        _buttonNormalRenderer->stopAllActions();
        _buttonClickedRenderer->stopAllActions();
        _titleRenderer->stopAllActions();
        
        if(_pressedTextureLoaded)
        {
            _buttonNormalRenderer->setScaleX(_normalTextureScaleXInSize + _buttonClickedRenderer->getScaleX() - _pressedTextureScaleXInSize);
            _buttonNormalRenderer->setScaleY(_normalTextureScaleYInSize + _buttonClickedRenderer->getScaleY() - _pressedTextureScaleYInSize);
        }
        FiniteTimeAction *backZoomAction = ScaleTo::create(ZOOM_ACTION_TIME_STEP, _normalTextureScaleXInSize, _normalTextureScaleYInSize);
        FiniteTimeAction *backColorAction = TintTo::create(ZOOM_ACTION_TIME_STEP, realBackgroundColor.r, realBackgroundColor.g, realBackgroundColor.b);
        FiniteTimeAction *backOpacityAction = FadeTo::create(ZOOM_ACTION_TIME_STEP, realBackgroundOpacity);
        Action *backSpawn = Spawn::create(backZoomAction, backColorAction, backOpacityAction, NULL);
        _buttonNormalRenderer->runAction(backSpawn);
        _buttonClickedRenderer->setScale(_pressedTextureScaleXInSize, _pressedTextureScaleYInSize);
        
        FiniteTimeAction *titleZoomAction = ScaleTo::create(ZOOM_ACTION_TIME_STEP, _normalTextureScaleXInSize, _normalTextureScaleYInSize);
        FiniteTimeAction *titleColorAction = TintTo::create(ZOOM_ACTION_TIME_STEP, realTitleColor.r, realTitleColor.g, realTitleColor.b);
        FiniteTimeAction *titleOpacityAction = FadeTo::create(ZOOM_ACTION_TIME_STEP, realTitleOpacity);
        Action *titleSpawn = Spawn::create(titleZoomAction, titleColorAction, titleOpacityAction, NULL);
        _titleRenderer->runAction(titleSpawn);
    }
    else
    {
        _buttonNormalRenderer->setColor(realBackgroundColor);
        _buttonNormalRenderer->setOpacity(realBackgroundOpacity);
        _titleRenderer->setColor(realTitleColor);
        _titleRenderer->setOpacity(realTitleOpacity);
    }
}

void Button::onPressStateChangedToPressed()
{
    _state = State::PRESSED;
    _buttonDisableRenderer->setVisible(false);
    
    Color3B realBackgroundColor(multiplyColors(_pressedBackgroundColor, _displayedColor));
    GLubyte realBackgroundOpacity(multiplyOpacity(_pressedBackgroundOpacity, _displayedOpacity));
    Color3B realTitleColor(multiplyColors(_pressedTitleColor, _displayedColor));
    GLubyte realTitleOpacity(multiplyOpacity(_pressedTitleOpacity, _displayedOpacity));
    
    Scale9Sprite* render = nullptr;
    if (_pressedTextureLoaded)
    {
        _buttonNormalRenderer->setVisible(false);
        _buttonClickedRenderer->setVisible(true);
        render = _buttonClickedRenderer;
        _buttonClickedRenderer->setColor(realBackgroundColor);
        _buttonClickedRenderer->setOpacity(realBackgroundOpacity);
        _buttonNormalRenderer->setScale(_normalTextureScaleXInSize, _normalTextureScaleYInSize);
    }
    else
    {
        _buttonNormalRenderer->setVisible(true);
        _buttonClickedRenderer->setVisible(false);
        _buttonNormalRenderer->setColor(multiplyColors(_normalBackgroundColor, _displayedColor));
        _buttonNormalRenderer->setOpacity(multiplyOpacity(_normalBackgroundOpacity, _displayedOpacity));
        render = _buttonNormalRenderer;
    }
    if (_pressedActionEnabled)
    {
        _buttonNormalRenderer->stopAllActions();
        _buttonClickedRenderer->stopAllActions();
        _titleRenderer->stopAllActions();
        
        FiniteTimeAction *backZoomAction = ScaleTo::create(ZOOM_ACTION_TIME_STEP, _pressedTextureScaleXInSize + _zoomScale, _pressedTextureScaleYInSize + _zoomScale);
        FiniteTimeAction *backColorAction = TintTo::create(ZOOM_ACTION_TIME_STEP, realBackgroundColor.r, realBackgroundColor.g, realBackgroundColor.b);
        FiniteTimeAction *backOpacityAction = FadeTo::create(ZOOM_ACTION_TIME_STEP, realBackgroundOpacity);
        Action *backSpawn = Spawn::create(backZoomAction, backColorAction, backOpacityAction, NULL);
        render->runAction(backSpawn);
        
        FiniteTimeAction *titleZoomAction = ScaleTo::create(ZOOM_ACTION_TIME_STEP, _pressedTextureScaleXInSize + _zoomScale, _pressedTextureScaleYInSize + _zoomScale);
        FiniteTimeAction *titleColorAction = TintTo::create(ZOOM_ACTION_TIME_STEP, realTitleColor.r, realTitleColor.g, realTitleColor.b);
        FiniteTimeAction *titleOpacityAction = FadeTo::create(ZOOM_ACTION_TIME_STEP, realTitleOpacity);
        Action *titleSpawn = Spawn::create(titleZoomAction, titleColorAction, titleOpacityAction, NULL);
        _titleRenderer->runAction(titleSpawn);
    }
    else
    {
        render->setColor(realBackgroundColor);
        render->setOpacity(realBackgroundOpacity);
        _titleRenderer->setColor(realTitleColor);
        _titleRenderer->setOpacity(realTitleOpacity);
    }
}

void Button::onPressStateChangedToDisabled()
{
    _state = State::DISABLED;
    _buttonNormalRenderer->setVisible(false);
    _buttonClickedRenderer->setVisible(false);
    _buttonDisableRenderer->setVisible(true);
    if (_pressedActionEnabled)
    {
        _buttonNormalRenderer->stopAllActions();
        _buttonClickedRenderer->stopAllActions();
        _titleRenderer->stopAllActions();
    }
    _buttonNormalRenderer->setScale(_normalTextureScaleXInSize, _normalTextureScaleYInSize);
    _buttonClickedRenderer->setScale(_pressedTextureScaleXInSize, _pressedTextureScaleYInSize);
    _titleRenderer->setScaleX(_normalTextureScaleXInSize);
    _titleRenderer->setScaleY(_normalTextureScaleYInSize);
    
    Color3B realBackgroundColor(multiplyColors(_disabledBackgroundColor, _displayedColor));
    GLubyte realBackgroundOpacity(multiplyOpacity(_disabledBackgroundOpacity,_displayedOpacity));
    Color3B realTitleColor(multiplyColors(_disabledTitleColor, _displayedColor));
    GLubyte realTitleOpacity(multiplyOpacity(_disabledTitleOpacity,_displayedOpacity));
    
    if (_disabledTextureLoaded)
    {
        _buttonNormalRenderer->setColor(realBackgroundColor);
        _buttonNormalRenderer->setOpacity(realBackgroundOpacity);
    }
    else
    {
        _buttonDisableRenderer->setColor(realBackgroundColor);
        _buttonDisableRenderer->setOpacity(realBackgroundOpacity);
    }
    _titleRenderer->setOpacity(realTitleOpacity);
    _titleRenderer->setColor(realTitleColor);
}
    
void Button::updateDisplayedOpacity(GLubyte parentOpacity)
{
    _displayedOpacity = _realOpacity * parentOpacity/255.0;
    updateColor();
    
    if (_cascadeOpacityEnabled)
    {
        for(auto child : _children){
            child->updateDisplayedOpacity(_displayedOpacity);
        }
    }
    _buttonNormalRenderer->setOpacity(multiplyOpacity(_pressedBackgroundOpacity, _displayedOpacity));
    _buttonNormalRenderer->setOpacity(multiplyOpacity(_disabledBackgroundOpacity, _displayedOpacity));
    switch (_state) {
        case State::NORMAL:
            _titleRenderer->setOpacity(multiplyOpacity(_disabledBackgroundOpacity, _displayedOpacity));
            _buttonNormalRenderer->setOpacity(multiplyOpacity(_normalBackgroundOpacity, _displayedOpacity));
            break;
        case State::PRESSED:
            _titleRenderer->setOpacity(multiplyOpacity(_disabledBackgroundOpacity, _displayedOpacity));
            if(!_pressedTextureLoaded)
                _buttonNormalRenderer->setOpacity(multiplyOpacity(_pressedBackgroundOpacity, _displayedOpacity));
            break;
        case State::DISABLED:
            _titleRenderer->setOpacity(multiplyOpacity(_disabledBackgroundOpacity, _displayedOpacity));
            if(!_disabledTextureLoaded)
                _buttonNormalRenderer->setOpacity(multiplyOpacity(_disabledBackgroundOpacity, _displayedOpacity));
            break;
    }
}

void Button::updateDisplayedColor(const Color3B& parentColor)
{
    _displayedColor.r = _realColor.r * parentColor.r/255.0;
    _displayedColor.g = _realColor.g * parentColor.g/255.0;
    _displayedColor.b = _realColor.b * parentColor.b/255.0;
    updateColor();
    
    if (_cascadeColorEnabled)
    {
        for(const auto &child : _children){
            child->updateDisplayedColor(_displayedColor);
        }
    }
    _buttonNormalRenderer->setColor(multiplyColors(_pressedBackgroundColor, _displayedColor));
    _buttonNormalRenderer->setColor(multiplyColors(_disabledBackgroundColor, _displayedColor));
    switch (_state) {
        case State::NORMAL:
            _titleRenderer->setColor(multiplyColors(_disabledBackgroundColor, _displayedColor));
            _buttonNormalRenderer->setColor(multiplyColors(_normalBackgroundColor, _displayedColor));
            break;
        case State::PRESSED:
            _titleRenderer->setColor(multiplyColors(_disabledBackgroundColor, _displayedColor));
            if(!_pressedTextureLoaded)
                _buttonNormalRenderer->setColor(multiplyColors(_pressedBackgroundColor, _displayedColor));
            break;
        case State::DISABLED:
            _titleRenderer->setColor(multiplyColors(_disabledBackgroundColor, _displayedColor));
            if(!_disabledTextureLoaded)
                _buttonNormalRenderer->setColor(multiplyColors(_disabledBackgroundColor, _displayedColor));
            break;
    }
}

void Button::updateFlippedX()
{
    float flip = _flippedX ? -1.0f : 1.0f;
    _titleRenderer->setScaleX(flip);

    _buttonNormalRenderer->setFlippedX(_flippedX);
    _buttonClickedRenderer->setFlippedX(_flippedX);
    _buttonDisableRenderer->setFlippedX(_flippedX);
}
    
void Button::updateFlippedY()
{
    float flip = _flippedY ? -1.0f : 1.0f;
    _titleRenderer->setScaleY(flip);
    _buttonNormalRenderer->setFlippedY(_flippedY);
    _buttonClickedRenderer->setFlippedY(_flippedY);
    _buttonDisableRenderer->setFlippedY(_flippedY);
}
    
void Button::updateTitleLocation()
{
    _titleRenderer->setPosition(_contentSize.width * 0.5f, _contentSize.height * 0.5f);
}

void Button::onSizeChanged()
{
    Widget::onSizeChanged();
    updateTitleLocation();
    _normalTextureAdaptDirty = true;
    _pressedTextureAdaptDirty = true;
    _disabledTextureAdaptDirty = true;
}
    
void Button::adaptRenderers()
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

Size Button::getVirtualRendererSize() const
{
    Size titleSize = _titleRenderer->getContentSize();
    if (!_normalTextureLoaded && _titleRenderer->getString().size() > 0) {
        return titleSize;
    }
    return _normalTextureSize;
}

Node* Button::getVirtualRenderer()
{
    if (_bright)
    {
        switch (_brightStyle)
        {
            case BrightStyle::NORMAL:
                return _buttonNormalRenderer;
            case BrightStyle::HIGHLIGHT:
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
            _normalTextureScaleXInSize = _normalTextureScaleYInSize = 1.0f;
        }
    }
    else
    {
        if (_scale9Enabled)
        {
            _buttonNormalRenderer->setPreferredSize(_contentSize);
            _normalTextureScaleXInSize = _normalTextureScaleYInSize = 1.0f;
            _buttonNormalRenderer->setScale(_normalTextureScaleXInSize,_normalTextureScaleYInSize);
        }
        else
        {
            Size textureSize = _normalTextureSize;
            if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
            {
                _buttonNormalRenderer->setScale(1.0f);
                return;
            }
            float scaleX = _contentSize.width / textureSize.width;
            float scaleY = _contentSize.height / textureSize.height;
            _buttonNormalRenderer->setScaleX(scaleX);
            _buttonNormalRenderer->setScaleY(scaleY);
            _normalTextureScaleXInSize = scaleX;
            _normalTextureScaleYInSize = scaleY;
        }
    }

    _buttonNormalRenderer->setPosition(_contentSize.width / 2.0f, _contentSize.height / 2.0f);
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
            _buttonClickedRenderer->setPreferredSize(_contentSize);
            _pressedTextureScaleXInSize = _pressedTextureScaleYInSize = 1.0f;
            _buttonClickedRenderer->setScale(_pressedTextureScaleXInSize,_pressedTextureScaleYInSize);
        }
        else
        {
            Size textureSize = _pressedTextureSize;
            if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
            {
                _buttonClickedRenderer->setScale(1.0f);
                return;
            }
            float scaleX = _contentSize.width / _pressedTextureSize.width;
            float scaleY = _contentSize.height / _pressedTextureSize.height;
            _buttonClickedRenderer->setScaleX(scaleX);
            _buttonClickedRenderer->setScaleY(scaleY);
            _pressedTextureScaleXInSize = scaleX;
            _pressedTextureScaleYInSize = scaleY;
        }
    }
    _buttonClickedRenderer->setPosition(_contentSize.width / 2.0f, _contentSize.height / 2.0f);
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
            _buttonDisableRenderer->setScale(1.0);
            _buttonDisableRenderer->setPreferredSize(_contentSize);
        }
        else
        {
            Size textureSize = _disabledTextureSize;
            if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
            {
                _buttonDisableRenderer->setScale(1.0f);
                return;
            }
            float scaleX = _contentSize.width / _disabledTextureSize.width;
            float scaleY = _contentSize.height / _disabledTextureSize.height;
            _buttonDisableRenderer->setScaleX(scaleX);
            _buttonDisableRenderer->setScaleY(scaleY);
        }
    }
    _buttonDisableRenderer->setPosition(_contentSize.width / 2.0f, _contentSize.height / 2.0f);
}

void Button::setPressedActionEnabled(bool enabled)
{
    _pressedActionEnabled = enabled;
}

void Button::setTitleText(const std::string& text)
{
    _titleRenderer->setString(text);
    if (_ignoreSize)
    {
        Size s = getVirtualRendererSize();
        this->setContentSize(s);
    }
}

const std::string& Button::getTitleText() const
{
    return _titleRenderer->getString();
}

void Button::setTitleColor(const Color3B& color)
{
    _normalTitleColor = color;
    _pressedTitleColor = color;
    _disabledTitleColor = color;
    _titleRenderer->setColor(color);
}

const Color3B& Button::getTitleColor() const
{
    return _titleRenderer->getColor();
}

void Button::setTitleFontSize(float size)
{
    if (_type == FontType::SYSTEM) {
        _titleRenderer->setSystemFontSize(size);
    }
    else{
        TTFConfig config = _titleRenderer->getTTFConfig();
        config.fontSize = size;
        _titleRenderer->setTTFConfig(config);
    }
    _fontSize = size;
}

float Button::getTitleFontSize() const
{
    return _fontSize;
}
    
void Button::setZoomScale(float scale)
{
    _zoomScale = scale;
}
    
float Button::getZoomScale()const
{
    return _zoomScale;
}

void Button::setTitleFontName(const std::string& fontName)
{
    if(FileUtils::getInstance()->isFileExist(fontName))
    {
        TTFConfig config = _titleRenderer->getTTFConfig();
        config.fontFilePath = fontName;
        config.fontSize = _fontSize;
        _titleRenderer->setTTFConfig(config);
        _type = FontType::TTF;
    } else{
        _titleRenderer->setSystemFontName(fontName);
        _type = FontType::SYSTEM;
    }
    _fontName = fontName;
}
    
Label* Button::getTitleRenderer()const
{
    return _titleRenderer;
}

const std::string& Button::getTitleFontName() const
{
    return _fontName;
}
    
std::string Button::getDescription() const
{
    return "Button";
}

Widget* Button::createCloneInstance()
{
    return Button::create();
}
    
void Button::setNormalBackgroundColor(const Color3B &color)
{
    _normalBackgroundColor = color;
    if(_state == State::NORMAL)
        _buttonNormalRenderer->setColor(multiplyColors(color, _displayedColor));
}

const Color3B& Button::getNormalBackgroundColor() const
{
    return _normalBackgroundColor;
}

void Button::setPressedBackgroundColor(const Color3B &color)
{
    _pressedBackgroundColor = color;
    if(_state == State::PRESSED)
    {
        if(_pressedTextureLoaded)
            _buttonClickedRenderer->setColor(multiplyColors(color, _displayedColor));
        else
            _buttonNormalRenderer->setColor(multiplyColors(color, _displayedColor));
    }
}

const Color3B& Button::getPressedBackgroundColor() const
{
    return _pressedBackgroundColor;
}

void Button::setDisabledBackgroundColor(const Color3B &color)
{
    _disabledBackgroundColor = color;
    if(_state == State::DISABLED)
    {
        if(_pressedTextureLoaded)
            _buttonDisableRenderer->setColor(multiplyColors(color, _displayedColor));
        else
            _buttonNormalRenderer->setColor(multiplyColors(color, _displayedColor));
    }
}

const Color3B& Button::getDisabledBackgroundColor() const
{
    return _disabledBackgroundColor;
}


void Button::setNormalBackgroundOpacity(GLubyte opacity)
{
    _normalBackgroundOpacity = opacity;
    if(_state == State::NORMAL)
        _buttonNormalRenderer->setOpacity(multiplyOpacity(opacity, _displayedOpacity));
}

GLubyte Button::getNormalBackgroundOpacity() const
{
    return _normalBackgroundOpacity;
}

void Button::setPressedBackgroundOpacity(GLubyte opacity)
{
    _pressedBackgroundOpacity = opacity;
    if(_state == State::PRESSED)
    {
        if(_pressedTextureLoaded)
            _buttonClickedRenderer->setOpacity(multiplyOpacity(opacity, _displayedOpacity));
        else
            _buttonNormalRenderer->setOpacity(multiplyOpacity(opacity, _displayedOpacity));
    }
}

GLubyte Button::getPressedBackgroundOpacity() const
{
    return _pressedBackgroundOpacity;
}

void Button::setDisabledBackgroundOpacity(GLubyte opacity)
{
    _disabledBackgroundOpacity = opacity;
    if(_state == State::DISABLED)
    {
        if(_pressedTextureLoaded)
            _buttonDisableRenderer->setOpacity(multiplyOpacity(opacity, _displayedOpacity));
        else
            _buttonNormalRenderer->setOpacity(multiplyOpacity(opacity, _displayedOpacity));
    }
}

GLubyte Button::getDisabledBackgroundOpacity() const
{
    return _disabledBackgroundOpacity;
}


void Button::setNormalTitleColor(const Color3B &color)
{
    _normalTitleColor = color;
    if(_state == State::NORMAL)
        _titleRenderer->setColor(multiplyColors(color, _displayedColor));
}

const Color3B& Button::getNormalTitleColor() const
{
    return _normalTitleColor;
}

void Button::setPressedTitleColor(const Color3B &color)
{
    _pressedTitleColor = color;
    if(_state == State::PRESSED)
        _titleRenderer->setColor(multiplyColors(color, _displayedColor));
}

const Color3B& Button::getPressedTitleColor() const
{
    return _pressedTitleColor;
}

void Button::setDisabledTitleColor(const Color3B &color)
{
    _disabledTitleColor = color;
    if(_state == State::DISABLED)
        _titleRenderer->setColor(multiplyColors(color, _displayedColor));
}

const Color3B& Button::getDisabledTitleColor() const
{
    return _disabledTitleColor;
}


void Button::setNormalTitleOpacity(GLubyte opacity)
{
    _normalTitleOpacity = opacity;
    if(_state == State::NORMAL)
        _titleRenderer->setOpacity(multiplyOpacity(opacity, _displayedOpacity));
}

GLubyte Button::getNormalTitleOpacity() const
{
    return _normalTitleOpacity;
}

void Button::setPressedTitleOpacity(GLubyte opacity)
{
    _pressedTitleOpacity = opacity;
    if(_state == State::PRESSED)
        _titleRenderer->setOpacity(multiplyOpacity(opacity, _displayedOpacity));
}

GLubyte Button::getPressedTitleOpacity() const
{
    return _pressedTitleOpacity;
}

void Button::setDisabledTitleOpacity(GLubyte opacity)
{
    _disabledTitleOpacity = opacity;
    if(_state == State::DISABLED)
        _titleRenderer->setOpacity(multiplyOpacity(opacity, _displayedOpacity));
}

GLubyte Button::getDisabledTitleOpacity() const
{
    return _disabledTitleOpacity;
}

void Button::copySpecialProperties(Widget *widget)
{
    Button* button = dynamic_cast<Button*>(widget);
    if (button)
    {
        _prevIgnoreSize = button->_prevIgnoreSize;
        setScale9Enabled(button->_scale9Enabled);
        loadTextureNormal(button->_normalFileName, button->_normalTexType);
        loadTexturePressed(button->_clickedFileName, button->_pressedTexType);
        loadTextureDisabled(button->_disabledFileName, button->_disabledTexType);
        setCapInsetsNormalRenderer(button->_capInsetsNormal);
        setCapInsetsPressedRenderer(button->_capInsetsPressed);
        setCapInsetsDisabledRenderer(button->_capInsetsDisabled);
        setTitleText(button->getTitleText());
        setTitleFontName(button->getTitleFontName());
        setTitleFontSize(button->getTitleFontSize());
        setTitleColor(button->getTitleColor());
        setPressedActionEnabled(button->_pressedActionEnabled);
        setZoomScale(button->_zoomScale);
        setNormalBackgroundColor(button->_normalBackgroundColor);
        setPressedBackgroundColor(button->_pressedBackgroundColor);
        setDisabledBackgroundColor(button->_disabledBackgroundColor);
        setNormalBackgroundOpacity(button->_normalBackgroundOpacity);
        setPressedBackgroundOpacity(button->_pressedBackgroundOpacity);
        setDisabledBackgroundOpacity(button->_disabledBackgroundOpacity);
        setNormalTitleColor(button->_normalTitleColor);
        setPressedTitleColor(button->_pressedTitleColor);
        setDisabledTitleColor(button->_disabledTitleColor);
        setNormalTitleOpacity(button->_normalTitleOpacity);
        setPressedTitleOpacity(button->_pressedTitleOpacity);
        setDisabledTitleOpacity(button->_disabledTitleOpacity);
    }
}

}

NS_CC_END
