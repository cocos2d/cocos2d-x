/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sts=4 et sw=4 tw=99:
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef js_CharacterEncoding_h
#define js_CharacterEncoding_h

#include "mozilla/NullPtr.h"
#include "mozilla/Range.h"

#include "js/TypeDecls.h"
#include "js/Utility.h"

namespace js {
struct ThreadSafeContext;
}

namespace JS {

/*
 * By default, all C/C++ 1-byte-per-character strings passed into the JSAPI
 * are treated as ISO/IEC 8859-1, also known as Latin-1. That is, each
 * byte is treated as a 2-byte character, and there is no way to pass in a
 * string containing characters beyond U+00FF.
 */
class Latin1Chars : public mozilla::Range<unsigned char>
{
    typedef mozilla::Range<unsigned char> Base;

  public:
    Latin1Chars() : Base() {}
    Latin1Chars(char *aBytes, size_t aLength) : Base(reinterpret_cast<unsigned char *>(aBytes), aLength) {}
    Latin1Chars(const char *aBytes, size_t aLength)
      : Base(reinterpret_cast<unsigned char *>(const_cast<char *>(aBytes)), aLength)
    {}
};

/*
 * A Latin1Chars, but with \0 termination for C compatibility.
 */
class Latin1CharsZ : public mozilla::RangedPtr<unsigned char>
{
    typedef mozilla::RangedPtr<unsigned char> Base;

  public:
    Latin1CharsZ() : Base(nullptr, 0) {}

    Latin1CharsZ(char *aBytes, size_t aLength)
      : Base(reinterpret_cast<unsigned char *>(aBytes), aLength)
    {
        JS_ASSERT(aBytes[aLength] == '\0');
    }

    Latin1CharsZ(unsigned char *aBytes, size_t aLength)
      : Base(aBytes, aLength)
    {
        JS_ASSERT(aBytes[aLength] == '\0');
    }

    char *c_str() { return reinterpret_cast<char *>(get()); }
};

class UTF8Chars : public mozilla::Range<unsigned char>
{
    typedef mozilla::Range<unsigned char> Base;

  public:
    UTF8Chars() : Base() {}
    UTF8Chars(char *aBytes, size_t aLength)
      : Base(reinterpret_cast<unsigned char *>(aBytes), aLength)
    {}
    UTF8Chars(const char *aBytes, size_t aLength)
      : Base(reinterpret_cast<unsigned char *>(const_cast<char *>(aBytes)), aLength)
    {}
};

/*
 * SpiderMonkey also deals directly with UTF-8 encoded text in some places.
 */
class UTF8CharsZ : public mozilla::RangedPtr<unsigned char>
{
    typedef mozilla::RangedPtr<unsigned char> Base;

  public:
    UTF8CharsZ() : Base(nullptr, 0) {}

    UTF8CharsZ(char *aBytes, size_t aLength)
      : Base(reinterpret_cast<unsigned char *>(aBytes), aLength)
    {
        JS_ASSERT(aBytes[aLength] == '\0');
    }

    UTF8CharsZ(unsigned char *aBytes, size_t aLength)
      : Base(aBytes, aLength)
    {
        JS_ASSERT(aBytes[aLength] == '\0');
    }

    char *c_str() { return reinterpret_cast<char *>(get()); }
};

/*
 * SpiderMonkey uses a 2-byte character representation: it is a
 * 2-byte-at-a-time view of a UTF-16 byte stream. This is similar to UCS-2,
 * but unlike UCS-2, we do not strip UTF-16 extension bytes. This allows a
 * sufficiently dedicated JavaScript program to be fully unicode-aware by
 * manually interpreting UTF-16 extension characters embedded in the JS
 * string.
 */
class TwoByteChars : public mozilla::Range<jschar>
{
    typedef mozilla::Range<jschar> Base;

  public:
    TwoByteChars() : Base() {}
    TwoByteChars(jschar *aChars, size_t aLength) : Base(aChars, aLength) {}
    TwoByteChars(const jschar *aChars, size_t aLength) : Base(const_cast<jschar *>(aChars), aLength) {}
};

/*
 * A non-convertible variant of TwoByteChars that does not refer to characters
 * inlined inside a JSShortString or a JSInlineString. StableTwoByteChars are
 * thus safe to hold across a GC.
 */
class StableTwoByteChars : public mozilla::Range<jschar>
{
    typedef mozilla::Range<jschar> Base;

  public:
    StableTwoByteChars() : Base() {}
    StableTwoByteChars(jschar *aChars, size_t aLength) : Base(aChars, aLength) {}
    StableTwoByteChars(const jschar *aChars, size_t aLength) : Base(const_cast<jschar *>(aChars), aLength) {}
};

/*
 * A TwoByteChars, but \0 terminated for compatibility with JSFlatString.
 */
class TwoByteCharsZ : public mozilla::RangedPtr<jschar>
{
    typedef mozilla::RangedPtr<jschar> Base;

  public:
    TwoByteCharsZ() : Base(nullptr, 0) {}

    TwoByteCharsZ(jschar *chars, size_t length)
      : Base(chars, length)
    {
        JS_ASSERT(chars[length] == '\0');
    }
};

/*
 * Convert a 2-byte character sequence to "ISO-Latin-1". This works by
 * truncating each 2-byte pair in the sequence to a 1-byte pair. If the source
 * contains any UTF-16 extension characters, then this may give invalid Latin1
 * output. The returned string is zero terminated. The returned string or the
 * returned string's |start()| must be freed with JS_free or js_free,
 * respectively. If allocation fails, an OOM error will be set and the method
 * will return a nullptr chars (which can be tested for with the ! operator).
 * This method cannot trigger GC.
 */
extern Latin1CharsZ
LossyTwoByteCharsToNewLatin1CharsZ(js::ThreadSafeContext *cx, TwoByteChars tbchars);

extern UTF8CharsZ
TwoByteCharsToNewUTF8CharsZ(js::ThreadSafeContext *cx, TwoByteChars tbchars);

uint32_t
Utf8ToOneUcs4Char(const uint8_t *utf8Buffer, int utf8Length);

/*
 * Inflate bytes in UTF-8 encoding to jschars.
 * - On error, returns an empty TwoByteCharsZ.
 * - On success, returns a malloc'd TwoByteCharsZ, and updates |outlen| to hold
 *   its length;  the length value excludes the trailing null.
 */
extern TwoByteCharsZ
UTF8CharsToNewTwoByteCharsZ(JSContext *cx, const UTF8Chars utf8, size_t *outlen);

/*
 * The same as UTF8CharsToNewTwoByteCharsZ(), except that any malformed UTF-8 characters
 * will be replaced by \uFFFD. No exception will be thrown for malformed UTF-8
 * input.
 */
extern TwoByteCharsZ
LossyUTF8CharsToNewTwoByteCharsZ(JSContext *cx, const UTF8Chars utf8, size_t *outlen);

} // namespace JS

inline void JS_free(JS::Latin1CharsZ &ptr) { js_free((void*)ptr.get()); }
inline void JS_free(JS::UTF8CharsZ &ptr) { js_free((void*)ptr.get()); }

#endif /* js_CharacterEncoding_h */
