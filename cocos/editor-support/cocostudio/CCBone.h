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

#ifndef __CCBONE_H__
#define __CCBONE_H__

#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCDatas.h"
#include "cocostudio/CCTween.h"
#include "cocostudio/CCDecorativeDisplay.h"
#include "cocostudio/CCDisplayManager.h"
#include "cocostudio/CocosStudioExport.h"
#include "2d/CCNode.h"
#include "math/CCMath.h"

namespace cocostudio {

class Armature;

class CC_STUDIO_DLL Bone : public cocos2d::Node
{
public:
    /**
    * @~english Allocates and initializes a bone.
    * @~chinese 分配并初始化一个骨头对象。
    * @return @~english An initialized bone which is marked as "autorelease".
    * @~chinese 一个初始化并且设置为自动释放的骨头对象。
    */
    static Bone *create();

    /**
    * @~english Allocates and initializes a bone.
    * @~chinese 分配并初始化一个骨头对象。
    * @param name  @~english If name is not null, then set name to the bone's name.
    * @~chinese 如果非空，则将该参数设为骨头的名称。
    * @return @~english An initialized bone which is marked as "autorelease".
    * @~chinese 一个初始化并且设置为自动释放的骨头对象。
    */
    static Bone *create(const std::string& name);

public:
    /**
     *  @js ctor
     */
    Bone();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Bone(void);
    virtual bool init() override;

    /**
     * @~english Initializes a Bone with the specified name.
     * @~chinese 以指定的名称初始化一段骨头。
     * @param name @~english Bone's name.
     * @~chinese 骨头的名称。
     */
    virtual bool init(const std::string& name);

    /**
     * @see DisplayManager::addDisplay(DisplayData *displayData, int index).
     */
    void addDisplay(DisplayData *displayData, int index);

    /**
    * @see DisplayManager::addDisplay(DisplayData *displayData, int index).
    */
    void addDisplay(cocos2d::Node *display, int index);

    /**
    * @see DisplayManager::removeDisplay(int index).
    */
    void removeDisplay(int index);

    /** @deprecated Use `changeDisplayWithIndex(int index, bool force)` instead */
    CC_DEPRECATED_ATTRIBUTE void changeDisplayByIndex(int index, bool force);
    /** @deprecated Use `changeDisplayWithName(const std::string& name, bool force)` instead */
    CC_DEPRECATED_ATTRIBUTE void changeDisplayByName(const std::string& name, bool force);

    /** @see `DisplayManager::changeDisplayWithIndex(int index, bool force)` */
    void changeDisplayWithIndex(int index, bool force);
    /** @see `DisplayManager::changeDisplayWithName(const std::string& name, bool force)` */
    void changeDisplayWithName(const std::string& name, bool force);

    /**
     * @~english Add a child to this bone, and it will let this child call `setParent(Bone *parent)` function to set self to it's parent
     * @~chinese 为当前骨头添加一段子骨头，同时该子骨头会调用`setParent(Bone *parent)`来将当前骨头设为其父骨头。
     * @param child @~english The child you want to add
     * @~chinese 要添加的子骨头。
     */
    void addChildBone(Bone *child);

    /**
     * @~english Set parent bone.
     * If parent is NUll, then also remove this bone from armature.
     * It will not set the Armature, if you want to add the bone to a Armature, you should use `Armature::addBone(Bone *bone, const char* parentName)`.
     * @~chinese 设置父骨头。如果父骨头参数为NULL，则将当前骨头从骨骼中移除。
     * 本函数不会对骨骼进行设置改变，如果要将骨头加入骨骼，应调用`Armature::addBone(Bone *bone, const char* parentName)`。
     * @param parent @~english the parent bone.
     *          nullptr : remove this bone from armature
     * @~chinese 父骨头，为nullptr时：将当前骨头从骨骼中移除。
     */
    void setParentBone(Bone *parent);

    /**
     * @~english Get parent bone
     * @~chinese 获取父骨头
     * @return @~english parent bone
     * @~chinese 父骨头
     */
    Bone *getParentBone();

    using Node::removeFromParent;
    /**
     * @~english Remove itself from its parent.
     * @~chinese 将当前骨头从父骨头中移除
     * @param recursion @~english   whether remove recursionly
     * @~chinese 是否递归移除
     */
    void removeFromParent(bool recursion);

    /**
     * @~english Removes a child Bone
     * @~chinese 将当前骨头从父骨头中移除
     * @param bone @~english  the bone you want to remove
     * @~chinese 要移除的骨头
     */
    void removeChildBone(Bone *bone, bool recursion);

    void update(float delta) override;

    void updateDisplayedColor(const cocos2d::Color3B &parentColor) override;
    void updateDisplayedOpacity(GLubyte parentOpacity) override;
    virtual void updateColor() override;

    /**
    * @~english Update zorder
    * @~chinese 更新Z排序
    */
    void updateZOrder();

    virtual void setLocalZOrder(int zOrder) override;

    /**
    * @~english Get tween of bone.
    * @~chinese 获取补间属性。
    * @return @~english Tween.
    * @~chinese 补间
    */
    Tween *getTween();

    /*
     * @~english Set whether or not the bone's transform property changed. if true, the bone will update the transform.
     * @~chinese 设置骨头的变形属性是否已改变，如果为真，骨头将会更新变形。
     * @param dirty @~english  Is the transform property changed.
     * @~chinese 是否改变。
     */
    virtual void setTransformDirty(bool dirty) { _boneTransformDirty = dirty; }

    /*
    * @~english Whether or not the bone's transform property changed.
    * @~chinese 骨头的变形属性是否已改变，如果为真，骨头将会更新变形。
    * @return @~english Is dirty.
    * @~chinese 是否已改变
    */
    virtual bool isTransformDirty() { return _boneTransformDirty; }

    /**
    * @~english Returns the armature affine transform matrix. The matrix is in Pixels.
    * @~chinese 返回节点到骨骼坐标仿射变换矩阵。矩阵单位是像素。
    * @return @~english Transformation matrix, in pixels. 
    * @~chinese 节点到骨骼坐标仿射变换矩阵。
    */
    virtual cocos2d::Mat4 getNodeToArmatureTransform() const;
    virtual cocos2d::Mat4 getNodeToWorldTransform() const override;

    /** @see `DisplayManager::getDisplayRenderNode()` */
    cocos2d::Node *getDisplayRenderNode();
    /** @see `DisplayManager::getDisplayRenderNodeType()` */
    DisplayType getDisplayRenderNodeType();

    /*
     * @~english Get the ColliderBody list in this bone. The object in the Array is ColliderBody.
     * @~chinese 获取骨头的碰撞体，数组中的对象为碰撞体。
     * @return @~english The ColliderBody list in this bone.
     * @~chinese 骨头的碰撞体。
     */
    virtual ColliderDetector* getColliderDetector() const;

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
    virtual void setColliderFilter(ColliderFilter *filter);
    virtual ColliderFilter *getColliderFilter();
#endif

    /*
    * @~english Set bone data.
    * @~chinese 设置骨头数据。
    * @param boneData @~english Bone data.
    * @~chinese 骨头数据。
    */
    virtual void setBoneData(BoneData *boneData);
    /*
    * @~english Get bone data.
    * @~chinese 获取骨头数据。
    * @return @~english Bone data.
    * @~chinese 骨头数据。
    */
    virtual BoneData *getBoneData() const;

    /*
    * @~english Set armature.
    * @~chinese 设置骨骼。
    * @param boneData @~english Armature.
    * @~chinese 骨骼。
    */
    virtual void setArmature(Armature *armature);
    /*
    * @~english Get armature.
    * @~chinese 获取骨骼。
    * @return @~english Armature.
    * @~chinese 骨骼。
    */
    virtual Armature *getArmature() const;

    /*
    * @~english Set child armature.
    * @~chinese 设置子骨骼。
    * @param boneData @~english Child armature.
    * @~chinese 子骨骼。
    */
    virtual void setChildArmature(Armature *childArmature);
    /*
    * @~english Get childe armature.
    * @~chinese 获取子骨骼。
    * @return @~english Child armature.
    * @~chinese 子骨骼。
    */
    virtual Armature *getChildArmature() const;

    /*
    * @~english Get display manager.
    * @~chinese 获取显示管理器。
    * @return @~english Display manager.
    * @~chinese 显示管理器。
    */
    virtual DisplayManager *getDisplayManager() const { return _displayManager; }

    /**
     * @lua NA
     * @~english Set whether or not ignore the movement bone data.
     * @~chinese 设置是否忽略活动骨头的数据。
     * @param ignore @~english  Is ignore.
     * @~chinese 是否忽略。
     */
    virtual void setIgnoreMovementBoneData(bool ignore) { _ignoreMovementBoneData = ignore; }
    /*
    * @~english Whether or not ignore the movement bone data.
    * @~chinese 是否忽略活动骨头的数据。
    * @return @~english Is ignore.
    * @~chinese 是否忽略。
    */
    virtual bool isIgnoreMovementBoneData() const { return _ignoreMovementBoneData; }

    /*
     * @deprecated Use `isIgnoreMovementBoneData()` instead
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual bool getIgnoreMovementBoneData() const { return isIgnoreMovementBoneData(); }

    
    /*
     * @~english Set blend function.
     * @~chinese 设置混合函数。
     * @param blendFunc @~english Blend function.
     * @~chinese 混合函数。
     */
    virtual void setBlendFunc(const cocos2d::BlendFunc& blendFunc);
    /*
    * @~english Get blend function.
    * @~chinese 获取混合函数。
    * @return @~english Blend function.
    * @~chinese 混合函数。
    */
    virtual cocos2d::BlendFunc getBlendFunc(void) { return _blendFunc; }

    /*
     * @~english Set if blend function is dirty.
     * @~chinese 设置混合函数是否为dirty。
     * @param dirty @~english Is dirty.
     * @~chinese 是否dirty。
     */
    virtual void setBlendDirty(bool dirty) { _blendDirty = dirty; }
    /*
    * @~english Get is blend function dirty.
    * @~chinese 获取混合函数是否为脏。
    * @return @~english Is dirty.
    * @~chinese 是否脏。
    */
    virtual bool isBlendDirty(void) { return _blendDirty; }

    /*
    * @~english Get tween frame data.
    * @~chinese 获取补间关键帧数据。
    * @return @~english Tween frame data.
    * @~chinese 补间关键帧数据。
    */
    virtual FrameData *getTweenData() const { return _tweenData; }

    /*
    * @~english Get world info.
    * @~chinese 获取世界信息。
    * @return @~english World info.
    * @~chinese 世界信息。
    */
    virtual BaseData *getWorldInfo() const { return _worldInfo; }
protected:
    void applyParentTransform(Bone *parent);

    /*
     *  The origin state of the Bone. Display's state is effected by _boneData, m_pNode, _tweenData
     *  when call setData function, it will copy from the BoneData.
     */
    BoneData *_boneData;

    //! A weak reference to the Armature
    Armature *_armature;

    //! A weak reference to the child Armature
    Armature *_childArmature;

    DisplayManager *_displayManager;

    /*
     *	When Armature play an animation, if there is not a MovementBoneData of this bone in this MovementData, this bone will be hidden.
     *	Set IgnoreMovementBoneData to true, then this bone will also be shown.
     */
    bool _ignoreMovementBoneData;

    cocos2d::BlendFunc _blendFunc;
    bool _blendDirty;

    Tween *_tween;				//! Calculate tween effect

    //! Used for making tween effect in every frame
    FrameData *_tweenData;

    Bone *_parentBone;	               //! A weak reference to its parent
    bool _boneTransformDirty;          //! Whether or not transform dirty

    //! self Transform, use this to change display's state
    cocos2d::Mat4 _worldTransform;

    BaseData *_worldInfo;
    
    //! Armature's parent bone
    Bone *_armatureParentBone;
    
    //! Data version
    float _dataVersion;
};

}

#endif /*__CCBONE_H__*/
