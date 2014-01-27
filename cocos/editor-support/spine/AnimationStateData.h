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

#ifndef SPINE_ANIMATIONSTATEDATA_H_
#define SPINE_ANIMATIONSTATEDATA_H_

#include <spine/Animation.h>
#include <spine/SkeletonData.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	spSkeletonData* const skeletonData;
	float defaultMix;
	const void* const entries;
} spAnimationStateData;

spAnimationStateData* spAnimationStateData_create (spSkeletonData* skeletonData);
void spAnimationStateData_dispose (spAnimationStateData* self);

void spAnimationStateData_setMixByName (spAnimationStateData* self, const char* fromName, const char* toName, float duration);
void spAnimationStateData_setMix (spAnimationStateData* self, spAnimation* from, spAnimation* to, float duration);
/* Returns 0 if there is no mixing between the animations. */
float spAnimationStateData_getMix (spAnimationStateData* self, spAnimation* from, spAnimation* to);

#ifdef SPINE_SHORT_NAMES
typedef spAnimationStateData AnimationStateData;
#define AnimationStateData_create(...) spAnimationStateData_create(__VA_ARGS__)
#define AnimationStateData_dispose(...) spAnimationStateData_dispose(__VA_ARGS__)
#define AnimationStateData_setMixByName(...) spAnimationStateData_setMixByName(__VA_ARGS__)
#define AnimationStateData_setMix(...) spAnimationStateData_setMix(__VA_ARGS__)
#define AnimationStateData_getMix(...) spAnimationStateData_getMix(__VA_ARGS__)
#endif

#ifdef __cplusplus
}
#endif

#endif /* SPINE_ANIMATIONSTATEDATA_H_ */
