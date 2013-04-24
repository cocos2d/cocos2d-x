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

/*
 Implementation notes:

 - An OOP style is used where each "class" is made up of a struct and a number of functions prefixed with the struct name.

 - struct fields that are const are readonly. Either they are set in a create function and can never be changed, or they can only
 be changed by calling a function.

 - Inheritance is done using a struct field named "super" as the first field, allowing the struct to be cast to its "super class".
 This works because a pointer to a struct is guaranteed to be a pointer to the first struct field.

 - Classes intended for inheritance provide init/deinit functions which subclasses must call in their create/dispose functions.

 - Polymorphism is done by a base class providing function pointers in its init function. The public API delegates to this
 function.

 - Subclasses do not provide a dispose function, instead the base class' dispose function should be used, which will delegate to
 a dispose function.

 - Classes not designed for inheritance cannot be extended. They may use an internal subclass to hide private data and don't
 expose function pointers.

 - The public API hides implementation details such init/deinit functions. An internal API is exposed in extension.h to allow
 classes to be extended. Internal functions begin with underscore (_).

 - OOP in C tends to lose type safety. Macros are provided in extension.h to give context for why a cast is being done.
 */

#ifndef SPINE_EXTENSION_H_
#define SPINE_EXTENSION_H_

/* All allocation uses these. */
#define MALLOC(TYPE,COUNT) ((TYPE*)_malloc(sizeof(TYPE) * COUNT))
#define CALLOC(TYPE,COUNT) ((TYPE*)_calloc(1, sizeof(TYPE) * COUNT))
#define NEW(TYPE) CALLOC(TYPE,1)

/* Gets the direct super class. Type safe. */
#define SUPER(VALUE) (&VALUE->super)

/* Cast to a super class. Not type safe, use with care. Prefer SUPER() where possible. */
#define SUPER_CAST(TYPE,VALUE) ((TYPE*)VALUE)

/* Cast to a sub class. Not type safe, use with care. */
#define SUB_CAST(TYPE,VALUE) ((TYPE*)VALUE)

/* Casts away const. Can be used as an lvalue. Not type safe, use with care. */
#define CONST_CAST(TYPE,VALUE) (*(TYPE*)&VALUE)

/* Gets the vtable for the specified type. Not type safe, use with care. */
#define VTABLE(TYPE,VALUE) ((_##TYPE##Vtable*)((TYPE*)VALUE)->vtable)

/* Frees memory. Can be used on const types. */
#define FREE(VALUE) _free((void*)VALUE)

/* Allocates a new char[], assigns it to TO, and copies FROM to it. Can be used on const types. */
#define MALLOC_STR(TO,FROM) strcpy(CONST_CAST(char*, TO) = (char*)malloc(strlen(FROM) + 1), FROM)

#include <stdlib.h>
#include <string.h>
#include <spine/Skeleton.h>
#include <spine/RegionAttachment.h>
#include <spine/Animation.h>
#include <spine/Atlas.h>
#include <spine/AttachmentLoader.h>

namespace cocos2d { namespace extension {

/*
 * Functions that must be implemented:
 */

void _AtlasPage_createTexture (AtlasPage* self, const char* path);
void _AtlasPage_disposeTexture (AtlasPage* self);
char* _Util_readFile (const char* path, int* length);

/*
 * Internal API available for extension:
 */

void* _malloc (size_t size);
void* _calloc (size_t num, size_t size);
void _free (void* ptr);

void _setMalloc (void* (*_malloc) (size_t size));
void _setFree (void (*_free) (void* ptr));

char* _readFile (const char* path, int* length);

/**/

void _AttachmentLoader_init (AttachmentLoader* self, //
		void (*dispose) (AttachmentLoader* self), //
		Attachment* (*newAttachment) (AttachmentLoader* self, Skin* skin, AttachmentType type, const char* name));
void _AttachmentLoader_deinit (AttachmentLoader* self);
void _AttachmentLoader_setError (AttachmentLoader* self, const char* error1, const char* error2);
void _AttachmentLoader_setUnknownTypeError (AttachmentLoader* self, AttachmentType type);

/**/

void _Attachment_init (Attachment* self, const char* name, AttachmentType type, //
		void (*dispose) (Attachment* self));
void _Attachment_deinit (Attachment* self);

/**/

void _Timeline_init (Timeline* self, //
		void (*dispose) (Timeline* self), //
		void (*apply) (const Timeline* self, Skeleton* skeleton, float time, float alpha));
void _Timeline_deinit (Timeline* self);

/**/

void _CurveTimeline_init (CurveTimeline* self, int frameCount, //
		void (*dispose) (Timeline* self), //
		void (*apply) (const Timeline* self, Skeleton* skeleton, float time, float alpha));
void _CurveTimeline_deinit (CurveTimeline* self);

}} // namespace cocos2d { namespace extension {

#endif /* SPINE_EXTENSION_H_ */
