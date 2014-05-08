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

#include "2d/CCSpriteBatchNode.h"
#include "base/ccTypes.h"
#include "renderer/CCCustomCommand.h"
#include "2d/CCFontAtlas.h"

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

    _ttfConfig(const char* filePath = "",int size = 12, const GlyphCollection& glyphCollection = GlyphCollection::DYNAMIC,
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
    static const int DistanceFieldFontSize;

    static Label* create();

    /** Creates a label with an initial string,font[font name or font file],font size, dimension in points, horizontal alignment and vertical alignment.
     * @warning It will generate texture by the platform-dependent code
     */
    static Label* createWithSystemFont(const std::string& text, const std::string& font, float fontSize,
        const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT,
        TextVAlignment vAlignment = TextVAlignment::TOP);

    /** Creates a label with an initial string,font file,font size, dimension in points, horizontal alignment and vertical alignment.
     * @warning Not support font name.
     */
    static Label * createWithTTF(const std::string& text, const std::string& fontFile, float fontSize,
        const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT,
        TextVAlignment vAlignment = TextVAlignment::TOP);

    /** Create a label with TTF configuration
     * @warning Not support font name.
     */
    static Label* createWithTTF(const TTFConfig& ttfConfig, const std::string& text, TextHAlignment alignment = TextHAlignment::LEFT, int maxLineWidth = 0);
    
    /* Creates a label with an FNT file,an initial string,horizontal alignment,max line width and the offset of image*/
    static Label* createWithBMFont(const std::string& bmfontFilePath, const std::string& text,
        const TextHAlignment& alignment = TextHAlignment::LEFT, int maxLineWidth = 0, 
        const Vector2& imageOffset = Vector2::ZERO);
    
    static Label * createWithCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);
    static Label * createWithCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap);
    static Label * createWithCharMap(const std::string& plistFile);

    /** set TTF configuration for Label */
    virtual bool setTTFConfig(const TTFConfig& ttfConfig);
    virtual const TTFConfig& getTTFConfig() const { return _fontConfig;}

    virtual bool setBMFontFilePath(const std::string& bmfontFilePath, const Vector2& imageOffset = Vector2::ZERO);
    const std::string& getBMFontFilePath() const { return _bmFontPath;}

    virtual bool setCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);
    virtual bool setCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap);
    virtual bool setCharMap(const std::string& plistFile);

    /* Sets the system font[font name or font file] of label*/
    virtual void setSystemFontName(const std::string& systemFont);
    virtual const std::string& getSystemFontName() const { return _systemFont;}

    /* Sets the system font size of label.*/
    virtual void setSystemFontSize(float fontSize);
    virtual float getSystemFontSize() const { return _systemFontSize;}

    /** changes the string to render
    * @warning It is as expensive as changing the string if you haven't set up TTF/BMFont/CharMap for the label.
    */
    virtual void setString(const std::string& text) override;

    virtual const std::string& getString() const override {  return _originalUTF8String; }

    /**
     * Enable shadow for the label
     *
     * @todo support blur for shadow effect
     */
    virtual void enableShadow(const Color4B& shadowColor = Color4B::BLACK,const Size &offset = Size(2,-2), int blurRadius = 0);

    /** only support for TTF */
    virtual void enableOutline(const Color4B& outlineColor,int outlineSize = -1);

    /** only support for TTF */
    virtual void enableGlow(const Color4B& glowColor);

    /** disable shadow/outline/glow rendering */
    virtual void disableEffect();

    void setAlignment(TextHAlignment hAlignment) { setAlignment(hAlignment,_vAlignment);}
    TextHAlignment getTextAlignment() const { return _hAlignment;}

    void setAlignment(TextHAlignment hAlignment,TextVAlignment vAlignment);

    void setHorizontalAlignment(TextHAlignment hAlignment) { setAlignment(hAlignment,_vAlignment); }
    TextHAlignment getHorizontalAlignment() const { return _hAlignment; }

    void setVerticalAlignment(TextVAlignment vAlignment) { setAlignment(_hAlignment,vAlignment); }
    TextVAlignment getVerticalAlignment() const { return _vAlignment; }

    void setLineBreakWithoutSpace(bool breakWithoutSpace);

    /** Sets the max line width of the label.
     * The label's max line width be used for force line breaks if the set value not equal zero.
     * The label's width and max line width has not always to be equal.
     */
    void setMaxLineWidth(unsigned int maxLineWidth);
    unsigned int getMaxLineWidth() { return _maxLineWidth;}

    /** Sets the untransformed size of the label.
     * The label's width be used for text align if the set value not equal zero.
     * The label's max line width will be equal to the same value.
     */
    void setWidth(unsigned int width) { setDimensions(width,_labelHeight);}
    unsigned int getWidth() const { return _labelWidth; }  

    /** Sets the untransformed size of the label.
     * The label's height be used for text align if the set value not equal zero.
     * The text will display of incomplete when the size of label not enough to support display all text.
     */
    void setHeight(unsigned int height){ setDimensions(_labelWidth,height);}
    unsigned int getHeight() const { return _labelHeight;}   

    /** Sets the untransformed size of the label in a more efficient way. */
    void setDimensions(unsigned int width,unsigned int height);
    const Size& getDimensions() const{ return _labelDimensions;}

    /** update content immediately.*/
    virtual void updateContent();

    /** Sets the text color
     *
     */
    virtual void setTextColor(const Color4B &color);

    const Color4B& getTextColor() const { return _textColor;}

    virtual Sprite * getLetter(int lettetIndex);

    /** clip upper and lower margin for reduce height of label.
     */
    void setClipMarginEnabled(bool clipEnabled) { _clipEnabled = clipEnabled; }
    bool isClipMarginEnabled() const { return _clipEnabled; }
    // font related stuff
    int getCommonLineHeight() const;
    
    // string related stuff
    int getStringNumLines() const { return _currNumLines;}
    int getStringLength() const;

    FontAtlas* getFontAtlas() { return _fontAtlas; }
    
    virtual void setBlendFunc(const BlendFunc &blendFunc) override;

    virtual bool isOpacityModifyRGB() const override;
    virtual void setOpacityModifyRGB(bool isOpacityModifyRGB) override;
    virtual void updateDisplayedColor(const Color3B& parentColor) override;
    virtual void updateDisplayedOpacity(GLubyte parentOpacity) override;

    virtual void setScale(float scale) override;
    virtual void setScaleX(float scaleX) override;
    virtual void setScaleY(float scaleY) override;
    virtual float getScaleX() const override;
    virtual float getScaleY() const override;

    virtual void addChild(Node * child, int zOrder=0, int tag=0) override;
    virtual void sortAllChildren() override;

    virtual std::string getDescription() const override;

    virtual const Size& getContentSize() const override;

    virtual Rect getBoundingBox() const override;

    virtual void visit(Renderer *renderer, const Matrix &parentTransform, bool parentTransformUpdated) override;
    virtual void draw(Renderer *renderer, const Matrix &transform, bool transformUpdated) override;

    CC_DEPRECATED_ATTRIBUTE static Label* create(const std::string& text, const std::string& font, float fontSize,
        const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT,
        TextVAlignment vAlignment = TextVAlignment::TOP);

    CC_DEPRECATED_ATTRIBUTE virtual void setFontDefinition(const FontDefinition& textDefinition);
    CC_DEPRECATED_ATTRIBUTE const FontDefinition& getFontDefinition() const { return _fontDefinition; }

protected:
    void onDraw(const Matrix& transform, bool transformUpdated);

    struct LetterInfo
    {
        FontLetterDefinition def;

        Vector2 position;
        Size  contentSize;
        int   atlasIndex;
    };
    enum class LabelType {

        TTF,
        BMFONT,
        CHARMAP,
        STRING_TEXTURE
    };

    /**
    * @js NA
    */
    Label(FontAtlas *atlas = nullptr, TextHAlignment hAlignment = TextHAlignment::LEFT, 
        TextVAlignment vAlignment = TextVAlignment::TOP,bool useDistanceField = false,bool useA8Shader = false);
    /**
    * @js NA
    * @lua NA
    */
    virtual ~Label();

    virtual void setFontAtlas(FontAtlas* atlas,bool distanceFieldEnabled = false, bool useA8Shader = false);

    bool recordLetterInfo(const cocos2d::Vector2& point,const FontLetterDefinition& letterDef, int spriteIndex);
    bool recordPlaceholderInfo(int spriteIndex);

    void setFontScale(float fontScale);
    
    virtual void alignText();
    
    bool computeHorizontalKernings(const std::u16string& stringToRender);
    bool setCurrentString(const std::u16string& stringToSet);
    bool setOriginalString(const std::u16string& stringToSet);
    void computeStringNumLines();

    void updateQuads();

    virtual void updateColor() override;

    virtual void updateShaderProgram();

    void drawShadowWithoutBlur();

    void drawTextSprite(Renderer *renderer, bool parentTransformUpdated);

    void createSpriteWithFontDefinition();

    void updateFont();
    void reset();

    std::string _bmFontPath;

    bool _isOpacityModifyRGB;
    bool _contentDirty;

    bool _fontDirty;
    std::string _systemFont;
    float         _systemFontSize;
    LabelType _currentLabelType;

    std::vector<SpriteBatchNode*> _batchNodes;
    FontAtlas *                   _fontAtlas;
    std::vector<LetterInfo>       _lettersInfo;

    TTFConfig _fontConfig;

    //compatibility with older LabelTTF
    Sprite* _textSprite;
    FontDefinition _fontDefinition;
    bool  _compatibleMode;

    //! used for optimization
    Sprite *_reusedLetter;
    Rect _reusedRect;
    int _limitShowCount;

    float _commonLineHeight;
    bool  _lineBreakWithoutSpaces;
    int * _horizontalKernings;

    unsigned int _maxLineWidth;
    Size         _labelDimensions;
    unsigned int _labelWidth;
    unsigned int _labelHeight;
    TextHAlignment _hAlignment;
    TextVAlignment _vAlignment;

    int           _currNumLines;
    std::u16string _currentUTF16String;
    std::u16string _originalUTF16String;
    std::string          _originalUTF8String;

    float _fontScale;

    bool _useDistanceField;
    bool _useA8Shader;

    LabelEffect _currLabelEffect;
    Color4B _effectColor;
    Color4F _effectColorF;

    GLuint _uniformEffectColor;
    GLuint _uniformTextColor;
    CustomCommand _customCommand;   

    bool    _shadowDirty;
    bool    _shadowEnabled;
    Size    _shadowOffset;
    int     _shadowBlurRadius;
    Matrix  _shadowTransform;
    Color3B _shadowColor;
    float   _shadowOpacity;
    Sprite*   _shadowNode;

    int     _outlineSize;

    Color4B _textColor;
    Color4F _textColorF;

    bool _clipEnabled;
    bool _blendFuncDirty;
    bool _insideBounds;                     /// whether or not the sprite was inside bounds the previous frame

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Label);

    friend class LabelTextFormatter;
};


NS_CC_END

#endif /*__COCOS2D_CCLABEL_H */
