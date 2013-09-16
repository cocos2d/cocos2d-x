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

#ifndef __CCARMATURE_H__
#define __CCARMATURE_H__

#include "utils/CCArmatureDefine.h"
#include "CCBone.h"
#include "display/CCBatchNode.h"
#include "animation/CCArmatureAnimation.h"
#include "utils/CCSpriteFrameCacheHelper.h"
#include "utils/CCArmatureDataManager.h"

class b2Body;
struct cpBody;

NS_CC_EXT_ARMATURE_BEGIN

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
CC_DEPRECATED_ATTRIBUTE typedef TweenFunction CCTweenFunction;
CC_DEPRECATED_ATTRIBUTE typedef ArmatureData CCArmatureData;
CC_DEPRECATED_ATTRIBUTE typedef Bone CCBone;
CC_DEPRECATED_ATTRIBUTE typedef ArmatureAnimation CCArmatureAnimation;
CC_DEPRECATED_ATTRIBUTE typedef Armature CCArmature;
CC_DEPRECATED_ATTRIBUTE typedef ArmatureDataManager CCArmatureDataManager;

class  Armature : public NodeRGBA, public BlendProtocol
{

public:

    /**
    * Allocates and initializes an armature.
    * @return An initialized armature which is marked as "autorelease".
    */
    static Armature *create();

    /**
    * Allocates an armature, and use the ArmatureData named name in ArmatureDataManager to initializes the armature.
    *
    * @param  name Armature will use the name to find the ArmatureData to initializes it.
    * @return A initialized armature which is marked as "autorelease".
    */
    static Armature *create(const char *name);

    static Armature *create(const char *name, Bone *parentBone);

public:
    Armature();
    /**
     * @js NA
     * @lua NA
     */
    ~Armature(void);

    /**
     * Init the empty armature
     */
    virtual bool init();

    /**
     * Init an armature with specified name
     * @param name Armature name
     */
    virtual bool init(const char *name);

    virtual bool init(const char *name, Bone *parentBone);
    /**
     * Add a Bone to this Armature,
     *
     * @param bone  The Bone you want to add to Armature
     * @param parentName   The parent Bone's name you want to add to . If it's  NULL, then set Armature to its parent
     */
    virtual void addBone(Bone *bone, const char *parentName);
    /**
     * Get a bone with the specified name
     *
     * @param name The bone's name you want to get
     */
    virtual Bone *getBone(const char *name) const;
    /**
     * Change a bone's parent with the specified parent name.
     *
     * @param bone The bone you want to change parent
     * @param parentName The new parent's name.
     */
    virtual void changeBoneParent(Bone *bone, const char *parentName);
    /**
     * Remove a bone with the specified name. If recursion it will also remove child Bone recursionly.
     *
     * @param bone The bone you want to remove
     * @param recursion Determine whether remove the bone's child  recursion.
     */
    virtual void removeBone(Bone *bone, bool recursion);

    /**
     * Get Armature's bone dictionary
     * @return Armature's bone dictionary
     */
    Dictionary *getBoneDic();

    /**
     * This boundingBox will calculate all bones' boundingBox every time
     */
    virtual Rect getBoundingBox() const;

    Bone *getBoneAtPoint(float x, float y);

    // overrides
    /**
     * @js NA
     * @lua NA
     */
    virtual void visit() override;
    virtual void update(float dt) override;
    virtual void draw() override;

    virtual const AffineTransform& getNodeToParentTransform() const override;

    inline void setBlendFunc(const BlendFunc &blendFunc) override { _blendFunc = blendFunc; }
    inline const BlendFunc &getBlendFunc(void) const override{ return _blendFunc; }
	

    /**
     * Set contentsize and Calculate anchor point.
     */
    virtual void updateOffsetPoint();

    virtual void setAnimation(ArmatureAnimation *animation);
    virtual ArmatureAnimation *getAnimation();
    
    virtual bool getArmatureTransformDirty();

#if ENABLE_PHYSICS_BOX2D_DETECT
    virtual b2Fixture *getShapeList();
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
    virtual cpShape *getShapeList();
#endif

protected:

    /*
     * Used to create Bone internal
     */
    Bone *createBone(const char *boneName );

    //! Update blend function
    void updateBlendType(BlendType blendType);

    CC_SYNTHESIZE(ArmatureData *, _armatureData, ArmatureData);

    CC_SYNTHESIZE(BatchNode *, _batchNode, BatchNode);

    CC_SYNTHESIZE(std::string, _name, Name);

    CC_SYNTHESIZE(TextureAtlas *, _atlas, TextureAtlas);

    CC_SYNTHESIZE(Bone *, _parentBone, ParentBone);

    CC_SYNTHESIZE(float, _version, Version);

protected:
    mutable bool _armatureTransformDirty;

    Dictionary *_boneDic;                    //! The dictionary of the bones, include all bones in the armature, no matter it is the direct bone or the indirect bone. It is different from m_pChindren.

    Array *_topBoneList;

    BlendFunc _blendFunc;                    //! It's required for CCTextureProtocol inheritance

    Point _offsetPoint;

    ArmatureAnimation *_animation;

#if ENABLE_PHYSICS_BOX2D_DETECT
    CC_PROPERTY(b2Body *, _body, Body);
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
    CC_PROPERTY(cpBody *, _body, Body);
#endif
};

NS_CC_EXT_ARMATURE_END

#endif /*__CCARMATURE_H__*/
