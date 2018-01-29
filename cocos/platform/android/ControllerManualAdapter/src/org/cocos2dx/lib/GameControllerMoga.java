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

import android.content.Context;
import android.os.Handler;
import android.util.SparseIntArray;

import com.bda.controller.Controller;
import com.bda.controller.ControllerListener;
import com.bda.controller.KeyEvent;
import com.bda.controller.MotionEvent;
import com.bda.controller.StateEvent;

public class GameControllerMoga implements ControllerListener, GameControllerDelegate {

    private static final String mVendorName = "Moga";
    
    private float mOldLeftThumbstickX = 0.0f;
    private float mOldLeftThumbstickY = 0.0f;
    private float mOldRightThumbstickX = 0.0f;
    private float mOldRightThumbstickY = 0.0f;
    
    private float mOldLeftTrigger = 0.0f;
    private float mOldRightTrigger = 0.0f;

    private SparseIntArray mKeyMap = null;

    public GameControllerMoga() {
        mKeyMap = new SparseIntArray(20);
        mKeyMap.put(KeyEvent.KEYCODE_BUTTON_A, GameControllerDelegate.BUTTON_A);
        mKeyMap.put(KeyEvent.KEYCODE_BUTTON_B, GameControllerDelegate.BUTTON_B);
        mKeyMap.put(KeyEvent.KEYCODE_BUTTON_X, GameControllerDelegate.BUTTON_X);
        mKeyMap.put(KeyEvent.KEYCODE_BUTTON_Y, GameControllerDelegate.BUTTON_Y);
        
        mKeyMap.put(KeyEvent.KEYCODE_BUTTON_L1,
                GameControllerDelegate.BUTTON_LEFT_SHOULDER);
        mKeyMap.put(KeyEvent.KEYCODE_BUTTON_R1,
                GameControllerDelegate.BUTTON_RIGHT_SHOULDER);
        mKeyMap.put(KeyEvent.KEYCODE_BUTTON_L2,
                GameControllerDelegate.BUTTON_LEFT_TRIGGER);
        mKeyMap.put(KeyEvent.KEYCODE_BUTTON_R2,
                GameControllerDelegate.BUTTON_RIGHT_TRIGGER);
        
        mKeyMap.put(KeyEvent.KEYCODE_DPAD_UP,
                GameControllerDelegate.BUTTON_DPAD_UP);
        mKeyMap.put(KeyEvent.KEYCODE_DPAD_DOWN,
                GameControllerDelegate.BUTTON_DPAD_DOWN);
        mKeyMap.put(KeyEvent.KEYCODE_DPAD_LEFT,
                GameControllerDelegate.BUTTON_DPAD_LEFT);
        mKeyMap.put(KeyEvent.KEYCODE_DPAD_RIGHT,
                GameControllerDelegate.BUTTON_DPAD_RIGHT);
        
        mKeyMap.put(KeyEvent.KEYCODE_BUTTON_START,
                GameControllerDelegate.BUTTON_START);
        mKeyMap.put(KeyEvent.KEYCODE_BUTTON_SELECT,
                GameControllerDelegate.BUTTON_SELECT);
        mKeyMap.put(KeyEvent.KEYCODE_BUTTON_START,
                GameControllerDelegate.BUTTON_START);
        mKeyMap.put(KeyEvent.KEYCODE_BUTTON_THUMBL,
                GameControllerDelegate.BUTTON_LEFT_THUMBSTICK);
        mKeyMap.put(KeyEvent.KEYCODE_BUTTON_THUMBR,
                GameControllerDelegate.BUTTON_RIGHT_THUMBSTICK);
    }
    
    public void onKeyEvent(KeyEvent event) {        
        int keycode = event.getKeyCode();
        if (keycode == KeyEvent.KEYCODE_BUTTON_L2
                || keycode == KeyEvent.KEYCODE_BUTTON_R2) {
            return;
        }
        boolean isPressed = event.getAction() == KeyEvent.ACTION_DOWN;
        boolean isAnalog = false;

        if (keycode == KeyEvent.KEYCODE_BUTTON_THUMBL
                || keycode == KeyEvent.KEYCODE_BUTTON_THUMBR) {
            isAnalog = true;
        }

        if (mKeyMap.get(keycode, Integer.MIN_VALUE) != Integer.MIN_VALUE && mControllerEventListener != null) {
            mControllerEventListener.onButtonEvent(mVendorName,
                    event.getControllerId(), mKeyMap.get(keycode), isPressed,
                    isPressed ? 1.0f : 0.0f, isAnalog);
        }
    }

    @Override
    public void onMotionEvent(MotionEvent event) {
        if (mControllerEventListener == null) {
            return;
        }
        int controllerId = event.getControllerId();
        
        float newLeftThumbstickX = event.getAxisValue(MotionEvent.AXIS_X);
        if (newLeftThumbstickX != mOldLeftThumbstickX) {
            mControllerEventListener.onAxisEvent(mVendorName,
                    controllerId,
                    GameControllerDelegate.THUMBSTICK_LEFT_X,
                    newLeftThumbstickX, true);
            mOldLeftThumbstickX = newLeftThumbstickX;
        }

        float newLeftThumbstickY = event.getAxisValue(MotionEvent.AXIS_Y);
        if (newLeftThumbstickY != mOldLeftThumbstickY) {
            mControllerEventListener.onAxisEvent(mVendorName,
                    controllerId,
                    GameControllerDelegate.THUMBSTICK_LEFT_Y,
                    newLeftThumbstickY, true);
            mOldLeftThumbstickY = newLeftThumbstickY;
        }

        float newRightThumbstickX = event.getAxisValue(MotionEvent.AXIS_Z);
        if (newRightThumbstickX != mOldRightThumbstickX) {
            mControllerEventListener.onAxisEvent(mVendorName,
                    controllerId,
                    GameControllerDelegate.THUMBSTICK_RIGHT_X,
                    newRightThumbstickX, true);
            mOldRightThumbstickX = newRightThumbstickX;
        }

        float newRightThumbstickY = event.getAxisValue(MotionEvent.AXIS_RZ);
        if (newRightThumbstickY != mOldRightThumbstickY) {
            mControllerEventListener.onAxisEvent(mVendorName,
                    controllerId,
                    GameControllerDelegate.THUMBSTICK_RIGHT_Y,
                    newRightThumbstickY, true);
            mOldRightThumbstickY = newRightThumbstickY;
        }
        
        float newLeftTrigger = event.getAxisValue(MotionEvent.AXIS_LTRIGGER);
        if (newLeftTrigger != mOldLeftTrigger) {
            mControllerEventListener.onAxisEvent(mVendorName,
                    controllerId,
                    GameControllerDelegate.BUTTON_LEFT_TRIGGER,
                    newLeftTrigger, true);
            mOldLeftTrigger = newLeftTrigger;
        }
        
        float newRightTrigger = event.getAxisValue(MotionEvent.AXIS_RTRIGGER);
        if (newRightTrigger != mOldRightTrigger) {
            mControllerEventListener.onAxisEvent(mVendorName,
                    controllerId,
                    GameControllerDelegate.BUTTON_RIGHT_TRIGGER,
                    newRightTrigger, true);
            mOldRightTrigger = newRightTrigger;
        }
    }

    @Override
    public void onStateEvent(StateEvent event) {
        if (mControllerEventListener != null) {
            switch (event.getState()) {
            case StateEvent.STATE_CONNECTION:
                switch (event.getAction()) {
                case StateEvent.ACTION_DISCONNECTED:
                    // disconnected from controller
                    mControllerEventListener.onDisconnected(mVendorName,
                            event.getControllerId());
                    break;
                case StateEvent.ACTION_CONNECTED:
                    // connected to controller
                    mControllerEventListener.onConnected(mVendorName,
                            event.getControllerId());
                    break;
                case StateEvent.ACTION_CONNECTING:
                    // attempting to connect to controller
                    break;
                }
                break;
            case StateEvent.STATE_POWER_LOW:
                if (event.getAction() == StateEvent.ACTION_TRUE) {
                    // controller has entered low power state
                } else {
                    // controller has entered normal power state
                }
                break;
            }
        }
    }

    private Controller mController = null;

    public void onCreate(Context context) {
        mController = Controller.getInstance(context);
        
        mController.init();
        mController.setListener(this, new Handler());
    }

    public void onPause() {
        mController.onPause();
    }

    public void onResume() {
        mController.onResume();
    }

    public void onDestroy() {
        mController.exit();
    }
    
    private ControllerEventListener mControllerEventListener;
    @Override
    public void setControllerEventListener(ControllerEventListener listener) {
        mControllerEventListener = listener;
    }

    @Override
    public boolean dispatchKeyEvent(android.view.KeyEvent event) {
        return false;
    }

    @Override
    public boolean dispatchGenericMotionEvent(android.view.MotionEvent event) {
        return false;
    }

}
