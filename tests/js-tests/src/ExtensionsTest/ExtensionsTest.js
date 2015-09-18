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

var TEST_NOTIFICATIONCENTER = 0;
var TEST_CCCONTROLBUTTON = 1;
var TEST_COCOSBUILDER = 2;
var TEST_HTTPCLIENT = 3;

var extensionsTestItemNames = [
    /*    {
     itemTitle:"NotificationCenterTest",
     testScene:function () {
     //runNotificationCenterTest();
     cc.log("not implement");
     }
     },*/
    {
        itemTitle:"CCControlButtonTest",
        testScene:function () {
            var pManager = ControlSceneManager.getInstance();
            var pScene = pManager.currentControlScene();
	        cc.director.runScene(pScene);
        }
    },
    {
        itemTitle:"CocosBuilderTest",
        testScene:function () {
            var pScene = new CocosBuilderTestScene();
            if (pScene) {
                pScene.runThisTest();
            }
        }
    },
    /*    {
     itemTitle:"HttpClientTest",
     testScene:function () {
     //runHttpClientTest();
     cc.log("not implement");
     }
     },*/
    {
        itemTitle:"TableViewTest",
        testScene:function () {
            runTableViewTest();
        }
    },
    {
        itemTitle:"WebSocketTest",
        testScene:function () {
            runWebSocketTest();
        }
    },
    {
        itemTitle:"SocketIOTest",
        testScene:function () {
            runSocketIOTest();
        }
    },
    {
        itemTitle:"CCPoolTest",
        testScene:function () {
            runCCPoolTest();
        }
    }
];

if(!cc.sys.isNative || cc.sys.OS_LINUX !== cc.sys.os){
    extensionsTestItemNames.push({
        itemTitle:"EditBoxTest",
        testScene:function () {
            runEditBoxTest();
        }
    });
}

if (cc.sys.isNative && cc.sys.OS_IOS == cc.sys.os) {
    extensionsTestItemNames.push({
        itemTitle:"PluginTest",
        testScene:function () {
            var testScene = pluginXSceneManager.currentPluginXScene();
            cc.director.runScene(testScene);
        }
    })
}

if (cc.sys.isNative && cc.sys.OS_WINDOWS != cc.sys.os) {
    extensionsTestItemNames.push({
        itemTitle:"AssetsManagerTest",
        testScene:function () {
            var testScene = new AssetsManagerLoaderScene();
            if (testScene) {
                testScene.runThisTest();
            }
        }
    });
}

var ExtensionsMainLayer = cc.Layer.extend({
    onEnter:function () {
        this._super();

        var winSize = cc.director.getWinSize();

        var pMenu = new cc.Menu();
        pMenu.x = 0;
        pMenu.y = 0;
        cc.MenuItemFont.setFontName("Arial");
        cc.MenuItemFont.setFontSize(24);
        for (var i = 0; i < extensionsTestItemNames.length; ++i) {
            var selItem = extensionsTestItemNames[i];
            var pItem = new cc.MenuItemFont(selItem.itemTitle, this.menuCallback, this);
            pItem.x = winSize.width / 2;
            pItem.y = winSize.height - (i + 1) * LINE_SPACE;
            pMenu.addChild(pItem, ITEM_TAG_BASIC + i);
        }
        this.addChild(pMenu);
    },

    menuCallback:function (sender) {
        var nIndex = sender.zIndex - ITEM_TAG_BASIC;
        extensionsTestItemNames[nIndex].testScene();
    }
});

var ExtensionsTestScene = TestScene.extend({
    runThisTest:function () {
        var pLayer = new ExtensionsMainLayer();
        this.addChild(pLayer);
	    cc.director.runScene(this);
    }
});
