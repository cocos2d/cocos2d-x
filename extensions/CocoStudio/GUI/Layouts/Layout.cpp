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

#include "Layout.h"
#include "../System/UILayer.h"
#include "../../../GUI/CCControlExtension/CCScale9Sprite.h"

NS_CC_EXT_BEGIN

#define DYNAMIC_CAST_CLIPPINGLAYER dynamic_cast<RectClippingNode*>(_renderer)

Layout::Layout():
_clippingEnabled(false),
_layoutExecutant(NULL),
_backGroundScale9Enabled(false),
_backGroundImage(NULL),
_backGroundImageFileName(""),
_backGroundImageCapInsets(Rect::ZERO),
_colorType(LAYOUT_COLOR_NONE),
_bgImageTexType(UI_TEX_TYPE_LOCAL),
_colorRender(NULL),
_gradientRender(NULL),
_cColor(Color3B::WHITE),
_gStartColor(Color3B::WHITE),
_gEndColor(Color3B::WHITE),
_alongVector(Point(0.0f, -1.0f)),
_cOpacity(255),
_backGroundImageTextureSize(Size::ZERO)
{
    _widgetType = WidgetTypeContainer;
}

Layout::~Layout()
{
    CC_SAFE_RELEASE_NULL(_layoutExecutant);
}

Layout* Layout::create()
{
    Layout* layout = new Layout();
    if (layout && layout->init())
    {
        layout->autorelease();
        return layout;
    }
    CC_SAFE_DELETE(layout);
    return NULL;
}

bool Layout::init()
{
    _children = CCArray::create();
    _children->retain();
    initRenderer();
    _renderer->retain();
    _renderer->setZOrder(_widgetZOrder);
    RGBAProtocol* renderRGBA = dynamic_cast<RGBAProtocol*>(_renderer);
    if (renderRGBA)
    {
        renderRGBA->setCascadeColorEnabled(false);
        renderRGBA->setCascadeOpacityEnabled(false);
    }
    ignoreContentAdaptWithSize(false);
    setSize(Size::ZERO);
    setBright(true);
    setAnchorPoint(Point(0, 0));
    _scheduler = Director::getInstance()->getScheduler();
    CC_SAFE_RETAIN(_scheduler);
    return true;
}

void Layout::setLayoutExecutant(LayoutExecutant *exe)
{
    if (_layoutExecutant)
    {
        CC_SAFE_RELEASE_NULL(_layoutExecutant);
    }
    _layoutExecutant = exe;
    _layoutExecutant->setLayout(this);
    CC_SAFE_RETAIN(_layoutExecutant);
}

LayoutExecutant* Layout::getLayoutExecutant() const
{
    return _layoutExecutant;
}

void Layout::initRenderer()
{
    _renderer = RectClippingNode::create();
}

bool Layout::isClippingEnabled()
{
    return _clippingEnabled;
}

bool Layout::hitTest(const Point &pt)
{
    Point nsp = _renderer->convertToNodeSpace(pt);
    Rect bb = Rect(0.0f, 0.0f, _size.width, _size.height);
    if (nsp.x >= bb.origin.x && nsp.x <= bb.origin.x + bb.size.width && nsp.y >= bb.origin.y && nsp.y <= bb.origin.y + bb.size.height)
    {
        return true;
    }
    return false;
}

void Layout::setClippingEnabled(bool able)
{
    _clippingEnabled = able;
    DYNAMIC_CAST_CLIPPINGLAYER->setClippingEnabled(able);
}

void Layout::onSizeChanged()
{
    DYNAMIC_CAST_CLIPPINGLAYER->setClippingSize(_size);
    if (_layoutExecutant)
    {
        _layoutExecutant->doLayout();
    }
    if (_backGroundImage)
    {
        _backGroundImage->setPosition(Point(_size.width/2.0f, _size.height/2.0f));
        if (_backGroundScale9Enabled)
        {
            dynamic_cast<Scale9Sprite*>(_backGroundImage)->setPreferredSize(_size);
        }
    }
    if (_colorRender)
    {
        _colorRender->setContentSize(_size);
    }
    if (_gradientRender)
    {
        _gradientRender->setContentSize(_size);
    }
}

void Layout::setBackGroundImageScale9Enabled(bool able)
{
    if (_backGroundScale9Enabled == able)
    {
        return;
    }
    _renderer->removeChild(_backGroundImage, true);
    _backGroundImage = NULL;
    _backGroundScale9Enabled = able;
    if (_backGroundScale9Enabled)
    {
        _backGroundImage = Scale9Sprite::create();
        _renderer->addChild(_backGroundImage);
    }
    else
    {
        _backGroundImage = Sprite::create();
        _renderer->addChild(_backGroundImage);
    }
    _backGroundImage->setZOrder(-1);
    setBackGroundImage(_backGroundImageFileName.c_str(),_bgImageTexType);
    setBackGroundImageCapInsets(_backGroundImageCapInsets);
}

void Layout::setBackGroundImage(const char* fileName,TextureResType texType)
{
    if (!fileName || strcmp(fileName, "") == 0)
    {
        return;
    }
    if (_backGroundImage == NULL)
    {
        addBackGroundImage();
    }
    _backGroundImageFileName = fileName;
    _bgImageTexType = texType;
    if (_backGroundScale9Enabled)
    {
        switch (_bgImageTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<Scale9Sprite*>(_backGroundImage)->initWithFile(fileName);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<Scale9Sprite*>(_backGroundImage)->initWithSpriteFrameName(fileName);
                break;
            default:
                break;
        }
        dynamic_cast<Scale9Sprite*>(_backGroundImage)->setPreferredSize(_size);
    }
    else
    {
        switch (_bgImageTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<Sprite*>(_backGroundImage)->initWithFile(fileName);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<Sprite*>(_backGroundImage)->initWithSpriteFrameName(fileName);
                break;
            default:
                break;
        }
    }
    if (_backGroundScale9Enabled)
    {
        dynamic_cast<Scale9Sprite*>(_backGroundImage)->setColor(getColor());
        dynamic_cast<Scale9Sprite*>(_backGroundImage)->setOpacity(getOpacity());
    }
    else
    {
        dynamic_cast<Sprite*>(_backGroundImage)->setColor(getColor());
        dynamic_cast<Sprite*>(_backGroundImage)->setOpacity(getOpacity());
    }
    _backGroundImageTextureSize = _backGroundImage->getContentSize();
    _backGroundImage->setPosition(Point(_size.width/2.0f, _size.height/2.0f));
}

void Layout::setBackGroundImageCapInsets(const Rect &capInsets)
{
    _backGroundImageCapInsets = capInsets;
    if (_backGroundScale9Enabled)
    {
        dynamic_cast<Scale9Sprite*>(_backGroundImage)->setCapInsets(capInsets);
    }
}

void Layout::addBackGroundImage()
{
    if (_backGroundScale9Enabled)
    {
        _backGroundImage = Scale9Sprite::create();
        _backGroundImage->setZOrder(-1);
        _renderer->addChild(_backGroundImage);
        dynamic_cast<Scale9Sprite*>(_backGroundImage)->setPreferredSize(_size);
    }
    else
    {
        _backGroundImage = CCSprite::create();
        _backGroundImage->setZOrder(-1);
        _renderer->addChild(_backGroundImage);
    }
    _backGroundImage->setPosition(Point(_size.width/2.0f, _size.height/2.0f));
}

void Layout::removeBackGroundImage()
{
    if (!_backGroundImage)
    {
        return;
    }
    _renderer->removeChild(_backGroundImage,  true);
    _backGroundImage = NULL;
    _backGroundImageFileName = "";
    _backGroundImageTextureSize = Size::ZERO;
}

void Layout::setBackGroundColorType(LayoutBackGroundColorType type)
{
    if (_colorType == type)
    {
        return;
    }
    switch (_colorType)
    {
        case LAYOUT_COLOR_NONE:
            if (_colorRender)
            {
                _renderer->removeChild(_colorRender, true);
                _colorRender = NULL;
            }
            if (_gradientRender)
            {
                _renderer->removeChild(_gradientRender, true);
                _gradientRender = NULL;
            }
            break;
        case LAYOUT_COLOR_SOLID:
            if (_colorRender)
            {
                _renderer->removeChild(_colorRender, true);
                _colorRender = NULL;
            }
            break;
        case LAYOUT_COLOR_GRADIENT:
            if (_gradientRender)
            {
                _renderer->removeChild(_gradientRender, true);
                _gradientRender = NULL;
            }
            break;
        default:
            break;
    }
    _colorType = type;
    switch (_colorType)
    {
        case LAYOUT_COLOR_NONE:
            break;
        case LAYOUT_COLOR_SOLID:
            _colorRender = CCLayerColor::create();
            _colorRender->setContentSize(_size);
            _colorRender->setOpacity(_cOpacity);
            _colorRender->setColor(_cColor);
            _renderer->addChild(_colorRender,-2);
            break;
        case LAYOUT_COLOR_GRADIENT:
            _gradientRender = CCLayerGradient::create();
            _gradientRender->setContentSize(_size);
            _gradientRender->setOpacity(_cOpacity);
            _gradientRender->setStartColor(_gStartColor);
            _gradientRender->setEndColor(_gEndColor);
            _gradientRender->setVector(_alongVector);
            _renderer->addChild(_gradientRender,-2);
            break;
        default:
            break;
    }
}

void Layout::setBackGroundColor(const Color3B &color)
{
    _cColor = color;
    if (_colorRender)
    {
        _colorRender->setColor(color);
    }
}

void Layout::setBackGroundColor(const Color3B &startColor, const Color3B &endColor)
{
    _gStartColor = startColor;
    if (_gradientRender)
    {
        _gradientRender->setStartColor(startColor);
    }
    _gEndColor = endColor;
    if (_gradientRender)
    {
        _gradientRender->setEndColor(endColor);
    }
}

void Layout::setBackGroundColorOpacity(int opacity)
{
    _cOpacity = opacity;
    switch (_colorType)
    {
        case LAYOUT_COLOR_NONE:
            break;
        case LAYOUT_COLOR_SOLID:
            _colorRender->setOpacity(opacity);
            break;
        case LAYOUT_COLOR_GRADIENT:
            _gradientRender->setOpacity(opacity);
            break;
        default:
            break;
    }
}

void Layout::setBackGroundColorVector(const Point &vector)
{
    _alongVector = vector;
    if (_gradientRender)
    {
        _gradientRender->setVector(vector);
    }
}

void Layout::setColor(const Color3B &color)
{
    UIWidget::setColor(color);
    if (_backGroundImage)
    {
        RGBAProtocol* rgbap = dynamic_cast<RGBAProtocol*>(_backGroundImage);
        if (rgbap)
        {
            rgbap->setColor(color);
        }
    }
}

void Layout::setOpacity(int opacity)
{
    UIWidget::setOpacity(opacity);
    if (_backGroundImage)
    {
        RGBAProtocol* rgbap = dynamic_cast<RGBAProtocol*>(_backGroundImage);
        if (rgbap)
        {
            rgbap->setOpacity(opacity);
        }
    }
}

const Size& Layout::getBackGroundImageTextureSize() const
{
    return _backGroundImageTextureSize;
}

const Size& Layout::getContentSize() const
{
    return _renderer->getContentSize();
}

const char* Layout::getDescription() const
{
    return "Layout";
}

RectClippingNode::RectClippingNode():
m_pInnerStencil(NULL),
_enabled(true),
_clippingSize(Size(50.0f, 50.0f)),
_clippingEnabled(false)
{
    
}

RectClippingNode::~RectClippingNode()
{
    
}

RectClippingNode* RectClippingNode::create()
{
    RectClippingNode *pRet = new RectClippingNode();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

bool RectClippingNode::init()
{
    m_pInnerStencil = CCDrawNode::create();
    rect[0] = Point(0, 0);
    rect[1] = Point(_clippingSize.width, 0);
    rect[2] = Point(_clippingSize.width, _clippingSize.height);
    rect[3] = Point(0, _clippingSize.height);
    
    Color4F green(0, 1, 0, 1);
    m_pInnerStencil->drawPolygon(rect, 4, green, 0, green);
    if (CCClippingNode::init(m_pInnerStencil))
    {
        return true;
    }
    return false;
}


void RectClippingNode::setClippingSize(const Size &size)
{
    setContentSize(size);
    _clippingSize = size;
    rect[0] = Point(0, 0);
    rect[1] = Point(_clippingSize.width, 0);
    rect[2] = Point(_clippingSize.width, _clippingSize.height);
    rect[3] = Point(0, _clippingSize.height);
    Color4F green(0, 1, 0, 1);
    m_pInnerStencil->clear();
    m_pInnerStencil->drawPolygon(rect, 4, green, 0, green);
}

void RectClippingNode::setClippingEnabled(bool enabled)
{
    _clippingEnabled = enabled;
}

void RectClippingNode::visit()
{
    if (!_enabled)
    {
        return;
    }
    if (_clippingEnabled)
    {
        CCClippingNode::visit();
    }
    else
    {
        CCNode::visit();
    }
}

void RectClippingNode::setEnabled(bool enabled)
{
    _enabled = enabled;
}

bool RectClippingNode::isEnabled() const
{
    return _enabled;
}

NS_CC_EXT_END