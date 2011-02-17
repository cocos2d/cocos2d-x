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

#include "TG3.h"

NS_CC_BEGIN

void ccxMessageBox(const ccxString& msg, const ccxString& title)
{
    TUChar szText[256] = { 0 };
    TUString::StrUtf8ToStrUnicode(szText,(Char*)msg.c_str());
    TMessageBox box(szText, NULL, WMB_OK);
    box.Show();
}

class BitmapDC
{
public:
    BitmapDC()
    : m_pBmp(NULL)
    , m_pMemWnd(NULL)
    {

    }

    ~BitmapDC(void)
    {
        prepareBitmap(0, 0);
    }

    bool setFont(const char * pFontName = NULL, int nSize = 0)
    {
        bool bRet = false;
        do 
        {
            CCX_BREAK_IF(! m_hFont.Create(0, (Int32)nSize));
            bRet = true;
        } while (0);
        return bRet;
    }

    bool getTextExtentPoint(TUChar* pszText, int nLen, TSize& tSize)
    {
        bool bRet = false;
        do 
        {
            CCX_BREAK_IF(! pszText);
            tSize.SetWidth(m_hFont.CharsWidth(pszText,nLen));
            tSize.SetHeight(m_hFont.LineHeight());
        } while (0);
        return bRet;
    }

    bool prepareBitmap(int nWidth, int nHeight)
    {
        // release bitmap
        if (m_pBmp)
        {
            m_pBmp->Destroy();
            m_pBmp = NULL;
        }
        if (nWidth > 0 && nHeight > 0)
        {
            m_pBmp = TBitmap::Create(nWidth, nHeight, 32);
            if (! m_pBmp)
            {
                return false;
            }
        }
        return true;
    }

    int drawText(TUChar* pszText, int nLen, TSize& tSize, UInt32 style)
    {
        int nRet = 0;
        do 
        {
            CCX_BREAK_IF(! pszText);

            if (tSize.Width() <= 0 || tSize.Height() <= 0)
            {
                CCX_BREAK_IF(! getTextExtentPoint(pszText, nLen, tSize));
            }
            CCX_BREAK_IF(tSize.Width() <= 0 || tSize.Height() <= 0);

            CCX_BREAK_IF(! prepareBitmap(tSize.Width(), tSize.Height()));

            Int32 nWidth  = tSize.Width();
            Int32 nHeight = tSize.Height();

            // create memory window
            if (m_pMemWnd)
            {
                TRectangle rcMemWnd(0, 0, 0, 0);
                m_pMemWnd->GetClientBounds(&rcMemWnd);
                if (rcMemWnd.Width() < nWidth || rcMemWnd.Height() < nHeight)
                {
                    m_pMemWnd->CloseWindow();
                    m_pMemWnd = NULL;
                }
            }

            do 
            {
                // if memory window is already break
                CCX_BREAK_IF(m_pMemWnd);

                TApplication* pApp = TApplication::GetCurrentApplication();
                CCX_BREAK_IF(! pApp || ! (m_pMemWnd = new TWindow(pApp)));

                Coord nCurrentWidth = pApp->GetScreenWidth();
                Coord nCurrentHeight = pApp->GetScreenHeight();

                Coord nMemWndW = (nWidth >= nCurrentWidth) ? nWidth : nCurrentWidth;
                Coord nMemWndH = (nHeight >= nCurrentHeight) ? nHeight : nCurrentHeight;
                CCX_BREAK_IF(m_pMemWnd->CreateMemWindow(nMemWndW, nMemWndH,screenAlphaFormat));
                delete m_pMemWnd;
                m_pMemWnd = NULL;
            } while (0);
            CCX_BREAK_IF(! m_pMemWnd);

            // create DC
            TDC dc(m_pMemWnd);

            // draw text
            m_pMemWnd->GetMemWindowTBitmapPtr()->Fill32(RGBA(0, 0, 0, 0), 0, 0, nWidth, nHeight);

            TRectangle rect(0, 0, nWidth, nHeight);
            dc.DrawTextInRectangleEx(pszText, 0, RGBA(255,255,255,255), RGBA(0,0,0,255), m_hFont, &rect, style);

            dc.ReadBitmap(m_pBmp, 0, 0);

            nRet = true;
        } while (0);
        return nRet;
    }

    CCX_SYNTHESIZE_READONLY(TBitmap*, m_pBmp, Bitmap);

private:
    TFont m_hFont;
    TWindow * m_pMemWnd;
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
    TUChar* pWText = NULL;
    do 
    {
        CCX_BREAK_IF(! pText);
        int nLen = strlen(pText) + 1;
        CCX_BREAK_IF(! (pWText = new TUChar[nLen]));
        TUString::StrGBToUnicode(pWText, (Char*)pText);

        BitmapDC& dc = sharedBitmapDC();

        dc.setFont(pFontName, nSize);

        TSize size(0, 0);
        if (nWidth > 0 && nHeight > 0)
        {
            size.SetSize(nWidth, nHeight);
        }
        else
        {
            dc.getTextExtentPoint(pWText, nLen, size);
        }
        CCX_BREAK_IF(! size.Width() || ! size.Height());

        // set style
        UInt32 styles = GUI_API_STYLE_SPECIFY_FORE_COLOR |  GUI_API_STYLE_ROP_MODE_TRANSPARENT |
            GUI_API_STYLE_CLIP_WORDWRAP | GUI_API_STYLE_SPECIFY_BACK_COLOR | GUI_API_STYLE_SPECIFY_FONT;

        switch (eAlignMask)
        {
        case kAlignCenter:
            styles |= GUI_API_STYLE_ALIGNMENT_CENTER | GUI_API_STYLE_ALIGNMENT_MIDDLE;
            break;
        case kAlignTop:
            styles |= GUI_API_STYLE_ALIGNMENT_CENTER | GUI_API_STYLE_ALIGNMENT_TOP;
            break;
        case kAlignTopRight:
            styles |= GUI_API_STYLE_ALIGNMENT_RIGHT | GUI_API_STYLE_ALIGNMENT_TOP;
            break;
        case kAlignRight:
            styles |= GUI_API_STYLE_ALIGNMENT_RIGHT | GUI_API_STYLE_ALIGNMENT_MIDDLE;
            break;
        case kAlignBottomRight:
            styles |= GUI_API_STYLE_ALIGNMENT_RIGHT | GUI_API_STYLE_ALIGNMENT_BOTTOM;
            break;
        case kAlignBottom:
            styles |= GUI_API_STYLE_ALIGNMENT_CENTER | GUI_API_STYLE_ALIGNMENT_BOTTOM;
            break;
        case kAlignBottomLeft:
            styles |= GUI_API_STYLE_ALIGNMENT_LEFT | GUI_API_STYLE_ALIGNMENT_BOTTOM;
            break;
        case kAlignLeft:
            styles |= GUI_API_STYLE_ALIGNMENT_LEFT | GUI_API_STYLE_ALIGNMENT_MIDDLE;
            break;
        case kAlignTopLeft:
            styles |= GUI_API_STYLE_ALIGNMENT_LEFT | GUI_API_STYLE_ALIGNMENT_TOP;
        }

        CCX_BREAK_IF(! dc.drawText(pWText, nLen, size, styles));

        // init image information
        TBitmap * pBitmap = dc.getBitmap();
        CCX_BREAK_IF(! pBitmap);

        INT32 nWidth	= pBitmap->GetWidth();
        INT32 nHeight	= pBitmap->GetHeight();
        CCX_BREAK_IF(nWidth <= 0 || nHeight <= 0);

        INT32 nDataLen = pBitmap->GetRowBytes() * nHeight;
        m_pData.reset(new ccxByte[nDataLen]);
        CCX_BREAK_IF(! m_pData.get());
        memcpy((void*) m_pData.get(), pBitmap->GetDataPtr(), nDataLen);

        m_nWidth    = (ccxInt16)nWidth;
        m_nHeight   = (ccxInt16)nHeight;
        m_bHasAlpha = true;
        m_bPreMulti = true;
        m_nBitsPerComponent = pBitmap->GetDepth() / 4;

        bRet = true;
    } while (0);

    if (pWText)
    {
        delete [] pWText;
        pWText = NULL;
    }

    return bRet;
}

NS_CC_END;
