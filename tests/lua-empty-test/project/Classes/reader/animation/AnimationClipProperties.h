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

#include "cocos2d.h"

#include "Macros.h"

NS_CCR_BEGIN

struct AnimPropRotation
{
    float frame;
    float value;
};

struct AnimPropPosition
{
    float frame;
    cocos2d::Vec2 value;
};

struct AnimPropPositionX
{
    float frame;
    float value;
};

struct AnimPropPositionY
{
    float frame;
    float value;
};

struct AnimPropScaleX
{
    float frame;
    float value;
};

struct AnimPropScaleY
{
    float frame;
    float value;
};

struct AnimPropWidth
{
    float frame;
    float value;
};

struct AnimPropHeight
{
    float frame;
    float value;
};

struct AnimPropColor
{
    float frame;
    cocos2d::Color3B value;
};

struct AnimPropOpacity
{
    float frame;
    float value;
};

struct AnimPropAnchorX
{
    float frame;
    float value;
};

struct AnimPropAnchorY
{
    float frame;
    float value;
};

struct AnimPropSkewX
{
    float frame;
    float value;
};

struct AnimPropSkewY
{
    float frame;
    float value;
};

struct AnimProperties
{
    std::vector<AnimPropRotation> animRotation;
    std::vector<AnimPropPosition> animPosition;
    std::vector<AnimPropPositionX> animPositionX;
    std::vector<AnimPropPositionY> animPositionY;
    std::vector<AnimPropScaleX> animScaleX;
    std::vector<AnimPropScaleY> animScaleY;
    std::vector<AnimPropSkewX> animSkewX;
    std::vector<AnimPropSkewY> animSkewY;
    std::vector<AnimPropAnchorX> animAnchorX;
    std::vector<AnimPropAnchorY> animAnchorY;
    std::vector<AnimPropColor> animColor;
    std::vector<AnimPropOpacity> animOpacity;
    std::vector<AnimPropWidth> animWidth;
    std::vector<AnimPropHeight> animHeight;
    std::string path;
};

NS_CCR_END
