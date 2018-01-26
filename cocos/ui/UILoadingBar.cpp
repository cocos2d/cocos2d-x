/****************************************************************************
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
#include "ui/UIHelper.h"
#include "ui/UIScale9Sprite.h"
#include "2d/CCSprite.h"
#include "editor-support/cocostudio/CocosStudioExtension.h"

NS_CC_BEGIN

/* FIXME:
 Code could be simplified by using Sprite's setContentSize feature.
 Instead of scaling the sprite, set call setContentSize both in scale9 and non-scale9 modes
 */

namespace ui {
    
static const int BAR_RENDERER_Z = (-1);
    
IMPLEMENT_CLASS_GUI_INFO(LoadingBar)
    
LoadingBar::LoadingBar():
_direction(Direction::LEFT),
_percent(100.0),
_totalLength(0),
_textureFile(""),
_barRenderer(nullptr),
_renderBarTexType(TextureResType::LOCAL),
_barRendererTextureSize(Size::ZERO),
_originalRect(Rect::ZERO),
_scale9Enabled(false),
_prevIgnoreSize(true),
_capInsets(Rect::ZERO),
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
    return LoadingBar::create(textureName, TextureResType::LOCAL, percentage);
}
    
LoadingBar* LoadingBar::create(const std::string &textureName,
                               TextureResType texType,
                               float percentage)
{
    LoadingBar* widget = new (std::nothrow) LoadingBar;
    if (widget && widget->init())
    {
        widget->autorelease();
        widget->loadTexture(textureName,texType);
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
            _barRenderer->setPosition(Vec2(0,_contentSize.height*0.5f));
            break;
        case Direction::RIGHT:
            _barRenderer->setAnchorPoint(Vec2(1.0f,0.5f));
            _barRenderer->setPosition(Vec2(_totalLength,_contentSize.height*0.5f));
            break;
    }
    this->handleSpriteFlipX();
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
    _textureFile = texture;
    _renderBarTexType = texType;
    switch (_renderBarTexType)
    {
        case TextureResType::LOCAL:
            _barRenderer->setTexture(texture);
            break;
        case TextureResType::PLIST:
            _barRenderer->setSpriteFrame(texture);
            break;
        default:
            break;
    }
    
    //FIXME: https://github.com/cocos2d/cocos2d-x/issues/12249
    if (!_ignoreSize && _customSize.equals(Size::ZERO)) {
        _customSize = _barRenderer->getContentSize();
    }
    this->setupTexture();
}

void LoadingBar::loadTexture(SpriteFrame* spriteframe)
{
    this->_barRenderer->initWithSpriteFrame(spriteframe);
    this->setupTexture();
}

void LoadingBar::setupTexture()
{
    _barRendererTextureSize = _barRenderer->getContentSize();
    _originalRect = _barRenderer->getTextureRect();

    switch (_direction)
    {
        case Direction::LEFT:
            _barRenderer->setAnchorPoint(Vec2(0.0f,0.5f));
            break;
        case Direction::RIGHT:
            _barRenderer->setAnchorPoint(Vec2(1.0f,0.5f));
            break;
    }
    this->handleSpriteFlipX();

    _barRenderer->setCapInsets(_capInsets);

    this->updateChildrenDisplayedRGBA();

    barRendererScaleChangedWithSize();

    updateContentSizeWithTextureSize(_barRendererTextureSize);


    this->updateProgressBar();

    _barRendererAdaptDirty = true;
}
    
void LoadingBar::handleSpriteFlipX()
{
    if (_direction == Direction::LEFT)
    {
        if (!_scale9Enabled)
        {
            _barRenderer->setFlippedX(false);
        }
    }
    else
    {
        if (!_scale9Enabled)
        {
            _barRenderer->setFlippedX(true);
        }
    }
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

    updateProgressBar();
    _barRendererAdaptDirty = true;
}

bool LoadingBar::isScale9Enabled()const
{
    return _scale9Enabled;
}
    
void LoadingBar::setCapInsets(const Rect &capInsets)
{
    _capInsets = ui::Helper::restrictCapInsetRect(capInsets, _barRendererTextureSize);
    if (!_scale9Enabled)
    {
        return;
    }

    // textureRect should be restored in order to calculate the scale9 correctly
    // https://github.com/cocos2d/cocos2d-x/issues/16930
    _barRenderer->setTextureRect(_originalRect, _barRenderer->isTextureRectRotated(), _barRendererTextureSize);
    _barRenderer->setCapInsets(_capInsets);
}

const Rect& LoadingBar::getCapInsets()const
{
    return _capInsets;
}
    
void LoadingBar::setPercent(float percent)
{
    if (percent > 100)
    {
        percent = 100;
    }
    if (percent < 0)
    {
        percent = 0;
    }
    if (_percent == percent)
    {
        return;
    }
     _percent = percent;
    
    if (_totalLength <= 0)
    {
        return;
    }
    
    this->updateProgressBar();
}
    
void LoadingBar::updateProgressBar()
{
    if (_scale9Enabled)
    {
        setScale9Scale();
    }
    else
    {
        float res = _percent / 100.0f;
        Rect rect = _barRenderer->getTextureRect();
        rect.size.width = _barRendererTextureSize.width * res;
        _barRenderer->setTextureRect(rect, _barRenderer->isTextureRectRotated(), rect.size);
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
    if (_unifySize)
    {
        //_barRenderer->setPreferredSize(_contentSize);
        _totalLength = _contentSize.width;
        this->setPercent(_percent);
    }
    else if (_ignoreSize)
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
            this->setScale9Scale();
            _barRenderer->setScale(1.0f);
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
            _barRenderer->setPosition(Vec2(0.0f,_contentSize.height*0.5f));
            break;
        case Direction::RIGHT:
            _barRenderer->setPosition(Vec2(_totalLength,_contentSize.height*0.5f));
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

        // clone the inner sprite: https://github.com/cocos2d/cocos2d-x/issues/16930
        loadingBar->_barRenderer->copyTo(_barRenderer);
        setupTexture();

        setCapInsets(loadingBar->_capInsets);
        setPercent(loadingBar->_percent);
        setDirection(loadingBar->_direction);
        _textureFile = loadingBar->_textureFile;
        _totalLength = loadingBar->_totalLength;
        _barRendererTextureSize = loadingBar->_barRendererTextureSize;
    }
}

ResourceData LoadingBar::getRenderFile()
{
    ResourceData rData;
    rData.type = (int)_renderBarTexType;
    rData.file = _textureFile;
    return rData;
}

}

NS_CC_END
