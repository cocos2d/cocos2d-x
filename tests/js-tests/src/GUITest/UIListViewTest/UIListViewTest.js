/****************************************************************************
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

var UIListViewTest_Vertical = UIMainLayer.extend({
    _spawnCount: 8,
    _totalCount: 100,
    _bufferZone: 50,
    _updateInterval: 0.01,
    _updateTimer: 0,
    _lastContentPosY: 0,
    _reuseItemOffset: 0,
    _initializeListSize: false,
    init: function () {
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();
            var background = this._widget.getChildByName("background_Panel");
            var backgroundSize = background.getContentSize();

            this._topDisplayLabel.setString("We only create 8 item templates here.");
            this._topDisplayLabel.x = widgetSize.width / 2.0;
            this._topDisplayLabel.y = widgetSize.height / 2.0 + this._topDisplayLabel.height * 1.5;

            this._array = [];
            for (var i = 0; i < this._totalCount; ++i) {
                this._array.push("item_" + i);
            }

            // Create the list view
            this.listView = new ccui.ListView();
            // set list view ex direction
            this.listView.setDirection(ccui.ScrollView.DIR_VERTICAL);
            this.listView.setTouchEnabled(true);
            this.listView.setBounceEnabled(true);
            this.listView.setBackGroundImage("ccs-res/cocosui/green_edit.png");
            this.listView.setBackGroundImageScale9Enabled(true);
            this.listView.setContentSize(cc.size(240, 130));
            this.listView.x = (widgetSize.width - backgroundSize.width) / 2 + (backgroundSize.width - this.listView.width) / 2;
            this.listView.y = (widgetSize.height - backgroundSize.height) / 2 + (backgroundSize.height - this.listView.height) / 2;
            this.listView.addEventListener(this.selectedItemEvent, this);
            this._mainNode.addChild(this.listView);

            // create model
            var default_button = new ccui.Button();
            default_button.setName("TextButton");
            default_button.setTouchEnabled(true);
            default_button.loadTextures("ccs-res/cocosui/backtotoppressed.png", "ccs-res/cocosui/backtotopnormal.png", "");

            var default_item = new ccui.Layout();
            default_item.setTouchEnabled(true);
            default_item.setContentSize(default_button.getContentSize());
            default_item.width = this.listView.width;
            default_button.x = default_item.width / 2;
            default_button.y = default_item.height / 2;
            default_item.addChild(default_button);

            // set model
            this.listView.setItemModel(default_item);
            // set all items layout gravity
            this.listView.setGravity(ccui.ListView.GRAVITY_CENTER_VERTICAL);

            for(i = 0; i < this._totalCount; ++i) {
                if (i < this._spawnCount) {
                    var item = default_item.clone();
                    item.setTag(i);
                    var btn = item.getChildByName('TextButton');
                    btn.setTitleText(this._array[i]);
                    this.listView.pushBackCustomItem(item);
                }
            }

            var spacing = 4;
            this.listView.setItemsMargin(spacing);
            this._itemTemplateHeight = default_item.getContentSize().height;
            this._reuseItemOffset = (this._itemTemplateHeight + spacing) * this._spawnCount;

            this.scheduleUpdate();
            return true;
        }
        return false;
    },

    onEnter: function() {
        cc.Node.prototype.onEnter.call(this);
        //we must call foreceDoLayout in onEnter method in h5.
        this.listView.forceDoLayout();
        var totalHeight = this._itemTemplateHeight * this._totalCount + (this._totalCount - 1) * 4;
        this.listView.getInnerContainer().setContentSize(cc.size(this.listView.getInnerContainerSize().width, totalHeight));
        this.listView.jumpToTop();
    },

    getItemPositionYInView: function(item) {
        var worldPos = item.getParent().convertToWorldSpaceAR(item.getPosition());
        var viewPos = this.listView.convertToNodeSpaceAR(worldPos);
        return viewPos.y;
    },

    updateItem: function(itemID, templateID) {
        var itemTemplate = this.listView.getItems()[templateID];
        var btn = itemTemplate.getChildByName('TextButton');
        itemTemplate.setTag(itemID);
        btn.setTitleText(this._array[itemID]);
    },

    update: function(dt){
        this._updateTimer += dt;
        if (this._updateTimer < this._updateInterval) {
            return;
        }
        this._updateTimer = 0;

        //here 4 is the spacing between items
        var totalHeight = this._itemTemplateHeight * this._totalCount + (this._totalCount - 1) * 4;
        var listViewHeight = this.listView.getContentSize().height;
        var items = this.listView.getItems();
        var isDown = this.listView.getInnerContainer().getPosition().y < this._lastContentPosY;

        for (var i = 0; i < this._spawnCount && i < this._totalCount; ++i) {
            var item = items[i];
            var itemPos = this.getItemPositionYInView(item);
            if (isDown) {
                if (itemPos < -this._bufferZone && item.getPosition().y + this._reuseItemOffset < totalHeight) {
                    var itemID = item.getTag() - items.length;
                    item.setPositionY(item.getPositionY() + this._reuseItemOffset);
                    this.updateItem(itemID, i);
                }
            } else {
                if (itemPos > this._bufferZone + listViewHeight && item.getPositionY() - this._reuseItemOffset >= 0){
                    item.setPositionY(item.getPositionY() - this._reuseItemOffset);
                    itemID = item.getTag() + items.length;
                    this.updateItem(itemID, i);
                }
            }
        }

        this._lastContentPosY = this.listView.getInnerContainer().getPosition().y;
    },

    selectedItemEvent: function (sender, type) {
        switch (type) {
            case ccui.ListView.EVENT_SELECTED_ITEM:
                var listViewEx = sender;
                var item = listViewEx.getItem(listViewEx.getCurSelectedIndex());
                cc.log("select child index = " + item.getTag());
                break;

            default:
                break;
        }
    }
});

var UIListViewTest_Horizontal = UIMainLayer.extend({
    _array: null,
    init: function () {
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();
            var background = this._widget.getChildByName("background_Panel");
            var backgroundSize = background.getContentSize();

            // create list view ex data
            this._array = [];
            var i;
            for (i = 0; i < 20; ++i) {
                this._array.push("item_" + i);
            }

            // Create the list view
            var listView = new ccui.ListView();
            // set list view ex direction
            listView.setDirection(ccui.ScrollView.DIR_HORIZONTAL);
            listView.setTouchEnabled(true);
            listView.setBounceEnabled(true);
            listView.setBackGroundImage("ccs-res/cocosui/green_edit.png");
            listView.setBackGroundImageScale9Enabled(true);
            listView.setContentSize(cc.size(240, 130));
            listView.x = (widgetSize.width - backgroundSize.width) / 2 + (backgroundSize.width - listView.width) / 2;
            listView.y = (widgetSize.height - backgroundSize.height) / 2 + (backgroundSize.height - listView.height) / 2;
            listView.addEventListener(this.selectedItemEvent, this);
            this._mainNode.addChild(listView);

            // create model
            var default_button = new ccui.Button();
            default_button.setName("TextButton");
            default_button.setTouchEnabled(true);
            default_button.loadTextures("ccs-res/cocosui/backtotoppressed.png", "ccs-res/cocosui/backtotopnormal.png", "");

            var default_item = new ccui.Layout();
            default_item.setTouchEnabled(true);
            default_item.setContentSize(default_button.getContentSize());
            default_button.x = default_item.width / 2;
            default_button.y = default_item.height / 2;
            default_item.addChild(default_button);

            // set model
            listView.setItemModel(default_item);

            // add default item
            var count = this._array.length;
            for (i = 0; i < count / 4; ++i) {
                listView.pushBackDefaultItem();
            }
            // insert default item
            for (i = 0; i < count / 4; ++i) {
                listView.insertDefaultItem(0);
            }

            // add custom item
            for (i = 0; i < count / 4; ++i) {
                var custom_button = new ccui.Button();
                custom_button.setName("TextButton");
                custom_button.setTouchEnabled(true);
                custom_button.setScale9Enabled(true);
                custom_button.loadTextures("ccs-res/cocosui/button.png", "ccs-res/cocosui/buttonHighlighted.png", "");
                custom_button.setContentSize(default_button.getContentSize());

                var custom_item = new ccui.Layout();
                custom_item.setContentSize(custom_button.getContentSize());
                custom_button.x = custom_item.width / 2;
                custom_button.y = custom_item.height / 2;
                custom_item.addChild(custom_button);

                listView.pushBackCustomItem(custom_item);
            }
            // insert custom item
            var items_count = listView.getItems().length;
            for (i = 0; i < count / 4; ++i) {
                var custom_button = new ccui.Button();
                custom_button.setName("TextButton");
                custom_button.setTouchEnabled(true);
                custom_button.setScale9Enabled(true);
                custom_button.loadTextures("ccs-res/cocosui/button.png", "ccs-res/cocosui/buttonHighlighted.png", "");
                custom_button.setContentSize(default_button.getContentSize());

                var custom_item = new ccui.Layout();
                custom_item.setContentSize(custom_button.getContentSize());
                custom_button.x = custom_item.width / 2;
                custom_button.y = custom_item.height / 2;
                custom_item.addChild(custom_button);

                listView.insertCustomItem(custom_item, items_count);
            }

            // set item data
            items_count = listView.getItems().length;
            for (i = 0; i < items_count; ++i) {
                var item = listView.getItem(i);
                var button = item.getChildByName("TextButton");
                var index = listView.getIndex(item);
                button.setTitleText(this._array[index]);
            }

            // remove last item
            listView.removeLastItem();

            // remove item by index
            items_count = listView.getItems().length;
            listView.removeItem(items_count - 1);

            // set all items layout gravity
            listView.setGravity(ccui.ListView.GRAVITY_CENTER_VERTICAL);

            // set items margin
            listView.setItemsMargin(2);
            return true;
        }
        return false;
    },

    selectedItemEvent: function (sender, type) {
        switch (type) {
            case ccui.ListView.EVENT_SELECTED_ITEM:
                cc.log("select child index = " + sender.getCurSelectedIndex());
                break;
            default:
                break;
        }
    }
});

var UIListViewTest_TouchIntercept = UIMainLayer.extend({
    init: function () {
        if(this._super()) {
            var widgetSize = this._widget.getContentSize();
            var background = this._widget.getChildByName("background_Panel");
            var backgroundSize = background.getContentSize();

            this._topDisplayLabel.setString("TouchIntercept");
            this._topDisplayLabel.x = widgetSize.width / 2.0;
            this._topDisplayLabel.y = widgetSize.height / 2.0 + this._topDisplayLabel.height * 1.5;
            this._bottomDisplayLabel.setString("ListView Disable Touch");
            this._bottomDisplayLabel.x = widgetSize.width / 2;
            this._bottomDisplayLabel.y = widgetSize.height / 2 - this._bottomDisplayLabel.height * 3;

            // Create the list view
            var listView = new ccui.ListView();
            // set list view ex direction
            listView.setDirection(ccui.ScrollView.DIR_NONE);
            listView.setBounceEnabled(true);
            listView.setTouchEnabled(false);
            listView.setBackGroundImage("ccs-res/cocosui/green_edit.png");
            listView.setBackGroundImageScale9Enabled(true);
            listView.setContentSize(cc.size(240, 130));
            listView.x = (widgetSize.width - backgroundSize.width) / 2 + (backgroundSize.width - listView.width) / 2;
            listView.y = (widgetSize.height - backgroundSize.height) / 2 + (backgroundSize.height - listView.height) / 2;
            this._mainNode.addChild(listView);

            // create model
            var default_button = new ccui.Button();
            default_button.setName("Title Button");
            default_button.loadTextures("ccs-res/cocosui/backtotoppressed.png", "ccs-res/cocosui/backtotopnormal.png", "");

            var default_item = new ccui.Layout();
            default_item.setTouchEnabled(true);
            default_item.setContentSize(default_button.getContentSize());
            default_item.width = listView.width;
            default_button.x = default_item.width / 2;
            default_button.y = default_item.height / 2;
            default_item.addChild(default_button);

            // set model
            listView.setItemModel(default_item);
            listView.pushBackDefaultItem();
            listView.pushBackDefaultItem();
            listView.pushBackDefaultItem();

            return true;
        }
        return false;
    }
});

var UIListViewTest_ScrollToItem = UIMainLayer.extend({
    _nextIndex: 0,
    init: function () {
        if(this._super()) {
            var widgetSize = this._widget.getContentSize();
            var background = this._widget.getChildByName("background_Panel");
            var backgroundSize = background.getContentSize();

            this._topDisplayLabel.setString("");
            this._topDisplayLabel.x = widgetSize.width / 2.0;
            this._topDisplayLabel.y = widgetSize.height / 2.0 + this._topDisplayLabel.height * 1.5;
            this._bottomDisplayLabel.setString("");
            this._bottomDisplayLabel.x = widgetSize.width / 2;
            this._bottomDisplayLabel.y = widgetSize.height / 2 - this._bottomDisplayLabel.height * 3;

            // Create the list view
            var listView = new ccui.ListView();
            // set list view ex direction
            listView.setDirection(this._getListViewDirection());
            listView.setBounceEnabled(true);
            listView.setBackGroundImage("ccs-res/cocosui/green_edit.png");
            listView.setBackGroundImageScale9Enabled(true);
            listView.setContentSize(widgetSize.width / 2, widgetSize.height / 2);
            listView.setScrollBarPositionFromCorner(cc.p(7, 7));
            listView.setItemsMargin(2.0);

            listView.x = (widgetSize.width - backgroundSize.width) / 2 + (backgroundSize.width - listView.width) / 2;
            listView.y = (widgetSize.height - backgroundSize.height) / 2 + (backgroundSize.height - listView.height) / 2;
            this._mainNode.addChild(listView);

            {
                var pNode = new cc.DrawNode();

                var center = cc.p(widgetSize.width / 2, widgetSize.height / 2);
                if(this._getListViewDirection() == ccui.ScrollView.DIR_HORIZONTAL)
                {
                    var halfY = 110;
                    pNode.drawSegment(cc.p(center.x, center.y - halfY), cc.p(center.x, center.y + halfY), 2, cc.color(0, 0, 0, 255));
                }
                else
                {
                    var halfX = 150;
                    pNode.drawSegment(cc.p(center.x - halfX, center.y), cc.p(center.x + halfX, center.y), 2, cc.color(0, 0, 0, 255));
                }
                pNode.setContentSize(listView.getContentSize());
                this._mainNode.addChild(pNode);
            }
            var NUMBER_OF_ITEMS = 31;
            // Button
            var pButton = new ccui.Button("ccs-res/cocosui/backtotoppressed.png", "ccs-res/cocosui/backtotopnormal.png");
            pButton.setAnchorPoint(cc.p(0, 0.5));
            pButton.setScale(0.8);
            pButton.setPosition(cc.pAdd(cc.p(widgetSize.width / 2, widgetSize.height / 2), cc.p(120, -60)));
            pButton.setTitleText("Go to '" +this._nextIndex + "'");
            pButton.addClickEventListener(function(pButton) {
                listView.scrollToItem(this._nextIndex, cc.p(0.5, 0.5), cc.p(0.5, 0.5));
                this._nextIndex = (this._nextIndex + Math.floor(NUMBER_OF_ITEMS / 2)) % NUMBER_OF_ITEMS;
                pButton.setTitleText("Go to '" + this._nextIndex+ "'");
            }.bind(this));
            this._mainNode.addChild(pButton);

            // Add list items

            var default_button = new ccui.Button();
            default_button.setName("TextButton");
            default_button.setTouchEnabled(true);
            default_button.loadTextures("ccs-res/cocosui/backtotoppressed.png", "ccs-res/cocosui/backtotopnormal.png", "");

            var default_item = new ccui.Layout();
            default_item.setTouchEnabled(true);
            default_item.setContentSize(default_button.getContentSize());
            default_button.x = default_item.width / 2;
            default_button.y = default_item.height / 2;
            default_item.addChild(default_button);

            // set model
            listView.setItemModel(default_item);

            // Add list items
            for (var i = 0; i < NUMBER_OF_ITEMS; ++i)
            {
                var item = default_item.clone();
                item.getChildByName("TextButton").setTitleText("Button-" + i);
                listView.pushBackCustomItem(item);
            }

            return true;
        }
        return false;
    },
    _getListViewDirection: function()
    {

    }
});

var UIListViewTest_ScrollToItemVertical = UIListViewTest_ScrollToItem.extend({
    _getListViewDirection: function()
    {
        return ccui.ScrollView.DIR_VERTICAL;
    }
});

var UIListViewTest_ScrollToItemHorizontal = UIListViewTest_ScrollToItem.extend({
    _getListViewDirection: function()
    {
        return ccui.ScrollView.DIR_HORIZONTAL;
    }
});

var UIListViewTest_Magnetic = UIMainLayer.extend({
    _listView: null,
    init: function () {
        if(this._super()) {
            var widgetSize = this._widget.getContentSize();
            var background = this._widget.getChildByName("background_Panel");
            var backgroundSize = background.getContentSize();

            this._topDisplayLabel.setString("1");
            this._topDisplayLabel.setFontSize(14);
            this._topDisplayLabel.x = widgetSize.width / 2.0;
            this._topDisplayLabel.y = widgetSize.height / 2 + 90;
            this._bottomDisplayLabel.setString("");
            this._bottomDisplayLabel.x = widgetSize.width / 2;
            this._bottomDisplayLabel.y = widgetSize.height / 2 - this._bottomDisplayLabel.height * 3;

            // Create the list view
            this._listView = new ccui.ListView();
            // set list view ex direction
            this._listView.setDirection(this._getListViewDirection());
            this._listView.setTouchEnabled(true);
            this._listView.setBounceEnabled(true);
            this._listView.setBackGroundImage("ccs-res/cocosui/green_edit.png");
            this._listView.setBackGroundImageScale9Enabled(true);
            this._listView.setContentSize(widgetSize.width / 2, widgetSize.height / 2);
            this._listView.setScrollBarPositionFromCorner(cc.p(7, 7));
            this._listView.setItemsMargin(2.0);
            this._listView.setAnchorPoint(cc.p(0.5 ,0.5));

            this._listView.x = widgetSize.width / 2;
            this._listView.y = widgetSize.height / 2;

            this._listView.setGravity(ccui.ListView.GRAVITY_CENTER_VERTICAL);

            this._mainNode.addChild(this._listView);

            {
                var pNode = new cc.DrawNode();

                var center = cc.p(widgetSize.width / 2, widgetSize.height / 2);
                if(this._getListViewDirection() == ccui.ScrollView.DIR_HORIZONTAL)
                {
                    var halfY = 110;
                    pNode.drawSegment(cc.p(center.x, center.y - halfY), cc.p(center.x, center.y + halfY), 1, cc.color(0, 0, 0, 255));
                }
                else
                {
                    var halfX = 150;
                    pNode.drawSegment(cc.p(center.x - halfX, center.y), cc.p(center.x + halfX, center.y), 1, cc.color(0, 0, 0, 255));
                }
                pNode.setContentSize(this._listView.getContentSize());
                this._mainNode.addChild(pNode);
            }

            // Initial magnetic type
            this._listView.setMagneticType(ccui.ListView.MAGNETIC_NONE);
            this._topDisplayLabel.setString("MagneticType - NONE");

            // Magnetic change button
            var pButton = new ccui.Button("ccs-res/cocosui/backtotoppressed.png", "ccs-res/cocosui/backtotopnormal.png");
            pButton.setAnchorPoint(cc.p(0.5, 0.5));
            pButton.setScale(0.8);
            pButton.setPosition(cc.pAdd(cc.p(widgetSize.width / 2, widgetSize.height / 2), cc.p(130, -60)));
            pButton.setTitleText("Next Magnetic");
            pButton.addClickEventListener(function() {
                var eCurrentType = this._listView.getMagneticType();
                var eNextType;
                var sString;
                if(eCurrentType == ccui.ListView.MAGNETIC_NONE)
                {
                    eNextType = ccui.ListView.MAGNETIC_CENTER;
                    sString = "CENTER";
                }
                else if(eCurrentType == ccui.ListView.MAGNETIC_CENTER)
                {
                    eNextType = ccui.ListView.MAGNETIC_BOTH_END;
                    sString = "BOTH_END";
                }
                else if(eCurrentType == ccui.ListView.MAGNETIC_BOTH_END)
                {
                    if(this._getListViewDirection() == ccui.ScrollView.DIR_HORIZONTAL)
                    {
                        eNextType = ccui.ListView.MAGNETIC_LEFT;
                        sString = "LEFT";
                    }
                    else
                    {
                        eNextType = ccui.ListView.MAGNETIC_TOP;
                        sString = "TOP";
                    }
                }
                else if(eCurrentType == ccui.ListView.MAGNETIC_LEFT)
                {
                    eNextType = ccui.ListView.MAGNETIC_RIGHT;
                    sString = "RIGHT";
                }
                else if(eCurrentType == ccui.ListView.MAGNETIC_RIGHT)
                {
                    eNextType = ccui.ListView.MAGNETIC_NONE;
                    sString = "NONE";
                }
                else if(eCurrentType == ccui.ListView.MAGNETIC_TOP)
                {
                    eNextType = ccui.ListView.MAGNETIC_BOTTOM;
                    sString = "BOTTOM";
                }
                else if(eCurrentType == ccui.ListView.MAGNETIC_BOTTOM)
                {
                    eNextType = ccui.ListView.MAGNETIC_NONE;
                    sString = "NONE";
                }
                this._listView.setMagneticType(eNextType);

                this._topDisplayLabel.setString("MagneticType - " + sString);
            }.bind(this));
            this._mainNode.addChild(pButton);


            // Add list items
            for (var i = 0; i < 40; ++i)
            {
                var button = new ccui.Button("ccs-res/cocosui/button.png", "ccs-res/cocosui/buttonHighlighted.png");
                button.setTitleText("Button-" + i);
                button.setContentSize(100, 70);
                button.setScale9Enabled(true);
                this._listView.pushBackCustomItem(button);
            }

            return true;
        }
        return false;
    },

    _getListViewDirection: function()
    {

    }
});

var UIListViewTest_MagneticVertical = UIListViewTest_Magnetic.extend({
    _getListViewDirection: function()
    {
        return ccui.ScrollView.DIR_VERTICAL;
    }
});

var UIListViewTest_MagneticHorizontal = UIListViewTest_Magnetic.extend({
    _getListViewDirection: function()
    {
        return ccui.ScrollView.DIR_HORIZONTAL;
    }
});