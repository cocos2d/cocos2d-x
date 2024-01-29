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

//2015-01-14
var UITextTest = UIMainLayer.extend({
    init: function(){
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();

            this._bottomDisplayLabel.setString("Text");

            // Create the text
            var text = new ccui.Text("Text", "AmericanTypewriter", 30);
            text.setPosition(cc.p(widgetSize.width / 2, widgetSize.height / 2 + text.height / 4));
            this._mainNode.addChild(text);

            return true;
        }
    }
});

//2015-01-14
var UITextTest_LineWrap = UIMainLayer.extend({
    init: function(){
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();

            this._bottomDisplayLabel.setString("Text line wrap");

            // Create the line wrap
            var text = new ccui.Text("TextArea Widget can line wrap","AmericanTypewriter",32);
            text.ignoreContentAdaptWithSize(false);
            text.setContentSize(cc.size(280, 150));
            text.setTextHorizontalAlignment(cc.TEXT_ALIGNMENT_CENTER);
            text.setTouchScaleChangeEnabled(true);
            text.setTouchEnabled(true);
            text.addTouchEventListener(function(sender, type){
                if (type == ccui.Widget.TOUCH_ENDED){
                    if (text.width == 280){
                        text.setContentSize(cc.size(380,100));
                    }else {
                        text.setContentSize(cc.size(280, 150));
                    }
                }
            });
            text.setPosition(widgetSize.width / 2, widgetSize.height / 2 - text.height / 8);
            this._mainNode.addChild(text);

            return true;
        }
    }
});

//2015-01-14
var UILabelTest_Effect = UIMainLayer.extend({
    init: function(){
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();

            this._bottomDisplayLabel.setString("");

            var alert = new ccui.Text();
            alert.setString("Label Effect");
            alert.setFontName("Marker Felt");
            alert.setFontSize(30);
            alert.setColor(cc.color(159, 168, 176));
            alert.setPosition(widgetSize.width / 2, widgetSize.height / 2 - alert.height * 3.05);
            this._mainNode.addChild(alert);

            // create the shadow only label
            var shadow_label = new ccui.Text();

            shadow_label.enableShadow(cc.color.GRAY, cc.p(10, -10));
            shadow_label.setString("Shadow");
            shadow_label.setPosition(widgetSize.width / 2, widgetSize.height / 2 + shadow_label.height);

            this._mainNode.addChild(shadow_label);

            // create the stroke only label
            var glow_label = new ccui.Text();
            glow_label.setFontName("Marker Felt");
            glow_label.setString("Glow");
            glow_label.enableGlow(cc.color.RED);
            glow_label.setPosition(widgetSize.width / 2, widgetSize.height / 2);
            this._mainNode.addChild(glow_label);

            // create the label stroke and shadow
            var outline_label = new ccui.Text();
            outline_label.enableOutline(cc.color.BLUE, 2);
            outline_label.setString("Outline");
            outline_label.setPosition(widgetSize.width / 2, widgetSize.height / 2 - shadow_label.height);

            this._mainNode.addChild(outline_label);

            return true;
        }
    }
});

//2015-01-14
var UITextTest_TTF = UIMainLayer.extend({
    init: function(){
        if(this._super()){
            var widgetSize = this._widget.getContentSize();

            this._bottomDisplayLabel.setString("Text set TTF font");

            // Create the text, and set font with .ttf
            var text = new ccui.Text("Text","fonts/A Damn Mess.ttf",30);
            text.setPosition(widgetSize.width / 2, widgetSize.height / 2 + text.height / 4);
            this._mainNode.addChild(text);

            return true;
        }
    }
});

//2015-01-14
var UITextTest_IgnoreContentSize = UIMainLayer.extend({

    init: function(){
        if(this._super()){
            var widgetSize = this._widget.getContentSize();

            this._bottomDisplayLabel.setString("");

            var leftText = new ccui.Text("ignore content", "Marker Felt", 10);
            leftText.setPosition(cc.p(widgetSize.width / 2 - 50,
                widgetSize.height / 2));
            leftText.ignoreContentAdaptWithSize(false);
            leftText.setTextAreaSize(cc.size(60,60));
            leftText.setString("Text line with break\nText line with break\nText line with break\nText line with break\n");
            leftText.setTouchScaleChangeEnabled(true);
            leftText.setTouchEnabled(true);
            this._mainNode.addChild(leftText);

            var rightText = new ccui.Text("ignore content", "Marker Felt", 10);
            rightText.setPosition(cc.p(widgetSize.width / 2 + 50,
                widgetSize.height / 2));
            rightText.setString("Text line with break\nText line with break\nText line with break\nText line with break\n");
            //note: setTextAreaSize must be used with ignoreContentAdaptWithSize(false)
            rightText.setTextAreaSize(cc.size(100,30));
            rightText.ignoreContentAdaptWithSize(false);
            this._mainNode.addChild(rightText);

            var halighButton = new ccui.Button();
            halighButton.setTitleText("Alignment Right");
            halighButton.addClickEventListener(function(){
                leftText.setTextHorizontalAlignment(cc.TEXT_ALIGNMENT_RIGHT);
                rightText.setTextHorizontalAlignment(cc.TEXT_ALIGNMENT_RIGHT);
            });
            halighButton.setPosition(cc.p(widgetSize.width/2 - 50,
                    widgetSize.height/2 - 50));
            this._mainNode.addChild(halighButton);

            return true;
        }
    }

});
