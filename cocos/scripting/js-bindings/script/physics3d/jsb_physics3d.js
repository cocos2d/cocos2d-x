/*
 * Copyright (c) 2014-2016 Chukong Technologies Inc.
 * Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
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

jsb.Physics3DRigidBodyDes = function(){
    this.mass = 0;
    this.localInertia = cc.math.vec3(0, 0, 0);
    this.shape = null;
    this.originalTransform = [1.0, 0.0, 0.0, 0.0,
                              0.0, 1.0, 0.0, 0.0,
                              0.0, 0.0, 1.0, 0.0,
                              0.0, 0.0, 0.0, 1.0];
    this.disableSleep = false;
};

jsb.physics3DRigidBodyDes = function(){
    return new jsb.Physics3DRigidBodyDes();
};

jsb.Physics3DComponent.PhysicsSyncFlag = {
    NONE : 0,
    NODE_TO_PHYSICS : 1, //align node transform to the physics
    PHYSICS_TO_NODE : 2, // align physics transform to the node
    NODE_AND_NODE : 1 | 2, //pre simulation, align the physics object to the node and align the node transform according to physics object after simulation
};

jsb.HitResult = function(){
  this.hitPosition = cc.math.vec3();
  this.hitNormal   = cc.math.vec3();
  this.hitObj      = null;
}

jsb.hitResult = function(){
    return new cc.HitResult();
};

jsb.Physics3DObject.PhysicsObjType = {
    UNKNOWN : 0,
    RIGID_BODY : 1, 
};