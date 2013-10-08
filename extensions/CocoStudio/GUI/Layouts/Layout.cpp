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
#include "../System/UIHelper.h"
#include "../../../GUI/CCControlExtension/CCScale9Sprite.h"

NS_CC_EXT_BEGIN

#define DYNAMIC_CAST_CLIPPINGLAYER dynamic_cast<RectClippingNode*>(_renderer)

Layout::Layout():
_clippingEnabled(false),
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
_backGroundImageTextureSize(Size::ZERO),
_layoutType(LAYOUT_ABSOLUTE)
{
    _widgetType = WidgetTypeContainer;
}

Layout::~Layout()
{
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
    doLayout();
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

void Layout::setLayoutType(LayoutType type)
{
    _layoutType = type;
}

LayoutType Layout::getLayoutType() const
{
    return _layoutType;
}

void Layout::doLayout()
{
    switch (_layoutType)
    {
        case LAYOUT_ABSOLUTE:
            break;
        case LAYOUT_LINEAR_VERTICAL:
        {
            ccArray* layoutChildrenArray = getChildren()->data;
            int length = layoutChildrenArray->num;
            Size layoutSize = getSize();
            float topBoundary = layoutSize.height;
            for (int i=0; i<length; ++i)
            {
                UIWidget* child = dynamic_cast<UIWidget*>(layoutChildrenArray->arr[i]);
                LinearLayoutParameter* layoutParameter = dynamic_cast<LinearLayoutParameter*>(child->getLayoutParameter());
                
                if (layoutParameter)
                {
                    WidgetType childType = child->getWidgetType();
                    UILinearGravity childGravity = layoutParameter->getGravity();
                    Point ap = child->getAnchorPoint();
                    Size cs = child->getSize();
                    float finalPosX = childType == WidgetTypeWidget ? ap.x * cs.width : 0.0f;
                    float finalPosY = childType == WidgetTypeWidget ? topBoundary - ((1.0f-ap.y) * cs.height) : topBoundary - cs.height;
                    switch (childGravity)
                    {
                        case LINEAR_GRAVITY_NONE:
                        case LINEAR_GRAVITY_LEFT:
                            break;
                        case LINEAR_GRAVITY_RIGHT:
                            finalPosX = childType == WidgetTypeWidget ? layoutSize.width - ((1.0f - ap.x) * cs.width) : layoutSize.width - cs.width;
                            break;
                        case LINEAR_GRAVITY_CENTER_HORIZONTAL:
                            finalPosX = childType == WidgetTypeWidget ? layoutSize.width / 2.0f - cs.width * (0.5f-ap.x) : (layoutSize.width - cs.width) * 0.5f;
                            break;
                        default:
                            break;
                    }
                    UIMargin mg = layoutParameter->getMargin();
                    finalPosX += mg.left;
                    finalPosY -= mg.top;
                    child->setPosition(Point(finalPosX, finalPosY));
                    topBoundary = child->getBottomInParent() - mg.bottom;
                }
            }
            break;
        }
        case LAYOUT_LINEAR_HORIZONTAL:
        {
            ccArray* layoutChildrenArray = getChildren()->data;
            int length = layoutChildrenArray->num;
            Size layoutSize = getSize();
            float leftBoundary = 0.0f;
            for (int i=0; i<length; ++i)
            {
                UIWidget* child = dynamic_cast<UIWidget*>(layoutChildrenArray->arr[i]);
                LinearLayoutParameter* layoutParameter = dynamic_cast<LinearLayoutParameter*>(child->getLayoutParameter());
                
                if (layoutParameter)
                {
                    WidgetType childType = child->getWidgetType();
                    UILinearGravity childGravity = layoutParameter->getGravity();
                    Point ap = child->getAnchorPoint();
                    Size cs = child->getSize();
                    float finalPosX = childType == WidgetTypeWidget ? leftBoundary + (ap.x * cs.width) : leftBoundary;
                    float finalPosY = childType == WidgetTypeWidget ? layoutSize.height - (1.0f - ap.y) * cs.height : layoutSize.height - cs.height;
                    switch (childGravity)
                    {
                        case LINEAR_GRAVITY_NONE:
                        case LINEAR_GRAVITY_TOP:
                            break;
                        case LINEAR_GRAVITY_BOTTOM:
                            finalPosY = childType == WidgetTypeWidget ? ap.y * cs.height : 0.0f;
                            break;
                        case LINEAR_GRAVITY_CENTER_VERTICAL:
                            finalPosY = childType == WidgetTypeWidget ? layoutSize.height/2.0f - cs.height * (0.5f - ap.y) : (layoutSize.height - cs.height) * 0.5f;
                            break;
                        default:
                            break;
                    }
                    UIMargin mg = layoutParameter->getMargin();
                    finalPosX += mg.left;
                    finalPosY -= mg.top;
                    child->setPosition(Point(finalPosX, finalPosY));
                    leftBoundary = child->getRightInParent() + mg.right;
                }
            }
            break;
        }
        case LAYOUT_RELATIVE:
        {
            ccArray* layoutChildrenArray = getChildren()->data;
            int length = layoutChildrenArray->num;
            Size layoutSize = getSize();
            for (int i=0; i<length; i++)
            {
                UIWidget* child = dynamic_cast<UIWidget*>(layoutChildrenArray->arr[i]);
                WidgetType childType = child->getWidgetType();
                Point ap = child->getAnchorPoint();
                Size cs = child->getSize();
                RelativeLayoutParameter* layoutParameter = dynamic_cast<RelativeLayoutParameter*>(child->getLayoutParameter());
                if (layoutParameter)
                {
                    float finalPosX = childType == WidgetTypeWidget ? ap.x * cs.width : 0.0f;
                    float finalPosY = childType == WidgetTypeWidget ? layoutSize.height - ((1.0f - ap.y) * cs.height) : layoutSize.height - cs.height;
                    UIRelativeAlign align = layoutParameter->getAlign();
                    const char* relativeName = layoutParameter->getRelativeToWidgetName();
                    UIWidget* relativeWidget = NULL;
                    if (relativeName && strcmp(relativeName, ""))
                    {
                        relativeWidget = CCUIHELPER->seekWidgetByRelativeName(this, relativeName);
                    }
                    switch (align)
                    {
                        case RELATIVE_ALIGN_NONE:
                            break;
                        case RELATIVE_ALIGN_PARENT_LEFT:
                            break;
                        case RELATIVE_ALIGN_PARENT_TOP:
                            break;
                        case RELATIVE_ALIGN_PARENT_RIGHT:
                            finalPosX = childType == WidgetTypeWidget ? layoutSize.width - ((1.0f - ap.x) * cs.width) : layoutSize.width - cs.width;
                            break;
                        case RELATIVE_ALIGN_PARENT_BOTTOM:
                            finalPosY = childType == WidgetTypeWidget ? ap.y * cs.height : 0.0f;
                            break;
                        case RELATIVE_CENTER_IN_PARENT:
                            finalPosX = childType == WidgetTypeWidget ? layoutSize.width * 0.5f - cs.width * (0.5f - ap.x) : (layoutSize.width - cs.width) * 0.5f;
                            finalPosY = childType == WidgetTypeWidget ? layoutSize.height * 0.5f - cs.height * (0.5f - ap.y) : (layoutSize.height - cs.height) * 0.5f;
                            break;
                        case RELATIVE_CENTER_HORIZONTAL:
                            finalPosX = childType == WidgetTypeWidget ? layoutSize.width * 0.5f - cs.width * (0.5f - ap.x) : (layoutSize.width - cs.width) * 0.5f;
                            break;
                        case RELATIVE_CENTER_VERTICAL:
                            finalPosY = childType == WidgetTypeWidget ? layoutSize.height * 0.5f - cs.height * (0.5f - ap.y) : (layoutSize.height - cs.height) * 0.5f;
                            break;
                        case RELATIVE_LOCATION_LEFT_OF_TOPALIGN:
                            if (relativeWidget)
                            {
                                float locationTop = relativeWidget->getTopInParent();
                                float locationRight = relativeWidget->getLeftInParent();
                                finalPosY = childType == WidgetTypeWidget ? locationTop - ap.y * cs.height : locationTop - cs.height;
                                finalPosX = childType == WidgetTypeWidget ? locationRight - (1.0f - ap.x) * cs.width : locationRight - cs.width;
                            }
                            break;
                        case RELATIVE_LOCATION_LEFT_OF_CENTER:
                            break;
                        case RELATIVE_LOCATION_LEFT_OF_BOTTOMALIGN:
                            if (relativeWidget)
                            {
                                float locationRight = relativeWidget->getLeftInParent();
                                float locationBottom = relativeWidget->getBottomInParent();
                                finalPosY = childType == WidgetTypeWidget ? locationBottom + ap.y * cs.height : locationBottom;
                                finalPosX = childType == WidgetTypeWidget ? locationRight - (1.0f - ap.x) * cs.width : locationRight - cs.width;
                            }
                            break;
                        case RELATIVE_LOCATION_RIGHT_OF_TOPALIGN:
                            if (relativeWidget)
                            {
                                float locationTop = relativeWidget->getTopInParent();
                                float locationLeft = relativeWidget->getRightInParent();
                                finalPosY = childType == WidgetTypeWidget ? locationTop - ap.y * cs.height : locationTop - cs.height;
                                finalPosX = childType == WidgetTypeWidget ? locationLeft + ap.x * cs.width : locationLeft;
                            }
                            break;
                        case RELATIVE_LOCATION_RIGHT_OF_CENTER:
                            break;
                        case RELATIVE_LOCATION_RIGHT_OF_BOTTOMALIGN:
                            if (relativeWidget)
                            {
                                float locationLeft = relativeWidget->getRightInParent();
                                float locationBottom = relativeWidget->getBottomInParent();
                                finalPosY = childType == WidgetTypeWidget ? locationBottom + ap.y * cs.height : locationBottom;
                                finalPosX = childType == WidgetTypeWidget ? locationLeft + ap.x * cs.width : locationLeft;
                            }
                            break;
                        case RELATIVE_LOCATION_ABOVE_LEFTALIGN:
                            if (relativeWidget)
                            {
                                float locationBottom = relativeWidget->getTopInParent();
                                float locationLeft = relativeWidget->getLeftInParent();
                                finalPosY = childType == WidgetTypeWidget ? locationBottom + ap.y * cs.height : locationBottom;
                                finalPosX = childType == WidgetTypeWidget ? locationLeft + ap.x * cs.width : locationLeft;
                            }
                            break;
                        case RELATIVE_LOCATION_ABOVE_CENTER:
                            break;
                        case RELATIVE_LOCATION_ABOVE_RIGHTALIGN:
                            if (relativeWidget)
                            {
                                float locationBottom = relativeWidget->getTopInParent();
                                float locationRight = relativeWidget->getRightInParent();
                                finalPosY = childType == WidgetTypeWidget ? locationBottom + ap.y * cs.height : locationBottom;
                                finalPosX = childType == WidgetTypeWidget ? locationRight - (1.0f - ap.x) * cs.width : locationRight - cs.width;
                            }
                            break;
                        case RELATIVE_LOCATION_BELOW_LEFTALIGN:
                            if (relativeWidget)
                            {
                                float locationTop = relativeWidget->getBottomInParent();
                                float locationLeft = relativeWidget->getLeftInParent();
                                finalPosY = childType == WidgetTypeWidget ? locationTop - (1.0f - ap.y) * cs.height : locationTop - cs.height;
                                finalPosX = childType == WidgetTypeWidget ? locationLeft + ap.x * cs.width : locationLeft;
                            }
                            break;
                        case RELATIVE_LOCATION_BELOW_CENTER:
                            break;
                        case RELATIVE_LOCATION_BELOW_RIGHTALIGN:
                            if (relativeWidget)
                            {
                                float locationTop = relativeWidget->getBottomInParent();
                                float locationRight = relativeWidget->getRightInParent();
                                finalPosY = childType == WidgetTypeWidget ? locationTop - (1.0f - ap.y) * cs.height : locationTop - cs.height;
                                finalPosX = childType == WidgetTypeWidget ? locationRight - (1.0f - ap.x) * cs.width : locationRight - cs.width;
                            }
                            break;
                        default:
                            break;
                    }
                    UIMargin relativeWidgetMargin;
                    UIMargin mg;
                    if (relativeWidget)
                    {
                        relativeWidgetMargin = relativeWidget->getLayoutParameter()->getMargin();
                        mg = child->getLayoutParameter()->getMargin();
                    }
                    //handle margin
                    switch (align)
                    {
                        case RELATIVE_LOCATION_ABOVE_LEFTALIGN:
                        case RELATIVE_LOCATION_ABOVE_RIGHTALIGN:
                        case RELATIVE_LOCATION_ABOVE_CENTER:
                            finalPosY += relativeWidgetMargin.top;
                            finalPosY += mg.bottom;
                            break;
                        case RELATIVE_LOCATION_BELOW_LEFTALIGN:
                        case RELATIVE_LOCATION_BELOW_RIGHTALIGN:
                        case RELATIVE_LOCATION_BELOW_CENTER:
                            finalPosY -= relativeWidgetMargin.bottom;
                            finalPosY -= mg.top;
                            break;
                        case RELATIVE_LOCATION_LEFT_OF_TOPALIGN:
                        case RELATIVE_LOCATION_LEFT_OF_BOTTOMALIGN:
                        case RELATIVE_LOCATION_LEFT_OF_CENTER:
                            finalPosX -= relativeWidgetMargin.left;
                            finalPosX -= mg.right;
                            break;
                        case RELATIVE_LOCATION_RIGHT_OF_TOPALIGN:
                        case RELATIVE_LOCATION_RIGHT_OF_BOTTOMALIGN:
                        case RELATIVE_LOCATION_RIGHT_OF_CENTER:
                            finalPosX += relativeWidgetMargin.right;
                            finalPosX += mg.left;
                            break;
                        default:
                            break;
                    }
                    child->setPosition(Point(finalPosX, finalPosY));
                }
            }
            break;
        }
        default:
            break;
    }
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