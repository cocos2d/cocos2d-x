/****************************************************************************
Copyright (c) 2011      Laschweinski
Copyright (c) 2013-2017 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_LINUX

#include "platform/CCDevice.h"
#include "platform/CCFileUtils.h"

#include <X11/Xlib.h>
#include <stdio.h>

#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <fontconfig/fontconfig.h>

#include "ft2build.h"
#include FT_FREETYPE_H

using namespace std;

// as FcFontMatch is quite an expensive call, cache the results of getFontFile
static std::map<std::string, std::string> fontCache;

struct LineBreakGlyph {
    FT_UInt glyphIndex;
    int paintPosition;
    int glyphWidth;

    int bearingX;
    int kerning;
    int horizAdvance;
};

struct LineBreakLine {
    LineBreakLine() : lineWidth(0) {}

    std::vector<LineBreakGlyph> glyphs;
    int lineWidth;

    void reset() {
        glyphs.clear();
        lineWidth = 0;
    }

    void calculateWidth() {
        lineWidth = 0;
        if ( glyphs.empty() == false ) {
            LineBreakGlyph& glyph = glyphs.at(glyphs.size() - 1);
            lineWidth = glyph.paintPosition + max(glyph.glyphWidth, glyph.horizAdvance - glyph.bearingX);
        }
    }
};

NS_CC_BEGIN

int Device::getDPI()
{
    static int dpi = -1;
    if (dpi == -1)
    {
        Display *dpy;
        char *displayname = NULL;
        int scr = 0; /* Screen number */
        dpy = XOpenDisplay (displayname);
        /*
         * there are 2.54 centimeters to an inch; so there are 25.4 millimeters.
         *
         *     dpi = N pixels / (M millimeters / (25.4 millimeters / 1 inch))
         *         = N pixels / (M inch / 25.4)
         *         = N * 25.4 pixels / M inch
         */
        double xres = ((((double) DisplayWidth(dpy,scr)) * 25.4) / 
            ((double) DisplayWidthMM(dpy,scr)));
        dpi = (int) (xres + 0.5);
        //printf("dpi = %d\n", dpi);
        XCloseDisplay (dpy);
    }
    return dpi;
}

void Device::setAccelerometerEnabled(bool isEnabled)
{

}

void Device::setAccelerometerInterval(float interval)
{

}

class BitmapDC
{
public:
    BitmapDC() {
        libError = FT_Init_FreeType( &library );
        FcInit();
        _data = NULL;
        reset();
    }

    ~BitmapDC() {
        FT_Done_FreeType(library);
        FcFini();
        
        reset();
    }

    void reset() {
        iMaxLineWidth = 0;
        iMaxLineHeight = 0;
        textLines.clear();
    }

    int utf8(char **p)
    {
        if ((**p & 0x80) == 0x00)
        {
            int a = *((*p)++);

            return a;
        }
        if ((**p & 0xE0) == 0xC0)
        {
            int a = *((*p)++) & 0x1F;
            int b = *((*p)++) & 0x3F;

            return (a << 6) | b;
        }
        if ((**p & 0xF0) == 0xE0)
        {
            int a = *((*p)++) & 0x0F;
            int b = *((*p)++) & 0x3F;
            int c = *((*p)++) & 0x3F;

            return (a << 12) | (b << 6) | c;
        }
        if ((**p & 0xF8) == 0xF0)
        {
            int a = *((*p)++) & 0x07;
            int b = *((*p)++) & 0x3F;
            int c = *((*p)++) & 0x3F;
            int d = *((*p)++) & 0x3F;

            return (a << 18) | (b << 12) | (c << 8) | d;
        }
        return 0;
    }

    bool isBreakPoint(FT_UInt currentCharacter, FT_UInt previousCharacter) {
        if ( previousCharacter == '-' || previousCharacter == '/' || previousCharacter == '\\' ) {
            // we can insert a line break after one of these characters
            return true;
        }
        return false;
    }

    bool divideString(FT_Face face, const char* sText, int iMaxWidth, int iMaxHeight) {
        const char* pText = sText;
        textLines.clear();
        iMaxLineWidth = 0;

        FT_UInt unicode;
        FT_UInt prevCharacter = 0;
        FT_UInt glyphIndex = 0;
        FT_UInt prevGlyphIndex = 0;
        FT_Vector delta;
        LineBreakLine currentLine;

        int currentPaintPosition = 0;
        int firstBreakIndex = -1;
        int lastBreakIndex = -1;
        bool hasKerning = FT_HAS_KERNING( face );
        while ((unicode=utf8((char**)&pText))) {
            if (unicode == '\n') {
                currentLine.calculateWidth();
                iMaxLineWidth = max(iMaxLineWidth, currentLine.lineWidth);
                textLines.push_back(currentLine);
                currentLine.reset();
                prevGlyphIndex = 0;
                prevCharacter = 0;
                firstBreakIndex = -1;
                lastBreakIndex = -1;
                currentPaintPosition = 0;
                continue;
            }

            if ( isBreakPoint(unicode, prevCharacter) ) {
                lastBreakIndex = currentLine.glyphs.size() - 1;
            }

            glyphIndex = FT_Get_Char_Index(face, unicode);
            if (FT_Load_Glyph(face, glyphIndex, FT_LOAD_DEFAULT)) {
                return false;
            }

            LineBreakGlyph glyph;
            glyph.glyphIndex = glyphIndex;
            glyph.glyphWidth = face->glyph->metrics.width >> 6;
            glyph.bearingX = face->glyph->metrics.horiBearingX >> 6;
            glyph.horizAdvance = face->glyph->metrics.horiAdvance >> 6;
            glyph.kerning = 0;

            if (prevGlyphIndex != 0 && hasKerning) {
                FT_Get_Kerning(face, prevGlyphIndex, glyphIndex, FT_KERNING_DEFAULT, &delta);
                glyph.kerning = delta.x >> 6;
            }

            if (iswspace(unicode)) {
                prevGlyphIndex = glyphIndex;
                prevCharacter = unicode;
                lastBreakIndex = currentLine.glyphs.size();

                if (firstBreakIndex == -1)
                    firstBreakIndex = lastBreakIndex;
            } else {
                if (iswspace(prevCharacter))
                    lastBreakIndex = currentLine.glyphs.size();

                if (iMaxWidth > 0 && currentPaintPosition + glyph.bearingX + glyph.kerning + glyph.glyphWidth > iMaxWidth) {
                    int glyphCount = currentLine.glyphs.size();
                    if ( lastBreakIndex >= 0 && lastBreakIndex < glyphCount && currentPaintPosition + glyph.bearingX + glyph.kerning + glyph.glyphWidth - currentLine.glyphs.at(lastBreakIndex).paintPosition < iMaxWidth ) {
                        // we insert a line break at our last break opportunity
                        std::vector<LineBreakGlyph> tempGlyphs;
                        std::vector<LineBreakGlyph>::iterator it = currentLine.glyphs.begin();
                        std::advance(it, lastBreakIndex);
                        tempGlyphs.insert(tempGlyphs.begin(), it, currentLine.glyphs.end());
                        if (firstBreakIndex == -1) {
                            currentLine.glyphs.erase(it, currentLine.glyphs.end());
                        } else {
                            it = currentLine.glyphs.begin();
                            std::advance(it, firstBreakIndex);
                            currentLine.glyphs.erase(it, currentLine.glyphs.end());
                        }
                        currentLine.calculateWidth();
                        iMaxLineWidth = max(iMaxLineWidth, currentLine.lineWidth);
                        textLines.push_back(currentLine);
                        currentLine.reset();
                        currentPaintPosition = 0;
                        for ( auto& glyph : tempGlyphs ) {
                            if ( currentLine.glyphs.empty() ) {
                                currentPaintPosition = -glyph.bearingX;
                                glyph.kerning = 0;
                            }
                            glyph.paintPosition = currentPaintPosition + glyph.bearingX + glyph.kerning;
                            currentLine.glyphs.push_back(glyph);
                            currentPaintPosition += glyph.kerning + glyph.horizAdvance;
                        }
                    } else {
                        // the current word is too big to fit into one line, insert line break right here
                        currentPaintPosition = 0;
                        glyph.kerning = 0;
                        currentLine.calculateWidth();
                        iMaxLineWidth = max(iMaxLineWidth, currentLine.lineWidth);
                        textLines.push_back(currentLine);
                        currentLine.reset();
                    }
    
                    prevGlyphIndex = 0;
                    prevCharacter = 0;
                    firstBreakIndex = -1;
                    lastBreakIndex = -1;
                } else {
                    prevGlyphIndex = glyphIndex;
                    prevCharacter = unicode;
                }
            }
            
            if ( currentLine.glyphs.empty() ) {
                currentPaintPosition = -glyph.bearingX;
            }
            glyph.paintPosition = currentPaintPosition + glyph.bearingX + glyph.kerning;
            currentLine.glyphs.push_back(glyph);
            currentPaintPosition += glyph.kerning + glyph.horizAdvance;
        }

        if ( currentLine.glyphs.empty() == false ) {
            currentLine.calculateWidth();
            iMaxLineWidth = max(iMaxLineWidth, currentLine.lineWidth);
            textLines.push_back(currentLine);
        }
        return true;
    }

    /**
     * compute the start pos of every line
     */
    int computeLineStart(FT_Face face, Device::TextAlign eAlignMask, int line) {
                int lineWidth = textLines.at(line).lineWidth;
        if (eAlignMask == Device::TextAlign::CENTER || eAlignMask == Device::TextAlign::TOP || eAlignMask == Device::TextAlign::BOTTOM) {
            return (iMaxLineWidth - lineWidth) / 2;
        } else if (eAlignMask == Device::TextAlign::RIGHT || eAlignMask == Device::TextAlign::TOP_RIGHT || eAlignMask == Device::TextAlign::BOTTOM_RIGHT) {
            return (iMaxLineWidth - lineWidth);
        }

        // left or other situation
        return 0;
    }

    int computeLineStartY( FT_Face face, Device::TextAlign eAlignMask, int txtHeight, int borderHeight ){
        int baseLinePos = ceilf(face->size->metrics.ascender/64.0f);
        if (eAlignMask == Device::TextAlign::CENTER || eAlignMask == Device::TextAlign::LEFT || eAlignMask == Device::TextAlign::RIGHT) {
            //vertical center
            return (borderHeight - txtHeight) / 2 + baseLinePos;
        } else if (eAlignMask == Device::TextAlign::BOTTOM_RIGHT || eAlignMask == Device::TextAlign::BOTTOM || eAlignMask == Device::TextAlign::BOTTOM_LEFT) {
            //vertical bottom
            return borderHeight - txtHeight + baseLinePos;
        }

        // top alignment
        return baseLinePos;
    }

    std::string getFontFile(const char* family_name) {
        std::string fontPath = family_name;

        std::map<std::string, std::string>::iterator it = fontCache.find(family_name);
        if ( it != fontCache.end() ) {
            return it->second;
        }

        // check if the parameter is a font file shipped with the application
        std::string lowerCasePath = fontPath;
        std::transform(lowerCasePath.begin(), lowerCasePath.end(), lowerCasePath.begin(), ::tolower);
        if ( lowerCasePath.find(".ttf") != std::string::npos ) {
            fontPath = cocos2d::FileUtils::getInstance()->fullPathForFilename(fontPath.c_str());

            FILE *f = fopen(fontPath.c_str(), "r");
            if ( f ) {
                fclose(f);
                fontCache.insert(std::pair<std::string, std::string>(family_name, fontPath));
                return fontPath;
            }
        }

        // use fontconfig to match the parameter against the fonts installed on the system
        FcPattern *pattern = FcPatternBuild (0, FC_FAMILY, FcTypeString, family_name, (char *) 0);
        FcConfigSubstitute(0, pattern, FcMatchPattern);
        FcDefaultSubstitute(pattern);

        FcResult result;
        FcPattern *font = FcFontMatch(0, pattern, &result);
        if ( font ) {
            FcChar8 *s = NULL;
            if ( FcPatternGetString(font, FC_FILE, 0, &s) == FcResultMatch ) {
                fontPath = (const char*)s;

                FcPatternDestroy(font);
                FcPatternDestroy(pattern);

                fontCache.insert(std::pair<std::string, std::string>(family_name, fontPath));
                return fontPath;
            }
            FcPatternDestroy(font);
        }
        FcPatternDestroy(pattern);

        return family_name;
    }

    bool getBitmap(const char *text, const FontDefinition& textDefinition, Device::TextAlign eAlignMask) {
        if (libError) {
            return false;
        }

        FT_Face face;
        std::string fontfile = getFontFile(textDefinition._fontName.c_str());
        if ( FT_New_Face(library, fontfile.c_str(), 0, &face) ) {
            //no valid font found use default
            if ( FT_New_Face(library, "/usr/share/fonts/truetype/freefont/FreeSerif.ttf", 0, &face) ) {
                return false;
            }
        }

        //select utf8 charmap
        if ( FT_Select_Charmap(face, FT_ENCODING_UNICODE) ) {
            FT_Done_Face(face);
            return false;
        }

        if ( FT_Set_Pixel_Sizes(face, textDefinition._fontSize, textDefinition._fontSize) ) {
            FT_Done_Face(face);
            return false;
        }

        if ( divideString(face, text, textDefinition._dimensions.width, textDefinition._dimensions.height) == false ) {
            FT_Done_Face(face);
            return false;
        }

        //compute the final line width
        iMaxLineWidth = MAX(iMaxLineWidth, textDefinition._dimensions.width);

        //compute the final line height
        int lineHeight = face->size->metrics.height>>6;
        int txtHeight = (lineHeight * textLines.size());
        iMaxLineHeight = MAX(txtHeight, textDefinition._dimensions.height);

        _data = (unsigned char*)malloc(sizeof(unsigned char) * (iMaxLineWidth * iMaxLineHeight * 4));
        memset(_data,0, iMaxLineWidth * iMaxLineHeight*4);

        int iCurYCursor = computeLineStartY(face, eAlignMask, txtHeight, iMaxLineHeight);

        int lineCount = textLines.size();
        for (int line = 0; line < lineCount; line++) {
            int iCurXCursor = computeLineStart(face, eAlignMask, line);

            int glyphCount = textLines.at(line).glyphs.size();
            for (int i = 0; i < glyphCount; i++) {
                LineBreakGlyph glyph = textLines.at(line).glyphs.at(i);

                if (FT_Load_Glyph(face, glyph.glyphIndex, FT_LOAD_RENDER)) {
                    continue;
                }

                FT_Bitmap& bitmap = face->glyph->bitmap;
                int yoffset = iCurYCursor - (face->glyph->metrics.horiBearingY >> 6);
                int xoffset = iCurXCursor + glyph.paintPosition;

                for (int y = 0; y < bitmap.rows; ++y) {
                    int iY = yoffset + y;
                    if (iY>=iMaxLineHeight) {
                        //exceed the height truncate
                        break;
                    }
                    iY *= iMaxLineWidth;

                    int bitmap_y = y * bitmap.width;

                    for (int x = 0; x < bitmap.width; ++x) {
                        unsigned char cTemp = bitmap.buffer[bitmap_y + x];
                        if (cTemp == 0) {
                            continue;
                        }

                        int iX = xoffset + x;
                        //FIXME:wrong text color
                        int iTemp = cTemp << 24 | cTemp << 16 | cTemp << 8 | cTemp;
                        *(int*) &_data[(iY + iX) * 4 + 0] = iTemp;
                    }
                }
            }
            // step to next line
            iCurYCursor += lineHeight;
        }

        //  free face
        FT_Done_Face(face);
        return true;
    }

public:
    FT_Library library;

    unsigned char *_data;
    int libError;
    std::vector<LineBreakLine> textLines;
    int iMaxLineWidth;
    int iMaxLineHeight;
};

static BitmapDC& sharedBitmapDC()
{
    static BitmapDC s_BmpDC;
    return s_BmpDC;
}

Data Device::getTextureDataForText(const char * text, const FontDefinition& textDefinition, TextAlign align, int &width, int &height, bool& hasPremultipliedAlpha)
{
    Data ret;
    do 
    {
        BitmapDC &dc = sharedBitmapDC();

        CC_BREAK_IF(! dc.getBitmap(text, textDefinition, align));
        CC_BREAK_IF(! dc._data);
        width = dc.iMaxLineWidth;
        height = dc.iMaxLineHeight;
        dc.reset();
        ret.fastSet(dc._data,width * height * 4);
        hasPremultipliedAlpha = true;
    } while (0);

    return ret;
}

void Device::setKeepScreenOn(bool /*value*/)
{
}

void Device::vibrate(float /*duration*/)
{
}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
