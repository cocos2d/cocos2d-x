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

#ifndef SkPorterDuff_DEFINED
#define SkPorterDuff_DEFINED

#include "SkColor.h"
#include "SkXfermode.h"

class SkXfermode;

/** DEPRECATED - use SkXfermode::Mode instead
 */
class SkPorterDuff {
public:
    /** List of predefined xfermodes. In general, the algebra for the modes
        uses the following symbols:
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
        kDarken_Mode,   //!< [Sa + Da - Sa*Da, Sc*(1 - Da) + Dc*(1 - Sa) + min(Sc, Dc)]
        kLighten_Mode,  //!< [Sa + Da - Sa*Da, Sc*(1 - Da) + Dc*(1 - Sa) + max(Sc, Dc)]
        kMultiply_Mode, //!< [Sa * Da, Sc * Dc]
        kScreen_Mode,   //!< [Sa + Da - Sa * Da, Sc + Dc - Sc * Dc]
        kAdd_Mode,      //!< Saturate(S + D)
#ifdef ANDROID
        kOverlay_Mode,
#endif

        kModeCount
    };

    /** Return an SkXfermode object for the specified mode.
    */
    static SkXfermode* CreateXfermode(Mode mode);
    
    /** Return a function pointer to a routine that applies the specified
        porter-duff transfer mode.
    */
    static SkXfermodeProc GetXfermodeProc(Mode mode);
    
    /** Return a function pointer to a routine that applies the specified
        porter-duff transfer mode and srcColor to a 16bit device color. Note,
        if the mode+srcColor might return a non-opaque color, then there is not
        16bit proc, and this will return NULL.
    */
    static SkXfermodeProc16 GetXfermodeProc16(Mode mode, SkColor srcColor);
    
    /** If the specified xfermode advertises itself as one of the porterduff
        modes (via SkXfermode::Coeff), return true and if not null, set mode
        to the corresponding porterduff mode. If it is not recognized as a one,
        return false and ignore the mode parameter.
    */
    static bool IsMode(SkXfermode*, Mode* mode);

    /** Return the corersponding SkXfermode::Mode
     */
    static SkXfermode::Mode ToXfermodeMode(Mode);
};

#endif

