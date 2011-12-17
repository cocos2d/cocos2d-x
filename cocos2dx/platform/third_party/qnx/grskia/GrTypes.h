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


#ifndef GrTypes_DEFINED
#define GrTypes_DEFINED

#include "SkTypes.h"
#include "GrConfig.h"

////////////////////////////////////////////////////////////////////////////////

/**
 * Defines overloaded bitwise operators to make it easier to use an enum as a
 * bitfield.
 */
#define GR_MAKE_BITFIELD_OPS(X) \
    static inline X operator | (X a, X b) { \
        return (X) (+a | +b); \
    } \
    \
    static inline X operator & (X a, X b) { \
        return (X) (+a & +b); \
    } \
    template <typename T> \
    static inline X operator & (T a, X b) { \
        return (X) (+a & +b); \
    } \
    template <typename T> \
    static inline X operator & (X a, T b) { \
        return (X) (+a & +b); \
    } \

////////////////////////////////////////////////////////////////////////////////


/**
 *  Macro to round n up to the next multiple of 4, or return it unchanged if
 *  n is already a multiple of 4
 */
#define GrALIGN4(n)     SkAlign4(n)
#define GrIsALIGN4(n)   (((n) & 3) == 0)

template <typename T> const T& GrMin(const T& a, const T& b) {
	return (a < b) ? a : b;
}

template <typename T> const T& GrMax(const T& a, const T& b) {
	return (b < a) ? a : b;
}

// compile time versions of min/max
#define GR_CT_MAX(a, b) (((b) < (a)) ? (a) : (b))
#define GR_CT_MIN(a, b) (((b) < (a)) ? (b) : (a))

/**
 *  divide, rounding up
 */
static inline int32_t GrIDivRoundUp(int x, int y) {
    GrAssert(y > 0);
    return (x + (y-1)) / y;
}
static inline uint32_t GrUIDivRoundUp(uint32_t x, uint32_t y) {
    return (x + (y-1)) / y;
}
static inline size_t GrSizeDivRoundUp(size_t x, uint32_t y) {
    return (x + (y-1)) / y;
}

/**
 *  align up
 */
static inline uint32_t GrUIAlignUp(uint32_t x, uint32_t alignment) {
    return GrUIDivRoundUp(x, alignment) * alignment;
}
static inline uint32_t GrSizeAlignUp(size_t x, uint32_t alignment) {
    return GrSizeDivRoundUp(x, alignment) * alignment;
}

/**
 * amount of pad needed to align up
 */
static inline uint32_t GrUIAlignUpPad(uint32_t x, uint32_t alignment) {
    return (alignment - x % alignment) % alignment;
}
static inline size_t GrSizeAlignUpPad(size_t x, uint32_t alignment) {
    return (alignment - x % alignment) % alignment;
}

/**
 *  align down
 */
static inline uint32_t GrUIAlignDown(uint32_t x, uint32_t alignment) {
    return (x / alignment) * alignment;
}
static inline uint32_t GrSizeAlignDown(size_t x, uint32_t alignment) {
    return (x / alignment) * alignment;
}

/**
 *  Count elements in an array
 */
#define GR_ARRAY_COUNT(array)  SK_ARRAY_COUNT(array)

//!< allocate a block of memory, will never return NULL
extern void* GrMalloc(size_t bytes);

//!< free block allocated by GrMalloc. ptr may be NULL
extern void GrFree(void* ptr);

static inline void Gr_bzero(void* dst, size_t size) {
    memset(dst, 0, size);
}

///////////////////////////////////////////////////////////////////////////////

/**
 *  Return the number of leading zeros in n
 */
extern int Gr_clz(uint32_t n);

/**
 *  Return true if n is a power of 2
 */
static inline bool GrIsPow2(unsigned n) {
    return n && 0 == (n & (n - 1));
}

/**
 *  Return the next power of 2 >= n.
 */
static inline uint32_t GrNextPow2(uint32_t n) {
    return n ? (1 << (32 - Gr_clz(n - 1))) : 1;
}

static inline int GrNextPow2(int n) {
    GrAssert(n >= 0); // this impl only works for non-neg.
    return n ? (1 << (32 - Gr_clz(n - 1))) : 1;
}

///////////////////////////////////////////////////////////////////////////////

/**
 *  16.16 fixed point type
 */
typedef int32_t GrFixed;

#if GR_DEBUG

static inline int16_t GrToS16(intptr_t x) {
    GrAssert((int16_t)x == x);
    return (int16_t)x;
}

#else

#define GrToS16(x)  x

#endif


///////////////////////////////////////////////////////////////////////////////

/**
 * Possible 3D APIs that may be used by Ganesh.
 */
enum GrEngine {
    kOpenGL_Shaders_GrEngine,
    kOpenGL_Fixed_GrEngine,
    kDirect3D9_GrEngine
};

/**
 * Engine-specific 3D context handle
 *      Unused for GL.
 *      IDirect3DDevice9* for D3D9
 */
typedef intptr_t GrPlatform3DContext;

///////////////////////////////////////////////////////////////////////////////

/**
 * Type used to describe format of vertices in arrays
 * Values are defined in GrDrawTarget
 */
typedef int GrVertexLayout;

/**
* Geometric primitives used for drawing.
*/
enum GrPrimitiveType {
    kTriangles_PrimitiveType,
    kTriangleStrip_PrimitiveType,
    kTriangleFan_PrimitiveType,
    kPoints_PrimitiveType,
    kLines_PrimitiveType,
    kLineStrip_PrimitiveType
};

static inline bool GrIsPrimTypeLines(GrPrimitiveType type) {
    return kLines_PrimitiveType == type || kLineStrip_PrimitiveType == type;
}

static inline bool GrIsPrimTypeTris(GrPrimitiveType type) {
    return kTriangles_PrimitiveType == type     ||
           kTriangleStrip_PrimitiveType == type ||
           kTriangleFan_PrimitiveType == type;
}

/**
 * Coeffecients for alpha-blending.
 */
enum GrBlendCoeff {
    kZero_BlendCoeff,    //<! 0
    kOne_BlendCoeff,     //<! 1
    kSC_BlendCoeff,      //<! src color
    kISC_BlendCoeff,     //<! one minus src color
    kDC_BlendCoeff,      //<! dst color
    kIDC_BlendCoeff,     //<! one minus dst color
    kSA_BlendCoeff,      //<! src alpha
    kISA_BlendCoeff,     //<! one minus src alpha
    kDA_BlendCoeff,      //<! dst alpha
    kIDA_BlendCoeff,     //<! one minus dst alpha
    kConstC_BlendCoeff,  //<! constant color
    kIConstC_BlendCoeff, //<! one minus constant color
    kConstA_BlendCoeff,  //<! constant color alpha
    kIConstA_BlendCoeff, //<! one minus constant color alpha

    kPublicBlendCoeffCount
};

/**
 *  Formats for masks, used by the font cache.
 *  Important that these are 0-based.
 */
enum GrMaskFormat {
    kA8_GrMaskFormat,    //!< 1-byte per pixel
    kA565_GrMaskFormat,  //!< 2-bytes per pixel
    kA888_GrMaskFormat,  //!< 4-bytes per pixel

    kCount_GrMaskFormats //!< used to allocate arrays sized for mask formats
};

/**
 *  Return the number of bytes-per-pixel for the specified mask format.
 */
static inline int GrMaskFormatBytesPerPixel(GrMaskFormat format) {
    GrAssert((unsigned)format <= 1);
    return (int)format + 1;
}

/**
 * Pixel configurations.
 */
enum GrPixelConfig {
    kUnknown_GrPixelConfig,
    kAlpha_8_GrPixelConfig,
    kIndex_8_GrPixelConfig,
    kRGB_565_GrPixelConfig,
    kRGBA_4444_GrPixelConfig, //!< premultiplied
    kRGBA_8888_GrPixelConfig, //!< premultiplied
    kRGBX_8888_GrPixelConfig, //!< treat the alpha channel as opaque
};

static inline size_t GrBytesPerPixel(GrPixelConfig config) {
    switch (config) {
        case kAlpha_8_GrPixelConfig:
        case kIndex_8_GrPixelConfig:
            return 1;
        case kRGB_565_GrPixelConfig:
        case kRGBA_4444_GrPixelConfig:
            return 2;
        case kRGBA_8888_GrPixelConfig:
        case kRGBX_8888_GrPixelConfig:
            return 4;
        default:
            return 0;
    }
}

static inline bool GrPixelConfigIsOpaque(GrPixelConfig config) {
    switch (config) {
        case kRGB_565_GrPixelConfig:
        case kRGBX_8888_GrPixelConfig:
            return true;
        default:
            return false;
    }
}

static inline bool GrPixelConfigIsAlphaOnly(GrPixelConfig config) {
    switch (config) {
        case kAlpha_8_GrPixelConfig:
            return true;
        default:
            return false;
    }
}

/**
    * Used to control the level of antialiasing available for a rendertarget.
    * Anti-alias quality levels depend on the underlying API/GPU capabilities.
    */
enum GrAALevels {
    kNone_GrAALevel, //<! No antialiasing available.
    kLow_GrAALevel,  //<! Low quality antialiased rendering. Actual
                     //   interpretation is platform-dependent.
    kMed_GrAALevel,  //<! Medium quality antialiased rendering. Actual
                     //   interpretation is platform-dependent.
    kHigh_GrAALevel, //<! High quality antialiased rendering. Actual
                     //   interpretation is platform-dependent.
};

/**
 * Optional bitfield flags that can be passed to createTexture.
 */
enum GrTextureFlags {
    kNone_GrTextureFlags            = 0x0,
    /**
     * Creates a texture that can be rendered to as a GrRenderTarget. Use
     * GrTexture::asRenderTarget() to access.
     */
    kRenderTarget_GrTextureFlagBit  = 0x1,  
    /**
     * By default all render targets have an associated stencil buffer that
     * may be required for path filling. This flag overrides stencil buffer
     * creation.
     * MAKE THIS PRIVATE?
     */
    kNoStencil_GrTextureFlagBit     = 0x2,
    /**
     * Hint that the CPU may modify this texture after creation.
     */
    kDynamicUpdate_GrTextureFlagBit = 0x4,
};

GR_MAKE_BITFIELD_OPS(GrTextureFlags)

enum {
   /**
    *  For Index8 pixel config, the colortable must be 256 entries
    */
    kGrColorTableSize = 256 * 4 //sizeof(GrColor)
};

/**
 * Describes a texture to be created.
 */
struct GrTextureDesc {
    GrTextureFlags         fFlags;  //!< bitfield of TextureFlags
    /**
     * The level of antialiasing available for a rendertarget texture. Only used
     * fFlags contains kRenderTarget_GrTextureFlag.
     */
    GrAALevels             fAALevel;
    int                    fWidth;  //!< Width of the texture
    int                    fHeight; //!< Height of the texture
    /**
     * Format of source data of the texture. Not guaraunteed to be the same as
     * internal format used by 3D API.
     */
    GrPixelConfig          fFormat; 
};

/**
 * Set Operations used to construct clips.
 */
enum GrSetOp {
    kReplace_SetOp,
    kIntersect_SetOp,
    kUnion_SetOp,
    kXor_SetOp,
    kDifference_SetOp,
    kReverseDifference_SetOp,
};

/**
 * Clips are composed from these objects.
 */
enum GrClipType {
    kRect_ClipType,
    kPath_ClipType
};

/**
 * Commands used to describe a path. Each command
 * is accompanied by some number of points.
 */
enum GrPathCmd {
    kMove_PathCmd,      //!< Starts a new subpath at
                        //   at the returned point
                        // 1 point
    kLine_PathCmd,      //!< Adds a line segment
                        // 2 points
    kQuadratic_PathCmd, //!< Adds a quadratic segment
                        // 3 points
    kCubic_PathCmd,     //!< Adds a cubic segment
                        // 4 points
    kClose_PathCmd,     //!< Closes the current subpath
                        //   by connecting a line to the
                        //   starting point.
                        // 0 points
    kEnd_PathCmd        //!< Indicates the end of the last subpath
                        //   when iterating
                        // 0 points.
};

/**
 * Gets the number of points associated with a path command.
 */
static int inline NumPathCmdPoints(GrPathCmd cmd) {
    static const int gNumPoints[] = {
        1, 2, 3, 4, 0, 0
    };
    return gNumPoints[cmd];
}

/**
 * Path filling rules
 */
enum GrPathFill {
    kWinding_PathFill,
    kEvenOdd_PathFill,
    kInverseWinding_PathFill,
    kInverseEvenOdd_PathFill,
    kHairLine_PathFill,

    kPathFillCount
};

static inline GrPathFill NonInvertedFill(GrPathFill fill) {
    static const GrPathFill gNonInvertedFills[] = {
        kWinding_PathFill, // kWinding_PathFill
        kEvenOdd_PathFill, // kEvenOdd_PathFill
        kWinding_PathFill, // kInverseWinding_PathFill
        kEvenOdd_PathFill, // kInverseEvenOdd_PathFill
        kHairLine_PathFill,// kHairLine_PathFill
    };
    GR_STATIC_ASSERT(0 == kWinding_PathFill);
    GR_STATIC_ASSERT(1 == kEvenOdd_PathFill);
    GR_STATIC_ASSERT(2 == kInverseWinding_PathFill);
    GR_STATIC_ASSERT(3 == kInverseEvenOdd_PathFill);
    GR_STATIC_ASSERT(4 == kHairLine_PathFill);
    GR_STATIC_ASSERT(5 == kPathFillCount);
    return gNonInvertedFills[fill];
}

static inline bool IsFillInverted(GrPathFill fill) {
    static const bool gIsFillInverted[] = {
        false, // kWinding_PathFill
        false, // kEvenOdd_PathFill
        true,  // kInverseWinding_PathFill
        true,  // kInverseEvenOdd_PathFill
        false, // kHairLine_PathFill
    };
    GR_STATIC_ASSERT(0 == kWinding_PathFill);
    GR_STATIC_ASSERT(1 == kEvenOdd_PathFill);
    GR_STATIC_ASSERT(2 == kInverseWinding_PathFill);
    GR_STATIC_ASSERT(3 == kInverseEvenOdd_PathFill);
    GR_STATIC_ASSERT(4 == kHairLine_PathFill);
    GR_STATIC_ASSERT(5 == kPathFillCount);
    return gIsFillInverted[fill];
}

/**
 * Hints provided about a path's convexity (or lack thereof).
 */
enum GrConvexHint {
    kNone_ConvexHint,                         //<! No hint about convexity
                                              //   of the path
    kConvex_ConvexHint,                       //<! Path is one convex piece
    kNonOverlappingConvexPieces_ConvexHint,   //<! Multiple convex pieces,
                                              //   pieces are known to be
                                              //   disjoint
    kSameWindingConvexPieces_ConvexHint,      //<! Multiple convex pieces,
                                              //   may or may not intersect,
                                              //   either all wind cw or all
                                              //   wind ccw.
    kConcave_ConvexHint                       //<! Path is known to be
                                              //   concave
};

///////////////////////////////////////////////////////////////////////////////

enum GrPlatformSurfaceType {
    /**
     * Specifies that the object being created is a render target.
     */
    kRenderTarget_GrPlatformSurfaceType,
    /**
     * Specifies that the object being created is a texture.
     */
    kTexture_GrPlatformSurfaceType,
    /**
     * Specifies that the object being created is a texture and a render
     * target.
     */
    kTextureRenderTarget_GrPlatformSurfaceType,
};

enum GrPlatformRenderTargetFlags {
    kNone_GrPlatformRenderTargetFlagBit             = 0x0,
    /**
     * Specifies that the object being created is multisampled.
     */
    kIsMultisampled_GrPlatformRenderTargetFlagBit   = 0x1,
    /**
     * Gives permission to Gr to perform the downsample-resolve of a
     * multisampled render target. If this is not set then read pixel
     * operations may fail. If the object is both a texture and render target
     * then this *must* be set. Otherwise, if the client wants do its own
     * resolves it must create separate GrRenderTarget and GrTexture objects
     * and insert appropriate flushes and resolves betweeen data hazards.
     * GrRenderTarget has a flagForResolve()
     */
    kGrCanResolve_GrPlatformRenderTargetFlagBit     = 0x2,
};

GR_MAKE_BITFIELD_OPS(GrPlatformRenderTargetFlags)

// opaque type for 3D API object handles
typedef intptr_t GrPlatform3DObject;

/**
 * Description of platform surface to create. See below for GL example.
 */
struct GrPlatformSurfaceDesc {
    GrPlatformSurfaceType           fSurfaceType;   // type of surface to create
    /**
     * Flags for kRenderTarget and kTextureRenderTarget surface types
     */
    GrPlatformRenderTargetFlags     fRenderTargetFlags;

    int                             fWidth;         // width in pixels
    int                             fHeight;        // height in pixels
    GrPixelConfig                   fConfig;        // color format
    /**
     * Number of per sample stencil buffer. Only relevant if kIsRenderTarget is
     * set in fFlags.
     */
    int                             fStencilBits;
    /**
     * Texture object in 3D API. Only relevant if fSurfaceType is kTexture or
     * kTextureRenderTarget.
     * GL: this is a texture object (glGenTextures)
     */
    GrPlatform3DObject              fPlatformTexture;
    /**
     * Render target object in 3D API. Only relevant if fSurfaceType is
     * kRenderTarget or kTextureRenderTarget
     * GL: this is a FBO object (glGenFramebuffers)
     */
    GrPlatform3DObject              fPlatformRenderTarget;
    /**
     * 3D API object used as destination of resolve. Only relevant if
     * fSurfaceType is kRenderTarget or kTextureRenderTarget and
     * kGrCanResolve is set in fRenderTargetFlags.
     * fFlags.
     * GL: this is a FBO object (glGenFramebuffers)
     */
    GrPlatform3DObject              fPlatformResolveDestination;

    void reset() { memset(this, 0, sizeof(GrPlatformSurfaceDesc)); }
};

/**
 * Example of how to wrap render-to-texture-with-MSAA GL objects with a GrPlatformSurace
 *
 * GLint colorBufferID;
 * glGenRenderbuffers(1, &colorID);
 * glBindRenderbuffer(GL_RENDERBUFFER, colorBufferID);
 * glRenderbufferStorageMultisample(GL_RENDERBUFFER, S, GL_RGBA, W, H);
 *
 * GLint stencilBufferID;
 * glGenRenderBuffers(1, &stencilBufferID);
 * glBindRenderbuffer(GL_RENDERBUFFER, stencilBufferID);
 * glRenderbufferStorageMultisample(GL_RENDERBUFFER, S, GL_STENCIL_INDEX8, W, H);
 *
 * GLint drawFBOID;
 * glGenFramebuffers(1, &drawFBOID);
 * glBindFramebuffer(GL_FRAMEBUFFER, drawFBOID);
 * glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorBufferID);
 * glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, stencilBufferID);
 *
 * GLint textureID;
 * glGenTextures(1, &textureID);
 * glBindTexture(GL_TEXTURE_2D, textureID);
 * glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, ...);
 *
 * GLint readFBOID;
 * glGenFramebuffers(1, &readFBOID);
 * glBindFramebuffer(GL_FRAMEBUFFER, readFBOID);
 * glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureID, 0);
 *
 * GrPlatformSurfaceDesc renderTargetTextureDesc;
 * renderTargetTextureDesc.fSurfaceType       = kTextureRenderTarget_GrPlatformSurfaceType;
 * renderTargetTextureDesc.fRenderTargetFlags = (kIsMultisampled_GrPlatformRenderTargetFlagBit | kGrCanResolve_GrPlatformRenderTargetFlagBit);
 * renderTargetTextureDesc.fWidth = W;
 * renderTargetTextureDesc.fHeight = H;
 * renderTargetTextureDesc.fConfig = kRGBA_8888_GrPixelConfig
 * renderTargetTextureDesc.fStencilBits = 8;
 * renderTargetTextureDesc.fPlatformTexture = textureID;
 * renderTargetTextureDesc.fPlatformRenderTarget = drawFBOID;
 * renderTargetTextureDesc.fPlatformResolveDestination = readFBOID;
 *
 * GrTexture* texture = static_cast<GrTexture*>(grContext->createPlatrformSurface(renderTargetTextureDesc));
 */


///////////////////////////////////////////////////////////////////////////////

// this is included only to make it easy to use this debugging facility
#include "GrInstanceCounter.h"

#endif
