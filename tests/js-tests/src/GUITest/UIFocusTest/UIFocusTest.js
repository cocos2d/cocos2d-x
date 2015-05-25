/****************************************************************************
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

var UIFocusTestBase = UIScene.extend({
    _dpadMenu: null,
    _firstFocusedWidget: null,
    _eventListener:null,

    init: function(){
        if (this._super()) {
            var root = this._mainNode.getChildByTag(81);
            var background = root.getChildByName("background_Panel");
            background.removeFromParent(true);

            this._dpadMenu = new cc.Menu();

            cc.MenuItemFont.setFontSize(20);
            var winSize = cc.director.getVisibleSize();
            var leftItem = new cc.MenuItemFont("Left", this.onLeftKeyPressed, this);
            leftItem.setPosition(winSize.width - 100, winSize.height/2);
            this._dpadMenu.addChild(leftItem);

            var rightItem = new cc.MenuItemFont("Right", this.onRightKeyPressed, this);
            rightItem.setPosition(winSize.width - 30, winSize.height/2);
            this._dpadMenu.addChild(rightItem);

            var upItem = new cc.MenuItemFont("Up", this.onUpKeyPressed, this);
            upItem.setPosition(winSize.width - 60, winSize.height/2 + 50);
            this._dpadMenu.addChild(upItem);

            var downItem = new cc.MenuItemFont("Down", this.onDownKeyPressed, this);
            downItem.setPosition(winSize.width - 60, winSize.height/2 - 50);
            this._dpadMenu.addChild(downItem);

            this._dpadMenu.setPosition(0, 0);
            this.addChild(this._dpadMenu);

            //call this method to enable Dpad focus navigation
            ccui.Widget.enableDpadNavigation(true);

            this._eventListener = cc.EventListener.create({
                event: cc.EventListener.FOCUS,                            //TODO Need add focus event in JSB
                onFocusChanged: this.onFocusChanged.bind(this)
            });
            cc.eventManager.addListener(this._eventListener, 1);
            return true;
        }
        return false;
    },

    onLeftKeyPressed: function(){
        var event = new cc.EventKeyboard(cc.KEY.dpadLeft, false);
        cc.eventManager.dispatchEvent(event);
    },
    onRightKeyPressed: function(){
        var event = new cc.EventKeyboard(cc.KEY.dpadRight, false);
        cc.eventManager.dispatchEvent(event);
    },
    onUpKeyPressed: function(){
        var event = new cc.EventKeyboard(cc.KEY.dpadUp, false);
        cc.eventManager.dispatchEvent(event);
    },
    onDownKeyPressed: function(){
        var event = new cc.EventKeyboard(cc.KEY.dpadDown, false);
        cc.eventManager.dispatchEvent(event);
    },
    onFocusChanged: function(widgetLostFocus, widgetGetFocus){
        if (widgetGetFocus && widgetGetFocus.isFocusEnabled())
            widgetGetFocus.setColor(cc.color.RED);

        if (widgetLostFocus && widgetLostFocus.isFocusEnabled())
            widgetLostFocus.setColor(cc.color.WHITE);

        if (widgetLostFocus && widgetGetFocus)
            cc.log("on focus change, %d widget get focus, %d widget lose focus", widgetGetFocus.getTag(),  widgetLostFocus.getTag());
    },

    onImageViewClicked: function(widget, touchType){
        if (touchType == ccui.Widget.TOUCH_ENDED) {
            if (widget.isFocusEnabled()) {
                widget.setFocusEnabled(false);
                widget.setColor(cc.color.YELLOW);
            }else{
                widget.setFocusEnabled(true);
                widget.setColor(cc.color.WHITE);
            }
        }
    }
});

var UIFocusTestHorizontal = UIFocusTestBase.extend({
    _horizontalLayout: null,
    _loopText: null,

    init: function(){
        if (this._super()) {
            var winSize = cc.director.getVisibleSize();

            this._horizontalLayout = new ccui.HBox();
            this._horizontalLayout.setPosition(winSize.height/2 - 20, winSize.height/2 + 40);
            this.addChild(this._horizontalLayout);

            this._horizontalLayout.setFocused(true);
            this._horizontalLayout.setLoopFocus(true);
            this._horizontalLayout.setTag(100);
            this._firstFocusedWidget = this._horizontalLayout;

            var count = 3;
            for (var i=0; i<count; ++i) {
                var w = new ccui.ImageView("ccs-res/cocosui/scrollviewbg.png");
                w.setTouchEnabled(true);
                w.setTag(i);
                w.addTouchEventListener(this.onImageViewClicked, this);
                this._horizontalLayout.addChild(w);
            }

            this._loopText = new ccui.Text("loop enabled", "Arial", 20);
            this._loopText.setPosition(winSize.width / 2, winSize.height - 50);
            this._loopText.setColor(cc.color.GREEN);
            this.addChild(this._loopText);

            var btn = new ccui.Button("ccs-res/cocosui/switch-mask.png");
            btn.setTitleText("Toggle Loop");
            btn.setPosition(60, winSize.height - 50);
            btn.setTitleColor(cc.color.RED);
            btn.addTouchEventListener(this.toggleFocusLoop,this);
            this.addChild(btn);
            return true;
        }
        return false;
    },

    toggleFocusLoop: function( ref, touchType){
        if (touchType == ccui.Widget.TOUCH_ENDED) {
            this._horizontalLayout.setLoopFocus(!this._horizontalLayout.isLoopFocus());
            if (this._horizontalLayout.isLoopFocus()) {
                this._loopText.setString("loop enabled");
            } else {
                this._loopText.setString("loop disabled");
            }
        }
    }
});

var UIFocusTestVertical = UIFocusTestBase.extend({
    _verticalLayout: null,
    _loopText: null,

    init: function(){
        if (this._super()) {
            var winSize = cc.director.getVisibleSize();

            this._verticalLayout = new ccui.VBox();
            this._verticalLayout.setPosition(winSize.width/2 - 50, winSize.height - 80);
            this.addChild(this._verticalLayout);
            this._verticalLayout.setTag(100);
            //this._verticalLayout.setScale(0.8);

            this._verticalLayout.setFocused(true);
            this._verticalLayout.setLoopFocus(true);
            this._firstFocusedWidget = this._verticalLayout;

            var count = 3;
            for (var i=0; i<count; ++i) {
                var w = new ccui.ImageView("ccs-res/cocosui/scrollviewbg.png");
                w.setTouchEnabled(true);
                w.setTag(i);
                w.addTouchEventListener(this.onImageViewClicked, this);
                this._verticalLayout.addChild(w);
                if (i == 2)
                    w.requestFocus();
            }

            this._loopText = new ccui.Text("loop enabled", "Arial", 20);
            this._loopText.setPosition(winSize.width/2, winSize.height - 50);
            this._loopText.setColor(cc.color.GREEN);
            this.addChild(this._loopText);

            var btn = new ccui.Button("ccs-res/cocosui/switch-mask.png");
            btn.setTitleText("Toggle Loop");
            btn.setPosition(60, winSize.height - 50);
            btn.setTitleColor(cc.color.RED);
            btn.addTouchEventListener(this.toggleFocusLoop, this);
            this.addChild(btn);
            return true;
        }
        return false;
    },

    toggleFocusLoop: function(ref, touchType){
        if (touchType == ccui.Widget.TOUCH_ENDED) {
            this._verticalLayout.setLoopFocus(!this._verticalLayout.isLoopFocus());
            if (this._verticalLayout.isLoopFocus()) {
                this._loopText.setString("loop enabled");
            } else {
                this._loopText.setString("loop disabled");
            }
        }
    }
});

var UIFocusTestNestedLayout1 = UIFocusTestBase.extend({
    _verticalLayout: null,
    _loopText: null,

    init: function(){
        if (this._super()) {
            var winSize = cc.director.getVisibleSize();

            this._verticalLayout = new ccui.VBox();
            this._verticalLayout.setPosition(winSize.width/2 - 100, winSize.height - 100);
            this.addChild(this._verticalLayout);
            //this._verticalLayout.setScale(0.5);

            this._verticalLayout.setFocused(true);
            this._verticalLayout.setLoopFocus(true);
            this._verticalLayout.setTag(100);
            this._firstFocusedWidget = this._verticalLayout;

            var count1 = 1, i, w;
            for (i = 0; i < count1; ++i) {
                w = new ccui.ImageView("ccs-res/cocosui/scrollviewbg.png");
                w.setAnchorPoint(0, 0);
                w.setTouchEnabled(true);
                w.setScaleX(2.5);
                w.setTag(i + count1);
                w.addTouchEventListener(this.onImageViewClicked, this);
                this._verticalLayout.addChild(w);
            }
            //add HBox into VBox
            var hbox = new ccui.HBox();
            hbox.setScale(0.8);
            hbox.setTag(101);
            this._verticalLayout.addChild(hbox);

            var count2 = 2;
            for (i=0; i < count2; ++i) {
                w = new ccui.ImageView("ccs-res/cocosui/scrollviewbg.png");
                w.setAnchorPoint(0,1);
                w.setScaleY(2.0);
                w.setTouchEnabled(true);
                w.setTag(i+count1+count2);
                w.addTouchEventListener(this.onImageViewClicked, this);
                hbox.addChild(w);
            }
            var innerVBox = new ccui.VBox();
            hbox.addChild(innerVBox);
            innerVBox.setTag(102);
//          innerVBox.setPassFocusToChild(false);
//          innerVBox.setFocusEnabled(false);

            var count3 = 2;
            for (i=0; i<count3; ++i) {
                w = new ccui.ImageView("ccs-res/cocosui/scrollviewbg.png");
                w.setTouchEnabled(true);
                w.setTag(i+count1+count2+count3);
                w.addTouchEventListener(this.onImageViewClicked, this);
                innerVBox.addChild(w);
            }
            this._loopText = new ccui.Text("loop enabled", "Arial", 20);
            this._loopText.setPosition(winSize.width/2, winSize.height - 50);
            this._loopText.setColor(cc.color.GREEN);
            this.addChild(this._loopText);

            var btn = new ccui.Button("ccs-res/cocosui/switch-mask.png");
            btn.setTitleText("Toggle Loop");
            btn.setPosition(60, winSize.height - 50);
            btn.setTitleColor(cc.color.RED);
            btn.addTouchEventListener(this.toggleFocusLoop, this);
            this.addChild(btn);
            return true;
        }
        return false;
    },

    toggleFocusLoop: function(ref, touchType){
        if (touchType == ccui.Widget.TOUCH_ENDED) {
            this._verticalLayout.setLoopFocus(!this._verticalLayout.isLoopFocus());
            if (this._verticalLayout.isLoopFocus()) {
                this._loopText.setString("loop enabled");
            }else{
                this._loopText.setString("loop disabled");
            }
        }
    }
});

var UIFocusTestNestedLayout2 = UIFocusTestBase.extend({
    _horizontalLayout: null,
    _loopText: null,

    init: function(){
        if (this._super()) {
            var winSize = cc.director.getVisibleSize();

            this._horizontalLayout = new ccui.HBox();
            this._horizontalLayout.setPosition(winSize.width/2 - 160, winSize.height - 120);
            this.addChild(this._horizontalLayout);
            //this._horizontalLayout.setScale(0.6);

            this._horizontalLayout.setFocused(true);
            this._horizontalLayout.setLoopFocus(true);
            this._horizontalLayout.setTag(100);
            this._firstFocusedWidget = this._horizontalLayout;

            var count1 = 2, i, w;
            for (i=0; i<count1; ++i) {
                w = new ccui.ImageView("ccs-res/cocosui/scrollviewbg.png");
                w.setAnchorPoint(0,1);
                w.setTouchEnabled(true);
                w.setTag(i+count1);
                w.setScaleY(2.4);
                w.addTouchEventListener(this.onImageViewClicked, this);
                this._horizontalLayout.addChild(w);
            }

            //add HBox into VBox
            var vbox = new ccui.VBox();
            vbox.setScale(0.8);
            vbox.setTag(101);
            this._horizontalLayout.addChild(vbox);
            var count2 = 2;
            for (i=0; i < count2; ++i) {
                w = new ccui.ImageView("ccs-res/cocosui/scrollviewbg.png");
                w.setAnchorPoint(0,1);
                w.setScaleX(2.0);
                w.setTouchEnabled(true);
                w.setTag(i+count1+count2);
                w.addTouchEventListener(this.onImageViewClicked, this);
                vbox.addChild(w);
            }

            var innerHBox = new ccui.HBox();
            vbox.addChild(innerHBox);
            innerHBox.setTag(102);
            //innerVBox.setPassFocusToChild(false);
            //innerVBox.setFocusEnabled(false);
            var count3 = 2;
            for (i = 0; i < count3; ++i) {
                w = new ccui.ImageView("ccs-res/cocosui/scrollviewbg.png");
                w.setTouchEnabled(true);
                w.setTag(i + count1 + count2 + count3);
                w.addTouchEventListener(this.onImageViewClicked, this);
                innerHBox.addChild(w);
            }

            this._loopText = new ccui.Text("loop enabled", "Arial", 20);
            this._loopText.setPosition(winSize.width/2, winSize.height - 50);
            this._loopText.setColor(cc.color.GREEN);
            this.addChild(this._loopText);

            var btn = new ccui.Button("ccs-res/cocosui/switch-mask.png");
            btn.setTitleText("Toggle Loop");
            btn.setPosition(60, winSize.height - 50);
            btn.setTitleColor(cc.color.RED);
            btn.addTouchEventListener(this.toggleFocusLoop, this);
            this.addChild(btn);
            return true;
        }
        return false;
    },

    toggleFocusLoop: function (ref, touchType) {
        if (touchType == ccui.Widget.TOUCH_ENDED) {
            this._horizontalLayout.setLoopFocus(!this._horizontalLayout.isLoopFocus());
            if (this._horizontalLayout.isLoopFocus()) {
                this._loopText.setString("loop enabled");
            } else {
                this._loopText.setString("loop disabled");
            }
        }
    }
});

var UIFocusTestNestedLayout3 = UIFocusTestBase.extend({
    _horizontalLayout: null,
    _loopText: null,

    init: function(){
        if (this._super()) {
            var winSize = cc.director.getVisibleSize();

            this._verticalLayout = new ccui.VBox();
            this._verticalLayout.setPosition(winSize.height / 2 + 80, winSize.height - 150);
            this.addChild(this._verticalLayout);
            //this._verticalLayout.setScale(0.8);

            this._verticalLayout.setFocused(true);
            this._verticalLayout.setLoopFocus(true);
            this._verticalLayout.setTag(-1000);
            this._firstFocusedWidget = this._verticalLayout;

            var upperHBox = new ccui.HBox();
            upperHBox.setTag(-200);
            this._verticalLayout.addChild(upperHBox);

            var params = new ccui.LinearLayoutParameter();
            params.setMargin(new ccui.Margin(0,0,50,0));

            var vparams = new ccui.LinearLayoutParameter();
            vparams.setMargin(new ccui.Margin(10, 0, 0, 140));
            upperHBox.setLayoutParameter(vparams);

            var count = 3, i, w;
            for (i = 0; i < count; ++i) {
                var firstVbox = new ccui.VBox();
                firstVbox.setScale(0.5);
                firstVbox.setLayoutParameter(params);
                firstVbox.setTag((i+1) * 100);

                var count1 = 3;
                for (var j = 0; j < count1; ++j) {
                    w = new ccui.ImageView("ccs-res/cocosui/scrollviewbg.png");
                    w.setTouchEnabled(true);
                    w.setTag(j + firstVbox.getTag() + 1);
                    w.addTouchEventListener(this.onImageViewClicked, this);
                    firstVbox.addChild(w);
                }
                upperHBox.addChild(firstVbox);
            }

            var bottomHBox = new ccui.HBox();
            bottomHBox.setScale(0.5);
            bottomHBox.setTag(600);
            bottomHBox.setLayoutParameter(vparams);
            count = 3;
            var bottomParams = new ccui.LinearLayoutParameter();
            bottomParams.setMargin(new ccui.Margin(0, 0, 8, 0));
            for (i = 0; i < count; ++i) {
                w = new ccui.ImageView("ccs-res/cocosui/scrollviewbg.png");
                w.setLayoutParameter(bottomParams);
                w.setTouchEnabled(true);
                w.setTag(i + 601);
                w.addTouchEventListener(this.onImageViewClicked, this);
                bottomHBox.addChild(w);
            }
            this._verticalLayout.addChild(bottomHBox);

            this._loopText = new ccui.Text("loop enabled", "Arial", 20);
            this._loopText.setPosition(winSize.width/2, winSize.height - 50);
            this._loopText.setColor(cc.color.GREEN);
            this.addChild(this._loopText);

            var btn = new ccui.Button("ccs-res/cocosui/switch-mask.png");
            btn.setTitleText("Toggle Loop");
            btn.setPosition(60, winSize.height - 50);
            btn.setTitleColor(cc.color.RED);
            btn.addTouchEventListener(this.toggleFocusLoop, this);
            this.addChild(btn);
            return true;
        }
        return false;
    },

    toggleFocusLoop: function(ref, touchType){
        if (touchType == ccui.Widget.TOUCH_ENDED) {
            this._verticalLayout.setLoopFocus(!this._verticalLayout.isLoopFocus());
            if (this._verticalLayout.isLoopFocus()) {
                this._loopText.setString("loop enabled");
            }else{
                this._loopText.setString("loop disabled");
            }
        }
    }
});

var UIFocusTestListView = UIFocusTestBase.extend({
    _listView: null,
    _loopText: null,

    init: function(){
        if (this._super()) {
            var winSize = cc.director.getVisibleSize();

            this._listView = new ccui.ListView();
            this._listView.setDirection(ccui.ScrollView.DIR_VERTICAL);
            this._listView.setBounceEnabled(true);
            this._listView.setBackGroundImage("ccs-res/cocosui/green_edit.png");
            this._listView.setBackGroundImageScale9Enabled(true);
            this._listView.setContentSize(240, 130);

            this._listView.setPosition(40, 70);
            this.addChild(this._listView);
            this._listView.setScale(0.8);

            this._listView.setFocused(true);
            this._listView.setLoopFocus(true);
            this._listView.setTag(-1000);
            this._firstFocusedWidget = this._listView;

            // create model
            var default_button = new ccui.Button("ccs-res/cocosui/backtotoppressed.png", "ccs-res/cocosui/backtotopnormal.png");
            default_button.setName("Title Button");

            // set model
            this._listView.setItemModel(default_button);

            // add default item
            var count = 20, i;
            for (i = 0; i < count / 4; ++i) {
                this._listView.pushBackDefaultItem();
            }
            // insert default item
            for (i = 0; i < count / 4; ++i) {
                this._listView.insertDefaultItem(0);
            }
            this._loopText = new ccui.Text("loop enabled", "Arial", 20);
            this._loopText.setPosition(winSize.width/2, winSize.height - 50);
            this._loopText.setColor(cc.color.GREEN);
            this.addChild(this._loopText);

            var btn = new ccui.Button("ccs-res/cocosui/switch-mask.png");
            btn.setTitleText("Toggle Loop");
            btn.setPosition(60, winSize.height - 50);
            btn.setTitleColor(cc.color.RED);
            btn.addTouchEventListener(this.toggleFocusLoop, this);
            this.addChild(btn);
            return true;
        }
        return false;
    },

    toggleFocusLoop: function(ref, touchType){
        if (touchType == ccui.Widget.TOUCH_ENDED) {
            this._listView.setLoopFocus(!this._listView.isLoopFocus());
            if (this._listView.isLoopFocus()) {
                this._loopText.setString("loop enabled");
            }else{
                this._loopText.setString("loop disabled");
            }
        }
    }
});