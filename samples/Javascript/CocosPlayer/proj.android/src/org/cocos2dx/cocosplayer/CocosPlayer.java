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
package org.cocos2dx.cocosplayer;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.content.ContextWrapper;
import android.content.Context;
import android.util.Log;

public class CocosPlayer extends Cocos2dxActivity {

	public static Context c;

	public static Activity activity;

	public static void setOrientation(int orient) {
		((Activity) Cocos2dxActivity.getContext())
				.setRequestedOrientation(orient);
	}

	@Override
	public void onStop() {
		Log.i("CocosPlayer", "onStop");
		CocosPlayerPresence.destroy();
		super.onStop();
	}

	@Override
	public void onResume() {
		CocosPlayerPresence.startPresence();
		Log.i("CocosPlayer", "onResume");
		super.onResume();
	}

	@Override
	public void finish() {
		Log.i("CocosPlayer", "onFinish");
		CocosPlayerPresence.destroy();
	}

	protected void onCreate(Bundle savedInstanceState) {
		Log.i("CocosPlayer", "onCreate");
		super.onCreate(savedInstanceState);
		activity = ((Activity) Cocos2dxActivity.getContext());
		c = getApplicationContext();
	}

	static {
		System.loadLibrary("cocosplayer");
	}

}
