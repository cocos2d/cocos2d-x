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
#include "ui/UIScale9Sprite.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/ccGLStateCache.h"
#include "base/CCDirector.h"
#include "2d/CCDrawingPrimitives.h"
#include "renderer/CCRenderer.h"
#include "ui/UILayoutManager.h"
#include "2d/CCDrawNode.h"
#include "2d/CCLayer.h"
#include "2d/CCSprite.h"
#include "base/CCEventFocus.h"


NS_CC_BEGIN

namespace ui {
    
static const int BACKGROUNDIMAGE_Z = (-1);
static const int BCAKGROUNDCOLORRENDERER_Z = (-2);
    
IMPLEMENT_CLASS_GUI_INFO(Layout)

Layout::Layout():
_backGroundScale9Enabled(false),
_backGroundImage(nullptr),
_backGroundImageFileName(""),
_backGroundImageCapInsets(Rect::ZERO),
_colorType(BackGroundColorType::NONE),
_bgImageTexType(TextureResType::LOCAL),
_backGroundImageTextureSize(Size::ZERO),
_backGroundImageColor(Color3B::WHITE),
_backGroundImageOpacity(255),
_colorRender(nullptr),
_gradientRender(nullptr),
_cColor(Color3B::WHITE),
_gStartColor(Color3B::WHITE),
_gEndColor(Color3B::WHITE),
_alongVector(Vec2(0.0f, -1.0f)),
_cOpacity(255),
_clippingEnabled(false),
_layoutType(Type::ABSOLUTE),
_clippingType(ClippingType::STENCIL),
_clippingStencil(nullptr),
_scissorRectDirty(false),
_clippingRect(Rect::ZERO),
_clippingParent(nullptr),
_clippingRectDirty(true),
_doLayoutDirty(true),
_isInterceptTouch(false),
_loopFocus(false),
_passFocusToChild(true),
_isFocusPassing(false)
{
    //no-op
}

Layout::~Layout()
{
    CC_SAFE_RELEASE(_clippingStencil);
}
    
void Layout::onEnter()
{
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeJavascript)
    {
        if (ScriptEngineManager::sendNodeEventToJSExtended(this, kNodeOnEnter))
            return;
    }
#endif
    
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
    Layout* layout = new (std::nothrow) Layout();
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
    if (Widget::init())
    {
        ignoreContentAdaptWithSize(false);
        setContentSize(Size::ZERO);
        setAnchorPoint(Vec2::ZERO);
        onPassFocusToChild = CC_CALLBACK_2(Layout::findNearestChildWidgetIndex, this);
        return true;
    }
    return false;
}
    
void Layout::addChild(Node* child)
{
    Layout::addChild(child, child->getLocalZOrder(), child->getTag());
}
    
void Layout::addChild(Node * child, int localZOrder)
{
    Layout::addChild(child, localZOrder, child->getTag());
}

void Layout::addChild(Node *child, int zOrder, int tag)
{
    if (dynamic_cast<Widget*>(child)) {
        supplyTheLayoutParameterLackToChild(static_cast<Widget*>(child));
    }
    Widget::addChild(child, zOrder, tag);
    _doLayoutDirty = true;
}
    
void Layout::addChild(Node* child, int zOrder, const std::string &name)
{
    if (dynamic_cast<Widget*>(child)) {
        supplyTheLayoutParameterLackToChild(static_cast<Widget*>(child));
    }
    Widget::addChild(child, zOrder, name);
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
    _doLayoutDirty = true;
}
    
void Layout::removeAllChildrenWithCleanup(bool cleanup)
{
    Widget::removeAllChildrenWithCleanup(cleanup);
    _doLayoutDirty = true;
}

bool Layout::isClippingEnabled()const
{
    return _clippingEnabled;
}

void Layout::visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    if (!_visible)
    {
        return;
    }
    
    adaptRenderers();
    doLayout();
    
    if (_clippingEnabled)
    {
        switch (_clippingType)
        {
            case ClippingType::STENCIL:
                stencilClippingVisit(renderer, parentTransform, parentFlags);
                break;
            case ClippingType::SCISSOR:
                scissorClippingVisit(renderer, parentTransform, parentFlags);
                break;
            default:
                break;
        }
    }
    else
    {
        Widget::visit(renderer, parentTransform, parentFlags);
    }
}
    
void Layout::stencilClippingVisit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
    if(!_visible)
        return;
    
    uint32_t flags = processParentFlags(parentTransform, parentFlags);

    // IMPORTANT:
    // To ease the migration to v3.0, we still support the Mat4 stack,
    // but it is deprecated and your code should not rely on it
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    CC_PUSH_MATRIX_MV(renderer->getMatrixStack())
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);
    //Add group command

    _groupCommand.init(_globalZOrder);
    renderer->addCommand(&_groupCommand);
    
    renderer->pushGroup(_groupCommand.getRenderQueueID());
    
    _beginStencilCommand.init(_globalZOrder, false, 1, _clippingStencil);
    renderer->addCommand(&_beginStencilCommand);
    
    _clippingStencil->visit(renderer, _modelViewTransform, flags);
    
    _afterStencilCommand.init(_globalZOrder);
    renderer->addCommand(&_afterStencilCommand);
    
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
            node->visit(renderer, _modelViewTransform, flags);
        else
            break;
    }
    
    for( ; j < _protectedChildren.size(); j++ )
    {
        auto node = _protectedChildren.at(j);
        
        if ( node && node->getLocalZOrder() < 0 )
            node->visit(renderer, _modelViewTransform, flags);
        else
            break;
    }
    
    //
    // draw self
    //
    this->draw(renderer, _modelViewTransform, flags);
    
    //
    // draw children and protectedChildren zOrder >= 0
    //
    for(auto it=_protectedChildren.cbegin()+j; it != _protectedChildren.cend(); ++it)
        (*it)->visit(renderer, _modelViewTransform, flags);
    
    for(auto it=_children.cbegin()+i; it != _children.cend(); ++it)
        (*it)->visit(renderer, _modelViewTransform, flags);

    
    _endStencilCommand.init(_globalZOrder);
    renderer->addCommand(&_endStencilCommand);
    
    renderer->popGroup();
    
    CC_POP_MATRIX_MV(renderer->getMatrixStack())
}
    
void Layout::scissorClippingVisit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
    _beginScissorCommand.init(_globalZOrder, getClippingRect());
    renderer->addCommand(&_beginScissorCommand);
    
    ProtectedNode::visit(renderer, parentTransform, parentFlags);
    
    _endScissorCommand.init(_globalZOrder);
    renderer->addCommand(&_endScissorCommand);
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
        case ClippingType::STENCIL:
            if (able)
            {
                _clippingStencil = DrawNode::create();
                if (_running)
                {
                    _clippingStencil->onEnter();
                }
                _clippingStencil->retain();
                setStencilClippingSize(_contentSize);
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
    
void Layout::setClippingType(ClippingType type)
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
    
Layout::ClippingType Layout::getClippingType()const
{
    return _clippingType;
}
    
void Layout::setStencilClippingSize(const Size &size)
{
    if (_clippingEnabled && _clippingType == ClippingType::STENCIL)
    {
        Vec2 rect[4];
        rect[0] = Vec2::ZERO;
        rect[1] = Vec2(_contentSize.width, 0);
        rect[2] = Vec2(_contentSize.width, _contentSize.height);
        rect[3] = Vec2(0, _contentSize.height);
        Color4F green(0, 1, 0, 1);
        _clippingStencil->clear();
        _clippingStencil->drawPolygon(rect, 4, green, 0, green);
    }
}
    
const Rect& Layout::getClippingRect() 
{
    if (_clippingRectDirty)
    {
        Vec2 worldPos = convertToWorldSpace(Vec2::ZERO);
        AffineTransform t = getNodeToWorldAffineTransform();
        float scissorWidth = _contentSize.width*t.a;
        float scissorHeight = _contentSize.height*t.d;
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
    setStencilClippingSize(_contentSize);
    _doLayoutDirty = true;
    _clippingRectDirty = true;
    if (_backGroundImage)
    {
        _backGroundImage->setPosition(_contentSize.width/2.0f, _contentSize.height/2.0f);
        if (_backGroundScale9Enabled && _backGroundImage)
        {
            _backGroundImage->setPreferredSize(_contentSize);
        }
    }
    if (_colorRender)
    {
        _colorRender->setContentSize(_contentSize);
    }
    if (_gradientRender)
    {
        _gradientRender->setContentSize(_contentSize);
    }
}

void Layout::setBackGroundImageScale9Enabled(bool able)
{
    if (_backGroundScale9Enabled == able)
    {
        return;
    }
    _backGroundScale9Enabled = able;
    if (nullptr == _backGroundImage)
    {
        addBackGroundImage();
        setBackGroundImage(_backGroundImageFileName,_bgImageTexType);
    }
    _backGroundImage->setScale9Enabled(_backGroundScale9Enabled);
    setBackGroundImageCapInsets(_backGroundImageCapInsets);
}
    
bool Layout::isBackGroundImageScale9Enabled()const
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
        _backGroundImage->setScale9Enabled(_backGroundScale9Enabled);
    }
    _backGroundImageFileName = fileName;
    _bgImageTexType = texType;
   
    switch (_bgImageTexType)
    {
        case TextureResType::LOCAL:
            _backGroundImage->initWithFile(fileName);
            break;
        case TextureResType::PLIST:
            _backGroundImage->initWithSpriteFrameName(fileName);
            break;
        default:
            break;
    }
    if (_backGroundScale9Enabled) {
        _backGroundImage->setPreferredSize(_contentSize);
    }
    
    _backGroundImageTextureSize = _backGroundImage->getContentSize();
    _backGroundImage->setPosition(_contentSize.width/2.0f, _contentSize.height/2.0f);
    updateBackGroundImageRGBA();
}

void Layout::setBackGroundImageCapInsets(const Rect &capInsets)
{
    _backGroundImageCapInsets = capInsets;
    if (_backGroundScale9Enabled && _backGroundImage)
    {
        _backGroundImage->setCapInsets(capInsets);
    }
}
    
const Rect& Layout::getBackGroundImageCapInsets()const
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
        case Type::ABSOLUTE:
            break;
        case Type::HORIZONTAL:
        case Type::VERTICAL:
        {
            LinearLayoutParameter* layoutParameter = dynamic_cast<LinearLayoutParameter*>(child->getLayoutParameter());
            if (!layoutParameter)
            {
                child->setLayoutParameter(LinearLayoutParameter::create());
            }
            break;
        }
        case Type::RELATIVE:
        {
            RelativeLayoutParameter* layoutParameter = dynamic_cast<RelativeLayoutParameter*>(child->getLayoutParameter());
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
    _backGroundImage = Scale9Sprite::create();
    _backGroundImage->setScale9Enabled(false);
    
    addProtectedChild(_backGroundImage, BACKGROUNDIMAGE_Z, -1);
   
    _backGroundImage->setPosition(_contentSize.width/2.0f, _contentSize.height/2.0f);
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

void Layout::setBackGroundColorType(BackGroundColorType type)
{
    if (_colorType == type)
    {
        return;
    }
    switch (_colorType)
    {
        case BackGroundColorType::NONE:
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
        case BackGroundColorType::SOLID:
            if (_colorRender)
            {
                removeProtectedChild(_colorRender);
                _colorRender = nullptr;
            }
            break;
        case BackGroundColorType::GRADIENT:
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
        case BackGroundColorType::NONE:
            break;
        case BackGroundColorType::SOLID:
            _colorRender = LayerColor::create();
            _colorRender->setContentSize(_contentSize);
            _colorRender->setOpacity(_cOpacity);
            _colorRender->setColor(_cColor);
            addProtectedChild(_colorRender, BCAKGROUNDCOLORRENDERER_Z, -1);
            break;
        case BackGroundColorType::GRADIENT:
            _gradientRender = LayerGradient::create();
            _gradientRender->setContentSize(_contentSize);
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
    
Layout::BackGroundColorType Layout::getBackGroundColorType()const
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
    
const Color3B& Layout::getBackGroundColor()const
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
    
const Color3B& Layout::getBackGroundStartColor()const
{
    return _gStartColor;
}

const Color3B& Layout::getBackGroundEndColor()const
{
    return _gEndColor;
}

void Layout::setBackGroundColorOpacity(GLubyte opacity)
{
    _cOpacity = opacity;
    switch (_colorType)
    {
        case BackGroundColorType::NONE:
            break;
        case BackGroundColorType::SOLID:
            _colorRender->setOpacity(opacity);
            break;
        case BackGroundColorType::GRADIENT:
            _gradientRender->setOpacity(opacity);
            break;
        default:
            break;
    }
}
    
GLubyte Layout::getBackGroundColorOpacity()const
{
    return _cOpacity;
}

void Layout::setBackGroundColorVector(const Vec2 &vector)
{
    _alongVector = vector;
    if (_gradientRender)
    {
        _gradientRender->setVector(vector);
    }
}
    
const Vec2& Layout::getBackGroundColorVector()const
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

const Color3B& Layout::getBackGroundImageColor()const
{
    return _backGroundImageColor;
}

GLubyte Layout::getBackGroundImageOpacity()const
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

void Layout::setLayoutType(Type type)
{
    _layoutType = type;
   
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
    


Layout::Type Layout::getLayoutType() const
{
    return _layoutType;
}

void Layout::forceDoLayout()
{
    this->requestDoLayout();
    this->doLayout();
}
    
void Layout::requestDoLayout()
{
    _doLayoutDirty = true;
}
    
Size Layout::getLayoutContentSize()const
{
    return this->getContentSize();
}
    
const Vector<Node*>& Layout::getLayoutElements()const
{
    return this->getChildren();
}
    
LayoutManager* Layout::createLayoutManager()
{
    LayoutManager* exe = nullptr;
    switch (_layoutType)
    {
        case Type::VERTICAL:
            exe = LinearVerticalLayoutManager::create();
            break;
        case Type::HORIZONTAL:
            exe = LinearHorizontalLayoutManager::create();
            break;
        case Type::RELATIVE:
            exe = RelativeLayoutManager::create();
            break;
        default:
            break;
    }
    return exe;

}

void Layout::doLayout()
{
    
    if (!_doLayoutDirty)
    {
        return;
    }
    
    sortAllChildren();

    LayoutManager* executant = this->createLayoutManager();
    
    if (executant)
    {
        executant->doLayout(this);
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
        _loopFocus = layout->_loopFocus;
        _passFocusToChild = layout->_passFocusToChild;
        _isInterceptTouch = layout->_isInterceptTouch;
    }
}
    
void Layout::setLoopFocus(bool loop)
{
    _loopFocus = loop;
}

bool Layout::isLoopFocus()const
{
    return _loopFocus;
}


void Layout::setPassFocusToChild(bool pass)
{
    _passFocusToChild = pass;
}

bool Layout::isPassFocusToChild()const
{
    return _passFocusToChild;
}

Size Layout::getLayoutAccumulatedSize()const
{
    const auto& children = this->getChildren();
    Size layoutSize = Size::ZERO;
    int widgetCount =0;
    for(const auto& widget : children)
    {
        Layout *layout = dynamic_cast<Layout*>(widget);
        if (nullptr != layout)
        {
            layoutSize = layoutSize + layout->getLayoutAccumulatedSize();
        }
        else
        {
            Widget *w = dynamic_cast<Widget*>(widget);
            if (w)
            {
                widgetCount++;
                Margin m = w->getLayoutParameter()->getMargin();
                layoutSize = layoutSize + w->getContentSize() + Size(m.right + m.left,  m.top + m.bottom) * 0.5;
            }
        }
    }
    
    //substract extra size
    Type type = this->getLayoutType();
    if (type == Type::HORIZONTAL)
    {
        layoutSize = layoutSize - Size(0, layoutSize.height/widgetCount * (widgetCount-1));
    }
    if (type == Type::VERTICAL)
    {
        layoutSize = layoutSize - Size(layoutSize.width/widgetCount * (widgetCount-1), 0);
    }
    return layoutSize;
}

Vec2 Layout::getWorldCenterPoint(Widget* widget)const
{
    Layout *layout = dynamic_cast<Layout*>(widget);
    //FIXEDME: we don't need to calculate the content size of layout anymore
    Size widgetSize = layout ? layout->getLayoutAccumulatedSize() :  widget->getContentSize();
//    CCLOG("contnet size : width = %f, height = %f", widgetSize.width, widgetSize.height);
    return widget->convertToWorldSpace(Vec2(widgetSize.width/2, widgetSize.height/2));
}

float Layout::calculateNearestDistance(Widget* baseWidget)
{
    float distance = FLT_MAX;
    
    Vec2 widgetPosition =  this->getWorldCenterPoint(baseWidget);
    
    for (Node* node : _children)
    {
        Layout *layout = dynamic_cast<Layout*>(node);
        int length;
        if (layout)
        {
            length = layout->calculateNearestDistance(baseWidget);
        }
        else
        {
            Widget* w = dynamic_cast<Widget*>(node);
            if (w && w->isFocusEnabled())
            {
                Vec2 wPosition = this->getWorldCenterPoint(w);
                length = (wPosition - widgetPosition).length();
            }
            else
            {
                continue;
            }
        }
        
        if (length < distance)
        {
            distance = length;
        }
        
        
    }
    return distance;
}
    
float Layout::calculateFarthestDistance(cocos2d::ui::Widget *baseWidget)
{
    float distance = -FLT_MAX;
    
    Vec2 widgetPosition =  this->getWorldCenterPoint(baseWidget);
    
    for (Node* node : _children)
    {
        Layout *layout = dynamic_cast<Layout*>(node);
        int length;
        if (layout)
        {
            length = layout->calculateFarthestDistance(baseWidget);
        }
        else
        {
            Widget* w = dynamic_cast<Widget*>(node);
            if (w && w->isFocusEnabled()) {
                Vec2 wPosition = this->getWorldCenterPoint(w);
                length = (wPosition - widgetPosition).length();
            }
            else
            {
                continue;
            }
        }
        
        if (length > distance)
        {
            distance = length;
        }
    }
    return distance;
}

int Layout::findFirstFocusEnabledWidgetIndex()
{
    ssize_t index = 0;
    ssize_t count = this->getChildren().size();
    while (index < count)
    {
        Widget* w =  dynamic_cast<Widget*>(_children.at(index));
        if (w && w->isFocusEnabled())
        {
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
    if (direction == FocusDirection::LEFT || direction == FocusDirection::RIGHT ||
        direction == FocusDirection::DOWN || direction == FocusDirection::UP)
    {
        Vec2 widgetPosition =  this->getWorldCenterPoint(baseWidget);
        while (index <  count)
        {
            Widget *w = dynamic_cast<Widget*>(this->getChildren().at(index));
            if (w && w->isFocusEnabled())
            {
                Vec2 wPosition = this->getWorldCenterPoint(w);
                float length;
                Layout *layout = dynamic_cast<Layout*>(w);
                if (layout)
                {
                    length = layout->calculateNearestDistance(baseWidget);
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
    
    
    CCASSERT(0, "invalid focus direction!!!");
    return 0;
}
    
int Layout::findFarthestChildWidgetIndex(FocusDirection direction, cocos2d::ui::Widget *baseWidget)
{
    if (baseWidget == nullptr || baseWidget == this)
    {
        return this->findFirstFocusEnabledWidgetIndex();
    }
    int index = 0;
    ssize_t count = this->getChildren().size();
    
    float distance = -FLT_MAX;
    int found = 0;
    if (direction == FocusDirection::LEFT || direction == FocusDirection::RIGHT
        || direction == FocusDirection::DOWN || direction == FocusDirection::UP)
    {
        Vec2 widgetPosition =  this->getWorldCenterPoint(baseWidget);
        while (index <  count)
        {
            Widget *w = dynamic_cast<Widget*>(this->getChildren().at(index));
            if (w && w->isFocusEnabled())
            {
                Vec2 wPosition = this->getWorldCenterPoint(w);
                float length;
                Layout *layout = dynamic_cast<Layout*>(w);
                if (layout)
                {
                    length = layout->calculateFarthestDistance(baseWidget);
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
        if (layout)
        {
            widget = layout->findFirstNonLayoutWidget();
            if (widget != nullptr)
            {
                return widget;
            }
        }
        else
        {
            Widget *w = dynamic_cast<Widget*>(node);
            if (w)
            {
                widget = w;
                break;
            }
        }
        
    }
    
    return widget;
}
    
void Layout::findProperSearchingFunctor(FocusDirection dir, Widget* baseWidget)
{
    if (baseWidget == nullptr)
    {
        return;
    }
    
    Vec2 previousWidgetPosition = this->getWorldCenterPoint(baseWidget);
    
    Vec2 widgetPosition = this->getWorldCenterPoint(this->findFirstNonLayoutWidget());
    
    if (dir == FocusDirection::LEFT)
    {
        if (previousWidgetPosition.x > widgetPosition.x)
        {
            onPassFocusToChild = CC_CALLBACK_2(Layout::findNearestChildWidgetIndex, this);
        }
        else
        {
            onPassFocusToChild = CC_CALLBACK_2(Layout::findFarthestChildWidgetIndex, this);
        }
    }
    else if(dir == FocusDirection::RIGHT)
    {
        if (previousWidgetPosition.x > widgetPosition.x)
        {
            onPassFocusToChild = CC_CALLBACK_2(Layout::findFarthestChildWidgetIndex, this);
        }
        else
        {
            onPassFocusToChild = CC_CALLBACK_2(Layout::findNearestChildWidgetIndex, this);
        }
    }
    else if(dir == FocusDirection::DOWN)
    {
        if (previousWidgetPosition.y > widgetPosition.y)
        {
            onPassFocusToChild = CC_CALLBACK_2(Layout::findNearestChildWidgetIndex, this);
        }
        else
        {
            onPassFocusToChild = CC_CALLBACK_2(Layout::findFarthestChildWidgetIndex, this);
        }
    }
    else if(dir == FocusDirection::UP)
    {
        if (previousWidgetPosition.y < widgetPosition.y)
        {
            onPassFocusToChild = CC_CALLBACK_2(Layout::findNearestChildWidgetIndex, this);
        }
        else
        {
            onPassFocusToChild = CC_CALLBACK_2(Layout::findFarthestChildWidgetIndex, this);
        }
    }
    else
    {
        CCASSERT(0, "invalid direction!");
    }

}


Widget* Layout::passFocusToChild(FocusDirection dir, cocos2d::ui::Widget *current)
{
    if (checkFocusEnabledChild())
    {
        Widget* previousWidget = this->getCurrentFocusedWidget();
        
        this->findProperSearchingFunctor(dir, previousWidget);
        
        int index = onPassFocusToChild(dir, previousWidget);
        
        Widget *widget = this->getChildWidgetByIndex(index);
        Layout *layout = dynamic_cast<Layout*>(widget);
        if (layout)
        {
            layout->_isFocusPassing = true;
            return layout->findNextFocusedWidget(dir, layout);
        }
        else
        {
            this->dispatchFocusEvent(current, widget);
            return widget;
        }
    }
    else
    {
        return this;
    }
        
}

bool Layout::checkFocusEnabledChild()const
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

Widget* Layout::getChildWidgetByIndex(ssize_t index)const
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
            Layout* layout = dynamic_cast<Layout*>(nextWidget);
            if (layout)
            {
                layout->_isFocusPassing = true;
                return layout->findNextFocusedWidget(direction, layout);
            }
            this->dispatchFocusEvent(current, nextWidget);
            return nextWidget;
        }
        else
        {
            //handling the disabled widget, there is no actual focus lose or get, so we don't need any envet
            return this->getPreviousFocusedWidget(direction, nextWidget);
        }
    }
    else
    {
        if (_loopFocus)
        {
            if (checkFocusEnabledChild())
            {
                previousWidgetPos = _children.size()-1;
                nextWidget = this->getChildWidgetByIndex(previousWidgetPos);
                if (nextWidget->isFocusEnabled())
                {
                    Layout* layout = dynamic_cast<Layout*>(nextWidget);
                    if (layout)
                    {
                        layout->_isFocusPassing = true;
                        return layout->findNextFocusedWidget(direction, layout);
                    }
                    else
                    {
                        this->dispatchFocusEvent(current, nextWidget);
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
                if (dynamic_cast<Layout*>(current))
                {
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
                    return Widget::findNextFocusedWidget(direction, this);
                }
                if (dynamic_cast<Layout*>(current))
                {
                    return current;
                }
                else
                {
                    return _focusedWidget;
                }
            }
            else
            {
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
                Layout* layout = dynamic_cast<Layout*>(nextWidget);
                if (layout)
                {
                    layout->_isFocusPassing = true;
                    return layout->findNextFocusedWidget(direction, layout);
                }
                else
                {
                    this->dispatchFocusEvent(current, nextWidget);
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
    }
    else
    {
        if (_loopFocus)
        {
            if (checkFocusEnabledChild())
            {
                previousWidgetPos = 0;
                nextWidget = this->getChildWidgetByIndex(previousWidgetPos);
                if (nextWidget->isFocusEnabled())
                {
                    Layout* layout = dynamic_cast<Layout*>(nextWidget);
                    if (layout)
                    {
                        layout->_isFocusPassing = true;
                        return layout->findNextFocusedWidget(direction, layout);
                    }
                    else
                    {
                        this->dispatchFocusEvent(current, nextWidget);
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
        else
        {
            if (isLastWidgetInContainer(current, direction))
            {
                if (isWidgetAncestorSupportLoopFocus(this, direction))
                {
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
                return Widget::findNextFocusedWidget(direction, this);
            }
        }
    }
}

bool  Layout::isLastWidgetInContainer(Widget* widget, FocusDirection direction)const
{
    Layout* parent = dynamic_cast<Layout*>(widget->getParent());
    if (parent == nullptr)
    {
        return true;
    }
    
    auto& container = parent->getChildren();
    ssize_t index = container.getIndex(widget);
    if (parent->getLayoutType() == Type::HORIZONTAL)
    {
        if (direction == FocusDirection::LEFT)
        {
            if (index == 0)
            {
                return isLastWidgetInContainer(parent, direction);
            }
            else
            {
                return false;
            }
        }
        if (direction == FocusDirection::RIGHT)
        {
            if (index == container.size()-1)
            {
                return isLastWidgetInContainer(parent, direction);
            }
            else
            {
                return false;
            }
        }
        if (direction == FocusDirection::DOWN)
        {
            return isLastWidgetInContainer(parent, direction);
        }
        
        if (direction == FocusDirection::UP)
        {
            return isLastWidgetInContainer(parent, direction);
        }
    }
    else if(parent->getLayoutType() == Type::VERTICAL)
    {
        if (direction == FocusDirection::UP)
        {
            if (index == 0)
            {
                return isLastWidgetInContainer(parent, direction);
                
            }
            else
            {
                return false;
            }
        }
        if (direction == FocusDirection::DOWN)
        {
            if (index == container.size() - 1)
            {
                return isLastWidgetInContainer(parent, direction);
            }
            else
            {
                return false;
            }
        }
        if (direction == FocusDirection::LEFT)
        {
            return isLastWidgetInContainer(parent, direction);
        }
        
        if (direction == FocusDirection::RIGHT)
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

bool  Layout::isWidgetAncestorSupportLoopFocus(Widget* widget, FocusDirection direction)const
{
    Layout* parent = dynamic_cast<Layout*>(widget->getParent());
    if (parent == nullptr)
    {
        return false;
    }
    if (parent->isLoopFocus())
    {
        auto layoutType = parent->getLayoutType();
        if (layoutType == Type::HORIZONTAL)
        {
            if (direction == FocusDirection::LEFT || direction == FocusDirection::RIGHT)
            {
                return true;
            }
            else
            {
                return isWidgetAncestorSupportLoopFocus(parent, direction);
            }
        }
        if (layoutType == Type::VERTICAL)
        {
            if (direction == FocusDirection::DOWN || direction == FocusDirection::UP)
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
            return false;
        }
    }
    else
    {
        return isWidgetAncestorSupportLoopFocus(parent, direction);
    }
}

Widget* Layout::findNextFocusedWidget(FocusDirection direction, Widget* current)
{
    if (_isFocusPassing || this->isFocused())
    {
        Layout* parent = dynamic_cast<Layout*>(this->getParent());
        _isFocusPassing = false;
        
        if (_passFocusToChild)
        {
            Widget * w = this->passFocusToChild(direction, current);
            if (dynamic_cast<Layout*>(w))
            {
                if (parent)
                {
                    parent->_isFocusPassing = true;
                    return parent->findNextFocusedWidget(direction, this);
                }
            }
            return w;
        }
        
        if (nullptr == parent)
        {
            return this;
        }
        parent->_isFocusPassing = true;
        return parent->findNextFocusedWidget(direction, this);
            
    }
    else if(current->isFocused() || dynamic_cast<Layout*>(current))
    {
        if (_layoutType == Type::HORIZONTAL)
        {
            switch (direction)
            {
                case FocusDirection::LEFT:
                {
                    return this->getPreviousFocusedWidget(direction, current);
                }break;
                case FocusDirection::RIGHT:
                {
                    return this->getNextFocusedWidget(direction, current);
                }break;
                case FocusDirection::DOWN:
                case FocusDirection::UP:
                {
                    if (isLastWidgetInContainer(this, direction))
                    {
                        if (isWidgetAncestorSupportLoopFocus(current, direction))
                        {
                            return Widget::findNextFocusedWidget(direction, this);
                        }
                        return current;
                    }
                    else
                    {
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
        else if (_layoutType == Type::VERTICAL)
        {
            switch (direction)
            {
                case FocusDirection::LEFT:
                case FocusDirection::RIGHT:
                {
                    if (isLastWidgetInContainer(this, direction))
                    {
                        if (isWidgetAncestorSupportLoopFocus(current, direction))
                        {
                            return Widget::findNextFocusedWidget(direction, this);
                        }
                        return current;
                    }
                    else
                    {
                        return Widget::findNextFocusedWidget(direction, this);
                    }
                } break;
                case FocusDirection::DOWN:
                {
                    return getNextFocusedWidget(direction, current);
                }
                    break;
                case FocusDirection::UP:
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
