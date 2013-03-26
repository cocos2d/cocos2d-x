/****************************************************************************
Copyright (c) 2010-2013 cocos2d-x.org

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

import org.cocos2dx.lib.Cocos2dxHelper.Cocos2dxHelperListener;

import android.app.Activity;
import android.app.NativeActivity;
import android.content.Context;
import android.os.Build;
import android.os.Bundle;

public class Cocos2dxActivity extends NativeActivity implements Cocos2dxHelperListener {
	// ===========================================================
	// Constants
	// ===========================================================

	private static final String TAG = Cocos2dxActivity.class.getSimpleName();

	// ===========================================================
	// Fields
	// ===========================================================
	
	private static Context sContext = null;
	
	public static Context getContext() {
		return sContext;
	}
	
	// ===========================================================
	// Constructors
	// ===========================================================
	
	@Override
	protected void onCreate(final Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		sContext = this;

		Cocos2dxHelper.init(this, this);
	}

	// @Override
	// protected void onDestroy() {
	// 	super.onDestroy();
	// }

	@Override
	protected void onPause() {
		super.onPause();

		Cocos2dxHelper.onPause();
	}

	@Override
	public void onWindowFocusChanged(final boolean hasWindowFocus) {
		super.onWindowFocusChanged(hasWindowFocus);
		if (hasWindowFocus) {
			Cocos2dxHelper.onResume();
			this.mGLSurfaceView.onResume();
		} else {
			Cocos2dxHelper.onPause();
			this.mGLSurfaceView.onPause();
		}
	}

	@Override
	protected void onResume() {
		super.onResume();

		Cocos2dxHelper.onResume();
	}

    // @Override
    // protected void onStart() {
    //     super.onStart();
    // }

    // @Override
    // protected void onStop() {
    //     super.onStop();
    // }

	@Override
	public void showDialog(final String pTitle, final String pMessage) {
        // NYI
	}

	@Override
        public void showEditTextDialog(final String pTitle,
                                       final String pContent,
                                       final int pInputMode,
                                       final int pInputFlag,
                                       final int pReturnType,
                                       final int pMaxLength) { 
        // NYI
	}
	
	@Override
	public void runOnGLThread(final Runnable pRunnable) {
        // this.mGLSurfaceView.queueEvent(pRunnable);
	}
>>>>>>> ccx : Cocos2dxActivity extends NativeActivity
}
