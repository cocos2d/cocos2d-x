#include "NdListView.h"
#include "../cocos2dx_support/LuaEngineImpl.h"

namespace NdCxControl 
{
#define ND_LISTVIEW_ACTION_INTERVAL		0.6666
/******************************************
**************Public Functions*************
*******************************************/
NdListView* NdListView::viewWithMode(NdListViewMode mode)
{
	NdListView *pRet = new NdListView();
	if (pRet && pRet->initWithMode(mode))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet)
		return NULL;
	}
}

bool NdListView::initWithMode(NdListViewMode mode)
{
	m_nMode = mode;
	m_layerPanel = CCLayer::node();
	this->addChild(m_layerPanel);

	return CCLayerColor::initWithColorWidthHeight(ccc4(255, 255, 255, 0), 0, 0);
}

NdListView::NdListView(void)
	:m_nMode(NdListViewModeVertical)
	,m_nState(NdListViewStateWatting)
	,m_nSlideDir(NdListViewSlideDirNone)
	,m_layerPanel(NULL)
	,m_nSeparatorStyle(NdListViewCellSeparatorStyleSingleLine)
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

NdListView::~NdListView(void) 
{
}

void NdListView::setDelegateName(const char* pszName)
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

void NdListView::selectCellAtRow(unsigned int nRow)
{
	NdListViewCell *cell = cellAtRow(nRow);
	if (cell)
	{
		cell->selected();
	}
}

void NdListView::unselectCellAtRow(unsigned int nRow)
{
	if (nRow == m_nSelectedRow)
	{
		m_nSelectedRow = -1;
	}
	NdListViewCell *cell = cellAtRow(nRow);
	if (cell)
	{
		cell->unselected();
	}
}

void NdListView::reload(void)
{
	m_layerPanel->removeAllChildrenWithCleanup(true);
	m_layerPanel->setPosition(CCPointZero);
	m_visibleRows = CCRangeMake(0, 0);
	m_drawedRows = CCRangeMake(0, 0);
	m_nNumberOfRows = triggerNumberOfCells();
	this->displayVisibleRows();
}

void NdListView::insertCellsAtRow(unsigned int nRow, unsigned int nCount)
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

void NdListView::deleteCellsAtRow(unsigned int nRow, unsigned int nCount)
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
			NdListViewCell *cell = this->cellAtRow(n);
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
						if (NdListViewModeHorizontal == m_nMode)
						{
							cell->setPosition(pos);
							pos.x += cell->getContentSize().width;
						}
						else if (NdListViewModeVertical == m_nMode)
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
				NdListViewCell *cell = this->cellAtRow(i);
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

void NdListView::scrollCellToFront(unsigned int nRow, bool bAnimated)
{
	if (!isFullFill())
	{
		return;
	}
	if (m_nNumberOfRows == 0)
	{
		return;
	}
	if (NdListViewStateWatting != m_nState)
	{
		this->stopActionImmediately();
	}

	if (nRow >= m_nNumberOfRows)
	{
		nRow = m_nNumberOfRows - 1;
	}

	float disX = 0;
	float disY = 0;
	m_nSlideDir = NdListViewSlideDirNone;
	if (NdListViewModeHorizontal == m_nMode)
	{
		float dis = 0;
		unsigned int nCount = 0;
		NdListViewCell *cell = NULL;
		if (nRow > m_visibleRows.location)
		{
			m_nSlideDir = NdListViewSlideDirLeft;
		}
		else
		{
			m_nSlideDir = NdListViewSlideDirRight;
		}

		while(1)
		{
			if (dis >= this->getContentSize().width || nRow + nCount >= m_nNumberOfRows)
			{
				break;
			}

			if (NdListViewSlideDirRight == m_nSlideDir)
			{
				cell = appendRowToFront(nRow + nCount);
			}
			else if (NdListViewSlideDirLeft == m_nSlideDir)
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
				CCLog("NdListView cell == NULL at line %d", __LINE__);
			}
		}

		if (NdListViewSlideDirLeft == m_nSlideDir && dis < this->getContentSize().width)
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
					CCLog("NdListView cell == NULL at line %d", __LINE__);
				}
			}
		}

		if (NdListViewSlideDirRight == m_nSlideDir)
		{
			NdListViewCell* cell = NULL;
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
						CCLog("NdListView cell == NULL at line %d", __LINE__);
					}
				}
			}
			else
			{
				CCLog("NdListView cell == NULL at line %d", __LINE__);
			}
		}
		else if (NdListViewSlideDirLeft == m_nSlideDir)
		{
			NdListViewCell* cell = NULL;
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
						CCLog("NdListView cell == NULL at line %d", __LINE__);
					}
				}
			}
			else
			{
				CCLog("NdListView cell == NULL at line %d", __LINE__);
			}
		}


		cell = cellAtRow(nRow);
		CCPoint ptCell = cell->convertToWorldSpace(CCPointZero);
		CCPoint ptView = this->convertToWorldSpace(CCPointZero);
		disX = ptView.x - ptCell.x;
	}
	else if (NdListViewModeVertical == m_nMode)
	{
		float dis = 0;
		unsigned int nCount = 0;
		NdListViewCell *cell = NULL;
		if (nRow > m_visibleRows.location)
		{
			m_nSlideDir = NdListViewSlideDirUp;
		}
		else
		{
			m_nSlideDir = NdListViewSlideDirDown;
		}

		while(1)
		{
			if (dis >= this->getContentSize().height || nRow + nCount >= m_nNumberOfRows)
			{
				break;
			}

			if (NdListViewSlideDirDown == m_nSlideDir)
			{
				cell = appendRowToFront(nRow + nCount);
			}
			else if (NdListViewSlideDirUp == m_nSlideDir)
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
				CCLog("NdListView cell == NULL at line %d", __LINE__);
			}
		}

		if (NdListViewSlideDirUp == m_nSlideDir && dis < this->getContentSize().height)
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
					CCLog("NdListView cell == NULL at line %d", __LINE__);
				}
			}
		}

		if (NdListViewSlideDirDown == m_nSlideDir)
		{
			NdListViewCell* cell = NULL;
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
						CCLog("NdListView cell == NULL at line %d", __LINE__);
					}
				}
			}
			else
			{
				CCLog("NdListView cell == NULL at line %d", __LINE__);
			}
		}
		else if (NdListViewSlideDirUp == m_nSlideDir)
		{
			NdListViewCell* cell = NULL;
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
						CCLog("NdListView cell == NULL at line %d", __LINE__);
					}
				}
			}
			else
			{
				CCLog("NdListView cell == NULL at line %d", __LINE__);
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
	m_nState = NdListViewStateScroll;

	if (bAnimated)
	{
		CCMoveBy *moveBy = CCMoveBy::actionWithDuration(m_fActionDuration, CCPointMake(disX, disY));
		CCEaseOut *ease = CCEaseOut::actionWithAction(moveBy, 3);
		CCFiniteTimeAction *actions = CCSequence::actions(ease, CCCallFunc::actionWithTarget(this, callfunc_selector(NdListView::finishScroll)), NULL);
		m_layerPanel->runAction(actions);
	}
	else
	{
		stopActionImmediately();
	}
}

void NdListView::scrollCellToBack(unsigned int nRow, bool bAnimated)
{
	if (!isFullFill())
	{
		return;
	}
	if (m_nNumberOfRows == 0)
	{
		return;
	}
	if (NdListViewStateWatting != m_nState)
	{
		this->stopActionImmediately();
	}

	if (nRow >= m_nNumberOfRows)
	{
		nRow = m_nNumberOfRows - 1;
	}

	float disX = 0;
	float disY = 0;
	m_nSlideDir = NdListViewSlideDirNone;
	if (NdListViewModeHorizontal == m_nMode)
	{
		float dis = 0;
		int nCount = 0;
		NdListViewCell *cell = NULL;
		if (nRow > CCRange::CCMaxRange(m_visibleRows))
		{
			m_nSlideDir = NdListViewSlideDirLeft;
		}
		else
		{
			m_nSlideDir = NdListViewSlideDirRight;
		}

		while(1)
		{
			if (dis >= this->getContentSize().width || (int)nRow - nCount < 0)
			{
				break;
			}

			if (NdListViewSlideDirRight == m_nSlideDir)
			{
				cell = appendRowToFront(nRow - nCount);
			}
			else if (NdListViewSlideDirLeft == m_nSlideDir)
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
				CCLog("NdListView cell == NULL at line %d", __LINE__);
			}
		}

		if (NdListViewSlideDirRight == m_nSlideDir && dis < this->getContentSize().width)
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
					CCLog("NdListView cell == NULL at line %d", __LINE__);
				}
			}
		}

		if (NdListViewSlideDirRight == m_nSlideDir)
		{
			NdListViewCell* cell = NULL;
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
						CCLog("NdListView cell == NULL at line %d", __LINE__);
					}
				}
			}
			else
			{
				CCLog("NdListView cell == NULL at line %d", __LINE__);
			}
		}
		else if (NdListViewSlideDirLeft == m_nSlideDir)
		{
			NdListViewCell* cell = NULL;
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
						CCLog("NdListView cell == NULL at line %d", __LINE__);
					}
				}
			}
			else
			{
				CCLog("NdListView cell == NULL at line %d", __LINE__);
			}
		}


		cell = cellAtRow(nRow);
		CCPoint ptCell = cell->convertToWorldSpace(CCPointZero);
		CCPoint ptView = this->convertToWorldSpace(CCPointZero);
		disX = ptView.x + this->getContentSize().width - (ptCell.x + cell->getContentSize().width);
	}
	else if (NdListViewModeVertical == m_nMode)
	{
		float dis = 0;
		int nCount = 0;
		NdListViewCell *cell = NULL;
		if (nRow > CCRange::CCMaxRange(m_visibleRows))
		{
			m_nSlideDir = NdListViewSlideDirUp;
		}
		else
		{
			m_nSlideDir = NdListViewSlideDirDown;
		}

		while(1)
		{
			if (dis >= this->getContentSize().height || (int)nRow - nCount < 0)
			{
				break;
			}

			if (NdListViewSlideDirDown == m_nSlideDir)
			{
				cell = appendRowToFront(nRow - nCount);
			}
			else if (NdListViewSlideDirUp == m_nSlideDir)
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
				CCLog("NdListView cell == NULL at line %d", __LINE__);
			}
		}

		if (NdListViewSlideDirDown == m_nSlideDir && dis < this->getContentSize().height)
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
					CCLog("NdListView cell == NULL at line %d", __LINE__);
				}
			}
		}

		if (NdListViewSlideDirDown == m_nSlideDir)
		{
			NdListViewCell* cell = NULL;
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
						CCLog("NdListView cell == NULL at line %d", __LINE__);
					}
				}
			}
			else
			{
				CCLog("NdListView cell == NULL at line %d", __LINE__);
			}
		}
		else if (NdListViewSlideDirUp == m_nSlideDir)
		{
			NdListViewCell* cell = NULL;
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
						CCLog("NdListView cell == NULL at line %d", __LINE__);
					}
				}
			}
			else
			{
				CCLog("NdListView cell == NULL at line %d", __LINE__);
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
	m_nState = NdListViewStateScroll;

	if (bAnimated)
	{
		CCMoveBy *moveBy = CCMoveBy::actionWithDuration(m_fActionDuration, CCPointMake(disX, disY));
		CCEaseOut *ease = CCEaseOut::actionWithAction(moveBy, 3);
		CCFiniteTimeAction *actions = CCSequence::actions(ease, CCCallFunc::actionWithTarget(this, callfunc_selector(NdListView::finishScroll)), NULL);
		m_layerPanel->runAction(actions);
	}
	else
	{
		stopActionImmediately();
	}
}

NdListViewSlideDir NdListView::getSlideDir(CCPoint ptTouchBegan, CCPoint ptTouchEnd)
{
	NdListViewSlideDir nSlideDir = NdListViewSlideDirNone;

	int nOffsetX = ptTouchEnd.x - ptTouchBegan.x;
	int nOffsetY = ptTouchEnd.y - ptTouchBegan.y;

	int disMin = CCDirector::sharedDirector()->getWinSize().height / 100;

	if(NdListViewModeHorizontal == m_nMode)
	{
		if(nOffsetX >= disMin)
		{
			nSlideDir = NdListViewSlideDirRight;
		}
		else if (nOffsetX <= -disMin)
		{
			nSlideDir = NdListViewSlideDirLeft;
		}
	}
	else if (NdListViewModeVertical == m_nMode)
	{
		if(nOffsetY >= disMin)
		{
			nSlideDir = NdListViewSlideDirUp;
		}
		else if (nOffsetY <= -disMin)
		{
			nSlideDir = NdListViewSlideDirDown;
		}
	}
	return nSlideDir;
}

/******************************************
**************Private Functions************
*******************************************/
int NdListView::rowForTouch(cocos2d::CCTouch *touch)
{
	CCPoint touchLocation = touch->locationInView(touch->view());
	touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);

	CCArray *pChildren = m_layerPanel->getChildren();
	if (pChildren && pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(pChildren, pObject)
		{
			CCNode* pChild = (CCNode*) pObject;
			if (pChild && pChild->getIsVisible())
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

void NdListView::finishFix(void)
{
	if(m_pListViewParent)
	{
		m_pListViewParent->setIsEnabled(true);
	}
	m_nState = NdListViewStateWatting;
	m_nSlideDir = NdListViewSlideDirNone;
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

void NdListView::finishScroll(void)
{
	finishFix();
}

void NdListView::finishEaseOut(void)
{
	bool bNeedFix = false;

	if (NdListViewModeHorizontal == m_nMode)
	{
		bool bFullFill = isFullFill();
		if (NdListViewSlideDirLeft == m_nSlideDir && bFullFill)
		{
			NdListViewCell *cell = cellAtRow(m_nNumberOfRows - 1);
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
			NdListViewCell *cell = cellAtRow(0);
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
	else if (NdListViewModeVertical == m_nMode)
	{
		bool bFullFill = this->isFullFill();
		if (NdListViewSlideDirUp == m_nSlideDir && bFullFill)
		{
			NdListViewCell *cell = cellAtRow(m_nNumberOfRows - 1);
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
			NdListViewCell *cell = cellAtRow(0);
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

bool NdListView::isTouchInside(CCTouch *touch)
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

bool NdListView::isFullFill(void)
{
	bool bRet = false;
	float length = 0;
	for (unsigned int i = m_drawedRows.location; i <= CCRange::CCMaxRange(m_drawedRows); i++)
	{
		NdListViewCell *cell = cellAtRow(i);
		if (cell)
		{
			if (NdListViewModeHorizontal == m_nMode)
			{
				length += cell->getContentSize().width;
				if (length >= this->getContentSize().width)
				{
					bRet = true;
					break;
				}
			}
			else if (NdListViewModeVertical == m_nMode)
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

NdListViewCell *NdListView::cellAtRow(unsigned int nRow)
{
	NdListViewCell *cell = (NdListViewCell*)m_layerPanel->getChildByTag(nRow);
	return cell;
}

void NdListView::stopActionImmediately(void)
{
	m_layerPanel->stopAllActions();
	if (NdListViewStateScroll == m_nState)
	{
		m_layerPanel->setPosition(m_ptDestination);
		finishScroll();
	}
}

unsigned int NdListView::triggerNumberOfCells(void)
{
	unsigned int nRow = 0;
	NdListViewProtrolData data;

	if (m_strDeletegate.size() > 0)
	{
		CCScriptEngineProtocol* scriptEngine = CCScriptEngineManager::sharedScriptEngineManager()->getScriptEngine();
		if (scriptEngine)
		{
			std::string script;
			script = m_strDeletegate + "NdListView_numberOfCells";
			scriptEngine->executeCallFuncNTDT(script.c_str(), this, "NdCxControl::NdListView", &data, "NdCxControl::NdListViewProtrolData");
			nRow = data.nNumberOfRows;
		}
	}

	if (m_pDelegate)
	{
		m_pDelegate->NdListView_numberOfCells(this, &data);
		nRow = data.nNumberOfRows;
	}
	return nRow;
}

NdListViewCell *NdListView::triggerCellForRow(unsigned int nRow)
{
	NdListViewCell *cell = NULL;
	NdListViewProtrolData data;
	data.nRow = nRow;
	data.cell = NULL;
	if (m_strDeletegate.size() > 0)
	{
		CCScriptEngineProtocol* scriptEngine = CCScriptEngineManager::sharedScriptEngineManager()->getScriptEngine();
		if (scriptEngine)
		{
			std::string script;
			script = m_strDeletegate + "NdListView_cellForRow";
			scriptEngine->executeCallFuncNTDT(script.c_str(), this, "NdCxControl::NdListView",  &data, "NdCxControl::NdListViewProtrolData");
			cell = data.cell;
		}
	}
	if (m_pDelegate)
	{
		m_pDelegate->NdListView_cellForRow(this, &data);
		cell = data.cell;
	}
	return cell;
}

void NdListView::triggerDidClickCellAtRow(unsigned int nRow)
{
	NdListViewProtrolData data;
	data.nRow = nRow;
	if (m_strDeletegate.size() > 0)
	{
		CCScriptEngineProtocol* scriptEngine = CCScriptEngineManager::sharedScriptEngineManager()->getScriptEngine();
		if (scriptEngine)
		{
			std::string script;
			script = m_strDeletegate + "NdListView_didClickCellAtRow";
			scriptEngine->executeCallFuncNTDT(script.c_str(), this, "NdCxControl::NdListView", &data, "NdCxControl::NdListViewProtrolData");
		}
	}

	if (m_pDelegate)
	{
		m_pDelegate->NdListView_didClickCellAtRow(this, &data);
	}
}

void NdListView::triggerDidScrollToRow(unsigned int nRow)
{
	NdListViewProtrolData data;
	data.nRow = nRow;
	if (m_strDeletegate.size() > 0)
	{
		CCScriptEngineProtocol* scriptEngine = CCScriptEngineManager::sharedScriptEngineManager()->getScriptEngine();
		if (scriptEngine)
		{
			std::string script;
			script = m_strDeletegate + "NdListView_didScrollToRow";
			scriptEngine->executeCallFuncNTDT(script.c_str(), this, "NdCxControl::NdListView", &data, "NdCxControl::NdListViewProtrolData");
		}
	}
	if (m_pDelegate)
	{
		m_pDelegate->NdListView_didScrollToRow(this, &data);
	}
}

void NdListView::displayVisibleRows(void)
{
	CCSize size = getContentSize();
	float posPannel, boundPannel;
	unsigned int rowCount = m_drawedRows.location;
	
	NdListViewCell *cell = cellAtRow(rowCount);

	if (m_nMode == NdListViewModeHorizontal)
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
	else if (m_nMode == NdListViewModeVertical)
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

	NdListViewCell *lastCell = NULL;
	while(1)
	{
		// row condition
		if (rowCount >= m_nNumberOfRows)
			break;

		// size condition
		if (m_nMode == NdListViewModeHorizontal)
		{
			if (posPannel >= boundPannel)
				break;
		}
		else if (m_nMode == NdListViewModeVertical)
		{
			if (posPannel <= boundPannel)
				break;
		}

		// get cell
		NdListViewCell *cell = cellAtRow(rowCount);

		if (NULL == cell)
		{
			cell = triggerCellForRow(rowCount);
			if (cell)
			{
				CCSize cellSize = cell->getContentSize();
				if (m_nMode == NdListViewModeHorizontal)
				{
					cell->setPosition(CCPointMake(posPannel, 0));
					cell->setContentSize(CCSizeMake(cellSize.width, size.height));
				}
				else if (m_nMode == NdListViewModeVertical)
				{
					cell->setPosition(CCPointMake(0, posPannel - cellSize.height));
					cell->setContentSize(CCSizeMake(size.width, cellSize.height));
				}
				m_layerPanel->addChild(cell, rowCount, rowCount);
			}
		}

		if (cell)
		{
			if (m_nMode == NdListViewModeHorizontal)
			{
				posPannel += cell->getContentSize().width;
			}
			else if (m_nMode == NdListViewModeVertical)
			{
				posPannel -= cell->getContentSize().height;
			}
			cell->setSeparatorStyle(m_nSeparatorStyle);
			lastCell = cell;
		}

		++rowCount;
	}
	m_drawedRows.length = rowCount - m_drawedRows.location;
	// 设置可视范围
	m_visibleRows = m_drawedRows;

	if (lastCell)
	{
		lastCell->setSeparatorStyle(NdListViewCellSeparatorStyleNone);
	}
}

NdListViewCell* NdListView::appendRowToBack(unsigned int nRow)
{
	if (nRow >= m_nNumberOfRows)
	{
		return NULL;
	}
	NdListViewCell *cell = cellAtRow(nRow);
	if (cell == NULL)
	{
		cell = triggerCellForRow(nRow);
		if (cell)
		{
			CCSize size = this->getContentSize();
			CCSize cellSize = cell->getContentSize();
			float pos;
			unsigned int nLastRow = CCRange::CCMaxRange(m_drawedRows);
			NdListViewCell *lastCell = cellAtRow(nLastRow);
			if (lastCell)
			{
				if (m_nMode == NdListViewModeHorizontal)
				{
					pos = lastCell->getPosition().x + lastCell->getContentSize().width;
					cell->setPosition(CCPointMake(pos, 0));
					cell->setContentSize(CCSizeMake(cellSize.width, size.height));
				}
				else if (m_nMode == NdListViewModeVertical)
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
					cell->setSeparatorStyle(NdListViewCellSeparatorStyleNone);
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
				CCLog("NdListView cell == NULL at line %d", __LINE__);
			}
		}
		else
		{
			CCLog("NdListView cell == NULL at line %d", __LINE__);
		}
	}
	return cell;
}

NdListViewCell* NdListView::appendRowToFront(unsigned int nRow)
{
	NdListViewCell *cell = cellAtRow(nRow);
	if (cell == NULL)
	{
		cell = triggerCellForRow(nRow);
		if (cell)
		{
			CCSize size = this->getContentSize();
			CCSize cellSize = cell->getContentSize();
			float pos;
			unsigned int nFirstRow = m_drawedRows.location;
			NdListViewCell *firstCell = cellAtRow(nFirstRow);
			if (firstCell)
			{
				if (m_nMode == NdListViewModeHorizontal)
				{
					pos = firstCell->getPosition().x - cell->getContentSize().width;
					cell->setPosition(CCPointMake(pos, 0));
					cell->setContentSize(CCSizeMake(cellSize.width, size.height));
				}
				else if (m_nMode == NdListViewModeVertical)
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
				CCLog("NdListView cell == NULL at line %d", __LINE__);
			}
		}
		else
		{
				CCLog("NdListView cell == NULL at line %d", __LINE__);
		}
	}
	return cell;
}
// 对齐末行
void NdListView::fixFirstRow(void)
{
	unsigned int location = m_drawedRows.location;

	NdListViewCell *cell = cellAtRow(location);
	if (cell)
	{
		float disX = 0;
		float disY = 0;
		CCPoint posCell = cell->convertToWorldSpace(CCPointZero);
		CCPoint posView = this->convertToWorldSpace(CCPointZero);
		if (NdListViewModeHorizontal == m_nMode)
		{
			float dis = posCell.x - posView.x;
			dis = -dis;

			disX = dis;
			disY = 0;
		}
		else if (NdListViewModeVertical == m_nMode)
		{
			float dis = posCell.y + cell->getContentSize().height - (posView.y + this->getContentSize().height);
			dis = -dis;

			disX = 0;
			disY = dis;
		}
		
		m_nState = NdListViewStateFix;
		CCMoveBy *moveBy = CCMoveBy::actionWithDuration(m_fActionDuration, CCPointMake(disX, disY));
		CCEaseInOut *ease = CCEaseInOut::actionWithAction(moveBy, 2);
		CCFiniteTimeAction *actions = CCSequence::actions(ease, CCCallFunc::actionWithTarget(this, callfunc_selector(NdListView::finishFix)), NULL);
		m_layerPanel->runAction(actions);
	}
	else
	{
		this->finishFix();
	}
}
// 对齐首行
void NdListView::fixLastRow(void)
{
	unsigned int nLastRow = CCRange::CCMaxRange(m_drawedRows);
	NdListViewCell *cell = cellAtRow(nLastRow);
	if (cell)
	{
		float disX = 0;
		float disY = 0;
		CCPoint posCell = cell->convertToWorldSpace(CCPointZero);
		CCPoint posView = this->convertToWorldSpace(CCPointZero);
		if (NdListViewModeHorizontal == m_nMode)
		{
			float dis = posCell.x + cell->getContentSize().width - (posView.x + this->getContentSize().width);
			dis = -dis;
			
			disX = dis;
			disY = 0;
		}
		else if (NdListViewModeVertical == m_nMode)
		{
			float dis = posCell.y - posView.y;
			dis = -dis;

			disX = 0;
			disY = dis;
		}

		m_nState = NdListViewStateFix;
		CCMoveBy *moveBy = CCMoveBy::actionWithDuration(m_fActionDuration, CCPointMake(disX, disY));
		CCEaseInOut *ease = CCEaseInOut::actionWithAction(moveBy, 2);
		CCFiniteTimeAction *actions = CCSequence::actions(ease, CCCallFunc::actionWithTarget(this, callfunc_selector(NdListView::finishFix)), NULL);
		m_layerPanel->runAction(actions);
	}
	else
	{
		finishFix();
	}
}
// 手势滑动界面，减速效果
void NdListView::easeOutWithDistance(float dis)
{
	float disX = 0;
	float disY = 0;

	if (NdListViewModeHorizontal == m_nMode)
	{
		if (NdListViewSlideDirLeft == m_nSlideDir)
		{
			// drag Left
			while(1)
			{
				unsigned int nLastRow = CCRange::CCMaxRange(m_drawedRows);
				NdListViewCell *cell = cellAtRow(nLastRow);
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
				NdListViewCell *cell = cellAtRow(nFirstRow);
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
	else if (NdListViewModeVertical == m_nMode)
	{
		if (NdListViewSlideDirUp == m_nSlideDir)
		{
			// drag up
			while(1)
			{
				unsigned int nLastRow = CCRange::CCMaxRange(m_drawedRows);
				NdListViewCell *cell = cellAtRow(nLastRow);
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
				NdListViewCell *cell = cellAtRow(nFirstRow);
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

	m_nState = NdListViewStateEaseOut;
	CCMoveBy *moveBy = CCMoveBy::actionWithDuration(m_fActionDuration, CCPointMake(disX, disY));
	CCEaseOut *ease = CCEaseOut::actionWithAction(moveBy, 3);
	CCFiniteTimeAction *actions = CCSequence::actions(ease, CCCallFunc::actionWithTarget(this, callfunc_selector(NdListView::finishEaseOut)), NULL);
	m_layerPanel->runAction(actions);
}

void NdListView::clearUnvisibleRows(void)
{
	CCRange oldRange = m_drawedRows;
	for (unsigned int i = oldRange.location; i < oldRange.location + oldRange.length; i++)
	{
		NdListViewCell *cell = cellAtRow(i);
		if (cell)
		{
			CCPoint posCell = cell->convertToWorldSpace(CCPointZero);
			CCPoint posView = this->convertToWorldSpace(CCPointZero);
			if (NdListViewModeHorizontal == m_nMode)
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
			else if (NdListViewModeVertical == m_nMode)
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
		NdListViewCell *cell = cellAtRow(i);
		if (cell)
		{
			CCPoint posCell = cell->convertToWorldSpace(CCPointZero);
			CCPoint posView = this->convertToWorldSpace(CCPointZero);
			if (NdListViewModeHorizontal == m_nMode)
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
			else if (NdListViewModeVertical == m_nMode)
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
void NdListView::registerWithTouchDispatcher()
{
	if (m_pListViewParent)
	{
		CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, kCCMenuTouchPriority - 1, false);
	}
	else
	{
		CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, kCCMenuTouchPriority - 2, false);
	}
}

void NdListView::onEnter(void)
{
	if (0 == m_nNumberOfRows)
	{
		m_layerPanel->setPosition(CCPointZero);
		m_layerPanel->setContentSize(this->getContentSize());
		// get number of rows
		m_nNumberOfRows = triggerNumberOfCells();
		displayVisibleRows();
	}
	
	CCLayerColor::onEnter();
}

void NdListView::onExit(void)
{
	CCLayerColor::onExit();
}

void NdListView::visit(void)
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

bool NdListView::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	 CC_UNUSED_PARAM(event);

	if (!isTouchInside(touch) || !getIsVisible() || !m_bIsEnabled)
	{
		return false;
	}

	if (m_pListViewParent && NdListViewSlideDirNone != m_pListViewParent->getSlideDir())
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

	CCPoint touchPoint = touch->locationInView(touch->view());

	m_ptTouchBegan = m_ptTouchEnd = CCDirector::sharedDirector()->convertToGL(touchPoint);
	m_ptPanelOffset = m_layerPanel->getPosition();

	m_timeTouchBegan = clock();

	m_nCurrentRow = this->rowForTouch(touch);
	if (m_nCurrentRow != -1)
	{	
		if (NdListViewStateWatting != m_nState)
		{
			stopActionImmediately();
		}

		m_nState = NdListViewStateTrackingTouch;
		if (NdListViewSlideDirNone == m_nSlideDir)
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

void NdListView::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	CC_UNUSED_PARAM(event);
	if (NdListViewStateTrackingTouch != m_nState || !isTouchInside(touch) || !m_bIsEnabled)
	{
		return;
	}

	CCPoint touchPoint = touch->locationInView(touch->view());
	m_ptTouchEnd = CCDirector::sharedDirector()->convertToGL(touchPoint);         	


	NdListViewSlideDir nsliderDir = NdListViewSlideDirNone;
	if (m_pListViewParent && NdListViewSlideDirNone != m_pListViewParent->getSlideDir(m_ptTouchBegan, m_ptTouchEnd))
	{
		return;
	}
	else
	{
		nsliderDir = getSlideDir(m_ptTouchBegan, m_ptTouchEnd);
	}
	

	if(NdListViewModeHorizontal == m_nMode && NdListViewSlideDirNone != nsliderDir)
	{
		m_nSlideDir = nsliderDir;
		m_layerPanel->setPosition(CCPointMake(m_ptPanelOffset.x + (m_ptTouchEnd.x - m_ptTouchBegan.x),m_ptPanelOffset.y));
		if (NdListViewSlideDirLeft == m_nSlideDir)
		{
			// drag left
			unsigned int nLastRow = CCRange::CCMaxRange(m_drawedRows);
			if (nLastRow < m_nNumberOfRows - 1)
			{
				NdListViewCell *cell = cellAtRow(nLastRow);
				CCPoint posCell = cell->convertToWorldSpace(CCPointZero);
				CCPoint posView = this->convertToWorldSpace(CCPointZero);
				if (posCell.x + cell->getContentSize().width <= posView.x + this->getContentSize().width)
				{
					appendRowToBack(nLastRow + 1);
				}
			}
		}
		else
		{
			// drag right
			unsigned int nFirstRow = m_drawedRows.location;
			if (nFirstRow > 0)
			{
				NdListViewCell *cell = cellAtRow(nFirstRow);
				CCPoint posCell = cell->convertToWorldSpace(CCPointZero);
				CCPoint posView = this->convertToWorldSpace(CCPointZero);
				if (posCell.x >= posView.x)
				{
					appendRowToFront(nFirstRow - 1);
				}
			}
		}
	}
	else if (NdListViewModeVertical == m_nMode && NdListViewSlideDirNone != nsliderDir)
	{
		m_nSlideDir = nsliderDir;
		m_layerPanel->setPosition(CCPointMake(m_ptPanelOffset.x, m_ptPanelOffset.y + (m_ptTouchEnd.y - m_ptTouchBegan.y)));
		if (NdListViewSlideDirUp == m_nSlideDir)
		{
			// drag up
			unsigned int nLastRow = CCRange::CCMaxRange(m_drawedRows);
			if (nLastRow < m_nNumberOfRows - 1)
			{
				NdListViewCell *cell = cellAtRow(nLastRow);
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
				NdListViewCell *cell = cellAtRow(nFirstRow);
				CCPoint posCell = cell->convertToWorldSpace(CCPointZero);
				CCPoint posView = this->convertToWorldSpace(CCPointZero);
				if (posCell.y + cell->getContentSize().height <= posView.y + this->getContentSize().height)
				{
					appendRowToFront(nFirstRow - 1);
				}
			}
		}
	}

	if (NdListViewSlideDirNone != m_nSlideDir && m_nCurrentRow != -1 && m_nCurrentRow != m_nSelectedRow)
	{
		this->unselectCellAtRow(m_nCurrentRow);
	}

	if (NdListViewSlideDirNone != m_nSlideDir && m_pListViewParent)
	{
		m_pListViewParent->setIsEnabled(false);
	}
}

void NdListView::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CC_UNUSED_PARAM(touch);
	CC_UNUSED_PARAM(event);

	if(m_nState != NdListViewStateTrackingTouch || !m_bIsEnabled)
	{
		m_bIsOnTouch = false;
		return;
	}

	m_fActionDuration = ND_LISTVIEW_ACTION_INTERVAL;
	clock_t timeElapse = clock() - m_timeTouchBegan;
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32 && CC_TARGET_PLATFORM != CC_PLATFORM_MAC
	// 手机平台用时较长，此系数可能需要根据不同平台做相应调整
	timeElapse /= 200;
#endif
	if(NdListViewSlideDirLeft == m_nSlideDir || NdListViewSlideDirRight == m_nSlideDir)
	{
		float dis = m_ptTouchEnd.x - m_ptTouchBegan.x;
		float speed = dis / timeElapse;
		if (fabs(speed) > 0.1 && timeElapse < 300)
		{
			easeOutWithDistance(dis * 3);
		}
		else
		{
			if (NdListViewSlideDirLeft == m_nSlideDir && isFullFill())
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
	else if (NdListViewSlideDirUp == m_nSlideDir || NdListViewSlideDirDown == m_nSlideDir)
	{
		float dis = m_ptTouchEnd.y - m_ptTouchBegan.y;
		float speed = dis / timeElapse;
		if (fabs(speed) > 0.1 && timeElapse < 300)
		{
			easeOutWithDistance(dis * 3);
		}
		else
		{
			if (NdListViewSlideDirUp == m_nSlideDir && isFullFill())
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
			if (NdListViewSlideDirNone == m_nSlideDir)
			{
				if (m_pListViewParent == NULL || (m_pListViewParent && NdListViewSlideDirNone == m_pListViewParent->getSlideDir()))
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

bool NdListView::isMenuTouch(CCTouch *touch, CCNode *parent)
{
	if (parent->getClassType() == CCMenuItem_classID)
	{
		CCPoint touchPoint = touch->locationInView(touch->view());
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
			for (int i = 0; i < pChildrens->count(); i++)
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

void NdListView::ccTouchCancelled(CCTouch *touch, CCEvent *event)
{
	CC_UNUSED_PARAM(touch);
	CC_UNUSED_PARAM(event);

	CCAssert(m_nState == NdListViewStateTrackingTouch, "[NdListview ccTouchCancelled] -- invalid state");
	
	finishFix();
	m_bIsOnTouch = false;
}

} // end of namespace NdCxControl




