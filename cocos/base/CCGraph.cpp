/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 Copyright (c) 2014 Chukong Technologies Inc.
 
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

#include "CCGraph.h"

NS_CC_BEGIN

// Gradient implement
Gradient::Gradient()
: _colors(nullptr)
, _alphas(nullptr)
{
    
}

Gradient::~Gradient()
{
    CC_SAFE_RELEASE(_colors);
    CC_SAFE_RELEASE(_alphas);
}

Gradient* Gradient::create()
{
    auto ret = new Gradient();
    if (ret != nullptr && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool Gradient::init()
{
    _colors = LineGraph<Color3B>::create();
    _colors->retain();
    
    _alphas = LineGraph<float>::create();
    _alphas->retain();
    
    return true;
}

void Gradient::add(float x, const Color3B& color, int tag/* = 0*/)
{
    _colors->add(x, color, tag);
}

void Gradient::add(float x, float alpha, int tag/* = 0*/)
{
    _alphas->add(x, alpha, tag);
}

void Gradient::add(float x, const Color4B& color, int tag/* = 0*/)
{
    _colors->add(x, Color3B(color), tag);
    _alphas->add(x, color.a, tag);
}

void Gradient::removeRGBByTag(int tag)
{
    _colors->removeByTag(tag);
}

void Gradient::removeAlphaByTag(int tag)
{
    _alphas->removeByTag(tag);
}

void Gradient::removeRGBAByTag(int tag)
{
    _colors->removeByTag(tag);
    _alphas->removeByTag(tag);
}

NS_CC_END