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

#ifndef Spine_Extension_h
#define Spine_Extension_h

#include <stdlib.h>
#include <spine/dll.h>

#define SP_UNUSED(x) (void)(x)

namespace spine {
class String;

class SP_API SpineExtension {
public:
	template<typename T>
	static T *alloc(size_t num, const char *file, int line) {
		return (T *) getInstance()->_alloc(sizeof(T) * num, file, line);
	}

	template<typename T>
	static T *calloc(size_t num, const char *file, int line) {
		return (T *) getInstance()->_calloc(sizeof(T) * num, file, line);
	}

	template<typename T>
	static T *realloc(T *ptr, size_t num, const char *file, int line) {
		return (T *) getInstance()->_realloc(ptr, sizeof(T) * num, file, line);
	}

	template<typename T>
	static void free(T *ptr, const char *file, int line) {
		getInstance()->_free((void *) ptr, file, line);
	}

	static char *readFile(const String &path, int *length) {
		return getInstance()->_readFile(path, length);
	}

	static void setInstance(SpineExtension *inSpineExtension);

	static SpineExtension *getInstance();

	virtual ~SpineExtension();

	/// Implement this function to use your own memory allocator
	virtual void *_alloc(size_t size, const char *file, int line) = 0;

	virtual void *_calloc(size_t size, const char *file, int line) = 0;

	virtual void *_realloc(void *ptr, size_t size, const char *file, int line) = 0;

	/// If you provide a spineAllocFunc, you should also provide a spineFreeFunc
	virtual void _free(void *mem, const char *file, int line) = 0;

	virtual char *_readFile(const String &path, int *length) = 0;

protected:
	SpineExtension();

private:
	static SpineExtension *_instance;
};

class SP_API DefaultSpineExtension : public SpineExtension {
public:
	DefaultSpineExtension();

	virtual ~DefaultSpineExtension();

protected:
	virtual void *_alloc(size_t size, const char *file, int line);

	virtual void *_calloc(size_t size, const char *file, int line);

	virtual void *_realloc(void *ptr, size_t size, const char *file, int line);

	virtual void _free(void *mem, const char *file, int line);

	virtual char *_readFile(const String &path, int *length);
};

// This function is to be implemented by engine specific runtimes to provide
// the default extension for that engine. It is called the first time
// SpineExtension::getInstance() is called, when no instance has been set
// yet.
extern SpineExtension *getDefaultExtension();
}

#endif /* Spine_Extension_h */
