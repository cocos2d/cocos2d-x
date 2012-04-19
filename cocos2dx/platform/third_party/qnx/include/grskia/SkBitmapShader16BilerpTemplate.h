/* libs/graphics/sgl/SkBitmapShader16BilerpTemplate.h
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

#include "SkFilterProc.h"

class BILERP_BITMAP16_SHADER_CLASS : public HasSpan16_Sampler_BitmapShader {
public:
    BILERP_BITMAP16_SHADER_CLASS(const SkBitmap& src)
        : HasSpan16_Sampler_BitmapShader(src, true,
                                         SkShader::kClamp_TileMode,
                                         SkShader::kClamp_TileMode)
    {
    }

    virtual void shadeSpan(int x, int y, SkPMColor dstC[], int count)
    {
        SkASSERT(count > 0);
        
        U8CPU alpha = this->getPaintAlpha();

        const SkMatrix& inv = this->getTotalInverse();
        const SkBitmap& srcBitmap = this->getSrcBitmap();
        unsigned        srcMaxX = srcBitmap.width() - 1;
        unsigned        srcMaxY = srcBitmap.height() - 1;
        unsigned        srcRB = srcBitmap.rowBytes();

        BILERP_BITMAP16_SHADER_PREAMBLE(srcBitmap);

        const SkFilterProc* proc_table = SkGetBilinearFilterProcTable();
        const BILERP_BITMAP16_SHADER_TYPE* srcPixels = (const BILERP_BITMAP16_SHADER_TYPE*)srcBitmap.getPixels();

        if (this->getInverseClass() == kPerspective_MatrixClass)
        {
            SkPerspIter   iter(inv, SkIntToScalar(x) + SK_ScalarHalf,
                                    SkIntToScalar(y) + SK_ScalarHalf, count);
            while ((count = iter.next()) != 0)
            {
                const SkFixed* srcXY = iter.getXY();
                while (--count >= 0)
                {
                    SkFixed fx = *srcXY++ - SK_FixedHalf;
                    SkFixed fy = *srcXY++ - SK_FixedHalf;
                    int ix = fx >> 16;
                    int iy = fy >> 16;
                    int x = SkClampMax(ix, srcMaxX);
                    int y = SkClampMax(iy, srcMaxY);

                    const BILERP_BITMAP16_SHADER_TYPE *p00, *p01, *p10, *p11;

                    p00 = p01 = ((const BILERP_BITMAP16_SHADER_TYPE*)((const char*)srcPixels + y * srcRB)) + x;
                    if ((unsigned)ix < srcMaxX)
                        p01 += 1;
                    p10 = p00;
                    p11 = p01;
                    if ((unsigned)iy < srcMaxY)
                    {
                        p10 = (const BILERP_BITMAP16_SHADER_TYPE*)((const char*)p10 + srcRB);
                        p11 = (const BILERP_BITMAP16_SHADER_TYPE*)((const char*)p11 + srcRB);
                    }

                    SkFilterProc proc = SkGetBilinearFilterProc(proc_table, fx, fy);
                    uint32_t c = proc(SkExpand_rgb_16(BILERP_BITMAP16_SHADER_PIXEL(*p00)),
                                      SkExpand_rgb_16(BILERP_BITMAP16_SHADER_PIXEL(*p01)),
                                      SkExpand_rgb_16(BILERP_BITMAP16_SHADER_PIXEL(*p10)),
                                      SkExpand_rgb_16(BILERP_BITMAP16_SHADER_PIXEL(*p11)));

                    *dstC++ = expanded_rgb16_to_8888(c, alpha);
                }
            }
        }
        else    // linear case
        {
            SkFixed fx, fy, dx, dy;

            // now init fx, fy, dx, dy
            {
                SkPoint srcPt;
                this->getInverseMapPtProc()(inv, SkIntToScalar(x) + SK_ScalarHalf,
                                                 SkIntToScalar(y) + SK_ScalarHalf, &srcPt);

                fx = SkScalarToFixed(srcPt.fX) - SK_FixedHalf;
                fy = SkScalarToFixed(srcPt.fY) - SK_FixedHalf;

                if (this->getInverseClass() == kFixedStepInX_MatrixClass)
                    (void)inv.fixedStepInX(SkIntToScalar(y), &dx, &dy);
                else
                {
                    dx = SkScalarToFixed(inv.getScaleX());
                    dy = SkScalarToFixed(inv.getSkewY());
                }
            }

            do {
                int ix = fx >> 16;
                int iy = fy >> 16;

                const BILERP_BITMAP16_SHADER_TYPE *p00, *p01, *p10, *p11;

                p00 = p01 = ((const BILERP_BITMAP16_SHADER_TYPE*)((const char*)srcPixels +
                                                                   SkClampMax(iy, srcMaxY) * srcRB)) +
                                                                   SkClampMax(ix, srcMaxX);
                if ((unsigned)ix < srcMaxX)
                    p01 += 1;
                p10 = p00;
                p11 = p01;
                if ((unsigned)iy < srcMaxY)
                {
                    p10 = (const BILERP_BITMAP16_SHADER_TYPE*)((const char*)p10 + srcRB);
                    p11 = (const BILERP_BITMAP16_SHADER_TYPE*)((const char*)p11 + srcRB);
                }

                SkFilterProc proc = SkGetBilinearFilterProc(proc_table, fx, fy);
                uint32_t c = proc(SkExpand_rgb_16(BILERP_BITMAP16_SHADER_PIXEL(*p00)),
                                  SkExpand_rgb_16(BILERP_BITMAP16_SHADER_PIXEL(*p01)),
                                  SkExpand_rgb_16(BILERP_BITMAP16_SHADER_PIXEL(*p10)),
                                  SkExpand_rgb_16(BILERP_BITMAP16_SHADER_PIXEL(*p11)));
                *dstC++ = expanded_rgb16_to_8888(c, alpha);

                fx += dx;
                fy += dy;
            } while (--count != 0);
        }
        BILERP_BITMAP16_SHADER_POSTAMBLE(srcBitmap);
    }

    virtual void shadeSpan16(int x, int y, uint16_t dstC[], int count)
    {
        SkASSERT(count > 0);

        const SkMatrix& inv = this->getTotalInverse();
        const SkBitmap& srcBitmap = this->getSrcBitmap();
        unsigned        srcMaxX = srcBitmap.width() - 1;
        unsigned        srcMaxY = srcBitmap.height() - 1;
        unsigned        srcRB = srcBitmap.rowBytes();

        BILERP_BITMAP16_SHADER_PREAMBLE(srcBitmap);

        const SkFilterProc* proc_table = SkGetBilinearFilterProcTable();
        const BILERP_BITMAP16_SHADER_TYPE* srcPixels = (const BILERP_BITMAP16_SHADER_TYPE*)srcBitmap.getPixels();

        if (this->getInverseClass() == kPerspective_MatrixClass)
        {
            SkPerspIter   iter(inv, SkIntToScalar(x) + SK_ScalarHalf,
                                    SkIntToScalar(y) + SK_ScalarHalf, count);
            while ((count = iter.next()) != 0)
            {
                const SkFixed* srcXY = iter.getXY();
                while (--count >= 0)
                {
                    SkFixed fx = *srcXY++ - SK_FixedHalf;
                    SkFixed fy = *srcXY++ - SK_FixedHalf;
                    int ix = fx >> 16;
                    int iy = fy >> 16;
                    
                    const BILERP_BITMAP16_SHADER_TYPE *p00, *p01, *p10, *p11;

                    p00 = p01 = ((const BILERP_BITMAP16_SHADER_TYPE*)((const char*)srcPixels +
                                                                      SkClampMax(iy, srcMaxY) * srcRB)) +
                                                                      SkClampMax(ix, srcMaxX);
                    if ((unsigned)ix < srcMaxX)
                        p01 += 1;
                    p10 = p00;
                    p11 = p01;
                    if ((unsigned)iy < srcMaxY)
                    {
                        p10 = (const BILERP_BITMAP16_SHADER_TYPE*)((const char*)p10 + srcRB);
                        p11 = (const BILERP_BITMAP16_SHADER_TYPE*)((const char*)p11 + srcRB);
                    }

                    SkFilterProc proc = SkGetBilinearFilterProc(proc_table, fx, fy);
                    uint32_t c = proc(SkExpand_rgb_16(BILERP_BITMAP16_SHADER_PIXEL(*p00)),
                                      SkExpand_rgb_16(BILERP_BITMAP16_SHADER_PIXEL(*p01)),
                                      SkExpand_rgb_16(BILERP_BITMAP16_SHADER_PIXEL(*p10)),
                                      SkExpand_rgb_16(BILERP_BITMAP16_SHADER_PIXEL(*p11)));
                    *dstC++ = SkCompact_rgb_16(c);
                }
            }
        }
        else    // linear case
        {
            SkFixed fx, fy, dx, dy;

            // now init fx, fy, dx, dy
            {
                SkPoint srcPt;
                this->getInverseMapPtProc()(inv, SkIntToScalar(x) + SK_ScalarHalf,
                                                 SkIntToScalar(y) + SK_ScalarHalf, &srcPt);

                fx = SkScalarToFixed(srcPt.fX) - SK_FixedHalf;
                fy = SkScalarToFixed(srcPt.fY) - SK_FixedHalf;

                if (this->getInverseClass() == kFixedStepInX_MatrixClass)
                    (void)inv.fixedStepInX(SkIntToScalar(y), &dx, &dy);
                else
                {
                    dx = SkScalarToFixed(inv.getScaleX());
                    dy = SkScalarToFixed(inv.getSkewY());
                }
            }

            do {
                int ix = fx >> 16;
                int iy = fy >> 16;
                
                const BILERP_BITMAP16_SHADER_TYPE *p00, *p01, *p10, *p11;

                p00 = p01 = ((const BILERP_BITMAP16_SHADER_TYPE*)((const char*)srcPixels +
                                                                  SkClampMax(iy, srcMaxY) * srcRB)) +
                                                                  SkClampMax(ix, srcMaxX);
                if ((unsigned)ix < srcMaxX)
                    p01 += 1;
                p10 = p00;
                p11 = p01;
                if ((unsigned)iy < srcMaxY)
                {
                    p10 = (const BILERP_BITMAP16_SHADER_TYPE*)((const char*)p10 + srcRB);
                    p11 = (const BILERP_BITMAP16_SHADER_TYPE*)((const char*)p11 + srcRB);
                }

                SkFilterProc proc = SkGetBilinearFilterProc(proc_table, fx, fy);
                uint32_t c = proc(SkExpand_rgb_16(BILERP_BITMAP16_SHADER_PIXEL(*p00)),
                                  SkExpand_rgb_16(BILERP_BITMAP16_SHADER_PIXEL(*p01)),
                                  SkExpand_rgb_16(BILERP_BITMAP16_SHADER_PIXEL(*p10)),
                                  SkExpand_rgb_16(BILERP_BITMAP16_SHADER_PIXEL(*p11)));
                *dstC++ = SkCompact_rgb_16(c);

                fx += dx;
                fy += dy;
            } while (--count != 0);
        }
        BILERP_BITMAP16_SHADER_POSTAMBLE(srcBitmap);
    }
};

#undef BILERP_BITMAP16_SHADER_CLASS
#undef BILERP_BITMAP16_SHADER_TYPE
#undef BILERP_BITMAP16_SHADER_PREAMBLE
#undef BILERP_BITMAP16_SHADER_PIXEL
#undef BILERP_BITMAP16_SHADER_POSTAMBLE
