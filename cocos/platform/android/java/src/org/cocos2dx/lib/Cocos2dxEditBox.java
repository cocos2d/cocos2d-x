/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
import android.graphics.Color;
import android.graphics.Typeface;
import android.text.InputFilter;
import android.text.InputType;
import android.text.Spanned;
import android.text.method.PasswordTransformationMethod;
import android.util.Log;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.View;
import android.view.inputmethod.EditorInfo;
import android.widget.EditText;
import android.widget.FrameLayout;

import java.util.ArrayList;
import java.util.List;

public class Cocos2dxEditBox extends EditText {
    /**
     * The user is allowed to enter any text, including line breaks.
     */
    private final int kEditBoxInputModeAny = 0;

    /**
     * The user is allowed to enter an e-mail address.
     */
    private final int kEditBoxInputModeEmailAddr = 1;

    /**
     * The user is allowed to enter an integer value.
     */
    private final int kEditBoxInputModeNumeric = 2;

    /**
     * The user is allowed to enter a phone number.
     */
    private final int kEditBoxInputModePhoneNumber = 3;

    /**
     * The user is allowed to enter a URL.
     */
    private final int kEditBoxInputModeUrl = 4;

    /**
     * The user is allowed to enter a real number value. This extends kEditBoxInputModeNumeric by allowing a decimal point.
     */
    private final int kEditBoxInputModeDecimal = 5;

    /**
     * The user is allowed to enter any text, except for line breaks.
     */
    private final int kEditBoxInputModeSingleLine = 6;

    /**
     * Indicates that the text entered is confidential data that should be obscured whenever possible. This implies EDIT_BOX_INPUT_FLAG_SENSITIVE.
     */
    private final int kEditBoxInputFlagPassword = 0;

    /**
     * Indicates that the text entered is sensitive data that the implementation must never store into a dictionary or table for use in predictive, auto-completing, or other accelerated input schemes. A credit card number is an example of sensitive data.
     */
    private final int kEditBoxInputFlagSensitive = 1;

    /**
     * This flag is a hint to the implementation that during text editing, the initial letter of each word should be capitalized.
     */
    private final int kEditBoxInputFlagInitialCapsWord = 2;

    /**
     * This flag is a hint to the implementation that during text editing, the initial letter of each sentence should be capitalized.
     */
    private final int kEditBoxInputFlagInitialCapsSentence = 3;

    /**
     * Capitalize all characters automatically.
     */
    private final int kEditBoxInputFlagInitialCapsAllCharacters = 4;

    /**
     *  Lowercase all characters automatically.
     */
    private final int kEditBoxInputFlagLowercaseAllCharacters = 5;

    private final int kEditBoxInputRestrictionAlNum = 1 << 2;
    private final int kEditBoxInputRestrictionSpace = 1 << 3;
    private final int kEditBoxInputRestrictionPunct = 1 << 4;

    private final int kKeyboardReturnTypeDefault = 0;
    private final int kKeyboardReturnTypeDone = 1;
    private final int kKeyboardReturnTypeSend = 2;
    private final int kKeyboardReturnTypeSearch = 3;
    private final int kKeyboardReturnTypeGo = 4;
    private final int kKeyboardReturnTypeNext = 5;

    public static final int kEndActionUnknown = 0;
    public static final int kEndActionNext = 1;
    public static final int kEndActionReturn = 3;

    private static final int kTextHorizontalAlignmentLeft = 0;
    private static final int kTextHorizontalAlignmentCenter = 1;
    private static final int kTextHorizontalAlignmentRight = 2;

    private static final int kTextVerticalAlignmentTop = 0;
    private static final int kTextVerticalAlignmentCenter = 1;
    private static final int kTextVerticalAlignmentBottom = 2;

    private int mInputFlagConstraints; 
    private int mInputModeConstraints;

    private int mInputRestrictionConstraints;
    private int mUneditableTextLength;

    private  int mMaxLength;
    private  InputFilter.LengthFilter mLengthFilter;

    public Boolean getChangedTextProgrammatically() {
        return changedTextProgrammatically;
    }

    public void setChangedTextProgrammatically(Boolean changedTextProgrammatically) {
        this.changedTextProgrammatically = changedTextProgrammatically;
    }

    private Boolean changedTextProgrammatically = false;

    //OpenGL view scaleX
    private  float mScaleX;

    // package private
    int endAction = kEndActionUnknown;


    public  Cocos2dxEditBox(Context context){
        super(context);
    }

    public void setEditBoxViewRect(int left, int top, int maxWidth, int maxHeight) {
        FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.WRAP_CONTENT,
                                                                            FrameLayout.LayoutParams.WRAP_CONTENT);
        layoutParams.leftMargin = left;
        layoutParams.topMargin = top;
        layoutParams.width = maxWidth;
        layoutParams.height = maxHeight;
        layoutParams.gravity = Gravity.TOP | Gravity.LEFT;
        this.setLayoutParams(layoutParams);
    }

    public float getOpenGLViewScaleX() {
        return mScaleX;
    }

    public void setOpenGLViewScaleX(float mScaleX) {
        this.mScaleX = mScaleX;
    }


    public  void setMaxLength(int maxLength){
        this.mMaxLength = maxLength;

        this.mLengthFilter = new InputFilter.LengthFilter(this.mMaxLength) {
            @Override
            public CharSequence filter (CharSequence source, int start, int end, Spanned dest, int dstart, int dend) {
                if (source.length() == 1 && source.charAt(start) == '\n') {
                    if (dest.length() == dstart) {
                        return null;
                    } else {
                        return "";
                    }
                }

                return super.filter(source, start, end, dest, dstart, dend);
            }
        };

        InputFilter[] inputFilters = this.getFilters();
        if (inputFilters.length > 0) {
            List<InputFilter> inputFiltersList = new ArrayList<>();
            for (InputFilter inputFilter : inputFilters) {
                inputFiltersList.add(inputFilter);
            }
            inputFiltersList.add(this.mLengthFilter);

            this.setFilters(inputFiltersList.toArray(new InputFilter[inputFiltersList.size()]));
        } else {
            this.setFilters(new InputFilter[]{this.mLengthFilter});
        }
    }

    public void setMultilineEnabled(boolean flag){
        this.mInputModeConstraints |= InputType.TYPE_TEXT_FLAG_MULTI_LINE;
    }

    public boolean getMultilineEnabled()
    {
        return  ((this.mInputModeConstraints & InputType.TYPE_TEXT_FLAG_MULTI_LINE) == InputType.TYPE_TEXT_FLAG_MULTI_LINE);
    }

    public void setReturnType(int returnType) {
        switch (returnType) {
            case kKeyboardReturnTypeDefault:
                this.setImeOptions(EditorInfo.IME_ACTION_NONE | EditorInfo.IME_FLAG_NO_EXTRACT_UI);
                break;
            case kKeyboardReturnTypeDone:
                this.setImeOptions(EditorInfo.IME_ACTION_DONE | EditorInfo.IME_FLAG_NO_EXTRACT_UI);
                break;
            case kKeyboardReturnTypeSend:
                this.setImeOptions(EditorInfo.IME_ACTION_SEND | EditorInfo.IME_FLAG_NO_EXTRACT_UI);
                break;
            case kKeyboardReturnTypeSearch:
                this.setImeOptions(EditorInfo.IME_ACTION_SEARCH | EditorInfo.IME_FLAG_NO_EXTRACT_UI);
                break;
            case kKeyboardReturnTypeGo:
                this.setImeOptions(EditorInfo.IME_ACTION_GO | EditorInfo.IME_FLAG_NO_EXTRACT_UI);
                break;
            case kKeyboardReturnTypeNext:
                this.setImeOptions(EditorInfo.IME_ACTION_NEXT | EditorInfo.IME_FLAG_NO_EXTRACT_UI);
                break;
            default:
                this.setImeOptions(EditorInfo.IME_ACTION_NONE | EditorInfo.IME_FLAG_NO_EXTRACT_UI);
                break;
        }
    }

    public void setTextHorizontalAlignment(int alignment) {
        int gravity = this.getGravity();
        switch (alignment) {
            case kTextHorizontalAlignmentLeft:
                gravity = (gravity & ~Gravity.RIGHT) | Gravity.LEFT ;
                break;
            case kTextHorizontalAlignmentCenter:
                gravity =(gravity & ~Gravity.RIGHT & ~Gravity.LEFT) | Gravity.CENTER_HORIZONTAL;
                break;
            case kTextHorizontalAlignmentRight:
                gravity = (gravity & ~Gravity.LEFT) | Gravity.RIGHT ;
                break;
            default:
                gravity = (gravity & ~Gravity.RIGHT) | Gravity.LEFT ;
                break;
        }
        this.setGravity(gravity);
    }
    
    public void setTextVerticalAlignment(int alignment) {
        int gravity = this.getGravity();
        int padding = Cocos2dxEditBoxHelper.getPadding(mScaleX);
        switch (alignment) {
            case kTextVerticalAlignmentTop:
                setPadding(padding, padding*3/4, 0, 0);
                gravity = (gravity & ~Gravity.BOTTOM) | Gravity.TOP ;
                break;
            case kTextVerticalAlignmentCenter:
                setPadding(padding, 0, 0, padding/2);
                gravity =(gravity & ~Gravity.TOP & ~Gravity.BOTTOM) | Gravity.CENTER_VERTICAL;
                break;
            case kTextVerticalAlignmentBottom:
                //TODO: Add appropriate padding when this alignment is used
                gravity = (gravity & ~Gravity.TOP) | Gravity.BOTTOM ;
                break;
            default:
                setPadding(padding, 0, 0, padding/2);
                gravity =(gravity & ~Gravity.TOP & ~Gravity.BOTTOM) | Gravity.CENTER_VERTICAL;
                break;
        }

        this.setGravity(gravity);
    }

    public  void setInputMode(int inputMode){
        this.setTextHorizontalAlignment(kTextHorizontalAlignmentLeft);
        this.setTextVerticalAlignment(kTextVerticalAlignmentCenter);
        switch (inputMode) {
            case kEditBoxInputModeAny:
                this.setTextVerticalAlignment(kTextVerticalAlignmentTop);
                this.mInputModeConstraints = InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_FLAG_MULTI_LINE;
                break;
            case kEditBoxInputModeEmailAddr:
                this.mInputModeConstraints = InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_EMAIL_ADDRESS;
                break;
            case kEditBoxInputModeNumeric:
                this.mInputModeConstraints = InputType.TYPE_CLASS_NUMBER | InputType.TYPE_NUMBER_FLAG_SIGNED;
                break;
            case kEditBoxInputModePhoneNumber:
                this.mInputModeConstraints = InputType.TYPE_CLASS_PHONE;
                break;
            case kEditBoxInputModeUrl:
                this.mInputModeConstraints = InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_URI;
                break;
            case kEditBoxInputModeDecimal:
                this.mInputModeConstraints = InputType.TYPE_CLASS_NUMBER | InputType.TYPE_NUMBER_FLAG_DECIMAL | InputType.TYPE_NUMBER_FLAG_SIGNED;
                break;
            case kEditBoxInputModeSingleLine:
                this.mInputModeConstraints = InputType.TYPE_CLASS_TEXT;
                break;
            default:

                break;
        }

        this.setInputType(this.mInputModeConstraints | this.mInputFlagConstraints);
    }

    private boolean IsPunctuationCharacter(char c) {
        if (c == '\n')
            return true;

        int charType = Character.getType(c);
        switch (charType) {
            case Character.DASH_PUNCTUATION:
            case Character.START_PUNCTUATION:
            case Character.END_PUNCTUATION:
            case Character.CONNECTOR_PUNCTUATION:
            case Character.INITIAL_QUOTE_PUNCTUATION:
            case Character.FINAL_QUOTE_PUNCTUATION:
            case Character.OTHER_PUNCTUATION:
                return true;
            default:
                return false;
        }
    }

    public void setInputRestriction(int inputRestriction) {
        this.mInputRestrictionConstraints = inputRestriction;

        final boolean alNumRestriction = (this.mInputRestrictionConstraints & kEditBoxInputRestrictionAlNum) == kEditBoxInputRestrictionAlNum;
        final boolean spaceRestriction = (this.mInputRestrictionConstraints & kEditBoxInputRestrictionSpace) == kEditBoxInputRestrictionSpace;
        final boolean punctRestriction = (this.mInputRestrictionConstraints & kEditBoxInputRestrictionPunct) == kEditBoxInputRestrictionPunct;
        if (alNumRestriction || spaceRestriction || punctRestriction) {
            InputFilter filter = new InputFilter() {
                @Override
                public CharSequence filter(CharSequence source, int start, int end, Spanned dest, int dstart, int dend) {
                    for (int i = start; i < end; i++) {
                        // If the character is valid, let's continue checking the next one
                        // but if its invalid let's return ending the check
                        char c = source.charAt(i);
                        if ((alNumRestriction && Character.isLetterOrDigit(c)) ||
                            (spaceRestriction && Character.isSpaceChar(c)) ||
                            (punctRestriction && IsPunctuationCharacter(c))) {
                            continue;
                        }

                        return "";
                    }

                    return null; // Valid!
                }
            };

            InputFilter[] inputFilters = this.getFilters();
            if (inputFilters.length > 0) {
                List<InputFilter> inputFiltersList = new ArrayList<>();
                for (InputFilter inputFilter : inputFilters) {
                    inputFiltersList.add(inputFilter);
                }
                inputFiltersList.add(filter);

                this.setFilters(inputFiltersList.toArray(new InputFilter[inputFiltersList.size()]));
            } else {
                this.setFilters(new InputFilter[] { filter });
            }
        }
    }

    public void setUneditableTextLength(int uneditableTextLength) {
        this.mUneditableTextLength = uneditableTextLength;

        InputFilter filter = new InputFilter() {
            @Override
            public CharSequence filter(CharSequence source, int start, int end, Spanned dest, int dstart, int dend) {
                if (dstart < Cocos2dxEditBox.this.mUneditableTextLength) {
                    return dest.subSequence(dstart, dend);
                }

                return null;
            }
        };

        InputFilter[] inputFilters = this.getFilters();
        if (inputFilters.length > 0) {
            List<InputFilter> inputFiltersList = new ArrayList<>();
            for (InputFilter inputFilter : inputFilters) {
                inputFiltersList.add(inputFilter);
            }
            inputFiltersList.add(filter);

            this.setFilters(inputFiltersList.toArray(new InputFilter[inputFiltersList.size()]));
        } else {
            this.setFilters(new InputFilter[] { filter });
        }
    }

    @Override
    public boolean onKeyDown(final int pKeyCode, final KeyEvent pKeyEvent) {
        switch (pKeyCode) {
            case KeyEvent.KEYCODE_BACK:
                Cocos2dxActivity activity = (Cocos2dxActivity)this.getContext();
                //To prevent program from going to background
                activity.getGLSurfaceView().requestFocus();
                return true;
            default:
                return super.onKeyDown(pKeyCode, pKeyEvent);
        }
    }

    @Override
    public boolean onKeyPreIme(int keyCode, KeyEvent event) {
        return super.onKeyPreIme(keyCode, event);
    }

    public void setInputFlag(int inputFlag) {

        switch (inputFlag) {
            case kEditBoxInputFlagPassword:
                this.mInputFlagConstraints = InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_PASSWORD;
                this.setTypeface(Typeface.DEFAULT);
                this.setTransformationMethod(new PasswordTransformationMethod());
                break;
            case kEditBoxInputFlagSensitive:
                this.mInputFlagConstraints = InputType.TYPE_TEXT_FLAG_NO_SUGGESTIONS;
                break;
            case kEditBoxInputFlagInitialCapsWord:
                this.mInputFlagConstraints = InputType.TYPE_TEXT_FLAG_CAP_WORDS;
                break;
            case kEditBoxInputFlagInitialCapsSentence:
                this.mInputFlagConstraints = InputType.TYPE_TEXT_FLAG_CAP_SENTENCES;
                break;
            case kEditBoxInputFlagInitialCapsAllCharacters:
                this.mInputFlagConstraints = InputType.TYPE_TEXT_FLAG_CAP_CHARACTERS;
                break;
            case kEditBoxInputFlagLowercaseAllCharacters:
                this.mInputFlagConstraints = InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_NORMAL;
                break;
            default:
                break;
        }

        this.setInputType(this.mInputFlagConstraints | this.mInputModeConstraints);
    }
}
