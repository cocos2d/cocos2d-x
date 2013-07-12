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

#include "ft2build.h"
#include "CCStdC.h"
#include FT_FREETYPE_H

NS_CC_BEGIN

FT_Library library;

void FontRenderFreeType::testRendering()
{
    // begin freetype
    //FT_Init_FreeType( &library );
    
    
    
    // end freetype
    //FT_Done_FreeType(library);
    
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