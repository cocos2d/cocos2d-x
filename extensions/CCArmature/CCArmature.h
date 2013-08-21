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

NS_CC_EXT_BEGIN
    
class  CCArmature : public CCNodeRGBA, public CCBlendProtocol 
{

public:
   /**
	* Allocates and initializes an armature.
	* @return An initialized armature which is marked as "autorelease".
	*/
	static CCArmature *create();
    
   /**
	* Allocates an armature, and use the CCArmatureData named name in CCArmatureDataManager to initializes the armature. 
	*
	* @param  name CCArmature will use the name to find the CCArmatureData to initializes it.
	* @return A initialized armature which is marked as "autorelease".
	*/
	static CCArmature *create(const char *name);

	static CCArmature *create(const char *name, CCBone *parentBone);

public:
    CCArmature();
    ~CCArmature(void);

    /**
     * Init the empty armature
     */
    virtual bool init();
    
    /**
     * Init an armature with specified name
     * @param name CCArmature name
     */
    virtual bool init(const char *name);

	virtual bool init(const char *name, CCBone *parentBone);
    /**
     * Add a CCBone to this CCArmature, 
     *
     * @param bone  The CCBone you want to add to CCArmature
     * @param parentName   The parent CCBone's name you want to add to . If it's  NULL, then set CCArmature to its parent
     */
    virtual void addBone(CCBone *bone, const char* parentName);
    /**
     * Get a bone with the specified name
     *
     * @param name The bone's name you want to get
     */
    virtual CCBone *getBone(const char *name) const;
    /**
     * Change a bone's parent with the specified parent name.
     *
     * @param bone The bone you want to change parent
	 * @param parentName The new parent's name.
     */
    virtual void changeBoneParent(CCBone *bone, const char *parentName);
    /**
     * Remove a bone with the specified name. If recursion it will also remove child CCBone recursionly.
     *
     * @param bone The bone you want to remove
	 * @param recursion Determine whether remove the bone's child  recursion.
     */
    virtual void removeBone(CCBone *bone, bool recursion);

    /**
     * Get CCArmature's bone dictionary
     * @return CCArmature's bone dictionary
     */
	CCDictionary *getBoneDic();

	/**
     * This boundingBox will calculate all bones' boundingBox every time
     */
	virtual CCRect boundingBox();
    
    CCBone *getBoneAtPoint(float x, float y);
    
	virtual void visit();
    virtual void update(float dt);
	virtual void draw();

	virtual CCAffineTransform nodeToParentTransform();

	/**
	 * Set contentsize and Calculate anchor point. 
     */
	virtual void updateOffsetPoint();

	inline void setBlendFunc(ccBlendFunc blendFunc) { m_sBlendFunc = blendFunc; }
	inline ccBlendFunc getBlendFunc(void) { return m_sBlendFunc; }

	virtual void setAnimation(CCArmatureAnimation *animation);
	virtual CCArmatureAnimation *getAnimation();
protected:
    
    /*
     * Used to create CCBone internal
     */
	CCBone *createBone(const char *boneName );
    
	//! Update blend function
	void updateBlendType(CCBlendType blendType);
    
    CC_SYNTHESIZE(CCArmatureData *, m_pArmatureData, ArmatureData);

	CC_SYNTHESIZE(CCBatchNode*, m_pBatchNode, BatchNode);

	CC_SYNTHESIZE_PASS_BY_REF(std::string, m_strName, Name);

	CC_SYNTHESIZE(CCTextureAtlas*, m_pAtlas, TextureAtlas);

	CC_SYNTHESIZE(CCBone*, m_pParentBone, ParentBone);

	CC_SYNTHESIZE(float, m_fVersion, Version);

	CC_SYNTHESIZE_READONLY(bool, m_bArmatureTransformDirty, ArmatureTransformDirty);
protected:
    CCDictionary *m_pBoneDic;                    //! The dictionary of the bones, include all bones in the armature, no matter it is the direct bone or the indirect bone. It is different from m_pChindren.

	CCArray *m_pTopBoneList;

    static std::map<int, CCArmature*> m_sArmatureIndexDic;	//! Use to save armature zorder info, 

	ccBlendFunc m_sBlendFunc;                    //! It's required for CCTextureProtocol inheritance

	CCPoint m_pOffsetPoint;

	CCArmatureAnimation *m_pAnimation;

#if ENABLE_PHYSICS_BOX2D_DETECT
	CC_PROPERTY(b2Body*, m_pB2Body, B2Body);
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
	CC_PROPERTY(cpBody*, m_pCPBody, CPBody);
#endif
};

NS_CC_EXT_END

#endif /*__CCARMATURE_H__*/
