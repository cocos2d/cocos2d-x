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
#include "CCDirector.h"
#include "CCGLProgram.h"
#include "CCShaderCache.h"

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
    : m_eAlignment(CCTextAlignmentCenter)
    , m_fFontSize(0.0)
{
}

CCLabelTTF::~CCLabelTTF()
{
      
}

CCLabelTTF * CCLabelTTF::node()
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

CCLabelTTF * CCLabelTTF::labelWithString(const char *label, const CCSize& dimensions, CCTextAlignment alignment, const char *fontName, float fontSize)
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

bool CCLabelTTF::init()
{
    return this->initWithString("", "Helvetica", 12);
}

bool CCLabelTTF::initWithString(const char *label, const CCSize& dimensions, CCTextAlignment alignment, const char *fontName, float fontSize)
{
    CCAssert(label != NULL, "");
    if (CCSprite::init())
    {
        // shader program
        setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(SHADER_PROGRAM));

        m_tDimensions = CCSizeMake( dimensions.width * CC_CONTENT_SCALE_FACTOR(), dimensions.height * CC_CONTENT_SCALE_FACTOR() );
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
    CCAssert(label != NULL, "");
    if (CCSprite::init())
    {
        // shader program
        setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(SHADER_PROGRAM));

        m_tDimensions = CCSizeZero;

        m_sFontName = fontName;

        m_fFontSize = fontSize * CC_CONTENT_SCALE_FACTOR();
        this->setString(label);
        return true;
    }
    return false;
}
const char * CCLabelTTF::getFontName()
{
    return this->m_sFontName.c_str();
}
void CCLabelTTF::setFontName(const char *fontName)
{
    if(strcmp(this->m_sFontName.c_str(), fontName) != 0)
    {
        this->m_sFontName = fontName;
        
        this->setString(this->m_sString.c_str());
    }
}
float CCLabelTTF::getFontSize()
{
    return this->m_fFontSize;
}
void CCLabelTTF::setFontSize(float fontSize)
{
    if(this->m_fFontSize != fontSize)
    {
        this->m_fFontSize = fontSize;
        
        this->setString(this->m_sString.c_str());
    }
}
void CCLabelTTF::setDimensions(CCSize dimensions)
{
    if(this->m_tDimensions.width != dimensions.width || this->m_tDimensions.height != dimensions.height)
    {
        this->m_tDimensions = dimensions;
        
        this->setString(this->m_sString.c_str());
    }
}
void CCLabelTTF::setHorizontalAlignment(CCTextAlignment pCCTextAlignment)
{
    if(this->m_eAlignment != pCCTextAlignment)
    {
        this->m_eAlignment = pCCTextAlignment;

        this->setString(this->m_sString.c_str());
    }
}
void CCLabelTTF::setString(const char *label)
{
    m_sString = label;
    
    CCTexture2D *texture;
    if( CCSize::CCSizeEqualToSize( m_tDimensions, CCSizeZero ) )
    {
        texture = new CCTexture2D();
        texture->initWithString(label, m_sFontName.c_str(), m_fFontSize);
    }
    else
    {
        texture = new CCTexture2D();
        texture->initWithString(label, m_tDimensions, m_eAlignment, m_sFontName.c_str(), m_fFontSize);
    }

// TODO
// #ifdef __CC_PLATFORM_IOS
//     // iPad ?
//     if( UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad ) {
//         if( CC_CONTENT_SCALE_FACTOR() == 2 )
//             [tex setResolutionType:kCCResolutioniPadRetinaDisplay];
//         else
//             [tex setResolutionType:kCCResolutioniPad];
//     }
//     // iPhone ?
//     else
//     {
//         if( CC_CONTENT_SCALE_FACTOR() == 2 )
//             [tex setResolutionType:kCCResolutioniPhoneRetinaDisplay];
//         else
//             [tex setResolutionType:kCCResolutioniPhone];
//     }
// #end
    this->setTexture(texture);
    texture->release();

    CCRect rect = CCRectZero;
    rect.size = m_pobTexture->getContentSize();
    this->setTextureRect(rect);
}

const char* CCLabelTTF::getString(void)
{
    return m_sString.c_str();
}

const char* CCLabelTTF::description()
{
    return CCString::stringWithFormat("<CCLabelTTF | FontName = %s, FontSize = %.1f>", m_sFontName.c_str(), m_fFontSize)->getCString();
}

NS_CC_END
