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

(function(cc){
    cc.math.Vec2 = function (x, y) {
        if(y === undefined){
            this.x = x.x;
            this.y = x.y;
        }else{
            this.x = x || 0;
            this.y = y || 0;
        }
    };

    var proto = cc.math.Vec2.prototype;
    proto.fill = function(x, y){   // = cc.kmVec2Fill
        this.x = x;
        this.y = y;
    };

    proto.length = function(){   // = cc.kmVec2Length
        return Math.sqrt(cc.math.square(this.x) + cc.math.square(this.y));
    };

    proto.lengthSq = function(){   // = cc.kmVec2LengthSq
        return cc.math.square(this.x) + cc.math.square(this.y);
    };

    proto.normalize = function(){  // = cc.kmVec2Normalize
        var l = 1.0 / this.length();
        this.x *= l;
        this.y *= l;
        return this;
    };

    cc.math.Vec2.add = function (pOut, pV1, pV2) {     // = cc.kmVec2Add
        pOut.x = pV1.x + pV2.x;
        pOut.y = pV1.y + pV2.y;
        return pOut
    };

    proto.add = function(vec){   // = cc.kmVec2Add
        this.x += vec.x;
        this.y += vec.y;
        return this;
    };

    proto.dot = function (vec) {   //cc.kmVec2Dot
        return this.x * vec.x + this.y * vec.y;
    };

    cc.math.Vec2.subtract = function (pOut, pV1, pV2) {      // = cc.kmVec2Subtract
        pOut.x = pV1.x - pV2.x;
        pOut.y = pV1.y - pV2.y;
        return pOut;
    };

    proto.subtract = function(vec){     // = cc.kmVec2Subtract
        this.x -= vec.x;
        this.y -= vec.y;
        return this;
    };

    proto.transform = function (mat3) {     // = cc.kmVec2Transform
        var x = this.x, y = this.y;
        this.x = x * mat3.mat[0] + y * mat3.mat[3] + mat3.mat[6];
        this.y = x * mat3.mat[1] + y * mat3.mat[4] + mat3.mat[7];
        return this;
    };

    cc.math.Vec2.scale = function (pOut, pIn, s) {  // = cc.kmVec2Scale
        pOut.x = pIn.x * s;
        pOut.y = pIn.y * s;
        return pOut;
    };

    proto.scale = function(s) {  // = cc.kmVec2Scale
        this.x *= s;
        this.y *= s;
        return this;
    };

    proto.equals = function (vec) {    // = cc.kmVec2AreEqual
        return (this.x < vec.x + cc.math.EPSILON && this.x > vec.x - cc.math.EPSILON) &&
            (this.y < vec.y + cc.math.EPSILON && this.y > vec.y - cc.math.EPSILON);
    };
})(cc);

