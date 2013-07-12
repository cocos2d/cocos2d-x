//
//  CCStringTTF.cpp
//  TestNewStringStuff
//
//  Created by Carlo Morgantini on 4/11/13.
//
//
#include "cocos2d.h"
#include "CCStringTTF.h"
#include "CCFont.h"
#include "CCLabelTextFormatter.h"

NS_CC_BEGIN

StringTTF::StringTTF(LabelFontDefinition *theDef, TextAlignment alignment) : _currentUTF8String(0),
                                                                             _fontDef(theDef),
                                                                             _alignment(alignment),
                                                                             _lineBreakWithoutSpaces(false),
                                                                             _advances(0)
{
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
}

bool StringTTF::setText(char *pStringToRender, float lineWidth, TextAlignment alignment, bool lineBreakWithoutSpaces)
{
    if (!_fontDef)
        return false;
    
    _width = lineWidth;
    
    _alignment              = alignment;
    _lineBreakWithoutSpaces = lineBreakWithoutSpaces;
     
    // release all the sprites
    moveAllSpritesToCache();
    
    // store locally common line height
    _commonLineHeight = _fontDef->getCommonLineHeight();
    if (_commonLineHeight <= 0)
        return false;
    
    Font *pFont = _fontDef->getFont();
    
    if (!pFont)
        return false;
    
    int numLetter = 0;
    unsigned short int *pUTF8Text = pFont->getUTF8Text(pStringToRender, numLetter);
    setCurrentString(pUTF8Text);
    
    // align text
    alignText();
    
    // done here
    return true;
}

void StringTTF::setAlignment(TextAlignment alignment)
{
    // store the new alignment
    if (alignment != _alignment)
    {
        // store
        _alignment = alignment;
    
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
    
}

void StringTTF::setScaleX(float scaleX)
{
    Node::setScaleX(scaleX);
}

void StringTTF::setScaleY(float scaleY)
{
    Node::setScaleY(scaleY);
}

void StringTTF::alignText()
{
    hideAllLetters();
    LabelTextFormatter::createStringSprites(this);
    LabelTextFormatter::multilineText(this);
    hideAllLetters();
    LabelTextFormatter::createStringSprites(this);
    LabelTextFormatter::alignText(this);
}

void StringTTF::hideAllLetters()
{
    Object* pObj = NULL;
    CCARRAY_FOREACH(&_spriteArray, pObj)
    {
        ((Sprite *)pObj)->setVisible(false);
    }
    
    CCARRAY_FOREACH(&_spriteArrayCache, pObj)
    {
        ((Sprite *)pObj)->setVisible(false);
    }
}

bool StringTTF::computeAdvancesForString(const char *stringToRender)
{
    if (_advances)
    {
        delete [] _advances;
        _advances = 0;
    }
    
    Font *pFont = _fontDef->getFont();
    
    if (!pFont)
        return false;
    
    int letterCount = 0;
    _advances = pFont->getAdvancesForText(stringToRender, letterCount);
    
    if(!_advances)
        return false;
    else
        return true;
}

bool StringTTF::computeAdvancesForString(unsigned short int *stringToRender)
{
    if (_advances)
    {
        delete [] _advances;
        _advances = 0;
    }
    
    Font *pFont = _fontDef->getFont();
    
    if (!pFont)
        return false;
    
    int letterCount = 0;
    _advances = pFont->getAdvancesForTextUTF8(stringToRender, letterCount);
    
    if(!_advances)
        return false;
    else
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
    _currentUTF8String = stringToSet;
    
    // compute the advances
    return computeAdvancesForString(stringToSet);
}

Sprite * StringTTF::createNewSpriteFromLetterDefinition(LetterDefinition &theDefinition, Texture2D *theTexture)
{
    Rect uvRect;
    uvRect.size.height = theDefinition.height;
    uvRect.size.width  = theDefinition.width;
    uvRect.origin.x    = theDefinition.U;
    uvRect.origin.y    = theDefinition.V;
    
    SpriteFrame *pFrame = SpriteFrame::createWithTexture(theTexture, uvRect);
    Sprite *tempSprite = getSprite();
    
    if (!tempSprite)
        return 0;
    
    tempSprite->initWithSpriteFrame(pFrame);
    tempSprite->setAnchorPoint(Point(0.0, 1.0));
    
    return tempSprite;
}

Sprite * StringTTF::updateSpriteWithLetterDefinition(Sprite *spriteToUpdate, LetterDefinition &theDefinition, Texture2D *theTexture)
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
        
        SpriteFrame *pFrame = SpriteFrame::createWithTexture(theTexture, uvRect);
        spriteToUpdate->initWithSpriteFrame(pFrame);
        spriteToUpdate->setAnchorPoint(Point(0.0, 1.0));
        
        return spriteToUpdate;
    }
}

Sprite * StringTTF::getSpriteForLetter(unsigned short int newLetter)
{
    LetterDefinition tempDefinition = _fontDef->getLetterDefinition(newLetter);
    Sprite *pNewSprite = createNewSpriteFromLetterDefinition(tempDefinition, _fontDef->getTexture(tempDefinition.textureID) );
    this->addChild(pNewSprite);
    return    pNewSprite;
}

Sprite * StringTTF::updateSpriteForLetter(Sprite *spriteToUpdate, unsigned short int newLetter)
{
    if (!spriteToUpdate)
        return 0;
    else
    {
        LetterDefinition tempDefinition = _fontDef->getLetterDefinition(newLetter);
        Sprite *pNewSprite = updateSpriteWithLetterDefinition(spriteToUpdate, tempDefinition, _fontDef->getTexture(tempDefinition.textureID) );
        return    pNewSprite;
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
    return 0;
}

Array  * StringTTF::getChildrenLetters()
{
    return &_spriteArray;
}

Sprite * StringTTF::getSpriteForChar(unsigned short int theChar, int spriteIndexHint)
{
    // ret sprite 
    Sprite *retSprite =  0;
    
    // lool for already existing sprites
    retSprite = getSpriteChild(spriteIndexHint);
    
    if (!retSprite)
    {
    
        retSprite = getSpriteForLetter(theChar);
        if (!retSprite)
            return 0;
            
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
    float scaleX = 1.0f;
    return sp->getPosition().x * scaleX - (sp->getContentSize().width * scaleX * sp->getAnchorPoint().x);
}

float StringTTF::getLetterPosXRight( Sprite* sp )
{
    float scaleX = 1.0f;
    float retVal = 0;
    retVal = sp->getPosition().x * scaleX + (sp->getContentSize().width * scaleX * sp->getAnchorPoint().x);
    return retVal;
}

int StringTTF::getCommonLineHeight()
{
    return _commonLineHeight * 0.8;
}

int StringTTF::getKerningForCharsPair(unsigned short first, unsigned short second)
{
    return 0;
}

int StringTTF::getXOffsetForChar(unsigned short c)
{
    return 0;
}

int StringTTF::getYOffsetForChar(unsigned short c)
{
    return 0;
}

int StringTTF::getAdvanceForChar(unsigned short c, int hintPositionInString)
{
    if (_advances)
    {
        // not that advance contains the X offset already
        LetterDefinition tempDefinition   = _fontDef->getLetterDefinition(c);
        return (_advances[hintPositionInString].width - tempDefinition.offset);
    }
    else
    {
        return -1;
    }
}

Rect StringTTF::getRectForChar(unsigned short c)
{
    Rect uvRect;
    
    uvRect.origin.x     = 0.0;
    uvRect.origin.y     = 0.0;
    uvRect.size.width   = 0.0;
    uvRect.size.height  = 0.0;
    
    // Not needed for StringTTF
    
    /*
    uvRect.size.height = tempDefinition.height;
    uvRect.size.width  = tempDefinition.width;
    uvRect.origin.x    = tempDefinition.U;
    uvRect.origin.y    = tempDefinition.V;
    */
    
    return uvRect;
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

TextAlignment StringTTF::getTextAlignment()
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

NS_CC_END
