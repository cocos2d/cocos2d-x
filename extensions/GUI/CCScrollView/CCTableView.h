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
#include "extensions/ExtensionExport.h"

#include <set>
#include <vector>

/**
 * @addtogroup ui
 * @{
 */
NS_CC_EXT_BEGIN

class TableView;

/**
 * Sole purpose of this delegate is to single touch event in this version.
 */
class CC_EX_DLL TableViewDelegate : public ScrollViewDelegate
{
public:
    /**
     * Delegate to respond touch event
     *
     * @param table table contains the given cell
     * @param cell  cell that is touched
     * @js NA
     * @lua NA
     */
    virtual void tableCellTouched(TableView* table, TableViewCell* cell) = 0;

    /**
     * Delegate to respond a table cell press event.
     *
     * @param table table contains the given cell
     * @param cell  cell that is pressed
     * @js NA
     * @lua NA
     */
    virtual void tableCellHighlight(TableView* table, TableViewCell* cell);

    /**
     * Delegate to respond a table cell release event
     *
     * @param table table contains the given cell
     * @param cell  cell that is pressed
     * @js NA
     * @lua NA
     */
    virtual void tableCellUnhighlight(TableView* table, TableViewCell* cell);

    /**
     * Delegate called when the cell is about to be recycled. Immediately
     * after this call the cell will be removed from the scene graph and
     * recycled.
     *
     * @param table table contains the given cell
     * @param cell  cell that is pressed
     * @js NA
     * @lua NA
     */
    virtual void tableCellWillRecycle(TableView* table, TableViewCell* cell);

};


/**
 * Data source that governs table backend data.
 */
class CC_EX_DLL TableViewDataSource
{
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TableViewDataSource() {}

    /**
     * cell size for a given index
     *
     * @param idx the index of a cell to get a size
     * @return size of a cell at given index
     */
    virtual Size tableCellSizeForIndex(TableView* table, ssize_t idx);
    /**
     * cell height for a given table.
     *
     * @param table table to hold the instances of Class
     * @return cell size
     */
    virtual Size cellSizeForTable(TableView* table);
    /**
     * a cell instance at a given index
     *
     * @param idx index to search for a cell
     * @return cell found at idx
     */
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx) = 0;
    /**
     * Returns number of cells in a given table view.
     *
     * @return number of cells
     */
    virtual ssize_t numberOfCellsInTableView(TableView *table) = 0;

};


/**
 * UITableView support for cocos2d-x.
 *
 * This is a very basic, minimal implementation to bring UITableView-like component into cocos2d world.
 */
class CC_EX_DLL TableView : public ScrollView, public ScrollViewDelegate
{
public:
    
    enum class VerticalFillOrder
    {
        TOP_DOWN,
        BOTTOM_UP
    };
    
    /** Empty constructor of TableView */
    static TableView* create();
    
    /**
     * An initialized table view object
     *
     * @param dataSource data source
     * @param size view size
     * @return table view
     * @code
     * when this function bound to js or lua,the input params are changed
     * in js:var create(var jsObject,var size)
     * in lua:local create(var size)
     * in lua:
     * @endcode
     */
    static TableView* create(TableViewDataSource* dataSource, Size size);
    /**
     * An initialized table view object
     *
     * @param dataSource data source;
     * @param size view size
     * @param container parent object for cells
     * @return table view
     * @code
     * when this function bound to js or lua,the input params are changed
     * in js:var create(var jsObject,var size,var container)
     * in lua:local create(var size, var container)
     * in lua:
     * @endcode
     */
    static TableView* create(TableViewDataSource* dataSource, Size size, Node *container);
    /**
     * @js ctor
     * @lua new
     */
    TableView();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TableView();

    bool initWithViewSize(Size size, Node* container = NULL);

    /**
     * data source
     * @js NA
     * @lua NA
     */
    TableViewDataSource* getDataSource() { return _dataSource; }
    /**
     * when this function bound to js or lua,the input params are changed
     * in js:var setDataSource(var jsSource)
     * in lua:local setDataSource()
     * @endcode
     */
    void setDataSource(TableViewDataSource* source) { _dataSource = source; }
    /**
     * delegate
     * @js NA
     * @lua NA
     */
    TableViewDelegate* getDelegate() { return _tableViewDelegate; }
    /**
     * @code
     * when this function bound to js or lua,the input params are changed
     * in js:var setDelegate(var jsDelegate)
     * in lua:local setDelegate()
     * @endcode
     */
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
    void updateCellAtIndex(ssize_t idx);
    /**
     * Inserts a new cell at a given index
     *
     * @param idx location to insert
     */
    void insertCellAtIndex(ssize_t idx);
    /**
     * Removes a cell at a given index
     *
     * @param idx index to find a cell
     */
    void removeCellAtIndex(ssize_t idx);
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
    TableViewCell *cellAtIndex(ssize_t idx);

    // Overrides
    virtual void scrollViewDidScroll(ScrollView* view) override;
    virtual void scrollViewDidZoom(ScrollView* view)  override {}
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent) override;
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent) override;
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent) override;
    virtual void onTouchCancelled(Touch *pTouch, Event *pEvent) override;

protected:
    long __indexFromOffset(Vec2 offset);
    long _indexFromOffset(Vec2 offset);
    Vec2 __offsetFromIndex(ssize_t index);
    Vec2 _offsetFromIndex(ssize_t index);

    void _moveCellOutOfSight(TableViewCell *cell);
    void _setIndexForCell(ssize_t index, TableViewCell *cell);
    void _addCellIfNecessary(TableViewCell * cell);

    void _updateCellPositions();


    TableViewCell *_touchedCell;
    /**
     * vertical direction of cell filling
     */
    VerticalFillOrder _vordering;

    /**
     * index set to query the indexes of the cells used.
     */
    std::set<ssize_t>* _indices;

    /**
     * vector with all cell positions
     */
    std::vector<float> _vCellsPositions;
    //NSMutableIndexSet *indices_;
    /**
     * cells that are currently in the table
     */
    Vector<TableViewCell*> _cellsUsed;
    /**
     * free list of cells
     */
    Vector<TableViewCell*> _cellsFreed;
    /**
     * weak link to the data source object
     */
    TableViewDataSource* _dataSource;
    /**
     * weak link to the delegate object
     */
    TableViewDelegate* _tableViewDelegate;

    Direction _oldDirection;

    bool _isUsedCellsDirty;

public:
    void _updateContentSize();

};

NS_CC_EXT_END
// end of ui group
/// @}

#endif /* __CCTABLEVIEW_H__ */
