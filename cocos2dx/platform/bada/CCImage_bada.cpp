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
#include <FGraphics.h>
#include "Gbk_Unicode.h"
using namespace Osp::Graphics;

NS_CC_BEGIN;

/**
@brief	A memory DC which uses to draw text on bitmap.
*/
class BitmapDC
{
public:
	BitmapDC()
	{

	}

	~BitmapDC()
	{
	
	}

	int drawText(const char * pszText, CGSize& dimensions, CCImage::ETextAlign alignment, const char * fontName = NULL, int fontSize = 0)
	{
		int nRet = 0;
		do 
		{
			// text
			unsigned short wideText[256] = {0};
			MyGBKToUnicode(wideText, 256, pszText);

			// Set a font to the TextElement
			Font font;
			font.Construct(FONT_STYLE_PLAIN, fontSize);

			// calculate text size
			if (CGSize::CGSizeEqualToSize(dimensions, CGSizeZero))
			{
				Dimension dim;
				font.GetTextExtent(wideText, wcslen(wideText), dim);
				m_tSize.width = dim.width;
				m_tSize.height = dim.height;
			}
			else
			{
				m_tSize = dimensions;
			}

			int width = (int)m_tSize.width;
			int height = (int)m_tSize.height;

			m_pCanvas = new Canvas();
			m_pCanvas->Construct(Rectangle(0, 0, width, height));

			// Create an EnrichedText
			m_pEnrichedText = new EnrichedText();
			m_pEnrichedText->Construct(Dimension(m_tSize.width, m_tSize.height));

			switch (alignment)
			{
			case kAlignLeft:
				m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_LEFT);
				m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
				break;
			case kAlignCenter:
				m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
				m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
				break;
			case kAlignRight:
				m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_RIGHT);
				m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
				break;
			case kAlignTop:
				m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
				m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_TOP);
				break;
			case kAlignTopRight:
				m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_RIGHT);
				m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_TOP);
				break;
			case kAlignBottomRight:
				m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_RIGHT);
				m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_BOTTOM);
				break;
			case kAlignBottom:
				m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
				m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_BOTTOM);
				break;
			default:
				m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
				m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
				break;
			}
			// Set attributes of the EnrichedText
			m_pEnrichedText->SetTextWrapStyle(TEXT_WRAP_CHARACTER_WRAP);
			m_pEnrichedText->SetTextAbbreviationEnabled(true);


			// Create a TextElement
			TextElement* pTextElement1 = new TextElement();
			pTextElement1->Construct(wideText);
			// After Adding, set attributes of the TextElement
			pTextElement1->SetTextColor(Color::COLOR_WHITE);
			pTextElement1->SetFont(font);
			// Add the TextElement to the EnrichedText
			m_pEnrichedText->Add(*pTextElement1);


			m_pCanvas->DrawText(Point(0, 0), *m_pEnrichedText);
			m_pEnrichedText->RemoveAllTextElements(true);
			delete m_pEnrichedText;
			nRet = 1;
		} while (0);
		return nRet;
	}
private:
	friend class CCImage;
	Canvas* m_pCanvas;
	EnrichedText* m_pEnrichedText;
	CGSize m_tSize;
	std::string m_curFontPath;
};

static BitmapDC& sharedBitmapDC()
{
	static BitmapDC s_BmpDC;
	return s_BmpDC;
}

bool CCImage::initWithString(
                               const char *    pText,
                               int             nWidth/* = 0*/,
                               int             nHeight/* = 0*/,
                               ETextAlign      eAlignMask/* = kAlignCenter*/,
                               const char *    pFontName/* = nil*/,
                               int             nSize/* = 0*/)
{
    bool bRet = false;
    result r = E_FAILURE;
	do
	{
		CC_BREAK_IF(! pText);       

		BitmapDC& dc = sharedBitmapDC();

		if (! dc.setFont(pFontName, nSize))
		{
			CCLog("Can't found font(%s), use system default", pFontName);
		}

		// draw text
		SIZE size = {nWidth, nHeight};
		CC_BREAK_IF(! dc.drawText(pText, size, eAlignMask));

		Canvas * pCanvas = new Canvas();
		CC_BREAK_IF(! pCanvas);

		r = pCanvas->Construct(Rectangle(0, 0, nWidth, nHeight));
		CC_BREAK_IF(IsFailed(r));

		BufferInfo bufferInfo;
		r = pCanvas->Lock(bufferInfo);
		CC_BREAK_IF(IsFailed(r));

		int nLen = bufferInfo.pitch * nHeight;
		m_pData = new unsigned char [nLen];
		CC_BREAK_IF(!m_pData);
		memcpy(m_pData, bufferInfo.pPixels, nLen);

		m_nHeight		= nHeight;
		m_nWidth		= nWidth;
		m_bHasAlpha	= true;
		m_bPreMulti = true;
		m_nBitsPerComponent = bufferInfo.bitsPerPixel / 4;
		pCanvas->Unlock();

		CC_SAFE_DELETE(pCanvas);
		bRet = true;
	} while (0);

    return bRet;
}

NS_CC_END;
