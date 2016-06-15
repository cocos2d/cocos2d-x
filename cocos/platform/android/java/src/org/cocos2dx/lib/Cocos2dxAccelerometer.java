/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

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

import android.content.Context;
import android.content.res.Configuration;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.view.Display;
import android.view.Surface;
import android.view.WindowManager;

public class Cocos2dxAccelerometer implements SensorEventListener {
    // ===========================================================
    // Constants
    // ===========================================================

    private static final String TAG = Cocos2dxAccelerometer.class.getSimpleName();

    // ===========================================================
    // Fields
    // ===========================================================

    private final Context mContext;
    private final SensorManager mSensorManager;
    private final Sensor mAccelerometer;
    private final Sensor mCompass;
    private final int mNaturalOrientation;
    final float[] accelerometerValues = new float[3];
    final float[] compassFieldValues = new float[3];
    static final float ALPHA = 0.25f; // if ALPHA = 1 OR 0, no filter applies.

    // ===========================================================
    // Constructors
    // ===========================================================

    public Cocos2dxAccelerometer(final Context context) {
        this.mContext = context;

        this.mSensorManager = (SensorManager) this.mContext.getSystemService(Context.SENSOR_SERVICE);
        this.mAccelerometer = this.mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        this.mCompass = this.mSensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);

        final Display display = ((WindowManager) this.mContext.getSystemService(Context.WINDOW_SERVICE)).getDefaultDisplay();
        this.mNaturalOrientation = display.getOrientation();
    }

    // ===========================================================
    // Getter & Setter
    // ===========================================================

    public void enableCompass() {
        this.mSensorManager.registerListener(this, this.mCompass, SensorManager.SENSOR_DELAY_GAME);
    }

    public void enableAccel() {
        this.mSensorManager.registerListener(this, this.mAccelerometer, SensorManager.SENSOR_DELAY_GAME);
    }

    public void setInterval(float interval) {
        // Honeycomb version is 11
        if(android.os.Build.VERSION.SDK_INT < 11) {
            this.mSensorManager.registerListener(this, this.mAccelerometer, SensorManager.SENSOR_DELAY_GAME);
        } else {
            //convert seconds to microseconds
            this.mSensorManager.registerListener(this, this.mAccelerometer, (int)(interval*100000));
        }
    }

    public void disable() {
        this.mSensorManager.unregisterListener(this);
    }

    // ===========================================================
    // Methods for/from SuperClass/Interfaces
    // ===========================================================
    @Override
    public void onSensorChanged(final SensorEvent sensorEvent) {
        if (sensorEvent.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {

            float x = sensorEvent.values[0];
            float y = sensorEvent.values[1];
            final float z = sensorEvent.values[2];

            // needed by VR code
            this.accelerometerValues[0] = x;
            this.accelerometerValues[1] = y;
            this.accelerometerValues[2] = z;

            /*
             * Because the axes are not swapped when the device's screen orientation
             * changes. So we should swap it here. In tablets such as Motorola Xoom,
             * the default orientation is landscape, so should consider this.
             */
            final int orientation = this.mContext.getResources().getConfiguration().orientation;

            if ((orientation == Configuration.ORIENTATION_LANDSCAPE) && (this.mNaturalOrientation != Surface.ROTATION_0)) {
                final float tmp = x;
                x = -y;
                y = tmp;
            } else if ((orientation == Configuration.ORIENTATION_PORTRAIT) && (this.mNaturalOrientation != Surface.ROTATION_0)) {
                final float tmp = x;
                x = y;
                y = -tmp;
            }


            Cocos2dxGLSurfaceView.queueAccelerometer(x,y,z,sensorEvent.timestamp);

            /*
            if(BuildConfig.DEBUG) {
                Log.d(TAG, "x = " + sensorEvent.values[0] + " y = " + sensorEvent.values[1] + " z = " + pSensorEvent.values[2]);
            }
            */
        }
        else if (sensorEvent.sensor.getType() == Sensor.TYPE_MAGNETIC_FIELD) {
            // needed by VR code
            this.compassFieldValues[0] = sensorEvent.values[0];
            this.compassFieldValues[1] = sensorEvent.values[1];
            this.compassFieldValues[2] = sensorEvent.values[2];
        }
    }

    @Override
    public void onAccuracyChanged(final Sensor sensor, final int accuracy) {
    }

    // ===========================================================
    // Methods
        // Native method called from Cocos2dxGLSurfaceView (To be in the same thread)
    // ===========================================================

    public static native void onSensorChanged(final float x, final float y, final float z, final long timestamp);

    // ===========================================================
    // Inner and Anonymous Classes
    // ===========================================================
}
