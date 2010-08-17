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
#include "ImageToolKit/IT_ImageDrawingTool.h"

namespace cocos2d {

	CCXBitmapDC::CCXBitmapDC(const char *text, CGSize dimensions, UITextAlignment alignment, const char *fontName, float fontSize)
	{
		TFont font;
		font.Create(0, fontSize);
		int len = strlen(text) + 1;
		TUChar *pText = new TUChar[len];
		TUString::StrUtf8ToStrUnicode(pText, (Char*)text);

		if (CGSize::CGSizeEqualToSize(dimensions, CGSizeZero))
		{
			m_tTextSize.width = font.CharsWidth(pText,len);
			m_tTextSize.height = font.LineHeight();
		}else
		{
			m_tTextSize = dimensions;
		}

		int i;
		int width = (int)m_tTextSize.width;
		int height = (int)m_tTextSize.height;
		if((width!= 1) && (width & (width - 1))) 
		{
			i = 1;
			while(i < width)
				i<<=1;
			width = i;
		}
		if((height != 1) && (height & (height - 1))) 
		{
			i = 1;
			while(i < height)
				i <<= 1;
			height = i;
		}

		m_tScaleSize.width = (float)width;
		m_tScaleSize.height = (float)height;

		TWindow *pWindow = new TWindow(CCXApplication::getSharedApplication());
		pWindow->CreateMemWindow(width, height, screenAlphaTransparentFormat);
   		TDC dc(pWindow);
		dc.SetFont(font);
 		dc.DrawTextXYEx(pText, 0, 0, 0, RGBA(255,255,0,255), RGBA(0,0,0,0), font, 
			GUI_API_STYLE_ROP_MODE_TRANSPARENT | GUI_API_STYLE_SPECIFY_FORE_COLOR |  
			GUI_API_STYLE_ALIGNMENT_CENTER | GUI_API_STYLE_ALIGNMENT_MIDDLE);
 		m_pBitmap = pWindow->GetBitmap()->DupBitmapTo32();
	}
	void *CCXBitmapDC::GetBuffer()
	{
		UINT8 *data = m_pBitmap->GetDataPtr();
		return data;
	}
	CGSize CCXBitmapDC::GetScaleSize()
	{
		return m_tScaleSize;
	}
	CGSize CCXBitmapDC::GetTextSize()
	{
		return m_tTextSize;
	}
}