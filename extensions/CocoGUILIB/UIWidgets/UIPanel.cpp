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

#include "UIPanel.h"
#include "../../GUI/CCControlExtension/CCScale9Sprite.h"
#include "../Drawable/UIClippingLayer.h"


NS_CC_EXT_BEGIN

#define DYNAMIC_CAST_CLIPPINGLAYER dynamic_cast<UIClippingLayer*>(m_pRender)

UIPanel::UIPanel():
m_bBackGroundScale9Enable(false),
m_pBackGroundImage(NULL),
m_strBackGroundImageFileName(""),
m_backGroundImageCapInsets(CCRectZero),
m_eBGImageTexType(UI_TEX_TYPE_LOCAL)
{
    m_WidgetName = WIDGET_PANEL;
}

UIPanel* UIPanel::create()
{
    UIPanel* widget = new UIPanel();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

UIPanel::~UIPanel()
{
    
}

void UIPanel::initNodes()
{
    UIContainerWidget::initNodes();
    m_pBackGroundImage = CCSprite::create();
    m_pBackGroundImage->setZOrder(-1);
    m_pRender->addChild(m_pBackGroundImage);
}

void UIPanel::addBackGroundImage()
{
    if (m_bBackGroundScale9Enable)
    {
        m_pBackGroundImage = CCScale9Sprite::create();
        m_pBackGroundImage->setZOrder(-1);
        m_pRender->addChild(m_pBackGroundImage);
    }
    else
    {
        m_pBackGroundImage = CCSprite::create();
        m_pBackGroundImage->setZOrder(-1);
        m_pRender->addChild(m_pBackGroundImage);
    }
}

void UIPanel::removeBackGroundImage()
{
    m_pRender->removeChild(m_pBackGroundImage,  true);
    m_pBackGroundImage = NULL;
    m_strBackGroundImageFileName = "";
}

void UIPanel::setBackGroundImageScale9Enable(bool able)
{
    if (m_bBackGroundScale9Enable == able)
    {
        return;
    }
    m_pRender->removeChild(m_pBackGroundImage, true);
    m_pBackGroundImage = NULL;
    m_bBackGroundScale9Enable = able;
    if (m_bBackGroundScale9Enable)
    {
        m_pBackGroundImage = CCScale9Sprite::create();
        m_pRender->addChild(m_pBackGroundImage);
    }
    else
    {
        m_pBackGroundImage = CCSprite::create();
        m_pRender->addChild(m_pBackGroundImage);
    }
    m_pBackGroundImage->setZOrder(-1);
    setBackGroundImage(m_strBackGroundImageFileName.c_str(),m_eBGImageTexType);
    setBackGroundImageCapInsets(m_backGroundImageCapInsets);
}
    
void UIPanel::setSize(const CCSize &size)
{
    UIContainerWidget::setSize(size);
    if (m_pBackGroundImage == NULL)
    {
        addBackGroundImage();
    }
    m_pBackGroundImage->setPosition(ccp(m_pRender->getContentSize().width/2.0f, m_pRender->getContentSize().height/2.0f));
    if (m_bBackGroundScale9Enable)
    {
        dynamic_cast<CCScale9Sprite*>(m_pBackGroundImage)->setContentSize(m_pRender->getContentSize());
    }
}

/* gui mark */
CCNode* UIPanel::getBackGroundImage() const
{
    return m_pBackGroundImage;
}
/**/

void UIPanel::setBackGroundImage(const char* fileName,TextureResType texType)
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
                dynamic_cast<CCScale9Sprite*>(m_pBackGroundImage)->initWithFile(fileName);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<CCScale9Sprite*>(m_pBackGroundImage)->initWithSpriteFrameName(fileName);
                break;
            default:
                break;
        }
        dynamic_cast<CCScale9Sprite*>(m_pBackGroundImage)->setContentSize(m_pRender->getContentSize());
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
    if (m_bBackGroundScale9Enable)
    {
        dynamic_cast<CCScale9Sprite*>(m_pBackGroundImage)->setColor(getColor());
        dynamic_cast<CCScale9Sprite*>(m_pBackGroundImage)->setOpacity(getOpacity());
    }
    else
    {
        dynamic_cast<CCSprite*>(m_pBackGroundImage)->setColor(getColor());
        dynamic_cast<CCSprite*>(m_pBackGroundImage)->setOpacity(getOpacity());
    }
    m_pBackGroundImage->setPosition(ccp(m_pRender->getContentSize().width/2, m_pRender->getContentSize().height/2));
}

void UIPanel::setBackGroundImageCapInsets(const CCRect &capInsets)
{
    m_backGroundImageCapInsets = capInsets;
    if (m_bBackGroundScale9Enable)
    {
        dynamic_cast<CCScale9Sprite*>(m_pBackGroundImage)->setCapInsets(capInsets);
    }
}

void UIPanel::setBackGroundColorType(PanelColorType type)
{
    DYNAMIC_CAST_CLIPPINGLAYER->setColorType((UILayerColorType)type);
}

void UIPanel::setBackGroundColor(const ccColor3B &color)
{
    DYNAMIC_CAST_CLIPPINGLAYER->setBGColor(color);
}

void UIPanel::setBackGroundColor(const ccColor3B &startColor, const ccColor3B &endColor)
{
    UIClippingLayer * render = DYNAMIC_CAST_CLIPPINGLAYER;
    render->setBGStartColor(startColor);
    render->setBGEndColor(endColor);
}

void UIPanel::setBackGroundColorOpacity(int opacity)
{
    DYNAMIC_CAST_CLIPPINGLAYER->setBGColorOpacity(opacity);
}

void UIPanel::setBackGroundColorVector(const CCPoint &vector)
{
    DYNAMIC_CAST_CLIPPINGLAYER->setBGVector(vector);
}

void UIPanel::setColor(const ccColor3B &color)
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

void UIPanel::setOpacity(int opacity)
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

NS_CC_EXT_END