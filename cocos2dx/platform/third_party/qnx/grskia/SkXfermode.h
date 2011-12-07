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

#ifndef SkXfermode_DEFINED
#define SkXfermode_DEFINED

#include "SkFlattenable.h"
#include "SkColor.h"

/** \class SkXfermode

    SkXfermode is the base class for objects that are called to implement custom
    "transfer-modes" in the drawing pipeline. The static function Create(Modes)
    can be called to return an instance of any of the predefined subclasses as
    specified in the Modes enum. When an SkXfermode is assigned to an SkPaint,
    then objects drawn with that paint have the xfermode applied.
*/
class SK_API SkXfermode : public SkFlattenable {
public:
    SkXfermode() {}

    virtual void xfer32(SkPMColor dst[], const SkPMColor src[], int count,
                        const SkAlpha aa[]);
    virtual void xfer16(uint16_t dst[], const SkPMColor src[], int count,
                        const SkAlpha aa[]);
    virtual void xfer4444(uint16_t dst[], const SkPMColor src[], int count,
                          const SkAlpha aa[]);
    virtual void xferA8(SkAlpha dst[], const SkPMColor src[], int count,
                        const SkAlpha aa[]);

    /** Enum of possible coefficients to describe some xfermodes
     */
    enum Coeff {
        kZero_Coeff,    /** 0 */
        kOne_Coeff,     /** 1 */
        kSC_Coeff,      /** src color */
        kISC_Coeff,     /** inverse src color (i.e. 1 - sc) */
        kDC_Coeff,      /** dst color */
        kIDC_Coeff,     /** inverse dst color (i.e. 1 - dc) */
        kSA_Coeff,      /** src alpha */
        kISA_Coeff,     /** inverse src alpha (i.e. 1 - sa) */
        kDA_Coeff,      /** dst alpha */
        kIDA_Coeff,     /** inverse dst alpha (i.e. 1 - da) */

        kCoeffCount
    };

    /** If the xfermode can be expressed as an equation using the coefficients
        in Coeff, then asCoeff() returns true, and sets (if not null) src and
        dst accordingly.

            result = src_coeff * src_color + dst_coeff * dst_color;

        As examples, here are some of the porterduff coefficients

        MODE        SRC_COEFF       DST_COEFF
        clear       zero            zero
        src         one             zero
        dst         zero            one
        srcover     one             isa
        dstover     ida             one
     */
    virtual bool asCoeff(Coeff* src, Coeff* dst);

    /**
     *  The same as calling xfermode->asCoeff(..), except that this also checks
     *  if the xfermode is NULL, and if so, treats its as kSrcOver_Mode.
     */
    static bool AsCoeff(SkXfermode*, Coeff* src, Coeff* dst);

    /** List of predefined xfermodes.
        The algebra for the modes uses the following symbols:
        Sa, Sc  - source alpha and color
        Da, Dc - destination alpha and color (before compositing)
        [a, c] - Resulting (alpha, color) values
        For these equations, the colors are in premultiplied state.
        If no xfermode is specified, kSrcOver is assumed.
     */
    enum Mode {
        kClear_Mode,    //!< [0, 0]
        kSrc_Mode,      //!< [Sa, Sc]
        kDst_Mode,      //!< [Da, Dc]
        kSrcOver_Mode,  //!< [Sa + Da - Sa*Da, Rc = Sc + (1 - Sa)*Dc]
        kDstOver_Mode,  //!< [Sa + Da - Sa*Da, Rc = Dc + (1 - Da)*Sc]
        kSrcIn_Mode,    //!< [Sa * Da, Sc * Da]
        kDstIn_Mode,    //!< [Sa * Da, Sa * Dc]
        kSrcOut_Mode,   //!< [Sa * (1 - Da), Sc * (1 - Da)]
        kDstOut_Mode,   //!< [Da * (1 - Sa), Dc * (1 - Sa)]
        kSrcATop_Mode,  //!< [Da, Sc * Da + (1 - Sa) * Dc]
        kDstATop_Mode,  //!< [Sa, Sa * Dc + Sc * (1 - Da)]
        kXor_Mode,      //!< [Sa + Da - 2 * Sa * Da, Sc * (1 - Da) + (1 - Sa) * Dc]

        // all remaining modes are defined in the SVG Compositing standard
        // http://www.w3.org/TR/2009/WD-SVGCompositing-20090430/
        kPlus_Mode,
        kMultiply_Mode, 
        
        // all above modes can be expressed as pair of src/dst Coeffs
        kCoeffModesCnt, 
        
        kScreen_Mode = kCoeffModesCnt,
        kOverlay_Mode,
        kDarken_Mode,
        kLighten_Mode,
        kColorDodge_Mode,
        kColorBurn_Mode,
        kHardLight_Mode,
        kSoftLight_Mode,
        kDifference_Mode,
        kExclusion_Mode,

        kLastMode = kExclusion_Mode
    };

    /**
     *  If the xfermode is one of the modes in the Mode enum, then asMode()
     *  returns true and sets (if not null) mode accordingly. Otherwise it
     *  returns false and ignores the mode parameter.
     */
    virtual bool asMode(Mode* mode);

    /**
     *  The same as calling xfermode->asMode(mode), except that this also checks
     *  if the xfermode is NULL, and if so, treats its as kSrcOver_Mode.
     */
    static bool AsMode(SkXfermode*, Mode* mode);

    /** Return an SkXfermode object for the specified mode.
     */
    static SkXfermode* Create(Mode mode);

    /** Return a function pointer to a routine that applies the specified
        porter-duff transfer mode.
     */
    static SkXfermodeProc GetProc(Mode mode);

    /** Return a function pointer to a routine that applies the specified
        porter-duff transfer mode and srcColor to a 16bit device color. Note,
        if the mode+srcColor might return a non-opaque color, then there is not
        16bit proc, and this will return NULL.
      */
    static SkXfermodeProc16 GetProc16(Mode mode, SkColor srcColor);

    /**
     *  If the specified mode can be represented by a pair of Coeff, then return
     *  true and set (if not NULL) the corresponding coeffs. If the mode is
     *  not representable as a pair of Coeffs, return false and ignore the
     *  src and dst parameters.
     */
    static bool ModeAsCoeff(Mode mode, Coeff* src, Coeff* dst);

    // DEPRECATED: call AsMode(...)
    static bool IsMode(SkXfermode* xfer, Mode* mode) {
        return AsMode(xfer, mode);
    }

protected:
    SkXfermode(SkFlattenableReadBuffer& rb) : SkFlattenable(rb) {}

    /** The default implementation of xfer32/xfer16/xferA8 in turn call this
        method, 1 color at a time (upscaled to a SkPMColor). The default
        implmentation of this method just returns dst. If performance is
        important, your subclass should override xfer32/xfer16/xferA8 directly.

        This method will not be called directly by the client, so it need not
        be implemented if your subclass has overridden xfer32/xfer16/xferA8
    */
    virtual SkPMColor xferColor(SkPMColor src, SkPMColor dst);

private:
    enum {
        kModeCount = kLastMode + 1
    };
    typedef SkFlattenable INHERITED;
};

///////////////////////////////////////////////////////////////////////////////

/** \class SkProcXfermode

    SkProcXfermode is a xfermode that applies the specified proc to its colors.
    This class is not exported to java.
*/
class SkProcXfermode : public SkXfermode {
public:
    SkProcXfermode(SkXfermodeProc proc) : fProc(proc) {}

    // overrides from SkXfermode
    virtual void xfer32(SkPMColor dst[], const SkPMColor src[], int count,
                        const SkAlpha aa[]);
    virtual void xfer16(uint16_t dst[], const SkPMColor src[], int count,
                        const SkAlpha aa[]);
    virtual void xfer4444(uint16_t dst[], const SkPMColor src[], int count,
                          const SkAlpha aa[]);
    virtual void xferA8(SkAlpha dst[], const SkPMColor src[], int count,
                        const SkAlpha aa[]);

    // overrides from SkFlattenable
    virtual Factory getFactory() { return CreateProc; }
    virtual void    flatten(SkFlattenableWriteBuffer&);

protected:
    SkProcXfermode(SkFlattenableReadBuffer&);

private:
    SkXfermodeProc  fProc;

    static SkFlattenable* CreateProc(SkFlattenableReadBuffer& buffer) {
        return SkNEW_ARGS(SkProcXfermode, (buffer)); }

    typedef SkXfermode INHERITED;
};

#endif
