/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

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
