/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
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
var TAG_LABEL1 = 550;
var TAG_LABEL2 = 551;
var TAG_LABEL3 = 552;
var TAG_LABEL4 = 553;

var fontIdx = 0;

var fontList = [

    // System Fonts
    "sans-serif",
    "sans-serif-light",
    "Verdana",
    "Lucida Sans Unicode",
    "Bookman Old Style",
    "Symbol",
    "Georgia",
    "Trebuchet MS",
    "Comic Sans MS",
    "Arial Black",
    "Tahoma",
    "Impact",

    // custom TTF
    "American Typewriter",
    "Marker Felt",
    "A Damn Mess",
    "Abberancy",
    "Abduction",
    "Paint Boy",
    "Schwarzwald",
    "Scissor Cuts"
];


function nextFontTestAction() {
    fontIdx++;
    fontIdx = fontIdx % fontList.length;

    if(window.sideIndexBar){
        fontIdx = window.sideIndexBar.changeTest(fontIdx, 16);
    }

    return fontList[fontIdx];
}

function backFontTestAction() {
    fontIdx--;
    if (fontIdx < 0) {
        fontIdx += fontList.length;
    }

    if(window.sideIndexBar){
        fontIdx = window.sideIndexBar.changeTest(fontIdx, 16);
    }

    return fontList[fontIdx];
}

function restartFontTestAction() {
    return fontList[fontIdx];
}
FontTestScene = TestScene.extend({

    runThisTest:function (num) {

        fontIdx = num || fontIdx;

        var layer = new FontTest();
        this.addChild(layer);

        director.runScene(this);
    }
});

var FontTest = BaseTestLayer.extend({
    ctor:function () {
        this._super(cc.color(0,0,0,255), cc.color(98,99,117,255));

        this.showFont(restartFontTestAction());

    },
    showFont:function (pFont) {
        this.removeChildByTag(TAG_LABEL1, true);
        this.removeChildByTag(TAG_LABEL2, true);
        this.removeChildByTag(TAG_LABEL3, true);
        this.removeChildByTag(TAG_LABEL4, true);

        var winSize = director.getWinSize();

        var top = new cc.LabelTTF(pFont, pFont, 24);
        var left = new cc.LabelTTF("alignment left", pFont, 32, cc.size(winSize.width, 50), cc.TEXT_ALIGNMENT_LEFT);
        var center = new cc.LabelTTF("alignment center", pFont, 32, cc.size(winSize.width, 50), cc.TEXT_ALIGNMENT_CENTER);
        var right = new cc.LabelTTF("alignment right", pFont, 32, cc.size(winSize.width, 50), cc.TEXT_ALIGNMENT_RIGHT);

        top.x = winSize.width / 2;
        top.y = winSize.height * 3 / 4;
        left.x = winSize.width / 2;
        left.y = winSize.height / 2;
        center.x = winSize.width / 2;
        center.y = winSize.height * 3 / 8;
        right.x = winSize.width / 2;
        right.y = winSize.height / 4;

        this.addChild(left, 0, TAG_LABEL1);
        this.addChild(right, 0, TAG_LABEL2);
        this.addChild(center, 0, TAG_LABEL3);
        this.addChild(top, 0, TAG_LABEL4);

    },

    onBackCallback:function (sender) {
        this.showFont(backFontTestAction());
    },
    onRestartCallback:function (sender) {
        this.showFont(restartFontTestAction());
    },
    onNextCallback:function (sender) {
        this.showFont(nextFontTestAction());
    },
    subtitle:function () {
        return "Font test";
    },
    title:function () {
        return "" + fontList[fontIdx];
    },

    // automation
    numberOfPendingTests:function() {
        return ( (fontList.length-1) - fontIdx );
    },
    getTestNumber:function() {
        return fontIdx;
    }

});
