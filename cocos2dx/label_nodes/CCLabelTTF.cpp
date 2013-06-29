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
: _alignment(kCCTextAlignmentCenter)
, _vAlignment(kCCVerticalTextAlignmentTop)
, _fontName(NULL)
, _fontSize(0.0)
, _string("")
, _shadowEnabled(false)
, _strokeEnabled(false)
, _textFillColor(ccWHITE)
{
}

CCLabelTTF::~CCLabelTTF()
{
    CC_SAFE_DELETE(_fontName);
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
        
        _dimensions = CCSizeMake(dimensions.width, dimensions.height);
        _alignment  = hAlignment;
        _vAlignment  = vAlignment;
        _fontName   = new std::string(fontName);
        _fontSize   = fontSize;
        
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
    
    if (_string.compare(string))
    {
        _string = string;
        
        this->updateTexture();
    }
}

const char* CCLabelTTF::getString(void)
{
    return _string.c_str();
}

const char* CCLabelTTF::description()
{
    return CCString::createWithFormat("<CCLabelTTF | FontName = %s, FontSize = %.1f>", _fontName->c_str(), _fontSize)->getCString();
}

CCTextAlignment CCLabelTTF::getHorizontalAlignment()
{
    return _alignment;
}

void CCLabelTTF::setHorizontalAlignment(CCTextAlignment alignment)
{
    if (alignment != _alignment)
    {
        _alignment = alignment;
        
        // Force update
        if (_string.size() > 0)
        {
            this->updateTexture();
        }
    }
}

CCVerticalTextAlignment CCLabelTTF::getVerticalAlignment()
{
    return _vAlignment;
}

void CCLabelTTF::setVerticalAlignment(CCVerticalTextAlignment verticalAlignment)
{
    if (verticalAlignment != _vAlignment)
    {
        _vAlignment = verticalAlignment;
        
        // Force update
        if (_string.size() > 0)
        {
            this->updateTexture();
        }
    }
}

CCSize CCLabelTTF::getDimensions()
{
    return _dimensions;
}

void CCLabelTTF::setDimensions(const CCSize &dim)
{
    if (dim.width != _dimensions.width || dim.height != _dimensions.height)
    {
        _dimensions = dim;
        
        // Force update
        if (_string.size() > 0)
        {
            this->updateTexture();
        }
    }
}

float CCLabelTTF::getFontSize()
{
    return _fontSize;
}

void CCLabelTTF::setFontSize(float fontSize)
{
    if (_fontSize != fontSize)
    {
        _fontSize = fontSize;
        
        // Force update
        if (_string.size() > 0)
        {
            this->updateTexture();
        }
    }
}

const char* CCLabelTTF::getFontName()
{
    return _fontName->c_str();
}

void CCLabelTTF::setFontName(const char *fontName)
{
    if (_fontName->compare(fontName))
    {
        delete _fontName;
        _fontName = new std::string(fontName);
        
        // Force update
        if (_string.size() > 0)
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
        tex->initWithString( _string.c_str(), &texDef );
    
    #else
    
        tex->initWithString( _string.c_str(),
                            _fontName->c_str(),
                            _fontSize * CC_CONTENT_SCALE_FACTOR(),
                            CC_SIZE_POINTS_TO_PIXELS(_dimensions),
                            _alignment,
                            _vAlignment);
    
    #endif
    
    // set the texture
    this->setTexture(tex);
    // release it
    tex->release();
    
    // set the size in the sprite
    CCRect rect =CCRectZero;
    rect.size   = _texture->getContentSize();
    this->setTextureRect(rect);
    
    //ok
    return true;
}

void CCLabelTTF::enableShadow(const CCSize &shadowOffset, float shadowOpacity, float shadowBlur, bool updateTexture)
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
        bool valueChanged = false;
        
        if (false == _shadowEnabled)
        {
            _shadowEnabled = true;
            valueChanged    = true;
        }
        
        if ( (_shadowOffset.width != shadowOffset.width) || (_shadowOffset.height!=shadowOffset.height) )
        {
            _shadowOffset.width  = shadowOffset.width;
            _shadowOffset.height = shadowOffset.height;
            
            valueChanged = true;
        }
        
        if (_shadowOpacity != shadowOpacity )
        {
            _shadowOpacity = shadowOpacity;
            valueChanged = true;
        }

        if (_shadowBlur    != shadowBlur)
        {
            _shadowBlur = shadowBlur;
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
    
        if (_shadowEnabled)
        {
            _shadowEnabled = false;
    
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
        
        if(_strokeEnabled == false)
        {
            _strokeEnabled = true;
            valueChanged = true;
        }
        
        if ( (_strokeColor.r != strokeColor.r) || (_strokeColor.g != strokeColor.g) || (_strokeColor.b != strokeColor.b) )
        {
            _strokeColor = strokeColor;
            valueChanged = true;
        }
        
        if (_strokeSize!=strokeSize)
        {
            _strokeSize = strokeSize;
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
    
        if (_strokeEnabled)
        {
            _strokeEnabled = false;
            
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
        if (_textFillColor.r != tintColor.r || _textFillColor.g != tintColor.g || _textFillColor.b != tintColor.b)
        {
            _textFillColor = tintColor;
            
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
    _dimensions = CCSizeMake(textDefinition._dimensions.width, textDefinition._dimensions.height);
    _alignment  = textDefinition._alignment;
    _vAlignment  = textDefinition._vertAlignment;
    
    _fontName   = new std::string(textDefinition._fontName);
    _fontSize   = textDefinition._fontSize;
    
    
    // shadow
    if ( textDefinition._shadow._shadowEnabled )
    {
        enableShadow(textDefinition._shadow._shadowOffset, textDefinition._shadow._shadowOpacity, textDefinition._shadow._shadowBlur, false);
    }
    
    // stroke
    if ( textDefinition._stroke._strokeEnabled )
    {
        enableStroke(textDefinition._stroke._strokeColor, textDefinition._stroke._strokeSize, false);
    }
    
    // fill color
    setFontFillColor(textDefinition._fontFillColor, false);
    
    if (mustUpdateTexture)
        updateTexture();
}

ccFontDefinition CCLabelTTF::_prepareTextDefinition(bool adjustForResolution)
{
    ccFontDefinition texDef;
    
    if (adjustForResolution)
        texDef._fontSize       =  _fontSize * CC_CONTENT_SCALE_FACTOR();
    else
        texDef._fontSize       =  _fontSize;
    
    texDef._fontName       = *_fontName;
    texDef._alignment      =  _alignment;
    texDef._vertAlignment  =  _vAlignment;
    
    
    if (adjustForResolution)
        texDef._dimensions     =  CC_SIZE_POINTS_TO_PIXELS(_dimensions);
    else
        texDef._dimensions     =  _dimensions;
    
    
    // stroke
    if ( _strokeEnabled )
    {
        texDef._stroke._strokeEnabled = true;
        texDef._stroke._strokeColor   = _strokeColor;
        
        if (adjustForResolution)
            texDef._stroke._strokeSize = _strokeSize * CC_CONTENT_SCALE_FACTOR();
        else
            texDef._stroke._strokeSize = _strokeSize;
        
        
    }
    else
    {
        texDef._stroke._strokeEnabled = false;
    }
    
    
    // shadow
    if ( _shadowEnabled )
    {
        texDef._shadow._shadowEnabled         = true;
        texDef._shadow._shadowBlur            = _shadowBlur;
        texDef._shadow._shadowOpacity         = _shadowOpacity;
        
        if (adjustForResolution)
            texDef._shadow._shadowOffset = CC_SIZE_POINTS_TO_PIXELS(_shadowOffset);
        else
            texDef._shadow._shadowOffset = _shadowOffset;
    }
    else
    {
        texDef._shadow._shadowEnabled = false;
    }
    
    // text tint
    texDef._fontFillColor = _textFillColor;
    
    return texDef;
}

NS_CC_END
