/* libs/graphics/svg/SkSVGDefs.h
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

#ifndef SkSVGDefs_DEFINED
#define SkSVGDefs_DEFINED

#include "SkSVGGroup.h"

class SkSVGDefs : public SkSVGGroup {
    DECLARE_SVG_INFO(Defs);
    virtual bool isDef();
    virtual bool isNotDef();
private:
    typedef SkSVGGroup INHERITED;
};

#endif // SkSVGDefs_DEFINED
