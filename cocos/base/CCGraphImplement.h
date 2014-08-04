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

#ifndef __cocos2d_libs__CCGraphImplement__
#define __cocos2d_libs__CCGraphImplement__

NS_CC_BEGIN

// Graph impletation
template<typename T>
const int Graph<T>::MAX_COMPILED_SIZE = 1000;

template<typename T>
Graph<T>::Graph()
: _func(nullptr)
, _start(0.0f)
, _end(0.0f)
, _interval(0.0f)
{
    
}

template<typename T>
Graph<T>::~Graph()
{
    
}

template<typename T>
Graph<T>* Graph<T>::create()
{
    Graph<T>* ret = new Graph<T>();
    if (ret != nullptr && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

template<typename T>
Graph<T>* create(CC_GRAPH_FUNC(T) func)
{
    Graph<T>* ret = new Graph<T>();
    if (ret != nullptr && ret->init(func))
    {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

template<typename T>
Graph<T>* Graph<T>::create(const T& defaultValue)
{
    Graph<T>* ret = new Graph<T>();
    if (ret != nullptr && ret->init(nullptr, defaultValue))
    {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

template<typename T>
Graph<T>* Graph<T>::create(const std::vector<T>& vec, float start, float end, float interval)
{
    Graph<T>* ret = new Graph<T>();
    if (ret != nullptr && ret->init(nullptr, nullptr, vec, start, end, interval))
    {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

template<typename T>
bool Graph<T>::init(CC_GRAPH_FUNC(T) func/* = nullptr*/, const T* defaultValue/* = nullptr*/, const std::vector<T>* vec/* = nullptr*/, float start/* = 0.0f*/, float end/* = 0.0f*/, float interval/* = 0.0f*/)
{
    _func = func;
    
    if (defaultValue != nullptr)
    {
        _default = *defaultValue;
    }
    
    if (vec != nullptr)
    {
        _compiled = *vec;
        _start = start;
        _end = end;
        _interval = interval;
    }
    
    return true;
}

template<typename T>
T Graph<T>::get(float time) const
{
    if (!_compiled.empty())
    {
        if (time >= _start && time <= _end)
        {
            return _compiled[(int)((time - _start) / _interval)];
        }
        else
        {
            return _default;
        }
    }
    else if(_func != nullptr)
    {
        return _func(time);
    }
    else
    {
        return _default;
    }
}

template<typename T>
void Graph<T>::compile(float start, float end, float interval)
{
    if ( _func == nullptr )
    {
        return;
    }
    
    if ( interval == 0.0f || (end - start) * interval < 0 )
    {
        CCLOG("Graph compile warning: invalid interval value");
        return;
    }
    
    if ( (end - start) / interval > MAX_COMPILED_SIZE)
    {
        CCLOG("Graph compile warning: sample values is too much");
        return;
    }
    
    _compiled.clear();
    for (float i = start; i <= end; i += interval)
    {
        _compiled.push_back(_func(i));
    }
    
    _start = start;
    _end = end;
    _interval = interval;
}

template<typename T>
void Graph<T>::setFunc(CC_GRAPH_FUNC(T) func)
{
    _func = func;
}

template<typename T>
void Graph<T>::setVector(std::vector<T>& vec, float start, float end, float interval)
{
    _compiled = vec;
    _start = start;
    _end = end;
    _interval = interval;
}

template<typename T>
void Graph<T>::setDefault(T& defaultValue)
{
    defaultValue = defaultValue;
}

namespace
{
    template<typename T>
    bool compareLineGraphPoint(const LineGraphPoint<T>& a, const LineGraphPoint<T>& b)
    {
        return a.p.x < b.p.x;
    }
}

//LineGraph implement
template<typename T>
void LineGraph<T>::add(const LineGraphPoint<T>& point)
{
    _points.push_back(point);
    std::sort(_points.begin(), _points.end(), compareLineGraphPoint<T>);
}

template<typename T>
void LineGraph<T>::add(float x, const T& y, int tag/* = 0*/)
{
    add(LineGraphPoint<T>(GraphPoint<T>(x, y), tag));
}

template<typename T>
void LineGraph<T>::removeByTag(int tag)
{
    for(int i = 0; i < _points.size(); ++i)
    {
        if(_points[i].tag == tag)
        {
            _points.erase(_points.begin() + i);
            break;
        }
    }
}

template<typename T>
void LineGraph<T>::removeByIndex(int index)
{
    if (index >= 0 && index < _points.size())
    {
        _points.erase(_points.begin() + index);
    }
}

template<typename T>
T LineGraph<T>::compute(float time)
{
    int a = -1, b = -1;
    for(int i = 0; i < _points.size(); ++i)
    {
        if ( time == _points[i].p.x)
        {
            return _points[i].p.y;
        }else if (time > _points[i].p.x)
        {
            a = i;
        }
        else
        {
            b = i;
            break;
        }
    }
    
    // time > max || time < min
    if (a == -1 || b == -1)
    {
        return Graph<T>::_default;
    }
    
    // y0 = (x0 - x1) / (x2 - x1) * y + (x2 - x0) / (x2 - x1) * y
    return _points[b].p.y * ((time - _points[a].p.x) / (_points[b].p.x - _points[a].p.x))
    + _points[a].p.y * ((_points[b].p.x - time) / (_points[b].p.x - _points[a].p.x));
}

template<typename T>
LineGraph<T>* LineGraph<T>::create()
{
    auto ret = new LineGraph<T>();
    if(ret != nullptr && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

template<typename T>
bool LineGraph<T>::init()
{
    Graph<T>::setFunc(std::bind(&LineGraph<T>::compute, this, std::placeholders::_1));
    
    return true;
}

NS_CC_END

#endif /* defined(__cocos2d_libs__CCGraphImplement__) */
