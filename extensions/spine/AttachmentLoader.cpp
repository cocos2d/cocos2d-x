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

#include <spine/AttachmentLoader.h>
#include <stdio.h>
#include <spine/extension.h>

namespace cocos2d { namespace extension {

typedef struct _AttachmentLoaderVtable {
	Attachment* (*newAttachment) (AttachmentLoader* self, Skin* skin, AttachmentType type, const char* name);
	void (*dispose) (AttachmentLoader* self);
} _AttachmentLoaderVtable;

void _AttachmentLoader_init (AttachmentLoader* self, /**/
		void (*dispose) (AttachmentLoader* self), /**/
		Attachment* (*newAttachment) (AttachmentLoader* self, Skin* skin, AttachmentType type, const char* name)) {
	CONST_CAST(void*, self->vtable) = NEW(_AttachmentLoaderVtable);
	VTABLE(AttachmentLoader, self) ->dispose = dispose;
	VTABLE(AttachmentLoader, self) ->newAttachment = newAttachment;
}

void _AttachmentLoader_deinit (AttachmentLoader* self) {
	FREE(self->vtable);
	FREE(self->error1);
	FREE(self->error2);
}

void AttachmentLoader_dispose (AttachmentLoader* self) {
	VTABLE(AttachmentLoader, self) ->dispose(self);
	FREE(self);
}

Attachment* AttachmentLoader_newAttachment (AttachmentLoader* self, Skin* skin, AttachmentType type, const char* name) {
	FREE(self->error1);
	FREE(self->error2);
	self->error1 = 0;
	self->error2 = 0;
	return VTABLE(AttachmentLoader, self) ->newAttachment(self, skin, type, name);
}

void _AttachmentLoader_setError (AttachmentLoader* self, const char* error1, const char* error2) {
	FREE(self->error1);
	FREE(self->error2);
	MALLOC_STR(self->error1, error1);
	MALLOC_STR(self->error2, error2);
}

void _AttachmentLoader_setUnknownTypeError (AttachmentLoader* self, AttachmentType type) {
	char buffer[16];
	sprintf(buffer, "%d", type);
	_AttachmentLoader_setError(self, "Unknown attachment type: ", buffer);
}

}} // namespace cocos2d { namespace extension {
