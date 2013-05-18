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

#include <spine/extension.h>
#include <stdio.h>

namespace cocos2d { namespace extension {

static void* (*mallocFunc) (size_t size) = malloc;
static void (*freeFunc) (void* ptr) = free;

void* _malloc (size_t size) {
	return mallocFunc(size);
}
void* _calloc (size_t num, size_t size) {
	void* ptr = mallocFunc(size);
	if (ptr) memset(ptr, 0, size);
	return ptr;
}
void _free (void* ptr) {
	freeFunc(ptr);
}

void _setMalloc (void* (*malloc) (size_t size)) {
	mallocFunc = malloc;
}
void _setFree (void (*free) (void* ptr)) {
	freeFunc = free;
}

char* _readFile (const char* path, int* length) {
	FILE *file = fopen(path, "rb");
	if (!file) return 0;

	fseek(file, 0, SEEK_END);
	*length = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* data = MALLOC(char, *length);
	int rtn = fread(data, 1, *length, file);
	fclose(file);
	if (rtn != *length) return 0;

	return data;
}

}} // namespace cocos2d { namespace extension {
