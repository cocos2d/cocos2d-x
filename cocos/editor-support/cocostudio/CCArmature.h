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

#ifndef __CCARMATURE_H__
#define __CCARMATURE_H__

#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCBone.h"
#include "cocostudio/CCBatchNode.h"
#include "cocostudio/CCArmatureAnimation.h"
#include "cocostudio/CCSpriteFrameCacheHelper.h"
#include "cocostudio/CCArmatureDataManager.h"
#include "cocostudio/CocosStudioExport.h"
#include "math/CCMath.h"

class b2Body;
struct cpBody;

namespace cocostudio {

CC_DEPRECATED_ATTRIBUTE typedef ProcessBase CCProcessBase;
CC_DEPRECATED_ATTRIBUTE typedef BaseData CCBaseData;
CC_DEPRECATED_ATTRIBUTE typedef DisplayData CCDisplayData;
CC_DEPRECATED_ATTRIBUTE typedef SpriteDisplayData CCSpriteDisplayData;
CC_DEPRECATED_ATTRIBUTE typedef ArmatureDisplayData CCArmatureDisplayData;
CC_DEPRECATED_ATTRIBUTE typedef ParticleDisplayData CCParticleDisplayData;
CC_DEPRECATED_ATTRIBUTE typedef BoneData CCBoneData;
CC_DEPRECATED_ATTRIBUTE typedef FrameData CCFrameData;
CC_DEPRECATED_ATTRIBUTE typedef MovementBoneData CCMovementBoneData;
CC_DEPRECATED_ATTRIBUTE typedef MovementData CCMovementData;
CC_DEPRECATED_ATTRIBUTE typedef AnimationData CCAnimationData;
CC_DEPRECATED_ATTRIBUTE typedef ContourData CCContourData;
CC_DEPRECATED_ATTRIBUTE typedef TextureData CCTextureData;
CC_DEPRECATED_ATTRIBUTE typedef DecorativeDisplay CCDecorativeDisplay;
CC_DEPRECATED_ATTRIBUTE typedef DisplayData CCDisplayData;
CC_DEPRECATED_ATTRIBUTE typedef DisplayFactory CCDisplayFactory;
CC_DEPRECATED_ATTRIBUTE typedef BatchNode CCBatchNode;
CC_DEPRECATED_ATTRIBUTE typedef DecorativeDisplay CCDecorativeDisplay;
CC_DEPRECATED_ATTRIBUTE typedef DisplayManager CCDisplayManager;
CC_DEPRECATED_ATTRIBUTE typedef ColliderBody CCColliderBody;
CC_DEPRECATED_ATTRIBUTE typedef ColliderDetector CCColliderDetector;
CC_DEPRECATED_ATTRIBUTE typedef SpriteFrameCacheHelper CCSpriteFrameCacheHelper;
CC_DEPRECATED_ATTRIBUTE typedef ArmatureData CCArmatureData;
CC_DEPRECATED_ATTRIBUTE typedef Bone CCBone;
CC_DEPRECATED_ATTRIBUTE typedef ArmatureAnimation CCArmatureAnimation;
CC_DEPRECATED_ATTRIBUTE typedef Armature CCArmature;
CC_DEPRECATED_ATTRIBUTE typedef ArmatureDataManager CCArmatureDataManager;
CC_DEPRECATED_ATTRIBUTE typedef cocos2d::tweenfunc::TweenType CCTweenType;

class CC_STUDIO_DLL Armature : public cocos2d::Node, public cocos2d::BlendProtocol
{

public:

    /**
    * @~english Allocates and initializes an armature.
    * @~chinese 分配并且初始化骨骼动画对象。
    * @return @~english An initialized armature which is marked as "autorelease".
    * @~chinese 一个初始化过并且设置为自动释放的骨骼动画对象。
    */
    static Armature *create();

    /**
    * @~english Allocates an armature, and use the `ArmatureData` named name in `ArmatureDataManager` to initializes the armature.
    * @~chinese 分配骨骼动画对象，并使用`ArmatureDataManager`中以name命名的`ArmatureData`对其进行初始化。
    * @param name  @~english Armature will use the name to find the `ArmatureData` to initializes it.
    * @~chinese 骨骼将以该name来查找`ArmatureData`来对骨骼进行初始化。
    * @return @~english An initialized armature which is marked as "autorelease".
    * @~chinese 一个初始化过并且设置为自动释放的骨骼动画对象。
    */
    static Armature *create(const std::string& name);

    /**
    * @~english Allocates an armature, and use the `ArmatureData` named name in `ArmatureDataManager` to initializes the armature.
    * @~chinese 分配骨骼动画对象，并使用`ArmatureDataManager`中以name命名的`ArmatureData`对其进行初始化。
    * @param name  @~english Armature will use the name to find the `ArmatureData` to initializes it.
    * @~chinese 骨骼将以name来查找`ArmatureData`来对骨骼进行初始化。
    * @param parentBone  @~english The armature will set the parentBone as its parent.
    * @~chinese 骨骼将以parentBone作为父骨头。
    * @return @~english An initialized armature which is marked as "autorelease".
    * @~chinese 一个初始化过并且设置为自动释放的骨骼动画对象。
    */
    static Armature *create(const std::string& name, Bone *parentBone);

public:
    /**
     *  @js ctor
     */
    Armature();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Armature(void);
    virtual bool init() override;

    /**
    * @~english Init an armature with specified name.
    * @~chinese 用指定的名称初始化骨骼。
    * @param name @~english Armature name.
    * @~chinese 骨骼名称。
    */
    virtual bool init(const std::string& name);

    /**
    * @~english Init an armature with specified name.
    * @~chinese 用指定的名称初始化骨骼。
    * @param name @~english Armature name.
    * @~chinese 骨骼名称。
    * @param parentBone @~english The armature will set the parentBone as its parent.
    * @~chinese 骨骼将以该参数作为父骨头。
    */
    virtual bool init(const std::string& name, Bone *parentBone);

    /**
     * @~english Add a bone to this Armature.
     * @~chinese 将一段骨头添加至骨骼中。
     * @param bone  @~english The bone you want to add to Armature.
     * @~chinese 要添加的骨头。
     * @param parentName @~english The parent Bone's name you want to add to. If it's nullptr, then set Armature to its parent.
     * @~chinese 以该参数作为名称的骨头将作为骨头被添加后的父骨头。如果该参数为空，骨头被添加后将以骨骼作为父骨头。
     */
    virtual void addBone(Bone *bone, const std::string& parentName);

    /**
     * @~english Get a bone with the specified name.
     * @~chinese 以指定的名称获取一段骨头。
     * @param name @~english The bone's name you want to get.
     * @~chinese 要获取骨头的名称。
     */
    virtual Bone *getBone(const std::string& name) const;

    /**
     * @~english Change a bone's parent with the specified parent name.
     * @~chinese 根据指定的名称，更改一段骨头的父骨头。
     * @param bone @~english The bone you want to change parent.
     * @~chinese 要更改的一段骨头。
     * @param parentName @~english The new parent's name.
     * @~chinese 新父骨头的名称。
     */
    virtual void changeBoneParent(Bone *bone, const std::string& parentName);

    /**
     * @~english Remove a bone with the specified name. If recursion it will also remove child Bone recursionly.
     * @~chinese 根据指定的名称，移除一段骨头。根据参数，将会决定是否对子骨头进行递归移除。
     * @param bone @~english The bone you want to remove.
     * @~chinese 要移除的骨头。
     * @param recursion @~english Determine whether remove the bone's child recursion.
     * @~chinese 是否递归移除。
     */
    virtual void removeBone(Bone *bone, bool recursion);

    /**
     * @~english Get Armature's bone dictionary.
     * @~chinese 获取骨头列表。
     * @return @~english Armature's bone dictionary.
     * @~chinese 骨头列表。
     */
    const cocos2d::Map<std::string, Bone*>& getBoneDic() const;

    /**
    * @~english Get armature's boundingBox by calculating all bones' boundingBox.
    * @~chinese 通过计算所有骨头的外边框，得到整套骨骼的外边框。
    * @return @~english Armature's boundingBox.
    * @~chinese 骨骼的外边框。
    */
    virtual cocos2d::Rect getBoundingBox() const override;

    /**
    * @~english Get a bone containing the specified point.
    * @~chinese 获取一段包含指定坐标点的骨头。
    * @param x @~english Specified point x.
    * @~chinese 指定点的X坐标。
    * @param y @~english Specified point y.
    * @~chinese 指定点的Y坐标。
    * @return @~english The bone containing the specified point, if no bone found, return null.
    * @~chinese 包含该点的骨骼，如果没有骨骼被找到，返回空。
    */
    Bone *getBoneAtPoint(float x, float y) const;

    // overrides
    virtual void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags) override;
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
    virtual void update(float dt) override;
    virtual void onEnter() override;
    virtual void onExit() override; 
    virtual const cocos2d::Mat4& getNodeToParentTransform() const override;
    inline void setBlendFunc(const cocos2d::BlendFunc &blendFunc) override { _blendFunc = blendFunc; }
    inline const cocos2d::BlendFunc &getBlendFunc(void) const override{ return _blendFunc; }
	

    /**
     * @~english Set contentsize and Calculate anchor point.
     * @~chinese 设置大小并计算锚点。
     */
    virtual void updateOffsetPoint();
    virtual void setAnchorPoint(const cocos2d::Vec2& point) override;
    virtual const cocos2d::Vec2& getAnchorPointInPoints() const override;

    /**
    * @~english Get offset points of bones.
    * @~chinese 获取骨头的坐标偏移量。
    */
    virtual const cocos2d::Vec2& getOffsetPoints() const;

    /**
    * @~english Set animation for armature.
    * @~chinese 为骨骼设置动画。
    * @param animation @~english Armature animation.
    * @~chinese 骨骼动画。
    */
    virtual void setAnimation(ArmatureAnimation *animation);

    /**
    * @~english Get animation of armature.
    * @~chinese 获得骨骼设置的动画。
    * @return @~english Animation of armature.
    * @~chinese 骨骼动画。
    */
    virtual ArmatureAnimation *getAnimation() const;

    /**
    * @~english Get is the armature is transformed.
    * @~chinese 获得骨骼是否已经进行坐标变换。
    * @return @~english Is the armature is transformed.
    * @~chinese 骨骼是否已经进行坐标变换。
    */
    virtual bool getArmatureTransformDirty() const;


#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
    virtual void setColliderFilter(ColliderFilter *filter);
#elif ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    CC_DEPRECATED_ATTRIBUTE virtual void drawContour();
#endif

    /**
    * @~english Set armature data for armature.
    * @~chinese 为骨骼设置数据。
    * @param armatureData @~english Armature data.
    * @~chinese 骨骼数据。
    */
    virtual void setArmatureData(ArmatureData *armatureData) { _armatureData = armatureData; }

    /**
    * @~english Get armature data of armature.
    * @~chinese 获取骨骼数据。
    * @return @~english Armature data.
    * @~chinese 骨骼数据。
    */
    virtual ArmatureData *getArmatureData() const { return _armatureData; }

    /**
    * @~english Set parent bone for armature.
    * @~chinese 为骨骼设置父骨头。
    * @param parentBone @~english Parent bone.
    * @~chinese 父骨头。
    */
    virtual void setParentBone(Bone *parentBone);

    /**
    * @~english Get parent bone of armature.
    * @~chinese 获取骨骼的父骨头。
    * @return @~english Parent bone.
    * @~chinese 骨骼数据。
    */
    virtual Bone *getParentBone() const;

    /**
    * @~english Set version for armature.
    * @~chinese 为骨骼设置版本号。
    * @param version @~english Armature version.
    * @~chinese 骨骼版本号。
    */
    virtual void setVersion(float version) { _version = version; }

    /**
    * @~english Get version of armature.
    * @~chinese 获取骨骼的版本号。
    * @return @~english Armature version.
    * @~chinese 骨骼版本号。
    */
    virtual float getVersion() const { return _version; }

    /**
    * @~english Set BatchNode for armature.
    * @~chinese 为骨骼设置批次节点。
    * @param batchNode @~english BatchNode.
    * @~chinese 批次节点。
    */
    virtual void setBatchNode(BatchNode *batchNode) { _batchNode = batchNode; }

    /**
    * @~english Get BatchNode of armature.
    * @~chinese 获取骨骼的批次节点。
    * @return @~english BatchNode.
    * @~chinese 批次节点。
    */
    virtual BatchNode *getBatchNode() const { return _batchNode; }

#if ENABLE_PHYSICS_BOX2D_DETECT
    virtual b2Fixture *getShapeList();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void setBody(b2Body *body);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual b2Body *getBody() const;
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
    /**
     *  @js NA
     *  @lua NA
     */
    virtual cpShape *getShapeList();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void setBody(cpBody *body);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual cpBody *getBody() const;
#endif

protected:

    /*
     * Used to create Bone internal
     * @js NA
     * @lua NA
     */
    Bone *createBone(const std::string& boneName );

protected:
    ArmatureData *_armatureData;

    BatchNode *_batchNode;

    Bone *_parentBone;
    float _version;

    mutable bool _armatureTransformDirty;

    cocos2d::Map<std::string, Bone*> _boneDic;                    //! The dictionary of the bones, include all bones in the armature, no matter it is the direct bone or the indirect bone. It is different from m_pChindren.

    cocos2d::Vector<Bone*> _topBoneList;

    cocos2d::BlendFunc _blendFunc;                    //! It's required for CCTextureProtocol inheritance

    cocos2d::Vec2 _offsetPoint;
    cocos2d::Vec2 _realAnchorPointInPoints;

    ArmatureAnimation *_animation;

#if ENABLE_PHYSICS_BOX2D_DETECT
    b2Body *_body;
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
    cpBody *_body;
#endif
};

}

#endif /*__CCARMATURE_H__*/
