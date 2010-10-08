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
// 	CCXBitmapDC::CCXBitmapDC(const char *text, CGSize dimensions, UITextAlignment alignment, const char *fontName, float fontSize)
// 	{
// 		// create font
// 		HFONT hFont = NULL;
// // 		font.Create(0, (Int32)fontSize);
// 
// 		// text
// 		int len = strlen(text);
// 		WCHAR *pText = new WCHAR[len + 1];
//         MultiByteToWideChar(CP_ACP, 0, text, len, pText, len + 1);
// 
//         DWORD dwStyle = 0;
// 
// 		switch (alignment)
// 		{
// 		case UITextAlignmentLeft:
// 			dwStyle |= GUI_API_STYLE_ALIGNMENT_LEFT;
// 			break;
// 		case UITextAlignmentCenter:
// 			dwStyle |= GUI_API_STYLE_ALIGNMENT_CENTER;
// 			break;
// 		case UITextAlignmentRight:
// 			dwStyle |= GUI_API_STYLE_ALIGNMENT_RIGHT;
// 			break;
// 		default:
// 			dwStyle |= GUI_API_STYLE_ALIGNMENT_CENTER;
// 			break;
// 		}
// 
//         FillRect(m_hMemDC, NULL, )
// 		
//  		dc.DrawTextInRectangleEx(pText, 0, RGBA(255,255,255,255), RGBA(0,0,0,255), font, &rect, styles);
// 
// 		delete [] pText;
// 	}

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
}
