/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#ifndef __UIRICHTEXT_H__
#define __UIRICHTEXT_H__

#include "ui/UIWidget.h"
#include "ui/GUIExport.h"
#include "base/CCValue.h"

NS_CC_BEGIN
/**
 * @addtogroup ui
 * @{
 */

class Label;

namespace ui {
    
/** @class RichElement
*@brief @~english Rich text element base class.
 It defines the basic common properties for all rich text element.
 
 @~chinese 富文本元素基类。
 它定义了所有的富文本元素的通用属性。
*/
class CC_GUI_DLL RichElement : public Ref
{
public:
    /**
     *@brief Rich element type.
     */
    enum class Type
    {
        TEXT,   /*!< RichElementText */
        IMAGE,  /*!< RichElementImage */
        CUSTOM, /*!< RichElementCustomNode */
        NEWLINE /*!< RichElementNewLine */
    };
    
    /**
     * @~english Default constructor.
     * @~chinese 默认构造器
     * @js ctor
     * @lua new
     */
    RichElement(){};
    
    /**
     * @~english Default destructor.
     * @~chinese 默认析构器
     * @js NA
     * @lua NA
     */
    virtual ~RichElement(){};

    
    /**
     * @~english Initialize a rich element with different arguments.
     * @~chinese 通过不同的参数初始化一个富文本元素。
     * @param tag @~english A integer tag value. @~chinese 标签值。
     * @param color @~english A color in @see `Color3B`. @~chinese 颜色值。 
     * @param opacity @~english A opacity value in `GLubyte`. @~chinese 不透明度。
     * @return @~english True if initialize success, false otherwise. @~chinese True表明初始化成功，反之失败。
     */
    bool init(int tag, const Color3B& color, GLubyte opacity);
    
    bool equalType(Type type);
    void setColor(const Color3B& color);
protected:
    Type _type;             /*!< Rich element type. */
    int _tag;               /*!< A integer tag value. */
    Color3B _color;         /*!< A color in `Color3B`. */
    GLubyte _opacity;       /*!< A opacity value in `GLubyte`. */
    friend class RichText;
};
    
/** @class RichElementText
*@brief @~english Rich element for displaying text.

 @~chinese 用以显示文本的RichElementText。
*/
class CC_GUI_DLL RichElementText : public RichElement
{
public:
    
    /**
     * @~english Default constructor.
     * @~chinese 默认构造器
     * @js ctor
     * @lua new
     */
    RichElementText()
    {_type = Type::TEXT;};

    enum {
        ITALICS_FLAG = 1 << 0,          /*!< italic text */
        BOLD_FLAG = 1 << 1,             /*!< bold text */
        UNDERLINE_FLAG = 1 << 2,        /*!< underline */
        STRIKETHROUGH_FLAG = 1 << 3,    /*!< strikethrough */
        URL_FLAG = 1 << 4,              /*!< url of anchor */
        OUTLINE_FLAG = 1 << 5,          /*!< outline effect */
        SHADOW_FLAG = 1 << 6,           /*!< shadow effect */
        GLOW_FLAG = 1 << 7              /*!< glow effect */
    };
    
    /**
     * @~english Default destructor.
     * @~chinese 默认析构器
     * @js NA
     * @lua NA
     */
    virtual ~RichElementText(){};
    
    /**
     * @~english Initialize a RichElementText with various arguments.
     * @~chinese 通过多个变量初始化一个RichElementText类。
     * @param tag @~english A integer tag value. @~chinese 标签值。
     * @param color @~english A color in Color3B. @~chinese 颜色值。
     * @param opacity @~english A opacity in GLubyte. @~chinese 不透明度。
     * @param text @~english Content string. @~chinese 文本内容。
     * @param fontName @~english Content font name. @~chinese 文本字体名称。
     * @param fontSize @~english Content font size. @~chinese 文本字体大小。
     * @param flags @~english italics, bold, underline, strikethrough, url, outline, shadow or glow
     * @~chinese 斜体、加粗、下划线、删除线、网络地址、描边、阴影、发光
     * @param url @~english uniform resource locator @~chinese 全球资源定位器
     * @param outlineColor @~english the color of the outline @~chinese 描边颜色
     * @param outlineSize @~english the outline effect size value @~chinese 描边大小
     * @param shadowColor @~english the shadow effect color value @~chinese 阴影颜色
     * @param shadowOffset @~english shadow effect offset value @~chinese 阴影偏移
     * @param shadowBlurRadius @~english the shadow effect blur radius @~chinese 阴影模糊半径
     * @param glowColor @~english  glow color @~chinese 发光颜色
     * @return @~english True if initialize scucess, false otherwise. @~chinese True表明初始化成功，反之失败。
     */
    bool init(int tag, const Color3B& color, GLubyte opacity, const std::string& text,
              const std::string& fontName, float fontSize, uint32_t flags, const std::string& url,
              const Color3B& outlineColor = Color3B::WHITE, int outlineSize = -1,
              const Color3B& shadowColor = Color3B::BLACK, const cocos2d::Size& shadowOffset = Size(2.0, -2.0), int shadowBlurRadius = 0,
              const Color3B& glowColor = Color3B::WHITE);
    
    /**
     * @brief @~english Create a RichElementText with various arguments.
     * @~chinese 通过多个变量创建一个RichElementText类。
     * @param tag @~english A integer tag value. @~chinese 标签值。
     * @param color @~english A color in Color3B. @~chinese 颜色值。
     * @param opacity @~english A opacity in GLubyte. @~chinese 不透明度。
     * @param text @~english Content string. @~chinese 文本内容。
     * @param fontName @~english Content font name. @~chinese 文本字体名称。
     * @param fontSize @~english Content font size. @~chinese 文本字体大小。
     * @param flags @~english italics, bold, underline, strikethrough, url, outline, shadow or glow
     * @~chinese 斜体、加粗、下划线、删除线、网络地址、描边、阴影、发光
     * @param url @~english uniform resource locator @~chinese 全球资源定位器
     * @param outlineColor @~english the color of the outline @~chinese 描边颜色
     * @param outlineSize @~english the outline effect size value @~chinese 描边大小
     * @param shadowColor @~english the shadow effect color value @~chinese 阴影颜色
     * @param shadowOffset @~english shadow effect offset value @~chinese 阴影偏移
     * @param shadowBlurRadius @~english the shadow effect blur radius @~chinese 阴影模糊半径
     * @param glowColor @~english  glow color @~chinese 发光颜色
     * @return @~english RichElementText instance. @~chinese 富文本类实例。
     */
    static RichElementText* create(int tag, const Color3B& color, GLubyte opacity, const std::string& text,
                                   const std::string& fontName, float fontSize, uint32_t flags=0, const std::string& url="",
                                   const Color3B& outlineColor = Color3B::WHITE, int outlineSize = -1,
                                   const Color3B& shadowColor = Color3B::BLACK, const cocos2d::Size& shadowOffset = Size(2.0, -2.0), int shadowBlurRadius = 0,
                                   const Color3B& glowColor = Color3B::WHITE);
protected:
    std::string _text;
    std::string _fontName;
    float _fontSize;
    uint32_t _flags;
    std::string _url;
    Color3B _outlineColor;                  /*!< the color of the outline */
    int _outlineSize;                       /*!< the outline effect size value */
    Color3B _shadowColor;                   /*!< the shadow effect color value */
    cocos2d::Size _shadowOffset;            /*!< shadow effect offset value */
    int _shadowBlurRadius;                  /*!< the shadow effect blur radius */
    Color3B _glowColor;                     /*!< attributes of glow tag */
    friend class RichText;
};
    
/** @class RichElementImage
*@brief @~english Rich element for displaying images.

 @~chinese 用以显示图片的RichElementImage。
*/
class CC_GUI_DLL RichElementImage : public RichElement
{
public:
    
    /**
     * @~english Default constructor.
     * @~chinese 默认构造器
     * @js ctor
     * @lua new
     *
     */
    RichElementImage(){_type = Type::IMAGE;};

    
    /**
     * @~english Default destructor.
     * @~chinese 默认析构器
     * @js NA
     * @lua NA
     */
    virtual ~RichElementImage(){};

    
    /**
     * @~english Initialize a RichElementImage with various arguments.
     * @~chinese 通过多个变量初始化一个RichElementImage类。
     * @param tag @~english A integer tag value. @~chinese 标签值。
     * @param color @~english A color in Color3B. @~chinese 颜色值。
     * @param opacity @~english A opacity in GLubyte. @~chinese 不透明度。
     * @param filePath @~english A image file name. @~chinese 图片文件名。
     * @param url @~english uniform resource locator @~chinese 全球资源定位器
     * @return @~english True if initialize success, false otherwise. @~chinese True表明初始化成功，反之失败。
     */
    bool init(int tag, const Color3B& color, GLubyte opacity, const std::string& filePath, const std::string& url = "");

    
    /**
     * @~english Create a RichElementImage with various arguments.
     * @~chinese 通过多个变量创建一个RichElementImage类。
     * @param tag @~english A integer tag value. @~chinese 标签值。
     * @param color @~english A color in Color3B. @~chinese 颜色值。
     * @param opacity @~english A opacity in GLubyte. @~chinese 不透明度。
     * @param filePath @~english A image file name. @~chinese 图片文件名。
     * @param url @~english uniform resource locator @~chinese 全球资源定位器
     * @return @~english A RichElementImage instance. @~chinese 一个RichElementImage实例。
     */
    static RichElementImage* create(int tag, const Color3B& color, GLubyte opacity, const std::string& filePath, const std::string& url = "");

    void setWidth(int width);
    void setHeight(int height);
    void setUrl(const std::string& url);
protected:
    std::string _filePath;
    Rect _textureRect;
    int _textureType;
    friend class RichText;
    int _width;
    int _height;
    std::string _url;   /*!< attributes of anchor tag */
};
    
/** @class RichElementCustomNode
*@brief @~english Rich element for displaying custom node type.

 @~chinese 用以显示自定义节点类型的RichElementCustomNode。
*/
class CC_GUI_DLL RichElementCustomNode : public RichElement
{
public:
    
    /**
     * @~english Default constructor.
     * @~chinese 默认构造器
     * @js ctor
     * @lua new
     */
    RichElementCustomNode(){_type = Type::CUSTOM;};

    
    /**
     * @~english Default destructor.
     * @~chinese 默认析构器
     * @js NA
     * @lua NA
     */
    virtual ~RichElementCustomNode(){CC_SAFE_RELEASE(_customNode);};

    
    /**
     * @~english Initialize a RichElementCustomNode with various arguments.
     * @~chinese 通过多个变量初始化一个RichElementCustomNode类。
     * @param tag @~english A integer tag value. @~chinese 标签值。
     * @param color @~english A color in Color3B. @~chinese 颜色值。
     * @param opacity @~english A opacity in GLubyte. @~chinese 不透明度。
     * @param customNode @~english A custom node pointer. @~chinese 自定义节点指针。
     * @return @~english True if initialize success, false otherwise. @~chinese True表明初始化成功，反之失败。
     */
    bool init(int tag, const Color3B& color, GLubyte opacity, Node* customNode);
    
    /**
     * @~english Create a RichElementCustomNode with various arguments.
     * @~chinese 通过多个变量创建一个RichElementCustomNode类。
     * @param tag @~english A integer tag value. @~chinese 标签值。
     * @param color @~english A color in Color3B. @~chinese 颜色值。
     * @param opacity @~english A opacity in GLubyte. @~chinese 不透明度。
     * @param customNode @~english A custom node pointer. @~chinese 自定义节点指针。
     * @return @~english A RichElementCustomNode instance. @~chinese True表明初始化成功，反之失败。
     */
    static RichElementCustomNode* create(int tag, const Color3B& color, GLubyte opacity, Node* customNode);
protected:
    Node* _customNode;
    friend class RichText;
};

/**
 *@brief Rich element for new line.
 */
class CC_GUI_DLL RichElementNewLine : public RichElement
{
public:
    
    /**
     * @brief Default constructor.
     * @js ctor
     * @lua new
     *
     */
    RichElementNewLine(){_type = Type::NEWLINE;};
    
    /**
     * @brief Default destructor.
     * @js NA
     * @lua NA
     */
    virtual ~RichElementNewLine(){};
    
    /**
     * @brief Create a RichElementNewLine with various arguments.
     *
     * @param tag A integer tag value.
     * @param color A color in Color3B.
     * @param opacity A opacity in GLubyte.
     * @return A RichElementNewLine instance.
     */
    static RichElementNewLine* create(int tag, const Color3B& color, GLubyte opacity);
protected:
    friend class RichText;
};

/**
*@brief @~english A container for displaying various RichElements.
 We could use it to display texts with images easily.

 @~chinese 一个显示多个RichElement的容器类。
 我们可以使用它很容易显示带图片的文本。
*/
class CC_GUI_DLL RichText : public Widget
{
public:

    enum WrapMode {
        WRAP_PER_WORD,
        WRAP_PER_CHAR
    };
    
    /**
     * @brief @~english call to open a resource specified by a URL @~chinese 打开指定URL的函数
     * @param url @~english a URL  @~chinese 打开的URL
     */
    typedef std::function<void(const std::string& url)> OpenUrlHandler;
    
    /**
     * @brief @~english called on the specified tag @~chinese 标签的处理函数
     * @param tagAttrValueMap @~english the attributes of a tag @~chinese 某一标签的属性
     * @result @~english text attributes and RichElement @~chinese 返回文本属性和富文本元素
     */
    typedef std::function<std::pair<ValueMap, RichElement*>(const ValueMap& tagAttrValueMap)> VisitEnterHandler;
    
    static const std::string KEY_VERTICAL_SPACE;                    /*!< key of vertical space */
    static const std::string KEY_WRAP_MODE;                         /*!< key of per word, or per char */
    static const std::string KEY_FONT_COLOR_STRING;                 /*!< key of font color */
    static const std::string KEY_FONT_SIZE;                         /*!< key of font size */
    static const std::string KEY_FONT_SMALL;                        /*!< key of font size small */
    static const std::string KEY_FONT_BIG;                          /*!< key of font size big */
    static const std::string KEY_FONT_FACE;                         /*!< key of font name */
    static const std::string KEY_TEXT_BOLD;                         /*!< key of text bold */
    static const std::string KEY_TEXT_ITALIC;                       /*!< key of text italic */
    static const std::string KEY_TEXT_LINE;                         /*!< key of line style */
    static const std::string VALUE_TEXT_LINE_NONE;                  /*!< value of none */
    static const std::string VALUE_TEXT_LINE_DEL;                   /*!< value of strikethrough line */
    static const std::string VALUE_TEXT_LINE_UNDER;                 /*!< value of underline */
    static const std::string KEY_TEXT_STYLE;                        /*!< key of effect style */
    static const std::string VALUE_TEXT_STYLE_NONE;                 /*!< value of none */
    static const std::string VALUE_TEXT_STYLE_OUTLINE;              /*!< value of outline */
    static const std::string VALUE_TEXT_STYLE_SHADOW;               /*!< value of shadow */
    static const std::string VALUE_TEXT_STYLE_GLOW;                 /*!< value of glow */
    static const std::string KEY_TEXT_OUTLINE_COLOR;                /*!< key of outline color */
    static const std::string KEY_TEXT_OUTLINE_SIZE;                 /*!< key of outline size */
    static const std::string KEY_TEXT_SHADOW_COLOR;                 /*!< key of shadow color */
    static const std::string KEY_TEXT_SHADOW_OFFSET_WIDTH;          /*!< key of shadow offset (width) */
    static const std::string KEY_TEXT_SHADOW_OFFSET_HEIGHT;         /*!< key of shadow offset (height) */
    static const std::string KEY_TEXT_SHADOW_BLUR_RADIUS;           /*!< key of shadow blur radius */
    static const std::string KEY_TEXT_GLOW_COLOR;                   /*!< key of glow color */
    static const std::string KEY_URL;                               /*!< key of url */
    static const std::string KEY_ANCHOR_FONT_COLOR_STRING;          /*!< key of font color of anchor tag */
    static const std::string KEY_ANCHOR_TEXT_BOLD;                  /*!< key of text bold of anchor tag */
    static const std::string KEY_ANCHOR_TEXT_ITALIC;                /*!< key of text italic of anchor tag */
    static const std::string KEY_ANCHOR_TEXT_LINE;                  /*!< key of line style of anchor tag */
    static const std::string KEY_ANCHOR_TEXT_STYLE;                 /*!< key of effect style of anchor tag */
    static const std::string KEY_ANCHOR_TEXT_OUTLINE_COLOR;         /*!< key of outline color of anchor tag */
    static const std::string KEY_ANCHOR_TEXT_OUTLINE_SIZE;          /*!< key of outline size of anchor tag */
    static const std::string KEY_ANCHOR_TEXT_SHADOW_COLOR;          /*!< key of shadow color of anchor tag */
    static const std::string KEY_ANCHOR_TEXT_SHADOW_OFFSET_WIDTH;   /*!< key of shadow offset (width) of anchor tag */
    static const std::string KEY_ANCHOR_TEXT_SHADOW_OFFSET_HEIGHT;  /*!< key of shadow offset (height) of anchor tag */
    static const std::string KEY_ANCHOR_TEXT_SHADOW_BLUR_RADIUS;    /*!< key of shadow blur radius of anchor tag */
    static const std::string KEY_ANCHOR_TEXT_GLOW_COLOR;            /*!< key of glow color of anchor tag */
    
    /**
     * @~english Default constructor.
     * @~chinese 默认构造器
     * @js ctor
     * @lua new
     */
    RichText();
    
    /**
     * @~english Default destructor.
     * @~chinese 默认析构器
     * @js NA
     * @lua NA
     */
    virtual ~RichText();
    
    /**
     * @~english Create a empty RichText.
     * @~chinese 创建一个空的RichText。
     * @return @~english RichText instance. @~chinese RichText实例。
     */
    static RichText* create();

    /**
     * @brief Create a RichText from an XML
     *
     * @return RichText instance.
     */
    static RichText* createWithXML(const std::string& xml, const ValueMap& defaults = ValueMap(), const OpenUrlHandler& handleOpenUrl = nullptr);

    /**
     * @~english Insert a RichElement at a given index.
     * @~chinese 在指定位置插入一个RichElement。
     * @param element @~english A RichElement type. @~chinese 一个RichElement类。
     * @param index @~english A given index. @~chinese 索引值。
     */
    void insertElement(RichElement* element, int index);
    
    /**
     * @~english Add a RichElement at the end of RichText.
     * @~chinese 在容器最后插入一个RichElement。
     * @param element @~english A RichElement instance. @~chinese 一个RichElement类。
     */
    void pushBackElement(RichElement* element);
    
    /**
     * @~english Remove a RichElement at a given index.
     * @~chinese 移除指定位置的RichElement。
     * @param index @~english A integer index value. @~chinese 索引值。
     */
    void removeElement(int index);
    
    /**
     * @~english Remove specific RichElement.
     * @~chinese 移除一个RichElement。
     * @param element @~english A RichElement type. @~chinese 一个RichElement类指针。
     */
    void removeElement(RichElement* element);
    
    /**
     * @~english Set vertical space between each RichElement.
     * @~chinese 设置每个RichElement的垂直间隔。
     * @param space @~english Point in float. @~chinese 垂直间隔值。
     */
    void setVerticalSpace(float space);
    
    /**
     * @~english Rearrange all RichElement in the RichText.
     * It's usually called internally.
     * @~chinese 重新排列所有的RichElement。
     * 常内部调用。
     */
    void formatText();

    //override functions.
    virtual void ignoreContentAdaptWithSize(bool ignore) override;
    virtual std::string getDescription() const override;

    void setWrapMode(WrapMode wrapMode);                /*!< sets the wrapping mode: WRAP_PER_CHAR or WRAP_PER_WORD */
    WrapMode getWrapMode() const;                       /*!< returns the current wrapping mode */
    void setFontColor(const std::string& color);        /*!< Set the font color. @param color the #RRGGBB hexadecimal notation. */
    std::string getFontColor();                         /*!< return the current font color */
    Color3B getFontColor3B();                           /*!< return the current font color */
    void setFontSize(float size);                       /*!< Set the font size. @param size the font size. */
    float getFontSize();                                /*!< return the current font size */
    void setFontFace(const std::string& face);          /*!< Set the font face. @param face the font face. */
    std::string getFontFace();                          /*!< return the current font face */
    void setAnchorFontColor(const std::string& color);  /*!< Set the font color of a-tag. @param face the font color. */
    std::string getAnchorFontColor();                   /*!< return the current font color of a-tag */
    cocos2d::Color3B getAnchorFontColor3B();            /*!< return the current font color of a-tag */
    void setAnchorTextBold(bool enable);                /*!< enable bold text of a-tag */
    bool isAnchorTextBoldEnabled();                     /*!< valid style is bold text of a-tag? */
    void setAnchorTextItalic(bool enable);              /*!< enable italic text of a-tag */
    bool isAnchorTextItalicEnabled();                   /*!< valid style is italic text of a-tag? */
    void setAnchorTextDel(bool enable);                 /*!< enable the strikethrough of a-tag */
    bool isAnchorTextDelEnabled();                      /*!< valid strikethrough of a-tag? */
    void setAnchorTextUnderline(bool enable);           /*!< enable the underline of a-tag */
    bool isAnchorTextUnderlineEnabled();                /*!< valid underline of a-tag? */
    /** @breif enable the outline of a-tag */
    void setAnchorTextOutline(bool enable, const Color3B& outlineColor = Color3B::WHITE, int outlineSize = -1);
    bool isAnchorTextOutlineEnabled();                  /*!< valid outline of a-tag? */
    Color3B getAnchorTextOutlineColor3B();              /*!< return the current text outline color of a-tag */
    int getAnchorTextOutlineSize();                     /*!< return the current text outline size of a-tag */
    /** @breif enable the shadow of a-tag */
    void setAnchorTextShadow(bool enable, const Color3B& shadowColor = Color3B::BLACK, const Size& offset = Size(2.0, -2.0), int blurRadius = 0);
    bool isAnchorTextShadowEnabled();                   /*!< valid shadow of a-tag? */
    Color3B getAnchorTextShadowColor3B();               /*!< return the current text shadow color of a-tag */
    Size getAnchorTextShadowOffset();                   /*!< return the current text shadow offset of a-tag */
    int getAnchorTextShadowBlurRadius();                /*!< return the current text shadow blur radius of a-tag */
    void setAnchorTextGlow(bool enable, const Color3B& glowColor = Color3B::WHITE); /*!< enable the glow of a-tag */
    bool isAnchorTextGlowEnabled();                     /*!< valid glow of a-tag? */
    Color3B getAnchorTextGlowColor3B();                 /*!< return the current text glow color of a-tag */
    void setDefaults(const ValueMap& defaults);         /*!< set the default values */
    ValueMap getDefaults() const;                       /*!< returns the default values */

    cocos2d::Color3B color3BWithString(const std::string& color);   /*!< convert a color string into a Color3B. */
    std::string stringWithColor3B(const cocos2d::Color3B& color3b); /*!< convert a Color3B into a color string. */
    std::string stringWithColor4B(const cocos2d::Color4B& color4b); /*!< convert a Color4B into a color string. */

    /**
     * @brief add a callback to own tag.
     * @param tag tag's name
     * @param isFontElement use attributes of text tag
     * @param handleVisitEnter callback
     */
    static void setTagDescription(const std::string& tag, bool isFontElement, VisitEnterHandler handleVisitEnter);

    /**
     * @brief remove a callback to own tag.
     * @param tag tag's name
     */
    static void removeTagDescription(const std::string& tag);
    
    void openUrl(const std::string& url);

    /**
     * @brief Asks the callback to open a resource specified by a URL.
     * @discussion If you set up your own URL in the anchor tag, it is used to intercept the URL open.
     * @param handleOpenUrl the callback
     */
    void setOpenUrlHandler(const OpenUrlHandler& handleOpenUrl);

CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;

    bool initWithXML(const std::string& xml, const ValueMap& defaults = ValueMap(), const OpenUrlHandler& handleOpenUrl = nullptr);

protected:
    virtual void adaptRenderers() override;

    virtual void initRenderer() override;
    void pushToContainer(Node* renderer);
    void handleTextRenderer(const std::string& text, const std::string& fontName, float fontSize, const Color3B& color,
                            GLubyte opacity, uint32_t flags, const std::string& url="",
                            const Color3B& outlineColor = Color3B::WHITE, int outlineSize = -1,
                            const Color3B& shadowColor = Color3B::BLACK, const cocos2d::Size& shadowOffset = Size(2.0, -2.0), int shadowBlurRadius = 0,
                            const Color3B& glowColor = Color3B::WHITE);
    void handleImageRenderer(const std::string& fileParh, const Color3B& color, GLubyte opacity, int width, int height, const std::string& url);
    void handleCustomRenderer(Node* renderer);
    void formarRenderers();
    void addNewLine();
    int findSplitPositionForWord(cocos2d::Label* label, const std::string& text);
    int findSplitPositionForChar(cocos2d::Label* label, const std::string& text);

    bool _formatTextDirty;
    Vector<RichElement*> _richElements;
    std::vector<Vector<Node*>*> _elementRenders;
    float _leftSpaceWidth;

    ValueMap _defaults;             /*!< default values */
    OpenUrlHandler _handleOpenUrl;  /*!< the callback for open URL */
};
    
}

// end of ui group
/// @}
NS_CC_END

#endif /* defined(__UIRichText__) */
