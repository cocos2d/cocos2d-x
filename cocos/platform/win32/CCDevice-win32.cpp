/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#include "platform/CCDevice.h"
#include "platform/CCFileUtils.h"
#include "platform/CCStdC.h"

NS_CC_BEGIN

int Device::getDPI()
{
    static int dpi = -1;
    if (dpi == -1)
    {
        HDC hScreenDC = GetDC( nullptr );
        int PixelsX = GetDeviceCaps( hScreenDC, HORZRES );
        int MMX = GetDeviceCaps( hScreenDC, HORZSIZE );
        ReleaseDC( nullptr, hScreenDC );
        dpi = 254.0f*PixelsX/MMX/10;
    }
    return dpi;
}

void Device::setAccelerometerEnabled(bool isEnabled)
{}

void Device::setAccelerometerInterval(float interval)
{}

class BitmapDC
{
public:
    BitmapDC(HWND hWnd = nullptr)
        : _DC(nullptr)
        , _bmp(nullptr)
        , _font((HFONT)GetStockObject(DEFAULT_GUI_FONT))
        , _wnd(nullptr)
    {
        _wnd = hWnd;
        HDC hdc = GetDC(hWnd);
        _DC   = CreateCompatibleDC(hdc);
        ReleaseDC(hWnd, hdc);
    }

    ~BitmapDC()
    {
        prepareBitmap(0, 0);
        if (_DC)
        {
            DeleteDC(_DC);
        }
        removeCustomFont();
    }

    wchar_t * utf8ToUtf16(const std::string& str)
    {
        wchar_t * pwszBuffer = nullptr;
        do
        {
            if (str.empty())
            {
                break;
            }
            // utf-8 to utf-16
            int nLen = str.size();
            int nBufLen  = nLen + 1;
            pwszBuffer = new wchar_t[nBufLen];
            CC_BREAK_IF(! pwszBuffer);
            memset(pwszBuffer,0,nBufLen);
            nLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), nLen, pwszBuffer, nBufLen);
            pwszBuffer[nLen] = '\0';
        } while (0);
        return pwszBuffer;

    }

    bool setFont(const char * pFontName = "", int nSize = 0)
    {
        bool bRet = false;
        do
        {
            std::string fontName = pFontName;
            std::string fontPath;
            HFONT       hDefFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
            LOGFONTA    tNewFont = {0};
            LOGFONTA    tOldFont = {0};
            GetObjectA(hDefFont, sizeof(tNewFont), &tNewFont);
            if (!fontName.empty())
            {
                // create font from ttf file
                if (FileUtils::getInstance()->getFileExtension(fontName) == ".ttf")
                {
                    fontPath = FileUtils::getInstance()->fullPathForFilename(fontName.c_str());
                    int nFindPos = fontName.rfind("/");
                    fontName = &fontName[nFindPos+1];
                    nFindPos = fontName.rfind(".");
                    fontName = fontName.substr(0,nFindPos);
                }
                else
                {
                    auto nFindPos = fontName.rfind("/");
                    if (nFindPos != fontName.npos)
                    {
                        if (fontName.length() == nFindPos + 1)
                        {
                            fontName = "";
                        }
                        else
                        {
                            fontName = &fontName[nFindPos+1];
                        }
                    }
                }
                tNewFont.lfCharSet = DEFAULT_CHARSET;
                strcpy_s(tNewFont.lfFaceName, LF_FACESIZE, fontName.c_str());
            }
            if (nSize)
            {
                tNewFont.lfHeight = -nSize;
            }
            GetObjectA(_font,  sizeof(tOldFont), &tOldFont);

            if (tOldFont.lfHeight == tNewFont.lfHeight
                && 0 == strcmp(tOldFont.lfFaceName, tNewFont.lfFaceName))
            {
                // already has the font
                bRet = true;
                break;
            }

            // delete old font
            removeCustomFont();

            if (fontPath.size() > 0)
            {
                _curFontPath = fontPath;
                wchar_t * pwszBuffer = utf8ToUtf16(_curFontPath);
                if (pwszBuffer)
                {
                    if(AddFontResource(pwszBuffer))
                    {
                        SendMessage( _wnd, WM_FONTCHANGE, 0, 0);
                    }
                    delete [] pwszBuffer;
                    pwszBuffer = nullptr;
                }
            }

            _font = nullptr;

            // disable Cleartype
            tNewFont.lfQuality = ANTIALIASED_QUALITY;

            // create new font
            _font = CreateFontIndirectA(&tNewFont);
            if (! _font)
            {
                // create failed, use default font
                _font = hDefFont;
                break;
            }

            bRet = true;
        } while (0);
        return bRet;
    }

    SIZE sizeWithText(const wchar_t * pszText, int nLen, DWORD dwFmt, LONG nWidthLimit)
    {
        SIZE tRet = {0};
        do
        {
            CC_BREAK_IF(! pszText || nLen <= 0);

            RECT rc = {0, 0, 0, 0};
            DWORD dwCalcFmt = DT_CALCRECT;

            if (nWidthLimit > 0)
            {
                rc.right = nWidthLimit;
                dwCalcFmt |= DT_WORDBREAK
                    | (dwFmt & DT_CENTER)
                    | (dwFmt & DT_RIGHT);
            }
            // use current font to measure text extent
            HGDIOBJ hOld = SelectObject(_DC, _font);

            // measure text size
            DrawTextW(_DC, pszText, nLen, &rc, dwCalcFmt);
            SelectObject(_DC, hOld);

            tRet.cx = rc.right;
            tRet.cy = rc.bottom;
        } while (0);

        return tRet;
    }

    bool prepareBitmap(int nWidth, int nHeight)
    {
        // release bitmap
        if (_bmp)
        {
            DeleteObject(_bmp);
            _bmp = nullptr;
        }
        if (nWidth > 0 && nHeight > 0)
        {
            _bmp = CreateBitmap(nWidth, nHeight, 1, 32, nullptr);
            if (! _bmp)
            {
                return false;
            }
        }
        return true;
    }

    int drawText(const char * pszText, SIZE& tSize, Device::TextAlign eAlign)
    {
        int nRet = 0;
        wchar_t * pwszBuffer = nullptr;
        wchar_t* fixedText = nullptr;
        do
        {
            CC_BREAK_IF(! pszText);

            DWORD dwFmt = DT_WORDBREAK;
            DWORD dwHoriFlag = (int)eAlign & 0x0f;
            DWORD dwVertFlag = ((int)eAlign & 0xf0) >> 4;

            switch (dwHoriFlag)
            {
            case 1: // left
                dwFmt |= DT_LEFT;
                break;
            case 2: // right
                dwFmt |= DT_RIGHT;
                break;
            case 3: // center
                dwFmt |= DT_CENTER;
                break;
            }

            int nLen = strlen(pszText);
            // utf-8 to utf-16
            int nBufLen  = nLen + 1;
            pwszBuffer = new wchar_t[nBufLen];
            CC_BREAK_IF(! pwszBuffer);

            memset(pwszBuffer, 0, sizeof(wchar_t)*nBufLen);
            nLen = MultiByteToWideChar(CP_UTF8, 0, pszText, nLen, pwszBuffer, nBufLen);

            if (strchr(pszText, '&'))
            {
                fixedText = new wchar_t[nLen * 2 + 1];
                int fixedIndex = 0;
                for (int index = 0; index < nLen; ++index)
                {
                    if (pwszBuffer[index] == '&')
                    {
                        fixedText[fixedIndex] = '&';
                        fixedText[fixedIndex + 1] = '&';
                        fixedIndex += 2;
                    }
                    else
                    {
                        fixedText[fixedIndex] = pwszBuffer[index];
                        fixedIndex += 1;
                    }
                }
                fixedText[fixedIndex] = '\0';
                nLen = fixedIndex;
            }

            SIZE newSize;
            if (fixedText)
            {
                newSize = sizeWithText(fixedText, nLen, dwFmt, tSize.cx);
            }
            else
            {
                newSize = sizeWithText(pwszBuffer, nLen, dwFmt, tSize.cx);
            }

            RECT rcText = {0};
            // if content width is 0, use text size as content size
            if (tSize.cx <= 0)
            {
                tSize = newSize;
                rcText.right  = newSize.cx;
                rcText.bottom = newSize.cy;
            }
            else
            {

                LONG offsetX = 0;
                LONG offsetY = 0;
                rcText.right = newSize.cx; // store the text width to rectangle

                // calculate text horizontal offset
                if (1 != dwHoriFlag          // and text isn't align to left
                    && newSize.cx < tSize.cx)   // and text's width less then content width,
                {                               // then need adjust offset of X.
                    offsetX = (2 == dwHoriFlag) ? tSize.cx - newSize.cx     // align to right
                        : (tSize.cx - newSize.cx) / 2;                      // align to center
                }

                // if content height is 0, use text height as content height
                // else if content height less than text height, use content height to draw text
                if (tSize.cy <= 0)
                {
                    tSize.cy = newSize.cy;
                    dwFmt   |= DT_NOCLIP;
                    rcText.bottom = newSize.cy; // store the text height to rectangle
                }
                else if (tSize.cy < newSize.cy)
                {
                    // content height larger than text height need, clip text to rect
                    rcText.bottom = tSize.cy;
                }
                else
                {
                    rcText.bottom = newSize.cy; // store the text height to rectangle

                    // content larger than text, need adjust vertical position
                    dwFmt |= DT_NOCLIP;

                    // calculate text vertical offset
                    offsetY = (2 == dwVertFlag) ? tSize.cy - newSize.cy     // align to bottom
                        : (3 == dwVertFlag) ? (tSize.cy - newSize.cy) / 2   // align to middle
                        : 0;                                                // align to top
                }

                if (offsetX || offsetY)
                {
                    OffsetRect(&rcText, offsetX, offsetY);
                }
            }

            CC_BREAK_IF(! prepareBitmap(tSize.cx, tSize.cy));

            // draw text
            HGDIOBJ hOldFont = SelectObject(_DC, _font);
            HGDIOBJ hOldBmp  = SelectObject(_DC, _bmp);

            SetBkMode(_DC, TRANSPARENT);
            SetTextColor(_DC, RGB(255, 255, 255)); // white color

            // draw text
            if (fixedText)
            {
                nRet = DrawTextW(_DC, fixedText, nLen, &rcText, dwFmt);
            }
            else
            {
                nRet = DrawTextW(_DC, pwszBuffer, nLen, &rcText, dwFmt);
            }

            //DrawTextA(_DC, pszText, nLen, &rcText, dwFmt);

            SelectObject(_DC, hOldBmp);
            SelectObject(_DC, hOldFont);
        } while (0);
        CC_SAFE_DELETE_ARRAY(pwszBuffer);
        delete[] fixedText;

        return nRet;
    }

    CC_SYNTHESIZE_READONLY(HDC, _DC, DC);
    CC_SYNTHESIZE_READONLY(HBITMAP, _bmp, Bitmap);
private:

    friend class Image;
    HFONT   _font;
    HWND    _wnd;
    std::string _curFontPath;

    void removeCustomFont()
    {
        HFONT hDefFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
        if (hDefFont != _font)
        {
            DeleteObject(_font);
            _font = hDefFont;
        }
        // release temp font resource
        if (_curFontPath.size() > 0)
        {
            wchar_t * pwszBuffer = utf8ToUtf16(_curFontPath);
            if (pwszBuffer)
            {
                RemoveFontResource(pwszBuffer);
                SendMessage( _wnd, WM_FONTCHANGE, 0, 0);
                delete [] pwszBuffer;
                pwszBuffer = nullptr;
            }
            _curFontPath.clear();
        }
    }
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
        BitmapDC& dc = sharedBitmapDC();

        if (! dc.setFont(textDefinition._fontName.c_str(), textDefinition._fontSize))
        {
            log("Can't found font(%s), use system default", textDefinition._fontName.c_str());
        }

        // draw text
        // does changing to SIZE here affects the font size by rounding from float?
        SIZE size = {(LONG) textDefinition._dimensions.width,(LONG) textDefinition._dimensions.height};
        CC_BREAK_IF(! dc.drawText(text, size, align));

        int dataLen = size.cx * size.cy * 4;
        unsigned char* dataBuf = (unsigned char*)malloc(sizeof(unsigned char) * dataLen);
        CC_BREAK_IF(! dataBuf);

        struct
        {
            BITMAPINFOHEADER bmiHeader;
            int mask[4];
        } bi = {0};
        bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
        CC_BREAK_IF(! GetDIBits(dc.getDC(), dc.getBitmap(), 0, 0,
            nullptr, (LPBITMAPINFO)&bi, DIB_RGB_COLORS));

        width    = (short)size.cx;
        height   = (short)size.cy;

        // copy pixel data
        bi.bmiHeader.biHeight = (bi.bmiHeader.biHeight > 0)
            ? - bi.bmiHeader.biHeight : bi.bmiHeader.biHeight;
        GetDIBits(dc.getDC(), dc.getBitmap(), 0, height, dataBuf,
            (LPBITMAPINFO)&bi, DIB_RGB_COLORS);

        COLORREF textColor = (textDefinition._fontFillColor.b << 16 | textDefinition._fontFillColor.g << 8 | textDefinition._fontFillColor.r) & 0x00ffffff;
        float alpha = textDefinition._fontAlpha / 255.0f;
        COLORREF * pPixel = nullptr;
        for (int y = 0; y < height; ++y)
        {
            pPixel = (COLORREF *)dataBuf + y * width;
            for (int x = 0; x < width; ++x)
            {
                COLORREF& clr = *pPixel;
                clr = ((BYTE)(GetRValue(clr) * alpha) << 24) | textColor;
                ++pPixel;
            }
        }

        ret.fastSet(dataBuf,dataLen);
        hasPremultipliedAlpha = false;
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

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
