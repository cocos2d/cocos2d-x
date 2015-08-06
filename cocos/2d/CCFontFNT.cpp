/****************************************************************************
 Copyright (c) 2013      Zynga Inc.
 Copyright (c) 2013-2015 Chukong Technologies Inc.
 
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

#include "2d/CCFontFNT.h"
#include <set>
#include "base/uthash.h"
#include "2d/CCFontAtlas.h"
#include "platform/CCFileUtils.h"
#include "base/CCConfiguration.h"
#include "base/CCDirector.h"
#include "base/CCMap.h"
#include "renderer/CCTextureCache.h"

#include "deprecated/CCString.h"

using namespace std;
NS_CC_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup label
 * @{
 */

enum {
    kLabelAutomaticWidth = -1,
};

struct _FontDefHashElement;

/**
@struct BMFontDef
BMFont definition
*/
typedef struct _BMFontDef {
    //! ID of the character
    unsigned int charID;
    //! origin and size of the font
    Rect rect;
    //! The X amount the image should be offset when drawing the image (in pixels)
    short xOffset;
    //! The Y amount the image should be offset when drawing the image (in pixels)
    short yOffset;
    //! The amount to move the current position after drawing the character (in pixels)
    short xAdvance;
} BMFontDef;

/** @struct BMFontPadding
BMFont padding
@since v0.8.2
*/
typedef struct _BMFontPadding {
    /// padding left
    int    left;
    /// padding top
    int top;
    /// padding right
    int right;
    /// padding bottom
    int bottom;
} BMFontPadding;

typedef struct _FontDefHashElement
{
    unsigned int    key;        // key. Font Unicode value
    BMFontDef       fontDef;    // font definition
    UT_hash_handle  hh;
} tFontDefHashElement;

// Equal function for targetSet.
typedef struct _KerningHashElement
{
    int				key;        // key for the hash. 16-bit for 1st element, 16-bit for 2nd element
    int				amount;
    UT_hash_handle	hh;
} tKerningHashElement;

/** @brief BMFontConfiguration has parsed configuration of the the .fnt file
@since v0.8
*/
class CC_DLL BMFontConfiguration : public Ref
{
    // FIXME: Creating a public interface so that the bitmapFontArray[] is accessible
public://@public
    // BMFont definitions
    tFontDefHashElement *_fontDefDictionary;

    //! FNTConfig: Common Height Should be signed (issue #1343)
    int _commonHeight;
    //! Padding
    BMFontPadding    _padding;
    //! atlas name
    std::string _atlasName;
    //! values for kerning
    tKerningHashElement *_kerningDictionary;
    
    // Character Set defines the letters that actually exist in the font
    std::set<unsigned int> *_characterSet;
public:
    /**
     * @js ctor
     */
    BMFontConfiguration();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~BMFontConfiguration();
    /**
     * @js NA
     * @lua NA
     */
    std::string description() const;

    /** allocates a BMFontConfiguration with a FNT file */
    static BMFontConfiguration * create(const std::string& FNTfile);

    /** initializes a BitmapFontConfiguration with a FNT file */
    bool initWithFNTfile(const std::string& FNTfile);
    
    inline const std::string& getAtlasName(){ return _atlasName; }
    inline void setAtlasName(const std::string& atlasName) { _atlasName = atlasName; }
    
    std::set<unsigned int>* getCharacterSet() const;
private:
    std::set<unsigned int>* parseConfigFile(const std::string& controlFile);
    std::set<unsigned int>* parseBinaryConfigFile(unsigned char* pData, unsigned long size, const std::string& controlFile);
    void parseCharacterDefinition(const char* line, BMFontDef *characterDefinition);
    void parseInfoArguments(const char* line);
    void parseCommonArguments(const char* line);
    void parseImageFileName(const char* line, const std::string& fntFile);
    void parseKerningEntry(const char* line);
    void purgeKerningDictionary();
    void purgeFontDefDictionary();
};

//
//FNTConfig Cache - free functions
//
static Map<std::string, BMFontConfiguration*>* s_configurations = nullptr;

BMFontConfiguration* FNTConfigLoadFile(const std::string& fntFile)
{
    BMFontConfiguration* ret = nullptr;

    if( s_configurations == nullptr )
    {
        s_configurations = new (std::nothrow) Map<std::string, BMFontConfiguration*>();
    }

    ret = s_configurations->at(fntFile);
    if( ret == nullptr )
    {
        ret = BMFontConfiguration::create(fntFile.c_str());
        if (ret)
        {
            s_configurations->insert(fntFile, ret);
        }        
    }

    return ret;
}

//
//BitmapFontConfiguration
//

BMFontConfiguration * BMFontConfiguration::create(const std::string& FNTfile)
{
    BMFontConfiguration * ret = new (std::nothrow) BMFontConfiguration();
    if (ret->initWithFNTfile(FNTfile))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool BMFontConfiguration::initWithFNTfile(const std::string& FNTfile)
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

std::set<unsigned int>* BMFontConfiguration::getCharacterSet() const
{
    return _characterSet;
}

BMFontConfiguration::BMFontConfiguration()
: _fontDefDictionary(nullptr)
, _commonHeight(0)
, _kerningDictionary(nullptr)
, _characterSet(nullptr)
{

}

BMFontConfiguration::~BMFontConfiguration()
{
    CCLOGINFO( "deallocing BMFontConfiguration: %p", this );
    this->purgeFontDefDictionary();
    this->purgeKerningDictionary();
    _atlasName.clear();
    CC_SAFE_DELETE(_characterSet);
}

std::string BMFontConfiguration::description(void) const
{
    return StringUtils::format(
        "<BMFontConfiguration = " CC_FORMAT_PRINTF_SIZE_T " | Glphys:%d Kernings:%d | Image = %s>",
        (size_t)this,
        HASH_COUNT(_fontDefDictionary),
        HASH_COUNT(_kerningDictionary),
        _atlasName.c_str()
    );
}

void BMFontConfiguration::purgeKerningDictionary()
{
    tKerningHashElement *current;
    while(_kerningDictionary) 
    {
        current = _kerningDictionary; 
        HASH_DEL(_kerningDictionary,current);
        free(current);
    }
}

void BMFontConfiguration::purgeFontDefDictionary()
{    
    tFontDefHashElement *current, *tmp;

    HASH_ITER(hh, _fontDefDictionary, current, tmp) {
        HASH_DEL(_fontDefDictionary, current);
        free(current);
    }
}

std::set<unsigned int>* BMFontConfiguration::parseConfigFile(const std::string& controlFile)
{
    Data data = FileUtils::getInstance()->getDataFromFile(controlFile);
    CCASSERT((!data.isNull()), "BMFontConfiguration::parseConfigFile | Open file error.");

    if (memcmp("BMF", data.getBytes(), 3) == 0) {
        std::set<unsigned int>* ret = parseBinaryConfigFile(data.getBytes(), data.getSize(), controlFile);
        return ret;
    }

    auto contents = (const char*)data.getBytes();
    if (contents[0] == 0)
    {
        CCLOG("cocos2d: Error parsing FNTfile %s", controlFile.c_str());
        return nullptr;
    }

    std::set<unsigned int> *validCharsString = new std::set<unsigned int>();
    
    auto contentsLen = data.getSize();
    char line[512];
    
    auto next = strchr(contents, '\n');
    auto base = contents;
    int lineLength = 0;
    int parseCount = 0;
    while (next)
    {
        lineLength = ((int)(next - base));
        memcpy(line, contents + parseCount, lineLength);
        line[lineLength] = 0;

        parseCount += lineLength + 1;
        if (parseCount < contentsLen)
        {
            base = next + 1;
            next = strchr(base, '\n');
        } 
        else
        {
            next = nullptr;
        }

        if (memcmp(line, "info face", 9) == 0)
        {
            // FIXME: info parsing is incomplete
            // Not needed for the Hiero editors, but needed for the AngelCode editor
            //            [self parseInfoArguments:line];
            this->parseInfoArguments(line);
        }
        // Check to see if the start of the line is something we are interested in
        else if (memcmp(line, "common lineHeight", 17) == 0)
        {
            this->parseCommonArguments(line);
        }
        else if (memcmp(line, "page id", 7) == 0)
        {
            this->parseImageFileName(line, controlFile);
        }
        else if (memcmp(line, "chars c", 7) == 0)
        {
            // Ignore this line
        }
        else if (memcmp(line, "char", 4) == 0)
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
        else if (memcmp(line, "kerning first", 13) == 0)
        {
            this->parseKerningEntry(line);
        }
    }
    
    return validCharsString;
}

std::set<unsigned int>* BMFontConfiguration::parseBinaryConfigFile(unsigned char* pData, unsigned long size, const std::string& controlFile)
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
             fontSize       2   int      0
             bitField       1   bits     2  bit 0: smooth, bit 1: unicode, bit 2: italic, bit 3: bold, bit 4: fixedHeigth, bits 5-7: reserved
             charSet        1   uint     3
             stretchH       2   uint     4
             aa             1   uint     6
             paddingUp      1   uint     7
             paddingRight   1   uint     8
             paddingDown    1   uint     9
             paddingLeft    1   uint     10
             spacingHoriz   1   uint     11
             spacingVert    1   uint     12
             outline        1   uint     13 added with version 2
             fontName       n+1 string   14 null terminated string with length n
             */

            _padding.top = (unsigned char)pData[7];
            _padding.right = (unsigned char)pData[8];
            _padding.bottom = (unsigned char)pData[9];
            _padding.left = (unsigned char)pData[10];
        }
		else if (blockId == 2)
		{
            /*
             lineHeight 2   uint    0
             base       2   uint    2
             scaleW     2   uint    4
             scaleH     2   uint    6
             pages      2   uint    8
             bitField   1   bits    10  bits 0-6: reserved, bit 7: packed
             alphaChnl  1   uint    11
             redChnl    1   uint    12
             greenChnl  1   uint    13
             blueChnl   1   uint    14
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
             id         4   uint    0+c*20  These fields are repeated until all characters have been described
             x          2   uint    4+c*20
             y          2   uint    6+c*20
             width      2   uint    8+c*20
             height     2   uint    10+c*20
             xoffset    2   int     12+c*20
             yoffset    2   int     14+c*20
             xadvance   2   int     16+c*20
             page       1   uint    18+c*20
             chnl       1   uint    19+c*20
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
             first  4   uint    0+c*10 	These fields are repeated until all kerning pairs have been described
             second 4   uint    4+c*10
             amount 2   int     8+c*10
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

void BMFontConfiguration::parseImageFileName(const char* line, const std::string& fntFile)
{
    //////////////////////////////////////////////////////////////////////////
    // line to parse:
    // page id=0 file="bitmapFontTest.png"
    //////////////////////////////////////////////////////////////////////////

    // page ID. Sanity check
    int pageId;
    sscanf(line, "page id=%d", &pageId);
    CCASSERT(pageId == 0, "LabelBMFont file could not be found");
    // file 
    char fileName[255];
    sscanf(strchr(line,'"') + 1, "%[^\"]", fileName);
    _atlasName = FileUtils::getInstance()->fullPathFromRelativeFile(fileName, fntFile);
}

void BMFontConfiguration::parseInfoArguments(const char* line)
{
    //////////////////////////////////////////////////////////////////////////
    // possible lines to parse:
    // info face="Script" size=32 bold=0 italic=0 charset="" unicode=1 stretchH=100 smooth=1 aa=1 padding=1,4,3,2 spacing=0,0 outline=0
    // info face="Cracked" size=36 bold=0 italic=0 charset="" unicode=0 stretchH=100 smooth=1 aa=1 padding=0,0,0,0 spacing=1,1
    //////////////////////////////////////////////////////////////////////////

    // padding
    sscanf(strstr(line,"padding=") + 8, "%d,%d,%d,%d", &_padding.top, &_padding.right, &_padding.bottom, &_padding.left);
    //CCLOG("cocos2d: padding: %d,%d,%d,%d", _padding.left, _padding.top, _padding.right, _padding.bottom);
}

void BMFontConfiguration::parseCommonArguments(const char* line)
{
    //////////////////////////////////////////////////////////////////////////
    // line to parse:
    // common lineHeight=104 base=26 scaleW=1024 scaleH=512 pages=1 packed=0
    //////////////////////////////////////////////////////////////////////////
  
    // Height
    auto tmp = strstr(line, "lineHeight=") + 11;
    sscanf(tmp, "%d", &_commonHeight);
    // scaleW. sanity check
    int value;
    tmp = strstr(tmp, "scaleW=") + 7;
    sscanf(tmp, "%d", &value);

    int maxTextureSize = Configuration::getInstance()->getMaxTextureSize();
    CCASSERT(value <= maxTextureSize, "CCLabelBMFont: page can't be larger than supported");

    // scaleH. sanity check
    tmp = strstr(tmp, "scaleH=") + 7;
    sscanf(tmp, "%d", &value);
    CCASSERT(value <= maxTextureSize, "CCLabelBMFont: page can't be larger than supported");

    // pages. sanity check
    tmp = strstr(tmp, "pages=") + 6;
    sscanf(tmp, "%d", &value);
    CCASSERT(value == 1, "CCBitfontAtlas: only supports 1 page");

    // packed (ignore) What does this mean ??
}

void BMFontConfiguration::parseCharacterDefinition(const char* line, BMFontDef *characterDefinition)
{    
    //////////////////////////////////////////////////////////////////////////
    // line to parse:
    // char id=32   x=0     y=0     width=0     height=0     xoffset=0     yoffset=44    xadvance=14     page=0  chnl=0 
    //////////////////////////////////////////////////////////////////////////

    // Character ID
    auto tmp = strstr(line, "id=") + 3;
    sscanf(tmp, "%u", &characterDefinition->charID);

    // Character x
    tmp = strstr(tmp, "x=") + 2;
    sscanf(tmp, "%f", &characterDefinition->rect.origin.x);
    // Character y
    tmp = strstr(tmp, "y=") + 2;
    sscanf(tmp, "%f", &characterDefinition->rect.origin.y);
    // Character width
    tmp = strstr(tmp, "width=") + 6;
    sscanf(tmp, "%f", &characterDefinition->rect.size.width);
    // Character height
    tmp = strstr(tmp, "height=") + 7;
    sscanf(tmp, "%f", &characterDefinition->rect.size.height);
    // Character xoffset
    tmp = strstr(tmp, "xoffset=") + 8;
    sscanf(tmp, "%hd", &characterDefinition->xOffset);
    // Character yoffset
    tmp = strstr(tmp, "yoffset=") + 8;
    sscanf(tmp, "%hd", &characterDefinition->yOffset);
    // Character xadvance
    tmp = strstr(tmp, "xadvance=") + 9;
    sscanf(tmp, "%hd", &characterDefinition->xAdvance);
}

void BMFontConfiguration::parseKerningEntry(const char* line)
{        
    //////////////////////////////////////////////////////////////////////////
    // line to parse:
    // kerning first=121  second=44  amount=-7
    //////////////////////////////////////////////////////////////////////////

    int first, second, amount;
    auto tmp = strstr(line, "first=") + 6;
    sscanf(tmp, "%d", &first);

    tmp = strstr(tmp, "second=") + 7;
    sscanf(tmp, "%d", &second);

    tmp = strstr(tmp, "amount=") + 7;
    sscanf(tmp, "%d", &amount);

    tKerningHashElement *element = (tKerningHashElement *)calloc( sizeof( *element ), 1 );
    element->amount = amount;
    element->key = (first<<16) | (second&0xffff);
    HASH_ADD_INT(_kerningDictionary,key, element);
}

FontFNT * FontFNT::create(const std::string& fntFilePath, const Vec2& imageOffset /* = Vec2::ZERO */)
{
    BMFontConfiguration *newConf = FNTConfigLoadFile(fntFilePath);
    if (!newConf)
        return nullptr;
    
    // add the texture
    Texture2D *tempTexture = Director::getInstance()->getTextureCache()->addImage(newConf->getAtlasName());
    if (!tempTexture)
    {
        return nullptr;
    }
    
    FontFNT *tempFont =  new FontFNT(newConf,imageOffset);
    
    if (!tempFont)
    {
        return nullptr;
    }
    tempFont->autorelease();
    return tempFont;
}

FontFNT::FontFNT(BMFontConfiguration *theContfig, const Vec2& imageOffset /* = Vec2::ZERO */)
:_configuration(theContfig)
,_imageOffset(CC_POINT_PIXELS_TO_POINTS(imageOffset))
{
    _configuration->retain();
}

FontFNT::~FontFNT()
{
    _configuration->release();
}

void FontFNT::purgeCachedData()
{
    if (s_configurations)
    {
        s_configurations->clear();
        CC_SAFE_DELETE(s_configurations);
    }
}

int * FontFNT::getHorizontalKerningForTextUTF16(const std::u16string& text, int &outNumLetters) const
{
    outNumLetters = static_cast<int>(text.length());
    
    if (!outNumLetters)
        return 0;
    
    int *sizes = new int[outNumLetters];
    if (!sizes)
        return 0;
    
    for (int c = 0; c < outNumLetters; ++c)
    {
        if (c < (outNumLetters-1))
            sizes[c] = getHorizontalKerningForChars(text[c], text[c+1]);
        else
            sizes[c] = 0;
    }
    
    return sizes;
}

int  FontFNT::getHorizontalKerningForChars(unsigned short firstChar, unsigned short secondChar) const
{
    int ret = 0;
    unsigned int key = (firstChar << 16) | (secondChar & 0xffff);
    
    if (_configuration->_kerningDictionary)
    {
        tKerningHashElement *element = nullptr;
        HASH_FIND_INT(_configuration->_kerningDictionary, &key, element);
        
        if (element)
            ret = element->amount;
    }
    
    return ret;
}

FontAtlas * FontFNT::createFontAtlas()
{
    FontAtlas *tempAtlas = new (std::nothrow) FontAtlas(*this);
    if (!tempAtlas)
        return nullptr;
    
    // check that everything is fine with the BMFontCofniguration
    if (!_configuration->_fontDefDictionary)
        return nullptr;
    
    size_t numGlyphs = _configuration->_characterSet->size();
    if (!numGlyphs)
        return nullptr;
    
    if (_configuration->_commonHeight == 0)
        return nullptr;
    
    // commone height
    tempAtlas->setLineHeight(_configuration->_commonHeight);
    
    
    BMFontDef fontDef;
    tFontDefHashElement *currentElement, *tmp;
    
    // Purge uniform hash
    HASH_ITER(hh, _configuration->_fontDefDictionary, currentElement, tmp)
    {
        
        FontLetterDefinition tempDefinition;
        
        fontDef = currentElement->fontDef;
        Rect tempRect;
        
        tempRect = fontDef.rect;
        tempRect = CC_RECT_PIXELS_TO_POINTS(tempRect);
        
        tempDefinition.offsetX  = fontDef.xOffset;
        tempDefinition.offsetY  = fontDef.yOffset;
        
        tempDefinition.U        = tempRect.origin.x + _imageOffset.x;
        tempDefinition.V        = tempRect.origin.y + _imageOffset.y;
        
        tempDefinition.width    = tempRect.size.width;
        tempDefinition.height   = tempRect.size.height;
        
        //carloX: only one texture supported FOR NOW
        tempDefinition.textureID = 0;
        
        tempDefinition.validDefinition = true;
        tempDefinition.xAdvance = fontDef.xAdvance;
        // add the new definition
        tempAtlas->addLetterDefinition(fontDef.charID,tempDefinition);
    }
    
    // add the texture (only one texture for now)
    
    Texture2D *tempTexture = Director::getInstance()->getTextureCache()->addImage(_configuration->getAtlasName());
    if (!tempTexture)
        return 0;
    
    // add the texture
    tempAtlas->addTexture(tempTexture, 0);
    
    // done
    return tempAtlas;
}


NS_CC_END
