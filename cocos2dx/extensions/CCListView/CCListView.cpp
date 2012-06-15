/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2012 NetGragon

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

#include "CCListView.h"
//#include "../cocos2dx_support/LuaEngineImpl.h"
#include "cocos2d.h"

using namespace std;

NS_CC_EXT_BEGIN

#define ND_LISTVIEW_ACTION_INTERVAL        0.6666f
/******************************************
**************Public Functions*************
*******************************************/
CCListView* CCListView::viewWithMode(CCListViewMode mode)
{
    return CCListView::create(mode);
}

CCListView* CCListView::create(CCListViewMode mode)
{
    CCListView *pRet = new CCListView();
    if (pRet && pRet->initWithMode(mode))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool CCListView::initWithMode(CCListViewMode mode)
{
    if (CCLayerColor::initWithColor(ccc4(255, 255, 255, 0), 0, 0))
    {
        setTouchEnabled(true);
        m_nMode = mode;
        m_layerPanel = CCLayer::create();
        this->addChild(m_layerPanel);
        return true;
    }
    return false;
}

CCListView::CCListView(void)
    :m_nMode(CCListViewModeVertical)
    ,m_nState(CCListViewStateWatting)
    ,m_nSlideDir(CCListViewSlideDirNone)
    ,m_layerPanel(NULL)
    ,m_nSeparatorStyle(CCListViewCellSeparatorStyleSingleLine)
    ,m_nSelectedRow(-1)
    ,m_nCurrentRow(-1)
    ,m_fActionDuration(ND_LISTVIEW_ACTION_INTERVAL)
    ,m_pListViewParent(NULL)
    ,m_bIsEnabled(true)
    ,m_pDelegate(NULL)
    ,m_nNumberOfRows(0)
    ,m_bIsOnTouch(false)
{
    m_drawedRows = CCRangeMake(0, 0);
    m_visibleRows = CCRangeMake(0, 0);
    m_bIsTouchEnabled = true;
}

CCListView::~CCListView(void) 
{
}

void CCListView::setDelegateName(const char* pszName)
{
    if (pszName)
    {
        this->m_strDeletegate = string(pszName) + ".";
    }
    else
    {
        this->m_strDeletegate.clear();
    }
}

void CCListView::selectCellAtRow(unsigned int nRow)
{
    CCListViewCell *cell = cellAtRow(nRow);
    if (cell)
    {
        cell->selected();
    }
}

void CCListView::unselectCellAtRow(unsigned int nRow)
{
    if (nRow == m_nSelectedRow)
    {
        m_nSelectedRow = -1;
    }
    CCListViewCell *cell = cellAtRow(nRow);
    if (cell)
    {
        cell->unselected();
    }
}

void CCListView::reload(void)
{
    m_layerPanel->removeAllChildrenWithCleanup(true);
    m_layerPanel->setPosition(CCPointZero);
    m_visibleRows = CCRangeMake(0, 0);
    m_drawedRows = CCRangeMake(0, 0);
    m_nNumberOfRows = triggerNumberOfCells();
    this->displayVisibleRows();
}

void CCListView::insertCellsAtRow(unsigned int nRow, unsigned int nCount)
{
    if (nRow >= m_nNumberOfRows)
    {
        if (m_nNumberOfRows > 0)
        {
            nRow = m_nNumberOfRows - 1;
        }
        else
        {
            nRow = 0;
        }
    }

    m_layerPanel->pauseSchedulerAndActions();
    if (m_nNumberOfRows == 0)
    {
        m_nNumberOfRows = this->triggerNumberOfCells();
        this->displayVisibleRows();
    }
    else
    {
        m_nNumberOfRows = this->triggerNumberOfCells();

        if (!this->isFullFill())
        {
            this->displayVisibleRows();
        }
    }
    m_layerPanel->resumeSchedulerAndActions();
}

void CCListView::deleteCellsAtRow(unsigned int nRow, unsigned int nCount)
{
    if (m_nNumberOfRows == 0)
    {
        return;
    }
    if (nRow >= m_nNumberOfRows)
    {
        if (m_nNumberOfRows > 0)
        {
            nRow = m_nNumberOfRows - 1;
        }
        else
        {
            nRow = 0;
        }
    }

    m_layerPanel->pauseSchedulerAndActions();


    m_nNumberOfRows = this->triggerNumberOfCells();

    for (unsigned int n = nRow;n < nRow + nCount; n++)
    {
        if (n >= m_drawedRows.location && n <= CCRange::CCMaxRange(m_drawedRows))
        {
            CCListViewCell *cell = this->cellAtRow(n);
            if (cell)
            {
                CCPoint pos = cell->getPosition();
                pos.y += cell->getContentSize().height;
                m_layerPanel->removeChild(cell, true);
                for (unsigned int i = n +1; i <= CCRange::CCMaxRange(m_drawedRows); i++)
                {
                    cell = this->cellAtRow(i);
                    if (cell)
                    {
                        int tag = cell->getTag();
                        cell->setTag(tag - 1);
                        if (CCListViewModeHorizontal == m_nMode)
                        {
                            cell->setPosition(pos);
                            pos.x += cell->getContentSize().width;
                        }
                        else if (CCListViewModeVertical == m_nMode)
                        {
                            pos.y -= cell->getContentSize().height;
                            cell->setPosition(pos);
                        }
                    }
                }
                if (m_drawedRows.length > 0)
                {
                    m_drawedRows.length--;
                    unsigned int nLastRow = CCRange::CCMaxRange(m_drawedRows);
                    this->appendRowToBack(nLastRow + 1);
                }
            }
        }
        else
        {
            for (unsigned int i = m_drawedRows.location; i <= CCRange::CCMaxRange(m_drawedRows); i++)
            {
                CCListViewCell *cell = this->cellAtRow(i);
                if (cell)
                {
                    int tag = cell->getTag();
                    cell->setTag(tag - 1);
                }
            }
            if (m_drawedRows.location > 0)
            {
                m_drawedRows.location--;
            }
        }
    }
        
    m_layerPanel->resumeSchedulerAndActions();
}

void CCListView::scrollCellToFront(unsigned int nRow, bool bAnimated)
{
    if (!isFullFill())
    {
        return;
    }
    if (m_nNumberOfRows == 0)
    {
        return;
    }
    if (CCListViewStateWatting != m_nState)
    {
        this->stopActionImmediately();
    }

    if (nRow >= m_nNumberOfRows)
    {
        nRow = m_nNumberOfRows - 1;
    }

    float disX = 0;
    float disY = 0;
    m_nSlideDir = CCListViewSlideDirNone;
    if (CCListViewModeHorizontal == m_nMode)
    {
        float dis = 0;
        unsigned int nCount = 0;
        CCListViewCell *cell = NULL;
        if (nRow > m_visibleRows.location)
        {
            m_nSlideDir = CCListViewSlideDirLeft;
        }
        else
        {
            m_nSlideDir = CCListViewSlideDirRight;
        }

        while(1)
        {
            if (dis >= this->getContentSize().width || nRow + nCount >= m_nNumberOfRows)
            {
                break;
            }

            if (CCListViewSlideDirRight == m_nSlideDir)
            {
                cell = appendRowToFront(nRow + nCount);
            }
            else if (CCListViewSlideDirLeft == m_nSlideDir)
            {
                cell = appendRowToBack(nRow + nCount);
            }

            if (cell)
            {
                nCount++;
                dis += cell->getContentSize().width;
            }
            else
            {
                CCLog("CCListView cell == NULL at line %d", __LINE__);
            }
        }

        if (CCListViewSlideDirLeft == m_nSlideDir && dis < this->getContentSize().width)
        {
            // at last
            while(1)
            {
                if (dis >= this->getContentSize().width)
                {
                    break;
                }
                cell = appendRowToBack(nRow - 1);
                if (cell)
                {
                    nRow--;
                    dis += cell->getContentSize().width;
                    nCount++;
                }
                else
                {
                    CCLog("CCListView cell == NULL at line %d", __LINE__);
                }
            }
        }

        if (CCListViewSlideDirRight == m_nSlideDir)
        {
            CCListViewCell* cell = NULL;
            unsigned nLast = 0;
            if (CCRange::CCLocationInRange(nRow + nCount - 1, m_visibleRows))
            {
                cell = cellAtRow(nRow + nCount - 1);
                nLast = nRow + nCount - 2;
            }
            else
            {
                cell = cellAtRow(m_visibleRows.location);
                nLast = nRow + nCount - 1;
            }
            if (cell)
            {
                CCPoint pos = cell->getPosition();
                for (int i = nLast; i >= (int)nRow; i--)
                {
                    cell = cellAtRow(i);
                    if (cell)
                    {
                        pos.x -= cell->getContentSize().width;
                        cell->setPosition(pos);
                    }
                    else
                    {
                        CCLog("CCListView cell == NULL at line %d", __LINE__);
                    }
                }
            }
            else
            {
                CCLog("CCListView cell == NULL at line %d", __LINE__);
            }
        }
        else if (CCListViewSlideDirLeft == m_nSlideDir)
        {
            CCListViewCell* cell = NULL;
            unsigned nFirst = 0;
            if (CCRange::CCLocationInRange(nRow, m_visibleRows))
            {
                cell = cellAtRow(nRow);
                nFirst = nRow + 1;
            }
            else
            {
                cell = cellAtRow(CCRange::CCMaxRange(m_visibleRows));
                nFirst = nRow;
            }
            if (cell)
            {
                CCPoint pos = cell->getPosition();
                pos.x += cell->getContentSize().width;
                for (unsigned int i = nFirst; i < nRow + nCount; i++)
                {
                    cell = cellAtRow(i);
                    if (cell)
                    {
                        cell->setPosition(pos);
                        pos.x += cell->getContentSize().width;

                    }
                    else
                    {
                        CCLog("CCListView cell == NULL at line %d", __LINE__);
                    }
                }
            }
            else
            {
                CCLog("CCListView cell == NULL at line %d", __LINE__);
            }
        }


        cell = cellAtRow(nRow);
        CCPoint ptCell = cell->convertToWorldSpace(CCPointZero);
        CCPoint ptView = this->convertToWorldSpace(CCPointZero);
        disX = ptView.x - ptCell.x;
    }
    else if (CCListViewModeVertical == m_nMode)
    {
        float dis = 0;
        unsigned int nCount = 0;
        CCListViewCell *cell = NULL;
        if (nRow > m_visibleRows.location)
        {
            m_nSlideDir = CCListViewSlideDirUp;
        }
        else
        {
            m_nSlideDir = CCListViewSlideDirDown;
        }

        while(1)
        {
            if (dis >= this->getContentSize().height || nRow + nCount >= m_nNumberOfRows)
            {
                break;
            }

            if (CCListViewSlideDirDown == m_nSlideDir)
            {
                cell = appendRowToFront(nRow + nCount);
            }
            else if (CCListViewSlideDirUp == m_nSlideDir)
            {
                cell = appendRowToBack(nRow + nCount);
            }

            if (cell)
            {
                nCount++;
                dis += cell->getContentSize().height;
            }
            else
            {
                CCLog("CCListView cell == NULL at line %d", __LINE__);
            }
        }

        if (CCListViewSlideDirUp == m_nSlideDir && dis < this->getContentSize().height)
        {
            // at last
            while(1)
            {
                if (dis >= this->getContentSize().height)
                {
                    break;
                }
                cell = appendRowToBack(nRow - 1);
                if (cell)
                {
                    nRow--;
                    dis += cell->getContentSize().height;
                    nCount++;
                }
                else
                {
                    CCLog("CCListView cell == NULL at line %d", __LINE__);
                }
            }
        }

        if (CCListViewSlideDirDown == m_nSlideDir)
        {
            CCListViewCell* cell = NULL;
            unsigned nLast = 0;
            if (CCRange::CCLocationInRange(nRow + nCount - 1, m_visibleRows))
            {
                cell = cellAtRow(nRow + nCount - 1);
                nLast = nRow + nCount - 2;
            }
            else
            {
                cell = cellAtRow(m_visibleRows.location);
                nLast = nRow + nCount - 1;
            }
            if (cell)
            {
                CCPoint pos = cell->getPosition();
                pos.y += cell->getContentSize().height;
                for (int i = nLast; i >= (int)nRow; i--)
                {
                    cell = cellAtRow(i);
                    if (cell)
                    {
                        cell->setPosition(pos);
                        pos.y += cell->getContentSize().height;
                    }
                    else
                    {
                        CCLog("CCListView cell == NULL at line %d", __LINE__);
                    }
                }
            }
            else
            {
                CCLog("CCListView cell == NULL at line %d", __LINE__);
            }
        }
        else if (CCListViewSlideDirUp == m_nSlideDir)
        {
            CCListViewCell* cell = NULL;
            unsigned nFirst = 0;
            if (CCRange::CCLocationInRange(nRow, m_visibleRows))
            {
                cell = cellAtRow(nRow);
                nFirst = nRow + 1;
            }
            else
            {
                cell = cellAtRow(CCRange::CCMaxRange(m_visibleRows));
                nFirst = nRow;
            }
            if (cell)
            {
                CCPoint pos = cell->getPosition();
                for (unsigned int i = nFirst; i < nRow + nCount; i++)
                {
                    cell = cellAtRow(i);
                    if (cell)
                    {
                        pos.y -= cell->getContentSize().height;
                        cell->setPosition(pos);
                    }
                    else
                    {
                        CCLog("CCListView cell == NULL at line %d", __LINE__);
                    }
                }
            }
            else
            {
                CCLog("CCListView cell == NULL at line %d", __LINE__);
            }
        }


        cell = cellAtRow(nRow);
        CCPoint ptCell = cell->convertToWorldSpace(CCPointZero);
        CCPoint ptView = this->convertToWorldSpace(CCPointZero);
        disY = ptView.y + this->getContentSize().height - (ptCell.y + cell->getContentSize().height);
    }
    
    m_ptDestination = m_layerPanel->getPosition();
    m_ptDestination.x += disX;
    m_ptDestination.y += disY;
    m_nState = CCListViewStateScroll;

    if (bAnimated)
    {
        CCMoveBy *moveBy = CCMoveBy::create(m_fActionDuration, CCPointMake(disX, disY));
        CCEaseOut *ease = CCEaseOut::create(moveBy, 3);
        CCFiniteTimeAction *actions = CCSequence::create(ease, CCCallFunc::create(this, callfunc_selector(CCListView::finishScroll)), NULL);
        m_layerPanel->runAction(actions);
    }
    else
    {
        stopActionImmediately();
    }
}

void CCListView::scrollCellToBack(unsigned int nRow, bool bAnimated)
{
    if (!isFullFill())
    {
        return;
    }
    if (m_nNumberOfRows == 0)
    {
        return;
    }
    if (CCListViewStateWatting != m_nState)
    {
        this->stopActionImmediately();
    }

    if (nRow >= m_nNumberOfRows)
    {
        nRow = m_nNumberOfRows - 1;
    }

    float disX = 0;
    float disY = 0;
    m_nSlideDir = CCListViewSlideDirNone;
    if (CCListViewModeHorizontal == m_nMode)
    {
        float dis = 0;
        int nCount = 0;
        CCListViewCell *cell = NULL;
        if (nRow > CCRange::CCMaxRange(m_visibleRows))
        {
            m_nSlideDir = CCListViewSlideDirLeft;
        }
        else
        {
            m_nSlideDir = CCListViewSlideDirRight;
        }

        while(1)
        {
            if (dis >= this->getContentSize().width || (int)nRow - nCount < 0)
            {
                break;
            }

            if (CCListViewSlideDirRight == m_nSlideDir)
            {
                cell = appendRowToFront(nRow - nCount);
            }
            else if (CCListViewSlideDirLeft == m_nSlideDir)
            {
                cell = appendRowToBack(nRow - nCount);
            }

            if (cell)
            {
                nCount++;
                dis += cell->getContentSize().width;
            }
            else
            {
                CCLog("CCListView cell == NULL at line %d", __LINE__);
            }
        }

        if (CCListViewSlideDirRight == m_nSlideDir && dis < this->getContentSize().width)
        {
            // at first
            while(1)
            {
                if (dis >= this->getContentSize().width)
                {
                    break;
                }
                cell = appendRowToBack(nRow + 1);
                if (cell)
                {
                    nRow++;
                    dis += cell->getContentSize().width;
                    nCount++;
                }
                else
                {
                    CCLog("CCListView cell == NULL at line %d", __LINE__);
                }
            }
        }

        if (CCListViewSlideDirRight == m_nSlideDir)
        {
            CCListViewCell* cell = NULL;
            unsigned nLast = 0;
            if (CCRange::CCLocationInRange(nRow, m_visibleRows))
            {
                cell = cellAtRow(nRow);
                nLast = nRow - 1;
            }
            else
            {
                cell = cellAtRow(m_visibleRows.location);
                nLast = nRow;
            }
            if (cell)
            {
                CCPoint pos = cell->getPosition();
                for (int i = nLast; i >= (int)(nRow - nCount + 1); i--)
                {
                    cell = cellAtRow(i);
                    if (cell)
                    {
                        pos.x -= cell->getContentSize().width;
                        cell->setPosition(pos);
                    }
                    else
                    {
                        CCLog("CCListView cell == NULL at line %d", __LINE__);
                    }
                }
            }
            else
            {
                CCLog("CCListView cell == NULL at line %d", __LINE__);
            }
        }
        else if (CCListViewSlideDirLeft == m_nSlideDir)
        {
            CCListViewCell* cell = NULL;
            unsigned nFirst = 0;
            if (CCRange::CCLocationInRange(nRow - nCount + 1, m_visibleRows))
            {
                cell = cellAtRow(nRow - nCount + 1);
                nFirst = nRow - nCount + 2;
                nCount--;
            }
            else
            {
                cell = cellAtRow(CCRange::CCMaxRange(m_visibleRows));
                nFirst = nRow - nCount + 1;
            }
            if (cell)
            {
                CCPoint pos = cell->getPosition();
                pos.x += cell->getContentSize().width;
                for (unsigned int i = nFirst; i < nFirst + nCount; i++)
                {
                    cell = cellAtRow(i);
                    if (cell)
                    {
                        cell->setPosition(pos);
                        pos.x += cell->getContentSize().width;

                    }
                    else
                    {
                        CCLog("CCListView cell == NULL at line %d", __LINE__);
                    }
                }
            }
            else
            {
                CCLog("CCListView cell == NULL at line %d", __LINE__);
            }
        }


        cell = cellAtRow(nRow);
        CCPoint ptCell = cell->convertToWorldSpace(CCPointZero);
        CCPoint ptView = this->convertToWorldSpace(CCPointZero);
        disX = ptView.x + this->getContentSize().width - (ptCell.x + cell->getContentSize().width);
    }
    else if (CCListViewModeVertical == m_nMode)
    {
        float dis = 0;
        int nCount = 0;
        CCListViewCell *cell = NULL;
        if (nRow > CCRange::CCMaxRange(m_visibleRows))
        {
            m_nSlideDir = CCListViewSlideDirUp;
        }
        else
        {
            m_nSlideDir = CCListViewSlideDirDown;
        }

        while(1)
        {
            if (dis >= this->getContentSize().height || (int)nRow - nCount < 0)
            {
                break;
            }

            if (CCListViewSlideDirDown == m_nSlideDir)
            {
                cell = appendRowToFront(nRow - nCount);
            }
            else if (CCListViewSlideDirUp == m_nSlideDir)
            {
                cell = appendRowToBack(nRow - nCount);
            }

            if (cell)
            {
                nCount++;
                dis += cell->getContentSize().height;
            }
            else
            {
                CCLog("CCListView cell == NULL at line %d", __LINE__);
            }
        }

        if (CCListViewSlideDirDown == m_nSlideDir && dis < this->getContentSize().height)
        {
            // at first
            while(1)
            {
                if (dis >= this->getContentSize().height)
                {
                    break;
                }
                cell = appendRowToBack(nRow + 1);
                if (cell)
                {
                    nRow++;
                    dis += cell->getContentSize().height;
                    nCount++;
                }
                else
                {
                    CCLog("CCListView cell == NULL at line %d", __LINE__);
                }
            }
        }

        if (CCListViewSlideDirDown == m_nSlideDir)
        {
            CCListViewCell* cell = NULL;
            unsigned nLast = 0;
            if (CCRange::CCLocationInRange(nRow, m_visibleRows))
            {
                cell = cellAtRow(nRow);
                nLast = nRow - 1;
            }
            else
            {
                cell = cellAtRow(m_visibleRows.location);
                nLast = nRow;
            }
            if (cell)
            {
                CCPoint pos = cell->getPosition();
                pos.y += cell->getContentSize().height;
                for (int i = nLast; i >= (int)(nRow - nCount + 1); i--)
                {
                    cell = cellAtRow(i);
                    if (cell)
                    {
                        cell->setPosition(pos);
                        pos.y += cell->getContentSize().height;
                    }
                    else
                    {
                        CCLog("CCListView cell == NULL at line %d", __LINE__);
                    }
                }
            }
            else
            {
                CCLog("CCListView cell == NULL at line %d", __LINE__);
            }
        }
        else if (CCListViewSlideDirUp == m_nSlideDir)
        {
            CCListViewCell* cell = NULL;
            unsigned nFirst = 0;
            if (CCRange::CCLocationInRange(nRow - nCount + 1, m_visibleRows))
            {
                cell = cellAtRow(nRow - nCount + 1);
                nFirst = nRow - nCount + 2;
                nCount--;
            }
            else
            {
                cell = cellAtRow(CCRange::CCMaxRange(m_visibleRows));
                nFirst = nRow - nCount + 1;
            }
            if (cell)
            {
                CCPoint pos = cell->getPosition();
                for (unsigned int i = nFirst; i < nFirst + nCount; i++)
                {
                    cell = cellAtRow(i);
                    if (cell)
                    {
                        pos.y -= cell->getContentSize().height;
                        cell->setPosition(pos);
                    }
                    else
                    {
                        CCLog("CCListView cell == NULL at line %d", __LINE__);
                    }
                }
            }
            else
            {
                CCLog("CCListView cell == NULL at line %d", __LINE__);
            }
        }


        cell = cellAtRow(nRow);
        CCPoint ptCell = cell->convertToWorldSpace(CCPointZero);
        CCPoint ptView = this->convertToWorldSpace(CCPointZero);
        disY = ptView.y - ptCell.y;
    }

    m_ptDestination = m_layerPanel->getPosition();
    m_ptDestination.x += disX;
    m_ptDestination.y += disY;
    m_nState = CCListViewStateScroll;

    if (bAnimated)
    {
        CCMoveBy *moveBy = CCMoveBy::create(m_fActionDuration, CCPointMake(disX, disY));
        CCEaseOut *ease = CCEaseOut::create(moveBy, 3);
        CCFiniteTimeAction *actions = CCSequence::create(ease, CCCallFunc::create(this, callfunc_selector(CCListView::finishScroll)), NULL);
        m_layerPanel->runAction(actions);
    }
    else
    {
        stopActionImmediately();
    }
}

CCListViewSlideDir CCListView::getSlideDir(CCPoint ptTouchBegan, CCPoint ptTouchEnd)
{
    CCListViewSlideDir nSlideDir = CCListViewSlideDirNone;

    int nOffsetX = ptTouchEnd.x - ptTouchBegan.x;
    int nOffsetY = ptTouchEnd.y - ptTouchBegan.y;

    int disMin = CCDirector::sharedDirector()->getWinSize().height / 100;

    if(CCListViewModeHorizontal == m_nMode)
    {
        if(nOffsetX >= disMin)
        {
            nSlideDir = CCListViewSlideDirRight;
        }
        else if (nOffsetX <= -disMin)
        {
            nSlideDir = CCListViewSlideDirLeft;
        }
    }
    else if (CCListViewModeVertical == m_nMode)
    {
        if(nOffsetY >= disMin)
        {
            nSlideDir = CCListViewSlideDirUp;
        }
        else if (nOffsetY <= -disMin)
        {
            nSlideDir = CCListViewSlideDirDown;
        }
    }
    return nSlideDir;
}

/******************************************
**************Private Functions************
*******************************************/
int CCListView::rowForTouch(cocos2d::CCTouch *touch)
{
    CCPoint touchLocation = touch->locationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);

    CCArray *pChildren = m_layerPanel->getChildren();
    if (pChildren && pChildren->count() > 0)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(pChildren, pObject)
        {
            CCNode* pChild = (CCNode*) pObject;
            if (pChild && pChild->isVisible())
            {
                CCPoint local = pChild->convertToNodeSpace(touchLocation);
                CCRect r = CCRectZero;
                r.size = pChild->getContentSize();

                if (CCRect::CCRectContainsPoint(r, local))
                {
                    return pChild->getTag();
                }
            }
        }

    }

    return -1;
}

void CCListView::finishFix(void)
{
    if(m_pListViewParent)
    {
        m_pListViewParent->setEnabled(true);
    }
    m_nState = CCListViewStateWatting;
    m_nSlideDir = CCListViewSlideDirNone;
    clearUnvisibleRows();
    triggerDidScrollToRow(m_visibleRows.location);

    CCArray *children = m_layerPanel->getChildren();
    int nCount = 0;
    if (children)
    {
        nCount = children->count();
    }
    //CCLog("row num left:%d [%d, %d]", nCount, m_drawedRows.location, CCRange::CCMaxRange(m_drawedRows));
}

void CCListView::finishScroll(void)
{
    finishFix();
}

void CCListView::finishEaseOut(void)
{
    bool bNeedFix = false;

    if (CCListViewModeHorizontal == m_nMode)
    {
        bool bFullFill = isFullFill();
        if (CCListViewSlideDirLeft == m_nSlideDir && bFullFill)
        {
            CCListViewCell *cell = cellAtRow(m_nNumberOfRows - 1);
            if (cell)
            {
                CCPoint ptCell = cell->convertToWorldSpace(CCPointZero);
                CCPoint ptView = this->convertToWorldSpace(CCPointZero);
                if (ptCell.x + cell->getContentSize().width < ptView.x + this->getContentSize().width)
                {
                    bNeedFix = true;
                    fixLastRow();
                }
            }
        }
        else
        {
            CCListViewCell *cell = cellAtRow(0);
            if (cell)
            {
                CCPoint ptCell = cell->convertToWorldSpace(CCPointZero);
                CCPoint ptView = this->convertToWorldSpace(CCPointZero);
                if (ptCell.x > ptView.x || !bFullFill)
                {
                    bNeedFix = true;
                    fixFirstRow();
                }
            }
        }
    }
    else if (CCListViewModeVertical == m_nMode)
    {
        bool bFullFill = this->isFullFill();
        if (CCListViewSlideDirUp == m_nSlideDir && bFullFill)
        {
            CCListViewCell *cell = cellAtRow(m_nNumberOfRows - 1);
            if (cell)
            {
                CCPoint ptCell = cell->convertToWorldSpace(CCPointZero);
                CCPoint ptView = this->convertToWorldSpace(CCPointZero);
                if (ptCell.y > ptView.y)
                {
                    bNeedFix = true;
                    fixLastRow();
                }
            }
        }
        else
        {
            CCListViewCell *cell = cellAtRow(0);
            if (cell)
            {
                CCPoint ptCell = cell->convertToWorldSpace(CCPointZero);
                CCPoint ptView = this->convertToWorldSpace(CCPointZero);
                if (ptCell.y + cell->getContentSize().height < ptView.y + this->getContentSize().height || !bFullFill)
                {
                    bNeedFix = true;
                    fixFirstRow();
                }
            }
        }
    }

    if (!bNeedFix)
    {
        finishFix();
    }
}

bool CCListView::isTouchInside(CCTouch *touch)
{
    CCPoint point;
    if (m_pListViewParent)
    {
        point = m_pListViewParent->convertTouchToNodeSpace(touch);
    }
    else
    {
        point = this->convertTouchToNodeSpace(touch);
    }
    CCRect bounds = CCRectMake(0, 0, this->getContentSize().width, this->getContentSize().height);
    bool bIn =  CCRect::CCRectContainsPoint(bounds, point);
    return bIn;
}

bool CCListView::isFullFill(void)
{
    bool bRet = false;
    float length = 0;
    for (unsigned int i = m_drawedRows.location; i <= CCRange::CCMaxRange(m_drawedRows); i++)
    {
        CCListViewCell *cell = cellAtRow(i);
        if (cell)
        {
            if (CCListViewModeHorizontal == m_nMode)
            {
                length += cell->getContentSize().width;
                if (length >= this->getContentSize().width)
                {
                    bRet = true;
                    break;
                }
            }
            else if (CCListViewModeVertical == m_nMode)
            {
                length += cell->getContentSize().height;
                if (length >= this->getContentSize().height)
                {
                    bRet = true;
                    break;
                }
            }
        }
    }
    return bRet;
}

CCListViewCell *CCListView::cellAtRow(unsigned int nRow)
{
    CCListViewCell *cell = (CCListViewCell*)m_layerPanel->getChildByTag(nRow);
    return cell;
}

void CCListView::stopActionImmediately(void)
{
    m_layerPanel->stopAllActions();
    if (CCListViewStateScroll == m_nState)
    {
        m_layerPanel->setPosition(m_ptDestination);
        finishScroll();
    }
}

unsigned int CCListView::triggerNumberOfCells(void)
{
    unsigned int nRow = 0;
    CCListViewProtrolData data;
    data.nNumberOfRows = 0;
    data.nRow = 0;
    data.cell = NULL;

    if (m_strDeletegate.size() > 0)
    {
        CCScriptEngineProtocol* scriptEngine = CCScriptEngineManager::sharedManager()->getScriptEngine();
        if (scriptEngine)
        {
            std::string script;
            script = m_strDeletegate + "CCListView_numberOfCells";
//TODO:            scriptEngine->executeCallFuncNTDT(script.c_str(), this, "NdCxControl::CCListView", &data, "NdCxControl::CCListViewProtrolData");
            nRow = data.nNumberOfRows;
        }
    }

    if (m_pDelegate)
    {
        m_pDelegate->CCListView_numberOfCells(this, &data);
        nRow = data.nNumberOfRows;
    }
    return nRow;
}

CCListViewCell *CCListView::triggerCellForRow(unsigned int nRow)
{
    CCListViewCell *cell = NULL;
    CCListViewProtrolData data;
    data.nRow = nRow;
    data.cell = NULL;
    if (m_strDeletegate.size() > 0)
    {
        CCScriptEngineProtocol* scriptEngine = CCScriptEngineManager::sharedManager()->getScriptEngine();
        if (scriptEngine)
        {
            std::string script;
            script = m_strDeletegate + "CCListView_cellForRow";
//TODO:            scriptEngine->executeCallFuncNTDT(script.c_str(), this, "NdCxControl::CCListView",  &data, "NdCxControl::CCListViewProtrolData");
            cell = data.cell;
        }
    }
    if (m_pDelegate)
    {
        m_pDelegate->CCListView_cellForRow(this, &data);
        cell = data.cell;
    }
    return cell;
}

void CCListView::triggerDidClickCellAtRow(unsigned int nRow)
{
    CCListViewProtrolData data;
    data.nRow = nRow;
    if (m_strDeletegate.size() > 0)
    {
        CCScriptEngineProtocol* scriptEngine = CCScriptEngineManager::sharedManager()->getScriptEngine();
        if (scriptEngine)
        {
            std::string script;
            script = m_strDeletegate + "CCListView_didClickCellAtRow";
//TODO:            scriptEngine->executeCallFuncNTDT(script.c_str(), this, "NdCxControl::CCListView", &data, "NdCxControl::CCListViewProtrolData");
        }
    }

    if (m_pDelegate)
    {
        m_pDelegate->CCListView_didClickCellAtRow(this, &data);
    }
}

void CCListView::triggerDidScrollToRow(unsigned int nRow)
{
    CCListViewProtrolData data;
    data.nRow = nRow;
    if (m_strDeletegate.size() > 0)
    {
        CCScriptEngineProtocol* scriptEngine = CCScriptEngineManager::sharedManager()->getScriptEngine();
        if (scriptEngine)
        {
            std::string script;
            script = m_strDeletegate + "CCListView_didScrollToRow";
//TODO:            scriptEngine->executeCallFuncNTDT(script.c_str(), this, "NdCxControl::CCListView", &data, "NdCxControl::CCListViewProtrolData");
        }
    }
    if (m_pDelegate)
    {
        m_pDelegate->CCListView_didScrollToRow(this, &data);
    }
}

void CCListView::displayVisibleRows(void)
{
    CCSize size = getContentSize();
    float posPannel, boundPannel;
    unsigned int rowCount = m_drawedRows.location;
    
    CCListViewCell *cell = cellAtRow(rowCount);

    if (m_nMode == CCListViewModeHorizontal)
    {
        if (cell)
        {
            posPannel = cell->getPosition().x;
        }
        else
        {
            posPannel = m_layerPanel->getPosition().x;
        }
        boundPannel = posPannel + size.width;
    }
    else if (m_nMode == CCListViewModeVertical)
    {
        if (cell)
        {
            posPannel = cell->getPosition().y + cell->getContentSize().height;
        }
        else
        {
            posPannel = size.height - m_layerPanel->getPosition().y;
        }
        boundPannel = posPannel - size.height;
    }

    CCListViewCell *lastCell = NULL;
    while(1)
    {
        // row condition
        if (rowCount >= m_nNumberOfRows)
            break;

        // size condition
        if (m_nMode == CCListViewModeHorizontal)
        {
            if (posPannel >= boundPannel)
                break;
        }
        else if (m_nMode == CCListViewModeVertical)
        {
            if (posPannel <= boundPannel)
                break;
        }

        // get cell
        CCListViewCell *cell = cellAtRow(rowCount);

        if (NULL == cell)
        {
            cell = triggerCellForRow(rowCount);
            if (cell)
            {
                CCSize cellSize = cell->getContentSize();
                if (m_nMode == CCListViewModeHorizontal)
                {
                    cell->setPosition(CCPointMake(posPannel, 0));
                    cell->setContentSize(CCSizeMake(cellSize.width, size.height));
                }
                else if (m_nMode == CCListViewModeVertical)
                {
                    cell->setPosition(CCPointMake(0, posPannel - cellSize.height));
                    cell->setContentSize(CCSizeMake(size.width, cellSize.height));
                }
                m_layerPanel->addChild(cell, rowCount, rowCount);
            }
        }

        if (cell)
        {
            if (m_nMode == CCListViewModeHorizontal)
            {
                posPannel += cell->getContentSize().width;
            }
            else if (m_nMode == CCListViewModeVertical)
            {
                posPannel -= cell->getContentSize().height;
            }
            cell->setSeparatorStyle(m_nSeparatorStyle);
            lastCell = cell;
        }

        ++rowCount;
    }
    m_drawedRows.length = rowCount - m_drawedRows.location;
    // set visible range
    m_visibleRows = m_drawedRows;

    if (lastCell)
    {
        lastCell->setSeparatorStyle(CCListViewCellSeparatorStyleNone);
    }
}

CCListViewCell* CCListView::appendRowToBack(unsigned int nRow)
{
    if (nRow >= m_nNumberOfRows)
    {
        return NULL;
    }
    CCListViewCell *cell = cellAtRow(nRow);
    if (cell == NULL)
    {
        cell = triggerCellForRow(nRow);
        if (cell)
        {
            CCSize size = this->getContentSize();
            CCSize cellSize = cell->getContentSize();
            float pos;
            unsigned int nLastRow = CCRange::CCMaxRange(m_drawedRows);
            CCListViewCell *lastCell = cellAtRow(nLastRow);
            if (lastCell)
            {
                if (m_nMode == CCListViewModeHorizontal)
                {
                    pos = lastCell->getPosition().x + lastCell->getContentSize().width;
                    cell->setPosition(CCPointMake(pos, 0));
                    cell->setContentSize(CCSizeMake(cellSize.width, size.height));
                }
                else if (m_nMode == CCListViewModeVertical)
                {
                    pos = lastCell->getPosition().y - cell->getContentSize().height;
                    cell->setPosition(CCPointMake(0, pos));
                    cell->setContentSize(CCSizeMake(size.width, cellSize.height));
                }

                if (nRow == m_nSelectedRow)
                {
                    cell->selected();
                }
                m_layerPanel->addChild(cell, nRow, nRow);
                if (nRow > CCRange::CCMaxRange(m_drawedRows))
                {
                    cell->setSeparatorStyle(CCListViewCellSeparatorStyleNone);
                    lastCell->setSeparatorStyle(m_nSeparatorStyle);
                    m_drawedRows.length += nRow - CCRange::CCMaxRange(m_drawedRows);
                }
                else
                {
                    cell->setSeparatorStyle(m_nSeparatorStyle);
                }
            }
            else
            {
                CCLog("CCListView cell == NULL at line %d", __LINE__);
            }
        }
        else
        {
            CCLog("CCListView cell == NULL at line %d", __LINE__);
        }
    }
    return cell;
}

CCListViewCell* CCListView::appendRowToFront(unsigned int nRow)
{
    CCListViewCell *cell = cellAtRow(nRow);
    if (cell == NULL)
    {
        cell = triggerCellForRow(nRow);
        if (cell)
        {
            CCSize size = this->getContentSize();
            CCSize cellSize = cell->getContentSize();
            float pos;
            unsigned int nFirstRow = m_drawedRows.location;
            CCListViewCell *firstCell = cellAtRow(nFirstRow);
            if (firstCell)
            {
                if (m_nMode == CCListViewModeHorizontal)
                {
                    pos = firstCell->getPosition().x - cell->getContentSize().width;
                    cell->setPosition(CCPointMake(pos, 0));
                    cell->setContentSize(CCSizeMake(cellSize.width, size.height));
                }
                else if (m_nMode == CCListViewModeVertical)
                {
                    pos = firstCell->getPosition().y + firstCell->getContentSize().height;
                    cell->setPosition(CCPointMake(0, pos));
                    cell->setContentSize(CCSizeMake(size.width, cellSize.height));
                }
                cell->setSeparatorStyle(m_nSeparatorStyle);
                if (nRow == m_nSelectedRow)
                {
                    cell->selected();
                }
                m_layerPanel->addChild(cell, nRow, nRow);
                if (nRow < m_drawedRows.location)
                {
                    m_drawedRows.length += m_drawedRows.location - nRow;
                    m_drawedRows.location = nRow;
                }
            }
            else
            {
                CCLog("CCListView cell == NULL at line %d", __LINE__);
            }
        }
        else
        {
                CCLog("CCListView cell == NULL at line %d", __LINE__);
        }
    }
    return cell;
}

// align first row
void CCListView::fixFirstRow(void)
{
    unsigned int location = m_drawedRows.location;

    CCListViewCell *cell = cellAtRow(location);
    if (cell)
    {
        float disX = 0;
        float disY = 0;
        CCPoint posCell = cell->convertToWorldSpace(CCPointZero);
        CCPoint posView = this->convertToWorldSpace(CCPointZero);
        if (CCListViewModeHorizontal == m_nMode)
        {
            float dis = posCell.x - posView.x;
            dis = -dis;

            disX = dis;
            disY = 0;
        }
        else if (CCListViewModeVertical == m_nMode)
        {
            float dis = posCell.y + cell->getContentSize().height - (posView.y + this->getContentSize().height);
            dis = -dis;

            disX = 0;
            disY = dis;
        }
        
        m_nState = CCListViewStateFix;
        CCMoveBy *moveBy = CCMoveBy::create(m_fActionDuration, CCPointMake(disX, disY));
        CCEaseInOut *ease = CCEaseInOut::create(moveBy, 2);
        CCFiniteTimeAction *actions = CCSequence::create(ease, CCCallFunc::create(this, callfunc_selector(CCListView::finishFix)), NULL);
        m_layerPanel->runAction(actions);
    }
    else
    {
        this->finishFix();
    }
}
// align last row
void CCListView::fixLastRow(void)
{
    unsigned int nLastRow = CCRange::CCMaxRange(m_drawedRows);
    CCListViewCell *cell = cellAtRow(nLastRow);
    if (cell)
    {
        float disX = 0;
        float disY = 0;
        CCPoint posCell = cell->convertToWorldSpace(CCPointZero);
        CCPoint posView = this->convertToWorldSpace(CCPointZero);
        if (CCListViewModeHorizontal == m_nMode)
        {
            float dis = posCell.x + cell->getContentSize().width - (posView.x + this->getContentSize().width);
            dis = -dis;
            
            disX = dis;
            disY = 0;
        }
        else if (CCListViewModeVertical == m_nMode)
        {
            float dis = posCell.y - posView.y;
            dis = -dis;

            disX = 0;
            disY = dis;
        }

        m_nState = CCListViewStateFix;
        CCMoveBy *moveBy = CCMoveBy::create(m_fActionDuration, CCPointMake(disX, disY));
        CCEaseInOut *ease = CCEaseInOut::create(moveBy, 2);
        CCFiniteTimeAction *actions = CCSequence::create(ease, CCCallFunc::create(this, callfunc_selector(CCListView::finishFix)), NULL);
        m_layerPanel->runAction(actions);
    }
    else
    {
        finishFix();
    }
}

void CCListView::easeOutWithDistance(float dis)
{
    float disX = 0;
    float disY = 0;

    if (CCListViewModeHorizontal == m_nMode)
    {
        if (CCListViewSlideDirLeft == m_nSlideDir)
        {
            // drag Left
            while(1)
            {
                unsigned int nLastRow = CCRange::CCMaxRange(m_drawedRows);
                CCListViewCell *cell = cellAtRow(nLastRow);
                if (cell)
                {
                    CCPoint ptCell = cell->convertToWorldSpace(CCPointZero);
                    CCPoint ptView = this->convertToWorldSpace(CCPointZero);
                    if (nLastRow < m_nNumberOfRows - 1)
                    {
                        float offset = ptView.x + this->getContentSize().width - (ptCell.x + cell->getContentSize().width);
                        if (offset > dis)
                        {
                            appendRowToBack(nLastRow + 1);
                        }
                        else
                        {
                            dis = offset;
                            break;
                        }
                    }
                    else
                    {
                        // already is the last row
                        float leftMin = cell->getContentSize().width / 5;
                        float offset = ptCell.x + cell->getContentSize().width + dis - ptView.x;
                        if (offset < -leftMin)
                        {
                            dis = ptView.x + leftMin - (ptCell.x + cell->getContentSize().width);
                        }
                        offset = ptCell.x + cell->getContentSize().width + dis - (ptView.x + this->getContentSize().width) ;
                        if (offset > 0)
                        {
                            dis = ptView.x + this->getContentSize().width - (ptCell.x + cell->getContentSize().width);
                        }
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            // drag right
            while(1)
            {
                unsigned int nFirstRow = m_drawedRows.location;
                CCListViewCell *cell = cellAtRow(nFirstRow);
                if (cell)
                {
                    CCPoint ptCell = cell->convertToWorldSpace(CCPointZero);
                    CCPoint ptView = this->convertToWorldSpace(CCPointZero);
                    if (nFirstRow > 0)
                    {
                        float offset = ptView.x - ptCell.x;
                        if (offset < dis)
                        {
                            appendRowToFront(nFirstRow - 1);
                        }
                        else
                        {
                            dis = offset;
                            break;
                        }
                    }
                    else
                    {
                        // already is the first row
                        float leftMin = cell->getContentSize().width / 5;
                        float offset = ptCell.x + dis - (ptView.x + this->getContentSize().width);
                        if (offset > leftMin)
                        {
                            dis = ptView.x + this->getContentSize().width - leftMin - ptCell.x;
                        }
                        offset = ptView.x - ptCell.x;
                        if (offset > 0)
                        {
                            dis = offset;
                        }
                        break;
                    }
                }
                else
                {

                }
            }
        }
        disX = dis;
        disY = 0;
    }
    else if (CCListViewModeVertical == m_nMode)
    {
        if (CCListViewSlideDirUp == m_nSlideDir)
        {
            // drag up
            while(1)
            {
                unsigned int nLastRow = CCRange::CCMaxRange(m_drawedRows);
                CCListViewCell *cell = cellAtRow(nLastRow);
                if (cell)
                {
                    CCPoint ptCell = cell->convertToWorldSpace(CCPointZero);
                    CCPoint ptView = this->convertToWorldSpace(CCPointZero);
                    if (nLastRow < m_nNumberOfRows - 1)
                    {
                        float offset = ptView.y - ptCell.y;
                        if (offset < dis)
                        {
                            appendRowToBack(nLastRow + 1);
                        }
                        else
                        {
                            dis = offset;
                            break;
                        }
                    }
                    else
                    {
                        // already is the last row
                        m_fActionDuration *= 0.5;
                        float leftMin = cell->getContentSize().height / 5;
                        float offset = ptCell.y + dis - (ptView.y + this->getContentSize().height);
                        if (offset > -leftMin)
                        {
                            dis = ptView.y + this->getContentSize().height - leftMin - ptCell.y;
                        }
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            // drag down
            while(1)
            {
                unsigned int nFirstRow = m_drawedRows.location;
                CCListViewCell *cell = cellAtRow(nFirstRow);
                if (cell)
                {
                    CCPoint ptCell = cell->convertToWorldSpace(CCPointZero);
                    CCPoint ptView = this->convertToWorldSpace(CCPointZero);
                    if (nFirstRow > 0)
                    {
                        float offset = ptView.y + this->getContentSize().height - (ptCell.y + cell->getContentSize().height);
                        if (offset > dis)
                        {
                            appendRowToFront(nFirstRow - 1);
                        }
                        else
                        {
                            dis = offset;
                            break;
                        }
                    }
                    else
                    {
                        // already is the first row
                        m_fActionDuration *= 0.5;
                        float leftMin = cell->getContentSize().height / 5;
                        float offset = ptCell.y + cell->getContentSize().height + dis - ptView.y;
                        if (offset < leftMin)
                        {
                            dis = ptView.y + leftMin - (ptCell.y + cell->getContentSize().height);
                        }
                        break;
                    }
                }
                else
                {

                }
            }
        }
        disX = 0;
        disY = dis;
    }

    m_nState = CCListViewStateEaseOut;
    CCMoveBy *moveBy = CCMoveBy::create(m_fActionDuration, CCPointMake(disX, disY));
    CCEaseOut *ease = CCEaseOut::create(moveBy, 3);
    CCFiniteTimeAction *actions = CCSequence::create(ease, CCCallFunc::create(this, callfunc_selector(CCListView::finishEaseOut)), NULL);
    m_layerPanel->runAction(actions);
}

void CCListView::clearUnvisibleRows(void)
{
    CCRange oldRange = m_drawedRows;
    for (unsigned int i = oldRange.location; i < oldRange.location + oldRange.length; i++)
    {
        CCListViewCell *cell = cellAtRow(i);
        if (cell)
        {
            CCPoint posCell = cell->convertToWorldSpace(CCPointZero);
            CCPoint posView = this->convertToWorldSpace(CCPointZero);
            if (CCListViewModeHorizontal == m_nMode)
            {
                if (posCell.x + cell->getContentSize().width <= posView.x) 
                {
                    m_layerPanel->removeChild(cell, true);
                }
                else
                {
                    break;
                }
            }
            else if (CCListViewModeVertical == m_nMode)
            {
                if (posCell.y >= posView.y + this->getContentSize().height) 
                {
                    m_layerPanel->removeChild(cell, true);
                }
                else
                {
                    break;
                }
            }
        }
        m_drawedRows.location++;
        m_drawedRows.length--;
    }

    oldRange = m_drawedRows;
    for (int i = oldRange.location + oldRange.length - 1; i >= (int)oldRange.location; i--)
    {
        CCListViewCell *cell = cellAtRow(i);
        if (cell)
        {
            CCPoint posCell = cell->convertToWorldSpace(CCPointZero);
            CCPoint posView = this->convertToWorldSpace(CCPointZero);
            if (CCListViewModeHorizontal == m_nMode)
            {
                if (posCell.x >= posView.x + this->getContentSize().width) 
                {
                    m_layerPanel->removeChild(cell, true);
                }
                else
                {
                    break;
                }
            }
            else if (CCListViewModeVertical == m_nMode)
            {
                if (posCell.y + cell->getContentSize().height <= posView.y) 
                {
                    m_layerPanel->removeChild(cell, true);
                }
                else
                {
                    break;
                }
            }
        }
        m_drawedRows.length--;
    }

    m_visibleRows = m_drawedRows;
}
/******************************************
**************Virturl Functions************
*******************************************/
void CCListView::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    if (m_pListViewParent)
    {
        pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 1, false);
    }
    else
    {
        pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 2, false);
    }
}

void CCListView::onEnter(void)
{
    CCLayerColor::onEnter();

    if (0 == m_nNumberOfRows)
    {
        m_layerPanel->setPosition(CCPointZero);
        m_layerPanel->setContentSize(this->getContentSize());
        // get number of rows
        m_nNumberOfRows = triggerNumberOfCells();
        displayVisibleRows();
    }
}

void CCListView::onExit(void)
{
    CCLayerColor::onExit();
}

void CCListView::visit(void)
{
    if (!m_pListViewParent)
    {
        CCRect rectSelf;
        float factor = CC_CONTENT_SCALE_FACTOR();
        rectSelf.origin = convertToWorldSpace(CCPoint(0,0));
        rectSelf.origin.x *= factor;
        rectSelf.origin.y *= factor;
        rectSelf.size = this->getContentSize();
        rectSelf.size.width *= factor;
        rectSelf.size.height *= factor;
        glScissor((GLsizei)rectSelf.origin.x, (GLsizei)rectSelf.origin.y, (GLsizei)rectSelf.size.width , (GLsizei)rectSelf.size.height);
        glEnable(GL_SCISSOR_TEST);
    }
    CCLayerColor::visit();
    if (!m_pListViewParent)
    {
        glDisable(GL_SCISSOR_TEST);
    }
}

bool CCListView::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
     CC_UNUSED_PARAM(event);

    if (!isTouchInside(touch) || !isVisible() || !m_bIsEnabled)
    {
        return false;
    }

    if (m_pListViewParent && CCListViewSlideDirNone != m_pListViewParent->getSlideDir())
    {
        return false;
    }

    CCArray *children = this->getChildren();
    if (!m_bIsVisible || !children || children->count() == 0)
    {
        return false;
    }

    if (m_bIsOnTouch)
    {
        return false;
    }

    CCPoint touchPoint = touch->locationInView();

    m_ptTouchBegan = m_ptTouchEnd = CCDirector::sharedDirector()->convertToGL(touchPoint);
    m_ptPanelOffset = m_layerPanel->getPosition();

    m_timeTouchBegan = clock();

    m_nCurrentRow = this->rowForTouch(touch);
    if (m_nCurrentRow != -1)
    {    
        if (CCListViewStateWatting != m_nState)
        {
            stopActionImmediately();
        }

        m_nState = CCListViewStateTrackingTouch;
        if (CCListViewSlideDirNone == m_nSlideDir)
        {
            this->selectCellAtRow(m_nCurrentRow);
        }
        else
        {
            m_nCurrentRow = -1;
        }
        m_bIsOnTouch = true;
        return true;
    }


    return false;
}

void CCListView::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    CC_UNUSED_PARAM(event);
    if (CCListViewStateTrackingTouch != m_nState || !isTouchInside(touch) || !m_bIsEnabled)
    {
        return;
    }

    CCPoint touchPoint = touch->locationInView();
    m_ptTouchEnd = CCDirector::sharedDirector()->convertToGL(touchPoint);             


    CCListViewSlideDir nsliderDir = CCListViewSlideDirNone;
    if (m_pListViewParent && CCListViewSlideDirNone != m_pListViewParent->getSlideDir(m_ptTouchBegan, m_ptTouchEnd))
    {
        return;
    }
    else
    {
        nsliderDir = getSlideDir(m_ptTouchBegan, m_ptTouchEnd);
    }
    

    if(CCListViewModeHorizontal == m_nMode && CCListViewSlideDirNone != nsliderDir)
    {
        m_nSlideDir = nsliderDir;
        m_layerPanel->setPosition(CCPointMake(m_ptPanelOffset.x + (m_ptTouchEnd.x - m_ptTouchBegan.x),m_ptPanelOffset.y));
        if (CCListViewSlideDirLeft == m_nSlideDir)
        {
            // drag left
            unsigned int nLastRow = CCRange::CCMaxRange(m_drawedRows);
            if (nLastRow < m_nNumberOfRows - 1)
            {
                CCListViewCell *cell = cellAtRow(nLastRow);
                if (cell)
                {
                    CCPoint posCell = cell->convertToWorldSpace(CCPointZero);
                    CCPoint posView = this->convertToWorldSpace(CCPointZero);
                    if (posCell.x + cell->getContentSize().width <= posView.x + this->getContentSize().width)
                    {
                        appendRowToBack(nLastRow + 1);
                    }
                }
            }
        }
        else
        {
            // drag right
            unsigned int nFirstRow = m_drawedRows.location;
            if (nFirstRow > 0)
            {
                CCListViewCell *cell = cellAtRow(nFirstRow);
                CCPoint posCell = cell->convertToWorldSpace(CCPointZero);
                CCPoint posView = this->convertToWorldSpace(CCPointZero);
                if (posCell.x >= posView.x)
                {
                    appendRowToFront(nFirstRow - 1);
                }
            }
        }
    }
    else if (CCListViewModeVertical == m_nMode && CCListViewSlideDirNone != nsliderDir)
    {
        m_nSlideDir = nsliderDir;
        m_layerPanel->setPosition(CCPointMake(m_ptPanelOffset.x, m_ptPanelOffset.y + (m_ptTouchEnd.y - m_ptTouchBegan.y)));
        if (CCListViewSlideDirUp == m_nSlideDir)
        {
            // drag up
            unsigned int nLastRow = CCRange::CCMaxRange(m_drawedRows);
            if (nLastRow < m_nNumberOfRows - 1)
            {
                CCListViewCell *cell = cellAtRow(nLastRow);
                CCPoint posCell = cell->convertToWorldSpace(CCPointZero);
                CCPoint posView = this->convertToWorldSpace(CCPointZero);
                if (posCell.y >= posView.y)
                {
                    appendRowToBack(nLastRow + 1);
                }
            }
        }
        else
        {
            // drag down
            unsigned int nFirstRow = m_drawedRows.location;
            if (nFirstRow > 0)
            {
                CCListViewCell *cell = cellAtRow(nFirstRow);
                CCPoint posCell = cell->convertToWorldSpace(CCPointZero);
                CCPoint posView = this->convertToWorldSpace(CCPointZero);
                if (posCell.y + cell->getContentSize().height <= posView.y + this->getContentSize().height)
                {
                    appendRowToFront(nFirstRow - 1);
                }
            }
        }
    }

    if (CCListViewSlideDirNone != m_nSlideDir && m_nCurrentRow != -1 && m_nCurrentRow != m_nSelectedRow)
    {
        this->unselectCellAtRow(m_nCurrentRow);
    }

    if (CCListViewSlideDirNone != m_nSlideDir && m_pListViewParent)
    {
        m_pListViewParent->setEnabled(false);
    }
}

void CCListView::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(event);

    if(m_nState != CCListViewStateTrackingTouch || !m_bIsEnabled)
    {
        m_bIsOnTouch = false;
        return;
    }

    m_fActionDuration = ND_LISTVIEW_ACTION_INTERVAL;
    clock_t timeElapse = clock() - m_timeTouchBegan;
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) && (CC_TARGET_PLATFORM != CC_PLATFORM_MAC)
    // It will take more time on mobile platform, this parameter may need to be adjusted according to the platform you use.
    timeElapse /= 200;
#endif
    if(CCListViewSlideDirLeft == m_nSlideDir || CCListViewSlideDirRight == m_nSlideDir)
    {
        float dis = m_ptTouchEnd.x - m_ptTouchBegan.x;
        float speed = dis / timeElapse;
        if (fabs(speed) > 0.1 && timeElapse < 300)
        {
            easeOutWithDistance(dis * 3);
        }
        else
        {
            if (CCListViewSlideDirLeft == m_nSlideDir && isFullFill())
            {
                // drag up
                fixLastRow();
            }
            else
            {
                // drag down
                fixFirstRow();
            }
        }
    }
    else if (CCListViewSlideDirUp == m_nSlideDir || CCListViewSlideDirDown == m_nSlideDir)
    {
        float dis = m_ptTouchEnd.y - m_ptTouchBegan.y;
        float speed = dis / timeElapse;
        if (fabs(speed) > 0.1 && timeElapse < 300)
        {
            easeOutWithDistance(dis * 3);
        }
        else
        {
            if (CCListViewSlideDirUp == m_nSlideDir && isFullFill())
            {
                // drag up
                fixLastRow();
            }
            else
            {
                // drag down
                fixFirstRow();
            }
        }
    }
    else
    {
        finishFix();
    }

    int currentRow = this->rowForTouch(touch);
    if (currentRow != -1 && isTouchInside(touch))
    {
        if (currentRow == m_nCurrentRow)
        {
            if (CCListViewSlideDirNone == m_nSlideDir)
            {
                if (m_pListViewParent == NULL || (m_pListViewParent && CCListViewSlideDirNone == m_pListViewParent->getSlideDir()))
                {
                    if (m_nSelectedRow != -1 && m_nSelectedRow != m_nCurrentRow)
                    {
                        this->unselectCellAtRow(m_nSelectedRow);
                    }
                    m_nSelectedRow = m_nCurrentRow;

                    if (!this->isMenuTouch(touch, this->cellAtRow(m_nSelectedRow)))
                    {
                        triggerDidClickCellAtRow(m_nSelectedRow);
                    }
                }
            }
            else
            {
                if (m_nSelectedRow != m_nCurrentRow)
                {
                    this->unselectCellAtRow(m_nCurrentRow);
                }
            }
        }
        else
        {
            if (-1 != m_nCurrentRow)
            {
                this->unselectCellAtRow(m_nCurrentRow);
            }
        }
    }
    else
    {
        if (-1 != m_nCurrentRow)
        {
            this->unselectCellAtRow(m_nCurrentRow);
            m_nCurrentRow = -1;
        }
    }
    m_bIsOnTouch = false;
}

bool CCListView::isMenuTouch(CCTouch *touch, CCNode *parent)
{
    if (dynamic_cast<CCMenuItem*>(parent))
    {
        CCPoint touchPoint = touch->locationInView();
        touchPoint.y = cocos2d::CCDirector::sharedDirector()->getWinSize().height - touchPoint.y;
        touchPoint = parent->convertToNodeSpace(touchPoint);
        CCRect rect = CCRectZero;
        rect.size = parent->getContentSize();
        return CCRect::CCRectContainsPoint(rect, touchPoint);
    }
    else
    {
        CCArray *pChildrens = parent->getChildren();
        if (pChildrens && pChildrens->count() > 0)
        {
            for (unsigned int i = 0; i < pChildrens->count(); i++)
            {
                CCNode *pChildren = (CCNode*)pChildrens->objectAtIndex(i);
                if (this->isMenuTouch(touch, pChildren))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void CCListView::ccTouchCancelled(CCTouch *touch, CCEvent *event)
{
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(event);

    CCAssert(m_nState == CCListViewStateTrackingTouch, "[NdListview ccTouchCancelled] -- invalid state");
    
    finishFix();
    m_bIsOnTouch = false;
}

NS_CC_EXT_END




