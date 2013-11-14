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
    virtual ~ColliderFilter() { }
#if ENABLE_PHYSICS_BOX2D_DETECT
public:
    ColliderFilter(unsigned short categoryBits = 0x0001, unsigned short maskBits = 0xFFFF, signed short groupIndex = 0);
    void updateShape(b2Fixture *fixture);

    virtual void setCategoryBits(unsigned short categoryBits) { _categoryBits = categoryBits; }
    virtual unsigned short getCategoryBits() const { return _categoryBits; }

    virtual void setMaskBits(unsigned short maskBits) { _maskBits = maskBits; }
    virtual unsigned short getMaskBits() const { return _maskBits; }

    virtual void setGroupIndex(signed short groupIndex) { _groupIndex = groupIndex; }
    virtual signed short getGroupIndex() const { return _groupIndex; }
protected:
    unsigned short _categoryBits;
    unsigned short _maskBits;
    signed short _groupIndex;
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
public:
    ColliderFilter(uintptr_t collisionType = 0, uintptr_t group = 0);
    void updateShape(cpShape *shape);

    virtual void setCollisionType(uintptr_t collisionType) { _collisionType = collisionType; }
    virtual uintptr_t getCollisionType() const { return _collisionType; }

    virtual void setGroup(uintptr_t group) { _group = group; }
    virtual uintptr_t getGroup() const { return _group; }
protected:
    uintptr_t _collisionType;
    uintptr_t _group;
#endif
};

class ColliderBody : public cocos2d::Object
{
public:
    ColliderBody(ContourData *contourData);
    ~ColliderBody();

    inline ContourData *getContourData() { return _contourData; }

    void setColliderFilter(ColliderFilter *filter);
    ColliderFilter *getColliderFilter();

#if ENABLE_PHYSICS_BOX2D_DETECT
    virtual void setB2Fixture(b2Fixture *fixture) { _fixture = fixture; }
    virtual b2Fixture *getB2Fixture() const { return _fixture; }
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
    virtual void setShape(cpShape *shape) { _shape = shape; }
    virtual cpShape *getShape() const { return _shape; }
#endif

#if ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    virtual const cocos2d::Array *getCalculatedVertexList() const { return _calculatedVertexList; }
#endif
private:

#if ENABLE_PHYSICS_BOX2D_DETECT
    b2Fixture *_fixture;
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
    cpShape *_shape;
#endif

    ContourData *_contourData;
    ColliderFilter *_filter;

#if ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    cocos2d::Array *_calculatedVertexList;
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

    virtual void setBone(Bone *bone) { _bone = bone; }
    virtual Bone *getBone() const { return _bone; }

#if ENABLE_PHYSICS_BOX2D_DETECT
    virtual void setBody(b2Body *body);
    virtual b2Body *getBody() const;
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
    virtual void setBody(cpBody *body);
    virtual cpBody *getBody() const;
#endif
 protected:
    cocos2d::Array *_colliderBodyList;
    ColliderFilter *_filter;

    Bone *_bone;

#if ENABLE_PHYSICS_BOX2D_DETECT
    b2Body *_body;
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
    cpBody *_body;
#endif

protected:
    bool _active;
};

}

#endif /*__CCCOLLIDERDETECTOR_H__*/
