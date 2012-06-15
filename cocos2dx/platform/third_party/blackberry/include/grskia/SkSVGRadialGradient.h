/* libs/graphics/svg/SkSVGRadialGradient.h
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

#ifndef SkSVGRadialGradient_DEFINED
#define SkSVGRadialGradient_DEFINED

#include "SkSVGGradient.h"

class SkSVGRadialGradient : public SkSVGGradient {
    DECLARE_SVG_INFO(RadialGradient);
protected:
    SkString f_cx;
    SkString f_cy;
    SkString f_fx;
    SkString f_fy;
    SkString f_gradientTransform;
    SkString f_gradientUnits;
    SkString f_r;
    SkString fMatrixID;
private:
    typedef SkSVGGradient INHERITED;
};

#endif // SkSVGRadialGradient_DEFINED
