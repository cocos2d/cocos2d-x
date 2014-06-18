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

#include "UIWidget.h"
#include "../Layouts/UILayout.h"
#include "../System/UIHelper.h"

NS_CC_BEGIN

namespace ui {
    
Widget::Widget():
_enabled(true),
_bright(true),
_touchEnabled(false),
_touchPassedEnabled(false),
_focus(false),
_brightStyle(BRIGHT_NONE),
_touchStartPos(CCPointZero),
_touchMovePos(CCPointZero),
_touchEndPos(CCPointZero),
_touchEventListener(NULL),
_touchEventSelector(NULL),
_name("default"),
_widgetType(WidgetTypeWidget),
_actionTag(0),
_size(CCSizeZero),
_customSize(CCSizeZero),
_ignoreSize(false),
_affectByClipping(false),
_sizeType(SIZE_ABSOLUTE),
_sizePercent(CCPointZero),
_positionType(POSITION_ABSOLUTE),
_positionPercent(CCPointZero),
_reorderWidgetChildDirty(true),
_hitted(false),
_widgetChildren(NULL),
_layoutParameterDictionary(NULL),
_nodes(NULL),
_color(ccWHITE),
_opacity(255),
_flippedX(false),
_flippedY(false),
_scriptObjectDict(NULL)
{
    
}

Widget::~Widget()
{
    _touchEventListener = NULL;
    _touchEventSelector = NULL;
    _widgetChildren->removeAllObjects();
    CC_SAFE_RELEASE(_widgetChildren);
    _layoutParameterDictionary->removeAllObjects();
    CC_SAFE_RELEASE(_layoutParameterDictionary);
    _nodes->removeAllObjects();
    CC_SAFE_RELEASE(_nodes);
    CC_SAFE_RELEASE_NULL(_scriptObjectDict);
}

Widget* Widget::create()
{
    Widget* widget = new Widget();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool Widget::init()
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
        ignoreContentAdaptWithSize(true);
        setAnchorPoint(CCPoint(0.5f, 0.5f));
        return true;
    }
    return false;
}

void Widget::onEnter()
{
    updateSizeAndPosition();
    CCNode::onEnter();
}

void Widget::onExit()
{
    unscheduleUpdate();
    CCNode::onExit();
}
    
void Widget::visit()
{
    if (_enabled)
    {
        CCNode::visit();
    }    
}

void Widget::addChild(CCNode *child)
{
    addChild(child, child->getZOrder(), child->getTag());
}

void Widget::addChild(CCNode * child, int zOrder)
{
    addChild(child, zOrder, child->getTag());
}
    
void Widget::addChild(CCNode* child, int zOrder, int tag)
{
    CCAssert(dynamic_cast<Widget*>(child) != NULL, "Widget only supports Widgets as children");
    CCNode::addChild(child, zOrder, tag);
    _widgetChildren->addObject(child);
}
    
void Widget::sortAllChildren()
{
    _reorderWidgetChildDirty = m_bReorderChildDirty;
    CCNode::sortAllChildren();
    if( _reorderWidgetChildDirty )
    {
        int i,j,length = _widgetChildren->data->num;
        CCNode ** x = (CCNode**)_widgetChildren->data->arr;
        CCNode *tempItem;
        
        // insertion sort
        for(i=1; i<length; i++)
        {
            tempItem = x[i];
            j = i-1;
            
            //continue moving element downwards while zOrder is smaller or when zOrder is the same but mutatedIndex is smaller
            while(j>=0 && ( tempItem->getZOrder() < x[j]->getZOrder() || ( tempItem->getZOrder()== x[j]->getZOrder() && tempItem->getOrderOfArrival() < x[j]->getOrderOfArrival() ) ) )
            {
                x[j+1] = x[j];
                j = j-1;
            }
            x[j+1] = tempItem;
        }
        
        //don't need to check children recursively, that's done in visit of each child
        
        _reorderWidgetChildDirty = false;
    }
}
    
CCNode* Widget::getChildByTag(int aTag)
{
    CCAssert( aTag != kCCNodeTagInvalid, "Invalid tag");
    
    if(_widgetChildren && _widgetChildren->count() > 0)
    {
        CCObject* child;
        CCARRAY_FOREACH(_widgetChildren, child)
        {
            CCNode* pNode = (CCNode*) child;
            if(pNode && pNode->getTag() == aTag)
                return pNode;
        }
    }
    return NULL;
}

CCArray* Widget::getChildren()
{
    return _widgetChildren;
}
    
unsigned int Widget::getChildrenCount() const
{
    return _widgetChildren ? _widgetChildren->count() : 0;
}

Widget* Widget::getWidgetParent()
{
    return dynamic_cast<Widget*>(getParent());
}
    
void Widget::removeFromParent()
{
    removeFromParentAndCleanup(true);
}

void Widget::removeFromParentAndCleanup(bool cleanup)
{
    CCNode::removeFromParentAndCleanup(cleanup);
}
    
void Widget::removeChild(CCNode *child)
{
    removeChild(child, true);
}

void Widget::removeChild(CCNode *child, bool cleanup)
{
    CCNode::removeChild(child, cleanup);
    _widgetChildren->removeObject(child);
}

void Widget::removeChildByTag(int tag, bool cleanup)
{
    CCAssert( tag != kCCNodeTagInvalid, "Invalid tag");
    
    CCNode *child = this->getChildByTag(tag);
    
    if (child == NULL)
    {
        CCLOG("cocos2d: removeChildByTag(tag = %d): child not found!", tag);
    }
    else
    {
        this->removeChild(child, cleanup);
    }
}

void Widget::removeAllChildren()
{
    removeAllChildrenWithCleanup(true);
}
    
void Widget::removeAllChildrenWithCleanup(bool cleanup)
{
    if(_widgetChildren && _widgetChildren->count() > 0)
    {
        CCObject* child;
        CCARRAY_FOREACH(_widgetChildren, child)
        {
            CCNode::removeChild((CCNode*)child, cleanup);
        }
    }
    _widgetChildren->removeAllObjects();
}

void Widget::setEnabled(bool enabled)
{
    _enabled = enabled;
    if(_widgetChildren && _widgetChildren->count() > 0)
    {
        CCObject* child;
        CCARRAY_FOREACH(_widgetChildren, child)
        {
            ((Widget*)child)->setEnabled(enabled);
        }
    }
}

Widget* Widget::getChildByName(const char *name)
{
    if(_widgetChildren && _widgetChildren->count() > 0)
    {
        CCObject* child;
        CCARRAY_FOREACH(_widgetChildren, child)
        {
            Widget* pNode = (Widget*) child;
            if(pNode && strcmp(pNode->getName(), name) == 0)
                return pNode;
        }
    }
    return NULL;
}
    
void Widget::addNode(CCNode* node)
{
    addNode(node, node->getZOrder(), node->getTag());
}
    
void Widget::addNode(CCNode * node, int zOrder)
{
    addNode(node, zOrder, node->getTag());
}
    
void Widget::addNode(CCNode* node, int zOrder, int tag)
{
    CCAssert(dynamic_cast<Widget*>(node) == NULL, "Widget only supports Nodes as renderer");
    CCNode::addChild(node, zOrder, tag);
    _nodes->addObject(node);
}
    
CCNode* Widget::getNodeByTag(int tag)
{
    CCAssert( tag != kCCNodeTagInvalid, "Invalid tag");
    
    if(_nodes && _nodes->count() > 0)
    {
        CCObject* renderer;
        CCARRAY_FOREACH(_nodes, renderer)
        {
            CCNode* pNode = (CCNode*) renderer;
            if(pNode && pNode->getTag() == tag)
                return pNode;
        }
    }
    return NULL;
}
    
CCArray* Widget::getNodes()
{
    return _nodes;
}
    
void Widget::removeNode(CCNode* node)
{
    CCNode::removeChild(node);
    _nodes->removeObject(node);
}
    
void Widget::removeNodeByTag(int tag)
{
    CCAssert( tag != kCCNodeTagInvalid, "Invalid tag");
    
    CCNode *node = this->getNodeByTag(tag);
    
    if (node == NULL)
    {
        CCLOG("cocos2d: removeNodeByTag(tag = %d): child not found!", tag);
    }
    else
    {
        this->removeNode(node);
    }
}
    
void Widget::removeAllNodes()
{
    if(_nodes && _nodes->count() > 0)
    {
        CCObject* renderer;
        CCARRAY_FOREACH(_nodes, renderer)
        {
            CCNode* pNode = (CCNode*) renderer;
            CCNode::removeChild(pNode);
        }
        _nodes->removeAllObjects();
    }
}

void Widget::setSize(const CCSize &size)
{
    _customSize = size;
    if (_ignoreSize)
    {
        _size = getContentSize();
    }
    else
    {
        _size = size;
    }
    if (m_bRunning)
    {
        Widget* widgetParent = getWidgetParent();
        CCSize pSize;
        if (widgetParent)
        {
            pSize = widgetParent->getSize();
        }
        else
        {
            pSize = m_pParent->getContentSize();
        }
        float spx = 0.0f;
        float spy = 0.0f;
        if (pSize.width > 0.0f)
        {
            spx = _customSize.width / pSize.width;
        }
        if (pSize.height > 0.0f)
        {
            spy = _customSize.height / pSize.height;
        }
        _sizePercent = CCPoint(spx, spy);
    }
    onSizeChanged();
}

void Widget::setSizePercent(const CCPoint &percent)
{
    _sizePercent = percent;
    CCSize cSize = _customSize;
    if (m_bRunning)
    {
        Widget* widgetParent = getWidgetParent();
        if (widgetParent)
        {
            cSize = CCSize(widgetParent->getSize().width * percent.x , widgetParent->getSize().height * percent.y);
        }
        else
        {
            cSize = CCSize(m_pParent->getContentSize().width * percent.x , m_pParent->getContentSize().height * percent.y);
        }
    }
    if (_ignoreSize)
    {
        _size = getContentSize();
    }
    else
    {
        _size = cSize;
    }
    _customSize = cSize;
    onSizeChanged();
}

void Widget::updateSizeAndPosition()
{
    Widget* widgetParent = getWidgetParent();
    CCSize pSize;
    if (widgetParent)
    {
        pSize = widgetParent->getLayoutSize();
    }
    else
    {
        pSize = m_pParent->getContentSize();
    }
    updateSizeAndPosition(pSize);
}
    
void Widget::updateSizeAndPosition(const cocos2d::CCSize &parentSize)
{
    switch (_sizeType)
    {
        case SIZE_ABSOLUTE:
        {
            if (_ignoreSize)
            {
                _size = getContentSize();
            }
            else
            {
                _size = _customSize;
            }
            float spx = 0.0f;
            float spy = 0.0f;
            if (parentSize.width > 0.0f)
            {
                spx = _customSize.width / parentSize.width;
            }
            if (parentSize.height > 0.0f)
            {
                spy = _customSize.height / parentSize.height;
            }
            _sizePercent = CCPoint(spx, spy);
            break;
        }
        case SIZE_PERCENT:
        {
            CCSize cSize = CCSize(parentSize.width * _sizePercent.x , parentSize.height * _sizePercent.y);
            if (_ignoreSize)
            {
                _size = getContentSize();
            }
            else
            {
                _size = cSize;
            }
            _customSize = cSize;
            break;
        }
        default:
            break;
    }
    onSizeChanged();
    CCPoint absPos = getPosition();
    switch (_positionType)
    {
        case POSITION_ABSOLUTE:
        {
            if (parentSize.width <= 0.0f || parentSize.height <= 0.0f)
            {
                _positionPercent = CCPointZero;
            }
            else
            {
                _positionPercent = CCPoint(absPos.x / parentSize.width, absPos.y / parentSize.height);
            }
            break;
        }
        case POSITION_PERCENT:
        {
            absPos = CCPoint(parentSize.width * _positionPercent.x, parentSize.height * _positionPercent.y);
            break;
        }
        default:
            break;
    }
    setPosition(absPos);
}

void Widget::setSizeType(SizeType type)
{
    _sizeType = type;
}

SizeType Widget::getSizeType() const
{
    return _sizeType;
}

void Widget::ignoreContentAdaptWithSize(bool ignore)
{
    if (_ignoreSize == ignore)
    {
        return;
    }
    _ignoreSize = ignore;
    if (_ignoreSize)
    {
        CCSize s = getContentSize();
        _size = s;
    }
    else
    {
        _size = _customSize;
    }
    onSizeChanged();
}

bool Widget::isIgnoreContentAdaptWithSize() const
{
    return _ignoreSize;
}

const CCSize& Widget::getSize() const
{
    return _size;
}
    
const CCSize& Widget::getCustomSize() const
{
    return _customSize;
}

const CCPoint& Widget::getSizePercent() const
{
    return _sizePercent;
}

CCPoint Widget::getWorldPosition()
{
    return convertToWorldSpace(CCPointZero);
}

CCNode* Widget::getVirtualRenderer()
{
    return this;
}

void Widget::onSizeChanged()
{
    if(_widgetChildren && _widgetChildren->count() > 0)
    {
        CCObject* child;
        CCARRAY_FOREACH(_widgetChildren, child)
        {
            Widget* pNode = (Widget*) child;
            pNode->updateSizeAndPosition();
        }
    }
}

const CCSize& Widget::getContentSize() const
{
    return _size;
}

void Widget::setTouchEnabled(bool enable)
{
    if (enable == _touchEnabled)
    {
        return;
    }
    _touchEnabled = enable;
}

bool Widget::isTouchEnabled() const
{
    return _touchEnabled;
}

bool Widget::isFocused() const
{
    return _focus;
}

void Widget::setFocused(bool fucos)
{
    if (fucos == _focus)
    {
        return;
    }
    _focus = fucos;
    if (_bright)
    {
        if (_focus)
        {
            setBrightStyle(BRIGHT_HIGHLIGHT);
        }
        else
        {
            setBrightStyle(BRIGHT_NORMAL);
        }
    }
    else
    {
        onPressStateChangedToDisabled();
    }
}

void Widget::setBright(bool bright)
{
    _bright = bright;
    if (_bright)
    {
        _brightStyle = BRIGHT_NONE;
        setBrightStyle(BRIGHT_NORMAL);
    }
    else
    {
        onPressStateChangedToDisabled();
    }
}

void Widget::setBrightStyle(BrightStyle style)
{
    if (_brightStyle == style)
    {
        return;
    }
    _brightStyle = style;
    switch (_brightStyle)
    {
        case BRIGHT_NORMAL:
            onPressStateChangedToNormal();
            break;
        case BRIGHT_HIGHLIGHT:
            onPressStateChangedToPressed();
            break;
        default:
            break;
    }
}

void Widget::onPressStateChangedToNormal()
{
    
}

void Widget::onPressStateChangedToPressed()
{
    
}

void Widget::onPressStateChangedToDisabled()
{
    
}

void Widget::didNotSelectSelf()
{
    
}

bool Widget::onTouchBegan(CCTouch *touch, CCEvent *unused_event)
{
    _hitted = false;
    if (isEnabled() && isTouchEnabled())
    {
        _touchStartPos = touch->getLocation();
        if(hitTest(_touchStartPos) && clippingParentAreaContainPoint(_touchStartPos))
        {
            _hitted = true;
        }
    }
    if (!_hitted)
    {
        return false;
    }
    setFocused(true);
    Widget* widgetParent = getWidgetParent();
    if (widgetParent)
    {
        widgetParent->checkChildInfo(0,this,_touchStartPos);
    }
    pushDownEvent();
    return !_touchPassedEnabled;
}

void Widget::onTouchMoved(CCTouch *touch, CCEvent *unused_event)
{
    _touchMovePos = touch->getLocation();
    setFocused(hitTest(_touchMovePos));
    Widget* widgetParent = getWidgetParent();
    if (widgetParent)
    {
        widgetParent->checkChildInfo(1,this,_touchMovePos);
    }
    moveEvent();
}

void Widget::onTouchEnded(CCTouch *touch, CCEvent *unused_event)
{
    _touchEndPos = touch->getLocation();
    bool focus = _focus;
    setFocused(false);
    Widget* widgetParent = getWidgetParent();
    if (widgetParent)
    {
        widgetParent->checkChildInfo(2,this,_touchEndPos);
    }
    if (focus)
    {
        releaseUpEvent();
    }
    else
    {
        cancelUpEvent();
    }
}

void Widget::onTouchCancelled(CCTouch *touch, CCEvent *unused_event)
{
    setFocused(false);
    cancelUpEvent();
}

void Widget::pushDownEvent()
{
    if (_touchEventListener && _touchEventSelector)
    {
        (_touchEventListener->*_touchEventSelector)(this,TOUCH_EVENT_BEGAN);
    }
}

void Widget::moveEvent()
{
    if (_touchEventListener && _touchEventSelector)
    {
        (_touchEventListener->*_touchEventSelector)(this,TOUCH_EVENT_MOVED);
    }
}

void Widget::releaseUpEvent()
{
    if (_touchEventListener && _touchEventSelector)
    {
        (_touchEventListener->*_touchEventSelector)(this,TOUCH_EVENT_ENDED);
    }
}

void Widget::cancelUpEvent()
{
    if (_touchEventListener && _touchEventSelector)
    {
        (_touchEventListener->*_touchEventSelector)(this,TOUCH_EVENT_CANCELED);
    }
}

void Widget::addTouchEventListener(CCObject *target, SEL_TouchEvent selector)
{
    _touchEventListener = target;
    _touchEventSelector = selector;
}

bool Widget::hitTest(const CCPoint &pt)
{
    CCPoint nsp = convertToNodeSpace(pt);
    CCRect bb = CCRect(-_size.width * m_obAnchorPoint.x, -_size.height * m_obAnchorPoint.y, _size.width, _size.height);
    if (nsp.x >= bb.origin.x && nsp.x <= bb.origin.x + bb.size.width && nsp.y >= bb.origin.y && nsp.y <= bb.origin.y + bb.size.height)
    {
        return true;
    }
    return false;
}

bool Widget::clippingParentAreaContainPoint(const CCPoint &pt)
{
    _affectByClipping = false;
    Widget* parent = getWidgetParent();
    Widget* clippingParent = NULL;
    while (parent)
    {
        Layout* layoutParent = dynamic_cast<Layout*>(parent);
        if (layoutParent)
        {
            if (layoutParent->isClippingEnabled())
            {
                _affectByClipping = true;
                clippingParent = layoutParent;
                break;
            }
        }
        parent = parent->getWidgetParent();
    }
    
    if (!_affectByClipping)
    {
        return true;
    }
    
    
    if (clippingParent)
    {
        bool bRet = false;
        if (clippingParent->hitTest(pt))
        {
            bRet = true;
        }
        if (bRet)
        {
            return clippingParent->clippingParentAreaContainPoint(pt);
        }
        return false;
    }
    return true;
}

void Widget::checkChildInfo(int handleState, Widget *sender, const CCPoint &touchPoint)
{
    Widget* widgetParent = getWidgetParent();
    if (widgetParent)
    {
        widgetParent->checkChildInfo(handleState,sender,touchPoint);
    }
}

void Widget::setPosition(const CCPoint &pos)
{
    if (m_bRunning)
    {
        Widget* widgetParent = getWidgetParent();
        if (widgetParent)
        {
            CCSize pSize = widgetParent->getSize();
            if (pSize.width <= 0.0f || pSize.height <= 0.0f)
            {
                _positionPercent = CCPointZero;
            }
            else
            {
                _positionPercent = CCPoint(pos.x / pSize.width, pos.y / pSize.height);
            }
        }
    }
    CCNode::setPosition(pos);
}

void Widget::setPositionPercent(const CCPoint &percent)
{
    _positionPercent = percent;
    if (m_bRunning)
    {
        Widget* widgetParent = getWidgetParent();
        if (widgetParent)
        {
            CCSize parentSize = widgetParent->getSize();
            CCPoint absPos = CCPoint(parentSize.width * _positionPercent.x, parentSize.height * _positionPercent.y);
            setPosition(absPos);
        }
    }
}

void Widget::updateAnchorPoint()
{
    setAnchorPoint(getAnchorPoint());
}

const CCPoint& Widget::getPositionPercent()
{
    return _positionPercent;
}

void Widget::setPositionType(PositionType type)
{
    _positionType = type;
}

PositionType Widget::getPositionType() const
{
    return _positionType;
}
    
bool Widget::isBright() const
{
    return _bright;
}

bool Widget::isEnabled() const
{
    return _enabled;
}

float Widget::getLeftInParent()
{
    return getPosition().x - getAnchorPoint().x * _size.width;;
}

float Widget::getBottomInParent()
{
    return getPosition().y - getAnchorPoint().y * _size.height;;
}

float Widget::getRightInParent()
{
    return getLeftInParent() + _size.width;
}

float Widget::getTopInParent()
{
    return getBottomInParent() + _size.height;
}

const CCPoint& Widget::getTouchStartPos()
{
    return _touchStartPos;
}

const CCPoint& Widget::getTouchMovePos()
{
    return _touchMovePos;
}

const CCPoint& Widget::getTouchEndPos()
{
    return _touchEndPos;
}

void Widget::setName(const char* name)
{
    _name = name;
}

const char* Widget::getName() const
{
    return _name.c_str();
}

WidgetType Widget::getWidgetType() const
{
    return _widgetType;
}

void Widget::setLayoutParameter(LayoutParameter *parameter)
{
    if (!parameter)
    {
        return;
    }
    _layoutParameterDictionary->setObject(parameter, parameter->getLayoutType());
}

LayoutParameter* Widget::getLayoutParameter(LayoutParameterType type)
{
    return dynamic_cast<LayoutParameter*>(_layoutParameterDictionary->objectForKey(type));
}

std::string Widget::getDescription() const
{
    return "Widget";
}

Widget* Widget::clone()
{
    Widget* clonedWidget = createCloneInstance();
    clonedWidget->copyProperties(this);
    clonedWidget->copyClonedWidgetChildren(this);
    return clonedWidget;
}

Widget* Widget::createCloneInstance()
{
    return Widget::create();
}

void Widget::copyClonedWidgetChildren(Widget* model)
{
    ccArray* arrayChildren = model->getChildren()->data;
    int length = arrayChildren->num;
    for (int i=0; i<length; i++)
    {
        Widget* child = static_cast<Widget*>(arrayChildren->arr[i]);
        addChild(child->clone());
    }
}

void Widget::copySpecialProperties(Widget* model)
{
    
}

void Widget::copyProperties(Widget *widget)
{
    setEnabled(widget->isEnabled());
    setVisible(widget->isVisible());
    setBright(widget->isBright());
    setTouchEnabled(widget->isTouchEnabled());
    _touchPassedEnabled = false;
    setZOrder(widget->getZOrder());
    setTag(widget->getTag());
    setName(widget->getName());
    setActionTag(widget->getActionTag());
    _ignoreSize = widget->_ignoreSize;
    _size = widget->_size;
    _customSize = widget->_customSize;
    copySpecialProperties(widget);
    _sizeType = widget->getSizeType();
    _sizePercent = widget->_sizePercent;
    _positionType = widget->_positionType;
    _positionPercent = widget->_positionPercent;
    setPosition(widget->getPosition());
    setAnchorPoint(widget->getAnchorPoint());
    setScaleX(widget->getScaleX());
    setScaleY(widget->getScaleY());
    setRotation(widget->getRotation());
    setRotationX(widget->getRotationX());
    setRotationY(widget->getRotationY());
    setFlipX(widget->isFlipX());
    setFlipY(widget->isFlipY());
    setColor(widget->getColor());
    setOpacity(widget->getOpacity());
    CCDictElement* parameterElement = NULL;
    CCDictionary* layoutParameterDic = widget->_layoutParameterDictionary;
    CCDICT_FOREACH(layoutParameterDic, parameterElement)
    {
        LayoutParameter* parameter = (LayoutParameter*)parameterElement->getObject();
        setLayoutParameter(parameter->clone());
    }
    onSizeChanged();
}

/*temp action*/
void Widget::setActionTag(int tag)
{
	_actionTag = tag;
}

int Widget::getActionTag()
{
	return _actionTag;
}
    
void Widget::setColor(const ccColor3B& color)
{
    _color = color;
    updateTextureColor();
}

void Widget::setOpacity(GLubyte opacity)
{
    _opacity = opacity;
    updateTextureOpacity();
}
    
void Widget::setFlipX(bool flipX)
{
    _flippedX = flipX;
    updateFlippedX();
}
    
void Widget::setFlipY(bool flipY)
{
    _flippedY = flipY;
    updateFlippedY();
}
    
void Widget::updateColorToRenderer(CCNode* renderer)
{
    CCRGBAProtocol* rgbap = dynamic_cast<CCRGBAProtocol*>(renderer);
    if (rgbap)
    {
        rgbap->setColor(_color);
    }
}
    
void Widget::updateOpacityToRenderer(CCNode* renderer)
{
    CCRGBAProtocol* rgbap = dynamic_cast<CCRGBAProtocol*>(renderer);
    if (rgbap)
    {
        rgbap->setOpacity(_opacity);
    }
}
    
void Widget::updateRGBAToRenderer(CCNode* renderer)
{
    CCRGBAProtocol* rgbap = dynamic_cast<CCRGBAProtocol*>(renderer);
    if (rgbap)
    {
        rgbap->setColor(_color);
        rgbap->setOpacity(_opacity);
    }
}
    
void Widget::setScriptObjectDict(cocos2d::CCDictionary* scriptObjectDict)
{
    CC_SAFE_RETAIN(scriptObjectDict);
    CC_SAFE_RELEASE(_scriptObjectDict);
    _scriptObjectDict = scriptObjectDict;
}
    
cocos2d::CCDictionary* Widget::getScriptObjectDict() const
{
    return _scriptObjectDict;
}
    
}

NS_CC_END
