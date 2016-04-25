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
#include "ui/UIHelper.h"
#include <algorithm>
#include "editor-support/cocostudio/CocosStudioExtension.h"

NS_CC_BEGIN

namespace ui {

static const int BUTTON_RENDERER_Z = (-2);
static const int TITLE_RENDERER_Z = (-1);
static const float ZOOM_ACTION_TIME_STEP = 0.05f;

IMPLEMENT_CLASS_GUI_INFO(Button)

Button::Button():
_buttonNormalRenderer(nullptr),
_buttonPressedRenderer(nullptr),
_buttonDisabledRenderer(nullptr),
_buttonMouseOverRenderer(nullptr),
_buttonRenderer(nullptr),
_titleRenderer(nullptr),
_imageScale(1.0f),
_zoomScale(0.1f),
_normalFileName(""),
_clickedFileName(""),
_disabledFileName(""),
_mouseOverFileName(""),
_normalTexType(TextureResType::LOCAL),
_pressedTexType(TextureResType::LOCAL),
_disabledTexType(TextureResType::LOCAL),
_mouseOverTexType(TextureResType::LOCAL),
_fontName(""),
_prevIgnoreSize(true),
_scale9Enabled(false),
_pressedActionEnabled(false),
_capInsetsNormal(Rect::ZERO),
_capInsetsPressed(Rect::ZERO),
_capInsetsDisabled(Rect::ZERO),
_capInsetsMouseOver(Rect::ZERO),
_normalTextureSize(_contentSize),
_pressedTextureSize(_contentSize),
_disabledTextureSize(_contentSize),
_mouseOverTextureSize(_contentSize),
_normalTextureScaleXInSize(1.0f),
_normalTextureScaleYInSize(1.0f),
_pressedTextureScaleXInSize(1.0f),
_pressedTextureScaleYInSize(1.0f),
_titleScale(1.0f),
_normalTextureLoaded(false),
_pressedTextureLoaded(false),
_disabledTextureLoaded(false),
_mouseOverTextureLoaded(false),
_normalTextureAdaptDirty(true),
_pressedTextureAdaptDirty(true),
_disabledTextureAdaptDirty(true),
_mouseOverTextureAdaptDirty(true),
_titileAdaptDirty(true),
_fontSize(10),
_type(FontType::SYSTEM),
_state(State::NORMAL),
_normalBackgroundColor(Color3B::WHITE),
_pressedBackgroundColor(Color3B::WHITE),
_disabledBackgroundColor(Color3B::WHITE),
_mouseOverBackgroundColor(Color3B::WHITE),
_normalBackgroundOpacity(255),
_pressedBackgroundOpacity(255),
_disabledBackgroundOpacity(127),
_mouseOverBackgroundOpacity(255),
_normalTitleColor(Color3B::WHITE),
_pressedTitleColor(Color3B::WHITE),
_disabledTitleColor(Color3B::WHITE),
_mouseOverTitleColor(Color3B::WHITE),
_normalTitleOpacity(255),
_pressedTitleOpacity(255),
_disabledTitleOpacity(255),
_mouseOverTitleOpacity(255),
_leftPadding(0),
_rightPadding(0),
_topPadding(0),
_bottomPadding(0),
_leftOffsets(0.0f),
_topOffsets(0.0f),
_rightOffsets(0.0f),
_bottomOffsets(0),
_overflowLabel(static_cast<int>(Label::Overflow::NONE)),
_wordWrapLabel(true),
_hAlignment(TextHAlignment::CENTER),
_vAlignment(TextVAlignment::CENTER)
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
                       const std::string& highlightdImage,
                       TextureResType texType)
{
    Button *btn = new (std::nothrow) Button;
    if (btn && btn->init(normalImage, selectedImage, disableImage, highlightdImage, texType))
    {
        btn->autorelease();
        return btn;
    }
    CC_SAFE_DELETE(btn);
    return nullptr;
}

bool Button::init(const std::string &normalImage,
                  const std::string& selectedImage ,
                  const std::string& disableImage,
                  const std::string& highlightdImage,
                  TextureResType texType)
{
    bool ret = true;
    do
    {
        if (!Widget::init())
        {
            ret = false;
            break;
        }

        this->loadTextures(normalImage, selectedImage, disableImage, highlightdImage, texType);
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
    _buttonPressedRenderer = Scale9Sprite::create();
    _buttonDisabledRenderer = Scale9Sprite::create();
    _buttonMouseOverRenderer = Scale9Sprite::create();
    _buttonPressedRenderer->setRenderingType(Scale9Sprite::RenderingType::SIMPLE);
    _buttonNormalRenderer->setRenderingType(Scale9Sprite::RenderingType::SIMPLE);
    _buttonDisabledRenderer->setRenderingType(Scale9Sprite::RenderingType::SIMPLE);
    _buttonMouseOverRenderer->setRenderingType(Scale9Sprite::RenderingType::SIMPLE);
    
    _buttonRenderer = Node::create();
    
    _buttonRenderer->addChild(_buttonNormalRenderer);
    _buttonRenderer->addChild(_buttonPressedRenderer);
    _buttonRenderer->addChild(_buttonDisabledRenderer);
    _buttonRenderer->addChild(_buttonMouseOverRenderer);
    _buttonRenderer->setCascadeColorEnabled(true);
    _buttonRenderer->setCascadeOpacityEnabled(true);
    
    addProtectedChild(_buttonRenderer, BUTTON_RENDERER_Z, -1);

    //addProtectedChild(_buttonNormalRenderer, NORMAL_RENDERER_Z, -1);
    //addProtectedChild(_buttonPressedRenderer, PRESSED_RENDERER_Z, -1);
    //addProtectedChild(_buttonDisabledRenderer, DISABLED_RENDERER_Z, -1);
}

void Button::createTitleRenderer()
{
    _titleRenderer = Label::create();
    _titleRenderer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _titleRenderer->setAlignment(_hAlignment, _vAlignment);
    updateFontName();
    updateFontSize();
    updateTextColor();
    updateTextOpacity();
    addProtectedChild(_titleRenderer, TITLE_RENDERER_Z, -1);
}

void Button::setScale9Enabled(bool able)
{
    if (_scale9Enabled == able)
    {
        return;
    }

    _scale9Enabled = able;
    
    if (_scale9Enabled) {
        _buttonNormalRenderer->setRenderingType(Scale9Sprite::RenderingType::SLICE);
        _buttonPressedRenderer->setRenderingType(Scale9Sprite::RenderingType::SLICE);
        _buttonDisabledRenderer->setRenderingType(Scale9Sprite::RenderingType::SLICE);
        _buttonMouseOverRenderer->setRenderingType(Scale9Sprite::RenderingType::SLICE);
    }else{
        _buttonNormalRenderer->setRenderingType(Scale9Sprite::RenderingType::SIMPLE);
        _buttonPressedRenderer->setRenderingType(Scale9Sprite::RenderingType::SIMPLE);
        _buttonDisabledRenderer->setRenderingType(Scale9Sprite::RenderingType::SIMPLE);
        _buttonMouseOverRenderer->setRenderingType(Scale9Sprite::RenderingType::SIMPLE);
    }
    

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
    setCapInsetsMouseOverRenderer(_capInsetsMouseOver);


    _brightStyle = BrightStyle::NONE;
    setBright(_bright);

    _normalTextureAdaptDirty = true;
    _pressedTextureAdaptDirty = true;
    _disabledTextureAdaptDirty = true;
    _mouseOverTextureAdaptDirty = true;
}

bool Button::isScale9Enabled()const
{
    return _scale9Enabled;
}

void Button::ignoreContentAdaptWithSize(bool ignore)
{
    if (_unifySize)
    {
        this->updateContentSize();
        return;
    }

    if (!_scale9Enabled || (_scale9Enabled && !ignore))
    {
        Widget::ignoreContentAdaptWithSize(ignore);
        _prevIgnoreSize = ignore;
    }
}

void Button::loadTextures(const std::string& normal,
                          const std::string& selected,
                          const std::string& disabled,
                          const std::string& mouseOver,
                          TextureResType texType)
{
    loadTextureNormal(normal,texType);
    loadTexturePressed(selected,texType);
    loadTextureDisabled(disabled,texType);
    loadTextureMouseOver(mouseOver,texType);
}

void Button::loadTextureNormal(const std::string& normal,TextureResType texType)
{
    _normalFileName = normal;
    _normalTexType = texType;
    bool textureLoaded = true;
    if(normal.empty())
    {
        _buttonNormalRenderer->resetRender();
        textureLoaded = false;
    }
    else
    {
        switch (texType)
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
    }
    //FIXME: https://github.com/cocos2d/cocos2d-x/issues/12249
    if (!_ignoreSize && _customSize.equals(Size::ZERO)) {
        _customSize = _buttonNormalRenderer->getContentSize();
    }
    this->setupNormalTexture(textureLoaded);
}

void Button::setupNormalTexture(bool textureLoaded)
{
    _normalTextureSize = _buttonNormalRenderer->getContentSize();

    this->updateChildrenDisplayedRGBA();

    if (_unifySize )
    {
        if (!_scale9Enabled)
        {
            updateContentSizeWithTextureSize(this->getNormalSize());
        }
    }
    else
    {
        updateContentSizeWithTextureSize(_normalTextureSize);
    }
    _normalTextureLoaded = textureLoaded;
    _normalTextureAdaptDirty = true;
}

void Button::loadTextureNormal(SpriteFrame* normalSpriteFrame)
{
    _buttonNormalRenderer->initWithSpriteFrame(normalSpriteFrame);
    this->setupNormalTexture(nullptr != normalSpriteFrame);
}

void Button::loadTexturePressed(const std::string& selected,TextureResType texType)
{
    _clickedFileName = selected;
    _pressedTexType = texType;
    bool textureLoade = true;
    if (selected.empty())
    {
        _buttonPressedRenderer->resetRender();
        textureLoade = false;
    }
    else
    {
        switch (texType)
        {
        case TextureResType::LOCAL:
            _buttonPressedRenderer->initWithFile(selected);
            break;
        case TextureResType::PLIST:
            _buttonPressedRenderer->initWithSpriteFrameName(selected);
            break;
        default:
            break;
        }
    }
    this->setupPressedTexture(textureLoade);
}

void Button::setupPressedTexture(bool textureLoaded)
{
    _pressedTextureSize = _buttonPressedRenderer->getContentSize();

    this->updateChildrenDisplayedRGBA();

    _pressedTextureLoaded = textureLoaded;
    _pressedTextureAdaptDirty = true;
}

void Button::loadTexturePressed(SpriteFrame* pressedSpriteFrame)
{
    _buttonPressedRenderer->initWithSpriteFrame(pressedSpriteFrame);
    this->setupPressedTexture(nullptr != pressedSpriteFrame);
}

void Button::loadTextureDisabled(const std::string& disabled,TextureResType texType)
{
    _disabledFileName = disabled;
    _disabledTexType = texType;
    bool textureLoaded = true;
    if (disabled.empty())
    {
        _buttonDisabledRenderer->resetRender();
        textureLoaded = false;
    }
    else
    {
        switch (texType)
        {
        case TextureResType::LOCAL:
            _buttonDisabledRenderer->initWithFile(disabled);
            break;
        case TextureResType::PLIST:
            _buttonDisabledRenderer->initWithSpriteFrameName(disabled);
            break;
        default:
            break;
        }
    }
    this->setupDisabledTexture(textureLoaded);
}

void Button::setupDisabledTexture(bool textureLoaded)
{
    _disabledTextureSize = _buttonDisabledRenderer->getContentSize();

    this->updateChildrenDisplayedRGBA();

    _disabledTextureLoaded = textureLoaded;
    _disabledTextureAdaptDirty = true;
}

void Button::loadTextureDisabled(SpriteFrame* disabledSpriteFrame)
{
    _buttonDisabledRenderer->initWithSpriteFrame(disabledSpriteFrame);
    this->setupDisabledTexture(nullptr != disabledSpriteFrame);
}
    
void Button::loadTextureMouseOver(const std::string& mouseOver,TextureResType texType)
{
    _mouseOverFileName = mouseOver;
    _mouseOverTexType = texType;
    bool textureLoaded = true;
    if (mouseOver.empty())
    {
        _buttonMouseOverRenderer->resetRender();
        textureLoaded = false;
    }
    else
    {
        switch (texType)
        {
            case TextureResType::LOCAL:
                _buttonMouseOverRenderer->initWithFile(mouseOver);
                break;
            case TextureResType::PLIST:
                _buttonMouseOverRenderer->initWithSpriteFrameName(mouseOver);
                break;
            default:
                break;
        }
    }
    this->setupMouseOverTexture(textureLoaded);
}

void Button::setupMouseOverTexture(bool textureLoaded)
{
    _mouseOverTextureSize = _buttonMouseOverRenderer->getContentSize();
    
    this->updateChildrenDisplayedRGBA();
    
    _mouseOverTextureLoaded = textureLoaded;
    _mouseOverTextureAdaptDirty = true;
}

void Button::loadTextureMouseOver(SpriteFrame* mouseOverSpriteFrame)
{
    _buttonMouseOverRenderer->initWithSpriteFrame(mouseOverSpriteFrame);
    this->setupMouseOverTexture(nullptr != mouseOverSpriteFrame);
}

void Button::setCapInsets(const Rect &capInsets)
{
    setCapInsetsNormalRenderer(capInsets);
    setCapInsetsPressedRenderer(capInsets);
    setCapInsetsDisabledRenderer(capInsets);
    setCapInsetsMouseOverRenderer(capInsets);
}


void Button::setCapInsetsNormalRenderer(const Rect &capInsets)
{
    _capInsetsNormal = Helper::restrictCapInsetRect(capInsets, this->_normalTextureSize);

    //for performance issue
    if (!_scale9Enabled)
    {
        return;
    }
    _buttonNormalRenderer->setCapInsets(_capInsetsNormal);
}

void Button::setCapInsetsPressedRenderer(const Rect &capInsets)
{
    _capInsetsPressed = Helper::restrictCapInsetRect(capInsets, this->_pressedTextureSize);

    //for performance issue
    if (!_scale9Enabled)
    {
        return;
    }
    _buttonPressedRenderer->setCapInsets(_capInsetsPressed);
}

void Button::setCapInsetsDisabledRenderer(const Rect &capInsets)
{
    _capInsetsDisabled = Helper::restrictCapInsetRect(capInsets, this->_disabledTextureSize);

    //for performance issue
    if (!_scale9Enabled)
    {
        return;
    }
    _buttonDisabledRenderer->setCapInsets(_capInsetsDisabled);
}
    
void Button::setCapInsetsMouseOverRenderer(const Rect &capInsets)
{
    _capInsetsMouseOver = Helper::restrictCapInsetRect(capInsets, this->_mouseOverTextureSize);
    
    //for performance issue
    if (!_scale9Enabled)
    {
        return;
    }
    _buttonMouseOverRenderer->setCapInsets(_capInsetsMouseOver);
}

const Rect& Button::getCapInsetsNormalRenderer()const
{
    return _capInsetsNormal;
}

const Rect& Button::getCapInsetsPressedRenderer()const
{
    return _capInsetsPressed;
}

const Rect& Button::getCapInsetsDisabledRenderer()const
{
    return _capInsetsDisabled;
}
    
const Rect& Button::getCapInsetsMouseOverRenderer()const
{
    return _capInsetsMouseOver;
}
    
bool Button::hitTest(const Vec2 &pt, const Camera* camera, Vec3 *p) const
{
    Rect rect;
    rect.origin.x = _leftOffsets * _contentSize.width;
    rect.origin.y = _topOffsets * _contentSize.height;
    rect.size.width = _contentSize.width - rect.origin.x - _rightOffsets * _contentSize.width;
    rect.size.height = _contentSize.height - rect.origin.y - _bottomOffsets * _contentSize.height;
    return isScreenPointInRect(pt, camera, getWorldToNodeTransform(), rect, p);
}
    
static Color3B multiplyColors(const Color3B& color1, const Color3B& color2)
{
    return Color3B(color1.r * color2.r/255.0,color1.g * color2.g/255.0,color1.b * color2.b/255.0);
}
    
static GLubyte multiplyOpacity(GLubyte opacity1, GLubyte opacity2)
{
    return opacity1 * opacity2/255.0;
}
    
class CC_DLL TextTintTo : public TintTo
{
public:
    
    static TextTintTo* create(float duration, GLubyte red, GLubyte green, GLubyte blue)
    {
        TextTintTo *tintTo = new (std::nothrow) TextTintTo();
        tintTo->initWithDuration(duration, red, green, blue);
        tintTo->autorelease();
        
        return tintTo;
    }
    
    void startWithTarget(Node *target) override
    {
        ActionInterval::startWithTarget(target);
        if (_target)
        {
            Label* label = dynamic_cast<Label*>(target);
            _from = label ? Color3B(label->getTextColor()): _target->getColor();
        }
    }
    
    static TextTintTo* create(float duration, const Color3B& color)
    {
        return create(duration, color.r, color.g, color.b);
    }
    
    bool initWithDuration(float duration, GLubyte red, GLubyte green, GLubyte blue)
    {
        if (ActionInterval::initWithDuration(duration))
        {
            _to = Color3B(red, green, blue);
            return true;
        }
        
        return false;
    }
    
    virtual TintTo* clone() const  override
    {
        // no copy constructor
        auto a = new (std::nothrow) TextTintTo();
        a->initWithDuration(_duration, _to.r, _to.g, _to.b);
        a->autorelease();
        return a;
    }
    
    virtual  TextTintTo* reverse() const  override
    {
        CCASSERT(false, "reverse() not supported in TintTo");
        return nullptr;
    }
    virtual void update(float time) override
    {
        Label *label = dynamic_cast<Label*>(_target);
        if (label)
        {
            label->setTextColor(Color4B(GLubyte(_from.r + (_to.r - _from.r) * time),
                                        (GLubyte)(_from.g + (_to.g - _from.g) * time),
                                        (GLubyte)(_from.b + (_to.b - _from.b) * time),
                                        255));
        }
    }
};

void Button::onPressStateChangedToNormal()
{
    _buttonNormalRenderer->setVisible(true);
    _buttonPressedRenderer->setVisible(false);
    _buttonDisabledRenderer->setVisible(false);
    _buttonMouseOverRenderer->setVisible(false);
    _buttonNormalRenderer->setState(Scale9Sprite::State::NORMAL);
    _state = State::NORMAL;
    
    Color3B realBackgroundColor(multiplyColors(_normalBackgroundColor, _displayedColor));
    GLubyte realBackgroundOpacity(multiplyOpacity(_normalBackgroundOpacity, _displayedOpacity));
    Color3B realTitleColor(multiplyColors(_normalTitleColor, _displayedColor));
    GLubyte realTitleOpacity(multiplyOpacity(_normalTitleOpacity, _displayedOpacity));
    
    _buttonNormalRenderer->stopAllActions();
    if (_pressedTextureLoaded)
    {
        _buttonPressedRenderer->stopAllActions();
        _buttonPressedRenderer->setScale(_pressedTextureScaleXInSize, _pressedTextureScaleYInSize);
    }
    
    if (_pressedActionEnabled)
    {
        
        FiniteTimeAction *backZoomAction = ScaleTo::create(ZOOM_ACTION_TIME_STEP, _normalTextureScaleXInSize, _normalTextureScaleYInSize);
        _buttonNormalRenderer->runAction(backZoomAction);
        
        _buttonNormalRenderer->setColor(realBackgroundColor);
        _buttonNormalRenderer->setOpacity(realBackgroundOpacity);
        
        if(_titleRenderer)
        {
            _titleRenderer->stopAllActions();
            FiniteTimeAction *titleZoomAction;
            if (_unifySize)
                titleZoomAction = ScaleTo::create(ZOOM_ACTION_TIME_STEP, 1.0f, 1.0f);
            else
                titleZoomAction = ScaleTo::create(ZOOM_ACTION_TIME_STEP, _titleScale, _titleScale);
            FiniteTimeAction *titleColorAction = TextTintTo::create(ZOOM_ACTION_TIME_STEP, realTitleColor.r, realTitleColor.g, realTitleColor.b);
            FiniteTimeAction *titleOpacityAction = FadeTo::create(ZOOM_ACTION_TIME_STEP, realTitleOpacity);
            Action *titleSpawn = Spawn::create(titleZoomAction, titleColorAction, titleOpacityAction, nullptr);
            _titleRenderer->runAction(titleSpawn);
        }
    }
    else
    {
        _buttonNormalRenderer->setColor(realBackgroundColor);
        _buttonNormalRenderer->setOpacity(realBackgroundOpacity);
        if(_titleRenderer)
        {
            if(FontType::BMFONT != _type)
                _titleRenderer->setTextColor(Color4B(realTitleColor));
            _titleRenderer->setOpacity(realTitleOpacity);
            if (_unifySize)
                _titleRenderer->setScale(1.0f, 1.0f);
            else
                _titleRenderer->setScale(_titleScale, _titleScale);
        }
    }
}

void Button::onPressStateChangedToPressed()
{
    _buttonNormalRenderer->setState(Scale9Sprite::State::NORMAL);

    _state = State::PRESSED;
    _buttonDisabledRenderer->setVisible(false);
    _buttonMouseOverRenderer->setVisible(false);
    
    Color3B realBackgroundColor(multiplyColors(_pressedBackgroundColor, _displayedColor));
    GLubyte realBackgroundOpacity(multiplyOpacity(_pressedBackgroundOpacity, _displayedOpacity));
    Color3B realTitleColor(multiplyColors(_pressedTitleColor, _displayedColor));
    GLubyte realTitleOpacity(multiplyOpacity(_pressedTitleOpacity, _displayedOpacity));
    
    Scale9Sprite* nextRender = nullptr;
    
    _buttonNormalRenderer->stopAllActions();
    _buttonPressedRenderer->stopAllActions();
    
    if (_pressedTextureLoaded)
    {
        _buttonNormalRenderer->setVisible(false);
        _buttonPressedRenderer->setVisible(true);
        nextRender = _buttonPressedRenderer;
    }
    else
    {
        _buttonNormalRenderer->setVisible(true);
        _buttonPressedRenderer->setVisible(false);
        nextRender = _buttonNormalRenderer;
    }
    
    nextRender->setColor(realBackgroundColor);
    nextRender->setOpacity(realBackgroundOpacity);
    
    if (_pressedActionEnabled)
    {
        FiniteTimeAction *backZoomAction = ScaleTo::create(ZOOM_ACTION_TIME_STEP, _pressedTextureScaleXInSize + _zoomScale, _pressedTextureScaleYInSize + _zoomScale);
        nextRender->runAction(backZoomAction);
        
        if(_titleRenderer)
        {
            _titleRenderer->stopAllActions();
            FiniteTimeAction *titleZoomAction;
            if (_unifySize)
                titleZoomAction = ScaleTo::create(ZOOM_ACTION_TIME_STEP, 1.0f + _zoomScale, 1.0f + _zoomScale);
            else
                titleZoomAction = ScaleTo::create(ZOOM_ACTION_TIME_STEP, _titleScale * (1.0f + _zoomScale), _titleScale + (1.0f * _zoomScale));
            FiniteTimeAction *titleColorAction = TextTintTo::create(ZOOM_ACTION_TIME_STEP, realTitleColor.r, realTitleColor.g, realTitleColor.b);
            FiniteTimeAction *titleOpacityAction = FadeTo::create(ZOOM_ACTION_TIME_STEP, realTitleOpacity);
            Action *titleSpawn =  nullptr;
            if(FontType::BMFONT != _type)
                titleSpawn = Spawn::create(titleZoomAction, titleColorAction, titleOpacityAction, nullptr);
            else
                titleSpawn = Spawn::create(titleZoomAction, titleOpacityAction, nullptr);
            _titleRenderer->runAction(titleSpawn);
        }
    }
    else
    {
        nextRender->setColor(realBackgroundColor);
        nextRender->setOpacity(realBackgroundOpacity);
        if(_titleRenderer)
        {
            if(FontType::BMFONT != _type)
                _titleRenderer->setTextColor(Color4B(realTitleColor));
            _titleRenderer->setOpacity(realTitleOpacity);
            if (_unifySize)
                _titleRenderer->setScale(1.0f, 1.0f);
            else
                _titleRenderer->setScale(_titleScale, _titleScale);
        }
    }
}

void Button::onPressStateChangedToDisabled()
{
    //if disable resource is null
    _state = State::DISABLED;
    Scale9Sprite* nextRender = nullptr;
    if (!_disabledTextureLoaded)
    {
        nextRender = _buttonNormalRenderer;
        _buttonNormalRenderer->setVisible(true);
        _buttonDisabledRenderer->setVisible(false);
    }
    else
    {
        nextRender = _buttonDisabledRenderer;
        _buttonNormalRenderer->setVisible(false);
        _buttonDisabledRenderer->setVisible(true);
    }

    _buttonPressedRenderer->setVisible(false);
    _buttonMouseOverRenderer->setVisible(false);
    _buttonNormalRenderer->setScale(_normalTextureScaleXInSize, _normalTextureScaleYInSize);
    _buttonPressedRenderer->setScale(_pressedTextureScaleXInSize, _pressedTextureScaleYInSize);
    nextRender->setColor(multiplyColors(_disabledBackgroundColor, _displayedColor));
    nextRender->setOpacity(multiplyOpacity(_disabledBackgroundOpacity, _displayedOpacity));
    if(_titleRenderer)
    {
        _titleRenderer->setTextColor(Color4B(multiplyColors(_disabledTitleColor, _displayedColor)));
        _titleRenderer->setOpacity(multiplyOpacity(_disabledTitleOpacity, _displayedOpacity));
        _titleRenderer->setScale(_titleScale);
    }
}
    
void Button::onPressStateChangedToMouseOver()
{
    //if highlighted resource is null
    Scale9Sprite* nextRender = nullptr;
    if (!_mouseOverTextureLoaded)
    {
        nextRender = _buttonNormalRenderer;
        _buttonNormalRenderer->setVisible(true);
        _buttonMouseOverRenderer->setVisible(false);
    }
    else
    {
        nextRender = _buttonMouseOverRenderer;
        _buttonNormalRenderer->setVisible(false);
        _buttonMouseOverRenderer->setVisible(true);
    }
    
    _buttonPressedRenderer->setVisible(false);
    _buttonNormalRenderer->setScale(_normalTextureScaleXInSize, _normalTextureScaleYInSize);
    _buttonPressedRenderer->setScale(_pressedTextureScaleXInSize, _pressedTextureScaleYInSize);
    nextRender->setColor(multiplyColors(_mouseOverBackgroundColor, _displayedColor));
    nextRender->setOpacity(multiplyOpacity(_mouseOverBackgroundOpacity, _displayedOpacity));
    if(_titleRenderer)
    {
        _titleRenderer->setTextColor(Color4B(multiplyColors(_mouseOverTitleColor, _displayedColor)));
        _titleRenderer->setOpacity(multiplyOpacity(_mouseOverTitleOpacity, _displayedOpacity));
        _titleRenderer->setScale(_titleScale);
    }
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
            _buttonNormalRenderer->setOpacity(multiplyOpacity(_normalBackgroundOpacity, _displayedOpacity));
            break;
        case State::PRESSED:
            if(!_pressedTextureLoaded)
                _buttonNormalRenderer->setOpacity(multiplyOpacity(_pressedBackgroundOpacity, _displayedOpacity));
            break;
        case State::DISABLED:
            if(!_disabledTextureLoaded)
                _buttonNormalRenderer->setOpacity(multiplyOpacity(_disabledBackgroundOpacity, _displayedOpacity));
            break;
        case State::MOUSEOVER:
            if(!_mouseOverTextureLoaded)
                _buttonNormalRenderer->setOpacity(multiplyOpacity(_mouseOverBackgroundOpacity, _displayedOpacity));
            break;
    }
    if(_titleRenderer)
        updateTextOpacity();
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
            _buttonNormalRenderer->setColor(multiplyColors(_normalBackgroundColor, _displayedColor));
            break;
        case State::PRESSED:
            if(!_pressedTextureLoaded)
                _buttonNormalRenderer->setColor(multiplyColors(_pressedBackgroundColor, _displayedColor));
            break;
        case State::DISABLED:
            if(!_disabledTextureLoaded)
                _buttonNormalRenderer->setColor(multiplyColors(_disabledBackgroundColor, _displayedColor));
            break;
        case State::MOUSEOVER:
            if(!_mouseOverTextureLoaded)
                _buttonNormalRenderer->setColor(multiplyColors(_mouseOverBackgroundColor, _displayedColor));
            break;
    }
    if(_titleRenderer)
        updateTextColor();
}

void Button::updateTitleLocation()
{
    if(_titleRenderer)
        _titleRenderer->setPosition(_contentSize.width * 0.5f + (_leftPadding - _rightPadding)/2.0f, _contentSize.height * 0.5f + (_bottomPadding - _topPadding)/2.0f);
}

void Button::updateContentSize()
{
    if (_unifySize)
    {
        if (_scale9Enabled)
        {
            ProtectedNode::setContentSize(_customSize);
        }
        else
        {
            Size s = getNormalSize();
            ProtectedNode::setContentSize(s);
        }
        onSizeChanged();
        return;
    }

    if (_ignoreSize)
    {
        this->setContentSize(getVirtualRendererSize());
    }
}

void Button::onSizeChanged()
{
    Widget::onSizeChanged();
    if(nullptr != _titleRenderer)
    {
        updateTitleLocation();
    }
    _normalTextureAdaptDirty = true;
    _pressedTextureAdaptDirty = true;
    _disabledTextureAdaptDirty = true;
    _mouseOverTextureAdaptDirty = true;
    _titileAdaptDirty = true;
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
    
    if (_mouseOverTextureAdaptDirty)
    {
        mouseOverTextureScaleChangedWithSize();
        _mouseOverTextureAdaptDirty = false;
    }
    
    if(_titileAdaptDirty)
    {
        if(_titleRenderer)
        {
            Size contentSize = getContentSize();
            Size paddedLabelSize = Size(contentSize.width - (_leftPadding + _rightPadding), contentSize.height -  (_topPadding + _bottomPadding));
            _titleRenderer->setScale(1.0f);
            
            _titleRenderer->setOverflow(static_cast<Label::Overflow>(_overflowLabel));
            _titleRenderer->setLineBreakWithoutSpace(!_wordWrapLabel);
           
            _titleRenderer->setDimensions(paddedLabelSize.width, paddedLabelSize.height);
            _titleRenderer->getContentSize();
            _titleRenderer->setScale(_normalTextureScaleXInSize);
            _titleScale = _normalTextureScaleXInSize;
            
            updateTitleLocation();
        }
        _titileAdaptDirty = false;
    }
}

Size Button::getVirtualRendererSize() const
{
    if (_unifySize)
    {
        return this->getNormalSize();
    }

    if (nullptr != _titleRenderer)
    {
        Size titleSize = _titleRenderer->getContentSize();
        if (!_normalTextureLoaded && _titleRenderer->getString().size() > 0)
        {
            return titleSize;
        }
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
                return _buttonPressedRenderer;
            case BrightStyle::MOUSEOVER:
                return _buttonMouseOverRenderer;
            default:
                return nullptr;
        }
    }
    else
    {
        return _buttonDisabledRenderer;
    }
}

void Button::normalTextureScaleChangedWithSize()
{
    _buttonNormalRenderer->setPreferredSize(_contentSize / _imageScale);

    _buttonNormalRenderer->setPosition(_contentSize.width / _imageScale / 2.0f, _contentSize.height / _imageScale / 2.0f);
}

void Button::pressedTextureScaleChangedWithSize()
{
    _buttonPressedRenderer->setPreferredSize(_contentSize / _imageScale);

    _buttonPressedRenderer->setPosition(_contentSize.width / _imageScale / 2.0f, _contentSize.height / _imageScale / 2.0f);
}

void Button::disabledTextureScaleChangedWithSize()
{
    _buttonDisabledRenderer->setPreferredSize(_contentSize / _imageScale);

    _buttonDisabledRenderer->setPosition(_contentSize.width / _imageScale / 2.0f, _contentSize.height / _imageScale / 2.0f);
}
    
void Button::mouseOverTextureScaleChangedWithSize()
{
    _buttonMouseOverRenderer->setPreferredSize(_contentSize / _imageScale);
    
    _buttonMouseOverRenderer->setPosition(_contentSize.width / _imageScale / 2.0f, _contentSize.height / _imageScale / 2.0f);
}

void Button::setPressedActionEnabled(bool enabled)
{
    _pressedActionEnabled = enabled;
}

void Button::setTitleAlignment(TextHAlignment hAlignment)
{
    if (_titleRenderer)
        _titleRenderer->setAlignment(hAlignment);
    _hAlignment = hAlignment;
}

void Button::setTitleAlignment(TextHAlignment hAlignment, TextVAlignment vAlignment)
{
    if (_titleRenderer)
        _titleRenderer->setAlignment(hAlignment, vAlignment);
    _hAlignment = hAlignment;
    _vAlignment = vAlignment;
}

void Button::setTitleText(const std::string& text)
{
    if (text == getTitleText())
    {
        return;
    }
    if(nullptr == _titleRenderer)
    {
        this->createTitleRenderer();
    }
    _titleRenderer->setString(text);
    updateContentSize();
    updateTitleLocation();
    _titileAdaptDirty = true;
}

std::string Button::getTitleText() const
{
    if(_titleRenderer)
    {
        return _titleRenderer->getString();
    }
    return "";
}

void Button::setTitleColor(const Color3B& color)
{
    if(_titleRenderer && FontType::BMFONT != _type)
    {
        _titleRenderer->setTextColor(Color4B(color));
    }
    _normalTitleColor = color;
    _pressedTitleColor = color;
    _disabledTitleColor = color;
}

Color3B Button::getTitleColor() const
{
    if(_titleRenderer)
    {
        return Color3B(_titleRenderer->getTextColor());
    }
    return Color3B::WHITE;
}

void Button::setTitleFontSize(float size)
{
    if (_titleRenderer)
    {
        updateFontSize();
        updateContentSize();
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
   
void Button::updateFontSize()
{
    if (_type == FontType::SYSTEM)
    {
        _titleRenderer->setSystemFontSize(_fontSize);
    }
    else if (_type == FontType::TTF)
    {
        TTFConfig config = _titleRenderer->getTTFConfig();
        config.fontSize = _fontSize;
        _titleRenderer->setTTFConfig(config);
    }
    //we can't change font size of BMFont.
    if(FontType::BMFONT != _type)
    {
        _titileAdaptDirty = true;
    }
}
    
void Button::updateFontName()
{
    if(FileUtils::getInstance()->isFileExist(_fontName))
    {
        std::string lowerCasedFontName = _fontName;
        std::transform(lowerCasedFontName.begin(), lowerCasedFontName.end(), lowerCasedFontName.begin(), ::tolower);
        if (lowerCasedFontName.find(".fnt") != std::string::npos)
        {
            _titleRenderer->setBMFontFilePath(_fontName);
            _type = FontType::BMFONT;
        }
        else
        {
            TTFConfig config = _titleRenderer->getTTFConfig();
            config.fontFilePath = _fontName;
            config.fontSize = _fontSize;
            _titleRenderer->setTTFConfig(config);
            _type = FontType::TTF;
        }
    }
    else
    {
        _titleRenderer->setSystemFontName(_fontName);
        if (_type == FontType::TTF)
        {
            _titleRenderer->requestSystemFontRefresh();
        }
        _titleRenderer->setSystemFontSize(_fontSize);
        _type = FontType::SYSTEM;
    }
}
    
void Button::updateTextColor()
{
    if(FontType::BMFONT != _type)
    {
        switch (_state) {
            case State::NORMAL:
                _titleRenderer->setTextColor(Color4B(multiplyColors(_normalTitleColor, _displayedColor)));
                break;
            case State::PRESSED:
                _titleRenderer->setTextColor(Color4B(multiplyColors(_pressedTitleColor, _displayedColor)));
                break;
            case State::DISABLED:
                _titleRenderer->setTextColor(Color4B(multiplyColors(_disabledTitleColor, _displayedColor)));
                break;
            case State::MOUSEOVER:
                _titleRenderer->setTextColor(Color4B(multiplyColors(_mouseOverTitleColor, _displayedColor)));
                break;
        }
    }
}
    
void Button::updateTextOpacity()
{
    switch (_state) {
        case State::NORMAL:
            _titleRenderer->setOpacity(multiplyOpacity(_normalTitleOpacity, _displayedOpacity));
            break;
        case State::PRESSED:
            _titleRenderer->setOpacity(multiplyOpacity(_pressedTitleOpacity, _displayedOpacity));
            break;
        case State::DISABLED:
            _titleRenderer->setOpacity(multiplyOpacity(_disabledTitleOpacity, _displayedOpacity));
            break;
        case State::MOUSEOVER:
            _titleRenderer->setOpacity(multiplyOpacity(_mouseOverTitleOpacity, _displayedOpacity));
            break;
    }
}

void Button::setTitleFontName(const std::string& fontName)
{
    if(_titleRenderer && _fontName != fontName)
    {
        updateFontName();
        updateContentSize();
    }
    _fontName = fontName;
    _titileAdaptDirty = true;
}

Label* Button::getTitleRenderer()const
{
    return _titleRenderer;
}

std::string Button::getTitleFontName() const
{
    if (nullptr != _titleRenderer)
    {
        if (this->_type == FontType::SYSTEM)
        {
            return _titleRenderer->getSystemFontName();
        }
        else if (this->_type == FontType::TTF)
        {
            return  _titleRenderer->getTTFConfig().fontFilePath;
        }
        else
        {
            return _titleRenderer->getBMFontFilePath();
        }
    }
    else
    {
        return _fontName;
    }
}

void Button::setOverflow(int value)
{
    _overflowLabel = value;
}
    
int Button::getOverflow() const
{
    return _overflowLabel;
}
    
void Button::setLabelWordWrap(bool value)
{
    _wordWrapLabel = value;
}

bool Button::getLabelWordWrap() const
{
    return _wordWrapLabel;
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
            _buttonPressedRenderer->setColor(multiplyColors(color, _displayedColor));
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
        if(_disabledTextureLoaded)
            _buttonDisabledRenderer->setColor(multiplyColors(color, _displayedColor));
        else
            _buttonNormalRenderer->setColor(multiplyColors(color, _displayedColor));
    }
}

const Color3B& Button::getDisabledBackgroundColor() const
{
    return _disabledBackgroundColor;
}

void Button::setMouseOverBackgroundColor(const Color3B &color)
{
    _mouseOverBackgroundColor = color;
    if(_state == State::MOUSEOVER)
    {
        if(_pressedTextureLoaded)
            _buttonMouseOverRenderer->setColor(multiplyColors(color, _displayedColor));
        else
            _buttonNormalRenderer->setColor(multiplyColors(color, _displayedColor));
    }
}

const Color3B& Button::getMouseOverBackgroundColor() const
{
    return _mouseOverBackgroundColor;
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
            _buttonPressedRenderer->setOpacity(multiplyOpacity(opacity, _displayedOpacity));
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
        if(_disabledTextureLoaded)
            _buttonDisabledRenderer->setOpacity(multiplyOpacity(opacity, _displayedOpacity));
        else
            _buttonNormalRenderer->setOpacity(multiplyOpacity(opacity, _displayedOpacity));
    }
}

GLubyte Button::getDisabledBackgroundOpacity() const
{
    return _disabledBackgroundOpacity;
}
    
void Button::setMouseOverBackgroundOpacity(GLubyte opacity)
{
    _mouseOverBackgroundOpacity = opacity;
    if(_state == State::MOUSEOVER)
    {
        if(_mouseOverTextureLoaded)
            _buttonMouseOverRenderer->setOpacity(multiplyOpacity(opacity, _displayedOpacity));
        else
            _buttonNormalRenderer->setOpacity(multiplyOpacity(opacity, _displayedOpacity));
    }
}

GLubyte Button::getMouseOverBackgroundOpacity() const
{
    return _mouseOverBackgroundOpacity;
}


void Button::setNormalTitleColor(const Color3B &color)
{
    _normalTitleColor = color;
    if(_state == State::NORMAL && FontType::BMFONT != _type)
        if(_titleRenderer)
            _titleRenderer->setTextColor(Color4B(multiplyColors(color, _displayedColor)));
}

const Color3B& Button::getNormalTitleColor() const
{
    return _normalTitleColor;
}

void Button::setPressedTitleColor(const Color3B &color)
{
    _pressedTitleColor = color;
    if(_state == State::PRESSED && FontType::BMFONT != _type)
        if(_titleRenderer)
            _titleRenderer->setTextColor(Color4B(multiplyColors(color, _displayedColor)));
}

const Color3B& Button::getPressedTitleColor() const
{
    return _pressedTitleColor;
}

void Button::setDisabledTitleColor(const Color3B &color)
{
    _disabledTitleColor = color;
    if(_state == State::DISABLED && FontType::BMFONT != _type)
        if(_titleRenderer)
            _titleRenderer->setTextColor(Color4B(multiplyColors(color, _displayedColor)));
}

const Color3B& Button::getDisabledTitleColor() const
{
    return _disabledTitleColor;
}
    
void Button::setMouseOverTitleColor(const Color3B &color)
{
    _mouseOverTitleColor = color;
    if(_state == State::MOUSEOVER && FontType::BMFONT != _type)
        if(_titleRenderer)
            _titleRenderer->setTextColor(Color4B(multiplyColors(color, _displayedColor)));
}

const Color3B& Button::getMouseOverTitleColor() const
{
    return _mouseOverTitleColor;
}

void Button::setNormalTitleOpacity(GLubyte opacity)
{
    _normalTitleOpacity = opacity;
    if(_state == State::NORMAL)
        if(_titleRenderer)
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
        if(_titleRenderer)
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
        if(_titleRenderer)
            _titleRenderer->setOpacity(multiplyOpacity(opacity, _displayedOpacity));
}

GLubyte Button::getDisabledTitleOpacity() const
{
    return _disabledTitleOpacity;
}
    
void Button::setMouseOverTitleOpacity(GLubyte opacity)
{
    _mouseOverTitleOpacity = opacity;
    if(_state == State::MOUSEOVER)
        if(_titleRenderer)
            _titleRenderer->setOpacity(multiplyOpacity(opacity, _displayedOpacity));
}

GLubyte Button::getMouseOverTitleOpacity() const
{
    return _mouseOverTitleOpacity;
}
    
void Button::setPaddingPadding(float left, float top, float right, float bottom)
{
    _leftPadding = left;
    _rightPadding = right;
    _topPadding = top;
    _bottomPadding = bottom;
    onSizeChanged();
}
    
void Button::setLeftPadding(float padding)
{
    _leftPadding = padding;
    onSizeChanged();
}

float Button::getLeftPadding()
{
    return _leftPadding;
}

void Button::setRightPadding(float padding)
{
    _rightPadding = padding;
    onSizeChanged();
}

float Button::getRightPadding()
{
    return _rightPadding;
}

void Button::setTopPadding(float padding)
{
    _topPadding = padding;
    onSizeChanged();
}

float Button::getTopPadding()
{
    return _topPadding;
}

void Button::setBottomPadding(float padding)
{
    _bottomPadding = padding;
    onSizeChanged();
}

float Button::getBottomPadding()
{
    return _bottomPadding;
}
    
void Button::setOffsets(float left, float top, float right, float bottom)
{
    _leftOffsets = left;
    _topOffsets = top;
    _rightOffsets = right;
    _bottomOffsets = bottom;
}

void Button::setLeftOffset(float left)
{
    _leftOffsets = left;
}

float Button::getLeftOffset() const
{
    return _leftOffsets;
}

void Button::setTopOffset(float top)
{
    _topOffsets = top;
}

float Button::getTopOffset() const
{
    return _topOffsets;
}

void Button::setRightOffset(float right)
{
    _rightOffsets = right;
}

float Button::getRightOffset() const
{
    return _rightOffsets;
}

void Button::setBottomOffset(float bottom)
{
    _bottomOffsets = bottom;
}

float Button::getBottomOffset() const
{
    return _bottomOffsets;
}
    
void Button::setImageScale(float scale)
{
    if(_imageScale != scale)
    {
        _imageScale = scale;
        _buttonRenderer->setScale(scale);
        _normalTextureAdaptDirty = true;
        _pressedTextureAdaptDirty = true;
        _disabledTextureAdaptDirty = true;
    }
}

float Button::getImageScale() const
{
    return _imageScale;
}

void Button::copySpecialProperties(Widget *widget)
{
    Button* button = dynamic_cast<Button*>(widget);
    if (button)
    {
        _prevIgnoreSize = button->_prevIgnoreSize;
        setScale9Enabled(button->_scale9Enabled);
        auto normalSprite = button->_buttonNormalRenderer->getSprite();
        if (nullptr != normalSprite)
        {
            loadTextureNormal(normalSprite->getSpriteFrame());
        }
        auto clickedSprite = button->_buttonPressedRenderer->getSprite();
        if (nullptr != clickedSprite)
        {
            loadTexturePressed(clickedSprite->getSpriteFrame());
        }
        auto disabledSprite = button->_buttonDisabledRenderer->getSprite();
        if (nullptr != disabledSprite)
        {
            loadTextureDisabled(disabledSprite->getSpriteFrame());
        }
        auto mouseOverSprite = button->_buttonMouseOverRenderer->getSprite();
        if (nullptr != mouseOverSprite)
        {
            loadTextureMouseOver(mouseOverSprite->getSpriteFrame());
        }
        setCapInsetsNormalRenderer(button->_capInsetsNormal);
        setCapInsetsPressedRenderer(button->_capInsetsPressed);
        setCapInsetsDisabledRenderer(button->_capInsetsDisabled);
        setCapInsetsMouseOverRenderer(button->_capInsetsMouseOver);
        if(nullptr != button->getTitleRenderer())
        {
            setTitleText(button->getTitleText());
            setTitleFontName(button->getTitleFontName());
            setTitleFontSize(button->getTitleFontSize());
            setTitleColor(button->getTitleColor());
        }
        setPressedActionEnabled(button->_pressedActionEnabled);
        setZoomScale(button->_zoomScale);
        setNormalBackgroundColor(button->_normalBackgroundColor);
        setPressedBackgroundColor(button->_pressedBackgroundColor);
        setDisabledBackgroundColor(button->_disabledBackgroundColor);
        setMouseOverBackgroundColor(button->_mouseOverBackgroundColor);
        setNormalBackgroundOpacity(button->_normalBackgroundOpacity);
        setPressedBackgroundOpacity(button->_pressedBackgroundOpacity);
        setDisabledBackgroundOpacity(button->_disabledBackgroundOpacity);
        setMouseOverBackgroundOpacity(button->_mouseOverBackgroundOpacity);
        setNormalTitleColor(button->_normalTitleColor);
        setPressedTitleColor(button->_pressedTitleColor);
        setDisabledTitleColor(button->_disabledTitleColor);
        setMouseOverTitleColor(button->_mouseOverTitleColor);
        setNormalTitleOpacity(button->_normalTitleOpacity);
        setPressedTitleOpacity(button->_pressedTitleOpacity);
        setDisabledTitleOpacity(button->_disabledTitleOpacity);
        setMouseOverTitleOpacity(button->_mouseOverTitleOpacity);
    }
}

Size Button::getNormalSize() const
{
    Size titleSize;
    if (_titleRenderer != nullptr)
    {
        titleSize = _titleRenderer->getContentSize();
    }
    Size imageSize;
    if (_buttonNormalRenderer != nullptr)
    {
        imageSize = _buttonNormalRenderer->getContentSize();
    }
    float width = titleSize.width > imageSize.width ? titleSize.width : imageSize.width;
    float height = titleSize.height > imageSize.height ? titleSize.height : imageSize.height;

    return Size(width,height);
}
    
Size Button::getNormalTextureSize() const
{
    return _normalTextureSize;
}

void Button::resetNormalRender()
{
    _normalFileName = "";
    _normalTexType = TextureResType::LOCAL;

    _normalTextureSize = Size(0, 0);

    _normalTextureLoaded = false;
    _normalTextureAdaptDirty = false;

    _buttonNormalRenderer->resetRender();
}
void Button::resetPressedRender()
{
    _clickedFileName = "";
    _pressedTexType = TextureResType::LOCAL;

    _pressedTextureSize = Size(0, 0);

    _pressedTextureLoaded = false;
    _pressedTextureAdaptDirty = false;

    _buttonPressedRenderer->resetRender();
}

void Button::resetDisabledRender()
{
    _disabledFileName = "";
    _disabledTexType = TextureResType::LOCAL;

    _disabledTextureSize = Size(0, 0);

    _disabledTextureLoaded = false;
    _disabledTextureAdaptDirty = false;

    _buttonDisabledRenderer->resetRender();
}
    
void Button::resetMouseOverRender()
{
    _mouseOverFileName = "";
    _mouseOverTexType = TextureResType::LOCAL;
    
    _mouseOverTextureSize = Size(0, 0);
    
    _mouseOverTextureLoaded = false;
    _mouseOverTextureAdaptDirty = false;
    
    _buttonMouseOverRenderer->resetRender();
}

ResourceData Button::getNormalFile()
{
    ResourceData rData;
    rData.type = (int)_normalTexType;
    rData.file = _normalFileName;
    return rData;
}
ResourceData Button::getPressedFile()
{
    ResourceData rData;
    rData.type = (int)_pressedTexType;
    rData.file = _clickedFileName;
    return rData;
}
ResourceData Button::getDisabledFile()
{
    ResourceData rData;
    rData.type = (int)_disabledTexType;
    rData.file = _disabledFileName;
    return rData;
}
ResourceData Button::getMouseOverFile()
{
    ResourceData rData;
    rData.type = (int)_mouseOverTexType;
    rData.file = _mouseOverFileName;
    return rData;
}

}

NS_CC_END
