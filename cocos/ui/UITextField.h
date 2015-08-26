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

#ifndef __UITEXTFIELD_H__
#define __UITEXTFIELD_H__

#include "ui/UIWidget.h"
#include "2d/CCTextFieldTTF.h"
#include "ui/GUIExport.h"

NS_CC_BEGIN
/**
 * @addtogroup ui
 * @{
 */

namespace ui {

/** @class UICCTextField
*@brief @~english A helper class which inherit from @see `TextFieldTTF` and implements the @see `TextFieldDelegate` protocol.
 It is mainly be used internally by @see `UITextField` class.

 @~chinese 从TextFieldTTF派生而来，并且实现了TextFieldDelegate定义的协议的帮助类。
 它主要是在UITextField类中使用。
 @js NA
 @lua NA
*/
class CC_GUI_DLL UICCTextField: public TextFieldTTF, public TextFieldDelegate
{
public:
    /**
    * @~english Default constructor.
    * @~chinese 默认构造器
    */
    UICCTextField();

    /**
    * @~english Default destructor.
    * @~chinese 默认析构器
    */
    ~UICCTextField();
    
    virtual void onEnter() override;
    
    /**
    * @~english Create a UICCTextField intance with a placeholder, a fontName and a fontSize.
    * @~chinese 通过一个占位符，字体名称和字体大小来创建一个UICCTextField。
    * @param placeholder @~english Placeholder in string. @~chinese 占位符。
    * @param fontName @~english Font name in string. @~chinese 字体名称。
    * @param fontSize @~english Font size in float. @~chinese 字体大小。
    * @return @~english A UICCTextField instance. @~chinese 一个UICCTextField实例。
    */
    static UICCTextField* create(const std::string& placeholder,
                                 const std::string& fontName,
                                 float fontSize);
    
    //override functions
    virtual bool onTextFieldAttachWithIME(TextFieldTTF *pSender) override;
    virtual bool onTextFieldDetachWithIME(TextFieldTTF * pSender) override;
    virtual bool onTextFieldInsertText(TextFieldTTF * pSender,
                                       const char * text,
                                       size_t nLen) override;
    virtual bool onTextFieldDeleteBackward(TextFieldTTF * pSender,
                                           const char * delText,
                                           size_t nLen) override;
    void insertText(const char* text, size_t len) override;
    void deleteBackward() override;
    
    /**
    * @~english Open up the IME.
    * @~chinese 打开输入法编辑器
    */
    void openIME();

    /**
    * @~english Close the IME.
    * @~chinese 关闭输入法编辑器
    */
    void closeIME();
    
    /**
    * @~english Toggle enable max length limitation.
    * @~chinese 开关最大长度限制
    * @param enable @~english True to enable max length, false otherwise. @~chinese True表示启用最大长度限制，反之关闭。
    */
    void setMaxLengthEnabled(bool enable);

    /**
    * @~english Query max length enable state.
    * @~chinese 请求最大长度限制的开关状态。
    * @return @~english Whether max length is enabled or not. @~chinese 最大长度限制是否启用。
    */
    bool isMaxLengthEnabled()const;

    /**
    * @~english Set maxmize length.
    * @~chinese 设置最大长度。
    * @param length  @~english The maxmize length in integer. @~chinese 整型单位的最大长度值。
    */
    void setMaxLength(int length);

    /**
    * @~english Get maximize length.
    * @~chinese 获得最大长度。
    * @return @~english Maximize length. @~chinese 最大长度。
    */
    int getMaxLength()const;

    /**
    * @~english Return the total inputed charaters.
    * @~chinese 获取总共输入的字符数。
    *@return @~english Total inputed character count. @~chinese 总共输入的字符数。
    */
    int getCharCount()const;
    
    
    /**
    * @~english Toggle password input mode.
    * @~chinese 开关密码输入模式。
    * @param enable @~english True if enable password input, false otherwise. @~chinese True表示开启密码输入模式，反之关闭。
    */
    void setPasswordEnabled(bool enable);
    
    /**
    * @~english Query whether password input mode is enabled or not.
    * @~chinese 请求密码输入模式是否开启。
    * @return @~english True if password input is enabled, false otherwise. @~chinese True表示开启密码输入模式，反之关闭。
    */
    bool isPasswordEnabled()const;
    
    /**
    * @~english Change password style text.
    * @~chinese 改变密码模式下的文本样式。
    * @param styleText @~english The styleText for password mask, the default value is "*". @~chinese 密码掩码的文本样式，默认为“*”。
    */
    void setPasswordStyleText(const std::string& styleText);
    
    /**
    * @~english Set the password text content.
    * @~chinese 设置密码。
    * @param text @~english The content of password. @~chinese 密码。
    */
    void setPasswordText(const std::string& text);

    
    /**
    * @~english Toggle attach with IME.
    * @~chinese 是否关联输入法编辑器。
    * @param attach @~english True if attach with IME, false otherwise. @~chinese True表明关联输入法编辑器，反之不关联。
    */
    void setAttachWithIME(bool attach);
    
    /**
    * @~english Query whether the IME is attached or not.
    * @~chinese 请求是否关联输入法编辑器。
    * @return @~english True if IME is attached, false otherwise. @~chinese True表明关联输入法编辑器，反之不关联。
    */
    bool getAttachWithIME()const;
    
    /**
    * @~english  Toggle detach with IME.
    * @~chinese 是否取消关联输入法编辑器。
    * @param detach @~english True if detach with IME, false otherwise. @~chinese True表明不关联输入法编辑器，反之关联。
    */
    void setDetachWithIME(bool detach);
    
    /**
    * @~english Query whether IME is detached or not.
    * @~chinese 请求是否不关联输入法编辑器。
    * @return True @~english if IME is detached, false otherwise. @~chinese True表明不关联输入法编辑器，反之关联。
    */
    bool getDetachWithIME()const;
    
    /**
    * @~english Toggle enable text insert.
    * @~chinese 开关是否允许文本输入。
    * @param insert @~english True if enable insert text, false otherwise. @~chinese True表示允许文本输入，反之不允许。
    */
    void setInsertText(bool insert);
    
    /**
    * @~english Query whether insert text is enabled or not.
    * @~chinese 请求是否允许文本输入。
    * @return @~english True if insert text is enabled, false otherwise. @~chinese True表示允许文本输入，反之不允许。
    */
    bool getInsertText()const;
     
    /**
    * @~english Toggle enable delete backward.
    * @~chinese 开关允许回删。
    * @param deleteBackward @~english True if enable delete backward, false otherwise. @~chinese True表示开启回删，反之关闭。
    */
    void setDeleteBackward(bool deleteBackward);
    
    /**
    * @~english Query whether delete backward is enabled   or not.
    * @~chinese 请求是否开启回删。
    * @return @~english True if delete backward is enabled, false otherwise. @~chinese True表示开启回删，反之关闭。
    */
    bool getDeleteBackward()const;
protected:
    bool _maxLengthEnabled;
    int _maxLength;
    bool _passwordEnabled;
    std::string _passwordStyleText;
    bool _attachWithIME;
    bool _detachWithIME;
    bool _insertText;
    bool _deleteBackward;
};

/**
* TextField event type.
 * @deprecated Use @see `TextField::EventType` instead.
 */
typedef enum
{
    TEXTFIELD_EVENT_ATTACH_WITH_IME,
    TEXTFIELD_EVENT_DETACH_WITH_IME,
    TEXTFIELD_EVENT_INSERT_TEXT,
    TEXTFIELD_EVENT_DELETE_BACKWARD,
}TextFiledEventType;

/**
 * A callback which would be called when a TextField event happens.
 * @deprecated Use @see `ccTextFieldCallback` instead.
 */
typedef void (Ref::*SEL_TextFieldEvent)(Ref*, TextFiledEventType);
#define textfieldeventselector(_SELECTOR) (SEL_TextFieldEvent)(&_SELECTOR)

/** @class TextField
 @brief @~english A widget which allows users to input text.
 The rendering of the input text are based on @see `TextFieldTTF'.
 If you want to use system control behavior, please use @see `EditBox` instead.

 @~chinese 一个接受用户输入的widget。
 输入文本的渲染基于TextFieldTTF。
 如果你想用系统控制行为，请使用EditBox来替代。
 @js NA
 @lua NA
*/
class CC_GUI_DLL TextField : public Widget
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
    * TextField event type.
    */
    enum class EventType
    {
        ATTACH_WITH_IME,
        DETACH_WITH_IME,
        INSERT_TEXT,
        DELETE_BACKWARD,
    };
    /**
    * @~english A callback which would be called when a TextField event happens.
    * @~chinese 当TextField的一个事件发生时进行的回调。
    */
    typedef std::function<void(Ref*, EventType)> ccTextFieldCallback;
    
    
    /**
    * @~english Default constructor.
    * @~chinese 默认构造器。
    *
    */
    TextField();
    
    /**
    * @~english Default destructor.
    * @~chinese 默认析构器。
    */
    virtual ~TextField();
    
    /**
    * @~english Create an empty TextField.
    * @~chinese 创建一个空的TextField。
    * @return @~english A TextField instance. @~chinese  TextField实例。
    */
    static TextField* create();
    
    /**
    * @~english Create a TextField with a placeholder, a font name and a font size.
    * @~chinese 通过一个占位符，一个字体名称和字体大小来创建一个TextField。
    * @param placeholder @~english The placeholder string. @~chinese 占位符。
    * @param fontName @~english The font name. @~chinese 字体名称。
    * @param fontSize @~english The font size. @~chinese 字体大小。
    * @return @~english A TextField instance. @~chinese TextField实例。
    */
    static TextField* create(const std::string& placeholder,
                             const std::string& fontName,
                             int fontSize);
    
    /**
    * @~english Set the touch size
    * The touch size is used for @see `hitTest`.
    * @~chinese 设置触摸区域大小。
    * 触摸大小用于hitTest。
    * @param size @~english A delimitation zone. @~chinese 一个限定区域。
    */
    void setTouchSize(const Size &size);
    
    /**
    * @~english Get current touch size of TextField.
    * @~chinese 获取当前的触摸区域大小。
    * @return @~english The TextField's touch size. @~chinese 触摸区域大小。
    */
    Size getTouchSize()const;
    
    /**
    * @~english Toggle enable touch area.
    * @~chinese 启用或关闭触摸区域。
    * @param enable @~english True if enable touch area, false otherwise. @~chinese True表明开启触摸区域，反之关闭。
    */
    void setTouchAreaEnabled(bool enable);
    
    virtual bool hitTest(const Vec2 &pt, const Camera* camera, Vec3 *p) const override;
    
    
    /**
    * @~english Set placeholder of TextField.
    * @~chinese 设置占位符。
    * @param value @~english The string value of placeholder. @~chinese 占位符。
    */
    void setPlaceHolder(const std::string& value);
    
    /**
    * @~english Get the placeholder of TextField.
    * @~chinese 获取占位符。
    * @return @~english A placeholder string. @~chinese 占位符。
    */
    const std::string& getPlaceHolder()const;
    
    /**
    * @~english Query the placeholder string color.
    * @~chinese 请求占位符使用颜色。
    * @return @~english The color of placeholder. @~chinese 占位符颜色。
    */
    const Color4B& getPlaceHolderColor()const;
    
    /**
    * @~english Change the placeholder color.
    * @~chinese 改变占位符颜色。
    * @param color @~english A color value in `Color3B`. @~chinese 占位符颜色。
    */
    void setPlaceHolderColor(const Color3B& color);
    
    /**
    * @~english Change the placeholder color.
    * @~chinese 改变占位符颜色。
    * @param color @~english A color value in `Color4B`. @~chinese 占位符颜色。
    */
    void setPlaceHolderColor(const Color4B& color);
    
    /**
    * @~english Query the text string color.
    * @~chinese 请求文本颜色。
    * @return @~english The color of the text. @~chinese 文本颜色。
    */
    const Color4B& getTextColor()const;
    
    /**
    * @~english Change the text color.
    * @~chinese 改变文本颜色。
    * @param textColor @~english The color value in `Color4B`. @~chinese 文本颜色。
    */
    void setTextColor(const Color4B& textColor);
     
    /**
    * @~english Change font size of TextField.
    * @~chinese 改变字体大小。
    * @param size @~english The integer font size. @~chinese 字体大小。
    */
    void setFontSize(int size);
    
    /**
    * @~english Query the font size.
    * @~chinese 请求获取字体大小。
    * @return @~english The integer font size. @~chinese 字体大小。
    */
    int getFontSize()const;
    
    /**
    * @~english Change the font name of TextField.
    * @~chinese 改变字体名称。
    * @param name @~english The font name string. @~chinese 字体名称。
    */
    void setFontName(const std::string& name);
    
    /**
    * @~english Query the TextField's font name.
    * @~chinese 请求获取字体名称。
    * @return @~english The font name string. @~chinese 字体名称。
    */
    const std::string& getFontName()const;
    
    
    /**
    * @~english Detach the IME.
    * @~chinese 取消关联输入法编辑器。
    */
    virtual void didNotSelectSelf();
    
    /**
    * @~english Change content of TextField.
    * @~chinese 改变文本内容。
    * @deprecated Use @see `setString(const std::string&)` instead.
    * @param text @~english A string content. @~chinese 文本内容。
    */
    CC_DEPRECATED_ATTRIBUTE void setText(const std::string& text){this->setString(text);}

    /**
    * @~english Query the content of TextField.
    * @~chinese 请求获取文本内容。
    * @deprecated Use @see `getString` instead.
    * @return @~english The string value of TextField. @~chinese 文本内容。
    */
    CC_DEPRECATED_ATTRIBUTE const std::string& getStringValue()const{return this->getString();}
    
    /**
    * @~english Change content of TextField.
    * @~chinese 改变文本内容。
    * @param text @~english A string content. @~chinese 文本内容。
    */
    void setString(const std::string& text);
    
    /**
    * @~english Query the content of TextField.
    * @~chinese 请求获取文本内容。
    * @return @~english The string value of TextField. @~chinese 文本内容。
    */
    const std::string& getString()const;
    
    virtual bool onTouchBegan(Touch *touch, Event *unusedEvent) override;
    
    
    /**
    * @~english Toggle maximize length enable
    * @~chinese 开关最大长度限制。
    * @param enable @~english True if enable maximize length, false otherwise. @~chinese True表明开启最大长度限制，反之关闭。
    */
    void setMaxLengthEnabled(bool enable);
    
    /**
    * @~english Query whether max length is enabled or not.
    * @~chinese 请求是否开启了最大长度限制。
    * @return @~english True if maximize length is enabled, false otherwise. @~chinese True表明开启最大长度限制，反之关闭。
    */
    bool isMaxLengthEnabled()const;
    
    /**
    * @~english Change maximize input length limitation.
    * @~chinese 改变最大输入长度限制。
    * @param length @~english A character count in integer. @~chinese 最大长度。
    */
    void setMaxLength(int length);
    
    /**
    * @~english Query maximize input length of TextField.
    * @~chinese  请求最大输入长度。
    * @return @~english The integer value of maximize input length. @~chinese 最大长度。
    */
    int getMaxLength()const;
    
    /**
    * @~english Query the input string length.
    * @~chinese 请求输入字符串长度。
    * @return @~english A integer length value. @~chinese 字符串长度。
    */
    int getStringLength() const;
    
    /**
    * @~english Toggle enable password input mode.
    * @~chinese 开关密码输入模式。
    * @param enable @~english True if enable password input mode, false otherwise. @~chinese True表示开启密码输入模式，反之关闭。
    */
    void setPasswordEnabled(bool enable);
    
    /**
    * @~english Query whether password is enabled or not.
    * @~chinese 请求密码输入模式是否开启。
    * @return @~english True if password is enabled, false otherwise. @~chinese True表示开启密码输入模式，反之关闭。
    */
    bool isPasswordEnabled()const;

    /**
    * @~english Change password style text.
    * @~chinese 改变密码模式下的文本样式。
    * @param styleText @~english The styleText for password mask, the default value is "*". @~chinese 密码掩码的文本样式，默认为“*”。
    */
    void setPasswordStyleText(const char* styleText);
    
    /**
    * @~english Query the password style text.
    * @~chinese 请求密码模式的文本样式。
    * @return @~english A password style text. @~chinese 密码模式的文本样式。
    */
    const char* getPasswordStyleText()const;
    
    virtual void update(float dt) override;
    
    /**
    * @~english Query whether the IME is attached or not.
    * @~chinese 请求是否输入法编辑器已被关联。
    * @return @~english True if IME is attached, false otherwise. @~chinese True表示已被关联，反之未关联。
    */
    bool getAttachWithIME()const;
    
    /**
    * @~english Toggle attach with IME.
    * @~chinese 设置关联输入法编辑器。
    * @param attach @~english True if attach with IME, false otherwise. @~chinese True表示已被关联，反之未关联。
    */
    void setAttachWithIME(bool attach);
    
    /**
    * @~english Query whether IME is detached or not.
    * @~chinese 请求是否输入法编辑器已被取消关联。
    * @return @~english True if IME is detached, false otherwise. @~chinese True表示已被取消关联，反之已关联。
    */
    bool getDetachWithIME()const;
    
    /**
    * @~english Toggle detach with IME.
    * @~chinese 设置取消关联输入法编辑器。
    * @param detach @~english True if detach with IME, false otherwise. @~chinese True表示已被取消关联，反之已关联。
    */
    void setDetachWithIME(bool detach);
    
    
    /**
    * @~english Whether it is ready to get the inserted text or not.
    * @~chinese 是否开启插入文本模式。
    * @return @~english True if the insert text is ready, false otherwise. @~chinese True表示开启插入文本模式，反之未开启。
    */
    bool getInsertText()const;
    
    /**
    * @~english Toggle enable insert text mode
    * @~chinese 开关插入文本模式。
    * @param insertText @~english True if enable insert text, false otherwise. @~chinese True表示开启插入文本模式，反之未开启。
    */
    void setInsertText(bool insertText);
     
    /**
    * @~english Whether it is ready to delete backward in TextField.
    * @~chinese 是否允许回删。
    * @return @~english True is the delete backward is enabled, false otherwise. @~chinese True表示允许回删，反之不允许。
    */
    bool getDeleteBackward()const;
    
    /**
    * @~english Toggle enable delete backward mode.
    * @~chinese 开关回删模式。
    * @param deleteBackward @~english True is delete backward is enabled, false otherwise. @~chinese True表示允许回删，反之不允许。
    */
    void setDeleteBackward(bool deleteBackward);
    
    /**
    * @~english Add a event listener to TextField, when some predefined event happens, the callback will be called.
    * @~chinese 添加一个监听器，当一些预定义事件发生时进行回调操作。
    * @deprecated Use @see `addEventListener` instead.
    * @param target @~english A pointer of `Ref*` type. @~chinese Ref类型的指针。
    * @param selecor @~english A member function pointer with type of `SEL_TextFieldEvent`. @~chinese 用以监听的回调函数。
    */
    CC_DEPRECATED_ATTRIBUTE void addEventListenerTextField(Ref* target, SEL_TextFieldEvent selecor);
    /**
    * @~english Add a event listener to TextField, when some predefined event happens, the callback will be called.
    * @~chinese 添加一个监听器，当一些预定义事件发生时进行回调操作。
    * @param callback @~english A callback function with type of `ccTextFieldCallback`. @~chinese 用以监听的回调函数。
    */
    void addEventListener(const ccTextFieldCallback& callback);
    
    /**
    * @~english Returns the "class name" of widget.
    * @~chinese 返回widget的类名称。
    * @return @~english The "class name" of widget. @~chinese widget的类名称。
    */
    virtual std::string getDescription() const override;
    
    /**
    * @~english Get the the renderer size in auto mode.
    * @~chinese 获取渲染时的大小。
    *
    * @return @~english A delimitation zone. @~chinese 一个限定区域。
    */
    virtual Size getAutoRenderSize();
    //overide functions.
    virtual Size getVirtualRendererSize() const override;
    virtual Node* getVirtualRenderer() override;
    virtual void onEnter() override;
    
    /**
    * @~english Attach the IME for inputing.
    * @~chinese 关联输入法编辑器用以输入。
    */
    void attachWithIME();
    
    /**
    * @~english Change the text area size.
    * @~chinese 改变文本区域大小。
    * @param size @~english A delimitation zone. @~chinese 一个限定区域。
    */
    void setTextAreaSize(const Size &size);
    
    /**
    * @~english Change horizontal text alignment.
    * @~chinese 改变文本水平对齐类型。
    * @param alignment @~english A alignment arguments in @see `TextHAlignment`. @~chinese 水平对齐类型。
    */
    void setTextHorizontalAlignment(TextHAlignment alignment);

    /**
    * @~english Inquire the horizontal alignment
    * @~chinese 获取水平对齐类型。
    * @return @~english The horizontal alignment @~chinese 水平对齐类型。
    */
    TextHAlignment getTextHorizontalAlignment() const;
    
    /**
    * @~english Change the vertical text alignment.
    * @~chinese 改变文本垂直对齐类型。
    * @param alignment @~english A alignment arguments in @see `TextVAlignment`. @~chinese 垂直对齐类型。
    */
    void setTextVerticalAlignment(TextVAlignment alignment);

    /**
    * @~english Inquire the horizontal alignment
    * @~chinese 获取文本垂直对齐类型。
    * @return @~english The horizontal alignment @~chinese 垂直对齐类型。
    */
    TextVAlignment getTextVerticalAlignment() const;
    
CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    
protected:
    virtual void initRenderer() override;
    void attachWithIMEEvent();
    void detachWithIMEEvent();
    void insertTextEvent();
    void deleteBackwardEvent();
    virtual void onSizeChanged() override;
  
    void textfieldRendererScaleChangedWithSize();
    
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void adaptRenderers() override;
protected:
    UICCTextField* _textFieldRenderer;

    float _touchWidth;
    float _touchHeight;
    bool _useTouchArea;
    
    Ref* _textFieldEventListener;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (push)
#pragma warning (disable: 4996)
#endif
    SEL_TextFieldEvent _textFieldEventSelector;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (pop)
#endif
    ccTextFieldCallback _eventCallback;
    
    std::string _passwordStyleText;
    bool _textFieldRendererAdaptDirty;
private:
    enum class FontType
    {
        SYSTEM,
        TTF
    };

    std::string _fontName;
    int _fontSize;
    FontType _fontType;
};

}

// end of ui group
/// @}
NS_CC_END

#endif /* defined(__TextField__) */
