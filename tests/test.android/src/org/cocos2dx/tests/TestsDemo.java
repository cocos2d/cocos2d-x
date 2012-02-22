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
package org.cocos2dx.tests;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxEditText;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.os.Bundle;

public class TestsDemo extends Cocos2dxActivity{
	private Cocos2dxGLSurfaceView mGLView;
	
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		
		// get the packageName,it's used to set the resource path
		String packageName = getApplication().getPackageName();
		super.setPackageName(packageName);

        setContentView(R.layout.test_demo);
        mGLView = (Cocos2dxGLSurfaceView) findViewById(R.id.test_demo_gl_surfaceview);
        mGLView.setTextField((Cocos2dxEditText)findViewById(R.id.textField));      
	}

	 @Override
	 protected void onPause() {		 
	     super.onPause();
	     
	     mGLView.onPause();
	 }

	 @Override
	 protected void onResume() {
	     super.onResume();
	     
	     mGLView.onResume();
	 }

     static {
    	 System.loadLibrary("cocosdenshion");
    	 System.loadLibrary("chipmunk");
    	 System.loadLibrary("box2d");
         System.loadLibrary("tests");
     }     
}
