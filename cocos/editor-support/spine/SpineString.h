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

#ifndef SPINE_STRING_H
#define SPINE_STRING_H

#include <spine/SpineObject.h>
#include <spine/Extension.h>

#include <string.h>
#include <stdio.h>

// Required for sprintf on MSVC
#ifdef _MSC_VER
#pragma warning(disable:4996)
#endif

namespace spine {
class SP_API String : public SpineObject {
public:
	String() : _length(0), _buffer(NULL) {
	}

	String(const char *chars, bool own = false) {
		if (!chars) {
			_length = 0;
			_buffer = NULL;
		} else {
			_length = strlen(chars);
			if (!own) {
				_buffer = SpineExtension::calloc<char>(_length + 1, __FILE__, __LINE__);
				memcpy((void *) _buffer, chars, _length + 1);
			} else {
				_buffer = (char *) chars;
			}
		}
	}

	String(const String &other) {
		if (!other._buffer) {
			_length = 0;
			_buffer = NULL;
		} else {
			_length = other._length;
			_buffer = SpineExtension::calloc<char>(other._length + 1, __FILE__, __LINE__);
			memcpy((void *) _buffer, other._buffer, other._length + 1);
		}
	}

	size_t length() const {
		return _length;
	}

	bool isEmpty() const {
		return _length == 0;
	}

	const char *buffer() const {
		return _buffer;
	}

	void own(const String &other) {
		if (this == &other) return;
		if (_buffer) {
			SpineExtension::free(_buffer, __FILE__, __LINE__);
		}
		_length = other._length;
		_buffer = other._buffer;
		other._length = 0;
		other._buffer = NULL;
	}

	void own(const char *chars) {
		if (_buffer == chars) return;
		if (_buffer) {
			SpineExtension::free(_buffer, __FILE__, __LINE__);
		}

		if (!chars) {
			_length = 0;
			_buffer = NULL;
		} else {
			_length = strlen(chars);
			_buffer = (char *) chars;
		}
	}

	void unown() {
		_length = 0;
		_buffer = NULL;
	}

	String &operator=(const String &other) {
		if (this == &other) return *this;
		if (_buffer) {
			SpineExtension::free(_buffer, __FILE__, __LINE__);
		}
		if (!other._buffer) {
			_length = 0;
			_buffer = NULL;
		} else {
			_length = other._length;
			_buffer = SpineExtension::calloc<char>(other._length + 1, __FILE__, __LINE__);
			memcpy((void *) _buffer, other._buffer, other._length + 1);
		}
		return *this;
	}

	String &operator=(const char *chars) {
		if (_buffer == chars) return *this;
		if (_buffer) {
			SpineExtension::free(_buffer, __FILE__, __LINE__);
		}
		if (!chars) {
			_length = 0;
			_buffer = NULL;
		} else {
			_length = strlen(chars);
			_buffer = SpineExtension::calloc<char>(_length + 1, __FILE__, __LINE__);
			memcpy((void *) _buffer, chars, _length + 1);
		}
		return *this;
	}

	String &append(const char *chars) {
		size_t len = strlen(chars);
		size_t thisLen = _length;
		_length = _length + len;
		bool same = chars == _buffer;
		_buffer = SpineExtension::realloc(_buffer, _length + 1, __FILE__, __LINE__);
		memcpy((void *) (_buffer + thisLen), (void *) (same ? _buffer : chars), len + 1);
		return *this;
	}

	String &append(const String &other) {
		size_t len = other.length();
		size_t thisLen = _length;
		_length = _length + len;
		bool same = other._buffer == _buffer;
		_buffer = SpineExtension::realloc(_buffer, _length + 1, __FILE__, __LINE__);
		memcpy((void *) (_buffer + thisLen), (void *) (same ? _buffer : other._buffer), len + 1);
		return *this;
	}

	String &append(int other) {
		char str[100];
		sprintf(str, "%i", other);
		append(str);
		return *this;
	}

	String &append(float other) {
		char str[100];
		sprintf(str, "%f", other);
		append(str);
		return *this;
	}

	friend bool operator==(const String &a, const String &b) {
		if (a._buffer == b._buffer) return true;
		if (a._length != b._length) return false;
		if (a._buffer && b._buffer) {
			return strcmp(a._buffer, b._buffer) == 0;
		} else {
			return false;
		}
	}

	friend bool operator!=(const String &a, const String &b) {
		return !(a == b);
	}

	~String() {
		if (_buffer) {
			SpineExtension::free(_buffer, __FILE__, __LINE__);
		}
	}

private:
	mutable size_t _length;
	mutable char *_buffer;
};
}


#endif //SPINE_STRING_H
