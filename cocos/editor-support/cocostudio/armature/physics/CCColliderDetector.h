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

NS_CC_EXT_ARMATURE_BEGIN

class Bone;

class ColliderBody : public Object
{
public:
#if ENABLE_PHYSICS_BOX2D_DETECT
    CC_SYNTHESIZE(b2Fixture *, _fixture, B2Fixture)
    CC_SYNTHESIZE(b2Filter *, _filter, B2Filter)

#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
    CC_SYNTHESIZE(cpShape *, _shape, Shape)
#endif

public:
    ColliderBody(ContourData *contourData);
    ~ColliderBody();

    inline ContourData *getContourData()
    {
        return _contourData;
    }
private:
    ContourData *_contourData;
};

/*
 *  @brief  ContourSprite used to draw the contour of the display
 */
class ColliderDetector : public Object
{
public:
    static ColliderDetector *create();
    static ColliderDetector *create(Bone *bone);
public:
	/**
     * @js ctor
     */
    ColliderDetector();
    /**
     * @js NA
     * @lua NA
     */
    ~ColliderDetector(void);

    virtual bool init();
    virtual bool init(Bone *bone);

    void addContourData(ContourData *contourData);
    void addContourDataList(Array *contourDataList);

    void removeContourData(ContourData *contourData);
    void removeAll();

    void updateTransform(AffineTransform &t);

    void setActive(bool active);
    bool getActive();

    Array *getColliderBodyList();

protected:
    Array *_colliderBodyList;
    CC_SYNTHESIZE(Bone *, _bone, Bone);

#if ENABLE_PHYSICS_BOX2D_DETECT
    CC_PROPERTY(b2Body *, _body, Body);
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
    CC_PROPERTY(cpBody *, _body, Body);
#endif

protected:
    bool _active;
};

NS_CC_EXT_ARMATURE_END

#endif /*__CCCOLLIDERDETECTOR_H__*/
