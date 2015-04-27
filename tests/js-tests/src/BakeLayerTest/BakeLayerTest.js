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

var _bakeLayerTestIdx = -1;

//------------------------------------------------------------------
//
// ActionManagerTest
//
//------------------------------------------------------------------
var BakeLayerBaseTest = BaseTestLayer.extend({
    _atlas:null,
    _title:"",

    title:function () {
        return "No title";
    },

    subtitle:function () {
        return "";
    },

    onBackCallback:function (sender) {
        var s = new BakeLayerTestScene();
        s.addChild(previousBakeLayerTest());
        director.runScene(s);
    },
    onRestartCallback:function (sender) {
        var s = new BakeLayerTestScene();
        s.addChild(restartBakeLayerTest());
        director.runScene(s);
    },
    onNextCallback:function (sender) {
        var s = new BakeLayerTestScene();
        s.addChild(nextBakeLayerTest());
        director.runScene(s);
    },
    // automation
    numberOfPendingTests:function() {
        return ( (arrayOfBakeLayerTest.length-1) - _bakeLayerTestIdx );
    },

    getTestNumber:function() {
        return _bakeLayerTestIdx;
    }
});

var BakeLayerTest1 = BakeLayerBaseTest.extend({
    _bakeLayer: null,

    title:function () {
        return "Test 1. Bake Layer (Canvas only)";
    },

    ctor: function(){
        this._super();

        var winSize = cc.winSize;
        var bakeItem = new cc.MenuItemFont("bake", this.onBake, this);
        var unbakeItem = new cc.MenuItemFont("unbake", this.onUnbake, this);
        var runActionItem = new cc.MenuItemFont("run action", this.onRunAction, this);
        var menu = new cc.Menu(bakeItem, unbakeItem, runActionItem);

        menu.alignItemsVertically();
        menu.x = winSize.width - 70;
        menu.y = winSize.height - 120;
        this.addChild(menu, 10);

        var rootLayer = new cc.Layer();
        rootLayer.setPosition(20,20);
        this.addChild(rootLayer);

        var bakeLayer = new cc.Layer();
        bakeLayer.bake();
        bakeLayer.setRotation(30);
        rootLayer.addChild(bakeLayer);

        for(var i = 0; i < 9; i++){
            var sprite1 = new cc.Sprite(s_pathGrossini);
            if (i % 2 === 0) {
                sprite1.setPosition(90 + i * 80, winSize.height / 2 - 50);
            } else {
                sprite1.setPosition(90 + i * 80, winSize.height / 2 + 50);
            }
            if(i === 4)
                this._actionSprite = sprite1;
            sprite1.rotation = 360 * Math.random();
            bakeLayer.addChild(sprite1);
        }
        this._bakeLayer = bakeLayer;
        bakeLayer.runAction(cc.sequence(cc.moveBy(2, cc.p(100,100)), cc.moveBy(2, cc.p(-100,-100))));
    },

    onBake: function(){
        this._bakeLayer.bake();
    },

    onUnbake: function(){
        this._bakeLayer.unbake();
    },

    onRunAction: function(){
        this._actionSprite.runAction(cc.rotateBy(1, 180));
    }
});

var BakeLayerColorTest = BakeLayerBaseTest.extend({
    _bakeLayer: null,
    _actionSprite: null,

    title:function () {
        return "Test 2. Bake Layer Gradient (Canvas only)";
    },

    ctor: function(){
        this._super();

        var winSize = cc.winSize;
        var bakeItem = new cc.MenuItemFont("bake", this.onBake, this);
        var unbakeItem = new cc.MenuItemFont("unbake", this.onUnbake, this);
        var runActionItem = new cc.MenuItemFont("run action", this.onRunAction, this);
        var menu = new cc.Menu(bakeItem, unbakeItem, runActionItem);

        menu.alignItemsVertically();
        menu.x = winSize.width - 70;
        menu.y = winSize.height - 120;
        this.addChild(menu, 10);

        var rootLayer = new cc.Layer();
        rootLayer.setPosition(20,20);
        this.addChild(rootLayer);

        //var bakeLayer = cc.LayerColor.create(cc.color(128,0, 128, 128), 700, 300);     //test for LayerColor
        //bakeLayer.setPosition(60, 80);

        var bakeLayer = new cc.LayerGradient(cc.color(128,0, 128, 255), cc.color(0, 0, 128, 255));
        bakeLayer.setPosition(60, 80);
        bakeLayer.setContentSize(700, 300);
        bakeLayer.setRotation(30);

        //bakeLayer.setPosition(winSize.width /2, winSize.height /2);         //test for ignoreAnchorPointForPosition
        //bakeLayer.ignoreAnchorPointForPosition(false);
        rootLayer.addChild(bakeLayer);

        for(var i = 0; i < 9; i++){
            var sprite1 = new cc.Sprite(s_pathGrossini);
            if (i % 2 === 0) {
                sprite1.setPosition(20 + i * 80, 100);
            } else {
                sprite1.setPosition(20 + i * 80, 200);
            }
            if(i === 4)
                this._actionSprite = sprite1;
            sprite1.rotation = 180 * Math.random();
            bakeLayer.addChild(sprite1);
        }

        this._bakeLayer = bakeLayer;
        bakeLayer.bake();
        bakeLayer.runAction(cc.sequence(cc.moveBy(2, cc.p(100,100)), cc.moveBy(2, cc.p(-100,-100))));
    },

    onBake: function(){
        this._bakeLayer.bake();
    },

    onUnbake: function(){
        this._bakeLayer.unbake();
    },

    onRunAction: function(){
        this._actionSprite.runAction(cc.rotateBy(2, 180));
    }
});

var BakeLayerTestScene = TestScene.extend({
    runThisTest:function (num) {
        _bakeLayerTestIdx = (num || 0) - 1;
        this.addChild(nextBakeLayerTest());
        director.runScene(this);
    }
});

//-
//
// Flow control
//
var arrayOfBakeLayerTest = [
    BakeLayerTest1,
    BakeLayerColorTest
];

var nextBakeLayerTest = function (num) {
    _bakeLayerTestIdx = num ? num - 1 : _bakeLayerTestIdx;
    _bakeLayerTestIdx++;
    _bakeLayerTestIdx = _bakeLayerTestIdx % arrayOfBakeLayerTest.length;

    if(window.sideIndexBar){
        _bakeLayerTestIdx = window.sideIndexBar.changeTest(_bakeLayerTestIdx, 0);
    }
    return new arrayOfBakeLayerTest[_bakeLayerTestIdx]();
};

var previousBakeLayerTest = function () {
    _bakeLayerTestIdx--;
    if (_bakeLayerTestIdx < 0)
        _bakeLayerTestIdx += arrayOfBakeLayerTest.length;

    if(window.sideIndexBar){
        _bakeLayerTestIdx = window.sideIndexBar.changeTest(_bakeLayerTestIdx, 0);
    }
    return new arrayOfBakeLayerTest[_bakeLayerTestIdx]();
};
var restartBakeLayerTest = function () {
    return new arrayOfBakeLayerTest[_bakeLayerTestIdx]();
};