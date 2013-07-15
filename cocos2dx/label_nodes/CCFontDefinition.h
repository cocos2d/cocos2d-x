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

#ifndef _FontDefinition_h
#define _FontDefinition_h

#include "CCTextImage.h"
#include "CCFont.h"

NS_CC_BEGIN

struct LetterDefinition
{
    unsigned short  letteCharUTF8;
    float           U;
    float           V;
    float           width;
    float           height;
    float           offset;
    int             textureID;
    float           commonLineHeight;
};

/**
 */
class LabelFontDefinition
{
public:

    static LabelFontDefinition* create(const char *fontName, int fontSize, const char *letters, int textureSize = 512, bool debugOutput = false);

    LabelFontDefinition();
   ~LabelFontDefinition();

    bool init(const char *fontName, int fontSize, const char *letters, int textureSize, bool debugOutput);

    
    LetterDefinition & getLetterDefinition(unsigned short int theLetter);
    Texture2D * getTexture(int index);

    Font * getFont() { return _textImages->getFont(); }
    float  getCommonLineHeight() const { return _commonLineHeight; }
    
private:
    
    void   addLetterDef(LetterDefinition &defToAdd);
    
    TextImage *                                 _textImages;
    float                                       _commonLineHeight;
    std::map<unsigned short, LetterDefinition>  _fontLettersDefinitionUTF8;
    
};

NS_CC_END

#endif 
