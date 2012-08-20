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

#ifndef SkDOM_DEFINED
#define SkDOM_DEFINED

#include "SkChunkAlloc.h"
#include "SkMath.h"
#include "SkScalar.h"
#include "SkTemplates.h"

struct SkDOMNode;
struct SkDOMAttr;

class SkDOM {
public:
    SkDOM();
    ~SkDOM();

    typedef SkDOMNode Node;
    typedef SkDOMAttr Attr;

    /** Returns null on failure
    */
    const Node* build(const char doc[], size_t len);
    const Node* copy(const SkDOM& dom, const Node* node);

    const Node* getRootNode() const;

    enum Type {
        kElement_Type,
        kText_Type
    };
    Type    getType(const Node*) const;

    const char* getName(const Node*) const;
    const Node* getFirstChild(const Node*, const char elem[] = NULL) const;
    const Node* getNextSibling(const Node*, const char elem[] = NULL) const;

    const char* findAttr(const Node*, const char attrName[]) const;
    const Attr* getFirstAttr(const Node*) const;
    const Attr* getNextAttr(const Node*, const Attr*) const;
    const char* getAttrName(const Node*, const Attr*) const;
    const char* getAttrValue(const Node*, const Attr*) const;
    
    // helpers for walking children
    int countChildren(const Node* node, const char elem[] = NULL) const;

    // helpers for calling SkParse
    bool findS32(const Node*, const char name[], int32_t* value) const;
    bool findScalars(const Node*, const char name[], SkScalar value[], int count) const;
    bool findHex(const Node*, const char name[], uint32_t* value) const;
    bool findBool(const Node*, const char name[], bool*) const;
    int  findList(const Node*, const char name[], const char list[]) const;

    bool findScalar(const Node* node, const char name[], SkScalar value[]) const
    {
        return this->findScalars(node, name, value, 1);
    }

    bool hasAttr(const Node*, const char name[], const char value[]) const;
    bool hasS32(const Node*, const char name[], int32_t value) const;
    bool hasScalar(const Node*, const char name[], SkScalar value) const;
    bool hasHex(const Node*, const char name[], uint32_t value) const;
    bool hasBool(const Node*, const char name[], bool value) const;

    class AttrIter {
    public:
        AttrIter(const class SkDOM&, const Node*);
        const char* next(const char** value);
    private:
        const Attr* fAttr;
        const Attr* fStop;
    };

    SkDEBUGCODE(void dump(const Node* node = NULL, int tabLevel = 0) const;)
    SkDEBUGCODE(static void UnitTest();)

private:
    SkChunkAlloc    fAlloc;
    Node*           fRoot;
    friend class AttrIter;
    friend class SkDOMParser;
};

#endif

