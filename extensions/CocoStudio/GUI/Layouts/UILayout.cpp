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
#include "../System/UIHelper.h"
#include "../../../GUI/CCControlExtension/CCScale9Sprite.h"

NS_CC_BEGIN

namespace ui {
    
static const int BACKGROUNDIMAGE_Z = (-1);
static const int BACKGROUNDCOLOR_RENDERER_Z = (-2);

static GLint g_sStencilBits = -1;
    
IMPLEMENT_CLASS_GUI_INFO(Layout)

Layout::Layout():
_clippingEnabled(false),
_backGroundScale9Enabled(false),
_backGroundImage(NULL),
_backGroundImageFileName(""),
_backGroundImageCapInsets(CCRectZero),
_colorType(LAYOUT_COLOR_NONE),
_bgImageTexType(UI_TEX_TYPE_LOCAL),
_colorRender(NULL),
_gradientRender(NULL),
_cColor(ccWHITE),
_gStartColor(ccWHITE),
_gEndColor(ccWHITE),
_alongVector(CCPoint(0.0f, -1.0f)),
_cOpacity(255),
_backGroundImageTextureSize(CCSizeZero),
_layoutType(LAYOUT_ABSOLUTE),
_clippingType(LAYOUT_CLIPPING_STENCIL),
_clippingStencil(NULL),
_handleScissor(false),
_scissorRectDirty(false),
_clippingRect(CCRectZero),
_clippingParent(NULL),
_doLayoutDirty(true),
_clippingRectDirty(true),
_backGroundImageColor(ccWHITE),
_backGroundImageOpacity(255)
{
    _widgetType = WidgetTypeContainer;
}

Layout::~Layout()
{
    CC_SAFE_RELEASE(_clippingStencil);
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
    return NULL;
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

bool Layout::init()
{
    if (CCNode::init())
    {
        _widgetChildren = CCArray::create();
        CC_SAFE_RETAIN(_widgetChildren);
        _layoutParameterDictionary = CCDictionary::create();
        CC_SAFE_RETAIN(_layoutParameterDictionary);
        _nodes = CCArray::create();
        CC_SAFE_RETAIN(_nodes);
        initRenderer();
        setBright(true);
        ignoreContentAdaptWithSize(false);
        setSize(CCSizeZero);
        setAnchorPoint(CCPointZero);
        return true;
    }
    return false;
}
    
void Layout::addChild(CCNode *child)
{
    addChild(child, child->getZOrder(), child->getTag());
}

void Layout::addChild(CCNode * child, int zOrder)
{
    addChild(child, zOrder, child->getTag());
}

void Layout::addChild(CCNode *child, int zOrder, int tag)
{
    supplyTheLayoutParameterLackToChild(static_cast<Widget*>(child));
    Widget::addChild(child, zOrder, tag);
    _doLayoutDirty = true;
}
    
void Layout::removeChild(CCNode *child)
{
    Widget::removeChild(child);
    _doLayoutDirty = true;
}
    
void Layout::removeChild(CCNode* widget, bool cleanup)
{
    Widget::removeChild(widget, cleanup);
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

bool Layout::isClippingEnabled()
{
    return _clippingEnabled;
}
    
bool Layout::hitTest(const CCPoint &pt)
{
    CCPoint nsp = convertToNodeSpace(pt);
    CCRect bb = CCRect(0.0f, 0.0f, _size.width, _size.height);
    if (nsp.x >= bb.origin.x && nsp.x <= bb.origin.x + bb.size.width && nsp.y >= bb.origin.y && nsp.y <= bb.origin.y + bb.size.height)
    {
        return true;
    }
    return false;
}
    
void Layout::visit()
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
        CCNode::visit();
    }
}
    
void Layout::sortAllChildren()
{
    Widget::sortAllChildren();
    doLayout();
}
    
void Layout::stencilClippingVisit()
{
    if (!_clippingStencil || !_clippingStencil->isVisible())
    {
        CCNode::visit();
        return;
    }
    if (g_sStencilBits < 1)
    {
        CCNode::visit();
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
        CCNode::visit();
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
    ccDrawSolidRect(CCPoint(-1,-1), CCPoint(1,1), ccc4f(1, 1, 1, 1));
    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLPopMatrix();
    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLPopMatrix();
    glStencilFunc(GL_NEVER, mask_layer, mask_layer);
    glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);
    kmGLPushMatrix();
    transform();
    _clippingStencil->visit();
    kmGLPopMatrix();
    glDepthMask(currentDepthWriteMask);
    glStencilFunc(GL_EQUAL, mask_layer_le, mask_layer_le);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    CCNode::visit();
    glStencilFunc(currentStencilFunc, currentStencilRef, currentStencilValueMask);
    glStencilOp(currentStencilFail, currentStencilPassDepthFail, currentStencilPassDepthPass);
    glStencilMask(currentStencilWriteMask);
    if (!currentStencilEnabled)
    {
        glDisable(GL_STENCIL_TEST);
    }
    layer--;
}
    
void Layout::scissorClippingVisit()
{
    CCRect clippingRect = getClippingRect();
    if (_handleScissor)
    {
        glEnable(GL_SCISSOR_TEST);
    }
    CCEGLView::sharedOpenGLView()->setScissorInPoints(clippingRect.origin.x, clippingRect.origin.y, clippingRect.size.width, clippingRect.size.height);
    CCNode::visit();
    if (_handleScissor)
    {
        glDisable(GL_SCISSOR_TEST);
    }
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
                glGetIntegerv(GL_STENCIL_BITS, &g_sStencilBits);
                _clippingStencil = CCDrawNode::create();
                if (m_bRunning)
                {
                    _clippingStencil->onEnter();
                }
                _clippingStencil->retain();
                setStencilClippingSize(_size);
            }
            else
            {
                if (m_bRunning)
                {
                    _clippingStencil->onExit();
                }
                _clippingStencil->release();
                _clippingStencil = NULL;
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
    
void Layout::setStencilClippingSize(const CCSize &size)
{
    if (_clippingEnabled && _clippingType == LAYOUT_CLIPPING_STENCIL)
    {
        CCPoint rect[4];
        rect[0] = CCPointZero;
        rect[1] = CCPoint(_size.width, 0);
        rect[2] = CCPoint(_size.width, _size.height);
        rect[3] = CCPoint(0, _size.height);
        ccColor4F green = ccc4f(0, 1, 0, 1);
        _clippingStencil->clear();
        _clippingStencil->drawPolygon(rect, 4, green, 0, green);
    }
}
    
const CCRect& Layout::getClippingRect()
{
    if (_clippingRectDirty)
    {
        _handleScissor = true;
        CCPoint worldPos = convertToWorldSpace(CCPointZero);
        CCAffineTransform t = nodeToWorldTransform();
        float scissorWidth = _size.width*t.a;
        float scissorHeight = _size.height*t.d;
        CCRect parentClippingRect;
        Layout* parent = this;
        bool firstClippingParentFounded = false;
        while (parent)
        {
            parent = dynamic_cast<Layout*>(parent->getParent());
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
            float finalX = worldPos.x - (scissorWidth * m_obAnchorPoint.x);
            float finalY = worldPos.y - (scissorHeight * m_obAnchorPoint.y);
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
            _clippingRect.origin.x = worldPos.x - (scissorWidth * m_obAnchorPoint.x);
            _clippingRect.origin.y = worldPos.y - (scissorHeight * m_obAnchorPoint.y);
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
    setContentSize(_size);
    setStencilClippingSize(_size);
    _doLayoutDirty = true;
    _clippingRectDirty = true;
    if (_backGroundImage)
    {
        _backGroundImage->setPosition(CCPoint(_size.width/2.0f, _size.height/2.0f));
        if (_backGroundScale9Enabled && _backGroundImage)
        {
            static_cast<extension::CCScale9Sprite*>(_backGroundImage)->setPreferredSize(_size);
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
    CCNode::removeChild(_backGroundImage, true);
    _backGroundImage = NULL;
    _backGroundScale9Enabled = able;
    if (_backGroundScale9Enabled)
    {
        _backGroundImage = extension::CCScale9Sprite::create();
        CCNode::addChild(_backGroundImage, BACKGROUNDIMAGE_Z, -1);
    }
    else
    {
        _backGroundImage = CCSprite::create();
        CCNode::addChild(_backGroundImage, BACKGROUNDIMAGE_Z, -1);
    }
    setBackGroundImage(_backGroundImageFileName.c_str(),_bgImageTexType);    
    setBackGroundImageCapInsets(_backGroundImageCapInsets);
}
    
bool Layout::isBackGroundImageScale9Enabled()
{
    return _backGroundScale9Enabled;
}

void Layout::setBackGroundImage(const char* fileName,TextureResType texType)
{
    if (!fileName || strcmp(fileName, "") == 0)
    {
        return;
    }
    if (_backGroundImage == NULL)
    {
        addBackGroundImage();
    }
    _backGroundImageFileName = fileName;
    _bgImageTexType = texType;
    if (_backGroundScale9Enabled)
    {
        extension::CCScale9Sprite* bgiScale9 = static_cast<extension::CCScale9Sprite*>(_backGroundImage);
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
                static_cast<CCSprite*>(_backGroundImage)->initWithFile(fileName);
                break;
            case UI_TEX_TYPE_PLIST:
                static_cast<CCSprite*>(_backGroundImage)->initWithSpriteFrameName(fileName);
                break;
            default:
                break;
        }
    }
    _backGroundImageTextureSize = _backGroundImage->getContentSize();
    _backGroundImage->setPosition(CCPoint(_size.width/2.0f, _size.height/2.0f));
    updateBackGroundImageRGBA();
}

void Layout::setBackGroundImageCapInsets(const CCRect &capInsets)
{
    _backGroundImageCapInsets = capInsets;
    if (_backGroundScale9Enabled && _backGroundImage)
    {
        static_cast<extension::CCScale9Sprite*>(_backGroundImage)->setCapInsets(capInsets);
    }
}

const CCRect& Layout::getBackGroundImageCapInsets()
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
        _backGroundImage = extension::CCScale9Sprite::create();
        CCNode::addChild(_backGroundImage, BACKGROUNDIMAGE_Z, -1);
        static_cast<extension::CCScale9Sprite*>(_backGroundImage)->setPreferredSize(_size);
    }
    else
    {
        _backGroundImage = CCSprite::create();
        CCNode::addChild(_backGroundImage, BACKGROUNDIMAGE_Z, -1);
    }
    _backGroundImage->setPosition(CCPoint(_size.width/2.0f, _size.height/2.0f));
}

void Layout::removeBackGroundImage()
{
    if (!_backGroundImage)
    {
        return;
    }
    CCNode::removeChild(_backGroundImage, true);
    _backGroundImage = NULL;
    _backGroundImageFileName = "";
    _backGroundImageTextureSize = CCSizeZero;
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
                CCNode::removeChild(_colorRender, true);
                _colorRender = NULL;
            }
            if (_gradientRender)
            {
                CCNode::removeChild(_gradientRender, true);
                _gradientRender = NULL;
            }
            break;
        case LAYOUT_COLOR_SOLID:
            if (_colorRender)
            {
                CCNode::removeChild(_colorRender, true);
                _colorRender = NULL;
            }
            break;
        case LAYOUT_COLOR_GRADIENT:
            if (_gradientRender)
            {
                CCNode::removeChild(_gradientRender, true);
                _gradientRender = NULL;
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
            _colorRender = CCLayerColor::create();
            _colorRender->setContentSize(_size);
            _colorRender->setOpacity(_cOpacity);
            _colorRender->setColor(_cColor);
            CCNode::addChild(_colorRender, BACKGROUNDCOLOR_RENDERER_Z, -1);
            break;
        case LAYOUT_COLOR_GRADIENT:
            _gradientRender = CCLayerGradient::create();
            _gradientRender->setContentSize(_size);
            _gradientRender->setOpacity(_cOpacity);
            _gradientRender->setStartColor(_gStartColor);
            _gradientRender->setEndColor(_gEndColor);
            _gradientRender->setVector(_alongVector);
            CCNode::addChild(_gradientRender, BACKGROUNDCOLOR_RENDERER_Z, -1);
            break;
        default:
            break;
    }
}
    
LayoutBackGroundColorType Layout::getBackGroundColorType()
{
    return _colorType;
}

void Layout::setBackGroundColor(const ccColor3B &color)
{
    _cColor = color;
    if (_colorRender)
    {
        _colorRender->setColor(color);
    }
}
    
const ccColor3B& Layout::getBackGroundColor()
{
    return _cColor;
}

void Layout::setBackGroundColor(const ccColor3B &startColor, const ccColor3B &endColor)
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
    
const ccColor3B& Layout::getBackGroundStartColor()
{
    return _gStartColor;
}

const ccColor3B& Layout::getBackGroundEndColor()
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

void Layout::setBackGroundColorVector(const CCPoint &vector)
{
    _alongVector = vector;
    if (_gradientRender)
    {
        _gradientRender->setVector(vector);
    }
}
    
const CCPoint& Layout::getBackGroundColorVector()
{
    return _alongVector;
}
    
void Layout::setBackGroundImageColor(const ccColor3B &color)
{
    _backGroundImageColor = color;
    updateBackGroundImageColor();
}
    
void Layout::setBackGroundImageOpacity(GLubyte opacity)
{
    _backGroundImageOpacity = opacity;
    updateBackGroundImageOpacity();
}
    
const ccColor3B& Layout::getBackGroundImageColor()
{
    return _backGroundImageColor;
}
    
GLubyte Layout::getBackGroundImageOpacity()
{
    return _backGroundImageOpacity;
}
    
void Layout::updateBackGroundImageColor()
{
    CCRGBAProtocol* rgba = dynamic_cast<CCRGBAProtocol*>(_backGroundImage);
    if (rgba)
    {
        rgba->setColor(_backGroundImageColor);
    }
}
    
void Layout::updateBackGroundImageOpacity()
{
    CCRGBAProtocol* rgba = dynamic_cast<CCRGBAProtocol*>(_backGroundImage);
    if (rgba)
    {
        rgba->setOpacity(_backGroundImageOpacity);
    }
}
    
void Layout::updateBackGroundImageRGBA()
{
    CCRGBAProtocol* rgba = dynamic_cast<CCRGBAProtocol*>(_backGroundImage);
    if (rgba)
    {
        rgba->setColor(_backGroundImageColor);
        rgba->setOpacity(_backGroundImageOpacity);
    }
}

const CCSize& Layout::getBackGroundImageTextureSize() const
{
    return _backGroundImageTextureSize;
}

void Layout::setLayoutType(LayoutType type)
{
    _layoutType = type;
    if(_widgetChildren && _widgetChildren->count() > 0)
    {
        CCObject* child;
        CCARRAY_FOREACH(_widgetChildren, child)
        {
            supplyTheLayoutParameterLackToChild(static_cast<Widget*>(child));
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
    switch (_layoutType)
    {
        case LAYOUT_ABSOLUTE:
            break;
        case LAYOUT_LINEAR_VERTICAL:
        {
            int length = _widgetChildren->count();
            CCSize layoutSize = getSize();
            float topBoundary = layoutSize.height;
            for (int i=0; i<length; ++i)
            {
                Widget* child = static_cast<Widget*>(_widgetChildren->objectAtIndex(i));
                LinearLayoutParameter* layoutParameter = dynamic_cast<LinearLayoutParameter*>(child->getLayoutParameter(LAYOUT_PARAMETER_LINEAR));
                
                if (layoutParameter)
                {
                    LinearGravity childGravity = layoutParameter->getGravity();
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
                    Margin mg = layoutParameter->getMargin();
                    finalPosX += mg.left;
                    finalPosY -= mg.top;
                    child->setPosition(CCPoint(finalPosX, finalPosY));
                    topBoundary = child->getBottomInParent() - mg.bottom;
                }
            }
            break;
        }
        case LAYOUT_LINEAR_HORIZONTAL:
        {
            int length = _widgetChildren->count();
            CCSize layoutSize = getSize();
            float leftBoundary = 0.0f;
            for (int i=0; i<length; ++i)
            {
                Widget* child = static_cast<Widget*>(_widgetChildren->objectAtIndex(i));
                LinearLayoutParameter* layoutParameter = dynamic_cast<LinearLayoutParameter*>(child->getLayoutParameter(LAYOUT_PARAMETER_LINEAR));
                
                if (layoutParameter)
                {
                    LinearGravity childGravity = layoutParameter->getGravity();
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
                    Margin mg = layoutParameter->getMargin();
                    finalPosX += mg.left;
                    finalPosY -= mg.top;
                    child->setPosition(CCPoint(finalPosX, finalPosY));
                    leftBoundary = child->getRightInParent() + mg.right;
                }
            }
            break;
        }
        case LAYOUT_RELATIVE:
        {
            int length = _widgetChildren->count();
            int unlayoutChildCount = length;
            CCSize layoutSize = getSize();
            
            for (int i=0; i<length; i++)
            {
                Widget* child = static_cast<Widget*>(_widgetChildren->objectAtIndex(i));
                RelativeLayoutParameter* layoutParameter = dynamic_cast<RelativeLayoutParameter*>(child->getLayoutParameter(LAYOUT_PARAMETER_RELATIVE));
                layoutParameter->_put = false;
            }
            
            while (unlayoutChildCount > 0)
            {
                for (int i=0; i<length; i++)
                {
                    Widget* child = static_cast<Widget*>(_widgetChildren->objectAtIndex(i));
                    RelativeLayoutParameter* layoutParameter = dynamic_cast<RelativeLayoutParameter*>(child->getLayoutParameter(LAYOUT_PARAMETER_RELATIVE));
                    
                    if (layoutParameter)
                    {
                        if (layoutParameter->_put)
                        {
                            continue;
                        }
                        CCPoint ap = child->getAnchorPoint();
                        CCSize cs = child->getSize();
                        RelativeAlign align = layoutParameter->getAlign();
                        const char* relativeName = layoutParameter->getRelativeToWidgetName();
                        Widget* relativeWidget = NULL;
                        RelativeLayoutParameter* relativeWidgetLP = NULL;
                        float finalPosX = 0.0f;
                        float finalPosY = 0.0f;
                        if (relativeName && strcmp(relativeName, ""))
                        {
                            relativeWidget = UIHelper::seekWidgetByRelativeName(this, relativeName);
                            if (relativeWidget)
                            {
                                relativeWidgetLP = dynamic_cast<RelativeLayoutParameter*>(relativeWidget->getLayoutParameter(LAYOUT_PARAMETER_RELATIVE));
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
                                    CCSize rbs = relativeWidget->getSize();
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
                                    CCSize rbs = relativeWidget->getSize();
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
                                    CCSize rbs = relativeWidget->getSize();
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
                                    CCSize rbs = relativeWidget->getSize();
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
                        child->setPosition(CCPoint(finalPosX, finalPosY));
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