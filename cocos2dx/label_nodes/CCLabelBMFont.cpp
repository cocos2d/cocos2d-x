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

    static int cc_wcslen(const unsigned short* str)
    {
        int i=0;
        while(*str++) i++;
        return i;
    }

    /* Code from GLIB gutf8.c starts here. */

    #define UTF8_COMPUTE(Char, Mask, Len)		\
      if (Char < 128)				\
        {						\
          Len = 1;					\
          Mask = 0x7f;				\
        }						\
      else if ((Char & 0xe0) == 0xc0)		\
        {						\
          Len = 2;					\
          Mask = 0x1f;				\
        }						\
      else if ((Char & 0xf0) == 0xe0)		\
        {						\
          Len = 3;					\
          Mask = 0x0f;				\
        }						\
      else if ((Char & 0xf8) == 0xf0)		\
        {						\
          Len = 4;					\
          Mask = 0x07;				\
        }						\
      else if ((Char & 0xfc) == 0xf8)		\
        {						\
          Len = 5;					\
          Mask = 0x03;				\
        }						\
      else if ((Char & 0xfe) == 0xfc)		\
        {						\
          Len = 6;					\
          Mask = 0x01;				\
        }						\
      else						\
        Len = -1;

    #define UTF8_LENGTH(Char)			\
      ((Char) < 0x80 ? 1 :				\
       ((Char) < 0x800 ? 2 :			\
        ((Char) < 0x10000 ? 3 :			\
         ((Char) < 0x200000 ? 4 :			\
          ((Char) < 0x4000000 ? 5 : 6)))))


    #define UTF8_GET(Result, Chars, Count, Mask, Len)	\
      (Result) = (Chars)[0] & (Mask);			\
      for ((Count) = 1; (Count) < (Len); ++(Count))		\
        {							\
          if (((Chars)[(Count)] & 0xc0) != 0x80)		\
	    {						\
	      (Result) = -1;				\
	      break;					\
	    }						\
          (Result) <<= 6;					\
          (Result) |= ((Chars)[(Count)] & 0x3f);		\
        }

    #define UNICODE_VALID(Char)			\
      ((Char) < 0x110000 &&				\
       (((Char) & 0xFFFFF800) != 0xD800) &&		\
       ((Char) < 0xFDD0 || (Char) > 0xFDEF) &&	\
       ((Char) & 0xFFFE) != 0xFFFE)


    static const char utf8_skip_data[256] = {
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1,
      2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
      2, 2, 2, 2, 2, 2, 2,
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5,
      5, 5, 5, 6, 6, 1, 1
    };

    static const char *const g_utf8_skip = utf8_skip_data;

    #define cc_utf8_next_char(p) (char *)((p) + g_utf8_skip[*(unsigned char *)(p)])

	/*
	 * @str:	the string to search through.
	 * @c:		the character to find.
	 * 
	 * Returns the index of the first occurrence of the character, if found.  Otherwise -1 is returned.
	 * 
	 * Return value: the index of the first occurrence of the character if found or -1 otherwise.
	 * */
	static unsigned int cc_utf8_find_char(std::vector<unsigned short> str, unsigned short c)
	{
		unsigned int len = str.size();

		for (unsigned int i = 0; i < len; ++i)
			if (str[i] == c) return i;

		return -1;
	}

	/*
	 * @str:	the string to search through.
	 * @c:		the character to not look for.
	 * 
	 * Return value: the index of the last character that is not c.
	 * */
	static unsigned int cc_utf8_find_last_not_char(std::vector<unsigned short> str, unsigned short c)
	{
		int len = str.size();

		int i = len - 1;
		for (; i >= 0; --i)
			if (str[i] != c) return i;

		return i;
	}

	/*
	 * @str:	the string to trim
	 * @index:	the index to start trimming from.
	 * 
	 * Trims str st str=[0, index) after the operation.
	 * 
	 * Return value: the trimmed string.
	 * */
	static void cc_utf8_trim_from(std::vector<unsigned short>* str, int index)
	{
		int size = str->size();
		if (index >= size || index < 0)
			return;

		str->erase(str->begin() + index, str->begin() + size);
	}

	/*
	 * @ch is the unicode character whitespace?
	 * 
	 * Reference: http://en.wikipedia.org/wiki/Whitespace_character#Unicode
	 * 
	 * Return value: weather the character is a whitespace character.
	 * */
	static bool isspace_unicode(unsigned short ch)
	{
		return  ch >= 0x0009 && ch <= 0x000D || ch == 0x0020 || ch == 0x0085 || ch == 0x00A0 || ch == 0x1680
			|| (ch >= 0x2000 && ch <= 0x200A) || ch == 0x2028 || ch == 0x2029 || ch == 0x202F
			||  ch == 0x205F || ch == 0x3000;
	}

	static void cc_utf8_trim_ws(std::vector<unsigned short>* str)
	{
		using namespace std;
		int len = str->size();

		if ( len <= 0 )
			return;

		int last_index = len - 1;

		// Only start trimming if the last character is whitespace..
		if (isspace_unicode((*str)[last_index]))
		{
			for (int i = last_index - 1; i >= 0; --i)
			{
				if (isspace_unicode((*str)[i]))
					last_index = i;
				else
					break;
			}

			cc_utf8_trim_from(str, last_index);
		}
	}

    /*
     * g_utf8_strlen:
     * @p: pointer to the start of a UTF-8 encoded string.
     * @max: the maximum number of bytes to examine. If @max
     *       is less than 0, then the string is assumed to be
     *       null-terminated. If @max is 0, @p will not be examined and
     *       may be %NULL.
     *
     * Returns the length of the string in characters.
     *
     * Return value: the length of the string in characters
     **/
    static long
    cc_utf8_strlen (const char * p, int max)
    {
      long len = 0;
      const char *start = p;

      if (!(p != NULL || max == 0))
      {
          return 0;
      }

      if (max < 0)
        {
          while (*p)
	    {
	      p = cc_utf8_next_char (p);
	      ++len;
	    }
        }
      else
        {
          if (max == 0 || !*p)
	    return 0;

          p = cc_utf8_next_char (p);

          while (p - start < max && *p)
	    {
	      ++len;
	      p = cc_utf8_next_char (p);
	    }

          /* only do the last len increment if we got a complete
           * char (don't count partial chars)
           */
          if (p - start == max)
	    ++len;
        }

      return len;
    }

    /*
     * g_utf8_get_char:
     * @p: a pointer to Unicode character encoded as UTF-8
     *
     * Converts a sequence of bytes encoded as UTF-8 to a Unicode character.
     * If @p does not point to a valid UTF-8 encoded character, results are
     * undefined. If you are not sure that the bytes are complete
     * valid Unicode characters, you should use g_utf8_get_char_validated()
     * instead.
     *
     * Return value: the resulting character
     **/
    static unsigned int
    cc_utf8_get_char (const char * p)
    {
      int i, mask = 0, len;
      unsigned int result;
      unsigned char c = (unsigned char) *p;

      UTF8_COMPUTE (c, mask, len);
      if (len == -1)
        return (unsigned int) - 1;
      UTF8_GET (result, p, i, mask, len);

      return result;
    }

	/*
	 * cc_utf8_from_cstr:
	 * @str_old: pointer to the start of a C string.
	 * 
	 * Creates a utf8 string from a cstring.
	 * 
	 * Return value: the newly created utf8 string.
	 * */
	static unsigned short* cc_utf8_from_cstr(const char* str_old)
	{
		int len = cc_utf8_strlen(str_old, -1);

		unsigned short* str_new = new unsigned short[len + 1];
		str_new[len] = 0;

		for (int i = 0; i < len; ++i)
		{
			str_new[i] = cc_utf8_get_char(str_old);
			str_old = cc_utf8_next_char(str_old);
		}

		return str_new;
	}

	static std::vector<unsigned short> cc_utf8_vec_from_cstr(const unsigned short* str)
	{
		int len = cc_wcslen(str);
		std::vector<unsigned short> str_new;

		for (int i = 0; i < len; ++i)
			str_new.push_back(str[i]);

		return str_new;
	}

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
		CCAssert(FNTfile != NULL && strlen(FNTfile)!=0, "");
		m_pKerningDictionary = NULL;
		this->parseConfigFile(FNTfile);
		return true;
	}

	CCBMFontConfiguration::CCBMFontConfiguration()
		: m_pBitmapFontArray(new std::map<unsigned int, ccBMFontDef>)
		, m_uCommonHeight(0)
		, m_pKerningDictionary(NULL)
	{

	}

	CCBMFontConfiguration::~CCBMFontConfiguration()
	{
		CCLOGINFO( "cocos2d: deallocing CCBMFontConfiguration" );
		CC_SAFE_DELETE(m_pBitmapFontArray);
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
		while (strLeft.length() > 0)
		{
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
				(*m_pBitmapFontArray)[ characterDefinition.charID ] = characterDefinition;
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
		return labelWithString(str, fntFile, CCTextAlignmentLeft, 0);
	}

	//LabelBMFont - Creation & Init
	CCLabelBMFont *CCLabelBMFont::labelWithString(const char *str, const char *fntFile, CCTextAlignment alignment
		, float width)
	{
		CCLabelBMFont *pRet = new CCLabelBMFont();
		if(pRet && pRet->initWithString(str, fntFile, alignment, width))
		{
			pRet->autorelease();
			return pRet;
		}
		CC_SAFE_DELETE(pRet)
			return NULL;
	}

	bool CCLabelBMFont::initWithString(const char *theString, const char *fntFile)
	{
		return initWithString(theString, fntFile, CCTextAlignmentCenter, 0);
	}

	bool CCLabelBMFont::initWithString(const char *theString, const char *fntFile, CCTextAlignment alignment
		, float width)
	{
		CCAssert(theString != NULL, "");
		CC_SAFE_RELEASE(m_pConfiguration);// allow re-init
		m_pConfiguration = FNTConfigLoadFile(fntFile);
		m_pConfiguration->retain();
		CCAssert( m_pConfiguration, "Error creating config for LabelBMFont");

		if (CCSpriteBatchNode::initWithFile(m_pConfiguration->m_sAtlasName.c_str(), strlen(theString)))
		{
			m_pAlignment = alignment;
			m_fWidth = width;
			m_sString = cc_utf8_from_cstr(theString);
			m_cOpacity = 255;
			m_tColor = ccWHITE;
			m_tContentSize = CCSizeZero;
			m_bIsOpacityModifyRGB = m_pobTextureAtlas->getTexture()->getHasPremultipliedAlpha();
			this->setString(theString);
			setAnchorPoint(ccp(0.5f, 0.5f));
			return true;
		}
		return false;
	}

	CCLabelBMFont::~CCLabelBMFont()
	{
		CC_SAFE_DELETE(m_sString);
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

		unsigned int stringLen = cc_wcslen(m_sString);
		if (stringLen == 0)
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

            if (c == '\n')
            {
                nextFontPositionX = 0;
                nextFontPositionY -= m_pConfiguration->m_uCommonHeight;
                continue;
            }

            std::map<unsigned int, ccBMFontDef>::iterator it = m_pConfiguration->m_pBitmapFontArray->find(c);
            CCAssert(it != m_pConfiguration->m_pBitmapFontArray->end(), "LabelBMFont: character is not supported");
            
			kerningAmount = this->kerningAmountForFirst(prev, c);

			const ccBMFontDef& fontDef = (*(m_pConfiguration->m_pBitmapFontArray))[c];

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

            float yOffset = (float)(m_pConfiguration->m_uCommonHeight) - fontDef.yOffset;
			fontChar->setPositionInPixels( ccp( nextFontPositionX + fontDef.xOffset + fontDef.rect.size.width / 2.0f + kerningAmount,
				                                (float) nextFontPositionY + yOffset - rect.size.height/2.0f ) );		

			//		NSLog(@"position.y: %f", fontChar.position.y);

			// update kerning
			nextFontPositionX += (*(m_pConfiguration->m_pBitmapFontArray))[c].xAdvance + kerningAmount;
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
		this->setString(newString, false);
	}

	void CCLabelBMFont::setString(const char *newString, bool fromUpdate)
	{
		if (fromUpdate)
		{
			m_sString = cc_utf8_from_cstr(newString);
		}
		else
		{
			m_sString_initial = std::string(newString);
		}

		updateString(fromUpdate);
	}

	void CCLabelBMFont::updateString(bool fromUpdate)
	{

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
			}
		}
		this->createFontChars();

		if (!fromUpdate)
			updateLabel();
	}

	const char* CCLabelBMFont::getString(void)
	{
		return m_sString_initial.c_str();
	}

    void CCLabelBMFont::setCString(const char *label)
    {
        setString(label);
    }

	//LabelBMFont - CCRGBAProtocol protocol
	void CCLabelBMFont::setColor(const ccColor3B& var)
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
            }
		}
	}
	const ccColor3B& CCLabelBMFont::getColor()
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
                    CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(pNode);
                    if (pRGBAProtocol)
                    {
                        pRGBAProtocol->setOpacity(m_cOpacity);
                    }
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
            CCObject* child;
            CCARRAY_FOREACH(m_pChildren, child)
            {
                CCNode* pNode = (CCNode*) child;
                if (pNode)
                {
                    CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(pNode);
                    if (pRGBAProtocol)
                    {
                        pRGBAProtocol->setIsOpacityModifyRGB(m_bIsOpacityModifyRGB);
                    }
                }
            }
		}
	}
	bool CCLabelBMFont::getIsOpacityModifyRGB()
	{
		return m_bIsOpacityModifyRGB;
	}

	// LabelBMFont - AnchorPoint
	void CCLabelBMFont::setAnchorPoint(const CCPoint& point)
	{
		if( ! CCPoint::CCPointEqualToPoint(point, m_tAnchorPoint) )
		{
			CCSpriteBatchNode::setAnchorPoint(point);
			updateLabel();
		}
	}

	// LabelBMFont - Alignment
	void CCLabelBMFont::updateLabel()
	{
		using namespace std;

		this->setString(m_sString_initial.c_str(), true);

		if (m_fWidth > 0)
		{
			// Step 1: Make multiline
			vector<unsigned short> str_whole = cc_utf8_vec_from_cstr(m_sString);
			unsigned int stringLength = str_whole.size();
			vector<unsigned short> multiline_string;
			vector<unsigned short> last_word;
			int line = 1, i = 0;
			bool start_line = false, start_word = false;
			float startOfLine = -1, startOfWord = -1;
			int skip = 0;

			CCArray* children = getChildren();
			for (unsigned int j = 0; j < children->count(); j++)
			{
				CCSprite* characterSprite;

				while (!(characterSprite = (CCSprite*)this->getChildByTag(j + skip)))
					skip++;

				if (!characterSprite->getIsVisible()) continue;

				if (i >= stringLength || i < 0)
					break;

				unsigned short character = str_whole[i];

				if (!start_word)
				{
					startOfWord = characterSprite->getPosition().x - characterSprite->getContentSize().width/2.0f;
					start_word = true;
				}
				if (!start_line)
				{
					startOfLine = startOfWord;
					start_line = true;
				}

				// Newline.
				if (character == '\n')
				{
					cc_utf8_trim_ws(&last_word);

// 					int found = cc_utf8_find_char(last_word, ' ');
// 					if (found != -1)
// 						cc_utf8_trim_from(&last_word, found + 1);

					multiline_string.insert(multiline_string.end(), last_word.begin(), last_word.end());
					last_word.clear();
					start_word = false;
					start_line = false;
					startOfWord = -1;
					startOfLine = -1;
					i++;
					line++;

					if (i >= stringLength || i < 0)
						break;

					character = str_whole[i];

					if (!startOfWord)
					{
						startOfWord = characterSprite->getPosition().x - characterSprite->getContentSize().width/2.0f;
						start_word = true;
					}
					if (!startOfLine)
					{
						startOfLine  = startOfWord;
						start_line = true;
					}
				}

				// Whitespace.
				if (isspace_unicode(character))
				{
					last_word.push_back(character);
					multiline_string.insert(multiline_string.end(), last_word.begin(), last_word.end());
					last_word.clear();
					start_word = false;
					startOfWord = -1;
					i++;
					continue;
				}

				// Out of bounds.
				if (characterSprite->getPosition().x + characterSprite->getContentSize().width / 2.0f - startOfLine 
					> m_fWidth )
				{
					if (!m_bLineBreakWithoutSpaces)
					{
						last_word.push_back(character);

						int found = cc_utf8_find_last_not_char(multiline_string, ' ');
						if (found != -1)
							cc_utf8_trim_ws(&multiline_string);
						else
							multiline_string.clear();

						if (multiline_string.size() > 0)
							multiline_string.push_back('\n');

						line++;
						start_line = false;
						startOfLine = -1;
						i++;
					}
					else
					{
						cc_utf8_trim_ws(&last_word);

						last_word.push_back('\n');
						multiline_string.insert(multiline_string.end(), last_word.begin(), last_word.end());
						last_word.clear();
						start_word = false;
						start_line = false;
						startOfWord = -1;
						startOfLine = -1;
						line++;

						if (i >= stringLength || i < 0)
							break;

						if (!startOfWord)
						{
							startOfWord = characterSprite->getPosition().x - characterSprite->getContentSize().width/2.0f;
							start_word = true;
						}
						if (!startOfLine)
						{
							startOfLine  = startOfWord;
							start_line = true;
						}

						j--;
					}

					continue;
				}
				else
				{
					// Character is normal.
					last_word.push_back(character);
					i++;
					continue;
				}
			}

			multiline_string.insert(multiline_string.end(), last_word.begin(), last_word.end());

			int size = multiline_string.size();
			unsigned short* str_new = new unsigned short[size + 1];

			for (int i = 0; i < size; ++i)
				str_new[i] = multiline_string[i];

			str_new[size] = 0;

			delete[] m_sString;
			m_sString = str_new;
			updateString(true);
		}

		// Step 2: Make alignment
		if (m_pAlignment != CCTextAlignmentLeft)
		{
			int i = 0;

			int lineNumber = 0;
			int str_len = cc_wcslen(m_sString);
			vector<unsigned short> last_line;
			for (int ctr = 0; ctr <= str_len; ++ctr)
			{
				if (m_sString[ctr] == '\n' || m_sString[ctr] == 0)
				{
					float lineWidth = 0.0f;
					int line_length = last_line.size();
					int index = i + line_length - 1 + lineNumber;
					if (index < 0) continue;

					CCSprite* lastChar = (CCSprite*)getChildByTag(index);

					lineWidth = lastChar->getPosition().x + lastChar->getContentSize().width/2.0f;

					float shift = 0;
					switch (m_pAlignment)
					{
					case CCTextAlignmentCenter:
						shift = getContentSize().width/2.0f - lineWidth/2.0f;
						break;
					case CCTextAlignmentRight:
						shift = getContentSize().width - lineWidth;
					default:
						break;
					}

					if (shift != 0)
					{
						for (unsigned j = 0; j < line_length; j++)
						{
							index = i + j + lineNumber;
							if (index < 0) continue;

							CCSprite* characterSprite = (CCSprite*)getChildByTag(index);
							characterSprite->setPosition(ccpAdd(characterSprite->getPosition(), ccp(shift, 0.0f)));
						}
					}

					i += line_length;
					lineNumber++;

					last_line.clear();
					continue;
				}

				last_line.push_back(m_sString[ctr]);
			}
		}
	}

	// LabelBMFont - Alignment
	void CCLabelBMFont::setAlignment(CCTextAlignment alignment)
	{
		this->m_pAlignment = alignment;
		updateLabel();
	}

	void CCLabelBMFont::setWidth(float width)
	{
		this->m_fWidth = width;
		updateLabel();
	}

	void CCLabelBMFont::setLineBreakWithoutSpace( bool breakWithoutSpace )
	{
		m_bLineBreakWithoutSpaces = breakWithoutSpace;
		updateLabel();
	}

	//LabelBMFont - Debug draw
#if CC_LABELBMFONT_DEBUG_DRAW
	void CCLabelBMFont::draw()
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

}
