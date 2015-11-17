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

var CameraType = {
    Free : 0,
    FirstPerson : 1,
    ThirdPerson : 2,      
};

var OperateCamType = {
    MoveCamera : 0,
    RotateCamera : 1
};

var Camera3DTestIdx = -1;

var Camera3DTestDemo = cc.Layer.extend({
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
        var s = new Camera3DTestScene();
        s.addChild(restartCamera3DTest());
        director.runScene(s);
    },

    onNextCallback:function (sender) {
        var s = new Camera3DTestScene();
        s.addChild(nextCamera3DTest());
        director.runScene(s);
    },

    onBackCallback:function (sender) {
        var s = new Camera3DTestScene();
        s.addChild(previousCamera3DTest());
        director.runScene(s);
    },
});

var Camera3DTestScene = cc.Scene.extend({
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
        Camera3DTestIdx = (num || num == 0) ? (num - 1) : -1;
        var layer = nextCamera3DTest();
        this.addChild(layer);

        director.runScene(this);
    }
});

var CameraRotationTest = Camera3DTestDemo.extend({
    _title:"Camera Rotation Test",
    _subtitle:"Slide to rotate",
    _camControlNode:null,
    _camNode:null,

    ctor:function(){
        this._super();

        var s = cc.winSize;
        this._camControlNode = new cc.Node();
        this._camControlNode.setNormalizedPosition(cc.p(0.5, 0.5));
        this.addChild(this._camControlNode);

        this._camNode = new cc.Node();
        this._camNode.setVertexZ(cc.Camera.getDefaultCamera().getPosition3D().z);
        this._camControlNode.addChild(this._camNode);

        var sp3d = new jsb.Sprite3D();
        sp3d.setPosition(s.width/2, s.height/2);
        this.addChild(sp3d);

        var lship = new cc.LabelTTF("Ship");
        lship.setPosition(0, 20);
        sp3d.addChild(lship);

        //Billboards
        //Yellow is at the back
        var bill1 = new jsb.BillBoard("Images/Icon.png");
        bill1.setPosition3D(cc.math.vec3(50, 10, -10));
        bill1.setColor(cc.color.YELLOW);
        bill1.setScale(0.6);
        sp3d.addChild(bill1);

        var l1 = new cc.LabelTTF("Billboard1");
        l1.setPosition(cc.p(0, -10));
        l1.setColor(cc.color.WHITE);
        l1.setScale(3);
        bill1.addChild(l1);

        var p1 = new cc.ParticleSystem("Particles/SmallSun.plist");
        p1.setPosition(30, 80);
        bill1.addChild(p1);

        var bill2 = new jsb.BillBoard("Images/Icon.png");
        bill2.setPosition3D(cc.math.vec3(-50, -10, 10));
        bill2.setScale(0.6);
        sp3d.addChild(bill2);

        var l2 = new cc.LabelTTF("Billboard2");
        l2.setPosition(0, -10);
        l2.setColor(cc.color.WHITE);
        l2.setScale(3);
        bill2.addChild(l2);

        var p2 = new cc.ParticleSystem("Particles/SmallSun.plist");
        p2.setPosition(30,80);
        bill2.addChild(p2);

        //3D models
        var model = new jsb.Sprite3D("Sprite3DTest/boss1.obj");
        model.setScale(4);
        model.setTexture("Sprite3DTest/boss.png");
        model.setPosition3D(cc.math.vec3(s.width/2, s.height/2, 0));
        this.addChild(model);

        var self = this;
        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            onTouchBegan: function(touch, event){return true;},
            onTouchMoved: function(touch, event){
                var dx = touch.getDelta().x;
                var rot = self._camControlNode.getRotation3D();
                rot.y += dx;
                self._camControlNode.setRotation3D(rot);

                var matrix = self._camNode.getNodeToWorldTransform3D();
                var worldPos = cc.math.vec3(matrix[12], matrix[13], matrix[14]);

                cc.Camera.getDefaultCamera().setPosition3D(worldPos);
                cc.Camera.getDefaultCamera().lookAt(self._camControlNode.getPosition3D());
            }
        }, this);
    }
});

var Camera3DTest = (function(){
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

    return Camera3DTestDemo.extend({
        _title:"Testing Camera",
        _subtitle:"",
        _layer3D:null,
        _sprite3D:null,
        _targetPos:null,
        _camera:null,
        _cameraType:-1,
        _curState:0,
        _bZoomOut:false,
        _bZoomIn:false,
        _bRotateLeft:false,
        _bRotateRight:false,
        _ZoomOutlabel:null,
        _ZoomInlabel:null,
        _RotateLeftlabel:null,
        _RotateRightlabel:null,
        
        ctor:function(){
            this._super();
        },

        onEnter:function(){
            this._super();

            cc.eventManager.addListener({
                event: cc.EventListener.TOUCH_ALL_AT_ONCE,
                // onTouchesBegan: this.onTouchesBegan,
                onTouchesMoved: this.onTouchesMoved.bind(this),
                onTouchesEnded: this.onTouchesEnded.bind(this)
            }, this);

            var layer3D = new cc.Layer();
            this.addChild(layer3D, 0);
            this._layer3D = layer3D;
            this._curState = State.State_None;
            this.addNewSpriteWithCoords(cc.math.vec3(0, 0, 0), "Sprite3DTest/girl.c3b", true, 0.2, true);

            var s = cc.winSize;
            var containerForLabel1 = new cc.Node();
            this._ZoomOutlabel = new cc.LabelTTF("zoom out", "Arial", 20);
            this._ZoomOutlabel.setPosition(s.width-50, cc.visibleRect.top.y-30);
            containerForLabel1.addChild(this._ZoomOutlabel);
            this.addChild(containerForLabel1, 10);

            cc.eventManager.addListener({
                event:cc.EventListener.TOUCH_ONE_BY_ONE,
                swallowTouches: true,
                onTouchBegan:this.onTouchZoomOut.bind(this),
                onTouchEnded:this.onTouchZoomOutEnd.bind(this)
            }, this._ZoomOutlabel);

            var containerForLabel2 = new cc.Node();
            this._ZoomInlabel = new cc.LabelTTF("zoom in", "Arial", 20);
            this._ZoomInlabel.setPosition(s.width-50, cc.visibleRect.top.y - 100);
            containerForLabel2.addChild(this._ZoomInlabel);
            this.addChild(containerForLabel2, 10);

            cc.eventManager.addListener({
                event:cc.EventListener.TOUCH_ONE_BY_ONE,
                swallowTouches:true,
                onTouchBegan:this.onTouchZoomIn.bind(this),
                onTouchEnded:this.onTouchZoomInEnd.bind(this)
            }, this._ZoomInlabel);

            var containerForLabel3 = new cc.Node();
            this._RotateLeftlabel = new cc.LabelTTF("rotate left", "Arial", 20);
            this._RotateLeftlabel.setPosition(s.width-50, cc.visibleRect.top.y - 170);
            containerForLabel3.addChild(this._RotateLeftlabel);
            this.addChild(containerForLabel3);

            cc.eventManager.addListener({
                event:cc.EventListener.TOUCH_ONE_BY_ONE,
                swallowTouches:true,
                onTouchBegan:this.onTouchRotateLeft.bind(this),
                onTouchEnded:this.onTouchRotateLeftEnd.bind(this)
            }, this._RotateLeftlabel);

            var containerForLabel4 = new cc.Node();
            this._RotateRightlabel = new cc.LabelTTF("rotate right", "Arial", 20);
            this._RotateRightlabel.setPosition(s.width-50, cc.visibleRect.top.y - 240);
            containerForLabel4.addChild(this._RotateRightlabel);
            this.addChild(containerForLabel4, 10);

            cc.eventManager.addListener({
                event:cc.EventListener.TOUCH_ONE_BY_ONE,
                swallowTouches:true,
                onTouchBegan:this.onTouchRotateRight.bind(this),
                onTouchEnded:this.onTouchRotateRightEnd.bind(this)
            }, this._RotateRightlabel);

            var label1 = new cc.LabelTTF("free", "Arial", 20);
            var item1 = new cc.MenuItemLabel(label1, this.switchViewCallback, this);
            item1.type = CameraType.Free;
            item1.setPosition(cc.visibleRect.left.x+100, cc.visibleRect.top.y-50);

            var label2 = new cc.LabelTTF("third person", "Arial", 20);
            var item2 = new cc.MenuItemLabel(label2, this.switchViewCallback, this);
            item2.type = CameraType.ThirdPerson;
            item2.setPosition(cc.visibleRect.left.x+100, cc.visibleRect.top.y-100);

            var label3 = new cc.LabelTTF("first person", "Arial", 20);
            var item3 = new cc.MenuItemLabel(label3, this.switchViewCallback, this);
            item3.type = CameraType.FirstPerson;
            item3.setPosition(cc.visibleRect.left.x+100, cc.visibleRect.top.y-150);

            var menu = new cc.Menu(item1, item2, item3);
            menu.setPosition(cc.p(0, 0));
            this.addChild(menu);

            this.schedule(this.updateCamera, 0);

            if(this._camera == null){
                this._camera = new cc.Camera(cc.Camera.Mode.PERSPECTIVE, 60, s.width/s.height, 1, 1000);
                this._camera.setCameraFlag(cc.CameraFlag.USER1);
                layer3D.addChild(this._camera);
            }
            this.switchViewCallback(item2);//third person

            var line = new cc.DrawNode3D();
            //draw x
            for(var i = -20; i < 20; ++i)
                line.drawLine(cc.math.vec3(-100, 0, 5*i), cc.math.vec3(100, 0, 5*i), cc.color(255, 0, 0, 1));

            //draw z
            for(var j = -20; j < 20; ++j)
                line.drawLine(cc.math.vec3(5*j, 0, -100), cc.math.vec3(5*j, 0, 100), cc.color(0, 0, 255, 1));

            //draw y
            line.drawLine(cc.math.vec3(0, -50, 0), cc.math.vec3(0, 0, 0), cc.color(0, 128, 0, 1));
            line.drawLine(cc.math.vec3(0, 0, 0), cc.math.vec3(0, 50, 0), cc.color(0, 255, 0, 1));
            layer3D.addChild(line);
            layer3D.setCameraMask(2);
        },

        addNewSpriteWithCoords:function(postion, file, playAnimation, scale, bindCamera){
            var sprite = new jsb.Sprite3D(file);
            this._layer3D.addChild(sprite);
            var globalZOrder = sprite.getGlobalZOrder();
            sprite.setPosition3D(postion);
            sprite.setGlobalZOrder(globalZOrder);
            if(playAnimation){
                var animation = new jsb.Animation3D(file, "Take 001");
                if(animation){
                    var animate = new jsb.Animate3D(animation);
                    sprite.runAction(cc.repeatForever(animate));
                }
            }
            if(bindCamera)
                this._sprite3D = sprite;

            sprite.setScale(scale);
        },

        updateState:function(dt){
            if(!this._targetPos)
                return;
            var curPos = this._sprite3D.getPosition3D();
            var m = this._sprite3D.getNodeToWorldTransform3D();
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

        move3D:function(dt){
            if(!this._targetPos)
                return;
            var curPos = this._sprite3D.getPosition3D();
            var newFaceDir = cc.math.vec3(this._targetPos.x - curPos.x, this._targetPos.y - curPos.y, this._targetPos.z - curPos.z);
            newFaceDir.y = 0;
            newFaceDir.normalize();
            var offset = cc.math.vec3(newFaceDir.x * 25 * dt, newFaceDir.y * 25 * dt, newFaceDir.z * 25 * dt);
            curPos.x += offset.x;
            curPos.y += offset.y;
            curPos.z += offset.z;
            this._sprite3D.setPosition3D(curPos);
            if(this._cameraType == CameraType.ThirdPerson){
                var cameraPos = this._camera.getPosition3D();
                cameraPos.x += offset.x;
                cameraPos.z += offset.z;
                this._camera.setPosition3D(cameraPos);
            }
        },

        updateCamera:function(dt){
            if(this._cameraType == CameraType.ThirdPerson){
                this.updateState(dt)
                
                if(this.isState(State.State_Move)){
                    this.move3D(dt);
                    if(this.isState(State.State_Rotate)){
                        var curPos = this._sprite3D.getPosition3D();
                        var newFaceDir = cc.math.vec3(this._targetPos.x - curPos.x, this._targetPos.y - curPos.y, this._targetPos.z - curPos.z);
                        newFaceDir.y = 0;
                        newFaceDir.normalize();

                        var m = this._sprite3D.getNodeToWorldTransform3D();
                        var up = cc.math.vec3(m[4], m[5], m[6]);
                        up.normalize();

                        var right = cc.math.vec3Cross(cc.math.vec3(-newFaceDir.x, -newFaceDir.y, -newFaceDir.z), up);
                        right.normalize();

                        var mat = [right.x,      right.y,      right.z,      0,
                                   up.x,         up.y,         up.z,         0,
                                   newFaceDir.x, newFaceDir.y, newFaceDir.z, 0,
                                   0,            0,            0,            1];

                        this._sprite3D.setAdditionalTransform(mat);
                    }
                }
            }

            if(this._bZoomOut == true){
                if(this._cameraType == CameraType.ThirdPerson){
                    var cameraPos = this._camera.getPosition3D();
                    var spritePos = this._sprite3D.getPosition3D();
                    var lookDir = cc.math.vec3(cameraPos.x - spritePos.x, cameraPos.y - spritePos.y, cameraPos.z - spritePos.z);
                    if(cc.math.vec3Length(lookDir) <= 300){
                        lookDir.normalize();
                        cameraPos.x += lookDir.x;
                        cameraPos.y += lookDir.y;
                        cameraPos.z += lookDir.z;
                        this._camera.setPosition3D(cameraPos);
                    }
                }else if(this._cameraType == CameraType.Free){
                    var cameraPos = this._camera.getPosition3D();
                    if(cc.math.vec3Length(cameraPos) <= 300){
                        var n = cc.math.vec3Normalize(cameraPos);
                        cameraPos.x += n.x;
                        cameraPos.y += n.y;
                        cameraPos.z += n.z;
                        this._camera.setPosition3D(cameraPos);
                    }
                }
            }

            if(this._bZoomIn == true){
                if(this._cameraType == CameraType.ThirdPerson){
                    var cameraPos = this._camera.getPosition3D();
                    var spritePos = this._sprite3D.getPosition3D();
                    var lookDir = cc.math.vec3(cameraPos.x - spritePos.x, cameraPos.y - spritePos.y, cameraPos.z - spritePos.z);
                    if(cc.math.vec3Length(lookDir) >= 50){
                        lookDir.normalize();
                        cameraPos.x -= lookDir.x;
                        cameraPos.y -= lookDir.y;
                        cameraPos.z -= lookDir.z;
                        this._camera.setPosition3D(cameraPos);
                    }
                }else if(this._cameraType == CameraType.Free){
                    var cameraPos = this._camera.getPosition3D();
                    if(cc.math.vec3Length(cameraPos) >= 50){
                        var n = cc.math.vec3Normalize(cameraPos);
                        cameraPos.x -= n.x;
                        cameraPos.y -= n.y;
                        cameraPos.z -= n.z;
                        this._camera.setPosition3D(cameraPos);
                    }
                }
            }

            if(this._bRotateLeft == true){
                if(this._cameraType == CameraType.Free || this._cameraType == CameraType.FirstPerson){
                    var rotation3D = this._camera.getRotation3D();
                    rotation3D.y += 1;
                    this._camera.setRotation3D(rotation3D);
                }
            }
            if(this._bRotateRight == true){
                if(this._cameraType == CameraType.Free || this._cameraType == CameraType.FirstPerson){
                    var rotation3D = this._camera.getRotation3D();
                    rotation3D.y -= 1;
                    this._camera.setRotation3D(rotation3D);
                }
            }
        },

        isState:function(bit){
            return (this._curState & bit) == bit;
        },

        switchViewCallback:function(sender){
            if(this._cameraType == sender.type)
                return;
            this._cameraType = sender.type;

            if(this._cameraType == CameraType.Free){                var p = this._sprite3D.getPosition3D();
                this._camera.setPosition3D(cc.math.vec3(p.x, p.y+130, p.z+130));

                this._RotateRightlabel.setColor(cc.color.WHITE);
                this._RotateLeftlabel.setColor(cc.color.WHITE);
                this._ZoomInlabel.setColor(cc.color.WHITE);
                this._ZoomOutlabel.setColor(cc.color.WHITE);

            }else if(this._cameraType == CameraType.FirstPerson){
                var m = this._sprite3D.getWorldToNodeTransform3D();
                var newFaceDir = cc.math.vec3(-m[8], -m[9], -m[10]);
                var p = this._sprite3D.getPosition3D();
                this._camera.setPosition3D(cc.math.vec3(p.x, p.y + 35, p.z));
                this._camera.lookAt(cc.math.vec3(p.x + newFaceDir.x*50, p.y + newFaceDir.y*50, p.z+newFaceDir.z*50));

                this._RotateRightlabel.setColor(cc.color.WHITE);
                this._RotateLeftlabel.setColor(cc.color.WHITE);
                this._ZoomInlabel.setColor(cc.color.GRAY);
                this._ZoomOutlabel.setColor(cc.color.GRAY);

            }else{
                var p = this._sprite3D.getPosition3D();
                this._camera.setPosition3D(cc.math.vec3(p.x, p.y+130, p.z+130));
                this._camera.lookAt(p);

                this._RotateRightlabel.setColor(cc.color.GRAY);
                this._RotateLeftlabel.setColor(cc.color.GRAY);
                this._ZoomInlabel.setColor(cc.color.WHITE);
                this._ZoomOutlabel.setColor(cc.color.WHITE);
            }
        },

        onTouchesMoved:function(touches, event){
            if(touches.length == 1){
                var touch = touches[0];
                var location = touch.getLocation();
                var previousLocation = touch.getPreviousLocation();
                var newPos = cc.math.vec3(previousLocation.x - location.x, previousLocation.y - location.y, previousLocation.z - location.z);
                if(this._cameraType == CameraType.Free || this._cameraType == CameraType.FirstPerson){
                    var m = this._camera.getNodeToWorldTransform3D();
                    var cameraDir = cc.math.vec3(-m[8], -m[9], -m[10]);
                    cameraDir.normalize();
                    cameraDir.y = 0;
                    var cameraRightDir = cc.math.vec3(m[0], m[1], m[2]);
                    cameraRightDir.normalize();
                    cameraRightDir.y = 0;

                    var cameraPos = this._camera.getPosition3D();
                    cameraPos.x += cameraDir.x*newPos.y*0.1 + cameraRightDir.x*newPos.x*0.1;
                    cameraPos.y += cameraDir.y*newPos.y*0.1 + cameraRightDir.y*newPos.x*0.1;
                    cameraPos.z += cameraDir.z*newPos.y*0.1 + cameraRightDir.z*newPos.x*0.1;
                    this._camera.setPosition3D(cameraPos);
                    if(this._sprite3D && this._cameraType == CameraType.FirstPerson){
                        this._sprite3D.setPosition3D(cc.math.vec3(this._camera.x, 0, this._camera.getVertexZ()));
                        this._targetPos = this._sprite3D.getPosition3D();
                    }
                }                
            }
        },

        onTouchesEnded:function(touches, event){
            for(var i in touches){
                var touch = touches[i];
                var location = touch.getLocationInView();
                if(this._sprite3D && this._cameraType == CameraType.ThirdPerson && this._bZoomOut == false && this._bZoomIn == false && this._bRotateLeft == false && this._bRotateRight == false){
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
        },

        onTouchZoomOut:function(touch, event){
            var target = event.getCurrentTarget();
            var locationInNode = target.convertToNodeSpace(touch.getLocation());
            var s = target.getContentSize();
            var rect = cc.rect(0, 0, s.width, s.height);
            if(cc.rectContainsPoint(rect, locationInNode)){
                this._bZoomOut = true;
                return true;
            }
            return false;
        },

        onTouchZoomOutEnd:function(touch, event){
            this._bZoomOut = false;
        },

        onTouchZoomIn:function(touch, event){
            var target = event.getCurrentTarget();
            var locationInNode = target.convertToNodeSpace(touch.getLocation());
            var s = target.getContentSize();
            var rect = cc.rect(0, 0, s.width, s.height);
            if(cc.rectContainsPoint(rect, locationInNode)){
                this._bZoomIn = true;
                return true;
            }
            return false;
        },

        onTouchZoomInEnd:function(touch, event){
            this._bZoomIn = false;
        },

        onTouchRotateLeft:function(touch, event){
            var target = event.getCurrentTarget();
            var locationInNode = target.convertToNodeSpace(touch.getLocation());
            var s = target.getContentSize();
            var rect = cc.rect(0, 0, s.width, s.height);
            if(cc.rectContainsPoint(rect, locationInNode)){
                this._bRotateLeft = true;
                return true;
            }
            return false;
        },

        onTouchRotateLeftEnd:function(touch, event){
            this._bRotateLeft = false;
        },

        onTouchRotateRight:function(touch, event){
            var target = event.getCurrentTarget();
            var locationInNode = target.convertToNodeSpace(touch.getLocation());
            var s = target.getContentSize();
            var rect = cc.rect(0, 0, s.width, s.height);
            if(cc.rectContainsPoint(rect, locationInNode)){
                this._bRotateRight = true;
                return true;
            }
            return false;
        },

        onTouchRotateRightEnd:function(touch, event){
            this._bRotateRight = false;
        }
    });
})();

var CameraCullingDemo = Camera3DTestDemo.extend({
    _title:"Camera Frustum Clipping",
    _subtitle:"",
    _objects:[],
    _layer3D:null,
    _labelSprite3DCount:null,
    _drawAABB:null,
    _drawFrustum:null,
    _row:3,
    _cameraType:CameraType.FirstPerson,
    _cameraFirst:null,
    _cameraThird:null,
    _moveAction:null,

    ctor:function(){
        this._super();

        this.scheduleUpdate();

        var layer3D = new cc.Layer();
        this.addChild(layer3D, 0);
        this._layer3D = layer3D;

        // swich camera
        cc.MenuItemFont.setFontName("Arial");
        cc.MenuItemFont.setFontSize(20);

        var menuItem1 = new cc.MenuItemFont("Switch Camera", this.switchViewCallback, this);
        menuItem1.setColor(cc.color(0, 200, 20));
        var menu = new cc.Menu(menuItem1);
        menu.setPosition(cc.p(0, 0));
        menuItem1.setPosition(cc.visibleRect.left.x + 80, cc.visibleRect.top.y - 70);
        this.addChild(menu);

        // + -
        cc.MenuItemFont.setFontSize(40);
        var decrease = new cc.MenuItemFont(" - ", this.delSpriteCallback, this);
        decrease.setColor(cc.color(0, 200, 20));
        var increase = new cc.MenuItemFont(" + ", this.addSpriteCallback, this);
        increase.setColor(cc.color(0, 200, 20));

        menu = new cc.Menu(decrease, increase);
        menu.alignItemsHorizontally();
        menu.setPosition(cc.winSize.width - 60, cc.visibleRect.top.y - 70);
        this.addChild(menu, 1);

        this._labelSprite3DCount = new cc.LabelTTF("0 sprites", "Marker Felt", 30);
        this._labelSprite3DCount.setColor(cc.color(0, 200, 20));
        this._labelSprite3DCount.setPosition(cc.p(cc.winSize.width / 2, cc.visibleRect.top.y - 70));
        this.addChild(this._labelSprite3DCount);

        // aabb drawNode3D
        this._drawAABB = new cc.DrawNode3D();
        this._drawAABB.setCameraMask(cc.CameraFlag.USER1);
        this.addChild(this._drawAABB);

        // frustum drawNode3D
        this._drawFrustum = new cc.DrawNode3D();
        this._drawFrustum.setCameraMask(cc.CameraFlag.USER1);
        this.addChild(this._drawFrustum);

        // set camera
        this.switchViewCallback();

        // add sprite
        this.addSpriteCallback();
    },

    onExit:function(){
        this._super();
        this._moveAction.release();
    },

    switchViewCallback:function(sender){
        if(!this._cameraFirst){
            var camera = new cc.Camera(cc.Camera.Mode.PERSPECTIVE, 30, cc.winSize.width/cc.winSize.height, 10, 200);
            camera.setCameraFlag(cc.CameraFlag.USER8);
            camera.setPosition3D(cc.math.vec3(-100, 0, 0));
            camera.lookAt(cc.math.vec3(1000, 0, 0));
            this._moveAction = cc.moveBy(4, cc.p(200, 0));
            this._moveAction.retain();
            var seq = cc.sequence(this._moveAction, cc.callFunc(this.reachEndCallBack, this));
            seq.setTag(100);
            camera.runAction(seq);
            this.addChild(camera);
            this._cameraFirst = camera;
        }

        if(!this._cameraThird){
            var camera = new cc.Camera(cc.Camera.Mode.PERSPECTIVE, 60, cc.winSize.width/ cc.winSize.height, 1, 1000);
            camera.setCameraFlag(cc.CameraFlag.USER8);
            camera.setPosition3D(cc.math.vec3(0, 130, 130));
            camera.lookAt(cc.math.vec3(0, 0, 0));
            this.addChild(camera);
            this._cameraThird = camera;
        }

        if(this._cameraType == CameraType.FirstPerson){
            this._cameraType = CameraType.ThirdPerson;
            this._cameraThird.setCameraFlag(cc.CameraFlag.USER1);
            this._cameraFirst.setCameraFlag(cc.CameraFlag.USER8);
        }else if(this._cameraType == CameraType.ThirdPerson){
            this._cameraType = CameraType.FirstPerson;
            this._cameraThird.setCameraFlag(cc.CameraFlag.USER8);
            this._cameraFirst.setCameraFlag(cc.CameraFlag.USER1);
            this._drawFrustum.clear();
        }
    },

    reachEndCallBack:function(){
        this._cameraFirst.stopActionByTag(100);
        var inverse = this._moveAction.reverse();
        inverse.retain();
        this._moveAction.release();
        this._moveAction = inverse;
        var rot = cc.rotateBy(1, cc.math.vec3(0, 180, 0));
        var seq = cc.sequence(rot, this._moveAction, cc.callFunc(this.reachEndCallBack, this));
        seq.setTag(100);
        this._cameraFirst.runAction(seq);
    },

    delSpriteCallback:function(sender){
        if(this._row == 0)
            return;

        this._layer3D.removeAllChildren();
        this._objects.length = 0;
        
        this._row--;
        for(var x = -this._row; x < this._row; ++x){
            for(var z = -this._row; z < this._row; ++z){
                var sprite = new jsb.Sprite3D("Sprite3DTest/orc.c3b");
                sprite.setPosition3D(cc.math.vec3(x * 30, 0, z * 30));
                sprite.setRotation3D(cc.math.vec3(0, 180, 0));
                this._objects.push(sprite);
                this._layer3D.addChild(sprite);
            }
        }

        //set layer mask
        this._layer3D.setCameraMask(cc.CameraFlag.USER1);

        //update sprite number
        this._labelSprite3DCount.setString(this._layer3D.getChildrenCount() + " sprites");
    },

    addSpriteCallback:function(sender){
        this._layer3D.removeAllChildren();
        this._objects.length = 0;
        this._drawAABB.clear();

        this._row++;
        for(var x = -this._row; x < this._row; ++x){
            for(var z = -this._row; z < this._row; ++z){
                var sprite = new jsb.Sprite3D("Sprite3DTest/orc.c3b");
                sprite.setPosition3D(cc.math.vec3(x * 30, 0, z * 30));
                sprite.setRotation3D(cc.math.vec3(0, 180, 0));
                this._objects.push(sprite);
                this._layer3D.addChild(sprite);
            }
        }

        //set layer mask
        this._layer3D.setCameraMask(cc.CameraFlag.USER1);

        //update sprite number
        this._labelSprite3DCount.setString(this._layer3D.getChildrenCount() + " sprites");
    },

    update:function(dt){
        this._drawAABB.clear();

        if(this._cameraType == CameraType.ThirdPerson)
            this.drawCameraFrustum();

        var children = this._layer3D.getChildren();

        for(var i in children){
            var aabb = children[i].getAABB();
            if(this._cameraFirst.isVisibleInFrustum(aabb)){
                var corners = cc.math.aabbGetCorners(aabb);
                this._drawAABB.drawCube(corners, cc.color(0, 255, 0));
            }
        }
    },

    drawCameraFrustum:function(){
        this._drawFrustum.clear();
        var size = cc.winSize;
        var color = cc.color(255, 255, 0);

        // top-left
        var src = cc.math.vec3(0, 0, 0);
        var tl_0 = this._cameraFirst.unproject(src);
        src = cc.math.vec3(0, 0, 1);
        var tl_1 = this._cameraFirst.unproject(src);

        // top-right
        src = cc.math.vec3(size.width, 0, 0);
        var tr_0 = this._cameraFirst.unproject(src);
        src = cc.math.vec3(size.width, 0, 1);
        var tr_1 = this._cameraFirst.unproject(src);

        // bottom-left
        src = cc.math.vec3(0, size.height, 0);
        var bl_0 = this._cameraFirst.unproject(src);
        src = cc.math.vec3(0, size.height, 1);
        var bl_1 = this._cameraFirst.unproject(src);

        // bottom-right
        src = cc.math.vec3(size.width, size.height, 0);
        var br_0 = this._cameraFirst.unproject(src);
        src = cc.math.vec3(size.width, size.height, 1);
        var br_1 = this._cameraFirst.unproject(src);

        this._drawFrustum.drawLine(tl_0, tl_1, color);
        this._drawFrustum.drawLine(tr_0, tr_1, color);
        this._drawFrustum.drawLine(bl_0, bl_1, color);
        this._drawFrustum.drawLine(br_0, br_1, color);
        
        this._drawFrustum.drawLine(tl_0, tr_0, color);
        this._drawFrustum.drawLine(tr_0, br_0, color);
        this._drawFrustum.drawLine(br_0, bl_0, color);
        this._drawFrustum.drawLine(bl_0, tl_0, color);
        
        this._drawFrustum.drawLine(tl_1, tr_1, color);
        this._drawFrustum.drawLine(tr_1, br_1, color);
        this._drawFrustum.drawLine(br_1, bl_1, color);
        this._drawFrustum.drawLine(bl_1, tl_1, color);
    }
});

var CameraArcBallDemo = Camera3DTestDemo.extend({
    _title:"Camera ArcBall Moving",
    _subtitle:"",
    _rotationQuat: null,
    _layer3D:null,
    _camera:null,
    _sprite3D1:null,
    _sprite3D2:null,
    _drawGrid:null,
    _operate:OperateCamType.RotateCamera,
    _target:0,
    _center:cc.math.vec3(0, 0, 0),
    _distanceZ:50,
    _radius:1,

    ctor:function(){
        this._super();
        this._rotationQuat = cc.math.quaternion(0, 0, 0, 1);
        cc.eventManager.addListener({
            event:cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesMoved:this.onTouchesMoved.bind(this)
        }, this);

        cc.MenuItemFont.setFontName("Arial");
        cc.MenuItemFont.setFontSize(20);

        var item1 = new cc.MenuItemFont("Switch Operation", this.switchOperateCallback, this);
        item1.setColor(cc.color(0, 200, 20));
        var item2 = new cc.MenuItemFont("Switch Target", this.switchTargetCallback, this);
        item2.setColor(cc.color(0, 200, 20));
        var menu = new cc.Menu(item1, item2);
        menu.setPosition(cc.p(0, 0));
        item1.setPosition(cc.visibleRect.left.x + 80, cc.visibleRect.top.y - 70);
        item2.setPosition(cc.visibleRect.left.x + 80, cc.visibleRect.top.y - 100);
        this.addChild(menu, 1);

        var layer3D = new cc.Layer();
        this.addChild(layer3D);
        this._layer3D = layer3D;

        this._camera = new cc.Camera(cc.Camera.Mode.PERSPECTIVE, 60, cc.winSize.width/cc.winSize.height, 1, 1000);
        this._camera.setCameraFlag(cc.CameraFlag.USER1);
        this._camera.setPosition3D(cc.math.vec3(0, 10, 50));
        this._camera.lookAt(cc.math.vec3(0, 0, 0), cc.math.vec3(0, 1, 0));
        layer3D.addChild(this._camera);

        this._sprite3D1 = new jsb.Sprite3D("Sprite3DTest/orc.c3b");
        this._sprite3D1.setScale(0.5);
        this._sprite3D1.setRotation3D(cc.math.vec3(0, 180, 0));
        this._sprite3D1.setPosition3D(cc.math.vec3(0, 0, 0));
        layer3D.addChild(this._sprite3D1);

        this._sprite3D2 = new jsb.Sprite3D("Sprite3DTest/boss.c3b");
        this._sprite3D2.setScale(0.6);
        this._sprite3D2.setRotation3D(cc.math.vec3(-90, 0, 0));
        this._sprite3D2.setPosition3D(cc.math.vec3(20, 0, 0));
        layer3D.addChild(this._sprite3D2);

        this._drawGrid = new cc.DrawNode3D();
        //draw x
        for(var i = -20; i < 20; ++i)
            this._drawGrid.drawLine(cc.math.vec3(-100, 0, 5*i), cc.math.vec3(100, 0, 5*i), cc.color(0, 0, 255));

        //draw z
        for(var j = -20; j < 20; ++j)
            this._drawGrid.drawLine(cc.math.vec3(5*j, 0, -100), cc.math.vec3(5*j, 0, 100), cc.color(0, 255, 0));

        //draw y
        this._drawGrid.drawLine(cc.math.vec3(0, 0, 0), cc.math.vec3(0, 50, 0), cc.color(0, 255, 0));

        layer3D.addChild(this._drawGrid);
        layer3D.setCameraMask(2);
        this.updateCameraTransform();
    },

    updateCameraTransform:function(){
        var trans = cc.math.mat4CreateTranslation(cc.math.vec3(0, 10, this._distanceZ));
        var rot = cc.math.mat4CreateRotation(this._rotationQuat);
        var center = cc.math.mat4CreateTranslation(this._center);

        var result = cc.math.mat4Multiply(cc.math.mat4Multiply(center, rot), trans);
        this._camera.setNodeToParentTransform(result);
    },

    switchOperateCallback:function(sender){
        if(this._operate === OperateCamType.MoveCamera)
            this._operate = OperateCamType.RotateCamera;
        else if(this._operate === OperateCamType.RotateCamera)
            this._operate =  OperateCamType.MoveCamera;
    },

    switchTargetCallback:function(sender){
        if(this._target === 0 ){
            this._target = 1;
            this._center = this._sprite3D2.getPosition3D();
            this.updateCameraTransform();
        }else if(this._target === 1){
            this._target = 0;
            this._center = this._sprite3D1.getPosition3D();
            this.updateCameraTransform();
        }
    },

    onTouchesMoved:function(touches, event){
        if(touches.length > 0){
            if(this._operate === OperateCamType.RotateCamera){    //arc ball rotate
                var visibleSize = cc.director.getVisibleSize();
                var prelocation = touches[0].getPreviousLocationInView();
                var location = touches[0].getLocationInView();
                location.x = 2 * location.x / visibleSize.width - 1;
                location.y = 2 * (visibleSize.height - location.y) / visibleSize.height - 1;
                prelocation.x = 2 * prelocation.x / visibleSize.width - 1;
                prelocation.y = 2 * (visibleSize.height - prelocation.y) / visibleSize.height - 1;    

                var quat = this.calculateArcBall(prelocation.x, prelocation.y, location.x, location.y);    //calculate  rotation cc.math.quaternion parameters
                this._rotationQuat = cc.math.quatMultiply(quat, this._rotationQuat);

                this.updateCameraTransform();
            }else if(this._operate === OperateCamType.MoveCamera){ //camera zoom
                var newPos = cc.pSub(touches[0].getPreviousLocation(), touches[0].getLocation());
                this._distanceZ -= newPos.y * 0.1;

                this.updateCameraTransform();
            }
        }
    },

    calculateArcBall:function(p1x, p1y, p2x, p2y){
        var axis, angle;

        var rotation_matrix = cc.math.mat4CreateRotation(this._rotationQuat);

        var uv = cc.math.mat4MultiplyVec3(rotation_matrix, cc.math.vec3(0, 1, 0)); //rotation y
        var sv = cc.math.mat4MultiplyVec3(rotation_matrix, cc.math.vec3(1, 0, 0)); //rotation x
        var lv = cc.math.mat4MultiplyVec3(rotation_matrix, cc.math.vec3(0, 0, -1));//rotation z

        var z = this.projectToSphere(this._radius, p1x, p1y);
        var p1 = cc.math.vec3Sub(cc.math.vec3Add(cc.math.vec3(sv.x * p1x, sv.y * p1x, sv.z * p1x), cc.math.vec3(uv.x * p1y, uv.y * p1y, uv.z *p1y)), cc.math.vec3(lv.x * z, lv.y * z, lv.z * z));  //start point screen transform to 3d
        z = this.projectToSphere(this._radius, p2x, p2y);
        var p2 = cc.math.vec3Sub(cc.math.vec3Add(cc.math.vec3(sv.x * p2x, sv.y * p2x, sv.z * p2x), cc.math.vec3(uv.x * p2y, uv.y * p2y, uv.z *p2y)), cc.math.vec3(lv.x * z, lv.y * z, lv.z * z));  //end point screen transform to 3d

        axis = cc.math.vec3Cross(p2, p1); //calculate rotation axis
        axis.normalize();

        var t = cc.math.vec3Length(cc.math.vec3Sub(p2, p1)) / (2 * this._radius);
        //clamp -1 to 1
        if(t > 1) t = 1;
        if(t < -1) t = -1;
        angle = Math.asin(t);      //rotation angle*/

        return cc.math.quaternion(axis, angle)
    },

    /* project an x,y pair onto a sphere of radius r or a
    hyperbolic sheet if we are away from the center of the sphere. */
    projectToSphere:function(r, x, y){
        var d = Math.sqrt(x*x + y*y);
        var t, z;
        if(d < r * 0.70710678118654752440)//inside sphere
            z = Math.sqrt(r*r - d*d)
        else{
            t = r / 1.41421356237309504880;
            z = t*t / d;
        }
        return z;
    }
});

var FogTestDemo = Camera3DTestDemo.extend({
    _title:"Fog Test Demo",
    _subtitle:"",
    _sprite3D1:null,
    _sprite3D2:null,
    _camera:null,
    _state:null,

    ctor:function(){
        this._super();
        cc.director.setClearColor(cc.color(128, 128, 128));

        cc.eventManager.addListener({
            event:cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesMoved:this.onTouchesMoved.bind(this)
        }, this);

        // swich fog type
        var label1 = new cc.LabelTTF("Linear", "Arial", 20);
        var item1 = new cc.MenuItemLabel(label1, this.switchTypeCallback, this);
        item1.setUserData(0);
        var label2 = new cc.LabelTTF("Exp", "Arial", 20);
        var item2 = new cc.MenuItemLabel(label2, this.switchTypeCallback, this);
        item2.setUserData(1);
        var label3 = new cc.LabelTTF("Exp2", "Arial", 20);
        var item3 = new cc.MenuItemLabel(label3, this.switchTypeCallback, this);
        item3.setUserData(2);
        var menu = new cc.Menu(item1, item2, item3);
        menu.setPosition(cc.p(0, 0));

        item1.setPosition(cc.visibleRect.left.x + 60, cc.visibleRect.top.y - 50);
        item2.setPosition(cc.visibleRect.left.x + 60, cc.visibleRect.top.y - 100);
        item3.setPosition(cc.visibleRect.left.x + 60, cc.visibleRect.top.y - 150);
        this.addChild(menu, 0);

        var layer3D = new cc.Layer();
        this.addChild(layer3D, 0);

        var shader = new cc.GLProgram("Sprite3DTest/fog.vert", "Sprite3DTest/fog.frag");
        var state = cc.GLProgramState.create(shader);
        this._state = state;

        this._sprite3D1 = new jsb.Sprite3D("Sprite3DTest/teapot.c3b");
        this._sprite3D2 = new jsb.Sprite3D("Sprite3DTest/teapot.c3b");

        this._sprite3D1.setGLProgramState(state);
        this._sprite3D2.setGLProgramState(state);

        //pass mesh's attribute to shader
        var offset = 0;
        var attributeCount = this._sprite3D1.getMesh().getMeshVertexAttribCount();
        for(var i = 0; i < attributeCount; ++i){
            var meshattribute = this._sprite3D1.getMesh().getMeshVertexAttribute(i);
            state.setVertexAttribPointer(cc.attributeNames[meshattribute.vertexAttrib],
                meshattribute.size,
                meshattribute.type,
                gl.FALSE,
                this._sprite3D1.getMesh().getVertexSizeInBytes(),
                offset);
            offset += meshattribute.attribSizeBytes;
        }

        var offset1 = 0;
        var attributeCount = this._sprite3D2.getMesh().getMeshVertexAttribCount();
        for(var i = 0; i < attributeCount; ++i){
            var meshattribute = this._sprite3D2.getMesh().getMeshVertexAttribute(i);
            state.setVertexAttribPointer(cc.attributeNames[meshattribute.vertexAttrib],
                meshattribute.size,
                meshattribute.type,
                gl.FALSE,
                this._sprite3D2.getMesh().getVertexSizeInBytes(),
                offset1);
            offset1 += meshattribute.attribSizeBytes;
        }

        state.setUniformVec4("u_fogColor", cc.math.vec4(0.5, 0.5, 0.5, 1.0));
        state.setUniformFloat("u_fogStart", 10);
        state.setUniformFloat("u_fogEnd", 60);
        state.setUniformInt("u_fogEquation", 0);

        layer3D.addChild(this._sprite3D1);
        this._sprite3D1.setPosition3D(cc.math.vec3(0, 0, 0));
        this._sprite3D1.setScale(2);
        this._sprite3D1.setRotation3D(cc.math.vec3(-90, 180, 0));

        layer3D.addChild(this._sprite3D2);
        this._sprite3D2.setPosition3D(cc.math.vec3(0, 0, -20));
        this._sprite3D2.setScale(2);
        this._sprite3D2.setRotation3D(cc.math.vec3(-90, 180, 0));

        this._camera = new cc.Camera(cc.Camera.Mode.PERSPECTIVE, 60, cc.winSize.width/cc.winSize.height, 1, 1000);
        this._camera.setCameraFlag(cc.CameraFlag.USER1);
        this._camera.setPosition3D(cc.math.vec3(0, 30, 40));
        this._camera.lookAt(cc.math.vec3(0, 0, 0), cc.math.vec3(0, 1, 0));
        layer3D.addChild(this._camera);
        layer3D.setCameraMask(2);
    },

    onExit:function(){
        this._super();
        cc.director.setClearColor(cc.color(0, 0, 0));
    },

    switchTypeCallback:function(sender){
        var type = sender.getUserData();
        if(type === 0){
            this._state.setUniformVec4("u_fogColor", cc.math.vec4(0.5, 0.5, 0.5, 1.0));
            this._state.setUniformFloat("u_fogStart", 10);
            this._state.setUniformFloat("u_fogEnd", 60);
            this._state.setUniformInt("u_fogEquation", 0);

            this._sprite3D1.setGLProgramState(this._state);
            this._sprite3D2.setGLProgramState(this._state);
        }else if(type === 1){
            this._state.setUniformVec4("u_fogColor", cc.math.vec4(0.5, 0.5, 0.5, 1.0));
            this._state.setUniformFloat("u_fogDensity", 0.03);
            this._state.setUniformInt("u_fogEquation", 1);

            this._sprite3D1.setGLProgramState(this._state);
            this._sprite3D2.setGLProgramState(this._state);
        }else if(type === 2){
            this._state.setUniformVec4("u_fogColor", cc.math.vec4(0.5, 0.5, 0.5, 1.0));
            this._state.setUniformFloat("u_fogDensity", 0.03);
            this._state.setUniformInt("u_fogEquation", 2);

            this._sprite3D1.setGLProgramState(this._state);
            this._sprite3D2.setGLProgramState(this._state);
        }
    },

    onTouchesMoved:function(touches, event){
        if(touches.length === 1){
            var prelocation = touches[0].getPreviousLocationInView();
            var location = touches[0].getLocationInView();
            var newPos = cc.math.vec3Sub(prelocation, location);

            var m = this._camera.getNodeToWorldTransform3D();
            var cameraDir = cc.math.vec3(-m[8], -m[9], -m[10]);
            cameraDir.normalize();
            cameraDir.y = 0;
            var cameraRightDir = cc.math.vec3(m[0], m[1], m[2]);
            cameraRightDir.normalize();
            cameraRightDir.y = 0;

            var cameraPos = this._camera.getPosition3D();
            cameraPos.x += cameraDir.x*newPos.y*0.1 + cameraRightDir.x*newPos.x*0.1;
            cameraPos.y += cameraDir.y*newPos.y*0.1 + cameraRightDir.y*newPos.x*0.1;
            cameraPos.z += cameraDir.z*newPos.y*0.1 + cameraRightDir.z*newPos.x*0.1;
            this._camera.setPosition3D(cameraPos);
        }
    }
});

//
// Flow control
//
var arrayOfCamera3DTest = [
    CameraRotationTest,
    Camera3DTest,
    CameraCullingDemo,
    CameraArcBallDemo
];

if(cc.sys.os !== cc.sys.OS_WP8 || cc.sys.os !== cc.sys.OS_WINRT){
    arrayOfCamera3DTest.push(FogTestDemo);
}

var nextCamera3DTest = function () {
    Camera3DTestIdx++;
    Camera3DTestIdx = Camera3DTestIdx % arrayOfCamera3DTest.length;

    return new arrayOfCamera3DTest[Camera3DTestIdx ]();
};
var previousCamera3DTest = function () {
    Camera3DTestIdx--;
    if (Camera3DTestIdx < 0)
        Camera3DTestIdx += arrayOfCamera3DTest.length;

    return new arrayOfCamera3DTest[Camera3DTestIdx ]();
};
var restartCamera3DTest = function () {
    return new arrayOfCamera3DTest[Camera3DTestIdx ]();
};
