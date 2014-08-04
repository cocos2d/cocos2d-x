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

#ifndef __cocos2d_libs__CCGraph__
#define __cocos2d_libs__CCGraph__

#include <functional>
#include <vector>
#include <map>

#include "CCRef.h"
#include "ccTypes.h"

#define CC_GRAPH_FUNC(T) std::function<T(float)>

NS_CC_BEGIN

template <typename T>
class Graph : public Ref
{
public:
    static const int MAX_COMPILED_SIZE;
public:
    static Graph<T>* create();
    static Graph<T>* create(const T& defaultValue);
    static Graph<T>* create(CC_GRAPH_FUNC(T) func);
    static Graph<T>* create(const std::vector<T>& vec, float start, float end, float interval);
    
public:
    T get(float time) const;
    void compile(float start, float end, float interval);
    
public:
    void setFunc(CC_GRAPH_FUNC(T) func);
    void setVector(std::vector<T>& vec, float start, float end, float interval);
    void setDefault(T& defaultValue);

CC_CONSTRUCTOR_ACCESS:
    Graph();
    virtual ~Graph();
    
    bool init(CC_GRAPH_FUNC(T) func = nullptr, const T* defaultValue = nullptr, const std::vector<T>* vector = nullptr, float start = 0.0f, float end = 0.0f, float interval = 0.0f);
    
protected:
    CC_GRAPH_FUNC(T) _func;
    std::vector<T> _compiled;
    T _default;
    float _start;
    float _end;
    float _interval;
};

template <typename T>
struct GraphPoint
{
    float x;
    T y;
    GraphPoint(float ax, const T& ay)
    : x(ax)
    , y(ay)
    {
    }
};

template <typename T>
struct LineGraphPoint
{
    GraphPoint<T> p;
    int tag;
    LineGraphPoint(const GraphPoint<T>& ap, int atag)
    : p(ap)
    , tag(atag)
    {
    }
};

template <typename T>
class LineGraph : public Graph<T>
{
public:
    static LineGraph* create();
    
public:
    void add(const LineGraphPoint<T>& point);
    void add(float x, const T& y, int tag = 0);
    void removeByTag(int tag);
    void removeByIndex(int index);
    
protected:
    T compute(float time);

CC_CONSTRUCTOR_ACCESS:
    LineGraph(){}
    virtual ~LineGraph(){}
    
    bool init();

protected:
    std::vector<LineGraphPoint<T>> _points;
};

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


#include "CCGraphImplement.h"

#endif /* defined(__cocos2d_libs__CCGraph__) */
