/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen
 
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

#ifndef __UIEDITTEXT_H__
#define __UIEDITTEXT_H__

#include "base/CCIMEDelegate.h"
#include "ui/GUIDefine.h"
#include "ui/UIButton.h"
#include "ui/UIScale9Sprite.h"

NS_CC_BEGIN

/**
 * @addtogroup ui
 * @{
 */
namespace ui {
        
    class EditBox;
    class EditBoxImpl;
        
    /**
     *@brief @~english Editbox delgate class.
     * It's useful when you want to do some customization duing Editbox input event
     *
     * @~chinese 编辑框代理类。
     * 当你想定制编辑框输入事件时，这个类非常有用。
     * 
     * @js NA
     * @lua NA
     */
    class CC_GUI_DLL EditBoxDelegate
    {
    public:
        virtual ~EditBoxDelegate() {};
            
        /**@~english
         * This method is called when an edit box gains focus after keyboard is shown.
         * @~chinese 
         * 这个方法在编辑框对象开始获得焦点时被调用
         * @param editBox @~english The edit box object that generated the event.
         * @~chinese 一个编辑框对象指针
         */
        virtual void editBoxEditingDidBegin(EditBox* editBox) {};
            
            
        /**@~english
         * This method is called when an edit box loses focus after keyboard is hidden.
         * @~chinese 
         * 当编辑框对象编辑时失去焦点后调用的函数。
         * @param editBox @~english The edit box object that generated the event.
         * @~chinese 一个编辑框对象指针
         */
        virtual void editBoxEditingDidEnd(EditBox* editBox) {};
            
        /**@~english
         * This method is called when the edit box text was changed.
         * @~chinese 
         * 这个方法在编辑框对象中的文本内容开始变化的时候被调用。
         * @param editBox @~english The edit box object that generated the event.
         * @~chinese 一个编辑框对象指针
         * @param text @~english The new text.
         * @~chinese 新文本内容。
         */
        virtual void editBoxTextChanged(EditBox* editBox, const std::string& text) {};
            
        /**@~english
         * This method is called when the return button was pressed or the outside area of keyboard was touched.
         * @~chinese 
         * 这个方法在编辑框对象的Return按钮被按下，或者编辑框键盘以外的区域被点击时所调用。
         * @param editBox @~english The edit box object that generated the event.
         * @~chinese 一个编辑框对象指针
         */
        virtual void editBoxReturn(EditBox* editBox) = 0;
            
    };
        
    /**
     * @brief @~english Class for edit box.
     *
     * You can use this widget to gather small amounts of text from the user.
     *
     * @~chinese 一个用来输入文本的类
     * 
     * 你可以使用这个类来获取用户的少量文本输入
     * 
     */
        
    class CC_GUI_DLL EditBox
        : public Widget
        , public IMEDelegate
    {
    public:

        /**@~english
         * The popup keyboard return type.
         * @~chinese 
         * 键盘的返回键类型
         */
        enum class KeyboardReturnType
        {
            DEFAULT,
            DONE,
            SEND,
            SEARCH,
            GO
        };
            
        /**
         * @brief @~english The EditBox::InputMode defines the type of text that the user is allowed
         * to enter.
         * @~chinese EditBox::InputMode定义了可以输入的文本类型
         */
        enum class InputMode
        {
            /**@~english
             * The user is allowed to enter any text, including line breaks.
             * @~chinese 
             * 用户可以输入任何文本,包括换行符。
             */
            ANY,
                
            /**@~english
             * The user is allowed to enter an e-mail address.
             * @~chinese 
             * 允许用户输入一个电子邮件地址。
             */
            EMAIL_ADDRESS,
                
            /**@~english
             * The user is allowed to enter an integer value.
             * @~chinese 
             * 允许用户输入一个整数值。
             */
            NUMERIC,
                
            /**@~english
             * The user is allowed to enter a phone number.
             * @~chinese 
             * 允许用户输入一个电话号码。
             */
            PHONE_NUMBER,
                
            /**@~english
             * The user is allowed to enter a URL.
             * @~chinese 
             * 允许用户输入一个URL。
             */
            URL,
                
            /**@~english
             * The user is allowed to enter a real number value.
             * This extends kEditBoxInputModeNumeric by allowing a decimal point.
             * @~chinese 
             * 允许用户输入一个实数
             * 通过允许一个小数点扩展了kEditBoxInputModeNumeric模式
             */
            DECIMAL,
                
            /**@~english
             * The user is allowed to enter any text, except for line breaks.
             * @~chinese 
             *除了换行符以外，用户可以输入任何文本,
             */
            SINGLE_LINE,
        };
            
        /**
         * @brief @~english The EditBox::InputFlag defines how the input text is displayed/formatted.
         * @~chinese EditBox::InputFlag定义如何显示和格式化输入文本。
         */
        enum class InputFlag
        {
            /**@~english
             * Indicates that the text entered is confidential data that should be
             * obscured whenever possible. This implies EDIT_BOX_INPUT_FLAG_SENSITIVE.
             * @~chinese 
             * 表明输入的文本是保密的数据，任何时候都应该隐藏起来
             * 它隐含了EDIT_BOX_INPUT_FLAG_SENSITIVE
             */
            PASSWORD,
                
            /**@~english
             * Indicates that the text entered is sensitive data that the
             * implementation must never store into a dictionary or table for use
             * in predictive, auto-completing, or other accelerated input schemes.
             * A credit card number is an example of sensitive data.
             * @~chinese 
             * 表明输入的文本是敏感数据，
             * 它禁止存储到字典或表里面，也不能用来自动补全和提示用户输入。
             * 一个信用卡号码就是一个敏感数据的例子。
             */
            SENSITIVE,
                
            /**@~english
             * This flag is a hint to the implementation that during text editing,
             * the initial letter of each word should be capitalized.
             * @~chinese 
             * 这个标志的作用是设置一个提示,在文本编辑的时候，是否把每一个单词的首字母大写。
             */
            INITIAL_CAPS_WORD,
                
            /**@~english
             * This flag is a hint to the implementation that during text editing,
             * the initial letter of each sentence should be capitalized.
             * @~chinese 
             * 这个标志的作用是设置一个提示,在文本编辑，是否每个句子的首字母大写。
             */
            INITIAL_CAPS_SENTENCE,
                
            /**@~english
             * Capitalize all characters automatically.
             * @~chinese 
             * 自动把输入的所有字符大写。
             */
            INITIAL_CAPS_ALL_CHARACTERS,
        };
            
        /**@~english
         * create a edit box with size.
         * @~chinese 
         * 创建一个固定大小的编辑框
         * @return @~english An autorelease pointer of EditBox, you don't need to release it only if you retain it again.
         * @~chinese 一个编辑框对象指针, 只有当你对返回对象调用retain的时候才需要调用release
         */
        static EditBox* create(const Size& size,
                               Scale9Sprite* normalSprite,
                               Scale9Sprite* pressedSprite = nullptr,
                               Scale9Sprite* disabledSprite = nullptr);

            
        /**@~english
         * create a edit box with size.
         * @~chinese 
         * 创建一个固定大小的编辑框。
         * @return @~english An autorelease pointer of EditBox, you don't need to release it only if you retain it again.
         * @~chinese 一个编辑框对象指针，只有当你对返回对象调用retain的时候才需要调用release
         */
        static EditBox* create(const Size& size,
                               const std::string& normal9SpriteBg,
                               TextureResType texType = TextureResType::LOCAL);
            
        /**@~english
         * Constructor.
         * @~chinese 
         * 构造函数。
         * @js ctor
         * @lua new
         */
        EditBox(void);
            
        /**@~english
         * Destructor.
         * @~chinese 
         * 析构函数。
         * @js NA
         * @lua NA
         */
        virtual ~EditBox(void);
            
        /**@~english
         * Init edit box with specified size. This method should be invoked right after constructor.
         * @~chinese 
         * 使用指定大小初始化编辑框。这个方法应该在构造函数之后调用。
         * @param size @~english The size of edit box.
         * @~chinese 编辑框的大小。
         * @param normal9SpriteBg  @~english background image of edit box.
         * @~chinese 编辑框的背景图片名字。
         * @param texType @~english the resource type, the default value is TextureResType::LOCAL
         * @~chinese 资源类型,默认值是TextureResType::LOCAL
         * @return @~english Whether initialization is successfully or not.
         * @~chinese 是否初始化成功。
         */
        bool initWithSizeAndBackgroundSprite(const Size& size,
                                             const std::string& normal9SpriteBg,
                                             TextureResType texType = TextureResType::LOCAL);
            
        
        /**@~english
         * Init edit box with specified size. This method should be invoked right after constructor.
         * @~chinese 
         * 使用指定大小初始化编辑框，这个方法应该在构造函数之后被调用。
         * @param size @~english The size of edit box.
         * @~chinese 编辑框的大小。
         * @param normal9SpriteBg  @~english background image of edit box.
         * @~chinese 编辑框的背景图片名字。
         * @return @~english Whether initialization is successfully or not.
         * @~chinese 是否初始化成功。
         */
        bool initWithSizeAndBackgroundSprite(const Size& size, Scale9Sprite* normal9SpriteBg);

        /**@~english
         * Sets the delegate for edit box.
         * @~chinese 
         * 设置编辑框控件的代理类
         * @lua NA
         */
        void setDelegate(EditBoxDelegate* delegate);

        /**
         * @js NA
         * @lua NA
         */
        EditBoxDelegate* getDelegate();
            
#if CC_ENABLE_SCRIPT_BINDING
        /**@~english
         * Registers a script function that will be called for EditBox events.
         *
         * This handler will be removed automatically after onExit() called.
         * @~chinese 
         * 注册一个脚本函数,当编辑框发出事件时，这个脚本函数会被调用
         * 
         * 这个回调函数将会在onExit函数调用后被删除。
         * @~english
         * @code
         * -- lua sample
         * local function editboxEventHandler(eventType)
         *     if eventType == "began" then
         *         -- triggered when an edit box gains focus after keyboard is shown
         *     elseif eventType == "ended" then
         *         -- triggered when an edit box loses focus after keyboard is hidden.
         *     elseif eventType == "changed" then
         *         -- triggered when the edit box text was changed.
         *     elseif eventType == "return" then
         *         -- triggered when the return button was pressed or the outside area of keyboard was touched.
         *     end
         * end
         *
         * local editbox = EditBox:create(Size(...), Scale9Sprite:create(...))
         * editbox = registerScriptEditBoxHandler(editboxEventHandler)
         * @endcode
         *
         * @~chinese
         * @code
         * -- lua sample
         * local function editboxEventHandler(eventType)
         *     if eventType == "began" then
         *         -- 当编辑框获得焦点并且键盘弹出的时候被调用
         *     elseif eventType == "ended" then
         *         -- 当编辑框失去焦点并且键盘消失的时候被调用
         *     elseif eventType == "changed" then
         *         -- 当编辑框的文本被修改的时候被调用
         *     elseif eventType == "return" then
         *         -- 当用户点击编辑框的键盘以外的区域，或者键盘的Return按钮被点击时所调用
         *     end
         * end
         *
         * local editbox = EditBox:create(Size(...), Scale9Sprite:create(...))
         * editbox = registerScriptEditBoxHandler(editboxEventHandler)
         * @endcode
         *
         * @param handler @~english A number that indicates a lua function.
         * @~chinese 一个整数，用来表示一个lua函数句柄
         * @js NA
         * @lua NA
         */
        void registerScriptEditBoxHandler(int handler);
            
        /**@~english
         * Unregisters a script function that will be called for EditBox events.
         * @~chinese 
         * 注销已注册的编辑框事件监听脚本函数
         * @js NA
         * @lua NA
         */
        void unregisterScriptEditBoxHandler(void);
        /**@~english
         * get a script Handler
         * @~chinese 
         * 获取一个脚本函数句柄
         * @js NA
         * @lua NA
         */
        int  getScriptEditBoxHandler(void){ return _scriptEditBoxHandler ;}
            
#endif // #if CC_ENABLE_SCRIPT_BINDING
            
        /**@~english
         * Set the text entered in the edit box.
         * @~chinese 
         * 设置编辑框中输入的文本。
         * @param pText @~english The given text.
         * @~chinese 给定的文本字符串。
         */
        void setText(const char* pText);
            
        /**@~english
         * Get the text entered in the edit box.
         * @~chinese 
         * 获取编辑框中输入的文本。
         * @return @~english The text entered in the edit box.
         * @~chinese 编辑框中输入的文本。
         */
        const char* getText(void);
            
        /**@~english
         * Set the font for EditBox. Only system font is allowed.
         * @~chinese 
         * 设置编辑框的字体。仅支持系统字体
         * @param pFontName @~english The font name.
         * @~chinese 字体名称。
         * @param fontSize @~english The font size.
         * @~chinese 字体大小。
         */
        void setFont(const char* pFontName, int fontSize);
            
        /**@~english
         * Set the font name. Only system font is allowed.
         * @~chinese 
         * 设置字体的名字。仅支持系统字体
         * @param pFontName @~english The font name.
         * @~chinese 字体名称。
         */
        void setFontName(const char* pFontName);
            
        /**@~english
         * Set the font size.
         * @~chinese 
         * 设置字体大小。
         * @param fontSize @~english The font size.
         * @~chinese 字体大小。
         */
        void setFontSize(int fontSize);
            
        /**@~english
         * Set the font color of the widget's text.
         * @~chinese 
         * 设置编辑框的文本字体颜色。
         */
        void setFontColor(const Color3B& color);
            
        /**@~english
         * Set the placeholder's font. Only system font is allowed.
         * @~chinese 
         * 设置占位符的字体。仅支持系统字体
         * @param pFontName @~english The font name.
         * @~chinese 字体名称。
         * @param fontSize @~english The font size.
         * @~chinese 字体大小。
         */
        void setPlaceholderFont(const char* pFontName, int fontSize);
            
        /**@~english
         * Set the placeholder's font name. Only system font is allowed.
         * @~chinese 
         * 设置占位符的字体名称。仅支持系统字体
         * @param pFontName @~english The font name.
         * @~chinese 字体名称。
         */
        void setPlaceholderFontName(const char* pFontName);
            
        /**@~english
         * Set the placeholder's font size.
         * @~chinese 
         * 设置占位符的字体大小。
         * @param fontSize @~english The font size.
         * @~chinese 字体大小。
         */
        void setPlaceholderFontSize(int fontSize);
            
        /**@~english
         * Set the font color of the placeholder text when the edit box is empty.
         * @~chinese 
         * 当编辑框为空的时候，设置占位符文本字体颜色，
         * @param color @~english The font color in Color3B
         * @~chinese 字体的颜色，类型是Color3B
         */
        void setPlaceholderFontColor(const Color3B& color);

        /**@~english
         * Set the font color of the placeholder text when the edit box is empty.
         * @~chinese 
         * 当编辑框为空的时候，设置占位符文本字体颜色
         * @param color @~english The font color in Color4B
         * @~chinese 字体的颜色，类型是Color4B
         */
        void setPlaceholderFontColor(const Color4B& color);
            
        /**@~english
         * Set a text in the edit box that acts as a placeholder when an
         * edit box is empty.
         * @~chinese 
         * 当编辑框为空的时候，设置编辑框中的占位符文本
         * @param pText @~english The given text.
         * @~chinese 给定的文本。
         */
        void setPlaceHolder(const char* pText);
            
        /**@~english
         * Get a text in the edit box that acts as a placeholder when an
         * edit box is empty.
         * @~chinese 
         * 当编辑框为空的时候，获取编辑框中的占位符文本
         */
        const char* getPlaceHolder(void);
            
        /**@~english
         * Set the input mode of the edit box.
         * @~chinese 
         * 设置编辑框的输入模式。
         * @param inputMode @~english One of the EditBox::InputMode constants.
         * @~chinese EditBox::InputMode常量之一
         */
        void setInputMode(InputMode inputMode);
            
        /**@~english
         * Sets the maximum input length of the edit box.
         * Setting this value enables multiline input mode by default.
         * Available on Android, iOS and Windows Phone.
         *
         * @~chinese 
         * 设置编辑框允许输入的最大长度。
         * 设置这个值默认允许多行输入
         * 可以在Android,iOS和Windows Phone平台使用
         * 
         * @param maxLength @~english The maximum length.
         * @~chinese 最大长度。
         */
        void setMaxLength(int maxLength);
            
        /**@~english
         * Gets the maximum input length of the edit box.
         *
         * @~chinese 
         * 获取编辑框的最大输入长度。
         * 
         * @return @~english Maximum input length.
         * @~chinese 最大长度
         */
        int getMaxLength();
            
        /**@~english
         * Set the input flags that are to be applied to the edit box.
         * @~chinese 
         * 设置编辑框的输入标识，这个标识是EditBox::InputFlag类型
         * @param inputFlag @~english One of the EditBox::InputFlag constants.
         * @~chinese EditBox::InputFlag常量之一
         */
        void setInputFlag(InputFlag inputFlag);
            
        /**@~english
         * Set the return type that are to be applied to the edit box.
         * @~chinese 
         * 设置编辑框的键盘的Return类型，这个类型的取值为EditBox::KeyboardReturnType常量之一
         * @param returnType @~english One of the EditBox::KeyboardReturnType constants.
         * @~chinese EditBox::KeyboardReturnType常量之一
         */
        void setReturnType(EditBox::KeyboardReturnType returnType);
            
        virtual void setPosition(const Vec2& pos) override;
        virtual void setVisible(bool visible) override;
        virtual void setContentSize(const Size& size) override;
        virtual void setAnchorPoint(const Vec2& anchorPoint) override;

        /**@~english
         * Returns the "class name" of widget.
         * @~chinese 
         * 返回类名描述字符串
         */
        virtual std::string getDescription() const override;

        /**
         * @js NA
         * @lua NA
         */
        virtual void draw(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
        /**
         * @js NA
         * @lua NA
         */
        virtual void onEnter(void) override;
        /**
         * @js NA
         * @lua NA
         */
        virtual void onExit(void) override;
        /**
         * @js NA
         * @lua NA
         */
        virtual void keyboardWillShow(IMEKeyboardNotificationInfo& info) override;
        /**
         * @js NA
         * @lua NA
         */
        virtual void keyboardDidShow(IMEKeyboardNotificationInfo& info) override;
        /**
         * @js NA
         * @lua NA
         */
        virtual void keyboardWillHide(IMEKeyboardNotificationInfo& info) override;
        /**
         * @js NA
         * @lua NA
         */
        virtual void keyboardDidHide(IMEKeyboardNotificationInfo& info) override;

        /*
         * @js NA
         * @lua NA
         */
        void touchDownAction(Ref *sender, TouchEventType controlEvent);
            
    protected:
        virtual void adaptRenderers() override;

        void updatePosition(float dt);
        EditBoxImpl*      _editBoxImpl;
        EditBoxDelegate*  _delegate;
            
        InputMode    _editBoxInputMode;
        InputFlag    _editBoxInputFlag;
        EditBox::KeyboardReturnType  _keyboardReturnType;
            
        Scale9Sprite *_backgroundSprite;
        std::string _text;
        std::string _placeHolder;
            
        std::string _fontName;
        std::string _placeholderFontName;
            
        int _fontSize;
        int _placeholderFontSize;
            
        Color4B _colText;
        Color4B _colPlaceHolder;
            
        int   _maxLength;
        float _adjustHeight;
#if CC_ENABLE_SCRIPT_BINDING
        int   _scriptEditBoxHandler;
#endif
    };
}

// end of ui group
/// @}
NS_CC_END

#endif /* __UIEDITTEXT_H__ */

