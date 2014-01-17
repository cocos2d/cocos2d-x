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
#include "CCFontDefinition.h"
#include "CCFontAtlasCache.h"
#include "CCLabelTextFormatter.h"
#include "CCSprite.h"
#include "CCShaderCache.h"
#include "ccUTF8.h"
#include "CCSpriteFrame.h"
#include "CCDirector.h"
#include "renderer/CCRenderer.h"

#define DISTANCEFIELD_ATLAS_FONTSIZE 50

NS_CC_BEGIN

Label* Label::create()
{
    Label *ret = new Label();

    if (!ret)
        return nullptr;

    ret->autorelease();

    return ret;
}

Label* Label::createWithTTF(const TTFConfig& ttfConfig, const std::string& text, TextHAlignment alignment /* = TextHAlignment::CENTER */, int lineSize /* = 0 */)
{
    Label *ret = new Label();

    if (!ret)
        return nullptr;
      
    if (ret->setTTFConfig(ttfConfig))
    {
        if(ttfConfig.distanceFieldEnabled)
            ret->setFontSize(ttfConfig.fontSize);
        ret->setString(text,alignment,lineSize);
        ret->autorelease();
        return ret;
    }
    else
    {
        delete ret;
        return nullptr;
    }
}

Label* Label::createWithTTF(const std::string& text, const std::string& fontFilePath, int fontSize, int lineSize /* = 0 */, TextHAlignment alignment /* = TextHAlignment::CENTER */, GlyphCollection glyphs /* = GlyphCollection::NEHE */, const char *customGlyphs /* = 0 */, bool useDistanceField /* = false */)
{
    TTFConfig ttfConfig(fontFilePath.c_str(),fontSize,glyphs,customGlyphs,useDistanceField);
    return createWithTTF(ttfConfig,text,alignment,lineSize);
}

Label* Label::createWithBMFont(const std::string& bmfontFilePath, const std::string& text,const TextHAlignment& alignment /* = TextHAlignment::CENTER */, int lineSize /* = 0 */)
{
    Label *ret = new Label();

    if (!ret)
        return nullptr;

    if (ret->setBMFontFilePath(bmfontFilePath))
    {
        ret->setString(text,alignment,lineSize);
        ret->autorelease();
        return ret;
    }
    else
    {
        delete ret;
        return nullptr;
    }
}

Label* Label::createWithCharMap(const std::string& plistFile)
{
    Label *ret = new Label();

    if (!ret)
        return nullptr;

    if (ret->setCharMap(plistFile))
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        delete ret;
        return nullptr;
    }
}

Label* Label::createWithCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap)
{
    Label *ret = new Label();

    if (!ret)
        return nullptr;

    if (ret->setCharMap(texture,itemWidth,itemHeight,startCharMap))
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        delete ret;
        return nullptr;
    }
}

Label* Label::createWithCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap)
{
    Label *ret = new Label();

    if (!ret)
        return nullptr;

    if (ret->setCharMap(charMapFile,itemWidth,itemHeight,startCharMap))
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        delete ret;
        return nullptr;
    }
}

bool Label::setCharMap(const std::string& plistFile)
{
    FontAtlas *newAtlas = FontAtlasCache::getFontAtlasCharMap(plistFile);

    if (!newAtlas)
        return false;

    return initWithFontAtlas(newAtlas);
}

bool Label::setCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap)
{
    FontAtlas *newAtlas = FontAtlasCache::getFontAtlasCharMap(texture,itemWidth,itemHeight,startCharMap);

    if (!newAtlas)
        return false;

    return initWithFontAtlas(newAtlas);
}

bool Label::setCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap)
{
    FontAtlas *newAtlas = FontAtlasCache::getFontAtlasCharMap(charMapFile,itemWidth,itemHeight,startCharMap);

    if (!newAtlas)
        return false;

    return initWithFontAtlas(newAtlas);
}

Label::Label(FontAtlas *atlas, TextHAlignment alignment, bool useDistanceField,bool useA8Shader)
: _reusedLetter(nullptr)
, _commonLineHeight(0.0f)
, _lineBreakWithoutSpaces(false)
, _width(0.0f)
, _alignment(alignment)
, _currentUTF16String(nullptr)
, _originalUTF16String(nullptr)
, _advances(nullptr)
, _fontAtlas(atlas)
, _isOpacityModifyRGB(true)
, _useDistanceField(useDistanceField)
, _useA8Shader(useA8Shader)
, _fontSize(0)
, _uniformEffectColor(0)
{
    _cascadeColorEnabled = true;
}

Label::~Label()
{   
    delete [] _currentUTF16String;
    delete [] _originalUTF16String;
    delete [] _advances;
    
    if (_fontAtlas)
        FontAtlasCache::releaseFontAtlas(_fontAtlas);

    _reusedLetter->release();
}

bool Label::init()
{ 
    bool ret = true;
    if(_fontAtlas)
    {
        if (_reusedLetter == nullptr)
        {
            _reusedLetter = Sprite::createWithTexture(&_fontAtlas->getTexture(0));
            _reusedLetter->setOpacityModifyRGB(_isOpacityModifyRGB);            
            _reusedLetter->retain();
        }
       ret = SpriteBatchNode::initWithTexture(&_fontAtlas->getTexture(0), 30);
    }
    if (_useDistanceField)
        setLabelEffect(LabelEffect::NORMAL,Color3B::BLACK);
    else if(_useA8Shader)
        setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_A8_COLOR));
    else
        setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));

    return ret;
}

bool Label::initWithFontAtlas(FontAtlas* atlas,bool distanceFieldEnabled /* = false */, bool useA8Shader /* = false */)
{
    FontAtlas *oldAtlas = _fontAtlas;
    bool oldDistanceFieldEnable = _useDistanceField;
    bool oldA8ShaderEnabel = _useA8Shader;

    _fontAtlas = atlas;
    _useDistanceField = distanceFieldEnabled;
    _useA8Shader = useA8Shader;

    bool ret = Label::init();
    if (oldAtlas)
    {
        if (ret)
        {
            FontAtlasCache::releaseFontAtlas(oldAtlas);        
        }
        else
        {
            _fontAtlas = oldAtlas;
            _useDistanceField = oldDistanceFieldEnable;
            _useA8Shader = oldA8ShaderEnabel;
            Label::init();

            FontAtlasCache::releaseFontAtlas(atlas);
        }
    }

    if (_fontAtlas)
    {
        _commonLineHeight = _fontAtlas->getCommonLineHeight();
        if (_currentUTF16String)
        {      
            alignText();
        }
    }

    return ret;
}

bool Label::setTTFConfig(const TTFConfig& ttfConfig)
{
    FontAtlas *newAtlas = nullptr;
    if(ttfConfig.distanceFieldEnabled)
        newAtlas = FontAtlasCache::getFontAtlasTTF(ttfConfig.fontFilePath, DISTANCEFIELD_ATLAS_FONTSIZE, ttfConfig.glyphs, ttfConfig.customGlyphs,true);
    else
        newAtlas = FontAtlasCache::getFontAtlasTTF(ttfConfig.fontFilePath, ttfConfig.fontSize, ttfConfig.glyphs, ttfConfig.customGlyphs,false);

    if (!newAtlas)
        return false;

    return initWithFontAtlas(newAtlas,ttfConfig.distanceFieldEnabled,true);
}

bool Label::setBMFontFilePath(const std::string& bmfontFilePath)
{
    FontAtlas *newAtlas = FontAtlasCache::getFontAtlasFNT(bmfontFilePath);

    if (!newAtlas)
        return false;

    return initWithFontAtlas(newAtlas);
}

bool Label::setString(const std::string& text, const TextHAlignment& alignment /* = TextHAlignment::CENTER */, float lineWidth /* = -1 */, bool lineBreakWithoutSpaces /* = false */)
{
    if (!_fontAtlas || _commonLineHeight <= 0)
        return false;
    
    // carloX
    // reset the string
    resetCurrentString();
    
    if(lineWidth >= 0)
    {
        _width                  = lineWidth;
    }   
    _alignment              = alignment;
    _lineBreakWithoutSpaces = lineBreakWithoutSpaces;
    
    unsigned short* utf16String = cc_utf8_to_utf16(text.c_str());
    if(!utf16String)
        return false;
    
    setCurrentString(utf16String);
    setOriginalString(utf16String);
    
    // align text
    alignText();
    
    // done here
    return true;
}

void Label::setAlignment(TextHAlignment alignment)
{
    // store the new alignment
    if (alignment != _alignment)
    {
        // store
        _alignment = alignment;
        
        // reset the string
        resetCurrentString();
        
        // need to align text again
        alignText();
    }
}

void Label::setWidth(float width)
{
    if (width != _width)
    {
        // store
        _width = width;
        
        
        // reset the string
        resetCurrentString();
        
        // need to align text again
        alignText();
    }
}

void Label::setLineBreakWithoutSpace(bool breakWithoutSpace)
{
    if (breakWithoutSpace != _lineBreakWithoutSpaces)
    {
        // store
        _lineBreakWithoutSpaces = breakWithoutSpace;
        
        // need to align text again
        alignText();
    }
}

void Label::setScale(float scale)
{
    if (_useDistanceField)
    {
        scale *= 1.0f * _fontSize / DISTANCEFIELD_ATLAS_FONTSIZE;
    } 
    Node::setScale(scale);
}

void Label::setScaleX(float scaleX)
{
    if (_useDistanceField)
    {
        scaleX *= 1.0f * _fontSize / DISTANCEFIELD_ATLAS_FONTSIZE;
    } 
    Node::setScaleX(scaleX);
}

void Label::setScaleY(float scaleY)
{
    if (_useDistanceField)
    {
        scaleY *= 1.0f * _fontSize / DISTANCEFIELD_ATLAS_FONTSIZE;
    } 
    Node::setScaleY(scaleY);
}

float Label::getScaleY() const
{
    if (_useDistanceField)
    {
        return _scaleY / (1.0f * _fontSize / DISTANCEFIELD_ATLAS_FONTSIZE);
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
        return _scaleX / (1.0f * _fontSize / DISTANCEFIELD_ATLAS_FONTSIZE);
    }
    else
    {
        return _scaleX;
    }
}

void Label::alignText()
{      
    if(_textureAtlas)
        _textureAtlas->removeAllQuads();  
    _fontAtlas->prepareLetterDefinitions(_currentUTF16String);
    LabelTextFormatter::createStringSprites(this);    
    if(_width > 0 && LabelTextFormatter::multilineText(this) )      
        LabelTextFormatter::createStringSprites(this);
    
    LabelTextFormatter::alignText(this);
  
    int strLen = cc_wcslen(_currentUTF16String);
    for(const auto &child : _children) {
        int tag = child->getTag();
        if(tag < 0 || tag >= strLen)
            SpriteBatchNode::removeChild(child, true);
    }

    _reusedLetter->setBatchNode(nullptr);
   
    int vaildIndex = 0;
    Sprite* child = nullptr;
    Rect uvRect;
    for (int ctr = 0; ctr < strLen; ++ctr)
    {        
        if (_lettersInfo[ctr].def.validDefinition)
        {
            child = static_cast<Sprite*>( this->getChildByTag(ctr) );
            if (child)
            {
                uvRect.size.height = _lettersInfo[ctr].def.height;
                uvRect.size.width  = _lettersInfo[ctr].def.width;
                uvRect.origin.x    = _lettersInfo[ctr].def.U;
                uvRect.origin.y    = _lettersInfo[ctr].def.V;

                child->setTexture(&_fontAtlas->getTexture(_lettersInfo[ctr].def.textureID));
                child->setTextureRect(uvRect);              
            }
           
            updateSpriteWithLetterDefinition(_reusedLetter,_lettersInfo[ctr].def,&_fontAtlas->getTexture(_lettersInfo[ctr].def.textureID));
            _reusedLetter->setPosition(_lettersInfo[ctr].position);
            insertQuadFromSprite(_reusedLetter,vaildIndex++);
        }     
    }
}

bool Label::computeAdvancesForString(unsigned short int *stringToRender)
{
    if (_advances)
    {
        delete [] _advances;
        _advances = 0;
    }
    
    int letterCount = 0;
    _advances = _fontAtlas->getFont()->getAdvancesForTextUTF16(stringToRender, letterCount);
    
    if(!_advances)
        return false;
    else
        return true;
}

bool Label::setOriginalString(unsigned short *stringToSet)
{
    if (_originalUTF16String)
    {
        delete [] _originalUTF16String;
        _originalUTF16String = 0;
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
        _currentUTF16String = 0;
    }
    //
    _currentUTF16String  = stringToSet;
    // compute the advances
    return computeAdvancesForString(stringToSet);
}

void Label::resetCurrentString()
{
    if ((!_currentUTF16String) && (!_originalUTF16String))
        return;
    
    // set the new string
    if (_currentUTF16String)
    {
        delete [] _currentUTF16String;
        _currentUTF16String = 0;
    }
    
    int stringLenght = cc_wcslen(_originalUTF16String);
    _currentUTF16String = new unsigned short int [stringLenght + 1];
    memcpy(_currentUTF16String, _originalUTF16String, stringLenght * 2);
    _currentUTF16String[stringLenght] = 0;
    
}

Sprite * Label::updateSpriteWithLetterDefinition(Sprite *spriteToUpdate, const FontLetterDefinition &theDefinition, Texture2D *theTexture)
{
    if (!spriteToUpdate)
    {
        return 0;
    }
    else
    {
        Rect uvRect;
        uvRect.size.height = theDefinition.height;
        uvRect.size.width  = theDefinition.width;
        uvRect.origin.x    = theDefinition.U;
        uvRect.origin.y    = theDefinition.V;
        
        SpriteFrame *frame = SpriteFrame::createWithTexture(theTexture, uvRect);
        if (frame)
        {
            spriteToUpdate->setBatchNode(this); 
            spriteToUpdate->setTexture(theTexture);
            spriteToUpdate->setSpriteFrame(frame);
            spriteToUpdate->setAnchorPoint(Point(theDefinition.anchorX, theDefinition.anchorY));                                        
        }     
        
        return spriteToUpdate;
    }
}

bool Label::recordLetterInfo(const cocos2d::Point& point,unsigned short int theChar, int spriteIndex)
{
    if (static_cast<std::size_t>(spriteIndex) >= _lettersInfo.size())
    {
        LetterInfo tmpInfo;
        _lettersInfo.push_back(tmpInfo);
    }    
       
    _fontAtlas->getLetterDefinitionForChar(theChar, _lettersInfo[spriteIndex].def);
    _lettersInfo[spriteIndex].position = point;
    _lettersInfo[spriteIndex].contentSize.width = _lettersInfo[spriteIndex].def.width;
    _lettersInfo[spriteIndex].contentSize.height = _lettersInfo[spriteIndex].def.height;

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
    
    return false;
}

void Label::addChild(Node * child, int zOrder/* =0 */, int tag/* =0 */)
{
    CCASSERT(0, "addChild: is not supported on Label.");
}

void Label::setLabelEffect(LabelEffect effect,const Color3B& effectColor)
{
    if(_useDistanceField == false)
        return;

    _currLabelEffect = effect;
    _effectColor = effectColor;

    switch (_currLabelEffect)
    {
    case cocos2d::LabelEffect::NORMAL:  
        setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_NORMAL));
        break;
    case cocos2d::LabelEffect::OUTLINE:
        setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_OUTLINE));
        break;
    case cocos2d::LabelEffect::SHADOW:
        setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_SHADOW));
        break;
    case cocos2d::LabelEffect::GLOW:
        setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_GLOW));
        break;
    default:
        return;
    }

    _uniformEffectColor = glGetUniformLocation(_shaderProgram->getProgram(), "v_effectColor");
}

void Label::setFontSize(int fontSize)
{
    _fontSize = fontSize;
    Node::setScale(1.0f*_fontSize/DISTANCEFIELD_ATLAS_FONTSIZE);
}

void Label::onDraw()
{
    CC_PROFILER_START("CCSpriteBatchNode - draw");

    // Optimization: Fast Dispatch
    if( _textureAtlas->getTotalQuads() == 0 )
    {
        return;
    }

    CC_NODE_DRAW_SETUP();

    if (_useDistanceField && _currLabelEffect != LabelEffect::NORMAL)
    {
        _shaderProgram->setUniformLocationWith3f(_uniformEffectColor, _effectColor.r/255.0f,_effectColor.g/255.0f,_effectColor.b/255.0f);
    }

    for(const auto &child: _children)
        child->updateTransform();

    GL::blendFunc( _blendFunc.src, _blendFunc.dst );

    _textureAtlas->drawQuads();

    CC_PROFILER_STOP("CCSpriteBatchNode - draw");
}

void Label::draw()
{
    _customCommand.init(0, _vertexZ);
    _customCommand.func = CC_CALLBACK_0(Label::onDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_customCommand);
}

///// PROTOCOL STUFF

Sprite * Label::getLetter(int ID)
{
    if (ID < getStringLenght())
    {       
        if(_lettersInfo[ID].def.validDefinition == false)
            return nullptr;
       
        Sprite* sp = static_cast<Sprite*>(this->getChildByTag(ID));

        if (!sp)
        {
            Rect uvRect;
            uvRect.size.height = _lettersInfo[ID].def.height;
            uvRect.size.width  = _lettersInfo[ID].def.width;
            uvRect.origin.x    = _lettersInfo[ID].def.U;
            uvRect.origin.y    = _lettersInfo[ID].def.V;

            sp = Sprite::createWithTexture(&_fontAtlas->getTexture(_lettersInfo[ID].def.textureID),uvRect);
            sp->setBatchNode(this);
            sp->setAnchorPoint(Point(_lettersInfo[ID].def.anchorX, _lettersInfo[ID].def.anchorY));                    
            sp->setPosition(_lettersInfo[ID].position);
            sp->setOpacity(_realOpacity);
         
            this->addSpriteWithoutQuad(sp, ID, ID);
        }
        return sp;
    }
    
    return nullptr;
}

float Label::getLetterPosXLeft( int index ) const
{
    return _lettersInfo[index].position.x * _scaleX - (_lettersInfo[index].contentSize.width * _scaleX * _lettersInfo[index].def.anchorX);
}

float Label::getLetterPosXRight( int index ) const
{
    return _lettersInfo[index].position.x * _scaleX + (_lettersInfo[index].contentSize.width * _scaleX * _lettersInfo[index].def.anchorX);
}

int Label::getCommonLineHeight() const
{
    return _commonLineHeight;
}

int Label::getKerningForCharsPair(unsigned short first, unsigned short second) const
{
    return 0;
}

int Label::getXOffsetForChar(unsigned short c) const
{
    FontLetterDefinition tempDefinition;
    bool validDefinition = _fontAtlas->getLetterDefinitionForChar(c, tempDefinition);
    if (!validDefinition)
        return -1;
    
    return (tempDefinition.offsetX);
}

int Label::getYOffsetForChar(unsigned short c) const
{
    FontLetterDefinition tempDefinition;
    bool validDefinition = _fontAtlas->getLetterDefinitionForChar(c, tempDefinition);
    if (!validDefinition)
        return -1;
    
    return (tempDefinition.offsetY);
}

int Label::getAdvanceForChar(unsigned short c, int hintPositionInString) const
{
    if (_advances)
    {
        // not that advance contains the X offset already
        FontLetterDefinition tempDefinition;
        bool validDefinition = _fontAtlas->getLetterDefinitionForChar(c, tempDefinition);
        if (!validDefinition)
            return -1;
        
        return (_advances[hintPositionInString].width);
    }
    else
    {
        return -1;
    }
}

Rect Label::getRectForChar(unsigned short c) const
{
    return _fontAtlas->getFont()->getRectForChar(c);
}

// string related stuff
int Label::getStringNumLines() const
{
    int quantityOfLines = 1;
    
    unsigned int stringLen = _currentUTF16String ? cc_wcslen(_currentUTF16String) : 0;
    if (stringLen == 0)
        return (-1);
    
    // count number of lines
    for (unsigned int i = 0; i < stringLen - 1; ++i)
    {
        unsigned short c = _currentUTF16String[i];
        if (c == '\n')
        {
            quantityOfLines++;
        }
    }
    
    return quantityOfLines;
}

int Label::getStringLenght() const
{
    return _currentUTF16String ? cc_wcslen(_currentUTF16String) : 0;
}

unsigned short Label::getCharAtStringPosition(int position) const
{
    return _currentUTF16String[position];
}

unsigned short * Label::getUTF8String() const
{
    return _currentUTF16String;
}

void Label::assignNewUTF8String(unsigned short *newString)
{
    setCurrentString(newString);
}

TextHAlignment Label::getTextAlignment() const
{
    return _alignment;
}

// label related stuff
float Label::getMaxLineWidth() const
{
    return _width;
}

bool Label::breakLineWithoutSpace() const
{
    return _lineBreakWithoutSpaces;
}

Size Label::getLabelContentSize() const
{
    return getContentSize();
}

void Label::setLabelContentSize(const Size &newSize)
{
    setContentSize(newSize);
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

void Label::setColor(const Color3B& color)
{
	_reusedLetter->setColor(color);
    SpriteBatchNode::setColor(color);
}

void Label::updateColor()
{
    V3F_C4B_T2F_Quad *quads = _textureAtlas->getQuads();
    auto count = _textureAtlas->getTotalQuads();
    Color4B color4( _displayedColor.r, _displayedColor.g, _displayedColor.b, _displayedOpacity );
    
    // special opacity for premultiplied textures
    if (_isOpacityModifyRGB)
    {
        color4.r *= _displayedOpacity/255.0f;
        color4.g *= _displayedOpacity/255.0f;
        color4.b *= _displayedOpacity/255.0f;
    }
    for (int index=0; index<count; ++index)
    {
        quads[index].bl.colors = color4;
        quads[index].br.colors = color4;
        quads[index].tl.colors = color4;
        quads[index].tr.colors = color4;
        _textureAtlas->updateQuad(&quads[index], index);
    }
}

std::string Label::getDescription() const
{
    return StringUtils::format("<Label | Tag = %d, Label = '%s'>", _tag, cc_utf16_to_utf8(_currentUTF16String,-1,nullptr,nullptr));
}


NS_CC_END
