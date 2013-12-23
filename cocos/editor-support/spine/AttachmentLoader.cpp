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

#include <spine/AttachmentLoader.h>
#include <stdio.h>
#include <spine/extension.h>

typedef struct _spAttachmentLoaderVtable {
	spAttachment* (*newAttachment) (spAttachmentLoader* self, spSkin* skin, spAttachmentType type, const char* name);
	void (*dispose) (spAttachmentLoader* self);
} _spAttachmentLoaderVtable;

void _spAttachmentLoader_init (spAttachmentLoader* self, /**/
void (*dispose) (spAttachmentLoader* self), /**/
spAttachment* (*newAttachment) (spAttachmentLoader* self, spSkin* skin, spAttachmentType type, const char* name)) {
	CONST_CAST(_spAttachmentLoaderVtable*, self->vtable) = NEW(_spAttachmentLoaderVtable);
	VTABLE(spAttachmentLoader, self)->dispose = dispose;
	VTABLE(spAttachmentLoader, self)->newAttachment = newAttachment;
}

void _spAttachmentLoader_deinit (spAttachmentLoader* self) {
	FREE(self->vtable);
	FREE(self->error1);
	FREE(self->error2);
}

void spAttachmentLoader_dispose (spAttachmentLoader* self) {
	VTABLE(spAttachmentLoader, self)->dispose(self);
	FREE(self);
}

spAttachment* spAttachmentLoader_newAttachment (spAttachmentLoader* self, spSkin* skin, spAttachmentType type, const char* name) {
	FREE(self->error1);
	FREE(self->error2);
	self->error1 = 0;
	self->error2 = 0;
	return VTABLE(spAttachmentLoader, self)->newAttachment(self, skin, type, name);
}

void _spAttachmentLoader_setError (spAttachmentLoader* self, const char* error1, const char* error2) {
	FREE(self->error1);
	FREE(self->error2);
	MALLOC_STR(self->error1, error1);
	MALLOC_STR(self->error2, error2);
}

void _spAttachmentLoader_setUnknownTypeError (spAttachmentLoader* self, spAttachmentType type) {
	char buffer[16];
	sprintf(buffer, "%d", type);
	_spAttachmentLoader_setError(self, "Unknown attachment type: ", buffer);
}
