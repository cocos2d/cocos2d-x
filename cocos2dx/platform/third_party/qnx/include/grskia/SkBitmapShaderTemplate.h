/* libs/graphics/sgl/SkBitmapShaderTemplate.h
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


#ifndef NOFILTER_BITMAP_SHADER_PREAMBLE
    #define NOFILTER_BITMAP_SHADER_PREAMBLE(bitmap, rb)
#endif
#ifndef NOFILTER_BITMAP_SHADER_POSTAMBLE
    #define NOFILTER_BITMAP_SHADER_POSTAMBLE(bitmap)
#endif
#ifndef NOFILTER_BITMAP_SHADER_PREAMBLE16
    #define NOFILTER_BITMAP_SHADER_PREAMBLE16(bitmap, rb)
#endif
#ifndef NOFILTER_BITMAP_SHADER_POSTAMBLE16
    #define NOFILTER_BITMAP_SHADER_POSTAMBLE16(bitmap)
#endif

class NOFILTER_BITMAP_SHADER_CLASS : public HasSpan16_Sampler_BitmapShader {
public:
    NOFILTER_BITMAP_SHADER_CLASS(const SkBitmap& src)
        : HasSpan16_Sampler_BitmapShader(src, false,
                                         NOFILTER_BITMAP_SHADER_TILEMODE,
                                         NOFILTER_BITMAP_SHADER_TILEMODE)
    {
    }
    
    virtual bool setContext(const SkBitmap& device, const SkPaint& paint, const SkMatrix& matrix)
    {
        if (!this->INHERITED::setContext(device, paint, matrix))
            return false;

#ifdef NOFILTER_BITMAP_SHADER_USE_UNITINVERSE
        this->computeUnitInverse();
#endif
        return true;
    }

    virtual void shadeSpan(int x, int y, SkPMColor dstC[], int count)
    {
        SkASSERT(count > 0);

#ifdef NOFILTER_BITMAP_SHADER_SPRITEPROC32
        if ((this->getTotalInverse().getType() & ~SkMatrix::kTranslate_Mask) == 0)
        {
            NOFILTER_BITMAP_SHADER_SPRITEPROC32(this, x, y, dstC, count);
            return;
        }
#endif

        unsigned        scale = SkAlpha255To256(this->getPaintAlpha());
#ifdef NOFILTER_BITMAP_SHADER_USE_UNITINVERSE
        const SkMatrix& inv = this->getUnitInverse();
        SkMatrix::MapPtProc invProc = this->getUnitInverseProc();
#else
        const SkMatrix& inv = this->getTotalInverse();
        SkMatrix::MapPtProc invProc = this->getInverseMapPtProc();
#endif
        const SkBitmap& srcBitmap = this->getSrcBitmap();
        unsigned        srcMaxX = srcBitmap.width() - 1;
        unsigned        srcMaxY = srcBitmap.height() - 1;
        unsigned        srcRB = srcBitmap.rowBytes();
        SkFixed         fx, fy, dx, dy;

        const NOFILTER_BITMAP_SHADER_TYPE* srcPixels = (const NOFILTER_BITMAP_SHADER_TYPE*)srcBitmap.getPixels();
        NOFILTER_BITMAP_SHADER_PREAMBLE(srcBitmap, srcRB);

        if (this->getInverseClass() == kPerspective_MatrixClass)
        {
            SkPerspIter   iter(inv, SkIntToScalar(x) + SK_ScalarHalf,
                                    SkIntToScalar(y) + SK_ScalarHalf, count);
            while ((count = iter.next()) != 0)
            {
                const SkFixed* srcXY = iter.getXY();

/*  Do I need this?
#ifndef NOFILTER_BITMAP_SHADER_USE_UNITINVERSE
            fx >>= level;
            fy >>= level;
#endif
*/
                if (256 == scale)
                {
                    while (--count >= 0)
                    {
                        fx = *srcXY++;
                        fy = *srcXY++;
                        unsigned x = NOFILTER_BITMAP_SHADER_TILEPROC(fx, srcMaxX);
                        unsigned y = NOFILTER_BITMAP_SHADER_TILEPROC(fy, srcMaxY);
                        *dstC++ = NOFILTER_BITMAP_SHADER_SAMPLE_XY(srcPixels, x, y, srcRB);
                    }
                }
                else
                {
                    while (--count >= 0)
                    {
                        fx = *srcXY++;
                        fy = *srcXY++;
                        unsigned x = NOFILTER_BITMAP_SHADER_TILEPROC(fx, srcMaxX);
                        unsigned y = NOFILTER_BITMAP_SHADER_TILEPROC(fy, srcMaxY);
                        uint32_t c = NOFILTER_BITMAP_SHADER_SAMPLE_XY(srcPixels, x, y, srcRB);
                        *dstC++ = SkAlphaMulQ(c, scale);
                    }
                }
            }
            return;
        }

        // now init fx, fy, dx, dy
        {
            SkPoint srcPt;
            invProc(inv, SkIntToScalar(x) + SK_ScalarHalf,
                         SkIntToScalar(y) + SK_ScalarHalf, &srcPt);

            fx = SkScalarToFixed(srcPt.fX);
            fy = SkScalarToFixed(srcPt.fY);

            if (this->getInverseClass() == kFixedStepInX_MatrixClass)
                (void)inv.fixedStepInX(SkIntToScalar(y), &dx, &dy);
            else
            {
                dx = SkScalarToFixed(inv.getScaleX());
                dy = SkScalarToFixed(inv.getSkewY());
            }
        }

#ifndef NOFILTER_BITMAP_SHADER_USE_UNITINVERSE
        {   int level = this->getMipLevel() >> 16;
            fx >>= level;
            fy >>= level;
            dx >>= level;
            dy >>= level;
        }
#endif

        if (dy == 0)
        {
            int y_index = NOFILTER_BITMAP_SHADER_TILEPROC(fy, srcMaxY);
//          SkDEBUGF(("fy = %g, srcMaxY = %d, y_index = %d\n", SkFixedToFloat(fy), srcMaxY, y_index));
            srcPixels = (const NOFILTER_BITMAP_SHADER_TYPE*)((const char*)srcPixels + y_index * srcRB);
            if (scale == 256)
                while (--count >= 0)
                {
                    unsigned x = NOFILTER_BITMAP_SHADER_TILEPROC(fx, srcMaxX);
                    fx += dx;
                    *dstC++ = NOFILTER_BITMAP_SHADER_SAMPLE_X(srcPixels, x);
                }
            else
                while (--count >= 0)
                {
                    unsigned x = NOFILTER_BITMAP_SHADER_TILEPROC(fx, srcMaxX);
                    SkPMColor c = NOFILTER_BITMAP_SHADER_SAMPLE_X(srcPixels, x);
                    fx += dx;
                    *dstC++ = SkAlphaMulQ(c, scale);
                }
        }
        else    // dy != 0
        {
            if (scale == 256)
                while (--count >= 0)
                {
                    unsigned x = NOFILTER_BITMAP_SHADER_TILEPROC(fx, srcMaxX);
                    unsigned y = NOFILTER_BITMAP_SHADER_TILEPROC(fy, srcMaxY);
                    fx += dx;
                    fy += dy;
                    *dstC++ = NOFILTER_BITMAP_SHADER_SAMPLE_XY(srcPixels, x, y, srcRB);
                }
            else
                while (--count >= 0)
                {
                    unsigned x = NOFILTER_BITMAP_SHADER_TILEPROC(fx, srcMaxX);
                    unsigned y = NOFILTER_BITMAP_SHADER_TILEPROC(fy, srcMaxY);
                    SkPMColor c = NOFILTER_BITMAP_SHADER_SAMPLE_XY(srcPixels, x, y, srcRB);
                    fx += dx;
                    fy += dy;
                    *dstC++ = SkAlphaMulQ(c, scale);
                }
        }

        NOFILTER_BITMAP_SHADER_POSTAMBLE(srcBitmap);
    }

    virtual void shadeSpan16(int x, int y, uint16_t dstC[], int count)
    {
        SkASSERT(count > 0);
        SkASSERT(this->getFlags() & SkShader::kHasSpan16_Flag);

#ifdef NOFILTER_BITMAP_SHADER_SPRITEPROC16
        if ((this->getTotalInverse().getType() & ~SkMatrix::kTranslate_Mask) == 0)
        {
            NOFILTER_BITMAP_SHADER_SPRITEPROC16(this, x, y, dstC, count);
            return;
        }
#endif

#ifdef NOFILTER_BITMAP_SHADER_USE_UNITINVERSE
        const SkMatrix& inv = this->getUnitInverse();
        SkMatrix::MapPtProc invProc = this->getUnitInverseProc();
#else
        const SkMatrix& inv = this->getTotalInverse();
        SkMatrix::MapPtProc invProc = this->getInverseMapPtProc();
#endif
        const SkBitmap& srcBitmap = this->getSrcBitmap();
        unsigned        srcMaxX = srcBitmap.width() - 1;
        unsigned        srcMaxY = srcBitmap.height() - 1;
        unsigned        srcRB = srcBitmap.rowBytes();
        SkFixed         fx, fy, dx, dy;

        const NOFILTER_BITMAP_SHADER_TYPE* srcPixels = (const NOFILTER_BITMAP_SHADER_TYPE*)srcBitmap.getPixels();
        NOFILTER_BITMAP_SHADER_PREAMBLE16(srcBitmap, srcRB);

        if (this->getInverseClass() == kPerspective_MatrixClass)
        {
            SkPerspIter   iter(inv, SkIntToScalar(x) + SK_ScalarHalf,
                                    SkIntToScalar(y) + SK_ScalarHalf, count);
            while ((count = iter.next()) != 0)
            {
                const SkFixed* srcXY = iter.getXY();
                
                while (--count >= 0)
                {
                    fx = *srcXY++;
                    fy = *srcXY++;
                    unsigned x = NOFILTER_BITMAP_SHADER_TILEPROC(fx, srcMaxX);
                    unsigned y = NOFILTER_BITMAP_SHADER_TILEPROC(fy, srcMaxY);
                    *dstC++ = NOFILTER_BITMAP_SHADER_SAMPLE_XY16(srcPixels, x, y, srcRB);
                }
            }
            return;
        }

        // now init fx, fy, dx, dy
        {
            SkPoint srcPt;
            invProc(inv, SkIntToScalar(x) + SK_ScalarHalf,
                         SkIntToScalar(y) + SK_ScalarHalf, &srcPt);

            fx = SkScalarToFixed(srcPt.fX);
            fy = SkScalarToFixed(srcPt.fY);

            if (this->getInverseClass() == kFixedStepInX_MatrixClass)
                (void)inv.fixedStepInX(SkIntToScalar(y), &dx, &dy);
            else
            {
                dx = SkScalarToFixed(inv.getScaleX());
                dy = SkScalarToFixed(inv.getSkewY());
            }
        }

#ifndef NOFILTER_BITMAP_SHADER_USE_UNITINVERSE
        {   int level = this->getMipLevel() >> 16;
            fx >>= level;
            fy >>= level;
            dx >>= level;
            dy >>= level;
        }
#endif

        if (dy == 0)
        {
            srcPixels = (const NOFILTER_BITMAP_SHADER_TYPE*)((const char*)srcPixels + NOFILTER_BITMAP_SHADER_TILEPROC(fy, srcMaxY) * srcRB);
            do {
                unsigned x = NOFILTER_BITMAP_SHADER_TILEPROC(fx, srcMaxX);
                fx += dx;
                *dstC++ = NOFILTER_BITMAP_SHADER_SAMPLE_X16(srcPixels, x);
            } while (--count != 0);
        }
        else    // dy != 0
        {
            do {
                unsigned x = NOFILTER_BITMAP_SHADER_TILEPROC(fx, srcMaxX);
                unsigned y = NOFILTER_BITMAP_SHADER_TILEPROC(fy, srcMaxY);
                fx += dx;
                fy += dy;
                *dstC++ = NOFILTER_BITMAP_SHADER_SAMPLE_XY16(srcPixels, x, y, srcRB);
            } while (--count != 0);
        }

        NOFILTER_BITMAP_SHADER_POSTAMBLE16(srcBitmap);
    }
private:
    typedef HasSpan16_Sampler_BitmapShader INHERITED;
};

#undef NOFILTER_BITMAP_SHADER_CLASS
#undef NOFILTER_BITMAP_SHADER_TYPE
#undef NOFILTER_BITMAP_SHADER_PREAMBLE
#undef NOFILTER_BITMAP_SHADER_POSTAMBLE
#undef NOFILTER_BITMAP_SHADER_SAMPLE_X      //(x)
#undef NOFILTER_BITMAP_SHADER_SAMPLE_XY     //(x, y, rowBytes)
#undef NOFILTER_BITMAP_SHADER_TILEMODE
#undef NOFILTER_BITMAP_SHADER_TILEPROC

#undef NOFILTER_BITMAP_SHADER_PREAMBLE16
#undef NOFILTER_BITMAP_SHADER_POSTAMBLE16
#undef NOFILTER_BITMAP_SHADER_SAMPLE_X16        //(x)
#undef NOFILTER_BITMAP_SHADER_SAMPLE_XY16       //(x, y, rowBytes)

#undef NOFILTER_BITMAP_SHADER_USE_UNITINVERSE
#undef NOFILTER_BITMAP_SHADER_SPRITEPROC16
#undef NOFILTER_BITMAP_SHADER_SPRITEPROC32
