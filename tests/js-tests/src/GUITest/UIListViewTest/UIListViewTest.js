/****************************************************************************
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

var UIListViewTest_Vertical = UIScene.extend({
    init: function () {
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();
            var background = this._widget.getChildByName("background_Panel");
            var backgroundSize = background.getContentSize();

            this._topDisplayLabel.setString("Scroll listview is disabled.");
            this._topDisplayLabel.x = widgetSize.width / 2.0;
            this._topDisplayLabel.y = widgetSize.height / 2.0 + this._topDisplayLabel.height * 1.5;

            this._array = [];
            for (var i = 0; i < 20; ++i) {
                this._array.push("item_" + i);
            }

            // Create the list view
            var listView = new ccui.ListView();
            // set list view ex direction
            listView.setDirection(ccui.ScrollView.DIR_NONE);
            listView.setTouchEnabled(false);
            listView.setBounceEnabled(false);
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
            default_item.width = listView.width;
            default_button.x = default_item.width / 2;
            default_button.y = default_item.height / 2;
            default_item.addChild(default_button);

            // set model
            listView.setItemModel(default_item);

            // add default item
            var count = this._array.length;
            for (var i = 0; i < count / 4; ++i) {
                listView.pushBackDefaultItem();
            }
            // insert default item
            for (var i = 0; i < count / 4; ++i) {
                listView.insertDefaultItem(0);
            }

            // add custom item
            for (var i = 0; i < count / 4; ++i) {
                var custom_button = new ccui.Button();
                custom_button.setName("TextButton");
                custom_button.setTouchEnabled(true);
                custom_button.setScale9Enabled(true);
                custom_button.loadTextures("ccs-res/cocosui/button.png", "ccs-res/cocosui/buttonHighlighted.png", "");
                custom_button.setContentSize(default_button.getContentSize());

                var custom_item = new ccui.Layout();
                custom_item.setContentSize(custom_button.getContentSize());
                custom_item.width = listView.width;
                custom_button.x = custom_item.width / 2;
                custom_button.y = custom_item.height / 2;
                custom_item.addChild(custom_button);

                listView.pushBackCustomItem(custom_item);
            }
            // insert custom item
            var items_count = listView.getItems().length;
            for (var i = 0; i < count / 4; ++i) {
                var custom_button = new ccui.Button();
                custom_button.setName("TextButton");
                custom_button.setTouchEnabled(true);
                custom_button.setScale9Enabled(true);
                custom_button.loadTextures("ccs-res/cocosui/button.png", "ccs-res/cocosui/buttonHighlighted.png", "");
                custom_button.setContentSize(default_button.getContentSize());

                var custom_item = new ccui.Layout();
                custom_item.setContentSize(custom_button.getContentSize());
                custom_item.width = listView.width;
                custom_button.x = custom_item.width / 2;
                custom_button.y = custom_item.height / 2;
                custom_item.addChild(custom_button);

                listView.insertCustomItem(custom_item, items_count);
            }

            // set item data
            items_count = listView.getItems().length;
            for (var i = 0; i < items_count; ++i) {
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

            return true;
        }

        return false;
    },

    selectedItemEvent: function (sender, type) {
        switch (type) {
            case ccui.ListView.EVENT_SELECTED_ITEM:
                var listViewEx = sender;
                cc.log("select child index = " + listViewEx.getCurSelectedIndex());
                break;

            default:
                break;
        }
    }
});

var UIListViewTest_Horizontal = UIScene.extend({
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
