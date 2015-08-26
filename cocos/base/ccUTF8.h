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

#include "platform/CCPlatformMacros.h"
#include <vector>
#include <string>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
#include "platform/android/jni/JniHelper.h"
#endif

NS_CC_BEGIN

namespace StringUtils {

/**
 *  @brief @~english Converts utf8 string to utf16 string.
 * @~chinese 将utf8字符串转为utf16字符串
 *
 *  @param utf8 @~english The utf8 string to be converted.
 * @~chinese 需要转换的utf8字符串
 *
 *  @param outUtf16 @~english The output utf16 string.
 * @~chinese 输出的utf16字符串
 *
 *  @return @~english True if succeed, otherwise false.
 * @~chinese 成功返回true，否则返回false
 *
 *  @note @~english Please check the return value before using \p outUtf16
 *  e.g.
 * @~chinese 使用前请检查返回值
 *  例如
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
 *  @brief @~english Converts utf16 string to utf8 string.
 * @~chinese 将utf16字符串转为utf8字符串
 *  @param utf16 @~english The utf16 string to be converted.
 * @~chinese 需要被转换的utf16字符串
 *  @param outUtf8 @~english The output utf8 string.
 * @~chinese 输出的utf8字符串
 *  @return @~english True if succeed, otherwise false.
 * @~chinese 成功返回true，否则返回false
 *
 *  @note @~english Please check the return value before using \p outUtf8
 *  e.g.
 * @~chinese 使用前请检查返回值
 *  例如
 *  @code
 *    std::string utf8;
 *    bool ret = StringUtils::UTF16ToUTF8(u"\u4f60\u597d", utf16);
 *    if (ret) {
 *        do_some_thing_with_utf8(utf8);
 *    }
 *  @endcode
 */
CC_DLL bool UTF16ToUTF8(const std::u16string& utf16, std::string& outUtf8);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)


/**
*  @brief convert jstring to utf8 std::string,  same function with env->getStringUTFChars. 
*         because getStringUTFChars can not pass special emoticon
*  @param env   The JNI Env
*  @param srcjStr The jstring which want to convert
*  @param ret   True if the conversion succeeds and the ret pointer isn't null
*  @returns the result of utf8 string
*/
CC_DLL std::string getStringUTFCharsJNI(JNIEnv* env, jstring srcjStr, bool* ret = nullptr);

/**
*  @brief create a jstring with utf8 std::string, same function with env->newStringUTF
*         because newStringUTF can not convert special emoticon
*  @param env   The JNI Env
*  @param srcjStr The std::string which want to convert
*  @param ret     True if the conversion succeeds and the ret pointer isn't null
*  @returns the result of jstring,the jstring need to DeleteLocalRef(jstring);
*/
CC_DLL jstring newStringUTFJNI(JNIEnv* env, std::string utf8Str, bool* ret = nullptr);
#endif

/**
 *  @brief @~english Trims the unicode spaces at the end of char16_t vector.
 * @~chinese 去除unicode结尾的空格
 */
CC_DLL void trimUTF16Vector(std::vector<char16_t>& str);

/**
 *  @brief @~english Whether the character is a whitespace character.
 * @~chinese 判断是否为一个空格字符
 *
 *  @param ch @~english The unicode character.
 * @~chinese 一个unicode字符.
 *
 *  @returns @~english Whether the character is a white space character.
 * @~chinese 是否为一个空白字符
 * 
 *  @see http://en.wikipedia.org/wiki/Whitespace_character#Unicode
 *
 */
CC_DLL bool isUnicodeSpace(char16_t ch);

/**
 *  @brief @~english Whether the character is a Chinese/Japanese/Korean character.
 * @~chinese 判断是否为 中/日/韩 字符
 *
 *  @param ch @~english The unicode character.
 * @~chinese 一个unicode字符.
 *
 *  @returns @~english Whether the character is a Chinese character.
 * @~chinese 是否为一个 中/日/韩 字符
 * 
 *  @see http://www.searchtb.com/2012/04/chinese_encode.html
 *  @see http://tieba.baidu.com/p/748765987
 *
 */
CC_DLL bool isCJKUnicode(char16_t ch);

/**
 *  @brief @~english Returns the length of the string in characters.
 * @~chinese 翻译字符串的长度
 *
 *  @param utf8 @~english An UTF-8 encoded string.
 * @~chinese 一个UTF-8编码字符.
 *
 *  @returns @~english The length of the string in characters.
 * @~chinese 返回一个字符串的长度
 */
CC_DLL long getCharacterCountInUTF8String(const std::string& utf8);

/**
 *  @brief @~english Gets the index of the last character that is not equal to the character given.
 * @~chinese 获取一个不等于自己的的字符的索引值
 *  @param str@~english The string to be searched.
 * @~chinese 被搜索的字符串
 *  @param c @~english The character to be searched for.
 * @~chinese 搜索的字符串
 *  @returns @~english The index of the last character that is not \p c.
 * @~chinese 最后一个字符的索引值
 */
CC_DLL unsigned int getIndexOfLastNotChar16(const std::vector<char16_t>& str, char16_t c);

/**
 *  @brief @~english Gets char16_t vector from a given utf16 string.
 * @~chinese 从指定的utf16字符串内获取char16_t向量
 */
CC_DLL std::vector<char16_t> getChar16VectorFromUTF16String(const std::u16string& utf16);

} // namespace StringUtils {

/**
 * @~english Returns the character count in UTF16 string.
 * @~chinese 返回一个utf16字符串的字符数量
 *
 * @param str @~english Pointer to the start of a UTF-16 encoded string. It must be an NULL terminal UTF8 string.
 * @~chinese 指向一个utf-16编码字符串的开始。
 *
 * @deprecated @~english Please use c++11 `std::u16string::length` instead, don't use `unsigned short*` directly.
 * @~chinese 请使用c++ 11 `std::u16string::length`
 */
CC_DEPRECATED_ATTRIBUTE CC_DLL int cc_wcslen(const unsigned short* str);

/**
 * @~english Trims the space characters at the end of UTF8 string.
 * @~chinese 修剪utf8字符串的前后空白
 *  @deprecated @~english Please use `StringUtils::trimUTF16Vector` instead.
 * @~chinese 请使用“StringUtils::trimUTF16Vector”代替。
 */
CC_DEPRECATED_ATTRIBUTE CC_DLL void cc_utf8_trim_ws(std::vector<unsigned short>* str);

/**
 * @~english Whether the character is a whitespace character.
 * @~chinese  是否为一个空格字符
 * 
 * @param ch @~english The unicode character.
 * @~chinese unicode字符。
 *
 * @returns @~english Whether the character is a white space character.
 * @~chinese 返回是一个空白字符。
 *
 * @deprecated @~english Please use `StringUtils::isUnicodeSpace` instead.
 * @~chinese 请使用“StringUtils::isUnicodeSpace”代替.
 * 
 * @see http://en.wikipedia.org/wiki/Whitespace_character#Unicode
 */
CC_DEPRECATED_ATTRIBUTE CC_DLL bool isspace_unicode(unsigned short ch);

/**
 * @~english Whether the character is a Chinese/Japanese/Korean character.
 * @~chinese 判断这个字符是否为中/日/韩文
 * 
 * @param ch @~english The unicode character
 * @~chinese 一个unicode字符
 *
 * @returns @~english Whether the character is a Chinese character.
 * @~chinese 返回字符是否为中|日|韩文。
 * @deprecated @~english Please use `StringUtils::isCJKUnicode` instead.
 *
 * @~chinese 请使用“StringUtils::isCJKUnicode”代替。
 * 
 * @see http://www.searchtb.com/2012/04/chinese_encode.html
 * @see http://tieba.baidu.com/p/748765987
 */
CC_DEPRECATED_ATTRIBUTE CC_DLL bool iscjk_unicode(unsigned short ch);

/**
 * @~english Returns the length of the string in characters.
 * @~chinese 返回字符串的长度。
 * 
 * @param p @~english Pointer to the start of a UTF-8 encoded string. It must be an NULL terminal UTF8 string.
 * @~chinese 指向一个utf8编码字符串的开始处。
 *
 * @param max @~english Not used from 3.1, just keep it for backward compatibility.
 * @~chinese 从3.1开始使用，仅仅保持向后兼容性。
 *
 * @deprecated @~english Please use `StringUtils::getCharacterCountInUTF8String` instead.
 * @~chinese 请使用“StringUtils::getCharacterCountInUTF8String”代替。
 *
 * @returns @~english The length of the string in characters.
 * @~chinese 字符串的长度。
 **/
CC_DEPRECATED_ATTRIBUTE CC_DLL long cc_utf8_strlen (const char * p, int max = -1);

/**
 * @~english Find the last character that is not equal to the character given.
 * @~chinese 在给定字符中查找一个字符（这个字符不等于给定的原字符），返回找到最后一个字符所在位置。
 * 
 * @param str   @~english The string to be searched.
 * @~chinese 要搜索的字符串。
 * @param c     @~english The character to be searched for.
 * @~chinese 搜索的字符。
 * @deprecated @~english Please use `StringUtils::getIndexOfLastNotChar16` instead.
 * @~chinese 请使用“stringutil::getIndexOfLastNotChar16”代替。
 * @returns @~english The index of the last character that is not \p c.
 * @~chinese 最后一个字符的索引。
 */
CC_DEPRECATED_ATTRIBUTE CC_DLL unsigned int cc_utf8_find_last_not_char(const std::vector<unsigned short>& str, unsigned short c);

/**
 *  @brief @~english Gets `unsigned short` vector from a given utf16 string.
 * @~chinese 从给定utf16字符串获取一个`unsigned short`向量。
 *  @param str @~english A given utf16 string.
 * @~chinese 一个utf16字符.
 *  @deprecated @~english Please use `StringUtils::getChar16VectorFromUTF16String` instead.
 * @~chinese 请使用“stringutil::getChar16VectorFromUTF16String”代替。
 */
CC_DEPRECATED_ATTRIBUTE CC_DLL std::vector<unsigned short> cc_utf16_vec_from_utf16_str(const unsigned short* str);

/**
 * @~english Creates an utf8 string from a c string. The result will be null terminated.
 * @~chinese 从一个C字符串创建一个utf8字符串。结果将以null结尾。
 * 
 * @param str_old @~english Pointer to the start of a C string. It must be an NULL terminal UTF8 string.
 * @~chinese 指向一个C字符串的开始。它必须是一个NULL终端UTF8字符串。
 *
 * @param length  @~english Not used from 3.1, keep it just for backward compatibility.
 * @~chinese 从3.1开始不再使用,仅仅保持向后兼容性。
 *
 * @param rUtf16Size @~english The character count in the return UTF16 string.
 * @~chinese 返回UTF16字符串中的字符数。
 *
 * @deprecated @~english Please use `StringUtils::UTF8ToUTF16` instead.
 * @~chinese 请使用“StringUtils::UTF8ToUTF16”代替。
 *
 * @returns @~english The newly created utf16 string, it must be released with `delete[]`,
 *          If an error occurs, %NULL will be returned.
 * @~chinese 创建一个新的utf16字符串,它必须被释放“delete[]”, 如果出现错误，将返回null
 */
CC_DEPRECATED_ATTRIBUTE CC_DLL unsigned short* cc_utf8_to_utf16(const char* str_old, int length = -1, int* rUtf16Size = nullptr);

/**
 * @~english Converts a string from UTF-16 to UTF-8. The result will be null terminated.
 * @~chinese 将UTF-16转为UTF-8,返回结果将以null终止
 * 
 * @param str @~english An UTF-16 encoded string, It must be an NULL terminal UTF16 string.
 * @~chinese 一个UTF-16编码字符串，必须是一个以null终止的字符串
 *
 * @param len @~english Not used from 3.1, keep it just for backward compatibility.
 * @~chinese 从3.1开始不再使用,仅仅保持向后兼容性。
 *
 * @param items_read @~english Not used from 3.1, keep it just for backward compatibility.
 * @~chinese 从3.1开始不再使用,仅仅保持向后兼容性。
 *
 * @param items_written  @~english Not used from 3.1, keep it just for backward compatibility.
 * @~chinese 从3.1开始不再使用,仅仅保持向后兼容性。
 *
 * @deprecated @~english Please use `StringUtils::UTF16ToUTF8` instead.
 * @~chinese 请使用“StringUtils::UTF16ToUTF8”代替。
 *
 * @returns @~english A pointer to a newly allocated UTF-8 string. This value must be
 *          released with `delete[]`. If an error occurs, %NULL will be returned.
 * @~chinese 新分配的utf-8的字符串的指针。这个值必须被释放delete[]。如果出现错误,将返回NULL。
 */
CC_DEPRECATED_ATTRIBUTE CC_DLL char * cc_utf16_to_utf8 (const unsigned short  *str,
                  int             len = -1,
                  long            *items_read = nullptr,
                  long            *items_written = nullptr);


NS_CC_END

#endif /** defined(__cocos2dx__ccUTF8__) */
