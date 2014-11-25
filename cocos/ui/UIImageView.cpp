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
#include "ui/UIScale9Sprite.h"
#include "2d/CCSprite.h"

NS_CC_BEGIN

namespace ui {
    
static const int IMAGE_RENDERER_Z = (-1);
    
IMPLEMENT_CLASS_GUI_INFO(ImageView)

ImageView::ImageView():
_scale9Enabled(false),
_prevIgnoreSize(true),
_capInsets(Rect::ZERO),
_imageRenderer(nullptr),
_textureFile(""),
_imageTexType(TextureResType::LOCAL),
_imageTextureSize(_contentSize),
_imageRendererAdaptDirty(true)
{

}

ImageView::~ImageView()
{
    
}
    
ImageView* ImageView::create(const std::string &imageFileName, TextureResType texType)
{
    ImageView *widget = new (std::nothrow) ImageView;
    if (widget && widget->init(imageFileName, texType)) {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

ImageView* ImageView::create()
{
    ImageView* widget = new (std::nothrow) ImageView();
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
    _imageRenderer = Scale9Sprite::create();
    _imageRenderer->setScale9Enabled(false);
    
    addProtectedChild(_imageRenderer, IMAGE_RENDERER_Z, -1);
}

void ImageView::loadTexture(const std::string& fileName, TextureResType texType)
{
    if (fileName.empty() || (_textureFile == fileName && _imageTexType == texType))
    {
        return;
    }
    _textureFile = fileName;
    _imageTexType = texType;
    switch (_imageTexType)
    {
        case TextureResType::LOCAL:
            _imageRenderer->initWithFile(fileName);
            break;
        case TextureResType::PLIST:
            _imageRenderer->initWithSpriteFrameName(fileName);
            break;
        default:
            break;
    }
    
    _imageTextureSize = _imageRenderer->getContentSize();
  
    this->updateChildrenDisplayedRGBA();

    updateContentSizeWithTextureSize(_imageTextureSize);
    _imageRendererAdaptDirty = true;
}

void ImageView::setTextureRect(const Rect &rect)
{
    //This API should be refactor
    if (_scale9Enabled)
    {
    }
    else
    {
        auto sprite = _imageRenderer->getSprite();
        if (sprite)
        {
            sprite->setTextureRect(rect);
        }
        else
        {
            CCLOG("Warning!! you should load texture before set the texture's rect!");
        }
    }
}
    
void ImageView::setScale9Enabled(bool able)
{
    if (_scale9Enabled == able)
    {
        return;
    }
    
    
    _scale9Enabled = able;
    _imageRenderer->setScale9Enabled(_scale9Enabled);
    
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
    
bool ImageView::isScale9Enabled()const
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
    _imageRenderer->setCapInsets(capInsets);
}

const Rect& ImageView::getCapInsets()const
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

Size ImageView::getVirtualRendererSize() const
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
            _imageRenderer->setPreferredSize(_contentSize);
        }
        else
        {
            Size textureSize = _imageRenderer->getContentSize();
            if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
            {
                _imageRenderer->setScale(1.0f);
                return;
            }
            float scaleX = _contentSize.width / textureSize.width;
            float scaleY = _contentSize.height / textureSize.height;
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
