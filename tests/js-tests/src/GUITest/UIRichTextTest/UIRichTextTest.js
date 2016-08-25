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

var UIRichTextTest = UIMainLayer.extend({
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
            richText.width = 120;
            richText.height = 100;

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

            richText.x = widgetSize.width / 2;
            richText.y = widgetSize.height / 2;

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
            } else {
                this._richText.ignoreContentAdaptWithSize(true);
            }
        }
    }
});

//
// UIRichTextXMLBasic
//
var UIRichTextXMLBasic = UIMainLayer.extend({
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
            richText.initWithXML("This is just a simple text. no xml tags here. testing the basics. testing word-wrapping. testing, testing, testing");

            richText.ignoreContentAdaptWithSize(false);
            richText.width = 120;
            richText.height = 100;

            richText.x = widgetSize.width / 2;
            richText.y = widgetSize.height / 2;

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
            } else {
                this._richText.ignoreContentAdaptWithSize(true);
            }
        }
    }
});

//
// UIRichTextXMLSmallBig
//
var UIRichTextXMLSmallBig = UIMainLayer.extend({
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
            richText.initWithXML("Regular size.<small>smaller size.</small><big>bigger.<small>normal.</small>bigger</big>.normal.");

            richText.ignoreContentAdaptWithSize(false);
            richText.width = 120;
            richText.height = 100;

            richText.x = widgetSize.width / 2;
            richText.y = widgetSize.height / 2;

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
            } else {
                this._richText.ignoreContentAdaptWithSize(true);
            }
        }
    }
});

//
// UIRichTextXMLColor
//
var UIRichTextXMLColor = UIMainLayer.extend({
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
            richText.initWithXML("Defaul color.<font color='#ff0000'>red.<font color='#00ff00'>green</font>red again.</font>default again");

            richText.ignoreContentAdaptWithSize(false);
            richText.width = 120;
            richText.height = 100;

            richText.x = widgetSize.width / 2;
            richText.y = widgetSize.height / 2;

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
            } else {
                this._richText.ignoreContentAdaptWithSize(true);
            }
        }
    }
});

//
// UIRichTextXMLSUIB
//
var UIRichTextXMLSUIB = UIMainLayer.extend({
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
            richText.initWithXML("system font: <u>underline</u><i>italics</i><b>bold</b><del>strike-through</del>");

            richText.ignoreContentAdaptWithSize(false);
            richText.width = 120;
            richText.height = 100;

            richText.x = widgetSize.width / 2;
            richText.y = widgetSize.height / 2;

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
            } else {
                this._richText.ignoreContentAdaptWithSize(true);
            }
        }
    }
});

//
// UIRichTextXMLSUIB2
//
var UIRichTextXMLSUIB2 = UIMainLayer.extend({
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
            richText.initWithXML("<font face='fonts/Marker Felt.ttf' size='24'>ttf font: <u>underline</u><i>italics</i><b>bold</b><del>strike-through</del></font>");

            richText.ignoreContentAdaptWithSize(false);
            richText.width = 120;
            richText.height = 100;

            richText.x = widgetSize.width / 2;
            richText.y = widgetSize.height / 2;

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
            } else {
                this._richText.ignoreContentAdaptWithSize(true);
            }
        }
    }
});

//
// UIRichTextXMLSUIB3
//
var UIRichTextXMLSUIB3 = UIMainLayer.extend({
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
            richText.initWithXML("<font face='fonts/Marker Felt.ttf' size='20'>ttf font: <i><u>italics and underline</u></i><del><b>bold and strike-through</b></del></font>");

            richText.ignoreContentAdaptWithSize(false);
            richText.width = 120;
            richText.height = 100;

            richText.x = widgetSize.width / 2;
            richText.y = widgetSize.height / 2;

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
            } else {
                this._richText.ignoreContentAdaptWithSize(true);
            }
        }
    }
});

//
// UIRichTextXMLImg
//
var UIRichTextXMLImg = UIMainLayer.extend({
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
            richText.initWithXML("you should see an image here: <img src='ccs-res/cocosui/sliderballnormal.png'/> and this is text again. and this is the same image, but bigger: <img src='ccs-res/cocosui/sliderballnormal.png' width='30' height='30' /> and here goes text again");

            richText.ignoreContentAdaptWithSize(false);
            richText.width = 120;
            richText.height = 100;

            richText.x = widgetSize.width / 2;
            richText.y = widgetSize.height / 2;

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
            } else {
                this._richText.ignoreContentAdaptWithSize(true);
            }
        }
    }
});

//
// UIRichTextXMLUrl
//
var UIRichTextXMLUrl = UIMainLayer.extend({
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
            richText.initWithXML("And this link will redirect you to google: <a href='http://www.google.com'>click me</a>");

            richText.ignoreContentAdaptWithSize(false);
            richText.width = 120;
            richText.height = 100;

            richText.x = widgetSize.width / 2;
            richText.y = widgetSize.height / 2;

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
            } else {
                this._richText.ignoreContentAdaptWithSize(true);
            }
        }
    }
});

//
// UIRichTextXMLFace
//
var UIRichTextXMLFace = UIMainLayer.extend({
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
            richText.initWithXML("<font size='20' face='fonts/Marker Felt.ttf'>Marker Felt 20.<font face='fonts/arial.ttf'>Arial 20.</font></font><font face='font/Thonburi.ttf' size='24' color='#0000ff'>Thonburi 24 blue</font>");

            richText.ignoreContentAdaptWithSize(false);
            richText.width = 120;
            richText.height = 100;

            richText.x = widgetSize.width / 2;
            richText.y = widgetSize.height / 2;

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
            } else {
                this._richText.ignoreContentAdaptWithSize(true);
            }
        }
    }
});

//
// UIRichTextXMLBR
//
var UIRichTextXMLBR = UIMainLayer.extend({
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
            richText.initWithXML("this is one line.<br/>this should be in another line.<br/>and this is another line");

            richText.ignoreContentAdaptWithSize(false);
            richText.width = 120;
            richText.height = 100;

            richText.x = widgetSize.width / 2;
            richText.y = widgetSize.height / 2;

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
            } else {
                this._richText.ignoreContentAdaptWithSize(true);
            }
        }
    }
});

//
// UIRichTextXMLInvalid
//
var UIRichTextXMLInvalid = UIMainLayer.extend({
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
            richText.initWithXML("this is an invalid xml. <i>no closing tag");

            richText.ignoreContentAdaptWithSize(false);
            richText.width = 120;
            richText.height = 100;

            richText.x = widgetSize.width / 2;
            richText.y = widgetSize.height / 2;

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
            } else {
                this._richText.ignoreContentAdaptWithSize(true);
            }
        }
    }
});
