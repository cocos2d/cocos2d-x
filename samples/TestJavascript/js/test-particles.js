//
// http://www.cocos2d-iphone.org
// http://www.cocos2d-html5.org
// http://www.cocos2d-x.org
//
// Javascript + cocos2d particles tests
//

require("js/helper.js");

director = cc.Director.getInstance();
winSize = director.getWinSize();
centerPos = cc.p( winSize.width/2, winSize.height/2 );

var scenes = []
var currentScene = 0;

var nextScene = function () {
	currentScene = currentScene + 1;
	if( currentScene >= scenes.length )
		currentScene = 0;

	withTransition = true;
	loadScene(currentScene);
};

var previousScene = function () {
	currentScene = currentScene -1;
	if( currentScene < 0 )
		currentScene = scenes.length -1;

	withTransition = true;
	loadScene(currentScene);
};

var restartScene = function () {
	loadScene( currentScene );
};

var loadScene = function (sceneIdx)
{
	winSize = director.getWinSize();
	centerPos = cc.p( winSize.width/2, winSize.height/2 );

	var scene = cc.Scene.create();
	var layer = new scenes[ sceneIdx ]();

	scene.addChild( layer );

//	scene.walkSceneGraph(0);

	director.replaceScene( scene );
//    __jsc__.garbageCollect();
}



//
// Globals
//
var TAG_LABEL_ATLAS = 100;

var s_stars1 = 'stars.png';
var s_stars2 = 'stars2.png';
var s_starsGrayscale = 'stars-grayscale.png';
var s_fire = 'fire.png';
var s_smoke = 'smoke.png';
var s_snow = 'snow.png';

//
// Base Layer
//

var BaseLayer = cc.LayerGradient.extend({
    _emitter:null,
    _background:null,
    _shapeModeButton:null,
    _textureModeButton:null,

    ctor:function () {
        var parent = new cc.LayerGradient();
        __associateObjWithNative(this, parent);
        this.init(cc.c4b(0, 0, 0, 255), cc.c4b(0, 128, 255, 255));

        this._emitter = null;

        
        var platform = __getPlatform();
        if( platform.substring(0,7) == 'desktop' )
            this.setMouseEnabled( true );
        else if( platform.substring(0,6) == 'mobile' )
            this.setTouchEnabled( true );

        var label = cc.LabelTTF.create(this.title(), "Arial", 28);
        this.addChild(label, 100, 1000);
        label.setPosition(cc.p(winSize.width / 2, winSize.height - 50));

        var tapScreen = cc.LabelTTF.create("(Tap the Screen)", "Arial", 20);
        tapScreen.setPosition( cc.p(winSize.width / 2, winSize.height - 80));
        this.addChild(tapScreen, 100);
        var selfPoint = this;


        var itemFree = cc.MenuItemFont.create("Free movement");
        var itemRel = cc.MenuItemFont.create("Relative movement");
        var itemGroup = cc.MenuItemFont.create("Group movement");
        var toggle = cc.MenuItemToggle.create( itemFree, itemRel, itemGroup );
        toggle.setCallback( this, this.toggleCB );

        var menu = cc.Menu.create( toggle );
        menu.alignItemsVertically();
        menu.setPosition( cc.p( 100, 100 ) );
        this.addChild(menu, 1);

        // Menu
        var item1 = cc.MenuItemImage.create("b1.png", "b2.png", this, this.backCallback);
        var item2 = cc.MenuItemImage.create("r1.png", "r2.png", this, this.restartCallback);
        var item3 = cc.MenuItemImage.create("f1.png", "f2.png", this, this.nextCallback);
        var item4 = cc.MenuItemFont.create("back", this, function() { require("js/main.js"); } );
        item4.setFontSize( 22 );

        var menu = cc.Menu.create(item1, item2, item3, item4 );

        menu.setPosition( cc.p(0,0) );
        item1.setPosition( cc.p(winSize.width / 2 - 100, 30));
        item2.setPosition( cc.p(winSize.width / 2, 30));
        item3.setPosition( cc.p(winSize.width / 2 + 100, 30));
        item4.setPosition( cc.p(winSize.width - 60, winSize.height - 30 ) );

        this.addChild(menu, 1);


        //TODO
        var labelAtlas = cc.LabelAtlas.create("0000", "fps_images.plist");
        this.addChild(labelAtlas, 100, TAG_LABEL_ATLAS);
        labelAtlas.setPosition( cc.p( winSize.width - 66, 50));

        // moving background
        this._background = cc.Sprite.create("background3.png");
        this.addChild(this._background, 5);
        this._background.setPosition(cc.p(winSize.width / 2, winSize.height - 180));

        var move = cc.MoveBy.create(4, cc.p(300, 0));
        var move_back = move.reverse();
        var seq = cc.Sequence.create(move, move_back);
        this._background.runAction(cc.RepeatForever.create(seq));

        this.scheduleUpdate();
    },

    toggleCB:function(sender) {
        var type = this._emitter.getPositionType();
        if( type == cc.PARTICLE_TYPE_GROUPED )
            this._emitter.setPositionType( cc.PARTICLE_TYPE_FREE );
        else if( type == cc.PARTICLE_TYPE_FREE )
            this._emitter.setPositionType( cc.PARTICLE_TYPE_RELATIVE );
        else if( type == cc.PARTICLE_TYPE_RELATIVE )
            this._emitter.setPositionType( cc.PARTICLE_TYPE_GROUPED );
    },

    onEnter:function () {
        // don't call super_.this()
        var pLabel = this.getChildByTag(1000);
        pLabel.setString(this.title());
    },
    title:function () {
        return "No title";
    },

    restartCallback:function (sender) {
        restartScene();
    },

    nextCallback:function (sender) {
        nextScene();
    },

    backCallback:function (sender) {
       previousScene();
    },

    toggleCallback:function (sender) {
        if (this._emitter.getPositionType() == cc.PARTICLE_TYPE_GROUPED )
            this._emitter.setPositionType( cc.PARTICLE_TYPE_FREE );
        else if (this._emitter.getPositionType() == cc.PARTICLE_TYPE_FREE )
            this._emitter.setPositionType( cc.PARTICLE_TYPE_RELATIVE );
        else if (this._emitter.getPositionType() ==  cc.PARTICLE_TYPE_RELATIVE )
            this._emitter.setPositionType( cc.PARTICLE_TYPE_GROUPED );
    },

    onTouchesBegan:function (touches, event) {
        return this.onTouchesEnded( touches, event );
    },

    onTouchesMoved:function (touches, event) {
        return this.onTouchesEnded(touches, event);
    },

    onTouchesEnded:function (touches, event) {
        var location = touches[0].getLocation();

        var pos = cc.p( 0, 0 );
        if (this._background)
            pos = this._background.convertToWorldSpace( cc.p(0,0) );
        this._emitter.setPosition(cc.pSub(location, pos));
    },

    onMouseDown : function( event ) {
        return this.onMouseEnded( event );
    },

    onMouseDragged : function( event ) {
        return this.onMouseEnded( event );
    },

    onMouseEnded: function(  event ) {
        var location = event.getLocation();
        var pos = cc.p(0,0);
        if (this._background)
            pos = this._background.convertToWorldSpace( cc.p(0,0) );

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
        var p = this._emitter.getSourcePosition();
        if( p.x==0 && p.y==0 )
            this._emitter.setPosition( cc.p(200, 70) );
    }
});

var DemoFirework = BaseLayer.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleFireworks.create();
        this._background.addChild(this._emitter, 10);
        var myTexture = cc.TextureCache.getInstance().addImage(s_stars1);
        this._emitter.setTexture(myTexture);
        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleFireworks";
    }
});

var DemoFire = BaseLayer.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleFire.create();
        this._background.addChild(this._emitter, 10);

        this._emitter.setTexture(cc.TextureCache.getInstance().addImage(s_fire));//.pvr"];
        var p = this._emitter.getPosition();
        this._emitter.setPosition(cc.p(p.x, 100));

        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleFire";
    }
});

var DemoSun = BaseLayer.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleSun.create();
        this._background.addChild(this._emitter, 10);
        var myTexture = cc.TextureCache.getInstance().addImage(s_fire);
        this._emitter.setTexture(myTexture);
        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleSun";
    }
});

var DemoGalaxy = BaseLayer.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleGalaxy.create();
        this._background.addChild(this._emitter, 10);
        var myTexture = cc.TextureCache.getInstance().addImage(s_fire);
        this._emitter.setTexture(myTexture);
        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleGalaxy";
    }
});

var DemoFlower = BaseLayer.extend({
    ctor:function () {
        this._super();
    },
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleFlower.create();
        this._background.addChild(this._emitter, 10);

        var myTexture = cc.TextureCache.getInstance().addImage(s_stars1);
        this._emitter.setTexture(myTexture);
        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleFlower";
    }
});

var DemoBigFlower = BaseLayer.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleSystem.createWithTotalParticles(50);
        //this._emitter.autorelease();

        this._background.addChild(this._emitter, 10);
        this._emitter.setTexture(cc.TextureCache.getInstance().addImage(s_stars1));
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
        this._emitter.setPosition(cc.p(160, 240));
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

var DemoRotFlower = BaseLayer.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleSystem.createWithTotalParticles( 150 );

        this._background.addChild(this._emitter, 10);
        this._emitter.setTexture(cc.TextureCache.getInstance().addImage(s_stars2));
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
        this._emitter.setPosition(cc.p(160, 240));
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

var DemoMeteor = BaseLayer.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleMeteor.create();
        this._background.addChild(this._emitter, 10);

        this._emitter.setTexture(cc.TextureCache.getInstance().addImage(s_fire));
        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleMeteor";
    }
});

var DemoSpiral = BaseLayer.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleSpiral.create();
        this._background.addChild(this._emitter, 10);

        this._emitter.setTexture(cc.TextureCache.getInstance().addImage(s_fire));
        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleSpiral";
    }
});

var DemoExplosion = BaseLayer.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleExplosion.create();
        this._background.addChild(this._emitter, 10);

        this._emitter.setTexture(cc.TextureCache.getInstance().addImage(s_stars1));
        this._emitter.setAutoRemoveOnFinish(true);

        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleExplosion";
    }
});

var DemoSmoke = BaseLayer.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleSmoke.create();
        this._background.addChild(this._emitter, 10);
        this._emitter.setTexture(cc.TextureCache.getInstance().addImage(s_fire));

        var p = this._emitter.getPosition();
        this._emitter.setPosition(cc.p(p.x, 100));

        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleSmoke";
    }
});

var DemoSnow = BaseLayer.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleSnow.create();
        this._background.addChild(this._emitter, 10);

        var p = this._emitter.getPosition();
        this._emitter.setPosition(cc.p(p.x, p.y - 110));
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

        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleSnow";
    }
});

var DemoRain = BaseLayer.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleRain.create();
        this._background.addChild(this._emitter, 10);

        var p = this._emitter.getPosition();
        this._emitter.setPosition(cc.p(p.x, p.y - 100));
        this._emitter.setLife(4);

        this._emitter.setTexture(cc.TextureCache.getInstance().addImage(s_fire));
        this.setEmitterPosition();
    },
    title:function () {
        return "ParticleRain";
    }
});

var DemoModernArt = BaseLayer.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleSystem.createWithTotalParticles( 200 );

        this._background.addChild(this._emitter, 10);

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

        // emitter position
        this._emitter.setPosition(cc.p(winSize.width / 2, winSize.height / 2));
        this._emitter.setPosVar(cc.p(0,0));

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
        // additive
        this._emitter.setBlendAdditive(false);

        this.setEmitterPosition();
    },
    title:function () {
        return "Varying size";
    }
});

var DemoRing = BaseLayer.extend({
    onEnter:function () {
        this._super();

        this._emitter = cc.ParticleFlower.create();

        this._background.addChild(this._emitter, 10);

        this._emitter.setTexture(cc.TextureCache.getInstance().addImage(s_stars1));

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

var ParallaxParticle = BaseLayer.extend({
    onEnter:function () {
        this._super();

        this._background.getParent().removeChild(this._background, true);
        this._background = null;

        //TODO
        var p = cc.ParallaxNode.create();
        this.addChild(p, 5);

        var p1 = cc.Sprite.create("background3.png");
        var p2 = cc.Sprite.create("background3.png");

        p.addChild(p1, 1, cc.p(0.5, 1), cc.p(0, 250));
        p.addChild(p2, 2, cc.p(1.5, 1), cc.p(0, 50));

        this._emitter = cc.ParticleFlower.create();
        this._emitter.setTexture(cc.TextureCache.getInstance().addImage(s_fire));

        p1.addChild(this._emitter, 10);
        this._emitter.setPosition(cc.p(250, 200));

        var par = cc.ParticleSun.create();
        p2.addChild(par, 10);
        par.setTexture(cc.TextureCache.getInstance().addImage(s_fire));

        var move = cc.MoveBy.create(4, cc.p(300, 0));
        var move_back = move.reverse();
        var seq = cc.Sequence.create(move, move_back);
        p.runAction( cc.RepeatForever.create(seq) );
    },
    title:function () {
        return "Parallax + Particles";
    }
});

var DemoFileParticle = BaseLayer.extend({
    _title:"",
    ctor:function (filename) {
        this._super();
        this._title = filename;
    },
    onEnter:function () {
        this._super();

        this.removeChild(this._background, true);
        this._background = null;

        var filename = "Particles/" + this._title + ".plist";
        this._emitter = cc.ParticleSystem.create( filename );
        this.addChild(this._emitter, 10);

        this.setEmitterPosition();
    },
    title:function () {
        return this._title;
    }
});

var DemoFileBoilingFoam = DemoFileParticle.extend({
    ctor:function () {
        this._super("BoilingFoam");
    },
});

var DemoFileBurstPipe = DemoFileParticle.extend({
    ctor:function () {
        this._super("BurstPipe");
    },
});

var DemoFileComet = DemoFileParticle.extend({
    ctor:function () {
        this._super("Comet");
    },
});

var DemoFileDebian = DemoFileParticle.extend({
    ctor:function () {
        this._super("debian");
    },
});

var DemoFileExplodingRing = DemoFileParticle.extend({
    ctor:function () {
        this._super("ExplodingRing");
    },
});

var DemoFileLavaFlow = DemoFileParticle.extend({
    ctor:function () {
        this._super("LavaFlow");
    },
});

var DemoFileSpinningPeas = DemoFileParticle.extend({
    ctor:function () {
        this._super("SpinningPeas");
    },
});

var DemoFileSpookyPeas = DemoFileParticle.extend({
    ctor:function () {
        this._super("SpookyPeas");
    },
});

var DemoFileUpsidedown= DemoFileParticle.extend({
    ctor:function () {
        this._super("Upsidedown");
    },
});

var DemoFileUpsidedown= DemoFileParticle.extend({
    ctor:function () {
        this._super("Upsidedown");
    },
});

var DemoFileFlower = DemoFileParticle.extend({
    ctor:function () {
        this._super("Flower");
    },
});

var DemoFileSpiral= DemoFileParticle.extend({
    ctor:function () {
        this._super("Spiral");
    },
});

var DemoFileGalaxy= DemoFileParticle.extend({
    ctor:function () {
        this._super("Galaxy");
    },
});

var RadiusMode1 = BaseLayer.extend({
    onEnter:function () {
        this._super();

        this.removeChild(this._background, true);
        this._background = null;

        this._emitter = cc.ParticleSystem.createWithTotalParticles( 150 );
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
        this._emitter.setPosition(cc.p(winSize.width / 2, winSize.height / 2));
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

var RadiusMode2 = BaseLayer.extend({
    onEnter:function () {
        this._super();

        this.removeChild(this._background, true);
        this._background = null;

        this._emitter = cc.ParticleSystem.createWithTotalParticles( 200 );
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
        this._emitter.setPosition(cc.p(winSize.width / 2, winSize.height / 2));
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

var Issue704 = BaseLayer.extend({
    onEnter:function () {
        this._super();

        this.removeChild(this._background, true);
        this._background = null;

        this._emitter = cc.ParticleSystem.createWithTotalParticles( 100 );

        this.addChild(this._emitter, 10);
        this._emitter.setTexture(cc.TextureCache.getInstance().addImage(s_fire));
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
        this._emitter.setPosition(cc.p(winSize.width / 2, winSize.height / 2));
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

var Issue870 = BaseLayer.extend({
    _index:0,
    _elapsedTime:0,
    onEnter:function () {
        this._super();

        this.removeChild(this._background, true);
        this._background = null;

        var system = cc.ParticleSystem.create( "Particles/SpinningPeas.plist" );
        system.setTextureWithRect(cc.TextureCache.getInstance().addImage("particles.png"), cc.rect(0, 0, 32, 32));
        this.addChild(system, 10);
        this._emitter = system;

        this._index = 0;
    },
    title:function () {
        return "Issue 870. SubRect";
    },
    subtitle:function () {
        return "Every 2 seconds the particle should change";
    },
    update:function (dt) {

        this._super(dt);

        this._elapsedTime += dt;
        if( this._elapsedTime > 2 ) {
            this._index = (this._index + 1) % 4;
            var rect = cc.rect(this._index * 32, 0, 32, 32);
            this._emitter.setTextureWithRect(this._emitter.getTexture(), rect);

            this._elapsedTime = 0;
        }
    }
});

//
// Order of tests
//

scenes.push( DemoFlower );
scenes.push( DemoGalaxy );
scenes.push( DemoFirework );
scenes.push( DemoSpiral );
scenes.push( DemoSun );
scenes.push( DemoMeteor );
scenes.push( DemoFire );
scenes.push( DemoSmoke );
scenes.push( DemoExplosion );
scenes.push( DemoSnow );
scenes.push( DemoRain );
scenes.push( DemoBigFlower );
scenes.push( DemoRotFlower );
scenes.push( DemoModernArt );
scenes.push( DemoRing );
scenes.push( ParallaxParticle );
scenes.push( DemoFileBoilingFoam );
scenes.push( DemoFileBurstPipe );
scenes.push( DemoFileComet );
scenes.push( DemoFileDebian );
scenes.push( DemoFileExplodingRing );
scenes.push( DemoFileLavaFlow );
scenes.push( DemoFileSpinningPeas );
scenes.push( DemoFileSpookyPeas );
scenes.push( DemoFileUpsidedown );
scenes.push( DemoFileFlower );
scenes.push( DemoFileSpiral );
scenes.push( DemoFileGalaxy );
scenes.push( RadiusMode1 );
scenes.push( RadiusMode2 );
scenes.push( Issue704 );
scenes.push( Issue870 );

//------------------------------------------------------------------
//
// Main entry point
//
//------------------------------------------------------------------
function run()
{
    var scene = cc.Scene.create();
    var layer = new scenes[currentScene]();
    scene.addChild( layer );

    var runningScene = director.getRunningScene();
    if( runningScene == null )
        director.runWithScene( scene );
    else
        director.replaceScene( cc.TransitionFade.create(0.5, scene ) );
}

run();


