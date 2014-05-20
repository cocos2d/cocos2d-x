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

#include "UILayoutExecutant.h"
#include "UILayout.h"

NS_CC_BEGIN

namespace ui {

LinearVerticalLayoutExecutant* LinearVerticalLayoutExecutant::create()
{
    LinearVerticalLayoutExecutant* exe = new LinearVerticalLayoutExecutant();
    if (exe)
    {
        exe->autorelease();
        return exe;
    }
    CC_SAFE_DELETE(exe);
    return nullptr;
}

LinearHorizontalLayoutExecutant* LinearHorizontalLayoutExecutant::create()
{
    LinearHorizontalLayoutExecutant* exe = new LinearHorizontalLayoutExecutant();
    if (exe)
    {
        exe->autorelease();
        return exe;
    }
    CC_SAFE_DELETE(exe);
    return nullptr;
}

RelativeLayoutExecutant* RelativeLayoutExecutant::create()
{
    RelativeLayoutExecutant* exe = new RelativeLayoutExecutant();
    if (exe)
    {
        exe->autorelease();
        return exe;
    }
    CC_SAFE_DELETE(exe);
    return nullptr;
}

void LinearVerticalLayoutExecutant::doLayout(LayoutProtocol* layout)
{
    Size layoutSize = layout->getLayoutSize();
    Vector<Node*> container = layout->getLayoutChildren();
    float topBoundary = layoutSize.height;
    
    for (auto& subWidget : container)
    {
        LayoutParameterProtocol* child = dynamic_cast<LayoutParameterProtocol*>(subWidget);
        if (child)
        {
            LinearLayoutParameter* layoutParameter = dynamic_cast<LinearLayoutParameter*>(child->getLayoutParameter());
            
            if (layoutParameter)
            {
                LinearLayoutParameter::LinearGravity childGravity = layoutParameter->getGravity();
                Vec2 ap = subWidget->getAnchorPoint();
                Size cs = subWidget->getContentSize();
                float finalPosX = ap.x * cs.width;
                float finalPosY = topBoundary - ((1.0f-ap.y) * cs.height);
                switch (childGravity)
                {
                    case LinearLayoutParameter::LinearGravity::NONE:
                    case LinearLayoutParameter::LinearGravity::LEFT:
                        break;
                    case LinearLayoutParameter::LinearGravity::RIGHT:
                        finalPosX = layoutSize.width - ((1.0f - ap.x) * cs.width);
                        break;
                    case LinearLayoutParameter::LinearGravity::CENTER_HORIZONTAL:
                        finalPosX = layoutSize.width / 2.0f - cs.width * (0.5f-ap.x);
                        break;
                    default:
                        break;
                }
                Margin mg = layoutParameter->getMargin();
                finalPosX += mg.left;
                finalPosY -= mg.top;
                subWidget->setPosition(Vec2(finalPosX, finalPosY));
                topBoundary = subWidget->getPosition().y - subWidget->getAnchorPoint().y * subWidget->getContentSize().height - mg.bottom;
            }
        }
    }
}

void LinearHorizontalLayoutExecutant::doLayout(LayoutProtocol* layout)
{
    Size layoutSize = layout->getLayoutSize();
    Vector<Node*> container = layout->getLayoutChildren();
    float leftBoundary = 0.0f;
    for (auto& subWidget : container)
    {
        Widget* child = dynamic_cast<Widget*>(subWidget);
        if (child)
        {
            LinearLayoutParameter* layoutParameter = dynamic_cast<LinearLayoutParameter*>(child->getLayoutParameter());
            if (layoutParameter)
            {
                LinearLayoutParameter::LinearGravity childGravity = layoutParameter->getGravity();
                Vec2 ap = child->getAnchorPoint();
                Size cs = child->getSize();
                float finalPosX = leftBoundary + (ap.x * cs.width);
                float finalPosY = layoutSize.height - (1.0f - ap.y) * cs.height;
                switch (childGravity)
                {
                    case LinearLayoutParameter::LinearGravity::NONE:
                    case LinearLayoutParameter::LinearGravity::TOP:
                        break;
                    case LinearLayoutParameter::LinearGravity::BOTTOM:
                        finalPosY = ap.y * cs.height;
                        break;
                    case LinearLayoutParameter::LinearGravity::CENTER_VERTICAL:
                        finalPosY = layoutSize.height / 2.0f - cs.height * (0.5f - ap.y);
                        break;
                    default:
                        break;
                }
                Margin mg = layoutParameter->getMargin();
                finalPosX += mg.left;
                finalPosY -= mg.top;
                child->setPosition(Vec2(finalPosX, finalPosY));
                leftBoundary = child->getRightBoundary() + mg.right;
            }
        }
    }
}

void RelativeLayoutExecutant::doLayout(LayoutProtocol *layout)
{
    Size layoutSize = layout->getLayoutSize();
    Vector<Node*> container = layout->getLayoutChildren();
    ssize_t unlayoutChildCount = 0;
    Vector<Widget*> widgetChildren;
    for (auto& subWidget : container)
    {
        Widget* child = dynamic_cast<Widget*>(subWidget);
        if (child)
        {
            RelativeLayoutParameter* layoutParameter = dynamic_cast<RelativeLayoutParameter*>(child->getLayoutParameter());
            layoutParameter->_put = false;
            unlayoutChildCount++;
            widgetChildren.pushBack(child);
        }
    }
    while (unlayoutChildCount > 0)
    {
        for (auto& subWidget : widgetChildren)
        {
            Widget* child = static_cast<Widget*>(subWidget);
            RelativeLayoutParameter* layoutParameter = dynamic_cast<RelativeLayoutParameter*>(child->getLayoutParameter());
            
            if (layoutParameter)
            {
                if (layoutParameter->_put)
                {
                    continue;
                }
                Vec2 ap = child->getAnchorPoint();
                Size cs = child->getSize();
                RelativeLayoutParameter::RelativeAlign align = layoutParameter->getAlign();
                const std::string relativeName = layoutParameter->getRelativeToWidgetName();
                Widget* relativeWidget = nullptr;
                RelativeLayoutParameter* relativeWidgetLP = nullptr;
                float finalPosX = 0.0f;
                float finalPosY = 0.0f;
                if (!relativeName.empty())
                {
                    for (auto& sWidget : widgetChildren)
                    {
                        if (sWidget)
                        {
                            RelativeLayoutParameter* rlayoutParameter = dynamic_cast<RelativeLayoutParameter*>(sWidget->getLayoutParameter());
                            if (rlayoutParameter &&  rlayoutParameter->getRelativeName() == relativeName)
                            {
                                relativeWidget = sWidget;
                                relativeWidgetLP = rlayoutParameter;
                                break;
                            }
                        }
                    }
                }
                switch (align)
                {
                    case RelativeLayoutParameter::RelativeAlign::NONE:
                    case RelativeLayoutParameter::RelativeAlign::PARENT_TOP_LEFT:
                        finalPosX = ap.x * cs.width;
                        finalPosY = layoutSize.height - ((1.0f - ap.y) * cs.height);
                        break;
                    case RelativeLayoutParameter::RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL:
                        finalPosX = layoutSize.width * 0.5f - cs.width * (0.5f - ap.x);
                        finalPosY = layoutSize.height - ((1.0f - ap.y) * cs.height);
                        break;
                    case RelativeLayoutParameter::RelativeAlign::PARENT_TOP_RIGHT:
                        finalPosX = layoutSize.width - ((1.0f - ap.x) * cs.width);
                        finalPosY = layoutSize.height - ((1.0f - ap.y) * cs.height);
                        break;
                    case RelativeLayoutParameter::RelativeAlign::PARENT_LEFT_CENTER_VERTICAL:
                        finalPosX = ap.x * cs.width;
                        finalPosY = layoutSize.height * 0.5f - cs.height * (0.5f - ap.y);
                        break;
                    case RelativeLayoutParameter::RelativeAlign::CENTER_IN_PARENT:
                        finalPosX = layoutSize.width * 0.5f - cs.width * (0.5f - ap.x);
                        finalPosY = layoutSize.height * 0.5f - cs.height * (0.5f - ap.y);
                        break;
                    case RelativeLayoutParameter::RelativeAlign::PARENT_RIGHT_CENTER_VERTICAL:
                        finalPosX = layoutSize.width - ((1.0f - ap.x) * cs.width);
                        finalPosY = layoutSize.height * 0.5f - cs.height * (0.5f - ap.y);
                        break;
                    case RelativeLayoutParameter::RelativeAlign::PARENT_LEFT_BOTTOM:
                        finalPosX = ap.x * cs.width;
                        finalPosY = ap.y * cs.height;
                        break;
                    case RelativeLayoutParameter::RelativeAlign::PARENT_BOTTOM_CENTER_HORIZONTAL:
                        finalPosX = layoutSize.width * 0.5f - cs.width * (0.5f - ap.x);
                        finalPosY = ap.y * cs.height;
                        break;
                    case RelativeLayoutParameter::RelativeAlign::PARENT_RIGHT_BOTTOM:
                        finalPosX = layoutSize.width - ((1.0f - ap.x) * cs.width);
                        finalPosY = ap.y * cs.height;
                        break;
                        
                    case RelativeLayoutParameter::RelativeAlign::LOCATION_ABOVE_LEFTALIGN:
                        if (relativeWidget)
                        {
                            if (relativeWidgetLP && !relativeWidgetLP->_put)
                            {
                                continue;
                            }
                            float locationTop = relativeWidget->getTopBoundary();
                            float locationLeft = relativeWidget->getLeftBoundary();
                            finalPosY = locationTop + ap.y * cs.height;
                            finalPosX = locationLeft + ap.x * cs.width;
                        }
                        break;
                    case RelativeLayoutParameter::RelativeAlign::LOCATION_ABOVE_CENTER:
                        if (relativeWidget)
                        {
                            if (relativeWidgetLP && !relativeWidgetLP->_put)
                            {
                                continue;
                            }
                            Size rbs = relativeWidget->getSize();
                            float locationTop = relativeWidget->getTopBoundary();
                            
                            finalPosY = locationTop + ap.y * cs.height;
                            finalPosX = relativeWidget->getLeftBoundary() + rbs.width * 0.5f + ap.x * cs.width - cs.width * 0.5f;
                        }
                        break;
                    case RelativeLayoutParameter::RelativeAlign::LOCATION_ABOVE_RIGHTALIGN:
                        if (relativeWidget)
                        {
                            if (relativeWidgetLP && !relativeWidgetLP->_put)
                            {
                                continue;
                            }
                            float locationTop = relativeWidget->getTopBoundary();
                            float locationRight = relativeWidget->getRightBoundary();
                            finalPosY = locationTop + ap.y * cs.height;
                            finalPosX = locationRight - (1.0f - ap.x) * cs.width;
                        }
                        break;
                    case RelativeLayoutParameter::RelativeAlign::LOCATION_LEFT_OF_TOPALIGN:
                        if (relativeWidget)
                        {
                            if (relativeWidgetLP && !relativeWidgetLP->_put)
                            {
                                continue;
                            }
                            float locationTop = relativeWidget->getTopBoundary();
                            float locationLeft = relativeWidget->getLeftBoundary();
                            finalPosY = locationTop - (1.0f - ap.y) * cs.height;
                            finalPosX = locationLeft - (1.0f - ap.x) * cs.width;
                        }
                        break;
                    case RelativeLayoutParameter::RelativeAlign::LOCATION_LEFT_OF_CENTER:
                        if (relativeWidget)
                        {
                            if (relativeWidgetLP && !relativeWidgetLP->_put)
                            {
                                continue;
                            }
                            Size rbs = relativeWidget->getSize();
                            float locationLeft = relativeWidget->getLeftBoundary();
                            finalPosX = locationLeft - (1.0f - ap.x) * cs.width;
                            
                            finalPosY = relativeWidget->getBottomBoundary() + rbs.height * 0.5f + ap.y * cs.height - cs.height * 0.5f;
                        }
                        break;
                    case RelativeLayoutParameter::RelativeAlign::LOCATION_LEFT_OF_BOTTOMALIGN:
                        if (relativeWidget)
                        {
                            if (relativeWidgetLP && !relativeWidgetLP->_put)
                            {
                                continue;
                            }
                            float locationBottom = relativeWidget->getBottomBoundary();
                            float locationLeft = relativeWidget->getLeftBoundary();
                            finalPosY = locationBottom + ap.y * cs.height;
                            finalPosX = locationLeft - (1.0f - ap.x) * cs.width;
                        }
                        break;
                    case RelativeLayoutParameter::RelativeAlign::LOCATION_RIGHT_OF_TOPALIGN:
                        if (relativeWidget)
                        {
                            if (relativeWidgetLP && !relativeWidgetLP->_put)
                            {
                                continue;
                            }
                            float locationTop = relativeWidget->getTopBoundary();
                            float locationRight = relativeWidget->getRightBoundary();
                            finalPosY = locationTop - (1.0f - ap.y) * cs.height;
                            finalPosX = locationRight + ap.x * cs.width;
                        }
                        break;
                    case RelativeLayoutParameter::RelativeAlign::LOCATION_RIGHT_OF_CENTER:
                        if (relativeWidget)
                        {
                            if (relativeWidgetLP && !relativeWidgetLP->_put)
                            {
                                continue;
                            }
                            Size rbs = relativeWidget->getSize();
                            float locationRight = relativeWidget->getRightBoundary();
                            finalPosX = locationRight + ap.x * cs.width;
                            
                            finalPosY = relativeWidget->getBottomBoundary() + rbs.height * 0.5f + ap.y * cs.height - cs.height * 0.5f;
                        }
                        break;
                    case RelativeLayoutParameter::RelativeAlign::LOCATION_RIGHT_OF_BOTTOMALIGN:
                        if (relativeWidget)
                        {
                            if (relativeWidgetLP && !relativeWidgetLP->_put)
                            {
                                continue;
                            }
                            float locationBottom = relativeWidget->getBottomBoundary();
                            float locationRight = relativeWidget->getRightBoundary();
                            finalPosY = locationBottom + ap.y * cs.height;
                            finalPosX = locationRight + ap.x * cs.width;
                        }
                        break;
                    case RelativeLayoutParameter::RelativeAlign::LOCATION_BELOW_LEFTALIGN:
                        if (relativeWidget)
                        {
                            if (relativeWidgetLP && !relativeWidgetLP->_put)
                            {
                                continue;
                            }
                            float locationBottom = relativeWidget->getBottomBoundary();
                            float locationLeft = relativeWidget->getLeftBoundary();
                            finalPosY = locationBottom - (1.0f - ap.y) * cs.height;
                            finalPosX = locationLeft + ap.x * cs.width;
                        }
                        break;
                    case RelativeLayoutParameter::RelativeAlign::LOCATION_BELOW_CENTER:
                        if (relativeWidget)
                        {
                            if (relativeWidgetLP && !relativeWidgetLP->_put)
                            {
                                continue;
                            }
                            Size rbs = relativeWidget->getSize();
                            float locationBottom = relativeWidget->getBottomBoundary();
                            
                            finalPosY = locationBottom - (1.0f - ap.y) * cs.height;
                            finalPosX = relativeWidget->getLeftBoundary() + rbs.width * 0.5f + ap.x * cs.width - cs.width * 0.5f;
                        }
                        break;
                    case RelativeLayoutParameter::RelativeAlign::LOCATION_BELOW_RIGHTALIGN:
                        if (relativeWidget)
                        {
                            if (relativeWidgetLP && !relativeWidgetLP->_put)
                            {
                                continue;
                            }
                            float locationBottom = relativeWidget->getBottomBoundary();
                            float locationRight = relativeWidget->getRightBoundary();
                            finalPosY = locationBottom - (1.0f - ap.y) * cs.height;
                            finalPosX = locationRight - (1.0f - ap.x) * cs.width;
                        }
                        break;
                    default:
                        break;
                }
                Margin relativeWidgetMargin;
                Margin mg = layoutParameter->getMargin();
                if (relativeWidgetLP)
                {
                    relativeWidgetMargin = relativeWidgetLP->getMargin();
                }
                //handle margin
                switch (align)
                {
                    case RelativeLayoutParameter::RelativeAlign::NONE:
                    case RelativeLayoutParameter::RelativeAlign::PARENT_TOP_LEFT:
                        finalPosX += mg.left;
                        finalPosY -= mg.top;
                        break;
                    case RelativeLayoutParameter::RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL:
                        finalPosY -= mg.top;
                        break;
                    case RelativeLayoutParameter::RelativeAlign::PARENT_TOP_RIGHT:
                        finalPosX -= mg.right;
                        finalPosY -= mg.top;
                        break;
                    case RelativeLayoutParameter::RelativeAlign::PARENT_LEFT_CENTER_VERTICAL:
                        finalPosX += mg.left;
                        break;
                    case RelativeLayoutParameter::RelativeAlign::CENTER_IN_PARENT:
                        break;
                    case RelativeLayoutParameter::RelativeAlign::PARENT_RIGHT_CENTER_VERTICAL:
                        finalPosX -= mg.right;
                        break;
                    case RelativeLayoutParameter::RelativeAlign::PARENT_LEFT_BOTTOM:
                        finalPosX += mg.left;
                        finalPosY += mg.bottom;
                        break;
                    case RelativeLayoutParameter::RelativeAlign::PARENT_BOTTOM_CENTER_HORIZONTAL:
                        finalPosY += mg.bottom;
                        break;
                    case RelativeLayoutParameter::RelativeAlign::PARENT_RIGHT_BOTTOM:
                        finalPosX -= mg.right;
                        finalPosY += mg.bottom;
                        break;
                        
                    case RelativeLayoutParameter::RelativeAlign::LOCATION_ABOVE_LEFTALIGN:
                        finalPosY += mg.bottom;
                        finalPosX += mg.left;
                        break;
                    case RelativeLayoutParameter::RelativeAlign::LOCATION_ABOVE_RIGHTALIGN:
                        finalPosY += mg.bottom;
                        finalPosX -= mg.right;
                        break;
                    case RelativeLayoutParameter::RelativeAlign::LOCATION_ABOVE_CENTER:
                        finalPosY += mg.bottom;
                        break;
                        
                    case RelativeLayoutParameter::RelativeAlign::LOCATION_LEFT_OF_TOPALIGN:
                        finalPosX -= mg.right;
                        finalPosY -= mg.top;
                        break;
                    case RelativeLayoutParameter::RelativeAlign::LOCATION_LEFT_OF_BOTTOMALIGN:
                        finalPosX -= mg.right;
                        finalPosY += mg.bottom;
                        break;
                    case RelativeLayoutParameter::RelativeAlign::LOCATION_LEFT_OF_CENTER:
                        finalPosX -= mg.right;
                        break;
                        
                    case RelativeLayoutParameter::RelativeAlign::LOCATION_RIGHT_OF_TOPALIGN:
                        finalPosX += mg.left;
                        finalPosY -= mg.top;
                        break;
                    case RelativeLayoutParameter::RelativeAlign::LOCATION_RIGHT_OF_BOTTOMALIGN:
                        finalPosX += mg.left;
                        finalPosY += mg.bottom;
                        break;
                    case RelativeLayoutParameter::RelativeAlign::LOCATION_RIGHT_OF_CENTER:
                        finalPosX += mg.left;
                        break;
                        
                    case RelativeLayoutParameter::RelativeAlign::LOCATION_BELOW_LEFTALIGN:
                        finalPosY -= mg.top;
                        finalPosX += mg.left;
                        break;
                    case RelativeLayoutParameter::RelativeAlign::LOCATION_BELOW_RIGHTALIGN:
                        finalPosY -= mg.top;
                        finalPosX -= mg.right;
                        break;
                    case RelativeLayoutParameter::RelativeAlign::LOCATION_BELOW_CENTER:
                        finalPosY -= mg.top;
                        break;
                    default:
                        break;
                }
                child->setPosition(Vec2(finalPosX, finalPosY));
                layoutParameter->_put = true;
                unlayoutChildCount--;
            }
        }
    }
    widgetChildren.clear();
}

}

NS_CC_END