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

	private static final String TAG = "NibiruTag";
		
	private Context mContext;
	private SparseIntArray mKeyMap;
	private ControllerEventListener mControllerEventListener = null;
	private ControllerService mControllerService = null;
	
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
			
			mControllerService.checkNibiruInstall(mContext, false);
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
				bun.putBoolean(ControllerService.FLAG_IS_SHOW_GAMEPAD_TIP, false);
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
		if (mKeyMap.get(keyCode) == 0) {
			Log.e(TAG, "Didn't map the key: " + keyCode);
			return;
		}
		
		if (mControllerEventListener != null) {
			try {
				ControllerDevice controllerDevice = mControllerService.getDeviceByPlayerOrder(playerOrder);
				
				mControllerEventListener.onButtonEvent(controllerDevice.getDeviceName(), controllerDevice.getDeviceId(), 
						mKeyMap.get(keyCode), true, 1.0f, false);
			} catch (ControllerServiceException e) {
				e.printStackTrace();
			}
		}
	}

	@Override
	public void onControllerKeyUp(int playerOrder, int keyCode, ControllerKeyEvent event) {		
		if (mKeyMap.get(keyCode) == 0) {
			Log.e(TAG, "Didn't map the key: " + keyCode);
			return;
		}
		
		if (mControllerEventListener != null) {
			try {
				ControllerDevice controllerDevice = mControllerService.getDeviceByPlayerOrder(playerOrder);
				
				mControllerEventListener.onButtonEvent(controllerDevice.getDeviceName(), controllerDevice.getDeviceId(), 
						mKeyMap.get(keyCode), false, 0.0f, false);
			} catch (ControllerServiceException e) {
				e.printStackTrace();
			}
		}
	}

	@Override
	public void onLeftStickChanged(int playerOrder, float x, float y) {
		if (mControllerEventListener != null) {
			try {
				ControllerDevice controllerDevice = mControllerService.getDeviceByPlayerOrder(playerOrder);
				
				String deviceName = controllerDevice.getDeviceName();
				int deviceId = controllerDevice.getDeviceId();
				
				mControllerEventListener.onAxisEvent(deviceName, deviceId, 
						GameControllerDelegate.THUMBSTICK_LEFT_X, x, true);
				mControllerEventListener.onAxisEvent(deviceName, deviceId, 
						GameControllerDelegate.THUMBSTICK_LEFT_Y, y, true);				
			} catch (ControllerServiceException e) {
				e.printStackTrace();
			}
		}
	}

	@Override
	public void onRightStickChanged(int playerOrder, float x, float y) {
		if (mControllerEventListener != null) {
			try {
				ControllerDevice controllerDevice = mControllerService.getDeviceByPlayerOrder(playerOrder);
				
				String deviceName = controllerDevice.getDeviceName();
				int deviceId = controllerDevice.getDeviceId();
				
				mControllerEventListener.onAxisEvent(deviceName, deviceId, 
						GameControllerDelegate.THUMBSTICK_RIGHT_X, x, true);
				mControllerEventListener.onAxisEvent(deviceName, deviceId, 
						GameControllerDelegate.THUMBSTICK_RIGHT_Y, y, true);
			} catch (ControllerServiceException e) {
				e.printStackTrace();
			}
		}
	}
	
	@Override
	public void onControllerStateChanged(int playerOrder, int state, ControllerDevice device) {
		if (mControllerEventListener != null) {
			if (state == ControllerDevice.STATE_CONN)
			{
				mControllerEventListener.onConnected(device.getDeviceName(), device.getDeviceId());
			}
			else if (state == ControllerDevice.STATE_DISCONN)
			{
				mControllerEventListener.onDisconnected(device.getDeviceName(), device.getDeviceId());
			}
		}
	}

	public boolean dispatchGenericMotionEvent(MotionEvent event){
		return mControllerService.handleExternalInput(event);
	}
	
	public boolean dispatchKeyEvent(KeyEvent event){
		return mControllerService.handleExternalInput(event);
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
