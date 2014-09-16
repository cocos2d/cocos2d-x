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

#include "ui/UILoadingBar.h"
#include "ui/UIScale9Sprite.h"
#include "2d/CCSprite.h"

NS_CC_BEGIN

namespace ui {
    
static const int BAR_RENDERER_Z = (-1);
    
IMPLEMENT_CLASS_GUI_INFO(LoadingBar)
    
LoadingBar::LoadingBar():
_direction(Direction::LEFT),
_percent(100.0),
_totalLength(0),
_barRenderer(nullptr),
_renderBarTexType(TextureResType::LOCAL),
_barRendererTextureSize(Size::ZERO),
_scale9Enabled(false),
_prevIgnoreSize(true),
_capInsets(Rect::ZERO),
_textureFile(""),
_barRendererAdaptDirty(true)
{
}

LoadingBar::~LoadingBar()
{
    
}

LoadingBar* LoadingBar::create()
{
    LoadingBar* widget = new (std::nothrow) LoadingBar();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}
    
LoadingBar* LoadingBar::create(const std::string &textureName, float percentage)
{
    LoadingBar* widget = new (std::nothrow) LoadingBar;
    if (widget && widget->init()) {
        widget->autorelease();
        widget->loadTexture(textureName);
        widget->setPercent(percentage);
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

void LoadingBar::initRenderer()
{
    _barRenderer = Scale9Sprite::create();
    _barRenderer->setScale9Enabled(false);
    addProtectedChild(_barRenderer, BAR_RENDERER_Z, -1);
    _barRenderer->setAnchorPoint(Vec2(0.0,0.5));
}

    
void LoadingBar::setDirection(cocos2d::ui::LoadingBar::Direction direction)
{
    if (_direction == direction)
    {
        return;
    }
    _direction = direction;
    
    switch (_direction)
    {
        case Direction::LEFT:
            _barRenderer->setAnchorPoint(Vec2(0.0f,0.5f));
            _barRenderer->setPosition(0,0.0f);
            if (!_scale9Enabled) {
                _barRenderer->setFlippedX(false);
            }
            break;
        case Direction::RIGHT:
            _barRenderer->setAnchorPoint(Vec2(1.0f,0.5f));
            _barRenderer->setPosition(_totalLength,0.0f);
            if (!_scale9Enabled) {
                _barRenderer->setFlippedX(true);
            }
            break;
    }

}

LoadingBar::Direction LoadingBar::getDirection()const
{
    return _direction;
}
    

void LoadingBar::loadTexture(const std::string& texture,TextureResType texType)
{
    if (texture.empty())
    {
        return;
    }
    _renderBarTexType = texType;
    _textureFile = texture;
    switch (_renderBarTexType)
    {
        case TextureResType::LOCAL:
            _barRenderer->initWithFile(texture);
            break;
        case TextureResType::PLIST:
            _barRenderer->initWithSpriteFrameName(texture);
            break;
        default:
            break;
    }
    
    _barRendererTextureSize = _barRenderer->getContentSize();
    
    switch (_direction)
    {
        case Direction::LEFT:
            _barRenderer->setAnchorPoint(Vec2(0.0f,0.5f));
            if (!_scale9Enabled) {
                _barRenderer->setFlippedX(false);
            }
            break;
        case Direction::RIGHT:
            _barRenderer->setAnchorPoint(Vec2(1.0f,0.5f));
            if (!_scale9Enabled) {
                _barRenderer->setFlippedX(true);
            }
            break;
    }
    _barRenderer->setCapInsets(_capInsets);
    this->updateChildrenDisplayedRGBA();

    barRendererScaleChangedWithSize();
    updateContentSizeWithTextureSize(_barRendererTextureSize);
    _barRendererAdaptDirty = true;
}

void LoadingBar::setScale9Enabled(bool enabled)
{
    if (_scale9Enabled == enabled)
    {
        return;
    }
    _scale9Enabled = enabled;
    _barRenderer->setScale9Enabled(_scale9Enabled);
    
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
    setPercent(_percent);
}

bool LoadingBar::isScale9Enabled()const
{
    return _scale9Enabled;
}
    
void LoadingBar::setCapInsets(const Rect &capInsets)
{
    _capInsets = capInsets;
    if (!_scale9Enabled)
    {
        return;
    }
    _barRenderer->setCapInsets(capInsets);
}

const Rect& LoadingBar::getCapInsets()const
{
    return _capInsets;
}
    
void LoadingBar::setPercent(float percent)
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
    float res = _percent / 100.0f;
    
    if (_scale9Enabled)
    {
        setScale9Scale();
    }
    else
    {
        Sprite* spriteRenderer = _barRenderer->getSprite();
        Rect rect = spriteRenderer->getTextureRect();
        rect.size.width = _barRendererTextureSize.width * res;
        spriteRenderer->setTextureRect(rect, spriteRenderer->isTextureRectRotated(), rect.size);
    }
}

float LoadingBar::getPercent() const
{
    return _percent;
}

void LoadingBar::onSizeChanged()
{
    Widget::onSizeChanged();
    _barRendererAdaptDirty = true;
}
    
void LoadingBar::adaptRenderers()
{
    if (_barRendererAdaptDirty)
    {
        barRendererScaleChangedWithSize();
        _barRendererAdaptDirty = false;
    }
}

void LoadingBar::ignoreContentAdaptWithSize(bool ignore)
{
    if (!_scale9Enabled || (_scale9Enabled && !ignore))
    {
        Widget::ignoreContentAdaptWithSize(ignore);
        _prevIgnoreSize = ignore;
    }
}

Size LoadingBar::getVirtualRendererSize() const
{
    return _barRendererTextureSize;
}

Node* LoadingBar::getVirtualRenderer()
{
    return _barRenderer;
}

void LoadingBar::barRendererScaleChangedWithSize()
{
    if (_ignoreSize)
    {
        if (!_scale9Enabled)
        {
            _totalLength = _barRendererTextureSize.width;
            _barRenderer->setScale(1.0f);
        }
    }
    else
    {
        _totalLength = _contentSize.width;
        if (_scale9Enabled)
        {
            setScale9Scale();
        }
        else
        {
            
            Size textureSize = _barRendererTextureSize;
            if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
            {
                _barRenderer->setScale(1.0f);
                return;
            }
            float scaleX = _contentSize.width / textureSize.width;
            float scaleY = _contentSize.height / textureSize.height;
            _barRenderer->setScaleX(scaleX);
            _barRenderer->setScaleY(scaleY);
        }
    }
    switch (_direction)
    {
        case Direction::LEFT:
            _barRenderer->setPosition(0.0f, _contentSize.height / 2.0f);
            break;
        case Direction::RIGHT:
            _barRenderer->setPosition(_totalLength, _contentSize.height / 2.0f);
            break;
        default:
            break;
    }
}

void LoadingBar::setScale9Scale()
{
    float width = (float)(_percent) / 100.0f * _totalLength;
    _barRenderer->setPreferredSize(Size(width, _contentSize.height));
}

std::string LoadingBar::getDescription() const
{
    return "LoadingBar";
}

Widget* LoadingBar::createCloneInstance()
{
    return LoadingBar::create();
}

void LoadingBar::copySpecialProperties(Widget *widget)
{
    LoadingBar* loadingBar = dynamic_cast<LoadingBar*>(widget);
    if (loadingBar)
    {
        _prevIgnoreSize = loadingBar->_prevIgnoreSize;
        setScale9Enabled(loadingBar->_scale9Enabled);
        loadTexture(loadingBar->_textureFile, loadingBar->_renderBarTexType);
        setCapInsets(loadingBar->_capInsets);
        setPercent(loadingBar->_percent);
        setDirection(loadingBar->_direction);
    }
}

}

NS_CC_END
