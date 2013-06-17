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

#ifndef __CCTABLEVIEW_H__
#define __CCTABLEVIEW_H__

#include "CCScrollView.h"
#include "CCTableViewCell.h"

#include <set>
#include <vector>

NS_CC_EXT_BEGIN

class CCTableView;
class CCArrayForObjectSorting;

typedef enum {
    kCCTableViewFillTopDown,
    kCCTableViewFillBottomUp
} CCTableViewVerticalFillOrder;

/**
 * Sole purpose of this delegate is to single touch event in this version.
 */
class CCTableViewDelegate : public CCScrollViewDelegate
{
public:
    /**
     * Delegate to respond touch event
     *
     * @param table table contains the given cell
     * @param cell  cell that is touched
     */
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell) = 0;

    /**
     * Delegate to respond a table cell press event.
     *
     * @param table table contains the given cell
     * @param cell  cell that is pressed
     */
    virtual void tableCellHighlight(CCTableView* table, CCTableViewCell* cell){};

    /**
     * Delegate to respond a table cell release event
     *
     * @param table table contains the given cell
     * @param cell  cell that is pressed
     */
    virtual void tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell){};

    /**
     * Delegate called when the cell is about to be recycled. Immediately
     * after this call the cell will be removed from the scene graph and
     * recycled.
     *
     * @param table table contains the given cell
     * @param cell  cell that is pressed
     */
    virtual void tableCellWillRecycle(CCTableView* table, CCTableViewCell* cell){};

};


/**
 * Data source that governs table backend data.
 */
class CCTableViewDataSource
{
public:
    virtual ~CCTableViewDataSource() {}

    /**
     * cell size for a given index
     *
     * @param idx the index of a cell to get a size
     * @return size of a cell at given index
     */
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx) {
        return cellSizeForTable(table);
    };
    /**
     * cell height for a given table.
     *
     * @param table table to hold the instances of Class
     * @return cell size
     */
    virtual CCSize cellSizeForTable(CCTableView *table) {
        return CCSizeZero;
    };
    /**
     * a cell instance at a given index
     *
     * @param idx index to search for a cell
     * @return cell found at idx
     */
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx) = 0;
    /**
     * Returns number of cells in a given table view.
     *
     * @return number of cells
     */
    virtual unsigned int numberOfCellsInTableView(CCTableView *table) = 0;

};


/**
 * UITableView counterpart for cocos2d for iphone.
 *
 * this is a very basic, minimal implementation to bring UITableView-like component into cocos2d world.
 *
 */
class CCTableView : public CCScrollView, public CCScrollViewDelegate
{
public:
    CCTableView();
    virtual ~CCTableView();

    /**
     * An intialized table view object
     *
     * @param dataSource data source
     * @param size view size
     * @return table view
     */
    static CCTableView* create(CCTableViewDataSource* dataSource, CCSize size);
    /**
     * An initialized table view object
     *
     * @param dataSource data source;
     * @param size view size
     * @param container parent object for cells
     * @return table view
     */
    static CCTableView* create(CCTableViewDataSource* dataSource, CCSize size, CCNode *container);

    /**
     * data source
     */
    CCTableViewDataSource* getDataSource() { return m_pDataSource; }
    void setDataSource(CCTableViewDataSource* source) { m_pDataSource = source; }
    /**
     * delegate
     */
    CCTableViewDelegate* getDelegate() { return m_pTableViewDelegate; }
    void setDelegate(CCTableViewDelegate* pDelegate) { m_pTableViewDelegate = pDelegate; }

    /**
     * determines how cell is ordered and filled in the view.
     */
    void setVerticalFillOrder(CCTableViewVerticalFillOrder order);
    CCTableViewVerticalFillOrder getVerticalFillOrder();


    bool initWithViewSize(CCSize size, CCNode* container = NULL);
    /**
     * Updates the content of the cell at a given index.
     *
     * @param idx index to find a cell
     */
    void updateCellAtIndex(unsigned int idx);
    /**
     * Inserts a new cell at a given index
     *
     * @param idx location to insert
     */
    void insertCellAtIndex(unsigned int idx);
    /**
     * Removes a cell at a given index
     *
     * @param idx index to find a cell
     */
    void removeCellAtIndex(unsigned int idx);
    /**
     * reloads data from data source.  the view will be refreshed.
     */
    void reloadData();
    /**
     * Dequeues a free cell if available. nil if not.
     *
     * @return free cell
     */
    CCTableViewCell *dequeueCell();

    /**
     * Returns an existing cell at a given index. Returns nil if a cell is nonexistent at the moment of query.
     *
     * @param idx index
     * @return a cell at a given index
     */
    CCTableViewCell *cellAtIndex(unsigned int idx);


    virtual void scrollViewDidScroll(CCScrollView* view);
    virtual void scrollViewDidZoom(CCScrollView* view) {}

    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

protected:

    CCTableViewCell *m_pTouchedCell;
    /**
     * vertical direction of cell filling
     */
    CCTableViewVerticalFillOrder m_eVordering;

    /**
     * index set to query the indexes of the cells used.
     */
    std::set<unsigned int>* m_pIndices;

    /**
     * vector with all cell positions
     */
    std::vector<float> m_vCellsPositions;
    //NSMutableIndexSet *indices_;
    /**
     * cells that are currently in the table
     */
    CCArrayForObjectSorting* m_pCellsUsed;
    /**
     * free list of cells
     */
    CCArrayForObjectSorting* m_pCellsFreed;
    /**
     * weak link to the data source object
     */
    CCTableViewDataSource* m_pDataSource;
    /**
     * weak link to the delegate object
     */
    CCTableViewDelegate* m_pTableViewDelegate;

	CCScrollViewDirection m_eOldDirection;

    int __indexFromOffset(CCPoint offset);
    unsigned int _indexFromOffset(CCPoint offset);
    CCPoint __offsetFromIndex(unsigned int index);
    CCPoint _offsetFromIndex(unsigned int index);

    void _moveCellOutOfSight(CCTableViewCell *cell);
    void _setIndexForCell(unsigned int index, CCTableViewCell *cell);
    void _addCellIfNecessary(CCTableViewCell * cell);

    void _updateCellPositions();
public:
    void _updateContentSize();

};


NS_CC_EXT_END

#endif /* __CCTABLEVIEW_H__ */
