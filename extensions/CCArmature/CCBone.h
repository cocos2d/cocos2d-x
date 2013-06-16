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
#include "external_tool/CCTexture2DMutable.h"
#include "display/CCDecorativeDisplay.h"
#include "display/CCDisplayManager.h"

NS_CC_EXT_BEGIN

class CCArmature;

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
    CCBone();
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
     * Add display and use  _DisplayData init the display.
     * If index already have a display, then replace it.
     * If index is current display index, then also change display to _index
     *
     * @param displayData it include the display information, like DisplayType.
     *          If you want to create a sprite display, then create a CCSpriteDisplayData param
     *
     *	@param 	_index the index of the display you want to replace or add to
     *          -1 : append display from back
     */
    void addDisplay(CCDisplayData *displayData, int index);

    void changeDisplayByIndex(int index, bool force);

    /**
     * Add a child to this bone, and it will let this child call setParent(CCBone *_parent) function to set self to it's parent
     *	@param 	_child  the child you want to add
     */
    void addChildBone(CCBone *_child);

    /**
     * Set parent bone.
     * If _parent is NUll, then also remove this bone from armature.
     * It will not set the CCArmature, if you want to add the bone to a CCArmature, you should use CCArmature::addBone(CCBone *bone, const char* _parentName).
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

    /**
     * Remove itself from its parent CCBone.
     * @param 	recursion    whether or not remove Child display
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

    //! Update color to render display
    void updateColor();

    CCArray *getChildren();
    CCTween *getTween();

    virtual void setZOrder(int zOrder);
    /*
     * Whether or not the bone's transform property changed. if true, the bone will update the transform.
     */
    virtual void setTransformDirty(bool dirty);

    virtual bool isTransformDirty();

    virtual CCAffineTransform nodeToArmatureTransform();

public:
    /*
     *  The origin state of the CCBone. Display's state is effected by _boneData, _node, _tweenData
     *  when call setData function, it will copy from the CCBoneData.
     */
    CC_PROPERTY(CCBoneData *, _boneData, BoneData);

    //! A weak reference to the CCArmature
    CC_PROPERTY(CCArmature *, _armature, Armature);

    //! A weak reference to the child CCArmature
    CC_PROPERTY(CCArmature *, _childArmature, ChildArmature);

    CC_SYNTHESIZE(CCDisplayManager *, _displayManager, DisplayManager)

    /*
     *	When CCArmature play a animation, if there is not a CCMovementBoneData of this bone in this CCMovementData, this bone will hide.
     *	Set IgnoreMovementBoneData to true, then this bone will also show.
     */
    CC_SYNTHESIZE_PASS_BY_REF(bool, _ignoreMovementBoneData, IgnoreMovementBoneData)

protected:
    CCTween *_tween;				//! Calculate tween effect

    //! Used for make tween effect between every frame
    CC_SYNTHESIZE_READONLY(CCFrameData *, _tweenData, TweenData);

    CC_SYNTHESIZE_PASS_BY_REF(std::string, _name, Name);

    //! Lazy allocs
    void childrenAlloc(void);
    CCArray *_children;

    CCBone *_parent;				//! A weak reference to it's parent
    bool _transformDirty;			//! Whether or not transform dirty

    //! self Transform, use this to change display's state
    CCAffineTransform _worldTransform;
};

NS_CC_EXT_END

#endif /*__CCBONE_H__*/
