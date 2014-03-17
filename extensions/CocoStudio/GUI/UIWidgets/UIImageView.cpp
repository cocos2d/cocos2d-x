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

#include "UIImageView.h"
#include "../../../GUI/CCControlExtension/CCScale9Sprite.h"

NS_CC_BEGIN

namespace ui {


#define STATIC_CAST_CCSPRITE static_cast<CCSprite*>(_imageRenderer)
#define STATIC_CAST_SCALE9SPRITE static_cast<extension::CCScale9Sprite*>(_imageRenderer)
    
static const int IMAGE_RENDERER_Z = (-1);
    
    IMPLEMENT_CLASS_GUI_INFO(ImageView)

ImageView::ImageView():
_scale9Enabled(false),
_prevIgnoreSize(true),
_capInsets(CCRectZero),
_imageRenderer(NULL),
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
    return NULL;
}

void ImageView::initRenderer()
{
    _imageRenderer = CCSprite::create();
    CCNode::addChild(_imageRenderer, IMAGE_RENDERER_Z, -1);
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
                extension::CCScale9Sprite* imageRendererScale9 = STATIC_CAST_SCALE9SPRITE;
                imageRendererScale9->initWithFile(fileName);
                imageRendererScale9->setCapInsets(_capInsets);
            }
            else
            {
                CCSprite* imageRenderer = STATIC_CAST_CCSPRITE;
                imageRenderer->initWithFile(fileName);
            }
            break;
        case UI_TEX_TYPE_PLIST:
            if (_scale9Enabled)
            {
                extension::CCScale9Sprite* imageRendererScale9 = STATIC_CAST_SCALE9SPRITE;
                imageRendererScale9->initWithSpriteFrameName(fileName);
                imageRendererScale9->setCapInsets(_capInsets);
            }
            else
            {
                CCSprite* imageRenderer = STATIC_CAST_CCSPRITE;
                imageRenderer->initWithSpriteFrameName(fileName);
            }
            break;
        default:
            break;
    }
    _imageTextureSize = _imageRenderer->getContentSize();
    imageTextureScaleChangedWithSize();
    updateAnchorPoint();
    updateFlippedX();
    updateFlippedY();
    updateRGBAToRenderer(_imageRenderer);
}

void ImageView::setTextureRect(const CCRect &rect)
{
    if (_scale9Enabled)
    {
    }
    else
    {
        STATIC_CAST_CCSPRITE->setTextureRect(rect);
    }
}
    
void ImageView::updateFlippedX()
{
    if (_scale9Enabled)
    {
        int flip = _flippedX ? -1 : 1;
        STATIC_CAST_SCALE9SPRITE->setScaleX(flip);
    }
    else
    {
        STATIC_CAST_CCSPRITE->setFlipX(_flippedX);
    }
}
    
void ImageView::updateFlippedY()
{
    if (_scale9Enabled)
    {
        int flip = _flippedY ? -1 : 1;
        STATIC_CAST_SCALE9SPRITE->setScaleY(flip);
    }
    else
    {
        STATIC_CAST_CCSPRITE->setFlipY(_flippedY);
    }
}

void ImageView::setScale9Enabled(bool able)
{
    if (_scale9Enabled == able)
    {
        return;
    }
    
    
    _scale9Enabled = able;
    CCNode::removeChild(_imageRenderer, true);
    _imageRenderer = NULL;
    if (_scale9Enabled)
    {
        _imageRenderer = extension::CCScale9Sprite::create();
    }
    else
    {
        _imageRenderer = CCSprite::create();
    }
    loadTexture(_textureFile.c_str(),_imageTexType);
    CCNode::addChild(_imageRenderer, IMAGE_RENDERER_Z, -1);
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
    
bool ImageView::isScale9Enabled()
{
    return _scale9Enabled;
}

void ImageView::ignoreContentAdaptWithSize(bool ignore)
{
    if (!_scale9Enabled || (_scale9Enabled && !ignore))
    {
        Widget::ignoreContentAdaptWithSize(ignore);
        _prevIgnoreSize = ignore;
    }
}

void ImageView::setCapInsets(const CCRect &capInsets)
{
    _capInsets = capInsets;
    if (!_scale9Enabled)
    {
        return;
    }
    STATIC_CAST_SCALE9SPRITE->setCapInsets(capInsets);
}
    
const CCRect& ImageView::getCapInsets()
{
    return _capInsets;
}

void ImageView::setAnchorPoint(const CCPoint &pt)
{
    Widget::setAnchorPoint(pt);
    _imageRenderer->setAnchorPoint(pt);
}

void ImageView::onSizeChanged()
{
    Widget::onSizeChanged();
    imageTextureScaleChangedWithSize();
}

const CCSize& ImageView::getContentSize() const
{
    return _imageTextureSize;
}

CCNode* ImageView::getVirtualRenderer()
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
            static_cast<extension::CCScale9Sprite*>(_imageRenderer)->setPreferredSize(_size);
        }
        else
        {
            CCSize textureSize = _imageRenderer->getContentSize();
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
    
void ImageView::updateTextureColor()
{
    updateColorToRenderer(_imageRenderer);
}

void ImageView::updateTextureOpacity()
{
    updateOpacityToRenderer(_imageRenderer);
}

void ImageView::updateTextureRGBA()
{
    updateRGBAToRenderer(_imageRenderer);
}

std::string ImageView::getDescription() const
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