/*
 * Copyright (C) 2006 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SkString_DEFINED
#define SkString_DEFINED

#include "SkScalar.h"

/*  Some helper functions for C strings
*/

bool SkStrStartsWith(const char string[], const char prefix[]);
bool SkStrEndsWith(const char string[], const char suffix[]);
int SkStrStartsWithOneOf(const char string[], const char prefixes[]);

#define SkStrAppendS32_MaxSize  11
char*   SkStrAppendS32(char buffer[], int32_t);
#define SkStrAppendScalar_MaxSize  11
char*   SkStrAppendScalar(char buffer[], SkScalar);

/** \class SkString

    Light weight class for managing strings. Uses reference
    counting to make string assignments and copies very fast
    with no extra RAM cost. Assumes UTF8 encoding.
*/
class SkString {
public:
                SkString();
    explicit    SkString(size_t len);
    explicit    SkString(const char text[]);
                SkString(const char text[], size_t len);
                SkString(const SkString&);
                ~SkString();

    bool        isEmpty() const { return fRec->fLength == 0; }
    size_t      size() const { return (size_t) fRec->fLength; }
    const char* c_str() const { return fRec->data(); }
    char operator[](size_t n) const { return this->c_str()[n]; }

    bool    equals(const SkString&) const;
    bool    equals(const char text[]) const;
    bool    equals(const char text[], size_t len) const;

    bool    startsWith(const char prefix[]) const
    {
        return SkStrStartsWith(fRec->data(), prefix);
    }
    bool    endsWith(const char suffix[]) const
    {
        return SkStrEndsWith(fRec->data(), suffix);
    }

    friend int operator==(const SkString& a, const SkString& b)
    {
        return a.equals(b);
    }
    friend int operator!=(const SkString& a, const SkString& b)
    {
        return !a.equals(b);
    }

    // these methods edit the string

    SkString&   operator=(const SkString&);

    char*   writable_str();
    char& operator[](size_t n) { return this->writable_str()[n]; }

    void    reset();
    void    resize(size_t len) { this->set(NULL, len); }
    void    set(const SkString& src) { *this = src; }
    void    set(const char text[]);
    void    set(const char text[], size_t len);
    void    setUTF16(const uint16_t[]);
    void    setUTF16(const uint16_t[], size_t len);

    void    insert(size_t offset, const SkString& src) { this->insert(offset, src.c_str(), src.size()); }
    void    insert(size_t offset, const char text[]);
    void    insert(size_t offset, const char text[], size_t len);
    void    insertUnichar(size_t offset, SkUnichar);
    void    insertS32(size_t offset, int32_t value);
    void    insertHex(size_t offset, uint32_t value, int minDigits = 0);
    void    insertScalar(size_t offset, SkScalar);

    void    append(const SkString& str) { this->insert((size_t)-1, str); }
    void    append(const char text[]) { this->insert((size_t)-1, text); }
    void    append(const char text[], size_t len) { this->insert((size_t)-1, text, len); }
    void    appendUnichar(SkUnichar uni) { this->insertUnichar((size_t)-1, uni); }
    void    appendS32(int32_t value) { this->insertS32((size_t)-1, value); }
    void    appendHex(uint32_t value, int minDigits = 0) { this->insertHex((size_t)-1, value, minDigits); }
    void    appendScalar(SkScalar value) { this->insertScalar((size_t)-1, value); }

    void    prepend(const SkString& str) { this->insert(0, str); }
    void    prepend(const char text[]) { this->insert(0, text); }
    void    prepend(const char text[], size_t len) { this->insert(0, text, len); }
    void    prependUnichar(SkUnichar uni) { this->insertUnichar(0, uni); }
    void    prependS32(int32_t value) { this->insertS32(0, value); }
    void    prependHex(uint32_t value, int minDigits = 0) { this->insertHex(0, value, minDigits); }
    void    prependScalar(SkScalar value) { this->insertScalar((size_t)-1, value); }

    void    printf(const char format[], ...);
    void    appendf(const char format[], ...);
    void    prependf(const char format[], ...);

    void    remove(size_t offset, size_t length);

    /** Swap contents between this and other. This function is guaranteed
        to never fail or throw.
    */
    void    swap(SkString& other);
    
private:
    struct Rec {
    public:
        uint16_t    fLength;
        uint16_t    fRefCnt;
        char        fBeginningOfData;

        char* data() { return &fBeginningOfData; }
        const char* data() const { return &fBeginningOfData; }
    };
    Rec* fRec;

#ifdef SK_DEBUG
    const char* fStr;
    void validate() const;
#else
    void validate() const {}
#endif

    static const Rec gEmptyRec;
    static Rec* AllocRec(const char text[], U16CPU len);
    static Rec* RefRec(Rec*);
};

class SkAutoUCS2 {
public:
    SkAutoUCS2(const char utf8[]);
    ~SkAutoUCS2();

    /** This returns the number of ucs2 characters
    */
    int count() const { return fCount; }
    /** This returns a null terminated ucs2 string
    */
    const uint16_t* getUCS2() const { return fUCS2; }

private:
    int         fCount;
    uint16_t*   fUCS2;
};

#endif

