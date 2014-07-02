package org.cocos2dx.lib;

import android.content.Context;
import android.view.KeyEvent;
import android.view.MotionEvent;

public interface GameControllerDelegate {

	public static final int THUMBSTICK_LEFT_X = 100;
    public static final int THUMBSTICK_LEFT_Y = 101;
    public static final int THUMBSTICK_RIGHT_X = 102;
    public static final int THUMBSTICK_RIGHT_Y = 103;
    
    public static final int BUTTON_A = 110;
    public static final int BUTTON_B = 111;
    public static final int BUTTON_C = 112;
    public static final int BUTTON_X = 113;
    public static final int BUTTON_Y = 114;
    public static final int BUTTON_Z = 115;
    
    public static final int BUTTON_LEFT_SHOULDER = 120;
    public static final int BUTTON_RIGHT_SHOULDER = 121;
    public static final int BUTTON_LEFT_TRIGGER = 122;
    public static final int BUTTON_RIGHT_TRIGGER = 123;
    
    public static final int BUTTON_DPAD_UP = 130;
    public static final int BUTTON_DPAD_DOWN = 131;
    public static final int BUTTON_DPAD_LEFT = 132;
    public static final int BUTTON_DPAD_RIGHT = 133;
    public static final int BUTTON_DPAD_CENTER = 134;
    
    public static final int BUTTON_LEFT_THUMBSTICK = 140;
    public static final int BUTTON_RIGHT_THUMBSTICK = 141;
    
    public static final int BUTTON_START = 150;
    public static final int BUTTON_SELECT = 151;  
    
	void onCreate(Context context);
	void onPause();
	void onResume();
	void onDestroy();
	
	boolean dispatchKeyEvent(KeyEvent event);
	boolean dispatchGenericMotionEvent(MotionEvent event);
	
	void setControllerEventListener(ControllerEventListener listener);
	
	public interface ControllerEventListener {
		void onButtonEvent(String vendorName, int controller, int button, boolean isPressed, float value, boolean isAnalog);
		void onAxisEvent(String vendorName, int controller, int axisID, float value, boolean isAnalog);
		
		void onConnected(String vendorName, int controller);
		void onDisconnected(String vendorName, int controller);
	}
}
