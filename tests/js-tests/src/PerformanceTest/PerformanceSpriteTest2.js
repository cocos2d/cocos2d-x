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

var SECONDS_PER_TEST = 5;
//------------------------------------------------------------------
//
// Profiler
//
//------------------------------------------------------------------

function Profiling(name) {
    this.name = name;
    this.numberOfCalls = 0;
    this.totalTime = 0;
    this.minTime = 10000;
    this.maxTime = 0;
    this.lastUpdate = 0;

    this.beginBlock = function() {
        this.lastUpdate = Date.now();
    };

    this.endBlock = function() {
        var now = Date.now();
        var diff = now-this.lastUpdate;
        this.totalTime += diff;
        this.numberOfCalls++;
        this.minTime = Math.min(this.minTime, diff);
        this.maxTime = Math.max(this.maxTime, diff);
    };

    this.beginEndBlock = function(diff) {
        this.totalTime += diff;
        this.numberOfCalls++;
        this.minTime = Math.min(this.minTime, diff);
        this.maxTime = Math.max(this.maxTime, diff);
    };

    this.reset = function() {
        this.totalTime = 0;
        this.minTime = 100000;
        this.maxTime = 0;
        this.lastUpdate = 0;
        this.numberOfCalls = 0;
    };

    this.dump = function() {
        cc.log('Profiling info for: ' + this.name + '\n' +
                'Number of calls: ' + this.numberOfCalls + '\n' +
                'Average Time: ' + (this.totalTime/this.numberOfCalls)/1000 + '\n' +
                'Min Time: ' + this.minTime/1000 + '\n' +
                'Max Time: ' + this.maxTime/1000 + '\n' +
                'Total Time: ' + this.totalTime/1000 + '\n'
                );
    };
}



var performanceSpriteTestSceneIdx = -1;
//------------------------------------------------------------------
//
// PerformanceSpriteTestDemo
//
//------------------------------------------------------------------
var PerformanceTestBase = cc.Layer.extend({
    _title:"",
    _subtitle:"",

    ctor:function() {
        this._super();
        this.init();
    },
    onEnter:function () {
        this._super();

        var label = new cc.LabelTTF(this._title, "Arial", 28);
        this.addChild(label, 1);
        label.x = winSize.width / 2;
        label.y = winSize.height - 50;

        if (this._subtitle !== "") {
            var l = new cc.LabelTTF(this._subtitle, "Thonburi", 16);
            this.addChild(l, 1);
            l.x = winSize.width / 2;
            l.y = winSize.height - 80;
        }

        var item1 = new cc.MenuItemImage(s_pathB1, s_pathB2, this.onBackCallback, this);
        var item2 = new cc.MenuItemImage(s_pathR1, s_pathR2, this.onRestartCallback, this);
        var item3 = new cc.MenuItemImage(s_pathF1, s_pathF2, this.onNextCallback, this);

        var menu = new cc.Menu(item1, item2, item3);

        menu.x = 0;

        menu.y = 0;
        var csw = item2.width, csh = item2.height;
        item1.x = winSize.width/2 - csw*2;
        item1.y = csh/2;
        item2.x = winSize.width/2;
        item2.y = csh/2;
        item3.x = winSize.width/2 + csw*2;
        item3.y = csh/2;

        this.addChild(menu, 1);
    },

    onRestartCallback:function (sender) {
        var s = new PerformanceSpriteTestScene();
        s.addChild(restartPerformanceSpriteTest());
        director.runScene(s);
    },
    onNextCallback:function (sender) {
        var s = new PerformanceSpriteTestScene();
        s.addChild(nextPerformanceSpriteTest());
        director.runScene(s);
    },
    onBackCallback:function (sender) {
        var s = new PerformanceSpriteTestScene();
        s.addChild(previousPerformanceSpriteTest());
        director.runScene(s);
    }
});

//------------------------------------------------------------------
//
// PerformanceSpriteTest1
//
//------------------------------------------------------------------
var PerformanceSpriteTest1 = PerformanceTestBase.extend({
    _title:"Performance Test 1",
    _subtitle:"Let it run until you see the 'done' message. See console for results.",

    ctor:function () {
        this._super();

        this.testFunctions = [this.testA, this.testB];
        this.endFunctions = [this.endA, this.endB];
        this.testSpriteTotals = [100,500,1000,2000,5000,10000];
        this.functionsIdx = 0;
        this.spritesTotalsIdx = -1;

        this.runNextTest();

        this.scheduleUpdate();
        this.schedule( this.endProfiling, SECONDS_PER_TEST);
        this.firstTick = true;
    },

    runNextTest:function() {

        // cleanup current function
        if( this.spritesTotalsIdx != -1) {
            var cleanup = this.endFunctions[ this.functionsIdx ];
            cleanup.bind(this)();
        }

        this.spritesTotalsIdx++;

        // get next function
        if( this.spritesTotalsIdx >= this.testSpriteTotals.length ) {
            this.spritesTotalsIdx = 0;
            this.functionsIdx++;
            if( this.functionsIdx >= this.testFunctions.length ) {
                cc.log("No more tests");
                return false;
            }
        }
        var func = this.testFunctions[ this.functionsIdx ];
        var t = this.testSpriteTotals[ this.spritesTotalsIdx ];
        func.bind(this)(t);
        return true;
    },

    testA:function(num) {
        // Draws all sprites on the screen
        // Non-batched drawing

        this.profiling = new Profiling("Test A - Total Sprites: " + num);

        // use the same seed for the tests
        Math.seedrandom('perftest');
        var parent = new cc.Node();
        this.addChild(parent,0,10);

        for( var i=0; i<num; i++) {
            var sprite = new cc.Sprite('Images/grossini.png');
            parent.addChild( sprite );

            var x = Math.random() * winSize.width;
            var y = Math.random() * winSize.height;
            sprite.x = x;
            sprite.y = y;
        }
    },
    endA:function() {
        this.removeChildByTag( 10, true );
    },

    testB:function(num) {
        // Draws all sprites on the screen
        // Batched drawing

        this.profiling = new Profiling("Test B - Total Sprites: " + num);

        // use the same seed for the tests
        Math.seedrandom('perftest');
        var parent = new cc.SpriteBatchNode('Images/grossini.png',num);
        this.addChild(parent,0,10);
        for( var i=0; i<num; i++) {
            var sprite = new cc.Sprite('Images/grossini.png');
            parent.addChild( sprite );

            var x = Math.random() * winSize.width;
            var y = Math.random() * winSize.height;
            sprite.x = x;
            sprite.y = y;
        }
    },
    endB:function() {
        this.removeChildByTag( 10, true );
    },

    update:function(dt) {
        if( ! this.firstTick ) {
            var ms = director.getSecondsPerFrame();
            this.profiling.beginEndBlock(ms*1000);
        } else
            this.firstTick = false;
    },

    endProfiling:function(dt) {
        this.profiling.dump();
        this.firstTick = true;
        if( ! this.runNextTest() )
            this.unschedule( this.endProfiling );
    }
});




//------------------------------------------------------------------
//
// Scenes
//
//------------------------------------------------------------------
var arrayOfPerformanceSpriteTest = [

    PerformanceSpriteTest1

];
var PerformanceSpriteTestScene = TestScene.extend({
    runThisTest:function (num) {
        performanceSpriteTestSceneIdx = (num || num == 0) ? (num - 1) : -1;
        var layer = nextPerformanceSpriteTest();
        this.addChild(layer);

        director.runScene(this);
    }
});

var nextPerformanceSpriteTest = function () {
    performanceSpriteTestSceneIdx++;
    performanceSpriteTestSceneIdx = performanceSpriteTestSceneIdx % arrayOfPerformanceSpriteTest.length;

    return new arrayOfPerformanceSpriteTest[performanceSpriteTestSceneIdx]();
};
var previousPerformanceSpriteTest = function () {
    performanceSpriteTestSceneIdx--;
    if (performanceSpriteTestSceneIdx < 0)
        performanceSpriteTestSceneIdx += arrayOfPerformanceSpriteTest.length;

    return new arrayOfPerformanceSpriteTest[performanceSpriteTestSceneIdx]();
};
var restartPerformanceSpriteTest = function () {
    return new arrayOfPerformanceSpriteTest[performanceSpriteTestSceneIdx]();
};

function runPerformanceSpriteTest2() {
    var scene = new PerformanceSpriteTestScene();
    scene.runThisTest();
}
