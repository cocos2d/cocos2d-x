//
//  SWTableView.m
//  SWGameLib
//
//  Copyright (c) 2012  cocos2d-x.org
//  Copyright (c) 2010 Sangwoo Im
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//  
//
//  Created by Sangwoo Im on 6/3/10.
//  Copyright 2010 Sangwoo Im. All rights reserved.
//
#include "cocos2d.h"
#include "CCTableView.h"
#include "CCTableViewCell.h"
#include "menu_nodes/CCMenu.h"
#include "support/CCPointExtension.h"
#include "CCSorting.h"
#include "layers_scenes_transitions_nodes/CCLayer.h"

NS_CC_EXT_BEGIN

CCTableView* CCTableView::viewWithDataSource(CCTableViewDataSource* dataSource, CCSize size)
{
    return CCTableView::viewWithDataSource(dataSource, size, NULL);
}

CCTableView* CCTableView::viewWithDataSource(CCTableViewDataSource* dataSource, CCSize size, CCNode *container)
{
    CCTableView *table = new CCTableView();
    table->initWithViewSize(size, container);
    table->autorelease();
    table->setDataSource(dataSource);
    table->_updateContentSize();

    return table;
}

bool CCTableView::initWithViewSize(CCSize size, CCNode* container/* = NULL*/)
{
    if (CCScrollView::initWithViewSize(size,container))
    {
        cellsUsed_      = new CCArrayForObjectSorting();
        cellsFreed_     = new CCArrayForObjectSorting();
        indices_        = new std::set<unsigned int>();
        tDelegate_      = NULL;
        vordering_      = CCTableViewFillBottomUp;
        this->setDirection(CCScrollViewDirectionVertical);
        
        CCScrollView::setDelegate(this);
        return true;
    }
    return false;
}

CCTableView::CCTableView()
: indices_(NULL)
, cellsUsed_(NULL)
, cellsFreed_(NULL)
, dataSource_(NULL)
, tDelegate_(NULL)
, m_eOldDirection(CCScrollViewDirectionNone)
{

}

CCTableView::~CCTableView()
{
    CC_SAFE_DELETE(indices_);
    CC_SAFE_RELEASE(cellsUsed_);
    CC_SAFE_RELEASE(cellsFreed_);
}

void CCTableView::setVerticalFillOrder(CCTableViewVerticalFillOrder fillOrder)
{
    if (vordering_ != fillOrder) {
        vordering_ = fillOrder;
        if (cellsUsed_->count() > 0) {
            this->reloadData();
        }
    }
}

CCTableViewVerticalFillOrder CCTableView::getVerticalFillOrder()
{
    return vordering_;
}

void CCTableView::reloadData()
{
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(cellsUsed_, pObj)
    {
        CCTableViewCell* cell = (CCTableViewCell*)pObj;
        cellsFreed_->addObject(cell);
        cell->reset();
        if (cell->getParent() == this->getContainer())
        {
            this->getContainer()->removeChild(cell, true);
        }
    }

    indices_->clear();
    cellsUsed_->release();
    cellsUsed_ = new CCArrayForObjectSorting();
    
    this->_updateContentSize();
    if (dataSource_->numberOfCellsInTableView(this) > 0)
    {
        this->scrollViewDidScroll(this);
    }
}

CCTableViewCell *CCTableView::cellAtIndex(unsigned int idx)
{
    return this->_cellWithIndex(idx);
}

void CCTableView::updateCellAtIndex(unsigned int idx)
{
    if (idx == CC_INVALID_INDEX || idx > dataSource_->numberOfCellsInTableView(this)-1)
    {
        return;
    }
    
    CCTableViewCell *cell;
    
    cell = this->_cellWithIndex(idx);
    if (cell) {
        this->_moveCellOutOfSight(cell);
    } 
    cell = dataSource_->tableCellAtIndex(this, idx);
    this->_setIndexForCell(idx, cell);
    this->_addCellIfNecessary(cell);
}

void CCTableView::insertCellAtIndex(unsigned  int idx)
{
    if (idx == CC_INVALID_INDEX || idx > dataSource_->numberOfCellsInTableView(this)-1) {
        return;
    }
    CCTableViewCell *cell;
    int newIdx;
    
    cell = (CCTableViewCell*)cellsUsed_->objectWithObjectID(idx);
    if (cell) 
    {
        newIdx = cellsUsed_->indexOfSortedObject(cell);
        for (unsigned int i=newIdx; i<cellsUsed_->count(); i++)
        {
            cell = (CCTableViewCell*)cellsUsed_->objectAtIndex(i);
            this->_setIndexForCell(cell->getIdx()+1, cell);
        }
    }
    
 //   [indices_ shiftIndexesStartingAtIndex:idx by:1];
    
    //insert a new cell
    cell = dataSource_->tableCellAtIndex(this, idx);
    this->_setIndexForCell(idx, cell);
    this->_addCellIfNecessary(cell);
    
    this->_updateContentSize();
}

void CCTableView::removeCellAtIndex(unsigned int idx)
{
    if (idx == CC_INVALID_INDEX || idx > dataSource_->numberOfCellsInTableView(this)-1) {
        return;
    }
    
    CCTableViewCell   *cell;
    unsigned int newIdx;
    
    cell = this->_cellWithIndex(idx);
    if (!cell) {
        return;
    }
    
    newIdx = cellsUsed_->indexOfSortedObject(cell);
    
    //remove first
    this->_moveCellOutOfSight(cell);
    
    indices_->erase(idx);
//    [indices_ shiftIndexesStartingAtIndex:idx+1 by:-1];
    for (unsigned int i=cellsUsed_->count()-1; i > newIdx; i--) {
        cell = (CCTableViewCell*)cellsUsed_->objectAtIndex(i);
        this->_setIndexForCell(cell->getIdx()-1, cell);
    }
}

CCTableViewCell *CCTableView::dequeueCell()
{
    CCTableViewCell *cell;
    
    if (cellsFreed_->count() == 0) {
        cell = NULL;
    } else {
        cell = (CCTableViewCell*)cellsFreed_->objectAtIndex(0);
        cell->retain();
        cellsFreed_->removeObjectAtIndex(0);
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
    cellsUsed_->insertSortedObject(cell);
    indices_->insert(cell->getIdx());
    // [indices_ addIndex:cell.idx];
}

void CCTableView::_updateContentSize()
{
    CCSize     size, cellSize;
    unsigned int cellCount;

    cellSize  = dataSource_->cellSizeForTable(this);
    cellCount = dataSource_->numberOfCellsInTableView(this);
    
    switch (this->getDirection())
    {
        case CCScrollViewDirectionHorizontal:
            size = CCSizeMake(cellCount * cellSize.width, cellSize.height);
            break;
        default:
            size = CCSizeMake(cellSize.width, cellCount * cellSize.height);
            break;
    }
    this->setContentSize(size);

	if (m_eOldDirection != m_eDirection)
	{
		if (m_eDirection == CCScrollViewDirectionHorizontal)
		{
			this->setContentOffset(ccp(0,0));
		}
		else
		{
			this->setContentOffset(ccp(0,this->minContainerOffset().y));
		}
		m_eOldDirection = m_eDirection;
	}

}

CCPoint CCTableView::_offsetFromIndex(unsigned int index)
{
    CCPoint offset = this->__offsetFromIndex(index);
    
    const CCSize cellSize = dataSource_->cellSizeForTable(this);
    if (vordering_ == CCTableViewFillTopDown) {
        offset.y = this->getContainer()->getContentSize().height - offset.y - cellSize.height;
    }
    return offset;
}

CCPoint CCTableView::__offsetFromIndex(unsigned int index)
{
    CCPoint offset;
    CCSize  cellSize;
    
    cellSize = dataSource_->cellSizeForTable(this);
    switch (this->getDirection()) {
        case CCScrollViewDirectionHorizontal:
            offset = ccp(cellSize.width * index, 0.0f);
            break;
        default:
            offset = ccp(0.0f, cellSize.height * index);
            break;
    }
    
    return offset;
}

unsigned int CCTableView::_indexFromOffset(CCPoint offset)
{
    int index = 0;
    const int maxIdx = dataSource_->numberOfCellsInTableView(this)-1;

    const CCSize cellSize = dataSource_->cellSizeForTable(this);
    if (vordering_ == CCTableViewFillTopDown) {
        offset.y = this->getContainer()->getContentSize().height - offset.y - cellSize.height;
    }
    index = MAX(0, this->__indexFromOffset(offset));
    index = MIN(index, maxIdx);

    return index;
}

int CCTableView::__indexFromOffset(CCPoint offset)
{
    int  index = 0;
    CCSize     cellSize;
    
    cellSize = dataSource_->cellSizeForTable(this);
    
    switch (this->getDirection()) {
        case CCScrollViewDirectionHorizontal:
            index = offset.x/cellSize.width;
            break;
        default:
            index = offset.y/cellSize.height;
            break;
    }
    
    return index;
}

CCTableViewCell* CCTableView::_cellWithIndex(unsigned int cellIndex)
{
    CCTableViewCell *found;
    
    found = NULL;
    
//     if ([indices_ containsIndex:cellIndex])
    if (indices_->find(cellIndex) != indices_->end())
    {
        found = (CCTableViewCell *)cellsUsed_->objectWithObjectID(cellIndex);
    }
    
    return found;
}

void CCTableView::_moveCellOutOfSight(CCTableViewCell *cell)
{
    cellsFreed_->addObject(cell);
    cellsUsed_->removeSortedObject(cell);
    indices_->erase(cell->getIdx());
    // [indices_ removeIndex:cell.idx];
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

void CCTableView::scrollViewDidScroll(CCScrollView* view)
{
	CCLOG("container pos x = %f, y = %f", getContainer()->getPosition().x, getContainer()->getPosition().y);
    unsigned int startIdx = 0, endIdx = 0, idx = 0, maxIdx = 0;
    CCPoint offset;

    offset   = ccpMult(this->getContentOffset(), -1);
    maxIdx   = MAX(dataSource_->numberOfCellsInTableView(this)-1, 0);
    
    const CCSize cellSize = dataSource_->cellSizeForTable(this);
    
    if (vordering_ == CCTableViewFillTopDown) {
        offset.y = offset.y + m_tViewSize.height/this->getContainer()->getScaleY() - cellSize.height;
    }
    startIdx = this->_indexFromOffset(offset);
    
    if (vordering_ == CCTableViewFillTopDown)
    {
        offset.y -= m_tViewSize.height/this->getContainer()->getScaleY();
    }
    else 
    {
        offset.y += m_tViewSize.height/this->getContainer()->getScaleY();
    }
    offset.x += m_tViewSize.width/this->getContainer()->getScaleX();
    
    endIdx   = this->_indexFromOffset(offset);   
    
    CCObject* pObj;
    int i = 0;
    CCARRAY_FOREACH(cellsUsed_, pObj)
    {
        CCTableViewCell* pCell = (CCTableViewCell*)pObj;
        CCLog("cells Used index %d, value = %d", i, pCell->getIdx());
        i++;
    }
    CCLog("---------------------------------------");
    i = 0;
    CCARRAY_FOREACH(cellsFreed_, pObj)
    {
        CCTableViewCell* pCell = (CCTableViewCell*)pObj;
        CCLog("cells freed index %d, value = %d", i, pCell->getIdx());
        i++;
    }
    CCLog("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    if (cellsUsed_->count() > 0)
    {
        CCTableViewCell* cell = (CCTableViewCell*)cellsUsed_->objectAtIndex(0);

        idx = cell->getIdx();
        while(idx <startIdx)
        {
            this->_moveCellOutOfSight(cell);
            if (cellsUsed_->count() > 0) {
                cell = (CCTableViewCell*)cellsUsed_->objectAtIndex(0);
                idx = cell->getIdx();    
            } else {
                break;
            }
            CCLog("idx 0 = %d", idx);
        }
    }
    if (cellsUsed_->count() > 0)
    {
        CCTableViewCell *cell = (CCTableViewCell*)cellsUsed_->lastObject();
        idx = cell->getIdx();

        while(idx <= maxIdx && idx > endIdx)
        {
            this->_moveCellOutOfSight(cell);
            if (cellsUsed_->count() > 0)
            {
                cell = (CCTableViewCell*)cellsUsed_->lastObject();
                idx = cell->getIdx();
                
            } else {
                break;
            }
            CCLog("idx 1 = %d, maxIdx = %d, endIdx = %d", idx, maxIdx, endIdx);
        }
    }
    
    for (unsigned int i=startIdx; i <= endIdx; i++)
    {
        //if ([indices_ containsIndex:i])
        if (indices_->find(i) != indices_->end())
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
    if (m_pTouches->count() == 1 && !this->isTouchMoved()) {
        unsigned int        index;
        CCTableViewCell   *cell;
        CCPoint           point;
        
        point = this->getContainer()->convertTouchToNodeSpace(pTouch);
        if (vordering_ == CCTableViewFillTopDown) {
            CCSize cellSize = dataSource_->cellSizeForTable(this);
            point.y -= cellSize.height;
        }
        index = this->_indexFromOffset(point);
        cell  = this->_cellWithIndex(index);
        
        if (cell) {
            tDelegate_->table_cellTouched(this, cell);   
        }
    }
    CCScrollView::ccTouchEnded(pTouch, pEvent);
}

NS_CC_EXT_END
