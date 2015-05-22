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

var ENABLE_PHYSICS_DETECT = false;
ccs.fmodf = function (x, y) {
    while (x > y) {
        x -= y;
    }
    return x;
};
var CC_SAFE_RELEASE = function (obj) {
    if (obj && obj.release) {
        obj.release();
    }
};

ccs.isSpriteContainPoint = function (sprite, point, outPoint) {
    var p = sprite.convertToNodeSpace(point);
    if (outPoint) {
        outPoint.x = p.x;
        outPoint.y = p.y;
    }
    var s = sprite.getContentSize();
    return cc.rectContainsPoint(cc.rect(0, 0, s.width, s.height), p);
};
ccs.SPRITE_CONTAIN_POINT = ccs.isSpriteContainPoint;
ccs.SPRITE_CONTAIN_POINT_WITH_RETURN = ccs.isSpriteContainPoint;

ccs.extBezierTo = function (t, point1, point2, point3, point4) {
    var p = cc.p(0, 0);
    if (point3 && !point4) {
        p.x = Math.pow((1 - t), 2) * point1.x + 2 * t * (1 - t) * point2.x + Math.pow(t, 2) * point3.x;
        p.y = Math.pow((1 - t), 2) * point1.y + 2 * t * (1 - t) * point2.y + Math.pow(t, 2) * point3.y;
    }
    if (point4) {
        p.x = point1.x * Math.pow((1 - t), 3) + 3 * t * point2.x * Math.pow((1 - t), 2) + 3 * point3.x * Math.pow(t, 2) * (1 - t) + point4.x * Math.pow(t, 3);
        p.y = point1.y * Math.pow((1 - t), 3) + 3 * t * point2.y * Math.pow((1 - t), 2) + 3 * point3.y * Math.pow(t, 2) * (1 - t) + point4.y * Math.pow(t, 3);
    }
    return p;
};

ccs.extCircleTo = function (t, center, radius, fromRadian, radianDif) {
    var p = cc.p(0, 0);
    p.x = center.x + radius * Math.cos(fromRadian + radianDif * t);
    p.y = center.y + radius * Math.sin(fromRadian + radianDif * t);
    return p;
};