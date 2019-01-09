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

#ifndef Spine_HashMap_h
#define Spine_HashMap_h

#include <spine/Extension.h>
#include <spine/Vector.h>
#include <spine/SpineObject.h>

 // Required for new with line number and file name in  MSVC
#ifdef _MSC_VER
#pragma warning(disable:4291)
#endif

namespace spine {
template<typename K, typename V>
class SP_API HashMap : public SpineObject {
private:
	class Entry;

public:
	class SP_API Pair {
	public:
		explicit Pair(K &k, V &v) : key(k), value(v) {}

		K &key;
		V &value;
	};

	class SP_API Entries {
	public:
		friend class HashMap;

		explicit Entries(Entry *entry) : _entry(NULL), _hasChecked(false) {
			_start.next = entry;
			_entry = &_start;
		}

		Pair next() {
			assert(_entry);
			assert(_hasChecked);
			_entry = _entry->next;
			Pair pair(_entry->_key, _entry->_value);
			_hasChecked = false;
			return pair;
		}

		bool hasNext() {
			_hasChecked = true;
			return _entry->next;
		}

	private:
		bool _hasChecked;
		Entry _start;
		Entry *_entry;
	};

	HashMap() :
			_head(NULL),
			_size(0) {
	}

	~HashMap() {
		for (Entry *entry = _head; entry != NULL;) {
			Entry* next = entry->next;
			delete entry;
			entry = next;
		}
	}

	size_t size() {
		return _size;
	}

	void put(const K &key, const V &value) {
		Entry *entry = find(key);
		if (entry) {
			entry->_key = key;
			entry->_value = value;
		} else {
			entry = new(__FILE__, __LINE__) Entry();
			entry->_key = key;
			entry->_value = value;

			Entry *oldHead = _head;

			if (oldHead) {
				_head = entry;
				oldHead->prev = entry;
				entry->next = oldHead;
			} else {
				_head = entry;
			}
			_size++;
		}
	}

	bool containsKey(const K &key) {
		return find(key) != NULL;
	}

	bool remove(const K &key) {
		Entry *entry = find(key);
		if (!entry) return false;

		Entry *prev = entry->prev;
		Entry *next = entry->next;

		if (prev) prev->next = next;
		else _head = next;
		if (next) next->prev = entry->prev;

		delete entry;
		_size--;

		return true;
	}

	V operator[](const K &key) {
		Entry *entry = find(key);
		if (entry) return entry->_value;
		else {
			assert(false);
			return 0;
		}
	}

	Entries getEntries() const {
		return Entries(_head);
	}

private:
	Entry *find(const K &key) {
		for (Entry *entry = _head; entry != NULL; entry = entry->next) {
			if (entry->_key == key)
				return entry;
		}
		return NULL;
	}

	class SP_API Entry : public SpineObject {
	public:
		K _key;
		V _value;
		Entry *next;
		Entry *prev;

		Entry() : next(NULL), prev(NULL) {}
	};

	Entry *_head;
	size_t _size;
};
}

#endif /* Spine_HashMap_h */
