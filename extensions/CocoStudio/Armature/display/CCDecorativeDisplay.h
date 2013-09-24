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

#ifndef __CCDECORATIVEDISPLAY_H__
#define __CCDECORATIVEDISPLAY_H__

#include "../utils/CCArmatureDefine.h"
#include "CCDisplayFactory.h"
#include "../datas/CCDatas.h"


#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
#include "../physics/CCColliderDetector.h"
#endif

NS_CC_EXT_BEGIN
/**
*   @js NA
*   @lua NA
*/
class  CCDecorativeDisplay: public CCObject
{
public:
    static CCDecorativeDisplay *create();
public:
    CCDecorativeDisplay(void);
    ~CCDecorativeDisplay(void);

    virtual bool init();

protected:

    CC_SYNTHESIZE_RETAIN(CCNode *, m_pDisplay, Display);
    CC_SYNTHESIZE_RETAIN(CCDisplayData *, m_pDisplayData, DisplayData);

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
    CC_SYNTHESIZE_RETAIN(CCColliderDetector *, m_pColliderDetector, ColliderDetector);
#endif
};

NS_CC_EXT_END

#endif /*__CCDECORATIVEDISPLAY_H__*/
