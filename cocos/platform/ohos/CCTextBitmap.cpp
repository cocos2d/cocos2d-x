#include <native_drawing/drawing_font_collection.h>
#include "CCTextBitmap.h"
#include "platform/CCPlatformMacros.h"
#include "platform/CCCommon.h"
#include "platform/ohos/napi/helper/NapiHelper.h"

NS_CC_BEGIN

void CCTextBitmap::createCCTextBitmap(CCTextBitmap *cCTextBitmap, const char *text, const char *pFontName,
                                      const float a, const float r, const float g, const float b,
                                      const Device::TextAlign eAlignMask, int width_, int height_, double fontSize) {
    createCCTextBitmap(cCTextBitmap, text, pFontName, fontSize, a, r, g, b, eAlignMask, width_, height_, false, 1, 1, 1,
                       false, 1, 1, 1, 1);
}

double CCTextBitmap::calxStartPosition(int pAlignment, int layoutWidth, int realWidth, int textWidth) {
    if (pAlignment == TEXT_ALIGN_LEFT) {
        return 0;
    }
    if (pAlignment == TEXT_ALIGN_CENTER) {
        // Move to the leftmost part of the text, and then add the margin between the text and the actual rendering
        // position. Note that the content drawn from the drawing moves to the left using the - position and to the
        // right using the + position.
        return (-(layoutWidth - realWidth) / 2) + ((textWidth - realWidth) / 2);
    }

    if (pAlignment == TEXT_ALIGN_RIGHT) {
        return -(layoutWidth - textWidth);
    }
    return 0;
}
double CCTextBitmap::calyStartPosition(int pAlignment, int realHeight, int textHeight) {
    const int pVerticalAlignment = (pAlignment >> 4) & 0x0F;
    int y = 0;
    switch (pVerticalAlignment) {
    case VERTICALALIGN_TOP:
        y = 0;
        break;
    case VERTICALALIGN_CENTER:
        y = (textHeight - realHeight) / 2;
        break;
    case VERTICALALIGN_BOTTOM:
        y = textHeight - realHeight;
        break;
    default:
        break;
    }

    return y;
}
int CCTextBitmap::processTextAlign(int pAlignment) {
    const int horizontalAlignment = pAlignment & 0x0F;
    int align = TEXT_ALIGN_LEFT;
    switch (horizontalAlignment) {
    case HORIZONTALALIGN_CENTER:
        align = TEXT_ALIGN_CENTER;
        break;
    case HORIZONTALALIGN_RIGHT:
        align = TEXT_ALIGN_RIGHT;
        break;
    case HORIZONTALALIGN_LEFT:
    default:
        align = TEXT_ALIGN_LEFT;
        break;
    }
    return align;
}

void CCTextBitmap::createCCTextBitmap(CCTextBitmap* cCTextBitmap, const char *text,  const char *pFontName, const int fontSize,
            const float fontTintA, const float fontTintR, const float fontTintG, const float fontTintB,
            const Device::TextAlign eAlignMask, const int pWidth, const int pHeight, const bool shadow,
            const float shadowDX, const float shadowDY, const float shadowBlur, const bool stroke,
            const float strokeR, const float strokeG, const float strokeB, const float strokeSize) {
    // Manages typographical styles, such as text orientation.
    cCTextBitmap->_typographyStyle = OH_Drawing_CreateTypographyStyle();
    // Set the text to be displayed from left to right.
    OH_Drawing_SetTypographyTextDirection(cCTextBitmap->_typographyStyle, TEXT_DIRECTION_LTR);
    int align = processTextAlign((int)eAlignMask);
    // Set text alignment
    OH_Drawing_SetTypographyTextAlign(cCTextBitmap->_typographyStyle, align);
    // Used to load fonts
    cCTextBitmap->_fontCollection = OH_Drawing_CreateFontCollection();
    // Creates a pointer to the OH_Drawing_TypographyCreate object
    cCTextBitmap->_typographyCreate = OH_Drawing_CreateTypographyHandler(cCTextBitmap->_typographyStyle, cCTextBitmap->_fontCollection);
    // Used to manage font colors, decorations, etc.
    cCTextBitmap->_textStyle = OH_Drawing_CreateTextStyle();

    // Set Text Color
    OH_Drawing_SetTextStyleColor(cCTextBitmap->_textStyle, OH_Drawing_ColorSetArgb(fontTintA, fontTintR, fontTintG, fontTintB));

    // Set text size
    OH_Drawing_SetTextStyleFontSize(cCTextBitmap->_textStyle, fontSize == 0 ? DEFAULT_FONTSIZE : fontSize);
    // Set word weight
    OH_Drawing_SetTextStyleFontWeight(cCTextBitmap->_textStyle, FONT_WEIGHT_400);
    // Set the font baseline position. TEXT_BASELINE_ALPHABotic is used to display phonetic characters and the baseline
    // position is lower in the middle. TEXT_BASELINE_IDEOGRAPHIC for ideographic text with baseline at bottom
    OH_Drawing_SetTextStyleBaseLine(cCTextBitmap->_textStyle, TEXT_BASELINE_ALPHABETIC);
    // Set font height
    OH_Drawing_SetTextStyleFontHeight(cCTextBitmap->_textStyle, 1);
    const char *fontFamilies[] = {pFontName};
    // Set the font type
    OH_Drawing_SetTextStyleFontFamilies(cCTextBitmap->_textStyle, 1, fontFamilies);
    // Set the font style. The font style is not italicized. FONT_EVEN_ITALIC Italic
    OH_Drawing_SetTextStyleFontStyle(cCTextBitmap->_textStyle, FONT_STYLE_NORMAL);
    // Setting the Language Area
    OH_Drawing_SetTextStyleLocale(cCTextBitmap->_textStyle, "en");

    // Set the typesetting style
    OH_Drawing_TypographyHandlerPushTextStyle(cCTextBitmap->_typographyCreate, cCTextBitmap->_textStyle);
    // Set text content
    OH_Drawing_TypographyHandlerAddText(cCTextBitmap->_typographyCreate, text);
    // Typesetting pop-up
    OH_Drawing_TypographyHandlerPopTextStyle(cCTextBitmap->_typographyCreate);

    // Used to create OH_Drawing_Typography, which is used to manage the layout and display of typesetting.
    cCTextBitmap->_typography = OH_Drawing_CreateTypography(cCTextBitmap->_typographyCreate);

    // The input width of the outer layer is preferentially used.
    int layoutWidth = pWidth;
    if (pWidth == 0) {
        // If there is no width set, assume a maximum width and calculate the actual width as the layout width
        OH_Drawing_TypographyLayout(cCTextBitmap->_typography, 100000);
        layoutWidth = OH_Drawing_TypographyGetMaxIntrinsicWidth(cCTextBitmap->_typography) + 1;
    }

    // typographic layout, setting maximum text width
    OH_Drawing_TypographyLayout(cCTextBitmap->_typography, layoutWidth);

    // Obtains the maximum inherent width.
    int realWidth = OH_Drawing_TypographyGetMaxIntrinsicWidth(cCTextBitmap->_typography);
    // Obtaining the height
    int realHeight = OH_Drawing_TypographyGetHeight(cCTextBitmap->_typography);
    int textWidth = pWidth != 0 ? pWidth : realWidth;
    int textHeight = pHeight != 0 ? pHeight : realHeight;

    // Format used to describe the bit pixel, including color type and transparency type.
    cCTextBitmap->_bitmap = OH_Drawing_BitmapCreate();
    // COLOR_FORMAT_RGBA_8888：Each pixel is represented by a 32-bit quantity. 8 bits indicate transparency, 8 bits
    // indicate red, 8 bits indicate green, and 8 bits indicate blue. ALPHA_FORMAT_OPAQUE：Bitmap has no transparency
    OH_Drawing_BitmapFormat cFormat = {COLOR_FORMAT_RGBA_8888, ALPHA_FORMAT_OPAQUE};

    // Initializes the width and height of the bitmap object, and sets the pixel format for the bitmap.
    OH_Drawing_BitmapBuild(cCTextBitmap->_bitmap, textWidth, textHeight, &cFormat);

    // Create a canvas object
    cCTextBitmap->_canvas = OH_Drawing_CanvasCreate();
    // Bind a bitmap object to the canvas so that the content drawn on the canvas is output to the bitmap (i.e., CPU rendering).
    OH_Drawing_CanvasBind(cCTextBitmap->_canvas, cCTextBitmap->_bitmap);

    double xStart = calxStartPosition(align, layoutWidth, realWidth, textWidth);
    double yStart = calyStartPosition((int)eAlignMask, realHeight, textHeight);
    double position[2] = {xStart, yStart};
    // Uses the specified color to clear the canvas. OH_Drawing_ColorSetArgb: Converts four variables (respectively
    // describing transparency, red, green, and blue) to a 32-bit (ARGB) variable that describes colors.
    OH_Drawing_CanvasClear(cCTextBitmap->_canvas, OH_Drawing_ColorSetArgb(0x00, 0xFF, 0x00, 0x00));
    // Display Text
    OH_Drawing_TypographyPaint(cCTextBitmap->_typography, cCTextBitmap->_canvas, position[0], position[1]);

    // Obtains the pixel address of a specified bitmap. The pixel data of the bitmap can be obtained based on the pixel address.
    cCTextBitmap->pixelAddr = OH_Drawing_BitmapGetPixels(cCTextBitmap->_bitmap);
    cCTextBitmap->width = textWidth;
    cCTextBitmap->height = textHeight;
}

void *CCTextBitmap::getPixelAddr() {
    return pixelAddr;
}

CCTextBitmap::~CCTextBitmap() {
    OH_Drawing_CanvasDestroy(_canvas);
    _canvas = nullptr;
    OH_Drawing_BitmapDestroy(_bitmap);
    _bitmap = nullptr;
    OH_Drawing_DestroyTypography(_typography);
    _typography = nullptr;
    OH_Drawing_DestroyTextStyle(_textStyle);
    _textStyle = nullptr;
    OH_Drawing_DestroyTypographyHandler(_typographyCreate);
    _typographyCreate = nullptr;
    OH_Drawing_DestroyFontCollection(_fontCollection);
    _fontCollection = nullptr;
    OH_Drawing_DestroyTypographyStyle(_typographyStyle);
    _typographyStyle = nullptr;

    pixelAddr = nullptr;
}

NS_CC_END
