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

class b2Body;
struct cpBody;

NS_CC_EXT_ARMATURE_BEGIN

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

    virtual void visit();
    virtual void update(float dt);
    virtual void draw();

    virtual const AffineTransform& getNodeToParentTransform() const;

    /**
     * Set contentsize and Calculate anchor point.
     */
    virtual void updateOffsetPoint();

    inline void setBlendFunc(const BlendFunc &blendFunc)
    {
        m_sBlendFunc = blendFunc;
    }
    inline const BlendFunc &getBlendFunc(void) const
    {
        return m_sBlendFunc;
    }

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

    CC_SYNTHESIZE(ArmatureData *, m_pArmatureData, ArmatureData);

    CC_SYNTHESIZE(BatchNode *, m_pBatchNode, BatchNode);

    CC_SYNTHESIZE(std::string, m_strName, Name);

    CC_SYNTHESIZE(TextureAtlas *, m_pAtlas, TextureAtlas);

    CC_SYNTHESIZE(Bone *, m_pParentBone, ParentBone);

    CC_SYNTHESIZE(float, m_fVersion, Version);

protected:
    mutable bool m_bArmatureTransformDirty;

    Dictionary *m_pBoneDic;                    //! The dictionary of the bones, include all bones in the armature, no matter it is the direct bone or the indirect bone. It is different from m_pChindren.

    Array *m_pTopBoneList;

    static std::map<int, Armature *> m_sArmatureIndexDic;	//! Use to save armature zorder info,

    BlendFunc m_sBlendFunc;                    //! It's required for CCTextureProtocol inheritance

    Point m_pOffsetPoint;

    ArmatureAnimation *m_pAnimation;

#if ENABLE_PHYSICS_BOX2D_DETECT
    CC_PROPERTY(b2Body *, m_pBody, Body);
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
    CC_PROPERTY(cpBody *, m_pBody, Body);
#endif
};

NS_CC_EXT_ARMATURE_END

#endif /*__CCARMATURE_H__*/
