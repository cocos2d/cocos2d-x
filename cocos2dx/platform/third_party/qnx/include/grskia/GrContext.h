/*
    Copyright 2010 Google Inc.

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

#ifndef GrContext_DEFINED
#define GrContext_DEFINED

#include "GrClip.h"
#include "GrTextureCache.h"
#include "GrPaint.h"
#include "GrPathRenderer.h"

class GrFontCache;
class GrGpu;
struct GrGpuStats;
class GrVertexBufferAllocPool;
class GrIndexBufferAllocPool;
class GrInOrderDrawBuffer;

class GR_API GrContext : public GrRefCnt {
public:
    /**
     * Creates a GrContext from within a 3D context.
     */
    static GrContext* Create(GrEngine engine,
                             GrPlatform3DContext context3D);

    /**
     *  Helper to create a opengl-shader based context
     */
    static GrContext* CreateGLShaderContext();

    virtual ~GrContext();

    /**
     * The GrContext normally assumes that no outsider is setting state
     * within the underlying 3D API's context/device/whatever. This call informs
     * the context that the state was modified and it should resend. Shouldn't
     * be called frequently for good performance.
     */
    void resetContext();

    /**
     * Abandons all gpu resources, assumes 3D API state is unknown. Call this
     * if you have lost the associated GPU context, and thus internal texture,
     * buffer, etc. references/IDs are now invalid. Should be called even when
     * GrContext is no longer going to be used for two reasons:
     *  1) ~GrContext will not try to free the objects in the 3D API.
     *  2) If you've created GrResources that outlive the GrContext they will
     *     be marked as invalid (GrResource::isValid()) and won't attempt to
     *     free their underlying resource in the 3D API.
     * Content drawn since the last GrContext::flush() may be lost.
     */
    void contextLost();

    /**
     * Similar to contextLost, but makes no attempt to reset state.
     * Use this method when GrContext destruction is pending, but
     * the graphics context is destroyed first.
     */
    void contextDestroyed();

    /**
     * Frees gpu created by the context. Can be called to reduce GPU memory
     * pressure.
     */
    void freeGpuResources();

    ///////////////////////////////////////////////////////////////////////////
    // Textures

    /**
     *  Search for an entry with the same Key. If found, "lock" it and return it.
     *  If not found, return null.
     */
    GrTextureEntry* findAndLockTexture(GrTextureKey*,
                                       const GrSamplerState&);


    /**
     *  Create a new entry, based on the specified key and texture, and return
     *  its "locked" entry.
     *
     *  Ownership of the texture is transferred to the Entry, which will unref()
     *  it when we are purged or deleted.
     */
    GrTextureEntry* createAndLockTexture(GrTextureKey* key,
                                         const GrSamplerState&,
                                         const GrTextureDesc&,
                                         void* srcData, size_t rowBytes);

    /**
     * Returns a texture matching the desc. It's contents are unknown. Subsequent
     * requests with the same descriptor are not guaranteed to return the same
     * texture. The same texture is guaranteed not be returned again until it is
     * unlocked.
     *
     * Textures created by createAndLockTexture() hide the complications of
     * tiling non-power-of-two textures on APIs that don't support this (e.g. 
     * unextended GLES2). Tiling a npot texture created by lockKeylessTexture on
     * such an API will create gaps in the tiling pattern. This includes clamp
     * mode. (This may be addressed in a future update.)
     */
    GrTextureEntry* lockKeylessTexture(const GrTextureDesc& desc);

    /**
     * Finds a texture that approximately matches the descriptor. Will be
     * at least as large in width and height as desc specifies. If desc
     * specifies that texture is a render target then result will be a
     * render target. If desc specifies a render target and doesn't set the
     * no stencil flag then result will have a stencil. Format and aa level
     * will always match.
     */
    GrTextureEntry* findApproximateKeylessTexture(const GrTextureDesc& desc);

    /**
     *  When done with an entry, call unlockTexture(entry) on it, which returns
     *  it to the cache, where it may be purged.
     */
    void unlockTexture(GrTextureEntry* entry);

    /**
     * Creates a texture that is outside the cache. Does not count against
     * cache's budget.
     */
    GrTexture* createUncachedTexture(const GrTextureDesc&,
                                     void* srcData,
                                     size_t rowBytes);

    /**
     *  Returns true if the specified use of an indexed texture is supported.
     */
    bool supportsIndex8PixelConfig(const GrSamplerState&, int width, int height);

    /**
     *  Return the current texture cache limits.
     *
     *  @param maxTextures If non-null, returns maximum number of textures that
     *                     can be held in the cache.
     *  @param maxTextureBytes If non-null, returns maximum number of bytes of
     *                         texture memory that can be held in the cache.
     */
    void getTextureCacheLimits(int* maxTextures, size_t* maxTextureBytes) const;

    /**
     *  Specify the texture cache limits. If the current cache exceeds either
     *  of these, it will be purged (LRU) to keep the cache within these limits.
     *
     *  @param maxTextures The maximum number of textures that can be held in
     *                     the cache.
     *  @param maxTextureBytes The maximum number of bytes of texture memory
     *                         that can be held in the cache.
     */
    void setTextureCacheLimits(int maxTextures, size_t maxTextureBytes);

    /**
     *  Return the max width or height of a texture supported by the current gpu
     */
    int getMaxTextureSize() const;

    /**
     * Return the max width or height of a render target supported by the 
     * current gpu
     */
    int getMaxRenderTargetSize() const;

    ///////////////////////////////////////////////////////////////////////////
    // Render targets

    /**
     * Sets the render target.
     * @param target    the render target to set. (should not be NULL.)
     */
    void setRenderTarget(GrRenderTarget* target);

    /**
     * Gets the current render target.
     * @return the currently bound render target. Should never be NULL.
     */
    const GrRenderTarget* getRenderTarget() const;
    GrRenderTarget* getRenderTarget();

    ///////////////////////////////////////////////////////////////////////////
    // Platform Surfaces

    // GrContext provides an interface for wrapping externally created textures
    // and rendertargets in their Gr-equivalents.

    /**
     * Wraps an existing 3D API surface in a GrObject. desc.fFlags determines
     * the type of object returned. If kIsTexture is set the returned object
     * will be a GrTexture*. Otherwise, it will be a GrRenderTarget*. If both 
     * are set the render target object is accessible by
     * GrTexture::asRenderTarget().
     *
     * GL: if the object is a texture Gr may change its GL texture parameters
     *     when it is drawn.
     *
     * @param   desc    description of the object to create.
     * @return either a GrTexture* or GrRenderTarget* depending on desc. NULL
     *         on failure.
     */
    GrResource* createPlatformSurface(const GrPlatformSurfaceDesc& desc);
    /**
     * Reads the current target object (e.g. FBO or IDirect3DSurface9*) and
     * viewport state from the underlying 3D API and wraps it in a
     * GrRenderTarget. The GrRenderTarget will not attempt to delete/destroy the
     * underlying object in its destructor and it is up to caller to guarantee
     * that it remains valid while the GrRenderTarget is used.
     *
     * Will not detect that the render target is also a texture. If you need
     * to also use the render target as a GrTexture use createPlatformSurface.
     *
     * @return the newly created GrRenderTarget
     */
    GrRenderTarget* createRenderTargetFrom3DApiState();

    ///////////////////////////////////////////////////////////////////////////
    // Matrix state

    /**
     * Gets the current transformation matrix.
     * @return the current matrix.
     */
    const GrMatrix& getMatrix() const;

    /**
     * Sets the transformation matrix.
     * @param m the matrix to set.
     */
    void setMatrix(const GrMatrix& m);

    /**
     * Concats the current matrix. The passed matrix is applied before the
     * current matrix.
     * @param m the matrix to concat.
     */
    void concatMatrix(const GrMatrix& m) const;


    ///////////////////////////////////////////////////////////////////////////
    // Clip state
    /**
     * Gets the current clip.
     * @return the current clip.
     */
    const GrClip& getClip() const;

    /**
     * Sets the clip.
     * @param clip  the clip to set.
     */
    void setClip(const GrClip& clip);

    /**
     * Convenience method for setting the clip to a rect.
     * @param rect  the rect to set as the new clip.
     */
    void setClip(const GrIRect& rect);

    ///////////////////////////////////////////////////////////////////////////
    // Draws

    /**
     * Clear the entire or rect of the render target, ignoring any clips.
     * @param rect  the rect to clear or the whole thing if rect is NULL.
     * @param color the color to clear to.
     */
    void clear(const GrIRect* rect, GrColor color);

    /**
     *  Draw everywhere (respecting the clip) with the paint.
     */
    void drawPaint(const GrPaint& paint);

    /**
     *  Draw the rect using a paint.
     *  @param paint        describes how to color pixels.
     *  @param strokeWidth  If strokeWidth < 0, then the rect is filled, else
     *                      the rect is mitered stroked based on strokeWidth. If
     *                      strokeWidth == 0, then the stroke is always a single
     *                      pixel thick.
     *  @param matrix       Optional matrix applied to the rect. Applied before
     *                      context's matrix or the paint's matrix.
     *  The rects coords are used to access the paint (through texture matrix)
     */
    void drawRect(const GrPaint& paint,
                  const GrRect&,
                  GrScalar strokeWidth = -1,
                  const GrMatrix* matrix = NULL);

    /**
     * Maps a rect of paint coordinates onto the a rect of destination
     * coordinates. Each rect can optionally be transformed. The srcRect
     * is stretched over the dstRect. The dstRect is transformed by the
     * context's matrix and the srcRect is transformed by the paint's matrix.
     * Additional optional matrices can be provided by parameters.
     *
     * @param paint     describes how to color pixels.
     * @param dstRect   the destination rect to draw.
     * @param srcRect   rect of paint coordinates to be mapped onto dstRect
     * @param dstMatrix Optional matrix to transform dstRect. Applied before
     *                  context's matrix.
     * @param srcMatrix Optional matrix to transform srcRect Applied before
     *                  paint's matrix.
     */
    void drawRectToRect(const GrPaint& paint,
                        const GrRect& dstRect,
                        const GrRect& srcRect,
                        const GrMatrix* dstMatrix = NULL,
                        const GrMatrix* srcMatrix = NULL);

    /**
     * Draws a path.
     *
     * @param paint         describes how to color pixels.
     * @param path          the path to draw
     * @param fill          the path filling rule to use.
     * @param translate     optional additional translation applied to the
     *                      path.
     */
    void drawPath(const GrPaint& paint, const GrPath& path, GrPathFill fill,
                  const GrPoint* translate = NULL);

    /**
     * Draws vertices with a paint.
     *
     * @param   paint           describes how to color pixels.
     * @param   primitiveType   primitives type to draw.
     * @param   vertexCount     number of vertices.
     * @param   positions       array of vertex positions, required.
     * @param   texCoords       optional array of texture coordinates used
     *                          to access the paint.
     * @param   colors          optional array of per-vertex colors, supercedes
     *                          the paint's color field.
     * @param   indices         optional array of indices. If NULL vertices
     *                          are drawn non-indexed.
     * @param   indexCount      if indices is non-null then this is the
     *                          number of indices.
     */
    void drawVertices(const GrPaint& paint,
                      GrPrimitiveType primitiveType,
                      int vertexCount,
                      const GrPoint positions[],
                      const GrPoint texs[],
                      const GrColor colors[],
                      const uint16_t indices[],
                      int indexCount);

    /**
     * Similar to drawVertices but caller provides objects that convert to Gr
     * types. The count of vertices is given by posSrc.
     *
     * @param   paint           describes how to color pixels.
     * @param   primitiveType   primitives type to draw.
     * @param   posSrc          Source of vertex positions. Must implement
     *                              int count() const;
     *                              void writeValue(int i, GrPoint* point) const;
     *                          count returns the total number of vertices and
     *                          writeValue writes a vertex position to point.
     * @param   texSrc          optional, pass NULL to not use explicit tex
     *                          coords. If present provides tex coords with
     *                          method:
     *                              void writeValue(int i, GrPoint* point) const;
     * @param   texSrc          optional, pass NULL to not use per-vertex colors
     *                          If present provides colors with method:
     *                              void writeValue(int i, GrColor* point) const;
     * @param   indices         optional, pass NULL for non-indexed drawing. If
     *                          present supplies indices for indexed drawing
     *                          with following methods:
     *                              int count() const;
     *                              void writeValue(int i, uint16_t* point) const;
     *                          count returns the number of indices and
     *                          writeValue supplies each index.
     */
    template <typename POS_SRC,
              typename TEX_SRC,
              typename COL_SRC,
              typename IDX_SRC>
    void drawCustomVertices(const GrPaint& paint,
                            GrPrimitiveType primitiveType,
                            const POS_SRC& posSrc,
                            const TEX_SRC* texCoordSrc,
                            const COL_SRC* colorSrc,
                            const IDX_SRC* idxSrc);
    /**
     * To avoid the problem of having to create a typename for NULL parameters,
     * these reduced versions of drawCustomVertices are provided.
     */
    template <typename POS_SRC>
    void drawCustomVertices(const GrPaint& paint,
                            GrPrimitiveType primitiveType,
                            const POS_SRC& posSrc);
    template <typename POS_SRC, typename TEX_SRC>
    void drawCustomVertices(const GrPaint& paint,
                            GrPrimitiveType primitiveType,
                            const POS_SRC& posSrc,
                            const TEX_SRC* texCoordSrc);
    template <typename POS_SRC, typename TEX_SRC, typename COL_SRC>
    void drawCustomVertices(const GrPaint& paint,
                            GrPrimitiveType primitiveType,
                            const POS_SRC& posSrc,
                            const TEX_SRC* texCoordSrc,
                            const COL_SRC* colorSrc);

    ///////////////////////////////////////////////////////////////////////////
    // Misc.

    /**
     * Flags that affect flush() behavior.
     */
    enum FlushBits {
        /**
         * A client may want Gr to bind a GrRenderTarget in the 3D API so that
         * it can be rendered to directly. However, Gr lazily sets state. Simply
         * calling setRenderTarget() followed by flush() without flags may not
         * bind the render target. This flag forces the context to bind the last
         * set render target in the 3D API.
         */
        kForceCurrentRenderTarget_FlushBit   = 0x1,
        /**
         * A client may reach a point where it has partially rendered a frame
         * through a GrContext that it knows the user will never see. This flag
         * causes the flush to skip submission of deferred content to the 3D API
         * during the flush.
         */
        kDiscard_FlushBit                    = 0x2,
    };

    /**
     * Call to ensure all drawing to the context has been issued to the
     * underlying 3D API.
     * @param flagsBitfield     flags that control the flushing behavior. See
     *                          FlushBits.
     */
    void flush(int flagsBitfield = 0);
    
    /**
     * Reads a rectangle of pixels from a render target.
     * @param renderTarget  the render target to read from. NULL means the
     *                      current render target.
     * @param left          left edge of the rectangle to read (inclusive)
     * @param top           top edge of the rectangle to read (inclusive)
     * @param width         width of rectangle to read in pixels.
     * @param height        height of rectangle to read in pixels.
     * @param config        the pixel config of the destination buffer
     * @param buffer        memory to read the rectangle into.
     *
     * @return true if the read succeeded, false if not. The read can fail
     *              because of a unsupported pixel config or because no render
     *              target is currently set.
     */
    bool readRenderTargetPixels(GrRenderTarget* target,
                                int left, int top, int width, int height,
                                GrPixelConfig config, void* buffer);

    /**
     * Reads a rectangle of pixels from a texture.
     * @param texture       the render target to read from.
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
    bool readTexturePixels(GrTexture* target,
                           int left, int top, int width, int height,
                           GrPixelConfig config, void* buffer);

    /**
     *  Copy the src pixels [buffer, stride, pixelconfig] into the current
     *  render-target at the specified rectangle.
     */
    void writePixels(int left, int top, int width, int height,
                     GrPixelConfig, const void* buffer, size_t stride);

    ///////////////////////////////////////////////////////////////////////////
    // Helpers

    class AutoRenderTarget : ::GrNoncopyable {
    public:
        AutoRenderTarget(GrContext* context, GrRenderTarget* target) {
            fContext = NULL;
            fPrevTarget = context->getRenderTarget();
            if (fPrevTarget != target) {
                context->setRenderTarget(target);
                fContext = context;
            }
        }
        ~AutoRenderTarget() {
            if (fContext) {
                fContext->setRenderTarget(fPrevTarget);
            }
        }
    private:
        GrContext*      fContext;
        GrRenderTarget* fPrevTarget;
    };


    ///////////////////////////////////////////////////////////////////////////
    // Functions intended for internal use only.
    GrGpu* getGpu() { return fGpu; }
    GrFontCache* getFontCache() { return fFontCache; }
    GrDrawTarget* getTextTarget(const GrPaint& paint);
    void flushText();
    const GrIndexBuffer* getQuadIndexBuffer() const;
    void resetStats();
    const GrGpuStats& getStats() const;
    void printStats() const;

private:
    // used to keep track of when we need to flush the draw buffer
    enum DrawCategory {
        kBuffered_DrawCategory,      // last draw was inserted in draw buffer
        kUnbuffered_DrawCategory,    // last draw was not inserted in the draw buffer
        kText_DrawCategory           // text context was last to draw
    };
    DrawCategory fLastDrawCategory;

    GrGpu*          fGpu;
    GrTextureCache* fTextureCache;
    GrFontCache*    fFontCache;

    GrPathRenderer*         fCustomPathRenderer;
    GrDefaultPathRenderer   fDefaultPathRenderer;

    GrVertexBufferAllocPool*    fDrawBufferVBAllocPool;
    GrIndexBufferAllocPool*     fDrawBufferIBAllocPool;
    GrInOrderDrawBuffer*        fDrawBuffer;

    GrIndexBuffer*              fAAFillRectIndexBuffer;
    GrIndexBuffer*              fAAStrokeRectIndexBuffer;
    int                         fMaxOffscreenAASize;

    GrContext(GrGpu* gpu);

    void fillAARect(GrDrawTarget* target,
                    const GrPaint& paint,
                    const GrRect& devRect);

    void strokeAARect(GrDrawTarget* target,
                      const GrPaint& paint,
                      const GrRect& devRect,
                      const GrVec& devStrokeSize);

    inline int aaFillRectIndexCount() const;
    GrIndexBuffer* aaFillRectIndexBuffer();

    inline int aaStrokeRectIndexCount() const;
    GrIndexBuffer* aaStrokeRectIndexBuffer();

    void setupDrawBuffer();

    void flushDrawBuffer();

    static void SetPaint(const GrPaint& paint, GrDrawTarget* target);

    bool finalizeTextureKey(GrTextureKey*, 
                            const GrSamplerState&,
                            bool keyless) const;

    GrDrawTarget* prepareToDraw(const GrPaint& paint, DrawCategory drawType);

    void drawClipIntoStencil();

    GrPathRenderer* getPathRenderer(const GrDrawTarget*, const GrPath&, GrPathFill);

    struct OffscreenRecord;

    // determines whether offscreen AA should be applied
    bool doOffscreenAA(GrDrawTarget* target, 
                       const GrPaint& paint,
                       bool isLines) const;

    // attempts to setup offscreen AA. All paint state must be transferred to
    // target by the time this is called.
    bool prepareForOffscreenAA(GrDrawTarget* target,
                               bool requireStencil,
                               const GrIRect& boundRect,
                               GrPathRenderer* pr,
                               OffscreenRecord* record);

    // sets up target to draw coverage to the supersampled render target
    void setupOffscreenAAPass1(GrDrawTarget* target,
                               const GrIRect& boundRect,
                               int tileX, int tileY,
                               OffscreenRecord* record);

    // sets up target to sample coverage of supersampled render target back
    // to the main render target using stage kOffscreenStage.
    void doOffscreenAAPass2(GrDrawTarget* target,
                            const GrPaint& paint,
                            const GrIRect& boundRect,
                            int tileX, int tileY,
                            OffscreenRecord* record);

    // restored the draw target state and releases offscreen target to cache
    void cleanupOffscreenAA(GrDrawTarget* target,
                            GrPathRenderer* pr,
                            OffscreenRecord* record);
    
    // computes vertex layout bits based on the paint. If paint expresses
    // a texture for a stage, the stage coords will be bound to postitions
    // unless hasTexCoords[s]==true in which case stage s's input coords
    // are bound to tex coord index s. hasTexCoords == NULL is a shortcut
    // for an array where all the values are false.
    static int PaintStageVertexLayoutBits(
                                    const GrPaint& paint,
                                    const bool hasTexCoords[GrPaint::kTotalStages]);
    
};

/**
 *  Save/restore the view-matrix in the context.
 */
class GrAutoMatrix : GrNoncopyable {
public:
    GrAutoMatrix(GrContext* ctx) : fContext(ctx) {
        fMatrix = ctx->getMatrix();
    }
    GrAutoMatrix(GrContext* ctx, const GrMatrix& matrix) : fContext(ctx) {
        fMatrix = ctx->getMatrix();
        ctx->setMatrix(matrix);
    }
    ~GrAutoMatrix() {
        fContext->setMatrix(fMatrix);
    }

private:
    GrContext*  fContext;
    GrMatrix    fMatrix;
};

#endif

#include "GrContext_impl.h"

