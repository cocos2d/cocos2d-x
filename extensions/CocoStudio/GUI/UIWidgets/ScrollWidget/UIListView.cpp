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

#include "UIListView.h"

NS_CC_EXT_BEGIN

UIListView::UIListView()
: _direction(LISTVIEW_DIR_VERTICAL)
, _moveDirection(LISTVIEW_MOVE_DIR_NONE)
, _touchStartLocation(0.0f)
, _touchEndLocation(0.0f)
, _touchMoveStartLocation(0.0f)
, _topBoundary(0.0f)
, _bottomBoundary(0.0f)
, _leftBoundary(0.0f)
, _rightBoundary(0.0f)
, _autoScroll(false)
, _autoScrollOriginalSpeed(0.0f)
, _autoScrollAcceleration(600.0f)
, _bePressed(false)
, _slidTime(0.0f)
, _childFocusCancelOffset(5.0f)
, _eventListener(NULL)
, _eventSelector(NULL)
, _childPool(NULL)
, _updatePool(NULL)
, _dataLength(0)
, _begin(0)
, _end(0)
, _updateChild(NULL)
, _updateDataIndex(-1)
, _updateSuccess(false)
, _overTopArray(NULL)
, _overBottomArray(NULL)
, _overLeftArray(NULL)
, _overRightArray(NULL)
, _disBoundaryToChild_0(0.0f)
, _disBetweenChild(0.0f)
, _scrollDegreeRange(45.0f)
{
}

UIListView::~UIListView()
{
    CC_SAFE_RELEASE_NULL(_childPool);
    CC_SAFE_RELEASE_NULL(_updatePool);
    CC_SAFE_RELEASE_NULL(_overTopArray);
    CC_SAFE_RELEASE_NULL(_overBottomArray);
    CC_SAFE_RELEASE_NULL(_overLeftArray);
    CC_SAFE_RELEASE_NULL(_overRightArray);
}

UIListView* UIListView::create()
{
    UIListView* widget = new UIListView();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool UIListView::init()
{
    if (Layout::init())
    {
        setUpdateEnabled(true);
        setTouchEnabled(true);
        setClippingEnabled(true);
        
        _childPool = CCArray::create();
        _updatePool = CCArray::create();
        CC_SAFE_RETAIN(_childPool);
        CC_SAFE_RETAIN(_updatePool);
        _overTopArray = cocos2d::CCArray::create();
        _overBottomArray = cocos2d::CCArray::create();
        _overLeftArray = cocos2d::CCArray::create();
        _overRightArray = cocos2d::CCArray::create();
        CC_SAFE_RETAIN(_overTopArray);
        CC_SAFE_RETAIN(_overBottomArray);
        CC_SAFE_RETAIN(_overLeftArray);
        CC_SAFE_RETAIN(_overRightArray);
        
        return true;
    }
    return false;
}

void UIListView::onSizeChanged()
{
    Layout::onSizeChanged();
    _topBoundary = _size.height;
    _rightBoundary = _size.width;
}

bool UIListView::addChild(UIWidget* widget)
{
    Layout::addChild(widget);
    resetProperty();
    return true;
}

void UIListView::removeAllChildren()
{
    _updatePool->removeAllObjects();
    _childPool->removeAllObjects();
    Layout::removeAllChildren();
}

bool UIListView::removeChild(UIWidget* child)
{
    bool value = false;
    
    if (Layout::removeChild(child))
    {
        value = true;
        resetProperty();
    }
    
    return value;
}

bool UIListView::onTouchBegan(const Point &touchPoint)
{
    bool pass = Layout::onTouchBegan(touchPoint);
    handlePressLogic(touchPoint);
    return pass;    
}

void UIListView::onTouchMoved(const Point &touchPoint)
{
    Layout::onTouchMoved(touchPoint);
    handleMoveLogic(touchPoint);
}

void UIListView::onTouchEnded(const Point &touchPoint)
{
    Layout::onTouchEnded(touchPoint);
    handleReleaseLogic(touchPoint);
}

void UIListView::onTouchCancelled(const Point &touchPoint)
{
    Layout::onTouchCancelled(touchPoint);
}

void UIListView::onTouchLongClicked(const Point &touchPoint)
{
    
}

void UIListView::update(float dt)
{
    if (_autoScroll)
    {
        autoScrollChildren(dt);
    }
    recordSlidTime(dt);
}

void UIListView::setDirection(ListViewDirection dir)
{
    _direction = dir;
}

ListViewDirection UIListView::getDirection()
{
    return _direction;
}

void UIListView::resetProperty()
{
    ccArray* arrayChildren = _children->data;
    
    if (arrayChildren->num <= 0)
    {
        return;
    }    
    
    switch (_direction)
    {
        case LISTVIEW_DIR_VERTICAL: // vertical
            if (_topBoundary == 0)
            {
                return;
            }
            break;
            
        case LISTVIEW_DIR_HORIZONTAL: // horizontal
            if (_rightBoundary == 0)
            {
                return;
            }
            break;
            
        default:
            break;
    }
    
    float scroll_top = _topBoundary;
    float scroll_left = _leftBoundary;
    
    switch (_children->count())
    {
        case 1:
        {
            UIWidget* child_0 = dynamic_cast<UIWidget*>(arrayChildren->arr[0]);            
            
            switch (_direction)
            {
                case LISTVIEW_DIR_VERTICAL: // vertical
                {
                    float child_0_top = child_0->getTopInParent();
                    _disBoundaryToChild_0 = scroll_top - child_0_top;
                }
                    break;
                    
                case LISTVIEW_DIR_HORIZONTAL: // horizontal
                {
                    float child_0_left = child_0->getLeftInParent();
                    _disBoundaryToChild_0 = child_0_left - scroll_left;
                }
                    break;
                    
                default:
                    break;
            }
        }
            break;
            
        default:
        {
            UIWidget* child_0 = dynamic_cast<UIWidget*>(arrayChildren->arr[0]);
            UIWidget* child_1 = dynamic_cast<UIWidget*>(arrayChildren->arr[1]);                        
            
            switch (_direction)
            {
                case LISTVIEW_DIR_VERTICAL: // vertical
                {
                    float child_0_top = child_0->getTopInParent();
                    _disBoundaryToChild_0 = scroll_top - child_0_top;
                    _disBetweenChild = child_0->getPosition().y - child_1->getPosition().y;
                }
                    break;
                    
                case LISTVIEW_DIR_HORIZONTAL: // horizontal
                {
                    float child_0_left = child_0->getLeftInParent();
                    _disBoundaryToChild_0 = child_0_left - scroll_left;
                    _disBetweenChild = child_1->getPosition().x - child_0->getPosition().x;
                }
                    break;
                    
                default:
                    break;
            }
        }
            break;
    }
}

void UIListView::handlePressLogic(const Point &touchPoint)
{
    Point nsp = _renderer->convertToNodeSpace(touchPoint);
    
    switch (_direction)
    {
        case LISTVIEW_DIR_VERTICAL: // vertical
            _touchMoveStartLocation = nsp.y;
            _touchStartLocation = nsp.y;
            break;
            
        case LISTVIEW_DIR_HORIZONTAL: // horizontal
            _touchMoveStartLocation = nsp.x;
            _touchStartLocation = nsp.x;
            break;
            
        default:
            break;
    }
    startRecordSlidAction();
    clearCollectOverArray();
}

void UIListView::handleMoveLogic(const Point &touchPoint)
{
    Point nsp = _renderer->convertToNodeSpace(touchPoint);
    float offset = 0.0f;
    
    switch (_direction)
    {
        case LISTVIEW_DIR_VERTICAL: // vertical
        {
            float moveY = nsp.y;
            offset = moveY - _touchMoveStartLocation;
            _touchMoveStartLocation = moveY;
            
            if (offset < 0.0f)
            {
                _moveDirection = LISTVIEW_MOVE_DIR_DOWN; // down
            }
            else if (offset > 0.0f)
            {
                _moveDirection = LISTVIEW_MOVE_DIR_UP; // up
            }
        }
            break;
            
        case LISTVIEW_DIR_HORIZONTAL: // horizontal
        {
            float moveX = nsp.x;
            offset = moveX - _touchMoveStartLocation;
            _touchMoveStartLocation = moveX;
            
            if (offset < 0)
            {
                _moveDirection = LISTVIEW_MOVE_DIR_LEFT; // left
            }
            else if (offset > 0)
            {
                _moveDirection = LISTVIEW_MOVE_DIR_RIGHT; // right
            }
        }
            break;
            
        default:
            break;
    }
    scrollChildren(offset);
}

void UIListView::handleReleaseLogic(const Point &touchPoint)
{
    Point nsp = _renderer->convertToNodeSpace(touchPoint);
    
    switch (_direction)
    {
        case LISTVIEW_DIR_VERTICAL: // vertical
            _touchEndLocation = nsp.y;
            break;
            
        case LISTVIEW_DIR_HORIZONTAL: // horizontal
            _touchEndLocation = nsp.x;
            break;
            
        default:
            break;
    }
    endRecordSlidAction();
}

void UIListView::interceptTouchEvent(int handleState, UIWidget *sender, const Point &touchPoint)
{
    switch (handleState)
    {
        case 0:
            handlePressLogic(touchPoint);
            break;
            
        case 1:
        {
            float offset = 0;
            switch (_direction)
            {
                case LISTVIEW_DIR_VERTICAL: // vertical
                    offset = fabs(sender->getTouchStartPos().y - touchPoint.y);
                    break;
                    
                case LISTVIEW_DIR_HORIZONTAL: // horizontal
                    offset = fabs(sender->getTouchStartPos().x - touchPoint.x);
                    break;
                    
                default:
                    break;
            }
            if (offset > _childFocusCancelOffset)
            {
                sender->setFocused(false);
                handleMoveLogic(touchPoint);
            }
        }
            break;
            
        case 2:
            handleReleaseLogic(touchPoint);
            break;
            
        case 3:
            break;
    }
}

void UIListView::checkChildInfo(int handleState,UIWidget* sender,const Point &touchPoint)
{
    interceptTouchEvent(handleState, sender, touchPoint);
}

void UIListView::moveChildren(float offset)
{
    switch (_direction)
    {
        case LISTVIEW_DIR_VERTICAL: // vertical
        {
            ccArray* arrayChildren = _children->data;
            int childrenCount = arrayChildren->num;
            for (int i = 0; i < childrenCount; i++)
            {
                UIWidget* child = (UIWidget*)(arrayChildren->arr[i]);
                _moveChildPoint.x = child->getPosition().x;
                _moveChildPoint.y = child->getPosition().y + offset;
                child->setPosition(_moveChildPoint);
            }
            break;
        }
            
        case LISTVIEW_DIR_HORIZONTAL: // horizontal
        {
            ccArray* arrayChildren = _children->data;
            int childrenCount = arrayChildren->num;
            for (int i=0;i<childrenCount;i++)
            {
                UIWidget* child = (UIWidget*)(arrayChildren->arr[i]);
                _moveChildPoint.x = child->getPosition().x + offset;
                _moveChildPoint.y = child->getPosition().y;
                child->setPosition(_moveChildPoint);
            }
            break;
        }
            
        default:
            break;
    }
}

bool UIListView::scrollChildren(float touchOffset)
{
    float realOffset = touchOffset;
    
    switch (_direction)
    {
        case LISTVIEW_DIR_VERTICAL: // vertical            
            switch (_moveDirection)
            {
                case LISTVIEW_MOVE_DIR_UP: // up
                    {
                        realOffset = MIN(realOffset, _disBetweenChild);
                        
                        UIWidget* child_last = dynamic_cast<UIWidget*>(_childPool->getLastObject());
                        float child_last_bottom = child_last->getBottomInParent();
                        float scroll_bottom = _bottomBoundary;
                        
                        if (_end == _dataLength - 1)
                        {
                            if (realOffset > scroll_bottom + _disBoundaryToChild_0 - child_last_bottom)
                            {
                                realOffset = scroll_bottom + _disBoundaryToChild_0 - child_last_bottom;
                            }
                            moveChildren(realOffset);
                            return false;
                        }
                        moveChildren(realOffset);
                        
                        if (_end < _dataLength - 1)
                        {
                            collectOverTopChild();
                            unsigned int count = _overTopArray->count();
                            if (count > 0)
                            {
                                updateChild();
                                setLoopPosition();
                                _overTopArray->removeAllObjects();
                            }
                        }
                    }
                    break;
                    
                case LISTVIEW_MOVE_DIR_DOWN: // down
                    {
                        realOffset = MAX(realOffset, -_disBetweenChild);
                        
                        UIWidget* child_0 = dynamic_cast<UIWidget*>(_childPool->getObjectAtIndex(0));
                        float child_0_top = child_0->getTopInParent();
                        float scroll_top = _topBoundary;
                        
                        if (_begin == 0)
                        {
                            if (realOffset < scroll_top - _disBoundaryToChild_0 - child_0_top)
                            {
                                realOffset = scroll_top - _disBoundaryToChild_0 - child_0_top;
                            }
                            moveChildren(realOffset);
                            return false;
                        }
                        moveChildren(realOffset);
                                                
                        if (_begin > 0)
                        {
                            collectOverBottomChild();
                            int count = _overBottomArray->count();
                            if (count > 0)
                            {                                
                                updateChild();
                                setLoopPosition();
                                _overBottomArray->removeAllObjects();
                            }
                        }
                    }
                    break;
                    
                default:
                    break;
            }                                                                
            return true;
            break;
            
        case LISTVIEW_DIR_HORIZONTAL: // horizontal
            switch (_moveDirection)
            {
                case LISTVIEW_MOVE_DIR_LEFT: // left
                    {
                        realOffset = MAX(realOffset, -_disBetweenChild);
                        
                        UIWidget* child_last = dynamic_cast<UIWidget*>(_childPool->getLastObject());
                        float child_last_right = child_last->getRightInParent();
                        float scroll_right = _rightBoundary;
                        
                        if (_end == _dataLength - 1)
                        {
                            if (realOffset < scroll_right - _disBoundaryToChild_0 - child_last_right)
                            {
                                realOffset = scroll_right - _disBoundaryToChild_0 - child_last_right;
                            }
                            moveChildren(realOffset);
                            return false;
                        }
                        moveChildren(realOffset);
                                                
                        if (_end < _dataLength - 1)
                        {
                            collectOverLeftChild();
                            int count = _overLeftArray->count();
                            if (count > 0)
                            {
                                updateChild();
                                setLoopPosition();
                                _overLeftArray->removeAllObjects();
                            }
                        }                                                                                                                
                    }
                    break;
                    
                case LISTVIEW_MOVE_DIR_RIGHT: // right
                    {
                        realOffset = MIN(realOffset, _disBetweenChild);
                        
                        UIWidget* child_0 = dynamic_cast<UIWidget*>(_childPool->getObjectAtIndex(0));
                        float child_0_left = child_0->getLeftInParent();
                        float scroll_left = _leftBoundary;
                        
                        if (_begin == 0)
                        {
                            if (realOffset > scroll_left + _disBoundaryToChild_0 - child_0_left)
                            {
                                realOffset = scroll_left + _disBoundaryToChild_0 - child_0_left;
                            }
                            moveChildren(realOffset);
                            return false;
                        }
                        moveChildren(realOffset);
                                                
                        collectOverRightChild();
                        int count = _overRightArray->count();
                        if (count > 0)
                        {
                            updateChild();
                            setLoopPosition();
                            _overRightArray->removeAllObjects();
                        }                                                                                    
                    }
                    break;
                    
                default:
                    break;
            }                                                                                                      
            return true;
            break;
            
        default:
            break;
    }
    
    return false;
}

void UIListView::autoScrollChildren(float dt)
{
    switch (_direction)
    {
        case LISTVIEW_DIR_VERTICAL: // vertical
            switch (_moveDirection)
        {
            case LISTVIEW_MOVE_DIR_UP: // up
            {
                float curDis = getCurAutoScrollDistance(dt);
                if (curDis <= 0)
                {
                    curDis = 0;
                    stopAutoScrollChildren();
                }
                if (!scrollChildren(curDis))
                {
                    stopAutoScrollChildren();
                }
            }
                break;
                
            case LISTVIEW_MOVE_DIR_DOWN: // down
            {
                float curDis = getCurAutoScrollDistance(dt);
                if (curDis <= 0)
                {
                    curDis = 0;
                    stopAutoScrollChildren();
                }
                if (!scrollChildren(-curDis))
                {
                    stopAutoScrollChildren();
                }
            }
                break;
                
            default:
                break;
        }
            break;
            
        case LISTVIEW_DIR_HORIZONTAL: // horizontal
            switch (_moveDirection)
        {
            case LISTVIEW_MOVE_DIR_LEFT: // left
            {
                float curDis = getCurAutoScrollDistance(dt);
                if (curDis <= 0)
                {
                    curDis = 0;
                    stopAutoScrollChildren();
                }
                if (!scrollChildren(-curDis))
                {
                    stopAutoScrollChildren();
                }
            }
                break;
                
            case LISTVIEW_MOVE_DIR_RIGHT: // right
            {
                float curDis = getCurAutoScrollDistance(dt);
                if (curDis <= 0)
                {
                    curDis = 0;
                    stopAutoScrollChildren();
                }
                if (!scrollChildren(curDis))
                {
                    stopAutoScrollChildren();
                }
            }
                break;
                
            default:
                break;
        }
            break;
            
        default:
            break;
    }
}

float UIListView::getCurAutoScrollDistance(float time)
{
    float dt = time;
    _autoScrollOriginalSpeed -= _autoScrollAcceleration*dt;
    return _autoScrollOriginalSpeed*dt;
}

void UIListView::startAutoScrollChildren(float v)
{
    _autoScrollOriginalSpeed = v;
    _autoScroll = true;
}

void UIListView::stopAutoScrollChildren()
{
    _autoScroll = false;
    _autoScrollOriginalSpeed = 0.0f;
}

void UIListView::recordSlidTime(float dt)
{
    if (_bePressed)
    {
        _slidTime += dt;
    }
}

void UIListView::startRecordSlidAction()
{
    if (_children->count() <= 0)
    {
        return;
    }
    if (_autoScroll)
    {
        stopAutoScrollChildren();
    }
    _bePressed = true;
    _slidTime = 0.0;
}

void UIListView::endRecordSlidAction()
{
    if (_children->count() <= 0)
    {
        return;
    }
    if (_slidTime <= 0.016f)
    {
        return;
    }
    float totalDis = 0;
    totalDis = _touchEndLocation-_touchStartLocation;
    float orSpeed = fabs(totalDis)/(_slidTime);
    startAutoScrollChildren(orSpeed / 4);
    
    _bePressed = false;
    _slidTime = 0.0;
}

UIWidget* UIListView::getCheckPositionChild()
{
    UIWidget* child = NULL;
    
    switch (_direction)
    {
        case LISTVIEW_DIR_VERTICAL: // vertical
            switch (_moveDirection)
            {
                case LISTVIEW_MOVE_DIR_UP: // up
                    child = dynamic_cast<UIWidget*>(_childPool->getLastObject());
                    break;
                    
                case LISTVIEW_MOVE_DIR_DOWN: // down
                    child = dynamic_cast<UIWidget*>(_childPool->getObjectAtIndex(0));
                    break;
                    
                default:
                    break;
            }
            break;
            
        case LISTVIEW_DIR_HORIZONTAL: // horizontal
            switch (_moveDirection)
            {
                case LISTVIEW_MOVE_DIR_LEFT: // left
                    child = dynamic_cast<UIWidget*>(_childPool->getLastObject());
                    break;
                    
                case LISTVIEW_MOVE_DIR_RIGHT: // right
                    child = dynamic_cast<UIWidget*>(_childPool->getObjectAtIndex(0));
                    break;
                    
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
    
    return child;
}

void UIListView::initChildWithDataLength(int length)
{
    _dataLength = length;
    _begin = 0;
    _end = 0;
    
    // init child pool
    ccArray* arrayChildren = _children->data;
    int times = arrayChildren->num;
    for (int i = 0; i < times; ++i)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
        setUpdateChild(child);
        setUpdateDataIndex(i);
        initChildEvent();
        _childPool->addObject(child);
        _end = i;
    }
}

UIWidget* UIListView::getChildFromUpdatePool()
{
    UIWidget* child = dynamic_cast<UIWidget*>(_updatePool->getLastObject());
    _updatePool->removeLastObject();
    return child;
}

void UIListView::pushChildToPool()
{
    switch (_direction)
    {
        case LISTVIEW_DIR_VERTICAL: // vertical
            switch (_moveDirection)
            {
                case LISTVIEW_MOVE_DIR_UP: // up
                    {
                        UIWidget* child = dynamic_cast<UIWidget*>(_childPool->getObjectAtIndex(0));
                        _updatePool->insertObject(child, 0);
                        _childPool->removeObjectAtIndex(0);
                    }
                    break;
                    
                case LISTVIEW_MOVE_DIR_DOWN: // down
                    {
                        UIWidget* child = dynamic_cast<UIWidget*>(_childPool->getLastObject());
                        _updatePool->insertObject(child, 0);
                        _childPool->removeLastObject();

                    }
                    break;
                    
                default:
                    break;
            }
            break;
            
        case LISTVIEW_DIR_HORIZONTAL: // horizontal
            switch (_moveDirection)
            {
                case LISTVIEW_MOVE_DIR_LEFT: // left
                    {
                        UIWidget* child = dynamic_cast<UIWidget*>(_childPool->getObjectAtIndex(0));
                        _updatePool->insertObject(child, 0);
                        _childPool->removeObjectAtIndex(0);
                    }
                    break;
                    
                case LISTVIEW_MOVE_DIR_RIGHT: // right
                    {
                        UIWidget* child = dynamic_cast<UIWidget*>(_childPool->getLastObject());
                        _updatePool->insertObject(child, 0);
                        _childPool->removeLastObject();
                    }
                    break;
                
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
}

void UIListView::getAndCallback()
{
    UIWidget* child = getChildFromUpdatePool();
    
    if (child == NULL)
    {
        return;
    }
    
    switch (_direction)
    {
        case LISTVIEW_DIR_VERTICAL: // vertical
            switch (_moveDirection)
            {
                case LISTVIEW_MOVE_DIR_UP: // up
                    ++_end;
                    setUpdateChild(child);
                    setUpdateDataIndex(_end);
                    updateChildEvent();
                    
                    if (_updateSuccess == false)
                    {
                        --_end;
                        _childPool->insertObject(child, 0);
                        return;
                    }
                    ++_begin;
                    break;
                    
                case LISTVIEW_MOVE_DIR_DOWN: // down
                    --_begin;
                    setUpdateChild(child);
                    setUpdateDataIndex(_begin);
                    updateChildEvent();
                    
                    if (_updateSuccess == false)
                    {
                        ++_begin;
                        _childPool->addObject(child);
                        return;
                    }
                    --_end;
                    break;
                    
                default:
                    break;
            }
            break;
            
        case LISTVIEW_DIR_HORIZONTAL: // horizontal
            switch (_moveDirection)
            {
                case LISTVIEW_MOVE_DIR_LEFT: // left
                    ++_end;
                    setUpdateChild(child);
                    setUpdateDataIndex(_end);
                    updateChildEvent();
                    
                    if (_updateSuccess == false)
                    {
                        --_end;
                        _childPool->insertObject(child, 0);
                        return;
                    }
                    ++_begin;
                    break;
                    
                case LISTVIEW_MOVE_DIR_RIGHT: // right
                    --_begin;
                    setUpdateChild(child);
                    setUpdateDataIndex(_begin);
                    updateChildEvent();
                    
                    if (_updateSuccess == false)
                    {
                        ++_begin;
                        _childPool->addObject(child);
                        return;
                    }
                    --_end;
                    break;
                    
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
    
    switch (_direction)
    {
        case LISTVIEW_DIR_VERTICAL: // vertical
            switch (_moveDirection)
            {
                case LISTVIEW_MOVE_DIR_UP: // up
                    _childPool->addObject(child);
                    break;
                    
                case LISTVIEW_MOVE_DIR_DOWN: // down
                    _childPool->insertObject(child, 0);
                    break;
                    
                default:
                    break;
            }
            break;
            
        case LISTVIEW_DIR_HORIZONTAL: // horizontal
            switch (_moveDirection)
            {
                case LISTVIEW_MOVE_DIR_LEFT: // left
                    _childPool->addObject(child);
                    break;
                case LISTVIEW_MOVE_DIR_RIGHT: // right
                    _childPool->insertObject(child, 0);
                    break;
                    
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
}

int UIListView::getDataLength()
{
    return _dataLength;
}        

UIWidget* UIListView::getUpdateChild()
{
    return _updateChild;
}

void UIListView::setUpdateChild(UIWidget* child)
{
    _updateChild = child;
}

int UIListView::getUpdateDataIndex()
{
    return _updateDataIndex;
}

void UIListView::setUpdateDataIndex(int index)
{
    _updateDataIndex = index;
}

bool UIListView::getUpdateSuccess()
{
    return _updateSuccess;
}

void UIListView::setUpdateSuccess(bool sucess)
{
    _updateSuccess = sucess;
}

void UIListView::clearCollectOverArray()
{
    switch (_direction)
    {
        case LISTVIEW_DIR_VERTICAL:
            _overTopArray->removeAllObjects();
            _overBottomArray->removeAllObjects();
            break;
            
        case LISTVIEW_DIR_HORIZONTAL:
            _overLeftArray->removeAllObjects();
            _overRightArray->removeAllObjects();
            break;
            
        default:
            break;
    }
}

void UIListView::collectOverTopChild()
{
    float scroll_top = _topBoundary;
    
    ccArray* arrayChildren = _children->data;
    int times = arrayChildren->num;
    for (int i = 0; i < times; ++i)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
        float child_bottom = child->getBottomInParent();
        
        if (child_bottom >= scroll_top)
        {
            _overTopArray->addObject(child);
        }
    }
}

void UIListView::collectOverBottomChild()
{
    float scroll_bottom = _bottomBoundary;
    
    ccArray* arrayChildren = _children->data;
    int times = arrayChildren->num;
    for (int i = 0; i < times; ++i)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
        float child_top = child->getTopInParent();
        
        if (child_top <= scroll_bottom)
        {
            _overBottomArray->addObject(child);
        }
    }
}

void UIListView::collectOverLeftChild()
{
    float scroll_left = _leftBoundary;
    
    ccArray* arrayChildren = _children->data;
    int times = arrayChildren->num;
    for (int i = 0; i < times; ++i)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
        float child_right = child->getRightInParent();
        
        if (child_right <= scroll_left)
        {
            _overLeftArray->addObject(child);
        }
    }
}

void UIListView::collectOverRightChild()
{
    float scroll_right = _rightBoundary;
    
    ccArray* arrayChildren = _children->data;
    int times = arrayChildren->num;
    for (int i = 0; i < times; ++i)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
        float child_left = child->getLeftInParent();
        if (child_left >= scroll_right)
        {
            _overRightArray->addObject(child);
        }
    }
}

void UIListView::setLoopPosition()
{
    switch (_direction)
    {
        case LISTVIEW_DIR_VERTICAL: // vertical
            switch (_moveDirection)
            {
                case LISTVIEW_MOVE_DIR_UP: // up
                {
                    ccArray* arrayChildren = _children->data;
                    unsigned int childrenCount = arrayChildren->num;
                    
                    if (_overTopArray->count() == childrenCount)
                    {
                        unsigned int count = childrenCount;
                        for (unsigned int i = 0; i < count; ++i)
                        {   
                            UIWidget* child = dynamic_cast<UIWidget*>(_overTopArray->getObjectAtIndex(i));
                            
                            if (i == 0)
                            {
                                float height = child->getSize().height;
                                float offset = (child->getWidgetType() == WidgetTypeWidget) ? height / 2 : height;
                                float y = _topBoundary - _disBoundaryToChild_0 - offset;
                                child->setPosition(Point(child->getPosition().x, y));
                            }
                            else
                            {
                                UIWidget* prev_child = dynamic_cast<UIWidget*>(_overTopArray->getObjectAtIndex(i - 1));
                                child->setPosition(Point(child->getPosition().x, prev_child->getPosition().y - _disBetweenChild));
                            }
                        }
                    }
                    else
                    {
                        float scroll_top = _topBoundary;
                        
                        ccArray* arrayChildren = _children->data;
                        int count = arrayChildren->num;
                        for (int i = 0; i < count; ++i)
                        {
                            UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
                            float child_bottom = child->getBottomInParent();
                            
                            if (child_bottom >= scroll_top)
                            {
                                int index = (i == 0) ? (count - 1) : (i - 1);
                                UIWidget* prev_child = dynamic_cast<UIWidget*>(arrayChildren->arr[index]);
                                child->setPosition(Point(child->getPosition().x, prev_child->getPosition().y - _disBetweenChild));
                            }
                        }
                    }
                }
                    break;
                    
                case LISTVIEW_MOVE_DIR_DOWN: // down
                {
                    ccArray* arrayChildren = _children->data;
                    unsigned int childrenCount = arrayChildren->num;
                    
                    if (_overBottomArray->count() == childrenCount)
                    {
                        unsigned int count = childrenCount;
                        for (unsigned int i = 0; i < count; ++i)
                        {
                            UIWidget* child = dynamic_cast<UIWidget*>(_overBottomArray->getObjectAtIndex(i));
                            
                            if (i == 0)
                            {                                
                                float y = _bottomBoundary + _disBoundaryToChild_0 - _disBetweenChild;
                                child->setPosition(Point(child->getPosition().x, y));
                            }
                            else
                            {
                                UIWidget* prev_child = dynamic_cast<UIWidget*>(_overBottomArray->getObjectAtIndex(i - 1));
                                child->setPosition(Point(child->getPosition().x, prev_child->getPosition().y + _disBetweenChild));
                            }
                        }
                    }
                    else
                    {
                        float scroll_bottom = _bottomBoundary;
                        
                        ccArray* arrayChildren = _children->data;
                        int count = arrayChildren->num;
                        for (int i = count - 1; i >= 0; --i)
                        {
                            UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
                            float child_top = child->getTopInParent();
                            
                            if (child_top <= scroll_bottom)
                            {
                                int index = (i == count - 1) ? 0 : (i + 1);
                                UIWidget* next_child = dynamic_cast<UIWidget*>(arrayChildren->arr[index]);
                                child->setPosition(Point(child->getPosition().x, next_child->getPosition().y + _disBetweenChild));
                            }
                        }
                    }
                }
                    break;
                    
                default:
                    break;
            }
            break;
            
        case LISTVIEW_DIR_HORIZONTAL: // horizontal
            switch (_moveDirection)
            {
                case LISTVIEW_MOVE_DIR_LEFT: // left
                {
                    ccArray* arrayChildren = _children->data;
                    unsigned int childrenCount = arrayChildren->num;
                    
                    if (_overLeftArray->count() == childrenCount)
                    {
                        unsigned int count = childrenCount;
                        for (unsigned int i = 0; i < count; ++i)
                        {
                            UIWidget* child = dynamic_cast<UIWidget*>(_overLeftArray->getObjectAtIndex(i));
                            
                            if (i == 0)
                            {
                                float width = child->getSize().width;
                                float offset = (child->getWidgetType() == WidgetTypeWidget) ? (width / 2) : 0;                                
                                float x = _leftBoundary + _disBoundaryToChild_0 + width + offset;
                                child->setPosition(Point(x, child->getPosition().y));
                            }
                            else
                            {
                                UIWidget* prev_child = dynamic_cast<UIWidget*>(_overLeftArray->getObjectAtIndex(i - 1));
                                child->setPosition(Point(prev_child->getPosition().x + _disBetweenChild, child->getPosition().y));
                            }
                        }
                    }
                    else
                    {
                        float scroll_left = _leftBoundary;
                        
                        ccArray* arrayChildren = _children->data;
                        int count = arrayChildren->num;
                        for (int i = 0; i < count; ++i)
                        {
                            UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
                            float child_right = child->getRightInParent();
                            
                            if (child_right <= scroll_left)
                            {
                                int index = (i == 0) ? (count - 1) : (i - 1);
                                UIWidget* prev_child = dynamic_cast<UIWidget*>(arrayChildren->arr[index]);
                                child->setPosition(Point(prev_child->getPosition().x + _disBetweenChild, child->getPosition().y));
                            }
                        }
                    }
                }
                    break;
                    
                case LISTVIEW_MOVE_DIR_RIGHT: // right
                {
                    ccArray* arrayChildren = _children->data;
                    unsigned int childrenCount = arrayChildren->num;
                    
                    if (_overRightArray->count() == childrenCount)
                    {
                        unsigned int count = childrenCount;
                        for (unsigned int i = 0; i < count; ++i)
                        {
                            UIWidget* child = dynamic_cast<UIWidget*>(_overRightArray->getObjectAtIndex(i));
                            
                            if (i == 0)
                            {
                                float x = _rightBoundary - _disBoundaryToChild_0 + _disBetweenChild;
                                child->setPosition(Point(x, child->getPosition().y));
                            }
                            else
                            {
                                UIWidget* prev_child = dynamic_cast<UIWidget*>(_overRightArray->getObjectAtIndex(i - 1));
                                child->setPosition(Point(prev_child->getPosition().x - _disBetweenChild, child->getPosition().y));
                            }
                        }
                    }
                    else
                    {
                        float scroll_right = _rightBoundary;
                        
                        ccArray* arrayChildren = _children->data;
                        int count = arrayChildren->num;
                        for (int i = count - 1; i >= 0; --i)
                        {
                            UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
                            float child_left = child->getLeftInParent();
                            
                            if (child_left >= scroll_right)
                            {
                                int index = (i == count - 1) ? 0 : (i + 1);
                                UIWidget* next_child = dynamic_cast<UIWidget*>(arrayChildren->arr[index]);
                                child->setPosition(Point(next_child->getPosition().x - _disBetweenChild, child->getPosition().y));
                            }
                        }
                    }
                }
                    break;
                    
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
}

void UIListView::updateChild()
{
    switch (_direction)
    {
        case LISTVIEW_DIR_VERTICAL: // vertical
            switch (_moveDirection)
            {
                case LISTVIEW_MOVE_DIR_UP: // up
                    {
                        int count = _overTopArray->count();
                        for (int i = 0; i < count; ++i)
                        {
                            pushChildToPool();
                            getAndCallback();
                        }
                    }
                    break;
                    
                case LISTVIEW_MOVE_DIR_DOWN: // down
                    {
                        int count = _overBottomArray->count();
                        for (int i = 0; i < count; ++i)
                        {
                            pushChildToPool();
                            getAndCallback();
                        }
                    }
                    break;
                    
                default:
                    break;
            }
            break;
            
        case LISTVIEW_DIR_HORIZONTAL: // horizontal
            switch (_moveDirection)
            {
                case LISTVIEW_MOVE_DIR_LEFT: // left
                    {
                        int count = _overLeftArray->count();
                        for (int i = 0; i < count; ++i)
                        {
                            pushChildToPool();
                            getAndCallback();
                        }
                    }
                    break;
                    
                case LISTVIEW_MOVE_DIR_RIGHT: // right
                    {
                        int count = _overRightArray->count();
                        for (int i = 0; i < count; ++i)
                        {
                            pushChildToPool();
                            getAndCallback();
                        }
                    }
                    break;
                    
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
}

void UIListView::initChildEvent()
{
    if (_eventListener && _eventSelector)
    {
        (_eventListener->*_eventSelector)(this, LISTVIEW_EVENT_INIT_CHILD);
    }
}

void UIListView::updateChildEvent()
{
    if (_eventListener && _eventSelector)
    {
        (_eventListener->*_eventSelector)(this, LISTVIEW_EVENT_UPDATE_CHILD);
    }
}

void UIListView::addEventListenter(Object *target, SEL_ListViewEvent selector)
{
    _eventListener = target;
    _eventSelector = selector;
}

const char* UIListView::getDescription() const
{
    return "ListView";
}


NS_CC_EXT_END