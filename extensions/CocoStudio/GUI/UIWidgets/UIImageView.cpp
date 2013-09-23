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

NS_CC_EXT_BEGIN

#define DYNAMIC_CAST_CCSPRITE dynamic_cast<cocos2d::Sprite*>(_imageRenderer)
#define DYNAMIC_CAST_SCALE9SPRITE dynamic_cast<cocos2d::extension::Scale9Sprite*>(_imageRenderer)

UIImageView::UIImageView():
_clickCount(0),
_clickTimeInterval(0.0),
_startCheckDoubleClick(false),
_touchRelease(false),
_doubleClickEnabled(false),
_scale9Enabled(false),
_prevIgnoreSize(true),
_capInsets(Rect::ZERO),
_imageRenderer(NULL),
_textureFile(""),
_imageTexType(UI_TEX_TYPE_LOCAL),
_imageTextureSize(_size)
{

}

UIImageView::~UIImageView()
{
    
}

UIImageView* UIImageView::create()
{
    UIImageView* widget = new UIImageView();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

void UIImageView::initRenderer()
{
    UIWidget::initRenderer();
    _imageRenderer = Sprite::create();
    _renderer->addChild(_imageRenderer);
}

void UIImageView::loadTexture(const char *fileName, TextureResType texType)
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
            }
            else
            {
                DYNAMIC_CAST_CCSPRITE->initWithFile(fileName);
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
            }
            else
            {
                DYNAMIC_CAST_CCSPRITE->initWithSpriteFrameName(fileName);
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

void UIImageView::setTextureRect(const Rect &rect)
{
    if (_scale9Enabled)
    {
    }
    else
    {
        DYNAMIC_CAST_CCSPRITE->setTextureRect(rect);
    }
}

bool UIImageView::onTouchBegan(const Point &touchPoint)
{
    setFocused(true);
    _touchStartPos.x = touchPoint.x;
    _touchStartPos.y = touchPoint.y;
    _widgetParent->checkChildInfo(0,this,touchPoint);
    pushDownEvent();
    
    if (_doubleClickEnabled)
    {
        _clickTimeInterval = 0;
        _startCheckDoubleClick = true;
        _clickCount++;
        _touchRelease = false;
    }
    return _touchPassedEnabled;
}

void UIImageView::onTouchEnded(const Point &touchPoint)
{
    if (_doubleClickEnabled)
    {
        if (_clickCount >= 2)
        {
            doubleClickEvent();
            _clickCount = 0;
            _startCheckDoubleClick = false;
        }
        else
        {
            _touchRelease = true;
        }
    }
    else
    {
        UIWidget::onTouchEnded(touchPoint);
    }
}

void UIImageView::doubleClickEvent()
{
    
}

void UIImageView::checkDoubleClick(float dt)
{
    if (_startCheckDoubleClick)
    {
        _clickTimeInterval += dt;
        if (_clickTimeInterval >= 200 && _clickCount > 0)
        {
            _clickTimeInterval = 0;
            _clickCount--;
            _startCheckDoubleClick = false;
        }
    }
    else
    {
        if (_clickCount <= 1)
        {
            if (_touchRelease)
            {
                releaseUpEvent();
                _clickTimeInterval = 0;
                _clickCount = 0;
                _touchRelease = false;
            }
        }
    }
}

void UIImageView::setDoubleClickEnabled(bool able)
{
    if (able == _doubleClickEnabled)
    {
        return;
    }
    _doubleClickEnabled = able;
    if (able)
    {
//        COCOUISYSTEM->getUIInputManager()->addCheckedDoubleClickWidget(this);
    }
    else
    {
        
    }
}

void UIImageView::setFlipX(bool flipX)
{
    if (_scale9Enabled)
    {
    }
    else
    {
        DYNAMIC_CAST_CCSPRITE->setFlippedX(flipX);
    }
}

void UIImageView::setFlipY(bool flipY)
{
    if (_scale9Enabled)
    {
    }
    else
    {
        DYNAMIC_CAST_CCSPRITE->setFlippedY(flipY);
    }
}

bool UIImageView::isFlipX()
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

bool UIImageView::isFlipY()
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

void UIImageView::setScale9Enabled(bool able)
{
    if (_scale9Enabled == able)
    {
        return;
    }
    
    
    _scale9Enabled = able;
    _renderer->removeChild(_imageRenderer, true);
    _imageRenderer = NULL;
    if (_scale9Enabled)
    {
        _imageRenderer = extension::Scale9Sprite::create();
    }
    else
    {
        _imageRenderer = CCSprite::create();
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

void UIImageView::ignoreContentAdaptWithSize(bool ignore)
{
    if (!_scale9Enabled || (_scale9Enabled && !ignore))
    {
        UIWidget::ignoreContentAdaptWithSize(ignore);
        _prevIgnoreSize = ignore;
    }
}

void UIImageView::setCapInsets(const Rect &capInsets)
{
    _capInsets = capInsets;
    if (!_scale9Enabled)
    {
        return;
    }
    DYNAMIC_CAST_SCALE9SPRITE->setCapInsets(capInsets);
}

void UIImageView::setAnchorPoint(const Point &pt)
{
    UIWidget::setAnchorPoint(pt);
    _imageRenderer->setAnchorPoint(pt);
}

void UIImageView::onSizeChanged()
{
    imageTextureScaleChangedWithSize();
}

const Size& UIImageView::getContentSize() const
{
    return _imageTextureSize;
}

Node* UIImageView::getVirtualRenderer()
{
    return _imageRenderer;
}

void UIImageView::imageTextureScaleChangedWithSize()
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
            dynamic_cast<Scale9Sprite*>(_imageRenderer)->setPreferredSize(_size);
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

const char* UIImageView::getDescription() const
{
    return "ImageView";
}

NS_CC_EXT_END