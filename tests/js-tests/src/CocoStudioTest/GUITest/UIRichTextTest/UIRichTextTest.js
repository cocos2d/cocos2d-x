/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
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

var UIRichTextTest = UISceneEditor.extend({
    _richText:null,
    init: function () {
        if (this._super()) {
            //init text
            this._topDisplayLabel.setString("");
            this._bottomDisplayLabel.setString("RichText");

            var widgetSize = this._widget.getContentSize();
            var button = new ccui.Button();
            button.setTouchEnabled(true);
            button.loadTextures("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png", "");
            button.setTitleText("switch");
            button.setPosition(cc.p(widgetSize.width / 2, widgetSize.height / 2 + button.getContentSize().height * 2.5));
            button.addTouchEventListener(this.touchEvent,this);
            this._mainNode.addChild(button);


            // RichText
            var richText = new ccui.RichText();
            richText.ignoreContentAdaptWithSize(false);
            richText.setContentSize(cc.size(120, 100));

            var re1 = new ccui.RichElementText(1, cc.color.WHITE, 255, "This color is white. ", "Helvetica", 10);
            var re2 = new ccui.RichElementText(2, cc.color.YELLOW, 255, "And this is yellow. ", "Helvetica", 10);
            var re3 = new ccui.RichElementText(3, cc.color.BLUE, 255, "This one is blue. ", "Helvetica", 10);
            var re4 = new ccui.RichElementText(4, cc.color.GREEN, 255, "And green. ", "Helvetica", 10);
            var re5 = new ccui.RichElementText(5, cc.color.RED, 255, "Last one is red ", "Helvetica", 10);

            var reimg = new ccui.RichElementImage(6, cc.color.WHITE, 255, "ccs-res/cocosui/sliderballnormal.png");

            ccs.armatureDataManager.addArmatureFileInfo("ccs-res/cocosui/100/100.ExportJson");
            var pAr = new ccs.Armature("100");
            pAr.getAnimation().play("Animation1");

            var recustom = new ccui.RichElementCustomNode(1, cc.color.WHITE, 255, pAr);
            var re6 = new ccui.RichElementText(7, cc.color.ORANGE, 255, "Have fun!! ", "Helvetica", 10);
            richText.pushBackElement(re1);
            richText.insertElement(re2, 1);
            richText.pushBackElement(re3);
            richText.pushBackElement(re4);
            richText.pushBackElement(re5);
            richText.insertElement(reimg, 2);
            richText.pushBackElement(recustom);
            richText.pushBackElement(re6);

            richText.setPosition(cc.p(widgetSize.width / 2, widgetSize.height / 2));

            this._mainNode.addChild(richText);
            this._richText = richText;
            return true;
        }
        return false;
    },
    touchEvent: function (sender, type) {
        if (type == ccui.Widget.TOUCH_ENDED) {
            if (this._richText.isIgnoreContentAdaptWithSize()) {
                this._richText.ignoreContentAdaptWithSize(false);
                this._richText.setContentSize(cc.size(120, 100));
            }
            else {
                this._richText.ignoreContentAdaptWithSize(true);
            }
        }
    }
});