/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 Copyright (c) 2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
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
 ****************************************************************************/

#ifndef __cocos2dx__ccUTF8__
#define __cocos2dx__ccUTF8__

#include "base/CCPlatformMacros.h"
#include <vector>
#include <string>

NS_CC_BEGIN

namespace StringUtils {

/**
 *  @brief Converts utf8 string to utf16 string
 *  @param utf8 The utf8 string to be converted
 *  @param outUtf16 The output utf16 string
 *  @return true if succeed, otherwise false
 *  @note Please check the return value before using \p outUtf16
 *  e.g.
 *  @code
 *    std::u16string utf16;
 *    bool ret = StringUtils::UTF8ToUTF16("你好hello", utf16);
 *    if (ret) {
 *        do_some_thing_with_utf16(utf16);
 *    }
 *  @endcode
 */
CC_DLL bool UTF8ToUTF16(const std::string& utf8, std::u16string& outUtf16);

/**
 *  @brief Converts utf16 string to utf8 string
 *  @param utf16 The utf16 string to be converted
 *  @param outUtf8 The output utf8 string
 *  @return true if succeed, otherwise false
 *  @note Please check the return value before using \p outUtf8
 *  e.g.
 *  @code
 *    std::string utf8;
 *    bool ret = StringUtils::UTF16ToUTF8(u"\u4f60\u597d", utf16);
 *    if (ret) {
 *        do_some_thing_with_utf8(utf8);
 *    }
 *  @endcode
 */
CC_DLL bool UTF16ToUTF8(const std::u16string& utf16, std::string& outUtf8);

/**
 *  @brief Trims the unicode spaces at the end of char16_t vector
 */
CC_DLL void trimUTF16Vector(std::vector<char16_t>& str);

/**
 *  @brief Whether the character is a whitespace character.
 *
 *  @param ch    the unicode character
 *  @returns     whether the character is a white space character.
 *
 *  @see http://en.wikipedia.org/wiki/Whitespace_character#Unicode
 *
 */
CC_DLL bool isUnicodeSpace(char16_t ch);

/**
 *  @brief Whether the character is a Chinese/Japanese/Korean character.
 *
 *  @param ch    the unicode character
 *  @returns     whether the character is a Chinese character.
 *
 *  @see http://www.searchtb.com/2012/04/chinese_encode.html
 *  @see http://tieba.baidu.com/p/748765987
 *
 */
CC_DLL bool isCJKUnicode(char16_t ch);

/**
 *  @brief Returns the length of the string in characters.
 *
 *  @param utf8 an UTF-8 encoded string.
 *  @returns the length of the string in characters
 */
CC_DLL long getCharacterCountInUTF8String(const std::string& utf8);

/**
 *  @brief Gets the index of the last character that is not equal to the character given.
 *
 *  @param str   the string to be searched.
 *  @param c     the character to be searched for.
 *
 *  @returns the index of the last character that is not \p c.
 *
 */
CC_DLL unsigned int getIndexOfLastNotChar16(const std::vector<char16_t>& str, char16_t c);

/**
 *  @brief Gets char16_t vector from a given utf16 string
 */
CC_DLL std::vector<char16_t> getChar16VectorFromUTF16String(const std::u16string& utf16);

} // namespace StringUtils {


CC_DLL int cc_wcslen(const unsigned short* str);

CC_DEPRECATED_ATTRIBUTE void cc_utf8_trim_ws(std::vector<unsigned short>* str);

/**
 * Whether the character is a whitespace character.
 *
 * @param ch    the unicode character
 * @returns     whether the character is a white space character.
 *
 * @see http://en.wikipedia.org/wiki/Whitespace_character#Unicode
 * */
CC_DEPRECATED_ATTRIBUTE bool isspace_unicode(unsigned short ch);

/**
 * Whether the character is a Chinese/Japanese/Korean character.
 *
 * @param ch    the unicode character
 * @returns     whether the character is a Chinese character.
 *
 * @see http://www.searchtb.com/2012/04/chinese_encode.html
 * @see http://tieba.baidu.com/p/748765987
 * */
CC_DEPRECATED_ATTRIBUTE bool iscjk_unicode(unsigned short ch);

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
CC_DEPRECATED_ATTRIBUTE long
cc_utf8_strlen (const char * p, int max);

/**
 * Find the last character that is not equal to the character given.
 *
 * @param str   the string to be searched.
 * @param c     the character to be searched for.
 *
 * @returns the index of the last character that is not \p c.
 * */
CC_DEPRECATED_ATTRIBUTE unsigned int cc_utf8_find_last_not_char(const std::vector<unsigned short>& str, unsigned short c);

CC_DEPRECATED_ATTRIBUTE std::vector<unsigned short> cc_utf16_vec_from_utf16_str(const unsigned short* str);

/**
 * Creates a utf8 string from a cstring.
 *
 * @param str_old   pointer to the start of a C string.
 *
 * @returns the newly created utf8 string.
 * */
CC_DEPRECATED_ATTRIBUTE unsigned short* cc_utf8_to_utf16(const char* str_old, int length = -1, int* rUtf16Size = nullptr);

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
CC_DEPRECATED_ATTRIBUTE char *
cc_utf16_to_utf8 (const unsigned short  *str,
                  int             len,
                  long            *items_read,
                  long            *items_written);


NS_CC_END

#endif /* defined(__cocos2dx__ccUTF8__) */
