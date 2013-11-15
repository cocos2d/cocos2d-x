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

#include "gui/UILayout.h"
#include "gui/UILayer.h"
#include "gui/UIHelper.h"
#include "extensions/GUI/CCControlExtension/CCScale9Sprite.h"

namespace gui {


#define DYNAMIC_CAST_CLIPPINGLAYER dynamic_cast<UIRectClippingNode*>(_renderer)

UILayout::UILayout():
_clippingEnabled(false),
_backGroundScale9Enabled(false),
_backGroundImage(nullptr),
_backGroundImageFileName(""),
_backGroundImageCapInsets(cocos2d::Rect::ZERO),
_colorType(LAYOUT_COLOR_NONE),
_bgImageTexType(UI_TEX_TYPE_LOCAL),
_colorRender(nullptr),
_gradientRender(nullptr),
_cColor(cocos2d::Color3B::WHITE),
_gStartColor(cocos2d::Color3B::WHITE),
_gEndColor(cocos2d::Color3B::WHITE),
_alongVector(cocos2d::Point(0.0f, -1.0f)),
_cOpacity(255),
_backGroundImageTextureSize(cocos2d::Size::ZERO),
_layoutType(LAYOUT_ABSOLUTE)
{
    _widgetType = WidgetTypeContainer;
}

UILayout::~UILayout()
{
}

UILayout* UILayout::create()
{
    UILayout* layout = new UILayout();
    if (layout && layout->init())
    {
        layout->autorelease();
        return layout;
    }
    CC_SAFE_DELETE(layout);
    return nullptr;
}

bool UILayout::init()
{
    _children = cocos2d::Array::create();
    _children->retain();
    _layoutParameterDictionary = cocos2d::Dictionary::create();
    CC_SAFE_RETAIN(_layoutParameterDictionary);
    initRenderer();
    _renderer->retain();
    _renderer->setZOrder(_widgetZOrder);
    cocos2d::RGBAProtocol* renderRGBA = dynamic_cast<cocos2d::RGBAProtocol*>(_renderer);
    if (renderRGBA)
    {
        renderRGBA->setCascadeColorEnabled(false);
        renderRGBA->setCascadeOpacityEnabled(false);
    }
    ignoreContentAdaptWithSize(false);
    setSize(cocos2d::Size::ZERO);
    setBright(true);
    setAnchorPoint(cocos2d::Point(0, 0));
    _scheduler = cocos2d::Director::getInstance()->getScheduler();
    CC_SAFE_RETAIN(_scheduler);
    return true;
}

void UILayout::initRenderer()
{
    _renderer = UIRectClippingNode::create();
}

bool UILayout::addChild(UIWidget *child)
{
    supplyTheLayoutParameterLackToChild(child);
    return UIWidget::addChild(child);
}

bool UILayout::isClippingEnabled()
{
    return _clippingEnabled;
}

bool UILayout::hitTest(const cocos2d::Point &pt)
{
    cocos2d::Point nsp = _renderer->convertToNodeSpace(pt);
    cocos2d::Rect bb = cocos2d::Rect(0.0f, 0.0f, _size.width, _size.height);
    if (nsp.x >= bb.origin.x && nsp.x <= bb.origin.x + bb.size.width && nsp.y >= bb.origin.y && nsp.y <= bb.origin.y + bb.size.height)
    {
        return true;
    }
    return false;
}

void UILayout::setClippingEnabled(bool able)
{
    _clippingEnabled = able;
    DYNAMIC_CAST_CLIPPINGLAYER->setClippingEnabled(able);
}

void UILayout::onSizeChanged()
{
    DYNAMIC_CAST_CLIPPINGLAYER->setClippingSize(_size);
    if (strcmp(getDescription(), "Layout") == 0)
    {
        cocos2d::ccArray* arrayChildren = _children->data;
        int length = arrayChildren->num;
        for (int i=0; i<length; ++i)
        {
            UIWidget* child = (UIWidget*)arrayChildren->arr[i];
            child->updateSizeAndPosition();
        }
        doLayout();
    }
    if (_backGroundImage)
    {
        _backGroundImage->setPosition(cocos2d::Point(_size.width/2.0f, _size.height/2.0f));
        if (_backGroundScale9Enabled && _backGroundImage)
        {
            dynamic_cast<cocos2d::extension::Scale9Sprite*>(_backGroundImage)->setPreferredSize(_size);
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

void UILayout::setBackGroundImageScale9Enabled(bool able)
{
    if (_backGroundScale9Enabled == able)
    {
        return;
    }
    _renderer->removeChild(_backGroundImage, true);
    _backGroundImage = nullptr;
    _backGroundScale9Enabled = able;
    if (_backGroundScale9Enabled)
    {
        _backGroundImage = cocos2d::extension::Scale9Sprite::create();
        _renderer->addChild(_backGroundImage);
    }
    else
    {
        _backGroundImage = cocos2d::Sprite::create();
        _renderer->addChild(_backGroundImage);
    }
    _backGroundImage->setZOrder(-1);
    setBackGroundImage(_backGroundImageFileName.c_str(),_bgImageTexType);    
    setBackGroundImageCapInsets(_backGroundImageCapInsets);
}

void UILayout::setBackGroundImage(const char* fileName,TextureResType texType)
{
    if (!fileName || strcmp(fileName, "") == 0)
    {
        return;
    }
    if (_backGroundImage == nullptr)
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
                dynamic_cast<cocos2d::extension::Scale9Sprite*>(_backGroundImage)->initWithFile(fileName);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<cocos2d::extension::Scale9Sprite*>(_backGroundImage)->initWithSpriteFrameName(fileName);
                break;
            default:
                break;
        }
        dynamic_cast<cocos2d::extension::Scale9Sprite*>(_backGroundImage)->setPreferredSize(_size);
    }
    else
    {
        switch (_bgImageTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<cocos2d::Sprite*>(_backGroundImage)->initWithFile(fileName);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<cocos2d::Sprite*>(_backGroundImage)->initWithSpriteFrameName(fileName);
                break;
            default:
                break;
        }
    }
    if (_backGroundScale9Enabled)
    {
        dynamic_cast<cocos2d::extension::Scale9Sprite*>(_backGroundImage)->setColor(getColor());
        dynamic_cast<cocos2d::extension::Scale9Sprite*>(_backGroundImage)->setOpacity(getOpacity());
    }
    else
    {
        dynamic_cast<cocos2d::Sprite*>(_backGroundImage)->setColor(getColor());
        dynamic_cast<cocos2d::Sprite*>(_backGroundImage)->setOpacity(getOpacity());
    }
    _backGroundImageTextureSize = _backGroundImage->getContentSize();
    _backGroundImage->setPosition(cocos2d::Point(_size.width/2.0f, _size.height/2.0f));
}

void UILayout::setBackGroundImageCapInsets(const cocos2d::Rect &capInsets)
{
    _backGroundImageCapInsets = capInsets;
    if (_backGroundScale9Enabled && _backGroundImage)
    {
        dynamic_cast<cocos2d::extension::Scale9Sprite*>(_backGroundImage)->setCapInsets(capInsets);
    }
}

void UILayout::supplyTheLayoutParameterLackToChild(UIWidget *child)
{
    if (!child)
    {
        return;
    }
    switch (_layoutType)
    {
        case LAYOUT_ABSOLUTE:
            break;
        case LAYOUT_LINEAR_HORIZONTAL:
        case LAYOUT_LINEAR_VERTICAL:
        {
            UILinearLayoutParameter* layoutParameter = dynamic_cast<UILinearLayoutParameter*>(child->getLayoutParameter(LAYOUT_PARAMETER_LINEAR));
            if (!layoutParameter)
            {
                child->setLayoutParameter(UILinearLayoutParameter::create());
            }
            break;
        }
        case LAYOUT_RELATIVE:
        {
            UIRelativeLayoutParameter* layoutParameter = dynamic_cast<UIRelativeLayoutParameter*>(child->getLayoutParameter(LAYOUT_PARAMETER_RELATIVE));
            if (!layoutParameter)
            {
                child->setLayoutParameter(UIRelativeLayoutParameter::create());
            }
            break;
        }
        default:
            break;
    }
}

void UILayout::addBackGroundImage()
{
    if (_backGroundScale9Enabled)
    {
        _backGroundImage = cocos2d::extension::Scale9Sprite::create();
        _backGroundImage->setZOrder(-1);
        _renderer->addChild(_backGroundImage);
        dynamic_cast<cocos2d::extension::Scale9Sprite*>(_backGroundImage)->setPreferredSize(_size);
    }
    else
    {
        _backGroundImage = cocos2d::Sprite::create();
        _backGroundImage->setZOrder(-1);
        _renderer->addChild(_backGroundImage);
    }
    _backGroundImage->setPosition(cocos2d::Point(_size.width/2.0f, _size.height/2.0f));
}

void UILayout::removeBackGroundImage()
{
    if (!_backGroundImage)
    {
        return;
    }
    _renderer->removeChild(_backGroundImage,  true);
    _backGroundImage = nullptr;
    _backGroundImageFileName = "";
    _backGroundImageTextureSize = cocos2d::Size::ZERO;
}

void UILayout::setBackGroundColorType(LayoutBackGroundColorType type)
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
                _colorRender = nullptr;
            }
            if (_gradientRender)
            {
                _renderer->removeChild(_gradientRender, true);
                _gradientRender = nullptr;
            }
            break;
        case LAYOUT_COLOR_SOLID:
            if (_colorRender)
            {
                _renderer->removeChild(_colorRender, true);
                _colorRender = nullptr;
            }
            break;
        case LAYOUT_COLOR_GRADIENT:
            if (_gradientRender)
            {
                _renderer->removeChild(_gradientRender, true);
                _gradientRender = nullptr;
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
            _colorRender = cocos2d::LayerColor::create();
            _colorRender->setContentSize(_size);
            _colorRender->setOpacity(_cOpacity);
            _colorRender->setColor(_cColor);
            _renderer->addChild(_colorRender,-2);
            break;
        case LAYOUT_COLOR_GRADIENT:
            _gradientRender = cocos2d::LayerGradient::create();
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

void UILayout::setBackGroundColor(const cocos2d::Color3B &color)
{
    _cColor = color;
    if (_colorRender)
    {
        _colorRender->setColor(color);
    }
}

void UILayout::setBackGroundColor(const cocos2d::Color3B &startColor, const cocos2d::Color3B &endColor)
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

void UILayout::setBackGroundColorOpacity(int opacity)
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

void UILayout::setBackGroundColorVector(const cocos2d::Point &vector)
{
    _alongVector = vector;
    if (_gradientRender)
    {
        _gradientRender->setVector(vector);
    }
}

void UILayout::setColor(const cocos2d::Color3B &color)
{
    UIWidget::setColor(color);
    if (_backGroundImage)
    {
        cocos2d::RGBAProtocol* rgbap = dynamic_cast<cocos2d::RGBAProtocol*>(_backGroundImage);
        if (rgbap)
        {
            rgbap->setColor(color);
        }
    }
}

void UILayout::setOpacity(int opacity)
{
    UIWidget::setOpacity(opacity);
    if (_backGroundImage)
    {
        cocos2d::RGBAProtocol* rgbap = dynamic_cast<cocos2d::RGBAProtocol*>(_backGroundImage);
        if (rgbap)
        {
            rgbap->setOpacity(opacity);
        }
    }
}

const cocos2d::Size& UILayout::getBackGroundImageTextureSize() const
{
    return _backGroundImageTextureSize;
}

const cocos2d::Size& UILayout::getContentSize() const
{
    return _renderer->getContentSize();
}

void UILayout::setLayoutType(LayoutType type)
{
    _layoutType = type;

    cocos2d::ccArray* layoutChildrenArray = getChildren()->data;
    int length = layoutChildrenArray->num;
    for (int i=0; i<length; i++)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(layoutChildrenArray->arr[i]);
        supplyTheLayoutParameterLackToChild(child);
    }
}

LayoutType UILayout::getLayoutType() const
{
    return _layoutType;
}

void UILayout::doLayout()
{
    switch (_layoutType)
    {
        case LAYOUT_ABSOLUTE:
            break;
        case LAYOUT_LINEAR_VERTICAL:
        {
            cocos2d::ccArray* layoutChildrenArray = getChildren()->data;
            int length = layoutChildrenArray->num;
            cocos2d::Size layoutSize = getSize();
            float topBoundary = layoutSize.height;
            for (int i=0; i<length; ++i)
            {
                UIWidget* child = dynamic_cast<UIWidget*>(layoutChildrenArray->arr[i]);
                UILinearLayoutParameter* layoutParameter = dynamic_cast<UILinearLayoutParameter*>(child->getLayoutParameter(LAYOUT_PARAMETER_LINEAR));
                
                if (layoutParameter)
                {
                    UILinearGravity childGravity = layoutParameter->getGravity();
                    cocos2d::Point ap = child->getAnchorPoint();
                    cocos2d::Size cs = child->getSize();
                    float finalPosX = ap.x * cs.width;
                    float finalPosY = topBoundary - ((1.0f-ap.y) * cs.height);
                    switch (childGravity)
                    {
                        case LINEAR_GRAVITY_NONE:
                        case LINEAR_GRAVITY_LEFT:
                            break;
                        case LINEAR_GRAVITY_RIGHT:
                            finalPosX = layoutSize.width - ((1.0f - ap.x) * cs.width);
                            break;
                        case LINEAR_GRAVITY_CENTER_HORIZONTAL:
                            finalPosX = layoutSize.width / 2.0f - cs.width * (0.5f-ap.x);
                            break;
                        default:
                            break;
                    }
                    UIMargin mg = layoutParameter->getMargin();
                    finalPosX += mg.left;
                    finalPosY -= mg.top;
                    child->setPosition(cocos2d::Point(finalPosX, finalPosY));
                    topBoundary = child->getBottomInParent() - mg.bottom;
                }
            }
            break;
        }
        case LAYOUT_LINEAR_HORIZONTAL:
        {
            cocos2d::ccArray* layoutChildrenArray = getChildren()->data;
            int length = layoutChildrenArray->num;
            cocos2d::Size layoutSize = getSize();
            float leftBoundary = 0.0f;
            for (int i=0; i<length; ++i)
            {
                UIWidget* child = dynamic_cast<UIWidget*>(layoutChildrenArray->arr[i]);
                UILinearLayoutParameter* layoutParameter = dynamic_cast<UILinearLayoutParameter*>(child->getLayoutParameter(LAYOUT_PARAMETER_LINEAR));
                
                if (layoutParameter)
                {
                    UILinearGravity childGravity = layoutParameter->getGravity();
                    cocos2d::Point ap = child->getAnchorPoint();
                    cocos2d::Size cs = child->getSize();
                    float finalPosX = leftBoundary + (ap.x * cs.width);
                    float finalPosY = layoutSize.height - (1.0f - ap.y) * cs.height;
                    switch (childGravity)
                    {
                        case LINEAR_GRAVITY_NONE:
                        case LINEAR_GRAVITY_TOP:
                            break;
                        case LINEAR_GRAVITY_BOTTOM:
                            finalPosY = ap.y * cs.height;
                            break;
                        case LINEAR_GRAVITY_CENTER_VERTICAL:
                            finalPosY = layoutSize.height / 2.0f - cs.height * (0.5f - ap.y);
                            break;
                        default:
                            break;
                    }
                    UIMargin mg = layoutParameter->getMargin();
                    finalPosX += mg.left;
                    finalPosY -= mg.top;
                    child->setPosition(cocos2d::Point(finalPosX, finalPosY));
                    leftBoundary = child->getRightInParent() + mg.right;
                }
            }
            break;
        }
        case LAYOUT_RELATIVE:
        {
            cocos2d::ccArray* layoutChildrenArray = getChildren()->data;
            int length = layoutChildrenArray->num;
            int unlayoutChildCount = length;
            cocos2d::Size layoutSize = getSize();
            
            for (int i=0; i<length; i++)
            {
                UIWidget* child = dynamic_cast<UIWidget*>(layoutChildrenArray->arr[i]);
                UIRelativeLayoutParameter* layoutParameter = dynamic_cast<UIRelativeLayoutParameter*>(child->getLayoutParameter(LAYOUT_PARAMETER_RELATIVE));
                layoutParameter->_put = false;
            }
            
            while (unlayoutChildCount > 0)
            {
                for (int i=0; i<length; i++)
                {
                    UIWidget* child = dynamic_cast<UIWidget*>(layoutChildrenArray->arr[i]);
                    UIRelativeLayoutParameter* layoutParameter = dynamic_cast<UIRelativeLayoutParameter*>(child->getLayoutParameter(LAYOUT_PARAMETER_RELATIVE));
                    
                    if (layoutParameter)
                    {
                        if (layoutParameter->_put)
                        {
                            continue;
                        }
                        cocos2d::Point ap = child->getAnchorPoint();
                        cocos2d::Size cs = child->getSize();
                        UIRelativeAlign align = layoutParameter->getAlign();
                        const char* relativeName = layoutParameter->getRelativeToWidgetName();
                        UIWidget* relativeWidget = nullptr;
                        UIRelativeLayoutParameter* relativeWidgetLP = nullptr;
                        float finalPosX = 0.0f;
                        float finalPosY = 0.0f;
                        if (relativeName && strcmp(relativeName, ""))
                        {
                            relativeWidget = UIHelper::seekWidgetByRelativeName(this, relativeName);
                            if (relativeWidget)
                            {
                                relativeWidgetLP = dynamic_cast<UIRelativeLayoutParameter*>(relativeWidget->getLayoutParameter(LAYOUT_PARAMETER_RELATIVE));
                            }
                        }
                        switch (align)
                        {
                            case RELATIVE_ALIGN_NONE:
                            case RELATIVE_ALIGN_PARENT_TOP_LEFT:
                                finalPosX = ap.x * cs.width;
                                finalPosY = layoutSize.height - ((1.0f - ap.y) * cs.height);
                                break;
                            case RELATIVE_ALIGN_PARENT_TOP_CENTER_HORIZONTAL:
                                finalPosX = layoutSize.width * 0.5f - cs.width * (0.5f - ap.x);
                                finalPosY = layoutSize.height - ((1.0f - ap.y) * cs.height);
                                break;
                            case RELATIVE_ALIGN_PARENT_TOP_RIGHT:
                                finalPosX = layoutSize.width - ((1.0f - ap.x) * cs.width);
                                finalPosY = layoutSize.height - ((1.0f - ap.y) * cs.height);
                                break;
                            case RELATIVE_ALIGN_PARENT_LEFT_CENTER_VERTICAL:
                                finalPosX = ap.x * cs.width;
                                finalPosY = layoutSize.height * 0.5f - cs.height * (0.5f - ap.y);
                                break;
                            case RELATIVE_CENTER_IN_PARENT:
                                finalPosX = layoutSize.width * 0.5f - cs.width * (0.5f - ap.x);
                                finalPosY = layoutSize.height * 0.5f - cs.height * (0.5f - ap.y);
                                break;
                            case RELATIVE_ALIGN_PARENT_RIGHT_CENTER_VERTICAL:
                                finalPosX = layoutSize.width - ((1.0f - ap.x) * cs.width);
                                finalPosY = layoutSize.height * 0.5f - cs.height * (0.5f - ap.y);
                                break;
                            case RELATIVE_ALIGN_PARENT_LEFT_BOTTOM:
                                finalPosX = ap.x * cs.width;
                                finalPosY = ap.y * cs.height;
                                break;
                            case RELATIVE_ALIGN_PARENT_BOTTOM_CENTER_HORIZONTAL:
                                finalPosX = layoutSize.width * 0.5f - cs.width * (0.5f - ap.x);
                                finalPosY = ap.y * cs.height;
                                break;
                            case RELATIVE_ALIGN_PARENT_RIGHT_BOTTOM:
                                finalPosX = layoutSize.width - ((1.0f - ap.x) * cs.width);
                                finalPosY = ap.y * cs.height;
                                break;
                                
                            case RELATIVE_LOCATION_ABOVE_LEFTALIGN:
                                if (relativeWidget)
                                {
                                    if (relativeWidgetLP && !relativeWidgetLP->_put)
                                    {
                                        continue;
                                    }
                                    float locationBottom = relativeWidget->getTopInParent();
                                    float locationLeft = relativeWidget->getLeftInParent();
                                    finalPosY = locationBottom + ap.y * cs.height;
                                    finalPosX = locationLeft + ap.x * cs.width;
                                }
                                break;
                            case RELATIVE_LOCATION_ABOVE_CENTER:
                                if (relativeWidget)
                                {
                                    if (relativeWidgetLP && !relativeWidgetLP->_put)
                                    {
                                        continue;
                                    }
                                    cocos2d::Size rbs = relativeWidget->getSize();
                                    float locationBottom = relativeWidget->getTopInParent();
                                    
                                    finalPosY = locationBottom + ap.y * cs.height;
                                    finalPosX = relativeWidget->getLeftInParent() + rbs.width * 0.5f + ap.x * cs.width - cs.width * 0.5f;
                                }
                                break;
                            case RELATIVE_LOCATION_ABOVE_RIGHTALIGN:
                                if (relativeWidget)
                                {
                                    if (relativeWidgetLP && !relativeWidgetLP->_put)
                                    {
                                        continue;
                                    }
                                    float locationBottom = relativeWidget->getTopInParent();
                                    float locationRight = relativeWidget->getRightInParent();
                                    finalPosY = locationBottom + ap.y * cs.height;
                                    finalPosX = locationRight - (1.0f - ap.x) * cs.width;
                                }
                                break;
                            case RELATIVE_LOCATION_LEFT_OF_TOPALIGN:
                                if (relativeWidget)
                                {
                                    if (relativeWidgetLP && !relativeWidgetLP->_put)
                                    {
                                        continue;
                                    }
                                    float locationTop = relativeWidget->getTopInParent();
                                    float locationRight = relativeWidget->getLeftInParent();
                                    finalPosY = locationTop - (1.0f - ap.y) * cs.height;
                                    finalPosX = locationRight - (1.0f - ap.x) * cs.width;
                                }
                                break;
                            case RELATIVE_LOCATION_LEFT_OF_CENTER:
                                if (relativeWidget)
                                {
                                    if (relativeWidgetLP && !relativeWidgetLP->_put)
                                    {
                                        continue;
                                    }
                                    cocos2d::Size rbs = relativeWidget->getSize();
                                    float locationRight = relativeWidget->getLeftInParent();
                                    finalPosX = locationRight - (1.0f - ap.x) * cs.width;
                                    
                                    finalPosY = relativeWidget->getBottomInParent() + rbs.height * 0.5f + ap.y * cs.height - cs.height * 0.5f;
                                }
                                break;
                            case RELATIVE_LOCATION_LEFT_OF_BOTTOMALIGN:
                                if (relativeWidget)
                                {
                                    if (relativeWidgetLP && !relativeWidgetLP->_put)
                                    {
                                        continue;
                                    }
                                    float locationBottom = relativeWidget->getBottomInParent();
                                    float locationRight = relativeWidget->getLeftInParent();
                                    finalPosY = locationBottom + ap.y * cs.height;
                                    finalPosX = locationRight - (1.0f - ap.x) * cs.width;
                                }
                                break;
                            case RELATIVE_LOCATION_RIGHT_OF_TOPALIGN:
                                if (relativeWidget)
                                {
                                    if (relativeWidgetLP && !relativeWidgetLP->_put)
                                    {
                                        continue;
                                    }
                                    float locationTop = relativeWidget->getTopInParent();
                                    float locationLeft = relativeWidget->getRightInParent();
                                    finalPosY = locationTop - (1.0f - ap.y) * cs.height;
                                    finalPosX = locationLeft + ap.x * cs.width;
                                }
                                break;
                            case RELATIVE_LOCATION_RIGHT_OF_CENTER:
                                if (relativeWidget)
                                {
                                    if (relativeWidgetLP && !relativeWidgetLP->_put)
                                    {
                                        continue;
                                    }
                                    cocos2d::Size rbs = relativeWidget->getSize();
                                    float locationLeft = relativeWidget->getRightInParent();
                                    finalPosX = locationLeft + ap.x * cs.width;
                                    
                                    finalPosY = relativeWidget->getBottomInParent() + rbs.height * 0.5f + ap.y * cs.height - cs.height * 0.5f;
                                }
                                break;
                            case RELATIVE_LOCATION_RIGHT_OF_BOTTOMALIGN:
                                if (relativeWidget)
                                {
                                    if (relativeWidgetLP && !relativeWidgetLP->_put)
                                    {
                                        continue;
                                    }
                                    float locationBottom = relativeWidget->getBottomInParent();
                                    float locationLeft = relativeWidget->getRightInParent();
                                    finalPosY = locationBottom + ap.y * cs.height;
                                    finalPosX = locationLeft + ap.x * cs.width;
                                }
                                break;
                            case RELATIVE_LOCATION_BELOW_LEFTALIGN:
                                if (relativeWidget)
                                {
                                    if (relativeWidgetLP && !relativeWidgetLP->_put)
                                    {
                                        continue;
                                    }
                                    float locationTop = relativeWidget->getBottomInParent();
                                    float locationLeft = relativeWidget->getLeftInParent();
                                    finalPosY = locationTop - (1.0f - ap.y) * cs.height;
                                    finalPosX = locationLeft + ap.x * cs.width;
                                }
                                break;
                            case RELATIVE_LOCATION_BELOW_CENTER:
                                if (relativeWidget)
                                {
                                    if (relativeWidgetLP && !relativeWidgetLP->_put)
                                    {
                                        continue;
                                    }
                                    cocos2d::Size rbs = relativeWidget->getSize();
                                    float locationTop = relativeWidget->getBottomInParent();
                                    
                                    finalPosY = locationTop - (1.0f - ap.y) * cs.height;
                                    finalPosX = relativeWidget->getLeftInParent() + rbs.width * 0.5f + ap.x * cs.width - cs.width * 0.5f;
                                }
                                break;
                            case RELATIVE_LOCATION_BELOW_RIGHTALIGN:
                                if (relativeWidget)
                                {
                                    if (relativeWidgetLP && !relativeWidgetLP->_put)
                                    {
                                        continue;
                                    }
                                    float locationTop = relativeWidget->getBottomInParent();
                                    float locationRight = relativeWidget->getRightInParent();
                                    finalPosY = locationTop - (1.0f - ap.y) * cs.height;
                                    finalPosX = locationRight - (1.0f - ap.x) * cs.width;
                                }
                                break;
                            default:
                                break;
                        }
                        UIMargin relativeWidgetMargin;
                        UIMargin mg = layoutParameter->getMargin();
                        if (relativeWidgetLP)
                        {
                            relativeWidgetMargin = relativeWidgetLP->getMargin();
                        }
                        //handle margin
                        switch (align)
                        {
                            case RELATIVE_ALIGN_NONE:
                            case RELATIVE_ALIGN_PARENT_TOP_LEFT:
                                finalPosX += mg.left;
                                finalPosY -= mg.top;
                                break;
                            case RELATIVE_ALIGN_PARENT_TOP_CENTER_HORIZONTAL:
                                finalPosY -= mg.top;
                                break;
                            case RELATIVE_ALIGN_PARENT_TOP_RIGHT:
                                finalPosX -= mg.right;
                                finalPosY -= mg.top;
                                break;
                            case RELATIVE_ALIGN_PARENT_LEFT_CENTER_VERTICAL:
                                finalPosX += mg.left;
                                break;
                            case RELATIVE_CENTER_IN_PARENT:
                                break;
                            case RELATIVE_ALIGN_PARENT_RIGHT_CENTER_VERTICAL:
                                finalPosX -= mg.right;
                                break;
                            case RELATIVE_ALIGN_PARENT_LEFT_BOTTOM:
                                finalPosX += mg.left;
                                finalPosY += mg.bottom;
                                break;
                            case RELATIVE_ALIGN_PARENT_BOTTOM_CENTER_HORIZONTAL:
                                finalPosY += mg.bottom;
                                break;
                            case RELATIVE_ALIGN_PARENT_RIGHT_BOTTOM:
                                finalPosX -= mg.right;
                                finalPosY += mg.bottom;
                                break;
                                
                            case RELATIVE_LOCATION_ABOVE_LEFTALIGN:
                                finalPosY += mg.bottom;
                                if (relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_TOP_CENTER_HORIZONTAL
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_TOP_LEFT
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_NONE
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_TOP_RIGHT)
                                {
                                    finalPosY += relativeWidgetMargin.top;
                                }
                                finalPosX += mg.left;
                                break;
                            case RELATIVE_LOCATION_ABOVE_RIGHTALIGN:
                                finalPosY += mg.bottom;
                                if (relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_TOP_CENTER_HORIZONTAL
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_TOP_LEFT
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_NONE
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_TOP_RIGHT)
                                {
                                    finalPosY += relativeWidgetMargin.top;
                                }
                                finalPosX -= mg.right;
                                break;
                            case RELATIVE_LOCATION_ABOVE_CENTER:
                                finalPosY += mg.bottom;
                                if (relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_TOP_CENTER_HORIZONTAL
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_TOP_LEFT
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_NONE
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_TOP_RIGHT)
                                {
                                    finalPosY += relativeWidgetMargin.top;
                                }
                                break;
                                
                            case RELATIVE_LOCATION_LEFT_OF_TOPALIGN:
                                finalPosX -= mg.right;
                                if (relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_TOP_LEFT
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_NONE
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_LEFT_BOTTOM
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_LEFT_CENTER_VERTICAL)
                                {
                                    finalPosX -= relativeWidgetMargin.left;
                                }
                                finalPosY -= mg.top;
                                break;
                            case RELATIVE_LOCATION_LEFT_OF_BOTTOMALIGN:
                                finalPosX -= mg.right;
                                if (relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_TOP_LEFT
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_NONE
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_LEFT_BOTTOM
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_LEFT_CENTER_VERTICAL)
                                {
                                    finalPosX -= relativeWidgetMargin.left;
                                }
                                finalPosY += mg.bottom;
                                break;
                            case RELATIVE_LOCATION_LEFT_OF_CENTER:
                                finalPosX -= mg.right;
                                if (relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_TOP_LEFT
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_NONE
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_LEFT_BOTTOM
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_LEFT_CENTER_VERTICAL)
                                {
                                    finalPosX -= relativeWidgetMargin.left;
                                }
                                break;
                                
                            case RELATIVE_LOCATION_RIGHT_OF_TOPALIGN:
                                finalPosX += mg.left;
                                if (relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_TOP_RIGHT
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_RIGHT_BOTTOM
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_RIGHT_CENTER_VERTICAL)
                                {
                                    finalPosX += relativeWidgetMargin.right;
                                }
                                finalPosY -= mg.top;
                                break;
                            case RELATIVE_LOCATION_RIGHT_OF_BOTTOMALIGN:
                                finalPosX += mg.left;
                                if (relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_TOP_RIGHT
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_RIGHT_BOTTOM
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_RIGHT_CENTER_VERTICAL)
                                {
                                    finalPosX += relativeWidgetMargin.right;
                                }
                                finalPosY += mg.bottom;
                                break;
                            case RELATIVE_LOCATION_RIGHT_OF_CENTER:
                                finalPosX += mg.left;
                                if (relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_TOP_RIGHT
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_RIGHT_BOTTOM
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_RIGHT_CENTER_VERTICAL)
                                {
                                    finalPosX += relativeWidgetMargin.right;
                                }
                                break;
                                
                            case RELATIVE_LOCATION_BELOW_LEFTALIGN:
                                finalPosY -= mg.top;
                                if (relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_LEFT_BOTTOM
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_RIGHT_BOTTOM
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_BOTTOM_CENTER_HORIZONTAL)
                                {
                                    finalPosY -= relativeWidgetMargin.bottom;
                                }
                                finalPosX += mg.left;
                                break;
                            case RELATIVE_LOCATION_BELOW_RIGHTALIGN:
                                finalPosY -= mg.top;
                                if (relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_LEFT_BOTTOM
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_RIGHT_BOTTOM
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_BOTTOM_CENTER_HORIZONTAL)
                                {
                                    finalPosY -= relativeWidgetMargin.bottom;
                                }
                                finalPosX -= mg.right;
                                break;
                            case RELATIVE_LOCATION_BELOW_CENTER:
                                finalPosY -= mg.top;
                                if (relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_LEFT_BOTTOM
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_RIGHT_BOTTOM
                                    && relativeWidgetLP->getAlign() != RELATIVE_ALIGN_PARENT_BOTTOM_CENTER_HORIZONTAL)
                                {
                                    finalPosY -= relativeWidgetMargin.bottom;
                                }
                                break;
                            default:
                                break;
                        }
                        child->setPosition(cocos2d::Point(finalPosX, finalPosY));
                        layoutParameter->_put = true;
                        unlayoutChildCount--;
                    }
                }
            }
            break;
        }
        default:
            break;
    }
}

const char* UILayout::getDescription() const
{
    return "Layout";
}

UIWidget* UILayout::createCloneInstance()
{
    return UILayout::create();
}

void UILayout::copyClonedWidgetChildren(UIWidget* model)
{
    UIWidget::copyClonedWidgetChildren(model);
    doLayout();
}

void UILayout::copySpecialProperties(UIWidget *widget)
{
    UILayout* layout = dynamic_cast<UILayout*>(widget);
    if (layout)
    {
        setBackGroundImageScale9Enabled(layout->_backGroundScale9Enabled);
        setBackGroundImage(layout->_backGroundImageFileName.c_str(),layout->_bgImageTexType);
        setBackGroundImageCapInsets(layout->_backGroundImageCapInsets);
        setBackGroundColorType(layout->_colorType);
        setBackGroundColor(layout->_cColor);
        setBackGroundColor(layout->_gStartColor, layout->_gEndColor);
        setBackGroundColorOpacity(layout->_cOpacity);
        setBackGroundColorVector(layout->_alongVector);
        setLayoutType(layout->_layoutType);
        setClippingEnabled(layout->_clippingEnabled);
    }
}

UIRectClippingNode::UIRectClippingNode():
_innerStencil(nullptr),
_enabled(true),
_clippingSize(cocos2d::Size(50.0f, 50.0f)),
_clippingEnabled(false)
{
    
}

UIRectClippingNode::~UIRectClippingNode()
{
    
}

UIRectClippingNode* UIRectClippingNode::create()
{
    UIRectClippingNode *pRet = new UIRectClippingNode();
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

bool UIRectClippingNode::init()
{
    _innerStencil = cocos2d::DrawNode::create();
    rect[0] = cocos2d::Point(0, 0);
    rect[1] = cocos2d::Point(_clippingSize.width, 0);
    rect[2] = cocos2d::Point(_clippingSize.width, _clippingSize.height);
    rect[3] = cocos2d::Point(0, _clippingSize.height);
    
    cocos2d::Color4F green(0, 1, 0, 1);
    _innerStencil->drawPolygon(rect, 4, green, 0, green);
    if (cocos2d::ClippingNode::init(_innerStencil))
    {
        return true;
    }
    return false;
}


void UIRectClippingNode::setClippingSize(const cocos2d::Size &size)
{
    setContentSize(size);
    _clippingSize = size;
    rect[0] = cocos2d::Point(0, 0);
    rect[1] = cocos2d::Point(_clippingSize.width, 0);
    rect[2] = cocos2d::Point(_clippingSize.width, _clippingSize.height);
    rect[3] = cocos2d::Point(0, _clippingSize.height);
    cocos2d::Color4F green(0, 1, 0, 1);
    _innerStencil->clear();
    _innerStencil->drawPolygon(rect, 4, green, 0, green);
}

void UIRectClippingNode::setClippingEnabled(bool enabled)
{
    _clippingEnabled = enabled;
}

void UIRectClippingNode::visit()
{
    if (!_enabled)
    {
        return;
    }
    if (_clippingEnabled)
    {
        cocos2d::ClippingNode::visit();
    }
    else
    {
        cocos2d::Node::visit();
    }
}

void UIRectClippingNode::setEnabled(bool enabled)
{
    _enabled = enabled;
}

bool UIRectClippingNode::isEnabled() const
{
    return _enabled;
}

}