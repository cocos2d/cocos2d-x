/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

import java.io.FileInputStream;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import android.content.Context;
import android.content.res.AssetManager;
import android.opengl.ETC1Util;
import android.util.Log;

public class Cocos2dxETCLoader {
	private static final String ASSETS_PATH = "assets/";
	private static Context context;
	
	public static boolean loadTexture(String filePath) {
		if (! ETC1Util.isETC1Supported()) {
			return false;
		}
		
		if (filePath.length() == 0) {
			return false;
		}
		
		// Create ETC1Texture
		InputStream inputStream = null;
		ETC1Util.ETC1Texture texture = null;
		AssetManager assetManager = null;
		try {
			if (filePath.charAt(0) == '/') {
				// absolute path
				inputStream = new FileInputStream(filePath);
			} else {
				// remove prefix: "assets/"
				if (filePath.startsWith(ASSETS_PATH)) {
					filePath = filePath.substring(ASSETS_PATH.length());
				}
				assetManager = context.getAssets();
				inputStream = assetManager.open(filePath);
			}
			
			texture = ETC1Util.createTexture(inputStream);
			inputStream.close();
			assetManager.close();
		} catch (Exception e) {
			Log.d("Cocos2dx", "Unable to create texture for " + filePath);
			
			texture = null;
		}
		
		if (texture != null) {
			try {
				int width = texture.getWidth();
				int height = texture.getHeight();

			    final byte[] data = new byte[width * height * 3];
			    final ByteBuffer buf = ByteBuffer.wrap(data);
			    buf.order(ByteOrder.nativeOrder());
			    buf.put(texture.getData());

				nativeSetTextureInfo(width,
			             height,
			             data);
			} catch (Exception e)
			{
				Log.d("invoke native function error", e.toString());
			}
			
			return true;
		} else {
			return false;
		}
	}
	
	public static void setContext(Context context) {
		Cocos2dxETCLoader.context = context;
	}
	
	private static native void nativeSetTextureInfo(final int width, final int height, final byte[] data);
}
