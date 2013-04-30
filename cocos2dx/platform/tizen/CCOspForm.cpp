/****************************************************************************
Copyright (c) 2013 cocos2d-x.org
Copyright (c) 2013 Lee, Jae-Hong

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

#include "CCOspForm.h"
#include "CCDirector.h"
#include "CCEGLView.h"

USING_NS_CC;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;

result
CCOspForm::OnInitializing(void)
{
    AddTouchEventListener(*this);
    SetMultipointTouchEnabled(true);

    return E_SUCCESS;
}

void
CCOspForm:: OnTouchDoublePressed(const Control& source, const Point& currentPosition, const TouchEventInfo& touchInfo)
{
}

void
CCOspForm:: OnTouchFocusIn(const Control& source, const Point& currentPosition, const TouchEventInfo& touchInfo)
{
}

void
CCOspForm::OnTouchFocusOut(const Control& source, const Point& currentPosition, const TouchEventInfo& touchInfo)
{
}

void
CCOspForm::OnTouchLongPressed(const Control& source, const Point& currentPosition, const TouchEventInfo& touchInfo)
{
}

void
CCOspForm::OnTouchMoved(const Control& source, const Point& currentPosition, const TouchEventInfo& touchInfo)
{
    int id = touchInfo.GetPointId();
    float x = currentPosition.x;
    float y = currentPosition.y;
    CCDirector::sharedDirector()->getOpenGLView()->handleTouchesMove(1, &id, &x, &y);
}

void
CCOspForm::OnTouchPressed(const Control& source, const Point& currentPosition, const TouchEventInfo& touchInfo)
{
    int id = touchInfo.GetPointId();
    float x = currentPosition.x;
    float y = currentPosition.y;
    CCDirector::sharedDirector()->getOpenGLView()->handleTouchesBegin(1, &id, &x, &y);
}

void
CCOspForm::OnTouchReleased(const Control& source, const Point& currentPosition, const TouchEventInfo& touchInfo)
{
    int id = touchInfo.GetPointId();
    float x = currentPosition.x;
    float y = currentPosition.y;
    CCDirector::sharedDirector()->getOpenGLView()->handleTouchesEnd(1, &id, &x, &y);
}
