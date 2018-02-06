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
var BillBoardTestIdx = -1;

var BillBoardTestDemo = cc.Layer.extend({
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
        var s = new BillBoardTestScene();
        s.addChild(restartBillBoardTest());
        director.runScene(s);
    },

    onNextCallback:function (sender) {
        var s = new BillBoardTestScene();
        s.addChild(nextBillBoardTest());
        director.runScene(s);
    },

    onBackCallback:function (sender) {
        var s = new BillBoardTestScene();
        s.addChild(previousBillBoardTest());
        director.runScene(s);
    },
});

var BillBoardTestScene = cc.Scene.extend({
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
        BillBoardTestIdx = (num || num == 0) ? (num - 1) : -1;
        var layer = nextBillBoardTest();
        this.addChild(layer);

        director.runScene(this);
    }
});

var BillBoardRotationTest = BillBoardTestDemo.extend({
    _title:"Rotation Test",
    _subtitle:"All the sprites should still facing camera",

    ctor:function(){
        this._super();

        var root = new jsb.Sprite3D();
        root.setNormalizedPosition(cc.p(0.5, 0.25));
        this.addChild(root);

        var model = new jsb.Sprite3D("Sprite3DTest/orc.c3b");
        model.setScale(5);
        model.setRotation3D(cc.math.vec3(0, 180, 0));
        root.addChild(model);

        var bill = new jsb.BillBoard();
        bill.setPosition(0, 120);
        root.addChild(bill);

        var sp = new cc.Sprite("Images/SpookyPeas.png");
        bill.addChild(sp);

        var label = new cc.LabelTTF("+100");
        label.setPosition(0, 30);
        bill.addChild(label);

        root.runAction(cc.rotateBy(10, cc.math.vec3(0, 360, 0)).repeatForever());

        var jump = cc.jumpBy(1, cc.p(0, 0), 30, 1);
        var scale = cc.scaleBy(2, 2, 2, 0.1);
        var rot = cc.rotateBy(2, cc.math.vec3(-90, 0, 0));
        model.runAction(cc.sequence(cc.spawn(cc.sequence(jump, scale), rot), cc.spawn(scale.reverse(), rot.reverse())).repeatForever());
    }
});

var BillBoardTest = BillBoardTestDemo.extend({
    _title:"BillBoard Test",
    _subtitle:"",
    _camera:null,
    _layerBillBoard:null,
    _billboards:[],

    ctor:function(){
        this._super();

        //Create touch listener
        cc.eventManager.addListener({
            event:cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesMoved:this.onTouchesMoved.bind(this)
        }, this);

        var layer3D = new cc.Layer();
        this.addChild(layer3D, 0);
        this._layerBillBoard = layer3D;

        var s = cc.winSize;
        if(!this._camera){
            this._camera = new cc.Camera(cc.Camera.Mode.PERSPECTIVE, 60, s.width/s.height, 1, 500);
            this._camera.setCameraFlag(cc.CameraFlag.USER1);
            this._layerBillBoard.addChild(this._camera);
        }

        //Create rotating billboards
        var imgs = ["Images/Icon.png", "Images/r2.png"];
        for(var i = 0; i < 4; ++i){
            var layer = new cc.Layer();
            var billboard = new jsb.BillBoard(imgs[Math.floor(Math.random() + 0.5)]);
            billboard.setScale(0.5);
            billboard.setPosition3D(cc.math.vec3(0, 0, (Math.random() * 2 - 1) * 150));
            billboard.setOpacity(Math.random() * 128 + 128);
            this._billboards.push(billboard);
            layer.addChild(billboard);
            this._layerBillBoard.addChild(layer);
            layer.runAction(cc.rotateBy(Math.random() * 10, cc.math.vec3(0, 45, 0)).repeatForever());
        }

        {
            var billboard1 = new jsb.BillBoard("Images/Icon.png");
            billboard1.setScale(0.2);
            billboard1.setPosition3D(cc.math.vec3(0, 30, 0));

            var billboard2 = new jsb.BillBoard("Images/r2.png");
            billboard2.setPosition3D(cc.math.vec3(0, 0, 100));
            billboard1.addChild(billboard2);
            this._billboards.push(billboard1);
            this._billboards.push(billboard2);

            var sprite3d = new jsb.Sprite3D("Sprite3DTest/orc.c3b");
            sprite3d.setScale(2);
            sprite3d.addChild(billboard1);
            sprite3d.runAction(cc.rotateBy(10, cc.math.vec3(0, 360, 0)).repeatForever());
            this._layerBillBoard.addChild(sprite3d);
        }

        this.addNewBillBoardWithCoords(cc.math.vec3(20, 5, 0));
        this.addNewBillBoardWithCoords(cc.math.vec3(60, 5, 0));
        this.addNewBillBoardWithCoords(cc.math.vec3(100, 5, 0));
        this.addNewBillBoardWithCoords(cc.math.vec3(140, 5, 0));
        this.addNewBillBoardWithCoords(cc.math.vec3(180, 5, 0));

        this.addNewAniBillBoardWithCoords(cc.math.vec3(-20, 0, 0));
        this.addNewAniBillBoardWithCoords(cc.math.vec3(-60, 0, 0));
        this.addNewAniBillBoardWithCoords(cc.math.vec3(-100, 0, 0));
        this.addNewAniBillBoardWithCoords(cc.math.vec3(-140, 0, 0));
        this.addNewAniBillBoardWithCoords(cc.math.vec3(-180, 0, 0));

        this._camera.setPosition3D(cc.math.vec3(0, 100, 230));
        this._camera.lookAt(cc.math.vec3(0, 0, 0), cc.math.vec3(0, 1, 0));

        this._layerBillBoard.setCameraMask(2);

        var label1 = new cc.LabelTTF("rotate+", "Arial", 16);
        var item1 = new cc.MenuItemLabel(label1, function(){
            var rotation3D = this._camera.getRotation3D();
            rotation3D.y += 10;
            this._camera.setRotation3D(rotation3D);
        }, this);
        var label2 = new cc.LabelTTF("rotate-", "Arial", 16);
        var item2 = new cc.MenuItemLabel(label2, function(){
            var rotation3D = this._camera.getRotation3D();
            rotation3D.y -= 10;
            this._camera.setRotation3D(rotation3D);
        }, this);
        var label3 = new cc.LabelTTF("Point Oriented", "Arial", 16);
        var item3 = new cc.MenuItemLabel(label3, this.menuCallback_orientedPoint, this);
        var label4 = new cc.LabelTTF("Plane Oriented", "Arial", 16);
        var item4 = new cc.MenuItemLabel(label4, this.menuCallback_orientedPlane, this);

        item1.setPosition(cc.p(s.width-80, s.height-160));
        item2.setPosition(cc.p(s.width-80, s.height-190));
        item3.setPosition(cc.p(s.width-80, s.height-100));
        item4.setPosition(cc.p(s.width-80, s.height-130));

        var menu = new cc.Menu(item1, item2, item3, item4);
        this.addChild(menu);
        menu.setPosition(0, 0);
    },

    addNewBillBoardWithCoords:function(position){
        var imgs = ["Images/Icon.png", "Images/r2.png"];
        for(var i = 0; i < 10; ++i){
            var billboard = new jsb.BillBoard(imgs[Math.floor(Math.random() + 0.5)]);
            billboard.setScale(0.5);
            billboard.setPosition3D(cc.math.vec3(position.x, position.y, -150+30*i));
            billboard.setOpacity(Math.random() * 128 + 128);
            this._layerBillBoard.addChild(billboard);
            this._billboards.push(billboard);
        }
    },

    addNewAniBillBoardWithCoords:function(position){
        for(var i = 0; i < 10; ++i){
            var billboardAni = new jsb.BillBoard("Images/grossini.png");
            billboardAni.setScale(0.5);
            billboardAni.setPosition3D(cc.math.vec3(position.x, position.y, -150+30*i));
            this._layerBillBoard.addChild(billboardAni);

            var animation = new cc.Animation();
            for(var j = 1; j < 15; ++j){
                if(j < 10)
                    animation.addSpriteFrameWithFile("Images/grossini_dance_0"+j+".png");
                else
                    animation.addSpriteFrameWithFile("Images/grossini_dance_"+j+".png");
            }
            // should last 2.8 seconds. And there are 14 frames.
            animation.setDelayPerUnit(2.8/14.0);
            animation.setRestoreOriginalFrame(true);

            var action = new cc.Animate(animation);
            billboardAni.runAction(action.repeatForever());
            billboardAni.setOpacity(Math.random() * 128 + 128);
            this._billboards.push(billboardAni);
        }
    },

    menuCallback_orientedPoint:function(sender){
        for(var i = 0; i < this._billboards.length; ++i){
            this._billboards[i].setMode(jsb.BillBoard.Mode.VIEW_POINT_ORIENTED);
        }
    },

    menuCallback_orientedPlane:function(sender){
        for(var i = 0; i < this._billboards.length; ++i){
            this._billboards[i].setMode(jsb.BillBoard.Mode.VIEW_PLANE_ORIENTED);
        }
    },

    onTouchesMoved:function(touches, event){
        if(touches.length == 1){
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
            cameraPos.x += cameraDir.x * newPos.y * 0.5 + cameraRightDir.x * newPos.x * 0.5;
            cameraPos.y += cameraDir.y * newPos.y * 0.5 + cameraRightDir.y * newPos.x * 0.5;
            cameraPos.z += cameraDir.z * newPos.y * 0.5 + cameraRightDir.z * newPos.x * 0.5;
            this._camera.setPosition3D(cameraPos);
        } 
    }
});

//
// Flow control
//
var arrayOfBillBoardTest = [
    BillBoardRotationTest,
    BillBoardTest
];

var nextBillBoardTest = function () {
    BillBoardTestIdx++;
    BillBoardTestIdx = BillBoardTestIdx % arrayOfBillBoardTest.length;

    return new arrayOfBillBoardTest[BillBoardTestIdx ]();
};
var previousBillBoardTest = function () {
    BillBoardTestIdx--;
    if (BillBoardTestIdx < 0)
        BillBoardTestIdx += arrayOfBillBoardTest.length;

    return new arrayOfBillBoardTest[BillBoardTestIdx ]();
};
var restartBillBoardTest = function () {
    return new arrayOfBillBoardTest[BillBoardTestIdx ]();
};
