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

    gtk_init(0, NULL);
    dialog = gtk_dialog_new();
    entry = gtk_entry_new();
    contentArea = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    gtk_container_add(GTK_CONTAINER(contentArea), entry);
    gtk_dialog_add_button(GTK_DIALOG(dialog), "OK", 0);
    gtk_entry_set_text(GTK_ENTRY(entry), entryLine.c_str());

    g_signal_connect(dialog, "focus-out-event", G_CALLBACK(dialogFocusOutCallback), NULL);
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
    while (g_main_context_iteration(NULL, false));
    return didChange;
}

NS_CC_BEGIN

namespace ui {

EditBoxImpl* __createSystemEditBox(EditBox* pEditBox)
{
    return new EditBoxImplLinux(pEditBox);
}

EditBoxImplLinux::EditBoxImplLinux(EditBox* pEditText)
: EditBoxImplCommon(pEditText)
{
    
}

EditBoxImplLinux::~EditBoxImplLinux()
{
	
}

bool EditBoxImplLinux::isEditing()
{
    return false;
}

void EditBoxImplLinux::nativeOpenKeyboard()
{
    std::string text = this->getText();
    bool didChange = LinuxInputBox(text);
    if (didChange)
    {
        this->editBoxEditingDidEnd(text);
    }
}

}

NS_CC_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) */

