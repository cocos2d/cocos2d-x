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
#include "CCStdC.h"
#include FT_FREETYPE_H

NS_CC_BEGIN

FT_Library library;


// globals

bool renderCharAt(FT_GlyphSlot theGlyph, unsigned char *destMemory, int posX, int posY, int destSize)
{
    // render the glyph
    if (FT_Render_Glyph( theGlyph, FT_RENDER_MODE_NORMAL ))
        return false;
    
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


void FontRenderFreeType::testRendering()
{
    
    const char *stringToRender = "abcdefghilmnopqrstuvz";
    
    // font info
    int dpi         = 72;
	int fontSize    = 30;
    
    // error 
    int libError;
    
    // begin freetype
    libError = FT_Init_FreeType( &library );
    
    unsigned char* data = NULL;
    int len = 0;
    data    = FileUtils::sharedFileUtils()->getFileData("fonts/Thonburi.ttf", "rb", (unsigned long *)(&len) );
    
    if (!data)
        return;

    // create the new face
    FT_Face face;
    
    // create the face from the data
    if (FT_New_Memory_Face(library, data, len, 0, &face) )
        return;
    
    // set the requested font size
	int fontSizePoints = (int)(64.f * fontSize);
	if( FT_Set_Char_Size(face, fontSizePoints, fontSizePoints, dpi, dpi) )
        return;
    
    // allocate memory for the bitmap
    int bitmapSize = 512;
    unsigned char *pBitmap = new unsigned char[bitmapSize * bitmapSize * 4];
    if(!pBitmap) return;
    memset(pBitmap, 0, bitmapSize * bitmapSize * 4);

    
    
    
    
    
    // padding between letters
    int paddingX = 5;
    int paddingY = 10;
    
    int renderPosX = paddingX;
    int renderPosY = paddingY;
    
    // this must be dynamic
    int letterWidth  = 30;
    int letterHeight = 30;
    
    int stringLength = strlen(stringToRender);
    
    for (int c = 0; c < stringLength; ++c)
    {
        int glyph_index = FT_Get_Char_Index(face, stringToRender[c]);
        if (!glyph_index)
            return;
        
        if (FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT))
            return;
        
        // get witdh and height for the next character
        
        // check for bounds
        if ( (renderPosX +letterWidth + paddingX) >= bitmapSize )
        {
            renderPosX = paddingX;
            renderPosY += (letterHeight + paddingY);
        }
        
        renderCharAt(face->glyph, pBitmap, renderPosX, renderPosY, bitmapSize);
        
        // move
        renderPosX += letterWidth + paddingX;
    }
    
    
    
    /*
        
    
    // allocate the bitmap
    int bitmapSize = 512;
    unsigned char *pBitmap = new unsigned char[bitmapSize * bitmapSize * 4];
    memset(pBitmap, 0, bitmapSize * bitmapSize * 4);
    
    renderCharAt(face->glyph, pBitmap, 10, 10, 512);
    renderCharAt(face->glyph, pBitmap, 200, 200, 512);
    renderCharAt(face->glyph, pBitmap, 300, 300, 512);
    */
    /*

    // render the glyph
    if (FT_Render_Glyph( face->glyph, FT_RENDER_MODE_NORMAL ))
    {
        return;
    }
    
    // copy the gliph into the bitmap
    FT_Bitmap& bitmap = face->glyph->bitmap;
    
    // allocate the bitmap
    int bitmapSize = 512;
    unsigned char *pBitmap = new unsigned char[bitmapSize * bitmapSize * 4];
    memset(pBitmap, 0, bitmapSize * bitmapSize * 4);
    
    
    if (!pBitmap)
        return;
    
    int destX = 10;
    int destY = 10;
    
    int iX = destX;
    int iY = destY;
    
    
    for (int y = 0; y < bitmap.rows; ++y)
    {
        int bitmap_y = y * bitmap.width;
        
        for (int x = 0; x < bitmap.width; ++x)
        {
            unsigned char cTemp = bitmap.buffer[bitmap_y + x];
            
            //if (cTemp == 0)
            //{
            //    continue;
            //}
            
            // the final pixel
            int iTemp = cTemp << 24 | cTemp << 16 | cTemp << 8 | cTemp;
            *(int*) &pBitmap[(iX + ( iY * bitmapSize ) ) * 4] = iTemp;
            
            iX += 1;
        }
        
        iX  = destX;
        iY += 1;
    }
    */
    
    // save the bitmap into a file
    Image *pImage = new Image;
    pImage->initWithRawData(pBitmap, (bitmapSize * bitmapSize * 4), 512, 512, 8, false);
    pImage->saveToFile("carlottone");
    
    // release the bitmap
    delete [] pBitmap;
    
    // end freetype
    FT_Done_FreeType(library);
}


void FontRenderFreeType::renderCharToBitmap(char *pDestBitmap, char charToRender, int posX, int posY)
{
}


unsigned char * FontRenderFreeType::preparePageGlyphData(TextPageDef *thePage, char *fontName, int fontSize)
{

    // constants
    float   LINE_PADDING    = 1.9;
    
    if (!thePage)
        return NULL;
    
    if (thePage->getNumLines() == 0)
        return NULL;
    
    int pageWidth  = thePage->getWidth();
    int pageHeight = thePage->getHeight();
    
    // prepare memory and clean to 0
    int sizeInBytes = (pageWidth * pageHeight * 4);
    unsigned char* data = new unsigned char[sizeInBytes];
    memset(data, 0, sizeInBytes);
    
    
    int numLines = thePage->getNumLines();
    for (int c = 0; c<numLines; ++c)
    {
        TextLineDef *pCurrentLine = thePage->getLineAt(c);
        float lineHeight            = pCurrentLine->getHeight();
        
        float origX         = LINE_PADDING;
        float origY         = pCurrentLine->getY();
        
        int numGlyphToRender = pCurrentLine->getNumGlyph();
        
        for (int cglyph = 0; cglyph < numGlyphToRender; ++cglyph)
        {
            GlyphDef currGlyph      = pCurrentLine->getGlyphAt(cglyph);
            
            //NSString *lineString = [NSString stringWithFormat: @"%C", currGlyph.getUTF8Letter()];
            //CGRect tempRect;
            Rect tempRect;
            
            tempRect.origin.x       = (origX - currGlyph.getRect().origin.x);
            tempRect.origin.y       = origY;
            tempRect.size.width     = currGlyph.getRect().size.width;
            tempRect.size.height    = lineHeight;
            
            // actually draw one character
            //[lineString drawInRect: tempRect withFont:font lineBreakMode:NSLineBreakByWordWrapping alignment:align];
            
            // move to next character
            origX += (tempRect.size.width + currGlyph.getPadding());
        }
    }
    
    // we are done here
    return data;
    
    /*
    // prepare the context
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGContextRef context = CGBitmapContextCreate(data, pageWidth, pageHeight, 8, pageWidth * 4, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
    CGColorSpaceRelease(colorSpace);
    
    if (!context)
    {
        delete[] data;
        return 0;
    }
    
    // prepare the context
    CGContextSetRGBFillColor(context, 1, 1, 1, 1);
    CGContextTranslateCTM(context, 0.0f, pageHeight);
    CGContextScaleCTM(context, 1.0f, -1.0f); //NOTE: NSString draws in UIKit referential i.e. renders upside-down compared to CGBitmapContext referential
    
    
    UIGraphicsPushContext(context);
    UITextAlignment align = NSTextAlignmentLeft;
    
    // create the font
    NSString *nsFontName = [NSString stringWithUTF8String:fontName];
    id font = [UIFont fontWithName:nsFontName size:fontSize];
    
    int numLines = thePage->getNumLines();
    for (int c = 0; c<numLines; ++c)
    {
        TextLineDef *pCurrentLine = thePage->getLineAt(c);
        float lineHeight            = pCurrentLine->getHeight();
        
        float origX         = LINE_PADDING;
        float origY         = pCurrentLine->getY();
        
        int numGlyphToRender = pCurrentLine->getNumGlyph();
        
        for (int cglyph = 0; cglyph < numGlyphToRender; ++cglyph)
        {
            GlyphDef currGlyph      = pCurrentLine->getGlyphAt(cglyph);
            
            NSString *lineString = [NSString stringWithFormat: @"%C", currGlyph.getUTF8Letter()];
            CGRect tempRect;
            
            tempRect.origin.x       = (origX - currGlyph.getRect().origin.x);
            tempRect.origin.y       = origY;
            tempRect.size.width     = currGlyph.getRect().size.width;
            tempRect.size.height    = lineHeight;
            
            // actually draw one character
            [lineString drawInRect: tempRect withFont:font lineBreakMode:NSLineBreakByWordWrapping alignment:align];
            
            // move to next character
            origX += (tempRect.size.width + currGlyph.getPadding());
        }
    }
    
    // clean everything
    UIGraphicsPopContext();
    CGContextRelease(context);
    
    // everything looks good
    return data;
     
    */
}


NS_CC_END