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

namespace
{
    // bezier curve: http://en.wikipedia.org/wiki/B%C3%A9zier_curve
    // t = (x0 - x1) / (x2 - x1)
    
    // y0 = (1 - t) * y1 + t * y2
    template<typename T>
    T linear_bezier(float x1, const T& y1, float x2, const T& y2, float x0)
    {
        float t = (x0 - x1) / (x2 - x1);
        return y1 * (1 - t) + y2 * t;
    }
    
    // y0 = (1 - t)^2 * y1 + 2 * t * (1 - t) * y2 + t^2 * y3
    template<typename T>
    T quadratic_bezier(float x1, const T& y1, float x2, const T& y2, float x3, const T& y3, float x0)
    {
        float t = (x0 - x1) / (x2 - x1);
        float r = 1.0f - t;
        return y1 * (r * r) + y2 * (2 * t * r) + y3 * (t * t);
    }
    
    // y0 = (1 - t)^3 * y1 + 3 * t * (1 - t)^2 * y2 + 3 * t^2 * (1 - t) * y3 + t^3 * y4
    template<typename T>
    T cubics_bezier(float x1, const T& y1, float x2, const T& y2, float x3, const T& y3, float x4, const T& y4, float x0)
    {
        float t = (x0 - x1) / (x2 - x1);
        float r = 1.0f - t;
        return y1 * (r * r * r) + y2 * (3 * t * r * r) + y3 * (3 * t * t * r) + y4 * (t * t * t);
    }
}

// Graph implementation
template<typename T>
Graph<T>::Graph()
: _func(nullptr)
, _start(0.0f)
, _end(0.0f)
, _interval(0.0f)
, _isNeedCompile(true)
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
T Graph<T>::get(float x) const
{
    if (!_compiled.empty())
    {
        if (x >= _start && x <= _end)
        {
            return _compiled[(int)((x - _start) / _interval)];
        }
        else
        {
            return _default;
        }
    }
    else if(_func != nullptr)
    {
        return _func(x);
    }
    else
    {
        return _default;
    }
}

template<typename T>
void Graph<T>::compile(float start, float end, float interval)
{
    _compiled.clear();
    
    if ( _func == nullptr )
    {
        return;
    }
    
    if ( !_isNeedCompile )
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
void Graph<T>::setVector(const std::vector<T>& vec, float start, float end, float interval)
{
    _compiled = vec;
    _start = start;
    _end = end;
    _interval = interval;
}

template<typename T>
void Graph<T>::setDefault(const T& defaultValue)
{
    _default = defaultValue;
}

namespace
{
    //TODO: use binary insert stable sort
    template<typename T>
    bool graphPointComparisonLess(const T& a, const T& b)
    {
        return a.p.x < b.p.x;
    }
}

//LineGraph implementation
template<typename T>
void LineGraph<T>::add(const LineGraphPoint<T>& point)
{
    _points.push_back(point);
    std::sort(_points.begin(), _points.end(), graphPointComparisonLess<LineGraphPoint<T>>);
    Graph<T>::setNeedCompile(_points.size() > 1);
}

template<typename T>
void LineGraph<T>::add(float x, const T& y, int tag/* = 0*/)
{
    add(LineGraphPoint<T>(GraphPoint<T>(x, y), tag));
}

template<typename T>
void LineGraph<T>::removeByTag(int tag)
{
    for(auto it = _points.begin(); it != _points.end(); ++it)
    {
        if(it->tag == tag)
        {
            _points.erase(it);
            break;
        }
    }
    Graph<T>::setNeedCompile(_points.size() > 1);
}

template<typename T>
void LineGraph<T>::removeByIndex(int index)
{
    if (index >= 0 && index < _points.size())
    {
        _points.erase(_points.begin() + index);
    }
    Graph<T>::setNeedCompile(_points.size() > 1);
}

template<typename T>
T LineGraph<T>::compute(float x)
{
    // return default when empty
    if (_points.empty())
    {
        return Graph<T>::_default;
    }
    
    // only one value
    if(_points.size() == 1)
    {
        return _points[0].p.y;
    }
    
    // find the area of x
    int a = -1, b = -1;
    for(int i = 0; i < _points.size(); ++i)
    {
        if ( x == _points[i].p.x)
        {
            return _points[i].p.y;
        }
        else if (x > _points[i].p.x)
        {
            a = i;
        }
        else
        {
            b = i;
            break;
        }
    }

    // x < min
    if (a == -1)
    {
        return _points[0].p.y;
    }
    
    // x > max
    if(b == -1)
    {
        return _points[_points.size() - 1].p.y;
    }
    
    return linear_bezier(_points[a].p.x, _points[a].p.y, _points[b].p.x, _points[b].p.y, x);
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

// BezierGraph implementation
template<typename T>
BezierGraph<T>* BezierGraph<T>::create()
{
    auto ret = new BezierGraph<T>();
    if (ret != nullptr && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

template<typename T>
void BezierGraph<T>::add(float x, const T& y, int tag)
{
    add(x, y, 0.0f, T(), 0.0f, T(), tag, BezierGraphPointType::LINE);
}

template<typename T>
void BezierGraph<T>::add(float x, const T& y, float cx, const T& cy, int tag/* = 0*/, int type/* = BezierGraphPointType::LCURVE*/)
{
    if (type == BezierGraphPointType::LINE)
    {
        add(x, y, tag);
    }
    else if(type == BezierGraphPointType::LCURVE)
    {
        add(x, y, cx, cy, 0.0f, T(), tag, type);
    }
    else if(type == BezierGraphPointType::RCURVE)
    {
        add(x, y, 0.0f, T(), cx, cy, tag, type);
    }
    else
    {
        CCASSERT(false, "unsupport type");
    }
}

template<typename T>
void BezierGraph<T>::add(float x, const T& y, float lx, const T& ly, float rx, const T& ry, int tag/* = 0*/, int type/* = BezierGraphPointType::CURVE*/)
{
    _points.push_back(BezierGraphPoint<T>(GraphPoint<T>(x, y), GraphPoint<T>(lx, ly), GraphPoint<T>(rx, ry), tag, type));
    std::sort(_points.begin(), _points.end(), graphPointComparisonLess<BezierGraphPoint<T>>);
    Graph<T>::setNeedCompile(_points.size() > 1);
}

template<typename T>
T BezierGraph<T>::compute(float x)
{
    
    // return default when empty
    if (_points.empty())
    {
        return Graph<T>::_default;
    }
    
    // only one value
    if(_points.size() == 1)
    {
        return _points[0].p.y;
    }
    
    // find the area of x
    int a = -1, b = -1;
    for(int i = 0; i < _points.size(); ++i)
    {
        if ( x == _points[i].p.x)
        {
            return _points[i].p.y;
        }else if (x > _points[i].p.x)
        {
            a = i;
        }
        else
        {
            b = i;
            break;
        }
    }
    
    // x < min
    if (a == -1)
    {
        return _points[0].p.y;
    }
    
    // x > max
    if(b == -1)
    {
        return _points[_points.size() - 1].p.y;
    }
    
    if ((_points[a].t & BezierGraphPointType::RCURVE) == 0
        && (_points[b].t & BezierGraphPointType::LCURVE) == 0)
    {
        return linear_bezier(_points[a].p.x, _points[a].p.y,
                             _points[b].p.x, _points[b].p.y,
                             x);
    }
    else if((_points[a].t & BezierGraphPointType::RCURVE) != 0
            && (_points[b].t & BezierGraphPointType::LCURVE) == 0)
    {
        return quadratic_bezier(_points[a].p.x, _points[a].p.y,
                                _points[a].r.x, _points[a].r.y,
                                _points[b].p.x, _points[b].p.y,
                                x);
    }
    else if((_points[a].t & BezierGraphPointType::RCURVE) == 0
            && (_points[b].t & BezierGraphPointType::LCURVE) != 0)
    {
        return quadratic_bezier(_points[a].p.x, _points[a].p.y,
                                _points[b].r.x, _points[b].r.y,
                                _points[b].p.x, _points[b].p.y,
                                x);
    }
    else if((_points[a].t & BezierGraphPointType::RCURVE) != 0
            && (_points[b].t & BezierGraphPointType::LCURVE) != 0)
    {
        return cubics_bezier(_points[a].p.x, _points[a].p.y,
                             _points[a].r.x, _points[a].r.y,
                             _points[b].l.x, _points[b].l.y,
                             _points[b].p.x, _points[b].p.y,
                             x);
    }
    else
    {
        CCASSERT(false, "won't happen");
        return T();
    }
}

template<typename T>
bool BezierGraph<T>::init()
{
    Graph<T>::setFunc(std::bind(&BezierGraph<T>::compute, this, std::placeholders::_1));
    
    return true;
}

NS_CC_END

#endif /* defined(__cocos2d_libs__CCGraphImplement__) */
