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

#ifndef SkXMLParser_DEFINED
#define SkXMLParser_DEFINED

#include "SkMath.h"
#include "SkString.h"

class SkStream;

class SkDOM;
struct SkDOMNode;

class SkXMLParserError {
public:
    enum ErrorCode {
        kNoError,
        kEmptyFile,
        kUnknownElement,
        kUnknownAttributeName,
        kErrorInAttributeValue,
        kDuplicateIDs,
        kUnknownError
    };

    SkXMLParserError();
    virtual ~SkXMLParserError();
    ErrorCode getErrorCode() const { return fCode; }
    virtual void getErrorString(SkString* str) const;
    int getLineNumber() const { return fLineNumber; }
    int getNativeCode() const { return fNativeCode; }
    bool hasError() const { return fCode != kNoError || fNativeCode != -1; }
    bool hasNoun() const { return fNoun.size() > 0; }
    void reset();
    void setCode(ErrorCode code) { fCode = code; }
    void setNoun(const SkString& str) { fNoun.set(str); }
    void setNoun(const char* ch)  { fNoun.set(ch); }
    void setNoun(const char* ch, size_t len) { fNoun.set(ch, len); }
protected:
    ErrorCode fCode;
private:
    int fLineNumber;
    int fNativeCode;
    SkString fNoun;
    friend class SkXMLParser;
};

class SkXMLParser {
public:
            SkXMLParser(SkXMLParserError* parserError = NULL);
    virtual ~SkXMLParser();

    /** Returns true for success
    */
    bool parse(const char doc[], size_t len);
    bool parse(SkStream& docStream);
    bool parse(const SkDOM&, const SkDOMNode*);

    static void GetNativeErrorString(int nativeErrorCode, SkString* str);

protected:
    // override in subclasses; return true to stop parsing
    virtual bool onStartElement(const char elem[]);
    virtual bool onAddAttribute(const char name[], const char value[]);
    virtual bool onEndElement(const char elem[]);
    virtual bool onText(const char text[], int len);

public:
    // public for ported implementation, not meant for clients to call
    virtual bool startElement(const char elem[]);
    virtual bool addAttribute(const char name[], const char value[]);
    virtual bool endElement(const char elem[]);
    virtual bool text(const char text[], int len); 
    void* fParser;
protected:
    SkXMLParserError* fError;
private:
    void reportError(void* parser);
};

#if 0
class SkXMLPullParser {
public:
            SkXMLPullParser();
    explicit SkXMLPullParser(SkStream*);
    virtual ~SkXMLPullParser();

    SkStream*   getStream() const { return fStream; }
    SkStream*   setStream(SkStream* stream);

    enum EventType {
        ERROR = -1,
        START_DOCUMENT,
        END_DOCUMENT,
        START_TAG,
        END_TAG,
        TEXT,
        CDSECT,
        ENTITY_REF,
        IGNORABLE_WHITESPACE,
        PROCESSING_INSTRUCTION,
        COMMENT,
        DOCDECL
    };

    EventType   nextToken();
    EventType   getEventType() const { return fCurr.fEventType; }

    struct AttrInfo {
        const char* fName;
        const char* fValue;
    };
    
    int         getDepth() const { return fDepth; }
    const char* getName();
    int         getAttributeCount();
    void        getAttributeInfo(int, AttrInfo*);
    const char* getText();
    bool        isWhitespace();
    
protected:
    virtual bool onEntityReplacement(const char name[],
                                     SkString* replacement);

public:
    struct Curr {
        EventType   fEventType;
        const char* fName;
        AttrInfo*   fAttrInfos;
        int         fAttrInfoCount;
        bool        fIsWhitespace;
    };

private:
    // implemented in the porting layer
    bool        onInit();   // return false on failure
    EventType   onNextToken();
    void        onExit();
    
    SkStream*   fStream;
    Curr        fCurr;
    int         fDepth;
    
    struct Impl;
    Impl*   fImpl;
};
#endif

#endif
