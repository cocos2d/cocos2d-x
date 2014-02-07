/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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
#define __CC_PLATFORM_IMAGE_CPP__

#include "CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#if _MSC_VER
#include <cctype>
#endif
#include "platform/CCImageCommon_cpp.h"

NS_CC_BEGIN

/**
@brief    A memory DC which uses to draw text on bitmap.
*/
class BitmapDC
{
public:
    BitmapDC(HWND hWnd = NULL)
    : _DC(NULL)
    , _bmp(NULL)
    , _font((HFONT)GetStockObject(DEFAULT_GUI_FONT))
    , _wnd(NULL)
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
				pwszBuffer = NULL;
			}
		}
    }

	wchar_t * utf8ToUtf16(std::string nString)
	{
		wchar_t * pwszBuffer = NULL;
		do 
		{
			if (nString.size() < 0)
			{
				break;
			}
			// utf-8 to utf-16
			int nLen = nString.size();
			int nBufLen  = nLen + 1;			
			pwszBuffer = new wchar_t[nBufLen];
			CC_BREAK_IF(! pwszBuffer);
			memset(pwszBuffer,0,nBufLen);
			nLen = MultiByteToWideChar(CP_UTF8, 0, nString.c_str(), nLen, pwszBuffer, nBufLen);		
			pwszBuffer[nLen] = '\0';
		} while (0);	
		return pwszBuffer;

	}

    bool setFont(const char * pFontName = NULL, int nSize = 0)
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
            if (fontName.c_str())
            {    
                // create font from ttf file
                int nFindttf = fontName.find(".ttf");
                int nFindTTF = fontName.find(".TTF");
                if (nFindttf >= 0 || nFindTTF >= 0)
                {
                    fontPath = FileUtils::getInstance()->fullPathForFilename(fontName.c_str());
                    int nFindPos = fontName.rfind("/");
                    fontName = &fontName[nFindPos+1];
                    nFindPos = fontName.rfind(".");
                    fontName = fontName.substr(0,nFindPos);                
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
            if (_font != hDefFont)
            {
                DeleteObject(_font);
				// release old font register
				if (_curFontPath.size() > 0)
				{
					wchar_t * pwszBuffer = utf8ToUtf16(_curFontPath);
					if (pwszBuffer)
					{
						if(RemoveFontResource(pwszBuffer))
						{
							SendMessage( _wnd, WM_FONTCHANGE, 0, 0);
						}						
						delete [] pwszBuffer;
						pwszBuffer = NULL;
					}
				}
				if (fontPath.size() > 0)
					_curFontPath = fontPath;
				else
					_curFontPath.clear();
				// register temp font
				if (_curFontPath.size() > 0)
				{
					wchar_t * pwszBuffer = utf8ToUtf16(_curFontPath);
					if (pwszBuffer)
					{
						if(AddFontResource(pwszBuffer))
						{
							SendMessage( _wnd, WM_FONTCHANGE, 0, 0);
						}						
						delete [] pwszBuffer;
						pwszBuffer = NULL;
					}
				}
            }
            _font = NULL;

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
            _bmp = NULL;
        }
        if (nWidth > 0 && nHeight > 0)
        {
            _bmp = CreateBitmap(nWidth, nHeight, 1, 32, NULL);
            if (! _bmp)
            {
                return false;
            }
        }
        return true;
    }

    int drawText(const char * pszText, SIZE& tSize, Image::TextAlign eAlign)
    {
        int nRet = 0;
        wchar_t * pwszBuffer = 0;
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

            SIZE newSize = sizeWithText(pwszBuffer, nLen, dwFmt, tSize.cx);

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
            nRet = DrawTextW(_DC, pwszBuffer, nLen, &rcText, dwFmt);
            //DrawTextA(_DC, pszText, nLen, &rcText, dwFmt);

            SelectObject(_DC, hOldBmp);
            SelectObject(_DC, hOldFont);
        } while (0);
        CC_SAFE_DELETE_ARRAY(pwszBuffer);
        return nRet;
    }

    CC_SYNTHESIZE_READONLY(HDC, _DC, DC);
    CC_SYNTHESIZE_READONLY(HBITMAP, _bmp, Bitmap);
private:
    friend class Image;
    HFONT   _font;
    HWND    _wnd;
    std::string _curFontPath;
};

static BitmapDC& sharedBitmapDC()
{
    static BitmapDC s_BmpDC;
    return s_BmpDC;
}

bool Image::initWithString(
                               const char *    pText, 
                               int             nWidth/* = 0*/, 
                               int             nHeight/* = 0*/,
                               TextAlign       eAlignMask/* = kAlignCenter*/,
                               const char *    pFontName/* = nil*/,
                               int             nSize/* = 0*/)
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! pText);       

        BitmapDC& dc = sharedBitmapDC();

        if (! dc.setFont(pFontName, nSize))
        {
            log("Can't found font(%s), use system default", pFontName);
        }

        // draw text
        SIZE size = {nWidth, nHeight};
        CC_BREAK_IF(! dc.drawText(pText, size, eAlignMask));

        _dataLen = size.cx * size.cy * 4;
        _data = new unsigned char[_dataLen];
        CC_BREAK_IF(! _data);

        struct
        {
            BITMAPINFOHEADER bmiHeader;
            int mask[4];
        } bi = {0};
        bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
        CC_BREAK_IF(! GetDIBits(dc.getDC(), dc.getBitmap(), 0, 0, 
            NULL, (LPBITMAPINFO)&bi, DIB_RGB_COLORS));

        _width    = (short)size.cx;
        _height   = (short)size.cy;
        _preMulti = false;
        _renderFormat = Texture2D::PixelFormat::RGBA8888;
        // copy pixed data
        bi.bmiHeader.biHeight = (bi.bmiHeader.biHeight > 0)
           ? - bi.bmiHeader.biHeight : bi.bmiHeader.biHeight;
        GetDIBits(dc.getDC(), dc.getBitmap(), 0, _height, _data, 
            (LPBITMAPINFO)&bi, DIB_RGB_COLORS);

        // change pixel's alpha value to 255, when it's RGB != 0
        COLORREF * pPixel = NULL;
        for (int y = 0; y < _height; ++y)
        {
            pPixel = (COLORREF *)_data + y * _width;
            for (int x = 0; x < _width; ++x)
            {
                COLORREF& clr = *pPixel;
                if (GetRValue(clr) || GetGValue(clr) || GetBValue(clr))
                {
                    clr |= 0xff000000;
                }
                ++pPixel;
            }
        }

        bRet = true;
    } while (0);

    return bRet;
}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
