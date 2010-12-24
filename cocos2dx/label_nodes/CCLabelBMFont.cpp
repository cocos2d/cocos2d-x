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

#define LINE_MAX_CHAR_NUM       1024

namespace cocos2d{
	
	//
	//FNTConfig Cache - free functions
	//
	NSMutableDictionary<std::string, CCBitmapFontConfiguration*> *configurations = NULL;
	CCBitmapFontConfiguration* FNTConfigLoadFile( const char *fntFile)
	{
		CCBitmapFontConfiguration *pRet = NULL;

		if( configurations == NULL )
		{
			configurations = new NSMutableDictionary<std::string, CCBitmapFontConfiguration*>();
		}
		std::string key(fntFile);
		pRet = configurations->objectForKey(key);
		if( pRet == NULL )
		{
			pRet = CCBitmapFontConfiguration::configurationWithFNTFile(fntFile);
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

	CCBitmapFontConfiguration * CCBitmapFontConfiguration::configurationWithFNTFile(const char *FNTfile)
	{
		CCBitmapFontConfiguration * pRet = new CCBitmapFontConfiguration();
		if (pRet->initWithFNTfile(FNTfile))
		{
			pRet->autorelease();
			return pRet;
		}
		CCX_SAFE_DELETE(pRet);
		return NULL;
	}
	bool CCBitmapFontConfiguration::initWithFNTfile(const char *FNTfile)
	{
		assert(FNTfile != NULL && strlen(FNTfile)!=0);
		m_pKerningDictionary = NULL;
		this->parseConfigFile(FNTfile);
		return true;
	}
	CCBitmapFontConfiguration::~CCBitmapFontConfiguration()
	{
		CCLOGINFO( "cocos2d: deallocing CCBitmapFontConfiguration" );
		this->purgeKerningDictionary();
		m_sAtlasName.clear();
	}
	char * CCBitmapFontConfiguration::description(void)
	{
		char *ret = new char[100];
		sprintf(ret, "<CCBitmapFontConfiguration | Kernings:%d | Image = %s>", HASH_COUNT(m_pKerningDictionary), m_sAtlasName.c_str());
		return ret;
	}
	void CCBitmapFontConfiguration::purgeKerningDictionary()
	{
		tKerningHashElement *current;
		while(m_pKerningDictionary) 
		{
			current = m_pKerningDictionary; 
			HASH_DEL(m_pKerningDictionary,current);
			free(current);
		}
	}
	void CCBitmapFontConfiguration::parseConfigFile(const char *controlFile)
	{	
		std::string fullpath = CCFileUtils::fullPathFromRelativePath(controlFile);

        FileData data;
        unsigned long nBufSize = 0;
        char* pBuffer = (char*) data.getFileData(fullpath.c_str(), "r", &nBufSize);

        NSAssert(pBuffer, "CCBitmapFontConfiguration::parseConfigFile | Open file error.");

        if (!pBuffer)
        {
            return;
        }
        
        char LineMax[LINE_MAX_CHAR_NUM] = {0};
        size_t step = 0;
        size_t leftSize = nBufSize - step;

        while (leftSize > 0)
        {
            // clean temp data
            memset(LineMax, 0, sizeof(char) * LINE_MAX_CHAR_NUM);

            // read some data into LineMax[LINE_MAX_CHAR_NUM]
            if (leftSize < LINE_MAX_CHAR_NUM)
            {
                memcpy(LineMax, pBuffer + step, sizeof(char) * leftSize);
            }
            else
            {
                // only read LINE_MAX_CHAR_NUM - 1 char from buffer,to make sure the LineMax is end with '\0'
                memcpy(LineMax, pBuffer + step, sizeof(char) * (LINE_MAX_CHAR_NUM - 1));
            }

            // find the '\n'
            char* pos = strchr(LineMax, '\n');
            size_t lineSize = strlen(LineMax) * sizeof(char);
            if (pos)
            {
                lineSize = (pos - LineMax + 1) * sizeof(char);
                memset(LineMax + lineSize, 0, sizeof(char) * LINE_MAX_CHAR_NUM - lineSize);
            }
            step += lineSize;
            leftSize = nBufSize - step;

            // parse spacing / padding
            std::string line = LineMax;
            if(line.substr(0,strlen("info face")) == "info face") 
            {
                // XXX: info parsing is incomplete
                // Not needed for the Hiero editors, but needed for the AngelCode editor
                //			[self parseInfoArguments:line];
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
                ccBitmapFontDef characterDefinition;
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
	void CCBitmapFontConfiguration::parseImageFileName(std::string line, const char *fntFile)
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
	void CCBitmapFontConfiguration::parseInfoArguments(std::string line)
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
	void CCBitmapFontConfiguration::parseCommonArguments(std::string line)
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
		NSAssert(atoi(value.c_str()) <= CCConfiguration::sharedConfiguration()->getMaxTextureSize(), "CCBitmapFontAtlas: page can't be larger than supported");
		// scaleH. sanity check
		index = line.find("scaleH=") + strlen("scaleH=");
		index2 = line.find(' ', index);
		value = line.substr(index, index2-index);
		NSAssert(atoi(value.c_str()) <= CCConfiguration::sharedConfiguration()->getMaxTextureSize(), "CCBitmapFontAtlas: page can't be larger than supported");
		// pages. sanity check
		index = line.find("pages=") + strlen("pages=");
		index2 = line.find(' ', index);
		value = line.substr(index, index2-index);
		NSAssert(atoi(value.c_str()) == 1, "CCBitfontAtlas: only supports 1 page");

		// packed (ignore) What does this mean ??
	}
	void CCBitmapFontConfiguration::parseCharacterDefinition(std::string line, ccBitmapFontDef *characterDefinition)
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
		NSAssert(characterDefinition->charID < kCCBitmapFontAtlasMaxChars, "BitmpaFontAtlas: CharID bigger than supported");
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
	void CCBitmapFontConfiguration::parseKerningCapacity(std::string line)
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
	void CCBitmapFontConfiguration::parseKerningEntry(std::string line)
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
	//CCBitmapFontAtlas
	//

	//BitmapFontAtlas - Purge Cache
	void CCBitmapFontAtlas::purgeCachedData()
	{
		FNTConfigRemoveCache();
	}

	//BitmapFontAtlas - Creation & Init
	CCBitmapFontAtlas *CCBitmapFontAtlas::bitmapFontAtlasWithString(const char *str, const char *fntFile)
	{
		CCBitmapFontAtlas *pRet = new CCBitmapFontAtlas();
		if(pRet && pRet->initWithString(str, fntFile))
		{
			pRet->autorelease();
			return pRet;
		}
		CCX_SAFE_DELETE(pRet)
		return NULL;
	}
	bool CCBitmapFontAtlas::initWithString(const char *theString, const char *fntFile)
	{	
		assert(theString != NULL);
		CCX_SAFE_RELEASE(m_pConfiguration);// allow re-init
		m_pConfiguration = FNTConfigLoadFile(fntFile);
		m_pConfiguration->retain();
		NSAssert( m_pConfiguration, "Error creating config for BitmapFontAtlas");

		if (CCSpriteSheet::initWithFile(m_pConfiguration->m_sAtlasName.c_str(), strlen(theString)))
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
	CCBitmapFontAtlas::~CCBitmapFontAtlas()
	{
		m_sString.clear();
		m_pConfiguration->release();
	}

	// BitmapFontAtlas - Atlas generation
	int CCBitmapFontAtlas::kerningAmountForFirst(unsigned short first, unsigned short second)
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
	void CCBitmapFontAtlas::createFontChars()
	{
		int nextFontPositionX = 0;
		INT16 prev = -1;
		int kerningAmount = 0;

		CGSize tmpSize = CGSizeZero;
		UINT32 len = m_sString.length();
		for(UINT32 i=0; i<len; i++)
		{
			INT16 c = m_sString[i];
			NSAssert( c < kCCBitmapFontAtlasMaxChars, "BitmapFontAtlas: character outside bounds");

			kerningAmount = this->kerningAmountForFirst(prev, c);

			ccBitmapFontDef fontDef = m_pConfiguration->m_pBitmapFontArray[c];

			CGRect rect = fontDef.rect;

			CCSprite *fontChar;

			fontChar = (CCSprite*)(this->getChildByTag(i));
			if( ! fontChar )
			{
				fontChar = new CCSprite();
				fontChar->initWithSpriteSheet(this, rect);
				this->addChild(fontChar, 0, i);
				fontChar->release();
			}
			else
			{
				// reusing fonts
				fontChar->setTextureRect(rect);

				// restore to default in case they were modified
				fontChar->setIsVisible(true);
				fontChar->setOpacity(255);
			}

			fontChar->setPosition( ccp( nextFontPositionX + fontDef.xOffset + fontDef.rect.size.width / 2.0f ,
				(m_pConfiguration->m_uCommonHeight - fontDef.yOffset) - rect.size.height/2.0f ) );		

			//		NSLog(@"position.y: %f", fontChar.position.y);

			// update kerning
			fontChar->setPosition( ccpAdd( fontChar->getPosition(), ccp((float)kerningAmount,0)) );
			nextFontPositionX += m_pConfiguration->m_pBitmapFontArray[c].xAdvance + kerningAmount;
			prev = c;

			tmpSize.width += m_pConfiguration->m_pBitmapFontArray[c].xAdvance + kerningAmount;
			tmpSize.height = (float)(m_pConfiguration->m_uCommonHeight);

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
		}
		this->setContentSize(tmpSize);
	}

	//BitmapFontAtlas - CCLabelProtocol protocol
	void CCBitmapFontAtlas::setString(const char *newString)
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

	//BitmapFontAtlas - CCRGBAProtocol protocol
	void CCBitmapFontAtlas::setColor(ccColor3B var)
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
	ccColor3B CCBitmapFontAtlas::getColor()
	{
		return m_tColor;
	}
	void CCBitmapFontAtlas::setOpacity(GLubyte var)
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
	GLubyte CCBitmapFontAtlas::getOpacity()
	{
		return m_cOpacity;
	}
	void CCBitmapFontAtlas::setIsOpacityModifyRGB(bool var)
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
	bool CCBitmapFontAtlas::getIsOpacityModifyRGB()
	{
		return m_bIsOpacityModifyRGB;
	}

	// BitmapFontAtlas - AnchorPoint
	void CCBitmapFontAtlas::setAnchorPoint(CGPoint point)
	{
		if( ! CGPoint::CGPointEqualToPoint(point, m_tAnchorPoint) )
		{
			CCSpriteSheet::setAnchorPoint(point);
			this->createFontChars();
		}
	}

	//BitmapFontAtlas - Debug draw
#if CC_BITMAPFONTATLAS_DEBUG_DRAW
	void CCBitmapFontAtlas::draw()
	{
		CCSpriteSheet::draw();
		CGSize s = this->getContentSize();
		CGPoint vertices[4]={
			ccp(0,0),ccp(s.width,0),
			ccp(s.width,s.height),ccp(0,s.height),
		};
		ccDrawPoly(vertices, 4, true);
	}
#endif // CC_BITMAPFONTATLAS_DEBUG_DRAW

}
