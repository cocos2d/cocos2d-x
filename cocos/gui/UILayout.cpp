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
#include "gui/UIHelper.h"
#include "extensions/GUI/CCControlExtension/CCScale9Sprite.h"

NS_CC_BEGIN

namespace gui {

static GLint g_sStencilBits = -1;

UILayout::UILayout():
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
_handleScissor(false),
_scissorRectDirty(false),
_clippingRect(Rect::ZERO),
_clippingParent(nullptr),
_doLayoutDirty(true)
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
    _layoutParameterDictionary = Dictionary::create();
    CC_SAFE_RETAIN(_layoutParameterDictionary);
    initRenderer();
    _renderer->retain();
    setCascadeColorEnabled(true);
    setCascadeOpacityEnabled(true);
    setBright(true);
    ignoreContentAdaptWithSize(false);
    setSize(Size::ZERO);
    setAnchorPoint(Point::ZERO);
    return true;
}
    
void UILayout::addChild(Node *child)
{
    UIWidget::addChild(child);
}

void UILayout::addChild(Node * child, int zOrder)
{
    UIWidget::addChild(child, zOrder);
}

void UILayout::addChild(Node *child, int zOrder, int tag)
{
    supplyTheLayoutParameterLackToChild(dynamic_cast<UIWidget*>(child));
    UIWidget::addChild(child, zOrder, tag);
}
    
void UILayout::initRenderer()
{
    UIWidget::initRenderer();
}

bool UILayout::isClippingEnabled()
{
    return _clippingEnabled;
}
    
void UILayout::visit()
{
    if (!_enabled)
    {
        return;
    }
    if (_clippingEnabled)
    {
        switch (_clippingType)
        {
            case LAYOUT_CLIPPING_STENCIL:
                stencilClippingVisit();
                break;
            case LAYOUT_CLIPPING_SCISSOR:
                scissorClippingVisit();
                break;
            default:
                break;
        }
    }
    else
    {
        NodeRGBA::visit();
    }
}
    
void UILayout::sortAllChildren()
{
    UIWidget::sortAllChildren();
    doLayout();
}
    
void UILayout::stencilClippingVisit()
{
    if (!_clippingStencil || !_clippingStencil->isVisible())
    {
        NodeRGBA::visit();
        return;
    }
    if (g_sStencilBits < 1)
    {
        NodeRGBA::visit();
        return;
    }
    static GLint layer = -1;
    if (layer + 1 == g_sStencilBits)
    {
        static bool once = true;
        if (once)
        {
            char warning[200] = {0};
            snprintf(warning, sizeof(warning), "Nesting more than %d stencils is not supported. Everything will be drawn without stencil for this node and its childs.", g_sStencilBits);
            CCLOG("%s", warning);
            
            once = false;
        }
        NodeRGBA::visit();
        return;
    }
    layer++;
    GLint mask_layer = 0x1 << layer;
    GLint mask_layer_l = mask_layer - 1;
    GLint mask_layer_le = mask_layer | mask_layer_l;
    GLboolean currentStencilEnabled = GL_FALSE;
    GLuint currentStencilWriteMask = ~0;
    GLenum currentStencilFunc = GL_ALWAYS;
    GLint currentStencilRef = 0;
    GLuint currentStencilValueMask = ~0;
    GLenum currentStencilFail = GL_KEEP;
    GLenum currentStencilPassDepthFail = GL_KEEP;
    GLenum currentStencilPassDepthPass = GL_KEEP;
    currentStencilEnabled = glIsEnabled(GL_STENCIL_TEST);
    glGetIntegerv(GL_STENCIL_WRITEMASK, (GLint *)&currentStencilWriteMask);
    glGetIntegerv(GL_STENCIL_FUNC, (GLint *)&currentStencilFunc);
    glGetIntegerv(GL_STENCIL_REF, &currentStencilRef);
    glGetIntegerv(GL_STENCIL_VALUE_MASK, (GLint *)&currentStencilValueMask);
    glGetIntegerv(GL_STENCIL_FAIL, (GLint *)&currentStencilFail);
    glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL, (GLint *)&currentStencilPassDepthFail);
    glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS, (GLint *)&currentStencilPassDepthPass);
    glEnable(GL_STENCIL_TEST);
    CHECK_GL_ERROR_DEBUG();
    glStencilMask(mask_layer);
    GLboolean currentDepthWriteMask = GL_TRUE;
    glGetBooleanv(GL_DEPTH_WRITEMASK, &currentDepthWriteMask);
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
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WINDOWS || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    GLboolean currentAlphaTestEnabled = GL_FALSE;
    GLenum currentAlphaTestFunc = GL_ALWAYS;
    GLclampf currentAlphaTestRef = 1;
#endif
    kmGLPushMatrix();
    transform();
    _clippingStencil->visit();
    kmGLPopMatrix();
    glDepthMask(currentDepthWriteMask);
    glStencilFunc(GL_EQUAL, mask_layer_le, mask_layer_le);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    NodeRGBA::visit();
    glStencilFunc(currentStencilFunc, currentStencilRef, currentStencilValueMask);
    glStencilOp(currentStencilFail, currentStencilPassDepthFail, currentStencilPassDepthPass);
    glStencilMask(currentStencilWriteMask);
    if (!currentStencilEnabled)
    {
        glDisable(GL_STENCIL_TEST);
    }
    layer--;
}
    
void UILayout::scissorClippingVisit()
{
    Rect clippingRect = getClippingRect();
    if (_handleScissor)
    {
        glEnable(GL_SCISSOR_TEST);
    }
    EGLView::getInstance()->setScissorInPoints(clippingRect.origin.x, clippingRect.origin.y, clippingRect.size.width, clippingRect.size.height);
    NodeRGBA::visit();
    if (_handleScissor)
    {
        glDisable(GL_SCISSOR_TEST);
    }
}

void UILayout::setClippingEnabled(bool able)
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
                glGetIntegerv(GL_STENCIL_BITS, &g_sStencilBits);
                _clippingStencil = DrawNode::create();
                _clippingStencil->onEnter();
                _clippingStencil->retain();
                setStencilClippingSize(_size);
            }
            else
            {
                _clippingStencil->onExit();
                _clippingStencil->release();
                _clippingStencil = nullptr;
            }
            break;
        default:
            break;
    }
}
    
void UILayout::setClippingType(LayoutClippingType type)
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
    
void UILayout::setStencilClippingSize(const Size &size)
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
    
const Rect& UILayout::getClippingRect()
{
    _handleScissor = true;
    Point worldPos = convertToWorldSpace(Point::ZERO);
    AffineTransform t = nodeToWorldTransform();
    float scissorWidth = _size.width*t.a;
    float scissorHeight = _size.height*t.d;
    Rect parentClippingRect;
    UILayout* parent = this;
    bool firstClippingParentFounded = false;
    while (parent)
    {
        parent = dynamic_cast<UILayout*>(parent->getParent());
        if(parent)
        {
            if (parent->isClippingEnabled())
            {
                if (!firstClippingParentFounded)
                {
                    _clippingParent = parent;
                    firstClippingParentFounded = true;
                }
                
                if (parent->_clippingType == LAYOUT_CLIPPING_SCISSOR)
                {
                    _handleScissor = false;
                    break;
                }
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
    return _clippingRect;
}

void UILayout::onSizeChanged()
{
    setStencilClippingSize(_size);
    for (auto& child : getChildren())
    {
        if (child)
        {
            ((UIWidget*)child)->updateSizeAndPosition();
        }
    }
    _doLayoutDirty = true;
    if (_backGroundImage)
    {
        _backGroundImage->setPosition(Point(_size.width/2.0f, _size.height/2.0f));
        if (_backGroundScale9Enabled && _backGroundImage)
        {
            dynamic_cast<extension::Scale9Sprite*>(_backGroundImage)->setPreferredSize(_size);
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
        _backGroundImage = extension::Scale9Sprite::create();
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
                dynamic_cast<extension::Scale9Sprite*>(_backGroundImage)->initWithFile(fileName);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<extension::Scale9Sprite*>(_backGroundImage)->initWithSpriteFrameName(fileName);
                break;
            default:
                break;
        }
        dynamic_cast<extension::Scale9Sprite*>(_backGroundImage)->setPreferredSize(_size);
    }
    else
    {
        switch (_bgImageTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<Sprite*>(_backGroundImage)->setTexture(fileName);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<Sprite*>(_backGroundImage)->setSpriteFrame(fileName);
                break;
            default:
                break;
        }
    }
    if (_backGroundScale9Enabled)
    {
        dynamic_cast<extension::Scale9Sprite*>(_backGroundImage)->setColor(getColor());
        dynamic_cast<extension::Scale9Sprite*>(_backGroundImage)->setOpacity(getOpacity());
    }
    else
    {
        dynamic_cast<Sprite*>(_backGroundImage)->setColor(getColor());
        dynamic_cast<Sprite*>(_backGroundImage)->setOpacity(getOpacity());
    }
    _backGroundImageTextureSize = _backGroundImage->getContentSize();
    _backGroundImage->setPosition(Point(_size.width/2.0f, _size.height/2.0f));
}

void UILayout::setBackGroundImageCapInsets(const Rect &capInsets)
{
    _backGroundImageCapInsets = capInsets;
    if (_backGroundScale9Enabled && _backGroundImage)
    {
        dynamic_cast<extension::Scale9Sprite*>(_backGroundImage)->setCapInsets(capInsets);
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
        _backGroundImage = extension::Scale9Sprite::create();
        _backGroundImage->setZOrder(-1);
        _renderer->addChild(_backGroundImage);
        dynamic_cast<extension::Scale9Sprite*>(_backGroundImage)->setPreferredSize(_size);
    }
    else
    {
        _backGroundImage = Sprite::create();
        _backGroundImage->setZOrder(-1);
        _renderer->addChild(_backGroundImage);
    }
    _backGroundImage->setPosition(Point(_size.width/2.0f, _size.height/2.0f));
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
    _backGroundImageTextureSize = Size::ZERO;
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
                _renderer->removeChild(_colorRender);
                _colorRender = nullptr;
            }
            if (_gradientRender)
            {
                _renderer->removeChild(_gradientRender);
                _gradientRender = nullptr;
            }
            break;
        case LAYOUT_COLOR_SOLID:
            if (_colorRender)
            {
                _renderer->removeChild(_colorRender);
                _colorRender = nullptr;
            }
            break;
        case LAYOUT_COLOR_GRADIENT:
            if (_gradientRender)
            {
                _renderer->removeChild(_gradientRender);
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
            _renderer->addChild(_colorRender,-2);
            break;
        case LAYOUT_COLOR_GRADIENT:
            _gradientRender = LayerGradient::create();
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

void UILayout::setBackGroundColor(const Color3B &color)
{
    _cColor = color;
    if (_colorRender)
    {
        _colorRender->setColor(color);
    }
}

void UILayout::setBackGroundColor(const Color3B &startColor, const Color3B &endColor)
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

void UILayout::setBackGroundColorVector(const Point &vector)
{
    _alongVector = vector;
    if (_gradientRender)
    {
        _gradientRender->setVector(vector);
    }
}

const Size& UILayout::getBackGroundImageTextureSize() const
{
    return _backGroundImageTextureSize;
}

void UILayout::setLayoutType(LayoutType type)
{
    _layoutType = type;
    for (auto& child : _widgetChildren)
    {
        if (child)
        {
            supplyTheLayoutParameterLackToChild((UIWidget*)child);
        }
    }
    _doLayoutDirty = true;
}

LayoutType UILayout::getLayoutType() const
{
    return _layoutType;
}

void UILayout::doLayout()
{
    if (!_doLayoutDirty)
    {
        return;
    }
    switch (_layoutType)
    {
        case LAYOUT_ABSOLUTE:
            break;
        case LAYOUT_LINEAR_VERTICAL:
        {
            int length = _widgetChildren.size();
            Size layoutSize = getSize();
            float topBoundary = layoutSize.height;
            for (int i=0; i<length; ++i)
            {
                UIWidget* child = static_cast<UIWidget*>(_widgetChildren.at(i));
                UILinearLayoutParameter* layoutParameter = dynamic_cast<UILinearLayoutParameter*>(child->getLayoutParameter(LAYOUT_PARAMETER_LINEAR));
                
                if (layoutParameter)
                {
                    UILinearGravity childGravity = layoutParameter->getGravity();
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
            int length = _widgetChildren.size();
            Size layoutSize = getSize();
            float leftBoundary = 0.0f;
            for (int i=0; i<length; ++i)
            {
                UIWidget* child = static_cast<UIWidget*>(_widgetChildren.at(i));
                UILinearLayoutParameter* layoutParameter = dynamic_cast<UILinearLayoutParameter*>(child->getLayoutParameter(LAYOUT_PARAMETER_LINEAR));
                
                if (layoutParameter)
                {
                    UILinearGravity childGravity = layoutParameter->getGravity();
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
            int length = _widgetChildren.size();
            int unlayoutChildCount = length;
            Size layoutSize = getSize();
            
            for (int i=0; i<length; i++)
            {
                UIWidget* child = static_cast<UIWidget*>(_widgetChildren.at(i));
                UIRelativeLayoutParameter* layoutParameter = dynamic_cast<UIRelativeLayoutParameter*>(child->getLayoutParameter(LAYOUT_PARAMETER_RELATIVE));
                layoutParameter->_put = false;
            }
            
            while (unlayoutChildCount > 0)
            {
                for (int i=0; i<length; i++)
                {
                    UIWidget* child = static_cast<UIWidget*>(_widgetChildren.at(i));
                    UIRelativeLayoutParameter* layoutParameter = dynamic_cast<UIRelativeLayoutParameter*>(child->getLayoutParameter(LAYOUT_PARAMETER_RELATIVE));
                    
                    if (layoutParameter)
                    {
                        if (layoutParameter->_put)
                        {
                            continue;
                        }
                        Point ap = child->getAnchorPoint();
                        Size cs = child->getSize();
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
                        child->setPosition(Point(finalPosX, finalPosY));
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
    _doLayoutDirty = false;
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
        setClippingType(layout->_clippingType);
    }
}
}
NS_CC_END