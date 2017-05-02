package org.cocos2dx.cpp;

import java.io.ByteArrayOutputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

import android.app.Activity;
import android.app.NativeActivity;
import android.content.Context;
import android.content.CursorLoader;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.util.Log;

// The name of .so is specified in AndroidMenifest.xml. NativityActivity will load it automatically for you.
// You can use "System.loadLibrary()" to load other .so files.

public class Cocos2dxActivity extends NativeActivity{
	private static Cocos2dxActivity self = null;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		
		//For supports translucency
		
		//1.change "attribs" in cocos\2d\platform\android\nativeactivity.cpp
		/*const EGLint attribs[] = {
	            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
	            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,  
	            //EGL_BLUE_SIZE, 5,   -->delete 
	            //EGL_GREEN_SIZE, 6,  -->delete 
	            //EGL_RED_SIZE, 5,    -->delete 
	            EGL_BUFFER_SIZE, 32,  //-->new field
	            EGL_DEPTH_SIZE, 16,
	            EGL_STENCIL_SIZE, 8,
	            EGL_NONE
	    };*/
		
		//2.Set the format of window
		// getWindow().setFormat(PixelFormat.TRANSLUCENT);
		
		self = this;
	}
	

	private static final int IMAGE_PICKER_ACTIVITY = 31;	//Magic Number
	
	public static void openImage()  {
		Intent intent = new Intent();
		intent.setType("image/*");
		intent.setAction(Intent.ACTION_GET_CONTENT);
		      
		self.startActivityForResult(intent, IMAGE_PICKER_ACTIVITY); 
	}
	
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		if (requestCode == IMAGE_PICKER_ACTIVITY) {
			byte[] byteArray = {0};
			if (resultCode == Activity.RESULT_OK) {
				Uri imageUri = data.getData();	
				try {
					Bitmap bmp = MediaStore.Images.Media.getBitmap(this.getContentResolver(), imageUri);
					ByteArrayOutputStream stream = new ByteArrayOutputStream();
					bmp.compress(Bitmap.CompressFormat.PNG, 100, stream);
					byteArray = stream.toByteArray();
				} catch (FileNotFoundException e) {
				} catch (IOException e) {
				}
			}
			ImagePickerResult(byteArray);
		}
	}

	public native void ImagePickerResult(final byte[] imagedata);
}
