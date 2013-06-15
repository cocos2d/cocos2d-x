/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2010 Sangwoo Im

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

#include "cocos2d.h"
#include "CCTableView.h"
#include "CCTableViewCell.h"
#include "menu_nodes/CCMenu.h"
#include "support/CCPointExtension.h"
#include "CCSorting.h"
#include "layers_scenes_transitions_nodes/CCLayer.h"

NS_CC_EXT_BEGIN

CCTableView* CCTableView::create(CCTableViewDataSource* dataSource, CCSize size)
{
    return CCTableView::create(dataSource, size, NULL);
}

CCTableView* CCTableView::create(CCTableViewDataSource* dataSource, CCSize size, CCNode *container)
{
    CCTableView *table = new CCTableView();
    table->initWithViewSize(size, container);
    table->autorelease();
    table->setDataSource(dataSource);
    table->_updateCellPositions();
    table->_updateContentSize();

    return table;
}

bool CCTableView::initWithViewSize(CCSize size, CCNode* container/* = NULL*/)
{
    if (CCScrollView::initWithViewSize(size,container))
    {
        _cellsUsed      = new CCArrayForObjectSorting();
        _cellsFreed     = new CCArrayForObjectSorting();
        _indices        = new std::set<unsigned int>();
        _vordering      = kCCTableViewFillBottomUp;
        this->setDirection(kCCScrollViewDirectionVertical);

        CCScrollView::setDelegate(this);
        return true;
    }
    return false;
}

CCTableView::CCTableView()
: _touchedCell(NULL)
, _indices(NULL)
, _cellsUsed(NULL)
, _cellsFreed(NULL)
, _dataSource(NULL)
, _tableViewDelegate(NULL)
, _oldDirection(kCCScrollViewDirectionNone)
{

}

CCTableView::~CCTableView()
{
    CC_SAFE_DELETE(_indices);
    CC_SAFE_RELEASE(_cellsUsed);
    CC_SAFE_RELEASE(_cellsFreed);
}

void CCTableView::setVerticalFillOrder(CCTableViewVerticalFillOrder fillOrder)
{
    if (_vordering != fillOrder) {
        _vordering = fillOrder;
        if (_cellsUsed->count() > 0) {
            this->reloadData();
        }
    }
}

CCTableViewVerticalFillOrder CCTableView::getVerticalFillOrder()
{
    return _vordering;
}

void CCTableView::reloadData()
{
    _oldDirection = kCCScrollViewDirectionNone;
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(_cellsUsed, pObj)
    {
        CCTableViewCell* cell = (CCTableViewCell*)pObj;

        if(_tableViewDelegate != NULL) {
            _tableViewDelegate->tableCellWillRecycle(this, cell);
        }

        _cellsFreed->addObject(cell);
        cell->reset();
        if (cell->getParent() == this->getContainer())
        {
            this->getContainer()->removeChild(cell, true);
        }
    }

    _indices->clear();
    _cellsUsed->release();
    _cellsUsed = new CCArrayForObjectSorting();

    this->_updateCellPositions();
    this->_updateContentSize();
    if (_dataSource->numberOfCellsInTableView(this) > 0)
    {
        this->scrollViewDidScroll(this);
    }
}

CCTableViewCell *CCTableView::cellAtIndex(unsigned int idx)
{
    CCTableViewCell *found = NULL;

    if (_indices->find(idx) != _indices->end())
    {
        found = (CCTableViewCell *)_cellsUsed->objectWithObjectID(idx);
    }

    return found;
}

void CCTableView::updateCellAtIndex(unsigned int idx)
{
    if (idx == CC_INVALID_INDEX)
    {
        return;
    }
    unsigned int uCountOfItems = _dataSource->numberOfCellsInTableView(this);
    if (0 == uCountOfItems || idx > uCountOfItems-1)
    {
        return;
    }

    CCTableViewCell* cell = this->cellAtIndex(idx);
    if (cell)
    {
        this->_moveCellOutOfSight(cell);
    }
    cell = _dataSource->tableCellAtIndex(this, idx);
    this->_setIndexForCell(idx, cell);
    this->_addCellIfNecessary(cell);
}

void CCTableView::insertCellAtIndex(unsigned  int idx)
{
    if (idx == CC_INVALID_INDEX)
    {
        return;
    }

    unsigned int uCountOfItems = _dataSource->numberOfCellsInTableView(this);
    if (0 == uCountOfItems || idx > uCountOfItems-1)
    {
        return;
    }

    CCTableViewCell* cell = NULL;
    int newIdx = 0;

    cell = (CCTableViewCell*)_cellsUsed->objectWithObjectID(idx);
    if (cell)
    {
        newIdx = _cellsUsed->indexOfSortedObject(cell);
        for (unsigned int i=newIdx; i<_cellsUsed->count(); i++)
        {
            cell = (CCTableViewCell*)_cellsUsed->objectAtIndex(i);
            this->_setIndexForCell(cell->getIdx()+1, cell);
        }
    }

 //   [_indices shiftIndexesStartingAtIndex:idx by:1];

    //insert a new cell
    cell = _dataSource->tableCellAtIndex(this, idx);
    this->_setIndexForCell(idx, cell);
    this->_addCellIfNecessary(cell);

    this->_updateCellPositions();
    this->_updateContentSize();
}

void CCTableView::removeCellAtIndex(unsigned int idx)
{
    if (idx == CC_INVALID_INDEX)
    {
        return;
    }

    unsigned int uCountOfItems = _dataSource->numberOfCellsInTableView(this);
    if (0 == uCountOfItems || idx > uCountOfItems-1)
    {
        return;
    }

    unsigned int newIdx = 0;

    CCTableViewCell* cell = this->cellAtIndex(idx);
    if (!cell)
    {
        return;
    }

    newIdx = _cellsUsed->indexOfSortedObject(cell);

    //remove first
    this->_moveCellOutOfSight(cell);

    _indices->erase(idx);
    this->_updateCellPositions();
//    [_indices shiftIndexesStartingAtIndex:idx+1 by:-1];
    for (unsigned int i=_cellsUsed->count()-1; i > newIdx; i--)
    {
        cell = (CCTableViewCell*)_cellsUsed->objectAtIndex(i);
        this->_setIndexForCell(cell->getIdx()-1, cell);
    }
}

CCTableViewCell *CCTableView::dequeueCell()
{
    CCTableViewCell *cell;

    if (_cellsFreed->count() == 0) {
        cell = NULL;
    } else {
        cell = (CCTableViewCell*)_cellsFreed->objectAtIndex(0);
        cell->retain();
        _cellsFreed->removeObjectAtIndex(0);
        cell->autorelease();
    }
    return cell;
}

void CCTableView::_addCellIfNecessary(CCTableViewCell * cell)
{
    if (cell->getParent() != this->getContainer())
    {
        this->getContainer()->addChild(cell);
    }
    _cellsUsed->insertSortedObject(cell);
    _indices->insert(cell->getIdx());
    // [_indices addIndex:cell.idx];
}

void CCTableView::_updateContentSize()
{
    CCSize size = CCSizeZero;
    unsigned int cellsCount = _dataSource->numberOfCellsInTableView(this);

    if (cellsCount > 0)
    {
        float maxPosition = _vCellsPositions[cellsCount];

        switch (this->getDirection())
        {
            case kCCScrollViewDirectionHorizontal:
                size = CCSizeMake(maxPosition, _viewSize.height);
                break;
            default:
                size = CCSizeMake(_viewSize.width, maxPosition);
                break;
        }
    }

    this->setContentSize(size);

	if (_oldDirection != _direction)
	{
		if (_direction == kCCScrollViewDirectionHorizontal)
		{
			this->setContentOffset(ccp(0,0));
		}
		else
		{
			this->setContentOffset(ccp(0,this->minContainerOffset().y));
		}
		_oldDirection = _direction;
	}

}

CCPoint CCTableView::_offsetFromIndex(unsigned int index)
{
    CCPoint offset = this->__offsetFromIndex(index);

    const CCSize cellSize = _dataSource->tableCellSizeForIndex(this, index);
    if (_vordering == kCCTableViewFillTopDown)
    {
        offset.y = this->getContainer()->getContentSize().height - offset.y - cellSize.height;
    }
    return offset;
}

CCPoint CCTableView::__offsetFromIndex(unsigned int index)
{
    CCPoint offset;
    CCSize  cellSize;

    switch (this->getDirection())
    {
        case kCCScrollViewDirectionHorizontal:
            offset = ccp(_vCellsPositions[index], 0.0f);
            break;
        default:
            offset = ccp(0.0f, _vCellsPositions[index]);
            break;
    }

    return offset;
}

unsigned int CCTableView::_indexFromOffset(CCPoint offset)
{
    int index = 0;
    const int maxIdx = _dataSource->numberOfCellsInTableView(this)-1;

    if (_vordering == kCCTableViewFillTopDown)
    {
        offset.y = this->getContainer()->getContentSize().height - offset.y;
    }
    index = this->__indexFromOffset(offset);
    if (index != -1)
    {
        index = MAX(0, index);
        if (index > maxIdx)
        {
            index = CC_INVALID_INDEX;
        }
    }

    return index;
}

int CCTableView::__indexFromOffset(CCPoint offset)
{
    int low = 0;
    int high = _dataSource->numberOfCellsInTableView(this) - 1;
    float search;
    switch (this->getDirection())
    {
        case kCCScrollViewDirectionHorizontal:
            search = offset.x;
            break;
        default:
            search = offset.y;
            break;
    }

    while (high >= low)
    {
        int index = low + (high - low) / 2;
        float cellStart = _vCellsPositions[index];
        float cellEnd = _vCellsPositions[index + 1];

        if (search >= cellStart && search <= cellEnd)
        {
            return index;
        }
        else if (search < cellStart)
        {
            high = index - 1;
        }
        else
        {
            low = index + 1;
        }
    }

    if (low <= 0) {
        return 0;
    }

    return -1;
}

void CCTableView::_moveCellOutOfSight(CCTableViewCell *cell)
{
    if(_tableViewDelegate != NULL) {
        _tableViewDelegate->tableCellWillRecycle(this, cell);
    }

    _cellsFreed->addObject(cell);
    _cellsUsed->removeSortedObject(cell);
    _indices->erase(cell->getIdx());
    // [_indices removeIndex:cell.idx];
    cell->reset();
    if (cell->getParent() == this->getContainer()) {
        this->getContainer()->removeChild(cell, true);;
    }
}

void CCTableView::_setIndexForCell(unsigned int index, CCTableViewCell *cell)
{
    cell->setAnchorPoint(ccp(0.0f, 0.0f));
    cell->setPosition(this->_offsetFromIndex(index));
    cell->setIdx(index);
}

void CCTableView::_updateCellPositions() {
    int cellsCount = _dataSource->numberOfCellsInTableView(this);
    _vCellsPositions.resize(cellsCount + 1, 0.0);

    if (cellsCount > 0)
    {
        float currentPos = 0;
        CCSize cellSize;
        for (int i=0; i < cellsCount; i++)
        {
            _vCellsPositions[i] = currentPos;
            cellSize = _dataSource->tableCellSizeForIndex(this, i);
            switch (this->getDirection())
            {
                case kCCScrollViewDirectionHorizontal:
                    currentPos += cellSize.width;
                    break;
                default:
                    currentPos += cellSize.height;
                    break;
            }
        }
        _vCellsPositions[cellsCount] = currentPos;//1 extra value allows us to get right/bottom of the last cell
    }

}

void CCTableView::scrollViewDidScroll(CCScrollView* view)
{
    unsigned int uCountOfItems = _dataSource->numberOfCellsInTableView(this);
    if (0 == uCountOfItems)
    {
        return;
    }

    if(_tableViewDelegate != NULL) {
        _tableViewDelegate->scrollViewDidScroll(this);
    }

    unsigned int startIdx = 0, endIdx = 0, idx = 0, maxIdx = 0;
    CCPoint offset = ccpMult(this->getContentOffset(), -1);
    maxIdx = MAX(uCountOfItems-1, 0);

    if (_vordering == kCCTableViewFillTopDown)
    {
        offset.y = offset.y + _viewSize.height/this->getContainer()->getScaleY();
    }
    startIdx = this->_indexFromOffset(offset);
	if (startIdx == CC_INVALID_INDEX)
	{
		startIdx = uCountOfItems - 1;
	}

    if (_vordering == kCCTableViewFillTopDown)
    {
        offset.y -= _viewSize.height/this->getContainer()->getScaleY();
    }
    else
    {
        offset.y += _viewSize.height/this->getContainer()->getScaleY();
    }
    offset.x += _viewSize.width/this->getContainer()->getScaleX();

    endIdx   = this->_indexFromOffset(offset);
    if (endIdx == CC_INVALID_INDEX)
	{
		endIdx = uCountOfItems - 1;
	}

#if 0 // For Testing.
    CCObject* pObj;
    int i = 0;
    CCARRAY_FOREACH(_cellsUsed, pObj)
    {
        CCTableViewCell* pCell = (CCTableViewCell*)pObj;
        CCLog("cells Used index %d, value = %d", i, pCell->getIdx());
        i++;
    }
    CCLog("---------------------------------------");
    i = 0;
    CCARRAY_FOREACH(_cellsFreed, pObj)
    {
        CCTableViewCell* pCell = (CCTableViewCell*)pObj;
        CCLog("cells freed index %d, value = %d", i, pCell->getIdx());
        i++;
    }
    CCLog("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
#endif

    if (_cellsUsed->count() > 0)
    {
        CCTableViewCell* cell = (CCTableViewCell*)_cellsUsed->objectAtIndex(0);

        idx = cell->getIdx();
        while(idx <startIdx)
        {
            this->_moveCellOutOfSight(cell);
            if (_cellsUsed->count() > 0)
            {
                cell = (CCTableViewCell*)_cellsUsed->objectAtIndex(0);
                idx = cell->getIdx();
            }
            else
            {
                break;
            }
        }
    }
    if (_cellsUsed->count() > 0)
    {
        CCTableViewCell *cell = (CCTableViewCell*)_cellsUsed->lastObject();
        idx = cell->getIdx();

        while(idx <= maxIdx && idx > endIdx)
        {
            this->_moveCellOutOfSight(cell);
            if (_cellsUsed->count() > 0)
            {
                cell = (CCTableViewCell*)_cellsUsed->lastObject();
                idx = cell->getIdx();

            }
            else
            {
                break;
            }
        }
    }

    for (unsigned int i=startIdx; i <= endIdx; i++)
    {
        //if ([_indices containsIndex:i])
        if (_indices->find(i) != _indices->end())
        {
            continue;
        }
        this->updateCellAtIndex(i);
    }
}

void CCTableView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!this->isVisible()) {
        return;
    }

    if (_touchedCell){
		CCRect bb = this->boundingBox();
		bb.origin = _parent->convertToWorldSpace(bb.origin);

		if (bb.containsPoint(pTouch->getLocation()) && _tableViewDelegate != NULL)
        {
            _tableViewDelegate->tableCellUnhighlight(this, _touchedCell);
            _tableViewDelegate->tableCellTouched(this, _touchedCell);
        }

        _touchedCell = NULL;
    }

    CCScrollView::ccTouchEnded(pTouch, pEvent);
}

bool CCTableView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!this->isVisible()) {
        return false;
    }

    bool touchResult = CCScrollView::ccTouchBegan(pTouch, pEvent);

    if(_touches->count() == 1) {
        unsigned int        index;
        CCPoint           point;

        point = this->getContainer()->convertTouchToNodeSpace(pTouch);

        index = this->_indexFromOffset(point);
		if (index == CC_INVALID_INDEX)
		{
			_touchedCell = NULL;
		}
        else
		{
			_touchedCell  = this->cellAtIndex(index);
		}

        if (_touchedCell && _tableViewDelegate != NULL) {
            _tableViewDelegate->tableCellHighlight(this, _touchedCell);
        }
    }
    else if(_touchedCell) {
        if(_tableViewDelegate != NULL) {
            _tableViewDelegate->tableCellUnhighlight(this, _touchedCell);
        }

        _touchedCell = NULL;
    }

    return touchResult;
}

void CCTableView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCScrollView::ccTouchMoved(pTouch, pEvent);

    if (_touchedCell && isTouchMoved()) {
        if(_tableViewDelegate != NULL) {
            _tableViewDelegate->tableCellUnhighlight(this, _touchedCell);
        }

        _touchedCell = NULL;
    }
}

void CCTableView::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    CCScrollView::ccTouchCancelled(pTouch, pEvent);

    if (_touchedCell) {
        if(_tableViewDelegate != NULL) {
            _tableViewDelegate->tableCellUnhighlight(this, _touchedCell);
        }

        _touchedCell = NULL;
    }
}

NS_CC_EXT_END
