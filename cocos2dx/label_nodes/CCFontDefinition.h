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

#ifndef _FontDefinition_h_
#define _FontDefinition_h_

#include "CCTextImage.h"
#include "CCFont.h"
#include "CCFontAtlas.h"

NS_CC_BEGIN

#define DEFAULT_ATLAS_TEXTURE_SIZE 1024

/**
 */
class CC_DLL FontDefinitionTTF : public Object
{
public:

    static FontDefinitionTTF* create(const char *fontName, int fontSize, const char *letters, int textureSize = DEFAULT_ATLAS_TEXTURE_SIZE);
    FontLetterDefinition & getLetterDefinition(unsigned short int theLetter);
    Texture2D * getTexture(int index);
    int         getNumTextures();
    Font *      getFont()                        { return _textImages->getFont(); }
    float       getCommonLineHeight()            { return _commonLineHeight;      }
    FontAtlas * createFontAtlas();
    
private:
    
     FontDefinitionTTF();
    ~FontDefinitionTTF();
    
    bool initDefinition(const char *fontName, int fontSize, const char *letters, int textureSize);
    bool prepareLetterDefinitions(TextFontPagesDef *pageDefs);
    void addLetterDefinition(FontLetterDefinition &defToAdd);
    
    TextImage *                                     _textImages;
    std::map<unsigned short, FontLetterDefinition>  _fontLettersDefinitionUTF16;
    float                                           _commonLineHeight;
    
};

NS_CC_END

#endif 
