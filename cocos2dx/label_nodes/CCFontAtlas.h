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
#ifndef _CCFontAtlas_h_
#define _CCFontAtlas_h_


#include <map>

NS_CC_BEGIN

struct FontLetterDefinition
{
    unsigned short  letteCharUTF16;
    float           U;
    float           V;
    float           width;
    float           height;
    float           offsetX;
    float           offsetY;
    int             textureID;
    float           commonLineHeight;
    float           anchorX;
    float           anchorY;
    bool            validDefinition;
};

class CC_DLL FontAtlas : public Object
{
    
public:
    
    FontAtlas(Font &theFont);
    virtual ~FontAtlas();
    
    void addLetterDefinition(const FontLetterDefinition &letterDefinition);
    bool getLetterDefinitionForChar(unsigned short  letteCharUTF16, FontLetterDefinition &outDefinition) const;
    void addTexture(Texture2D &texture, int slot);
    Texture2D & getTexture(int slot);
    void  setCommonLineHeight(float newHeight);
    float getCommonLineHeight() const;
    unsigned short int * getUTF16Text(const char *pText, int &outNumLetters) const;
    Font & getFont() const;
    
private:
    
    void relaseTextures();
    std::map<int, Texture2D *>                      _atlasTextures;
    std::map<unsigned short, FontLetterDefinition>  _fontLetterDefinitions;
    float                                           _commonLineHeight;
    Font &                                          _font;

};


NS_CC_END


#endif /* defined(__cocos2d_libs__CCFontAtlas__) */
