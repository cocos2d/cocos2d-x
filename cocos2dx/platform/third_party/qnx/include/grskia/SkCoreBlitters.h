/* libs/graphics/sgl/SkCoreBlitters.h
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

#ifndef SkCoreBlitters_DEFINED
#define SkCoreBlitters_DEFINED

#include "SkBlitter.h"
#include "SkBlitRow.h"

class SkRasterBlitter : public SkBlitter {
public:
    SkRasterBlitter(const SkBitmap& device) : fDevice(device) {}

protected:
    const SkBitmap& fDevice;

private:
    typedef SkBlitter INHERITED;
};

class SkShaderBlitter : public SkRasterBlitter {
public:
    SkShaderBlitter(const SkBitmap& device, const SkPaint& paint);
    virtual ~SkShaderBlitter();

protected:
    uint32_t    fShaderFlags;
    SkShader*   fShader;

private:
    // illegal
    SkShaderBlitter& operator=(const SkShaderBlitter&);

    typedef SkRasterBlitter INHERITED;
};

///////////////////////////////////////////////////////////////////////////////

class SkA8_Blitter : public SkRasterBlitter {
public:
    SkA8_Blitter(const SkBitmap& device, const SkPaint& paint);
    virtual void blitH(int x, int y, int width);
    virtual void blitAntiH(int x, int y, const SkAlpha antialias[], const int16_t runs[]);
    virtual void blitV(int x, int y, int height, SkAlpha alpha);
    virtual void blitRect(int x, int y, int width, int height);
    virtual void blitMask(const SkMask&, const SkIRect&);
    virtual const SkBitmap* justAnOpaqueColor(uint32_t*);

private:
    unsigned fSrcA;

    // illegal
    SkA8_Blitter& operator=(const SkA8_Blitter&);

    typedef SkRasterBlitter INHERITED;
};

class SkA8_Shader_Blitter : public SkShaderBlitter {
public:
    SkA8_Shader_Blitter(const SkBitmap& device, const SkPaint& paint);
    virtual ~SkA8_Shader_Blitter();
    virtual void blitH(int x, int y, int width);
    virtual void blitAntiH(int x, int y, const SkAlpha antialias[], const int16_t runs[]);
    virtual void blitMask(const SkMask&, const SkIRect&);

private:
    SkXfermode* fXfermode;
    SkPMColor*  fBuffer;
    uint8_t*    fAAExpand;

    // illegal
    SkA8_Shader_Blitter& operator=(const SkA8_Shader_Blitter&);

    typedef SkShaderBlitter INHERITED;
};

////////////////////////////////////////////////////////////////

class SkARGB32_Blitter : public SkRasterBlitter {
public:
    SkARGB32_Blitter(const SkBitmap& device, const SkPaint& paint);
    virtual void blitH(int x, int y, int width);
    virtual void blitAntiH(int x, int y, const SkAlpha antialias[], const int16_t runs[]);
    virtual void blitV(int x, int y, int height, SkAlpha alpha);
    virtual void blitRect(int x, int y, int width, int height);
    virtual void blitMask(const SkMask&, const SkIRect&);
    virtual const SkBitmap* justAnOpaqueColor(uint32_t*);

protected:
    SkColor                fColor;
    SkPMColor              fPMColor;
    SkBlitRow::ColorProc   fColor32Proc;
    SkBlitMask::Proc       fBlitMaskProc;

private:
    unsigned fSrcA, fSrcR, fSrcG, fSrcB;

    // illegal
    SkARGB32_Blitter& operator=(const SkARGB32_Blitter&);

    typedef SkRasterBlitter INHERITED;
};

class SkARGB32_Opaque_Blitter : public SkARGB32_Blitter {
public:
    SkARGB32_Opaque_Blitter(const SkBitmap& device, const SkPaint& paint)
        : INHERITED(device, paint) { SkASSERT(paint.getAlpha() == 0xFF); }
    virtual void blitMask(const SkMask&, const SkIRect&);

private:
    typedef SkARGB32_Blitter INHERITED;
};

class SkARGB32_Black_Blitter : public SkARGB32_Opaque_Blitter {
public:
    SkARGB32_Black_Blitter(const SkBitmap& device, const SkPaint& paint)
        : INHERITED(device, paint) {}
    virtual void blitMask(const SkMask&, const SkIRect&);
    virtual void blitAntiH(int x, int y, const SkAlpha antialias[], const int16_t runs[]);

private:
    typedef SkARGB32_Opaque_Blitter INHERITED;
};

class SkARGB32_Shader_Blitter : public SkShaderBlitter {
public:
    SkARGB32_Shader_Blitter(const SkBitmap& device, const SkPaint& paint);
    virtual ~SkARGB32_Shader_Blitter();
    virtual void blitH(int x, int y, int width);
    virtual void blitAntiH(int x, int y, const SkAlpha antialias[], const int16_t runs[]);

private:
    SkXfermode*         fXfermode;
    SkPMColor*          fBuffer;
    SkBlitRow::Proc32   fProc32;
    SkBlitRow::Proc32   fProc32Blend;

    // illegal
    SkARGB32_Shader_Blitter& operator=(const SkARGB32_Shader_Blitter&);

    typedef SkShaderBlitter INHERITED;
};

///////////////////////////////////////////////////////////////////////////////

class SkA1_Blitter : public SkRasterBlitter {
public:
    SkA1_Blitter(const SkBitmap& device, const SkPaint& paint);
    virtual void blitH(int x, int y, int width);

private:
    uint8_t fSrcA;

    // illegal
    SkA1_Blitter& operator=(const SkA1_Blitter&);

    typedef SkRasterBlitter INHERITED;
};

///////////////////////////////////////////////////////////////////////////////

/*  These return the correct subclass of blitter for their device config.

    Currently, they make the following assumptions about the state of the
    paint:

    1. If there is an xfermode, there will also be a shader
    2. If there is a colorfilter, there will be a shader that itself handles
       calling the filter, so the blitter can always ignore the colorfilter obj

    These pre-conditions must be handled by the caller, in our case
    SkBlitter::Choose(...)
 */

extern SkBlitter* SkBlitter_ChooseD4444(const SkBitmap& device,
                                        const SkPaint& paint,
                                        void* storage, size_t storageSize);

extern SkBlitter* SkBlitter_ChooseD565(const SkBitmap& device,
                                       const SkPaint& paint,
                                       void* storage, size_t storageSize);

#endif

