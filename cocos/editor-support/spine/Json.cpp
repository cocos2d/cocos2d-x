/*
 Copyright (c) 2009 Dave Gamble

 Permission is hereby granted, dispose of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

/* Json */
/* JSON parser in C. */

#include "Json.h"
#include <stdio.h>
#include <ctype.h>
#include <spine/extension.h>

static const char* ep;

const char* Json_getError (void) {
	return ep;
}

static int Json_strcasecmp (const char* s1, const char* s2) {
	if (!s1) return (s1 == s2) ? 0 : 1;
	if (!s2) return 1;
	for (; tolower(*s1) == tolower(*s2); ++s1, ++s2)
		if (*s1 == 0) return 0;
	return tolower(*(const unsigned char*)s1) - tolower(*(const unsigned char*)s2);
}

/* Internal constructor. */
static Json *Json_new (void) {
	return (Json*)CALLOC(Json, 1);
}

/* Delete a Json structure. */
void Json_dispose (Json *c) {
	Json *next;
	while (c) {
		next = c->next;
		if (c->child) Json_dispose(c->child);
		if (c->valueString) FREE(c->valueString);
		if (c->name) FREE(c->name);
		FREE(c);
		c = next;
	}
}

/* Parse the input text to generate a number, and populate the result into item. */
static const char* parse_number (Json *item, const char* num) {
	float n = 0, sign = 1, scale = 0;
	int subscale = 0, signsubscale = 1;

	/* Could use sscanf for this? */
	if (*num == '-') sign = -1, num++; /* Has sign? */
	if (*num == '0') num++; /* is zero */
	if (*num >= '1' && *num <= '9') do
		n = (n * 10.0f) + (*num++ - '0');
	while (*num >= '0' && *num <= '9'); /* Number? */
	if (*num == '.' && num[1] >= '0' && num[1] <= '9') {
		num++;
		do
			n = (n * 10.0f) + (*num++ - '0'), scale--;
		while (*num >= '0' && *num <= '9');
	} /* Fractional part? */
	if (*num == 'e' || *num == 'E') /* Exponent? */
	{
		num++;
		if (*num == '+')
			num++;
		else if (*num == '-') signsubscale = -1, num++; /* With sign? */
		while (*num >= '0' && *num <= '9')
			subscale = (subscale * 10) + (*num++ - '0'); /* Number? */
	}

	n = sign * n * (float)pow(10.0f, (scale + subscale * signsubscale)); /* number = +/- number.fraction * 10^+/- exponent */

	item->valueFloat = n;
	item->valueInt = (int)n;
	item->type = Json_Number;
	return num;
}

/* Parse the input text into an unescaped cstring, and populate item. */
static const unsigned char firstByteMark[7] = {0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC};
static const char* parse_string (Json *item, const char* str) {
	const char* ptr = str + 1;
	char* ptr2;
	char* out;
	int len = 0;
	unsigned uc, uc2;
	if (*str != '\"') {
		ep = str;
		return 0;
	} /* not a string! */

	while (*ptr != '\"' && *ptr && ++len)
		if (*ptr++ == '\\') ptr++; /* Skip escaped quotes. */

	out = (char*)malloc(len + 1); /* This is how long we need for the string, roughly. */
	if (!out) return 0;

	ptr = str + 1;
	ptr2 = out;
	while (*ptr != '\"' && *ptr) {
		if (*ptr != '\\')
			*ptr2++ = *ptr++;
		else {
			ptr++;
			switch (*ptr) {
			case 'b':
				*ptr2++ = '\b';
				break;
			case 'f':
				*ptr2++ = '\f';
				break;
			case 'n':
				*ptr2++ = '\n';
				break;
			case 'r':
				*ptr2++ = '\r';
				break;
			case 't':
				*ptr2++ = '\t';
				break;
			case 'u': /* transcode utf16 to utf8. */
				sscanf(ptr + 1, "%4x", &uc);
				ptr += 4; /* get the unicode char. */

				if ((uc >= 0xDC00 && uc <= 0xDFFF) || uc == 0) break; /* check for invalid.	*/

				if (uc >= 0xD800 && uc <= 0xDBFF) /* UTF16 surrogate pairs.	*/
				{
					if (ptr[1] != '\\' || ptr[2] != 'u') break; /* missing second-half of surrogate.	*/
					sscanf(ptr + 3, "%4x", &uc2);
					ptr += 6;
					if (uc2 < 0xDC00 || uc2 > 0xDFFF) break; /* invalid second-half of surrogate.	*/
					uc = 0x10000 + (((uc & 0x3FF) << 10) | (uc2 & 0x3FF));
				}

				len = 4;
				if (uc < 0x80)
					len = 1;
				else if (uc < 0x800)
					len = 2;
				else if (uc < 0x10000) len = 3;
				ptr2 += len;

				switch (len) {
				case 4:
					*--ptr2 = ((uc | 0x80) & 0xBF);
					uc >>= 6;
				case 3:
					*--ptr2 = ((uc | 0x80) & 0xBF);
					uc >>= 6;
				case 2:
					*--ptr2 = ((uc | 0x80) & 0xBF);
					uc >>= 6;
				case 1:
					*--ptr2 = (uc | firstByteMark[len]);
				}
				ptr2 += len;
				break;
			default:
				*ptr2++ = *ptr;
				break;
			}
			ptr++;
		}
	}
	*ptr2 = 0;
	if (*ptr == '\"') ptr++;
	item->valueString = out;
	item->type = Json_String;
	return ptr;
}

/* Predeclare these prototypes. */
static const char* parse_value (Json *item, const char* value);
static const char* parse_array (Json *item, const char* value);
static const char* parse_object (Json *item, const char* value);

/* Utility to jump whitespace and cr/lf */
static const char* skip (const char* in) {
	while (in && *in && (unsigned char)*in <= 32)
		in++;
	return in;
}

/* Parse an object - create a new root, and populate. */
Json *Json_create (const char* value) {
	const char* end = 0;
	Json *c = Json_new();
	ep = 0;
	if (!c) return 0; /* memory fail */

	end = parse_value(c, skip(value));
	if (!end) {
		Json_dispose(c);
		return 0;
	} /* parse failure. ep is set. */

	return c;
}

/* Parser core - when encountering text, process appropriately. */
static const char* parse_value (Json *item, const char* value) {
	if (!value) return 0; /* Fail on null. */
	if (!strncmp(value, "null", 4)) {
		item->type = Json_NULL;
		return value + 4;
	}
	if (!strncmp(value, "false", 5)) {
		item->type = Json_False;
		return value + 5;
	}
	if (!strncmp(value, "true", 4)) {
		item->type = Json_True;
		item->valueInt = 1;
		return value + 4;
	}
	if (*value == '\"') {
		return parse_string(item, value);
	}
	if (*value == '-' || (*value >= '0' && *value <= '9')) {
		return parse_number(item, value);
	}
	if (*value == '[') {
		return parse_array(item, value);
	}
	if (*value == '{') {
		return parse_object(item, value);
	}

	ep = value;
	return 0; /* failure. */
}

/* Build an array from input text. */
static const char* parse_array (Json *item, const char* value) {
	Json *child;
	if (*value != '[') {
		ep = value;
		return 0;
	} /* not an array! */

	item->type = Json_Array;
	value = skip(value + 1);
	if (*value == ']') return value + 1; /* empty array. */

	item->child = child = Json_new();
	if (!item->child) return 0; /* memory fail */
	value = skip(parse_value(child, skip(value))); /* skip any spacing, get the value. */
	if (!value) return 0;
	item->size = 1;

	while (*value == ',') {
		Json *new_item;
		if (!(new_item = Json_new())) return 0; /* memory fail */
		child->next = new_item;
		new_item->prev = child;
		child = new_item;
		value = skip(parse_value(child, skip(value + 1)));
		if (!value) return 0; /* memory fail */
		item->size++;
	}

	if (*value == ']') return value + 1; /* end of array */
	ep = value;
	return 0; /* malformed. */
}

/* Build an object from the text. */
static const char* parse_object (Json *item, const char* value) {
	Json *child;
	if (*value != '{') {
		ep = value;
		return 0;
	} /* not an object! */

	item->type = Json_Object;
	value = skip(value + 1);
	if (*value == '}') return value + 1; /* empty array. */

	item->child = child = Json_new();
	if (!item->child) return 0;
	value = skip(parse_string(child, skip(value)));
	if (!value) return 0;
	child->name = child->valueString;
	child->valueString = 0;
	if (*value != ':') {
		ep = value;
		return 0;
	} /* fail! */
	value = skip(parse_value(child, skip(value + 1))); /* skip any spacing, get the value. */
	if (!value) return 0;
	item->size = 1;

	while (*value == ',') {
		Json *new_item;
		if (!(new_item = Json_new())) return 0; /* memory fail */
		child->next = new_item;
		new_item->prev = child;
		child = new_item;
		value = skip(parse_string(child, skip(value + 1)));
		if (!value) return 0;
		child->name = child->valueString;
		child->valueString = 0;
		if (*value != ':') {
			ep = value;
			return 0;
		} /* fail! */
		value = skip(parse_value(child, skip(value + 1))); /* skip any spacing, get the value. */
		if (!value) return 0;
		item->size++;
	}

	if (*value == '}') return value + 1; /* end of array */
	ep = value;
	return 0; /* malformed. */
}

Json *Json_getItem (Json *object, const char* string) {
	Json *c = object->child;
	while (c && Json_strcasecmp(c->name, string))
		c = c->next;
	return c;
}

const char* Json_getString (Json* object, const char* name, const char* defaultValue) {
	object = Json_getItem(object, name);
	if (object) return object->valueString;
	return defaultValue;
}

float Json_getFloat (Json* value, const char* name, float defaultValue) {
	value = Json_getItem(value, name);
	return value ? value->valueFloat : defaultValue;
}

int Json_getInt (Json* value, const char* name, int defaultValue) {
	value = Json_getItem(value, name);
	return value ? value->valueInt : defaultValue;
}
