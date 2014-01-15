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

import android.app.Activity;
import android.content.Context;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.KeyEvent;
import android.view.ViewGroup;
import android.view.inputmethod.EditorInfo;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.TextView.OnEditorActionListener;

public class Cocos2dxEditText extends EditText {
	// ===========================================================
	// Constants
	// ===========================================================

	// ===========================================================
	// Fields
	// ===========================================================
	
	private Cocos2dxTextInputWraper mTextWatcher = null;
	private Context mContext = null;
	private static Cocos2dxEditText instance = null;

	// ===========================================================
	// Constructors
	// ===========================================================

	public Cocos2dxEditText(final Context context) {
		super(context);
		
		this.mContext = context;
		this.mTextWatcher = new Cocos2dxTextInputWraper(context, this);
		this.setOnEditorActionListener(this.mTextWatcher);
		
		ViewGroup.LayoutParams layout =
	            new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,
	                                       ViewGroup.LayoutParams.WRAP_CONTENT);
		
		Activity activity = (Activity)context;
		activity.addContentView(this, layout);
	}

	// ===========================================================
	// Getter & Setter
	// ===========================================================


	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================
	
	public static Cocos2dxEditText getInstance(final Context context) {
		if (instance == null) {
			instance = new Cocos2dxEditText(context);
		}
		return instance;
	}
	
	public void closeIMEKeyboard() {
		this.removeTextChangedListener(mTextWatcher);
		final InputMethodManager imm = (InputMethodManager)mContext.getSystemService(Context.INPUT_METHOD_SERVICE);
		imm.hideSoftInputFromWindow(this.getWindowToken(), 0);
		//Cocos2dxHelper.nativeRequestFocus();
	}
	
	public void openIMEKeyboard() {
		this.requestFocus();
		final String content = nativeGetContent();
		this.setText(content);
			
		mTextWatcher.setOriginText(content);
		this.addTextChangedListener(mTextWatcher);
		
		final InputMethodManager imm = (InputMethodManager)mContext.getSystemService(Context.INPUT_METHOD_SERVICE);
		imm.showSoftInput(this, InputMethodManager.SHOW_FORCED);
	}

	@Override
	public boolean onKeyDown(final int keyCode, final KeyEvent keyEvent) {
		super.onKeyDown(keyCode, keyEvent);

		/* Let GlSurfaceView get focus if back key is input. */
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			//Cocos2dxHelper.nativeRequestFocus();
		}

		return true;
	}

	// ===========================================================
	// Methods
	// ===========================================================
	
	private native static String nativeGetContent();

	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================
}

class Cocos2dxTextInputWraper implements TextWatcher, OnEditorActionListener {
	// ===========================================================
	// Constants
	// ===========================================================

	private static final String TAG = Cocos2dxTextInputWraper.class.getSimpleName();

	// ===========================================================
	// Fields
	// ===========================================================

	private String mText;
	private String mOriginText;
	private Context mContext;
	private TextView mTextView;

	// ===========================================================
	// Constructors
	// ===========================================================

	public Cocos2dxTextInputWraper(Context context, TextView textView) {
		this.mContext = context;
		this.mTextView = textView;
	}

	// ===========================================================
	// Getter & Setter
	// ===========================================================

	private boolean isFullScreenEdit() {
		final InputMethodManager imm = (InputMethodManager) this.mContext.getSystemService(Context.INPUT_METHOD_SERVICE);
		return imm.isFullscreenMode();
	}

	public void setOriginText(final String originText) {
		this.mOriginText = originText;
	}

	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================

	@Override
	public void afterTextChanged(final Editable s) {
		if (this.isFullScreenEdit()) {
			return;
		}

		int nModified = s.length() - this.mText.length();
		if (nModified > 0) {
			final String insertText = s.subSequence(this.mText.length(), s.length()).toString();
			nativeInsertText(insertText);
		} else {
			for (; nModified < 0; ++nModified) {
				nativeDeleteBackward();
			}
		}
		this.mText = s.toString();
	}

	@Override
	public void beforeTextChanged(final CharSequence pCharSequence, final int start, final int count, final int after) {
		this.mText = pCharSequence.toString();
	}

	@Override
	public void onTextChanged(final CharSequence pCharSequence, final int start, final int before, final int count) {
	}

	@Override
	public boolean onEditorAction(final TextView pTextView, final int pActionID, final KeyEvent pKeyEvent) {
		if (this.mTextView  == pTextView && this.isFullScreenEdit()) {
			// user press the action button, delete all old text and insert new text
			for (int i = this.mOriginText.length(); i > 0; i--) {
				Cocos2dxHelper.runOnGLThread(new Runnable() {

					@Override
					public void run() {
						nativeDeleteBackward();
					}
					
				});
				
			}
			String text = pTextView.getText().toString();

			/* If user input nothing, translate "\n" to engine. */
			if (text.compareTo("") == 0) {
				text = "\n";
			}

			if ('\n' != text.charAt(text.length() - 1)) {
				text += '\n';
			}

			final String insertText = text;
			Cocos2dxHelper.runOnGLThread(new Runnable() {

				@Override
				public void run() {
					nativeInsertText(insertText);
				}
				
			});
		}
		
		if (pActionID == EditorInfo.IME_ACTION_DONE) {
			//Cocos2dxHelper.nativeRequestFocus();
		}
		return false;
	}

	// ===========================================================
	// Methods
	// ===========================================================
	
	private native static void nativeInsertText(String text);
	private native static void nativeDeleteBackward();
	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================
}
