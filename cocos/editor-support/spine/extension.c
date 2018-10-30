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

#include <spine/extension.h>
#include <stdio.h>

float _spInternalRandom () {
	return rand() / (float)RAND_MAX;
}

static void* (*mallocFunc) (size_t size) = malloc;
static void* (*reallocFunc) (void* ptr, size_t size) = realloc;
static void* (*debugMallocFunc) (size_t size, const char* file, int line) = NULL;
static void (*freeFunc) (void* ptr) = free;
static float (*randomFunc) () = _spInternalRandom;

void* _spMalloc (size_t size, const char* file, int line) {
	if(debugMallocFunc)
		return debugMallocFunc(size, file, line);

	return mallocFunc(size);
}
void* _spCalloc (size_t num, size_t size, const char* file, int line) {
	void* ptr = _spMalloc(num * size, file, line);
	if (ptr) memset(ptr, 0, num * size);
	return ptr;
}
void* _spRealloc(void* ptr, size_t size) {
	return reallocFunc(ptr, size);
}
void _spFree (void* ptr) {
	freeFunc(ptr);
}

float _spRandom () {
	return randomFunc();
}

void _spSetDebugMalloc(void* (*malloc) (size_t size, const char* file, int line)) {
	debugMallocFunc = malloc;
}

void _spSetMalloc (void* (*malloc) (size_t size)) {
	mallocFunc = malloc;
}

void _spSetRealloc (void* (*realloc) (void* ptr, size_t size)) {
	reallocFunc = realloc;
}

void _spSetFree (void (*free) (void* ptr)) {
	freeFunc = free;
}

void _spSetRandom (float (*random) ()) {
	randomFunc = random;
}

char* _spReadFile (const char* path, int* length) {
	char *data;
	FILE *file = fopen(path, "rb");
	if (!file) return 0;

	fseek(file, 0, SEEK_END);
	*length = (int)ftell(file);
	fseek(file, 0, SEEK_SET);

	data = MALLOC(char, *length);
	fread(data, 1, *length, file);
	fclose(file);

	return data;
}

float _spMath_random(float min, float max) {
	return min + (max - min) * _spRandom();
}

float _spMath_randomTriangular(float min, float max) {
	return _spMath_randomTriangularWith(min, max, (min + max) * 0.5f);
}

float _spMath_randomTriangularWith(float min, float max, float mode) {
	float u = _spRandom();
	float d = max - min;
	if (u <= (mode - min) / d) return min + SQRT(u * d * (mode - min));
	return max - SQRT((1 - u) * d * (max - mode));
}

float _spMath_interpolate(float (*apply) (float a), float start, float end, float a) {
	return start + (end - start) * apply(a);
}

float _spMath_pow2_apply(float a) {
	if (a <= 0.5) return POW(a * 2, 2) / 2;
	return POW((a - 1) * 2, 2) / -2 + 1;
}

float _spMath_pow2out_apply(float a) {
	return POW(a - 1, 2) * -1 + 1;
}
