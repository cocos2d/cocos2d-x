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

#include "UILoadingBar.h"
#include "../../../GUI/CCControlExtension/CCScale9Sprite.h"

NS_CC_EXT_BEGIN

#define DYNAMIC_CAST_CCSPRITE dynamic_cast<cocos2d::Sprite*>(_barRenderer)

UILoadingBar::UILoadingBar():
_barType(LoadingBarTypeLeft),
_percent(100),
_totalLength(0),
_barRenderer(NULL),
_renderBarTexType(UI_TEX_TYPE_LOCAL),
_barRendererTextureSize(Size::ZERO),
_scale9Enabled(false),
_prevIgnoreSize(true),
_capInsets(Rect::ZERO),
_textureFile("")
{
}

UILoadingBar::~UILoadingBar()
{
    
}

UILoadingBar* UILoadingBar::create()
{
    UILoadingBar* widget = new UILoadingBar();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

void UILoadingBar::initRenderer()
{
    UIWidget::initRenderer();
    _barRenderer = CCSprite::create();
    _renderer->addChild(_barRenderer);
    _barRenderer->setAnchorPoint(Point(0.0f,0.5f));
}

void UILoadingBar::setDirection(LoadingBarType dir)
{
    if (_barType == dir)
    {
        return;
    }
    _barType = dir;

    switch (_barType)
    {
        case LoadingBarTypeLeft:
            _barRenderer->setAnchorPoint(Point(0.0f,0.5f));
            _barRenderer->setPosition(Point(-_totalLength*0.5f,0.0f));
            if (!_scale9Enabled)
            {
                dynamic_cast<Sprite*>(_barRenderer)->setFlippedX(false);
            }
            break;
        case LoadingBarTypeRight:
            _barRenderer->setAnchorPoint(Point(1.0f,0.5f));
            _barRenderer->setPosition(Point(_totalLength*0.5f,0.0f));
            if (!_scale9Enabled)
            {
                dynamic_cast<Sprite*>(_barRenderer)->setFlippedX(true);
            }
            break;
    }
}

int UILoadingBar::getDirection()
{
    return _barType;
}

void UILoadingBar::loadTexture(const char* texture,TextureResType texType)
{
    if (!texture || strcmp(texture, "") == 0)
    {
        return;
    }
    _renderBarTexType = texType;
    _textureFile = texture;
    switch (_renderBarTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            if (_scale9Enabled)
            {
                dynamic_cast<Scale9Sprite*>(_barRenderer)->initWithFile(texture);
            }
            else
            {
                dynamic_cast<Sprite*>(_barRenderer)->initWithFile(texture);
            }
            break;
        case UI_TEX_TYPE_PLIST:
            if (_scale9Enabled)
            {
                dynamic_cast<Scale9Sprite*>(_barRenderer)->initWithSpriteFrameName(texture);
            }
            else
            {
                dynamic_cast<Sprite*>(_barRenderer)->initWithSpriteFrameName(texture);
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
    _barRendererTextureSize.width = _barRenderer->getContentSize().width;
    _barRendererTextureSize.height = _barRenderer->getContentSize().height;
    
    switch (_barType)
    {
    case LoadingBarTypeLeft:
        _barRenderer->setAnchorPoint(Point(0.0f,0.5f));
        if (!_scale9Enabled)
        {
            dynamic_cast<Sprite*>(_barRenderer)->setFlippedX(false);
        }
        break;
    case LoadingBarTypeRight:
        _barRenderer->setAnchorPoint(Point(1.0f,0.5f));
        if (!_scale9Enabled)
        {
            dynamic_cast<Sprite*>(_barRenderer)->setFlippedX(true);
        }
        break;
    }
    barRendererScaleChangedWithSize();
}

void UILoadingBar::setScale9Enabled(bool enabled)
{
    if (_scale9Enabled == enabled)
    {
        return;
    }
    _scale9Enabled = enabled;
    _renderer->removeChild(_barRenderer, true);
    _barRenderer = NULL;
    if (_scale9Enabled)
    {
        _barRenderer = Scale9Sprite::create();
    }
    else
    {
        _barRenderer = CCSprite::create();
    }
    loadTexture(_textureFile.c_str(),_renderBarTexType);
    _renderer->addChild(_barRenderer);
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
    setCapInsets(_capInsets);
}

void UILoadingBar::setCapInsets(const Rect &capInsets)
{
    _capInsets = capInsets;
    if (!_scale9Enabled)
    {
        return;
    }
    dynamic_cast<Scale9Sprite*>(_barRenderer)->setCapInsets(capInsets);
}

void UILoadingBar::setPercent(int percent)
{
    if ( percent < 0 || percent > 100)
    {
        return;
    }
    if (_totalLength <= 0)
    {
        return;
    }
    _percent = percent;
    float res = _percent/100.0;
    
    int x = 0, y = 0;
    switch (_renderBarTexType)
    {
        case UI_TEX_TYPE_PLIST:
        {
            Sprite* barNode = DYNAMIC_CAST_CCSPRITE;
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
    if (_scale9Enabled)
    {
        setScale9Scale();
    }
    else
    {
        dynamic_cast<Sprite*>(_barRenderer)->setTextureRect(Rect(x, y, _barRendererTextureSize.width * res, _barRendererTextureSize.height));
    }
}

int UILoadingBar::getPercent()
{
    return _percent;
}

void UILoadingBar::onSizeChanged()
{
    barRendererScaleChangedWithSize();
}

void UILoadingBar::ignoreContentAdaptWithSize(bool ignore)
{
    if (!_scale9Enabled || (_scale9Enabled && !ignore))
    {
        UIWidget::ignoreContentAdaptWithSize(ignore);
        _prevIgnoreSize = ignore;
    }
}

const Size& UILoadingBar::getContentSize() const
{
    return _barRendererTextureSize;
}

Node* UILoadingBar::getVirtualRenderer()
{
    return _barRenderer;
}

void UILoadingBar::barRendererScaleChangedWithSize()
{
    if (_ignoreSize)
    {
        if (!_scale9Enabled)
        {
            _totalLength = _barRendererTextureSize.width;
            _barRenderer->setScale(1.0f);
            _size = _barRendererTextureSize;
        }
    }
    else
    {
        _totalLength = _size.width;
        if (_scale9Enabled)
        {
            setScale9Scale();
        }
        else
        {
            
            Size textureSize = _barRenderer->getContentSize();
            if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
            {
                _barRenderer->setScale(1.0f);
                return;
            }
            float scaleX = _size.width / textureSize.width;
            float scaleY = _size.height / textureSize.height;
            _barRenderer->setScaleX(scaleX);
            _barRenderer->setScaleY(scaleY);
        }
    }
    switch (_barType)
    {
        case LoadingBarTypeLeft:
            _barRenderer->setPosition(Point(-_totalLength * 0.5f, 0.0f));
            break;
        case LoadingBarTypeRight:
            _barRenderer->setPosition(Point(_totalLength * 0.5f, 0.0f));
            break;
        default:
            break;
    }
}

void UILoadingBar::setScale9Scale()
{
    float width = (float)(_percent) / 100 * _totalLength;
    dynamic_cast<Scale9Sprite*>(_barRenderer)->setPreferredSize(Size(width, _barRendererTextureSize.height));
}

const char* UILoadingBar::getDescription() const
{
    return "LoadingBar";
}

NS_CC_EXT_END