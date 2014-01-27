/******************************************************************************
 * Spine Runtime Software License - Version 1.1
 * 
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms in whole or in part, with
 * or without modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. A Spine Essential, Professional, Enterprise, or Education License must
 *    be purchased from Esoteric Software and the license must remain valid:
 *    http://esotericsoftware.com/
 * 2. Redistributions of source code must retain this license, which is the
 *    above copyright notice, this declaration of conditions and the following
 *    disclaimer.
 * 3. Redistributions in binary form must reproduce this license, which is the
 *    above copyright notice, this declaration of conditions and the following
 *    disclaimer, in the documentation and/or other materials provided with the
 *    distribution.
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
 *****************************************************************************/

#ifndef SPINE_ATLAS_H_
#define SPINE_ATLAS_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	ATLAS_ALPHA, ATLAS_INTENSITY, ATLAS_LUMINANCE_ALPHA, ATLAS_RGB565, ATLAS_RGBA4444, ATLAS_RGB888, ATLAS_RGBA8888
} spAtlasFormat;

typedef enum {
	ATLAS_NEAREST,
	ATLAS_LINEAR,
	ATLAS_MIPMAP,
	ATLAS_MIPMAP_NEAREST_NEAREST,
	ATLAS_MIPMAP_LINEAR_NEAREST,
	ATLAS_MIPMAP_NEAREST_LINEAR,
	ATLAS_MIPMAP_LINEAR_LINEAR
} spAtlasFilter;

typedef enum {
	ATLAS_MIRROREDREPEAT, ATLAS_CLAMPTOEDGE, ATLAS_REPEAT
} spAtlasWrap;

typedef struct spAtlasPage spAtlasPage;
struct spAtlasPage {
	const char* name;
	spAtlasFormat format;
	spAtlasFilter minFilter, magFilter;
	spAtlasWrap uWrap, vWrap;

	void* rendererObject;
	int width, height;

	spAtlasPage* next;
};

spAtlasPage* spAtlasPage_create (const char* name);
void spAtlasPage_dispose (spAtlasPage* self);

#ifdef SPINE_SHORT_NAMES
typedef spAtlasFormat AtlasFormat;
typedef spAtlasFilter AtlasFilter;
typedef spAtlasWrap AtlasWrap;
typedef spAtlasPage AtlasPage;
#define AtlasPage_create(...) spAtlasPage_create(__VA_ARGS__)
#define AtlasPage_dispose(...) spAtlasPage_dispose(__VA_ARGS__)
#endif

/**/

typedef struct spAtlasRegion spAtlasRegion;
struct spAtlasRegion {
	const char* name;
	int x, y, width, height;
	float u, v, u2, v2;
	int offsetX, offsetY;
	int originalWidth, originalHeight;
	int index;
	int/*bool*/rotate;
	int/*bool*/flip;
	int* splits;
	int* pads;

	spAtlasPage* page;

	spAtlasRegion* next;
};

spAtlasRegion* spAtlasRegion_create ();
void spAtlasRegion_dispose (spAtlasRegion* self);

#ifdef SPINE_SHORT_NAMES
typedef spAtlasRegion AtlasRegion;
#define AtlasRegion_create(...) spAtlasRegion_create(__VA_ARGS__)
#define AtlasRegion_dispose(...) spAtlasRegion_dispose(__VA_ARGS__)
#endif

/**/

typedef struct {
	spAtlasPage* pages;
	spAtlasRegion* regions;
} spAtlas;

/* Image files referenced in the atlas file will be prefixed with dir. */
spAtlas* spAtlas_readAtlas (const char* data, int length, const char* dir);
/* Image files referenced in the atlas file will be prefixed with the directory containing the atlas file. */
spAtlas* spAtlas_readAtlasFile (const char* path);
void spAtlas_dispose (spAtlas* atlas);

/* Returns 0 if the region was not found. */
spAtlasRegion* spAtlas_findRegion (const spAtlas* self, const char* name);

#ifdef SPINE_SHORT_NAMES
typedef spAtlas Atlas;
#define Atlas_readAtlas(...) spAtlas_readAtlas(__VA_ARGS__)
#define Atlas_readAtlasFile(...) spAtlas_readAtlasFile(__VA_ARGS__)
#define Atlas_dispose(...) spAtlas_dispose(__VA_ARGS__)
#define Atlas_findRegion(...) spAtlas_findRegion(__VA_ARGS__)
#endif

#ifdef __cplusplus
}
#endif

#endif /* SPINE_ATLAS_H_ */
