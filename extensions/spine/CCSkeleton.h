/*******************************************************************************
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

#ifndef SPINE_CCSKELETON_H_
#define SPINE_CCSKELETON_H_

#include <spine/spine.h>
#include "cocos2d.h"

namespace cocos2d { namespace extension {

/**
Draws a skeleton.
*/
class CC_EX_DLL CCSkeleton: public cocos2d::CCNodeRGBA, public cocos2d::CCBlendProtocol {
public:
	Skeleton* skeleton;
	Bone* rootBone;
	float timeScale;
	bool debugSlots;
	bool debugBones;
	bool premultipliedAlpha;

	static CCSkeleton* createWithData (SkeletonData* skeletonData, bool ownsSkeletonData = false);
	static CCSkeleton* createWithFile (const char* skeletonDataFile, Atlas* atlas, float scale = 1);
	static CCSkeleton* createWithFile (const char* skeletonDataFile, const char* atlasFile, float scale = 1);

	CCSkeleton (SkeletonData* skeletonData, bool ownsSkeletonData = false);
	CCSkeleton (const char* skeletonDataFile, Atlas* atlas, float scale = 1);
	CCSkeleton (const char* skeletonDataFile, const char* atlasFile, float scale = 1);

	virtual ~CCSkeleton ();

	virtual void update (float deltaTime);
	virtual void draw ();
	virtual cocos2d::CCRect boundingBox ();

	// --- Convenience methods for common Skeleton_* functions.
	void updateWorldTransform ();

	void setToSetupPose ();
	void setBonesToSetupPose ();
	void setSlotsToSetupPose ();

	/* Returns 0 if the bone was not found. */
	Bone* findBone (const char* boneName) const;
	/* Returns 0 if the slot was not found. */
	Slot* findSlot (const char* slotName) const;
	
	/* Sets the skin used to look up attachments not found in the SkeletonData defaultSkin. Attachments from the new skin are
	 * attached if the corresponding attachment from the old skin was attached. Returns false if the skin was not found.
	 * @param skin May be 0.*/
	bool setSkin (const char* skinName);
	
	/* Returns 0 if the slot or attachment was not found. */
	Attachment* getAttachment (const char* slotName, const char* attachmentName) const;
	/* Returns false if the slot or attachment was not found. */
	bool setAttachment (const char* slotName, const char* attachmentName);

	// --- CCBlendProtocol
	CC_PROPERTY(cocos2d::ccBlendFunc, blendFunc, BlendFunc);
	virtual void setOpacityModifyRGB (bool value);
	virtual bool isOpacityModifyRGB ();

protected:
	CCSkeleton ();
	void setSkeletonData (SkeletonData* skeletonData, bool ownsSkeletonData);
	cocos2d::CCTextureAtlas* getTextureAtlas (RegionAttachment* regionAttachment) const;

private:
	bool ownsSkeletonData;
	Atlas* atlas;
	void initialize ();
};

}} // namespace cocos2d { namespace extension {

#endif /* SPINE_CCSKELETON_H_ */
