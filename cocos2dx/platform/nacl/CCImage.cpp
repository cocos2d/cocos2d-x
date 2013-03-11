/****************************************************************************
Copyright (c) 2013 The Chromium Authors

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

#include <string.h>

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include "platform/CCFileUtils.h"
#include "platform/CCPlatformMacros.h"
#define __CC_PLATFORM_IMAGE_CPP__
#include "platform/CCImageCommon_cpp.h"
#include "platform/CCImage.h"
#include "platform/linux/CCApplication.h"

#include "ft2build.h"
#include "CCStdC.h"

#include FT_FREETYPE_H

#define szFont_kenning 2

#define SHIFT6(num) (num>>6)

using namespace std;

struct TextLine {
    int iLineWidth;
    wchar_t* text;
};

NS_CC_BEGIN

class BitmapDC
{
public:
    BitmapDC() : m_pData(NULL), m_cachedSize(0), m_cachedFont(NULL)
    {
        libError = FT_Init_FreeType(&m_library);
        iInterval = szFont_kenning;
        reset();
    }

    ~BitmapDC()
    {
        if (m_cachedFont)
            FT_Done_Face(m_cachedFont);
        FT_Done_FreeType(m_library);
        reset();
    }

    void reset()
    {
        iMaxLineWidth = 0;
        iMaxLineHeight = 0;
        //Free all text lines
        size_t size = vLines.size();
        for (size_t i=0; i<size; ++i)
        {
            TextLine line = vLines[i];
            free(line.text);
        }
        vLines.clear();
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

    void buildLine(wchar_t* buf, size_t buf_len, FT_Face face, int iCurXCursor, FT_UInt cLastChar)
    {
        TextLine oTempLine;
        wchar_t* text = (wchar_t*)malloc(sizeof(wchar_t) * (buf_len+1));
        memcpy(text, buf, sizeof(wchar_t) * buf_len);
        text[buf_len] = '\0';
        oTempLine.text = text;

        //get last glyph
        FT_Load_Char(face, cLastChar, FT_LOAD_DEFAULT);

        oTempLine.iLineWidth = iCurXCursor;// - SHIFT6((face->glyph->metrics.horiAdvance + face->glyph->metrics.horiBearingX - face->glyph->metrics.width))/*-iInterval*/;//TODO interval
        iMaxLineWidth = MAX(iMaxLineWidth, oTempLine.iLineWidth);

        vLines.push_back(oTempLine);
    }

    bool divideString(FT_Face face, const char* sText, int iMaxWidth, int iMaxHeight)
    {
        int iError = 0;
        const char* pText = sText;

        FT_UInt unicode = utf8((char**)&pText);
        iError = FT_Load_Char(face, unicode, FT_LOAD_DEFAULT);
        if (iError)
            return false;

        int iCurXCursor = -SHIFT6(face->glyph->metrics.horiBearingX);

        FT_UInt cLastCh = 0;

        pText = sText;
        size_t text_len = 0;
        wchar_t* text_buf = (wchar_t*) malloc(sizeof(wchar_t) * strlen(sText));
        while ((unicode=utf8((char**)&pText)))
        {
            if (unicode == '\n')
            {
                buildLine(text_buf, text_len, face, iCurXCursor, cLastCh);
                text_len = 0;

                iError = FT_Load_Char(face, unicode, FT_LOAD_DEFAULT);
                if (iError) {
                    free(text_buf);
                    return false;
                }
                iCurXCursor = -SHIFT6(face->glyph->metrics.horiBearingX);
                continue;
            }

            iError = FT_Load_Char(face, unicode, FT_LOAD_DEFAULT);

            if (iError) {
                free(text_buf);
                return false;
            }

            //check its width
            //divide it when exceeding
            if ((iMaxWidth > 0
                            && iCurXCursor + SHIFT6(face->glyph->metrics.width)
                            > iMaxWidth)) {
                buildLine(text_buf, text_len, face , iCurXCursor, cLastCh);
                text_len = 0;

                iCurXCursor = -SHIFT6(face->glyph->metrics.horiBearingX);
            }

            cLastCh = unicode;
            text_buf[text_len] = unicode;
            ++text_len;
            iCurXCursor += SHIFT6(face->glyph->metrics.horiAdvance) + iInterval;
        }

        if (iError)
        {
            free(text_buf);
            return false;
        }

        buildLine(text_buf, text_len, face, iCurXCursor, cLastCh);
        free(text_buf);

        return true;
    }

    /**
     * compute the start pos of every line
     *
     * return >0 represent the start x pos of the line
     * while -1 means fail
     *
     */
    int computeLineStart(FT_Face face, CCImage::ETextAlign eAlignMask, FT_UInt unicode,
            int iLineIndex)
    {
        int iRet;
        int iError = FT_Load_Char(face, unicode, FT_LOAD_DEFAULT);
        if (iError) {
            return -1;
        }

        if (eAlignMask == CCImage::kAlignCenter) {
            iRet = (iMaxLineWidth - vLines[iLineIndex].iLineWidth) / 2
            - SHIFT6(face->glyph->metrics.horiBearingX );

        } else if (eAlignMask == CCImage::kAlignRight) {
            iRet = (iMaxLineWidth - vLines[iLineIndex].iLineWidth)
            - SHIFT6(face->glyph->metrics.horiBearingX );
        } else {
            // left or other situation
            iRet = -SHIFT6(face->glyph->metrics.horiBearingX );
        }
        return iRet;
    }

    int computeLineStartY(FT_Face face, CCImage::ETextAlign eAlignMask, int txtHeight, int borderHeight)
    {
        int iRet = 0;
        if (eAlignMask == CCImage::kAlignCenter || eAlignMask == CCImage::kAlignLeft ||
            eAlignMask == CCImage::kAlignRight ) {
            //vertical center
            iRet = (borderHeight - txtHeight)/2;

        } else if (eAlignMask == CCImage::kAlignBottomRight ||
                   eAlignMask == CCImage::kAlignBottom ||
                   eAlignMask == CCImage::kAlignBottomLeft ) {
            //vertical bottom
            iRet = borderHeight - txtHeight;
        }
        iRet += SHIFT6(face->size->metrics.ascender);
        return iRet;
    }

    bool renderLine(FT_Face face, const wchar_t* text_ptr, int* iCurXCursor, int iCurYCursor)
    {
        assert(iCurYCursor > 0);
        size_t text_len = wcslen(text_ptr);
        for (size_t i=0; i<text_len; ++i)
        {
            int iError = FT_Load_Char(face, text_ptr[i], FT_LOAD_RENDER);
            if (iError)
                return false;

            //  convert glyph to bitmap with 256 gray
            //  and get the bitmap
            FT_Bitmap& bitmap = face->glyph->bitmap;

            int yoffset = iCurYCursor - SHIFT6(face->glyph->metrics.horiBearingY);
            int xoffset = *iCurXCursor + SHIFT6(face->glyph->metrics.horiBearingX);
            for (int i = 0; i < bitmap.rows; ++i)
            {
                for (int j = 0; j < bitmap.width; ++j)
                {
                    unsigned char cTemp = bitmap.buffer[i * bitmap.width + j];
                    if (cTemp == 0) continue;

                    //  if it has gray>0 we set show it as 1, o otherwise
                    int iY = yoffset + i;
                    int iX = xoffset + j;

                    if (iY < 0)
                    {
                        //truncate if drawing below first line
                        assert(iY >= -1);
                        continue;
                    }

                    if (iY >= iMaxLineHeight)
                    {
                        //exceed the height truncate
                        assert(iY <= iMaxLineHeight + 1);
                        continue;
                    }

                    int iTemp = cTemp << 24 | cTemp << 16 | cTemp << 8 | cTemp;
                    int data_offset = iY * iMaxLineWidth + iX;
                    assert(data_offset >= 0);
                    assert(data_offset < m_DataSize);
                    m_pData[data_offset] = iTemp;
                }
            }

            //step to next glyph
            *iCurXCursor += SHIFT6(face->glyph->metrics.horiAdvance) + iInterval;
        }
        return true;
    }

    bool renderLines(FT_Face face, CCImage::ETextAlign eAlignMask, int iCurYCursor)
    {
        size_t lines = vLines.size();
        for (size_t i = 0; i < lines; i++)
        {
            const wchar_t* text_ptr = vLines[i].text;

            // initialize the origin cursor
            int iCurXCursor = computeLineStart(face, eAlignMask, text_ptr[0], i);
            if (!renderLine(face, text_ptr, &iCurXCursor, iCurYCursor))
                return false;

            iCurYCursor += SHIFT6(face->size->metrics.ascender) -
                SHIFT6(face->size->metrics.descender);
        }
        return true;
    }

    bool getBitmap(const char *text, int nWidth, int nHeight, CCImage::ETextAlign eAlignMask, const char * pFontName, float fontSize)
    {
        FT_Error iError;
        if (libError)
            return false;

        std::string fontfile = pFontName;
        std::string fontfileOrig = std::string(fontfile);

        std::string ext = fileNameExtension(fontfile);
        if (ext.empty() || (ext != "ttf" && ext != "TTF"))
        {
            fontfile += ".ttf" ;
        }

        iError = openFont(fontfile, fontSize, fontfileOrig);
        // try with fonts prefixed
        if (iError && !startsWith(fontfile,"fonts/") )
        {
            fontfile = std::string("fonts/") + fontfile;
            iError = openFont(fontfile, fontSize, fontfileOrig);
        }

        if (iError)
        {
            // try lowercase version
            std::transform(fontfile.begin(), fontfile.end(), fontfile.begin(), ::tolower);
            iError = openFont(fontfile, fontSize, fontfileOrig);
            if (iError)
            {
                // try default font
                CCLOG("font missing (%s) falling back to default font", fontfileOrig.c_str());
                iError = openFont("fonts/Marker Felt.ttf", fontSize, fontfileOrig);
                if (iError)
                    CCLOG("default font missing (fonts/Marker Felt.ttf)");
            }
        }
        if (iError)
            return false;

        FT_Face face = m_cachedFont;

        //select utf8 charmap
        iError = FT_Select_Charmap(face,FT_ENCODING_UNICODE);
        if (iError)
            return false;

        iError = FT_Set_Pixel_Sizes(face, fontSize, fontSize);
        if (iError)
            return false;

        if (!divideString(face, text, nWidth, nHeight))
            return false;

        //compute the final line width
        iMaxLineWidth = MAX(iMaxLineWidth, nWidth);

        iMaxLineHeight = SHIFT6(face->size->metrics.ascender) - SHIFT6(face->size->metrics.descender);
        iMaxLineHeight *= vLines.size();

        int txtHeight = iMaxLineHeight;

        //compute the final line height
        iMaxLineHeight = MAX(iMaxLineHeight, nHeight);

        // create m_pData as render target
        m_DataSize = iMaxLineWidth * iMaxLineHeight;
        m_pData = new int[m_DataSize];
        memset(m_pData, 0, m_DataSize*sizeof(*m_pData));

        //iCurYCursor = SHIFT6(face->size->metrics.ascender);
        int iCurYCursor = computeLineStartY(face, eAlignMask, txtHeight, iMaxLineHeight);
        if (!renderLines(face, eAlignMask, iCurYCursor))
            return false;

        // success;
        return true;
    }

public:
    FT_Library m_library;

    int *m_pData;
    // size of m_pData in words
    int m_DataSize;
    int libError;
    vector<TextLine> vLines;
    int iInterval;
    int iMaxLineWidth;
    int iMaxLineHeight;
private:
    bool startsWith(const std::string& str, const std::string& what);
    /**
     * Attempt to open font file, and cache it if successful.
     */
    int openFont(const std::string& fontName, uint fontSize, const std::string& fontNameOrig);
    std::string fileNameExtension(const std::string& pathName);

    uint m_cachedSize;
    FT_Face m_cachedFont;
    std::string m_cachedFontname;
    std::string m_cachedFontnameOrig;
};

static BitmapDC& sharedBitmapDC()
{
    static BitmapDC s_BmpDC;
    return s_BmpDC;
}

bool CCImage::initWithString(
        const char * pText,
        int nWidth/* = 0*/,
        int nHeight/* = 0*/,
        ETextAlign eAlignMask/* = kAlignCenter*/,
        const char * pFontName/* = nil*/,
        int nSize/* = 0*/)
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(! pText);

        BitmapDC &dc = sharedBitmapDC();

        //const char* pFullFontName = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(pFontName);

        CC_BREAK_IF(! dc.getBitmap(pText, nWidth, nHeight, eAlignMask, pFontName, nSize));

        // assign the dc.m_pData to m_pData in order to save time
        m_pData = (unsigned char*)dc.m_pData;
        CC_BREAK_IF(! m_pData);

        m_nWidth = (short)dc.iMaxLineWidth;
        m_nHeight = (short)dc.iMaxLineHeight;
        m_bHasAlpha = true;
        m_bPreMulti = true;
        m_nBitsPerComponent = 8;

        bRet = true;

        dc.reset();
    } while (0);

    if (!bRet)
      CCLOG("CCImage::initWithString failed");

    //do nothing
    return bRet;
}

std::string BitmapDC::fileNameExtension(const std::string& pathName)
{
    std::string ext ;
    std::string::size_type pos = pathName.find_last_of(".") ;
    if (pos != std::string::npos && pos != pathName.size()-1 )
    {
        ext = pathName.substr(pos+1) ;
    }

    return ext ;
}

bool BitmapDC::startsWith(const std::string& str, const std::string& what)
{
    bool result = false ;
    if (what.size() <= str.size())
    {
        result = (str.substr(0, what.size()) == what);
    }
    return result ;
}

int BitmapDC::openFont(const std::string& fontName, uint fontSize, const std::string& fontNameOrig)
{
    // try to satisfy request based on currently cached font.
    if (m_cachedSize == fontSize)
    {
        if (fontNameOrig == m_cachedFontnameOrig)
          return 0;

        if (fontName == m_cachedFontname)
          return 0;
    }

    FT_Face face;
    int iError = FT_New_Face(m_library, fontName.c_str(), 0, &face);
    if (iError)
      return iError;

    // free existing cached font
    if (m_cachedFont)
      FT_Done_Face(m_cachedFont);

    // cache newly loaded font
    m_cachedFontnameOrig = fontNameOrig;
    m_cachedFontname = fontName;
    m_cachedFont = face;
    m_cachedSize = fontSize;
    return 0;
}

NS_CC_END
