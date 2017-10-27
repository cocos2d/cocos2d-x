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

#ifndef SPINE_ATTACHMENTLOADER_H_
#define SPINE_ATTACHMENTLOADER_H_

#include <spine/dll.h>
#include <spine/Attachment.h>
#include <spine/Skin.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct spAttachmentLoader {
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
} spAttachmentLoader;

SP_API void spAttachmentLoader_dispose (spAttachmentLoader* self);

/* Called to create each attachment. Returns 0 to not load an attachment. If 0 is returned and _spAttachmentLoader_setError was
 * called, an error occurred. */
SP_API spAttachment* spAttachmentLoader_createAttachment (spAttachmentLoader* self, spSkin* skin, spAttachmentType type, const char* name,
		const char* path);
/* Called after the attachment has been fully configured. */
SP_API void spAttachmentLoader_configureAttachment (spAttachmentLoader* self, spAttachment* attachment);
/* Called just before the attachment is disposed. This can release allocations made in spAttachmentLoader_configureAttachment. */
SP_API void spAttachmentLoader_disposeAttachment (spAttachmentLoader* self, spAttachment* attachment);

#ifdef SPINE_SHORT_NAMES
typedef spAttachmentLoader AttachmentLoader;
#define AttachmentLoader_dispose(...) spAttachmentLoader_dispose(__VA_ARGS__)
#define AttachmentLoader_createAttachment(...) spAttachmentLoader_createAttachment(__VA_ARGS__)
#define AttachmentLoader_configureAttachment(...) spAttachmentLoader_configureAttachment(__VA_ARGS__)
#define AttachmentLoader_disposeAttachment(...) spAttachmentLoader_disposeAttachment(__VA_ARGS__)
#endif

#ifdef __cplusplus
}
#endif

#endif /* SPINE_ATTACHMENTLOADER_H_ */
