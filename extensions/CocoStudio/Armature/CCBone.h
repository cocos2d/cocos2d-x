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

#ifndef __CCBONE_H__
#define __CCBONE_H__

#include "utils/CCArmatureDefine.h"
#include "datas/CCDatas.h"
#include "animation/CCTween.h"
#include "display/CCDecorativeDisplay.h"
#include "display/CCDisplayManager.h"

NS_CC_EXT_BEGIN

class CCArmature;
/**
 * @lua NA
 */
class CCBone : public CCNodeRGBA
{
public:
    /**
     * Allocates and initializes a bone.
     * @return A initialized bone which is marked as "autorelease".
     */
    static CCBone *create();
    /**
     * Allocates and initializes a bone.
     *
     * @param  name If name is not null, then set name to the bone's name
     * @return A initialized bone which is marked as "autorelease".
     */
    static CCBone *create(const char *name);

public:
    /**
     *  @js ctor
     */
    CCBone();
    /**
     *  @js NA
     */
    virtual ~CCBone(void);

    /**
     * Initializes an empty CCBone with nothing init.
     */
    virtual bool init();

    /**
     * Initializes a CCBone with the specified name
     * @param name CCBone's name.
     */
    virtual bool init(const char *name);

    /**
     * Add display and use displayData to init the display.
     * If index already have a display, then replace it.
     * If index is current display index, then also change display to _index
     *
     * @param displayData it include the display information, like DisplayType.
     *          If you want to create a sprite display, then create a CCSpriteDisplayData param
     *
     * @param index the index of the display you want to replace or add to
     *          -1 : append display from back
     */
    void addDisplay(CCDisplayData *displayData, int index);

    void addDisplay(CCNode *display, int index);

    void removeDisplay(int index);

    /**
     * @deprecated please use changeDisplayWithIndex and changeDisplayWithName
     */
    CC_DEPRECATED_ATTRIBUTE void changeDisplayByIndex(int index, bool force);
    CC_DEPRECATED_ATTRIBUTE void changeDisplayByName(const char *name, bool force);

    void changeDisplayWithIndex(int index, bool force);
    void changeDisplayWithName(const char *name, bool force);

    /**
     * Add a child to this bone, and it will let this child call setParent(CCBone *parent) function to set self to it's parent
     * @param 	child  the child you want to add
     */
    void addChildBone(CCBone *child);

    /**
     * Set parent bone.
     * If parent is NUll, then also remove this bone from armature.
     * It will not set the CCArmature, if you want to add the bone to a CCArmature, you should use CCArmature::addBone(CCBone *bone, const char* parentName).
     *
     * @param parent  the parent bone.
     *          NULL : remove this bone from armature
     */
    void setParentBone(CCBone *parent);

    /**
     * Get parent bone
     * @return parent bone
     */
    CCBone *getParentBone();

    using CCNode::removeFromParent;
    /**
     * Remove itself from its parent.
     * @param 	recursion    whether or not to remove childBone's display
     */
    void removeFromParent(bool recursion);

    /**
     * Removes a child CCBone
     * @param 	bone   the bone you want to remove
     */
    void removeChildBone(CCBone *bone, bool recursion);

    void update(float delta);

    void updateDisplayedColor(const ccColor3B &parentColor);
    void updateDisplayedOpacity(GLubyte parentOpacity);

    void setColor(const ccColor3B &color);
    void setOpacity(GLubyte opacity);

    //! Update color to render display
    void updateColor();

    //! Update zorder
    void updateZOrder();

    virtual void setZOrder(int zOrder);

    CCTween *getTween();

    /*
     * Whether or not the bone's transform property changed. if true, the bone will update the transform.
     */
    virtual inline void setTransformDirty(bool dirty) { m_bBoneTransformDirty = dirty; }
    virtual inline bool isTransformDirty() { return m_bBoneTransformDirty; }

    /*
     * Set blend function
     */
    virtual void setBlendFunc(const ccBlendFunc& blendFunc);
    virtual ccBlendFunc getBlendFunc(void) { return m_sBlendFunc; }

    /*
     * Set if blend function is dirty 
     */
    virtual void setBlendDirty(bool dirty) { m_bBlendDirty = dirty; }
    virtual bool isBlendDirty(void) { return m_bBlendDirty; }

    virtual CCAffineTransform nodeToArmatureTransform();
    virtual CCAffineTransform nodeToWorldTransform();

    CCNode *getDisplayRenderNode();
    DisplayType getDisplayRenderNodeType();

    /*
     * Get the ColliderBody list in this bone. The object in the CCArray is ColliderBody.
     */
    virtual CCArray *getColliderBodyList();

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
    virtual void setColliderFilter(CCColliderFilter *filter);
    virtual CCColliderFilter *getColliderFilter();
#endif

public:
    /*
     *  The origin state of the CCBone. Display's state is effected by m_pBoneData, m_pNode, m_pTweenData
     *  when call setData function, it will copy from the CCBoneData.
     */
    CC_PROPERTY(CCBoneData *, m_pBoneData, BoneData);

    //! A weak reference to the CCArmature
    CC_PROPERTY(CCArmature *, m_pArmature, Armature);

    //! A weak reference to the child CCArmature
    CC_PROPERTY(CCArmature *, m_pChildArmature, ChildArmature);

    CC_SYNTHESIZE(CCDisplayManager *, m_pDisplayManager, DisplayManager)

    /*
     *	When CCArmature play an animation, if there is not a CCMovementBoneData of this bone in this CCMovementData, this bone will be hidden.
     *	Set IgnoreMovementBoneData to true, then this bone will also be shown.
     */
    CC_SYNTHESIZE(bool, m_bIgnoreMovementBoneData, IgnoreMovementBoneData)

protected:
    virtual void applyParentTransform(CCBone *parent);

    CCTween *m_pTween;				//! Calculate tween effect

    //! Used for making tween effect in every frame
    CC_SYNTHESIZE_READONLY(CCFrameData *, m_pTweenData, TweenData);

    CC_SYNTHESIZE(std::string, m_strName, Name);

    CCBone *m_pParentBone;	             //! A weak reference to its parent
    bool m_bBoneTransformDirty;          //! Whether or not transform dirty

    //! Transform in armature space, use this to change display's state
    CCAffineTransform m_tWorldTransform;

    //! World Point, Scale, Rotation in armature space
    CC_SYNTHESIZE_READONLY(CCBaseData *, m_tWorldInfo, WorldInfo);

    //! Armature's parent bone
    CCBone *m_pArmatureParentBone;

    //! Data version
    float m_fDataVersion;

    ccBlendFunc m_sBlendFunc; 
    bool m_bBlendDirty;
};

NS_CC_EXT_END

#endif /*__CCBONE_H__*/
