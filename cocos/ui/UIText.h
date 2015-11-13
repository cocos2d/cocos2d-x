/****************************************************************************
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

#ifndef __UILABEL_H__
#define __UILABEL_H__

#include "ui/UIWidget.h"
#include "ui/GUIExport.h"
#include "base/ccTypes.h"

/**
 * @addtogroup ui
 * @{
 */

NS_CC_BEGIN

class Label;

namespace ui {

/**
 * @class Text
 * @brief @~english For creating a system font or a TTF font Text.
 * @~chinses 用于显示系统字体或ttf字体的文本控件
 */
class CC_GUI_DLL Text : public Widget
{

    DECLARE_CLASS_GUI_INFO

public:
    /** 
     * @~english Type Text type.
     * @~chinses 字体类型
     */
    enum class Type
    {
        SYSTEM,
        TTF
    };
    /**
     * @~english Default constructor.
     * @~chinese 默认构造函数
     * @js ctor
     * @lua new
     */
    Text();

    /**
     * @~english Default destructor.
     * @~chinese 默认析构函数
     * @js NA
     * @lua NA
     */
    virtual ~Text();

    /**
     * @~english Create a Text object.
     * @~chinese 创建一个文本对象
     * @return An autoreleased Text object.
     * @~chinese 被创建的文本对象
     */
    static Text* create();

    /**
     *  @~english Create a Text object with textContent, fontName and fontSize.
     *  The fontName could be a system font name or a TTF file path.
     *  Usage:
     *  @code
     *       //create a system font UIText.
     *       Text *text = Text::create("Hello", "Arial", 20);
     *       //create a TTF font UIText.
     *       Text *text = Text::create("Hello", "xxx\xxx.ttf", 20);
     *  @endcode
     * @~chinese 通过指定文本内容，字体名称，字体大小来创建一个文本对象，字体名称必须是系统所带的字体名称，或一个指定的ttf文件路径
     * 用例：
     *  @code
     *       //create a system font UIText.
     *       Text *text = Text::create("Hello", "Arial", 20);
     *       //create a TTF font UIText.
     *       Text *text = Text::create("Hello", "xxx\xxx.ttf", 20);
     *  @endcode
     * @param textContent @~english Text content string.
     * @~chinese 文本内容的字符串
     * @param fontName @~english A given font name.
     * @~chinese 指定字体名
     * @param fontSize @~english A given font size.
     * @~chinese 字体大小
     * @return @~english An autoreleased Text object.
     * @~chinese 文本对象
     */
    static Text* create(const std::string& textContent,
                        const std::string& fontName,
                        float fontSize);

    /**
     * @~english Changes the string value of label.
     * @~chinese 设置文本对象所显示的文本
     * @param text  @~english The string value.
     * @~chinese 指定字符串
     */
    CC_DEPRECATED_ATTRIBUTE void setText(const std::string& text)
    {
        this->setString(text);
    }
    /**
    * @~english Changes the string value of label.
    * @~chinese 设置文本对象所显示的文本
    * @param text  @~english String value.
    * @~chinese 指定字符串
    */
    void setString(const std::string& text);

    /**
     * @~english Gets the string value of label.
     * @~chinese 获取文本对象中的文本字符串
     * @return @~english String value.
     * @~chinese 字符串
     */
    CC_DEPRECATED_ATTRIBUTE const std::string& getStringValue()
    {
        return this->getString();
    }

    /**
    * @~english Gets the string value of label.
    * @~chinese 获取文本对象中的文本字符串
    * @return @~english String value.
    * @~chinese 字符串
    */
    const std::string& getString()const;

    /**
     * @~english Gets the string length of the label.
     * @~chinese 获取文本标签的字符串长度
     * @return  @~english String length.
     * @~chinese 字符串长度
     * @note @~english This length will be larger than the raw string length,
     * if you want to get the raw string length,
     * you should call this->getString().size() instead.
     * @~chinese 该长度将会比原始字符串长度要大，如果你想获得原始字符串长度，请调用this->getString().size()
     */
    ssize_t getStringLength()const;

    /**
     * @~english Sets the font size of label.
     * @~chinese 设置文本对象的字体大小
     * @param size @~english The font size.
     * @~chinese 字体大小
     */
    void setFontSize(float size);

    /**
     * @~english Gets the font size of label.
     * @~chinese 获取文本对象的字体大小
     * @return @~english The font size.
     * @~chinese 字体大小
     */
    float getFontSize()const;

    /**
     * @~english Sets the font name of label.
     *  If you are trying to use a system font, you could just pass a font name
     * If you are trying to use a TTF, you should pass a file path to the TTF file
     * Usage:
     * @code
     *          //create a system font UIText
     *         Text *text = Text::create("Hello", "Arial", 20);
     *         // it will change the font to system font no matter the previous font type is TTF or system font
     *         text->setFontName("Marfelt");
     *         //it will change the font to TTF font no matter the previous font type is TTF or system font
     *         text->setFontName("xxxx/xxx.ttf");
     * @endcode
     * @~chinese 设置文本对象的字体，如果你需要使用系统字体，只需将字体名作为参数传递即可，如果你使用TTF文件，你需要传递TTF文件的路径
     * 用例：
     * Usage:
     * @code
     *          //create a system font UIText
     *         Text *text = Text::create("Hello", "Arial", 20);
     *         // it will change the font to system font no matter the previous font type is TTF or system font
     *         text->setFontName("Marfelt");
     *         //it will change the font to TTF font no matter the previous font type is TTF or system font
     *         text->setFontName("xxxx/xxx.ttf");
     * @endcode
     * @param name @~english The font name.
     * @~chinese 字体名称
     */
    void setFontName(const std::string& name);

    /** 
     * @~english Gets the font name.
     * @~chinese 获取字体名称
     * @return @~english Font name.
     * @~chinese 字体名称
     */
    const std::string& getFontName()const;

    /**
     * @~english Gets the font type.
     * @~chinese 获取字体类型
     * @return @~english The font type.
     * @~chinese 字体类型
     */
    Type getType() const;

    /**
     * @~english Sets the touch scale enabled of label.
     * @~chinese 设置文本对象是否支持触摸放大
     * @param enabled @~english Touch scale enabled of label.
     * @~chinese 是否支持触摸放大
     */
    void setTouchScaleChangeEnabled(bool enabled);

    /**
     * @~english Gets the touch scale enabled of label.
     * @~chinese 获取当前文本对象是否支持触摸放大
     *
     * @return  @~english Touch scale enabled of label.
     * @~chinese 是否支持触摸放大
     */
    bool isTouchScaleChangeEnabled()const;

    //override "getVirtualRendererSize" method of widget.
    virtual Size getVirtualRendererSize() const override;

    //override "getVirtualRenderer" method of widget.
    virtual Node* getVirtualRenderer() override;

    /** 
     * @~english Gets the render size in auto mode.
     * @~chinses 获取在自动模式下的渲染尺寸
     * @return @~english The size of render size in auto mode.
     * @~chinses 自动模式的渲染尺寸
     */
    virtual Size getAutoRenderSize();

    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const override;

    /**
     * @~english Sets the rendering size of the text, you should call this method
     * along with calling `ignoreContentAdaptWithSize(false)`, otherwise the text area
     * size is calculated by the real size of the text content.
     * @~chinese 设置文本的实际渲染尺寸（文本域），你必须同时调用`ignoreContentAdaptWithSize(false)`，否则渲染尺寸（文本域）将会
     * 按照文本内容的实际大小计算
     * @param size @~english The text rendering area size.
     * @~chinese 文本渲染尺寸（文本域）
     */
    void setTextAreaSize(const Size &size);

    /** 
     * @~chinese Return the text rendering area size.
     * @~chinese 返回文本对象的实际渲染尺寸（文本域）
     * @return @~chinese The text rendering area size.
     * @~chinese 文本域大小
     */
    const Size& getTextAreaSize()const;

    /** 
     * @~chinese Sets text horizontal alignment.
     * @~chinese 设置文本水平方向对齐类型
     * @param alignment @~chinese Horizontal text alignment type
     * @~chinese 水平方向对齐类型
     */
    void setTextHorizontalAlignment(TextHAlignment alignment);

    /** 
     * @~chinese Gets text horizontal alignment.
     * @~chinese 获取文本对象水平方向对齐类型
     * @return Horizontal @~chinese text alignment type
     * @~chinese 水平方向对齐类型
     */
    TextHAlignment getTextHorizontalAlignment()const;

    /** 
     * @~chinese Sets text vertical alignment.
     * @~chinese 设置文本对象竖直方向对齐类型
     * @param alignment @~chinese The vertical text alignment type
     * @~chinese 竖直方向对齐类型
     */
    void setTextVerticalAlignment(TextVAlignment alignment);

    /** 
     * @~chinese Gets text vertical alignment.
     * @~chinese 获取文本竖直方向对齐类型
     * @return @~chinese The vertical text alignment type
     * @~chinese 文本竖直方向对其类型
     */
    TextVAlignment getTextVerticalAlignment()const;

    /** 
     * @~chinese Sets text color.
     * @~chinese 设置文本颜色
     * @param color @~chinese Text color.
     * @~chinese 文本颜色
     */
    void setTextColor(const Color4B color);

    /** 
     * @~chinese Gets text color.
     * @~chinese 获取文本颜色
     * @return @~chinese Text color.
     * @~chinese 文本颜色
     */
    const Color4B& getTextColor() const;

    /**
     * @~chinese Enable shadow for the label.
     * @~chinese 开启文本阴影
     * @todo support blur for shadow effect
     *
     * @param shadowColor @~chinese The color of shadow effect.
     * @~chinese 阴影颜色
     * @param offset @~chinese The offset of shadow effect.
     * @~chinese 阴影偏移量
     * @param blurRadius @~chinese The blur radius of shadow effect.
     * @~chinese 阴影模糊半径
     */
    void enableShadow(const Color4B& shadowColor = Color4B::BLACK,
                      const Size &offset = Size(2,-2),
                      int blurRadius = 0);

    /**
     * @~chinese Enable outline for the label.
     * It only works on IOS and Android when you use System fonts.
     * @~chinese 设置文本轮廓，只在安卓或者IOS平台下使用系统字体时有效
     * @param outlineColor @~chinese The color of outline.
     * @~chinese 轮廓颜色
     * @param outlineSize @~chinese The size of outline.
     * @~chinese 轮廓尺寸
     */
    void enableOutline(const Color4B& outlineColor,int outlineSize = 1);

    /**
     * @~chinese Enable the glow effect of the text,Only support for TTF.
     * @~chinese 设置文本的辉光效果，仅支持TTF字体
     * 
     * @param glowColor @~chinese The color of glow.
     * @~chinese 辉光颜色
     */
    void enableGlow(const Color4B& glowColor);

    /** 
     * @~chinese Disable all text effects, including shadow, outline and glow.
     * @~chinese 禁用所有文本特效，包括阴影，轮廓以及辉光
     */
    void disableEffect();

    /**
     * @~chinese Disable specific text effect.
     * @~chinese 禁用指定的文本特效
     * @param effect @~chinese The specified text effect.
     * @~chinese 指定的文本特效
     * @see `LabelEffect`
     */
    void disableEffect(LabelEffect effect);

CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    virtual bool init(const std::string& textContent,
                      const std::string& fontName,
                      float fontSize);

protected:
    virtual void initRenderer() override;
    virtual void onPressStateChangedToNormal() override;
    virtual void onPressStateChangedToPressed() override;
    virtual void onPressStateChangedToDisabled() override;
    virtual void onSizeChanged() override;

    void labelScaleChangedWithSize();
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void adaptRenderers() override;
protected:
    bool _touchScaleChangeEnabled;
    float _normalScaleValueX;
    float _normalScaleValueY;
    std::string _fontName;
    float _fontSize;
    float _onSelectedScaleOffset;
    Label* _labelRenderer;
    bool _labelRendererAdaptDirty;
    Type _type;
};

}

NS_CC_END

// end of ui group
/// @}

#endif /* defined(__CocoGUI__Label__) */
