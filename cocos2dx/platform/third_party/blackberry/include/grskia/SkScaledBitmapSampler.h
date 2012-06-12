#ifndef SkScaledBitmapSampler_DEFINED
#define SkScaledBitmapSampler_DEFINED

#include "SkTypes.h"
#include "SkColor.h"

class SkBitmap;

class SkScaledBitmapSampler {
public:
    SkScaledBitmapSampler(int origWidth, int origHeight, int cellSize);
    
    int scaledWidth() const { return fScaledWidth; }
    int scaledHeight() const { return fScaledHeight; }
    
    int srcY0() const { return fY0; }
    int srcDY() const { return fDY; }

    enum SrcConfig {
        kGray,  // 1 byte per pixel
        kIndex, // 1 byte per pixel
        kRGB,   // 3 bytes per pixel
        kRGBX,  // 4 byes per pixel (ignore 4th)
        kRGBA,  // 4 bytes per pixel
        kRGB_565 // 2 bytes per pixel
    };

    // Given a dst bitmap (with pixels already allocated) and a src-config,
    // prepares iterator to process the src colors and write them into dst.
    // Returns false if the request cannot be fulfulled.
    bool begin(SkBitmap* dst, SrcConfig sc, bool doDither,
               const SkPMColor* = NULL);
    // call with row of src pixels, for y = 0...scaledHeight-1.
    // returns true if the row had non-opaque alpha in it
    bool next(const uint8_t* SK_RESTRICT src);

private:
    int fScaledWidth;
    int fScaledHeight;

    int fX0;    // first X coord to sample
    int fY0;    // first Y coord (scanline) to sample
    int fDX;    // step between X samples
    int fDY;    // step between Y samples

    typedef bool (*RowProc)(void* SK_RESTRICT dstRow,
                            const uint8_t* SK_RESTRICT src,
                            int width, int deltaSrc, int y,
                            const SkPMColor[]);

    // setup state
    char*   fDstRow; // points into bitmap's pixels
    int     fDstRowBytes;
    int     fCurrY; // used for dithering
    int     fSrcPixelSize;  // 1, 3, 4    
    RowProc fRowProc;

    // optional reference to the src colors if the src is a palette model
    const SkPMColor* fCTable;
};

#endif
