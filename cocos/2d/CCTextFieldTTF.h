/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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

#ifndef __CC_TEXT_FIELD_H__
#define __CC_TEXT_FIELD_H__

#include "2d/CCLabel.h"
#include "base/CCIMEDelegate.h"

/**
 * @addtogroup ui
 * @{
 */
NS_CC_BEGIN

class TextFieldTTF;


/**@~english
 * A input protocol for TextField.
 * @~chinese 
 * 文本输入框的协议。
 */
class CC_DLL TextFieldDelegate
{
public:
    /**@~english
     * Desctructor for TextFieldDelegate.
     * @~chinese 
     * 析构函数
     * @js NA
     */
    virtual ~TextFieldDelegate() {}

    /**
     * @brief @~english The callback method of IME attached on the TextField.
     * @~chinese 文本编辑框挂载输入法时的回调函数。
     *
     * @param sender @~english The TextField object.
     * @~chinese 文本编辑框实例。
     * @return @~english If the sender doesn't want to attach to the IME, return true.
     * @~chinese 如果不希望编辑框挂载输入法，返回true。
     */
    virtual bool onTextFieldAttachWithIME(TextFieldTTF * sender)
    {
        CC_UNUSED_PARAM(sender);
        return false;
    }

    /**
     * @brief @~english The callback method of IME detached on the TextField.
     * @~chinese 文本编辑框取消挂载输入法时的回调函数。
     *
     * @param sender @~english The TextField object.
     * @~chinese 文本编辑框实例。
     * @return @~english If the sender doesn't want to attach to the IME, return true.
     * @~chinese 如果不希望编辑框取消挂载输入法，返回true。
     */
    virtual bool onTextFieldDetachWithIME(TextFieldTTF * sender)
    {
        CC_UNUSED_PARAM(sender);
        return false;
    }

    /**
     * @brief @~english The callback method of text inserted on the TextField.
     * @~chinese 文本编辑框插入文本时的回调函数。
     *
     * @param sender @~english The TextField object.
     * @~chinese 文本编辑框实例。
     * @param text @~english The text will be inserted.
     * @~chinese 将要插入的字符串。
     * @param nLen @~english The length of the inserted text.
     * @~chinese 将要插入的字符串长度。
     * @return @~english If the sender doesn't want to insert text, return true.
     * @~chinese 如果不希望编辑框插入文本，返回true。
     */
    virtual bool onTextFieldInsertText(TextFieldTTF * sender, const char * text, size_t nLen)
    {
        CC_UNUSED_PARAM(sender);
        CC_UNUSED_PARAM(text);
        CC_UNUSED_PARAM(nLen);
        return false;
    }

    /**
     * @brief @~english The callback method of text will be delete on the TextField.
     * @~chinese 文本编辑框删除文本时的回调函数。
     *
     * @param sender @~english The TextField object.
     * @~chinese 文本编辑框实例。
     * @param delText @~english The text will be deleted.
     * @~chinese 将要删除的字符串。
     * @param nLen @~english The length of the deleted text.
     * @~chinese 将要删除的字符串长度。
     * @return @~english If the sender doesn't want to delete text, return true.
     * @~chinese 如果不希望编辑框删除文本，返回true。
     */
    virtual bool onTextFieldDeleteBackward(TextFieldTTF * sender, const char * delText, size_t nLen)
    {
        CC_UNUSED_PARAM(sender);
        CC_UNUSED_PARAM(delText);
        CC_UNUSED_PARAM(nLen);
        return false;
    }

    /**
     * @brief @~english The callback method of the TextField will be drawn.
     * @~chinese 文本编辑框要被绘制时的回调函数。
     *
     * @param sender @~english The TextField object.
     * @~chinese 文本编辑框实例。
     * @param renderer @~english The renderer will render the TextField.
     * @~chinese 绘制文本编辑框的渲染器。
     * @param transform @~english The transform matrix used for renderer.
     * @~chinese 渲染器所使用的转置矩阵。
     * @param flags @~english The flags for the renderer.
     * @~chinese 渲染器所使用的标记位。
     * @return @~english If you don't want to render the TextField, return true.
     * @~chinese 如果不希望绘制文本编辑框，返回true。
     */
    virtual bool onVisit(TextFieldTTF * sender,Renderer *renderer, const Mat4 &transform, uint32_t flags)
    {
        CC_UNUSED_PARAM(sender);
        return false;
    }
};

/**
 *@brief @~english A simple text input field with TTF font.
 * @~chinese 一个使用 TTF 字体实现的简单的文本输入框。
 */
class CC_DLL TextFieldTTF : public Label, public IMEDelegate
{
public:
    /**@~english
     * Default constructor.
     * @~chinese 
     * 默认构造函数。
     * @js ctor
     */
    TextFieldTTF();
    
    /**@~english
     * Default destructor.
     * @~chinese 
     * 默认的析构函数。
     * @js NA
     * @lua NA
     */
    virtual ~TextFieldTTF();

    /** @~english Creates a TextFieldTTF from placeholder, a fontname, alignment, dimension and font size.
     * @~chinese 使用指定的占位符，大小，对齐方式，字体名称和字体大小创建一个 TextFieldTTF。
     * @param placeholder @~english The place holder string.
     * @~chinese 占位符字符串。
     * @param dimensions @~english The size of the TextField.
     * @~chinese 文本编辑框的大小。
     * @param alignment @~english The alignment of the TextField.
     * @~chinese 文本编辑框的对齐方式。
     * @param fontName @~english The font name of the TextField.
     * @~chinese 使用的字体名称。
     * @param fontSize @~english The font size of the TextField.
     * @~chinese 使用的字体大小。
     * @return @~english A TextFieldTTF object.
     * @~chinese 一个 TextFieldTTF 实例。
     * @js NA
     */
    static TextFieldTTF * textFieldWithPlaceHolder(const std::string& placeholder, const Size& dimensions, TextHAlignment alignment, const std::string& fontName, float fontSize);
    
    /** @~english Creates a TextFieldTTF from placeholder, a fontname and font size.
     * @~chinese 使用指定的占位符，字体名称和字体大小创建一个 TextFieldTTF。
     * @param placeholder @~english The place holder string.
     * @~chinese 占位符字符串。
     * @param fontName @~english The font name of the TextField.
     * @~chinese 使用的字体名称。
     * @param fontSize @~english The font size of the TextField.
     * @~chinese 使用的字体大小。
     * @return @~english A TextFieldTTF object.
     * @~chinese 一个 TextFieldTTF 实例。
     * @js NA
     */
    static TextFieldTTF * textFieldWithPlaceHolder(const std::string& placeholder, const std::string& fontName, float fontSize);
    
    /** @~english Initializes the TextFieldTTF with a font name, alignment, dimension and font size.
     * @~chinese 使用指定的占位符，大小，对齐方式，字体名称和字体大小初始化一个 TextFieldTTF。
     * @param placeholder @~english The place holder string.
     * @~chinese 占位符字符串。
     * @param dimensions @~english The size of the TextField.
     * @~chinese 文本编辑框的大小。
     * @param alignment @~english The alignment of the TextField.
     * @~chinese 文本编辑框的对齐方式。
     * @param fontName @~english The font name of the TextField.
     * @~chinese 使用的字体名称。
     * @param fontSize @~english The font size of the TextField.
     * @~chinese 使用的字体大小。
     * @return @~english If the initialization success, return true; else, return false.
     * @~chinese 如果初始化成功，返回 true；否则返回 false
     */
    bool initWithPlaceHolder(const std::string& placeholder, const Size& dimensions, TextHAlignment alignment, const std::string& fontName, float fontSize);
    
    /** @~english Creates a TextFieldTTF from placeholder, a fontname and font size.
     * @~chinese 使用指定的占位符，字体名称和字体大小初始化一个 TextFieldTTF。
     * @param placeholder @~english The place holder string.
     * @~chinese 占位符字符串。
     * @param fontName @~english The font name of the TextField.
     * @~chinese 使用的字体名称。
     * @param fontSize @~english The font size of the TextField.
     * @~chinese 使用的字体大小。
     * @return @~english If the initialization success, return true; else, return false.
     * @~chinese 如果初始化成功，返回 true；否则返回 false
     */
    bool initWithPlaceHolder(const std::string& placeholder, const std::string& fontName, float fontSize);

    /**
     *@brief @~english Open keyboard and receive input text.
     * @~chinese 打开键盘和接收输入文本。
     * @return @~english If the action success, return true; else return false.
     * @~chinese 如果成功，返回 true；否则返回 false。
     */
    virtual bool attachWithIME() override;

    /**
     *@brief    @~english End text input and close keyboard.
     * @~chinese 文本输入结束并关闭键盘。
     * @return @~english If the action success, return true; else return false.
     * @~chinese 如果成功，返回 true；否则返回 false。
     */
    virtual bool detachWithIME() override;

    //////////////////////////////////////////////////////////////////////////
    // properties
    //////////////////////////////////////////////////////////////////////////
    /**
     * @lua NA
     */
    inline TextFieldDelegate* getDelegate() const { return _delegate; };
    /**
     * @lua NA
     */
    inline void setDelegate(TextFieldDelegate* delegate) { _delegate = delegate; };

    /**@~english
     * Query the currently inputed charater count.
     * @~chinese 
     * 获取当前输入的字符数。
     *@return @~english The total input character count.
     * @~chinese 总输入字符数。
     */
    inline int getCharCount() const { return _charCount; };
    
    /**@~english
     * Query the color of place holder.
     * @~chinese 
     * 获取占位符的颜色。
     *@return @~english The place holder color.
     * @~chinese 占位符的颜色。
     */
    virtual const Color4B& getColorSpaceHolder();

    /**
     *@brief @~english Change input placeholder color.
     * @~chinese 设置占位符的颜色。
     *@param color @~english A color value in `Color3B`.
     * @~chinese Color3B 的颜色值。
     */
    virtual void setColorSpaceHolder(const Color3B& color);

    /**@~english
     * Change the placeholder color.
     * @~chinese 
     * 设置占位符的颜色。
     *@param color @~english The placeholder color in Color4B.
     * @~chinese Color4B 的颜色值。
     */
    virtual void setColorSpaceHolder(const Color4B& color);

    /**@~english
     * Change the color of input text.
     * @~chinese 
     * 设置输入文本的颜色。
     *@param textColor @~english The text color in Color4B.
     * @~chinese Color4B 的颜色值。
     */
    virtual void setTextColor(const Color4B& textColor) override;

    /**@~english
     * Change input text of TextField.
     * @~chinese 
     * 设置文本框中的文本。
     *@param text @~english The input text of TextField.
     * @~chinese 文本字符串。
     */
    virtual void setString(const std::string& text) override;

    /**@~english
     * Query the input text of TextField.
     * @~chinese 
     * 获取文本框中的文本。
     *@return @~english Get the input text of TextField.
     * @~chinese 文本框中的文本。
     */
    virtual const std::string& getString() const override;

    /**@~english
     * Change placeholder text.
     * place holder text displayed when there is no text in the text field.
     * @~chinese 
     * 设置占位符字符串。
     * 文本框中没有输入内容时，显示占位符字符串。
     *@param text  @~english The place holder string.
     * @~chinese 占位符字符串。
     */
    virtual void setPlaceHolder(const std::string& text);

    /**@~english
     * Query the placeholder string.
     * @~chinese 
     * 获取占位符字符串。
     *@return @~english The placeholder string.
     * @~chinese 占位符字符串。
     */
    virtual const std::string& getPlaceHolder() const;

    /**@~english
     * Set enable secure text entry represention.
     * If you want to display password in TextField, this option is very helpful.
     * @~chinese 
     * 启用/关闭 安全的文本输入。
     * 如果你想要在文本框中显示密码，可以开启此功能。
     *@param value @~english Whether or not to display text with secure text entry.
     * @~chinese 是否显示输入的文本。
     * @js NA
     */
    virtual void setSecureTextEntry(bool value);

    /**@~english
     * Query whether the currently display mode is secure text entry or not.
     * @~chinese 
     * 获取当前是否开启了安全的文本输入功能。
     *@return @~english Whether current text is displayed as secure text entry.
     * @~chinese 如果开启了安全的文本输入功能，返回 true；否则返回 false。
     * @js NA
     */
    virtual bool isSecureTextEntry();

    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;

protected:
    //////////////////////////////////////////////////////////////////////////
    // IMEDelegate interface
    //////////////////////////////////////////////////////////////////////////

    virtual bool canAttachWithIME() override;
    virtual bool canDetachWithIME() override;
    virtual void insertText(const char * text, size_t len) override;
    virtual void deleteBackward() override;
    virtual const std::string& getContentText() override;

    TextFieldDelegate * _delegate;
    int _charCount;

    std::string _inputText;

    std::string _placeHolder;
    Color4B _colorSpaceHolder;
    Color4B _colorText;

    bool _secureTextEntry;

private:
    class LengthStack;
    LengthStack * _lens;
};

NS_CC_END
// end of ui group
/// @}

#endif    // __CC_TEXT_FIELD_H__
