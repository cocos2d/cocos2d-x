/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.


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

var sysTestSceneIdx = -1;
//------------------------------------------------------------------
//
// SysTestBase
//
//------------------------------------------------------------------
var SysTestBase = BaseTestLayer.extend({
    _title:"",
    _subtitle:"",

    ctor:function() {
        this._super(cc.color(0,0,0,0), cc.color(98,99,117,0));
    },
    onRestartCallback:function (sender) {
        var s = new SysTestScene();
        s.addChild(restartSysTest());
        director.runScene(s);
    },
    onNextCallback:function (sender) {
        var s = new SysTestScene();
        s.addChild(nextSysTest());
        director.runScene(s);
    },
    onBackCallback:function (sender) {
        var s = new SysTestScene();
        s.addChild(previousSysTest());
        director.runScene(s);
    },
    // automation
    numberOfPendingTests:function() {
        return ( (arrayOfSysTest.length-1) - sysTestSceneIdx );
    },

    getTestNumber:function() {
        return sysTestSceneIdx;
    }

});

//------------------------------------------------------------------
//
// setClearColorTest
//
//------------------------------------------------------------------
var setClearColorTest = SysTestBase.extend({
    _title:"Set clearColor to red with alpha = 0 ",
    ctor:function()
    {
        this._super();
        var bg = new cc.Sprite(s_back,cc.rect(0,0, 200, 200));
        bg.x = winSize.width/2;
        bg.y = winSize.height/2;
        this.addChild(bg);
        return true;
    },
    onEnter:function()
    {
        this._super();
        var clearColor = cc.color(255, 0, 0, 0);
        director.setClearColor(clearColor);
    },
    onExit:function()
    {
        director.setClearColor(cc.color(0, 0, 0, 255));
        this._super();
    }
});

//------------------------------------------------------------------
//
// LocalStorageTest
//
//------------------------------------------------------------------
var LocalStorageTest = SysTestBase.extend({
    _title:"LocalStorage Test ",
    _subtitle:"See the console",

    ctor:function () {
        this._super();

        var key = 'key_' + Math.random();
        var ls = cc.sys.localStorage;
        cc.log("- Adding items");
        ls.setItem(key, "Hello world");
        var key1 = "1" + key;
        ls.setItem(key1, "Hello JavaScript");
        var key2 = "2" + key;
        ls.setItem(key2, "Hello Cocos2d-JS");
        var key3 = "3" + key;
        ls.setItem(key3, "Hello Cocos");

        cc.log("- Getting Hello world");
        var r = ls.getItem(key);
        cc.log(r);

        cc.log("- Removing Hello world");
        ls.removeItem(key);

        cc.log("- Getting Hello world");
        r = ls.getItem(key);
        cc.log(r);

        cc.log("- Getting other items");
        cc.log( ls.getItem(key1) );
        cc.log( ls.getItem(key2) );
        cc.log( ls.getItem(key3) );

        cc.log("- Clearing local storage");
        ls.clear();
        cc.log("- Getting other items");
        cc.log( ls.getItem(key1) );
        cc.log( ls.getItem(key2) );
        cc.log( ls.getItem(key3) );
    }

});

//------------------------------------------------------------------
//
// CapabilitiesTest
//
//------------------------------------------------------------------
var CapabilitiesTest = SysTestBase.extend({
    _title:"Capabilities Test ",
    _subtitle:"See the console",

    ctor:function () {
        this._super();

        var c = cc.sys.capabilities;
        for( var i in c )
            cc.log( i + " = " + c[i] );
    }

});

var SysTestScene = TestScene.extend({
    runThisTest:function (num) {
        sysTestSceneIdx = (num || num == 0) ? (num - 1) : -1;
        var layer = nextSysTest();
        this.addChild(layer);
        director.runScene(this);
    }
});

//------------------------------------------------------------------
//
// Script dynamic reload test
//
//------------------------------------------------------------------
var tempJSFileName = "ScriptTestTempFile.js";
var ScriptTestLayer = SysTestBase.extend({
    _tempLayer:null,
    _am : null,
    startDownload:function () {
        if (!cc.sys.isNative)
        {
            return;
        }
        var that = this;
        var manifestPath = "Manifests/ScriptTest/project.manifest";
        var storagePath = ((jsb.fileUtils ? jsb.fileUtils.getWritablePath() : "/") + "JSBTests/AssetsManagerTest/ScriptTest/");
        cc.log("Storage path for this test : " + storagePath);

        if (this._am){
            this._am.release();
            this._am = null;
        }

        this._am = new jsb.AssetsManager(manifestPath, storagePath);
        this._am.retain();
        if (!this._am.getLocalManifest().isLoaded()){
            cc.log("Fail to update assets, step skipped.");
            that.clickMeShowTempLayer();
        }else {
            var listener = new jsb.EventListenerAssetsManager(this._am, function (event) {
                var scene;
                switch (event.getEventCode()) {
                    case jsb.EventAssetsManager.ERROR_NO_LOCAL_MANIFEST:
                        cc.log("No local manifest file found, skip assets update.");
                        that.clickMeShowTempLayer();
                        break;
                    case jsb.EventAssetsManager.UPDATE_PROGRESSION:
                        cc.log(event.getPercent() + "%");
                        break;
                    case jsb.EventAssetsManager.ERROR_DOWNLOAD_MANIFEST:
                    case jsb.EventAssetsManager.ERROR_PARSE_MANIFEST:
                        cc.log("Fail to download manifest file, update skipped.");
                        that.clickMeShowTempLayer();
                        break;
                    case jsb.EventAssetsManager.ALREADY_UP_TO_DATE:
                    case jsb.EventAssetsManager.UPDATE_FINISHED:
                        cc.log("Update finished. " + event.getMessage());
                        require(tempJSFileName);
                        that.clickMeShowTempLayer();
                        break;
                    case jsb.EventAssetsManager.UPDATE_FAILED:
                        cc.log("Update failed. " + event.getMessage());
                        break;
                    case jsb.EventAssetsManager.ERROR_UPDATING:
                        cc.log("Asset update error: " + event.getAssetId() + ", " + event.getMessage());
                        break;
                    case jsb.EventAssetsManager.ERROR_DECOMPRESS:
                        cc.log(event.getMessage());
                        break;
                    default:
                        break;
                }
            });
            cc.eventManager.addListener(listener, 1);
            this._am.update();
        }
    },
    clickMeShowTempLayer:function () {
        this.removeChildByTag(233, true);
        this._tempLayer = new ScriptTestTempLayer();
        this.addChild(this._tempLayer, 0, 233);
    },
    clickMeReloadTempLayer:function(){
        cc.sys.cleanScript(tempJSFileName);
        if (!cc.sys.isNative){
            this.clickMeShowTempLayer();
        }else{
            this.startDownload();
        }

    },
    onExit : function () {
        if (this._am)
        {
            this._am.release();
            this._am = null;
        }

        this._super();
    },
    ctor : function () {
        this._super();

        var menu = new cc.Menu();
        menu.setPosition(cc.p(0, 0));
        menu.width = winSize.width;
        menu.height = winSize.height;
        this.addChild(menu, 1);
        var item1 = new cc.MenuItemLabel(new cc.LabelTTF("Click me show tempLayer", "Arial", 22), this.clickMeShowTempLayer, this);
        menu.addChild(item1);

        var item2 = new cc.MenuItemLabel(new cc.LabelTTF("Click me reload tempLayer", "Arial", 22), this.clickMeReloadTempLayer, this);
        menu.addChild(item2);

        menu.alignItemsVerticallyWithPadding(8);
        menu.setPosition(cc.pAdd(cc.visibleRect.left, cc.p(+180, 0)));
    },

    getTitle : function() {
        return "ScriptTest only used in native";
    }

});

//------------------------------------------------------------------
//
// Restart game test
//
//------------------------------------------------------------------
var RestartGameLayerTest = SysTestBase.extend({
    getTitle : function() {
        return "RestartGameTest only used in native";
    },
    restartGame:function()
    {
        cc.game.restart();
    },
    ctor : function () {
        this._super();
        var menu = new cc.Menu();
        menu.setPosition(cc.p(0, 0));
        menu.width = winSize.width;
        menu.height = winSize.height;
        this.addChild(menu, 1);
        var item1 = new cc.MenuItemLabel(new cc.LabelTTF("restartGame", "Arial", 22), this.restartGame, this);
        menu.addChild(item1);
        menu.setPosition(cc.pAdd(cc.visibleRect.left, cc.p(+180, 0)));
    }
});

var OpenURLTest = SysTestBase.extend({
    getTitle:function(){
        return "Open URL Test";
    },

    ctor:function(){
        this._super();
        
        var label = new cc.LabelTTF("Touch the screen to open\nthe cocos2d-x home page", "Arial", 22);
        this.addChild(label);
        label.setPosition(cc.winSize.width/2, cc.winSize.height/2);

        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches: true,
            onTouchBegan: function(){
                return true;
            },
            onTouchEnded: function(){
                cc.sys.openURL("http://www.cocos2d-x.org/");
            }
        }, this);

    }
});

//
// Flow control
//

var arrayOfSysTest = [
    LocalStorageTest,
    CapabilitiesTest,
    OpenURLTest,
    setClearColorTest
];

if (cc.sys.isNative && cc.sys.OS_WINDOWS != cc.sys.os) {
    arrayOfSysTest.push(ScriptTestLayer);
    arrayOfSysTest.push(RestartGameLayerTest);
}

var nextSysTest = function () {
    sysTestSceneIdx++;
    sysTestSceneIdx = sysTestSceneIdx % arrayOfSysTest.length;

    return new arrayOfSysTest[sysTestSceneIdx]();
};
var previousSysTest = function () {
    sysTestSceneIdx--;
    if (sysTestSceneIdx < 0)
        sysTestSceneIdx += arrayOfSysTest.length;

    return new arrayOfSysTest[sysTestSceneIdx]();
};
var restartSysTest = function () {
    return new arrayOfSysTest[sysTestSceneIdx]();
};

