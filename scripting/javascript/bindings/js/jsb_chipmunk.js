//
// Chipmunk defines
//

require('jsb_chipmunk_constants.js');

var cp = cp || {};

cp.v = cc.p;
cp._v = cc._p;
cp.vzero  = cp.v(0,0);

// Vector: Compatibility with Chipmunk-JS
cp.v.add = cp.vadd;
cp.v.clamp = cp.vclamp;
cp.v.cross = cp.vcross;
cp.v.dist = cp.vdist;
cp.v.distsq = cp.vdistsq;
cp.v.dot = cp.vdot;
cp.v.eql = cp.veql;
cp.v.forangle = cp.vforangle;
cp.v.len = cp.vlength;
cp.v.lengthsq = cp.vlengthsq;
cp.v.lerp = cp.vlerp;
cp.v.lerpconst = cp.vlerpconst;
cp.v.mult = cp.vmult;
cp.v.near = cp.vnear;
cp.v.neg = cp.vneg;
cp.v.normalize = cp.vnormalize;
cp.v.normalize_safe = cp.vnormalize_safe;
cp.v.perp = cp.vperp;
cp.v.project = cp.vproject;
cp.v.rotate = cp.vrotate;
cp.v.rperp = cp.vrperp;
cp.v.slerp = cp.vslerp;
cp.v.slerpconst = cp.vslerpconst;
cp.v.sub = cp.vsub;
cp.v.toangle = cp.vtoangle;
cp.v.unrotate = cp.vunrotate;

// XXX: renaming functions should be supported in JSB
cp.clamp01 = cp.fclamp01;


/// Initialize an offset box shaped polygon shape.
cp.BoxShape2 = function(body, box)
{
	var verts = [
		box.l, box.b,
		box.l, box.t,
		box.r, box.t,
		box.r, box.b
	];

	return new cp.PolyShape(body, verts, cp.vzero);
};

/// Initialize a box shaped polygon shape.
cp.BoxShape = function(body, width, height)
{
	var hw = width/2;
	var hh = height/2;

	return cp.BoxShape2(body, new cp.BB(-hw, -hh, hw, hh));
};


/// Initialize an static body
cp.StaticBody = function()
{
	return new cp.Body(Infinity, Infinity);
};


// "Bounding Box" compatibility with Chipmunk-JS
cp.BB = function(l, b, r, t)
{
	return {l:l, b:b, r:r, t:t};
};

// helper function to create a BB
cp.bb = function(l, b, r, t) {
	return new cp.BB(l, b, r, t);
};

//
// Some properties
//
// "handle" needed in some cases
Object.defineProperties(cp.Base.prototype,
				{
					"handle" : {
						get : function(){
                            return this.getHandle();
                        },
                        enumerable : true,
						configurable : true
					}
				});

// Properties, for Chipmunk-JS compatibility
// Space properties
Object.defineProperties(cp.Space.prototype,
				{
					"gravity" : {
						get : function(){
                            return this.getGravity();
                        },
						set : function(newValue){
                            this.setGravity(newValue);
                        },
						enumerable : true,
						configurable : true
					},
					"iterations" : {
						get : function(){
                            return this.getIterations();
                        },
						set : function(newValue){
                            this.setIterations(newValue);
                        },
						enumerable : true,
						configurable : true
					},
					"damping" : {
						get : function(){
                            return this.getDamping();
                        },
						set : function(newValue){
                            this.setDamping(newValue);
                        },
						enumerable : true,
						configurable : true
					},
					"staticBody" : {
						get : function(){
                            return this.getStaticBody();
                        },
						enumerable : true,
						configurable : true
					},
					"idleSpeedThreshold" : {
						get : function(){
                            return this.getIdleSpeedThreshold();
                        },
						set : function(newValue){
                            this.setIdleSpeedThreshold(newValue);
                        },
						enumerable : true,
						configurable : true
					},
					"sleepTimeThreshold": {
						get : function(){
                            return this.getSleepTimeThreshold();
                        },
						set : function(newValue){
                            this.setSleepTimeThreshold(newValue);
                        },
						enumerable : true,
						configurable : true
					},
					"collisionSlop": {
						get : function(){
                            return this.getCollisionSlop();
                        },
						set : function(newValue){
                            this.setCollisionSlop(newValue);
                        },
						enumerable : true,
						configurable : true
					},
					"collisionBias": {
						get : function(){
                            return this.getCollisionBias();
                        },
						set : function(newValue){
                            this.setCollisionBias(newValue);
                        },
						enumerable : true,
						configurable : true
					},
					"collisionPersistence": {
						get : function(){
                            return this.getCollisionPersistence();
                        },
						set : function(newValue){
                            this.setCollisionPersistence(newValue);
                        },
						enumerable : true,
						configurable : true
					},
					"enableContactGraph": {
						get : function(){
                            return this.getEnableContactGraph();
                        },
						set : function(newValue){
                            this.setEnableContactGraph(newValue);
                        },
						enumerable : true,
						configurable : true
					}
				});

// Body properties
Object.defineProperties(cp.Body.prototype,
				{
					"a" : {
						get : function(){
                            return this.getAngle();
                        },
						set : function(newValue){
                            this.setAngle(newValue);
                        },
						enumerable : true,
						configurable : true
					},
					"w" : {
						get : function(){
                            return this.getAngVel();
                        },
						set : function(newValue){
                            this.setAngVel(newValue);
                        },
						enumerable : true,
						configurable : true
					},
					"p" : {
						get : function(){
                            return this.getPos();
                        },
						set : function(newValue){
                            this.setPos(newValue);
                        },
						enumerable : true,
						configurable : true
					},
					"v" : {
						get : function(){
                            return this.getVel();
                        },
						set : function(newValue){
                            this.setVel(newValue);
                        },
						enumerable : true,
						configurable : true
					},
					"i" : {
						get : function(){
                            return this.getMoment();
                        },
						set : function(newValue){
                            this.setMoment(newValue);
                        },
						enumerable : true,
						configurable : true
					}

				});

// Shape properties
Object.defineProperties(cp.Shape.prototype,
				{
					"body" : {
						get : function(){
                            return this.getBody();
                        },
						set : function(newValue){
                            this.setBody(newValue);
                        },
						enumerable : true,
						configurable : true
					},
                    "group" : {
						get : function(){
                            return this.getGroup();
                        },
						set : function(newValue){
                            this.setGroup(newValue);
                        },
						enumerable : true,
						configurable : true
                    },
					"collision_type" : {
						get : function(){
                            return this.getCollisionType();
                        },
						enumerable : true,
						configurable : true
					}
				});

// Constraint properties
Object.defineProperties(cp.Constraint.prototype,
				{
					"maxForce" : {
						get : function(){
                            return this.getMaxForce();
                        },
						set : function(newValue){
                            this.setMaxForce(newValue);
                        },
						enumerable : true,
						configurable : true
					}
				});

// PinJoint properties
Object.defineProperties(cp.PinJoint.prototype,
				{
					"anchr1" : {
						get : function(){
                            return this.getAnchr1();
                        },
						set : function(newValue){
                            this.setAnchr1(newValue);
                        },
						enumerable : true,
						configurable : true
					},
					"anchr2" : {
						get : function(){
                            return this.getAnchr2();
                        },
						set : function(newValue){
                            this.setAnchr2(newValue);
                        },
						enumerable : true,
						configurable : true
					}
				});
