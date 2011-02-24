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

#ifndef SkBML_WXMLParser_DEFINED
#define SkBML_WXMLParser_DEFINED

#include "SkString.h"
#include "SkXMLParser.h"

class SkStream;
class SkWStream;

class BML_WXMLParser : public SkXMLParser {
public:
    BML_WXMLParser(SkWStream& writer);
    virtual ~BML_WXMLParser();
    static void Write(SkStream& s, const char filename[]);
  
  /** @cond UNIT_TEST */
  SkDEBUGCODE(static void UnitTest();)
  /** @endcond */  
private:
    virtual bool onAddAttribute(const char name[], const char value[]);
    virtual bool onEndElement(const char name[]);
    virtual bool onStartElement(const char name[]);
    BML_WXMLParser& operator=(const BML_WXMLParser& src);
#ifdef SK_DEBUG
    int fElemsCount, fElemsReused;
    int fAttrsCount, fNamesReused, fValuesReused;
#endif
    SkWStream&  fWriter;
    char*       fElems[256];
    char*       fAttrNames[256];
    char*       fAttrValues[256];

    // important that these are U8, so we get automatic wrap-around
    U8  fNextElem, fNextAttrName, fNextAttrValue;
};

#endif // SkBML_WXMLParser_DEFINED

