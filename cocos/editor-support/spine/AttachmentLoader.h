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

#ifndef SPINE_ATTACHMENTLOADER_H_
#define SPINE_ATTACHMENTLOADER_H_

#include <spine/Attachment.h>
#include <spine/Skin.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct spAttachmentLoader spAttachmentLoader;
struct spAttachmentLoader {
	const char* error1;
	const char* error2;

	const void* const vtable;
#ifdef __cplusplus
	spAttachmentLoader () :
					error1(0),
					error2(0),
					vtable(0) {
	}
#endif
};

void spAttachmentLoader_dispose (spAttachmentLoader* self);

/* Returns 0 to not load an attachment. If 0 is returned and spAttachmentLoader.error1 is set, an error occurred. */
spAttachment* spAttachmentLoader_newAttachment (spAttachmentLoader* self, spSkin* skin, spAttachmentType type, const char* name);

#ifdef SPINE_SHORT_NAMES
typedef spAttachmentLoader AttachmentLoader;
#define AttachmentLoader_dispose(...) spAttachmentLoader_dispose(__VA_ARGS__)
#define AttachmentLoader_newAttachment(...) spAttachmentLoader_newAttachment(__VA_ARGS__)
#endif

#ifdef __cplusplus
}
#endif

#endif /* SPINE_ATTACHMENTLOADER_H_ */
