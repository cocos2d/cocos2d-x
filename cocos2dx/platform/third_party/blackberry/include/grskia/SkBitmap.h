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

#ifndef SkBitmap_DEFINED
#define SkBitmap_DEFINED

#include "Sk64.h"
#include "SkColor.h"
#include "SkPoint.h"
#include "SkRefCnt.h"

struct SkIRect;
class SkColorTable;
class SkPaint;
class SkPixelRef;
class SkRegion;
class SkFlattenableReadBuffer;
class SkFlattenableWriteBuffer;

// This is an opaque class, not interpreted by skia
class SkGpuTexture;

/** \class SkBitmap

    The SkBitmap class specifies a raster bitmap. A bitmap has an integer width
    and height, and a format (config), and a pointer to the actual pixels.
    Bitmaps can be drawn into a SkCanvas, but they are also used to specify the
    target of a SkCanvas' drawing operations.
    A const SkBitmap exposes getAddr(), which lets a caller write its pixels;
    the constness is considered to apply to the bitmap's configuration, not
    its contents.
*/
class SK_API SkBitmap {
public:
    class Allocator;

    enum Config {
        kNo_Config,         //!< bitmap has not been configured
        /**
         *  1-bit per pixel, (0 is transparent, 1 is opaque)
         *  Valid as a destination (target of a canvas), but not valid as a src.
         *  i.e. you can draw into a 1-bit bitmap, but you cannot draw from one.
         */
        kA1_Config,
        kA8_Config,         //!< 8-bits per pixel, with only alpha specified (0 is transparent, 0xFF is opaque)
        kIndex8_Config,     //!< 8-bits per pixel, using SkColorTable to specify the colors
        kRGB_565_Config,    //!< 16-bits per pixel, (see SkColorPriv.h for packing)
        kARGB_4444_Config,  //!< 16-bits per pixel, (see SkColorPriv.h for packing)
        kARGB_8888_Config,  //!< 32-bits per pixel, (see SkColorPriv.h for packing)
        /**
         *  Custom compressed format, not supported on all platforms.
         *  Cannot be used as a destination (target of a canvas).
         *  i.e. you may be able to draw from one, but you cannot draw into one.
         */
        kRLE_Index8_Config,

        kConfigCount
    };

    /** Default construct creates a bitmap with zero width and height, and no pixels.
        Its config is set to kNo_Config.
    */
    SkBitmap();
    /** Constructor initializes the new bitmap by copying the src bitmap. All fields are copied,
        but ownership of the pixels remains with the src bitmap.
    */
    SkBitmap(const SkBitmap& src);
    /** Decrements our (shared) pixel ownership if needed.
    */
    ~SkBitmap();

    /** Copies the src bitmap into this bitmap. Ownership of the src bitmap's pixels remains
        with the src bitmap.
    */
    SkBitmap& operator=(const SkBitmap& src);
    /** Swap the fields of the two bitmaps. This routine is guaranteed to never fail or throw.
    */
    //  This method is not exported to java.
    void swap(SkBitmap& other);

    /** Return true iff the bitmap has empty dimensions.
    */
    bool empty() const { return 0 == fWidth || 0 == fHeight; }

    /** Return true iff the bitmap has no pixels nor a pixelref. Note: this can
        return true even if the dimensions of the bitmap are > 0 (see empty()).
    */
    bool isNull() const { return NULL == fPixels && NULL == fPixelRef; }

    /** Return the config for the bitmap.
    */
    Config  config() const { return (Config)fConfig; }
    /** DEPRECATED, use config()
    */
    Config  getConfig() const { return this->config(); }
    /** Return the bitmap's width, in pixels.
    */
    int width() const { return fWidth; }
    /** Return the bitmap's height, in pixels.
    */
    int height() const { return fHeight; }
    /** Return the number of bytes between subsequent rows of the bitmap.
    */
    int rowBytes() const { return fRowBytes; }

    /** Return the shift amount per pixel (i.e. 0 for 1-byte per pixel, 1 for
        2-bytes per pixel configs, 2 for 4-bytes per pixel configs). Return 0
        for configs that are not at least 1-byte per pixel (e.g. kA1_Config
        or kNo_Config)
    */
    int shiftPerPixel() const { return fBytesPerPixel >> 1; }

    /** Return the number of bytes per pixel based on the config. If the config
        does not have at least 1 byte per (e.g. kA1_Config) then 0 is returned.
    */
    int bytesPerPixel() const { return fBytesPerPixel; }

    /** Return the rowbytes expressed as a number of pixels (like width and
        height). Note, for 1-byte per pixel configs like kA8_Config, this will
        return the same as rowBytes(). Is undefined for configs that are less
        than 1-byte per pixel (e.g. kA1_Config)
    */
    int rowBytesAsPixels() const { return fRowBytes >> (fBytesPerPixel >> 1); }

    /** Return the address of the pixels for this SkBitmap.
    */
    void* getPixels() const { return fPixels; }

    /** Return the byte size of the pixels, based on the height and rowBytes.
        Note this truncates the result to 32bits. Call getSize64() to detect
        if the real size exceeds 32bits.
    */
    size_t getSize() const { return fHeight * fRowBytes; }

    /** Return the number of bytes from the pointer returned by getPixels()
        to the end of the allocated space in the buffer. Required in
        cases where extractBitmap has been called.
    */
    size_t getSafeSize() const ;

    /** Return the byte size of the pixels, based on the height and rowBytes.
        This routine is slightly slower than getSize(), but does not truncate
        the answer to 32bits.
    */
    Sk64 getSize64() const {
        Sk64 size;
        size.setMul(fHeight, fRowBytes);
        return size;
    }

    /** Same as getSafeSize(), but does not truncate the answer to 32bits.
    */
    Sk64 getSafeSize64() const ;

    /** Returns true if the bitmap is opaque (has no translucent/transparent pixels).
    */
    bool isOpaque() const;
    /** Specify if this bitmap's pixels are all opaque or not. Is only meaningful for configs
        that support per-pixel alpha (RGB32, A1, A8).
    */
    void setIsOpaque(bool);

    /** Reset the bitmap to its initial state (see default constructor). If we are a (shared)
        owner of the pixels, that ownership is decremented.
    */
    void reset();

    /** Given a config and a width, this computes the optimal rowBytes value. This is called automatically
        if you pass 0 for rowBytes to setConfig().
    */
    static int ComputeRowBytes(Config c, int width);

    /** Return the bytes-per-pixel for the specified config. If the config is
        not at least 1-byte per pixel, return 0, including for kNo_Config.
    */
    static int ComputeBytesPerPixel(Config c);

    /** Return the shift-per-pixel for the specified config. If the config is
     not at least 1-byte per pixel, return 0, including for kNo_Config.
     */
    static int ComputeShiftPerPixel(Config c) {
        return ComputeBytesPerPixel(c) >> 1;
    }

    static Sk64 ComputeSize64(Config, int width, int height);
    static size_t ComputeSize(Config, int width, int height);

    /** Set the bitmap's config and dimensions. If rowBytes is 0, then
        ComputeRowBytes() is called to compute the optimal value. This resets
        any pixel/colortable ownership, just like reset().
    */
    void setConfig(Config, int width, int height, int rowBytes = 0);
    /** Use this to assign a new pixel address for an existing bitmap. This
        will automatically release any pixelref previously installed. Only call
        this if you are handling ownership/lifetime of the pixel memory.

        If the bitmap retains a reference to the colortable (assuming it is
        not null) it will take care of incrementing the reference count.

        @param pixels   Address for the pixels, managed by the caller.
        @param ctable   ColorTable (or null) that matches the specified pixels
    */
    void setPixels(void* p, SkColorTable* ctable = NULL);

    /** Copies the bitmap's pixels to the location pointed at by dst and returns
        true if possible, returns false otherwise.

        In the event that the bitmap's stride is equal to dstRowBytes, and if
        it is greater than strictly required by the bitmap's current config
        (this may happen if the bitmap is an extracted subset of another), then
        this function will copy bytes past the eand of each row, excluding the
        last row. No copies are made outside of the declared size of dst,
        however.

        Always returns false for RLE formats.

        @param dst      Location of destination buffer.
        @param dstSize  Size of destination buffer. Must be large enough to hold
                        pixels using indicated stride.
        @param dstRowBytes  Width of each line in the buffer. If -1, uses
                            bitmap's internal stride.
    */
    bool copyPixelsTo(void* const dst, size_t dstSize, int dstRowBytes = -1)
         const;

    /** Copies the pixels at location src to the bitmap's pixel buffer.
        Returns true if copy if possible (bitmap buffer is large enough),
        false otherwise.

        Like copyPixelsTo, this function may write values beyond the end of
        each row, although never outside the defined buffer.

        Always returns false for RLE formats.

        @param src      Location of the source buffer.
        @param srcSize  Height of source buffer in pixels.
        @param srcRowBytes  Width of each line in the buffer. If -1, uses i
                            bitmap's internal stride.
    */
    bool copyPixelsFrom(const void* const src, size_t srcSize,
                        int srcRowBytes = -1);

    /** Use the standard HeapAllocator to create the pixelref that manages the
        pixel memory. It will be sized based on the current width/height/config.
        If this is called multiple times, a new pixelref object will be created
        each time.

        If the bitmap retains a reference to the colortable (assuming it is
        not null) it will take care of incrementing the reference count.

        @param ctable   ColorTable (or null) to use with the pixels that will
                        be allocated. Only used if config == Index8_Config
        @return true if the allocation succeeds. If not the pixelref field of
                     the bitmap will be unchanged.
    */
    bool allocPixels(SkColorTable* ctable = NULL) {
        return this->allocPixels(NULL, ctable);
    }

    /** Use the specified Allocator to create the pixelref that manages the
        pixel memory. It will be sized based on the current width/height/config.
        If this is called multiple times, a new pixelref object will be created
        each time.

        If the bitmap retains a reference to the colortable (assuming it is
        not null) it will take care of incrementing the reference count.

        @param allocator The Allocator to use to create a pixelref that can
                         manage the pixel memory for the current
                         width/height/config. If allocator is NULL, the standard
                         HeapAllocator will be used.
        @param ctable   ColorTable (or null) to use with the pixels that will
                        be allocated. Only used if config == Index8_Config.
                        If it is non-null and the config is not Index8, it will
                        be ignored.
        @return true if the allocation succeeds. If not the pixelref field of
                     the bitmap will be unchanged.
    */
    bool allocPixels(Allocator* allocator, SkColorTable* ctable);

    /** Return the current pixelref object, if any
    */
    SkPixelRef* pixelRef() const { return fPixelRef; }
    /** Return the offset into the pixelref, if any. Will return 0 if there is
        no pixelref installed.
    */
    size_t pixelRefOffset() const { return fPixelRefOffset; }
    /** Assign a pixelref and optional offset. Pixelrefs are reference counted,
        so the existing one (if any) will be unref'd and the new one will be
        ref'd.
    */
    SkPixelRef* setPixelRef(SkPixelRef* pr, size_t offset = 0);

    /** Call this to ensure that the bitmap points to the current pixel address
        in the pixelref. Balance it with a call to unlockPixels(). These calls
        are harmless if there is no pixelref.
    */
    void lockPixels() const;
    /** When you are finished access the pixel memory, call this to balance a
        previous call to lockPixels(). This allows pixelrefs that implement
        cached/deferred image decoding to know when there are active clients of
        a given image.
    */
    void unlockPixels() const;

    /** Call this to be sure that the bitmap is valid enough to be drawn (i.e.
        it has non-null pixels, and if required by its config, it has a
        non-null colortable. Returns true if all of the above are met.
    */
    bool readyToDraw() const {
        return this->getPixels() != NULL &&
               ((this->config() != kIndex8_Config &&
                 this->config() != kRLE_Index8_Config) ||
                       fColorTable != NULL);
    }

    /** Returns the pixelRef's texture, or NULL
     */
    SkGpuTexture* getTexture() const;

    /** Return the bitmap's colortable (if any). Does not affect the colortable's
        reference count.
    */
    SkColorTable* getColorTable() const { return fColorTable; }

    /** Returns a non-zero, unique value corresponding to the pixels in our
        pixelref (or raw pixels set via setPixels). Each time the pixels are
        changed (and notifyPixelsChanged is called), a different generation ID
        will be returned.
    */
    uint32_t getGenerationID() const;

    /** Call this if you have changed the contents of the pixels. This will in-
        turn cause a different generation ID value to be returned from
        getGenerationID().
    */
    void notifyPixelsChanged() const;

    /** Initialize the bitmap's pixels with the specified color+alpha, automatically converting into the correct format
        for the bitmap's config. If the config is kRGB_565_Config, then the alpha value is ignored.
        If the config is kA8_Config, then the r,g,b parameters are ignored.
    */
    void eraseARGB(U8CPU a, U8CPU r, U8CPU g, U8CPU b) const;
    /** Initialize the bitmap's pixels with the specified color+alpha, automatically converting into the correct format
        for the bitmap's config. If the config is kRGB_565_Config, then the alpha value is presumed
        to be 0xFF. If the config is kA8_Config, then the r,g,b parameters are ignored and the
        pixels are all set to 0xFF.
    */
    void eraseRGB(U8CPU r, U8CPU g, U8CPU b) const {
        this->eraseARGB(0xFF, r, g, b);
    }
    /** Initialize the bitmap's pixels with the specified color, automatically converting into the correct format
        for the bitmap's config. If the config is kRGB_565_Config, then the color's alpha value is presumed
        to be 0xFF. If the config is kA8_Config, then only the color's alpha value is used.
    */
    void eraseColor(SkColor c) const {
        this->eraseARGB(SkColorGetA(c), SkColorGetR(c), SkColorGetG(c),
                        SkColorGetB(c));
    }

    /** Scroll (a subset of) the contents of this bitmap by dx/dy. If there are
        no pixels allocated (i.e. getPixels() returns null) the method will
        still update the inval region (if present).

        @param subset The subset of the bitmap to scroll/move. To scroll the
                      entire contents, specify [0, 0, width, height] or just
                      pass null.
        @param dx The amount to scroll in X
        @param dy The amount to scroll in Y
        @param inval Optional (may be null). Returns the area of the bitmap that
                     was scrolled away. E.g. if dx = dy = 0, then inval would
                     be set to empty. If dx >= width or dy >= height, then
                     inval would be set to the entire bounds of the bitmap.
        @return true if the scroll was doable. Will return false if the bitmap
                     uses an unsupported config for scrolling (only kA8,
                     kIndex8, kRGB_565, kARGB_4444, kARGB_8888 are supported).
                     If no pixels are present (i.e. getPixels() returns false)
                     inval will still be updated, and true will be returned.
    */
    bool scrollRect(const SkIRect* subset, int dx, int dy,
                    SkRegion* inval = NULL) const;

    /**
     *  Return the SkColor of the specified pixel.  In most cases this will
     *  require un-premultiplying the color.  Alpha only configs (A1 and A8)
     *  return black with the appropriate alpha set.  The value is undefined
     *  for kNone_Config or if x or y are out of bounds, or if the bitmap
     *  does not have any pixels (or has not be locked with lockPixels()).
     */
    SkColor getColor(int x, int y) const;
    
    /** Returns the address of the specified pixel. This performs a runtime
        check to know the size of the pixels, and will return the same answer
        as the corresponding size-specific method (e.g. getAddr16). Since the
        check happens at runtime, it is much slower than using a size-specific
        version. Unlike the size-specific methods, this routine also checks if
        getPixels() returns null, and returns that. The size-specific routines
        perform a debugging assert that getPixels() is not null, but they do
        not do any runtime checks.
    */
    void* getAddr(int x, int y) const;

    /** Returns the address of the pixel specified by x,y for 32bit pixels.
     *  In debug build, this asserts that the pixels are allocated and locked,
     *  and that the config is 32-bit, however none of these checks are performed
     *  in the release build.
     */
    inline uint32_t* getAddr32(int x, int y) const;

    /** Returns the address of the pixel specified by x,y for 16bit pixels.
     *  In debug build, this asserts that the pixels are allocated and locked,
     *  and that the config is 16-bit, however none of these checks are performed
     *  in the release build.
     */
    inline uint16_t* getAddr16(int x, int y) const;

    /** Returns the address of the pixel specified by x,y for 8bit pixels.
     *  In debug build, this asserts that the pixels are allocated and locked,
     *  and that the config is 8-bit, however none of these checks are performed
     *  in the release build.
     */
    inline uint8_t* getAddr8(int x, int y) const;

    /** Returns the address of the byte containing the pixel specified by x,y
     *  for 1bit pixels.
     *  In debug build, this asserts that the pixels are allocated and locked,
     *  and that the config is 1-bit, however none of these checks are performed
     *  in the release build.
     */
    inline uint8_t* getAddr1(int x, int y) const;

    /** Returns the color corresponding to the pixel specified by x,y for
     *  colortable based bitmaps.
     *  In debug build, this asserts that the pixels are allocated and locked,
     *  that the config is kIndex8, and that the colortable is allocated,
     *  however none of these checks are performed in the release build.
     */
    inline SkPMColor getIndex8Color(int x, int y) const;

    /** Set dst to be a setset of this bitmap. If possible, it will share the
        pixel memory, and just point into a subset of it. However, if the config
        does not support this, a local copy will be made and associated with
        the dst bitmap. If the subset rectangle, intersected with the bitmap's
        dimensions is empty, or if there is an unsupported config, false will be
        returned and dst will be untouched.
        @param dst  The bitmap that will be set to a subset of this bitmap
        @param subset The rectangle of pixels in this bitmap that dst will
                      reference.
        @return true if the subset copy was successfully made.
    */
    bool extractSubset(SkBitmap* dst, const SkIRect& subset) const;

    /** Makes a deep copy of this bitmap, respecting the requested config.
        Returns false if either there is an error (i.e. the src does not have
        pixels) or the request cannot be satisfied (e.g. the src has per-pixel
        alpha, and the requested config does not support alpha).
        @param dst The bitmap to be sized and allocated
        @param c The desired config for dst
        @param allocator Allocator used to allocate the pixelref for the dst
                         bitmap. If this is null, the standard HeapAllocator
                         will be used.
        @return true if the copy could be made.
    */
    bool copyTo(SkBitmap* dst, Config c, Allocator* allocator = NULL) const;

    /** Returns true if this bitmap can be deep copied into the requested config
        by calling copyTo().
     */
    bool canCopyTo(Config newConfig) const;

    bool hasMipMap() const;
    void buildMipMap(bool forceRebuild = false);
    void freeMipMap();

    /** Given scale factors sx, sy, determine the miplevel available in the
        bitmap, and return it (this is the amount to shift matrix iterators
        by). If dst is not null, it is set to the correct level.
    */
    int extractMipLevel(SkBitmap* dst, SkFixed sx, SkFixed sy);

    bool extractAlpha(SkBitmap* dst) const {
        return this->extractAlpha(dst, NULL, NULL, NULL);
    }

    bool extractAlpha(SkBitmap* dst, const SkPaint* paint,
                      SkIPoint* offset) const {
        return this->extractAlpha(dst, paint, NULL, offset);
    }

    /** Set dst to contain alpha layer of this bitmap. If destination bitmap
        fails to be initialized, e.g. because allocator can't allocate pixels
        for it, dst will not be modified and false will be returned.

        @param dst The bitmap to be filled with alpha layer
        @param paint The paint to draw with
        @param allocator Allocator used to allocate the pixelref for the dst
                         bitmap. If this is null, the standard HeapAllocator
                         will be used.
        @param offset If not null, it is set to top-left coordinate to position
                      the returned bitmap so that it visually lines up with the
                      original
    */
    bool extractAlpha(SkBitmap* dst, const SkPaint* paint, Allocator* allocator,
                      SkIPoint* offset) const;

    void flatten(SkFlattenableWriteBuffer&) const;
    void unflatten(SkFlattenableReadBuffer&);

    SkDEBUGCODE(void validate() const;)

    class Allocator : public SkRefCnt {
    public:
        /** Allocate the pixel memory for the bitmap, given its dimensions and
            config. Return true on success, where success means either setPixels
            or setPixelRef was called. The pixels need not be locked when this
            returns. If the config requires a colortable, it also must be
            installed via setColorTable. If false is returned, the bitmap and
            colortable should be left unchanged.
        */
        virtual bool allocPixelRef(SkBitmap*, SkColorTable*) = 0;
    };

    /** Subclass of Allocator that returns a pixelref that allocates its pixel
        memory from the heap. This is the default Allocator invoked by
        allocPixels().
    */
    class HeapAllocator : public Allocator {
    public:
        virtual bool allocPixelRef(SkBitmap*, SkColorTable*);
    };

    class RLEPixels {
    public:
        RLEPixels(int width, int height);
        virtual ~RLEPixels();

        uint8_t* packedAtY(int y) const {
            SkASSERT((unsigned)y < (unsigned)fHeight);
            return fYPtrs[y];
        }

        // called by subclasses during creation
        void setPackedAtY(int y, uint8_t* addr) {
            SkASSERT((unsigned)y < (unsigned)fHeight);
            fYPtrs[y] = addr;
        }

    private:
        uint8_t** fYPtrs;
        int       fHeight;
    };

private:
    struct MipMap;
    mutable MipMap* fMipMap;

    mutable SkPixelRef* fPixelRef;
    mutable size_t      fPixelRefOffset;
    mutable int         fPixelLockCount;
    // either user-specified (in which case it is not treated as mutable)
    // or a cache of the returned value from fPixelRef->lockPixels()
    mutable void*       fPixels;
    mutable SkColorTable* fColorTable;    // only meaningful for kIndex8
    // When there is no pixel ref (setPixels was called) we still need a
    // gen id for SkDevice implementations that may cache a copy of the
    // pixels (e.g. as a gpu texture)
    mutable int         fRawPixelGenerationID;

    enum Flags {
        kImageIsOpaque_Flag  = 0x01
    };

    uint32_t    fRowBytes;
    uint32_t    fWidth;
    uint32_t    fHeight;
    uint8_t     fConfig;
    uint8_t     fFlags;
    uint8_t     fBytesPerPixel; // based on config

    /* Internal computations for safe size.
    */
    static Sk64 ComputeSafeSize64(Config config,
                                  uint32_t width,
                                  uint32_t height,
                                  uint32_t rowBytes);
    static size_t ComputeSafeSize(Config   config,
                                  uint32_t width,
                                  uint32_t height,
                                  uint32_t rowBytes);

    /*  Unreference any pixelrefs or colortables
    */
    void freePixels();
    void updatePixelsFromRef() const;

    static SkFixed ComputeMipLevel(SkFixed sx, SkFixed dy);
};

/** \class SkColorTable

    SkColorTable holds an array SkPMColors (premultiplied 32-bit colors) used by
    8-bit bitmaps, where the bitmap bytes are interpreted as indices into the colortable.
*/
class SkColorTable : public SkRefCnt {
public:
    /** Makes a deep copy of colors.
     */
    SkColorTable(const SkColorTable& src);
    /** Preallocates the colortable to have 'count' colors, which
     *  are initially set to 0.
    */
    explicit SkColorTable(int count);
    explicit SkColorTable(SkFlattenableReadBuffer&);
    SkColorTable(const SkPMColor colors[], int count);
    virtual ~SkColorTable();

    enum Flags {
        kColorsAreOpaque_Flag   = 0x01  //!< if set, all of the colors in the table are opaque (alpha==0xFF)
    };
    /** Returns the flag bits for the color table. These can be changed with setFlags().
    */
    unsigned getFlags() const { return fFlags; }
    /** Set the flags for the color table. See the Flags enum for possible values.
    */
    void    setFlags(unsigned flags);

    bool isOpaque() const { return (fFlags & kColorsAreOpaque_Flag) != 0; }
    void setIsOpaque(bool isOpaque);

    /** Returns the number of colors in the table.
    */
    int count() const { return fCount; }

    /** Returns the specified color from the table. In the debug build, this asserts that
        the index is in range (0 <= index < count).
    */
    SkPMColor operator[](int index) const {
        SkASSERT(fColors != NULL && (unsigned)index < fCount);
        return fColors[index];
    }

    /** Specify the number of colors in the color table. This does not initialize the colors
        to any value, just allocates memory for them. To initialize the values, either call
        setColors(array, count), or follow setCount(count) with a call to
        lockColors()/{set the values}/unlockColors(true).
    */
//    void    setColors(int count) { this->setColors(NULL, count); }
//    void    setColors(const SkPMColor[], int count);

    /** Return the array of colors for reading and/or writing. This must be
        balanced by a call to unlockColors(changed?), telling the colortable if
        the colors were changed during the lock.
    */
    SkPMColor* lockColors() {
        SkDEBUGCODE(fColorLockCount += 1;)
        return fColors;
    }
    /** Balancing call to lockColors(). If the colors have been changed, pass true.
    */
    void unlockColors(bool changed);

    /** Similar to lockColors(), lock16BitCache() returns the array of
        RGB16 colors that mirror the 32bit colors. However, this function
        will return null if kColorsAreOpaque_Flag is not set.
        Also, unlike lockColors(), the returned array here cannot be modified.
    */
    const uint16_t* lock16BitCache();
    /** Balancing call to lock16BitCache().
    */
    void unlock16BitCache() {
        SkASSERT(f16BitCacheLockCount > 0);
        SkDEBUGCODE(f16BitCacheLockCount -= 1);
    }

    void flatten(SkFlattenableWriteBuffer&) const;

private:
    SkPMColor*  fColors;
    uint16_t*   f16BitCache;
    uint16_t    fCount;
    uint8_t     fFlags;
    SkDEBUGCODE(int fColorLockCount;)
    SkDEBUGCODE(int f16BitCacheLockCount;)

    void inval16BitCache();
};

class SkAutoLockPixels {
public:
    SkAutoLockPixels(const SkBitmap& bitmap) : fBitmap(bitmap) {
        bitmap.lockPixels();
    }
    ~SkAutoLockPixels() {
        fBitmap.unlockPixels();
    }

private:
    const SkBitmap& fBitmap;
};

/** Helper class that performs the lock/unlockColors calls on a colortable.
    The destructor will call unlockColors(false) if it has a bitmap's colortable
*/
class SkAutoLockColors : public SkNoncopyable {
public:
    /** Initialize with no bitmap. Call lockColors(bitmap) to lock bitmap's
        colortable
     */
    SkAutoLockColors() : fCTable(NULL), fColors(NULL) {}
    /** Initialize with bitmap, locking its colortable if present
     */
    explicit SkAutoLockColors(const SkBitmap& bm) {
        fCTable = bm.getColorTable();
        fColors = fCTable ? fCTable->lockColors() : NULL;
    }
    /** Initialize with a colortable (may be null)
     */
    explicit SkAutoLockColors(SkColorTable* ctable) {
        fCTable = ctable;
        fColors = ctable ? ctable->lockColors() : NULL;
    }
    ~SkAutoLockColors() {
        if (fCTable) {
            fCTable->unlockColors(false);
        }
    }

    /** Return the currently locked colors, or NULL if no bitmap's colortable
        is currently locked.
    */
    const SkPMColor* colors() const { return fColors; }

    /** Locks the table and returns is colors (assuming ctable is not null) and
        unlocks the previous table if one was present
     */
    const SkPMColor* lockColors(SkColorTable* ctable) {
        if (fCTable) {
            fCTable->unlockColors(false);
        }
        fCTable = ctable;
        fColors = ctable ? ctable->lockColors() : NULL;
        return fColors;
    }

    const SkPMColor* lockColors(const SkBitmap& bm) {
        return this->lockColors(bm.getColorTable());
    }

private:
    SkColorTable*    fCTable;
    const SkPMColor* fColors;
};

///////////////////////////////////////////////////////////////////////////////

inline uint32_t* SkBitmap::getAddr32(int x, int y) const {
    SkASSERT(fPixels);
    SkASSERT(fConfig == kARGB_8888_Config);
    SkASSERT((unsigned)x < fWidth && (unsigned)y < fHeight);
    return (uint32_t*)((char*)fPixels + y * fRowBytes + (x << 2));
}

inline uint16_t* SkBitmap::getAddr16(int x, int y) const {
    SkASSERT(fPixels);
    SkASSERT(fConfig == kRGB_565_Config || fConfig == kARGB_4444_Config);
    SkASSERT((unsigned)x < fWidth && (unsigned)y < fHeight);
    return (uint16_t*)((char*)fPixels + y * fRowBytes + (x << 1));
}

inline uint8_t* SkBitmap::getAddr8(int x, int y) const {
    SkASSERT(fPixels);
    SkASSERT(fConfig == kA8_Config || fConfig == kIndex8_Config);
    SkASSERT((unsigned)x < fWidth && (unsigned)y < fHeight);
    return (uint8_t*)fPixels + y * fRowBytes + x;
}

inline SkPMColor SkBitmap::getIndex8Color(int x, int y) const {
    SkASSERT(fPixels);
    SkASSERT(fConfig == kIndex8_Config);
    SkASSERT((unsigned)x < fWidth && (unsigned)y < fHeight);
    SkASSERT(fColorTable);
    return (*fColorTable)[*((const uint8_t*)fPixels + y * fRowBytes + x)];
}

// returns the address of the byte that contains the x coordinate
inline uint8_t* SkBitmap::getAddr1(int x, int y) const {
    SkASSERT(fPixels);
    SkASSERT(fConfig == kA1_Config);
    SkASSERT((unsigned)x < fWidth && (unsigned)y < fHeight);
    return (uint8_t*)fPixels + y * fRowBytes + (x >> 3);
}

#endif
