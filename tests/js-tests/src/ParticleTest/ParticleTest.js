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
var TAG_LABEL_ATLAS = 1;

var particleSceneIdx = -1;

var ParticleTestScene = TestScene.extend({
    runThisTest:function (num) {
        particleSceneIdx = (num || num == 0) ? (num - 1) : -1;

        this.addChild(nextParticleAction());
        director.runScene(this);
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
    function(){
        return new DemoParticleFromFile("SpinningPeas");
    },
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
    },
    function() {
        return new ParticleResizeTest();
    },
    function() {
        return new DemoPause();
    }
];

if( 'opengl' in cc.sys.capabilities && cc._renderType === cc.game.RENDER_TYPE_WEBGL){
    particleSceneArr.push( function () {
        return new ParallaxParticle();
    });
    particleSceneArr.push(function () {
        return new ParticleBatchTest();
    });
}


var nextParticleAction = function () {
    particleSceneIdx++;
    particleSceneIdx = particleSceneIdx % particleSceneArr.length;
    return particleSceneArr[particleSceneIdx]();
};

var backParticleAction = function () {
    particleSceneIdx--;
    if (particleSceneIdx < 0)
        particleSceneIdx += particleSceneArr.length;

    return particleSceneArr[particleSceneIdx]();
};

var restartParticleAction = function () {
    return particleSceneArr[particleSceneIdx]();
};

var ParticleDemo = BaseTestLayer.extend({
    _emitter:null,
    _background:null,
    _shapeModeButton:null,
    _textureModeButton:null,
    _isPressed:false,

    setColor:function () {
    },

    ctor:function () {
        this._super(cc.color(0,0,0,255), cc.color(98,99,117,255));
        this._emitter = null;

        if ('touches' in cc.sys.capabilities){
            cc.eventManager.addListener({
                event: cc.EventListener.TOUCH_ALL_AT_ONCE,
                onTouchesBegan:function (touches, event) {
                    event.getCurrentTarget()._moveToTouchPoint(touches[0].getLocation());
                },
                onTouchesMoved:function (touches, event) {
                    event.getCurrentTarget()._moveToTouchPoint(touches[0].getLocation());
                }
            }, this);
        } else if ('mouse' in cc.sys.capabilities)
            cc.eventManager.addListener({
                event: cc.EventListener.MOUSE,
                onMouseDown: function(event){
                    event.getCurrentTarget()._moveToTouchPoint(event.getLocation());
                },
                onMouseMove: function(event){
                    if(event.getButton() == cc.EventMouse.BUTTON_LEFT)
                        event.getCurrentTarget()._moveToTouchPoint(event.getLocation());
                }
            }, this);

        var s = director.getWinSize();

        var freeBtnNormal = new cc.Sprite(s_MovementMenuItem, cc.rect(0, 23 * 2, 123, 23));
        var freeBtnSelected = new cc.Sprite(s_MovementMenuItem, cc.rect(0, 23, 123, 23));
        var freeBtnDisabled = new cc.Sprite(s_MovementMenuItem, cc.rect(0, 0, 123, 23));

        var relativeBtnNormal = new cc.Sprite(s_MovementMenuItem, cc.rect(123, 23 * 2, 138, 23));
        var relativeBtnSelected = new cc.Sprite(s_MovementMenuItem, cc.rect(123, 23, 138, 23));
        var relativeBtnDisabled = new cc.Sprite(s_MovementMenuItem, cc.rect(123, 0, 138, 23));

        var groupBtnNormal = new cc.Sprite(s_MovementMenuItem, cc.rect(261, 23 * 2, 136, 23));
        var groupBtnSelected = new cc.Sprite(s_MovementMenuItem, cc.rect(261, 23, 136, 23));
        var groupBtnDisabled = new cc.Sprite(s_MovementMenuItem, cc.rect(261, 0, 136, 23));

        var selfPoint = this;
        this._freeMovementButton = new cc.MenuItemSprite(freeBtnNormal, freeBtnSelected, freeBtnDisabled,
            function () {
                selfPoint._emitter.setPositionType(cc.ParticleSystem.TYPE_RELATIVE);
                selfPoint._relativeMovementButton.setVisible(true);
                selfPoint._freeMovementButton.setVisible(false);
                selfPoint._groupMovementButton.setVisible(false);
            });
        this._freeMovementButton.x = 10;
        this._freeMovementButton.y = 150;
        this._freeMovementButton.setAnchorPoint(0, 0);

        this._relativeMovementButton = new cc.MenuItemSprite(relativeBtnNormal, relativeBtnSelected, relativeBtnDisabled,
            function () {
                selfPoint._emitter.setPositionType(cc.ParticleSystem.TYPE_GROUPED);
                selfPoint._relativeMovementButton.setVisible(false);
                selfPoint._freeMovementButton.setVisible(false);
                selfPoint._groupMovementButton.setVisible(true);
            });
        this._relativeMovementButton.setVisible(false);
        this._relativeMovementButton.x = 10;
        this._relativeMovementButton.y = 150;
        this._relativeMovementButton.setAnchorPoint(0, 0);

        this._groupMovementButton = new cc.MenuItemSprite(groupBtnNormal, groupBtnSelected, groupBtnDisabled,
            function () {
                selfPoint._emitter.setPositionType(cc.ParticleSystem.TYPE_FREE);
                selfPoint._relativeMovementButton.setVisible(false);
                selfPoint._freeMovementButton.setVisible(true);
                selfPoint._groupMovementButton.setVisible(false);
            });
        this._groupMovementButton.setVisible(false);
        this._groupMovementButton.x = 10;
        this._groupMovementButton.y = 150;
        this._groupMovementButton.setAnchorPoint(0, 0);

        var spriteNormal = new cc.Sprite(s_shapeModeMenuItem, cc.rect(0, 23 * 2, 115, 23));
        var spriteSelected = new cc.Sprite(s_shapeModeMenuItem, cc.rect(0, 23, 115, 23));
        var spriteDisabled = new cc.Sprite(s_shapeModeMenuItem, cc.rect(0, 0, 115, 23));

        this._shapeModeButton = new cc.MenuItemSprite(spriteNormal, spriteSelected, spriteDisabled,
            function () {
                if (selfPoint._emitter.setDrawMode)
                    selfPoint._emitter.setDrawMode(cc.ParticleSystem.TEXTURE_MODE);
                selfPoint._textureModeButton.setVisible(true);
                selfPoint._shapeModeButton.setVisible(false);
            });
        this._shapeModeButton.setVisible(false);
        this._shapeModeButton.x = 10;
        this._shapeModeButton.y = 100;
        this._shapeModeButton.setAnchorPoint(0, 0);

        var spriteNormal_t = new cc.Sprite(s_textureModeMenuItem, cc.rect(0, 23 * 2, 115, 23));
        var spriteSelected_t = new cc.Sprite(s_textureModeMenuItem, cc.rect(0, 23, 115, 23));
        var spriteDisabled_t = new cc.Sprite(s_textureModeMenuItem, cc.rect(0, 0, 115, 23));

        this._textureModeButton = new cc.MenuItemSprite(spriteNormal_t, spriteSelected_t, spriteDisabled_t,
            function () {
                if (selfPoint._emitter.setDrawMode)
                    selfPoint._emitter.setDrawMode(cc.ParticleSystem.SHAPE_MODE);
                selfPoint._textureModeButton.setVisible(false);
                selfPoint._shapeModeButton.setVisible(true);
            });
        this._textureModeButton.x = 10;
        this._textureModeButton.y = 100;
        this._textureModeButton.setAnchorPoint(0, 0);

        if ('opengl' in cc.sys.capabilities ) {
            // Shape type is not compatible with JSB
            this._textureModeButton.enabled = false;
        }

        var menu = new cc.Menu( this._shapeModeButton, this._textureModeButton,
            this._freeMovementButton, this._relativeMovementButton, this._groupMovementButton);
        menu.x = 0;
        menu.y = 0;

        this.addChild(menu, 100);
        //TODO
        var labelAtlas = new cc.LabelAtlas("0123456789", s_fpsImages, 12, 32, '.');
        this.addChild(labelAtlas, 100, TAG_LABEL_ATLAS);
        labelAtlas.x = s.width - 66;
        labelAtlas.y = 50;

        // moving background
        this._background = new cc.Sprite(s_back3);
        this.addChild(this._background, 5);
        this._background.x = s.width / 2;
        this._background.y = s.height - 180;

        var move = cc.moveBy(4, cc.p(300, 0));
        var move_back = move.reverse();

        var seq = cc.sequence(move, move_back);
        this._background.runAction(seq.repeatForever());
        this.scheduleUpdate();
    },

    onEnter:function () {
        this._super();

        var pLabel = this.getChildByTag(BASE_TEST_TITLE_TAG);
        pLabel.setString(this.title());
    },
    title:function () {
        return "No title";
    },

    subtitle:function () {
        return "(Tap the Screen)";
    },

    onRestartCallback:function (sender) {
        this._emitter.resetSystem();
    },
    onNextCallback:function (sender) {
        var s = new ParticleTestScene();
        s.addChild(nextParticleAction());
        director.runScene(s);
    },
    onBackCallback:function (sender) {
        var s = new ParticleTestScene();
        s.addChild(backParticleAction());
        director.runScene(s);
    },
    toggleCallback:function (sender) {
        if (this._emitter.getPositionType() == cc.ParticleSystem.TYPE_GROUPED)
            this._emitter.setPositionType(cc.ParticleSystem.TYPE_FREE);
        else if (this._emitter.getPositionType() == cc.ParticleSystem.TYPE_FREE)
            this._emitter.setPositionType(cc.ParticleSystem.TYPE_RELATIVE);
        else if (this._emitter.getPositionType() == cc.ParticleSystem.TYPE_RELATIVE)
            this._emitter.setPositionType(cc.ParticleSystem.TYPE_GROUPED);
    },

    _moveToTouchPoint: function (location) {
        var pos = cc.p(0, 0);
        if (this._background) {
            pos = this._background.convertToWorldSpace(cc.p(0, 0));
        }
        this._emitter.x = location.x - pos.x;
        this._emitter.y = location.y - pos.y;
    },

    update:function (dt) {
        if (this._emitter) {
            var atlas = this.getChildByTag(TAG_LABEL_ATLAS);
            atlas.setString(this._emitter.getParticleCount().toFixed(0));
        }
    },
    setEmitterPosition:function () {
        var sourcePos = this._emitter.getSourcePosition();
        if (sourcePos.x === 0 && sourcePos.y === 0)
            this._emitter.x = 200;
            this._emitter.y = 70;
    },
    // automation
    numberOfPendingTests:function() {
        return ( (particleSceneArr.length-1) - particleSceneIdx );
    },

    getTestNumber:function() {
        return particleSceneIdx;
    }
});

var DemoFirework = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this._emitter = new cc.ParticleFireworks();
        this._background.addChild(this._emitter, 10);
        this._emitter.texture = cc.textureCache.addImage(s_stars1);
        if (this._emitter.setShapeType)
            this._emitter.setShapeType(cc.ParticleSystem.STAR_SHAPE);
        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleFireworks";
    }
});

var DemoFire = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this._emitter = new cc.ParticleFire();
        this._background.addChild(this._emitter, 10);

        this._emitter.texture = cc.textureCache.addImage(s_fire);//.pvr"];
        if (this._emitter.setShapeType)
            this._emitter.setShapeType(cc.ParticleSystem.BALL_SHAPE);

        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleFire";
    }
});

var DemoSun = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this._emitter = new cc.ParticleSun();
        this._background.addChild(this._emitter, 10);
        this._emitter.texture = cc.textureCache.addImage(s_fire);
        if (this._emitter.setShapeType)
            this._emitter.setShapeType(cc.ParticleSystem.BALL_SHAPE);

        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleSun";
    }
});

var DemoPause = ParticleDemo.extend({
    onEnter:function () {
    this._super();

    this._emitter = new cc.ParticleSmoke();
    this._background.addChild(this._emitter, 10);
    this._emitter.texture = cc.textureCache.addImage(s_fire);
    if (this._emitter.setShapeType)
    this._emitter.setShapeType(cc.ParticleSystem.BALL_SHAPE);

    this.setEmitterPosition();
    },
    title:function () {
    return "Pause Particle";
    }
    });

var DemoGalaxy = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this._emitter = new cc.ParticleGalaxy();
        this._background.addChild(this._emitter, 10);
        this._emitter.texture = cc.textureCache.addImage(s_fire);
        if (this._emitter.setShapeType)
            this._emitter.setShapeType(cc.ParticleSystem.BALL_SHAPE);

        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleGalaxy";
    }
});

var DemoFlower = ParticleDemo.extend({
    _title:"ParticleFlower",

    onEnter:function () {
        this._super();

        this._emitter = new cc.ParticleFlower();
        this._background.addChild(this._emitter, 10);
        this._emitter.texture = cc.textureCache.addImage(s_stars1);

        if (this._emitter.setShapeType)
            this._emitter.setShapeType(cc.ParticleSystem.STAR_SHAPE);

        this.setEmitterPosition();
    },
    title:function () {
        return this._title;
    }
});

var DemoBigFlower = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this._emitter = new cc.ParticleSystem(50);

        this._background.addChild(this._emitter, 10);
        this._emitter.texture = cc.textureCache.addImage(s_stars1);
        this._emitter.shapeType = cc.ParticleSystem.STAR_SHAPE;

        this._emitter.duration = -1;

        // gravity
        this._emitter.gravity = cc.p(0, 0);

        // angle
        this._emitter.angle = 90;
        this._emitter.angleVar = 360;

        // speed of particles
        this._emitter.speed = 160;
        this._emitter.speedVar = 20;

        // radial
        this._emitter.radialAccel = -120;
        this._emitter.radialAccelVar = 0;

        // tangential
        this._emitter.tangentialAccel = 30;
        this._emitter.tangentialAccelVar = 0;

        // emitter position
        this._emitter.x = 160;
        this._emitter.y = 240;
        this._emitter.posVar = cc.p(0, 0);

        // life of particles
        this._emitter.life = 4;
        this._emitter.lifeVar = 1;

        // spin of particles
        this._emitter.startSpin = 0;
        this._emitter.startSizeVar = 0;
        this._emitter.endSpin = 0;
        this._emitter.endSpinVar = 0;

        // color of particles
        this._emitter.startColor = cc.color(128, 128, 128, 255);
        this._emitter.startColorVar = cc.color(128, 128, 128, 255);
        this._emitter.endColor = cc.color(26, 26, 26, 50);
        this._emitter.endColorVar = cc.color(26, 26, 26, 50);

        // size, in pixels
        this._emitter.startSize = 80.0;
        this._emitter.startSizeVar = 40.0;
        this._emitter.endSize = cc.ParticleSystem.START_SIZE_EQUAL_TO_END_SIZE;

        // emits per second
        this._emitter.emissionRate = this._emitter.totalParticles / this._emitter.life;

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

        this._emitter = new cc.ParticleSystem(("opengl" in cc.sys.capabilities) ? 300 : 150);

        this._background.addChild(this._emitter, 10);
        this._emitter.texture = cc.textureCache.addImage(s_stars2);
        if (this._emitter.setShapeType)
            this._emitter.setShapeType(cc.ParticleSystem.STAR_SHAPE);

        // duration
        this._emitter.duration = -1;

        // gravity
        this._emitter.gravity = cc.p(0, 0);

        // angle
        this._emitter.angle = 90;
        this._emitter.angleVar = 360;

        // speed of particles
        this._emitter.speed = 160;
        this._emitter.speedVar = 20;

        // radial
        this._emitter.radialAccel = -120;
        this._emitter.radialAccelVar = 0;

        // tangential
        this._emitter.tangentialAccel = 30;
        this._emitter.tangentialAccelVar = 0;

        // emitter position
        this._emitter.x = 160;
        this._emitter.y = 240;
        this._emitter.posVar = cc.p(0, 0);

        // life of particles
        this._emitter.life = 3;
        this._emitter.lifeVar = 1;

        // spin of particles
        this._emitter.startSpin = 0;
        this._emitter.startSpinVar = 0;
        this._emitter.endSpin = 0;
        this._emitter.endSpinVar = 2000;

        this._emitter.startColor = cc.color(128, 128, 128, 255);
        this._emitter.startColorVar = cc.color(128, 128, 128, 255);
        this._emitter.endColor = cc.color(26, 26, 26, 50);
        this._emitter.endColorVar = cc.color(26, 26, 26, 50);

        // size, in pixels
        this._emitter.startSize = 30.0;
        this._emitter.startSizeVar = 0;
        this._emitter.endSize = cc.ParticleSystem.START_SIZE_EQUAL_TO_END_SIZE;

        // emits per second
        this._emitter.emissionRate = this._emitter.totalParticles / this._emitter.life;

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

        this._emitter = new cc.ParticleMeteor();
        this._background.addChild(this._emitter, 10);

        this._emitter.texture = cc.textureCache.addImage(s_fire);
        this._emitter.shapeType = cc.ParticleSystem.BALL_SHAPE;

        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleMeteor";
    }
});

var DemoSpiral = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this._emitter = new cc.ParticleSpiral();
        this._background.addChild(this._emitter, 10);

        this._emitter.texture = cc.textureCache.addImage(s_fire);
        this._emitter.shapeType = cc.ParticleSystem.BALL_SHAPE;

        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleSpiral";
    }
});

var DemoExplosion = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this._emitter = new cc.ParticleExplosion();
        this._background.addChild(this._emitter, 10);

        this._emitter.texture = cc.textureCache.addImage(s_stars1);
        this._emitter.shapeType = cc.ParticleSystem.STAR_SHAPE;

        this._emitter.setAutoRemoveOnFinish(true);

        this.setEmitterPosition();
    },
    onExit: function() {
        this._super();
    },
    title:function () {
        return "ParticleExplosion";
    }
});

var DemoSmoke = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this._emitter = new cc.ParticleSmoke();
        this._background.addChild(this._emitter, 10);
        this._emitter.texture = cc.textureCache.addImage(s_fire);

        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleSmoke";
    }
});

var DemoSnow = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this._emitter = new cc.ParticleSnow();
        this._background.addChild(this._emitter, 10);

        this._emitter.life = 3;
        this._emitter.lifeVar = 1;

        // gravity
        this._emitter.gravity = cc.p(0, -10);

        // speed of particles
        this._emitter.speed = 130;
        this._emitter.speedVar = 30;


        var startColor = this._emitter.startColor;
        startColor.r = 230;
        startColor.g = 230;
        startColor.b = 230;
        this._emitter.startColor = startColor;

        var startColorVar = this._emitter.startColorVar;
        startColorVar.b = 26;
        this._emitter.startColorVar = startColorVar;

        this._emitter.emissionRate = this._emitter.totalParticles / this._emitter.life;

        this._emitter.texture = cc.textureCache.addImage(s_snow);
        this._emitter.shapeType = cc.ParticleSystem.STAR_SHAPE;

        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleSnow";
    }
});

var DemoRain = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this._emitter = new cc.ParticleRain();
        this._background.addChild(this._emitter, 10);

        this._emitter.life = 4;

        this._emitter.texture = cc.textureCache.addImage(s_fire);
        this._emitter.shapeType = cc.ParticleSystem.BALL_SHAPE;

        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleRain";
    }
});

var DemoModernArt = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this._emitter = new cc.ParticleSystem(("opengl" in cc.sys.capabilities) ? 1000 : 200);

        this._background.addChild(this._emitter, 10);

        var winSize = director.getWinSize();

        // duration
        this._emitter.duration = -1;

        // gravity
        this._emitter.gravity = cc.p(0, 0);

        // angle
        this._emitter.angle = 0;
        this._emitter.angleVar = 360;

        // radial
        this._emitter.radialAccel = 70;
        this._emitter.radialAccelVar = 10;

        // tangential
        this._emitter.tangentialAccel = 80;
        this._emitter.tangentialAccelVar = 0;

        // speed of particles
        this._emitter.speed = 50;
        this._emitter.speedVar = 10;

        // life of particles
        this._emitter.life = 2.0;
        this._emitter.lifeVar = 0.3;

        // emits per frame
        this._emitter.emissionRate = this._emitter.totalParticles / this._emitter.life;

        // color of particles
        this._emitter.startColor = cc.color(128, 128, 128, 255);
        this._emitter.startColorVar = cc.color(128, 128, 128, 255);
        this._emitter.endColor = cc.color(26, 26, 26, 50);
        this._emitter.endColorVar = cc.color(26, 26, 26, 50);

        // size, in pixels
        this._emitter.startSize = 1.0;
        this._emitter.startSizeVar = 1.0;
        this._emitter.endSize = 32.0;
        this._emitter.endSizeVar = 8.0;

        // texture
        this._emitter.texture = cc.textureCache.addImage(s_fire);
        this._emitter.shapeType = cc.ParticleSystem.BALL_SHAPE;

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

        this._emitter = new cc.ParticleFlower();

        this._background.addChild(this._emitter, 10);

        this._emitter.texture = cc.textureCache.addImage(s_stars1);
        this._emitter.shapeType = cc.ParticleSystem.STAR_SHAPE;

        this._emitter.lifeVar = 0;
        this._emitter.life = 10;
        this._emitter.speed = 100;
        this._emitter.speedVar = 0;
        this._emitter.emissionRate = 10000;

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
        var p = new cc.ParallaxNode();
        this.addChild(p, 5);

        var p1 = new cc.Sprite(s_back3);
        var p2 = new cc.Sprite(s_back3);

        p.addChild(p1, 1, cc.p(0.5, 1), cc.p(0, 250));
        p.addChild(p2, 2, cc.p(1.5, 1), cc.p(0, 50));

        this._emitter = new cc.ParticleFlower();
        this._emitter.texture = cc.textureCache.addImage(s_fire);

        p1.addChild(this._emitter, 10);
        this._emitter.x = 250;
        this._emitter.y = 200;

        var par = new cc.ParticleSun();
        p2.addChild(par, 10);
        par.texture = cc.textureCache.addImage(s_fire);

        var move = cc.moveBy(4, cc.p(300, 0));
        var move_back = move.reverse();
        var seq = cc.sequence(move, move_back);
        p.runAction(seq.repeatForever());
    },
    title:function () {
        return "Parallax + Particles";
    }
});

var DemoParticleFromFile = ParticleDemo.extend({
    _title:"",
    ctor:function (filename) {
        this._super();
        this._title = filename;
    },
    onEnter:function () {
        this._super();
        this.setColor(cc.color(0, 0, 0));
        this.removeChild(this._background, true);
        this._background = null;

        this._emitter = new cc.ParticleSystem(s_resprefix + "Particles/" + this._title + ".plist");
        // test create from a object
        // var plistData = jsb.fileUtils.getValueMapFromFile(s_resprefix + "Particles/" + this._title + ".plist");
        // this._emitter = new cc.ParticleSystem(plistData);

        this.addChild(this._emitter, 10);

        if (this._title == "Flower") {
            this._emitter.shapeType = cc.ParticleSystem.STAR_SHAPE;
        }//else if( this._title == "Upsidedown"){
        //   this._emitter.setDrawMode(cc.ParticleSystem.TEXTURE_MODE);
        //}

        this.setEmitterPosition();
    },

    setEmitterPosition:function () {
        var sourcePos = this._emitter.getSourcePosition();
        if (sourcePos.x === 0 && sourcePos.y === 0)
            this._emitter.x = director.getWinSize().width / 2;
            this._emitter.y = director.getWinSize().height / 2 - 50;
    },

    title:function () {
        return this._title;
    }
});

var RadiusMode1 = ParticleDemo.extend({
    onEnter:function () {
        this._super();

        this.setColor(cc.color(0, 0, 0));
        this.removeChild(this._background, true);
        this._background = null;

        this._emitter = new cc.ParticleSystem(100);
        this.addChild(this._emitter, 10);
        this._emitter.texture = cc.textureCache.addImage(s_starsGrayscale);

        // duration
        this._emitter.duration = cc.ParticleSystem.DURATION_INFINITY;

        // radius mode
        this._emitter.emitterMode = cc.ParticleSystem.MODE_RADIUS;

        // radius mode: start and end radius in pixels
        this._emitter.startRadius = 0;
        this._emitter.startRadiusVar = 0;
        this._emitter.endRadius = 160;
        this._emitter.endRadiusVar = 0;

        // radius mode: degrees per second
        this._emitter.rotatePerS = 180;
        this._emitter.rotatePerSVar = 0;


        // angle
        this._emitter.angle = 90;
        this._emitter.angleVar = 0;

        // emitter position
        var size = director.getWinSize();
        this._emitter.x = size.width / 2;
        this._emitter.y = size.height / 2;
        this._emitter.posVar = cc.p(0, 0);

        // life of particles
        this._emitter.life = 5;
        this._emitter.lifeVar = 0;

        // spin of particles
        this._emitter.startSpin = 0;
        this._emitter.startSpinVar = 0;
        this._emitter.endSpin = 0;
        this._emitter.endSpinVar = 0;

        // color of particles
        this._emitter.startColor = cc.color(128, 128, 128, 255);
        this._emitter.startColorVar = cc.color(128, 128, 128, 255);
        this._emitter.endColor = cc.color(26, 26, 26, 50);
        this._emitter.endColorVar = cc.color(26, 26, 26, 50);

        // size, in pixels
        this._emitter.startSize = 32;
        this._emitter.startSizeVar = 0;
        this._emitter.endSize = cc.ParticleSystem.START_SIZE_EQUAL_TO_END_SIZE;

        // emits per second
        this._emitter.emissionRate = this._emitter.totalParticles / this._emitter.life;

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

        this.color = cc.color(0, 0, 0);
        this.removeChild(this._background, true);
        this._background = null;

        this._emitter = new cc.ParticleSystem(100);
        this.addChild(this._emitter, 10);
        this._emitter.texture = cc.textureCache.addImage(s_starsGrayscale);

        // duration
        this._emitter.duration = cc.ParticleSystem.DURATION_INFINITY;

        // radius mode
        this._emitter.emitterMode = cc.ParticleSystem.MODE_RADIUS;

        // radius mode: start and end radius in pixels
        this._emitter.startRadius = 100;
        this._emitter.startRadiusVar = 0;
        this._emitter.endRadius = cc.ParticleSystem.START_RADIUS_EQUAL_TO_END_RADIUS;
        this._emitter.endRadiusVar = 0;

        // radius mode: degrees per second
        this._emitter.rotatePerS = 45;
        this._emitter.rotatePerSVar = 0;

        // angle
        this._emitter.angle = 90;
        this._emitter.angleVar = 0;

        // emitter position
        var size = director.getWinSize();
        this._emitter.x = size.width / 2;
        this._emitter.y = size.height / 2;
        this._emitter.posVar = cc.p(0, 0);

        // life of particles
        this._emitter.life = 4;
        this._emitter.lifeVar = 0;

        // spin of particles
        this._emitter.startSpin = 0;
        this._emitter.startSpinVar = 0;
        this._emitter.endSpin = 0;
        this._emitter.endSpinVar = 0;

        // color of particles
        this._emitter.startColor = cc.color(128, 128, 128, 255);
        this._emitter.startColorVar = cc.color(128, 128, 128, 255);
        this._emitter.endColor = cc.color(26, 26, 26, 50);
        this._emitter.endColorVar = cc.color(26, 26, 26, 50);

        // size, in pixels
        this._emitter.startSize = 32;
        this._emitter.startSizeVar = 0;
        this._emitter.endSize = cc.ParticleSystem.START_SIZE_EQUAL_TO_END_SIZE;

        // emits per second
        this._emitter.emissionRate = this._emitter.totalParticles / this._emitter.life;

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

        this.color = cc.color(0, 0, 0);
        this.removeChild(this._background, true);
        this._background = null;

        this._emitter = new cc.ParticleSystem(100);
        this.addChild(this._emitter, 10);
        this._emitter.texture = cc.textureCache.addImage(s_fire);
        this._emitter.shapeType = cc.ParticleSystem.BALL_SHAPE;

        // duration
        this._emitter.duration = cc.ParticleSystem.DURATION_INFINITY;

        // radius mode
        this._emitter.emitterMode = cc.ParticleSystem.MODE_RADIUS;

        // radius mode: start and end radius in pixels
        this._emitter.startRadius = 50;
        this._emitter.startRadiusVar = 0;
        this._emitter.endRadius = cc.ParticleSystem.START_RADIUS_EQUAL_TO_END_RADIUS;
        this._emitter.endRadiusVar = 0;

        // radius mode: degrees per second
        this._emitter.rotatePerS = 0;
        this._emitter.rotatePerSVar = 0;

        // angle
        this._emitter.angle = 90;
        this._emitter.angleVar = 0;

        // emitter position
        var size = director.getWinSize();
        this._emitter.x = size.width / 2;
        this._emitter.y = size.height / 2;
        this._emitter.posVar = cc.p(0, 0);

        // life of particles
        this._emitter.life = 5;
        this._emitter.lifeVar = 0;

        // spin of particles
        this._emitter.startSpin = 0;
        this._emitter.startSpinVar = 0;
        this._emitter.endSpin = 0;
        this._emitter.endSpinVar = 0;

        // color of particles
        this._emitter.startColor = cc.color(128, 128, 128, 255);
        this._emitter.startColorVar = cc.color(128, 128, 128, 255);
        this._emitter.endColor = cc.color(26, 26, 26, 50);
        this._emitter.endColorVar = cc.color(26, 26, 26, 50);

        // size, in pixels
        this._emitter.startSize = 16;
        this._emitter.startSizeVar = 0;
        this._emitter.endSize = cc.ParticleSystem.START_SIZE_EQUAL_TO_END_SIZE;

        // emits per second
        this._emitter.emissionRate = this._emitter.totalParticles / this._emitter.life;

        // additive
        this._emitter.setBlendAdditive(false);

        var rot = cc.rotateBy(16, 360);
        this._emitter.runAction(rot.repeatForever());
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

        this.setColor(cc.color(0, 0, 0));
        this.removeChild(this._background, true);
        this._background = null;

        var system = new cc.ParticleSystem(s_resprefix + "Particles/SpinningPeas.plist");
        system.setTextureWithRect(cc.textureCache.addImage(s_particles), cc.rect(0, 0, 32, 32));
        this.addChild(system, 10);
        this._emitter = system;
        this._emitter.drawMode = cc.ParticleSystem.TEXTURE_MODE;
        this._emitter.x = director.getWinSize().width / 2;
        this._emitter.y = director.getWinSize().height / 2 - 50;
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
        this._emitter.setTextureWithRect(this._emitter.texture, rect);
    }
});

var ParticleBatchTest = ParticleDemo.extend({
    _index:0,
    onEnter:function () {
        this._super();

        var emitter1 = new cc.ParticleSystem(s_resprefix + 'Particles/LavaFlow.plist');
        emitter1.startColor = cc.color(255, 0, 0, 255);
        var emitter2 = new cc.ParticleSystem(s_resprefix + 'Particles/LavaFlow.plist');
        emitter2.startColor = cc.color(0, 255, 0, 255);
        var emitter3 = new cc.ParticleSystem(s_resprefix + 'Particles/LavaFlow.plist');
        emitter3.startColor = cc.color(0, 0, 255, 255);

        emitter1.x = winSize.width / 1.25;

        emitter1.y = winSize.height / 1.25;
        emitter2.x = winSize.width / 2;
        emitter2.y = winSize.height / 2;
        emitter3.x = winSize.width / 4;
        emitter3.y = winSize.height / 4;

        var batch = new cc.ParticleBatchNode(emitter1.texture);

        batch.addChild(emitter1);
        batch.addChild(emitter2);
        batch.addChild(emitter3);

        this.addChild(batch, 10);

        // to be able to use "reset" button
        this.removeChild(this._background, true);
        this._background = null;
        this._emitter = emitter1;
    },
    title:function () {
        return "Particle Batch Test";
    },
    subtitle:function () {
        return "You should 3 particles. They are batched";
    }
});

var ParticleResizeTest = ParticleDemo.extend({
    _index:0,
    onEnter:function () {
        this._super();

        var emitter1 = new cc.ParticleSystem( s_resprefix + 'Particles/LavaFlow.plist');
        emitter1.x = winSize.width/2;
        emitter1.y = winSize.height/2;
        this.addChild(emitter1);

        this.schedule( this.onResizeParticle50, 2 );

        // to be able to use "reset" button
        this.removeChild(this._background, true);
        this._background = null;
        this._emitter = emitter1;
    },
    onResizeParticle50:function(dt) {
        this._emitter.totalParticles = 50;
        this.scheduleOnce( this.onResizeParticle400, 1);
    },
    onResizeParticle400:function(dt) {
        this._emitter.totalParticles = 400;
    },

    title:function () {
        return "Particle Resize Test";
    },
    subtitle:function () {
        return "In 2 seconds, the emitter should have only 15 particles. Shall not crash.";
    }
});