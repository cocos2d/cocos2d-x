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
#include "2d/CCGLProgram.h"
#include "2d/CCShaderCache.h"
#include "base/CCDirector.h"
#include "2d/CCDrawingPrimitives.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCGroupCommand.h"
#include "renderer/CCCustomCommand.h"

NS_CC_BEGIN

namespace ui {
    
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
_alongVector(Vector2(0.0f, -1.0f)),
_cOpacity(255),
_backGroundImageTextureSize(Size::ZERO),
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
_passFocusToChild(true),
_loopFocus(false)
{
    _widgetType = WidgetTypeContainer;
    onPassFocusToChild = CC_CALLBACK_2(Layout::findNearestChildWidgetIndex, this);
}

Layout::~Layout()
{
    CC_SAFE_RELEASE(_clippingStencil);
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
        setAnchorPoint(Vector2::ZERO);
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
    supplyTheLayoutParameterLackToChild(dynamic_cast<LayoutParameterProtocol*>(child));
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

void Layout::visit(Renderer *renderer, const Matrix &parentTransform, bool parentTransformUpdated)
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
    
void Layout::stencilClippingVisit(Renderer *renderer, const Matrix &parentTransform, bool parentTransformUpdated)
{
    if(!_visible)
        return;
    
    bool dirty = parentTransformUpdated || _transformUpdated;
    if(dirty)
        _modelViewTransform = transform(parentTransform);
    _transformUpdated = false;

    // IMPORTANT:
    // To ease the migration to v3.0, we still support the Matrix stack,
    // but it is deprecated and your code should not rely on it
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);
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
    
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
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

    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    director->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    
    DrawPrimitives::drawSolidRect(Vector2(-1,-1), Vector2(1,1), Color4F(1, 1, 1, 1));
    
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
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
    
void Layout::scissorClippingVisit(Renderer *renderer, const Matrix& parentTransform, bool parentTransformUpdated)
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
        Vector2 rect[4];
        rect[0] = Vector2::ZERO;
        rect[1] = Vector2(_size.width, 0);
        rect[2] = Vector2(_size.width, _size.height);
        rect[3] = Vector2(0, _size.height);
        Color4F green(0, 1, 0, 1);
        _clippingStencil->clear();
        _clippingStencil->drawPolygon(rect, 4, green, 0, green);
    }
}
    
const Rect& Layout::getClippingRect()
{
    if (_clippingRectDirty)
    {
        Vector2 worldPos = convertToWorldSpace(Vector2::ZERO);
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
        _backGroundImage->setPosition(Vector2(_size.width/2.0f, _size.height/2.0f));
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
    _backGroundImage->setPosition(Vector2(_size.width/2.0f, _size.height/2.0f));
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

void Layout::supplyTheLayoutParameterLackToChild(LayoutParameterProtocol *child)
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
    _backGroundImage->setPosition(Vector2(_size.width/2.0f, _size.height/2.0f));
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

void Layout::setBackGroundColorVector(const Vector2 &vector)
{
    _alongVector = vector;
    if (_gradientRender)
    {
        _gradientRender->setVector(vector);
    }
}
    
const Vector2& Layout::getBackGroundColorVector()
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
    LayoutProtocol::setLayoutType(type);
    for (auto& child : _children)
    {
        Widget* widgetChild = dynamic_cast<Widget*>(child);
        if (widgetChild)
        {
            supplyTheLayoutParameterLackToChild(dynamic_cast<LayoutParameterProtocol*>(child));
        }
    }
    _doLayoutDirty = true;
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
    LayoutProtocol::doLayout(getSize(), getChildren());
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
    
void Layout::setLoopFocus(bool loop)
{
    _loopFocus = loop;
}

bool Layout::isLoopFocus()
{
    return _loopFocus;
}


void Layout::setPassFocusToChild(bool pass)
{
    _passFocusToChild = pass;
}

bool Layout::isPassFocusToChild()
{
    return _passFocusToChild;
}

Size Layout::getLayoutContentSize()const
{
    const auto& children = this->getChildren();
    Size layoutSize = Size::ZERO;
    int widgetCount =0;
    for(const auto& widget : children)
    {
        Layout *layout = dynamic_cast<Layout*>(widget);
        if (nullptr != layout)
        {
            layoutSize = layoutSize + layout->getLayoutContentSize();
        }
        else
        {
            Widget *w = dynamic_cast<Widget*>(widget);
            if (w)
            {
                widgetCount++;
                Margin m = w->getLayoutParameter(LAYOUT_PARAMETER_LINEAR)->getMargin();
                layoutSize = layoutSize + w->getSize() + Size(m.right + m.left,  m.top + m.bottom) * 0.5;
            }
        }
    }
    
    //substract extra size
    LayoutType type = this->getLayoutType();
    if (type == LAYOUT_LINEAR_HORIZONTAL)
    {
        layoutSize = layoutSize - Size(0, layoutSize.height/widgetCount * (widgetCount-1));
    }
    if (type == LAYOUT_LINEAR_VERTICAL)
    {
        layoutSize = layoutSize - Size(layoutSize.width/widgetCount * (widgetCount-1), 0);
    }
    return layoutSize;
}

Vector2 Layout::getWorldCenterPoint(Widget* widget)
{
    Layout *layout = dynamic_cast<Layout*>(widget);
    //FIXEDME: we don't need to calculate the content size of layout anymore
    Size widgetSize = layout ? layout->getLayoutContentSize() :  widget->getSize();
//    CCLOG("contnet size : width = %f, height = %f", widgetSize.width, widgetSize.height);
    return widget->convertToWorldSpace(Vector2(widgetSize.width/2, widgetSize.height/2));
}

float Layout::caculateNearestDistance(Widget* baseWidget)
{
    float distance = FLT_MAX;
    
    Vector2 widgetPosition =  this->getWorldCenterPoint(baseWidget);
    
    for (Node* node : _children) {
        Layout *layout = dynamic_cast<Layout*>(node);
        int length;
        if (layout) {
            length = layout->caculateNearestDistance(baseWidget);
        }
        else
        {
            Widget* w = dynamic_cast<Widget*>(node);
            if (w && w->isFocusEnabled()) {
                Vector2 wPosition = this->getWorldCenterPoint(w);
                length = (wPosition - widgetPosition).length();
            }
            else {
                continue;
            }
        }
        
        if (length < distance) {
            distance = length;
        }
        
        
    }
    return distance;
}
    
float Layout::caculateFarestDistance(cocos2d::ui::Widget *baseWidget)
{
    float distance = -FLT_MAX;
    
    Vector2 widgetPosition =  this->getWorldCenterPoint(baseWidget);
    
    for (Node* node : _children) {
        Layout *layout = dynamic_cast<Layout*>(node);
        int length;
        if (layout) {
            length = layout->caculateFarestDistance(baseWidget);
        }
        else
        {
            Widget* w = dynamic_cast<Widget*>(node);
            if (w && w->isFocusEnabled()) {
                Vector2 wPosition = this->getWorldCenterPoint(w);
                length = (wPosition - widgetPosition).length();
            }
            else {
                continue;
            }
        }
        
        if (length > distance) {
            distance = length;
        }
    }
    return distance;
}

int Layout::findFirstFocusEnabledWidgetIndex()
{
    ssize_t index = 0;
    ssize_t count = this->getChildren().size();
    while (index < count) {
        Widget* w =  dynamic_cast<Widget*>(_children.at(index));
        if (w && w->isFocusEnabled()) {
            return (int)index;
        }
        index++;
    }
    CCASSERT(0, "invalide operation");
    return 0;
}

int Layout::findNearestChildWidgetIndex(FocusDirection direction, Widget* baseWidget)
{
    if (baseWidget == nullptr || baseWidget == this)
    {
        return this->findFirstFocusEnabledWidgetIndex();
    }
    int index = 0;
    ssize_t count = this->getChildren().size();
    
    float distance = FLT_MAX;
    int found = 0;
    if (direction == FocusDirection::FocusDirection_Left || direction == FocusDirection::FocusDirection_Right)
    {
        Vector2 widgetPosition =  this->getWorldCenterPoint(baseWidget);
        while (index <  count)
        {
            Widget *w = dynamic_cast<Widget*>(this->getChildren().at(index));
            if (w && w->isFocusEnabled())
            {
                Vector2 wPosition = this->getWorldCenterPoint(w);
                float length;
                Layout *layout = dynamic_cast<Layout*>(w);
                if (layout)
                {
                    length = layout->caculateNearestDistance(baseWidget);
                }
                else
                {
                    length = (wPosition - widgetPosition).getLength();
                }
               
                if (length < distance)
                {
                        found = index;
                        distance = length;
                }
            }
            index++;
        }
        return  found;
    }
    
    index = 0;
    found = 0;
    distance = FLT_MAX;
    if (direction == FocusDirection::FocusDirection_Down || direction == FocusDirection::FocusDirection_Up) {
        Vector2 widgetPosition = this->getWorldCenterPoint(baseWidget);
        while (index < count)
        {
            Widget *w = dynamic_cast<Widget*>(this->getChildren().at(index));
            if (w && w->isFocusEnabled())
            {
                Vector2 wPosition = this->getWorldCenterPoint(w);
                float length;
                Layout *layout = dynamic_cast<Layout*>(w);
                if (layout)
                {
                    length = layout->caculateNearestDistance(baseWidget);
                }
                else
                {
                    length = (wPosition - widgetPosition).getLength();
                }
                
                if (length < distance)
                {
                    found = index;
                    distance = length;
                }

            }
            index++;
        }
        return found;
    }
    CCASSERT(0, "invalid focus direction!!!");
    return 0;
}
    
int Layout::findFarestChildWidgetIndex(cocos2d::ui::FocusDirection direction, cocos2d::ui::Widget *baseWidget)
{
    if (baseWidget == nullptr || baseWidget == this)
    {
        return this->findFirstFocusEnabledWidgetIndex();
    }
    int index = 0;
    ssize_t count = this->getChildren().size();
    
    float distance = -FLT_MAX;
    int found = 0;
    if (direction == FocusDirection::FocusDirection_Left || direction == FocusDirection::FocusDirection_Right)
    {
        Vector2 widgetPosition =  this->getWorldCenterPoint(baseWidget);
        while (index <  count)
        {
            Widget *w = dynamic_cast<Widget*>(this->getChildren().at(index));
            if (w && w->isFocusEnabled())
            {
                Vector2 wPosition = this->getWorldCenterPoint(w);
                float length;
                Layout *layout = dynamic_cast<Layout*>(w);
                if (layout)
                {
                    length = layout->caculateFarestDistance(baseWidget);
                }
                else
                {
                    length = (wPosition - widgetPosition).getLength();
                }
                
                if (length > distance)
                {
                    found = index;
                    distance = length;
                }
            }
            index++;
        }
        return  found;
    }
    
    index = 0;
    found = 0;
    distance = -FLT_MAX;
    if (direction == FocusDirection::FocusDirection_Down || direction == FocusDirection::FocusDirection_Up) {
        Vector2 widgetPosition = this->getWorldCenterPoint(baseWidget);
        while (index < count)
        {
            Widget *w = dynamic_cast<Widget*>(this->getChildren().at(index));
            if (w && w->isFocusEnabled())
            {
                Vector2 wPosition = this->getWorldCenterPoint(w);
                float length;
                Layout *layout = dynamic_cast<Layout*>(w);
                if (layout)
                {
                    length = layout->caculateFarestDistance(baseWidget);
                }
                else
                {
                    length = (wPosition - widgetPosition).getLength();
                }
                
                if (length > distance)
                {
                    found = index;
                    distance = length;
                }
                
            }
            index++;
        }
        return found;
    }
    CCASSERT(0, "invalid focus direction!!!");
    return 0;
}
    


Widget* Layout::findFocusEnabledChildWidgetByIndex(ssize_t index)
{
  
    Widget *widget = this->getChildWidgetByIndex(index);
    
    if (widget)
    {
        if (widget->isFocusEnabled())
        {
            return widget;
        }
        index = index + 1;
        return this->findFocusEnabledChildWidgetByIndex(index);
    }
    return nullptr;
}
    
Widget *Layout::findFirstNonLayoutWidget()
{
    Widget* widget = nullptr;
    for(Node *node : _children)
    {
        Layout* layout = dynamic_cast<Layout*>(node);
        if (layout) {
            widget = layout->findFirstNonLayoutWidget();
        }
        else{
            Widget *w = dynamic_cast<Widget*>(node);
            if (w) {
                widget = w;
                break;
            }
        }
        
    }
    
    return widget;
}
    
void Layout::findProperSearchingFunctor(FocusDirection dir, Widget* baseWidget)
{
    if (baseWidget == nullptr) {
        return;
    }
    
    Vector2 previousWidgetPosition = this->getWorldCenterPoint(baseWidget);
    
    Vector2 layoutPosition = this->getWorldCenterPoint(this->findFirstNonLayoutWidget());
    
    if (dir == FocusDirection::FocusDirection_Left) {
        if (previousWidgetPosition.x > layoutPosition.x) {
            onPassFocusToChild = CC_CALLBACK_2(Layout::findNearestChildWidgetIndex, this);
        }
        else{
            onPassFocusToChild = CC_CALLBACK_2(Layout::findFarestChildWidgetIndex, this);
        }
    }else if(dir == FocusDirection::FocusDirection_Right){
        if (previousWidgetPosition.x > layoutPosition.x) {
            onPassFocusToChild = CC_CALLBACK_2(Layout::findFarestChildWidgetIndex, this);
        }
        else{
            onPassFocusToChild = CC_CALLBACK_2(Layout::findNearestChildWidgetIndex, this);
        }
    }else if(dir == FocusDirection::FocusDirection_Down){
        if (previousWidgetPosition.y > layoutPosition.y) {
            onPassFocusToChild = CC_CALLBACK_2(Layout::findNearestChildWidgetIndex, this);
        }else{
            onPassFocusToChild = CC_CALLBACK_2(Layout::findFarestChildWidgetIndex, this);
        }
    }else if(dir == FocusDirection::FocusDirection_Up){
        if (previousWidgetPosition.y < layoutPosition.y) {
            onPassFocusToChild = CC_CALLBACK_2(Layout::findNearestChildWidgetIndex, this);
        }else{
            onPassFocusToChild = CC_CALLBACK_2(Layout::findFarestChildWidgetIndex, this);
        }
    }else{
        CCASSERT(0, "invalid direction!");
    }

}


Widget* Layout::passFocusToChild(cocos2d::ui::FocusDirection dir, cocos2d::ui::Widget *current)
{
    if (checkFocusEnabledChild())
    {
        Widget* previousWidget = this->getCurrentFocusedWidget(true);
        
        this->findProperSearchingFunctor(dir, previousWidget);
        
        int index = onPassFocusToChild(dir, previousWidget);
        
        Widget *widget = this->getChildWidgetByIndex(index);
        this->dispatchFocusEvent(current, widget);
        Layout *layout = dynamic_cast<Layout*>(widget);
        if (layout)
        {
            return layout->findNextFocusedWidget(dir, layout);
        }
        else
        {
            return widget;
        }
    }
    else
    {
        return this;
    }
        
}

bool Layout::checkFocusEnabledChild()
{
    bool ret = false;
    for(Node* node : _children)
    {
        Widget* widget = dynamic_cast<Widget*>(node);
        if (widget && widget->isFocusEnabled())
        {
            ret = true;
            break;
        }
    }
    return ret;
}

Widget* Layout::getChildWidgetByIndex(ssize_t index)
{
    ssize_t size = _children.size();
    int count = 0;
    ssize_t oldIndex = index;
    Widget *widget = nullptr;
    while (index < size)
    {
        Widget* firstChild = dynamic_cast<Widget*>(_children.at(index));
        if (firstChild)
        {
            widget = firstChild;
            break;
        }
        count++;
        index++;
    }
    
    if (nullptr == widget)
    {
        int begin = 0;
        while (begin < oldIndex)
        {
            Widget* firstChild = dynamic_cast<Widget*>(_children.at(begin));
            if (firstChild)
            {
                widget = firstChild;
                break;
            }
            count++;
            begin++;
        }
    }
    
    
    return widget;
}

Widget* Layout::getPreviousFocusedWidget(FocusDirection direction, Widget *current)
{
    Widget *nextWidget = nullptr;
    ssize_t previousWidgetPos = _children.getIndex(current);
    previousWidgetPos = previousWidgetPos - 1;
    if (previousWidgetPos >= 0)
    {
        nextWidget = this->getChildWidgetByIndex(previousWidgetPos);
        if (nextWidget->isFocusEnabled())
        {
            
            this->dispatchFocusEvent(current, nextWidget);
            
            Layout* layout = dynamic_cast<Layout*>(nextWidget);
            if (layout)
            {
                return layout->findNextFocusedWidget(direction, layout);
            }
           
            return nextWidget;
        }
        else
        {
            //handling the disabled widget, there is no actual focus lose or get, so we don't need any envet
            return this->getPreviousFocusedWidget(direction, nextWidget);
        }
    }else
    {
        if (_loopFocus)
        {
            if (checkFocusEnabledChild())
            {
                previousWidgetPos = _children.size()-1;
                nextWidget = this->getChildWidgetByIndex(previousWidgetPos);
                if (nextWidget->isFocusEnabled())
                {
                    this->dispatchFocusEvent(current, nextWidget);
                    Layout* layout = dynamic_cast<Layout*>(nextWidget);
                    if (layout)
                    {
                        return layout->findNextFocusedWidget(direction, layout);
                    }
                    else
                    {
                        return nextWidget;
                    }
                }
                else
                {
                    return this->getPreviousFocusedWidget(direction, nextWidget);
                }
            }
            else
            {
                if (dynamic_cast<Layout*>(current)) {
                    return current;
                }
                else
                {
                    return _focusedWidget;
                }
            }
        }
        else
        {
            if (isLastWidgetInContainer(current, direction))
            {
                if (isWidgetAncestorSupportLoopFocus(this, direction))
                {
                    this->dispatchFocusEvent(current, this);
                    return Widget::findNextFocusedWidget(direction, this);
                }
                if (dynamic_cast<Layout*>(current)) {
                    return current;
                }
                else
                {
                    return _focusedWidget;
                }
            }
            else
            {
                //call parent method to get its parent's next focus enabled widget
                this->dispatchFocusEvent(current,this);
                return Widget::findNextFocusedWidget(direction, this);
            }
        }
    }
}

Widget* Layout::getNextFocusedWidget(FocusDirection direction, Widget *current)
{
    Widget *nextWidget = nullptr;
    ssize_t previousWidgetPos = _children.getIndex(current);
    previousWidgetPos = previousWidgetPos + 1;
    if (previousWidgetPos < _children.size())
    {
        nextWidget = this->getChildWidgetByIndex(previousWidgetPos);
        //handle widget
        if (nextWidget)
        {
            if (nextWidget->isFocusEnabled())
            {
                
                this->dispatchFocusEvent(current, nextWidget);
                Layout* layout = dynamic_cast<Layout*>(nextWidget);
                if (layout)
                {
                    return layout->findNextFocusedWidget(direction, layout);
                }
                else
                {
                    return nextWidget;
                }
            }
            else
            {
                return this->getNextFocusedWidget(direction, nextWidget);
            }
        }
        else
        {
            return current;
        }
    }else
    {
        if (_loopFocus)
        {
            if (checkFocusEnabledChild())
            {
                previousWidgetPos = 0;
                nextWidget = this->getChildWidgetByIndex(previousWidgetPos);
                if (nextWidget->isFocusEnabled())
                {
                    
                    this->dispatchFocusEvent(current, nextWidget);
                    
                    Layout* layout = dynamic_cast<Layout*>(nextWidget);
                    if (layout)
                    {
                        return layout->findNextFocusedWidget(direction, layout);
                    }else
                    {
                        return nextWidget;
                    }
                }
                else
                {
                    return this->getNextFocusedWidget(direction, nextWidget);
                }
            }
            else
            {
                if (dynamic_cast<Layout*>(current)) {
                    return current;
                }
                else
                {
                    return _focusedWidget;
                }
            }
        }
        else{
            if (isLastWidgetInContainer(current, direction))
            {
                if (isWidgetAncestorSupportLoopFocus(this, direction))
                {
                    this->dispatchFocusEvent(current, this);
                    return Widget::findNextFocusedWidget(direction, this);
                }
                if (dynamic_cast<Layout*>(current)) {
                    return current;
                }
                else
                {
                    return _focusedWidget;
                }
            }
            else
            {
                //call parent method to get its parent's next focus enabled widget
                this->dispatchFocusEvent(current,this);
                return Widget::findNextFocusedWidget(direction, this);
            }
        }
    }
}

bool  Layout::isLastWidgetInContainer(Widget* widget, FocusDirection direction)
{
    Layout* parent = dynamic_cast<Layout*>(widget->getParent());
    if (parent == nullptr)
    {
        return true;
    }
    
    auto container = parent->getChildren();
    ssize_t index = container.getIndex(widget);
    if (parent->getLayoutType() == LAYOUT_LINEAR_HORIZONTAL)
    {
        if (direction == FocusDirection::FocusDirection_Left) {
            if (index == 0)
            {
                return true * isLastWidgetInContainer(parent, direction);
            }
            else
            {
                return false;
            }
        }
        if (direction == FocusDirection::FocusDirection_Right) {
            if (index == container.size()-1)
            {
                return true * isLastWidgetInContainer(parent, direction);
            }
            else
            {
                return false;
            }
        }
        if (direction == FocusDirection::FocusDirection_Down)
        {
            return isLastWidgetInContainer(parent, direction);
        }
        
        if (direction == FocusDirection::FocusDirection_Up)
        {
            return isLastWidgetInContainer(parent, direction);
        }
    }
    else if(parent->getLayoutType() == LAYOUT_LINEAR_VERTICAL)
    {
        if (direction == FocusDirection::FocusDirection_Up)
        {
            if (index == 0)
            {
                return true * isLastWidgetInContainer(parent, direction);
                
            }
            else
            {
                return false;
            }
        }
        if (direction == FocusDirection::FocusDirection_Down)
        {
            if (index == container.size() - 1)
            {
                return true * isLastWidgetInContainer(parent, direction);
            }
            else
            {
                return false;
            }
        }
        if (direction == FocusDirection::FocusDirection_Left)
        {
            return isLastWidgetInContainer(parent, direction);
        }
        
        if (direction == FocusDirection::FocusDirection_Right)
        {
            return isLastWidgetInContainer(parent, direction);
        }
    }
    else
    {
        CCASSERT(0, "invalid layout Type");
        return false;
    }
    
    return false;
}

bool  Layout::isWidgetAncestorSupportLoopFocus(Widget* widget, FocusDirection direction)
{
    Layout* parent = dynamic_cast<Layout*>(widget->getParent());
    if (parent == nullptr)
    {
        return false;
    }
    if (parent->isLoopFocus())
    {
        auto layoutType = parent->getLayoutType();
        if (layoutType == LAYOUT_LINEAR_HORIZONTAL)
        {
            if (direction == FocusDirection::FocusDirection_Left || direction == FocusDirection::FocusDirection_Right)
            {
                return true;
            }
            else
            {
                return isWidgetAncestorSupportLoopFocus(parent, direction);
            }
        }
        if (layoutType == LAYOUT_LINEAR_VERTICAL)
        {
            if (direction == FocusDirection::FocusDirection_Down || direction == FocusDirection::FocusDirection_Up)
            {
                return true;
            }
            else
            {
                return isWidgetAncestorSupportLoopFocus(parent, direction);
            }
        }
        else
        {
            CCASSERT(0, "invalid layout type");
        }
        
    }
    else
    {
        return isWidgetAncestorSupportLoopFocus(parent, direction);
    }
}




Widget* Layout::findNextFocusedWidget(FocusDirection direction, Widget* current)
{
    if (this->isFocused())
    {
        Layout* parent = dynamic_cast<Layout*>(this->getParent());

        if (_passFocusToChild)
        {
            Widget * w = this->passFocusToChild(direction, current);
            if (dynamic_cast<Layout*>(w)) {
                if (parent) {
                    return parent->findNextFocusedWidget(direction, this);
                }
            }
            return w;
        }
        
        if (nullptr == parent) {
            return this;
        }
        return parent->findNextFocusedWidget(direction, this);
            
    }
    else if(current->isFocused() || !current->isFocusEnabled())
    {
        if (_layoutType == LAYOUT_LINEAR_HORIZONTAL)
        {
            switch (direction)
            {
                case FocusDirection::FocusDirection_Left:
                {
                    return this->getPreviousFocusedWidget(direction, current);
                }break;
                case FocusDirection::FocusDirection_Right:
                {
                    return this->getNextFocusedWidget(direction, current);
                }break;
                case FocusDirection::FocusDirection_Down:
                case FocusDirection::FocusDirection_Up:
                {
                    if (isLastWidgetInContainer(this, direction))
                    {
                        if (isWidgetAncestorSupportLoopFocus(current, direction))
                        {
                            this->dispatchFocusEvent(current, this);
                            return Widget::findNextFocusedWidget(direction, this);
                        }
                        return current;
                    }
                    else{
                        this->dispatchFocusEvent(current, this);
                        return Widget::findNextFocusedWidget(direction, this);
                    }
                }break;
                default:
                {
                    CCASSERT(0, "Invalid Focus Direction");
                    return current;
                }
                    break;
            }
        }
        else if (_layoutType == LAYOUT_LINEAR_VERTICAL)
        {
            switch (direction)
            {
                case FocusDirection::FocusDirection_Left:
                case FocusDirection::FocusDirection_Right:
                {
                    if (isLastWidgetInContainer(this, direction))
                    {
                        if (isWidgetAncestorSupportLoopFocus(current, direction))
                        {
                            this->dispatchFocusEvent(current, this);
                            return Widget::findNextFocusedWidget(direction, this);
                        }
                        return current;
                    }
                    else
                    {
                        this->dispatchFocusEvent(current, this);
                        return Widget::findNextFocusedWidget(direction, this);
                    }
                } break;
                case FocusDirection::FocusDirection_Down:
                {
                    return getNextFocusedWidget(direction, current);
                }
                    break;
                case FocusDirection::FocusDirection_Up:
                {
                    return getPreviousFocusedWidget(direction, current);
                }
                    break;
                default:
                {
                    CCASSERT(0, "Invalid Focus Direction");
                    return current;
                }
                    break;
            }
        }
        else
        {
            CCASSERT(0, "Un Supported Layout type, please use VBox and HBox instead!!!");
            return current;
        }
    }
    else
    {
        return current;
    }
}
    
}
NS_CC_END
