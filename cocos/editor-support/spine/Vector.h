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

#ifndef Spine_Vector_h
#define Spine_Vector_h

#include <spine/Extension.h>
#include <spine/SpineObject.h>
#include <spine/SpineString.h>
#include <stdlib.h>
#include <memory>
#include <assert.h>

namespace spine {
template<typename T>
class SP_API Vector : public SpineObject {
public:
	Vector() : _size(0), _capacity(0), _buffer(NULL) {
	}

	Vector(const Vector &inVector) : _size(inVector._size), _capacity(inVector._capacity), _buffer(NULL) {
		if (_capacity > 0) {
			_buffer = allocate(_capacity);
			for (size_t i = 0; i < _size; ++i) {
				construct(_buffer + i, inVector._buffer[i]);
			}
		}
	}

	~Vector() {
		clear();
		deallocate(_buffer);
	}

	inline void clear() {
		for (size_t i = 0; i < _size; ++i) {
			destroy(_buffer + (_size - 1 - i));
		}

		_size = 0;
	}

	inline size_t getCapacity() const {
		return _capacity;
	}

	inline size_t size() const {
		return _size;
	}

	inline void setSize(size_t newSize, const T &defaultValue) {
		assert(newSize >= 0);
		size_t oldSize = _size;
		_size = newSize;
		if (_capacity < newSize) {
			_capacity = (int) (_size * 1.75f);
			if (_capacity < 8) _capacity = 8;
			_buffer = spine::SpineExtension::realloc<T>(_buffer, _capacity, __FILE__, __LINE__);
		}
		if (oldSize < _size) {
			for (size_t i = oldSize; i < _size; i++) {
				construct(_buffer + i, defaultValue);
			}
		}
	}

	inline void ensureCapacity(size_t newCapacity = 0) {
		if (_capacity >= newCapacity) return;
		_capacity = newCapacity;
		_buffer = SpineExtension::realloc<T>(_buffer, newCapacity, __FILE__, __LINE__);
	}

	inline void add(const T &inValue) {
		if (_size == _capacity) {
			// inValue might reference an element in this buffer
			// When we reallocate, the reference becomes invalid.
			// We thus need to create a defensive copy before
			// reallocating.
			T valueCopy = inValue;
			_capacity = (int) (_size * 1.75f);
			if (_capacity < 8) _capacity = 8;
			_buffer = spine::SpineExtension::realloc<T>(_buffer, _capacity, __FILE__, __LINE__);
			construct(_buffer + _size++, valueCopy);
		} else {
			construct(_buffer + _size++, inValue);
		}
	}

	inline void addAll(Vector<T> &inValue) {
		ensureCapacity(this->size() + inValue.size());
		for (size_t i = 0; i < inValue.size(); i++) {
			add(inValue[i]);
		}
	}

	inline void clearAndAddAll(Vector<T> &inValue) {
		this->clear();
		this->addAll(inValue);
	}

	inline void removeAt(size_t inIndex) {
		assert(inIndex < _size);

		--_size;

		if (inIndex != _size) {
			for (size_t i = inIndex; i < _size; ++i) {
				std::swap(_buffer[i], _buffer[i + 1]);
			}
		}

		destroy(_buffer + _size);
	}

	inline bool contains(const T &inValue) {
		for (size_t i = 0; i < _size; ++i) {
			if (_buffer[i] == inValue) {
				return true;
			}
		}

		return false;
	}

	inline int indexOf(const T &inValue) {
		for (size_t i = 0; i < _size; ++i) {
			if (_buffer[i] == inValue) {
				return (int)i;
			}
		}

		return -1;
	}

	inline T &operator[](size_t inIndex) {
		assert(inIndex < _size);

		return _buffer[inIndex];
	}

	inline friend bool operator==(Vector<T> &lhs, Vector<T> &rhs) {
		if (lhs.size() != rhs.size()) {
			return false;
		}

		for (size_t i = 0, n = lhs.size(); i < n; ++i) {
			if (lhs[i] != rhs[i]) {
				return false;
			}
		}

		return true;
	}

	inline friend bool operator!=(Vector<T> &lhs, Vector<T> &rhs) {
		return !(lhs == rhs);
	}

	inline T *buffer() {
		return _buffer;
	}

private:
	size_t _size;
	size_t _capacity;
	T *_buffer;

	inline T *allocate(size_t n) {
		assert(n > 0);

		T *ptr = SpineExtension::calloc<T>(n, __FILE__, __LINE__);

		assert(ptr);

		return ptr;
	}

	inline void deallocate(T *buffer) {
		if (_buffer) {
			SpineExtension::free(buffer, __FILE__, __LINE__);
		}
	}

	inline void construct(T *buffer, const T &val) {
		new(buffer) T(val);
	}

	inline void destroy(T *buffer) {
		buffer->~T();
	}

	// Vector &operator=(const Vector &inVector) {};
};
}

#endif /* Spine_Vector_h */
