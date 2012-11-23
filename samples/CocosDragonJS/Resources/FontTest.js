/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011      Zynga Inc.

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
    "Verdana",
    "Lucida Sans Unicode",
    "Bookman Old Style",
    "Symbol",
    "Georgia",
    "Trebuchet MS",
    "Comic Sans MS",
    "Arial Black",
    "Tahoma",
    "Impact"
];


function nextFontTestAction() {
    fontIdx++;
    fontIdx = fontIdx % fontList.length;
    return fontList[fontIdx]
}

function backFontTestAction() {
    fontIdx--;
    if (fontIdx < 0) {
        fontIdx += fontList.length;
    }

    return fontList[fontIdx];
}

function restartFontTestAction() {
    return fontList[fontIdx];
}
FontTestScene = TestScene.extend({

    runThisTest:function () {
        var layer = FontTest.node();
        this.addChild(layer);

        cc.Director.getInstance().replaceScene(this);
    }
});

FontTest = cc.Layer.extend({
    ctor:function () {
        var size = cc.Director.getInstance().getWinSize();
        var item1 = cc.MenuItemImage.create(s_pathB1, s_pathB2, this, this.backCallback);
        var item2 = cc.MenuItemImage.create(s_pathR1, s_pathR2, this, this.restartCallback);
        var item3 = cc.MenuItemImage.create(s_pathF1, s_pathF2, this, this.nextCallback);

        var menu = cc.Menu.create(item1, item2, item3, null);
        menu.setPosition(cc.p(0,0));
        item1.setPosition(cc.p(size.width / 2 - 100, 30));
        item2.setPosition(cc.p(size.width / 2, 30));
        item3.setPosition(cc.p(size.width / 2 + 100, 30));
        this.addChild(menu, 1);

        this.showFont(restartFontTestAction());

    },
    showFont:function (pFont) {
        this.removeChildByTag(TAG_LABEL1, true);
        this.removeChildByTag(TAG_LABEL2, true);
        this.removeChildByTag(TAG_LABEL3, true);
        this.removeChildByTag(TAG_LABEL4, true);

        var s = cc.Director.getInstance().getWinSize();

        var top = cc.LabelTTF.create(pFont, pFont, 24);
        var left = cc.LabelTTF.create("alignment left", pFont, 32, cc.size(s.width, 50), cc.TEXT_ALIGNMENT_LEFT);
        var center = cc.LabelTTF.create("alignment center", pFont, 32, cc.size(s.width, 50), cc.TEXT_ALIGNMENT_CENTER);
        var right = cc.LabelTTF.create("alignment right", pFont, 32, cc.size(s.width, 50), cc.TEXT_ALIGNMENT_RIGHT);

        top.setPosition(cc.p(s.width / 2, s.height * 3 / 4));
        left.setPosition(cc.p(s.width / 2, s.height / 2));
        center.setPosition(cc.p(s.width / 2, s.height * 3 / 8));
        right.setPosition(cc.p(s.width / 2, s.height / 4));

        this.addChild(left, 0, TAG_LABEL1);
        this.addChild(right, 0, TAG_LABEL2);
        this.addChild(center, 0, TAG_LABEL3);
        this.addChild(top, 0, TAG_LABEL4);

    },

    restartCallback:function (sender) {
        this.showFont(restartFontTestAction());
    },
    nextCallback:function (sender) {
        this.showFont(nextFontTestAction());
    },
    backCallback:function (sender) {
        this.showFont(backFontTestAction());
    },
    title:function () {
        return "Font test";
    }


});

FontTest.node = function () {
    var ret = new FontTest();
    ret.init();
    return ret;
};
