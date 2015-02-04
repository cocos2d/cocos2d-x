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

var UIImageViewTest = UIScene.extend({
    init: function () {
        if (this._super()) {
            //init text
            this._topDisplayLabel.setString("");
            this._bottomDisplayLabel.setString("ImageView");

            var widgetSize = this._widget.getContentSize();
            // Create the imageview
            var imageView = new ccui.ImageView();
            imageView.loadTexture("res/cocosui/ccicon.png");
            imageView.x = widgetSize.width / 2;
	        imageView.y = widgetSize.height / 2 + imageView.height / 4;
            this._mainNode.addChild(imageView);

            return true;
        }
        return false;
    }
});

var UIImageViewTest_Scale9 = UIScene.extend({
    init: function () {
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();
            //init text
            this._topDisplayLabel.setString("");
            this._bottomDisplayLabel.setString("ImageView scale9 render");

            // Create the imageview
            var imageView = new ccui.ImageView();
            imageView.setScale9Enabled(true);
            imageView.loadTexture("res/cocosui/buttonHighlighted.png");
            imageView.setContentSize(cc.size(200, 85));
            imageView.x = widgetSize.width / 2;
	        imageView.y = widgetSize.height / 2 + imageView.getContentSize().height / 4;
            this._mainNode.addChild(imageView);

            return true;
        }
        return false;
    }
});