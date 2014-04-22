/****************************************************************************
 Copyright (c) 2013      Zynga Inc.
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

#include "CCLabel.h"
#include "CCFontAtlasCache.h"
#include "CCLabelTextFormatter.h"
#include "CCSprite.h"
#include "CCShaderCache.h"
#include "ccUTF8.h"
#include "CCSpriteFrame.h"
#include "CCDirector.h"
#include "renderer/CCRenderer.h"
#include "CCFont.h"
#include "CCEventListenerCustom.h"
#include "CCEventDispatcher.h"
#include "CCEventType.h"
#include "CCEventCustom.h"
#include "platform/CCFileUtils.h"
#include "deprecated/CCString.h"
#include "CCProfiling.h"

NS_CC_BEGIN

const int Label::DistanceFieldFontSize = 50;

Label* Label::create()
{
    auto ret = new Label();

    if (ret)
    {
        ret->autorelease();
    }

    return ret;
}

Label* Label::create(const std::string& text, const std::string& font, float fontSize, const Size& dimensions /* = Size::ZERO */, TextHAlignment hAlignment /* = TextHAlignment::LEFT */, TextVAlignment vAlignment /* = TextVAlignment::TOP */)
{
    if (FileUtils::getInstance()->isFileExist(font))
    {
        return createWithTTF(text,font,fontSize,dimensions,hAlignment,vAlignment);
    } 
    else
    {
        return createWithSystemFont(text,font,fontSize,dimensions,hAlignment,vAlignment);
    }
}

Label* Label::createWithSystemFont(const std::string& text, const std::string& font, float fontSize, const Size& dimensions /* = Size::ZERO */, TextHAlignment hAlignment /* = TextHAlignment::LEFT */, TextVAlignment vAlignment /* = TextVAlignment::TOP */)
{
    auto ret = new Label(nullptr,hAlignment,vAlignment);

    if (ret)
    {
        ret->setSystemFontName(font);
        ret->setSystemFontSize(fontSize);
        ret->setDimensions(dimensions.width, dimensions.height);
        ret->setString(text);

        ret->autorelease();

        return ret;
    }

    delete ret;
    return nullptr;
}

Label* Label::createWithTTF(const std::string& text, const std::string& fontFile, float fontSize, const Size& dimensions /* = Size::ZERO */, TextHAlignment hAlignment /* = TextHAlignment::LEFT */, TextVAlignment vAlignment /* = TextVAlignment::TOP */)
{
    auto ret = new Label(nullptr,hAlignment,vAlignment);

    if (ret && FileUtils::getInstance()->isFileExist(fontFile))
    {
        TTFConfig ttfConfig(fontFile.c_str(),fontSize,GlyphCollection::DYNAMIC);
        if (ret->setTTFConfig(ttfConfig))
        {
            ret->setDimensions(dimensions.width,dimensions.height);
            ret->setString(text);

            ret->autorelease();

            return ret;
        }
    }

    delete ret;
    return nullptr;
}

Label* Label::createWithTTF(const TTFConfig& ttfConfig, const std::string& text, TextHAlignment alignment /* = TextHAlignment::CENTER */, int maxLineWidth /* = 0 */)
{
    auto ret = new Label(nullptr,alignment);

    if (ret && FileUtils::getInstance()->isFileExist(ttfConfig.fontFilePath) && ret->setTTFConfig(ttfConfig))
    {
        ret->setMaxLineWidth(maxLineWidth);
        ret->setString(text);
        ret->autorelease();

        return ret;
    }

    delete ret;
    return nullptr;
}

Label* Label::createWithBMFont(const std::string& bmfontFilePath, const std::string& text,const TextHAlignment& alignment /* = TextHAlignment::LEFT */, int maxLineWidth /* = 0 */, const Point& imageOffset /* = Point::ZERO */)
{
    auto ret = new Label(nullptr,alignment);

    if (ret && ret->setBMFontFilePath(bmfontFilePath,imageOffset))
    {
        ret->setMaxLineWidth(maxLineWidth);
        ret->setString(text);
        ret->autorelease();

        return ret;
    }
    
    delete ret;
    return nullptr;
}

Label* Label::createWithCharMap(const std::string& plistFile)
{
    auto ret = new Label();

    if (ret && ret->setCharMap(plistFile))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

Label* Label::createWithCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap)
{
    auto ret = new Label();

    if (ret && ret->setCharMap(texture,itemWidth,itemHeight,startCharMap))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

Label* Label::createWithCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap)
{
    auto ret = new Label();

    if (ret && ret->setCharMap(charMapFile,itemWidth,itemHeight,startCharMap))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

bool Label::setCharMap(const std::string& plistFile)
{
    auto newAtlas = FontAtlasCache::getFontAtlasCharMap(plistFile);

    if (!newAtlas)
    {
        reset();
        return false;
    }

    _currentLabelType = LabelType::CHARMAP;
    setFontAtlas(newAtlas);

    return true;
}

bool Label::setCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap)
{
    auto newAtlas = FontAtlasCache::getFontAtlasCharMap(texture,itemWidth,itemHeight,startCharMap);

    if (!newAtlas)
    {
        reset();
        return false;
    }

    _currentLabelType = LabelType::CHARMAP;
    setFontAtlas(newAtlas);

    return true;
}

bool Label::setCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap)
{
    auto newAtlas = FontAtlasCache::getFontAtlasCharMap(charMapFile,itemWidth,itemHeight,startCharMap);

    if (!newAtlas)
    {
        reset();
        return false;
    }

    _currentLabelType = LabelType::CHARMAP;
    setFontAtlas(newAtlas);

    return true;
}

Label::Label(FontAtlas *atlas /* = nullptr */, TextHAlignment hAlignment /* = TextHAlignment::LEFT */, 
             TextVAlignment vAlignment /* = TextVAlignment::TOP */,bool useDistanceField /* = false */,bool useA8Shader /* = false */)
: _reusedLetter(nullptr)
, _commonLineHeight(0.0f)
, _lineBreakWithoutSpaces(false)
, _maxLineWidth(0)
, _labelWidth(0)
, _labelHeight(0)
, _labelDimensions(Size::ZERO)
, _hAlignment(hAlignment)
, _vAlignment(vAlignment)
, _currentUTF16String(nullptr)
, _originalUTF16String(nullptr)
, _horizontalKernings(nullptr)
, _fontAtlas(atlas)
, _isOpacityModifyRGB(false)
, _useDistanceField(useDistanceField)
, _useA8Shader(useA8Shader)
, _fontScale(1.0f)
, _uniformEffectColor(0)
, _currNumLines(-1)
, _textSprite(nullptr)
, _contentDirty(false)
, _shadowDirty(false)
, _compatibleMode(false)
{
    setAnchorPoint(Point::ANCHOR_MIDDLE);
    reset();

#if CC_ENABLE_CACHE_TEXTURE_DATA
    auto toBackgroundListener = EventListenerCustom::create(EVENT_COME_TO_BACKGROUND, [this](EventCustom* event){
        if (_fontAtlas && _currentLabelType == LabelType::TTF)
        {
            _batchNodes.clear();
            _batchNodes.push_back(this);
            Node::removeAllChildrenWithCleanup(true);
        }
    });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(toBackgroundListener, this);
#endif
    auto purgeTextureListener = EventListenerCustom::create(FontAtlas::EVENT_PURGE_TEXTURES, [this](EventCustom* event){
        if (_fontAtlas && _currentLabelType == LabelType::TTF && event->getUserData() == _fontAtlas)
        {
            alignText();
        }
    });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(purgeTextureListener, this);
}

Label::~Label()
{   
    delete [] _currentUTF16String;
    delete [] _originalUTF16String;
    delete [] _horizontalKernings;

    if (_fontAtlas)
    {
        FontAtlasCache::releaseFontAtlas(_fontAtlas);
    }

    CC_SAFE_RELEASE_NULL(_reusedLetter);
}

void Label::reset()
{
    TTFConfig temp;
    _fontConfig = temp;

    _fontDirty = false;
    _systemFont = "Helvetica";
    _systemFontSize = 12;

    _batchNodes.clear();
    _batchNodes.push_back(this);

    if (_fontAtlas)
    {
        FontAtlasCache::releaseFontAtlas(_fontAtlas);
        _fontAtlas = nullptr;
    }

    _currentLabelType = LabelType::STRING_TEXTURE;
    _currLabelEffect = LabelEffect::NORMAL;
    _shadowBlurRadius = 0;

    Node::removeAllChildrenWithCleanup(true);
    _textSprite = nullptr;
    _shadowNode = nullptr;

    CC_SAFE_RELEASE_NULL(_reusedLetter);

    _textColor = Color4B::WHITE;
    _textColorF = Color4F::WHITE;
    setColor(Color3B::WHITE);

    _shadowEnabled = false;
    _clipEnabled = false;
    _blendFuncDirty = false;
}

void Label::updateShaderProgram()
{
    switch (_currLabelEffect)
    {
    case cocos2d::LabelEffect::NORMAL:
        if (_useDistanceField)
            setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_NORMAL));
        else if (_useA8Shader)
            setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_LABEL_NORMAL));
        else
            setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));

        break;
    case cocos2d::LabelEffect::OUTLINE: 
        setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_LABEL_OUTLINE));
        _uniformEffectColor = glGetUniformLocation(_shaderProgram->getProgram(), "v_effectColor");
        break;
    case cocos2d::LabelEffect::GLOW:
        if (_useDistanceField)
        {
            setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_GLOW));
            _uniformEffectColor = glGetUniformLocation(_shaderProgram->getProgram(), "v_effectColor");
        }
        break;
    default:
        return;
    }
    
    _uniformTextColor = glGetUniformLocation(_shaderProgram->getProgram(), "v_textColor");
}

void Label::setFontAtlas(FontAtlas* atlas,bool distanceFieldEnabled /* = false */, bool useA8Shader /* = false */)
{
    if (atlas == _fontAtlas)
    {
        FontAtlasCache::releaseFontAtlas(atlas);
        return;
    }

    if (_fontAtlas)
    {
        FontAtlasCache::releaseFontAtlas(_fontAtlas);
        _fontAtlas = nullptr;
    }

    _fontAtlas = atlas;

    if (_textureAtlas)
    {
        _textureAtlas->setTexture(_fontAtlas->getTexture(0));
    }
    else
    {
        SpriteBatchNode::initWithTexture(_fontAtlas->getTexture(0), 30);
    }

    if (_reusedLetter == nullptr)
    {
        _reusedLetter = Sprite::createWithTexture(_fontAtlas->getTexture(0));
        _reusedLetter->setOpacityModifyRGB(_isOpacityModifyRGB);            
        _reusedLetter->retain();
        _reusedLetter->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        _reusedLetter->setBatchNode(this);
    }
    else
    {
        _reusedLetter->setTexture(_fontAtlas->getTexture(0));
    }

    if (_fontAtlas)
    {
        _commonLineHeight = _fontAtlas->getCommonLineHeight();
        _contentDirty = true;
    }
    _useDistanceField = distanceFieldEnabled;
    _useA8Shader = useA8Shader;

    if (_currentLabelType != LabelType::TTF)
    {
        _currLabelEffect = LabelEffect::NORMAL;
        updateShaderProgram();
    }
}

bool Label::setTTFConfig(const TTFConfig& ttfConfig)
{
    FontAtlas *newAtlas = FontAtlasCache::getFontAtlasTTF(ttfConfig);

    if (!newAtlas)
    {
        reset();
        return false;
    }

    _currentLabelType = LabelType::TTF;
    setFontAtlas(newAtlas,ttfConfig.distanceFieldEnabled,true);

    _fontConfig = ttfConfig;
    if (_fontConfig.outlineSize > 0)
    {
        _fontConfig.distanceFieldEnabled = false;
        _useDistanceField = false;
        _useA8Shader = false;
        _currLabelEffect = LabelEffect::OUTLINE;
        updateShaderProgram();
    }
    else 
    {
        _currLabelEffect = LabelEffect::NORMAL;
        updateShaderProgram();
        if(ttfConfig.distanceFieldEnabled)
        {
            this->setFontScale(1.0f * ttfConfig.fontSize / DistanceFieldFontSize);
        }
    }

    return true;
}

bool Label::setBMFontFilePath(const std::string& bmfontFilePath, const Point& imageOffset /* = Point::ZERO */)
{
    FontAtlas *newAtlas = FontAtlasCache::getFontAtlasFNT(bmfontFilePath,imageOffset);

    if (!newAtlas)
    {
        reset();
        return false;
    }
    _bmFontPath = bmfontFilePath;
    _currentLabelType = LabelType::BMFONT;
    setFontAtlas(newAtlas);

    return true;
}

void Label::setString(const std::string& text)
{
    _originalUTF8String = text;
    _contentDirty = true;
}

void Label::setAlignment(TextHAlignment hAlignment,TextVAlignment vAlignment)
{
    if (hAlignment != _hAlignment || vAlignment != _vAlignment)
    {
        _hAlignment = hAlignment;
        _vAlignment = vAlignment;

        _contentDirty = true;
    }
}

void Label::setMaxLineWidth(unsigned int maxLineWidth)
{
    if (_labelWidth == 0 && _maxLineWidth != maxLineWidth)
    {
        _maxLineWidth = maxLineWidth;
        _contentDirty = true;
    }
}

void Label::setDimensions(unsigned int width,unsigned int height)
{
    if (height != _labelHeight || width != _labelWidth)
    {
        _labelWidth = width;
        _labelHeight = height;
        _labelDimensions.width = width;
        _labelDimensions.height = height;

        _maxLineWidth = width;
        _contentDirty = true;
    }  
}

void Label::setLineBreakWithoutSpace(bool breakWithoutSpace)
{
    if (breakWithoutSpace != _lineBreakWithoutSpaces)
    {
        _lineBreakWithoutSpaces = breakWithoutSpace;
        _contentDirty = true;     
    }
}

void Label::setScale(float scale)
{
    if (_useDistanceField)
    {
        scale *= _fontScale;
    } 
    Node::setScale(scale);
}

void Label::setScaleX(float scaleX)
{
    if (_useDistanceField)
    {
        scaleX *= _fontScale;
    } 
    Node::setScaleX(scaleX);
}

void Label::setScaleY(float scaleY)
{
    if (_useDistanceField)
    {
        scaleY *= _fontScale;
    } 
    Node::setScaleY(scaleY);
}

float Label::getScaleY() const
{
    if (_useDistanceField)
    {
        return _scaleY / _fontScale;
    }
    else
    {
        return _scaleY;
    }
}

float Label::getScaleX() const
{
    if (_useDistanceField)
    {
        return _scaleX / _fontScale;
    }
    else
    {
        return _scaleX;
    }
}

void Label::alignText()
{
    if (_fontAtlas == nullptr)
    {
        return;
    }

    for (const auto& batchNode:_batchNodes)
    {
        batchNode->getTextureAtlas()->removeAllQuads();
    }
    _fontAtlas->prepareLetterDefinitions(_currentUTF16String);
    auto textures = _fontAtlas->getTextures();
    if (textures.size() > _batchNodes.size())
    {
        for (auto index = _batchNodes.size(); index < textures.size(); ++index)
        {
            auto batchNode = SpriteBatchNode::createWithTexture(textures[index]);
            batchNode->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
            batchNode->setPosition(Point::ZERO);
            Node::addChild(batchNode,0,Node::INVALID_TAG);
            _batchNodes.push_back(batchNode);
        }
    }
    LabelTextFormatter::createStringSprites(this);    
    if(_maxLineWidth > 0 && _contentSize.width > _maxLineWidth && LabelTextFormatter::multilineText(this) )      
        LabelTextFormatter::createStringSprites(this);

    if(_labelWidth > 0 || (_currNumLines > 1 && _hAlignment != TextHAlignment::LEFT))
        LabelTextFormatter::alignText(this);

    int strLen = cc_wcslen(_currentUTF16String);
    Rect uvRect;
    Sprite* letterSprite;
    for(const auto &child : _children) {
        int tag = child->getTag();
        if(tag >= strLen)
        {
            SpriteBatchNode::removeChild(child, true);
        }
        else if(tag >= 0)
        {
            letterSprite = dynamic_cast<Sprite*>(child);
            if (letterSprite)
            {
                uvRect.size.height = _lettersInfo[tag].def.height;
                uvRect.size.width  = _lettersInfo[tag].def.width;
                uvRect.origin.x    = _lettersInfo[tag].def.U;
                uvRect.origin.y    = _lettersInfo[tag].def.V;

                letterSprite->setTexture(textures[_lettersInfo[tag].def.textureID]);
                letterSprite->setTextureRect(uvRect);
            }          
        }
    }

    updateQuads();

    updateColor();
}

bool Label::computeHorizontalKernings(unsigned short int *stringToRender)
{
    if (_horizontalKernings)
    {
        delete [] _horizontalKernings;
        _horizontalKernings = nullptr;
    }

    int letterCount = 0;
    _horizontalKernings = _fontAtlas->getFont()->getHorizontalKerningForTextUTF16(stringToRender, letterCount);

    if(!_horizontalKernings)
        return false;
    else
        return true;
}

bool Label::setOriginalString(unsigned short *stringToSet)
{
    if (_originalUTF16String)
    {
        delete [] _originalUTF16String;
    }

    int newStringLenght = cc_wcslen(stringToSet);
    _originalUTF16String = new unsigned short int [newStringLenght + 1];
    memset(_originalUTF16String, 0, (newStringLenght + 1) * 2);
    memcpy(_originalUTF16String, stringToSet, (newStringLenght * 2));
    _originalUTF16String[newStringLenght] = 0;

    return true;
}

bool Label::setCurrentString(unsigned short *stringToSet)
{
    // set the new string
    if (_currentUTF16String)
    {
        delete [] _currentUTF16String;
    }

    _currentUTF16String  = stringToSet;
    computeStringNumLines();

    // compute the advances
    if (_fontAtlas)
    {
        computeHorizontalKernings(stringToSet);
    }
    return true;
}

void Label::updateQuads()
{
    int index;
    for (int ctr = 0; ctr < _limitShowCount; ++ctr)
    {
        auto &letterDef = _lettersInfo[ctr].def;

        if (letterDef.validDefinition)
        {
            _reusedRect.size.height = letterDef.height;
            _reusedRect.size.width  = letterDef.width;
            _reusedRect.origin.x    = letterDef.U;
            _reusedRect.origin.y    = letterDef.V;
            _reusedLetter->setTextureRect(_reusedRect,false,_reusedRect.size);

            _reusedLetter->setPosition(_lettersInfo[ctr].position);
            index = static_cast<int>(_batchNodes[letterDef.textureID]->getTextureAtlas()->getTotalQuads());
            _lettersInfo[ctr].atlasIndex = index;
            _batchNodes[letterDef.textureID]->insertQuadFromSprite(_reusedLetter,index);
        }     
    }
}

bool Label::recordLetterInfo(const cocos2d::Point& point,const FontLetterDefinition& letterDef, int spriteIndex)
{
    if (static_cast<std::size_t>(spriteIndex) >= _lettersInfo.size())
    {
        LetterInfo tmpInfo;
        _lettersInfo.push_back(tmpInfo);
    }

    _lettersInfo[spriteIndex].def = letterDef;
    _lettersInfo[spriteIndex].position = point;
    _lettersInfo[spriteIndex].contentSize.width = _lettersInfo[spriteIndex].def.width;
    _lettersInfo[spriteIndex].contentSize.height = _lettersInfo[spriteIndex].def.height;
    _limitShowCount++;

    return _lettersInfo[spriteIndex].def.validDefinition;
}

bool Label::recordPlaceholderInfo(int spriteIndex)
{
    if (static_cast<std::size_t>(spriteIndex) >= _lettersInfo.size())
    {
        LetterInfo tmpInfo;
        _lettersInfo.push_back(tmpInfo);
    }

    _lettersInfo[spriteIndex].def.validDefinition = false;
    _limitShowCount++;

    return false;
}

void Label::addChild(Node * child, int zOrder/* =0 */, int tag/* =0 */)
{
    CCASSERT(0, "addChild: is not supported on Label.");
}

void Label::sortAllChildren()
{
    // Label ignore sort children
}

void Label::enableGlow(const Color4B& glowColor)
{
    if(! _useDistanceField)
        return;
    _currLabelEffect = LabelEffect::GLOW;
    _effectColor = glowColor;
    _effectColorF.r = _effectColor.r / 255.0f;
    _effectColorF.g = _effectColor.g / 255.0f;
    _effectColorF.b = _effectColor.b / 255.0f;
    _effectColorF.a = _effectColor.a / 255.0f;
    updateShaderProgram();
}

void Label::enableOutline(const Color4B& outlineColor,int outlineSize /* = -1 */)
{
    _effectColor = outlineColor;
    _effectColorF.r = _effectColor.r / 255.0f;
    _effectColorF.g = _effectColor.g / 255.0f;
    _effectColorF.b = _effectColor.b / 255.0f;
    _effectColorF.a = _effectColor.a / 255.0f;

    if (outlineSize > 0)
    {
        _outlineSize = outlineSize;
        if (_currentLabelType == LabelType::TTF)
        {
            if (_fontConfig.outlineSize != outlineSize)
            { 
                auto config = _fontConfig;
                config.outlineSize = outlineSize;
                setTTFConfig(config);
                updateShaderProgram();
            }
        }

        _currLabelEffect = LabelEffect::OUTLINE;
        _contentDirty = true;
    }
}

void Label::enableShadow(const Color4B& shadowColor /* = Color4B::BLACK */,const Size &offset /* = Size(2 ,-2)*/, int blurRadius /* = 0 */)
{
    _shadowEnabled = true;
    _shadowDirty = true;

    _shadowColor.r = shadowColor.r;
    _shadowColor.g = shadowColor.g;
    _shadowColor.b = shadowColor.b;
    _shadowOpacity = shadowColor.a / 255.0f;

    auto contentScaleFactor = CC_CONTENT_SCALE_FACTOR();
    _shadowOffset.width = offset.width * contentScaleFactor;
    _shadowOffset.height = offset.height * contentScaleFactor;
    //todo:support blur for shadow
    _shadowBlurRadius = 0;

    if (_textSprite && _shadowNode)
    {
        _shadowNode->setColor(_shadowColor);
        _shadowNode->setOpacity(_shadowOpacity * _displayedOpacity);
        _shadowNode->setPosition(_shadowOffset.width, _shadowOffset.height);
    }
}

void Label::disableEffect()
{
    if (_currLabelEffect == LabelEffect::OUTLINE)
    {
        _fontConfig.outlineSize = 0;
        setTTFConfig(_fontConfig);
    }
    _currLabelEffect = LabelEffect::NORMAL;
    updateShaderProgram();
    _contentDirty = true;
    _shadowEnabled = false;
    if (_shadowNode)
    {
        Node::removeChild(_shadowNode,true);
        _shadowNode = nullptr;
    }
}

void Label::setFontScale(float fontScale)
{
    _fontScale = fontScale * CC_CONTENT_SCALE_FACTOR();
    Node::setScale(_fontScale);
}

void Label::onDraw(const kmMat4& transform, bool transformUpdated)
{
    CC_PROFILER_START("Label - draw");

    // Optimization: Fast Dispatch
    if( _batchNodes.size() == 1 && _textureAtlas->getTotalQuads() == 0 )
    {
        return;
    }

    _shaderProgram->use();
    GL::blendFunc( _blendFunc.src, _blendFunc.dst );

    if (_currentLabelType == LabelType::TTF)
    {
        _shaderProgram->setUniformLocationWith4f(_uniformTextColor, 
            _textColorF.r,_textColorF.g,_textColorF.b,_textColorF.a);
    }

    if (_currLabelEffect == LabelEffect::OUTLINE || _currLabelEffect == LabelEffect::GLOW)
    {
         _shaderProgram->setUniformLocationWith4f(_uniformEffectColor, 
             _effectColorF.r,_effectColorF.g,_effectColorF.b,_effectColorF.a);
    }

    if(_shadowEnabled && _shadowBlurRadius <= 0)
    {
        drawShadowWithoutBlur();
    }

    _shaderProgram->setUniformsForBuiltins(transform);

    for(const auto &child: _children)
    {
        if(child->getTag() >= 0)
            child->updateTransform();
    }

    for (const auto& batchNode:_batchNodes)
    {
        batchNode->getTextureAtlas()->drawQuads();
    }

    CC_PROFILER_STOP("Label - draw");
}

void Label::drawShadowWithoutBlur()
{
    Color3B oldColor = _realColor;
    GLubyte oldOPacity = _displayedOpacity;
    _displayedOpacity = _shadowOpacity * _displayedOpacity;
    setColor(_shadowColor);

    _shaderProgram->setUniformsForBuiltins(_shadowTransform);
    for(const auto &child: _children)
    {
        child->updateTransform();
    }
    for (const auto& batchNode:_batchNodes)
    {
        batchNode->getTextureAtlas()->drawQuads();
    }
    
    _displayedOpacity = oldOPacity;
    setColor(oldColor);
}

void Label::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(Label::onDraw, this, transform, transformUpdated);
    renderer->addCommand(&_customCommand);
}

void Label::createSpriteWithFontDefinition()
{
    _currentLabelType = LabelType::STRING_TEXTURE;

    auto texture = new Texture2D;
    texture->initWithString(_originalUTF8String.c_str(),_fontDefinition);

    _textSprite = Sprite::createWithTexture(texture);
    _textSprite->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    this->setContentSize(_textSprite->getContentSize());
    texture->release();
    if (_blendFuncDirty)
    {
        _textSprite->setBlendFunc(_blendFunc);
    }

    Node::addChild(_textSprite,0,Node::INVALID_TAG);

    _textSprite->updateDisplayedColor(_displayedColor);
}

void Label::setFontDefinition(const FontDefinition& textDefinition)
{
    _fontDefinition = textDefinition;
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID) && (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
    if (_fontDefinition._stroke._strokeEnabled)
    {
        CCLOGERROR("Currently only supported on iOS and Android!");
    }
    _fontDefinition._stroke._strokeEnabled = false;
#endif
    if (_fontDefinition._shadow._shadowEnabled)
    {
        _fontDefinition._shadow._shadowEnabled = false;
        enableShadow(Color4B(0,0,0,255 * _fontDefinition._shadow._shadowOpacity),_fontDefinition._shadow._shadowOffset,_fontDefinition._shadow._shadowBlur);
    }
    _compatibleMode = true;
}

void Label::updateContent()
{
    auto utf16String = cc_utf8_to_utf16(_originalUTF8String.c_str());
    setCurrentString(utf16String);
    setOriginalString(utf16String);

    if (_textSprite)
    {
        Node::removeChild(_textSprite,true);
        _textSprite = nullptr;
        if (_shadowNode)
        {
            Node::removeChild(_shadowNode,true);
            _shadowNode = nullptr;
        }
    }

    if (_fontAtlas)
    {
        alignText();
    }
    else
    {
        if (!_compatibleMode)
        {
            _fontDefinition._fontName = _systemFont;
            _fontDefinition._fontSize = _systemFontSize;

            _fontDefinition._alignment = _hAlignment;
            _fontDefinition._vertAlignment = _vAlignment;

            _fontDefinition._dimensions.width = _labelWidth;
            _fontDefinition._dimensions.height = _labelHeight;

            _fontDefinition._fontFillColor.r = _textColor.r;
            _fontDefinition._fontFillColor.g = _textColor.g;
            _fontDefinition._fontFillColor.b = _textColor.b;

            _fontDefinition._shadow._shadowEnabled = false;

            if (_currLabelEffect == LabelEffect::OUTLINE && _outlineSize > 0)
            {
                _fontDefinition._stroke._strokeEnabled = true;
                _fontDefinition._stroke._strokeSize = _outlineSize;
                _fontDefinition._stroke._strokeColor.r = _effectColor.r;
                _fontDefinition._stroke._strokeColor.g = _effectColor.g;
                _fontDefinition._stroke._strokeColor.b = _effectColor.b;
            }
            else
            {
                _fontDefinition._stroke._strokeEnabled = false;
            }

#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID) && (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
            if (_fontDefinition._stroke._strokeEnabled)
            {
                CCLOGERROR("Currently only supported on iOS and Android!");
            }
            _fontDefinition._stroke._strokeEnabled = false;
#endif
        }

        createSpriteWithFontDefinition();
    }
    _contentDirty = false;
}

void Label::updateFont()
{
    if (_fontAtlas)
    {
        _batchNodes.clear();
        _batchNodes.push_back(this);

        FontAtlasCache::releaseFontAtlas(_fontAtlas);
        _fontAtlas = nullptr;
    }

    _contentDirty = true;
    _fontDirty = false;
}

void Label::drawTextSprite(Renderer *renderer, bool parentTransformUpdated)
{
    if (_fontDefinition._fontFillColor != _textColor)
    {
        updateContent();
    }
    
    if (_shadowEnabled && _shadowNode == nullptr)
    {
        _shadowNode = Sprite::createWithTexture(_textSprite->getTexture());
        if (_shadowNode)
        {
            if (_blendFuncDirty)
            {
                _shadowNode->setBlendFunc(_blendFunc);
            }
            _shadowNode->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
            _shadowNode->setColor(_shadowColor);
            _shadowNode->setOpacity(_shadowOpacity * _displayedOpacity);
            _shadowNode->setPosition(_shadowOffset.width, _shadowOffset.height);
            Node::addChild(_shadowNode,0,Node::INVALID_TAG);
        }
    }
    if (_shadowNode)
    {
        _shadowNode->visit(renderer, _modelViewTransform, parentTransformUpdated);
    }
    _textSprite->visit(renderer, _modelViewTransform, parentTransformUpdated);
}

void Label::visit(Renderer *renderer, const kmMat4 &parentTransform, bool parentTransformUpdated)
{
    if (! _visible || _originalUTF8String.empty())
    {
        return;
    }
    if (_fontDirty)
    {
        updateFont();
    }
    if (_contentDirty)
    {
        updateContent();
    }

    bool dirty = parentTransformUpdated || _transformUpdated;

    if (_shadowEnabled && _shadowBlurRadius <= 0 && (_shadowDirty || dirty))
    {
        _position.x += _shadowOffset.width;
        _position.y += _shadowOffset.height;
        _transformDirty = _inverseDirty = true;

        _shadowTransform = transform(parentTransform);

        _position.x -= _shadowOffset.width;
        _position.y -= _shadowOffset.height;
        _transformDirty = _inverseDirty = true;

        _shadowDirty = false;
    }

    if(dirty)
    {
        _modelViewTransform = transform(parentTransform);
    }
    _transformUpdated = false;

    // IMPORTANT:
    // To ease the migration to v3.0, we still support the kmGL stack,
    // but it is deprecated and your code should not rely on it
    kmGLPushMatrix();
    kmGLLoadMatrix(&_modelViewTransform);

    if (_textSprite)
    {
        drawTextSprite(renderer,dirty);
    }
    else
    {
        draw(renderer, _modelViewTransform, dirty);
    }

    kmGLPopMatrix();
    
    setOrderOfArrival(0);
}

void Label::setSystemFontName(const std::string& systemFont)
{
    if (systemFont != _systemFont)
    {
        _systemFont = systemFont;
        _fontDirty = true;
    }
}

void Label::setSystemFontSize(float fontSize)
{
    if (_systemFontSize != fontSize)
    {
        _systemFontSize = fontSize;
        _fontDirty = true;
    }
}

///// PROTOCOL STUFF
Sprite * Label::getLetter(int letterIndex)
{
    if (_fontDirty)
    {
        updateFont();
        return nullptr;
    }

    if (_contentDirty)
    {
        updateContent();
    }
    
    if (! _textSprite && letterIndex < _limitShowCount)
    {
        const auto &letter = _lettersInfo[letterIndex];

        if(! letter.def.validDefinition)
            return nullptr;

        Sprite* sp = static_cast<Sprite*>(this->getChildByTag(letterIndex));

        if (!sp)
        {
            Rect uvRect;
            uvRect.size.height = letter.def.height;
            uvRect.size.width  = letter.def.width;
            uvRect.origin.x    = letter.def.U;
            uvRect.origin.y    = letter.def.V;

            sp = Sprite::createWithTexture(_fontAtlas->getTexture(letter.def.textureID),uvRect);
            sp->setBatchNode(_batchNodes[letter.def.textureID]);
            sp->setPosition(Point(letter.position.x + uvRect.size.width / 2, 
                letter.position.y - uvRect.size.height / 2));
            sp->setOpacity(_realOpacity);

            _batchNodes[letter.def.textureID]->addSpriteWithoutQuad(sp, letter.atlasIndex, letterIndex);
        }
        return sp;
    }

    return nullptr;
}

int Label::getCommonLineHeight() const
{
    return _textSprite ? 0 : _commonLineHeight;
}

void Label::computeStringNumLines()
{
    int quantityOfLines = 1;

    int stringLen = _currentUTF16String ? cc_wcslen(_currentUTF16String) : -1;
    if (stringLen < 1)
    {
        _currNumLines = stringLen;
        return;
    }

    // count number of lines
    for (int i = 0; i < stringLen - 1; ++i)
    {
        if (_currentUTF16String[i] == '\n')
        {
            quantityOfLines++;
        }
    }

    _currNumLines = quantityOfLines;
}

int Label::getStringLength() const
{
    return _currentUTF16String ? cc_wcslen(_currentUTF16String) : (int)_originalUTF8String.length();
}

// RGBA protocol
bool Label::isOpacityModifyRGB() const
{
    return _isOpacityModifyRGB;
}

void Label::setOpacityModifyRGB(bool isOpacityModifyRGB)
{
    _isOpacityModifyRGB = isOpacityModifyRGB;

    for(const auto& child: _children) {
        child->setOpacityModifyRGB(_isOpacityModifyRGB);
    }

    _reusedLetter->setOpacityModifyRGB(true);
}

void Label::updateDisplayedColor(const Color3B& parentColor)
{
    _displayedColor.r = _realColor.r * parentColor.r/255.0;
    _displayedColor.g = _realColor.g * parentColor.g/255.0;
    _displayedColor.b = _realColor.b * parentColor.b/255.0;
    updateColor();

    if (_textSprite)
    {
        _textSprite->updateDisplayedColor(_displayedColor);
        if (_shadowNode)
        {
            _shadowNode->updateDisplayedColor(_displayedColor);
        }
    }
}

void Label::updateDisplayedOpacity(GLubyte parentOpacity)
{
    _displayedOpacity = _realOpacity * parentOpacity/255.0;
    updateColor();

    if (_textSprite)
    {
        _textSprite->updateDisplayedOpacity(_displayedOpacity);
        if (_shadowNode)
        {
            _shadowNode->updateDisplayedOpacity(_displayedOpacity);
        }
    }
}

void Label::setTextColor(const Color4B &color)
{
    _textColor = color;
    _textColorF.r = _textColor.r / 255.0f;
    _textColorF.g = _textColor.g / 255.0f;
    _textColorF.b = _textColor.b / 255.0f;
    _textColorF.a = _textColor.a / 255.0f;
}

void Label::updateColor()
{
    if (nullptr == _textureAtlas)
    {
        return;
    }

    Color4B color4( _displayedColor.r, _displayedColor.g, _displayedColor.b, _displayedOpacity );

    // special opacity for premultiplied textures
    if (_isOpacityModifyRGB)
    {
        color4.r *= _displayedOpacity/255.0f;
        color4.g *= _displayedOpacity/255.0f;
        color4.b *= _displayedOpacity/255.0f;
    }

    cocos2d::TextureAtlas* textureAtlas;
    V3F_C4B_T2F_Quad *quads;
    for (const auto& batchNode:_batchNodes)
    {
        textureAtlas = batchNode->getTextureAtlas();
        quads = textureAtlas->getQuads();
        auto count = textureAtlas->getTotalQuads();

        for (int index = 0; index < count; ++index)
        {
            quads[index].bl.colors = color4;
            quads[index].br.colors = color4;
            quads[index].tl.colors = color4;
            quads[index].tr.colors = color4;
            textureAtlas->updateQuad(&quads[index], index);
        }
    }
}

std::string Label::getDescription() const
{
    return StringUtils::format("<Label | Tag = %d, Label = '%s'>", _tag, cc_utf16_to_utf8(_currentUTF16String,-1,nullptr,nullptr));
}

const Size& Label::getContentSize() const
{
    if (_fontDirty)
    {
        const_cast<Label*>(this)->updateFont();
    }
    if (_contentDirty)
    {
        const_cast<Label*>(this)->updateContent();
    }
    return _contentSize;
}

Rect Label::getBoundingBox() const
{
    const_cast<Label*>(this)->getContentSize();

    return Node::getBoundingBox();
}

void Label::setBlendFunc(const BlendFunc &blendFunc)
{
    _blendFunc = blendFunc;
    _blendFuncDirty = true;
    if (_textSprite)
    {
        _textSprite->setBlendFunc(blendFunc);
        if (_shadowNode)
        {
            _shadowNode->setBlendFunc(blendFunc);
        }
    }
}

NS_CC_END
