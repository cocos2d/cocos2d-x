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

#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCDatas.h"

#ifndef PT_RATIO
#define PT_RATIO 32
#endif


#if ENABLE_PHYSICS_CHIPMUNK_DETECT
#include "chipmunk.h"
struct cpBody;
struct cpShape;
#elif ENABLE_PHYSICS_BOX2D_DETECT
class b2Body;
class b2Fixture;
struct b2Filter;
#endif

namespace cocostudio {

class Bone;


class ColliderFilter
{
public:
    ~ColliderFilter() { }
#if ENABLE_PHYSICS_BOX2D_DETECT
public:
    ColliderFilter(unsigned short categoryBits = 0x0001, unsigned short maskBits = 0xFFFF, signed short groupIndex = 0);
    void updateShape(b2Fixture *fixture);
protected:
    CC_SYNTHESIZE(unsigned short, _categoryBits, CategoryBits);
    CC_SYNTHESIZE(unsigned short, _maskBits, MaskBits);
    CC_SYNTHESIZE(signed short, _groupIndex, GroupIndex);
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
public:
    ColliderFilter(cpCollisionType collisionType = 0, cpGroup group = 0);
    void updateShape(cpShape *shape);
protected:
    CC_SYNTHESIZE(cpCollisionType, _collisionType, CollisionType);
    CC_SYNTHESIZE(cpGroup, _group, Group);
#endif
};

class ColliderBody : public cocos2d::Object
{
public:
#if ENABLE_PHYSICS_BOX2D_DETECT
    CC_SYNTHESIZE(b2Fixture *, _fixture, B2Fixture)
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
    CC_SYNTHESIZE(cpShape *, _shape, Shape)
#endif

public:
    ColliderBody(ContourData *contourData);
    ~ColliderBody();

    inline ContourData *getContourData() { return _contourData; }

    void setColliderFilter(ColliderFilter *filter);
    ColliderFilter *getColliderFilter();
private:
    ContourData *_contourData;
    ColliderFilter *_filter;

#if ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    CC_SYNTHESIZE_READONLY(CCArray *, _calculatedVertexList, CalculatedVertexList);
#endif
};

/*
 *  @brief  ContourSprite used to draw the contour of the display
 */
class ColliderDetector : public cocos2d::Object
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
    void addContourDataList(cocos2d::Array *contourDataList);

    void removeContourData(ContourData *contourData);
    void removeAll();

    void updateTransform(cocos2d::AffineTransform &t);

    void setActive(bool active);
    bool getActive();

    cocos2d::Array *getColliderBodyList();

    virtual void setColliderFilter(ColliderFilter *filter);
    virtual ColliderFilter *getColliderFilter();
protected:
    cocos2d::Array *_colliderBodyList;
    ColliderFilter *_filter;

    CC_SYNTHESIZE(Bone *, _bone, Bone);

#if ENABLE_PHYSICS_BOX2D_DETECT
    CC_PROPERTY(b2Body *, _body, Body);
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
    CC_PROPERTY(cpBody *, _body, Body);
#endif

protected:
    bool _active;
};

}

#endif /*__CCCOLLIDERDETECTOR_H__*/
