/*
 * Copyright (C) 1999      Tom Tromey
 * Copyright (C) 2000      Red Hat, Inc.
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __cocos2dx__ccUTF8__
#define __cocos2dx__ccUTF8__

#include "base/CCPlatformMacros.h"
#include <vector>

NS_CC_BEGIN

CC_DLL int cc_wcslen(const unsigned short* str);

CC_DLL void cc_utf8_trim_ws(std::vector<unsigned short>* str);

/**
 * Whether the character is a whitespace character.
 *
 * @param ch    the unicode character
 * @returns     whether the character is a white space character.
 *
 * @see http://en.wikipedia.org/wiki/Whitespace_character#Unicode
 * */
CC_DLL bool isspace_unicode(unsigned short ch);

/**
 * Whether the character is a Chinese/Japanese/Korean character.
 *
 * @param ch    the unicode character
 * @returns     whether the character is a Chinese character.
 *
 * @see http://www.searchtb.com/2012/04/chinese_encode.html
 * @see http://tieba.baidu.com/p/748765987
 * */
CC_DLL bool iscjk_unicode(unsigned short ch);

/**
 * Returns the length of the string in characters.
 *
 * @param p     pointer to the start of a UTF-8 encoded string.
 * @param max   the maximum number of bytes to examine. If \p max is less than
 *              0, then the string is assumed to be null-terminated. If \p max
 *              is 0, \p p will not be examined and my be %nullptr.
 *
 * @returns the length of the string in characters
 **/
CC_DLL long
cc_utf8_strlen (const char * p, int max);

/**
 * Find the last character that is not equal to the character given.
 *
 * @param str   the string to be searched.
 * @param c     the character to be searched for.
 *
 * @returns the index of the last character that is not \p c.
 * */
CC_DLL unsigned int cc_utf8_find_last_not_char(std::vector<unsigned short> str, unsigned short c);

CC_DLL std::vector<unsigned short> cc_utf16_vec_from_utf16_str(const unsigned short* str);

/**
 * Creates a utf8 string from a cstring.
 *
 * @param str_old   pointer to the start of a C string.
 *
 * @returns the newly created utf8 string.
 * */
CC_DLL unsigned short* cc_utf8_to_utf16(const char* str_old, int length = -1, int* rUtf16Size = nullptr);

/**
 * Convert a string from UTF-16 to UTF-8. The result will be null terminated.
 *
 * @param str   a UTF-16 encoded string
 * @param len   the maximum length of \p str to use. If \p len < 0, then the
 *              string is null terminated.
 * @param items_read    location to store number of words read, or %nullptr.
 *                      If %nullptr, then %G_CONVERT_ERROR_PARTIAL_INPUT will be
 *                      returned in case \p str contains a trailing partial
 *                      character. If an error occurs then the index of the
 *                      invalid input is stored here.
 * @param items_written location to store number of bytes written, or %nullptr.
 *                      The value stored here does not include the trailing null.
 *
 * @returns a pointer to a newly allocated UTF-8 string. This value must be
 *          freed with free(). If an error occurs, %nullptr will be returned.
 **/
CC_DLL char *
cc_utf16_to_utf8 (const unsigned short  *str,
                  int             len,
                  long            *items_read,
                  long            *items_written);

NS_CC_END

#endif /* defined(__cocos2dx__ccUTF8__) */
