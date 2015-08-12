/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2015 Chukong Technologies Inc.

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

import android.content.Context;
import android.content.res.Resources;
import android.graphics.Color;
import android.graphics.Typeface;
import android.text.Editable;
import android.text.InputType;
import android.text.TextWatcher;
import android.util.Log;
import android.util.SparseArray;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.View;
import android.view.inputmethod.EditorInfo;
import android.view.inputmethod.InputMethodManager;
import android.widget.FrameLayout;
import android.widget.TextView;


public class Cocos2dxEditBoxHelper {
    private static final String TAG = Cocos2dxEditBoxHelper.class.getSimpleName();
    private static Cocos2dxActivity mCocos2dxActivity;
    private static ResizeLayout mFrameLayout;

    private static SparseArray<Cocos2dxEditBox> mEditBoxArray;
    private static int mViewTag = 0;

    //Call native methods
    private static native void editBoxEditingDidBegin(int index);
    public static void __editBoxEditingDidBegin(int index){
        editBoxEditingDidBegin(index);
    }

    private static native void editBoxEditingChanged(int index, String text);
    public static void __editBoxEditingChanged(int index, String text){
        editBoxEditingChanged(index, text);
    }

    private static native void editBoxEditingDidEnd(int index, String text);
    public static void __editBoxEditingDidEnd(int index, String text){
        editBoxEditingDidEnd(index, text);
    }


    public Cocos2dxEditBoxHelper(ResizeLayout layout) {
        Cocos2dxEditBoxHelper.mFrameLayout = layout;

        Cocos2dxEditBoxHelper.mCocos2dxActivity = (Cocos2dxActivity) Cocos2dxActivity.getContext();
        Cocos2dxEditBoxHelper.mEditBoxArray = new SparseArray<Cocos2dxEditBox>();
    }


    public static int createEditBox(final int left, final int top, final int width, final int height) {
        final int index = mViewTag;
        mCocos2dxActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                final Cocos2dxEditBox editBox = new Cocos2dxEditBox(mCocos2dxActivity);
                editBox.setFocusable(true);
                editBox.setFocusableInTouchMode(true);
                editBox.setInputFlag(4); //kEditBoxInputFlagInitialCapsAllCharacters
                editBox.setInputMode(6); //kEditBoxInputModeSingleLine
                editBox.setReturnType(0);  //kKeyboardReturnTypeDefault
                editBox.setHintTextColor(Color.GRAY);
                editBox.setVisibility(View.INVISIBLE);
                editBox.setBackgroundColor(Color.TRANSPARENT);
                editBox.setTextColor(Color.WHITE);
                editBox.setSingleLine();


                FrameLayout.LayoutParams lParams = new FrameLayout.LayoutParams(
                        FrameLayout.LayoutParams.WRAP_CONTENT,
                        FrameLayout.LayoutParams.WRAP_CONTENT);

                lParams.leftMargin = left;
                lParams.topMargin = top;
                lParams.width = width;
                lParams.height = height+20;
                lParams.gravity = Gravity.TOP | Gravity.LEFT;

                mFrameLayout.addView(editBox, lParams);

                editBox.addTextChangedListener(new TextWatcher() {
                    @Override
                    public void beforeTextChanged(CharSequence s, int start, int count, int after) {
                    }

                    @Override
                    public void onTextChanged(final CharSequence s, int start, int before, int count) {
                        //The optimization can't be turn on due to unknown keyboard hide in some custom keyboard
//                        mFrameLayout.setEnableForceDoLayout(false);

                        mCocos2dxActivity.runOnGLThread(new Runnable() {
                            @Override
                            public void run() {
                                Cocos2dxEditBoxHelper.__editBoxEditingChanged(index, s.toString());
                            }
                        });
                    }

                    @Override
                    public void afterTextChanged(Editable s) {

                    }
                });


                editBox.setOnFocusChangeListener(new View.OnFocusChangeListener() {

                    @Override
                    public void onFocusChange(View v, boolean hasFocus) {
                        if (hasFocus) {
                            mCocos2dxActivity.runOnGLThread(new Runnable() {
                                @Override
                                public void run() {
                                    Cocos2dxEditBoxHelper.__editBoxEditingDidBegin(index);
                                }
                            });
                            editBox.setSelection(editBox.getText().length());
                            mFrameLayout.setEnableForceDoLayout(true);
                            mCocos2dxActivity.getGLSurfaceView().setSoftKeyboardShown(true);
                            Log.d(TAG, "edit box get focus");
                        } else {
                            editBox.setVisibility(View.GONE);
                            mCocos2dxActivity.runOnGLThread(new Runnable() {
                                @Override
                                public void run() {
                                    Cocos2dxEditBoxHelper.__editBoxEditingDidEnd(index, editBox.getText().toString());
                                }
                            });
                            mFrameLayout.setEnableForceDoLayout(false);
                            Log.d(TAG, "edit box lose focus");
                        }
                    }
                });

                editBox.setOnKeyListener(new View.OnKeyListener() {
                    public boolean onKey(View v, int keyCode, KeyEvent event) {
                        // If the event is a key-down event on the "enter" button
                        if ((event.getAction() == KeyEvent.ACTION_DOWN) &&
                                (keyCode == KeyEvent.KEYCODE_ENTER)) {
                            //if editbox doesn't support multiline, just hide the keyboard
                            if ((editBox.getInputType() & InputType.TYPE_TEXT_FLAG_MULTI_LINE) != InputType.TYPE_TEXT_FLAG_MULTI_LINE) {
                                Cocos2dxEditBoxHelper.closeKeyboard(index);
                                mCocos2dxActivity.getGLSurfaceView().requestFocus();
                                return true;
                            }
                        }
                        return false;
                    }
                });


                editBox.setOnEditorActionListener(new TextView.OnEditorActionListener() {
                    @Override
                    public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
                        if (actionId == EditorInfo.IME_ACTION_DONE) {
                            Cocos2dxEditBoxHelper.closeKeyboard(index);
                            mCocos2dxActivity.getGLSurfaceView().requestFocus();
                        }
                        return false;
                    }
                });

                mEditBoxArray.put(index, editBox);
            }
        });
        return mViewTag++;
    }

    public static void removeEditBox(final int index) {
        mCocos2dxActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Cocos2dxEditBox editBox = mEditBoxArray.get(index);
                if (editBox != null) {
                    mEditBoxArray.remove(index);
                    mFrameLayout.removeView(editBox);
                    Log.e(TAG, "remove EditBox");
                }
            }
        });
    }

    public static void setFont(final int index, final String fontName, final float fontSize){
        mCocos2dxActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Cocos2dxEditBox editBox = mEditBoxArray.get(index);
                if (editBox != null) {
                    Typeface tf;
                    if (!fontName.isEmpty()) {
                        tf  =  Typeface.create(fontName, Typeface.NORMAL);
                    }else{
                        tf = Typeface.DEFAULT;
                    }
                    //TODO: The font size is not the same across all the anroid devices...
                    if (fontSize >= 0){
                        editBox.setTextSize(TypedValue.COMPLEX_UNIT_SP, fontSize);
                    }
                    editBox.setTypeface(tf);
                }
            }
        });
    }

    public static void setFontColor(final int index, final int red, final int green, final int blue, final int alpha){
        mCocos2dxActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Cocos2dxEditBox editBox = mEditBoxArray.get(index);
                if (editBox != null) {
                    editBox.setTextColor(Color.argb(alpha, red, green, blue));
                }
            }
        });
    }

    public static void setPlaceHolderText(final int index, final String text){
        mCocos2dxActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Cocos2dxEditBox editBox = mEditBoxArray.get(index);
                if (editBox != null) {
                    editBox.setHint(text);
                }
            }
        });
    }

    public static void setPlaceHolderTextColor(final int index, final int red, final int green, final int blue, final int alpha){
        mCocos2dxActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Cocos2dxEditBox editBox = mEditBoxArray.get(index);
                if (editBox != null) {
                    editBox.setHintTextColor(Color.argb(alpha, red, green, blue));
                }
            }
        });
    }

    public static void setMaxLength(final int index, final int maxLength) {
        mCocos2dxActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Cocos2dxEditBox editBox = mEditBoxArray.get(index);
                if (editBox != null) {
                    editBox.setMaxLength(maxLength);
                }
            }
        });
    }

    public static void setVisible(final int index, final boolean visible) {
        mCocos2dxActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Cocos2dxEditBox editBox = mEditBoxArray.get(index);
                if (editBox != null) {
                    editBox.setVisibility(visible ? View.VISIBLE : View.GONE);
                    if (visible) {
                        editBox.requestFocus();
                        Cocos2dxEditBoxHelper.openKeyboard(index);
                    }else{
                        mCocos2dxActivity.getGLSurfaceView().requestFocus();
                        Cocos2dxEditBoxHelper.closeKeyboard(index);
                    }
                }
            }
        });
    }


    public static void setText(final int index, final String text){
        mCocos2dxActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Cocos2dxEditBox editBox = mEditBoxArray.get(index);
                if (editBox != null) {
                    editBox.setText(text);
                }
            }
        });
    }

    public static void setReturnType(final int index, final int returnType) {
        mCocos2dxActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Cocos2dxEditBox editBox = mEditBoxArray.get(index);
                if (editBox != null) {
                    editBox.setReturnType(returnType);
                }
            }
        });
    }

    public static void setInputMode(final int index, final int inputMode) {
        mCocos2dxActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Cocos2dxEditBox editBox = mEditBoxArray.get(index);
                if (editBox != null) {
                    editBox.setInputMode(inputMode);
                }
            }
        });
    }

    public static void setInputFlag(final int index, final int inputFlag) {
        mCocos2dxActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Cocos2dxEditBox editBox = mEditBoxArray.get(index);
                if (editBox != null) {
                    editBox.setInputFlag(inputFlag);
                }
            }
        });
    }


    public static void setEditBoxViewRect(final int index, final int left, final int top, final int maxWidth, final int maxHeight) {
        mCocos2dxActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Cocos2dxEditBox editBox = mEditBoxArray.get(index);
                if (editBox != null) {
                    editBox.setEditBoxViewRect(left, top, maxWidth, maxHeight);
                }
            }
        });
    }



    public static void openKeyboard(int index) {
        final InputMethodManager imm = (InputMethodManager) mCocos2dxActivity.getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
        Cocos2dxEditBox editBox = mEditBoxArray.get(index);
        if (null != editBox) {
            imm.showSoftInput(editBox, 0);
            mCocos2dxActivity.getGLSurfaceView().setSoftKeyboardShown(true);
        }
    }

    public static void closeKeyboard(int index) {
        final InputMethodManager imm = (InputMethodManager) mCocos2dxActivity.getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
        Cocos2dxEditBox editBox = mEditBoxArray.get(index);
        if (null != editBox) {
            imm.hideSoftInputFromWindow(editBox.getWindowToken(), 0);
            mCocos2dxActivity.getGLSurfaceView().setSoftKeyboardShown(false);
        }
    }
}
