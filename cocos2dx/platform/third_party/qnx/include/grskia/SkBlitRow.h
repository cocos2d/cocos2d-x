#ifndef SkBlitRow_DEFINED
#define SkBlitRow_DEFINED

#include "SkBitmap.h"
#include "SkColor.h"

class SkBlitRow {
public:
    enum Flags16 {
        //! If set, the alpha parameter will be != 255
        kGlobalAlpha_Flag   = 0x01,
        //! If set, the src colors may have alpha != 255
        kSrcPixelAlpha_Flag = 0x02,
        //! If set, the resulting 16bit colors should be dithered
        kDither_Flag        = 0x04
    };

    /** Function pointer that reads a scanline of src SkPMColors, and writes
        a corresponding scanline of 16bit colors (specific format based on the
        config passed to the Factory.

        The x,y params are useful just for dithering

        @param alpha A global alpha to be applied to all of the src colors
        @param x The x coordinate of the beginning of the scanline
        @param y THe y coordinate of the scanline
     */
    typedef void (*Proc)(uint16_t* dst,
                         const SkPMColor* src,
                         int count, U8CPU alpha, int x, int y);

   /** Function pointer that blends a single color with a row of 32-bit colors
       onto a 32-bit destination
   */
   typedef void (*ColorProc)(SkPMColor* dst, const SkPMColor* src, int count,
                             SkPMColor color);

    //! Public entry-point to return a blit function ptr
    static Proc Factory(unsigned flags, SkBitmap::Config);

    ///////////// D32 version

    enum Flags32 {
        kGlobalAlpha_Flag32     = 1 << 0,
        kSrcPixelAlpha_Flag32   = 1 << 1,
    };

    /** Function pointer that blends 32bit colors onto a 32bit destination.
        @param dst  array of dst 32bit colors
        @param src  array of src 32bit colors (w/ or w/o alpha)
        @param count number of colors to blend
        @param alpha global alpha to be applied to all src colors
     */
    typedef void (*Proc32)(uint32_t* dst,
                         const SkPMColor* src,
                         int count, U8CPU alpha);

    static Proc32 Factory32(unsigned flags32);

    /** Blend a single color onto a row of S32 pixels, writing the result
        into a row of D32 pixels. src and dst may be the same memory, but
        if they are not, they may not overlap.
     */
    static void Color32(SkPMColor dst[], const SkPMColor src[],
                        int count, SkPMColor color);

    static ColorProc ColorProcFactory();

    /** These static functions are called by the Factory and Factory32
        functions, and should return either NULL, or a
        platform-specific function-ptr to be used in place of the
        system default.
     */

    static Proc32 PlatformProcs32(unsigned flags);
    static Proc PlatformProcs565(unsigned flags);
    static Proc PlatformProcs4444(unsigned flags);
    static ColorProc PlatformColorProc();

private:
    enum {
        kFlags16_Mask = 7,
        kFlags32_Mask = 3
    };
};

/**
 *  Factory for blitmask procs
 */
class SkBlitMask {
public:
    /**
     *  Function pointer that blits the mask into a device (dst) colorized
     *  by color. The number of pixels to blit is specified by width and height,
     *  but each scanline is offset by dstRB (rowbytes) and srcRB respectively.
     */
    typedef void (*Proc)(void* dst, size_t dstRB, SkBitmap::Config dstConfig,
                        const uint8_t* mask, size_t maskRB, SkColor color,
                        int width, int height);

    /* Public entry-point to return a blitmask function ptr
     */
    static Proc Factory(SkBitmap::Config dstConfig, SkColor color);

    /* return either platform specific optimized blitmask function-ptr,
     * or NULL if no optimized
     */
    static Proc PlatformProcs(SkBitmap::Config dstConfig, SkColor color);
};


#endif
