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

#ifndef __cocos2d_libs__CCGradient__
#define __cocos2d_libs__CCGradient__

#include "CCRef.h"
#include "ccTypes.h"
#include "CCGraph.h"

NS_CC_BEGIN

class Gradient : public Ref
{
public:
    static Gradient* create();
    
public:
    void add(float x, const Color3B& color, int tag = 0);
    void add(float x, float alpha, int tag = 0);
    void add(float x, const Color4B& color, int tag = 0);
    void removeRGBByTag(int tag);
    void removeAlphaByTag(int tag);
    void removeRGBAByTag(int tag);
    
CC_CONSTRUCTOR_ACCESS:
    Gradient();
    virtual ~Gradient();
    
    bool init();
    
protected:
    LineGraph<Color3B>* _colors;
    LineGraph<float>* _alphas;
};

NS_CC_END

#endif /* defined(__cocos2d_libs__CCGradient__) */
