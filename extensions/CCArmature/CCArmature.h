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

namespace cocos2d { namespace extension { namespace armature {
    
class  Armature : public NodeRGBA, public BlendProtocol 
{

public:
   /**
	* Allocates and initializes a armature.
	* @return A initialized armature which is marked as "autorelease".
	*/
	static Armature *create();
    
   /**
	* Allocates a armature, and use the ArmatureData named name in ArmatureDataManager to initializes the armature. 
	*
	* @param  name Armature will use the name to find to the ArmatureData to initializes it.
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
     * Init a armature with specified name
     * @param name Armature name
     */
    virtual bool init(const char *name);

	virtual bool init(const char *name, Bone *parentBone);
    /**
     * Add a Bone to this Armature, 
     *
     * @param bone  The Bone you want to add to Armature
     * @param parentName   The parent Bone's name you want to add to . If it's  NULL, then set Armature to it's parent
     */
    virtual void addBone(Bone *bone, const char* parentName);
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
	virtual Rect boundingBox();
    
    Bone *getBoneAtPoint(float x, float y);
    
	virtual void visit();
    virtual void update(float dt);
	virtual void draw();

	virtual AffineTransform nodeToParentTransform();

	/**
	 * Set contentsize and Calculate anchor point. 
     */
	virtual void updateOffsetPoint();

	inline void setBlendFunc(ccBlendFunc blendFunc) { _blendFunc = blendFunc; }
	inline ccBlendFunc getBlendFunc(void) { return _blendFunc; }

protected:
    
    /*
     * Used to create Bone internal
     */
	Bone *createBone(const char *boneName );
    

	CC_SYNTHESIZE_RETAIN(ArmatureAnimation *, _animation, Animation);
    
    CC_SYNTHESIZE(ArmatureData *, _armatureData, ArmatureData);

	CC_SYNTHESIZE(BatchNode*, _batchNode, BatchNode);

	CC_SYNTHESIZE_PASS_BY_REF(std::string, _name, Name);

	CC_SYNTHESIZE(TextureAtlas*, _atlas, TextureAtlas);

	CC_SYNTHESIZE(Bone*, _parentBone, ParentBone);
protected:
    Dictionary *_boneDic;                    //! The dictionary of the bones, include all bones in the armature, no matter it is the direct bone or the indirect bone. It is different from _chindren.

	Array *_topBoneList;

    static std::map<int, Armature*> _armatureIndexDic;	//! Use to save armature zorder info, 

	ccBlendFunc _blendFunc;                    //! It's required for TextureProtocol inheritance

	Point _offsetPoint;
};

}}} // namespace cocos2d { namespace extension { namespace armature {

#endif /*__CCARMATURE_H__*/
