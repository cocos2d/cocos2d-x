/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef __CC_TOUCH_H__
#define __CC_TOUCH_H__

#include "base/CCRef.h"
#include "math/CCGeometry.h"

NS_CC_BEGIN

/**
 * @addtogroup input
 * @{
 */

class CC_DLL Touch : public Ref
{
public:
    /** how the touches are dispathced */
    enum class DispatchMode {
        /** All at once */
        ALL_AT_ONCE,
        /** one by one */
        ONE_BY_ONE,
    };

    Touch() 
        : _id(0),
        _startPointCaptured(false)
    {}

    /** returns the current touch location in OpenGL coordinates */
    Vec2 getLocation() const;
    /** returns the previous touch location in OpenGL coordinates */
    Vec2 getPreviousLocation() const;
    /** returns the start touch location in OpenGL coordinates */
    Vec2 getStartLocation() const;
    /** returns the delta of 2 current touches locations in screen coordinates */
    Vec2 getDelta() const;
    /** returns the current touch location in screen coordinates */
    Vec2 getLocationInView() const;
    /** returns the previous touch location in screen coordinates */
    Vec2 getPreviousLocationInView() const;
    /** returns the start touch location in screen coordinates */
    Vec2 getStartLocationInView() const;
    
    void setTouchInfo(int id, float x, float y)
    {
        _id = id;
        _prevPoint = _point;
        _point.x   = x;
        _point.y   = y;
        if (!_startPointCaptured)
        {
            _startPoint = _point;
            _startPointCaptured = true;
        }
    }
    /**
     * @js getId
     * @lua getId
     */
    int getID() const
    {
        return _id;
    }

private:
    int _id;
    bool _startPointCaptured;
    Vec2 _startPoint;
    Vec2 _point;
    Vec2 _prevPoint;
};

// end of input group
/// @}

NS_CC_END

#endif  // __PLATFORM_TOUCH_H__
