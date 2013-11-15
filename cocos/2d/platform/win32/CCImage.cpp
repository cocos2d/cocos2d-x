/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
			wchar_t * buffer = utf8ToUtf16(_curFontPath);
			if (buffer)
			{
				RemoveFontResource(buffer);
				SendMessage( _wnd, WM_FONTCHANGE, 0, 0);
				delete [] buffer;
				buffer = nullptr;
			}
		}
    }

	wchar_t * utf8ToUtf16(std::string str)
	{
		wchar_t * buffer = nullptr;
		do 
		{
			if (str.size() < 0)
			{
				break;
			}
			// utf-8 to utf-16
			int len = str.size();
			int bufLen  = len + 1;			
			buffer = new wchar_t[bufLen];
			CC_BREAK_IF(! buffer);
			memset(buffer,0,bufLen);
			len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), len, buffer, bufLen);		
			buffer[len] = '\0';
		} while (0);	
		return buffer;

	}

    bool setFont(const char * fontName = nullptr, int size = 0)
    {
        bool bRet = false;
        do 
        {
            std::string fntName = fontName;
            std::string fontPath;
            HFONT       defFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
            LOGFONTA    newFont = {0};
            LOGFONTA    oldFont = {0};
            GetObjectA(defFont, sizeof(newFont), &newFont);
            if (fntName.c_str())
            {    
                // create font from ttf file
                int nFindttf = fntName.find(".ttf");
                int nFindTTF = fntName.find(".TTF");
                if (nFindttf >= 0 || nFindTTF >= 0)
                {
                    fontPath = FileUtils::getInstance()->fullPathForFilename(fntName.c_str());
                    int nFindPos = fntName.rfind("/");
                    fntName = &fntName[nFindPos+1];
                    nFindPos = fntName.rfind(".");
                    fntName = fntName.substr(0,nFindPos);                
                }
                newFont.lfCharSet = DEFAULT_CHARSET;
                strcpy_s(newFont.lfFaceName, LF_FACESIZE, fntName.c_str());
            }
            if (size)
            {
                newFont.lfHeight = -size;
            }
            GetObjectA(_font,  sizeof(oldFont), &oldFont);

            if (oldFont.lfHeight == newFont.lfHeight
                && 0 == strcmp(oldFont.lfFaceName, newFont.lfFaceName))
            {
                // already has the font 
                bRet = true;
                break;
            }

            // delete old font
            if (_font != defFont)
            {
                DeleteObject(_font);
				// release old font register
				if (_curFontPath.size() > 0)
				{
					wchar_t * buffer = utf8ToUtf16(_curFontPath);
					if (buffer)
					{
						if(RemoveFontResource(buffer))
						{
							SendMessage( _wnd, WM_FONTCHANGE, 0, 0);
						}						
						delete [] buffer;
						buffer = NULL;
					}
				}
				if (fontPath.size() > 0)
					_curFontPath = fontPath;
				else
					_curFontPath.clear();
				// register temp font
				if (_curFontPath.size() > 0)
				{
					wchar_t * buffer = utf8ToUtf16(_curFontPath);
					if (buffer)
					{
						if(AddFontResource(buffer))
						{
							SendMessage( _wnd, WM_FONTCHANGE, 0, 0);
						}						
						delete [] buffer;
						buffer = NULL;
					}
				}
            }
            _font = NULL;

            // disable Cleartype
            newFont.lfQuality = ANTIALIASED_QUALITY;

            // create new font
            _font = CreateFontIndirectA(&newFont);
            if (! _font)
            {
                // create failed, use default font
                _font = defFont;
                break;
            }
            
            bRet = true;
        } while (0);
        return bRet;
    }

    SIZE sizeWithText(const wchar_t * text, long len, DWORD fmt, LONG widthLimit)
    {
        SIZE tRet = {0};
        do 
        {
            CC_BREAK_IF(! text || len <= 0);

            RECT rc = {0, 0, 0, 0};
            DWORD calcFmt = DT_CALCRECT;

            if (widthLimit > 0)
            {
                rc.right = widthLimit;
                calcFmt |= DT_WORDBREAK
                    | (fmt & DT_CENTER)
                    | (fmt & DT_RIGHT);
            }
            // use current font to measure text extent
            HGDIOBJ hOld = SelectObject(_DC, _font);

            // measure text size
            DrawTextW(_DC, text, len, &rc, calcFmt);
            SelectObject(_DC, hOld);

            tRet.cx = rc.right;
            tRet.cy = rc.bottom;
        } while (0);

        return tRet;
    }

    bool prepareBitmap(int width, int height)
    {
        // release bitmap
        if (_bmp)
        {
            DeleteObject(_bmp);
            _bmp = NULL;
        }
        if (width > 0 && height > 0)
        {
            _bmp = CreateBitmap(width, height, 1, 32, NULL);
            if (! _bmp)
            {
                return false;
            }
        }
        return true;
    }

    int drawText(const char * text, SIZE& size, Image::TextAlign align)
    {
        int ret = 0;
        wchar_t * buffer = 0;
        do 
        {
            CC_BREAK_IF(! text);

            DWORD dwFmt = DT_WORDBREAK;
            DWORD dwHoriFlag = (int)align & 0x0f;
            DWORD dwVertFlag = ((int)align & 0xf0) >> 4;

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

            long len = strlen(text);
            // utf-8 to utf-16
            int bufLen  = len + 1;
            buffer = new wchar_t[bufLen];
            CC_BREAK_IF(! buffer);

            memset(buffer, 0, sizeof(wchar_t)*bufLen);
            len = MultiByteToWideChar(CP_UTF8, 0, text, len, buffer, bufLen);

            SIZE newSize = sizeWithText(buffer, len, dwFmt, size.cx);

            RECT rcText = {0};
            // if content width is 0, use text size as content size
            if (size.cx <= 0)
            {
                size = newSize;
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
                    && newSize.cx < size.cx)   // and text's width less then content width,
                {                               // then need adjust offset of X.
                    offsetX = (2 == dwHoriFlag) ? size.cx - newSize.cx     // align to right
                        : (size.cx - newSize.cx) / 2;                      // align to center
                }

                // if content height is 0, use text height as content height
                // else if content height less than text height, use content height to draw text
                if (size.cy <= 0)
                {
                    size.cy = newSize.cy;
                    dwFmt   |= DT_NOCLIP;
                    rcText.bottom = newSize.cy; // store the text height to rectangle
                }
                else if (size.cy < newSize.cy)
                {
                    // content height larger than text height need, clip text to rect
                    rcText.bottom = size.cy;
                }
                else
                {
                    rcText.bottom = newSize.cy; // store the text height to rectangle

                    // content larger than text, need adjust vertical position
                    dwFmt |= DT_NOCLIP;

                    // calculate text vertical offset
                    offsetY = (2 == dwVertFlag) ? size.cy - newSize.cy     // align to bottom
                        : (3 == dwVertFlag) ? (size.cy - newSize.cy) / 2   // align to middle
                        : 0;                                                // align to top
                }

                if (offsetX || offsetY)
                {
                    OffsetRect(&rcText, offsetX, offsetY);
                }
            }

            CC_BREAK_IF(! prepareBitmap(size.cx, size.cy));

            // draw text
            HGDIOBJ hOldFont = SelectObject(_DC, _font);
            HGDIOBJ hOldBmp  = SelectObject(_DC, _bmp);
            
            SetBkMode(_DC, TRANSPARENT);
            SetTextColor(_DC, RGB(255, 255, 255)); // white color

            // draw text
            ret = DrawTextW(_DC, buffer, len, &rcText, dwFmt);
            //DrawTextA(_DC, pszText, nLen, &rcText, dwFmt);

            SelectObject(_DC, hOldBmp);
            SelectObject(_DC, hOldFont);
        } while (0);
        CC_SAFE_DELETE_ARRAY(buffer);
        return ret;
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
                               const char *    text, 
                               long            width/* = 0*/, 
                               long            height/* = 0*/,
                               TextAlign       alignMask/* = kAlignCenter*/,
                               const char *    fontName/* = nil*/,
                               long            size/* = 0*/)
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! text);       

        BitmapDC& dc = sharedBitmapDC();

        if (! dc.setFont(fontName, size))
        {
            log("Can't found font(%s), use system default", fontName);
        }

        // draw text
        SIZE textSize = {width, height};
        CC_BREAK_IF(! dc.drawText(text, textSize, alignMask));

        _dataLen = textSize.cx * textSize.cy * 4;
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

        _width    = (long)textSize.cx;
        _height   = (long)textSize.cy;
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
