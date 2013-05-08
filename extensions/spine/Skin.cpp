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

#include <spine/Skin.h>
#include <spine/extension.h>
#include <stdio.h>

namespace cocos2d { namespace extension {

typedef struct _Entry _Entry;
struct _Entry {
	int slotIndex;
	const char* name;
	Attachment* attachment;
	_Entry* next;
};

_Entry* _Entry_create (int slotIndex, const char* name, Attachment* attachment) {
	_Entry* self = NEW(_Entry);
	self->slotIndex = slotIndex;
	MALLOC_STR(self->name, name);
	self->attachment = attachment;
	return self;
}

void _Entry_dispose (_Entry* self) {
	Attachment_dispose(self->attachment);
	FREE(self->name);
	FREE(self);
}

/**/

typedef struct {
	Skin super;
	_Entry* entries;
} _Internal;

Skin* Skin_create (const char* name) {
	Skin* self = SUPER(NEW(_Internal));
	MALLOC_STR(self->name, name);
	return self;
}

void Skin_dispose (Skin* self) {
	_Entry* entry = SUB_CAST(_Internal, self)->entries;
	while (entry) {
		_Entry* nextEtry = entry->next;
		_Entry_dispose(entry);
		entry = nextEtry;
	}

	FREE(self->name);
	FREE(self);
}

void Skin_addAttachment (Skin* self, int slotIndex, const char* name, Attachment* attachment) {
	_Entry* newEntry = _Entry_create(slotIndex, name, attachment);
	newEntry->next = SUB_CAST(_Internal, self)->entries;
	SUB_CAST(_Internal, self)->entries = newEntry;
}

Attachment* Skin_getAttachment (const Skin* self, int slotIndex, const char* name) {
	const _Entry* entry = SUB_CAST(_Internal, self) ->entries;
	while (entry) {
		if (entry->slotIndex == slotIndex && strcmp(entry->name, name) == 0) return entry->attachment;
		entry = entry->next;
	}
	return 0;
}

void Skin_attachAll (const Skin* self, Skeleton* skeleton, const Skin* oldSkin) {
	const _Entry *entry = SUB_CAST(_Internal, oldSkin) ->entries;
	while (entry) {
		Slot *slot = skeleton->slots[entry->slotIndex];
		if (slot->attachment == entry->attachment) {
			Attachment *attachment = Skin_getAttachment(self, entry->slotIndex, entry->name);
			if (attachment) Slot_setAttachment(slot, attachment);
		}
		entry = entry->next;
	}
}

}} // namespace cocos2d { namespace extension {
