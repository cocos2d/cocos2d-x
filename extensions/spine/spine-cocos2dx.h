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

#ifndef SPINE_COCOS2DX_H_
#define SPINE_COCOS2DX_H_

#include <spine/spine.h>
#include "cocos2d.h"

namespace spine {

class CCSkeleton: public cocos2d::CCNodeRGBA, public cocos2d::CCBlendProtocol {
private:
	bool ownsSkeleton;
	bool ownsStateData;
	Atlas* atlas;

public:
	Skeleton* const skeleton;
	AnimationState* const state;
	float timeScale;
	bool debugSlots;
	bool debugBones;

	static CCSkeleton* create (const char* skeletonDataFile, Atlas* atlas, float scale = 1);
	static CCSkeleton* create (const char* skeletonDataFile, const char* atlasFile, float scale = 1);
	static CCSkeleton* create (SkeletonData* skeletonData, AnimationStateData* stateData = 0);

	CCSkeleton (SkeletonData* skeletonData, AnimationStateData* stateData = 0);
	virtual ~CCSkeleton ();

	void setMix (const char* fromName, const char* toName, float duration);
	void setAnimation (const char* animationName, bool loop);
	void clearAnimation ();

	void updateWorldTransform ();

	void setToBindPose ();
	void setBonesToBindPose ();
	void setSlotsToBindPose ();
	
	/* Returns 0 if the bone was not found. */
	Bone* findBone (const char* boneName) const;
	/* Returns -1 if the bone was not found. */
	int findBoneIndex (const char* boneName) const;

	/* Returns 0 if the slot was not found. */
	Slot* findSlot (const char* slotName) const;
	/* Returns -1 if the slot was not found. */
	int findSlotIndex (const char* slotName) const;

	/* Sets the skin used to look up attachments not found in the SkeletonData defaultSkin. Attachments from the new skin are
	 * attached if the corresponding attachment from the old skin was attached. Returns false if the skin was not found.
	 * @param skin May be 0.*/
	bool setSkin (const char* skinName);

	/* Returns 0 if the slot or attachment was not found. */
	Attachment* getAttachment (const char* slotName, const char* attachmentName) const;
	/* Returns 0 if the slot or attachment was not found. */
	Attachment* getAttachment (int slotIndex, const char* attachmentName) const;
	/* Returns false if the slot or attachment was not found. */
	bool setAttachment (const char* slotName, const char* attachmentName);

	virtual void update (float deltaTime);
	virtual void draw ();
	virtual cocos2d::CCRect boundingBox ();

	// CCBlendProtocol
	CC_PROPERTY(cocos2d::ccBlendFunc, blendFunc, BlendFunc);
};

/**/

void RegionAttachment_updateQuad (RegionAttachment* self, Slot* slot, cocos2d::ccV3F_C4B_T2F_Quad* quad);

}

#endif /* SPINE_COCOS2DX_H_ */
