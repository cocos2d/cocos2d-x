package org.cocos2dx.lib;


import org.cocos2dx.lib.GameControllerDelegate;

import tv.ouya.console.api.OuyaController;
import android.content.Context;
import android.util.SparseIntArray;
import android.view.KeyEvent;
import android.view.MotionEvent;

public class GameControllerOuya implements GameControllerDelegate{

	public static String sVendorName = "Ouya";
	
	private SparseIntArray mKeyMap = null;
    
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
    
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        boolean handled = false;

        handled = OuyaController.onKeyDown(keyCode, event);

        if (handled && mControllerEventListener != null)
        {
    		int keycode = event.getKeyCode();
    		boolean isAnalog = false;
    		
    		if (keycode == KeyEvent.KEYCODE_BUTTON_THUMBL || keycode == KeyEvent.KEYCODE_BUTTON_THUMBR)
    		{
    			isAnalog = true;
    		}
    		
    		if (mKeyMap.get(keyCode, Integer.MIN_VALUE) != Integer.MIN_VALUE)
    		{
    			int controllerID = OuyaController.getPlayerNumByDeviceId(event.getDeviceId());
    			mControllerEventListener.onButtonEvent(sVendorName, controllerID, mKeyMap.get(keycode), true, 1.0f, isAnalog);
    		}
        }

        return handled; 
    }

    public boolean onKeyUp(int keyCode, KeyEvent event) {
        boolean handled = false;
        handled = OuyaController.onKeyUp(keyCode, event);
    
        if (handled && mControllerEventListener != null)
        {
    		int keycode = event.getKeyCode();
    		boolean isAnalog = false;
    		
    		if (keycode == KeyEvent.KEYCODE_BUTTON_THUMBL || keycode == KeyEvent.KEYCODE_BUTTON_THUMBR)
    		{
    			isAnalog = true;
    		}
    		
        	int controllerID = OuyaController.getPlayerNumByDeviceId(event.getDeviceId());
        	mControllerEventListener.onButtonEvent(sVendorName, controllerID, mKeyMap.get(keycode), false, 0.0f, isAnalog);
        }

        return handled;
    }

    private float mOldLeftThumbstickX = 0.0f;
	private float mOldLeftThumbstickY = 0.0f;
	private float mOldRightThumbstickX = 0.0f;
	private float mOldRightThumbstickY = 0.0f;
	
    private float mOldLeftTrigger = 0.0f;
	private float mOldRightTrigger = 0.0f;
	
    public boolean onGenericMotionEvent(MotionEvent event) {
        boolean handled = false;

        handled = OuyaController.onGenericMotionEvent(event);

        if (handled && mControllerEventListener != null)
        {
        	OuyaController c = OuyaController.getControllerByDeviceId(event.getDeviceId());
        	int controllerID = OuyaController.getPlayerNumByDeviceId(event.getDeviceId());
        	
        	float newLeftTrigger = c.getAxisValue(OuyaController.AXIS_L2);
        	if (Float.compare(newLeftTrigger, mOldLeftTrigger) != 0) {
				if (Float.compare(newLeftTrigger, 0.0f) == 0) {
					mControllerEventListener.onButtonEvent(sVendorName, controllerID, GameControllerDelegate.BUTTON_LEFT_TRIGGER, false, 0.0f, true);
				}else {
					mControllerEventListener.onButtonEvent(sVendorName, controllerID, GameControllerDelegate.BUTTON_LEFT_TRIGGER, true, newLeftTrigger, true);
				}
				mOldLeftTrigger = newLeftTrigger;
			}
        	
        	float newRightTrigger = c.getAxisValue(OuyaController.AXIS_R2);
        	if (Float.compare(newRightTrigger, mOldRightTrigger) != 0) {
				if (Float.compare(newRightTrigger, 0.0f) == 0) {
					mControllerEventListener.onButtonEvent(sVendorName, controllerID, GameControllerDelegate.BUTTON_RIGHT_TRIGGER, false, 0.0f, true);
				}else {
					mControllerEventListener.onButtonEvent(sVendorName, controllerID, GameControllerDelegate.BUTTON_RIGHT_TRIGGER, true, newRightTrigger, true);
				}
				mOldRightTrigger = newRightTrigger;
			}
        	
        	float newLeftThumbstickX = c.getAxisValue(OuyaController.AXIS_LS_X);
        	if (Float.compare(newLeftThumbstickX, mOldLeftThumbstickX) != 0) {
				if (Float.compare(newLeftThumbstickX, 0.0f) == 0) {
					mControllerEventListener.onButtonEvent(sVendorName, controllerID, GameControllerDelegate.THUMBSTICK_LEFT_X, false, 0.0f, true);
				}else {
					mControllerEventListener.onButtonEvent(sVendorName, controllerID, GameControllerDelegate.THUMBSTICK_LEFT_X, true, newLeftThumbstickX, true);
				}
				mOldLeftThumbstickX = newLeftThumbstickX;
			}
        	
        	//GameControllerAdapter.onAxisEvent(sVendorName, controllerID, GameControllerAdapter.LEFT_THUMBSTICK_X, c.getAxisValue(OuyaController.AXIS_LS_X), true);
        	//GameControllerAdapter.onAxisEvent(sVendorName, controllerID, GameControllerAdapter.LEFT_THUMBSTICK_Y, c.getAxisValue(OuyaController.AXIS_LS_Y), true);
        	//GameControllerAdapter.onAxisEvent(sVendorName, controllerID, GameControllerAdapter.RIGHT_THUMBSTICK_X, c.getAxisValue(OuyaController.AXIS_RS_X), true);
        	//GameControllerAdapter.onAxisEvent(sVendorName, controllerID, GameControllerAdapter.RIGHT_THUMBSTICK_Y, c.getAxisValue(OuyaController.AXIS_RS_Y), true);
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

	@Override
	public boolean dispatchKeyEvent(KeyEvent event) {
		return false;
	}

	@Override
	public boolean dispatchGenericMotionEvent(MotionEvent event) {
		return false;
	}
}
