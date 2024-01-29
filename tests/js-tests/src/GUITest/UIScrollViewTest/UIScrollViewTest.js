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

var UIScrollViewTest_Vertical = UIMainLayer.extend({
    init: function () {
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();
            //init text
            this._topDisplayLabel.setString("Move by vertical direction");
            this._topDisplayLabel.x = widgetSize.width / 2.0;
            this._topDisplayLabel.y = widgetSize.height / 2.0 + this._topDisplayLabel.height * 1.5;
            this._bottomDisplayLabel.setString("ScrollView");
            this._bottomDisplayLabel.x = widgetSize.width / 2;
            this._bottomDisplayLabel.y = widgetSize.height / 2 - this._bottomDisplayLabel.height * 3;

            var background = this._widget.getChildByName("background_Panel");

            // Create the scrollview
            var scrollView = new ccui.ScrollView();
            scrollView.setDirection(ccui.ScrollView.DIR_VERTICAL);
            scrollView.setTouchEnabled(true);
            scrollView.setContentSize(cc.size(280, 150));

            scrollView.x = (widgetSize.width - background.width) / 2 + (background.width - scrollView.width) / 2;
            scrollView.y = (widgetSize.height - background.height) / 2 + (background.height - scrollView.height) / 2;
            this._mainNode.addChild(scrollView);

            var imageView = new ccui.ImageView();
            imageView.loadTexture("ccs-res/cocosui/ccicon.png");

            var innerWidth = scrollView.width;
            var innerHeight = scrollView.height + imageView.height;

            scrollView.setInnerContainerSize(cc.size(innerWidth, innerHeight));

            var button = new ccui.Button();
            button.setTouchEnabled(true);
            button.loadTextures("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png", "");
            button.x = innerWidth / 2;
            button.y = scrollView.getInnerContainerSize().height - button.height / 2;
            scrollView.addChild(button);

            var textButton = new ccui.Button();
            textButton.setTouchEnabled(true);
            textButton.loadTextures("ccs-res/cocosui/backtotopnormal.png", "ccs-res/cocosui/backtotoppressed.png", "");
            textButton.setTitleText("Text Button");
            textButton.x = innerWidth / 2;
            textButton.y = button.getBottomBoundary() - button.height;
            scrollView.addChild(textButton);

            var button_scale9 = new ccui.Button();
            button_scale9.setTouchEnabled(true);
            button_scale9.setScale9Enabled(true);
            button_scale9.loadTextures("ccs-res/cocosui/button.png", "ccs-res/cocosui/buttonHighlighted.png", "");
            button_scale9.width = 100;
	        button_scale9.height = 32;
            button_scale9.x = innerWidth / 2;
            button_scale9.y = textButton.getBottomBoundary() - textButton.height;
            scrollView.addChild(button_scale9);

            imageView.x = innerWidth / 2;
            imageView.y = imageView.height / 2;
            scrollView.addChild(imageView);

            return true;
        }
        return false;
    }
});

var UIScrollViewTest_Horizontal = UIMainLayer.extend({
    init: function () {
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();
            //init text
            this._topDisplayLabel.setString("Move by horizontal direction");
            this._topDisplayLabel.x = widgetSize.width / 2.0;
            this._topDisplayLabel.y = widgetSize.height / 2.0 + this._topDisplayLabel.height * 1.5;
            this._bottomDisplayLabel.setString("ScrollView");
            this._bottomDisplayLabel.x = widgetSize.width / 2;
            this._bottomDisplayLabel.y = widgetSize.height / 2 - this._bottomDisplayLabel.height * 3;

            var background = this._widget.getChildByName("background_Panel");

            // Create the scrollview
            var scrollView = new ccui.ScrollView();
            scrollView.setDirection(ccui.ScrollView.DIR_HORIZONTAL);
            scrollView.setTouchEnabled(true);
            scrollView.setContentSize(cc.size(280, 150));
            var scrollViewRect = scrollView.getContentSize();
            scrollView.setInnerContainerSize(cc.size(scrollViewRect.width,scrollViewRect.height));

            scrollView.x = (widgetSize.width - background.width) / 2 + (background.width - scrollViewRect.width) / 2;
            scrollView.y = (widgetSize.height - background.height) / 2 + (background.height - scrollViewRect.height) / 2;
            this._mainNode.addChild(scrollView);

            var imageView = new ccui.ImageView();
            imageView.loadTexture("ccs-res/cocosui/ccicon.png");

            var innerWidth = scrollViewRect.width + imageView.getContentSize().width;
            var innerHeight = scrollViewRect.height;

            scrollView.setInnerContainerSize(cc.size(innerWidth, innerHeight));

            var button = new ccui.Button();
            button.setTouchEnabled(true);
            button.loadTextures("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png", "");
            button.x = button.width / 2;
            button.y = scrollView.getInnerContainerSize().height - button.height / 2;
            scrollView.addChild(button);

            var textButton = new ccui.Button();
            textButton.setTouchEnabled(true);
            textButton.loadTextures("ccs-res/cocosui/backtotopnormal.png", "ccs-res/cocosui/backtotoppressed.png", "");
            textButton.setTitleText("Text Button");
            textButton.x = button.getRightBoundary() + button.width / 2;
            textButton.y = button.getBottomBoundary() - button.height;
            scrollView.addChild(textButton);

            var button_scale9 = new ccui.Button();
            button_scale9.setTouchEnabled(true);
            button_scale9.setScale9Enabled(true);
            button_scale9.loadTextures("ccs-res/cocosui/button.png", "ccs-res/cocosui/buttonHighlighted.png", "");
            button_scale9.width = 100;
            button_scale9.height = 32;
            button_scale9.x = textButton.getRightBoundary() + textButton.width / 2;
            button_scale9.y = textButton.getBottomBoundary() - textButton.height;
            scrollView.addChild(button_scale9);

            imageView.x = innerWidth - imageView.width / 2;
	        imageView.y = button_scale9.getBottomBoundary() - button_scale9.height / 2;
            scrollView.addChild(imageView);

            return true;
        }
        return false;
    }
});

var UIScrollViewTest_Both = UIMainLayer.extend({
    init: function () {
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();
            //init text
            this._topDisplayLabel.setString("Move by any direction");
            this._topDisplayLabel.x = widgetSize.width / 2.0;
            this._topDisplayLabel.y = widgetSize.height / 2.0 + this._topDisplayLabel.height * 1.5;
            this._bottomDisplayLabel.setString("ScrollView both");
            this._bottomDisplayLabel.x = widgetSize.width / 2;
            this._bottomDisplayLabel.y = widgetSize.height / 2 - this._bottomDisplayLabel.height * 3;

            var background = this._widget.getChildByName("background_Panel");

            // Create the scrollview
            var scrollView = new ccui.ScrollView();
            scrollView.setDirection(ccui.ScrollView.DIR_BOTH);
            scrollView.setTouchEnabled(true);
            scrollView.setBounceEnabled(true);
            scrollView.setBackGroundImageScale9Enabled(true);
            scrollView.setBackGroundImage("ccs-res/cocosui/green_edit.png");
            scrollView.setContentSize(cc.size(210, 122));
            var scrollViewSize = scrollView.getContentSize();

            scrollView.x = (widgetSize.width - background.width) / 2 + (background.width - scrollViewSize.width) / 2;
            scrollView.y = (widgetSize.height - background.height) / 2 + (background.height - scrollViewSize.height) / 2;
            this._mainNode.addChild(scrollView);

            var imageView = new ccui.ImageView();
            imageView.loadTexture("ccs-res/cocosui/b11.png");
            scrollView.addChild(imageView);

            scrollView.setInnerContainerSize(cc.size(imageView.width, imageView.height));
            imageView.x = imageView.width/2;
            imageView.y = imageView.height/2;

            return true;
        }
        return false;
    }
});

var UIScrollViewTest_ScrollToPercentBothDirection = UIMainLayer.extend({
    init: function () {
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();
            //init text
            this._topDisplayLabel.setString("");
            this._bottomDisplayLabel.setString("ScrollView scroll to percent both directrion");
            this._bottomDisplayLabel.x = widgetSize.width / 2;
            this._bottomDisplayLabel.y = widgetSize.height / 2 - this._bottomDisplayLabel.height * 3;

            var background = this._widget.getChildByName("background_Panel");

            // Create the scrollview
            var scrollView = new ccui.ScrollView();
            scrollView.setTouchEnabled(true);
            scrollView.setBackGroundColor(cc.color.GREEN);
            scrollView.setBackGroundColorType(ccui.Layout.BG_COLOR_SOLID);
            scrollView.setDirection(ccui.ScrollView.DIR_BOTH);
            scrollView.setInnerContainerSize(cc.size(480, 320));
            scrollView.setContentSize(cc.size(100, 100));
            var scrollViewSize = scrollView.getContentSize();

            scrollView.x = (widgetSize.width - background.width) / 2 + (background.width - scrollViewSize.width) / 2;
            scrollView.y = (widgetSize.height - background.height) / 2 + (background.height - scrollViewSize.height) / 2;
            scrollView.scrollToPercentBothDirection(cc.p(50, 50), 1, true);

            this._mainNode.addChild(scrollView);

            var imageView = new ccui.ImageView();
            imageView.loadTexture("ccs-res/cocosui/Hello.png");
            imageView.x = 240;
            imageView.y = 160;
            scrollView.addChild(imageView);

            return true;
        }
        return false;
    }
});

var UIScrollViewTest_ScrollToPercentBothDirection_Bounce = UIMainLayer.extend({
    init: function () {
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();
            //init text
            this._topDisplayLabel.setString("");
            this._bottomDisplayLabel.setString("ScrollView scroll to percent both directrion bounce");
            this._bottomDisplayLabel.x = widgetSize.width / 2;
            this._bottomDisplayLabel.y = widgetSize.height / 2 - this._bottomDisplayLabel.height * 3;

            var background = this._widget.getChildByName("background_Panel");

            // Create the scrollview
            var scrollView = new ccui.ScrollView();
            scrollView.setTouchEnabled(true);
            scrollView.setBounceEnabled(true);
            scrollView.setBackGroundColor(cc.color.GREEN);
            scrollView.setBackGroundColorType(ccui.Layout.BG_COLOR_SOLID);
            scrollView.setDirection(ccui.ScrollView.DIR_BOTH);
            scrollView.setInnerContainerSize(cc.size(480, 320));
            scrollView.setContentSize(cc.size(100, 100));
            var scrollViewSize = scrollView.getContentSize();

            scrollView.x = (widgetSize.width - background.width) / 2 + (background.width - scrollViewSize.width) / 2;
            scrollView.y = (widgetSize.height - background.height) / 2 + (background.height - scrollViewSize.height) / 2;
            scrollView.scrollToPercentBothDirection(cc.p(50, 50), 1, true);

            this._mainNode.addChild(scrollView);

            var imageView = new ccui.ImageView();
            imageView.loadTexture("ccs-res/cocosui/Hello.png");
            imageView.x = 240;
            imageView.y = 160;
            scrollView.addChild(imageView);

            return true;
        }
        return false;
    }
});

//2015-01-14
var UIScrollViewNestTest = UIMainLayer.extend({
    init: function(){
        if(this._super()){
            var widgetSize = this._widget.getContentSize();

            // Add a label in which the scrollview alert will be displayed
            this._topDisplayLabel.setString("Move by vertical direction");

            // Add the alert
            this._bottomDisplayLabel.setString("ScrollView vertical");
            this._bottomDisplayLabel.setPosition(widgetSize.width / 2.0, widgetSize.height / 2.0 - this._bottomDisplayLabel.height * 3.075);

            var root = this._mainNode.getChildByTag(81);

            var background = root.getChildByName("background_Panel");

            // Create the scrollview by vertical
            var scrollView = new ccui.ScrollView();
            scrollView.setContentSize(cc.size(280.0, 150.0));
            scrollView.setDirection(ccui.ScrollView.DIR_BOTH);
            var backgroundSize = background.getContentSize();
            scrollView.setPosition(cc.p((widgetSize.width - backgroundSize.width) / 2.0 +
                (backgroundSize.width - scrollView.getContentSize().width) / 2.0,
                (widgetSize.height - backgroundSize.height) / 2.0 +
                (backgroundSize.height - scrollView.getContentSize().height) / 2.0));
            this._mainNode.addChild(scrollView);

            var imageView = new ccui.ImageView("ccs-res/cocosui/ccicon.png");

            var innerWidth = scrollView.getContentSize().width;
            var innerHeight = scrollView.getContentSize().height + imageView.getContentSize().height;

            scrollView.setInnerContainerSize(cc.size(innerWidth, innerHeight));

            var button = new ccui.Button("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png");
            button.setPosition(cc.p(innerWidth / 2.0, scrollView.getInnerContainerSize().height - button.getContentSize().height / 2.0));
            scrollView.addChild(button);

            var titleButton = new ccui.Button("ccs-res/cocosui/backtotopnormal.png", "ccs-res/cocosui/backtotoppressed.png");
            titleButton.setTitleText("Title Button");
            titleButton.setPosition(cc.p(innerWidth / 2.0, button.getBottomBoundary() - button.getContentSize().height));
            scrollView.addChild(titleButton);

            var button_scale9 = new ccui.Button("ccs-res/cocosui/button.png", "ccs-res/cocosui/buttonHighlighted.png");
            button_scale9.setScale9Enabled(true);
            button_scale9.setContentSize(cc.size(100.0, button_scale9.getVirtualRendererSize().height));
            button_scale9.setPosition(cc.p(innerWidth / 2.0, titleButton.getBottomBoundary() - titleButton.getContentSize().height));
            scrollView.addChild(button_scale9);

            imageView.setPosition(cc.p(innerWidth / 2.0, imageView.getContentSize().height / 2.0));
            scrollView.addChild(imageView);

            // Create the scrollview by horizontal
            var sc = new ccui.ScrollView();
            sc.setBackGroundColor(cc.color.GREEN);
            sc.setBackGroundColorType(ccui.Layout.BG_COLOR_SOLID);
            sc.setBounceEnabled(true);
            sc.setDirection(ccui.ScrollView.DIR_BOTH);
            sc.setInnerContainerSize(cc.size(480, 320));
            sc.setContentSize(cc.size(100,100));
            sc.setPropagateTouchEvents(false);
            sc.setPosition(cc.p(180,100));
            sc.scrollToPercentBothDirection(cc.p(50, 50), 1, true);
            var iv = new ccui.ImageView("ccs-res/cocosui/Hello.png");
            iv.setPosition(cc.p(240, 160));
            sc.addChild(iv);
            scrollView.addChild(sc);

            return true;
        }
    }

});

//2015-01-14
var UIScrollViewRotated = UIMainLayer.extend({
    init: function(){
        if(this._super()){
            var widgetSize = this._widget.getContentSize();

            // Add a label in which the scrollview alert will be displayed
            this._topDisplayLabel.setString("Move by vertical direction");

            // Add the alert
            this._bottomDisplayLabel.setString("ScrollView vertical");
            this._bottomDisplayLabel.setPosition(widgetSize.width / 2.0, widgetSize.height / 2.0 - this._bottomDisplayLabel.height * 3.075);

            var root = this._mainNode.getChildByTag(81);
            var background = root.getChildByName("background_Panel");

            // Create the scrollview by vertical
            var scrollView = new ccui.ScrollView();
            scrollView.setContentSize(cc.size(280.0, 150.0));
            scrollView.setDirection(ccui.ScrollView.DIR_BOTH);
            var backgroundSize = background.getContentSize();
            scrollView.setPosition(cc.p((widgetSize.width - backgroundSize.width) / 2.0 +
                (backgroundSize.width - scrollView.getContentSize().width) / 2.0,
                (widgetSize.height - backgroundSize.height) / 2.0 +
                (backgroundSize.height - scrollView.getContentSize().height) / 2.0 + 100) );
            scrollView.setRotation(45);
            this._mainNode.addChild(scrollView);

            var imageView = new ccui.ImageView("ccs-res/cocosui/ccicon.png");

            var innerWidth = scrollView.getContentSize().width;
            var innerHeight = scrollView.getContentSize().height + imageView.getContentSize().height;
            scrollView.setInnerContainerSize(cc.size(innerWidth, innerHeight));

            var button = new ccui.Button("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png");
            button.setPosition(cc.p(innerWidth / 2.0, scrollView.getInnerContainerSize().height - button.getContentSize().height / 2.0));
            scrollView.addChild(button);

            var titleButton = new ccui.Button("ccs-res/cocosui/backtotopnormal.png", "ccs-res/cocosui/backtotoppressed.png");
            titleButton.setTitleText("Title Button");
            titleButton.setPosition(cc.p(innerWidth / 2.0, button.getBottomBoundary() - button.getContentSize().height));
            scrollView.addChild(titleButton);

            var button_scale9 = new ccui.Button("ccs-res/cocosui/button.png", "ccs-res/cocosui/buttonHighlighted.png");
            button_scale9.setScale9Enabled(true);
            button_scale9.setContentSize(cc.size(100.0, button_scale9.getVirtualRendererSize().height));
            button_scale9.setPosition(cc.p(innerWidth / 2.0, titleButton.getBottomBoundary() - titleButton.getContentSize().height));
            scrollView.addChild(button_scale9);

            imageView.setPosition(cc.p(innerWidth / 2.0, imageView.getContentSize().height / 2.0));
            scrollView.addChild(imageView);

            return true;
        }
    }
});

var UIScrollViewDisableTest = UIMainLayer.extend({
    init: function () {
        if (this._super()){
            var widgetSize = this._widget.getContentSize();

            this._topDisplayLabel.setString("ScrollView Disable Test");
            this._topDisplayLabel.x = widgetSize.width / 2.0;
            this._topDisplayLabel.y = widgetSize.height / 2.0 + this._topDisplayLabel.height * 1.5;

            this._bottomDisplayLabel.setString("ScrollView vertical");
            this._bottomDisplayLabel.x = widgetSize.width / 2;
            this._bottomDisplayLabel.y = widgetSize.height / 2 - this._bottomDisplayLabel.height * 3;

            var background = this._widget.getChildByName("background_Panel");
            var backgroundSize = background.getContentSize();

            var scrollView = new ccui.ScrollView();
            scrollView.setContentSize(cc.size(280, 150));
            scrollView.x = (widgetSize.width - backgroundSize.width) / 2 + (backgroundSize.width - scrollView.width) / 2;
            scrollView.y = (widgetSize.height - backgroundSize.height) / 2 + (backgroundSize.height - scrollView.height) / 2;
            scrollView.setTouchEnabled(false);

            this._mainNode.addChild(scrollView);

            var imageView = new ccui.ImageView();
            imageView.loadTexture("ccs-res/cocosui/ccicon.png");

            var innerWidth = scrollView.width;
            var innerHeight = scrollView.height + imageView.height;

            scrollView.setInnerContainerSize(cc.size(innerWidth, innerHeight));

            var button = new ccui.Button();
            button.setTouchEnabled(true);
            button.loadTextures("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png", "");
            button.x = innerWidth / 2;
            button.y = scrollView.getInnerContainerSize().height - button.height / 2;
            scrollView.addChild(button);

            var textButton = new ccui.Button();
            textButton.setTouchEnabled(true);
            textButton.loadTextures("ccs-res/cocosui/backtotopnormal.png", "ccs-res/cocosui/backtotoppressed.png", "");
            textButton.setTitleText("Text Button");
            textButton.x = innerWidth / 2;
            textButton.y = button.getBottomBoundary() - button.height;
            scrollView.addChild(textButton);

            var button_scale9 = new ccui.Button();
            button_scale9.setTouchEnabled(true);
            button_scale9.setScale9Enabled(true);
            button_scale9.loadTextures("ccs-res/cocosui/button.png", "ccs-res/cocosui/buttonHighlighted.png", "");
            button_scale9.width = 100;
            button_scale9.height = 32;
            button_scale9.x = innerWidth / 2;
            button_scale9.y = textButton.getBottomBoundary() - textButton.height;
            scrollView.addChild(button_scale9);

            imageView.setPosition(cc.p(innerWidth/2, imageView.getContentSize().height/2));
            scrollView.addChild(imageView);

            return true;
        }
        return false;
    }
});

var UIScrollViewTest_Vertical_Multiple = UIMainLayer.extend({
    _scrollView:null,
    _itemNumber:1000,
    init: function () {
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();
            //init text
            this._topDisplayLabel.setString("Move by vertical direction");
            this._topDisplayLabel.x = widgetSize.width / 2.0;
            this._topDisplayLabel.y = widgetSize.height / 2.0 + this._topDisplayLabel.height * 1.5;
            this._bottomDisplayLabel.setString("Compare drawCalls and FPS with Previous Version");
            this._bottomDisplayLabel.setFontSize(25);
            this._bottomDisplayLabel.x = widgetSize.width / 2;
            this._bottomDisplayLabel.y = widgetSize.height / 2 - this._bottomDisplayLabel.height * 4;

            var background = this._widget.getChildByName("background_Panel");

            // Create the scrollview
            var scrollView = this._scrollView = new ccui.ScrollView();
            scrollView.setDirection(ccui.ScrollView.DIR_VERTICAL);
            scrollView.setTouchEnabled(true);
            scrollView.setContentSize(cc.size(280, 150));

            scrollView.x = (widgetSize.width - background.width) / 2 + (background.width - scrollView.width) / 2;
            scrollView.y = (widgetSize.height - background.height) / 2 + (background.height - scrollView.height) / 2;
            this._mainNode.addChild(scrollView);

            var labelText = new cc.LabelTTF("Texts", "Arial", 25);
            var labelButton = new cc.LabelTTF("Buttons", "Arial", 25);
            var labelS9sprite = new cc.LabelTTF("s9Sprites", "Arial", 25);

            var menuItem1 = new cc.MenuItemLabel(labelText, this.drawTexts, this);
            var menuItem2 = new cc.MenuItemLabel(labelButton, this.drawButtons, this, false);
            var menuItem3 = new cc.MenuItemLabel(labelS9sprite, this.drawS9Buttons, this);
            var menu = new cc.Menu(menuItem1, menuItem2, menuItem3);
            menu.x = 0;
            menu.y = 0;
            menuItem1.x = menuItem2.x = menuItem3.x = 120;
            menuItem1.y = 150;
            menuItem2.y = 200;
            menuItem3.y = 250;
            this.addChild(menu, 1);
            this.drawTexts();
            return true;
        }
        return false;
    },
    drawTexts:function() {
        var scrollView = this._scrollView;
        var n = this._itemNumber/2;
        if(scrollView.getChildren())
            scrollView.removeAllChildren(true);
        var Texts = [];
        var start = new ccui.Text("---start---", "Thonburi", 10);
        var innerWidth = scrollView.width;
        var innerHeight = n * start.height;
        scrollView.setInnerContainerSize(cc.size(innerWidth, innerHeight));

        start.x = innerWidth / 2;
        start.y = scrollView.getInnerContainerSize().height - start.height / 2;
        Texts[0] = start;
        scrollView.addChild(start);

        for (var i = 1; i < n; i++) {
            var text = new ccui.Text("This is a test label: " + i, "Thonburi", 10);
            text.x = innerWidth / 2;
            text.y = Texts[i - 1].getBottomBoundary() - text.height / 2;
            Texts[i] = text;
            scrollView.addChild(Texts[i]);
        }
    },
    drawButtons:function() {
        var scrollView = this._scrollView;
        var n = this._itemNumber/2;
        if(scrollView.getChildren())
            scrollView.removeAllChildren(true);
        var Buttons = [];
        var innerWidth = scrollView.width;

        for (var j = 0; j < n; j++) {
            var button = new ccui.Button();
            button.setTouchEnabled(true);
            button.loadTextures("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png", "");
            button.x = innerWidth / 2;
            if(j===0) {
                var innerHeight = n * button.height;
                scrollView.setInnerContainerSize(cc.size(innerWidth, innerHeight));
                button.y =scrollView.getInnerContainerSize().height - button.height / 2;
            }
            else
                button.y =Buttons[j - 1].getBottomBoundary() - button.height / 2;
            Buttons.push(button);
            scrollView.addChild(button);
        }

    },
    drawS9Buttons: function() {
        var scrollView = this._scrollView;
        var n = this._itemNumber;
        if(scrollView.getChildren())
            scrollView.removeAllChildren(true);
        var Buttons = [];
        var innerWidth = scrollView.width;

        for (var j = 0; j < n; j++) {
            var button_scale9 = new ccui.Button();
            button_scale9.setTouchEnabled(true);
            button_scale9.setScale9Enabled(true);
            button_scale9.loadTextures("ccs-res/cocosui/button.png", "ccs-res/cocosui/buttonHighlighted.png", "");
            button_scale9.width = 100;
            button_scale9.height = 32;
            button_scale9.x = innerWidth / 2;
            if(j === 0) {
                var innerHeight = n * 32;
                scrollView.setInnerContainerSize(cc.size(innerWidth, innerHeight));
                button_scale9.y = scrollView.getInnerContainerSize().height - button_scale9.height / 2;
            }
            else
                button_scale9.y = Buttons[j-1].getBottomBoundary() - button_scale9.height / 2;
            Buttons.push(button_scale9);
            scrollView.addChild(button_scale9);
        }
    }
});

var UIScrollViewTest_ScrollBar = UIMainLayer.extend({
    init: function () {
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();
            //init text
            this._topDisplayLabel.setString("Scroll bar is red, 65% opacity, auto hide time: 5 sec");
            this._topDisplayLabel.setFontSize(14);
            this._topDisplayLabel.x = widgetSize.width / 2.0;
            this._topDisplayLabel.y = widgetSize.height / 2.0 + this._topDisplayLabel.height * 1.5;

            this._bottomDisplayLabel.setString("");
            this._bottomDisplayLabel.x = widgetSize.width / 2;
            this._bottomDisplayLabel.y = widgetSize.height / 2 - this._bottomDisplayLabel.height * 3;

            var background = this._widget.getChildByName("background_Panel");

            // Create the scrollview
            var scrollView = new ccui.ScrollView();
            scrollView.setTouchEnabled(true);
            scrollView.setBounceEnabled(true);
            scrollView.setBackGroundColor(cc.color.GREEN);
            scrollView.setBackGroundColorType(ccui.Layout.BG_COLOR_SOLID);
            scrollView.setDirection(ccui.ScrollView.DIR_BOTH);
            scrollView.setInnerContainerSize(cc.size(480, 320));
            scrollView.setContentSize(cc.size(100, 100));
            var scrollViewSize = scrollView.getContentSize();

            scrollView.x = (widgetSize.width - background.width) / 2 + (background.width - scrollViewSize.width) / 2;
            scrollView.y = (widgetSize.height - background.height) / 2 + (background.height - scrollViewSize.height) / 2;

            this._mainNode.addChild(scrollView);

            scrollView.setScrollBarAutoHideTime(5);
            scrollView.setScrollBarColor(cc.color.RED);
            scrollView.setScrollBarOpacity(255 * 0.65);
            scrollView.setScrollBarWidth(5);

            return true;
        }
        return false;
    }
});

