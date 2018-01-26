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

var unitTestSceneIdx = -1;

//------------------------------------------------------------------
//
// UnitTestBase
//
//------------------------------------------------------------------
var UnitTestBase = BaseTestLayer.extend({
    _title:"",
    _subtitle:"",

    onRestartCallback:function (sender) {
        var s = new UnitTestScene();
        s.addChild(restartUnitTest());
        director.runScene(s);
    },
    onNextCallback:function (sender) {
        var s = new UnitTestScene();
        s.addChild(nextUnitTest());
        director.runScene(s);
    },
    onBackCallback:function (sender) {
        var s = new UnitTestScene();
        s.addChild(previousUnitTest());
        director.runScene(s);
    },

    // automation
    numberOfPendingTests:function() {
        return ( (arrayOfUnitTest.length-1) - unitTestSceneIdx );
    },

    getTestNumber:function() {
        return unitTestSceneIdx;
    }

});

//------------------------------------------------------------------
//
// RectUnitTest
//
//------------------------------------------------------------------
var RectUnitTest = UnitTestBase.extend({
    _title:"Rect Unit Test",
    _subtitle:"See console for possible errors",

    onEnter:function () {
        this._super();
        this.runTest();
    },

    runTest:function () {

        var ret = [];
        var rectA;
        var rectB;
        var rectC;
        var point;
        var r;

        this.log("Test 1: rectIntersectsRect 1");
        rectA = cc.rect(0,0,5,10);
        rectB = cc.rect(4,9,5,10);
        r = cc.rectIntersectsRect(rectA, rectB);
        if(!r)
            throw "Fail rectIntersectsRect 1";
        ret.push(r);

        this.log("Test 2: rectIntersectsRect 2");
        rectA = cc.rect(0,0,5,10);
        rectB = cc.rect(40,90,5,10);
        r = cc.rectIntersectsRect(rectA, rectB);
        if(r)
            throw "Fail rectIntersectsRect 2";
        ret.push(r);

        this.log("Test 3: rectIntersection");
        rectA = cc.rect(0,0,5,10);
        rectB = cc.rect(4,9,5,10);
        rectC = cc.rectIntersection(rectA, rectB);
        r = cc.rectEqualToRect(rectC, cc.rect(4,9,1,1) );
        if(!r)
            throw "Fail rectIntersection";
        ret.push(r);

        this.log("Test 4: rectUnion");
        rectA = cc.rect(0,0,5,10);
        rectB = cc.rect(4,9,5,10);
        rectC = cc.rectUnion(rectA, rectB);
        r = cc.rectEqualToRect(rectC, cc.rect(0,0,9,19) );
        if(!r)
            throw "Fail rectUnion";
        ret.push(r);

        this.log("Test 5: rectContainsPoint 1");
        rectA = cc.rect(0,0,5,10);
        point = cc.p(1,1);
        r = cc.rectContainsPoint(rectA, point);
        if(!r)
            throw "Fail rectContainsPoint 1";
        ret.push(r);

        this.log("Test 6: rectContainsPoint 2");
        rectA = cc.rect(0,0,5,10);
        point = cc.p(1,-1);
        r = cc.rectContainsPoint(rectA, point);
        if(r)
            throw "Fail rectContainsPoint 2";
        ret.push(r);

        this.log("Test 7: rect property x");
        rectA = cc.rect(1,2,3,4);
        if( rectA.x != 1)
            throw "Fail rect property x";
        ret.push(rectA.x);

        this.log("Test 8: rect property y");
        rectA = cc.rect(1,2,3,4);
        if( rectA.y != 2)
            throw "Fail rect property y";
        ret.push(rectA.y);

        this.log("Test 9: rect property width");
        rectA = cc.rect(1,2,3,4);
        if( rectA.width != 3)
            throw "Fail rect property width";
        ret.push(rectA.width);

        this.log("Test 10: rect property height");
        rectA = cc.rect(1,2,3,4);
        if( rectA.height != 4)
            throw "Fail rect property height";
        ret.push(rectA.height);

        this.log("Test 11: getBoundingBox()");
        var node = new cc.Node();
        node.width = 99;
	    node.height = 101;
        var bb = node.getBoundingBox();
        if( bb.height != 101 || bb.width != 99)
            throw "Fail getBoundingBox()";
        ret.push( bb.height );
        ret.push( bb.width );
        return ret;
    },

    //
    // Automation
    //
    testDuration:0.1,

    getExpectedResult:function() {
        var ret = [true,false,true,true,true,false,1,2,3,4,101,99];
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret = this.runTest();
        return JSON.stringify(ret);
    }

});

//------------------------------------------------------------------
//
// DictionaryToFromTest
//
//------------------------------------------------------------------
var DictionaryToFromTest = UnitTestBase.extend({
    _title:"Dictionary To/From Test",
    _subtitle:"Sends and receives a dictionary to JSB",

    ctor:function() {
        this._super();

        this.runTest();
    },

    runTest:function() {
        var frameCache = cc.spriteFrameCache;
        frameCache.addSpriteFrames(s_grossiniPlist);

        // Purge previously loaded animation
        var animCache = cc.animationCache;
        animCache.addAnimations(s_animations2Plist);

        var normal = animCache.getAnimation("dance_1");
        var frame = normal.getFrames()[0];
        var dict = frame.getUserInfo();
        this.log( JSON.stringify(dict) );
        frame.setUserInfo( {
                            "array":[1,2,3,"hello world"],
                            "bool0":0,  // false  XXX
                            "bool1":1,  // true   XXX
                            "dict":{"key1":"value1", "key2":2},
                            "number":42,
                            "string":"hello!"
                        });

        dict = frame.getUserInfo();
        this.log(JSON.stringify(dict));
        return dict;
    },

    //
    // Automation
    //
    testDuration:0.1,

    getExpectedResult:function() {
        var ret = this.sortObject( {"array":[1,2,3,"hello world"],"bool0":0,"bool1":1,"dict":{"key1":"value1","key2":2},"number":42,"string":"hello!"} );

        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret = this.sortObject( this.runTest() );
        return JSON.stringify(ret);
    }
});

var UnitTestScene = TestScene.extend({
    runThisTest:function (num) {
        unitTestSceneIdx = (num || num == 0) ? (num - 1) : -1;
        var layer = nextUnitTest();
        this.addChild(layer);

        director.runScene(this);
    }
});

//
// Flow control
//

var arrayOfUnitTest = [

    RectUnitTest,
    DictionaryToFromTest

];

var nextUnitTest = function () {
    unitTestSceneIdx++;
    unitTestSceneIdx = unitTestSceneIdx % arrayOfUnitTest.length;

    return new arrayOfUnitTest[unitTestSceneIdx]();
};
var previousUnitTest = function () {
    unitTestSceneIdx--;
    if (unitTestSceneIdx < 0)
        unitTestSceneIdx += arrayOfUnitTest.length;

    return new arrayOfUnitTest[unitTestSceneIdx]();
};
var restartUnitTest = function () {
    return new arrayOfUnitTest[unitTestSceneIdx]();
};

