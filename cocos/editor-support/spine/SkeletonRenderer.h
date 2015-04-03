/******************************************************************************
 * Spine Runtimes Software License
 * Version 2.1
 * 
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 * 
 * You are granted a perpetual, non-exclusive, non-sublicensable and
 * non-transferable license to install, execute and perform the Spine Runtimes
 * Software (the "Software") solely for internal use. Without the written
 * permission of Esoteric Software (typically granted by licensing Spine), you
 * may not (a) modify, translate, adapt or otherwise create derivative works,
 * improvements of the Software or develop new applications using the Software
 * or (b) remove, delete, alter or obscure any trademarks or any copyright,
 * trademark, patent or other intellectual property or proprietary rights
 * notices on or in the Software, including any copy thereof. Redistributions
 * in binary or source form must include this license and terms.
 * 
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef SPINE_SKELETONRENDERER_H_
#define SPINE_SKELETONRENDERER_H_

#include <spine/spine.h>
#include "cocos2d.h"

namespace spine {

class PolygonBatch;

/** Draws a skeleton. */
class SkeletonRenderer: public cocos2d::Node, public cocos2d::BlendProtocol {
public:
	static SkeletonRenderer* createWithData (spSkeletonData* skeletonData, bool ownsSkeletonData = false);
	static SkeletonRenderer* createWithFile (const std::string& skeletonDataFile, spAtlas* atlas, float scale = 1);
	static SkeletonRenderer* createWithFile (const std::string& skeletonDataFile, const std::string& atlasFile, float scale = 1);

	virtual void update (float deltaTime) override;
	virtual void draw (cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t transformFlags) override;
	virtual void drawSkeleton (const cocos2d::Mat4& transform, uint32_t transformFlags);
	virtual cocos2d::Rect getBoundingBox () const override;

	spSkeleton* getSkeleton();

	void setTimeScale(float scale);
	float getTimeScale() const;

	void setDebugSlotsEnabled(bool enabled);
	bool getDebugSlotsEnabled() const;

	void setDebugBonesEnabled(bool enabled);
	bool getDebugBonesEnabled() const;

	// --- Convenience methods for common Skeleton_* functions.
	void updateWorldTransform ();

	void setToSetupPose ();
	void setBonesToSetupPose ();
	void setSlotsToSetupPose ();

	/* Returns 0 if the bone was not found. */
	spBone* findBone (const std::string& boneName) const;
	/* Returns 0 if the slot was not found. */
	spSlot* findSlot (const std::string& slotName) const;
	
	/* Sets the skin used to look up attachments not found in the SkeletonData defaultSkin. Attachments from the new skin are
	 * attached if the corresponding attachment from the old skin was attached. Returns false if the skin was not found.
	 * @param skin May be 0.*/
	bool setSkin (const std::string& skinName);
	
	/* Returns 0 if the slot or attachment was not found. */
	spAttachment* getAttachment (const std::string& slotName, const std::string& attachmentName) const;
	/* Returns false if the slot or attachment was not found. */
	bool setAttachment (const std::string& slotName, const std::string& attachmentName);

	// --- BlendProtocol
	virtual void setBlendFunc (const cocos2d::BlendFunc& blendFunc);
	virtual const cocos2d::BlendFunc& getBlendFunc () const;
	virtual void setOpacityModifyRGB (bool value);
	virtual bool isOpacityModifyRGB () const;

protected:
	SkeletonRenderer ();
	SkeletonRenderer (spSkeletonData* skeletonData, bool ownsSkeletonData = false);
	SkeletonRenderer (const std::string& skeletonDataFile, spAtlas* atlas, float scale = 1);
	SkeletonRenderer (const std::string& skeletonDataFile, const std::string& atlasFile, float scale = 1);
	virtual ~SkeletonRenderer ();
	void initialize ();

	void setSkeletonData (spSkeletonData* skeletonData, bool ownsSkeletonData);
	virtual cocos2d::Texture2D* getTexture (spRegionAttachment* attachment) const;
	virtual cocos2d::Texture2D* getTexture (spMeshAttachment* attachment) const;
	virtual cocos2d::Texture2D* getTexture (spSkinnedMeshAttachment* attachment) const;

	bool _ownsSkeletonData;
	spAtlas* _atlas;
	cocos2d::CustomCommand _drawCommand;
	cocos2d::BlendFunc _blendFunc;
	PolygonBatch* _batch;
	float* _worldVertices;
	bool _premultipliedAlpha;
	spSkeleton* _skeleton;
	float _timeScale;
	bool _debugSlots;
	bool _debugBones;
};

}

#endif /* SPINE_SKELETONRENDERER_H_ */
