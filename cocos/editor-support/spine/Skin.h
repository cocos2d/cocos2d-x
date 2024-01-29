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

#ifndef SPINE_SKIN_H_
#define SPINE_SKIN_H_

#include "spine/dll.h"
#include "spine/Attachment.h"

#ifdef __cplusplus
extern "C" {
#endif

struct spSkeleton;

typedef struct spSkin {
	const char* const name;

#ifdef __cplusplus
	spSkin() :
		name(0) {
	}
#endif
} spSkin;

/* Private structs, needed by Skeleton */
typedef struct _Entry _Entry;
struct _Entry {
	int slotIndex;
	const char* name;
	spAttachment* attachment;
	_Entry* next;
};

typedef struct {
	spSkin super;
	_Entry* entries;
} _spSkin;

SP_API spSkin* spSkin_create (const char* name);
SP_API void spSkin_dispose (spSkin* self);

/* The Skin owns the attachment. */
SP_API void spSkin_addAttachment (spSkin* self, int slotIndex, const char* name, spAttachment* attachment);
/* Returns 0 if the attachment was not found. */
SP_API spAttachment* spSkin_getAttachment (const spSkin* self, int slotIndex, const char* name);

/* Returns 0 if the slot or attachment was not found. */
SP_API const char* spSkin_getAttachmentName (const spSkin* self, int slotIndex, int attachmentIndex);

/** Attach each attachment in this skin if the corresponding attachment in oldSkin is currently attached. */
SP_API void spSkin_attachAll (const spSkin* self, struct spSkeleton* skeleton, const spSkin* oldspSkin);

#ifdef SPINE_SHORT_NAMES
typedef spSkin Skin;
#define Skin_create(...) spSkin_create(__VA_ARGS__)
#define Skin_dispose(...) spSkin_dispose(__VA_ARGS__)
#define Skin_addAttachment(...) spSkin_addAttachment(__VA_ARGS__)
#define Skin_getAttachment(...) spSkin_getAttachment(__VA_ARGS__)
#define Skin_getAttachmentName(...) spSkin_getAttachmentName(__VA_ARGS__)
#define Skin_attachAll(...) spSkin_attachAll(__VA_ARGS__)
#endif

#ifdef __cplusplus
}
#endif

#endif /* SPINE_SKIN_H_ */
