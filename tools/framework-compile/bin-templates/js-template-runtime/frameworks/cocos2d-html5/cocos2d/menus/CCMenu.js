/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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
 * @constant
 * @type Number
 */
cc.MENU_STATE_WAITING = 0;
/**
 * @constant
 * @type Number
 */
cc.MENU_STATE_TRACKING_TOUCH = 1;
/**
 * @constant
 * @type Number
 */
cc.MENU_HANDLER_PRIORITY = -128;
/**
 * @constant
 * @type Number
 */
cc.DEFAULT_PADDING = 5;

/**
 *<p> Features and Limitation:<br/>
 *  - You can add MenuItem objects in runtime using addChild:<br/>
 *  - But the only accepted children are MenuItem objects</p>
 * @class
 * @extends cc.Layer
 * @param {...cc.MenuItem|null} menuItems}
 * @example
 * var layer = new cc.Menu(menuitem1, menuitem2, menuitem3);
 */
cc.Menu = cc.Layer.extend(/** @lends cc.Menu# */{
    enabled: false,

    _selectedItem: null,
    _state: -1,
    _touchListener: null,
    _className: "Menu",

    /**
     * Constructor of cc.Menu override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function.
     * @param {...cc.MenuItem|null} menuItems
     */
    ctor: function (menuItems) {
        cc.Layer.prototype.ctor.call(this);
        this._color = cc.color.WHITE;
        this.enabled = false;
        this._opacity = 255;
        this._selectedItem = null;
        this._state = -1;

        this._touchListener = cc.EventListener.create({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches: true,
            onTouchBegan: this._onTouchBegan,
            onTouchMoved: this._onTouchMoved,
            onTouchEnded: this._onTouchEnded,
            onTouchCancelled: this._onTouchCancelled
        });

        if ((arguments.length > 0) && (arguments[arguments.length - 1] == null))
            cc.log("parameters should not be ending with null in Javascript");

        var argc = arguments.length, items;
        if (argc === 0) {
            items = [];
        } else if (argc === 1) {
            if (menuItems instanceof Array) {
                items = menuItems;
            }
            else items = [menuItems];
        }
        else if (argc > 1) {
            items = [];
            for (var i = 0; i < argc; i++) {
                if (arguments[i])
                    items.push(arguments[i]);
            }
        }
        this.initWithArray(items);
    },
    /**
     * <p>
     *     Event callback that is invoked every time when CCMenu enters the 'stage'.                                   <br/>
     *     If the CCMenu enters the 'stage' with a transition, this event is called when the transition starts.        <br/>
     *     During onEnter you can't access a "sister/brother" node.                                                    <br/>
     *     If you override onEnter, you must call its parent's onEnter function with this._super().
     * </p>
     */
    onEnter: function () {
        var locListener = this._touchListener;
        if (!locListener._isRegistered())
            cc.eventManager.addListener(locListener, this);
        cc.Node.prototype.onEnter.call(this);
    },

    /**
     * return whether or not the menu will receive events
     * @return {Boolean}
     */
    isEnabled: function () {
        return this.enabled;
    },

    /**
     * set whether or not the menu will receive events
     * @param {Boolean} enabled
     */
    setEnabled: function (enabled) {
        this.enabled = enabled;
    },

    /**
     * initializes a cc.Menu with it's items
     * @param {Array} args
     * @return {Boolean}
     */
    initWithItems: function (args) {
        var pArray = [];
        if (args) {
            for (var i = 0; i < args.length; i++) {
                if (args[i])
                    pArray.push(args[i]);
            }
        }

        return this.initWithArray(pArray);
    },

    /**
     * initializes a cc.Menu with a Array of cc.MenuItem objects
     * @param {Array} arrayOfItems array Of cc.MenuItem Items
     * @return {Boolean}
     */
    initWithArray: function (arrayOfItems) {
        if (cc.Layer.prototype.init.call(this)) {
            this.enabled = true;

            // menu in the center of the screen
            var winSize = cc.winSize;
            this.setPosition(winSize.width / 2, winSize.height / 2);
            this.setContentSize(winSize);
            this.setAnchorPoint(0.5, 0.5);
            this.ignoreAnchorPointForPosition(true);

            if (arrayOfItems) {
                for (var i = 0; i < arrayOfItems.length; i++)
                    this.addChild(arrayOfItems[i], i);
            }

            this._selectedItem = null;
            this._state = cc.MENU_STATE_WAITING;

            // enable cascade color and opacity on menus
            this.cascadeColor = true;
            this.cascadeOpacity = true;

            return true;
        }
        return false;
    },

    /**
     * add a child for  cc.Menu
     * @param {cc.Node} child
     * @param {Number|Null} [zOrder=] zOrder for the child
     * @param {Number|Null} [tag=] tag for the child
     */
    addChild: function (child, zOrder, tag) {
        if (!(child instanceof cc.MenuItem))
            throw "cc.Menu.addChild() : Menu only supports MenuItem objects as children";
        cc.Layer.prototype.addChild.call(this, child, zOrder, tag);
    },

    /**
     * align items vertically with default padding
     */
    alignItemsVertically: function () {
        this.alignItemsVerticallyWithPadding(cc.DEFAULT_PADDING);
    },

    /**
     * align items vertically with specified padding
     * @param {Number} padding
     */
    alignItemsVerticallyWithPadding: function (padding) {
        var height = -padding, locChildren = this._children, len, i, locScaleY, locHeight, locChild;
        if (locChildren && locChildren.length > 0) {
            for (i = 0, len = locChildren.length; i < len; i++)
                height += locChildren[i].height * locChildren[i].scaleY + padding;

            var y = height / 2.0;

            for (i = 0, len = locChildren.length; i < len; i++) {
                locChild = locChildren[i];
                locHeight = locChild.height;
                locScaleY = locChild.scaleY;
                locChild.setPosition(0, y - locHeight * locScaleY / 2);
                y -= locHeight * locScaleY + padding;
            }
        }
    },

    /**
     * align items horizontally with default padding
     */
    alignItemsHorizontally: function () {
        this.alignItemsHorizontallyWithPadding(cc.DEFAULT_PADDING);
    },

    /**
     * align items horizontally with specified padding
     * @param {Number} padding
     */
    alignItemsHorizontallyWithPadding: function (padding) {
        var width = -padding, locChildren = this._children, i, len, locScaleX, locWidth, locChild;
        if (locChildren && locChildren.length > 0) {
            for (i = 0, len = locChildren.length; i < len; i++)
                width += locChildren[i].width * locChildren[i].scaleX + padding;

            var x = -width / 2.0;

            for (i = 0, len = locChildren.length; i < len; i++) {
                locChild = locChildren[i];
                locScaleX = locChild.scaleX;
                locWidth = locChildren[i].width;
                locChild.setPosition(x + locWidth * locScaleX / 2, 0);
                x += locWidth * locScaleX + padding;
            }
        }
    },

    /**
     * align items in columns
     * @example
     * // Example
     * menu.alignItemsInColumns(3,2,3)// this will create 3 columns, with 3 items for first column, 2 items for second and 3 for third
     *
     * menu.alignItemsInColumns(3,3)//this creates 2 columns, each have 3 items
     */
    alignItemsInColumns: function (/*Multiple Arguments*/) {
        if ((arguments.length > 0) && (arguments[arguments.length - 1] == null))
            cc.log("parameters should not be ending with null in Javascript");

        var rows = [];
        for (var i = 0; i < arguments.length; i++) {
            rows.push(arguments[i]);
        }
        var height = -5;
        var row = 0;
        var rowHeight = 0;
        var columnsOccupied = 0;
        var rowColumns, tmp, len;
        var locChildren = this._children;
        if (locChildren && locChildren.length > 0) {
            for (i = 0, len = locChildren.length; i < len; i++) {
                if (row >= rows.length)
                    continue;

                rowColumns = rows[row];
                // can not have zero columns on a row
                if (!rowColumns)
                    continue;

                tmp = locChildren[i].height;
                rowHeight = ((rowHeight >= tmp || isNaN(tmp)) ? rowHeight : tmp);

                ++columnsOccupied;
                if (columnsOccupied >= rowColumns) {
                    height += rowHeight + 5;

                    columnsOccupied = 0;
                    rowHeight = 0;
                    ++row;
                }
            }
        }
        // check if too many rows/columns for available menu items
        //cc.assert(!columnsOccupied, "");    //?
        var winSize = cc.director.getWinSize();

        row = 0;
        rowHeight = 0;
        rowColumns = 0;
        var w = 0.0;
        var x = 0.0;
        var y = (height / 2);

        if (locChildren && locChildren.length > 0) {
            for (i = 0, len = locChildren.length; i < len; i++) {
                var child = locChildren[i];
                if (rowColumns === 0) {
                    rowColumns = rows[row];
                    w = winSize.width / (1 + rowColumns);
                    x = w;
                }

                tmp = child._getHeight();
                rowHeight = ((rowHeight >= tmp || isNaN(tmp)) ? rowHeight : tmp);
                child.setPosition(x - winSize.width / 2, y - tmp / 2);

                x += w;
                ++columnsOccupied;

                if (columnsOccupied >= rowColumns) {
                    y -= rowHeight + 5;
                    columnsOccupied = 0;
                    rowColumns = 0;
                    rowHeight = 0;
                    ++row;
                }
            }
        }
    },
    /**
     * align menu items in rows
     * @param {Number}
     * @example
     * // Example
     * menu.alignItemsInRows(5,3)//this will align items to 2 rows, first row with 5 items, second row with 3
     *
     * menu.alignItemsInRows(4,4,4,4)//this creates 4 rows each have 4 items
     */
    alignItemsInRows: function (/*Multiple arguments*/) {
        if ((arguments.length > 0) && (arguments[arguments.length - 1] == null))
            cc.log("parameters should not be ending with null in Javascript");
        var columns = [], i;
        for (i = 0; i < arguments.length; i++) {
            columns.push(arguments[i]);
        }
        var columnWidths = [];
        var columnHeights = [];

        var width = -10;
        var columnHeight = -5;
        var column = 0;
        var columnWidth = 0;
        var rowsOccupied = 0;
        var columnRows, child, len, tmp;

        var locChildren = this._children;
        if (locChildren && locChildren.length > 0) {
            for (i = 0, len = locChildren.length; i < len; i++) {
                child = locChildren[i];
                // check if too many menu items for the amount of rows/columns
                if (column >= columns.length)
                    continue;

                columnRows = columns[column];
                // can't have zero rows on a column
                if (!columnRows)
                    continue;

                // columnWidth = fmaxf(columnWidth, [item contentSize].width);
                tmp = child.width;
                columnWidth = ((columnWidth >= tmp || isNaN(tmp)) ? columnWidth : tmp);

                columnHeight += (child.height + 5);
                ++rowsOccupied;

                if (rowsOccupied >= columnRows) {
                    columnWidths.push(columnWidth);
                    columnHeights.push(columnHeight);
                    width += columnWidth + 10;

                    rowsOccupied = 0;
                    columnWidth = 0;
                    columnHeight = -5;
                    ++column;
                }
            }
        }
        // check if too many rows/columns for available menu items.
        //cc.assert(!rowsOccupied, "");
        var winSize = cc.director.getWinSize();

        column = 0;
        columnWidth = 0;
        columnRows = 0;
        var x = -width / 2;
        var y = 0.0;

        if (locChildren && locChildren.length > 0) {
            for (i = 0, len = locChildren.length; i < len; i++) {
                child = locChildren[i];
                if (columnRows === 0) {
                    columnRows = columns[column];
                    y = columnHeights[column];
                }

                // columnWidth = fmaxf(columnWidth, [item contentSize].width);
                tmp = child._getWidth();
                columnWidth = ((columnWidth >= tmp || isNaN(tmp)) ? columnWidth : tmp);

                child.setPosition(x + columnWidths[column] / 2, y - winSize.height / 2);

                y -= child.height + 10;
                ++rowsOccupied;

                if (rowsOccupied >= columnRows) {
                    x += columnWidth + 5;
                    rowsOccupied = 0;
                    columnRows = 0;
                    columnWidth = 0;
                    ++column;
                }
            }
        }
    },

    /**
     * remove a child from cc.Menu
     * @param {cc.Node} child the child you want to remove
     * @param {boolean} cleanup whether to cleanup
     */
    removeChild: function (child, cleanup) {
        if (child == null)
            return;
        if (!(child instanceof cc.MenuItem)) {
            cc.log("cc.Menu.removeChild():Menu only supports MenuItem objects as children");
            return;
        }

        if (this._selectedItem === child)
            this._selectedItem = null;
        cc.Node.prototype.removeChild.call(this, child, cleanup);
    },

    _onTouchBegan: function (touch, event) {
        var target = event.getCurrentTarget();
        if (target._state !== cc.MENU_STATE_WAITING || !target._visible || !target.enabled)
            return false;

        for (var c = target.parent; c != null; c = c.parent) {
            if (!c.isVisible())
                return false;
        }

        target._selectedItem = target._itemForTouch(touch);
        if (target._selectedItem) {
            target._state = cc.MENU_STATE_TRACKING_TOUCH;
            target._selectedItem.selected();
            target._selectedItem.setNodeDirty();
            return true;
        }
        return false;
    },

    _onTouchEnded: function (touch, event) {
        var target = event.getCurrentTarget();
        if (target._state !== cc.MENU_STATE_TRACKING_TOUCH) {
            cc.log("cc.Menu.onTouchEnded(): invalid state");
            return;
        }
        if (target._selectedItem) {
            target._selectedItem.unselected();
            target._selectedItem.setNodeDirty();
            target._selectedItem.activate();
        }
        target._state = cc.MENU_STATE_WAITING;
    },

    _onTouchCancelled: function (touch, event) {
        var target = event.getCurrentTarget();
        if (target._state !== cc.MENU_STATE_TRACKING_TOUCH) {
            cc.log("cc.Menu.onTouchCancelled(): invalid state");
            return;
        }
        if (this._selectedItem) {
            target._selectedItem.unselected();
            target._selectedItem.setNodeDirty();
        }
        target._state = cc.MENU_STATE_WAITING;
    },

    _onTouchMoved: function (touch, event) {
        var target = event.getCurrentTarget();
        if (target._state !== cc.MENU_STATE_TRACKING_TOUCH) {
            cc.log("cc.Menu.onTouchMoved(): invalid state");
            return;
        }
        var currentItem = target._itemForTouch(touch);
        if (currentItem !== target._selectedItem) {
            if (target._selectedItem) {
                target._selectedItem.unselected();
                target._selectedItem.setNodeDirty();
            }
            target._selectedItem = currentItem;
            if (target._selectedItem) {
                target._selectedItem.selected();
                target._selectedItem.setNodeDirty();
            }
        }
    },

    /**
     * <p>
     * callback that is called every time the cc.Menu leaves the 'stage'.                                         <br/>
     * If the cc.Menu leaves the 'stage' with a transition, this callback is called when the transition finishes. <br/>
     * During onExit you can't access a sibling node.                                                             <br/>
     * If you override onExit, you shall call its parent's onExit with this._super().
     * </p>
     */
    onExit: function () {
        if (this._state === cc.MENU_STATE_TRACKING_TOUCH) {
            if (this._selectedItem) {
                this._selectedItem.unselected();
                this._selectedItem = null;
            }
            this._state = cc.MENU_STATE_WAITING;
        }
        cc.Node.prototype.onExit.call(this);
    },
    /**
     * only use for jsbinding
     * @param value
     */
    setOpacityModifyRGB: function (value) {
    },
    /**
     * only use for jsbinding
      * @returns {boolean}
     */
    isOpacityModifyRGB: function () {
        return false;
    },

    _itemForTouch: function (touch) {
        var touchLocation = touch.getLocation();
        var itemChildren = this._children, locItemChild;
        if (itemChildren && itemChildren.length > 0) {
            for (var i = itemChildren.length - 1; i >= 0; i--) {
                locItemChild = itemChildren[i];
                if (locItemChild.isVisible() && locItemChild.isEnabled()) {
                    var local = locItemChild.convertToNodeSpace(touchLocation);
                    var r = locItemChild.rect();
                    r.x = 0;
                    r.y = 0;
                    if (cc.rectContainsPoint(r, local))
                        return locItemChild;
                }
            }
        }
        return null;
    }
});

var _p = cc.Menu.prototype;

// Extended properties
/** @expose */
_p.enabled;

/**
 * create a new menu
 * @deprecated  since v3.0, please use new cc.Menu(menuitem1, menuitem2, menuitem3) to create a new menu
 * @param {...cc.MenuItem|null} menuItems
 * todo: need to use new
 * @return {cc.Menu}
 */
cc.Menu.create = function (menuItems) {
    var argc = arguments.length;
    if ((argc > 0) && (arguments[argc - 1] == null))
        cc.log("parameters should not be ending with null in Javascript");

    var ret;
    if (argc === 0)
        ret = new cc.Menu();
    else if (argc === 1)
        ret = new cc.Menu(menuItems);
    else
        ret = new cc.Menu(Array.prototype.slice.call(arguments, 0));
    return ret;
};
