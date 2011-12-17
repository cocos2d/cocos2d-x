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

#ifndef SkSVGBase_DEFINED
#define SkSVGBase_DEFINED

#include "SkSVGAttribute.h"

class SkSVGParser;

class SkSVGBase {
public:
    virtual ~SkSVGBase();
    virtual void addAttribute(SkSVGParser& parser, int attrIndex, 
        const char* attrValue, size_t attrLength);
    virtual int getAttributes(const SkSVGAttribute** attrPtr) = 0;
};

#endif // SkSVGBase_DEFINEDes(const SkSVGAttribute** attrPtr) = 0;

