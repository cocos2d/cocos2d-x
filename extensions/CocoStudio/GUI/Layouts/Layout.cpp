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
m_bClippingEnabled(false),
m_pLayoutExecutant(NULL),
m_bBackGroundScale9Enable(false),
m_pBackGroundImage(NULL),
m_strBackGroundImageFileName(""),
m_backGroundImageCapInsets(Rect::ZERO),
m_colorType(LAYOUT_COLOR_NONE),
m_eBGImageTexType(UI_TEX_TYPE_LOCAL),
m_pColorRender(NULL),
m_pGradientRender(NULL),
m_cColor(Color3B::WHITE),
m_gStartColor(Color3B::WHITE),
m_gEndColor(Color3B::WHITE),
m_AlongVector(Point(0.0f, -1.0f)),
m_nCOpacity(255),
m_backGroundImageTextureSize(Size::ZERO)
{
    _widgetType = WidgetTypeContainer;
}

Layout::~Layout()
{
    CC_SAFE_RELEASE_NULL(m_pLayoutExecutant);
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
    if (m_pLayoutExecutant)
    {
        CC_SAFE_RELEASE_NULL(m_pLayoutExecutant);
    }
    m_pLayoutExecutant = exe;
    m_pLayoutExecutant->setLayout(this);
    CC_SAFE_RETAIN(m_pLayoutExecutant);
}

LayoutExecutant* Layout::getLayoutExecutant() const
{
    return m_pLayoutExecutant;
}

void Layout::initRenderer()
{
    _renderer = RectClippingNode::create();
}

bool Layout::isClippingEnabled()
{
    return m_bClippingEnabled;
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
    m_bClippingEnabled = able;
    DYNAMIC_CAST_CLIPPINGLAYER->setClippingEnabled(able);
}

void Layout::onSizeChanged()
{
    DYNAMIC_CAST_CLIPPINGLAYER->setClippingSize(_size);
    if (m_pLayoutExecutant)
    {
        m_pLayoutExecutant->doLayout();
    }
    if (m_pBackGroundImage)
    {
        m_pBackGroundImage->setPosition(Point(_size.width/2.0f, _size.height/2.0f));
        if (m_bBackGroundScale9Enable)
        {
            dynamic_cast<Scale9Sprite*>(m_pBackGroundImage)->setPreferredSize(_size);
        }
    }
    if (m_pColorRender)
    {
        m_pColorRender->setContentSize(_size);
    }
    if (m_pGradientRender)
    {
        m_pGradientRender->setContentSize(_size);
    }
}

void Layout::setBackGroundImageScale9Enabled(bool able)
{
    if (m_bBackGroundScale9Enable == able)
    {
        return;
    }
    _renderer->removeChild(m_pBackGroundImage, true);
    m_pBackGroundImage = NULL;
    m_bBackGroundScale9Enable = able;
    if (m_bBackGroundScale9Enable)
    {
        m_pBackGroundImage = Scale9Sprite::create();
        _renderer->addChild(m_pBackGroundImage);
    }
    else
    {
        m_pBackGroundImage = CCSprite::create();
        _renderer->addChild(m_pBackGroundImage);
    }
    m_pBackGroundImage->setZOrder(-1);
    setBackGroundImage(m_strBackGroundImageFileName.c_str(),m_eBGImageTexType);    
    setBackGroundImageCapInsets(m_backGroundImageCapInsets);
}

void Layout::setBackGroundImage(const char* fileName,TextureResType texType)
{
    if (!fileName || strcmp(fileName, "") == 0)
    {
        return;
    }
    if (m_pBackGroundImage == NULL)
    {
        addBackGroundImage();
    }
    m_strBackGroundImageFileName = fileName;
    m_eBGImageTexType = texType;
    if (m_bBackGroundScale9Enable)
    {
        switch (m_eBGImageTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<Scale9Sprite*>(m_pBackGroundImage)->initWithFile(fileName);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<Scale9Sprite*>(m_pBackGroundImage)->initWithSpriteFrameName(fileName);
                break;
            default:
                break;
        }
        dynamic_cast<Scale9Sprite*>(m_pBackGroundImage)->setPreferredSize(_size);
    }
    else
    {
        switch (m_eBGImageTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<Sprite*>(m_pBackGroundImage)->initWithFile(fileName);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<Sprite*>(m_pBackGroundImage)->initWithSpriteFrameName(fileName);
                break;
            default:
                break;
        }
    }
    if (m_bBackGroundScale9Enable)
    {
        dynamic_cast<Scale9Sprite*>(m_pBackGroundImage)->setColor(getColor());
        dynamic_cast<Scale9Sprite*>(m_pBackGroundImage)->setOpacity(getOpacity());
    }
    else
    {
        dynamic_cast<Sprite*>(m_pBackGroundImage)->setColor(getColor());
        dynamic_cast<Sprite*>(m_pBackGroundImage)->setOpacity(getOpacity());
    }
    m_backGroundImageTextureSize = m_pBackGroundImage->getContentSize();
    m_pBackGroundImage->setPosition(Point(_size.width/2.0f, _size.height/2.0f));
}

void Layout::setBackGroundImageCapInsets(const Rect &capInsets)
{
    m_backGroundImageCapInsets = capInsets;
    if (m_bBackGroundScale9Enable)
    {
        dynamic_cast<Scale9Sprite*>(m_pBackGroundImage)->setCapInsets(capInsets);
    }
}

void Layout::addBackGroundImage()
{
    if (m_bBackGroundScale9Enable)
    {
        m_pBackGroundImage = Scale9Sprite::create();
        m_pBackGroundImage->setZOrder(-1);
        _renderer->addChild(m_pBackGroundImage);
        dynamic_cast<Scale9Sprite*>(m_pBackGroundImage)->setPreferredSize(_size);
    }
    else
    {
        m_pBackGroundImage = CCSprite::create();
        m_pBackGroundImage->setZOrder(-1);
        _renderer->addChild(m_pBackGroundImage);
    }
    m_pBackGroundImage->setPosition(Point(_size.width/2.0f, _size.height/2.0f));
}

void Layout::removeBackGroundImage()
{
    if (!m_pBackGroundImage)
    {
        return;
    }
    _renderer->removeChild(m_pBackGroundImage,  true);
    m_pBackGroundImage = NULL;
    m_strBackGroundImageFileName = "";
    m_backGroundImageTextureSize = Size::ZERO;
}

void Layout::setBackGroundColorType(LayoutBackGroundColorType type)
{
    if (m_colorType == type)
    {
        return;
    }
    switch (m_colorType)
    {
        case LAYOUT_COLOR_NONE:
            if (m_pColorRender)
            {
                _renderer->removeChild(m_pColorRender, true);
                m_pColorRender = NULL;
            }
            if (m_pGradientRender)
            {
                _renderer->removeChild(m_pGradientRender, true);
                m_pGradientRender = NULL;
            }
            break;
        case LAYOUT_COLOR_SOLID:
            if (m_pColorRender)
            {
                _renderer->removeChild(m_pColorRender, true);
                m_pColorRender = NULL;
            }
            break;
        case LAYOUT_COLOR_GRADIENT:
            if (m_pGradientRender)
            {
                _renderer->removeChild(m_pGradientRender, true);
                m_pGradientRender = NULL;
            }
            break;
        default:
            break;
    }
    m_colorType = type;
    switch (m_colorType)
    {
        case LAYOUT_COLOR_NONE:
            break;
        case LAYOUT_COLOR_SOLID:
            m_pColorRender = CCLayerColor::create();
            m_pColorRender->setContentSize(_size);
            m_pColorRender->setOpacity(m_nCOpacity);
            m_pColorRender->setColor(m_cColor);
            _renderer->addChild(m_pColorRender,-2);
            break;
        case LAYOUT_COLOR_GRADIENT:
            m_pGradientRender = CCLayerGradient::create();
            m_pGradientRender->setContentSize(_size);
            m_pGradientRender->setOpacity(m_nCOpacity);
            m_pGradientRender->setStartColor(m_gStartColor);
            m_pGradientRender->setEndColor(m_gEndColor);
            m_pGradientRender->setVector(m_AlongVector);
            _renderer->addChild(m_pGradientRender,-2);
            break;
        default:
            break;
    }
}

void Layout::setBackGroundColor(const Color3B &color)
{
    m_cColor = color;
    if (m_pColorRender)
    {
        m_pColorRender->setColor(color);
    }
}

void Layout::setBackGroundColor(const Color3B &startColor, const Color3B &endColor)
{
    m_gStartColor = startColor;
    if (m_pGradientRender)
    {
        m_pGradientRender->setStartColor(startColor);
    }
    m_gEndColor = endColor;
    if (m_pGradientRender)
    {
        m_pGradientRender->setEndColor(endColor);
    }
}

void Layout::setBackGroundColorOpacity(int opacity)
{
    m_nCOpacity = opacity;
    switch (m_colorType)
    {
        case LAYOUT_COLOR_NONE:
            break;
        case LAYOUT_COLOR_SOLID:
            m_pColorRender->setOpacity(opacity);
            break;
        case LAYOUT_COLOR_GRADIENT:
            m_pGradientRender->setOpacity(opacity);
            break;
        default:
            break;
    }
}

void Layout::setBackGroundColorVector(const Point &vector)
{
    m_AlongVector = vector;
    if (m_pGradientRender)
    {
        m_pGradientRender->setVector(vector);
    }
}

void Layout::setColor(const Color3B &color)
{
    UIWidget::setColor(color);
    if (m_pBackGroundImage)
    {
        RGBAProtocol* rgbap = dynamic_cast<RGBAProtocol*>(m_pBackGroundImage);
        if (rgbap)
        {
            rgbap->setColor(color);
        }
    }
}

void Layout::setOpacity(int opacity)
{
    UIWidget::setOpacity(opacity);
    if (m_pBackGroundImage)
    {
        RGBAProtocol* rgbap = dynamic_cast<RGBAProtocol*>(m_pBackGroundImage);
        if (rgbap)
        {
            rgbap->setOpacity(opacity);
        }
    }
}

const Size& Layout::getBackGroundImageTextureSize() const
{
    return m_backGroundImageTextureSize;
}

const Size& Layout::getContentSize() const
{
    return _renderer->getContentSize();
}

RectClippingNode::RectClippingNode():
m_pInnerStencil(NULL),
m_bEnabled(true),
m_clippingSize(Size(50.0f, 50.0f)),
m_bClippingEnabled(false)
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
    rect[1] = Point(m_clippingSize.width, 0);
    rect[2] = Point(m_clippingSize.width, m_clippingSize.height);
    rect[3] = Point(0, m_clippingSize.height);
    
    Color4F green = Color4F(0, 1, 0, 1);
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
    m_clippingSize = size;
    rect[0] = Point(0, 0);
    rect[1] = Point(m_clippingSize.width, 0);
    rect[2] = Point(m_clippingSize.width, m_clippingSize.height);
    rect[3] = Point(0, m_clippingSize.height);
    Color4F green = Color4F(0, 1, 0, 1);
    m_pInnerStencil->clear();
    m_pInnerStencil->drawPolygon(rect, 4, green, 0, green);
}

void RectClippingNode::setClippingEnabled(bool enabled)
{
    m_bClippingEnabled = enabled;
}

void RectClippingNode::visit()
{
    if (!m_bEnabled)
    {
        return;
    }
    if (m_bClippingEnabled)
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
    m_bEnabled = enabled;
}

bool RectClippingNode::isEnabled() const
{
    return m_bEnabled;
}

NS_CC_EXT_END