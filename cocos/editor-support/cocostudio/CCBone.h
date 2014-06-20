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
#include "2d/CCNode.h"
#include "math/CCMath.h"

namespace cocostudio {

class Armature;

class Bone : public cocos2d::Node
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
     * Initializes an empty Bone with nothing init.
     */
    virtual bool init() override;

    /**
     * Initializes a Bone with the specified name
     * @param name Bone's name.
     */
    virtual bool init(const std::string& name);

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

    void addDisplay(cocos2d::Node *display, int index);

    void removeDisplay(int index);

    CC_DEPRECATED_ATTRIBUTE void changeDisplayByIndex(int index, bool force);
    CC_DEPRECATED_ATTRIBUTE void changeDisplayByName(const std::string& name, bool force);

    void changeDisplayWithIndex(int index, bool force);
    void changeDisplayWithName(const std::string& name, bool force);

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
     *          nullptr : remove this bone from armature
     */
    void setParentBone(Bone *parent);

    /**
     * Get parent bone
     * @return parent bone
     */
    Bone *getParentBone();

    using Node::removeFromParent;
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

    void update(float delta) override;

    void updateDisplayedColor(const cocos2d::Color3B &parentColor) override;
    void updateDisplayedOpacity(GLubyte parentOpacity) override;

    //! Update color to render display
    virtual void updateColor() override;

    //! Update zorder
    void updateZOrder();

    virtual void setLocalZOrder(int zOrder) override;

    Tween *getTween();

    /*
     * Whether or not the bone's transform property changed. if true, the bone will update the transform.
     */
    virtual void setTransformDirty(bool dirty) { _boneTransformDirty = dirty; }
    virtual bool isTransformDirty() { return _boneTransformDirty; }

    virtual cocos2d::Mat4 getNodeToArmatureTransform() const;
    virtual cocos2d::Mat4 getNodeToWorldTransform() const override;

    cocos2d::Node *getDisplayRenderNode();
    DisplayType getDisplayRenderNodeType();

    /*
     * Get the ColliderBody list in this bone. The object in the Array is ColliderBody.
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
     * Set blend function
     */
    virtual void setBlendFunc(const cocos2d::BlendFunc& blendFunc);
    virtual cocos2d::BlendFunc getBlendFunc(void) { return _blendFunc; }

    /*
     * Set if blend function is dirty 
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
