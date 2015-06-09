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

var UIButtonTest = UIScene.extend({
    init: function () {
        if (this._super()) {
            //init text
            this._topDisplayLabel.setString("No Event");
            this._bottomDisplayLabel.setString("Button");

            var widgetSize = this._widget.getContentSize();
            // Create the button
            var button = new ccui.Button();
            button.setTouchEnabled(true);
            button.loadTextures("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png", "");
            button.x = widgetSize.width / 2.0;
            button.y = widgetSize.height / 2.0;
            button.addTouchEventListener(this.touchEvent, this);
            this._mainNode.addChild(button);

            return true;
        }
        return false;
    },

    touchEvent: function (sender, type) {
        switch (type) {
            case ccui.Widget.TOUCH_BEGAN:
                this._topDisplayLabel.setString("Touch Down");
                break;

            case ccui.Widget.TOUCH_MOVED:
                this._topDisplayLabel.setString("Touch Move");
                break;

            case ccui.Widget.TOUCH_ENDED:
                this._topDisplayLabel.setString("Touch Up");
                break;

            case ccui.Widget.TOUCH_CANCELED:
                this._topDisplayLabel.setString("Touch Cancelled");
                break;

            default:
                break;
        }
    }
});
var UIButtonTest_Scale9 = UIScene.extend({
    init: function () {
        if (this._super()) {
            //init text
            this._topDisplayLabel.setString("No Event");
            this._bottomDisplayLabel.setString("Button scale9 render");

            // Create the button
            var button = new ccui.Button();
            button.setTouchEnabled(true);
            button.setScale9Enabled(true);
            button.loadTextures("ccs-res/cocosui/button.png", "ccs-res/cocosui/buttonHighlighted.png", "");
            button.x = this._widget.width / 2.0;
            button.y = this._widget.height / 2.0;
            button.setContentSize(cc.size(150, 48));
            button.addTouchEventListener(this.touchEvent ,this);
            this._mainNode.addChild(button);

            return true;
        }
        return false;
    },

    touchEvent: function (sender, type) {
        switch (type) {
            case ccui.Widget.TOUCH_BEGAN:
                this._topDisplayLabel.setString("Touch Down");
                break;
            case ccui.Widget.TOUCH_MOVED:
                this._topDisplayLabel.setString("Touch Move");
                break;
            case ccui.Widget.TOUCH_ENDED:
                this._topDisplayLabel.setString("Touch Up");
                break;
            case ccui.Widget.TOUCH_CANCELED:
                this._topDisplayLabel.setString("Touch Cancelled");
                break;

            default:
                break;
        }
    }
});

var UIButtonTest_PressedAction = UIScene.extend({
    init: function () {
        if (this._super()) {
            //init text
            this._topDisplayLabel.setString("No Event");
            this._bottomDisplayLabel.setString("Button Pressed Action");

            var widgetSize = this._widget.getContentSize();
            // Create the button
            var button = new ccui.Button();
            button.setTouchEnabled(true);
            button.setPressedActionEnabled(true);
            button.loadTextures("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png", "");
            button.x = widgetSize.width / 2;
            button.y = widgetSize.height / 2;
            button.addTouchEventListener(this.touchEvent ,this);
            this._mainNode.addChild(button);
            return true;
        }
        return false;
    },

    touchEvent: function (sender, type) {
        switch (type) {
            case ccui.Widget.TOUCH_BEGAN:
                this._topDisplayLabel.setString("Touch Down");
                break;
            case ccui.Widget.TOUCH_MOVED:
                this._topDisplayLabel.setString("Touch Move");
                break;
            case ccui.Widget.TOUCH_ENDED:
                this._topDisplayLabel.setString("Touch Up");
                break;
            case ccui.Widget.TOUCH_CANCELED:
                this._topDisplayLabel.setString("Touch Cancelled");
                break;
            default:
                break;
        }
    }
});

var UIButtonTest_Title = UIScene.extend({
    init: function () {
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();
            //init text
            this._topDisplayLabel.setString("No Event");
            this._bottomDisplayLabel.setString("Button with title");

            // Create the text button
            var textButton = new ccui.Button();
            textButton.setTouchEnabled(true);
            textButton.loadTextures("ccs-res/cocosui/backtotopnormal.png", "ccs-res/cocosui/backtotoppressed.png", "");
            textButton.setTitleText("Title Button");
            textButton.x = widgetSize.width / 2.0;
            textButton.y = widgetSize.height / 2.0;
            textButton.addTouchEventListener(this.touchEvent ,this);
            this._mainNode.addChild(textButton);

            return true;
        }
        return false;
    },

    touchEvent: function (sender, type) {
        switch (type) {
            case ccui.Widget.TOUCH_BEGAN:
                this._topDisplayLabel.setString("Touch Down");
                break;
            case ccui.Widget.TOUCH_MOVED:
                this._topDisplayLabel.setString("Touch Move");
                break;
            case ccui.Widget.TOUCH_ENDED:
                this._topDisplayLabel.setString("Touch Up");
                break;
            case ccui.Widget.TOUCH_CANCELED:
                this._topDisplayLabel.setString("Touch Cancelled");
                break;
            default:
                break;
        }
    }
});

var UIButtonTestRemoveSelf = UIScene.extend({
    init: function () {
        if (this._super()) {
            //init text
            this._topDisplayLabel.setString("No Event");
            this._bottomDisplayLabel.setString("Remove Self in the Button's Callback shouldn't cause crash!");
            this._bottomDisplayLabel.setFontSize(15);

            var widgetSize = this._widget.getContentSize();

            var layout = new ccui.Layout();
            layout.setContentSize(widgetSize.width * 0.6, widgetSize.height * 0.6);
            layout.setBackGroundColor(cc.color.GREEN);
            layout.setBackGroundColorType(ccui.Layout.BG_COLOR_SOLID);
            layout.setBackGroundColorOpacity(100);
            layout.setPosition(widgetSize.width/2, widgetSize.height/2);
            layout.setAnchorPoint(0.5, 0.5);
            layout.setTag(12);
            this._mainNode.addChild(layout);

            // Create the button
            var button = new ccui.Button("ccs-res/cocosui/animationbuttonnormal.png",
                "ccs-res/cocosui/animationbuttonpressed.png");
            button.setPosition(layout.width / 2.0, layout.height / 2.0);
            button.addTouchEventListener(this.touchEvent, this);
            layout.addChild(button);
            return true;
        }
        return false;
    },

    touchEvent: function(sender, type){
        switch (type) {
            case ccui.Widget.TOUCH_BEGAN:
                this._topDisplayLabel.setString("Touch Down");
                break;

            case ccui.Widget.TOUCH_MOVED:
                this._topDisplayLabel.setString("Touch Move");
                break;

            case ccui.Widget.TOUCH_ENDED:
                this._topDisplayLabel.setString("Touch Up");
                var layout = this._mainNode.getChildByTag(12);
                layout.removeFromParent(true);
                break;

            case ccui.Widget.TOUCH_CANCELED:
                this._topDisplayLabel.setString("Touch Cancelled");
                break;

            default:
                break;
        }
    }
});

var UIButtonTestSwitchScale9 = UIScene.extend({
    init: function(){
        if (this._super()){
            var widgetSize = this._widget.getContentSize();

            // Add a label in which the button events will be displayed
            this._topDisplayLabel.setString("No Event");
            this._bottomDisplayLabel.setString("");

            // Create the button
            var button = new ccui.Button("ccs-res/cocosui/animationbuttonnormal.png",
                "ccs-res/cocosui/animationbuttonpressed.png");
            button.setPosition(widgetSize.width / 2.0, widgetSize.height / 2.0);
            button.addTouchEventListener(this.touchEvent, this);
            button.setTitleText("Button Title");
            button.ignoreContentAdaptWithSize(false);

            this._mainNode.addChild(button);
            return true;
        }
        return false;
    },

    touchEvent: function(sender, type){
        switch (type) {
            case ccui.Widget.TOUCH_BEGAN:
                this._topDisplayLabel.setString("Touch Down");
                break;

            case ccui.Widget.TOUCH_MOVED:
                this._topDisplayLabel.setString("Touch Move");
                break;

            case ccui.Widget.TOUCH_ENDED:
                this._topDisplayLabel.setString("Touch Up");
                sender.setScale9Enabled(!sender.isScale9Enabled());
                sender.setContentSize(200,100);
                break;

            case ccui.Widget.TOUCH_CANCELED:
                this._topDisplayLabel.setString("Touch Cancelled");
                break;

            default:
                break;
        }
    }
});

var UIButtonTestZoomScale = UIScene.extend({
    init: function(){
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();

            // Add a label in which the button events will be displayed
            this._topDisplayLabel.setString("Zoom Scale: -0.5");
            this._bottomDisplayLabel.setString("");

            // Create the button
            var button = new ccui.Button("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png");
            button.setPosition(widgetSize.width / 2.0, widgetSize.height / 2.0 );
            button.setPressedActionEnabled(true);
            button.addClickEventListener(function () {
                cc.log("Button clicked, position = (" + button.x + ", " + button.y + ")");
            });
            button.setName("button");
            this._mainNode.addChild(button);
            button.setZoomScale(-0.5);

            var slider = new ccui.Slider();
            slider.loadBarTexture("ccs-res/cocosui/sliderTrack.png");
            slider.loadSlidBallTextures("ccs-res/cocosui/sliderThumb.png", "ccs-res/cocosui/sliderThumb.png", "");
            slider.loadProgressBarTexture("ccs-res/cocosui/sliderProgress.png");
            slider.setPosition(widgetSize.width / 2.0 , widgetSize.height / 2.0 - 50);
            slider.addEventListener(this.sliderEvent, this);
            slider.setPercent(button.getZoomScale() * 100);
            this._mainNode.addChild(slider);
            return true;
        }
        return false;
    },

    sliderEvent: function(slider, type){
        if (type == ccui.Slider.EVENT_PERCENT_CHANGED){
            var percent = slider.getPercent();
            var btn = this._mainNode.getChildByName("button");
            var zoomScale = percent * 0.01;
            btn.setZoomScale(zoomScale);
            this._topDisplayLabel.setString("Zoom Scale: "+ zoomScale.toFixed(2));
        }
    }
});

var UIButtonTextOnly = UIScene.extend({
    init: function(){
        if (this._super()) {
            // Add a label in which the button events will be displayed
            this._topDisplayLabel.setString("Text Only Button");
            this._bottomDisplayLabel.setString("");

            // Create the button
            var button = new ccui.Button();
            button.setNormalizedPosition(0.5, 0.5);

            button.setTitleText("PLAY GAME");
            cc.log("content size should be greater than 0:  width = %f, height = %f", button.width, button.height);
            button.setZoomScale(0.3);
            button.setPressedActionEnabled(true);
            button.addClickEventListener(function () {
                cc.log("clicked!");
            });
            this.addChild(button);
            return true;
        }
        return false;
    }
});

var UIButtonIgnoreContentSizeTest = UIScene.extend({
    init: function(){
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();

            // Add a label in which the button events will be displayed
            this._topDisplayLabel.setString("Button IgnoreContent Size Test");
            this._bottomDisplayLabel.setString("");

            // Create the button
            var button = new ccui.Button("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png");
            button.ignoreContentAdaptWithSize(false);
            button.setContentSize(200,100);
            button.setNormalizedPosition(0.3, 0.5);
            button.setTitleText("PLAY GAME");
            button.setZoomScale(0.3);
            button.setPressedActionEnabled(true);
            button.addClickEventListener(function () {
                cc.log("clicked!");
                button.setScale(1.2);
            });
            this.addChild(button);

            // Create the button
            var button2 = new ccui.Button("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png");
            button2.ignoreContentAdaptWithSize(false);
            button2.setContentSize(200,100);
            button2.setNormalizedPosition(0.8, 0.5);
            button2.setTitleText("PLAY GAME");
            button2.setZoomScale(0.3);
            button2.setPressedActionEnabled(true);
            button2.addClickEventListener(function () {
                button2.runAction(cc.scaleTo(1.0, 1.2));
                cc.log("clicked!");
            });
            this.addChild(button2);

            return true;
        }
        return false;
    }
});

var UIButtonTitleEffectTest = UIScene.extend({
    init: function(){
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();

            // Add a label in which the button events will be displayed
            this._topDisplayLabel.setString("Button Title Effect");
            this._bottomDisplayLabel.setString("");

            // Create the button
            var button = new ccui.Button("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png");
            button.setNormalizedPosition(0.3, 0.5);
            button.setTitleText("PLAY GAME");
            //button.setTitleFontName("Marker Felt");
            button.setZoomScale(0.3);
            button.setScale(2.0);
            button.setPressedActionEnabled(true);
            var title = button.getTitleRenderer();
            button.setTitleColor(cc.color.RED);
            title.enableShadow(cc.color.BLACK, cc.size(2,-2));
            this.addChild(button);

            // Create the button
            var button2 = new ccui.Button("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png");
            button2.setNormalizedPosition(0.8, 0.5);
            button2.setTitleText("PLAY GAME");
            var title2 = button2.getTitleRenderer();
            title2.enableStroke(cc.color.GREEN, 3);
            this.addChild(button2);
            return true;
        }
        return false;
    }
});

var UIButtonFlipTest = UIScene.extend({
    init: function(){
        if (this._super()) {

            // Add a label in which the button events will be displayed
            this._topDisplayLabel.setString("");
            this._bottomDisplayLabel.setString("");

            // Create the button
            var button = new ccui.Button("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png");
            button.setNormalizedPosition(0.3, 0.5);
            button.setTitleText("PLAY GAME");
            //button.setTitleFontName("Marker Felt");
            button.setZoomScale(0.3);
            button.setScale(2.0);
            button.setFlippedX(true);
            button.setPressedActionEnabled(true);
            this.addChild(button);

            var titleLabel = new ccui.Text("Button X flipped", "Arial", 20);
            titleLabel.setNormalizedPosition(0.3, 0.7);
            this.addChild(titleLabel);

            // Create the button
            var button2 = new ccui.Button("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png");
            button2.setNormalizedPosition(0.8, 0.5);
            button2.setTitleText("PLAY GAME");
            button2.setFlippedY(true);
            this.addChild(button2);

            titleLabel = new ccui.Text("Button Y flipped", "Arial", 20);
            titleLabel.setNormalizedPosition(0.8, 0.7);
            this.addChild(titleLabel);
            return true;
        }
        return false;
    }
});

var UIButtonNormalDefaultTest = UIScene.extend({
    init: function(){
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();

            // Add a label in which the button events will be displayed
            this._topDisplayLabel.setString("");
            this._bottomDisplayLabel.setString("");

            // Add the alert
            var alert = new ccui.Text("Button should scale when clicked","Arial",20);
            alert.setColor(cc.color(159, 168, 176));
            alert.setPosition(widgetSize.width / 2.0,
                    widgetSize.height / 2.0 - alert.height * 1.75);
            this._mainNode.addChild(alert);

            // Create the button
            var button = new ccui.Button("ccs-res/cocosui/animationbuttonnormal.png");
            button.setPosition(widgetSize.width / 2.0 - 80, widgetSize.height / 2.0 + 40);
            button.setZoomScale(0.4);
            button.setPressedActionEnabled(true);
            this._mainNode.addChild(button);

            // Create the button
            var buttonScale9 = new ccui.Button("ccs-res/cocosui/button.png");
            // open scale9 render
            buttonScale9.setScale9Enabled(true);
            buttonScale9.setPosition(widgetSize.width / 2.0 + 50, widgetSize.height / 2.0 + 40);
            buttonScale9.setContentSize(150, 70);
            buttonScale9.setPressedActionEnabled(true);
            this._mainNode.addChild(buttonScale9);
            return true;
        }
        return false;
    }
});

var UIButtonDisableDefaultTest = UIScene.extend({
    init: function(){
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();

            this._topDisplayLabel.setString("");
            this._bottomDisplayLabel.setString("");

            // Add the alert
            var alert = new ccui.Text("Left button will turn normal when clicked","Arial",20);
            alert.setColor(cc.color(159, 168, 176));
            alert.setPosition(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert.height * 1.75);
            this._mainNode.addChild(alert);

            // Create the button
            var button = new ccui.Button("ccs-res/cocosui/animationbuttonnormal.png");
            button.setPosition(widgetSize.width / 2.0 - 80, widgetSize.height / 2.0 + 40);
            button.setZoomScale(0.4);
            button.setPressedActionEnabled(true);
            button.setBright(false);
            button.addClickEventListener(function () {
                button.setBright(true);
            });
            this._mainNode.addChild(button);

            // Create the button
            var buttonScale9 = new ccui.Button("ccs-res/cocosui/button.png");
            // open scale9 render
            buttonScale9.setScale9Enabled(true);
            buttonScale9.setPosition(widgetSize.width / 2.0 + 50, widgetSize.height / 2.0 + 40);
            buttonScale9.setContentSize(150, 70);
            buttonScale9.setPressedActionEnabled(true);
            buttonScale9.setEnabled(false);
            buttonScale9.setBright(false);
            this._mainNode.addChild(buttonScale9);
            return true;
        }
        return false;
    }
});