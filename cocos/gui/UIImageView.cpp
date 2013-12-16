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

#include "gui/UIImageView.h"
#include "extensions/GUI/CCControlExtension/CCScale9Sprite.h"

NS_CC_BEGIN

namespace gui {


#define DYNAMIC_CAST_CCSPRITE dynamic_cast<Sprite*>(_imageRenderer)
#define DYNAMIC_CAST_SCALE9SPRITE dynamic_cast<extension::Scale9Sprite*>(_imageRenderer)

ImageView::ImageView():
_scale9Enabled(false),
_prevIgnoreSize(true),
_capInsets(Rect::ZERO),
_imageRenderer(nullptr),
_textureFile(""),
_imageTexType(UI_TEX_TYPE_LOCAL),
_imageTextureSize(_size)
{

}

ImageView::~ImageView()
{
    
}

ImageView* ImageView::create()
{
    ImageView* widget = new ImageView();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

void ImageView::initRenderer()
{
    Widget::initRenderer();
    _imageRenderer = Sprite::create();
    _renderer->addChild(_imageRenderer);
}

void ImageView::loadTexture(const char *fileName, TextureResType texType)
{
    if (!fileName || strcmp(fileName, "") == 0)
    {
        return;
    }
    _textureFile = fileName;
    _imageTexType = texType;
    switch (_imageTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            if (_scale9Enabled)
            {
                DYNAMIC_CAST_SCALE9SPRITE->initWithFile(fileName);
                DYNAMIC_CAST_SCALE9SPRITE->setColor(getColor());
                DYNAMIC_CAST_SCALE9SPRITE->setOpacity(getOpacity());
                DYNAMIC_CAST_SCALE9SPRITE->setCapInsets(_capInsets);
            }
            else
            {
                DYNAMIC_CAST_CCSPRITE->setTexture(fileName);
                DYNAMIC_CAST_CCSPRITE->setColor(getColor());
                DYNAMIC_CAST_CCSPRITE->setOpacity(getOpacity());
            }
            break;
        case UI_TEX_TYPE_PLIST:
            if (_scale9Enabled)
            {
                DYNAMIC_CAST_SCALE9SPRITE->initWithSpriteFrameName(fileName);
                DYNAMIC_CAST_SCALE9SPRITE->setColor(getColor());
                DYNAMIC_CAST_SCALE9SPRITE->setOpacity(getOpacity());
                DYNAMIC_CAST_SCALE9SPRITE->setCapInsets(_capInsets);
            }
            else
            {
                DYNAMIC_CAST_CCSPRITE->setSpriteFrame(fileName);
                DYNAMIC_CAST_CCSPRITE->setColor(getColor());
                DYNAMIC_CAST_CCSPRITE->setOpacity(getOpacity());
            }
            break;
        default:
            break;
    }
    _imageTextureSize = _imageRenderer->getContentSize();
    updateAnchorPoint();
    imageTextureScaleChangedWithSize();
}

void ImageView::setTextureRect(const Rect &rect)
{
    if (_scale9Enabled)
    {
    }
    else
    {
        DYNAMIC_CAST_CCSPRITE->setTextureRect(rect);
    }
}

void ImageView::setFlipX(bool flipX)
{
    if (_scale9Enabled)
    {
    }
    else
    {
        DYNAMIC_CAST_CCSPRITE->setFlippedX(flipX);
    }
}

void ImageView::setFlipY(bool flipY)
{
    if (_scale9Enabled)
    {
    }
    else
    {
        DYNAMIC_CAST_CCSPRITE->setFlippedY(flipY);
    }
}

bool ImageView::isFlipX()
{
    if (_scale9Enabled)
    {
        return false;
    }
    else
    {
        return DYNAMIC_CAST_CCSPRITE->isFlippedX();
    }
}

bool ImageView::isFlipY()
{
    if (_scale9Enabled)
    {
        return false;
    }
    else
    {
        return DYNAMIC_CAST_CCSPRITE->isFlippedY();
    }
}

void ImageView::setScale9Enabled(bool able)
{
    if (_scale9Enabled == able)
    {
        return;
    }
    
    
    _scale9Enabled = able;
    _renderer->removeChild(_imageRenderer, true);
    _imageRenderer = nullptr;
    if (_scale9Enabled)
    {
        _imageRenderer = extension::Scale9Sprite::create();
    }
    else
    {
        _imageRenderer = Sprite::create();
    }
    loadTexture(_textureFile.c_str(),_imageTexType);
    _renderer->addChild(_imageRenderer);
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

void ImageView::ignoreContentAdaptWithSize(bool ignore)
{
    if (!_scale9Enabled || (_scale9Enabled && !ignore))
    {
        Widget::ignoreContentAdaptWithSize(ignore);
        _prevIgnoreSize = ignore;
    }
}

void ImageView::setCapInsets(const Rect &capInsets)
{
    _capInsets = capInsets;
    if (!_scale9Enabled)
    {
        return;
    }
    DYNAMIC_CAST_SCALE9SPRITE->setCapInsets(capInsets);
}

void ImageView::setAnchorPoint(const Point &pt)
{
    Widget::setAnchorPoint(pt);
    _imageRenderer->setAnchorPoint(pt);
}

void ImageView::onSizeChanged()
{
    imageTextureScaleChangedWithSize();
}

const Size& ImageView::getContentSize() const
{
    return _imageTextureSize;
}

Node* ImageView::getVirtualRenderer()
{
    return _imageRenderer;
}

void ImageView::imageTextureScaleChangedWithSize()
{
    if (_ignoreSize)
    {
        if (!_scale9Enabled)
        {
            _imageRenderer->setScale(1.0f);
            _size = _imageTextureSize;
        }
    }
    else
    {
        if (_scale9Enabled)
        {
            dynamic_cast<extension::Scale9Sprite*>(_imageRenderer)->setPreferredSize(_size);
        }
        else
        {
            Size textureSize = _imageRenderer->getContentSize();
            if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
            {
                _imageRenderer->setScale(1.0f);
                return;
            }
            float scaleX = _size.width / textureSize.width;
            float scaleY = _size.height / textureSize.height;
            _imageRenderer->setScaleX(scaleX);
            _imageRenderer->setScaleY(scaleY);
        }
    }
}

const char* ImageView::getDescription() const
{
    return "ImageView";
}

Widget* ImageView::createCloneInstance()
{
    return ImageView::create();
}

void ImageView::copySpecialProperties(Widget *widget)
{
    ImageView* imageView = dynamic_cast<ImageView*>(widget);
    if (imageView)
    {
        _prevIgnoreSize = imageView->_prevIgnoreSize;
        setScale9Enabled(imageView->_scale9Enabled);
        loadTexture(imageView->_textureFile.c_str(), imageView->_imageTexType);
        setCapInsets(imageView->_capInsets);
    }
}

}

NS_CC_END