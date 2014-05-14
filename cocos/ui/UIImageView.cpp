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

#include "ui/UIImageView.h"
#include "extensions/GUI/CCControlExtension/CCScale9Sprite.h"

NS_CC_BEGIN

namespace ui {


#define STATIC_CAST_CCSPRITE static_cast<Sprite*>(_imageRenderer)
#define STATIC_CAST_SCALE9SPRITE static_cast<extension::Scale9Sprite*>(_imageRenderer)
    
static const int IMAGE_RENDERER_Z = (-1);
    
IMPLEMENT_CLASS_GUI_INFO(ImageView)

ImageView::ImageView():
_scale9Enabled(false),
_prevIgnoreSize(true),
_capInsets(Rect::ZERO),
_imageRenderer(nullptr),
_textureFile(""),
_imageTexType(TextureResType::LOCAL),
_imageTextureSize(_size),
_imageRendererAdaptDirty(true)
{

}

ImageView::~ImageView()
{
    
}
    
ImageView* ImageView::create(const std::string &imageFileName, TextureResType texType)
{
    ImageView *widget = new ImageView;
    if (widget && widget->init(imageFileName, texType)) {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
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
    
bool ImageView::init()
{
    bool ret = true;
    do {
        if (!Widget::init()) {
            ret = false;
            break;
        }
        _imageTexType = TextureResType::LOCAL;
    } while (0);
    return ret;
}
    
bool ImageView::init(const std::string &imageFileName, TextureResType texType)
{
    bool bRet = true;
    do {
        if (!Widget::init()) {
            bRet = false;
            break;
        }
        
        this->loadTexture(imageFileName, texType);
    } while (0);
    return bRet;
}

void ImageView::initRenderer()
{
    _imageRenderer = Sprite::create();
    addProtectedChild(_imageRenderer, IMAGE_RENDERER_Z, -1);
}

void ImageView::loadTexture(const std::string& fileName, TextureResType texType)
{
    if (fileName.empty())
    {
        return;
    }
    _textureFile = fileName;
    _imageTexType = texType;
    switch (_imageTexType)
    {
        case TextureResType::LOCAL:
            if (_scale9Enabled)
            {
                extension::Scale9Sprite* imageRendererScale9 = STATIC_CAST_SCALE9SPRITE;
                imageRendererScale9->initWithFile(fileName);
                imageRendererScale9->setCapInsets(_capInsets);
            }
            else
            {
                Sprite* imageRenderer = STATIC_CAST_CCSPRITE;
                imageRenderer->setTexture(fileName);
            }
            break;
        case TextureResType::PLIST:
            if (_scale9Enabled)
            {
                extension::Scale9Sprite* imageRendererScale9 = STATIC_CAST_SCALE9SPRITE;
                imageRendererScale9->initWithSpriteFrameName(fileName);
                imageRendererScale9->setCapInsets(_capInsets);
            }
            else
            {
                Sprite* imageRenderer = STATIC_CAST_CCSPRITE;
                imageRenderer->setSpriteFrame(fileName);
            }
            break;
        default:
            break;
    }
    _imageTextureSize = _imageRenderer->getContentSize();
    updateFlippedX();
    updateFlippedY();
    updateRGBAToRenderer(_imageRenderer);
    updateContentSizeWithTextureSize(_imageTextureSize);
    _imageRendererAdaptDirty = true;
}

void ImageView::setTextureRect(const Rect &rect)
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
        STATIC_CAST_CCSPRITE->setFlippedX(_flippedX);
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
        STATIC_CAST_CCSPRITE->setFlippedY(_flippedY);
    }

}

void ImageView::setScale9Enabled(bool able)
{
    if (_scale9Enabled == able)
    {
        return;
    }
    
    
    _scale9Enabled = able;
    removeProtectedChild(_imageRenderer);
    _imageRenderer = nullptr;
    if (_scale9Enabled)
    {
        _imageRenderer = extension::Scale9Sprite::create();
    }
    else
    {
        _imageRenderer = Sprite::create();
    }
    loadTexture(_textureFile,_imageTexType);
    addProtectedChild(_imageRenderer, IMAGE_RENDERER_Z, -1);
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

void ImageView::setCapInsets(const Rect &capInsets)
{
    _capInsets = capInsets;
    if (!_scale9Enabled)
    {
        return;
    }
    STATIC_CAST_SCALE9SPRITE->setCapInsets(capInsets);
}

const Rect& ImageView::getCapInsets()
{
    return _capInsets;
}

void ImageView::onSizeChanged()
{
    Widget::onSizeChanged();
    _imageRendererAdaptDirty = true;
}
    
void ImageView::adaptRenderers()
{
    if (_imageRendererAdaptDirty)
    {
        imageTextureScaleChangedWithSize();
        _imageRendererAdaptDirty = false;
    }
}

const Size& ImageView::getVirtualRendererSize() const
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
        }
    }
    else
    {
        if (_scale9Enabled)
        {
            static_cast<extension::Scale9Sprite*>(_imageRenderer)->setPreferredSize(_size);
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
    _imageRenderer->setPosition(_contentSize.width / 2.0f, _contentSize.height / 2.0f);
}

std::string ImageView::getDescription() const
{
    return "ImageView";
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
        loadTexture(imageView->_textureFile, imageView->_imageTexType);
        setCapInsets(imageView->_capInsets);
    }
}

}

NS_CC_END
