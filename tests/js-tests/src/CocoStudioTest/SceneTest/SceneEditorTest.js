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

var sceneTestIdx = -1;

var SceneEditorScene = TestScene.extend({
    onEnter: function () {
        this._super();
    },
    runThisTest: function () {
        sceneTestIdx = -1;
        this.addChild(nextSceneEditorTest());
        director.runScene(this);
    },
    onMainMenuCallback: function () {
        var scene = new CocoStudioTestScene();
        scene.runThisTest();
    },
    onExit: function () {
        this._super();
    }
});
var sceneEditorArr = [
    function () {
        return new LoadSceneEdtiorFileTest();
    },
    function () {
        return new SpriteComponentTest();
    },
    function () {
        return new ArmatureComponentTest();
    },
    function () {
        return new UIComponentTest();
    },
    function () {
        return new TmxMapComponentTest();
    },
    function () {
        return new ParticleComponentTest();
    },
    function () {
        return new EffectComponentTest();
    },
    function () {
        return new BackgroundComponentTest();
    },
    function () {
        return new AttributeComponentTest();
    },
    function () {
        return new TriggerTest();
    }
];

var nextSceneEditorTest = function () {
    sceneTestIdx++;
    sceneTestIdx = sceneTestIdx % sceneEditorArr.length;
    return sceneEditorArr[sceneTestIdx]();
};

var backSceneEditorTest = function () {
    sceneTestIdx--;
    if (sceneTestIdx < 0)
        sceneTestIdx += sceneEditorArr.length;

    return sceneEditorArr[sceneTestIdx]();
};

var restartSceneEditorTest = function () {
    return sceneEditorArr[sceneTestIdx]();
};
var SceneEditorTestLayer = BaseTestLayer.extend({
    ctor: function () {
        if (arguments.length === 0) {
            this._super(cc.color(0, 0, 0, 255), cc.color(98, 99, 117, 255));
        } else {
            this._super.apply(this, arguments);
        }
    },

    onRestartCallback: function (sender) {
        var s = new SceneEditorScene();
        s.addChild(restartSceneEditorTest());
        director.runScene(s);
    },

    onNextCallback: function (sender) {
        var s = new SceneEditorScene();
        s.addChild(nextSceneEditorTest());
        director.runScene(s);
    },

    onBackCallback: function (sender) {
        var s = new SceneEditorScene();
        s.addChild(backSceneEditorTest());
        director.runScene(s);
    },
    onExit: function () {
        ccs.armatureDataManager.clear();
        ccs.sceneReader.clear();
        ccs.actionManager.clear();
        ccs.uiReader.clear();
        this._super();
    },
    initSize:function(node){
        var winSize = cc.director.getWinSize();
        var scale = winSize.height / 320;
        node.scale = scale;
        node.x = (winSize.width - 480 * scale) / 2;
	    node.y = (winSize.height - 320 * scale) / 2;
    }
});

var runSceneEditorTest = function () {
    var pScene = new SceneEditorScene();
    if (pScene) {
        pScene.runThisTest();
    }
};

//------------------------------------------------------------------
//
// LoadSceneEdtiorFileTest
//
//------------------------------------------------------------------
var LoadSceneEdtiorFileTest = SceneEditorTestLayer.extend({
    onEnter: function () {
        this._super();
        var node,
            file = "ccs-res/scenetest/LoadSceneEdtiorFileTest/FishJoy2.json";
        if(cocoStudioOldApiFlag == 0){
            cc.log("ccs.load : %s", file);
            var json = ccs.load(file);
            node = json.node;
        }else{
            //ccs.sceneReader only supports 1.x file
            cc.log("ccs.sceneReader.createNodeWithSceneFile : %s", file);
            node = ccs.sceneReader.createNodeWithSceneFile(file);
        }
        this.addChild(node);
        ccs.actionManager.playActionByName("startMenu_1.json", "Animation1");
        this.initSize(node);
    },
    onExit: function() {
        ccs.actionManager.releaseActions();
        this._super();
    },
    title: function () {
        return "loadSceneEdtiorFile Test";
    }
});

//------------------------------------------------------------------
//
// SpriteComponentTest
//
//------------------------------------------------------------------
var SpriteComponentTest = SceneEditorTestLayer.extend({
    onEnter: function () {
        this._super();
        var node,
            file = "ccs-res/scenetest/SpriteComponentTest/SpriteComponentTest.json";
        if(cocoStudioOldApiFlag == 0){
            cc.log("ccs.load : %s", file);
            var json = ccs.load(file);
            node = json.node;
        }else{
            //ccs.sceneReader only supports 1.x file
            cc.log("ccs.sceneReader.createNodeWithSceneFile : %s", file);
            node = ccs.sceneReader.createNodeWithSceneFile(file);
        }
        this.addChild(node);

        var action1 = cc.blink(2, 10);
        var action2 = cc.blink(2, 5);
        var sister1 = node.getChildByTag(10003).getComponent("CCSprite").getNode();
        sister1.runAction(action1);

        var sister2 = node.getChildByTag(10004).getComponent("CCSprite").getNode();
        sister2.runAction(action2);

        this.initSize(node);
    },
    title: function () {
        return "Sprite Component Test";
    }
});

//------------------------------------------------------------------
//
// ArmatureComponentTest
//
//------------------------------------------------------------------
var ArmatureComponentTest = SceneEditorTestLayer.extend({
    onEnter: function () {
        this._super();
        var node,
            file = "ccs-res/scenetest/ArmatureComponentTest/ArmatureComponentTest.json";
        if(cocoStudioOldApiFlag == 0){
            cc.log("ccs.load : %s", file);
            var json = ccs.load(file);
            node = json.node;ccs.load(file);
        }else{
            //ccs.sceneReader only supports 1.x file
            cc.log("ccs.sceneReader.createNodeWithSceneFile : %s", file);
            node = ccs.sceneReader.createNodeWithSceneFile(file);
        }
        this.addChild(node);

        var blowFish = node.getChildByTag(10007).getComponent("CCArmature").getNode();
        blowFish.runAction(cc.moveBy(10, cc.p(-1000, 0)));

        var butterFlyFish = node.getChildByTag(10008).getComponent("CCArmature").getNode();
        butterFlyFish.runAction(cc.moveBy(10, cc.p(-1000, 0)));

        this.initSize(node);
    },
    title: function () {
        return "Armature Component Test";
    }
});

//------------------------------------------------------------------
//
// UIComponentTest
//
//------------------------------------------------------------------
var UIComponentTest = SceneEditorTestLayer.extend({
    _node: null,
    onEnter: function () {
        this._super();
        var node,
            file = "ccs-res/scenetest/UIComponentTest/UIComponentTest.json";
        if(cocoStudioOldApiFlag == 0){
            cc.log("ccs.load : %s", file);
            var json = ccs.load(file);
            node = json.node;
        }else{
            //ccs.sceneReader only supports 1.x file
            cc.log("ccs.sceneReader.createNodeWithSceneFile : %s", file);
            node = ccs.sceneReader.createNodeWithSceneFile(file);
        }
        this._node = node;
        this.addChild(this._node);
        var widget = this._node.getChildByTag(10025).getComponent("GUIComponent").getNode();
        var button = widget.getChildByName("Button_156");
        button.addTouchEventListener(this.touchEvent, this);

        this.initSize(this._node);
    },
    touchEvent: function (sender, type) {
        switch (type) {
            case ccui.Widget.TOUCH_BEGAN:
                var blowFish = this._node.getChildByTag(10010).getComponent("CCArmature").getNode();
                blowFish.runAction(cc.moveBy(10, cc.p(-1000, 0)));

                var butterFlyFish = this._node.getChildByTag(10011).getComponent("CCArmature").getNode();
                butterFlyFish.runAction(cc.moveBy(10, cc.p(-1000.0, 0)));
                break;
            default:
                break;
        }
    },
    title: function () {
        return "UI Component Test";
    }
});

//------------------------------------------------------------------
//
// TmxMapComponentTest
//
//------------------------------------------------------------------
var TmxMapComponentTest = SceneEditorTestLayer.extend({
    onEnter: function () {
        this._super();
        var node,
            file = "ccs-res/scenetest/TmxMapComponentTest/TmxMapComponentTest.json";
        if(cocoStudioOldApiFlag == 0){
            cc.log("ccs.load : %s", file);
            var json = ccs.load(file);
            node = json.node;
        }else{
            //ccs.sceneReader only supports 1.x file
            cc.log("ccs.sceneReader.createNodeWithSceneFile : %s", file);
            node = ccs.sceneReader.createNodeWithSceneFile(file);
        }
        this.addChild(node);
        var tmxMap = node.getChildByTag(10015).getComponent("CCTMXTiledMap").getNode();
        var actionTo = cc.skewTo(2, 0, 2);
        var rotateTo = cc.rotateTo(2, 61);
        var actionScaleTo = cc.scaleTo(2, -0.44, 0.47);

        var actionScaleToBack = cc.scaleTo(2, 1, 1);
        var rotateToBack = cc.rotateTo(2, 0);
        var actionToBack = cc.skewTo(2, 0, 0);

        tmxMap.runAction(cc.sequence(actionTo, actionToBack));
        tmxMap.runAction(cc.sequence(rotateTo, rotateToBack));
        tmxMap.runAction(cc.sequence(actionScaleTo, actionScaleToBack));

        this.initSize(node);
    },
    title: function () {
        return "TmxMap Component Test";
    }
});


//------------------------------------------------------------------
//
// ParticleComponentTest
//
//------------------------------------------------------------------
var ParticleComponentTest = SceneEditorTestLayer.extend({
    onEnter: function () {
        this._super();
        var node,
            file = "ccs-res/scenetest/ParticleComponentTest/ParticleComponentTest.json";
        if(cocoStudioOldApiFlag == 0){
            cc.log("ccs.load : %s", file);
            var json = ccs.load(file);
            node = json.node;
        }else{
            //ccs.sceneReader only supports 1.x file
            cc.log("ccs.sceneReader.createNodeWithSceneFile : %s", file);
            node = ccs.sceneReader.createNodeWithSceneFile(file);
        }
        this.addChild(node);

        var particle = node.getChildByTag(10020).getComponent("CCParticleSystemQuad").getNode();
        var jump = cc.jumpBy(5, cc.p(-500, 0), 50, 4);
        var action = cc.sequence(jump, jump.reverse());
        particle.runAction(action);

        this.initSize(node);
    },
    title: function () {
        return "Particle Component Test";
    }
});

//------------------------------------------------------------------
//
// EffectComponentTest
//
//------------------------------------------------------------------
var EffectComponentTest = SceneEditorTestLayer.extend({
    _node: null,
    onEnter: function () {
        this._super();
        var node,
            file = "ccs-res/scenetest/EffectComponentTest/EffectComponentTest.json";
        if(cocoStudioOldApiFlag == 0){
            cc.log("ccs.load : %s", file);
            var json = ccs.load(file);
            node = json.node;
        }else{
            //ccs.sceneReader only supports 1.x file
            cc.log("ccs.sceneReader.createNodeWithSceneFile : %s", file);
            node = ccs.sceneReader.createNodeWithSceneFile(file);
        }
        this._node = node;
        this.addChild(this._node);

        var armature = this._node.getChildByTag(10015).getComponent("CCArmature").getNode();
        armature.getAnimation().setMovementEventCallFunc(this.animationEvent, this);

        this.initSize(this._node);
    },
    title: function () {
        return "Effect Component Test";
    },
    animationEvent: function (armature, movementType, movementID) {
        if (movementType == ccs.MovementEventType.loopComplete) {
            if (movementID == "Fire") {
                var audio = this._node.getChildByTag(10015).getComponent("CCComAudio");
                audio.playEffect();
            }
        }
    }
});

//------------------------------------------------------------------
//
// BackgroundComponentTest
//
//------------------------------------------------------------------
var BackgroundComponentTest = SceneEditorTestLayer.extend({
    onEnter: function () {
        this._super();
        var node,
            file = "ccs-res/scenetest/BackgroundComponentTest/BackgroundComponentTest.json";
        if(cocoStudioOldApiFlag == 0){
            cc.log("ccs.load : %s", file);
            var json = ccs.load(file);
            node = json.node;
        }else{
            //ccs.sceneReader only supports 1.x file
            cc.log("ccs.sceneReader.createNodeWithSceneFile : %s", file);
            node = ccs.sceneReader.createNodeWithSceneFile(file);
        }
        this.addChild(node);
        ccs.actionManager.playActionByName("startMenu_1.json", "Animation1");

        var audio = node.getComponent("CCBackgroundAudio");
        audio.playBackgroundMusic();

        this.initSize(node);
    },
    onExit: function() {
        ccs.actionManager.releaseActions();
        this._super();
    },
    title: function () {
        return "Background Component Test";
    }
});

//------------------------------------------------------------------
//
// AttributeComponentTest
//
//------------------------------------------------------------------
var AttributeComponentTest = SceneEditorTestLayer.extend({
    onEnter: function () {
        this._super();
        var node,
            file = "ccs-res/scenetest/AttributeComponentTest/AttributeComponentTest.json";
        if(cocoStudioOldApiFlag == 0){
            cc.log("ccs.load : %s", file);
            var json = ccs.load(file);
            node = json.node;
        }else{
            //ccs.sceneReader only supports 1.x file
            cc.log("ccs.sceneReader.createNodeWithSceneFile : %s", file);
            node = ccs.sceneReader.createNodeWithSceneFile(file);
        }
        this.addChild(node);

        var comAttribute = node.getChildByTag(10015).getComponent("CCComAttribute");
        cc.log("name:" + comAttribute.getString("name"));
        cc.log("maxHP:" + comAttribute.getFloat("maxHP"));
        cc.log("maxMP:" + comAttribute.getFloat("maxMP"));

        this.initSize(node);
    },
    title: function () {
        return "Attribute Component Test";
    },
    subtitle:function(){
        return "See console";
    }
});

//------------------------------------------------------------------
//
// TriggerTest
//
//------------------------------------------------------------------
var TriggerTest = SceneEditorTestLayer.extend({
    _blowFishNode: null,
    _flyFishNode: null,
    onEnter: function () {
        this._super();
        var node,
            file = "ccs-res/scenetest/TriggerTest/TriggerTest.json";
        if(cocoStudioOldApiFlag == 0){
            cc.log("ccs.load : %s", file);
            var json = ccs.load(file);
            node = json.node;
        }else{
            //ccs.sceneReader only supports 1.x file
            cc.log("ccs.sceneReader.createNodeWithSceneFile : %s", file);
            node = ccs.sceneReader.createNodeWithSceneFile(file);
        }
        this.addChild(node);
        ccs.actionManager.playActionByName("startMenu_1.json", "Animation1");

        this.schedule(this.gameLogic);
        ccs.sendEvent(TRIGGER_EVENT_ENTERSCENE);

        var listener1 = cc.EventListener.create({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches: true,
            onTouchBegan: this.onTouchBegan.bind(this),
            onTouchMoved: this.onTouchMoved.bind(this),
            onTouchEnded: this.onTouchEnded.bind(this)
        });
        cc.eventManager.addListener(listener1, this);
        this.initSize(node);
    },
    onExit: function () {
        ccs.actionManager.releaseActions();
        ccs.sendEvent(TRIGGER_EVENT_LEAVESCENE);
        this.unschedule(this.gameLogic, this);
        this._super();
    },

    onTouchBegan: function (touch, event) {
        ccs.sendEvent(TRIGGER_EVENT_TOUCHBEGAN);
        return true;
    },

    onTouchMoved: function (touch, event) {
        ccs.sendEvent(TRIGGER_EVENT_TOUCHMOVED);
    },

    onTouchEnded: function (touch, event) {
        ccs.sendEvent(TRIGGER_EVENT_TOUCHENDED);
    },

    onTouchCancelled: function (touch, event) {
        ccs.sendEvent(TRIGGER_EVENT_TOUCHCANCELLED);
    },

    gameLogic: function () {
        ccs.sendEvent(TRIGGER_EVENT_UPDATESCENE);
    },
    title: function () {
        return "Trigger Test";
    }
});
