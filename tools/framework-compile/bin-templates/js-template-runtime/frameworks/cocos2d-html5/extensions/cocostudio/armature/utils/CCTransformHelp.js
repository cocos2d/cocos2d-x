/****************************************************************************
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
 *  use to calculate the matrix of node from parent node
 * @class ccs.TransformHelp
 * @extend ccs.Class
 */
ccs.TransformHelp = ccs.TransformHelp || ccs.Class.extend({});

ccs.TransformHelp.helpMatrix1 = cc.affineTransformMake(1, 0, 0, 1, 0, 0);
ccs.TransformHelp.helpMatrix2 = cc.affineTransformMake(1, 0, 0, 1, 0, 0);
ccs.TransformHelp.helpPoint1 = cc.p(0, 0);
ccs.TransformHelp.helpPoint2 = cc.p(0, 0);
ccs.TransformHelp.helpParentNode = {};

/**
 * Calculate a BaseData's transform matrix from parent node.
 * @function
 * @static
 * @param {ccs.BaseData} bone
 * Constructor
 */
ccs.TransformHelp.transformFromParent = function (bone, parentNode) {
    this.nodeToMatrix(bone, this.helpMatrix1);
    this.nodeToMatrix(parentNode, this.helpMatrix2);

    this.helpMatrix2 = cc.affineTransformInvert(this.helpMatrix2);
    this.helpMatrix1 = cc.affineTransformConcat(this.helpMatrix1, this.helpMatrix2);

    this.matrixToNode(this.helpMatrix1, bone);
};

ccs.TransformHelp.transformToParent = function(node, parentNode){
    this.nodeToMatrix(node, this.helpMatrix1);
    this.nodeToMatrix(parentNode, this.helpMatrix2);

    this.helpMatrix1 = cc.affineTransformConcat(this.helpMatrix1, this.helpMatrix2);

    this.matrixToNode(this.helpMatrix1, node);
};

ccs.TransformHelp.transformFromParentWithoutScale = function(node, parentNode){
//    this.helpParentNode.copy(&parentNode);

    for(var p in parentNode){
        this.helpParentNode[p] = parentNode[p];
    }
    this.helpParentNode.scaleX = 1;
    this.helpParentNode.scaleY = 1;

    this.nodeToMatrix(node, this.helpMatrix1);
    this.nodeToMatrix(this.helpParentNode, this.helpMatrix2);

    this.helpMatrix2 = cc.affineTransformInvert(this.helpMatrix2);
    this.helpMatrix1 = cc.affineTransformConcat(this.helpMatrix1, this.helpMatrix2);

    this.matrixToNode(this.helpMatrix1, node);
};

ccs.TransformHelp.transformToParentWithoutScale = function(node, parentNode){
    for(var p in parentNode){
        this.helpParentNode[p] = parentNode[p];
    }
    this.helpParentNode.scaleX = 1;
    this.helpParentNode.scaleY = 1;

    this.nodeToMatrix(node, this.helpMatrix1);
    this.nodeToMatrix(this.helpParentNode, this.helpMatrix2);

    this.helpMatrix1 = cc.affineTransformConcat(this.helpMatrix1, this.helpMatrix2);

    this.matrixToNode(this.helpMatrix1, node);

};

/**
 * @function
 * @static
 * @param {ccs.BaseData} node
 * @param {cc.AffineTransform} matrix
 */
ccs.TransformHelp.nodeToMatrix = function (node, matrix) {
    if (node.skewX === -node.skewY) {
        var sine = Math.sin(node.skewX);
        var cosine = Math.cos(node.skewX);
        matrix.a = node.scaleX * cosine;
        matrix.b = node.scaleX * -sine;
        matrix.c = node.scaleY * sine;
        matrix.d = node.scaleY * cosine;
    } else {
        matrix.a = node.scaleX * Math.cos(node.skewY);
        matrix.b = node.scaleX * Math.sin(node.skewY);
        matrix.c = node.scaleY * Math.sin(node.skewX);
        matrix.d = node.scaleY * Math.cos(node.skewX);
    }
    matrix.tx = node.x;
    matrix.ty = node.y;
};

/**
 * @function
 * @static
 * @param {cc.AffineTransform} matrix
 * @param {ccs.BaseData} node
 */
ccs.TransformHelp.matrixToNode = function (matrix, node) {
    /*
     *  In as3 language, there is a function called "deltaTransformPoint", it calculate a point used give Transform
     *  but not used the tx, ty value. we simulate the function here
     */
    this.helpPoint1.x = 0;
    this.helpPoint1.y = 1;
    this.helpPoint1 = cc.pointApplyAffineTransform(this.helpPoint1, matrix);
    this.helpPoint1.x -= matrix.tx;
    this.helpPoint1.y -= matrix.ty;

    this.helpPoint2.x = 1;
    this.helpPoint2.y = 0;
    this.helpPoint2 = cc.pointApplyAffineTransform(this.helpPoint2, matrix);
    this.helpPoint2.x -= matrix.tx;
    this.helpPoint2.y -= matrix.ty;

    node.skewX = -(Math.atan2(this.helpPoint1.y, this.helpPoint1.x) - 1.5707964); //todo
    //node.skewX = -Math.atan2(this.helpPoint2.y, this.helpPoint2.x);
    node.skewY = Math.atan2(this.helpPoint2.y, this.helpPoint2.x);
    node.scaleX = Math.sqrt(matrix.a * matrix.a + matrix.b * matrix.b);
    node.scaleY = Math.sqrt(matrix.c * matrix.c + matrix.d * matrix.d);
    node.x = matrix.tx;
    node.y = matrix.ty;
};

/**
 * @function
 * @static
 * @param {ccs.BaseData} target
 * @param {ccs.BaseData} source
 */
ccs.TransformHelp.nodeConcat = function (target, source) {
    target.x += source.x;
    target.y += source.y;
    target.skewX += source.skewX;
    target.skewY += source.skewY;
    target.scaleX += source.scaleX;
    target.scaleY += source.scaleY;
};

/**
 * @function
 * @static
 * @param {ccs.BaseData} target
 * @param {ccs.BaseData} source
 */
ccs.TransformHelp.nodeSub = function (target, source) {
    target.x -= source.x;
    target.y -= source.y;
    target.skewX -= source.skewX;
    target.skewY -= source.skewY;
    target.scaleX -= source.scaleX;
    target.scaleY -= source.scaleY;
};