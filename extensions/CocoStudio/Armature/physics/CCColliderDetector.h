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

#ifndef __CCCOLLIDERDETECTOR_H__
#define __CCCOLLIDERDETECTOR_H__

#include "../utils/CCArmatureDefine.h"
#include "../datas/CCDatas.h"

#ifndef PT_RATIO
#define PT_RATIO 32
#endif


class b2Body;
class b2Fixture;
struct b2Filter;

struct cpBody;
struct cpShape;

NS_CC_EXT_BEGIN

class CCBone;
/**
*   @js NA
*   @lua NA
*/
class ColliderBody : public CCObject
{
public:
#if ENABLE_PHYSICS_BOX2D_DETECT
    CC_SYNTHESIZE(b2Fixture *, m_pFixture, B2Fixture)
    CC_SYNTHESIZE(b2Filter *, m_pFilter, B2Filter)

#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
    CC_SYNTHESIZE(cpShape *, m_pShape, Shape)
#endif

public:
    ColliderBody(CCContourData *contourData);
    ~ColliderBody();

    inline CCContourData *getContourData()
    {
        return m_pContourData;
    }
private:
    CCContourData *m_pContourData;
};

/*
 *  @brief  ContourSprite used to draw the contour of the display
 *  @js NA
 *  @lua NA
 */
class CCColliderDetector : public CCObject
{
public:
    static CCColliderDetector *create();
    static CCColliderDetector *create(CCBone *bone);
public:
    CCColliderDetector();
    ~CCColliderDetector(void);

    virtual bool init();
    virtual bool init(CCBone *bone);

    void addContourData(CCContourData *contourData);
    void addContourDataList(CCArray *contourDataList);

    void removeContourData(CCContourData *contourData);
    void removeAll();

    void updateTransform(CCAffineTransform &t);

    void setActive(bool active);
    bool getActive();

    CCArray *getColliderBodyList();

protected:
    CCArray *m_pColliderBodyList;
    CC_SYNTHESIZE(CCBone *, m_pBone, Bone);

#if ENABLE_PHYSICS_BOX2D_DETECT
    CC_PROPERTY(b2Body *, m_pBody, Body);
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
    CC_PROPERTY(cpBody *, m_pBody, Body);
#endif

protected:
    bool m_bActive;
};

NS_CC_EXT_END

#endif /*__CCCOLLIDERDETECTOR_H__*/
