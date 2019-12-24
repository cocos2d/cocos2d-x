/******************************************************************************
 * Spine Runtimes License Agreement
 * Last updated May 1, 2019. Replaces all prior versions.
 *
 * Copyright (c) 2013-2019, Esoteric Software LLC
 *
 * Integration of the Spine Runtimes into software or otherwise creating
 * derivative works of the Spine Runtimes is permitted under the terms and
 * conditions of Section 2 of the Spine Editor License Agreement:
 * http://esotericsoftware.com/spine-editor-license
 *
 * Otherwise, it is permitted to integrate the Spine Runtimes into software
 * or otherwise create derivative works of the Spine Runtimes (collectively,
 * "Products"), provided that each user of the Products must obtain their own
 * Spine Editor license and redistribution of the Products in any form must
 * include this license and copyright notice.
 *
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE LLC "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
 * NO EVENT SHALL ESOTERIC SOFTWARE LLC BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, BUSINESS
 * INTERRUPTION, OR LOSS OF USE, DATA, OR PROFITS) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef SPINE_DEBUG_H
#define SPINE_DEBUG_H

#include <spine/Extension.h>

#include <map>

namespace spine {
class SP_API DebugExtension : public SpineExtension {
	struct Allocation {
		void *address;
		size_t size;
		const char *fileName;
		int line;

		Allocation() : address(NULL), size(0), fileName(NULL), line(0) {
		}

		Allocation(void *a, size_t s, const char *f, int l) : address(a), size(s), fileName(f), line(l) {
		}
	};

public:
	DebugExtension(SpineExtension* extension): _extension(extension), _allocations(0), _reallocations(0), _frees(0) {
	}

	void reportLeaks() {
		for (std::map<void*, Allocation>::iterator it = _allocated.begin(); it != _allocated.end(); it++) {
			printf("\"%s:%i (%zu bytes at %p)\n", it->second.fileName, it->second.line, it->second.size, it->second.address);
		}
		printf("allocations: %zu, reallocations: %zu, frees: %zu\n", _allocations, _reallocations, _frees);
		if (_allocated.empty()) printf("No leaks detected");
	}

	void clearAllocations() {
		_allocated.clear();
		_usedMemory = 0;
	}

	virtual void *_alloc(size_t size, const char *file, int line) {
		void *result = _extension->_alloc(size, file, line);
		_allocated[result] = Allocation(result, size, file, line);
		_allocations++;
		_usedMemory += size;
		return result;
	}

	virtual void *_calloc(size_t size, const char *file, int line) {
		void *result = _extension->_calloc(size, file, line);
		_allocated[result] = Allocation(result, size, file, line);
		_allocations++;
		_usedMemory += size;
		return result;
	}

	virtual void *_realloc(void *ptr, size_t size, const char *file, int line) {
		if (_allocated.count(ptr)) _usedMemory -= _allocated[ptr].size;
		_allocated.erase(ptr);
		void *result = _extension->_realloc(ptr, size, file, line);
		_reallocations++;
		_allocated[result] = Allocation(result, size, file, line);
		_usedMemory += size;
		return result;
	}

	virtual void _free(void *mem, const char *file, int line) {
		if (_allocated.count(mem)) {
			_extension->_free(mem, file, line);
			_frees++;
			_usedMemory -= _allocated[mem].size;
			_allocated.erase(mem);
			return;
		}

		printf("%s:%i (address %p): Double free or not allocated through SpineExtension\n", file, line, mem);
		_extension->_free(mem, file, line);
	}

	virtual char *_readFile(const String &path, int *length) {
		return _extension->_readFile(path, length);
	}
	
	size_t getUsedMemory() {
		return _usedMemory;
	}

private:
	SpineExtension* _extension;
	std::map<void*, Allocation> _allocated;
	size_t _allocations;
	size_t _reallocations;
	size_t _frees;
	size_t _usedMemory;
};
}


#endif //SPINE_DEBUG_H
