/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "CCObject.h"
#include "CCGeometry.h"

namespace cocos2d {

class CCTouch : public CCObject
{
public:
    CCTouch() {}
    CCTouch(float x, float y) :  m_point(x, y), m_prevPoint(x, y) {}

    CCPoint locationInView() { return m_point; }
    CCPoint previousLocationInView() { return m_prevPoint; }

    void SetTouchInfo(float x, float y)
    {
        m_prevPoint = m_point;
        m_point.x   = x;
        m_point.y   = y;
    }

private:
    CCPoint m_point;
    CCPoint	m_prevPoint;
};

class CCEvent : public CCObject
{
};

}       // end of namespace cocos2d

#endif  // __PLATFORM_TOUCH_H__
