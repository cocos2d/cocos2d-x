/*
    Copyright 2011 Google Inc.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

         http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
 */

#ifndef GrStencil_DEFINED
#define GrStencil_DEFINED

#include "GrTypes.h"
/**
 * Gr uses the stencil buffer to implement complex clipping inside the
 * GrDrawTarget class. The GrDrawTarget makes a subset of the stencil buffer
 * bits available for other uses by external code (clients). Client code can
 * modify these bits. GrDrawTarget will ignore ref, mask, and writemask bits
 * provided by clients that overlap the bits used to implement clipping. The
 * client can use the getUsableStencilBits() function to find out how many
 * client accessible stencil bits are available.
 *
 * When code outside the GrDrawTarget class uses the stencil buffer the contract
 * is as follows:
 *
 * > Normal stencil funcs allow the GrGpu client to modify the client bits of
 *   the stencil buffer outside of the clip.
 * > Special functions allow a test against the clip. These are more limited
 *   than the general stencil functions.
 * > Client can assume all client bits are zero initially.
 * > Client must ensure that after all its passes are finished it has only
 *   written to the color buffer in the region inside the clip. Furthermore, it
 *   must zero all client bits that were modifed (both inside and outside the
 *   clip).
 */

/**
 * Determines which pixels pass / fail the stencil test.
 * Stencil test passes if (ref & mask) FUNC (stencil & mask) is true
 */
enum GrStencilFunc {
    kAlways_StencilFunc = 0,
    kNever_StencilFunc,
    kGreater_StencilFunc,
    kGEqual_StencilFunc,
    kLess_StencilFunc,
    kLEqual_StencilFunc,
    kEqual_StencilFunc,
    kNotEqual_StencilFunc,

    // Gr stores the current clip in the
    // stencil buffer in the high bits that
    // are not directly accessible modifiable
    // via the GrDrawTarget interface. The below
    // stencil funcs test against the current
    // clip in addition to the GrDrawTarget
    // client's stencil bits.

    // pass if inside the clip
    kAlwaysIfInClip_StencilFunc,
    kEqualIfInClip_StencilFunc,
    kLessIfInClip_StencilFunc,
    kLEqualIfInClip_StencilFunc,
    kNonZeroIfInClip_StencilFunc, // this one forces the ref to be 0

    // counts
    kStencilFuncCount,
    kClipStencilFuncCount = kNonZeroIfInClip_StencilFunc -
                            kAlwaysIfInClip_StencilFunc + 1,
    kBasicStencilFuncCount = kStencilFuncCount - kClipStencilFuncCount
};

/**
 * Operations to perform based on whether stencil test passed failed.
 */
enum GrStencilOp {
    kKeep_StencilOp = 0,    // preserve existing stencil value
    kReplace_StencilOp,     // replace with reference value from stencl test
    kIncWrap_StencilOp,     // increment and wrap at max
    kIncClamp_StencilOp,    // increment and clamp at max
    kDecWrap_StencilOp,     // decrement and wrap at 0
    kDecClamp_StencilOp,    // decrement and clamp at 0
    kZero_StencilOp,        // zero stencil bits
    kInvert_StencilOp,      // invert stencil bits

    kStencilOpCount
};

/**
 * Struct representing stencil state.
 */
struct GrStencilSettings {
    GrStencilOp   fFrontPassOp;     // op to perform when front faces pass
    GrStencilOp   fBackPassOp;      // op to perform when back faces pass
    GrStencilOp   fFrontFailOp;     // op to perform when front faces fail
    GrStencilOp   fBackFailOp;      // op to perform when back faces fail
    GrStencilFunc fFrontFunc;       // test function for front faces
    GrStencilFunc fBackFunc;        // test function for back faces
    unsigned int fFrontFuncMask;    // mask for front face test
    unsigned int fBackFuncMask;     // mask for back face test
    unsigned int fFrontFuncRef;     // reference value for front face test
    unsigned int fBackFuncRef;      // reference value for back face test
    unsigned int fFrontWriteMask;   // stencil write mask for front faces
    unsigned int fBackWriteMask;    // stencil write mask for back faces

    bool operator == (const GrStencilSettings& s) const {
        // make sure this is tightly packed.
        GR_STATIC_ASSERT(0 == sizeof(GrStencilOp)%4);
        GR_STATIC_ASSERT(0 == sizeof(GrStencilFunc)%4);
        GR_STATIC_ASSERT(sizeof(GrStencilSettings) ==
                        4*sizeof(GrStencilOp) +
                        2*sizeof(GrStencilFunc) +
                        6*sizeof(unsigned int));
        return 0 == memcmp(this, &s, sizeof(GrStencilSettings));
    }

    bool operator != (const GrStencilSettings& s) const {
        return !(*this == s);
    }

    GrStencilSettings& operator =(const GrStencilSettings& s) {
        memcpy(this, &s, sizeof(GrStencilSettings));
        return *this;
    }

    void setSame(GrStencilOp passOp,
                 GrStencilOp failOp,
                 GrStencilFunc func,
                 unsigned int funcMask,
                 unsigned int funcRef,
                 unsigned int writeMask) {
        fFrontPassOp        = passOp;
        fBackPassOp         = passOp;
        fFrontFailOp        = failOp;
        fBackFailOp         = failOp;
        fFrontFunc          = func;
        fBackFunc           = func;
        fFrontFuncMask      = funcMask;
        fBackFuncMask       = funcMask;
        fFrontFuncRef       = funcRef;
        fBackFuncRef        = funcRef;
        fFrontWriteMask     = writeMask;
        fBackWriteMask      = writeMask;
    }

    // canonical value for disabled stenciling
    static const GrStencilSettings gDisabled;
    void setDisabled() {
        *this = gDisabled;
    }
    bool isDisabled() const {
        return kKeep_StencilOp == fFrontPassOp   &&
               kKeep_StencilOp == fBackPassOp    &&
               kKeep_StencilOp == fFrontFailOp   &&
               kKeep_StencilOp == fBackFailOp   &&
               kAlways_StencilFunc == fFrontFunc &&
               kAlways_StencilFunc == fBackFunc;
    }
    void invalidate()  {
        // just write an illegal value to the first member
        fFrontPassOp = (GrStencilOp)-1;
    }

private:
    friend class GrGpu;

    enum {
        kMaxStencilClipPasses = 2  // maximum number of passes to add a clip 
                                   // element to the stencil buffer.
    };

    /**
     * Given a thing to draw into the stencil clip, a fill type, and a set op
     * this function determines:
     *      1. Whether the thing can be draw directly to the stencil clip or
     *      needs to be drawn to the client portion of the stencil first.
     *      2. How many passes are needed.
     *      3. What those passes are.
     *      4. The fill rule that should actually be used to render (will 
     *         always be non-inverted).
     *
     * @param op                the set op to combine this element with the 
     *                          existing clip
     * @param stencilClipMask   mask with just the stencil bit used for clipping
     *                          enabled.
     * @param invertedFill      is this path inverted
     * @param numPasses         out: the number of passes needed to add the 
     *                               element to the clip.
     * @param settings          out: the stencil settings to use for each pass
     *
     * @return true if the clip element's geometry can be drawn directly to the
     *         stencil clip bit. Will only be true if canBeDirect is true.
     *         numPasses will be 1 if return value is true.
     */
    static bool GetClipPasses(GrSetOp op, 
                              bool canBeDirect,
                              unsigned int stencilClipMask,
                              bool invertedFill,
                              int* numPasses,
                              GrStencilSettings settings[kMaxStencilClipPasses]);
};

#endif
