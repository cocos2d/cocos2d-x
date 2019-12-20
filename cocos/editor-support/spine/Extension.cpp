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
#ifdef SPINE_UE4
#include "SpinePluginPrivatePCH.h"
#endif

#include <spine/Extension.h>
#include <spine/SpineString.h>

#include <assert.h>

using namespace spine;

SpineExtension *SpineExtension::_instance = NULL;

void SpineExtension::setInstance(SpineExtension *inValue) {
	assert(inValue);

	_instance = inValue;
}

SpineExtension *SpineExtension::getInstance() {
	if (!_instance) _instance = spine::getDefaultExtension();
	assert(_instance);

	return _instance;
}

SpineExtension::~SpineExtension() {
}

SpineExtension::SpineExtension() {
}

DefaultSpineExtension::~DefaultSpineExtension() {
}

void *DefaultSpineExtension::_alloc(size_t size, const char *file, int line) {
	SP_UNUSED(file);
	SP_UNUSED(line);

	if (size == 0)
		return 0;
	void *ptr = ::malloc(size);
	return ptr;
}

void *DefaultSpineExtension::_calloc(size_t size, const char *file, int line) {
	SP_UNUSED(file);
	SP_UNUSED(line);

	if (size == 0)
		return 0;

	void *ptr = ::malloc(size);
	if (ptr) {
		memset(ptr, 0, size);
	}
	return ptr;
}

void *DefaultSpineExtension::_realloc(void *ptr, size_t size, const char *file, int line) {
	SP_UNUSED(file);
	SP_UNUSED(line);

	void *mem = NULL;
	if (size == 0)
		return 0;
	if (ptr == NULL)
		mem = ::malloc(size);
	else
		mem = ::realloc(ptr, size);
	return mem;
}

void DefaultSpineExtension::_free(void *mem, const char *file, int line) {
	SP_UNUSED(file);
	SP_UNUSED(line);

	::free(mem);
}

char *DefaultSpineExtension::_readFile(const String &path, int *length) {
	char *data;
	FILE *file = fopen(path.buffer(), "rb");
	if (!file) return 0;

	fseek(file, 0, SEEK_END);
	*length = (int) ftell(file);
	fseek(file, 0, SEEK_SET);

	data = SpineExtension::alloc<char>(*length, __FILE__, __LINE__);
	fread(data, 1, *length, file);
	fclose(file);

	return data;
}

DefaultSpineExtension::DefaultSpineExtension() : SpineExtension() {
}
