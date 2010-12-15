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
#include "Gbk_Unicode.h"

using namespace Osp::Graphics;

namespace cocos2d {

	CCXBitmapDC::CCXBitmapDC(int width, int height)
	{
		m_pCanvas = new Canvas();
		m_pCanvas->Construct(Rectangle(0, 0, width, height));
	}
 	CCXBitmapDC::CCXBitmapDC(const char *text, CGSize dimensions, UITextAlignment alignment, const char *fontName, float fontSize)
 	{
		// create font
//		Font font;
//		font.Create(0, (Int32)fontSize);



		// text
		wchar_t wideText[256] = {0};
		MyGBKToUnicode(wideText, (char*)text);

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
			case UITextAlignmentLeft:
				m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_LEFT);
				m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
				break;
			case UITextAlignmentCenter:
				m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
				m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
				break;
			case UITextAlignmentRight:
				m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_RIGHT);
				m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
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
			pTextElement1->SetTextColor(Color::COLOR_BLUE);
			pTextElement1->SetFont(font);
			// Add the TextElement to the EnrichedText
			m_pEnrichedText->Add(*pTextElement1);


			m_pCanvas->DrawText(Point(0, 0), *m_pEnrichedText);
			m_pEnrichedText->RemoveAllTextElements(true);
			delete m_pEnrichedText;
 	}

	CCXBitmapDC::~CCXBitmapDC(void)
	{
		delete m_pCanvas;
	}

	Osp::Graphics::Canvas* CCXBitmapDC::getCanvas(void)
	{
		return m_pCanvas;
	}

	CGSize CCXBitmapDC::getSize(void)
	{
		return m_tSize;
	}

}
