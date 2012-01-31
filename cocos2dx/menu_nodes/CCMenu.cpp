/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada

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
#include "CCMenu.h"
#include "CCDirector.h"
#include "CCApplication.h"
#include "CCPointExtension.h"
#include "CCTouchDispatcher.h"
#include "CCTouch.h"
#include "CCStdC.h"

#include <vector>
#include <stdarg.h>

using namespace std;

namespace cocos2d{

	enum 
	{
		kDefaultPadding =  5,
	};

	//
	//CCMenu
	//

        CCMenu* CCMenu::node()
        {
            return menuWithItem(NULL);
        }

	CCMenu * CCMenu::menuWithItems(CCMenuItem* item, ...)
	{
		va_list args;
		va_start(args,item);
		CCMenu *pRet = new CCMenu();
		if (pRet && pRet->initWithItems(item, args))
		{
			pRet->autorelease();
			va_end(args);
			return pRet;
		}
		va_end(args);
		CC_SAFE_DELETE(pRet)
		return NULL;
	}

	CCMenu* CCMenu::menuWithItem(CCMenuItem* item)
	{
		return menuWithItems(item, NULL);
	}

	bool CCMenu::initWithItems(CCMenuItem* item, va_list args)
	{
		if (CCLayer::init())
		{
			this->m_bIsTouchEnabled = true;

			// menu in the center of the screen
			CCSize s = CCDirector::sharedDirector()->getWinSize();

			this->m_bIsRelativeAnchorPoint = false;
			setAnchorPoint(ccp(0.5f, 0.5f));
			this->setContentSize(s);

			// XXX: in v0.7, winSize should return the visible size
			// XXX: so the bar calculation should be done there
			CCRect r;
            CCApplication::sharedApplication().statusBarFrame(&r);
			ccDeviceOrientation orientation = CCDirector::sharedDirector()->getDeviceOrientation();
			if (orientation == CCDeviceOrientationLandscapeLeft || orientation == CCDeviceOrientationLandscapeRight)
			{
				s.height -= r.size.width;
			}
			else
			{
				s.height -= r.size.height;
			}
			setPosition(ccp(s.width/2, s.height/2));

			int z=0;

			if (item)
			{
				this->addChild(item, z);
				CCMenuItem *i = va_arg(args, CCMenuItem*);
				while (i)
				{
					z++;
					this->addChild(i, z);
					i = va_arg(args, CCMenuItem*);
				}
			}
			//	[self alignItemsVertically];

			m_pSelectedItem = NULL;
			m_eState = kCCMenuStateWaiting;
			return true;
		}

		return false;
	}

	/*
	* override add:
	*/
	void CCMenu::addChild(CCNode * child, int zOrder)
	{
		CCLayer::addChild(child, zOrder);
	}

	void CCMenu::addChild(CCNode * child, int zOrder, int tag)
	{
		// we can not use RTTI, so we do not known the type of object
		/*CCAssert( dynamic_cast<CCMenuItem*>(child) != NULL, L"Menu only supports MenuItem objects as children");*/
		CCLayer::addChild(child, zOrder, tag);
	}

    void CCMenu::onExit()
    {
        if (m_eState == kCCMenuStateTrackingTouch)
        {
            m_pSelectedItem->unselected();
            m_eState = kCCMenuStateWaiting;
            m_pSelectedItem = NULL;
        }

        CCLayer::onExit();
    }

	//Menu - Events
	void CCMenu::registerWithTouchDispatcher()
	{
		CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, kCCMenuTouchPriority, true);
	}

	bool CCMenu::ccTouchBegan(CCTouch* touch, CCEvent* event)
	{
        CC_UNUSED_PARAM(event);
		if (m_eState != kCCMenuStateWaiting || ! m_bIsVisible)
		{
			return false;
		}

		for (CCNode *c = this->m_pParent; c != NULL; c = c->getParent())
		{
			if (c->getIsVisible() == false)
			{
				return false;
			}
		}

		m_pSelectedItem = this->itemForTouch(touch);
		if (m_pSelectedItem)
		{
			m_eState = kCCMenuStateTrackingTouch;
			m_pSelectedItem->selected();
			return true;
		}
		return false;
	}

	void CCMenu::ccTouchEnded(CCTouch *touch, CCEvent* event)
	{
        CC_UNUSED_PARAM(touch);
        CC_UNUSED_PARAM(event);
		CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchEnded] -- invalid state");
		if (m_pSelectedItem)
		{
			m_pSelectedItem->unselected();
			m_pSelectedItem->activate();
		}
		m_eState = kCCMenuStateWaiting;
	}

	void CCMenu::ccTouchCancelled(CCTouch *touch, CCEvent* event)
	{
        CC_UNUSED_PARAM(touch);
        CC_UNUSED_PARAM(event);
		CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchCancelled] -- invalid state");
		if (m_pSelectedItem)
		{
			m_pSelectedItem->unselected();
		}
		m_eState = kCCMenuStateWaiting;
	}

	void CCMenu::ccTouchMoved(CCTouch* touch, CCEvent* event)
	{
        CC_UNUSED_PARAM(event);
		CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchMoved] -- invalid state");
		CCMenuItem *currentItem = this->itemForTouch(touch);
		if (currentItem != m_pSelectedItem) 
		{
			if (m_pSelectedItem)
			{
				m_pSelectedItem->unselected();
			}
			m_pSelectedItem = currentItem;
			if (m_pSelectedItem)
			{
				m_pSelectedItem->selected();
			}
		}
	}

	//Menu - Alignment
	void CCMenu::alignItemsVertically()
	{
		this->alignItemsVerticallyWithPadding(kDefaultPadding);
	}

	void CCMenu::alignItemsVerticallyWithPadding(float padding)
	{
		float height = -padding;
		if (m_pChildren && m_pChildren->count() > 0)
		{
            CCObject* pObject = NULL;
            CCARRAY_FOREACH(m_pChildren, pObject)
            {
                CCNode* pChild = dynamic_cast<CCNode*>(pObject);
                if (pChild)
                {
                    height += pChild->getContentSize().height * pChild->getScaleY() + padding;
                }
            }
		}

		float y = height / 2.0f;
		if (m_pChildren && m_pChildren->count() > 0)
		{
            CCObject* pObject = NULL;
            CCARRAY_FOREACH(m_pChildren, pObject)
            {
                CCNode* pChild = dynamic_cast<CCNode*>(pObject);
                if (pChild)
                {
                    pChild->setPosition(ccp(0, y - pChild->getContentSize().height * pChild->getScaleY() / 2.0f));
                    y -= pChild->getContentSize().height * pChild->getScaleY() + padding;
                }
            }
		}
	}

	void CCMenu::alignItemsHorizontally(void)
	{
		this->alignItemsHorizontallyWithPadding(kDefaultPadding);
	}

	void CCMenu::alignItemsHorizontallyWithPadding(float padding)
	{

		float width = -padding;
		if (m_pChildren && m_pChildren->count() > 0)
		{
            CCObject* pObject = NULL;
            CCARRAY_FOREACH(m_pChildren, pObject)
            {
                CCNode* pChild = dynamic_cast<CCNode*>(pObject);
                if (pChild)
                {
                    width += pChild->getContentSize().width * pChild->getScaleX() + padding;
                }
            }
		}

		float x = -width / 2.0f;
		if (m_pChildren && m_pChildren->count() > 0)
		{
            CCObject* pObject = NULL;
            CCARRAY_FOREACH(m_pChildren, pObject)
            {
                CCNode* pChild = dynamic_cast<CCNode*>(pObject);
                if (pChild)
                {
                    pChild->setPosition(ccp(x + pChild->getContentSize().width * pChild->getScaleX() / 2.0f, 0));
     				x += pChild->getContentSize().width * pChild->getScaleX() + padding;
                }
            }
		}
	}

	void CCMenu::alignItemsInColumns(unsigned int columns, ...)
	{
		va_list args;
		va_start(args, columns);

		this->alignItemsInColumns(columns, args);

		va_end(args);
	}

	void CCMenu::alignItemsInColumns(unsigned int columns, va_list args)
	{
		vector<unsigned int> rows;
		while (columns)
		{
			rows.push_back(columns);
			columns = va_arg(args, unsigned int);
		}

		int height = -5;
		unsigned int row = 0;
		unsigned int rowHeight = 0;
		unsigned int columnsOccupied = 0;
		unsigned int rowColumns;

		if (m_pChildren && m_pChildren->count() > 0)
		{
            CCObject* pObject = NULL;
            CCARRAY_FOREACH(m_pChildren, pObject)
            {
                CCNode* pChild = dynamic_cast<CCNode*>(pObject);
                if (pChild)
                {
                    CCAssert(row < rows.size(), "");

				    rowColumns = rows[row];
				    // can not have zero columns on a row
				    CCAssert(rowColumns, "");

				    float tmp = pChild->getContentSize().height;
				    rowHeight = (unsigned int)((rowHeight >= tmp || isnan(tmp)) ? rowHeight : tmp);

				    ++columnsOccupied;
				    if (columnsOccupied >= rowColumns)
				    {
					    height += rowHeight + 5;

					    columnsOccupied = 0;
					    rowHeight = 0;
					    ++row;
				    }
                }
            }
		}	

		// check if too many rows/columns for available menu items
		CCAssert(! columnsOccupied, "");

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		row = 0;
		rowHeight = 0;
		rowColumns = 0;
		float w = 0.0;
		float x = 0.0;
		float y = (float)(height / 2);

		if (m_pChildren && m_pChildren->count() > 0)
		{
            CCObject* pObject = NULL;
            CCARRAY_FOREACH(m_pChildren, pObject)
            {
                CCNode* pChild = dynamic_cast<CCNode*>(pObject);
                if (pChild)
                {
				    if (rowColumns == 0)
				    {
					    rowColumns = rows[row];
					    w = winSize.width / (1 + rowColumns);
					    x = w;
				    }

				    float tmp = pChild->getContentSize().height;
				    rowHeight = (unsigned int)((rowHeight >= tmp || isnan(tmp)) ? rowHeight : tmp);

				    pChild->setPosition(ccp(x - winSize.width / 2,
					                       y - pChild->getContentSize().height / 2));

				    x += w;
				    ++columnsOccupied;

				    if (columnsOccupied >= rowColumns)
				    {
					    y -= rowHeight + 5;

					    columnsOccupied = 0;
					    rowColumns = 0;
					    rowHeight = 0;
					    ++row;
				    }
                }
            }
		}	
	}

	void CCMenu::alignItemsInRows(unsigned int rows, ...)
	{
		va_list args;
		va_start(args, rows);

		this->alignItemsInRows(rows, args);

		va_end(args);
	}

	void CCMenu::alignItemsInRows(unsigned int rows, va_list args)
	{
		vector<unsigned int> columns;
		while (rows)
		{
			columns.push_back(rows);
			rows = va_arg(args, unsigned int);
		}

		vector<unsigned int> columnWidths;
		vector<unsigned int> columnHeights;

		int width = -10;
		int columnHeight = -5;
		unsigned int column = 0;
		unsigned int columnWidth = 0;
		unsigned int rowsOccupied = 0;
		unsigned int columnRows;

		if (m_pChildren && m_pChildren->count() > 0)
		{
            CCObject* pObject = NULL;
            CCARRAY_FOREACH(m_pChildren, pObject)
            {
                CCNode* pChild = dynamic_cast<CCNode*>(pObject);
                if (pChild)
                {
                    // check if too many menu items for the amount of rows/columns
				    CCAssert(column < columns.size(), "");

				    columnRows = columns[column];
				    // can't have zero rows on a column
				    CCAssert(columnRows, "");

				    // columnWidth = fmaxf(columnWidth, [item contentSize].width);
				    float tmp = pChild->getContentSize().width;
				    columnWidth = (unsigned int)((columnWidth >= tmp || isnan(tmp)) ? columnWidth : tmp);

				    columnHeight += (int)(pChild->getContentSize().height + 5);
				    ++rowsOccupied;

				    if (rowsOccupied >= columnRows)
				    {
					    columnWidths.push_back(columnWidth);
					    columnHeights.push_back(columnHeight);
					    width += columnWidth + 10;

					    rowsOccupied = 0;
					    columnWidth = 0;
					    columnHeight = -5;
					    ++column;
				    }
                }
            }
		}

		// check if too many rows/columns for available menu items.
		CCAssert(! rowsOccupied, "");

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		column = 0;
		columnWidth = 0;
		columnRows = 0;
		float x = (float)(-width / 2);
		float y = 0.0;

        if (m_pChildren && m_pChildren->count() > 0)
		{
            CCObject* pObject = NULL;
            CCARRAY_FOREACH(m_pChildren, pObject)
            {
                CCNode* pChild = dynamic_cast<CCNode*>(pObject);
                if (pChild)
                {
                    if (columnRows == 0)
				    {
					    columnRows = columns[column];
					    y = (float) columnHeights[column];
				    }

				    // columnWidth = fmaxf(columnWidth, [item contentSize].width);
				    float tmp = pChild->getContentSize().width;
				    columnWidth = (unsigned int)((columnWidth >= tmp || isnan(tmp)) ? columnWidth : tmp);

				    pChild->setPosition(ccp(x + columnWidths[column] / 2,
					                       y - winSize.height / 2));

				    y -= pChild->getContentSize().height + 10;
				    ++rowsOccupied;

				    if (rowsOccupied >= columnRows)
				    {
					    x += columnWidth + 5;
					    rowsOccupied = 0;
					    columnRows = 0;
					    columnWidth = 0;
					    ++column;
				    }
                }
            }
		}
	}

	// Opacity Protocol

	/** Override synthesized setOpacity to recurse items */
	void CCMenu::setOpacity(GLubyte var)
	{
		m_cOpacity = var;

		if (m_pChildren && m_pChildren->count() > 0)
		{
            CCObject* pObject = NULL;
            CCARRAY_FOREACH(m_pChildren, pObject)
            {
                CCNode* pChild = dynamic_cast<CCNode*>(pObject);
                if (pChild)
                {
                    CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(pChild);
				    if (pRGBAProtocol)
				    {
					    pRGBAProtocol->setOpacity(m_cOpacity);
				    }
                }
            }
		}
	}

	GLubyte CCMenu::getOpacity(void)
	{
		return m_cOpacity;
	}

	void CCMenu::setColor(const ccColor3B& var)
	{
		m_tColor = var;

		if (m_pChildren && m_pChildren->count() > 0)
		{
            CCObject* pObject = NULL;
            CCARRAY_FOREACH(m_pChildren, pObject)
            {
                CCNode* pChild = dynamic_cast<CCNode*>(pObject);
                if (pChild)
                {
                    CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(pChild);
                    if (pRGBAProtocol)
                    {
                    	pRGBAProtocol->setColor(m_tColor);
                    }
                }
            }
		}
	}

	const ccColor3B& CCMenu::getColor(void)
	{
		return m_tColor;
	}

	CCMenuItem* CCMenu::itemForTouch(CCTouch *touch)
	{
		CCPoint touchLocation = touch->locationInView(touch->view());
		touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);

        if (m_pChildren && m_pChildren->count() > 0)
		{
            CCObject* pObject = NULL;
            CCARRAY_FOREACH(m_pChildren, pObject)
            {
                CCNode* pChild = dynamic_cast<CCNode*>(pObject);
                if (pChild && pChild->getIsVisible() && ((CCMenuItem*)pChild)->getIsEnabled())
                {
                    CCPoint local = pChild->convertToNodeSpace(touchLocation);
					CCRect r = ((CCMenuItem*)pChild)->rect();
					r.origin = CCPointZero;

					if (CCRect::CCRectContainsPoint(r, local))
					{
						return (CCMenuItem*)pChild;
					}
                }
            }
			
		}

		return NULL;
	}

}
