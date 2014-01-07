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

#include "gui/UISlider.h"
#include "extensions/GUI/CCControlExtension/CCScale9Sprite.h"

NS_CC_BEGIN

namespace gui {
    
static const int BASEBAR_RENDERER_Z = (-2);
static const int PROGRESSBAR_RENDERER_Z = (-2);
static const int SLIDBALL_RENDERER_Z = (-1);
    
Slider::Slider():
_barRenderer(nullptr),
_progressBarRenderer(nullptr),
_progressBarTextureSize(Size::ZERO),
_slidBallNormalRenderer(nullptr),
_slidBallPressedRenderer(nullptr),
_slidBallDisabledRenderer(nullptr),
_slidBallRenderer(nullptr),
_barLength(0.0),
_percent(0),
_scale9Enabled(false),
_prevIgnoreSize(true),
_textureFile(""),
_progressBarTextureFile(""),
_slidBallNormalTextureFile(""),
_slidBallPressedTextureFile(""),
_slidBallDisabledTextureFile(""),
_capInsetsBarRenderer(Rect::ZERO),
_capInsetsProgressBarRenderer(Rect::ZERO),
_sliderEventListener(nullptr),
_sliderEventSelector(nullptr),
_barTexType(UI_TEX_TYPE_LOCAL),
_progressBarTexType(UI_TEX_TYPE_LOCAL),
_ballNTexType(UI_TEX_TYPE_LOCAL),
_ballPTexType(UI_TEX_TYPE_LOCAL),
_ballDTexType(UI_TEX_TYPE_LOCAL)
{
}

Slider::~Slider()
{
    _sliderEventListener = nullptr;
    _sliderEventSelector = nullptr;
}

Slider* Slider::create()
{
    Slider* widget = new Slider();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

void Slider::initRenderer()
{
    _barRenderer = Sprite::create();
    _progressBarRenderer = Sprite::create();
    _progressBarRenderer->setAnchorPoint(Point(0.0f, 0.5f));
    Node::addChild(_barRenderer, BASEBAR_RENDERER_Z, -1);
    Node::addChild(_progressBarRenderer, PROGRESSBAR_RENDERER_Z, -1);
    _slidBallNormalRenderer = Sprite::create();
    _slidBallPressedRenderer = Sprite::create();
    _slidBallPressedRenderer->setVisible(false);
    _slidBallDisabledRenderer = Sprite::create();
    _slidBallDisabledRenderer->setVisible(false);
    _slidBallRenderer = Node::create();
    _slidBallRenderer->addChild(_slidBallNormalRenderer);
    _slidBallRenderer->addChild(_slidBallPressedRenderer);
    _slidBallRenderer->addChild(_slidBallDisabledRenderer);
    Node::addChild(_slidBallRenderer, SLIDBALL_RENDERER_Z, -1);
}

void Slider::loadBarTexture(const char* fileName, TextureResType texType)
{
    if (!fileName || strcmp(fileName, "") == 0)
    {
        return;
    }
    _textureFile = fileName;
    _barTexType = texType;
    switch (_barTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            if (_scale9Enabled)
            {
                static_cast<extension::Scale9Sprite*>(_barRenderer)->initWithFile(fileName);
            }
            else
            {
                static_cast<Sprite*>(_barRenderer)->setTexture(fileName);
            }
            break;
        case UI_TEX_TYPE_PLIST:
            if (_scale9Enabled)
            {
                static_cast<extension::Scale9Sprite*>(_barRenderer)->initWithSpriteFrameName(fileName);
            }
            else
            {
                static_cast<Sprite*>(_barRenderer)->setSpriteFrame(fileName);
            }
            break;
        default:
            break;
    }
    updateDisplayedColor(getColor());
    updateDisplayedOpacity(getOpacity());
    barRendererScaleChangedWithSize();
}

void Slider::loadProgressBarTexture(const char *fileName, TextureResType texType)
{
    if (!fileName || strcmp(fileName, "") == 0)
    {
        return;
    }
    _progressBarTextureFile = fileName;
    _progressBarTexType = texType;
    switch (_progressBarTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            if (_scale9Enabled)
            {
                static_cast<extension::Scale9Sprite*>(_progressBarRenderer)->initWithFile(fileName);
            }
            else
            {
                static_cast<Sprite*>(_progressBarRenderer)->setTexture(fileName);
            }
            break;
        case UI_TEX_TYPE_PLIST:
            if (_scale9Enabled)
            {
                static_cast<extension::Scale9Sprite*>(_progressBarRenderer)->initWithSpriteFrameName(fileName);
            }
            else
            {
                static_cast<Sprite*>(_progressBarRenderer)->setSpriteFrame(fileName);
            }
            break;
        default:
            break;
    }
    updateDisplayedColor(getColor());
    updateDisplayedOpacity(getOpacity());
    _progressBarRenderer->setAnchorPoint(Point(0.0f, 0.5f));
    _progressBarTextureSize = _progressBarRenderer->getContentSize();
    progressBarRendererScaleChangedWithSize();
}

void Slider::setScale9Enabled(bool able)
{
    if (_scale9Enabled == able)
    {
        return;
    }
    
    _scale9Enabled = able;
    Node::removeChild(_barRenderer);
    Node::removeChild(_progressBarRenderer);
    _barRenderer = nullptr;
    _progressBarRenderer = nullptr;
    if (_scale9Enabled)
    {
        _barRenderer = extension::Scale9Sprite::create();
        _progressBarRenderer = extension::Scale9Sprite::create();
    }
    else
    {
        _barRenderer = Sprite::create();
        _progressBarRenderer = Sprite::create();
    }
    loadBarTexture(_textureFile.c_str(), _barTexType);
    loadProgressBarTexture(_progressBarTextureFile.c_str(), _progressBarTexType);
    Node::addChild(_barRenderer, BASEBAR_RENDERER_Z, -1);
    Node::addChild(_progressBarRenderer, PROGRESSBAR_RENDERER_Z, -1);
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
    setCapInsetsBarRenderer(_capInsetsBarRenderer);
    setCapInsetProgressBarRebderer(_capInsetsProgressBarRenderer);
}

void Slider::ignoreContentAdaptWithSize(bool ignore)
{
    if (!_scale9Enabled || (_scale9Enabled && !ignore))
    {
        Widget::ignoreContentAdaptWithSize(ignore);
        _prevIgnoreSize = ignore;
    }
}

void Slider::setCapInsets(const Rect &capInsets)
{
    setCapInsetsBarRenderer(capInsets);
    setCapInsetProgressBarRebderer(capInsets);
}

void Slider::setCapInsetsBarRenderer(const Rect &capInsets)
{
    _capInsetsBarRenderer = capInsets;
    if (!_scale9Enabled)
    {
        return;
    }
    static_cast<extension::Scale9Sprite*>(_barRenderer)->setCapInsets(capInsets);
}

void Slider::setCapInsetProgressBarRebderer(const Rect &capInsets)
{
    _capInsetsProgressBarRenderer = capInsets;
    if (!_scale9Enabled)
    {
        return;
    }
    static_cast<extension::Scale9Sprite*>(_progressBarRenderer)->setCapInsets(capInsets);
}

void Slider::loadSlidBallTextures(const char* normal,const char* pressed,const char* disabled,TextureResType texType)
{
    loadSlidBallTextureNormal(normal, texType);
    loadSlidBallTexturePressed(pressed,texType);
    loadSlidBallTextureDisabled(disabled,texType);
}

void Slider::loadSlidBallTextureNormal(const char* normal,TextureResType texType)
{
    if (!normal || strcmp(normal, "") == 0)
    {
        return;
    }
    _slidBallNormalTextureFile = normal;
    _ballNTexType = texType;
    switch (_ballNTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            _slidBallNormalRenderer->setTexture(normal);
            break;
        case UI_TEX_TYPE_PLIST:
            _slidBallNormalRenderer->setSpriteFrame(normal);
            break;
        default:
            break;
    }
    updateDisplayedColor(getColor());
    updateDisplayedOpacity(getOpacity());
}

void Slider::loadSlidBallTexturePressed(const char* pressed,TextureResType texType)
{
    if (!pressed || strcmp(pressed, "") == 0)
    {
        return;
    }
    _slidBallPressedTextureFile = pressed;
    _ballPTexType = texType;
    switch (_ballPTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            _slidBallPressedRenderer->setTexture(pressed);
            break;
        case UI_TEX_TYPE_PLIST:
            _slidBallPressedRenderer->setSpriteFrame(pressed);
            break;
        default:
            break;
    }
    updateDisplayedColor(getColor());
    updateDisplayedOpacity(getOpacity());
}

void Slider::loadSlidBallTextureDisabled(const char* disabled,TextureResType texType)
{
    if (!disabled || strcmp(disabled, "") == 0)
    {
        return;
    }
    _slidBallDisabledTextureFile = disabled;
    _ballDTexType = texType;
    switch (_ballDTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            _slidBallDisabledRenderer->setTexture(disabled);
            break;
        case UI_TEX_TYPE_PLIST:
            _slidBallDisabledRenderer->setSpriteFrame(disabled);
            break;
        default:
            break;
    }
    updateDisplayedColor(getColor());
    updateDisplayedOpacity(getOpacity());
}

void Slider::setPercent(int percent)
{
    if (percent > 100)
    {
        percent = 100;
    }
    if (percent < 0)
    {
        percent = 0;
    }
    _percent = percent;
    float res = percent / 100.0f;
    float dis = _barLength * res;
    _slidBallRenderer->setPosition(Point(-_barLength/2.0f + dis, 0.0f));
    if (_scale9Enabled)
    {
        static_cast<extension::Scale9Sprite*>(_progressBarRenderer)->setPreferredSize(Size(dis,_progressBarTextureSize.height));
    }
    else
    {
        Sprite* spriteRenderer = static_cast<Sprite*>(_progressBarRenderer);
        Rect rect = spriteRenderer->getTextureRect();
        rect.size.width = _progressBarTextureSize.width * res;
        spriteRenderer->setTextureRect(rect, spriteRenderer->isTextureRectRotated(), rect.size);
    }
}

bool Slider::onTouchBegan(Touch *touch, Event *unusedEvent)
{
    bool pass = Widget::onTouchBegan(touch, unusedEvent);
    if (_hitted)
    {
        Point nsp = convertToNodeSpace(_touchStartPos);
        setPercent(getPercentWithBallPos(nsp.x));
        percentChangedEvent();
    }
    return pass;
}

void Slider::onTouchMoved(Touch *touch, Event *unusedEvent)
{
    _touchMovePos = touch->getLocation();
    Point nsp = convertToNodeSpace(_touchMovePos);
    _slidBallRenderer->setPosition(Point(nsp.x,0));
    setPercent(getPercentWithBallPos(nsp.x));
    percentChangedEvent();
}

void Slider::onTouchEnded(Touch *touch, Event *unusedEvent)
{
    Widget::onTouchEnded(touch, unusedEvent);
}

void Slider::onTouchCancelled(Touch *touch, Event *unusedEvent)
{
    Widget::onTouchCancelled(touch, unusedEvent);
}

float Slider::getPercentWithBallPos(float px)
{
    return (((px-(-_barLength/2.0f))/_barLength)*100.0f);
}

void Slider::addEventListenerSlider(Object *target, SEL_SlidPercentChangedEvent selector)
{
    _sliderEventListener = target;
    _sliderEventSelector = selector;
}

void Slider::percentChangedEvent()
{
    if (_sliderEventListener && _sliderEventSelector)
    {
        (_sliderEventListener->*_sliderEventSelector)(this,SLIDER_PERCENTCHANGED);
    }
}

int Slider::getPercent()
{
    return _percent;
}

void Slider::onSizeChanged()
{
    Widget::onSizeChanged();
    barRendererScaleChangedWithSize();
    progressBarRendererScaleChangedWithSize();
}

const Size& Slider::getContentSize() const
{
    return _barRenderer->getContentSize();
}

Node* Slider::getVirtualRenderer()
{
    return _barRenderer;
}

void Slider::barRendererScaleChangedWithSize()
{
    if (_ignoreSize)
    {
        
        _barRenderer->setScale(1.0f);
        _size = _barRenderer->getContentSize();
        _barLength = _size.width;
    }
    else
    {
        _barLength = _size.width;
        if (_scale9Enabled)
        {
            static_cast<extension::Scale9Sprite*>(_barRenderer)->setPreferredSize(_size);
        }
        else
        {
            Size btextureSize = _barRenderer->getContentSize();
            if (btextureSize.width <= 0.0f || btextureSize.height <= 0.0f)
            {
                _barRenderer->setScale(1.0f);
                return;
            }
            float bscaleX = _size.width / btextureSize.width;
            float bscaleY = _size.height / btextureSize.height;
            _barRenderer->setScaleX(bscaleX);
            _barRenderer->setScaleY(bscaleY);
        }
    }
    setPercent(_percent);
}

void Slider::progressBarRendererScaleChangedWithSize()
{
    if (_ignoreSize)
    {
        if (!_scale9Enabled)
        {
            Size ptextureSize = _progressBarTextureSize;
            float pscaleX = _size.width / ptextureSize.width;
            float pscaleY = _size.height / ptextureSize.height;
            _progressBarRenderer->setScaleX(pscaleX);
            _progressBarRenderer->setScaleY(pscaleY);
        }
    }
    else
    {
        if (_scale9Enabled)
        {
            static_cast<extension::Scale9Sprite*>(_progressBarRenderer)->setPreferredSize(_size);
        }
        else
        {
            Size ptextureSize = _progressBarTextureSize;
            if (ptextureSize.width <= 0.0f || ptextureSize.height <= 0.0f)
            {
                _progressBarRenderer->setScale(1.0f);
                return;
            }
            float pscaleX = _size.width / ptextureSize.width;
            float pscaleY = _size.height / ptextureSize.height;
            _progressBarRenderer->setScaleX(pscaleX);
            _progressBarRenderer->setScaleY(pscaleY);
        }
    }
    _progressBarRenderer->setPosition(Point(-_barLength * 0.5f, 0.0f));
    setPercent(_percent);
}

void Slider::onPressStateChangedToNormal()
{
    _slidBallNormalRenderer->setVisible(true);
    _slidBallPressedRenderer->setVisible(false);
    _slidBallDisabledRenderer->setVisible(false);
}

void Slider::onPressStateChangedToPressed()
{
    _slidBallNormalRenderer->setVisible(false);
    _slidBallPressedRenderer->setVisible(true);
    _slidBallDisabledRenderer->setVisible(false);
}

void Slider::onPressStateChangedToDisabled()
{
    _slidBallNormalRenderer->setVisible(false);
    _slidBallPressedRenderer->setVisible(false);
    _slidBallDisabledRenderer->setVisible(true);
}

std::string Slider::getDescription() const
{
    return "Slider";
}

Widget* Slider::createCloneInstance()
{
    return Slider::create();
}

void Slider::copySpecialProperties(Widget *widget)
{
    Slider* slider = dynamic_cast<Slider*>(widget);
    if (slider)
    {
        _prevIgnoreSize = slider->_prevIgnoreSize;
        setScale9Enabled(slider->_scale9Enabled);
        loadBarTexture(slider->_textureFile.c_str(), slider->_barTexType);
        loadProgressBarTexture(slider->_progressBarTextureFile.c_str(), slider->_progressBarTexType);
        loadSlidBallTextureNormal(slider->_slidBallNormalTextureFile.c_str(), slider->_ballNTexType);
        loadSlidBallTexturePressed(slider->_slidBallPressedTextureFile.c_str(), slider->_ballPTexType);
        loadSlidBallTextureDisabled(slider->_slidBallDisabledTextureFile.c_str(), slider->_ballDTexType);
        setPercent(slider->getPercent());
    }
}

}

NS_CC_END