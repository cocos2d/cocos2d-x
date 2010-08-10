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
#include "support/CGPointExtension.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
namespace cocos2d{


	enum {
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
		if(	pRet->initWithItems(item, args) )
		{
			pRet->autorelease();
			va_end(args);
			return pRet;
		}
		va_end(args);
		return NULL;
	}
	CCMenu * CCMenu::initWithItems(CCMenuItem* item, va_list args)
	{
		if ( __super::init() )
		{
			this->m_bIsTouchEnabled = true;
			// menu in the center of the screen
			CGSize s = CCDirector::getSharedDirector()->getWinSize();
			this->m_bIsRelativeAnchorPoint = false;
			m_tAnchorPoint = ccp(0.5f, 0.5f);
			this->setContentSize(s);
			// XXX: in v0.7, winSize should return the visible size
			// XXX: so the bar calculation should be done there
			CGRect r = CCXApplication::getSharedApplication()->statusBarFrame();
			ccDeviceOrientation orientation = CCDirector::getSharedDirector()->getDeviceOrientation();
			if( orientation == CCDeviceOrientationLandscapeLeft || orientation == CCDeviceOrientationLandscapeRight )
				s.height -= r.size.width;
			else
				s.height -= r.size.height;
			this->m_tPosition = ccp(s.width/2, s.height/2);

			int z=0;

			if (item)
			{
				this->addChild(item, z);
				CCMenuItem *i = va_arg(args, CCMenuItem*);
				while(i)
				{
					z++;
					this->addChild(i, z);
					i = va_arg(args, CCMenuItem*);
				}
			}
			//	[self alignItemsVertically];

			m_pSelectedItem = NULL;
			m_eState = kMenuStateWaiting;
			return this;
		}
		return NULL;
	}
	/*
	* override add:
	*/
	CCNode * CCMenu::addChild(CCNode * child, int zOrder)
	{
		__super::addChild(child, zOrder);
	}
	CCNode * CCMenu::addChild(CCNode * child, int zOrder, int tag)
	{
		NSAssert( dynamic_cast<CCMenuItem*>(child) != NULL, L"Menu only supports MenuItem objects as children");
		return __super::addChild(child, zOrder, tag);
	}

	//Menu - Events
	void CCMenu::registerWithTouchDispatcher()
	{
		CCTouchDispatcher::getSharedDispatcher->addTargetedDelegate(this, INT_MIN+1, true);
	}
	bool CCMenu::ccTouchBegan(CCTouch* touch, UIEvent* event)
	{
		if( m_eState != kMenuStateWaiting || !m_bIsVisible )
			return false;
		m_pSelectedItem = this->itemForTouch(touch);

		if(m_pSelectedItem)
		{
			m_pSelectedItem->selected();
			m_eState = kMenuStateTrackingTouch;
			return true;
		}
		return false;
	}
	void CCMenu::ccTouchEnded(CCTouch *touch, UIEvent* event)
	{
		NSAssert(m_eState == kMenuStateTrackingTouch, "[Menu ccTouchEnded] -- invalid state");
		m_pSelectedItem->unselected();
		m_pSelectedItem->activate();
		m_eState = kMenuStateWaiting;
	}
	void CCMenu::ccTouchCancelled(CCTouch *touch, UIEvent* event)
	{
		NSAssert(m_eState == kMenuStateTrackingTouch, "[Menu ccTouchCancelled] -- invalid state");
		m_pSelectedItem->unselected();
		m_eState = kMenuStateWaiting;
	}
	void CCMenu::ccTouchMoved(CCTouch* touch, UIEvent* event)
	{
		NSAssert(m_eState == kMenuStateTrackingTouch, "[Menu ccTouchMoved] -- invalid state");
		CCMenuItem *currentItem = this->itemForTouch(touch);
		if (currentItem != m_pSelectedItem) 
		{
			m_pSelectedItem->unselected();
			m_pSelectedItem = currentItem;
			m_pSelectedItem->selected();
		}
	}

	//Menu - Alignment
	void CCMenu::alignItemsVertically()
	{
		return this->alignItemsVerticallyWithPadding(kDefaultPadding);
	}
	void CCMenu::alignItemsVerticallyWithPadding(float padding)
	{
		float height = -padding;
		if(m_pChildren && m_pChildren->count() > 0)
		{
			NSMutableArray<CCNode*>::NSMutableArrayIterator it;
			for( it = m_pChildren->begin(); it != m_pChildren->end(); ++it)
			{
				height += (*it)->getContentSize().height * (*it)->getScaleY() + padding;
			}
		}

		float y = height / 2.0f;
		if(m_pChildren && m_pChildren->count() > 0)
		{
			NSMutableArray<CCNode*>::NSMutableArrayIterator it;
			for( it = m_pChildren->begin(); it != m_pChildren->end(); ++it)
			{
				(*it)->setPosition( ccp(0, (*it)->getContentSize().height * (*it)->getScaleY() / 2.0f) );
				y -= (*it)->getContentSize().height * (*it)->getScaleY() + padding;
			}
		}
	}

	-(void) alignItemsHorizontally
	{
		return [self alignItemsHorizontallyWithPadding:kDefaultPadding];
	}

	-(void) alignItemsHorizontallyWithPadding:(float)padding
	{

		float width = -padding;
		for(CCMenuItem* item in children_)
			width += [item contentSize].width * item.scaleX + padding;

		float x = -width / 2.0f;
		for(CCMenuItem* item in children_) {
			[item setPosition:ccp(x + [item contentSize].width * item.scaleX / 2.0f, 0)];
			x += [item contentSize].width * item.scaleX + padding;
		}
	}

	-(void) alignItemsInColumns: (NSNumber *) columns, ...
	{
		va_list args;
		va_start(args, columns);

		[self alignItemsInColumns:columns vaList:args];

		va_end(args);
	}

	-(void) alignItemsInColumns: (NSNumber *) columns vaList: (va_list) args
	{
		NSMutableArray *rows = [[NSMutableArray alloc] initWithObjects:columns, nil];
		columns = va_arg(args, NSNumber*);
		while(columns) {
			[rows addObject:columns];
			columns = va_arg(args, NSNumber*);
		}

		int height = -5;
		NSUInteger row = 0, rowHeight = 0, columnsOccupied = 0, rowColumns;
		for(CCMenuItem *item in children_) {
			NSAssert( row < [rows count], @"Too many menu items for the amount of rows/columns.");

			rowColumns = [(NSNumber *) [rows objectAtIndex:row] unsignedIntegerValue];
			NSAssert( rowColumns, @"Can't have zero columns on a row");

			rowHeight = fmaxf(rowHeight, [item contentSize].height);
			++columnsOccupied;

			if(columnsOccupied >= rowColumns) {
				height += rowHeight + 5;

				columnsOccupied = 0;
				rowHeight = 0;
				++row;
			}
		}
		NSAssert( !columnsOccupied, @"Too many rows/columns for available menu items." );

		CGSize winSize = [[CCDirector sharedDirector] winSize];

		row = 0; rowHeight = 0; rowColumns = 0;
		float w, x, y = height / 2;
		for(CCMenuItem *item in children_) {
			if(rowColumns == 0) {
				rowColumns = [(NSNumber *) [rows objectAtIndex:row] unsignedIntegerValue];
				w = winSize.width / (1 + rowColumns);
				x = w;
			}

			rowHeight = fmaxf(rowHeight, [item contentSize].height);
			[item setPosition:ccp(x - winSize.width / 2,
				y - [item contentSize].height / 2)];

			x += w + 10;
			++columnsOccupied;

			if(columnsOccupied >= rowColumns) {
				y -= rowHeight + 5;

				columnsOccupied = 0;
				rowColumns = 0;
				rowHeight = 0;
				++row;
			}
		}

		[rows release];
	}

	-(void) alignItemsInRows: (NSNumber *) rows, ...
	{
		va_list args;
		va_start(args, rows);

		[self alignItemsInRows:rows vaList:args];

		va_end(args);
	}

	-(void) alignItemsInRows: (NSNumber *) rows vaList: (va_list) args
	{
		NSMutableArray *columns = [[NSMutableArray alloc] initWithObjects:rows, nil];
		rows = va_arg(args, NSNumber*);
		while(rows) {
			[columns addObject:rows];
			rows = va_arg(args, NSNumber*);
		}

		NSMutableArray *columnWidths = [[NSMutableArray alloc] init];
		NSMutableArray *columnHeights = [[NSMutableArray alloc] init];

		int width = -10, columnHeight = -5;
		NSUInteger column = 0, columnWidth = 0, rowsOccupied = 0, columnRows;
		for(CCMenuItem *item in children_) {
			NSAssert( column < [columns count], @"Too many menu items for the amount of rows/columns.");

			columnRows = [(NSNumber *) [columns objectAtIndex:column] unsignedIntegerValue];
			NSAssert( columnRows, @"Can't have zero rows on a column");

			columnWidth = fmaxf(columnWidth, [item contentSize].width);
			columnHeight += [item contentSize].height + 5;
			++rowsOccupied;

			if(rowsOccupied >= columnRows) {
				[columnWidths addObject:[NSNumber numberWithUnsignedInteger:columnWidth]];
				[columnHeights addObject:[NSNumber numberWithUnsignedInteger:columnHeight]];
				width += columnWidth + 10;

				rowsOccupied = 0;
				columnWidth = 0;
				columnHeight = -5;
				++column;
			}
		}
		NSAssert( !rowsOccupied, @"Too many rows/columns for available menu items.");

		CGSize winSize = [[CCDirector sharedDirector] winSize];

		column = 0; columnWidth = 0; columnRows = 0;
		float x = -width / 2, y;
		for(CCMenuItem *item in children_) {
			if(columnRows == 0) {
				columnRows = [(NSNumber *) [columns objectAtIndex:column] unsignedIntegerValue];
				y = ([(NSNumber *) [columnHeights objectAtIndex:column] intValue] + winSize.height) / 2;
			}

			columnWidth = fmaxf(columnWidth, [item contentSize].width);
			[item setPosition:ccp(x + [(NSNumber *) [columnWidths objectAtIndex:column] unsignedIntegerValue] / 2,
				y - winSize.height / 2)];

			y -= [item contentSize].height + 10;
			++rowsOccupied;

			if(rowsOccupied >= columnRows) {
				x += columnWidth + 5;

				rowsOccupied = 0;
				columnRows = 0;
				columnWidth = 0;
				++column;
			}
		}

		[columns release];
		[columnWidths release];
		[columnHeights release];
	}

#pragma mark Menu - Opacity Protocol

	/** Override synthesized setOpacity to recurse items */
	- (void) setOpacity:(GLubyte)newOpacity
	{
		opacity_ = newOpacity;
		for(id<CCRGBAProtocol> item in children_)
			[item setOpacity:opacity_];
	}
	GLubyte CCMenu::getOpacity()
	{
		return m_cOpacity;
	}

	-(void) setColor:(ccColor3B)color
	{
		color_ = color;
		for(id<CCRGBAProtocol> item in children_)
			[item setColor:color_];
	}
	ccColor3B CCMenu::getColor()
	{
		return m_tColor;
	}

#pragma mark Menu - Private

	-(CCMenuItem *) itemForTouch: (UITouch *) touch
	{
		CGPoint touchLocation = [touch locationInView: [touch view]];
		touchLocation = [[CCDirector sharedDirector] convertToGL: touchLocation];

		for( CCMenuItem* item in children_ ) {

			// ignore invisible and disabled items: issue #779, #866
			if ( [item visible] && [item isEnabled] ) {

				CGPoint local = [item convertToNodeSpace:touchLocation];

				CGRect r = [item rect];
				r.origin = CGPointZero;

				if( CGRectContainsPoint( r, local ) )
					return item;
			}
		}
		return nil;
	}
	@end

}