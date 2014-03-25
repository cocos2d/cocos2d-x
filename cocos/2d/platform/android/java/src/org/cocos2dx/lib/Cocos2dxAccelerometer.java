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
import android.util.Log;
import android.view.Display;
import android.view.Surface;
import android.view.WindowManager;
import android.os.Build.*;

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
	private final int mNaturalOrientation;

	// ===========================================================
	// Constructors
	// ===========================================================

	public Cocos2dxAccelerometer(final Context pContext) {
		this.mContext = pContext;

		this.mSensorManager = (SensorManager) this.mContext.getSystemService(Context.SENSOR_SERVICE);
		this.mAccelerometer = this.mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);

		final Display display = ((WindowManager) this.mContext.getSystemService(Context.WINDOW_SERVICE)).getDefaultDisplay();
		this.mNaturalOrientation = display.getOrientation();
	}

	// ===========================================================
	// Getter & Setter
	// ===========================================================

	public void enable() {
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
	public void onSensorChanged(final SensorEvent pSensorEvent) {
		if (pSensorEvent.sensor.getType() != Sensor.TYPE_ACCELEROMETER) {
			return;
		}

		float x = pSensorEvent.values[0];
		float y = pSensorEvent.values[1];
		final float z = pSensorEvent.values[2];

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
		
		Cocos2dxGLSurfaceView.queueAccelerometer(x,y,z,pSensorEvent.timestamp);
		
		/*
		if(BuildConfig.DEBUG) {
			Log.d(TAG, "x = " + pSensorEvent.values[0] + " y = " + pSensorEvent.values[1] + " z = " + pSensorEvent.values[2]);
		}
		*/
	}

	@Override
	public void onAccuracyChanged(final Sensor pSensor, final int pAccuracy) {
	}

	// ===========================================================
	// Methods
        // Native method called from Cocos2dxGLSurfaceView (To be in the same thread)
	// ===========================================================
    
	public static native void onSensorChanged(final float pX, final float pY, final float pZ, final long pTimestamp);

	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================
}
