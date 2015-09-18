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


var effectsTestSceneIdx = -1;

//
// Base Layer
//

var EffectsBaseLayer = BaseTestLayer.extend({
    code:function () {
        return "";
    },
    // callbacks
    onRestartCallback:function (sender) {
        var s = new EffectsTestScene();
        s.addChild(restartEffectsTest());
        director.runScene(s);
    },
    onNextCallback:function (sender) {
        var s = new EffectsTestScene();
        s.addChild(nextEffectsTest());
        //director.runScene(cc.TransitionZoomFlipX.create(5, s));
        director.runScene(s);
    },
    onBackCallback:function (sender) {
        var s = new EffectsTestScene();
        s.addChild(previousEffectsTest());
        director.runScene(s);
    },
    onEnter:function () {
        this._super();

        var node = new cc.Node();

        //Whether to demonstrate the effects inside a smaller rect
        var nodeGrid = new cc.NodeGrid();
        nodeGrid.addChild(node);
        nodeGrid.runAction(this.getEffect(3));
        this.addChild( nodeGrid );

        // back gradient
        var gradient = new cc.LayerGradient( cc.color(255,0,0,255), cc.color(255,255,0,255));
        node.addChild( gradient );

        // back image
        var bg = new cc.Sprite(s_back3);
        bg.x = winSize.width/2;
        bg.y = winSize.height/2;
        node.addChild( bg );

        var sister1 = new cc.Sprite(s_pathSister1);
        sister1.x = winSize.width/3;
        sister1.y = winSize.height/2;
        node.addChild( sister1, 1 );

        var sister2 = new cc.Sprite(s_pathSister2);
        sister2.x = winSize.width*2/3;
        sister2.y = winSize.height/2;
        node.addChild( sister2, 1 );

        var sc = cc.scaleBy(2, 5);
        var sc_back = sc.reverse();
        var seq = cc.sequence( sc, sc_back );
        var repeat = seq.repeatForever();

        sister1.runAction( repeat );
        sister2.runAction( repeat.clone() );
    },

    getEffect:function(duration) {
        // override me
        return cc.moveBy(2, cc.p(10,10) );
    },

    // automation
    numberOfPendingTests:function() {
        return ( (arrayOfEffectsTest.length-1) - effectsTestSceneIdx );
    },

    getTestNumber:function() {
        return effectsTestSceneIdx;
    }

});

//------------------------------------------------------------------
//
// Tests
//
//------------------------------------------------------------------
var Shaky3DTest = EffectsBaseLayer.extend({
    title:function () {
        return "Shaky 3D";
    },
    code:function () {
        return "a = cc.shaky3D(duration, gridSize, range, shakeZ)";
    },
    getEffect:function(duration) {
        return cc.shaky3D( duration, cc.size(15,10), 5, false );
    }
});

var Waves3DTest = EffectsBaseLayer.extend({
    title:function () {
        return "Waves 3D";
    },
    code:function () {
        return "a = cc.waves3D(duration, gridSize, range, shakeZ)";
    },
    getEffect:function(duration) {
        return cc.waves3D(duration, cc.size(15,10), 5, 40 );
    }
});

var FlipXTest = EffectsBaseLayer.extend({
    title:function () {
        return "FlipX3D";
    },
    code:function () {
        return "a = cc.flipX3D(duration )";
    },
    getEffect:function(duration) {
        var a = cc.flipX3D(duration);
        var delay = cc.delayTime(2);
        var r = a.reverse();
        return cc.sequence( a, delay, r );
    }
});

var FlipYTest = EffectsBaseLayer.extend({
    title:function () {
        return "FlipY3D";
    },
    code:function () {
        return "a = cc.flipY3D(duration )";
    },
    getEffect:function(duration) {
        var a = cc.flipY3D(duration );
        var delay = cc.delayTime(2);
        var r = a.reverse();
        return cc.sequence( a, delay, r );
    }
});

var Lens3DTest = EffectsBaseLayer.extend({
    title:function () {
        return "Lens3D";
    },
    code:function () {
        return "a = cc.lens3D(duration, gridSize, position, radius)";
    },
    getEffect:function(duration) {
        return cc.lens3D( duration, cc.size(15,10), cc.p(winSize.width/2, winSize.height/2), 240);
    }
});

var Ripple3DTest = EffectsBaseLayer.extend({
    title:function () {
        return "Ripple3D";
    },
    code:function () {
        return "a = cc.ripple3D(duration, gridSize, position, radius, waves, amplitude)";
    },
    getEffect:function(duration) {
        return cc.ripple3D( duration, cc.size(32,24), cc.p(winSize.width/2, winSize.height/2), 240, 4, 160);
    }
});

var LiquidTest = EffectsBaseLayer.extend({
    title:function () {
        return "Liquid";
    },
    code:function () {
        return "a = cc.liquid(duration, gridSize, waves, amplitude)";
    },
    getEffect:function(duration) {
        return cc.liquid( duration, cc.size(16,12), 4, 20);
    }
});

var WavesTest = EffectsBaseLayer.extend({
    title:function () {
        return "Waves";
    },
    code:function () {
        return "a = cc.waves(duration, gridSize, waves, amplitude, horizontal, vertical)";
    },
    getEffect:function(duration) {
        return cc.waves( duration, cc.size(16,12), 4, 20, true, true);
    }
});

var TwirlTest = EffectsBaseLayer.extend({
    title:function () {
        return "Twirl";
    },
    code:function () {
        return "a = cc.twirl(duration, gridSize, position, twirls, amplitude)";
    },
    getEffect:function(duration) {
        return cc.twirl( duration, cc.size(12,8), cc.p(winSize.width/2, winSize.height/2), 1, 2.5);
    }
});

var ShakyTiles3DTest = EffectsBaseLayer.extend({
    title:function () {
        return "ShakyTiles3D";
    },
    code:function () {
        return "a = cc.shakyTiles3D(duration, gridSize, range, shakeZ)";
    },
    getEffect:function(duration) {
        return cc.shakyTiles3D( duration, cc.size(16,12), 5, false);
    }
});

var ShatteredTiles3DTest = EffectsBaseLayer.extend({
    title:function () {
        return "ShatteredTiles3D";
    },
    code:function () {
        return "a = cc.shatteredTiles3D(duration, gridSize, range, shatterZ)";
    },
    getEffect:function(duration) {
        return cc.shatteredTiles3D( duration, cc.size(16,12), 5, false);
    }
});

var ShuffleTilesTest = EffectsBaseLayer.extend({
    title:function () {
        return "ShuffleTiles";
    },
    code:function () {
        return "a = cc.shuffleTiles(duration, gridSize, seed)";
    },
    getEffect:function(duration) {
        var action = cc.shuffleTiles( duration, cc.size(16,12), 25);
        var delay = cc.delayTime(2);
        var back = action.reverse();
        var seq = cc.sequence( action, delay, back);
        return seq;
    }
});

var FadeOutTRTilesTest = EffectsBaseLayer.extend({
    title:function () {
        return "FadeOutTRTilesTest";
    },
    code:function () {
        return "a = cc.fadeOutTRTiles(duration, gridSize)";
    },
    getEffect:function(duration) {
        var action = cc.fadeOutTRTiles( duration, cc.size(16,12));
        var delay = cc.delayTime(0.5);
        var back = action.reverse();
        var seq = cc.sequence( action, delay, back);
        return seq;
    }
});

var FadeOutBLTilesTest = EffectsBaseLayer.extend({
    title:function () {
        return "FadeOutBLTilesTest";
    },
    code:function () {
        return "a = cc.fadeOutBLTiles(duration, gridSize)";
    },
    getEffect:function(duration) {
        var action = cc.fadeOutBLTiles( duration, cc.size(16,12));
        var delay = cc.delayTime(0.5);
        var back = action.reverse();
        var seq = cc.sequence( action, delay, back);
        return seq;
    }
});

var FadeOutUpTilesTest = EffectsBaseLayer.extend({
    title:function () {
        return "FadeOutUpTilesTest";
    },
    code:function () {
        return "a = cc.fadeOutUpTiles(duration, gridSize)";
    },
    getEffect:function(duration) {
        var action = cc.fadeOutUpTiles( duration, cc.size(16,12));
        var delay = cc.delayTime(0.5);
        var back = action.reverse();
        var seq = cc.sequence( action, delay, back);
        return seq;
    }
});

var FadeOutDownTilesTest = EffectsBaseLayer.extend({
    title:function () {
        return "FadeOutDownTilesTest";
    },
    code:function () {
        return "a = cc.fadeOutDownTiles(duration, gridSize)";
    },
    getEffect:function(duration) {
        var action = cc.fadeOutDownTiles( duration, cc.size(16,12));
        var delay = cc.delayTime(0.5);
        var back = action.reverse();
        var seq = cc.sequence( action, delay, back);
        return seq;
    }
});

var TurnOffTilesTest = EffectsBaseLayer.extend({
    title:function () {
        return "TurnOffTiles";
    },
    code:function () {
        return "a = cc.turnOffTiles(duration, gridSize, seed)";
    },
    getEffect:function(duration) {
        var action = cc.turnOffTiles( duration, cc.size(48,32), 25);
        var delay = cc.delayTime(0.5);
        var back = action.reverse();
        var seq = cc.sequence( action, delay, back);
        return seq;
    }
});

var WavesTiles3DTest = EffectsBaseLayer.extend({
    title:function () {
        return "WavesTiles3D";
    },
    code:function () {
        return "a = cc.wavesTiles3D(duration, gridSize, waves, amplitude)";
    },
    getEffect:function(duration) {
        var action = cc.wavesTiles3D( duration, cc.size(16,12), 4, 120);
        return action;
    }
});


var JumpTiles3DTest = EffectsBaseLayer.extend({
    title:function () {
        return "JumpTiles3D";
    },
    code:function () {
        return "a = cc.jumpTiles3D(duration, gridSize, jumps, amplitude)";
    },
    getEffect:function(duration) {
        var action = cc.jumpTiles3D(duration, cc.size(16,12), 2, 30);
        return action;
    }
});

var SplitRowsTest = EffectsBaseLayer.extend({
    title:function () {
        return "SplitRows";
    },
    code:function () {
        return "a = cc.splitRows(duration, rows)";
    },
    getEffect:function(duration) {
        var action = cc.splitRows(duration, 9);
        var delay = cc.delayTime(0.5);
        var back = action.reverse();
        var seq = cc.sequence( action, delay, back);
        return seq;
    }
});

var SplitColsTest = EffectsBaseLayer.extend({
    title:function () {
        return "SplitCols";
    },
    code:function () {
        return "a = cc.splitCols(duration, cols)";
    },
    getEffect:function(duration) {
        var action = cc.splitCols(duration, 9);
        var delay = cc.delayTime(0.5);
        var back = action.reverse();
        var seq = cc.sequence( action, delay, back);
        return seq;
    }
});

var PageTurn3DTest = EffectsBaseLayer.extend({
    title:function () {
        return "PageTurn3D";
    },
    code:function () {
        return "a = cc.pageTurn3D(duration, gridSize)";
    },
    getEffect:function(duration) {
        var action = cc.pageTurn3D(duration, cc.size(15,10));
        return action;
    }
});

var PageTurn3DInRectTest = BaseTestLayer.extend({
    title:function () {
        return "PageTurn3DInRectTest";
    },
    code:function () {
        return "a = cc.pageTurn3D(duration, gridSize)";
    },
    // callbacks
    onRestartCallback:function (sender) {
        var s = new EffectsTestScene();
        s.addChild(restartEffectsTest());
        director.runScene(s);
    },
    onNextCallback:function (sender) {
        var s = new EffectsTestScene();
        s.addChild(nextEffectsTest());
        //director.runScene(cc.TransitionZoomFlipX.create(5, s));
        director.runScene(s);
    },
    onBackCallback:function (sender) {
        var s = new EffectsTestScene();
        s.addChild(previousEffectsTest());
        director.runScene(s);
    },
    onEnter:function(){
        this._super();

        //var node = new cc.Node();
        var visiableSize = director.getVisibleSize();
        var gridRect = cc.rect(visiableSize.width*0.1,
            visiableSize.height*0.1,
            visiableSize.width*0.4,
            visiableSize.height*0.4);
        var gridNodeTarget = new cc.NodeGrid(gridRect);

        gridNodeTarget.runAction(this.getEffect(3));
        this.addChild( gridNodeTarget );

        // back gradient
        var background = new cc.LayerGradient( cc.color(255,0,0,255), cc.color(255,255,0,255));
        gridNodeTarget.addChild( background );

        // back image
        var bg = new cc.Sprite(s_back3);
        bg.x = winSize.width/2;
        bg.y = winSize.height/2;
        gridNodeTarget.addChild( bg );

        var sister1 = new cc.Sprite(s_pathSister1);
        sister1.x = winSize.width/3;
        sister1.y = winSize.height/2;
        gridNodeTarget.addChild( sister1, 1 );

        var sister2 = new cc.Sprite(s_pathSister2);
        sister2.x = winSize.width*2/3;
        sister2.y = winSize.height/2;
        gridNodeTarget.addChild( sister2, 1 );

        var sc = cc.scaleBy(2, 5);
        var sc_back = sc.reverse();
        var seq = cc.sequence( sc, sc_back );
        var repeat = seq.repeatForever();

        sister1.runAction( repeat );
        sister2.runAction( repeat.clone() );
    },

    getEffect:function(duration) {
        var action = cc.pageTurn3D(duration, cc.size(15,10));
        return action;
    }
});

//
// Order of tests
//
var EffectsTestScene = TestScene.extend({
    runThisTest:function (num) {
        effectsTestSceneIdx = (num || num == 0) ? (num - 1) : -1;
        var layer = nextEffectsTest();
        this.addChild(layer);

        director.runScene(this);
    }
});

//
// Flow control
//
var arrayOfEffectsTest = [
    Shaky3DTest,
    Waves3DTest,
    FlipXTest,
    FlipYTest,
    Lens3DTest,
    Ripple3DTest,
    LiquidTest,
    WavesTest,
    TwirlTest,
    ShakyTiles3DTest,
    ShatteredTiles3DTest,
    ShuffleTilesTest,
    FadeOutTRTilesTest,
    FadeOutBLTilesTest,
    FadeOutUpTilesTest,
    FadeOutDownTilesTest,
    TurnOffTilesTest,
    WavesTiles3DTest,
    JumpTiles3DTest,
    SplitRowsTest,
    SplitColsTest,
    PageTurn3DTest,
    PageTurn3DInRectTest
];

var nextEffectsTest = function () {
    effectsTestSceneIdx++;
    effectsTestSceneIdx = effectsTestSceneIdx % arrayOfEffectsTest.length;

    if(window.sideIndexBar){
        effectsTestSceneIdx = window.sideIndexBar.changeTest(effectsTestSceneIdx, 14);
    }

    return new arrayOfEffectsTest[effectsTestSceneIdx]();
};
var previousEffectsTest = function () {
    effectsTestSceneIdx--;
    if (effectsTestSceneIdx < 0)
        effectsTestSceneIdx += arrayOfEffectsTest.length;

    if(window.sideIndexBar){
        effectsTestSceneIdx = window.sideIndexBar.changeTest(effectsTestSceneIdx, 14);
    }

    return new arrayOfEffectsTest[effectsTestSceneIdx]();
};
var restartEffectsTest = function () {
    return new arrayOfEffectsTest[effectsTestSceneIdx]();
};