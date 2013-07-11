

#include <stdio.h>
#include "cocos2d.h"
#include "CCFontFreeType.h"
#include "CCTextImage.h"

NS_CC_BEGIN

bool FontFreeType::createFontObject(const std::string &fontName, int fontSize)
{
    /*
    CFStringRef theRefString    = NULL;
    theRefString                = CFStringCreateWithCString(kCFAllocatorDefault, fontName.c_str(), CFStringGetSystemEncoding());
    NSString * fntName          = [NSString stringWithUTF8String:fontName.c_str()];
    
    // actually create iOS font (s)
    _fontRef = CTFontCreateWithName(theRefString, fontSize, NULL);
    _fontUI  = [UIFont fontWithName:fntName size:fontSize];
    
    return ( (_fontRef != NULL) && (_fontUI != NULL) );
    */
    
    return false;
}

FontFreeType::~FontFreeType()
{
    // release the font
    // TO DO 
}

GlyphDef * FontFreeType::getGlyphsForText(const char *pText, int &outNumGlyphs)
{
    /*
    float CHAR_PADDING = 10.0f;
    
    UniChar * characters;
    CGGlyph * glyphs;
    CFIndex   count;
    
    CFStringRef lettersString;
    lettersString   = CFStringCreateWithCString(kCFAllocatorDefault, pText, kCFStringEncodingUTF8);
    
    if (NULL == lettersString)
        return false;
    
    count = CFStringGetLength(lettersString);
    
    // Allocate our buffers for characters and glyphs.
    characters = new UniChar[count];
    assert(characters != NULL);
    
    glyphs = new CGGlyph[count];
    assert(glyphs != NULL);
    
    // Get the characters from the string.
    CFStringGetCharacters(lettersString, CFRangeMake(0, count), characters);
    
    // Get the glyphs for the characters.
    CTFontGetGlyphsForCharacters(_fontRef, characters, glyphs, count);
    CGGlyph *theFirstGlyph = &glyphs[0];
    
    // get letters bounding boxes
    CGRect *BBOx  = new CGRect[count];
    assert(BBOx != NULL);
    
    
    CTFontGetBoundingRectsForGlyphs(_fontRef, kCTFontHorizontalOrientation, theFirstGlyph, BBOx, count);
    
    GlyphDef *pGlyphs = new GlyphDef[count];
    assert(pGlyphs != NULL);
    
    
    // sore result as CCRect
    for (int c=0; c<count; ++c)
    {
        Rect tempRect;
        tempRect.origin.x       = BBOx[c].origin.x;
        tempRect.origin.y       = BBOx[c].origin.y;
        tempRect.size.width     = BBOx[c].size.width;
        tempRect.size.height    = BBOx[c].size.height;
        
        pGlyphs[c].setRect(tempRect);
        pGlyphs[c].setUTF8Letter(characters[c]);
        pGlyphs[c].setPadding(CHAR_PADDING);
    }
    
    // release memory
    delete [] characters;
    delete [] glyphs;
    delete [] BBOx;
    
    outNumGlyphs = count;
    return pGlyphs;
    */
    
    return 0;
}

Size * FontFreeType::getAdvancesForTextUTF8(unsigned short *pText, int &outNumLetters)
{
    /*
    if (!pText)
        return 0;
    
    outNumLetters = cc_wcslen(pText);

    if (!outNumLetters)
        return 0;
    
    // create the reference to the string
    CFStringRef lettersString = CFStringCreateWithCharacters(kCFAllocatorDefault, pText, outNumLetters);
    
    if (NULL == lettersString)
    {
        return 0;
    }
    
    UniChar *characters;
    CGGlyph *glyphs;
    CFIndex  count;
    
    // num char
    count = CFStringGetLength(lettersString);
    
    // Allocate our buffers for characters and glyphs.
    characters = new UniChar[count];
    assert(characters != NULL);
    
    glyphs = new CGGlyph[count];
    assert(glyphs != NULL);
    
    // Get the characters from the string.
    CFStringGetCharacters(lettersString, CFRangeMake(0, count), characters);
    
    // Get the glyphs for the characters.
    CTFontGetGlyphsForCharacters(_fontRef, characters, glyphs, count);
    
    CGGlyph *theFirstGlyph = &glyphs[0];
    
    
    CGSize *pSize = new CGSize[count];
    if(!pSize)
        return 0;
    
    Size *pCCSizes = new Size[count];
    if (!pCCSizes)
        return 0;
    
    // actually get the advances
    CTFontGetAdvancesForGlyphs(_fontRef, kCTFontHorizontalOrientation, theFirstGlyph, pSize, count);
    
    for (int c = 0; c<count; ++c)
    {
        pCCSizes[c].width  = pSize[c].width;
        pCCSizes[c].height = pSize[c].height;
    }
    
    delete [] characters;
    delete [] glyphs;
    delete [] pSize;
    
    outNumLetters = count;
    return pCCSizes;
    */
    
    return 0;
}

Size * FontFreeType::getAdvancesForText(const char *pText, int &outNumLetters)
{
    /*
    unsigned short int *utf8Text = FontIOS::getUTF8Text(pText, outNumLetters);
    if (utf8Text)
    {
        Size *ret = getAdvancesForTextUTF8(utf8Text, outNumLetters);
        delete [] utf8Text;
        return ret;
    }
    else
    {
        return 0;
    }
    */
    
    return 0;
}

Size FontFreeType::getTextWidthAndHeight(const char *pText)
{
    /*
    Size retSize;
    NSString * str      = [NSString stringWithUTF8String:pText];
    CGSize tmp          = [str sizeWithFont:(UIFont *)_fontUI];
    
    retSize.width       = tmp.width;
    retSize.height      = tmp.height;
    
    return retSize;
    */
    
    Size retSize;
    return retSize;
}

unsigned short int * FontFreeType::getUTF8Text(const char *pText, int &outNumLetters)
{
    /*
    CFStringRef lettersString = CFStringCreateWithCString(kCFAllocatorDefault, pText, kCFStringEncodingUTF8);
    if (NULL == lettersString)
    {
        return 0;
    }
    
    // num char
    int count = CFStringGetLength(lettersString);
    
    // Allocate our buffers for characters and glyphs.
    UniChar *characters = new UniChar[count + 1];
    if (!characters)
        return 0;
    
    // Get the characters from the string.
    CFStringGetCharacters(lettersString, CFRangeMake(0, count), characters);
    
    // terminate the string
    outNumLetters = count;
    characters[count] = 0;
    
    return (unsigned short int *) characters;
    */
    
    return 0;
}

const char * FontFreeType::trimUTF8Text(const char *pText, int newBegin, int newEnd)
{
    /*
    if ( newBegin<0 || newEnd<=0 )
        return 0;
    
    if ( newBegin>=newEnd )
        return 0;
    
    NSString * str      = [NSString stringWithUTF8String:pText];
    if ( newEnd >= [str length])
        return 0;
    
    NSRange theRange;
    
    theRange.location = newBegin;
    theRange.length   = (newEnd - newBegin) +1;
    
    // trim the string
    NSString *trimmedString = [str substringWithRange:theRange];
    
    // ret the string
    return [trimmedString UTF8String];
    */
    
    return 0;
}

int FontFreeType::getUTF8TextLenght(const char *pText)
{
    /*
    CFStringRef lettersString = CFStringCreateWithCString(kCFAllocatorDefault, pText, kCFStringEncodingUTF8);
    if (NULL == lettersString)
    {
        return 0;
    }
    
    return  CFStringGetLength(lettersString);
    */
    return 0;
}

NS_CC_END