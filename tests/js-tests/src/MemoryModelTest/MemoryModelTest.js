/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

var memoryModelTestSceneIdx = -1;

//------------------------------------------------------------------
//
// MemoryModelTestBase
//
//------------------------------------------------------------------
var MemoryModelTestBase = BaseTestLayer.extend({
    _title:"",
    _subtitle:"",

    onRestartCallback:function (sender) {
        var s = new MemoryModelTestScene();
        s.addChild(restartMemoryModelTest());
        director.runScene(s);
    },
    onNextCallback:function (sender) {
        var s = new MemoryModelTestScene();
        s.addChild(nextMemoryModelTest());
        director.runScene(s);
    },
    onBackCallback:function (sender) {
        var s = new MemoryModelTestScene();
        s.addChild(previousMemoryModelTest());
        director.runScene(s);
    },

    // automation
    numberOfPendingTests:function() {
        return ( (arrayOfMemoryModelTest.length-1) - memoryModelTestSceneIdx );
    },

    getTestNumber:function() {
        return memoryModelTestSceneIdx;
    }

});

//------------------------------------------------------------------
//
// Set property on sprite
//
//------------------------------------------------------------------
var SetPropertyMemoryModelTest = MemoryModelTestBase.extend({
    _title:"Set Property Test",
    _subtitle:"See console for possible errors",

    ctor:function () {
        cc.sys.garbageCollect();
        this._super();
        var sprite = new cc.Sprite(s_grossini_dance_atlas, cc.rect(0, 0, 85, 121));
        var tag = 10;
        this.addChild(sprite, 0, tag);
        var x = winSize.width / 2;
        var y = winSize.height / 2;
        sprite.setPosition(x, y);

        // add random property
        sprite.randomProperty = "hello world";

        sprite = this.getChildByTag(tag);
        
        // should print "hello world"
        this.log(sprite.randomProperty);
    },
});

//------------------------------------------------------------------
//
// Using Ivar 1: from ctor to onEnter
//
//------------------------------------------------------------------
var Ivar1MemoryModelTest = MemoryModelTestBase.extend({
    _title:"Using ivars to hold C++ objects",
    _subtitle:"From ctor to onEnter",

    ctor:function () {
        this._super();
        this.sprite = new cc.Sprite(s_grossini_dance_atlas, cc.rect(0, 0, 85, 121));
    },
    onEnter:function() {
        this._super();
        this.addChild(this.sprite);
        var x = winSize.width / 2;
        var y = winSize.height / 2;
        this.sprite.setPosition(x, y);
    },
});

//------------------------------------------------------------------
//
// Using Ivar 2: from ctor to update 
//
//------------------------------------------------------------------
var Ivar2MemoryModelTest = MemoryModelTestBase.extend({
    _title:"Using ivars to hold C++ objects",
    _subtitle:"From ctor to update",

    ctor:function () {
        this._super();
        this.sprite = new cc.Sprite(s_grossini_dance_atlas, cc.rect(0, 0, 85, 121));
        this.scheduleOnce(this.showSprite, 0.5);
    },
    showSprite:function() {
        this.addChild(this.sprite);
        var x = winSize.width / 2;
        var y = winSize.height / 2;
        this.sprite.setPosition(x, y);
    },
});

var MemoryModelTestScene = TestScene.extend({
    runThisTest:function (num) {
        memoryModelTestSceneIdx = (num || num == 0) ? (num - 1) : -1;
        var layer = nextMemoryModelTest();
        this.addChild(layer);

        director.runScene(this);
    }
});

//------------------------------------------------------------------
//
// Using Local vars
//
//------------------------------------------------------------------
var LocalVarMemoryModelTest = MemoryModelTestBase.extend({
    _title:"Using local vars + GC",
    _subtitle:"native objects should get destroyed",

    ctor:function () {
        this._super();
        var sprite1 = new cc.Sprite(s_grossini_dance_atlas, cc.rect(0, 0, 85, 121));
        var sprite2 = new cc.Sprite(s_grossini_dance_atlas, cc.rect(0, 0, 85, 121));
        var sprite3 = new cc.Sprite(s_grossini_dance_atlas, cc.rect(0, 0, 85, 121));
        var a = 10;
        this.addChild(sprite1);
        this.removeChild(sprite1);
//        this.addChild(sprite2);
//        this.removeChild(sprite2);
        this.addChild(sprite3);
        this.removeChild(sprite3);
        //cc.sys.dumpRoot();
        cc.sys.garbageCollect();
        cc.log(sprite1);
        cc.log(sprite2);
        cc.log(sprite3);
        cc.log(a);
    },
});

//------------------------------------------------------------------
//
// Using Local vars
//
//------------------------------------------------------------------
var RetainRootsMemoryModelTest = MemoryModelTestBase.extend({
    _title:"retain must root",
    _subtitle:"native objects should not get destroyed",

    ctor:function () {
        this._super();
        var sprite = new cc.Sprite(s_grossini_dance_atlas, cc.rect(0, 0, 85, 121));
        // addChild should root the sprite
        this.addChild(sprite);
        cc.sys.garbageCollect();

        var x = winSize.width / 2;
        var y = winSize.height / 2;
        sprite.setPosition(x, y);
    },
});

//------------------------------------------------------------------
//
// Testing Root/Unroot
//
//------------------------------------------------------------------
var RootUnrootMemoryModelTest = MemoryModelTestBase.extend({
    _title:"root/unroot",
    _subtitle:"rooting/unrooting with GC memory model",

    ctor:function () {
        this._super();
        var sprite = new cc.Sprite(s_grossini_dance_atlas, cc.rect(0, 0, 85, 121));
        // addChild should root the sprite
        this.addChild(sprite);

        // should unroot the sprite
        this.removeChild(sprite)
        cc.sys.garbageCollect();
    },
});


//
// Entry point
//
var MemoryModelTestScene = TestScene.extend({
    runThisTest:function (num) {
        memoryModelTestSceneIdx = (num || num == 0) ? (num - 1) : -1;
        var layer = nextMemoryModelTest();
        this.addChild(layer);

        director.runScene(this);
    }
});


//
// Flow control
//

var arrayOfMemoryModelTest = [
    SetPropertyMemoryModelTest,
    Ivar1MemoryModelTest,
    Ivar2MemoryModelTest,
    LocalVarMemoryModelTest,
    RetainRootsMemoryModelTest,
    RootUnrootMemoryModelTest,
];

var nextMemoryModelTest = function () {
    memoryModelTestSceneIdx++;
    memoryModelTestSceneIdx = memoryModelTestSceneIdx % arrayOfMemoryModelTest.length;

    return new arrayOfMemoryModelTest[memoryModelTestSceneIdx]();
};
var previousMemoryModelTest = function () {
    memoryModelTestSceneIdx--;
    if (memoryModelTestSceneIdx < 0)
        memoryModelTestSceneIdx += arrayOfMemoryModelTest.length;

    return new arrayOfMemoryModelTest[memoryModelTestSceneIdx]();
};
var restartMemoryModelTest = function () {
    return new arrayOfMemoryModelTest[memoryModelTestSceneIdx]();
};

