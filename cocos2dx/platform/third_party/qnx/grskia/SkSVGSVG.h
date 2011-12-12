/* libs/graphics/svg/SkSVGSVG.h
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

#ifndef SkSVGSVG_DEFINED
#define SkSVGSVG_DEFINED

#include "SkSVGElements.h"

class SkSVGSVG : public SkSVGElement {
    DECLARE_SVG_INFO(SVG);
    virtual bool isFlushable();
private:
    SkString f_enable_background;
    SkString f_height;
    SkString f_overflow;
    SkString f_width;
    SkString f_version;
    SkString f_viewBox;
	SkString f_x;
    SkString f_xml_space;
    SkString f_xmlns;
    SkString f_xml_xlink;
	SkString f_y;

    typedef SkSVGElement INHERITED;
};

#endif // SkSVGSVG_DEFINED
