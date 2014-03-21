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

import android.content.Context;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.KeyEvent;
import android.view.inputmethod.EditorInfo;
import android.view.inputmethod.InputMethodManager;
import android.widget.TextView;
import android.widget.TextView.OnEditorActionListener;

public class Cocos2dxTextInputWraper implements TextWatcher, OnEditorActionListener {
	// ===========================================================
	// Constants
	// ===========================================================

	private static final String TAG = Cocos2dxTextInputWraper.class.getSimpleName();

	// ===========================================================
	// Fields
	// ===========================================================

	private final Cocos2dxGLSurfaceView mCocos2dxGLSurfaceView;
	private String mText;
	private String mOriginText;

	// ===========================================================
	// Constructors
	// ===========================================================

	public Cocos2dxTextInputWraper(final Cocos2dxGLSurfaceView pCocos2dxGLSurfaceView) {
		this.mCocos2dxGLSurfaceView = pCocos2dxGLSurfaceView;
	}

	// ===========================================================
	// Getter & Setter
	// ===========================================================

	private boolean isFullScreenEdit() {
		final TextView textField = this.mCocos2dxGLSurfaceView.getCocos2dxEditText();
		final InputMethodManager imm = (InputMethodManager) textField.getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
		return imm.isFullscreenMode();
	}

	public void setOriginText(final String pOriginText) {
		this.mOriginText = pOriginText;
	}

	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================

	@Override
	public void afterTextChanged(final Editable s) {
		if (this.isFullScreenEdit()) {
			return;
		}

		//if (BuildConfig.DEBUG) {
			//Log.d(TAG, "afterTextChanged: " + s);
		//}
		int nModified = s.length() - this.mText.length();
		if (nModified > 0) {
			final String insertText = s.subSequence(this.mText.length(), s.length()).toString();
			this.mCocos2dxGLSurfaceView.insertText(insertText);
			/*
			if (BuildConfig.DEBUG) {
				Log.d(TAG, "insertText(" + insertText + ")");
			}
			*/
		} else {
			for (; nModified < 0; ++nModified) {
				this.mCocos2dxGLSurfaceView.deleteBackward();
				/*
				if (BuildConfig.DEBUG) {
					Log.d(TAG, "deleteBackward");
				}
				*/
			}
		}
		this.mText = s.toString();
	}

	@Override
	public void beforeTextChanged(final CharSequence pCharSequence, final int start, final int count, final int after) {
		/*
		if (BuildConfig.DEBUG) {
			Log.d(TAG, "beforeTextChanged(" + pCharSequence + ")start: " + start + ",count: " + count + ",after: " + after);
		}
		*/
		this.mText = pCharSequence.toString();
	}

	@Override
	public void onTextChanged(final CharSequence pCharSequence, final int start, final int before, final int count) {

	}

	@Override
	public boolean onEditorAction(final TextView pTextView, final int pActionID, final KeyEvent pKeyEvent) {
		if (this.mCocos2dxGLSurfaceView.getCocos2dxEditText() == pTextView && this.isFullScreenEdit()) {
			// user press the action button, delete all old text and insert new text
			for (int i = this.mOriginText.length(); i > 0; i--) {
				this.mCocos2dxGLSurfaceView.deleteBackward();
				/*
				if (BuildConfig.DEBUG) {
					Log.d(TAG, "deleteBackward");
				}
				*/
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
			this.mCocos2dxGLSurfaceView.insertText(insertText);
			/*
			if (BuildConfig.DEBUG) {
				Log.d(TAG, "insertText(" + insertText + ")");
			}
			*/
		}
		
		if (pActionID == EditorInfo.IME_ACTION_DONE) {
			this.mCocos2dxGLSurfaceView.requestFocus();
		}
		return false;
	}

	// ===========================================================
	// Methods
	// ===========================================================

	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================
}