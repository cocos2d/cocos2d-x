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

NS_CC_BEGIN

namespace ui {
    
static const int BAR_RENDERER_Z = (-1);
    
IMPLEMENT_CLASS_GUI_INFO(LoadingBar)
    
LoadingBar::LoadingBar():
_barType(LoadingBarTypeLeft),
_percent(100),
_totalLength(0),
_barRenderer(NULL),
_renderBarTexType(UI_TEX_TYPE_LOCAL),
_barRendererTextureSize(CCSizeZero),
_scale9Enabled(false),
_prevIgnoreSize(true),
_capInsets(CCRectZero),
_textureFile("")
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
    return NULL;
}

void LoadingBar::initRenderer()
{
    _barRenderer = CCSprite::create();
    CCNode::addChild(_barRenderer, BAR_RENDERER_Z, -1);
    _barRenderer->setAnchorPoint(CCPoint(0.0,0.5));
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
            _barRenderer->setAnchorPoint(CCPoint(0.0f,0.5f));
            _barRenderer->setPosition(CCPoint(-_totalLength*0.5f,0.0f));
            if (!_scale9Enabled)
            {
                static_cast<CCSprite*>(_barRenderer)->setFlipX(false);
            }
            break;
        case LoadingBarTypeRight:
            _barRenderer->setAnchorPoint(CCPoint(1.0f,0.5f));
            _barRenderer->setPosition(CCPoint(_totalLength*0.5f,0.0f));
            if (!_scale9Enabled)
            {
                static_cast<CCSprite*>(_barRenderer)->setFlipX(true);
            }
            break;
    }
}

int LoadingBar::getDirection()
{
    return _barType;
}

void LoadingBar::loadTexture(const char* texture,TextureResType texType)
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
                extension::CCScale9Sprite* barRendererScale9 = static_cast<extension::CCScale9Sprite*>(_barRenderer);
                barRendererScale9->initWithFile(texture);
                barRendererScale9->setCapInsets(_capInsets);
            }
            else
            {
                static_cast<CCSprite*>(_barRenderer)->initWithFile(texture);
            }
            break;
        case UI_TEX_TYPE_PLIST:
            if (_scale9Enabled)
            {
                extension::CCScale9Sprite* barRendererScale9 = static_cast<extension::CCScale9Sprite*>(_barRenderer);
                barRendererScale9->initWithSpriteFrameName(texture);
                barRendererScale9->setCapInsets(_capInsets);
            }
            else
            {
                static_cast<CCSprite*>(_barRenderer)->initWithSpriteFrameName(texture);
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
        _barRenderer->setAnchorPoint(CCPoint(0.0f,0.5f));
        if (!_scale9Enabled)
        {
            static_cast<CCSprite*>(_barRenderer)->setFlipX(false);
        }
        break;
    case LoadingBarTypeRight:
        _barRenderer->setAnchorPoint(CCPoint(1.0f,0.5f));
        if (!_scale9Enabled)
        {
            static_cast<CCSprite*>(_barRenderer)->setFlipX(true);
        }
        break;
    }
    barRendererScaleChangedWithSize();
}

void LoadingBar::setScale9Enabled(bool enabled)
{
    if (_scale9Enabled == enabled)
    {
        return;
    }
    _scale9Enabled = enabled;
    CCNode::removeChild(_barRenderer, true);
    _barRenderer = NULL;
    if (_scale9Enabled)
    {
        _barRenderer = extension::CCScale9Sprite::create();
    }
    else
    {
        _barRenderer = CCSprite::create();
    }
    loadTexture(_textureFile.c_str(),_renderBarTexType);
    CCNode::addChild(_barRenderer, BAR_RENDERER_Z, -1);
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

void LoadingBar::setCapInsets(const CCRect &capInsets)
{
    _capInsets = capInsets;
    if (!_scale9Enabled)
    {
        return;
    }
    static_cast<extension::CCScale9Sprite*>(_barRenderer)->setCapInsets(capInsets);
}
    
const CCRect& LoadingBar::getCapInsets()
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
        CCSprite* spriteRenderer = static_cast<CCSprite*>(_barRenderer);
        CCRect rect = spriteRenderer->getTextureRect();
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
    barRendererScaleChangedWithSize();
}

void LoadingBar::ignoreContentAdaptWithSize(bool ignore)
{
    if (!_scale9Enabled || (_scale9Enabled && !ignore))
    {
        Widget::ignoreContentAdaptWithSize(ignore);
        _prevIgnoreSize = ignore;
    }
}

const CCSize& LoadingBar::getContentSize() const
{
    return _barRendererTextureSize;
}

CCNode* LoadingBar::getVirtualRenderer()
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
            
            CCSize textureSize = _barRendererTextureSize;
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
            _barRenderer->setPosition(CCPoint(-_totalLength * 0.5f, 0.0f));
            break;
        case LoadingBarTypeRight:
            _barRenderer->setPosition(CCPoint(_totalLength * 0.5f, 0.0f));
            break;
        default:
            break;
    }
}

void LoadingBar::setScale9Scale()
{
    float width = (float)(_percent) / 100.0f * _totalLength;
    static_cast<extension::CCScale9Sprite*>(_barRenderer)->setPreferredSize(CCSize(width, _size.height));
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
        loadTexture(loadingBar->_textureFile.c_str(), loadingBar->_renderBarTexType);
        setCapInsets(loadingBar->_capInsets);
        setPercent(loadingBar->_percent);
        setDirection(loadingBar->_barType);
    }
}

}

NS_CC_END