/*
** Copyright 2007, The Android Open Source Project
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

#ifndef SkBitmapProcState_DEFINED
#define SkBitmapProcState_DEFINED

#include "SkBitmap.h"
#include "SkMatrix.h"

class SkPaint;

struct SkBitmapProcState {

    typedef void (*ShaderProc32)(const SkBitmapProcState&, int x, int y,
                                 SkPMColor[], int count);

    typedef void (*ShaderProc16)(const SkBitmapProcState&, int x, int y,
                                 uint16_t[], int count);

    typedef void (*MatrixProc)(const SkBitmapProcState&,
                               uint32_t bitmapXY[],
                               int count,
                               int x, int y);
    
    typedef void (*SampleProc32)(const SkBitmapProcState&,
                                 const uint32_t[],
                                 int count,
                                 SkPMColor colors[]);

    typedef void (*SampleProc16)(const SkBitmapProcState&,
                                 const uint32_t[],
                                 int count,
                                 uint16_t colors[]);
    
    typedef U16CPU (*FixedTileProc)(SkFixed);   // returns 0..0xFFFF
    typedef U16CPU (*IntTileProc)(int value, int count);   // returns 0..count-1

    // If a shader proc is present, then the corresponding matrix/sample procs
    // are ignored
    ShaderProc32        fShaderProc32;      // chooseProcs
    ShaderProc16        fShaderProc16;      // chooseProcs
    // These are used if the shaderproc is NULL
    MatrixProc          fMatrixProc;        // chooseProcs
    SampleProc32        fSampleProc32;      // chooseProcs
    SampleProc16        fSampleProc16;      // chooseProcs

    const SkBitmap*     fBitmap;            // chooseProcs - orig or mip
    const SkMatrix*     fInvMatrix;         // chooseProcs
    SkMatrix::MapXYProc fInvProc;           // chooseProcs

    FixedTileProc       fTileProcX;         // chooseProcs
    FixedTileProc       fTileProcY;         // chooseProcs
    IntTileProc         fIntTileProcY;      // chooseProcs
    SkFixed             fFilterOneX;
    SkFixed             fFilterOneY;

    SkPMColor           fPaintPMColor;      // chooseProcs - A8 config
    SkFixed             fInvSx;             // chooseProcs
    SkFixed             fInvKy;             // chooseProcs
    uint16_t            fAlphaScale;        // chooseProcs
    uint8_t             fInvType;           // chooseProcs
    uint8_t             fTileModeX;         // CONSTRUCTOR
    uint8_t             fTileModeY;         // CONSTRUCTOR
    SkBool8             fDoFilter;          // chooseProcs

    /** Platforms implement this, and can optionally overwrite only the
        following fields:

        fShaderProc32
        fShaderProc16
        fMatrixProc
        fSampleProc32
        fSampleProc32

        They will already have valid function pointers, so a platform that does
        not have an accelerated version can just leave that field as is. A valid
        implementation can do nothing (see SkBitmapProcState_opts_none.cpp)
     */
    void platformProcs();

    /** Given the byte size of the index buffer to be passed to the matrix proc,
        return the maximum number of resulting pixels that can be computed
        (i.e. the number of SkPMColor values to be written by the sample proc).
        This routine takes into account that filtering and scale-vs-affine
        affect the amount of buffer space needed.
     
        Only valid to call after chooseProcs (setContext) has been called. It is
        safe to call this inside the shader's shadeSpan() method.
     */
    int maxCountForBufferSize(size_t bufferSize) const;

private:
    friend class SkBitmapProcShader;

    SkMatrix            fUnitInvMatrix;     // chooseProcs
    SkBitmap            fOrigBitmap;        // CONSTRUCTOR
    SkBitmap            fMipBitmap;

    MatrixProc chooseMatrixProc(bool trivial_matrix);
    bool chooseProcs(const SkMatrix& inv, const SkPaint&);
};

/*  Macros for packing and unpacking pairs of 16bit values in a 32bit uint.
    Used to allow access to a stream of uint16_t either one at a time, or
    2 at a time by unpacking a uint32_t
 */
#ifdef SK_CPU_BENDIAN
    #define PACK_TWO_SHORTS(pri, sec) ((pri) << 16 | (sec))
    #define UNPACK_PRIMARY_SHORT(packed)    ((uint32_t)(packed) >> 16)
    #define UNPACK_SECONDARY_SHORT(packed)  ((packed) & 0xFFFF)
#else
    #define PACK_TWO_SHORTS(pri, sec) ((pri) | ((sec) << 16))
    #define UNPACK_PRIMARY_SHORT(packed)    ((packed) & 0xFFFF)
    #define UNPACK_SECONDARY_SHORT(packed)  ((uint32_t)(packed) >> 16)
#endif

#ifdef SK_DEBUG
    static inline uint32_t pack_two_shorts(U16CPU pri, U16CPU sec) {
        SkASSERT((uint16_t)pri == pri);
        SkASSERT((uint16_t)sec == sec);
        return PACK_TWO_SHORTS(pri, sec);
    }
#else
    #define pack_two_shorts(pri, sec)   PACK_TWO_SHORTS(pri, sec)
#endif

// These functions are generated via macros, but are exposed here so that
// platformProcs may test for them by name.
void S32_opaque_D32_filter_DX(const SkBitmapProcState& s, const uint32_t xy[],
                              int count, SkPMColor colors[]);
void S32_alpha_D32_filter_DX(const SkBitmapProcState& s, const uint32_t xy[],
                             int count, SkPMColor colors[]);

#endif
