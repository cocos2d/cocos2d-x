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

#include "LayoutExecutant.h"
#include "Layout.h"
#include "../System/UIHelper.h"

NS_CC_EXT_BEGIN

void LayoutExecutant::setLayout(Layout *layout)
{
    m_pLayout = layout;
}

Layout* LayoutExecutant::getLayout() const
{
    return m_pLayout;
}

LinearVerticalLayoutExecutant* LinearVerticalLayoutExecutant::create()
{
    LinearVerticalLayoutExecutant* executant = new LinearVerticalLayoutExecutant();
    if (executant)
    {
        executant->autorelease();
        return executant;
    }
    CC_SAFE_DELETE(executant);
    return NULL;
}

LinearHorizontalLayoutExecutant* LinearHorizontalLayoutExecutant::create()
{
    LinearHorizontalLayoutExecutant* executant = new LinearHorizontalLayoutExecutant();
    if (executant)
    {
        executant->autorelease();
        return executant;
    }
    CC_SAFE_DELETE(executant);
    return NULL;
}

RelativeLayoutExecutant* RelativeLayoutExecutant::create()
{
    RelativeLayoutExecutant* executant = new RelativeLayoutExecutant();
    if (executant)
    {
        executant->autorelease();
        return executant;
    }
    CC_SAFE_DELETE(executant);
    return NULL;
}

void LinearVerticalLayoutExecutant::doLayout()
{
    if (m_pLayout)
    {
        ccArray* layoutChildrenArray = m_pLayout->getChildren()->data;
        int length = layoutChildrenArray->num;
        CCSize layoutSize = m_pLayout->getSize();
        float topBoundary = layoutSize.height;
        for (int i=0; i<length; ++i)
        {
            UIWidget* child = dynamic_cast<UIWidget*>(layoutChildrenArray->arr[i]);
            LinearLayoutParameter* layoutParameter = dynamic_cast<LinearLayoutParameter*>(child->getLayoutParameter());
            
            if (layoutParameter)
            {
                WidgetType childType = child->getWidgetType();
                UILinearGravity childGravity = layoutParameter->getGravity();
                CCPoint ap = child->getAnchorPoint();
                CCSize cs = child->getSize();
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
                child->setPosition(ccp(finalPosX, finalPosY));
                topBoundary = child->getBottomInParent() - mg.bottom;
            }
        }
    }
}

void LinearHorizontalLayoutExecutant::doLayout()
{
    if (m_pLayout)
    {
        ccArray* layoutChildrenArray = m_pLayout->getChildren()->data;
        int length = layoutChildrenArray->num;
        CCSize layoutSize = m_pLayout->getSize();
        float leftBoundary = 0.0f;
        for (int i=0; i<length; ++i)
        {
            UIWidget* child = dynamic_cast<UIWidget*>(layoutChildrenArray->arr[i]);
            LinearLayoutParameter* layoutParameter = dynamic_cast<LinearLayoutParameter*>(child->getLayoutParameter());
            
            if (layoutParameter)
            {
                WidgetType childType = child->getWidgetType();
                UILinearGravity childGravity = layoutParameter->getGravity();
                CCPoint ap = child->getAnchorPoint();
                CCSize cs = child->getSize();
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
                child->setPosition(ccp(finalPosX, finalPosY));
                leftBoundary = child->getRightInParent() + mg.right;
            }
        }
    }
}

void RelativeLayoutExecutant::doLayout()
{
    if (m_pLayout)
    {
        ccArray* layoutChildrenArray = m_pLayout->getChildren()->data;
        int length = layoutChildrenArray->num;
        CCSize layoutSize = m_pLayout->getSize();
        for (int i=0; i<length; i++)
        {
            UIWidget* child = dynamic_cast<UIWidget*>(layoutChildrenArray->arr[i]);
            WidgetType childType = child->getWidgetType();
            CCPoint ap = child->getAnchorPoint();
            CCSize cs = child->getSize();
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
                    relativeWidget = CCUIHELPER->seekWidgetByRelativeName(m_pLayout, relativeName);
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
                child->setPosition(ccp(finalPosX, finalPosY));
            }
        }
    }
}

NS_CC_EXT_END