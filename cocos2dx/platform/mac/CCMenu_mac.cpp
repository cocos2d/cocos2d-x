/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#include "CCXApplication.h"
#include "CGPointExtension.h"
#include "CCTouchDispatcher.h"
#include "CCTouch.h"
#include "platform/CCXMath.h"

#include <vector>
#include <float.h>
using namespace std;

namespace cocos2d{

	enum 
	{
		kDefaultPadding =  5,
	};

	//
	//CCMenu
	//
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
		CCX_SAFE_DELETE(pRet)
		return NULL;
	}

	bool CCMenu::initWithItems(CCMenuItem* item, va_list args)
	{
		if (CCLayer::init())
		{
			this->m_bIsMouseEnabled = true;

			// menu in the center of the screen
			CGSize s = CCDirector::sharedDirector()->getWinSize();

			this->m_bIsRelativeAnchorPoint = false;
			m_tAnchorPoint = ccp(0.5f, 0.5f);
			this->setContentSize(s);

			// XXX: in v0.7, winSize should return the visible size
			// XXX: so the bar calculation should be done there
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
	CCNode * CCMenu::addChild(CCNode * child, int zOrder)
	{
		return CCLayer::addChild(child, zOrder);
	}

	CCNode * CCMenu::addChild(CCNode * child, int zOrder, int tag)
	{
		// we can not use RTTI, so we do not known the type of object
		/*NSAssert( dynamic_cast<CCMenuItem*>(child) != NULL, L"Menu only supports MenuItem objects as children");*/
		return CCLayer::addChild(child, zOrder, tag);
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

    void CCMenu::registerWithTouchDispatcher()
    {
        CCLOG("cocos2d: CCMenu: unsupported");
    }

    CCMenuItem* CCMenu::itemForTouch(CCTouch * touch)
    {
        CCLOG("cocos2d: CCMenu: unsupported");
        return NULL;
    }

    bool CCMenu::ccTouchBegan(CCTouch* touch, UIEvent* event)
    {
        CCLOG("cocos2d: CCMenu: unsupported");
        return false;
    }

    void CCMenu::ccTouchEnded(CCTouch* touch, UIEvent* event)
    {
        CCLOG("cocos2d: CCMenu: unsupported");
    }

    void CCMenu::ccTouchCancelled(CCTouch *touch, UIEvent* event)
    {
        CCLOG("cocos2d: CCMenu: unsupported");
    }

    void CCMenu::ccTouchMoved(CCTouch* touch, UIEvent* event)
    {
        CCLOG("cocos2d: CCMenu: unsupported");
    }

	//Menu - Events
    int CCMenu::mouseDelegatePriority()
    {
        return -1;/** @todo upto-0.99.5  use NSIntegerMin+1 instead*/
    }

    CCMenuItem* CCMenu::itemForMouseEvent(NSEvent * pEvent)
    {
        CGPoint touchLocation = CCDirector::sharedDirector()->convertEventToGL(pEvent);

        if (m_pChildren && m_pChildren->count() > 0)
        {
            NSMutableArray<CCNode*>::NSMutableArrayIterator it;
            for (it = m_pChildren->begin(); it != m_pChildren->end(); ++it)
            {
                if (! *it)
                {
                    break;
                }

                if ((*it)->getIsVisible() && ((CCMenuItem*)(*it))->getIsEnabled())
                {
                    CGPoint local = (*it)->convertToNodeSpace(touchLocation);

                    CGRect r = ((CCMenuItem*)(*it))->rect();
                    r.origin = CGPointZero;

                    if (CGRect::CGRectContainsPoint(r, local))
                    {
                        return (CCMenuItem*)(*it);
                    }
                }
            }
        }

        return NULL;
    }

    bool CCMenu::ccMouseUp(NSEvent * pEvent)
    {
        if (m_pSelectedItem)
        {
            m_pSelectedItem->unselected();
            m_pSelectedItem->activate();

            m_eState = kCCMenuStateWaiting;
            return true;
        }
        
        return false;
    }

    bool CCMenu::ccMouseDown(NSEvent * pEvent)
    {
        if (! getIsVisible())
        {
            return false;
        }
        
        m_pSelectedItem = itemForMouseEvent(pEvent);
        m_pSelectedItem->selected();

        if (m_pSelectedItem)
        {
            m_eState = kCCMenuStateTrackingTouch;
            return true;
        }
        
        return false;
    }

    bool CCMenu::ccMouseDragged(NSEvent * pEvent)
    {
        CCMenuItem* currentItem = itemForMouseEvent(pEvent);

        if (currentItem && currentItem != m_pSelectedItem)
        {
            if (m_pSelectedItem)
            {
                m_pSelectedItem->unselected();
            }

            m_pSelectedItem = currentItem;
            m_pSelectedItem->selected();
        }
        
        if (currentItem && m_eState == kCCMenuStateTrackingTouch)
        {
            return true;
        }
        
        return false;
    }

	void CCMenu::destroy(void)
	{
		release();
	}

	void CCMenu::keep(void)
	{
		retain();
	}

	//Menu - Alignment
	void CCMenu::alignItemsVertically()
	{
		return this->alignItemsVerticallyWithPadding(kDefaultPadding);
	}

	void CCMenu::alignItemsVerticallyWithPadding(float padding)
	{
		float height = -padding;
		if (m_pChildren && m_pChildren->count() > 0)
		{
			NSMutableArray<CCNode*>::NSMutableArrayIterator it;
			for (it = m_pChildren->begin(); it != m_pChildren->end(); ++it)
			{
                if (!(*it))
                {
                    break;
                }
                
				height += (*it)->getContentSize().height * (*it)->getScaleY() + padding;
			}
		}

		float y = height / 2.0f;
		if (m_pChildren && m_pChildren->count() > 0)
		{
			NSMutableArray<CCNode*>::NSMutableArrayIterator it;
			for (it = m_pChildren->begin(); it != m_pChildren->end(); ++it)
			{
                if (!(*it))
                {
                    break;
                }
                
				(*it)->setPosition(ccp(0, y - (*it)->getContentSize().height * (*it)->getScaleY() / 2.0f));
				y -= (*it)->getContentSize().height * (*it)->getScaleY() + padding;
			}
		}
	}

	void CCMenu::alignItemsHorizontally(void)
	{
		return this->alignItemsHorizontallyWithPadding(kDefaultPadding);
	}

	void CCMenu::alignItemsHorizontallyWithPadding(float padding)
	{

		float width = -padding;
		if (m_pChildren && m_pChildren->count() > 0)
		{
            NSMutableArray<CCNode*>::NSMutableArrayIterator it;
			for (it = m_pChildren->begin(); it != m_pChildren->end(); ++it)
			{
                if (!(*it))
                {
                    break;
                }

				width += (*it)->getContentSize().width * (*it)->getScaleX() + padding;
			}
		}

		float x = -width / 2.0f;
		if (m_pChildren && m_pChildren->count() > 0)
		{
            NSMutableArray<CCNode*>::NSMutableArrayIterator it;
			for (it = m_pChildren->begin(); it != m_pChildren->end(); ++it)
			{
                if (!(*it))
                {
                    break;
                }

				(*it)->setPosition(ccp(x + (*it)->getContentSize().width * (*it)->getScaleX() / 2.0f, 0));
				x += (*it)->getContentSize().width * (*it)->getScaleX() + padding;
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
			NSMutableArray<CCNode*>::NSMutableArrayIterator it;
			for (it = m_pChildren->begin(); it != m_pChildren->end(); ++it)
			{
				// if it has no value, break
				if (! *it)
				{
					break;
				}

                assert(row < rows.size());

				rowColumns = rows[row];
				// can not have zero columns on a row
				assert(rowColumns);

				float tmp = (*it)->getContentSize().height;
				rowHeight = (unsigned int)((rowHeight >= tmp || CCXMath::isnanCocos2d(tmp)) ? rowHeight : tmp);

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

		// check if too many rows/columns for available menu items
		assert(! columnsOccupied);

		CGSize winSize = CCDirector::sharedDirector()->getWinSize();

		row = 0;
		rowHeight = 0;
		rowColumns = 0;
		float w;
		float x;
		float y = (float)(height / 2);

		if (m_pChildren && m_pChildren->count() > 0)
		{
			NSMutableArray<CCNode*>::NSMutableArrayIterator it;
			for (it = m_pChildren->begin(); it != m_pChildren->end(); ++it)
			{
				if (! *it)
				{
					break;
				}

				if (rowColumns == 0)
				{
					rowColumns = rows[row];
					w = winSize.width / (1 + rowColumns);
					x = w;
				}

				float tmp = (*it)->getContentSize().height;
				rowHeight = (unsigned int)((rowHeight >= tmp || CCXMath::isnanCocos2d(tmp)) ? rowHeight : tmp);

				(*it)->setPosition(ccp(x - winSize.width / 2,
					                   y - (*it)->getContentSize().height / 2));

				x += w + 10;
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

	void CCMenu::alignItemsInRows(unsigned int rows, ...)
	{
		va_list args;
		va_start(args, rows);

		this->alignItemsInColumns(rows, args);

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
			NSMutableArray<CCNode*>::NSMutableArrayIterator it;
			for (it = m_pChildren->begin(); it != m_pChildren->end(); ++it)
			{
				if (! *it)
				{
					break;
				}

				// check if too many menu items for the amount of rows/columns
				assert(column < columns.size());

				columnRows = columns[column];
				// can't have zero rows on a column
				assert(columnRows);

				// columnWidth = fmaxf(columnWidth, [item contentSize].width);
				float tmp = (*it)->getContentSize().width;
				columnWidth = (unsigned int)((columnWidth >= tmp || CCXMath::isnanCocos2d(tmp)) ? columnWidth : tmp);

				columnHeight += (int)((*it)->getContentSize().height + 5);
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

		// check if too many rows/columns for available menu items.
		assert(! rowsOccupied);

		CGSize winSize = CCDirector::sharedDirector()->getWinSize();

		column = 0;
		columnWidth = 0;
		columnRows = 0;
		float x = (float)(-width / 2);
		float y;

        if (m_pChildren && m_pChildren->count() > 0)
		{
			NSMutableArray<CCNode*>::NSMutableArrayIterator it;
			for (it = m_pChildren->begin(); it != m_pChildren->end(); ++it)
			{
				if (! *it)
				{
					break;
				}

				if (columnRows == 0)
				{
					columnRows = columns[column];
					y = (float) columnHeights[column];
				}

				// columnWidth = fmaxf(columnWidth, [item contentSize].width);
				float tmp = (*it)->getContentSize().width;
				columnWidth = (unsigned int)((columnWidth >= tmp || CCXMath::isnanCocos2d(tmp)) ? columnWidth : tmp);

				(*it)->setPosition(ccp(x + columnWidths[column] / 2,
					                   y - winSize.height / 2));

				y -= (*it)->getContentSize().height + 10;
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

	// Opacity Protocol

	/** Override synthesized setOpacity to recurse items */
	void CCMenu::setOpacity(GLubyte var)
	{
		m_cOpacity = var;

		if (m_pChildren && m_pChildren->count() > 0)
		{
			NSMutableArray<CCNode*>::NSMutableArrayIterator it;
			for (it = m_pChildren->begin(); it != m_pChildren->end(); ++it)
			{
				if (! *it)
				{
					break;
				}
                
				CCRGBAProtocol *pRGBAProtocol = (*it)->convertToRGBAProtocol();
				if (pRGBAProtocol)
				{
					pRGBAProtocol->setOpacity(m_cOpacity);
				}
			}
		}
	}

	GLubyte CCMenu::getOpacity(void)
	{
		return m_cOpacity;
	}

	void CCMenu::setColor(cocos2d::ccColor3B var)
	{
		m_tColor = var;

		if (m_pChildren && m_pChildren->count() > 0)
		{
			NSMutableArray<CCNode*>::NSMutableArrayIterator it;
			for (it = m_pChildren->begin(); it != m_pChildren->end(); ++it)
			{
				if (! *it)
				{
					break;
				}

				CCRGBAProtocol *pRGBAProtocol = (*it)->convertToRGBAProtocol();
				if (pRGBAProtocol)
				{
					pRGBAProtocol->setColor(m_tColor);
				}
			}
		}
	}

	ccColor3B CCMenu::getColor(void)
	{
		return m_tColor;
	}
}
