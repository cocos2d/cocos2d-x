//
//  CCLayoutProtocol.cpp
//  cocos2d_libs
//
//  Created by cai wenzhi on 14-5-7.
//
//

#include "layout/CCLayoutProtocol.h"
#include "layout/CCLayoutParameterProtocol.h"


NS_CC_BEGIN

namespace layout{
    
static LayoutParameter* getLayoutParameterFromNode(cocos2d::Node *node, LayoutParameterType type)
{
    LayoutParameterProtocol* lpp = dynamic_cast<LayoutParameterProtocol*>(node);
    if (lpp)
    {
        return lpp->getLayoutParameter(type);
    }
    return nullptr;
}

static float getLeftInParentFromNode(cocos2d::Node* node)
{
    return node->getPosition().x - node->getAnchorPoint().x * node->getContentSize().width;;
}

static float getBottomInParentFromNode(cocos2d::Node* node)
{
    return node->getPosition().y - node->getAnchorPoint().y * node->getContentSize().height;;
}

static float getRightInParentFromNode(cocos2d::Node* node)
{
    return getLeftInParentFromNode(node) + node->getContentSize().width;
}

static float getTopInParentFromNode(cocos2d::Node* node)
{
    return getBottomInParentFromNode(node) + node->getContentSize().height;
}


LayoutExecutant* LayoutExecutant::create()
{
    LayoutExecutant* exe = new LayoutExecutant();
    if (exe)
    {
        exe->autorelease();
        return exe;
    }
    CC_SAFE_DELETE(exe);
    return nullptr;
}

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

void LinearVerticalLayoutExecutant::doLayout(const cocos2d::Size &layoutSize, Vector<cocos2d::Node *> container)
{
    float topBoundary = layoutSize.height;
    
    for (auto& subWidget : container)
    {
        LinearLayoutParameter* layoutParameter = dynamic_cast<LinearLayoutParameter*>(getLayoutParameterFromNode(subWidget, LAYOUT_PARAMETER_LINEAR));
        if (layoutParameter)
        {
            LinearGravity childGravity = layoutParameter->getGravity();
            Vector2 ap = subWidget->getAnchorPoint();
            Size cs = subWidget->getContentSize();
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
            Margin mg = layoutParameter->getMargin();
            finalPosX += mg.left;
            finalPosY -= mg.top;
            subWidget->setPosition(Vector2(finalPosX, finalPosY));
            topBoundary = getBottomInParentFromNode(subWidget) - mg.bottom;
        }
    }
}

void LinearHorizontalLayoutExecutant::doLayout(const cocos2d::Size &layoutSize, Vector<cocos2d::Node *> container)
{
    float leftBoundary = 0.0f;
    for (auto& subWidget : container)
    {
        LinearLayoutParameter* layoutParameter = dynamic_cast<LinearLayoutParameter*>(getLayoutParameterFromNode(subWidget, LAYOUT_PARAMETER_LINEAR));
        if (layoutParameter)
        {
            LinearGravity childGravity = layoutParameter->getGravity();
            Vector2 ap = subWidget->getAnchorPoint();
            Size cs = subWidget->getContentSize();
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
            Margin mg = layoutParameter->getMargin();
            finalPosX += mg.left;
            finalPosY -= mg.top;
            subWidget->setPosition(Vector2(finalPosX, finalPosY));
            leftBoundary = getRightInParentFromNode(subWidget) + mg.right;
        }
    }
}

void RelativeLayoutExecutant::doLayout(const cocos2d::Size &layoutSize, Vector<cocos2d::Node *> container)
{
    ssize_t unlayoutChildCount = container.size();
    while (unlayoutChildCount > 0)
    {
        for (auto& subWidget : container)
        {
            RelativeLayoutParameter* layoutParameter = dynamic_cast<RelativeLayoutParameter*>(getLayoutParameterFromNode(subWidget, LAYOUT_PARAMETER_RELATIVE));
            
            if (layoutParameter)
            {
                if (layoutParameter->_put)
                {
                    continue;
                }
                Vector2 ap = subWidget->getAnchorPoint();
                Size cs = subWidget->getContentSize();
                RelativeAlign align = layoutParameter->getAlign();
                const char* relativeName = layoutParameter->getRelativeToWidgetName();
                Node* relativeWidget = nullptr;
                RelativeLayoutParameter* relativeWidgetLP = nullptr;
                float finalPosX = 0.0f;
                float finalPosY = 0.0f;
                if (relativeName && strcmp(relativeName, ""))
                {
                    for (auto& sWidget : container)
                    {
                        if (sWidget)
                        {
                            RelativeLayoutParameter* rlayoutParameter = dynamic_cast<RelativeLayoutParameter*>(getLayoutParameterFromNode(sWidget, LAYOUT_PARAMETER_RELATIVE));
                            if (rlayoutParameter && strcmp(rlayoutParameter->getRelativeName(), relativeName) == 0)
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
                            float locationBottom = getTopInParentFromNode(relativeWidget);
                            float locationLeft = getLeftInParentFromNode(relativeWidget);
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
                            Size rbs = relativeWidget->getContentSize();
                            float locationBottom = getTopInParentFromNode(relativeWidget);
                            
                            finalPosY = locationBottom + ap.y * cs.height;
                            finalPosX = getLeftInParentFromNode(relativeWidget) + rbs.width * 0.5f + ap.x * cs.width - cs.width * 0.5f;
                        }
                        break;
                    case RELATIVE_LOCATION_ABOVE_RIGHTALIGN:
                        if (relativeWidget)
                        {
                            if (relativeWidgetLP && !relativeWidgetLP->_put)
                            {
                                continue;
                            }
                            float locationBottom = getTopInParentFromNode(relativeWidget);
                            float locationRight = getRightInParentFromNode(relativeWidget);
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
                            float locationTop = getTopInParentFromNode(relativeWidget);
                            float locationRight = getLeftInParentFromNode(relativeWidget);
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
                            Size rbs = relativeWidget->getContentSize();
                            float locationRight = getLeftInParentFromNode(relativeWidget);
                            finalPosX = locationRight - (1.0f - ap.x) * cs.width;
                            
                            finalPosY = getBottomInParentFromNode(relativeWidget) + rbs.height * 0.5f + ap.y * cs.height - cs.height * 0.5f;
                        }
                        break;
                    case RELATIVE_LOCATION_LEFT_OF_BOTTOMALIGN:
                        if (relativeWidget)
                        {
                            if (relativeWidgetLP && !relativeWidgetLP->_put)
                            {
                                continue;
                            }
                            float locationBottom = getBottomInParentFromNode(relativeWidget);
                            float locationRight = getLeftInParentFromNode(relativeWidget);
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
                            float locationTop = getTopInParentFromNode(relativeWidget);
                            float locationLeft = getRightInParentFromNode(relativeWidget);
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
                            Size rbs = relativeWidget->getContentSize();
                            float locationLeft = getRightInParentFromNode(relativeWidget);
                            finalPosX = locationLeft + ap.x * cs.width;
                            
                            finalPosY = getBottomInParentFromNode(relativeWidget) + rbs.height * 0.5f + ap.y * cs.height - cs.height * 0.5f;
                        }
                        break;
                    case RELATIVE_LOCATION_RIGHT_OF_BOTTOMALIGN:
                        if (relativeWidget)
                        {
                            if (relativeWidgetLP && !relativeWidgetLP->_put)
                            {
                                continue;
                            }
                            float locationBottom = getBottomInParentFromNode(relativeWidget);
                            float locationLeft = getRightInParentFromNode(relativeWidget);
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
                            float locationTop = getBottomInParentFromNode(relativeWidget);
                            float locationLeft = getLeftInParentFromNode(relativeWidget);
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
                            Size rbs = relativeWidget->getContentSize();
                            float locationTop = getBottomInParentFromNode(relativeWidget);
                            
                            finalPosY = locationTop - (1.0f - ap.y) * cs.height;
                            finalPosX = getLeftInParentFromNode(relativeWidget) + rbs.width * 0.5f + ap.x * cs.width - cs.width * 0.5f;
                        }
                        break;
                    case RELATIVE_LOCATION_BELOW_RIGHTALIGN:
                        if (relativeWidget)
                        {
                            if (relativeWidgetLP && !relativeWidgetLP->_put)
                            {
                                continue;
                            }
                            float locationTop = getBottomInParentFromNode(relativeWidget);
                            float locationRight = getRightInParentFromNode(relativeWidget);
                            finalPosY = locationTop - (1.0f - ap.y) * cs.height;
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
                        finalPosX += mg.left;
                        break;
                    case RELATIVE_LOCATION_ABOVE_RIGHTALIGN:
                        finalPosY += mg.bottom;
                        finalPosX -= mg.right;
                        break;
                    case RELATIVE_LOCATION_ABOVE_CENTER:
                        finalPosY += mg.bottom;
                        break;
                        
                    case RELATIVE_LOCATION_LEFT_OF_TOPALIGN:
                        finalPosX -= mg.right;
                        finalPosY -= mg.top;
                        break;
                    case RELATIVE_LOCATION_LEFT_OF_BOTTOMALIGN:
                        finalPosX -= mg.right;
                        finalPosY += mg.bottom;
                        break;
                    case RELATIVE_LOCATION_LEFT_OF_CENTER:
                        finalPosX -= mg.right;
                        break;
                        
                    case RELATIVE_LOCATION_RIGHT_OF_TOPALIGN:
                        finalPosX += mg.left;
                        finalPosY -= mg.top;
                        break;
                    case RELATIVE_LOCATION_RIGHT_OF_BOTTOMALIGN:
                        finalPosX += mg.left;
                        finalPosY += mg.bottom;
                        break;
                    case RELATIVE_LOCATION_RIGHT_OF_CENTER:
                        finalPosX += mg.left;
                        break;
                        
                    case RELATIVE_LOCATION_BELOW_LEFTALIGN:
                        finalPosY -= mg.top;
                        finalPosX += mg.left;
                        break;
                    case RELATIVE_LOCATION_BELOW_RIGHTALIGN:
                        finalPosY -= mg.top;
                        finalPosX -= mg.right;
                        break;
                    case RELATIVE_LOCATION_BELOW_CENTER:
                        finalPosY -= mg.top;
                        break;
                    default:
                        break;
                }
                subWidget->setPosition(Vector2(finalPosX, finalPosY));
                layoutParameter->_put = true;
                unlayoutChildCount--;
            }
        }
    }
}
    
void LayoutProtocol::setLayoutType(LayoutType type)
{
    _layoutType = type;
    CC_SAFE_RELEASE_NULL(_curLayoutExecutant);
    _curLayoutExecutant = createCurrentLayoutExecutant();
    CC_SAFE_RETAIN(_curLayoutExecutant);
}

LayoutExecutant* LayoutProtocol::createCurrentLayoutExecutant()
{
    LayoutExecutant* exe = nullptr;
    switch (_layoutType)
    {
        case LAYOUT_LINEAR_VERTICAL:
            exe = LinearVerticalLayoutExecutant::create();
            break;
        case LAYOUT_LINEAR_HORIZONTAL:
            exe = LinearHorizontalLayoutExecutant::create();
            break;
        case LAYOUT_RELATIVE:
            exe = RelativeLayoutExecutant::create();
            break;
        default:
            break;
    }
    return exe;
}

LayoutType LayoutProtocol::getLayoutType() const
{
    return _layoutType;
}

void LayoutProtocol::doLayout(const Size& layoutSize, Vector<Node*> container)
{
    if (_curLayoutExecutant)
    {
        _curLayoutExecutant->doLayout(layoutSize, container);
    }
}
    
}

NS_CC_END