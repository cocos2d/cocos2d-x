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
, m_shadowEnabled(false)
, m_strokeEnabled(false)
, m_textFillColor(ccWHITE)
{
}

CCLabelTTF::~CCLabelTTF()
{
    CC_SAFE_DELETE(m_pFontName);
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

CCLabelTTF * CCLabelTTF::create(const char *string, const char *fontName, float fontSize)
{
    return CCLabelTTF::create(string, fontName, fontSize,
                              CCSizeZero, kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
}

CCLabelTTF * CCLabelTTF::create(const char *string, const char *fontName, float fontSize,
                                const CCSize& dimensions, CCTextAlignment hAlignment)
{
    return CCLabelTTF::create(string, fontName, fontSize, dimensions, hAlignment, kCCVerticalTextAlignmentTop);
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

CCLabelTTF * CCLabelTTF::createWithFontDefinition(const char *string, ccFontDefinition &textDefinition)
{
    CCLabelTTF *pRet = new CCLabelTTF();
    if(pRet && pRet->initWithStringAndTextDefinition(string, textDefinition))
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
        m_hAlignment  = hAlignment;
        m_vAlignment  = vAlignment;
        m_pFontName   = new std::string(fontName);
        m_fFontSize   = fontSize;
        
        this->setString(string);
        
        return true;
    }
    
    return false;
}

bool CCLabelTTF::initWithStringAndTextDefinition(const char *string, ccFontDefinition &textDefinition)
{
    if (CCSprite::init())
    {
        // shader program
        this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(SHADER_PROGRAM));
        
        // prepare everythin needed to render the label
        _updateWithTextDefinition(textDefinition, false);
        
        // set the string
        this->setString(string);
        
        //
        return true;
    }
    else
    {
        return false;
    }
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
    tex = new CCTexture2D();
    
    if (!tex)
        return false;
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
        ccFontDefinition texDef = _prepareTextDefinition(true);
        tex->initWithString( m_string.c_str(), &texDef );
    
    #else
    
        tex->initWithString( m_string.c_str(),
                            m_pFontName->c_str(),
                            m_fFontSize * CC_CONTENT_SCALE_FACTOR(),
                            CC_SIZE_POINTS_TO_PIXELS(m_tDimensions),
                            m_hAlignment,
                            m_vAlignment);
    
    #endif
    
    // set the texture
    this->setTexture(tex);
    // release it
    tex->release();
    
    // set the size in the sprite
    CCRect rect =CCRectZero;
    rect.size   = m_pobTexture->getContentSize();
    this->setTextureRect(rect);
    
    //ok
    return true;
}

void CCLabelTTF::enableShadow(const CCSize &shadowOffset, float shadowOpacity, float shadowBlur, bool updateTexture)
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
        bool valueChanged = false;
        
        if (false == m_shadowEnabled)
        {
            m_shadowEnabled = true;
            valueChanged    = true;
        }
        
        if ( (m_shadowOffset.width != shadowOffset.width) || (m_shadowOffset.height!=shadowOffset.height) )
        {
            m_shadowOffset.width  = shadowOffset.width;
            m_shadowOffset.height = shadowOffset.height;
            
            valueChanged = true;
        }
        
        if (m_shadowOpacity != shadowOpacity )
        {
            m_shadowOpacity = shadowOpacity;
            valueChanged = true;
        }

        if (m_shadowBlur    != shadowBlur)
        {
            m_shadowBlur = shadowBlur;
            valueChanged = true;
        }
        
        
        if ( valueChanged && updateTexture )
        {
            this->updateTexture();
        }
    
    #else
        CCLOGERROR("Currently only supported on iOS and Android!");
    #endif
    
}

void CCLabelTTF::disableShadow(bool updateTexture)
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
        if (m_shadowEnabled)
        {
            m_shadowEnabled = false;
    
            if (updateTexture)
                this->updateTexture();
            
        }
    
    #else
        CCLOGERROR("Currently only supported on iOS and Android!");
    #endif
}

void CCLabelTTF::enableStroke(const ccColor3B &strokeColor, float strokeSize, bool updateTexture)
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
        bool valueChanged = false;
        
        if(m_strokeEnabled == false)
        {
            m_strokeEnabled = true;
            valueChanged = true;
        }
        
        if ( (m_strokeColor.r != strokeColor.r) || (m_strokeColor.g != strokeColor.g) || (m_strokeColor.b != strokeColor.b) )
        {
            m_strokeColor = strokeColor;
            valueChanged = true;
        }
        
        if (m_strokeSize!=strokeSize)
        {
            m_strokeSize = strokeSize;
            valueChanged = true;
        }
        
        if ( valueChanged && updateTexture )
        {
            this->updateTexture();
        }
    
    #else
        CCLOGERROR("Currently only supported on iOS and Android!");
    #endif
    
}

void CCLabelTTF::disableStroke(bool updateTexture)
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
        if (m_strokeEnabled)
        {
            m_strokeEnabled = false;
            
            if (updateTexture)
                this->updateTexture();
        }
    
    #else
        CCLOGERROR("Currently only supported on iOS and Android!");
    #endif
    
}

void CCLabelTTF::setFontFillColor(const ccColor3B &tintColor, bool updateTexture)
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        if (m_textFillColor.r != tintColor.r || m_textFillColor.g != tintColor.g || m_textFillColor.b != tintColor.b)
        {
            m_textFillColor = tintColor;
            
            if (updateTexture)
                this->updateTexture();
        }
    #else
        CCLOGERROR("Currently only supported on iOS and Android!");
    #endif
}

void CCLabelTTF::setTextDefinition(ccFontDefinition *theDefinition)
{
    if (theDefinition)
    {
        _updateWithTextDefinition(*theDefinition, true);
    }
}

ccFontDefinition *CCLabelTTF::getTextDefinition()
{
    ccFontDefinition *tempDefinition = new ccFontDefinition;
    *tempDefinition = _prepareTextDefinition(false);
    return tempDefinition;
}

void CCLabelTTF::_updateWithTextDefinition(ccFontDefinition & textDefinition, bool mustUpdateTexture)
{
    m_tDimensions = CCSizeMake(textDefinition.m_dimensions.width, textDefinition.m_dimensions.height);
    m_hAlignment  = textDefinition.m_alignment;
    m_vAlignment  = textDefinition.m_vertAlignment;
    
    m_pFontName   = new std::string(textDefinition.m_fontName);
    m_fFontSize   = textDefinition.m_fontSize;
    
    
    // shadow
    if ( textDefinition.m_shadow.m_shadowEnabled )
    {
        enableShadow(textDefinition.m_shadow.m_shadowOffset, textDefinition.m_shadow.m_shadowOpacity, textDefinition.m_shadow.m_shadowBlur, false);
    }
    
    // stroke
    if ( textDefinition.m_stroke.m_strokeEnabled )
    {
        enableStroke(textDefinition.m_stroke.m_strokeColor, textDefinition.m_stroke.m_strokeSize, false);
    }
    
    // fill color
    setFontFillColor(textDefinition.m_fontFillColor, false);
    
    if (mustUpdateTexture)
        updateTexture();
}

ccFontDefinition CCLabelTTF::_prepareTextDefinition(bool adjustForResolution)
{
    ccFontDefinition texDef;
    
    if (adjustForResolution)
        texDef.m_fontSize       =  m_fFontSize * CC_CONTENT_SCALE_FACTOR();
    else
        texDef.m_fontSize       =  m_fFontSize;
    
    texDef.m_fontName       = *m_pFontName;
    texDef.m_alignment      =  m_hAlignment;
    texDef.m_vertAlignment  =  m_vAlignment;
    
    
    if (adjustForResolution)
        texDef.m_dimensions     =  CC_SIZE_POINTS_TO_PIXELS(m_tDimensions);
    else
        texDef.m_dimensions     =  m_tDimensions;
    
    
    // stroke
    if ( m_strokeEnabled )
    {
        texDef.m_stroke.m_strokeEnabled = true;
        texDef.m_stroke.m_strokeColor   = m_strokeColor;
        
        if (adjustForResolution)
            texDef.m_stroke.m_strokeSize = m_strokeSize * CC_CONTENT_SCALE_FACTOR();
        else
            texDef.m_stroke.m_strokeSize = m_strokeSize;
        
        
    }
    else
    {
        texDef.m_stroke.m_strokeEnabled = false;
    }
    
    
    // shadow
    if ( m_shadowEnabled )
    {
        texDef.m_shadow.m_shadowEnabled         = true;
        texDef.m_shadow.m_shadowBlur            = m_shadowBlur;
        texDef.m_shadow.m_shadowOpacity         = m_shadowOpacity;
        
        if (adjustForResolution)
            texDef.m_shadow.m_shadowOffset = CC_SIZE_POINTS_TO_PIXELS(m_shadowOffset);
        else
            texDef.m_shadow.m_shadowOffset = m_shadowOffset;
    }
    else
    {
        texDef.m_shadow.m_shadowEnabled = false;
    }
    
    // text tint
    texDef.m_fontFillColor = m_textFillColor;
    
    return texDef;
}

NS_CC_END
