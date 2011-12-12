/* libs/graphics/svg/SkSVGLine.h
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

#ifndef SkSVGLine_DEFINED
#define SkSVGLine_DEFINED

#include "SkSVGElements.h"

class SkSVGLine : public SkSVGElement {
    DECLARE_SVG_INFO(Line);
private:
    SkString f_x1;
    SkString f_x2;
    SkString f_y1;
    SkString f_y2;
    typedef SkSVGElement INHERITED;
};

#endif // SkSVGLine_DEFINED
