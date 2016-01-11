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

import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

import android.content.Context;
import android.content.res.Configuration;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.util.Log;
import android.view.Display;
import android.view.Surface;
import android.view.WindowManager;
import android.os.Build.*;

public class Cocos2dxSensor implements SensorEventListener {
    // ===========================================================
    // Constants
    // ===========================================================

    private static final String TAG =
      Cocos2dxSensor.class.getSimpleName();
    // Must match sensor type enum in ccTypes.h
    private static final int[] SENSOR_TYPES = {
      Sensor.TYPE_ACCELEROMETER, Sensor.TYPE_GYROSCOPE,
      Sensor.TYPE_ROTATION_VECTOR, Sensor.TYPE_MAGNETIC_FIELD,
      Sensor.TYPE_LINEAR_ACCELERATION, Sensor.TYPE_GRAVITY};
    private static final Map<Integer, Integer> SENSOR_MAP =
      Collections.unmodifiableMap(
        new HashMap<Integer, Integer>() {{
          for (int i = 0; i < SENSOR_TYPES.length; ++i) {
            put(SENSOR_TYPES[i], i);
          }
        }});

    // ===========================================================
    // Fields
    // ===========================================================

    private final Context mContext;
    private final SensorManager mSensorManager;
    private final int mNaturalOrientation;

    // ===========================================================
    // Constructors
    // ===========================================================

    public Cocos2dxSensor(final Context context) {
        this.mContext = context;

        this.mSensorManager = (SensorManager) this.mContext.getSystemService(Context.SENSOR_SERVICE);

        final Display display = ((WindowManager) this.mContext.getSystemService(Context.WINDOW_SERVICE)).getDefaultDisplay();
        this.mNaturalOrientation = display.getOrientation();
    }

    // ===========================================================
    // Getter & Setter
    // ===========================================================

    public void enable(int type) {
        if (type < 0 || type >= SENSOR_TYPES.length) {
            return;
        }
        this.mSensorManager.registerListener(
          this, this.mSensorManager.getDefaultSensor(SENSOR_TYPES[type]),
          SensorManager.SENSOR_DELAY_GAME);
    }

    public void setInterval(int type, float interval) {
        if (type < 0 || type >= SENSOR_TYPES.length) {
            return;
        }
        // Honeycomb version is 11
        if(android.os.Build.VERSION.SDK_INT < 11) {
            this.mSensorManager.registerListener(
              this, this.mSensorManager.getDefaultSensor(SENSOR_TYPES[type]),
              SensorManager.SENSOR_DELAY_GAME);
        } else {
            //convert seconds to microseconds
            this.mSensorManager.registerListener(
              this, this.mSensorManager.getDefaultSensor(SENSOR_TYPES[type]),
              (int)(interval*100000));
        }
    }

    public void disable(int type) {
        if (type < 0 || type >= SENSOR_TYPES.length) {
            return;
        }
        this.mSensorManager.unregisterListener(
          this, this.mSensorManager.getDefaultSensor(SENSOR_TYPES[type]));
    }

    // ===========================================================
    // Methods for/from SuperClass/Interfaces
    // ===========================================================

    @Override
    public void onSensorChanged(final SensorEvent sensorEvent) {
        float[] values = sensorEvent.values;
        /*
         * Because the axes are not swapped when the device's screen orientation
         * changes. So we should swap it here. In tablets such as Motorola Xoom,
         * the default orientation is landscape, so should consider this.
         * Only x, y axis are swapped. They are values[0] and values[1]. In
         * case of uncalibrated data, value[3] and values[4] are also swapped
         * where values.length is 6. This also covers the case of rotation 
         * vector where the values.length could be 3-5.
         */
        final int orientation =
          this.mContext.getResources().getConfiguration().orientation;
        if (values.length > 2) {
            for (int i = 0; i < values.length - 2; i += 3) {
                if ((orientation == Configuration.ORIENTATION_LANDSCAPE) &&
                    (this.mNaturalOrientation != Surface.ROTATION_0)) {
                    final float tmp = values[i];
                    values[i] = -values[i + 1];
                    values[i + 1] = tmp;
                } else if (
                  (orientation == Configuration.ORIENTATION_PORTRAIT) &&
                  (this.mNaturalOrientation != Surface.ROTATION_0)) {
                    final float tmp = values[i];
                    values[i] = values[i + 1];
                    values[i + 1] = -tmp;
                }
            }
        }
        if (SENSOR_MAP.get(sensorEvent.sensor.getType()) == null) {
          return;
        }
        Cocos2dxGLSurfaceView.queueSensor(SENSOR_MAP.get(
          sensorEvent.sensor.getType()), values, sensorEvent.timestamp);


        // if(BuildConfig.DEBUG) {
        //     Log.d(TAG, "x = " + sensorEvent.values[0] + " y = " + sensorEvent.values[1] + " z = " + sensorEvent.values[2]);
        // }

    }

    @Override
    public void onAccuracyChanged(final Sensor sensor, final int accuracy) {
    }

    // ===========================================================
    // Methods
        // Native method called from Cocos2dxGLSurfaceView (To be in the same thread)
    // ===========================================================

    public static native void onSensorChanged(final int sensorType,
                                              final float[] sensorValues,
                                              final long timestamp);

    // ===========================================================
    // Inner and Anonymous Classes
    // ===========================================================
}
