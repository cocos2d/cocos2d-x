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

typedef struct _ttfConfig
{
    std::string fontFilePath;
    int fontSize;
    GlyphCollection glyphs;
    const char *customGlyphs;
    bool distanceFieldEnabled;
    int outlineSize;

    _ttfConfig(const char* filePath = "",int size = 36, const GlyphCollection& glyphCollection = GlyphCollection::NEHE,
        const char *customGlyphCollection = nullptr,bool useDistanceField = false,int outline = 0)
        :fontFilePath(filePath)
        ,fontSize(size)
        ,glyphs(glyphCollection)
        ,customGlyphs(customGlyphCollection)
        ,distanceFieldEnabled(useDistanceField)
        ,outlineSize(outline)
    {
        if(outline > 0)
        {
            distanceFieldEnabled = false;
        }
    }
}TTFConfig;

class CC_DLL Label : public SpriteBatchNode, public LabelProtocol
{
public:
    static const int DefultFontSize;

    static Label* create();

    CC_DEPRECATED_ATTRIBUTE static Label* createWithTTF(const std::string& label, const std::string& fontFilePath, 
        int fontSize, int lineSize = 0, TextHAlignment alignment = TextHAlignment::LEFT, 
        GlyphCollection glyphs = GlyphCollection::NEHE, const char *customGlyphs = 0, bool useDistanceField = false);

    /** create a label with TTF configuration
     * It will generate texture of character by freetype.
     */
    static Label* createWithTTF(const TTFConfig& ttfConfig, const std::string& text, TextHAlignment alignment = TextHAlignment::LEFT, int lineWidth = 0);
    
    static Label* createWithBMFont(const std::string& bmfontFilePath, const std::string& text,
        const TextHAlignment& alignment = TextHAlignment::LEFT, int lineWidth = 0, 
        const Point& imageOffset = Point::ZERO);
    
    static Label * createWithCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);
    static Label * createWithCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap);
    static Label * createWithCharMap(const std::string& plistFile);

    /** set TTF configuration for Label */
    virtual bool setTTFConfig(const TTFConfig& ttfConfig);

    virtual bool setBMFontFilePath(const std::string& bmfontFilePath, const Point& imageOffset = Point::ZERO);

    virtual bool setCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);
    virtual bool setCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap);
    virtual bool setCharMap(const std::string& plistFile);

    /** changes the string to render
    * 
    */
    virtual void setString(const std::string& text) override;

    virtual const std::string& getString() const override {  return _originalUTF8String; }


    CC_DEPRECATED_ATTRIBUTE void setLabelEffect(LabelEffect effect,const Color3B& effectColor);

    /**
     * Enable shadow for the label
     *
     * @todo support blur for shadow effect
     */
    virtual void enableShadow(const Color3B& shadowColor = Color3B::BLACK,const Size &offset = Size(2,-2), float opacity = 0.75f, int blurRadius = 0);

    /** only support for TTF */
    virtual void enableOutline(const Color4B& outlineColor,int outlineSize = -1);

    /** only support for TTF */
    virtual void enableGlow(const Color3B& glowColor);

    /** disable shadow/outline/glow rendering */
    virtual void disableEffect();
    

    virtual void setAlignment(TextHAlignment hAlignment,bool aligntext = true);
    TextHAlignment getTextAlignment() const { return _hAlignment;}

    virtual void setAlignment(TextHAlignment hAlignment,TextVAlignment vAlignment,bool aligntext = true);

    virtual void setHorizontalAlignment(TextHAlignment alignment,bool aligntext = true);
    TextHAlignment getHorizontalAlignment() const { return _hAlignment; }

    virtual void setVerticalAlignment(TextVAlignment verticalAlignment,bool aligntext = true);
    TextVAlignment getVerticalAlignment() const { return _vAlignment; }

    virtual void setLineBreakWithoutSpace(bool breakWithoutSpace);

    /** Sets the max line width of the label.
     * The label's max line width be used for force line breaks if the set value not equal zero.
     * The label's width and max line width has not always to be equal.
     */
    virtual void setMaxLineWidth(unsigned int maxLineWidth);
    unsigned int getMaxLineWidth() { return _maxLineWidth;}

    /** Sets the untransformed size of the label.
     * The label's width be used for text align if the set value not equal zero.
     * The label's max line width will be equal to the same value.
     */
    virtual void setWidth(unsigned int width);
    unsigned int getWidth() const { return _labelWidth; }  

    /** Sets the untransformed size of the label.
     * The label's height be used for text align if the set value not equal zero.
     * The text will display of incomplete when the size of label not enough to support display all text.
     */
    virtual void setHeight(unsigned int height);
    unsigned int getHeight() const { return _labelHeight;}   

    /** Sets the untransformed size of the label in a more efficient way. */
    virtual void setDimensions(unsigned int width,unsigned int height);
    
    virtual bool isOpacityModifyRGB() const override;
    virtual void setOpacityModifyRGB(bool isOpacityModifyRGB) override;
    virtual void setColor(const Color3B& color) override;

    virtual Sprite * getLetter(int lettetIndex);

    // font related stuff
    int getCommonLineHeight() const;
    
    // string related stuff
    int getStringNumLines() const;
    CC_DEPRECATED_ATTRIBUTE int getStringLenght() const { return getStringLength(); }
    int getStringLength() const;
    
    virtual void visit(Renderer *renderer, const kmMat4 &parentTransform, bool parentTransformUpdated) override;
    virtual void draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated) override;

    virtual void setScale(float scale) override;
    virtual void setScaleX(float scaleX) override;
    virtual void setScaleY(float scaleY) override;
    virtual float getScaleX() const override;
    virtual float getScaleY() const override;

    virtual void addChild(Node * child, int zOrder=0, int tag=0) override;
    virtual std::string getDescription() const override;

protected:
    void onDraw(const kmMat4& transform, bool transformUpdated);

    struct LetterInfo
    {
        FontLetterDefinition def;

        Point position;
        Size  contentSize;
    };
    /**
    * @js NA
    */
    Label(FontAtlas *atlas = nullptr, TextHAlignment alignment = TextHAlignment::LEFT, bool useDistanceField = false,bool useA8Shader = false);
    /**
    * @js NA
    * @lua NA
    */
    virtual ~Label();

    virtual bool initWithFontAtlas(FontAtlas* atlas,bool distanceFieldEnabled = false, bool useA8Shader = false);

    bool recordLetterInfo(const cocos2d::Point& point,const FontLetterDefinition& letterDef, int spriteIndex);
    bool recordPlaceholderInfo(int spriteIndex);

    void setFontScale(float fontScale);

    virtual bool init();
    
    virtual void alignText();
    
    bool computeHorizontalKernings(unsigned short int *stringToRender);
    bool setCurrentString(unsigned short *stringToSet);
    bool setOriginalString(unsigned short *stringToSet);
    void resetCurrentString();
    void computeStringNumLines();

    void updateSpriteWithLetterDefinition(const FontLetterDefinition &theDefinition, Texture2D *theTexture);

    virtual void updateColor() override;

    virtual void initProgram();

    void drawShadowWithoutBlur();

    bool _isOpacityModifyRGB;

    std::vector<SpriteBatchNode*> _batchNodes;
    FontAtlas *                   _fontAtlas;
    std::vector<LetterInfo>       _lettersInfo;

    TTFConfig _fontConfig;

    //! used for optimization
    Sprite *_reusedLetter;
    Rect _reusedRect;
    int _limitShowCount;

    float _commonLineHeight;
    bool  _lineBreakWithoutSpaces;
    int * _horizontalKernings;

    unsigned int _maxLineWidth;
    unsigned int _labelWidth;
    unsigned int _labelHeight;
    TextHAlignment _hAlignment;
    TextVAlignment _vAlignment;

    int           _currNumLines;
    unsigned short int * _currentUTF16String;
    unsigned short int * _originalUTF16String;
    std::string          _originalUTF8String;

    float _fontScale;

    bool _useDistanceField;
    bool _useA8Shader;

    LabelEffect _currLabelEffect;
    Color3B _effectColor;

    GLuint _uniformEffectColor;
    CustomCommand _customCommand;   

    Size    _shadowOffset;
    float   _shadowOpacity;
    int     _shadowBlurRadius;
    kmMat4  _parentTransform;

    Color4B _outlineColor;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Label);

    friend class LabelTextFormatter;
};


NS_CC_END

#endif /*__COCOS2D_CCLABEL_H */
