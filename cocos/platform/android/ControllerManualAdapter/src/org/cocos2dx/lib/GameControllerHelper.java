package org.cocos2dx.lib;

import android.util.Log;
import android.util.SparseIntArray;
import android.view.InputDevice;
import android.view.KeyEvent;
import android.view.MotionEvent;

public class GameControllerHelper {

	public static final String StandardControllerName = "Standard";	
	
	SparseIntArray ControllerKeyMap;
	
	private static final int AXIS_X = 0;
	private static final int AXIS_Y = 1;
	private static final int AXIS_Z = 11;
	private static final int AXIS_RZ = 14;
	private static final int AXIS_LTRIGGER = 17;
	private static final int AXIS_RTRIGGER = 18;
	public static final int AXIS_GAS = 22;
	private static final int AXIS_BRAKE = 23;
	private static final int AXIS_THROTTLE = 19;
	
	public GameControllerHelper(GameControllerActivity activity){
		
		ControllerKeyMap = new SparseIntArray(25);
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_A, GameControllerDelegate.BUTTON_A);
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_B, GameControllerDelegate.BUTTON_B);
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_C, GameControllerDelegate.BUTTON_C);
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_X, GameControllerDelegate.BUTTON_X);
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_Y, GameControllerDelegate.BUTTON_Y);
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_Z, GameControllerDelegate.BUTTON_Z);
		
		ControllerKeyMap.put(KeyEvent.KEYCODE_DPAD_UP, GameControllerDelegate.BUTTON_DPAD_UP);
		ControllerKeyMap.put(KeyEvent.KEYCODE_DPAD_DOWN, GameControllerDelegate.BUTTON_DPAD_DOWN);
		ControllerKeyMap.put(KeyEvent.KEYCODE_DPAD_LEFT, GameControllerDelegate.BUTTON_DPAD_LEFT);
		ControllerKeyMap.put(KeyEvent.KEYCODE_DPAD_RIGHT, GameControllerDelegate.BUTTON_DPAD_RIGHT);
		ControllerKeyMap.put(KeyEvent.KEYCODE_DPAD_CENTER, GameControllerDelegate.BUTTON_DPAD_CENTER);
		
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_THUMBL, GameControllerDelegate.BUTTON_LEFT_THUMBSTICK);
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_THUMBR, GameControllerDelegate.BUTTON_RIGHT_THUMBSTICK);
		
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_L1, GameControllerDelegate.BUTTON_LEFT_SHOULDER);
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_R1, GameControllerDelegate.BUTTON_RIGHT_SHOULDER);
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_L2, GameControllerDelegate.BUTTON_LEFT_TRIGGER);
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_R2, GameControllerDelegate.BUTTON_RIGHT_TRIGGER);
				
		ControllerKeyMap.put(AXIS_X, GameControllerDelegate.THUMBSTICK_LEFT_X);
		ControllerKeyMap.put(AXIS_Y, GameControllerDelegate.THUMBSTICK_LEFT_Y);
		ControllerKeyMap.put(AXIS_Z, GameControllerDelegate.THUMBSTICK_RIGHT_X);
		ControllerKeyMap.put(AXIS_RZ, GameControllerDelegate.THUMBSTICK_RIGHT_Y);
		
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_START, GameControllerDelegate.BUTTON_START);
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_SELECT, GameControllerDelegate.BUTTON_SELECT);
		//KEYCODE_BUTTON_MODE
	}
	
	private float mOldLeftThumbstickX = 0.0f;
	private float mOldLeftThumbstickY = 0.0f;
	private float mOldRightThumbstickX = 0.0f;
	private float mOldRightThumbstickY = 0.0f;
	
	private float mOldLeftTrigger = 0.0f;
	private float mOldRightTrigger = 0.0f;
	private float mOldThrottle = 0.0f;
	private float mOldBrake = 0.0f;
	private float mOldGas = 0.0f;
	
	public boolean dispatchGenericMotionEvent(MotionEvent event) {		
		boolean handled = false;
		
		int eventSource = event.getSource();
		
        if ( ((eventSource & InputDevice.SOURCE_GAMEPAD)  == InputDevice.SOURCE_GAMEPAD) 
        		|| ((eventSource & InputDevice.SOURCE_JOYSTICK) == InputDevice.SOURCE_JOYSTICK) )
        {       	
        	if (event.getAction() == MotionEvent.ACTION_MOVE) {
        		int devicedId = event.getDeviceId();
        		String deviceName = event.getDevice().getName();
        		
        		float newAXIS_LX = event.getAxisValue(AXIS_X);
        		if (Float.compare(newAXIS_LX , mOldLeftThumbstickX) != 0) {
					GameControllerAdapter.onAxisEvent(deviceName, devicedId, GameControllerDelegate.THUMBSTICK_LEFT_X, newAXIS_LX, true);
					mOldLeftThumbstickX = newAXIS_LX;
					handled = true;
				}
        		
        		float newAXIS_LY = event.getAxisValue(AXIS_Y);
        		if (Float.compare(newAXIS_LY , mOldLeftThumbstickY) != 0) {
					GameControllerAdapter.onAxisEvent(deviceName, devicedId, GameControllerDelegate.THUMBSTICK_LEFT_Y, newAXIS_LY, true);
					mOldLeftThumbstickY = newAXIS_LY;
					handled = true;
				}
        		
        		float newAXIS_RX = event.getAxisValue(AXIS_Z);
        		if (Float.compare(newAXIS_RX , mOldRightThumbstickX) != 0) {
					GameControllerAdapter.onAxisEvent(deviceName, devicedId, GameControllerDelegate.THUMBSTICK_RIGHT_X, newAXIS_RX, true);
					mOldRightThumbstickX = newAXIS_RX;
					handled = true;
				}
        		
        		float newAXIS_RY = event.getAxisValue(AXIS_RZ);
        		if (Float.compare(newAXIS_RY , mOldRightThumbstickY) != 0) {
					GameControllerAdapter.onAxisEvent(deviceName, devicedId, GameControllerDelegate.THUMBSTICK_RIGHT_Y, newAXIS_RY, true);
					mOldRightThumbstickY = newAXIS_RY;
					handled = true;
				}
        		
        		float newAXIS_LTRIGGER = event.getAxisValue(AXIS_LTRIGGER);
        		if (Float.compare(newAXIS_LTRIGGER , mOldLeftTrigger) != 0) {					
        			GameControllerAdapter.onAxisEvent(deviceName, devicedId, GameControllerDelegate.BUTTON_LEFT_TRIGGER, newAXIS_LTRIGGER, true);
					mOldLeftTrigger = newAXIS_LTRIGGER;
					handled = true;
				}
        		
        		float newAXIS_RTRIGGER = event.getAxisValue(AXIS_RTRIGGER);
        		if (Float.compare(newAXIS_RTRIGGER , mOldRightTrigger) != 0) {
        			GameControllerAdapter.onAxisEvent(deviceName, devicedId, GameControllerDelegate.BUTTON_RIGHT_TRIGGER, newAXIS_RTRIGGER, true);
					mOldRightTrigger = newAXIS_RTRIGGER;
					handled = true;
				}
        		
        		float newAXIS_BRAKE = event.getAxisValue(AXIS_BRAKE);
        		if (Float.compare(newAXIS_BRAKE , mOldBrake) != 0) {
        			GameControllerAdapter.onAxisEvent(deviceName, devicedId, GameControllerDelegate.BUTTON_LEFT_TRIGGER, newAXIS_BRAKE, true);
					mOldBrake = newAXIS_BRAKE;
					handled = true;
				}
        		
        		float newAXIS_THROTTLE = event.getAxisValue(AXIS_THROTTLE);
        		if (Float.compare(newAXIS_THROTTLE , mOldThrottle) != 0) {
        			GameControllerAdapter.onAxisEvent(deviceName, devicedId, GameControllerDelegate.BUTTON_RIGHT_TRIGGER, newAXIS_THROTTLE, true);
					mOldThrottle = newAXIS_THROTTLE;
					handled = true;
				}
        		
        		float newAXIS_GAS = event.getAxisValue(AXIS_GAS);
        		if (Float.compare(newAXIS_GAS , mOldGas) != 0) {
        			GameControllerAdapter.onAxisEvent(deviceName, devicedId, GameControllerDelegate.BUTTON_RIGHT_TRIGGER, newAXIS_GAS, true);
        			mOldGas = newAXIS_GAS;
					handled = true;
				}
			} 	
        }
        
		return handled;
	}
	
	public boolean dispatchKeyEvent(KeyEvent event) {
    	boolean handled = false;
    	
    	int eventSource = event.getSource();
    	int keyCode = event.getKeyCode();
		int controllerKey = ControllerKeyMap.get(keyCode);
		
		if (controllerKey != 0 && (((eventSource & InputDevice.SOURCE_GAMEPAD) == InputDevice.SOURCE_GAMEPAD)
				|| ((eventSource & InputDevice.SOURCE_JOYSTICK) == InputDevice.SOURCE_JOYSTICK) )) 
		{
			int action = event.getAction();
			if (action == KeyEvent.ACTION_DOWN) {
				handled = true;
				GameControllerAdapter.onButtonEvent(event.getDevice().getName(),event.getDeviceId(), controllerKey,true, 1.0f, false);
			}else if (action == KeyEvent.ACTION_UP) {
				handled = true;
				GameControllerAdapter.onButtonEvent(event.getDevice().getName(),event.getDeviceId(), controllerKey,false, 0.0f, false);
			}
		}
		
    	return handled;
    }
}
