//
// http://www.cocos2d-iphone.org
// http://www.chipmunk-physics.org
//
// Watermelon with Me
// A JS game using cocos2d and Chipmunk
// 
//
// Physics code based on Space Patrol:
// https://github.com/slembcke/SpacePatrol
//
// Most of the comments in the physics code were copied+pased from Space Patrol
//
//
// LICENSE:
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

require("js/helper.js");

// Z Orders (grouped by parent)

// parent is scroll batch node 
Z_WATERMELON = 5;
Z_COIN = 8;
Z_FINISH = 9;
Z_CHASSIS = 10;
Z_WHEEL = 11;

// parent is scroll node (parallax node)
Z_MOUNTAINS = 0;
Z_SPRITES = 10;
Z_TERRAIN = 20;
Z_DEBUG_PHYSICS = 50;

// parent is game layer
Z_SCROLL = 10;
Z_SMOKE = 15;
Z_HUD = 20;
Z_LABEL = 30;
Z_DEBUG_MENU = 30;

// Game state
STATE_PAUSE = 0;
STATE_PLAYING = 1;
STATE_GAME_OVER = 2;
STATE_LEVEL_COMPLETE = 3;

audioEngine = cc.AudioEngine.getInstance();
director = cc.Director.getInstance();
winSize = director.getWinSize();
centerPos = cc.p( winSize.width/2, winSize.height/2 );

sizeRatio = winSize.width / 480;

//
// Levels
//
levels = [];

// Level 0
levels.push( {'coins' : [ {x:300,y:50},{x:350,y:50},{x:400,y:50},{x:450,y:50},{x:500,y:50},{x:550,y:50},{x:600,y:50},
                      {x:1300,y:50},{x:1350,y:50},{x:1400,y:50},{x:1450,y:50},{x:1500,y:50},{x:1550,y:50},{x:1600,y:50},
                    ],

          'car' : {x:80, y:60}, 
          'finish' : {x:3000, y:20},

          // points relatives to the previous point
          'lines' : [ {x:0,y:0}, {x:850,y:0},
                      {x:20, y:5},{x:20,y:-5}, {x:20, y:10},{x:20,y:-10}, {x:20, y:5},{x:20,y:-5},
                      {x:500,y:0},
                      {x:20, y:5},{x:20,y:-5}, {x:20, y:10},{x:20,y:-10}, {x:20, y:5},{x:20,y:-5},
                      {x:500,y:0},
                      {x:20, y:5},{x:20,y:-5}, {x:20, y:10},{x:20,y:-10}, {x:20, y:5},{x:20,y:-5},
                      {x:500,y:0},
                      {x:20, y:5},{x:20,y:-5}, {x:20, y:10},{x:20,y:-10}, {x:20, y:5},{x:20,y:-5},
                      {x:300,y:0},
                    ],
          }
          );

// Level 1
levels.push( {'coins' : [ {x:1120,y:150}, {x:1160,y:140}, {x:1200,y:130}, {x:1240,y:120}, {x:1280,y:110},
                      {x:2470,y:150}, {x:2510,y:140}, {x:2550,y:130}, {x:2590,y:120}, {x:2630,y:110},
                      {x:2220,y:60}, {x:2260,y:70}, {x:2300,y:80}, {x:2340,y:90}, {x:2380,y:100},
                    ],

          'car' : {x:80, y:60}, 
          'finish' : {x:3400, y:20},

          // points relatives to the previous point
          'lines' : [ {x:0,y:0}, {x:350,y:10}, {x:20, y:5}, {x:500, y:-20}, {x:200, y:80}, {x:100, y:-40}, {x:200,y:-10}, {x:400, y:-50}, {x:300,y:0}, {x:400,y:100}, {x:200,y:-100}, {x:400,y:0}, {x:20,y:15}, {x:20,y:-15}, {x:400,y:0}, ],
          }
          );

// Level 2
levels.push( {'coins' : [ {x:1120,y:150}, {x:1160,y:140}, {x:1200,y:130}, {x:1240,y:120}, {x:1280,y:110},
                    ],

          'car' : {x:80, y:60}, 
          'finish' : {x:4100, y:-100},

          // points relatives to the previous point
          'lines' : [ {x:0,y:0}, {x:350,y:0},
                      {x:300, y:100}, {x:100, y:50}, {x:50, y:12}, {x:25, y:0}, {x:50,y:-12}, {x:100, y:-25}, {x:400, y:-200}, {x:500, y:0},
                      {x:20, y:15},{x:20,y:-15}, {x:20, y:5},{x:20,y:-5},
                      {x:300,y:0},
                      {x:300, y:100}, {x:100, y:50}, {x:50, y:12}, {x:25, y:0}, {x:50,y:-12}, {x:100, y:-25}, {x:400, y:-200}, {x:500, y:0},
                      {x:20, y:15},{x:20,y:-15}, {x:20, y:5},{x:20,y:-5},
                      {x:300,y:0},
                    ],
          }
          );
//
// Physics constants
//

INFINITY = 1e50;

COLLISION_TYPE_CAR = 1;
COLLISION_TYPE_COIN = 2;
COLLISION_TYPE_WATERMELON = 3;
COLLISION_TYPE_FLOOR = 4;
COLLISION_TYPE_FINISH = 5;

// Create some collision rules for fancy layer based filtering.
// There is more information about how this works in the Chipmunk docs.
COLLISION_RULE_TERRAIN_BUGGY = 1 << 0;
COLLISION_RULE_BUGGY_ONLY = 1 << 1;

// Bitwise or the rules together to get the layers for a certain shape type.
COLLISION_LAYERS_TERRAIN = COLLISION_RULE_TERRAIN_BUGGY;
COLLISION_LAYERS_BUGGY = (COLLISION_RULE_TERRAIN_BUGGY | COLLISION_RULE_BUGGY_ONLY);

// Some constants for controlling the car and world:
GRAVITY =  1200.0;
WHEEL_MASS = 0.25;
CHASSIS_MASS = 0.7;
FRONT_SPRING = 150.0;
FRONT_DAMPING = 3.0;
COG_ADJUSTMENT = cp.v(0.0, -10.0);
REAR_SPRING = 100.0;
REAR_DAMPING = 3.0;
ROLLING_FRICTION = 5e2;
ENGINE_MAX_TORQUE = 6.0e4;
ENGINE_MAX_W = 60;
BRAKING_TORQUE = 3.0e4;
DIFFERENTIAL_TORQUE = 0.5;

// Groups
GROUP_BUGGY = 1;
GROUP_COIN = 2;

WATERMELON_MASS = 0.05;

// Node Tags (used by CocosBuilder)
SCORE_LABEL_TAG = 10;
TIME_LABEL_TAG = 11;
TITLE_TAG = 50;

//
// Game Layer
//
var GameLayer = cc.LayerGradient.extend({

    _space:null,
    _motor:null,
    _frontBrake:null,
    _rearBrake:null,
    _rearWheel:null,
    _chassis:null,
    _batch:null,
    _shapesToRemove:[],
    _score:0,
    _scoreLabel:null,
    _time:0,
    _timeLabel:null,
    _level:0,
    _state:STATE_PAUSE,
    _deferredState:null,
    _debugNode:null,
    _scrollNode:null,
    _terrain:null,
    _carSprite:null,
    _carSmoke:null,

    ctor:function (level) {
                                
        var parent = new cc.LayerGradient();
        __associateObjWithNative(this, parent);
        this.init(cc.c4b(0, 0, 0, 255), cc.c4b(255, 255, 255, 255));

        this.scheduleUpdate();

        this.enableEvents( true );

        cc.MenuItemFont.setFontSize(16 * sizeRatio );

        var item1_pause = cc.MenuItemFont.create("Pause" );
        var item1_resume = cc.MenuItemFont.create("Resume" );
        var item1 = cc.MenuItemToggle.create( item1_pause, item1_resume );
        item1.setCallback( this, this.onPause);
        var item2 = cc.MenuItemFont.create("Debug On/Off", this, this.onToggleDebug);
        var menu = cc.Menu.create( item1, item2 );
        menu.alignItemsVertically();
        this.addChild( menu, Z_DEBUG_MENU );
        menu.setPosition( cc._p( winSize.width-(50*sizeRatio), winSize.height-(80*sizeRatio) )  );
    
        var animCache = cc.AnimationCache.getInstance();
        animCache.addAnimations("coins_animation.plist");

        // scrollng Node.. all game objects are children of this node (or one of its subchildre)
        var scroll = cc.ParallaxNode.create();
        this.addChild( scroll, Z_SCROLL );
        this._scrollNode = scroll;

        // coin only needed to obtain the texture for the Batch Node
        var coin = cc.Sprite.createWithSpriteFrameName("coin01.png");
        this._batch = cc.SpriteBatchNode.createWithTexture( coin.getTexture(), 100 );
        scroll.addChild( this._batch, Z_SPRITES, cc._p(1,1), cc.POINT_ZERO );

        // "endless" background image
        var background = cc.Sprite.create("Parallax.pvr.gz", cc.rect(0,0,4096,512) );
        scroll.addChild(background, Z_MOUNTAINS , cc._p(0.2, 0.2), cc._p(0,-150));
        background.setAnchorPoint( cc.POINT_ZERO );
        background.getTexture().setTexParameters(gl.LINEAR, gl.LINEAR, gl.REPEAT, gl.CLAMP_TO_EDGE);

        // Terrain
        this._terrain = cc.DrawNode.create();
        scroll.addChild( this._terrain, Z_TERRAIN, cc._p(1,1), cc.POINT_ZERO );
//        this._terrain.setVisible( false );

        // Smoke
        this._carSmoke = cc.ParticleSystem.create( "car_smoke.plist" );
        this._carSmoke.setPosition( cc.POINT_ZERO );
        this.addChild( this._carSmoke, Z_SMOKE );
        this._carSmoke.setPositionType( cc.PARTICLE_TYPE_RELATIVE );

        this._shapesToRemove = [];

        this.initHUD();

        this._score = 0;
        this._time = 0;
        this._state = STATE_PAUSE;
        this._level = level;

    },

    // HUD stuff
    initHUD:function() {
        var hud = cc.Reader.load("HUD.ccbi", this);
        this.addChild( hud, Z_HUD );
        this._scoreLabel = hud.getChildByTag( SCORE_LABEL_TAG );
        this._timeLabel = hud.getChildByTag( TIME_LABEL_TAG );

        // bug in cocosbuilder
        this._scoreLabel.setAnchorPoint( cc._p(1, 0.5) );
        this._timeLabel.setAnchorPoint( cc._p(0, 0.5) );
    },

    addScore:function(value) {
        this._score += value;
        this._scoreLabel.setString( this._score );
        this._scoreLabel.stopAllActions();

        var scaleUpTo = cc.ScaleTo.create(0.05, 1.2);
        var scaleDownTo = cc.ScaleTo.create(0.05, 1.0);
        var seq = cc.Sequence.create( scaleUpTo, scaleDownTo );
        this._scoreLabel.runAction( seq );

    },

    //
    // Events
    //
    onRestart:function(sender) {
        var scene = cc.Scene.create();
        var layer = new GameLayer(this._level);
        scene.addChild( layer );
        director.replaceScene( cc.TransitionFade.create(1, scene) );
    },

    onPause:function(sender) {
        if( this._state == STATE_PAUSE )
            this._state = STATE_PLAYING;
        else
            this._state = STATE_PAUSE;
    },

    onNextLevel:function(sender) {
        var scene = cc.Scene.create();
        var layer = new GameLayer(this._level+1);
        scene.addChild( layer );
        director.replaceScene( cc.TransitionFade.create(1, scene) );
    },

    onMainMenu:function(sender) {
        var scene = cc.Scene.create();
        var layer = new MenuLayer();
        scene.addChild( layer );
        director.replaceScene( cc.TransitionProgressRadialCCW.create(1, scene) );
    },

    onToggleDebug:function(sender) {
        var state = this._debugNode.getVisible();
        this._debugNode.setVisible( !state );
    },

    onMouseDown:function(event) {
        this.setThrottle(1);
        return true;
    },
    onMouseUp:function(event) {
        this.setThrottle(0);
        return true;
    },
    onTouchesBegan:function( touches, event) {
        this.setThrottle(1);
        return true;
    },
    onTouchesEnded:function( touches, event) {
        this.setThrottle(0);
        return true;
    },

    onEnterTransitionDidFinish:function() {

        this.initPhysics();
        this.setupLevel(this._level);

        this._state = STATE_PLAYING;

        // Level Label
        var label = cc.LabelBMFont.create("LEVEL " + this._level, "Abadi40.fnt" );
        label.setPosition( centerPos );
        this.addChild( label, Z_LABEL );
        var d = cc.DelayTime.create(1);
        var scale = cc.ScaleBy.create(1.1, 5);
        var fade = cc.FadeOut.create(1.1);
        var s = cc.Spawn.create( scale, fade );
        var selfremove = cc.CallFunc.create(this, this.onRemoveMe );
        var seq = cc.Sequence.create(d, s, selfremove );
        label.runAction( seq );
        
    },

    onRemoveMe:function( sender ) {
        sender.removeFromParentAndCleanup( true );
    },

    onExit:function() {

        this.enableCollisionEvents( false );
        // XXX: Leak... all Shapes and Bodies should be freed
        cp.spaceFree( this._space );
    },

    // Coin and Car
	onCollisionBeginCoin : function ( arbiter, space ) {

		var bodies = cp.arbiterGetBodies( arbiter );
		var shapes = cp.arbiterGetShapes( arbiter );
		var collTypeA = cp.shapeGetCollisionType( shapes[0] );
		var collTypeB = cp.shapeGetCollisionType( shapes[1] );

        var shapeCoin =  (collTypeA == COLLISION_TYPE_COIN) ? shapes[0] : shapes[1];

        // XXX: hack to prevent double deletion... argh...
        // Since shapeCoin in 64bits is a typedArray and in 32-bits is an integer
        // a ad-hoc solution needs to be implemented
        if( this._shapesToRemove.length == 0 ) {
            // since Coin is a sensor, it can't be removed at PostStep.
            // PostStep is not called for Sensors
            this._shapesToRemove.push( shapeCoin );
            audioEngine.playEffect("pickup_coin.wav");

//            cc.log("Adding shape: " + shapeCoin[0] + " : " + shapeCoin[1] );
            cc.log("Adding shape: " + shapeCoin );
            this.addScore(1);
        }
        return true;
	},

    // Floor and Watermelon
	onCollisionBeginWatermelon : function ( arbiter, space ) {
        this.setThrottle(0);
        this.setGameStateDeferred( STATE_GAME_OVER );
        return true;
	},

    // Car and Finish line
	onCollisionBeginFinish : function ( arbiter, space ) {
        this.setThrottle(0);
        this.setGameStateDeferred( STATE_LEVEL_COMPLETE );
        return true;
	},

    update:function(dt) {

        // update state if necessary
        if( this._deferredState )
            this.setGameState( this._deferredState );

        if( this._state == STATE_PLAYING ) {
            // update time
            this._time += dt;
            this._timeLabel.setString( '' + this._time.toFixed(1) );
        }

        // Don't update physics on game over
        if( this._state != STATE_PAUSE )
            cp.spaceStep( this._space, dt);

        // sync smoke with car
        if( this._carSprite ) {
            var p = this._carSprite.convertToWorldSpace( cc.POINT_ZERO );
            this._carSmoke.setPosition( p );
        }

        var l = this._shapesToRemove.length;

        for( var i=0; i < l; i++ ) {
            var shape = this._shapesToRemove[i];

//            cc.log("removing shape: " + shape[0] + " : " + shape[1] );
            cc.log("removing shape: " + shape );

            cp.spaceRemoveStaticShape( this._space, shape );
            cp.shapeFree( shape );

            var body = cp.shapeGetBody( shape );

            var sprite = cp.bodyGetUserData( body );
            sprite.removeFromParentAndCleanup(true);

            cp.bodyFree( body );

        }

        if( l > 0 )
            this._shapesToRemove = [];
    },

    //
    // Level Setup
    //
    setupLevel : function(lvl) {

        var x = 0;
        var y = 0;
        var width = winSize.width;
        var height = winSize.height;

        var level = levels[ lvl ];
        
        // Coins
        var coins = level['coins']; 
        for( var i=0;i < coins.length; i++) {
            var coin = coins[i];
            this.createCoin( cc._p( coin.x, coin.y) ); 
        }

        // car
        var car = level['car'];
        this.createCar( cp.v( car.x, car.y) );

        // finish
        var finish = level['finish'];
        this.createFinish( cp._v(finish.x, finish.y) );

        //lines  
        var poly = [];
        var p = {x:0, y:0};
        var lines = level['lines']; 

        for( var i=0; i < lines.length; i++) {
            var line = lines[i];
            if( i > 0 ) {
                this.createSegment( cp._v(p.x, p.y), cp._v( p.x+line.x, p.y+line.y )  ); 
                this._terrain.drawSegment( cc._p(p.x, p.y), cc._p(p.x+line.x, p.y+line.y), 5, cc.c4f(0.43,0.39,0.34,1) );
            }

            p = {x:p.x+line.x, y:p.y+line.y};

            poly.push( cc.p(p.x, p.y) );

            // needed for world boundary
            x = Math.min(x, p.x);
            y = Math.min(y, p.y);
            width = Math.max( width, p.x);
            height = Math.max( height, p.y);
        }

        poly.unshift( cc.p(x,y) );

        // XXX: Bug in CCDrawNode: No tesselation, so "fill" is disabled
        // XXX: CCDrawNode#drawPoly is super expensive... using drawSegment instead
        // poly, fill color, border width, border color
//        this._terrain.drawPoly( poly, cc.c4f(0,0,0,0 ), 1, cc.c4f(0.82,0.41,0.04,1) );

        cc.log("World Boundary: " + x + " " + y + " " + width + " " + height );

        var rect = cc.rect(x,y,width,height); 
        var a = cc.Follow.create( this._carSprite, rect );
        this._scrollNode.runAction( a );

        this.createWorldBoundary( rect );
    },

    createWorldBoundary:function( rect ) {

		var staticBody = cp.spaceGetStaticBody( this._space );

        var x = rect.x;
        var y = rect.y;
        var w = rect.width;
        var h = rect.height;

		// Walls
		var walls =[cp.segmentShapeNew( staticBody, cp._v(x,y), cp._v(w,y), 0 ),   // bottom
			     	cp.segmentShapeNew( staticBody, cp._v(x,h), cp._v(w,h), 0),	    // top
                    cp.segmentShapeNew( staticBody, cp._v(x,y), cp._v(x,h), 0),     // left
                    cp.segmentShapeNew( staticBody, cp._v(w,y), cp._v(w,h), 0)  	// right
				];
		for( var i=0; i < walls.length; i++ ) {
			var wall = walls[i];
			cp.shapeSetElasticity(wall, 0);
			cp.shapeSetFriction(wall, 0);
            cp.shapeSetCollisionType(wall, COLLISION_TYPE_FLOOR);
			cp.spaceAddStaticShape( this._space, wall );
		}
    },

    //
    // Physics
    //
	initPhysics :  function() {
		this._space =  cp.spaceNew();

		// Gravity
		cp.spaceSetGravity( this._space, cp._v(0, -GRAVITY) );

        this.enableCollisionEvents( true );

        // debug only
        this._debugNode = cc.ChipmunkDebugNode.create( this._space );
        this._debugNode.setVisible( false );
        // Parallax ratio and offset
        this._scrollNode.addChild( this._debugNode, Z_DEBUG_PHYSICS, cc._p(1,1), cc.POINT_ZERO );
	},

    setThrottle : function( throttle ) {
        if(throttle > 0){
            // The motor is modeled like an electric motor where the torque decreases inversely as the rate approaches the maximum.
            // It's simple to code up and feels nice.

            // _motor.maxForce = cpfclamp01(1.0 - (_chassis.body.angVel - _rearWheel.body.angVel)/ENGINE_MAX_W)*ENGINE_MAX_TORQUE;
            var maxForce = cp.fclamp01(1.0 - ( (cp.bodyGetAngVel(this._chassis) - cp.bodyGetAngVel(this._rearWheel)) / ENGINE_MAX_W)) * ENGINE_MAX_TORQUE;
            cp.constraintSetMaxForce( this._motor, maxForce );

            // Set the brakes to apply the baseline rolling friction torque.
            cp.constraintSetMaxForce( this._frontBrake, ROLLING_FRICTION );
            cp.constraintSetMaxForce( this._rearBrake, ROLLING_FRICTION );
        } else if(throttle < 0){
            // Disable the motor.
            cp.constraintSetMaxForce( this._motor, 0 );
            // It would be a pretty good idea to give the front and rear brakes different torques.
            // The buggy as is now has a tendency to tip forward when braking hard.
            cp.constraintSetMaxForce( this._frontBrake, BRAKING_TORQUE);
            cp.constraintSetMaxForce( this._rearBrake, BRAKING_TORQUE);
        } else {
            // Disable the motor.
            cp.constraintSetMaxForce( this._motor, 0 );
            // Set the brakes to apply the baseline rolling friction torque.
            cp.constraintSetMaxForce( this._frontBrake, ROLLING_FRICTION );
            cp.constraintSetMaxForce( this._rearBrake, ROLLING_FRICTION );
        }
    },

    createCar : function(pos) {
        var front = this.createWheel( cp.vadd(pos, cp._v(47,-25) ) );
        this._chassis = this.createChassis( cp.vadd( pos, COG_ADJUSTMENT ) );
        this._rearWheel = this.createWheel( cp.vadd( pos, cp._v(-35, -25) ) );
        this.createCarJoints( this._chassis, front, this._rearWheel );
        this.createCarFruits( pos );

        this.setThrottle( 0 );
    },

    createCarJoints: function( chassis, front, rear ) {

        // The front wheel strut telescopes, so we'll attach the center of the wheel to a groov joint on the chassis.
        // I created the graphics specifically to have a 45 degree angle. So it's easy to just fudge the numbers.
        var grv_a = cp.bodyWorld2Local( chassis, cp.bodyGetPos(front) );
        var grv_b = cp.vadd( grv_a, cp.vmult( cp._v(-1, 1), 7 ) );
        var frontJoint = cp.grooveJointNew( chassis, front, grv_a, grv_b, cp.vzero );

        // Create the front zero-length spring.
        var front_anchor =  cp.bodyWorld2Local( chassis, cp.bodyGetPos(front) );
        var frontSpring = cp.dampedSpringNew( chassis, front, front_anchor, cp.vzero, 0, FRONT_SPRING, FRONT_DAMPING );

        // The rear strut is a swinging arm that holds the wheel a at a certain distance from a pivot on the chassis.
        // A perfect fit for a pin joint conected between the chassis and the wheel's center.
        var rearJoint = cp.pinJointNew( chassis, rear, cp.vsub( cp._v(-14,-8), COG_ADJUSTMENT), cp.vzero );
        
    	// return cpvtoangle(cpvsub([_chassis.body local2world:_rearJoint.anchr1], _rearWheel.body.pos));
        var rearStrutRestAngle = cp.vtoangle( cp.vsub(
                                                cp.bodyLocal2World( chassis, cp.pinJointGetAnchr1(rearJoint) ),
                                                cp.bodyGetPos(rear) ) );

        // Create the rear zero-length spring.
        var rear_anchor = cp.bodyWorld2Local( chassis, cp.bodyGetPos( rear ) );
        var rearSpring = cp.dampedSpringNew( chassis, rear, rear_anchor, cp.vzero, 0, REAR_SPRING, REAR_DAMPING );

        // Attach a slide joint to the wheel to limit it's range of motion.
        var rearStrutLimit = cp.slideJointNew( chassis, rear, rear_anchor, cp.vzero, 0, 20 );
			
        // The main motor that drives the buggy.
        var motor = cp.simpleMotorNew( chassis, rear, ENGINE_MAX_W );
        cp.constraintSetMaxForce( motor, 0.0 );
			
        // I don't know if "differential" is the correct word, but it transfers a fraction of the rear torque to the front wheels.
        // In case the rear wheels are slipping. This makes the buggy less frustrating when climbing steep hills.
        var differential = cp.simpleMotorNew( rear, front, 0 );
        cp.constraintSetMaxForce( differential, ENGINE_MAX_TORQUE*DIFFERENTIAL_TORQUE );
			
        // Wheel brakes.
        // While you could reuse the main motor for the brakes, it's easier not to.
        // It won't cause a performance issue to have too many extra motors unless you have hundreds of buggies in the game.
        // Even then, the motor constraints would be the least of your performance worries.
        var frontBrake = cp.simpleMotorNew( chassis, front, 0 );
        cp.constraintSetMaxForce( frontBrake, ROLLING_FRICTION );
        var rearBrake = cp.simpleMotorNew( chassis, rear, 0 );
        cp.constraintSetMaxForce( rearBrake, ROLLING_FRICTION );

        cp.spaceAddConstraint(this._space, frontJoint );
        cp.spaceAddConstraint(this._space, rearJoint );
        cp.spaceAddConstraint(this._space, rearSpring );
        cp.spaceAddConstraint(this._space, motor );
        cp.spaceAddConstraint(this._space, differential );
        cp.spaceAddConstraint(this._space, frontBrake );
        cp.spaceAddConstraint(this._space, rearBrake );

        this._motor = motor;
        this._frontBrake = frontBrake;
        this._rearBrake = rearBrake;
    },

    createWheel : function( pos ) {
        var sprite = cc.ChipmunkSprite.createWithSpriteFrameName("Wheel.png");  
        var radius = 0.95 * sprite.getContentSize().width / 2;

		var body = cp.bodyNew(WHEEL_MASS, cp.momentForCircle(WHEEL_MASS, 0, radius, cp.vzero ) );
		cp.bodySetPos( body, pos );
        sprite.setBody( body );

        var shape = cp.circleShapeNew( body, radius, cp.vzero );
        cp.shapeSetFriction( shape, 1 );
        cp.shapeSetGroup( shape, GROUP_BUGGY );
        cp.shapeSetLayers( shape, COLLISION_LAYERS_BUGGY );
        cp.shapeSetCollisionType( shape, COLLISION_TYPE_CAR );

        cp.spaceAddBody( this._space, body );
        cp.spaceAddShape( this._space, shape );
        this._batch.addChild( sprite, Z_WHEEL);

        return body;
    },

    createChassis : function(pos) {
        var sprite = cc.ChipmunkSprite.createWithSpriteFrameName("Chassis.png"); 
        var anchor = cp.vadd( sprite.getAnchorPointInPoints(), COG_ADJUSTMENT );
        var cs = sprite.getContentSize();
        sprite.setAnchorPoint( cc.p(anchor.x / cs.width, anchor.y/cs.height) );

        // XXX: Space Patrol uses a nice poly for the chassis.
        // XXX: Add something similar here, instead of a boxed chassis

        var body = cp.bodyNew( CHASSIS_MASS, cp.momentForBox(CHASSIS_MASS, cs.width, cs.height ) );
        cp.bodySetPos( body, pos );
        sprite.setBody( body );

        cp.spaceAddBody( this._space, body );
        this._batch.addChild( sprite, Z_CHASSIS );
        this._carSprite = sprite;

        // bottom of chassis
        var shape = cp.boxShapeNew( body, cs.width, 15 );
		cp.shapeSetFriction(shape, 0.3);
		cp.shapeSetGroup( shape, GROUP_BUGGY );
		cp.shapeSetLayers( shape, COLLISION_LAYERS_BUGGY );
        cp.shapeSetCollisionType( shape, COLLISION_TYPE_CAR );

        cp.spaceAddShape( this._space, shape );

        // box for fruits (left)
        var shape = cp.boxShapeNew2( body, cp.bBNew(-50,0, -46,30) );
		cp.shapeSetFriction(shape, 0.3);
		cp.shapeSetGroup( shape, GROUP_BUGGY );
		cp.shapeSetLayers( shape, COLLISION_LAYERS_BUGGY );
        cp.shapeSetCollisionType( shape, COLLISION_TYPE_CAR );
        cp.spaceAddShape( this._space, shape );

        // box for fruits (right)
        var shape = cp.boxShapeNew2( body, cp.bBNew(8,0, 12,30) );
		cp.shapeSetFriction(shape, 0.3);
		cp.shapeSetGroup( shape, GROUP_BUGGY );
		cp.shapeSetLayers( shape, COLLISION_LAYERS_BUGGY );
        cp.shapeSetCollisionType( shape, COLLISION_TYPE_CAR );
        cp.spaceAddShape( this._space, shape );

        return body;
    },

    createCarFruits : function(pos) {
        // create some fruits
        for(var i=0; i < 4;i++) {
            var sprite = cc.ChipmunkSprite.createWithSpriteFrameName("watermelon.png");  
            var radius = 0.95 * sprite.getContentSize().width / 2;

            var body = cp.bodyNew(WATERMELON_MASS, cp.momentForCircle(WATERMELON_MASS, 0, radius, cp.vzero) );
            cp.bodySetPos( body, pos );
            sprite.setBody( body );

            var shape = cp.circleShapeNew( body, radius, cp.vzero );
            cp.shapeSetFriction( shape, 1 );
            cp.shapeSetCollisionType( shape, COLLISION_TYPE_WATERMELON);

            cp.spaceAddShape( this._space, shape );
            cp.spaceAddBody( this._space, body );
            this._batch.addChild( sprite, Z_WATERMELON );
        }
    },

    createCoin: function( pos ) {
        // coins are static bodies and sensors
        var sprite = cc.ChipmunkSprite.createWithSpriteFrameName("coin01.png");  
        var radius = 0.95 * sprite.getContentSize().width / 2;
        
        var body = cp.bodyNew(1, 1);
        cp.bodyInitStatic(body);
		cp.bodySetPos( body, pos );
        sprite.setBody( body );

        var shape = cp.circleShapeNew( body, radius, cp.vzero );
        cp.shapeSetFriction( shape, 1 );
        cp.shapeSetGroup( shape, GROUP_COIN );
        cp.shapeSetCollisionType( shape, COLLISION_TYPE_COIN );
        cp.shapeSetSensor( shape, true );

        cp.spaceAddStaticShape( this._space, shape );
        this._batch.addChild( sprite, Z_COIN);

        var animation = cc.AnimationCache.getInstance().getAnimation("coin");
        var animate = cc.Animate.create(animation); 
        var repeat = cc.RepeatForever.create( animate );
        sprite.runAction( repeat );

        // Needed for deletion
        cp.bodySetUserData( body, sprite );

        return body;
    },

    createFinish:function( pos ) {
        var sprite = cc.ChipmunkSprite.createWithSpriteFrameName("farmers-market.png"); 
        var cs = sprite.getContentSize();
        var body = cp.bodyNew( 1, 1);
        cp.bodyInitStatic( body );
        sprite.setBody( body );
        cp.bodySetPos( body, pos );

        var shape = cp.boxShapeNew( body, cs.width, cs.height );
        cp.shapeSetCollisionType( shape, COLLISION_TYPE_FINISH );
        cp.shapeSetSensor( shape, true );

        cp.spaceAddStaticShape( this._space, shape );
        this._batch.addChild( sprite, Z_FINISH);
    },

    createSegment: function( src, dst) {
		var staticBody = cp.spaceGetStaticBody( this._space );
		var segment = cp.segmentShapeNew( staticBody, src, dst, 5 );
        cp.shapeSetElasticity(segment, 1);
        cp.shapeSetFriction(segment, 1);
        cp.shapeSetCollisionType(segment, COLLISION_TYPE_FLOOR);
        cp.spaceAddStaticShape( this._space, segment );
    },

    //
    // Game State
    //
    
    // call the 'deferred' option if you want to modify Chipmunk's state from a Chipmunk's callback
    setGameStateDeferred: function( state ) {
        this._deferredState = state; 
    },

    setGameState: function( state ) {
        if( state != this._state ) {

            if( state == STATE_GAME_OVER  )
                this.displayGameOver();

            else if (state == STATE_LEVEL_COMPLETE )
                this.displayLevelComplete();

            this._state = state;
        }
        this._deferredState = null;
    },

    displayLevelComplete:function() {
        

        if( this._level+1 < levels.length ) {
            cc.MenuItemFont.setFontSize(16 * sizeRatio );
            var item1 = cc.MenuItemFont.create("Next Level", this, this.onNextLevel);
            var menu = cc.Menu.create( item1 );
            menu.alignItemsVertically();
            this.addChild( menu, Z_DEBUG_MENU );
            menu.setPosition( cc._p( winSize.width/2, winSize.height/3 )  );

            var legend = "LEVEL COMPLETE";
        } else {
            cc.MenuItemFont.setFontSize(16 * sizeRatio );
            var item1 = cc.MenuItemFont.create("Main Menu", this, this.onMainMenu);
            var menu = cc.Menu.create( item1 );
            menu.alignItemsVertically();
            this.addChild( menu, Z_DEBUG_MENU );
            menu.setPosition( cc._p( winSize.width/2, winSize.height/3 )  );

            var legend = "GAME COMPLETE";
        }

        var label = cc.LabelBMFont.create(legend, "Abadi40.fnt" );
        label.setPosition( centerPos );
        label.setScale(0.2);
        var sa = cc.ScaleTo.create(0.5, 1.05 );
        var sb1 = cc.ScaleTo.create(0.5, 1 );
        var sb2 = cc.ScaleTo.create(0.5, 1.05);
        var seq = cc.Sequence.create( sb1, sb2 );
        var rep = cc.Repeat.create( seq, 1000 );
        var all = cc.Sequence.create( sa, rep );
        label.runAction( all );
        this.addChild( label, Z_LABEL );

        this.enableEvents( false );
        this.enableCollisionEvents( false );

        audioEngine.playEffect("LevelComplete.wav");
    },

    displayGameOver:function() {
        var label = cc.LabelBMFont.create("GAME OVER", "Abadi40.fnt" );
        label.setPosition( centerPos );
        this.addChild( label, Z_LABEL );
        label.setScale(0.2);
        var sa = cc.ScaleTo.create(0.5, 1.05 );
        var sb1 = cc.ScaleTo.create(0.5, 1 );
        var sb2 = cc.ScaleTo.create(0.5, 1.05);
        var seq = cc.Sequence.create( sb1, sb2 );
        var rep = cc.Repeat.create( seq, 1000 );
        var all = cc.Sequence.create( sa, rep );
        label.runAction( all );

        this.enableEvents( false );
        this.enableCollisionEvents( false );

        audioEngine.playEffect("GameOver.wav");

        cc.MenuItemFont.setFontSize(16 * sizeRatio );
        var item1 = cc.MenuItemFont.create("Play Again", this, this.onRestart);
        var item2 = cc.MenuItemFont.create("Main Menu", this, this.onMainMenu);
        var menu = cc.Menu.create( item1, item2 );
        menu.alignItemsVertically();
        this.addChild( menu, Z_DEBUG_MENU );
        menu.setPosition( cc._p( winSize.width/2, winSize.height/3 )  );
    },


    //
    // Helpers
    //
    enableEvents:function(enabled) {
        var platform = __getPlatform();
        if( platform.substring(0,7) == 'desktop' ) {
            this.setMouseEnabled( enabled );
        } else if( platform.substring(0,6) == 'mobile' ) {
            this.setTouchEnabled( enabled );
        }
    },

    enableCollisionEvents:function(enabled) {
        if( enabled ) {
            // collision handler
            cp.spaceAddCollisionHandler( this._space, COLLISION_TYPE_CAR, COLLISION_TYPE_COIN, this, this.onCollisionBeginCoin, null, null, null );
            cp.spaceAddCollisionHandler( this._space, COLLISION_TYPE_CAR, COLLISION_TYPE_FINISH, this, this.onCollisionBeginFinish, null, null, null );
            cp.spaceAddCollisionHandler( this._space, COLLISION_TYPE_FLOOR, COLLISION_TYPE_WATERMELON, this, this.onCollisionBeginWatermelon, null, null, null );
        } else {
            cp.spaceRemoveCollisionHandler( this._space, COLLISION_TYPE_FLOOR, COLLISION_TYPE_WATERMELON );
            cp.spaceRemoveCollisionHandler( this._space, COLLISION_TYPE_COIN, COLLISION_TYPE_CAR );
            cp.spaceRemoveCollisionHandler( this._space, COLLISION_TYPE_FINISH, COLLISION_TYPE_CAR );
        }
    },


});

//
// Boot Layer
//
var BootLayer = cc.Layer.extend({

    ctor:function () {
                                
        var parent = new cc.Layer();
        __associateObjWithNative(this, parent);
        this.init();

        // music
        audioEngine.playBackgroundMusic("game-music.mp3");
        audioEngine.preloadEffect("pickup_coin.wav");

		var cache = cc.SpriteFrameCache.getInstance();
		cache.addSpriteFrames( "coins.plist" );
    },
    
    onEnter:function() {
        var scene = cc.Scene.create();
        var layer = new MenuLayer();
        scene.addChild( layer );
        director.replaceScene( scene );
    },
});

//
// Main Menu
//
var MenuLayer = cc.Layer.extend({

    ctor:function () {
                                
        var parent = new cc.Layer();
        __associateObjWithNative(this, parent);
        this.init();

        // background
        var node = cc.Reader.load("MainMenu.ccbi", this, winSize);
        this.addChild( node );
        var label = node.getChildByTag( TITLE_TAG );
        var o = label.getChildByTag( 8 );

        var a_delay = cc.DelayTime.create(6);
        var a_tint = cc.TintTo.create( 0.5, 0, 255, 0 );
        var a_rotate = cc.RotateBy.create( 4, 360 );
        var a_rep = cc.Repeat.create( a_rotate, 1000 );
        var a_seq = cc.Sequence.create( a_delay, a_tint, a_delay.copy(), a_rep );
        o.runAction( a_seq );

    },

    onPlay:function( sender) {
        var scene = cc.Scene.create();
        var layer = new GameLayer(0);
        scene.addChild( layer );
        director.replaceScene( cc.TransitionFade.create(1, scene) );
    },

    onOptions:function( sender) {
        var scene = cc.Scene.create();
        var layer = new OptionsLayer();
        scene.addChild( layer );
        director.replaceScene( cc.TransitionFlipY.create(1, scene) );
    },

    onAbout:function( sender ) {
        var scene = cc.Scene.create();
        var layer = new AboutLayer();
        scene.addChild( layer );
        director.replaceScene( cc.TransitionZoomFlipY.create(1, scene) );
    },
});

//
// About
//
var AboutLayer = cc.Layer.extend({

    ctor:function () {
        var parent = new cc.LayerGradient();
        __associateObjWithNative(this, parent);
        this.init();

        var about = cc.Reader.load("About.ccbi", this);
        this.addChild( about )

        var back = cc.MenuItemFont.create("Back", this, this.onBack );
        back.setColor( cc.BLACK );
        var menu = cc.Menu.create( back );
        this.addChild( menu );
        menu.alignItemsVertically();
        menu.setPosition( cc._p( winSize.width - 50, 50) );

    },

    onBack:function( sender) {
        var scene = cc.Scene.create();
        var layer = new MenuLayer();
        scene.addChild( layer );
        director.replaceScene( cc.TransitionFlipX.create(1, scene) );
    },
});

//
// Options 
//
var OptionsLayer = cc.LayerGradient.extend({

    ctor:function () {
        var parent = new cc.LayerGradient();
        __associateObjWithNative(this, parent);
        this.init(cc.c4b(0, 0, 0, 255), cc.c4b(255, 255, 255, 255));

        var label1 = cc.LabelBMFont.create("MUSIC ON", "konqa32.fnt" );
        var item1 = cc.MenuItemLabel.create(label1);
        var label2 = cc.LabelBMFont.create("MUSIC OFF", "konqa32.fnt" );
        var item2 = cc.MenuItemLabel.create(label2);
        var toggle = cc.MenuItemToggle.create( item1, item2 );
        toggle.setCallback( this, this.onMusicToggle);

        var back = cc.MenuItemFont.create("Back", this, this.onBack );
        var menu = cc.Menu.create( toggle, back );
        this.addChild( menu );
        menu.alignItemsVertically();
        menu.setPosition( centerPos );
    },

    onBack:function( sender) {
        var scene = cc.Scene.create();
        var layer = new MenuLayer();
        scene.addChild( layer );
        director.replaceScene( cc.TransitionFlipX.create(1, scene) );
    },

    onMusicToggle:function( sender ) {
        // music
        if ( audioEngine.isBackgroundMusicPlaying() ) {
            audioEngine.stopBackgroundMusic();
        } else {
            audioEngine.playBackgroundMusic("game-music.mp3");
        }
    },
});

//------------------------------------------------------------------
//
// Main entry point
//
//------------------------------------------------------------------
function run()
{
    // update globals
    winSize = director.getWinSize();
    centerPos = cc.p( winSize.width/2, winSize.height/2 );

    var scene = cc.Scene.create();

    // main menu
    var menu = new BootLayer();
    scene.addChild( menu);

    var runningScene = director.getRunningScene();
    if( runningScene == null )
        director.runWithScene( scene );
    else
        director.replaceScene( cc.TransitionFade.create(0.5, scene ) );
}

run();

