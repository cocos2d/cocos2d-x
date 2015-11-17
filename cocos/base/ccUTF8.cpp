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

#include "base/ccUTF8.h"
#include "platform/CCCommon.h"
#include "base/CCConsole.h"
#include "ConvertUTF.h"

NS_CC_BEGIN

namespace StringUtils {

/*
 * @str:    the string to search through.
 * @c:        the character to not look for.
 *
 * Return value: the index of the last character that is not c.
 * */
unsigned int getIndexOfLastNotChar16(const std::vector<char16_t>& str, char16_t c)
{
    int len = static_cast<int>(str.size());

    int i = len - 1;
    for (; i >= 0; --i)
        if (str[i] != c) return i;

    return i;
}

/*
 * @str:    the string to trim
 * @index:    the index to start trimming from.
 *
 * Trims str st str=[0, index) after the operation.
 *
 * Return value: the trimmed string.
 * */
static void trimUTF16VectorFromIndex(std::vector<char16_t>& str, int index)
{
    int size = static_cast<int>(str.size());
    if (index >= size || index < 0)
        return;

    str.erase(str.begin() + index, str.begin() + size);
}

/*
 * @ch is the unicode character whitespace?
 *
 * Reference: http://en.wikipedia.org/wiki/Whitespace_character#Unicode
 *
 * Return value: weather the character is a whitespace character.
 * */
bool isUnicodeSpace(char16_t ch)
{
    return  (ch >= 0x0009 && ch <= 0x000D) || ch == 0x0020 || ch == 0x0085 || ch == 0x00A0 || ch == 0x1680
    || (ch >= 0x2000 && ch <= 0x200A) || ch == 0x2028 || ch == 0x2029 || ch == 0x202F
    ||  ch == 0x205F || ch == 0x3000;
}

bool isCJKUnicode(char16_t ch)
{
    return (ch >= 0x4E00 && ch <= 0x9FBF)   // CJK Unified Ideographs
        || (ch >= 0x2E80 && ch <= 0x2FDF)   // CJK Radicals Supplement & Kangxi Radicals
        || (ch >= 0x2FF0 && ch <= 0x30FF)   // Ideographic Description Characters, CJK Symbols and Punctuation & Japanese
        || (ch >= 0x3100 && ch <= 0x31BF)   // Korean
        || (ch >= 0xAC00 && ch <= 0xD7AF)   // Hangul Syllables
        || (ch >= 0xF900 && ch <= 0xFAFF)   // CJK Compatibility Ideographs
        || (ch >= 0xFE30 && ch <= 0xFE4F)   // CJK Compatibility Forms
        || (ch >= 0x31C0 && ch <= 0x4DFF);  // Other exiensions
}

void trimUTF16Vector(std::vector<char16_t>& str)
{
    int len = static_cast<int>(str.size());

    if ( len <= 0 )
        return;

    int last_index = len - 1;

    // Only start trimming if the last character is whitespace..
    if (isUnicodeSpace(str[last_index]))
    {
        for (int i = last_index - 1; i >= 0; --i)
        {
            if (isUnicodeSpace(str[i]))
                last_index = i;
            else
                break;
        }

        trimUTF16VectorFromIndex(str, last_index);
    }
}

bool UTF8ToUTF16(const std::string& utf8, std::u16string& outUtf16)
{
    if (utf8.empty())
    {
        outUtf16.clear();
        return true;
    }

    bool ret = false;
    
    const size_t utf16Bytes = (utf8.length()+1) * sizeof(char16_t);
    char16_t* utf16 = (char16_t*)malloc(utf16Bytes);
    memset(utf16, 0, utf16Bytes);

    char* utf16ptr = reinterpret_cast<char*>(utf16);
    const UTF8* error = nullptr;

    if (llvm::ConvertUTF8toWide(2, utf8, utf16ptr, error))
    {
        outUtf16 = utf16;
        ret = true;
    }

    free(utf16);

    return ret;
}

bool UTF16ToUTF8(const std::u16string& utf16, std::string& outUtf8)
{
    if (utf16.empty())
    {
        outUtf8.clear();
        return true;
    }

    return llvm::convertUTF16ToUTF8String(utf16, outUtf8);
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
std::string getStringUTFCharsJNI(JNIEnv* env, jstring srcjStr, bool* ret)
{
    std::string utf8Str;
    const unsigned short * unicodeChar = ( const unsigned short *)env->GetStringChars(srcjStr, nullptr);
    size_t unicodeCharLength = env->GetStringLength(srcjStr);
    const std::u16string unicodeStr((const char16_t *)unicodeChar, unicodeCharLength);
    bool flag = UTF16ToUTF8(unicodeStr, utf8Str);

    if (ret)
    {
        *ret = flag;
    }

    if (!flag)
    {
        utf8Str = "";
    }
    env->ReleaseStringChars(srcjStr, unicodeChar);
    return utf8Str;
}

jstring newStringUTFJNI(JNIEnv* env, std::string utf8Str, bool* ret)
{
    std::u16string utf16Str;
    bool flag = cocos2d::StringUtils::UTF8ToUTF16(utf8Str, utf16Str);

    if (ret)
    {
        *ret = flag;
    }

    if(!flag)
    {
        utf16Str.clear();
    }
    jstring stringText = env->NewString((const jchar*)utf16Str.data(), utf16Str.length());
    return stringText;
}
#endif

std::vector<char16_t> getChar16VectorFromUTF16String(const std::u16string& utf16)
{
    std::vector<char16_t> ret;
    size_t len = utf16.length();
    ret.reserve(len);
    for (size_t i = 0; i < len; ++i)
    {
        ret.push_back(utf16[i]);
    }
    return ret;
}

long getCharacterCountInUTF8String(const std::string& utf8)
{
    return getUTF8StringLength((const UTF8*)utf8.c_str());
}

} //namespace StringUtils {


int cc_wcslen(const unsigned short* str)
{
    if (str == nullptr)
        return -1;
    int i=0;
    while(*str++) i++;
    return i;
}

void cc_utf8_trim_ws(std::vector<unsigned short>* str)
{
    if (str == nullptr)
        return;
    // unsigned short and char16_t are both 2 bytes
    std::vector<char16_t>* ret = reinterpret_cast<std::vector<char16_t>*>(str);
    StringUtils::trimUTF16Vector(*ret);
}

bool isspace_unicode(unsigned short ch)
{
    return StringUtils::isUnicodeSpace(ch);
}


bool iscjk_unicode(unsigned short ch)
{
    return StringUtils::isCJKUnicode(ch);
}


long cc_utf8_strlen (const char * p, int max)
{
    CC_UNUSED_PARAM(max);
    if (p == nullptr)
        return -1;
    return StringUtils::getCharacterCountInUTF8String(p);
}

unsigned int cc_utf8_find_last_not_char(const std::vector<unsigned short>& str, unsigned short c)
{
    std::vector<char16_t> char16Vector;
    for (const auto& e : str)
    {
        char16Vector.push_back(e);
    }
    
    return StringUtils::getIndexOfLastNotChar16(char16Vector, c);
}

std::vector<unsigned short> cc_utf16_vec_from_utf16_str(const unsigned short* str)
{
    std::vector<unsigned short> str_new;
    
    if (str == nullptr)
        return str_new;
    
    int len = cc_wcslen(str);
    
    for (int i = 0; i < len; ++i)
    {
        str_new.push_back(str[i]);
    }
    return str_new;
}

unsigned short* cc_utf8_to_utf16(const char* str_old, int length/* = -1*/, int* rUtf16Size/* = nullptr*/)
{
    if (str_old == nullptr)
        return nullptr;
    
    unsigned short* ret = nullptr;
    
    std::u16string outUtf16;
    bool succeed = StringUtils::UTF8ToUTF16(str_old, outUtf16);
    
    if (succeed)
    {
        ret = new unsigned short[outUtf16.length() + 1];
        ret[outUtf16.length()] = 0;
        memcpy(ret, outUtf16.data(), outUtf16.length() * sizeof(unsigned short));
        if (rUtf16Size)
        {
            *rUtf16Size = static_cast<int>(outUtf16.length());
        }
    }
    
    return ret;
}

char * cc_utf16_to_utf8 (const unsigned short  *str,
                  int             len,
                  long            *items_read,
                  long            *items_written)
{
    if (str == nullptr)
        return nullptr;
    
    
    std::u16string utf16;
    int utf16Len = len < 0 ? cc_wcslen(str) : len;
    
    for (int i = 0; i < utf16Len; ++i)
    {
        utf16.push_back(str[i]);
    }
    
    char* ret = nullptr;
    std::string outUtf8;
    bool succeed = StringUtils::UTF16ToUTF8(utf16, outUtf8);
    
    if (succeed)
    {
        ret = new char[outUtf8.length() + 1];
        ret[outUtf8.length()] = '\0';
        memcpy(ret, outUtf8.data(), outUtf8.length());
    }
    
    return ret;
}


NS_CC_END
