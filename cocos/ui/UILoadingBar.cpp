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
#include "extensions/GUI/CCControlExtension/CCScale9Sprite.h"

NS_CC_BEGIN

namespace ui {
    
static const int BAR_RENDERER_Z = (-1);
    
IMPLEMENT_CLASS_GUI_INFO(LoadingBar)
    
LoadingBar::LoadingBar():
_barType(LoadingBarTypeLeft),
_percent(100),
_totalLength(0),
_barRenderer(nullptr),
_renderBarTexType(UI_TEX_TYPE_LOCAL),
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
    LoadingBar* widget = new LoadingBar();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}
    
LoadingBar* LoadingBar::create(const std::string &textureName, int percentage)
{
    LoadingBar* widget = new LoadingBar;
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
    _barRenderer = Sprite::create();
    addProtectedChild(_barRenderer, BAR_RENDERER_Z, -1);
    _barRenderer->setAnchorPoint(Point(0.0,0.5));
}

void LoadingBar::setDirection(LoadingBarType dir)
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
                static_cast<Sprite*>(_barRenderer)->setFlippedX(false);
            }
            break;
        case LoadingBarTypeRight:
            _barRenderer->setAnchorPoint(Point(1.0f,0.5f));
            _barRenderer->setPosition(Point(_totalLength*0.5f,0.0f));
            if (!_scale9Enabled)
            {
                static_cast<Sprite*>(_barRenderer)->setFlippedX(true);
            }
            break;
    }
}

int LoadingBar::getDirection()
{
    return _barType;
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
        case UI_TEX_TYPE_LOCAL:
            if (_scale9Enabled)
            {
                extension::Scale9Sprite* barRendererScale9 = static_cast<extension::Scale9Sprite*>(_barRenderer);
                barRendererScale9->initWithFile(texture);
                barRendererScale9->setCapInsets(_capInsets);
            }
            else
            {
                static_cast<Sprite*>(_barRenderer)->setTexture(texture);
            }
            break;
        case UI_TEX_TYPE_PLIST:
            if (_scale9Enabled)
            {
                extension::Scale9Sprite* barRendererScale9 = static_cast<extension::Scale9Sprite*>(_barRenderer);
                barRendererScale9->initWithSpriteFrameName(texture);
                barRendererScale9->setCapInsets(_capInsets);
            }
            else
            {
                static_cast<Sprite*>(_barRenderer)->setSpriteFrame(texture);
            }
            break;
        default:
            break;
    }
    updateRGBAToRenderer(_barRenderer);
    _barRendererTextureSize = _barRenderer->getContentSize();
    
    switch (_barType)
    {
    case LoadingBarTypeLeft:
        _barRenderer->setAnchorPoint(Point(0.0f,0.5f));
        if (!_scale9Enabled)
        {
            static_cast<Sprite*>(_barRenderer)->setFlippedX(false);
        }
        break;
    case LoadingBarTypeRight:
        _barRenderer->setAnchorPoint(Point(1.0f,0.5f));
        if (!_scale9Enabled)
        {
            static_cast<Sprite*>(_barRenderer)->setFlippedX(true);
        }
        break;
    }
//    barRendererScaleChangedWithSize();
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
    removeProtectedChild(_barRenderer);
    _barRenderer = nullptr;
    if (_scale9Enabled)
    {
        _barRenderer = extension::Scale9Sprite::create();
    }
    else
    {
        _barRenderer = Sprite::create();
    }
    loadTexture(_textureFile,_renderBarTexType);
    addProtectedChild(_barRenderer, BAR_RENDERER_Z, -1);
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

bool LoadingBar::isScale9Enabled()
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
    static_cast<extension::Scale9Sprite*>(_barRenderer)->setCapInsets(capInsets);
}

const Rect& LoadingBar::getCapInsets()
{
    return _capInsets;
}
    
void LoadingBar::setPercent(int percent)
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
        Sprite* spriteRenderer = static_cast<Sprite*>(_barRenderer);
        Rect rect = spriteRenderer->getTextureRect();
        rect.size.width = _barRendererTextureSize.width * res;
        spriteRenderer->setTextureRect(rect, spriteRenderer->isTextureRectRotated(), rect.size);
    }
}

int LoadingBar::getPercent()
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

const Size& LoadingBar::getVirtualRendererSize() const
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
        _totalLength = _size.width;
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
            float scaleX = _size.width / textureSize.width;
            float scaleY = _size.height / textureSize.height;
            _barRenderer->setScaleX(scaleX);
            _barRenderer->setScaleY(scaleY);
        }
    }
    switch (_barType)
    {
        case LoadingBarTypeLeft:
            _barRenderer->setPosition(Point(0.0f, _contentSize.height / 2.0f));
            break;
        case LoadingBarTypeRight:
            _barRenderer->setPosition(Point(_totalLength, _contentSize.height / 2.0f));
            break;
        default:
            break;
    }
}

void LoadingBar::setScale9Scale()
{
    float width = (float)(_percent) / 100.0f * _totalLength;
    static_cast<extension::Scale9Sprite*>(_barRenderer)->setPreferredSize(Size(width, _size.height));
}

std::string LoadingBar::getDescription() const
{
    return "LoadingBar";
}
    
void LoadingBar::updateTextureColor()
{
    updateColorToRenderer(_barRenderer);
}

void LoadingBar::updateTextureOpacity()
{
    updateOpacityToRenderer(_barRenderer);
}

void LoadingBar::updateTextureRGBA()
{
    updateRGBAToRenderer(_barRenderer);
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
        setDirection(loadingBar->_barType);
    }
}

}

NS_CC_END
