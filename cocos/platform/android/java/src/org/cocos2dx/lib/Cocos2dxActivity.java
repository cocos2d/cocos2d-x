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
import org.cocos2dx.lib.GameControllerDelegate.ControllerEventListener;
import org.cocos2dx.lib.inputmanagercompat.InputManagerCompat;
import org.cocos2dx.lib.inputmanagercompat.InputManagerCompat.InputDeviceListener;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Message;
import android.view.InputDevice;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.ViewGroup;
import android.util.Log;
import android.widget.FrameLayout;
import android.preference.PreferenceManager.OnActivityResultListener;

public abstract class Cocos2dxActivity extends Activity implements Cocos2dxHelperListener, InputDeviceListener {
	// ===========================================================
	// Constants
	// ===========================================================

	private final static String TAG = Cocos2dxActivity.class.getSimpleName();

	// ===========================================================
	// Fields
	// ===========================================================
	
	private Cocos2dxGLSurfaceView mGLSurfaceView;
	private Cocos2dxHandler mHandler;	
	private static Cocos2dxActivity sContext = null;
	private Cocos2dxVideoHelper mVideoHelper = null;
	private InputManagerCompat mInputManager = null;
	
	protected GameControllerHelper mControllerHelper = null;
	protected GameControllerDelegate mControllerDelegate = null;
	
	public static Context getContext() {
		return sContext;
	}
	
	protected void onLoadNativeLibraries() {
		try {
			ApplicationInfo ai = getPackageManager().getApplicationInfo(getPackageName(), PackageManager.GET_META_DATA);
			Bundle bundle = ai.metaData;
			String libName = bundle.getString("android.app.lib_name");
    		System.loadLibrary(libName);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public void setGameControllerInstance(GameControllerDelegate controllerDelegate) {
		if (mControllerDelegate != null) {
			mControllerDelegate.onDestroy();
			mControllerDelegate = null;
		}
		mControllerDelegate = controllerDelegate;
		mControllerDelegate.setControllerEventListener(mControllerEventListener);
		mControllerDelegate.onCreate(this);
	}
	
	public GameControllerDelegate getGameControllerInstance(){
		return mControllerDelegate;
	}
	
	ControllerEventListener mControllerEventListener = new ControllerEventListener() {
		
		@Override
		public void onButtonEvent(String vendorName, int controller, int button,
				boolean isPressed, float value, boolean isAnalog) {
			GameControllerAdapter.onButtonEvent(vendorName, controller, button, isPressed, value, isAnalog);
		}
		
		@Override
		public void onAxisEvent(String vendorName, int controller, int axisID,
				float value, boolean isAnalog) {
			GameControllerAdapter.onAxisEvent(vendorName, controller, axisID, value, isAnalog);
		}

		@Override
		public void onConnected(String vendorName, int controller) {
			GameControllerAdapter.onConnected(vendorName, controller);
		}

		@Override
		public void onDisconnected(String vendorName, int controller) {
			GameControllerAdapter.onDisconnected(vendorName, controller);
		}
	};
	
	// ===========================================================
	// Constructors
	// ===========================================================
	
	@Override
	protected void onCreate(final Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		onLoadNativeLibraries();

		sContext = this;
    	this.mHandler = new Cocos2dxHandler(this);
    	
    	Cocos2dxHelper.init(this);
    	
    	this.init();
    	if (mVideoHelper == null) {
    		mVideoHelper = new Cocos2dxVideoHelper(this, mFrameLayout);
		}
    	
    	mInputManager = InputManagerCompat.Factory.getInputManager(this);
    	mInputManager.registerInputDeviceListener(this, null);
    	
    	if (mControllerDelegate != null) {
			mControllerDelegate.onCreate(this);
		}
    	if (mControllerHelper == null) {
    		mControllerHelper = new GameControllerHelper(this);
		}
	}
	
	// ===========================================================
	// Getter & Setter
	// ===========================================================

	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================

	@Override
	public boolean dispatchKeyEvent(KeyEvent event) {
		boolean handled = false; 
		if (mControllerDelegate != null) {
			handled = mControllerDelegate.dispatchKeyEvent(event);
		}
		else {
			handled = mControllerHelper.dispatchKeyEvent(event);
		}
		return handled || super.dispatchKeyEvent(event);
	}
	
	@Override
	public boolean dispatchGenericMotionEvent(MotionEvent event) {
		boolean handled = false;
		if (mControllerDelegate != null) {
			handled = mControllerDelegate.dispatchGenericMotionEvent(event);
		}else {
			handled = mControllerHelper.dispatchGenericMotionEvent(event);
		}
		return handled || super.dispatchGenericMotionEvent(event);
	}
	
	@Override
	public void onInputDeviceAdded(int deviceId) {
		
		Log.d(TAG,"onInputDeviceAdded:" + deviceId);
		
		InputDevice device = InputDevice.getDevice(deviceId);
		int deviceSource = device.getSources();
		
		if ( ((deviceSource & InputDevice.SOURCE_GAMEPAD)  == InputDevice.SOURCE_GAMEPAD) 
        		|| ((deviceSource & InputDevice.SOURCE_JOYSTICK) == InputDevice.SOURCE_JOYSTICK) )
		{
			GameControllerAdapter.onConnected("Standard", deviceId);
		}
	}
	/*
	 * This is an unusual case. Input devices don't typically change, but they
	 * certainly can --- for example a device may have different modes. We use
	 * this to make sure that the ship has an up-to-date InputDevice.
	 * 
	 * @see
	 * com.example.inputmanagercompat.InputManagerCompat.InputDeviceListener
	 * #onInputDeviceChanged(int)
	 */
	@Override
	public void onInputDeviceChanged(int deviceId) {
		Log.d(TAG,"onInputDeviceChanged:" + deviceId);
	}
	
	/*
	 * Remove any ship associated with the ID.
	 * 
	 * @see
	 * com.example.inputmanagercompat.InputManagerCompat.InputDeviceListener
	 * #onInputDeviceRemoved(int)
	 */
	@Override
	public void onInputDeviceRemoved(int deviceId) {
		Log.d(TAG,"onInputDeviceRemoved:" + deviceId);
		
		InputDevice device = InputDevice.getDevice(deviceId);
		int deviceSource = device.getSources();
		
		if ( ((deviceSource & InputDevice.SOURCE_GAMEPAD)  == InputDevice.SOURCE_GAMEPAD) 
        		|| ((deviceSource & InputDevice.SOURCE_JOYSTICK) == InputDevice.SOURCE_JOYSTICK) )
		{
			GameControllerAdapter.onDisconnected("Standard", deviceId);
		}
	}

	@Override
	protected void onResume() {
		super.onResume();

		Cocos2dxHelper.onResume();
		this.mGLSurfaceView.onResume();
		
		if (mControllerDelegate != null) {
			mControllerDelegate.onResume();
		}
	}

	@Override
	protected void onPause() {
		if (mControllerDelegate != null) {
			mControllerDelegate.onPause();
		}
		
		super.onPause();
		
		Cocos2dxHelper.onPause();
		this.mGLSurfaceView.onPause();
	}
	
	@Override
	protected void onDestroy() {
		if (mControllerDelegate != null) {
			mControllerDelegate.onDestroy();
		}
		mControllerHelper.destrory();
		
		super.onDestroy();
	}

	@Override
	public void showDialog(final String pTitle, final String pMessage) {
		Message msg = new Message();
		msg.what = Cocos2dxHandler.HANDLER_SHOW_DIALOG;
		msg.obj = new Cocos2dxHandler.DialogMessage(pTitle, pMessage);
		this.mHandler.sendMessage(msg);
	}

	@Override
	public void showEditTextDialog(final String pTitle, final String pContent, final int pInputMode, final int pInputFlag, final int pReturnType, final int pMaxLength) { 
		Message msg = new Message();
		msg.what = Cocos2dxHandler.HANDLER_SHOW_EDITBOX_DIALOG;
		msg.obj = new Cocos2dxHandler.EditBoxMessage(pTitle, pContent, pInputMode, pInputFlag, pReturnType, pMaxLength);
		this.mHandler.sendMessage(msg);
	}
	
	@Override
	public void runOnGLThread(final Runnable pRunnable) {
		this.mGLSurfaceView.queueEvent(pRunnable);
	}
	
	@Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        for (OnActivityResultListener listener : Cocos2dxHelper.getOnActivityResultListeners()) {
            listener.onActivityResult(requestCode, resultCode, data);
        }

        super.onActivityResult(requestCode, resultCode, data);
    }


	protected FrameLayout mFrameLayout = null;
	// ===========================================================
	// Methods
	// ===========================================================
	public void init() {
		
    	// FrameLayout
        ViewGroup.LayoutParams framelayout_params =
            new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,
                                       ViewGroup.LayoutParams.MATCH_PARENT);
        mFrameLayout = new FrameLayout(this);
        mFrameLayout.setLayoutParams(framelayout_params);

        // Cocos2dxEditText layout
        ViewGroup.LayoutParams edittext_layout_params =
            new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,
                                       ViewGroup.LayoutParams.WRAP_CONTENT);
        Cocos2dxEditText edittext = new Cocos2dxEditText(this);
        edittext.setLayoutParams(edittext_layout_params);

        // ...add to FrameLayout
        mFrameLayout.addView(edittext);

        // Cocos2dxGLSurfaceView
        this.mGLSurfaceView = this.onCreateView();

        // ...add to FrameLayout
        mFrameLayout.addView(this.mGLSurfaceView);

        // Switch to supported OpenGL (ARGB888) mode on emulator
        if (isAndroidEmulator())
           this.mGLSurfaceView.setEGLConfigChooser(8 , 8, 8, 8, 16, 0);

        this.mGLSurfaceView.setCocos2dxRenderer(new Cocos2dxRenderer());
        this.mGLSurfaceView.setCocos2dxEditText(edittext);

        // Set framelayout as the content view
		setContentView(mFrameLayout);
	}
	
    public Cocos2dxGLSurfaceView onCreateView() {
    	return new Cocos2dxGLSurfaceView(this);
    }

   private final static boolean isAndroidEmulator() {
      String model = Build.MODEL;
      Log.d(TAG, "model=" + model);
      String product = Build.PRODUCT;
      Log.d(TAG, "product=" + product);
      boolean isEmulator = false;
      if (product != null) {
         isEmulator = product.equals("sdk") || product.contains("_sdk") || product.contains("sdk_");
      }
      Log.d(TAG, "isEmulator=" + isEmulator);
      return isEmulator;
   }

	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================
}
