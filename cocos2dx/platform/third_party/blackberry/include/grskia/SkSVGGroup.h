/* libs/graphics/svg/SkSVGGroup.h
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

#ifndef SkSVGGroup_DEFINED
#define SkSVGGroup_DEFINED

#include "SkSVGElements.h"

class SkSVGGroup : public SkSVGElement {
public:
    SkSVGGroup();
    virtual SkSVGElement* getGradient();
    virtual bool isDef();
    virtual bool isFlushable();
    virtual bool isGroup();
    virtual bool isNotDef();
    void translate(SkSVGParser& , bool defState);
private:
    typedef SkSVGElement INHERITED;
};

#endif // SkSVGGroup_DEFINED
