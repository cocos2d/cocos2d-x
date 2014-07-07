package org.cocos2dx.lib;


import org.cocos2dx.lib.GameControllerDelegate;

import tv.ouya.console.api.OuyaController;
import android.content.Context;
import android.util.SparseIntArray;
import android.view.KeyEvent;
import android.view.MotionEvent;

public class GameControllerOuya implements GameControllerDelegate{

	public static final String sVendorName = "Ouya";
	
	private SparseIntArray mKeyMap;
    
	public GameControllerOuya(){
    	mKeyMap = new SparseIntArray(20);
		mKeyMap.put(OuyaController.BUTTON_A, GameControllerDelegate.BUTTON_B);
		mKeyMap.put(OuyaController.BUTTON_O, GameControllerDelegate.BUTTON_A);
		mKeyMap.put(OuyaController.BUTTON_U, GameControllerDelegate.BUTTON_X);
		mKeyMap.put(OuyaController.BUTTON_Y, GameControllerDelegate.BUTTON_Y);
        mKeyMap.put(OuyaController.BUTTON_DPAD_DOWN, GameControllerDelegate.BUTTON_DPAD_DOWN);
        mKeyMap.put(OuyaController.BUTTON_DPAD_LEFT, GameControllerDelegate.BUTTON_DPAD_LEFT);
        mKeyMap.put(OuyaController.BUTTON_DPAD_RIGHT, GameControllerDelegate.BUTTON_DPAD_RIGHT);
        mKeyMap.put(OuyaController.BUTTON_DPAD_UP, GameControllerDelegate.BUTTON_DPAD_UP);
        mKeyMap.put(OuyaController.BUTTON_L1, GameControllerDelegate.BUTTON_LEFT_SHOULDER);
        mKeyMap.put(OuyaController.BUTTON_R1,  GameControllerDelegate.BUTTON_RIGHT_SHOULDER);
        mKeyMap.put(OuyaController.AXIS_L2, GameControllerDelegate.BUTTON_LEFT_TRIGGER);
        mKeyMap.put(OuyaController.AXIS_R2, GameControllerDelegate.BUTTON_RIGHT_TRIGGER);
        
        mKeyMap.put(OuyaController.AXIS_LS_X, GameControllerDelegate.BUTTON_LEFT_THUMBSTICK);
        mKeyMap.put(OuyaController.AXIS_LS_Y, GameControllerDelegate.BUTTON_LEFT_THUMBSTICK);
        mKeyMap.put(OuyaController.AXIS_RS_X, GameControllerDelegate.BUTTON_RIGHT_THUMBSTICK);
        mKeyMap.put(OuyaController.AXIS_RS_Y, GameControllerDelegate.BUTTON_RIGHT_THUMBSTICK);
    }
    
    public void onCreate(Context context) {
    	OuyaController.init(context);
    	/*GameControllerAdapter.addRunnableToFrameStartList(new Runnable() {

			@Override
			public void run() {
				OuyaController.startOfFrame();
			}
    		
    	});*/
    }
    
    private float mOldLeftThumbstickX = 0.0f;
	private float mOldLeftThumbstickY = 0.0f;
	private float mOldRightThumbstickX = 0.0f;
	private float mOldRightThumbstickY = 0.0f;
	
    private float mOldLeftTrigger = 0.0f;
	private float mOldRightTrigger = 0.0f;
	
    public boolean dispatchGenericMotionEvent(MotionEvent event) {
        boolean handled = OuyaController.onGenericMotionEvent(event);
        
        if (handled && mControllerEventListener != null)
        {
        	OuyaController c = OuyaController.getControllerByDeviceId(event.getDeviceId());
        	int controllerID = OuyaController.getPlayerNumByDeviceId(event.getDeviceId());
        	
        	float newLeftTrigger = c.getAxisValue(OuyaController.AXIS_L2);
        	if (Float.compare(newLeftTrigger, mOldLeftTrigger) != 0) {
        		mControllerEventListener.onAxisEvent(sVendorName, controllerID, GameControllerDelegate.BUTTON_LEFT_TRIGGER, newLeftTrigger, true);
				mOldLeftTrigger = newLeftTrigger;
			}
        	
        	float newRightTrigger = c.getAxisValue(OuyaController.AXIS_R2);
        	if (Float.compare(newRightTrigger, mOldRightTrigger) != 0) {
        		mControllerEventListener.onAxisEvent(sVendorName, controllerID, GameControllerDelegate.BUTTON_RIGHT_TRIGGER, newRightTrigger, true);
				mOldRightTrigger = newRightTrigger;
			}
        	
        	float newLeftThumbstickX = c.getAxisValue(OuyaController.AXIS_LS_X);
        	if (Float.compare(newLeftThumbstickX, mOldLeftThumbstickX) != 0) {
				if (Float.compare(newLeftThumbstickX, 0.0f) == 0) {
					mControllerEventListener.onAxisEvent(sVendorName, controllerID, GameControllerDelegate.THUMBSTICK_LEFT_X, 0.0f, true);
				}else {
					mControllerEventListener.onAxisEvent(sVendorName, controllerID, GameControllerDelegate.THUMBSTICK_LEFT_X, newLeftThumbstickX, true);
				}
				mOldLeftThumbstickX = newLeftThumbstickX;
			}
        	
        	float newLeftThumbstickY = c.getAxisValue(OuyaController.AXIS_LS_Y);
        	if (Float.compare(newLeftThumbstickY, mOldLeftThumbstickY) != 0) {
				if (Float.compare(newLeftThumbstickY, 0.0f) == 0) {
					mControllerEventListener.onAxisEvent(sVendorName, controllerID, GameControllerDelegate.THUMBSTICK_LEFT_Y, 0.0f, true);
				}else {
					mControllerEventListener.onAxisEvent(sVendorName, controllerID, GameControllerDelegate.THUMBSTICK_LEFT_Y, newLeftThumbstickY, true);
				}
				mOldLeftThumbstickY = newLeftThumbstickY;
			}
        	
        	float newRightThumbstickX = c.getAxisValue(OuyaController.AXIS_RS_X);
        	if (Float.compare(newRightThumbstickX, mOldRightThumbstickX) != 0) {
				if (Float.compare(newRightThumbstickX, 0.0f) == 0) {
					mControllerEventListener.onAxisEvent(sVendorName, controllerID, GameControllerDelegate.THUMBSTICK_RIGHT_X, 0.0f, true);
				}else {
					mControllerEventListener.onAxisEvent(sVendorName, controllerID, GameControllerDelegate.THUMBSTICK_RIGHT_X, newRightThumbstickX, true);
				}
				mOldRightThumbstickX = newRightThumbstickX;
			}
        	
        	float newRightThumbstickY = c.getAxisValue(OuyaController.AXIS_RS_Y);
        	if (Float.compare(newRightThumbstickY, mOldRightThumbstickY) != 0) {
				if (Float.compare(newRightThumbstickY, 0.0f) == 0) {
					mControllerEventListener.onAxisEvent(sVendorName, controllerID, GameControllerDelegate.THUMBSTICK_RIGHT_Y, 0.0f, true);
				}else {
					mControllerEventListener.onAxisEvent(sVendorName, controllerID, GameControllerDelegate.THUMBSTICK_RIGHT_Y, newRightThumbstickY, true);
				}
				mOldRightThumbstickY = newRightThumbstickY;
			}
        }
        
        return handled;
    }
    
    public boolean dispatchKeyEvent(KeyEvent event) {
    	boolean handled = false;
    	int action = event.getAction();
    	int keyCode = event.getKeyCode();
    	
    	if (action == KeyEvent.ACTION_DOWN) {
    		handled = OuyaController.onKeyDown(keyCode, event);
		}
    	else if (action == KeyEvent.ACTION_UP) {
    		handled = OuyaController.onKeyUp(keyCode, event);
		}
    	
    	if (handled && mControllerEventListener != null) {
    		boolean isAnalog = false;
    		
    		if (keyCode == KeyEvent.KEYCODE_BUTTON_THUMBL || keyCode == KeyEvent.KEYCODE_BUTTON_THUMBR){
    			isAnalog = true;
    		}
    		
    		int controllerID = OuyaController.getPlayerNumByDeviceId(event.getDeviceId());
    		if (action == KeyEvent.ACTION_DOWN) {
    			mControllerEventListener.onButtonEvent(sVendorName, controllerID, mKeyMap.get(keyCode), true, 1.0f, isAnalog);
			}else {
				mControllerEventListener.onButtonEvent(sVendorName, controllerID, mKeyMap.get(keyCode), false, 0.0f, isAnalog);
			}
		}
    	
    	return handled;
    }
    
	public void onPause() {
        // show the mouse cursor
        OuyaController.showCursor(true);
	}
	
	public void onResume() {
        // hide the mouse cursor
        OuyaController.showCursor(false);
	}
	
	public void onDestroy() {
		
	}

	private ControllerEventListener mControllerEventListener;
	
	@Override
	public void setControllerEventListener(ControllerEventListener listener) {
		mControllerEventListener = listener;
	}
	
}
