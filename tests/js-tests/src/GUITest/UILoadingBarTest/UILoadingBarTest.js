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

var UILoadingBarTest = UIScene.extend({
    _count: 0,
    _loadingBar:null,
    ctor: function () {
        this._super();
        this._count = 0;
    },
    init: function () {
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();
            //init text
            this._topDisplayLabel.setString("");
            this._bottomDisplayLabel.setString("LoadingBar");

            this.createLoadingBar();

            this.scheduleUpdate();
            return true;
        }
        return false;
    },
    createLoadingBar: function () {
        // override me
    },
    update: function (dt) {
        this._count++;
        if (this._count > 100) {
            this._count = 0;
        }

        this._loadingBar && this._loadingBar.setPercent(this._count);
    },

    previousCallback: function (sender, type) {
        this.unscheduleUpdate();
        this._super(sender, type)
    },

    restartCallback: function (sender, type) {
        this.unscheduleUpdate();
        this._super(sender, type)
    },

    nextCallback: function (sender, type) {
        this.unscheduleUpdate();
        this._super(sender, type)
    }
});

var UILoadingBarTest_Left = UILoadingBarTest.extend({
    createLoadingBar: function () {
        var widgetSize = this._widget.getContentSize();
        var loadingBar = new ccui.LoadingBar();
        loadingBar.setName("LoadingBar");
        loadingBar.loadTexture("ccs-res/cocosui/sliderProgress.png");
        loadingBar.setPercent(0);
        loadingBar.x = widgetSize.width / 2;
        loadingBar.y = widgetSize.height / 2 + loadingBar.height / 4;
        this._mainNode.addChild(loadingBar);
        this._loadingBar = loadingBar;
    }
});

var UILoadingBarTest_Right = UILoadingBarTest.extend({
    createLoadingBar: function () {
        var widgetSize = this._widget.getContentSize();
        var loadingBar = new ccui.LoadingBar();
        loadingBar.setName("LoadingBar");
        loadingBar.loadTexture("ccs-res/cocosui/sliderProgress.png");
        loadingBar.setDirection(ccui.LoadingBar.TYPE_RIGHT);
        loadingBar.setPercent(0);
        loadingBar.x = widgetSize.width / 2;
        loadingBar.y = widgetSize.height / 2 + loadingBar.height / 4;
        this._mainNode.addChild(loadingBar);
        this._loadingBar = loadingBar;
    }
});

var UILoadingBarTest_Fix = UILoadingBarTest.extend({
    createLoadingBar: function () {
        var widgetSize = this._widget.getContentSize();
        var loadingBar = new ccui.LoadingBar();
        loadingBar.setName("LoadingBar");
        loadingBar.loadTexture("ccs-res/cocosui/sliderProgress.png");
        loadingBar.setDirection(ccui.LoadingBar.TYPE_RIGHT);
        loadingBar.setPercent(40);
        loadingBar.x = widgetSize.width / 2;
        loadingBar.y = widgetSize.height / 2 + loadingBar.height / 4;
        this._mainNode.addChild(loadingBar);
        this._loadingBar = null;
    }
});

var UILoadingBarTest_Left_Scale9 = UILoadingBarTest.extend({
    createLoadingBar: function () {
        var widgetSize = this._widget.getContentSize();
        var loadingBar = new ccui.LoadingBar();
        loadingBar.setName("LoadingBar");
        loadingBar.setScale9Enabled(true);
        loadingBar.loadTexture("ccs-res/cocosui/slider_bar_active_9patch.png");
        loadingBar.setCapInsets(cc.rect(0, 0, 0, 0));
        loadingBar.setContentSize(cc.size(300, 30));
        loadingBar.setPercent(0);
        loadingBar.x = widgetSize.width / 2;
        loadingBar.y = widgetSize.height / 2 + loadingBar.height / 4;
        this._mainNode.addChild(loadingBar);
        this._loadingBar = loadingBar;
    }
});

var UILoadingBarTest_Right_Scale9 = UILoadingBarTest.extend({
    createLoadingBar: function () {
        var widgetSize = this._widget.getContentSize();
        var loadingBar = new ccui.LoadingBar();
        loadingBar.setName("LoadingBar");
        loadingBar.setScale9Enabled(true);
        loadingBar.loadTexture("ccs-res/cocosui/slider_bar_active_9patch.png");
        loadingBar.setCapInsets(cc.rect(0, 0, 0, 0));
        loadingBar.setContentSize(cc.size(300, 30));
        loadingBar.setDirection(ccui.LoadingBar.TYPE_RIGHT);
        loadingBar.setPercent(0);
        loadingBar.x = widgetSize.width / 2;
        loadingBar.y = widgetSize.height / 2 + loadingBar.height / 4;
        this._mainNode.addChild(loadingBar);
        this._loadingBar = loadingBar;
    }
});

var UILoadingBarTest_Fix_Scale9 = UILoadingBarTest.extend({
    createLoadingBar: function () {
        var widgetSize = this._widget.getContentSize();
        var loadingBar = new ccui.LoadingBar();
        loadingBar.setName("LoadingBar");
        loadingBar.setScale9Enabled(true);
        loadingBar.loadTexture("ccs-res/cocosui/slider_bar_active_9patch.png");
        loadingBar.setPercent(40);
        loadingBar.setCapInsets(cc.rect(0, 0, 0, 0));
        loadingBar.setContentSize(cc.size(300, 30));
        loadingBar.setDirection(ccui.LoadingBar.TYPE_RIGHT);
        loadingBar.x = widgetSize.width / 2;
        loadingBar.y = widgetSize.height / 2 + loadingBar.height / 4;
        this._mainNode.addChild(loadingBar);
        this._loadingBar = null;
    }
});