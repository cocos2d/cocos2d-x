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
    cc.math.Ray2 = function (start, dir) {   // = cc.kmRay2
        this.start = start || new cc.math.Vec2();
        this.dir = dir || new cc.math.Vec2();
    };

    cc.math.Ray2.prototype.fill = function (px, py, vx, vy) {   // = cc.kmRay2Fill
        this.start.x = px;
        this.start.y = py;
        this.dir.x = vx;
        this.dir.y = vy;
    };

    cc.math.Ray2.prototype.intersectLineSegment = function (p1, p2, intersection) {   // = cc.kmRay2IntersectLineSegment
        var x1 = this.start.x, y1 = this.start.y;
        var x2 = this.start.x + this.dir.x, y2 = this.start.y + this.dir.y;
        var x3 = p1.x, y3 = p1.y;
        var x4 = p2.x, y4 = p2.y;

        var denom = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
        var ua, x, y;
        //If denom is zero, the lines are parallel
        if (denom > -cc.math.EPSILON && denom < cc.math.EPSILON)
            return false;

        ua = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / denom;
        //var ub = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / denom;

        x = x1 + ua * (x2 - x1);
        y = y1 + ua * (y2 - y1);

        if (x < Math.min(p1.x, p2.x) - cc.math.EPSILON ||
            x > Math.max(p1.x, p2.x) + cc.math.EPSILON ||
            y < Math.min(p1.y, p2.y) - cc.math.EPSILON ||
            y > Math.max(p1.y, p2.y) + cc.math.EPSILON) {
            //Outside of line
            //printf("Outside of line, %f %f (%f %f)(%f, %f)\n", x, y, p1.x, p1.y, p2.x, p2.y);
            return false;
        }

        if (x < Math.min(x1, x2) - cc.math.EPSILON ||
            x > Math.max(x1, x2) + cc.math.EPSILON ||
            y < Math.min(y1, y2) - cc.math.EPSILON ||
            y > Math.max(y1, y2) + cc.math.EPSILON) {
            //printf("Outside of ray, %f %f (%f %f)(%f, %f)\n", x, y, x1, y1, x2, y2);
            return false;
        }

        intersection.x = x;
        intersection.y = y;
        return true;
    };

    function calculate_line_normal(p1, p2, normalOut){
        var tmp = new cc.math.Vec2(p2);
        tmp.subtract(p1);

        normalOut.x = -tmp.y;
        normalOut.y = tmp.x;
        normalOut.normalize();
        //TODO: should check that the normal is pointing out of the triangle
    }

    cc.math.Ray2.prototype.intersectTriangle = function(p1, p2, p3, intersection, normal_out){
        var intersect = new cc.math.Vec2(), final_intersect = new cc.math.Vec2();
        var normal = new cc.math.Vec2(), distance = 10000.0, intersected = false;
        var this_distance;

        if(this.intersectLineSegment(p1, p2, intersect)) {
            intersected = true;
            this_distance = intersect.subtract(this.start).length();
            if(this_distance < distance) {
                final_intersect.x = intersect.x;
                final_intersect.y = intersect.y;
                distance = this_distance;
                calculate_line_normal(p1, p2, normal);
            }
        }

        if(this.intersectLineSegment(p2, p3, intersect)) {
            intersected = true;
            this_distance = intersect.subtract(this.start).length();
            if(this_distance < distance) {
                final_intersect.x = intersect.x;
                final_intersect.y = intersect.y;
                distance = this_distance;
                calculate_line_normal(p2, p3, normal);
            }
        }

        if(this.intersectLineSegment(p3, p1, intersect)) {
            intersected = true;
            this_distance = intersect.subtract(this.start).length();
            if(this_distance < distance) {
                final_intersect.x = intersect.x;
                final_intersect.y = intersect.y;
                distance = this_distance;
                calculate_line_normal(p3, p1, normal);
            }
        }

        if(intersected) {
            intersection.x = final_intersect.x;
            intersection.y = final_intersect.y;
            if(normal_out) {
                normal_out.x = normal.x;
                normal_out.y = normal.y;
            }
        }
        return intersected;
    };
})(cc);
