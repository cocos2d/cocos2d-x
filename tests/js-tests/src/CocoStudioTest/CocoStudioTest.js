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

var LINE_SPACE = 40;
var ITEM_TAG_BASIC = 1000;

var cocoStudioTestItemNames = [
    {
        itemTitle:"CocoStudioArmatureTest",
        testScene:function () {
            runArmatureTestScene();
        }
    },
    {
        itemTitle:"CocoStudioGUITest",
        testScene:function () {
            runGuiTestMain();
        }
    },
    {
        itemTitle:"CocoStudioSceneTest",
        testScene:function () {
            runSceneEditorTest();
        }
    },
    {
        itemTitle:"ParserTest",
        testScene:function(){
            runParserTest();
        }
    },
    {
        itemTitle:"ActionTimeLineTest",
        testScene:function () {
            runActionTimeLineTest();
        }
    }
];

if(!cc.sys.isNative){
    cocoStudioTestItemNames.push({
        itemTitle: "CocoStudioComponentsTest",
        testScene: function () {
            runComponentsTestLayer();
        }
    });
    cocoStudioTestItemNames.push({
        itemTitle:"CustomWidget",
        testScene:function(){
            runCustomGUITest();
        }
    });
}

var CocoStudioMainLayer = cc.Layer.extend({
    onEnter:function () {
        this._super();

        var winSize = cc.director.getWinSize();

        var pMenu = new cc.Menu();
        pMenu.x = 0;
	    pMenu.y = 0;
        cc.MenuItemFont.setFontName("Arial");
        cc.MenuItemFont.setFontSize(24);
        for (var i = 0; i < cocoStudioTestItemNames.length; ++i) {
            var selItem = cocoStudioTestItemNames[i];
            var pItem = new cc.MenuItemFont(selItem.itemTitle,
                this.menuCallback, this);
            pItem.x = winSize.width / 2;
	        pItem.y = winSize.height - (i + 1) * LINE_SPACE;
            pMenu.addChild(pItem, ITEM_TAG_BASIC + i);
        }
        this.addChild(pMenu);
    },

    menuCallback:function (sender) {
        var nIndex = sender.zIndex - ITEM_TAG_BASIC;
        cocoStudioTestItemNames[nIndex].testScene();
    }
});

var cocoStudioOldApiFlag = 0;
var CocoStudioTestScene = TestScene.extend({

    onEnter: function(){
        TestScene.prototype.onEnter.call(this);

        var winSize = cc.director.getWinSize();

        var pMenu = new cc.Menu();
        pMenu.x = 0;
        pMenu.y = 0;
        cc.MenuItemFont.setFontName("Arial");
        cc.MenuItemFont.setFontSize(24);
        var str = "new api";
        if(cocoStudioOldApiFlag){
            str = "old api";
        }
        var pItem = new cc.MenuItemFont(str,
            function(){
                if(cocoStudioOldApiFlag){
                    cocoStudioOldApiFlag = 0;
                    pItem.setString("new api");
                }else{
                    cocoStudioOldApiFlag = 1;
                    pItem.setString("old api");
                }
            }, this);
        pItem.x = 50;
        pItem.y = winSize.height - 20;
        pMenu.addChild(pItem);

        this.addChild(pMenu);
    },

    runThisTest:function () {
        var pLayer = new CocoStudioMainLayer();
        this.addChild(pLayer);
        cc.director.runScene(this);
    }
});
