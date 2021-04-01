/*
Copyright (c) 2009, Dave Gamble
Copyright (c) 2013, Esoteric Software

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

#ifdef SPINE_UE4
#include "SpinePluginPrivatePCH.h"
#endif

/* Json */
/* JSON parser in CPP, from json.c in the spine-c runtime */

#ifndef _DEFAULT_SOURCE
/* Bring strings.h definitions into string.h, where appropriate */
#define _DEFAULT_SOURCE
#endif

#ifndef _BSD_SOURCE
/* Bring strings.h definitions into string.h, where appropriate */
#define _BSD_SOURCE
#endif

#include <spine/Json.h>
#include <spine/Extension.h>
#include <spine/SpineString.h>

#include <assert.h>
#include <math.h>

using namespace spine;

const int Json::JSON_FALSE = 0;
const int Json::JSON_TRUE = 1;
const int Json::JSON_NULL = 2;
const int Json::JSON_NUMBER = 3;
const int Json::JSON_STRING = 4;
const int Json::JSON_ARRAY = 5;
const int Json::JSON_OBJECT = 6;

const char *Json::_error = NULL;

Json *Json::getItem(Json *object, const char *string) {
	Json *c = object->_child;
	while (c && json_strcasecmp(c->_name, string)) {
		c = c->_next;
	}
	return c;
}

const char *Json::getString(Json *object, const char *name, const char *defaultValue) {
	object = getItem(object, name);
	if (object) {
		return object->_valueString;
	}

	return defaultValue;
}

float Json::getFloat(Json *value, const char *name, float defaultValue) {
	value = getItem(value, name);
	return value ? value->_valueFloat : defaultValue;
}

int Json::getInt(Json *value, const char *name, int defaultValue) {
	value = getItem(value, name);
	return value ? value->_valueInt : defaultValue;
}

bool Json::getBoolean(spine::Json *value, const char *name, bool defaultValue) {
	value = getItem(value, name);
	if (value) {
		if (value->_valueString) return strcmp(value->_valueString, "true") == 0;
		if (value->_type == JSON_NULL) return false;
		if (value->_type == JSON_NUMBER) return value->_valueFloat != 0;
		return defaultValue;
	} else {
		return defaultValue;
	}
}

const char *Json::getError() {
	return _error;
}

Json::Json(const char *value) :
		_next(NULL),
#if SPINE_JSON_HAVE_PREV
		_prev(NULL),
#endif
		_child(NULL),
		_type(0),
		_size(0),
		_valueString(NULL),
		_valueInt(0),
		_valueFloat(0),
		_name(NULL) {
	if (value) {
		value = parseValue(this, skip(value));

		assert(value);
	}
}

Json::~Json() {
    spine::Json* curr = nullptr;
    spine::Json* next = _child;
    do {
        curr = next;
        if (curr) {
            next = curr->_next;
        }
        delete curr;
    } while(next);

    if (_valueString) {
        SpineExtension::free(_valueString, __FILE__, __LINE__);
    }

    if (_name) {
        SpineExtension::free(_name, __FILE__, __LINE__);
    }
}

const char *Json::skip(const char *inValue) {
	if (!inValue) {
		/* must propagate NULL since it's often called in skip(f(...)) form */
		return NULL;
	}

	while (*inValue && (unsigned char) *inValue <= 32) {
		inValue++;
	}

	return inValue;
}

const char *Json::parseValue(Json *item, const char *value) {
	/* Referenced by constructor, parseArray(), and parseObject(). */
	/* Always called with the result of skip(). */
#ifdef SPINE_JSON_DEBUG /* Checked at entry to graph, constructor, and after every parse call. */
	if (!value) {
		/* Fail on null. */
		return NULL;
	}
#endif

	switch (*value) {
	case 'n': {
		if (!strncmp(value + 1, "ull", 3)) {
			item->_type = JSON_NULL;
			return value + 4;
		}
		break;
	}
	case 'f': {
		if (!strncmp(value + 1, "alse", 4)) {
			item->_type = JSON_FALSE;
			/* calloc prevents us needing item->_type = JSON_FALSE or valueInt = 0 here */
			return value + 5;
		}
		break;
	}
	case 't': {
		if (!strncmp(value + 1, "rue", 3)) {
			item->_type = JSON_TRUE;
			item->_valueInt = 1;
			return value + 4;
		}
		break;
	}
	case '\"':
		return parseString(item, value);
	case '[':
		return parseArray(item, value);
	case '{':
		return parseObject(item, value);
	case '-': /* fallthrough */
	case '0': /* fallthrough */
	case '1': /* fallthrough */
	case '2': /* fallthrough */
	case '3': /* fallthrough */
	case '4': /* fallthrough */
	case '5': /* fallthrough */
	case '6': /* fallthrough */
	case '7': /* fallthrough */
	case '8': /* fallthrough */
	case '9':
		return parseNumber(item, value);
	default:
		break;
	}

	_error = value;
	return NULL; /* failure. */
}

static const unsigned char firstByteMark[7] = {0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC};

const char *Json::parseString(Json *item, const char *str) {
	const char *ptr = str + 1;
	char *ptr2;
	char *out;
	int len = 0;
	unsigned uc, uc2;
	if (*str != '\"') {
		/* TODO: don't need this check when called from parseValue, but do need from parseObject */
		_error = str;
		return 0;
	} /* not a string! */

	while (*ptr != '\"' && *ptr && ++len) {
		if (*ptr++ == '\\') {
			ptr++; /* Skip escaped quotes. */
		}
	}

	out = SpineExtension::alloc<char>(len + 1, __FILE__, __LINE__); /* The length needed for the string, roughly. */
	if (!out) {
		return 0;
	}

	ptr = str + 1;
	ptr2 = out;
	while (*ptr != '\"' && *ptr) {
		if (*ptr != '\\') {
			*ptr2++ = *ptr++;
		} else {
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
				case 'u': {
					/* transcode utf16 to utf8. */
					sscanf(ptr + 1, "%4x", &uc);
					ptr += 4; /* get the unicode char. */

					if ((uc >= 0xDC00 && uc <= 0xDFFF) || uc == 0) {
						break; /* check for invalid.	*/
					}

					/* TODO provide an option to ignore surrogates, use unicode replacement character? */
					if (uc >= 0xD800 && uc <= 0xDBFF) /* UTF16 surrogate pairs.	*/ {
						if (ptr[1] != '\\' || ptr[2] != 'u') {
							break; /* missing second-half of surrogate.	*/
						}
						sscanf(ptr + 3, "%4x", &uc2);
						ptr += 6;
						if (uc2 < 0xDC00 || uc2 > 0xDFFF) {
							break; /* invalid second-half of surrogate.	*/
						}
						uc = 0x10000 + (((uc & 0x3FF) << 10) | (uc2 & 0x3FF));
					}

					len = 4;
					if (uc < 0x80) {
						len = 1;
					} else if (uc < 0x800) {
						len = 2;
					} else if (uc < 0x10000) {
						len = 3;
					}
					ptr2 += len;

					switch (len) {
						case 4:
							*--ptr2 = ((uc | 0x80) & 0xBF);
							uc >>= 6;
							/* fallthrough */
						case 3:
							*--ptr2 = ((uc | 0x80) & 0xBF);
							uc >>= 6;
							/* fallthrough */
						case 2:
							*--ptr2 = ((uc | 0x80) & 0xBF);
							uc >>= 6;
							/* fallthrough */
						case 1:
							*--ptr2 = (uc | firstByteMark[len]);
					}
					ptr2 += len;
					break;
				}
				default:
					*ptr2++ = *ptr;
					break;
			}
			ptr++;
		}
	}

	*ptr2 = 0;

	if (*ptr == '\"') {
		ptr++; /* TODO error handling if not \" or \0 ? */
	}

	item->_valueString = out;
	item->_type = JSON_STRING;

	return ptr;
}

const char *Json::parseNumber(Json *item, const char *num) {
	double result = 0.0;
	int negative = 0;
	char *ptr = (char *) num;

	if (*ptr == '-') {
		negative = -1;
		++ptr;
	}

	while (*ptr >= '0' && *ptr <= '9') {
		result = result * 10.0 + (*ptr - '0');
		++ptr;
	}

	if (*ptr == '.') {
		double fraction = 0.0;
		int n = 0;
		++ptr;

		while (*ptr >= '0' && *ptr <= '9') {
			fraction = (fraction * 10.0) + (*ptr - '0');
			++ptr;
			++n;
		}
		result += fraction / pow(10.0, n);
	}

	if (negative) {
		result = -result;
	}

	if (*ptr == 'e' || *ptr == 'E') {
		double exponent = 0;
		int expNegative = 0;
		int n = 0;
		++ptr;

		if (*ptr == '-') {
			expNegative = -1;
			++ptr;
		} else if (*ptr == '+') {
			++ptr;
		}

		while (*ptr >= '0' && *ptr <= '9') {
			exponent = (exponent * 10.0) + (*ptr - '0');
			++ptr;
			++n;
		}

		if (expNegative) {
			result = result / pow(10, exponent);
		} else {
			result = result * pow(10, exponent);
		}
	}

	if (ptr != num) {
		/* Parse success, number found. */
		item->_valueFloat = (float)result;
		item->_valueInt = (int)result;
		item->_type = JSON_NUMBER;
		return ptr;
	} else {
		/* Parse failure, _error is set. */
		_error = num;
		return NULL;
	}
}

const char *Json::parseArray(Json *item, const char *value) {
	Json *child;

#ifdef SPINE_JSON_DEBUG /* unnecessary, only callsite (parse_value) verifies this */
	if (*value != '[') {
		ep = value;
		return 0;
	} /* not an array! */
#endif

	item->_type = JSON_ARRAY;
	value = skip(value + 1);
	if (*value == ']') {
		return value + 1; /* empty array. */
	}

	item->_child = child = new(__FILE__, __LINE__) Json(NULL);
	if (!item->_child) {
		return NULL; /* memory fail */
	}

	value = skip(parseValue(child, skip(value))); /* skip any spacing, get the value. */

	if (!value) {
		return NULL;
	}

	item->_size = 1;

	while (*value == ',') {
		Json *new_item = new(__FILE__, __LINE__) Json(NULL);
		if (!new_item) {
			return NULL; /* memory fail */
		}
		child->_next = new_item;
#if SPINE_JSON_HAVE_PREV
		new_item->prev = child;
#endif
		child = new_item;
		value = skip(parseValue(child, skip(value + 1)));
		if (!value) {
			return NULL; /* parse fail */
		}
		item->_size++;
	}

	if (*value == ']') {
		return value + 1; /* end of array */
	}

	_error = value;

	return NULL; /* malformed. */
}

/* Build an object from the text. */
const char *Json::parseObject(Json *item, const char *value) {
	Json *child;

#ifdef SPINE_JSON_DEBUG /* unnecessary, only callsite (parse_value) verifies this */
	if (*value != '{') {
		ep = value;
		return 0;
	} /* not an object! */
#endif

	item->_type = JSON_OBJECT;
	value = skip(value + 1);
	if (*value == '}') {
		return value + 1; /* empty array. */
	}

	item->_child = child = new(__FILE__, __LINE__) Json(NULL);
	if (!item->_child) {
		return NULL;
	}
	value = skip(parseString(child, skip(value)));
	if (!value) {
		return NULL;
	}
	child->_name = child->_valueString;
	child->_valueString = 0;
	if (*value != ':') {
		_error = value;
		return NULL;
	} /* fail! */

	value = skip(parseValue(child, skip(value + 1))); /* skip any spacing, get the value. */
	if (!value) {
		return NULL;
	}

	item->_size = 1;

	while (*value == ',') {
		Json *new_item = new(__FILE__, __LINE__) Json(NULL);
		if (!new_item) {
			return NULL; /* memory fail */
		}
		child->_next = new_item;
#if SPINE_JSON_HAVE_PREV
		new_item->prev = child;
#endif
		child = new_item;
		value = skip(parseString(child, skip(value + 1)));
		if (!value) {
			return NULL;
		}
		child->_name = child->_valueString;
		child->_valueString = 0;
		if (*value != ':') {
			_error = value;
			return NULL;
		} /* fail! */

		value = skip(parseValue(child, skip(value + 1))); /* skip any spacing, get the value. */
		if (!value) {
			return NULL;
		}
		item->_size++;
	}

	if (*value == '}') {
		return value + 1; /* end of array */
	}

	_error = value;

	return NULL; /* malformed. */
}

int Json::json_strcasecmp(const char *s1, const char *s2) {
	/* TODO we may be able to elide these NULL checks if we can prove
	 * the graph and input (only callsite is Json_getItem) should not have NULLs
	 */
	if (s1 && s2) {
#if defined(_WIN32)
		return _stricmp(s1, s2);
#else
		return strcasecmp(s1, s2);
#endif
	} else {
		if (s1 < s2) {
			return -1; /* s1 is null, s2 is not */
		} else if (s1 == s2) {
			return 0; /* both are null */
		} else {
			return 1; /* s2 is nul	s1 is not */
		}
	}
}
