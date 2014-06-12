package org.cocos2dx.lib;

import android.content.Context;
import android.view.KeyEvent;
import android.view.MotionEvent;

public abstract interface GameControllerDelegate {

	public static final int THUMBSTICK_LEFT_X = 101;//MotionEvent.AXIS_X;
    public static final int THUMBSTICK_LEFT_Y = 102;//MotionEvent.AXIS_Y;
    public static final int THUMBSTICK_RIGHT_X = 103;//MotionEvent.AXIS_RX;
    public static final int THUMBSTICK_RIGHT_Y = 104;//MotionEvent.AXIS_RY;
    public static final int BUTTON_A = 105;//KeyEvent.KEYCODE_BUTTON_A;
    public static final int BUTTON_B = 106;//KeyEvent.KEYCODE_BUTTON_B;
    public static final int BUTTON_X = 107;//KeyEvent.KEYCODE_BUTTON_X;
    public static final int BUTTON_Y = 108;//KeyEvent.KEYCODE_BUTTON_Y;
    public static final int BUTTON_LEFT_SHOULDER = 109;//KeyEvent.KEYCODE_BUTTON_L1;
    public static final int BUTTON_RIGHT_SHOULDER = 110;//KeyEvent.KEYCODE_BUTTON_R1;
    public static final int BUTTON_DPAD_UP = 111;//KeyEvent.KEYCODE_DPAD_UP;
    public static final int BUTTON_DPAD_DOWN = 112;//KeyEvent.KEYCODE_DPAD_DOWN;
    public static final int BUTTON_DPAD_LEFT = 113;//KeyEvent.KEYCODE_DPAD_LEFT;
    public static final int BUTTON_DPAD_RIGHT = 114;//KeyEvent.KEYCODE_DPAD_RIGHT;
    public static final int BUTTON_START = 115;//KeyEvent.KEYCODE_BUTTON_START;
    public static final int BUTTON_SELECT = 116;//KeyEvent.KEYCODE_BUTTON_SELECT;
    public static final int BUTTON_LEFT_THUMBSTICK = 117;//KeyEvent.KEYCODE_BUTTON_THUMBL;
    public static final int BUTTON_RIGHT_THUMBSTICK = 118;//KeyEvent.KEYCODE_BUTTON_THUMBR;
    public static final int BUTTON_LEFT_TRIGGER = 119;//KeyEvent.KEYCODE_BUTTON_L2;
    public static final int BUTTON_RIGHT_TRIGGER = 120;//KeyEvent.KEYCODE_BUTTON_R2;
    
	void onCreate(Context context);
	void onPause();
	void onResume();
	void onDestroy();
	
	boolean onKeyDown(int keyCode, KeyEvent event);
	boolean onKeyUp(int keyCode, KeyEvent event);
	boolean onGenericMotionEvent(MotionEvent event);
	
	void setControllerEventListener(ControllerEventListener listener);
	
	public interface ControllerEventListener{
		void onButtonEvent(String vendorName, int controller, int button, boolean isPressed, float value, boolean isAnalog);
		void onAxisEvent(String vendorName, int controller, int axisID, float value, boolean isAnalog);
		
		void onConnected(String vendorName, int controller);
		void onDisconnected(String vendorName, int controller);
		
	}
}
