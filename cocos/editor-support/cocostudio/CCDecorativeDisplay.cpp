/****************************************************************************
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#include "editor-support/cocostudio/CCDecorativeDisplay.h"
#include "2d/CCNode.h"

using namespace cocos2d;

namespace cocostudio {

DecorativeDisplay *DecorativeDisplay::create()
{
    DecorativeDisplay *pDisplay = new (std::nothrow) DecorativeDisplay();
    if (pDisplay && pDisplay->init())
    {
        pDisplay->autorelease();
        return pDisplay;
    }
    CC_SAFE_DELETE(pDisplay);
    return nullptr;
}

DecorativeDisplay::DecorativeDisplay()
    : _display(nullptr)
    , _displayData(nullptr)

{
#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT || ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    _colliderDetector = nullptr;
#endif
}


DecorativeDisplay::~DecorativeDisplay(void)
{
    CC_SAFE_RELEASE_NULL(_displayData);
    CC_SAFE_RELEASE_NULL(_display);

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT || ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    CC_SAFE_RELEASE_NULL(_colliderDetector);
#endif
}

bool DecorativeDisplay::init()
{
    return true;
}

void DecorativeDisplay::setDisplay(cocos2d::Node *display)
{
    if (_display != display)
    {
        CC_SAFE_RETAIN(display);
        CC_SAFE_RELEASE(_display);
        _display = display;
    }
}
    
}
