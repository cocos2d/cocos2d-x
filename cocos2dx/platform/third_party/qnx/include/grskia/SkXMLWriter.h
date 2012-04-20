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

#ifndef SkXMLWriter_DEFINED
#define SkXMLWriter_DEFINED

#include "SkTDArray.h"
#include "SkString.h"
#include "SkDOM.h"

class SkWStream;
class SkXMLParser;

class SkXMLWriter {
public:
            SkXMLWriter(bool doEscapeMarkup = true);
    virtual ~SkXMLWriter();

    void    addS32Attribute(const char name[], int32_t value);
    void    addAttribute(const char name[], const char value[]);
    void    addAttributeLen(const char name[], const char value[], size_t length);
    void    addHexAttribute(const char name[], uint32_t value, int minDigits = 0);
    void    addScalarAttribute(const char name[], SkScalar value);
    void    endElement() { this->onEndElement(); }
    void    startElement(const char elem[]);
    void    startElementLen(const char elem[], size_t length);
    void    writeDOM(const SkDOM&, const SkDOM::Node*, bool skipRoot);
    void    flush();
    virtual void writeHeader();

protected:
    virtual void onStartElementLen(const char elem[], size_t length) = 0;
    virtual void onAddAttributeLen(const char name[], const char value[], size_t length) = 0;
    virtual void onEndElement() = 0;

    struct Elem {
        SkString    fName;
        bool        fHasChildren;
    };
    void doEnd(Elem* elem);
    bool doStart(const char name[], size_t length);
    Elem* getEnd();
    const char* getHeader();
    SkTDArray<Elem*> fElems;

private:
    bool fDoEscapeMarkup;
    // illegal
    SkXMLWriter& operator=(const SkXMLWriter&);
};

class SkXMLStreamWriter : public SkXMLWriter {
public:
    SkXMLStreamWriter(SkWStream*);
    virtual ~SkXMLStreamWriter();
    virtual void    writeHeader();
    SkDEBUGCODE(static void UnitTest();)
protected:
    virtual void onStartElementLen(const char elem[], size_t length);
    virtual void onEndElement();
    virtual void onAddAttributeLen(const char name[], const char value[], size_t length);
private:
    SkWStream&      fStream;
};

class SkXMLParserWriter : public SkXMLWriter {
public:
    SkXMLParserWriter(SkXMLParser*);
    virtual ~SkXMLParserWriter();
protected:
    virtual void onStartElementLen(const char elem[], size_t length);
    virtual void onEndElement();
    virtual void onAddAttributeLen(const char name[], const char value[], size_t length);
private:
    SkXMLParser&        fParser;
};


#endif

