/****************************************************************************
 Copyright (c) 2013      Zynga Inc.

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

NS_CC_BEGIN

Label* Label::createWithTTF( const char* label, const char* fontFilePath, int fontSize, int lineSize, TextHAlignment alignment, GlyphCollection glyphs, const char *customGlyphs )
{
    FontAtlas *tmpAtlas = FontAtlasCache::getFontAtlasTTF(fontFilePath, fontSize, glyphs, customGlyphs);

    if (!tmpAtlas)
        return nullptr;
    
    // create the actual label
    Label* templabel = Label::createWithAtlas(tmpAtlas, alignment, lineSize);
    
    if (templabel)
    {
        templabel->setText(label, lineSize, alignment, false);
        return templabel;
    }
    
    return nullptr;
     
    return 0;
}

Label* Label::createWithBMFont( const char* label, const char* bmfontFilePath, TextHAlignment alignment, int lineSize)
{
    
    FontAtlas *tmpAtlas = FontAtlasCache::getFontAtlasFNT(bmfontFilePath);
    
    if (!tmpAtlas)
        return 0;
    
    Label* templabel = Label::createWithAtlas(tmpAtlas, alignment, lineSize);
    
    if (templabel)
    {
        templabel->setText(label, lineSize, alignment, false);
        return templabel;
    }
    else
    {
        return 0;
    }
     
    return 0;
}

Label* Label::createWithAtlas(FontAtlas *atlas, TextHAlignment alignment, int lineSize)
{
    Label *ret = new Label(atlas, alignment);
    
    if (!ret)
        return 0;
    
    if( ret->init() )
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        delete ret;
        return 0;
    }
    
    return ret;
}

Label::Label(FontAtlas *atlas, TextHAlignment alignment)
: _currentUTF8String(0)
, _originalUTF8String(0)
, _fontAtlas(atlas)
, _alignment(alignment)
, _lineBreakWithoutSpaces(false)
, _advances(0)
, _displayedColor(Color3B::WHITE)
, _realColor(Color3B::WHITE)
, _cascadeColorEnabled(true)
, _cascadeOpacityEnabled(true)
, _displayedOpacity(255)
, _realOpacity(255)
, _isOpacityModifyRGB(false)
{
}

Label::~Label()
{
    CC_SAFE_RELEASE(_spriteArray);
    CC_SAFE_RELEASE(_spriteArrayCache);

    if (_currentUTF8String)
        delete [] _currentUTF8String;
    
    if (_advances)
        delete [] _advances;
    
    if (_fontAtlas)
        FontAtlasCache::releaseFontAtlas(_fontAtlas);
}

bool Label::init()
{
    _spriteArray = Array::createWithCapacity(30);
    _spriteArrayCache = Array::createWithCapacity(30);

    _spriteArray->retain();
    _spriteArrayCache->retain();

    return true;
}

void Label::setString(const char *stringToRender)
{
    setText(stringToRender, _width, TextHAlignment::CENTER, false);
}

bool Label::setText(const char *stringToRender, float lineWidth, TextHAlignment alignment, bool lineBreakWithoutSpaces)
{
    if (!_fontAtlas)
        return false;
    
    // carloX
    // reset the string
    resetCurrentString();
    
    
    _width                  = lineWidth;
    _alignment              = alignment;
    _lineBreakWithoutSpaces = lineBreakWithoutSpaces;
    
    // release all the sprites
    moveAllSpritesToCache();
    
    // store locally common line height
    _commonLineHeight = _fontAtlas->getCommonLineHeight();
    if (_commonLineHeight <= 0)
        return false;
    
    int numLetter = 0;
    unsigned short* utf16String = cc_utf8_to_utf16(stringToRender);
    if(!utf16String)
        return false;
    
    numLetter = cc_wcslen(utf16String);
    SpriteBatchNode::initWithTexture(&_fontAtlas->getTexture(0), numLetter);
    _cascadeColorEnabled = true;
    
    //
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
    Node::setScale(scale);
    alignText();
}

void Label::setScaleX(float scaleX)
{
    Node::setScaleX(scaleX);
    alignText();
}

void Label::setScaleY(float scaleY)
{
    Node::setScaleY(scaleY);
    alignText();
}

void Label::alignText()
{
    hideAllLetters();
    LabelTextFormatter::createStringSprites(this);
    
    if( LabelTextFormatter::multilineText(this) )
    {
        hideAllLetters();
        LabelTextFormatter::createStringSprites(this);
    }
    
    LabelTextFormatter::alignText(this);
}

void Label::hideAllLetters()
{
    Object* Obj = NULL;
    CCARRAY_FOREACH(_spriteArray, Obj)
    {
        ((Sprite *)Obj)->setVisible(false);
    }
    
    CCARRAY_FOREACH(_spriteArrayCache, Obj)
    {
        ((Sprite *)Obj)->setVisible(false);
    }
}

bool Label::computeAdvancesForString(unsigned short int *stringToRender)
{
    if (_advances)
    {
        delete [] _advances;
        _advances = 0;
    }
    
    Font &theFont = _fontAtlas->getFont();
    
    int letterCount = 0;
    _advances = theFont.getAdvancesForTextUTF16(stringToRender, letterCount);
    
    if(!_advances)
        return false;
    else
        return true;
}

bool Label::setOriginalString(unsigned short *stringToSet)
{
    if (_originalUTF8String)
    {
        delete [] _originalUTF8String;
        _originalUTF8String = 0;
    }
    
    int newStringLenght = cc_wcslen(stringToSet);
    _originalUTF8String = new unsigned short int [newStringLenght + 1];
    memset(_originalUTF8String, 0, (newStringLenght + 1) * 2);
    memcpy(_originalUTF8String, stringToSet, (newStringLenght * 2));
    _originalUTF8String[newStringLenght] = 0;
    
    return true;
}

bool Label::setCurrentString(unsigned short *stringToSet)
{
    // set the new string
    if (_currentUTF8String)
    {
        delete [] _currentUTF8String;
        _currentUTF8String = 0;
    }
    //
    _currentUTF8String  = stringToSet;
    // compute the advances
    return computeAdvancesForString(stringToSet);
}

void Label::resetCurrentString()
{
    if ((!_currentUTF8String) && (!_originalUTF8String))
        return;
    
    // set the new string
    if (_currentUTF8String)
    {
        delete [] _currentUTF8String;
        _currentUTF8String = 0;
    }
    
    int stringLenght = cc_wcslen(_originalUTF8String);
    _currentUTF8String = new unsigned short int [stringLenght + 1];
    memcpy(_currentUTF8String, _originalUTF8String, stringLenght * 2);
    _currentUTF8String[stringLenght] = 0;
    
}

Sprite * Label::createNewSpriteFromLetterDefinition(const FontLetterDefinition &theDefinition, Texture2D *theTexture)
{
    Rect uvRect;
    uvRect.size.height = theDefinition.height;
    uvRect.size.width  = theDefinition.width;
    uvRect.origin.x    = theDefinition.U;
    uvRect.origin.y    = theDefinition.V;
    
    SpriteFrame *pFrame = SpriteFrame::createWithTexture(theTexture, uvRect);
    Sprite *tempSprite  = getSprite();
    
    if (!tempSprite)
        return 0;
    
    tempSprite->initWithSpriteFrame(pFrame);
    tempSprite->setAnchorPoint(Point(theDefinition.anchorX, theDefinition.anchorY));
    tempSprite->setBatchNode(this);
    
    // Apply label properties
    tempSprite->setOpacityModifyRGB(_isOpacityModifyRGB);
    
    // Color MUST be set before opacity, since opacity might change color if OpacityModifyRGB is on
    tempSprite->updateDisplayedColor(_displayedColor);
    tempSprite->updateDisplayedOpacity(_displayedOpacity);
    
    
    return tempSprite;
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
            spriteToUpdate->setTexture(theTexture);
            spriteToUpdate->setDisplayFrame(frame);
            spriteToUpdate->setAnchorPoint(Point(theDefinition.anchorX, theDefinition.anchorY));
            spriteToUpdate->setBatchNode(this);
        }
        
        return spriteToUpdate;
    }
}

Sprite * Label::getSpriteForLetter(unsigned short int newLetter)
{
    if (!_fontAtlas)
        return 0;
    
    FontLetterDefinition tempDefinition;
    bool validDefinition = _fontAtlas->getLetterDefinitionForChar(newLetter, tempDefinition);
    if (validDefinition)
    {
        Sprite *newSprite = createNewSpriteFromLetterDefinition(tempDefinition, &_fontAtlas->getTexture(tempDefinition.textureID) );
        this->addChild(newSprite);
        return    newSprite;
    }
    else
    {
        return 0;
    }
}

Sprite * Label::updateSpriteForLetter(Sprite *spriteToUpdate, unsigned short int newLetter)
{
    if (!spriteToUpdate || !_fontAtlas)
        return 0;
    else
    {
        FontLetterDefinition tempDefinition;
        bool validDefinition = _fontAtlas->getLetterDefinitionForChar(newLetter, tempDefinition);
        if (validDefinition)
        {
            Sprite *pNewSprite = updateSpriteWithLetterDefinition(spriteToUpdate, tempDefinition, &_fontAtlas->getTexture(tempDefinition.textureID) );
            return  pNewSprite;
        }
        else
        {
            return 0;
        }
    }
}

void Label::moveAllSpritesToCache()
{
    Object* pObj = NULL;
    CCARRAY_FOREACH(_spriteArray, pObj)
    {
        ((Sprite *)pObj)->removeFromParent();
        _spriteArrayCache->addObject(pObj);
    }
    
    _spriteArray->removeAllObjects();
}

Sprite * Label::getSprite()
{
    if (_spriteArrayCache->count())
    {
        Sprite *retSprite = static_cast<Sprite *>(_spriteArrayCache->getLastObject());
        _spriteArrayCache->removeLastObject();
        return retSprite;
    }
    else
    {
        Sprite *retSprite = new Sprite;
        return retSprite;
    }
}

///// PROTOCOL STUFF

Sprite * Label::getSpriteChild(int ID) const
{
    Object* pObj = NULL;
    CCARRAY_FOREACH(_spriteArray, pObj)
    {
        Sprite *pSprite = (Sprite *)pObj;
        if ( pSprite->getTag() == ID)
        {
            return pSprite;
        }
    }
    return 0;
}

Array* Label::getChildrenLetters() const
{
    return _spriteArray;
}

Sprite * Label::getSpriteForChar(unsigned short int theChar, int spriteIndexHint)
{
    // ret sprite
    Sprite *retSprite =  0;
    
    // look for already existing sprites
    retSprite = getSpriteChild(spriteIndexHint);
    
    if (!retSprite)
    {
        retSprite = getSpriteForLetter(theChar);
        if (!retSprite)
            return 0;
        
        if (retSprite)
            retSprite->setTag(spriteIndexHint);
        
        _spriteArray->addObject(retSprite);
    }
    
    // the sprite is now visible
    retSprite->setVisible(true);
    
    // set the right texture letter to the sprite
    updateSpriteForLetter(retSprite, theChar);
    
    // we are done here
    return retSprite;
}

float Label::getLetterPosXLeft( Sprite* sp ) const
{
    float scaleX = _scaleX;
    return sp->getPosition().x * scaleX - (sp->getContentSize().width * scaleX * sp->getAnchorPoint().x);
}

float Label::getLetterPosXRight( Sprite* sp ) const
{
    float scaleX = _scaleX;
    return sp->getPosition().x * scaleX + (sp->getContentSize().width * scaleX * sp->getAnchorPoint().x);
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
    return _fontAtlas->getFont().getRectForChar(c);
}

// string related stuff
int Label::getStringNumLines() const
{
    int quantityOfLines = 1;
    
    unsigned int stringLen = _currentUTF8String ? cc_wcslen(_currentUTF8String) : 0;
    if (stringLen == 0)
        return (-1);
    
    // count number of lines
    for (unsigned int i = 0; i < stringLen - 1; ++i)
    {
        unsigned short c = _currentUTF8String[i];
        if (c == '\n')
        {
            quantityOfLines++;
        }
    }
    
    return quantityOfLines;
}

int Label::getStringLenght() const
{
    return _currentUTF8String ? cc_wcslen(_currentUTF8String) : 0;
}

unsigned short Label::getCharAtStringPosition(int position) const
{
    return _currentUTF8String[position];
}

unsigned short * Label::getUTF8String() const
{
    return _currentUTF8String;
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
    if (_children && _children->count() != 0)
    {
        Object* child;
        CCARRAY_FOREACH(_children, child)
        {
            Node* pNode = static_cast<Node*>( child );
            if (pNode)
            {
                RGBAProtocol *pRGBAProtocol = dynamic_cast<RGBAProtocol*>(pNode);
                if (pRGBAProtocol)
                {
                    pRGBAProtocol->setOpacityModifyRGB(_isOpacityModifyRGB);
                }
            }
        }
    }
}

unsigned char Label::getOpacity() const
{
     return _realOpacity;
}

unsigned char Label::getDisplayedOpacity() const
{
    return _displayedOpacity;
}

void Label::setOpacity(GLubyte opacity)
{
    _displayedOpacity = _realOpacity = opacity;
    
	if( _cascadeOpacityEnabled ) {
		GLubyte parentOpacity = 255;
        RGBAProtocol* pParent = dynamic_cast<RGBAProtocol*>(_parent);
        if (pParent && pParent->isCascadeOpacityEnabled())
        {
            parentOpacity = pParent->getDisplayedOpacity();
        }
        this->updateDisplayedOpacity(parentOpacity);
	}
}
void Label::updateDisplayedOpacity(GLubyte parentOpacity)
{
    _displayedOpacity = _realOpacity * parentOpacity/255.0;
    
	Object* pObj;
	CCARRAY_FOREACH(_children, pObj)
    {
        Sprite *item = static_cast<Sprite*>( pObj );
		item->updateDisplayedOpacity(_displayedOpacity);
	}
}

bool Label::isCascadeOpacityEnabled() const
{
    return false;
}

void Label::setCascadeOpacityEnabled(bool cascadeOpacityEnabled)
{
    _cascadeOpacityEnabled = cascadeOpacityEnabled;
}

const Color3B& Label::getColor(void) const
{
    return _realColor;
}

const Color3B& Label::getDisplayedColor() const
{
    return _displayedColor;
}

void Label::setColor(const Color3B& color)
{
    _displayedColor = _realColor = color;
	
	if( _cascadeColorEnabled )
    {
		Color3B parentColor = Color3B::WHITE;
        RGBAProtocol* pParent = dynamic_cast<RGBAProtocol*>(_parent);
        
        if (pParent && pParent->isCascadeColorEnabled())
            parentColor = pParent->getDisplayedColor();
        
        updateDisplayedColor(parentColor);
	}
}

void Label::updateDisplayedColor(const Color3B& parentColor)
{
    _displayedColor.r = _realColor.r * parentColor.r/255.0;
	_displayedColor.g = _realColor.g * parentColor.g/255.0;
	_displayedColor.b = _realColor.b * parentColor.b/255.0;
    
    Object* pObj;
	CCARRAY_FOREACH(_children, pObj)
    {
        Sprite *item = static_cast<Sprite*>( pObj );
		item->updateDisplayedColor(_displayedColor);
	}
}

bool Label::isCascadeColorEnabled() const
{
    return false;
}

void Label::setCascadeColorEnabled(bool cascadeColorEnabled)
{
    _cascadeColorEnabled = cascadeColorEnabled;
}


NS_CC_END