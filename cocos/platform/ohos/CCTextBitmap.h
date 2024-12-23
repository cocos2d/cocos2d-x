#ifndef XComponent_CCTextBitmap_H
#define XComponent_CCTextBitmap_H

#include "platform/CCPlatformMacros.h"
#include "platform/CCImage.h"
#include "platform/CCDevice.h"

#include <native_drawing/drawing_bitmap.h>
#include <native_drawing/drawing_canvas.h>
#include <native_drawing/drawing_text_typography.h>
#include <native_drawing/drawing_font_collection.h>

#define DEFAULT_FONTSIZE 20

NS_CC_BEGIN
class CCTextBitmap {
    public:
        static const int HORIZONTALALIGN_LEFT = 1;
        static const int HORIZONTALALIGN_RIGHT = 2;
        static const int HORIZONTALALIGN_CENTER = 3;

        static const int VERTICALALIGN_TOP = 1;
        static const int VERTICALALIGN_BOTTOM = 2;
        static const int VERTICALALIGN_CENTER = 3;
        static void createCCTextBitmap(CCTextBitmap* cCTextBitmap, const char *text, const char *pFontName, const float a, const float r, const float g, const float b, 
            const Device::TextAlign eAlignMask, int width_, int height_, double fontSize);
        static void createCCTextBitmap(CCTextBitmap* cCTextBitmap, const char *text,  const char *pFontName, const int pFontSize,
                                                const float fontTintA, const float fontTintR, const float fontTintG, const float fontTintB,
                                                const Device::TextAlign eAlignMask, const int pWidth, const int pHeight, const bool shadow,
                                                const float shadowDX, const float shadowDY, const float shadowBlur, const bool stroke,
                                                const float strokeR, const float strokeG, const float strokeB, const float strokeSize);

        ~CCTextBitmap();
        void* getPixelAddr();
        int GetWidth() { return width; }
        int GetHeight() { return height; }
    private:

        /**
        * Calculate the start point of x-drawing
        * @param pAlignment Edge settings for text
        * @param layoutWidth Width when text is measured
        * @param realWidth Actual text width
        * @param textWidth Width of the last display of the text control, that is, the width of the bitmap.
        * @return x The starting point of the drawing
         */
        static double calxStartPosition(int pAlignment, int layoutWidth, int realWidth, int textWidth);

        /**
        * Calculate the start point of y drawing
        * @param pAlignment Edge settings for text
        * @param realWidth Actual text width
        * @param textWidth Width of the last display of the text control, that is, the width of the bitmap.
        * @return x The starting point of the drawing
         */
        static double calyStartPosition(int pAlignment, int realHeight, int textHeight);

        static int processTextAlign(int pAlignment);
        void* pixelAddr = nullptr;
        int width = 0;
        int height = 0;

        OH_Drawing_Bitmap* _bitmap{nullptr};
        OH_Drawing_Canvas* _canvas{nullptr};
        OH_Drawing_TypographyStyle* _typographyStyle{nullptr};
        OH_Drawing_TypographyCreate* _typographyCreate{nullptr};
        OH_Drawing_FontCollection* _fontCollection{nullptr};
        OH_Drawing_TextStyle* _textStyle{nullptr};
        OH_Drawing_Typography *_typography{nullptr};
    };
NS_CC_END
#endif 
