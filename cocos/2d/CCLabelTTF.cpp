/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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
#include "CCApplication.h"

NS_CC_BEGIN

#if CC_USE_LA88_LABELS
#define SHADER_PROGRAM GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR
#else
#define SHADER_PROGRAM GLProgram::SHADER_NAME_POSITION_TEXTUREA8Color
#endif

//
//CCLabelTTF
//
LabelTTF::LabelTTF()
: _alignment(TextHAlignment::CENTER)
, _vAlignment(TextVAlignment::TOP)
, _fontName("")
, _fontSize(0.0)
, _string("")
, _shadowEnabled(false)
, _strokeEnabled(false)
, _textFillColor(Color3B::WHITE)
{
}

LabelTTF::~LabelTTF()
{
}

LabelTTF * LabelTTF::create()
{
    LabelTTF * ret = new LabelTTF();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

LabelTTF * LabelTTF::create(const std::string& string, const std::string& fontName, float fontSize)
{
    return LabelTTF::create(string, fontName, fontSize,
                              Size::ZERO, TextHAlignment::CENTER, TextVAlignment::TOP);
}

LabelTTF * LabelTTF::create(const std::string& string, const std::string& fontName, float fontSize,
                                const Size& dimensions, TextHAlignment hAlignment)
{
    return LabelTTF::create(string, fontName, fontSize, dimensions, hAlignment, TextVAlignment::TOP);
}

LabelTTF* LabelTTF::create(const std::string& string, const std::string& fontName, float fontSize,
                               const Size &dimensions, TextHAlignment hAlignment, 
                               TextVAlignment vAlignment)
{
    LabelTTF *ret = new LabelTTF();
    if(ret && ret->initWithString(string, fontName, fontSize, dimensions, hAlignment, vAlignment))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

LabelTTF * LabelTTF::createWithFontDefinition(const std::string& string, FontDefinition &textDefinition)
{
    LabelTTF *ret = new LabelTTF();
    if(ret && ret->initWithStringAndTextDefinition(string, textDefinition))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool LabelTTF::init()
{
    return this->initWithString("", "Helvetica", 12);
}

bool LabelTTF::initWithString(const std::string& label, const std::string& fontName, float fontSize,
                                const Size& dimensions, TextHAlignment alignment)
{
    return this->initWithString(label, fontName, fontSize, dimensions, alignment, TextVAlignment::TOP);
}

bool LabelTTF::initWithString(const std::string& label, const std::string& fontName, float fontSize)
{
    return this->initWithString(label, fontName, fontSize, 
                                Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
}

bool LabelTTF::initWithString(const std::string& string, const std::string& fontName, float fontSize,
                                const cocos2d::Size &dimensions, TextHAlignment hAlignment,
                                TextVAlignment vAlignment)
{
    if (Sprite::init())
    {
        // shader program
//        this->setShaderProgram(ShaderCache::getInstance()->getProgram(SHADER_PROGRAM));

        _dimensions = Size(dimensions.width, dimensions.height);
        _alignment = hAlignment;
        _vAlignment = vAlignment;
        _fontName = fontName;
        _fontSize = fontSize;
        
        this->setString(string);
        
        return true;
    }
    
    return false;
}

bool LabelTTF::initWithStringAndTextDefinition(const std::string& string, FontDefinition &textDefinition)
{
    if (Sprite::init())
    {
        // shader program
        this->setShaderProgram(ShaderCache::getInstance()->getProgram(SHADER_PROGRAM));
        
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


void LabelTTF::setString(const std::string &string)
{
    if (_string.compare(string))
    {
        _string = string;
        
        this->updateTexture();
    }
}

const std::string& LabelTTF::getString() const
{
    return _string;
}

std::string LabelTTF::getDescription() const
{
    return StringUtils::format("<LabelTTF | FontName = %s, FontSize = %.1f, Label = '%s'>", _fontName.c_str(), _fontSize, _string.c_str());
}

TextHAlignment LabelTTF::getHorizontalAlignment() const
{
    return _alignment;
}

void LabelTTF::setHorizontalAlignment(TextHAlignment alignment)
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

TextVAlignment LabelTTF::getVerticalAlignment() const
{
    return _vAlignment;
}

void LabelTTF::setVerticalAlignment(TextVAlignment verticalAlignment)
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

const Size& LabelTTF::getDimensions() const
{
    return _dimensions;
}

void LabelTTF::setDimensions(const Size &dim)
{
    // XXX: float comparison... very unreliable
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

float LabelTTF::getFontSize() const
{
    return _fontSize;
}

void LabelTTF::setFontSize(float fontSize)
{
    // XXX: float comparison... very unreliable
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

const std::string& LabelTTF::getFontName() const
{
    return _fontName;
}

void LabelTTF::setFontName(const std::string& fontName)
{
    if (_fontName.compare(fontName))
    {
        _fontName = fontName;
        
        // Force update
        if (_string.size() > 0)
        {
            this->updateTexture();
        }
    }
}

// Helper
bool LabelTTF::updateTexture()
{
    Texture2D *tex;
    tex = new Texture2D();
    
    if (!tex)
        return false;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
        FontDefinition texDef = _prepareTextDefinition(true);
        tex->initWithString( _string.c_str(), texDef );
    
#else
    
        tex->initWithString( _string.c_str(),
                            _fontName.c_str(),
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
    Rect rect =Rect::ZERO;
    rect.size   = _texture->getContentSize();
    this->setTextureRect(rect);
    
    //ok
    return true;
}

void LabelTTF::enableShadow(const Size &shadowOffset, float shadowOpacity, float shadowBlur, bool updateTexture)
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
            _shadowOffset.width = shadowOffset.width;
            _shadowOffset.height = shadowOffset.height;
            
            valueChanged = true;
        }
        
        if (_shadowOpacity != shadowOpacity )
        {
            _shadowOpacity = shadowOpacity;
            valueChanged = true;
        }

        if (_shadowBlur != shadowBlur)
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

void LabelTTF::disableShadow(bool updateTexture)
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

void LabelTTF::enableStroke(const Color3B &strokeColor, float strokeSize, bool updateTexture)
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

void LabelTTF::disableStroke(bool updateTexture)
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

void LabelTTF::setFontFillColor(const Color3B &tintColor, bool updateTexture)
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

void LabelTTF::setTextDefinition(const FontDefinition& theDefinition)
{
    _updateWithTextDefinition(theDefinition, true);
}

FontDefinition LabelTTF::getTextDefinition()
{
    return _prepareTextDefinition(false);
}

void LabelTTF::_updateWithTextDefinition(const FontDefinition& textDefinition, bool mustUpdateTexture)
{
    _dimensions = Size(textDefinition._dimensions.width, textDefinition._dimensions.height);
    _alignment = textDefinition._alignment;
    _vAlignment = textDefinition._vertAlignment;
    
    _fontName = textDefinition._fontName;
    _fontSize = textDefinition._fontSize;
    
    
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

FontDefinition LabelTTF::_prepareTextDefinition(bool adjustForResolution)
{
    FontDefinition texDef;
    
    if (adjustForResolution)
        texDef._fontSize = _fontSize * CC_CONTENT_SCALE_FACTOR();
    else
        texDef._fontSize = _fontSize;
    
    texDef._fontName = _fontName;
    texDef._alignment = _alignment;
    texDef._vertAlignment = _vAlignment;
    
    
    if (adjustForResolution)
        texDef._dimensions = CC_SIZE_POINTS_TO_PIXELS(_dimensions);
    else
        texDef._dimensions = _dimensions;
    
    
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
        texDef._shadow._shadowEnabled = true;
        texDef._shadow._shadowBlur = _shadowBlur;
        texDef._shadow._shadowOpacity = _shadowOpacity;
        
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
