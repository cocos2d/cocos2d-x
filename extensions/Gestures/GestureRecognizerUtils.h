/****************************************************************************
Copyright (c) 2016 Alfonso Grillo

    drakon.cocos@gmail.com

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

#include "cocos2d.h"
/**
 * 
 * @param map
 * @param key
 * @return true if the container 'map' has the element 'key'
 */
template <class Map, class Key>
inline bool mapHasKey(const Map& map, const Key& key)
{
    return map.find(key) != map.end();
}

/**
 * 
 * @param node
 * @param pt
 * @return true if 'node' contains the point 'pt'
 */
bool nodeContainsThePoint(cocos2d::Node* node, const cocos2d::Vec2& pt);

/**
 * 
 * @param v1
 * @param v2
 * @return angle between v1 and v2. The angle is positive if v1 overlaps v2 clockwise, negative otherwise.
 */
float computeSignedAngle(const cocos2d::Vec2& v1, const cocos2d::Vec2& v2);