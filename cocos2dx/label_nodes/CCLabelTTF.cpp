/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada

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
    CCLabelTTF::CCLabelTTF()
        : m_eAlignment(CCTextAlignmentCenter)
        , m_pFontName(NULL)
        , m_fFontSize(0.0)
        , m_pString(NULL)
    {
    }

    CCLabelTTF::~CCLabelTTF()
    {
		CC_SAFE_DELETE(m_pFontName);
		CC_SAFE_DELETE(m_pString);        
    }

	CCLabelTTF * CCLabelTTF::labelWithString(const char *label, CCSize dimensions, CCTextAlignment alignment, const char *fontName, float fontSize)
	{
		CCLabelTTF *pRet = new CCLabelTTF();
		if(pRet && pRet->initWithString(label, dimensions, alignment, fontName, fontSize))
		{
			pRet->autorelease();
			return pRet;
		}
		CC_SAFE_DELETE(pRet);
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
		CC_SAFE_DELETE(pRet);
		return NULL;
	}

	bool CCLabelTTF::initWithString(const char *label, CCSize dimensions, CCTextAlignment alignment, const char *fontName, float fontSize)
	{
		assert(label != NULL);
		if (CCSprite::init())
		{
			m_tDimensions = CCSizeMake( dimensions.width * CC_CONTENT_SCALE_FACTOR(), dimensions.height * CC_CONTENT_SCALE_FACTOR() );
			m_eAlignment = alignment;

            if (m_pFontName)
            {
                delete m_pFontName;
                m_pFontName = NULL;
            }
            m_pFontName = new std::string(fontName);

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
			m_tDimensions = CCSizeZero;

            if (m_pFontName)
            {
                delete m_pFontName;
                m_pFontName = NULL;
            }
            m_pFontName = new std::string(fontName);

			m_fFontSize = fontSize * CC_CONTENT_SCALE_FACTOR();
			this->setString(label);
			return true;
		}
		return false;
	}
	void CCLabelTTF::setString(const char *label)
	{
        if (m_pString)
        {
            delete m_pString;
            m_pString = NULL;
        }
        m_pString = new std::string(label);
        
		CCTexture2D *texture;
		if( CCSize::CCSizeEqualToSize( m_tDimensions, CCSizeZero ) )
		{
			texture = new CCTexture2D();
			texture->initWithString(label, m_pFontName->c_str(), m_fFontSize);
		}
		else
		{
			texture = new CCTexture2D();
			texture->initWithString(label, m_tDimensions, m_eAlignment, m_pFontName->c_str(), m_fFontSize);
		}
		this->setTexture(texture);
		texture->release();

        CCRect rect = CCRectZero;
		rect.size = m_pobTexture->getContentSize();
		this->setTextureRect(rect);
	}

	const char* CCLabelTTF::getString(void)
	{
		return m_pString->c_str();
	}

	char * CCLabelTTF::description()
	{
		char *ret = new char[100] ;
		sprintf(ret, "<CCLabelTTF | FontName = %s, FontSize = %.1f>", m_pFontName->c_str(), m_fFontSize);
		return ret;
	}
}// namespace cocos2d
