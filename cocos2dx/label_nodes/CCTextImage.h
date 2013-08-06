/****************************************************************************
 Copyright (c) 2013      Zynga Inc.
 
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

#ifndef _TextImage_h_
#define _TextImage_h_

#include "CCFontRender.h"
#include "CCFont.h"

NS_CC_BEGIN

/** @brief GlyphDef defines one single glyph (character) in a text image
 *
 * it defines the bounding box for the glyph in the texture page, the character the padding (spacing) between characters
 *
 */

class CC_DLL GlyphDef
{
public:
    
    GlyphDef() : _validGlyph(false)                                     {   /*do nothing*/                              }
    GlyphDef(unsigned short int letterUTF8, Rect &rect)                 { _gliphRect = rect; _uTF16Letter = letterUTF8; }
    
    void setUTF16Letter(unsigned short int letterUTF8)                  { _uTF16Letter  = letterUTF8;   }
    void setRect(Rect & theRect)                                        { _gliphRect = theRect;         }
    unsigned short int getUTF8Letter()                                  { return _uTF16Letter;          }
    Rect &  getRect()                                                   { return _gliphRect;            }
    void    setPadding(float padding)                                   { _padding = padding;           }
    float   getPadding()                                                { return _padding;              }
    void    setCommonHeight(float commonHeight)                         { _commonHeight = commonHeight; }
    float   getCommonHeight()                                           { return _commonHeight;         }
    void    setValid(bool isValid)                                      { _validGlyph = isValid;        }
    bool    isValid()                                                   { return _validGlyph;           }
    
private:
    
    Rect                _gliphRect;
    unsigned short int  _uTF16Letter;
    float               _padding;
    float               _commonHeight;
    bool                _validGlyph;
    
};

/** @brief TextLineDef define a line of text in a text image texture page
 *
 * conllects all the GlyphDef for a text line plus line size and line position in text image space
 *
 */
class CC_DLL TextLineDef
{
public:
    
    TextLineDef(float x, float y, float width, float height);
    
    float getX()        { return _x;        }
    float getY()        { return _y;        }
    float getWidth()    { return _width;    }
    float getHeight()   { return _height;   }
    
    void  addGlyph(GlyphDef theGlyph) { _glyphs.push_back(theGlyph);  }
    int   getNumGlyph()               { return _glyphs.size();        }
    GlyphDef & getGlyphAt(int index)  { return _glyphs[index];        }
    
private:
    
    float                   _x;
    float                   _y;
    float                   _width;
    float                   _height;
    std::vector<GlyphDef>   _glyphs;
    
};

/** @brief TextPageDef defines one text image page (a TextImage can have/use more than one page)
 *
 * collects all the TextLineDef for one page, the witdh and height of the page and the  graphics (texture) for the page
 *
 */
class CC_DLL TextPageDef
{
public:
    
     TextPageDef(int pageNum, int width, int height);
    ~TextPageDef();
    
    void addLine(TextLineDef *theLine)      { _lines.push_back(theLine); }
    int  getNumLines()                      { return _lines.size();      }
    TextLineDef * getLineAt(int index)      { return _lines[index];      }
    int getWidth()                          { return _width;             }
    int getHeight()                         { return _height;            }
    int getPageNumber()                     { return _pageNum;           }
    void setPageData(unsigned char *pData)  { _pageData = pData;         }
    unsigned char * getPageData()           { return _pageData;          }
    Texture2D     *getPageTexture();
    void preparePageTexture(bool releaseRAWData = true);
    
private:
    
    bool generatePageTexture(bool releasePageData = false);
    
    int                         _pageNum;
    int                         _width;
    int                         _height;
    unsigned char *             _pageData;
    Texture2D   *               _pageTexture;
    std::vector<TextLineDef *>  _lines;
    
};

/** @brief CCTextFontPages collection of pages (TextPageDef)
 *
 *  A TextImage is composed by one or more text pages. This calss collects all of those pages
 */
class CC_DLL TextFontPagesDef
{
public:
    
    TextFontPagesDef();
   ~TextFontPagesDef();
    
    void addPage(TextPageDef *newPage)      { _pages.push_back(newPage);    }
    int  getNumPages()                      { return _pages.size();         }
    TextPageDef* getPageAt(int index)       { return _pages[index];         }
    
private:
    
    std::vector<TextPageDef *>    _pages;
    
};

/** @brief TextImage 
 *
 */
class CC_DLL TextImage
{
public:
    
    TextImage();
   ~TextImage();
    
    bool initWithString(const char *pText, int nWidth, int nHeight, const char * pFontName, int nSize, bool releaseRAWData = true);
    TextFontPagesDef  * getPages()    { return _fontPages; }
    Font              * getFont()     { return _font;      }
    
private:
    
    unsigned char * preparePageGlyphData(TextPageDef *thePage);
    bool createImageDataFromPages(TextFontPagesDef *thePages, bool releaseRAWData = true);
    bool createFontRender();
    bool addGlyphsToLine(TextLineDef *line, const char *lineText, bool textIsUTF16 = false);
    bool createFontRef(const char *fontName, int size);
    bool generateTextGlyphs(const char * pText);
    int  getNumGlyphsFittingInSize(std::map<unsigned short int, GlyphDef> &glyphDefs, unsigned short int *strUTF8, Font *pFont, Size *constrainSize, int &outNewSize);
    bool createPageDefinitions(unsigned short int *inText, int imageWidth, int imageHeight, int lineHeight);
    
    std::map<unsigned short int, GlyphDef>      _textGlyphs;
    TextFontPagesDef *                          _fontPages;
    Font *                                      _font;
    FontRender *                                _fontRender;
    
    
};


NS_CC_END


#endif
