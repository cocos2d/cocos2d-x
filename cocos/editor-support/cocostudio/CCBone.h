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
    * @~chinese 分配并且初始化一段骨头。
    * @return @~english An initialized bone which is marked as "autorelease".
    * @~chinese 一段初始化的骨头，该骨头会自动被标记为“autorelease”（自动释放）。
    */
    static Bone *create();

    /**
    * @~english Allocates and initializes a bone.
    * @~chinese 分配并且初始化一段骨头。
    * @param name  @~english If name is not null, then set name to the bone's name
    * @~chinese 如果非空，则将该参数设为骨头的名称
    * @return @~english An initialized bone which is marked as "autorelease".
    * @~chinese 一段初始化的骨头，该骨头会自动被标记为“autorelease”（自动释放）。
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

    /**
     * @~english Initializes an empty Bone with nothing init.
     * @~chinese 初始化一段空骨头，没有其他被初始化。
     */
    virtual bool init() override;

    /**
     * @~english Initializes a Bone with the specified name
     * @~chinese 以指定的名称初始化一段骨头。
     * @param name @~english Bone's name.
     * @~chinese 骨头的名称。
     */
    virtual bool init(const std::string& name);

    /**
     * @~english Add display and use displayData to init the display.
     * If index already have a display, then replace it.
     * If index is current display index, then also change display to _index
     * @~chinese 为骨头增加显示，并使用显示属性数据来初始化显示性。
     * 如果索引处已有显示，则将其覆盖。
     * 如果索引为当前显示索引，则同时将显示更改为_index处显示。
     *
     * @param @~english displayData it include the display information, like DisplayType.
     *          If you want to create a sprite display, then create a `SpriteDisplayData` param
     * @~chinese 显示数据，包含显示信息，例如显示种类。
     * 要创建一个精灵显示，则创建一个`SpriteDisplayData`参数。
     * @param index @~english the index of the display you want to replace or add to
     *          -1 : append display from back
     * @~chinese 要添加或覆盖的显示的索引。为-1时将显示添加至最后。
     */
    void addDisplay(DisplayData *displayData, int index);

    void addDisplay(cocos2d::Node *display, int index);

    void removeDisplay(int index);

    CC_DEPRECATED_ATTRIBUTE void changeDisplayByIndex(int index, bool force);
    CC_DEPRECATED_ATTRIBUTE void changeDisplayByName(const std::string& name, bool force);

    void changeDisplayWithIndex(int index, bool force);
    void changeDisplayWithName(const std::string& name, bool force);

    /**
     * @~english Add a child to this bone, and it will let this child call `setParent(Bone *parent)` function to set self to it's parent
     * @~chinese 为当前骨头添加一段子骨头，同时该子骨头会调用`setParent(Bone *parent)`函数来将当前骨头设为其父骨头。
     * @param child @~english the child you want to add
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

    /**
    * @~english Update color to render display
    * @~chinese 更新颜色以渲染显示
    */
    virtual void updateColor() override;

    /**
    * @~english Update zorder
    * @~chinese 更新Z顺序
    */
    void updateZOrder();

    virtual void setLocalZOrder(int zOrder) override;

    Tween *getTween();

    /*
     * @~english Whether or not the bone's transform property changed. if true, the bone will update the transform.
     * @~chinese 骨头的变形属性是否已改变，如果为真，骨头将会更新变形。
     */
    virtual void setTransformDirty(bool dirty) { _boneTransformDirty = dirty; }
    virtual bool isTransformDirty() { return _boneTransformDirty; }

    virtual cocos2d::Mat4 getNodeToArmatureTransform() const;
    virtual cocos2d::Mat4 getNodeToWorldTransform() const override;

    cocos2d::Node *getDisplayRenderNode();
    DisplayType getDisplayRenderNodeType();

    /*
     * @~english Get the ColliderBody list in this bone. The object in the Array is ColliderBody.
     * @~chinese 获取骨头的碰撞体，数组中的对象为碰撞体。
     */
    virtual ColliderDetector* getColliderDetector() const;

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
    virtual void setColliderFilter(ColliderFilter *filter);
    virtual ColliderFilter *getColliderFilter();
#endif

    virtual void setBoneData(BoneData *boneData);
    virtual BoneData *getBoneData() const;

    virtual void setArmature(Armature *armature);
    virtual Armature *getArmature() const;

    virtual void setChildArmature(Armature *childArmature);
    virtual Armature *getChildArmature() const;

    virtual DisplayManager *getDisplayManager() const { return _displayManager; }
    /**
     *  @lua NA
     */
    virtual void setIgnoreMovementBoneData(bool ignore) { _ignoreMovementBoneData = ignore; }
    virtual bool isIgnoreMovementBoneData() const { return _ignoreMovementBoneData; }

    /*
     * This function is deprecated, please use isIgnoreMovementBoneData()
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual bool getIgnoreMovementBoneData() const { return isIgnoreMovementBoneData(); }

    
    /*
     * @~english Set blend function
     * @~chinese 设置混合函数。
     */
    virtual void setBlendFunc(const cocos2d::BlendFunc& blendFunc);
    virtual cocos2d::BlendFunc getBlendFunc(void) { return _blendFunc; }

    /*
     * @~english Set if blend function is dirty 
     * @~chinese 混合函数为脏时设置。
     */
    virtual void setBlendDirty(bool dirty) { _blendDirty = dirty; }
    virtual bool isBlendDirty(void) { return _blendDirty; }

    virtual FrameData *getTweenData() const { return _tweenData; }

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
