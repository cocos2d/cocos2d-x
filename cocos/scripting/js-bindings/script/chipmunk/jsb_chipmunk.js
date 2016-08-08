/*
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 *
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
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

//
// Chipmunk defines
//

var cp = cp || {};

cp.Vect = function(x, y){
    this.x = x;
    this.y = y;
}
cp.Vect.prototype.add = function(v){
    this.x += v.x;
    this.y += v.y;
    return this;
}
cp.Vect.prototype.sub = function(v){
    this.x -= v.x;
    this.y -= v.y;
    return this;
}
cp.Vect.prototype.neg = function(){
    this.x = -this.x;
    this.y = -this.y;
    return this;
}
cp.Vect.prototype.mult = function(s){
    this.x *= s;
    this.y *= s;
    return this;
}
cp.Vect.prototype.rotate = function(v){
    this.x = this.x * v.x - this.y * v.y;
    this.y = this.x * v.y + this.y * v.x;
    return this;
}
cp.Vect.prototype.project = function(v){
    this.mult(cp.vdot(this, v) / cp.vlengthsq(v));
    return this;
}

cp.v = function(x, y){
    return new cp.Vect(x, y);
}
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
cp.v.pvrperp = cp.vrperp;
cp.v.slerp = cp.vslerp;
cp.v.slerpconst = cp.vslerpconst;
cp.v.sub = cp.vsub;
cp.v.toangle = cp.vtoangle;
cp.v.unrotate = cp.vunrotate;
cp.v.str = function(v){
    return "(" + v.x.toFixed(3) + ", " + v.y.toFixed(3) + ")";
}

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
    this.l = l;
    this.b = b;
    this.r = r;
    this.t = t;
};

// helper function to create a BB
cp.bb = function(l, b, r, t) {
    return new cp.BB(l, b, r, t);
};

//
// BEGIN OF CHIPMUNK V6.2 COMPATIBILIY
// Define them before the properties
//

// Body
cp.Body.prototype.getVelAtWorldPoint = function(point) {
        return this.getVelocityAtWorldPoint(point);
}
cp.Body.prototype.getVelAtLocalPoint = function(point) {
        return this.getVelocityAtLocalPoint(point);
}
cp.Body.prototype.getVel = function() {
        return this.getVelocity();
}
cp.Body.prototype.setVel = function(velocity) {
        this.setVelocity(velocity);
}
cp.Body.prototype.getPos = function() {
        return this.getPosition();
}
cp.Body.prototype.setPos = function(pos) {
        this.setPosition(pos);
}
cp.Body.prototype.getRot = function() {
        return this.getRotation();
}
cp.Body.prototype.getAngVel = function() {
        return this.getAngularVelocity();
}
cp.Body.prototype.setAngVel = function(angularVelocity) {
        this.setAngularVelocity(angularVelocity);
}
cp.Body.prototype.local2World = function(point) {
        return this.localToWorld(point);
}
cp.Body.prototype.world2Local = function(point) {
        return this.worldToLocal(point);
}
cp.Body.prototype.applyImpulse = function(j,r) {
        this.applyImpulseAtWorldPoint(j,r);
}
cp.Body.prototype.applyForce = function(force, point) {
        this.applyForceAtWorldPoint(force, point);
}


// Shapes
cp.Shape.prototype.setLayers = function(layer) {
        var filter = this.getFilter();
        filter.mask = layer;
        this.setFilter(filter);
}
cp.Shape.prototype.getLayers = function() {
        var filter = this.getFilter();
        return filter.mask;
}
cp.Shape.prototype.setGroup = function(group) {
        var filter = this.getFilter();
        filter.group = group;
        this.setFilter(filter);
}

cp.Shape.prototype.getGroup = function() {
        var filter = this.getFilter();
        return filter.group;
}

cp.Shape.prototype.nearestPointQuery = function(p) {
        return this.pointQuery(p);
}
cp.PolyShape.prototype.getNumVerts = function() {
        return this.getCount();
}

// Space
cp.Space.prototype.addStaticShape = function(shape) {
        this.addShape(shape);
}

// Joints
cp.PinJoint.prototype.getAnchr1 = function() {
    return this.getAnchorA();
};

cp.PinJoint.prototype.getAnchr2 = function() {
    return this.getAnchorB();
};

cp.SlideJoint.prototype.getAnchr1 = function() {
    return this.getAnchorA();
};

cp.SlideJoint.prototype.getAnchr2 = function() {
    return this.getAnchorB();
};

cp.PivotJoint.prototype.getAnchr1 = function() {
    return this.getAnchorA();
};

cp.PivotJoint.prototype.getAnchr2 = function() {
    return this.getAnchorB();
};

cp.GrooveJoint.prototype.getAnchr2 = function() {
    return this.getAnchorB();
};

cp.DampedSpring.prototype.getAnchr1 = function() {
    return this.getAnchorA();
};

cp.DampedSpring.prototype.getAnchr2 = function() {
    return this.getAnchorB();
};

cp.Space.prototype.addStaticShape = function(shape) {
    this.addShape(shape);
};


// END OF CHIPMUNK V6.2 COMPATIBILIY


// Chipmunk v7.0 constants
cp.SHAPE_FILTER_ALL = {
        group:cp.NO_GROUP,
        categories:cp.ALL_CATEGORIES,
        mask:cp.ALL_CATEGORIES
};

cp.privateAPI = function() {
        cc.log("Private API not exposed in Chipmunk v7.0");
}

// helpers for the properties. see below, in the properties section
cp.Arbiter.prototype.getBodyA = function() {
        return this.getBodies()[0];
}
cp.Arbiter.prototype.getBodyB = function() {
        return this.getBodies()[1];
}
cp.Body.prototype.getVelocityX = function() {
        return this.getVelocity().x;
}
cp.Body.prototype.getVelocityY = function() {
        return this.getVelocity().y;
}
cp.Shape.prototype.getBBL = function() {
        return this.getBB().l;
}
cp.Shape.prototype.getBBB = function() {
        return this.getBB().b;
}
cp.Shape.prototype.getBBR = function() {
        return this.getBB().r;
}
cp.Shape.prototype.getBBT = function() {
        return this.getBB().t;
}


//
// Some properties
//
var _proto = cp.Base.prototype;
// "handle" needed in some cases
cc.defineGetterSetter(_proto, "handle", _proto.getHandle);

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
_proto = cp.Body.prototype;
cc.defineGetterSetter(_proto, "a", _proto.getAngle, _proto.setAngle);
cc.defineGetterSetter(_proto, "w", _proto.getAngVel, _proto.setAngVel);
cc.defineGetterSetter(_proto, "p", _proto.getPos, _proto.setPos);
cc.defineGetterSetter(_proto, "v", _proto.getVel, _proto.setVel);
cc.defineGetterSetter(_proto, "f", _proto.getForce, _proto.setForce);
cc.defineGetterSetter(_proto, "t", _proto.getTorque, _proto.setTorque);
cc.defineGetterSetter(_proto, "v_limit", _proto.getVelLimit, _proto.setVelLimit);
cc.defineGetterSetter(_proto, "w_limit", _proto.getAngVelLimit, _proto.setAngVelLimit);
cc.defineGetterSetter(_proto, "space", _proto.getSpace);
cc.defineGetterSetter(_proto, "rot", _proto.getRot);
cc.defineGetterSetter(_proto, "m", _proto.getMass, _proto.setMass);
cc.defineGetterSetter(_proto, "i", _proto.getMoment, _proto.setMoment);
cc.defineGetterSetter(_proto, "vx", _proto.getVelocityX);
cc.defineGetterSetter(_proto, "vy", _proto.getVelocityY);
cc.defineGetterSetter(_proto, "m_inv", cp.privateAPI);
cc.defineGetterSetter(_proto, "i_inv", cp.privateAPI);


// Shape properties
_proto = cp.Shape.prototype;
cc.defineGetterSetter(_proto, "body", _proto.getBody, _proto.setBody);
cc.defineGetterSetter(_proto, "group", _proto.getGroup, _proto.setGroup);
cc.defineGetterSetter(_proto, "collision_type", _proto.getCollisionType, _proto.setCollisionType);
cc.defineGetterSetter(_proto, "layers", _proto.getLayers, _proto.setLayers);
cc.defineGetterSetter(_proto, "sensor", _proto.getSensor, _proto.setSensor);
cc.defineGetterSetter(_proto, "space", _proto.getSpace);
cc.defineGetterSetter(_proto, "surface_v", _proto.getSurfaceVelocity, _proto.setSurfaceVelocity);
cc.defineGetterSetter(_proto, "e", _proto.getElasticity, _proto.setElasticity);
cc.defineGetterSetter(_proto, "u", _proto.getFriction, _proto.setFriction);
cc.defineGetterSetter(_proto, "bb_l", _proto.getBBL, cp.privateAPI);
cc.defineGetterSetter(_proto, "bb_b", _proto.getBBB, cp.privateAPI);
cc.defineGetterSetter(_proto, "bb_r", _proto.getBBR, cp.privateAPI);
cc.defineGetterSetter(_proto, "bb_t", _proto.getBBT, cp.privateAPI);

_proto.cacheData = _proto.update;

//CircleShape properties
_proto = cp.CircleShape.prototype;
_proto.type  = "circle";
cc.defineGetterSetter(_proto, "r", _proto.getRadius);
cc.defineGetterSetter(_proto, "c", _proto.getOffset);

//SegmentShape properties
_proto = cp.SegmentShape.prototype;
_proto.type = "segment";
cc.defineGetterSetter(_proto, "a", _proto.getA);
cc.defineGetterSetter(_proto, "b", _proto.getB);
cc.defineGetterSetter(_proto, "n", _proto.getNormal);
cc.defineGetterSetter(_proto, "r", _proto.getRadius);
cc.defineGetterSetter(_proto, "a_tangent", cp.privateAPI);
cc.defineGetterSetter(_proto, "b_tangent", cp.privateAPI);

//PolyShape properties
_proto = cp.PolyShape.prototype;
_proto.type = "poly";
cc.defineGetterSetter(_proto, "verts", _proto.getVerts);

// Constraint properties
_proto = cp.Constraint.prototype;
cc.defineGetterSetter(_proto, "a", _proto.getA);
cc.defineGetterSetter(_proto, "b", _proto.getB);
cc.defineGetterSetter(_proto, "space", _proto.getSpace);
cc.defineGetterSetter(_proto, "maxForce", _proto.getMaxForce, _proto.setMaxForce);
cc.defineGetterSetter(_proto, "errorBias", _proto.getErrorBias, _proto.setErrorBias);
cc.defineGetterSetter(_proto, "maxBias", _proto.getMaxBias, _proto.setMaxBias);

// PinJoint properties
_proto = cp.PinJoint.prototype;
cc.defineGetterSetter(_proto, "anchr1", _proto.getAnchr1, _proto.setAnchr1);
cc.defineGetterSetter(_proto, "anchr2", _proto.getAnchr2, _proto.setAnchr2);
cc.defineGetterSetter(_proto, "dist", _proto.getDist, _proto.setDist);

//SlideJoint  properties
_proto = cp.SlideJoint.prototype;
cc.defineGetterSetter(_proto, "anchr1", _proto.getAnchr1, _proto.setAnchr1);
cc.defineGetterSetter(_proto, "anchr2", _proto.getAnchr2, _proto.setAnchr2);
cc.defineGetterSetter(_proto, "min", _proto.getMin, _proto.setMin);
cc.defineGetterSetter(_proto, "max", _proto.getMax, _proto.setMax);

//PivotJoint properties
_proto = cp.PivotJoint.prototype;
cc.defineGetterSetter(_proto, "anchr1", _proto.getAnchr1, _proto.setAnchr1);
cc.defineGetterSetter(_proto, "anchr2", _proto.getAnchr2, _proto.setAnchr2);

//GrooveJoint properties
_proto = cp.GrooveJoint.prototype;
cc.defineGetterSetter(_proto, "anchr2", _proto.getAnchr2, _proto.setAnchr2);
cc.defineGetterSetter(_proto, "grv_a", _proto.getGrooveA, _proto.setGrooveA);
cc.defineGetterSetter(_proto, "grv_b", _proto.getGrooveB, _proto.setGrooveB);

//DampedSpring properties
_proto = cp.DampedSpring.prototype;
cc.defineGetterSetter(_proto, "anchr1", _proto.getAnchr1, _proto.setAnchr1);
cc.defineGetterSetter(_proto, "anchr2", _proto.getAnchr2, _proto.setAnchr2);
cc.defineGetterSetter(_proto, "damping", _proto.getDamping, _proto.setDamping);
cc.defineGetterSetter(_proto, "restLength", _proto.getRestLength, _proto.setRestLength);
cc.defineGetterSetter(_proto, "stiffness", _proto.getStiffness, _proto.setStiffness);

//DampedRotarySpring properties
_proto = cp.DampedRotarySpring.prototype;
cc.defineGetterSetter(_proto, "restAngle", _proto.getRestAngle, _proto.setRestAngle);
cc.defineGetterSetter(_proto, "stiffness", _proto.getStiffness, _proto.setStiffness);
cc.defineGetterSetter(_proto, "damping", _proto.getDamping, _proto.setDamping);

//RotaryLimitJoint properties
_proto = cp.RotaryLimitJoint.prototype;
cc.defineGetterSetter(_proto, "min", _proto.getMin, _proto.setMin);
cc.defineGetterSetter(_proto, "max", _proto.getMax, _proto.setMax);

//RatchetJoint properties
_proto = cp.RatchetJoint.prototype;
cc.defineGetterSetter(_proto, "angle", _proto.getAngle, _proto.setAngle);
cc.defineGetterSetter(_proto, "phase", _proto.getPhase, _proto.setPhase);
cc.defineGetterSetter(_proto, "ratchet", _proto.getRatchet, _proto.setRatchet);

//GearJoint properties
_proto = cp.GearJoint.prototype;
cc.defineGetterSetter(_proto, "phase", _proto.getPhase, _proto.setPhase);
cc.defineGetterSetter(_proto, "ratio", _proto.getRatio, _proto.setRatio);

//SimpleMotor properties
_proto = cp.SimpleMotor.prototype;
cc.defineGetterSetter(_proto, "rate", _proto.getRate, _proto.setRate);

//Arbiter properties
_proto = cp.Arbiter.prototype;
cc.defineGetterSetter(_proto, "e", _proto.getElasticity, _proto.setElasticity);
cc.defineGetterSetter(_proto, "u", _proto.getFriction, _proto.setFriction);
cc.defineGetterSetter(_proto, "surface_vr", _proto.getSurfaceVelocity, _proto.setSurfaceVelocity);
// not auto-generated
cc.defineGetterSetter(_proto, "a", _proto.getPointA);
cc.defineGetterSetter(_proto, "b", _proto.getPointA);
cc.defineGetterSetter(_proto, "body_a", _proto.getBodyA);
cc.defineGetterSetter(_proto, "body_b", _proto.getBodyB);

_proto = null;

