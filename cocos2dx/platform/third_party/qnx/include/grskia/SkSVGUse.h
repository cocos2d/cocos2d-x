/* libs/graphics/svg/SkSVGUse.h
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

#ifndef SkSVGUse_DEFINED
#define SkSVGUse_DEFINED

#include "SkSVGElements.h"

class SkSVGUse : public SkSVGElement {
    DECLARE_SVG_INFO(Use);
protected:
    SkString f_height;
    SkString f_width;
    SkString f_x;
    SkString f_xlink_href;
    SkString f_y;
private:
    typedef SkSVGElement INHERITED;
    friend class SkSVGClipPath;
};

#endif // SkSVGUse_DEFINED
