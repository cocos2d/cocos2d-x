/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

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
package org.cocos2dx.js_tests;

import org.cocos2dx.js_tests.R;
import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.cocos2dx.lib.Cocos2dxJavascriptJavaBridge;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;

public class AppActivity extends Cocos2dxActivity {
    
    private static AppActivity app = null;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        app = this;
    }

    @Override
    public Cocos2dxGLSurfaceView onCreateView() {
        Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
        // TestCpp should create stencil buffer
        glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
        
        return glSurfaceView;
    }
    
    public static void showAlertDialog(final String title, final String message) {
        app.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                AlertDialog alertDialog = new AlertDialog.Builder(app).create();
                alertDialog.setTitle(title);
                alertDialog.setMessage(message);
                alertDialog.setCancelable(true);
                alertDialog.setIcon(R.drawable.icon);
                alertDialog.setButton("OK", new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int which) {
                        app.runOnGLThread(new Runnable() {
                            @Override
                            public void run() {

                                Cocos2dxJavascriptJavaBridge.evalString("cc.log(\"Javascript Java bridge!\")");
                            }
                        });
                    }
                });
                alertDialog.show();
            }
        });
    }
    public static void showAlertDialog(final String title, final String message, final boolean logicSwitch) {
        app.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                AlertDialog alertDialog = new AlertDialog.Builder(app).create();
                alertDialog.setTitle(title);
                alertDialog.setMessage(message);
                alertDialog.setCancelable(true);
                alertDialog.setIcon(R.drawable.icon);
                String buttonStr = "it's false";
                if (logicSwitch)
                {
                	buttonStr = "it's true";
                }
                alertDialog.setButton(buttonStr, new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int which) {
                        app.runOnGLThread(new Runnable() {
                            @Override
                            public void run() {

                                Cocos2dxJavascriptJavaBridge.evalString("cc.log(\"Javascript Java bridge!\")");
                            }
                        });
                    }
                });
                alertDialog.show();
            }
        });
    }

    public static String getUtfStr() {
        final String utf8Str = "you will see emotion:💝";
        app.runOnGLThread(new Runnable() {
            @Override
            public void run() {

                Cocos2dxJavascriptJavaBridge.evalString("cc.log(\"" + utf8Str + "\")");
            }
        });
        return utf8Str;
    }

}
