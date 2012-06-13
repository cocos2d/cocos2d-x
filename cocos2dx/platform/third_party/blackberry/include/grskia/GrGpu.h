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

#ifndef GrGpu_DEFINED
#define GrGpu_DEFINED

#include "GrDrawTarget.h"
#include "GrPathRenderer.h"
#include "GrRect.h"
#include "GrRefCnt.h"
#include "GrTexture.h"

class GrContext;
class GrIndexBufferAllocPool;
class GrResource;
class GrVertexBufferAllocPool;

/**
 * Gpu usage statistics.
 */
struct GrGpuStats {
    uint32_t fVertexCnt;  //<! Number of vertices drawn
    uint32_t fIndexCnt;   //<! Number of indices drawn
    uint32_t fDrawCnt;    //<! Number of draws

    uint32_t fProgChngCnt;//<! Number of program changes (N/A for fixed)

    /*
        *  Number of times the texture is set in 3D API
        */
    uint32_t fTextureChngCnt;
    /*
        *  Number of times the render target is set in 3D API
        */
    uint32_t fRenderTargetChngCnt;
    /*
        *  Number of textures created (includes textures that are rendertargets).
        */
    uint32_t fTextureCreateCnt;
    /*
        *  Number of rendertargets created.
        */
    uint32_t fRenderTargetCreateCnt;
};

class GrGpu : public GrDrawTarget {

public:
    /**
     * Additional blend coeffecients for dual source blending, not exposed
     * through GrPaint/GrContext.
     */
    enum ExtendedBlendCoeffs {
        // source 2 refers to second output color when
        // using dual source blending.
        kS2C_BlendCoeff = kPublicBlendCoeffCount,
        kIS2C_BlendCoeff,
        kS2A_BlendCoeff,
        kIS2A_BlendCoeff,

        kTotalBlendCoeffCount
    };

    /**
     *  Create an instance of GrGpu that matches the specified Engine backend.
     *  If the requested engine is not supported (at compile-time or run-time)
     *  this returns NULL.
     */
    static GrGpu* Create(GrEngine, GrPlatform3DContext context3D);

    ////////////////////////////////////////////////////////////////////////////

    GrGpu();
    virtual ~GrGpu();

    // The GrContext sets itself as the owner of this Gpu object
    void setContext(GrContext* context) {
        GrAssert(NULL == fContext); 
        fContext = context;
    }
    GrContext* getContext() { return fContext; }
    const GrContext* getContext() const { return fContext; }

    /**
     * The GrGpu object normally assumes that no outsider is setting state
     * within the underlying 3D API's context/device/whatever. This call informs
     * the GrGpu that the state was modified and it shouldn't make assumptions
     * about the state.
     */
    void markContextDirty() { fContextIsDirty = true; }

    void unimpl(const char[]);

    /**
     * Creates a texture object. If desc width or height is not a power of
     * two but underlying API requires a power of two texture then srcData
     * will be embedded in a power of two texture. The extra width and height
     * is filled as though srcData were rendered clamped into the texture.
     *
     * If kRenderTarget_TextureFlag is specified the GrRenderTarget is
     * accessible via GrTexture::asRenderTarget(). The texture will hold a ref
     * on the render target until its releaseRenderTarget() is called or it is
     * destroyed.
     *
     * @param desc        describes the texture to be created.
     * @param srcData     texel data to load texture. Begins with full-size
     *                    palette data for paletted textures. Contains width*
     *                    height texels. If NULL texture data is uninitialized.
     *
     * @return    The texture object if successful, otherwise NULL.
     */
    GrTexture* createTexture(const GrTextureDesc& desc,
                             const void* srcData, size_t rowBytes);

    GrResource* createPlatformSurface(const GrPlatformSurfaceDesc& desc);

    /**
     * Reads the current target object (e.g. FBO or IDirect3DSurface9*) and
     * viewport state from the underlying 3D API and wraps it in a
     * GrRenderTarget. The GrRenderTarget will not attempt to delete/destroy the
     * underlying object in its destructor and it is up to caller to guarantee
     * that it remains valid while the GrRenderTarget is used.
     *
     * @return the newly created GrRenderTarget
     */
    GrRenderTarget* createRenderTargetFrom3DApiState();

    /**
     * Creates a vertex buffer.
     *
     * @param size    size in bytes of the vertex buffer
     * @param dynamic hints whether the data will be frequently changed
     *                by either GrVertexBuffer::lock or
     *                GrVertexBuffer::updateData.
     *
     * @return    The vertex buffer if successful, otherwise NULL.
     */
    GrVertexBuffer* createVertexBuffer(uint32_t size, bool dynamic);

    /**
     * Creates an index buffer.
     *
     * @param size    size in bytes of the index buffer
     * @param dynamic hints whether the data will be frequently changed
     *                by either GrIndexBuffer::lock or
     *                GrIndexBuffer::updateData.
     *
     * @return The index buffer if successful, otherwise NULL.
     */
    GrIndexBuffer* createIndexBuffer(uint32_t size, bool dynamic);

    /**
     * Are 8 bit paletted textures supported.
     *
     * @return    true if 8bit palette textures are supported, false otherwise
     */
    bool supports8BitPalette() const { return f8bitPaletteSupport; }

    /**
     * returns true if two sided stenciling is supported. If false then only
     * the front face values of the GrStencilSettings
     * @return    true if only a single stencil pass is needed.
     */
    bool supportsTwoSidedStencil() const
                                        { return fTwoSidedStencilSupport; }

    /**
     * returns true if stencil wrap is supported. If false then
     * kIncWrap_StencilOp and kDecWrap_StencilOp are treated as
     * kIncClamp_StencilOp and kDecClamp_StencilOp, respectively.
     * @return    true if stencil wrap ops are supported.
     */
    bool supportsStencilWrapOps() const
                                        { return fStencilWrapOpsSupport; }

    /**
     * Checks whether locking vertex and index buffers is supported.
     *
     * @return true if locking is supported.
     */
    bool supportsBufferLocking() const { return fBufferLockSupport; }

    /**
     * Does the 3D API support anti-aliased lines. If so then line primitive
     * types will use this functionality when the AA state flag is set.
     */
    bool supportsAALines() const { return fAALineSupport; }

    /**
     * Does the subclass support GrSamplerState::k4x4Downsample_Filter
     */
    bool supports4x4DownsampleFilter() const { return f4X4DownsampleFilterSupport; }

    /**
     * Does this instance support dual-source blending? Required for proper
     * blending with partial coverage with certain blend modes (dst coeff is
     * not 1, ISA, or ISC)
     */
    bool supportsDualSourceBlending() const { 
        return fDualSourceBlendingSupport; 
    }

    /**
     * Gets the minimum width of a render target. If a texture/rt is created
     * with a width less than this size the GrGpu object will clamp it to this
     * value.
     */
    int minRenderTargetWidth() const { return fMinRenderTargetWidth; }

    /**
     * Gets the minimum width of a render target. If a texture/rt is created
     * with a height less than this size the GrGpu object will clamp it to this
     * value.
     */
    int minRenderTargetHeight() const  { return fMinRenderTargetHeight; }
    
    /**
     * Reports whether full scene anti-aliasing is supported.
     */
    bool supportsFullsceneAA() const { return fFSAASupport; }

    /**
     * Returns true if NPOT textures can be created
     *
     * @return    true if NPOT textures can be created
     */
    bool npotTextureSupport() const { return fNPOTTextureSupport; }

    /**
     * Returns true if NPOT textures can be repeat/mirror tiled.
     *
     * @return    true if NPOT textures can be tiled
     */
    bool npotTextureTileSupport() const { return fNPOTTextureTileSupport; }

    /**
     * Returns true if a NPOT texture can be a rendertarget
     *
     * @return    the true if NPOT texture/rendertarget can be created.
     */
    bool npotRenderTargetSupport() const { return fNPOTRenderTargetSupport; }

    /**
     * Gets the largest allowed width and height of a texture.
     */
    int maxTextureSize() const { return fMaxTextureSize; }
    /**
     * Gets the largest allowed width and height of a render target.
     */
    int maxRenderTargetSize() const { return fMaxRenderTargetSize; }

    int maxRenderTargetCount() const { return fMaxRenderTargetCnt; }

    int renderTargetCount() const { return fRenderTargetCnt; }

    virtual void clear(const GrIRect* rect, GrColor color);

    /**
     * Installs a path renderer that will be used to draw paths that are
     * part of the clip.
     */
    void setClipPathRenderer(GrPathRenderer* pathRenderer) {
        GrSafeAssign(fClientPathRenderer, pathRenderer);
    }

    /**
     * Returns an index buffer that can be used to render quads.
     * Six indices per quad: 0, 1, 2, 0, 2, 3, etc.
     * The max number of quads can be queried using GrIndexBuffer::maxQuads().
     * Draw with kTriangles_PrimitiveType
     * @ return the quad index buffer
     */
    const GrIndexBuffer* getQuadIndexBuffer() const;

    /**
     * Returns a vertex buffer with four position-only vertices [(0,0), (1,0),
     * (1,1), (0,1)].
     * @ return unit square vertex buffer
     */
    const GrVertexBuffer* getUnitSquareVertexBuffer() const;

    /**
     * Ensures that the current render target is actually set in the
     * underlying 3D API. Used when client wants to use 3D API to directly
     * render to the RT.
     */
    void forceRenderTargetFlush();

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
    bool readPixels(GrRenderTarget* renderTarget,
                    int left, int top, int width, int height,
                    GrPixelConfig config, void* buffer);

    const GrGpuStats& getStats() const;
    void resetStats();
    void printStats() const;

    /**
     * Called to tell Gpu object that all GrResources have been lost and should
     * be abandoned.
     */
    virtual void abandonResources();

    /**
     * Called to tell Gpu object to release all GrResources.
     */
    void releaseResources();

    /**
     * Add resource to list of resources. Should only be called by GrResource.
     * @param resource  the resource to add.
     */
    void insertResource(GrResource* resource);

    /**
     * Remove resource from list of resources. Should only be called by
     * GrResource.
     * @param resource  the resource to remove.
     */
    void removeResource(GrResource* resource);

protected:
    enum PrivateStateBits {
        kFirstBit = (kLastPublicStateBit << 1),

        kModifyStencilClip_StateBit = kFirstBit, // allows draws to modify
                                                 // stencil bits used for
                                                 // clipping.
    };

    /**
     * Extensions to GrDrawTarget::StateBits to implement stencil clipping
     */
    struct ClipState {
        bool            fClipInStencil;
        bool            fClipIsDirty;
    } fClipState;

    // GrDrawTarget override
    virtual void clipWillBeSet(const GrClip& newClip);

    // prepares clip flushes gpu state before a draw
    bool setupClipAndFlushState(GrPrimitiveType type);

    // Functions used to map clip-respecting stencil tests into normal
    // stencil funcs supported by GPUs.
    static GrStencilFunc ConvertStencilFunc(bool stencilInClip,
                                            GrStencilFunc func);
    static void ConvertStencilFuncAndMask(GrStencilFunc func,
                                          bool clipInStencil,
                                          unsigned int clipBit,
                                          unsigned int userBits,
                                          unsigned int* ref,
                                          unsigned int* mask);

    // stencil settings to clip drawing when stencil clipping is in effect
    // and the client isn't using the stencil test.
    static const GrStencilSettings gClipStencilSettings;

    // defaults to false, subclass can set true to support palleted textures
    bool f8bitPaletteSupport;

    // set by subclass
    bool fNPOTTextureSupport;
    bool fNPOTTextureTileSupport;
    bool fNPOTRenderTargetSupport;
    bool fTwoSidedStencilSupport;
    bool fStencilWrapOpsSupport;
    bool fAALineSupport;
    bool fFSAASupport;
    bool f4X4DownsampleFilterSupport; // supports GrSamplerState::k4x4Downsample_Filter
    bool fDualSourceBlendingSupport;

    // set by subclass to true if index and vertex buffers can be locked, false
    // otherwise.
    bool fBufferLockSupport;

    // set by subclass
    int fMinRenderTargetWidth;
    int fMinRenderTargetHeight;
    int fMaxRenderTargetSize;
    int fMaxTextureSize;
    int fRenderTargetCnt;
    int fMaxRenderTargetCnt;

    GrGpuStats fStats;

    struct GeometryPoolState {
        const GrVertexBuffer* fPoolVertexBuffer;
        int                   fPoolStartVertex;
        
        const GrIndexBuffer*  fPoolIndexBuffer;
        int                   fPoolStartIndex;
    };
    const GeometryPoolState& getGeomPoolState() { 
        return fGeomPoolStateStack.back(); 
    }

    // GrDrawTarget overrides
    virtual bool onReserveVertexSpace(GrVertexLayout vertexLayout,
                                      int vertexCount,
                                      void** vertices);
    virtual bool onReserveIndexSpace(int indexCount, void** indices);
    virtual void releaseReservedVertexSpace();
    virtual void releaseReservedIndexSpace();    
    virtual void onSetVertexSourceToArray(const void* vertexArray,
                                          int vertexCount);
    virtual void onSetIndexSourceToArray(const void* indexArray,
                                         int indexCount);
    virtual void releaseVertexArray();
    virtual void releaseIndexArray();
    virtual void geometrySourceWillPush();
    virtual void geometrySourceWillPop(const GeometrySrcState& restoredState);

    // Helpers for setting up geometry state
    void finalizeReservedVertices();
    void finalizeReservedIndices();

    // overridden by API-specific derived class to handle re-emitting 3D API
    // preample and dirtying state cache.
    virtual void resetContext() = 0;

    // overridden by API-specific derived class to create objects.
    virtual GrTexture* onCreateTexture(const GrTextureDesc& desc,
                                       const void* srcData,
                                       size_t rowBytes) = 0;
    virtual GrResource* onCreatePlatformSurface(const GrPlatformSurfaceDesc& desc) = 0;
    virtual GrRenderTarget* onCreateRenderTargetFrom3DApiState() = 0;
    virtual GrVertexBuffer* onCreateVertexBuffer(uint32_t size,
                                                 bool dynamic) = 0;
    virtual GrIndexBuffer* onCreateIndexBuffer(uint32_t size,
                                               bool dynamic) = 0;

    // overridden by API-specific derivated class to perform the clear and 
    // clearRect. NULL rect means clear whole target.
    virtual void onClear(const GrIRect* rect, GrColor color) = 0;

    // overridden by API-specific derived class to perform the draw call.
    virtual void onGpuDrawIndexed(GrPrimitiveType type,
                                  uint32_t startVertex,
                                  uint32_t startIndex,
                                  uint32_t vertexCount,
                                  uint32_t indexCount) = 0;

    virtual void onGpuDrawNonIndexed(GrPrimitiveType type,
                                     uint32_t vertexCount,
                                     uint32_t numVertices) = 0;

    // overridden by API-specific derived class to perform flush
    virtual void onForceRenderTargetFlush() = 0;

    // overridden by API-specific derived class to perform the read pixels.
    virtual bool onReadPixels(GrRenderTarget* target,
                              int left, int top, int width, int height,
                              GrPixelConfig, void* buffer) = 0;

    // called to program the vertex data, indexCount will be 0 if drawing non-
    // indexed geometry. The subclass may adjust the startVertex and/or
    // startIndex since it may have already accounted for these in the setup.
    virtual void setupGeometry(int* startVertex,
                               int* startIndex,
                               int vertexCount,
                               int indexCount) = 0;


    // The GrGpu typically records the clients requested state and then flushes
    // deltas from previous state at draw time. This function does the
    // API-specific flush of the state
    // returns false if current state is unsupported.
    virtual bool flushGraphicsState(GrPrimitiveType type) = 0;

    // Sets the scissor rect, or disables if rect is NULL.
    virtual void flushScissor(const GrIRect* rect) = 0;

    // GrGpu subclass removes the clip from the stencil buffer
    virtual void clearStencilClip(const GrIRect& rect) = 0;

private:
    GrContext*                  fContext; // not reffed (context refs gpu)

    GrVertexBufferAllocPool*    fVertexPool;

    GrIndexBufferAllocPool*     fIndexPool;
    
    // counts number of uses of vertex/index pool in the geometry stack
    int                         fVertexPoolUseCnt;
    int                         fIndexPoolUseCnt;
    
    enum {
        kPreallocGeomPoolStateStackCnt = 4,
    };
    GrAlignedSTStorage<kPreallocGeomPoolStateStackCnt, 
                       GeometryPoolState>           fGeoSrcStateStackStorage;
    GrTArray<GeometryPoolState, true>               fGeomPoolStateStack;
    
    mutable GrIndexBuffer*      fQuadIndexBuffer; // mutable so it can be
                                                  // created on-demand

    mutable GrVertexBuffer*     fUnitSquareVertexBuffer; // mutable so it can be
                                                         // created on-demand

    GrDefaultPathRenderer*      fDefaultPathRenderer;
    GrPathRenderer*             fClientPathRenderer;

    bool                        fContextIsDirty;

    GrResource*                 fResourceHead;

    // GrDrawTarget overrides
    virtual void onDrawIndexed(GrPrimitiveType type,
                               int startVertex,
                               int startIndex,
                               int vertexCount,
                               int indexCount);
    virtual void onDrawNonIndexed(GrPrimitiveType type,
                                  int startVertex,
                                  int vertexCount);

    // readies the pools to provide vertex/index data.
    void prepareVertexPool();
    void prepareIndexPool();

    // determines the path renderer used to draw a clip path element.
    GrPathRenderer* getClipPathRenderer(const SkPath& path, GrPathFill fill);

    void handleDirtyContext() {
        if (fContextIsDirty) {
            this->resetContext();
            fContextIsDirty = false;
        }
    }

    typedef GrDrawTarget INHERITED;
};

#endif
