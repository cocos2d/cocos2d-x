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

#include <spine/Atlas.h>
#include <spine/TextureLoader.h>
#include <spine/ContainerUtil.h>

#include <ctype.h>

using namespace spine;

Atlas::Atlas(const String &path, TextureLoader *textureLoader, bool createTexture) : _textureLoader(textureLoader) {
	int dirLength;
	char *dir;
	int length;
	const char *data;

	/* Get directory from atlas path. */
	const char *lastForwardSlash = strrchr(path.buffer(), '/');
	const char *lastBackwardSlash = strrchr(path.buffer(), '\\');
	const char *lastSlash = lastForwardSlash > lastBackwardSlash ? lastForwardSlash : lastBackwardSlash;
	if (lastSlash == path) lastSlash++; /* Never drop starting slash. */
	dirLength = (int) (lastSlash ? lastSlash - path.buffer() : 0);
	dir = SpineExtension::calloc<char>(dirLength + 1, __FILE__, __LINE__);
	memcpy(dir, path.buffer(), dirLength);
	dir[dirLength] = '\0';

	data = SpineExtension::readFile(path, &length);
	if (data) {
		load(data, length, dir, createTexture);
	}

	SpineExtension::free(data, __FILE__, __LINE__);
	SpineExtension::free(dir, __FILE__, __LINE__);
}

Atlas::Atlas(const char *data, int length, const char *dir, TextureLoader *textureLoader, bool createTexture) : _textureLoader(
		textureLoader) {
	load(data, length, dir, createTexture);
}

Atlas::~Atlas() {
	if (_textureLoader) {
		for (size_t i = 0, n = _pages.size(); i < n; ++i) {
			_textureLoader->unload(_pages[i]->getRendererObject());
		}
	}
	ContainerUtil::cleanUpVectorOfPointers(_pages);
	ContainerUtil::cleanUpVectorOfPointers(_regions);
}

void Atlas::flipV() {
	for (size_t i = 0, n = _regions.size(); i < n; ++i) {
		AtlasRegion *regionP = _regions[i];
		AtlasRegion &region = *regionP;
		region.v = 1 - region.v;
		region.v2 = 1 - region.v2;
	}
}

AtlasRegion *Atlas::findRegion(const String &name) {
	for (size_t i = 0, n = _regions.size(); i < n; ++i)
		if (_regions[i]->name == name) return _regions[i];
	return NULL;
}

Vector<AtlasPage*> &Atlas::getPages() {
	return _pages;
}

void Atlas::load(const char *begin, int length, const char *dir, bool createTexture) {
	static const char *formatNames[] = {"", "Alpha", "Intensity", "LuminanceAlpha", "RGB565", "RGBA4444", "RGB888", "RGBA8888"};
	static const char *textureFilterNames[] = {"", "Nearest", "Linear", "MipMap", "MipMapNearestNearest", "MipMapLinearNearest",
		"MipMapNearestLinear", "MipMapLinearLinear"};

	int count;
	const char *end = begin + length;
	int dirLength = (int) strlen(dir);
	int needsSlash = dirLength > 0 && dir[dirLength - 1] != '/' && dir[dirLength - 1] != '\\';

	AtlasPage *page = NULL;
	Str str;
	Str tuple[4];

	while (readLine(&begin, end, &str)) {
		if (str.end - str.begin == 0) {
			page = 0;
		} else if (!page) {
			char *name = mallocString(&str);
			char *path = SpineExtension::calloc<char>(dirLength + needsSlash + strlen(name) + 1, __FILE__, __LINE__);
			memcpy(path, dir, dirLength);
			if (needsSlash) path[dirLength] = '/';
			strcpy(path + dirLength + needsSlash, name);

			page = new(__FILE__, __LINE__) AtlasPage(String(name, true));

			int tupleVal = readTuple(&begin, end, tuple);
			assert(tupleVal == 2);

			/* size is only optional for an atlas packed with an old TexturePacker. */
			page->width = toInt(tuple);
			page->height = toInt(tuple + 1);
			readTuple(&begin, end, tuple);

			page->format = (Format) indexOf(formatNames, 8, tuple);

			readTuple(&begin, end, tuple);
			page->minFilter = (TextureFilter) indexOf(textureFilterNames, 8, tuple);
			page->magFilter = (TextureFilter) indexOf(textureFilterNames, 8, tuple + 1);

			readValue(&begin, end, &str);

			page->uWrap = TextureWrap_ClampToEdge;
			page->vWrap = TextureWrap_ClampToEdge;
			if (!equals(&str, "none")) {
				if (str.end - str.begin == 1) {
					if (*str.begin == 'x') {
						page->uWrap = TextureWrap_Repeat;
					} else if (*str.begin == 'y') {
						page->vWrap = TextureWrap_Repeat;
					}
				} else if (equals(&str, "xy")) {
					page->uWrap = TextureWrap_Repeat;
					page->vWrap = TextureWrap_Repeat;
				}
			}

			if (createTexture) {
				if (_textureLoader) _textureLoader->load(*page, String(path));
				SpineExtension::free(path, __FILE__, __LINE__);
			} else
				page->texturePath = String(path, true);

			_pages.add(page);
		} else {
			AtlasRegion *region = new(__FILE__, __LINE__) AtlasRegion();

			region->page = page;
			region->name = String(mallocString(&str), true);

			readValue(&begin, end, &str);
			if (equals(&str, "true")) region->degrees = 90;
			else if (equals(&str, "false")) region->degrees = 0;
			else region->degrees = toInt(&str);
			region->rotate = region->degrees == 90;

			readTuple(&begin, end, tuple);
			region->x = toInt(tuple);
			region->y = toInt(tuple + 1);

			readTuple(&begin, end, tuple);
			region->width = toInt(tuple);
			region->height = toInt(tuple + 1);

			region->u = region->x / (float) page->width;
			region->v = region->y / (float) page->height;
			if (region->rotate) {
				region->u2 = (region->x + region->height) / (float) page->width;
				region->v2 = (region->y + region->width) / (float) page->height;
			} else {
				region->u2 = (region->x + region->width) / (float) page->width;
				region->v2 = (region->y + region->height) / (float) page->height;
			}

			count = readTuple(&begin, end, tuple);
			assert(count);

			if (count == 4) {
				/* split is optional */
				region->splits.setSize(4, 0);
				region->splits[0] = toInt(tuple);
				region->splits[1] = toInt(tuple + 1);
				region->splits[2] = toInt(tuple + 2);
				region->splits[3] = toInt(tuple + 3);

				count = readTuple(&begin, end, tuple);
				assert(count);

				if (count == 4) {
					/* pad is optional, but only present with splits */
					region->pads.setSize(4, 0);
					region->pads[0] = toInt(tuple);
					region->pads[1] = toInt(tuple + 1);
					region->pads[2] = toInt(tuple + 2);
					region->pads[3] = toInt(tuple + 3);

					readTuple(&begin, end, tuple);
				}
			}

			region->originalWidth = toInt(tuple);
			region->originalHeight = toInt(tuple + 1);

			readTuple(&begin, end, tuple);
			region->offsetX = (float)toInt(tuple);
			region->offsetY = (float)toInt(tuple + 1);

			readValue(&begin, end, &str);

			region->index = toInt(&str);

			_regions.add(region);
		}
	}
}

void Atlas::trim(Str *str) {
	while (isspace((unsigned char) *str->begin) && str->begin < str->end)
		(str->begin)++;

	if (str->begin == str->end) return;

	str->end--;

	while (((unsigned char)*str->end == '\r') && str->end >= str->begin)
		str->end--;

	str->end++;
}

int Atlas::readLine(const char **begin, const char *end, Str *str) {
	if (*begin == end) return 0;

	str->begin = *begin;

	/* Find next delimiter. */
	while (*begin != end && **begin != '\n')
		(*begin)++;

	str->end = *begin;
	trim(str);

	if (*begin != end) (*begin)++;

	return 1;
}

int Atlas::beginPast(Str *str, char c) {
	const char *begin = str->begin;
	while (true) {
		char lastSkippedChar = *begin;
		if (begin == str->end) return 0;
		begin++;
		if (lastSkippedChar == c) break;
	}
	str->begin = begin;
	return 1;
}

int Atlas::readValue(const char **begin, const char *end, Str *str) {
	readLine(begin, end, str);
	if (!beginPast(str, ':')) return 0;
	trim(str);
	return 1;
}

int Atlas::readTuple(const char **begin, const char *end, Str tuple[]) {
	int i;
	Str str = {NULL, NULL};
	readLine(begin, end, &str);
	if (!beginPast(&str, ':')) return 0;

	for (i = 0; i < 3; ++i) {
		tuple[i].begin = str.begin;
		if (!beginPast(&str, ',')) break;
		tuple[i].end = str.begin - 2;
		trim(&tuple[i]);
	}

	tuple[i].begin = str.begin;
	tuple[i].end = str.end;
	trim(&tuple[i]);

	return i + 1;
}

char *Atlas::mallocString(Str *str) {
	int length = (int) (str->end - str->begin);
	char *string = SpineExtension::calloc<char>(length + 1, __FILE__, __LINE__);
	memcpy(string, str->begin, length);
	string[length] = '\0';
	return string;
}

int Atlas::indexOf(const char **array, int count, Str *str) {
	int length = (int) (str->end - str->begin);
	int i;
	for (i = count - 1; i >= 0; i--)
		if (strncmp(array[i], str->begin, length) == 0) return i;
	return 0;
}

int Atlas::equals(Str *str, const char *other) {
	return strncmp(other, str->begin, str->end - str->begin) == 0;
}

int Atlas::toInt(Str *str) {
	return (int) strtol(str->begin, (char **) &str->end, 10);
}
