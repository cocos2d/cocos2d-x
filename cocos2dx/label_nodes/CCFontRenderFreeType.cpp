//
//  CCFontRenderIOS.mm
//  TestNewStringStuff
//
//  Created by Carlo Morgantini on 5/28/13.
//
//

#include "cocos2d.h"
#include "CCTextImage.h"
#include "CCFontRenderFreeType.h"

#include "CCImage.h"

#include "ft2build.h"
#include FT_FREETYPE_H


NS_CC_BEGIN

FT_Library library;
FT_Face    currentFace;


// globals

bool renderCharAtStatic(FT_GlyphSlot theGlyph, unsigned char *destMemory, int posX, int posY, int destSize)
{
    // render the glyph
    if (FT_Render_Glyph( theGlyph, FT_RENDER_MODE_NORMAL ))
        return false;
    
    // carloX posY -= theGlyph->bitmap_top;
    // carloX int testbearing = theGlyph->bitmap_top;
    
    // copy the gliph into the bitmap
    FT_Bitmap& bitmap = theGlyph->bitmap;
    
    int iX = posX;
    int iY = posY;
    
    for (int y = 0; y < bitmap.rows; ++y)
    {
        int bitmap_y = y * bitmap.width;
        
        for (int x = 0; x < bitmap.width; ++x)
        {
            unsigned char cTemp = bitmap.buffer[bitmap_y + x];
            
            // the final pixel
            int iTemp = cTemp << 24 | cTemp << 16 | cTemp << 8 | cTemp;
            *(int*) &destMemory[(iX + ( iY * destSize ) ) * 4] = iTemp;
            
            iX += 1;
        }
        
        iX  = posX;
        iY += 1;
    }
    
    //everything good
    return true;
}

bool FontRenderFreeType::renderCharAt(unsigned short int charToRender, int posX, int posY, unsigned char *destMemory, int destSize)
{
    if (!_font)
        return false;
    
    unsigned char *sourceBitmap = 0;
    int sourceWidth  = 0;
    int sourceHeight = 0;
    
    // get the glyph's bitmap
    sourceBitmap = _font->getGlyphBitmap(charToRender, sourceWidth, sourceHeight);
    
    if(!sourceBitmap)
        return false;
    
    int iX = posX;
    int iY = posY;
    
    for (int y = 0; y < sourceHeight; ++y)
    {
        int bitmap_y = y * sourceWidth;
        
        for (int x = 0; x < sourceWidth; ++x)
        {
            unsigned char cTemp = sourceBitmap[bitmap_y + x];
            
            // the final pixel
            int iTemp = cTemp << 24 | cTemp << 16 | cTemp << 8 | cTemp;
            *(int*) &destMemory[(iX + ( iY * destSize ) ) * 4] = iTemp;
            
            iX += 1;
        }
        
        iX  = posX;
        iY += 1;
    }
    
    //everything good
    return true;
}

bool FontRenderFreeType::InitFreeType()
{
    // begin freetype
    if (FT_Init_FreeType( &library ))
        return false;
    else
        return true;
}

bool FontRenderFreeType::CreateFreeTypeFont(const char *fontName, int fontSize, int dpi)
{
    unsigned char* data = NULL;
    
    int len = 0;
    data    = FileUtils::sharedFileUtils()->getFileData(fontName, "rb", (unsigned long *)(&len) );
    
    if (!data)
        return false;
    
    // create the new face
    FT_Face face;
    
    // create the face from the data
    if (FT_New_Memory_Face(library, data, len, 0, &face) )
        return false;
    
    // set the requested font size
	int fontSizePoints = (int)(64.f * fontSize);
	if( FT_Set_Char_Size(face, fontSizePoints, fontSizePoints, dpi, dpi) )
        return false;
    
    // store the face globally
    currentFace = face;
    
    // done and good
    return true;
}

void FontRenderFreeType::ReleaseFreeType()
{
    // end freetype
    FT_Done_FreeType(library);
}


void FontRenderFreeType::testRendering()
{
    //
    const char *stringToRender = "abcdefghilmnopqrstuvz";
    
    // init freetype
    InitFreeType();
    
    
    // init and create a font
    CreateFreeTypeFont("fonts/Thonburi.ttf", 100, 72);
    
    
    
    // allocate memory for the bitmap
    int bitmapSize = 512;
    unsigned char *pBitmap = new unsigned char[bitmapSize * bitmapSize * 4];
    if(!pBitmap) return;
    memset(pBitmap, 0, bitmapSize * bitmapSize * 4);
    
    // carloX: has to be changed
    FT_Face face = currentFace;
    
    // line height
    int lineHeight = face->size->metrics.height>>6;
    
    // padding between letters
    int paddingX =  5;
    int paddingY =  0;
    
    // where we need to render first
    int renderPosX =  paddingX;
    // carloX int renderPosY =  lineHeight + paddingY;
    int renderPosY =  0;
    
    int stringLength = strlen(stringToRender);
    
    for (int c = 0; c < stringLength; ++c)
    {
        int glyph_index = FT_Get_Char_Index(face, stringToRender[c]);
        if (!glyph_index)
            return;
        
        if (FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT))
            return;
        
        // check for bounds
        
        // test carloX
        int advancePixel    = face->glyph->advance.x >> 6;
        int widthInPixel    = face->glyph->metrics.width >> 6;
        int heightInPixel   = face->glyph->metrics.height >> 6;
        int ascent          = face->glyph->metrics.horiBearingY>>6;
        // end test carloX
        
        if ( (renderPosX + (face->glyph->advance.x >> 6) + paddingX) >= bitmapSize )
        {
            renderPosX  = paddingX;
            renderPosY += (lineHeight + paddingY);
        }
        
        // render in bitmap
        renderCharAtStatic(face->glyph, pBitmap, renderPosX, renderPosY, bitmapSize);
        
        // move pen
        // carloX renderPosX += ((face->glyph->advance.x >> 6) + paddingX);
        renderPosX += (widthInPixel + paddingX);
    }
    
    
    
    // save the bitmap into a file
    Image *pImage = new Image;
    pImage->initWithRawData(pBitmap, (bitmapSize * bitmapSize * 4), 512, 512, 8, false);
    pImage->saveToFile("carlottone");
    
    
    // release the bitmap
    delete [] pBitmap;
    
    // end freetype
    ReleaseFreeType();
}

unsigned char * FontRenderFreeType::preparePageGlyphData(TextPageDef *thePage, char *fontName, int fontSize)
{
    if (!thePage)
        return 0;
    
    if (_font)
        return 0;
    
    if (thePage->getNumLines() == 0)
        return NULL;
    
    int pageWidth  = thePage->getWidth();
    int pageHeight = thePage->getHeight();
    
    // prepare memory and clean to 0
    int sizeInBytes = (pageWidth * pageHeight * 4);
    unsigned char* data = new unsigned char[sizeInBytes];
    
    if (!data)
        return 0;
    
    memset(data, 0, sizeInBytes);
    
    int numLines = thePage->getNumLines();
    
    for (int c = 0; c<numLines; ++c)
    {
        TextLineDef *pCurrentLine   = thePage->getLineAt(c);
        
        float origX         = _font->getLetterPadding();
        float origY         = pCurrentLine->getY();
        
        int numGlyphToRender = pCurrentLine->getNumGlyph();
        
        for (int cglyph = 0; cglyph < numGlyphToRender; ++cglyph)
        {
            GlyphDef currGlyph      = pCurrentLine->getGlyphAt(cglyph);
            renderCharAt(currGlyph.getUTF8Letter(), origX, origY, data, pageWidth);
            origX += (currGlyph.getRect().size.width + _font->getLetterPadding());
        }
    }
    
    
    bool debug = true;
    if (debug)
    {
        static int counter = 0;
        
        char outFilename[512];
        sprintf(outFilename,"carlottone%d", counter);
        ++counter;
        
        // save the bitmap into a file
        Image *pImage = new Image;
        pImage->initWithRawData(data, (pageWidth * pageWidth * 4), 512, 512, 8, false);
        pImage->saveToFile(outFilename);
    }
        
        
    
    // we are done here
    return data;
}


NS_CC_END