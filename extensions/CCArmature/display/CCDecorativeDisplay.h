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
#include "../external_tool/sigslot.h"


#if ENABLE_PHYSICS_DETECT
#include "../physics/CCColliderDetector.h"
#endif

namespace cocos2d { namespace extension { namespace armature {

class  CCDecorativeDisplay: public CCObject, public sigslot::has_slots<>
{
public:
    static CCDecorativeDisplay *create();
public:
    CCDecorativeDisplay(void);
    ~CCDecorativeDisplay(void);

    virtual bool init();

protected:

    CC_SYNTHESIZE_RETAIN(CCNode *, _display, Display);
    CC_SYNTHESIZE_RETAIN(CCDisplayData *, _displayData, DisplayData);

#if ENABLE_PHYSICS_DETECT
    CC_SYNTHESIZE_RETAIN(CCColliderDetector *, _colliderDetector, ColliderDetector);
#endif
public:
    void anchorPointChanged(float pointX, float pointY);
};

}}} // namespace cocos2d { namespace extension { namespace armature {

#endif /*__CCDECORATIVEDISPLAY_H__*/
