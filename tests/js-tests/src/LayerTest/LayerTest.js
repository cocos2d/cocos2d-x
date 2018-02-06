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
cc.TAG_LAYER = 1;

var layerTestSceneIdx = -1;
var LAYERTEST2_LAYER1_TAG = 1;
var LAYERTEST2_LAYER2_TAG = 2;

var LayerTestScene = TestScene.extend({
    runThisTest:function (num) {
        layerTestSceneIdx = (num || num == 0) ? (num - 1) : -1;
        this.addChild(nextLayerTest());
        director.runScene(this);
    }
});

//------------------------------------------------------------------
//
// LayerTest
//
//------------------------------------------------------------------
var LayerTest = BaseTestLayer.extend({
    _title:null,


    title:function () {
        return "No title";
    },
    subtitle:function () {
        return "";
    },

    onRestartCallback:function (sender) {
        var s = new LayerTestScene();
        s.addChild(restartLayerTest());
        director.runScene(s);

    },
    onNextCallback:function (sender) {
        var s = new LayerTestScene();
        s.addChild(nextLayerTest());
        director.runScene(s);

    },
    onBackCallback:function (sender) {
        var s = new LayerTestScene();
        s.addChild(previousLayerTest());
        director.runScene(s);

    },
    // automation
    numberOfPendingTests:function() {
        return ( (arrayOfLayerTest.length-1) - layerTestSceneIdx );
    },

    getTestNumber:function() {
        return layerTestSceneIdx;
    }

});

//------------------------------------------------------------------
//
// LayerTest1
//
//------------------------------------------------------------------
var LayerTest1 = LayerTest.extend({
    onEnter:function () {
        //----start0----onEnter
        this._super();

        if( 'touches' in cc.sys.capabilities )
            cc.eventManager.addListener({
                event: cc.EventListener.TOUCH_ALL_AT_ONCE,
                onTouchesMoved:function (touches, event) {
                    event.getCurrentTarget().updateSize(touches[0].getLocation());
                }
            }, this);
        else if ('mouse' in cc.sys.capabilities )
            cc.eventManager.addListener({
                event: cc.EventListener.MOUSE,
                onMouseMove: function(event){
                    if(event.getButton() == cc.EventMouse.BUTTON_LEFT)
                        event.getCurrentTarget().updateSize(event.getLocation());
                }
            }, this);

        var s = director.getWinSize();
        var layer = new cc.LayerColor(cc.color(255, 0, 0, 128));

        layer.ignoreAnchor = false;
        layer.anchorX = 0.5;
        layer.anchorY = 0.5;
        layer.setContentSize(200, 200);
        layer.x = s.width / 2;
        layer.y = s.height / 2;
        this.addChild(layer, 1, cc.TAG_LAYER);
        //----end0----
    },
    title:function () {
        return "ColorLayer resize (tap & move)";
    },

    updateSize:function (location) {
        //----start0----updateSize
        var l = this.getChildByTag(cc.TAG_LAYER);

        l.width = Math.abs(location.x - winSize.width / 2) * 2;
	    l.height = Math.abs(location.y - winSize.height / 2) * 2;
        //----end0----
    },

    //
    // Automation
    //
    pixel: {"0": 190, "1": 0, "2": 0, "3": 128},

    getExpectedResult:function() {

        var s = director.getWinSize();
        var ret = {"center": "yes"};
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {

        var s = director.getWinSize();
        var ret2 =  this.readPixels(s.width/2, s.height/2, 5, 5);
        var ret = {"center": this.containsPixel(ret2, this.pixel, true, 100) ? "yes" : "no"};

        return JSON.stringify(ret);
    }
});

var IgnoreAnchorpointTest1 = LayerTest.extend({
    onEnter:function () {
        //----start3----onEnter
        this._super();
        //create layer
        var ws = director.getWinSize();
        var layer1 = new cc.LayerColor(cc.color(255, 100, 100, 128), ws.width / 2, ws.height / 2);
        layer1.ignoreAnchorPointForPosition(true);
        var layer2 = new cc.LayerColor(cc.color(100, 255, 100, 128), ws.width / 4, ws.height / 4);
        layer2.ignoreAnchorPointForPosition(true);
        layer1.addChild(layer2);
        layer1.x = ws.width / 2;
        layer1.y = ws.height / 2;
        this.addChild(layer1);
        //----end3----
    },
    title:function () {
        return "ignore Anchorpoint Test #1";
    },
    subtitle:function () {
        return "red:true  green:true";
	},


    //
    // Automation
    //

    pixel1: {"0": 100, "1": 150, "2": 100, "3": 200},
    pixel2: {"0": 100, "1": 50, "2": 50, "3": 200},

    getExpectedResult:function() {
        
        var s = director.getWinSize();
        var ret = {"big": "yes", "small": "yes"};
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {

        var s = director.getWinSize();
        var ret2 =  this.readPixels(s.width/2 + s.width/5, s.height/2 + s.height/5, 5, 5);
        var ret3 =  this.readPixels(s.width - 50, s.height - 50, 50, 50);
        var ret = {"big": this.containsPixel(ret2, this.pixel1, true, 100) ? "yes" : "no",
		   "small": this.containsPixel(ret3, this.pixel2, true, 100) ? "yes" : "no"};
	
        return JSON.stringify(ret);
    }
});
var IgnoreAnchorpointTest2 = LayerTest.extend({
    onEnter:function () {
        //----start4----onEnter
        this._super();
        //create layer
        var ws = director.getWinSize();
        var layer1 = new cc.LayerColor(cc.color(255, 100, 100, 128), ws.width / 2, ws.height / 2);
        layer1.ignoreAnchorPointForPosition(true);
        var layer2 = new cc.LayerColor(cc.color(100, 255, 100, 128), ws.width / 4, ws.height / 4);
        layer2.ignoreAnchorPointForPosition(false);
        layer1.addChild(layer2);
        layer1.x = ws.width / 2;
        layer1.y = ws.height / 2;
        this.addChild(layer1);
        //----end4----
    },
    title:function () {
        return "ignore Anchorpoint Test #2";
    },
    subtitle:function () {
        return "red:true  green:false";
    },


    //
    // Automation
    //

    pixel1: {"0": 50, "1": 100, "2": 50, "3": 200},
    pixel2: {"0": 100, "1": 50, "2": 50, "3": 200},

    getExpectedResult:function() {
        
        var s = director.getWinSize();
        var ret = {"big": "yes", "small": "yes"};
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {

        var s = director.getWinSize();
        var ret2 =  this.readPixels(s.width/2 - 50, s.height/2 - 50, 5, 5);
        var ret3 =  this.readPixels(s.width - 50, s.height - 50, 5, 5);
        var ret = {"big": this.containsPixel(ret2, this.pixel1, true, 100) ? "yes" : "no",
		   "small": this.containsPixel(ret3, this.pixel2, true, 100) ? "yes" : "no"};
	
        return JSON.stringify(ret);
    }
});

var IgnoreAnchorpointTest3 = LayerTest.extend({
    onEnter:function () {
        //----start5----onEnter
        this._super();
        //create layer
        var ws = director.getWinSize();
        var layer1 = new cc.LayerColor(cc.color(255, 100, 100, 128), ws.width / 2, ws.height / 2);
        layer1.ignoreAnchorPointForPosition(false);
        var layer2 = new cc.LayerColor(cc.color(100, 255, 100, 128), ws.width / 4, ws.height / 4);
        layer2.ignoreAnchorPointForPosition(false);
        layer1.addChild(layer2);
        layer1.x = ws.width / 2;
        layer1.y = ws.height / 2;
        this.addChild(layer1);
        //----end5----
    },
    title:function () {
        return "ignore Anchorpoint Test #3";
    },
    subtitle:function () {
        return "red:false  green:false";
    }
});

var IgnoreAnchorpointTest4 = LayerTest.extend({
    onEnter:function () {
        //----start6----onEnter
        this._super();
        //create layer
        var ws = director.getWinSize();
        var layer1 = new cc.LayerColor(cc.color(255, 100, 100, 128), ws.width / 2, ws.height / 2);
        layer1.ignoreAnchorPointForPosition(false);
        var layer2 = new cc.LayerColor(cc.color(100, 255, 100, 128), ws.width / 4, ws.height / 4);
        layer2.ignoreAnchorPointForPosition(true);
        layer1.addChild(layer2);
        layer1.x = ws.width / 2;
        layer1.y = ws.height / 2;
        this.addChild(layer1);
        //----end6----
    },
    title:function () {
        return "ignore Anchorpoint Test #4";
    },
    subtitle:function () {
        return "red:false  green:true";
    }

});

//------------------------------------------------------------------
//
// LayerTest2
//
//------------------------------------------------------------------
var LayerTest2 = LayerTest.extend({

    onEnter:function () {
        //----start1----onEnter
        this._super();

        var s = director.getWinSize();
        var layer1 = new cc.LayerColor(cc.color(255, 255, 0, 80), 100, 300);
        layer1.x = s.width / 3;
        layer1.y = s.height / 2;
        layer1.ignoreAnchorPointForPosition(false);
        this.addChild(layer1, 1, LAYERTEST2_LAYER1_TAG);

        var layer2 = new cc.LayerColor(cc.color(0, 0, 255, 255), 100, 300);
        layer2.x = (s.width / 3) * 2;
        layer2.y = s.height / 2;
        layer2.ignoreAnchorPointForPosition(false);
        this.addChild(layer2, 2, LAYERTEST2_LAYER2_TAG);

        var actionTint = cc.tintBy(2, -255, -127, 0);
        var actionTintBack = actionTint.reverse();

        var actionFade = cc.fadeOut(2.0);
        var actionFadeBack = actionFade.reverse();

        if (autoTestEnabled) {
            var seq1 = cc.sequence(actionTint, cc.delayTime(0.25), actionTintBack);
            var seq2 = cc.sequence(actionFade, cc.delayTime(0.25), actionFadeBack);
        } else {
            var seq1 = cc.sequence(actionTint, actionTintBack);
            var seq2 = cc.sequence(actionFade, actionFadeBack);
        }

        layer1.runAction(seq1);
        layer2.runAction(seq2);
        //----end1----
    },
    title:function () {
        return "ColorLayer: fade and tint";
    },

    //
    // Automation
    //

    testDuration: 2.1,
    tintTest: {"r": 0, "g": 128, "b": 60},
    getExpectedResult:function() {
        var ret = {"tint": "yes", "opacity": 0};
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var abs = function (a) {
            return (a > 0) ? a : a * -1;
        };

        var inColorRange = function (pix1, pix2) {
            // Color on iOS comes as 0,128,128 and on web as 0,128,0
            if (abs(pix1.r - pix2.r) < 50 && abs(pix1.g - pix2.g) < 50 &&
                abs(pix1.b - pix2.b) < 90) {
                return true;
            }
            return false;
        };
        var s = director.getWinSize();
        var tint = this.getChildByTag(LAYERTEST2_LAYER1_TAG).color;
        var op = this.getChildByTag(LAYERTEST2_LAYER2_TAG).opacity;
        var ret = {"tint": inColorRange(tint, this.tintTest) ? "yes" : "no",
            "opacity": op};

        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// LayerTestBlend
//
//------------------------------------------------------------------
var LayerTestBlend = LayerTest.extend({
    _blend:true,

    ctor:function () {
        //----start2----ctor
        this._super();
        var layer1 = new cc.LayerColor(cc.color(255, 255, 255, 80));

        var sister1 = new cc.Sprite(s_pathSister1);
        var sister2 = new cc.Sprite(s_pathSister2);

        this.addChild(sister1);
        this.addChild(sister2);
        this.addChild(layer1, 100, cc.TAG_LAYER);

        sister1.x = winSize.width/3;

        sister1.y = winSize.height / 2;
        sister2.x = winSize.width/3 * 2;
        sister2.y = winSize.height / 2;

        if (!cc.sys.isNative && !("opengl" in cc.sys.capabilities)) {
            var label = new cc.LabelTTF("Not supported on HTML5-canvas", "Times New Roman", 30);
            this.addChild(label);
            label.x = winSize.width / 2;
            label.y = winSize.height / 2;
        }

        this.schedule(this.onNewBlend, 1.0);
        this._blend = true;
        //----end2----
    },
    onNewBlend:function (dt) {
        //----start2----onNewBlend
        var layer = this.getChildByTag(cc.TAG_LAYER);

        var src;
        var dst;

        if (this._blend) {
            src = cc.SRC_ALPHA;
            dst = cc.ONE_MINUS_SRC_ALPHA;
        } else {
            src = cc.ONE_MINUS_DST_COLOR;
            dst = cc.ZERO;
        }
        layer.setBlendFunc( src, dst );
        this._blend = ! this._blend;
        //----end2----
    },
    title:function () {
        return "ColorLayer: blend";
    }
});

//------------------------------------------------------------------
//
// LayerGradient
//
//------------------------------------------------------------------
var LayerGradient = LayerTest.extend({
    _isPressed:false,
    ctor:function () {
        //----start7----onEnter
        this._super();
        var layer1 = new cc.LayerGradient(cc.color(255, 0, 0, 255), cc.color(0, 255, 0, 255), cc.p(0.9, 0.9));
        this.addChild(layer1, 0, cc.TAG_LAYER);

        if( 'touches' in cc.sys.capabilities ){
            cc.eventManager.addListener({
                event: cc.EventListener.TOUCH_ALL_AT_ONCE,
                onTouchesBegan:function(touches, event){
                    event.getCurrentTarget().updateGradient(touches[0].getLocation());
                },
                onTouchesMoved:function (touches, event) {
                    event.getCurrentTarget().updateGradient(touches[0].getLocation());
                }
            }, this);
        } else if ('mouse' in cc.sys.capabilities ){
            cc.eventManager.addListener({
                event: cc.EventListener.MOUSE,
                onMouseDown: function(event){
                    event.getCurrentTarget().updateGradient(event.getLocation());
                },
                onMouseMove: function(event){
                    if(event.getButton() == cc.EventMouse.BUTTON_LEFT)
                        event.getCurrentTarget().updateGradient(event.getLocation());
                }
            }, this);
        }

        var label1 = new cc.LabelTTF("Compressed Interpolation: Enabled", "Marker Felt", 26);
        var label2 = new cc.LabelTTF("Compressed Interpolation: Disabled", "Marker Felt", 26);
        var item1 = new cc.MenuItemLabel(label1);
        var item2 = new cc.MenuItemLabel(label2);
        var item = new cc.MenuItemToggle(item1, item2, this.onToggleItem, this);

         var menu = new cc.Menu(item);
         this.addChild(menu);
         menu.x = winSize.width / 2;
         menu.y = 100;
        //----end7----
    },

    updateGradient:function(pos) {
        //----start7----updateGradient
        var diff = cc.pSub(cc.p(winSize.width / 2, winSize.height / 2), pos);
        diff = cc.pNormalize(diff);

        var gradient = this.getChildByTag(1);
        gradient.setVector(diff);
        //----end7----
    },

    onToggleItem:function (sender) {
        //----start7----onToggleItem
        var gradient = this.getChildByTag(cc.TAG_LAYER);
        gradient.setCompressedInterpolation(!gradient.isCompressedInterpolation());
        //----end7----
    },

    title:function () {
        return "LayerGradient";
    },
    subtitle:function () {
        return "Touch the screen and move your finger";
    },

    //
    // Automation
    //

    pixel1: {"0": 255, "1": 0, "2": 0, "3": 255},
    pixel2: {"0": 0, "1": 255, "2": 0, "3": 255},

    getExpectedResult:function() {
        
        var s = director.getWinSize();
        var ret = {"bottomleft": "yes", "topright": "yes"};
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {

        var s = director.getWinSize();
        var ret2 =  this.readPixels(50, 50, 50, 50);
        var ret3 =  this.readPixels(s.width - 50, s.height - 50, 50, 50);
        var ret = {"bottomleft": this.containsPixel(ret2, this.pixel1) ? "yes" : "no",
		   "topright": this.containsPixel(ret3, this.pixel2) ? "yes" : "no"};
	
        return JSON.stringify(ret);
    }
});

var arrayOfLayerTest = [
    LayerTest1,
    LayerTest2,
    LayerGradient,
    LayerTestBlend,
    IgnoreAnchorpointTest1,
    IgnoreAnchorpointTest2,
    IgnoreAnchorpointTest3,
    IgnoreAnchorpointTest4
];

var nextLayerTest = function () {
    layerTestSceneIdx++;
    layerTestSceneIdx = layerTestSceneIdx % arrayOfLayerTest.length;

    if(window.sideIndexBar){
        layerTestSceneIdx = window.sideIndexBar.changeTest(layerTestSceneIdx, 20);
    }

    return new arrayOfLayerTest[layerTestSceneIdx]();
};
var previousLayerTest = function () {
    layerTestSceneIdx--;
    if (layerTestSceneIdx < 0)
        layerTestSceneIdx += arrayOfLayerTest.length;

    if(window.sideIndexBar){
        layerTestSceneIdx = window.sideIndexBar.changeTest(layerTestSceneIdx, 20);
    }

    return new arrayOfLayerTest[layerTestSceneIdx]();
};
var restartLayerTest = function () {
    return new arrayOfLayerTest[layerTestSceneIdx]();
};
