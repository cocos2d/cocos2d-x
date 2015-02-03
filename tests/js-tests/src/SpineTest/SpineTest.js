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

var sp = sp || {};

var ANIMATION_TYPE = {
    ANIMATION_START:      0,
    ANIMATION_END:        1,
    ANIMATION_COMPLETE:   2,
    ANIMATION_EVENT:      3
};

SpineTestScene = TestScene.extend({

    runThisTest:function () {
        var layer = new SpineTest();
        this.addChild(layer);

        director.runScene(this);
    }
});

touchcount = 0;

var SpineTest = BaseTestLayer.extend({
    _spineboy:null,
    _debugMode: 0,
    ctor:function () {
        this._super(cc.color(0,0,0,255), cc.color(98,99,117,255));

        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesBegan: function(touches, event){
                var target = event.getCurrentTarget();
                target._debugMode ++;
                target._debugMode = target._debugMode % 3;
                if (target._debugMode == 0) {
                    target._spineboy.setDebugBones(false);
                    target._spineboy.setDebugSolots(false);
                    return;
                }

                if (target._debugMode == 1) {
                    target._spineboy.setDebugBones(true);
                    target._spineboy.setDebugSolots(false);
                    return;
                }

                if (target._debugMode == 2) {
                    target._spineboy.setDebugBones(false);
                    target._spineboy.setDebugSolots(true);
                }
            }
        }, this);
        var size = director.getWinSize();

        /////////////////////////////
        // Make Spine's Animated skeleton Node
        // You need 'json + atlas + image' resource files to make it.
        // No JS binding for spine-c in this version. So, only file loading is supported.
        var spineBoy = new sp.SkeletonAnimation('res/skeletons/spineboy.json', 'res/skeletons/spineboy.atlas');
        spineBoy.setPosition(cc.p(size.width / 2, size.height / 2 - 150));
        spineBoy.setAnimation(0, 'walk', true);
        spineBoy.setMix('walk', 'jump', 0.2);
        spineBoy.setMix('jump', 'walk', 0.4);
        spineBoy.setAnimationListener(this, this.animationStateEvent);
        this.addChild(spineBoy, 4);
        this._spineboy = spineBoy;
    },
    onBackCallback:function (sender) {
    },
    onRestartCallback:function (sender) {
    },
    onNextCallback:function (sender) {
        touchcount++;
        this._spineboy.setAnimation(0, ['walk', 'jump'][touchcount % 2], true);
    },
    subtitle:function () {
        return "Spine test";
    },
    title:function () {
        return "Spine test";
    },

    animationStateEvent: function(obj, trackIndex, type, event, loopCount) {
        var entry = this._spineboy.getCurrent();
        var animationName = (entry && entry.animation) ? entry.animation.name : 0;

        switch(type)
        {
            case ANIMATION_TYPE.ANIMATION_START:
                cc.log(trackIndex + " start: " + animationName);
                break;
            case ANIMATION_TYPE.ANIMATION_END:
                cc.log(trackIndex + " end:" + animationName);
                break;
            case ANIMATION_TYPE.ANIMATION_EVENT:
                cc.log(trackIndex + " event: " + animationName);
                break;
            case ANIMATION_TYPE.ANIMATION_COMPLETE:
                cc.log(trackIndex + " complete: " + animationName + "," + loopCount);
                break;
            default :
                break;
        }
    },
    
    // automation
    numberOfPendingTests:function() {
        return 1;
    },
    getTestNumber:function() {
        return 0;
    }

});
