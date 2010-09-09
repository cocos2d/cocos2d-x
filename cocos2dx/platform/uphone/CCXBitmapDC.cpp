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
#include <cstring>
#include "CCXBitmapDC.h"
#include "CCXApplication_uphone.h"
#include "CCDirector.h"
#include "platform/platform.h"

namespace cocos2d {

	CCXBitmapDC::CCXBitmapDC(int width, int height)
	{
		m_pBitmap->Create(width, height, 32);
	}
	CCXBitmapDC::CCXBitmapDC(const char *text, CGSize dimensions, UITextAlignment alignment, const char *fontName, float fontSize)
	{
		// create font
		TFont font;
		font.Create(0, (Int32)fontSize);
		// text
		Int32 len = strlen(text) + 1;
		TUChar *pText = new TUChar[len];
		TUString::StrUtf8ToStrUnicode(pText, (Char*)text);
		// calculate text size
		if (CGSize::CGSizeEqualToSize(dimensions, CGSizeZero))
		{
			m_tSize.width = font.CharsWidth(pText,len);
			m_tSize.height = font.LineHeight();
		}else
		{
			m_tSize = dimensions;
		}

		Int16 width = (Int16)m_tSize.width;
		Int16 height = (Int16)m_tSize.height;
		// create memory window
		TWindow *pWindow = new TWindow(CCXApplication::getSharedApplication());
		pWindow->CreateMemWindow(width, height, screenAlphaTransparentFormat);
		// create DC
		TDC dc(pWindow);
		// set DC styles
		UInt32 styles = GUI_API_STYLE_ROP_MODE_TRANSPARENT | GUI_API_STYLE_SPECIFY_FORE_COLOR |  GUI_API_STYLE_ROP_MODE_ALPHA |
			 GUI_API_STYLE_ALIGNMENT_MIDDLE | GUI_API_STYLE_SPECIFY_FONT;
		/*UInt32 styles = GUI_API_STYLE_ROP_MODE_TRANSPARENT;*/
		switch (alignment)
		{
		case UITextAlignmentLeft:
			styles |= GUI_API_STYLE_ALIGNMENT_LEFT;
			break;
		case UITextAlignmentCenter:
			styles |= GUI_API_STYLE_ALIGNMENT_CENTER;
			break;
		case UITextAlignmentRight:
			styles |= GUI_API_STYLE_ALIGNMENT_RIGHT;
			break;
		default:
			styles |= GUI_API_STYLE_ALIGNMENT_CENTER;
			break;
		}
		TRectangle rect;
		pWindow->GetWindowFrameRect(&rect);

		m_pBitmap = TBitmap::Create(rect.Width(), rect.Height(), 32);
		m_pBitmap->Fill32(RGBA(0,0,0,0));
		dc.SetBackColor(RGBA(0,0,0,0));
		dc.DrawBitmap(m_pBitmap, 0, 0);
		

		dc.DrawTextInRectangleEx(pText, 0, RGBA(255,255,255,255), RGBA(0,0,0,0), font, &rect, styles);

		dc.ReadBitmap(m_pBitmap, rect.X(), rect.Y());

		/*m_pBitmap = pWindow->GetBitmap()->DupBitmapTo32();*/
		/*m_pBitmap = pWindow->GetMemWindowTBitmapPtr()->DupBitmapTo32();*/

// 		TUChar pszFile[100] = { 0 };
// 		TUString::StrUtf8ToStrUnicode(pszFile, (Char *)"/NEWPLUS/TDA_DATA/tmp.bmp");
// 		m_pBitmap->SaveToFile(pszFile);

		// close window
		pWindow->CloseWindowNow();
		delete [] pText;
	}
	void *CCXBitmapDC::getBuffer()
	{
		return m_pBitmap->GetDataPtr();
	}
	CGSize CCXBitmapDC::getSize()
	{
		return m_tSize;
	}

	TBitmap* CCXBitmapDC::getBitmap()
	{
		return m_pBitmap;
	}
}
