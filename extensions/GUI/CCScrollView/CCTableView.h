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

class TableView;
class ArrayForObjectSorting;

/**
 * Sole purpose of this delegate is to single touch event in this version.
 */
class TableViewDelegate : public ScrollViewDelegate
{
public:
    /**
     * Delegate to respond touch event
     *
     * @param table table contains the given cell
     * @param cell  cell that is touched
     */
    virtual void tableCellTouched(TableView* table, TableViewCell* cell) = 0;

    /**
     * Delegate to respond a table cell press event.
     *
     * @param table table contains the given cell
     * @param cell  cell that is pressed
     */
    virtual void tableCellHighlight(TableView* table, TableViewCell* cell){};

    /**
     * Delegate to respond a table cell release event
     *
     * @param table table contains the given cell
     * @param cell  cell that is pressed
     */
    virtual void tableCellUnhighlight(TableView* table, TableViewCell* cell){};

    /**
     * Delegate called when the cell is about to be recycled. Immediately
     * after this call the cell will be removed from the scene graph and
     * recycled.
     *
     * @param table table contains the given cell
     * @param cell  cell that is pressed
     */
    virtual void tableCellWillRecycle(TableView* table, TableViewCell* cell){};

};


/**
 * Data source that governs table backend data.
 */
class TableViewDataSource
{
public:
    virtual ~TableViewDataSource() {}

    /**
     * cell size for a given index
     *
     * @param idx the index of a cell to get a size
     * @return size of a cell at given index
     */
    virtual Size tableCellSizeForIndex(TableView *table, unsigned int idx) {
        return cellSizeForTable(table);
    };
    /**
     * cell height for a given table.
     *
     * @param table table to hold the instances of Class
     * @return cell size
     */
    virtual Size cellSizeForTable(TableView *table) {
        return Size::ZERO;
    };
    /**
     * a cell instance at a given index
     *
     * @param idx index to search for a cell
     * @return cell found at idx
     */
    virtual TableViewCell* tableCellAtIndex(TableView *table, unsigned int idx) = 0;
    /**
     * Returns number of cells in a given table view.
     *
     * @return number of cells
     */
    virtual unsigned int numberOfCellsInTableView(TableView *table) = 0;

};


/**
 * UITableView counterpart for cocos2d for iphone.
 *
 * this is a very basic, minimal implementation to bring UITableView-like component into cocos2d world.
 *
 */
class TableView : public ScrollView, public ScrollViewDelegate
{
public:
    
    enum class VerticalFillOrder
    {
        TOP_DOWN,
        BOTTOM_UP
    };
    /**
     * An intialized table view object
     *
     * @param dataSource data source
     * @param size view size
     * @return table view
     */
    static TableView* create(TableViewDataSource* dataSource, Size size);
    /**
     * An initialized table view object
     *
     * @param dataSource data source;
     * @param size view size
     * @param container parent object for cells
     * @return table view
     */
    static TableView* create(TableViewDataSource* dataSource, Size size, Node *container);

    TableView();
    virtual ~TableView();

    bool initWithViewSize(Size size, Node* container = NULL);

    /**
     * data source
     */
    TableViewDataSource* getDataSource() { return _dataSource; }
    void setDataSource(TableViewDataSource* source) { _dataSource = source; }
    /**
     * delegate
     */
    TableViewDelegate* getDelegate() { return _tableViewDelegate; }
    void setDelegate(TableViewDelegate* pDelegate) { _tableViewDelegate = pDelegate; }

    /**
     * determines how cell is ordered and filled in the view.
     */
    void setVerticalFillOrder(VerticalFillOrder order);
    VerticalFillOrder getVerticalFillOrder();

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
    TableViewCell *dequeueCell();

    /**
     * Returns an existing cell at a given index. Returns nil if a cell is nonexistent at the moment of query.
     *
     * @param idx index
     * @return a cell at a given index
     */
    TableViewCell *cellAtIndex(unsigned int idx);

    // Overrides
    virtual void scrollViewDidScroll(ScrollView* view) override;
    virtual void scrollViewDidZoom(ScrollView* view)  override {}
    virtual bool ccTouchBegan(Touch *pTouch, Event *pEvent) override;
    virtual void ccTouchMoved(Touch *pTouch, Event *pEvent) override;
    virtual void ccTouchEnded(Touch *pTouch, Event *pEvent) override;
    virtual void ccTouchCancelled(Touch *pTouch, Event *pEvent) override;

protected:

    TableViewCell *_touchedCell;
    /**
     * vertical direction of cell filling
     */
    VerticalFillOrder _vordering;

    /**
     * index set to query the indexes of the cells used.
     */
    std::set<unsigned int>* _indices;

    /**
     * vector with all cell positions
     */
    std::vector<float> _vCellsPositions;
    //NSMutableIndexSet *indices_;
    /**
     * cells that are currently in the table
     */
    ArrayForObjectSorting* _cellsUsed;
    /**
     * free list of cells
     */
    ArrayForObjectSorting* _cellsFreed;
    /**
     * weak link to the data source object
     */
    TableViewDataSource* _dataSource;
    /**
     * weak link to the delegate object
     */
    TableViewDelegate* _tableViewDelegate;

	Direction _oldDirection;

    int __indexFromOffset(Point offset);
    unsigned int _indexFromOffset(Point offset);
    Point __offsetFromIndex(unsigned int index);
    Point _offsetFromIndex(unsigned int index);

    void _moveCellOutOfSight(TableViewCell *cell);
    void _setIndexForCell(unsigned int index, TableViewCell *cell);
    void _addCellIfNecessary(TableViewCell * cell);

    void _updateCellPositions();
public:
    void _updateContentSize();

};


NS_CC_EXT_END

#endif /* __CCTABLEVIEW_H__ */
