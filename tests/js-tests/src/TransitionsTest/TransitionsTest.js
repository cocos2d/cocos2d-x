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
TRANSITION_DURATION = 1.2;

var arrayOfTransitionsTest = [

    {title:"JumpZoomTransition", transitionFunc:function (t, s) {
        return new JumpZoomTransition(t, s);
    }},

    {title:"TransitionProgressRadialCCW", transitionFunc:function (t, s) {
        return new cc.TransitionProgressRadialCCW(t, s);
    }},

    {title:"TransitionProgressRadialCW", transitionFunc:function (t, s) {
        return new cc.TransitionProgressRadialCW(t, s);
    }},

    {title:"TransitionProgressHorizontal", transitionFunc:function (t, s) {
        return new cc.TransitionProgressHorizontal(t, s);
    }},

    {title:"TransitionProgressVertical", transitionFunc:function (t, s) {
        return new cc.TransitionProgressVertical(t, s);
    }},

    {title:"TransitionProgressInOut", transitionFunc:function (t, s) {
        return new cc.TransitionProgressInOut(t, s);
    }},

    {title:"TransitionProgressOutIn", transitionFunc:function (t, s) {
        return new cc.TransitionProgressOutIn(t, s);
    }},

    //ok
    {title:"FadeTransition", transitionFunc:function (t, s) {
        return FadeTransition(t, s);
    }},
    {title:"FadeWhiteTransition", transitionFunc:function (t, s) {
        return FadeWhiteTransition(t, s);
    }},

    {title:"ShrinkGrowTransition", transitionFunc:function (t, s) {
        return ShrinkGrowTransition(t, s);
    }},
    {title:"RotoZoomTransition", transitionFunc:function (t, s) {
        return RotoZoomTransition(t, s);
    }},
    {title:"MoveInLTransition", transitionFunc:function (t, s) {
        return MoveInLTransition(t, s);
    }},
    {title:"MoveInRTransition", transitionFunc:function (t, s) {
        return MoveInRTransition(t, s);
    }},
    {title:"MoveInTTransition", transitionFunc:function (t, s) {
        return MoveInTTransition(t, s);
    }},
    {title:"MoveInBTransition", transitionFunc:function (t, s) {
        return MoveInBTransition(t, s);
    }},
    {title:"SlideInLTransition", transitionFunc:function (t, s) {
        return SlideInLTransition(t, s);
    }},
    {title:"SlideInRTransition", transitionFunc:function (t, s) {
        return SlideInRTransition(t, s);
    }},
    {title:"SlideInTTransition", transitionFunc:function (t, s) {
        return SlideInTTransition(t, s);
    }},
    {title:"SlideInBTransition", transitionFunc:function (t, s) {
        return SlideInBTransition(t, s);
    }},
    {title:"CCTransitionRadialCCW", transitionFunc:function (t, s) {
        return CCTransitionRadialCCW(t, s);
    }},
    {title:"CCTransitionRadialCW", transitionFunc:function (t, s) {
        return CCTransitionRadialCW(t, s);
    }}
];

if ('opengl' in cc.sys.capabilities) {
    arrayOfTransitionsTest = arrayOfTransitionsTest.concat(
        [
            {title: "FlipXLeftOver", transitionFunc: function (t, s) {
                return FlipXLeftOver(t, s);
            }},
            {title: "FlipXRightOver", transitionFunc: function (t, s) {
                return FlipXRightOver(t, s);
            }},
            {title: "FlipYUpOver", transitionFunc: function (t, s) {
                return FlipYUpOver(t, s);
            }},
            {title: "FlipYDownOver", transitionFunc: function (t, s) {
                return FlipYDownOver(t, s);
            }},
            {title: "FlipAngularLeftOver", transitionFunc: function (t, s) {
                return FlipAngularLeftOver(t, s);
            }},
            {title: "FlipAngularRightOver", transitionFunc: function (t, s) {
                return FlipAngularRightOver(t, s);
            }},
            {title: "ZoomFlipXLeftOver", transitionFunc: function (t, s) {
                return ZoomFlipXLeftOver(t, s);
            }},
            {title: "ZoomFlipXRightOver", transitionFunc: function (t, s) {
                return ZoomFlipXRightOver(t, s);
            }},
            {title: "ZoomFlipYUpOver", transitionFunc: function (t, s) {
                return ZoomFlipYUpOver(t, s);
            }},
            {title: "ZoomFlipYDownOver", transitionFunc: function (t, s) {
                return ZoomFlipYDownOver(t, s);
            }},
            {title: "ZoomFlipAngularLeftOver", transitionFunc: function (t, s) {
                return ZoomFlipAngularLeftOver(t, s);
            }},
            {title: "ZoomFlipAngularRightOver", transitionFunc: function (t, s) {
                return ZoomFlipAngularRightOver(t, s);
            }},
            {title: "PageTransitionForward", transitionFunc: function (t, s) {
                return PageTransitionForward(t, s);
            }},
            {title: "PageTransitionBackward", transitionFunc: function (t, s) {
                return PageTransitionBackward(t, s);
            }},
            {title: "FadeTRTransition", transitionFunc: function (t, s) {
                return FadeTRTransition(t, s);
            }},
            {title: "FadeBLTransition", transitionFunc: function (t, s) {
                return FadeBLTransition(t, s);
            }},
            {title: "FadeUpTransition", transitionFunc: function (t, s) {
                return FadeUpTransition(t, s);
            }},
            {title: "FadeDownTransition", transitionFunc: function (t, s) {
                return FadeDownTransition(t, s);
            }},
            {title: "TurnOffTilesTransition", transitionFunc: function (t, s) {
                return TurnOffTilesTransition(t, s);
            }},
            {title: "SplitRowsTransition", transitionFunc: function (t, s) {
                return SplitRowsTransition(t, s);
            }},
            {title: "CCTransitionCrossFade", transitionFunc: function (t, s) {
                return CCTransitionCrossFade(t, s);
            }},
            {title: "SplitColsTransition", transitionFunc: function (t, s) {
                return SplitColsTransition(t, s);
            }}
        ]);
}

var transitionsIdx = 0;

// the class inherit from TestScene
// every .Scene each test used must inherit from TestScene,
// make sure the test have the menu item for back to main menu
var TransitionsTestScene = TestScene.extend({
    onEnter: function () {
        this._super();
        director.setDepthTest(false);
    },
    runThisTest:function () {
        var layer = new TestLayer1();
        this.addChild(layer);
        director.runScene(this);
    }
});

var TransitionBase = BaseTestLayer.extend({

    testDuration:TRANSITION_DURATION + 0.1,
    title:function() {
        return arrayOfTransitionsTest[transitionsIdx].title;
    },
    ctor:function () {
        this._super(this.colorA, this.colorB);

        var x, y;
        var size = director.getWinSize();
        x = size.width;
        y = size.height;

        var bg1 = new cc.Sprite(this.backgroundImage);
        bg1.x = size.width / 2;
        bg1.y = size.height / 2;
        bg1.scale = 1.7;
        this.addChild(bg1);

        var title = new cc.LabelTTF(this.title(), "Thonburi", 32);
        this.addChild(title);
        title.color = cc.color(255, 32, 32);
        title.x = x / 2;
        title.y = y - 100;

        var label = new cc.LabelTTF(this.sceneName, "Marker Felt", 38);
        label.color = cc.color(16, 16, 255);
        label.x = x / 2;
        label.y = y / 2;
        this.addChild(label);

        // this.schedule(this.step, 1.0);
    },
    onRestartCallback:function (sender) {
        var s = new TransitionsTestScene();

        var layer = this.createNextScene();
        s.addChild(layer);
        var scene = arrayOfTransitionsTest[transitionsIdx].transitionFunc(TRANSITION_DURATION, s);

        if (scene)
            director.runScene(scene);
    },
    onNextCallback:function (sender) {
        transitionsIdx++;
        transitionsIdx = transitionsIdx % arrayOfTransitionsTest.length;

        var s = new TransitionsTestScene();

        var layer = this.createNextScene();
        s.addChild(layer);

        var scene = arrayOfTransitionsTest[transitionsIdx].transitionFunc(TRANSITION_DURATION, s);
        if (scene)
            director.runScene(scene);
    },
    onBackCallback:function (sender) {
        transitionsIdx--;
        if (transitionsIdx < 0)
            transitionsIdx += arrayOfTransitionsTest.length;

        var s = new TransitionsTestScene();
        var layer = this.createNextScene();
        s.addChild(layer);

        var scene = arrayOfTransitionsTest[transitionsIdx].transitionFunc(TRANSITION_DURATION, s);
        if (scene)
            director.runScene(scene);
    },

    step:function (dt) {
    },

    onEnter:function () {
        this._super();
        this.log("" + this.sceneName + " onEnter");
    },
    onEnterTransitionDidFinish:function () {
        this._super();
        this.log("" + this.sceneName + " onEnterTransitionDidFinish");
    },

    onExitTransitionDidStart:function () {
        this._super();
        this.log("" + this.sceneName + " onExitTransitionDidStart");
    },

    onExit:function () {
        this._super();
        this.log("" + this.sceneName + " onExit");
    },
    // automation
    numberOfPendingTests:function() {
        return ( (arrayOfTransitionsTest.length-1) - transitionsIdx );
    },

    getTestNumber:function() {
        return transitionsIdx;
    }

});
var TestLayer1 = TransitionBase.extend({
    backgroundImage:s_back1,
    colorA:cc.color(0,0,0,255),
    colorB:cc.color(160,99,117,255),
    sceneName:"Scene 1",
    createNextScene:function() {
        return new TestLayer2();
    }
});

var TestLayer2 = TransitionBase.extend({
    backgroundImage:s_back2,
    colorA:cc.color(0,0,0,255),
    colorB:cc.color(99,160,117,255),
    sceneName:"Scene 2",
    createNextScene:function() {
        return new TestLayer1();
    }
});

var JumpZoomTransition = function (t, s) {
    return new cc.TransitionJumpZoom(t, s);
};
var FadeTransition = function (t, s) {
    return new cc.TransitionFade(t, s);
};

var FadeWhiteTransition = function (t, s) {
    return new cc.TransitionFade(t, s, cc.color(255, 255, 255));
};

var FlipXLeftOver = function (t, s) {
    return new cc.TransitionFlipX(t, s, cc.TRANSITION_ORIENTATION_LEFT_OVER);
};

var FlipXRightOver = function (t, s) {
    return new cc.TransitionFlipX(t, s, cc.TRANSITION_ORIENTATION_RIGHT_OVER);
};

var FlipYUpOver = function (t, s) {
    return new cc.TransitionFlipY(t, s, cc.TRANSITION_ORIENTATION_UP_OVER);
};

var FlipYDownOver = function (t, s) {
    return new cc.TransitionFlipY(t, s, cc.TRANSITION_ORIENTATION_DOWN_OVER);
};

var FlipAngularLeftOver = function (t, s) {
    return new cc.TransitionFlipAngular(t, s, cc.TRANSITION_ORIENTATION_LEFT_OVER);
};

var FlipAngularRightOver = function (t, s) {
    return new cc.TransitionFlipAngular(t, s, cc.TRANSITION_ORIENTATION_RIGHT_OVER);
};

var ZoomFlipXLeftOver = function (t, s) {
    return new cc.TransitionZoomFlipX(t, s, cc.TRANSITION_ORIENTATION_LEFT_OVER);
};

var ZoomFlipXRightOver = function (t, s) {
    return new cc.TransitionZoomFlipX(t, s, cc.TRANSITION_ORIENTATION_RIGHT_OVER);
};

var ZoomFlipYUpOver = function (t, s) {
    return new cc.TransitionZoomFlipY(t, s, cc.TRANSITION_ORIENTATION_UP_OVER);
};

var ZoomFlipYDownOver = function (t, s) {
    return new cc.TransitionZoomFlipY(t, s, cc.TRANSITION_ORIENTATION_DOWN_OVER);
};

var ZoomFlipAngularLeftOver = function (t, s) {
    return new cc.TransitionZoomFlipAngular(t, s, cc.TRANSITION_ORIENTATION_LEFT_OVER);
};

var ZoomFlipAngularRightOver = function (t, s) {
    return new cc.TransitionZoomFlipAngular(t, s, cc.TRANSITION_ORIENTATION_RIGHT_OVER);
};

var ShrinkGrowTransition = function (t, s) {
    return new cc.TransitionShrinkGrow(t, s);
};

var RotoZoomTransition = function (t, s) {
    return new cc.TransitionRotoZoom(t, s);
};

var MoveInLTransition = function (t, s) {
    return new cc.TransitionMoveInL(t, s);
};

var MoveInRTransition = function (t, s) {
    return new cc.TransitionMoveInR(t, s);
};

var MoveInTTransition = function (t, s) {
    return new cc.TransitionMoveInT(t, s);
};

var MoveInBTransition = function (t, s) {
    return new cc.TransitionMoveInB(t, s);
};

var SlideInLTransition = function (t, s) {
    return new cc.TransitionSlideInL(t, s);
};

var SlideInRTransition = function (t, s) {
    return new cc.TransitionSlideInR(t, s);
};

var SlideInTTransition = function (t, s) {
    return new cc.TransitionSlideInT(t, s);
};

var SlideInBTransition = function (t, s) {
    return new cc.TransitionSlideInB(t, s);
};

var CCTransitionCrossFade = function (t, s) {
    return new cc.TransitionCrossFade(t, s);
};

var CCTransitionRadialCCW = function (t, s) {
    return new cc.TransitionProgressRadialCCW(t, s);
};

var CCTransitionRadialCW = function (t, s) {
    return new cc.TransitionProgressRadialCW(t, s);
};

var PageTransitionForward = function (t, s) {
    director.setDepthTest(true);
    return new cc.TransitionPageTurn(t, s, false);
};

var PageTransitionBackward = function (t, s) {
    director.setDepthTest(true);
    return new cc.TransitionPageTurn(t, s, true);
};

var FadeTRTransition = function (t, s) {
    return new cc.TransitionFadeTR(t, s);
};

var FadeBLTransition = function (t, s) {
    return new cc.TransitionFadeBL(t, s);
};

var FadeUpTransition = function (t, s) {
    return new cc.TransitionFadeUp(t, s);
};

var FadeDownTransition = function (t, s) {
    return new cc.TransitionFadeDown(t, s);
};

var TurnOffTilesTransition = function (t, s) {
    return new cc.TransitionTurnOffTiles(t, s);
};

var SplitRowsTransition = function (t, s) {
    return new cc.TransitionSplitRows(t, s);
};

var SplitColsTransition = function (t, s) {
    return new cc.TransitionSplitCols(t, s);
};
