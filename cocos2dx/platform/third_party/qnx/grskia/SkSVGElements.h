/* libs/graphics/svg/SkSVGElements.h
**
** Copyright 2006, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License"); 
** you may not use this file except in compliance with the License. 
** You may obtain a copy of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** Unless required by applicable law or agreed to in writing, software 
** distributed under the License is distributed on an "AS IS" BASIS, 
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
** See the License for the specific language governing permissions and 
** limitations under the License.
*/

#ifndef SkSVGElements_DEFINED
#define SkSVGElements_DEFINED

#include "SkSVGPaintState.h"
#include "SkSVGTypes.h"
#include "SkTDArray.h"

class SkSVGParser;

#define DECLARE_SVG_INFO(_type) \
public: \
    virtual ~SkSVG##_type(); \
    static const SkSVGAttribute gAttributes[]; \
    virtual int getAttributes(const SkSVGAttribute** attrPtr); \
    virtual SkSVGTypes getType() const; \
    virtual void translate(SkSVGParser& parser, bool defState); \
    typedef SkSVG##_type BASE_CLASS

#define DEFINE_SVG_INFO(_type) \
    SkSVG##_type::~SkSVG##_type() {} \
    int SkSVG##_type::getAttributes(const SkSVGAttribute** attrPtr) { \
        *attrPtr = gAttributes; \
        return SK_ARRAY_COUNT(gAttributes); \
    } \
    SkSVGTypes SkSVG##_type::getType() const { return SkSVGType_##_type; }

#define DEFINE_SVG_NO_INFO(_type) \
    SkSVG##_type::~SkSVG##_type() {} \
    int SkSVG##_type::getAttributes(const SkSVGAttribute** ) { return 0; } \
    SkSVGTypes SkSVG##_type::getType() const { return SkSVGType_##_type; }


struct SkSVGTypeName {
    const char* fName;
    SkSVGTypes fType;
};

class SkSVGElement : public SkSVGBase {
public:
    SkSVGElement();
    virtual ~SkSVGElement();
    virtual SkSVGElement* getGradient();
    virtual SkSVGTypes getType() const  = 0;
    virtual bool isDef();
    virtual bool isFlushable();
    virtual bool isGroup();
    virtual bool isNotDef();
    virtual bool onEndElement(SkSVGParser& parser);
    virtual bool onStartElement(SkSVGElement* child);
    void setIsDef();
//  void setIsNotDef();
    virtual void translate(SkSVGParser& parser, bool defState);
    virtual void write(SkSVGParser& , SkString& color);
    SkString f_id;
    SkSVGPaint fPaintState;
    SkTDArray<SkSVGElement*> fChildren;
    SkSVGElement* fParent;
    bool fIsDef;
    bool fIsNotDef;
private:
    bool isGroupParent();
};

#endif // SkSVGElements_DEFINED
