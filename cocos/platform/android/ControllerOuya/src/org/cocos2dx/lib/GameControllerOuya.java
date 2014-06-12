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
        //sKeyMap.put(OuyaController.AXIS_LS_X, GameControllerDelegate.LEFT_THUMBSTICK_X);
        //sKeyMap.put(OuyaController.AXIS_LS_Y, GameControllerDelegate.LEFT_THUMBSTICK_Y);
        //sKeyMap.put(OuyaController.AXIS_RS_X, GameControllerDelegate.RIGHT_THUMBSTICK_X);
        //sKeyMap.put(OuyaController.AXIS_RS_Y, GameControllerDelegate.RIGHT_THUMBSTICK_Y);
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

    public boolean onGenericMotionEvent(MotionEvent event) {
        boolean handled = false;

        handled = OuyaController.onGenericMotionEvent(event);

        if (handled && mControllerEventListener != null)
        {
        	OuyaController c = OuyaController.getControllerByDeviceId(event.getDeviceId());
        	int controllerID = OuyaController.getPlayerNumByDeviceId(event.getDeviceId());
        	
        	mControllerEventListener.onAxisEvent(sVendorName, controllerID, GameControllerDelegate.BUTTON_LEFT_TRIGGER, c.getAxisValue(OuyaController.AXIS_L2), true);
        	mControllerEventListener.onAxisEvent(sVendorName, controllerID, GameControllerDelegate.BUTTON_RIGHT_TRIGGER, c.getAxisValue(OuyaController.AXIS_R2), true);
        	
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
}
