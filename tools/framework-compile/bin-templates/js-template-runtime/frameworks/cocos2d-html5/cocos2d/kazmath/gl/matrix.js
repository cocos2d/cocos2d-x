/**
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 Copyright (c) 2008, Luke Benstead.
 All rights reserved.

 Redistribution and use in source and binary forms, with or without modification,
 are permitted provided that the following conditions are met:

 Redistributions of source code must retain the above copyright notice,
 this list of conditions and the following disclaimer.
 Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

(function(cc) {
    cc.KM_GL_MODELVIEW = 0x1700;
    cc.KM_GL_PROJECTION = 0x1701;
    cc.KM_GL_TEXTURE = 0x1702;

    cc.modelview_matrix_stack = new cc.math.Matrix4Stack();
    cc.projection_matrix_stack = new cc.math.Matrix4Stack();
    cc.texture_matrix_stack = new cc.math.Matrix4Stack();

    cc.current_stack = null;
    var initialized = false;

    cc.lazyInitialize = function () {
        if (!initialized) {
            var identity = new cc.math.Matrix4(); //Temporary identity matrix

            //Initialize all 3 stacks
            cc.modelview_matrix_stack.initialize();
            cc.projection_matrix_stack.initialize();
            cc.texture_matrix_stack.initialize();

            cc.current_stack = cc.modelview_matrix_stack;
            cc.initialized = true;
            identity.identity();

            //Make sure that each stack has the identity matrix
            cc.modelview_matrix_stack.push(identity);
            cc.projection_matrix_stack.push(identity);
            cc.texture_matrix_stack.push(identity);
        }
    };

    cc.lazyInitialize();

    cc.kmGLFreeAll = function () {
        //Clear the matrix stacks
        cc.modelview_matrix_stack.release();
        cc.modelview_matrix_stack = null;
        cc.projection_matrix_stack.release();
        cc.projection_matrix_stack = null;
        cc.texture_matrix_stack.release();
        cc.texture_matrix_stack = null;

        //Delete the matrices
        cc.initialized = false; //Set to uninitialized
        cc.current_stack = null; //Set the current stack to point nowhere
    };

    cc.kmGLPushMatrix = function () {
        cc.current_stack.push(cc.current_stack.top);
    };

    cc.kmGLPushMatrixWitMat4 = function (saveMat) {
        cc.current_stack.stack.push(cc.current_stack.top);
        saveMat.assignFrom(cc.current_stack.top);
        cc.current_stack.top = saveMat;
    };

    cc.kmGLPopMatrix = function () {
        //No need to lazy initialize, you shouldnt be popping first anyway!
        //cc.km_mat4_stack_pop(cc.current_stack, null);
        cc.current_stack.top = cc.current_stack.stack.pop();
    };

    cc.kmGLMatrixMode = function (mode) {
        //cc.lazyInitialize();
        switch (mode) {
            case cc.KM_GL_MODELVIEW:
                cc.current_stack = cc.modelview_matrix_stack;
                break;
            case cc.KM_GL_PROJECTION:
                cc.current_stack = cc.projection_matrix_stack;
                break;
            case cc.KM_GL_TEXTURE:
                cc.current_stack = cc.texture_matrix_stack;
                break;
            default:
                throw "Invalid matrix mode specified";   //TODO: Proper error handling
                break;
        }
    };

    cc.kmGLLoadIdentity = function () {
        //cc.lazyInitialize();
        cc.current_stack.top.identity(); //Replace the top matrix with the identity matrix
    };

    cc.kmGLLoadMatrix = function (pIn) {
        //cc.lazyInitialize();
        cc.current_stack.top.assignFrom(pIn);
    };

    cc.kmGLMultMatrix = function (pIn) {
        //cc.lazyInitialize();
        cc.current_stack.top.multiply(pIn);
    };

    var tempMatrix = new cc.math.Matrix4();    //an internal matrix
    cc.kmGLTranslatef = function (x, y, z) {
        //Create a rotation matrix using translation
        var translation = cc.math.Matrix4.createByTranslation(x, y, z, tempMatrix);

        //Multiply the rotation matrix by the current matrix
        cc.current_stack.top.multiply(translation);
    };

    var tempVector3 = new cc.math.Vec3();
    cc.kmGLRotatef = function (angle, x, y, z) {
        tempVector3.fill(x, y, z);
        //Create a rotation matrix using the axis and the angle
        var rotation = cc.math.Matrix4.createByAxisAndAngle(tempVector3, cc.degreesToRadians(angle), tempMatrix);

        //Multiply the rotation matrix by the current matrix
        cc.current_stack.top.multiply(rotation);
    };

    cc.kmGLScalef = function (x, y, z) {
        var scaling = cc.math.Matrix4.createByScale(x, y, z, tempMatrix);
        cc.current_stack.top.multiply(scaling);
    };

    cc.kmGLGetMatrix = function (mode, pOut) {
        //cc.lazyInitialize();
        switch (mode) {
            case cc.KM_GL_MODELVIEW:
                pOut.assignFrom(cc.modelview_matrix_stack.top);
                break;
            case cc.KM_GL_PROJECTION:
                pOut.assignFrom(cc.projection_matrix_stack.top);
                break;
            case cc.KM_GL_TEXTURE:
                pOut.assignFrom(cc.texture_matrix_stack.top);
                break;
            default:
                throw "Invalid matrix mode specified"; //TODO: Proper error handling
                break;
        }
    };
})(cc);
