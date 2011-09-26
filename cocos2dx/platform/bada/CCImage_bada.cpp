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
		m_pCanvas = NULL;
		m_pEnrichedText = NULL;
	}

	~BitmapDC()
	{
		CC_SAFE_DELETE(m_pCanvas);
	}

	bool drawText(const char * pszText, CCSize& dimensions, CCImage::ETextAlign alignment, const char * fontName = NULL, int fontSize = 0)
	{
		bool nRet = false;
		do 
		{
			// text
			mchar wideText[256] = {0};
			MyGBKToUnicode((unsigned short*)wideText, 256, pszText);

			// Set a font to the TextElement
			Font font;
			font.Construct(FONT_STYLE_PLAIN, fontSize);

			// calculate text size
			if (CCSize::CCSizeEqualToSize(dimensions, CCSizeZero))
			{
				Dimension dim;
				font.GetTextExtent(wideText, wcslen(wideText), dim);
				dimensions.width = dim.width;
				dimensions.height = dim.height;
			}

			CC_SAFE_DELETE(m_pCanvas);

			CC_BREAK_IF(dimensions.width <= 0 || dimensions.height <= 0);

			m_pCanvas = new Canvas();
			m_pCanvas->Construct(Rectangle(0, 0, dimensions.width, dimensions.height));

			// Create an EnrichedText
			m_pEnrichedText = new EnrichedText();
			m_pEnrichedText->Construct(Dimension(dimensions.width, dimensions.height));

			switch (alignment)
			{
			case CCImage::kAlignCenter:
				m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
				m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
				break;
			case CCImage::kAlignTop:
				m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
				m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_TOP);
				break;
			case CCImage::kAlignTopRight:
				m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_RIGHT);
				m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_TOP);
				break;
			case CCImage::kAlignRight:
				m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_RIGHT);
				m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
				break;
			case CCImage::kAlignBottomRight:
				m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_RIGHT);
				m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_BOTTOM);
				break;
			case CCImage::kAlignBottom:
				m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
				m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_BOTTOM);
				break;
			case CCImage::kAlignBottomLeft:
				m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_LEFT);
				m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_BOTTOM);
				break;
			case CCImage::kAlignLeft:
				m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_LEFT);
				m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
				break;
			case CCImage::kAlignTopLeft:
				m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_LEFT);
				m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_TOP);
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
			TextElement* pTextElement = new TextElement();
			pTextElement->Construct(wideText);
			// After Adding, set attributes of the TextElement
			pTextElement->SetTextColor(Color::COLOR_WHITE);
			pTextElement->SetFont(font);
			// Add the TextElement to the EnrichedText
			m_pEnrichedText->Add(*pTextElement);

			m_pCanvas->DrawText(Point(0, 0), *m_pEnrichedText);

			m_pEnrichedText->RemoveAllTextElements(true);
			CC_SAFE_DELETE(m_pEnrichedText);

			nRet = true;
		} while (0);
		return nRet;
	}
private:
	friend class CCImage;
	Canvas* m_pCanvas;
	EnrichedText* m_pEnrichedText;
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

		CCSize size(nWidth, nHeight);

		bRet = dc.drawText(pText, size, eAlignMask, pFontName, nSize);

		CC_BREAK_IF(!bRet);

		BufferInfo bufferInfo;
		r = dc.m_pCanvas->Lock(bufferInfo);
		CC_BREAK_IF(IsFailed(r));

		int nLen = bufferInfo.pitch * bufferInfo.height;

		CC_SAFE_DELETE(m_pData);
		m_pData = new unsigned char [nLen];
		CC_BREAK_IF(!m_pData);
		memcpy(m_pData, bufferInfo.pPixels, nLen);


		m_nWidth		= bufferInfo.width;
		m_nHeight		= bufferInfo.height;

		m_bHasAlpha	= true;
		m_bPreMulti = false;
		m_nBitsPerComponent = bufferInfo.bitsPerPixel / 4;
		dc.m_pCanvas->Unlock();

		bRet = true;
	} while (0);

    return bRet;
}

NS_CC_END;
