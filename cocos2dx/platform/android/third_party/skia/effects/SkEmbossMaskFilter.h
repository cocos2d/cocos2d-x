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

#ifndef SkEmbossMaskFilter_DEFINED
#define SkEmbossMaskFilter_DEFINED

#include "SkMaskFilter.h"

/** \class SkEmbossMaskFilter

    This mask filter creates a 3D emboss look, by specifying a light and blur amount.
*/
class SkEmbossMaskFilter : public SkMaskFilter {
public:
    struct Light {
        SkScalar    fDirection[3];  // x,y,z
        uint16_t    fPad;
        uint8_t     fAmbient;
        uint8_t     fSpecular;      // exponent, 4.4 right now
    };

    SkEmbossMaskFilter(const Light& light, SkScalar blurRadius);

    // overrides from SkMaskFilter
    //  This method is not exported to java.
    virtual SkMask::Format getFormat();
    //  This method is not exported to java.
    virtual bool filterMask(SkMask* dst, const SkMask& src, const SkMatrix& matrix, SkIPoint* margin);

    // overrides from SkFlattenable

    //  This method is not exported to java.
    virtual Factory getFactory();
    //  This method is not exported to java.
    virtual void flatten(SkFlattenableWriteBuffer&);

protected:
    SkEmbossMaskFilter(SkFlattenableReadBuffer&);

private:
    Light       fLight;
    SkScalar    fBlurRadius;

    static SkFlattenable* CreateProc(SkFlattenableReadBuffer&);
    
    typedef SkMaskFilter INHERITED;
};

#endif

