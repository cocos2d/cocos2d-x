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

var UIPageViewTest = UIScene.extend({
    init: function () {
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();
            //init text
            this._topDisplayLabel.setString("Move by horizontal direction");
            this._topDisplayLabel.x = widgetSize.width / 2.0;
            this._topDisplayLabel.y = widgetSize.height / 2.0 + this._topDisplayLabel.height * 1.5;
            this._bottomDisplayLabel.setString("PageView");
            this._bottomDisplayLabel.x = widgetSize.width / 2;
            this._bottomDisplayLabel.y = widgetSize.height / 2 - this._bottomDisplayLabel.height * 3;

            var background = this._widget.getChildByName("background_Panel");

            // Create the page view
            var pageView = new ccui.PageView();
            pageView.setTouchEnabled(true);
            pageView.setContentSize(cc.size(240, 130));
            pageView.x = (widgetSize.width - background.width) / 2 + (background.width - pageView.width) / 2;
            pageView.y = (widgetSize.height - background.height) / 2 + (background.height - pageView.height) / 2;

            for (var i = 0; i < 3; ++i) {
                var layout = new ccui.Layout();
                layout.setContentSize(cc.size(240, 130));
                var layoutRect = layout.getContentSize();

                var imageView = new ccui.ImageView();
                imageView.setTouchEnabled(true);
                imageView.setScale9Enabled(true);
                imageView.loadTexture("res/cocosui/scrollviewbg.png");
                imageView.setContentSize(cc.size(240, 130));
                imageView.x = layoutRect.width / 2;
                imageView.y = layoutRect.height / 2;
                layout.addChild(imageView);

                var text = new ccui.Text();
                text.string = "page" + (i + 1);
                text.font = "30px 'Marker Felt'";
                text.color = cc.color(192, 192, 192);
                text.x = layoutRect.width / 2;
                text.y = layoutRect.height / 2;
                layout.addChild(text);

                pageView.addPage(layout);
            }
            pageView.addEventListener(this.pageViewEvent, this);
            this._mainNode.addChild(pageView);

            return true;
        }
        return false;
    },

    pageViewEvent: function (sender, type) {
        switch (type) {
            case ccui.PageView.EVENT_TURNING:
                var pageView = sender;
                this._topDisplayLabel.setString("page = " + (pageView.getCurPageIndex() + 1));
                break;
            default:
                break;
        }
    }
});
