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
#include "cocostudio/CocosStudioExport.h"

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
class CC_STUDIO_DLL ColliderFilter
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

class CC_STUDIO_DLL ColliderBody : public cocos2d::Ref
{
public:
    ColliderBody(ContourData *contourData);
    ~ColliderBody();

    /*
    * @~english Get contour data.
    * @~chinese 获取轮廓数据。
    * @return @~english Contour data.
    * @~chinese 轮廓数据。
    */
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

    /*
    * @~english Get calculated vertex list.
    * @~chinese 获取顶点列表。
    * @return @~english Calculated vertex list.
    * @~chinese 顶点列表。
    */
    virtual const std::vector<cocos2d::Vec2> &getCalculatedVertexList() const { return _calculatedVertexList; }
#endif

private:

#if ENABLE_PHYSICS_BOX2D_DETECT
    b2Fixture *_fixture;
    ColliderFilter *_filter;
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
    cpShape *_shape;
    ColliderFilter *_filter;
#elif ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    std::vector<cocos2d::Vec2> _calculatedVertexList;
#endif

    ContourData *_contourData;

    friend class ColliderDetector;
};

/*
 *  @brief  @~english ContourSprite used to draw the contour of the display
 * @~chinese 轮廓精灵用来绘制显示的轮廓。
 *  @js NA
 *  @lua NA
 */
class CC_STUDIO_DLL ColliderDetector : public cocos2d::Ref
{
public:

    /**
    * @~english Allocates and initializes a ColliderDetector.
    * @~chinese 分配并且初始化碰撞检测器。
    * @return @~english An initialized ColliderDetector which is marked as "autorelease".
    * @~chinese 初始化的碰撞检测器，会自动被标记为“autorelease”（自动释放）。
    */
    static ColliderDetector *create();

    /**
    * @~english Allocates and initializes a ColliderDetector by a bone.
    * @~chinese 使用一段骨头分配并且初始化碰撞检测器。
    * @param bone  @~english A bone for initialize the ColliderDetector.
    * @~chinese 初始化碰撞检测器的骨头。
    * @return @~english An initialized ColliderDetector which is marked as "autorelease".
    * @~chinese 初始化的碰撞检测器，会自动被标记为“autorelease”（自动释放）。
    */
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

    /**
    * @~english Init ColliderDetector.
    * @~chinese 初始化碰撞检测器。
    * @return @~english Is initialize succeed.
    * @~chinese 是否初始化成功。
    */
    virtual bool init();

    /**
    * @~english Init ColliderDetector by a bone.
    * @~chinese 是用一段骨头初始化碰撞检测器。
    * @param bone @~english A bone for initialize the ColliderDetector.
    * @~chinese 初始化碰撞检测器的骨头。
    * @return @~english Is initialize succeed.
    * @~chinese 是否初始化成功。
    */
    virtual bool init(Bone *bone);

    /**
    * @~english Add contour data to the ColliderDetector.
    * @~chinese 为碰撞检测器添加轮廓数据。
    * @param contourData @~english The contour data to be added.
    * @~chinese 要添加的轮廓数据。
    */
    void addContourData(ContourData *contourData);

    /**
    * @~english Add contour datas to the ColliderDetector.
    * @~chinese 为碰撞检测器添加一组轮廓数据。
    * @param contourData @~english The contour datas to be added.
    * @~chinese 要添加的一组轮廓数据。
    */
    void addContourDataList(cocos2d::Vector<ContourData*> &contourDataList);

    /**
    * @~english Remove a contour data.
    * @~chinese 移除轮廓数据。
    * @param contourData @~english The contour data to be removed.
    * @~chinese 要移除的轮廓数据。
    */
    void removeContourData(ContourData *contourData);

    /**
    * @~english Remove all contour data.
    * @~chinese 移除所有轮廓数据。
    */
    void removeAll();

    /**
    * @~english Returns the armature affine transform matrix. The matrix is in Pixels.
    * @~chinese 使用变换矩阵仿射轮廓数据。矩阵单位是像素。
    * @param t @~english Transformation matrix, in pixels.
    * @~chinese 变换矩阵。
    */
    void updateTransform(cocos2d::Mat4 &t);

    /**
    * @~english Set is the ColliderDetector active.
    * @~chinese 设置碰撞检测器是否激活。
    * @param active @~english Is the ColliderDetector active.
    * @~chinese 是否激活。
    */
    void setActive(bool active);
    /**
    * @~english Get is the ColliderDetector active.
    * @~chinese 获取碰撞检测器是否激活。
    * @return @~english Is the ColliderDetector active.
    * @~chinese 是否激活。
    */
    bool getActive();

    /**
    * @~english Get the collider bodies.
    * @~chinese 获取碰撞体列表。
    * @return @~english Collider bodies.
    * @~chinese 碰撞体列表。
    */
    const cocos2d::Vector<ColliderBody*>& getColliderBodyList();

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT 
    virtual void setColliderFilter(ColliderFilter *filter);
    virtual ColliderFilter *getColliderFilter();
#endif

    /**
    * @~english Set the bone.
    * @~chinese 设置骨头。
    * @param bone @~english The bone.
    * @~chinese 骨头。
    */
    virtual void setBone(Bone *bone) { _bone = bone; }

    /**
    * @~english Get the bone.
    * @~chinese 获取骨头。
    * @return @~english The bone.
    * @~chinese 骨头。
    */
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
