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
#include "CCLabelTextFormatProtocol.h"
#include "ccTypes.h"
#include "renderer/CCCustomCommand.h"

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

//fwd
struct FontLetterDefinition;
class FontAtlas;

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

class CC_DLL Label : public SpriteBatchNode, public LabelTextFormatProtocol
{
public:
    static Label* create();

    CC_DEPRECATED_ATTRIBUTE static Label* createWithTTF(const std::string& label, const std::string& fontFilePath, int fontSize, int lineSize = 0, TextHAlignment alignment = TextHAlignment::CENTER, GlyphCollection glyphs = GlyphCollection::NEHE, const char *customGlyphs = 0, bool useDistanceField = false);
    static Label* createWithTTF(const TTFConfig& ttfConfig, const std::string& text, TextHAlignment alignment = TextHAlignment::CENTER, int lineWidth = 0);
    
    static Label* createWithBMFont(const std::string& bmfontFilePath, const std::string& text,const TextHAlignment& alignment = TextHAlignment::CENTER, int lineWidth = 0);
    
    static Label * createWithCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);
    static Label * createWithCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap);
    static Label * createWithCharMap(const std::string& plistFile);

    bool setTTFConfig(const TTFConfig& ttfConfig);

    bool setBMFontFilePath(const std::string& bmfontFilePath);

    bool setCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);
    bool setCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap);
    bool setCharMap(const std::string& plistFile);

    bool setString(const std::string& text, const TextHAlignment& alignment = TextHAlignment::CENTER, float lineWidth = -1, bool lineBreakWithoutSpaces = false);

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
    virtual std::vector<LetterInfo>     *getLettersInfo() override { return &_lettersInfo; };
    virtual bool recordLetterInfo(const cocos2d::Point& point,unsigned short int theChar, int spriteIndex) override;
    virtual bool recordPlaceholderInfo(int spriteIndex) override;
    virtual float getLetterPosXLeft( int index ) const override;
    virtual float getLetterPosXRight( int index ) const override;

    virtual Sprite * getLetter(int ID) override;
    
    // font related stuff
    virtual int getCommonLineHeight() const override;
    virtual int getKerningForCharsPair(unsigned short first, unsigned short second) const override;
    virtual int getXOffsetForChar(unsigned short c) const override;
    virtual int getYOffsetForChar(unsigned short c) const override;
    virtual int getAdvanceForChar(unsigned short c, int hintPositionInString) const override;
    virtual Rect getRectForChar(unsigned short c) const override;
    
    // string related stuff
    virtual int getStringNumLines() const override;
    virtual int getStringLenght() const override;
    virtual unsigned short getCharAtStringPosition(int position) const override;
    virtual unsigned short * getUTF8String() const override;
    virtual void assignNewUTF8String(unsigned short *newString) override;
    virtual TextHAlignment getTextAlignment() const override;
    
    // label related stuff
    virtual float getMaxLineWidth() const override;
    virtual bool breakLineWithoutSpace() const override;
    virtual Size getLabelContentSize() const override;
    virtual void setLabelContentSize(const Size &newSize) override;
    
    // carloX
    virtual const std::string& getString() const { static std::string _ret("not implemented"); return _ret; }
    void addChild(Node * child, int zOrder=0, int tag=0) override;

    virtual std::string getDescription() const override;
    virtual void draw(void) override;
    virtual void onDraw();

private:
    /**
     * @js NA
     */
    Label(FontAtlas *atlas = nullptr, TextHAlignment alignment = TextHAlignment::CENTER, bool useDistanceField = false,bool useA8Shader = false);
    /**
     * @js NA
     * @lua NA
     */
   ~Label();
    
   bool initWithFontAtlas(FontAtlas* atlas,bool distanceFieldEnabled = false, bool useA8Shader = false);

    void setFontSize(int fontSize);
    
    bool init();
    
    void alignText();   
    
    bool computeAdvancesForString(unsigned short int *stringToRender);
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
    Size * _advances;
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
