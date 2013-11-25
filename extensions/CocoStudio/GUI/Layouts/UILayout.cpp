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

#include "UILayout.h"
#include "../System/UILayer.h"
#include "../System/UIHelper.h"
#include "../../../GUI/CCControlExtension/CCScale9Sprite.h"

NS_CC_EXT_BEGIN

#define DYNAMIC_CAST_CLIPPINGLAYER dynamic_cast<UIRectClippingNode*>(m_pRenderer)

UILayout::UILayout():
m_bClippingEnabled(false),
m_bBackGroundScale9Enabled(false),
m_pBackGroundImage(NULL),
m_strBackGroundImageFileName(""),
m_backGroundImageCapInsets(CCRectZero),
m_colorType(LAYOUT_COLOR_NONE),
m_eBGImageTexType(UI_TEX_TYPE_LOCAL),
m_pColorRender(NULL),
m_pGradientRender(NULL),
m_cColor(ccWHITE),
m_gStartColor(ccWHITE),
m_gEndColor(ccWHITE),
m_AlongVector(ccp(0.0f, -1.0f)),
m_nCOpacity(255),
m_backGroundImageTextureSize(CCSizeZero),
m_eLayoutType(LAYOUT_ABSOLUTE)
{
    m_WidgetType = WidgetTypeContainer;
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
    return NULL;
}

bool UILayout::init()
{
    m_children = CCArray::create();
    m_children->retain();
    m_pLayoutParameterDictionary = CCDictionary::create();
    CC_SAFE_RETAIN(m_pLayoutParameterDictionary);
    initRenderer();
    m_pRenderer->retain();
    m_pRenderer->setZOrder(m_nWidgetZOrder);
    CCRGBAProtocol* renderRGBA = dynamic_cast<CCRGBAProtocol*>(m_pRenderer);
    if (renderRGBA)
    {
        renderRGBA->setCascadeColorEnabled(false);
        renderRGBA->setCascadeOpacityEnabled(false);
    }
    ignoreContentAdaptWithSize(false);
    setSize(CCSizeZero);
    setBright(true);
    setAnchorPoint(ccp(0, 0));
    m_pScheduler = CCDirector::sharedDirector()->getScheduler();
    CC_SAFE_RETAIN(m_pScheduler);
    return true;
}

void UILayout::initRenderer()
{
    m_pRenderer = UIRectClippingNode::create();
}

bool UILayout::addChild(cocos2d::extension::UIWidget *child)
{
    supplyTheLayoutParameterLackToChild(child);
    return UIWidget::addChild(child);
}

bool UILayout::isClippingEnabled()
{
    return m_bClippingEnabled;
}

bool UILayout::hitTest(const CCPoint &pt)
{
    CCPoint nsp = m_pRenderer->convertToNodeSpace(pt);
    CCRect bb = CCRectMake(0.0f, 0.0f, m_size.width, m_size.height);
    if (nsp.x >= bb.origin.x && nsp.x <= bb.origin.x + bb.size.width && nsp.y >= bb.origin.y && nsp.y <= bb.origin.y + bb.size.height)
    {
        return true;
    }
    return false;
}

void UILayout::setClippingEnabled(bool able)
{
    m_bClippingEnabled = able;
    DYNAMIC_CAST_CLIPPINGLAYER->setClippingEnabled(able);
}

void UILayout::onSizeChanged()
{
    DYNAMIC_CAST_CLIPPINGLAYER->setClippingSize(m_size);
    if (strcmp(getDescription(), "Layout") == 0)
    {
        ccArray* arrayChildren = m_children->data;
        int length = arrayChildren->num;
        for (int i=0; i<length; ++i)
        {
            UIWidget* child = (UIWidget*)arrayChildren->arr[i];
            child->updateSizeAndPosition();
        }
        doLayout();
    }
    
    if (m_pBackGroundImage)
    {
        m_pBackGroundImage->setPosition(ccp(m_size.width/2.0f, m_size.height/2.0f));
        if (m_bBackGroundScale9Enabled && m_pBackGroundImage)
        {
            dynamic_cast<CCScale9Sprite*>(m_pBackGroundImage)->setPreferredSize(m_size);
        }
    }
    if (m_pColorRender)
    {
        m_pColorRender->setContentSize(m_size);
    }
    if (m_pGradientRender)
    {
        m_pGradientRender->setContentSize(m_size);
    }
}

void UILayout::setBackGroundImageScale9Enabled(bool able)
{
    if (m_bBackGroundScale9Enabled == able)
    {
        return;
    }
    m_pRenderer->removeChild(m_pBackGroundImage, true);
    m_pBackGroundImage = NULL;
    m_bBackGroundScale9Enabled = able;
    if (m_bBackGroundScale9Enabled)
    {
        m_pBackGroundImage = CCScale9Sprite::create();
        m_pRenderer->addChild(m_pBackGroundImage);
    }
    else
    {
        m_pBackGroundImage = CCSprite::create();
        m_pRenderer->addChild(m_pBackGroundImage);
    }
    m_pBackGroundImage->setZOrder(-1);
    setBackGroundImage(m_strBackGroundImageFileName.c_str(),m_eBGImageTexType);    
    setBackGroundImageCapInsets(m_backGroundImageCapInsets);
}

void UILayout::setBackGroundImage(const char* fileName,TextureResType texType)
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
    if (m_bBackGroundScale9Enabled)
    {
        switch (m_eBGImageTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<CCScale9Sprite*>(m_pBackGroundImage)->initWithFile(fileName);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<CCScale9Sprite*>(m_pBackGroundImage)->initWithSpriteFrameName(fileName);
                break;
            default:
                break;
        }
        dynamic_cast<CCScale9Sprite*>(m_pBackGroundImage)->setPreferredSize(m_size);
    }
    else
    {
        switch (m_eBGImageTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<CCSprite*>(m_pBackGroundImage)->initWithFile(fileName);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<CCSprite*>(m_pBackGroundImage)->initWithSpriteFrameName(fileName);
                break;
            default:
                break;
        }
    }
    if (m_bBackGroundScale9Enabled)
    {
        dynamic_cast<CCScale9Sprite*>(m_pBackGroundImage)->setColor(getColor());
        dynamic_cast<CCScale9Sprite*>(m_pBackGroundImage)->setOpacity(getOpacity());
    }
    else
    {
        dynamic_cast<CCSprite*>(m_pBackGroundImage)->setColor(getColor());
        dynamic_cast<CCSprite*>(m_pBackGroundImage)->setOpacity(getOpacity());
    }
    m_backGroundImageTextureSize = m_pBackGroundImage->getContentSize();
    m_pBackGroundImage->setPosition(ccp(m_size.width/2.0f, m_size.height/2.0f));
}

void UILayout::setBackGroundImageCapInsets(const CCRect &capInsets)
{
    m_backGroundImageCapInsets = capInsets;
    if (m_bBackGroundScale9Enabled && m_pBackGroundImage)
    {
        dynamic_cast<CCScale9Sprite*>(m_pBackGroundImage)->setCapInsets(capInsets);
    }
}

void UILayout::supplyTheLayoutParameterLackToChild(UIWidget *child)
{
    if (!child)
    {
        return;
    }
    switch (m_eLayoutType)
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
    if (m_bBackGroundScale9Enabled)
    {
        m_pBackGroundImage = CCScale9Sprite::create();
        m_pBackGroundImage->setZOrder(-1);
        m_pRenderer->addChild(m_pBackGroundImage);
        dynamic_cast<CCScale9Sprite*>(m_pBackGroundImage)->setPreferredSize(m_size);
    }
    else
    {
        m_pBackGroundImage = CCSprite::create();
        m_pBackGroundImage->setZOrder(-1);
        m_pRenderer->addChild(m_pBackGroundImage);
    }
    m_pBackGroundImage->setPosition(ccp(m_size.width/2.0f, m_size.height/2.0f));
}

void UILayout::removeBackGroundImage()
{
    if (!m_pBackGroundImage)
    {
        return;
    }
    m_pRenderer->removeChild(m_pBackGroundImage,  true);
    m_pBackGroundImage = NULL;
    m_strBackGroundImageFileName = "";
    m_backGroundImageTextureSize = CCSizeZero;
}

void UILayout::setBackGroundColorType(LayoutBackGroundColorType type)
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
                m_pRenderer->removeChild(m_pColorRender, true);
                m_pColorRender = NULL;
            }
            if (m_pGradientRender)
            {
                m_pRenderer->removeChild(m_pGradientRender, true);
                m_pGradientRender = NULL;
            }
            break;
        case LAYOUT_COLOR_SOLID:
            if (m_pColorRender)
            {
                m_pRenderer->removeChild(m_pColorRender, true);
                m_pColorRender = NULL;
            }
            break;
        case LAYOUT_COLOR_GRADIENT:
            if (m_pGradientRender)
            {
                m_pRenderer->removeChild(m_pGradientRender, true);
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
            m_pColorRender->setContentSize(m_size);
            m_pColorRender->setOpacity(m_nCOpacity);
            m_pColorRender->setColor(m_cColor);
            m_pRenderer->addChild(m_pColorRender,-2);
            break;
        case LAYOUT_COLOR_GRADIENT:
            m_pGradientRender = CCLayerGradient::create();
            m_pGradientRender->setContentSize(m_size);
            m_pGradientRender->setOpacity(m_nCOpacity);
            m_pGradientRender->setStartColor(m_gStartColor);
            m_pGradientRender->setEndColor(m_gEndColor);
            m_pGradientRender->setVector(m_AlongVector);
            m_pRenderer->addChild(m_pGradientRender,-2);
            break;
        default:
            break;
    }
}

void UILayout::setBackGroundColor(const ccColor3B &color)
{
    m_cColor = color;
    if (m_pColorRender)
    {
        m_pColorRender->setColor(color);
    }
}

void UILayout::setBackGroundColor(const ccColor3B &startColor, const ccColor3B &endColor)
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

void UILayout::setBackGroundColorOpacity(int opacity)
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

void UILayout::setBackGroundColorVector(const CCPoint &vector)
{
    m_AlongVector = vector;
    if (m_pGradientRender)
    {
        m_pGradientRender->setVector(vector);
    }
}

void UILayout::setColor(const ccColor3B &color)
{
    UIWidget::setColor(color);
    if (m_pBackGroundImage)
    {
        CCRGBAProtocol* rgbap = dynamic_cast<CCRGBAProtocol*>(m_pBackGroundImage);
        if (rgbap)
        {
            rgbap->setColor(color);
        }
    }
}

void UILayout::setOpacity(int opacity)
{
    UIWidget::setOpacity(opacity);
    if (m_pBackGroundImage)
    {
        CCRGBAProtocol* rgbap = dynamic_cast<CCRGBAProtocol*>(m_pBackGroundImage);
        if (rgbap)
        {
            rgbap->setOpacity(opacity);
        }
    }
}

const CCSize& UILayout::getBackGroundImageTextureSize() const
{
    return m_backGroundImageTextureSize;
}

const CCSize& UILayout::getContentSize() const
{
    return m_pRenderer->getContentSize();
}

void UILayout::setLayoutType(LayoutType type)
{
    m_eLayoutType = type;

    ccArray* layoutChildrenArray = getChildren()->data;
    int length = layoutChildrenArray->num;
    for (int i=0; i<length; i++)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(layoutChildrenArray->arr[i]);
        supplyTheLayoutParameterLackToChild(child);
    }
}

LayoutType UILayout::getLayoutType() const
{
    return m_eLayoutType;
}

void UILayout::doLayout()
{
    switch (m_eLayoutType)
    {
        case LAYOUT_ABSOLUTE:
            break;
        case LAYOUT_LINEAR_VERTICAL:
        {
            ccArray* layoutChildrenArray = getChildren()->data;
            int length = layoutChildrenArray->num;
            CCSize layoutSize = getSize();
            float topBoundary = layoutSize.height;
            for (int i=0; i<length; ++i)
            {
                UIWidget* child = dynamic_cast<UIWidget*>(layoutChildrenArray->arr[i]);
                UILinearLayoutParameter* layoutParameter = dynamic_cast<UILinearLayoutParameter*>(child->getLayoutParameter(LAYOUT_PARAMETER_LINEAR));
                
                if (layoutParameter)
                {
                    UILinearGravity childGravity = layoutParameter->getGravity();
                    CCPoint ap = child->getAnchorPoint();
                    CCSize cs = child->getSize();
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
                    child->setPosition(ccp(finalPosX, finalPosY));
                    topBoundary = child->getBottomInParent() - mg.bottom;
                }
            }
            break;
        }
        case LAYOUT_LINEAR_HORIZONTAL:
        {
            ccArray* layoutChildrenArray = getChildren()->data;
            int length = layoutChildrenArray->num;
            CCSize layoutSize = getSize();
            float leftBoundary = 0.0f;
            for (int i=0; i<length; ++i)
            {
                UIWidget* child = dynamic_cast<UIWidget*>(layoutChildrenArray->arr[i]);
                UILinearLayoutParameter* layoutParameter = dynamic_cast<UILinearLayoutParameter*>(child->getLayoutParameter(LAYOUT_PARAMETER_LINEAR));
                
                if (layoutParameter)
                {
                    UILinearGravity childGravity = layoutParameter->getGravity();
                    CCPoint ap = child->getAnchorPoint();
                    CCSize cs = child->getSize();
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
                    child->setPosition(ccp(finalPosX, finalPosY));
                    leftBoundary = child->getRightInParent() + mg.right;
                }
            }
            break;
        }
        case LAYOUT_RELATIVE:
        {
            ccArray* layoutChildrenArray = getChildren()->data;
            int length = layoutChildrenArray->num;
            int unlayoutChildCount = length;
            CCSize layoutSize = getSize();
            
            for (int i=0; i<length; i++)
            {
                UIWidget* child = dynamic_cast<UIWidget*>(layoutChildrenArray->arr[i]);
                UIRelativeLayoutParameter* layoutParameter = dynamic_cast<UIRelativeLayoutParameter*>(child->getLayoutParameter(LAYOUT_PARAMETER_RELATIVE));
                layoutParameter->m_bPut = false;
            }
            
            while (unlayoutChildCount > 0)
            {
                for (int i=0; i<length; i++)
                {
                    UIWidget* child = dynamic_cast<UIWidget*>(layoutChildrenArray->arr[i]);
                    UIRelativeLayoutParameter* layoutParameter = dynamic_cast<UIRelativeLayoutParameter*>(child->getLayoutParameter(LAYOUT_PARAMETER_RELATIVE));
                    
                    if (layoutParameter)
                    {
                        if (layoutParameter->m_bPut)
                        {
                            continue;
                        }
                        CCPoint ap = child->getAnchorPoint();
                        CCSize cs = child->getSize();
                        UIRelativeAlign align = layoutParameter->getAlign();
                        const char* relativeName = layoutParameter->getRelativeToWidgetName();
                        UIWidget* relativeWidget = NULL;
                        UIRelativeLayoutParameter* relativeWidgetLP = NULL;
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
                                    if (relativeWidgetLP && !relativeWidgetLP->m_bPut)
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
                                    if (relativeWidgetLP && !relativeWidgetLP->m_bPut)
                                    {
                                        continue;
                                    }
                                    CCSize rbs = relativeWidget->getSize();
                                    float locationBottom = relativeWidget->getTopInParent();
                                    
                                    finalPosY = locationBottom + ap.y * cs.height;
                                    finalPosX = relativeWidget->getLeftInParent() + rbs.width * 0.5f + ap.x * cs.width - cs.width * 0.5f;
                                }
                                break;
                            case RELATIVE_LOCATION_ABOVE_RIGHTALIGN:
                                if (relativeWidget)
                                {
                                    if (relativeWidgetLP && !relativeWidgetLP->m_bPut)
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
                                    if (relativeWidgetLP && !relativeWidgetLP->m_bPut)
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
                                    if (relativeWidgetLP && !relativeWidgetLP->m_bPut)
                                    {
                                        continue;
                                    }
                                    CCSize rbs = relativeWidget->getSize();
                                    float locationRight = relativeWidget->getLeftInParent();
                                    finalPosX = locationRight - (1.0f - ap.x) * cs.width;
                                    
                                    finalPosY = relativeWidget->getBottomInParent() + rbs.height * 0.5f + ap.y * cs.height - cs.height * 0.5f;
                                }
                                break;
                            case RELATIVE_LOCATION_LEFT_OF_BOTTOMALIGN:
                                if (relativeWidget)
                                {
                                    if (relativeWidgetLP && !relativeWidgetLP->m_bPut)
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
                                    if (relativeWidgetLP && !relativeWidgetLP->m_bPut)
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
                                    if (relativeWidgetLP && !relativeWidgetLP->m_bPut)
                                    {
                                        continue;
                                    }
                                    CCSize rbs = relativeWidget->getSize();
                                    float locationLeft = relativeWidget->getRightInParent();
                                    finalPosX = locationLeft + ap.x * cs.width;
                                    
                                    finalPosY = relativeWidget->getBottomInParent() + rbs.height * 0.5f + ap.y * cs.height - cs.height * 0.5f;
                                }
                                break;
                            case RELATIVE_LOCATION_RIGHT_OF_BOTTOMALIGN:
                                if (relativeWidget)
                                {
                                    if (relativeWidgetLP && !relativeWidgetLP->m_bPut)
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
                                    if (relativeWidgetLP && !relativeWidgetLP->m_bPut)
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
                                    if (relativeWidgetLP && !relativeWidgetLP->m_bPut)
                                    {
                                        continue;
                                    }
                                    CCSize rbs = relativeWidget->getSize();
                                    float locationTop = relativeWidget->getBottomInParent();
                                    
                                    finalPosY = locationTop - (1.0f - ap.y) * cs.height;
                                    finalPosX = relativeWidget->getLeftInParent() + rbs.width * 0.5f + ap.x * cs.width - cs.width * 0.5f;
                                }
                                break;
                            case RELATIVE_LOCATION_BELOW_RIGHTALIGN:
                                if (relativeWidget)
                                {
                                    if (relativeWidgetLP && !relativeWidgetLP->m_bPut)
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
                        child->setPosition(ccp(finalPosX, finalPosY));
                        layoutParameter->m_bPut = true;
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
        setBackGroundImageScale9Enabled(layout->m_bBackGroundScale9Enabled);
        setBackGroundImage(layout->m_strBackGroundImageFileName.c_str(),layout->m_eBGImageTexType);
        setBackGroundImageCapInsets(layout->m_backGroundImageCapInsets);
        setBackGroundColorType(layout->m_colorType);
        setBackGroundColor(layout->m_cColor);
        setBackGroundColor(layout->m_gStartColor, layout->m_gEndColor);
        setBackGroundColorOpacity(layout->m_nCOpacity);
        setBackGroundColorVector(layout->m_AlongVector);
        setLayoutType(layout->m_eLayoutType);
        setClippingEnabled(layout->m_bClippingEnabled);
    }
}

UIRectClippingNode::UIRectClippingNode():
m_pInnerStencil(NULL),
m_bEnabled(true),
m_clippingSize(CCSizeMake(50.0f, 50.0f)),
m_bClippingEnabled(false)
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
    m_pInnerStencil = CCDrawNode::create();
    rect[0] = ccp(0, 0);
    rect[1] = ccp(m_clippingSize.width, 0);
    rect[2] = ccp(m_clippingSize.width, m_clippingSize.height);
    rect[3] = ccp(0, m_clippingSize.height);
    
    ccColor4F green = {0, 1, 0, 1};
    m_pInnerStencil->drawPolygon(rect, 4, green, 0, green);
    if (CCClippingNode::init(m_pInnerStencil))
    {
        return true;
    }
    return false;
}


void UIRectClippingNode::setClippingSize(const cocos2d::CCSize &size)
{
    setContentSize(size);
    m_clippingSize = size;
    rect[0] = ccp(0, 0);
    rect[1] = ccp(m_clippingSize.width, 0);
    rect[2] = ccp(m_clippingSize.width, m_clippingSize.height);
    rect[3] = ccp(0, m_clippingSize.height);
    ccColor4F green = {0, 1, 0, 1};
    m_pInnerStencil->clear();
    m_pInnerStencil->drawPolygon(rect, 4, green, 0, green);
}

void UIRectClippingNode::setClippingEnabled(bool enabled)
{
    m_bClippingEnabled = enabled;
}

void UIRectClippingNode::visit()
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

void UIRectClippingNode::setEnabled(bool enabled)
{
    m_bEnabled = enabled;
}

bool UIRectClippingNode::isEnabled() const
{
    return m_bEnabled;
}

NS_CC_EXT_END