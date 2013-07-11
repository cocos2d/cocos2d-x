/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
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

#ifndef _TextImage_h
#define _TextImage_h

#include "CCFontRender.h"
#include "CCFont.h"

NS_CC_BEGIN

/** @brief GlyphDef defines one single glyph (character) in a text image
 *
 * it defines the bounding box for the glyph in the texture page, the character the padding (spacing) between characters
 *
 */

class GlyphDef
{
public:
    
    GlyphDef()                                                          {   /*do nothing*/                               }
    GlyphDef(unsigned short int letterUTF8, Rect &rect)                 { _gliphRect = rect; _uTF8Letter = letterUTF8;   }
    
    void setUTF8Letter(unsigned short int letterUTF8)                   { _uTF8Letter  = letterUTF8;    }
    void setRect(Rect & theRect)                                        { _gliphRect = theRect;         }
    unsigned short int getUTF8Letter()                                  { return _uTF8Letter;           }
    Rect &  getRect()                                                   { return _gliphRect;            }
    void  setPadding(float padding)                                     { _padding = padding;           }
    float getPadding()                                                  { return _padding;              }
    void  setCommonHeight(float commonHeight)                           { _commonHeight = commonHeight; }
    float getCommonHeight()                                             { return _commonHeight;         }
    
private:
    
    Rect                _gliphRect;
    unsigned short int  _uTF8Letter;
    float               _padding;
    float               _commonHeight;
    
};

/** @brief TextLineDef define a line of text in a text image texture page
 *
 * conllects all the GlyphDef for a text line plus line size and line position in text image space
 *
 */
class TextLineDef
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
    
    float _x;
    float _y;
    float _width;
    float _height;
    std::vector<GlyphDef> _glyphs;
    
};

/** @brief TextPageDef defines one text image page (a TextImage can have/use more than one page)
 *
 * collects all the TextLineDef for one page, the witdh and height of the page and the  graphics (texture) for the page
 *
 */
class TextPageDef
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
    
    int             _pageNum;
    int             _width;
    int             _height;
    unsigned char * _pageData;
    Texture2D   *   _pageTexture;
    std::vector<TextLineDef *> _lines;
    
};

/** @brief CCTextFontPages collection of pages (TextPageDef)
 *
 *  A TextImage is composed by one or more text pages. This calss collects all of those pages
 */
class TextFontPagesDef
{
public:
    
    TextFontPagesDef(char *fontName, int fontSize);
   ~TextFontPagesDef();
    
    void addPage(TextPageDef *newPage)      { _pages.push_back(newPage);    }
    int  getNumPages()                      { return _pages.size();         }
    TextPageDef     *getPageAt(int index)   { return _pages[index];         }
    char            *getFontName()          { return _fontName;             }
    int              getFontSize()          { return _fontSize;             }
    
private:
    
    std::vector<TextPageDef *>    _pages;
    int                             _fontSize;
    char *                          _fontName;
};

/** @brief TextImage 
 *
 */
class TextImage
{
public:
    TextImage();
   ~TextImage();
    
    bool initWithString(const char *pText, int nWidth, int nHeight, const char * pFontName, int nSize, bool releaseRAWData = true);
    
    TextFontPagesDef  * getPages()    { return _fontPages; }
    Font              * getFont()     { return _font;      }
    
    // debug only (this will go)
    bool debugSaveToFile(const char *pszFilePath, bool bIsToRGB);
    
private:
    
    bool createImageDataFromPages(TextFontPagesDef *thePages, bool releaseRAWData = true);
    bool createFontRef(const char *fontName, int size);
    bool createFontRender();
    bool generateTextGlyphs(const char * pText);
    unsigned char * preparePageGlyphData(TextPageDef *thePage, char *fontName, int fontSize);
    bool addGlyphsToLine(TextLineDef *line, const char *lineText);
    
    
    std::map<unsigned short int, GlyphDef>      _textGlyphs;
    TextFontPagesDef *                          _fontPages;
    Font *                                      _font;
    FontRender *                                _fontRender;
    
};


NS_CC_END


#endif
