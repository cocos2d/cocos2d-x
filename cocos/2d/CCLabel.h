/****************************************************************************
 Copyright (c) 2013      Zynga Inc.
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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


#ifndef _COCOS2D_CCLABEL_H_
#define _COCOS2D_CCLABEL_H_

#include "CCSpriteBatchNode.h"
#include "ccTypes.h"
#include "renderer/CCCustomCommand.h"
#include "CCFontAtlas.h"

NS_CC_BEGIN

enum class GlyphCollection {
    
    DYNAMIC,
    NEHE,
    ASCII,
    CUSTOM
};

enum class LabelEffect {

    NORMAL,
    OUTLINE,
    SHADOW,
    GLOW
};

struct LetterInfo
{
    FontLetterDefinition def;

    Point position;
    Size  contentSize;
};

typedef struct _ttfConfig
{
    std::string fontFilePath;
    int fontSize;
    GlyphCollection glyphs;
    const char *customGlyphs;
    bool distanceFieldEnabled;

    _ttfConfig(const char* filePath,int size = 36, const GlyphCollection& glyphCollection = GlyphCollection::NEHE,
        const char *customGlyphCollection = nullptr,bool useDistanceField = false)
        :fontFilePath(filePath)
        ,fontSize(size)
        ,glyphs(glyphCollection)
        ,customGlyphs(customGlyphCollection)
        ,distanceFieldEnabled(useDistanceField)
    {}
}TTFConfig;

class CC_DLL Label : public SpriteBatchNode, public LabelProtocol
{
public:
    static Label* create();

    CC_DEPRECATED_ATTRIBUTE static Label* createWithTTF(const std::string& label, const std::string& fontFilePath, int fontSize, int lineSize = 0, TextHAlignment alignment = TextHAlignment::LEFT, GlyphCollection glyphs = GlyphCollection::NEHE, const char *customGlyphs = 0, bool useDistanceField = false);
    static Label* createWithTTF(const TTFConfig& ttfConfig, const std::string& text, TextHAlignment alignment = TextHAlignment::LEFT, int lineWidth = 0);
    
    static Label* createWithBMFont(const std::string& bmfontFilePath, const std::string& text,const TextHAlignment& alignment = TextHAlignment::LEFT, int lineWidth = 0);
    
    static Label * createWithCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);
    static Label * createWithCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap);
    static Label * createWithCharMap(const std::string& plistFile);

    bool setTTFConfig(const TTFConfig& ttfConfig);

    bool setBMFontFilePath(const std::string& bmfontFilePath);

    bool setCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);
    bool setCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap);
    bool setCharMap(const std::string& plistFile);

    virtual void setString(const std::string& text) override;

    //only support for TTF
    void setLabelEffect(LabelEffect effect,const Color3B& effectColor);
    
    virtual void setAlignment(TextHAlignment alignment);
    virtual void setWidth(float width);
    virtual void setLineBreakWithoutSpace(bool breakWithoutSpace);
    virtual void setScale(float scale) override;
    virtual void setScaleX(float scaleX) override;
    virtual void setScaleY(float scaleY) override;
    virtual float getScaleX() const;
    virtual float getScaleY() const;

    virtual bool isOpacityModifyRGB() const override;
    virtual void setOpacityModifyRGB(bool isOpacityModifyRGB) override;
    virtual void setColor(const Color3B& color) override;
    
     // CCLabelTextFormat protocol implementation
    virtual std::vector<LetterInfo>     *getLettersInfo() { return &_lettersInfo; };
    virtual bool recordLetterInfo(const cocos2d::Point& point,unsigned short int theChar, int spriteIndex);
    virtual bool recordPlaceholderInfo(int spriteIndex);

    virtual Sprite * getLetter(int ID);
    
    // font related stuff
    virtual int getCommonLineHeight() const;
    virtual int* getKernings() const { return _horizontalKernings;}
    
    // string related stuff
    virtual int getStringNumLines() const;
    virtual int getStringLenght() const;
    virtual unsigned short * getUTF16String() const;
    virtual void assignNewUTF16String(unsigned short *newString);
    virtual TextHAlignment getTextAlignment() const;
    
    // label related stuff
    virtual float getMaxLineWidth() const;
    virtual bool breakLineWithoutSpace() const;
    
    // carloX
    virtual const std::string& getString() const override {  return _originalUTF8String; }
    void addChild(Node * child, int zOrder=0, int tag=0) override;

    virtual std::string getDescription() const override;
    virtual void draw(void) override;
    virtual void onDraw();

    virtual FontAtlas* getFontAtlas() const {return _fontAtlas;}

private:
    /**
     * @js NA
     */
    Label(FontAtlas *atlas = nullptr, TextHAlignment alignment = TextHAlignment::LEFT, bool useDistanceField = false,bool useA8Shader = false);
    /**
     * @js NA
     * @lua NA
     */
   ~Label();
    
   bool initWithFontAtlas(FontAtlas* atlas,bool distanceFieldEnabled = false, bool useA8Shader = false);

    void setFontSize(int fontSize);
    
    bool init();
    
    void alignText();   
    
    bool computeHorizontalKernings(unsigned short int *stringToRender);
    bool setCurrentString(unsigned short *stringToSet);
    bool setOriginalString(unsigned short *stringToSet);
    void resetCurrentString();

    Sprite * updateSpriteWithLetterDefinition(Sprite *spriteToUpdate, const FontLetterDefinition &theDefinition, Texture2D *theTexture);

    virtual void updateColor() override;

    //! used for optimization
    Sprite *_reusedLetter;
    std::vector<LetterInfo> _lettersInfo;

    float _commonLineHeight;
    bool _lineBreakWithoutSpaces;
    float _width;
    TextHAlignment _alignment;
    unsigned short int * _currentUTF16String;
    unsigned short int * _originalUTF16String;
    std::string          _originalUTF8String;
    int * _horizontalKernings;
    FontAtlas * _fontAtlas;
    bool _isOpacityModifyRGB;

    bool _useDistanceField;
    bool _useA8Shader;
    int _fontSize;

    LabelEffect _currLabelEffect;
    Color3B _effectColor;

    GLuint _uniformEffectColor;

    CustomCommand _customCommand;
};


NS_CC_END

#endif /*__COCOS2D_CCLABEL_H */
