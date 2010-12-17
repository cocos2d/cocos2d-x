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

#ifndef SkTransparentShader_DEFINED
#define SkTransparentShader_DEFINED

#include "SkShader.h"

class SkTransparentShader : public SkShader {
public:
    SkTransparentShader() {}
    virtual uint32_t getFlags();
    virtual bool    setContext( const SkBitmap& device,
                                const SkPaint& paint,
                                const SkMatrix& matrix);
    virtual void    shadeSpan(int x, int y, SkPMColor[], int count);
    virtual void    shadeSpan16(int x, int y, uint16_t span[], int count);

    // overrides for SkFlattenable
    virtual Factory getFactory() { return Create; }
    virtual void flatten(SkFlattenableWriteBuffer& buffer)
    {
        this->INHERITED::flatten(buffer);
    }
        
private:
    // these are a cache from the call to setContext()
    const SkBitmap* fDevice;
    uint8_t         fAlpha;

    SkTransparentShader(SkFlattenableReadBuffer& buffer) : INHERITED(buffer) {}
    
    static SkFlattenable* Create(SkFlattenableReadBuffer& buffer)
    {
        return SkNEW_ARGS(SkTransparentShader, (buffer));
    }

    typedef SkShader INHERITED;
};

#endif

