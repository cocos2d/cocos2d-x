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
package org.cocos2dx.HelloPlugins;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.cocos2dx.plugin.PluginWrapper;
import org.cocos2dx.plugin.FacebookWrapper;

import android.content.Intent;
import android.os.Bundle;

public class AppActivity extends Cocos2dxActivity {
    
    public Cocos2dxGLSurfaceView onCreateView() {
        Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
        // TestCpp should create stencil buffer
        glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
        
        PluginWrapper.init(this);
        PluginWrapper.setGLSurfaceView(glSurfaceView);
        FacebookWrapper.onCreate(this);
        return glSurfaceView;
    }

	@Override
	protected void onResume() {
		super.onResume();
		PluginWrapper.onResume();
	}

	@Override
	protected void onPause() {
		super.onPause();
		PluginWrapper.onPause();
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		PluginWrapper.onDestroy();
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		if(!PluginWrapper.onActivityResult(requestCode, resultCode, data))
		{
			super.onActivityResult(requestCode, resultCode, data);
		}
        FacebookWrapper.onAcitivityResult(requestCode, resultCode, data);
	}
    
    @Override
    public void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);
        FacebookWrapper.onSaveInstanceState(outState);
    }
    
}
