/* libs/graphics/sgl/SkBitmapShader.h
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

#ifndef SkBitmapProcShader_DEFINED
#define SkBitmapProcShader_DEFINED

#include "SkShader.h"
#include "SkBitmapProcState.h"

class SkBitmapProcShader : public SkShader {
public:
    SkBitmapProcShader(const SkBitmap& src, TileMode tx, TileMode ty);

    // overrides from SkShader
    virtual bool setContext(const SkBitmap&, const SkPaint&, const SkMatrix&);
    virtual uint32_t getFlags() { return fFlags; }
    virtual void shadeSpan(int x, int y, SkPMColor dstC[], int count);
    virtual void shadeSpan16(int x, int y, uint16_t dstC[], int count);
    virtual void beginSession();
    virtual void endSession();
    virtual BitmapType asABitmap(SkBitmap*, SkMatrix*, TileMode*,
                                 SkScalar* twoPointRadialParams) const;

    static bool CanDo(const SkBitmap&, TileMode tx, TileMode ty);

    static SkFlattenable* CreateProc(SkFlattenableReadBuffer& buffer) {
        return SkNEW_ARGS(SkBitmapProcShader, (buffer));
    }

    // override from flattenable
    virtual bool toDumpString(SkString* str) const;

protected:
    SkBitmapProcShader(SkFlattenableReadBuffer& );
    virtual void flatten(SkFlattenableWriteBuffer& );
    virtual Factory getFactory() { return CreateProc; }

    SkBitmap          fRawBitmap;   // experimental for RLE encoding
    SkBitmapProcState fState;
    uint32_t          fFlags;

private:
    typedef SkShader INHERITED;
};

#endif
