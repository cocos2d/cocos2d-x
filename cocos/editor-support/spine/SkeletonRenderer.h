/******************************************************************************
 * Spine Runtimes Software License v2.5
 *
 * Copyright (c) 2013-2016, Esoteric Software
 * All rights reserved.
 *
 * You are granted a perpetual, non-exclusive, non-sublicensable, and
 * non-transferable license to use, install, execute, and perform the Spine
 * Runtimes software and derivative works solely for personal or internal
 * use. Without the written permission of Esoteric Software (see Section 2 of
 * the Spine Software License Agreement), you may not (a) modify, translate,
 * adapt, or develop new applications using the Spine Runtimes or otherwise
 * create derivative works or improvements of the Spine Runtimes or (b) remove,
 * delete, alter, or obscure any trademarks or any copyright, trademark, patent,
 * or other intellectual property or proprietary rights notices on or in the
 * Software, including any copy thereof. Redistributions in binary or source
 * form must include this license and terms.
 *
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, BUSINESS INTERRUPTION, OR LOSS OF
 * USE, DATA, OR PROFITS) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef SPINE_SKELETONRENDERER_H_
#define SPINE_SKELETONRENDERER_H_

#include <spine/spine.h>
#include "cocos2d.h"

namespace spine {
	
	class AttachmentVertices;
	
	/* Draws a skeleton. */
	class SkeletonRenderer: public cocos2d::Node, public cocos2d::BlendProtocol {
	public:
		CREATE_FUNC(SkeletonRenderer);
		static SkeletonRenderer* createWithSkeleton(Skeleton* skeleton, bool ownsSkeleton = false, bool ownsSkeletonData = false);
		static SkeletonRenderer* createWithData (SkeletonData* skeletonData, bool ownsSkeletonData = false);
		static SkeletonRenderer* createWithFile (const std::string& skeletonDataFile, Atlas* atlas, float scale = 1);
		static SkeletonRenderer* createWithFile (const std::string& skeletonDataFile, const std::string& atlasFile, float scale = 1);
		
		virtual void update (float deltaTime) override;
		virtual void draw (cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t transformFlags) override;
		virtual void drawDebug (cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t transformFlags);
		virtual cocos2d::Rect getBoundingBox () const override;
		virtual void onEnter () override;
		virtual void onExit () override;
		
		Skeleton* getSkeleton();
		
		void setTimeScale(float scale);
		float getTimeScale() const;
		
		/*  */
		void setDebugSlotsEnabled(bool enabled);
		bool getDebugSlotsEnabled() const;
		
		void setDebugBonesEnabled(bool enabled);
		bool getDebugBonesEnabled() const;
		
		void setDebugMeshesEnabled(bool enabled);
		bool getDebugMeshesEnabled() const;
		
		// --- Convenience methods for common Skeleton_* functions.
		void updateWorldTransform ();
		
		void setToSetupPose ();
		void setBonesToSetupPose ();
		void setSlotsToSetupPose ();
		
		/* Returns 0 if the bone was not found. */
		Bone* findBone (const std::string& boneName) const;
		/* Returns 0 if the slot was not found. */
		Slot* findSlot (const std::string& slotName) const;
		
		/* Sets the skin used to look up attachments not found in the SkeletonData defaultSkin. Attachments from the new skin are
		 * attached if the corresponding attachment from the old skin was attached.
		 * @param skin May be empty string ("") for no skin.*/
		void setSkin (const std::string& skinName);
		/** @param skin May be 0 for no skin.*/
		void setSkin (const char* skinName);
		
		/* Returns 0 if the slot or attachment was not found. */
		Attachment* getAttachment (const std::string& slotName, const std::string& attachmentName) const;
		/* Returns false if the slot or attachment was not found.
		 * @param attachmentName May be empty string ("") for no attachment. */
		bool setAttachment (const std::string& slotName, const std::string& attachmentName);
		/* @param attachmentName May be 0 for no attachment. */
		bool setAttachment (const std::string& slotName, const char* attachmentName);
		
		/* Enables/disables two color tinting for this instance. May break batching */
		void setTwoColorTint(bool enabled);
		/* Whether two color tinting is enabled */
		bool isTwoColorTint();
		
		/* Sets the vertex effect to be used, set to 0 to disable vertex effects */
		void setVertexEffect(VertexEffect* effect);
		
		/* Sets the range of slots that should be rendered. Use -1, -1 to clear the range */
		void setSlotsRange(int startSlotIndex, int endSlotIndex);
		
		// --- BlendProtocol
		virtual void setBlendFunc (const cocos2d::BlendFunc& blendFunc)override;
		virtual const cocos2d::BlendFunc& getBlendFunc () const override;
		virtual void setOpacityModifyRGB (bool value) override;
		virtual bool isOpacityModifyRGB () const override;
		
		// Frees global memory used for temporay vertex transformations.
		static void destroyScratchBuffers();
		
	CC_CONSTRUCTOR_ACCESS:
		SkeletonRenderer ();
		SkeletonRenderer(Skeleton* skeleton, bool ownsSkeleton = false, bool ownsSkeletonData = false, bool ownsAtlas = false);
		SkeletonRenderer (SkeletonData* skeletonData, bool ownsSkeletonData = false);
		SkeletonRenderer (const std::string& skeletonDataFile, Atlas* atlas, float scale = 1);
		SkeletonRenderer (const std::string& skeletonDataFile, const std::string& atlasFile, float scale = 1);
		
		virtual ~SkeletonRenderer ();
		
		void initWithSkeleton(Skeleton* skeleton, bool ownsSkeleton = false, bool ownsSkeletonData = false, bool ownsAtlas = false);
		void initWithData (SkeletonData* skeletonData, bool ownsSkeletonData = false);
		void initWithJsonFile (const std::string& skeletonDataFile, Atlas* atlas, float scale = 1);
		void initWithJsonFile (const std::string& skeletonDataFile, const std::string& atlasFile, float scale = 1);
		void initWithBinaryFile (const std::string& skeletonDataFile, Atlas* atlas, float scale = 1);
		void initWithBinaryFile (const std::string& skeletonDataFile, const std::string& atlasFile, float scale = 1);
		
		virtual void initialize ();
		
	protected:
		void setSkeletonData (SkeletonData* skeletonData, bool ownsSkeletonData);
		void setupGLProgramState(bool twoColorTintEnabled);
		
		bool _ownsSkeletonData;
		bool _ownsSkeleton;
		bool _ownsAtlas;
		Atlas* _atlas;
		AttachmentLoader* _attachmentLoader;
#ifndef CC_USE_NEW_RENDERER
		cocos2d::CustomCommand _debugCommand;
#endif
		cocos2d::BlendFunc _blendFunc;
		bool _premultipliedAlpha;
		Skeleton* _skeleton;
		float _timeScale;
		bool _debugSlots;
		bool _debugBones;
		bool _debugMeshes;
		SkeletonClipping* _clipper;
		VertexEffect* _effect;
#if CC_USE_NEW_RENDERER        		
        bool _twoColorTintEnabled = false;
#endif 
		int _startSlotIndex;
		int _endSlotIndex;
	};
	
}

#endif /* SPINE_SKELETONRENDERER_H_ */
