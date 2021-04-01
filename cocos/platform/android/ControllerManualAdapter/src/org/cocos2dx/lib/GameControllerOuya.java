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


import org.cocos2dx.lib.GameControllerDelegate;

import tv.ouya.console.api.OuyaController;
import android.content.Context;
import android.util.SparseArray;
import android.util.SparseIntArray;
import android.view.KeyEvent;
import android.view.MotionEvent;

public class GameControllerOuya implements GameControllerDelegate{
    
    private SparseIntArray mKeyMap;
    
    private SparseArray<String> mGameController = new SparseArray<String>();
    
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
        
        mKeyMap.put(OuyaController.BUTTON_L3, GameControllerDelegate.BUTTON_LEFT_THUMBSTICK);
        mKeyMap.put(OuyaController.BUTTON_R3, GameControllerDelegate.BUTTON_RIGHT_THUMBSTICK);
    }
    
    public void onCreate(Context context) {
        OuyaController.init(context);
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
            int deviceId = event.getDeviceId();
            String deviceName = event.getDevice().getName();
            OuyaController c = OuyaController.getControllerByDeviceId(deviceId);
            if (mGameController.get(deviceId) == null) {
                GameControllerHelper.gatherControllers(mGameController);
                mGameController.append(deviceId, deviceName);
            }
            
            float newLeftTrigger = c.getAxisValue(OuyaController.AXIS_L2);
            if (Float.compare(newLeftTrigger, mOldLeftTrigger) != 0) {
                mControllerEventListener.onAxisEvent(deviceName, deviceId, GameControllerDelegate.BUTTON_LEFT_TRIGGER, newLeftTrigger, true);
                mOldLeftTrigger = newLeftTrigger;
            }
            
            float newRightTrigger = c.getAxisValue(OuyaController.AXIS_R2);
            if (Float.compare(newRightTrigger, mOldRightTrigger) != 0) {
                mControllerEventListener.onAxisEvent(deviceName, deviceId, GameControllerDelegate.BUTTON_RIGHT_TRIGGER, newRightTrigger, true);
                mOldRightTrigger = newRightTrigger;
            }
            
            float newLeftThumbstickX = c.getAxisValue(OuyaController.AXIS_LS_X);
            if (Float.compare(newLeftThumbstickX, mOldLeftThumbstickX) != 0) {
                if (Float.compare(newLeftThumbstickX, 0.0f) == 0) {
                    mControllerEventListener.onAxisEvent(deviceName, deviceId, GameControllerDelegate.THUMBSTICK_LEFT_X, 0.0f, true);
                }else {
                    mControllerEventListener.onAxisEvent(deviceName, deviceId, GameControllerDelegate.THUMBSTICK_LEFT_X, newLeftThumbstickX, true);
                }
                mOldLeftThumbstickX = newLeftThumbstickX;
            }
            
            float newLeftThumbstickY = c.getAxisValue(OuyaController.AXIS_LS_Y);
            if (Float.compare(newLeftThumbstickY, mOldLeftThumbstickY) != 0) {
                if (Float.compare(newLeftThumbstickY, 0.0f) == 0) {
                    mControllerEventListener.onAxisEvent(deviceName, deviceId, GameControllerDelegate.THUMBSTICK_LEFT_Y, 0.0f, true);
                }else {
                    mControllerEventListener.onAxisEvent(deviceName, deviceId, GameControllerDelegate.THUMBSTICK_LEFT_Y, newLeftThumbstickY, true);
                }
                mOldLeftThumbstickY = newLeftThumbstickY;
            }
            
            float newRightThumbstickX = c.getAxisValue(OuyaController.AXIS_RS_X);
            if (Float.compare(newRightThumbstickX, mOldRightThumbstickX) != 0) {
                if (Float.compare(newRightThumbstickX, 0.0f) == 0) {
                    mControllerEventListener.onAxisEvent(deviceName, deviceId, GameControllerDelegate.THUMBSTICK_RIGHT_X, 0.0f, true);
                }else {
                    mControllerEventListener.onAxisEvent(deviceName, deviceId, GameControllerDelegate.THUMBSTICK_RIGHT_X, newRightThumbstickX, true);
                }
                mOldRightThumbstickX = newRightThumbstickX;
            }
            
            float newRightThumbstickY = c.getAxisValue(OuyaController.AXIS_RS_Y);
            if (Float.compare(newRightThumbstickY, mOldRightThumbstickY) != 0) {
                if (Float.compare(newRightThumbstickY, 0.0f) == 0) {
                    mControllerEventListener.onAxisEvent(deviceName, deviceId, GameControllerDelegate.THUMBSTICK_RIGHT_Y, 0.0f, true);
                }else {
                    mControllerEventListener.onAxisEvent(deviceName, deviceId, GameControllerDelegate.THUMBSTICK_RIGHT_Y, newRightThumbstickY, true);
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
            
            int deviceId = event.getDeviceId();
            String deviceName = event.getDevice().getName();
            
            if (mGameController.get(deviceId) == null) {
                GameControllerHelper.gatherControllers(mGameController);
                mGameController.append(deviceId, deviceName);
            }
            if (action == KeyEvent.ACTION_DOWN) {
                mControllerEventListener.onButtonEvent(deviceName, deviceId, mKeyMap.get(keyCode), true, 1.0f, isAnalog);
            }else {
                mControllerEventListener.onButtonEvent(deviceName, deviceId, mKeyMap.get(keyCode), false, 0.0f, isAnalog);
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
