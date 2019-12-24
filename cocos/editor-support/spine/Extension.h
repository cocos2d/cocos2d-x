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
