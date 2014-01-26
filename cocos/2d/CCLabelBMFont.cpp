/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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

Use any of these editors to generate BMFonts:
http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
http://www.angelcode.com/products/bmfont/ (Free, Windows only)

****************************************************************************/
#include "CCLabelBMFont.h"
#include "CCString.h"
#include "CCDictionary.h"
#include "CCConfiguration.h"
#include "CCDrawingPrimitives.h"
#include "CCSprite.h"
#include "platform/CCFileUtils.h"
#include "CCDirector.h"
#include "CCTextureCache.h"
#include "ccUTF8.h"
#include "CCMap.h"

using namespace std;

NS_CC_BEGIN

// The return value needs to be deleted by CC_SAFE_DELETE_ARRAY.
static unsigned short* copyUTF16StringN(unsigned short* str)
{
    int length = str ? cc_wcslen(str) : 0;
    unsigned short* ret = new unsigned short[length+1];
    for (int i = 0; i < length; ++i) {
        ret[i] = str[i];
    }
    ret[length] = 0;
    return ret;
}

//
//FNTConfig Cache - free functions
//
static Map<std::string, CCBMFontConfiguration*>* s_configurations = nullptr;

CCBMFontConfiguration* FNTConfigLoadFile(const std::string& fntFile)
{
    CCBMFontConfiguration* ret = nullptr;

    if( s_configurations == nullptr )
    {
        s_configurations = new Map<std::string, CCBMFontConfiguration*>();
    }

    ret = s_configurations->at(fntFile);
    if( ret == nullptr )
    {
        ret = CCBMFontConfiguration::create(fntFile.c_str());
        if (ret)
        {
            s_configurations->insert(fntFile, ret);
        }        
    }

    return ret;
}

void FNTConfigRemoveCache( void )
{
    if (s_configurations)
    {
        s_configurations->clear();
        CC_SAFE_DELETE(s_configurations);
    }
}

//
//BitmapFontConfiguration
//

CCBMFontConfiguration * CCBMFontConfiguration::create(const std::string& FNTfile)
{
    CCBMFontConfiguration * ret = new CCBMFontConfiguration();
    if (ret->initWithFNTfile(FNTfile))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool CCBMFontConfiguration::initWithFNTfile(const std::string& FNTfile)
{
    _kerningDictionary = nullptr;
    _fontDefDictionary = nullptr;
    
    _characterSet = this->parseConfigFile(FNTfile);
    
    if (! _characterSet)
    {
        return false;
    }

    return true;
}

std::set<unsigned int>* CCBMFontConfiguration::getCharacterSet() const
{
    return _characterSet;
}

CCBMFontConfiguration::CCBMFontConfiguration()
: _fontDefDictionary(nullptr)
, _commonHeight(0)
, _kerningDictionary(nullptr)
, _characterSet(nullptr)
{

}

CCBMFontConfiguration::~CCBMFontConfiguration()
{
    CCLOGINFO( "deallocing CCBMFontConfiguration: %p", this );
    this->purgeFontDefDictionary();
    this->purgeKerningDictionary();
    _atlasName.clear();
    CC_SAFE_DELETE(_characterSet);
}

std::string CCBMFontConfiguration::description(void) const
{
    return StringUtils::format(
        "<CCBMFontConfiguration = " CC_FORMAT_PRINTF_SIZE_T " | Glphys:%d Kernings:%d | Image = %s>",
        (size_t)this,
        HASH_COUNT(_fontDefDictionary),
        HASH_COUNT(_kerningDictionary),
        _atlasName.c_str()
    );
}

void CCBMFontConfiguration::purgeKerningDictionary()
{
    tKerningHashElement *current;
    while(_kerningDictionary) 
    {
        current = _kerningDictionary; 
        HASH_DEL(_kerningDictionary,current);
        free(current);
    }
}

void CCBMFontConfiguration::purgeFontDefDictionary()
{    
    tFontDefHashElement *current, *tmp;

    HASH_ITER(hh, _fontDefDictionary, current, tmp) {
        HASH_DEL(_fontDefDictionary, current);
        free(current);
    }
}

std::set<unsigned int>* CCBMFontConfiguration::parseConfigFile(const std::string& controlFile)
{    
    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(controlFile);

	Data data = FileUtils::getInstance()->getDataFromFile(fullpath);
    CCASSERT((!data.isNull() && data.getSize() > 0), "CCBMFontConfiguration::parseConfigFile | Open file error.");

    if (memcmp("BMF", data.getBytes(), 3) == 0) {
        std::set<unsigned int>* ret = parseBinaryConfigFile(data.getBytes(), data.getSize(), controlFile);
        return ret;
    }

    std::string contents((const char*)data.getBytes(), data.getSize());
    
    std::set<unsigned int> *validCharsString = new std::set<unsigned int>();

    if (contents.empty())
    {
        CCLOG("cocos2d: Error parsing FNTfile %s", controlFile.c_str());
        return nullptr;
    }

    // parse spacing / padding
    std::string line;
    std::string strLeft(contents);
    while (strLeft.length() > 0)
    {
        size_t pos = strLeft.find('\n');

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
            //            [self parseInfoArguments:line];
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
            tFontDefHashElement* element = (tFontDefHashElement*)malloc( sizeof(*element) );
            this->parseCharacterDefinition(line, &element->fontDef);

            element->key = element->fontDef.charID;
            HASH_ADD_INT(_fontDefDictionary, key, element);
            
            validCharsString->insert(element->fontDef.charID);
        }
//        else if(line.substr(0,strlen("kernings count")) == "kernings count")
//        {
//            this->parseKerningCapacity(line);
//        }
        else if(line.substr(0,strlen("kerning first")) == "kerning first")
        {
            this->parseKerningEntry(line);
        }
    }
    
    return validCharsString;
}

std::set<unsigned int>* CCBMFontConfiguration::parseBinaryConfigFile(unsigned char* pData, unsigned long size, const std::string& controlFile)
{
    /* based on http://www.angelcode.com/products/bmfont/doc/file_format.html file format */

    set<unsigned int> *validCharsString = new set<unsigned int>();

    unsigned long remains = size;

    CCASSERT(pData[3] == 3, "Only version 3 is supported");

    pData += 4; remains -= 4;

    while (remains > 0)
	{
        unsigned char blockId = pData[0]; pData += 1; remains -= 1;
        uint32_t blockSize = 0; memcpy(&blockSize, pData, 4);

        pData += 4; remains -= 4;

        if (blockId == 1)
		{
            /*
             fontSize 	2 	int 	0
             bitField 	1 	bits 	2 	bit 0: smooth, bit 1: unicode, bit 2: italic, bit 3: bold, bit 4: fixedHeigth, bits 5-7: reserved
             charSet 	1 	uint 	3
             stretchH 	2 	uint 	4
             aa 	1 	uint 	6
             paddingUp 	1 	uint 	7
             paddingRight	1 	uint 	8
             paddingDown 	1 	uint 	9
             paddingLeft 	1 	uint 	10
             spacingHoriz	1 	uint 	11
             spacingVert 	1 	uint 	12
             outline 	1 	uint 	13	added with version 2
             fontName 	n+1	string 	14	null terminated string with length n
             */

            _padding.top = (unsigned char)pData[7];
            _padding.right = (unsigned char)pData[8];
            _padding.bottom = (unsigned char)pData[9];
            _padding.left = (unsigned char)pData[10];
        }
		else if (blockId == 2)
		{
            /*
             lineHeight 	2 	uint 	0
             base 	2 	uint 	2
             scaleW 	2 	uint 	4
             scaleH 	2 	uint 	6
             pages 	2 	uint 	8
             bitField 	1 	bits 	10 	bits 0-6: reserved, bit 7: packed
             alphaChnl 	1 	uint 	11
             redChnl 	1 	uint 	12
             greenChnl 	1 	uint 	13
             blueChnl 	1 	uint 	14
             */

            uint16_t lineHeight = 0; memcpy(&lineHeight, pData, 2);
            _commonHeight = lineHeight;

            uint16_t scaleW = 0; memcpy(&scaleW, pData + 4, 2);
            uint16_t scaleH = 0; memcpy(&scaleH, pData + 6, 2);

            CCASSERT(scaleW <= Configuration::getInstance()->getMaxTextureSize() && scaleH <= Configuration::getInstance()->getMaxTextureSize(), "CCLabelBMFont: page can't be larger than supported");

            uint16_t pages = 0; memcpy(&pages, pData + 8, 2);
            CCASSERT(pages == 1, "CCBitfontAtlas: only supports 1 page");
        }
		else if (blockId == 3)
		{
            /*
             pageNames 	p*(n+1) 	strings 	0 	p null terminated strings, each with length n
             */

            const char *value = (const char *)pData;
            CCASSERT(strlen(value) < blockSize, "Block size should be less then string");

            _atlasName = FileUtils::getInstance()->fullPathFromRelativeFile(value, controlFile);
        }
		else if (blockId == 4)
		{
            /*
             id 	4 	uint 	0+c*20 	These fields are repeated until all characters have been described
             x 	2 	uint 	4+c*20
             y 	2 	uint 	6+c*20
             width 	2 	uint 	8+c*20
             height 	2 	uint 	10+c*20
             xoffset 	2 	int 	12+c*20
             yoffset 	2 	int 	14+c*20
             xadvance 	2 	int 	16+c*20
             page 	1 	uint 	18+c*20
             chnl 	1 	uint 	19+c*20
             */

            unsigned long count = blockSize / 20;

            for (unsigned long i = 0; i < count; i++)
			{
                tFontDefHashElement* element = (tFontDefHashElement*)malloc( sizeof(*element) );

                uint32_t charId = 0; memcpy(&charId, pData + (i * 20), 4);
                element->fontDef.charID = charId;

                uint16_t charX = 0; memcpy(&charX, pData + (i * 20) + 4, 2);
                element->fontDef.rect.origin.x = charX;

                uint16_t charY = 0; memcpy(&charY, pData + (i * 20) + 6, 2);
                element->fontDef.rect.origin.y = charY;

                uint16_t charWidth = 0; memcpy(&charWidth, pData + (i * 20) + 8, 2);
                element->fontDef.rect.size.width = charWidth;

                uint16_t charHeight = 0; memcpy(&charHeight, pData + (i * 20) + 10, 2);
                element->fontDef.rect.size.height = charHeight;

                int16_t xoffset = 0; memcpy(&xoffset, pData + (i * 20) + 12, 2);
                element->fontDef.xOffset = xoffset;

                int16_t yoffset = 0; memcpy(&yoffset, pData + (i * 20) + 14, 2);
                element->fontDef.yOffset = yoffset;

                int16_t xadvance = 0; memcpy(&xadvance, pData + (i * 20) + 16, 2);
                element->fontDef.xAdvance = xadvance;

                element->key = element->fontDef.charID;
                HASH_ADD_INT(_fontDefDictionary, key, element);

                validCharsString->insert(element->fontDef.charID);
            }
        }
		else if (blockId == 5) {
            /*
			 first 	4 	uint 	0+c*10 	These fields are repeated until all kerning pairs have been described
			 second 	4 	uint 	4+c*10
			 amount 	2 	int 	8+c*10
             */

            unsigned long count = blockSize / 20;

            for (unsigned long i = 0; i < count; i++)
			{

                uint32_t first = 0; memcpy(&first, pData + (i * 10), 4);
                uint32_t second = 0; memcpy(&second, pData + (i * 10) + 4, 4);
                int16_t amount = 0; memcpy(&amount, pData + (i * 10) + 8, 2);

                tKerningHashElement *element = (tKerningHashElement *)calloc( sizeof( *element ), 1 );
                element->amount = amount;
                element->key = (first<<16) | (second&0xffff);
                HASH_ADD_INT(_kerningDictionary,key, element);
            }
        }

        pData += blockSize; remains -= blockSize;
    }

    return validCharsString;
}

void CCBMFontConfiguration::parseImageFileName(std::string line, const std::string& fntFile)
{
    //////////////////////////////////////////////////////////////////////////
    // line to parse:
    // page id=0 file="bitmapFontTest.png"
    //////////////////////////////////////////////////////////////////////////

    // page ID. Sanity check
    auto index = line.find('=')+1;
    auto index2 = line.find(' ', index);
    std::string value = line.substr(index, index2-index);
    CCASSERT(atoi(value.c_str()) == 0, "LabelBMFont file could not be found");
    // file 
    index = line.find('"')+1;
    index2 = line.find('"', index);
    value = line.substr(index, index2-index);

    _atlasName = FileUtils::getInstance()->fullPathFromRelativeFile(value.c_str(), fntFile);
}

void CCBMFontConfiguration::parseInfoArguments(std::string line)
{
    //////////////////////////////////////////////////////////////////////////
    // possible lines to parse:
    // info face="Script" size=32 bold=0 italic=0 charset="" unicode=1 stretchH=100 smooth=1 aa=1 padding=1,4,3,2 spacing=0,0 outline=0
    // info face="Cracked" size=36 bold=0 italic=0 charset="" unicode=0 stretchH=100 smooth=1 aa=1 padding=0,0,0,0 spacing=1,1
    //////////////////////////////////////////////////////////////////////////

    // padding
    auto index = line.find("padding=");
    auto index2 = line.find(' ', index);
    std::string value = line.substr(index, index2-index);
    sscanf(value.c_str(), "padding=%d,%d,%d,%d", &_padding.top, &_padding.right, &_padding.bottom, &_padding.left);
    CCLOG("cocos2d: padding: %d,%d,%d,%d", _padding.left, _padding.top, _padding.right, _padding.bottom);
}

void CCBMFontConfiguration::parseCommonArguments(std::string line)
{
    //////////////////////////////////////////////////////////////////////////
    // line to parse:
    // common lineHeight=104 base=26 scaleW=1024 scaleH=512 pages=1 packed=0
    //////////////////////////////////////////////////////////////////////////

    // Height
    auto index = line.find("lineHeight=");
    auto index2 = line.find(' ', index);
    std::string value = line.substr(index, index2-index);
    sscanf(value.c_str(), "lineHeight=%d", &_commonHeight);
    // scaleW. sanity check
    index = line.find("scaleW=") + strlen("scaleW=");
    index2 = line.find(' ', index);
    value = line.substr(index, index2-index);
    CCASSERT(atoi(value.c_str()) <= Configuration::getInstance()->getMaxTextureSize(), "CCLabelBMFont: page can't be larger than supported");
    // scaleH. sanity check
    index = line.find("scaleH=") + strlen("scaleH=");
    index2 = line.find(' ', index);
    value = line.substr(index, index2-index);
    CCASSERT(atoi(value.c_str()) <= Configuration::getInstance()->getMaxTextureSize(), "CCLabelBMFont: page can't be larger than supported");
    // pages. sanity check
    index = line.find("pages=") + strlen("pages=");
    index2 = line.find(' ', index);
    value = line.substr(index, index2-index);
    CCASSERT(atoi(value.c_str()) == 1, "CCBitfontAtlas: only supports 1 page");

    // packed (ignore) What does this mean ??
}

void CCBMFontConfiguration::parseCharacterDefinition(std::string line, ccBMFontDef *characterDefinition)
{    
    //////////////////////////////////////////////////////////////////////////
    // line to parse:
    // char id=32   x=0     y=0     width=0     height=0     xoffset=0     yoffset=44    xadvance=14     page=0  chnl=0 
    //////////////////////////////////////////////////////////////////////////

    // Character ID
    auto index = line.find("id=");
    auto index2 = line.find(' ', index);
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
    sscanf(value.c_str(), "xoffset=%hd", &characterDefinition->xOffset);
    // Character yoffset
    index = line.find("yoffset=");
    index2 = line.find(' ', index);
    value = line.substr(index, index2-index);
    sscanf(value.c_str(), "yoffset=%hd", &characterDefinition->yOffset);
    // Character xadvance
    index = line.find("xadvance=");
    index2 = line.find(' ', index);
    value = line.substr(index, index2-index);
    sscanf(value.c_str(), "xadvance=%hd", &characterDefinition->xAdvance);
}

void CCBMFontConfiguration::parseKerningEntry(std::string line)
{        
    //////////////////////////////////////////////////////////////////////////
    // line to parse:
    // kerning first=121  second=44  amount=-7
    //////////////////////////////////////////////////////////////////////////

    // first
    int first;
    auto index = line.find("first=");
    auto index2 = line.find(' ', index);
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
    HASH_ADD_INT(_kerningDictionary,key, element);
}
//
//CCLabelBMFont
//

//LabelBMFont - Purge Cache
void LabelBMFont::purgeCachedData()
{
    FNTConfigRemoveCache();
}

LabelBMFont * LabelBMFont::create()
{
    LabelBMFont * pRet = new LabelBMFont();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

LabelBMFont * LabelBMFont::create(const std::string& str, const std::string& fntFile, float width, TextHAlignment alignment)
{
    return LabelBMFont::create(str, fntFile, width, alignment, Point::ZERO);
}

LabelBMFont * LabelBMFont::create(const std::string& str, const std::string& fntFile, float width)
{
    return LabelBMFont::create(str, fntFile, width, TextHAlignment::LEFT, Point::ZERO);
}

LabelBMFont * LabelBMFont::create(const std::string& str, const std::string& fntFile)
{
    return LabelBMFont::create(str, fntFile, kLabelAutomaticWidth, TextHAlignment::LEFT, Point::ZERO);
}

//LabelBMFont - Creation & Init
LabelBMFont *LabelBMFont::create(const std::string& str, const std::string& fntFile, float width/* = kLabelAutomaticWidth*/, TextHAlignment alignment/* = TextHAlignment::LEFT*/, Point imageOffset/* = Point::ZERO*/)
{
    LabelBMFont *ret = new LabelBMFont();
    if(ret && ret->initWithString(str, fntFile, width, alignment, imageOffset))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool LabelBMFont::init()
{
    return initWithString("", "", kLabelAutomaticWidth, TextHAlignment::LEFT, Point::ZERO);
}

bool LabelBMFont::initWithString(const std::string& theString, const std::string& fntFile, float width/* = kLabelAutomaticWidth*/, TextHAlignment alignment/* = TextHAlignment::LEFT*/, Point imageOffset/* = Point::ZERO*/)
{
    CCASSERT(!_configuration, "re-init is no longer supported");

    Texture2D *texture = nullptr;
    
    if (fntFile.size() > 0 )
    {
        CCBMFontConfiguration *newConf = FNTConfigLoadFile(fntFile);
        if (!newConf)
        {
            CCLOG("cocos2d: WARNING. LabelBMFont: Impossible to create font. Please check file: '%s'", fntFile.c_str());
            release();
            return false;
        }
        
        newConf->retain();
        CC_SAFE_RELEASE(_configuration);
        _configuration = newConf;
        
        _fntFile = fntFile;
        
        texture = Director::getInstance()->getTextureCache()->addImage(_configuration->getAtlasName());
    }
    else 
    {
        texture = new Texture2D();
        texture->autorelease();
    }

    if (SpriteBatchNode::initWithTexture(texture, static_cast<int>(theString.size())))
    {
        _width = width;
        _alignment = alignment;
        
        _displayedOpacity = _realOpacity = 255;
		_displayedColor = _realColor = Color3B::WHITE;
        _cascadeOpacityEnabled = true;
        _cascadeColorEnabled = true;
        
        _contentSize = Size::ZERO;
        
        _isOpacityModifyRGB = _textureAtlas->getTexture()->hasPremultipliedAlpha();
        _anchorPoint = Point(0.5f, 0.5f);
        
        _imageOffset = imageOffset;
        
        _reusedChar = Sprite::createWithTexture(_textureAtlas->getTexture(), Rect(0, 0, 0, 0));
        _reusedChar->retain();
        _reusedChar->setBatchNode(this);
        
        this->setString(theString, true);
        
        return true;
    }
    return false;
}

LabelBMFont::LabelBMFont()
: _string(nullptr)
, _initialString(nullptr)
, _alignment(TextHAlignment::CENTER)
, _width(-1.0f)
, _configuration(nullptr)
, _lineBreakWithoutSpaces(false)
, _imageOffset(Point::ZERO)
, _reusedChar(nullptr)
, _isOpacityModifyRGB(false)
{

}

LabelBMFont::~LabelBMFont()
{
    CC_SAFE_RELEASE(_reusedChar);
    CC_SAFE_DELETE_ARRAY(_string);
    CC_SAFE_DELETE_ARRAY(_initialString);
    CC_SAFE_RELEASE(_configuration);
}

// LabelBMFont - Atlas generation
int LabelBMFont::kerningAmountForFirst(unsigned short first, unsigned short second)
{
    int ret = 0;
    unsigned int key = (first<<16) | (second & 0xffff);

    if( _configuration->_kerningDictionary ) {
        tKerningHashElement *element = nullptr;
        HASH_FIND_INT(_configuration->_kerningDictionary, &key, element);        
        if(element)
            ret = element->amount;
    }
    return ret;
}

void LabelBMFont::createFontChars()
{
    int nextFontPositionX = 0;
    int nextFontPositionY = 0;
    unsigned short prev = -1;
    int kerningAmount = 0;

    Size tmpSize = Size::ZERO;

    int longestLine = 0;
    unsigned int totalHeight = 0;

    unsigned int quantityOfLines = 1;
    unsigned int stringLen = _string ? cc_wcslen(_string) : 0;
    if (stringLen == 0)
    {
        return;
    }

    set<unsigned int> *charSet = _configuration->getCharacterSet();

    for (unsigned int i = 0; i < stringLen - 1; ++i)
    {
        unsigned short c = _string[i];
        if (c == '\n')
        {
            quantityOfLines++;
        }
    }

    totalHeight = _configuration->_commonHeight * quantityOfLines;
    nextFontPositionY = 0-(_configuration->_commonHeight - _configuration->_commonHeight * quantityOfLines);
    
    Rect rect;
    ccBMFontDef fontDef;

    for (unsigned int i= 0; i < stringLen; i++)
    {
        unsigned short c = _string[i];

        if (c == '\n')
        {
            nextFontPositionX = 0;
            nextFontPositionY -= _configuration->_commonHeight;
            continue;
        }
        
        if (charSet->find(c) == charSet->end())
        {
            CCLOGWARN("cocos2d::LabelBMFont: Attempted to use character not defined in this bitmap: %d", c);
            continue;      
        }

        kerningAmount = this->kerningAmountForFirst(prev, c);
        
        tFontDefHashElement *element = nullptr;

        // unichar is a short, and an int is needed on HASH_FIND_INT
        unsigned int key = c;
        HASH_FIND_INT(_configuration->_fontDefDictionary, &key, element);
        if (! element)
        {
            CCLOGWARN("cocos2d::LabelBMFont: characer not found %d", c);
            continue;
        }

        fontDef = element->fontDef;

        rect = fontDef.rect;
        rect = CC_RECT_PIXELS_TO_POINTS(rect);

        rect.origin.x += _imageOffset.x;
        rect.origin.y += _imageOffset.y;

        Sprite *fontChar;

        bool hasSprite = true;
        fontChar = static_cast<Sprite*>( this->getChildByTag(i) );
        if(fontChar )
        {
            // Reusing previous Sprite
			fontChar->setVisible(true);
        }
        else
        {
            // New Sprite ? Set correct color, opacity, etc...
            if( 0 )
            {
				/* WIP: Doesn't support many features yet.
				 But this code is super fast. It doesn't create any sprite.
				 Ideal for big labels.
				 */
				fontChar = _reusedChar;
				fontChar->setBatchNode(nullptr);
				hasSprite = false;
			}
            else
            {
                fontChar = Sprite::createWithTexture(_textureAtlas->getTexture(), rect);
                addChild(fontChar, i, i);
			}
            
            // Apply label properties
			fontChar->setOpacityModifyRGB(_isOpacityModifyRGB);
            
			// Color MUST be set before opacity, since opacity might change color if OpacityModifyRGB is on
			fontChar->updateDisplayedColor(_displayedColor);
			fontChar->updateDisplayedOpacity(_displayedOpacity);
        }

        // updating previous sprite
        fontChar->setTextureRect(rect, false, rect.size);

        // See issue 1343. cast( signed short + unsigned integer ) == unsigned integer (sign is lost!)
        int yOffset = _configuration->_commonHeight - fontDef.yOffset;
        Point fontPos = Point( (float)nextFontPositionX + fontDef.xOffset + fontDef.rect.size.width*0.5f + kerningAmount,
            (float)nextFontPositionY + yOffset - rect.size.height*0.5f * CC_CONTENT_SCALE_FACTOR() );
        fontChar->setPosition(CC_POINT_PIXELS_TO_POINTS(fontPos));

        // update kerning
        nextFontPositionX += fontDef.xAdvance + kerningAmount;
        prev = c;

        if (longestLine < nextFontPositionX)
        {
            longestLine = nextFontPositionX;
        }
        
        if (! hasSprite)
        {
            updateQuadFromSprite(fontChar, i);
        }
    }

    // If the last character processed has an xAdvance which is less that the width of the characters image, then we need
    // to adjust the width of the string to take this into account, or the character will overlap the end of the bounding
    // box
    if (fontDef.xAdvance < fontDef.rect.size.width)
    {
        tmpSize.width = longestLine + fontDef.rect.size.width - fontDef.xAdvance;
    }
    else
    {
        tmpSize.width = longestLine;
    }
    tmpSize.height = totalHeight;

    this->setContentSize(CC_SIZE_PIXELS_TO_POINTS(tmpSize));
}

//LabelBMFont - LabelProtocol protocol
void LabelBMFont::setString(const std::string &newString)
{
    this->setString(newString, true);
}

void LabelBMFont::setString(const std::string &newString, bool needUpdateLabel)
{
    if (needUpdateLabel) {
        _initialStringUTF8 = newString;
    }
    unsigned short* utf16String = cc_utf8_to_utf16(newString.c_str());
    setString(utf16String, needUpdateLabel);
    CC_SAFE_DELETE_ARRAY(utf16String);
 }

void LabelBMFont::setString(unsigned short *newString, bool needUpdateLabel)
{
    if (!needUpdateLabel)
    {
        unsigned short* tmp = _string;
        _string = copyUTF16StringN(newString);
        CC_SAFE_DELETE_ARRAY(tmp);
    }
    else
    {
        unsigned short* tmp = _initialString;
        _initialString = copyUTF16StringN(newString);
        CC_SAFE_DELETE_ARRAY(tmp);
    }
    
    for(const auto &child : _children)
        child->setVisible(false);

    this->createFontChars();
    
    if (needUpdateLabel) {
        updateLabel();
    }
}

const std::string& LabelBMFont::getString() const
{
    return _initialStringUTF8;
}

void LabelBMFont::setCString(const char *label)
{
    setString(label);
}

/** Override synthesized setOpacity to recurse items */

void LabelBMFont::setOpacityModifyRGB(bool var)
{
    _isOpacityModifyRGB = var;
    for(const auto &child : _children) {
        child->setOpacityModifyRGB(_isOpacityModifyRGB);
    }
}
bool LabelBMFont::isOpacityModifyRGB() const
{
    return _isOpacityModifyRGB;
}

// LabelBMFont - AnchorPoint
void LabelBMFont::setAnchorPoint(const Point& point)
{
    if( ! point.equals(_anchorPoint))
    {
        SpriteBatchNode::setAnchorPoint(point);
        updateLabel();
    }
}

// LabelBMFont - Alignment
void LabelBMFont::updateLabel()
{
    this->setString(_initialString, false);

    if (_width > 0)
    {
        // Step 1: Make multiline
        vector<unsigned short> str_whole = cc_utf16_vec_from_utf16_str(_string);
        size_t stringLength = str_whole.size();
        vector<unsigned short> multiline_string;
        multiline_string.reserve( stringLength );
        vector<unsigned short> last_word;
        last_word.reserve( stringLength );

        unsigned int line = 1, i = 0;
        bool start_line = false, start_word = false;
        float startOfLine = -1, startOfWord = -1;
        int skip = 0;

        auto children = getChildren();
        for (int j = 0; j < children.size(); j++)
        {
            Sprite* characterSprite;
            unsigned int justSkipped = 0;
            
            while (!(characterSprite = static_cast<Sprite*>( this->getChildByTag(j + skip + justSkipped))) )
            {
                justSkipped++;
            }
            
            skip += justSkipped;

            if (i >= stringLength)
                break;

            unsigned short character = str_whole[i];

            if (!start_word)
            {
                startOfWord = getLetterPosXLeft( characterSprite );
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

                last_word.push_back('\n');
                multiline_string.insert(multiline_string.end(), last_word.begin(), last_word.end());
                last_word.clear();
                start_word = false;
                start_line = false;
                startOfWord = -1;
                startOfLine = -1;
                i+=justSkipped;
                line++;

                if (i >= stringLength)
                    break;

                character = str_whole[i];

                if (!startOfWord)
                {
                    startOfWord = getLetterPosXLeft( characterSprite );
                    start_word = true;
                }
                if (!startOfLine)
                {
                    startOfLine  = startOfWord;
                    start_line = true;
                }
                ++i;
                continue;
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
            if ( getLetterPosXRight( characterSprite ) - startOfLine > _width )
            {
                if (!_lineBreakWithoutSpaces)
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

                    if (i >= stringLength)
                        break;

                    if (!startOfWord)
                    {
                        startOfWord = getLetterPosXLeft( characterSprite );
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

        size_t size = multiline_string.size();
        unsigned short* str_new = new unsigned short[size + 1];

        for (size_t j = 0; j < size; ++j)
        {
            str_new[j] = multiline_string[j];
        }

        str_new[size] = '\0';

        this->setString(str_new, false);
        
        CC_SAFE_DELETE_ARRAY(str_new);
    }

    // Step 2: Make alignment
    if (_alignment != TextHAlignment::LEFT)
    {
        int i = 0;

        int lineNumber = 0;
        int str_len = cc_wcslen(_string);
        vector<unsigned short> last_line;
        for (int ctr = 0; ctr <= str_len; ++ctr)
        {
            if (_string[ctr] == '\n' || _string[ctr] == 0)
            {
                float lineWidth = 0.0f;
                size_t line_length = last_line.size();
				// if last line is empty we must just increase lineNumber and work with next line
                if (line_length == 0)
                {
                    lineNumber++;
                    continue;
                }
                int index = static_cast<int>(i + line_length - 1 + lineNumber);
                if (index < 0) continue;

                Sprite* lastChar = static_cast<Sprite*>( getChildByTag(index) );
                if ( lastChar == nullptr )
                    continue;

                lineWidth = lastChar->getPosition().x + lastChar->getContentSize().width/2.0f;

                float shift = 0;
                switch (_alignment)
                {
                case TextHAlignment::CENTER:
                    shift = getContentSize().width/2.0f - lineWidth/2.0f;
                    break;
                case TextHAlignment::RIGHT:
                    shift = getContentSize().width - lineWidth;
                    break;
                default:
                    break;
                }

                if (shift != 0)
                {
                    for (unsigned j = 0; j < line_length; j++)
                    {
                        index = i + j + lineNumber;
                        if (index < 0) continue;

                        Sprite* characterSprite = static_cast<Sprite*>( getChildByTag(index) );
                        characterSprite->setPosition(characterSprite->getPosition() + Point(shift, 0.0f));
                    }
                }

                i += line_length;
                lineNumber++;

                last_line.clear();
                continue;
            }

            last_line.push_back(_string[ctr]);
        }
    }
}

// LabelBMFont - Alignment
void LabelBMFont::setAlignment(TextHAlignment alignment)
{
    this->_alignment = alignment;
    updateLabel();
}

void LabelBMFont::setWidth(float width)
{
    this->_width = width;
    updateLabel();
}

void LabelBMFont::setLineBreakWithoutSpace( bool breakWithoutSpace )
{
    _lineBreakWithoutSpaces = breakWithoutSpace;
    updateLabel();
}

void LabelBMFont::setScale(float scale)
{
    SpriteBatchNode::setScale(scale);
    updateLabel();
}

void LabelBMFont::setScaleX(float scaleX)
{
    SpriteBatchNode::setScaleX(scaleX);
    updateLabel();
}

void LabelBMFont::setScaleY(float scaleY)
{
    SpriteBatchNode::setScaleY(scaleY);
    updateLabel();
}

float LabelBMFont::getLetterPosXLeft( Sprite* sp )
{
    return sp->getPosition().x * _scaleX - (sp->getContentSize().width * _scaleX * sp->getAnchorPoint().x);
}

float LabelBMFont::getLetterPosXRight( Sprite* sp )
{
    return sp->getPosition().x * _scaleX + (sp->getContentSize().width * _scaleX * sp->getAnchorPoint().x);
}

// LabelBMFont - FntFile
void LabelBMFont::setFntFile(const std::string& fntFile)
{
    if (_fntFile.compare(fntFile) != 0)
    {
        CCBMFontConfiguration *newConf = FNTConfigLoadFile(fntFile);

        CCASSERT( newConf, "CCLabelBMFont: Impossible to create font. Please check file");

        _fntFile = fntFile;

        CC_SAFE_RETAIN(newConf);
        CC_SAFE_RELEASE(_configuration);
        _configuration = newConf;

        this->setTexture(Director::getInstance()->getTextureCache()->addImage(_configuration->getAtlasName()));
        this->createFontChars();
    }
}

const std::string& LabelBMFont::getFntFile() const
{
    return _fntFile;
}

std::string LabelBMFont::getDescription() const
{
    return StringUtils::format("<LabelBMFont | Tag = %d, Label = '%s'>", _tag, _initialStringUTF8.c_str());
}

//LabelBMFont - Debug draw
#if CC_LABELBMFONT_DEBUG_DRAW
void LabelBMFont::draw()
{
    SpriteBatchNode::draw();
    const Size& s = this->getContentSize();
    Point vertices[4]={
        Point(0,0),Point(s.width,0),
        Point(s.width,s.height),Point(0,s.height),
    };
    ccDrawPoly(vertices, 4, true);
}

#endif // CC_LABELBMFONT_DEBUG_DRAW

NS_CC_END
