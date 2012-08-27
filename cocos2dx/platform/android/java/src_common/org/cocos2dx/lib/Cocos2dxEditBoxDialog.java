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

package org.cocos2dx.lib;

import android.app.Dialog;
import android.content.Context;
import android.graphics.drawable.ColorDrawable;
import android.os.Bundle;
import android.os.Handler;
import android.text.InputFilter;
import android.text.InputType;
import android.util.Log;
import android.util.TypedValue;
import android.view.KeyEvent;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.view.inputmethod.EditorInfo;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.TextView.OnEditorActionListener;

public class Cocos2dxEditBoxDialog extends Dialog {

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
     * The user is allowed to enter a real number value.
     * This extends kEditBoxInputModeNumeric by allowing a decimal point.
     */
	private final int kEditBoxInputModeDecimal = 5;

    /**
     * The user is allowed to enter any text, except for line breaks.
     */
	private final int kEditBoxInputModeSingleLine = 6;


    /**
     * Indicates that the text entered is confidential data that should be
     * obscured whenever possible. This implies EDIT_BOX_INPUT_FLAG_SENSITIVE.
     */
    private final int kEditBoxInputFlagPassword = 0;

    /**
     * Indicates that the text entered is sensitive data that the
     * implementation must never store into a dictionary or table for use
     * in predictive, auto-completing, or other accelerated input schemes.
     * A credit card number is an example of sensitive data.
     */
    private final int kEditBoxInputFlagSensitive = 1;

    /**
     * This flag is a hint to the implementation that during text editing,
     * the initial letter of each word should be capitalized.
     */
    private final int kEditBoxInputFlagInitialCapsWord = 2;

    /**
     * This flag is a hint to the implementation that during text editing,
     * the initial letter of each sentence should be capitalized.
     */
    private final int kEditBoxInputFlagInitialCapsSentence = 3;

    /**
     * Capitalize all characters automatically.
     */
    private final int kEditBoxInputFlagInitialCapsAllCharacters = 4;
	
    private final int kKeyboardReturnTypeDefault = 0;
    private final int kKeyboardReturnTypeDone = 1;
    private final int kKeyboardReturnTypeSend = 2;
    private final int kKeyboardReturnTypeSearch = 3;
    private final int kKeyboardReturnTypeGo = 4;

	//
	private EditText mInputEditText = null;
	private TextView mTextViewTitle = null;
	private int mInputMode = 0;
	private int mInputFlag = 0;
	private int mReturnType = 0;
	private int mMaxLength = -1;
	
	private int mInputFlagConstraints = 0x00000;
	private int mInputModeContraints = 0x00000;
	private boolean mIsMultiline = false;
	private Cocos2dxActivity mParentActivity = null;
	private EditBoxMessage mMsg = null;
	
	public Cocos2dxEditBoxDialog(Context context, EditBoxMessage msg) {
		//super(context, R.style.Theme_Translucent);
		super(context, android.R.style.Theme_Translucent_NoTitleBar_Fullscreen);
		// TODO Auto-generated constructor stub
		mParentActivity = (Cocos2dxActivity)context;
		mMsg = msg;
	}
	
	// Converting dips to pixels
	private int convertDipsToPixels(float dips)
	{
		float scale = getContext().getResources().getDisplayMetrics().density;
		return Math.round(dips * scale);
	}
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		
		getWindow().setBackgroundDrawable(new ColorDrawable(0x80000000));

		LinearLayout layout = new LinearLayout(mParentActivity);
		layout.setOrientation(LinearLayout.VERTICAL);
		
		LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(ViewGroup.
        		LayoutParams.FILL_PARENT,ViewGroup.LayoutParams.FILL_PARENT);
		
		mTextViewTitle = new TextView(mParentActivity);
		LinearLayout.LayoutParams textviewParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT,
		      ViewGroup.LayoutParams.WRAP_CONTENT);
		textviewParams.leftMargin = textviewParams.rightMargin = convertDipsToPixels(10);
		mTextViewTitle.setTextSize(TypedValue.COMPLEX_UNIT_DIP, 20);
		layout.addView(mTextViewTitle, textviewParams);

		mInputEditText = new EditText(mParentActivity);
		LinearLayout.LayoutParams editTextParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.FILL_PARENT,
		      ViewGroup.LayoutParams.WRAP_CONTENT);
		editTextParams.leftMargin = editTextParams.rightMargin = convertDipsToPixels(10);
		
		layout.addView(mInputEditText, editTextParams);
		
		setContentView(layout, layoutParams);
		
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
        
		mInputMode = mMsg.inputMode;
		mInputFlag = mMsg.inputFlag;
		mReturnType = mMsg.returnType;
		mMaxLength = mMsg.maxLength;

		mTextViewTitle.setText(mMsg.title);
		mInputEditText.setText(mMsg.content);
		
		int oldImeOptions = mInputEditText.getImeOptions();
		mInputEditText.setImeOptions(oldImeOptions | EditorInfo.IME_FLAG_NO_EXTRACT_UI);
		oldImeOptions = mInputEditText.getImeOptions();
		
	    switch (mInputMode)
	    {
	    	case kEditBoxInputModeAny:
	    		mInputModeContraints =
				InputType.TYPE_CLASS_TEXT |
				InputType.TYPE_TEXT_FLAG_MULTI_LINE;
	    		break;
	        case kEditBoxInputModeEmailAddr:
	        	mInputModeContraints =
				InputType.TYPE_CLASS_TEXT |
				InputType.TYPE_TEXT_VARIATION_EMAIL_ADDRESS;
	            break;
	        case kEditBoxInputModeNumeric:
	        	mInputModeContraints =
				InputType.TYPE_CLASS_NUMBER |
				InputType.TYPE_NUMBER_FLAG_SIGNED;
	            break;
	        case kEditBoxInputModePhoneNumber:
	        	mInputModeContraints = InputType.TYPE_CLASS_PHONE;
	            break;
	        case kEditBoxInputModeUrl:
	        	mInputModeContraints =
				InputType.TYPE_CLASS_TEXT |
				InputType.TYPE_TEXT_VARIATION_URI;
	            break;
	        case kEditBoxInputModeDecimal:
	        	mInputModeContraints =
				InputType.TYPE_CLASS_NUMBER |
				InputType.TYPE_NUMBER_FLAG_DECIMAL |
				InputType.TYPE_NUMBER_FLAG_SIGNED;
	            break;
	        case kEditBoxInputModeSingleLine:
	        	mInputModeContraints = InputType.TYPE_CLASS_TEXT;
	            break;
	        default:

	            break;
	    }
	    
	    if ( mIsMultiline ) {
			mInputModeContraints |= InputType.TYPE_TEXT_FLAG_MULTI_LINE;
	    }
	    
	    mInputEditText.setInputType(mInputModeContraints | mInputFlagConstraints);
		
	    switch (mInputFlag)
	    {
	        case kEditBoxInputFlagPassword:
	        	mInputFlagConstraints = InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_PASSWORD;
	            break;
	        case kEditBoxInputFlagSensitive:
	        	mInputFlagConstraints = InputType.TYPE_TEXT_FLAG_NO_SUGGESTIONS;
	        	break;
	        case kEditBoxInputFlagInitialCapsWord:
	        	mInputFlagConstraints = InputType.TYPE_TEXT_FLAG_CAP_WORDS;
	            break;
	        case kEditBoxInputFlagInitialCapsSentence:
	        	mInputFlagConstraints = InputType.TYPE_TEXT_FLAG_CAP_SENTENCES;
	            break;
	        case kEditBoxInputFlagInitialCapsAllCharacters:
	        	mInputFlagConstraints = InputType.TYPE_TEXT_FLAG_CAP_CHARACTERS;
	            break;
	        default:
	            break;
	    }
	    mInputEditText.setInputType(mInputFlagConstraints | mInputModeContraints);
	    
	    switch (mReturnType) {
	        case kKeyboardReturnTypeDefault:
	        	mInputEditText.setImeOptions(oldImeOptions | EditorInfo.IME_ACTION_NONE);
	            break;
	        case kKeyboardReturnTypeDone:
	        	mInputEditText.setImeOptions(oldImeOptions | EditorInfo.IME_ACTION_DONE);
	            break;
	        case kKeyboardReturnTypeSend:
	        	mInputEditText.setImeOptions(oldImeOptions | EditorInfo.IME_ACTION_SEND);
	            break;
	        case kKeyboardReturnTypeSearch:
	        	mInputEditText.setImeOptions(oldImeOptions | EditorInfo.IME_ACTION_SEARCH);
	            break;
	        case kKeyboardReturnTypeGo:
	        	mInputEditText.setImeOptions(oldImeOptions | EditorInfo.IME_ACTION_GO);
	            break;
	        default:
	        	mInputEditText.setImeOptions(oldImeOptions | EditorInfo.IME_ACTION_NONE);
	            break;
    	}
	    
	    if (mMaxLength > 0) {
			mInputEditText.setFilters(
					new InputFilter[] {
							new InputFilter.LengthFilter(mMaxLength)
							}
					);
	    }
	    
		Handler initHandler = new Handler();
		initHandler.postDelayed(new Runnable() {
			public void run() {
				mInputEditText.requestFocus();
				mInputEditText.setSelection(mInputEditText.length());
				openKeyboard();
			}
		}, 200);
		 
		mInputEditText.setOnEditorActionListener(new OnEditorActionListener() {
		     @Override
		     public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
	        	 // if user didn't set keyboard type,
	        	 // this callback will be invoked twice with 'KeyEvent.ACTION_DOWN' and 'KeyEvent.ACTION_UP'
	        	 if (actionId != EditorInfo.IME_NULL
	        			 || (actionId == EditorInfo.IME_NULL
	        			 	&& event != null
	        			 	&& event.getAction() == KeyEvent.ACTION_DOWN))
	        	 {
	        		 //Log.d("EditBox", "actionId: "+actionId +",event: "+event);
	            	 mParentActivity.setEditBoxResult(mInputEditText.getText().toString());
	            	 closeKeyboard();
	            	 dismiss();
					 return true;
	        	 }
		         return false;
		     }
		 });
	}

	private void openKeyboard() {
		InputMethodManager imm = (InputMethodManager) mParentActivity.getSystemService(Context.INPUT_METHOD_SERVICE);
		imm.showSoftInput(mInputEditText, 0);
        Log.d("Cocos2dxEditBox", "openKeyboard");	
	}
	
	private void closeKeyboard() {
		InputMethodManager imm = (InputMethodManager) mParentActivity.getSystemService(Context.INPUT_METHOD_SERVICE);
		imm.hideSoftInputFromWindow(mInputEditText.getWindowToken(), 0);
		Log.d("Cocos2dxEditBox", "closeKeyboard");
	}

	@Override
	protected void onStop() {
		// TODO Auto-generated method stub
		super.onStop();
		Log.d("EditBox", "onStop...");
	}
}
