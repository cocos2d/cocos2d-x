/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011      Zynga Inc.

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

var TransitionsTests = [
    {title:"JumpZoomTransition", transitionFunc:function (t, s) {
        return new JumpZoomTransition(t, s);
    }},

    {title:"TransitionProgressRadialCCW", transitionFunc:function (t, s) {
        return cc.TransitionProgressRadialCCW.create(t, s);
    }},

    {title:"TransitionProgressRadialCW", transitionFunc:function (t, s) {
        return cc.TransitionProgressRadialCW.create(t, s);
    }},

    {title:"TransitionProgressHorizontal", transitionFunc:function (t, s) {
        return cc.TransitionProgressHorizontal.create(t, s);
    }},

    {title:"TransitionProgressVertical", transitionFunc:function (t, s) {
        return cc.TransitionProgressVertical.create(t, s);
    }},

    {title:"TransitionProgressInOut", transitionFunc:function (t, s) {
        return cc.TransitionProgressInOut.create(t, s);
    }},

    {title:"TransitionProgressOutIn", transitionFunc:function (t, s) {
        return cc.TransitionProgressOutIn.create(t, s);
    }},

    //ok
    {title:"FadeTransition", transitionFunc:function (t, s) {
        return new FadeTransition(t, s);
    }},
    {title:"FadeWhiteTransition", transitionFunc:function (t, s) {
        return new FadeWhiteTransition(t, s);
    }},

    /*function(t,s){ return new FlipXLeftOver(t,s);},
     function(t,s){ return new FlipXRightOver(t,s);},
     function(t,s){ return new FlipYUpOver(t,s);},
     function(t,s){ return new FlipYDownOver(t,s);},
     function(t,s){ return new FlipAngularLeftOver(t,s);},
     function(t,s){ return new FlipAngularRightOver(t,s);},
     function(t,s){ return new ZoomFlipXLeftOver(t,s);},
     function(t,s){ return new ZoomFlipXRightOver(t,s);},
     function(t,s){ return new ZoomFlipYUpOver(t,s);},
     function(t,s){ return new ZoomFlipYDownOver(t,s);},
     function(t,s){ return new ZoomFlipAngularLeftOver(t,s);},
     function(t,s){ return new ZoomFlipAngularRightOver(t,s);},*/

    {title:"ShrinkGrowTransition", transitionFunc:function (t, s) {
        return new ShrinkGrowTransition(t, s);
    }},
    {title:"RotoZoomTransition", transitionFunc:function (t, s) {
        return new RotoZoomTransition(t, s);
    }},
    {title:"MoveInLTransition", transitionFunc:function (t, s) {
        return new MoveInLTransition(t, s);
    }},
    {title:"MoveInRTransition", transitionFunc:function (t, s) {
        return new MoveInRTransition(t, s);
    }},
    {title:"MoveInTTransition", transitionFunc:function (t, s) {
        return new MoveInTTransition(t, s);
    }},
    {title:"MoveInBTransition", transitionFunc:function (t, s) {
        return new MoveInBTransition(t, s);
    }},
    {title:"SlideInLTransition", transitionFunc:function (t, s) {
        return new SlideInLTransition(t, s);
    }},
    {title:"SlideInRTransition", transitionFunc:function (t, s) {
        return new SlideInRTransition(t, s);
    }},
    {title:"SlideInTTransition", transitionFunc:function (t, s) {
        return new SlideInTTransition(t, s);
    }},
    {title:"SlideInBTransition", transitionFunc:function (t, s) {
        return new SlideInBTransition(t, s);
    }}

    /*function(t,s){ return new CCTransitionCrossFade(t,s);},
     function(t,s){ return new CCTransitionRadialCCW(t,s);},
     function(t,s){ return new CCTransitionRadialCW(t,s);},*/

    /*function(t,s){ return new PageTransitionForward(t,s);},
     function(t,s){ return new PageTransitionBackward(t,s);},
     function(t,s){ return new FadeTRTransition(t,s);},
     function(t,s){ return new FadeBLTransition(t,s);},
     function(t,s){ return new FadeUpTransition(t,s);},
     function(t,s){ return new FadeDownTransition(t,s);},
     function(t,s){ return new TurnOffTilesTransition(t,s);},
     function(t,s){ return new SplitRowsTransition(t,s);},
     function(t,s){ return new SplitColsTransition(t,s);}*/
];

var transitionsIdx = 0;

// the class inherit from TestScene
// every .Scene each test used must inherit from TestScene,
// make sure the test have the menu item for back to main menu
var TransitionsTestScene = TestScene.extend({
    runThisTest:function () {
        var layer = new TestLayer1();
        this.addChild(layer);
        cc.Director.getInstance().replaceScene(this);
    }
});

var TestLayer1 = cc.Layer.extend({
    ctor:function () {
        this._super();
        //this.init();
        var x, y;
        var size = cc.Director.getInstance().getWinSize();
        x = size.width;
        y = size.height;

        var bg1 = cc.Sprite.create(s_back1);
        bg1.setPosition(cc.p(size.width / 2, size.height / 2));
        bg1.setScale(1.7);
        this.addChild(bg1, -1);

        var title = cc.LabelTTF.create(TransitionsTests[transitionsIdx].title, "Thonburi", 32);
        this.addChild(title);
        title.setColor(cc.c3b(255, 32, 32));
        title.setPosition(cc.p(x / 2, y - 100));

        var label = cc.LabelTTF.create("SCENE 1", "Marker Felt", 38);
        label.setColor(cc.c3b(16, 16, 255));
        label.setPosition(cc.p(x / 2, y / 2));
        this.addChild(label);

        // menu
        var item1 = cc.MenuItemImage.create(s_pathB1, s_pathB2, this, this.backCallback);
        var item2 = cc.MenuItemImage.create(s_pathR1, s_pathR2, this, this.restartCallback);
        var item3 = cc.MenuItemImage.create(s_pathF1, s_pathF2, this, this.nextCallback);

        var menu = cc.Menu.create(item1, item2, item3, null);

        menu.setPosition(cc.p(0,0));
        item1.setPosition(cc.p(size.width / 2 - item2.getContentSize().width * 2, item2.getContentSize().height / 2));
        item2.setPosition(cc.p(size.width / 2, item2.getContentSize().height / 2));
        item3.setPosition(cc.p(size.width / 2 + item2.getContentSize().width * 2, item2.getContentSize().height / 2));
        this.addChild(menu, 1);
        this.schedule(this.step, 1.0);

    },
    restartCallback:function (sender) {
        var s = new TransitionsTestScene();

        var layer = new TestLayer2();
        s.addChild(layer);
        var scene = TransitionsTests[transitionsIdx].transitionFunc(TRANSITION_DURATION, s);

        if (scene) {
            cc.Director.getInstance().replaceScene(scene);
        }
    },
    nextCallback:function (sender) {
        transitionsIdx++;
        transitionsIdx = transitionsIdx % TransitionsTests.length;

        var s = new TransitionsTestScene();

        var layer = new TestLayer2();
        s.addChild(layer);

        var scene = TransitionsTests[transitionsIdx].transitionFunc(TRANSITION_DURATION, s);
        if (scene) {
            cc.Director.getInstance().replaceScene(scene);
        }
    },
    backCallback:function (sender) {
        transitionsIdx--;
        if (transitionsIdx < 0)
            transitionsIdx += TransitionsTests.length;

        var s = new TransitionsTestScene();
        var layer = new TestLayer2();
        s.addChild(layer);

        var scene = TransitionsTests[transitionsIdx].transitionFunc(TRANSITION_DURATION, s);
        if (scene) {
            cc.Director.getInstance().replaceScene(scene);
        }
    },

    step:function (dt) {
    },

    onEnter:function () {
        this._super();
        cc.log("Scene 1 onEnter");
    },
    onEnterTransitionDidFinish:function () {
        this._super();
        cc.log("Scene 1 onEnterTransitionDidFinish");
    },

    onExitTransitionDidStart:function () {
        this._super();
        cc.log("Scene 1 onExitTransitionDidStart");
    },

    onExit:function () {
        this._super();
        cc.log("Scene 1 onExit");
    }
});

var TestLayer2 = cc.Layer.extend({
    ctor:function () {
        this._super();
        //this.init();
        var x, y;
        var size = cc.Director.getInstance().getWinSize();
        x = size.width;
        y = size.height;

        var bg1 = cc.Sprite.create(s_back2);
        bg1.setPosition(cc.p(size.width / 2, size.height / 2));
        bg1.setScale(1.7);
        this.addChild(bg1, -1);

        var title = cc.LabelTTF.create(TransitionsTests[transitionsIdx].title, "Thonburi", 32);
        this.addChild(title);
        title.setColor(cc.c3b(255, 32, 32));
        title.setPosition(cc.p(x / 2, y - 100));

        var label = cc.LabelTTF.create("SCENE 2", "Marker Felt", 38);
        label.setColor(cc.c3b(16, 16, 255));
        label.setPosition(cc.p(x / 2, y / 2));
        this.addChild(label);

        // menu
        var item1 = cc.MenuItemImage.create(s_pathB1, s_pathB2, this, this.backCallback);
        var item2 = cc.MenuItemImage.create(s_pathR1, s_pathR2, this, this.restartCallback);
        var item3 = cc.MenuItemImage.create(s_pathF1, s_pathF2, this, this.nextCallback);

        var menu = cc.Menu.create(item1, item2, item3, null);

        menu.setPosition(cc.p(0,0));
        item1.setPosition(cc.p(size.width / 2 - item2.getContentSize().width * 2, item2.getContentSize().height / 2));
        item2.setPosition(cc.p(size.width / 2, item2.getContentSize().height / 2));
        item3.setPosition(cc.p(size.width / 2 + item2.getContentSize().width * 2, item2.getContentSize().height / 2));

        this.addChild(menu, 1);

        this.schedule(this.step, 1.0);
    },
    restartCallback:function (sender) {
        var s = new TransitionsTestScene();

        var layer = new TestLayer1();
        s.addChild(layer);

        var scene = TransitionsTests[transitionsIdx].transitionFunc(TRANSITION_DURATION, s);
        if (scene) {
            cc.Director.getInstance().replaceScene(scene);
        }
    },
    nextCallback:function (sender) {
        transitionsIdx++;
        transitionsIdx = transitionsIdx % TransitionsTests.length;

        var s = new TransitionsTestScene();

        var layer = new TestLayer1();
        s.addChild(layer);

        var scene = TransitionsTests[transitionsIdx].transitionFunc(TRANSITION_DURATION, s);
        if (scene) {
            cc.Director.getInstance().replaceScene(scene);
        }
    },
    backCallback:function (sender) {
        transitionsIdx--;
        if (transitionsIdx < 0)
            transitionsIdx += TransitionsTests.length;

        var s = new TransitionsTestScene();

        var layer = new TestLayer1();
        s.addChild(layer);

        var scene = TransitionsTests[transitionsIdx].transitionFunc(TRANSITION_DURATION, s);
        if (scene) {
            cc.Director.getInstance().replaceScene(scene);
        }
    },

    step:function (dt) {

    },

    onEnter:function () {
        this._super();
        cc.log("Scene 2 onEnter");
    },
    onEnterTransitionDidFinish:function () {
        this._super();
        cc.log("Scene 2 onEnterTransitionDidFinish");
    },

    onExitTransitionDidStart:function () {
        this._super();
        cc.log("Scene 2 onExitTransitionDidStart");
    },

    onExit:function () {
        this._super();
        cc.log("Scene 2 onExit");
    }
});

var JumpZoomTransition = function (t, s) {
    return cc.TransitionJumpZoom.create(t, s);
};
var FadeTransition = function (t, s) {
    return cc.TransitionFade.create(t, s);
};

var FadeWhiteTransition = function (t, s) {
    return cc.TransitionFade.create(t, s, cc.white());
};

var FlipXLeftOver = function (t, s) {
    return cc.TransitionFlipX.create(t, s, cc.ORIENTATION_LEFT_OVER);
};

var FlipXRightOver = function (t, s) {
    return cc.TransitionFlipX.create(t, s, cc.ORIENTATION_RIGHT_OVER);
};

var FlipYUpOver = function (t, s) {
    return cc.TransitionFlipY.create(t, s, cc.ORIENTATION_UP_OVER);
};

var FlipYDownOver = function (t, s) {
    return cc.TransitionFlipY.create(t, s, cc.ORIENTATION_DOWN_OVER);
};

var FlipAngularLeftOver = function (t, s) {
    return cc.TransitionFlipAngular.create(t, s, cc.ORIENTATION_LEFT_OVER);
};

var FlipAngularRightOver = function (t, s) {
    return cc.TransitionFlipAngular.create(t, s, cc.ORIENTATION_RIGHT_OVER);
};

var ZoomFlipXLeftOver = function (t, s) {
    return cc.TransitionZoomFlipX.create(t, s, cc.ORIENTATION_LEFT_OVER);
};

var ZoomFlipXRightOver = function (t, s) {
    return cc.TransitionZoomFlipX.create(t, s, cc.ORIENTATION_RIGHT_OVER);
};

var ZoomFlipYUpOver = function (t, s) {
    return cc.TransitionZoomFlipY.create(t, s, cc.ORIENTATION_UP_OVER);
};

var ZoomFlipYDownOver = function (t, s) {
    return cc.TransitionZoomFlipY.create(t, s, cc.ORIENTATION_DOWN_OVER);
};

var ZoomFlipAngularLeftOver = function (t, s) {
    return cc.TransitionZoomFlipAngular.create(t, s, cc.ORIENTATION_LEFT_OVER);
};

var ZoomFlipAngularRightOver = function (t, s) {
    return cc.TransitionZoomFlipAngular.create(t, s, cc.ORIENTATION_RIGHT_OVER);
};

var ShrinkGrowTransition = function (t, s) {
    return cc.TransitionShrinkGrow.create(t, s);
};

var RotoZoomTransition = function (t, s) {
    return cc.TransitionRotoZoom.create(t, s);
};

var MoveInLTransition = function (t, s) {
    return cc.TransitionMoveInL.create(t, s);
};

var MoveInRTransition = function (t, s) {
    return cc.TransitionMoveInR.create(t, s);
};

var MoveInTTransition = function (t, s) {
    return cc.TransitionMoveInT.create(t, s);
};

var MoveInBTransition = function (t, s) {
    return cc.TransitionMoveInB.create(t, s);
};

var SlideInLTransition = function (t, s) {
    return cc.TransitionSlideInL.create(t, s);
};

var SlideInRTransition = function (t, s) {
    return cc.TransitionSlideInR.create(t, s);
};

var SlideInTTransition = function (t, s) {
    return cc.TransitionSlideInT.create(t, s);
};

var SlideInBTransition = function (t, s) {
    return cc.TransitionSlideInB.create(t, s);
};

var CCTransitionCrossFade = function (t, s) {
    return cc.TransitionCrossFade.create(t, s);
};

var CCTransitionRadialCCW = function (t, s) {
    return cc.TransitionRadialCCW.create(t, s);
};

var CCTransitionRadialCW = function (t, s) {
    return cc.TransitionRadialCW.create(t, s);
};

var PageTransitionForward = function (t, s) {
    cc.Director.getInstance().setDepthTest(true);
    return cc.TransitionPageTurn.create(t, s, false);
};

var PageTransitionBackward = function (t, s) {
    cc.Director.getInstance().setDepthTest(true);
    return cc.TransitionPageTurn.create(t, s, true);
};

var FadeTRTransition = function (t, s) {
    return cc.TransitionFadeTR.create(t, s);
};

var FadeBLTransition = function (t, s) {
    return cc.TransitionFadeBL.create(t, s);
};

var FadeUpTransition = function (t, s) {
    return cc.TransitionFadeUp.create(t, s);
};

var FadeDownTransition = function (t, s) {
    return cc.TransitionFadeDown.create(t, s);
};

var TurnOffTilesTransition = function (t, s) {
    return cc.TransitionTurnOffTiles.create(t, s);
};

var SplitRowsTransition = function (t, s) {
    return cc.TransitionSplitRows.create(t, s);
};

var SplitColsTransition = function (t, s) {
    return cc.TransitionSplitCols.create(t, s);
};
