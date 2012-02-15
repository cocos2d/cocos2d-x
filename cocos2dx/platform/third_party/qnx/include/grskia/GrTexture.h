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


#ifndef GrTexture_DEFINED
#define GrTexture_DEFINED

#include "GrRefCnt.h"
#include "GrClip.h"
#include "GrResource.h"

class GrTexture;

/**
 * GrRenderTarget represents a 2D buffer of pixels that can be rendered to.
 * A context's render target is set by setRenderTarget(). Render targets are
 * created by a createTexture with the kRenderTarget_TextureFlag flag.
 * Additionally, GrContext provides methods for creating GrRenderTargets
 * that wrap externally created render targets.
 */
class GrRenderTarget : public GrResource {

public:
    /**
     * @return the width of the rendertarget
     */
    int width() const { return fWidth; }
    /**
     * @return the height of the rendertarget
     */
    int height() const { return fHeight; }

    /**
     * @return the number of stencil bits in the rendertarget
     */
    int stencilBits() const { return fStencilBits; }

    /**
     * @return the texture associated with the rendertarget, may be NULL.
     */
    GrTexture* asTexture() {return fTexture;}

    /**
     * @return true if the render target is multisampled, false otherwise
     */
    bool isMultisampled() { return fIsMultisampled; }

    /**
     * Call to indicate the multisample contents were modified such that the
     * render target needs to be resolved before it can be used as texture. Gr
     * tracks this for its own drawing and thus this only needs to be called
     * when the render target has been modified outside of Gr. Only meaningful
     * for Gr-created RT/Textures and Platform RT/Textures created with the
     * kGrCanResolve flag.
     * @param rect  a rect bounding the area needing resolve. NULL indicates
     *              the whole RT needs resolving.
     */
    void flagAsNeedingResolve(const GrIRect* rect = NULL);

    /**
     * Call to override the region that needs to be resolved.
     */
    void overrideResolveRect(const GrIRect rect);

    /**
     * Call to indicate that GrRenderTarget was externally resolved. This may
     * allow Gr to skip a redundant resolve step.
     */
    void flagAsResolved() { fResolveRect.setLargestInverted(); }

    /**
     * @return true if the GrRenderTarget requires MSAA resolving
     */
    bool needsResolve() const { return !fResolveRect.isEmpty(); }

    /**
     * Returns a rect bounding the region needing resolving.
     */
    const GrIRect& getResolveRect() const { return fResolveRect; }

    /**
     * Reads a rectangle of pixels from the render target.
     * @param left          left edge of the rectangle to read (inclusive)
     * @param top           top edge of the rectangle to read (inclusive)
     * @param width         width of rectangle to read in pixels.
     * @param height        height of rectangle to read in pixels.
     * @param config        the pixel config of the destination buffer
     * @param buffer        memory to read the rectangle into.
     *
     * @return true if the read succeeded, false if not. The read can fail
     *              because of a unsupported pixel config.
     */
    bool readPixels(int left, int top, int width, int height,
                    GrPixelConfig config, void* buffer);

    // a MSAA RT may require explicit resolving , it may auto-resolve (e.g. FBO
    // 0 in GL), or be unresolvable because the client didn't give us the 
    // resolve destination.
    enum ResolveType {
        kCanResolve_ResolveType,
        kAutoResolves_ResolveType,
        kCantResolve_ResolveType,
    };
    virtual ResolveType getResolveType() const = 0;

protected:
    GrRenderTarget(GrGpu* gpu,
                   GrTexture* texture,
                   int width,
                   int height,
                   int stencilBits,
                   bool isMultisampled)
        : INHERITED(gpu)
        , fTexture(texture)
        , fWidth(width)
        , fHeight(height)
        , fStencilBits(stencilBits)
        , fIsMultisampled(isMultisampled)
    {
        fResolveRect.setLargestInverted();
    }

    friend class GrTexture;
    // When a texture unrefs an owned rendertarget this func
    // removes the back pointer. This could be done called from 
    // texture's destructor but would have to be done in derived
    // class. By the time of texture base destructor it has already
    // lost its pointer to the rt.
    void onTextureReleaseRenderTarget() {
        GrAssert(NULL != fTexture);
        fTexture = NULL;
    }

private:
    GrTexture* fTexture; // not ref'ed
    int        fWidth;
    int        fHeight;
    int        fStencilBits;
    bool       fIsMultisampled;
    GrIRect    fResolveRect;

    // GrGpu keeps a cached clip in the render target to avoid redundantly
    // rendering the clip into the same stencil buffer.
    friend class GrGpu;
    GrClip     fLastStencilClip;

    typedef GrResource INHERITED;
};

class GrTexture : public GrResource {

public:
    /**
     * Retrieves the width of the texture.
     *
     * @return the width in texels
     */
    int width() const { return fWidth; }

    /**
     * Retrieves the height of the texture.
     *
     * @return the height in texels
     */
    int height() const { return fHeight; }

    /**
     * Convert from texels to normalized texture coords for POT textures
     * only.
     */
    GrFixed normalizeFixedX(GrFixed x) const { GrAssert(GrIsPow2(fWidth));
                                               return x >> fShiftFixedX; }
    GrFixed normalizeFixedY(GrFixed y) const { GrAssert(GrIsPow2(fHeight));
                                               return y >> fShiftFixedY; }

    /**
     * Retrieves the pixel config specified when the texture was created.
     */
    GrPixelConfig config() const { return fConfig; }

    /**
     *  Approximate number of bytes used by the texture
     */
    size_t sizeInBytes() const {
        return fWidth * fHeight * GrBytesPerPixel(fConfig);
    }

    /**
     * Updates a subrectangle of texels in the texture.
     *
     * @param x       left edge of rectangle to update
     * @param y       top edge of rectangle to update
     * @param width   width of rectangle to update
     * @param height  height of rectangle to update
     * @param srcData width*height texels of data in same format that was used
     *                at texture creation.
     */
    virtual void uploadTextureData(int x,
                                   int y,
                                   int width,
                                   int height,
                                   const void* srcData) = 0;

    /**
     * Reads a rectangle of pixels from the texture.
     * @param left          left edge of the rectangle to read (inclusive)
     * @param top           top edge of the rectangle to read (inclusive)
     * @param width         width of rectangle to read in pixels.
     * @param height        height of rectangle to read in pixels.
     * @param config        the pixel config of the destination buffer
     * @param buffer        memory to read the rectangle into.
     *
     * @return true if the read succeeded, false if not. The read can fail
     *              because of a unsupported pixel config.
     */
    bool readPixels(int left, int top, int width, int height,
                    GrPixelConfig config, void* buffer);

    /**
     * Retrieves the render target underlying this texture that can be passed to
     * GrGpu::setRenderTarget().
     *
     * @return    handle to render target or NULL if the texture is not a
     *            render target
     */
    GrRenderTarget* asRenderTarget() { return fRenderTarget; }

    /**
     * Removes the reference on the associated GrRenderTarget held by this
     * texture. Afterwards asRenderTarget() will return NULL. The
     * GrRenderTarget survives the release if another ref is held on it.
     */
    void releaseRenderTarget() {
        if (NULL != fRenderTarget) {
            GrAssert(fRenderTarget->asTexture() == this);
            fRenderTarget->onTextureReleaseRenderTarget();
            fRenderTarget->unref();
            fRenderTarget = NULL;
        }
    }

    /**
     *  Return the native ID or handle to the texture, depending on the
     *  platform. e.g. on opengl, return the texture ID.
     */
    virtual intptr_t getTextureHandle() = 0;

#if GR_DEBUG
    void validate() const {
        this->INHERITED::validate();
    }
#else
    void validate() const {}
#endif

protected:
    GrRenderTarget* fRenderTarget; // texture refs its rt representation
                                   // base class cons sets to NULL
                                   // subclass cons can create and set

    GrTexture(GrGpu* gpu,
              int width,
              int height,
              GrPixelConfig config)
    : INHERITED(gpu)
    , fRenderTarget(NULL)
    , fWidth(width)
    , fHeight(height)
    , fConfig(config) {
        // only make sense if alloc size is pow2
        fShiftFixedX = 31 - Gr_clz(fWidth);
        fShiftFixedY = 31 - Gr_clz(fHeight);
    }
    
    // GrResource overrides
    virtual void onRelease() {
        releaseRenderTarget();
    }

    virtual void onAbandon() {
        if (NULL != fRenderTarget) {
            fRenderTarget->abandon();
        }
    }

private:
    int fWidth;
    int fHeight;
    // these two shift a fixed-point value into normalized coordinates
    // for this texture if the texture is power of two sized.
    int      fShiftFixedX;
    int      fShiftFixedY;

    GrPixelConfig fConfig;

    typedef GrResource INHERITED;
};

#endif

