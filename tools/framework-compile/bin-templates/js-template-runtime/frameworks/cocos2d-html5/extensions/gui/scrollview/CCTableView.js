/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.
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

/**
 * The constant value of the fill style from top to bottom for cc.TableView
 * @constant
 * @type {number}
 */
cc.TABLEVIEW_FILL_TOPDOWN = 0;

/**
 * The constant value of the fill style from bottom to top for cc.TableView
 * @constant
 * @type {number}
 */
cc.TABLEVIEW_FILL_BOTTOMUP = 1;

/**
 * Abstract class for SWTableView cell node
 * @class
 * @abstract
 * @extends cc.Node
 *
 * @property {Number}   objectId    - The index used internally by SWTableView and its subclasses
 */
cc.TableViewCell = cc.Node.extend(/** @lends cc.TableViewCell# */{
    _idx:0,
    _className:"TableViewCell",

    /**
     * The index used internally by SWTableView and its subclasses
     */
    getIdx:function () {
        return this._idx;
    },
    setIdx:function (idx) {
        this._idx = idx;
    },

    /**
     * Cleans up any resources linked to this cell and resets <code>idx</code> property.
     */
    reset:function () {
        this._idx = cc.INVALID_INDEX;
    },

    setObjectID:function (idx) {
        this._idx = idx;
    },
    getObjectID:function () {
        return this._idx;
    }
});

var _p = cc.TableViewCell.prototype;

/** @expose */
_p.objectId;
cc.defineGetterSetter(_p, "objectId", _p.getObjectID, _p.setObjectID);

_p = null;

/**
 * Sole purpose of this delegate is to single touch event in this version.
 */
cc.TableViewDelegate = cc.ScrollViewDelegate.extend(/** @lends cc.TableViewDelegate# */{
    /**
     * Delegate to respond touch event
     *
     * @param {cc.TableView} table table contains the given cell
     * @param {cc.TableViewCell} cell  cell that is touched
     */
    tableCellTouched:function (table, cell) {
    },

    /**
     * Delegate to respond a table cell press event.
     *
     * @param {cc.TableView} table table contains the given cell
     * @param {cc.TableViewCell} cell  cell that is pressed
     */
    tableCellHighlight:function(table, cell){
    },

    /**
     * Delegate to respond a table cell release event
     *
     * @param {cc.TableView} table table contains the given cell
     * @param {cc.TableViewCell} cell  cell that is pressed
     */
    tableCellUnhighlight:function(table, cell){

    },

    /**
     * <p>
     * Delegate called when the cell is about to be recycled. Immediately                     <br/>
     * after this call the cell will be removed from the scene graph and                      <br/>
     * recycled.
     * </p>
     * @param table table contains the given cell
     * @param cell  cell that is pressed
     */
    tableCellWillRecycle:function(table, cell){

    }
});

/**
 * Data source that governs table backend data.
 */
cc.TableViewDataSource = cc.Class.extend(/** @lends cc.TableViewDataSource# */{
    /**
     * cell size for a given index
     * @param {cc.TableView} table table to hold the instances of Class
     * @param {Number} idx the index of a cell to get a size
     * @return {cc.Size} size of a cell at given index
     */
    tableCellSizeForIndex:function(table, idx){
        return this.cellSizeForTable(table);
    },
    /**
     * cell height for a given table.
     *
     * @param {cc.TableView} table table to hold the instances of Class
     * @return {cc.Size} cell size
     */
    cellSizeForTable:function (table) {
        return cc.size(0,0);
    },

    /**
     * a cell instance at a given index
     * @param {cc.TableView} table table to hold the instances of Class
     * @param idx index to search for a cell
     * @return {cc.TableView} cell found at idx
     */
    tableCellAtIndex:function (table, idx) {
        return null;
    },

    /**
     * Returns number of cells in a given table view.
     * @param {cc.TableView} table table to hold the instances of Class
     * @return {Number} number of cells
     */
    numberOfCellsInTableView:function (table) {
        return 0;
    }
});

/**
 * UITableView counterpart for cocos2d for iphone.
 * this is a very basic, minimal implementation to bring UITableView-like component into cocos2d world.
 *
 * @class
 * @extends cc.ScrollView
 *
 * @property {cc.TableViewDataSource}   dataSource          - The data source of the table view
 * @property {cc.TableViewDelegate}     delegate            - The event delegate of the table view
 * @property {Number}                   verticalFillOrder   - The index to determine how cell is ordered and filled in the view
 *
 */
cc.TableView = cc.ScrollView.extend(/** @lends cc.TableView# */{
    _vOrdering:null,
    _indices:null,
    _cellsFreed:null,
    _dataSource:null,
    _tableViewDelegate:null,
    _oldDirection:null,
    _cellsPositions:null,                       //vector with all cell positions
    _touchedCell:null,

    /**
     * The
     * @param dataSource
     * @param size
     * @param container
     */
    ctor:function (dataSource, size, container) {
        cc.ScrollView.prototype.ctor.call(this);
        this._oldDirection = cc.SCROLLVIEW_DIRECTION_NONE;
        this._cellsPositions = [];

        this.initWithViewSize(size, container);
        this.setDataSource(dataSource);
        this._updateCellPositions();
        this._updateContentSize();
    },

    __indexFromOffset:function (offset) {
        var low = 0;
        var high = this._dataSource.numberOfCellsInTableView(this) - 1;
        var search;
        switch (this.getDirection()) {
            case cc.SCROLLVIEW_DIRECTION_HORIZONTAL:
                search = offset.x;
                break;
            default:
                search = offset.y;
                break;
        }

        var locCellsPositions = this._cellsPositions;
        while (high >= low){
            var index = 0|(low + (high - low) / 2);
            var cellStart = locCellsPositions[index];
            var cellEnd = locCellsPositions[index + 1];

            if (search >= cellStart && search <= cellEnd){
                return index;
            } else if (search < cellStart){
                high = index - 1;
            }else {
                low = index + 1;
            }
        }

        if (low <= 0)
            return 0;
        return -1;
    },

    _indexFromOffset:function (offset) {
        var locOffset = {x: offset.x, y: offset.y};
        var locDataSource = this._dataSource;
        var maxIdx = locDataSource.numberOfCellsInTableView(this) - 1;

        if (this._vOrdering === cc.TABLEVIEW_FILL_TOPDOWN)
            locOffset.y = this.getContainer().getContentSize().height - locOffset.y;

        var index = this.__indexFromOffset(locOffset);
        if (index !== -1) {
            index = Math.max(0, index);
            if (index > maxIdx)
                index = cc.INVALID_INDEX;
        }
        return index;
    },

    __offsetFromIndex:function (index) {
        var offset;
        switch (this.getDirection()) {
            case cc.SCROLLVIEW_DIRECTION_HORIZONTAL:
                offset = cc.p(this._cellsPositions[index], 0);
                break;
            default:
                offset = cc.p(0, this._cellsPositions[index]);
                break;
        }

        return offset;
    },

    _offsetFromIndex:function (index) {
        var offset = this.__offsetFromIndex(index);

        var cellSize = this._dataSource.tableCellSizeForIndex(this, index);
        if (this._vOrdering === cc.TABLEVIEW_FILL_TOPDOWN)
            offset.y = this.getContainer().getContentSize().height - offset.y - cellSize.height;

        return offset;
    },

    _updateCellPositions:function(){
        var cellsCount = this._dataSource.numberOfCellsInTableView(this);
        var locCellsPositions = this._cellsPositions;

        if (cellsCount > 0){
            var currentPos = 0;
            var cellSize, locDataSource = this._dataSource;
            for (var i=0; i < cellsCount; i++) {
                locCellsPositions[i] = currentPos;
                cellSize = locDataSource.tableCellSizeForIndex(this, i);
                switch (this.getDirection()) {
                    case cc.SCROLLVIEW_DIRECTION_HORIZONTAL:
                        currentPos += cellSize.width;
                        break;
                    default:
                        currentPos += cellSize.height;
                        break;
                }
            }
            this._cellsPositions[cellsCount] = currentPos;//1 extra value allows us to get right/bottom of the last cell
        }
    },

    _updateContentSize:function () {
        var size = cc.size(0, 0);

        var cellsCount = this._dataSource.numberOfCellsInTableView(this);

        if(cellsCount > 0){
            var maxPosition = this._cellsPositions[cellsCount];
            switch (this.getDirection()) {
                case cc.SCROLLVIEW_DIRECTION_HORIZONTAL:
                    size = cc.size(maxPosition, this._viewSize.height);
                    break;
                default:
                    size = cc.size(this._viewSize.width, maxPosition);
                    break;
            }
        }

        this.setContentSize(size);

        if (this._oldDirection !== this._direction) {
            if (this._direction === cc.SCROLLVIEW_DIRECTION_HORIZONTAL) {
                this.setContentOffset(cc.p(0, 0));
            } else {
                this.setContentOffset(cc.p(0, this.minContainerOffset().y));
            }
            this._oldDirection = this._direction;
        }
    },

    _moveCellOutOfSight:function (cell) {
        if(this._tableViewDelegate && this._tableViewDelegate.tableCellWillRecycle)
            this._tableViewDelegate.tableCellWillRecycle(this, cell);

        this._cellsFreed.addObject(cell);
        this._cellsUsed.removeSortedObject(cell);
        cc.arrayRemoveObject(this._indices, cell.getIdx());

        cell.reset();
        if (cell.getParent() === this.getContainer()) {
            this.getContainer().removeChild(cell, true);
        }
    },

    _setIndexForCell:function (index, cell) {
        cell.setAnchorPoint(0, 0);
        cell.setPosition(this._offsetFromIndex(index));
        cell.setIdx(index);
    },

    _addCellIfNecessary:function (cell) {
        if (cell.getParent() !== this.getContainer()) {
            this.getContainer().addChild(cell);
        }
        this._cellsUsed.insertSortedObject(cell);
        var locIndices = this._indices, addIdx = cell.getIdx();
        if(locIndices.indexOf(addIdx) === -1){
            locIndices.push(addIdx);
            //sort
            locIndices.sort(function(a,b){return a-b;});
        }
    },

    /**
     * data source
     */
    getDataSource:function () {
        return this._dataSource;
    },
    setDataSource:function (source) {
        this._dataSource = source;
    },

    /**
     * delegate
     */
    getDelegate:function () {
        return this._tableViewDelegate;
    },

    setDelegate:function (delegate) {
        this._tableViewDelegate = delegate;
    },

    /**
     * determines how cell is ordered and filled in the view.
     */
    setVerticalFillOrder:function (fillOrder) {
        if (this._vOrdering !== fillOrder) {
            this._vOrdering = fillOrder;
            if (this._cellsUsed.count() > 0) {
                this.reloadData();
            }
        }
    },
    getVerticalFillOrder:function () {
        return this._vOrdering;
    },

    initWithViewSize:function (size, container) {
        if (cc.ScrollView.prototype.initWithViewSize.call(this, size, container)) {
            this._cellsUsed = new cc.ArrayForObjectSorting();
            this._cellsFreed = new cc.ArrayForObjectSorting();
            this._indices = [];
            this._tableViewDelegate = null;
            this._vOrdering = cc.TABLEVIEW_FILL_BOTTOMUP;
            this.setDirection(cc.SCROLLVIEW_DIRECTION_VERTICAL);

            cc.ScrollView.prototype.setDelegate.call(this, this);
            return true;
        }
        return false;
    },

    /**
     * Updates the content of the cell at a given index.
     *
     * @param idx index to find a cell
     */
    updateCellAtIndex:function (idx) {
        if (idx === cc.INVALID_INDEX || idx > this._dataSource.numberOfCellsInTableView(this) - 1)
            return;

        var cell = this.cellAtIndex(idx);
        if (cell)
            this._moveCellOutOfSight(cell);

        cell = this._dataSource.tableCellAtIndex(this, idx);
        this._setIndexForCell(idx, cell);
        this._addCellIfNecessary(cell);
    },

    /**
     * Inserts a new cell at a given index
     *
     * @param idx location to insert
     */
    insertCellAtIndex:function (idx) {
        if (idx === cc.INVALID_INDEX || idx > this._dataSource.numberOfCellsInTableView(this) - 1)
            return;

        var newIdx, locCellsUsed = this._cellsUsed;
        var cell = locCellsUsed.objectWithObjectID(idx);
        if (cell) {
            newIdx = locCellsUsed.indexOfSortedObject(cell);
            for (var i = newIdx; i < locCellsUsed.count(); i++) {
                cell = locCellsUsed.objectAtIndex(i);
                this._setIndexForCell(cell.getIdx() + 1, cell);
            }
        }

        //insert a new cell
        cell = this._dataSource.tableCellAtIndex(this, idx);
        this._setIndexForCell(idx, cell);
        this._addCellIfNecessary(cell);

        this._updateCellPositions();
        this._updateContentSize();
    },

    /**
     * Removes a cell at a given index
     *
     * @param idx index to find a cell
     */
    removeCellAtIndex:function (idx) {
        if (idx === cc.INVALID_INDEX || idx > this._dataSource.numberOfCellsInTableView(this) - 1)
            return;

        var cell = this.cellAtIndex(idx);
        if (!cell)
            return;

        var locCellsUsed = this._cellsUsed;
        var newIdx = locCellsUsed.indexOfSortedObject(cell);

        //remove first
        this._moveCellOutOfSight(cell);
        cc.arrayRemoveObject(this._indices, idx);
        this._updateCellPositions();

        for (var i = locCellsUsed.count() - 1; i > newIdx; i--) {
            cell = locCellsUsed.objectAtIndex(i);
            this._setIndexForCell(cell.getIdx() - 1, cell);
        }
    },

    /**
     * reloads data from data source.  the view will be refreshed.
     */
    reloadData:function () {
        this._oldDirection = cc.SCROLLVIEW_DIRECTION_NONE;
        var locCellsUsed = this._cellsUsed, locCellsFreed = this._cellsFreed, locContainer = this.getContainer();
        for (var i = 0, len = locCellsUsed.count(); i < len; i++) {
            var cell = locCellsUsed.objectAtIndex(i);

            if(this._tableViewDelegate && this._tableViewDelegate.tableCellWillRecycle)
                this._tableViewDelegate.tableCellWillRecycle(this, cell);

            locCellsFreed.addObject(cell);
            cell.reset();
            if (cell.getParent() === locContainer)
                locContainer.removeChild(cell, true);
        }

        this._indices = [];
        this._cellsUsed = new cc.ArrayForObjectSorting();

        this._updateCellPositions();
        this._updateContentSize();
        if (this._dataSource.numberOfCellsInTableView(this) > 0)
            this.scrollViewDidScroll(this);
    },

    /**
     * Dequeues a free cell if available. nil if not.
     *
     * @return {TableViewCell} free cell
     */
    dequeueCell:function () {
        if (this._cellsFreed.count() === 0) {
            return null;
        } else {
            var cell = this._cellsFreed.objectAtIndex(0);
            this._cellsFreed.removeObjectAtIndex(0);
            return cell;
        }
    },

    /**
     * Returns an existing cell at a given index. Returns nil if a cell is nonexistent at the moment of query.
     *
     * @param idx index
     * @return {cc.TableViewCell} a cell at a given index
     */
    cellAtIndex:function (idx) {
        var i = this._indices.indexOf(idx);
        if (i === -1)
            return null;
        return this._cellsUsed.objectWithObjectID(idx);
    },

    scrollViewDidScroll:function (view) {
        var locDataSource = this._dataSource;
        var countOfItems = locDataSource.numberOfCellsInTableView(this);
        if (0 === countOfItems)
            return;

        if (this._tableViewDelegate !== null && this._tableViewDelegate.scrollViewDidScroll)
            this._tableViewDelegate.scrollViewDidScroll(this);

        var  idx = 0, locViewSize = this._viewSize, locContainer = this.getContainer();
        var offset = this.getContentOffset();
        offset.x *= -1;
        offset.y *= -1;

        var maxIdx = Math.max(countOfItems-1, 0);

        if (this._vOrdering === cc.TABLEVIEW_FILL_TOPDOWN)
            offset.y = offset.y + locViewSize.height/locContainer.getScaleY();
        var startIdx = this._indexFromOffset(offset);
        if (startIdx === cc.INVALID_INDEX)
            startIdx = countOfItems - 1;

        if (this._vOrdering === cc.TABLEVIEW_FILL_TOPDOWN)
            offset.y -= locViewSize.height/locContainer.getScaleY();
        else
            offset.y += locViewSize.height/locContainer.getScaleY();
        offset.x += locViewSize.width/locContainer.getScaleX();

        var endIdx = this._indexFromOffset(offset);
        if (endIdx === cc.INVALID_INDEX)
            endIdx = countOfItems - 1;

        var cell, locCellsUsed = this._cellsUsed;
        if (locCellsUsed.count() > 0) {
            cell = locCellsUsed.objectAtIndex(0);
            idx = cell.getIdx();
            while (idx < startIdx) {
                this._moveCellOutOfSight(cell);
                if (locCellsUsed.count() > 0) {
                    cell = locCellsUsed.objectAtIndex(0);
                    idx = cell.getIdx();
                } else
                    break;
            }
        }

        if (locCellsUsed.count() > 0) {
            cell = locCellsUsed.lastObject();
            idx = cell.getIdx();
            while (idx <= maxIdx && idx > endIdx) {
                this._moveCellOutOfSight(cell);
                if (locCellsUsed.count() > 0) {
                    cell = locCellsUsed.lastObject();
                    idx = cell.getIdx();
                } else
                    break;
            }
        }

        var locIndices = this._indices;
        for (var i = startIdx; i <= endIdx; i++) {
            if (locIndices.indexOf(i) !== -1)
                continue;
            this.updateCellAtIndex(i);
        }
    },

    scrollViewDidZoom:function (view) {
    },

    onTouchEnded:function (touch, event) {
        if (!this.isVisible())
            return;

        if (this._touchedCell){
            var bb = this.getBoundingBox();
            var tmpOrigin = cc.p(bb.x, bb.y);
            tmpOrigin = this._parent.convertToWorldSpace(tmpOrigin);
            bb.x = tmpOrigin.x;
            bb.y = tmpOrigin.y;
            var locTableViewDelegate = this._tableViewDelegate;
            if (cc.rectContainsPoint(bb, touch.getLocation()) && locTableViewDelegate !== null){
                if(locTableViewDelegate.tableCellUnhighlight)
                    locTableViewDelegate.tableCellUnhighlight(this, this._touchedCell);
                if(locTableViewDelegate.tableCellTouched)
                    locTableViewDelegate.tableCellTouched(this, this._touchedCell);
            }
            this._touchedCell = null;
        }
        cc.ScrollView.prototype.onTouchEnded.call(this, touch, event);
    },

    onTouchBegan:function(touch, event){
        if (!this.isVisible())
            return false;

        var touchResult = cc.ScrollView.prototype.onTouchBegan.call(this, touch, event);

        if(this._touches.length === 1) {
            var index, point;

            point = this.getContainer().convertTouchToNodeSpace(touch);

            index = this._indexFromOffset(point);
            if (index === cc.INVALID_INDEX)
                this._touchedCell = null;
            else
                this._touchedCell  = this.cellAtIndex(index);

            if (this._touchedCell && this._tableViewDelegate !== null && this._tableViewDelegate.tableCellHighlight)
                this._tableViewDelegate.tableCellHighlight(this, this._touchedCell);
        } else if(this._touchedCell) {
            if(this._tableViewDelegate !== null && this._tableViewDelegate.tableCellUnhighlight)
                this._tableViewDelegate.tableCellUnhighlight(this, this._touchedCell);
            this._touchedCell = null;
        }

        return touchResult;
    },

    onTouchMoved: function(touch, event){
        cc.ScrollView.prototype.onTouchMoved.call(this, touch, event);

        if (this._touchedCell && this.isTouchMoved()) {
            if(this._tableViewDelegate !== null && this._tableViewDelegate.tableCellUnhighlight)
                this._tableViewDelegate.tableCellUnhighlight(this, this._touchedCell);
            this._touchedCell = null;
        }
    },

    onTouchCancelled: function(touch, event){
        cc.ScrollView.prototype.onTouchCancelled.call(this, touch, event);

        if (this._touchedCell) {
            if(this._tableViewDelegate !== null && this._tableViewDelegate.tableCellUnhighlight)
                this._tableViewDelegate.tableCellUnhighlight(this, this._touchedCell);
            this._touchedCell = null;
        }
    }
});

var _p = cc.TableView.prototype;

/** @expose */
_p.dataSource;
cc.defineGetterSetter(_p, "dataSource", _p.getDataSource, _p.setDataSource);
/** @expose */
_p.delegate;
cc.defineGetterSetter(_p, "delegate", _p.getDelegate, _p.setDelegate);
/** @expose */
_p.verticalFillOrder;
cc.defineGetterSetter(_p, "verticalFillOrder", _p.getVerticalFillOrder, _p.setVerticalFillOrder);

_p = null;

/**
 * An initialized table view object
 * @deprecated
 * @param {cc.TableViewDataSource} dataSource data source;
 * @param {cc.Size} size view size
 * @param {cc.Node} [container] parent object for cells
 * @return {cc.TableView} table view
 */
cc.TableView.create = function (dataSource, size, container) {
    return new cc.TableView(dataSource, size, container);
};
