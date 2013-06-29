/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#include "CCDecorativeDisplay.h"
#include "../utils/CCConstValue.h"

namespace cocos2d { namespace extension { namespace armature {

DecorativeDisplay *DecorativeDisplay::create()
{
    DecorativeDisplay *pDisplay = new DecorativeDisplay();
    if (pDisplay && pDisplay->init())
    {
        pDisplay->autorelease();
        return pDisplay;
    }
    CC_SAFE_DELETE(pDisplay);
    return NULL;
}

DecorativeDisplay::DecorativeDisplay()
    : _display(NULL)
    , _displayData(NULL)

{
#if ENABLE_PHYSICS_DETECT
    _colliderDetector = NULL;
#endif
}


DecorativeDisplay::~DecorativeDisplay(void)
{
    CC_SAFE_RELEASE_NULL(_displayData);
    CC_SAFE_RELEASE_NULL(_display);

#if ENABLE_PHYSICS_DETECT
    CC_SAFE_RELEASE_NULL(_colliderDetector);
#endif
}

bool DecorativeDisplay::init()
{
    return true;
}


void DecorativeDisplay::anchorPointChanged(float pointX, float pointY)
{
}

}}} // namespace cocos2d { namespace extension { namespace armature {
