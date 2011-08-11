/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
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
#include "CCLabelBMFont.h"

#include "platform/platform.h"
#include "CCMutableDictionary.h"
#include "CCConfiguration.h"
#include "CCDrawingPrimitives.h"
#include "CCSprite.h"
#include "CCPointExtension.h"

#include "CCFileUtils.h"
#include "support/data_support/uthash.h"

namespace cocos2d{
	
	//
	//FNTConfig Cache - free functions
	//
	CCMutableDictionary<std::string, CCBMFontConfiguration*> *configurations = NULL;
	CCBMFontConfiguration* FNTConfigLoadFile( const char *fntFile)
	{
		CCBMFontConfiguration *pRet = NULL;

		if( configurations == NULL )
		{
			configurations = new CCMutableDictionary<std::string, CCBMFontConfiguration*>();
		}
		std::string key(fntFile);
		pRet = configurations->objectForKey(key);
		if( pRet == NULL )
		{
			pRet = CCBMFontConfiguration::configurationWithFNTFile(fntFile);
			configurations->setObject(pRet, key);
		}

		return pRet;
	}

	void FNTConfigRemoveCache( void )
	{
		if (configurations)
		{
			configurations->removeAllObjects();
            CC_SAFE_RELEASE_NULL(configurations);
		}
	}
	//
	//Hash Element
	//
	// Equal function for targetSet.
	typedef struct _KerningHashElement
	{	
		int				key;		// key for the hash. 16-bit for 1st element, 16-bit for 2nd element
		int				amount;
		UT_hash_handle	hh;
	} tKerningHashElement;
	//
	//BitmapFontConfiguration
	//

	CCBMFontConfiguration * CCBMFontConfiguration::configurationWithFNTFile(const char *FNTfile)
	{
		CCBMFontConfiguration * pRet = new CCBMFontConfiguration();
		if (pRet->initWithFNTfile(FNTfile))
		{
			pRet->autorelease();
			return pRet;
		}
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
	bool CCBMFontConfiguration::initWithFNTfile(const char *FNTfile)
	{
		assert(FNTfile != NULL && strlen(FNTfile)!=0);
		m_pKerningDictionary = NULL;
		this->parseConfigFile(FNTfile);
		return true;
	}
	CCBMFontConfiguration::~CCBMFontConfiguration()
	{
		CCLOGINFO( "cocos2d: deallocing CCBMFontConfiguration" );
		this->purgeKerningDictionary();
		m_sAtlasName.clear();
	}
	char * CCBMFontConfiguration::description(void)
	{
		char *ret = new char[100];
		sprintf(ret, "<CCBMFontConfiguration | Kernings:%d | Image = %s>", HASH_COUNT(m_pKerningDictionary), m_sAtlasName.c_str());
		return ret;
	}
	void CCBMFontConfiguration::purgeKerningDictionary()
	{
		tKerningHashElement *current;
		while(m_pKerningDictionary) 
		{
			current = m_pKerningDictionary; 
			HASH_DEL(m_pKerningDictionary,current);
			free(current);
		}
	}
	void CCBMFontConfiguration::parseConfigFile(const char *controlFile)
	{	
		std::string fullpath = CCFileUtils::fullPathFromRelativePath(controlFile);

        CCFileData data(fullpath.c_str(), "rb");
        unsigned long nBufSize = data.getSize();
        char* pBuffer = (char*) data.getBuffer();

        CCAssert(pBuffer, "CCBMFontConfiguration::parseConfigFile | Open file error.");

        if (!pBuffer)
        {
            return;
        }

        // parse spacing / padding
        std::string line;
        std::string strLeft(pBuffer, nBufSize);
        while (strLeft.length() > 0)        {
            int pos = strLeft.find('\n');

            if (pos != (int)std::string::npos)
            {
                // the data is more than a line.get one line
                line = strLeft.substr(0, pos);
                strLeft = strLeft.substr(pos + 1);
            }
            else
            {
                // get the left data
                line = strLeft;
                strLeft.erase();
            }

            if(line.substr(0,strlen("info face")) == "info face") 
            {
                // XXX: info parsing is incomplete
                // Not needed for the Hiero editors, but needed for the AngelCode editor
                //			[self parseInfoArguments:line];
                this->parseInfoArguments(line);
            }
            // Check to see if the start of the line is something we are interested in
            else if(line.substr(0,strlen("common lineHeight")) == "common lineHeight")
            {
                this->parseCommonArguments(line);
            }
            else if(line.substr(0,strlen("page id")) == "page id")
            {
                this->parseImageFileName(line, controlFile);
            }
            else if(line.substr(0,strlen("chars c")) == "chars c")
            {
                // Ignore this line
            }
            else if(line.substr(0,strlen("char")) == "char")
            {
                // Parse the current line and create a new CharDef
                ccBMFontDef characterDefinition;
                this->parseCharacterDefinition(line, &characterDefinition);

                // Add the CharDef returned to the charArray
                m_pBitmapFontArray[ characterDefinition.charID ] = characterDefinition;
            }
            else if(line.substr(0,strlen("kernings count")) == "kernings count")
            {
                this->parseKerningCapacity(line);
            }
            else if(line.substr(0,strlen("kerning first")) == "kerning first")
            {
                this->parseKerningEntry(line);
            }
        }
	}
	void CCBMFontConfiguration::parseImageFileName(std::string line, const char *fntFile)
	{
		//////////////////////////////////////////////////////////////////////////
		// line to parse:
		// page id=0 file="bitmapFontTest.png"
		//////////////////////////////////////////////////////////////////////////

		// page ID. Sanity check
		int index = line.find('=')+1;
		int index2 = line.find(' ', index);
		std::string value = line.substr(index, index2-index);
		CCAssert(atoi(value.c_str()) == 0, "LabelBMFont file could not be found");
		// file 
		index = line.find('"')+1;
		index2 = line.find('"', index);
		value = line.substr(index, index2-index);

		m_sAtlasName = CCFileUtils::fullPathFromRelativeFile(value.c_str(), fntFile);
	}
	void CCBMFontConfiguration::parseInfoArguments(std::string line)
	{
		//////////////////////////////////////////////////////////////////////////
		// possible lines to parse:
		// info face="Script" size=32 bold=0 italic=0 charset="" unicode=1 stretchH=100 smooth=1 aa=1 padding=1,4,3,2 spacing=0,0 outline=0
		// info face="Cracked" size=36 bold=0 italic=0 charset="" unicode=0 stretchH=100 smooth=1 aa=1 padding=0,0,0,0 spacing=1,1
		//////////////////////////////////////////////////////////////////////////

		// padding
		int index = line.find("padding=");
		int index2 = line.find(' ', index);
		std::string value = line.substr(index, index2-index);
		sscanf(value.c_str(), "padding=%d,%d,%d,%d", &m_tPadding.top, &m_tPadding.right, &m_tPadding.bottom, &m_tPadding.left);
		CCLOG("cocos2d: padding: %d,%d,%d,%d", m_tPadding.left, m_tPadding.top, m_tPadding.right, m_tPadding.bottom);
	}
	void CCBMFontConfiguration::parseCommonArguments(std::string line)
	{
		//////////////////////////////////////////////////////////////////////////
		// line to parse:
		// common lineHeight=104 base=26 scaleW=1024 scaleH=512 pages=1 packed=0
		//////////////////////////////////////////////////////////////////////////
		
		// Height
		int index = line.find("lineHeight=");
		int index2 = line.find(' ', index);
		std::string value = line.substr(index, index2-index);
		sscanf(value.c_str(), "lineHeight=%u", &m_uCommonHeight);
		// scaleW. sanity check
		index = line.find("scaleW=") + strlen("scaleW=");
		index2 = line.find(' ', index);
		value = line.substr(index, index2-index);
		CCAssert(atoi(value.c_str()) <= CCConfiguration::sharedConfiguration()->getMaxTextureSize(), "CCLabelBMFont: page can't be larger than supported");
		// scaleH. sanity check
		index = line.find("scaleH=") + strlen("scaleH=");
		index2 = line.find(' ', index);
		value = line.substr(index, index2-index);
		CCAssert(atoi(value.c_str()) <= CCConfiguration::sharedConfiguration()->getMaxTextureSize(), "CCLabelBMFont: page can't be larger than supported");
		// pages. sanity check
		index = line.find("pages=") + strlen("pages=");
		index2 = line.find(' ', index);
		value = line.substr(index, index2-index);
		CCAssert(atoi(value.c_str()) == 1, "CCBitfontAtlas: only supports 1 page");

		// packed (ignore) What does this mean ??
	}
	void CCBMFontConfiguration::parseCharacterDefinition(std::string line, ccBMFontDef *characterDefinition)
	{	
		//////////////////////////////////////////////////////////////////////////
		// line to parse:
		// char id=32   x=0     y=0     width=0     height=0     xoffset=0     yoffset=44    xadvance=14     page=0  chnl=0 
		//////////////////////////////////////////////////////////////////////////

		// Character ID
		int index = line.find("id=");
		int index2 = line.find(' ', index);
		std::string value = line.substr(index, index2-index);
		sscanf(value.c_str(), "id=%u", &characterDefinition->charID);
		CCAssert(characterDefinition->charID < kCCBMFontMaxChars, "BitmpaFontAtlas: CharID bigger than supported");
		// Character x
		index = line.find("x=");
		index2 = line.find(' ', index);
		value = line.substr(index, index2-index);
		sscanf(value.c_str(), "x=%f", &characterDefinition->rect.origin.x);
		// Character y
		index = line.find("y=");
		index2 = line.find(' ', index);
		value = line.substr(index, index2-index);
		sscanf(value.c_str(), "y=%f", &characterDefinition->rect.origin.y);
		// Character width
		index = line.find("width=");
		index2 = line.find(' ', index);
		value = line.substr(index, index2-index);
		sscanf(value.c_str(), "width=%f", &characterDefinition->rect.size.width);
		// Character height
		index = line.find("height=");
		index2 = line.find(' ', index);
		value = line.substr(index, index2-index);
		sscanf(value.c_str(), "height=%f", &characterDefinition->rect.size.height);
		// Character xoffset
		index = line.find("xoffset=");
		index2 = line.find(' ', index);
		value = line.substr(index, index2-index);
		sscanf(value.c_str(), "xoffset=%d", &characterDefinition->xOffset);
		// Character yoffset
		index = line.find("yoffset=");
		index2 = line.find(' ', index);
		value = line.substr(index, index2-index);
		sscanf(value.c_str(), "yoffset=%d", &characterDefinition->yOffset);
		// Character xadvance
		index = line.find("xadvance=");
		index2 = line.find(' ', index);
		value = line.substr(index, index2-index);
		sscanf(value.c_str(), "xadvance=%d", &characterDefinition->xAdvance);
	}
	void CCBMFontConfiguration::parseKerningCapacity(std::string line)
	{
		// When using uthash there is not need to parse the capacity.

		//	CCAssert(!kerningDictionary, @"dictionary already initialized");
		//	
		//	// Break the values for this line up using =
		//	CCMutableArray *values = [line componentsSeparatedByString:@"="];
		//	NSEnumerator *nse = [values objectEnumerator];	
		//	CCString *propertyValue;
		//	
		//	// We need to move past the first entry in the array before we start assigning values
		//	[nse nextObject];
		//	
		//	// count
		//	propertyValue = [nse nextObject];
		//	int capacity = [propertyValue intValue];
		//	
		//	if( capacity != -1 )
		//		kerningDictionary = ccHashSetNew(capacity, targetSetEql);
	}
	void CCBMFontConfiguration::parseKerningEntry(std::string line)
	{		
		//////////////////////////////////////////////////////////////////////////
		// line to parse:
		// kerning first=121  second=44  amount=-7
		//////////////////////////////////////////////////////////////////////////

		// first
		int first;
		int index = line.find("first=");
		int index2 = line.find(' ', index);
		std::string value = line.substr(index, index2-index);
		sscanf(value.c_str(), "first=%d", &first);

		// second
		int second;
		index = line.find("second=");
		index2 = line.find(' ', index);
		value = line.substr(index, index2-index);
		sscanf(value.c_str(), "second=%d", &second);

		// amount
		int amount;
		index = line.find("amount=");
		index2 = line.find(' ', index);
		value = line.substr(index, index2-index);
		sscanf(value.c_str(), "amount=%d", &amount);

		tKerningHashElement *element = (tKerningHashElement *)calloc( sizeof( *element ), 1 );
		element->amount = amount;
		element->key = (first<<16) | (second&0xffff);
		HASH_ADD_INT(m_pKerningDictionary,key, element);
	}
	//
	//CCLabelBMFont
	//

	//LabelBMFont - Purge Cache
	void CCLabelBMFont::purgeCachedData()
	{
		FNTConfigRemoveCache();
	}

	//LabelBMFont - Creation & Init
	CCLabelBMFont *CCLabelBMFont::labelWithString(const char *str, const char *fntFile)
	{
		CCLabelBMFont *pRet = new CCLabelBMFont();
		if(pRet && pRet->initWithString(str, fntFile))
		{
			pRet->autorelease();
			return pRet;
		}
		CC_SAFE_DELETE(pRet)
		return NULL;
	}

	bool CCLabelBMFont::initWithString(const char *theString, const char *fntFile)
	{	
		assert(theString != NULL);
		CC_SAFE_RELEASE(m_pConfiguration);// allow re-init
		m_pConfiguration = FNTConfigLoadFile(fntFile);
		m_pConfiguration->retain();
		CCAssert( m_pConfiguration, "Error creating config for LabelBMFont");

		if (CCSpriteBatchNode::initWithFile(m_pConfiguration->m_sAtlasName.c_str(), strlen(theString)))
		{
			m_cOpacity = 255;
			m_tColor = ccWHITE;
			m_tContentSize = CCSizeZero;
			m_bIsOpacityModifyRGB = m_pobTextureAtlas->getTexture()->getHasPremultipliedAlpha();
			setAnchorPoint(ccp(0.5f, 0.5f));
			this->setString(theString);
			return true;
		}
		return false;
	}
	CCLabelBMFont::~CCLabelBMFont()
	{
		m_sString.clear();
		CC_SAFE_RELEASE(m_pConfiguration);
	}

	// LabelBMFont - Atlas generation
	int CCLabelBMFont::kerningAmountForFirst(unsigned short first, unsigned short second)
	{
		int ret = 0;
		unsigned int key = (first<<16) | (second & 0xffff);

		if( m_pConfiguration->m_pKerningDictionary ) {
			tKerningHashElement *element = NULL;
			HASH_FIND_INT(m_pConfiguration->m_pKerningDictionary, &key, element);		
			if(element)
				ret = element->amount;
		}
		return ret;
	}
	void CCLabelBMFont::createFontChars()
	{
		int nextFontPositionX = 0;
        int nextFontPositionY = 0;
		unsigned short prev = -1;
		int kerningAmount = 0;

		CCSize tmpSize = CCSizeZero;

        int longestLine = 0;
        unsigned int totalHeight = 0;

        unsigned int quantityOfLines = 1;

		unsigned int stringLen = m_sString.length();

        if (0 == stringLen)
        {
            return;
        }

        for (unsigned int i = 0; i < stringLen - 1; ++i)
        {
            unsigned short c = m_sString[i];
            if (c == '\n')
            {
                quantityOfLines++;
            }
        }

        totalHeight = m_pConfiguration->m_uCommonHeight * quantityOfLines;
        nextFontPositionY = -(m_pConfiguration->m_uCommonHeight - m_pConfiguration->m_uCommonHeight * quantityOfLines);

		for (unsigned int i= 0; i < stringLen; i++)
		{
			unsigned short c = m_sString[i];
			CCAssert( c < kCCBMFontMaxChars, "LabelBMFont: character outside bounds");

            if (c == '\n')
            {
                nextFontPositionX = 0;
                nextFontPositionY -= m_pConfiguration->m_uCommonHeight;
                continue;
            }
            
			kerningAmount = this->kerningAmountForFirst(prev, c);

			const ccBMFontDef& fontDef = m_pConfiguration->m_pBitmapFontArray[c];

			CCRect rect = fontDef.rect;

			CCSprite *fontChar;

			fontChar = (CCSprite*)(this->getChildByTag(i));
			if( ! fontChar )
			{
				fontChar = new CCSprite();
				fontChar->initWithBatchNodeRectInPixels(this, rect);
				this->addChild(fontChar, 0, i);
				fontChar->release();
			}
			else
			{
				// reusing fonts
				fontChar->setTextureRectInPixels(rect, false, rect.size);

				// restore to default in case they were modified
				fontChar->setIsVisible(true);
				fontChar->setOpacity(255);
			}

            float yOffset = (float) (m_pConfiguration->m_uCommonHeight - fontDef.yOffset);
			fontChar->setPositionInPixels( ccp( nextFontPositionX + fontDef.xOffset + fontDef.rect.size.width / 2.0f + kerningAmount,
				                                (float) nextFontPositionY + yOffset - rect.size.height/2.0f ) );		

			//		NSLog(@"position.y: %f", fontChar.position.y);

			// update kerning
			nextFontPositionX += m_pConfiguration->m_pBitmapFontArray[c].xAdvance + kerningAmount;
			prev = c;

			// Apply label properties
			fontChar->setIsOpacityModifyRGB(m_bIsOpacityModifyRGB);
			// Color MUST be set before opacity, since opacity might change color if OpacityModifyRGB is on
			fontChar->setColor(m_tColor);

			// only apply opaccity if it is different than 255 )
			// to prevent modifying the color too (issue #610)
			if( m_cOpacity != 255 )
			{
				fontChar->setOpacity(m_cOpacity);
			}

            if (longestLine < nextFontPositionX)
            {
                longestLine = nextFontPositionX;
            }
		}

        tmpSize.width  = (float) longestLine;
        tmpSize.height = (float) totalHeight;

		this->setContentSizeInPixels(tmpSize);
	}

	//LabelBMFont - CCLabelProtocol protocol
	void CCLabelBMFont::setString(const char *newString)
	{	
		m_sString.clear();
		m_sString = newString;

		if (m_pChildren && m_pChildren->count() != 0)
		{
            CCObject* child;
            CCARRAY_FOREACH(m_pChildren, child)
            {
                CCNode* pNode = (CCNode*) child;
                if (pNode)
                {
                    pNode->setIsVisible(false);
                }
            }		}
		this->createFontChars();
	}

	const char* CCLabelBMFont::getString(void)
	{
		return m_sString.c_str();
	}

    void CCLabelBMFont::setCString(const char *label)
    {
        setString(label);
    }

	//LabelBMFont - CCRGBAProtocol protocol
	void CCLabelBMFont::setColor(ccColor3B var)
	{
		m_tColor = var;
		if (m_pChildren && m_pChildren->count() != 0)
		{
            CCObject* child;
            CCARRAY_FOREACH(m_pChildren, child)
            {
                CCSprite* pNode = (CCSprite*) child;
                if (pNode)
                {
                    pNode->setColor(m_tColor);
                }
            }		}
	}
	ccColor3B CCLabelBMFont::getColor()
	{
		return m_tColor;
	}
	void CCLabelBMFont::setOpacity(GLubyte var)
	{
		m_cOpacity = var;

		if (m_pChildren && m_pChildren->count() != 0)
		{
            CCObject* child;
            CCARRAY_FOREACH(m_pChildren, child)
            {
                CCNode* pNode = (CCNode*) child;
                if (pNode)
                {
                    CCRGBAProtocol *pRGBAProtocol = pNode->convertToRGBAProtocol();
                    if (pRGBAProtocol)
                    {
                        pRGBAProtocol->setOpacity(m_cOpacity);
                    }
                }
            }		}
	}
	GLubyte CCLabelBMFont::getOpacity()
	{
		return m_cOpacity;
	}
	void CCLabelBMFont::setIsOpacityModifyRGB(bool var)
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
                    CCRGBAProtocol *pRGBAProtocol = pNode->convertToRGBAProtocol();
                    if (pRGBAProtocol)
                    {
                        pRGBAProtocol->setIsOpacityModifyRGB(m_bIsOpacityModifyRGB);
                    }
                }
            }		}
	}
	bool CCLabelBMFont::getIsOpacityModifyRGB()
	{
		return m_bIsOpacityModifyRGB;
	}

	// LabelBMFont - AnchorPoint
	void CCLabelBMFont::setAnchorPoint(CCPoint point)
	{
		if( ! CCPoint::CCPointEqualToPoint(point, m_tAnchorPoint) )
		{
			CCSpriteBatchNode::setAnchorPoint(point);
			this->createFontChars();
		}
	}

	//LabelBMFont - Debug draw
#if CC_LABELBMFONT_DEBUG_DRAW
	void CCLabelBMFont::draw()
	{
		CCSpriteBatchNode::draw();
		CCSize s = this->getContentSize();
		CCPoint vertices[4]={
			ccp(0,0),ccp(s.width,0),
			ccp(s.width,s.height),ccp(0,s.height),
		};
		ccDrawPoly(vertices, 4, true);
	}
#endif // CC_LABELBMFONT_DEBUG_DRAW

}
