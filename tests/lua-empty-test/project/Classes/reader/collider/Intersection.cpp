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
#include "Intersection.h"

#include "math/Vec2.h"

NS_CCR_BEGIN


bool Intersection::polygonPolygon(const std::vector<cocos2d::Vec2>& polygon1, const std::vector<cocos2d::Vec2>& polygon2)
{
    size_t i = 0, l = 0;
    
    // check if p1 polygon1 intersects polygon2
    for (l = polygon1.size(); i < l; ++i)
    {
        const auto& a1 = polygon1[i];
        const auto& a2 = polygon1[(i+1) % l];
        
        if (Intersection::linePolygon(a1, a2, polygon2))
            return true;
    }
    
    // check if polygon1 contains polygon2
    for (i = 0, l = polygon2.size(); i < l; ++i)
    {
        if (Intersection::pointInPolygon(polygon2[i], polygon1))
            return true;
    }
    
    // check if polygon2 contains polygon1
    for (i = 0, l = polygon1.size(); i < l; ++i)
    {
        if (Intersection::pointInPolygon(polygon1[i], polygon2))
            return true;
    }
    
    return false;
}

bool Intersection::circleCircle(const cocos2d::Vec2& pos1, float r1, const cocos2d::Vec2& pos2, float r2)
{
    auto distance = pos1.distance(pos2);
    return distance < (r1 + r2);
}

bool Intersection::polygonCircle(const std::vector<cocos2d::Vec2>& polygon, const cocos2d::Vec2& pos, float r)
{
    if (Intersection::pointInPolygon(pos, polygon))
        return true;
    
    for (size_t i = 0, l = polygon.size(); i < l; ++i)
    {
        const auto& start = i == 0 ? polygon[l-1] : polygon[i-1];
        const auto& end = polygon[i];
        
        if (Intersection::pointLineDistance(pos, start, end, true) < r)
            return true;
    }
    
    return false;
}

bool Intersection::linePolygon(const cocos2d::Vec2& A, const cocos2d::Vec2& B, const std::vector<cocos2d::Vec2>& polygon)
{
    auto length = polygon.size();
    for (size_t i = 0; i < length; ++i)
    {
        auto C = polygon[i];
        auto D = polygon[(i+1) % length];
        
        if (cocos2d::Vec2::isLineIntersect(A, B, C, D))
            return true;
    }
    
    return false;
}

bool Intersection::pointInPolygon(const cocos2d::Vec2& pos, const std::vector<cocos2d::Vec2>& polygon)
{
    bool inside = false;
    auto x = pos.x;
    auto y = pos.y;
    
    // use some raycasting to test hits
    // https://github.com/substack/point-in-polygon/blob/master/index.js
    auto length = polygon.size();
    
    bool intersect = false;
    for (size_t i = 0, j = length-1; i < length; j = ++i)
    {
        auto xi = polygon[i].x, yi = polygon[i].y,
             xj = polygon[j].x, yj = polygon[j].y;
        intersect = ((yi > y) != (yj > y)) && (x < (xj - xi) * (y - yi) / (yj - yi) + xi);
        
        if (intersect)
            inside = !inside;
    }
    
    return inside;
}

float Intersection::pointLineDistance(const cocos2d::Vec2& point, const cocos2d::Vec2& start, const cocos2d::Vec2& end, bool isSegment)
{
    auto dx = end.x - start.x;
    auto dy = end.y - start.y;
    auto d = dx*dx + dy*dy;
    auto t = ((point.x - start.x) * dx + (point.y - start.y) * dy) / d;
    cocos2d::Vec2 p;
    
    if (!isSegment)
        p = cocos2d::Vec2(start.x + t * dx, start.y + t * dy);
    else {
        if (d)
        {
            if (t < 0) p = start;
            else if (t > 1) p = end;
            else p = cocos2d::Vec2(start.x + t * dx, start.y + t * dy);
        }
        else
            p = start;
    }
    
    dx = point.x - p.x;
    dy = point.y - p.y;
    return std::sqrt(dx*dx + dy*dy);
}

NS_CCR_END
