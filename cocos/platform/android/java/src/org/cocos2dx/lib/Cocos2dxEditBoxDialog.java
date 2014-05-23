/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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
	// ===========================================================
	// Constants
	// ===========================================================

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

	private final int kKeyboardReturnTypeDefault = 0;
	private final int kKeyboardReturnTypeDone = 1;
	private final int kKeyboardReturnTypeSend = 2;
	private final int kKeyboardReturnTypeSearch = 3;
	private final int kKeyboardReturnTypeGo = 4;

	// ===========================================================
	// Fields
	// ===========================================================

	private EditText mInputEditText;
	private TextView mTextViewTitle;

	private final String mTitle;
	private final String mMessage;
	private final int mInputMode;
	private final int mInputFlag;
	private final int mReturnType;
	private final int mMaxLength;

	private int mInputFlagConstraints;
	private int mInputModeContraints;
	private boolean mIsMultiline;

	// ===========================================================
	// Constructors
	// ===========================================================

	public Cocos2dxEditBoxDialog(final Context pContext, final String pTitle, final String pMessage, final int pInputMode, final int pInputFlag, final int pReturnType, final int pMaxLength) {
		super(pContext, android.R.style.Theme_Translucent_NoTitleBar_Fullscreen);
//		super(context, R.style.Theme_Translucent);

		this.mTitle = pTitle;
		this.mMessage = pMessage;
		this.mInputMode = pInputMode;
		this.mInputFlag = pInputFlag;
		this.mReturnType = pReturnType;
		this.mMaxLength = pMaxLength;
	}

	@Override
	protected void onCreate(final Bundle pSavedInstanceState) {
		super.onCreate(pSavedInstanceState);

		this.getWindow().setBackgroundDrawable(new ColorDrawable(0x80000000));

		final LinearLayout layout = new LinearLayout(this.getContext());
		layout.setOrientation(LinearLayout.VERTICAL);

		final LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);

		this.mTextViewTitle = new TextView(this.getContext());
		final LinearLayout.LayoutParams textviewParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
		textviewParams.leftMargin = textviewParams.rightMargin = this.convertDipsToPixels(10);
		this.mTextViewTitle.setTextSize(TypedValue.COMPLEX_UNIT_DIP, 20);
		layout.addView(this.mTextViewTitle, textviewParams);

		this.mInputEditText = new EditText(this.getContext());
		final LinearLayout.LayoutParams editTextParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
		editTextParams.leftMargin = editTextParams.rightMargin = this.convertDipsToPixels(10);

		layout.addView(this.mInputEditText, editTextParams);

		this.setContentView(layout, layoutParams);

		this.getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);

		this.mTextViewTitle.setText(this.mTitle);
		this.mInputEditText.setText(this.mMessage);

		int oldImeOptions = this.mInputEditText.getImeOptions();
		this.mInputEditText.setImeOptions(oldImeOptions | EditorInfo.IME_FLAG_NO_EXTRACT_UI);
		oldImeOptions = this.mInputEditText.getImeOptions();

		switch (this.mInputMode) {
			case kEditBoxInputModeAny:
				this.mInputModeContraints = InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_FLAG_MULTI_LINE;
				break;
			case kEditBoxInputModeEmailAddr:
				this.mInputModeContraints = InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_EMAIL_ADDRESS;
				break;
			case kEditBoxInputModeNumeric:
				this.mInputModeContraints = InputType.TYPE_CLASS_NUMBER | InputType.TYPE_NUMBER_FLAG_SIGNED;
				break;
			case kEditBoxInputModePhoneNumber:
				this.mInputModeContraints = InputType.TYPE_CLASS_PHONE;
				break;
			case kEditBoxInputModeUrl:
				this.mInputModeContraints = InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_URI;
				break;
			case kEditBoxInputModeDecimal:
				this.mInputModeContraints = InputType.TYPE_CLASS_NUMBER | InputType.TYPE_NUMBER_FLAG_DECIMAL | InputType.TYPE_NUMBER_FLAG_SIGNED;
				break;
			case kEditBoxInputModeSingleLine:
				this.mInputModeContraints = InputType.TYPE_CLASS_TEXT;
				break;
			default:

				break;
		}

		if (this.mIsMultiline) {
			this.mInputModeContraints |= InputType.TYPE_TEXT_FLAG_MULTI_LINE;
		}

		this.mInputEditText.setInputType(this.mInputModeContraints | this.mInputFlagConstraints);

		switch (this.mInputFlag) {
			case kEditBoxInputFlagPassword:
				this.mInputFlagConstraints = InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_PASSWORD;
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
			default:
				break;
		}

		this.mInputEditText.setInputType(this.mInputFlagConstraints | this.mInputModeContraints);

		switch (this.mReturnType) {
			case kKeyboardReturnTypeDefault:
				this.mInputEditText.setImeOptions(oldImeOptions | EditorInfo.IME_ACTION_NONE);
				break;
			case kKeyboardReturnTypeDone:
				this.mInputEditText.setImeOptions(oldImeOptions | EditorInfo.IME_ACTION_DONE);
				break;
			case kKeyboardReturnTypeSend:
				this.mInputEditText.setImeOptions(oldImeOptions | EditorInfo.IME_ACTION_SEND);
				break;
			case kKeyboardReturnTypeSearch:
				this.mInputEditText.setImeOptions(oldImeOptions | EditorInfo.IME_ACTION_SEARCH);
				break;
			case kKeyboardReturnTypeGo:
				this.mInputEditText.setImeOptions(oldImeOptions | EditorInfo.IME_ACTION_GO);
				break;
			default:
				this.mInputEditText.setImeOptions(oldImeOptions | EditorInfo.IME_ACTION_NONE);
				break;
		}

		if (this.mMaxLength > 0) {
			this.mInputEditText.setFilters(new InputFilter[] { new InputFilter.LengthFilter(this.mMaxLength) });
		}

		final Handler initHandler = new Handler();
		initHandler.postDelayed(new Runnable() {
			@Override
			public void run() {
				Cocos2dxEditBoxDialog.this.mInputEditText.requestFocus();
				Cocos2dxEditBoxDialog.this.mInputEditText.setSelection(Cocos2dxEditBoxDialog.this.mInputEditText.length());
				Cocos2dxEditBoxDialog.this.openKeyboard();
			}
		}, 200);

		this.mInputEditText.setOnEditorActionListener(new OnEditorActionListener() {
			@Override
			public boolean onEditorAction(final TextView v, final int actionId, final KeyEvent event) {
				/* If user didn't set keyboard type, this callback will be invoked twice with 'KeyEvent.ACTION_DOWN' and 'KeyEvent.ACTION_UP'. */
				if (actionId != EditorInfo.IME_NULL || (actionId == EditorInfo.IME_NULL && event != null && event.getAction() == KeyEvent.ACTION_DOWN)) {
					Cocos2dxHelper.setEditTextDialogResult(Cocos2dxEditBoxDialog.this.mInputEditText.getText().toString());
					Cocos2dxEditBoxDialog.this.closeKeyboard();
					Cocos2dxEditBoxDialog.this.dismiss();
					return true;
				}
				return false;
			}
		});
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

	private int convertDipsToPixels(final float pDIPs) {
		final float scale = this.getContext().getResources().getDisplayMetrics().density;
		return Math.round(pDIPs * scale);
	}

	private void openKeyboard() {
		final InputMethodManager imm = (InputMethodManager) this.getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
		imm.showSoftInput(this.mInputEditText, 0);
	}

	private void closeKeyboard() {
		final InputMethodManager imm = (InputMethodManager) this.getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
		imm.hideSoftInputFromWindow(this.mInputEditText.getWindowToken(), 0);
	}

	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================
}
