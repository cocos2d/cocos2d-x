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
#include "CCSorting.h"
#include "layers_scenes_transitions_nodes/CCLayer.h"

NS_CC_EXT_BEGIN

TableView* TableView::create(TableViewDataSource* dataSource, Size size)
{
    return TableView::create(dataSource, size, NULL);
}

TableView* TableView::create(TableViewDataSource* dataSource, Size size, Node *container)
{
    TableView *table = new TableView();
    table->initWithViewSize(size, container);
    table->autorelease();
    table->setDataSource(dataSource);
    table->_updateCellPositions();
    table->_updateContentSize();

    return table;
}

bool TableView::initWithViewSize(Size size, Node* container/* = NULL*/)
{
    if (ScrollView::initWithViewSize(size,container))
    {
        _cellsUsed      = new ArrayForObjectSorting();
        _cellsFreed     = new ArrayForObjectSorting();
        _indices        = new std::set<unsigned int>();
        _vordering      = VerticalFillOrder::BOTTOM_UP;
        this->setDirection(Direction::VERTICAL);

        ScrollView::setDelegate(this);
        return true;
    }
    return false;
}

TableView::TableView()
: _touchedCell(nullptr)
, _indices(nullptr)
, _cellsUsed(nullptr)
, _cellsFreed(nullptr)
, _dataSource(nullptr)
, _tableViewDelegate(nullptr)
, _oldDirection(Direction::NONE)
{

}

TableView::~TableView()
{
    CC_SAFE_DELETE(_indices);
    CC_SAFE_RELEASE(_cellsUsed);
    CC_SAFE_RELEASE(_cellsFreed);
}

void TableView::setVerticalFillOrder(VerticalFillOrder fillOrder)
{
    if (_vordering != fillOrder) {
        _vordering = fillOrder;
        if (_cellsUsed->count() > 0) {
            this->reloadData();
        }
    }
}

TableView::VerticalFillOrder TableView::getVerticalFillOrder()
{
    return _vordering;
}

void TableView::reloadData()
{
    _oldDirection = Direction::NONE;
    Object* pObj = NULL;
    CCARRAY_FOREACH(_cellsUsed, pObj)
    {
        TableViewCell* cell = static_cast<TableViewCell*>(pObj);

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
    _cellsUsed = new ArrayForObjectSorting();

    this->_updateCellPositions();
    this->_updateContentSize();
    if (_dataSource->numberOfCellsInTableView(this) > 0)
    {
        this->scrollViewDidScroll(this);
    }
}

TableViewCell *TableView::cellAtIndex(unsigned int idx)
{
    TableViewCell *found = NULL;

    if (_indices->find(idx) != _indices->end())
    {
        found = (TableViewCell *)_cellsUsed->objectWithObjectID(idx);
    }

    return found;
}

void TableView::updateCellAtIndex(unsigned int idx)
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

    TableViewCell* cell = this->cellAtIndex(idx);
    if (cell)
    {
        this->_moveCellOutOfSight(cell);
    }
    cell = _dataSource->tableCellAtIndex(this, idx);
    this->_setIndexForCell(idx, cell);
    this->_addCellIfNecessary(cell);
}

void TableView::insertCellAtIndex(unsigned  int idx)
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

    TableViewCell* cell = NULL;
    int newIdx = 0;

    cell = (TableViewCell*)_cellsUsed->objectWithObjectID(idx);
    if (cell)
    {
        newIdx = _cellsUsed->indexOfSortedObject(cell);
        for (unsigned int i=newIdx; i<_cellsUsed->count(); i++)
        {
            cell = (TableViewCell*)_cellsUsed->objectAtIndex(i);
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

void TableView::removeCellAtIndex(unsigned int idx)
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

    TableViewCell* cell = this->cellAtIndex(idx);
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
        cell = (TableViewCell*)_cellsUsed->objectAtIndex(i);
        this->_setIndexForCell(cell->getIdx()-1, cell);
    }
}

TableViewCell *TableView::dequeueCell()
{
    TableViewCell *cell;

    if (_cellsFreed->count() == 0) {
        cell = NULL;
    } else {
        cell = (TableViewCell*)_cellsFreed->objectAtIndex(0);
        cell->retain();
        _cellsFreed->removeObjectAtIndex(0);
        cell->autorelease();
    }
    return cell;
}

void TableView::_addCellIfNecessary(TableViewCell * cell)
{
    if (cell->getParent() != this->getContainer())
    {
        this->getContainer()->addChild(cell);
    }
    _cellsUsed->insertSortedObject(cell);
    _indices->insert(cell->getIdx());
    // [_indices addIndex:cell.idx];
}

void TableView::_updateContentSize()
{
    Size size = Size::ZERO;
    unsigned int cellsCount = _dataSource->numberOfCellsInTableView(this);

    if (cellsCount > 0)
    {
        float maxPosition = _vCellsPositions[cellsCount];

        switch (this->getDirection())
        {
            case Direction::HORIZONTAL:
                size = Size(maxPosition, _viewSize.height);
                break;
            default:
                size = Size(_viewSize.width, maxPosition);
                break;
        }
    }

    this->setContentSize(size);

	if (_oldDirection != _direction)
	{
		if (_direction == Direction::HORIZONTAL)
		{
			this->setContentOffset(Point(0,0));
		}
		else
		{
			this->setContentOffset(Point(0,this->minContainerOffset().y));
		}
		_oldDirection = _direction;
	}

}

Point TableView::_offsetFromIndex(unsigned int index)
{
    Point offset = this->__offsetFromIndex(index);

    const Size cellSize = _dataSource->tableCellSizeForIndex(this, index);
    if (_vordering == VerticalFillOrder::TOP_DOWN)
    {
        offset.y = this->getContainer()->getContentSize().height - offset.y - cellSize.height;
    }
    return offset;
}

Point TableView::__offsetFromIndex(unsigned int index)
{
    Point offset;
    Size  cellSize;

    switch (this->getDirection())
    {
        case Direction::HORIZONTAL:
            offset = Point(_vCellsPositions[index], 0.0f);
            break;
        default:
            offset = Point(0.0f, _vCellsPositions[index]);
            break;
    }

    return offset;
}

unsigned int TableView::_indexFromOffset(Point offset)
{
    int index = 0;
    const int maxIdx = _dataSource->numberOfCellsInTableView(this)-1;

    if (_vordering == VerticalFillOrder::TOP_DOWN)
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

int TableView::__indexFromOffset(Point offset)
{
    int low = 0;
    int high = _dataSource->numberOfCellsInTableView(this) - 1;
    float search;
    switch (this->getDirection())
    {
        case Direction::HORIZONTAL:
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

void TableView::_moveCellOutOfSight(TableViewCell *cell)
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

void TableView::_setIndexForCell(unsigned int index, TableViewCell *cell)
{
    cell->setAnchorPoint(Point(0.0f, 0.0f));
    cell->setPosition(this->_offsetFromIndex(index));
    cell->setIdx(index);
}

void TableView::_updateCellPositions() {
    int cellsCount = _dataSource->numberOfCellsInTableView(this);
    _vCellsPositions.resize(cellsCount + 1, 0.0);

    if (cellsCount > 0)
    {
        float currentPos = 0;
        Size cellSize;
        for (int i=0; i < cellsCount; i++)
        {
            _vCellsPositions[i] = currentPos;
            cellSize = _dataSource->tableCellSizeForIndex(this, i);
            switch (this->getDirection())
            {
                case Direction::HORIZONTAL:
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

void TableView::scrollViewDidScroll(ScrollView* view)
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
    Point offset = this->getContentOffset() * -1;
    maxIdx = MAX(uCountOfItems-1, 0);

    if (_vordering == VerticalFillOrder::TOP_DOWN)
    {
        offset.y = offset.y + _viewSize.height/this->getContainer()->getScaleY();
    }
    startIdx = this->_indexFromOffset(offset);
	if (startIdx == CC_INVALID_INDEX)
	{
		startIdx = uCountOfItems - 1;
	}

    if (_vordering == VerticalFillOrder::TOP_DOWN)
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
    Object* pObj;
    int i = 0;
    CCARRAY_FOREACH(_cellsUsed, pObj)
    {
        TableViewCell* pCell = static_cast<TableViewCell*>(pObj);
        log("cells Used index %d, value = %d", i, pCell->getIdx());
        i++;
    }
    log("---------------------------------------");
    i = 0;
    CCARRAY_FOREACH(_cellsFreed, pObj)
    {
        TableViewCell* pCell = static_cast<TableViewCell*>(pObj);
        log("cells freed index %d, value = %d", i, pCell->getIdx());
        i++;
    }
    log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
#endif

    if (_cellsUsed->count() > 0)
    {
        TableViewCell* cell = (TableViewCell*)_cellsUsed->objectAtIndex(0);

        idx = cell->getIdx();
        while(idx <startIdx)
        {
            this->_moveCellOutOfSight(cell);
            if (_cellsUsed->count() > 0)
            {
                cell = (TableViewCell*)_cellsUsed->objectAtIndex(0);
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
        TableViewCell *cell = (TableViewCell*)_cellsUsed->lastObject();
        idx = cell->getIdx();

        while(idx <= maxIdx && idx > endIdx)
        {
            this->_moveCellOutOfSight(cell);
            if (_cellsUsed->count() > 0)
            {
                cell = (TableViewCell*)_cellsUsed->lastObject();
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

void TableView::ccTouchEnded(Touch *pTouch, Event *pEvent)
{
    if (!this->isVisible()) {
        return;
    }

    if (_touchedCell){
		Rect bb = this->getBoundingBox();
		bb.origin = _parent->convertToWorldSpace(bb.origin);

		if (bb.containsPoint(pTouch->getLocation()) && _tableViewDelegate != NULL)
        {
            _tableViewDelegate->tableCellUnhighlight(this, _touchedCell);
            _tableViewDelegate->tableCellTouched(this, _touchedCell);
        }

        _touchedCell = NULL;
    }

    ScrollView::ccTouchEnded(pTouch, pEvent);
}

bool TableView::ccTouchBegan(Touch *pTouch, Event *pEvent)
{
    if (!this->isVisible()) {
        return false;
    }

    bool touchResult = ScrollView::ccTouchBegan(pTouch, pEvent);

    if(_touches->count() == 1) {
        unsigned int        index;
        Point           point;

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

void TableView::ccTouchMoved(Touch *pTouch, Event *pEvent)
{
    ScrollView::ccTouchMoved(pTouch, pEvent);

    if (_touchedCell && isTouchMoved()) {
        if(_tableViewDelegate != NULL) {
            _tableViewDelegate->tableCellUnhighlight(this, _touchedCell);
        }

        _touchedCell = NULL;
    }
}

void TableView::ccTouchCancelled(Touch *pTouch, Event *pEvent)
{
    ScrollView::ccTouchCancelled(pTouch, pEvent);

    if (_touchedCell) {
        if(_tableViewDelegate != NULL) {
            _tableViewDelegate->tableCellUnhighlight(this, _touchedCell);
        }

        _touchedCell = NULL;
    }
}

NS_CC_EXT_END
