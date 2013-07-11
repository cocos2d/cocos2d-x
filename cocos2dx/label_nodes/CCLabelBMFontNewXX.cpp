/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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

Use any of these editors to generate BMFonts:
http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
http://www.angelcode.com/products/bmfont/ (Free, Windows only)

****************************************************************************/
#include "CCLabelBMFontNew.h"
#include "cocoa/CCString.h"
#include "platform/platform.h"
#include "cocoa/CCDictionary.h"
#include "CCConfiguration.h"
#include "draw_nodes/CCDrawingPrimitives.h"
#include "sprite_nodes/CCSprite.h"
#include "support/CCPointExtension.h"
#include "platform/CCFileUtils.h"
#include "CCDirector.h"
#include "textures/CCTextureCache.h"
#include "support/ccUTF8.h"

#include "CCLabelTextFormatter.h"

using namespace std;

NS_CC_BEGIN

//
//CCLabelBMFont
//

//LabelBMFont - Purge Cache
void LabelBMFontNew::purgeCachedData()
{
    FNTConfigRemoveCache();
}

LabelBMFontNew * LabelBMFontNew::create()
{
    LabelBMFontNew * pRet = new LabelBMFontNew();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

LabelBMFontNew * LabelBMFontNew::create(const char *str, const char *fntFile, float width, TextAlignment alignment)
{
    return LabelBMFontNew::create(str, fntFile, width, alignment, PointZero);
}

LabelBMFontNew * LabelBMFontNew::create(const char *str, const char *fntFile, float width)
{
    return LabelBMFontNew::create(str, fntFile, width, kTextAlignmentLeft, PointZero);
}

LabelBMFontNew * LabelBMFontNew::create(const char *str, const char *fntFile)
{
    return LabelBMFontNew::create(str, fntFile, kLabelAutomaticWidth, kTextAlignmentLeft, PointZero);
}

//LabelBMFont - Creation & Init
LabelBMFontNew *LabelBMFontNew::create(const char *str, const char *fntFile, float width/* = kCCLabelAutomaticWidth*/, TextAlignment alignment/* = kCCTextAlignmentLeft*/, Point imageOffset/* = CCPointZero*/)
{
    LabelBMFontNew *pRet = new LabelBMFontNew();
    if(pRet && pRet->initWithString(str, fntFile, width, alignment, imageOffset))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool LabelBMFontNew::init()
{
    return initWithString(NULL, NULL, kLabelAutomaticWidth, kTextAlignmentLeft, PointZero);
}

bool LabelBMFontNew::initWithString(const char *theString, const char *fntFile, float width/* = kCCLabelAutomaticWidth*/, TextAlignment alignment/* = kCCTextAlignmentLeft*/, Point imageOffset/* = CCPointZero*/)
{
    CCAssert(!m_pConfiguration, "re-init is no longer supported");
    CCAssert( (theString && fntFile) || (theString==NULL && fntFile==NULL), "Invalid params for LabelBMFontNew");
    
    Texture2D *texture = NULL;
    
    if (fntFile)
    {
        CCBMFontConfiguration *newConf = FNTConfigLoadFile(fntFile);
        if (!newConf)
        {
            CCLOG("cocos2d: WARNING. LabelBMFontNew: Impossible to create font. Please check file: '%s'", fntFile);
            release();
            return false;
        }
        
        newConf->retain();
        CC_SAFE_RELEASE(m_pConfiguration);
        m_pConfiguration = newConf;
        
        m_sFntFile = fntFile;
        
        texture = TextureCache::sharedTextureCache()->addImage(m_pConfiguration->getAtlasName());
    }
    else 
    {
        texture = new Texture2D();
        texture->autorelease();
    }

    if (theString == NULL)
    {
        theString = "";
    }

    if (SpriteBatchNode::initWithTexture(texture, strlen(theString)))
    {
        m_fWidth = width;
        m_pAlignment = alignment;
        
        m_cDisplayedOpacity = m_cRealOpacity = 255;
		m_tDisplayedColor = m_tRealColor = ccWHITE;
        m_bCascadeOpacityEnabled = true;
        m_bCascadeColorEnabled = true;
        
        m_obContentSize = SizeZero;
        
        m_bIsOpacityModifyRGB = m_pobTextureAtlas->getTexture()->hasPremultipliedAlpha();
        m_obAnchorPoint = ccp(0.5f, 0.5f);
        
        m_tImageOffset = imageOffset;
        
        m_pReusedChar = new CCSprite();
        m_pReusedChar->initWithTexture(m_pobTextureAtlas->getTexture(), CCRectMake(0, 0, 0, 0), false);
        m_pReusedChar->setBatchNode(this);
        
        this->setString(theString);
        
        return true;
    }
    return false;
}

LabelBMFontNew::LabelBMFontNew()
:  m_sString(NULL)
, m_pConfiguration(NULL)
, m_bLineBreakWithoutSpaces(false)
, m_tImageOffset(CCPointZero)
, m_cDisplayedOpacity(255)
, m_cRealOpacity(255)
, m_tDisplayedColor(ccWHITE)
, m_tRealColor(ccWHITE)
, m_bCascadeColorEnabled(true)
, m_bCascadeOpacityEnabled(true)
, m_bIsOpacityModifyRGB(false)
{

}

LabelBMFontNew::~LabelBMFontNew()
{
    CC_SAFE_RELEASE(m_pReusedChar);
    CC_SAFE_DELETE(m_sString);
    CC_SAFE_RELEASE(m_pConfiguration);
}

// LabelBMFont - Atlas generation
int LabelBMFontNew::kerningAmountForFirst(unsigned short first, unsigned short second)
{
    int ret = 0;
    unsigned int key = (first<<16) | (second & 0xffff);

    if( m_pConfiguration->m_pKerningDictionary ) {
        tCCKerningHashElement *element = NULL;
        HASH_FIND_INT(m_pConfiguration->m_pKerningDictionary, &key, element);        
        if(element)
            ret = element->amount;
    }
    return ret;
}



//////////////////////////////////////////////////
// carloX all new stuff //////////////////////////
//////////////////////////////////////////////////

int  LabelBMFontNew::getCommonLineHeight()
{
    if (m_pConfiguration)
    {
        return m_pConfiguration->m_nCommonHeight;
    }
    else
    {
        return -1;
    }
}

int  LabelBMFontNew::getKerningForCharsPair(unsigned short first, unsigned short second)
{
    return this->kerningAmountForFirst(first, second);
}

ccBMFontDef LabelBMFontNew::getFontDefForChar(unsigned short int theChar)
{
    ccBMFontDef fontDef;
    tCCFontDefHashElement *element = NULL;
    unsigned int key = theChar;
    
    HASH_FIND_INT(m_pConfiguration->m_pFontDefDictionary, &key, element);
    
    if (element)
    {
        fontDef = element->fontDef;
    }

    return fontDef;
}

// return a sprite for rendering one letter
cocos2d::CCSprite * LabelBMFontNew::getSpriteForChar(unsigned short int theChar, int spriteIndexHint)
{
    
    CCRect      rect;
    ccBMFontDef fontDef;
    CCSprite   *pRetSprite = 0;
    
    // unichar is a short, and an int is needed on HASH_FIND_INT
    tCCFontDefHashElement *element  = NULL;
    unsigned int key                = theChar;
    
    HASH_FIND_INT(m_pConfiguration->m_pFontDefDictionary, &key, element);
    
    if (! element)
    {
        return 0;
    }
    
    
    fontDef = element->fontDef;
    
    rect = fontDef.rect;
    rect = CC_RECT_PIXELS_TO_POINTS(rect);
    
    rect.origin.x += m_tImageOffset.x;
    rect.origin.y += m_tImageOffset.y;
    
    //bool hasSprite  = true;
    pRetSprite      = (CCSprite*)(this->getChildByTag(spriteIndexHint));
    
    if(pRetSprite )
    {
        // Reusing previous Sprite
        pRetSprite->setVisible(true);
    }
    else
    {
        pRetSprite = new CCSprite();
        pRetSprite->initWithTexture(m_pobTextureAtlas->getTexture(), rect);
        addChild(pRetSprite, spriteIndexHint, spriteIndexHint);
        pRetSprite->release();
        
        // Apply label properties
        pRetSprite->setOpacityModifyRGB(m_bIsOpacityModifyRGB);
        
        // Color MUST be set before opacity, since opacity might change color if OpacityModifyRGB is on
        pRetSprite->updateDisplayedColor(m_tDisplayedColor);
        pRetSprite->updateDisplayedOpacity(m_cDisplayedOpacity);
    }
    
    // updating previous sprite
    pRetSprite->setTextureRect(rect, false, rect.size);
    return pRetSprite;
}

int LabelBMFontNew::getStringNumLines()
{
    int quantityOfLines = 1;
    
    unsigned int stringLen = m_sString ? cc_wcslen(m_sString) : 0;
    if (stringLen == 0)
        return (-1);
    
    // count number of lines
    for (unsigned int i = 0; i < stringLen - 1; ++i)
    {
        unsigned short c = m_sString[i];
        if (c == '\n')
        {
            quantityOfLines++;
        }
    }
    
    return quantityOfLines;
}

// need cross implementation
int LabelBMFontNew::getStringLenght()
{
    return m_sString ? cc_wcslen(m_sString) : 0;
}

unsigned short LabelBMFontNew::getCharAtStringPosition(int position)
{
    return m_sString[position];
}

int LabelBMFontNew::getXOffsetForChar(unsigned short c)
{
    ccBMFontDef fontDef = getFontDefForChar(c);
    return fontDef.xOffset;
}

int LabelBMFontNew::getYOffsetForChar(unsigned short c)
{
    ccBMFontDef fontDef = getFontDefForChar(c);
    return fontDef.yOffset;
}

CCRect LabelBMFontNew::getRectForChar(unsigned short c)
{
    ccBMFontDef fontDef = getFontDefForChar(c);
    return fontDef.rect;
}

int LabelBMFontNew::getAdvanceForChar(unsigned short c, int hintPositionInString)
{
    ccBMFontDef fontDef = getFontDefForChar(c);
    return fontDef.xAdvance;
}

void  LabelBMFontNew::setLabelContentSize(const CCSize &newSize)
{
    setContentSize(newSize);
}

void LabelBMFontNew::createStringSprites()
{
    CCLabelTextFormatter::createStringSprites(this);
}

//LabelBMFont - CCLabelProtocol protocol
void LabelBMFontNew::setString(const char *newString)
{
    // update the initial string if needed
    if (strcmp(m_sInitialString.c_str(), newString))
        m_sInitialString = newString;
    
    // do the rest of the josb
    updateLabel();
}

const char* LabelBMFontNew::getString(void)
{
    return m_sInitialString.c_str();
}

void LabelBMFontNew::setCString(const char *label)
{
    setString(label);
}

//LabelBMFont - CCRGBAProtocol protocol
const ccColor3B& LabelBMFontNew::getColor()
{
    return m_tRealColor;
}

const ccColor3B& LabelBMFontNew::getDisplayedColor()
{
    return m_tDisplayedColor;
}

void LabelBMFontNew::setColor(const ccColor3B& color)
{
	m_tDisplayedColor = m_tRealColor = color;
	
	if( m_bCascadeColorEnabled ) {
		ccColor3B parentColor = ccWHITE;
        CCRGBAProtocol* pParent = dynamic_cast<CCRGBAProtocol*>(m_pParent);
        if (pParent && pParent->isCascadeColorEnabled())
        {
            parentColor = pParent->getDisplayedColor();
        }
        this->updateDisplayedColor(parentColor);
	}
}

GLubyte LabelBMFontNew::getOpacity(void)
{
    return m_cRealOpacity;
}

GLubyte LabelBMFontNew::getDisplayedOpacity(void)
{
    return m_cDisplayedOpacity;
}

/** Override synthesized setOpacity to recurse items */
void LabelBMFontNew::setOpacity(GLubyte opacity)
{
	m_cDisplayedOpacity = m_cRealOpacity = opacity;
    
	if( m_bCascadeOpacityEnabled ) {
		GLubyte parentOpacity = 255;
        CCRGBAProtocol* pParent = dynamic_cast<CCRGBAProtocol*>(m_pParent);
        if (pParent && pParent->isCascadeOpacityEnabled())
        {
            parentOpacity = pParent->getDisplayedOpacity();
        }
        this->updateDisplayedOpacity(parentOpacity);
	}
}

void LabelBMFontNew::setOpacityModifyRGB(bool var)
{
    m_bIsOpacityModifyRGB = var;
    if (m_pChildren && m_pChildren->count() != 0)
    {
        CCObject* child;
        CCARRAY_FOREACH(m_pChildren, child)
        {
            CCNode* pNode = (CCNode*) child;
            if (pNode)
            {
                CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(pNode);
                if (pRGBAProtocol)
                {
                    pRGBAProtocol->setOpacityModifyRGB(m_bIsOpacityModifyRGB);
                }
            }
        }
    }
}

bool LabelBMFontNew::isOpacityModifyRGB()
{
    return m_bIsOpacityModifyRGB;
}

void LabelBMFontNew::updateDisplayedOpacity(GLubyte parentOpacity)
{
	m_cDisplayedOpacity = m_cRealOpacity * parentOpacity/255.0;
    
	CCObject* pObj;
	CCARRAY_FOREACH(m_pChildren, pObj)
    {
        CCSprite *item = (CCSprite*)pObj;
		item->updateDisplayedOpacity(m_cDisplayedOpacity);
	}
}

void LabelBMFontNew::updateDisplayedColor(const ccColor3B& parentColor)
{
	m_tDisplayedColor.r = m_tRealColor.r * parentColor.r/255.0;
	m_tDisplayedColor.g = m_tRealColor.g * parentColor.g/255.0;
	m_tDisplayedColor.b = m_tRealColor.b * parentColor.b/255.0;
    
    CCObject* pObj;
	CCARRAY_FOREACH(m_pChildren, pObj)
    {
        CCSprite *item = (CCSprite*)pObj;
		item->updateDisplayedColor(m_tDisplayedColor);
	}
}

bool LabelBMFontNew::isCascadeColorEnabled()
{
    return false;
}

void LabelBMFontNew::setCascadeColorEnabled(bool cascadeColorEnabled)
{
    m_bCascadeColorEnabled = cascadeColorEnabled;
}

bool LabelBMFontNew::isCascadeOpacityEnabled()
{
    return false;
}

void LabelBMFontNew::setCascadeOpacityEnabled(bool cascadeOpacityEnabled)
{
    m_bCascadeOpacityEnabled = cascadeOpacityEnabled;
}

// LabelBMFont - AnchorPoint
void LabelBMFontNew::setAnchorPoint(const CCPoint& point)
{
    if( ! point.equals(m_obAnchorPoint) )
    {
        CCSpriteBatchNode::setAnchorPoint(point);
        updateLabel();
    }
}

// cleaned version !
void LabelBMFontNew::updateLabel()
{
    if ( !m_sInitialString.empty() )
    {
        // set the new string
        CC_SAFE_DELETE_ARRAY(m_sString);
        m_sString = cc_utf8_to_utf16(m_sInitialString.c_str());
        
        // hide all the letters and create or recicle sprites for the new letters
        updateLetterSprites();
        
        // format the text on more than line
        multilineText();
        
        // align the text (left - center - right)
        alignText();
    }
}

CCSprite * LabelBMFontNew::getSpriteChild(int ID)
{
    return (CCSprite*)this->getChildByTag(ID);
}

CCArray*  LabelBMFontNew::getChildrenLetters()
{
    return m_pChildren;
}

unsigned short * LabelBMFontNew::getUTF8String()
{
    return m_sString;
}

void LabelBMFontNew::assignNewUTF8String(unsigned short *newString)
{
    CC_SAFE_DELETE_ARRAY(m_sString);
    m_sString = newString;
}

float LabelBMFontNew::getMaxLineWidth()
{
    return m_fWidth;
}

bool LabelBMFontNew::breakLineWithoutSpace()
{
    return m_bLineBreakWithoutSpaces;
}

cocos2d::CCTextAlignment LabelBMFontNew::getTextAlignment()
{
    return m_pAlignment;
}

cocos2d::CCSize LabelBMFontNew::getLabelContentSize()
{
    return getContentSize();
}

void LabelBMFontNew::multilineText()
{
    if (m_fWidth > 0)
    {
        // format on more than one line
        CCLabelTextFormatter::multilineText(this);
        
        // hide all the letter sprites and create/reclaim letters sprite with new position
        updateLetterSprites();
    }
}

// align the text that's already on more than one line
void LabelBMFontNew::alignText()
{
    if (m_pAlignment != kCCTextAlignmentLeft)
    {
        CCLabelTextFormatter::alignText(this);
    }
}

// hide all the sprites used by this label
void LabelBMFontNew::hideStringSprites()
{
    if (m_pChildren && m_pChildren->count() != 0)
    {
        CCObject* child;
        CCARRAY_FOREACH(m_pChildren, child)
        {
            CCNode* pNode = (CCNode*) child;
            if (pNode)
            {
                pNode->setVisible(false);
            }
        }
    }
}

void LabelBMFontNew::updateLetterSprites()
{
    // hide all the letters
    hideStringSprites();
    
    // create new letters sprites
    createStringSprites();
}

// LabelBMFont - Alignment
void LabelBMFontNew::setAlignment(CCTextAlignment alignment)
{
    this->m_pAlignment = alignment;
    updateLabel();
}

void LabelBMFontNew::setWidth(float width)
{
    this->m_fWidth = width;
    updateLabel();
}

void LabelBMFontNew::setLineBreakWithoutSpace( bool breakWithoutSpace )
{
    m_bLineBreakWithoutSpaces = breakWithoutSpace;
    updateLabel();
}

void LabelBMFontNew::setScale(float scale)
{
    CCSpriteBatchNode::setScale(scale);
    updateLabel();
}

void LabelBMFontNew::setScaleX(float scaleX)
{
    CCSpriteBatchNode::setScaleX(scaleX);
    updateLabel();
}

void LabelBMFontNew::setScaleY(float scaleY)
{
    CCSpriteBatchNode::setScaleY(scaleY);
    updateLabel();
}

float LabelBMFontNew::getLetterPosXLeft( CCSprite* sp )
{
    return sp->getPosition().x * m_fScaleX - (sp->getContentSize().width * m_fScaleX * sp->getAnchorPoint().x);
}

float LabelBMFontNew::getLetterPosXRight( CCSprite* sp )
{
    return sp->getPosition().x * m_fScaleX + (sp->getContentSize().width * m_fScaleX * sp->getAnchorPoint().x);
}

// LabelBMFont - FntFile
void LabelBMFontNew::setFntFile(const char* fntFile)
{
    if (fntFile != NULL && strcmp(fntFile, m_sFntFile.c_str()) != 0 )
    {
        CCBMFontConfiguration *newConf = FNTConfigLoadFile(fntFile);

        CCAssert( newConf, "LabelBMFontNew: Impossible to create font. Please check file");

        m_sFntFile = fntFile;

        CC_SAFE_RETAIN(newConf);
        CC_SAFE_RELEASE(m_pConfiguration);
        m_pConfiguration = newConf;

        this->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_pConfiguration->getAtlasName()));
        this->createStringSprites();
    }
}

const char* LabelBMFontNew::getFntFile()
{
    return m_sFntFile.c_str();
}

//LabelBMFont - Debug draw
#if CC_LABELBMFONT_DEBUG_DRAW
void LabelBMFontNew::draw()
{
    CCSpriteBatchNode::draw();
    const CCSize& s = this->getContentSize();
    CCPoint vertices[4]={
        ccp(0,0),ccp(s.width,0),
        ccp(s.width,s.height),ccp(0,s.height),
    };
    ccDrawPoly(vertices, 4, true);
}
#endif // CC_LABELBMFONT_DEBUG_DRAW

NS_CC_END
