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

#ifndef __CCEDITTEXT_H__
#define __CCEDITTEXT_H__

#include "2d/CCIMEDelegate.h"
#include "extensions/ExtensionMacros.h"
#include "../CCControlExtension/CCControlExtensions.h"

NS_CC_EXT_BEGIN

class EditBox;
class EditBoxImpl;


class EditBoxDelegate 
{
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~EditBoxDelegate() {};
    
    /**
     * 本方法在键盘弹出，编辑框获得焦点后调用
     * @param editBox 产生事件的编辑框对象
     * @js NA
     * @lua NA
     */
    virtual void editBoxEditingDidBegin(EditBox* editBox) {};
    
    
    /**
     * 本方法在键盘隐藏，编辑框失去焦点后调用
     * @param editBox 产生事件的编辑框对象
     * @js NA
     * @lua NA
     */
    virtual void editBoxEditingDidEnd(EditBox* editBox) {};
    
    /**
     * 本方法在编辑框文本内容被改变时调用
     * @param editBox 产生事件的编辑框对象
     * @param text 新文本
     * @js NA
     * @lua NA
     */
    virtual void editBoxTextChanged(EditBox* editBox, const std::string& text) {};
    
    /**
     * 本方法在按下返回按钮，或者按下键盘以外区域时被调用
     * @param editBox 产生事件的编辑框对象
     * @js NA
     * @lua NA
     */
    virtual void editBoxReturn(EditBox* editBox) = 0;
    
};

/**
 * \brief 编辑框类
 *
 * 本控件可用于让用户输入少量文本
 * 
 */
 
class EditBox
: public ControlButton
, public IMEDelegate
{
public:
    enum class KeyboardReturnType
    {
        DEFAULT,
        DONE,
        SEND,
        SEARCH,
        GO
    };
    
    /**
     * \brief EditBox::InputMode定义了用户可输入的文本类型
     */
    enum class InputMode
    {
        /**
         * 用户可输入任何文本，包括换行
         */
        ANY,
        
        /**
         * 用户可输入一个电子邮件地址
         */
        EMAIL_ADDRESS,
        
        /**
         * 用户可输入一个整数
         */
        NUMERIC,
        
        /**
         * 用户可输入一个电话号码
         */
        PHONE_NUMBER,
        
        /**
         * 用户可输入一个URL
         */
        URL,
        
        /**
         * 用户可输入一个实数
         * 跟NUMERIC相比，此模式可以多出一个小数点
         */
        DECIMAL,
        
        /**
         * 用户可输入除换行符外的任何文本
         */
        SINGLE_LINE,
    };
    
    /**
     * \brief EditBox::InputFlag定义了被输入文字的显示格式
     */
    enum class InputFlag
    {
        /**
         * 表示输入文本为机密数据，只要可能就不要直接显示。
         * 此标志暗含了SENSITIVE标志。
         */
        PASSWORD,
        
        /**
         * 表示输入文字为敏感数据，在实现时禁止为了预测、自动填充
         * 或者其余加速输入的目的而将其存入字典或者表格。
         * 例如信用卡号就是一种敏感数据。
         */
        SENSITIVE,
        
        /**
         * 表示在文本编辑的过程中，每个单词的首字母都应该大写。
         */
        INITIAL_CAPS_WORD,
        
        /**
         * 表示在文本编辑的过程中，每句话的首字母都应该大写。
         */
        INITIAL_CAPS_SENTENCE,
        
        /**
         * 自动将所有字母大写。
         */
        INTIAL_CAPS_ALL_CHARACTERS,
    };
    
    /**
     * 创建一个给定尺寸的编辑框
     * @return 返回一个autorelease的编辑框指针，只有在你手动retain的时候才需要自己release。
     */
    static EditBox* create(const Size& size, Scale9Sprite* pNormal9SpriteBg, Scale9Sprite* pPressed9SpriteBg = NULL, Scale9Sprite* pDisabled9SpriteBg = NULL);

    /**
     * 构造函数
     * @js ctor
     */
    EditBox(void);
    
    /**
     * 析构函数
     * @js NA
     * @lua NA
     */
    virtual ~EditBox(void);

    /**
     * 用指定尺寸初始化编辑框。应该在构造函数执行完毕后即刻执行本函数。
     * @param size 编辑框的尺寸
     */
    bool initWithSizeAndBackgroundSprite(const Size& size, Scale9Sprite* pNormal9SpriteBg);
    
    /**
     * 获取/设置编辑框的委托
     * @lua NA
     */
    void setDelegate(EditBoxDelegate* pDelegate);
    /**
     * @js NA
     * @lua NA
     */
    EditBoxDelegate* getDelegate();
    
#if CC_ENABLE_SCRIPT_BINDING
    /**
     * 注册一个用于编辑框事件的脚本函数
     *
     * 此处理器会在onExit()调用结束后自行移除
     * @code
     * -- lua sample
     * local function editboxEventHandler(eventType)
     *     if eventType == "began" then
     *         -- 在键盘弹出，编辑框获得焦点时触发
     *     elseif eventType == "ended" then
     *         -- 在键盘隐藏，编辑框失去焦点后触发
     *     elseif eventType == "changed" then
     *         -- 在键盘文本内容被改变时触发
     *     elseif eventType == "return" then
     *         -- 在按下返回按钮，或者按下键盘以外区域时触发
     *     end
     * end
     *
     * local editbox = EditBox:create(Size(...), Scale9Sprite:create(...))
     * editbox = registerScriptEditBoxHandler(editboxEventHandler)
     * @endcode
     *
     * @param handler 一个用于表示lua函数的数字
     * @js NA
     * @lua NA
     */
    void registerScriptEditBoxHandler(int handler);
    
    /**
     * 取消注册一个用于处理编辑框事件的脚本函数
     * @js NA
     * @lua NA
     */
    void unregisterScriptEditBoxHandler(void);
    /**
     * 获取脚本的处理器
     * @js NA
     * @lua NA
     */
    int  getScriptEditBoxHandler(void){ return _scriptEditBoxHandler ;}
    
#endif // #if CC_ENABLE_SCRIPT_BINDING
    
    /**
     * 对编辑框的文本进行设置
     * @param pText 指定文本
     */
    void setText(const char* pText);
    
    /**
     * 获取输入框输入的文本
     * @return 输入框输入的文本
     */
    const char* getText(void);
	
	/**
	 * 设置字体
	 * @param pFontName 字体名称
	 * @param fontSize 字体尺寸
	 */
	void setFont(const char* pFontName, int fontSize);
    
	/**
	 * 设置字体名称
	 * @param pFontName 字体名称
	 */
	void setFontName(const char* pFontName);
    
    /**
	 * 设置字体尺寸
	 * @param fontSize 字体尺寸
	 */
	void setFontSize(int fontSize);
    
    /**
     * 设置控件字体的颜色
     */
    void setFontColor(const Color3B& color);
    
	/**
	 * 设置占位符的字体
	 * @param pFontName 字体名称
	 * @param fontSize 字体尺寸
	 */
	void setPlaceholderFont(const char* pFontName, int fontSize);
    
    /**
	 * 设置占位符的字体名称
	 * @param pFontName 字体名称
	 */
	void setPlaceholderFontName(const char* pFontName);
    
    /**
	 * 设置占位符的字体尺寸
	 * @param fontSize 字体尺寸
	 */
	void setPlaceholderFontSize(int fontSize);
    
    /**
     * 设置当输入框为空时，占位符的字体颜色
     * IOS不支持
     */
    void setPlaceholderFontColor(const Color3B& color);
    
    /**
     * 设置当输入框为空时，占位符的文本内容
     * @param pText 指定文本
     */
    void setPlaceHolder(const char* pText);
    
    /**
     * 获取当输入框为空时，占位符的文本内容
     */
    const char* getPlaceHolder(void);
    
    /**
     * 设置编辑框的输入模式
     * @param inputMode EditBox::InputMode常量中的一种模式
     */
    void setInputMode(InputMode inputMode);
    
    /**
     * 设置编辑框的最大输入长度
     * 设置此值默认就打开了多行输入模式
     * 在Android, iOS和Windows Phone可用
     *
     * @param maxLength 最大长度
     */
    void setMaxLength(int maxLength);
    
    /**
     * 获取编辑框的最大可输入长度
     *
     * @return 最大可输入长度
     */
    int getMaxLength();
    
    /**
     * 设置编辑框的输入标志
     * @param inputFlag EditBox::InputFlag常量中的某种标志
     */
    void setInputFlag(InputFlag inputFlag);
    
    /**
     * 设置编辑框的返回类型
     * @param returnType EditBox::KeyboardReturnType常量中的某种类型.
     */
    void setReturnType(EditBox::KeyboardReturnType returnType);
    
    /* override functions */
    virtual void setPosition(const Vec2& pos) override;
    virtual void setVisible(bool visible) override;
    virtual void setContentSize(const Size& size) override;
	virtual void setAnchorPoint(const Vec2& anchorPoint) override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, bool parentTransformUpdated) override;
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
    
    /* 回调函数
     * @js NA
     * @lua NA
     */
    void touchDownAction(Ref *sender, Control::EventType controlEvent);
    
protected:
    void updatePosition(float dt);
    EditBoxImpl*      _editBoxImpl;
    EditBoxDelegate*  _delegate;
    
    InputMode    _editBoxInputMode;
    InputFlag    _editBoxInputFlag;
    EditBox::KeyboardReturnType  _keyboardReturnType;
    
    std::string _text;
    std::string _placeHolder;
    
    std::string _fontName;
    std::string _placeholderFontName;
    
    int _fontSize;
    int _placeholderFontSize;
    
    Color3B _colText;
    Color3B _colPlaceHolder;
    
    int   _maxLength;
    float _adjustHeight;
#if CC_ENABLE_SCRIPT_BINDING
    int   _scriptEditBoxHandler;
#endif
};

NS_CC_EXT_END

#endif /* __CCEDITTEXT_H__ */

