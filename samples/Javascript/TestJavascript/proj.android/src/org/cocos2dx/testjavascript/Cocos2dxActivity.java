package org.cocos2dx.testjavascript;

import android.app.NativeActivity;
import android.graphics.PixelFormat;
import android.os.Bundle;

public class Cocos2dxActivity extends NativeActivity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		
		//For supports translucency.
		//You need configure egl attribs of the color buffer size in cocos\2d\platform\android\nativeactivity.cpp on some android versions(eg.4.4) 
		//getWindow().setFormat(PixelFormat.TRANSLUCENT);
	}
}
