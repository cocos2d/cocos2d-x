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
var TAG_LABEL_ATLAS = 1;

var sceneIdx = -1;
var MAX_LAYER = 33;

var ParticleTestScene = TestScene.extend({
    runThisTest:function () {
        sceneIdx = -1;
        MAX_LAYER = 33;

        this.addChild(nextParticleAction());
        director.replaceScene(this);
    }
});

var particleSceneArr = [
    function () {
        return new DemoFlower();
    },
    function () {
        return new DemoGalaxy();
    },
    function () {
        return new DemoFirework();
    },
    function () {
        return new DemoSpiral();
    },
    function () {
        return new DemoSun();
    },
    function () {
        return new DemoMeteor();
    },
    function () {
        return new DemoFire();
    },
    function () {
        return new DemoSmoke();
    },
    function () {
        return new DemoExplosion();
    },
    function () {
        return new DemoSnow();
    },
    function () {
        return new DemoRain();
    },
    function () {
        return new DemoBigFlower();
    },
    function () {
        return new DemoRotFlower();
    },
    function () {
        return new DemoModernArt();
    },
    function () {
        return new DemoRing();
    },
    //function(){return new ParallaxParticle();},
    function () {
        return new DemoParticleFromFile("BoilingFoam");
    },
    function () {
        return new DemoParticleFromFile("BurstPipe");
    },
    function () {
        return new DemoParticleFromFile("Comet");
    },
    function () {
        return new DemoParticleFromFile("debian");
    },
    function () {
        return new DemoParticleFromFile("ExplodingRing");
    },
    function () {
        return new DemoParticleFromFile("LavaFlow");
    },
    //function(){return new DemoParticleFromFile("SpinningPeas");},
    function () {
        return new DemoParticleFromFile("SpookyPeas");
    },
    function () {
        return new DemoParticleFromFile("Upsidedown");
    },
    function () {
        return new DemoParticleFromFile("Flower");
    },
    function () {
        return new DemoParticleFromFile("Spiral");
    },
    function () {
        return new DemoParticleFromFile("Galaxy");
    },
    function () {
        return new RadiusMode1();
    },
    function () {
        return new RadiusMode2();
    },
    function () {
        return new Issue704();
    },
    function () {
        return new Issue870();
    },
    function () {
        return new DemoParticleFromFile("Phoenix");
    }
];

var nextParticleAction = function () {
    sceneIdx++;
    sceneIdx = sceneIdx % particleSceneArr.length;
    return particleSceneArr[sceneIdx]();
};

var backParticleAction = function () {
    sceneIdx--;
    if (sceneIdx < 0)
        sceneIdx += particleSceneArr.length;

    return particleSceneArr[sceneIdx]();
};

var restartParticleAction = function () {
    return particleSceneArr[sceneIdx]();
};

var ParticleDemo = cc.Layer.extend({
    _emitter: null,
    _background: null,
    _shapeModeButton: null,
    _textureModeButton: null,

    ctor: function() {
        //this._super();
        cc.associateWithNative(this, cc.Layer);
        this.init();
    },
    setColor:function() {},
    init: function() {
        this._super();
        // this.initWithColor(cc.c4b(127, 127, 127, 255));

        this._emitter = null;

        var t = cc.config.deviceType;
        if( t == 'browser' )  {
            this.setTouchEnabled(true);
            // this.setKeyboardEnabled(true);
        } else if( t == 'desktop' ) {
            this.setMouseEnabled(true);
        } else if( t == 'mobile' ) {
            this.setTouchEnabled(true);
        }

        var s = director.getWinSize();
        var label = cc.LabelTTF.create(this.title(), "Arial", 28);
        this.addChild(label, 100, 1000);
        label.setPosition(s.width / 2, s.height - 50);

        var tapScreen = cc.LabelTTF.create("(Tap the Screen)", "Arial", 20);
        tapScreen.setPosition(s.width / 2, s.height - 80);
        this.addChild(tapScreen, 100);
        var selfPoint = this;
        var item1 = cc.MenuItemImage.create(s_pathB1, s_pathB2, this, this.backCallback);
        var item2 = cc.MenuItemImage.create(s_pathR1, s_pathR2, this, function () {
            selfPoint._emitter.resetSystem();
        });
        var item3 = cc.MenuItemImage.create(s_pathF1, s_pathF2, this, this.nextCallback);

        var freeBtnNormal = cc.Sprite.create(s_MovementMenuItem, cc.rect(0, 23 * 2, 123, 23));
        var freeBtnSelected = cc.Sprite.create(s_MovementMenuItem, cc.rect(0, 23, 123, 23));
        var freeBtnDisabled = cc.Sprite.create(s_MovementMenuItem, cc.rect(0, 0, 123, 23));

        var relativeBtnNormal = cc.Sprite.create(s_MovementMenuItem, cc.rect(123, 23 * 2, 138, 23));
        var relativeBtnSelected = cc.Sprite.create(s_MovementMenuItem, cc.rect(123, 23, 138, 23));
        var relativeBtnDisabled = cc.Sprite.create(s_MovementMenuItem, cc.rect(123, 0, 138, 23));

        var groupBtnNormal = cc.Sprite.create(s_MovementMenuItem, cc.rect(261, 23 * 2, 136, 23));
        var groupBtnSelected = cc.Sprite.create(s_MovementMenuItem, cc.rect(261, 23, 136, 23));
        var groupBtnDisabled = cc.Sprite.create(s_MovementMenuItem, cc.rect(261, 0, 136, 23));

        this._freeMovementButton = cc.MenuItemSprite.create(freeBtnNormal, freeBtnSelected, freeBtnDisabled, this,
            function () {
                selfPoint._emitter.setPositionType(cc.PARTICLE_TYPE_RELATIVE);
                selfPoint._relativeMovementButton.setVisible(true);
                selfPoint._freeMovementButton.setVisible(false);
                selfPoint._groupMovementButton.setVisible(false);
            });
        this._freeMovementButton.setPosition(10, 150);
        this._freeMovementButton.setAnchorPoint(cc.p(0, 0));

        this._relativeMovementButton = cc.MenuItemSprite.create(relativeBtnNormal, relativeBtnSelected, relativeBtnDisabled, this,
            function () {
                selfPoint._emitter.setPositionType(cc.PARTICLE_TYPE_GROUPED);
                selfPoint._relativeMovementButton.setVisible(false);
                selfPoint._freeMovementButton.setVisible(false);
                selfPoint._groupMovementButton.setVisible(true);
            });
        this._relativeMovementButton.setVisible(false);
        this._relativeMovementButton.setPosition(10, 150);
        this._relativeMovementButton.setAnchorPoint(cc.p(0, 0));

        this._groupMovementButton = cc.MenuItemSprite.create(groupBtnNormal, groupBtnSelected, groupBtnDisabled, this,
            function () {
                selfPoint._emitter.setPositionType(cc.PARTICLE_TYPE_FREE);
                selfPoint._relativeMovementButton.setVisible(false);
                selfPoint._freeMovementButton.setVisible(true);
                selfPoint._groupMovementButton.setVisible(false);
            });
        this._groupMovementButton.setVisible(false);
        this._groupMovementButton.setPosition(10, 150);
        this._groupMovementButton.setAnchorPoint(cc.p(0, 0));

        var spriteNormal = cc.Sprite.create(s_shapeModeMenuItem, cc.rect(0, 23 * 2, 115, 23));
        var spriteSelected = cc.Sprite.create(s_shapeModeMenuItem, cc.rect(0, 23, 115, 23));
        var spriteDisabled = cc.Sprite.create(s_shapeModeMenuItem, cc.rect(0, 0, 115, 23));

        this._shapeModeButton = cc.MenuItemSprite.create(spriteNormal, spriteSelected, spriteDisabled, this,
            function () {
                selfPoint._emitter.setDrawMode(cc.PARTICLE_TEXTURE_MODE);
                selfPoint._textureModeButton.setVisible(true);
                selfPoint._shapeModeButton.setVisible(false);
            });
        this._shapeModeButton.setPosition(10, 100);
        this._shapeModeButton.setAnchorPoint(cc.p(0, 0));

        if( cc.config.deviceType != "browser" ) {
            // Shape type is not compatible with JSB
            this._shapeModeButton.setEnabled(false);
        }

        var spriteNormal_t = cc.Sprite.create(s_textureModeMenuItem, cc.rect(0, 23 * 2, 115, 23));
        var spriteSelected_t = cc.Sprite.create(s_textureModeMenuItem, cc.rect(0, 23, 115, 23));
        var spriteDisabled_t = cc.Sprite.create(s_textureModeMenuItem, cc.rect(0, 0, 115, 23));

        this._textureModeButton = cc.MenuItemSprite.create(spriteNormal_t, spriteSelected_t, spriteDisabled_t, this,
            function () {
                selfPoint._emitter.setDrawMode(cc.PARTICLE_SHAPE_MODE);
                selfPoint._textureModeButton.setVisible(false);
                selfPoint._shapeModeButton.setVisible(true);
            });
        this._textureModeButton.setVisible(false);
        this._textureModeButton.setPosition(10, 100);
        this._textureModeButton.setAnchorPoint(cc.p(0, 0));

        var menu = cc.Menu.create(item1, item2, item3, this._shapeModeButton, this._textureModeButton,
            this._freeMovementButton, this._relativeMovementButton, this._groupMovementButton);

        menu.setPosition(0,0);
        item1.setPosition(s.width / 2 - 100, 30);
        item2.setPosition(s.width / 2, 30);
        item3.setPosition(s.width / 2 + 100, 30);

        this.addChild(menu, 100);
        //TODO
        var labelAtlas = cc.LabelAtlas.create("0123456789", s_fpsImages, 16, 24, '.'.charCodeAt(0));
        this.addChild(labelAtlas, 100, TAG_LABEL_ATLAS);
        labelAtlas.setPosition(s.width - 66, 50);

        // moving background
        this._background = cc.Sprite.create(s_back3);
        this.addChild(this._background, 5);
        this._background.setPosition(s.width / 2, s.height - 180);

        var move = cc.MoveBy.create(4, cc.p(300, 0));
        var move_back = move.reverse();

        var seq = cc.Sequence.create(move, move_back);
        this._background.runAction(cc.RepeatForever.create(seq));

        this.scheduleUpdate();
    },

    onEnter:function () {
        this._super();

        var pLabel = this.getChildByTag(1000);
        pLabel.setString(this.title());
    },
    title:function () {
        return "No title";
    },

    restartCallback:function (sender) {
        this._emitter.resetSystem();
    },
    nextCallback:function (sender) {
        var s = new ParticleTestScene();
        s.addChild(nextParticleAction());
        director.replaceScene(s);
    },
    backCallback:function (sender) {
        var s = new ParticleTestScene();
        s.addChild(backParticleAction());
        director.replaceScene(s);
    },
    toggleCallback:function (sender) {
        if (this._emitter.getPositionType() == cc.PARTICLE_TYPE_GROUPED)
            this._emitter.setPositionType(cc.PARTICLE_TYPE_FREE);
        else if (this._emitter.getPositionType() == cc.PARTICLE_TYPE_FREE)
            this._emitter.setPositionType(cc.PARTICLE_TYPE_RELATIVE);
        else if (this._emitter.getPositionType() == cc.PARTICLE_TYPE_RELATIVE)
            this._emitter.setPositionType(cc.PARTICLE_TYPE_GROUPED);
    },

    onTouchesMoved: function(touches, event) {
        if( touches.length > 0 ) {
            var location = touches[0].getLocation();
            var pos = cc.p(0,0);
            if (this._background) {
                pos = this._background.convertToWorldSpace(cc.p(0,0));
            }
            this._emitter.setPosition(cc.pSub(location, pos));
        }
    },
    onMouseDragged : function( event ) {
        var location = event.getLocation();
        var pos = cc.p(0,0);
        if (this._background) {
            pos = this._background.convertToWorldSpace(cc.p(0,0));
        }
        this._emitter.setPosition(cc.pSub(location, pos));
        return true;
    },
    update:function (dt) {
        if (this._emitter) {
            var atlas = this.getChildByTag(TAG_LABEL_ATLAS);
            atlas.setString(this._emitter.getParticleCount().toFixed(0));
        }
    },
    setEmitterPosition:function () {
        var sourcePos = this._emitter.getSourcePosition();
        if( sourcePos.x === 0 && sourcePos.y === 0)
            this._emitter.setPosition(200,70);
    }
});

var DemoFirework = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleFireworks.create();
        this._background.addChild(this._emitter, 10);
        var myTexture = cc.TextureCache.getInstance().addImage(s_stars1);
        this._emitter.setTexture(myTexture);
        if(this._emitter.setShapeType)
            this._emitter.setShapeType(cc.PARTICLE_STAR_SHAPE);
        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleFireworks";
    }
});

var DemoFire = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleFire.create();
        this._background.addChild(this._emitter, 10);

        this._emitter.setTexture(cc.TextureCache.getInstance().addImage(s_fire));//.pvr"];
        if(this._emitter.setShapeType)
            this._emitter.setShapeType(cc.PARTICLE_BALL_SHAPE);

        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleFire";
    }
});

var DemoSun = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleSun.create();
        this._background.addChild(this._emitter, 10);
        var myTexture = cc.TextureCache.getInstance().addImage(s_fire);
        this._emitter.setTexture(myTexture);
        if(this._emitter.setShapeType)
            this._emitter.setShapeType(cc.PARTICLE_BALL_SHAPE);

        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleSun";
    }
});

var DemoGalaxy = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleGalaxy.create();
        this._background.addChild(this._emitter, 10);
        var myTexture = cc.TextureCache.getInstance().addImage(s_fire);
        this._emitter.setTexture(myTexture);
        if(this._emitter.setShapeType)
            this._emitter.setShapeType(cc.PARTICLE_BALL_SHAPE);

        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleGalaxy";
    }
});

var DemoFlower = ParticleDemo.extend({
    _title: "ParticleFlower",

    onEnter: function() {
        this._super();

        this._emitter = cc.ParticleFlower.create();
        this._background.addChild(this._emitter, 10);

        var myTexture = cc.TextureCache.getInstance().addImage(s_stars1);
        this._emitter.setTexture(myTexture);
        if(this._emitter.setShapeType)
            this._emitter.setShapeType(cc.PARTICLE_STAR_SHAPE);

        this.setEmitterPosition();
    },
    title: function() {
        return this._title;
    }
});

var DemoBigFlower = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleSystem.createWithTotalParticles(50);

        this._background.addChild(this._emitter, 10);
        this._emitter.setTexture(cc.TextureCache.getInstance().addImage(s_stars1));
        if(this._emitter.setShapeType)
            this._emitter.setShapeType(cc.PARTICLE_STAR_SHAPE);

        this._emitter.setDuration(-1);

        // gravity
        this._emitter.setGravity(cc.p(0,0));

        // angle
        this._emitter.setAngle(90);
        this._emitter.setAngleVar(360);

        // speed of particles
        this._emitter.setSpeed(160);
        this._emitter.setSpeedVar(20);

        // radial
        this._emitter.setRadialAccel(-120);
        this._emitter.setRadialAccelVar(0);

        // tagential
        this._emitter.setTangentialAccel(30);
        this._emitter.setTangentialAccelVar(0);

        // emitter position
        this._emitter.setPosition(160, 240);
        this._emitter.setPosVar(cc.p(0,0));

        // life of particles
        this._emitter.setLife(4);
        this._emitter.setLifeVar(1);

        // spin of particles
        this._emitter.setStartSpin(0);
        this._emitter.setStartSizeVar(0);
        this._emitter.setEndSpin(0);
        this._emitter.setEndSpinVar(0);

        // color of particles
        var startColor = cc.c4f(0.5, 0.5, 0.5, 1.0);
        this._emitter.setStartColor(startColor);

        var startColorVar = cc.c4f(0.5, 0.5, 0.5, 1.0);
        this._emitter.setStartColorVar(startColorVar);

        var endColor = cc.c4f(0.1, 0.1, 0.1, 0.2);
        this._emitter.setEndColor(endColor);

        var endColorVar = cc.c4f(0.1, 0.1, 0.1, 0.2);
        this._emitter.setEndColorVar(endColorVar);

        // size, in pixels
        this._emitter.setStartSize(80.0);
        this._emitter.setStartSizeVar(40.0);
        this._emitter.setEndSize(cc.PARTICLE_START_SIZE_EQUAL_TO_END_SIZE);

        // emits per second
        this._emitter.setEmissionRate(this._emitter.getTotalParticles() / this._emitter.getLife());

        // additive
        this._emitter.setBlendAdditive(true);

        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleBigFlower";
    }
});

var DemoRotFlower = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleSystem.createWithTotalParticles(150);

        this._background.addChild(this._emitter, 10);
        this._emitter.setTexture(cc.TextureCache.getInstance().addImage(s_stars2));
        if(this._emitter.setShapeType)
            this._emitter.setShapeType(cc.PARTICLE_STAR_SHAPE);

        // duration
        this._emitter.setDuration(-1);

        // gravity
        this._emitter.setGravity(cc.p(0,0));

        // angle
        this._emitter.setAngle(90);
        this._emitter.setAngleVar(360);

        // speed of particles
        this._emitter.setSpeed(160);
        this._emitter.setSpeedVar(20);

        // radial
        this._emitter.setRadialAccel(-120);
        this._emitter.setRadialAccelVar(0);

        // tagential
        this._emitter.setTangentialAccel(30);
        this._emitter.setTangentialAccelVar(0);

        // emitter position
        this._emitter.setPosition(160, 240);
        this._emitter.setPosVar(cc.p(0,0));

        // life of particles
        this._emitter.setLife(3);
        this._emitter.setLifeVar(1);

        // spin of particles
        this._emitter.setStartSpin(0);
        this._emitter.setStartSpinVar(0);
        this._emitter.setEndSpin(0);
        this._emitter.setEndSpinVar(2000);

        var startColor = cc.c4f(0.5, 0.5, 0.5, 1.0);
        this._emitter.setStartColor(startColor);

        var startColorVar = cc.c4f(0.5, 0.5, 0.5, 1.0);
        this._emitter.setStartColorVar(startColorVar);

        var endColor = cc.c4f(0.1, 0.1, 0.1, 0.2);
        this._emitter.setEndColor(endColor);

        var endColorVar = cc.c4f(0.1, 0.1, 0.1, 0.2);
        this._emitter.setEndColorVar(endColorVar);

        // size, in pixels
        this._emitter.setStartSize(30.0);
        this._emitter.setStartSizeVar(0);
        this._emitter.setEndSize(cc.PARTICLE_START_SIZE_EQUAL_TO_END_SIZE);

        // emits per second
        this._emitter.setEmissionRate(this._emitter.getTotalParticles() / this._emitter.getLife());

        // additive
        this._emitter.setBlendAdditive(false);

        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleRotFlower";
    }
});

var DemoMeteor = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleMeteor.create();
        this._background.addChild(this._emitter, 10);

        this._emitter.setTexture(cc.TextureCache.getInstance().addImage(s_fire));
        if(this._emitter.setShapeType)
            this._emitter.setShapeType(cc.PARTICLE_BALL_SHAPE);

        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleMeteor";
    }
});

var DemoSpiral = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleSpiral.create();
        this._background.addChild(this._emitter, 10);

        this._emitter.setTexture(cc.TextureCache.getInstance().addImage(s_fire));
        if(this._emitter.setShapeType)
            this._emitter.setShapeType(cc.PARTICLE_BALL_SHAPE);

        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleSpiral";
    }
});

var DemoExplosion = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleExplosion.create();
        this._background.addChild(this._emitter, 10);

        this._emitter.setTexture(cc.TextureCache.getInstance().addImage(s_stars1));
        if(this._emitter.setShapeType)
            this._emitter.setShapeType(cc.PARTICLE_STAR_SHAPE);

        this._emitter.setAutoRemoveOnFinish(true);
	
        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleExplosion";
    }
});

var DemoSmoke = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleSmoke.create();
        this._background.addChild(this._emitter, 10);
        this._emitter.setTexture(cc.TextureCache.getInstance().addImage(s_fire));

        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleSmoke";
    }
});

var DemoSnow = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleSnow.create();
        this._background.addChild(this._emitter, 10);

        this._emitter.setLife(3);
        this._emitter.setLifeVar(1);

        // gravity
        this._emitter.setGravity(cc.p(0, -10));

        // speed of particles
        this._emitter.setSpeed(130);
        this._emitter.setSpeedVar(30);


        var startColor = this._emitter.getStartColor();
        startColor.r = 0.9;
        startColor.g = 0.9;
        startColor.b = 0.9;
        this._emitter.setStartColor(startColor);

        var startColorVar = this._emitter.getStartColorVar();
        startColorVar.b = 0.1;
        this._emitter.setStartColorVar(startColorVar);

        this._emitter.setEmissionRate(this._emitter.getTotalParticles() / this._emitter.getLife());

        this._emitter.setTexture(cc.TextureCache.getInstance().addImage(s_snow));
        if(this._emitter.setShapeType)
            this._emitter.setShapeType(cc.PARTICLE_STAR_SHAPE);

        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleSnow";
    }
});

var DemoRain = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleRain.create();
        this._background.addChild(this._emitter, 10);

        this._emitter.setLife(4);

        this._emitter.setTexture(cc.TextureCache.getInstance().addImage(s_fire));
        if(this._emitter.setShapeType)
            this._emitter.setShapeType(cc.PARTICLE_BALL_SHAPE);

        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleRain";
    }
});

var DemoModernArt = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleSystem.createWithTotalParticles(200);

        this._background.addChild(this._emitter, 10);
        ////this._emitter.release();

        var s = director.getWinSize();

        // duration
        this._emitter.setDuration(-1);

        // gravity
        this._emitter.setGravity(cc.p(0, 0));

        // angle
        this._emitter.setAngle(0);
        this._emitter.setAngleVar(360);

        // radial
        this._emitter.setRadialAccel(70);
        this._emitter.setRadialAccelVar(10);

        // tagential
        this._emitter.setTangentialAccel(80);
        this._emitter.setTangentialAccelVar(0);

        // speed of particles
        this._emitter.setSpeed(50);
        this._emitter.setSpeedVar(10);

        // life of particles
        this._emitter.setLife(2.0);
        this._emitter.setLifeVar(0.3);

        // emits per frame
        this._emitter.setEmissionRate(this._emitter.getTotalParticles() / this._emitter.getLife());

        // color of particles
        var startColor = cc.c4f(0.5, 0.5, 0.5, 1.0);
        this._emitter.setStartColor(startColor);

        var startColorVar = cc.c4f(0.5, 0.5, 0.5, 1.0);
        this._emitter.setStartColorVar(startColorVar);

        var endColor = cc.c4f(0.1, 0.1, 0.1, 0.2);
        this._emitter.setEndColor(endColor);

        var endColorVar = cc.c4f(0.1, 0.1, 0.1, 0.2);
        this._emitter.setEndColorVar(endColorVar);

        // size, in pixels
        this._emitter.setStartSize(1.0);
        this._emitter.setStartSizeVar(1.0);
        this._emitter.setEndSize(32.0);
        this._emitter.setEndSizeVar(8.0);

        // texture
        this._emitter.setTexture(cc.TextureCache.getInstance().addImage(s_fire));
        if(this._emitter.setShapeType)
            this._emitter.setShapeType(cc.PARTICLE_BALL_SHAPE);

        // additive
        this._emitter.setBlendAdditive(false);

        this.setEmitterPosition();
    },
    title:function () {
        return "Varying size";
    }
});

var DemoRing = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleFlower.create();

        this._background.addChild(this._emitter, 10);

        this._emitter.setTexture(cc.TextureCache.getInstance().addImage(s_stars1));
        if(this._emitter.setShapeType)
            this._emitter.setShapeType(cc.PARTICLE_STAR_SHAPE);

        this._emitter.setLifeVar(0);
        this._emitter.setLife(10);
        this._emitter.setSpeed(100);
        this._emitter.setSpeedVar(0);
        this._emitter.setEmissionRate(10000);

        this.setEmitterPosition();
    },
    title:function () {
        return "Ring Demo";
    }
});

var ParallaxParticle = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this._background.getParent().removeChild(this._background, true);
        this._background = null;

        //TODO
        var p = cc.ParallaxNode.create();
        this.addChild(p, 5);

        var p1 = cc.Sprite.create(s_back3);
        var p2 = cc.Sprite.create(s_back3);

        p.addChild(p1, 1, cc.p(0.5, 1), cc.p(0, 250));
        p.addChild(p2, 2, cc.p(1.5, 1), cc.p(0, 50));

        this._emitter = cc.ParticleFlower.create();
        this._emitter.setTexture(cc.TextureCache.getInstance().addImage(s_fire));

        p1.addChild(this._emitter, 10);
        this._emitter.setPosition(250, 200);

        var par = cc.ParticleSun.create();
        p2.addChild(par, 10);
        par.setTexture(cc.TextureCache.getInstance().addImage(s_fire));

        var move = cc.MoveBy.create(4, cc.p(300, 0));
        var move_back = move.reverse();
        var seq = cc.Sequence.create(move, move_back, null);
        p.runAction(cc.RepeatForever.create(seq));
    },
    title:function () {
        return "Parallax + Particles";
    }
});

var DemoParticleFromFile = ParticleDemo.extend({
    _title:"",
    ctor:function(filename) {
        this._super();
        this._title = filename;
    },
    onEnter:function () {
        this._super();
        this.setColor(cc.c3b(0,0,0));
        this.removeChild(this._background, true);
        this._background = null;

        var filename = "res/Particles/" + this._title + ".plist";
        this._emitter = cc.ParticleSystem.create(filename);
        this.addChild(this._emitter, 10);

        this.setEmitterPosition();
    },
    title:function () {
        return this._title;
    }
});

var RadiusMode1 = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this.setColor(cc.c3b(0, 0, 0));
        this.removeChild(this._background, true);
        this._background = null;

        this._emitter = cc.ParticleSystem.createWithTotalParticles(100);
        this.addChild(this._emitter, 10);
        this._emitter.setTexture(cc.TextureCache.getInstance().addImage(s_starsGrayscale));

        // duration
        this._emitter.setDuration(cc.PARTICLE_DURATION_INFINITY);

        // radius mode
        this._emitter.setEmitterMode(cc.PARTICLE_MODE_RADIUS);

        // radius mode: start and end radius in pixels
        this._emitter.setStartRadius(0);
        this._emitter.setStartRadiusVar(0);
        this._emitter.setEndRadius(160);
        this._emitter.setEndRadiusVar(0);

        // radius mode: degrees per second
        this._emitter.setRotatePerSecond(180);
        this._emitter.setRotatePerSecondVar(0);


        // angle
        this._emitter.setAngle(90);
        this._emitter.setAngleVar(0);

        // emitter position
        var size = director.getWinSize();
        this._emitter.setPosition(size.width / 2, size.height / 2);
        this._emitter.setPosVar(cc.p(0,0));

        // life of particles
        this._emitter.setLife(5);
        this._emitter.setLifeVar(0);

        // spin of particles
        this._emitter.setStartSpin(0);
        this._emitter.setStartSpinVar(0);
        this._emitter.setEndSpin(0);
        this._emitter.setEndSpinVar(0);

        // color of particles
        var startColor = cc.c4f(0.5, 0.5, 0.5, 1.0);
        this._emitter.setStartColor(startColor);

        var startColorVar = cc.c4f(0.5, 0.5, 0.5, 1.0);
        this._emitter.setStartColorVar(startColorVar);

        var endColor = cc.c4f(0.1, 0.1, 0.1, 0.2);
        this._emitter.setEndColor(endColor);

        var endColorVar = cc.c4f(0.1, 0.1, 0.1, 0.2);
        this._emitter.setEndColorVar(endColorVar);

        // size, in pixels
        this._emitter.setStartSize(32);
        this._emitter.setStartSizeVar(0);
        this._emitter.setEndSize(cc.PARTICLE_START_SIZE_EQUAL_TO_END_SIZE);

        // emits per second
        this._emitter.setEmissionRate(this._emitter.getTotalParticles() / this._emitter.getLife());

        // additive
        this._emitter.setBlendAdditive(false);
    },
    title:function () {
        return "Radius Mode: Spiral";
    }
});

var RadiusMode2 = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this.setColor(cc.c3b(0, 0, 0));
        this.removeChild(this._background, true);
        this._background = null;

        this._emitter = cc.ParticleSystem.createWithTotalParticles(100);
        this.addChild(this._emitter, 10);
        this._emitter.setTexture(cc.TextureCache.getInstance().addImage(s_starsGrayscale));

        // duration
        this._emitter.setDuration(cc.PARTICLE_DURATION_INFINITY);

        // radius mode
        this._emitter.setEmitterMode(cc.PARTICLE_MODE_RADIUS);

        // radius mode: start and end radius in pixels
        this._emitter.setStartRadius(100);
        this._emitter.setStartRadiusVar(0);
        this._emitter.setEndRadius(cc.PARTICLE_START_RADIUS_EQUAL_TO_END_RADIUS);
        this._emitter.setEndRadiusVar(0);

        // radius mode: degrees per second
        this._emitter.setRotatePerSecond(45);
        this._emitter.setRotatePerSecondVar(0);


        // angle
        this._emitter.setAngle(90);
        this._emitter.setAngleVar(0);

        // emitter position
        var size = director.getWinSize();
        this._emitter.setPosition(size.width / 2, size.height / 2);
        this._emitter.setPosVar(cc.p(0,0));

        // life of particles
        this._emitter.setLife(4);
        this._emitter.setLifeVar(0);

        // spin of particles
        this._emitter.setStartSpin(0);
        this._emitter.setStartSpinVar(0);
        this._emitter.setEndSpin(0);
        this._emitter.setEndSpinVar(0);

        // color of particles
        var startColor = cc.c4f(0.5, 0.5, 0.5, 1.0);
        this._emitter.setStartColor(startColor);

        var startColorVar = cc.c4f(0.5, 0.5, 0.5, 1.0);
        this._emitter.setStartColorVar(startColorVar);

        var endColor = cc.c4f(0.1, 0.1, 0.1, 0.2);
        this._emitter.setEndColor(endColor);

        var endColorVar = cc.c4f(0.1, 0.1, 0.1, 0.2);
        this._emitter.setEndColorVar(endColorVar);

        // size, in pixels
        this._emitter.setStartSize(32);
        this._emitter.setStartSizeVar(0);
        this._emitter.setEndSize(cc.PARTICLE_START_SIZE_EQUAL_TO_END_SIZE);

        // emits per second
        this._emitter.setEmissionRate(this._emitter.getTotalParticles() / this._emitter.getLife());

        // additive
        this._emitter.setBlendAdditive(false);
    },
    title:function () {
        return "Radius Mode: Semi Circle";
    }
});

var Issue704 = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this.setColor(cc.c3b(0, 0, 0));
        this.removeChild(this._background, true);
        this._background = null;

        this._emitter = cc.ParticleSystem.createWithTotalParticles(100);
        this.addChild(this._emitter, 10);
        this._emitter.setTexture(cc.TextureCache.getInstance().addImage(s_fire));
        if(this._emitter.setShapeType)
            this._emitter.setShapeType(cc.PARTICLE_BALL_SHAPE);

        // duration
        this._emitter.setDuration(cc.PARTICLE_DURATION_INFINITY);

        // radius mode
        this._emitter.setEmitterMode(cc.PARTICLE_MODE_RADIUS);

        // radius mode: start and end radius in pixels
        this._emitter.setStartRadius(50);
        this._emitter.setStartRadiusVar(0);
        this._emitter.setEndRadius(cc.PARTICLE_START_RADIUS_EQUAL_TO_END_RADIUS);
        this._emitter.setEndRadiusVar(0);

        // radius mode: degrees per second
        this._emitter.setRotatePerSecond(0);
        this._emitter.setRotatePerSecondVar(0);


        // angle
        this._emitter.setAngle(90);
        this._emitter.setAngleVar(0);

        // emitter position
        var size = director.getWinSize();
        this._emitter.setPosition(size.width / 2, size.height / 2);
        this._emitter.setPosVar(cc.p(0,0));

        // life of particles
        this._emitter.setLife(5);
        this._emitter.setLifeVar(0);

        // spin of particles
        this._emitter.setStartSpin(0);
        this._emitter.setStartSpinVar(0);
        this._emitter.setEndSpin(0);
        this._emitter.setEndSpinVar(0);

        // color of particles
        var startColor = cc.c4f(0.5, 0.5, 0.5, 1.0);
        this._emitter.setStartColor(startColor);

        var startColorVar = cc.c4f(0.5, 0.5, 0.5, 1.0);
        this._emitter.setStartColorVar(startColorVar);

        var endColor = cc.c4f(0.1, 0.1, 0.1, 0.2);
        this._emitter.setEndColor(endColor);

        var endColorVar = cc.c4f(0.1, 0.1, 0.1, 0.2);
        this._emitter.setEndColorVar(endColorVar);

        // size, in pixels
        this._emitter.setStartSize(16);
        this._emitter.setStartSizeVar(0);
        this._emitter.setEndSize(cc.PARTICLE_START_SIZE_EQUAL_TO_END_SIZE);

        // emits per second
        this._emitter.setEmissionRate(this._emitter.getTotalParticles() / this._emitter.getLife());

        // additive
        this._emitter.setBlendAdditive(false);

        var rot = cc.RotateBy.create(16, 360);
        this._emitter.runAction(cc.RepeatForever.create(rot));
    },
    title:function () {
        return "Issue 704. Free + Rot";
    },
    subtitle:function () {
        return "Emitted particles should not rotate";
    }
});

var Issue870 = ParticleDemo.extend({
    _index:0,
    onEnter:function () {
        this._super();

        this.setColor(cc.c3b(0, 0, 0));
        this.removeChild(this._background, true);
        this._background = null;

        var system = cc.ParticleSystem.create("res/Particles/SpinningPeas.plist");
        system.setTextureWithRect(cc.TextureCache.getInstance().addImage(s_particles), cc.rect(0, 0, 32, 32));
        this.addChild(system, 10);
        this._emitter = system;

        this._index = 0;
        this.schedule(this.updateQuads, 2.0);
    },
    title:function () {
        return "Issue 870. SubRect";
    },
    subtitle:function () {
        return "Every 2 seconds the particle should change";
    },
    updateQuads:function (dt) {
        this._index = (this._index + 1) % 4;
        var rect = cc.rect(this._index * 32, 0, 32, 32);
        this._emitter.setTextureWithRect(this._emitter.getTexture(), rect);
    }
});
