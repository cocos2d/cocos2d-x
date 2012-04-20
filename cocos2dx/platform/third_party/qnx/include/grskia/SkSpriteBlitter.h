/* libs/graphics/sgl/SkSpriteBlitter.h
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

#ifndef SkSpriteBlitter_DEFINED
#define SkSpriteBlitter_DEFINED

#include "SkBlitter.h"
#include "SkBitmap.h"

class SkPaint;

class SkSpriteBlitter : public SkBlitter {
public:
            SkSpriteBlitter(const SkBitmap& source);
    virtual ~SkSpriteBlitter();

    virtual void setup(const SkBitmap& device, int left, int top,
                       const SkPaint& paint);

    // overrides
#ifdef SK_DEBUG
    virtual void    blitH(int x, int y, int width);
    virtual void    blitAntiH(int x, int y, const SkAlpha antialias[], const int16_t runs[]);
    virtual void    blitV(int x, int y, int height, SkAlpha alpha);
    virtual void    blitMask(const SkMask&, const SkIRect& clip);
#endif

    static SkSpriteBlitter* ChooseD16(const SkBitmap& source, const SkPaint&,
                                      void* storage, size_t storageSize);
    static SkSpriteBlitter* ChooseD32(const SkBitmap& source, const SkPaint&,
                                      void* storage, size_t storageSize);

protected:
    const SkBitmap* fDevice;
    const SkBitmap* fSource;
    int             fLeft, fTop;
    const SkPaint*  fPaint;
};

#endif

