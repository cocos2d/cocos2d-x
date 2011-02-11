/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#include "CCLabelBMFont.h"

#include "platform/platform.h"
#include "NSMutableDictionary.h"
#include "CCConfiguration.h"
#include "CCDrawingPrimitives.h"
#include "CCSprite.h"
#include "CGPointExtension.h"

#include "support/file_support/FileData.h"
#include "support/data_support/uthash.h"

namespace cocos2d{
	
	//
	//FNTConfig Cache - free functions
	//
	NSMutableDictionary<std::string, CCBMFontConfiguration*> *configurations = NULL;
	CCBMFontConfiguration* FNTConfigLoadFile( const char *fntFile)
	{
		CCBMFontConfiguration *pRet = NULL;

		if( configurations == NULL )
		{
			configurations = new NSMutableDictionary<std::string, CCBMFontConfiguration*>();
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
            CCX_SAFE_RELEASE_NULL(configurations);
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
		CCX_SAFE_DELETE(pRet);
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

        FileData data;
        unsigned long nBufSize = 0;
        char* pBuffer = (char*) data.getFileData(fullpath.c_str(), "r", &nBufSize);

        NSAssert(pBuffer, "CCBMFontConfiguration::parseConfigFile | Open file error.");

        if (!pBuffer)
        {
            return;
        }

        // parse spacing / padding
        std::string line;
        std::string strLeft(pBuffer, nBufSize);
        while (strLeft.length() > 0)        {
            int pos = strLeft.find('\n');

            if (pos != std::string::npos)
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
		NSAssert(atoi(value.c_str()) == 0, "BitmapFontAtlas file could not be found");
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
		NSAssert(atoi(value.c_str()) <= CCConfiguration::sharedConfiguration()->getMaxTextureSize(), "CCLabelBMFont: page can't be larger than supported");
		// scaleH. sanity check
		index = line.find("scaleH=") + strlen("scaleH=");
		index2 = line.find(' ', index);
		value = line.substr(index, index2-index);
		NSAssert(atoi(value.c_str()) <= CCConfiguration::sharedConfiguration()->getMaxTextureSize(), "CCLabelBMFont: page can't be larger than supported");
		// pages. sanity check
		index = line.find("pages=") + strlen("pages=");
		index2 = line.find(' ', index);
		value = line.substr(index, index2-index);
		NSAssert(atoi(value.c_str()) == 1, "CCBitfontAtlas: only supports 1 page");

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
		NSAssert(characterDefinition->charID < kCCBMFontMaxChars, "BitmpaFontAtlas: CharID bigger than supported");
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

		//	NSAssert(!kerningDictionary, @"dictionary already initialized");
		//	
		//	// Break the values for this line up using =
		//	NSArray *values = [line componentsSeparatedByString:@"="];
		//	NSEnumerator *nse = [values objectEnumerator];	
		//	NSString *propertyValue;
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

	//BitmapFontAtlas - Purge Cache
	void CCLabelBMFont::purgeCachedData()
	{
		FNTConfigRemoveCache();
	}

	//BitmapFontAtlas - Creation & Init
	CCLabelBMFont *CCLabelBMFont::labelWithString(const char *str, const char *fntFile)
	{
		CCLabelBMFont *pRet = new CCLabelBMFont();
		if(pRet && pRet->initWithString(str, fntFile))
		{
			pRet->autorelease();
			return pRet;
		}
		CCX_SAFE_DELETE(pRet)
		return NULL;
	}

    CCLabelBMFont * CCLabelBMFont::bitmapFontAtlasWithString(const char *str, const char *fntFile)
    {
        return labelWithString(str, fntFile);
    }

	bool CCLabelBMFont::initWithString(const char *theString, const char *fntFile)
	{	
		assert(theString != NULL);
		CCX_SAFE_RELEASE(m_pConfiguration);// allow re-init
		m_pConfiguration = FNTConfigLoadFile(fntFile);
		m_pConfiguration->retain();
		NSAssert( m_pConfiguration, "Error creating config for BitmapFontAtlas");

		if (CCSpriteBatchNode::initWithFile(m_pConfiguration->m_sAtlasName.c_str(), strlen(theString)))
		{
			m_cOpacity = 255;
			m_tColor = ccWHITE;
			m_tContentSize = CGSizeZero;
			m_bIsOpacityModifyRGB = m_pobTextureAtlas->getTexture()->getHasPremultipliedAlpha();
			m_tAnchorPoint = ccp(0.5f, 0.5f);
			this->setString(theString);
			return true;
		}
		return false;
	}
	CCLabelBMFont::~CCLabelBMFont()
	{
		m_sString.clear();
		m_pConfiguration->release();
	}

	// BitmapFontAtlas - Atlas generation
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
		INT16 prev = -1;
		int kerningAmount = 0;

		CGSize tmpSize = CGSizeZero;

        int longestLine = 0;
        int totalHeight = 0;

        int quantityOfLines = 1;

		UINT32 len = m_sString.length();

        if (0 == len)
        {
            return;
        }

        for (UINT32 i = 0; i < len - 1; ++i)
        {
            INT16 c = m_sString[i];
            if (c == '\n')
            {
                quantityOfLines++;
            }
        }

        totalHeight = m_pConfiguration->m_uCommonHeight * quantityOfLines;
        nextFontPositionY = m_pConfiguration->m_uCommonHeight * (quantityOfLines - 1);

		for(UINT32 i=0; i<len; i++)
		{
			INT16 c = m_sString[i];
			NSAssert( c < kCCBMFontMaxChars, "BitmapFontAtlas: character outside bounds");

            if (c == '\n')
            {
                nextFontPositionX = 0;
                nextFontPositionY -= m_pConfiguration->m_uCommonHeight;
                continue;
            }
            
			kerningAmount = this->kerningAmountForFirst(prev, c);

			ccBMFontDef fontDef = m_pConfiguration->m_pBitmapFontArray[c];

			CGRect rect = fontDef.rect;

			CCSprite *fontChar;

			fontChar = (CCSprite*)(this->getChildByTag(i));
			if( ! fontChar )
			{
				fontChar = new CCSprite();
				fontChar->initWithSpriteSheet((CCSpriteSheetInternalOnly *) this, rect);
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

	//BitmapFontAtlas - CCLabelProtocol protocol
	void CCLabelBMFont::setString(const char *newString)
	{	
		m_sString.clear();
		m_sString = newString;

		if (m_pChildren && m_pChildren->count() != 0)
		{
			NSMutableArray<CCNode*>::NSMutableArrayIterator it;
			for(it = m_pChildren->begin(); it != m_pChildren->end(); ++it)
			{
				(*it)->setIsVisible(false);
			}
		}
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

	//BitmapFontAtlas - CCRGBAProtocol protocol
	void CCLabelBMFont::setColor(ccColor3B var)
	{
		m_tColor = var;
		if (m_pChildren && m_pChildren->count() != 0)
		{
			NSMutableArray<CCNode*>::NSMutableArrayIterator it;
			for(it = m_pChildren->begin(); it != m_pChildren->end(); ++it)
			{
				((CCSprite*)(*it))->setColor(m_tColor);
			}
		}
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
			NSMutableArray<CCNode*>::NSMutableArrayIterator it;
			for(it = m_pChildren->begin(); it != m_pChildren->end(); ++it)
			{
				CCRGBAProtocol *pRGBAProtocol = (*it)->convertToRGBAProtocol();
				if (pRGBAProtocol)
				{
                    pRGBAProtocol->setOpacity(m_cOpacity);
				}
			}
		}
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
			NSMutableArray<CCNode*>::NSMutableArrayIterator it;
			for(it = m_pChildren->begin(); it != m_pChildren->end(); ++it)
			{
				CCRGBAProtocol *pRGBAProtocol = (*it)->convertToRGBAProtocol();
				if (pRGBAProtocol)
				{
					pRGBAProtocol->setIsOpacityModifyRGB(m_bIsOpacityModifyRGB);
				}
			}
		}
	}
	bool CCLabelBMFont::getIsOpacityModifyRGB()
	{
		return m_bIsOpacityModifyRGB;
	}

	// BitmapFontAtlas - AnchorPoint
	void CCLabelBMFont::setAnchorPoint(CGPoint point)
	{
		if( ! CGPoint::CGPointEqualToPoint(point, m_tAnchorPoint) )
		{
			CCSpriteBatchNode::setAnchorPoint(point);
			this->createFontChars();
		}
	}

	//BitmapFontAtlas - Debug draw
#if CC_BITMAPFONTATLAS_DEBUG_DRAW
	void CCLabelBMFont::draw()
	{
		CCSpriteBatchNode::draw();
		CGSize s = this->getContentSize();
		CGPoint vertices[4]={
			ccp(0,0),ccp(s.width,0),
			ccp(s.width,s.height),ccp(0,s.height),
		};
		ccDrawPoly(vertices, 4, true);
	}
#endif // CC_BITMAPFONTATLAS_DEBUG_DRAW

}
