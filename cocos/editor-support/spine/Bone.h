/******************************************************************************
 * Spine Runtimes Software License
 * Version 2.3
 * 
 * Copyright (c) 2013-2015, Esoteric Software
 * All rights reserved.
 * 
 * You are granted a perpetual, non-exclusive, non-sublicensable and
 * non-transferable license to use, install, execute and perform the Spine
 * Runtimes Software (the "Software") and derivative works solely for personal
 * or internal use. Without the written permission of Esoteric Software (see
 * Section 2 of the Spine Software License Agreement), you may not (a) modify,
 * translate, adapt or otherwise create derivative works, improvements of the
 * Software or develop new applications using the Software or (b) remove,
 * delete, alter or obscure any trademarks or any copyright, trademark, patent
 * or other intellectual property or proprietary rights notices on or in the
 * Software, including any copy thereof. Redistributions in binary or source
 * form must include this license and terms.
 * 
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef SPINE_BONE_H_
#define SPINE_BONE_H_

#include <spine/BoneData.h>

#ifdef __cplusplus
extern "C" {
#endif

struct spSkeleton;

typedef struct spBone spBone;
struct spBone {
	spBoneData* const data;
	struct spSkeleton* const skeleton;
	spBone* const parent;
	int childrenCount;
	spBone** const children;
	float x, y, rotation, scaleX, scaleY, shearX, shearY;
	float appliedRotation;

	float const a, b, worldX;
	float const c, d, worldY;
	float const worldSignX, worldSignY;

	int/*bool*/ sorted;

#ifdef __cplusplus
	spBone() :
		data(0),
		skeleton(0),
		parent(0),
		childrenCount(0), children(0),
		x(0), y(0), rotation(0), scaleX(0), scaleY(0),
		appliedRotation(0),

		a(0), b(0), worldX(0),
		c(0), d(0), worldY(0),
		worldSignX(0), worldSignY(0),
		
		sorted(0) {
	}
#endif
};

void spBone_setYDown (int/*bool*/yDown);
int/*bool*/spBone_isYDown ();

/* @param parent May be 0. */
spBone* spBone_create (spBoneData* data, struct spSkeleton* skeleton, spBone* parent);
void spBone_dispose (spBone* self);

void spBone_setToSetupPose (spBone* self);

void spBone_updateWorldTransform (spBone* self);
void spBone_updateWorldTransformWith (spBone* self, float x, float y, float rotation, float scaleX, float scaleY, float shearX, float shearY);

float spBone_getWorldRotationX (spBone* self);
float spBone_getWorldRotationY (spBone* self);
float spBone_getWorldScaleX (spBone* self);
float spBone_getWorldScaleY (spBone* self);

float spBone_worldToLocalRotationX (spBone* self);
float spBone_worldToLocalRotationY (spBone* self);
void spBone_rotateWorld (spBone* self, float degrees);
void spBone_updateLocalTransform (spBone* self);

void spBone_worldToLocal (spBone* self, float worldX, float worldY, float* localX, float* localY);
void spBone_localToWorld (spBone* self, float localX, float localY, float* worldX, float* worldY);

#ifdef SPINE_SHORT_NAMES
typedef spBone Bone;
#define Bone_setYDown(...) spBone_setYDown(__VA_ARGS__)
#define Bone_isYDown() spBone_isYDown()
#define Bone_create(...) spBone_create(__VA_ARGS__)
#define Bone_dispose(...) spBone_dispose(__VA_ARGS__)
#define Bone_setToSetupPose(...) spBone_setToSetupPose(__VA_ARGS__)
#define Bone_updateWorldTransform(...) spBone_updateWorldTransform(__VA_ARGS__)
#define Bone_updateWorldTransformWith(...) spBone_updateWorldTransformWith(__VA_ARGS__)
#define Bone_getWorldRotationX(...) spBone_getWorldRotationX(__VA_ARGS__)
#define Bone_getWorldRotationY(...) spBone_getWorldRotationY(__VA_ARGS__)
#define Bone_getWorldScaleX(...) spBone_getWorldScaleX(__VA_ARGS__)
#define Bone_getWorldScaleY(...) spBone_getWorldScaleY(__VA_ARGS__)
#define Bone_worldToLocalRotationX(...) spBone_worldToLocalRotationX(__VA_ARGS__)
#define Bone_worldToLocalRotationY(...) spBone_worldToLocalRotationY(__VA_ARGS__)
#define Bone_rotateWorld(...) spBone_rotateWorld(__VA_ARGS__)
#define Bone_updateLocalTransform(...) spBone_updateLocalTransform(__VA_ARGS__)
#define Bone_worldToLocal(...) spBone_worldToLocal(__VA_ARGS__)
#define Bone_localToWorld(...) spBone_localToWorld(__VA_ARGS__)
#endif

#ifdef __cplusplus
}
#endif

#endif /* SPINE_BONE_H_ */
