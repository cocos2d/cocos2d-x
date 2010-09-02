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
#include "CCLabel.h"

namespace cocos2d{
	//
	//CCLabel
	//
	CCLabel * CCLabel::labelWithString(const char *label, CGSize dimensions, UITextAlignment alignment, const char *fontName, float fontSize)
	{
		CCLabel *pRet = new CCLabel();
		if(pRet && pRet->initWithString(label, dimensions, alignment, fontName, fontSize))
		{
			pRet->autorelease();
			return pRet;
		}
		CCX_SAFE_DELETE(pRet)
		return NULL;
	}
	CCLabel * CCLabel::labelWithString(const char *label, const char *fontName, float fontSize)
	{
		CCLabel *pRet = new CCLabel();
		if(pRet && pRet->initWithString(label, fontName, fontSize))
		{
			pRet->autorelease();
			return pRet;
		}
		CCX_SAFE_DELETE(pRet)
		return NULL;
	}

	CCLabel * CCLabel::initWithString(const char *label, CGSize dimensions, UITextAlignment alignment, const char *fontName, float fontSize)
	{
		if (CCSprite::init())
		{
			m_tDimensions = dimensions;
			m_eAlignment = alignment;
			m_sFontName = fontName;
			m_fFontSize = fontSize;
			this->setString(label);
			return this;
		}
		return NULL;
	}
	CCLabel * CCLabel::initWithString(const char *label, const char *fontName, float fontSize)
	{
		if (CCSprite::init())
		{
			m_tDimensions = CGSizeZero;
			m_sFontName = fontName;
			m_fFontSize = fontSize;
			this->setString(label);
			return this;
		}
		return NULL;
	}
	void CCLabel::setString(const char *label)
	{
		CCTexture2D *texture;
		if( CGSize::CGSizeEqualToSize( m_tDimensions, CGSizeZero ) )
		{
			texture = new CCTexture2D();
			texture->initWithString(label, m_sFontName.c_str(), m_fFontSize);
		}
		else
		{
			texture = new CCTexture2D();
			texture->initWithString(label, m_tDimensions, m_eAlignment, m_sFontName.c_str(), m_fFontSize);
		}
		this->setTexture(texture);
		texture->release();

		CGSize size = m_pobTexture->getContentSize();
		this->setTextureRect(CGRectMake(0, 0, size.width, size.height));
	}

	char * CCLabel::description()
	{
		char *ret = new char[100] ;
		sprintf(ret, "<CCLabel | FontName = %s, FontSize = %.1f>", m_sFontName, m_fFontSize);
		return ret;
	}
}// namespace cocos2d
