/******************************************************************************
 * Spine Runtime Software License - Version 1.1
 * 
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms in whole or in part, with
 * or without modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. A Spine Essential, Professional, Enterprise, or Education License must
 *    be purchased from Esoteric Software and the license must remain valid:
 *    http://esotericsoftware.com/
 * 2. Redistributions of source code must retain this license, which is the
 *    above copyright notice, this declaration of conditions and the following
 *    disclaimer.
 * 3. Redistributions in binary form must reproduce this license, which is the
 *    above copyright notice, this declaration of conditions and the following
 *    disclaimer, in the documentation and/or other materials provided with the
 *    distribution.
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
 *****************************************************************************/

#ifndef SPINE_BONE_H_
#define SPINE_BONE_H_

#include <spine/BoneData.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct spBone spBone;
struct spBone {
	spBoneData* const data;
	spBone* const parent;
	float x, y;
	float rotation;
	float scaleX, scaleY;

	float const m00, m01, worldX; /* a b x */
	float const m10, m11, worldY; /* c d y */
	float const worldRotation;
	float const worldScaleX, worldScaleY;
};

void spBone_setYDown (int/*bool*/yDown);

/* @param parent May be 0. */
spBone* spBone_create (spBoneData* data, spBone* parent);
void spBone_dispose (spBone* self);

void spBone_setToSetupPose (spBone* self);

void spBone_updateWorldTransform (spBone* self, int/*bool*/flipX, int/*bool*/flipY);

#ifdef SPINE_SHORT_NAMES
typedef spBone Bone;
#define Bone_setYDown(...) spBone_setYDown(__VA_ARGS__)
#define Bone_create(...) spBone_create(__VA_ARGS__)
#define Bone_dispose(...) spBone_dispose(__VA_ARGS__)
#define Bone_setToSetupPose(...) spBone_setToSetupPose(__VA_ARGS__)
#define Bone_updateWorldTransform(...) spBone_updateWorldTransform(__VA_ARGS__)
#endif

#ifdef __cplusplus
}
#endif

#endif /* SPINE_BONE_H_ */
