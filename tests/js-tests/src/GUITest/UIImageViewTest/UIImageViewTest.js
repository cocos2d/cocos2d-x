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
            var imageView = new ccui.ImageView("ccs-res/cocosui/ccicon.png");
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
            imageView.loadTexture("ccs-res/cocosui/buttonHighlighted.png");
            imageView.setContentSize(cc.size(200, 85));
            imageView.x = widgetSize.width / 2;
	        imageView.y = widgetSize.height / 2 + imageView.getContentSize().height / 4;
            this._mainNode.addChild(imageView);

            return true;
        }
        return false;
    }
});

//2015-01-14
var UIImageViewTest_ContentSize = UIScene.extend({
    init: function(){
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();

            this._bottomDisplayLabel.setString("");
            var alert = new ccui.Text("ImageView ContentSize Change", "Marker Felt", 26);
            alert.setColor(cc.color(159, 168, 176));
            alert.setPosition(cc.p(widgetSize.width / 2, widgetSize.height / 2 - alert.getContentSize().height * 2.125));

            this._mainNode.addChild(alert);

            var status = new ccui.Text("child ImageView position percent", "Marker Felt", 16);
            status.setColor(cc.color.RED);
            status.setPosition(cc.p(widgetSize.width/2, widgetSize.height/2 + 80));
            this._mainNode.addChild(status,20);

            // Create the imageview
            var imageView = new ccui.ImageView("ccs-res/cocosui/buttonHighlighted.png");
            imageView.setScale9Enabled(true);
            imageView.setContentSize(cc.size(200, 80));
            imageView.setPosition(cc.p(widgetSize.width / 2, widgetSize.height / 2));

            var imageViewChild = new ccui.ImageView("ccs-res/cocosui/buttonHighlighted.png");
            imageViewChild.setScale9Enabled(true);
            imageViewChild.setSizeType(ccui.Widget.SIZE_PERCENT);
            imageViewChild.setPositionType(ccui.Widget.POSITION_PERCENT);
            imageViewChild.setSizePercent(cc.p(0.5, 0.5));
            imageViewChild.setPositionPercent(cc.p(0.5, 0.5));
            //imageViewChild.setPosition(cc.p(widgetSize.width / 2, widgetSize.height / 2));

            var imageViewChild2 = new ccui.ImageView("ccs-res/cocosui/buttonHighlighted.png");
            imageViewChild2.setScale9Enabled(true);
            imageViewChild2.setSizeType(ccui.Widget.SIZE_PERCENT);
            imageViewChild2.setPositionType(ccui.Widget.POSITION_PERCENT);
            imageViewChild2.setSizePercent(cc.p(0.5, 0.5));
            imageViewChild2.setPositionPercent(cc.p(0.5, 0.5));
            imageViewChild.addChild(imageViewChild2);

            imageView.addChild(imageViewChild);
            window.aa = imageView;

            imageView.setTouchEnabled(true);
            imageView.addTouchEventListener(function(sender, type){
                if (type == ccui.Widget.TOUCH_ENDED) {
                    var width = (Math.random() * 200 | 0) + 50;
                    var height = (Math.random() * 80 | 0) + 30;
                    imageView.setContentSize(cc.size(width, height));

                    imageViewChild.setPositionPercent(cc.p(Math.random().toFixed(2), Math.random().toFixed(2)));
                    status.setString("child ImageView position percent: "+imageViewChild.getPositionPercent().x+", "+imageViewChild.getPositionPercent().y);
                }
            });
            this._mainNode.addChild(imageView);
            return true;
        }
    }
});

//2015-01-14
var UIImageViewFlipTest = UIScene.extend({
    init: function(){
        if (this._super()) {
            cc.spriteFrameCache.addSpriteFrames("Images/blocks9ss.plist");
            var widgetSize = this._widget.getContentSize();

            this._bottomDisplayLabel.setString("ImageView flip test");

            // Create the imageview
            var imageView = new ccui.ImageView("blocks9r.png", ccui.Widget.PLIST_TEXTURE);
            imageView.setScale9Enabled(true);
            imageView.setContentSize(cc.size(250, 115));
            imageView.setFlippedX(true);
            imageView.setScale(0.5);
            imageView.ignoreContentAdaptWithSize(false);
            imageView.setPosition(cc.p(widgetSize.width / 2, widgetSize.height / 2));

            this._mainNode.addChild(imageView);

            var toggleButton = new ccui.Button();
            toggleButton.setTitleText("Toggle FlipX");
            var ip = imageView.getPosition();
            toggleButton.setPosition(ip.x - 50, ip.y - imageView.getContentSize().height/2 - 20);
            this.addChild(toggleButton);
            toggleButton.addClickEventListener(function(){
                imageView.setFlippedX(!imageView.isFlippedX());
            });

            var toggleScale9 = new ccui.Button();
            toggleScale9.setTitleText("Toggle Scale9");
            var ip9 = imageView.getPosition();
            toggleScale9.setPosition(ip9.x + 50, ip9.y - imageView.getContentSize().height/2- 20);
            this.addChild(toggleScale9);
            toggleScale9.addClickEventListener(function(){
                imageView.setScale9Enabled(!imageView.isScale9Enabled());
                //after switching scale9, you must call setContentSize to keep the size not change
                imageView.setContentSize(cc.size(250, 115));
            });
            return true;
        }
    }
});