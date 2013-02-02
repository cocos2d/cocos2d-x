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
    table->_updateContentSize();

    return table;
}

bool CCTableView::initWithViewSize(CCSize size, CCNode* container/* = NULL*/)
{
    if (CCScrollView::initWithViewSize(size,container))
    {
        m_pCellsUsed      = new CCArrayForObjectSorting();
        m_pCellsFreed     = new CCArrayForObjectSorting();
        m_pIndices        = new std::set<unsigned int>();
        m_eVordering      = kCCTableViewFillBottomUp;
        this->setDirection(kCCScrollViewDirectionVertical);
        
        CCScrollView::setDelegate(this);
        return true;
    }
    return false;
}

CCTableView::CCTableView()
: m_pIndices(NULL)
, m_pCellsUsed(NULL)
, m_pCellsFreed(NULL)
, m_pDataSource(NULL)
, m_pTableViewDelegate(NULL)
, m_pTouchedCell(NULL)
, m_eOldDirection(kCCScrollViewDirectionNone)
{

}

CCTableView::~CCTableView()
{
    CC_SAFE_DELETE(m_pIndices);
    CC_SAFE_RELEASE(m_pCellsUsed);
    CC_SAFE_RELEASE(m_pCellsFreed);
}

void CCTableView::setVerticalFillOrder(CCTableViewVerticalFillOrder fillOrder)
{
    if (m_eVordering != fillOrder) {
        m_eVordering = fillOrder;
        if (m_pCellsUsed->count() > 0) {
            this->reloadData();
        }
    }
}

CCTableViewVerticalFillOrder CCTableView::getVerticalFillOrder()
{
    return m_eVordering;
}

void CCTableView::reloadData()
{
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_pCellsUsed, pObj)
    {
        CCTableViewCell* cell = (CCTableViewCell*)pObj;
        
        if(m_pTableViewDelegate != NULL) {
            m_pTableViewDelegate->tableCellWillRecycle(this, cell);
        }
        
        m_pCellsFreed->addObject(cell);
        cell->reset();
        if (cell->getParent() == this->getContainer())
        {
            this->getContainer()->removeChild(cell, true);
        }
    }

    m_pIndices->clear();
    m_pCellsUsed->release();
    m_pCellsUsed = new CCArrayForObjectSorting();
    
    this->_updateContentSize();
    if (m_pDataSource->numberOfCellsInTableView(this) > 0)
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
    if (idx == CC_INVALID_INDEX)
    {
        return;
    }
    unsigned int uCountOfItems = m_pDataSource->numberOfCellsInTableView(this);
    if (0 == uCountOfItems || idx > uCountOfItems-1)
    {
        return;
    }

    CCTableViewCell* cell = this->_cellWithIndex(idx);
    if (cell)
    {
        this->_moveCellOutOfSight(cell);
    } 
    cell = m_pDataSource->tableCellAtIndex(this, idx);
    this->_setIndexForCell(idx, cell);
    this->_addCellIfNecessary(cell);
}

void CCTableView::insertCellAtIndex(unsigned  int idx)
{
    if (idx == CC_INVALID_INDEX)
    {
        return;
    }

    unsigned int uCountOfItems = m_pDataSource->numberOfCellsInTableView(this);
    if (0 == uCountOfItems || idx > uCountOfItems-1)
    {
        return;
    }

    CCTableViewCell* cell = NULL;
    int newIdx = 0;
    
    cell = (CCTableViewCell*)m_pCellsUsed->objectWithObjectID(idx);
    if (cell) 
    {
        newIdx = m_pCellsUsed->indexOfSortedObject(cell);
        for (unsigned int i=newIdx; i<m_pCellsUsed->count(); i++)
        {
            cell = (CCTableViewCell*)m_pCellsUsed->objectAtIndex(i);
            this->_setIndexForCell(cell->getIdx()+1, cell);
        }
    }
    
 //   [m_pIndices shiftIndexesStartingAtIndex:idx by:1];
    
    //insert a new cell
    cell = m_pDataSource->tableCellAtIndex(this, idx);
    this->_setIndexForCell(idx, cell);
    this->_addCellIfNecessary(cell);
    
    this->_updateContentSize();
}

void CCTableView::removeCellAtIndex(unsigned int idx)
{
    if (idx == CC_INVALID_INDEX)
    {
        return;
    }
    
    unsigned int uCountOfItems = m_pDataSource->numberOfCellsInTableView(this);
    if (0 == uCountOfItems || idx > uCountOfItems-1)
    {
        return;
    }

    CCTableViewCell* cell = NULL;
    unsigned int newIdx = 0;
    
    cell = this->_cellWithIndex(idx);
    if (!cell) {
        return;
    }
    
    newIdx = m_pCellsUsed->indexOfSortedObject(cell);
    
    //remove first
    this->_moveCellOutOfSight(cell);
    
    m_pIndices->erase(idx);
//    [m_pIndices shiftIndexesStartingAtIndex:idx+1 by:-1];
    for (unsigned int i=m_pCellsUsed->count()-1; i > newIdx; i--) {
        cell = (CCTableViewCell*)m_pCellsUsed->objectAtIndex(i);
        this->_setIndexForCell(cell->getIdx()-1, cell);
    }
}

CCTableViewCell *CCTableView::dequeueCell()
{
    CCTableViewCell *cell;
    
    if (m_pCellsFreed->count() == 0) {
        cell = NULL;
    } else {
        cell = (CCTableViewCell*)m_pCellsFreed->objectAtIndex(0);
        cell->retain();
        m_pCellsFreed->removeObjectAtIndex(0);
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
    m_pCellsUsed->insertSortedObject(cell);
    m_pIndices->insert(cell->getIdx());
    // [m_pIndices addIndex:cell.idx];
}

void CCTableView::_updateContentSize()
{
    CCSize     size, cellSize;
    unsigned int cellCount;

    cellSize  = m_pDataSource->cellSizeForTable(this);
    cellCount = m_pDataSource->numberOfCellsInTableView(this);
    
    switch (this->getDirection())
    {
        case kCCScrollViewDirectionHorizontal:
            size = CCSizeMake(cellCount * cellSize.width, cellSize.height);
            break;
        default:
            size = CCSizeMake(cellSize.width, cellCount * cellSize.height);
            break;
    }
    this->setContentSize(size);

	if (m_eOldDirection != m_eDirection)
	{
		if (m_eDirection == kCCScrollViewDirectionHorizontal)
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
    
    const CCSize cellSize = m_pDataSource->cellSizeForTable(this);
    if (m_eVordering == kCCTableViewFillTopDown) {
        offset.y = this->getContainer()->getContentSize().height - offset.y - cellSize.height;
    }
    return offset;
}

CCPoint CCTableView::__offsetFromIndex(unsigned int index)
{
    CCPoint offset;
    CCSize  cellSize;
    
    cellSize = m_pDataSource->cellSizeForTable(this);
    switch (this->getDirection()) {
        case kCCScrollViewDirectionHorizontal:
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
    const int maxIdx = m_pDataSource->numberOfCellsInTableView(this)-1;

    const CCSize cellSize = m_pDataSource->cellSizeForTable(this);
    if (m_eVordering == kCCTableViewFillTopDown) {
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
    
    cellSize = m_pDataSource->cellSizeForTable(this);
    
    switch (this->getDirection()) {
        case kCCScrollViewDirectionHorizontal:
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
    
//     if ([m_pIndices containsIndex:cellIndex])
    if (m_pIndices->find(cellIndex) != m_pIndices->end())
    {
        found = (CCTableViewCell *)m_pCellsUsed->objectWithObjectID(cellIndex);
    }
    
    return found;
}

void CCTableView::_moveCellOutOfSight(CCTableViewCell *cell)
{
    if(m_pTableViewDelegate != NULL) {
        m_pTableViewDelegate->tableCellWillRecycle(this, cell);
    }
    
    m_pCellsFreed->addObject(cell);
    m_pCellsUsed->removeSortedObject(cell);
    m_pIndices->erase(cell->getIdx());
    // [m_pIndices removeIndex:cell.idx];
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
    unsigned int uCountOfItems = m_pDataSource->numberOfCellsInTableView(this);
    if (0 == uCountOfItems)
    {
        return;
    }
    
    if(m_pTableViewDelegate != NULL) {
        m_pTableViewDelegate->scrollViewDidScroll(this);
    }
    
    unsigned int startIdx = 0, endIdx = 0, idx = 0, maxIdx = 0;
    CCPoint offset = ccpMult(this->getContentOffset(), -1);
    maxIdx = MAX(uCountOfItems-1, 0);
    const CCSize cellSize = m_pDataSource->cellSizeForTable(this);
    
    if (m_eVordering == kCCTableViewFillTopDown)
    {
        offset.y = offset.y + m_tViewSize.height/this->getContainer()->getScaleY() - cellSize.height;
    }
    startIdx = this->_indexFromOffset(offset);
    
    if (m_eVordering == kCCTableViewFillTopDown)
    {
        offset.y -= m_tViewSize.height/this->getContainer()->getScaleY();
    }
    else 
    {
        offset.y += m_tViewSize.height/this->getContainer()->getScaleY();
    }
    offset.x += m_tViewSize.width/this->getContainer()->getScaleX();
    
    endIdx   = this->_indexFromOffset(offset);   
    
#if 0 // For Testing.
    CCObject* pObj;
    int i = 0;
    CCARRAY_FOREACH(m_pCellsUsed, pObj)
    {
        CCTableViewCell* pCell = (CCTableViewCell*)pObj;
        CCLog("cells Used index %d, value = %d", i, pCell->getIdx());
        i++;
    }
    CCLog("---------------------------------------");
    i = 0;
    CCARRAY_FOREACH(m_pCellsFreed, pObj)
    {
        CCTableViewCell* pCell = (CCTableViewCell*)pObj;
        CCLog("cells freed index %d, value = %d", i, pCell->getIdx());
        i++;
    }
    CCLog("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
#endif
    
    if (m_pCellsUsed->count() > 0)
    {
        CCTableViewCell* cell = (CCTableViewCell*)m_pCellsUsed->objectAtIndex(0);

        idx = cell->getIdx();
        while(idx <startIdx)
        {
            this->_moveCellOutOfSight(cell);
            if (m_pCellsUsed->count() > 0)
            {
                cell = (CCTableViewCell*)m_pCellsUsed->objectAtIndex(0);
                idx = cell->getIdx();    
            }
            else
            {
                break;
            }
        }
    }
    if (m_pCellsUsed->count() > 0)
    {
        CCTableViewCell *cell = (CCTableViewCell*)m_pCellsUsed->lastObject();
        idx = cell->getIdx();

        while(idx <= maxIdx && idx > endIdx)
        {
            this->_moveCellOutOfSight(cell);
            if (m_pCellsUsed->count() > 0)
            {
                cell = (CCTableViewCell*)m_pCellsUsed->lastObject();
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
        //if ([m_pIndices containsIndex:i])
        if (m_pIndices->find(i) != m_pIndices->end())
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
    
    if (m_pTouchedCell){
        if(m_pTableViewDelegate != NULL) {
            m_pTableViewDelegate->tableCellUnhighlight(this, m_pTouchedCell);
            m_pTableViewDelegate->tableCellTouched(this, m_pTouchedCell);
        }
        
        m_pTouchedCell = NULL;
    }
    
    CCScrollView::ccTouchEnded(pTouch, pEvent);
}

bool CCTableView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!this->isVisible()) {
        return false;
    }
    
    bool touchResult = CCScrollView::ccTouchBegan(pTouch, pEvent);
    
    if(m_pTouches->count() == 1) {
        unsigned int        index;
        CCPoint           point;
        
        point = this->getContainer()->convertTouchToNodeSpace(pTouch);
        
        if (m_eVordering == kCCTableViewFillTopDown) {
            CCSize cellSize = m_pDataSource->cellSizeForTable(this);
            point.y -= cellSize.height;
        }
        
        index = this->_indexFromOffset(point);
        m_pTouchedCell  = this->_cellWithIndex(index);
        
        if (m_pTouchedCell && m_pTableViewDelegate != NULL) {
            m_pTableViewDelegate->tableCellHighlight(this, m_pTouchedCell);
        }
    }
    else if(m_pTouchedCell) {
        if(m_pTableViewDelegate != NULL) {
            m_pTableViewDelegate->tableCellUnhighlight(this, m_pTouchedCell);
        }
        
        m_pTouchedCell = NULL;
    }

    return touchResult;
}

void CCTableView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCScrollView::ccTouchMoved(pTouch, pEvent);

    if (m_pTouchedCell && isTouchMoved()) {
        if(m_pTableViewDelegate != NULL) {
            m_pTableViewDelegate->tableCellUnhighlight(this, m_pTouchedCell);
        }
        
        m_pTouchedCell = NULL;
    }
}

void CCTableView::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    CCScrollView::ccTouchCancelled(pTouch, pEvent);

    if (m_pTouchedCell) {
        if(m_pTableViewDelegate != NULL) {
            m_pTableViewDelegate->tableCellUnhighlight(this, m_pTouchedCell);
        }
        
        m_pTouchedCell = NULL;
    }
}

NS_CC_EXT_END
