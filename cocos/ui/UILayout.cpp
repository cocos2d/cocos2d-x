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

#include "ui/UILayout.h"
#include "ui/UIHelper.h"
#include "extensions/GUI/CCControlExtension/CCScale9Sprite.h"
#include "kazmath/GL/matrix.h"
#include "CCGLProgram.h"
#include "CCShaderCache.h"
#include "CCDirector.h"
#include "CCDrawingPrimitives.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCGroupCommand.h"
#include "renderer/CCCustomCommand.h"

NS_CC_BEGIN

namespace ui {
    
class LayoutExecutant : public Ref
{
public:
    LayoutExecutant(){};
    virtual ~LayoutExecutant(){};
    static LayoutExecutant* create();
    virtual void doLayout(const Size& layoutSize, Vector<Node*> container){};
};

class LinearVerticalLayoutExecutant : public LayoutExecutant
{
public:
    LinearVerticalLayoutExecutant(){};
    virtual ~LinearVerticalLayoutExecutant(){};
    static LinearVerticalLayoutExecutant* create();
    virtual void doLayout(const Size& layoutSize, Vector<Node*> container);
};

class LinearHorizontalLayoutExecutant : public LayoutExecutant
{
public:
    LinearHorizontalLayoutExecutant(){};
    virtual ~LinearHorizontalLayoutExecutant(){};
    static LinearHorizontalLayoutExecutant* create();
    virtual void doLayout(const Size& layoutSize, Vector<Node*> container);
};

class RelativeLayoutExecutant : public LayoutExecutant
{
public:
    RelativeLayoutExecutant(){};
    virtual ~RelativeLayoutExecutant(){};
    static RelativeLayoutExecutant* create();
    virtual void doLayout(const Size& layoutSize, Vector<Node*> container);
};
    
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
        Widget* child = dynamic_cast<Widget*>(subWidget);
        if (child)
        {
            LinearLayoutParameter* layoutParameter = dynamic_cast<LinearLayoutParameter*>(child->getLayoutParameter(LAYOUT_PARAMETER_LINEAR));
            
            if (layoutParameter)
            {
                LinearGravity childGravity = layoutParameter->getGravity();
                Point ap = child->getAnchorPoint();
                Size cs = child->getSize();
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
                child->setPosition(Point(finalPosX, finalPosY));
                topBoundary = child->getBottomInParent() - mg.bottom;
            }
        }
    }
}
    
void LinearHorizontalLayoutExecutant::doLayout(const cocos2d::Size &layoutSize, Vector<cocos2d::Node *> container)
{
    float leftBoundary = 0.0f;
    for (auto& subWidget : container)
    {
        Widget* child = dynamic_cast<Widget*>(subWidget);
        if (child)
        {
            LinearLayoutParameter* layoutParameter = dynamic_cast<LinearLayoutParameter*>(child->getLayoutParameter(LAYOUT_PARAMETER_LINEAR));
            if (layoutParameter)
            {
                LinearGravity childGravity = layoutParameter->getGravity();
                Point ap = child->getAnchorPoint();
                Size cs = child->getSize();
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
                child->setPosition(Point(finalPosX, finalPosY));
                leftBoundary = child->getRightInParent() + mg.right;
            }
        }
    }
}

void RelativeLayoutExecutant::doLayout(const cocos2d::Size &layoutSize, Vector<cocos2d::Node *> container)
{
    ssize_t unlayoutChildCount = 0;
    Vector<Widget*> widgetChildren;
    for (auto& subWidget : container)
    {
        Widget* child = dynamic_cast<Widget*>(subWidget);
        if (child)
        {
            RelativeLayoutParameter* layoutParameter = dynamic_cast<RelativeLayoutParameter*>(child->getLayoutParameter(LAYOUT_PARAMETER_RELATIVE));
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
            RelativeLayoutParameter* layoutParameter = dynamic_cast<RelativeLayoutParameter*>(child->getLayoutParameter(LAYOUT_PARAMETER_RELATIVE));
            
            if (layoutParameter)
            {
                if (layoutParameter->_put)
                {
                    continue;
                }
                Point ap = child->getAnchorPoint();
                Size cs = child->getSize();
                RelativeAlign align = layoutParameter->getAlign();
                const char* relativeName = layoutParameter->getRelativeToWidgetName();
                Widget* relativeWidget = nullptr;
                RelativeLayoutParameter* relativeWidgetLP = nullptr;
                float finalPosX = 0.0f;
                float finalPosY = 0.0f;
                if (relativeName && strcmp(relativeName, ""))
                {
                    for (auto& sWidget : widgetChildren)
                    {
                        if (sWidget)
                        {
                            RelativeLayoutParameter* rlayoutParameter = dynamic_cast<RelativeLayoutParameter*>(sWidget->getLayoutParameter(LAYOUT_PARAMETER_RELATIVE));
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
                            Size rbs = relativeWidget->getSize();
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
                            Size rbs = relativeWidget->getSize();
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
                            Size rbs = relativeWidget->getSize();
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
                            Size rbs = relativeWidget->getSize();
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
                child->setPosition(Point(finalPosX, finalPosY));
                layoutParameter->_put = true;
                unlayoutChildCount--;
            }
        }
    }
    widgetChildren.clear();
}
    
static const int BACKGROUNDIMAGE_Z = (-1);
static const int BCAKGROUNDCOLORRENDERER_Z = (-2);

static GLint g_sStencilBits = -1;
static GLint s_layer = -1;
    
IMPLEMENT_CLASS_GUI_INFO(Layout)

Layout::Layout():
_clippingEnabled(false),
_backGroundScale9Enabled(false),
_backGroundImage(nullptr),
_backGroundImageFileName(""),
_backGroundImageCapInsets(Rect::ZERO),
_colorType(LAYOUT_COLOR_NONE),
_bgImageTexType(UI_TEX_TYPE_LOCAL),
_colorRender(nullptr),
_gradientRender(nullptr),
_cColor(Color3B::WHITE),
_gStartColor(Color3B::WHITE),
_gEndColor(Color3B::WHITE),
_alongVector(Point(0.0f, -1.0f)),
_cOpacity(255),
_backGroundImageTextureSize(Size::ZERO),
_layoutType(LAYOUT_ABSOLUTE),
_clippingType(LAYOUT_CLIPPING_STENCIL),
_clippingStencil(nullptr),
_scissorRectDirty(false),
_clippingRect(Rect::ZERO),
_clippingParent(nullptr),
_doLayoutDirty(true),
_clippingRectDirty(true),
_currentStencilEnabled(GL_FALSE),
_currentStencilWriteMask(~0),
_currentStencilFunc(GL_ALWAYS),
_currentStencilRef(0),
_currentStencilValueMask(~0),
_currentStencilFail(GL_KEEP),
_currentStencilPassDepthFail(GL_KEEP),
_currentStencilPassDepthPass(GL_KEEP),
_currentDepthWriteMask(GL_TRUE),
_currentAlphaTestEnabled(GL_FALSE),
_currentAlphaTestFunc(GL_ALWAYS),
_currentAlphaTestRef(1),
_backGroundImageColor(Color3B::WHITE),
_backGroundImageOpacity(255),
_curLayoutExecutant(nullptr)
{
    _widgetType = WidgetTypeContainer;
}

Layout::~Layout()
{
    CC_SAFE_RELEASE(_clippingStencil);
    CC_SAFE_RELEASE(_curLayoutExecutant);
}
    
void Layout::onEnter()
{
    Widget::onEnter();
    if (_clippingStencil)
    {
        _clippingStencil->onEnter();
    }
    _doLayoutDirty = true;
    _clippingRectDirty = true;
}
    
void Layout::onExit()
{
    Widget::onExit();
    if (_clippingStencil)
    {
        _clippingStencil->onExit();
    }
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
    return nullptr;
}

bool Layout::init()
{
    if (ProtectedNode::init())
    {
        initRenderer();
        setBright(true);
        ignoreContentAdaptWithSize(false);
        setSize(Size::ZERO);
        setAnchorPoint(Point::ZERO);
        return true;
    }
    return false;
}
    
void Layout::addChild(Node *child)
{
    Widget::addChild(child);
}

void Layout::addChild(Node * child, int zOrder)
{
    Widget::addChild(child, zOrder);
}

void Layout::addChild(Node *child, int zOrder, int tag)
{
    supplyTheLayoutParameterLackToChild(static_cast<Widget*>(child));
    Widget::addChild(child, zOrder, tag);
    _doLayoutDirty = true;
}
    
void Layout::removeChild(Node *child, bool cleanup)
{
    Widget::removeChild(child, cleanup);
    _doLayoutDirty = true;
}
    
void Layout::removeAllChildren()
{
    Widget::removeAllChildren();
}
    
void Layout::removeAllChildrenWithCleanup(bool cleanup)
{
    Widget::removeAllChildrenWithCleanup(cleanup);
    _doLayoutDirty = true;
}

bool Layout::isClippingEnabled()
{
    return _clippingEnabled;
}

void Layout::visit(Renderer *renderer, const kmMat4 &parentTransform, bool parentTransformUpdated)
{
    if (!_enabled)
    {
        return;
    }
    adaptRenderers();
    if (_clippingEnabled)
    {
        switch (_clippingType)
        {
            case LAYOUT_CLIPPING_STENCIL:
                stencilClippingVisit(renderer, parentTransform, parentTransformUpdated);
                break;
            case LAYOUT_CLIPPING_SCISSOR:
                scissorClippingVisit(renderer, parentTransform, parentTransformUpdated);
                break;
            default:
                break;
        }
    }
    else
    {
        ProtectedNode::visit(renderer, parentTransform, parentTransformUpdated);
    }
}
    
void Layout::sortAllChildren()
{
    Widget::sortAllChildren();
    doLayout();
}
    
void Layout::stencilClippingVisit(Renderer *renderer, const kmMat4 &parentTransform, bool parentTransformUpdated)
{
    if(!_visible)
        return;
    
    bool dirty = parentTransformUpdated || _transformUpdated;
    if(dirty)
        _modelViewTransform = transform(parentTransform);
    _transformUpdated = false;

    // IMPORTANT:
    // To ease the migration to v3.0, we still support the kmGL stack,
    // but it is deprecated and your code should not rely on it
    kmGLPushMatrix();
    kmGLLoadMatrix(&_modelViewTransform);

    //Add group command

    _groupCommand.init(_globalZOrder);
    renderer->addCommand(&_groupCommand);
    
    renderer->pushGroup(_groupCommand.getRenderQueueID());
    
    _beforeVisitCmdStencil.init(_globalZOrder);
    _beforeVisitCmdStencil.func = CC_CALLBACK_0(Layout::onBeforeVisitStencil, this);
    renderer->addCommand(&_beforeVisitCmdStencil);
    
    _clippingStencil->visit(renderer, _modelViewTransform, dirty);
    
    _afterDrawStencilCmd.init(_globalZOrder);
    _afterDrawStencilCmd.func = CC_CALLBACK_0(Layout::onAfterDrawStencil, this);
    renderer->addCommand(&_afterDrawStencilCmd);
    
    int i = 0;      // used by _children
    int j = 0;      // used by _protectedChildren
    
    sortAllChildren();
    sortAllProtectedChildren();
    
    //
    // draw children and protectedChildren zOrder < 0
    //
    for( ; i < _children.size(); i++ )
    {
        auto node = _children.at(i);
        
        if ( node && node->getLocalZOrder() < 0 )
            node->visit(renderer, _modelViewTransform, dirty);
        else
            break;
    }
    
    for( ; j < _protectedChildren.size(); j++ )
    {
        auto node = _protectedChildren.at(j);
        
        if ( node && node->getLocalZOrder() < 0 )
            node->visit(renderer, _modelViewTransform, dirty);
        else
            break;
    }
    
    //
    // draw self
    //
    this->draw(renderer, _modelViewTransform, dirty);
    
    //
    // draw children and protectedChildren zOrder >= 0
    //
    for(auto it=_protectedChildren.cbegin()+j; it != _protectedChildren.cend(); ++it)
        (*it)->visit(renderer, _modelViewTransform, dirty);
    
    for(auto it=_children.cbegin()+i; it != _children.cend(); ++it)
        (*it)->visit(renderer, _modelViewTransform, dirty);

    
    _afterVisitCmdStencil.init(_globalZOrder);
    _afterVisitCmdStencil.func = CC_CALLBACK_0(Layout::onAfterVisitStencil, this);
    renderer->addCommand(&_afterVisitCmdStencil);
    
    renderer->popGroup();
    
    kmGLPopMatrix();
}
    
void Layout::onBeforeVisitStencil()
{
    s_layer++;
    GLint mask_layer = 0x1 << s_layer;
    GLint mask_layer_l = mask_layer - 1;
    _mask_layer_le = mask_layer | mask_layer_l;
    _currentStencilEnabled = glIsEnabled(GL_STENCIL_TEST);
    glGetIntegerv(GL_STENCIL_WRITEMASK, (GLint *)&_currentStencilWriteMask);
    glGetIntegerv(GL_STENCIL_FUNC, (GLint *)&_currentStencilFunc);
    glGetIntegerv(GL_STENCIL_REF, &_currentStencilRef);
    glGetIntegerv(GL_STENCIL_VALUE_MASK, (GLint *)&_currentStencilValueMask);
    glGetIntegerv(GL_STENCIL_FAIL, (GLint *)&_currentStencilFail);
    glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL, (GLint *)&_currentStencilPassDepthFail);
    glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS, (GLint *)&_currentStencilPassDepthPass);
    
    glEnable(GL_STENCIL_TEST);
    CHECK_GL_ERROR_DEBUG();
    glStencilMask(mask_layer);
    glGetBooleanv(GL_DEPTH_WRITEMASK, &_currentDepthWriteMask);
    glDepthMask(GL_FALSE);
    glStencilFunc(GL_NEVER, mask_layer, mask_layer);
    glStencilOp(GL_ZERO, GL_KEEP, GL_KEEP);
    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLPushMatrix();
    kmGLLoadIdentity();
    
    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLPushMatrix();
    kmGLLoadIdentity();
    
    DrawPrimitives::drawSolidRect(Point(-1,-1), Point(1,1), Color4F(1, 1, 1, 1));
    
    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLPopMatrix();
    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLPopMatrix();
    glStencilFunc(GL_NEVER, mask_layer, mask_layer);
    glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);
}

void Layout::onAfterDrawStencil()
{
    glDepthMask(_currentDepthWriteMask);
    glStencilFunc(GL_EQUAL, _mask_layer_le, _mask_layer_le);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
}


void Layout::onAfterVisitStencil()
{
    glStencilFunc(_currentStencilFunc, _currentStencilRef, _currentStencilValueMask);
    glStencilOp(_currentStencilFail, _currentStencilPassDepthFail, _currentStencilPassDepthPass);
    glStencilMask(_currentStencilWriteMask);
    if (!_currentStencilEnabled)
    {
        glDisable(GL_STENCIL_TEST);
    }
    s_layer--;
}
    
void Layout::onBeforeVisitScissor()
{
    Rect clippingRect = getClippingRect();
    glEnable(GL_SCISSOR_TEST);
    auto glview = Director::getInstance()->getOpenGLView();
    glview->setScissorInPoints(clippingRect.origin.x, clippingRect.origin.y, clippingRect.size.width, clippingRect.size.height);
}

void Layout::onAfterVisitScissor()
{
    glDisable(GL_SCISSOR_TEST);
}
    
void Layout::scissorClippingVisit(Renderer *renderer, const kmMat4& parentTransform, bool parentTransformUpdated)
{
    _beforeVisitCmdScissor.init(_globalZOrder);
    _beforeVisitCmdScissor.func = CC_CALLBACK_0(Layout::onBeforeVisitScissor, this);
    renderer->addCommand(&_beforeVisitCmdScissor);

    ProtectedNode::visit(renderer, parentTransform, parentTransformUpdated);
    
    _afterVisitCmdScissor.init(_globalZOrder);
    _afterVisitCmdScissor.func = CC_CALLBACK_0(Layout::onAfterVisitScissor, this);
    renderer->addCommand(&_afterVisitCmdScissor);
}

void Layout::setClippingEnabled(bool able)
{
    if (able == _clippingEnabled)
    {
        return;
    }
    _clippingEnabled = able;
    switch (_clippingType)
    {
        case LAYOUT_CLIPPING_STENCIL:
            if (able)
            {
                static bool once = true;
                if (once)
                {
                    glGetIntegerv(GL_STENCIL_BITS, &g_sStencilBits);
                    if (g_sStencilBits <= 0)
                    {
                        CCLOG("Stencil buffer is not enabled.");
                    }
                    once = false;
                }
                _clippingStencil = DrawNode::create();
                if (_running)
                {
                    _clippingStencil->onEnter();
                }
                _clippingStencil->retain();
                setStencilClippingSize(_size);
            }
            else
            {
                if (_running)
                {
                    _clippingStencil->onExit();
                }
                _clippingStencil->release();
                _clippingStencil = nullptr;
            }
            break;
        default:
            break;
    }
}
    
void Layout::setClippingType(LayoutClippingType type)
{
    if (type == _clippingType)
    {
        return;
    }
    bool clippingEnabled = isClippingEnabled();
    setClippingEnabled(false);
    _clippingType = type;
    setClippingEnabled(clippingEnabled);
}
    
LayoutClippingType Layout::getClippingType()
{
    return _clippingType;
}
    
void Layout::setStencilClippingSize(const Size &size)
{
    if (_clippingEnabled && _clippingType == LAYOUT_CLIPPING_STENCIL)
    {
        Point rect[4];
        rect[0] = Point::ZERO;
        rect[1] = Point(_size.width, 0);
        rect[2] = Point(_size.width, _size.height);
        rect[3] = Point(0, _size.height);
        Color4F green(0, 1, 0, 1);
        _clippingStencil->clear();
        _clippingStencil->drawPolygon(rect, 4, green, 0, green);
    }
}
    
const Rect& Layout::getClippingRect()
{
    if (_clippingRectDirty)
    {
        Point worldPos = convertToWorldSpace(Point::ZERO);
        AffineTransform t = getNodeToWorldAffineTransform();
        float scissorWidth = _size.width*t.a;
        float scissorHeight = _size.height*t.d;
        Rect parentClippingRect;
        Layout* parent = this;

        while (parent)
        {
            parent = dynamic_cast<Layout*>(parent->getParent());
            if(parent)
            {
                if (parent->isClippingEnabled())
                {
                    _clippingParent = parent;
                    break;
                }
            }
        }
        
        if (_clippingParent)
        {
            parentClippingRect = _clippingParent->getClippingRect();
            float finalX = worldPos.x - (scissorWidth * _anchorPoint.x);
            float finalY = worldPos.y - (scissorHeight * _anchorPoint.y);
            float finalWidth = scissorWidth;
            float finalHeight = scissorHeight;
            
            float leftOffset = worldPos.x - parentClippingRect.origin.x;
            if (leftOffset < 0.0f)
            {
                finalX = parentClippingRect.origin.x;
                finalWidth += leftOffset;
            }
            float rightOffset = (worldPos.x + scissorWidth) - (parentClippingRect.origin.x + parentClippingRect.size.width);
            if (rightOffset > 0.0f)
            {
                finalWidth -= rightOffset;
            }
            float topOffset = (worldPos.y + scissorHeight) - (parentClippingRect.origin.y + parentClippingRect.size.height);
            if (topOffset > 0.0f)
            {
                finalHeight -= topOffset;
            }
            float bottomOffset = worldPos.y - parentClippingRect.origin.y;
            if (bottomOffset < 0.0f)
            {
                finalY = parentClippingRect.origin.x;
                finalHeight += bottomOffset;
            }
            if (finalWidth < 0.0f)
            {
                finalWidth = 0.0f;
            }
            if (finalHeight < 0.0f)
            {
                finalHeight = 0.0f;
            }
            _clippingRect.origin.x = finalX;
            _clippingRect.origin.y = finalY;
            _clippingRect.size.width = finalWidth;
            _clippingRect.size.height = finalHeight;
        }
        else
        {
            _clippingRect.origin.x = worldPos.x - (scissorWidth * _anchorPoint.x);
            _clippingRect.origin.y = worldPos.y - (scissorHeight * _anchorPoint.y);
            _clippingRect.size.width = scissorWidth;
            _clippingRect.size.height = scissorHeight;
        }
        _clippingRectDirty = false;
    }
    return _clippingRect;
}

void Layout::onSizeChanged()
{
    Widget::onSizeChanged();
    setStencilClippingSize(_size);
    _doLayoutDirty = true;
    _clippingRectDirty = true;
    if (_backGroundImage)
    {
        _backGroundImage->setPosition(Point(_size.width/2.0f, _size.height/2.0f));
        if (_backGroundScale9Enabled && _backGroundImage)
        {
            static_cast<extension::Scale9Sprite*>(_backGroundImage)->setPreferredSize(_size);
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
    removeProtectedChild(_backGroundImage);
    _backGroundImage = nullptr;
    _backGroundScale9Enabled = able;
    addBackGroundImage();
    setBackGroundImage(_backGroundImageFileName,_bgImageTexType);
    setBackGroundImageCapInsets(_backGroundImageCapInsets);
}
    
bool Layout::isBackGroundImageScale9Enabled()
{
    return _backGroundScale9Enabled;
}

void Layout::setBackGroundImage(const std::string& fileName,TextureResType texType)
{
    if (fileName.empty())
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
        extension::Scale9Sprite* bgiScale9 = static_cast<extension::Scale9Sprite*>(_backGroundImage);
        switch (_bgImageTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                bgiScale9->initWithFile(fileName);
                break;
            case UI_TEX_TYPE_PLIST:
                bgiScale9->initWithSpriteFrameName(fileName);
                break;
            default:
                break;
        }
        bgiScale9->setPreferredSize(_size);
    }
    else
    {
        switch (_bgImageTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                static_cast<Sprite*>(_backGroundImage)->setTexture(fileName);
                break;
            case UI_TEX_TYPE_PLIST:
                static_cast<Sprite*>(_backGroundImage)->setSpriteFrame(fileName);
                break;
            default:
                break;
        }
    }
    _backGroundImageTextureSize = _backGroundImage->getContentSize();
    _backGroundImage->setPosition(Point(_size.width/2.0f, _size.height/2.0f));
    updateBackGroundImageRGBA();
}

void Layout::setBackGroundImageCapInsets(const Rect &capInsets)
{
    _backGroundImageCapInsets = capInsets;
    if (_backGroundScale9Enabled && _backGroundImage)
    {
        static_cast<extension::Scale9Sprite*>(_backGroundImage)->setCapInsets(capInsets);
    }
}
    
const Rect& Layout::getBackGroundImageCapInsets()
{
    return _backGroundImageCapInsets;
}

void Layout::supplyTheLayoutParameterLackToChild(Widget *child)
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
            LinearLayoutParameter* layoutParameter = dynamic_cast<LinearLayoutParameter*>(child->getLayoutParameter(LAYOUT_PARAMETER_LINEAR));
            if (!layoutParameter)
            {
                child->setLayoutParameter(LinearLayoutParameter::create());
            }
            break;
        }
        case LAYOUT_RELATIVE:
        {
            RelativeLayoutParameter* layoutParameter = dynamic_cast<RelativeLayoutParameter*>(child->getLayoutParameter(LAYOUT_PARAMETER_RELATIVE));
            if (!layoutParameter)
            {
                child->setLayoutParameter(RelativeLayoutParameter::create());
            }
            break;
        }
        default:
            break;
    }
}

void Layout::addBackGroundImage()
{
    if (_backGroundScale9Enabled)
    {
        _backGroundImage = extension::Scale9Sprite::create();
        addProtectedChild(_backGroundImage, BACKGROUNDIMAGE_Z, -1);
        static_cast<extension::Scale9Sprite*>(_backGroundImage)->setPreferredSize(_size);
    }
    else
    {
        _backGroundImage = Sprite::create();
        addProtectedChild(_backGroundImage, BACKGROUNDIMAGE_Z, -1);
    }
    _backGroundImage->setPosition(Point(_size.width/2.0f, _size.height/2.0f));
}

void Layout::removeBackGroundImage()
{
    if (!_backGroundImage)
    {
        return;
    }
    removeProtectedChild(_backGroundImage);
    _backGroundImage = nullptr;
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
                removeProtectedChild(_colorRender);
                _colorRender = nullptr;
            }
            if (_gradientRender)
            {
                removeProtectedChild(_gradientRender);
                _gradientRender = nullptr;
            }
            break;
        case LAYOUT_COLOR_SOLID:
            if (_colorRender)
            {
                removeProtectedChild(_colorRender);
                _colorRender = nullptr;
            }
            break;
        case LAYOUT_COLOR_GRADIENT:
            if (_gradientRender)
            {
                removeProtectedChild(_gradientRender);
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
            _colorRender = LayerColor::create();
            _colorRender->setContentSize(_size);
            _colorRender->setOpacity(_cOpacity);
            _colorRender->setColor(_cColor);
            addProtectedChild(_colorRender, BCAKGROUNDCOLORRENDERER_Z, -1);
            break;
        case LAYOUT_COLOR_GRADIENT:
            _gradientRender = LayerGradient::create();
            _gradientRender->setContentSize(_size);
            _gradientRender->setOpacity(_cOpacity);
            _gradientRender->setStartColor(_gStartColor);
            _gradientRender->setEndColor(_gEndColor);
            _gradientRender->setVector(_alongVector);
            addProtectedChild(_gradientRender, BCAKGROUNDCOLORRENDERER_Z, -1);
            break;
        default:
            break;
    }
}
    
LayoutBackGroundColorType Layout::getBackGroundColorType()
{
    return _colorType;
}

void Layout::setBackGroundColor(const Color3B &color)
{
    _cColor = color;
    if (_colorRender)
    {
        _colorRender->setColor(color);
    }
}
    
const Color3B& Layout::getBackGroundColor()
{
    return _cColor;
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
    
const Color3B& Layout::getBackGroundStartColor()
{
    return _gStartColor;
}

const Color3B& Layout::getBackGroundEndColor()
{
    return _gEndColor;
}

void Layout::setBackGroundColorOpacity(GLubyte opacity)
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
    
GLubyte Layout::getBackGroundColorOpacity()
{
    return _cOpacity;
}

void Layout::setBackGroundColorVector(const Point &vector)
{
    _alongVector = vector;
    if (_gradientRender)
    {
        _gradientRender->setVector(vector);
    }
}
    
const Point& Layout::getBackGroundColorVector()
{
    return _alongVector;
}

void Layout::setBackGroundImageColor(const Color3B &color)
{
    _backGroundImageColor = color;
    updateBackGroundImageColor();
}

void Layout::setBackGroundImageOpacity(GLubyte opacity)
{
    _backGroundImageOpacity = opacity;
    updateBackGroundImageOpacity();
}

const Color3B& Layout::getBackGroundImageColor()
{
    return _backGroundImageColor;
}

GLubyte Layout::getBackGroundImageOpacity()
{
    return _backGroundImageOpacity;
}

void Layout::updateBackGroundImageColor()
{
    if (_backGroundImage)
    {
        _backGroundImage->setColor(_backGroundImageColor);
    }
}

void Layout::updateBackGroundImageOpacity()
{
    if (_backGroundImage)
    {
        _backGroundImage->setOpacity(_backGroundImageOpacity);
    }
}

void Layout::updateBackGroundImageRGBA()
{
    if (_backGroundImage)
    {
        _backGroundImage->setColor(_backGroundImageColor);
        _backGroundImage->setOpacity(_backGroundImageOpacity);
    }
}

const Size& Layout::getBackGroundImageTextureSize() const
{
    return _backGroundImageTextureSize;
}

void Layout::setLayoutType(LayoutType type)
{
    _layoutType = type;
    CC_SAFE_RELEASE_NULL(_curLayoutExecutant);
    _curLayoutExecutant = createCurrentLayoutExecutant();
    CC_SAFE_RETAIN(_curLayoutExecutant);
    for (auto& child : _children)
    {
        Widget* widgetChild = dynamic_cast<Widget*>(child);
        if (widgetChild)
        {
            supplyTheLayoutParameterLackToChild(static_cast<Widget*>(child));
        }
    }
    _doLayoutDirty = true;
}
    
LayoutExecutant* Layout::createCurrentLayoutExecutant()
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

LayoutType Layout::getLayoutType() const
{
    return _layoutType;
}
    
void Layout::requestDoLayout()
{
    _doLayoutDirty = true;
}

void Layout::doLayout()
{
    if (!_doLayoutDirty)
    {
        return;
    }
    if (_curLayoutExecutant)
    {
        _curLayoutExecutant->doLayout(getSize(), getChildren());
    }
    _doLayoutDirty = false;
}

std::string Layout::getDescription() const
{
    return "Layout";
}

Widget* Layout::createCloneInstance()
{
    return Layout::create();
}

void Layout::copyClonedWidgetChildren(Widget* model)
{
    Widget::copyClonedWidgetChildren(model);
}

void Layout::copySpecialProperties(Widget *widget)
{
    Layout* layout = dynamic_cast<Layout*>(widget);
    if (layout)
    {
        setBackGroundImageScale9Enabled(layout->_backGroundScale9Enabled);
        setBackGroundImage(layout->_backGroundImageFileName,layout->_bgImageTexType);
        setBackGroundImageCapInsets(layout->_backGroundImageCapInsets);
        setBackGroundColorType(layout->_colorType);
        setBackGroundColor(layout->_cColor);
        setBackGroundColor(layout->_gStartColor, layout->_gEndColor);
        setBackGroundColorOpacity(layout->_cOpacity);
        setBackGroundColorVector(layout->_alongVector);
        setLayoutType(layout->_layoutType);
        setClippingEnabled(layout->_clippingEnabled);
        setClippingType(layout->_clippingType);
    }
}
}
NS_CC_END
