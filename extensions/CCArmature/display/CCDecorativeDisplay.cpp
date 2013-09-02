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

NS_CC_EXT_BEGIN

CCDecorativeDisplay *CCDecorativeDisplay::create()
{
    CCDecorativeDisplay *pDisplay = new CCDecorativeDisplay();
    if (pDisplay && pDisplay->init())
    {
        pDisplay->autorelease();
        return pDisplay;
    }
    CC_SAFE_DELETE(pDisplay);
    return NULL;
}

CCDecorativeDisplay::CCDecorativeDisplay()
    : m_pDisplay(NULL)
    , m_pDisplayData(NULL)

{
#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
    m_pColliderDetector = NULL;
#endif
}


CCDecorativeDisplay::~CCDecorativeDisplay(void)
{
    CC_SAFE_RELEASE_NULL(m_pDisplayData);
    CC_SAFE_RELEASE_NULL(m_pDisplay);

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
    CC_SAFE_RELEASE_NULL(m_pColliderDetector);
#endif
}

bool CCDecorativeDisplay::init()
{
    return true;
}

NS_CC_EXT_END
