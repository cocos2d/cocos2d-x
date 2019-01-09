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

#ifdef SPINE_UE4
#include "SpinePluginPrivatePCH.h"
#endif

#include <spine/Skin.h>

#include <spine/Attachment.h>
#include <spine/Skeleton.h>

#include <spine/Slot.h>

#include <assert.h>

using namespace spine;

Skin::AttachmentMap::AttachmentMap() {
}

void Skin::AttachmentMap::put(size_t slotIndex, const String &attachmentName, Attachment *attachment) {
	if (slotIndex >= _buckets.size())
		_buckets.setSize(slotIndex + 1, Vector<Entry>());
	Vector<Entry> &bucket = _buckets[slotIndex];
	int existing = findInBucket(bucket, attachmentName);
	if (existing >= 0) {
		bucket[existing]._attachment = attachment;
	} else {
		bucket.add(Entry(slotIndex, attachmentName, attachment));
	}
}

Attachment *Skin::AttachmentMap::get(size_t slotIndex, const String &attachmentName) {
	if (slotIndex >= _buckets.size()) return NULL;
	int existing = findInBucket(_buckets[slotIndex], attachmentName);
	return existing >= 0 ? _buckets[slotIndex][existing]._attachment : NULL;
}

void Skin::AttachmentMap::remove(size_t slotIndex, const String &attachmentName) {
	if (slotIndex >= _buckets.size()) return;
	int existing = findInBucket(_buckets[slotIndex], attachmentName);
	if (existing >= 0) _buckets[slotIndex].removeAt(existing);
}

int Skin::AttachmentMap::findInBucket(Vector<Entry> &bucket, const String &attachmentName) {
	for (size_t i = 0; i < bucket.size(); i++)
		if (bucket[i]._name == attachmentName) return i;
	return -1;
}

Skin::AttachmentMap::Entries Skin::AttachmentMap::getEntries() {
	return Skin::AttachmentMap::Entries(_buckets);
}

Skin::Skin(const String &name) : _name(name), _attachments() {
	assert(_name.length() > 0);
}

Skin::~Skin() {
	Skin::AttachmentMap::Entries entries = _attachments.getEntries();
	while (entries.hasNext()) {
		Skin::AttachmentMap::Entry entry = entries.next();
		delete entry._attachment;
	}
}

void Skin::addAttachment(size_t slotIndex, const String &name, Attachment *attachment) {
	assert(attachment);
	_attachments.put(slotIndex, name, attachment);
}

Attachment *Skin::getAttachment(size_t slotIndex, const String &name) {
	return _attachments.get(slotIndex, name);
}

void Skin::findNamesForSlot(size_t slotIndex, Vector<String> &names) {
	Skin::AttachmentMap::Entries entries = _attachments.getEntries();
	while (entries.hasNext()) {
		Skin::AttachmentMap::Entry &entry = entries.next();
		if (entry._slotIndex == slotIndex) {
			names.add(entry._name);
		}
	}
}

void Skin::findAttachmentsForSlot(size_t slotIndex, Vector<Attachment *> &attachments) {
	Skin::AttachmentMap::Entries entries = _attachments.getEntries();
	while (entries.hasNext()) {
		Skin::AttachmentMap::Entry &entry = entries.next();
		if (entry._slotIndex == slotIndex) {
			attachments.add(entry._attachment);
		}
	}
}

const String &Skin::getName() {
	return _name;
}

Skin::AttachmentMap::Entries Skin::getAttachments() {
	return _attachments.getEntries();
}

void Skin::attachAll(Skeleton &skeleton, Skin &oldSkin) {
	Vector<Slot *> &slots = skeleton.getSlots();
	Skin::AttachmentMap::Entries entries = oldSkin.getAttachments();
	while (entries.hasNext()) {
		Skin::AttachmentMap::Entry &entry = entries.next();
		int slotIndex = entry._slotIndex;
		Slot *slot = slots[slotIndex];

		if (slot->getAttachment() == entry._attachment) {
			Attachment *attachment = getAttachment(slotIndex, entry._name);
			if (attachment) {
				slot->setAttachment(attachment);
			}
		}
	}
}
