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

#ifndef SPINE_ATLAS_H_
#define SPINE_ATLAS_H_

namespace cocos2d { namespace extension {

typedef enum {
	ATLAS_ALPHA, ATLAS_INTENSITY, ATLAS_LUMINANCE_ALPHA, ATLAS_RGB565, ATLAS_RGBA4444, ATLAS_RGB888, ATLAS_RGBA8888
} AtlasFormat;

typedef enum {
	ATLAS_NEAREST,
	ATLAS_LINEAR,
	ATLAS_MIPMAP,
	ATLAS_MIPMAP_NEAREST_NEAREST,
	ATLAS_MIPMAP_LINEAR_NEAREST,
	ATLAS_MIPMAP_NEAREST_LINEAR,
	ATLAS_MIPMAP_LINEAR_LINEAR
} AtlasFilter;

typedef enum {
	ATLAS_MIRROREDREPEAT, ATLAS_CLAMPTOEDGE, ATLAS_REPEAT
} AtlasWrap;

typedef struct AtlasPage AtlasPage;
struct AtlasPage {
	const char* name;
	AtlasFormat format;
	AtlasFilter minFilter, magFilter;
	AtlasWrap uWrap, vWrap;

	void* texture;
	int width, height;

	AtlasPage* next;
};

AtlasPage* AtlasPage_create (const char* name);
void AtlasPage_dispose (AtlasPage* self);

/**/

typedef struct AtlasRegion AtlasRegion;
struct AtlasRegion {
	const char* name;
	int x, y, width, height;
	float u, v, u2, v2;
	float offsetX, offsetY;
	int originalWidth, originalHeight;
	int index;
	int/*bool*/rotate;
	int/*bool*/flip;
	int* splits;
	int* pads;

	AtlasPage* page;

	AtlasRegion* next;
};

AtlasRegion* AtlasRegion_create ();
void AtlasRegion_dispose (AtlasRegion* self);

/**/

typedef struct {
	AtlasPage* pages;
	AtlasRegion* regions;
} Atlas;

/* Image files referenced in the atlas file will be prefixed with dir. */
Atlas* Atlas_readAtlas (const char* data, int length, const char* dir);
/* Image files referenced in the atlas file will be prefixed with the directory containing the atlas file. */
Atlas* Atlas_readAtlasFile (const char* path);
void Atlas_dispose (Atlas* atlas);

/* Returns 0 if the region was not found. */
AtlasRegion* Atlas_findRegion (const Atlas* self, const char* name);

}} // namespace cocos2d { namespace extension {

#endif /* SPINE_ATLAS_H_ */
