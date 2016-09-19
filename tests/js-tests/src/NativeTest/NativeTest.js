/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.

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

var NATIVE_TEST_LINE_SPACE = 40;
var NATIVE_TEST_ITEM_TAG_BASIC = 1000;

var nativetestItemNames = [
    {
        itemTitle:"FileUtilsTest",
        testScene:function () {
            startFileUtilsTest();
        }
    },
    {
        itemTitle:"AudioEngineTest",
        testScene:function () {
            AudioTestFlow.start();
        }
    },
    {
        itemTitle:"JSBExtendTest",
        testScene:function () {
            cc.director.runScene(new JSBExtendTest());
        }
    }
];

var NativeMainLayer = cc.Layer.extend({
    onEnter:function () {
        this._super();

        var winSize = cc.director.getWinSize();

        var pMenu = new cc.Menu();
        pMenu.x = 0;
        pMenu.y = 0;
        cc.MenuItemFont.setFontName("Arial");
        cc.MenuItemFont.setFontSize(24);
        for (var i = 0; i < nativetestItemNames.length; ++i) {
            var selItem = nativetestItemNames[i];
            var pItem = new cc.MenuItemFont(selItem.itemTitle, this.menuCallback, this);
            pItem.x = winSize.width / 2;
            pItem.y = winSize.height - (i + 1) * NATIVE_TEST_LINE_SPACE;
            pMenu.addChild(pItem, NATIVE_TEST_ITEM_TAG_BASIC + i);
        }
        this.addChild(pMenu);
    },

    menuCallback:function (sender) {
        var nIndex = sender.zIndex - NATIVE_TEST_ITEM_TAG_BASIC;
        nativetestItemNames[nIndex].testScene();
    }
});

var NativeTestScene = TestScene.extend({
    runThisTest:function () {
        var pLayer = new NativeMainLayer();
        this.addChild(pLayer);
        cc.director.runScene(this);
    }
});
