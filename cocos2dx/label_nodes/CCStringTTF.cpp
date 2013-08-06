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

#include "cocos2d.h"
#include "CCStringTTF.h"
#include "CCFont.h"
#include "CCLabelTextFormatter.h"
#include "CCFontAtlasCache.h"

NS_CC_BEGIN

StringTTF::StringTTF(FontAtlas *pAtlas, TextHAlignment alignment):      _currentUTF8String(0),
                                                                        _originalUTF8String(0),
                                                                        _fontAtlas(pAtlas),
                                                                        _alignment(alignment),
                                                                        _lineBreakWithoutSpaces(false),
                                                                        _advances(0),
                                                                        _displayedColor(Color3B::WHITE),
                                                                        _realColor(Color3B::WHITE),
                                                                        _cascadeColorEnabled(true)
{
}

StringTTF* StringTTF::create(FontAtlas *pAtlas, TextHAlignment alignment, int lineSize)
{
    StringTTF *ret = new StringTTF(pAtlas, alignment);
    
    if (!ret)
        return nullptr;
    
    if( ret->init() )
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        delete ret;
        return nullptr;
    }
    
    return ret;
}

StringTTF::~StringTTF()
{
    if (_currentUTF8String)
    {
        delete [] _currentUTF8String;
        _currentUTF8String = 0;
    }
    
    if (_advances)
    {
        delete [] _advances;
        _advances = 0;
    }
    
    if (_fontAtlas)
    {
        FontAtlasCache::releaseFontAtlas(_fontAtlas);
    }
}

bool StringTTF::init()
{
    return true;
}

void StringTTF::setString(const char *stringToRender)
{
    setText(stringToRender, 0, TextHAlignment::CENTER, false);
}

bool StringTTF::setText(const char *stringToRender, float lineWidth, TextHAlignment alignment, bool lineBreakWithoutSpaces)
{
    if (!_fontAtlas)
        return false;
    
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

void StringTTF::setAlignment(TextHAlignment alignment)
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

void StringTTF::setWidth(float width)
{
    if (width != _width)
    {
        // store
        _width = width;
        
        // need to align text again
        alignText();
    }
}

void StringTTF::setLineBreakWithoutSpace(bool breakWithoutSpace)
{
    if (breakWithoutSpace != _lineBreakWithoutSpaces)
    {
        // store
        _lineBreakWithoutSpaces = breakWithoutSpace;
        
        // need to align text again
        alignText();
    }
}

void StringTTF::setScale(float scale)
{
    Node::setScale(scale);
    alignText();
}

void StringTTF::setScaleX(float scaleX)
{
    Node::setScaleX(scaleX);
    alignText();
}

void StringTTF::setScaleY(float scaleY)
{
    Node::setScaleY(scaleY);
    alignText();
}

void StringTTF::alignText()
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

void StringTTF::hideAllLetters()
{
    Object* Obj = NULL;
    CCARRAY_FOREACH(&_spriteArray, Obj)
    {
        ((Sprite *)Obj)->setVisible(false);
    }
    
    CCARRAY_FOREACH(&_spriteArrayCache, Obj)
    {
        ((Sprite *)Obj)->setVisible(false);
    }
}

bool StringTTF::computeAdvancesForString(unsigned short int *stringToRender)
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

bool StringTTF::setOriginalString(unsigned short *stringToSet)
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

bool StringTTF::setCurrentString(unsigned short *stringToSet)
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

void StringTTF::resetCurrentString()
{
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

Sprite * StringTTF::createNewSpriteFromLetterDefinition(FontLetterDefinition &theDefinition, Texture2D *theTexture)
{
    Rect uvRect;
    uvRect.size.height = theDefinition.height;
    uvRect.size.width  = theDefinition.width;
    uvRect.origin.x    = theDefinition.U;
    uvRect.origin.y    = theDefinition.V;
    
    SpriteFrame *pFrame = SpriteFrame::createWithTexture(theTexture, uvRect);
    Sprite *tempSprite  = getSprite();
    
    if (!tempSprite)
        return nullptr;
    
    tempSprite->initWithSpriteFrame(pFrame);
    tempSprite->setAnchorPoint(Point(theDefinition.anchorX, theDefinition.anchorY));
    tempSprite->setBatchNode(this);
    
    return tempSprite;
}

Sprite * StringTTF::updateSpriteWithLetterDefinition(Sprite *spriteToUpdate, FontLetterDefinition &theDefinition, Texture2D *theTexture)
{
    if (!spriteToUpdate)
    {
        return nullptr;
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

Sprite * StringTTF::getSpriteForLetter(unsigned short int newLetter)
{
    if (!_fontAtlas)
        return nullptr;
    
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
        return nullptr;
    }
}

Sprite * StringTTF::updateSpriteForLetter(Sprite *spriteToUpdate, unsigned short int newLetter)
{
    if (!spriteToUpdate || !_fontAtlas)
        return nullptr;
    
    FontLetterDefinition tempDefinition;
    bool validDefinition = _fontAtlas->getLetterDefinitionForChar(newLetter, tempDefinition);
    if (validDefinition)
    {
        Sprite *pNewSprite = updateSpriteWithLetterDefinition(spriteToUpdate, tempDefinition, &_fontAtlas->getTexture(tempDefinition.textureID) );
        return  pNewSprite;
    }
    else
    {
        return nullptr;
    }
    
}

void StringTTF::moveAllSpritesToCache()
{
    Object* pObj = NULL;
    CCARRAY_FOREACH(&_spriteArray, pObj)
    {
        ((Sprite *)pObj)->removeFromParent();
        _spriteArrayCache.addObject(pObj);
    }
    
    _spriteArray.removeAllObjects();
}

Sprite * StringTTF::getSprite()
{
    if (_spriteArrayCache.count())
    {
        Sprite *retSprite = (Sprite *) _spriteArrayCache.lastObject();
        _spriteArrayCache.removeLastObject();
        return retSprite;
    }
    else
    {
        Sprite *retSprite = new Sprite;
        return retSprite;
    }
}

///// PROTOCOL STUFF

Sprite * StringTTF::getSpriteChild(int ID)
{
    Object* pObj = NULL;
    CCARRAY_FOREACH(&_spriteArray, pObj)
    {
        Sprite *pSprite = (Sprite *)pObj;
        if ( pSprite->getTag() == ID)
        {
            return pSprite;
        }
    }
    return nullptr;
}

Array  * StringTTF::getChildrenLetters()
{
    return &_spriteArray;
}

Sprite * StringTTF::getSpriteForChar(unsigned short int theChar, int spriteIndexHint)
{
    // ret sprite 
    Sprite *retSprite =  0;
    
    // look for already existing sprites
    retSprite = getSpriteChild(spriteIndexHint);
        
    if (!retSprite)
    {
        retSprite = getSpriteForLetter(theChar);
        if (!retSprite)
            return nullptr;
        
        if (retSprite)
            retSprite->setTag(spriteIndexHint);
        
        _spriteArray.addObject(retSprite);
    }
        
    // the sprite is now visible
    retSprite->setVisible(true);
        
    // set the right texture letter to the sprite
    updateSpriteForLetter(retSprite, theChar);
    
    // we are done here
    return retSprite;
}

float StringTTF::getLetterPosXLeft( Sprite* sp )
{
    float scaleX = _scaleX;
    return sp->getPosition().x * scaleX - (sp->getContentSize().width * scaleX * sp->getAnchorPoint().x);
}

float StringTTF::getLetterPosXRight( Sprite* sp )
{
    float scaleX = _scaleX;
    return sp->getPosition().x * scaleX + (sp->getContentSize().width * scaleX * sp->getAnchorPoint().x);
}

int StringTTF::getCommonLineHeight()
{
    return _commonLineHeight;
}

int StringTTF::getKerningForCharsPair(unsigned short first, unsigned short second)
{
    return 0;
}

int StringTTF::getXOffsetForChar(unsigned short c)
{
    FontLetterDefinition tempDefinition;
    bool validDefinition = _fontAtlas->getLetterDefinitionForChar(c, tempDefinition);
    if (!validDefinition)
        return -1;
    
    return (tempDefinition.offsetX);
}

int StringTTF::getYOffsetForChar(unsigned short c)
{
    FontLetterDefinition tempDefinition;
    bool validDefinition = _fontAtlas->getLetterDefinitionForChar(c, tempDefinition);
    if (!validDefinition)
        return -1;
    
    return (tempDefinition.offsetY);
}

int StringTTF::getAdvanceForChar(unsigned short c, int hintPositionInString)
{
    if (_advances)
    {
        // not that advance contains the X offset already
        FontLetterDefinition tempDefinition;
        bool validDefinition = _fontAtlas->getLetterDefinitionForChar(c, tempDefinition);
        if (!validDefinition)
            return -1;
        
        return (_advances[hintPositionInString].width - tempDefinition.offsetX);
    }
    else
    {
        return -1;
    }
}

Rect StringTTF::getRectForChar(unsigned short c)
{
    return _fontAtlas->getFont().getRectForChar(c);
}

// string related stuff
int StringTTF::getStringNumLines()
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

int StringTTF::getStringLenght()
{
    return _currentUTF8String ? cc_wcslen(_currentUTF8String) : 0;
}

unsigned short StringTTF::getCharAtStringPosition(int position)
{
   return _currentUTF8String[position];
}

unsigned short * StringTTF::getUTF8String()
{
    return _currentUTF8String;
}

void StringTTF::assignNewUTF8String(unsigned short *newString)
{
    setCurrentString(newString);
}

TextHAlignment StringTTF::getTextAlignment()
{
    return _alignment;
}

// label related stuff
float StringTTF::getMaxLineWidth()
{
    return _width;
}

bool StringTTF::breakLineWithoutSpace()
{
    return _lineBreakWithoutSpaces;
}

Size StringTTF::getLabelContentSize()
{
    return getContentSize();
}

void StringTTF::setLabelContentSize(const Size &newSize)
{
    setContentSize(newSize);
}


// RGBA protocol


bool StringTTF::isOpacityModifyRGB() const
{
    return false;
}

void StringTTF::setOpacityModifyRGB(bool isOpacityModifyRGB)
{
}

unsigned char StringTTF::getOpacity() const
{
    return 0;
}

unsigned char StringTTF::getDisplayedOpacity() const
{
    return 0;
}

void StringTTF::setOpacity(GLubyte opacity)
{
}
void StringTTF::updateDisplayedOpacity(GLubyte parentOpacity)
{
}

bool StringTTF::isCascadeOpacityEnabled() const
{
    return false;
}

void StringTTF::setCascadeOpacityEnabled(bool cascadeOpacityEnabled)
{
}

const Color3B& StringTTF::getColor(void) const
{
    return _realColor;
}

const Color3B& StringTTF::getDisplayedColor() const
{
    return _displayedColor;
}

void StringTTF::setColor(const Color3B& color)
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

void StringTTF::updateDisplayedColor(const Color3B& parentColor)
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

bool StringTTF::isCascadeColorEnabled() const
{
    return false;
}

void StringTTF::setCascadeColorEnabled(bool cascadeColorEnabled)
{
    _cascadeColorEnabled = cascadeColorEnabled;
}

NS_CC_END
