/****************************************************************************
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

#ifndef __UISCROLLDELEGATE_H__
#define __UISCROLLDELEGATE_H__

#include "gui/UIWidget.h"

NS_CC_BEGIN

namespace gui {

class UIScrollInterface
{
public:
    virtual ~UIScrollInterface() {}

protected:
    virtual void handlePressLogic(const Point &touchPoint) = 0;
    virtual void handleMoveLogic(const Point &touchPoint) = 0;
    virtual void handleReleaseLogic(const Point &touchPoint) = 0;
    virtual void interceptTouchEvent(int handleState, Widget* sender, const Point &touchPoint) = 0;
};

}
NS_CC_END

#endif /* defined(__UIScrollDelegate__) */
