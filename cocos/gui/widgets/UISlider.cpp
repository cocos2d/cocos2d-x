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

#include "UISlider.h"
#include "../../../GUI/CCControlExtension/CCScale9Sprite.h"

NS_CC_EXT_BEGIN

UISlider::UISlider():
_barRenderer(NULL),
_progressBarRenderer(NULL),
_progressBarTextureSize(Size::ZERO),
_slidBallNormalRenderer(NULL),
_slidBallPressedRenderer(NULL),
_slidBallDisabledRenderer(NULL),
_slidBallRenderer(NULL),
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
_slidPercentListener(NULL),
_slidPercentSelector(NULL),
_barTexType(UI_TEX_TYPE_LOCAL),
_progressBarTexType(UI_TEX_TYPE_LOCAL),
_ballNTexType(UI_TEX_TYPE_LOCAL),
_ballPTexType(UI_TEX_TYPE_LOCAL),
_ballDTexType(UI_TEX_TYPE_LOCAL)
{
}

UISlider::~UISlider()
{
    
}

UISlider* UISlider::create()
{
    UISlider* widget = new UISlider();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

void UISlider::initRenderer()
{
    UIWidget::initRenderer();
    _barRenderer = CCSprite::create();
    _progressBarRenderer = CCSprite::create();
    _progressBarRenderer->setAnchorPoint(Point(0.0f, 0.5f));
    _renderer->addChild(_barRenderer, -1);
    _renderer->addChild(_progressBarRenderer, -1);
    _slidBallNormalRenderer = CCSprite::create();
    _slidBallPressedRenderer = CCSprite::create();
    _slidBallPressedRenderer->setVisible(false);
    _slidBallDisabledRenderer = CCSprite::create();
    _slidBallDisabledRenderer->setVisible(false);
    _slidBallRenderer = CCNode::create();
    _slidBallRenderer->addChild(_slidBallNormalRenderer);
    _slidBallRenderer->addChild(_slidBallPressedRenderer);
    _slidBallRenderer->addChild(_slidBallDisabledRenderer);
    _renderer->addChild(_slidBallRenderer);
}

void UISlider::loadBarTexture(const char* fileName, TextureResType texType)
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
                dynamic_cast<Scale9Sprite*>(_barRenderer)->initWithFile(fileName);
            }
            else
            {
                dynamic_cast<Sprite*>(_barRenderer)->initWithFile(fileName);
            }
            break;
        case UI_TEX_TYPE_PLIST:
            if (_scale9Enabled)
            {
                dynamic_cast<Scale9Sprite*>(_barRenderer)->initWithSpriteFrameName(fileName);
            }
            else
            {
                dynamic_cast<Sprite*>(_barRenderer)->initWithSpriteFrameName(fileName);
            }
            break;
        default:
            break;
    }
    if (_scale9Enabled)
    {
        dynamic_cast<Scale9Sprite*>(_barRenderer)->setColor(getColor());
        dynamic_cast<Scale9Sprite*>(_barRenderer)->setOpacity(getOpacity());
    }
    else
    {
        dynamic_cast<Sprite*>(_barRenderer)->setColor(getColor());
        dynamic_cast<Sprite*>(_barRenderer)->setOpacity(getOpacity());
    }
    barRendererScaleChangedWithSize();
}

void UISlider::loadProgressBarTexture(const char *fileName, TextureResType texType)
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
                dynamic_cast<Scale9Sprite*>(_progressBarRenderer)->initWithFile(fileName);
            }
            else
            {
                dynamic_cast<Sprite*>(_progressBarRenderer)->initWithFile(fileName);
            }
            break;
        case UI_TEX_TYPE_PLIST:
            if (_scale9Enabled)
            {
                dynamic_cast<Scale9Sprite*>(_progressBarRenderer)->initWithSpriteFrameName(fileName);
            }
            else
            {
                dynamic_cast<Sprite*>(_progressBarRenderer)->initWithSpriteFrameName(fileName);
            }
            break;
        default:
            break;
    }
    if (_scale9Enabled)
    {
        dynamic_cast<Scale9Sprite*>(_progressBarRenderer)->setColor(getColor());
        dynamic_cast<Scale9Sprite*>(_progressBarRenderer)->setOpacity(getOpacity());
    }
    else
    {
        dynamic_cast<Sprite*>(_progressBarRenderer)->setColor(getColor());
        dynamic_cast<Sprite*>(_progressBarRenderer)->setOpacity(getOpacity());
    }
    _progressBarRenderer->setAnchorPoint(Point(0.0f, 0.5f));
    _progressBarTextureSize = _progressBarRenderer->getContentSize();
    progressBarRendererScaleChangedWithSize();
}

void UISlider::setScale9Enabled(bool able)
{
    if (_scale9Enabled == able)
    {
        return;
    }
    
    _scale9Enabled = able;
    _renderer->removeChild(_barRenderer, true);
    _renderer->removeChild(_progressBarRenderer, true);
    _barRenderer = NULL;
    _progressBarRenderer = NULL;
    if (_scale9Enabled)
    {
        _barRenderer = Scale9Sprite::create();
        _progressBarRenderer = Scale9Sprite::create();
    }
    else
    {
        _barRenderer = CCSprite::create();
        _progressBarRenderer = CCSprite::create();
    }
    loadBarTexture(_textureFile.c_str(), _barTexType);
    loadProgressBarTexture(_progressBarTextureFile.c_str(), _progressBarTexType);
    _renderer->addChild(_barRenderer, -1);
    _renderer->addChild(_progressBarRenderer, -1);
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

void UISlider::ignoreContentAdaptWithSize(bool ignore)
{
    if (!_scale9Enabled || (_scale9Enabled && !ignore))
    {
        UIWidget::ignoreContentAdaptWithSize(ignore);
        _prevIgnoreSize = ignore;
    }
}

void UISlider::setCapInsets(const Rect &capInsets)
{
    setCapInsetsBarRenderer(capInsets);
    setCapInsetProgressBarRebderer(capInsets);
}

void UISlider::setCapInsetsBarRenderer(const Rect &capInsets)
{
    _capInsetsBarRenderer = capInsets;
    if (!_scale9Enabled)
    {
        return;
    }
    dynamic_cast<Scale9Sprite*>(_barRenderer)->setCapInsets(capInsets);
}

void UISlider::setCapInsetProgressBarRebderer(const Rect &capInsets)
{
    _capInsetsProgressBarRenderer = capInsets;
    if (!_scale9Enabled)
    {
        return;
    }
    dynamic_cast<Scale9Sprite*>(_progressBarRenderer)->setCapInsets(capInsets);
}

void UISlider::loadSlidBallTextures(const char* normal,const char* pressed,const char* disabled,TextureResType texType)
{
    loadSlidBallTextureNormal(normal, texType);
    loadSlidBallTexturePressed(pressed,texType);
    loadSlidBallTextureDisabled(disabled,texType);
}

void UISlider::loadSlidBallTextureNormal(const char* normal,TextureResType texType)
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
            _slidBallNormalRenderer->initWithFile(normal);
            break;
        case UI_TEX_TYPE_PLIST:
            _slidBallNormalRenderer->initWithSpriteFrameName(normal);
            break;
        default:
            break;
    }
    _slidBallNormalRenderer->setColor(getColor());
    _slidBallNormalRenderer->setOpacity(getOpacity());
}

void UISlider::loadSlidBallTexturePressed(const char* pressed,TextureResType texType)
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
            _slidBallPressedRenderer->initWithFile(pressed);
            break;
        case UI_TEX_TYPE_PLIST:
            _slidBallPressedRenderer->initWithSpriteFrameName(pressed);
            break;
        default:
            break;
    }
    _slidBallPressedRenderer->setColor(getColor());
    _slidBallPressedRenderer->setOpacity(getOpacity());
}

void UISlider::loadSlidBallTextureDisabled(const char* disabled,TextureResType texType)
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
            _slidBallDisabledRenderer->initWithFile(disabled);
            break;
        case UI_TEX_TYPE_PLIST:
            _slidBallDisabledRenderer->initWithSpriteFrameName(disabled);
            break;
        default:
            break;
    }
    _slidBallDisabledRenderer->setColor(getColor());
    _slidBallDisabledRenderer->setOpacity(getOpacity());
}

void UISlider::setPercent(int percent)
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
    float dis = _barLength*(percent/100.0f);
    _slidBallRenderer->setPosition(Point(-_barLength/2.0f + dis, 0.0f));
    if (_scale9Enabled)
    {
        dynamic_cast<Scale9Sprite*>(_progressBarRenderer)->setPreferredSize(Size(dis,_progressBarTextureSize.height));
    }
    else
    {
        int x = 0, y = 0;
        switch (_progressBarTexType)
        {
            case UI_TEX_TYPE_PLIST:
            {
                Sprite* barNode = dynamic_cast<Sprite*>(_progressBarRenderer);
                if (barNode)
                {
                    Point to = barNode->getTextureRect().origin;
                    x = to.x;
                    y = to.y;
                }
                break;
            }
            default:
                break;
        }
        dynamic_cast<Sprite*>(_progressBarRenderer)->setTextureRect(Rect(x, y, _progressBarTextureSize.width * (percent/100.0f), _progressBarTextureSize.height));
    }
}

bool UISlider::onTouchBegan(const Point &touchPoint)
{
    bool pass = UIWidget::onTouchBegan(touchPoint);
    Point nsp = _renderer->convertToNodeSpace(touchPoint);
    setPercent(getPercentWithBallPos(nsp.x));
    percentChangedEvent();
    return pass;
}

void UISlider::onTouchMoved(const Point &touchPoint)
{
    Point nsp = _renderer->convertToNodeSpace(touchPoint);
    _slidBallRenderer->setPosition(Point(nsp.x,0));
    setPercent(getPercentWithBallPos(nsp.x));
    percentChangedEvent();
}

void UISlider::onTouchEnded(const Point &touchPoint)
{
    UIWidget::onTouchEnded(touchPoint);
}

void UISlider::onTouchCancelled(const Point &touchPoint)
{
    UIWidget::onTouchCancelled(touchPoint);
}

float UISlider::getPercentWithBallPos(float px)
{
    return (((px-(-_barLength/2.0f))/_barLength)*100.0f);
}

void UISlider::addEventListener(Object *target, SEL_SlidPercentChangedEvent selector)
{
    _slidPercentListener = target;
    _slidPercentSelector = selector;
}

void UISlider::percentChangedEvent()
{
    if (_slidPercentListener && _slidPercentSelector)
    {
        (_slidPercentListener->*_slidPercentSelector)(this,SLIDER_PERCENTCHANGED);
    }
}

int UISlider::getPercent()
{
    return _percent;
}

void UISlider::onSizeChanged()
{
    barRendererScaleChangedWithSize();
    progressBarRendererScaleChangedWithSize();
}

const Size& UISlider::getContentSize() const
{
    return _barRenderer->getContentSize();
}

Node* UISlider::getVirtualRenderer()
{
    return _barRenderer;
}

void UISlider::barRendererScaleChangedWithSize()
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
            dynamic_cast<Scale9Sprite*>(_barRenderer)->setPreferredSize(_size);
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

void UISlider::progressBarRendererScaleChangedWithSize()
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
            dynamic_cast<Scale9Sprite*>(_progressBarRenderer)->setPreferredSize(_size);
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

void UISlider::onPressStateChangedToNormal()
{
    _slidBallNormalRenderer->setVisible(true);
    _slidBallPressedRenderer->setVisible(false);
    _slidBallDisabledRenderer->setVisible(false);
}

void UISlider::onPressStateChangedToPressed()
{
    _slidBallNormalRenderer->setVisible(false);
    _slidBallPressedRenderer->setVisible(true);
    _slidBallDisabledRenderer->setVisible(false);
}

void UISlider::onPressStateChangedToDisabled()
{
    _slidBallNormalRenderer->setVisible(false);
    _slidBallPressedRenderer->setVisible(false);
    _slidBallDisabledRenderer->setVisible(true);
}

const char* UISlider::getDescription() const
{
    return "Slider";
}

NS_CC_EXT_END