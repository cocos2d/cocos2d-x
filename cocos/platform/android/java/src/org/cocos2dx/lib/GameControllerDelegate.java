package org.cocos2dx.lib;

import android.content.Context;
import android.view.KeyEvent;
import android.view.MotionEvent;

public interface GameControllerDelegate {

    static final int KEY_BASE = 1000;
    
    public static final int THUMBSTICK_LEFT_X = KEY_BASE;
    public static final int THUMBSTICK_LEFT_Y = KEY_BASE + 1;
    public static final int THUMBSTICK_RIGHT_X = KEY_BASE + 2;
    public static final int THUMBSTICK_RIGHT_Y = KEY_BASE + 3;
    
    public static final int BUTTON_A = KEY_BASE + 4;
    public static final int BUTTON_B = KEY_BASE + 5;
    public static final int BUTTON_C = KEY_BASE + 6;
    public static final int BUTTON_X = KEY_BASE + 7;
    public static final int BUTTON_Y = KEY_BASE + 8;
    public static final int BUTTON_Z = KEY_BASE + 9;
    
    public static final int BUTTON_DPAD_UP = KEY_BASE + 10;
    public static final int BUTTON_DPAD_DOWN = KEY_BASE + 11;
    public static final int BUTTON_DPAD_LEFT = KEY_BASE + 12;
    public static final int BUTTON_DPAD_RIGHT = KEY_BASE + 13;
    public static final int BUTTON_DPAD_CENTER = KEY_BASE + 14;
    
    public static final int BUTTON_LEFT_SHOULDER = KEY_BASE + 15;
    public static final int BUTTON_RIGHT_SHOULDER = KEY_BASE + 16;
    public static final int BUTTON_LEFT_TRIGGER = KEY_BASE + 17;
    public static final int BUTTON_RIGHT_TRIGGER = KEY_BASE + 18;
    
    public static final int BUTTON_LEFT_THUMBSTICK = KEY_BASE + 19;
    public static final int BUTTON_RIGHT_THUMBSTICK = KEY_BASE + 20;
    
    public static final int BUTTON_START = KEY_BASE + 21;
    public static final int BUTTON_SELECT = KEY_BASE + 22;  
    
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
