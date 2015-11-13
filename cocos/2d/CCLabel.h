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

#include "2d/CCNode.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCQuadCommand.h"
#include "2d/CCFontAtlas.h"
#include "base/ccTypes.h"

NS_CC_BEGIN

/**
 * @addtogroup _2d
 * @{
 */


/**
 * @struct TTFConfig
 * @see `GlyphCollection`
 */
typedef struct _ttfConfig
{
    std::string fontFilePath;
    float fontSize;

    GlyphCollection glyphs;
    const char *customGlyphs;

    bool distanceFieldEnabled;
    int outlineSize;

    _ttfConfig(const char* filePath = "",float size = 12, const GlyphCollection& glyphCollection = GlyphCollection::DYNAMIC,
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

class Sprite;
class SpriteBatchNode;
class DrawNode;
class EventListenerCustom;

/**
 * @brief @~english Label is a subclass of Node that knows how to render text labels.
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
 * @~chinese Label(文本)是Node的子类,它知道如何渲染文本。
 * 
 * 文本可以通过以下方法来创建:
 * - 一个TTF字体文件。
 * - 一个位图字体文件。
 * - 一个字符映射文件。
 * -  内置的系统字体。
 * 
 * 支持位图字体的编辑器:
 * - http://glyphdesigner.71squared.com/ (商业的, Mac OS X)
 * - http://www.n4te.com/hiero/hiero.jnlp (免费的, Java)
 * - http://slick.cokeandcode.com/demos/hiero.jnlp (免费的, Java)
 * - http://www.angelcode.com/products/bmfont/ (免费的, Windows only)
 * @js NA
 */
class CC_DLL Label : public Node, public LabelProtocol, public BlendProtocol
{
public:
    /// @name Creators
    /// @{

    /**@~english
     * Allocates and initializes a Label, with default settings.
     *
     * @~chinese 
     * 使用默认设置分配和初始化一个文本。
     * 
     * @return @~english An automatically released Label object.
     * @~chinese 一个自动释放的文本对象。
     */
    static Label* create();

    /**@~english
     * Allocates and initializes a Label, base on platform-dependent API.
     *
     * @~chinese 
     * 基于平台相关的API创建和初始化一个文本
     * 
     * @param text @~english The initial text.
     * @~chinese 最始文本内容。
     * @param font @~english A font file or a font family name.
     * @~chinese 一个字体文件或字体名称。
     * @param fontSize @~english The font size. This value must be > 0.
     * @~chinese 字体大小。这个值必须大于0。
     * @param dimensions @~english dimensions of the label node
     * @~chinese 文本的内容大小。
     * @param hAlignment @~english The text horizontal alignment.
     * @~chinese 水平对齐方式。
     * @param vAlignment @~english The text vertical alignment.
     *
     * @~chinese 垂直对齐方式。
     * 
     * @warning @~english It will generate texture by the platform-dependent code.
     *
     * @~chinese 它将通过平台相关的代码来生成纹理。
     * 
     * @return @~english An automatically released Label object.
     * @~chinese 一个自动释放的文本对象。
     */
    static Label* createWithSystemFont(const std::string& text, const std::string& font, float fontSize,
        const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT,
        TextVAlignment vAlignment = TextVAlignment::TOP);

    /**@~english
     * Allocates and initializes a Label, based on FreeType2.
     *
     * @~chinese 
     * 使用FreeType2库创建和初始化一个文本。
     * 
     * @param text @~english The initial text.
     * @~chinese 最初文本内容。
     * @param fontFilePath @~english A font file.
     * @~chinese 一个TTF字体文件。
     * @param fontSize @~english The font size. This value must be > 0.
     * @~chinese 字体大小。这个值必须大于0。
     * @param dimensions @~english dimensions of the label node
     * @~chinese 文本的内容大小
     * @param hAlignment @~english The text horizontal alignment.
     * @~chinese 水平对齐方式。
     * @param vAlignment @~english The text vertical alignment.
     *
     * @~chinese 垂直对齐方式。
     * 
     * @return @~english An automatically released Label object.
     * @~chinese 一个自动释放的文本对象。
     */
    static Label * createWithTTF(const std::string& text, const std::string& fontFilePath, float fontSize,
        const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT,
        TextVAlignment vAlignment = TextVAlignment::TOP);

    /**@~english
     * Allocates and initializes a Label, base on FreeType2.
     *
     * @~chinese 
     * 使用FreeType2库创建和初始化一个文本
     * 
     * @param ttfConfig @~english A pointer to a TTFConfig object.
     * @~chinese 一个TTFConfig对象实例。
     * @param text @~english The initial text.
     * @~chinese 最初文本内容。
     * @param hAlignment @~english The text horizontal alignment.
     * @~chinese 水平对齐方式
     * @param maxLineWidth @~english The max line width.
     *
     * @~chinese 最大线宽
     * 
     * @return @~english An automatically released Label object.
     * @~chinese 一个自动释放的文本对象。
     * @see TTFConfig setTTFConfig setMaxLineWidth
     */
    static Label* createWithTTF(const TTFConfig& ttfConfig, const std::string& text, 
        TextHAlignment hAlignment = TextHAlignment::LEFT, int maxLineWidth = 0);

    /**@~english
     * Allocates and initializes a Label, with a bitmap font file.
     *
     * @~chinese 
     * 使用位图字体文件创建和初始化一个文本。
     * 
     * @param bmfontPath @~english A bitmap font file, it's a FNT format.
     * @~chinese 一个位图字体文件,它是FNT格式。
     * @param text @~english The initial text.
     * @~chinese 初始文本内容。
     * @param hAlignment @~english Text horizontal alignment.
     * @~chinese 水平对齐方式。
     * @param maxLineWidth @~english The max line width.
     * @~chinese 最大线宽
     * @param imageOffset The first character offset in BMfont
     *@~english
     * @~chinese 第一个字符的在位图文件中的偏移
     * 
     * @return @~english An automatically released Label object.
     * @~chinese 一个标签自动释放对象。
     * @see setBMFontFilePath setMaxLineWidth
     */
    static Label* createWithBMFont(const std::string& bmfontPath, const std::string& text,
        const TextHAlignment& hAlignment = TextHAlignment::LEFT, int maxLineWidth = 0,
        const Vec2& imageOffset = Vec2::ZERO);

    /**@~english
     * Allocates and initializes a Label, with char map configuration.
     *
     * @~chinese 
     * 使用字符映射文件来创建和初始化一个文本
     * 
     * @param charMapFile @~english A char map file, it's a PNG format.
     * @~chinese 一个字符映射文件,它是一个PNG格式的文件。
     * @param itemWidth @~english The width in points of each element.
     * @~chinese 每个元素的宽度,单位是“点”。
     * @param itemHeight @~english The height in points of each element.
     * @~chinese 每个元素的高度,单位“点”。
     * @param startCharMap @~english The starting char of the char map.
     *
     * @~chinese 字符映射文件的起始字符
     * 
     * @return @~english An automatically released Label object.
     * @~chinese 一个自动释放的文本对象。
     */
    static Label * createWithCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);

    /**@~english
     * Allocates and initializes a Label, with char map configuration.
     *
     * @~chinese 
     * 使用字符映射文件创建和初始化一个文本
     * 
     * @param texture @~english A pointer to an existing Texture2D object.
     * @~chinese 一个已有的纹理对象指针。
     * @param itemWidth @~english The width in points of each element.
     * @~chinese 每个元素的宽度,单位是“点”。
     * @param itemHeight @~english The height in points of each element.
     * @~chinese 每个元素的高度，单位是“点”。
     * @param startCharMap @~english The starting char of the char map.
     *
     * @~chinese 字符映射文件的起始字符
     * 
     * @return @~english An automatically released Label object.
     * @~chinese 一个自动释放的文本对象
     */
    static Label * createWithCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap);

    /**@~english
     * Allocates and initializes a Label, with char map configuration.
     *
     * @~chinese 
     * 使用字符映射文件来创建和初始化一个文本
     * 
     * @param plistFile @~english A configuration file of char map.
     *
     * @~chinese 一个字符映射的配置文件。
     * 
     * @return @~english An automatically released Label object.
     * @~chinese 一个自动释放的文本对象
     */
    static Label * createWithCharMap(const std::string& plistFile);

    //  end of creators group
    /// @}

    /// @{
    /// @name Font methods

    /**@~english
     * Sets a new TTF configuration to Label.
     * @~chinese
     * 设置一个新的TTFConfig
     * @see `TTFConfig`
     */
    virtual bool setTTFConfig(const TTFConfig& ttfConfig);

    /**@~english
     * Returns the TTF configuration object used by the Label.
     * @~chinese 
     * 返回文本对象的TTF配置对象
     * @see `TTFConfig`
     */
    virtual const TTFConfig& getTTFConfig() const { return _fontConfig;}

    /** @~english Sets a new bitmap font to Label  @~chinese 给文本设置一个新的位图字体*/
    virtual bool setBMFontFilePath(const std::string& bmfontFilePath, const Vec2& imageOffset = Vec2::ZERO);

    /** @~english Returns the bitmap font used by the Label. @~chinese 返回当前文本使用的位图字体.*/
    const std::string& getBMFontFilePath() const { return _bmFontPath;}

    /**@~english
     * Sets a new char map configuration to Label.
     *
     * @~chinese 
     * 给文本设置一个新的字符映射文件。
     * 
     * @see `createWithCharMap(const std::string&,int,int,int)`
     */
    virtual bool setCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);

    /**@~english
     * Sets a new char map configuration to Label.
     *
     * @~chinese 
     * 给文本设置一个新的字符映射文件
     * 
     * @see `createWithCharMap(Texture2D*,int,int,int)`
     */
    virtual bool setCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap);

    /**@~english
     * Sets a new char map configuration to Label.
     *
     * @~chinese 
     * 给文本设置一个新的字符映射文件
     * 
     * @see `createWithCharMap(const std::string&)`
     */
    virtual bool setCharMap(const std::string& plistFile);

    /**@~english
     * Sets a new system font to Label.
     *
     * @~chinese 
     * 给文本设置一个新的系统字体
     * 
     * @param font @~english A font file or a font family name.
     * @~chinese 一个字体文件或字体名称
     */
    virtual void setSystemFontName(const std::string& font);

    /** @~english Returns the system font used by the Label. @~chinese 返回文本使用的系统字体。*/
    virtual const std::string& getSystemFontName() const { return _systemFont;}

    /* @~english Sets the system font size of Label. @~chinese 设置文本使用的系统字体大小。*/
    virtual void setSystemFontSize(float fontSize);

    /** @~english Returns the bitmap font path used by the Label. @~chinese 返回文本使用的位图字体路径。*/
    virtual float getSystemFontSize() const { return _systemFontSize;}

    /**
     * @warning @~english This method is not recommended for game developers.
     * @~chinese 这个方法不推荐游戏开发者调用,它是给编辑器用的。
     */
    virtual void requestSystemFontRefresh() { _systemFontDirty = true;}

    //  end of font methods
    /// @}

    /** @~english Sets the text that this Label is to display. @~chinese 设置文本显示的字符串。*/
    virtual void setString(const std::string& text) override;

    /** @~english Return the text the Label is displaying. @~chinese 返回文本显示的字符串。*/
    virtual const std::string& getString() const override {  return _utf8Text; }

    /**
     * @~english Get the string's display line number.
     * @~chinese 获取文本显示的行数。
     *
     * @return @~english Label line number. @~chinese 文本行数。
     */
    int getStringNumLines();

    /**
     * @~english Get the string length.
     * @~chinese 获取字符串的长度
     *
     * @return @~english Label string length. @~chinese 文本的字符串长度
     */
    int getStringLength();

    /**@~english
     * Sets the text color of Label.
     *
     * The text color is different from the color of Node.
     *
     * @~chinese 
     * 设置文本的字符串的颜色。
     * 
     * 文本的颜色不同于节点的颜色。
     * 
     * @warning @~english Limiting usage when the Label created with true type font or system font.
     * @~chinese 只有使用TTF字体或者系统字体创建的文本对象才可以调用这个方法。
     */
    virtual void setTextColor(const Color4B &color);

    /** @~english Returns the text color of the Label. @~chinese 返回文本的字符串的颜色。*/
    const Color4B& getTextColor() const { return _textColor;}

    /**@~english
     * Enable shadow effect to Label.
     *
     * @~chinese 
     * 激活文本的阴影效果
     * 
     */
    virtual void enableShadow(const Color4B& shadowColor = Color4B::BLACK,const Size &offset = Size(2,-2), int blurRadius = 0);

    /**@~english
     * Enable outline effect to Label.
     * @~chinese 
     * 激活文本的描边效果。
     * @warning @~english Limiting use to only when the Label created with true type font or system font.
     * @~chinese 只有使用TTF字体或者系统字体创建的文本对象才可以调用这个方法。
     */
    virtual void enableOutline(const Color4B& outlineColor,int outlineSize = -1);

    /**@~english
    * Enable glow effect to Label.
     * @~chinese 
     * 激活文本的发光效果
    * @warning @~english Limiting use to only when the Label created with true type font.
     * @~chinese 只有使用TTF字体创建的文本对象才可以调用这个方法。
    */
    virtual void enableGlow(const Color4B& glowColor);

    /**@~english
     * Disable all effect to Label.
     * @~chinese 
     * 禁用所有文本特效。
     * @warning @~english Please use disableEffect(LabelEffect::ALL) instead of this API.
     * @~chinese 请使用disableEffect(LabelEffect:ALL)而不是这个API。
     */
    virtual void disableEffect();

    /**@~english
     * Disable effect to Label.
     *
     * @~chinese 
     * 禁用文本特效。
     * 
     * @see `LabelEffect`
     */
    virtual void disableEffect(LabelEffect effect);

    /** @~english Sets the Label's text horizontal alignment. @~chinese 设置文本的水平对齐。*/
    void setAlignment(TextHAlignment hAlignment) { setAlignment(hAlignment,_vAlignment);}

    /** @~english Returns the Label's text horizontal alignment. @~chinese 获取文本的对齐方式。*/
    TextHAlignment getTextAlignment() const { return _hAlignment;}

    /** @~english Sets the Label's text alignment. @~chinese 设置文本的水平和垂直对齐方式。*/
    void setAlignment(TextHAlignment hAlignment,TextVAlignment vAlignment);

    /** @~english Sets the Label's text horizontal alignment. @~chinese 设置文本的水平对齐。*/
    void setHorizontalAlignment(TextHAlignment hAlignment) { setAlignment(hAlignment,_vAlignment); }

    /** @~english Returns the Label's text horizontal alignment. @~chinese 返回文本的水平对齐。*/
    TextHAlignment getHorizontalAlignment() const { return _hAlignment; }

    /** @~english Sets the Label's text vertical alignment. @~chinese 设置文本垂直对齐。*/
    void setVerticalAlignment(TextVAlignment vAlignment) { setAlignment(_hAlignment,vAlignment); }

    /** @~english Returns the Label's text vertical alignment. @~chinese 返回文本垂直对齐。*/
    TextVAlignment getVerticalAlignment() const { return _vAlignment; }

    /**@~english
     * Specify what happens when a line is too long for Label.
     *
     * @~chinese 
     * 指定当文本太长时，是否需要换行。
     * 
     * @param breakWithoutSpace @~english Lines are automatically broken between words if this value is false.
     * @~chinese 如果参数传false，那么当文本过长时会自动换行。
     */
    void setLineBreakWithoutSpace(bool breakWithoutSpace);

    /**@~english
     * Makes the Label at most this line untransformed width.
     * The Label's max line width be used for force line breaks if the value not equal zero.
     * @~chinese 
     * 设置文本的最大行宽。
     * 如果文本的行宽不等于零的话，那么它可以用来强制换行
     */
    void setMaxLineWidth(float maxLineWidth);
    /**
     *@~english Return the maximize line width.
     *@~chinese 获取文本的最大行宽
     * @return @~english The maximize line width. @~chinese 文本的最大行宽
     */
    float getMaxLineWidth() { return _maxLineWidth; }

    /**@~english
     * Makes the Label exactly this untransformed width.
     *
     * The Label's width be used for text align if the value not equal zero.
     * @~chinese 
     * 设置文本的行宽
     * 
     * 如果行宽不为0，则它可以用来对齐文本。
     */
    void setWidth(float width) { setDimensions(width,_labelHeight);}
    /**
     * @~english Get the label width.
     * @~chinese 返回文本的行宽
     *
     * @return @~english The line width. @~chinese 行宽
     */
    float getWidth() const { return _labelWidth; }

    /**@~english
     * Makes the Label exactly this untransformed height.
     *
     * The Label's height be used for text align if the value not equal zero.
     * The text will display of incomplete when the size of Label not enough to support display all text.
     * @~chinese 
     * 设置文本的行高
     * 
     * 如果行高不为0，则它可以用来对齐文本
     * 如果文本内容大于文本的大小，那么可能会显示不完整
     */
    void setHeight(float height){ setDimensions(_labelWidth, height); }
    /**
     *@~english Get the label height.
     *@~chinese 返回文本的行高
     *
     * @return @~english The line height. @~chinese 行高
     */
    float getHeight() const { return _labelHeight; }

    /** @~english Sets the untransformed size of the Label in a more efficient way.
     * @~chinese 更高效地设置文本大小的方法。这个大小是未进行坐标变换的大小。
     */
    void setDimensions(float width, float height);
    /**
     * @~english Get the dimension of label.
     * @~chinese 获取文本的大小
     *
     * @return @~english the dimension in Size. @~chinese 文本大小
     */
    const Size& getDimensions() const{ return _labelDimensions;}

    /** @~english Update content immediately. @~chinese 立即更新文本内容。*/
    virtual void updateContent();

    /**@~english
     * Provides a way to treats each character like a Sprite.
     * @~chinese 
     * 提供了一种方法,可以把每个字符当作精灵来看待。
     * @warning @~english No support system font.
     * @~chinese 不支持系统字体。
     */
    virtual Sprite * getLetter(int lettetIndex);

    /** @~english Makes the Label to clip upper and lower margin for reduce height of Label.
     *@~chinese 设置是否裁剪文本上下边距，主要用来减少文本的调试。
     */
    void setClipMarginEnabled(bool clipEnabled) { _clipEnabled = clipEnabled; }

    /**
     *@~english Determines whether clipping upper and lower margin of label.
     *@~chinese 判断文本是否裁剪上下边距
     *
     * @return @~english Retuen true if enable clipping margin, otherwise return false.
     * @~chinese 如果激活裁剪文本上下边框，则返回真，否则返回假。
     */
    bool isClipMarginEnabled() const { return _clipEnabled; }

    /** @~english Sets the line height of the Label.
     * @~chinese 设置文本的行高。
     * @warning @~english Not support system font.
     * @~chinese 不支持系统字体。
     * @since v3.2.0
     */
    void setLineHeight(float height);

    /**@~english
     * Returns the line height of this Label.
     * @~chinese 
     * 返回这个文本的行高。
     * @warning @~english Not support system font.
     * @~chinese 不支持系统字体
     * @since v3.2.0
     */
    float getLineHeight() const;

    /**@~english
     * Sets the additional kerning of the Label.
     *
     * @~chinese 
     * 设置文本的字符间距。
     * 
     * @warning @~english Not support system font.
     * @~chinese 不支持系统字体。
     * @since v3.2.0
     */
    void setAdditionalKerning(float space);

    /**@~english
     * Returns the additional kerning of the Label.
     *
     * @~chinese 
     * 返回文本的字符间距
     * 
     * @warning @~english Not support system font.
     * @~chinese 不支持系统字体。
     * @since v3.2.0
     */
    float getAdditionalKerning() const;

    /**
     * @~english Get the font atlas
     * @~chinese 返回一个FontAtlas对象指针
     *
     * @return @~english A FontAtlas pointer @~chinese FontAtlas指针
     */
    FontAtlas* getFontAtlas() { return _fontAtlas; }

    virtual const BlendFunc& getBlendFunc() const override { return _blendFunc; }
    virtual void setBlendFunc(const BlendFunc &blendFunc) override;

    virtual bool isOpacityModifyRGB() const override { return _isOpacityModifyRGB; }
    virtual void setOpacityModifyRGB(bool isOpacityModifyRGB) override;
    virtual void updateDisplayedColor(const Color3B& parentColor) override;
    virtual void updateDisplayedOpacity(GLubyte parentOpacity) override;

    virtual std::string getDescription() const override;

    virtual const Size& getContentSize() const override;
    virtual Rect getBoundingBox() const override;

    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

    virtual void setCameraMask(unsigned short mask, bool applyChildren = true) override;

    virtual void removeAllChildrenWithCleanup(bool cleanup) override;
    virtual void removeChild(Node* child, bool cleanup = true) override;
    virtual void setGlobalZOrder(float globalZOrder) override;

    CC_DEPRECATED_ATTRIBUTE static Label* create(const std::string& text, const std::string& font, float fontSize,
        const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT,
        TextVAlignment vAlignment = TextVAlignment::TOP);
    CC_DEPRECATED_ATTRIBUTE virtual void setFontDefinition(const FontDefinition& textDefinition);
    CC_DEPRECATED_ATTRIBUTE FontDefinition getFontDefinition() const { return _getFontDefinition(); }
    CC_DEPRECATED_ATTRIBUTE int getCommonLineHeight() const { return (int)getLineHeight();}

CC_CONSTRUCTOR_ACCESS:
    /**@~english
     * Constructor of Label.
     * @~chinese 
     * 构造函数的标签。
     * @js NA
     */
    Label(TextHAlignment hAlignment = TextHAlignment::LEFT,
      TextVAlignment vAlignment = TextVAlignment::TOP);

    /**@~english
     * Destructor of Label.
     * @~chinese 
     * 析构函数的标签。
     * @js NA
     * @lua NA
     */
    virtual ~Label();

protected:
    struct LetterInfo
    {
        char16_t utf16Char;
        bool valid;
        float positionX;
        float positionY;
        int atlasIndex;
        int lineIndex;
    };

    enum class LabelType {
        TTF,
        BMFONT,
        CHARMAP,
        STRING_TEXTURE
    };

    virtual void setFontAtlas(FontAtlas* atlas, bool distanceFieldEnabled = false, bool useA8Shader = false);

    void computeStringNumLines();

    void onDraw(const Mat4& transform, bool transformUpdated);
    void onDrawShadow(GLProgram* glProgram);
    void drawSelf(bool visibleByCamera, Renderer* renderer, uint32_t flags);

    bool multilineTextWrapByChar();
    bool multilineTextWrapByWord();

    void updateLabelLetters();
    virtual void alignText();
    void computeAlignmentOffset();
    bool computeHorizontalKernings(const std::u16string& stringToRender);

    void recordLetterInfo(const cocos2d::Vec2& point, char16_t utf16Char, int letterIndex, int lineIndex);
    void recordPlaceholderInfo(int letterIndex, char16_t utf16Char);
    
    void updateQuads();

    void createSpriteForSystemFont(const FontDefinition& fontDef);
    void createShadowSpriteForSystemFont(const FontDefinition& fontDef);

    virtual void updateShaderProgram();

    void reset();

    FontDefinition _getFontDefinition() const;

    virtual void updateColor() override;

    LabelType _currentLabelType;
    bool _contentDirty;
    std::u16string _utf16Text;
    std::string _utf8Text;
    int _numberOfLines;

    std::string _bmFontPath;
    TTFConfig _fontConfig;
    float _outlineSize;

    bool _systemFontDirty;
    std::string _systemFont;
    float _systemFontSize;
    Sprite* _textSprite;
    Sprite* _shadowNode;

    FontAtlas* _fontAtlas;
    Vector<SpriteBatchNode*> _batchNodes;
    std::vector<LetterInfo> _lettersInfo;

    //! used for optimization
    Sprite *_reusedLetter;
    Rect _reusedRect;
    int _lengthOfString;

    //layout relevant properties.
    float _lineHeight;
    float _lineSpacing;
    float _additionalKerning;
    int* _horizontalKernings;
    bool _lineBreakWithoutSpaces;
    float _maxLineWidth;
    Size _labelDimensions;
    float _labelWidth;
    float _labelHeight;
    TextHAlignment _hAlignment;
    TextVAlignment _vAlignment;

    float _textDesiredHeight;
    std::vector<float> _linesWidth;
    std::vector<float> _linesOffsetX;
    float _letterOffsetY;
    float _tailoredTopY;
    float _tailoredBottomY;

    LabelEffect _currLabelEffect;
    Color4F _effectColorF;
    Color4B _textColor;
    Color4F _textColorF;

    QuadCommand _quadCommand;
    CustomCommand _customCommand;
    Mat4  _shadowTransform;
    GLuint _uniformEffectColor;
    GLuint _uniformTextColor;
    bool _useDistanceField;
    bool _useA8Shader;

    bool _shadowDirty;
    bool _shadowEnabled;
    Size _shadowOffset;
    
    Color4F _shadowColor4F;
    Color3B _shadowColor3B;
    GLubyte _shadowOpacity;
    float _shadowBlurRadius;

    bool _clipEnabled;
    bool _blendFuncDirty;
    BlendFunc _blendFunc;

    /// whether or not the label was inside bounds the previous frame
    bool _insideBounds;

    bool _isOpacityModifyRGB;

    std::unordered_map<int, Sprite*> _letters;

    EventListenerCustom* _purgeTextureListener;
    EventListenerCustom* _resetTextureListener;

#if CC_LABEL_DEBUG_DRAW
    DrawNode* _debugDrawNode;
#endif
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Label);
};

// end group
/// @}

NS_CC_END

#endif /*__COCOS2D_CCLABEL_H */
