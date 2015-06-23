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
var Physics3DTestIdx = -1;

var physicsScene = null;

const START_POS_X = -0.5;
const START_POS_Y = -2.5;
const START_POS_Z = -0.5;

const ARRAY_SIZE_X = 4;
const ARRAY_SIZE_Y = 3;
const ARRAY_SIZE_Z = 4;

var Physics3DTestDemo = cc.Layer.extend({
    _title:"Physics3D Test",
    _subtitle:"",
    _camera:null,
    _angle:0.0,
    _needShootBox:false,
    _listener: null,

    ctor:function () {
        this._super();

        var size = cc.winSize;
        this._camera = cc.Camera.createPerspective(30.0, size.width / size.height, 1.0, 1000.0);
        this._camera.setPosition3D(cc.math.vec3(0, 50, 100));
        this._camera.lookAt(cc.math.vec3(0, 0, 0), cc.math.vec3(0, 1, 0));
        this._camera.setCameraFlag(cc.CameraFlag.USER1);
        this.addChild(this._camera);

        this._listener = cc.eventManager.addListener({
            event:cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesBegan:this.onTouchesBegan.bind(this),
            onTouchesMoved:this.onTouchesMoved.bind(this),
            onTouchesEnded:this.onTouchesEnded.bind(this)
        }, this);

        var label = new cc.LabelTTF("DebugDraw OFF");
        var menuItem = new cc.MenuItemLabel(label, function(){
            if(physicsScene.getPhysics3DWorld().isDebugDrawEnabled()){
                physicsScene.getPhysics3DWorld().setDebugDrawEnable(false);
                label.setString("DebugDraw OFF");
            }else{
                physicsScene.getPhysics3DWorld().setDebugDrawEnable(true);
                label.setString("DebugDraw ON");
            }
        }, this);

        var menu = new cc.Menu(menuItem);
        menu.setPosition(cc.p(0, 0));
        menuItem.setAnchorPoint(cc.p(0, 1));
        menuItem.setPosition(cc.p(cc.visibleRect.left.x, cc.visibleRect.top.y - 50));
        this.addChild(menu);
    },

    onTouchesBegan:function(touches, event){
        this._needShootBox = true;
    },

    onTouchesMoved:function(touches, event){
        if(touches.length > 0 && this._camera){
            var touch = touches[0];
            var delta = touch.getDelta();

            this._angle -= cc.degreesToRadians(delta.x);
            this._camera.setPosition3D(cc.math.vec3(100*Math.sin(this._angle), 50, 100*Math.cos(this._angle)));
            this._camera.lookAt(cc.math.vec3(0, 0, 0), cc.math.vec3(0, 1, 0));

            if(delta.x * delta.x + delta.y + delta.y > 16)
                this._needShootBox = false;
        }
    },

    onTouchesEnded:function(touches, event){
        if(!this._needShootBox)
            return;
        if(touches.length > 0){
            var location = touches[0].getLocationInView();

            var nearP = cc.math.vec3(location.x, location.y, -1);
            var farP = cc.math.vec3(location.x, location.y, 1);
            nearP = this._camera.unproject(nearP);
            farP = this._camera.unproject(farP);

            var dir = cc.math.vec3Sub(farP, nearP);
            this.shootBox(cc.math.vec3Add(this._camera.getPosition3D(), cc.math.vec3(dir.x*10, dir.y*10, dir.z*10)));
        }
    },

    shootBox:function(des){
        var rbDes = jsb.physics3DRigidBodyDes();
        var linearVel = cc.math.vec3Sub(des, this._camera.getPosition3D());
        linearVel.normalize();
        linearVel.x *= 100;
        linearVel.y *= 100;
        linearVel.z *= 100;

        rbDes.mass = 1;
        rbDes.shape = jsb.Physics3DShape.createBox(cc.math.vec3(0.5, 0.5, 0.5));
        var v = this._camera.getPosition3D();
        rbDes.originalTransform[12] = v.x;
        rbDes.originalTransform[13] = v.y;
        rbDes.originalTransform[14] = v.z;
        var sprite = jsb.PhysicsSprite3D.create("Sprite3DTest/box.c3t", rbDes);
        sprite.setTexture("Images/Icon.png");

        var rigidBody = sprite.getPhysicsObj();
        rigidBody.setLinearFactor(cc.math.vec3(1, 1, 1));
        rigidBody.setLinearVelocity(linearVel);
        rigidBody.setAngularVelocity(cc.math.vec3(0, 0, 0));
        rigidBody.setCcdMotionThreshold(0.5);
        rigidBody.setCcdSweptSphereRadius(0.4);

        this.addChild(sprite);
        sprite.setPosition3D(this._camera.getPosition3D());
        sprite.setScale(0.5);
        sprite.syncNodeToPhysics();
        sprite.setSyncFlag(jsb.Physics3DComponent.PhysicsSyncFlag.PHYSICS_TO_NODE);
        sprite.setCameraMask(cc.CameraFlag.USER1);
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
        var s = new Physics3DTestScene();
        s.addChild(restartPhysics3DTest());
        director.runScene(s);
    },

    onNextCallback:function (sender) {
        var s = new Physics3DTestScene();
        s.addChild(nextPhysics3DTest());
        director.runScene(s);
    },

    onBackCallback:function (sender) {
        var s = new Physics3DTestScene();
        s.addChild(previousPhysics3DTest());
        director.runScene(s);
    }
});

var Physics3DTestScene = cc.Scene.extend({
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

        this.initWithPhysics();
        this.getPhysics3DWorld().setDebugDrawEnable(false);
        physicsScene = this;
    },
    onMainMenuCallback:function () {
        var scene = new cc.Scene();
        var layer = new TestController();
        scene.addChild(layer);
        director.runScene(scene);
    },
    runThisTest:function (num) {
        Physics3DTestIdx = (num || num == 0) ? (num - 1) : -1;
        var layer = nextPhysics3DTest();
        this.addChild(layer);

        director.runScene(this);
    }
});

var BasicPhysics3DDemo = Physics3DTestDemo.extend({
    _subtitle:"Basic Physics3D",

    ctor:function(){
        this._super();

        var rbDes = jsb.physics3DRigidBodyDes();
        rbDes.mass = 0;
        rbDes.shape = jsb.Physics3DShape.createBox(cc.math.vec3(60, 1, 60));

        var floor = jsb.PhysicsSprite3D.create("Sprite3DTest/box.c3t", rbDes);
        floor.setTexture("Sprite3DTest/plane.png");
        floor.setScaleX(60);
        floor.setScaleZ(60);
        this.addChild(floor);
        floor.setCameraMask(cc.CameraFlag.USER1);
        floor.syncNodeToPhysics();
        //static object sync is not needed
        floor.setSyncFlag(jsb.Physics3DComponent.PhysicsSyncFlag.NONE);

        //create several boxes using PhysicsSprite3D
        rbDes.mass = 1;
        rbDes.shape = jsb.Physics3DShape.createBox(cc.math.vec3(0.8, 0.8, 0.8));
        var start_x = START_POS_X - ARRAY_SIZE_X/2;
        var start_y = START_POS_Y;
        var start_z = START_POS_Z - ARRAY_SIZE_Z/2;

        for(var k = 0; k < ARRAY_SIZE_Y; ++k){
            for(var i = 0; i < ARRAY_SIZE_X; ++i){
                for(var j = 0; j < ARRAY_SIZE_Z; ++j){
                    var x = i + start_x,
                        y = 5 + k + start_y,
                        z = j + start_z;
                    var sprite = jsb.PhysicsSprite3D.create("Sprite3DTest/box.c3t", rbDes);
                    sprite.setTexture("Images/CyanSquare.png");
                    sprite.setPosition3D(cc.math.vec3(x, y, z));
                    sprite.syncNodeToPhysics();
                    sprite.setSyncFlag(jsb.Physics3DComponent.PhysicsSyncFlag.PHYSICS_TO_NODE);
                    sprite.setCameraMask(cc.CameraFlag.USER1);
                    sprite.setScale(0.8);
                    this.addChild(sprite);
                }
            }
        }

        physicsScene.setPhysics3DDebugCamera(this._camera);
    }
});

var Physics3DConstraintDemo = Physics3DTestDemo.extend({
    _subtitle:"Physics3D Constraint",
    _constraint: null,
    _world: null,

    ctor:function(){
        this._super();

        this._listener.onTouchesBegan = this.onTouchesBegan.bind(this);
        this._listener.onTouchesMoved = this.onTouchesMoved.bind(this);
        this._listener.onTouchesEnded = this.onTouchesEnded.bind(this);

        //PhysicsSprite3d = Sprite3D + Physics3DComponent
        var rbDes = jsb.physics3DRigidBodyDes();
        rbDes.disableSleep = true;
        rbDes.mass = 10;
        rbDes.shape = jsb.Physics3DShape.createBox(cc.math.vec3(5, 5, 5));

        var rigidBody = jsb.Physics3DRigidBody.create(rbDes);
        var quat = cc.math.quaternion(cc.math.vec3(0, 1, 0), cc.degreesToRadians(180));
        var component = jsb.Physics3DComponent.create(rigidBody, cc.math.vec3(0, -3, 0), quat);

        var sprite = new jsb.Sprite3D("Sprite3DTest/orc.c3b");
        sprite.addComponent(component);
        this.addChild(sprite);
        sprite.setCameraMask(cc.CameraFlag.USER1);
        sprite.setScale(0.4);
        sprite.setPosition3D(cc.math.vec3(-20, 5, 0));
        component.syncNodeToPhysics();
        component.setSyncFlag(jsb.Physics3DComponent.PhysicsSyncFlag.PHYSICS_TO_NODE);

        physicsScene.setPhysics3DDebugCamera(this._camera);
        this._world = physicsScene.getPhysics3DWorld();

        //create point to point constraint
        var constraint = jsb.Physics3DPointToPointConstraint.create(rigidBody, cc.math.vec3(2.5, 2.5, 2.5));
        this._world.addPhysics3DConstraint(constraint);

        //create hinge constraint
        rbDes.mass = 1;
        rbDes.shape = jsb.Physics3DShape.createBox(cc.math.vec3(8, 8, 1));
        rigidBody = jsb.Physics3DRigidBody.create(rbDes);
        component = jsb.Physics3DComponent.create(rigidBody);
        sprite = new jsb.Sprite3D("Sprite3DTest/box.c3t");
        sprite.setTexture("Sprite3DTest/plane.png");
        sprite.setScaleX(8);
        sprite.setScaleY(8);
        sprite.setPosition3D(cc.math.vec3(5, 0, 0));
        sprite.addComponent(component);
        sprite.setCameraMask(cc.CameraFlag.USER1);
        this.addChild(sprite);
        component.syncNodeToPhysics();
        rigidBody.setAngularVelocity(cc.math.vec3(0, 3, 0));
        constraint = jsb.Physics3DHingeConstraint.create(rigidBody, cc.math.vec3(4, 4, 0.5), cc.math.vec3(0, 1, 0));
        this._world.addPhysics3DConstraint(constraint);

        //create slider constraint
        rbDes.mass = 1;
        rbDes.shape = jsb.Physics3DShape.createBox(cc.math.vec3(3, 2, 3));
        rigidBody = jsb.Physics3DRigidBody.create(rbDes);
        component = jsb.Physics3DComponent.create(rigidBody);
        sprite = new jsb.Sprite3D("Sprite3DTest/box.c3t");
        sprite.setTexture("Sprite3DTest/plane.png");
        sprite.setScaleX(3);
        sprite.setScaleZ(3);
        sprite.setPosition3D(cc.math.vec3(30, 15, 0));
        sprite.addComponent(component);
        sprite.setCameraMask(cc.CameraFlag.USER1);
        this.addChild(sprite);
        component.syncNodeToPhysics();
        rigidBody.setLinearVelocity(cc.math.vec3(0, 3, 0));

        rbDes.mass = 0;
        rbDes.shape = jsb.Physics3DShape.createBox(cc.math.vec3(3, 3, 3));
        var rigidBodyB = jsb.Physics3DRigidBody.create(rbDes);
        component = jsb.Physics3DComponent.create(rigidBodyB);
        sprite = new jsb.Sprite3D("Sprite3DTest/box.c3t");
        sprite.setTexture("Sprite3DTest/plane.png");
        sprite.setScale(3);
        sprite.setPosition3D(cc.math.vec3(30, 5, 0));
        sprite.addComponent(component);
        sprite.setCameraMask(cc.CameraFlag.USER1);
        this.addChild(sprite);
        component.syncNodeToPhysics();

        var frameInA = [-4.37114e-8, 1, 0, 0, -1, -4.37114e-8, 0, 0, 0, 0, 1, 0, 0, -5, 0, 1];
        var frameInB = [-4.37114e-8, 1, 0, 0, -1, -4.37114e-8, 0, 0, 0, 0, 1, 0, 0, 5, 0, 1];
        constraint = jsb.Physics3DSliderConstraint.create(rigidBody, rigidBodyB, frameInA, frameInB, false);
        this._world.addPhysics3DConstraint(constraint);
        constraint.setLowerLinLimit(-5);
        constraint.setUpperLinLimit(5);

        //create ConeTwist constraint
        rbDes.mass = 1;
        rbDes.shape = jsb.Physics3DShape.createBox(cc.math.vec3(3, 3, 3));
        rigidBody = jsb.Physics3DRigidBody.create(rbDes);
        component = jsb.Physics3DComponent.create(rigidBody);
        sprite = new jsb.Sprite3D("Sprite3DTest/box.c3t");
        sprite.setTexture("Sprite3DTest/plane.png");
        sprite.setScale(3);
        sprite.setPosition3D(cc.math.vec3(-10, 5, 5));
        sprite.addComponent(component);
        sprite.setCameraMask(cc.CameraFlag.USER1);
        this.addChild(sprite);
        component.syncNodeToPhysics();

        frameInA = [-4.37114e-8, 1, 0, 0, -1, -4.37114e-8, 0, 0, 0, 0, 1, 0, 0, -10, 0, 1];
        constraint = jsb.Physics3DConeTwistConstraint.create(rigidBody, frameInA);
        this._world.addPhysics3DConstraint(constraint, true);
        constraint.setLimit(cc.degreesToRadians(10), cc.degreesToRadians(10), cc.degreesToRadians(40));

        //create 6 dof constraint
        rbDes.mass = 1;
        rbDes.shape = jsb.Physics3DShape.createBox(cc.math.vec3(3, 3, 3));
        rigidBody = jsb.Physics3DRigidBody.create(rbDes);
        component = jsb.Physics3DComponent.create(rigidBody);
        sprite = new jsb.Sprite3D("Sprite3DTest/box.c3t");
        sprite.setTexture("Sprite3DTest/plane.png");
        sprite.setScale(3);
        sprite.setPosition3D(cc.math.vec3(30, -5, 0));
        sprite.addComponent(component);
        sprite.setCameraMask(cc.CameraFlag.USER1);
        this.addChild(sprite);
        component.syncNodeToPhysics();

        frameInA = [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1];
        constraint = jsb.Physics3D6DofConstraint.create(rigidBody, frameInA, false);
        this._world.addPhysics3DConstraint(constraint);
        constraint.setAngularLowerLimit(cc.math.vec3(0, 0, 0));
        constraint.setAngularUpperLimit(cc.math.vec3(0, 0, 0));
        constraint.setLinearLowerLimit(cc.math.vec3(-10, 0, 0));
        constraint.setLinearUpperLimit(cc.math.vec3(10, 0, 0));
    },

    onTouchesBegan:function(touches, event){
        if(this._camera){
            cc.log("STARTED " + touches.length);
            var touch = touches[0];
            var location = touch.getLocationInView();

            var nearP = cc.math.vec3(location.x, location.y, 0);
            var farP = cc.math.vec3(location.x, location.y, 1);

            var size = director.getWinSize();
            nearP    = this._camera.unproject(size, nearP);
            farP     = this._camera.unproject(size, farP);

            var result = this._world.rayCast(nearP, farP);
            if(result.hitObj !== undefined && result.hitObj.getObjType() == jsb.Physics3DObject.PhysicsObjType.RIGID_BODY)
            {
                var mat = cc.math.mat4GetInversed(result.hitObj.getWorldTransform());
                var position =  cc.math.mat4TransformPoint(mat, result.hitPosition);

                this._constraint = jsb.Physics3DPointToPointConstraint.create(result.hitObj, position);
                this._world.addPhysics3DConstraint(this._constraint, true);
                this._pickingDistance = cc.math.vec3Length(cc.math.vec3Sub(result.hitPosition, nearP));
                return;
            }
        }
        Physics3DTestDemo.prototype.onTouchesBegan.call(this, touches, event);
        this._needShootBox = false;
    },

    onTouchesMoved:function(touches, event){
        if(this._constraint){
            var touch = touches[0];
            var location = touch.getLocationInView();

            var nearP = cc.math.vec3(location.x, location.y, 0);
            var farP = cc.math.vec3(location.x, location.y, 1);

            var size = director.getWinSize();
            nearP    = this._camera.unproject(size, nearP);
            farP     = this._camera.unproject(size, farP);

            var dir  = cc.math.vec3Normalize(cc.math.vec3Sub(farP, nearP));
            this._constraint.setPivotPointInB(cc.math.vec3Add(nearP, cc.math.vec3(dir.x * this._pickingDistance, dir.y * this._pickingDistance, dir.z * this._pickingDistance)));
            return;
        }
        Physics3DTestDemo.prototype.onTouchesMoved.call(this, touches, event);
    },

    onTouchesEnded:function(touches, event){
        if(this._constraint){
            this._world.removePhysics3DConstraint(this._constraint);
            this._constraint = null;
            return;
        }
        Physics3DTestDemo.prototype.onTouchesEnded.call(this, touches, event);
    }
});

var Physics3DKinematicDemo = Physics3DTestDemo.extend({
    _subtitle:"Physics3D Kinematic",

    ctor:function(){
        this._super();

        var rbDes = jsb.physics3DRigidBodyDes();
        rbDes.mass = 0;
        rbDes.shape = jsb.Physics3DShape.createBox(cc.math.vec3(60, 1, 60));

        var floor = jsb.PhysicsSprite3D.create("Sprite3DTest/box.c3t", rbDes);
        floor.setTexture("Sprite3DTest/plane.png");
        floor.setScaleX(60);
        floor.setScaleZ(60);
        floor.setPosition3D(cc.math.vec3(0, -1, 0));
        this.addChild(floor);
        floor.setCameraMask(cc.CameraFlag.USER1);
        floor.syncNodeToPhysics();
        //static object sync is not needed
        floor.setSyncFlag(jsb.Physics3DComponent.PhysicsSyncFlag.NONE);

        //create Kinematics
        for(var i = 0; i < 3; ++i){
            rbDes.mass = 0;
            rbDes.shape = jsb.Physics3DShape.createBox(cc.math.vec3(2, 2, 2));

            var sprite = jsb.PhysicsSprite3D.create("Sprite3DTest/box.c3t", rbDes);
            sprite.setTexture("Images/CyanSquare.png");
            sprite.setCameraMask(cc.CameraFlag.USER1);
            var rigidBody = sprite.getPhysicsObj();
            rigidBody.setKinematic(true);

            this.addChild(sprite);

            sprite.setScale(2);
            sprite.setPosition3D(cc.math.vec3(-15, 0, 15-15*i));
            var moveby = cc.moveBy(2+i, cc.math.vec3(30, 0, 0));
            sprite.runAction(cc.sequence(moveby, moveby.reverse()).repeatForever());
        }

        //create Dynamic
        rbDes.mass = 1;
        rbDes.shape = jsb.Physics3DShape.createSphere(0.5);
        var start_x = START_POS_X - ARRAY_SIZE_X/2;
        var start_y = START_POS_Y + 5;
        var start_z = START_POS_Z - ARRAY_SIZE_Z/2;

        for(var k = 0; k < ARRAY_SIZE_Y; ++k){
            for(var i = 0; i < ARRAY_SIZE_X; ++i){
                for(var j = 0; j < ARRAY_SIZE_Z; ++j){
                    var x = i + start_x,
                        y = 5 + k + start_y,
                        z = j + start_z;

                    rbDes.originalTransform[12] = x;
                    rbDes.originalTransform[13] = y;
                    rbDes.originalTransform[14] = z;

                    var sprite = jsb.PhysicsSprite3D.create("Sprite3DTest/sphere.c3b", rbDes);
                    sprite.setTexture("Sprite3DTest/plane.png");
                    sprite.setPosition3D(cc.math.vec3(x, y, z));
                    sprite.syncNodeToPhysics();
                    sprite.setSyncFlag(jsb.Physics3DComponent.PhysicsSyncFlag.PHYSICS_TO_NODE);
                    sprite.setCameraMask(cc.CameraFlag.USER1);
                    sprite.setScale(1/sprite.getContentSize().width);
                    this.addChild(sprite);
                }
            }
        }

        physicsScene.setPhysics3DDebugCamera(this._camera);
    }
});

var Physics3DCollisionCallbackDemo = Physics3DTestDemo.extend({
    _subtitle:"Physics3D CollisionCallback",

    ctor:function(){
        this._super();

        var rbDes = jsb.physics3DRigidBodyDes();

        var scale = 2;
        var trianglesList = jsb.Bundle3D.getTrianglesList("Sprite3DTest/boss.c3b");

        for(var i = 0; i < trianglesList.length; ++i){
            trianglesList[i].x *= scale;
            trianglesList[i].y *= scale;
            trianglesList[i].z *= scale;
        }

        rbDes.mass = 0;
        rbDes.shape = jsb.Physics3DShape.createMesh(trianglesList, trianglesList.length/3);

        var rigidBody = jsb.Physics3DRigidBody.create(rbDes);
        var component = jsb.Physics3DComponent.create(rigidBody);
        var sprite = new jsb.Sprite3D("Sprite3DTest/boss.c3b");
        sprite.addComponent(component);
        sprite.setRotation3D(cc.math.vec3(-90, 0, 0));
        sprite.setScale(scale);
        sprite.setCameraMask(cc.CameraFlag.USER1);
        this.addChild(sprite);

        rigidBody.setCollisionCallback(function(collisionInfo){
            if(collisionInfo.collisionPointList.length > 0 && collisionInfo.objA.getMask() != 0){
                var ps = jsb.PUParticleSystem3D.create("Particle3D/scripts/mp_hit_04.pu");
                ps.setPosition3D(collisionInfo.collisionPointList[0].worldPositionOnB);
                ps.setScale(0.05);
                ps.startParticleSystem();
                ps.setCameraMask(2);
                this.addChild(ps);

                ps.runAction(cc.sequence(cc.delayTime(1), cc.callFunc(function(){
                    ps.removeFromParent();
                })));

                collisionInfo.objA.setMask(0);
            }

        }, this);

        physicsScene.setPhysics3DDebugCamera(this._camera);
    }
});

var Physics3DTerrainDemo = Physics3DTestDemo.extend({
    _subtitle:"Physics3D Terrain",

    ctor:function(){
        this._super();

        var r = jsb.Terrain.detailMap("TerrainTest/dirt.jpg"),
            g = jsb.Terrain.detailMap("TerrainTest/Grass2.jpg", 10),
            b = jsb.Terrain.detailMap("TerrainTest/road.jpg"),
            a = jsb.Terrain.detailMap("TerrainTest/GreenSkin.jpg", 20);
        var data = jsb.Terrain.terrainData(
            "TerrainTest/heightmap129.jpg",
            "TerrainTest/alphamap.png",
            [r, g, b, a],
            cc.size(32,32),
            20,
            1
        );

        var terrain = jsb.Terrain.create(data, jsb.Terrain.CrackFixedType.SKIRT);
        terrain.setSkirtHeightRatio(3);
        terrain.setLODDistance(64, 128, 192);
        terrain.setMaxDetailMapAmount(4);
        terrain.setCameraMask(2);
        terrain.setDrawWire(false);

        var rbDes = jsb.physics3DRigidBodyDes();
        rbDes.mass = 0;

        var heightData = terrain.getHeightData();
        var size = terrain.getTerrainSize();
        rbDes.shape = jsb.Physics3DShape.createHeightfield(size.width, size.height, heightData, 1.0, terrain.getMinHeight(), terrain.getMaxHeight(), true, false, true);
        var rigidBody = jsb.Physics3DRigidBody.create(rbDes);
        var component = jsb.Physics3DComponent.create(rigidBody);
        terrain.addComponent(component);
        component.syncNodeToPhysics();
        component.setSyncFlag(jsb.Physics3DComponent.PhysicsSyncFlag.NONE);

        this.addChild(terrain);

        //create several spheres
        rbDes.mass = 1;
        rbDes.shape = jsb.Physics3DShape.createSphere(0.5);
        var start_x = START_POS_X - ARRAY_SIZE_X/2 + 5;
        var start_y = START_POS_Y + 20;
        var start_z = START_POS_Z - ARRAY_SIZE_Z/2;

        for(var k = 0; k < ARRAY_SIZE_Y; ++k){
            for(var i = 0; i < ARRAY_SIZE_X; ++i){
                for(var j = 0; j < ARRAY_SIZE_Z; ++j){
                    var x = i + start_x,
                        y = 5 + k + start_y,
                        z = j + start_z;

                    var sprite = jsb.PhysicsSprite3D.create("Sprite3DTest/sphere.c3b", rbDes);
                    sprite.setTexture("Sprite3DTest/plane.png");
                    sprite.setPosition3D(cc.math.vec3(x, y, z));
                    sprite.syncNodeToPhysics();
                    sprite.setSyncFlag(jsb.Physics3DComponent.PhysicsSyncFlag.PHYSICS_TO_NODE);
                    sprite.setCameraMask(cc.CameraFlag.USER1);
                    sprite.setScale(1/sprite.getContentSize().width);
                    this.addChild(sprite);
                }
            }
        }

        //create mesh
        var trianglesList = jsb.Bundle3D.getTrianglesList("Sprite3DTest/boss.c3b");
        rbDes.mass = 0;
        rbDes.shape = jsb.Physics3DShape.createMesh(trianglesList, trianglesList.length/3);
        rigidBody = jsb.Physics3DRigidBody.create(rbDes);
        component = jsb.Physics3DComponent.create(rigidBody);
        var sprite = new jsb.Sprite3D("Sprite3DTest/boss.c3b");
        sprite.addComponent(component);
        sprite.setRotation3D(cc.math.vec3(-90, 0, 0));
        sprite.setPosition3D(cc.math.vec3(0, 15, 0));
        sprite.setCameraMask(2);
        this.addChild(sprite);


        physicsScene.setPhysics3DDebugCamera(this._camera);
    }
});

//
// Flow control
//
var arrayOfPhysics3DTest = [
    BasicPhysics3DDemo,
    Physics3DConstraintDemo,
    Physics3DKinematicDemo,
    Physics3DCollisionCallbackDemo,
    Physics3DTerrainDemo
];

var nextPhysics3DTest = function () {
    Physics3DTestIdx++;
    Physics3DTestIdx = Physics3DTestIdx % arrayOfPhysics3DTest.length;

    return new arrayOfPhysics3DTest[Physics3DTestIdx ]();
};
var previousPhysics3DTest = function () {
    Physics3DTestIdx--;
    if (Physics3DTestIdx < 0)
        Physics3DTestIdx += arrayOfPhysics3DTest.length;

    return new arrayOfPhysics3DTest[Physics3DTestIdx ]();
};
var restartPhysics3DTest = function () {
    return new arrayOfPhysics3DTest[Physics3DTestIdx ]();
};
