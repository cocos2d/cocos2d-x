package org.cocos2dx.lib;

import java.util.ArrayList;

public class GameControllerAdapter {
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
	
	private static ArrayList<Runnable> sRunnableFrameStartList = null;
	
	public static void addRunnableToFrameStartList(Runnable runnable) {
		if (sRunnableFrameStartList == null)
			sRunnableFrameStartList = new ArrayList<Runnable>();
		sRunnableFrameStartList.add(runnable);
	}

	public static void removeRunnableFromFrameStartList(Runnable runnable) {
		if (sRunnableFrameStartList != null)
			sRunnableFrameStartList.remove(runnable);
	}

	public static void onDrawFrameStart() {
		if (sRunnableFrameStartList != null)
		{
			int size = sRunnableFrameStartList.size();
			for (int i = 0; i < size; ++i) {
				sRunnableFrameStartList.get(i).run();
			}
		}
	}	
	
	public static void checkConnectedControllers() {
//		for(int deviceId: InputDevice.getDeviceIds()) {
//			InputDevice device = InputDevice.getDevice(deviceId);
//			Cocos2dxGameController.onConnected(vendorName, deviceId);
//		}
	}
	
	public static void onConnected(final String vendorName, final int controller)
	{
		Cocos2dxHelper.runOnGLThread(new Runnable() {

			@Override
			public void run() {
				nativeControllerConnected(vendorName, controller);
			}	
		});
	}
	
	public static void onDisconnected(final String vendorName, final int controller)
	{
		Cocos2dxHelper.runOnGLThread(new Runnable() {

			@Override
			public void run() {
				nativeControllerDisconnected(vendorName, controller);
			}	
		});
	}
	
	public static void onButtonEvent(final String vendorName, final int controller, final int button, final boolean isPressed, final float value, final boolean isAnalog)
	{
		Cocos2dxHelper.runOnGLThread(new Runnable() {

			@Override
			public void run() {
				nativeControllerButtonEvent(vendorName, controller, button, isPressed, value, isAnalog);
			}	
		});
	}
	
	public static void onAxisEvent(final String vendorName, final int controller, final int axisID, final float value, final boolean isAnalog)
	{
		Cocos2dxHelper.runOnGLThread(new Runnable() {

			@Override
			public void run() {
				nativeControllerAxisEvent(vendorName, controller, axisID, value, isAnalog);
			}	
		});
	}
	
	private static native void nativeControllerConnected(final String vendorName, final int controller);
	private static native void nativeControllerDisconnected(final String vendorName, final int controller);
	private static native void nativeControllerButtonEvent(final String vendorName, final int controller, final int button, final boolean isPressed, final float value, final boolean isAnalog);
	private static native void nativeControllerAxisEvent(final String vendorName, final int controller, final int axisID, final float value, final boolean isAnalog);
}
