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

var sp = sp || {};

var spineSceneIdx = -1;
var SpineTestScene = TestScene.extend({
    runThisTest:function () {
        var layer = SpineTestScene.nextSpineTestLayer();
        this.addChild(layer);
        director.runScene(this);
    }
});

SpineTestScene.nextSpineTestLayer = function() {
    spineSceneIdx++;
    var layers = SpineTestScene.testLayers;
    spineSceneIdx = spineSceneIdx % layers.length;
    return new layers[spineSceneIdx](spineSceneIdx);
};

SpineTestScene.backSpineTestLayer = function() {
    spineSceneIdx--;
    var layers = SpineTestScene.testLayers;
    if(spineSceneIdx < 0)
        spineSceneIdx = layers.length - 1;
    return new layers[spineSceneIdx](spineSceneIdx);
};

SpineTestScene.restartSpineTestLayer = function(){
    return new SpineTestScene.testLayers[spineSceneIdx](spineSceneIdx);
};

var SpineTestLayer = BaseTestLayer.extend({
    onRestartCallback: function(sender){
        var s = new SpineTestScene();
        s.addChild(SpineTestScene.restartSpineTestLayer());
        cc.director.runScene(s);
    },

    onNextCallback: function(sender){
        var s = new SpineTestScene();
        s.addChild(SpineTestScene.nextSpineTestLayer());
        cc.director.runScene(s);
    },

    onBackCallback: function(sender){
        var s = new SpineTestScene();
        s.addChild(SpineTestScene.backSpineTestLayer());
        cc.director.runScene(s);
    }
});

var customSkeletonAnimation = sp.SkeletonAnimation.extend({
    ctor:function () {
        this._super.apply(this, arguments);
    }
});

var SpineTestLayerNormal = SpineTestLayer.extend({
    _spineboy:null,
    _debugMode: 0,
    _flipped: false,
    _idx:0,
    ctor:function (idx) {
        this._super(cc.color(0,0,0,255), cc.color(98,99,117,255));
        this._idx = idx;

        var size = director.getWinSize();

        /////////////////////////////
        // Make Spine's Animated skeleton Node
        // You need 'json + atlas + image' resource files to make it.
        var spineBoy = sp.SkeletonAnimation.createWithJsonFile('spine/spineboy-ess.json', 'spine/spineboy.atlas', 0.6);
        spineBoy.setPosition(cc.p(size.width / 2, size.height / 2 - 150));
        spineBoy.setMix('walk', 'jump', 0.2);
        spineBoy.setMix('jump', 'run', 0.2);
        spineBoy.setAnimation(0, 'walk', true);
        //spineBoy.setAnimationListener(this, this.animationStateEvent);
        spineBoy.setScale(0.5);
        this.addChild(spineBoy, 4);
        this._spineboy = spineBoy;
        spineBoy.setStartListener(function(trackEntry){
            if(trackEntry){
                var animationName = trackEntry.animation ? trackEntry.animation.name : "";
                cc.log("%d start: %s", trackEntry.trackIndex, animationName);
            }
        });
        spineBoy.setEndListener(function(trackEntry){
            cc.log("%d end.", trackEntry.trackIndex);
        });
        spineBoy.setCompleteListener(function(trackEntry){
            var loopCount = Math.floor(trackEntry.trackTime / trackEntry.animationEnd);
            cc.log("%d complete: %d", trackEntry.trackIndex, loopCount);
        });
        spineBoy.setEventListener(function(trackEntry, event){
            cc.log( trackEntry.trackIndex + " event: %s, %d, %d, %s",event.data.name, event.intValue, event.floatValue, event.stringValue);
        });

        var jumpEntry = spineBoy.addAnimation(0, "jump", false, 3);
        spineBoy.addAnimation(0, "run", true);
        // spineBoy.setTrackStartListener(jumpEntry, function(traceIndex){
        //     cc.log("jumped!");
        // });

        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesBegan: function(touches, event){
                if(spineBoy.getTimeScale() === 1.0)
                    spineBoy.setTimeScale(0.3);
                else
                    spineBoy.setTimeScale(1);
            }
        }, this);

        cc.MenuItemFont.setFontSize(20);
        var bonesToggle = new cc.MenuItemToggle(
            new cc.MenuItemFont("Debug Bones: Off"),
            new cc.MenuItemFont("Debug Bones: On"));
        bonesToggle.setCallback(this.onDebugBones, this);
        bonesToggle.setPosition(160 - size.width / 2, 120 - size.height / 2);
        var slotsToggle = new cc.MenuItemToggle(
            new cc.MenuItemFont("Debug Slots: Off"),
            new cc.MenuItemFont("Debug Slots: On"));
        slotsToggle.setCallback(this.onDebugSlots, this);
        slotsToggle.setPosition(160 - size.width / 2, 160 - size.height / 2);
        var menu = new cc.Menu();
        menu.ignoreAnchorPointForPosition(true);
        menu.addChild(bonesToggle);
        menu.addChild(slotsToggle);
        this.addChild(menu, 5);
    },

    onDebugBones: function(sender){
        this._spineboy.setDebugBonesEnabled(!this._spineboy.getDebugBonesEnabled());
    },

    onDebugSlots: function(sender){
        this._spineboy.setDebugSlotsEnabled(!this._spineboy.getDebugSlotsEnabled());
    },

    subtitle:function () {
        if (this._idx % 2 == 0) {
            return "custom spine test";
        }
        else {
            return "Spine test";
        }
        
    },
    title:function () {
        return "Spine test";
    },

    animationStateEvent: function(obj, trackIndex, type, event, loopCount) {
        var entry = this._spineboy.getCurrent();
        var animationName = (entry && entry.animation) ? entry.animation.name : 0;
        switch(type) {
            case sp.ANIMATION_EVENT_TYPE.START:
                cc.log(trackIndex + " start: " + animationName);
                break;
            case sp.ANIMATION_EVENT_TYPE.END:
                cc.log(trackIndex + " end:" + animationName);
                break;
            case sp.ANIMATION_EVENT_TYPE.EVENT:
                cc.log(trackIndex + " event: " + animationName);
                break;
            case sp.ANIMATION_EVENT_TYPE.COMPLETE:
                cc.log(trackIndex + " complete: " + animationName + "," + loopCount);
                if(this._flipped){
                    this._flipped = false;
                    this._spineboy.setScaleX(0.5);
                }else{
                    this._flipped = true;
                    this._spineboy.setScaleX(-0.5);
                }
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

var SpineTestLayerFFD = SpineTestLayer.extend({
    ctor: function(){
        this._super(cc.color(0,0,0,255), cc.color(98,99,117,255));

        var skeletonNode = sp.SkeletonAnimation.createWithJsonFile("spine/goblins-pro.json", "spine/goblins.atlas", 1.5);
        skeletonNode.setAnimation(0, "walk", true);
        skeletonNode.setSkin("goblin");

        skeletonNode.setScale(0.5);
        var winSize = cc.director.getWinSize();
        skeletonNode.setPosition(winSize.width /2, 20);
        this.addChild(skeletonNode);

        var listener = cc.EventListener.create({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            onTouchBegan : function(touch, event){
                if(!skeletonNode.getDebugBonesEnabled())
                    skeletonNode.setDebugBonesEnabled(true);
                else if(skeletonNode.getTimeScale() === 1.0)
                    skeletonNode.setTimeScale(0.3);
                else{
                    skeletonNode.setTimeScale(1);
                    skeletonNode.setDebugBonesEnabled(false);
                }
                return true;
            }
        });
        cc.eventManager.addListener(listener, this);
    },

    title: function(){
       return "Spine Test";
    },

    subtitle: function(){
        return "FFD Spine";
    }
});

var SpineTestPerformanceLayer = SpineTestLayer.extend({
    ctor: function(){
        this._super(cc.color(0,0,0,255), cc.color(98,99,117,255));

        var self = this;
        var listener = cc.EventListener.create({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            onTouchBegan: function(touch, event){
                var pos = self.convertToNodeSpace(touch.getLocation());
                var skeletonNode = sp.SkeletonAnimation.createWithJsonFile("spine/goblins-pro.json", "spine/goblins.atlas", 1.5);
                skeletonNode.setAnimation(0, "walk", true);
                skeletonNode.setSkin("goblin");

                skeletonNode.setScale(0.2);
                skeletonNode.setPosition(pos);
                self.addChild(skeletonNode);
                return true;
            }
        });
        cc.eventManager.addListener(listener, this);
    },
    title: function(){
        return "Spine Test";
    },
    subtitle: function() {
        return "Performance Test for Spine";
    }
});

SpineTestScene.testLayers = [
    SpineTestLayerNormal,
    //SpineTestLayerNormal // custom spine,diff code in sample
    //SpineTestLayerFFD,        //it doesn't support mesh on Canvas.
    //SpineTestPerformanceLayer //it doesn't support mesh on Canvas.
];

if(cc.sys.isNative || cc._renderType === cc.game.RENDER_TYPE_WEBGL){
    SpineTestScene.testLayers.push(SpineTestLayerFFD);
    SpineTestScene.testLayers.push(SpineTestPerformanceLayer);
}
