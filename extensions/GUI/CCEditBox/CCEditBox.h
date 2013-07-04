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

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "../CCControlExtension/CCControlExtensions.h"

NS_CC_EXT_BEGIN


enum KeyboardReturnType {
    kKeyboardReturnTypeDefault = 0,
    kKeyboardReturnTypeDone,
    kKeyboardReturnTypeSend,
    kKeyboardReturnTypeSearch,
    kKeyboardReturnTypeGo
};


/**
 * \brief The EditBoxInputMode defines the type of text that the user is allowed
 * to enter.
 */
enum EditBoxInputMode
{
    /**
     * The user is allowed to enter any text, including line breaks.
     */
    kEditBoxInputModeAny = 0,
    
    /**
     * The user is allowed to enter an e-mail address.
     */
    kEditBoxInputModeEmailAddr,

    /**
     * The user is allowed to enter an integer value.
     */
    kEditBoxInputModeNumeric,

    /**
     * The user is allowed to enter a phone number.
     */
    kEditBoxInputModePhoneNumber,

    /**
     * The user is allowed to enter a URL.
     */
    kEditBoxInputModeUrl,

    /**
     * The user is allowed to enter a real number value.
     * This extends kEditBoxInputModeNumeric by allowing a decimal point.
     */
    kEditBoxInputModeDecimal,

    /**
     * The user is allowed to enter any text, except for line breaks.
     */
    kEditBoxInputModeSingleLine
};

/**
 * \brief The EditBoxInputFlag defines how the input text is displayed/formatted.
 */
enum EditBoxInputFlag
{
    /**
     * Indicates that the text entered is confidential data that should be
     * obscured whenever possible. This implies EDIT_BOX_INPUT_FLAG_SENSITIVE.
     */
    kEditBoxInputFlagPassword = 0,

    /**
     * Indicates that the text entered is sensitive data that the
     * implementation must never store into a dictionary or table for use
     * in predictive, auto-completing, or other accelerated input schemes.
     * A credit card number is an example of sensitive data.
     */
    kEditBoxInputFlagSensitive,

    /**
     * This flag is a hint to the implementation that during text editing,
     * the initial letter of each word should be capitalized.
     */
    kEditBoxInputFlagInitialCapsWord,

    /**
     * This flag is a hint to the implementation that during text editing,
     * the initial letter of each sentence should be capitalized.
     */
    kEditBoxInputFlagInitialCapsSentence,

    /**
     * Capitalize all characters automatically.
     */
    kEditBoxInputFlagInitialCapsAllCharacters

};


class EditBox;
class EditBoxImpl;


class EditBoxDelegate 
{
public:
    virtual ~EditBoxDelegate() {};
    
    /**
     * This method is called when an edit box gains focus after keyboard is shown.
     * @param editBox The edit box object that generated the event.
     */
    virtual void editBoxEditingDidBegin(EditBox* editBox) {};
    
    
    /**
     * This method is called when an edit box loses focus after keyboard is hidden.
     * @param editBox The edit box object that generated the event.
     */
    virtual void editBoxEditingDidEnd(EditBox* editBox) {};
    
    /**
     * This method is called when the edit box text was changed.
     * @param editBox The edit box object that generated the event.
     * @param text The new text.
     */
    virtual void editBoxTextChanged(EditBox* editBox, const std::string& text) {};
    
    /**
     * This method is called when the return button was pressed or the outside area of keyboard was touched.
     * @param editBox The edit box object that generated the event.
     */
    virtual void editBoxReturn(EditBox* editBox) = 0;
    
};

/**
 * \brief Class for edit box.
 *
 * You can use this widget to gather small amounts of text from the user.
 * 
 */
 
class EditBox
: public ControlButton
, public IMEDelegate
{
public:
    /**
     * Constructor.
     */
    EditBox(void);
    
    /**
     * Destructor.
     */
    virtual ~EditBox(void);

    /**
     * create a edit box with size.
     * @return An autorelease pointer of EditBox, you don't need to release it only if you retain it again.
     */
    static EditBox* create(const Size& size, Scale9Sprite* pNormal9SpriteBg, Scale9Sprite* pPressed9SpriteBg = NULL, Scale9Sprite* pDisabled9SpriteBg = NULL);
    
    /**
     * Init edit box with specified size. This method should be invoked right after constructor.
     * @param size The size of edit box.
     */
    bool initWithSizeAndBackgroundSprite(const Size& size, Scale9Sprite* pNormal9SpriteBg);
    
    /**
     * Gets/Sets the delegate for edit box.
     */
    void setDelegate(EditBoxDelegate* pDelegate);
    EditBoxDelegate* getDelegate();
    /**
     * Registers a script function that will be called for EditBox events.
     *
     * This handler will be removed automatically after onExit() called.
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
     * @param handler A number that indicates a lua function.
     */
    void registerScriptEditBoxHandler(int handler);
    
    /**
     * Unregisters a script function that will be called for EditBox events.
     */
    void unregisterScriptEditBoxHandler(void);
    /**
     * get a script Handler
     */
    int  getScriptEditBoxHandler(void){ return _scriptEditBoxHandler ;}
    /**
     * Set the text entered in the edit box.
     * @param pText The given text.
     */
    void setText(const char* pText);
    
    /**
     * Get the text entered in the edit box.
     * @return The text entered in the edit box.
     */
    const char* getText(void);
	
	/**
	 * Set the font.
	 * @param pFontName The font name.
	 * @param fontSize The font size.
	 */
	void setFont(const char* pFontName, int fontSize);
    
	/**
	 * Set the font name.
	 * @param pFontName The font name.
	 */
	void setFontName(const char* pFontName);
    
    /**
	 * Set the font size.
	 * @param fontSize The font size.
	 */
	void setFontSize(int fontSize);
    
    /**
     * Set the font color of the widget's text.
     */
    void setFontColor(const ccColor3B& color);
    
	/**
	 * Set the placeholder's font.
	 * @param pFontName The font name.
	 * @param fontSize The font size.
	 */
	void setPlaceholderFont(const char* pFontName, int fontSize);
    
    /**
	 * Set the placeholder's font name.
	 * @param pFontName The font name.
	 */
	void setPlaceholderFontName(const char* pFontName);
    
    /**
	 * Set the placeholder's font size.
	 * @param fontSize The font size.
	 */
	void setPlaceholderFontSize(int fontSize);
    
    /**
     * Set the font color of the placeholder text when the edit box is empty.
     * Not supported on IOS.
     */
    void setPlaceholderFontColor(const ccColor3B& color);
    
    /**
     * Set a text in the edit box that acts as a placeholder when an
     * edit box is empty.
     * @param pText The given text.
     */
    void setPlaceHolder(const char* pText);
    
    /**
     * Get a text in the edit box that acts as a placeholder when an
     * edit box is empty.
     */
    const char* getPlaceHolder(void);
    
    /**
     * Set the input mode of the edit box.
     * @param inputMode One of the EditBoxInputMode constants.
     */
    void setInputMode(EditBoxInputMode inputMode);
    
    /**
     * Sets the maximum input length of the edit box.
     * Setting this value enables multiline input mode by default.
     * Available on Android, iOS and Windows Phone.
     *
     * @param maxLength The maximum length.
     */
    void setMaxLength(int maxLength);
    
    /**
     * Gets the maximum input length of the edit box.
     *
     * @return Maximum input length.
     */
    int getMaxLength();
    
    /**
     * Set the input flags that are to be applied to the edit box.
     * @param inputFlag One of the EditBoxInputFlag constants.
     */
    void setInputFlag(EditBoxInputFlag inputFlag);
    
    /**
     * Set the return type that are to be applied to the edit box.
     * @param returnType One of the KeyboardReturnType constants.
     */
    void setReturnType(KeyboardReturnType returnType);
    
    /* override functions */
    virtual void setPosition(const Point& pos);
    virtual void setVisible(bool visible);
    virtual void setContentSize(const Size& size);
	virtual void setAnchorPoint(const Point& anchorPoint);
    virtual void visit(void);
	virtual void onEnter(void);
    virtual void onExit(void);
    virtual void keyboardWillShow(IMEKeyboardNotificationInfo& info);
    virtual void keyboardDidShow(IMEKeyboardNotificationInfo& info);
    virtual void keyboardWillHide(IMEKeyboardNotificationInfo& info);
    virtual void keyboardDidHide(IMEKeyboardNotificationInfo& info);
    
    /* callback funtions */
    void touchDownAction(Object *sender, ControlEvent controlEvent);
    
protected:
    EditBoxImpl*      _editBoxImpl;
    EditBoxDelegate*  _delegate;
    
    EditBoxInputMode    _editBoxInputMode;
    EditBoxInputFlag    _editBoxInputFlag;
    KeyboardReturnType  _keyboardReturnType;
    
    std::string _text;
    std::string _placeHolder;
    
    std::string _fontName;
    std::string _placeholderFontName;
    
    int _fontSize;
    int _placeholderFontSize;
    
    ccColor3B _colText;
    ccColor3B _colPlaceHolder;
    
    int   _maxLength;
    float _adjustHeight;
    int   _scriptEditBoxHandler;
};

NS_CC_EXT_END

#endif /* __CCEDITTEXT_H__ */

