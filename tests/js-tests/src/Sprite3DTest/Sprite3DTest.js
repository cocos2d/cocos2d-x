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
var Sprite3DTestIdx = -1;

var Sprite3DTestDemo = cc.Layer.extend({
    _title:"",
    _subtitle:"",

    ctor:function () {
        this._super();
    },

    //
    // Menu
    //
    onEnter:function () {
        this._super();

        var label = new cc.LabelTTF(this._title, "Arial", 28);
        this.addChild(label, 100, BASE_TEST_TITLE_TAG);
        label.x = winSize.width / 2;
        label.y = winSize.height - 50;

        var label2 = new cc.LabelTTF(this._subtitle, "Thonburi", 16);
        this.addChild(label2, 101, BASE_TEST_SUBTITLE_TAG);
        label2.x = winSize.width / 2;
        label2.y = winSize.height - 80;

        var item1 = new cc.MenuItemImage(s_pathB1, s_pathB2, this.onBackCallback, this);
        var item2 = new cc.MenuItemImage(s_pathR1, s_pathR2, this.onRestartCallback, this);
        var item3 = new cc.MenuItemImage(s_pathF1, s_pathF2, this.onNextCallback, this);

        item1.tag = BASE_TEST_MENUITEM_PREV_TAG;
        item2.tag = BASE_TEST_MENUITEM_RESET_TAG;
        item3.tag = BASE_TEST_MENUITEM_NEXT_TAG;

        var menu = new cc.Menu(item1, item2, item3);

        menu.x = 0;
        menu.y = 0;
        var width = item2.width, height = item2.height;
        item1.x =  winSize.width/2 - width*2;
        item1.y = height/2 ;
        item2.x =  winSize.width/2;
        item2.y = height/2 ;
        item3.x =  winSize.width/2 + width*2;
        item3.y = height/2 ;

        this.addChild(menu, 102, BASE_TEST_MENU_TAG);
    },

    onRestartCallback:function (sender) {
        var s = new Sprite3DTestScene();
        s.addChild(restartSprite3DTest());
        director.runScene(s);
    },

    onNextCallback:function (sender) {
        var s = new Sprite3DTestScene();
        s.addChild(nextSprite3DTest());
        director.runScene(s);
    },

    onBackCallback:function (sender) {
        var s = new Sprite3DTestScene();
        s.addChild(previousSprite3DTest());
        director.runScene(s);
    },
});

var Sprite3DTestScene = cc.Scene.extend({
    ctor:function () {
        this._super();

        var label = new cc.LabelTTF("Main Menu", "Arial", 20);
        var menuItem = new cc.MenuItemLabel(label, this.onMainMenuCallback, this);

        var menu = new cc.Menu(menuItem);
        menu.x = 0;
        menu.y = 0;
        menuItem.x = winSize.width - 50;
        menuItem.y = 25;
        this.addChild(menu);
    },
    onMainMenuCallback:function () {
        var scene = new cc.Scene();
        var layer = new TestController();
        scene.addChild(layer);
        director.runScene(scene);
    },
    runThisTest:function (num) {
        Sprite3DTestIdx = (num || num == 0) ? (num - 1) : -1;
        var layer = nextSprite3DTest();
        this.addChild(layer);

        director.runScene(this);
    }
});


var Sprite3DBasicTest = Sprite3DTestDemo.extend({
    _title: "Testing Sprite3D",
    _subtitle: "Tap screen to add more sprites",

    ctor:function(){
        this._super();

        var winSize = cc.winSize;
        this.addNewSpriteWithCoords(cc.p(winSize.width/2, winSize.height/2));

        var that = this;
        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesEnded: function(touches, event){
                for(var i in touches){
                    that.addNewSpriteWithCoords(touches[i].getLocation());
                }
            }
        }, this);
    },

    addNewSpriteWithCoords:function(position){
        var sprite = new jsb.Sprite3D("Sprite3DTest/boss1.obj");
        sprite.setScale(3.0);
        sprite.setTexture("Sprite3DTest/boss.png");
        sprite.x = position.x;
        sprite.y = position.y;

        this.addChild(sprite);

        var action;
        var random = Math.random();
        if(random < 0.2)
            action = cc.scaleBy(3, 2);
        else if(random < 0.4)
            action = cc.rotateBy(3, 360);
        else if(random < 0.6)
            action = cc.blink(1, 3);
        else if(random < 0.8)
            action = cc.tintBy(2, 0, -255, -255);
        else
            action = cc.fadeOut(2);

        var action_back = action.reverse();
        var seq = cc.sequence(action, action_back);

        sprite.runAction(seq.repeatForever());
    }
});

var Sprite3DHitTest = Sprite3DTestDemo.extend({
    _title:"Testing Sprite3D Touch in 2D",
    _subtitle:"Tap Sprite3D and Drag",

    ctor:function(){
        this._super();

        var s = cc.winSize;

        var sprite1 = new jsb.Sprite3D("Sprite3DTest/boss1.obj");
        sprite1.setScale(4.0);
        sprite1.setTexture("Sprite3DTest/boss.png");
        sprite1.setPosition(cc.p(s.width/2, s.height/2));

        this.addChild(sprite1);
        sprite1.runAction(cc.rotateBy(3, 360).repeatForever());

        var sprite2 = new jsb.Sprite3D("Sprite3DTest/boss1.obj")
        sprite2.setScale(4.0);
        sprite2.setTexture("Sprite3DTest/boss.png");
        sprite2.setPosition(cc.p(s.width/2, s.height/2));
        sprite2.setAnchorPoint(cc.p(0.5, 0.5));

        this.addChild(sprite2);
        sprite2.runAction(cc.rotateBy(3, -360).repeatForever());

        // Make sprite1 touchable
        var listener1 = cc.EventListener.create({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches: true,
            onTouchBegan: function (touch, event) {
                var target = event.getCurrentTarget();
                var rect = target.getBoundingBox();
                if(cc.rectContainsPoint(rect, touch.getLocation())){
                    cc.log("sprite3d began... x = " + touch.getLocation().x + ", y = " + touch.getLocation().y);
                    target.setOpacity(100);
                    return true;
                }
                return false;
            },
            onTouchMoved: function (touch, event) {
                var target = event.getCurrentTarget();
                var oldPos = target.getPosition();
                var delta = touch.getDelta();
                target.setPosition(cc.p(oldPos.x + delta.x, oldPos.y + delta.y));
            },
            onTouchEnded: function (touch, event) {
                var target = event.getCurrentTarget();
                cc.log("sprite3d onTouchEnded...");
                target.setOpacity(255);
            }
        });
        cc.eventManager.addListener(listener1, sprite1);
        cc.eventManager.addListener(listener1.clone(), sprite2);
    }
});

var AsyncLoadSprite3DTest = Sprite3DTestDemo.extend({
    _title:"Testing Sprite3D::createAsync",
    _subtitle:"",
    _path:["Sprite3DTest/boss.obj", "Sprite3DTest/girl.c3b", "Sprite3DTest/orc.c3b", "Sprite3DTest/ReskinGirl.c3b", "Sprite3DTest/axe.c3b"],
    
    ctor:function(){
        this._super();

        var label = new cc.LabelTTF("AsyncLoad Sprite3D", "Arial", 15);
        var item = new cc.MenuItemLabel(label, this.menuCallback_asyncLoadSprite, this);

        var s = cc.winSize;
        item.setPosition(s.width / 2, s.height / 2);

        var menu = new cc.Menu(item);
        menu.setPosition(cc.p(0, 0));
        this.addChild(menu, 10);

        var node = new cc.Node();
        node.setTag(101);
        this.addChild(node);

        this.menuCallback_asyncLoadSprite();

        this.asyncPool = null;
    },

    menuCallback_asyncLoadSprite:function(sender){
        if (!this.asyncPool) {
            this.asyncPool = cc.AsyncTaskPool.getInstance();
        }
        //Note that you must stop the tasks before leaving the scene.
        this.asyncPool.stopTasks(cc.AsyncTaskPool.TaskType.TASK_IO);

        var node = this.getChildByTag(101);
        node.removeAllChildren(); // remove all loaded sprites

        //remove cache data
        jsb.sprite3DCache.removeAllSprite3DData();

        for(var i = 0; i < this._path.length; ++i){
            jsb.Sprite3D.createAsync(this._path[i], this.asyncLoad_Callback, this, i);
        }
    },

    asyncLoad_Callback:function(sprite, data){
        var node = this.getChildByTag(101);
        var s = cc.winSize;
        var width = s.width / this._path.length;
        sprite.setPosition(width * (0.5 + data), s.height / 2);
        node.addChild(sprite);
    }
});

var Sprite3DWithSkinTest = Sprite3DTestDemo.extend({
    _title:"Testing Sprite3D",
    _subtitle:"Tap screen to add more sprite3D",
    
    ctor:function(){
        this._super();

        var size = cc.winSize;
        this.addNewSpriteWithCoords(cc.p(size.width/2, size.height/2));

        var that = this;
        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesEnded: function(touches, event){
                for(var i in touches){
                    that.addNewSpriteWithCoords(touches[i].getLocation());
                }
            }
        }, this);
    },

    addNewSpriteWithCoords:function(position){
        var sprite = new jsb.Sprite3D("Sprite3DTest/orc.c3b");
        sprite.setScale(3);
        sprite.setRotation3D({x : 0, y : 180, z: 0});
        this.addChild(sprite);
        sprite.setPosition(position);

        var animation = new jsb.Animation3D("Sprite3DTest/orc.c3b");
        if(animation){
            var animate = new jsb.Animate3D(animation);
            var inverse = Math.random() < 0.33 ? true : false;

            var rand2 = Math.random();
            var speed = 1.0;
            if(rand2 < 0.33)
                speed = animate.getSpeed() + Math.random();
            else if(rand2 < 0.66)            
                speed = animate.getSpeed() - 0.5 * Math.random();

            animate.setSpeed(inverse ? -speed : speed);
            sprite.runAction(new cc.RepeatForever(animate));
        }
    }
});

var Animate3DTest = (function(){

    var State = {
        SWIMMING : 0,
        SWIMMING_TO_HURT : 1,
        HURT : 2,
        HURT_TO_SWIMMING : 3
    };

    return Sprite3DTestDemo.extend({
        _title:"Testing Animate3D",
        _subtitle:"Touch to beat the tortoise",
        _sprite:null,
        _swim:null,
        _hurt:null,
        _moveAction:null,
        _state:0,
        _elapseTransTime:0,

        ctor:function(){
            this._super();

            this.addSprite3D();

            cc.eventManager.addListener({
                event: cc.EventListener.TOUCH_ALL_AT_ONCE,
                onTouchesEnded: this.onTouchesEnded.bind(this)
            }, this);

            this.scheduleUpdate();
        },

        onExit:function(){
            this._super();
            this._moveAction.release();
            this._hurt.release();
            this._swim.release();
        },

        addSprite3D:function(){
            var sprite = new jsb.Sprite3D("Sprite3DTest/tortoise.c3b");
            sprite.setScale(0.1);
            var s = cc.winSize;
            sprite.setPosition(cc.p(s.width * 4 / 5, s.height / 2));
            this.addChild(sprite);
            this._sprite = sprite;

            var animation = new jsb.Animation3D("Sprite3DTest/tortoise.c3b");
            if(animation){
                var animate = new jsb.Animate3D(animation, 0, 1.933);
                this._swim = new cc.RepeatForever(animate);
                sprite.runAction(this._swim);

                this._swim.retain();
                this._hurt = new jsb.Animate3D(animation, 1.933, 2.8);
                this._hurt.retain();

                this._state = State.SWIMMING;
            }

            this._moveAction = cc.moveBy(4.0, cc.p(-s.width / 5 * 3, 0));
            this._moveAction.retain();
            var seq = cc.sequence(this._moveAction, cc.callFunc(this.reachEndCallBack, this));
            seq.setTag(100);
            sprite.runAction(seq);
        },

        reachEndCallBack:function(sender){
            var sprite = this._sprite;
            sprite.stopActionByTag(100);
            var inverse = this._moveAction.reverse();
            inverse.retain();
            this._moveAction.release();
            this._moveAction = inverse;
            var rot = cc.rotateBy(1, {x : 0, y : 180, z : 0});
            var seq = cc.sequence(rot, this._moveAction, cc.callFunc(this.reachEndCallBack, this));
            seq.setTag(100);
            sprite.runAction(seq);
        },

        renewCallBack:function(){
            this._sprite.runAction(this._swim);
            this._state = State.HURT_TO_SWIMMING;
            this._elapseTransTime = 0.0;
        },

        onTouchesEnded:function(touches, event){
            for(var i in touches){
                var location = touches[i].getLocation();

                if(this._sprite){
                    var len = cc.pDistance(this._sprite.getPosition(), location);

                    if(len < 40){
                        //hurt the tortoise
                        if(this._state == State.SWIMMING){
                            this._elapseTransTime = 0;
                            this._state = State.SWIMMING_TO_HURT;
                            this._sprite.stopAction(this._hurt);
                            this._sprite.runAction(this._hurt);
                            var delay = cc.delayTime(this._hurt.getDuration() - jsb.Animate3D.getTransitionTime());
                            var seq = cc.sequence(delay, cc.callFunc(this.renewCallBack, this));
                            seq.setTag(101);
                            this._sprite.runAction(seq);
                        }
                    }
                }
            }
        },

        update:function(dt){
            if(this._state == State.HURT_TO_SWIMMING){
                this._elapseTransTime += dt;

                if(this._elapseTransTime >= jsb.Animate3D.getTransitionTime()){
                    this._sprite.stopAction(this._hurt);
                    this._state = State.SWIMMING;
                }
            }else if(this._state == State.SWIMMING_TO_HURT){
                this._elapseTransTime += dt;

                if(this._elapseTransTime >= jsb.Animate3D.getTransitionTime()){
                    this._sprite.stopAction(this._swim);
                    this._state = State.HURT;
                }
            }
        }
    });
})();


var AttachmentTest = Sprite3DTestDemo.extend({
    _title:"Testing Sprite3D Attachment",
    _subtitle:"touch to switch weapon",
    _hasWeapon:false,
    _sprite:null,

    ctor:function(){
        this._super();

        var s = cc.winSize;
        this.addNewSpriteWithCoords(cc.p(s.width/2, s.height/2));

        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesEnded: this.onTouchesEnded.bind(this)
        }, this);
    },

    addNewSpriteWithCoords:function(position){
        var sprite = new jsb.Sprite3D("Sprite3DTest/orc.c3b");
        sprite.setScale(5);
        sprite.setRotation3D(cc.math.vec3(0, 180, 0));
        this.addChild(sprite);
        sprite.setPosition(position);

        //test attach
        var sp = new jsb.Sprite3D("Sprite3DTest/axe.c3b");
        sprite.getAttachNode("Bip001 R Hand").addChild(sp);

        var animation = new jsb.Animation3D("Sprite3DTest/orc.c3b");
        if(animation){
            var animate = new jsb.Animate3D(animation);
            sprite.runAction(cc.repeatForever(animate));
        }

        this._sprite = sprite;
        this._hasWeapon = true;
    },

    onTouchesEnded:function(touches, event){
        if(this._hasWeapon){
            this._sprite.removeAllAttachNode();
        }else{
            var sp = new jsb.Sprite3D("Sprite3DTest/axe.c3b");
            this._sprite.getAttachNode("Bip001 R Hand").addChild(sp);
        }
        this._hasWeapon = !this._hasWeapon;
    }
});

var Sprite3DReskinTest = (function(){
    var SkinType = {
        UPPER_BODY : 0,
        PANTS : 1,
        SHOES : 2,
        HAIR : 3,
        FACE : 4,
        HAND : 5,
        GLASSES : 6,
        MAX_TYPE : 7
    };

    return Sprite3DTestDemo.extend({
        _title:"Testing Sprite3D Reskin",
        _subtitle:"",
        _sprite:null,
        _skins:[["Girl_UpperBody01", "Girl_UpperBody02"], ["Girl_LowerBody01", "Girl_LowerBody02"], ["Girl_Shoes01", "Girl_Shoes02"], ["Girl_Hair01", "Girl_Hair02"], ["Girl_Face01", "Girl_Face02"], ["Girl_Hand01", "Girl_Hand02"], ["", "Girl_Glasses01"]],
        _curSkin:["Girl_UpperBody01", "Girl_LowerBody01", "Girl_Shoes01", "Girl_Hair01", "Girl_Face01", "Girl_Hand01", ""],

        ctor:function(){
            this._super();

            var s = cc.winSize;
            this.addNewSpriteWithCoords(cc.p(s.width/2, s.height/2));

            var label1 = new cc.LabelTTF("Hair", "Arial", 20);
            var item1 = new cc.MenuItemLabel(label1, this.menuCallback_reSkin, this );
            item1.setPosition(cc.p(50, item1.getContentSize().height * 4));
            item1.setUserData(SkinType.HAIR);

            var label2 = new cc.LabelTTF("Glasses", "Arial", 20);
            var item2 = new cc.MenuItemLabel(label2, this.menuCallback_reSkin, this);
            item2.setPosition(cc.p(50, item2.getContentSize().height * 5));
            item2.setUserData(SkinType.GLASSES);

            var label3 = new cc.LabelTTF("Coat", "Arial", 20);
            var item3 = new cc.MenuItemLabel(label3, this.menuCallback_reSkin, this);
            item3.setPosition(cc.p(50, item3.getContentSize().height * 6));
            item3.setUserData(SkinType.UPPER_BODY);

            var label4 = new cc.LabelTTF("Pants", "Arial", 20);
            var item4 = new cc.MenuItemLabel(label4, this.menuCallback_reSkin, this);
            item4.setPosition(cc.p(50, item4.getContentSize().height * 7));
            item4.setUserData(SkinType.PANTS);

            var label5 = new cc.LabelTTF("Shoes", "Arial", 20);
            var item5 = new cc.MenuItemLabel(label5, this.menuCallback_reSkin, this);
            item5.setPosition(cc.p(50, item5.getContentSize().height * 8));
            item5.setUserData(SkinType.SHOES);

            var menu = new cc.Menu(item1, item2, item3, item4, item5);
            this.addChild(menu);
            menu.setPosition(cc.p(0, 0));
        },

        addNewSpriteWithCoords:function(position){
            var sprite = new jsb.Sprite3D("Sprite3DTest/ReskinGirl.c3b");
            sprite.setScale(4);
            sprite.setRotation3D(cc.math.vec3(0, 0, 0));
            this.addChild(sprite);
            sprite.setPosition(cc.p(position.x, position.y - 60));
            var animation = new jsb.Animation3D("Sprite3DTest/ReskinGirl.c3b");
            if(animation){
                var animate = new jsb.Animate3D(animation);
                sprite.runAction(cc.repeatForever(animate));
            }
            this._sprite = sprite;

            this.applyCurSkin();
        },

        applyCurSkin:function(){
            for(var i = 0; i < this._sprite.getMeshCount(); i++){
                var mesh = this._sprite.getMeshByIndex(i);
                var isVisible = false;
                for(var j = 0; j < SkinType.MAX_TYPE; j++){
                    if(mesh.getName() == this._curSkin[j]){
                        isVisible = true;
                        break;
                    }
                }
                mesh.setVisible(isVisible);
            }
        },

        menuCallback_reSkin:function(sender){
            var index = sender.getUserData();
            if(index < SkinType.MAX_TYPE){
                var curr = (this._skins[index].indexOf(this._curSkin[index]) + 1) % this._skins[index].length;
                this._curSkin[index] = this._skins[index][curr];
            }
            this.applyCurSkin();
        }
    });
})();

var Sprite3DWithOBBPerformanceTest = Sprite3DTestDemo.extend({
    _title:"OBB Collision Performance Test",
    _subtitle:"",
    _drawOBB:null,
    _drawDebug:null,
    _sprite:null,
    _moveAction:null,
    _obbt:null,
    _obb:[],
    _labelCubeCount:null,
    _targetObbIndex:-1,

    ctor:function(){
        this._super();

        cc.eventManager.addListener({
            event:cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesBegan:this.onTouchesBegan.bind(this),
            onTouchesMoved:this.onTouchesMoved.bind(this)
        }, this);

        this.initDrawBox();
        this.addSprite();

        var s = cc.winSize;
        cc.MenuItemFont.setFontName("Arial");
        cc.MenuItemFont.setFontSize(65);
        var decrease = new cc.MenuItemFont(" - ", this.delOBBCallback, this);
        decrease.setColor(cc.color(0, 200, 20));
        var increase = new cc.MenuItemFont(" + ", this.addOBBCallback, this);
        increase.setColor(cc.color(0, 200, 20));

        var menu = new cc.Menu(decrease, increase);
        menu.alignItemsHorizontally();
        menu.setPosition(s.width / 2, s.height - 65);
        this.addChild(menu, 1);

        this._labelCubeCount = new cc.LabelTTF("0 cubes", "Arial", 30);
        this._labelCubeCount.setColor(cc.color(0, 200, 20));
        this._labelCubeCount.setPosition(cc.p(s.width / 2, s.height - 90));
        this.addChild(this._labelCubeCount);

        this.addOBBCallback();
        this.scheduleUpdate();
    },

    onExit:function(){
        this._super();
        this._moveAction.release();
    },

    update:function(){
        if(this._drawDebug !== undefined){
            this._drawDebug.clear();

            var mat = this._sprite.getNodeToWorldTransform3D();
            this._obbt.xAxis.x = mat[0];
            this._obbt.xAxis.y = mat[1];
            this._obbt.xAxis.z = mat[2];
            this._obbt.xAxis.normalize();

            this._obbt.yAxis.x = mat[4];
            this._obbt.yAxis.y = mat[5];
            this._obbt.yAxis.z = mat[6];
            this._obbt.yAxis.normalize();

            this._obbt.zAxis.x = -mat[8];
            this._obbt.zAxis.y = -mat[9];
            this._obbt.zAxis.z = -mat[10];
            this._obbt.zAxis.normalize();

            this._obbt.center = this._sprite.getPosition3D();

            var corners = cc.math.obbGetCorners(this._obbt);
            this._drawDebug.drawCube(corners, cc.color(0, 0, 255));
        }

        if(this._obb.length > 0){
            this._drawOBB.clear();
            for(var i = 0; i < this._obb.length; ++i){
                corners = cc.math.obbGetCorners(this._obb[i]);
                this._drawOBB.drawCube(corners, cc.math.obbIntersectsObb(this._obbt, this._obb[i]) ? cc.color(255, 0, 0) : cc.color(0, 255, 0));
            }
        }
    },

    initDrawBox:function(){
        this._drawOBB = new cc.DrawNode3D();
        this.addChild(this._drawOBB);
    },

    addSprite:function(){
        var  sprite = new jsb.Sprite3D("Sprite3DTest/tortoise.c3b");
        sprite.setScale(0.1);
        var s = cc.winSize;
        sprite.setPosition(cc.p(s.width * 4 / 5, s.height / 2));
        this.addChild(sprite);

        this._sprite = sprite;
        var animation = new jsb.Animation3D("Sprite3DTest/tortoise.c3b");
        if(animation){
            var animate = new jsb.Animate3D(animation);
            sprite.runAction(cc.repeatForever(animate));
        }

        this._moveAction = cc.moveBy(4, cc.p(-s.width * 3 / 5, 0));
        this._moveAction.retain();
        var seq = cc.sequence(this._moveAction, cc.callFunc(this.reachEndCallBack, this));
        seq.setTag(100);
        sprite.runAction(seq);

        var aabb = sprite.getAABB();
        this._obbt = cc.math.obb(aabb);

        this._drawDebug = new cc.DrawNode3D();
        this.addChild(this._drawDebug);
    },

    reachEndCallBack:function(){
        var sprite = this._sprite;
        sprite.stopActionByTag(100);
        var inverse = this._moveAction.reverse();
        inverse.retain();
        this._moveAction.release();
        this._moveAction = inverse;
        var rot = cc.rotateBy(1, {x : 0, y : 180, z : 0});
        var seq = cc.sequence(rot, this._moveAction, cc.callFunc(this.reachEndCallBack, this));
        seq.setTag(100);
        sprite.runAction(seq);
    },

    addOBBCallback:function(sender){
        var s = cc.winSize;
        for(var i = 0; i < 10; ++i){
            var randompos = cc.p(Math.random() * s.width, Math.random() * s.height);
            var aabb = cc.math.aabb(cc.math.vec3(-10, -10, -10), cc.math.vec3(10, 10, 10));
            var obb = cc.math.obb(aabb);
            obb.center = cc.math.vec3(randompos.x, randompos.y, 0);
            this._obb.push(obb);
        }
        this._labelCubeCount.setString(this._obb.length + " cubes");
    },

    delOBBCallback:function(sender){
        if(this._obb.length >= 10){
            this._obb.splice(0, 10);
            this._drawOBB.clear();
        }
        this._labelCubeCount.setString(this._obb.length + " cubes");
    },

    onTouchesBegan:function(touches, event){
        var location = touches[0].getLocationInView();
        var ray = this.calculateRayByLocationInView(location);
        for(var j = 0; j < this._obb.length; ++j){
            if(cc.math.rayIntersectsObb(ray, this._obb[j])){
                this._targetObbIndex = j;
                return;
            }
        }
        this._targetObbIndex = -1;
    },

    onTouchesMoved:function(touches, event){
        if(this._targetObbIndex >= 0){
            var location = touches[0].getLocation();
            this._obb[this._targetObbIndex].center = cc.math.vec3(location.x, location.y, 0);    
        }
    },

    calculateRayByLocationInView:function(location){
        var camera = cc.Camera.getDefaultCamera();

        var src = cc.math.vec3(location.x, location.y, -1);
        var nearPoint = camera.unproject(src);

        src = cc.math.vec3(location.x, location.y, 1);
        var farPoint = camera.unproject(src);

        var direction = cc.math.vec3(farPoint.x - nearPoint.x, farPoint.y - nearPoint.y, farPoint.z - nearPoint.z);
        direction.normalize();

        return cc.math.ray(nearPoint, direction);
    }
});

var Sprite3DMirrorTest = Sprite3DTestDemo.extend({
    _title:"Sprite3D Mirror Test",
    _subtitle:"",

    ctor:function(){
        this._super();

        var s = cc.winSize;
        this.addNewSpriteWithCoords(cc.p(s.width / 2, s.height / 2));
    },

    addNewSpriteWithCoords:function(position){
        var fileName = "Sprite3DTest/orc.c3b";
        var sprite = new jsb.Sprite3D("Sprite3DTest/orc.c3b");
        sprite.setScale(5);
        sprite.setRotation3D(cc.math.vec3(0, 180, 0));
        this.addChild(sprite);
        sprite.setPosition(cc.p(position.x - 80, position.y));

        //test attach
        var sp = new jsb.Sprite3D("Sprite3DTest/axe.c3b");
        sprite.getAttachNode("Bip001 R Hand").addChild(sp);

        var animation = new jsb.Animation3D(fileName);
        if(animation){
            var animate = new jsb.Animate3D(animation);
            sprite.runAction(cc.repeatForever(animate));
        }

        //create mirror Sprite3D
        sprite = new jsb.Sprite3D(fileName);
        sprite.setScale(5);
        sprite.setScaleX(-5);
        sprite.setCullFace(gl.FRONT);
        sprite.setRotation3D(cc.math.vec3(0, 180, 0));
        this.addChild(sprite);
        sprite.setPosition(cc.p(position.x + 80, position.y));

        //test attach
        sp = new jsb.Sprite3D("Sprite3DTest/axe.c3b");
        sprite.getAttachNode("Bip001 R Hand").addChild(sp);
        
        var animation = new jsb.Animation3D(fileName);
        if(animation){
            var animate = new jsb.Animate3D(animation);
            sprite.runAction(cc.repeatForever(animate));
        }
    }

});

var QuaternionTest = Sprite3DTestDemo.extend({
    _title:"Test Rotation With Quaternion",
    _subtitle:"",
    _sprite:null,
    _radius:100,
    _accAngle:0,

    ctor:function(){
        this._super();

        var sprite = new jsb.Sprite3D("Sprite3DTest/tortoise.c3b");
        sprite.setScale(0.1);
        var s = cc.winSize;
        sprite.setPosition(cc.p(s.width/2 + this._radius * Math.cos(this._accAngle), s.height / 2 + this._radius * Math.sin(this._accAngle)));
        this.addChild(sprite);
        this._sprite = sprite;
        var animation = new jsb.Animation3D("Sprite3DTest/tortoise.c3b");
        if(animation){
            var animate = new jsb.Animate3D(animation, 0, 1.933);
            sprite.runAction(cc.repeatForever(animate));
        }

        this.scheduleUpdate();
    },

    update:function(dt){
        this._accAngle += dt * cc.degreesToRadians(90);
        if(this._accAngle >= 2 * Math.PI)
            this._accAngle -= 2 * Math.PI;

        var s = cc.winSize;
        this._sprite.setPosition(cc.p(s.width / 2 + this._radius * Math.cos(this._accAngle), s.height / 2 + this._radius * Math.sin(this._accAngle)));

        var quat = cc.math.quaternion(cc.math.vec3(0, 0, 1), this._accAngle - Math.PI * 0.5);
        this._sprite.setRotationQuat(quat);
    }
});

var Sprite3DEmptyTest = Sprite3DTestDemo.extend({
    _title:"Testing Sprite3D Container",
    _subtitle:"Sprite3D can act as containers for 2D objects",

    ctor:function(){
        this._super();

        var s = new jsb.Sprite3D();
        s.setNormalizedPosition(cc.p(0.5, 0.5));
        var l = new cc.LabelTTF("Test");
        s.addChild(l);
        this.addChild(s);
    }
});

var Sprite3DForceDepthTest = Sprite3DTestDemo.extend({
    _title:"Force Depth Write Error Test",
    _subtitle:"Ship should always appear behind orc",

    ctor:function(){
        this._super();

        var orc = new jsb.Sprite3D("Sprite3DTest/orc.c3b");
        orc.setScale(5);
        orc.setNormalizedPosition(cc.p(0.5, 0.3));
        // orc.setPositionZ(40);
        orc.setVertexZ(40);
        orc.setRotation3D(cc.math.vec3(0, 180, 0));
        orc.setGlobalZOrder(-1);

        this.addChild(orc);

        var ship = new jsb.Sprite3D("Sprite3DTest/boss1.obj");
        ship.setScale(5);
        ship.setTexture("Sprite3DTest/boss.png");
        ship.setNormalizedPosition(cc.p(0.5, 0.5));
        ship.setRotation3D(cc.math.vec3(90, 0, 0));
        ship.setForceDepthWrite(true);

        this.addChild(ship);
    }
});

var UseCaseSprite3D1 = Sprite3DTestDemo.extend({
    _title:"Use Case For 2D + 3D",
    _subtitle:"3d transparent sprite + 2d sprite",
    _accAngle:0,

    ctor:function(){
        this._super();

        var s = cc.winSize;
        //setup camera
        var camera = new cc.Camera(cc.Camera.Mode.PERSPECTIVE, 40, s.width/s.height, 0.01, 1000);
        camera.setCameraFlag(cc.CameraFlag.USER1);
        camera.setPosition3D(cc.math.vec3(0, 30, 100));
        camera.lookAt(cc.math.vec3(0, 0, 0));
        this.addChild(camera);

        var sprite = new jsb.Sprite3D("Sprite3DTest/girl.c3b");
        sprite.setScale(0.15);
        var animation = new jsb.Animation3D("Sprite3DTest/girl.c3b");
        if(animation){
            var animate = new jsb.Animate3D(animation);
            sprite.runAction(cc.repeatForever(animate));
        }

        var circleBack = new jsb.Sprite3D();
        var circle = new cc.Sprite("Sprite3DTest/circle.png");
        circleBack.setScale(0.5);
        circleBack.addChild(circle);
        circle.runAction(cc.rotateBy(3, cc.math.vec3(0, 0, 360)).repeatForever());

        circleBack.setRotation3D(cc.math.vec3(90, 0, 0));

        var pos = sprite.getPosition3D();
        circleBack.setPosition3D(cc.math.vec3(pos.x, pos.y, pos.z-1));

        sprite.setOpacity(250);
        sprite.setCameraMask(2);
        circleBack.setCameraMask(2);
        sprite.setTag(3);
        circleBack.setTag(2);

        this.addChild(sprite);
        this.addChild(circleBack);

        this.scheduleUpdate();
        this.update(0.1);
    },

    update:function(dt){
        this._accAngle += dt * cc.degreesToRadians(60);

        var radius = 30;
        var x = Math.cos(this._accAngle) * radius;
        var z = Math.sin(this._accAngle) * radius;

        var sprite = this.getChildByTag(3);
        var circle = this.getChildByTag(2);

        sprite.setPositionX(x);
        sprite.setVertexZ(z);
        circle.setPositionX(x);
        circle.setVertexZ(z);
    }
});

var UseCaseSprite3D2 = Sprite3DTestDemo.extend({
    _title:"Use Case For 2D + 3D",
    _subtitle:"ui - 3d - ui, last ui should on the top",
    ctor:function(){
        this._super();

        var s = cc.winSize;
        //setup camera
        var camera = new cc.Camera(cc.Camera.Mode.PERSPECTIVE, 40, s.width/s.height, 0.01, 1000);
        camera.setCameraFlag(cc.CameraFlag.USER1);
        camera.setPosition3D(cc.math.vec3(0, 30, 100));
        camera.lookAt(cc.math.vec3(0, 0, 0));
        this.addChild(camera);

        var layer = new cc.LayerColor(cc.color(0, 0, 100, 255), s.width/2, s.height/2);
        layer.setPosition(s.width/4, s.height/4);
        layer.setGlobalZOrder(-1);
        layer.setTag(101);
        this.addChild(layer);

        var sprite = new jsb.Sprite3D("Sprite3DTest/girl.c3b");
        sprite.setScale(0.5);
        var animation = new jsb.Animation3D("Sprite3DTest/girl.c3b");
        if(animation){
            var animate = new jsb.Animate3D(animation);
            sprite.runAction(cc.repeatForever(animate));
        }
        sprite.setPosition(s.width/4, s.height/4);
        layer.addChild(sprite);

        var label1 = new cc.LabelTTF("Message", "Arial", 15);
        var item1 = new cc.MenuItemLabel(label1, this.menuCallback_Message, this);
        var label2 = new cc.LabelTTF("Message", "Arial", 15);
        var item2 = new cc.MenuItemLabel(label2, this.menuCallback_Message, this);

        item1.setPosition(cc.p(s.width/2 - item1.getContentSize().width/2, s.height/2 - item1.getContentSize().height));
        item2.setPosition(cc.p(s.width/2 - item1.getContentSize().width/2, s.height/2 - item1.getContentSize().height * 2));

        var menu = new cc.Menu(item1, item2);
        menu.setPosition(cc.p(0, 0));
        layer.addChild(menu);

    },

    menuCallback_Message:function(sender){
        var layer = this.getChildByTag(101);
        var message = layer.getChildByTag(102);
        if(message)
            layer.removeChild(message);
        else{
            // create a new message layer on the top
            var s = layer.getContentSize();
            var messagelayer = new cc.LayerColor(cc.color(100, 100, 0, 255));
            messagelayer.setContentSize(cc.size(s.width/2, s.height/2));
            messagelayer.setPosition(cc.p(s.width/4, s.height/4));
            var label = new cc.LabelTTF("This Message Layer \n Should Be On Top");
            label.setPosition(cc.p(s.width/4, s.height/4));
            messagelayer.addChild(label);
            messagelayer.setTag(102);
            layer.addChild(messagelayer);
        }

    }
});

var Sprite3DEffectTest = Sprite3DTestDemo.extend({
    _title:"Testing Sprite3D",
    _subtitle:"Sprite3d with effects",

    ctor:function(){
        this._super();

        cc.eventManager.addListener({
            event:cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesBegan:this.onTouchesBegan.bind(this)
        }, this);

        this.addNewSpriteWithCoords(cc.p(cc.winSize.width/2, cc.winSize.height/2));
    },

    addNewSpriteWithCoords:function(position){
        var sprite = new cc.EffectSprite3D("Sprite3DTest/boss1.obj", "Sprite3DTest/boss.png");
        var effect = new cc.Effect3DOutline();
        effect.setOutlineColor(cc.math.vec3(1, 0, 0));
        effect.setOutlineWidth(0.01);
        sprite.addEffect(effect, -1);

        var effect2 = new cc.Effect3DOutline();
        effect2.setOutlineColor(cc.math.vec3(1, 1, 0));
        effect2.setOutlineWidth(0.02);
        sprite.addEffect(effect2, -2);

        sprite.setScale(6);
        this.addChild(sprite);
        sprite.setPosition(position);

        var action;
        var random = Math.random();
        if(random < 0.2)
            action = cc.scaleBy(3, 2);
        else if(random < 0.4)
            action = cc.rotateBy(3, 360);
        else if(random < 0.6)
            action = cc.blink(1, 3);
        else if(random < 0.8)
            action = cc.tintBy(2, 0, -255, -255);
        else
            action = cc.fadeOut(2);

        var action_back = action.reverse();
        var seq = cc.sequence(action, action_back);

        sprite.runAction(seq.repeatForever());
    },

    onTouchesBegan:function(touches, event){
        for(var i = 0; i < touches.length; ++i){
            var location = touches[i].getLocation();
            this.addNewSpriteWithCoords(location);
        }
    }
});

var Sprite3DWithSkinOutlineTest = Sprite3DTestDemo.extend({
    _title:"Testing Sprite3D for skinned outline",
    _subtitle:"Tap screen to add more sprite3D",

    ctor:function(){
        this._super();

        cc.eventManager.addListener({
            event:cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesBegan:this.onTouchesBegan.bind(this)
        }, this);

        this.addNewSpriteWithCoords(cc.p(cc.winSize.width/2, cc.winSize.height/2));
    },

    addNewSpriteWithCoords:function(p){
        var sprite = new cc.EffectSprite3D("Sprite3DTest/orc.c3b");
        sprite.setScale(3);
        sprite.setRotation3D(cc.math.vec3(0, 180, 0));
        this.addChild(sprite);
        sprite.setPosition(p);

        var effect = new cc.Effect3DOutline();
        effect.setOutlineColor(cc.math.vec3(1, 0, 0));
        effect.setOutlineWidth(0.01);
        sprite.addEffect(effect, -1);

        var effect2 = new cc.Effect3DOutline();
        effect2.setOutlineColor(cc.math.vec3(1, 1, 0));
        effect2.setOutlineWidth(0.02);
        sprite.addEffect(effect2, -2);

        var animation = new jsb.Animation3D("Sprite3DTest/orc.c3b");
        if(animation){
            var animate = new jsb.Animate3D(animation);
            var inverse = Math.random() < 0.33 ? true : false;

            var rand2 = Math.random();
            var speed = 1.0;
            if(rand2 < 0.33)
                speed = animate.getSpeed() + Math.random();
            else if(rand2 < 0.66)            
                speed = animate.getSpeed() - 0.5 * Math.random();

            animate.setSpeed(inverse ? -speed : speed);
            sprite.runAction(new cc.RepeatForever(animate));
        }
    },

    onTouchesBegan:function(touches, event){
        for(var i = 0; i < touches.length; ++i){
            var location = touches[i].getLocation();
            this.addNewSpriteWithCoords(location);
        }
    }
});

var Sprite3DLightMapTest = Sprite3DTestDemo.extend({
    _title:"light map test",
    _subtitle:"drag the screen to move around",
    _camera:null,

    ctor:function(){
        this._super();

        //the assets are from the OpenVR demo
        //get the visible size.
        var visibleSize = cc.director.getVisibleSize();
        this._camera = new cc.Camera(cc.Camera.Mode.PERSPECTIVE, 60, visibleSize.width/visibleSize.height, 0.1, 200);
        this._camera.setCameraFlag(cc.CameraFlag.USER1);
        this._camera.setPosition3D(cc.math.vec3(0, 25, 15));
        this._camera.setRotation3D(cc.math.vec3(-35, 0, 0));

        var LightMapScene = new jsb.Sprite3D("Sprite3DTest/LightMapScene.c3b");
        LightMapScene.setScale(0.1);
        this.addChild(LightMapScene);
        this.addChild(this._camera);
        this.setCameraMask(2);

        //add a point light
        var light = new jsb.PointLight(cc.math.vec3(35, 75, -20.5), cc.color(255, 255, 255), 150);
        this.addChild(light);
        //set the ambient light 
        var ambient = new jsb.AmbientLight(cc.color(55, 55, 55));
        this.addChild(ambient);

        //create a listener
        cc.eventManager.addListener({
            event:cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesMoved:this.onTouchesMoved.bind(this)
        }, this);
    },

    onTouchesMoved:function(touches, event){
        if(touches.length === 1){
            var dt = cc.director.getDeltaTime();
            var touch = touches[0];
            var location = touch.getLocation();
            var previousLocation = touch.getPreviousLocation();
            var newPos = cc.p(previousLocation.x - location.x, previousLocation.y - location.y);

            var m = this._camera.getNodeToWorldTransform3D();
            var cameraDir = cc.math.vec3(-m[8], -m[9], -m[10]);
            cameraDir.normalize();
            cameraDir.y = 0;

            var cameraRightDir = cc.math.vec3(m[0], m[1], m[2]);
            cameraRightDir.normalize();
            cameraRightDir.y = 0;

            var cameraPos = this._camera.getPosition3D();
            cameraPos.x += cameraDir.x * newPos.y * dt + cameraRightDir.x * newPos.x * dt;
            cameraPos.y += cameraDir.y * newPos.y * dt + cameraRightDir.y * newPos.x * dt;
            cameraPos.z += cameraDir.z * newPos.y * dt + cameraRightDir.z * newPos.x * dt;
            this._camera.setPosition3D(cameraPos);
        }
    }
});

var Sprite3DUVAnimationTest = Sprite3DTestDemo.extend({
    _title:"Testing UV Animation",
    _subtitle:"",
    _cylinder_texture_offset:0,
    _shining_duration:0,
    _state:null,
    fade_in:true,

    ctor:function(){
        this._super();

        var visibleSize = cc.director.getVisibleSize();
        //use custom camera
        var camera = new cc.Camera(cc.Camera.Mode.PERSPECTIVE, 60, visibleSize.width/visibleSize.height, 0.1, 200);
        camera.setCameraFlag(cc.CameraFlag.USER1);
        this.addChild(camera);
        this.setCameraMask(2);

        //create cylinder
        var cylinder = new jsb.Sprite3D("Sprite3DTest/cylinder.c3b");
        this.addChild(cylinder);
        cylinder.setScale(3);
        cylinder.setPosition(visibleSize.width/2, visibleSize.height/2);
        cylinder.setRotation3D(cc.math.vec3(-90, 0, 0));

        //create and set our custom shader
        var shader = new cc.GLProgram("Sprite3DTest/cylinder.vert","Sprite3DTest/cylinder.frag");
        this._state = cc.GLProgramState.create(shader);
        cylinder.setGLProgramState(this._state);

        this._state.setUniformFloat("offset", this._cylinder_texture_offset);
        this._state.setUniformFloat("duration", this._shining_duration);

        //pass mesh's attribute to shader
        var offset = 0;
        var attributeCount = cylinder.getMesh().getMeshVertexAttribCount();
        for(var i = 0; i < attributeCount; ++i){
            var meshattribute = cylinder.getMesh().getMeshVertexAttribute(i);
            this._state.setVertexAttribPointer(cc.attributeNames[meshattribute.vertexAttrib],
                meshattribute.size,
                meshattribute.type,
                gl.FALSE,
                cylinder.getMesh().getVertexSizeInBytes(),
                offset);
            offset += meshattribute.attribSizeBytes;
        }

        //create the second texture for cylinder
        var shining_texture = cc.textureCache.addImage("Sprite3DTest/caustics.png");
        shining_texture.setTexParameters(gl.NEAREST, gl.NEAREST, gl.REPEAT, gl.REPEAT);
        //pass the texture sampler to our custom shader
        this._state.setUniformTexture("caustics", shining_texture);

        this.scheduleUpdate();
    },

    update:function(dt){
        //callback function to update cylinder's texcoord
        this._cylinder_texture_offset += 0.3 * dt;
        this._cylinder_texture_offset = this._cylinder_texture_offset > 1 ? 0 : this._cylinder_texture_offset;

        if(this.fade_in){
            this._shining_duration += 0.5 * dt;
            if(this._shining_duration > 1)
                this.fade_in = false;
        }else{
            this._shining_duration -= 0.5 * dt;
            if(this._shining_duration < 0)
                this.fade_in = true;
        }

        //pass the result to shader
        this._state.setUniformFloat("offset", this._cylinder_texture_offset);
        this._state.setUniformFloat("duration", this._shining_duration);
    }
});

var State = {
    State_None : 0,
    State_Idle : 0x01,
    State_Move : 0x02,
    State_Rotate : 0x04,
    State_Speak : 0x08,
    State_MeleeAttack : 0x10,
    State_RemoteAttack : 0x20,
    State_Attack : 0x40      
};

var Sprite3DFakeShadowTest = Sprite3DTestDemo.extend({
    _title:"fake shadow effect",
    _subtitle:"touch the screen to move around",
    _camera:null,
    _plane:null,
    _orc:null,
    _targetPos:null,
    _curState:0,

    ctor:function(){
        this._super();

        cc.eventManager.addListener({
            event:cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesEnded:this.onTouchesEnded.bind(this)
        }, this);

        var visibleSize = cc.director.getVisibleSize();
        var s = cc.winSize;

        this._orc = new jsb.Sprite3D("Sprite3DTest/orc.c3b");
        this._orc.setScale(0.2);
        this._orc.setRotation3D(cc.math.vec3(0, 180, 0));
        this._orc.setPosition3D(cc.math.vec3(0, 0, 0));

        this._targetPos = this._orc.getPosition3D();
        this.addChild(this._orc);

        //create a plane
        this._plane = new jsb.Sprite3D("Sprite3DTest/plane.c3t");
        this._plane.setRotation3D(cc.math.vec3(90, 0, 0));
        this.addChild(this._plane);

        //use a custom shader
        var shader = new cc.GLProgram("Sprite3DTest/simple_shadow.vert", "Sprite3DTest/simple_shadow.frag");
        var state = cc.GLProgramState.create(shader);
        this._plane.setGLProgramState(state);

        //pass mesh's attribute to shader
        var offset = 0;
        var attributeCount = this._plane.getMesh().getMeshVertexAttribCount();
        for(var i = 0; i < attributeCount; ++i){
            var meshattribute = this._plane.getMesh().getMeshVertexAttribute(i);
            state.setVertexAttribPointer(cc.attributeNames[meshattribute.vertexAttrib],
                meshattribute.size,
                meshattribute.type,
                gl.FALSE,
                this._plane.getMesh().getVertexSizeInBytes(),
                offset);
            offset += meshattribute.attribSizeBytes;
        }
        state.setUniformMat4("u_model_matrix", this._plane.getNodeToWorldTransform3D());

        //create shadow texture
        var shadowTexture = cc.textureCache.addImage("Sprite3DTest/shadowCircle.png");
        shadowTexture.setTexParameters(gl.LINEAR, gl.LINEAR, gl.CLAMP_TO_EDGE, gl.CLAMP_TO_EDGE);
        state.setUniformTexture("u_shadowTexture", shadowTexture);
        state.setUniformVec3("u_target_pos", this._targetPos);
        
        this._camera = new cc.Camera(cc.Camera.Mode.PERSPECTIVE, 60, s.width/s.height, 1, 1000);
        this._camera.setCameraFlag(cc.CameraFlag.USER1);
        this._camera.setPosition3D(cc.math.vec3(0, 20, 25));
        this._camera.lookAt(cc.math.vec3(0, 0, 0));
        this.addChild(this._camera);
        this.setCameraMask(2);

        this.scheduleUpdate();
    },

    update:function(dt){
        this.updateState(dt)
        
        if(this.isState(State.State_Move)){
            this.move3D(dt);
            if(this.isState(State.State_Rotate)){
                var curPos = this._orc.getPosition3D();
                var newFaceDir = cc.math.vec3(this._targetPos.x - curPos.x, this._targetPos.y - curPos.y, this._targetPos.z - curPos.z);
                newFaceDir.y = 0;
                newFaceDir.normalize();

                var m = this._orc.getNodeToWorldTransform3D();
                var up = cc.math.vec3(m[4], m[5], m[6]);
                up.normalize();

                var right = cc.math.vec3Cross(cc.math.vec3(-newFaceDir.x, -newFaceDir.y, -newFaceDir.z), up);
                right.normalize();

                var mat = [right.x,      right.y,      right.z,      0,
                           up.x,         up.y,         up.z,         0,
                           newFaceDir.x, newFaceDir.y, newFaceDir.z, 0,
                           0,            0,            0,            1];

                this._orc.setAdditionalTransform(mat);
            }
        }
    },

    updateState:function(dt){
        if(!this._targetPos)
            return;
        var curPos = this._orc.getPosition3D();
        var m = this._orc.getNodeToWorldTransform3D();
        var curFaceDir = cc.math.vec3(m[8], m[9], m[10]);
        curFaceDir.normalize();
        var newFaceDir = cc.math.vec3(this._targetPos.x - curPos.x, this._targetPos.y - curPos.y, this._targetPos.z - curPos.z);
        newFaceDir.y = 0;
        newFaceDir.normalize();
        var cosAngle = Math.abs(cc.math.vec3Dot(curFaceDir, newFaceDir) - 1);
        
        var dx = curPos.x - this._targetPos.x,
            dy = curPos.y - this._targetPos.y,
            dz = curPos.z - this._targetPos.z;
        var dist = dx * dx + dy * dy + dz * dz;

        if(dist <= 4){
            if(cosAngle <= 0.01)
                this._curState = State.State_Idle;
            else
                this._curState = State.State_Rotate;
        }else{
            if(cosAngle > 0.01)
                this._curState = State.State_Rotate | State.State_Move;
            else
                this._curState = State.State_Move;
        }
    },

    isState:function(bit){
        return (this._curState & bit) == bit;
    },

    move3D:function(dt){
        if(!this._targetPos)
            return;
        var curPos = this._orc.getPosition3D();
        var newFaceDir = cc.math.vec3(this._targetPos.x - curPos.x, this._targetPos.y - curPos.y, this._targetPos.z - curPos.z);
        newFaceDir.y = 0;
        newFaceDir.normalize();
        var offset = cc.math.vec3(newFaceDir.x * 25 * dt, newFaceDir.y * 25 * dt, newFaceDir.z * 25 * dt);
        curPos.x += offset.x;
        curPos.y += offset.y;
        curPos.z += offset.z;
        this._orc.setPosition3D(curPos);
        //pass the newest orc position
        this._plane.getGLProgramState().setUniformVec3("u_target_pos",curPos);
    },

    onTouchesEnded:function(touches, event){
        var touch = touches[0];
        var location = touch.getLocationInView();
        if(this._camera !== null){
           var nearP = cc.math.vec3(location.x, location.y, -1);
            var farP = cc.math.vec3(location.x, location.y, 1);

            nearP = this._camera.unproject(nearP);
            farP = this._camera.unproject(farP);

            var dir = cc.math.vec3(farP.x-nearP.x, farP.y-nearP.y, farP.z-nearP.z);
            var ndd = dir.y; // (0, 1, 0) * dir
            var ndo = nearP.y; // (0, 1, 0) * nearP
            var dist = - ndo / ndd;
            var p = cc.math.vec3(nearP.x+dist*dir.x, nearP.y+dist*dir.y, nearP.z+dist*dir.z);

            if(p.x > 100)
                p.x = 100;
            if(p.x < -100)
                p.x = -100;
            if(p.z > 100)
                p.z = 100
            if(p.z < -100)
                p.z = -100;

            this._targetPos = p;
        }
    }
});

var Sprite3DBasicToonShaderTest = Sprite3DTestDemo.extend({
    _title:"basic toon shader test",
    _subtitle:"",

    ctor:function(){
        this._super();

        var camera = new cc.Camera(cc.Camera.Mode.PERSPECTIVE, 60, cc.winSize.width/cc.winSize.height, 1, 1000);
        camera.setCameraFlag(cc.CameraFlag.USER1);
        this.addChild(camera);
        this.setCameraMask(2);

        //create a teapot
        var teapot = new jsb.Sprite3D("Sprite3DTest/teapot.c3b");
        //create and set out custom shader
        var shader = new cc.GLProgram("Sprite3DTest/toon.vert", "Sprite3DTest/toon.frag");
        var state = cc.GLProgramState.create(shader);
        teapot.setGLProgramState(state);
        teapot.setPosition3D(cc.math.vec3(cc.winSize.width/2, cc.winSize.height/2, -20));
        teapot.setRotation3D(cc.math.vec3(-90, 180, 0));
        teapot.setScale(10);
        teapot.runAction(cc.rotateBy(1.5, cc.math.vec3(0, 30, 0)).repeatForever());
        this.addChild(teapot);

        //pass mesh's attribute to shader
        var offset = 0;
        var attributeCount = teapot.getMesh().getMeshVertexAttribCount();
        for(var i = 0; i < attributeCount; ++i){
            var meshattribute = teapot.getMesh().getMeshVertexAttribute(i);
            state.setVertexAttribPointer(cc.attributeNames[meshattribute.vertexAttrib],
                meshattribute.size,
                meshattribute.type,
                gl.FALSE,
                teapot.getMesh().getVertexSizeInBytes(),
                offset);
            offset += meshattribute.attribSizeBytes;
        }
    }
});

var Sprite3DCubeMapTest = Sprite3DTestDemo.extend({
    _title:"CubeMap & Skybox Test",
    _subtitle:"",
    _camera:null,
    _angle:0,

    ctor:function(){
        this._super();

        var visibleSize = cc.director.getVisibleSize();
        var camera = new cc.Camera(cc.Camera.Mode.PERSPECTIVE, 60, visibleSize.width/visibleSize.height, 10, 1000);
        camera.setCameraFlag(cc.CameraFlag.USER1);
        camera.setPosition3D(cc.math.vec3(0, 0, 50));

        cc.eventManager.addListener({
            event:cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesMoved:this.onTouchesMoved.bind(this)
        }, this);

        //create a teap
        var teapot = new jsb.Sprite3D("Sprite3DTest/teapot.c3b");

        //create and set our custom shader
        var shader = new cc.GLProgram("Sprite3DTest/cube_map.vert","Sprite3DTest/cube_map.frag");
        var state = cc.GLProgramState.create(shader);

        //create the second texture for cylinder
        var textureCube = jsb.TextureCube.create("Sprite3DTest/skybox/left.jpg","Sprite3DTest/skybox/right.jpg", "Sprite3DTest/skybox/top.jpg", "Sprite3DTest/skybox/bottom.jpg", "Sprite3DTest/skybox/front.jpg", "Sprite3DTest/skybox/back.jpg");

        //set the texture parameters
        textureCube.setTexParameters(gl.LINEAR, gl.LINEAR, gl.MIRRORED_REPEAT, gl.MIRRORED_REPEAT);

        //pass the texture sampler to our custom shader
        state.setUniformTexture("u_cubeTex", textureCube);

        teapot.setGLProgramState(state);
        teapot.setPosition3D(cc.math.vec3(0, -5, 0));
        teapot.setRotation3D(cc.math.vec3(-90, 180, 0));

        teapot.runAction(cc.rotateBy(1.5, cc.math.vec3(0, 30, 0)).repeatForever());

        //pass mesh's attribute to shader
        var offset = 0;
        var attributeCount = teapot.getMesh().getMeshVertexAttribCount();
        for(var i = 0; i < attributeCount; ++i){
            var meshattribute = teapot.getMesh().getMeshVertexAttribute(i);
            state.setVertexAttribPointer(cc.attributeNames[meshattribute.vertexAttrib],
                                               meshattribute.size,
                                               meshattribute.type,
                                               gl.FALSE,
                                               teapot.getMesh().getVertexSizeInBytes(),
                                               offset);
            offset += meshattribute.attribSizeBytes;
        }

        this.addChild(teapot);

        //config skybox
        var skybox = jsb.Skybox.create();
        skybox.setTexture(textureCube);
        this.addChild(skybox);

        this.addChild(camera);
        this.setCameraMask(2);
        this._camera = camera;
    },

    onTouchesMoved:function(touches, event){
        if(touches.length > 0){
            var touch = touches[0];
            var delta = touch.getDelta();

            this._angle -= cc.degreesToRadians(delta.x);
            this._camera.setPosition3D(cc.math.vec3(50*Math.sin(this._angle), 0, 50*Math.cos(this._angle)));
            this._camera.lookAt(cc.math.vec3(0, 0, 0), cc.math.vec3(0, 1, 0));
        }
    }
});

var Sprite3DNormalMappingTest = Sprite3DTestDemo.extend({
                                                        
    _title:"NormalMapping Test",
    _subtitle:"",
    _angle:0.0,
    _reverseDir:false,
    _radius:100,
    _light:null,
    _TAG_GROSSINI:10,
    ctor:function(){
    this._super();
 
    var visibleSize = cc.director.getVisibleSize();
    var sphere1 = new jsb.Sprite3D("Sprite3DTest/sphere.c3b");
    sphere1.setPosition3D(cc.math.vec3(-30, 0, 0));
    sphere1.setRotation3D(cc.math.vec3(90, 0, 0));
    sphere1.setScale(2);
    sphere1.setCameraMask(2);
    sphere1.setTexture("Sprite3DTest/brickwork-texture.jpg");
    this.addChild(sphere1);
 
    var sphere2 = new jsb.Sprite3D("Sprite3DTest/sphere_bumped.c3b");
    sphere2.setPosition3D(cc.math.vec3(30, 0, 0));
    sphere2.setRotation3D(cc.math.vec3(90, 0, 0));
    sphere2.setScale(20);
    sphere2.setCameraMask(2);
    sphere2.setTexture("Sprite3DTest/brickwork-texture.jpg");
    this.addChild(sphere2);
 
    _light = new jsb.PointLight(cc.math.vec3(0, 0, 0), cc.color(255, 255, 255), 1000);
 
                                                        
    var camera = new cc.Camera(cc.Camera.Mode.PERSPECTIVE, 60, visibleSize.width/visibleSize.height, 1, 1000);
    camera.setCameraFlag(cc.CameraFlag.USER1);
    camera.setPosition3D(cc.math.vec3(0, 0, 100));
    camera.lookAt(cc.math.vec3(0,0,0));
    this.addChild(camera);
    this.addChild(_light, 1, this._TAG_GROSSINI);
    var angleReverseDir = cc.callFunc(function(){
                                      
                                      if(this._reverseDir){
                                      this._angle -= 0.01;
                                      if(this._angle < 0.0)
                                      {
                                      this._reverseDir = false;
                                      }
                                      }
                                      else{
                                      this._angle += 0.01;
                                      if(3.14159 < this._angle)
                                      {
                                      this._reverseDir = true;
                                      }
                                      }
                                      this.getChildByTag(this._TAG_GROSSINI).setPosition3D(cc.math.vec3(this._radius * Math.cos(this._angle), 0, this._radius * Math.sin(this._angle)));
                                      
                                      }, this);
    var seq1 = cc.sequence(angleReverseDir);
    _light.runAction(cc.repeatForever(seq1));
    
    }
});

//
// Flow control
//
var arrayOfSprite3DTest = [
    Sprite3DBasicTest,
    Sprite3DHitTest,
    AsyncLoadSprite3DTest,
    Sprite3DWithSkinTest,
    Animate3DTest,
    AttachmentTest,
    Sprite3DReskinTest,
    Sprite3DWithOBBPerformanceTest,
    Sprite3DMirrorTest,
    QuaternionTest,
    Sprite3DEmptyTest,
    Sprite3DForceDepthTest,
    UseCaseSprite3D1,
    UseCaseSprite3D2,
    Sprite3DCubeMapTest
];

// 3DEffect use custom shader which is not supported on WP8/WinRT yet. 
if (cc.sys.os !== cc.sys.OS_WP8 || cc.sys.os !== cc.sys.OS_WINRT) {
    arrayOfSprite3DTest = arrayOfSprite3DTest.concat([
        Sprite3DEffectTest,
        Sprite3DWithSkinOutlineTest,
        Sprite3DLightMapTest,
        Sprite3DUVAnimationTest,
        Sprite3DFakeShadowTest,
        Sprite3DBasicToonShaderTest,
        Sprite3DNormalMappingTest
    ]);
}

var nextSprite3DTest = function () {
    Sprite3DTestIdx++;
    Sprite3DTestIdx = Sprite3DTestIdx % arrayOfSprite3DTest.length;

    if(window.sideIndexBar){
        Sprite3DTestIdx = window.sideIndexBar.changeTest(Sprite3DTestIdx, 36);
    }

    return new arrayOfSprite3DTest[Sprite3DTestIdx ]();
};
var previousSprite3DTest = function () {
    Sprite3DTestIdx--;
    if (Sprite3DTestIdx < 0)
        Sprite3DTestIdx += arrayOfSprite3DTest.length;

    if(window.sideIndexBar){
        Sprite3DTestIdx = window.sideIndexBar.changeTest(Sprite3DTestIdx, 36);
    }

    return new arrayOfSprite3DTest[Sprite3DTestIdx ]();
};
var restartSprite3DTest = function () {
    return new arrayOfSprite3DTest[Sprite3DTestIdx ]();
};
