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

var UIScrollViewTest_Vertical = UIScene.extend({
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
            imageView.loadTexture("res/cocosui/ccicon.png");

            var innerWidth = scrollView.width;
            var innerHeight = scrollView.height + imageView.height;

            scrollView.setInnerContainerSize(cc.size(innerWidth, innerHeight));

            var button = new ccui.Button();
            button.setTouchEnabled(true);
            button.loadTextures("res/cocosui/animationbuttonnormal.png", "res/cocosui/animationbuttonpressed.png", "");
            button.x = innerWidth / 2;
            button.y = scrollView.getInnerContainerSize().height - button.height / 2;
            scrollView.addChild(button);

            var textButton = new ccui.Button();
            textButton.setTouchEnabled(true);
            textButton.loadTextures("res/cocosui/backtotopnormal.png", "res/cocosui/backtotoppressed.png", "");
            textButton.setTitleText("Text Button");
            textButton.x = innerWidth / 2;
            textButton.y = button.getBottomBoundary() - button.height;
            scrollView.addChild(textButton);

            var button_scale9 = new ccui.Button();
            button_scale9.setTouchEnabled(true);
            button_scale9.setScale9Enabled(true);
            button_scale9.loadTextures("res/cocosui/button.png", "res/cocosui/buttonHighlighted.png", "");
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

var UIScrollViewTest_Horizontal = UIScene.extend({
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
            imageView.loadTexture("res/cocosui/ccicon.png");

            var innerWidth = scrollViewRect.width + imageView.getContentSize().width;
            var innerHeight = scrollViewRect.height;

            scrollView.setInnerContainerSize(cc.size(innerWidth, innerHeight));

            var button = new ccui.Button();
            button.setTouchEnabled(true);
            button.loadTextures("res/cocosui/animationbuttonnormal.png", "res/cocosui/animationbuttonpressed.png", "");
            button.x = button.width / 2;
            button.y = scrollView.getInnerContainerSize().height - button.height / 2;
            scrollView.addChild(button);

            var textButton = new ccui.Button();
            textButton.setTouchEnabled(true);
            textButton.loadTextures("res/cocosui/backtotopnormal.png", "res/cocosui/backtotoppressed.png", "");
            textButton.setTitleText("Text Button");
            textButton.x = button.getRightBoundary() + button.width / 2;
            textButton.y = button.getBottomBoundary() - button.height;
            scrollView.addChild(textButton);

            var button_scale9 = new ccui.Button();
            button_scale9.setTouchEnabled(true);
            button_scale9.setScale9Enabled(true);
            button_scale9.loadTextures("res/cocosui/button.png", "res/cocosui/buttonHighlighted.png", "");
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

var UIScrollViewTest_Both = UIScene.extend({
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
            scrollView.setBackGroundImage("res/cocosui/green_edit.png");
            scrollView.setContentSize(cc.size(210, 122));
            var scrollViewSize = scrollView.getContentSize();

            scrollView.x = (widgetSize.width - background.width) / 2 + (background.width - scrollViewSize.width) / 2;
            scrollView.y = (widgetSize.height - background.height) / 2 + (background.height - scrollViewSize.height) / 2;
            this._mainNode.addChild(scrollView);

            var imageView = new ccui.ImageView();
            imageView.loadTexture("res/cocosui/b11.png");
            scrollView.addChild(imageView);

            scrollView.setInnerContainerSize(cc.size(imageView.width, imageView.height));
            imageView.x = imageView.width/2;
            imageView.y = imageView.height/2;

            return true;
        }
        return false;
    }
});

var UIScrollViewTest_ScrollToPercentBothDirection = UIScene.extend({
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
            imageView.loadTexture("res/cocosui/Hello.png");
            imageView.x = 240;
            imageView.y = 160;
            scrollView.addChild(imageView);

            return true;
        }
        return false;
    }
});

var UIScrollViewTest_ScrollToPercentBothDirection_Bounce = UIScene.extend({
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
            imageView.loadTexture("res/cocosui/Hello.png");
            imageView.x = 240;
            imageView.y = 160;
            scrollView.addChild(imageView);

            return true;
        }
        return false;
    }
});
