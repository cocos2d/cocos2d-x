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

NS_CC_BEGIN;

void ccxMessageBox(const ccxString& msg, const ccxString& title)
{
    MessageBoxA(NULL, msg.c_str(), title.c_str(), MB_OK);
}

/**
@brief	A memory DC which uses to draw text on bitmap.
*/
class BitmapDC
{
public:
    BitmapDC(HWND hWnd = NULL)
    : m_hDC(NULL)
    , m_hBmp(NULL)
    , m_hFont((HFONT)GetStockObject(DEFAULT_GUI_FONT))
    {
        HDC hdc = GetDC(hWnd);
        m_hDC   = CreateCompatibleDC(hdc);
        ReleaseDC(hWnd, hdc);
    }

    ~BitmapDC()
    {
        prepareBitmap(0, 0);
        if (m_hDC)
        {
            DeleteDC(m_hDC);
        }
    }

    bool setFont(const char * pFontName = NULL, int nSize = 0)
    {
        bool bRet = false;
        do 
        {
            HFONT       hDefFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
            LOGFONTA    tNewFont = {0};
            LOGFONTA    tOldFont = {0};
            GetObjectA(hDefFont, sizeof(tNewFont), &tNewFont);
            if (pFontName)
            {
                strcpy_s(tNewFont.lfFaceName, LF_FACESIZE, pFontName);
            }
            if (nSize)
            {
                tNewFont.lfHeight = -nSize;
            }
            GetObjectA(m_hFont,  sizeof(tOldFont), &tOldFont);

            if (tOldFont.lfHeight == tNewFont.lfHeight
                && ! strcpy(tOldFont.lfFaceName, tNewFont.lfFaceName))
            {
                // already has the font 
                bRet = true;
                break;
            }

            // delete old font
            if (m_hFont != hDefFont)
            {
                DeleteObject(m_hFont);
            }
            m_hFont = NULL;

            // create new font
            m_hFont = CreateFontIndirectA(&tNewFont);
            if (! m_hFont)
            {
                // create failed, use default font
                m_hFont = hDefFont;
                break;
            }
            
            bRet = true;
        } while (0);
        return bRet;
    }

    bool getTextExtentPoint(const char * pszText, int nLen, SIZE& tSize)
    {
        bool bRet = false;
        do 
        {
            CCX_BREAK_IF(! pszText);
            HGDIOBJ hOld = SelectObject(m_hDC, m_hFont);
            bRet = (GetTextExtentPointA(m_hDC, pszText, nLen, &tSize)) ? true : false;
            SelectObject(m_hDC, hOld);
        } while (0);
        return bRet;
    }

    bool prepareBitmap(int nWidth, int nHeight)
    {
        // release bitmap
        if (m_hBmp)
        {
            DeleteObject(m_hBmp);
            m_hBmp = NULL;
        }
        if (nWidth > 0 && nHeight > 0)
        {
            m_hBmp = CreateBitmap(nWidth, nHeight, 1, 32, NULL);
            if (! m_hBmp)
            {
                return false;
            }
        }
        return true;
    }

    int drawText(const char * pszText, int nLen, SIZE& tSize, DWORD dwFmt)
    {
        int nRet = 0;
        do 
        {
            CCX_BREAK_IF(! pszText);

            if (tSize.cx <= 0 || tSize.cy <= 0)
            {
                CCX_BREAK_IF(! getTextExtentPoint(pszText, nLen, tSize));
            }
            CCX_BREAK_IF(tSize.cx <= 0 || tSize.cy <= 0);

            CCX_BREAK_IF(! prepareBitmap(tSize.cx, tSize.cy));

            // draw text
            HGDIOBJ hOldFont = SelectObject(m_hDC, m_hFont);
            HGDIOBJ hOldBmp  = SelectObject(m_hDC, m_hBmp);

            RECT rc = {0, 0, tSize.cx, tSize.cy};
            SetBkMode(m_hDC, TRANSPARENT);
            SetTextColor(m_hDC, RGB(255, 255, 255)); // white color
            nRet = DrawTextA(m_hDC, pszText, nLen, &rc, dwFmt);

            SelectObject(m_hDC, hOldBmp);
            SelectObject(m_hDC, hOldFont);
        } while (0);
        return nRet;
    }

    CCX_SYNTHESIZE_READONLY(HDC, m_hDC, DC);
    CCX_SYNTHESIZE_READONLY(HBITMAP, m_hBmp, Bitmap);
private:
    friend class ccxImage;
    HFONT   m_hFont;
};

static BitmapDC& sharedBitmapDC()
{
    static BitmapDC s_BmpDC;
    return s_BmpDC;
}

bool ccxImage::initWithString(
                               const char *    pText, 
                               int             nWidth/* = 0*/, 
                               int             nHeight/* = 0*/,
                               ETextAlign      eAlignMask/* = kAlignCenter*/,
                               const char *    pFontName/* = nil*/,
                               int             nSize/* = 0*/)
{
    bool bRet = false;
    do 
    {
        CCX_BREAK_IF(! pText);
        int nLen = strlen(pText);

        BitmapDC& dc = sharedBitmapDC();

        dc.setFont(pFontName, nSize);

        SIZE size = {0, 0};
        if (nWidth > 0 && nHeight > 0)
        {
            size.cx = nWidth;
            size.cy = nHeight;
        }
        else
        {
            dc.getTextExtentPoint(pText, nLen, size);
        }
        CCX_BREAK_IF(! size.cx || ! size.cy);

        // set style
        DWORD dwFmt = DT_SINGLELINE;

        switch (eAlignMask)
        {
        case kAlignCenter:
            dwFmt |= DT_CENTER | DT_VCENTER;
            break;
        case kAlignTop:
            dwFmt |= DT_CENTER | DT_TOP;
            break;
        case kAlignTopRight:
            dwFmt |= DT_RIGHT | DT_TOP;
            break;
        case kAlignRight:
            dwFmt |= DT_RIGHT | DT_VCENTER;
            break;
        case kAlignBottomRight:
            dwFmt |= DT_RIGHT | DT_BOTTOM;
            break;
        case kAlignBottom:
            dwFmt |= DT_CENTER | DT_BOTTOM;
            break;
        case kAlignBottomLeft:
            dwFmt |= DT_LEFT | DT_BOTTOM;
            break;
        case kAlignLeft:
            dwFmt |= DT_LEFT | DT_VCENTER;
            break;
        case kAlignTopLeft:
            dwFmt |= DT_LEFT | DT_TOP;
            break;
        }

        CCX_BREAK_IF(! dc.drawText(pText, nLen, size, dwFmt));

        m_pData.reset(new ccxByte[size.cx * size.cy * 4]);
        CCX_BREAK_IF(! m_pData.get());

        struct
        {
            BITMAPINFOHEADER bmiHeader;
            int mask[4];
        } bi = {0};
        bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
        CCX_BREAK_IF(! GetDIBits(dc.getDC(), dc.getBitmap(), 0, 0, 
            NULL, (LPBITMAPINFO)&bi, DIB_RGB_COLORS));

        m_nWidth    = (ccxInt16)size.cx;
        m_nHeight   = (ccxInt16)size.cy;
        m_bHasAlpha = true;
        m_bPreMulti = false;
        m_nBitsPerComponent = 8;

        // copy pixed data
        bi.bmiHeader.biHeight = (bi.bmiHeader.biHeight > 0)
           ? - bi.bmiHeader.biHeight : bi.bmiHeader.biHeight;
        GetDIBits(dc.getDC(), dc.getBitmap(), 0, m_nHeight, m_pData.get(), 
            (LPBITMAPINFO)&bi, DIB_RGB_COLORS);

        // change pixel's alpha value to 255, when it's RGB != 0
        COLORREF * pPixel = NULL;
        for (int y = 0; y < m_nHeight; ++y)
        {
            pPixel = (COLORREF *)m_pData.get() + y * m_nWidth;
            for (int x = 0; x < m_nWidth; ++x)
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

NS_CC_END;
