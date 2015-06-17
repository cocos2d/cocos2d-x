/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

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

package org.cocos2dx.lib;

import java.lang.ref.WeakReference;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Handler;
import android.os.Message;

public class Cocos2dxHandler extends Handler {
    // ===========================================================
    // Constants
    // ===========================================================
    public final static int HANDLER_SHOW_DIALOG = 1;
    public final static int HANDLER_SHOW_EDITBOX_DIALOG = 2;
    
    // ===========================================================
    // Fields
    // ===========================================================
    private WeakReference<Cocos2dxActivity> mActivity;
    
    // ===========================================================
    // Constructors
    // ===========================================================
    public Cocos2dxHandler(Cocos2dxActivity activity) {
        this.mActivity = new WeakReference<Cocos2dxActivity>(activity);
    }

    // ===========================================================
    // Getter & Setter
    // ===========================================================

    // ===========================================================
    // Methods for/from SuperClass/Interfaces
    // ===========================================================
    
    // ===========================================================
    // Methods
    // ===========================================================

    public void handleMessage(Message msg) {
        switch (msg.what) {
        case Cocos2dxHandler.HANDLER_SHOW_DIALOG:
            showDialog(msg);
            break;
        case Cocos2dxHandler.HANDLER_SHOW_EDITBOX_DIALOG:
            showEditBoxDialog(msg);
            break;
        }
    }
    
    private void showDialog(Message msg) {
        Cocos2dxActivity theActivity = this.mActivity.get();
        DialogMessage dialogMessage = (DialogMessage)msg.obj;
        new AlertDialog.Builder(theActivity)
        .setTitle(dialogMessage.titile)
        .setMessage(dialogMessage.message)
        .setPositiveButton("Ok", 
                new DialogInterface.OnClickListener() {
                    
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        // TODO Auto-generated method stub
                        
                    }
                }).create().show();
    }
    
    private void showEditBoxDialog(Message msg) {
        EditBoxMessage editBoxMessage = (EditBoxMessage)msg.obj;
        new Cocos2dxEditBoxDialog(this.mActivity.get(),
                editBoxMessage.title,
                editBoxMessage.content,
                editBoxMessage.inputMode,
                editBoxMessage.inputFlag,
                editBoxMessage.returnType,
                editBoxMessage.maxLength).show();
    }
    
    // ===========================================================
    // Inner and Anonymous Classes
    // ===========================================================
    
    public static class DialogMessage {
        public String titile;
        public String message;
        
        public DialogMessage(String title, String message) {
            this.titile = title;
            this.message = message;
        }
    }
    
    public static class EditBoxMessage {
        public String title;
        public String content;
        public int inputMode;
        public int inputFlag;
        public int returnType;
        public int maxLength;
        
        public EditBoxMessage(String title, String content, int inputMode, int inputFlag, int returnType, int maxLength){
            this.content = content;
            this.title = title;
            this.inputMode = inputMode;
            this.inputFlag = inputFlag;
            this.returnType = returnType;
            this.maxLength = maxLength;
        }
    }
}
