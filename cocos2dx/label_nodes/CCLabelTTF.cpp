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
#include "CCLabelTTF.h"

namespace cocos2d{
	//
	//CCLabelTTF
	//
	CCLabelTTF * CCLabelTTF::labelWithString(const char *label, CGSize dimensions, UITextAlignment alignment, const char *fontName, float fontSize)
	{
		CCLabelTTF *pRet = new CCLabelTTF();
		if(pRet && pRet->initWithString(label, dimensions, alignment, fontName, fontSize))
		{
			pRet->autorelease();
			return pRet;
		}
		CCX_SAFE_DELETE(pRet)
		return NULL;
	}
	CCLabelTTF * CCLabelTTF::labelWithString(const char *label, const char *fontName, float fontSize)
	{
		CCLabelTTF *pRet = new CCLabelTTF();
		if(pRet && pRet->initWithString(label, fontName, fontSize))
		{
			pRet->autorelease();
			return pRet;
		}
		CCX_SAFE_DELETE(pRet)
		return NULL;
	}

	bool CCLabelTTF::initWithString(const char *label, CGSize dimensions, UITextAlignment alignment, const char *fontName, float fontSize)
	{
		assert(label != NULL);
		if (CCSprite::init())
		{
			m_tDimensions = CGSizeMake( dimensions.width * CC_CONTENT_SCALE_FACTOR(), dimensions.height * CC_CONTENT_SCALE_FACTOR() );
			m_eAlignment = alignment;
			m_sFontName = fontName;
			m_fFontSize = fontSize * CC_CONTENT_SCALE_FACTOR();
			this->setString(label);
			return true;
		}
		return false;
	}
	bool CCLabelTTF::initWithString(const char *label, const char *fontName, float fontSize)
	{
		assert(label != NULL);
		if (CCSprite::init())
		{
			m_tDimensions = CGSizeZero;
			m_sFontName = fontName;
			m_fFontSize = fontSize * CC_CONTENT_SCALE_FACTOR();
			this->setString(label);
			return true;
		}
		return false;
	}
	void CCLabelTTF::setString(const char *label)
	{
        if (strlen(label)==0)
        {
            return;
        }

		m_sString = string(label);
        
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

        CGRect rect = CGRectZero;
		rect.size = m_pobTexture->getContentSize();
		this->setTextureRect(rect);
	}

	const char* CCLabelTTF::getString(void)
	{
		return m_sString.c_str();
	}

	char * CCLabelTTF::description()
	{
		char *ret = new char[100] ;
		sprintf(ret, "<CCLabelTTF | FontName = %s, FontSize = %.1f>", m_sFontName.c_str(), m_fFontSize);
		return ret;
	}
}// namespace cocos2d
