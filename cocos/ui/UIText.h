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

NS_CC_BEGIN

namespace ui {

/**
 *  为创建系统字体（font）或TTF字体（font）提供支持
 *@js 
 *@lua NA
 */
class Text : public Widget
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    enum class Type
    {
        SYSTEM,
        TTF
    };
    /**
     * 默认构造函数
     */
    Text();

    /**
     * 默认析构函数
     */
    virtual ~Text();

    /**
     * 创建和初始化对象
	 * 译者注：Allocate此处是为对象分配空间
     */
    static Text* create();
    
    /**
	 *  创建一个指定文本内容（textContent），字体名称（fontName）和字体大小（fontSize）的文本对象
	 *  字体名称（fontName）可以是系统字体名称或TTF文件路径。
	 *  用法：  Text *text = Text::create("Hello", "Arial", 20);  //创建一个系统字体的UIText
	 *          Text *text = Text::create("Hello", "xxx\xxx.ttf", 20); //创建一个TTF字体的UIText
     */
    static Text* create(const std::string& textContent,
                        const std::string& fontName,
                        int fontSize);

    /**
     * 变更标签（label）的字符串值
     *
     * @param text  字符串值
     */
    CC_DEPRECATED_ATTRIBUTE void setText(const std::string& text){this->setString(text);}
    void setString(const std::string& text);

    /**
     * 获得标签（label）的字符串值
     *
     * @return 字符串文本值
     */
    CC_DEPRECATED_ATTRIBUTE const std::string& getStringValue(){ return this->getString();}
    const std::string& getString()const;

    /**
     * 获得标签（label）的字符串长度
	 * 注：获得的长度会比原始字符串的长度长，
	 * 如果你想得到原始字符串的长度， 你应用调用this->getString().size()来获得
     *
     * @return  字符串长度
     */
    ssize_t getStringLength()const;

    /**
     * 设置标签（label）的字体（font）大小
     *
     * @param  font 大小
     */
    void setFontSize(int size);

    int getFontSize();

    /**
     * 设置标签（label）的字体（font）名称
	 * 如果你要用系统字体，你应该传一个字体名称的参数
	 * 如果你要用TTF字体，你应该传一个TTF字体的文件路径
	 * 用法：  Text *text = Text::create("Hello", "Arial", 20);  //创建一个系统字体的UIText
	 *         text->setFontName("Marfelt");  // 不管之前的字体类型是TTF字体还是系统字体，它都会把字体改为系统字体
	 *         text->setFontName("xxxx/xxx.ttf"); //不管之前的字体类型是TTF字体还是系统字体，它都会把字体改为TTF字体
     * @param  font 字体名称
     */
    void setFontName(const std::string& name);

    const std::string& getFontName();
    
    Type getType() const;

    /**
     * 设置标签（label）是否可点击
     *
     * @param  touch 标签（label）是否可点击
     */
    void setTouchScaleChangeEnabled(bool enabled);

    /**
     * 获得标签（label）是否可点击
     *
     * @return  touch 获得标签（label）是否可点击
     */
    bool isTouchScaleChangeEnabled();

    //override "getVirtualRendererSize" method of widget.
    virtual const Size& getVirtualRendererSize() const override;

    //override "getVirtualRenderer" method of widget.
    virtual Node* getVirtualRenderer() override;

    /**
     * 返回控件（widget）的类名（class name）
     */
    virtual std::string getDescription() const override;

    void setTextAreaSize(const Size &size);

    const Size& getTextAreaSize();

    void setTextHorizontalAlignment(TextHAlignment alignment);

    TextHAlignment getTextHorizontalAlignment();

    void setTextVerticalAlignment(TextVAlignment alignment);

    TextVAlignment getTextVerticalAlignment();
    
CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    virtual bool init(const std::string& textContent,
                      const std::string& fontName,
                      int fontSize);

protected:
    virtual void initRenderer() override;
    virtual void onPressStateChangedToNormal() override;
    virtual void onPressStateChangedToPressed() override;
    virtual void onPressStateChangedToDisabled() override;
    virtual void onSizeChanged() override;
    virtual void updateTextureColor() override;
    virtual void updateTextureOpacity() override;
    virtual void updateTextureRGBA() override;
    virtual void updateFlippedX() override;
    virtual void updateFlippedY() override;
    void labelScaleChangedWithSize();
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void adaptRenderers() override;
protected:
    bool _touchScaleChangeEnabled;
    float _normalScaleValueX;
    float _normalScaleValueY;
    std::string _fontName;
    int _fontSize;
    float _onSelectedScaleOffset;
    Label* _labelRenderer;
    bool _labelRendererAdaptDirty;
    Type _type;
};

}

NS_CC_END

#endif /* defined(__CocoGUI__Label__) */
