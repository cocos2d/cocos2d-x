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
            button.loadTextures("res/cocosui/animationbuttonnormal.png", "res/cocosui/animationbuttonpressed.png", "");
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
            button.loadTextures("res/cocosui/button.png", "res/cocosui/buttonHighlighted.png", "");
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
            button.loadTextures("res/cocosui/animationbuttonnormal.png", "res/cocosui/animationbuttonpressed.png", "");
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
            textButton.loadTextures("res/cocosui/backtotopnormal.png", "res/cocosui/backtotoppressed.png", "");
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