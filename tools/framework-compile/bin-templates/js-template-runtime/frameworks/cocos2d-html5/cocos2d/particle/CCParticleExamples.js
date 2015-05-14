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

/**
 * A fire particle system
 * @class
 * @extends cc.ParticleSystem
 *
 * @example
 * var emitter = new cc.ParticleFire();
 */
cc.ParticleFire = cc.ParticleSystem.extend(/** @lends cc.ParticleFire# */{
    /**
     * <p>The cc.ParticleFire's constructor. <br/>
     * This function will automatically be invoked when you create a node using new construction: "var node = new cc.ParticleFire()".<br/>
     * Override it to extend its behavior, remember to call "this._super()" in the extended "ctor" function.</p>
     */
    ctor:function () {
        cc.ParticleSystem.prototype.ctor.call(this, (cc._renderType === cc._RENDER_TYPE_WEBGL) ? 300 : 150);
    },

    /**
     * initialize a fire particle system with number Of Particles
     * @param {Number} numberOfParticles
     * @return {Boolean}
     */
    initWithTotalParticles:function (numberOfParticles) {
        if (cc.ParticleSystem.prototype.initWithTotalParticles.call(this, numberOfParticles)) {
            // duration
            this.setDuration(cc.ParticleSystem.DURATION_INFINITY);

            // Gravity Mode
            this.setEmitterMode(cc.ParticleSystem.MODE_GRAVITY);


            // Gravity Mode: gravity
            this.setGravity(cc.p(0, 0));

            // Gravity Mode: radial acceleration
            this.setRadialAccel(0);
            this.setRadialAccelVar(0);

            // Gravity Mode: speed of particles
            this.setSpeed(60);
            this.setSpeedVar(20);

            // starting angle
            this.setAngle(90);
            this.setAngleVar(10);

            // emitter position
            var winSize = cc.director.getWinSize();
            this.setPosition(winSize.width / 2, 60);
            this.setPosVar(cc.p(40, 20));

            // life of particles
            this.setLife(3);
            this.setLifeVar(0.25);


            // size, in pixels
            this.setStartSize(54.0);
            this.setStartSizeVar(10.0);
            this.setEndSize(cc.ParticleSystem.START_SIZE_EQUAL_TO_END_SIZE);

            // emits per frame
            this.setEmissionRate(this.getTotalParticles() / this.getLife());

            // color of particles
            this.setStartColor(cc.color(194,64,31,255));
            this.setStartColorVar(cc.color(0,0,0,0));
            this.setEndColor(cc.color(0,0,0,255));
            this.setEndColorVar(cc.color(0,0,0,0));

            // additive
            this.setBlendAdditive(true);
            return true;
        }
        return false;
    }
});

/**
 * Create a fire particle system
 * @deprecated since v3.0 please use new cc.ParticleFire() instead
 * @return {cc.ParticleFire}
 */
cc.ParticleFire.create = function () {
    return new cc.ParticleFire();
};

/**
 * A fireworks particle system
 * @class
 * @extends cc.ParticleSystem
 *
 * @example
 * var emitter = new cc.ParticleFireworks();
 */
cc.ParticleFireworks = cc.ParticleSystem.extend(/** @lends cc.ParticleFireworks# */{
    /**
     * <p>The cc.ParticleFireworks's constructor. <br/>
     * This function will automatically be invoked when you create a node using new construction: "var node = new cc.ParticleFireworks()".<br/>
     * Override it to extend its behavior, remember to call "this._super()" in the extended "ctor" function.</p>
     */
    ctor:function () {
        cc.ParticleSystem.prototype.ctor.call(this, (cc._renderType === cc._RENDER_TYPE_WEBGL) ? 1500 : 150);
    },

    /**
     * initialize a fireworks particle system with number Of Particles
     * @param {Number} numberOfParticles
     * @return {Boolean}
     */
    initWithTotalParticles:function (numberOfParticles) {
        if (cc.ParticleSystem.prototype.initWithTotalParticles.call(this, numberOfParticles)) {
            // duration
            this.setDuration(cc.ParticleSystem.DURATION_INFINITY);

            // Gravity Mode
            this.setEmitterMode(cc.ParticleSystem.MODE_GRAVITY);

            // Gravity Mode: gravity
            this.setGravity(cc.p(0, -90));

            // Gravity Mode:  radial
            this.setRadialAccel(0);
            this.setRadialAccelVar(0);

            //  Gravity Mode: speed of particles
            this.setSpeed(180);
            this.setSpeedVar(50);

            // emitter position
            var winSize = cc.director.getWinSize();
            this.setPosition(winSize.width / 2, winSize.height / 2);

            // angle
            this.setAngle(90);
            this.setAngleVar(20);

            // life of particles
            this.setLife(3.5);
            this.setLifeVar(1);

            // emits per frame
            this.setEmissionRate(this.getTotalParticles() / this.getLife());

            // color of particles
            this.setStartColor(cc.color(128,128,128,255));
            this.setStartColorVar(cc.color(128,128,128,255));
            this.setEndColor(cc.color(26,26,26,51));
            this.setEndColorVar(cc.color(26,26,26,51));

            // size, in pixels
            this.setStartSize(8.0);
            this.setStartSizeVar(2.0);
            this.setEndSize(cc.ParticleSystem.START_SIZE_EQUAL_TO_END_SIZE);

            // additive
            this.setBlendAdditive(false);
            return true;
        }
        return false;
    }
});

/**
 * Create a fireworks particle system
 * @deprecated since v3.0 please use new cc.ParticleFireworks() instead.
 * @return {cc.ParticleFireworks}
 */
cc.ParticleFireworks.create = function () {
    return new cc.ParticleFireworks();
};

/**
 * A sun particle system
 * @class
 * @extends cc.ParticleSystem
 *
 * @example
 * var emitter = new cc.ParticleSun();
 */
cc.ParticleSun = cc.ParticleSystem.extend(/** @lends cc.ParticleSun# */{
    /**
     * <p>The cc.ParticleSun's constructor. <br/>
     * This function will automatically be invoked when you create a node using new construction: "var node = new cc.ParticleSun()".<br/>
     * Override it to extend its behavior, remember to call "this._super()" in the extended "ctor" function.</p>
     */
    ctor:function () {
        cc.ParticleSystem.prototype.ctor.call(this, (cc._renderType === cc._RENDER_TYPE_WEBGL) ? 350 : 150);
    },

    /**
     * initialize a sun particle system with number Of Particles
     * @param {Number} numberOfParticles
     * @return {Boolean}
     */
    initWithTotalParticles:function (numberOfParticles) {
        if (cc.ParticleSystem.prototype.initWithTotalParticles.call(this, numberOfParticles)) {
            // additive
            this.setBlendAdditive(true);

            // duration
            this.setDuration(cc.ParticleSystem.DURATION_INFINITY);

            // Gravity Mode
            this.setEmitterMode(cc.ParticleSystem.MODE_GRAVITY);

            // Gravity Mode: gravity
            this.setGravity(cc.p(0, 0));

            // Gravity mode: radial acceleration
            this.setRadialAccel(0);
            this.setRadialAccelVar(0);

            // Gravity mode: speed of particles
            this.setSpeed(20);
            this.setSpeedVar(5);

            // angle
            this.setAngle(90);
            this.setAngleVar(360);

            // emitter position
            var winSize = cc.director.getWinSize();
            this.setPosition(winSize.width / 2, winSize.height / 2);
            this.setPosVar(cc.p(0,0));

            // life of particles
            this.setLife(1);
            this.setLifeVar(0.5);

            // size, in pixels
            this.setStartSize(30.0);
            this.setStartSizeVar(10.0);
            this.setEndSize(cc.ParticleSystem.START_SIZE_EQUAL_TO_END_SIZE);

            // emits per seconds
            this.setEmissionRate(this.getTotalParticles() / this.getLife());

            // color of particles
            this.setStartColor(cc.color(194, 64, 31, 255));
            this.setStartColorVar(cc.color(0, 0, 0, 0));
            this.setEndColor(cc.color(0, 0, 0, 255));
            this.setEndColorVar(cc.color(0, 0, 0, 0));

            return true;
        }
        return false;
    }
});

/**
 * Create a sun particle system
 * @deprecated since v3.0 please use new cc.ParticleSun() instead.
 * @return {cc.ParticleSun}
 */
cc.ParticleSun.create = function () {
    return new cc.ParticleSun();
};

//! @brief A  particle system
/**
 * A galaxy particle system
 * @class
 * @extends cc.ParticleSystem
 *
 * @example
 * var emitter = new cc.ParticleGalaxy();
 */
cc.ParticleGalaxy = cc.ParticleSystem.extend(/** @lends cc.ParticleGalaxy# */{
    /**
     * <p>The cc.ParticleGalaxy's constructor. <br/>
     * This function will automatically be invoked when you create a node using new construction: "var node = new cc.ParticleGalaxy()".<br/>
     * Override it to extend its behavior, remember to call "this._super()" in the extended "ctor" function.</p>
     */
    ctor:function () {
        cc.ParticleSystem.prototype.ctor.call(this, (cc._renderType === cc._RENDER_TYPE_WEBGL) ? 200 : 100);
    },

    /**
     * initialize a galaxy particle system with number Of Particles
     * @param {Number} numberOfParticles
     * @return {Boolean}
     */
    initWithTotalParticles:function (numberOfParticles) {
        if (cc.ParticleSystem.prototype.initWithTotalParticles.call(this, numberOfParticles)) {
            // duration
            this.setDuration(cc.ParticleSystem.DURATION_INFINITY);

            // Gravity Mode
            this.setEmitterMode(cc.ParticleSystem.MODE_GRAVITY);

            // Gravity Mode: gravity
            this.setGravity(cc.p(0, 0));

            // Gravity Mode: speed of particles
            this.setSpeed(60);
            this.setSpeedVar(10);

            // Gravity Mode: radial
            this.setRadialAccel(-80);
            this.setRadialAccelVar(0);

            // Gravity Mode: tangential
            this.setTangentialAccel(80);
            this.setTangentialAccelVar(0);

            // angle
            this.setAngle(90);
            this.setAngleVar(360);

            // emitter position
            var winSize = cc.director.getWinSize();
            this.setPosition(winSize.width / 2, winSize.height / 2);
            this.setPosVar(cc.p(0,0));

            // life of particles
            this.setLife(4);
            this.setLifeVar(1);

            // size, in pixels
            this.setStartSize(37.0);
            this.setStartSizeVar(10.0);
            this.setEndSize(cc.ParticleSystem.START_SIZE_EQUAL_TO_END_SIZE);

            // emits per second
            this.setEmissionRate(this.getTotalParticles() / this.getLife());

            // color of particles
            this.setStartColor(cc.color(31, 64, 194, 255));
            this.setStartColorVar(cc.color(0, 0, 0, 0));
            this.setEndColor(cc.color(0, 0, 0, 255));
            this.setEndColorVar(cc.color(0, 0, 0, 0));

            // additive
            this.setBlendAdditive(true);
            return true;
        }
        return false;
    }
});
/**
 * Create a galaxy particle system
 * @deprecated since v3.0 please use new cc.OarticleGalaxy() instead.
 * @return {cc.ParticleGalaxy}
 */
cc.ParticleGalaxy.create = function () {
    return new cc.ParticleGalaxy();
};

/**
 * A flower particle system
 * @class
 * @extends cc.ParticleSystem
 *
 * @example
 * var emitter = new cc.ParticleFlower();
 */
cc.ParticleFlower = cc.ParticleSystem.extend(/** @lends cc.ParticleFlower# */{
    /**
     * <p>The cc.ParticleFlower's constructor. <br/>
     * This function will automatically be invoked when you create a node using new construction: "var node = new cc.ParticleFlower()".<br/>
     * Override it to extend its behavior, remember to call "this._super()" in the extended "ctor" function.</p>
     */
    ctor : function () {
        cc.ParticleSystem.prototype.ctor.call(this, (cc._renderType === cc._RENDER_TYPE_WEBGL) ? 250 : 100);
    },

    /**
     * initialize a flower particle system with number Of Particles
     * @param {Number} numberOfParticles
     * @return {Boolean}
     */
    initWithTotalParticles:function (numberOfParticles) {
        if (cc.ParticleSystem.prototype.initWithTotalParticles.call(this, numberOfParticles)) {
            // duration
            this.setDuration(cc.ParticleSystem.DURATION_INFINITY);

            // Gravity Mode
            this.setEmitterMode(cc.ParticleSystem.MODE_GRAVITY);

            // Gravity Mode: gravity
            this.setGravity(cc.p(0, 0));

            // Gravity Mode: speed of particles
            this.setSpeed(80);
            this.setSpeedVar(10);

            // Gravity Mode: radial
            this.setRadialAccel(-60);
            this.setRadialAccelVar(0);

            // Gravity Mode: tangential
            this.setTangentialAccel(15);
            this.setTangentialAccelVar(0);

            // angle
            this.setAngle(90);
            this.setAngleVar(360);

            // emitter position
            var winSize = cc.director.getWinSize();
            this.setPosition(winSize.width / 2, winSize.height / 2);
            this.setPosVar(cc.p(0,0));

            // life of particles
            this.setLife(4);
            this.setLifeVar(1);

            // size, in pixels
            this.setStartSize(30.0);
            this.setStartSizeVar(10.0);
            this.setEndSize(cc.ParticleSystem.START_SIZE_EQUAL_TO_END_SIZE);

            // emits per second
            this.setEmissionRate(this.getTotalParticles() / this.getLife());

            // color of particles
            this.setStartColor(cc.color(128, 128, 128, 255));
            this.setStartColorVar(cc.color(128, 128, 128, 128));
            this.setEndColor(cc.color(0, 0, 0, 255));
            this.setEndColorVar(cc.color(0, 0, 0, 0));

            // additive
            this.setBlendAdditive(true);
            return true;
        }
        return false;
    }
});

/**
 * Create a flower particle system
 * @deprecated since v3.0 please use new cc.ParticleFlower() instead.
 * @return {cc.ParticleFlower}
 */
cc.ParticleFlower.create = function () {
    return new cc.ParticleFlower();
};

//! @brief A meteor particle system
/**
 * A meteor particle system
 * @class
 * @extends cc.ParticleSystem
 *
 * @example
 * var emitter = new cc.ParticleMeteor();
 */
cc.ParticleMeteor = cc.ParticleSystem.extend(/** @lends cc.ParticleMeteor# */{
    /**
     * <p>The cc.ParticleMeteor's constructor. <br/>
     * This function will automatically be invoked when you create a node using new construction: "var node = new cc.ParticleMeteor()".<br/>
     * Override it to extend its behavior, remember to call "this._super()" in the extended "ctor" function.</p>
     */
    ctor:function () {
        cc.ParticleSystem.prototype.ctor.call(this, (cc._renderType === cc._RENDER_TYPE_WEBGL) ? 150 : 100);
    },

    /**
     * initialize a meteor particle system with number Of Particles
     * @param {Number} numberOfParticles
     * @return {Boolean}
     */
    initWithTotalParticles:function (numberOfParticles) {
        if (cc.ParticleSystem.prototype.initWithTotalParticles.call(this, numberOfParticles)) {
            // duration
            this.setDuration(cc.ParticleSystem.DURATION_INFINITY);

            // Gravity Mode
            this.setEmitterMode(cc.ParticleSystem.MODE_GRAVITY);

            // Gravity Mode: gravity
            this.setGravity(cc.p(-200, 200));

            // Gravity Mode: speed of particles
            this.setSpeed(15);
            this.setSpeedVar(5);

            // Gravity Mode: radial
            this.setRadialAccel(0);
            this.setRadialAccelVar(0);

            // Gravity Mode: tangential
            this.setTangentialAccel(0);
            this.setTangentialAccelVar(0);

            // angle
            this.setAngle(90);
            this.setAngleVar(360);

            // emitter position
            var winSize = cc.director.getWinSize();
            this.setPosition(winSize.width / 2, winSize.height / 2);
            this.setPosVar(cc.p(0,0));

            // life of particles
            this.setLife(2);
            this.setLifeVar(1);

            // size, in pixels
            this.setStartSize(60.0);
            this.setStartSizeVar(10.0);
            this.setEndSize(cc.ParticleSystem.START_SIZE_EQUAL_TO_END_SIZE);

            // emits per second
            this.setEmissionRate(this.getTotalParticles() / this.getLife());

            // color of particles
            this.setStartColor(cc.color(51, 102, 179));
            this.setStartColorVar(cc.color(0, 0, 51, 26));
            this.setEndColor(cc.color(0, 0, 0, 255));
            this.setEndColorVar(cc.color(0, 0, 0, 0));

            // additive
            this.setBlendAdditive(true);
            return true;
        }
        return false;
    }
});

/**
 * Create a meteor particle system
 * @deprecated since v3.0 please use new cc.ParticleMeteor() instead.
 * @return {cc.ParticleMeteor}
 */
cc.ParticleMeteor.create = function () {
    return new cc.ParticleMeteor();
};

/**
 * A spiral particle system
 * @class
 * @extends cc.ParticleSystem
 *
 * @example
 * var emitter = new cc.ParticleSpiral();
 */
cc.ParticleSpiral = cc.ParticleSystem.extend(/** @lends cc.ParticleSpiral# */{

    /**
     * <p>The cc.ParticleSpiral's constructor. <br/>
     * This function will automatically be invoked when you create a node using new construction: "var node = new cc.ParticleSpiral()".<br/>
     * Override it to extend its behavior, remember to call "this._super()" in the extended "ctor" function.</p>
     */
    ctor:function() {
        cc.ParticleSystem.prototype.ctor.call(this,(cc._renderType === cc._RENDER_TYPE_WEBGL) ? 500 : 100);
    },

    /**
     * initialize a spiral particle system with number Of Particles
     * @param {Number} numberOfParticles
     * @return {Boolean}
     */
    initWithTotalParticles:function (numberOfParticles) {
        if (cc.ParticleSystem.prototype.initWithTotalParticles.call(this, numberOfParticles)) {
            // duration
            this.setDuration(cc.ParticleSystem.DURATION_INFINITY);

            // Gravity Mode
            this.setEmitterMode(cc.ParticleSystem.MODE_GRAVITY);

            // Gravity Mode: gravity
            this.setGravity(cc.p(0, 0));

            // Gravity Mode: speed of particles
            this.setSpeed(150);
            this.setSpeedVar(0);

            // Gravity Mode: radial
            this.setRadialAccel(-380);
            this.setRadialAccelVar(0);

            // Gravity Mode: tangential
            this.setTangentialAccel(45);
            this.setTangentialAccelVar(0);

            // angle
            this.setAngle(90);
            this.setAngleVar(0);

            // emitter position
            var winSize = cc.director.getWinSize();
            this.setPosition(winSize.width / 2, winSize.height / 2);
            this.setPosVar(cc.p(0,0));

            // life of particles
            this.setLife(12);
            this.setLifeVar(0);

            // size, in pixels
            this.setStartSize(20.0);
            this.setStartSizeVar(0.0);
            this.setEndSize(cc.ParticleSystem.START_SIZE_EQUAL_TO_END_SIZE);

            // emits per second
            this.setEmissionRate(this.getTotalParticles() / this.getLife());

            // color of particles
            this.setStartColor(cc.color(128,128,128,255));
            this.setStartColorVar(cc.color(128,128,128,0));
            this.setEndColor(cc.color(128,128,128,255));
            this.setEndColorVar(cc.color(128,128,128,0));

            // additive
            this.setBlendAdditive(false);
            return true;
        }
        return false;
    }
});

/**
 * Create a spiral particle system
 * @deprecated since v3.0 please use new cc.ParticleSpiral() instead.
 * @return {cc.ParticleSpiral}
 */
cc.ParticleSpiral.create = function () {
    return new cc.ParticleSpiral();
};

/**
 * An explosion particle system
 * @class
 * @extends cc.ParticleSystem
 *
 * @example
 * var emitter = new cc.ParticleExplosion();
 */
cc.ParticleExplosion = cc.ParticleSystem.extend(/** @lends cc.ParticleExplosion# */{
    /**
     * <p>The cc.ParticleExplosion's constructor. <br/>
     * This function will automatically be invoked when you create a node using new construction: "var node = new cc.ParticleExplosion()".<br/>
     * Override it to extend its behavior, remember to call "this._super()" in the extended "ctor" function.</p>
     */
    ctor:function () {
        cc.ParticleSystem.prototype.ctor.call(this, (cc._renderType === cc._RENDER_TYPE_WEBGL) ? 700 : 300);
    },

    /**
     * initialize an explosion particle system with number Of Particles
     * @param {Number} numberOfParticles
     * @return {Boolean}
     */
    initWithTotalParticles:function (numberOfParticles) {
        if (cc.ParticleSystem.prototype.initWithTotalParticles.call(this, numberOfParticles)) {
            // duration
            this.setDuration(0.1);

            this.setEmitterMode(cc.ParticleSystem.MODE_GRAVITY);

            // Gravity Mode: gravity
            this.setGravity(cc.p(0, 0));

            // Gravity Mode: speed of particles
            this.setSpeed(70);
            this.setSpeedVar(40);

            // Gravity Mode: radial
            this.setRadialAccel(0);
            this.setRadialAccelVar(0);

            // Gravity Mode: tangential
            this.setTangentialAccel(0);
            this.setTangentialAccelVar(0);

            // angle
            this.setAngle(90);
            this.setAngleVar(360);

            // emitter position
            var winSize = cc.director.getWinSize();
            this.setPosition(winSize.width / 2, winSize.height / 2);
            this.setPosVar(cc.p(0,0));

            // life of particles
            this.setLife(5.0);
            this.setLifeVar(2);

            // size, in pixels
            this.setStartSize(15.0);
            this.setStartSizeVar(10.0);
            this.setEndSize(cc.ParticleSystem.START_SIZE_EQUAL_TO_END_SIZE);

            // emits per second
            this.setEmissionRate(this.getTotalParticles() / this.getDuration());

            // color of particles
            this.setStartColor(cc.color(179, 26, 51, 255));
            this.setStartColorVar(cc.color(128, 128, 128, 0));
            this.setEndColor(cc.color(128, 128, 128, 0));
            this.setEndColorVar(cc.color(128, 128, 128, 0));

            // additive
            this.setBlendAdditive(false);
            return true;
        }
        return false;
    }
});

/**
 * Create an explosion particle system
 * @deprecated since v3.0 please use new cc.ParticleExplosion() instead.
 * @return {cc.ParticleExplosion}
 */
cc.ParticleExplosion.create = function () {
    return new cc.ParticleExplosion();
};

/**
 * A smoke particle system
 * @class
 * @extends cc.ParticleSystem
 *
 * @example
 * var emitter = new cc.ParticleSmoke();
 */
cc.ParticleSmoke = cc.ParticleSystem.extend(/** @lends cc.ParticleSmoke# */{

    /**
     * <p>The cc.ParticleSmoke's constructor. <br/>
     * This function will automatically be invoked when you create a node using new construction: "var node = new cc.ParticleSmoke()".<br/>
     * Override it to extend its behavior, remember to call "this._super()" in the extended "ctor" function.</p>
     */
    ctor:function () {
        cc.ParticleSystem.prototype.ctor.call(this, (cc._renderType === cc._RENDER_TYPE_WEBGL) ? 200 : 100);
    },

    /**
     * initialize a smoke particle system with number Of Particles
     * @param {Number} numberOfParticles
     * @return {Boolean}
     */
    initWithTotalParticles:function (numberOfParticles) {
        if (cc.ParticleSystem.prototype.initWithTotalParticles.call(this, numberOfParticles)) {
            // duration
            this.setDuration(cc.ParticleSystem.DURATION_INFINITY);

            // Emitter mode: Gravity Mode
            this.setEmitterMode(cc.ParticleSystem.MODE_GRAVITY);

            // Gravity Mode: gravity
            this.setGravity(cc.p(0, 0));

            // Gravity Mode: radial acceleration
            this.setRadialAccel(0);
            this.setRadialAccelVar(0);

            // Gravity Mode: speed of particles
            this.setSpeed(25);
            this.setSpeedVar(10);

            // angle
            this.setAngle(90);
            this.setAngleVar(5);

            // emitter position
            var winSize = cc.director.getWinSize();
            this.setPosition(winSize.width / 2, 0);
            this.setPosVar(cc.p(20, 0));

            // life of particles
            this.setLife(4);
            this.setLifeVar(1);

            // size, in pixels
            this.setStartSize(60.0);
            this.setStartSizeVar(10.0);
            this.setEndSize(cc.ParticleSystem.START_SIZE_EQUAL_TO_END_SIZE);

            // emits per frame
            this.setEmissionRate(this.getTotalParticles() / this.getLife());

            // color of particles
            this.setStartColor(cc.color(204, 204, 204, 255));
            this.setStartColorVar(cc.color(5, 5, 5, 0));
            this.setEndColor(cc.color(0, 0, 0, 255));
            this.setEndColorVar(cc.color(0, 0, 0, 0));

            // additive
            this.setBlendAdditive(false);
            return true;
        }
        return false;
    }
});

/**
 * Create a smoke particle system
 * @deprecated since v3.0 please use new cc.ParticleSmoke() instead.
 * @return {cc.ParticleSmoke}
 */
cc.ParticleSmoke.create = function () {
    return new cc.ParticleSmoke();
};

/**
 * A snow particle system
 * @class
 * @extends cc.ParticleSystem
 *
 * @example
 * var emitter = new cc.ParticleSnow();
 */
cc.ParticleSnow = cc.ParticleSystem.extend(/** @lends cc.ParticleSnow# */{

    /**
     * <p>The cc.ParticleSnow's constructor. <br/>
     * This function will automatically be invoked when you create a node using new construction: "var node = new cc.ParticleSnow()".<br/>
     * Override it to extend its behavior, remember to call "this._super()" in the extended "ctor" function.</p>
     */
    ctor:function () {
        cc.ParticleSystem.prototype.ctor.call(this, (cc._renderType === cc._RENDER_TYPE_WEBGL) ? 700 : 250);
    },

    /**
     * initialize a snow particle system with number Of Particles
     * @param {Number} numberOfParticles
     * @return {Boolean}
     */
    initWithTotalParticles:function (numberOfParticles) {
        if (cc.ParticleSystem.prototype.initWithTotalParticles.call(this, numberOfParticles)) {
            // duration
            this.setDuration(cc.ParticleSystem.DURATION_INFINITY);

            // set gravity mode.
            this.setEmitterMode(cc.ParticleSystem.MODE_GRAVITY);

            // Gravity Mode: gravity
            this.setGravity(cc.p(0, -1));

            // Gravity Mode: speed of particles
            this.setSpeed(5);
            this.setSpeedVar(1);

            // Gravity Mode: radial
            this.setRadialAccel(0);
            this.setRadialAccelVar(1);

            // Gravity mode: tangential
            this.setTangentialAccel(0);
            this.setTangentialAccelVar(1);

            // emitter position
            var winSize = cc.director.getWinSize();
            this.setPosition(winSize.width / 2, winSize.height + 10);
            this.setPosVar(cc.p(winSize.width / 2, 0));

            // angle
            this.setAngle(-90);
            this.setAngleVar(5);

            // life of particles
            this.setLife(45);
            this.setLifeVar(15);

            // size, in pixels
            this.setStartSize(10.0);
            this.setStartSizeVar(5.0);
            this.setEndSize(cc.ParticleSystem.START_SIZE_EQUAL_TO_END_SIZE);

            // emits per second
            this.setEmissionRate(10);

            // color of particles
            this.setStartColor(cc.color(255, 255, 255, 255));
            this.setStartColorVar(cc.color(0, 0, 0, 0));
            this.setEndColor(cc.color(255, 255, 255, 0));
            this.setEndColorVar(cc.color(0, 0, 0, 0));

            // additive
            this.setBlendAdditive(false);
            return true;
        }
        return false;
    }
});

/**
 * Create a snow particle system
 * @deprecated since v3.0 please use new cc.ParticleSnow() instead.
 * @return {cc.ParticleSnow}
 */
cc.ParticleSnow.create = function () {
    return new cc.ParticleSnow();
};

//! @brief A rain particle system
/**
 * A rain particle system
 * @class
 * @extends cc.ParticleSystem
 *
 * @example
 * var emitter = new cc.ParticleRain();
 */
cc.ParticleRain = cc.ParticleSystem.extend(/** @lends cc.ParticleRain# */{

    /**
     * <p>The cc.ParticleRain's constructor. <br/>
     * This function will automatically be invoked when you create a node using new construction: "var node = new cc.ParticleRain()".<br/>
     * Override it to extend its behavior, remember to call "this._super()" in the extended "ctor" function.</p>
     */
    ctor:function () {
        cc.ParticleSystem.prototype.ctor.call(this, (cc._renderType === cc._RENDER_TYPE_WEBGL) ? 1000 : 300);
    },

    /**
     * initialize a rain particle system with number Of Particles
     * @param {Number} numberOfParticles
     * @return {Boolean}
     */
    initWithTotalParticles:function (numberOfParticles) {
        if (cc.ParticleSystem.prototype.initWithTotalParticles.call(this, numberOfParticles)) {
            // duration
            this.setDuration(cc.ParticleSystem.DURATION_INFINITY);

            this.setEmitterMode(cc.ParticleSystem.MODE_GRAVITY);

            // Gravity Mode: gravity
            this.setGravity(cc.p(10, -10));

            // Gravity Mode: radial
            this.setRadialAccel(0);
            this.setRadialAccelVar(1);

            // Gravity Mode: tangential
            this.setTangentialAccel(0);
            this.setTangentialAccelVar(1);

            // Gravity Mode: speed of particles
            this.setSpeed(130);
            this.setSpeedVar(30);

            // angle
            this.setAngle(-90);
            this.setAngleVar(5);


            // emitter position
            var winSize = cc.director.getWinSize();
            this.setPosition(winSize.width / 2, winSize.height);
            this.setPosVar(cc.p(winSize.width / 2, 0));

            // life of particles
            this.setLife(4.5);
            this.setLifeVar(0);

            // size, in pixels
            this.setStartSize(4.0);
            this.setStartSizeVar(2.0);
            this.setEndSize(cc.ParticleSystem.START_SIZE_EQUAL_TO_END_SIZE);

            // emits per second
            this.setEmissionRate(20);

            // color of particles
            this.setStartColor(cc.color(179, 204, 255, 255));
            this.setStartColorVar(cc.color(0, 0, 0, 0));
            this.setEndColor(cc.color(179, 204, 255, 128));
            this.setEndColorVar(cc.color(0, 0, 0, 0));

            // additive
            this.setBlendAdditive(false);
            return true;
        }
        return false;
    }
});

/**
 * Create a rain particle system
 * @deprecated since v3.0 please use cc.ParticleRain() instead.
 * @return {cc.ParticleRain}
 */
cc.ParticleRain.create = function () {
    return new cc.ParticleRain();
};
