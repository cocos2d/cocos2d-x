/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2015 hanxi
 
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

#include "UIEditBoxImpl-linux.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)

#include "UIEditBox.h"
#include "2d/CCLabel.h"
#include "base/ccUTF8.h"
#include <gtk/gtk.h>

// desoty dialog when lost focus
static void dialogFocusOutCallback(GtkWidget* widget, gpointer user_data)
{
    gtk_widget_destroy(widget);
}

bool LinuxInputBox(std::string &entryLine)
{
    bool didChange = false;
    GtkWidget *dialog;
    GtkWidget *entry;
    GtkWidget *contentArea;

    gtk_init(0, nullptr);
    dialog = gtk_dialog_new();
    entry = gtk_entry_new();
    contentArea = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    gtk_container_add(GTK_CONTAINER(contentArea), entry);
    gtk_dialog_add_button(GTK_DIALOG(dialog), "OK", 0);
    gtk_entry_set_text(GTK_ENTRY(entry), entryLine.c_str());

    g_signal_connect(dialog, "focus-out-event", G_CALLBACK(dialogFocusOutCallback), nullptr);
    gtk_window_set_keep_above(GTK_WINDOW(dialog), true);
    gtk_window_set_type_hint(GTK_WINDOW(dialog), GDK_WINDOW_TYPE_HINT_MENU);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_widget_show_all(dialog);

    gint result = gtk_dialog_run(GTK_DIALOG(dialog));
    switch(result)
    {
    case 0:
        entryLine = gtk_entry_get_text(GTK_ENTRY(entry));
        didChange = true;
        break;
    default:
        // CCLOG("Undefined. Perhaps dialog was closed");
        break;
    }

    gtk_widget_destroy(dialog);
    while (g_main_context_iteration(nullptr, false));
    return didChange;
}

NS_CC_BEGIN

namespace ui {

EditBoxImpl* __createSystemEditBox(EditBox* editBox)
{
    return new (std::nothrow) EditBoxImplLinux(editBox);
}

EditBoxImplLinux::EditBoxImplLinux(EditBox* editBox)
: EditBoxImpl(editBox)
, _label(nullptr)
, _labelPlaceHolder(nullptr)
, _editBoxInputMode(EditBox::InputMode::SINGLE_LINE)
, _editBoxInputFlag(EditBox::InputFlag::INTIAL_CAPS_ALL_CHARACTERS)
, _keyboardReturnType(EditBox::KeyboardReturnType::DEFAULT)
, _colText(Color3B::WHITE)
, _colPlaceHolder(Color3B::GRAY)
, _maxLength(-1)
{
    
}

EditBoxImplLinux::~EditBoxImplLinux()
{
	
}

void EditBoxImplLinux::doAnimationWhenKeyboardMove(float duration, float distance)
{ // don't need to be implemented on linux platform.
	
}

static const int CC_EDIT_BOX_PADDING = 5;

bool EditBoxImplLinux::initWithSize(const Size& size)
{
    _label = Label::create();
    _label->setSystemFontSize(size.height-12);
	// align the text vertically center
    _label->setAnchorPoint(Vec2(0, 0.5f));
    _label->setPosition(Vec2(CC_EDIT_BOX_PADDING, size.height / 2.0f));
    _label->setTextColor(_colText);
    _editBox->addChild(_label);
	
    _labelPlaceHolder = Label::create();
    _labelPlaceHolder->setSystemFontSize(size.height-12);
	// align the text vertically center
    _labelPlaceHolder->setAnchorPoint(Vec2(0, 0.5f));
    _labelPlaceHolder->setPosition(CC_EDIT_BOX_PADDING, size.height / 2.0f);
    _labelPlaceHolder->setVisible(false);
    _labelPlaceHolder->setTextColor(_colPlaceHolder);
    _editBox->addChild(_labelPlaceHolder);
    
    _editSize = size;
    return true;
}

void EditBoxImplLinux::setFont(const char* fontName, int fontSize)
{
	if(_label != nullptr) {
        _label->setSystemFontName(fontName);
		_label->setSystemFontSize(fontSize);
	}
	
	if(_labelPlaceHolder != nullptr) {
        _labelPlaceHolder->setSystemFontName(fontName);
		_labelPlaceHolder->setSystemFontSize(fontSize);
	}
}

void EditBoxImplLinux::setFontColor(const Color4B& color)
{
    _colText = color;
    _label->setTextColor(color);
}

void EditBoxImplLinux::setPlaceholderFont(const char* fontName, int fontSize)
{
	if(_labelPlaceHolder != nullptr) {
        _labelPlaceHolder->setSystemFontName(fontName);
		_labelPlaceHolder->setSystemFontSize(fontSize);
	}
}

void EditBoxImplLinux::setPlaceholderFontColor(const Color4B& color)
{
    _colPlaceHolder = color;
    _labelPlaceHolder->setTextColor(color);
}

void EditBoxImplLinux::setInputMode(EditBox::InputMode inputMode)
{
    _editBoxInputMode = inputMode;
}

void EditBoxImplLinux::setMaxLength(int maxLength)
{
    _maxLength = maxLength;
}

int EditBoxImplLinux::getMaxLength()
{
    return _maxLength;
}

void EditBoxImplLinux::setInputFlag(EditBox::InputFlag inputFlag)
{
    _editBoxInputFlag = inputFlag;
}

void EditBoxImplLinux::setReturnType(EditBox::KeyboardReturnType returnType)
{
    _keyboardReturnType = returnType;
}

bool EditBoxImplLinux::isEditing()
{
    return false;
}

void EditBoxImplLinux::setText(const char* text)
{
    if (text != nullptr)
    {
        _text = text;
		
        if (_text.length() > 0)
        {
            _labelPlaceHolder->setVisible(false);
			
            std::string strToShow;
			
            if (EditBox::InputFlag::PASSWORD == _editBoxInputFlag)
            {
                long length = StringUtils::getCharacterCountInUTF8String(_text.c_str());
                for (long i = 0; i < length; i++)
                {
                    strToShow.append("*");
                }
            }
            else
            {
                strToShow = _text;
            }

			_label->setString(strToShow.c_str());

			// Clip the text width to fit to the text box

            float fMaxWidth = _editSize.width - CC_EDIT_BOX_PADDING * 2;
            auto labelSize = _label->getContentSize();
            if(labelSize.width > fMaxWidth) {
                _label->setDimensions(fMaxWidth,labelSize.height);
            }
        }
        else
        {
            _labelPlaceHolder->setVisible(true);
            _label->setString("");
        }
		
    }
}

const char*  EditBoxImplLinux::getText(void)
{
    return _text.c_str();
}

void EditBoxImplLinux::setPlaceHolder(const char* text)
{
    if (text != nullptr)
    {
        _placeHolder = text;
        if (_placeHolder.length() > 0 && _text.length() == 0)
        {
            _labelPlaceHolder->setVisible(true);
        }
		
        _labelPlaceHolder->setString(_placeHolder.c_str());
    }
}

void EditBoxImplLinux::setPosition(const Vec2& pos)
{ // don't need to be implemented on linux platform.
	
}

void EditBoxImplLinux::setVisible(bool visible)
{ // don't need to be implemented on linux platform.

}

void EditBoxImplLinux::setContentSize(const Size& size)
{ // don't need to be implemented on linux platform.
	
}

void EditBoxImplLinux::setAnchorPoint(const Vec2& anchorPoint)
{ // don't need to be implemented on linux platform.
	
}

void EditBoxImplLinux::draw(cocos2d::Renderer *renderer, cocos2d::Mat4 const &transform, uint32_t flags)
{ // don't need to be implemented on linux platform.
    
}

void EditBoxImplLinux::onEnter()
{ // don't need to be implemented on linux platform.
    
}

static void editBoxCallbackFunc(const char* text, void* ctx)
{
    EditBoxImplLinux* thiz = (EditBoxImplLinux*)ctx;
    thiz->setText(text);
	
    if (thiz->getDelegate() != nullptr)
    {
        thiz->getDelegate()->editBoxTextChanged(thiz->getEditBox(), thiz->getText());
        thiz->getDelegate()->editBoxEditingDidEnd(thiz->getEditBox());
        thiz->getDelegate()->editBoxReturn(thiz->getEditBox());
    }
    
#if CC_ENABLE_SCRIPT_BINDING
    EditBox* pEditBox = thiz->getEditBox();
    if (nullptr != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {        
        CommonScriptData data(pEditBox->getScriptEditBoxHandler(), "changed",pEditBox);
        ScriptEvent event(kCommonEvent,(void*)&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
        memset(data.eventName, 0, sizeof(data.eventName));
        strncpy(data.eventName, "ended", sizeof(data.eventName));
        event.data = (void*)&data;
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
        memset(data.eventName, 0, sizeof(data.eventName));
        strncpy(data.eventName, "return", sizeof(data.eventName));
        event.data = (void*)&data;
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#endif
}

void EditBoxImplLinux::openKeyboard()
{
    if (_delegate != nullptr)
    {
        _delegate->editBoxEditingDidBegin(_editBox);
    }
    
#if CC_ENABLE_SCRIPT_BINDING
    EditBox* pEditBox = this->getEditBox();
    if (nullptr != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {        
        CommonScriptData data(pEditBox->getScriptEditBoxHandler(), "began",pEditBox);
        ScriptEvent event(cocos2d::kCommonEvent,(void*)&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#endif
	
    std::string placeHolder = _placeHolder;
    if (_text.length() > 0)
    {
        placeHolder = _text;
    }

    bool didChange = LinuxInputBox(placeHolder);
    if (didChange)
    {
        editBoxCallbackFunc(placeHolder.c_str(), this);
    }
}

void EditBoxImplLinux::closeKeyboard()
{
	
}

}

NS_CC_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) */

