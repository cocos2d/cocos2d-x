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

    /** 使用初始字符串，字体（字体名称或字体文件），字号，尺寸，水平对齐方式和
        垂直对齐方式创建一个Label
     * @warning 会根据不同平台生成Texture
     */
    static Label* createWithSystemFont(const std::string& text, const std::string& font, float fontSize,
        const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT,
        TextVAlignment vAlignment = TextVAlignment::TOP);

    /** 使用初始字符串，字体文件，字号，尺寸，水平对齐方式和垂直对齐方式创建一个Label
     * @warning 不支持使用字体名称创建
     */
    static Label * createWithTTF(const std::string& text, const std::string& fontFile, float fontSize,
        const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT,
        TextVAlignment vAlignment = TextVAlignment::TOP);

    /** 使用TTFConfig创建Label
     * @warning 不支持使用字体名称创建
     */
    static Label* createWithTTF(const TTFConfig& ttfConfig, const std::string& text, TextHAlignment alignment = TextHAlignment::LEFT, int maxLineWidth = 0);
    
    /* 使用FNT文件，初始字符串，水平对齐方式，最大行数和图片偏移量创建Label*/
    static Label* createWithBMFont(const std::string& bmfontFilePath, const std::string& text,
        const TextHAlignment& alignment = TextHAlignment::LEFT, int maxLineWidth = 0, 
        const Vec2& imageOffset = Vec2::ZERO);
    
    static Label * createWithCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);
    static Label * createWithCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap);
    static Label * createWithCharMap(const std::string& plistFile);

    /** 设置Label的TTFConfig */
    virtual bool setTTFConfig(const TTFConfig& ttfConfig);
    virtual const TTFConfig& getTTFConfig() const { return _fontConfig;}

    virtual bool setBMFontFilePath(const std::string& bmfontFilePath, const Vec2& imageOffset = Vec2::ZERO);
    const std::string& getBMFontFilePath() const { return _bmFontPath;}

    virtual bool setCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);
    virtual bool setCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap);
    virtual bool setCharMap(const std::string& plistFile);

    /* 设置Label的系统字体（字体名称或字体文件）*/
    virtual void setSystemFontName(const std::string& systemFont);
    virtual const std::string& getSystemFontName() const { return _systemFont;}

    /* 设置Label的系统字体大小*/
    virtual void setSystemFontSize(float fontSize);
    virtual float getSystemFontSize() const { return _systemFontSize;}

    /** 改变字符串内容并重新渲染
     * @warning 如果你没有为Label设置TTF/BMFont/CharMap，会产生很大的开销
     */
    virtual void setString(const std::string& text) override;

    virtual const std::string& getString() const override {  return _originalUTF8String; }

    /**
     * 显示阴影
     *
     * @todo 支持模糊阴影效果
     */
    virtual void enableShadow(const Color4B& shadowColor = Color4B::BLACK,const Size &offset = Size(2,-2), int blurRadius = 0);

    /** 只支持TTF */
    virtual void enableOutline(const Color4B& outlineColor,int outlineSize = -1);

    /** 只支持TTF */
    virtual void enableGlow(const Color4B& glowColor);

    /** 取消阴影/描边/发光渲染效果 */
    virtual void disableEffect();

    void setAlignment(TextHAlignment hAlignment) { setAlignment(hAlignment,_vAlignment);}
    TextHAlignment getTextAlignment() const { return _hAlignment;}

    void setAlignment(TextHAlignment hAlignment,TextVAlignment vAlignment);

    void setHorizontalAlignment(TextHAlignment hAlignment) { setAlignment(hAlignment,_vAlignment); }
    TextHAlignment getHorizontalAlignment() const { return _hAlignment; }

    void setVerticalAlignment(TextVAlignment vAlignment) { setAlignment(_hAlignment,vAlignment); }
    TextVAlignment getVerticalAlignment() const { return _vAlignment; }

    void setLineBreakWithoutSpace(bool breakWithoutSpace);

    /** 设置Label的最大列数
     * 在不等于0的情况下，Label的最大列数用于强制断行
     * Label的宽度和最大列数不总是相等的
     */
    void setMaxLineWidth(unsigned int maxLineWidth);
    unsigned int getMaxLineWidth() { return _maxLineWidth;}

    /** 设置Label的原始宽度.
     * 在不等于0的情况下，Label的宽度被用于文字对齐
     * Label的最大列数也会被赋值为宽度的值
     */
    void setWidth(unsigned int width) { setDimensions(width,_labelHeight);}
    unsigned int getWidth() const { return _labelWidth; }  

    /** 设置Label的原始高度
     * 在不等于0的情况下，Label的高度被用于文字对齐
     * 如果Label的大小过小，文本内容会显示不完整
     */
    void setHeight(unsigned int height){ setDimensions(_labelWidth,height);}
    unsigned int getHeight() const { return _labelHeight;}   

    /** 一种更有效设置Label大小的方法 */
    void setDimensions(unsigned int width,unsigned int height);
    const Size& getDimensions() const{ return _labelDimensions;}

    /** 立即刷新内容 */
    virtual void updateContent();

    /** 设置文字颜色
     *
     */
    virtual void setTextColor(const Color4B &color);

    const Color4B& getTextColor() const { return _textColor;}

    virtual Sprite * getLetter(int lettetIndex);

    /** 剪裁上下边距以减少Label的高度
     */
    void setClipMarginEnabled(bool clipEnabled) { _clipEnabled = clipEnabled; }
    bool isClipMarginEnabled() const { return _clipEnabled; }
    // 字体相关
    int getCommonLineHeight() const;
    
    // 字符串相关
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

    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, bool parentTransformUpdated) override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;

    CC_DEPRECATED_ATTRIBUTE static Label* create(const std::string& text, const std::string& font, float fontSize,
        const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT,
        TextVAlignment vAlignment = TextVAlignment::TOP);

    CC_DEPRECATED_ATTRIBUTE virtual void setFontDefinition(const FontDefinition& textDefinition);
    CC_DEPRECATED_ATTRIBUTE const FontDefinition& getFontDefinition() const { return _fontDefinition; }

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

    bool recordLetterInfo(const cocos2d::Vec2& point,const FontLetterDefinition& letterDef, int spriteIndex);
    bool recordPlaceholderInfo(int spriteIndex);

    void setFontScale(float fontScale);
    
    virtual void alignText();
    
    bool computeHorizontalKernings(const std::u16string& stringToRender);

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

    bool _systemFontDirty;
    std::string _systemFont;
    float         _systemFontSize;
    LabelType _currentLabelType;

    std::vector<SpriteBatchNode*> _batchNodes;
    FontAtlas *                   _fontAtlas;
    std::vector<LetterInfo>       _lettersInfo;

    TTFConfig _fontConfig;

    // 兼容旧的LabelTTF
    Sprite* _textSprite;
    FontDefinition _fontDefinition;
    bool  _compatibleMode;

    //! 用于优化
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
    Color3B _shadowColor;
    float   _shadowOpacity;
    Sprite*   _shadowNode;

    int     _outlineSize;

    Color4B _textColor;
    Color4F _textColorF;

    bool _clipEnabled;
    bool _blendFuncDirty;
    bool _insideBounds;                     /// 记录前一帧精灵是否在边界内

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Label);

    friend class LabelTextFormatter;
};


NS_CC_END

#endif /*__COCOS2D_CCLABEL_H */
