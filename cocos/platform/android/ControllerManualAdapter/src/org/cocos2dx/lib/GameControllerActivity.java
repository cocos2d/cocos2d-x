/****************************************************************************
Copyright (c) 2010-2013 cocos2d-x.org

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

import java.lang.reflect.Method;

import org.cocos2dx.lib.GameControllerDelegate.ControllerEventListener;
import org.cocos2dx.lib.inputmanagercompat.InputManagerCompat;
import org.cocos2dx.lib.inputmanagercompat.InputManagerCompat.InputDeviceListener;
import org.cocos2dx.lib.Cocos2dxActivity;

import android.os.Bundle;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.util.Log;

public abstract class GameControllerActivity extends Cocos2dxActivity implements InputDeviceListener {
    // ===========================================================
    // Constants
    // ===========================================================

    private final static String TAG = GameControllerActivity.class.getSimpleName();

    public static final int DRIVERTYPE_NIBIRU = 0;
    public static final int DRIVERTYPE_MOGA = 1;
    public static final int DRIVERTYPE_OUYA = 2;
    public static final int DRIVERTYPE_STANDARD = 3;
    public static final int DRIVERTYPE_UNKNOWN = 4;
    
    // ===========================================================
    // Fields
    // ===========================================================
    private static GameControllerActivity sGameControllerActivity;
    private InputManagerCompat mInputManager = null;
    
    protected GameControllerHelper mControllerHelper = null;
    
    protected GameControllerDelegate mControllerNibiru = null;
    protected GameControllerDelegate mControllerMoga = null;
    protected GameControllerDelegate mControllerOuya = null;
    
    public void connectController(int driveType){
        try {
            
            ClassLoader loader = sGameControllerActivity.getClassLoader();
            Class<?> controllerDelegate = null;
            if (driveType == DRIVERTYPE_MOGA) {
                if (mControllerMoga != null) {
                    return;
                }
                controllerDelegate = loader.loadClass("org.cocos2dx.lib.GameControllerMoga");
            } else if (driveType == DRIVERTYPE_NIBIRU) {
                if (mControllerNibiru != null) {
                    mControllerNibiru.onCreate(sGameControllerActivity);
                    mControllerNibiru.onResume();
                    return;
                }
                controllerDelegate = loader.loadClass("org.cocos2dx.lib.GameControllerNibiru");
            } else if (driveType == DRIVERTYPE_OUYA) {
                if (mControllerOuya != null) {
                    return;
                }
                controllerDelegate = loader.loadClass("org.cocos2dx.lib.GameControllerOuya");
            }
            
            GameControllerDelegate instance = (GameControllerDelegate)controllerDelegate.newInstance();         
            sGameControllerActivity.setGameControllerInstance(instance, driveType);
            
            if (driveType == DRIVERTYPE_NIBIRU) {
                Method method = controllerDelegate.getDeclaredMethod("onResume");
                method.invoke(instance);
            }
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }
    
    public void setGameControllerInstance(GameControllerDelegate controllerDelegate, int driveType) {
        if (driveType == DRIVERTYPE_NIBIRU) {
            mControllerNibiru = controllerDelegate;
        }else if (driveType == DRIVERTYPE_MOGA) {
            mControllerMoga = controllerDelegate;
        }
        else if (driveType == DRIVERTYPE_OUYA) {
            mControllerOuya = controllerDelegate;
        }
        controllerDelegate.setControllerEventListener(mControllerEventListener);
        controllerDelegate.onCreate(sGameControllerActivity);
    }
    
    public GameControllerDelegate getGameControllerDelegate(int driveType){
        if (driveType == DRIVERTYPE_NIBIRU) {
            return mControllerNibiru;
        }else if (driveType == DRIVERTYPE_MOGA) {
            return mControllerMoga;
        }
        else if (driveType == DRIVERTYPE_OUYA) {
            return mControllerOuya;
        }
        
        return null;
    }
    
    ControllerEventListener mControllerEventListener = new ControllerEventListener() {
        
        @Override
        public void onButtonEvent(String vendorName, int controller, int button,
                boolean isPressed, float value, boolean isAnalog) {
            GameControllerAdapter.onButtonEvent(vendorName, controller, button, isPressed, value, isAnalog);
        }
        
        @Override
        public void onAxisEvent(String vendorName, int controller, int axisID,
                float value, boolean isAnalog) {
            GameControllerAdapter.onAxisEvent(vendorName, controller, axisID, value, isAnalog);
        }

        @Override
        public void onConnected(String vendorName, int controller) {
            GameControllerAdapter.onConnected(vendorName, controller);
        }

        @Override
        public void onDisconnected(String vendorName, int controller) {
            GameControllerAdapter.onDisconnected(vendorName, controller);
        }
    };
    
    // ===========================================================
    // Constructors
    // ===========================================================
    
    @Override
    protected void onCreate(final Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        sGameControllerActivity = this;
        mInputManager = InputManagerCompat.Factory.getInputManager(this);
        mInputManager.registerInputDeviceListener(this, null);
        
        if (mControllerNibiru != null) {
            mControllerNibiru.onCreate(this);
        }
        if (mControllerMoga != null) {
            mControllerMoga.onCreate(this);
        }
        if (mControllerOuya != null) {
            mControllerOuya.onCreate(this);
        }
        if (mControllerHelper == null) {
            mControllerHelper = new GameControllerHelper(this);
        }
    }
    
    // ===========================================================
    // Getter & Setter
    // ===========================================================

    // ===========================================================
    // Methods for/from SuperClass/Interfaces
    // ===========================================================

    @Override
    public boolean dispatchKeyEvent(KeyEvent event) {
        boolean handled = false; 
        if (mControllerNibiru != null) {
            handled |= mControllerNibiru.dispatchKeyEvent(event);
        }
        if (handled == false && mControllerMoga != null) {
            handled |= mControllerMoga.dispatchKeyEvent(event);
        }
        if (handled == false && mControllerOuya != null) {
            handled |= mControllerOuya.dispatchKeyEvent(event);
        }
        
        if (handled == false) {
            handled |= mControllerHelper.dispatchKeyEvent(event);
        }
        
        return handled || super.dispatchKeyEvent(event);
    }
    
    @Override
    public boolean dispatchGenericMotionEvent(MotionEvent event) {
        boolean handled = false;
        if (mControllerNibiru != null) {
            handled |= mControllerNibiru.dispatchGenericMotionEvent(event);
        }
        if (handled == false && mControllerMoga != null) {
            handled |= mControllerMoga.dispatchGenericMotionEvent(event);
        }
        if (handled == false && mControllerOuya != null) {
            handled |= mControllerOuya.dispatchGenericMotionEvent(event);
        }
        
        if (handled == false) {
            handled |= mControllerHelper.dispatchGenericMotionEvent(event);
        }
        
        return handled || super.dispatchGenericMotionEvent(event);
    }
    
    @Override
    public void onInputDeviceAdded(int deviceId) {  
        Log.d(TAG,"onInputDeviceAdded:" + deviceId);
        
        mControllerHelper.onInputDeviceAdded(deviceId);
    }
    /*
     * This is an unusual case. Input devices don't typically change, but they
     * certainly can --- for example a device may have different modes. We use
     * this to make sure that the ship has an up-to-date InputDevice.
     * 
     * @see
     * com.example.inputmanagercompat.InputManagerCompat.InputDeviceListener
     * #onInputDeviceChanged(int)
     */
    @Override
    public void onInputDeviceChanged(int deviceId) {
        Log.w(TAG,"onInputDeviceChanged:" + deviceId);
    }
    
    /*
     * Remove any ship associated with the ID.
     * 
     * @see
     * com.example.inputmanagercompat.InputManagerCompat.InputDeviceListener
     * #onInputDeviceRemoved(int)
     */
    @Override
    public void onInputDeviceRemoved(int deviceId) {
        Log.d(TAG,"onInputDeviceRemoved:" + deviceId);
        
        mControllerHelper.onInputDeviceRemoved(deviceId);
    }

    @Override
    protected void onResume() {
        super.onResume();
        
        if (mControllerNibiru != null) {
            mControllerNibiru.onResume();
        }
        if (mControllerMoga != null) {
            mControllerMoga.onResume();
        }
        if (mControllerOuya != null) {
            mControllerOuya.onResume();
        }
        
        GameControllerHelper.gatherControllers(mControllerHelper.mGameController);
    }
    
    @Override
    protected void onPause() {
        if (mControllerNibiru != null) {
            mControllerNibiru.onPause();
        }
        if (mControllerMoga != null) {
            mControllerMoga.onPause();
        }
        if (mControllerOuya != null) {
            mControllerOuya.onPause();
        }
        
        super.onPause();
    }
    
    @Override
    protected void onDestroy() {
        if (mControllerNibiru != null) {
            mControllerNibiru.onDestroy();
        }
        if (mControllerMoga != null) {
            mControllerMoga.onDestroy();
        }
        if (mControllerOuya != null) {
            mControllerOuya.onDestroy();
        }
        
        super.onDestroy();
    }

}