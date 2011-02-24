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

#ifndef SkShader_DEFINED
#define SkShader_DEFINED

#include "SkBitmap.h"
#include "SkFlattenable.h"
#include "SkMask.h"
#include "SkMatrix.h"
#include "SkPaint.h"

class SkPath;

/** \class SkShader

    SkShader is the based class for objects that return horizontal spans of colors during drawing.
    A subclass of SkShader is installed in a SkPaint calling paint.setShader(shader). After that
    any object (other than a bitmap) that is drawn with that paint will get its color(s) from the
    shader.
*/
class SkShader : public SkFlattenable {
public:
            SkShader();
    virtual ~SkShader();

    /** Return true if the shader has a non-identity local matrix.
        @param localM   Optional: If not null, return the shader's local matrix
        @return true if the shader has a non-identity local matrix.
    */
    bool getLocalMatrix(SkMatrix* localM) const;
    /** Set the shader's local matrix.
        @param localM   The shader's new local matrix.
    */
    void setLocalMatrix(const SkMatrix& localM);
    /** Reset the shader's local matrix to identity.
    */
    void resetLocalMatrix();

    enum TileMode {
        kClamp_TileMode,    //!< replicate the edge color if the shader draws outside of its original bounds
        kRepeat_TileMode,   //!< repeat the shader's image horizontally and vertically
        kMirror_TileMode,   //!< repeat the shader's image horizontally and vertically, alternating mirror images so that adjacent images always seam

        kTileModeCount
    };

    // override these in your subclass

    enum Flags {
        //!< set if all of the colors will be opaque
        kOpaqueAlpha_Flag  = 0x01,

        //! set if this shader's shadeSpan16() method can be called
        kHasSpan16_Flag = 0x02,

        /** Set this bit if the shader's native data type is instrinsically 16
            bit, meaning that calling the 32bit shadeSpan() entry point will
            mean the the impl has to up-sample 16bit data into 32bit. Used as a
            a means of clearing a dither request if the it will have no effect
        */
        kIntrinsicly16_Flag = 0x04,

        /** set (after setContext) if the spans only vary in X (const in Y).
            e.g. an Nx1 bitmap that is being tiled in Y, or a linear-gradient
            that varies from left-to-right. This flag specifies this for
            shadeSpan().
         */
        kConstInY32_Flag = 0x08,
        
        /** same as kConstInY32_Flag, but is set if this is true for shadeSpan16
            which may not always be the case, since shadeSpan16 may be
            predithered, which would mean it was not const in Y, even though
            the 32bit shadeSpan() would be const.
         */
        kConstInY16_Flag = 0x10
    };

    /** Called sometimes before drawing with this shader.
        Return the type of alpha your shader will return.
        The default implementation returns 0. Your subclass should override if it can
        (even sometimes) report a non-zero value, since that will enable various blitters
        to perform faster.
    */
    virtual uint32_t getFlags() { return 0; }

    /** Return the alpha associated with the data returned by shadeSpan16(). If
        kHasSpan16_Flag is not set, this value is meaningless.
    */
    virtual uint8_t getSpan16Alpha() const { return fPaintAlpha; }
    
    /** Called once before drawing, with the current paint and
        device matrix. Return true if your shader supports these
        parameters, or false if not. If false is returned, nothing
        will be drawn.
    */
    virtual bool setContext(const SkBitmap& device, const SkPaint& paint,
                            const SkMatrix& matrix);

    /** Called for each span of the object being drawn. Your subclass
        should set the appropriate colors (with premultiplied alpha) that
        correspond to the specified device coordinates.
    */
    virtual void shadeSpan(int x, int y, SkPMColor[], int count) = 0;
    /** Called only for 16bit devices when getFlags() returns
        kOpaqueAlphaFlag | kHasSpan16_Flag
    */
    virtual void shadeSpan16(int x, int y, uint16_t[], int count);
    /** Similar to shadeSpan, but only returns the alpha-channel for a span.
        The default implementation calls shadeSpan() and then extracts the alpha
        values from the returned colors.
    */
    virtual void shadeSpanAlpha(int x, int y, uint8_t alpha[], int count);

    /** Helper function that returns true if this shader's shadeSpan16() method can
        be called.
    */
    bool canCallShadeSpan16() {
        return SkShader::CanCallShadeSpan16(this->getFlags());
    }

    /** Helper to check the flags to know if it is legal to call shadeSpan16()
    */
    static bool CanCallShadeSpan16(uint32_t flags) {
        return (flags & kHasSpan16_Flag) != 0;
    }

    /** Called before a session using the shader begins. Some shaders override
        this to defer some of their work (like calling bitmap.lockPixels()).
        Must be balanced by a call to endSession.
    */
    virtual void beginSession();
    virtual void endSession();
    
    /** Optional methods for shaders that can pretend to be a bitmap/texture
        to play along with opengl. Default just returns false and ignores
        the out parameters.
    */
    virtual bool asABitmap(SkBitmap* outTexture, SkMatrix* outMatrix,
                           TileMode xy[2]);

    //////////////////////////////////////////////////////////////////////////
    //  Factory methods for stock shaders

    /** Call this to create a new shader that will draw with the specified bitmap.
        @param src  The bitmap to use inside the shader
        @param tmx  The tiling mode to use when sampling the bitmap in the x-direction.
        @param tmy  The tiling mode to use when sampling the bitmap in the y-direction.
        @return     Returns a new shader object. Note: this function never returns null.
    */
    static SkShader* CreateBitmapShader(const SkBitmap& src,
                                        TileMode tmx, TileMode tmy);

    virtual void flatten(SkFlattenableWriteBuffer& );
protected:
    enum MatrixClass {
        kLinear_MatrixClass,            // no perspective
        kFixedStepInX_MatrixClass,      // fast perspective, need to call fixedStepInX() each scanline
        kPerspective_MatrixClass        // slow perspective, need to mappoints each pixel
    };
    static MatrixClass ComputeMatrixClass(const SkMatrix&);

    // These can be called by your subclass after setContext() has been called
    uint8_t             getPaintAlpha() const { return fPaintAlpha; }
    SkBitmap::Config    getDeviceConfig() const { return (SkBitmap::Config)fDeviceConfig; }
    const SkMatrix&     getTotalInverse() const { return fTotalInverse; }
    MatrixClass         getInverseClass() const { return (MatrixClass)fTotalInverseClass; }

    SkShader(SkFlattenableReadBuffer& );
private:
    SkMatrix*           fLocalMatrix;
    SkMatrix            fTotalInverse;
    uint8_t             fPaintAlpha;
    uint8_t             fDeviceConfig;
    uint8_t             fTotalInverseClass;
    SkDEBUGCODE(SkBool8 fInSession;)

    static SkShader* CreateBitmapShader(const SkBitmap& src,
                                        TileMode, TileMode,
                                        void* storage, size_t storageSize);
    friend class SkAutoBitmapShaderInstall;
    typedef SkFlattenable INHERITED;
};

#endif

