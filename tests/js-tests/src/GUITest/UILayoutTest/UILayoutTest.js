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

var UILayoutTestBase = UIScene.extend({
    layout: null,
    button: null,
    textButton: null,
    button_scale9: null,
    init: function () {
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();
            //init text
            this._topDisplayLabel.setString("");
            this._bottomDisplayLabel.setString(this.getText());
            this._bottomDisplayLabel.x = widgetSize.width / 2;
            this._bottomDisplayLabel.y = widgetSize.height / 2 - this._bottomDisplayLabel.height * 3;

            var background = this._widget.getChildByName("background_Panel");
            this._mainNode.width = widgetSize.width;
            this._mainNode.height = widgetSize.height;

            // Create the layout
            this.layout = this.createLayout();
            var layoutRect = this.layout.getContentSize();
            var backgroundRect = background.getContentSize();
            this.layout.x = (widgetSize.width - backgroundRect.width) / 2 + (backgroundRect.width - layoutRect.width) / 2;
	        this.layout.y = (widgetSize.height - backgroundRect.height) / 2 + (backgroundRect.height - layoutRect.height) / 2;
            this._mainNode.addChild(this.layout);

            this.button = new ccui.Button();
            this.button.setTouchEnabled(true);
            this.button.loadTextures("res/cocosui/animationbuttonnormal.png", "res/cocosui/animationbuttonpressed.png", "");
            this.button.x = this.button.width / 2;
            this.button.y = layoutRect.height - this.button.height / 2;
            this.layout.addChild(this.button);

            this.textButton = new ccui.Button();
            this.textButton.setTouchEnabled(true);
            this.textButton.loadTextures("res/cocosui/backtotopnormal.png", "res/cocosui/backtotoppressed.png", "");
            this.textButton.setTitleText("Text Button");
            this.textButton.x = layoutRect.width / 2;
            this.textButton.y = layoutRect.height / 2;
            this.layout.addChild(this.textButton);

            this.button_scale9 = new ccui.Button();
            this.button_scale9.setTouchEnabled(true);
            this.button_scale9.setScale9Enabled(true);
            this.button_scale9.loadTextures("res/cocosui/button.png", "res/cocosui/buttonHighlighted.png", "");
            this.button_scale9.width = 100;
	        this.button_scale9.height = 32;
            this.button_scale9.x = layoutRect.width - this.button_scale9.width / 2;
            this.button_scale9.y = this.button_scale9.height / 2;
            this.layout.addChild(this.button_scale9);

            this.setLayoutParameter();
            return true;
        }
        return false;
    },
    getText: function () {
        return "";
    },
    createLayout: function () {
        var layout = new ccui.Layout();
        layout.setContentSize(cc.size(280, 150));
        return layout;
    },
    setLayoutParameter: function () {

    }
});
var UILayoutTest = UILayoutTestBase.extend({
    createLayout: function () {
        var layout = new ccui.Layout();
        layout.setContentSize(cc.size(280, 150));
        return layout;
    },
    getText: function () {
        return "Layout";
    }
});
var UILayoutTest_Color = UILayoutTestBase.extend({
    createLayout: function () {
        var layout = new ccui.Layout();
        layout.setBackGroundColorType(ccui.Layout.BG_COLOR_SOLID);
        layout.setBackGroundColor(cc.color(128, 128, 128));
        layout.setContentSize(cc.size(280, 150));
        return layout;
    },
    getText: function () {
        return "Layout color render";
    }
});
var UILayoutTest_Gradient = UILayoutTestBase.extend({
    createLayout: function () {
        var layout = new ccui.Layout();
        layout.setBackGroundColorType(ccui.Layout.BG_COLOR_GRADIENT);
        layout.setBackGroundColor(cc.color(64, 64, 64), cc.color(192, 192, 192));
        layout.setContentSize(cc.size(280, 150));
        return layout;
    },
    getText: function () {
        return "Layout gradient render";
    }
});
var UILayoutTest_BackGroundImage = UILayoutTestBase.extend({
    createLayout: function () {
        var layout = new ccui.Layout();
        layout.setClippingEnabled(true);
        layout.setBackGroundImage("res/cocosui/Hello.png");
        layout.setContentSize(cc.size(280, 150));
        return layout;
    },
    getText: function () {
        return "Layout background image";
    }
});

var UILayoutTest_BackGroundImage_Scale9 = UILayoutTestBase.extend({
    createLayout: function () {
        var layout = new ccui.Layout();
        layout.setBackGroundImageScale9Enabled(true);
        layout.setBackGroundImage("res/cocosui/green_edit.png");
        layout.setContentSize(cc.size(280, 150));
        return layout;
    },
    getText: function () {
        return "Layout background image scale9";
    }
});
var UILayoutTest_Layout_Linear_Vertical = UILayoutTestBase.extend({
    createLayout: function () {
        var layout = new ccui.Layout();
        layout.setLayoutType(ccui.Layout.LINEAR_VERTICAL);
        layout.setContentSize(cc.size(280, 150));
        return layout;
    },
    getText: function () {
        return "Layout Layout Linear Vertical";
    },
    setLayoutParameter: function () {
        var lp1 = new ccui.LinearLayoutParameter();
        this.button.setLayoutParameter(lp1);
        lp1.setGravity(ccui.LinearLayoutParameter.CENTER_HORIZONTAL);
        lp1.setMargin(new ccui.Margin(0, 5, 0, 10));

        var lp2 = new ccui.LinearLayoutParameter();
        this.textButton.setLayoutParameter(lp2);
        lp2.setGravity(ccui.LinearLayoutParameter.CENTER_HORIZONTAL);
        lp2.setMargin(new ccui.Margin(0, 10, 0, 10));

        var lp3 = new ccui.LinearLayoutParameter();
        this.button_scale9.setLayoutParameter(lp3);
        lp3.setGravity(ccui.LinearLayoutParameter.CENTER_HORIZONTAL);
        lp3.setMargin(new ccui.Margin(0, 10, 0, 10));
    }
});
var UILayoutTest_Layout_Linear_Horizontal = UILayoutTestBase.extend({
    createLayout: function () {
        var layout = new ccui.Layout();
        layout.setLayoutType(ccui.Layout.LINEAR_HORIZONTAL);
        layout.setClippingEnabled(true);
        layout.setContentSize(cc.size(280, 150));
        return layout;
    },
    getText: function () {
        return "Layout Layout Linear Horizontal";
    },
    setLayoutParameter: function () {
        var lp1 = new ccui.LinearLayoutParameter();
        this.button.setLayoutParameter(lp1);
        lp1.setGravity(ccui.LinearLayoutParameter.CENTER_VERTICAL);
        lp1.setMargin(new ccui.Margin(0, 10, 0, 10));

        var lp2 = new ccui.LinearLayoutParameter();
        this.textButton.setLayoutParameter(lp2);
        lp2.setGravity(ccui.LinearLayoutParameter.CENTER_VERTICAL);
        lp2.setMargin(new ccui.Margin(0, 10, 0, 10));

        var lp3 = new ccui.LinearLayoutParameter();
        this.button_scale9.setLayoutParameter(lp3);
        lp3.setGravity(ccui.LinearLayoutParameter.CENTER_VERTICAL);
        lp3.setMargin(new ccui.Margin(0, 10, 0, 10));
    }
});

var UILayoutTest_Layout_Relative = UILayoutTestBase.extend({
    createLayout: function () {
        var layout = new ccui.Layout();
        layout.ignoreContentAdaptWithSize(false);
        layout.setLayoutType(ccui.Layout.RELATIVE);
        layout.sizeType = ccui.Widget.SIZE_PERCENT;
        layout.setSizePercent(cc.p(0.5, 0.5));
        //layout.setContentSize(cc.size(280, 150));
        layout.setPositionType(ccui.Widget.POSITION_PERCENT);
        layout.setPositionPercent(cc.p(0.25, 0.25));
        //layout.setPosition(cc.p(cc.winSize.width/2, cc.winSize.height/2));
        layout.setBackGroundColorType(ccui.Layout.BG_COLOR_SOLID);
        layout.setBackGroundColor(cc.color.GREEN);
        return layout;
    },
    getText: function () {
        return "Layout Layout Relative";
    },
    setLayoutParameter: function () {
        var lp1 = new ccui.RelativeLayoutParameter();
        this.button.setLayoutParameter(lp1);
        lp1.setAlign(ccui.RelativeLayoutParameter.PARENT_TOP_LEFT);

        var lp2 = new ccui.RelativeLayoutParameter();
        this.textButton.setLayoutParameter(lp2);
        lp2.setAlign(ccui.RelativeLayoutParameter.CENTER_IN_PARENT);

        var lp3 = new ccui.RelativeLayoutParameter();
        this.button_scale9.setLayoutParameter(lp3);
        lp3.setAlign(ccui.RelativeLayoutParameter.PARENT_RIGHT_BOTTOM);
    }
});