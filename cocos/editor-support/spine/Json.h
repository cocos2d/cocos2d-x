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

#ifndef Spine_Json_h
#define Spine_Json_h

#include <spine/SpineObject.h>

#ifndef SPINE_JSON_HAVE_PREV
/* spine doesn't use the "prev" link in the Json sibling lists. */
#define SPINE_JSON_HAVE_PREV 0
#endif

namespace spine {
class SP_API Json : public SpineObject {
	friend class SkeletonJson;

public:
	/* Json Types: */
	static const int JSON_FALSE;
	static const int JSON_TRUE;
	static const int JSON_NULL;
	static const int JSON_NUMBER;
	static const int JSON_STRING;
	static const int JSON_ARRAY;
	static const int JSON_OBJECT;

	/* Get item "string" from object. Case insensitive. */
	static Json *getItem(Json *object, const char *string);

	static const char *getString(Json *object, const char *name, const char *defaultValue);

	static float getFloat(Json *object, const char *name, float defaultValue);

	static int getInt(Json *object, const char *name, int defaultValue);

	static bool getBoolean(Json *object, const char *name, bool defaultValue);

	/* For analysing failed parses. This returns a pointer to the parse error. You'll probably need to look a few chars back to make sense of it. Defined when Json_create() returns 0. 0 when Json_create() succeeds. */
	static const char *getError();

	/* Supply a block of JSON, and this returns a Json object you can interrogate. Call Json_dispose when finished. */
	explicit Json(const char *value);

	~Json();



private:
	static const char *_error;

	Json *_next;
#if SPINE_JSON_HAVE_PREV
	Json* _prev; /* next/prev allow you to walk array/object chains. Alternatively, use getSize/getItem */
#endif
	Json *_child; /* An array or object item will have a child pointer pointing to a chain of the items in the array/object. */

	int _type; /* The type of the item, as above. */
	int _size; /* The number of children. */

	const char *_valueString; /* The item's string, if type==JSON_STRING */
	int _valueInt; /* The item's number, if type==JSON_NUMBER */
	float _valueFloat; /* The item's number, if type==JSON_NUMBER */

	const char *_name; /* The item's name string, if this item is the child of, or is in the list of subitems of an object. */

	/* Utility to jump whitespace and cr/lf */
	static const char *skip(const char *inValue);

	/* Parser core - when encountering text, process appropriately. */
	static const char *parseValue(Json *item, const char *value);

	/* Parse the input text into an unescaped cstring, and populate item. */
	static const char *parseString(Json *item, const char *str);

	/* Parse the input text to generate a number, and populate the result into item. */
	static const char *parseNumber(Json *item, const char *num);

	/* Build an array from input text. */
	static const char *parseArray(Json *item, const char *value);

	/* Build an object from the text. */
	static const char *parseObject(Json *item, const char *value);

	static int json_strcasecmp(const char *s1, const char *s2);
};
}

#endif /* Spine_Json_h */
