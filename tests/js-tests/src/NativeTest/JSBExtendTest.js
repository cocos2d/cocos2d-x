/****************************************************************************
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

(function (window) {

var message = "";

var appendMessage = function (tail) {
    message += "\n" + tail;
    cc.log(tail);
};

var ScrollViewExtended = ccui.ScrollView.extend({
    onEnter: function (){
        this._super();
        appendMessage("3. ScrollViewExtended: onEnter");
    },

    onExit: function () {
        appendMessage("E-3. ScrollViewExtended: onExit");
        this._super();
    }
});

var ButtonExtended = ccui.Button.extend({
    onEnter: function (){
        this._super();
        appendMessage("4. ButtonExtended: onEnter");
    },

    onExit: function () {
        appendMessage("E-4. ButtonExtended: onExit");
        this._super();
    }
});

var ImageViewExtended = ccui.ImageView.extend({
    onEnter: function (){
        this._super();
        appendMessage("5. ImageViewExtended: onEnter");
    },

    onExit: function () {
        appendMessage("E-5. ImageViewExtended: onExit");
        this._super();
    }
});

var LayerExtended = cc.Layer.extend({
    onEnter: function (){
        this._super();
        appendMessage("2. LayerExtended: onEnter");

        //add main node
        var scale = cc.winSize.height / 320;
        this.attr({
            anchorX: 0, 
            anchorY: 0, 
            scale: scale, 
            x: (cc.winSize.width - 480 * scale) / 2, 
            y: (cc.winSize.height - 320 * scale) / 2
        });

        var json = ccs.load("ccs-res/cocosui/UITest/UITest.json");
        var widget = json.node;
        this.addChild(widget, -1);

        var widgetSize = widget.getContentSize();

        var background = widget.getChildByName("background_Panel");
        background.y += 50;

        // Create the scrollview
        var scrollView = new ScrollViewExtended();
        scrollView.setDirection(ccui.ScrollView.DIR_VERTICAL);
        scrollView.setTouchEnabled(true);
        scrollView.setContentSize(cc.size(280, 150));

        scrollView.x = (widgetSize.width - background.width) / 2 + (background.width - scrollView.width) / 2;
        scrollView.y = background.y;
        this.addChild(scrollView);

        var imageView = new ImageViewExtended();
        imageView.loadTexture("ccs-res/cocosui/ccicon.png");

        var innerWidth = scrollView.width;
        var innerHeight = scrollView.height + imageView.height;

        scrollView.setInnerContainerSize(cc.size(innerWidth, innerHeight));

        var button = new ButtonExtended();
        button.setTouchEnabled(true);
        button.loadTextures("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png", "");
        button.x = innerWidth / 2;
        button.y = scrollView.getInnerContainerSize().height - button.height / 2;
        scrollView.addChild(button);

        var textButton = new ccui.Button();
        textButton.setTouchEnabled(true);
        textButton.loadTextures("ccs-res/cocosui/backtotopnormal.png", "ccs-res/cocosui/backtotoppressed.png", "");
        textButton.setTitleText("Remove UI");
        textButton.x = innerWidth / 2;
        textButton.y = button.getBottomBoundary() - button.height;
        textButton.addTouchEventListener(this.exit, this);
        scrollView.addChild(textButton);

        imageView.x = innerWidth / 2;
        imageView.y = textButton.getBottomBoundary() - imageView.height;
        scrollView.addChild(imageView);

        widget.getChildByName("UItest").string = "Please click 'Remove UI' button";
        widget.removeChild(widget.getChildByName("back"));
        widget.removeChild(widget.getChildByName("left_Button"));
        widget.removeChild(widget.getChildByName("middle_Button"));
        widget.removeChild(widget.getChildByName("right_Button"));
    },

    onExitTransitionDidStart: function () {
        this._super();
        appendMessage("E-1. LayerExtended: onExitTransitionDidStart");
    },

    onExit: function () {
        appendMessage("E-2. LayerExtended: onExit");
        this._super();
    },
    exit: function () {
        this.parent.removeUI();
    }
});

window.JSBExtendTest = cc.Scene.extend({
    label: null,
    ui: null,
    onEnter: function () {
        message = "";
        this._super();

        appendMessage("1. SceneExtended: onEnter");

        this.ui = new LayerExtended();
        this.addChild(this.ui);

        var scale = cc.winSize.height / 320;
        this.label = new cc.LabelTTF(message);
        this.label.x = cc.winSize.width/2;
        this.label.y = (cc.winSize.height - 320 * scale / 2) / 2;
        this.addChild(this.label);

        var back = new cc.LabelTTF("Back", "Arial", 20);
        var menuItem = new cc.MenuItemLabel(back, this.toNativeTest, this);
        var menu = new cc.Menu(menuItem);
        menu.x = 0;
        menu.y = 0;
        menuItem.x = winSize.width - 50;
        menuItem.y = 25;
        this.addChild(menu, 1);
    },
    removeUI: function () {
        this.removeChild(this.ui, true);
        this.label.y = cc.winSize.height/2;
        this.label.string = message;
    },
    toNativeTest: function () {
        var scene = new NativeTestScene();
        scene.runThisTest();
    }
});

})(window);