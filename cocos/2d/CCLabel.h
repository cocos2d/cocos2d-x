/****************************************************************************
 Copyright (c) 2013      Zynga Inc.
 Copyright (c) 2013-2015 Chukong Technologies Inc.

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
#include "renderer/CCCustomCommand.h"
#include "2d/CCFontAtlas.h"
#include "base/ccTypes.h"

NS_CC_BEGIN

/**
 * @addtogroup _2d
 * @{
 */

/**
 * @brief Possible GlyphCollection used by Label.
 *
 * Specify a collections of characters to be load when Label created.
 * Consider using DYNAMIC.
 */
enum class GlyphCollection {
    DYNAMIC,
    NEHE,
    ASCII,
    CUSTOM
};


/**
 * @struct TTFConfig
 * @see `GlyphCollection`
 */
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

/**
 * @brief Label is a subclass of SpriteBatchNode that knows how to render text labels.
 *
 * Label can be created with:
 * - A true type font file.
 * - A bitmap font file.
 * - A char map file.
 * - The built in system font.
 *
 * Bitmap Font supported editors:
 * - http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
 * - http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
 * - http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
 * - http://www.angelcode.com/products/bmfont/ (Free, Windows only)
 * @js NA
 */
class CC_DLL Label : public SpriteBatchNode, public LabelProtocol
{
public:
    static const int DistanceFieldFontSize;

    /// @name Creators
    /// @{

    /**
    * Allocates and initializes a Label, with default settings.
    *
    * @return An automatically released Label object.
    */
    static Label* create();

    /**
     * Allocates and initializes a Label, base on platform-dependent API.
     *
     * @param text The initial text.
     * @param font A font file or a font family name.
     * @param fontSize The font size. This value must be > 0.
     * @param dimensions
     * @param hAlignment The text horizontal alignment.
     * @param vAlignment The text vertical alignment.
     *
     * @warning It will generate texture by the platform-dependent code.
     *
     * @return An automatically released Label object.
     */
    static Label* createWithSystemFont(const std::string& text, const std::string& font, float fontSize,
        const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT,
        TextVAlignment vAlignment = TextVAlignment::TOP);

    /**
    * Allocates and initializes a Label, base on FreeType2.
    *
    * @param text The initial text.
    * @param fontFilePath A font file.
    * @param fontSize The font size. This value must be > 0.
    * @param dimensions
    * @param hAlignment The text horizontal alignment.
    * @param vAlignment The text vertical alignment.
    *
    * @return An automatically released Label object.
    */
    static Label * createWithTTF(const std::string& text, const std::string& fontFilePath, float fontSize,
        const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT,
        TextVAlignment vAlignment = TextVAlignment::TOP);

    /**
    * Allocates and initializes a Label, base on FreeType2.
    *
    * @param ttfConfig A pointer to a TTFConfig object.
    * @param text The initial text.
    * @param hAlignment The text horizontal alignment.
    * @param maxLineWidth The max line width.
    *
    * @return An automatically released Label object.
    * @see TTFConfig setTTFConfig setMaxLineWidth
    */
    static Label* createWithTTF(const TTFConfig& ttfConfig, const std::string& text, TextHAlignment hAlignment = TextHAlignment::LEFT, int maxLineWidth = 0);

    /**
    * Allocates and initializes a Label, with a bitmap font file.
    *
    * @param bmfontPath A bitmap font file, it's a FNT format.
    * @param text The initial text.
    * @param hAlignment Text horizontal alignment.
    * @param maxLineWidth The max line width.
    * @param imageOffset
    *
    * @return An automatically released Label object.
    * @see setBMFontFilePath setMaxLineWidth
    */
    static Label* createWithBMFont(const std::string& bmfontPath, const std::string& text,
        const TextHAlignment& hAlignment = TextHAlignment::LEFT, int maxLineWidth = 0,
        const Vec2& imageOffset = Vec2::ZERO);

    /**
    * Allocates and initializes a Label, with char map configuration.
    *
    * @param charMapFile A char map file, it's a PNG format.
    * @param itemWidth The width in points of each element.
    * @param itemHeight The height in points of each element.
    * @param startCharMap The starting char of the char map.
    *
    * @return An automatically released Label object.
    */
    static Label * createWithCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);

    /**
    * Allocates and initializes a Label, with char map configuration.
    *
    * @param texture A pointer to an existing Texture2D object.
    * @param itemWidth The width in points of each element.
    * @param itemHeight The height in points of each element.
    * @param startCharMap The starting char of the char map.
    *
    * @return An automatically released Label object.
    */
    static Label * createWithCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap);

    /**
    * Allocates and initializes a Label, with char map configuration.
    *
    * @param plistFile A configuration file of char map.
    *
    * @return An automatically released Label object.
    */
    static Label * createWithCharMap(const std::string& plistFile);

    //  end of creators group
    /// @}

    /// @{
    /// @name Font methods

    /**
     * Sets a new TTF configuration to Label.
     * @see `TTFConfig`
     */
    virtual bool setTTFConfig(const TTFConfig& ttfConfig);

    /**
     * Returns the TTF configuration object used by the Label.
     * @see `TTFConfig`
     */
    virtual const TTFConfig& getTTFConfig() const { return _fontConfig;}

    /** Sets a new bitmap font to Label */
    virtual bool setBMFontFilePath(const std::string& bmfontFilePath, const Vec2& imageOffset = Vec2::ZERO);

    /** Returns the bitmap font used by the Label.*/
    const std::string& getBMFontFilePath() const { return _bmFontPath;}

    /**
     * Sets a new char map configuration to Label.
     *
     * @see `createWithCharMap(const std::string&,int,int,int)`
     */
    virtual bool setCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);

    /**
     * Sets a new char map configuration to Label.
     *
     * @see `createWithCharMap(Texture2D*,int,int,int)`
     */
    virtual bool setCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap);

    /**
     * Sets a new char map configuration to Label.
     *
     * @see `createWithCharMap(const std::string&)`
     */
    virtual bool setCharMap(const std::string& plistFile);

    /**
     * Sets a new system font to Label.
     *
     * @param font A font file or a font family name.
     * @warning
     */
    virtual void setSystemFontName(const std::string& font);

    /** Returns the system font used by the Label.*/
    virtual const std::string& getSystemFontName() const { return _systemFont;}

    /* Sets the system font size of Label.*/
    virtual void setSystemFontSize(float fontSize);

    /** Returns the bitmap font path used by the Label.*/
    virtual float getSystemFontSize() const { return _systemFontSize;}

    /**
     * @warning This method is not recommended for game developers.
     */
    virtual void requestSystemFontRefresh() { _systemFontDirty = true;}

    //  end of font methods
    /// @}

    /** Sets the text that this Label is to display.*/
    virtual void setString(const std::string& text) override;

    /** Return the text the Label is displaying.*/
    virtual const std::string& getString() const override {  return _originalUTF8String; }

    int getStringNumLines() const;

    int getStringLength() const;

    /**
     * Sets the text color of Label.
     *
     * The text color is different from the color of Node.
     *
     * @warning Limiting use to only when the Label created with true type font or system font.
     */
    virtual void setTextColor(const Color4B &color);

    /** Returns the text color of the Label.*/
    const Color4B& getTextColor() const { return _textColor;}

    /**
     * Enable shadow effect to Label.
     *
     * @todo Support blur for shadow effect.
     */
    virtual void enableShadow(const Color4B& shadowColor = Color4B::BLACK,const Size &offset = Size(2,-2), int blurRadius = 0);

    /**
     * Enable outline effect to Label.
     * @warning Limiting use to only when the Label created with true type font or system font.
     */
    virtual void enableOutline(const Color4B& outlineColor,int outlineSize = -1);

    /**
    * Enable glow effect to Label.
    * @warning Limiting use to only when the Label created with true type font.
    */
    virtual void enableGlow(const Color4B& glowColor);

    /**
     * Disable all effect to Label.
     * @warning Please use disableEffect(LabelEffect::ALL) instead of this API.
     */
    virtual void disableEffect();

    /**
     * Disable effect to Label.
     *
     * @see `LabelEffect`
     */
    virtual void disableEffect(LabelEffect effect);

    /** Sets the Label's text horizontal alignment.*/
    void setAlignment(TextHAlignment hAlignment) { setAlignment(hAlignment,_vAlignment);}

    /** Returns the Label's text horizontal alignment.*/
    TextHAlignment getTextAlignment() const { return _hAlignment;}

    /** Sets the Label's text alignment.*/
    void setAlignment(TextHAlignment hAlignment,TextVAlignment vAlignment);

    /** Sets the Label's text horizontal alignment.*/
    void setHorizontalAlignment(TextHAlignment hAlignment) { setAlignment(hAlignment,_vAlignment); }

    /** Returns the Label's text horizontal alignment.*/
    TextHAlignment getHorizontalAlignment() const { return _hAlignment; }

    /** Sets the Label's text vertical alignment.*/
    void setVerticalAlignment(TextVAlignment vAlignment) { setAlignment(_hAlignment,vAlignment); }

    /** Returns the Label's text vertical alignment.*/
    TextVAlignment getVerticalAlignment() const { return _vAlignment; }

    /**
     * Specify what happens when a line is too long for Label.
     *
     * @param breakWithoutSpace Lines are automatically broken between words if this value is false.
     */
    void setLineBreakWithoutSpace(bool breakWithoutSpace);

    /**
     * Makes the Label at most this line untransformed width.
     * The Label's max line width be used for force line breaks if the value not equal zero.
     */
    void setMaxLineWidth(float maxLineWidth);
    float getMaxLineWidth() { return _maxLineWidth; }

    /**
     * Makes the Label exactly this untransformed width.
     *
     * The Label's width be used for text align if the value not equal zero.
     */
    void setWidth(float width) { setDimensions(width,_labelHeight);}
    float getWidth() const { return _labelWidth; }

    /**
     * Makes the Label exactly this untransformed height.
     *
     * The Label's height be used for text align if the value not equal zero.
     * The text will display of incomplete when the size of Label not enough to support display all text.
     */
    void setHeight(float height){ setDimensions(_labelWidth, height); }
    float getHeight() const { return _labelHeight; }

    /** Sets the untransformed size of the Label in a more efficient way. */
    void setDimensions(float width, float height);
    const Size& getDimensions() const{ return _labelDimensions;}

    /** Update content immediately.*/
    virtual void updateContent();

    /**
     * Provides a way to treats each character like a Sprite.
     * @warning No support system font.
     */
    virtual Sprite * getLetter(int lettetIndex);

    /** Makes the Label to clip upper and lower margin for reduce height of Label.*/
    void setClipMarginEnabled(bool clipEnabled) { _clipEnabled = clipEnabled; }

    bool isClipMarginEnabled() const { return _clipEnabled; }

    /** Sets the line height of the Label.
     * @warning Not support system font.
     * @since v3.2.0
     */
    void setLineHeight(float height);

    /**
     * Returns the line height of this Label.
     * @warning Not support system font.
     * @since v3.2.0
     */
    float getLineHeight() const;

    /**
     * Sets the additional kerning of the Label.
     *
     * @warning Not support system font.
     * @since v3.2.0
     */
    void setAdditionalKerning(float space);

    /**
     * Returns the additional kerning of the Label.
     *
     * @warning Not support system font.
     * @since v3.2.0
     */
    float getAdditionalKerning() const;

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

    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

    virtual void setCameraMask(unsigned short mask, bool applyChildren = true) override;

    CC_DEPRECATED_ATTRIBUTE static Label* create(const std::string& text, const std::string& font, float fontSize,
        const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT,
        TextVAlignment vAlignment = TextVAlignment::TOP);

    CC_DEPRECATED_ATTRIBUTE virtual void setFontDefinition(const FontDefinition& textDefinition);
    CC_DEPRECATED_ATTRIBUTE const FontDefinition& getFontDefinition() const { return _fontDefinition; }

    /**
     * @deprecated Use `getLineHeight` instead.
     */
    CC_DEPRECATED_ATTRIBUTE int getCommonLineHeight() const { return (int)getLineHeight();}

CC_CONSTRUCTOR_ACCESS:
    /**
     * Constructor of Label.
     * @js NA
     */
    Label(FontAtlas *atlas = nullptr, TextHAlignment hAlignment = TextHAlignment::LEFT,
      TextVAlignment vAlignment = TextVAlignment::TOP,bool useDistanceField = false,bool useA8Shader = false);

    /**
     * Destructor of Label.
     * @js NA
     * @lua NA
     */
    virtual ~Label();

protected:
    void onDraw(const Mat4& transform, bool transformUpdated);

    struct LetterInfo
    {
        FontLetterDefinition def;

        Vec2 position;
        Size  contentSize;
        int   atlasIndex;
    };
    enum class LabelType {

        TTF,
        BMFONT,
        CHARMAP,
        STRING_TEXTURE
    };

    virtual void setFontAtlas(FontAtlas* atlas,bool distanceFieldEnabled = false, bool useA8Shader = false);

    bool recordLetterInfo(const cocos2d::Vec2& point,const FontLetterDefinition& letterDef, int spriteIndex);
    bool recordPlaceholderInfo(int spriteIndex);

    void setFontScale(float fontScale);

    virtual void alignText();

    bool computeHorizontalKernings(const std::u16string& stringToRender);

    void computeStringNumLines();

    void updateQuads();

    virtual void updateColor() override;

    virtual void updateShaderProgram();

    void createSpriteForSystemFont();

    void createShadowSpriteForSystemFont();

    void reset();

    std::string _bmFontPath;

    bool _isOpacityModifyRGB;
    bool _contentDirty;

    bool _systemFontDirty;
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

    float _additionalKerning;
    float _commonLineHeight;
    bool  _lineBreakWithoutSpaces;
    int * _horizontalKernings;

    float _maxLineWidth;
    Size  _labelDimensions;
    float _labelWidth;
    float _labelHeight;
    TextHAlignment _hAlignment;
    TextVAlignment _vAlignment;

    int           _currNumLines;
    std::u16string _currentUTF16String;
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
    Mat4  _shadowTransform;
    Color4F _shadowColor4F;
    Color3B _shadowColor3B;
    GLubyte _shadowOpacity;
    Sprite*   _shadowNode;

    int     _outlineSize;

    Color4B _textColor;
    Color4F _textColorF;

    bool _clipEnabled;
    bool _blendFuncDirty;
    /// whether or not the sprite was inside bounds the previous frame
    bool _insideBounds;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Label);

    friend class LabelTextFormatter;
};

// end group
/// @}

NS_CC_END

#endif /*__COCOS2D_CCLABEL_H */
