 /**
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *
 * Chipmunk Demo code:
 *    Original Demo code written in C by Scott Lembcke
 *    Ported to JavaScript by Joseph Gentle
 *    Additions to the demo code by Ricardo Quesada
 */

//
// JavaScript + chipmunk tests
//

var chipmunkTestSceneIdx = -1;

function k_scalar_body(body, point, n) {
    var rcn = cp.v.cross(cp.v.sub(point, body.p), n);
    return 1.0/body.m + rcn*rcn/body.i;
}

//------------------------------------------------------------------
//
// ChipmunkBaseLayer
//
//------------------------------------------------------------------
var ChipmunkBaseLayer = BaseTestLayer.extend( {
    ctor : function() {
        //
        // VERY IMPORTANT
        //
        // Only subclasses of a native classes MUST call cc.associateWithNative
        // Failure to do so, it will crash.
        //
        this._super( cc.color(0,0,0,255), cc.color(98*0.5,99*0.5,117*0.5,255) );

        this._title =  "No title";
        this._subtitle = "No Subtitle";

        // Menu to toggle debug physics on / off
        var item = new cc.MenuItemFont("Physics On/Off", this.onToggleDebug, this);
        item.fontSize = 24;
        var menu = new cc.Menu( item );
        this.addChild( menu );
        menu.x = winSize.width-100;
        menu.y = winSize.height-90;

        // Create the initial space
        this.space = new cp.Space();

        this.setupDebugNode();
    },

    setupDebugNode : function()
    {
        // debug only
        this._debugNode = new cc.PhysicsDebugNode(this.space );
        this._debugNode.visible = false ;
        this.addChild( this._debugNode );
    },

    onToggleDebug : function(sender) {
        var state = this._debugNode.visible;
        this._debugNode.visible = !state ;
    },

    onEnter : function() {
        BaseTestLayer.prototype.onEnter.call(this);
        //cc.base(this, 'onEnter');

        cc.sys.dumpRoot();
        cc.sys.garbageCollect();
    },

    onCleanup : function() {
        // Not compulsory, but recommended: cleanup the scene
        this.unscheduleUpdate();
    },

    onRestartCallback : function (sender) {
        this.onCleanup();
        var s = new ChipmunkTestScene();
        s.addChild(restartChipmunkTest());
        director.runScene(s);
    },

    onNextCallback : function (sender) {
        this.onCleanup();
        var s = new ChipmunkTestScene();
        s.addChild(nextChipmunkTest());
        director.runScene(s);
    },

    onBackCallback : function (sender) {
        this.onCleanup();
        var s = new ChipmunkTestScene();
        s.addChild(previousChipmunkTest());
        director.runScene(s);
    },

    numberOfPendingTests : function() {
        return ( (arrayOfChipmunkTest.length-1) - chipmunkTestSceneIdx );
    },

    getTestNumber : function() {
        return chipmunkTestSceneIdx;
    }
});

//------------------------------------------------------------------
//
// Chipmunk + Sprite
//
//------------------------------------------------------------------
var ChipmunkSprite = ChipmunkBaseLayer.extend( {

    ctor: function() {
        this._super();
        //cc.base(this);

        this.addSprite = function( pos ) {
            var sprite =  this.createPhysicsSprite( pos );
            var child = new cc.Sprite(s_pathSister1);
            child.attr({
                scale: 0.4,
                anchorX: 0,
                anchorY: 0,
                x: sprite.width/2,
                y: sprite.height/2
            });
            sprite.addChild(child);
            this.addChild( sprite );
        };

        this._title = 'Chipmunk Sprite Test';
        this._subtitle = 'Chipmunk + cocos2d sprites tests. Tap screen.';

        this.initPhysics();
    },

    title : function(){
        return 'Chipmunk Sprite Test';
    },

    initPhysics : function() {
        var space = this.space ;
        var staticBody = space.staticBody;

        // Walls
        var walls = [ new cp.SegmentShape( staticBody, cp.v(0,0), cp.v(winSize.width,0), 0 ),               // bottom
            new cp.SegmentShape( staticBody, cp.v(0,winSize.height), cp.v(winSize.width,winSize.height), 0),    // top
            new cp.SegmentShape( staticBody, cp.v(0,0), cp.v(0,winSize.height), 0),             // left
            new cp.SegmentShape( staticBody, cp.v(winSize.width,0), cp.v(winSize.width,winSize.height), 0)  // right
        ];
        for( var i=0; i < walls.length; i++ ) {
            var shape = walls[i];
            shape.setElasticity(1);
            shape.setFriction(1);
            space.addStaticShape( shape );
        }

        // Gravity
        space.gravity = cp.v(0, -100);
    },

    createPhysicsSprite : function( pos ) {
        var body = new cp.Body(1, cp.momentForBox(1, 48, 108) );
        body.setPos( pos );
        this.space.addBody( body );
        var shape = new cp.BoxShape( body, 48, 108);
        shape.setElasticity( 0.5 );
        shape.setFriction( 0.5 );
        this.space.addShape( shape );

        var sprite = new cc.PhysicsSprite(s_pathGrossini);
        sprite.setBody( body );
        return sprite;
    },

    onEnter : function () {
        ChipmunkBaseLayer.prototype.onEnter.call(this);
        //cc.base(this, 'onEnter');

        this.scheduleUpdate();
        for(var i=0; i<10; i++) {
            var variancex = cc.randomMinus1To1() * 5;
            var variancey = cc.randomMinus1To1() * 5;
            this.addSprite( cp.v(winSize.width/2 + variancex, winSize.height/2 + variancey) );
        }

        if( 'touches' in cc.sys.capabilities ){
            cc.eventManager.addListener({
                event: cc.EventListener.TOUCH_ALL_AT_ONCE,
                onTouchesEnded: function(touches, event){
                    var l = touches.length, target = event.getCurrentTarget();
                    for( var i=0; i < l; i++) {
                        target.addSprite( touches[i].getLocation() );
                    }
                }
            }, this);
        } else if( 'mouse' in cc.sys.capabilities )
            cc.eventManager.addListener({
                event: cc.EventListener.MOUSE,
                onMouseDown: function(event){
                    event.getCurrentTarget().addSprite(event.getLocation());
                }
            }, this);
    },

    update : function( delta ) {
        this.space.step( delta );
    }
});

//------------------------------------------------------------------
//
// Chipmunk + Sprite + Batch
//
//------------------------------------------------------------------
var ChipmunkSpriteBatchTest = ChipmunkSprite.extend( {
    ctor : function () {
        this._super();
        // cc.base(this);

        // batch node
        this.batch = new cc.SpriteBatchNode(s_pathGrossini, 50 );
        this.addChild( this.batch );

        this.addSprite = function( pos ) {
            var sprite =  this.createPhysicsSprite( pos );
            var child = new cc.Sprite(s_pathGrossini);
            child.attr({
                scale: 0.4,
                anchorX: 0,
                anchorY: 0,
                x: sprite.width/2,
                y: sprite.height/2
            });
            sprite.addChild(child);
            this.batch.addChild( sprite );
        };

        this._title = 'Chipmunk SpriteBatch Test';
        this._subtitle = 'Chipmunk + cocos2d sprite batch tests. Tap screen.';
    },

    title : function(){
        return 'Chipmunk SpriteBatch Test';
    }
});

 //------------------------------------------------------------------
 //
 // Chipmunk Collision Test
 // Using setDefaultCollisionHandler
 // The default collision handler is invoked for each colliding pair of shapes that isn't explicitly handled by a specific collision handler.
 //
 //------------------------------------------------------------------
var ChipmunkCollisionTest_no_specific_type = ChipmunkBaseLayer.extend({
    ctor : function () {
        this._super();

        this._title = 'Chipmunk Collision test';
        this._subtitle = 'Using setDefaultCollisionHandler';
    },

    // init physics
    initPhysics : function() {
        var staticBody = this.space.staticBody;

        // Walls
        var walls = [ new cp.SegmentShape( staticBody, cp.v(0,0), cp.v(winSize.width,0), 0 )               // bottom
            // new cp.SegmentShape( staticBody, cp.v(0,winSize.height), cp.v(winSize.width,winSize.height), 0),    // top
            // new cp.SegmentShape( staticBody, cp.v(0,0), cp.v(0,winSize.height), 0),             // left
            // new cp.SegmentShape( staticBody, cp.v(winSize.width,0), cp.v(winSize.width,winSize.height), 0)  // right
        ];
        for( var i=0; i < walls.length; i++ ) {
            var wall = walls[i];
            wall.setElasticity(1);
            wall.setFriction(1);
            this.space.addStaticShape( wall );
        }

        // Gravity:
        // testing properties
        this.space.gravity = cp.v(0,-100);
        this.space.iterations = 15;
    },

    createPhysicsSprite : function( pos, file ) {
        var body = new cp.Body(1, cp.momentForBox(1, 48, 108) );
        body.setPos(pos);
        this.space.addBody(body);
        var shape = new cp.BoxShape( body, 48, 108);
        shape.setElasticity( 0.5 );
        shape.setFriction( 0.5 );
        this.space.addShape( shape );

        var sprite = new cc.PhysicsSprite(file);
        sprite.setBody( body );
        return sprite;
    },

    onEnter : function () {
        ChipmunkBaseLayer.prototype.onEnter.call(this);

        this.initPhysics();
        this.scheduleUpdate();

        var sprite1 = this.createPhysicsSprite( cc.p(winSize.width/2, winSize.height-20), s_pathGrossini);
        this.addChild( sprite1 );

        this.space.setDefaultCollisionHandler(
            this.collisionBegin.bind(this),
            this.collisionPre.bind(this),
            this.collisionPost.bind(this),
            this.collisionSeparate.bind(this)
        );
    },

    onExit : function() {
        ChipmunkBaseLayer.prototype.onExit.call(this);
    },

    update : function( delta ) {
        this.space.step( delta );
    },

    collisionBegin : function ( arbiter, space ) {
        cc.log('collision begin');
        return true;
    },

    collisionPre : function ( arbiter, space ) {
        cc.log('collision pre');
        return true;
    },

    collisionPost : function ( arbiter, space ) {
        cc.log('collision post');
    },

    collisionSeparate : function ( arbiter, space ) {
        cc.log('collision separate');
    }
});
//------------------------------------------------------------------
//
// Chipmunk Collision Test
// Using Object Oriented API.
// Base your samples on the "Object Oriented" API.
//
//------------------------------------------------------------------
var ChipmunkCollisionTest = ChipmunkBaseLayer.extend( {

    ctor : function () {
        this._super();
        // cc.base(this);

        this._title = 'Chipmunk Collision test';
        this._subtitle = 'Using Object Oriented API. ** Use this API **';
    },

    // init physics
    initPhysics : function() {
        var staticBody = this.space.staticBody;

        // Walls
        var walls = [ new cp.SegmentShape( staticBody, cp.v(0,0), cp.v(winSize.width,0), 0 ),               // bottom
                new cp.SegmentShape( staticBody, cp.v(0,winSize.height), cp.v(winSize.width,winSize.height), 0),    // top
                new cp.SegmentShape( staticBody, cp.v(0,0), cp.v(0,winSize.height), 0),             // left
                new cp.SegmentShape( staticBody, cp.v(winSize.width,0), cp.v(winSize.width,winSize.height), 0)  // right
                ];
        for( var i=0; i < walls.length; i++ ) {
            var wall = walls[i];
            wall.setElasticity(1);
            wall.setFriction(1);
            this.space.addStaticShape( wall );
        }

        // Gravity:
        // testing properties
        this.space.gravity = cp.v(0,-100);
        this.space.iterations = 15;
    },

    createPhysicsSprite : function( pos, file, collision_type ) {
        var body = new cp.Body(1, cp.momentForBox(1, 48, 108) );
        body.setPos(pos);
        this.space.addBody(body);
        var shape = new cp.BoxShape( body, 48, 108);
        shape.setElasticity( 0.5 );
        shape.setFriction( 0.5 );
        shape.setCollisionType( collision_type );
        this.space.addShape( shape );

        var sprite = new cc.PhysicsSprite(file);
        sprite.setBody( body );
        return sprite;
    },

    onEnter : function () {
        ChipmunkBaseLayer.prototype.onEnter.call(this);
        // cc.base(this, 'onEnter');

        this.initPhysics();
        this.scheduleUpdate();

        var sprite1 = this.createPhysicsSprite( cc.p(winSize.width/2, winSize.height-20), s_pathGrossini, 1);
        var sprite2 = this.createPhysicsSprite( cc.p(winSize.width/2, 50), s_pathSister1, 2);

        this.addChild( sprite1 );
        this.addChild( sprite2 );

        this.space.addCollisionHandler( 1, 2,
            this.collisionBegin.bind(this),
            this.collisionPre.bind(this),
            this.collisionPost.bind(this),
            this.collisionSeparate.bind(this)
            );
    },

    onExit : function() {
        this.space.removeCollisionHandler( 1, 2 );
        ChipmunkBaseLayer.prototype.onExit.call(this);
    },

    update : function( delta ) {
        this.space.step( delta );
    },

    collisionBegin : function ( arbiter, space ) {

        if( ! this.messageDisplayed ) {
            var label = new cc.LabelBMFont("Collision Detected", s_bitmapFontTest5_fnt);
            this.addChild( label );
            label.x = winSize.width/2;
            label.y = winSize.height/2 ;
            this.messageDisplayed = true;
        }
        cc.log('collision begin');
        var shapes = arbiter.getShapes();
        var collTypeA = shapes[0].collision_type;
        var collTypeB = shapes[1].collision_type;
        cc.log( 'Collision Type A:' + collTypeA );
        cc.log( 'Collision Type B:' + collTypeB );

        //test addPostStepCallback
        space.addPostStepCallback(function(){
            cc.log("post step callback 1");
        });
        space.addPostStepCallback(function(){
            cc.log("post step callback 2");
        });
        return true;
    },

    collisionPre : function ( arbiter, space ) {
        cc.log('collision pre');
        cc.log("arbiter e : " + arbiter.e);
        cc.log("arbiter u : " +arbiter.u);
        cc.log("arbiter surface_vr : " + arbiter.surface_vr.x + "," + arbiter.surface_vr.y);
        return true;
    },

    collisionPost : function ( arbiter, space ) {
        cc.log('collision post');
    },

    collisionSeparate : function ( arbiter, space ) {
        cc.log('collision separate');
    },

    title : function(){
        return 'Chipmunk Collision test';
    }
});


//------------------------------------------------------------------
//
// Chipmunk Collision Test
// Using "C" API.
// XXX  DO NOT USE THE "C" API.
// XXX  IT WAS ADDED FOR TESTING PURPOSES ONLY
//
//------------------------------------------------------------------
var ChipmunkCollisionTestB = ChipmunkBaseLayer.extend( {

    ctor: function () {
        this._super();
        // cc.base(this);

        this.messageDisplayed = false;

        this._title = 'Chipmunk Collision Test';
        this._subtitle = 'using "C"-like API. ** DO NOT USE THIS API **';
    },

    // init physics
    initPhysics : function() {
        this.space =  cp.spaceNew();

        // update Physics Debug Node with new space
        this._debugNode.setSpace(this.space);

        var staticBody = cp.spaceGetStaticBody( this.space );

        // Walls using "C" API. DO NO USE THIS API
        var walls = [cp.segmentShapeNew( staticBody, cp.v(0,0), cp.v(winSize.width,0), 0 ),             // bottom
                cp.segmentShapeNew( staticBody, cp.v(0,winSize.height), cp.v(winSize.width,winSize.height), 0), // top
                cp.segmentShapeNew( staticBody, cp.v(0,0), cp.v(0,winSize.height), 0),              // left
                cp.segmentShapeNew( staticBody, cp.v(winSize.width,0), cp.v(winSize.width,winSize.height), 0)   // right
                ];

        for( var i=0; i < walls.length; i++ ) {
            // 'properties' using "C" API. DO NO USE THIS API
            var wall = walls[i];
            cp.shapeSetElasticity(wall, 1);
            cp.shapeSetFriction(wall, 1);
            cp.spaceAddShape(this.space, wall);
        }

        // Gravity
        cp.spaceSetGravity( this.space, cp.v(0, -30) );
    },

    createPhysicsSprite : function( pos, file, collision_type ) {
        // using "C" API. DO NO USE THIS API
        var body = cp.bodyNew(1, cp.momentForBox(1, 48, 108) );
        cp.bodySetPosition( body, pos );
        cp.spaceAddBody( this.space, body );
        // chipmunk v7.0 uses an extra argument
        var shape = cp.boxShapeNew( body, 48, 108, 0);
        cp.shapeSetElasticity( shape, 0.5 );
        cp.shapeSetFriction( shape, 0.5 );
        cp.shapeSetCollisionType( shape, collision_type );
        cp.spaceAddShape( this.space, shape );

        var sprite = new cc.PhysicsSprite(file);
        sprite.setBody( body );
        return sprite;
    },

    onEnter : function () {
        ChipmunkBaseLayer.prototype.onEnter.call(this);
        // cc.base(this, 'onEnter');

        this.initPhysics();
        this.scheduleUpdate();

        var sprite1 = this.createPhysicsSprite( cc.p(winSize.width/2, winSize.height-20), s_pathGrossini, 1);
        var sprite2 = this.createPhysicsSprite( cc.p(winSize.width/2, 50), s_pathSister1, 2);

        this.addChild( sprite1 );
        this.addChild( sprite2 );

        cp.spaceAddCollisionHandler( this.space, 1, 2,
            this.collisionBegin.bind(this),
            this.collisionPre.bind(this),
            this.collisionPost.bind(this),
            this.collisionSeparate.bind(this) );
    },

    onExit : function() {
        cp.spaceRemoveCollisionHandler( this.space, 1, 2 );
        cp.spaceFree( this.space );
        ChipmunkBaseLayer.prototype.onExit.call(this);
    },

    update : function( delta ) {
        cp.spaceStep( this.space, delta );
    },

    collisionBegin : function ( arbiter, space ) {

        if( ! this.messageDisplayed ) {
            var label = new cc.LabelBMFont("Collision Detected", s_bitmapFontTest5_fnt);
            this.addChild( label );
            label.x = winSize.width/2;
            label.y = winSize.height/2 ;
            this.messageDisplayed = true;
        }
        cc.log('collision begin');
        var bodies = cp.arbiterGetBodies( arbiter );
        var shapes = cp.arbiterGetShapes( arbiter );
        var collTypeA = cp.shapeGetCollisionType( shapes[0] );
        var collTypeB = cp.shapeGetCollisionType( shapes[1] );
        cc.log( 'Collision Type A:' + collTypeA );
        cc.log( 'Collision Type B:' + collTypeB );
        return true;
    },

    collisionPre : function ( arbiter, space ) {
        cc.log('collision pre');
        return true;
    },

    collisionPost : function ( arbiter, space ) {
        cc.log('collision post');
    },

    collisionSeparate : function ( arbiter, space ) {
        cc.log('collision separate');
    }
});


//------------------------------------------------------------------
//
// Chipmunk Collision Memory Leak Test
//
//------------------------------------------------------------------
var ChipmunkCollisionMemoryLeakTest = ChipmunkBaseLayer.extend({

    ctor : function() {
        this._super();
        // cc.base(this);

        this._title = 'Chipmunk Memory Leak Test';
        this._subtitle = 'Testing possible memory leak on the collision handler. No visual feedback';
    },

    collisionBegin : function ( arbiter, space ) {
        return true;
    },

    collisionPre : function ( arbiter, space ) {
        return true;
    },

    collisionPost : function ( arbiter, space ) {
        cc.log('collision post');
    },

    collisionSeparate : function ( arbiter, space ) {
        cc.log('collision separate');
    },

    onEnter : function() {
        ChipmunkBaseLayer.prototype.onEnter.call(this);
        // cc.base(this, 'onEnter');

        for( var i=1 ; i < 100 ; i++ )
            this.space.addCollisionHandler( i, i+1,
                this.collisionBegin.bind(this),
                this.collisionPre.bind(this),
                this.collisionPost.bind(this),
                this.collisionSeparate.bind(this)
                );

    },

    onExit : function() {
        ChipmunkBaseLayer.prototype.onExit.call(this);

        for( var i=1 ; i < 100 ; i++ )
            this.space.removeCollisionHandler( i, i+1 );
    },

    title : function(){
        return 'Chipmunk Memory Leak Test';
    }
});

//------------------------------------------------------------------
//
// Test Anchor Point with PhysicsSprite
//
//------------------------------------------------------------------
var ChipmunkSpriteAnchorPoint = ChipmunkBaseLayer.extend({

    ctor : function() {
        this._super();
        // cc.base(this);

        this._title = 'AnchorPoint in PhysicsSprite';
        this._subtitle = 'Tests AnchorPoint in PhysicsSprite. See animated sprites';
    },

    onEnter : function() {
        ChipmunkBaseLayer.prototype.onEnter.call(this);
        // cc.base(this, 'onEnter');

        this._debugNode.visible = true ;

        this.space.gravity = v(0, 0);

        var sprite1 = this.createPhysicsSprite( cp.v(winSize.width/4*1, winSize.height/2) );
        var sprite2 = this.createPhysicsSprite( cp.v(winSize.width/4*2, winSize.height/2) );
        var sprite3 = this.createPhysicsSprite( cp.v(winSize.width/4*3, winSize.height/2) );

        sprite1.anchorX = 0;
        sprite1.anchorY = 0;
        sprite2.anchorX = 0.5;
        sprite2.anchorY = 0.5;
        sprite3.anchorX = 1;
        sprite3.anchorY = 1;

        // scale sprite
        var scaledown = cc.scaleBy(0.5, 0.5);
        var scaleup = scaledown.reverse();
        var seq = cc.sequence( scaledown, scaleup);
        var repeat = seq.repeatForever();

        sprite1.runAction( repeat );
        sprite2.runAction( repeat.clone() );
        sprite3.runAction( repeat.clone() );

        this.addChild(sprite1);
        this.addChild(sprite2);
        this.addChild(sprite3);

        this.scheduleUpdate();
    },

    title : function(){
        return 'AnchorPoint in PhysicsSprite';
    },

    createPhysicsSprite : function(pos) {

        // create body
        var body = new cp.Body(1, cp.momentForBox(1, 48, 108) );
        body.setPos( pos );
        this.space.addBody( body );

        // create shape
        var shape = new cp.BoxShape( body, 48, 108);
        shape.setElasticity( 0.5 );
        shape.setFriction( 0.5 );
        this.space.addShape( shape );

        // create sprite
        var sprite = new cc.PhysicsSprite(s_pathGrossini);

        // associate sprite with body
        sprite.setBody( body );

        return sprite;
    },

    update : function(dt) {
        var steps = 1;
        dt /= steps;
        for (var i = 0; i < steps; i++){
            this.space.step(dt);
        }
    }
});


//------------------------------------------------------------------
//
// ChipmunkReleaseTest
//
//------------------------------------------------------------------
var ChipmunkReleaseTest = ChipmunkBaseLayer.extend({

    ctor : function () {
        this._super();
        // cc.base(this);

        this._title = 'Chipmunk Release Test';
        this._subtitle = 'Space finalizer should be called';
    },

    collisionBegin : function ( arbiter, space ) {
        return true;
    },

    collisionPre : function ( arbiter, space ) {
        return true;
    },

    collisionPost : function ( arbiter, space ) {
        cc.log('collision post');
    },

    collisionSeparate : function ( arbiter, space ) {
        cc.log('collision separate');
    },

    onEnter : function() {
        ChipmunkBaseLayer.prototype.onEnter.call(this);
        // cc.base(this, 'onEnter');

        cc.log("OnEnter");
        cc.sys.dumpRoot();
        cc.sys.garbageCollect();

        this.space.addCollisionHandler( 10,11,
            this.collisionBegin.bind(this),
            this.collisionPre.bind(this),
            this.collisionPost.bind(this),
            this.collisionSeparate.bind(this)
            );

    },

    onExit : function() {

        cc.log("OnExit");

        // not calling this on purpose
        // this.space.removeCollisionHandler( 10, 11 );

        this.space = null;

        cc.sys.dumpRoot();
        cc.sys.garbageCollect();

        // cc.base(this, 'onExit');
        ChipmunkBaseLayer.prototype.onExit.call(this);
    }
});

//
// Base class for Chipmunk Demo
//
// Chipmunk Demos from Chipmunk-JS project
// https://github.com/josephg/chipmunk-js
//

var v = cp.v;
var ctx;
var GRABABLE_MASK_BIT = 1<<31;
var NOT_GRABABLE_MASK = ~GRABABLE_MASK_BIT;

var ChipmunkDemo = ChipmunkBaseLayer.extend( {
    ctor : function () {
        this._super();
        //cc.base(this);

        this.remainder = 0;

        // debug only
        this._debugNode.visible = true ;

        this.scheduleUpdate();
    },

    update : function(dt) {
        this.space.step(dt);
    },

    addFloor : function() {
        var space = this.space;
        var floor = space.addShape(new cp.SegmentShape(space.staticBody, v(0, 0), v(640, 0), 0));
        floor.setElasticity(1);
        floor.setFriction(1);
        floor.setLayers(NOT_GRABABLE_MASK);
    },

    addWalls : function() {
        var space = this.space;
        var wall1 = space.addShape(new cp.SegmentShape(space.staticBody, v(0, 0), v(0, 480), 0));
        wall1.setElasticity(1);
        wall1.setFriction(1);
        wall1.setLayers(NOT_GRABABLE_MASK);

        var wall2 = space.addShape(new cp.SegmentShape(space.staticBody, v(640, 0), v(640, 480), 0));
        wall2.setElasticity(1);
        wall2.setFriction(1);
        wall2.setLayers(NOT_GRABABLE_MASK);
    }
});

//------------------------------------------------------------------
//
// Chipmunk Demo: Pyramid Stack
//
//------------------------------------------------------------------
var PyramidStack = ChipmunkDemo.extend( {

    ctor : function () {
        this._super();
        // cc.base(this);
        this._subtitle = 'Chipmunk Demo';
        this._title = 'Pyramid Stack';

        var space = this.space;
        //space.iterations = 30;
        space.gravity = v(0, -100);
        space.sleepTimeThreshold = 0.5;
        space.collisionSlop = 0.5;

        var body, staticBody = space.staticBody;
        var shape;

        this.addFloor();
        this.addWalls();

        // Add lots of boxes.
        for(var i=0; i<14; i++){
            for(var j=0; j<=i; j++){
                body = space.addBody(new cp.Body(1, cp.momentForBox(1, 30, 30)));
                body.setPos(v(j*32 - i*16 + 320, 540 - i*32));

                shape = space.addShape(new cp.BoxShape(body, 30, 30));
                shape.setElasticity(0);
                shape.setFriction(0.8);
            }
        }

        // Add a ball to make things more interesting
        var radius = 15;
        body = space.addBody(new cp.Body(10, cp.momentForCircle(10, 0, radius, v(0,0))));
        body.setPos(v(320, radius+5));

        shape = space.addShape(new cp.CircleShape(body, radius, v(0,0)));
        shape.setElasticity(0);
        shape.setFriction(0.9);
    },

    title : function(){
        return 'Pyramid Stack';
    }
});

//------------------------------------------------------------------
//
// Chipmunk Demo: Pyramid Topple
//
//------------------------------------------------------------------
var PyramidTopple = ChipmunkDemo.extend( {

    ctor : function() {
        this._super();
        // cc.base(this);
        this._subtitle = 'Chipmunk Demo';
        this._title = 'Pyramid Topple';

        var WIDTH = 4;
        var HEIGHT = 30;

        var space = this.space;

        var add_domino = function(pos, flipped)
        {
            var mass = 1;
            var moment = cp.momentForBox(mass, WIDTH, HEIGHT);

            var body = space.addBody(new cp.Body(mass, moment));
            body.setPos(pos);

            var shape = (flipped ? new cp.BoxShape(body, HEIGHT, WIDTH) : new cp.BoxShape(body, WIDTH, HEIGHT));
            space.addShape(shape);
            shape.setElasticity(0);
            shape.setFriction(0.6);
        };

        space.iterations = 30;
        space.gravity = v(0, -300);
        space.sleepTimeThreshold = 0.5;
        space.collisionSlop = 0.5;

        this.addFloor();

        // Add the dominoes.
        var n = 12;
        for(var i=0; i<n; i++){
            for(var j=0; j<(n - i); j++){
                var offset = v(320 + (j - (n - 1 - i)*0.5)*1.5*HEIGHT, (i + 0.5)*(HEIGHT + 2*WIDTH) - WIDTH);
                add_domino(offset, false);
                add_domino(cp.v.add(offset, v(0, (HEIGHT + WIDTH)/2)), true);

                if(j === 0){
                    add_domino(cp.v.add(offset, v(0.5*(WIDTH - HEIGHT), HEIGHT + WIDTH)), false);
                }

                if(j != n - i - 1){
                    add_domino(cp.v.add(offset, v(HEIGHT*0.75, (HEIGHT + 3*WIDTH)/2)), true);
                } else {
                    add_domino(cp.v.add(offset, v(0.5*(HEIGHT - WIDTH), HEIGHT + WIDTH)), false);
                }
            }
        }
    },

    update : function(dt)
    {
        var steps = 3;
        dt /= steps;
        for (var i = 0; i < 3; i++){
            this.space.step(dt);
        }
    },

    title : function(){
        return 'Pyramid Topple';
    }
});

//------------------------------------------------------------------
//
// Chipmunk Demo: Joints
//
//------------------------------------------------------------------
var Joints = ChipmunkDemo.extend({
    ctor : function() {
        this._super();
        // cc.base(this);
        this._subtitle = 'Chipmunk Demo';
        this._title = 'Joints';

        var space = this.space;
        var boxOffset;

        var addBall = function(pos)
        {
            var radius = 15;
            var mass = 1;
            var body = space.addBody(new cp.Body(mass, cp.momentForCircle(mass, 0, radius, v(0,0))));
            body.setPos(cp.v.add(pos, boxOffset));

            var shape = space.addShape(new cp.CircleShape(body, radius, v(0,0)));
            shape.setElasticity(0);
            shape.setFriction(0.7);

            return body;
        };

        var addLever = function(pos)
        {
            var mass = 1;
            var a = v(0,  15);
            var b = v(0, -15);

            var body = space.addBody(new cp.Body(mass, cp.momentForSegment(mass, a, b)));
            body.setPos(cp.v.add(pos, cp.v.add(boxOffset, cp.v(0, -15))));

            var shape = space.addShape(new cp.SegmentShape(body, a, b, 5));
            shape.setElasticity(0);
            shape.setFriction(0.7);

            return body;
        };

        var addBar = function(pos)
        {
            var mass = 2;
            var a = v(0,  30);
            var b = v(0, -30);

            var body = space.addBody(new cp.Body(mass, cp.momentForSegment(mass, a, b)));
            body.setPos(cp.v.add(pos, boxOffset));

            var shape = space.addShape(new cp.SegmentShape(body, a, b, 5));
            shape.setElasticity(0);
            shape.setFriction(0.7);

            return body;
        };

        var addWheel = function(pos)
        {
            var radius = 15;
            var mass = 1;
            var body = space.addBody(new cp.Body(mass, cp.momentForCircle(mass, 0, radius, v(0,0))));
            body.setPos(cp.v.add(pos, boxOffset));

            var shape = space.addShape(new cp.CircleShape(body, radius, v(0,0)));
            shape.setElasticity(0);
            shape.setFriction(0.7);
            shape.group = 1; // use a group to keep the car parts from colliding

            return body;
        };

        var addChassis = function(pos)
        {
            var mass = 5;
            var width = 80;
            var height = 30;

            var body = space.addBody(new cp.Body(mass, cp.momentForBox(mass, width, height)));
            body.setPos(cp.v.add(pos, boxOffset));

            var shape = space.addShape(new cp.BoxShape(body, width, height));
            shape.setElasticity(0);
            shape.setFriction(0.7);
            shape.group = 1; // use a group to keep the car parts from colliding

            return body;
        };

        space.iterations = 10;
        space.gravity = v(0, -100);
        space.sleepTimeThreshold = 0.5;

        var staticBody = space.staticBody;
        var shape;

        for(var y = 480; y >= 0; y -= 120) {
            shape = space.addShape(new cp.SegmentShape(staticBody, v(0,y), v(640,y), 0));
            shape.setElasticity(1);
            shape.setFriction(1);
            shape.layers = NOT_GRABABLE_MASK;
        }

        for(var x = 0; x <= 640; x += 160) {
            shape = space.addShape(new cp.SegmentShape(staticBody, v(x,0), v(x,480), 0));
            shape.setElasticity(1);
            shape.setFriction(1);
            shape.layers = NOT_GRABABLE_MASK;
        }

        var body1, body2;

        var posA = v( 50, 60);
        var posB = v(110, 60);

        var POS_A = function() { return cp.v.add(boxOffset, posA); };
        var POS_B = function() { return cp.v.add(boxOffset, posB); };
        //#define POS_A vadd(boxOffset, posA)
        //#define POS_B vadd(boxOffset, posB)

        this.labels = labels = [];
        var label = function(text) {
            labels.push({text:text, pos:boxOffset});
        };

        // Pin Joints - Link shapes with a solid bar or pin.
        // Keeps the anchor points the same distance apart from when the joint was created.
        boxOffset = v(0, 0);
        label('Pin Joint');
        body1 = addBall(posA);
        body2 = addBall(posB);
        body2.setAngle(Math.PI);
        var pinJoint = new cp.PinJoint(body1, body2, v(15,0), v(15,0));
        space.addConstraint(pinJoint);
        cc.log("pin joint anchr1 : " + pinJoint.anchr1.x + "," + pinJoint.anchr1.y);
        cc.log("pin joint anchr2 : " + pinJoint.anchr2.x + "," + pinJoint.anchr2.y);
        cc.log("pin joint dist : " + pinJoint.dist);

        // Slide Joints - Like pin joints but with a min/max distance.
        // Can be used for a cheap approximation of a rope.
        boxOffset = v(160, 0);
        label('Slide Joint');
        body1 = addBall(posA);
        body2 = addBall(posB);
        body2.setAngle(Math.PI);
        var slideJoint = new cp.SlideJoint(body1, body2, v(15,0), v(15,0), 20, 40);
        space.addConstraint(slideJoint);
        cc.log("slide joint anchr1 : " + slideJoint.anchr1.x + "," + slideJoint.anchr1.y);
        cc.log("slide joint anchr2 : " + slideJoint.anchr2.x + "," + slideJoint.anchr2.y);
        cc.log("slide joint min : " + slideJoint.min);
        cc.log("slide joint max : " + slideJoint.max);

        // Pivot Joints - Holds the two anchor points together. Like a swivel.
        boxOffset = v(320, 0);
        label('Pivot Joint');
        body1 = addBall(posA);
        body2 = addBall(posB);
        body2.setAngle(Math.PI);
        // cp.PivotJoint(a, b, v) takes it's anchor parameter in world coordinates. The anchors are calculated from that
        // Alternately, specify two anchor points using cp.PivotJoint(a, b, anch1, anch2)
        var pivotJoint = new cp.PivotJoint(body1, body2, cp.v.add(boxOffset, v(80,60)));
        space.addConstraint(pivotJoint);
        cc.log("pivot joint anchr1 : " + pivotJoint.anchr1.x + "," + pivotJoint.anchr1.y);
        cc.log("pivot joint anchr2 : " + pivotJoint.anchr2.x + "," + pivotJoint.anchr2.y);

        // Groove Joints - Like a pivot joint, but one of the anchors is a line segment that the pivot can slide in
        boxOffset = v(480, 0);
        label('Groove Joint');
        body1 = addBall(posA);
        body2 = addBall(posB);
        var grooveJoint = new cp.GrooveJoint(body1, body2, v(30,30), v(30,-30), v(-30,0));
        space.addConstraint(grooveJoint);
        cc.log("groove joint anchr2 : " + grooveJoint.anchr2.x + "," + grooveJoint.anchr2.y);
        cc.log("groove joint grv_a : " +grooveJoint.grv_a.x + "," + grooveJoint.grv_a.y);
        cc.log("groove joint grv_b : " +grooveJoint.grv_b.x + "," + grooveJoint.grv_b.y);

        // Damped Springs
        boxOffset = v(0, 120);
        label('Damped Spring');
        body1 = addBall(posA);
        body2 = addBall(posB);
        body2.setAngle(Math.PI);
        var dampedSpring = new cp.DampedSpring(body1, body2, v(15,0), v(15,0), 20, 5, 0.3);
        space.addConstraint(dampedSpring);
        cc.log("damped spring anchr1 : " + dampedSpring.anchr1.x + "," + dampedSpring.anchr1.y);
        cc.log("damped spring anchr2 : " + dampedSpring.anchr2.x + "," + dampedSpring.anchr2.y);
        cc.log("damped spring damping : " + dampedSpring.damping);
        cc.log("damped spring restLength : " + dampedSpring.restLength);
        cc.log("damped spring stiffness : " + dampedSpring.stiffness);

        // Damped Rotary Springs
        boxOffset = v(160, 120);
        label('Damped Rotary Spring');
        body1 = addBar(posA);
        body2 = addBar(posB);
        // Add some pin joints to hold the circles in place.
        space.addConstraint(new cp.PivotJoint(body1, staticBody, POS_A()));
        space.addConstraint(new cp.PivotJoint(body2, staticBody, POS_B()));
        var dampedRotarySpring = new cp.DampedRotarySpring(body1, body2, 0, 3000, 60);
        space.addConstraint(dampedRotarySpring);
        cc.log("damped rotary spring restAngle : " + dampedRotarySpring.restAngle);
        cc.log("damped rotary spring stiffness : " + dampedRotarySpring.stiffness);
        cc.log("damped rotary spring damping : " + dampedRotarySpring.damping);

        // Rotary Limit Joint
        boxOffset = v(320, 120);
        label('Rotary Limit Joint');
        body1 = addLever(posA);
        body2 = addLever(posB);
        // Add some pin joints to hold the circles in place.
        space.addConstraint(new cp.PivotJoint(body1, staticBody, POS_A()));
        space.addConstraint(new cp.PivotJoint(body2, staticBody, POS_B()));
        // Hold their rotation within 90 degrees of each other.
        var rotaryLimitJoint = new cp.RotaryLimitJoint(body1, body2, -Math.PI/2, Math.PI/2);
        space.addConstraint(rotaryLimitJoint);
        cc.log("rotary limit joint min : " + rotaryLimitJoint.min);
        cc.log("rotary limit joint max : " + rotaryLimitJoint.max);

        // Ratchet Joint - A rotary ratchet, like a socket wrench
        boxOffset = v(480, 120);
        label('Ratchet Joint');
        body1 = addLever(posA);
        body2 = addLever(posB);
        // Add some pin joints to hold the circles in place.
        space.addConstraint(new cp.PivotJoint(body1, staticBody, POS_A()));
        space.addConstraint(new cp.PivotJoint(body2, staticBody, POS_B()));
        // Ratchet every 90 degrees
        var ratchet = new cp.RatchetJoint(body1, body2, 0, Math.PI/2);
        space.addConstraint(ratchet);
        cc.log("ratchet phase : " + ratchet.phase);
        cc.log("ratchet ratchet : " + ratchet.ratchet);
        cc.log("ratchet angle : " + ratchet.angle);

        // Gear Joint - Maintain a specific angular velocity ratio
        boxOffset = v(0, 240);
        label('Gear Joint');
        body1 = addBar(posA);
        body2 = addBar(posB);
        // Add some pin joints to hold the circles in place.
        space.addConstraint(new cp.PivotJoint(body1, staticBody, POS_A()));
        space.addConstraint(new cp.PivotJoint(body2, staticBody, POS_B()));
        // Force one to sping 2x as fast as the other
        var gearJoint = new cp.GearJoint(body1, body2, 0, 2);
        space.addConstraint(gearJoint);
        cc.log("gear joint phase : " + gearJoint.phase);
        cc.log("gear jonit ratio : " + gearJoint.ratio);

        // Simple Motor - Maintain a specific angular relative velocity
        boxOffset = v(160, 240);
        label('Simple Motor');
        body1 = addBar(posA);
        body2 = addBar(posB);
        // Add some pin joints to hold the circles in place.
        space.addConstraint(new cp.PivotJoint(body1, staticBody, POS_A()));
        space.addConstraint(new cp.PivotJoint(body2, staticBody, POS_B()));
        // Make them spin at 1/2 revolution per second in relation to each other.
        var simpleMotor = new cp.SimpleMotor(body1, body2, Math.PI);
        space.addConstraint(simpleMotor);
        cc.log("simple motor rate : " + simpleMotor.rate);

        // Make a car with some nice soft suspension
        boxOffset = v(320, 240);
        var wheel1 = addWheel(posA);
        var wheel2 = addWheel(posB);
        var chassis = addChassis(v(80, 100));

        space.addConstraint(new cp.GrooveJoint(chassis, wheel1, v(-30, -10), v(-30, -40), v(0,0)));
        space.addConstraint(new cp.GrooveJoint(chassis, wheel2, v( 30, -10), v( 30, -40), v(0,0)));

        space.addConstraint(new cp.DampedSpring(chassis, wheel1, v(-30, 0), v(0,0), 50, 20, 10));
        space.addConstraint(new cp.DampedSpring(chassis, wheel2, v( 30, 0), v(0,0), 50, 20, 10));
    },

    title : function(){
        return 'Joints';
    }
});

//------------------------------------------------------------------
//
// Chipmunk Demo: Balls
//
//------------------------------------------------------------------
var Balls = ChipmunkDemo.extend({
    ctor: function() {
        this._super();
        // cc.base(this);
        this._subtitle = 'Chipmunk Demo';
        this._title = 'Balls';

        var space = this.space;
        space.iterations = 60;
        space.gravity = v(0, -500);
        space.sleepTimeThreshold = 0.5;
        space.collisionSlop = 0.5;
        space.sleepTimeThreshold = 0.5;

        this.addFloor();
        this.addWalls();

        var width = 50;
        var height = 60;
        var mass = width * height * 1/1000;
        var rock = space.addBody(new cp.Body(mass, cp.momentForBox(mass, width, height)));
        rock.setPos(v(500, 100));
        rock.setAngle(1);
        shape = space.addShape(new cp.BoxShape(rock, width, height));
        shape.setFriction(0.3);
        shape.setElasticity(0.3);

        for (var i = 1; i <= 10; i++) {
            var radius = 20;
            mass = 3;
            var body = space.addBody(new cp.Body(mass, cp.momentForCircle(mass, 0, radius, v(0, 0))));
            body.setPos(v(200 + i, (2 * radius + 5) * i));
            var circle = space.addShape(new cp.CircleShape(body, radius, v(0, 0)));
            circle.setElasticity(0.8);
            circle.setFriction(1);
        }
        /*
         * atom.canvas.onmousedown = function(e) {
         radius = 10;
         mass = 3;
         body = space.addBody(new cp.Body(mass, cp.momentForCircle(mass, 0, radius, v(0, 0))));
         body.setPos(v(e.clientX, e.clientY));
         circle = space.addShape(new cp.CircleShape(body, radius, v(0, 0)));
         circle.setElasticity(0.5);
         return circle.setFriction(1);
         };
         */

        // this.ctx.strokeStyle = "black";

        var ramp = space.addShape(new cp.SegmentShape(space.staticBody, v(100, 100), v(300, 200), 10));
        ramp.setElasticity(1);
        ramp.setFriction(1);
        ramp.setLayers(NOT_GRABABLE_MASK);
    },

    title : function(){
        return 'Balls';
    }
});


//------------------------------------------------------------------
//
// Buoyancy
//
//------------------------------------------------------------------

var FLUID_DENSITY = 0.00014;
var FLUID_DRAG = 2.0;

var Buoyancy = ChipmunkDemo.extend( {
    ctor: function() {
        this._super();
        // cc.base(this);
        this._subtitle = 'Chipmunk Demo';
        this._title = 'Buoyancy';

        var space = this.space;
        space.iterations = 30;
        space.gravity = cp.v(0,-500);
    //  cpSpaceSetDamping(space, 0.5);
        space.sleepTimeThreshold = 0.5;
        space.collisionSlop = 0.5;

        var staticBody = space.staticBody;

        // Create segments around the edge of the screen.
        var shape = space.addShape( new cp.SegmentShape(staticBody, cp.v(0,0), cp.v(0,480), 0.0));
        shape.setElasticity(1.0);
        shape.setFriction(1.0);
        shape.setLayers(NOT_GRABABLE_MASK);

        shape = space.addShape( new cp.SegmentShape(staticBody, cp.v(640,0), cp.v(640,480), 0.0));
        shape.setElasticity(1.0);
        shape.setFriction(1.0);
        shape.setLayers(NOT_GRABABLE_MASK);

        shape = space.addShape( new cp.SegmentShape(staticBody, cp.v(0,0), cp.v(640,0), 0.0));
        shape.setElasticity(1.0);
        shape.setFriction(1.0);
        shape.setLayers(NOT_GRABABLE_MASK);

        shape = space.addShape( new cp.SegmentShape(staticBody, cp.v(0,480), cp.v(640,480), 0.0));
        shape.setElasticity(1.0);
        shape.setFriction(1.0);
        shape.setLayers(NOT_GRABABLE_MASK);

        // {
            // Add the edges of the bucket
            var bb = new cp.BB(20, 40, 420, 240);
            var radius = 5.0;

            shape = space.addShape( new cp.SegmentShape(staticBody, cp.v(bb.l, bb.b), cp.v(bb.l, bb.t), radius));
            shape.setElasticity(1.0);
            shape.setFriction(1.0);
            shape.setLayers(NOT_GRABABLE_MASK);

            shape = space.addShape( new cp.SegmentShape(staticBody, cp.v(bb.r, bb.b), cp.v(bb.r, bb.t), radius));
            shape.setElasticity(1.0);
            shape.setFriction(1.0);
            shape.setLayers(NOT_GRABABLE_MASK);

            shape = space.addShape( new cp.SegmentShape(staticBody, cp.v(bb.l, bb.b), cp.v(bb.r, bb.b), radius));
            shape.setElasticity(1.0);
            shape.setFriction(1.0);
            shape.setLayers(NOT_GRABABLE_MASK);

            // Add the sensor for the water.
            shape = space.addShape( new cp.BoxShape2(staticBody, bb) );
            shape.setSensor(true);
            shape.setCollisionType(1);
        // }


        // {
            var width = 200.0;
            var height = 50.0;
            var mass = 0.3*FLUID_DENSITY*width*height;
            var moment = cp.momentForBox(mass, width, height);

            body = space.addBody( new cp.Body(mass, moment));
            body.setPos( cp.v(270, 140));
            body.setVel( cp.v(0, -100));
            body.setAngVel( 1 );

            shape = space.addShape( new cp.BoxShape(body, width, height));
            shape.setFriction(0.8);
        // }

        // {
            width = 40.0;
            height = width*2;
            mass = 0.3*FLUID_DENSITY*width*height;
            moment = cp.momentForBox(mass, width, height);

            body = space.addBody( new cp.Body(mass, moment));
            body.setPos(cp.v(120, 190));
            body.setVel(cp.v(0, -100));
            body.setAngVel(1);

            shape = space.addShape(new cp.BoxShape(body, width, height));
            shape.setFriction(0.8);
        // }
    },

    update: function(dt) {
        var steps = 3;
        dt /= steps;
        for (var i = 0; i < 3; i++){
            this.space.step(dt);
        }
    },

    onEnter: function() {
        this._super();
        this.space.addCollisionHandler( 1, 0, null, this.waterPreSolve, null, null);
    },

    onExit: function() {
        this.space.removeCollisionHandler(1, 0);
        this._super();
    },

    title: function() {
        return 'Buoyancy';
    },

    waterPreSolve : function(arb, space, ptr) {
        var shapes = arb.getShapes();
        var water = shapes[0];
        var poly = shapes[1];

        var body = poly.getBody();

        // Get the top of the water sensor bounding box to use as the water level.
        var level = water.getBB().t;

        // Clip the polygon against the water level
        var count = poly.getNumVerts();

        var clipped = [];

        var j=count-1;
        for(var i=0; i<count; i++) {
            var a = body.local2World(poly.getVert(j));
            var b = body.local2World(poly.getVert(i));

            if(a.y < level){
                clipped.push(a.x);
                clipped.push(a.y);
            }

            var a_level = a.y - level;
            var b_level = b.y - level;

            if(a_level*b_level < 0.0){
                var t = Math.abs(a_level)/(Math.abs(a_level) + Math.abs(b_level));

                var v = cp.v.lerp(a, b, t);
                clipped.push(v.x);
                clipped.push(v.y);
            }
            j=i;
        }

        // Calculate buoyancy from the clipped polygon area
        var clippedArea = cp.areaForPoly(clipped);

        var displacedMass = clippedArea*FLUID_DENSITY;
        var centroid = cp.centroidForPoly(clipped);

        var dt = space.getCurrentTimeStep();
        var g = space.gravity;

        // Apply the buoyancy force as an impulse.
        body.applyImpulse(cp.v.mult(g, -displacedMass*dt), centroid);

        // Apply linear damping for the fluid drag.
        var v_centroid = body.getVelAtWorldPoint(centroid)
        var k = k_scalar_body(body, centroid, cp.v.normalize(v_centroid));
        var damping = clippedArea*FLUID_DRAG*FLUID_DENSITY;
        var v_coef = Math.exp(-damping*dt*k); // linear drag
//  var v_coef = 1.0/(1.0 + damping*dt*cp.v.len(v_centroid)*k); // quadratic drag
        body.applyImpulse(cp.v.mult(cp.v.sub(cp.v.mult(v_centroid, v_coef), v_centroid), 1.0/k), centroid);

        // Apply angular damping for the fluid drag.
        var cog = body.local2World(body.getCenterOfGravity());
        var w_damping = cp.momentForPoly(FLUID_DRAG*FLUID_DENSITY*clippedArea, clipped, cp.v.neg(cog), 0);
        body.w *= Math.exp(-w_damping*dt* (1/body.i));

        return true;
    }
});

//------------------------------------------------------------------
//
// Planet
//
//------------------------------------------------------------------

var Planet = ChipmunkDemo.extend({
    ctor: function () {
        this._super();
        // cc.base(this);
        this._subtitle = 'Chipmunk Demo';
        this._title = 'Planet';

        var space = this.space;

        // global
        this.gravityStrength = 5000000;

        // Create a rouge body to control the planet manually.
        //var planetBody = this.planetBody = new cp.BodyStatic();
        var planetBody = this.planetBody = new cp.StaticBody();
        planetBody.setAngVel(0.2);
        planetBody.setPos( cp.v(winSize.width/2, winSize.height/2) );

        space.iterations = 20;

        for(var i=0; i<30; i++)
            this.add_box();

        var shape = space.addShape(new cp.CircleShape(planetBody, 70.0, cp.vzero));
        shape.setElasticity(1.0);
        shape.setFriction(1.0);
        shape.setLayers(NOT_GRABABLE_MASK);
    },

    update : function(dt)
    {
        var steps = 1;
        dt /= steps;
        for (var i = 0; i < 3; i++){
            this.space.step(dt);

            // Update the static body spin so that it looks like it's rotating.
            // this.planetBody.position_func(dt);
        }
    },

    planetGravityVelocityFunc : function(gravity, damping, dt)
    {
        // Gravitational acceleration is proportional to the inverse square of
        // distance, and directed toward the origin. The central planet is assumed
        // to be massive enough that it affects the satellites but not vice versa.
        var p = this.p;
        var sqdist = cp.v.lengthsq(p);
        var g = cp.v.mult(p, this.gravityStrength / (sqdist * Math.sqrt(sqdist)));

        body.velocity_func(g, damping, dt);
    },

    rand_pos : function(radius)
    {
        var v;
        do {
            v = cp.v(Math.random()*(640 - 2*radius) - (320 - radius), Math.random()*(480 - 2*radius) - (240 - radius));
        } while(cp.v.len(v) < 85.0);

        return v;
    },

    add_box : function()
    {
        var size = 10.0;
        var mass = 1.0;

        var verts = [
            -size,-size,
            -size, size,
            size, size,
            size,-size
        ];

        var radius = cp.v.len(cp.v(size, size));
        var pos = this.rand_pos(radius);

        var body = this.space.addBody( new cp.Body(mass, cp.momentForPoly(mass, verts, cp.vzero)));
        body.velocity_func = this.planetGravityVelocityFunc;
        body.setPos( cp.v.add(pos, cp.v(winSize.width/2, winSize.height/2) ) );

        // Set the box's velocity to put it into a circular orbit from its
        // starting position.
        var r = cp.v.len(pos);
        var v = Math.sqrt(this.gravityStrength / r) / r;
        body.setVel( cp.v.mult(cp.v.perp(pos), v));

        // Set the box's angular velocity to match its orbital period and
        // align its initial angle with its position.
        body.setAngVel(v);
        body.setAngle( Math.atan2(pos.y, pos.x));

        var shape = this.space.addShape( new cp.PolyShape(body, verts, cp.vzero));
        shape.setElasticity(0.0);
        shape.setFriction(0.7);
    },

    title : function(){
        return 'Planet';
    }
});

//------------------------------------------------------------------
//
// Query
//
//------------------------------------------------------------------

var Query = ChipmunkDemo.extend({
    drawNode: null,
    ctor: function () {
        this._super();
        this._subtitle = 'Chipmunk Demo';
        this._title = 'Query';

        this.drawNode = new cc.DrawNode();
        this.addChild(this.drawNode, 10);

        if( 'mouse' in cc.sys.capabilities ) {
            cc.eventManager.addListener({
                event: cc.EventListener.MOUSE,
                onMouseMove: this.drawQuery
            }, this);
        }
        else if( 'touches' in cc.sys.capabilities ) {
            cc.eventManager.addListener({
                event: cc.EventListener.TOUCH_ONE_BY_ONE,
                swallowTouches: true,
                onTouchBegan:function(){
                    return true;
                },
                onTouchMoved: this.drawQuery
            }, this);
        }

        var space = this.space;

        { // add a fat segment
            var mass = 1;
            var length = 100;
            var a = v(-length/2, 0), b = v(length/2, 0);
            
            var body = space.addBody(new cp.Body(mass, cp.momentForSegment(mass, a, b)));
            body.setPos(v(320, 340));
            
            space.addShape(new cp.SegmentShape(body, a, b, 20));
        }

        { // add a static segment
            space.addShape(new cp.SegmentShape(space.staticBody, v(320, 540), v(620, 240), 0));
        }

        { // add a pentagon
            var mass = 1;
            var NUM_VERTS = 5;
            
            var verts = new Array(NUM_VERTS * 2);
            for(var i=0; i<NUM_VERTS*2; i+=2){
                var angle = -Math.PI*i/NUM_VERTS;
                verts[i]   = 30*Math.cos(angle);
                verts[i+1] = 30*Math.sin(angle);
            }
            
            var body = space.addBody(new cp.Body(mass, cp.momentForPoly(mass, verts, v(0,0))));
            body.setPos(v(350+60, 220+60));

            space.addShape(new cp.PolyShape(body, verts, v(0,0)));
        }
        
        { // add a circle
            var mass = 1;
            var r = 20;
            
            var body = space.addBody(new cp.Body(mass, cp.momentForCircle(mass, 0, r, v(0,0))));
            body.setPos(v(320+100, 240+120));
            
            space.addShape(new cp.CircleShape(body, r, v(0,0)));
        }

    },

    drawBB: function(bb, fillColor, lineColor){
        this.drawNode.drawRect(cc.p(bb.l, bb.b), cc.p(bb.r, bb.t), fillColor, 1, lineColor);
    },

    drawQuery: function(touch, event){
        var target = !!event ? event.getCurrentTarget() : touch.getCurrentTarget();
        var drawNode = target.drawNode;
        drawNode.clear();

        var start = cc.p(320, 240);
        var end = touch.getLocation();
        var radius = 10;
        drawNode.drawSegment(start, end, 1, cc.color(0, 255, 0, 255));

        // WARNING: API changed in Chipmunk v7.0
        var info = target.space.segmentQueryFirst(start, end, radius, cp.SHAPE_FILTER_ALL);
        if(info) {

            // Draw blue over the occluded part of the query
            drawNode.drawSegment(cp.v.lerp(start, end, info.alpha), end, 1, cc.color(0,0,255,255));
            
            // Draw a little red surface normal
            drawNode.drawSegment(info.point, cp.v.add(info.point, cp.v.mult(info.normal, 16)), 1, cc.color(255,0,0,255));
        
            // Draw a little red dot on the hit point.
            drawNode.drawDot(info.point, 3, cc.color(255,0,0,255));

            cc.log("Segment Query: Dist(" + info.alpha * cp.v.dist(start,end) + ") Normal:(" + info.normal.x + "," + info.normal.y + ")");

            // Draw a fat green line over the unoccluded part of the query
            // drawNode.drawSegment(start, cp.v.lerp(start, end, info.alpha), radius, cc.color(0,255,0,255));
        } else {
            cc.log("Segment Query (None)");
        }

        var nearestInfo = target.space.pointQueryNearest(touch.getLocation(), 100.0, cp.SHAPE_FILTER_ALL);
        if(nearestInfo){
            // Draw a grey line to the closest shape.
            drawNode.drawDot(touch.getLocation(), 3, cc.color(128, 128, 128, 255));
            drawNode.drawSegment(touch.getLocation(), nearestInfo.p, 1, cc.color(128, 128, 128, 255));
            
            // Draw a red bounding box around the shape under the mouse.
//            if(nearestInfo.d < 0)
//                drawNode.drawBB(cpShapeGetBB(nearestInfo.shape), RGBAColor(1,0,0,1));
        }
        
    }
});

 //------------------------------------------------------------------
 //
 // LogoSmash
 //
 //------------------------------------------------------------------

var LogoSmash = (function(){

    var image_width = 188;
    var image_height = 35;
    var image_row_length = 24;

    var image_bitmap = [
        15,-16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,-64,15,63,-32,-2,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,31,-64,15,127,-125,-1,-128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,127,-64,15,127,15,-1,-64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,-1,-64,15,-2,
        31,-1,-64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,-1,-64,0,-4,63,-1,-32,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,1,-1,-64,15,-8,127,-1,-32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,-1,-64,0,-8,-15,-1,-32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,-31,-1,-64,15,-8,-32,
        -1,-32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,-15,-1,-64,9,-15,-32,-1,-32,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,31,-15,-1,-64,0,-15,-32,-1,-32,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,63,-7,-1,-64,9,-29,-32,127,-61,-16,63,15,-61,-1,-8,31,-16,15,-8,126,7,-31,
        -8,31,-65,-7,-1,-64,9,-29,-32,0,7,-8,127,-97,-25,-1,-2,63,-8,31,-4,-1,15,-13,
        -4,63,-1,-3,-1,-64,9,-29,-32,0,7,-8,127,-97,-25,-1,-2,63,-8,31,-4,-1,15,-13,
        -2,63,-1,-3,-1,-64,9,-29,-32,0,7,-8,127,-97,-25,-1,-1,63,-4,63,-4,-1,15,-13,
        -2,63,-33,-1,-1,-32,9,-25,-32,0,7,-8,127,-97,-25,-1,-1,63,-4,63,-4,-1,15,-13,
        -1,63,-33,-1,-1,-16,9,-25,-32,0,7,-8,127,-97,-25,-1,-1,63,-4,63,-4,-1,15,-13,
        -1,63,-49,-1,-1,-8,9,-57,-32,0,7,-8,127,-97,-25,-8,-1,63,-2,127,-4,-1,15,-13,
        -1,-65,-49,-1,-1,-4,9,-57,-32,0,7,-8,127,-97,-25,-8,-1,63,-2,127,-4,-1,15,-13,
        -1,-65,-57,-1,-1,-2,9,-57,-32,0,7,-8,127,-97,-25,-8,-1,63,-2,127,-4,-1,15,-13,
        -1,-1,-57,-1,-1,-1,9,-57,-32,0,7,-1,-1,-97,-25,-8,-1,63,-1,-1,-4,-1,15,-13,-1,
        -1,-61,-1,-1,-1,-119,-57,-32,0,7,-1,-1,-97,-25,-8,-1,63,-1,-1,-4,-1,15,-13,-1,
        -1,-61,-1,-1,-1,-55,-49,-32,0,7,-1,-1,-97,-25,-8,-1,63,-1,-1,-4,-1,15,-13,-1,
        -1,-63,-1,-1,-1,-23,-49,-32,127,-57,-1,-1,-97,-25,-1,-1,63,-1,-1,-4,-1,15,-13,
        -1,-1,-63,-1,-1,-1,-16,-49,-32,-1,-25,-1,-1,-97,-25,-1,-1,63,-33,-5,-4,-1,15,
        -13,-1,-1,-64,-1,-9,-1,-7,-49,-32,-1,-25,-8,127,-97,-25,-1,-1,63,-33,-5,-4,-1,
        15,-13,-1,-1,-64,-1,-13,-1,-32,-49,-32,-1,-25,-8,127,-97,-25,-1,-2,63,-49,-13,
        -4,-1,15,-13,-1,-1,-64,127,-7,-1,-119,-17,-15,-1,-25,-8,127,-97,-25,-1,-2,63,
        -49,-13,-4,-1,15,-13,-3,-1,-64,127,-8,-2,15,-17,-1,-1,-25,-8,127,-97,-25,-1,
        -8,63,-49,-13,-4,-1,15,-13,-3,-1,-64,63,-4,120,0,-17,-1,-1,-25,-8,127,-97,-25,
        -8,0,63,-57,-29,-4,-1,15,-13,-4,-1,-64,63,-4,0,15,-17,-1,-1,-25,-8,127,-97,
        -25,-8,0,63,-57,-29,-4,-1,-1,-13,-4,-1,-64,31,-2,0,0,103,-1,-1,-57,-8,127,-97,
        -25,-8,0,63,-57,-29,-4,-1,-1,-13,-4,127,-64,31,-2,0,15,103,-1,-1,-57,-8,127,
        -97,-25,-8,0,63,-61,-61,-4,127,-1,-29,-4,127,-64,15,-8,0,0,55,-1,-1,-121,-8,
        127,-97,-25,-8,0,63,-61,-61,-4,127,-1,-29,-4,63,-64,15,-32,0,0,23,-1,-2,3,-16,
        63,15,-61,-16,0,31,-127,-127,-8,31,-1,-127,-8,31,-128,7,-128,0,0
    ];

    var get_pixel = function(x, y)
    {
        return (image_bitmap[(x>>3) + y*image_row_length]>>(~x&0x7)) & 1;
    };

    var make_ball = function(x, y)
    {
        var body = new cp.Body(1, Infinity);
        body.setPos(cp.v(x, y));

        var shape = new cp.CircleShape(body, 0.95, cp.vzero);
        shape.setElasticity(0);
        shape.setFriction(0);

        return shape;
    };

    return ChipmunkBaseLayer.extend({
        ctor:function(){
            this._super();
            this._title =  "LogoSmash";
            this._subtitle = "Chipmunk Demo";

            var space = this.space;
            space.setIterations(1);

            // The space will contain a very large number of similary sized objects.
            // This is the perfect candidate for using the spatial hash.
            // Generally you will never need to do this.
            //
            // (... Except the spatial hash isn't implemented in JS)
            // but it is implemented in JSB :)
            if(cc.sys.isNative)
                space.useSpatialHash(2.0, 10000);

            var batch = new cc.SpriteBatchNode(s_hole_stencil_png);
            this.addChild(batch);

            var body;
            var shape;
            var sprite;

            for(var y=0; y<image_height; y++){
                for(var x=0; x<image_width; x++){
                    if(!get_pixel(x, y)) continue;

                    var x_jitter = 0.05*Math.random();
                    var y_jitter = 0.05*Math.random();

                    var posx = 2*(x - image_width/2 + x_jitter) + 320;
                    var posy = 2*(image_height/2 - y + y_jitter) + 240;
                    shape = make_ball(posx, posy);
                    space.addBody(shape.getBody());
                    space.addShape(shape);

                    sprite = new cc.Sprite(batch.texture);
                    sprite.setPosition(posx, posy);
                    batch.addChild(sprite);

                    shape.sprite = sprite;
                }
            }

            body = space.addBody(new cp.Body(9999, Infinity));
            body.setPos(cp.v(-1000, 240-10));
            body.setVel(cp.v(400, 0));

            shape = space.addShape(new cp.CircleShape(body, 8, cp.vzero));
            shape.setElasticity(0);
            shape.setFriction(0);
            shape.setLayers(NOT_GRABABLE_MASK);
            shape.ball = true;

            sprite = new cc.Sprite(batch.texture);
            sprite.setPosition(posx, posy);
            batch.addChild(sprite);
            shape.sprite = sprite;

            this.scheduleUpdate();
        },

        update:function(dt){
            var space = this.space;
            space.step(dt);
            space.eachShape(function(shape){
                var pos = shape.body.p;
                shape.sprite.setPosition(pos.x, pos.y);
                //no need to set rotation for this case, for all sprites are round
            });
        }
    });
})();

//
// Entry point
//

var ChipmunkTestScene = function() {
    TestScene.call(this);
    //var parent = cc.base(this);
};
cc.inherits(ChipmunkTestScene, TestScene );

ChipmunkTestScene.prototype.runThisTest = function (num) {
    chipmunkTestSceneIdx = (num || num == 0) ? (num - 1) : -1;
    var layer = nextChipmunkTest();
    this.addChild(layer);
    director.runScene(this);
};

//
// Flow control
//

var Issue1092 = ChipmunkDemo.extend({
    ctor:function(){
        this._super();
        this._subtitle = 'Chipmunk Demo';
        this._title = 'Issue 1092';

        var space = this.space;

        var body = space.addBody(new cp.Body(100, 50));
        body.setPos(cp.v(winSize.width/2, winSize.height/2));
        space.addShape(cp.BoxShape(body, 50, 50));

        cc.assert(body.vx == 0, "assertion failed : vx");
        cc.assert(body.vy == 0, "assertion failed : vy");
        cc.assert(body.v_limit == Infinity, "assertion failed : v_limit");
        cc.assert(body.w_limit == Infinity, "assertion failed : w_limit");
        cc.assert(body.f.x == 0, "assertion failed : f");
        cc.assert(body.t == 0, "assertion failed : t");
        cc.assert(body.m == 100, "assertion failed : m");
        cc.assert(body.m_inv == 0.01, "assertion failed : m_inv");
        cc.assert(body.i == 50, "assertion failed : i");
        cc.assert(body.i_inv == 0.02, "assertion failed : i_inv");
        cc.assert(body.rot.x == Math.cos(0), "assertion failed : rot");


        space.addConstraint(new cp.PivotJoint(body, space.staticBody, cp.v(winSize.width/2, winSize.height/2)));
        body.applyImpulse(cp.v(winSize.width/2, winSize.height/2-20), cp.v(1, -1));

        body.eachShape(function(shape){
            cc.log(shape);
        });
        body.eachConstraint(function(joint){
            cc.log(joint);
        });
        body.eachArbiter(function(arbiter){
            cc.log(arbiter);
        })
    }
});

var Issue1073 = ChipmunkDemo.extend({
    ctor:function(){
        this._super();
        this._subtitle = 'Chipmunk Demo';
        this._title = 'Issue 1073';

        var space = this.space;
        // add a circle
        var mass = 1;
        var r = 20;
        var body = space.addBody(new cp.Body(mass, cp.momentForCircle(mass, 0, r, v(0,0))));
        body.setPos(cp.v(winSize.width/2, winSize.height/2));
        var shape = new cp.CircleShape(body, r, v(0,0));
        space.addShape(shape);

        var nearestPointQueryInfo = shape.nearestPointQuery(cp.v(winSize.width/2+100, winSize.height/2));
        cc.log("The nearest point on the shape's surface to query point is : (" + nearestPointQueryInfo.p.x + "," + nearestPointQueryInfo.p.y + ")");
        cc.log("And the distance is : " + nearestPointQueryInfo.d);

        var segmentQueryInfo = shape.segmentQuery(cp.v(winSize.width/2 - 100, winSize.height/2), cp.v(winSize.width/2 + 100, winSize.height/2));
        cc.log("The normal of the surface hit is : (" + segmentQueryInfo.n.x + "," + segmentQueryInfo.n.y + ")");
        cc.log("The normalized distance along the query segment in the range [0, 1] is : " + segmentQueryInfo.t);
    }
});

var Issue1083 = ChipmunkDemo.extend({
    ctor:function(){
        this._super();
        this._subtitle = 'Chipmunk Demo';
        this._title = 'Issue 1083';

        var space = this.space;

        //add a segment
        var mass = 1;
        var length = 100;
        var a = v(-length/2, 0), b = v(length/2, 0);
        var body = space.addBody(new cp.Body(mass, cp.momentForSegment(mass, a, b)));
        body.setPos(v(320, 340));
        var segment = new cp.SegmentShape(body, a, b, 20);
        space.addShape(segment);

        //add a poly
        var mass = 1;
        var NUM_VERTS = 5;
        var verts = new Array(NUM_VERTS * 2);
        for(var i=0; i<NUM_VERTS*2; i+=2){
            var angle = -Math.PI*i/NUM_VERTS;
            verts[i]   = 30*Math.cos(angle);
            verts[i+1] = 30*Math.sin(angle);
        }
        var body = space.addBody(new cp.Body(mass, cp.momentForPoly(mass, verts, v(0,0))));
        body.setPos(v(350+60, 220+60));
        var poly = new cp.PolyShape(body, verts, v(0,0));
        space.addShape(poly);

        cc.assert(segment.a.x == -length/2, "SegmentShape assertion failed : a.x");
        cc.assert(segment.a.y == 0, "SegmentShape assertion failed : a.y");
        cc.assert(segment.b.x == length/2, "SegmentShape assertion failed : b.x");
        cc.assert(segment.b.y == 0, "SegmentShape assertion failed : b.y");
        var normal = cp.v.perp(cp.v.normalize(cp.v.sub(b, a)));
        cc.assert(segment.n.x == normal.x, "SegmentShape assertion failed : n.x");
        cc.assert(segment.n.y == normal.y, "SegmentShape assertion failed : n.y");
        cc.assert(segment.r == 20, "SegmentShape assertion failed : r");

        for(var i = 0; i < verts.length; ++i){
            cc.assert(verts[i] == poly.verts[i],"PolyShape assertion failed : verts");
        }

        // FIXME: Chipmunk v7.0 does export planes
        // var plane = poly.planes[0];
        // cc.assert(plane.d.toFixed(4) == 24.2705, "PolyShape assertion failed : planes d");
        // cc.assert(plane.n.x.toFixed(4) == 0.8090, "PolyShape assertion failed : planes n");
    }
});

// Chipmunk Demos
var arrayOfChipmunkTest =  [

// Chipmunk "C" Tests
        // Planet,
        LogoSmash,
        Query,
        Buoyancy,
        PyramidStack,
        PyramidTopple,
        Joints,
        Balls,

// Custom Tests
        ChipmunkSprite ,
        ChipmunkSpriteBatchTest ,
        ChipmunkCollisionTest_no_specific_type,
        ChipmunkCollisionTest,
        ChipmunkCollisionMemoryLeakTest,
        ChipmunkSpriteAnchorPoint,

        Issue1073,
        Issue1083,
        Issue1092
        ];

if( cc.sys.isNative ) {
    arrayOfChipmunkTest.push( ChipmunkCollisionTestB );
    arrayOfChipmunkTest.push( ChipmunkReleaseTest );
}

var nextChipmunkTest = function () {
    chipmunkTestSceneIdx++;
    chipmunkTestSceneIdx = chipmunkTestSceneIdx % arrayOfChipmunkTest.length;

    if(window.sideIndexBar){
        chipmunkTestSceneIdx = window.sideIndexBar.changeTest(chipmunkTestSceneIdx, 3);
    }

    return new arrayOfChipmunkTest[chipmunkTestSceneIdx]();
};
var previousChipmunkTest = function () {
    chipmunkTestSceneIdx--;
    if (chipmunkTestSceneIdx < 0)
        chipmunkTestSceneIdx += arrayOfChipmunkTest.length;

    if(window.sideIndexBar){
        chipmunkTestSceneIdx = window.sideIndexBar.changeTest(chipmunkTestSceneIdx, 3);
    }

    return new arrayOfChipmunkTest[chipmunkTestSceneIdx]();
};
var restartChipmunkTest = function () {
    return new arrayOfChipmunkTest[chipmunkTestSceneIdx]();
};
