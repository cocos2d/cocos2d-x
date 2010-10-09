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
#include "CCXBitmapDC.h"
#include "CCDirector.h"

namespace cocos2d {

	CCXBitmapDC::CCXBitmapDC(int width, int height)
	{
        m_hMemDC = CreateDC(NULL, NULL, NULL, NULL);
		m_hBmp   = CreateBitmap(width, height, 1, 32, NULL);
        m_hOld   = SelectObject(m_hMemDC, m_hBmp);
	}
 	CCXBitmapDC::CCXBitmapDC(const char *text, CGSize dimensions, UITextAlignment alignment, const char *fontName, float fontSize)
 	{
		HWND hWnd  = CCDirector::getSharedDirector()->getOpenGLView()->getHWnd();
		HDC hWndDC = GetDC(hWnd);
		m_hMemDC = CreateCompatibleDC(hWndDC);
		ReleaseDC(hWnd, hWndDC);

		// create font
		HFONT hFont = NULL;
		HFONT hNewFont = NULL;
		LOGFONT lFont = {0};
		lFont.lfHeight = -MulDiv((int)fontSize, GetDeviceCaps(m_hMemDC, LOGPIXELSY), 72);
		MultiByteToWideChar(CP_ACP, 0, fontName, -1, lFont.lfFaceName, LF_FACESIZE);
		hFont = CreateFontIndirect(&lFont);
		if (hFont)
		{
			hNewFont = hFont;
		}
		else
		{
			hNewFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
		}
		HGDIOBJ hOldFont = SelectObject(m_hMemDC, hNewFont);

		// text
		int len = strlen(text) + 1;
		WCHAR *pText = new WCHAR[len];
        MultiByteToWideChar(CP_ACP, 0, text, len, pText, len);

		// calculate text size
		SIZE extent;
		if (CGSize::CGSizeEqualToSize(dimensions, CGSizeZero))
		{
			GetTextExtentPoint(m_hMemDC, pText, len, &extent);
		}
		else
		{
			extent.cx = (int)dimensions.width;
			extent.cy = (int)dimensions.height;
		}

		// create hbitmap
		m_hBmp = CreateBitmap(extent.cx, extent.cy, 1, 32, NULL);
		m_hOld = SelectObject(m_hMemDC, m_hBmp);

		// set style
        DWORD dwStyle = DT_SINGLELINE | DT_VCENTER;

		switch (alignment)
		{
		case UITextAlignmentLeft:
			dwStyle |= DT_LEFT;
			break;
		case UITextAlignmentCenter:
			dwStyle |= DT_CENTER;
			break;
		case UITextAlignmentRight:
			dwStyle |= DT_RIGHT;
			break;
		default:
			dwStyle |= DT_CENTER;
			break;
		}

		// draw text
		RECT rc = {0, 0, extent.cx, extent.cy};
		SetBkMode(m_hMemDC, TRANSPARENT);
		DrawText(m_hMemDC, pText, len, &rc, dwStyle);

		// free resource
 		delete [] pText;
		SelectObject(m_hMemDC, hOldFont);
		if (hFont)
		{
			DeleteObject(hFont);
		}
 	}

	CCXBitmapDC::~CCXBitmapDC(void)
	{
		SelectObject(m_hMemDC, m_hOld);
        DeleteObject(m_hBmp);
        DeleteDC(m_hMemDC);
	}

	HBITMAP CCXBitmapDC::getBitmap()
	{
		return m_hBmp;
	}

	HDC CCXBitmapDC::getDC()
	{
		return m_hMemDC;
	}
}
