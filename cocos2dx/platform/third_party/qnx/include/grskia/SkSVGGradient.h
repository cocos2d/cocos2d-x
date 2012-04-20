/* libs/graphics/svg/SkSVGGradient.h
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

#ifndef SkSVGGradient_DEFINED
#define SkSVGGradient_DEFINED

#include "SkSVGElements.h"

class SkSVGGradient : public SkSVGElement {
public:
    SkSVGGradient();
    virtual SkSVGElement* getGradient();
    virtual bool isDef();
    virtual bool isNotDef();
    virtual void write(SkSVGParser& , SkString& color);
protected:
    void translate(SkSVGParser& , bool defState);
    void translateGradientUnits(SkString& units);
private:
    typedef SkSVGElement INHERITED;
};

#endif // SkSVGGradient_DEFINED
