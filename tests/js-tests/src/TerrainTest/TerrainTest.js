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
if(cc.sys.isNative)(function(){

var TerrainTestIdx = -1;

var TerrainTestDemo = cc.Layer.extend({
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
        var s = new TerrainTestScene();
        s.addChild(restartTerrainTest());
        director.runScene(s);
    },

    onNextCallback:function (sender) {
        var s = new TerrainTestScene();
        s.addChild(nextTerrainTest());
        director.runScene(s);
    },

    onBackCallback:function (sender) {
        var s = new TerrainTestScene();
        s.addChild(previousTerrainTest());
        director.runScene(s);
    },
});

TerrainTestScene = cc.Scene.extend({
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
        TerrainTestIdx = (num || num == 0) ? (num - 1) : -1;
        var layer = nextTerrainTest();
        this.addChild(layer);

        director.runScene(this);
    }
});

var TerrainSimple = TerrainTestDemo.extend({
    _title:"Terrain with skirt",
    _subtitle:"Drag to walkthru",
    _camera:null,

    ctor:function(){
        this._super();

        var visibleSize = cc.director.getVisibleSize();

        //use custom camera
        this._camera = new cc.Camera(cc.Camera.Mode.PERSPECTIVE, 60,visibleSize.width/visibleSize.height,0.1,800);
        this._camera.setCameraFlag(cc.CameraFlag.USER1);
        this._camera.setPosition3D(cc.math.vec3(-1, 1.6, 4));
        this.addChild(this._camera);

        var r = jsb.Terrain.detailMap("TerrainTest/dirt.jpg", 35),
            g = jsb.Terrain.detailMap("TerrainTest/Grass2.jpg", 35),
            b = jsb.Terrain.detailMap("TerrainTest/road.jpg", 35),
            a = jsb.Terrain.detailMap("TerrainTest/GreenSkin.jpg", 35);
        var data = jsb.Terrain.terrainData(
            "TerrainTest/heightmap16.jpg",
            "TerrainTest/alphamap.png",
            [r, g, b, a],
            cc.size(32,32),
            2,
            0.1
        );

        var terrain = new jsb.Terrain(data, jsb.Terrain.CrackFixedType.SKIRT);
        terrain.setLODDistance(3.2,6.4,9.6);
        terrain.setMaxDetailMapAmount(4);
        this.addChild(terrain);
        terrain.setCameraMask(2);
        terrain.setDrawWire(false);

        cc.eventManager.addListener({
            event:cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesMoved:this.onTouchesMoved.bind(this)
        }, this);

        var rootps = jsb.PUParticleSystem3D.create("Particle3D/scripts/mp_torch.pu");
        rootps.setCameraMask(2);
        rootps.startParticleSystem();

        this.addChild(rootps, 0, 0);
    },

    onTouchesMoved:function(touches, event){
        var delta = cc.director.getDeltaTime();
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
        cameraPos.x += cameraDir.x * newPos.y * 0.5 *delta + cameraRightDir.x * newPos.x * 0.5 *delta;
        cameraPos.y += cameraDir.y * newPos.y * 0.5 *delta + cameraRightDir.y * newPos.x * 0.5 *delta;
        cameraPos.z += cameraDir.z * newPos.y * 0.5 *delta + cameraRightDir.z * newPos.x * 0.5 *delta;
        this._camera.setPosition3D(cameraPos);
    }
});

var TerrainWalkThru = (function(){
    var PlayerState = {
        LEFT : 0,
        RIGHT : 1,
        IDLE : 2,
        FORWARD : 3,
        BACKWARD : 4
    };

    var PLAYER_HEIGHT = 0;
    var camera_offset = cc.math.vec3(0, 45, 60);

    var Player = jsb.Sprite3D.extend({
        _targetPos:null,
        _headingAxis:null,
        _headingAngle:0,
        _playerState:PlayerState.IDLE,
        _camera:null,
        _terrain:null,

        ctor:function(file, camera, terrain){
            this._super(file);
            this._camera = camera;
            this._terrain = terrain;
            this.scheduleUpdate();
        },

        update:function(dt){
            switch(this._playerState){
            case PlayerState.IDLE:
                break;
            case PlayerState.FORWARD:
                var curPos = this.getPosition3D();
                var newFaceDir = cc.math.vec3Sub(this._targetPos, curPos);
                newFaceDir.y = 0;
                newFaceDir.normalize();
                curPos.x += newFaceDir.x * 25 * dt;
                curPos.y += newFaceDir.y * 25 * dt;
                curPos.z += newFaceDir.z * 25 * dt;
                this.setPosition3D(curPos);
                break;
            case PlayerState.BACKWARD:
                break;
            case PlayerState.LEFT:
                this.setRotation3D(cc.math.vec3Add(this.getRotation3D(), cc.math.vec3(0, 25*dt, 0)));
                break;
            case PlayerState.RIGHT:
                this.setRotation3D(cc.math.vec3Add(this.getRotation3D(), cc.math.vec3(0, -25*dt, 0)));
                break;
            default:
                break;
            }

            var player_h = this._terrain.getHeight(this.getPositionX(), this.getVertexZ());
            this.y = player_h + PLAYER_HEIGHT;
            this._camera.setPosition3D(cc.math.vec3Add(this.getPosition3D(), camera_offset));

            if(this._headingAxis){
                var quat = cc.math.quaternion(cc.math.vec3(0, 1, 0), -Math.PI);
                var headingQ = cc.math.quaternion(this._headingAxis, this._headingAngle);
                this.setRotationQuat(cc.math.quatMultiply(quat, headingQ));
            }

            this.updateState();
        },

        turnLeft:function(){
            this._playerState = PlayerState.LEFT;
        },

        turnRight:function(){
            this._playerState = PlayerState.RIGHT;
        },

        forward:function(){
            this._playerState = PlayerState.FORWARD;
        },

        backward:function(){
            this._playerState = PlayerState.BACKWARD;
        },

        idle:function(){
            this._playerState = PlayerState.IDLE;
        },

        updateState:function(){
            if(this._playerState === PlayerState.FORWARD){
                var playerPos = cc.p(this.getPositionX(), this.getVertexZ());
                var targetPos = cc.p(this._targetPos.x, this._targetPos.z);
                var dist = cc.pDistance(playerPos, targetPos);
                if(dist < 1){
                    this._playerState = PlayerState.IDLE;
                }
            }
        }
    });

    return TerrainTestDemo.extend({
        _title:"Player walk around in terrain",
        _subtitle:"touch to move",
        _camera:null,
        _player:null,
        _terrain:null,

        ctor:function(){
            this._super();

            cc.eventManager.addListener({
                event:cc.EventListener.TOUCH_ALL_AT_ONCE,
                onTouchesEnded:this.onTouchesEnded.bind(this)
            }, this);

            var visibleSize = cc.director.getVisibleSize();
            this._camera = new cc.Camera(cc.Camera.Mode.PERSPECTIVE, 60, visibleSize.width/visibleSize.height, 0.1, 200);
            this._camera.setCameraFlag(cc.CameraFlag.USER1);
            this.addChild(this._camera);

            var r = jsb.Terrain.detailMap("TerrainTest/dirt.jpg"),
                g = jsb.Terrain.detailMap("TerrainTest/Grass2.jpg", 10),
                b = jsb.Terrain.detailMap("TerrainTest/road.jpg"),
                a = jsb.Terrain.detailMap("TerrainTest/GreenSkin.jpg", 20);
            var data = jsb.Terrain.terrainData(
                "TerrainTest/heightmap16.jpg",
                "TerrainTest/alphamap.png",
                [r, g, b, a],
                cc.size(32,32),
                40.0,
                2
            );

            this._terrain = new jsb.Terrain(data, jsb.Terrain.CrackFixedType.SKIRT);
            this._terrain.setLODDistance(64, 128, 192);
            this._terrain.setMaxDetailMapAmount(4);
            this._terrain.setCameraMask(2);
            this._terrain.setDrawWire(false);
            this._terrain.setSkirtHeightRatio(3);
            this.addChild(this._terrain);

            this._player = new Player("Sprite3DTest/girl.c3b", this._camera, this._terrain);
            this._player.setCameraMask(2);
            this._player.setScale(0.08);
            this._player.y = this._terrain.getHeight(this._player.x, this._player.getVertexZ()) + PLAYER_HEIGHT;

            var animation = new jsb.Animation3D("Sprite3DTest/girl.c3b", "Take 001");
            if(animation){
                var animate = new jsb.Animate3D(animation);
                this._player.runAction(cc.repeatForever(animate));
            }

            this.addChild(this._player);

            this._camera.setPosition3D(cc.math.vec3Add(this._player.getPosition3D(), camera_offset));
            this._camera.setRotation3D(cc.math.vec3(-45, 0, 0));
        },

        onTouchesEnded:function(touches, event){
            var touch = touches[0];
            var location = touch.getLocationInView();
            if(this._camera && this._player){
                var nearP = cc.math.vec3(location.x, location.y, 0);
                var farP = cc.math.vec3(location.x, location.y, 1);

                nearP = this._camera.unproject(nearP);
                farP = this._camera.unproject(farP);

                var dir = cc.math.vec3Sub(farP, nearP);
                dir.normalize();
                var rayStep = cc.math.vec3(15*dir.x, 15*dir.y, 15*dir.z);
                var rayPos = nearP;
                var rayStartPosition = nearP;
                var lastRayPosition = rayPos;
                rayPos.x += rayStep.x;
                rayPos.y += rayStep.y;
                rayPos.z += rayStep.z;

                // Linear search - Loop until find a point inside and outside the terrain Vector3
                var height = this._terrain.getHeight(rayPos.x, rayPos.z);
                while(rayPos.y > height){
                    lastRayPosition = rayPos;
                    rayPos.x += rayStep.x;
                    rayPos.y += rayStep.y;
                    rayPos.z += rayStep.z;
                    height = this._terrain.getHeight(rayPos.x, rayPos.z);
                }

                var startPosition = lastRayPosition;
                var endPosition = rayPos;

                for(var i = 0; i < 32; ++i){
                    // Binary search pass
                    var middlePoint = cc.math.vec3((startPosition.x+endPosition.x)*0.5, (startPosition.y+endPosition.y)*0.5, (startPosition.z+endPosition.z)*0.5);
                    if(middlePoint.y < height)
                        endPosition = middlePoint;
                    else
                        startPosition = middlePoint;
                }

                var collisionPoint = cc.math.vec3((startPosition.x+endPosition.x)*0.5, (startPosition.y+endPosition.y)*0.5, (startPosition.z+endPosition.z)*0.5);
                dir = cc.math.vec3Sub(collisionPoint, this._player.getPosition3D());
                dir.y = 0;
                dir.normalize();
                this._player._headingAngle = -1 * Math.acos(cc.math.vec3Dot(dir, cc.math.vec3(0, 0, -1)));
                this._player._headingAxis = cc.math.vec3Cross(dir, cc.math.vec3(0, 0, -1));
                this._player._targetPos = collisionPoint;
                this._player.forward();
            }
        }
    });
})();
//
// Flow control
//
var arrayOfTerrainTest = [
    TerrainSimple,
    TerrainWalkThru
];

var nextTerrainTest = function () {
    TerrainTestIdx++;
    TerrainTestIdx = TerrainTestIdx % arrayOfTerrainTest.length;

    return new arrayOfTerrainTest[TerrainTestIdx ]();
};
var previousTerrainTest = function () {
    TerrainTestIdx--;
    if (TerrainTestIdx < 0)
        TerrainTestIdx += arrayOfTerrainTest.length;

    return new arrayOfTerrainTest[TerrainTestIdx ]();
};
var restartTerrainTest = function () {
    return new arrayOfTerrainTest[TerrainTestIdx ]();
};

})();
