package org.cocos2dx.lib;

import java.util.ArrayList;

public class GameControllerAdapter {
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
