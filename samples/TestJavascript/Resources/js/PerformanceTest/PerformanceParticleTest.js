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
var TAG_PARTICLE_SYSTEM = 3;
var TAG_LABEL_ATLAS = 4;
var MAX_PARTICLES = 1000;
var PARTICLE_NODES_INCREASE = 50;
var s_nParCurIdx = 0;
var TAG_PARTICLE_MENU_LAYER = 1000;

////////////////////////////////////////////////////////
//
// ParticleMenuLayer
//
////////////////////////////////////////////////////////
var ParticleMenuLayer = PerformBasicLayer.extend({
    _maxCases:4,
    showCurrentTest:function () {
        var scene = this.getParent();
        var subTest = scene.getSubTestNum();
        var parNum = scene.getParticlesNum();

        var newScene = null;

        switch (this._curCase) {
            case 0:
                newScene = new ParticlePerformTest1;
                break;
            case 1:
                newScene = new ParticlePerformTest2;
                break;
            case 2:
                newScene = new ParticlePerformTest3;
                break;
            case 3:
                newScene = new ParticlePerformTest4;
                break;
        }

        s_nParCurIdx = this._curCase;
        if (newScene) {
            newScene.initWithSubTest(subTest, parNum);
            cc.Director.getInstance().replaceScene(newScene);
        }
    }
});

////////////////////////////////////////////////////////
//
// ParticleMainScene
//
////////////////////////////////////////////////////////
var ParticleMainScene = cc.Scene.extend({
    _lastRenderedCount:null,
    _quantityParticles:null,
    _subtestNumber:null,
    initWithSubTest:function (asubtest, particles) {
        //srandom(0);

        this._subtestNumber = asubtest;
        var s = cc.Director.getInstance().getWinSize();

        this._lastRenderedCount = 0;
        this._quantityParticles = particles;

        cc.MenuItemFont.setFontSize(65);
        var decrease = cc.MenuItemFont.create(" - ", this, this.onDecrease);
        decrease.setColor(cc.c3b(0, 200, 20));
        var increase = cc.MenuItemFont.create(" + ", this, this.onIncrease);
        increase.setColor(cc.c3b(0, 200, 20));

        var menu = cc.Menu.create(decrease, increase, null);
        menu.alignItemsHorizontally();
        menu.setPosition(cc.p(s.width / 2, s.height / 2 + 15));
        this.addChild(menu, 1);

        var infoLabel = cc.LabelTTF.create("0 nodes", "Marker Felt", 30);
        infoLabel.setColor(cc.c3b(0, 200, 20));
        infoLabel.setPosition(cc.p(s.width / 2, s.height - 90));
        this.addChild(infoLabel, 1, TAG_INFO_LAYER);

        // particles on stage
        //var labelAtlas = cc.LabelAtlas.create("0000", "res/Images/fps_images.png", 16, 24, '.');
        var labelAtlas = cc.LabelTTF.create("0000", "Marker Felt", 30);
        this.addChild(labelAtlas, 0, TAG_LABEL_ATLAS);
        labelAtlas.setPosition(cc.p(s.width - 66, 50));

        // Next Prev Test
        var menu = new ParticleMenuLayer(true, 4, s_nParCurIdx);
        this.addChild(menu, 1, TAG_PARTICLE_MENU_LAYER);

        // Sub Tests
        cc.MenuItemFont.setFontSize(40);
        var subMenu = cc.Menu.create(null);
        for (var i = 1; i <= 3; ++i) {
            var str = i.toString();
            var itemFont = cc.MenuItemFont.create(str, this, this.testNCallback);
            itemFont.setTag(i);
            subMenu.addChild(itemFont, 10);

            if (i <= 1) {
                itemFont.setColor(cc.c3b(200, 20, 20));
            }
            else {
                itemFont.setColor(cc.c3b(0, 200, 20));
            }
        }
        subMenu.alignItemsHorizontally();
        subMenu.setPosition(cc.p(s.width / 2, 80));
        this.addChild(subMenu, 2);

        var label = cc.LabelTTF.create(this.title(), "Arial", 40);
        this.addChild(label, 1);
        label.setPosition(cc.p(s.width / 2, s.height - 32));
        label.setColor(cc.c3b(255, 255, 40));

        this.updateQuantityLabel();
        this.createParticleSystem();

        this.schedule(this.step);
    },
    title:function () {
        return "No title";
    },

    step:function (dt) {
        var atlas = this.getChildByTag(TAG_LABEL_ATLAS);
        var emitter = this.getChildByTag(TAG_PARTICLE_SYSTEM);

        var str = emitter.getParticleCount();
        atlas.setString(str);
    },
    createParticleSystem:function () {
        var particleSystem = null;

        /*
         * Tests:
         * 1 Quad Particle System using 32-bit textures (PNG)
         * 2: Quad Particle System using 16-bit textures (PNG)
         * 3: Quad Particle System using 8-bit textures (PNG)
         * 4: Quad Particle System using 4-bit textures (PVRTC)
         */

        this.removeChildByTag(TAG_PARTICLE_SYSTEM, true);

        //todo
        // remove the "fire.png" from the TextureCache cache.
        var texture = cc.TextureCache.getInstance().addImage("res/Images/fire.png");
        cc.TextureCache.getInstance().removeTexture(texture);

        particleSystem = new cc.ParticleSystemQuad();

        switch (this._subtestNumber) {
            case 1:
                cc.Texture2D.setDefaultAlphaPixelFormat(cc.TEXTURE_2D_PIXEL_FORMAT_RGBA8888);
                particleSystem.initWithTotalParticles(this._quantityParticles);
                particleSystem.setTexture(cc.TextureCache.getInstance().addImage("res/Images/fire.png"));
                break;
            case 2:
                cc.Texture2D.setDefaultAlphaPixelFormat(cc.TEXTURE_2D_PIXEL_FORMAT_RGBA4444);
                particleSystem.initWithTotalParticles(this._quantityParticles);
                particleSystem.setTexture(cc.TextureCache.getInstance().addImage("res/Images/fire.png"));
                break;
            case 3:
                cc.Texture2D.setDefaultAlphaPixelFormat(cc.TEXTURE_2D_PIXEL_FORMAT_A8);
                particleSystem.initWithTotalParticles(this._quantityParticles);
                particleSystem.setTexture(cc.TextureCache.getInstance().addImage("res/Images/fire.png"));
                break;
            default:
                particleSystem = null;
                cc.log("Shall not happen!");
                break;
        }
        this.addChild(particleSystem, 0, TAG_PARTICLE_SYSTEM);

        this.doTest();

        // restore the default pixel format
        cc.Texture2D.setDefaultAlphaPixelFormat(cc.TEXTURE_2D_PIXEL_FORMAT_RGBA8888);
    },
    onDecrease:function (sender) {
        this._quantityParticles -= PARTICLE_NODES_INCREASE;
        if (this._quantityParticles < 0)
            this._quantityParticles = 0;

        this.updateQuantityLabel();
        this.createParticleSystem();
    },
    onIncrease:function (sender) {
        this._quantityParticles += PARTICLE_NODES_INCREASE;
        if (this._quantityParticles > MAX_PARTICLES) {
            this._quantityParticles = MAX_PARTICLES;
        }
        this.updateQuantityLabel();
        this.createParticleSystem();
    },
    testNCallback:function (sender) {
        this._subtestNumber = sender.getTag();
        var menu = this.getChildByTag(TAG_PARTICLE_MENU_LAYER);
        menu.restartCallback(sender);
    },
    updateQuantityLabel:function () {
        if (this._quantityParticles != this._lastRenderedCount) {
            var infoLabel = this.getChildByTag(TAG_INFO_LAYER);
            var str = this._quantityParticles + " particles";
            infoLabel.setString(str);

            this._lastRenderedCount = this._quantityParticles;
        }
    },
    getSubTestNum:function () {
        return this._subtestNumber;
    },
    getParticlesNum:function () {
        return this._quantityParticles;
    },
    doTest:function () {
    }
});

////////////////////////////////////////////////////////
//
// ParticlePerformTest1
//
////////////////////////////////////////////////////////
var ParticlePerformTest1 = ParticleMainScene.extend({

    title:function () {
        return "A " + this._subtestNumber + " size=4";
    },
    doTest:function () {
        var s = cc.Director.getInstance().getWinSize();
        var particleSystem = this.getChildByTag(TAG_PARTICLE_SYSTEM);

        // duration
        particleSystem.setDuration(-1);

        // gravity
        particleSystem.setGravity(cc.p(0, -90));

        // angle
        particleSystem.setAngle(90);
        particleSystem.setAngleVar(0);

        // radial
        particleSystem.setRadialAccel(0);
        particleSystem.setRadialAccelVar(0);

        // speed of particles
        particleSystem.setSpeed(180);
        particleSystem.setSpeedVar(50);

        // emitter position
        particleSystem.setPosition(cc.p(s.width / 2, 100));
        particleSystem.setPosVar(cc.p(s.width / 2, 0));

        // life of particles
        particleSystem.setLife(2.0);
        particleSystem.setLifeVar(1);

        // emits per frame
        particleSystem.setEmissionRate(particleSystem.getTotalParticles() / particleSystem.getLife());

        // color of particles
        var startColor = new cc.Color4F(0.5, 0.5, 0.5, 1.0);
        particleSystem.setStartColor(startColor);

        var startColorVar = new cc.Color4F(0.5, 0.5, 0.5, 1.0);
        particleSystem.setStartColorVar(startColorVar);

        var endColor = new cc.Color4F(0.1, 0.1, 0.1, 0.2);
        particleSystem.setEndColor(endColor);

        var endColorVar = new cc.Color4F(0.1, 0.1, 0.1, 0.2);
        particleSystem.setEndColorVar(endColorVar);

        // size, in pixels
        particleSystem.setEndSize(4.0);
        particleSystem.setStartSize(4.0);
        particleSystem.setEndSizeVar(0);
        particleSystem.setStartSizeVar(0);

        // additive
        particleSystem.setBlendAdditive(false);
    }
});

////////////////////////////////////////////////////////
//
// ParticlePerformTest2
//
////////////////////////////////////////////////////////
var ParticlePerformTest2 = ParticleMainScene.extend({

    title:function () {
        return "B " + this._subtestNumber + " size=8";
    },
    doTest:function () {
        var s = cc.Director.getInstance().getWinSize();
        var particleSystem = this.getChildByTag(TAG_PARTICLE_SYSTEM);

        // duration
        particleSystem.setDuration(-1);

        // gravity
        particleSystem.setGravity(cc.p(0, -90));

        // angle
        particleSystem.setAngle(90);
        particleSystem.setAngleVar(0);

        // radial
        particleSystem.setRadialAccel(0);
        particleSystem.setRadialAccelVar(0);

        // speed of particles
        particleSystem.setSpeed(180);
        particleSystem.setSpeedVar(50);

        // emitter position
        particleSystem.setPosition(cc.p(s.width / 2, 100));
        particleSystem.setPosVar(cc.p(s.width / 2, 0));

        // life of particles
        particleSystem.setLife(2.0);
        particleSystem.setLifeVar(1);

        // emits per frame
        particleSystem.setEmissionRate(particleSystem.getTotalParticles() / particleSystem.getLife());

        // color of particles
        var startColor = new cc.Color4F(0.5, 0.5, 0.5, 1.0);
        particleSystem.setStartColor(startColor);

        var startColorVar = new cc.Color4F(0.5, 0.5, 0.5, 1.0);
        particleSystem.setStartColorVar(startColorVar);

        var endColor = new cc.Color4F(0.1, 0.1, 0.1, 0.2);
        particleSystem.setEndColor(endColor);

        var endColorVar = new cc.Color4F(0.1, 0.1, 0.1, 0.2);
        particleSystem.setEndColorVar(endColorVar);

        // size, in pixels
        particleSystem.setEndSize(8.0);
        particleSystem.setStartSize(8.0);
        particleSystem.setEndSizeVar(0);
        particleSystem.setStartSizeVar(0);

        // additive
        particleSystem.setBlendAdditive(false);
    }
});

////////////////////////////////////////////////////////
//
// ParticlePerformTest3
//
////////////////////////////////////////////////////////
var ParticlePerformTest3 = ParticleMainScene.extend({

    title:function () {
        return "C " + this._subtestNumber + " size=32";
    },
    doTest:function () {
        var s = cc.Director.getInstance().getWinSize();
        var particleSystem = this.getChildByTag(TAG_PARTICLE_SYSTEM);

        // duration
        particleSystem.setDuration(-1);

        // gravity
        particleSystem.setGravity(cc.p(0, -90));

        // angle
        particleSystem.setAngle(90);
        particleSystem.setAngleVar(0);

        // radial
        particleSystem.setRadialAccel(0);
        particleSystem.setRadialAccelVar(0);

        // speed of particles
        particleSystem.setSpeed(180);
        particleSystem.setSpeedVar(50);

        // emitter position
        particleSystem.setPosition(cc.p(s.width / 2, 100));
        particleSystem.setPosVar(cc.p(s.width / 2, 0));

        // life of particles
        particleSystem.setLife(2.0);
        particleSystem.setLifeVar(1);

        // emits per frame
        particleSystem.setEmissionRate(particleSystem.getTotalParticles() / particleSystem.getLife());

        // color of particles
        var startColor = new cc.Color4F(0.5, 0.5, 0.5, 1.0);
        particleSystem.setStartColor(startColor);

        var startColorVar = new cc.Color4F(0.5, 0.5, 0.5, 1.0);
        particleSystem.setStartColorVar(startColorVar);

        var endColor = new cc.Color4F(0.1, 0.1, 0.1, 0.2);
        particleSystem.setEndColor(endColor);

        var endColorVar = new cc.Color4F(0.1, 0.1, 0.1, 0.2);
        particleSystem.setEndColorVar(endColorVar);

        // size, in pixels
        particleSystem.setEndSize(32.0);
        particleSystem.setStartSize(32.0);
        particleSystem.setEndSizeVar(0);
        particleSystem.setStartSizeVar(0);

        // additive
        particleSystem.setBlendAdditive(false);
    }
});

////////////////////////////////////////////////////////
//
// ParticlePerformTest4
//
////////////////////////////////////////////////////////
var ParticlePerformTest4 = ParticleMainScene.extend({

    title:function () {
        return "D " + this._subtestNumber + " size=64";
    },
    doTest:function () {
        var s = cc.Director.getInstance().getWinSize();
        var particleSystem = this.getChildByTag(TAG_PARTICLE_SYSTEM);

        // duration
        particleSystem.setDuration(-1);

        // gravity
        particleSystem.setGravity(cc.p(0, -90));

        // angle
        particleSystem.setAngle(90);
        particleSystem.setAngleVar(0);

        // radial
        particleSystem.setRadialAccel(0);
        particleSystem.setRadialAccelVar(0);

        // speed of particles
        particleSystem.setSpeed(180);
        particleSystem.setSpeedVar(50);

        // emitter position
        particleSystem.setPosition(cc.p(s.width / 2, 100));
        particleSystem.setPosVar(cc.p(s.width / 2, 0));

        // life of particles
        particleSystem.setLife(2.0);
        particleSystem.setLifeVar(1);

        // emits per frame
        particleSystem.setEmissionRate(particleSystem.getTotalParticles() / particleSystem.getLife());

        // color of particles
        var startColor = new cc.Color4F(0.5, 0.5, 0.5, 1.0);
        particleSystem.setStartColor(startColor);

        var startColorVar = new cc.Color4F(0.5, 0.5, 0.5, 1.0);
        particleSystem.setStartColorVar(startColorVar);

        var endColor = new cc.Color4F(0.1, 0.1, 0.1, 0.2);
        particleSystem.setEndColor(endColor);

        var endColorVar = new cc.Color4F(0.1, 0.1, 0.1, 0.2);
        particleSystem.setEndColorVar(endColorVar);

        // size, in pixels
        particleSystem.setEndSize(64.0);
        particleSystem.setStartSize(64.0);
        particleSystem.setEndSizeVar(0);
        particleSystem.setStartSizeVar(0);

        // additive
        particleSystem.setBlendAdditive(false);
    }
});

function runParticleTest() {
    var scene = new ParticlePerformTest1;
    scene.initWithSubTest(1, PARTICLE_NODES_INCREASE);
    cc.Director.getInstance().replaceScene(scene);
}
