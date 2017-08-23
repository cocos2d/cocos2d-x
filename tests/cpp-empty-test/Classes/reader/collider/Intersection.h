/****************************************************************************
 Copyright (c) 2017 Chukong Technologies Inc.
 
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
#pragma once

#include <vector>
#include "math/Vec2.h"
#include "Macros.h"

NS_CCR_BEGIN

class Intersection
{
public:
    /** Test whether two polygons interset.
     * @param p1 points of first polygon
     * @param p2 points of second polygon
     * @return True if two polygon intersect
     *         False else
     */
    static bool polygonPolygon(const std::vector<cocos2d::Vec2>& polygon1, const std::vector<cocos2d::Vec2>& polygon2);
    /** Test whether two circles intersect.
     * @param pos1 first circle's position
     * @param r1 first circle's radius
     * @param pos2 second circle's position
     * @param r2 second circle's radius
     */
    static bool circleCircle(const cocos2d::Vec2& pos1, float r1, const cocos2d::Vec2& pos2, float r2);
    /** Test whether a polygon intersects with a circle.
     * @param p points of the polygon
     * @param pos the circle's position
     * @param r the circle's radius
     */
    static bool polygonCircle(const std::vector<cocos2d::Vec2>& polygon, const cocos2d::Vec2& pos, float r);
private:
    static bool linePolygon(const cocos2d::Vec2& A, const cocos2d::Vec2& B, const std::vector<cocos2d::Vec2>& polygon);
    static bool pointInPolygon(const cocos2d::Vec2& pos, const std::vector<cocos2d::Vec2>& p);
    static float pointLineDistance(const cocos2d::Vec2& point, const cocos2d::Vec2& start, const cocos2d::Vec2& end, bool isSegment);
};

NS_CCR_END
