/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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
#elif ENABLE_PHYSICS_BOX2D_DETECT
#include "Box2D/Box2D.h"
#endif


namespace cocostudio {

class Bone;

/**
 *  @js NA
 *  @lua NA
 */
class ColliderFilter
{
public:
    virtual ~ColliderFilter() { }
#if ENABLE_PHYSICS_BOX2D_DETECT
public:
    ColliderFilter(uint16 categoryBits = 0x0001, uint16 maskBits = 0xFFFF, int16 groupIndex = 0);
    void updateShape(b2Fixture *fixture);

    virtual void setCategoryBits(uint16 categoryBits) { _categoryBits = categoryBits; }
    virtual uint16 getCategoryBits() const { return _categoryBits; }

    virtual void setMaskBits(uint16 maskBits) { _maskBits = maskBits; }
    virtual uint16 getMaskBits() const { return _maskBits; }

    virtual void setGroupIndex(int16 groupIndex) { _groupIndex = groupIndex; }
    virtual int16 getGroupIndex() const { return _groupIndex; }
protected:
    uint16 _categoryBits;
    uint16 _maskBits;
    int16 _groupIndex;
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
public:
    ColliderFilter(cpCollisionType collisionType = 0, cpGroup group = 0);
    void updateShape(cpShape *shape);

    virtual void setCollisionType(cpCollisionType collisionType) { _collisionType = collisionType; }
    virtual cpCollisionType getCollisionType() const { return _collisionType; }

    virtual void setGroup(cpGroup group) { _group = group; }
    virtual cpGroup getGroup() const { return _group; }
protected:
    cpCollisionType _collisionType;
    cpGroup _group;
#endif
};

class ColliderBody : public cocos2d::Object
{
public:
    ColliderBody(ContourData *contourData);
    ~ColliderBody();

    inline ContourData *getContourData() { return _contourData; }

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT 
    void setColliderFilter(ColliderFilter *filter);
    ColliderFilter *getColliderFilter();
#endif

#if ENABLE_PHYSICS_BOX2D_DETECT
    virtual void setB2Fixture(b2Fixture *fixture) { _fixture = fixture; }
    virtual b2Fixture *getB2Fixture() const { return _fixture; }
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
    virtual void setShape(cpShape *shape) { _shape = shape; }
    virtual cpShape *getShape() const { return _shape; }
#elif ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    virtual const std::vector<cocos2d::Point> &getCalculatedVertexList() const { return _calculatedVertexList; }
#endif

private:

#if ENABLE_PHYSICS_BOX2D_DETECT
    b2Fixture *_fixture;
    ColliderFilter *_filter;
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
    cpShape *_shape;
    ColliderFilter *_filter;
#elif ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    std::vector<cocos2d::Point> _calculatedVertexList;
#endif

    ContourData *_contourData;

    friend class ColliderDetector;
};

/*
 *  @brief  ContourSprite used to draw the contour of the display
 *  @js NA
 *  @lua NA
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
    void addContourDataList(cocos2d::Vector<ContourData*> &contourDataList);

    void removeContourData(ContourData *contourData);
    void removeAll();

    void updateTransform(kmMat4 &t);

    void setActive(bool active);
    bool getActive();

    const cocos2d::Vector<ColliderBody*>& getColliderBodyList();

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT 
    virtual void setColliderFilter(ColliderFilter *filter);
    virtual ColliderFilter *getColliderFilter();
#endif

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
    cocos2d::Vector<ColliderBody*> _colliderBodyList;

    Bone *_bone;

#if ENABLE_PHYSICS_BOX2D_DETECT
    b2Body *_body;
    ColliderFilter *_filter;
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
    cpBody *_body;
    ColliderFilter *_filter;
#endif

protected:
    bool _active;
};

}

#endif /*__CCCOLLIDERDETECTOR_H__*/
