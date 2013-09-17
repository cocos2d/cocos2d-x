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

NS_CC_EXT_ARMATURE_BEGIN


class Armature;

class Bone : public NodeRGBA
{
public:
    /**
     * Allocates and initializes a bone.
     * @return A initialized bone which is marked as "autorelease".
     */
    static Bone *create();
    /**
     * Allocates and initializes a bone.
     *
     * @param  name If name is not null, then set name to the bone's name
     * @return A initialized bone which is marked as "autorelease".
     */
    static Bone *create(const char *name);

public:
    Bone();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Bone(void);

    /**
     * Initializes an empty Bone with nothing init.
     */
    virtual bool init();

    /**
     * Initializes a Bone with the specified name
     * @param name Bone's name.
     */
    virtual bool init(const char *name);

    /**
     * Add display and use displayData to init the display.
     * If index already have a display, then replace it.
     * If index is current display index, then also change display to _index
     *
     * @param displayData it include the display information, like DisplayType.
     *          If you want to create a sprite display, then create a SpriteDisplayData param
     *
     * @param index the index of the display you want to replace or add to
     *          -1 : append display from back
     */
    void addDisplay(DisplayData *displayData, int index);

    void addDisplay(Node *display, int index);

    void changeDisplayByIndex(int index, bool force);

    /**
     * Add a child to this bone, and it will let this child call setParent(Bone *parent) function to set self to it's parent
     * @param 	child  the child you want to add
     */
    void addChildBone(Bone *child);

    /**
     * Set parent bone.
     * If parent is NUll, then also remove this bone from armature.
     * It will not set the Armature, if you want to add the bone to a Armature, you should use Armature::addBone(Bone *bone, const char* parentName).
     *
     * @param parent  the parent bone.
     *          NULL : remove this bone from armature
     */
    void setParentBone(Bone *parent);

    /**
     * Get parent bone
     * @return parent bone
     */
    Bone *getParentBone();

    /**
     * Remove itself from its parent.
     * @param recursion    whether or not to remove childBone's display
     */
    void removeFromParent(bool recursion);

    /**
     * Removes a child Bone
     * @param 	bone   the bone you want to remove
     */
    void removeChildBone(Bone *bone, bool recursion);

    void update(float delta);

    void updateDisplayedColor(const Color3B &parentColor);
    void updateDisplayedOpacity(GLubyte parentOpacity);

    //! Update color to render display
    void updateColor();

    //! Update zorder
    void updateZOrder();

    virtual void setZOrder(int zOrder);

    Tween *getTween();

    /*
     * Whether or not the bone's transform property changed. if true, the bone will update the transform.
     */
    virtual void setTransformDirty(bool dirty);

    virtual bool isTransformDirty();

    virtual AffineTransform getNodeToArmatureTransform() const;
    virtual AffineTransform getNodeToWorldTransform() const override;

    Node *getDisplayRenderNode();

    /*
     * Get the ColliderBody list in this bone. The object in the Array is ColliderBody.
     */
    virtual Array *getColliderBodyList();

public:
    /*
     *  The origin state of the Bone. Display's state is effected by _boneData, m_pNode, _tweenData
     *  when call setData function, it will copy from the BoneData.
     */
    CC_PROPERTY(BoneData *, _boneData, BoneData);

    //! A weak reference to the Armature
    CC_PROPERTY(Armature *, _armature, Armature);

    //! A weak reference to the child Armature
    CC_PROPERTY(Armature *, _childArmature, ChildArmature);

    CC_SYNTHESIZE(DisplayManager *, _displayManager, DisplayManager)

    /*
     *	When Armature play an animation, if there is not a MovementBoneData of this bone in this MovementData, this bone will be hidden.
     *	Set IgnoreMovementBoneData to true, then this bone will also be shown.
     */
    CC_SYNTHESIZE(bool, _ignoreMovementBoneData, IgnoreMovementBoneData)

    CC_SYNTHESIZE(BlendType, _blendType, BlendType)
protected:
    Tween *_tween;				//! Calculate tween effect

    //! Used for making tween effect in every frame
    CC_SYNTHESIZE_READONLY(FrameData *, _tweenData, TweenData);

    CC_SYNTHESIZE(std::string, _name, Name);

    Bone *_parentBone;	             //! A weak reference to its parent
    bool _boneTransformDirty;          //! Whether or not transform dirty

    //! self Transform, use this to change display's state
    AffineTransform _worldTransform;
};

NS_CC_EXT_ARMATURE_END

#endif /*__CCBONE_H__*/
