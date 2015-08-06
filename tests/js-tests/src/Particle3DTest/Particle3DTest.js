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
if(cc.sys.isNative)(function(){

var Particle3DTestIdx = -1;

var PARTICLE_SYSTEM_TAG = 0x0001;

jsb.fileUtils.addSearchPath("res/Sprite3DTest");
jsb.fileUtils.addSearchPath("res/Particle3D/materials");
jsb.fileUtils.addSearchPath("res/Particle3D/scripts");

var Particle3DTestDemo = cc.Layer.extend({
    _title:"Particle3D Test",
    _subtitle:"",
    _camera:null,
    _particleLabel:null,
    _angle:0,

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

        var size = cc.winSize;
        this._camera = new cc.Camera(cc.Camera.Mode.PERSPECTIVE, 30.0, size.width / size.height, 1.0, 1000.0);
        this._camera.setPosition3D(cc.math.vec3(0, 0, 100));
        this._camera.lookAt(cc.math.vec3(0, 0, 0), cc.math.vec3(0, 1, 0));
        this._camera.setCameraFlag(cc.CameraFlag.USER1);
        this.addChild(this._camera);

        var ttfconfig = {outlineSize:0, fontSize:15, glyphs:0, customGlyphs:"", fontFilePath:"fonts/tahoma.ttf"};
        this._particleLabel = cc.Label.createWithTTF(ttfconfig, "Particle count: 0");
        this._particleLabel.setPosition(0, size.height/6);
        this._particleLabel.setAnchorPoint(cc.p(0, 0));
        this.addChild(this._particleLabel);

        cc.eventManager.addListener({
            event:cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesMoved:this.onTouchesMoved.bind(this)
        }, this);

        this.scheduleUpdate();
    },

    onTouchesMoved:function(touches, event){
        var touch = touches[0];
        var delta = touch.getDelta();

        this._angle -= cc.degreesToRadians(delta.x);
        this._camera.setPosition3D(cc.math.vec3(100*Math.sin(this._angle), 0, 100*Math.cos(this._angle)));
        this._camera.lookAt(cc.math.vec3(0, 0, 0), cc.math.vec3(0, 1, 0));
    },

    update:function(dt){
        var ps = this.getChildByTag(PARTICLE_SYSTEM_TAG);
        if(ps){
            var count = 0;
            var children = ps.children;
            for(var i = 0; i < children.length; ++i){
                var child = children[i];
                if(child && child.getAliveParticleCount)
                    count += child.getAliveParticleCount();
            }
            this._particleLabel.setString("Particle Count: "+count);
        }
    },

    onRestartCallback:function (sender) {
        var s = new Particle3DTestScene();
        s.addChild(restartParticle3DTest());
        director.runScene(s);
    },

    onNextCallback:function (sender) {
        var s = new Particle3DTestScene();
        s.addChild(nextParticle3DTest());
        director.runScene(s);
    },

    onBackCallback:function (sender) {
        var s = new Particle3DTestScene();
        s.addChild(previousParticle3DTest());
        director.runScene(s);
    }
});

Particle3DTestScene = cc.Scene.extend({
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
        Particle3DTestIdx = (num || num == 0) ? (num - 1) : -1;
        var layer = nextParticle3DTest();
        this.addChild(layer);

        director.runScene(this);
    }
});

var Particle3DExplosionSystemDemo = Particle3DTestDemo.extend({
    _subtitle:"ExplosionSystem",

    ctor:function(){
        this._super();

        var rootps = jsb.PUParticleSystem3D.create("explosionSystem.pu");
        rootps.setCameraMask(cc.CameraFlag.USER1);
        rootps.startParticleSystem();
        this.addChild(rootps, 0, PARTICLE_SYSTEM_TAG);
    }
});

var Particle3DLineStreakDemo = Particle3DTestDemo.extend({
    _subtitle:"LineStreak",

    ctor:function(){
        this._super();

        var rootps = jsb.PUParticleSystem3D.create("lineStreak.pu", "pu_mediapack_01.material");
        rootps.setCameraMask(2);
        rootps.setScale(5);
        rootps.startParticleSystem();
        this.addChild(rootps, 0, PARTICLE_SYSTEM_TAG);
    }
});

var Particle3DBlackHoleDemo = Particle3DTestDemo.extend({
    _subtitle:"BlackHole",

    ctor:function(){
        this._super();

        var rootps = jsb.PUParticleSystem3D.create("blackHole.pu", "pu_mediapack_01.material");
        rootps.setCameraMask(2);
        rootps.runAction(cc.sequence(
            cc.moveBy(2, cc.p(50, 0)),
            cc.moveBy(2, cc.p(-50, 0))
        ).repeatForever());

        rootps.startParticleSystem();
        this.addChild(rootps, 0, PARTICLE_SYSTEM_TAG);
    }
});

var Particle3DHypnoDemo = Particle3DTestDemo.extend({
    _subtitle:"Hypno",

    ctor:function(){
        this._super();

        var rootps = jsb.PUParticleSystem3D.create("hypno.pu", "pu_mediapack_01.material");
        rootps.setCameraMask(2);
        rootps.startParticleSystem();
        this.addChild(rootps, 0, PARTICLE_SYSTEM_TAG);
    }
});

var Particle3DAdvancedLodSystemDemo = Particle3DTestDemo.extend({
    _subtitle:"AdvancedSystem",

    ctor:function(){
        this._super();

        var rootps = jsb.PUParticleSystem3D.create("advancedLodSystem.pu");
        rootps.setCameraMask(2);
        rootps.runAction(cc.rotateBy(1, cc.math.vec3(0, 0, 100)).repeatForever());
        var scale = cc.scaleBy(1, 2, 2, 2);
        rootps.runAction(cc.sequence(scale, scale.reverse()).repeatForever());
        rootps.startParticleSystem();
        this.addChild(rootps, 0, PARTICLE_SYSTEM_TAG);
    }
});

var Particle3DTimeShiftDemo = Particle3DTestDemo.extend({
    _subtitle:"TimeShift",

    ctor:function(){
        this._super();

        var rootps = jsb.PUParticleSystem3D.create("timeShift.pu", "pu_mediapack_01.material");
        rootps.setScale(2);
        rootps.setCameraMask(2);
        rootps.startParticleSystem();
        this.addChild(rootps, 0, PARTICLE_SYSTEM_TAG);
    }
});

var Particle3DUVAnimDemo = Particle3DTestDemo.extend({
    _subtitle:"UVAnim",

    ctor:function(){
        this._super();

        var rootps = jsb.PUParticleSystem3D.create("UVAnimation.pu", "pu_mediapack_01.material");
        rootps.setCameraMask(2);
        rootps.startParticleSystem();
        this.addChild(rootps, 0, PARTICLE_SYSTEM_TAG);
    }
});
var Particle3DFirePlaceDemo = Particle3DTestDemo.extend({
    _subtitle:"Fire",

    ctor:function(){
        this._super();

        var rootps = jsb.PUParticleSystem3D.create("mp_torch.pu", "pu_mediapack_01.material");
        rootps.setScale(5);
        rootps.setCameraMask(2);
        rootps.startParticleSystem();
        this.addChild(rootps, 0, PARTICLE_SYSTEM_TAG);
    }
});
var Particle3DElectricBeamSystemDemo = Particle3DTestDemo.extend({
    _subtitle:"ElectricBeamSystem",

    ctor:function(){
        this._super();

        var rootps = jsb.PUParticleSystem3D.create("electricBeamSystem.pu");
        rootps.setCameraMask(2);
        rootps.startParticleSystem();
        this.addChild(rootps, 0, PARTICLE_SYSTEM_TAG);
    }
});

var Particle3DFlareShieldDemo = Particle3DTestDemo.extend({
    _subtitle:"flareShield",

    ctor:function(){
        this._super();

        var rootps = jsb.PUParticleSystem3D.create("flareShield.pu");
        rootps.setCameraMask(2);
        rootps.startParticleSystem();
        this.addChild(rootps, 0, PARTICLE_SYSTEM_TAG);
    }
});

var Particle3DLightningBoltDemo = Particle3DTestDemo.extend({
    _subtitle:"LightningBolt",

    ctor:function(){
        this._super();

        var rootps = jsb.PUParticleSystem3D.create("lightningBolt.pu");
        rootps.setCameraMask(2);
        rootps.startParticleSystem();
        this.addChild(rootps, 0, PARTICLE_SYSTEM_TAG);
    }
});

var Particle3DCanOfWormsDemo = Particle3DTestDemo.extend({
    _subtitle:"CanOfWorms",

    ctor:function(){
        this._super();

        var rootps = jsb.PUParticleSystem3D.create("canOfWorms.pu");
        rootps.setCameraMask(2);
        rootps.startParticleSystem();
        this.addChild(rootps, 0, PARTICLE_SYSTEM_TAG);
    }
});

var Particle3DRibbonTrailDemo = Particle3DTestDemo.extend({
    _subtitle:"RibbonTrailTest",

    ctor:function(){
        this._super();

        var rootps = jsb.PUParticleSystem3D.create("ribbonTrailTest.pu");
        rootps.setCameraMask(2);
        rootps.startParticleSystem();
        this.addChild(rootps, 0, PARTICLE_SYSTEM_TAG);
    }
});

var Particle3DWeaponTrailDemo = Particle3DTestDemo.extend({
    _subtitle:"WeaponTrail",

    ctor:function(){
        this._super();

        var rootps = jsb.PUParticleSystem3D.create("weaponTrail.pu");
        rootps.setCameraMask(2);
        rootps.startParticleSystem();
        this.addChild(rootps, 0, PARTICLE_SYSTEM_TAG);
    }
});

var Particle3DWithSprite3DDemo = Particle3DTestDemo.extend({
    _subtitle:"Particle with Sprite3D",

    ctor:function(){
        this._super();

        var c3bfileName = "Sprite3DTest/orc.c3b";
        var sprite = new jsb.Sprite3D(c3bfileName);
        this.addChild(sprite);
        sprite.setPosition3D(cc.math.vec3(-20, 0, 0));
        sprite.setRotation3D(cc.math.vec3(0, 180, 0));
        sprite.setCameraMask(2);
        var animation = new jsb.Animation3D(c3bfileName);
        if(animation){
            var animate = new jsb.Animate3D(animation);
            sprite.runAction(cc.repeatForever(animate));
        }

        var billboard = new jsb.BillBoard("Images/Icon.png");
        billboard.setPosition3D(cc.math.vec3(20, 0, 0));
        billboard.setScale(0.2);
        billboard.setCameraMask(2);
        this.addChild(billboard);

        var rootps = jsb.PUParticleSystem3D.create("lineStreak.pu");
        rootps.setCameraMask(2);
        rootps.startParticleSystem();
        this.addChild(rootps, 0, PARTICLE_SYSTEM_TAG);
    }
})
//
// Flow control
//
var arrayOfParticle3DTest = [
    Particle3DExplosionSystemDemo,
    Particle3DLineStreakDemo,
    Particle3DBlackHoleDemo,
    Particle3DHypnoDemo,
    Particle3DAdvancedLodSystemDemo,
    Particle3DTimeShiftDemo,
    Particle3DUVAnimDemo,
    Particle3DFirePlaceDemo,
    Particle3DElectricBeamSystemDemo,
    Particle3DFlareShieldDemo,
    Particle3DLightningBoltDemo,
    Particle3DCanOfWormsDemo,
    Particle3DRibbonTrailDemo,
    Particle3DWeaponTrailDemo,
    Particle3DWithSprite3DDemo
];

var nextParticle3DTest = function () {
    Particle3DTestIdx++;
    Particle3DTestIdx = Particle3DTestIdx % arrayOfParticle3DTest.length;

    return new arrayOfParticle3DTest[Particle3DTestIdx ]();
};
var previousParticle3DTest = function () {
    Particle3DTestIdx--;
    if (Particle3DTestIdx < 0)
        Particle3DTestIdx += arrayOfParticle3DTest.length;

    return new arrayOfParticle3DTest[Particle3DTestIdx ]();
};
var restartParticle3DTest = function () {
    return new arrayOfParticle3DTest[Particle3DTestIdx ]();
};

})();
