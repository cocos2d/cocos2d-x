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
    typedef void (*Proc)(uint16_t* SK_RESTRICT dst,
                         const SkPMColor* SK_RESTRICT src,
                         int count, U8CPU alpha, int x, int y);

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
    typedef void (*Proc32)(uint32_t* SK_RESTRICT dst,
                         const SkPMColor* SK_RESTRICT src,
                         int count, U8CPU alpha);

    static Proc32 Factory32(unsigned flags32);
    
    /** Blend a single color onto a row of S32 pixels, writing the result
        into a row of D32 pixels. src and dst may be the same memory, but
        if they are not, they may not overlap.
     */
    static void Color32(SkPMColor dst[], const SkPMColor src[], int count,
                         SkPMColor color);

    /** Blend a single color onto a row of 32bit pixels, writing the result
        into the same row.
     */
    static void Color32(SkPMColor row[], int count, SkPMColor color) {
        Color32(row, row, count, color);
    }

    /** These static functions are called by the Factory and Factory32
        functions, and should return either NULL, or a
        platform-specific function-ptr to be used in place of the
        system default.
     */

    static Proc32 PlatformProcs32(unsigned flags);
    static Proc PlatformProcs565(unsigned flags);
    static Proc PlatformProcs4444(unsigned flags);

private:
    enum {
        kFlags16_Mask = 7,
        kFlags32_Mask = 3
    };
};

#endif
