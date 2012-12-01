/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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
#include "CCDirector.h"
#include "shaders/CCGLProgram.h"
#include "shaders/CCShaderCache.h"
#include "CCApplication.h"

NS_CC_BEGIN

#if CC_USE_LA88_LABELS
#define SHADER_PROGRAM kCCShader_PositionTextureColor
#else
#define SHADER_PROGRAM kCCShader_PositionTextureA8Color
#endif

//
//CCLabelTTF
//
CCLabelTTF::CCLabelTTF()
: m_hAlignment(kCCTextAlignmentCenter)
, m_vAlignment(kCCVerticalTextAlignmentTop)
, m_pFontName(NULL)
, m_fFontSize(0.0)
, m_string("")
{
}

CCLabelTTF::~CCLabelTTF()
{
    CC_SAFE_DELETE(m_pFontName);
}

CCLabelTTF * CCLabelTTF::node()
{
    return CCLabelTTF::create();
}

CCLabelTTF * CCLabelTTF::create()
{
    CCLabelTTF * pRet = new CCLabelTTF();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

CCLabelTTF * CCLabelTTF::labelWithString(const char *string, const char *fontName, float fontSize)
{
    return CCLabelTTF::create(string, fontName, fontSize);
}

CCLabelTTF * CCLabelTTF::create(const char *string, const char *fontName, float fontSize)
{
    return CCLabelTTF::create(string, fontName, fontSize,
                              CCSizeZero, kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
}

CCLabelTTF * CCLabelTTF::labelWithString(const char *string, const CCSize& dimensions, CCTextAlignment hAlignment, const char *fontName, float fontSize)
{
    return CCLabelTTF::create(string, fontName, fontSize,
                              dimensions, hAlignment, kCCVerticalTextAlignmentTop);
}

CCLabelTTF * CCLabelTTF::create(const char *string, const char *fontName, float fontSize,
                                const CCSize& dimensions, CCTextAlignment hAlignment)
{
    return CCLabelTTF::create(string, fontName, fontSize, dimensions, hAlignment, kCCVerticalTextAlignmentTop);
}

CCLabelTTF* CCLabelTTF::labelWithString(const char *string, const cocos2d::CCSize &dimensions, 
                                        CCTextAlignment hAlignment, CCVerticalTextAlignment vAlignment, 
                                        const char *fontName, float fontSize)
{
    return CCLabelTTF::create(string, fontName, fontSize, dimensions, hAlignment, vAlignment);
}

CCLabelTTF* CCLabelTTF::create(const char *string, const char *fontName, float fontSize,
                               const CCSize &dimensions, CCTextAlignment hAlignment, 
                               CCVerticalTextAlignment vAlignment)
{
    CCLabelTTF *pRet = new CCLabelTTF();
    if(pRet && pRet->initWithString(string, fontName, fontSize, dimensions, hAlignment, vAlignment))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCLabelTTF::init()
{
    return this->initWithString("", "Helvetica", 12);
}

bool CCLabelTTF::initWithString(const char *label, const char *fontName, float fontSize, 
                                const CCSize& dimensions, CCTextAlignment alignment)
{
    return this->initWithString(label, fontName, fontSize, dimensions, alignment, kCCVerticalTextAlignmentTop);
}

bool CCLabelTTF::initWithString(const char *label, const char *fontName, float fontSize)
{
    return this->initWithString(label, fontName, fontSize, 
                                CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
}

bool CCLabelTTF::initWithString(const char *string, const char *fontName, float fontSize,
                                const cocos2d::CCSize &dimensions, CCTextAlignment hAlignment,
                                CCVerticalTextAlignment vAlignment)
{
    if (CCSprite::init())
    {
        // shader program
        this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(SHADER_PROGRAM));
        
        m_tDimensions = CCSizeMake(dimensions.width, dimensions.height);
        m_hAlignment = hAlignment;
        m_vAlignment = vAlignment;
        m_pFontName = new std::string(fontName);
        m_fFontSize = fontSize;
        
        this->setString(string);
        
        return true;
    }
    
    return false;
}

void CCLabelTTF::setString(const char *string)
{
    CCAssert(string != NULL, "Invalid string");
    
    if (m_string.compare(string))
    {
        m_string = string;
        
        this->updateTexture();
    }
}

const char* CCLabelTTF::getString(void)
{
    return m_string.c_str();
}

const char* CCLabelTTF::description()
{
    return CCString::createWithFormat("<CCLabelTTF | FontName = %s, FontSize = %.1f>", m_pFontName->c_str(), m_fFontSize)->getCString();
}

CCTextAlignment CCLabelTTF::getHorizontalAlignment()
{
    return m_hAlignment;
}

void CCLabelTTF::setHorizontalAlignment(CCTextAlignment alignment)
{
    if (alignment != m_hAlignment)
    {
        m_hAlignment = alignment;
        
        // Force update
        if (m_string.size() > 0)
        {
            this->updateTexture();
        }
    }
}

CCVerticalTextAlignment CCLabelTTF::getVerticalAlignment()
{
    return m_vAlignment;
}

void CCLabelTTF::setVerticalAlignment(CCVerticalTextAlignment verticalAlignment)
{
    if (verticalAlignment != m_vAlignment)
    {
        m_vAlignment = verticalAlignment;
        
        // Force update
        if (m_string.size() > 0)
        {
            this->updateTexture();
        }
    }
}

CCSize CCLabelTTF::getDimensions()
{
    return m_tDimensions;
}

void CCLabelTTF::setDimensions(const CCSize &dim)
{
    if (dim.width != m_tDimensions.width || dim.height != m_tDimensions.height)
    {
        m_tDimensions = dim;
        
        // Force update
        if (m_string.size() > 0)
        {
            this->updateTexture();
        }
    }
}

float CCLabelTTF::getFontSize()
{
    return m_fFontSize;
}

void CCLabelTTF::setFontSize(float fontSize)
{
    if (m_fFontSize != fontSize)
    {
        m_fFontSize = fontSize;
        
        // Force update
        if (m_string.size() > 0)
        {
            this->updateTexture();
        }
    }
}

const char* CCLabelTTF::getFontName()
{
    return m_pFontName->c_str();
}

void CCLabelTTF::setFontName(const char *fontName)
{
    if (m_pFontName->compare(fontName))
    {
        delete m_pFontName;
        m_pFontName = new std::string(fontName);
        
        // Force update
        if (m_string.size() > 0)
        {
            this->updateTexture();
        }
    }
}

// Helper
bool CCLabelTTF::updateTexture()
{
    CCTexture2D *tex;
    
    // let system compute label's width or height when its value is 0
    // refer to cocos2d-x issue #1430
    tex = new CCTexture2D();
    tex->initWithString( m_string.c_str(),
                        m_pFontName->c_str(),
                        m_fFontSize * CC_CONTENT_SCALE_FACTOR(),
                        CC_SIZE_POINTS_TO_PIXELS(m_tDimensions), 
                        m_hAlignment,
                        m_vAlignment);
    
    if (! tex)
    {
        return false;
    }
	
    this->setTexture(tex);
    tex->release();
	
	CCRect rect = CCRectZero;
    rect.size = m_pobTexture->getContentSize();
    this->setTextureRect(rect);
    
    return true;
}

NS_CC_END
