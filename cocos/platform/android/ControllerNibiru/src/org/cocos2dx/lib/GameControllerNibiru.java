package org.cocos2dx.lib;

import org.cocos2dx.lib.GameControllerDelegate;

import com.nibiru.lib.controller.AccEvent;
import com.nibiru.lib.controller.Controller;
import com.nibiru.lib.controller.ControllerDevice;
import com.nibiru.lib.controller.ControllerKeyEvent;
import com.nibiru.lib.controller.ControllerService;
import com.nibiru.lib.controller.ControllerService.OnControllerSeviceListener;
import com.nibiru.lib.controller.ControllerServiceException;
import com.nibiru.lib.controller.GyroEvent;
import com.nibiru.lib.controller.OnAccListener;
import com.nibiru.lib.controller.OnGyroListener;
import com.nibiru.lib.controller.OnKeyListener;
import com.nibiru.lib.controller.OnSimpleStickListener;
import com.nibiru.lib.controller.OnStateListener;

import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.util.SparseIntArray;
import android.view.KeyEvent;
import android.view.MotionEvent;

public class GameControllerNibiru implements OnControllerSeviceListener, OnKeyListener, 
OnSimpleStickListener, OnAccListener, OnGyroListener, OnStateListener, GameControllerDelegate {

	private String TAG = "NibiruTag";
	private String mVendorName = "Nibiru";
	private ControllerService mControllerService = null;
	private Context mContext = null;
	
	private SparseIntArray mKeyMap = null;
	private ControllerEventListener mControllerEventListener;
	   
	public GameControllerNibiru() {
		mKeyMap = new SparseIntArray(20);
		
        mKeyMap.put(ControllerKeyEvent.KEYCODE_BUTTON_A , GameControllerDelegate.BUTTON_A);
        mKeyMap.put(ControllerKeyEvent.KEYCODE_BUTTON_B , GameControllerDelegate.BUTTON_B);
        mKeyMap.put(ControllerKeyEvent.KEYCODE_BUTTON_X , GameControllerDelegate.BUTTON_X);
        mKeyMap.put(ControllerKeyEvent.KEYCODE_BUTTON_Y , GameControllerDelegate.BUTTON_Y);
        mKeyMap.put(ControllerKeyEvent.KEYCODE_BUTTON_L1 , GameControllerDelegate.BUTTON_LEFT_SHOULDER);
        mKeyMap.put(ControllerKeyEvent.KEYCODE_BUTTON_R1 , GameControllerDelegate.BUTTON_RIGHT_SHOULDER);
        mKeyMap.put(ControllerKeyEvent.KEYCODE_BUTTON_L2, GameControllerDelegate.BUTTON_LEFT_TRIGGER);
        mKeyMap.put(ControllerKeyEvent.KEYCODE_BUTTON_R2, GameControllerDelegate.BUTTON_RIGHT_TRIGGER);
        mKeyMap.put(ControllerKeyEvent.KEYCODE_UP , GameControllerDelegate.BUTTON_DPAD_UP);
        mKeyMap.put(ControllerKeyEvent.KEYCODE_DOWN , GameControllerDelegate.BUTTON_DPAD_DOWN);
        mKeyMap.put(ControllerKeyEvent.KEYCODE_LEFT , GameControllerDelegate.BUTTON_DPAD_LEFT);
        mKeyMap.put(ControllerKeyEvent.KEYCODE_RIGHT , GameControllerDelegate.BUTTON_DPAD_RIGHT);
        mKeyMap.put(ControllerKeyEvent.KEYCODE_BUTTON_START , GameControllerDelegate.BUTTON_START);
        mKeyMap.put(ControllerKeyEvent.KEYCODE_BUTTON_SELECT , GameControllerDelegate.BUTTON_SELECT);
        mKeyMap.put(ControllerKeyEvent.KEYCODE_BUTTON_THUMBL , GameControllerDelegate.BUTTON_LEFT_THUMBSTICK);
        mKeyMap.put(ControllerKeyEvent.KEYCODE_BUTTON_THUMBR , GameControllerDelegate.BUTTON_RIGHT_THUMBSTICK);
	}
	
	@Override
	public void setControllerEventListener(ControllerEventListener listener) {
		mControllerEventListener = listener;
	}
	
	public void onCreate(Context context) {
		mContext = context;
		
		mControllerService = Controller.getControllerService();
		if (mControllerService != null) {
			mControllerService.setControllerServiceListener(this);
			mControllerService.setStateListener(this);
			mControllerService.setKeyListener(this);
			mControllerService.setSimpleStickListener(this);
			//mControllerService.setAccListener(this);
			//mControllerService.setGyroListener(this);
			mControllerService.setEnableLR2(true);
			mControllerService.setAutoKeyUpMode(false);
			
			mControllerService.checkNibiruInstall(mContext, true);
		}
	}
	
	public void onPause() {
		if (mControllerService != null) {
			mControllerService.setEnable(false);
		}
	}
	
	public void onResume() {
		if (mControllerService != null) {
			if (mControllerService.isServiceEnable()) {
				//onControllerServiceReady(true);
			} else {
				if (mControllerService.checkNibiruInstall(mContext, false)) {
					try {
						mControllerService.register(mContext);
					} catch (ControllerServiceException e) {
						e.printStackTrace();
					}
				}
			}
			
			mControllerService.setEnable(true);
		}
	}
	
	public void onDestroy() {
		if( mControllerService != null ){
			mControllerService.unregister();
		}
	}

	@Override
	public void onControllerServiceReady(boolean isSucc) {
		if( isSucc )
		{
			if( !mControllerService.hasDeviceConnected() ){
				Bundle bun = new Bundle();
				bun.putBoolean(ControllerService.FLAG_IS_SHOW_GAMEPAD_TIP, true);
				try {
					mControllerService.showDeviceManagerUI(mContext, bun); 
				} catch (ControllerServiceException e) {
						e.printStackTrace(); 
				}
			} 
		}
	}

	@Override
	public void onControllerKeyDown(int playerOrder, int keyCode, ControllerKeyEvent event) {
		Log.d(TAG, "KeyDown: " + keyCode);
		
		if (mKeyMap.get(keyCode, Integer.MIN_VALUE) == Integer.MIN_VALUE) {
			Log.e(TAG, "Didn't map the key: " + keyCode);
			return;
		}
		
		if (mControllerEventListener != null) {
			mControllerEventListener.onButtonEvent(mVendorName, playerOrder, mKeyMap.get(keyCode), true, 1.0f, false);
		}
	}

	@Override
	public void onControllerKeyUp(int playerOrder, int keyCode, ControllerKeyEvent event) {		
		Log.d(TAG, "Keyup: " + keyCode);
		
		if (mKeyMap.get(keyCode, Integer.MIN_VALUE) == Integer.MIN_VALUE) {
			Log.e(TAG, "Didn't map the key: " + keyCode);
			return;
		}
		
		if (mControllerEventListener != null) {
			mControllerEventListener.onButtonEvent(mVendorName, playerOrder, 
					mKeyMap.get(keyCode), false, 0.0f, false);
		}
	}

	@Override
	public void onLeftStickChanged(int playerOrder, float x, float y) {
		Log.d(TAG, "onLeftStickChanged: playerOrder=" + playerOrder + ", x = " + x + ", y = " + y);
		if (mControllerEventListener != null) {
			mControllerEventListener.onAxisEvent(mVendorName, playerOrder, 
					GameControllerDelegate.THUMBSTICK_LEFT_X, x, true);
			mControllerEventListener.onAxisEvent(mVendorName, playerOrder, 
					GameControllerDelegate.THUMBSTICK_LEFT_Y, y, true);
		}
	}

	@Override
	public void onRightStickChanged(int playerOrder, float x, float y) {
		if (mControllerEventListener != null) {
			mControllerEventListener.onAxisEvent(mVendorName, playerOrder, 
					GameControllerDelegate.THUMBSTICK_RIGHT_X, x, true);
			mControllerEventListener.onAxisEvent(mVendorName, playerOrder, 
					GameControllerDelegate.THUMBSTICK_RIGHT_Y, y, true);
		}
		Log.d(TAG, "onRightStickChanged: playerOrder=" + playerOrder + ", x = " + x + ", y = " + y);
	}
	
	@Override
	public void onControllerStateChanged(int playerOrder, int state, ControllerDevice device) {
		Log.d(TAG, "onControllerStateChanged:"+state);
		if (mControllerEventListener != null) {
			if (state == ControllerDevice.STATE_CONN)
			{
				mControllerEventListener.onConnected(mVendorName, playerOrder);
			}
			else if (state == ControllerDevice.STATE_DISCONN)
			{
				mControllerEventListener.onDisconnected(mVendorName, playerOrder);
			}
		}
	}

	public boolean dispatchGenericMotionEvent(MotionEvent event){
		return mControllerService.handleExternalInput(event);
	}
	
	public boolean dispatchKeyEvent(KeyEvent event){
		return mControllerService.handleExternalInput(event);
	}
	
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		return false;
	}
	
	public boolean onKeyUp(int keyCode, KeyEvent event) {
		return false;
	}
	
	public boolean onGenericMotionEvent(MotionEvent event) {
		return false;
	}
	
	@Override
	public void onControllerAccEvent(int playerOrder, AccEvent event) {
		
	}

	@Override
	public void onControllerGyroEvent(int playerOrder, GyroEvent event) {
		
	}

	@Override
	public void onBluetoothStateChanged(int state) {
		Log.d(TAG, "onBluetoothStateChanged:"+state);
	}

}
