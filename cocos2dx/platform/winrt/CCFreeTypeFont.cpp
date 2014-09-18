/****************************************************************************
 Copyright (c) 2013      cocos2d-x.org   http://cocos2d-x.org
 Copyright (c) Microsoft Open Technologies, Inc.

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

#include "CCFreeTypeFont.h"
#include "CCDirector.h"
#include "platform/CCFileUtils.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
#include <dwrite.h>
#endif
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

NS_CC_BEGIN

static map<std::string, FontBufferInfo> s_fontsNames;
static vector<pair<FT_Face, unsigned char*>> s_faces;
static FT_Library s_FreeTypeLibrary = nullptr;

CCFreeTypeFont::CCFreeTypeFont() 
    :m_space(" ")
    , m_face(nullptr)
{

}

CCFreeTypeFont::~CCFreeTypeFont() 
{
    reset();
}

void CCFreeTypeFont::reset()
{
    for(auto line:m_lines)
    {
        line->glyphs.clear();
        delete line;
    }

    m_lines.clear();

	if(m_face)
	{
		FT_Done_Face(m_face);
	    m_face = nullptr;
	}

}

bool CCFreeTypeFont::initWithString(
	const char* pText, 
	const char* pFontName,
	int         nSize,
    int         inWidth,
    int         inHeight )
{
	FT_Error error = 0;
	unsigned long size = 0;
    unsigned char* pBuffer = nullptr;

    CCSize winSize = CCDirector::sharedDirector()->getWinSizeInPixels();
    m_windowWidth = (int)winSize.width;

    m_inWidth = inWidth;
    m_inHeight = inHeight;

    // check the cache for the font file buffer
    auto ittFontNames = s_fontsNames.find(pFontName);
    if(ittFontNames != s_fontsNames.end()) 
    {
        pBuffer =ittFontNames->second.pBuffer;
        size = ittFontNames->second.size;
    }
    
	if(!pBuffer)
    {
        // attempt to load font from Resources fonts folder
        pBuffer = loadFont(pFontName, &size);
	    if(!pBuffer)
	    {
         // attempt to load font from System fonts folder
           pBuffer = loadSystemFont(pFontName, &size);
	    }
        if(!pBuffer)
        {
            // attempt to load default font from Resources fonts folder
		    pBuffer = loadFont("Arial", &size);
        }
        if(!pBuffer)
        {
            // attempt to load default font from System fonts folder
            pBuffer = loadSystemFont("Arial", &size);
        }

        if(!pBuffer) // font not found!
            return false;

        // cache the font file buffer
        FontBufferInfo info;
        info.pBuffer = pBuffer;
        info.size = size;
        s_fontsNames[pFontName]=info;
    }

    m_fontName = pFontName;
	m_text = pText;

	if(!s_FreeTypeLibrary)
	{
		error = FT_Init_FreeType(&s_FreeTypeLibrary);
	}

    for (auto i = s_faces.begin(); !error && i != s_faces.end(); ++i)
    {
        error = FT_Set_Char_Size(i->first, nSize << 6, nSize << 6, 72, 72);
    }

	if(!error && !m_face)
	{
		error = FT_New_Memory_Face(s_FreeTypeLibrary, pBuffer, size, 0, &m_face);
	}

    if(!error)
    {
        error = FT_Select_Charmap(m_face, FT_ENCODING_UNICODE);
    }

    if(!error)
	    error = FT_Set_Char_Size(m_face,nSize<<6,nSize<<6,72,72);

    if(!error)
	    error = initGlyphs(pText);

	return error == 0;
}

unsigned char* CCFreeTypeFont::getBitmap(CCImage::ETextAlign eAlignMask, int* outWidth, int* outHeight)
{
    int lineNumber = 0;
    int totalLines = m_lines.size();

    m_width = m_inWidth ? m_inWidth : m_textWidth;
    m_height = m_inHeight ? m_inHeight : m_textHeight;
    
    unsigned int size = m_width * m_height * 4;
    unsigned char* pBuffer = new unsigned char[size];
    if(!pBuffer)
    {
        return nullptr;
    }
    memset(pBuffer, 0, size);

    for (auto line = m_lines.begin() ; line != m_lines.end(); ++line)
    {
        FT_Vector pen = getPenForAlignment(*line, eAlignMask, lineNumber, totalLines);
        drawText(*line, pBuffer, &pen);
        lineNumber++;
    }
    *outWidth = m_width;
    *outHeight = m_height;

    reset();

    return pBuffer;
}

#if CC_TARGET_PLATFORM == CC_PLATFORM_WP8

const char*  CCFreeTypeFont::getSystemFontFileName(SystemFont systemFont)
{
    const char* fontFileName;
    switch (systemFont)
    {
        /* UI Fonts */
    case SystemFont::SEGOE_WP:
        fontFileName = "SegoeWP.ttf";
        break;
    case SystemFont::DENG_XIAN:
        fontFileName = "DengXian.ttf";
        break;
    case SystemFont::MICROSOFT_MHEI:
        fontFileName = "MSMhei.ttf";
        break;
    case SystemFont::YU_GOTHIC:
        fontFileName = "YuGothic.ttf";
        break;
    case SystemFont::MICROSOFT_NEO_GOTHIC:
        fontFileName = "MSNeoGothic.ttf";
        break;
    case SystemFont::SEGOE_UI:
        fontFileName = "SegoeUI.ttf";
        break;
    case SystemFont::NIRMALA_UI:
        fontFileName = "Nirmala.ttf";
        break;
    case SystemFont::LEELAWADEE:
        fontFileName = "leelawad.ttf";
        break;
    case SystemFont::SEGOE_UI_SYMBOL:
        fontFileName = "seguisym.ttf";
        break;
        /* Text display fonts */
    case SystemFont::EBRIMA:
        fontFileName = "ebrima.ttf";
        break;
    case SystemFont::ESTRANGELO_EDESSA:
        fontFileName = "estre.ttf";
        break;
    case SystemFont::GADUGI:
        fontFileName = "gadugi.ttf";
        break;
    case SystemFont::KHMER_UI:
        fontFileName = "KhmerUI.ttf";
        break;
    case SystemFont::LAO_UI:
        fontFileName = "LaoUI.ttf";
        break;
    case SystemFont::MICROSOFT_HIMALAYA:
        fontFileName = "himalaya.ttf";
        break;
    case SystemFont::MICROSOFT_NEW_TAI_LUE:
        fontFileName = "ntailu.ttf";
        break;
    case SystemFont::MICROSOFT_TAI_LE:
        fontFileName = "taile.ttf";
        break;
    case SystemFont::MICROSOFT_UIGHUR:
        fontFileName = "msuighur.ttf";
        break;
    case SystemFont::MICROSOFT_YI_BAITI:
        fontFileName = "msyi.ttf";
        break;
    case SystemFont::MONGOLIAN_BAITI:
        fontFileName = "monbaiti.ttf";
        break;
    case SystemFont::MV_BOLI:
        fontFileName = "mvboli.ttf";
        break;
    case SystemFont::PHAGS_PA:
        fontFileName = "phagspa.ttf";
        break;
    case SystemFont::SIM_SUN:
        fontFileName = "simsun.ttc";
        break;
    case SystemFont::URDU_TYPESETTING:
        fontFileName = "UrdType.ttf";
        break;
        /* Additional fonts */
    case SystemFont::ARIAL:
        fontFileName = "arial.ttf";
        break;
    case SystemFont::ARIAL_BLACK:
        fontFileName = "ariblk.ttf";
        break;
    case SystemFont::CALIBRI:
        fontFileName = "calibri.ttf";
        break;
    case SystemFont::CALIBRI_LIGHT:
        fontFileName = "calibril.ttf";
        break;
    case SystemFont::COMIC_SANS_MS:
        fontFileName = "comic.ttf";
        break;
    case SystemFont::COURIER_NEW:
        fontFileName = "cour.ttf";
        break;
    case SystemFont::GEORGIA:
        fontFileName = "georgia.ttf";
        break;
    case SystemFont::LUCIDA_SANS_UNICODE:
        fontFileName = "l_10646.ttf";
        break;
    case SystemFont::TAHOMA:
        fontFileName = "tahoma.ttf";
        break;
    case SystemFont::TIMES_NEW_ROMAN:
        fontFileName = "times.ttf";
        break;
    case SystemFont::TREBUCHET_MS:
        fontFileName = "trebuc.ttf";
        break;
    case SystemFont::VERDANA:
        fontFileName = "verdana.ttf";
        break;
        /* Mathematical and symbol fonts */
    case SystemFont::CAMBRIA_AND_CAMBRIA_MATH:
        fontFileName = "cambria.ttc";
        break;
    case SystemFont::WINGDINGS:
        fontFileName = "webdings.ttf";
        break;
    case SystemFont::WEBDINGS:
        fontFileName = "wingding.ttf";
        break;
    default:
        fontFileName = nullptr;
        break;
    }
    return fontFileName;
}

#endif

void CCFreeTypeFont::setFallbackFonts(const std::vector<const char*>& fonts)
{
    // Ensure the library is initialised
    if (!s_FreeTypeLibrary)
    {
        FT_Error error = FT_Init_FreeType(&s_FreeTypeLibrary);
        if (error != 0)
            return;
    }

    // Clear out the system fonts first
    for (auto i = s_faces.begin(); i != s_faces.end(); ++i)
    {
        FT_Done_Face(i->first);
        delete [] i->second;
    }
    s_faces.clear();
    s_faces.reserve(fonts.size());

    // Load the system font files that match the enums
    for (auto i = fonts.begin(); i != fonts.end(); ++i)
    {
        FT_Face face;
        unsigned long fontSize = 0;
        // Try as a system font first
        unsigned char* fontData = loadSystemFont(*i, &fontSize);
        if (!fontData)
        {
            // Else try loading as a supplied font
            fontData = loadFont(*i, &fontSize);
        }

        if (fontData)
        {
            FT_Error error = FT_New_Memory_Face(s_FreeTypeLibrary, fontData, fontSize, 0, &face);
            if (!error)
                error = FT_Select_Charmap(face, FT_ENCODING_UNICODE);

            if (!error)
                s_faces.push_back(pair<FT_Face, unsigned char*>(face, fontData));
        }
    } // end for systemFonts
}

FT_Vector CCFreeTypeFont::getPenForAlignment(FTLineInfo* pInfo, CCImage::ETextAlign eAlignMask,int lineNumber, int totalLines)
{
    FT_Error error = 0;
    FT_Vector pen;
    
    int top;
    int stringWidth  = pInfo->bbox.xMax - pInfo->bbox.xMin;
    int maxLineNumber = totalLines - 1;
    pen.x = 0;
    pen.y = 0;

    switch(eAlignMask)
    {
        case CCImage::ETextAlign::kAlignTop: // Horizontal center and vertical top.
            pen.x = ((m_width  - stringWidth) / 2) - pInfo->bbox.xMin;
            pen.y = pInfo->bbox.yMax + (lineNumber * m_lineHeight);		    
 		    break;
			
        case CCImage::ETextAlign::kAlignTopLeft: // Horizontal left and vertical top.
            pen.x -=pInfo->bbox.xMin;
            pen.y = pInfo->bbox.yMax + (lineNumber * m_lineHeight);		    
 		    break;

	    case CCImage::ETextAlign::kAlignTopRight: // Horizontal right and vertical top.
            pen.x = m_width - stringWidth - pInfo->bbox.xMin;
            pen.y = pInfo->bbox.yMax + (lineNumber * m_lineHeight);		    
		    break;
 
	    case CCImage::ETextAlign::kAlignBottomRight: // Horizontal right and vertical bottom.
            pen.x = m_width - stringWidth - pInfo->bbox.xMin;
            pen.y = m_height + pInfo->bbox.yMin - ((maxLineNumber - lineNumber) * m_lineHeight);
		    break;

	    case CCImage::ETextAlign::kAlignBottom: // Horizontal center and vertical bottom.
            pen.x = ((m_width  - stringWidth) / 2) - pInfo->bbox.xMin;
            pen.y = m_height + pInfo->bbox.yMin - ((maxLineNumber - lineNumber) * m_lineHeight);
		    break;

	    case CCImage::ETextAlign::kAlignBottomLeft: // Horizontal left and vertical bottom.
            pen.x -=pInfo->bbox.xMin;
            top = (m_height - m_textHeight) / 2;
            pen.y = m_height + pInfo->bbox.yMin - ((maxLineNumber - lineNumber) * m_lineHeight);
  		    break;

	    case CCImage::ETextAlign::kAlignCenter: // Horizontal center and vertical center
            pen.x = ((m_width  - stringWidth) / 2) - pInfo->bbox.xMin;
            top = (m_height - m_textHeight) / 2;
            pen.y = top + (lineNumber * m_lineHeight) + pInfo->bbox.yMax;		    
            break;

	    case CCImage::ETextAlign::kAlignRight: // Horizontal right and vertical center.
            pen.x = m_width - stringWidth - pInfo->bbox.xMin;
            top = (m_height - m_textHeight) / 2;
            pen.y = top + (lineNumber * m_lineHeight) + pInfo->bbox.yMax;		    
  		    break;

	    case CCImage::ETextAlign::kAlignLeft: // Horizontal left and vertical center.
	    default:
            pen.x -=pInfo->bbox.xMin;
            top = (m_height - m_textHeight) / 2;
            pen.y = top + (lineNumber * m_lineHeight) + pInfo->bbox.yMax;		    
  		    break;
    }

    return pen;
}

void  CCFreeTypeFont::drawText(FTLineInfo* pInfo, unsigned char* pBuffer, FT_Vector *pen)
{

    auto glyphs = pInfo->glyphs;
    for (auto glyph = glyphs.begin() ; glyph != glyphs.end(); ++glyph)
    {
        FT_Glyph image = glyph->image;
        FT_Error error = FT_Glyph_To_Bitmap(&image, FT_RENDER_MODE_NORMAL, 0, 1);
        if (!error)
        {
            FT_BitmapGlyph  bit = (FT_BitmapGlyph)image;
            draw_bitmap(pBuffer, &bit->bitmap, pen->x + glyph->pos.x + bit->left,pen->y - bit->top);
            FT_Done_Glyph(image);
        }
    }
}


void CCFreeTypeFont::draw_bitmap(unsigned char* pBuffer, FT_Bitmap*  bitmap, FT_Int x, FT_Int y)
{
    FT_Int  i, j, p, q;
    FT_Int  x_max = x + bitmap->width;
    FT_Int  y_max = y + bitmap->rows;

    for (i = x, p = 0; i < x_max; i++, p++)
    {
        for ( j = y, q = 0; j < y_max; j++, q++ )
        {
            if (i < 0 || j < 0 || i >= m_width || j >= m_height)
                continue;

            unsigned char value =  bitmap->buffer[q * bitmap->width + p];

            if(value > 0)
            {
                FT_Int index = (j * m_width * 4) + (i * 4);
                pBuffer[index++] = 0xff;
                pBuffer[index++] = 0xff;
                pBuffer[index++] = 0xff;
                pBuffer[index++] = value;
           }
        }
    }  
}

void CCFreeTypeFont::endLine() 
{
    if(m_currentLine)
    {
        m_lines.push_back(m_currentLine);
        m_textWidth = max(m_textWidth,m_currentLine->bbox.xMax - m_currentLine->bbox.xMin);
        m_textHeight += m_lineHeight;
    }
}

void CCFreeTypeFont::newLine() 
{
    m_currentLine = new FTLineInfo();
    m_currentLine->width = 0;
    m_currentLine->pen.x = 0;
    m_currentLine->pen.y = 0;
}


FT_Error CCFreeTypeFont::addWord(const std::string& word) 
{
	std::vector<TGlyph> glyphs; // glyphs for the word
	FT_BBox             bbox;   // bounding box containing all of the glyphs in the word
    int maxWidth = m_inWidth ? m_inWidth : m_windowWidth;
    std::string newWord;

    if(m_currentLine->width > 0) 
    {
        newWord = ' ' + word;
    } 
    else
    {
        newWord = word;
    }

    FT_Error error = initWordGlyphs(glyphs, newWord, m_currentLine->pen);
    if(!error) 
    {
        compute_bbox(glyphs, &bbox);
        if(m_currentLine->width == 0 || bbox.xMax <= maxWidth)
        {
            m_currentLine->glyphs.insert(m_currentLine->glyphs.end(),glyphs.begin(),glyphs.end());
            if(m_currentLine->width == 0)
            {
                m_currentLine->bbox = bbox;
            }
            else
            {
                m_currentLine->bbox.xMax = bbox.xMax;
            }
            m_currentLine->width = m_currentLine->bbox.xMax - m_currentLine->bbox.xMin;
        }
        else 
        {
            endLine();
            newLine();
            addWord(word);
        }
    }
    return error;
}

FT_Error CCFreeTypeFont::initGlyphs(const char* text) 
{
    FT_Error error = 0;
    std::stringstream stringStream(text);
    std::string line;
    vector<std::string> lines;
    vector<std::string> words;

    m_textWidth = 0;
    m_textHeight = 0;

    // the height of a line of text based on the max height of a glyph in the font size
    m_lineHeight = ((m_face->size->metrics.ascender) >> 6) - ((m_face->size->metrics.descender) >> 6);

    m_lines.clear();

    while(std::getline(stringStream, line) && !error) 
    {
        newLine();

        std::size_t prev = 0, pos;
        while ((pos = line.find_first_of(" ", prev)) != std::string::npos)
        {
            if (pos > prev)
            {
                addWord(line.substr(prev, pos-prev));
            }
            prev = pos + 1;
        }
        if (prev < line.length())
        {
            addWord(line.substr(prev, std::string::npos));
        }
        endLine();
    }

    return error;
}

// if linewidth > m_inWidth
// get words for line

void CCFreeTypeFont::initWords(const char* text) 
{
    std::stringstream stringStream(text);
    std::string line;
    vector<std::string> lines;
    vector<std::string> words;

    while(std::getline(stringStream, line)) 
    {
        lines.push_back(line);
    }

    for (auto it = lines.begin() ; it != lines.end(); ++it)
    {
        std::size_t prev = 0, pos;
        while ((pos = it->find_first_of(" ';", prev)) != std::string::npos)
        {
            if (pos > prev)
                words.push_back(it->substr(prev, pos-prev));
            prev = pos+1;
        }
        if (prev < it->length())
            words.push_back(it->substr(prev, std::string::npos));
    }

    for (auto it = words.begin() ; it != words.end(); ++it)
    {
        std::string foo(*it);
    }
}

FT_Error CCFreeTypeFont::initWordGlyphs(std::vector<TGlyph>& glyphs, const std::string& text, FT_Vector& pen) 
{
	FT_UInt			glyph_index;
	FT_UInt			previous = 0;
    FT_Face         previousFace = m_face;
	FT_Error		error = 0;
	PGlyph			glyph;
    unsigned int    numGlyphs = 0;
    wchar_t *       pwszBuffer = nullptr;

	int num_chars = text.size();
	int nBufLen  = num_chars + 1;			
	pwszBuffer = new wchar_t[nBufLen];
    if(!pwszBuffer)
    {
        return -1;
    }
    
    memset(pwszBuffer,0,nBufLen);
    num_chars = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), num_chars, pwszBuffer, nBufLen);		
    pwszBuffer[num_chars] = '\0';

    glyphs.clear();
	glyphs.resize(num_chars);

	for (int n = 0; n < num_chars; n++)
	{
		glyph = &glyphs[numGlyphs];

		/* convert character code to glyph index */
        FT_ULong c = pwszBuffer[n];
        FT_Face face = m_face;
        glyph_index = FT_Get_Char_Index(face, c);
        // If the glyph isn't found, search the other faces
        for (auto i = s_faces.begin(); (glyph_index == 0) && (i != s_faces.end()); ++i)
        {
            face = i->first;
            glyph_index = FT_Get_Char_Index(face, c);
        }

        if (FT_HAS_KERNING(face) && previousFace == face && previous && glyph_index)
		{
			FT_Vector  delta;
            FT_Get_Kerning(face, previous, glyph_index,
							FT_KERNING_DEFAULT, &delta);
			pen.x += delta.x >> 6;
		}

		/* store current pen position */
		glyph->pos = pen;
		glyph->index = glyph_index;

		/* load glyph image into the slot without rendering */
        error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
		if (error)
			continue;  /* ignore errors, jump to next glyph */

		/* extract glyph image and store it in our table */
        error = FT_Get_Glyph(face->glyph, &glyph->image);
		if (error)
			continue;  /* ignore errors, jump to next glyph */

		 /* translate the glyph image now */
		FT_Glyph_Transform(glyph->image, nullptr, &glyph->pos);

		/* increment pen position */
		pen.x += (FT_Pos)(face->glyph->advance.x) >> 6;

		/* record current glyph index */
		previous = glyph_index;
        previousFace = face;

		numGlyphs++;
	}

    CC_SAFE_DELETE_ARRAY(pwszBuffer);

	return error;
}

void  CCFreeTypeFont::compute_bbox(std::vector<TGlyph>& glyphs, FT_BBox  *abbox)
{
    FT_BBox bbox;
    FT_BBox glyph_bbox;

    /* initialize string bbox to "empty" values */
    bbox.xMin = 32000;
    bbox.xMax = -32000;

    // use the max and min values for the entire font face
    bbox.yMin = (m_face->size->metrics.descender) >> 6;
    bbox.yMax = (m_face->size->metrics.ascender) >> 6;

    /* for each glyph image, compute its bounding box, */
    /* translate it, and grow the string bbox          */
    for (auto glyph = glyphs.begin() ; glyph != glyphs.end(); ++glyph)
    {
        FT_Glyph_Get_CBox(glyph->image, ft_glyph_bbox_pixels, &glyph_bbox);

        glyph_bbox.xMin += glyph->pos.x;
        glyph_bbox.xMax += glyph->pos.x;
        glyph_bbox.yMin += glyph->pos.y;
        glyph_bbox.yMax += glyph->pos.y;

        if (glyph_bbox.xMin < bbox.xMin)
            bbox.xMin = glyph_bbox.xMin;

        if (glyph_bbox.yMin < bbox.yMin)
            bbox.yMin = glyph_bbox.yMin;

        if (glyph_bbox.xMax > bbox.xMax)
            bbox.xMax = glyph_bbox.xMax;

        if (glyph_bbox.yMax > bbox.yMax)
            bbox.yMax = glyph_bbox.yMax;
    }

    /* check that we really grew the string bbox */
    if (bbox.xMin > bbox.xMax)
    {
        bbox.xMin = 0;
        bbox.yMin = 0;
        bbox.xMax = 0;
        bbox.yMax = 0;
    }
  
    /* return string bbox */
    *abbox = bbox;
}

unsigned char* CCFreeTypeFont::loadFont(const char *pFontName, unsigned long *size) 
{
	std::string lowerCase(pFontName);
	std::string path(pFontName);

    for (unsigned int i = 0; i < lowerCase.length(); ++i)
    {
        lowerCase[i] = tolower(lowerCase[i]);
    }

    if (std::string::npos == lowerCase.find("fonts/"))
    {
        path = "fonts/";
        path += pFontName;
    }

    if (std::string::npos == lowerCase.find(".ttf"))
    {
        path += ".ttf";
    }

	std::string fullpath  = CCFileUtils::sharedFileUtils()->fullPathForFilename(path.c_str());
	return CCFileUtils::sharedFileUtils()->getFileData(fullpath.c_str(), "rb", size);
}

unsigned char* CCFreeTypeFont::loadSystemFont(const char *pFontName, unsigned long *size) 
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    //Froxul: Add the ability to use system fonts on WP8 and WinRT
    //http://www.cocos2d-x.org/forums/6/topics/37224
    std::string fontName(pFontName);
    if (fontName.rfind(".ttf") == std::string::npos &&
        fontName.rfind(".ttc") == std::string::npos)
    {
        fontName += ".ttf";
    }
    std::string fontPath = "C:\\Windows\\Fonts\\" + fontName;
    return CCFileUtils::sharedFileUtils()->getFileData(fontPath.c_str(), "rb", size);
#else
    std::string aName(pFontName);
    unsigned char* pBuffer = nullptr;
    HRESULT hr = S_OK;
	IDWriteFactory *writeFactory = nullptr;
	IDWriteFontCollection *fontCollection = nullptr;
	IDWriteFontFamily *fontFamily = nullptr;
	IDWriteFont *matchingFont = nullptr;
	IDWriteFontFace *fontFace = nullptr;
	IDWriteFontFile *fontFile = nullptr;
	IDWriteFontFileLoader *fontFileLoader = nullptr;
	IDWriteFontFileStream *fontFileStream = nullptr;
	UINT32 index;
	BOOL exists;
	std::wstring fontNameW;
    const void *fontFileReferenceKey = nullptr;
    UINT32 fontFileReferenceKeySize;            
    void *fragmentContext = nullptr;
 
    for (unsigned int i = 0; i < aName.length(); ++i)
    {
        aName[i] = tolower(aName[i]);
    }
    fontNameW.assign(aName.begin(), aName.end());

	//create the factory
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&writeFactory));

    if(SUCCEEDED(hr))
    {
	    //obtain the fonts owned by the machine
	    hr  = writeFactory->GetSystemFontCollection(&fontCollection, TRUE);
    }

	//get the font 
    if(SUCCEEDED(hr))
    {
	    hr = fontCollection->FindFamilyName(fontNameW.c_str(), &index, &exists);
        if(SUCCEEDED(hr) && exists)
        {
	        hr = fontCollection->GetFontFamily(index, &fontFamily);

            if(SUCCEEDED(hr))
            {
	            hr = fontFamily->GetFirstMatchingFont(DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STRETCH_NORMAL, DWRITE_FONT_STYLE_NORMAL, &matchingFont);
            }

            if(SUCCEEDED(hr))
            {
	            hr = matchingFont->CreateFontFace(&fontFace);
            }

            if(SUCCEEDED(hr))
            {
	            UINT32 numberOfFiles = 1;
	            hr = fontFace->GetFiles(&numberOfFiles, &fontFile);
            }

            if(SUCCEEDED(hr))
            {
	            //create the font file stream
               hr = fontFile->GetReferenceKey(&fontFileReferenceKey, &fontFileReferenceKeySize);
            }

            if(SUCCEEDED(hr))
            {
                hr = fontFile->GetLoader(&fontFileLoader);
            }

            if(SUCCEEDED(hr))
            {
                hr = fontFileLoader->CreateStreamFromKey(fontFileReferenceKey, fontFileReferenceKeySize, &fontFileStream);
            }

            if(SUCCEEDED(hr))
            {
	            //finally get the font file dat
	            UINT64 fileSize;
		        const void *fragmentStart = nullptr;
                hr = fontFileStream->GetFileSize(&fileSize);

                if(SUCCEEDED(hr))
                {
	                hr = fontFileStream->ReadFileFragment(&fragmentStart, 0, fileSize, &fragmentContext);
                }

                if(SUCCEEDED(hr))
                {
	                pBuffer = (unsigned char*)malloc((size_t)fileSize);
	                memcpy(pBuffer, fragmentStart, (size_t)fileSize);      
                    *size = (unsigned long)fileSize;
                }
            }
        }
    }

	//clean up all the DWrite stuff
    if(fontFileStream)
    {
	    fontFileStream->ReleaseFileFragment(fragmentContext);
	    fontFileStream->Release();
    }
    if(fontFileLoader)
    {
	    fontFileLoader->Release();
    }
    if(fontFile)
    {
	    fontFile->Release();
    }
    if(fontFace)
    {
	    fontFace->Release();
    }
    if(matchingFont)
    {
	    matchingFont->Release();
    }
    if(fontFamily)
    {
	    fontFamily->Release();
    }
    if(fontCollection)
    {
	    fontCollection->Release();
    }
    if(writeFactory)
    {
	    writeFactory->Release();
    }

    return pBuffer;
#endif
}

NS_CC_END

